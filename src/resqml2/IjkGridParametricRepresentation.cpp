/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"; you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-----------------------------------------------------------------------*/

#include "IjkGridParametricRepresentation.h"

#include <stdexcept>

#include <hdf5.h>

#include "AbstractFeatureInterpretation.h"
#include "AbstractLocal3dCrs.h"
#include "AbstractValuesProperty.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace RESQML2_NS;

/// From  https://en.wikipedia.org/w/index.php?title=Spline_%28mathematics%29&oldid=288288033#Algorithm_for_computing_natural_cubic_splines
IjkGridParametricRepresentation::BSpline::BSpline(const vector<double> & parametersAtControlPoint, const std::vector<double> & valuesAtControlPoint)
{
	setParameterAndValueAtControlPoint(parametersAtControlPoint, valuesAtControlPoint);
}

void IjkGridParametricRepresentation::BSpline::setParameterAndValueAtControlPoint(const std::vector<double> & parametersAtControlPoint, const std::vector<double> & valuesAtControlPoint)
{
	a = valuesAtControlPoint;
	parameter = parametersAtControlPoint;

	checkIfParametersIncreaseOrDecrease();

	vector<double> h(parametersAtControlPoint.size() - 1);
	for (size_t i = 0; i < parametersAtControlPoint.size() - 1; ++i) {
		h[i] = parametersAtControlPoint[i + 1] - parametersAtControlPoint[i];
	}

	vector<double> alpha(h.size());
	alpha[0] = numeric_limits<double>::signaling_NaN();
	for (size_t i = 1; i < h.size(); ++i) {
		alpha[i] = 3.0 * (valuesAtControlPoint[i + 1] - valuesAtControlPoint[i]) / h[i] - 3.0 * (valuesAtControlPoint[i] - valuesAtControlPoint[i - 1]) / h[i - 1];
	}

	c.resize(parametersAtControlPoint.size());
	vector<double> l(parametersAtControlPoint.size());
	vector<double> mu(parametersAtControlPoint.size());
	vector<double> z(parametersAtControlPoint.size());
	l[0] = 1;
	mu[0] = 0;
	z[0] = 0;
	for (size_t i = 1; i < h.size(); ++i) {
		l[i] = 2 * (parametersAtControlPoint[i + 1] - parametersAtControlPoint[i - 1]) - h[i - 1] * mu[i - 1];
		mu[i] = h[i] / l[i];
		z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
	}

	l[l.size() - 1] = 1;
	z[z.size() - 1] = 0;
	c[c.size() - 1] = 0;
	b.resize(h.size());
	d.resize(h.size());
	for (int i = h.size() - 1; i >= 0; --i) {
		c[i] = z[i] - mu[i] * c[i + 1];
		b[i] = (valuesAtControlPoint[i + 1] - valuesAtControlPoint[i]) / h[i] - h[i] * (c[i + 1] + 2 * c[i]) / 3;
		d[i] = (c[i + 1] - c[i]) / (3 * h[i]);
	}
}

void IjkGridParametricRepresentation::BSpline::checkIfParametersIncreaseOrDecrease()
{
	if (parameter.empty() || parameter.size() != a.size()) {
		throw invalid_argument("Given parameter or value array are inconsistent.");
	}

	// initialization
	for (size_t i = 0; i < parameter.size() - 1; ++i) {
		if (parameter[i] != parameter[i] || parameter[i + 1] != parameter[i + 1]) {
			throw invalid_argument("Control points with NaN parameter are not supported yet.");
		}

		if (parameter[i + 1] > parameter[i]) {
			areParametersIncreasing = true;
			break;
		}
		else if (parameter[i + 1] < parameter[i]) {
			areParametersIncreasing = false;
			break;
		}
		else {
			throw invalid_argument("Control points with equal parameter are not supported yet.");
		}
	}

	// Checking
	if (areParametersIncreasing) {
		for (size_t i = 0; i < parameter.size() - 1; ++i) {
			if (parameter[i + 1] <= parameter[i]) {
				throw invalid_argument("Control points are not ordered increasingly.");
			}
		}
	}
	else {
		for (size_t i = 0; i < parameter.size() - 1; ++i) {
			if (parameter[i + 1] >= parameter[i]) {
				throw invalid_argument("Control points are not ordered decreasingly.");
			}
		}
	}
}

size_t IjkGridParametricRepresentation::BSpline::getSplineIndexFromParameter(double param) const
{
	size_t splineIndex = 0;
	if (areParametersIncreasing) {
		if (param <= parameter[0]) {
			return 0; // extrapolation if param < parameter[0]
		}
		while (splineIndex < parameter.size() && parameter[splineIndex] < param) {
			splineIndex++;
		}
	}
	else {
		if (param >= parameter[0]) {
			return 0; // extrapolation if param < parameter[0]
		}
		while (splineIndex < parameter.size() && parameter[splineIndex] > param) {
			splineIndex++;
		}
	}

	return splineIndex == parameter.size()
		? splineIndex - 2 // extrapolation
		: splineIndex - 1; // interpolation
}

double IjkGridParametricRepresentation::BSpline::getValueFromParameter(double param) const
{
	if (param != param) {
		throw invalid_argument("Cannot return a value for a NaN parameter.");
	}

	const size_t splineIndex = getSplineIndexFromParameter(param);

	const double deltaParam = param - parameter[splineIndex];
	const double deltaParam2 = deltaParam * deltaParam;

	return a[splineIndex] +
		b[splineIndex] * deltaParam +
		c[splineIndex] * deltaParam2 +
		d[splineIndex] * deltaParam2 * deltaParam;
}

void IjkGridParametricRepresentation::getControlPoints(double * controlPoints, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) const
{
	string datasetPath;
	EML2_NS::AbstractHdfProxy* hdfProxy = getControlPointDatasetPath(datasetPath);
	hdfProxy->readArrayNdOfDoubleValues(datasetPath, controlPoints);

	if (reverseIAxis || reverseJAxis || reverseKAxis)
	{
		unsigned int iPillarCount = getICellCount() + 1;
		unsigned int jPillarCount = getJCellCount() + 1;
		unsigned int arrayCount = iPillarCount * jPillarCount * getControlPointMaxCountPerPillar() * 3;

		// Copy in order not to modify the controlPoints pointer
		std::unique_ptr<double[]> reversedControlPoints(new double[arrayCount]);
		for (unsigned int index = 0; index < arrayCount; ++index) {
			reversedControlPoints[index] = controlPoints[index];
		}

		if (reverseIAxis) {
			unsigned int controlPointIndex = 0;
			for (unsigned int k = 0; k < getControlPointMaxCountPerPillar(); ++k) {
				for (unsigned int j = 0; j < jPillarCount; ++j) {
					for (unsigned int i = 0; i < iPillarCount; ++i) {
						unsigned int reversedControlPointIndex = getICellCount() - i + j * iPillarCount + k * iPillarCount*jPillarCount;
						controlPoints[controlPointIndex * 3] = reversedControlPoints[reversedControlPointIndex * 3];
						controlPoints[controlPointIndex * 3 + 1] = reversedControlPoints[reversedControlPointIndex * 3 + 1];
						controlPoints[controlPointIndex * 3 + 2] = reversedControlPoints[reversedControlPointIndex * 3 + 2];
						++controlPointIndex;
					}
				}
			}
		}

		if (reverseJAxis) {
			unsigned int controlPointIndex = 0;
			for (unsigned int k = 0; k < getControlPointMaxCountPerPillar(); ++k) {
				for (unsigned int j = 0; j < jPillarCount; ++j) {
					for (unsigned int i = 0; i < iPillarCount; ++i) {
						unsigned int reversedControlPointIndex = i + (getJCellCount() - j)*iPillarCount + k * iPillarCount*jPillarCount;
						controlPoints[controlPointIndex * 3] = reversedControlPoints[reversedControlPointIndex * 3];
						controlPoints[controlPointIndex * 3 + 1] = reversedControlPoints[reversedControlPointIndex * 3 + 1];
						controlPoints[controlPointIndex * 3 + 2] = reversedControlPoints[reversedControlPointIndex * 3 + 2];
						++controlPointIndex;
					}
				}
			}
		}

		if (reverseKAxis)
		{
			unsigned int controlPointIndex = 0;
			for (unsigned int k = 0; k < getControlPointMaxCountPerPillar(); ++k)
			{
				for (unsigned int j = 0; j < jPillarCount; ++j)
				{
					for (unsigned int i = 0; i < iPillarCount; ++i)
					{
						unsigned int reversedControlPointIndex = i + j * iPillarCount + (getControlPointMaxCountPerPillar() - 1 - k)*iPillarCount*jPillarCount;
						controlPoints[controlPointIndex * 3] = reversedControlPoints[reversedControlPointIndex * 3];
						controlPoints[controlPointIndex * 3 + 1] = reversedControlPoints[reversedControlPointIndex * 3 + 1];
						controlPoints[controlPointIndex * 3 + 2] = reversedControlPoints[reversedControlPointIndex * 3 + 2];
						++controlPointIndex;
					}
				}
			}
		}
	}
}

