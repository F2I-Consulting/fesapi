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

#include <limits>
#include <stdexcept>

#include <hdf5.h>

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../resqml2/AbstractLocal3dCrs.h"
#include "../resqml2/AbstractValuesProperty.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace gsoap_eml2_3;
using namespace RESQML2_2_NS;

const char* IjkGridParametricRepresentation::XML_NS = "resqml22";

unsigned int IjkGridParametricRepresentation::getControlPointMaxCountPerPillar() const
{
	resqml22__PointGeometry* geom = getPointGeometry2_2(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml22__Point3dParametricArray* points = static_cast<resqml22__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__ParametricLineArray) {
		const uint64_t result = static_cast<resqml22__ParametricLineArray*>(points->ParametricLines)->KnotCount;
		if (result > (std::numeric_limits<unsigned int>::max)())
			throw std::range_error("There are too many knot counts");
		return static_cast<unsigned int>(result);
	}

	throw std::logic_error("Not yet implemented");
}

bool IjkGridParametricRepresentation::hasControlPointParameters() const
{
	resqml22__PointGeometry* geom = getPointGeometry2_2(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml22__Point3dParametricArray* points = static_cast<resqml22__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__ParametricLineArray)
	{
		resqml22__ParametricLineArray* paramLineArray = static_cast<resqml22__ParametricLineArray*>(points->ParametricLines);
		return paramLineArray->ControlPointParameters != nullptr;
	}
	else
		throw std::logic_error("Not yet implemented");
}

bool IjkGridParametricRepresentation::isParametricLineKindConstant() const
{
	resqml22__PointGeometry* geom = getPointGeometry2_2(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml22__Point3dParametricArray* points = static_cast<resqml22__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__ParametricLineArray)
	{
		resqml22__ParametricLineArray* paramLineArray = static_cast<resqml22__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerLatticeArray)
		{
			if (static_cast<eml23__IntegerLatticeArray*>(paramLineArray->LineKindIndices)->Offset[0]->Count == 0)
				return true;
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray)
		{
			return true;
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray)
		{
			auto const* daPart = static_cast<eml23__IntegerExternalArray*>(paramLineArray->LineKindIndices)->Values->ExternalDataArrayPart[0];
			EML2_NS::AbstractHdfProxy * hdfProxy = getOrCreateHdfProxyFromDataArrayPart(daPart);
			if (getPillarCount() != hdfProxy->getElementCount(daPart->PathInExternalFile)) {
				throw std::logic_error("Size difference between values count in hdf and pillars count");
			}
			std::unique_ptr<short[]> pillarKind(new short[getPillarCount()]);
			hdfProxy->readArrayNdOfShortValues(daPart->PathInExternalFile, pillarKind.get());
			short firstPillarKind = pillarKind[0];
			size_t pillarIndex = 0;
			while (pillarIndex < getPillarCount()) {
				if (pillarKind[pillarIndex] != firstPillarKind) {
					return false;
				}
				++pillarIndex;
			}
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
	if (!isParametricLineKindConstant()) {
		throw invalid_argument("The parametric line kind is not constant.");
	}

	resqml22__PointGeometry* geom = getPointGeometry2_2(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml22__Point3dParametricArray* points = static_cast<resqml22__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__ParametricLineArray)
	{
		resqml22__ParametricLineArray* paramLineArray = static_cast<resqml22__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerLatticeArray) {
			int64_t result = static_cast<eml23__IntegerLatticeArray*>(paramLineArray->LineKindIndices)->StartValue;
			if (result > (std::numeric_limits<short>::max)()) {
				throw std::range_error("The constant parametric line kind is not a short one.");
			}
			return static_cast<short>(result);
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray) {
			int64_t result = static_cast<eml23__IntegerConstantArray*>(paramLineArray->LineKindIndices)->Value;
			if (result > (std::numeric_limits<short>::max)()) {
				throw std::range_error("The constant parametric line kind is not a short one.");
			}
			return static_cast<short>(result);
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			auto const* daPart = static_cast<eml23__IntegerExternalArray*>(paramLineArray->LineKindIndices)->Values->ExternalDataArrayPart[0];
			EML2_NS::AbstractHdfProxy * hdfProxy = getOrCreateHdfProxyFromDataArrayPart(daPart);
			std::unique_ptr<short[]> pillarKind(new short[getPillarCount()]);
			hdfProxy->readArrayNdOfShortValues(daPart->PathInExternalFile, pillarKind.get());
			return pillarKind[0];
		}
		else {
			throw std::logic_error("Not yet implemented");
		}
	}

	throw std::logic_error("This ijk grid should be a parametric one but does not look like a parametric one.");
}


