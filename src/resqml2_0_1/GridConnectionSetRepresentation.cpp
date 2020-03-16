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
#if defined(__gnu_linux__) || defined(__APPLE__) 
#include <stdexcept>
#endif 

#include <hdf5.h>

#include "FaultInterpretation.h"
#include "../resqml2/AbstractGridRepresentation.h"
#include "../common/AbstractHdfProxy.h"
#include "../resqml2/AbstractLocal3dCrs.h"
#include "StructuralOrganizationInterpretation.h"

#include "../tools/Misc.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

void GridConnectionSetRepresentation::init(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title)
{
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREGridConnectionSetRepresentation(repo->getGsoapContext());

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
	_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (rep->CellIndexPairs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		return COMMON_NS::DataObjectReference(static_cast<resqml20__IntegerHdf5Array*>(rep->CellIndexPairs)->Values->HdfProxy);
	}

	throw std::logic_error("Not implemented yet");
}

void GridConnectionSetRepresentation::setCellIndexPairsUsingExistingDataset(ULONG64 cellIndexPairCount, const std::string & cellIndexPair, LONG64 cellIndexPairNullValue, COMMON_NS::AbstractHdfProxy * proxy, LONG64 gridIndexPairNullValue, const std::string & gridIndexPair)
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

	_resqml20__GridConnectionSetRepresentation* const rep = static_cast<_resqml20__GridConnectionSetRepresentation* const>(gsoapProxy2_0_1);
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

void GridConnectionSetRepresentation::setLocalFacePerCellIndexPairsUsingExistingDataset(const std::string & localFacePerCellIndexPair, LONG64 nullValue, COMMON_NS::AbstractHdfProxy * proxy)
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

void GridConnectionSetRepresentation::setLocalFacePerCellIndexPairs(ULONG64 cellIndexPairCount, int * localFacePerCellIndexPair, int nullValue, COMMON_NS::AbstractHdfProxy * proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	setLocalFacePerCellIndexPairsUsingExistingDataset(getHdfGroup() + "/LocalFacePerCellIndexPairs", nullValue, proxy);

	// ************ HDF ************		
	hsize_t numValues[2] = {cellIndexPairCount,2};
	proxy->writeArrayNd(getHdfGroup(), "LocalFacePerCellIndexPairs", H5T_NATIVE_INT, localFacePerCellIndexPair, numValues, 2);
}

bool GridConnectionSetRepresentation::isAssociatedToInterpretations() const
{
	return static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->ConnectionInterpretations != nullptr;
}

void GridConnectionSetRepresentation::getInterpretationIndexCumulativeCount(unsigned int * cumulativeCount) const
{
	if (isAssociatedToInterpretations()) {		
		_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
		if (rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			eml20__Hdf5Dataset* dataset =  static_cast<resqml20__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength)->Values;
			getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID)->readArrayNdOfUIntValues(dataset->PathInHdfFile, cumulativeCount);
		}
		else {
			throw std::logic_error("Not implemented yet");
		}
	}
	else {
		throw std::invalid_argument("There are no fault associated to the cell connections.");
	}
}

void GridConnectionSetRepresentation::getInterpretationIndices(unsigned int * interpretationIndices) const
{
	if (isAssociatedToInterpretations()) {
		_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
		if (rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			eml20__Hdf5Dataset* dataset = static_cast<resqml20__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values;
			getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID)->readArrayNdOfUIntValues(dataset->PathInHdfFile, interpretationIndices);
		}
		else {
			throw std::logic_error("Not implemented yet");
		}
	}
	else {
		throw std::invalid_argument("There are no fault associated to the cell connections.");
	}
}

LONG64 GridConnectionSetRepresentation::getInterpretationIndexNullValue() const
{
	if (isAssociatedToInterpretations()) {
		_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
		if (rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			return static_cast<resqml20__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->NullValue;
		}
		else {
			throw std::logic_error("Not implemented yet");
		}
	}
	else {
		throw std::invalid_argument("There are no fault associated to the cell connections.");
	}
}

ULONG64 GridConnectionSetRepresentation::getCellIndexPairCount() const
{
	return static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->Count;
}

