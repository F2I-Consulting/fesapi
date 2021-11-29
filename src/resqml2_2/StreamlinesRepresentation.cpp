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
#include "StreamlinesRepresentation.h"

#include <hdf5.h>

#include "../eml2/AbstractHdfProxy.h"

#include "../resqml2/AbstractGridRepresentation.h"
#include "../eml2/AbstractLocal3dCrs.h"
#include "../resqml2/GenericFeatureInterpretation.h"
#include "../resqml2/WellboreTrajectoryRepresentation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* StreamlinesRepresentation::XML_NS = "resqml22";

StreamlinesRepresentation::StreamlinesRepresentation(RESQML2_NS::GenericFeatureInterpretation* interp, const std::string & guid, const std::string & title, uint64_t lineCount)
{
	if (interp == nullptr) {
		throw invalid_argument("You must provide an interpretation.");
	}

	gsoapProxy2_3 = soap_new_resqml22__StreamlinesRepresentation(interp->getGsoapContext());
	resqml22__StreamlinesRepresentation* sr = static_cast<resqml22__StreamlinesRepresentation*>(gsoapProxy2_3);
	sr->LineCount = lineCount;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	interp->getRepository()->addDataObject(this);
	// relationhsips
	setInterpretation(interp);
}

uint64_t StreamlinesRepresentation::getLineCount() const
{
	if (isPartial()) {
		throw std::logic_error("The representation is partial.");
	}

	return static_cast<resqml22__StreamlinesRepresentation*>(gsoapProxy2_3)->LineCount;
}

uint64_t StreamlinesRepresentation::getWellboreTrajectoryCount() const
{
	auto const* wellbores = static_cast<resqml22__StreamlinesRepresentation*>(gsoapProxy2_3)->StreamlineWellbores;

	return wellbores->WellboreTrajectoryRepresentation.size();
}

COMMON_NS::DataObjectReference StreamlinesRepresentation::getWellboreTrajectoryDor(uint64_t index) const
{
	auto const* wellbores = static_cast<resqml22__StreamlinesRepresentation*>(gsoapProxy2_3)->StreamlineWellbores;
	if (wellbores == nullptr) {
		throw std::logic_error("There is no wellbore associated to this streamlines representation");
	}
	if (index >= wellbores->WellboreTrajectoryRepresentation.size()) {
		throw std::range_error("The index of the wellbore is out of range");
	}

	return COMMON_NS::DataObjectReference(wellbores->WellboreTrajectoryRepresentation[index]);
}

uint32_t StreamlinesRepresentation::getInjectorPerLine(uint32_t* injectorPerLine) const
{
	auto const* wellboresInfo = static_cast<resqml22__StreamlinesRepresentation*>(gsoapProxy2_3)->StreamlineWellbores;

	if (wellboresInfo == nullptr) {
		throw std::logic_error("There is no wellbore trajectory associated to this streamlines representation");
	}

	return readArrayNdOfUInt32Values(wellboresInfo->InjectorPerLine, injectorPerLine);
}

uint32_t StreamlinesRepresentation::getProducerPerLine(uint32_t* producerPerLine) const
{
	auto const* wellboresInfo = static_cast<resqml22__StreamlinesRepresentation*>(gsoapProxy2_3)->StreamlineWellbores;

	if (wellboresInfo == nullptr) {
		throw std::logic_error("There is no wellbore trajectory associated to this streamlines representation");
	}

	return readArrayNdOfUInt32Values(wellboresInfo->ProducerPerLine, producerPerLine);
}