void IjkGridParametricRepresentation::getRawParametricLineKind(short * pillarKind) const
{
	resqml22__PointGeometry* geom = getPointGeometry2_2(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml22__Point3dParametricArray* points = static_cast<resqml22__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__ParametricLineArray)
	{
		resqml22__ParametricLineArray* paramLineArray = static_cast<resqml22__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray)
		{
			auto const* daPart = static_cast<eml23__IntegerExternalArray*>(paramLineArray->LineKindIndices)->Values->ExternalDataArrayPart[0];
			EML2_NS::AbstractHdfProxy * hdfProxy = getOrCreateHdfProxyFromDataArrayPart(daPart);
			hdfProxy->readArrayNdOfShortValues(daPart->PathInExternalFile, pillarKind);
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray)
		{
			const int64_t value = static_cast<eml23__IntegerConstantArray*>(paramLineArray->LineKindIndices)->Value;
			const uint64_t lineKindCount = static_cast<eml23__IntegerConstantArray*>(paramLineArray->LineKindIndices)->Count;
			if( lineKindCount != getPillarCount() ) {
				throw invalid_argument("The parametric line kind count is inconsistent with the pillar count.");
			}
			for (uint64_t i = 0; i < lineKindCount; ++i) {
				pillarKind[i] = (short)value;
			}
		}
		else
			throw std::logic_error("Not yet implemented");
	}
	else
		throw std::logic_error("Not yet implemented");
}

COMMON_NS::DataObjectReference IjkGridParametricRepresentation::getHdfProxyDor() const
{
	resqml22__PointGeometry* geom = getPointGeometry2_2(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml22__Point3dParametricArray* points = static_cast<resqml22__Point3dParametricArray*>(geom->Points);
	if (points->Parameters->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray)
	{
		return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__FloatingPointExternalArray*>(points->Parameters)->Values->ExternalDataArrayPart[0]));
	}
	else
		throw std::logic_error("Not yet implemented");
}

void IjkGridParametricRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const
{
	getXyzPointsFromParametricPoints(xyzPoints);

	// Truncation
	if (isTruncated()) {
		resqml22__PointGeometry* geom = getPointGeometry2_2(0);
		if (geom == nullptr) {
			throw logic_error("There is no geometry on this grid.");
		}

		resqml22__AbstractGridGeometry* truncatedGeom = static_cast<resqml22__AbstractGridGeometry*>(geom);
		if (truncatedGeom->AdditionalGridPoints.size() == 1 && truncatedGeom->AdditionalGridPoints[0]->Attachment == resqml22__GridGeometryAttachment::nodes) {
			if (truncatedGeom->AdditionalGridPoints[0]->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray)
			{
				auto const* daPart = static_cast<resqml22__Point3dExternalArray*>(truncatedGeom->AdditionalGridPoints[0]->Points)->Coordinates->ExternalDataArrayPart[0];
				EML2_NS::AbstractHdfProxy * hdfProxy = getOrCreateHdfProxyFromDataArrayPart(daPart);
				xyzPoints += getXyzPointCountOfPatch(patchIndex) - static_cast<_resqml22__TruncatedIjkGridRepresentation*>(gsoapProxy2_3)->TruncationCellPatch->TruncationNodeCount;
				hdfProxy->readArrayNdOfDoubleValues(daPart->PathInExternalFile, xyzPoints);
			}
			else {
				throw logic_error("The additional grid points must be explicit ones for now. Parametric additional points are not supported yet for example.");
			}
		}
		else {
			throw logic_error("The truncated geometry must have one additional grid points construct (more than one is not implemented in fesapi yet although allowed by the standard). The attachment of this grid points must be set to node.");
		}
	}
}

