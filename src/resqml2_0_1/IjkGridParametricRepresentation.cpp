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

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../resqml2/AbstractLocal3dCrs.h"
#include "../resqml2/AbstractValuesProperty.h"
#include "../common/AbstractHdfProxy.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace RESQML2_0_1_NS;

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

IjkGridParametricRepresentation::IjkGridParametricRepresentation(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount,
	bool withTruncatedPillars) :
	AbstractIjkGridRepresentation(repo, guid, title, iCount, jCount, kCount, withTruncatedPillars), pillarInformation(nullptr)
{
}

IjkGridParametricRepresentation::IjkGridParametricRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount,
	bool withTruncatedPillars) :
	AbstractIjkGridRepresentation(interp, guid, title, iCount, jCount, kCount, withTruncatedPillars), pillarInformation(nullptr)
{
}

unsigned int IjkGridParametricRepresentation::getControlPointMaxCountPerPillar() const
{
	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineArray) {
		const ULONG64 result = static_cast<resqml20__ParametricLineArray*>(points->ParametricLines)->KnotCount;
		if (result > (std::numeric_limits<unsigned int>::max)())
			throw std::out_of_range("There are too many knot counts");
		return static_cast<unsigned int>(result);
	}

	throw std::logic_error("Not yet implemented");
}

void IjkGridParametricRepresentation::getControlPoints(double * controlPoints, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) const
{
	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineArray) {
		resqml20__ParametricLineArray* paramLineArray = static_cast<resqml20__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->ControlPoints->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array) {
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__Point3dHdf5Array*>(paramLineArray->ControlPoints)->Coordinates;
			COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, controlPoints);
		}
		else
			throw std::logic_error("Not yet implemented");
	}
	else {
		throw std::logic_error("Not yet implemented");
	}

	if (reverseIAxis || reverseJAxis || reverseKAxis)
	{
		unsigned int iPillarCount = getICellCount()+1;
		unsigned int jPillarCount = getJCellCount()+1;
		unsigned int arrayCount = iPillarCount * jPillarCount * getControlPointMaxCountPerPillar() * 3;

		// Copy in order not to modify the controlPoints pointer
		double * reversedControlPoints = new double [arrayCount];
		for (unsigned int index = 0; index < arrayCount; ++index) {
			reversedControlPoints[index] = controlPoints[index];
		}

		if (reverseIAxis) {
			unsigned int controlPointIndex = 0;
			for (unsigned int k = 0; k < getControlPointMaxCountPerPillar(); ++k) {
				for (unsigned int j = 0; j < jPillarCount; ++j) {
					for (unsigned int i = 0; i < iPillarCount; ++i) {
						unsigned int reversedControlPointIndex = getICellCount() - i + j*iPillarCount + k*iPillarCount*jPillarCount;
						controlPoints[controlPointIndex*3] = reversedControlPoints[reversedControlPointIndex*3];
						controlPoints[controlPointIndex*3 + 1] = reversedControlPoints[reversedControlPointIndex*3 + 1];
						controlPoints[controlPointIndex*3 + 2] = reversedControlPoints[reversedControlPointIndex*3 + 2];
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
						controlPoints[controlPointIndex*3] = reversedControlPoints[reversedControlPointIndex*3];
						controlPoints[controlPointIndex*3 + 1] = reversedControlPoints[reversedControlPointIndex*3 + 1];
						controlPoints[controlPointIndex*3 + 2] = reversedControlPoints[reversedControlPointIndex*3 + 2];
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
						unsigned int reversedControlPointIndex = i + j*iPillarCount + (getControlPointMaxCountPerPillar()-1-k)*iPillarCount*jPillarCount;
						controlPoints[controlPointIndex*3] = reversedControlPoints[reversedControlPointIndex*3];
						controlPoints[controlPointIndex*3 + 1] = reversedControlPoints[reversedControlPointIndex*3 + 1];
						controlPoints[controlPointIndex*3 + 2] = reversedControlPoints[reversedControlPointIndex*3 + 2];
						++controlPointIndex;
					}
				}
			}
		}

		delete [] reversedControlPoints;
	}
}

bool IjkGridParametricRepresentation::hasControlPointParameters() const
{
	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineArray)
	{
		resqml20__ParametricLineArray* paramLineArray = static_cast<resqml20__ParametricLineArray*>(points->ParametricLines);
		return paramLineArray->ControlPointParameters != nullptr;
	}
	else
		throw std::logic_error("Not yet implemented");
}

