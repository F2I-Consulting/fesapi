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
#include "BlockedWellboreRepresentation.h"

#include <hdf5.h>

#include "../resqml2/AbstractGridRepresentation.h"
#include "../resqml2/WellboreInterpretation.h"
#include "../resqml2/WellboreTrajectoryRepresentation.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

void BlockedWellboreRepresentation::init(const std::string & guid, const std::string & title, RESQML2_NS::WellboreTrajectoryRepresentation * traj)
{
	if (traj == nullptr) {
		throw invalid_argument("The wellbore trajectory of a blocked wellbore cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__BlockedWellboreRepresentation(traj->getGsoapContext());
	_resqml22__BlockedWellboreRepresentation* frame = static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	traj->getRepository()->addDataObject(this);

	frame->Trajectory = traj->newEml23Reference();
	getRepository()->addRelationship(this, traj);
}

BlockedWellboreRepresentation::BlockedWellboreRepresentation(RESQML2_NS::WellboreInterpretation * interp,
	const std::string & guid, const std::string & title, RESQML2_NS::WellboreTrajectoryRepresentation  * traj)
{
	init(guid, title, traj);

	if (interp != nullptr) {
		setInterpretation(interp);
	}
}

void BlockedWellboreRepresentation::setIntervalGridCells(int8_t const* gridIndices, int8_t gridIndicesNullValue, int64_t const* cellIndices,
	int8_t const* localFacePairPerCellIndices, int8_t localFacePairPerCellIndicesNullValue, EML2_NS::AbstractHdfProxy * hdfProxy)
{
	// Preconditions
	if (getXyzPointCountOfAllPatches() == 0) {
		throw logic_error("You must first provide MD values of the frame before to use this method");
	}
	if (gridIndices == nullptr) {
		throw invalid_argument("The grid indices cannot be null.");
	}
	if (cellIndices == nullptr) {
		throw invalid_argument("The cell indices cannot be null.");
	}
	if (localFacePairPerCellIndices == nullptr) {
		throw invalid_argument("The local Face Per Cell Indices cannot be null.");
	}

	_resqml22__BlockedWellboreRepresentation* rep = static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3);
	ULONG64 cellCount = 0;
	for (LONG64 intervalIndex = 0; intervalIndex < rep->NodeCount - 1; ++intervalIndex) {
		if (gridIndices[intervalIndex] != gridIndicesNullValue) {
			++cellCount;
		}
	}
	if (rep->IntervalGridCells == nullptr) {
		rep->IntervalGridCells = soap_new_resqml22__IntervalGridCells(gsoapProxy2_3->soap);
	}
	rep->IntervalGridCells->CellCount = cellCount;

	if (hdfProxy == nullptr) {
		hdfProxy = getRepository()->getDefaultHdfProxy();
		if (hdfProxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, hdfProxy);

	// gridIndices
	// XML
	eml23__IntegerExternalArray* xmlGridIndices = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	xmlGridIndices->NullValue = gridIndicesNullValue;
	xmlGridIndices->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlGridIndices->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/GridIndices", rep->NodeCount, hdfProxy));
	rep->IntervalGridCells->GridIndices = xmlGridIndices;
	// HDF
	hsize_t intervalCount = rep->NodeCount - 1;
	hdfProxy->writeArrayNd(getHdfGroup(),
		"GridIndices",
		COMMON_NS::AbstractObject::numericalDatatypeEnum::INT8,
		gridIndices,
		&intervalCount, 1);

	// cellIndices
	// XML
	eml23__IntegerExternalArray* xmlCellIndices = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	xmlCellIndices->NullValue = -1;
	xmlCellIndices->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlCellIndices->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/CellIndices", cellCount, hdfProxy));
	rep->IntervalGridCells->CellIndices = xmlCellIndices;
	// HDF
	hdfProxy->writeArrayNd(getHdfGroup(),
		"CellIndices",
		COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64,
		cellIndices,
		&intervalCount, 1);

	// localFacePairPerCellIndices
	// XML
	eml23__IntegerExternalArray* xmlLocalFacePairPerCellIndices = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	xmlLocalFacePairPerCellIndices->NullValue = localFacePairPerCellIndicesNullValue;
	xmlLocalFacePairPerCellIndices->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlLocalFacePairPerCellIndices->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/LocalFacePairPerCellIndices", cellCount*2, hdfProxy));
	rep->IntervalGridCells->LocalFacePairPerCellIndices = xmlLocalFacePairPerCellIndices;
	// HDF
	intervalCount *= 2;
	hdfProxy->writeArrayNd(getHdfGroup(),
		"LocalFacePairPerCellIndices",
		COMMON_NS::AbstractObject::numericalDatatypeEnum::INT8,
		localFacePairPerCellIndices,
		&intervalCount, 1);
}

uint64_t BlockedWellboreRepresentation::getCellCount() const
{
	return static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3)->IntervalGridCells->CellCount;
}

int8_t BlockedWellboreRepresentation::getGridIndices(int8_t * gridIndices) const
{
	auto const* xmlGridIndices = static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3)->IntervalGridCells->GridIndices;
	return readArrayNdOfInt8Values(xmlGridIndices, gridIndices);
}

int64_t BlockedWellboreRepresentation::getCellIndices(int64_t* cellIndices) const
{
	auto const* xmlCellIndices = static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3)->IntervalGridCells->CellIndices;
	return readArrayNdOfInt64Values(xmlCellIndices, cellIndices);
}

int8_t BlockedWellboreRepresentation::getLocalFacePairPerCellIndices(int8_t* localFacePairPerCellIndices) const
{
	auto const* xmlLocalFacePairPerCellIndices = static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3)->IntervalGridCells->LocalFacePairPerCellIndices;
	return readArrayNdOfInt8Values(xmlLocalFacePairPerCellIndices, localFacePairPerCellIndices);
}

void BlockedWellboreRepresentation::pushBackSupportingGridRepresentation(RESQML2_NS::AbstractGridRepresentation * supportingGridRep)
{
	if (supportingGridRep == nullptr) {
		throw invalid_argument("The supporting Grid Representation cannot be null.");
	}

	// EPC
	getRepository()->addRelationship(this, supportingGridRep);

	// XML
	if (static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3)->IntervalGridCells == nullptr) {
		static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3)->IntervalGridCells = soap_new_resqml22__IntervalGridCells(gsoapProxy2_3->soap);
	}
	static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3)->IntervalGridCells->Grid.push_back(supportingGridRep->newEml23Reference());
}

COMMON_NS::DataObjectReference BlockedWellboreRepresentation::getSupportingGridRepresentationDor(uint64_t index) const
{
	_resqml22__BlockedWellboreRepresentation* rep = static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3);
	return rep->IntervalGridCells->Grid.at(index);
}

uint64_t BlockedWellboreRepresentation::getSupportingGridRepresentationCount() const
{
	return static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3)->IntervalGridCells->Grid.size();
}
