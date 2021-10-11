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
#include "../eml2/AbstractLocal3dCrs.h"
#include "../resqml2/AbstractValuesProperty.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace RESQML2_0_1_NS;

const char* IjkGridExplicitRepresentation::XML_NS = "resqml20";

COMMON_NS::DataObjectReference IjkGridExplicitRepresentation::getHdfProxyDor() const
{
	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

EML2_NS::AbstractHdfProxy* IjkGridExplicitRepresentation::getPointDatasetPath(std::string & datasetPathInExternalFile, unsigned long & splitCoordinateLineCount) const
{
	resqml20__PointGeometry* pointGeom = getPointGeometry2_0_1(0);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array)
	{
		splitCoordinateLineCount = getSplitCoordinateLineCount();

		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__Point3dHdf5Array*>(pointGeom->Points)->Coordinates;
		datasetPathInExternalFile = dataset->PathInHdfFile;

		return getHdfProxyFromDataset(dataset);
	}
	else {
		throw invalid_argument("The geometry of the grid either does not exist or it is not an explicit one.");
	}
}

void IjkGridExplicitRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("An ijk grid has a maximum of one patch.");
	}

	resqml20__PointGeometry* pointGeom = getPointGeometry2_0_1(0);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array) {
		eml20__Hdf5Dataset const * xmlDataset = static_cast<resqml20__Point3dHdf5Array*>(pointGeom->Points)->Coordinates;
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(xmlDataset);
		hdfProxy->readArrayNdOfDoubleValues(xmlDataset->PathInHdfFile, xyzPoints);
	}
	else {
		throw logic_error("The geometry of the grid either does not exist or is not an explicit one.");
	}

	// Truncation
	if (isTruncated()) {
		resqml20__AbstractGridGeometry* truncatedGeom = static_cast<gsoap_resqml2_0_1::resqml20__AbstractGridGeometry*>(pointGeom);
		if (truncatedGeom->AdditionalGridPoints.size() == 1 && truncatedGeom->AdditionalGridPoints[0]->Attachment == resqml20__GridGeometryAttachment::nodes) {
			if (truncatedGeom->AdditionalGridPoints[0]->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array) {
				eml20__Hdf5Dataset const * xmlDataset = static_cast<resqml20__Point3dHdf5Array*>(truncatedGeom->AdditionalGridPoints[0]->Points)->Coordinates;
				EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(xmlDataset);
				xyzPoints += (getXyzPointCountOfPatch(patchIndex) - static_cast<gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation*>(gsoapProxy2_0_1)->TruncationCells->TruncationNodeCount)*3;
				hdfProxy->readArrayNdOfDoubleValues(xmlDataset->PathInHdfFile, xyzPoints);
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

void IjkGridExplicitRepresentation::setGeometryAsCoordinateLineNodesUsingExistingDatasets(
	gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
	const std::string & points, EML2_NS::AbstractHdfProxy* proxy,
	unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
	const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns,
	const std::string & definedPillars, EML2_NS::AbstractLocal3dCrs * localCrs)
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

	resqml20__IjkGridGeometry* geom = soap_new_resqml20__IjkGridGeometry(gsoapProxy2_0_1->soap);
	geom->LocalCrs = localCrs->newResqmlReference();
	if (!isTruncated()) {
		getSpecializedGsoapProxy2_0_1()->Geometry = geom;
	}
	else {
		getSpecializedTruncatedGsoapProxy2_0_1()->Geometry = geom;
	}
	geom->GridIsRighthanded = isRightHanded;
	geom->PillarShape = mostComplexPillarGeometry;
	geom->KDirection = kDirectionKind;

	getRepository()->addRelationship(this, proxy);
	// Pillar defined
	if (definedPillars.empty()) {
		resqml20__BooleanConstantArray* xmlDefinedPillars = soap_new_resqml20__BooleanConstantArray(gsoapProxy2_0_1->soap);
		geom->PillarGeometryIsDefined = xmlDefinedPillars;
		xmlDefinedPillars->Count = (getICellCount() + 1) * (getJCellCount() + 1);
		xmlDefinedPillars->Value = true;
	}
	else {
		resqml20__BooleanHdf5Array* xmlDefinedPillars = soap_new_resqml20__BooleanHdf5Array(gsoapProxy2_0_1->soap);
		geom->PillarGeometryIsDefined = xmlDefinedPillars;
		xmlDefinedPillars->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		xmlDefinedPillars->Values->HdfProxy = proxy->newResqmlReference();
		xmlDefinedPillars->Values->PathInHdfFile = definedPillars;
	}

	// XML coordinate lines
	resqml20__Point3dHdf5Array* xmlPoints = soap_new_resqml20__Point3dHdf5Array(gsoapProxy2_0_1->soap);
	geom->Points = xmlPoints;
	xmlPoints->Coordinates = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlPoints->Coordinates->HdfProxy = proxy->newResqmlReference();
	xmlPoints->Coordinates->PathInHdfFile = points;

	if (splitCoordinateLineCount > 0)
	{
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

	getRepository()->addRelationship(this, localCrs);
}


void IjkGridExplicitRepresentation::setGeometryAsCoordinateLineNodes(
	resqml20__PillarShape mostComplexPillarGeometry,
	resqml20__KDirection kDirectionKind,
	bool isRightHanded,
	double * points, EML2_NS::AbstractHdfProxy * proxy,
	unsigned long splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
	unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns,
	char * definedPillars, EML2_NS::AbstractLocal3dCrs * localCrs)
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
		splitCoordinateLineColumnCumulativeCount == nullptr ? "" : hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + EML2_NS::AbstractHdfProxy::CUMULATIVE_LENGTH_DS_NAME,
		splitCoordinateLineColumns == nullptr ? "" : hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + EML2_NS::AbstractHdfProxy::ELEMENTS_DS_NAME,
		definedPillars == nullptr ? "" : hdfDatasetPrefix + "/PillarGeometryIsDefined", localCrs);

	// Pillar defined
	if (definedPillars != nullptr) {
		hsize_t pillarGeometryIsDefinedCount[2] = { getJCellCount() + 1, getICellCount() + 1 };
		proxy->writeArrayNd(getHdfGroup(), "PillarGeometryIsDefined", H5T_NATIVE_CHAR, definedPillars, pillarGeometryIsDefinedCount, 2);
	}

	if (splitCoordinateLineCount == 0) {
		// Points
		hsize_t numValues[4] = { getKCellCount() + 1 + getKGapsCount(), getJCellCount() + 1, getICellCount() + 1, 3 };
		proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "Points", points, numValues, 4);
	}
	else {
		// Points
		hsize_t numValues[3] = { getKCellCount() + 1 + getKGapsCount(), (getJCellCount() + 1) * (getICellCount() + 1) + splitCoordinateLineCount, 3 };
		proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "Points", points, numValues, 3);
		
		// split coordinate lines
		hsize_t hdfSplitCoordinateLineCount = splitCoordinateLineCount;
		proxy->writeArrayNd(getHdfGroup(), "PillarIndices", H5T_NATIVE_UINT, pillarOfCoordinateLine, &hdfSplitCoordinateLineCount, 1);
		proxy->writeItemizedListOfList(getHdfGroup(), "ColumnsPerSplitCoordinateLine", H5T_NATIVE_UINT, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineCount, H5T_NATIVE_UINT, splitCoordinateLineColumns, splitCoordinateLineColumnCumulativeCount[splitCoordinateLineCount - 1]);
	}
}