void IjkGridParametricRepresentation::getControlPointParameters(double * controlPointParameters, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) const
{
	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineArray)
	{
		resqml20__ParametricLineArray* paramLineArray = static_cast<resqml20__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->ControlPointParameters == nullptr)
			throw invalid_argument("The grid does not contain any control point parameters.");
		if (paramLineArray->ControlPointParameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array)
		{
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__DoubleHdf5Array*>(paramLineArray->ControlPointParameters)->Values;
			COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, controlPointParameters);
		}
		else
			throw std::logic_error("Not yet implemented");
	}
	else
		throw std::logic_error("Not yet implemented");
	
	if (reverseIAxis || reverseJAxis || reverseKAxis)
	{
		unsigned int iPillarCount = getICellCount()+1;
		unsigned int jPillarCount = getJCellCount()+1;
		unsigned int arrayCount = iPillarCount * jPillarCount * getControlPointMaxCountPerPillar();

		// Copy in order not to modify the controlPoints pointer
		double * reversedControlPointParameters = new double [arrayCount];
		for (unsigned int index = 0; index < arrayCount; ++index)
		{
			reversedControlPointParameters[index] = controlPointParameters[index];
		}

		if (reverseIAxis)
		{
			unsigned int controlPointIndex = 0;
			for (unsigned int k = 0; k < getControlPointMaxCountPerPillar(); ++k)
			{
				for (unsigned int j = 0; j < jPillarCount; ++j)
				{
					for (unsigned int i = 0; i < iPillarCount; ++i)
					{
						unsigned int reversedControlPointIndex = getICellCount() - i + j*iPillarCount + k*iPillarCount*jPillarCount;
						controlPointParameters[controlPointIndex] = reversedControlPointParameters[reversedControlPointIndex];
						++controlPointIndex;
					}
				}
			}
		}

		if (reverseJAxis)
		{
			unsigned int controlPointIndex = 0;
			for (unsigned int k = 0; k < getControlPointMaxCountPerPillar(); ++k)
			{
				for (unsigned int j = 0; j < jPillarCount; ++j)
				{
					for (unsigned int i = 0; i < iPillarCount; ++i)
					{
						unsigned int reversedControlPointIndex = i + (getJCellCount() - j)*iPillarCount + k*iPillarCount*jPillarCount;
						controlPointParameters[controlPointIndex] = reversedControlPointParameters[reversedControlPointIndex];
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
						unsigned int reversedControlPointIndex = i + j*iPillarCount + (getControlPointMaxCountPerPillar()-1-k)*iPillarCount*jPillarCount;
						controlPointParameters[controlPointIndex] = reversedControlPointParameters[reversedControlPointIndex];
						++controlPointIndex;
					}
				}
			}
		}

		delete [] reversedControlPointParameters;
	}
}

bool IjkGridParametricRepresentation::isParametricLineKindConstant() const
{
	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineArray)
	{
		resqml20__ParametricLineArray* paramLineArray = static_cast<resqml20__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray)
		{
			if (static_cast<resqml20__IntegerLatticeArray*>(paramLineArray->LineKindIndices)->Offset[0]->Count == 0)
				return true;
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray)
		{
			return true;
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
		{
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(paramLineArray->LineKindIndices)->Values;
			COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			short * pillarKind = new short [getPillarCount()];
			hdfProxy->readArrayNdOfShortValues(dataset->PathInHdfFile, pillarKind);
			short firstPillarKind = pillarKind[0];
			size_t pillarIndex = 0;
			while (pillarIndex < getPillarCount()) {
				if (pillarKind[pillarIndex] != firstPillarKind) {
					delete [] pillarKind;
					return false;
				}
				++pillarIndex;
			}
			delete [] pillarKind;
			return true;
		}
		else
			throw std::logic_error("Not yet implemented");
	}
	else
		throw std::logic_error("This ijk grid should be a parametric one but does not look like a parametric one.");

	return false;
}

short IjkGridParametricRepresentation::getConstantParametricLineKind() const
{
	if (!isParametricLineKindConstant())
		throw invalid_argument("The parametric line kind is not constant.");

	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineArray)
	{
		resqml20__ParametricLineArray* paramLineArray = static_cast<resqml20__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray)
		{
			return static_cast<resqml20__IntegerLatticeArray*>(paramLineArray->LineKindIndices)->StartValue;
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray)
		{
			return static_cast<resqml20__IntegerConstantArray*>(paramLineArray->LineKindIndices)->Value;
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
		{
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(paramLineArray->LineKindIndices)->Values;
			COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			short * pillarKind = new short [getPillarCount()];
			hdfProxy->readArrayNdOfShortValues(dataset->PathInHdfFile, pillarKind);
			short firstPillarKind = pillarKind[0];
			delete [] pillarKind;
			return firstPillarKind;
		}
		else
			throw std::logic_error("Not yet implemented");
	}
	else
		throw std::logic_error("This ijk grid should be a parametric one but does not look like a parametric one.");
}

void IjkGridParametricRepresentation::getParametricLineKind(short * pillarKind, bool reverseIAxis, bool reverseJAxis) const
{
	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineArray)
	{
		resqml20__ParametricLineArray* paramLineArray = static_cast<resqml20__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
		{
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(paramLineArray->LineKindIndices)->Values;
			COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfShortValues(dataset->PathInHdfFile, pillarKind);
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray)
		{
			const LONG64 value =
				static_cast<resqml20__IntegerConstantArray*>(paramLineArray->LineKindIndices)->Value;
			const ULONG64 lineKindCount =
				static_cast<resqml20__IntegerConstantArray*>(paramLineArray->LineKindIndices)->Count;
			if( lineKindCount != getPillarCount() )
			{
				throw invalid_argument("The parametric line kind count is inconsistent with the pillar count.");
			}
			for (unsigned int i = 0; i < lineKindCount; ++i)
			{
				pillarKind[i] = (short)value;
			}
		}
		else
			throw std::logic_error("Not yet implemented");
	}
	else
		throw std::logic_error("Not yet implemented");

	if (reverseIAxis || reverseJAxis)
	{
		unsigned int iPillarCount = getICellCount()+1;
		unsigned int jPillarCount = getJCellCount()+1;
		unsigned int arrayCount = iPillarCount * jPillarCount;

		// Copy in order not to modify the controlPoints pointer
		double * initialPillarKind = new double [arrayCount];
		for (unsigned int index = 0; index < arrayCount; ++index)
		{
			initialPillarKind[index] = pillarKind[index];
		}

		if (reverseIAxis)
		{
			unsigned int pillarIndex = 0;
			for (unsigned int j = 0; j < jPillarCount; ++j)
			{
				for (unsigned int i = 0; i < iPillarCount; ++i)
				{
					pillarKind[pillarIndex] = initialPillarKind[getICellCount() - i + j*iPillarCount];
					++pillarIndex;
				}
			}
		}

		if (reverseJAxis)
		{
			unsigned int pillarIndex = 0;
			for (unsigned int j = 0; j < jPillarCount; ++j)
			{
				for (unsigned int i = 0; i < iPillarCount; ++i)
				{
					pillarKind[pillarIndex] = initialPillarKind[i + (getJCellCount() - j)*iPillarCount];
					++pillarIndex;
				}
			}
		}

		delete [] initialPillarKind;
	}
}