void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodes(
	gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, bool isRightHanded,
	double const * parameters, double const * controlPoints, double const * controlPointParameters, unsigned int controlPointMaxCountPerPillar, short const * pillarKind, EML2_NS::AbstractHdfProxy * proxy,
	unsigned long splitCoordinateLineCount, unsigned int const * pillarOfCoordinateLine,
	unsigned int const * splitCoordinateLineColumnCumulativeCount, unsigned int const * splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs)
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

	writeGeometryOnHdf(parameters,
		controlPoints, controlPointParameters, controlPointMaxCountPerPillar,
		splitCoordinateLineCount, pillarOfCoordinateLine,
		splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns, proxy);

	const std::string hdfDatasetPrefix = getHdfGroup();
	setGeometryAsParametricSplittedPillarNodesWithoutPillarKindUsingExistingDatasets(kDirectionKind, isRightHanded,
		hdfDatasetPrefix + "/PointParameters", hdfDatasetPrefix + "/ControlPoints", controlPointParameters != nullptr ? hdfDatasetPrefix + "/controlPointParameters" : "", controlPointMaxCountPerPillar, proxy,
		splitCoordinateLineCount, hdfDatasetPrefix + "/PillarIndices",
		hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + EML2_NS::AbstractHdfProxy::CUMULATIVE_LENGTH_DS_NAME, hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + EML2_NS::AbstractHdfProxy::ELEMENTS_DS_NAME, localCrs);

	resqml22__IjkGridGeometry* geom = static_cast<resqml22__IjkGridGeometry*>(getPointGeometry2_2(0));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	geom->PillarShape = static_cast<gsoap_eml2_3::resqml22__PillarShape>(mostComplexPillarGeometry);

	// XML Pillar defined
	eml23__BooleanExternalArray* xmlDefinedPillars = soap_new_eml23__BooleanExternalArray(gsoapProxy2_3->soap);
	geom->PillarGeometryIsDefined = xmlDefinedPillars;
	xmlDefinedPillars->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlDefinedPillars->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/PillarGeometryIsDefined", getPillarCount(), proxy));

	// HDF Pillar defined
	getRepository()->addRelationship(this, proxy);
	const unsigned int pillarCount = getPillarCount();
	std::unique_ptr<unsigned char[]> definedPillars(new unsigned char[pillarCount]);
	for (unsigned int i = 0; i < pillarCount; ++i) {
		definedPillars[i] = pillarKind[i] == -1 ? 0 : 1;
	}
	hsize_t pillarGeometryIsDefinedCount[2] = { getJCellCount() + 1, getICellCount() + 1 };
	proxy->writeArrayNd(getHdfGroup(), "PillarGeometryIsDefined", H5T_NATIVE_UCHAR, definedPillars.get(), pillarGeometryIsDefinedCount, 2);

	// *********************************
	// Overwrite line kind hdf dataset
	// *********************************
	resqml22__Point3dParametricArray* xmlPoints = static_cast<resqml22__Point3dParametricArray*>(geom->Points);
	resqml22__ParametricLineArray* paramLines = static_cast<resqml22__ParametricLineArray*>(xmlPoints->ParametricLines);
	paramLines->KnotCount = controlPointMaxCountPerPillar;

	// XML Line kinds
	eml23__IntegerExternalArray* xmlLineKinds = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	paramLines->LineKindIndices = xmlLineKinds;
	xmlLineKinds->NullValue = -1;
	xmlLineKinds->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlLineKinds->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/LineKindIndices", getPillarCount(), proxy));

	// HDF Line kinds
	hsize_t lineKindCount[2] = { getJCellCount() + 1, getICellCount() + 1 };
	proxy->writeArrayNd(getHdfGroup(), "LineKindIndices", H5T_NATIVE_SHORT, pillarKind, lineKindCount, 2);
}

void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
	gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
	const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars, EML2_NS::AbstractHdfProxy* proxy,
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

	resqml22__IjkGridGeometry* geom = static_cast<resqml22__IjkGridGeometry*>(getPointGeometry2_2(0));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	geom->PillarShape = static_cast<resqml22__PillarShape>(mostComplexPillarGeometry);

	// XML Pillar defined
	eml23__BooleanExternalArray* xmlDefinedPillars = soap_new_eml23__BooleanExternalArray(gsoapProxy2_3->soap);
	geom->PillarGeometryIsDefined = xmlDefinedPillars;
	xmlDefinedPillars->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlDefinedPillars->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(definedPillars, getPillarCount(), proxy));

	// *********************************
	// Line kind hdf dataset
	// *********************************
	resqml22__Point3dParametricArray* xmlPoints = static_cast<resqml22__Point3dParametricArray*>(geom->Points);
	resqml22__ParametricLineArray* paramLines = static_cast<resqml22__ParametricLineArray*>(xmlPoints->ParametricLines);
	paramLines->KnotCount = controlPointMaxCountPerPillar;

	// XML Line kinds
	eml23__IntegerExternalArray* xmlLineKinds = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	paramLines->LineKindIndices = xmlLineKinds;
	xmlLineKinds->NullValue = -1;
	xmlLineKinds->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlLineKinds->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(pillarKind, getPillarCount(), proxy));
}

