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

#include "../eml2/AbstractHdfProxy.h"

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../resqml2/AbstractGridRepresentation.h"
#include "../eml2/AbstractLocal3dCrs.h"

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

	throw std::logic_error("Not implemented yet");
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

void GridConnectionSetRepresentation::getInterpretationIndexCumulativeCount(unsigned int * cumulativeCount) const
{
	if (isAssociatedToInterpretations()) {		
		_resqml22__GridConnectionSetRepresentation const* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);
		readArrayNdOfUInt32Values(rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength, cumulativeCount);
	}
	else {
		throw std::invalid_argument("The grid connection does not contain any (fault) interpretation association.");
	}
}

void GridConnectionSetRepresentation::getInterpretationIndices(unsigned int * interpretationIndices) const
{
	if (isAssociatedToInterpretations()) {
		_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);
		if (rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			eml23__ExternalDataArrayPart* daPart = static_cast<eml23__IntegerExternalArray*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values->ExternalDataArrayPart[0];
			getOrCreateHdfProxyFromDataArrayPart(daPart)->readArrayNdOfUIntValues(daPart->PathInExternalFile, interpretationIndices);
		}
		else {
			throw std::logic_error("Not implemented yet");
		}
	}
	else {
		throw std::invalid_argument("The grid connection does not contain any (fault) interpretation association.");
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
			throw std::logic_error("Not implemented yet");
		}
	}
	else {
		throw std::invalid_argument("The grid connection does not contain any (fault) interpretation association.");
	}
}

uint64_t GridConnectionSetRepresentation::getCellIndexPairCount() const
{
	return static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3)->Count;
}

uint64_t GridConnectionSetRepresentation::getCellIndexPairCountFromInterpretationIndex(int interpretationIndex) const
{
	const unsigned int interpCount = getInterpretationCount();
	if (interpretationIndex < -1 || interpretationIndex >= static_cast<int>(interpCount)) {
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
		if (rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray)
		{
			auto const* daPart = static_cast<eml23__IntegerExternalArray*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values->ExternalDataArrayPart[0];
			auto hdfProxy = getOrCreateHdfProxyFromDataArrayPart(daPart);
			const signed long long faultIndexCount = getOrCreateHdfProxyFromDataArrayPart(daPart)->getElementCount(daPart->PathInExternalFile);
			if (faultIndexCount < 0) {
				throw invalid_argument("The HDF5 library could not read the element count of this dataset.");
			}
			std::unique_ptr<unsigned int[]> faultIndices(new unsigned int[static_cast<size_t>(faultIndexCount)]);

			hdfProxy->readArrayNdOfUIntValues(daPart->PathInExternalFile, faultIndices.get());
			for (size_t i = 0; i < static_cast<size_t>(faultIndexCount); ++i) {
				if (faultIndices[i] == static_cast<unsigned int>(interpretationIndex)) {
					result++;
				}
			}
		}
		else {
			throw std::logic_error("Not implemented yet");
		}
	}

	return result;
}