void IjkGridParametricRepresentation::getParametersOfNodes(double * parameters, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) const
{
	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	if (points->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array)
	{
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__DoubleHdf5Array*>(points->Parameters)->Values;
		COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, parameters);
	}
	else
		throw std::logic_error("Not yet implemented");

	// Copy in order not to modify the controlPoints pointer
	if (reverseIAxis || reverseJAxis || reverseKAxis)
	{
		unsigned int iPillarCount = getICellCount()+1;
		unsigned int jPillarCount = getJCellCount()+1;
		unsigned int kNodeCount = getKCellCount()+1;
		unsigned int arrayCount = iPillarCount * jPillarCount * kNodeCount + getSplitCoordinateLineCount()*kNodeCount;
		double * initialParameters = new double [arrayCount];
		for (unsigned int index = 0; index < arrayCount; ++index)
		{
			initialParameters[index] = parameters[index];
		}

		if (reverseIAxis)
		{
			unsigned int nodeIndex = 0;
			for (unsigned int k = 0; k < kNodeCount; ++k)
			{
				for (unsigned int j = 0; j < jPillarCount; ++j)
				{
					for (unsigned int i = 0; i < iPillarCount; ++i)
					{
						parameters[nodeIndex] = initialParameters[getICellCount() - i + j*iPillarCount + k*(jPillarCount*iPillarCount+getSplitCoordinateLineCount())];
						++nodeIndex;
					}
				}
				nodeIndex += getSplitCoordinateLineCount();
			}
		}

		if (reverseJAxis)
		{
			unsigned int nodeIndex = 0;
			for (unsigned int k = 0; k < kNodeCount; ++k)
			{
				for (unsigned int j = 0; j < jPillarCount; ++j)
				{
					for (unsigned int i = 0; i < iPillarCount; ++i)
					{
						parameters[nodeIndex] = initialParameters[i + (getJCellCount() -j)*iPillarCount + k*(jPillarCount*iPillarCount+getSplitCoordinateLineCount())];
						++nodeIndex;
					}
				}
				nodeIndex += getSplitCoordinateLineCount();
			}
		}

		if (reverseKAxis)
		{
			unsigned int nodeIndex = 0;
			for (unsigned int k = 0; k < kNodeCount; ++k)
			{
				for (unsigned int j = 0; j < jPillarCount; ++j)
				{
					for (unsigned int i = 0; i < iPillarCount; ++i)
					{
						parameters[nodeIndex] = initialParameters[i + j*iPillarCount + (getKCellCount() - k)*(jPillarCount*iPillarCount+getSplitCoordinateLineCount())];
						++nodeIndex;
					}
				}
				nodeIndex += getSplitCoordinateLineCount();
			}
		}

		delete [] initialParameters;
	}
}

void IjkGridParametricRepresentation::getParametersOfNodesOfKInterfaceSequenceOfPatch(unsigned int kInterfaceStart, unsigned int kInterfaceEnd, unsigned int patchIndex, double * parameters)
{
	if (kInterfaceStart > getKCellCount() || kInterfaceEnd > getKCellCount())
		throw range_error("kInterfaceStart and/or kInterfaceEnd is/are out of boundaries.");
	if (kInterfaceStart > kInterfaceEnd)
		throw range_error("kInterfaceStart > kInterfaceEnd");

	if (patchIndex >= getPatchCount())
		throw range_error("An ijk grid has a maximum of one patch.");

	if (parameters == nullptr)
		throw invalid_argument("xyzPoints must be allocated.");

	gsoap_resqml2_0_1::resqml20__PointGeometry const * const geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray const * const parametricPoint3d = static_cast<resqml20__Point3dParametricArray*>(geom->Points);

	// parameters : ordered
	if (parametricPoint3d->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__DoubleHdf5Array*>(parametricPoint3d->Parameters)->Values;
		COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);

		unsigned long long* const numValuesInEachDimension = new unsigned long long[2];
		numValuesInEachDimension[0] = kInterfaceEnd - kInterfaceStart + 1;
		numValuesInEachDimension[1] = getXyzPointCountOfKInterfaceOfPatch(patchIndex);
		unsigned long long* const offsetInEachDimension = new unsigned long long[2];
		offsetInEachDimension[0] = kInterfaceStart;
		offsetInEachDimension[1] = 0;
		hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, parameters,
			numValuesInEachDimension, offsetInEachDimension, 2);
		delete[] numValuesInEachDimension;
		delete[] offsetInEachDimension;
	}
	else {
		throw logic_error("Only floating point parameters stored in an HDF5 dataset are supported for now.");
	}
}

gsoap_resqml2_0_1::eml20__DataObjectReference* IjkGridParametricRepresentation::getHdfProxyDor() const
{
	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	if (points->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array)
	{
		return static_cast<resqml20__DoubleHdf5Array*>(points->Parameters)->Values->HdfProxy;
	}
	else
		throw std::logic_error("Not yet implemented");
}