void StreamlinesRepresentation::setWellboreInformation(uint32_t const* injectorPerLine, uint32_t const* producerPerLine, const std::vector<RESQML2_NS::WellboreTrajectoryRepresentation*> & wellboreTrajectories,
	uint32_t nullValue, EML2_NS::AbstractHdfProxy* hdfProxy)
{
	if (injectorPerLine == nullptr) {
		throw invalid_argument("The injectorPerLine cannot be null.");
	}
	if (producerPerLine == nullptr) {
		throw invalid_argument("The producerPerLine cannot be null.");
	}
	if (wellboreTrajectories.empty()) {
		throw invalid_argument("You must provide some wellbore trajectories.");
	}

	if (hdfProxy == nullptr) {
		hdfProxy = getRepository()->getDefaultHdfProxy();
		if (hdfProxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, hdfProxy);

	auto* rep = static_cast<resqml22__StreamlinesRepresentation*>(gsoapProxy2_3);
	resqml22__StreamlineWellbores* wellboreInfo = soap_new_resqml22__StreamlineWellbores(getGsoapContext());
	// injectorPerLine
	// XML
	eml23__IntegerExternalArray* xmlInjectorPerLine = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	xmlInjectorPerLine->NullValue = nullValue;
	xmlInjectorPerLine->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlInjectorPerLine->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/InjectorPerLine", rep->LineCount, hdfProxy));
	wellboreInfo->InjectorPerLine = xmlInjectorPerLine;
	// HDF
	hsize_t datasetDim = rep->LineCount;
	hdfProxy->writeArrayNd(getHdfGroup(),
		"InjectorPerLine",
		H5T_NATIVE_UINT32,
		injectorPerLine,
		&datasetDim, 1);

	// producerPerLine
	// XML
	eml23__IntegerExternalArray* xmlProducerPerLine = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	xmlProducerPerLine->NullValue = nullValue;
	xmlProducerPerLine->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlProducerPerLine->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/ProducerPerLine", rep->LineCount, hdfProxy));
	wellboreInfo->ProducerPerLine = xmlProducerPerLine;
	// HDF
	hdfProxy->writeArrayNd(getHdfGroup(),
		"ProducerPerLine",
		H5T_NATIVE_UINT32,
		producerPerLine,
		&datasetDim, 1);

	// trajectories
	for (auto const* traj : wellboreTrajectories) {
		wellboreInfo->WellboreTrajectoryRepresentation.push_back(traj->newEml23Reference());
	}

	rep->StreamlineWellbores = wellboreInfo;
}
void StreamlinesRepresentation::getNodeCountPerLine(uint32_t * nodeCountPerPolyline) const
{
	auto const* geometry = static_cast<resqml22__StreamlinesRepresentation*>(gsoapProxy2_3)->Geometry;

	if (geometry == nullptr) {
		throw std::logic_error("There is no geometry associated to this streamlines representation");
	}

	readArrayNdOfUInt32Values(geometry->NodeCountPerPolyline, nodeCountPerPolyline);
}

void StreamlinesRepresentation::setGeometry(
	uint32_t const * nodeCountPerPolyline, double const * xyzPoints,
	EML2_NS::AbstractHdfProxy* hdfProxy, EML2_NS::AbstractLocal3dCrs* localCrs)
{
	if (nodeCountPerPolyline == nullptr) {
		throw invalid_argument("The nodeCountPerPolyline cannot be null.");
	}
	if (xyzPoints == nullptr) {
		throw invalid_argument("The XYZ poins cannot be nullptr.");
	}

	if (hdfProxy == nullptr) {
		hdfProxy = getRepository()->getDefaultHdfProxy();
		if (hdfProxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, hdfProxy);

	auto* rep = static_cast<resqml22__StreamlinesRepresentation*>(gsoapProxy2_3);
	auto* polyline = soap_new_resqml22__PolylineSetPatch(getGsoapContext());
	rep->Geometry = polyline;

	uint64_t nodeCount = 0;
	uint64_t intervalCount = 0;
	const auto lineCount = getLineCount();
	for (size_t lineIndex = 0; lineIndex < lineCount; ++lineIndex) {
		nodeCount += nodeCountPerPolyline[lineIndex];
		intervalCount += nodeCount - 1;
	}
	polyline->NodeCount = nodeCount;
	polyline->IntervalCount = intervalCount;

	eml23__BooleanConstantArray* closedPolylines = soap_new_eml23__BooleanConstantArray(getGsoapContext());
	closedPolylines->Count = lineCount;
	closedPolylines->Value = false;
	polyline->ClosedPolylines = closedPolylines;

	// nodeCountPerPolyline
	// XML
	eml23__IntegerExternalArray* xmlNodeCountPerPolyline = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	xmlNodeCountPerPolyline->NullValue = (std::numeric_limits<uint32_t>::max)();
	xmlNodeCountPerPolyline->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlNodeCountPerPolyline->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/NodeCountPerPolyline", lineCount, hdfProxy));
	polyline->NodeCountPerPolyline = xmlNodeCountPerPolyline;
	// HDF
	hsize_t datasetDim = lineCount;
	hdfProxy->writeArrayNd(getHdfGroup(),
		"NodeCountPerPolyline",
		H5T_NATIVE_UINT32,
		nodeCountPerPolyline,
		&datasetDim, 1);

	// XYZ
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}
	polyline->Geometry = createPointGeometryPatch2_2(0, xyzPoints, localCrs, &nodeCount, 1, hdfProxy);
	getRepository()->addRelationship(this, localCrs);
}

resqml22__PointGeometry* StreamlinesRepresentation::getPointGeometry2_2(unsigned int patchIndex) const
{
	if (patchIndex == 0 && static_cast<resqml22__StreamlinesRepresentation*>(gsoapProxy2_3)->Geometry != nullptr &&
		static_cast<resqml22__StreamlinesRepresentation*>(gsoapProxy2_3)->Geometry->Geometry->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__PointGeometry)
		return static_cast<resqml22__PointGeometry*>(static_cast<resqml22__StreamlinesRepresentation*>(gsoapProxy2_3)->Geometry->Geometry);

	return nullptr;
}

void StreamlinesRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	resqml22__PointGeometry* pointGeom = getPointGeometry2_2(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray)
	{
		auto const* daPart = static_cast<resqml22__Point3dExternalArray*>(pointGeom->Points)->Coordinates->ExternalDataArrayPart[0];
		getOrCreateHdfProxyFromDataArrayPart(daPart)->readArrayNdOfDoubleValues(daPart->PathInExternalFile, xyzPoints);
	}
	else
		throw invalid_argument("The geometry of the representation either does not exist or it is not an explicit one.");
}