void IjkGridParametricRepresentation::getControlPointParameters(double * controlPointParameters, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) const
{
	string datasetPath;
	EML2_NS::AbstractHdfProxy* hdfProxy = getControlPointParametersDatasetPath(datasetPath);
	hdfProxy->readArrayNdOfDoubleValues(datasetPath, controlPointParameters);
	
	if (reverseIAxis || reverseJAxis || reverseKAxis)
	{
		unsigned int iPillarCount = getICellCount()+1;
		unsigned int jPillarCount = getJCellCount()+1;
		unsigned int arrayCount = iPillarCount * jPillarCount * getControlPointMaxCountPerPillar();

		// Copy in order not to modify the controlPoints pointer
		std::unique_ptr<double[]> reversedControlPointParameters(new double[arrayCount]);
		for (unsigned int index = 0; index < arrayCount; ++index) {
			reversedControlPointParameters[index] = controlPointParameters[index];
		}

		if (reverseIAxis) {
			unsigned int controlPointIndex = 0;
			for (unsigned int k = 0; k < getControlPointMaxCountPerPillar(); ++k) {
				for (unsigned int j = 0; j < jPillarCount; ++j) {
					for (unsigned int i = 0; i < iPillarCount; ++i) {
						unsigned int reversedControlPointIndex = getICellCount() - i + j*iPillarCount + k*iPillarCount*jPillarCount;
						controlPointParameters[controlPointIndex] = reversedControlPointParameters[reversedControlPointIndex];
						++controlPointIndex;
					}
				}
			}
		}

		if (reverseJAxis) {
			unsigned int controlPointIndex = 0;
			for (unsigned int k = 0; k < getControlPointMaxCountPerPillar(); ++k) {
				for (unsigned int j = 0; j < jPillarCount; ++j) {
					for (unsigned int i = 0; i < iPillarCount; ++i) {
						unsigned int reversedControlPointIndex = i + (getJCellCount() - j)*iPillarCount + k*iPillarCount*jPillarCount;
						controlPointParameters[controlPointIndex] = reversedControlPointParameters[reversedControlPointIndex];
						++controlPointIndex;
					}
				}
			}
		}

		if (reverseKAxis) {
			unsigned int controlPointIndex = 0;
			for (unsigned int k = 0; k < getControlPointMaxCountPerPillar(); ++k) {
				for (unsigned int j = 0; j < jPillarCount; ++j) {
					for (unsigned int i = 0; i < iPillarCount; ++i) {
						unsigned int reversedControlPointIndex = i + j*iPillarCount + (getControlPointMaxCountPerPillar()-1-k)*iPillarCount*jPillarCount;
						controlPointParameters[controlPointIndex] = reversedControlPointParameters[reversedControlPointIndex];
						++controlPointIndex;
					}
				}
			}
		}
	}
}

void IjkGridParametricRepresentation::getParametricLineKind(short * pillarKind, bool reverseIAxis, bool reverseJAxis) const
{
	getRawParametricLineKind(pillarKind);

	if (reverseIAxis || reverseJAxis)
	{
		unsigned int iPillarCount = getICellCount()+1;
		unsigned int jPillarCount = getJCellCount()+1;
		unsigned int arrayCount = iPillarCount * jPillarCount;

		// Copy in order not to modify the controlPoints pointer
		std::unique_ptr<double[]> initialPillarKind(new double [arrayCount]);
		for (unsigned int index = 0; index < arrayCount; ++index) {
			initialPillarKind[index] = pillarKind[index];
		}

		if (reverseIAxis) {
			unsigned int pillarIndex = 0;
			for (unsigned int j = 0; j < jPillarCount; ++j) {
				for (unsigned int i = 0; i < iPillarCount; ++i) {
					pillarKind[pillarIndex] = initialPillarKind[getICellCount() - i + j*iPillarCount];
					++pillarIndex;
				}
			}
		}

		if (reverseJAxis) {
			unsigned int pillarIndex = 0;
			for (unsigned int j = 0; j < jPillarCount; ++j) {
				for (unsigned int i = 0; i < iPillarCount; ++i) {
					pillarKind[pillarIndex] = initialPillarKind[i + (getJCellCount() - j)*iPillarCount];
					++pillarIndex;
				}
			}
		}
	}
}

void IjkGridParametricRepresentation::getParametersOfNodes(double * parameters, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) const
{
	string datasetPath;
	EML2_NS::AbstractHdfProxy* hdfProxy = getParametersOfNodesDatasetPath(datasetPath);
	hdfProxy->readArrayNdOfDoubleValues(datasetPath, parameters);

	// Copy in order not to modify the controlPoints pointer
	if (reverseIAxis || reverseJAxis || reverseKAxis)
	{
		unsigned int iPillarCount = getICellCount()+1;
		unsigned int jPillarCount = getJCellCount()+1;
		unsigned int kNodeCount = getKCellCount()+1;
		unsigned int arrayCount = iPillarCount * jPillarCount * kNodeCount + getSplitCoordinateLineCount()*kNodeCount;
		std::unique_ptr<double[]> initialParameters(new double[arrayCount]);
		for (unsigned int index = 0; index < arrayCount; ++index) {
			initialParameters[index] = parameters[index];
		}

		if (reverseIAxis) {
			unsigned int nodeIndex = 0;
			for (unsigned int k = 0; k < kNodeCount; ++k) {
				for (unsigned int j = 0; j < jPillarCount; ++j) {
					for (unsigned int i = 0; i < iPillarCount; ++i) {
						parameters[nodeIndex] = initialParameters[getICellCount() - i + j*iPillarCount + k*(jPillarCount*iPillarCount+getSplitCoordinateLineCount())];
						++nodeIndex;
					}
				}
				nodeIndex += getSplitCoordinateLineCount();
			}
		}

		if (reverseJAxis) {
			unsigned int nodeIndex = 0;
			for (unsigned int k = 0; k < kNodeCount; ++k) {
				for (unsigned int j = 0; j < jPillarCount; ++j) {
					for (unsigned int i = 0; i < iPillarCount; ++i) {
						parameters[nodeIndex] = initialParameters[i + (getJCellCount() -j)*iPillarCount + k*(jPillarCount*iPillarCount+getSplitCoordinateLineCount())];
						++nodeIndex;
					}
				}
				nodeIndex += getSplitCoordinateLineCount();
			}
		}

		if (reverseKAxis) {
			unsigned int nodeIndex = 0;
			for (unsigned int k = 0; k < kNodeCount; ++k) {
				for (unsigned int j = 0; j < jPillarCount; ++j) {
					for (unsigned int i = 0; i < iPillarCount; ++i) {
						parameters[nodeIndex] = initialParameters[i + j*iPillarCount + (getKCellCount() - k)*(jPillarCount*iPillarCount+getSplitCoordinateLineCount())];
						++nodeIndex;
					}
				}
				nodeIndex += getSplitCoordinateLineCount();
			}
		}
	}
}

void IjkGridParametricRepresentation::getParametersOfNodesOfKInterfaceSequence(unsigned int kInterfaceStart, unsigned int kInterfaceEnd, double * parameters)
{
	if (kInterfaceStart > getKCellCount() || kInterfaceEnd > getKCellCount()) {
		throw out_of_range("kInterfaceStart and/or kInterfaceEnd is/are out of boundaries.");
	}
	if (kInterfaceStart > kInterfaceEnd) {
		throw out_of_range("kInterfaceStart > kInterfaceEnd");
	}
	if (parameters == nullptr) {
		throw invalid_argument("xyzPoints must be allocated.");
	}

	string datasetPath;
	EML2_NS::AbstractHdfProxy* hdfProxy = getParametersOfNodesDatasetPath(datasetPath);
	const unsigned long long numValuesInEachDimension[2] = { kInterfaceEnd - kInterfaceStart + 1, getXyzPointCountOfKInterface() };
	const unsigned long long offsetInEachDimension[2] = { kInterfaceStart, 0 };
	hdfProxy->readArrayNdOfDoubleValues(datasetPath, parameters, numValuesInEachDimension, offsetInEachDimension, 2);
}

