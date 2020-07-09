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
#include <limits>
#include <stdexcept>

#include <hdf5.h>

#include "../eml2/AbstractHdfProxy.h"

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../resqml2/AbstractGridRepresentation.h"
#include "../resqml2/AbstractLocal3dCrs.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* GridConnectionSetRepresentation::XML_NS = "resqml22";

void GridConnectionSetRepresentation::init(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title)
{
	gsoapProxy2_3 = soap_new_resqml22__GridConnectionSetRepresentation(repo->getGsoapContext());

    initMandatoryMetadata();
    setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addOrReplaceDataObject(this);
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
	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);

	if (rep->CellIndexPairs->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		return COMMON_NS::DataObjectReference(static_cast<eml23__IntegerExternalArray*>(rep->CellIndexPairs)->Values->ExternalFileProxy[0]->EpcExternalPartReference);
	}

	throw std::logic_error("Not implemented yet");
}

void GridConnectionSetRepresentation::setCellIndexPairsUsingExistingDataset(ULONG64 cellIndexPairCount, const std::string & cellIndexPair, LONG64 cellIndexPairNullValue, EML2_NS::AbstractHdfProxy * proxy, LONG64 gridIndexPairNullValue, const std::string & gridIndexPair)
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

	_resqml22__GridConnectionSetRepresentation* const rep = static_cast<_resqml22__GridConnectionSetRepresentation* const>(gsoapProxy2_3);
	rep->Count = cellIndexPairCount;

	// XML cell index pair
	eml23__IntegerExternalArray* const integerArray = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	eml23__ExternalDataset * resqmlHDF5dataset = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	auto dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = cellIndexPair;
	integerArray->Values = resqmlHDF5dataset;
	integerArray->NullValue = cellIndexPairNullValue;
	resqmlHDF5dataset->ExternalFileProxy.push_back(dsPart);
	rep->CellIndexPairs = integerArray;

	// XML grid index pair
	if (!gridIndexPair.empty()) {
		eml23__IntegerExternalArray* const gridIndexPairArray = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
		eml23__ExternalDataset * const gridIndexPairDataset = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
		dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
		dsPart->EpcExternalPartReference = proxy->newEml23Reference();
		dsPart->PathInExternalFile = gridIndexPair;
		gridIndexPairArray->Values = gridIndexPairDataset;
		gridIndexPairArray->NullValue = gridIndexPairNullValue;
		gridIndexPairDataset->ExternalFileProxy.push_back(dsPart);
		rep->GridIndexPairs = gridIndexPairArray;
	}
}

void GridConnectionSetRepresentation::setLocalFacePerCellIndexPairsUsingExistingDataset(const std::string & localFacePerCellIndexPair, LONG64 nullValue, EML2_NS::AbstractHdfProxy * proxy)
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
	eml23__ExternalDataset * resqmlHDF5dataset = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	auto dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = localFacePerCellIndexPair;
	integerArray->Values = resqmlHDF5dataset;
	integerArray->NullValue = nullValue;
	resqmlHDF5dataset->ExternalFileProxy.push_back(dsPart);
	rep->LocalFacePerCellIndexPairs = integerArray;
}

bool GridConnectionSetRepresentation::isAssociatedToInterpretations() const
{
	return static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3)->ConnectionInterpretations != nullptr;
}

void GridConnectionSetRepresentation::getInterpretationIndexCumulativeCount(unsigned int * cumulativeCount) const
{
	if (isAssociatedToInterpretations()) {		
		_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);
		if (rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			eml23__ExternalDatasetPart* dsPart =  static_cast<eml23__IntegerExternalArray*>(rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength)->Values->ExternalFileProxy[0];
			getHdfProxyFromDataset(dsPart)->readArrayNdOfUIntValues(dsPart->PathInExternalFile, cumulativeCount);
		}
		else {
			throw std::logic_error("Not implemented yet");
		}
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
			eml23__ExternalDatasetPart* dsPart = static_cast<eml23__IntegerExternalArray*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values->ExternalFileProxy[0];
			getHdfProxyFromDataset(dsPart)->readArrayNdOfUIntValues(dsPart->PathInExternalFile, interpretationIndices);
		}
		else {
			throw std::logic_error("Not implemented yet");
		}
	}
	else {
		throw std::invalid_argument("The grid connection does not contain any (fault) interpretation association.");
	}
}

LONG64 GridConnectionSetRepresentation::getInterpretationIndexNullValue() const
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

ULONG64 GridConnectionSetRepresentation::getCellIndexPairCount() const
{
	return static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3)->Count;
}