void StreamlinesRepresentation::setIntervalGridCells(uint16_t const* gridIndices, uint16_t gridIndicesNullValue,
	int64_t const* cellIndices,
	uint8_t const* localFacePairPerCellIndices, uint8_t localFacePairPerCellIndicesNullValue,
	const std::vector<RESQML2_NS::AbstractGridRepresentation*> & supportingGrids,
	EML2_NS::AbstractHdfProxy * hdfProxy)
{
	if (gridIndices == nullptr) {
		throw invalid_argument("The gridIndices cannot be null.");
	}
	if (cellIndices == nullptr) {
		throw invalid_argument("The cellIndices cannot be null.");
	}
	if (localFacePairPerCellIndices == nullptr) {
		throw invalid_argument("The localFacePairPerCellIndices cannot be null.");
	}
	if (supportingGrids.empty()) {
		throw invalid_argument("The grids cannot be empty.");
	}
	auto* geom = static_cast<resqml22__StreamlinesRepresentation*>(gsoapProxy2_3)->Geometry;
	if (geom == nullptr) {
		throw logic_error("A geometry must be first set before to associate grids to the streamlines.");
	}

	if (hdfProxy == nullptr) {
		hdfProxy = getRepository()->getDefaultHdfProxy();
		if (hdfProxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, hdfProxy);

	resqml22__IntervalGridCells* igc = soap_new_resqml22__IntervalGridCells(getGsoapContext());
	geom->IntervalGridCells = igc;
	igc->CellCount = getIntervalCount();

	// gridIndices
	// XML
	eml23__IntegerExternalArray* xmlGridIndices = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	xmlGridIndices->NullValue = gridIndicesNullValue;
	xmlGridIndices->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlGridIndices->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/GridIndices", igc->CellCount, hdfProxy));
	igc->GridIndices = xmlGridIndices;
	// HDF
	hsize_t datasetDim = igc->CellCount;
	hdfProxy->writeArrayNd(getHdfGroup(),
		"GridIndices",
		H5T_NATIVE_UINT16,
		gridIndices,
		&datasetDim, 1);

	// CellIndices
	// XML
	eml23__IntegerExternalArray* xmlCellIndices = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	xmlCellIndices->NullValue = -1;
	xmlCellIndices->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlCellIndices->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/CellIndices", igc->CellCount, hdfProxy));
	igc->CellIndices = xmlCellIndices;
	// HDF
	datasetDim = igc->CellCount;
	hdfProxy->writeArrayNd(getHdfGroup(),
		"CellIndices",
		H5T_NATIVE_INT64,
		cellIndices,
		&datasetDim, 1);

	// CellIndices
	// XML
	eml23__IntegerExternalArray* xmlLocalFacePairPerCellIndices = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	xmlLocalFacePairPerCellIndices->NullValue = localFacePairPerCellIndicesNullValue;
	xmlLocalFacePairPerCellIndices->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlLocalFacePairPerCellIndices->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/LocalFacePairPerCellIndices", igc->CellCount * 2, hdfProxy));
	igc->LocalFacePairPerCellIndices = xmlLocalFacePairPerCellIndices;
	// HDF
	datasetDim = igc->CellCount * 2;
	hdfProxy->writeArrayNd(getHdfGroup(),
		"LocalFacePairPerCellIndices",
		H5T_NATIVE_UINT8,
		localFacePairPerCellIndices,
		&datasetDim, 1);

	// grids
	for (auto const* grid : supportingGrids) {
		igc->Grid.push_back(grid->newEml23Reference());
	}
}

uint16_t StreamlinesRepresentation::getGridIndices(uint16_t * gridIndices) const
{
	auto const* geometry = static_cast<resqml22__StreamlinesRepresentation*>(gsoapProxy2_3)->Geometry;
	if (geometry == nullptr) {
		throw std::logic_error("There is no geometry associated to this streamlines representation");
	}
	auto const* gridLink = geometry->IntervalGridCells;
	if (gridLink == nullptr) {
		throw std::logic_error("There is no grid associated to this streamlines representation");
	}

	return readArrayNdOfUInt16Values(gridLink->GridIndices, gridIndices);
}

int64_t StreamlinesRepresentation::getCellIndices(int64_t * cellIndices) const
{
	auto const* geometry = static_cast<resqml22__StreamlinesRepresentation*>(gsoapProxy2_3)->Geometry;
	if (geometry == nullptr) {
		throw std::logic_error("There is no geometry associated to this streamlines representation");
	}
	auto const* gridLink = geometry->IntervalGridCells;
	if (gridLink == nullptr) {
		throw std::logic_error("There is no grid associated to this streamlines representation");
	}

	return readArrayNdOfInt64Values(gridLink->CellIndices, cellIndices);
}

uint8_t StreamlinesRepresentation::getLocalFacePairPerCellIndices(uint8_t * localFacePairPerCellIndices) const
{
	auto const* geometry = static_cast<resqml22__StreamlinesRepresentation*>(gsoapProxy2_3)->Geometry;
	if (geometry == nullptr) {
		throw std::logic_error("There is no geometry associated to this streamlines representation");
	}
	auto const* gridLink = geometry->IntervalGridCells;
	if (gridLink == nullptr) {
		throw std::logic_error("There is no grid associated to this streamlines representation");
	}

	return readArrayNdOfUInt8Values(gridLink->LocalFacePairPerCellIndices, localFacePairPerCellIndices);
}

uint64_t StreamlinesRepresentation::getGridRepresentationCount() const
{
	auto const* geometry = static_cast<resqml22__StreamlinesRepresentation*>(gsoapProxy2_3)->Geometry;
	if (geometry == nullptr) {
		throw std::logic_error("There is no geometry associated to this streamlines representation");
	}
	auto const* gridLink = geometry->IntervalGridCells;
	if (gridLink == nullptr) {
		throw std::logic_error("There is no grid associated to this streamlines representation");
	}

	return gridLink->Grid.size();
}

COMMON_NS::DataObjectReference StreamlinesRepresentation::getGridRepresentationDor(uint64_t index) const
{
	auto const* geometry = static_cast<resqml22__StreamlinesRepresentation*>(gsoapProxy2_3)->Geometry;
	if (geometry == nullptr) {
		throw std::logic_error("There is no geometry associated to this streamlines representation");
	}
	auto const* gridLink = geometry->IntervalGridCells;
	if (gridLink == nullptr) {
		throw std::logic_error("There is no grid associated to this streamlines representation");
	}
	if (index >= gridLink->Grid.size()) {
		throw std::range_error("The index of the grid is out of range");
	}

	return COMMON_NS::DataObjectReference(gridLink->Grid[index]);
}

COMMON_NS::DataObjectReference StreamlinesRepresentation::getHdfProxyDor() const
{
	resqml22__StreamlinesRepresentation* rep = static_cast<resqml22__StreamlinesRepresentation*>(gsoapProxy2_3);
	if (rep->StreamlineWellbores != nullptr) {
		if (rep->StreamlineWellbores->InjectorPerLine->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__IntegerExternalArray*>(rep->StreamlineWellbores->InjectorPerLine)->Values->ExternalDataArrayPart[0]));
		}
		if (rep->StreamlineWellbores->ProducerPerLine->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__IntegerExternalArray*>(rep->StreamlineWellbores->ProducerPerLine)->Values->ExternalDataArrayPart[0]));
		}
	}
	if (rep->Geometry != nullptr) {
		if (rep->Geometry->NodeCountPerPolyline->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__IntegerExternalArray*>(rep->Geometry->NodeCountPerPolyline)->Values->ExternalDataArrayPart[0]));
		}
		if (rep->Geometry->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray) {
			return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__BooleanExternalArray*>(rep->Geometry->ClosedPolylines)->Values->ExternalDataArrayPart[0]));
		}
		if (rep->Geometry->IntervalGridCells != nullptr) {
			if (rep->Geometry->IntervalGridCells->CellIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
				return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__IntegerExternalArray*>(rep->Geometry->IntervalGridCells->CellIndices)->Values->ExternalDataArrayPart[0]));
			}
			if (rep->Geometry->IntervalGridCells->GridIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
				return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__IntegerExternalArray*>(rep->Geometry->IntervalGridCells->GridIndices)->Values->ExternalDataArrayPart[0]));
			}
			if (rep->Geometry->IntervalGridCells->LocalFacePairPerCellIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
				return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__IntegerExternalArray*>(rep->Geometry->IntervalGridCells->LocalFacePairPerCellIndices)->Values->ExternalDataArrayPart[0]));
			}
		}
	}

	return COMMON_NS::DataObjectReference();
}
