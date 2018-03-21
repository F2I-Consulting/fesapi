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

#include "resqml2_0_1/IjkGridParametricRepresentation.h"

#include <stdexcept>

#include "hdf5.h"

#include "resqml2/AbstractFeatureInterpretation.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "resqml2/AbstractValuesProperty.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace RESQML2_0_1_NS;

IjkGridParametricRepresentation::IjkGridParametricRepresentation(soap* soapContext, RESQML2_NS::AbstractLocal3dCrs * crs,
	const std::string & guid, const std::string & title,
	const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount,
	bool withTruncatedPillars) :
	AbstractIjkGridRepresentation(soapContext, crs, guid, title, iCount, jCount, kCount, withTruncatedPillars), pillarInformation(nullptr)
{
}

IjkGridParametricRepresentation::IjkGridParametricRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
	const std::string & guid, const std::string & title,
	const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount,
	bool withTruncatedPillars) :
	AbstractIjkGridRepresentation(interp, crs, guid, title, iCount, jCount, kCount, withTruncatedPillars), pillarInformation(nullptr)
{
}

unsigned int IjkGridParametricRepresentation::getControlPointMaxCountPerPillar() const
{
	gsoap_resqml2_0_1::resqml2__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineArray) {
		return static_cast<resqml2__ParametricLineArray*>(points->ParametricLines)->KnotCount;
	}
	else
		throw std::logic_error("Not yet implemented");
}

void IjkGridParametricRepresentation::getControlPoints(double * controlPoints, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) const
{
	gsoap_resqml2_0_1::resqml2__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineArray) {
		resqml2__ParametricLineArray* paramLineArray = static_cast<resqml2__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->ControlPoints->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dHdf5Array) {
			hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__Point3dHdf5Array*>(paramLineArray->ControlPoints)->Coordinates->PathInHdfFile, controlPoints);
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
	gsoap_resqml2_0_1::resqml2__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineArray)
	{
		resqml2__ParametricLineArray* paramLineArray = static_cast<resqml2__ParametricLineArray*>(points->ParametricLines);
		return paramLineArray->ControlPointParameters != nullptr;
	}
	else
		throw std::logic_error("Not yet implemented");
}