void IjkGridParametricRepresentation::getXyzPointsOfKInterfaceSequence(unsigned int kInterfaceStart, unsigned int kInterfaceEnd, double * xyzPoints)
{
	if (xyzPoints == nullptr) {
		throw invalid_argument("xyzPoints must be allocated.");
	}
	if (kInterfaceEnd < kInterfaceStart) {
		throw range_error("kInterfaceEnd cannot be inferior to kInterfaceStart");
	}

	// Get the parameters
	const ULONG64 xyzPointCount = getXyzPointCountOfKInterface();
	std::unique_ptr<double[]> parameters(new double[xyzPointCount * (kInterfaceEnd - kInterfaceStart + 1)]);
	getParametersOfNodesOfKInterfaceSequence(kInterfaceStart, kInterfaceEnd, parameters.get());

	// Convert the parameters into XYZ points
	if (pillarInformation == nullptr)
	{
		pillarInformation = new PillarInformation();
		loadPillarInformation(*pillarInformation);
	}

	//Mapping
	size_t paramIndex = 0;
	for (unsigned int pillarIndex = 0; pillarIndex < pillarInformation->parametricLineCount; ++pillarIndex) {
		if (pillarInformation->pillarKind[pillarIndex] == -1 || parameters[paramIndex] != parameters[paramIndex]) { // not defined line
			for (unsigned int k = 0; k <= kInterfaceEnd - kInterfaceStart; ++k) {
				xyzPoints[(k * xyzPointCount + paramIndex) * 3] = std::numeric_limits<double>::quiet_NaN();
				xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 1] = std::numeric_limits<double>::quiet_NaN();
				xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = std::numeric_limits<double>::quiet_NaN();
			}
		}
		else if (pillarInformation->pillarKind[pillarIndex] == 0) { // vertical (parameter must be the Z value)
			for (unsigned int k = 0; k <= kInterfaceEnd - kInterfaceStart; ++k) {
				xyzPoints[(k * xyzPointCount + paramIndex) * 3] = pillarInformation->controlPoints[pillarIndex * 3];
				xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 1] = pillarInformation->controlPoints[pillarIndex * 3 + 1];
				xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = parameters[(k * xyzPointCount) + paramIndex];
			}
		}
		else if (pillarInformation->pillarKind[pillarIndex] == 1) { // linear interpolation
			unsigned int controlPointCount = 0;
			while (controlPointCount < pillarInformation->maxControlPointCount &&
				pillarInformation->controlPoints[(pillarIndex + controlPointCount*pillarInformation->parametricLineCount) * 3] == 
				pillarInformation->controlPoints[(pillarIndex + controlPointCount*pillarInformation->parametricLineCount) * 3]) {
				controlPointCount++;
			}

			// Control point count on this line
			if (controlPointCount == 2) { // straight
				double parameterDistance = .0;
				if (pillarInformation->controlPointParameters != nullptr)
					parameterDistance = pillarInformation->controlPointParameters[pillarIndex + pillarInformation->parametricLineCount] - 
										pillarInformation->controlPointParameters[pillarIndex]; // Parameter distance from top to bottom.
				else // Should never occur by business rule. Assume the parameters are Z values for now (workaround for some softwares)....
					parameterDistance = pillarInformation->controlPoints[(pillarIndex + pillarInformation->parametricLineCount) * 3 + 2] - pillarInformation->controlPoints[pillarIndex * 3 + 2]; // Parameter distance from top to bottom.

				const double xDist = (pillarInformation->controlPoints[(pillarIndex + pillarInformation->parametricLineCount) * 3] - pillarInformation->controlPoints[pillarIndex * 3]);
				const double yDist = (pillarInformation->controlPoints[(pillarIndex + pillarInformation->parametricLineCount) * 3 + 1] - pillarInformation->controlPoints[pillarIndex * 3 + 1]);
				const double zDist = (pillarInformation->controlPoints[(pillarIndex + pillarInformation->parametricLineCount) * 3 + 2] - pillarInformation->controlPoints[pillarIndex * 3 + 2]);

				double ratioFromFirstControlPoint = .0;
				for (unsigned int k = 0; k <= kInterfaceEnd - kInterfaceStart; ++k)
				{
					if (parameterDistance != .0)
						if (pillarInformation->controlPointParameters != nullptr)
							ratioFromFirstControlPoint = (parameters[(k * xyzPointCount) + paramIndex] - pillarInformation->controlPointParameters[pillarIndex]) / parameterDistance;
						else
							ratioFromFirstControlPoint = (parameters[(k * xyzPointCount) + paramIndex] - pillarInformation->controlPoints[pillarIndex * 3 + 2]) / parameterDistance;
					else
						ratioFromFirstControlPoint = .0;

					xyzPoints[(k * xyzPointCount + paramIndex) * 3] = pillarInformation->controlPoints[pillarIndex * 3] + ratioFromFirstControlPoint * xDist;
					xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 1] = pillarInformation->controlPoints[pillarIndex * 3 + 1] + ratioFromFirstControlPoint * yDist;
					xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = pillarInformation->controlPoints[pillarIndex * 3 + 2] + ratioFromFirstControlPoint * zDist;
				}
			}
			else { // piecewise linear

				//unsigned int previousControlPoint = 0;
				//if (pillarInformation->controlPointParameters != nullptr) {
				//	while ((parameters[paramIndex] < pillarInformation->controlPointParameters[coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint] && parameters[paramIndex] < pillarInformation->controlPointParameters[coordLineIndex + pillarInformation->parametricLineCount*(previousControlPoint + 1)]) ||
				//		(parameters[paramIndex] > pillarInformation->controlPointParameters[coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint] && parameters[paramIndex] > pillarInformation->controlPointParameters[coordLineIndex + pillarInformation->parametricLineCount*(previousControlPoint + 1)]) &&
				//		previousControlPoint < controlPointCount - 1) {
				//		++previousControlPoint;
				//	}
				//}
				//else { // Should never occur by business rule. Assume the parameters are Z values for now (workaround for some softwares)....
				//	while ((parameters[paramIndex] < pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3 + 2] && parameters[paramIndex] < pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*(previousControlPoint + 1)) * 3 + 2]) ||
				//		(parameters[paramIndex] > pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3 + 2] && parameters[paramIndex] > pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*(previousControlPoint + 1)) * 3 + 2]) &&
				//		previousControlPoint < controlPointCount - 1) {
				//		++previousControlPoint;
				//	}
				//}

				//if (previousControlPoint == controlPointCount - 1) {
				//	throw invalid_argument("Cannot extrapolate piecewiselinear pillar for now to explicit a grid node.");
				//}

				//double ratioFromPreviousControlPoint = .0;
				//double parameterDistance = .0;
				//if (pillarInformation->controlPointParameters != nullptr) {
				//	parameterDistance = pillarInformation->controlPointParameters[coordLineIndex + pillarInformation->parametricLineCount*(previousControlPoint + 1)] - pillarInformation->controlPointParameters[coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint]; // Parameter distance from top to bottom.
				//	if (parameterDistance != .0)
				//		ratioFromPreviousControlPoint = (parameters[paramIndex] - pillarInformation->controlPointParameters[coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint]) / parameterDistance;
				//}
				//else { // Should never occur by business rule. Assume the parameters are Z values for now (workaround for some softwares)....
				//	parameterDistance = pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*(previousControlPoint + 1)) * 3 + 2] - pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3 + 2]; // Parameter distance from top to bottom.
				//	if (parameterDistance != .0) {
				//		ratioFromPreviousControlPoint = (parameters[paramIndex] - pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3 + 2]) / parameterDistance;
				//	}
				//}
				//xyzPoints[paramIndex * 3] = pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3] + ratioFromPreviousControlPoint * (pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount) * 3] - pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3]);
				//xyzPoints[paramIndex * 3 + 1] = pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3 + 1] + ratioFromPreviousControlPoint * (pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*(previousControlPoint + 1)) * 3 + 1] - pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3 + 1]);
				//xyzPoints[paramIndex * 3 + 2] = pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3 + 2] + ratioFromPreviousControlPoint * (pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*(previousControlPoint + 1)) * 3 + 2] - pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3 + 2]);

				//// TODO AND TO VERIFY ABOVE (MERGE PIECEWISE AND LINEAR (only 2 control points) IF POSSIBLE)

				//delete[] parameters;
				throw logic_error("Piecewise linear pillars are not implemented yet");
			}
		}
		else if (pillarInformation->pillarKind[pillarIndex] == 2 || pillarInformation->pillarKind[pillarIndex] == 4) { // XY Natural cubic spline
			for (unsigned int k = 0; k <= kInterfaceEnd - kInterfaceStart; ++k) {
				xyzPoints[(k * xyzPointCount + paramIndex) * 3] = pillarInformation->splines[pillarIndex][0].getValueFromParameter(parameters[k * xyzPointCount + paramIndex]);
				xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 1] = pillarInformation->splines[pillarIndex][1].getValueFromParameter(parameters[k * xyzPointCount + paramIndex]);
				if (pillarInformation->pillarKind[pillarIndex] == 2) { //  Z natural cubic spline
					xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = pillarInformation->splines[pillarIndex][2].getValueFromParameter(parameters[k * xyzPointCount + paramIndex]);
				}
				else { // Z linear cubic spline
					xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = parameters[k * xyzPointCount + paramIndex];
				}
			}
		}
		else {
			throw logic_error("Computing XYZ from parameters on a non natural cubic spline or on a minimum curvature spline is not implemented yet.");
		}
		++paramIndex;
	}

	for (unsigned int splitLineIndex = 0; splitLineIndex < pillarInformation->splitLineCount; ++splitLineIndex)
	{
		unsigned int pillarIndex = pillarInformation->pillarOfSplitCoordLines[splitLineIndex];
		if (pillarInformation->pillarKind[pillarIndex] == -1 || parameters[paramIndex] != parameters[paramIndex]) { // not defined line
			for (unsigned int k = 0; k <= kInterfaceEnd - kInterfaceStart; ++k) {
				xyzPoints[(k * xyzPointCount + paramIndex) * 3] = std::numeric_limits<double>::quiet_NaN();
				xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 1] = std::numeric_limits<double>::quiet_NaN();
				xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = std::numeric_limits<double>::quiet_NaN();
			}
		}
		else if (pillarInformation->pillarKind[pillarIndex] == 0) { // vertical (parameter must be the Z value)
			for (unsigned int k = 0; k <= kInterfaceEnd - kInterfaceStart; ++k) {
				xyzPoints[(k * xyzPointCount + paramIndex) * 3] = pillarInformation->controlPoints[pillarIndex * 3];
				xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 1] = pillarInformation->controlPoints[pillarIndex * 3 + 1];
				xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = parameters[k * xyzPointCount + paramIndex];
			}
		}
		else if (pillarInformation->pillarKind[pillarIndex] == 1) { // Linear interpolation
			unsigned int controlPointCount = 0;
			while (controlPointCount < pillarInformation->maxControlPointCount &&
				pillarInformation->controlPoints[(pillarIndex + controlPointCount*pillarInformation->parametricLineCount) * 3] == pillarInformation->controlPoints[(pillarIndex + controlPointCount*pillarInformation->parametricLineCount) * 3]) {
				controlPointCount++;
			}

			// Control point count on this line
			if (controlPointCount == 2) { // straight
				double parameterDistance = .0;
				if (pillarInformation->controlPointParameters != nullptr)
					parameterDistance = pillarInformation->controlPointParameters[pillarIndex + pillarInformation->parametricLineCount] - pillarInformation->controlPointParameters[pillarIndex]; // Parameter distance from top to bottom.
				else // Should never occur by business rule. Assume the parameters are Z values for now (workaround for some softwares)....
					parameterDistance = pillarInformation->controlPoints[(pillarIndex + pillarInformation->parametricLineCount) * 3 + 2] - pillarInformation->controlPoints[pillarIndex * 3 + 2]; // Parameter distance from top to bottom.

				double xDist = pillarInformation->controlPoints[(pillarIndex + pillarInformation->parametricLineCount) * 3] - pillarInformation->controlPoints[pillarIndex * 3];
				double yDist = pillarInformation->controlPoints[(pillarIndex + pillarInformation->parametricLineCount) * 3 + 1] - pillarInformation->controlPoints[pillarIndex * 3 + 1];
				double zDist = pillarInformation->controlPoints[(pillarIndex + pillarInformation->parametricLineCount) * 3 + 2] - pillarInformation->controlPoints[pillarIndex * 3 + 2];

				double ratioFromFirstControlPoint = .0;
				for (unsigned int k = 0; k <= kInterfaceEnd - kInterfaceStart; ++k) {
					if (parameterDistance != .0) {
						if (pillarInformation->controlPointParameters != nullptr)
							ratioFromFirstControlPoint = (parameters[(k * xyzPointCount) + paramIndex] - pillarInformation->controlPointParameters[pillarIndex]) / parameterDistance;
						else { // Should never occur by business rule. Assume the parameters are Z values for now (workaround for some softwares)....
							ratioFromFirstControlPoint = (parameters[(k * xyzPointCount) + paramIndex] - pillarInformation->controlPoints[pillarIndex * 3 + 2]) / parameterDistance;
						}
					}
					else
						ratioFromFirstControlPoint = .0;

					xyzPoints[(k * xyzPointCount + paramIndex) * 3] = pillarInformation->controlPoints[pillarIndex * 3] + ratioFromFirstControlPoint * xDist;
					xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 1] = pillarInformation->controlPoints[pillarIndex * 3 + 1] + ratioFromFirstControlPoint * yDist;
					xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = pillarInformation->controlPoints[pillarIndex * 3 + 2] + ratioFromFirstControlPoint * zDist;
				}
			}
			else { // piecewise linear
				throw logic_error("Piecewise linear pillars are not implemented yet");
			}
		}
		else if (pillarInformation->pillarKind[pillarIndex] == 2 || pillarInformation->pillarKind[pillarIndex] == 4) { // XY Natural cubic spline
			for (unsigned int k = 0; k <= kInterfaceEnd - kInterfaceStart; ++k) {
				xyzPoints[(k * xyzPointCount + paramIndex) * 3] = pillarInformation->splines[pillarIndex][0].getValueFromParameter(parameters[k * xyzPointCount + paramIndex]);
				xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 1] = pillarInformation->splines[pillarIndex][1].getValueFromParameter(parameters[k * xyzPointCount + paramIndex]);
				if (pillarInformation->pillarKind[pillarIndex] == 2) { //  Z natural cubic spline
					xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = pillarInformation->splines[pillarIndex][2].getValueFromParameter(parameters[k * xyzPointCount + paramIndex]);
				}
				else { // Z linear cubic spline
					xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = parameters[k * xyzPointCount + paramIndex];
				}
			}
		}
		else {
			throw logic_error("Computing XYZ from parameters on a non natural cubic spline or on a minimum curvature spline is not implemented yet.");
		}
		++paramIndex;
	}
}