unsigned int GridConnectionSetRepresentation::getCellIndexPairCountFromInterpretationIndex(unsigned int interpretationIndex) const
{
	if (interpretationIndex >= getInterpretationCount()) {
		throw out_of_range("The interpretation index is out of range.");
	}
	
	unsigned int result = 0;
	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);

	if (rep->ConnectionInterpretations != nullptr)
	{
		if (rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray)
		{
			auto dsPart = static_cast<eml23__IntegerExternalArray*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values->ExternalFileProxy[0];
			auto hdfProxy = getHdfProxyFromDataset(dsPart);
			const signed long long faultIndexCount = getHdfProxyFromDataset(dsPart)->getElementCount(dsPart->PathInExternalFile);
			if (faultIndexCount < 0) {
				throw invalid_argument("The HDF5 library could not read the element count of this dataset.");
			}
			std::unique_ptr<unsigned int[]> faultIndices(new unsigned int[static_cast<size_t>(faultIndexCount)]);

			hdfProxy->readArrayNdOfUIntValues(dsPart->PathInExternalFile, faultIndices.get());
			for (size_t i = 0; i < static_cast<size_t>(faultIndexCount); ++i) {
				if (faultIndices[i] == interpretationIndex) {
					result++;
				}
			}
		}
		else {
			throw std::logic_error("Not implemented yet");
		}
	}
	else {
		throw invalid_argument("The grid connection does not contain any (fault) interpretation association."); 
	}

	return result;
}

void GridConnectionSetRepresentation::getGridConnectionSetInformationFromInterpretationIndex(ULONG64 * cellIndexPairs, unsigned short * gridIndexPairs, int * localFaceIndexPairs, unsigned int interpretationIndex) const
{
	//load global information into memory
	const ULONG64 totalCellIndexPairCount = getCellIndexPairCount();
	std::unique_ptr<ULONG64[]> const totalCellIndexPairs(new ULONG64[totalCellIndexPairCount*2]);
	getCellIndexPairs(totalCellIndexPairs.get());
	std::unique_ptr<unsigned short[]> totalGridIndexPairs;
	if (gridIndexPairs != nullptr)
	{
		totalGridIndexPairs = std::unique_ptr<unsigned short[]>(new unsigned short[totalCellIndexPairCount * 2]);
		getGridIndexPairs(totalGridIndexPairs.get());
	}
	std::unique_ptr<int[]> totalLocalFaceIndexPairs;
	if (localFaceIndexPairs != nullptr)
	{
		totalLocalFaceIndexPairs = std::unique_ptr<int[]>(new int[totalCellIndexPairCount*2]);
		getLocalFacePerCellIndexPairs(totalLocalFaceIndexPairs.get());
	}

	_resqml22__GridConnectionSetRepresentation* const rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);

	if (rep->ConnectionInterpretations != nullptr)
	{
		// Get the fault indices information
		std::unique_ptr<unsigned int[]> cumulativeCount = nullptr;
		if (rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray)
		{
			cumulativeCount = std::unique_ptr<unsigned int[]>(new unsigned int[totalCellIndexPairCount]);
			eml23__ExternalDatasetPart* dsPart = static_cast<eml23__IntegerExternalArray*>(rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength)->Values->ExternalFileProxy[0];
			getHdfProxyFromDataset(dsPart)->readArrayNdOfUIntValues(dsPart->PathInExternalFile, cumulativeCount.get());
		}
		else
		{
			throw std::logic_error("Not yet implemented");
		}

		std::unique_ptr<unsigned int[]> faultIndices = nullptr;
		if (rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray)
		{
			faultIndices = std::unique_ptr<unsigned int[]>(new unsigned int[cumulativeCount[totalCellIndexPairCount-1]]);
			eml23__ExternalDatasetPart* dsPart = static_cast<eml23__IntegerExternalArray*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values->ExternalFileProxy[0];
			getHdfProxyFromDataset(dsPart)->readArrayNdOfUIntValues(dsPart->PathInExternalFile, faultIndices.get());
		}
		else
		{
			throw std::logic_error("Not yet implemented");
		}

		// Based on the fault indices information, construct the required subset of information
		size_t cellIndexPairIndex = 0;
		unsigned int j = 0;
		for (unsigned int i = 0; i < totalCellIndexPairCount; ++i)
		{
			for (; j < cumulativeCount[i]; ++j)
			{
				if (faultIndices[j] == interpretationIndex)
				{
					cellIndexPairs[cellIndexPairIndex*2] = totalCellIndexPairs[i*2];
					cellIndexPairs[cellIndexPairIndex*2+1] = totalCellIndexPairs[i*2+1];
					if (gridIndexPairs != nullptr)
					{
						gridIndexPairs[cellIndexPairIndex*2] = totalGridIndexPairs[i*2];
						gridIndexPairs[cellIndexPairIndex*2+1] = totalGridIndexPairs[i*2+1];
					}
					if (localFaceIndexPairs != nullptr)
					{
						localFaceIndexPairs[cellIndexPairIndex*2] = totalLocalFaceIndexPairs[i*2];
						localFaceIndexPairs[cellIndexPairIndex*2+1] = totalLocalFaceIndexPairs[i*2+1];
					}
					++cellIndexPairIndex;
					break;
				}
			}
		}
	}
	else
	{
		throw invalid_argument("The grid connection does not contain any (fault) interpretation association."); 
	}
}