ULONG64 IjkGridParametricRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	ULONG64 result = getXyzPointCountOfKInterfaceOfPatch(patchIndex) * (getKCellCount() + 1);

	gsoap_resqml2_0_1::resqml20__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml20__IjkGridGeometry*>(getPointGeometry2_0_1(patchIndex));
	if (geom->SplitNodes != nullptr) {
		result += geom->SplitNodes->Count;
	}

	if (isTruncated()) {
		result += static_cast<gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation*>(gsoapProxy2_0_1)->TruncationCells->TruncationNodeCount;
	}

	return result;
}

void IjkGridParametricRepresentation::getXyzPointsOfKInterfaceSequenceOfPatch(const unsigned int & kInterfaceStart, const unsigned int & kInterfaceEnd, const unsigned int & patchIndex, double * xyzPoints)
{
	if (xyzPoints == nullptr) {
		throw invalid_argument("xyzPoints must be allocated.");
	}
	if (patchIndex >= getPatchCount()) {
		throw range_error("An ijk grid has a maximum of one patch.");
	}

	// Get the parameters
	const ULONG64 xyzPointCount = getXyzPointCountOfKInterfaceOfPatch(patchIndex);
	double * const parameters = new double[xyzPointCount * (kInterfaceEnd - kInterfaceStart + 1)];
	getParametersOfNodesOfKInterfaceSequenceOfPatch(kInterfaceStart, kInterfaceEnd, patchIndex, parameters);

	// Convert the parameters into XYZ points
	if (pillarInformation == nullptr)
	{
		pillarInformation = new PillarInformation();
		loadPillarInformation(*pillarInformation);
	}
	resqml20__Point3dParametricArray const * const parametricPoint3d = static_cast<resqml20__Point3dParametricArray*>(getPointGeometry2_0_1(patchIndex)->Points);
	if (parametricPoint3d->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineArray) {
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
				delete[] parameters;
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
					   // Cleaning
					delete[] parameters;
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
				// Cleaning
				delete[] parameters;
				throw logic_error("Computing XYZ from parameters on a non natural cubic spline or on a minimum curvature spline is not implemented yet.");
			}
			++paramIndex;
		}
	}
	else
	{
		delete[] parameters;
		throw logic_error("Parametric lines should be of type resqml20__ParametricLineArray. Other type is not implemented yet.");
	}

	delete[] parameters;
}

void IjkGridParametricRepresentation::getXyzPointsOfBlockOfPatch(const unsigned int & patchIndex, double * xyzPoints)
{
	if (blockInformation == nullptr)
		throw invalid_argument("The block information must have been loaded first.");

	if (patchIndex >= getPatchCount())
		throw range_error("An ijk grid has a maximum of one patch.");

	if (xyzPoints == nullptr)
		throw invalid_argument("xyzPoints must be allocated.");

	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* parametricPoint3d = static_cast<resqml20__Point3dParametricArray*>(geom->Points);

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
	double * parameters = new double[getXyzPointCountOfBlock()];
	if (parametricPoint3d->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {	
		unsigned long long* blockCountPerDimension = new unsigned long long[2];
		blockCountPerDimension[0] = 1;
		blockCountPerDimension[1] = blockInformation->jInterfaceEnd - blockInformation->jInterfaceStart + 1;
		unsigned long long* offsetPerDimension = new unsigned long long[2];
		offsetPerDimension[0] = blockInformation->kInterfaceStart;
		offsetPerDimension[1] = blockInformation->jInterfaceStart * (getICellCount() + 1) + blockInformation->iInterfaceStart;
		unsigned long long* strideInEachDimension = new unsigned long long[2];
		strideInEachDimension[0] = 1;
		strideInEachDimension[1] = (blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1) + ((getICellCount() + 1) - (blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1));
		unsigned long long* blockSizeInEachDimension = new unsigned long long[2];
		blockSizeInEachDimension[0] = blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart + 1;
		blockSizeInEachDimension[1] = blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1;

		eml20__Hdf5Dataset const * xmlDataset = static_cast<resqml20__DoubleHdf5Array*>(parametricPoint3d->Parameters)->Values;
		COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(xmlDataset);

		hid_t dataset, filespace;
		hdfProxy->selectArrayNdOfValues(
			xmlDataset->PathInHdfFile,
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
									xmlDataset->PathInHdfFile,
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
		hdfProxy->readArrayNdOfDoubleValues(dataset, filespace,
			parameters, slab_size);

		delete[] blockCountPerDimension;
		delete[] offsetPerDimension;
		delete[] strideInEachDimension;
		delete[] blockSizeInEachDimension;
	}
	else {
		delete[] parameters;
		throw logic_error("Non floating point coordinate line parameters are not implemented yet");
	}

	if (parametricPoint3d->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineArray) {
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
					delete[] parameters;
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
						   // Cleaning
						delete[] parameters;
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
					// Cleaning
					delete[] parameters;
					throw logic_error("Computing XYZ from parameters on a non natural cubic spline or on a minimum curvature spline is not implemented yet.");
				}
			}
		}
	}
	else
	{
		delete[] parameters;
		throw logic_error("Parametric lines should be of type resqml20__ParametricLineArray. Other type is not implemented yet.");
	}

	delete[] parameters;
}

void IjkGridParametricRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);

	getXyzPointsOfPatchFromParametricPoints(points, xyzPoints);

	// Truncation
	if (isTruncated()) {
		resqml20__AbstractGridGeometry* truncatedGeom = static_cast<gsoap_resqml2_0_1::resqml20__AbstractGridGeometry*>(geom);
		if (truncatedGeom->AdditionalGridPoints.size() == 1 && truncatedGeom->AdditionalGridPoints[0]->Attachment == resqml20__GridGeometryAttachment__nodes) {
			if (truncatedGeom->AdditionalGridPoints[0]->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array)
			{
				eml20__Hdf5Dataset const * xmlDataset = static_cast<resqml20__Point3dHdf5Array*>(truncatedGeom->AdditionalGridPoints[0]->Points)->Coordinates;
				COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(xmlDataset);
				xyzPoints += getXyzPointCountOfPatch(patchIndex) - static_cast<gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation*>(gsoapProxy2_0_1)->TruncationCells->TruncationNodeCount;
				hdfProxy->readArrayNdOfDoubleValues(xmlDataset->PathInHdfFile, xyzPoints);
			}
			else {
				throw invalid_argument("The additional grid points must be explicit ones for now. Parametric additional points are not supported yet for example.");
			}
		}
		else {
			throw invalid_argument("The truncated geometry must have one additional grid points construct (more than one is not implemented in fesapi yet although allowed by the standard). The attachment of this grid points must be set to node.");
		}
	}
}

void IjkGridParametricRepresentation::setGeometryAsParametricNonSplittedPillarNodes(
	gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, bool isRightHanded,
	double * parameters, double * controlPoints, double * controlPointParameters, unsigned int controlPointMaxCountPerPillar, short * pillarKind, COMMON_NS::AbstractHdfProxy* proxy, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	setGeometryAsParametricSplittedPillarNodes(mostComplexPillarGeometry, isRightHanded, parameters, controlPoints, controlPointParameters, controlPointMaxCountPerPillar, pillarKind, proxy,
		0, nullptr, nullptr, nullptr, localCrs);
}

void IjkGridParametricRepresentation::setGeometryAsParametricNonSplittedPillarNodesUsingExistingDatasets(
	gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
	const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars, COMMON_NS::AbstractHdfProxy* proxy, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(mostComplexPillarGeometry, kDirectionKind, isRightHanded, parameters, controlPoints, controlPointParameters, controlPointMaxCountPerPillar, pillarKind, definedPillars, proxy,
		0, "", "", "", localCrs);
}

void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodes(
	gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, bool isRightHanded,
	double * parameters, double * controlPoints, double * controlPointParameters, unsigned int controlPointMaxCountPerPillar, short * pillarKind, COMMON_NS::AbstractHdfProxy * proxy,
	unsigned long splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
	unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (pillarKind == nullptr) {
		throw invalid_argument("The kind of the coordinate lines cannot be null.");
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

	gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind = computeKDirection(controlPoints, controlPointMaxCountPerPillar, pillarKind, localCrs);

	const std::string hdfDatasetPrefix = "/RESQML/" + gsoapProxy2_0_1->uuid;
	setGeometryAsParametricSplittedPillarNodesWithoutPillarKindUsingExistingDatasets(kDirectionKind, isRightHanded,
		hdfDatasetPrefix + "/PointParameters", hdfDatasetPrefix + "/ControlPoints", controlPointParameters != nullptr ? hdfDatasetPrefix + "/controlPointParameters" : "", controlPointMaxCountPerPillar, proxy,
		splitCoordinateLineCount, hdfDatasetPrefix + "/PillarIndices",
		hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + CUMULATIVE_LENGTH_DS_NAME, hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + ELEMENTS_DS_NAME, localCrs);

	writeGeometryOnHdf(parameters,
		controlPoints, controlPointParameters, controlPointMaxCountPerPillar,
		splitCoordinateLineCount, pillarOfCoordinateLine,
		splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns, proxy);

	gsoap_resqml2_0_1::resqml20__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml20__IjkGridGeometry*>(getPointGeometry2_0_1(0));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	geom->PillarShape = mostComplexPillarGeometry;

	// XML Pillar defined
	resqml20__BooleanHdf5Array* xmlDefinedPillars = soap_new_resqml20__BooleanHdf5Array(gsoapProxy2_0_1->soap);
	geom->PillarGeometryIsDefined = xmlDefinedPillars;
	xmlDefinedPillars->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlDefinedPillars->Values->HdfProxy = proxy->newResqmlReference();
	xmlDefinedPillars->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/PillarGeometryIsDefined";

	// HDF Pillar defined
	getRepository()->addRelationship(this, proxy);
	const unsigned int pillarCount = getPillarCount();
	unsigned char * definedPillars = new unsigned char[pillarCount];
	for (unsigned int i = 0; i < pillarCount; ++i) {
		definedPillars[i] = pillarKind[i] == -1 ? 0 : 1;
	}
	hsize_t * pillarGeometryIsDefinedCount = new hsize_t[2];
	pillarGeometryIsDefinedCount[0] = getJCellCount() + 1;
	pillarGeometryIsDefinedCount[1] = getICellCount() + 1;
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid, "PillarGeometryIsDefined", H5T_NATIVE_UCHAR, definedPillars, pillarGeometryIsDefinedCount, 2);
	delete [] pillarGeometryIsDefinedCount;
	delete [] definedPillars;

	// *********************************
	// Overwrite line kind hdf dataset
	// *********************************
	resqml20__Point3dParametricArray* xmlPoints = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	resqml20__ParametricLineArray* paramLines = static_cast<resqml20__ParametricLineArray*>(xmlPoints->ParametricLines);
	paramLines->KnotCount = controlPointMaxCountPerPillar;

	// XML Line kinds
	resqml20__IntegerHdf5Array* xmlLineKinds = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	paramLines->LineKindIndices = xmlLineKinds;
	xmlLineKinds->NullValue = -1;
	xmlLineKinds->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlLineKinds->Values->HdfProxy = proxy->newResqmlReference();
	xmlLineKinds->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/LineKindIndices";

	// HDF Line kinds
	hsize_t * lineKindCount = new hsize_t[2];
	lineKindCount[0] = getJCellCount() + 1;
	lineKindCount[1] = getICellCount() + 1;
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid, "LineKindIndices", H5T_NATIVE_SHORT, pillarKind, lineKindCount, 2);
	delete [] lineKindCount;
}