void IjkGridParametricRepresentation::getXyzPointsOfBlock(double * xyzPoints)
{
	if (blockInformation == nullptr) {
		throw logic_error("The block information must have been loaded first.");
	}

	if (xyzPoints == nullptr) {
		throw invalid_argument("xyzPoints must be allocated.");
	}

	if (pillarInformation == nullptr)
	{
		pillarInformation = new PillarInformation();
		loadPillarInformation(*pillarInformation);
	}

	// following lines for time testing
	//if (pillarInformation != nullptr)
	//	delete pillarInformation;
	//pillarInformation = new PillarInformation();
	//loadPillarInformation(*pillarInformation);

	ULONG64 xyzPointCount =	(blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1) *  (blockInformation->jInterfaceEnd - blockInformation->jInterfaceStart + 1) + getBlockSplitCoordinateLineCount(); 

	// parameters : ordered
	std::unique_ptr<double[]> parameters(new double[getXyzPointCountOfBlock()]);
	unsigned long long blockCountPerDimension[2] = { 1, blockInformation->jInterfaceEnd - blockInformation->jInterfaceStart + 1 };
	unsigned long long offsetPerDimension[2] = { blockInformation->kInterfaceStart , blockInformation->jInterfaceStart * (getICellCount() + 1) + blockInformation->iInterfaceStart };
	unsigned long long strideInEachDimension[2] = { 1, (blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1) + ((getICellCount() + 1) - (blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1)) };
	unsigned long long blockSizeInEachDimension[2] = { blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart + 1, blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1 };

	std::string datasetPathInExternalFile;
	EML2_NS::AbstractHdfProxy* hdfProxy = getParameterDatasetPath(datasetPathInExternalFile);

	hid_t dataset, filespace;
	hdfProxy->selectArrayNdOfValues(
		datasetPathInExternalFile,
		blockCountPerDimension,
		offsetPerDimension,
		strideInEachDimension,
		blockSizeInEachDimension,
		2,
		true,
		dataset,
		filespace);

	unsigned long long slab_size = 1;
	for (size_t h = 0; h < 2; ++h) {
		slab_size *= blockSizeInEachDimension[h];
	}
	for (size_t h = 0; h < 2; ++h) {
		slab_size *= blockCountPerDimension[h];
	}

	// Adding block split coordinate lines to the selected regions
	// traversing all bloc pillars in direction i and then in direction j
	for (unsigned int jPillarIndex = blockInformation->jInterfaceStart; jPillarIndex <= blockInformation->jInterfaceEnd; ++jPillarIndex)
	{
		for (unsigned int iPillarIndex = blockInformation->iInterfaceStart; iPillarIndex <= blockInformation->iInterfaceEnd; iPillarIndex++)
		{
			unsigned int pillarIndex = getGlobalIndexPillarFromIjIndex(iPillarIndex, jPillarIndex);

			if (splitInformation[pillarIndex].size() != 0)
			{
				// here is a split pillar

				// traversing all split coordinate lines corresponding to the current splitted pillar
				for (size_t splitCoordinateLineIndex = 0; splitCoordinateLineIndex < splitInformation[pillarIndex].size(); ++splitCoordinateLineIndex)
				{
					// traversing adjacent columns, it current column is in the bloc, corresponding coordinate line is added to the selected region
					for (size_t columnIndex = 0; columnIndex < splitInformation[pillarIndex][splitCoordinateLineIndex].second.size(); ++columnIndex)
					{
						unsigned int iColumnIndex = getIColumnFromGlobalIndex(splitInformation[pillarIndex][splitCoordinateLineIndex].second[columnIndex]);
						unsigned int jColumnIndex = getJColumnFromGlobalIndex(splitInformation[pillarIndex][splitCoordinateLineIndex].second[columnIndex]);

						if ((iColumnIndex >= blockInformation->iInterfaceStart && iColumnIndex < blockInformation->iInterfaceEnd) && (jColumnIndex >= blockInformation->jInterfaceStart && jColumnIndex < blockInformation->jInterfaceEnd))
						{
							// here is a split coordinate line impacting the bloc
							unsigned int splitCoordinateLineHdfIndex = (getICellCount() + 1) * (getJCellCount() + 1) + splitInformation[pillarIndex][splitCoordinateLineIndex].first;

							// the split coordinate line is added to the selected region
							blockCountPerDimension[0] = 1;
							blockCountPerDimension[1] = 1;
							offsetPerDimension[0] = blockInformation->kInterfaceStart;
							offsetPerDimension[1] = splitCoordinateLineHdfIndex;
							strideInEachDimension[0] = 1;
							strideInEachDimension[1] = 1;
							blockSizeInEachDimension[0] = blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart + 1;
							blockSizeInEachDimension[1] = 1;
							
							hdfProxy->selectArrayNdOfValues(
								datasetPathInExternalFile,
								blockCountPerDimension,
								offsetPerDimension,
								strideInEachDimension,
								blockSizeInEachDimension,
								2,
								false,
								dataset,
								filespace);

							slab_size += (blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart + 1);

							break; // in order to be sure not adding twice a same coordinate line if it is adjacent to several columns within the bloc
						}
					}
				}
			}
		}
	}

	// reading values corresponding to the whole selected region (non splitted and splitted part)
	hdfProxy->readArrayNdOfDoubleValues(dataset, filespace, parameters.get(), slab_size);

	//Mapping
	size_t paramIndex = 0;
	for (unsigned int j = blockInformation->jInterfaceStart; j <= blockInformation->jInterfaceEnd; ++j)
	{
		for (unsigned int i = blockInformation->iInterfaceStart; i <= blockInformation->iInterfaceEnd; ++i) {
		//for (unsigned int pillarIndex = 0; pillarIndex < pillarInformation->parametricLineCount; ++pillarIndex) {
			unsigned int pillarIndex = i + j * (getICellCount()+1);
			if (pillarInformation->pillarKind[pillarIndex] == -1 || parameters[paramIndex] != parameters[paramIndex]) { // not defined line
				for (unsigned int k = 0; k <= blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart; ++k) {
					xyzPoints[(k * xyzPointCount + paramIndex) * 3] = std::numeric_limits<double>::quiet_NaN();
					xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 1] = std::numeric_limits<double>::quiet_NaN();
					xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = std::numeric_limits<double>::quiet_NaN();
				}
			}
			else if (pillarInformation->pillarKind[pillarIndex] == 0) { // vertical (parameter must be the Z value)
				for (unsigned int k = 0; k <= blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart; ++k) {
					xyzPoints[(k * xyzPointCount + paramIndex) * 3] = pillarInformation->controlPoints[pillarIndex * 3];
					xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 1] = pillarInformation->controlPoints[pillarIndex * 3 + 1];
					xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = parameters[(k * xyzPointCount) + paramIndex];
				}
			}
			else if (pillarInformation->pillarKind[pillarIndex] == 1) { // linear interpolation
				unsigned int controlPointCount = 0;
				while (controlPointCount < pillarInformation->maxControlPointCount &&
					pillarInformation->controlPoints[(pillarIndex + controlPointCount*pillarInformation->parametricLineCount) * 3] ==
					pillarInformation->controlPoints[(pillarIndex + controlPointCount*pillarInformation->parametricLineCount) * 3]) {
					controlPointCount++;
				}

				// Control point count on this line
				if (controlPointCount == 2) { // straight
					double parameterDistance = .0;
					if (pillarInformation->controlPointParameters != nullptr)
						parameterDistance = pillarInformation->controlPointParameters[pillarIndex + pillarInformation->parametricLineCount] -
						pillarInformation->controlPointParameters[pillarIndex]; // Parameter distance from top to bottom.
					else // Should never occur by business rule. Assume the parameters are Z values for now (workaround for some softwares)....
						parameterDistance = pillarInformation->controlPoints[(pillarIndex + pillarInformation->parametricLineCount) * 3 + 2] - pillarInformation->controlPoints[pillarIndex * 3 + 2]; // Parameter distance from top to bottom.

					const double xDist = (pillarInformation->controlPoints[(pillarIndex + pillarInformation->parametricLineCount) * 3] - pillarInformation->controlPoints[pillarIndex * 3]);
					const double yDist = (pillarInformation->controlPoints[(pillarIndex + pillarInformation->parametricLineCount) * 3 + 1] - pillarInformation->controlPoints[pillarIndex * 3 + 1]);
					const double zDist = (pillarInformation->controlPoints[(pillarIndex + pillarInformation->parametricLineCount) * 3 + 2] - pillarInformation->controlPoints[pillarIndex * 3 + 2]);

					double ratioFromFirstControlPoint = .0;
					for (unsigned int k = 0; k <= blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart; ++k)
					{
						if (parameterDistance != .0)
							if (pillarInformation->controlPointParameters != nullptr)
								ratioFromFirstControlPoint = (parameters[(k * xyzPointCount) + paramIndex] - pillarInformation->controlPointParameters[pillarIndex]) / parameterDistance;
							else
								ratioFromFirstControlPoint = (parameters[(k * xyzPointCount) + paramIndex] - pillarInformation->controlPoints[pillarIndex * 3 + 2]) / parameterDistance;
						else
							ratioFromFirstControlPoint = .0;

						xyzPoints[(k * xyzPointCount + paramIndex) * 3] = pillarInformation->controlPoints[pillarIndex * 3] + ratioFromFirstControlPoint * xDist;
						xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 1] = pillarInformation->controlPoints[pillarIndex * 3 + 1] + ratioFromFirstControlPoint * yDist;
						xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = pillarInformation->controlPoints[pillarIndex * 3 + 2] + ratioFromFirstControlPoint * zDist;
					}
				}
				else { // piecewise linear

						//unsigned int previousControlPoint = 0;
						//if (pillarInformation->controlPointParameters != nullptr) {
						//	while ((parameters[paramIndex] < pillarInformation->controlPointParameters[coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint] && parameters[paramIndex] < pillarInformation->controlPointParameters[coordLineIndex + pillarInformation->parametricLineCount*(previousControlPoint + 1)]) ||
						//		(parameters[paramIndex] > pillarInformation->controlPointParameters[coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint] && parameters[paramIndex] > pillarInformation->controlPointParameters[coordLineIndex + pillarInformation->parametricLineCount*(previousControlPoint + 1)]) &&
						//		previousControlPoint < controlPointCount - 1) {
						//		++previousControlPoint;
						//	}
						//}
						//else { // Should never occur by business rule. Assume the parameters are Z values for now (workaround for some softwares)....
						//	while ((parameters[paramIndex] < pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3 + 2] && parameters[paramIndex] < pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*(previousControlPoint + 1)) * 3 + 2]) ||
						//		(parameters[paramIndex] > pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3 + 2] && parameters[paramIndex] > pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*(previousControlPoint + 1)) * 3 + 2]) &&
						//		previousControlPoint < controlPointCount - 1) {
						//		++previousControlPoint;
						//	}
						//}

						//if (previousControlPoint == controlPointCount - 1) {
						//	throw invalid_argument("Cannot extrapolate piecewiselinear pillar for now to explicit a grid node.");
						//}

						//double ratioFromPreviousControlPoint = .0;
						//double parameterDistance = .0;
						//if (pillarInformation->controlPointParameters != nullptr) {
						//	parameterDistance = pillarInformation->controlPointParameters[coordLineIndex + pillarInformation->parametricLineCount*(previousControlPoint + 1)] - pillarInformation->controlPointParameters[coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint]; // Parameter distance from top to bottom.
						//	if (parameterDistance != .0)
						//		ratioFromPreviousControlPoint = (parameters[paramIndex] - pillarInformation->controlPointParameters[coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint]) / parameterDistance;
						//}
						//else { // Should never occur by business rule. Assume the parameters are Z values for now (workaround for some softwares)....
						//	parameterDistance = pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*(previousControlPoint + 1)) * 3 + 2] - pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3 + 2]; // Parameter distance from top to bottom.
						//	if (parameterDistance != .0) {
						//		ratioFromPreviousControlPoint = (parameters[paramIndex] - pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3 + 2]) / parameterDistance;
						//	}
						//}
						//xyzPoints[paramIndex * 3] = pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3] + ratioFromPreviousControlPoint * (pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount) * 3] - pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3]);
						//xyzPoints[paramIndex * 3 + 1] = pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3 + 1] + ratioFromPreviousControlPoint * (pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*(previousControlPoint + 1)) * 3 + 1] - pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3 + 1]);
						//xyzPoints[paramIndex * 3 + 2] = pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3 + 2] + ratioFromPreviousControlPoint * (pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*(previousControlPoint + 1)) * 3 + 2] - pillarInformation->controlPoints[(coordLineIndex + pillarInformation->parametricLineCount*previousControlPoint) * 3 + 2]);

						//// TODO AND TO VERIFY ABOVE (MERGE PIECEWISE AND LINEAR (only 2 control points) IF POSSIBLE)

						//delete[] parameters;
					throw logic_error("Piecewise linear pillars are not implemented yet");
				}
			}
			else if (pillarInformation->pillarKind[pillarIndex] == 2 || pillarInformation->pillarKind[pillarIndex] == 4) { // XY Natural cubic spline
				for (unsigned int k = 0; k <= blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart; ++k) {
					xyzPoints[(k * xyzPointCount + paramIndex) * 3] = pillarInformation->splines[pillarIndex][0].getValueFromParameter(parameters[k * xyzPointCount + paramIndex]);
					xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 1] = pillarInformation->splines[pillarIndex][1].getValueFromParameter(parameters[k * xyzPointCount + paramIndex]);
					if (pillarInformation->pillarKind[pillarIndex] == 2) { //  Z natural cubic spline
						xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = pillarInformation->splines[pillarIndex][2].getValueFromParameter(parameters[k * xyzPointCount + paramIndex]);
					}
					else { // Z linear cubic spline
						xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = parameters[k * xyzPointCount + paramIndex];
					}
				}
			}
			else {
				throw logic_error("Computing XYZ from parameters on a non natural cubic spline or on a minimum curvature spline is not implemented yet.");
			}
			++paramIndex;
		}
	}

	for (unsigned int splitLineIndex = 0; splitLineIndex < pillarInformation->splitLineCount; ++splitLineIndex)
	{
		if (blockInformation->globalToLocalSplitCoordinateLinesIndex.find(splitLineIndex) != blockInformation->globalToLocalSplitCoordinateLinesIndex.end())
		{
			paramIndex = blockInformation->globalToLocalSplitCoordinateLinesIndex[splitLineIndex];
			unsigned int pillarIndex = pillarInformation->pillarOfSplitCoordLines[splitLineIndex];
			if (pillarInformation->pillarKind[pillarIndex] == -1 || parameters[paramIndex] != parameters[paramIndex]) { // not defined line
				for (unsigned int k = 0; k <= blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart; ++k) {
					xyzPoints[(k * xyzPointCount + paramIndex) * 3] = std::numeric_limits<double>::quiet_NaN();
					xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 1] = std::numeric_limits<double>::quiet_NaN();
					xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = std::numeric_limits<double>::quiet_NaN();
				}
			}
			else if (pillarInformation->pillarKind[pillarIndex] == 0) { // vertical (parameter must be the Z value)
				for (unsigned int k = 0; k <= blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart; ++k) {
					xyzPoints[(k * xyzPointCount + paramIndex) * 3] = pillarInformation->controlPoints[pillarIndex * 3];
					xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 1] = pillarInformation->controlPoints[pillarIndex * 3 + 1];
					xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = parameters[k * xyzPointCount + paramIndex];
				}
			}
			else if (pillarInformation->pillarKind[pillarIndex] == 1) { // Linear interpolation
				unsigned int controlPointCount = 0;
				while (controlPointCount < pillarInformation->maxControlPointCount &&
					pillarInformation->controlPoints[(pillarIndex + controlPointCount*pillarInformation->parametricLineCount) * 3] == pillarInformation->controlPoints[(pillarIndex + controlPointCount*pillarInformation->parametricLineCount) * 3]) {
					controlPointCount++;
				}

				// Control point count on this line
				if (controlPointCount == 2) { // straight
					double parameterDistance = .0;
					if (pillarInformation->controlPointParameters != nullptr)
						parameterDistance = pillarInformation->controlPointParameters[pillarIndex + pillarInformation->parametricLineCount] - pillarInformation->controlPointParameters[pillarIndex]; // Parameter distance from top to bottom.
					else // Should never occur by business rule. Assume the parameters are Z values for now (workaround for some softwares)....
						parameterDistance = pillarInformation->controlPoints[(pillarIndex + pillarInformation->parametricLineCount) * 3 + 2] - pillarInformation->controlPoints[pillarIndex * 3 + 2]; // Parameter distance from top to bottom.

					double xDist = pillarInformation->controlPoints[(pillarIndex + pillarInformation->parametricLineCount) * 3] - pillarInformation->controlPoints[pillarIndex * 3];
					double yDist = pillarInformation->controlPoints[(pillarIndex + pillarInformation->parametricLineCount) * 3 + 1] - pillarInformation->controlPoints[pillarIndex * 3 + 1];
					double zDist = pillarInformation->controlPoints[(pillarIndex + pillarInformation->parametricLineCount) * 3 + 2] - pillarInformation->controlPoints[pillarIndex * 3 + 2];

					double ratioFromFirstControlPoint = .0;
					for (unsigned int k = 0; k <= blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart; ++k) {
						if (parameterDistance != .0) {
							if (pillarInformation->controlPointParameters != nullptr)
								ratioFromFirstControlPoint = (parameters[k * xyzPointCount + paramIndex] - pillarInformation->controlPointParameters[pillarIndex]) / parameterDistance;
							else { // Should never occur by business rule. Assume the parameters are Z values for now (workaround for some softwares)....
								ratioFromFirstControlPoint = (parameters[k * xyzPointCount + paramIndex] - pillarInformation->controlPoints[pillarIndex * 3 + 2]) / parameterDistance;
							}
						}
						else
							ratioFromFirstControlPoint = .0;

						xyzPoints[(k * xyzPointCount + paramIndex) * 3] = pillarInformation->controlPoints[pillarIndex * 3] + ratioFromFirstControlPoint * xDist;
						xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 1] = pillarInformation->controlPoints[pillarIndex * 3 + 1] + ratioFromFirstControlPoint * yDist;
						xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = pillarInformation->controlPoints[pillarIndex * 3 + 2] + ratioFromFirstControlPoint * zDist;
					}
				}
				else { // piecewise linear
					throw logic_error("Piecewise linear pillars are not implemented yet");
				}
			}
			else if (pillarInformation->pillarKind[pillarIndex] == 2 || pillarInformation->pillarKind[pillarIndex] == 4) { // XY Natural cubic spline
				for (unsigned int k = 0; k <= blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart; ++k) {
					xyzPoints[(k * xyzPointCount + paramIndex) * 3] = pillarInformation->splines[pillarIndex][0].getValueFromParameter(parameters[k * xyzPointCount + paramIndex]);
					xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 1] = pillarInformation->splines[pillarIndex][1].getValueFromParameter(parameters[k * xyzPointCount + paramIndex]);
					if (pillarInformation->pillarKind[pillarIndex] == 2) { //  Z natural cubic spline
						xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = pillarInformation->splines[pillarIndex][2].getValueFromParameter(parameters[k * xyzPointCount + paramIndex]);
					}
					else { // Z linear cubic spline
						xyzPoints[(k * xyzPointCount + paramIndex) * 3 + 2] = parameters[k * xyzPointCount + paramIndex];
					}
				}
			}
			else {
				throw logic_error("Computing XYZ from parameters on a non natural cubic spline or on a minimum curvature spline is not implemented yet.");
			}
		}
	}
}