void IjkGridParametricRepresentation::getControlPointParameters(double * controlPointParameters, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) const
{
	gsoap_resqml2_0_1::resqml2__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineArray)
	{
		resqml2__ParametricLineArray* paramLineArray = static_cast<resqml2__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->ControlPointParameters == nullptr)
			throw invalid_argument("The grid does not contain any control point parameters.");
		if (paramLineArray->ControlPointParameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
		{
			hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__DoubleHdf5Array*>(paramLineArray->ControlPointParameters)->Values->PathInHdfFile, controlPointParameters);
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
	gsoap_resqml2_0_1::resqml2__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineArray)
	{
		resqml2__ParametricLineArray* paramLineArray = static_cast<resqml2__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerLatticeArray)
		{
			if (static_cast<resqml2__IntegerLatticeArray*>(paramLineArray->LineKindIndices)->Offset[0]->Count == 0)
				return true;
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
		{
			return true;
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			short * pillarKind = new short [getPillarCount()];
			hdfProxy->readArrayNdOfShortValues(static_cast<resqml2__IntegerHdf5Array*>(paramLineArray->LineKindIndices)->Values->PathInHdfFile, pillarKind);
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

	gsoap_resqml2_0_1::resqml2__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineArray)
	{
		resqml2__ParametricLineArray* paramLineArray = static_cast<resqml2__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerLatticeArray)
		{
			return static_cast<resqml2__IntegerLatticeArray*>(paramLineArray->LineKindIndices)->StartValue;
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
		{
			return static_cast<resqml2__IntegerConstantArray*>(paramLineArray->LineKindIndices)->Value;
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			short * pillarKind = new short [getPillarCount()];
			hdfProxy->readArrayNdOfShortValues(static_cast<resqml2__IntegerHdf5Array*>(paramLineArray->LineKindIndices)->Values->PathInHdfFile, pillarKind);
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
	gsoap_resqml2_0_1::resqml2__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineArray)
	{
		resqml2__ParametricLineArray* paramLineArray = static_cast<resqml2__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			hdfProxy->readArrayNdOfShortValues(static_cast<resqml2__IntegerHdf5Array*>(paramLineArray->LineKindIndices)->Values->PathInHdfFile, pillarKind);
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
		{
			const LONG64 value =
				static_cast<resqml2__IntegerConstantArray*>(paramLineArray->LineKindIndices)->Value;
			const ULONG64 lineKindCount =
				static_cast<resqml2__IntegerConstantArray*>(paramLineArray->LineKindIndices)->Count;
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
	gsoap_resqml2_0_1::resqml2__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(geom->Points);
	if (points->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
	{
		hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__DoubleHdf5Array*>(points->Parameters)->Values->PathInHdfFile, parameters);
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

string IjkGridParametricRepresentation::getHdfProxyUuid() const
{
	gsoap_resqml2_0_1::resqml2__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(geom->Points);
	if (points->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
	{
		return static_cast<resqml2__DoubleHdf5Array*>(points->Parameters)->Values->HdfProxy->UUID;
	}
	else
		throw std::logic_error("Not yet implemented");
}

ULONG64 IjkGridParametricRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	ULONG64 result = getXyzPointCountOfKInterfaceOfPatch(patchIndex) * (getKCellCount() + 1);

	gsoap_resqml2_0_1::resqml2__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml2__IjkGridGeometry*>(getPointGeometry2_0_1(patchIndex));
	if (geom->SplitNodes != nullptr) {
		result += geom->SplitNodes->Count;
	}

	if (isTruncated()) {
		result += static_cast<gsoap_resqml2_0_1::_resqml2__TruncatedIjkGridRepresentation*>(gsoapProxy2_0_1)->TruncationCells->TruncationNodeCount;
	}

	return result;
}

void IjkGridParametricRepresentation::getXyzPointsOfKInterfaceSequenceOfPatch(const unsigned int & kInterfaceStart, const unsigned int & kInterfaceEnd, const unsigned int & patchIndex, double * xyzPoints)
{
	if ( kInterfaceStart > getKCellCount() || kInterfaceEnd > getKCellCount())
		throw range_error("kInterfaceStart and/or kInterfaceEnd is/are out of boundaries.");
	if (kInterfaceStart > kInterfaceEnd)
		throw range_error("kInterfaceStart > kInterfaceEnd");
	
	if (patchIndex >= getPatchCount())
		throw range_error("An ijk grid has a maximum of one patch.");

	if (xyzPoints == nullptr)
		throw invalid_argument("xyzPoints must be allocated.");

	gsoap_resqml2_0_1::resqml2__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml2__Point3dParametricArray* parametricPoint3d = static_cast<resqml2__Point3dParametricArray*>(geom->Points);

	if (pillarInformation == nullptr)
	{
		pillarInformation = new PillarInformation();
		loadPillarInformation(*pillarInformation);
	}
	
	ULONG64 xyzPointCount = getXyzPointCountOfKInterfaceOfPatch(patchIndex);

	// parameters : ordered
	double * parameters = new double[xyzPointCount * (kInterfaceEnd - kInterfaceStart + 1)];
	if (parametricPoint3d->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
		const std::string pathInHdfFile = static_cast<resqml2__DoubleHdf5Array*>(parametricPoint3d->Parameters)->Values->PathInHdfFile;
	
		unsigned long long* numValuesInEachDimension = new unsigned long long[2];
		numValuesInEachDimension[0] = kInterfaceEnd - kInterfaceStart + 1;
		numValuesInEachDimension[1] = xyzPointCount;
		unsigned long long* offsetInEachDimension = new unsigned long long[2];
		offsetInEachDimension[0] = kInterfaceStart;
		offsetInEachDimension[1] = 0;
		hdfProxy->readArrayNdOfDoubleValues(pathInHdfFile, parameters,
			numValuesInEachDimension, offsetInEachDimension, 2);
		delete[] numValuesInEachDimension;
		delete[] offsetInEachDimension;
	}
	else {
		delete[] parameters;
		throw logic_error("Non floating point coordinate line parameters are not implemented yet");
	}

	if (parametricPoint3d->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineArray) {
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
		throw logic_error("Parametric lines should be of type resqml2__ParametricLineArray. Other type is not implemented yet.");
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

	gsoap_resqml2_0_1::resqml2__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml2__Point3dParametricArray* parametricPoint3d = static_cast<resqml2__Point3dParametricArray*>(geom->Points);

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
	if (parametricPoint3d->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
		const std::string pathInHdfFile = static_cast<resqml2__DoubleHdf5Array*>(parametricPoint3d->Parameters)->Values->PathInHdfFile;
	
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

		int dataset, filespace;
		hdfProxy->selectArrayNdOfValues(
			pathInHdfFile,
			blockCountPerDimension,
			offsetPerDimension,
			strideInEachDimension,
			blockSizeInEachDimension,
			2,
			true,
			dataset,
			filespace);

		unsigned long long slab_size = 1;
		for (unsigned int h = 0; h < 2; ++h) {
			slab_size *= blockSizeInEachDimension[h];
		}
		for (unsigned int h = 0; h < 2; ++h) {
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
					for (unsigned int splitCoordinateLineIndex = 0; splitCoordinateLineIndex < splitInformation[pillarIndex].size(); ++splitCoordinateLineIndex)
					{
						// traversing adjacent columns, it current column is in the bloc, corresponding coordinate line is added to the selected region
						for (unsigned int columnIndex = 0; columnIndex < splitInformation[pillarIndex][splitCoordinateLineIndex].second.size(); ++columnIndex)
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
									pathInHdfFile,
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
		throw logic_error("Non floating point coordinate line parameters are not implemented yet");
	}

	if (parametricPoint3d->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineArray) {
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
		throw logic_error("Parametric lines should be of type resqml2__ParametricLineArray. Other type is not implemented yet.");
	}

	delete[] parameters;
}

void IjkGridParametricRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	gsoap_resqml2_0_1::resqml2__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(geom->Points);

	getXyzPointsOfPatchFromParametricPoints(points, xyzPoints);

	// Truncation
	if (isTruncated()) {
		resqml2__AbstractGridGeometry* truncatedGeom = static_cast<gsoap_resqml2_0_1::resqml2__AbstractGridGeometry*>(geom);
		if (truncatedGeom->AdditionalGridPoints.size() == 1 && truncatedGeom->AdditionalGridPoints[0]->Attachment == resqml2__GridGeometryAttachment__nodes) {
			if (truncatedGeom->AdditionalGridPoints[0]->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dHdf5Array)
			{
				xyzPoints += getXyzPointCountOfPatch(patchIndex) - static_cast<gsoap_resqml2_0_1::_resqml2__TruncatedIjkGridRepresentation*>(gsoapProxy2_0_1)->TruncationCells->TruncationNodeCount;
				hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__Point3dHdf5Array*>(truncatedGeom->AdditionalGridPoints[0]->Points)->Coordinates->PathInHdfFile, xyzPoints);
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
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, const unsigned int & controlPointMaxCountPerPillar, short * pillarKind, COMMON_NS::AbstractHdfProxy* proxy)
{
	setGeometryAsParametricSplittedPillarNodes(mostComplexPillarGeometry, kDirectionKind, isRightHanded, parameters, controlPoints, controlPointParameters, controlPointMaxCountPerPillar, pillarKind, proxy,
		0, nullptr, nullptr, nullptr);
}

void IjkGridParametricRepresentation::setGeometryAsParametricNonSplittedPillarNodesUsingExistingDatasets(
	const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
	const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, const unsigned int & controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars, COMMON_NS::AbstractHdfProxy* proxy)
{
	setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(mostComplexPillarGeometry, kDirectionKind, isRightHanded, parameters, controlPoints, controlPointParameters, controlPointMaxCountPerPillar, pillarKind, definedPillars, proxy,
		0, "", "", "");
}

void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodes(
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, const unsigned int & controlPointMaxCountPerPillar, short * pillarKind, COMMON_NS::AbstractHdfProxy * proxy,
			const unsigned long & splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
			unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns)
{
	if (pillarKind == nullptr) {
		throw invalid_argument("The kind of the coordinate lines cannot be null.");
	}

	setGeometryAsParametricSplittedPillarNodes(kDirectionKind, isRightHanded, parameters, controlPoints, controlPointParameters, controlPointMaxCountPerPillar, 2, proxy,
		splitCoordinateLineCount, pillarOfCoordinateLine, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns);

	gsoap_resqml2_0_1::resqml2__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml2__IjkGridGeometry*>(getPointGeometry2_0_1(0));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	geom->PillarShape = mostComplexPillarGeometry;

	// XML Pillar defined
	resqml2__BooleanHdf5Array* xmlDefinedPillars = soap_new_resqml2__BooleanHdf5Array(gsoapProxy2_0_1->soap, 1);
	geom->PillarGeometryIsDefined = xmlDefinedPillars;
	xmlDefinedPillars->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlDefinedPillars->Values->HdfProxy = proxy->newResqmlReference();
	xmlDefinedPillars->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/PillarGeometryIsDefined";

	// HDF Pillar defined
	const unsigned int pillarCount = getPillarCount();
	unsigned char * definedPillars = new unsigned char[pillarCount];
	for (unsigned int i = 0; i < pillarCount; ++i) {
		definedPillars[i] = pillarKind[i] == -1 ? 0 : 1;
	}
	hsize_t * pillarGeometryIsDefinedCount = new hsize_t[2];
	pillarGeometryIsDefinedCount[0] = getJCellCount() + 1;
	pillarGeometryIsDefinedCount[1] = getICellCount() + 1;
	hdfProxy->writeArrayNd(gsoapProxy2_0_1->uuid, "PillarGeometryIsDefined", H5T_NATIVE_UCHAR, definedPillars, pillarGeometryIsDefinedCount, 2);
	delete [] pillarGeometryIsDefinedCount;
	delete [] definedPillars;

	// *********************************
	// Line kind hdf dataset
	// *********************************
	resqml2__Point3dParametricArray* xmlPoints = static_cast<resqml2__Point3dParametricArray*>(geom->Points);
	resqml2__ParametricLineArray* paramLines = static_cast<resqml2__ParametricLineArray*>(xmlPoints->ParametricLines);
	paramLines->KnotCount = controlPointMaxCountPerPillar;

	// XML Line kinds
	resqml2__IntegerHdf5Array* xmlLineKinds = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	paramLines->LineKindIndices = xmlLineKinds;
	xmlLineKinds->NullValue = -1;
	xmlLineKinds->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlLineKinds->Values->HdfProxy = proxy->newResqmlReference();
	xmlLineKinds->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/LineKindIndices";

	// HDF Line kinds
	hsize_t * lineKindCount = new hsize_t[2];
	lineKindCount[0] = getJCellCount() + 1;
	lineKindCount[1] = getICellCount() + 1;
	hdfProxy->writeArrayNd(gsoapProxy2_0_1->uuid, "LineKindIndices", H5T_NATIVE_SHORT, pillarKind, lineKindCount, 2);
	delete [] lineKindCount;
}

void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
	const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
	const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, const unsigned int & controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars, COMMON_NS::AbstractHdfProxy* proxy,
	const unsigned long & splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
	const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns)
{
	if (pillarKind.empty())
		throw invalid_argument("The kind of the coordinate lines cannot be null.");
	if (definedPillars.empty())
		throw invalid_argument("The defined pillars cannot be null.");

	setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(kDirectionKind, isRightHanded, parameters, controlPoints, controlPointParameters, controlPointMaxCountPerPillar, 2, proxy,
		splitCoordinateLineCount, pillarOfCoordinateLine, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns);

	gsoap_resqml2_0_1::resqml2__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml2__IjkGridGeometry*>(getPointGeometry2_0_1(0));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	geom->PillarShape = mostComplexPillarGeometry;

	// XML Pillar defined
	resqml2__BooleanHdf5Array* xmlDefinedPillars = soap_new_resqml2__BooleanHdf5Array(gsoapProxy2_0_1->soap, 1);
	geom->PillarGeometryIsDefined = xmlDefinedPillars;
	xmlDefinedPillars->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlDefinedPillars->Values->HdfProxy = proxy->newResqmlReference();
	xmlDefinedPillars->Values->PathInHdfFile = definedPillars;

	// *********************************
	// Line kind hdf dataset
	// *********************************
	resqml2__Point3dParametricArray* xmlPoints = static_cast<resqml2__Point3dParametricArray*>(geom->Points);
	resqml2__ParametricLineArray* paramLines = static_cast<resqml2__ParametricLineArray*>(xmlPoints->ParametricLines);
	paramLines->KnotCount = controlPointMaxCountPerPillar;

	// XML Line kinds
	resqml2__IntegerHdf5Array* xmlLineKinds = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	paramLines->LineKindIndices = xmlLineKinds;
	xmlLineKinds->NullValue = -1;
	xmlLineKinds->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlLineKinds->Values->HdfProxy = proxy->newResqmlReference();
	xmlLineKinds->Values->PathInHdfFile = pillarKind;
}

void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodes(
	const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
	double * parameters, double * controlPoints, double * controlPointParameters, const unsigned int & controlPointCountPerPillar, short pillarKind, COMMON_NS::AbstractHdfProxy * proxy,
	const unsigned long & splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
	unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns)
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

	const std::string hdfDatasetPrefix = "/RESQML/" + gsoapProxy2_0_1->uuid;
	setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(kDirectionKind, isRightHanded,
		hdfDatasetPrefix + "/PointParameters", hdfDatasetPrefix + "/ControlPoints", controlPointParameters != nullptr ? hdfDatasetPrefix + "/controlPointParameters" : "", controlPointCountPerPillar, pillarKind, proxy,
		splitCoordinateLineCount, hdfDatasetPrefix + "/PillarIndices",
		hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + CUMULATIVE_LENGTH_DS_NAME, hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + ELEMENTS_DS_NAME);

	if (splitCoordinateLineCount == 0) {
		// HDF
		hsize_t * numValues = new hsize_t[3];
		numValues[0] = getKCellCount() + 1;
		numValues[1] = getJCellCount() + 1;
		numValues[2] = getICellCount() + 1;

		hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid, "PointParameters", parameters, numValues, 3);
		delete[] numValues;
	}
	else {
		// PointParameters
		hsize_t * numValues = new hsize_t[2];
		numValues[0] = getKCellCount() + 1;
		numValues[1] = (getJCellCount() + 1) * (getICellCount() + 1) + splitCoordinateLineCount;

		hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid, "PointParameters", parameters, numValues, 2);
		delete[] numValues;

		// split coordinate lines
		numValues = new hsize_t[1];
		numValues[0] = splitCoordinateLineCount;
		hdfProxy->writeArrayNd(gsoapProxy2_0_1->uuid, "PillarIndices", H5T_NATIVE_UINT, pillarOfCoordinateLine, numValues, 1);
		delete[] numValues;

		hdfProxy->writeItemizedListOfList(gsoapProxy2_0_1->uuid, "ColumnsPerSplitCoordinateLine", H5T_NATIVE_UINT, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineCount, H5T_NATIVE_UINT, splitCoordinateLineColumns, splitCoordinateLineColumnCumulativeCount[splitCoordinateLineCount - 1]);
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
	hdfProxy->writeArrayNd(gsoapProxy2_0_1->uuid, "ControlPoints", H5T_NATIVE_DOUBLE, controlPoints, controlPointCount, 4);
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
		hdfProxy->writeArrayNd(gsoapProxy2_0_1->uuid, "controlPointParameters", H5T_NATIVE_DOUBLE, controlPointParameters, controlPointParamCount, 3);
		delete[] controlPointParamCount;
	}
}

void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
	const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
	const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, const unsigned int & controlPointCountPerPillar, short pillarKind, COMMON_NS::AbstractHdfProxy* proxy,
	const unsigned long & splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
	const std::string &  splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns)
{
	if (proxy == nullptr) {
		throw invalid_argument("The hdf proxy cannot be null.");
	}
	if (controlPointCountPerPillar < 1) {
		throw invalid_argument("The max count of control points per coordinate line of the ijk grid cannot be less than one.");
	}
	if (pillarKind < 0 || pillarKind > 5) {
		throw range_error("The kind of the coordinate lines is out of range.");
	}

	setHdfProxy(proxy);

	resqml2__IjkGridGeometry* geom = soap_new_resqml2__IjkGridGeometry(gsoapProxy2_0_1->soap, 1);
	geom->LocalCrs = localCrs->newResqmlReference();
	if (!isTruncated()) {
		getSpecializedGsoapProxy()->Geometry = geom;
	}
	else {
		getSpecializedTruncatedGsoapProxy()->Geometry = geom;
	}
	geom->GridIsRighthanded = isRightHanded;
	if (pillarKind > 1 || controlPointCountPerPillar > 2)
	{
		geom->PillarShape = resqml2__PillarShape__curved;
	}
	else if (pillarKind == 1)
	{
		geom->PillarShape = resqml2__PillarShape__straight;
	}
	else
	{
		geom->PillarShape = resqml2__PillarShape__vertical;
	}
	geom->KDirection = kDirectionKind;

	// XML Pillar defined
	resqml2__BooleanConstantArray* xmlDefinedPillars = soap_new_resqml2__BooleanConstantArray(gsoapProxy2_0_1->soap, 1);
	geom->PillarGeometryIsDefined = xmlDefinedPillars;
	xmlDefinedPillars->Value = true;
	xmlDefinedPillars->Count = getPillarCount();

	// XML parametric nodes
	resqml2__Point3dParametricArray* xmlPoints = soap_new_resqml2__Point3dParametricArray(gsoapProxy2_0_1->soap, 1);
	geom->Points = xmlPoints;
	resqml2__DoubleHdf5Array* xmlParameters = soap_new_resqml2__DoubleHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlPoints->Parameters = xmlParameters;
	xmlParameters->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlParameters->Values->HdfProxy = proxy->newResqmlReference();
	xmlParameters->Values->PathInHdfFile = parameters;

	if (splitCoordinateLineCount > 0) {
		// XML split coordinate lines
		geom->SplitCoordinateLines = soap_new_resqml2__ColumnLayerSplitCoordinateLines(gsoapProxy2_0_1->soap, 1);;
		geom->SplitCoordinateLines->Count = splitCoordinateLineCount;

		//XML
		resqml2__IntegerHdf5Array* pillarIndices = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
		geom->SplitCoordinateLines->PillarIndices = pillarIndices;
		pillarIndices->NullValue = getPillarCount();
		pillarIndices->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
		pillarIndices->Values->HdfProxy = proxy->newResqmlReference();
		pillarIndices->Values->PathInHdfFile = pillarOfCoordinateLine;

		//XML
		geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine = soap_new_resqml2__ResqmlJaggedArray(gsoapProxy2_0_1->soap, 1);
		// Cumulative
		resqml2__IntegerHdf5Array* cumulativeLength = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
		geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->CumulativeLength = cumulativeLength;
		cumulativeLength->NullValue = 0;
		cumulativeLength->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
		cumulativeLength->Values->HdfProxy = proxy->newResqmlReference();
		cumulativeLength->Values->PathInHdfFile = splitCoordinateLineColumnCumulativeCount;
		// Elements
		resqml2__IntegerHdf5Array* elements = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
		geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements = elements;
		elements->NullValue = getColumnCount();
		elements->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
		elements->Values->HdfProxy = proxy->newResqmlReference();
		elements->Values->PathInHdfFile = splitCoordinateLineColumns;
	}

	// *********************************
	// Parametric coordinate lines
	// *********************************
	resqml2__ParametricLineArray* paramLines = soap_new_resqml2__ParametricLineArray(gsoapProxy2_0_1->soap, 1);
	xmlPoints->ParametricLines = paramLines;
	paramLines->KnotCount = controlPointCountPerPillar;

	// XML Line kinds
	resqml2__IntegerConstantArray* xmlLineKinds = soap_new_resqml2__IntegerConstantArray(gsoapProxy2_0_1->soap, 1);
	paramLines->LineKindIndices = xmlLineKinds;
	xmlLineKinds->Value = pillarKind;
	xmlLineKinds->Count = getPillarCount();

	// XML control points
	resqml2__Point3dHdf5Array* xmlcontrolPoints = soap_new_resqml2__Point3dHdf5Array(gsoapProxy2_0_1->soap, 1);
	paramLines->ControlPoints = xmlcontrolPoints;
	xmlcontrolPoints->Coordinates = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlcontrolPoints->Coordinates->HdfProxy = proxy->newResqmlReference();
	xmlcontrolPoints->Coordinates->PathInHdfFile = controlPoints;

	// *********************************
	// Control point parameters are defined
	// *********************************
	if (!controlPointParameters.empty()) {
		// XML control point parameters
		resqml2__DoubleHdf5Array* xmlcontrolPointParams = soap_new_resqml2__DoubleHdf5Array(gsoapProxy2_0_1->soap, 1);
		paramLines->ControlPointParameters = xmlcontrolPointParams;
		xmlcontrolPointParams->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
		xmlcontrolPointParams->Values->HdfProxy = proxy->newResqmlReference();
		xmlcontrolPointParams->Values->PathInHdfFile = controlPointParameters;
	}
}

void IjkGridParametricRepresentation::loadPillarInformation(IjkGridParametricRepresentation::PillarInformation & pillarInfo) const
{
	pillarInfo.cleanMemory();

	gsoap_resqml2_0_1::resqml2__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	if (geom->Points->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dParametricArray)
	{
		throw invalid_argument("The geometry of the grid is not a parametric one.");
	}
	resqml2__Point3dParametricArray* parametricPoint3d = static_cast<resqml2__Point3dParametricArray*>(geom->Points);

	if (parametricPoint3d->ParametricLines->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineArray) {
		throw logic_error("Parametric lines should be of type resqml2__ParametricLineArray. Other type is not implemented yet.");
	}

	resqml2__ParametricLineArray* paramLineArray = static_cast<resqml2__ParametricLineArray*>(parametricPoint3d->ParametricLines);
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
	geometry::BSpline spline;
	for (unsigned int parametricLineIndex = 0; parametricLineIndex < pillarInfo.parametricLineCount; ++parametricLineIndex) {
		vector<geometry::BSpline> xyzSplines;
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

void IjkGridParametricRepresentation::getXyzPointsOfPatchFromParametricPoints(gsoap_resqml2_0_1::resqml2__Point3dParametricArray* parametricPoint3d, double * xyzPoints) const
{
	ULONG64 xyzPointCount = getXyzPointCountOfPatch(0);

	// parameters : ordered
	double * parameters = new double[xyzPointCount];
	if (parametricPoint3d->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
		hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__DoubleHdf5Array*>(parametricPoint3d->Parameters)->Values->PathInHdfFile, parameters);
	}
	else {
		throw logic_error("Non floating point coordinate line parameters are not implemented yet");
	}

	if (parametricPoint3d->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineArray) {
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
		throw logic_error("Parametric lines should be of type resqml2__ParametricLineArray. Other type is not implemented yet.");
	}

	delete [] parameters;
}

AbstractIjkGridRepresentation::geometryKind IjkGridParametricRepresentation::getGeometryKind() const
{
	return PARAMETRIC;
}

