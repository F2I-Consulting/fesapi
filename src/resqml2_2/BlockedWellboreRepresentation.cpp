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

void BlockedWellboreRepresentation::setIntervalGridCells(char const* gridIndices, char gridIndicesNullValue, int64_t const* cellIndices,
	char const* localFacePairPerCellIndices, char localFacePairPerCellIndicesNullValue, EML2_NS::AbstractHdfProxy * hdfProxy)
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
		H5T_NATIVE_CHAR,
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
		H5T_NATIVE_INT64,
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
		H5T_NATIVE_CHAR,
		localFacePairPerCellIndices,
		&intervalCount, 1);
}

uint64_t BlockedWellboreRepresentation::getCellCount() const
{
	return static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3)->IntervalGridCells->CellCount;
}

char BlockedWellboreRepresentation::getGridIndices(char * gridIndices) const
{
	auto xmlGridIndices = static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3)->IntervalGridCells->GridIndices;

	if (xmlGridIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		eml23__ExternalDataArrayPart const * daPart = static_cast<eml23__IntegerExternalArray*>(xmlGridIndices)->Values->ExternalDataArrayPart[0];
		getOrCreateHdfProxyFromDataArrayPart(daPart)->readArrayNdOfCharValues(daPart->PathInExternalFile, gridIndices);

		const LONG64 nullValue = static_cast<eml23__IntegerExternalArray*>(xmlGridIndices)->NullValue;
		if (nullValue < (std::numeric_limits<char>::lowest)() || nullValue >(std::numeric_limits<char>::max)()) {
			throw range_error("The null value is not in the char range");
		}

		return static_cast<char>(nullValue);
	}
	else if (xmlGridIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray) {
		const int64_t constantXmlValue = static_cast<eml23__IntegerConstantArray*>(xmlGridIndices)->Value;
		if (constantXmlValue > (std::numeric_limits<char>::max)()) {
			throw std::range_error("The constant value is strictly superior than char maximum value.");
		}
		std::fill_n(gridIndices, getMdValuesCount() - 1, static_cast<char>(constantXmlValue));
	}
	else {
		throw std::logic_error("Not implemented yet");
	}

	return (numeric_limits<char>::max)();
}

int64_t BlockedWellboreRepresentation::getCellIndices(int64_t* cellIndices) const
{
	auto xmlCellIndices = static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3)->IntervalGridCells->CellIndices;

	if (xmlCellIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		eml23__ExternalDataArrayPart const* dsPart = static_cast<eml23__IntegerExternalArray*>(xmlCellIndices)->Values->ExternalDataArrayPart[0];
		getOrCreateHdfProxyFromDataArrayPart(dsPart)->readArrayNdOfInt64Values(dsPart->PathInExternalFile, cellIndices);
		return static_cast<eml23__IntegerExternalArray*>(xmlCellIndices)->NullValue;
	}
	else if (xmlCellIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray) {
		std::fill_n(cellIndices, getMdValuesCount() - 1, static_cast<eml23__IntegerConstantArray*>(xmlCellIndices)->Value);
	}
	else {
		throw std::logic_error("Not implemented yet");
	}

	return (numeric_limits<int64_t>::max)();
}

char BlockedWellboreRepresentation::getLocalFacePairPerCellIndices(char* localFacePairPerCellIndices) const
{
	auto xmlLocalFacePairPerCellIndices = static_cast<_resqml22__BlockedWellboreRepresentation*>(gsoapProxy2_3)->IntervalGridCells->LocalFacePairPerCellIndices;

	if (xmlLocalFacePairPerCellIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		eml23__ExternalDataArrayPart const* dsPart = static_cast<eml23__IntegerExternalArray*>(xmlLocalFacePairPerCellIndices)->Values->ExternalDataArrayPart[0];
		getOrCreateHdfProxyFromDataArrayPart(dsPart)->readArrayNdOfCharValues(dsPart->PathInExternalFile, localFacePairPerCellIndices);

		const LONG64 nullValue = static_cast<eml23__IntegerExternalArray*>(xmlLocalFacePairPerCellIndices)->NullValue;
		if (nullValue < (std::numeric_limits<char>::lowest)() || nullValue >(std::numeric_limits<char>::max)()) {
			throw range_error("The null value is not in the char range");
		}

		return static_cast<char>(nullValue);
	}
	else if (xmlLocalFacePairPerCellIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray) {
		const int64_t constantXmlValue = static_cast<eml23__IntegerConstantArray*>(xmlLocalFacePairPerCellIndices)->Value;
		if (constantXmlValue > (std::numeric_limits<char>::max)()) {
			throw std::range_error("The constant value is strictly superior than char maximum value.");
		}
		std::fill_n(localFacePairPerCellIndices, (getMdValuesCount() - 1)*2, static_cast<char>(constantXmlValue));
	}
	else {
		throw std::logic_error("Not implemented yet");
	}

	return (numeric_limits<char>::max)();
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