void IjkGridParametricRepresentation::setGeometryAsParametricNonSplittedPillarNodes(
	gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, bool isRightHanded,
	double * parameters, double * controlPoints, double * controlPointParameters, unsigned int controlPointMaxCountPerPillar, short * pillarKind, EML2_NS::AbstractHdfProxy* proxy, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	setGeometryAsParametricSplittedPillarNodes(mostComplexPillarGeometry, isRightHanded, parameters, controlPoints, controlPointParameters, controlPointMaxCountPerPillar, pillarKind, proxy,
		0, nullptr, nullptr, nullptr, localCrs);
}

void IjkGridParametricRepresentation::setGeometryAsParametricNonSplittedPillarNodesUsingExistingDatasets(
	gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
	const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars, EML2_NS::AbstractHdfProxy* proxy, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(mostComplexPillarGeometry, kDirectionKind, isRightHanded, parameters, controlPoints, controlPointParameters, controlPointMaxCountPerPillar, pillarKind, definedPillars, proxy,
		0, "", "", "", localCrs);
}

void IjkGridParametricRepresentation::writeGeometryOnHdf(double const * parameters,
	double const * controlPoints, double const * controlPointParameters, unsigned int controlPointCountPerPillar,
	unsigned long splitCoordinateLineCount, unsigned int const * pillarOfCoordinateLine,
	unsigned int const * splitCoordinateLineColumnCumulativeCount, unsigned int const * splitCoordinateLineColumns, EML2_NS::AbstractHdfProxy * proxy)
{
	if (splitCoordinateLineCount == 0) {
		hsize_t numValues[3] = { getKCellCount() + 1, getJCellCount() + 1, getICellCount() + 1 };
		proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "PointParameters", parameters, numValues, 3);
	}
	else {
		// PointParameters
		hsize_t numValues[2] = { getKCellCount() + 1, (getJCellCount() + 1) * (getICellCount() + 1) + splitCoordinateLineCount };
		proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "PointParameters", parameters, numValues, 2);

		// split coordinate lines
		hsize_t hdfSplitCoordinateLineCount = splitCoordinateLineCount;
		proxy->writeArrayNd(getHdfGroup(), "PillarIndices", H5T_NATIVE_UINT, pillarOfCoordinateLine, &hdfSplitCoordinateLineCount, 1);

		proxy->writeItemizedListOfList(getHdfGroup(), "ColumnsPerSplitCoordinateLine", H5T_NATIVE_UINT, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineCount, H5T_NATIVE_UINT, splitCoordinateLineColumns, splitCoordinateLineColumnCumulativeCount[splitCoordinateLineCount - 1]);
	}

	// *********************************
	// Parametric coordinate lines
	// *********************************
	// HDF control points
	hsize_t controlPointCount[4] = { controlPointCountPerPillar, getJCellCount() + 1, getICellCount() + 1, 3 };
	proxy->writeArrayNd(getHdfGroup(), "ControlPoints", H5T_NATIVE_DOUBLE, controlPoints, controlPointCount, 4);

	// *********************************
	// Control point parameters are defined
	// *********************************
	if (controlPointParameters != nullptr) {
		// HDF control points parameters
		hsize_t controlPointParamCount[3] = { controlPointCountPerPillar, getJCellCount() + 1, getICellCount() + 1 };
		proxy->writeArrayNd(getHdfGroup(), "controlPointParameters", H5T_NATIVE_DOUBLE, controlPointParameters, controlPointParamCount, 3);
	}
}

