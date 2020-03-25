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
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace gsoap_eml2_3;
using namespace RESQML2_2_NS;

unsigned int IjkGridParametricRepresentation::getControlPointMaxCountPerPillar() const
{
	resqml22__PointGeometry* geom = getPointGeometry2_2(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml22__Point3dParametricArray* points = static_cast<resqml22__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__ParametricLineArray) {
		const ULONG64 result = static_cast<resqml22__ParametricLineArray*>(points->ParametricLines)->KnotCount;
		if (result > (std::numeric_limits<unsigned int>::max)())
			throw std::out_of_range("There are too many knot counts");
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
			auto dataset = static_cast<eml23__IntegerExternalArray*>(paramLineArray->LineKindIndices)->Values->ExternalFileProxy[0];
			EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			std::unique_ptr<short[]> pillarKind(new short[getPillarCount()]);
			hdfProxy->readArrayNdOfShortValues(dataset->PathInExternalFile, pillarKind.get());
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
			LONG64 result = static_cast<eml23__IntegerLatticeArray*>(paramLineArray->LineKindIndices)->StartValue;
			if (result > (std::numeric_limits<short>::max)()) {
				throw std::range_error("The constant parametric line kind is not a short one.");
			}
			return static_cast<short>(result);
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray) {
			LONG64 result = static_cast<eml23__IntegerConstantArray*>(paramLineArray->LineKindIndices)->Value;
			if (result > (std::numeric_limits<short>::max)()) {
				throw std::range_error("The constant parametric line kind is not a short one.");
			}
			return static_cast<short>(result);
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			auto dataset = static_cast<eml23__IntegerExternalArray*>(paramLineArray->LineKindIndices)->Values->ExternalFileProxy[0];
			EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			std::unique_ptr<short[]> pillarKind(new short[getPillarCount()]);
			hdfProxy->readArrayNdOfShortValues(dataset->PathInExternalFile, pillarKind.get());
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
			auto dataset = static_cast<eml23__IntegerExternalArray*>(paramLineArray->LineKindIndices)->Values->ExternalFileProxy[0];
			EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfShortValues(dataset->PathInExternalFile, pillarKind);
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray)
		{
			const LONG64 value = static_cast<eml23__IntegerConstantArray*>(paramLineArray->LineKindIndices)->Value;
			const ULONG64 lineKindCount = static_cast<eml23__IntegerConstantArray*>(paramLineArray->LineKindIndices)->Count;
			if( lineKindCount != getPillarCount() ) {
				throw invalid_argument("The parametric line kind count is inconsistent with the pillar count.");
			}
			for (ULONG64 i = 0; i < lineKindCount; ++i) {
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
	if (points->Parameters->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__DoubleExternalArray)
	{
		return COMMON_NS::DataObjectReference(static_cast<eml23__DoubleExternalArray*>(points->Parameters)->Values->ExternalFileProxy[0]->EpcExternalPartReference);
	}
	else
		throw std::logic_error("Not yet implemented");
}

ULONG64 IjkGridParametricRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	ULONG64 result = getXyzPointCountOfKInterface() * (getKCellCount() + 1);

	resqml22__IjkGridGeometry* geom = static_cast<resqml22__IjkGridGeometry*>(getPointGeometry2_2(patchIndex));
	if (geom->SplitNodePatch != nullptr) {
		result += geom->SplitNodePatch->Count;
	}

	if (isTruncated()) {
		result += static_cast<_resqml22__TruncatedIjkGridRepresentation*>(gsoapProxy2_3)->TruncationCellPatch->TruncationNodeCount;
	}

	return result;
}

void IjkGridParametricRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	getXyzPointsFromParametricPoints(xyzPoints);

	// Truncation
	if (isTruncated()) {
		resqml22__PointGeometry* geom = getPointGeometry2_2(0);
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this grid.");
		}

		resqml22__AbstractGridGeometry* truncatedGeom = static_cast<resqml22__AbstractGridGeometry*>(geom);
		if (truncatedGeom->AdditionalGridPoints.size() == 1 && truncatedGeom->AdditionalGridPoints[0]->Attachment == resqml22__GridGeometryAttachment__nodes) {
			if (truncatedGeom->AdditionalGridPoints[0]->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray)
			{
				auto xmlDataset = static_cast<resqml22__Point3dExternalArray*>(truncatedGeom->AdditionalGridPoints[0]->Points)->Coordinates->ExternalFileProxy[0];
				EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(xmlDataset);
				xyzPoints += getXyzPointCountOfPatch(patchIndex) - static_cast<_resqml22__TruncatedIjkGridRepresentation*>(gsoapProxy2_3)->TruncationCellPatch->TruncationNodeCount;
				hdfProxy->readArrayNdOfDoubleValues(xmlDataset->PathInExternalFile, xyzPoints);
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

void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodes(
	gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, bool isRightHanded,
	double * parameters, double * controlPoints, double * controlPointParameters, unsigned int controlPointMaxCountPerPillar, short * pillarKind, EML2_NS::AbstractHdfProxy * proxy,
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

	const std::string hdfDatasetPrefix = getHdfGroup();
	setGeometryAsParametricSplittedPillarNodesWithoutPillarKindUsingExistingDatasets(kDirectionKind, isRightHanded,
		hdfDatasetPrefix + "/PointParameters", hdfDatasetPrefix + "/ControlPoints", controlPointParameters != nullptr ? hdfDatasetPrefix + "/controlPointParameters" : "", controlPointMaxCountPerPillar, proxy,
		splitCoordinateLineCount, hdfDatasetPrefix + "/PillarIndices",
		hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + CUMULATIVE_LENGTH_DS_NAME, hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + ELEMENTS_DS_NAME, localCrs);

	writeGeometryOnHdf(parameters,
		controlPoints, controlPointParameters, controlPointMaxCountPerPillar,
		splitCoordinateLineCount, pillarOfCoordinateLine,
		splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns, proxy);

	resqml22__IjkGridGeometry* geom = static_cast<resqml22__IjkGridGeometry*>(getPointGeometry2_2(0));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	geom->PillarShape = static_cast<gsoap_eml2_3::resqml22__PillarShape>(mostComplexPillarGeometry);

	// XML Pillar defined
	eml23__BooleanExternalArray* xmlDefinedPillars = soap_new_eml23__BooleanExternalArray(gsoapProxy2_3->soap);
	geom->PillarGeometryIsDefined = xmlDefinedPillars;
	xmlDefinedPillars->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	auto dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = getHdfGroup() + "/PillarGeometryIsDefined";
	xmlDefinedPillars->Values->ExternalFileProxy.push_back(dsPart);

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
	xmlLineKinds->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = getHdfGroup() + "/LineKindIndices";
	xmlLineKinds->Values->ExternalFileProxy.push_back(dsPart);

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
	xmlDefinedPillars->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	auto dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = definedPillars;
	xmlDefinedPillars->Values->ExternalFileProxy.push_back(dsPart);

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
	xmlLineKinds->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = pillarKind;
	xmlLineKinds->Values->ExternalFileProxy.push_back(dsPart);
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
	eml23__DoubleExternalArray* xmlParameters = soap_new_eml23__DoubleExternalArray(gsoapProxy2_3->soap);
	xmlPoints->Parameters = xmlParameters;
	xmlParameters->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	auto dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = parameters;
	xmlParameters->Values->ExternalFileProxy.push_back(dsPart);

	if (splitCoordinateLineCount > 0) {
		// XML split coordinate lines
		geom->ColumnLayerSplitCoordinateLines = soap_new_resqml22__ColumnLayerSplitCoordinateLines(gsoapProxy2_3->soap);;
		geom->ColumnLayerSplitCoordinateLines->Count = splitCoordinateLineCount;

		//XML
		eml23__IntegerExternalArray* pillarIndices = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
		geom->ColumnLayerSplitCoordinateLines->PillarIndices = pillarIndices;
		pillarIndices->NullValue = getPillarCount();
		pillarIndices->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
		dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
		dsPart->EpcExternalPartReference = proxy->newEml23Reference();
		dsPart->PathInExternalFile = pillarOfCoordinateLine;
		pillarIndices->Values->ExternalFileProxy.push_back(dsPart);

		//XML
		geom->ColumnLayerSplitCoordinateLines->ColumnsPerSplitCoordinateLine = soap_new_eml23__JaggedArray(gsoapProxy2_3->soap);
		// Cumulative
		eml23__IntegerExternalArray* cumulativeLength = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
		geom->ColumnLayerSplitCoordinateLines->ColumnsPerSplitCoordinateLine->CumulativeLength = cumulativeLength;
		cumulativeLength->NullValue = 0;
		cumulativeLength->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
		dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
		dsPart->EpcExternalPartReference = proxy->newEml23Reference();
		dsPart->PathInExternalFile = splitCoordinateLineColumnCumulativeCount;
		cumulativeLength->Values->ExternalFileProxy.push_back(dsPart);
		// Elements
		eml23__IntegerExternalArray* elements = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
		geom->ColumnLayerSplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements = elements;
		elements->NullValue = getColumnCount();
		elements->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
		dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
		dsPart->EpcExternalPartReference = proxy->newEml23Reference();
		dsPart->PathInExternalFile = splitCoordinateLineColumns;
		elements->Values->ExternalFileProxy.push_back(dsPart);
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
	xmlcontrolPoints->Coordinates = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = controlPoints;
	xmlcontrolPoints->Coordinates->ExternalFileProxy.push_back(dsPart);

	// *********************************
	// Control point parameters are defined
	// *********************************
	if (!controlPointParameters.empty()) {
		// XML control point parameters
		eml23__DoubleExternalArray* xmlcontrolPointParams = soap_new_eml23__DoubleExternalArray(gsoapProxy2_3->soap);
		paramLines->ControlPointParameters = xmlcontrolPointParams;
		xmlcontrolPointParams->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
		dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
		dsPart->EpcExternalPartReference = proxy->newEml23Reference();
		dsPart->PathInExternalFile = controlPointParameters;
		xmlcontrolPointParams->Values->ExternalFileProxy.push_back(dsPart);
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
		geom->PillarShape = resqml22__PillarShape__curved;
	}
	else if (pillarKind == 1) {
		geom->PillarShape = resqml22__PillarShape__straight;
	}
	else {
		geom->PillarShape = resqml22__PillarShape__vertical;
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
	if (parametricPoint3d->Parameters->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__DoubleExternalArray) {
		auto xmlDataset = static_cast<eml23__DoubleExternalArray*>(parametricPoint3d->Parameters)->Values->ExternalFileProxy[0];
		datasetPathInExternalFile = xmlDataset->PathInExternalFile;
		return getHdfProxyFromDataset(xmlDataset);
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
			auto dataset = static_cast<resqml22__Point3dExternalArray*>(paramLineArray->ControlPoints)->Coordinates->ExternalFileProxy[0];
			datasetPathInExternalFile = dataset->PathInExternalFile;
			return getHdfProxyFromDataset(dataset);
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
		if (paramLineArray->ControlPointParameters->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__DoubleExternalArray)
		{
			auto dataset = static_cast<eml23__DoubleExternalArray*>(paramLineArray->ControlPointParameters)->Values->ExternalFileProxy[0];
			datasetPathInExternalFile = dataset->PathInExternalFile;
			return getHdfProxyFromDataset(dataset);
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
	if (points->Parameters->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__DoubleExternalArray)
	{
		auto dataset = static_cast<eml23__DoubleExternalArray*>(points->Parameters)->Values->ExternalFileProxy[0];
		datasetPathInExternalFile = dataset->PathInExternalFile;
		return getHdfProxyFromDataset(dataset);
	}
	else
		throw std::logic_error("Not implemented yet");
}
