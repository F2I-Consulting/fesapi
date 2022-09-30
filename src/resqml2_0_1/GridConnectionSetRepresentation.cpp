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
#include "GridConnectionSetRepresentation.h"

#include <algorithm>

#include <hdf5.h>

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../resqml2/AbstractGridRepresentation.h"
#include "../eml2/AbstractHdfProxy.h"
#include "../eml2/AbstractLocal3dCrs.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* GridConnectionSetRepresentation::XML_NS = "resqml20";

void GridConnectionSetRepresentation::init(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title)
{
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREGridConnectionSetRepresentation(repo->getGsoapContext());

    initMandatoryMetadata();
    setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(this);
}

GridConnectionSetRepresentation::GridConnectionSetRepresentation(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid, const std::string & title)
{
	init(repo, guid, title);
}

GridConnectionSetRepresentation::GridConnectionSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const string & guid, const string & title)
{
	if (interp == nullptr) {
		throw invalid_argument("You must provide an interpretation");
	}

	init(interp->getRepository(), guid, title);

	setInterpretation(interp);
}

COMMON_NS::DataObjectReference GridConnectionSetRepresentation::getHdfProxyDor() const
{
	_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (rep->CellIndexPairs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		return COMMON_NS::DataObjectReference(static_cast<resqml20__IntegerHdf5Array*>(rep->CellIndexPairs)->Values->HdfProxy);
	}

	return COMMON_NS::DataObjectReference();
}

void GridConnectionSetRepresentation::setCellIndexPairsUsingExistingDataset(uint64_t cellIndexPairCount, const std::string & cellIndexPair, int64_t cellIndexPairNullValue, EML2_NS::AbstractHdfProxy * proxy, int64_t gridIndexPairNullValue, const std::string & gridIndexPair)
{
	if (cellIndexPairCount == 0) {
		throw std::invalid_argument("You cannot set zero cell index pair.");
	}
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

	_resqml20__GridConnectionSetRepresentation* const rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
	rep->Count = cellIndexPairCount;

	// XML cell index pair
	resqml20__IntegerHdf5Array* const integerArray = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	eml20__Hdf5Dataset * const resqmlHDF5dataset = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	resqmlHDF5dataset->HdfProxy = proxy->newResqmlReference();
	resqmlHDF5dataset->PathInHdfFile = cellIndexPair;
	integerArray->Values = resqmlHDF5dataset;
	integerArray->NullValue = cellIndexPairNullValue;
	rep->CellIndexPairs = integerArray;

	// XML grid index pair
	if (!gridIndexPair.empty()) {
		resqml20__IntegerHdf5Array* const gridIndexPairArray = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
		eml20__Hdf5Dataset * const gridIndexPairDataset = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		gridIndexPairDataset->HdfProxy = proxy->newResqmlReference();
		gridIndexPairDataset->PathInHdfFile = gridIndexPair;
		gridIndexPairArray->Values = gridIndexPairDataset;
		gridIndexPairArray->NullValue = gridIndexPairNullValue;
		rep->GridIndexPairs = gridIndexPairArray;
	}
}

void GridConnectionSetRepresentation::setLocalFacePerCellIndexPairsUsingExistingDataset(const std::string & localFacePerCellIndexPair, int64_t nullValue, EML2_NS::AbstractHdfProxy * proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

	_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	// XML
	resqml20__IntegerHdf5Array* integerArray = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	eml20__Hdf5Dataset * resqmlHDF5dataset = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	resqmlHDF5dataset->HdfProxy = proxy->newResqmlReference();
	resqmlHDF5dataset->PathInHdfFile = localFacePerCellIndexPair;
	integerArray->Values = resqmlHDF5dataset;
	integerArray->NullValue = nullValue;
	rep->LocalFacePerCellIndexPairs = integerArray;
}

bool GridConnectionSetRepresentation::isAssociatedToInterpretations() const
{
	return static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->ConnectionInterpretations != nullptr;
}

void GridConnectionSetRepresentation::getInterpretationIndexCumulativeCount(uint64_t * cumulativeCount) const
{
	if (isAssociatedToInterpretations()) {		
		_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
		readArrayNdOfUInt64Values(rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength, cumulativeCount);
	}
	else {
		throw std::invalid_argument("The grid connection does not contain any (fault) interpretation association.");
	}
}