void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodes(bool isRightHanded,
	double const * parameters, double const * controlPoints, double const * controlPointParameters, unsigned int controlPointCountPerPillar, short pillarKind, EML2_NS::AbstractHdfProxy * proxy,
	unsigned long splitCoordinateLineCount, unsigned int const * pillarOfCoordinateLine,
	unsigned int const * splitCoordinateLineColumnCumulativeCount, unsigned int const * splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (parameters == nullptr) {
		throw invalid_argument("The parameters of the nodes of the ijk grid cannot be null.");
	}
	if (controlPoints == nullptr) {
		throw invalid_argument("The control points of the coordinate lines of the ijk grid cannot be null.");
	}
	if (splitCoordinateLineCount != 0 && (pillarOfCoordinateLine == nullptr || splitCoordinateLineColumnCumulativeCount == nullptr || splitCoordinateLineColumns == nullptr)) {
		throw invalid_argument("The definition of the split coordinate lines is incomplete.");
	}
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind = pillarKind == -1
		? gsoap_resqml2_0_1::resqml20__KDirection__down
		: computeKDirection(controlPoints, controlPointCountPerPillar, nullptr, localCrs);

	const std::string hdfDatasetPrefix = getHdfGroup();
	setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(kDirectionKind, isRightHanded,
		hdfDatasetPrefix + "/PointParameters", hdfDatasetPrefix + "/ControlPoints", controlPointParameters != nullptr ? hdfDatasetPrefix + "/controlPointParameters" : "", controlPointCountPerPillar, pillarKind, proxy,
		splitCoordinateLineCount, hdfDatasetPrefix + "/PillarIndices",
		hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + CUMULATIVE_LENGTH_DS_NAME, hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + ELEMENTS_DS_NAME, localCrs);

	writeGeometryOnHdf(parameters,
		controlPoints, controlPointParameters, controlPointCountPerPillar,
		splitCoordinateLineCount, pillarOfCoordinateLine,
		splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns, proxy);
}

void IjkGridParametricRepresentation::loadPillarInformation(IjkGridParametricRepresentation::PillarInformation & pillarInfo) const
{
	pillarInfo.cleanMemory();

	pillarInfo.maxControlPointCount = getControlPointMaxCountPerPillar();
	pillarInfo.parametricLineCount = getPillarCount();
	pillarInfo.splitLineCount = getSplitCoordinateLineCount();

	// Control points
	pillarInfo.controlPoints = new double[pillarInfo.parametricLineCount*pillarInfo.maxControlPointCount * 3];
	getControlPoints(pillarInfo.controlPoints);

	// Control points parameters
	if (hasControlPointParameters()) {
		pillarInfo.controlPointParameters = new double[pillarInfo.parametricLineCount*pillarInfo.maxControlPointCount];
		getControlPointParameters(pillarInfo.controlPointParameters);
	}

	// Line kind indices
	pillarInfo.pillarKind = new short[pillarInfo.parametricLineCount];
	getParametricLineKind(pillarInfo.pillarKind);
	// Pillar geometry definition overrides the kind information : https://discourse.f2i-consulting.com/t/ijkparametricgrid-xyz-points/148
	std::unique_ptr<bool[]> pillarGeomIsDefined(new bool[pillarInfo.parametricLineCount]);
	getPillarGeometryIsDefined(pillarGeomIsDefined.get());
	for (unsigned int parametricLineIndex = 0; parametricLineIndex < pillarInfo.parametricLineCount; ++parametricLineIndex) {
		if (!pillarGeomIsDefined[parametricLineIndex]) {
			pillarInfo.pillarKind[parametricLineIndex] = -1;
		}
	}

	// Pillars of split line
	if (pillarInfo.splitLineCount > 0) {
		pillarInfo.pillarOfSplitCoordLines = new unsigned int[pillarInfo.splitLineCount];
		getPillarsOfSplitCoordinateLines(pillarInfo.pillarOfSplitCoordLines);
	}

	// Spline creation
	BSpline spline;
	for (unsigned int parametricLineIndex = 0; parametricLineIndex < pillarInfo.parametricLineCount; ++parametricLineIndex) {
		vector<BSpline> xyzSplines;
		if (pillarInfo.pillarKind[parametricLineIndex] == 2 || pillarInfo.pillarKind[parametricLineIndex] == 4) { // X and Y natural cubic spline
			vector<double> parameters;
			vector<double> xValues;
			vector<double> yValues;
			for (unsigned int cpIndex = 0; cpIndex < pillarInfo.maxControlPointCount; ++cpIndex) {
				unsigned int globalCpIndex = parametricLineIndex + cpIndex * pillarInfo.parametricLineCount;
				if (pillarInfo.controlPointParameters != nullptr && pillarInfo.controlPointParameters[globalCpIndex] == pillarInfo.controlPointParameters[globalCpIndex]) {
					parameters.push_back(pillarInfo.controlPointParameters[globalCpIndex]);
					xValues.push_back(pillarInfo.controlPoints[globalCpIndex * 3]);
					yValues.push_back(pillarInfo.controlPoints[globalCpIndex * 3 + 1]);
				}
				// A variant in v2.0.1 when the KIL about presency of control point parameters was not existing yet.
				else if (pillarInfo.pillarKind[parametricLineIndex] == 4 && pillarInfo.controlPoints[globalCpIndex * 3] == pillarInfo.controlPoints[globalCpIndex * 3]) {
					parameters.push_back(pillarInfo.controlPoints[globalCpIndex * 3 + 2]);
					xValues.push_back(pillarInfo.controlPoints[globalCpIndex * 3]);
					yValues.push_back(pillarInfo.controlPoints[globalCpIndex * 3 + 1]);
				}
			}
			// X
			spline.setParameterAndValueAtControlPoint(parameters, xValues);
			xyzSplines.push_back(spline);
			// Y
			spline.setParameterAndValueAtControlPoint(parameters, yValues);
			xyzSplines.push_back(spline);
			// Z
			if (pillarInfo.pillarKind[parametricLineIndex] == 2) { // Z Natural cubic spline
				vector<double> zValues;
				for (unsigned int cpIndex = 0; cpIndex < pillarInfo.maxControlPointCount; ++cpIndex) {
					double zvalue = pillarInfo.controlPoints[parametricLineIndex + cpIndex * pillarInfo.parametricLineCount * 3 + 2];
					if (zvalue == zvalue) {
						zValues.push_back(zvalue);
					}
				}
				spline.setParameterAndValueAtControlPoint(parameters, zValues);
				xyzSplines.push_back(spline);
			}
		}
		pillarInfo.splines.push_back(xyzSplines);
	}
}