void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodesWithoutPillarKindUsingExistingDatasets(
	gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
	const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointCountPerPillar, EML2_NS::AbstractHdfProxy* proxy,
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

	resqml22__IjkGridGeometry* geom = soap_new_resqml22__IjkGridGeometry(gsoapProxy2_3->soap);
	geom->LocalCrs = localCrs->newEml23Reference();
	if (!isTruncated()) {
		getSpecializedGsoapProxy2_2()->Geometry = geom;
	}
	else {
		getSpecializedTruncatedGsoapProxy2_2()->Geometry = geom;
	}
	geom->GridIsRighthanded = isRightHanded;
	geom->KDirection = static_cast<resqml22__KDirection>(kDirectionKind);

	getRepository()->addRelationship(this, proxy);
	// XML parametric nodes
	resqml22__Point3dParametricArray* xmlPoints = soap_new_resqml22__Point3dParametricArray(gsoapProxy2_3->soap);
	geom->Points = xmlPoints;
	eml23__FloatingPointExternalArray* xmlParameters = soap_new_eml23__FloatingPointExternalArray(gsoapProxy2_3->soap);
	xmlPoints->Parameters = xmlParameters;
	xmlParameters->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlParameters->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(parameters, proxy->getElementCount(parameters), proxy));

	if (splitCoordinateLineCount > 0) {
		// XML split coordinate lines
		geom->ColumnLayerSplitCoordinateLines = soap_new_resqml22__ColumnLayerSplitCoordinateLines(gsoapProxy2_3->soap);;
		geom->ColumnLayerSplitCoordinateLines->Count = splitCoordinateLineCount;

		//XML
		eml23__IntegerExternalArray* pillarIndices = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
		geom->ColumnLayerSplitCoordinateLines->PillarIndices = pillarIndices;
		pillarIndices->NullValue = getPillarCount();
		pillarIndices->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
		pillarIndices->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(pillarOfCoordinateLine, proxy->getElementCount(pillarOfCoordinateLine), proxy));

		//XML
		geom->ColumnLayerSplitCoordinateLines->ColumnsPerSplitCoordinateLine = soap_new_eml23__JaggedArray(gsoapProxy2_3->soap);
		// Cumulative
		eml23__IntegerExternalArray* cumulativeLength = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
		geom->ColumnLayerSplitCoordinateLines->ColumnsPerSplitCoordinateLine->CumulativeLength = cumulativeLength;
		cumulativeLength->NullValue = 0;
		cumulativeLength->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
		cumulativeLength->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(splitCoordinateLineColumnCumulativeCount, proxy->getElementCount(splitCoordinateLineColumnCumulativeCount), proxy));
		// Elements
		eml23__IntegerExternalArray* elements = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
		geom->ColumnLayerSplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements = elements;
		elements->NullValue = getColumnCount();
		elements->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
		elements->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(splitCoordinateLineColumns, proxy->getElementCount(splitCoordinateLineColumns), proxy));
	}

	// *********************************
	// Parametric coordinate lines
	// *********************************
	resqml22__ParametricLineArray* paramLines = soap_new_resqml22__ParametricLineArray(gsoapProxy2_3->soap);
	xmlPoints->ParametricLines = paramLines;
	paramLines->KnotCount = controlPointCountPerPillar;

	// XML control points
	resqml22__Point3dExternalArray* xmlcontrolPoints = soap_new_resqml22__Point3dExternalArray(gsoapProxy2_3->soap);
	paramLines->ControlPoints = xmlcontrolPoints;
	xmlcontrolPoints->Coordinates = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlcontrolPoints->Coordinates->ExternalDataArrayPart.push_back(createExternalDataArrayPart(controlPoints, proxy->getElementCount(controlPoints), proxy));

	// *********************************
	// Control point parameters are defined
	// *********************************
	if (!controlPointParameters.empty()) {
		// XML control point parameters
		eml23__FloatingPointExternalArray* xmlcontrolPointParams = soap_new_eml23__FloatingPointExternalArray(gsoapProxy2_3->soap);
		paramLines->ControlPointParameters = xmlcontrolPointParams;
		xmlcontrolPointParams->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
		xmlcontrolPointParams->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(controlPointParameters, proxy->getElementCount(controlPointParameters), proxy));
	}

	getRepository()->addRelationship(this, localCrs);
}


