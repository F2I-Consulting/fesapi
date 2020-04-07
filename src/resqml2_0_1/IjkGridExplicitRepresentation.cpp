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
using namespace gsoap_resqml2_0_1;
using namespace RESQML2_0_1_NS;

IjkGridExplicitRepresentation::IjkGridExplicitRepresentation(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount,
	bool withTruncatedPillars) :
	AbstractIjkGridRepresentation(repo, guid, title, iCount, jCount, kCount, withTruncatedPillars)
{
}

IjkGridExplicitRepresentation::IjkGridExplicitRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount,
	bool withTruncatedPillars) :
	AbstractIjkGridRepresentation(interp, guid, title, iCount, jCount, kCount, withTruncatedPillars)
{
}

gsoap_resqml2_0_1::eml20__DataObjectReference* IjkGridExplicitRepresentation::getHdfProxyDor() const
{
	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

ULONG64 IjkGridExplicitRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	gsoap_resqml2_0_1::resqml20__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml20__IjkGridGeometry*>(getPointGeometry2_0_1(patchIndex));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}

	const unsigned int kNodeCount = getKCellCount() + 1;
	ULONG64 result = (getICellCount() + 1) * (getJCellCount() + 1) * kNodeCount;

	if (geom->SplitCoordinateLines != nullptr) {
		result += geom->SplitCoordinateLines->Count * kNodeCount;
	}
	if (geom->SplitNodes != nullptr) {
		result += geom->SplitNodes->Count;
	}

	if (isTruncated()) {
		result += static_cast<gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation*>(gsoapProxy2_0_1)->TruncationCells->TruncationNodeCount;
	}

	return result;
}

void IjkGridExplicitRepresentation::getXyzPointsOfKInterfaceSequenceOfPatch(const unsigned int & kInterfaceStart, const unsigned int & kInterfaceEnd, const unsigned int & patchIndex, double * xyzPoints)
{
	if (kInterfaceStart > getKCellCount() || kInterfaceEnd > getKCellCount())
		throw range_error("kInterfaceStart and/or kInterfaceEnd is/are out of boundaries.");
	if (kInterfaceStart > kInterfaceEnd)
		throw range_error("kInterfaceStart > kInterfaceEnd");

	if (patchIndex >= getPatchCount())
		throw range_error("An ijk grid has a maximum of one patch.");

	if (xyzPoints == nullptr)
		throw invalid_argument("xyzPoints must be allocated.");

	resqml20__PointGeometry* pointGeom = getPointGeometry2_0_1(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array)
	{
		unsigned long splitCoordinateLineCount = getSplitCoordinateLineCount();

		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__Point3dHdf5Array*>(pointGeom->Points)->Coordinates;
		COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		if (splitCoordinateLineCount == 0)
		{
			unsigned long long* valueCountPerDimension = new unsigned long long[4];
			valueCountPerDimension[0] = kInterfaceEnd - kInterfaceStart + 1;
			valueCountPerDimension[1] = getJCellCount() + 1;
			valueCountPerDimension[2] = getICellCount() + 1;
			valueCountPerDimension[3] = 3;
			unsigned long long* offsetPerDimension = new unsigned long long[4];
			offsetPerDimension[0] = kInterfaceStart;
			offsetPerDimension[1] = 0;
			offsetPerDimension[2] = 0;
			offsetPerDimension[3] = 0;

			hdfProxy->readArrayNdOfDoubleValues(
				dataset->PathInHdfFile,
				xyzPoints,
				valueCountPerDimension,
				offsetPerDimension,
				4);
			delete[] valueCountPerDimension;
			delete[] offsetPerDimension;
		}
		else
		{
			unsigned long long* valueCountPerDimension = new unsigned long long[3];
			valueCountPerDimension[0] = kInterfaceEnd - kInterfaceStart + 1;
			valueCountPerDimension[1] = (getJCellCount() + 1) * (getICellCount() + 1) + splitCoordinateLineCount;
			valueCountPerDimension[2] = 3;
			unsigned long long* offsetPerDimension = new unsigned long long[3];
			offsetPerDimension[0] = kInterfaceStart;
			offsetPerDimension[1] = 0;
			offsetPerDimension[2] = 0;

			hdfProxy->readArrayNdOfDoubleValues(
				dataset->PathInHdfFile,
				xyzPoints,
				valueCountPerDimension,
				offsetPerDimension,
				3);

			delete[] valueCountPerDimension;
			delete[] offsetPerDimension;
		}
	}
	else {
		throw invalid_argument("The geometry of the grid either does not exist or it is not an explicit one.");
	}

	// Truncation
	if (isTruncated()) {
		throw invalid_argument("Getting all the XYZ points of a particular K interface is not supported yet for truncated grids.");
	}
}