void GridConnectionSetRepresentation::getInterpretationIndices(int64_t * interpretationIndices) const
{
	if (isAssociatedToInterpretations()) {
		_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
		auto const* integerArray = dynamic_cast<resqml20__AbstractIntegerArray const*>(rep->ConnectionInterpretations->InterpretationIndices->Elements);
		if (integerArray != nullptr) {
			readArrayNdOfInt64Values(integerArray, interpretationIndices);
		}
		else {
			throw std::logic_error("The interpretation indices array should be an integer one.");
		}
	}
	else {
		throw std::invalid_argument("The grid connection does not contain any (fault) interpretation association.");
	}
}

int64_t GridConnectionSetRepresentation::getInterpretationIndexNullValue() const
{
	if (isAssociatedToInterpretations()) {
		_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
		if (rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			return static_cast<resqml20__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->NullValue;
		}
		else {
			return -1; // this value cannot be used since it should only be indices.
		}
	}
	else {
		throw std::invalid_argument("The grid connection does not contain any (fault) interpretation association.");
	}
}

uint64_t GridConnectionSetRepresentation::getCellIndexPairCount() const
{
	return static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->Count;
}

uint64_t GridConnectionSetRepresentation::getCellIndexPairCountFromInterpretationIndex(int64_t interpretationIndex) const
{
	const uint64_t interpCount = getInterpretationCount();
	if (interpretationIndex < -1 || interpretationIndex >= static_cast<int64_t>(interpCount)) {
		throw out_of_range("The interpretation index is out of range.");
	}
	
	uint64_t result = 0;
	_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (interpretationIndex < 0) {
		const uint64_t totalCellIndexPairCount = getCellIndexPairCount();
		if (interpCount == 0) {
			return totalCellIndexPairCount;
		}
		else {
			std::unique_ptr<unsigned int[]> const cumulative(new unsigned int[totalCellIndexPairCount]);
			readArrayNdOfUInt32Values(rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength, cumulative.get());
			result = cumulative[0] > 0 ? 0 : 1;
			for (uint64_t i = 1; i < totalCellIndexPairCount; ++i) {
				if (cumulative[i] == cumulative[i-1]) {
					result++;
				}
			}
		}
	}
	else
	{
		long arrayType = rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type();
		if (arrayType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
		{
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
			const signed long long faultIndexCount = hdfProxy->getElementCount(dataset->PathInHdfFile);
			if (faultIndexCount < 0) {
				throw invalid_argument("The HDF5 library could not read the element count of this dataset.");
			}
			std::unique_ptr<int64_t[]> const faultIndices(new int64_t[static_cast<size_t>(faultIndexCount)]);

			hdfProxy->readArrayNdOfInt64Values(dataset->PathInHdfFile, faultIndices.get());
			for (size_t i = 0; i < static_cast<size_t>(faultIndexCount); ++i) {
				if (faultIndices[i] == interpretationIndex) {
					result++;
				}
			}
		}
		else if (arrayType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray)
		{
			resqml20__IntegerConstantArray const * constantArray = static_cast<resqml20__IntegerConstantArray const*>(rep->ConnectionInterpretations->InterpretationIndices->Elements);
			return constantArray->Value == interpretationIndex
				? constantArray->Count
				: 0;
		}
		else {
			throw std::logic_error("Interpretation indices: only constant or HDF5 arrays are supported for now");
		}
	}

	return result;
}

void GridConnectionSetRepresentation::getGridConnectionSetInformationFromInterpretationIndex(int64_t * cellIndexPairs, unsigned short * gridIndexPairs, int * localFaceIndexPairs, int64_t interpretationIndex) const
{
	const uint64_t interpCount = getInterpretationCount();
	if (interpretationIndex < -1 || interpretationIndex >= static_cast<int64_t>(interpCount)) {
		throw out_of_range("The interpretation index is out of range.");
	}

	//load global information into memory
	const uint64_t totalCellIndexPairCount = getCellIndexPairCount();
	std::unique_ptr<int64_t[]> totalCellIndexPairs(new int64_t[totalCellIndexPairCount * 2]);
	getCellIndexPairs(totalCellIndexPairs.get());
	std::unique_ptr<unsigned short[]> totalGridIndexPairs;
	if (gridIndexPairs != nullptr) {
		totalGridIndexPairs.reset(new unsigned short[totalCellIndexPairCount * 2]);
		getGridIndexPairs(totalGridIndexPairs.get());
	}
	std::unique_ptr<int[]> totalLocalFaceIndexPairs;
	if (localFaceIndexPairs != nullptr) {
		totalLocalFaceIndexPairs.reset(new int[totalCellIndexPairCount*2]);
		getLocalFacePerCellIndexPairs(totalLocalFaceIndexPairs.get());
	}

	_resqml20__GridConnectionSetRepresentation* const rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	std::unique_ptr<unsigned int[]> cumulativeCount(new unsigned int[totalCellIndexPairCount]);
	if (interpCount > 0) {
		readArrayNdOfUInt32Values(rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength, cumulativeCount.get());
	}
	else {
		std::fill(cumulativeCount.get(), cumulativeCount.get() + totalCellIndexPairCount, 0);
	}
	if (interpretationIndex < 0) {
		size_t cellIndexPairIndex = 0;
		if (cumulativeCount[0] == 0) {
			cellIndexPairs[0] = totalCellIndexPairs[0];
			cellIndexPairs[1] = totalCellIndexPairs[1];
			if (gridIndexPairs != nullptr) {
				gridIndexPairs[0] = totalGridIndexPairs[0];
				gridIndexPairs[1] = totalGridIndexPairs[1];
			}
			if (localFaceIndexPairs != nullptr) {
				localFaceIndexPairs[0] = totalLocalFaceIndexPairs[0];
				localFaceIndexPairs[1] = totalLocalFaceIndexPairs[1];
			}
			++cellIndexPairIndex;
		}
		for (uint64_t i = 1; i < totalCellIndexPairCount; ++i) {
			if (cumulativeCount[i] == cumulativeCount[i - 1]) {
				cellIndexPairs[cellIndexPairIndex * 2] = totalCellIndexPairs[i * 2];
				cellIndexPairs[cellIndexPairIndex * 2 + 1] = totalCellIndexPairs[i * 2 + 1];
				if (gridIndexPairs != nullptr) {
					gridIndexPairs[cellIndexPairIndex * 2] = totalGridIndexPairs[i * 2];
					gridIndexPairs[cellIndexPairIndex * 2 + 1] = totalGridIndexPairs[i * 2 + 1];
				}
				if (localFaceIndexPairs != nullptr) {
					localFaceIndexPairs[cellIndexPairIndex * 2] = totalLocalFaceIndexPairs[i * 2];
					localFaceIndexPairs[cellIndexPairIndex * 2 + 1] = totalLocalFaceIndexPairs[i * 2 + 1];
				}
				++cellIndexPairIndex;
			}
		}
	}
	else
	{
		long arrayType = rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type();
		std::unique_ptr<int64_t[]> faultIndices;
		if (arrayType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			faultIndices.reset(new int64_t[cumulativeCount[totalCellIndexPairCount-1]]);
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values;
			getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID)->readArrayNdOfInt64Values(dataset->PathInHdfFile, faultIndices.get());
		}
		else if (arrayType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray)
		{
			resqml20__IntegerConstantArray const * constantArray = static_cast<resqml20__IntegerConstantArray const*>(rep->ConnectionInterpretations->InterpretationIndices->Elements);
			if (constantArray->Value != interpretationIndex) {
				throw std::invalid_argument("There is no GridConnectionSet Information for the interpretation at index " + std::to_string(interpretationIndex));
			}
			faultIndices.reset(new int64_t[constantArray->Count]);
			std::fill_n(faultIndices.get(), constantArray->Count, constantArray->Value);
		}
		else {
			throw std::logic_error("Interpretation indices: only constant or HDF5 arrays are supported for now");
		}

		// Based on the fault indices information, construct the required subset of information
		size_t cellIndexPairIndex = 0;
		unsigned int j = 0;
		for (uint64_t i = 0; i < totalCellIndexPairCount; ++i) {
			for (; j < cumulativeCount[i]; ++j) {
				if (faultIndices[j] == interpretationIndex) {
					cellIndexPairs[cellIndexPairIndex*2] = totalCellIndexPairs[i*2];
					cellIndexPairs[cellIndexPairIndex*2+1] = totalCellIndexPairs[i*2+1];
					if (gridIndexPairs != nullptr) {
						gridIndexPairs[cellIndexPairIndex*2] = totalGridIndexPairs[i*2];
						gridIndexPairs[cellIndexPairIndex*2+1] = totalGridIndexPairs[i*2+1];
					}
					if (localFaceIndexPairs != nullptr) {
						localFaceIndexPairs[cellIndexPairIndex*2] = totalLocalFaceIndexPairs[i*2];
						localFaceIndexPairs[cellIndexPairIndex*2+1] = totalLocalFaceIndexPairs[i*2+1];
					}
					++cellIndexPairIndex;
				}
			}
		}
	}
}