void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
	gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
	const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars, COMMON_NS::AbstractHdfProxy* proxy,
	unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
	const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (pillarKind.empty())
		throw invalid_argument("The kind of the coordinate lines cannot be null.");
	if (definedPillars.empty())
		throw invalid_argument("The defined pillars cannot be null.");

	setGeometryAsParametricSplittedPillarNodesWithoutPillarKindUsingExistingDatasets(kDirectionKind, isRightHanded,
		parameters, controlPoints, controlPointParameters, controlPointMaxCountPerPillar, proxy,
		splitCoordinateLineCount, pillarOfCoordinateLine,
		splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns, localCrs);

	gsoap_resqml2_0_1::resqml20__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml20__IjkGridGeometry*>(getPointGeometry2_0_1(0));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	geom->PillarShape = mostComplexPillarGeometry;

	// XML Pillar defined
	resqml20__BooleanHdf5Array* xmlDefinedPillars = soap_new_resqml20__BooleanHdf5Array(gsoapProxy2_0_1->soap);
	geom->PillarGeometryIsDefined = xmlDefinedPillars;
	xmlDefinedPillars->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlDefinedPillars->Values->HdfProxy = proxy->newResqmlReference();
	xmlDefinedPillars->Values->PathInHdfFile = definedPillars;

	// *********************************
	// Line kind hdf dataset
	// *********************************
	resqml20__Point3dParametricArray* xmlPoints = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	resqml20__ParametricLineArray* paramLines = static_cast<resqml20__ParametricLineArray*>(xmlPoints->ParametricLines);
	paramLines->KnotCount = controlPointMaxCountPerPillar;

	// XML Line kinds
	resqml20__IntegerHdf5Array* xmlLineKinds = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	paramLines->LineKindIndices = xmlLineKinds;
	xmlLineKinds->NullValue = -1;
	xmlLineKinds->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlLineKinds->Values->HdfProxy = proxy->newResqmlReference();
	xmlLineKinds->Values->PathInHdfFile = pillarKind;
}

void IjkGridParametricRepresentation::writeGeometryOnHdf(double const * parameters,
	double const * controlPoints, double const * controlPointParameters, unsigned int controlPointCountPerPillar,
	unsigned long splitCoordinateLineCount, unsigned int const * pillarOfCoordinateLine,
	unsigned int const * splitCoordinateLineColumnCumulativeCount, unsigned int const * splitCoordinateLineColumns, COMMON_NS::AbstractHdfProxy * proxy)
{
	if (splitCoordinateLineCount == 0) {
		// HDF
		hsize_t * numValues = new hsize_t[3];
		numValues[0] = getKCellCount() + 1;
		numValues[1] = getJCellCount() + 1;
		numValues[2] = getICellCount() + 1;

		proxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid, "PointParameters", parameters, numValues, 3);
		delete[] numValues;
	}
	else {
		// PointParameters
		hsize_t * numValues = new hsize_t[2];
		numValues[0] = getKCellCount() + 1;
		numValues[1] = (getJCellCount() + 1) * (getICellCount() + 1) + splitCoordinateLineCount;

		proxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid, "PointParameters", parameters, numValues, 2);
		delete[] numValues;

		// split coordinate lines
		numValues = new hsize_t[1];
		numValues[0] = splitCoordinateLineCount;
		proxy->writeArrayNd(gsoapProxy2_0_1->uuid, "PillarIndices", H5T_NATIVE_UINT, pillarOfCoordinateLine, numValues, 1);
		delete[] numValues;

		proxy->writeItemizedListOfList(gsoapProxy2_0_1->uuid, "ColumnsPerSplitCoordinateLine", H5T_NATIVE_UINT, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineCount, H5T_NATIVE_UINT, splitCoordinateLineColumns, splitCoordinateLineColumnCumulativeCount[splitCoordinateLineCount - 1]);
	}

	// *********************************
	// Parametric coordinate lines
	// *********************************
	// HDF control points
	hsize_t * controlPointCount = new hsize_t[4];
	controlPointCount[0] = controlPointCountPerPillar;
	controlPointCount[1] = getJCellCount() + 1;
	controlPointCount[2] = getICellCount() + 1;
	controlPointCount[3] = 3; // 3 for X, Y and Z
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid, "ControlPoints", H5T_NATIVE_DOUBLE, controlPoints, controlPointCount, 4);
	delete[] controlPointCount;

	// *********************************
	// Control point parameters are defined
	// *********************************
	if (controlPointParameters != nullptr) {
		// HDF control points parameters
		hsize_t * controlPointParamCount = new hsize_t[3];
		controlPointParamCount[0] = controlPointCountPerPillar;
		controlPointParamCount[1] = getJCellCount() + 1;
		controlPointParamCount[2] = getICellCount() + 1;
		proxy->writeArrayNd(gsoapProxy2_0_1->uuid, "controlPointParameters", H5T_NATIVE_DOUBLE, controlPointParameters, controlPointParamCount, 3);
		delete[] controlPointParamCount;
	}
}