void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
	gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
	const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointCountPerPillar, short pillarKind, EML2_NS::AbstractHdfProxy* proxy,
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

	resqml22__IjkGridGeometry* geom = isTruncated() ? getSpecializedTruncatedGsoapProxy2_2()->Geometry : getSpecializedGsoapProxy2_2()->Geometry;
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}

	if (pillarKind > 1 || controlPointCountPerPillar > 2) {
		geom->PillarShape = resqml22__PillarShape::curved;
	}
	else if (pillarKind == 1) {
		geom->PillarShape = resqml22__PillarShape::straight;
	}
	else {
		geom->PillarShape = resqml22__PillarShape::vertical;
	}

	// XML Pillar defined
	eml23__BooleanConstantArray* xmlDefinedPillars = soap_new_eml23__BooleanConstantArray(gsoapProxy2_3->soap);
	geom->PillarGeometryIsDefined = xmlDefinedPillars;
	xmlDefinedPillars->Value = true;
	xmlDefinedPillars->Count = getPillarCount();

	resqml22__Point3dParametricArray* xmlPoints = static_cast<resqml22__Point3dParametricArray*>(geom->Points);
	resqml22__ParametricLineArray* paramLines = static_cast<resqml22__ParametricLineArray*>(xmlPoints->ParametricLines);

	// XML Line kinds
	eml23__IntegerConstantArray* xmlLineKinds = soap_new_eml23__IntegerConstantArray(gsoapProxy2_3->soap);
	paramLines->LineKindIndices = xmlLineKinds;
	xmlLineKinds->Value = pillarKind;
	xmlLineKinds->Count = getPillarCount();
}

EML2_NS::AbstractHdfProxy* IjkGridParametricRepresentation::getParameterDatasetPath(std::string & datasetPathInExternalFile) const
{
	resqml22__PointGeometry* geom = getPointGeometry2_2(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml22__Point3dParametricArray* parametricPoint3d = static_cast<resqml22__Point3dParametricArray*>(geom->Points);
	if (parametricPoint3d->Parameters->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray) {
		auto const* daPart = static_cast<eml23__FloatingPointExternalArray*>(parametricPoint3d->Parameters)->Values->ExternalDataArrayPart[0];
		datasetPathInExternalFile = daPart->PathInExternalFile;
		return getOrCreateHdfProxyFromDataArrayPart(daPart);
	}
	else {
		throw logic_error("Non floating point coordinate line parameters are not implemented yet");
	}
}

EML2_NS::AbstractHdfProxy* IjkGridParametricRepresentation::getControlPointDatasetPath(std::string & datasetPathInExternalFile) const
{
	resqml22__PointGeometry* geom = getPointGeometry2_2(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml22__Point3dParametricArray* points = static_cast<resqml22__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__ParametricLineArray) {
		resqml22__ParametricLineArray* paramLineArray = static_cast<resqml22__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->ControlPoints->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray) {
			auto const* daPart = static_cast<resqml22__Point3dExternalArray*>(paramLineArray->ControlPoints)->Coordinates->ExternalDataArrayPart[0];
			datasetPathInExternalFile = daPart->PathInExternalFile;
			return getOrCreateHdfProxyFromDataArrayPart(daPart);
		}
		else
			throw std::logic_error("Not implemented yet");
	}
	else {
		throw std::logic_error("Not implemented yet");
	}
}

EML2_NS::AbstractHdfProxy* IjkGridParametricRepresentation::getControlPointParametersDatasetPath(std::string & datasetPathInExternalFile) const
{
	resqml22__PointGeometry* geom = getPointGeometry2_2(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml22__Point3dParametricArray* points = static_cast<resqml22__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__ParametricLineArray)
	{
		resqml22__ParametricLineArray* paramLineArray = static_cast<resqml22__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->ControlPointParameters == nullptr)
			throw invalid_argument("The grid does not contain any control point parameters.");
		if (paramLineArray->ControlPointParameters->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray)
		{
			auto const* daPart = static_cast<eml23__FloatingPointExternalArray*>(paramLineArray->ControlPointParameters)->Values->ExternalDataArrayPart[0];
			datasetPathInExternalFile = daPart->PathInExternalFile;
			return getOrCreateHdfProxyFromDataArrayPart(daPart);
		}
		else
			throw std::logic_error("Not implemented yet");
	}
	else
		throw std::logic_error("Not implemented yet");
}

EML2_NS::AbstractHdfProxy* IjkGridParametricRepresentation::getParametersOfNodesDatasetPath(std::string & datasetPathInExternalFile) const
{
	resqml22__PointGeometry* geom = getPointGeometry2_2(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml22__Point3dParametricArray* points = static_cast<resqml22__Point3dParametricArray*>(geom->Points);
	if (points->Parameters->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray)
	{
		auto const* daPart = static_cast<eml23__FloatingPointExternalArray*>(points->Parameters)->Values->ExternalDataArrayPart[0];
		datasetPathInExternalFile = daPart->PathInExternalFile;
		return getOrCreateHdfProxyFromDataArrayPart(daPart);
	}
	else
		throw std::logic_error("Not implemented yet");
}