std::string GridConnectionSetRepresentation::getInterpretationUuidFromIndex(unsigned int interpretationIndex) const
{
	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);

	if (rep->ConnectionInterpretations != nullptr) {
		if (rep->ConnectionInterpretations->FeatureInterpretation.size() > interpretationIndex) {
			if (rep->ConnectionInterpretations->FeatureInterpretation[interpretationIndex]->ContentType.find("FaultInterpretation") != string::npos) {
				return rep->ConnectionInterpretations->FeatureInterpretation[interpretationIndex]->Uuid;
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

ULONG64 GridConnectionSetRepresentation::getCellIndexPairs(ULONG64 * cellIndexPairs) const
{
	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);

	if (rep->CellIndexPairs->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		eml23__ExternalDatasetPart * dsPart = static_cast<eml23__IntegerExternalArray*>(rep->CellIndexPairs)->Values->ExternalFileProxy[0];
		getHdfProxyFromDataset(dsPart)->readArrayNdOfULongValues(dsPart->PathInExternalFile, cellIndexPairs);
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
		eml23__ExternalDatasetPart * dsPart = static_cast<eml23__IntegerExternalArray*>(rep->GridIndexPairs)->Values->ExternalFileProxy[0];
		getHdfProxyFromDataset(dsPart)->readArrayNdOfUShortValues(dsPart->PathInExternalFile, gridIndexPairs);
	}
	else {
		throw std::logic_error("Not implemented yet");
	}
}

bool GridConnectionSetRepresentation::hasLocalFacePerCell() const
{
	return static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3)->LocalFacePerCellIndexPairs != nullptr;
}

LONG64 GridConnectionSetRepresentation::getLocalFacePerCellIndexPairs(int * localFaceCellIndexPairs) const
{
	if (!hasLocalFacePerCell()) {
		throw std::invalid_argument("This representation has no local face per cell.");
	}

	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);

	if (rep->LocalFacePerCellIndexPairs->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		eml23__ExternalDatasetPart * dsPart = static_cast<eml23__IntegerExternalArray*>(rep->LocalFacePerCellIndexPairs)->Values->ExternalFileProxy[0];
		getHdfProxyFromDataset(dsPart)->readArrayNdOfIntValues(dsPart->PathInExternalFile, localFaceCellIndexPairs);
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
void GridConnectionSetRepresentation::setConnectionInterpretationIndices(unsigned int const * interpretationIndices, unsigned int interpretationIndiceCount, unsigned int nullValue, EML2_NS::AbstractHdfProxy * proxy)
{
	getRepository()->addRelationship(this, proxy);

	_resqml22__GridConnectionSetRepresentation* rep = static_cast<_resqml22__GridConnectionSetRepresentation*>(gsoapProxy2_3);
	if (rep->ConnectionInterpretations == nullptr) {
		rep->ConnectionInterpretations = soap_new_resqml22__ConnectionInterpretations(gsoapProxy2_3->soap);
	}
	rep->ConnectionInterpretations->InterpretationIndices = soap_new_eml23__JaggedArray(gsoapProxy2_3->soap);
	
	// Cumulative
	eml23__IntegerExternalArray* cumulativeLength = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength = cumulativeLength;
	cumulativeLength->NullValue = nullValue;
	cumulativeLength->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	auto dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = getHdfGroup() + "/InterpretationIndices/" + CUMULATIVE_LENGTH_DS_NAME;
	cumulativeLength->Values->ExternalFileProxy.push_back(dsPart);
	// Elements
	eml23__IntegerExternalArray* elements = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	rep->ConnectionInterpretations->InterpretationIndices->Elements = elements;
	elements->NullValue = nullValue;
	elements->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = getHdfGroup() + "/InterpretationIndices/" + ELEMENTS_DS_NAME;
	elements->Values->ExternalFileProxy.push_back(dsPart);

	// HDF
	std::unique_ptr<unsigned int[]> cumulative(new unsigned int[interpretationIndiceCount]);
	for (unsigned int i = 0; i < interpretationIndiceCount; ++i) {
		cumulative[i] = i + 1;
	}
	proxy->writeItemizedListOfList(getHdfGroup(), "InterpretationIndices", H5T_NATIVE_UINT, cumulative.get(), interpretationIndiceCount, H5T_NATIVE_UINT, interpretationIndices, interpretationIndiceCount);
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