void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodes(bool isRightHanded,
	double const * parameters, double const * controlPoints, double const * controlPointParameters, unsigned int controlPointCountPerPillar, short pillarKind, COMMON_NS::AbstractHdfProxy * proxy,
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

	const std::string hdfDatasetPrefix = "/RESQML/" + gsoapProxy2_0_1->uuid;
	setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(kDirectionKind, isRightHanded,
		hdfDatasetPrefix + "/PointParameters", hdfDatasetPrefix + "/ControlPoints", controlPointParameters != nullptr ? hdfDatasetPrefix + "/controlPointParameters" : "", controlPointCountPerPillar, pillarKind, proxy,
		splitCoordinateLineCount, hdfDatasetPrefix + "/PillarIndices",
		hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + CUMULATIVE_LENGTH_DS_NAME, hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + ELEMENTS_DS_NAME, localCrs);

	writeGeometryOnHdf(parameters,
		controlPoints, controlPointParameters, controlPointCountPerPillar,
		splitCoordinateLineCount, pillarOfCoordinateLine,
		splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns, proxy);
}

void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodesWithoutPillarKindUsingExistingDatasets(
	gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
	const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointCountPerPillar, COMMON_NS::AbstractHdfProxy* proxy,
	unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
	const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (controlPointCountPerPillar < 1) {
		throw invalid_argument("The max count of control points per coordinate line of the ijk grid cannot be less than one.");
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

	resqml20__IjkGridGeometry* geom = soap_new_resqml20__IjkGridGeometry(gsoapProxy2_0_1->soap);
	geom->LocalCrs = localCrs->newResqmlReference();
	if (!isTruncated()) {
		getSpecializedGsoapProxy()->Geometry = geom;
	}
	else {
		getSpecializedTruncatedGsoapProxy()->Geometry = geom;
	}
	geom->GridIsRighthanded = isRightHanded;
	geom->KDirection = kDirectionKind;

	getRepository()->addRelationship(this, proxy);
	// XML parametric nodes
	resqml20__Point3dParametricArray* xmlPoints = soap_new_resqml20__Point3dParametricArray(gsoapProxy2_0_1->soap);
	geom->Points = xmlPoints;
	resqml20__DoubleHdf5Array* xmlParameters = soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
	xmlPoints->Parameters = xmlParameters;
	xmlParameters->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlParameters->Values->HdfProxy = proxy->newResqmlReference();
	xmlParameters->Values->PathInHdfFile = parameters;

	if (splitCoordinateLineCount > 0) {
		// XML split coordinate lines
		geom->SplitCoordinateLines = soap_new_resqml20__ColumnLayerSplitCoordinateLines(gsoapProxy2_0_1->soap);;
		geom->SplitCoordinateLines->Count = splitCoordinateLineCount;

		//XML
		resqml20__IntegerHdf5Array* pillarIndices = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
		geom->SplitCoordinateLines->PillarIndices = pillarIndices;
		pillarIndices->NullValue = getPillarCount();
		pillarIndices->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		pillarIndices->Values->HdfProxy = proxy->newResqmlReference();
		pillarIndices->Values->PathInHdfFile = pillarOfCoordinateLine;

		//XML
		geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine = soap_new_resqml20__ResqmlJaggedArray(gsoapProxy2_0_1->soap);
		// Cumulative
		resqml20__IntegerHdf5Array* cumulativeLength = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
		geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->CumulativeLength = cumulativeLength;
		cumulativeLength->NullValue = 0;
		cumulativeLength->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		cumulativeLength->Values->HdfProxy = proxy->newResqmlReference();
		cumulativeLength->Values->PathInHdfFile = splitCoordinateLineColumnCumulativeCount;
		// Elements
		resqml20__IntegerHdf5Array* elements = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
		geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements = elements;
		elements->NullValue = getColumnCount();
		elements->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		elements->Values->HdfProxy = proxy->newResqmlReference();
		elements->Values->PathInHdfFile = splitCoordinateLineColumns;
	}

	// *********************************
	// Parametric coordinate lines
	// *********************************
	resqml20__ParametricLineArray* paramLines = soap_new_resqml20__ParametricLineArray(gsoapProxy2_0_1->soap);
	xmlPoints->ParametricLines = paramLines;
	paramLines->KnotCount = controlPointCountPerPillar;

	// XML control points
	resqml20__Point3dHdf5Array* xmlcontrolPoints = soap_new_resqml20__Point3dHdf5Array(gsoapProxy2_0_1->soap);
	paramLines->ControlPoints = xmlcontrolPoints;
	xmlcontrolPoints->Coordinates = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlcontrolPoints->Coordinates->HdfProxy = proxy->newResqmlReference();
	xmlcontrolPoints->Coordinates->PathInHdfFile = controlPoints;

	// *********************************
	// Control point parameters are defined
	// *********************************
	if (!controlPointParameters.empty()) {
		// XML control point parameters
		resqml20__DoubleHdf5Array* xmlcontrolPointParams = soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
		paramLines->ControlPointParameters = xmlcontrolPointParams;
		xmlcontrolPointParams->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		xmlcontrolPointParams->Values->HdfProxy = proxy->newResqmlReference();
		xmlcontrolPointParams->Values->PathInHdfFile = controlPointParameters;
	}

	getRepository()->addRelationship(this, localCrs);
}


void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
	gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
	const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointCountPerPillar, short pillarKind, COMMON_NS::AbstractHdfProxy* proxy,
	unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
	const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (pillarKind < 0 || pillarKind > 5) {
		throw range_error("The kind of the coordinate lines is out of range.");
	}

	setGeometryAsParametricSplittedPillarNodesWithoutPillarKindUsingExistingDatasets(kDirectionKind, isRightHanded,
		parameters, controlPoints, controlPointParameters, controlPointCountPerPillar, proxy,
		splitCoordinateLineCount, pillarOfCoordinateLine,
		splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns, localCrs);

	resqml20__IjkGridGeometry* geom = isTruncated() ? getSpecializedTruncatedGsoapProxy()->Geometry : getSpecializedGsoapProxy()->Geometry;
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}

	if (pillarKind > 1 || controlPointCountPerPillar > 2) {
		geom->PillarShape = resqml20__PillarShape__curved;
	}
	else if (pillarKind == 1) {
		geom->PillarShape = resqml20__PillarShape__straight;
	}
	else {
		geom->PillarShape = resqml20__PillarShape__vertical;
	}

	// XML Pillar defined
	resqml20__BooleanConstantArray* xmlDefinedPillars = soap_new_resqml20__BooleanConstantArray(gsoapProxy2_0_1->soap);
	geom->PillarGeometryIsDefined = xmlDefinedPillars;
	xmlDefinedPillars->Value = true;
	xmlDefinedPillars->Count = getPillarCount();

	resqml20__Point3dParametricArray* xmlPoints = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	resqml20__ParametricLineArray* paramLines = static_cast<resqml20__ParametricLineArray*>(xmlPoints->ParametricLines);

	// XML Line kinds
	resqml20__IntegerConstantArray* xmlLineKinds = soap_new_resqml20__IntegerConstantArray(gsoapProxy2_0_1->soap);
	paramLines->LineKindIndices = xmlLineKinds;
	xmlLineKinds->Value = pillarKind;
	xmlLineKinds->Count = getPillarCount();
}