unsigned int GridConnectionSetRepresentation::getCellIndexPairCountFromInterpretationIndex(unsigned int interpretationIndex) const
{
	unsigned int result = 0;
	_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (rep->ConnectionInterpretations != nullptr)
	{
		if (rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
		{
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values;
			COMMON_NS::AbstractHdfProxy * hdfProxy = getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
			const signed long long faultIndexCount = hdfProxy->getElementCount(dataset->PathInHdfFile);
			if (faultIndexCount < 0) {
				throw invalid_argument("The HDF5 library could not read the element count of this dataset.");
			}
			unsigned int * const faultIndices = new unsigned int[static_cast<size_t>(faultIndexCount)];

			hdfProxy->readArrayNdOfUIntValues(dataset->PathInHdfFile, faultIndices);
			for (size_t i = 0; i < static_cast<size_t>(faultIndexCount); ++i) {
				if (faultIndices[i] == interpretationIndex) {
					result++;
				}
			}

			delete [] faultIndices;
		}
		else {
			throw std::logic_error("Not yet implemented");
		}
	}
	else {
		throw invalid_argument("The grid connection does not contain any fault association."); 
	}

	return result;
}

void GridConnectionSetRepresentation::getGridConnectionSetInformationFromInterpretationIndex(ULONG64 * cellIndexPairs, unsigned short * gridIndexPairs, int * localFaceIndexPairs, unsigned int interpretationIndex) const
{
	//load global information into memory
	const ULONG64 totalCellIndexPairCount = getCellIndexPairCount();
	ULONG64 * const totalCellIndexPairs = new ULONG64[totalCellIndexPairCount*2];
	getCellIndexPairs(totalCellIndexPairs);
	unsigned short * totalGridIndexPairs = nullptr;
	if (gridIndexPairs != nullptr)
	{
		totalGridIndexPairs = new unsigned short[totalCellIndexPairCount * 2];
		getGridIndexPairs(totalGridIndexPairs);
	}
	int * totalLocalFaceIndexPairs = nullptr;
	if (localFaceIndexPairs != nullptr)
	{
		totalLocalFaceIndexPairs = new int[totalCellIndexPairCount*2];
		getLocalFacePerCellIndexPairs(totalLocalFaceIndexPairs);
	}

	_resqml20__GridConnectionSetRepresentation* const rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (rep->ConnectionInterpretations != nullptr)
	{
		// Get the fault indices information
		unsigned int * cumulativeCount = nullptr;
		if (rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
		{
			cumulativeCount = new unsigned int[totalCellIndexPairCount];
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength)->Values;
			getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID)->readArrayNdOfUIntValues(dataset->PathInHdfFile, cumulativeCount);
		}
		else
		{
			if (totalGridIndexPairs != nullptr) {
				delete[] totalGridIndexPairs;
			}
			if (totalLocalFaceIndexPairs != nullptr) {
				delete[] totalLocalFaceIndexPairs;
			}
			delete [] totalCellIndexPairs;
			throw std::logic_error("Not yet implemented");
		}

		unsigned int * faultIndices = nullptr;
		if (rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
		{
			faultIndices = new unsigned int[cumulativeCount[totalCellIndexPairCount-1]];
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values;
			getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID)->readArrayNdOfUIntValues(dataset->PathInHdfFile, faultIndices);
		}
		else
		{
			delete [] cumulativeCount;
			if (totalGridIndexPairs != nullptr) {
				delete[] totalGridIndexPairs;
			}
			if (totalLocalFaceIndexPairs != nullptr) {
				delete[] totalLocalFaceIndexPairs;
			}
			delete [] totalCellIndexPairs;
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

		delete [] faultIndices;
		delete [] cumulativeCount;
	}
	else
	{
		if (totalGridIndexPairs != nullptr) {
			delete[] totalGridIndexPairs;
		}
		if (totalLocalFaceIndexPairs != nullptr) {
			delete[] totalLocalFaceIndexPairs;
		}
		delete [] totalCellIndexPairs;
		throw invalid_argument("The grid connection does not contain any fault association."); 
	}
	
	if (totalGridIndexPairs != nullptr) {
		delete[] totalGridIndexPairs;
	}
	if (totalLocalFaceIndexPairs != nullptr) {
		delete[] totalLocalFaceIndexPairs;
	}
	delete [] totalCellIndexPairs;
}

std::string GridConnectionSetRepresentation::getInterpretationUuidFromIndex(unsigned int interpretationIndex) const
{
	_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (rep->ConnectionInterpretations != nullptr) {
		if (rep->ConnectionInterpretations->FeatureInterpretation.size() > interpretationIndex) {
			if (rep->ConnectionInterpretations->FeatureInterpretation[interpretationIndex]->ContentType.find("FaultInterpretation") != string::npos) {
				return rep->ConnectionInterpretations->FeatureInterpretation[interpretationIndex]->UUID;
			}
			else {
				throw invalid_argument("The associated feature interpretation is not a fault one. Legal but not yet implemented.");
			}
		}
		else {
			throw range_error("The fault index is out of range in this grid connection context.");
		}
	}
	else {
		throw invalid_argument("The grid connection does not contain any fault association.");
	}
}

unsigned int GridConnectionSetRepresentation::getInterpretationCount() const
{
	_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (rep->ConnectionInterpretations != nullptr) {
		const size_t result = rep->ConnectionInterpretations->FeatureInterpretation.size();

		if (result > (numeric_limits<unsigned int>::max)()) {
			throw out_of_range("There are too many associated interpretations.");
		}

		return static_cast<unsigned int>(result);
	}

	return 0;
}

ULONG64 GridConnectionSetRepresentation::getCellIndexPairs(ULONG64 * cellIndexPairs) const
{
	_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (rep->CellIndexPairs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(rep->CellIndexPairs)->Values;
		getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID)->readArrayNdOfULongValues(dataset->PathInHdfFile, cellIndexPairs);
		return static_cast<resqml20__IntegerHdf5Array*>(rep->CellIndexPairs)->NullValue;
	}
	else {
		throw std::logic_error("Not yet implemented");
	}
}