void IjkGridParametricRepresentation::getXyzPointsFromParametricPoints(double * xyzPoints) const
{
	std::string datasetPathInExternalFile;
	EML2_NS::AbstractHdfProxy* hdfProxy = getParameterDatasetPath(datasetPathInExternalFile);
	std::unique_ptr<double[]> parameters(new double[getXyzPointCountOfPatch(0)]);
	hdfProxy->readArrayNdOfDoubleValues(datasetPathInExternalFile, parameters.get());

	IjkGridParametricRepresentation::PillarInformation pillarInfo;
	loadPillarInformation(pillarInfo);

	//Mapping
	size_t paramIndex = 0;
	for (unsigned int kInterface = 0; kInterface < getKCellCount() + 1; ++kInterface) {
		for (unsigned int coordLineIndex = 0; coordLineIndex < pillarInfo.parametricLineCount; ++coordLineIndex) {
			if (pillarInfo.pillarKind[coordLineIndex] == -1 || parameters[paramIndex] != parameters[paramIndex]) { // not defined line
				xyzPoints[paramIndex*3] = std::numeric_limits<double>::quiet_NaN();
				xyzPoints[paramIndex*3+1] = std::numeric_limits<double>::quiet_NaN();
				xyzPoints[paramIndex*3+2] = std::numeric_limits<double>::quiet_NaN();
			}
			else if (pillarInfo.pillarKind[coordLineIndex] == 0) { // vertical (parameter must be the Z value)
				xyzPoints[paramIndex*3] = pillarInfo.controlPoints[coordLineIndex*3];
				xyzPoints[paramIndex*3+1] = pillarInfo.controlPoints[coordLineIndex*3+1];
				xyzPoints[paramIndex*3+2] = parameters[paramIndex];
			}
			else if (pillarInfo.pillarKind[coordLineIndex] == 1) { // linear interpolation
				unsigned int controlPointCount = 0;
				while (controlPointCount < pillarInfo.maxControlPointCount &&
						pillarInfo.controlPoints[(coordLineIndex + controlPointCount*pillarInfo.parametricLineCount)*3] == 
						pillarInfo.controlPoints[(coordLineIndex + controlPointCount*pillarInfo.parametricLineCount)*3]) {
					controlPointCount++;
				}

				// Control point count on this line
				if (controlPointCount == 2) { // straight
					double ratioFromFirstControlPoint = .0;
					double parameterDistance = .0;
					if (pillarInfo.controlPointParameters != nullptr) {
						parameterDistance = pillarInfo.controlPointParameters[coordLineIndex + pillarInfo.parametricLineCount] - pillarInfo.controlPointParameters[coordLineIndex]; // Parameter distance from top to bottom.
						if (parameterDistance != .0)
							ratioFromFirstControlPoint = (parameters[paramIndex] - pillarInfo.controlPointParameters[coordLineIndex]) / parameterDistance;
					}
					else { // Should never occur by business rule. Assume the parameters are Z values for now (workaround for some softwares)....
						parameterDistance = pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount)*3+2] - pillarInfo.controlPoints[coordLineIndex*3+2]; // Parameter distance from top to bottom.
						if (parameterDistance != .0) {
							ratioFromFirstControlPoint = (parameters[paramIndex] - pillarInfo.controlPoints[coordLineIndex * 3 + 2]) / parameterDistance;
						}
					}
					xyzPoints[paramIndex*3] = pillarInfo.controlPoints[coordLineIndex*3] + ratioFromFirstControlPoint * (pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount)*3] - pillarInfo.controlPoints[coordLineIndex*3]);
					xyzPoints[paramIndex*3 + 1] = pillarInfo.controlPoints[coordLineIndex*3 + 1] + ratioFromFirstControlPoint * (pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount)*3 + 1] - pillarInfo.controlPoints[coordLineIndex*3 + 1]);
					xyzPoints[paramIndex*3 + 2] = pillarInfo.controlPoints[coordLineIndex*3 + 2] + ratioFromFirstControlPoint * (pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount)*3 + 2] - pillarInfo.controlPoints[coordLineIndex*3 + 2]);
				}
				else { // piecewise linear

					unsigned int previousControlPoint = 0;
					if (pillarInfo.controlPointParameters != nullptr) {
						while (((parameters[paramIndex] < pillarInfo.controlPointParameters[coordLineIndex + pillarInfo.parametricLineCount*previousControlPoint] && parameters[paramIndex] < pillarInfo.controlPointParameters[coordLineIndex + pillarInfo.parametricLineCount*(previousControlPoint + 1)]) ||
							(parameters[paramIndex] > pillarInfo.controlPointParameters[coordLineIndex + pillarInfo.parametricLineCount*previousControlPoint] && parameters[paramIndex] > pillarInfo.controlPointParameters[coordLineIndex + pillarInfo.parametricLineCount*(previousControlPoint + 1)])) &&
							previousControlPoint < controlPointCount - 1) {
							++previousControlPoint;
						}
					}
					else { // Should never occur by business rule. Assume the parameters are Z values for now (workaround for some softwares)....
						while (((parameters[paramIndex] < pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount*previousControlPoint) * 3 + 2] && parameters[paramIndex] < pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount*(previousControlPoint + 1)) * 3 + 2]) ||
							(parameters[paramIndex] > pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount*previousControlPoint) * 3 + 2] && parameters[paramIndex] > pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount*(previousControlPoint + 1)) * 3 + 2])) &&
							previousControlPoint < controlPointCount - 1) {
							++previousControlPoint;
						}
					}

					if (previousControlPoint == controlPointCount - 1) {
						throw invalid_argument("Cannot extrapolate piecewiselinear pillar for now to explicit a grid node.");
					}

					double ratioFromPreviousControlPoint = .0;
					double parameterDistance = .0;
					if (pillarInfo.controlPointParameters != nullptr) {
						parameterDistance = pillarInfo.controlPointParameters[coordLineIndex + pillarInfo.parametricLineCount*(previousControlPoint + 1)] - pillarInfo.controlPointParameters[coordLineIndex + pillarInfo.parametricLineCount*previousControlPoint]; // Parameter distance from top to bottom.
						if (parameterDistance != .0)
							ratioFromPreviousControlPoint = (parameters[paramIndex] - pillarInfo.controlPointParameters[coordLineIndex + pillarInfo.parametricLineCount*previousControlPoint]) / parameterDistance;
					}
					else { // Should never occur by business rule. Assume the parameters are Z values for now (workaround for some softwares)....
						parameterDistance = pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount*(previousControlPoint + 1)) * 3 + 2] - pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount*previousControlPoint) * 3 + 2]; // Parameter distance from top to bottom.
						if (parameterDistance != .0) {
							ratioFromPreviousControlPoint = (parameters[paramIndex] - pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount*previousControlPoint) * 3 + 2]) / parameterDistance;
						}
					}
					xyzPoints[paramIndex * 3] = pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount*previousControlPoint) * 3] + ratioFromPreviousControlPoint * (pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount) * 3] - pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount*previousControlPoint) * 3]);
					xyzPoints[paramIndex * 3 + 1] = pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount*previousControlPoint) * 3 + 1] + ratioFromPreviousControlPoint * (pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount*(previousControlPoint + 1)) * 3 + 1] - pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount*previousControlPoint) * 3 + 1]);
					xyzPoints[paramIndex * 3 + 2] = pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount*previousControlPoint) * 3 + 2] + ratioFromPreviousControlPoint * (pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount*(previousControlPoint + 1)) * 3 + 2] - pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount*previousControlPoint) * 3 + 2]);

					// TODO AND TO VERIFY ABOVE (MERGE PIECEWISE AND LINEAR (only 2 control points) IF POSSIBLE)

					throw logic_error("Piecewise linear pillars are not implemented yet");
				}
			}
			else if (pillarInfo.pillarKind[coordLineIndex] == 2 || pillarInfo.pillarKind[coordLineIndex] == 4) { // XY Natural cubic spline
				xyzPoints[paramIndex * 3] = pillarInfo.splines[coordLineIndex][0].getValueFromParameter(parameters[paramIndex]);
				xyzPoints[paramIndex * 3 + 1] = pillarInfo.splines[coordLineIndex][1].getValueFromParameter(parameters[paramIndex]);
				if (pillarInfo.pillarKind[coordLineIndex] == 2) { //  Z natural cubic spline
					xyzPoints[paramIndex * 3 + 2] = pillarInfo.splines[coordLineIndex][2].getValueFromParameter(parameters[paramIndex]);
				}
				else { // Z linear cubic spline
					xyzPoints[paramIndex * 3 + 2] = parameters[paramIndex];
				}
			}
			else {
				throw logic_error("Computing XYZ from parameters on a non natural cubic spline or on a minimum curvature spline is not implemented yet.");
			}
			++paramIndex;
		}
		for (unsigned int splitLineIndex = 0; splitLineIndex < pillarInfo.splitLineCount; ++splitLineIndex)
		{
			unsigned int coordLineIndex = pillarInfo.pillarOfSplitCoordLines[splitLineIndex];
			if (pillarInfo.pillarKind[coordLineIndex] == -1 || parameters[paramIndex] != parameters[paramIndex]) { // not defined line
				xyzPoints[paramIndex*3] = std::numeric_limits<double>::quiet_NaN();
				xyzPoints[paramIndex*3+1] = std::numeric_limits<double>::quiet_NaN();
				xyzPoints[paramIndex*3+2] = std::numeric_limits<double>::quiet_NaN();
			}
			else if (pillarInfo.pillarKind[coordLineIndex] == 0) { // vertical (parameter must be the Z value)
				xyzPoints[paramIndex*3] = pillarInfo.controlPoints[coordLineIndex*3];
				xyzPoints[paramIndex*3+1] = pillarInfo.controlPoints[coordLineIndex*3+1];
				xyzPoints[paramIndex*3+2] = parameters[paramIndex];
			}
			else if (pillarInfo.pillarKind[coordLineIndex] == 1) { // Linear interpolation
				unsigned int controlPointCount = 0;
				while (controlPointCount < pillarInfo.maxControlPointCount &&
						pillarInfo.controlPoints[(coordLineIndex + controlPointCount*pillarInfo.parametricLineCount)*3] == pillarInfo.controlPoints[(coordLineIndex + controlPointCount*pillarInfo.parametricLineCount)*3]) {
					controlPointCount++;
				}

				// Control point count on this line
				if (controlPointCount == 2) { // straight
					double ratioFromFirstControlPoint = .0;
					double parameterDistance = .0;
					if (pillarInfo.controlPointParameters != nullptr) {
						parameterDistance = pillarInfo.controlPointParameters[coordLineIndex + pillarInfo.parametricLineCount] - pillarInfo.controlPointParameters[coordLineIndex]; // Parameter distance from top to bottom.
						if (parameterDistance != .0) {
							ratioFromFirstControlPoint = (parameters[paramIndex] - pillarInfo.controlPointParameters[coordLineIndex]) / parameterDistance;
						}
					}
					else { // Should never occur by business rule. Assume the parameters are Z values for now (workaround for some softwares)....
						parameterDistance = pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount)*3+2] - pillarInfo.controlPoints[coordLineIndex*3+2]; // Parameter distance from top to bottom.
						if (parameterDistance != .0)
							ratioFromFirstControlPoint = (parameters[paramIndex] - pillarInfo.controlPoints[coordLineIndex*3+2]) / parameterDistance;
					}

					xyzPoints[paramIndex*3] = pillarInfo.controlPoints[coordLineIndex*3] + ratioFromFirstControlPoint * (pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount)*3] - pillarInfo.controlPoints[coordLineIndex*3]);
					xyzPoints[paramIndex*3 + 1] = pillarInfo.controlPoints[coordLineIndex*3 + 1] + ratioFromFirstControlPoint * (pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount)*3 + 1] - pillarInfo.controlPoints[coordLineIndex*3 + 1]);
					xyzPoints[paramIndex*3 + 2] = pillarInfo.controlPoints[coordLineIndex*3 + 2] + ratioFromFirstControlPoint * (pillarInfo.controlPoints[(coordLineIndex + pillarInfo.parametricLineCount)*3 + 2] - pillarInfo.controlPoints[coordLineIndex*3 + 2]);
				}
				else { // piecewise linear
					throw logic_error("Piecewise linear pillars are not implemented yet");
				}
			}
			else if (pillarInfo.pillarKind[coordLineIndex] == 2 || pillarInfo.pillarKind[coordLineIndex] == 4) { // XY Natural cubic spline
				xyzPoints[paramIndex * 3] = pillarInfo.splines[coordLineIndex][0].getValueFromParameter(parameters[paramIndex]);
				xyzPoints[paramIndex * 3 + 1] = pillarInfo.splines[coordLineIndex][1].getValueFromParameter(parameters[paramIndex]);
				if (pillarInfo.pillarKind[coordLineIndex] == 2) { // Z natural cubic spline
					xyzPoints[paramIndex * 3 + 2] = pillarInfo.splines[coordLineIndex][2].getValueFromParameter(parameters[paramIndex]);
				}
				else { // Z linear cubic spline
					xyzPoints[paramIndex * 3 + 2] = parameters[paramIndex];
				}
			}
			else {
				throw logic_error("Computing XYZ from parameters on a non natural cubic spline or on a minimum curvature spline is not implemented yet.");
			}
			++paramIndex;
		}
	}
}

