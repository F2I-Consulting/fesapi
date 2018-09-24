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
#include "resqml2_0_1/BlockedWellboreRepresentation.h"

#include <stdexcept>

#include "hdf5.h"

#include "resqml2/AbstractGridRepresentation.h"
#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "common/AbstractHdfProxy.h"

#include "tools/Misc.h"

using namespace std;
using namespace epc;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* BlockedWellboreRepresentation::XML_TAG = "BlockedWellboreRepresentation";

void BlockedWellboreRepresentation::init(const std::string & guid, const std::string & title, WellboreTrajectoryRepresentation * traj)
{
	if (traj == nullptr) {
		throw invalid_argument("The wellbore trajectory of a blocked wellbore cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREBlockedWellboreRepresentation(traj->getGsoapContext(), 1);
	_resqml2__BlockedWellboreRepresentation* frame = static_cast<_resqml2__BlockedWellboreRepresentation*>(gsoapProxy2_0_1);

	frame->Trajectory = traj->newResqmlReference();
	trajectory = traj;
	traj->addWellboreFrameRepresentation(this);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

BlockedWellboreRepresentation::BlockedWellboreRepresentation(WellboreInterpretation* interp,
	const std::string & guid, const std::string & title, class WellboreTrajectoryRepresentation * traj) :
	WellboreFrameRepresentation(interp, nullptr)
{
	init(guid, title, traj);

	if (interp != nullptr) {
		setInterpretation(interp);
	}
}

vector<Relationship> BlockedWellboreRepresentation::getAllTargetRelationships() const
{
	vector<Relationship> result = WellboreFrameRepresentation::getAllTargetRelationships();

	_resqml2__BlockedWellboreRepresentation* rep = static_cast<_resqml2__BlockedWellboreRepresentation*>(gsoapProxy2_0_1);
	for (size_t i = 0; i < rep->Grid.size(); ++i) {
		Relationship relSupportingGrid(misc::getPartNameFromReference(rep->Grid[i]), "", rep->Grid[i]->UUID);
		relSupportingGrid.setDestinationObjectType();
		result.push_back(relSupportingGrid);
	}

	return result;
}

void BlockedWellboreRepresentation::setIntevalGridCells(unsigned int * gridIndices, unsigned int gridIndicesNullValue, unsigned int cellCount, ULONG64* cellIndices, unsigned char* localFacePairPerCellIndices, unsigned char localFacePairPerCellIndicesNullValue, COMMON_NS::AbstractHdfProxy * hdfProxy)
{
	// Preconditions
	if (getXyzPointCountOfAllPatches() == 0) {
		throw logic_error("You must first provide MD values of the frame before to use this method");
	}
	if (gridIndices == nullptr) {
		throw invalid_argument("The grid indices cannot be null.");
	}
	if (cellCount == 0) {
		throw invalid_argument("The intersected cell count must not be zero.");
	}
	if (cellIndices == nullptr) {
		throw invalid_argument("The cell indices cannot be null.");
	}
	if (localFacePairPerCellIndices == nullptr) {
		throw invalid_argument("The local Face Per Cell Indices cannot be null.");
	}

	_resqml2__BlockedWellboreRepresentation* rep = static_cast<_resqml2__BlockedWellboreRepresentation*>(gsoapProxy2_0_1);
	rep->CellCount = cellCount;

	setHdfProxy(hdfProxy);

	// gridIndices
	// XML
	resqml2__IntegerHdf5Array* xmlGridIndices = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlGridIndices->NullValue = gridIndicesNullValue;
	xmlGridIndices->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlGridIndices->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlGridIndices->Values->PathInHdfFile = "/RESQML/" + rep->uuid + "/GridIndices";
	rep->GridIndices = xmlGridIndices;
	// HDF
	hsize_t dimGridIndices[] = { rep->NodeCount };
	hdfProxy->writeArrayNd(rep->uuid,
		"GridIndices",
		H5T_NATIVE_UINT,
		gridIndices,
		dimGridIndices, 1);

	// cellIndices
	// XML
	resqml2__IntegerHdf5Array* xmlCellIndices = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlCellIndices->NullValue = -1;
	xmlCellIndices->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlCellIndices->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlCellIndices->Values->PathInHdfFile = "/RESQML/" + rep->uuid + "/CellIndices";
	rep->CellIndices = xmlCellIndices;
	// HDF
	hsize_t dimCellIndices[] = { cellCount };
	hdfProxy->writeArrayNd(rep->uuid,
		"CellIndices",
		H5T_NATIVE_ULLONG,
		cellIndices,
		dimCellIndices, 1);

	// localFacePairPerCellIndices
	// XML
	resqml2__IntegerHdf5Array* xmlLocalFacePairPerCellIndices = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlLocalFacePairPerCellIndices->NullValue = localFacePairPerCellIndicesNullValue;
	xmlLocalFacePairPerCellIndices->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlLocalFacePairPerCellIndices->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlLocalFacePairPerCellIndices->Values->PathInHdfFile = "/RESQML/" + rep->uuid + "/LocalFacePairPerCellIndices";
	rep->LocalFacePairPerCellIndices = xmlLocalFacePairPerCellIndices;
	// HDF
	hsize_t dimLocalFacePerCellIndicesNullValue[] = { cellCount*2 };
	hdfProxy->writeArrayNd(rep->uuid,
		"LocalFacePairPerCellIndices",
		H5T_NATIVE_UCHAR,
		localFacePairPerCellIndices,
		dimLocalFacePerCellIndicesNullValue, 1);
}

ULONG64 BlockedWellboreRepresentation::getCellCount() const
{
	return static_cast<_resqml2__BlockedWellboreRepresentation*>(gsoapProxy2_0_1)->CellCount;
}

unsigned int BlockedWellboreRepresentation::getGridIndices(unsigned int * gridIndices) const
{
	_resqml2__BlockedWellboreRepresentation* rep = static_cast<_resqml2__BlockedWellboreRepresentation*>(gsoapProxy2_0_1);

	if (rep->GridIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(rep->GridIndices)->Values->PathInHdfFile, gridIndices);
		return static_cast<resqml2__IntegerHdf5Array*>(rep->GridIndices)->NullValue;
	}
	else if (rep->GridIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray) {
		unsigned int intervalCount = getMdValuesCount() - 1;
		for (unsigned int i = 0; i < intervalCount; ++i) {
			gridIndices[i] = static_cast<resqml2__IntegerConstantArray*>(rep->GridIndices)->Value;
		}
	}
	else {
		throw std::logic_error("Not implemented yet");
	}

	return (numeric_limits<unsigned int>::max)();
}

void BlockedWellboreRepresentation::pushBackSupportingGridRepresentation(RESQML2_NS::AbstractGridRepresentation * supportingGridRep)
{
	if (supportingGridRep == nullptr) {
		throw invalid_argument("The supporting Grid Representation cannot be null.");
	}

	// EPC
	supportingGridRep->blockedWellboreRepresentationSet.push_back(this);

	// XML
	if (updateXml) {
		static_cast<_resqml2__BlockedWellboreRepresentation*>(gsoapProxy2_0_1)->Grid.push_back(supportingGridRep->newResqmlReference());
	}
}

gsoap_resqml2_0_1::eml20__DataObjectReference* BlockedWellboreRepresentation::getSupportingGridRepresentationDor(unsigned int index) const
{
	_resqml2__BlockedWellboreRepresentation* rep = static_cast<_resqml2__BlockedWellboreRepresentation*>(gsoapProxy2_0_1);

	if (index >= rep->Grid.size()) {
		throw range_error("The requested index is out of range of the available supporting grid representations.");
	}
	return rep->Grid[index];
}

std::string BlockedWellboreRepresentation::getSupportingGridRepresentationUuid(unsigned int index) const
{
	return getSupportingGridRepresentationDor(index)->UUID;
}

void BlockedWellboreRepresentation::resolveTargetRelationships(COMMON_NS::EpcDocument* epcDoc)
{
	WellboreFrameRepresentation::resolveTargetRelationships(epcDoc);

	_resqml2__BlockedWellboreRepresentation* rep = static_cast<_resqml2__BlockedWellboreRepresentation*>(gsoapProxy2_0_1);

	// Supporting grid representation
	updateXml = false;
	for (size_t i = 0; i < rep->Grid.size(); ++i) {
		RESQML2_NS::AbstractGridRepresentation* supportingGridRep = epcDocument->getResqmlAbstractObjectByUuid<RESQML2_NS::AbstractGridRepresentation>(rep->Grid[i]->UUID);
		pushBackSupportingGridRepresentation(supportingGridRep);
	}
	updateXml = true;

}

unsigned int BlockedWellboreRepresentation::getSupportingGridRepresentationCount() const
{
	return static_cast<_resqml2__BlockedWellboreRepresentation*>(gsoapProxy2_0_1)->Grid.size();
}

RESQML2_NS::AbstractGridRepresentation* BlockedWellboreRepresentation::getSupportingGridRepresentation(unsigned int index) const
{
	return epcDocument->getResqmlAbstractObjectByUuid<RESQML2_NS::AbstractGridRepresentation>(getSupportingGridRepresentationUuid(index));
}