COMMON_NS::DataObjectReference GridConnectionSetRepresentation::getInterpretationDorFromIndex(uint64_t interpretationIndex) const
{
	_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (rep->ConnectionInterpretations != nullptr) {
		if (rep->ConnectionInterpretations->FeatureInterpretation.size() > interpretationIndex) {
			if (rep->ConnectionInterpretations->FeatureInterpretation[interpretationIndex]->ContentType.find("FaultInterpretation") != string::npos) {
				return COMMON_NS::DataObjectReference(rep->ConnectionInterpretations->FeatureInterpretation[interpretationIndex]);
			}
			else {
				throw invalid_argument("The associated feature interpretation is not a fault one. Legal but not yet implemented.");
			}
		}
		else {
			throw out_of_range("The fault index is out of range in this grid connection context.");
		}
	}
	else {
		throw invalid_argument("The grid connection does not contain any (fault) interpretation association.");
	}
}

uint64_t GridConnectionSetRepresentation::getInterpretationCount() const
{
	_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	return rep->ConnectionInterpretations != nullptr
		? rep->ConnectionInterpretations->FeatureInterpretation.size()
		: 0;
}

int64_t GridConnectionSetRepresentation::getCellIndexPairs(int64_t * cellIndexPairs) const
{
	_resqml20__GridConnectionSetRepresentation const* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
	return readArrayNdOfInt64Values(rep->CellIndexPairs, cellIndexPairs);
}