AbstractIjkGridRepresentation::geometryKind IjkGridParametricRepresentation::getGeometryKind() const
{
	return PARAMETRIC;
}

namespace {
	/**
	* @param controlPointIndex The index of the first control point of the studied pillar in the controlPoints array
	*/
	short computeKDirectionOnASinglePillar(unsigned int pillarIndex, unsigned int pillarCount, double const * controlPoints, unsigned int controlPointCountOnPillar, bool isCrsDepthOriented) {
		short result = -1;

		size_t controlPointIndex = pillarIndex * 3 + 2;
		double firstZ = controlPoints[controlPointIndex];
		if (firstZ != firstZ) { // The pillar is undefined
			return -1;
		}
		unsigned int pillarCountTimes3 = pillarCount * 3; // optim
		controlPointIndex += pillarCountTimes3;

		for (; controlPointIndex < controlPointCountOnPillar * pillarCountTimes3; controlPointIndex += pillarCountTimes3) {
			if (controlPoints[controlPointIndex] != controlPoints[controlPointIndex]) { // The pillar definition is already complete
				break;
			}
			if (controlPoints[controlPointIndex] == firstZ) { // The K Direction cannot be deduced
				continue;
			}

			gsoap_resqml2_0_1::resqml20__KDirection tmp = gsoap_resqml2_0_1::resqml20__KDirection::resqml20__KDirection__not_x0020monotonic;
			if (isCrsDepthOriented) {
				tmp = controlPoints[controlPointIndex] > firstZ
					? gsoap_resqml2_0_1::resqml20__KDirection::resqml20__KDirection__down
					: gsoap_resqml2_0_1::resqml20__KDirection::resqml20__KDirection__up;
			}
			else {
				tmp = controlPoints[controlPointIndex] > firstZ
					? gsoap_resqml2_0_1::resqml20__KDirection::resqml20__KDirection__up
					: gsoap_resqml2_0_1::resqml20__KDirection::resqml20__KDirection__down;
			}

			if (result == -1) {
				result = tmp;
			}
			else if (result != tmp) {
				return gsoap_resqml2_0_1::resqml20__KDirection::resqml20__KDirection__not_x0020monotonic;
			}
		}

		return result;
	}
}

gsoap_resqml2_0_1::resqml20__KDirection IjkGridParametricRepresentation::computeKDirection(double const * controlPoints, unsigned int controlPointCountPerPillar, short * pillarKind, RESQML2_NS::AbstractLocal3dCrs const * localCrs) {
	if (controlPoints == nullptr) {
		throw invalid_argument("The control points cannot be null.");
	}
	if (controlPointCountPerPillar < 1) {
		throw invalid_argument("The max count of control points per coordinate line of the ijk grid cannot be less than one.");
	}
	if (controlPointCountPerPillar == 1) {
		return gsoap_resqml2_0_1::resqml20__KDirection::resqml20__KDirection__down; // arbitrary default
	}
	
	// CRS
	const bool isCrsDepthOriented = localCrs->isDepthOriented();

	// Initialization
	short result = -1;
	unsigned int pillarIndex = 0;
	for (; pillarIndex < getPillarCount() && result == -1; ++pillarIndex) {
		if (pillarKind == nullptr || pillarKind[pillarIndex] > -1) {
			result = computeKDirectionOnASinglePillar(pillarIndex, getPillarCount(), controlPoints, controlPointCountPerPillar, isCrsDepthOriented);
		}
	}
	if (result == gsoap_resqml2_0_1::resqml20__KDirection::resqml20__KDirection__not_x0020monotonic)
		return gsoap_resqml2_0_1::resqml20__KDirection::resqml20__KDirection__not_x0020monotonic;

	// Loop
	for (; pillarIndex < getPillarCount(); ++pillarIndex) {
		if (pillarKind == nullptr || pillarKind[pillarIndex] > -1) {
			const short tmp = computeKDirectionOnASinglePillar(pillarIndex, getPillarCount(), controlPoints, controlPointCountPerPillar, isCrsDepthOriented);

			if (tmp != -1 && tmp != result) {
				return gsoap_resqml2_0_1::resqml20__KDirection::resqml20__KDirection__not_x0020monotonic;
			}
		}
	}

	return result < 0
		? gsoap_resqml2_0_1::resqml20__KDirection::resqml20__KDirection__down  // arbitrary default
		: static_cast<gsoap_resqml2_0_1::resqml20__KDirection>(result);
}

bool IjkGridParametricRepresentation::isNodeGeometryCompressed() const
{
	std::string datasetPathInExternalFile;
	EML2_NS::AbstractHdfProxy* hdfProxy = getParameterDatasetPath(datasetPathInExternalFile);
	return hdfProxy->isCompressed(datasetPathInExternalFile);
}
