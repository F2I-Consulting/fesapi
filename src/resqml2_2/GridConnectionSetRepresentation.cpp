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

#include "../eml2/AbstractHdfProxy.h"

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../resqml2/AbstractGridRepresentation.h"

#include "../resqml2_2/GenericFeatureInterpretation.h"

#include "../resqml2_2/GenericFeatureInterpretation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* GridConnectionSetRepresentation::XML_NS = "resqml22";

void GridConnectionSetRepresentation::init(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title)
{
	gsoapProxy2_3 = soap_new_resqml22__GridConnectionSetRepresentation(repo->getGsoapContext());

    initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(this);
}

GridConnectionSetRepresentation::GridConnectionSetRepresentation(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid, const std::string & title)
{
	init(repo, guid, title);

	setInterpretation(repo->createPartial<RESQML2_2_NS::GenericFeatureInterpretation>("", "Unknown interp"));
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
	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);

	if (rep->CellIndexPairs->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__IntegerExternalArray*>(rep->CellIndexPairs)->Values->ExternalDataArrayPart[0]));
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

	_resqml22__GridConnectionSetRepresentation* const rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);
	rep->Count = cellIndexPairCount;

	// XML cell index pair
	eml23__IntegerExternalArray* const integerArray = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	integerArray->NullValue = cellIndexPairNullValue;
	integerArray->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	integerArray->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(cellIndexPair, proxy->getElementCount(cellIndexPair), proxy));
	rep->CellIndexPairs = integerArray;

	// XML grid index pair
	if (!gridIndexPair.empty()) {
		eml23__IntegerExternalArray* const gridIndexPairArray = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
		gridIndexPairArray->NullValue = gridIndexPairNullValue;
		gridIndexPairArray->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
		gridIndexPairArray->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(gridIndexPair, proxy->getElementCount(gridIndexPair), proxy));
		rep->GridIndexPairs = gridIndexPairArray;
	}
}

void GridConnectionSetRepresentation::setLocalFacePerCellIndexPairsUsingExistingDataset(const std::string & localFacePerCellIndexPair, int64_t nullValue, EML2_NS::AbstractHdfProxy * proxy)
{
	const uint64_t cellIndexPairCount = getCellIndexPairCount();
	if (cellIndexPairCount == 0) {
		throw logic_error("You must set some cell connections before to set local face connections");
	}
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);

	// XML
	eml23__IntegerExternalArray* integerArray = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	integerArray->NullValue = nullValue;
	integerArray->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	integerArray->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(localFacePerCellIndexPair, proxy->getElementCount(localFacePerCellIndexPair), proxy));
	rep->LocalFacePerCellIndexPairs = integerArray;
}

bool GridConnectionSetRepresentation::isAssociatedToInterpretations() const
{
	return static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3)->ConnectionInterpretations != nullptr;
}

void GridConnectionSetRepresentation::getInterpretationIndexCumulativeCount(uint64_t * cumulativeCount) const
{
	if (isAssociatedToInterpretations()) {		
		_resqml22__GridConnectionSetRepresentation const* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);
		readArrayNdOfUInt64Values(rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength, cumulativeCount);
	}
	else {
		throw std::invalid_argument("The grid connection does not contain any interpretation association.");
	}
}

void GridConnectionSetRepresentation::getInterpretationIndices(int64_t * interpretationIndices) const
{
	if (isAssociatedToInterpretations()) {
		_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);
		auto const* integerArray = dynamic_cast<eml23__AbstractIntegerArray const*>(rep->ConnectionInterpretations->InterpretationIndices->Elements);
		if (integerArray != nullptr) {
			readArrayNdOfInt64Values(integerArray, interpretationIndices);
		}
		else {
			throw std::logic_error("The interpretation indices array should be an integer one.");
		}
	}
	else {
		throw std::invalid_argument("The grid connection does not contain any interpretation association.");
	}
}

int64_t GridConnectionSetRepresentation::getInterpretationIndexNullValue() const
{
	if (isAssociatedToInterpretations()) {
		_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);
		if (rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			return static_cast<eml23__IntegerExternalArray*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->NullValue;
		}
		else {
			return -1; // this value cannot be used since it should only be indices.
		}
	}
	else {
		throw std::invalid_argument("The grid connection does not contain any interpretation association.");
	}
}

uint64_t GridConnectionSetRepresentation::getCellIndexPairCount() const
{
	return static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3)->Count;
}

