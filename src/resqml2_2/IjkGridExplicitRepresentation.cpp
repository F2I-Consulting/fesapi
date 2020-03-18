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

#include "IjkGridExplicitRepresentation.h"

#include <stdexcept>

#include <hdf5.h>

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../resqml2/AbstractLocal3dCrs.h"
#include "../resqml2/AbstractValuesProperty.h"
#include "../common/AbstractHdfProxy.h"

using namespace std;
using namespace gsoap_eml2_2;
using namespace RESQML2_2_NS;

COMMON_NS::DataObjectReference IjkGridExplicitRepresentation::getHdfProxyDor() const
{
	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_2(0));
}

ULONG64 IjkGridExplicitRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	resqml22__IjkGridGeometry* geom = static_cast<resqml22__IjkGridGeometry*>(getPointGeometry2_2(patchIndex));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}

	const unsigned int kNodeCount = getKCellCount() + 1;
	ULONG64 result = (getICellCount() + 1) * (getJCellCount() + 1) * kNodeCount;

	if (geom->ColumnLayerSplitCoordinateLines != nullptr) {
		result += geom->ColumnLayerSplitCoordinateLines->Count * kNodeCount;
	}
	if (geom->SplitNodePatch != nullptr) {
		result += geom->SplitNodePatch->Count;
	}

	if (isTruncated()) {
		result += static_cast<_resqml22__TruncatedIjkGridRepresentation*>(gsoapProxy2_2)->TruncationCellPatch->TruncationNodeCount;
	}

	return result;
}

COMMON_NS::AbstractHdfProxy* IjkGridExplicitRepresentation::getPointDatasetPath(std::string & datasetPathInExternalFile, unsigned long & splitCoordinateLineCount) const
{
	resqml22__PointGeometry* pointGeom = getPointGeometry2_2(0);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_eml2_2_resqml22__Point3dExternalArray)
	{
		splitCoordinateLineCount = getSplitCoordinateLineCount();

		auto dataset = static_cast<resqml22__Point3dExternalArray*>(pointGeom->Points)->Coordinates->ExternalFileProxy[0];
		datasetPathInExternalFile = dataset->PathInExternalFile;

		return getHdfProxyFromDataset(dataset);
	}
	else {
		throw invalid_argument("The geometry of the grid either does not exist or it is not an explicit one.");
	}
}

void IjkGridExplicitRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("An ijk grid has a maximum of one patch.");
	}

	resqml22__PointGeometry* pointGeom = getPointGeometry2_2(0);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_eml2_2_resqml22__Point3dExternalArray) {
		auto xmlDataset = static_cast<resqml22__Point3dExternalArray*>(pointGeom->Points)->Coordinates->ExternalFileProxy[0];
		COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(xmlDataset);
		hdfProxy->readArrayNdOfDoubleValues(xmlDataset->PathInExternalFile, xyzPoints);
	}
	else {
		throw invalid_argument("The geometry of the grid either does not exist or is not an explicit one.");
	}

	// Truncation
	if (isTruncated()) {
		resqml22__AbstractGridGeometry* truncatedGeom = static_cast<resqml22__AbstractGridGeometry*>(pointGeom);
		if (truncatedGeom->AdditionalGridPoints.size() == 1 && truncatedGeom->AdditionalGridPoints[0]->Attachment == resqml22__GridGeometryAttachment__nodes) {
			if (truncatedGeom->AdditionalGridPoints[0]->Points->soap_type() == SOAP_TYPE_gsoap_eml2_2_resqml22__Point3dExternalArray) {
				auto xmlDataset = static_cast<resqml22__Point3dExternalArray*>(truncatedGeom->AdditionalGridPoints[0]->Points)->Coordinates->ExternalFileProxy[0];
				COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(xmlDataset);
				xyzPoints += getXyzPointCountOfPatch(patchIndex) - static_cast<_resqml22__TruncatedIjkGridRepresentation*>(gsoapProxy2_2)->TruncationCellPatch->TruncationNodeCount;
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

void IjkGridExplicitRepresentation::setGeometryAsCoordinateLineNodesUsingExistingDatasets(
	gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
	const std::string & points, COMMON_NS::AbstractHdfProxy* proxy,
	unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
	const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns,
	const std::string & definedPillars, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (points.empty()) {
		throw invalid_argument("The points HDF dataset of the ijk grid cannot be empty.");
	}
	if (splitCoordinateLineCount != 0 && (pillarOfCoordinateLine.empty() || splitCoordinateLineColumnCumulativeCount.empty() || splitCoordinateLineColumns.empty())) {
		throw invalid_argument("The definition of the split coordinate lines HDF dataset is incomplete.");
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

	resqml22__IjkGridGeometry* geom = soap_new_resqml22__IjkGridGeometry(gsoapProxy2_2->soap);
	geom->LocalCrs = localCrs->newEml22Reference();
	if (!isTruncated()) {
		getSpecializedGsoapProxy2_2()->Geometry = geom;
	}
	else {
		getSpecializedTruncatedGsoapProxy2_2()->Geometry = geom;
	}
	geom->GridIsRighthanded = isRightHanded;
	geom->PillarShape = static_cast<resqml22__PillarShape>(mostComplexPillarGeometry);
	geom->KDirection = static_cast<resqml22__KDirection>(kDirectionKind);

	getRepository()->addRelationship(this, proxy);
	// Pillar defined
	if (definedPillars.empty()) {
		eml22__BooleanConstantArray* xmlDefinedPillars = soap_new_eml22__BooleanConstantArray(gsoapProxy2_2->soap);
		geom->PillarGeometryIsDefined = xmlDefinedPillars;
		xmlDefinedPillars->Count = (getICellCount() + 1) * (getJCellCount() + 1);
		xmlDefinedPillars->Value = true;
	}
	else {
		eml22__BooleanExternalArray* xmlDefinedPillars = soap_new_eml22__BooleanExternalArray(gsoapProxy2_2->soap);
		geom->PillarGeometryIsDefined = xmlDefinedPillars;
		xmlDefinedPillars->Values = soap_new_eml22__ExternalDataset(gsoapProxy2_2->soap);
		auto dsPart = soap_new_eml22__ExternalDatasetPart(gsoapProxy2_2->soap);
		dsPart->EpcExternalPartReference = proxy->newEml22Reference();
		dsPart->PathInExternalFile = definedPillars;
		xmlDefinedPillars->Values->ExternalFileProxy.push_back(dsPart);
	}

	// XML coordinate lines
	resqml22__Point3dExternalArray* xmlPoints = soap_new_resqml22__Point3dExternalArray(gsoapProxy2_2->soap);
	geom->Points = xmlPoints;
	xmlPoints->Coordinates = soap_new_eml22__ExternalDataset(gsoapProxy2_2->soap);
	auto dsPart = soap_new_eml22__ExternalDatasetPart(gsoapProxy2_2->soap);
	dsPart->EpcExternalPartReference = proxy->newEml22Reference();
	dsPart->PathInExternalFile = points;
	xmlPoints->Coordinates->ExternalFileProxy.push_back(dsPart);

	if (splitCoordinateLineCount > 0)
	{
		// XML split coordinate lines
		geom->ColumnLayerSplitCoordinateLines = soap_new_resqml22__ColumnLayerSplitCoordinateLines(gsoapProxy2_2->soap);;
		geom->ColumnLayerSplitCoordinateLines->Count = splitCoordinateLineCount;

		//XML
		eml22__IntegerExternalArray* pillarIndices = soap_new_eml22__IntegerExternalArray(gsoapProxy2_2->soap);
		geom->ColumnLayerSplitCoordinateLines->PillarIndices = pillarIndices;
		pillarIndices->NullValue = getPillarCount();
		pillarIndices->Values = soap_new_eml22__ExternalDataset(gsoapProxy2_2->soap);
		dsPart = soap_new_eml22__ExternalDatasetPart(gsoapProxy2_2->soap);
		dsPart->EpcExternalPartReference = proxy->newEml22Reference();
		dsPart->PathInExternalFile = pillarOfCoordinateLine;
		pillarIndices->Values->ExternalFileProxy.push_back(dsPart);

		//XML
		geom->ColumnLayerSplitCoordinateLines->ColumnsPerSplitCoordinateLine = soap_new_eml22__JaggedArray(gsoapProxy2_2->soap);
		// Cumulative
		eml22__IntegerExternalArray* cumulativeLength = soap_new_eml22__IntegerExternalArray(gsoapProxy2_2->soap);
		geom->ColumnLayerSplitCoordinateLines->ColumnsPerSplitCoordinateLine->CumulativeLength = cumulativeLength;
		cumulativeLength->NullValue = 0;
		cumulativeLength->Values = soap_new_eml22__ExternalDataset(gsoapProxy2_2->soap);
		dsPart = soap_new_eml22__ExternalDatasetPart(gsoapProxy2_2->soap);
		dsPart->EpcExternalPartReference = proxy->newEml22Reference();
		dsPart->PathInExternalFile = splitCoordinateLineColumnCumulativeCount;
		cumulativeLength->Values->ExternalFileProxy.push_back(dsPart);
		// Elements
		eml22__IntegerExternalArray* elements = soap_new_eml22__IntegerExternalArray(gsoapProxy2_2->soap);
		geom->ColumnLayerSplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements = elements;
		elements->NullValue = getColumnCount();
		elements->Values = soap_new_eml22__ExternalDataset(gsoapProxy2_2->soap);
		dsPart = soap_new_eml22__ExternalDatasetPart(gsoapProxy2_2->soap);
		dsPart->EpcExternalPartReference = proxy->newEml22Reference();
		dsPart->PathInExternalFile = splitCoordinateLineColumns;
		elements->Values->ExternalFileProxy.push_back(dsPart);
	}

	getRepository()->addRelationship(this, localCrs);
}


void IjkGridExplicitRepresentation::setGeometryAsCoordinateLineNodes(
	gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry,
	gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind,
	bool isRightHanded,
	double * points, COMMON_NS::AbstractHdfProxy * proxy,
	unsigned long splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
	unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns,
	char * definedPillars, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (points == nullptr) {
		throw invalid_argument("The points of the ijk grid cannot be null.");
	}
	if (splitCoordinateLineCount != 0 && (pillarOfCoordinateLine == nullptr || splitCoordinateLineColumnCumulativeCount == nullptr || splitCoordinateLineColumns == nullptr)) {
		throw invalid_argument("The definition of the split coordinate lines is incomplete.");
	}
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	const std::string hdfDatasetPrefix = getHdfGroup();
	setGeometryAsCoordinateLineNodesUsingExistingDatasets(mostComplexPillarGeometry, kDirectionKind, isRightHanded,
		hdfDatasetPrefix + "/Points", proxy,
		splitCoordinateLineCount, pillarOfCoordinateLine == nullptr ? "" : hdfDatasetPrefix + "/PillarIndices",
		splitCoordinateLineColumnCumulativeCount == nullptr ? "" : hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + CUMULATIVE_LENGTH_DS_NAME,
		splitCoordinateLineColumns == nullptr ? "" : hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + ELEMENTS_DS_NAME,
		definedPillars == nullptr ? "" : hdfDatasetPrefix + "/PillarGeometryIsDefined", localCrs);

	// Pillar defined
	if (definedPillars != nullptr) {
		hsize_t pillarGeometryIsDefinedCount[2] = { getJCellCount() + 1, getICellCount() + 1 };
		proxy->writeArrayNd(getHdfGroup(), "PillarGeometryIsDefined", H5T_NATIVE_CHAR, definedPillars, pillarGeometryIsDefinedCount, 2);
	}

	if (splitCoordinateLineCount == 0) {
		// Points
		hsize_t numValues[4] = { getKCellCount() + 1, getJCellCount() + 1, getICellCount() + 1, 3 };
		proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "Points", points, numValues, 4);
	}
	else {
		// Points
		hsize_t numValues[3] = { getKCellCount() + 1, (getJCellCount() + 1) * (getICellCount() + 1) + splitCoordinateLineCount, 3 };
		proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "Points", points, numValues, 3);
		
		// split coordinate lines
		hsize_t hdfSplitCoordinateLineCount = splitCoordinateLineCount;
		proxy->writeArrayNd(getHdfGroup(), "PillarIndices", H5T_NATIVE_UINT, pillarOfCoordinateLine, &hdfSplitCoordinateLineCount, 1);
		proxy->writeItemizedListOfList(getHdfGroup(), "ColumnsPerSplitCoordinateLine", H5T_NATIVE_UINT, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineCount, H5T_NATIVE_UINT, splitCoordinateLineColumns, splitCoordinateLineColumnCumulativeCount[splitCoordinateLineCount - 1]);
	}
}
