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

#include <limits>
#include <stdexcept>

#include <hdf5.h>

#include "../resqml2/AbstractGridRepresentation.h"
#include "../resqml2/WellboreInterpretation.h"
#include "../resqml2/WellboreTrajectoryRepresentation.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* BlockedWellboreRepresentation::XML_NS = "resqml22";

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

void BlockedWellboreRepresentation::setIntervalGridCells(unsigned int const* gridIndices, unsigned int gridIndicesNullValue,
	unsigned int cellCount, int64_t const* cellIndices,
	unsigned char const* localFacePairPerCellIndices, unsigned char localFacePairPerCellIndicesNullValue, EML2_NS::AbstractHdfProxy * hdfProxy)
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

	_resqml22__BlockedWellboreRepresentation* rep = static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3);
	rep->IntervalGridCells = soap_new_resqml22__IntervalGridCells(gsoapProxy2_3->soap);
	rep->IntervalGridCells->CellCount = cellCount;

	getRepository()->addRelationship(this, hdfProxy);

	// gridIndices
	// XML
	eml23__IntegerExternalArray* xmlGridIndices = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	xmlGridIndices->NullValue = gridIndicesNullValue;
	xmlGridIndices->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlGridIndices->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/GridIndices", rep->NodeCount, hdfProxy));
	rep->IntervalGridCells->GridIndices = xmlGridIndices;
	// HDF
	hsize_t dimGridIndices = rep->NodeCount;
	hdfProxy->writeArrayNd(getHdfGroup(),
		"GridIndices",
		H5T_NATIVE_UINT,
		gridIndices,
		&dimGridIndices, 1);

	// cellIndices
	// XML
	eml23__IntegerExternalArray* xmlCellIndices = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	xmlCellIndices->NullValue = -1;
	xmlCellIndices->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlCellIndices->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/CellIndices", cellCount, hdfProxy));
	rep->IntervalGridCells->CellIndices = xmlCellIndices;
	// HDF
	hsize_t dimCellIndices = cellCount;
	hdfProxy->writeArrayNd(getHdfGroup(),
		"CellIndices",
		H5T_NATIVE_INT64,
		cellIndices,
		&dimCellIndices, 1);

	// localFacePairPerCellIndices
	// XML
	eml23__IntegerExternalArray* xmlLocalFacePairPerCellIndices = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	xmlLocalFacePairPerCellIndices->NullValue = localFacePairPerCellIndicesNullValue;
	xmlLocalFacePairPerCellIndices->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlLocalFacePairPerCellIndices->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/LocalFacePairPerCellIndices", cellCount*2, hdfProxy));
	rep->IntervalGridCells->LocalFacePairPerCellIndices = xmlLocalFacePairPerCellIndices;
	// HDF
	hsize_t dimLocalFacePerCellIndicesNullValue = cellCount*2;
	hdfProxy->writeArrayNd(getHdfGroup(),
		"LocalFacePairPerCellIndices",
		H5T_NATIVE_UCHAR,
		localFacePairPerCellIndices,
		&dimLocalFacePerCellIndicesNullValue, 1);
}

uint64_t BlockedWellboreRepresentation::getCellCount() const
{
	return static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3)->IntervalGridCells->CellCount;
}

int64_t BlockedWellboreRepresentation::getGridIndices(unsigned int * gridIndices) const
{
	auto xmlGridIndices = static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3)->IntervalGridCells->GridIndices;

	if (xmlGridIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		eml23__ExternalDataArrayPart const * daPart = static_cast<eml23__IntegerExternalArray*>(xmlGridIndices)->Values->ExternalDataArrayPart[0];
		getOrCreateHdfProxyFromDataArrayPart(daPart)->readArrayNdOfUIntValues(daPart->PathInExternalFile, gridIndices);
		return static_cast<eml23__IntegerExternalArray*>(xmlGridIndices)->NullValue;
	}
	else if (xmlGridIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray) {
		const int64_t constantXmlValue = static_cast<eml23__IntegerConstantArray*>(xmlGridIndices)->Value;
		if (constantXmlValue > (std::numeric_limits<int64_t>::max)()) {
			throw std::range_error("The constant value is strictly superior than unsigned int maximum value.");
		}

		const unsigned int intervalCount = getMdValuesCount() - 1;
		for (unsigned int i = 0; i < intervalCount; ++i) {
			gridIndices[i] = static_cast<unsigned int>(constantXmlValue);
		}
	}
	else {
		throw std::logic_error("Not implemented yet");
	}

	return (numeric_limits<int64_t>::max)();
}

void BlockedWellboreRepresentation::pushBackSupportingGridRepresentation(RESQML2_NS::AbstractGridRepresentation * supportingGridRep)
{
	if (supportingGridRep == nullptr) {
		throw invalid_argument("The supporting Grid Representation cannot be null.");
	}

	// EPC
	getRepository()->addRelationship(this, supportingGridRep);

	// XML
	static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3)->IntervalGridCells->Grid.push_back(supportingGridRep->newEml23Reference());
}

COMMON_NS::DataObjectReference BlockedWellboreRepresentation::getSupportingGridRepresentationDor(unsigned int index) const
{
	_resqml22__BlockedWellboreRepresentation* rep = static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3);

	if (index >= rep->IntervalGridCells->Grid.size()) {
		throw out_of_range("The requested index is out of range of the available supporting grid representations.");
	}
	return rep->IntervalGridCells->Grid[index];
}

unsigned int BlockedWellboreRepresentation::getSupportingGridRepresentationCount() const
{
	const size_t result = static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3)->IntervalGridCells->Grid.size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much supporting representations");
	}

	return static_cast<unsigned int>(result);
}