uint64_t GridConnectionSetRepresentation::getCellIndexPairCountFromInterpretationIndex(int64_t interpretationIndex) const
{
	const uint64_t interpCount = getInterpretationCount();
	if (interpretationIndex < -1 || interpretationIndex >= static_cast<int64_t>(interpCount)) {
		throw out_of_range("The interpretation index is out of range.");
	}

	uint64_t result = 0;
	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);

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
				if (cumulative[i] == cumulative[i - 1]) {
					result++;
				}
			}
		}
	}
	else
	{
		long arrayType = rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type();
		if (arrayType == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray)
		{
			auto const* daPart = static_cast<eml23__IntegerExternalArray*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values->ExternalDataArrayPart[0];
			auto hdfProxy = getOrCreateHdfProxyFromDataArrayPart(daPart);
			const uint64_t faultIndexCount = getOrCreateHdfProxyFromDataArrayPart(daPart)->getElementCount(daPart->PathInExternalFile);
			std::unique_ptr<int64_t[]> faultIndices(new int64_t[faultIndexCount]);

			hdfProxy->readArrayNdOfInt64Values(daPart->PathInExternalFile, faultIndices.get());
			for (size_t i = 0; i < faultIndexCount; ++i) {
				if (faultIndices[i] == interpretationIndex) {
					result++;
				}
			}
		}
		else if (arrayType == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray)
		{
			eml23__IntegerConstantArray const * constantArray = static_cast<eml23__IntegerConstantArray const*>(rep->ConnectionInterpretations->InterpretationIndices->Elements);
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
	std::unique_ptr<int64_t[]> const totalCellIndexPairs(new int64_t[totalCellIndexPairCount*2]);
	getCellIndexPairs(totalCellIndexPairs.get());
	std::unique_ptr<unsigned short[]> totalGridIndexPairs;
	if (gridIndexPairs != nullptr) {
		totalGridIndexPairs = std::unique_ptr<unsigned short[]>(new unsigned short[totalCellIndexPairCount * 2]);
		getGridIndexPairs(totalGridIndexPairs.get());
	}
	std::unique_ptr<int[]> totalLocalFaceIndexPairs;
	if (localFaceIndexPairs != nullptr) {
		totalLocalFaceIndexPairs = std::unique_ptr<int[]>(new int[totalCellIndexPairCount*2]);
		getLocalFacePerCellIndexPairs(totalLocalFaceIndexPairs.get());
	}

	_resqml22__GridConnectionSetRepresentation* const rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);

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
				if (gridIndexPairs != nullptr)	{
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
		auto const* xmlArray = rep->ConnectionInterpretations->InterpretationIndices->Elements;
		std::unique_ptr<int64_t[]> faultIndices(new int64_t[getCountOfArray(xmlArray)]);
		eml23__AbstractIntegerArray const* xmlIntArray = dynamic_cast<eml23__AbstractIntegerArray const*>(xmlArray);
		if (xmlIntArray != nullptr) {
			readArrayNdOfInt64Values(xmlIntArray, faultIndices.get());
		}
		else {
			throw std::logic_error("Interpretation indices: only integer arrays are supported for now");
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
	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);

	if (rep->ConnectionInterpretations != nullptr) {
		if (rep->ConnectionInterpretations->FeatureInterpretation.size() > interpretationIndex) {
			return COMMON_NS::DataObjectReference(rep->ConnectionInterpretations->FeatureInterpretation[interpretationIndex]);
		}
		else {
			throw out_of_range("The interpretation index is out of range in this grid connection context.");
		}
	}
	else {
		throw invalid_argument("The grid connection does not contain any interpretation association.");
	}
}

uint64_t GridConnectionSetRepresentation::getInterpretationCount() const
{
	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);

	return rep->ConnectionInterpretations != nullptr
		? rep->ConnectionInterpretations->FeatureInterpretation.size()
		: 0;
}

int64_t GridConnectionSetRepresentation::getCellIndexPairs(int64_t* cellIndexPairs) const
{
	return readArrayNdOfInt64Values(static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3)->CellIndexPairs, cellIndexPairs);
}

bool GridConnectionSetRepresentation::isBasedOnMultiGrids() const 
{
	return static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3)->GridIndexPairs != nullptr && 
		static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3)->Grid.size() > 1;
}

void GridConnectionSetRepresentation::getGridIndexPairs(unsigned short* gridIndexPairs) const
{
	cannotBePartial();

	if (!isBasedOnMultiGrids()) {
		throw std::invalid_argument("This representation has no multiple grid support.");
	}
	readArrayNdOfUInt16Values(static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3)->GridIndexPairs, gridIndexPairs);
}

bool GridConnectionSetRepresentation::hasLocalFacePerCell() const
{
	return static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3)->LocalFacePerCellIndexPairs != nullptr;
}