void IjkGridParametricRepresentation::loadPillarInformation(IjkGridParametricRepresentation::PillarInformation & pillarInfo) const
{
	pillarInfo.cleanMemory();

	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	if (geom->Points->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dParametricArray)
	{
		throw invalid_argument("The geometry of the grid is not a parametric one.");
	}
	resqml20__Point3dParametricArray* parametricPoint3d = static_cast<resqml20__Point3dParametricArray*>(geom->Points);

	if (parametricPoint3d->ParametricLines->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineArray) {
		throw logic_error("Parametric lines should be of type resqml20__ParametricLineArray. Other type is not implemented yet.");
	}

	resqml20__ParametricLineArray* paramLineArray = static_cast<resqml20__ParametricLineArray*>(parametricPoint3d->ParametricLines);
	pillarInfo.maxControlPointCount = getControlPointMaxCountPerPillar();
	pillarInfo.parametricLineCount = getPillarCount();
	pillarInfo.splitLineCount = getSplitCoordinateLineCount();

	// Control points
	pillarInfo.controlPoints = new double[pillarInfo.parametricLineCount*pillarInfo.maxControlPointCount*3];
	getControlPoints(pillarInfo.controlPoints);

	// Control points parameters
	if (paramLineArray->ControlPointParameters != nullptr) {
		pillarInfo.controlPointParameters = new double[pillarInfo.parametricLineCount*pillarInfo.maxControlPointCount];
		getControlPointParameters(pillarInfo.controlPointParameters);
	}

	// Line kind indices
	pillarInfo.pillarKind = new short[pillarInfo.parametricLineCount];
	getParametricLineKind(pillarInfo.pillarKind);

	// Pillars of split line
	if (pillarInfo.splitLineCount > 0) {
		pillarInfo.pillarOfSplitCoordLines = new unsigned int [pillarInfo.splitLineCount];
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
				unsigned int globalCpIndex = parametricLineIndex + cpIndex*pillarInfo.parametricLineCount;
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
					double zvalue = pillarInfo.controlPoints[parametricLineIndex + cpIndex*pillarInfo.parametricLineCount * 3 + 2];
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

void IjkGridParametricRepresentation::getXyzPointsOfPatchFromParametricPoints(gsoap_resqml2_0_1::resqml20__Point3dParametricArray* parametricPoint3d, double * xyzPoints) const
{
	// parameters : ordered
	double * parameters = new double[getXyzPointCountOfPatch(0)];
	if (parametricPoint3d->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__DoubleHdf5Array*>(parametricPoint3d->Parameters)->Values;
		COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, parameters);
	}
	else {
		delete[] parameters;
		throw logic_error("Non floating point coordinate line parameters are not implemented yet");
	}

	if (parametricPoint3d->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineArray) {
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

						delete[] parameters;
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
					delete[] parameters;
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
						// Cleaning
						delete [] parameters;
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
					// Cleaning
					delete [] parameters;
					throw logic_error("Computing XYZ from parameters on a non natural cubic spline or on a minimum curvature spline is not implemented yet.");
				}
				++paramIndex;
			}
		}
	}
	else
	{
		delete [] parameters;
		throw logic_error("Parametric lines should be of type resqml20__ParametricLineArray. Other type is not implemented yet.");
	}

	delete [] parameters;
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

bool IjkGridParametricRepresentation::isNodeGeometryCompressed() const {
	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);

	if (points->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__DoubleHdf5Array*>(points->Parameters)->Values;
		COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		return hdfProxy->isCompressed(dataset->PathInHdfFile);
	}
	else {
		throw logic_error("Non floating point coordinate line parameters are not implemented yet");
	}
}