bool GridConnectionSetRepresentation::isBasedOnMultiGrids() const 
{
	cannotBePartial();

	return static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->GridIndexPairs != nullptr && 
		static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->Grid.size() > 1;
}

void GridConnectionSetRepresentation::getGridIndexPairs(unsigned short * gridIndexPairs) const
{
	if (!isBasedOnMultiGrids()) {
		throw std::invalid_argument("This representation has no multiple grid support.");
	}

	_resqml20__GridConnectionSetRepresentation const* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
	readArrayNdOfUInt16Values(rep->GridIndexPairs, gridIndexPairs);
}

bool GridConnectionSetRepresentation::hasLocalFacePerCell() const
{
	return static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->LocalFacePerCellIndexPairs != nullptr;
}

int64_t GridConnectionSetRepresentation::getLocalFacePerCellIndexPairs(int* localFaceCellIndexPairs) const
{
	if (!hasLocalFacePerCell()) {
		throw std::invalid_argument("This representation has no local face per cell.");
	}
	return readArrayNdOfInt32Values(static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->LocalFacePerCellIndexPairs, localFaceCellIndexPairs);
}

void GridConnectionSetRepresentation::pushBackXmlSupportingGridRepresentation(RESQML2_NS::AbstractGridRepresentation * supportingGridRep)
{
	static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->Grid.push_back(supportingGridRep->newResqmlReference());
}

