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

#include <stdexcept>

#include <hdf5.h>

#include "../resqml2/AbstractGridRepresentation.h"
#include "WellboreInterpretation.h"
#include "WellboreTrajectoryRepresentation.h"
#include "../common/AbstractHdfProxy.h"

#include "../tools/Misc.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* BlockedWellboreRepresentation::XML_TAG = "BlockedWellboreRepresentation";

void BlockedWellboreRepresentation::init(const std::string & guid, const std::string & title, WellboreTrajectoryRepresentation * traj)
{
	if (traj == nullptr) {
		throw invalid_argument("The wellbore trajectory of a blocked wellbore cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREBlockedWellboreRepresentation(traj->getGsoapContext());
	_resqml20__BlockedWellboreRepresentation* frame = static_cast<_resqml20__BlockedWellboreRepresentation*>(gsoapProxy2_0_1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	traj->getRepository()->addOrReplaceDataObject(this);

	frame->Trajectory = traj->newResqmlReference();
	getRepository()->addRelationship(this, traj);
}

BlockedWellboreRepresentation::BlockedWellboreRepresentation(WellboreInterpretation * interp,
	const std::string & guid, const std::string & title, WellboreTrajectoryRepresentation  * traj)
{
	init(guid, title, traj);

	if (interp != nullptr) {
		setInterpretation(interp);
	}
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

	_resqml20__BlockedWellboreRepresentation* rep = static_cast<_resqml20__BlockedWellboreRepresentation*>(gsoapProxy2_0_1);
	rep->CellCount = cellCount;

	getRepository()->addRelationship(this, hdfProxy);

	// gridIndices
	// XML
	resqml20__IntegerHdf5Array* xmlGridIndices = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	xmlGridIndices->NullValue = gridIndicesNullValue;
	xmlGridIndices->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlGridIndices->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlGridIndices->Values->PathInHdfFile = getHdfGroup() + "/GridIndices";
	rep->GridIndices = xmlGridIndices;
	// HDF
	hsize_t dimGridIndices = rep->NodeCount;
	hdfProxy->writeArrayNd(getHdfGroup(),
		"GridIndices",
		H5T_NATIVE_UINT,
		gridIndices,
		&dimGridIndices, 1);

	// cellIndices
	// XML
	resqml20__IntegerHdf5Array* xmlCellIndices = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	xmlCellIndices->NullValue = -1;
	xmlCellIndices->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlCellIndices->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlCellIndices->Values->PathInHdfFile = getHdfGroup() + "/CellIndices";
	rep->CellIndices = xmlCellIndices;
	// HDF
	hsize_t dimCellIndices = cellCount;
	hdfProxy->writeArrayNd(getHdfGroup(),
		"CellIndices",
		H5T_NATIVE_ULLONG,
		cellIndices,
		&dimCellIndices, 1);

	// localFacePairPerCellIndices
	// XML
	resqml20__IntegerHdf5Array* xmlLocalFacePairPerCellIndices = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	xmlLocalFacePairPerCellIndices->NullValue = localFacePairPerCellIndicesNullValue;
	xmlLocalFacePairPerCellIndices->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlLocalFacePairPerCellIndices->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlLocalFacePairPerCellIndices->Values->PathInHdfFile = getHdfGroup() + "/LocalFacePairPerCellIndices";
	rep->LocalFacePairPerCellIndices = xmlLocalFacePairPerCellIndices;
	// HDF
	hsize_t dimLocalFacePerCellIndicesNullValue = cellCount*2;
	hdfProxy->writeArrayNd(getHdfGroup(),
		"LocalFacePairPerCellIndices",
		H5T_NATIVE_UCHAR,
		localFacePairPerCellIndices,
		&dimLocalFacePerCellIndicesNullValue, 1);
}

ULONG64 BlockedWellboreRepresentation::getCellCount() const
{
	return static_cast<_resqml20__BlockedWellboreRepresentation*>(gsoapProxy2_0_1)->CellCount;
}

LONG64 BlockedWellboreRepresentation::getGridIndices(unsigned int * gridIndices) const
{
	auto xmlGridIndices = static_cast<_resqml20__BlockedWellboreRepresentation*>(gsoapProxy2_0_1)->GridIndices;

	if (xmlGridIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(xmlGridIndices)->Values;
		COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfUIntValues(dataset->PathInHdfFile, gridIndices);
		return static_cast<resqml20__IntegerHdf5Array*>(xmlGridIndices)->NullValue;
	}
	else if (xmlGridIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray) {
		const LONG64 constantXmlValue = static_cast<resqml20__IntegerConstantArray*>(xmlGridIndices)->Value;
		if (constantXmlValue > (std::numeric_limits<LONG64>::max)()) {
			throw std::range_error("The constant value is superior than unsigned int maximum value.");
		}

		const unsigned int intervalCount = getMdValuesCount() - 1;
		for (unsigned int i = 0; i < intervalCount; ++i) {
			gridIndices[i] = static_cast<unsigned int>(constantXmlValue);
		}
	}
	else {
		throw std::logic_error("Not implemented yet");
	}

	return (numeric_limits<LONG64>::max)();
}

void BlockedWellboreRepresentation::pushBackSupportingGridRepresentation(RESQML2_NS::AbstractGridRepresentation * supportingGridRep)
{
	if (supportingGridRep == nullptr) {
		throw invalid_argument("The supporting Grid Representation cannot be null.");
	}

	// EPC
	getRepository()->addRelationship(this, supportingGridRep);

	// XML
	static_cast<_resqml20__BlockedWellboreRepresentation*>(gsoapProxy2_0_1)->Grid.push_back(supportingGridRep->newResqmlReference());
}

gsoap_resqml2_0_1::eml20__DataObjectReference* BlockedWellboreRepresentation::getSupportingGridRepresentationDor(unsigned int index) const
{
	_resqml20__BlockedWellboreRepresentation* rep = static_cast<_resqml20__BlockedWellboreRepresentation*>(gsoapProxy2_0_1);

	if (index >= rep->Grid.size()) {
		throw range_error("The requested index is out of range of the available supporting grid representations.");
	}
	return rep->Grid[index];
}

std::string BlockedWellboreRepresentation::getSupportingGridRepresentationUuid(unsigned int index) const
{
	return getSupportingGridRepresentationDor(index)->UUID;
}

void BlockedWellboreRepresentation::loadTargetRelationships()
{
	WellboreFrameRepresentation::loadTargetRelationships();

	_resqml20__BlockedWellboreRepresentation* rep = static_cast<_resqml20__BlockedWellboreRepresentation*>(gsoapProxy2_0_1);

	// Supporting grid representation
	for (size_t i = 0; i < rep->Grid.size(); ++i) {
		gsoap_resqml2_0_1::eml20__DataObjectReference* dor = rep->Grid[i];
		RESQML2_NS::AbstractGridRepresentation * supportingGridRep = getRepository()->getDataObjectByUuid<RESQML2_NS::AbstractGridRepresentation>(dor->UUID);
		if (supportingGridRep == nullptr) { // partial transfer
			getRepository()->createPartial(dor);
			supportingGridRep = getRepository()->getDataObjectByUuid<RESQML2_NS::AbstractGridRepresentation>(dor->UUID);
			if (supportingGridRep == nullptr) {
				throw invalid_argument("The DOR looks invalid.");
			}
		}
		getRepository()->addRelationship(this, supportingGridRep);
	}

}

unsigned int BlockedWellboreRepresentation::getSupportingGridRepresentationCount() const
{
	const size_t result = static_cast<_resqml20__BlockedWellboreRepresentation*>(gsoapProxy2_0_1)->Grid.size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much supporting representations");
	}

	return static_cast<unsigned int>(result);
}

RESQML2_NS::AbstractGridRepresentation* BlockedWellboreRepresentation::getSupportingGridRepresentation(unsigned int index) const
{
	return repository->getDataObjectByUuid<RESQML2_NS::AbstractGridRepresentation>(getSupportingGridRepresentationUuid(index));
}