bool GridConnectionSetRepresentation::isBasedOnMultiGrids() const 
{
	return static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->GridIndexPairs != nullptr && 
		static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->Grid.size() > 1;
}

void GridConnectionSetRepresentation::getGridIndexPairs(unsigned short * gridIndexPairs) const
{
	if (!isBasedOnMultiGrids()) {
		throw std::invalid_argument("This representation has no multiple grid support.");
	}

	_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (rep->GridIndexPairs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(rep->GridIndexPairs)->Values;
		getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID)->readArrayNdOfUShortValues(dataset->PathInHdfFile, gridIndexPairs);
	}
	else {
		throw std::logic_error("Not implemented yet");
	}
}

bool GridConnectionSetRepresentation::hasLocalFacePerCell() const
{
	return static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->LocalFacePerCellIndexPairs != nullptr;
}

LONG64 GridConnectionSetRepresentation::getLocalFacePerCellIndexPairs(int * localFaceCellIndexPairs) const
{
	if (!hasLocalFacePerCell()) {
		throw std::invalid_argument("This representation has no local face per cell.");
	}

	_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (rep->LocalFacePerCellIndexPairs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(rep->LocalFacePerCellIndexPairs)->Values;
		getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID)->readArrayNdOfIntValues(dataset->PathInHdfFile, localFaceCellIndexPairs);
		return static_cast<resqml20__IntegerHdf5Array*>(rep->LocalFacePerCellIndexPairs)->NullValue;
	}
	else {
		throw std::logic_error("Not implemented yet");
	}
}

void GridConnectionSetRepresentation::pushBackXmlSupportingGridRepresentation(RESQML2_NS::AbstractGridRepresentation * supportingGridRep)
{
	static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->Grid.push_back(supportingGridRep->newResqmlReference());
}

void GridConnectionSetRepresentation::setConnectionInterpretationIndices(unsigned int * interpretationIndices, unsigned int interpretationIndiceCount, unsigned int nullValue, COMMON_NS::AbstractHdfProxy * proxy)
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
	cumulativeLength->NullValue = nullValue;
	cumulativeLength->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	cumulativeLength->Values->HdfProxy = proxy->newResqmlReference();
	cumulativeLength->Values->PathInHdfFile = getHdfGroup() + "/InterpretationIndices/" + CUMULATIVE_LENGTH_DS_NAME;
	// Elements
	resqml20__IntegerHdf5Array* elements = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	rep->ConnectionInterpretations->InterpretationIndices->Elements = elements;
	elements->NullValue = nullValue;
	elements->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	elements->Values->HdfProxy = proxy->newResqmlReference();
	elements->Values->PathInHdfFile = getHdfGroup() + "/InterpretationIndices/" + ELEMENTS_DS_NAME;

	// HDF
	std::unique_ptr<unsigned int[]> cumulative(new unsigned int[interpretationIndiceCount]);
	for (unsigned int i = 0; i < interpretationIndiceCount; ++i) {
		cumulative[i] = i + 1;
	}
	proxy->writeItemizedListOfList(getHdfGroup(), "InterpretationIndices", H5T_NATIVE_UINT, cumulative.get(), interpretationIndiceCount, H5T_NATIVE_UINT, interpretationIndices, interpretationIndiceCount);
}

void GridConnectionSetRepresentation::pushBackXmlInterpretation(RESQML2_NS::AbstractFeatureInterpretation* interp)
{
	_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
	if (rep->ConnectionInterpretations == nullptr) {
		rep->ConnectionInterpretations = soap_new_resqml20__ConnectionInterpretations(gsoapProxy2_0_1->soap);
	}

	rep->ConnectionInterpretations->FeatureInterpretation.push_back(interp->newResqmlReference());
}

unsigned int GridConnectionSetRepresentation::getSupportingGridRepresentationCount() const
{
	const size_t result = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->Grid.size();

	if (result > (numeric_limits<unsigned int>::max)()) {
		throw out_of_range("There are too many supporting grid representations.");
	}

	return static_cast<unsigned int>(result);
}

COMMON_NS::DataObjectReference GridConnectionSetRepresentation::getSupportingGridRepresentationDor(unsigned int index) const
{
	_resqml20__GridConnectionSetRepresentation* rep = static_cast<_resqml20__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (index >= rep->Grid.size()) {
		throw range_error("The requested index is out of range of the available supporting grid representations.");
	}
	return COMMON_NS::DataObjectReference(rep->Grid[index]);
}
