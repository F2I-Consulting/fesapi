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

#include "../eml2/AbstractHdfProxy.h"

#include "../resqml2/AbstractGridRepresentation.h"
#include "../resqml2/GenericFeatureInterpretation.h"
#include "../resqml2/WellboreTrajectoryRepresentation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* StreamlinesRepresentation::XML_NS = "resqml20";

StreamlinesRepresentation::StreamlinesRepresentation(RESQML2_NS::GenericFeatureInterpretation* interp, const std::string & guid, const std::string & title, uint64_t lineCount)
{
	if (interp == nullptr) {
		throw invalid_argument("You must provide an interpretation.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREStreamlinesRepresentation(interp->getGsoapContext());
	_resqml20__StreamlinesRepresentation* sr = static_cast<_resqml20__StreamlinesRepresentation*>(gsoapProxy2_0_1);
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

	return static_cast<_resqml20__StreamlinesRepresentation*>(gsoapProxy2_0_1)->LineCount;
}

uint64_t StreamlinesRepresentation::getWellboreTrajectoryCount() const
{
	auto const* wellbores = static_cast<_resqml20__StreamlinesRepresentation*>(gsoapProxy2_0_1)->StreamlineWellbores;
	if (wellbores == nullptr) {
		throw std::logic_error("There is no wellbore associated to this streamlines representation");
	}

	return wellbores->WellboreTrajectoryRepresentation.size();
}

COMMON_NS::DataObjectReference StreamlinesRepresentation::getWellboreTrajectoryDor(uint64_t index) const
{
	auto const* wellbores = static_cast<_resqml20__StreamlinesRepresentation*>(gsoapProxy2_0_1)->StreamlineWellbores;
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
	auto const* wellboresInfo = static_cast<_resqml20__StreamlinesRepresentation*>(gsoapProxy2_0_1)->StreamlineWellbores;

	if (wellboresInfo == nullptr) {
		throw std::logic_error("There is no wellbore trajectory associated to this streamlines representation");
	}

	return readArrayNdOfUInt32Values(wellboresInfo->InjectorPerLine, injectorPerLine);
}

uint32_t StreamlinesRepresentation::getProducerPerLine(uint32_t* producerPerLine) const
{
	auto const* wellboresInfo = static_cast<_resqml20__StreamlinesRepresentation*>(gsoapProxy2_0_1)->StreamlineWellbores;

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

	auto* rep = static_cast<_resqml20__StreamlinesRepresentation*>(gsoapProxy2_0_1);
	resqml20__StreamlineWellbores* wellboreInfo = soap_new_resqml20__StreamlineWellbores(getGsoapContext());
	// injectorPerLine
	// XML
	resqml20__IntegerHdf5Array* xmlInjectorPerLine = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	xmlInjectorPerLine->NullValue = nullValue;
	xmlInjectorPerLine->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlInjectorPerLine->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlInjectorPerLine->Values->PathInHdfFile = getHdfGroup() + "/InjectorPerLine";
	wellboreInfo->InjectorPerLine = xmlInjectorPerLine;
	// HDF
	uint64_t datasetDim = rep->LineCount;
	hdfProxy->writeArrayNd(getHdfGroup(),
		"InjectorPerLine",
		COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT32,
		injectorPerLine,
		&datasetDim, 1);

	// producerPerLine
	// XML
	resqml20__IntegerHdf5Array* xmlProducerPerLine = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	xmlProducerPerLine->NullValue = nullValue;
	xmlProducerPerLine->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlProducerPerLine->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlProducerPerLine->Values->PathInHdfFile = getHdfGroup() + "/ProducerPerLine";
	wellboreInfo->ProducerPerLine = xmlProducerPerLine;
	// HDF
	hdfProxy->writeArrayNd(getHdfGroup(),
		"ProducerPerLine",
		COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT32,
		producerPerLine,
		&datasetDim, 1);

	// trajectories
	for (auto const* traj : wellboreTrajectories) {
		wellboreInfo->WellboreTrajectoryRepresentation.push_back(traj->newResqmlReference());
	}

	rep->StreamlineWellbores = wellboreInfo;
}
void StreamlinesRepresentation::getNodeCountPerLine(uint32_t * nodeCountPerPolyline) const
{
	auto const* geometry = static_cast<_resqml20__StreamlinesRepresentation*>(gsoapProxy2_0_1)->Geometry;

	if (geometry == nullptr) {
		throw std::logic_error("There is no geometry associated to this streamlines representation");
	}

	readArrayNdOfUInt32Values(geometry->NodeCountPerPolyline, nodeCountPerPolyline);
}

void StreamlinesRepresentation::setGeometry(
	uint32_t const * nodeCountPerPolyline, double const * xyzPoints,
	EML2_NS::AbstractHdfProxy* hdfProxy, RESQML2_NS::AbstractLocal3dCrs*)
{
	if (nodeCountPerPolyline == nullptr) {
		throw invalid_argument("The nodeCountPerPolyline cannot be null.");
	}
	if (xyzPoints != nullptr) {
		throw invalid_argument("xyzPoints must be nullptr in RESQML2.0.1. Please use RESQML.2.2 if you need to provide xyz points.");
	}

	if (hdfProxy == nullptr) {
		hdfProxy = getRepository()->getDefaultHdfProxy();
		if (hdfProxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, hdfProxy);

	auto* rep = static_cast<_resqml20__StreamlinesRepresentation*>(gsoapProxy2_0_1);
	resqml20__StreamlinePolylineSetPatch* polyline = soap_new_resqml20__StreamlinePolylineSetPatch(getGsoapContext());
	rep->Geometry = polyline;
	polyline->PatchIndex = 0;

	uint64_t nodeCount = 0;
	uint64_t intervalCount = 0;
	const auto lineCount = getLineCount();
	for (size_t lineIndex = 0; lineIndex < lineCount; ++lineIndex) {
		nodeCount += nodeCountPerPolyline[lineIndex];
		intervalCount += nodeCount - 1;
	}
	polyline->NodeCount = nodeCount;
	polyline->IntervalCount = intervalCount;

	resqml20__BooleanConstantArray* closedPolylines = soap_new_resqml20__BooleanConstantArray(getGsoapContext());
	closedPolylines->Count = lineCount;
	closedPolylines->Value = false;
	polyline->ClosedPolylines = closedPolylines;

	// nodeCountPerPolyline
	// XML
	resqml20__IntegerHdf5Array* xmlNodeCountPerPolyline = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	xmlNodeCountPerPolyline->NullValue = (std::numeric_limits<uint32_t>::max)();
	xmlNodeCountPerPolyline->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlNodeCountPerPolyline->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlNodeCountPerPolyline->Values->PathInHdfFile = getHdfGroup() + "/NodeCountPerPolyline";
	polyline->NodeCountPerPolyline = xmlNodeCountPerPolyline;
	// HDF
	hdfProxy->writeArrayNd(getHdfGroup(),
		"NodeCountPerPolyline",
		COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT32,
		nodeCountPerPolyline,
		&lineCount, 1);
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
	auto* geom = static_cast<_resqml20__StreamlinesRepresentation*>(gsoapProxy2_0_1)->Geometry;
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

	resqml20__IntervalGridCells* igc = soap_new_resqml20__IntervalGridCells(getGsoapContext());
	geom->IntervalGridCells = igc;
	igc->CellCount = getIntervalCount();

	// gridIndices
	// XML
	resqml20__IntegerHdf5Array* xmlGridIndices = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	xmlGridIndices->NullValue = gridIndicesNullValue;
	xmlGridIndices->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlGridIndices->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlGridIndices->Values->PathInHdfFile = getHdfGroup() + "/GridIndices";
	igc->GridIndices = xmlGridIndices;
	// HDF
	uint64_t datasetDim = igc->CellCount;
	hdfProxy->writeArrayNd(getHdfGroup(),
		"GridIndices",
		COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT16,
		gridIndices,
		&datasetDim, 1);

	// CellIndices
	// XML
	resqml20__IntegerHdf5Array* xmlCellIndices = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	xmlCellIndices->NullValue = -1;
	xmlCellIndices->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlCellIndices->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlCellIndices->Values->PathInHdfFile = getHdfGroup() + "/CellIndices";
	igc->CellIndices = xmlCellIndices;
	// HDF
	datasetDim = igc->CellCount;
	hdfProxy->writeArrayNd(getHdfGroup(),
		"CellIndices",
		COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64,
		cellIndices,
		&datasetDim, 1);

	// CellIndices
	// XML
	resqml20__IntegerHdf5Array* xmlLocalFacePairPerCellIndices = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	xmlLocalFacePairPerCellIndices->NullValue = localFacePairPerCellIndicesNullValue;
	xmlLocalFacePairPerCellIndices->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlLocalFacePairPerCellIndices->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlLocalFacePairPerCellIndices->Values->PathInHdfFile = getHdfGroup() + "/LocalFacePairPerCellIndices";
	igc->LocalFacePairPerCellIndices = xmlLocalFacePairPerCellIndices;
	// HDF
	datasetDim = igc->CellCount * 2;
	hdfProxy->writeArrayNd(getHdfGroup(),
		"LocalFacePairPerCellIndices",
		COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT8,
		localFacePairPerCellIndices,
		&datasetDim, 1);

	// grids
	for (auto const* grid : supportingGrids) {
		igc->Grids.push_back(grid->newResqmlReference());
	}
}

uint16_t StreamlinesRepresentation::getGridIndices(uint16_t * gridIndices) const
{
	auto const* geometry = static_cast<_resqml20__StreamlinesRepresentation*>(gsoapProxy2_0_1)->Geometry;
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
	auto const* geometry = static_cast<_resqml20__StreamlinesRepresentation*>(gsoapProxy2_0_1)->Geometry;
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
	auto const* geometry = static_cast<_resqml20__StreamlinesRepresentation*>(gsoapProxy2_0_1)->Geometry;
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
	auto const* geometry = static_cast<_resqml20__StreamlinesRepresentation*>(gsoapProxy2_0_1)->Geometry;
	if (geometry == nullptr) {
		throw std::logic_error("There is no geometry associated to this streamlines representation");
	}
	auto const* gridLink = geometry->IntervalGridCells;
	if (gridLink == nullptr) {
		throw std::logic_error("There is no grid associated to this streamlines representation");
	}

	return gridLink->Grids.size();
}

COMMON_NS::DataObjectReference StreamlinesRepresentation::getGridRepresentationDor(uint64_t index) const
{
	auto const* geometry = static_cast<_resqml20__StreamlinesRepresentation*>(gsoapProxy2_0_1)->Geometry;
	if (geometry == nullptr) {
		throw std::logic_error("There is no geometry associated to this streamlines representation");
	}
	auto const* gridLink = geometry->IntervalGridCells;
	if (gridLink == nullptr) {
		throw std::logic_error("There is no grid associated to this streamlines representation");
	}
	if (index >= gridLink->Grids.size()) {
		throw std::range_error("The index of the grid is out of range");
	}

	return COMMON_NS::DataObjectReference(gridLink->Grids[index]);
}

COMMON_NS::DataObjectReference StreamlinesRepresentation::getHdfProxyDor() const
{
	_resqml20__StreamlinesRepresentation* rep = static_cast<_resqml20__StreamlinesRepresentation*>(gsoapProxy2_0_1);
	if (rep->StreamlineWellbores != nullptr) {
		if (rep->StreamlineWellbores->InjectorPerLine->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			return COMMON_NS::DataObjectReference(static_cast<resqml20__IntegerHdf5Array*>(rep->StreamlineWellbores->InjectorPerLine)->Values->HdfProxy);
		}
		if (rep->StreamlineWellbores->ProducerPerLine->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			return COMMON_NS::DataObjectReference(static_cast<resqml20__IntegerHdf5Array*>(rep->StreamlineWellbores->ProducerPerLine)->Values->HdfProxy);
		}
	}
	if (rep->Geometry != nullptr) {
		if (rep->Geometry->NodeCountPerPolyline->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			return COMMON_NS::DataObjectReference(static_cast<resqml20__IntegerHdf5Array*>(rep->Geometry->NodeCountPerPolyline)->Values->HdfProxy);
		}
		if (rep->Geometry->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array) {
			return COMMON_NS::DataObjectReference(static_cast<resqml20__BooleanHdf5Array*>(rep->Geometry->ClosedPolylines)->Values->HdfProxy);
		}
		if (rep->Geometry->IntervalGridCells != nullptr) {
			if (rep->Geometry->IntervalGridCells->CellIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
				return COMMON_NS::DataObjectReference(static_cast<resqml20__IntegerHdf5Array*>(rep->Geometry->IntervalGridCells->CellIndices)->Values->HdfProxy);
			}
			if (rep->Geometry->IntervalGridCells->GridIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
				return COMMON_NS::DataObjectReference(static_cast<resqml20__IntegerHdf5Array*>(rep->Geometry->IntervalGridCells->GridIndices)->Values->HdfProxy);
			}
			if (rep->Geometry->IntervalGridCells->LocalFacePairPerCellIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
				return COMMON_NS::DataObjectReference(static_cast<resqml20__IntegerHdf5Array*>(rep->Geometry->IntervalGridCells->LocalFacePairPerCellIndices)->Values->HdfProxy);
			}
		}
	}

	return COMMON_NS::DataObjectReference();
}