void GridConnectionSetRepresentation::getGridConnectionSetInformationFromInterpretationIndex(int64_t * cellIndexPairs, unsigned short * gridIndexPairs, int * localFaceIndexPairs, int interpretationIndex) const
{
	const unsigned int interpCount = getInterpretationCount();
	if (interpretationIndex < -1 || interpretationIndex >= static_cast<int>(interpCount)) {
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
		std::unique_ptr<unsigned int[]> faultIndices;
		if (rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			faultIndices = std::unique_ptr<unsigned int[]>(new unsigned int[cumulativeCount[totalCellIndexPairCount-1]]);
			eml23__ExternalDataArrayPart* daPart = static_cast<eml23__IntegerExternalArray*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values->ExternalDataArrayPart[0];
			getOrCreateHdfProxyFromDataArrayPart(daPart)->readArrayNdOfUIntValues(daPart->PathInExternalFile, faultIndices.get());
		}
		else {
			throw std::logic_error("Not yet implemented");
		}

		// Based on the fault indices information, construct the required subset of information
		size_t cellIndexPairIndex = 0;
		unsigned int j = 0;
		for (unsigned int i = 0; i < totalCellIndexPairCount; ++i) {
			for (; j < cumulativeCount[i]; ++j) {
				if (faultIndices[j] == static_cast<unsigned int>(interpretationIndex)) {
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

COMMON_NS::DataObjectReference GridConnectionSetRepresentation::getInterpretationDorFromIndex(unsigned int interpretationIndex) const
{
	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);

	if (rep->ConnectionInterpretations != nullptr) {
		if (rep->ConnectionInterpretations->FeatureInterpretation.size() > interpretationIndex) {
			if (rep->ConnectionInterpretations->FeatureInterpretation[interpretationIndex]->QualifiedType.find("FaultInterpretation") != string::npos) {
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

unsigned int GridConnectionSetRepresentation::getInterpretationCount() const
{
	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);

	if (rep->ConnectionInterpretations != nullptr) {
		const size_t result = rep->ConnectionInterpretations->FeatureInterpretation.size();

		if (result > (numeric_limits<unsigned int>::max)()) {
			throw range_error("There are too many associated interpretations.");
		}

		return static_cast<unsigned int>(result);
	}

	return 0;
}

int64_t GridConnectionSetRepresentation::getCellIndexPairs(int64_t * cellIndexPairs) const
{
	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);

	if (rep->CellIndexPairs->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		eml23__ExternalDataArrayPart * daPart = static_cast<eml23__IntegerExternalArray*>(rep->CellIndexPairs)->Values->ExternalDataArrayPart[0];
		getOrCreateHdfProxyFromDataArrayPart(daPart)->readArrayNdOfInt64Values(daPart->PathInExternalFile, cellIndexPairs);
		return static_cast<eml23__IntegerExternalArray*>(rep->CellIndexPairs)->NullValue;
	}
	else {
		throw std::logic_error("Not yet implemented");
	}
}

bool GridConnectionSetRepresentation::isBasedOnMultiGrids() const 
{
	return static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3)->GridIndexPairs != nullptr && 
		static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3)->Grid.size() > 1;
}

void GridConnectionSetRepresentation::getGridIndexPairs(unsigned short * gridIndexPairs) const
{
	if (!isBasedOnMultiGrids()) {
		throw std::invalid_argument("This representation has no multiple grid support.");
	}

	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);

	if (rep->GridIndexPairs->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		eml23__ExternalDataArrayPart * daPart = static_cast<eml23__IntegerExternalArray*>(rep->GridIndexPairs)->Values->ExternalDataArrayPart[0];
		getOrCreateHdfProxyFromDataArrayPart(daPart)->readArrayNdOfUShortValues(daPart->PathInExternalFile, gridIndexPairs);
	}
	else {
		throw std::logic_error("Not implemented yet");
	}
}

bool GridConnectionSetRepresentation::hasLocalFacePerCell() const
{
	return static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3)->LocalFacePerCellIndexPairs != nullptr;
}

int64_t GridConnectionSetRepresentation::getLocalFacePerCellIndexPairs(int * localFaceCellIndexPairs) const
{
	if (!hasLocalFacePerCell()) {
		throw std::invalid_argument("This representation has no local face per cell.");
	}

	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);

	if (rep->LocalFacePerCellIndexPairs->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		eml23__ExternalDataArrayPart * daPart = static_cast<eml23__IntegerExternalArray*>(rep->LocalFacePerCellIndexPairs)->Values->ExternalDataArrayPart[0];
		getOrCreateHdfProxyFromDataArrayPart(daPart)->readArrayNdOfIntValues(daPart->PathInExternalFile, localFaceCellIndexPairs);
		return static_cast<eml23__IntegerExternalArray*>(rep->LocalFacePerCellIndexPairs)->NullValue;
	}
	else {
		throw std::logic_error("Not implemented yet");
	}
}

void GridConnectionSetRepresentation::pushBackXmlSupportingGridRepresentation(RESQML2_NS::AbstractGridRepresentation * supportingGridRep)
{
	static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3)->Grid.push_back(supportingGridRep->newEml23Reference());
}

// TODO: Resqml allows to map with more than one feature interpretation.
void GridConnectionSetRepresentation::setConnectionInterpretationIndices(unsigned int const* cumulativeInterpCount, unsigned int const* interpIndices, EML2_NS::AbstractHdfProxy * proxy)
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
	proxy->writeItemizedListOfList(getHdfGroup(), "InterpretationIndices", H5T_NATIVE_UINT, cumulativeInterpCount, cellIndexPairCount, H5T_NATIVE_UINT, interpIndices, cumulativeInterpCount[cellIndexPairCount - 1]);
}

void GridConnectionSetRepresentation::pushBackXmlInterpretation(RESQML2_NS::AbstractFeatureInterpretation* interp)
{
	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);
	if (rep->ConnectionInterpretations == nullptr) {
		rep->ConnectionInterpretations = soap_new_resqml22__ConnectionInterpretations(gsoapProxy2_3->soap);
	}

	rep->ConnectionInterpretations->FeatureInterpretation.push_back(interp->newEml23Reference());
}

unsigned int GridConnectionSetRepresentation::getSupportingGridRepresentationCount() const
{
	const size_t result = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3)->Grid.size();

	if (result > (numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too many supporting grid representations.");
	}

	return static_cast<unsigned int>(result);
}

COMMON_NS::DataObjectReference GridConnectionSetRepresentation::getSupportingGridRepresentationDor(unsigned int index) const
{
	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);

	if (index >= rep->Grid.size()) {
		throw out_of_range("The requested index is out of range of the available supporting grid representations.");
	}
	return COMMON_NS::DataObjectReference(rep->Grid[index]);
}