// TODO: RESQML allows to map with more than one feature interpretation.
void GridConnectionSetRepresentation::setConnectionInterpretationIndices(uint64_t const* cumulativeInterpCount, int64_t const* interpIndices, EML2_NS::AbstractHdfProxy * proxy)
{
	getRepository()->addRelationship(this, proxy);

	_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
	if (rep->ConnectionInterpretations == nullptr) {
		rep->ConnectionInterpretations = soap_new_resqml20__ConnectionInterpretations(gsoapProxy2_0_1->soap);
	}
	rep->ConnectionInterpretations->InterpretationIndices = soap_new_resqml20__ResqmlJaggedArray(gsoapProxy2_0_1->soap);
	
	// Cumulative
	resqml20__IntegerHdf5Array* cumulativeLength = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength = cumulativeLength;
	cumulativeLength->NullValue = -1;
	cumulativeLength->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	cumulativeLength->Values->HdfProxy = proxy->newResqmlReference();
	cumulativeLength->Values->PathInHdfFile = getHdfGroup() + "/InterpretationIndices/" + EML2_NS::AbstractHdfProxy::CUMULATIVE_LENGTH_DS_NAME;
	// Elements
	resqml20__IntegerHdf5Array* elements = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	rep->ConnectionInterpretations->InterpretationIndices->Elements = elements;
	elements->NullValue = -1;
	elements->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	elements->Values->HdfProxy = proxy->newResqmlReference();
	elements->Values->PathInHdfFile = getHdfGroup() + "/InterpretationIndices/" + EML2_NS::AbstractHdfProxy::ELEMENTS_DS_NAME;

	// HDF
	const uint64_t cellIndexPairCount = getCellIndexPairCount();
	if (cellIndexPairCount == 0) {
		throw logic_error("You must set the cell index pairs before to set the connection interpretations.");
	}
	proxy->writeItemizedListOfList(getHdfGroup(), "InterpretationIndices",
		COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT64, cumulativeInterpCount, cellIndexPairCount,
		COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64, interpIndices, cumulativeInterpCount[cellIndexPairCount-1]);
}

void GridConnectionSetRepresentation::setInterpretationForAllConnections(RESQML2_NS::AbstractFeatureInterpretation* interp, EML2_NS::AbstractHdfProxy * proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

	const uint64_t cellIndexPairCount = getCellIndexPairCount();
	if (cellIndexPairCount == 0) {
		throw logic_error("You must set the cell index pairs before to set the connection interpretations.");
	}

	pushBackInterpretation(interp);

	_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
	if (rep->ConnectionInterpretations == nullptr) {
		rep->ConnectionInterpretations = soap_new_resqml20__ConnectionInterpretations(gsoapProxy2_0_1->soap);
	}
	rep->ConnectionInterpretations->InterpretationIndices = soap_new_resqml20__ResqmlJaggedArray(gsoapProxy2_0_1->soap);

	// Cumulative
	resqml20__IntegerHdf5Array* cumulativeLength = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength = cumulativeLength;
	cumulativeLength->NullValue = -1;
	cumulativeLength->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	cumulativeLength->Values->HdfProxy = proxy->newResqmlReference();
	cumulativeLength->Values->PathInHdfFile = getHdfGroup() + "/InterpretationIndicesCumulativeLength";
	// Elements
	resqml20__IntegerConstantArray* elements = soap_new_resqml20__IntegerConstantArray(gsoapProxy2_0_1->soap);
	rep->ConnectionInterpretations->InterpretationIndices->Elements = elements;
	elements->Value = 0;
	elements->Count = cellIndexPairCount;

	// HDF
	std::unique_ptr<uint64_t[]> const cumulative(new uint64_t[cellIndexPairCount]);
	for (uint64_t i = 0; i < cellIndexPairCount; ++i) {
		cumulative[i] = i + 1;
	}
	hsize_t numValueInEachDim = cellIndexPairCount;
	proxy->writeArrayNd(getHdfGroup(), "InterpretationIndicesCumulativeLength", COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT64, cumulative.get(), &numValueInEachDim, 1);
}

void GridConnectionSetRepresentation::pushBackXmlInterpretation(RESQML2_NS::AbstractFeatureInterpretation* interp)
{
	_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
	if (rep->ConnectionInterpretations == nullptr) {
		rep->ConnectionInterpretations = soap_new_resqml20__ConnectionInterpretations(gsoapProxy2_0_1->soap);
	}

	rep->ConnectionInterpretations->FeatureInterpretation.push_back(interp->newResqmlReference());
}

uint64_t GridConnectionSetRepresentation::getSupportingGridRepresentationCount() const
{
	return static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->Grid.size();
}

COMMON_NS::DataObjectReference GridConnectionSetRepresentation::getSupportingGridRepresentationDor(uint64_t index) const
{
	_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (index >= rep->Grid.size()) {
		throw out_of_range("The requested index is out of range of the available supporting grid representations.");
	}
	return COMMON_NS::DataObjectReference(rep->Grid[index]);
}
