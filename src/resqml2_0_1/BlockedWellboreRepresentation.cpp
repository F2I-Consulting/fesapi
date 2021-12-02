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
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

void BlockedWellboreRepresentation::init(const std::string & guid, const std::string & title, RESQML2_NS::WellboreTrajectoryRepresentation * traj)
{
	if (traj == nullptr) {
		throw invalid_argument("The wellbore trajectory of a blocked wellbore cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREBlockedWellboreRepresentation(traj->getGsoapContext());
	_resqml20__BlockedWellboreRepresentation* frame = static_cast<_resqml20__BlockedWellboreRepresentation*>(gsoapProxy2_0_1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	traj->getRepository()->addDataObject(this);

	frame->Trajectory = traj->newResqmlReference();
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

	_resqml20__BlockedWellboreRepresentation* rep = static_cast<_resqml20__BlockedWellboreRepresentation*>(gsoapProxy2_0_1);
	ULONG64 cellCount = 0;
	for (ULONG64 intervalIndex = 0; intervalIndex < rep->NodeCount - 1; ++intervalIndex) {
		if (gridIndices[intervalIndex] != gridIndicesNullValue) {
			++cellCount;
		}
	}
	rep->CellCount = cellCount;

	if (hdfProxy == nullptr) {
		hdfProxy = getRepository()->getDefaultHdfProxy();
		if (hdfProxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
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
	hsize_t intervalCount = rep->NodeCount - 1;
	hdfProxy->writeArrayNd(getHdfGroup(),
		"GridIndices",
		H5T_NATIVE_CHAR,
		gridIndices,
		&intervalCount, 1);

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
	if (cellCount == intervalCount) {
		hdfProxy->writeArrayNd(getHdfGroup(),
			"CellIndices",
			H5T_NATIVE_INT64,
			cellIndices,
			&dimCellIndices, 1);
	}
	else {
		std::unique_ptr<int64_t[]> nonNullCellIndices(new int64_t[cellCount]);
		size_t tmp = 0;
		for (ULONG64 intervalIndex = 0; intervalIndex < intervalCount; ++intervalIndex) {
			if (gridIndices[intervalIndex] != gridIndicesNullValue) {
				nonNullCellIndices[tmp] = cellIndices[intervalIndex];
				++tmp;
			}
		}
		hdfProxy->writeArrayNd(getHdfGroup(),
			"CellIndices",
			H5T_NATIVE_INT64,
			nonNullCellIndices.get(),
			&dimCellIndices, 1);
	}

	// localFacePairPerCellIndices
	// XML
	resqml20__IntegerHdf5Array* xmlLocalFacePairPerCellIndices = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	xmlLocalFacePairPerCellIndices->NullValue = localFacePairPerCellIndicesNullValue;
	xmlLocalFacePairPerCellIndices->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlLocalFacePairPerCellIndices->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlLocalFacePairPerCellIndices->Values->PathInHdfFile = getHdfGroup() + "/LocalFacePairPerCellIndices";
	rep->LocalFacePairPerCellIndices = xmlLocalFacePairPerCellIndices;
	// HDF
	hsize_t dimLocalFacePerCellIndicesNullValue = cellCount * 2;
	if (cellCount == intervalCount) {
		hdfProxy->writeArrayNd(getHdfGroup(),
			"LocalFacePairPerCellIndices",
			H5T_NATIVE_CHAR,
			localFacePairPerCellIndices,
			&dimLocalFacePerCellIndicesNullValue, 1);
	}
	else {
		std::unique_ptr<char[]> nonNullLocalFacePairPerCellIndices(new char[cellCount*2]);
		size_t tmp = 0;
		for (ULONG64 intervalIndex = 0; intervalIndex < intervalCount; ++intervalIndex) {
			if (gridIndices[intervalIndex] != gridIndicesNullValue) {
				nonNullLocalFacePairPerCellIndices[tmp * 2] = localFacePairPerCellIndices[intervalIndex * 2];
				nonNullLocalFacePairPerCellIndices[tmp * 2 + 1] = localFacePairPerCellIndices[intervalIndex * 2 + 1];
				++tmp;
			}
		}
		hdfProxy->writeArrayNd(getHdfGroup(),
			"LocalFacePairPerCellIndices",
			H5T_NATIVE_CHAR,
			nonNullLocalFacePairPerCellIndices.get(),
			&dimLocalFacePerCellIndicesNullValue, 1);
	}
}

uint64_t BlockedWellboreRepresentation::getCellCount() const
{
	return static_cast<_resqml20__BlockedWellboreRepresentation*>(gsoapProxy2_0_1)->CellCount;
}

char BlockedWellboreRepresentation::getGridIndices(char* gridIndices) const
{
	auto xmlGridIndices = static_cast<_resqml20__BlockedWellboreRepresentation*>(gsoapProxy2_0_1)->GridIndices;

	if (xmlGridIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(xmlGridIndices)->Values;
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfCharValues(dataset->PathInHdfFile, gridIndices);

		const LONG64 nullValue = static_cast<resqml20__IntegerHdf5Array*>(xmlGridIndices)->NullValue;
		if (nullValue < (std::numeric_limits<char>::lowest)() || nullValue > (std::numeric_limits<char>::max)()) {
			throw range_error("The null value is not in the char range");
		}

		return static_cast<char>(nullValue);
	}
	else if (xmlGridIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray) {
		const int64_t constantXmlValue = static_cast<resqml20__IntegerConstantArray*>(xmlGridIndices)->Value;
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
	auto xmlCellIndices = static_cast<_resqml20__BlockedWellboreRepresentation*>(gsoapProxy2_0_1)->CellIndices;
	auto intervalCount = static_cast<_resqml20__BlockedWellboreRepresentation*>(gsoapProxy2_0_1)->NodeCount - 1;
	auto cellCount = getCellCount();

	if (xmlCellIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		LONG64 nullvalue = static_cast<resqml20__IntegerHdf5Array*>(xmlCellIndices)->NullValue;
		gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(xmlCellIndices)->Values;
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		if (cellCount == intervalCount) {
			hdfProxy->readArrayNdOfInt64Values(dataset->PathInHdfFile, cellIndices);
		}
		else {
			std::unique_ptr<int64_t[]> nonNullCellIndices(new int64_t[cellCount]);
			hdfProxy->readArrayNdOfInt64Values(dataset->PathInHdfFile, nonNullCellIndices.get());
			std::unique_ptr<char[]> gridIndices(new char[intervalCount]);
			char gridIndexNullvalue = getGridIndices(gridIndices.get());
			size_t tmp = 0;
			for (ULONG64 intervalIndex = 0; intervalIndex < intervalCount; ++intervalIndex) {
				cellIndices[intervalIndex] = gridIndices[intervalIndex] != gridIndexNullvalue
					? nonNullCellIndices[tmp++]
					: nullvalue;
			}
		}
		return nullvalue;
	}
	else if (xmlCellIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray) {
		std::fill_n(cellIndices, intervalCount, static_cast<resqml20__IntegerConstantArray*>(xmlCellIndices)->Value);
	}
	else {
		throw std::logic_error("Not implemented yet");
	}

	return (numeric_limits<char>::max)();
}

char BlockedWellboreRepresentation::getLocalFacePairPerCellIndices(char* localFacePairPerCellIndices) const
{
	auto xmlLocalFacePairPerCellIndices = static_cast<_resqml20__BlockedWellboreRepresentation*>(gsoapProxy2_0_1)->LocalFacePairPerCellIndices;
	auto intervalCount = static_cast<_resqml20__BlockedWellboreRepresentation*>(gsoapProxy2_0_1)->NodeCount - 1;
	auto cellCount = getCellCount();

	if (xmlLocalFacePairPerCellIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		const LONG64 nullValue = static_cast<resqml20__IntegerHdf5Array*>(xmlLocalFacePairPerCellIndices)->NullValue;
		if (nullValue < (std::numeric_limits<char>::lowest)() || nullValue >(std::numeric_limits<char>::max)()) {
			throw range_error("The null value is not in the char range");
		}
		const char nullValueChar = static_cast<char>(nullValue);

		gsoap_resqml2_0_1::eml20__Hdf5Dataset const* dataset = static_cast<resqml20__IntegerHdf5Array*>(xmlLocalFacePairPerCellIndices)->Values;
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		if (cellCount == intervalCount) {
			hdfProxy->readArrayNdOfCharValues(dataset->PathInHdfFile, localFacePairPerCellIndices);
		}
		else {
			std::unique_ptr<char[]> nonNullCellLocalFacePairPerCellIndices(new char[cellCount*2]);
			hdfProxy->readArrayNdOfCharValues(dataset->PathInHdfFile, nonNullCellLocalFacePairPerCellIndices.get());
			std::unique_ptr<char[]> gridIndices(new char[intervalCount]);
			char gridIndexNullvalue = getGridIndices(gridIndices.get());
			size_t tmp = 0;
			for (ULONG64 intervalIndex = 0; intervalIndex < intervalCount; ++intervalIndex) {
				if (gridIndices[intervalIndex] != gridIndexNullvalue) {
					localFacePairPerCellIndices[intervalIndex * 2] = nonNullCellLocalFacePairPerCellIndices[tmp++];
					localFacePairPerCellIndices[intervalIndex * 2 + 1] = nonNullCellLocalFacePairPerCellIndices[tmp++];
				}
				else {
					localFacePairPerCellIndices[intervalIndex * 2] = nullValueChar;
					localFacePairPerCellIndices[intervalIndex * 2 + 1] = nullValueChar;
				}
			}
		}
		return nullValueChar;
	}
	else if (xmlLocalFacePairPerCellIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray) {
		const int64_t constantXmlValue = static_cast<resqml20__IntegerConstantArray*>(xmlLocalFacePairPerCellIndices)->Value;
		if (constantXmlValue > (std::numeric_limits<char>::max)()) {
			throw std::range_error("The constant value is strictly superior than char maximum value.");
		}
		std::fill_n(localFacePairPerCellIndices, intervalCount * 2, static_cast<char>(constantXmlValue));
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
	static_cast<_resqml20__BlockedWellboreRepresentation*>(gsoapProxy2_0_1)->Grid.push_back(supportingGridRep->newResqmlReference());
}

COMMON_NS::DataObjectReference BlockedWellboreRepresentation::getSupportingGridRepresentationDor(uint64_t index) const
{
	_resqml20__BlockedWellboreRepresentation* rep = static_cast<_resqml20__BlockedWellboreRepresentation*>(gsoapProxy2_0_1);
	return rep->Grid.at(index);
}

uint64_t BlockedWellboreRepresentation::getSupportingGridRepresentationCount() const
{
	return static_cast<_resqml20__BlockedWellboreRepresentation*>(gsoapProxy2_0_1)->Grid.size();
}