int64_t GridConnectionSetRepresentation::getLocalFacePerCellIndexPairs(int* localFaceCellIndexPairs) const
{
	if (!hasLocalFacePerCell()) {
		throw std::invalid_argument("This representation has no local face per cell.");
	}
	return readArrayNdOfInt32Values(static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3)->LocalFacePerCellIndexPairs, localFaceCellIndexPairs);
}

void GridConnectionSetRepresentation::pushBackXmlSupportingGridRepresentation(RESQML2_NS::AbstractGridRepresentation * supportingGridRep)
{
	static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3)->Grid.push_back(supportingGridRep->newEml23Reference());
}

// TODO: Resqml allows to map with more than one feature interpretation.
void GridConnectionSetRepresentation::setConnectionInterpretationIndices(uint64_t const* cumulativeInterpCount, int64_t const* interpIndices, EML2_NS::AbstractHdfProxy * proxy)
{
	const uint64_t cellIndexPairCount = getCellIndexPairCount();
	if (cellIndexPairCount == 0) {
		throw logic_error("You must set the cell index pairs before to set the connection interpretations.");
	}

	getRepository()->addRelationship(this, proxy);

	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);
	if (rep->ConnectionInterpretations == nullptr) {
		rep->ConnectionInterpretations = soap_new_resqml22__ConnectionInterpretations(gsoapProxy2_3->soap);
	}
	rep->ConnectionInterpretations->InterpretationIndices = soap_new_eml23__JaggedArray(gsoapProxy2_3->soap);
	
	// Cumulative
	eml23__IntegerExternalArray* cumulativeLength = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength = cumulativeLength;
	cumulativeLength->NullValue = -1;
	cumulativeLength->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	cumulativeLength->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/InterpretationIndices/" + EML2_NS::AbstractHdfProxy::CUMULATIVE_LENGTH_DS_NAME, cellIndexPairCount, proxy));
	// Elements
	eml23__IntegerExternalArray* elements = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	rep->ConnectionInterpretations->InterpretationIndices->Elements = elements;
	elements->NullValue = -1;
	elements->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	elements->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/InterpretationIndices/" + EML2_NS::AbstractHdfProxy::ELEMENTS_DS_NAME, cumulativeInterpCount[cellIndexPairCount - 1], proxy));

	// HDF
	proxy->writeItemizedListOfList(getHdfGroup(), "InterpretationIndices",
		COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT64, cumulativeInterpCount, cellIndexPairCount,
		COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64, interpIndices, cumulativeInterpCount[cellIndexPairCount - 1]);
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

	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);
	if (rep->ConnectionInterpretations == nullptr) {
		rep->ConnectionInterpretations = soap_new_resqml22__ConnectionInterpretations(gsoapProxy2_3->soap);
	}
	rep->ConnectionInterpretations->InterpretationIndices = soap_new_eml23__JaggedArray(gsoapProxy2_3->soap);

	// Cumulative
	eml23__IntegerExternalArray* cumulativeLength = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength = cumulativeLength;
	cumulativeLength->NullValue = -1;
	cumulativeLength->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	cumulativeLength->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() + "/InterpretationIndicesCumulativeLength", cellIndexPairCount));
	// Elements
	eml23__IntegerConstantArray* elements = soap_new_eml23__IntegerConstantArray(gsoapProxy2_3->soap);
	rep->ConnectionInterpretations->InterpretationIndices->Elements = elements;
	elements->Value = 0;
	elements->Count = cellIndexPairCount;

	// HDF
	std::unique_ptr<uint64_t[]> const cumulative(new uint64_t[cellIndexPairCount]);
	for (uint64_t i = 0; i < cellIndexPairCount; ++i) {
		cumulative[i] = i + 1;
	}
	proxy->writeArrayNd(getHdfGroup(), "InterpretationIndicesCumulativeLength", COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT64, cumulative.get(), &cellIndexPairCount, 1);
}

void GridConnectionSetRepresentation::pushBackXmlInterpretation(RESQML2_NS::AbstractFeatureInterpretation* interp)
{
	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);
	if (rep->ConnectionInterpretations == nullptr) {
		rep->ConnectionInterpretations = soap_new_resqml22__ConnectionInterpretations(gsoapProxy2_3->soap);
	}

	rep->ConnectionInterpretations->FeatureInterpretation.push_back(interp->newEml23Reference());
}

uint64_t GridConnectionSetRepresentation::getSupportingGridRepresentationCount() const
{
	return static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3)->Grid.size();
}

COMMON_NS::DataObjectReference GridConnectionSetRepresentation::getSupportingGridRepresentationDor(uint64_t index) const
{
	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);

	if (index >= rep->Grid.size()) {
		throw out_of_range("The requested index is out of range of the available supporting grid representations.");
	}
	return COMMON_NS::DataObjectReference(rep->Grid[index]);
}