void IjkGridExplicitRepresentation::getXyzPointsOfBlockOfPatch(const unsigned int & patchIndex, double * xyzPoints)
{
	if (blockInformation == nullptr)
		throw invalid_argument("The block information must have been loaded first.");

	if (patchIndex >= getPatchCount())
		throw range_error("An ijk grid has a maximum of one patch.");

	if (xyzPoints == nullptr)
		throw invalid_argument("xyzPoints must be allocated.");

	resqml20__PointGeometry* pointGeom = getPointGeometry2_0_1(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array)
	{
		unsigned long splitCoordinateLineCount = getSplitCoordinateLineCount();

		eml20__Hdf5Dataset const * xmlDataset = static_cast<resqml20__Point3dHdf5Array*>(pointGeom->Points)->Coordinates;
		COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(xmlDataset);
		if (splitCoordinateLineCount == 0)
		{
			unsigned long long* valueCountPerDimension = new unsigned long long[4];
			valueCountPerDimension[0] = blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart + 1;
			valueCountPerDimension[1] = blockInformation->jInterfaceEnd - blockInformation->jInterfaceStart + 1;
			valueCountPerDimension[2] = blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1;
			valueCountPerDimension[3] = 3;
			unsigned long long* offsetPerDimension = new unsigned long long[4];
			offsetPerDimension[0] = blockInformation->kInterfaceStart;
			offsetPerDimension[1] = blockInformation->jInterfaceStart;
			offsetPerDimension[2] = blockInformation->iInterfaceStart;
			offsetPerDimension[3] = 0;

			hdfProxy->readArrayNdOfDoubleValues(
				xmlDataset->PathInHdfFile,
				xyzPoints,
				valueCountPerDimension,
				offsetPerDimension,
				4);
			delete[] valueCountPerDimension;
			delete[] offsetPerDimension;
		}
		else
		{
			unsigned long long* blockCountPerDimension = new unsigned long long[3];
			blockCountPerDimension[0] = 1;
			blockCountPerDimension[1] = blockInformation->jInterfaceEnd - blockInformation->jInterfaceStart + 1;
			blockCountPerDimension[2] = 1;
			unsigned long long* offsetPerDimension = new unsigned long long[3];
			offsetPerDimension[0] = blockInformation->kInterfaceStart;
			offsetPerDimension[1] = blockInformation->jInterfaceStart * (getICellCount() + 1) + blockInformation->iInterfaceStart;
			offsetPerDimension[2] = 0;
			unsigned long long* strideInEachDimension = new unsigned long long[3];
			strideInEachDimension[0] = 1;
			strideInEachDimension[1] = (blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1) + ((getICellCount() + 1) - (blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1));
			strideInEachDimension[2] = 1;
			unsigned long long* blockSizeInEachDimension = new unsigned long long[3];
			blockSizeInEachDimension[0] = blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart + 1;
			blockSizeInEachDimension[1] = blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1;
			blockSizeInEachDimension[2] = 3;
		
			hid_t dataset, filespace;
			hdfProxy->selectArrayNdOfValues(
				xmlDataset->PathInHdfFile,
				blockCountPerDimension,
				offsetPerDimension,
				strideInEachDimension,
				blockSizeInEachDimension,
				3,
				true,
				dataset,
				filespace);

			unsigned long long slab_size = 1;
			for (size_t h = 0; h < 3; ++h) {
				slab_size *= blockSizeInEachDimension[h];
			}
			for (size_t h = 0; h < 3; ++h) {
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
									blockCountPerDimension[2] = 1;
									offsetPerDimension[0] = blockInformation->kInterfaceStart;
									offsetPerDimension[1] = splitCoordinateLineHdfIndex;
									offsetPerDimension[2] = 0;
									strideInEachDimension[0] = 1;
									strideInEachDimension[1] = 1;
									strideInEachDimension[2] = 1;
									blockSizeInEachDimension[0] = blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart + 1;
									blockSizeInEachDimension[1] = 1;
									blockSizeInEachDimension[2] = 3;

									hdfProxy->selectArrayNdOfValues(
										xmlDataset->PathInHdfFile,
										blockCountPerDimension,
										offsetPerDimension,
										strideInEachDimension,
										blockSizeInEachDimension,
										3,
										false,
										dataset,
										filespace);

									slab_size += (blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart + 1) * 3;

									break; // in order to be sure not adding twice a same coordinate line if it is adjacent to several columns within the bloc
								}
							}
						}
					}
				}
			}

			// reading values corresponding to the whole selected region (non splitted and splitted part)
			hdfProxy->readArrayNdOfDoubleValues(dataset, filespace,
				xyzPoints, slab_size);

			delete[] blockCountPerDimension;
			delete[] offsetPerDimension;
			delete[] strideInEachDimension;
			delete[] blockSizeInEachDimension;
		}
	}
	else {
		throw invalid_argument("The geometry of the grid either does not exist or it is not an explicit one.");
	}

	// Truncation
	if (isTruncated()) {
		throw invalid_argument("Getting all the XYZ points of a particular K interface is not supported yet for truncated grids.");
	}
}

void IjkGridExplicitRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("An ijk grid has a maximum of one patch.");

	resqml20__PointGeometry* pointGeom = getPointGeometry2_0_1(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array) {
		eml20__Hdf5Dataset const * xmlDataset = static_cast<resqml20__Point3dHdf5Array*>(pointGeom->Points)->Coordinates;
		COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(xmlDataset);
		hdfProxy->readArrayNdOfDoubleValues(xmlDataset->PathInHdfFile, xyzPoints);
	}
	else {
		throw invalid_argument("The geometry of the grid either does not exist or is not an explicit one.");
	}

	// Truncation
	if (isTruncated()) {
		resqml20__AbstractGridGeometry* truncatedGeom = static_cast<gsoap_resqml2_0_1::resqml20__AbstractGridGeometry*>(pointGeom);
		if (truncatedGeom->AdditionalGridPoints.size() == 1 && truncatedGeom->AdditionalGridPoints[0]->Attachment == resqml20__GridGeometryAttachment__nodes) {
			if (truncatedGeom->AdditionalGridPoints[0]->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array) {
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

void IjkGridExplicitRepresentation::setGeometryAsCoordinateLineNodesUsingExistingDatasets(
	gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
	const std::string & points, COMMON_NS::AbstractHdfProxy* proxy,
	const unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
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

	resqml20__IjkGridGeometry* geom = soap_new_resqml20__IjkGridGeometry(gsoapProxy2_0_1->soap);
	geom->LocalCrs = localCrs->newResqmlReference();
	if (!isTruncated()) {
		getSpecializedGsoapProxy()->Geometry = geom;
	}
	else {
		getSpecializedTruncatedGsoapProxy()->Geometry = geom;
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

	const std::string hdfDatasetPrefix = "/RESQML/" + gsoapProxy2_0_1->uuid;
	setGeometryAsCoordinateLineNodesUsingExistingDatasets(mostComplexPillarGeometry, kDirectionKind, isRightHanded,
		hdfDatasetPrefix + "/Points", proxy,
		splitCoordinateLineCount, pillarOfCoordinateLine == nullptr ? "" : hdfDatasetPrefix + "/PillarIndices",
		splitCoordinateLineColumnCumulativeCount == nullptr ? "" : hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + CUMULATIVE_LENGTH_DS_NAME, splitCoordinateLineColumns == nullptr ? "" : hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + ELEMENTS_DS_NAME,
		definedPillars == nullptr ? "" : hdfDatasetPrefix + "/PillarGeometryIsDefined", localCrs);

	// Pillar defined
	if (definedPillars != nullptr) {
		hsize_t * pillarGeometryIsDefinedCount = new hsize_t[2];
		pillarGeometryIsDefinedCount[0] = getJCellCount() + 1;
		pillarGeometryIsDefinedCount[1] = getICellCount() + 1;
		proxy->writeArrayNd(gsoapProxy2_0_1->uuid, "PillarGeometryIsDefined", H5T_NATIVE_CHAR, definedPillars, pillarGeometryIsDefinedCount, 2);
	}

	if (splitCoordinateLineCount == 0)
	{
		// Points
		hsize_t * numValues = new hsize_t[4];
		numValues[0] = getKCellCount() + 1;
		numValues[1] = getJCellCount() + 1;
		numValues[2] = getICellCount() + 1;
		numValues[3] = 3; // 3 for X, Y and Z	
		proxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid, "Points", points, numValues, 4);
		delete [] numValues;
	}
	else
	{
		// Points
		hsize_t * numValues = new hsize_t[3];
		numValues[0] = getKCellCount() + 1;
		numValues[1] = (getJCellCount() + 1) * (getICellCount() + 1) + splitCoordinateLineCount;
		numValues[2] = 3; // 3 for X, Y and Z
		proxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid, "Points", points, numValues, 3);
		delete [] numValues;
		
		// split coordinate lines
		numValues = new hsize_t[1];
		numValues[0] = splitCoordinateLineCount;
		proxy->writeArrayNd(gsoapProxy2_0_1->uuid, "PillarIndices", H5T_NATIVE_UINT, pillarOfCoordinateLine, numValues, 1);
		delete [] numValues;
		proxy->writeItemizedListOfList(gsoapProxy2_0_1->uuid, "ColumnsPerSplitCoordinateLine", H5T_NATIVE_UINT, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineCount, H5T_NATIVE_UINT, splitCoordinateLineColumns, splitCoordinateLineColumnCumulativeCount[splitCoordinateLineCount - 1]);
	}
}

AbstractIjkGridRepresentation::geometryKind IjkGridExplicitRepresentation::getGeometryKind() const
{
	return EXPLICIT;
}

bool IjkGridExplicitRepresentation::isNodeGeometryCompressed() const {
	resqml20__PointGeometry* pointGeom = getPointGeometry2_0_1(0);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array) {
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__Point3dHdf5Array*>(pointGeom->Points)->Coordinates;
		COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		return hdfProxy->isCompressed(dataset->PathInHdfFile);
	}
	else {
		throw invalid_argument("The geometry of the grid either does not exist or is not an explicit one.");
	}
}
