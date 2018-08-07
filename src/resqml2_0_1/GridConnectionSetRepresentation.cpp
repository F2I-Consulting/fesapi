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
#include "resqml2_0_1/GridConnectionSetRepresentation.h"

#include <algorithm>
#if defined(__gnu_linux__) || defined(__APPLE__) 
#include <stdexcept>
#endif 

#include "hdf5.h"

#include "resqml2_0_1/FaultInterpretation.h"
#include "resqml2/AbstractGridRepresentation.h"
#include "common/AbstractHdfProxy.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"

#include "tools/Misc.h"

using namespace std;
using namespace epc;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

void GridConnectionSetRepresentation::init(soap* soapContext, const std::string & guid, const std::string & title)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREGridConnectionSetRepresentation(soapContext, 1);

    initMandatoryMetadata();
    setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

GridConnectionSetRepresentation::GridConnectionSetRepresentation(soap* soapContext,
	const std::string & guid, const std::string & title):
	RESQML2_NS::GridConnectionSetRepresentation(static_cast<RESQML2_NS::AbstractFeatureInterpretation*>(nullptr))
{
	init(soapContext, guid, title);
}

GridConnectionSetRepresentation::GridConnectionSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const string & guid, const string & title):
	RESQML2_NS::GridConnectionSetRepresentation(interp)
{
	init(interp->getGsoapContext(), guid, title);

	if (interp != nullptr) {
		setInterpretation(interp);
	}
}

string GridConnectionSetRepresentation::getHdfProxyUuid() const
{
	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (rep->CellIndexPairs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
		return static_cast<resqml2__IntegerHdf5Array*>(rep->CellIndexPairs)->Values->HdfProxy->UUID;
	}

	throw std::logic_error("Not implemented yet");
}

void GridConnectionSetRepresentation::setCellIndexPairsUsingExistingDataset(const ULONG64 & cellIndexPairCount, const std::string & cellIndexPair, const LONG64 & nullValue, COMMON_NS::AbstractHdfProxy * proxy, const std::string & gridIndexPair)
{
	if (cellIndexPairCount == 0) {
		throw std::invalid_argument("You cannot set zero cell index pair.");
	}
	_resqml2__GridConnectionSetRepresentation* const rep = static_cast<_resqml2__GridConnectionSetRepresentation* const>(gsoapProxy2_0_1);
	rep->Count = cellIndexPairCount;

	setHdfProxy(proxy);

	// XML cell index pair
	resqml2__IntegerHdf5Array* const integerArray = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	eml20__Hdf5Dataset * const resqmlHDF5dataset = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	resqmlHDF5dataset->HdfProxy = hdfProxy->newResqmlReference();
	resqmlHDF5dataset->PathInHdfFile = cellIndexPair;
	integerArray->Values = resqmlHDF5dataset;
	integerArray->NullValue = nullValue;
	rep->CellIndexPairs = integerArray;

	// XML grid index pair
	if (!gridIndexPair.empty()) {
		resqml2__IntegerHdf5Array* const gridIndexPairArray = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
		eml20__Hdf5Dataset * const gridIndexPairDataset = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
		gridIndexPairDataset->HdfProxy = hdfProxy->newResqmlReference();
		gridIndexPairDataset->PathInHdfFile = gridIndexPair;
		gridIndexPairArray->Values = gridIndexPairDataset;
		gridIndexPairArray->NullValue = nullValue;
		rep->GridIndexPairs = gridIndexPairArray;
	}
}

void GridConnectionSetRepresentation::setLocalFacePerCellIndexPairsUsingExistingDataset(const std::string & localFacePerCellIndexPair, const LONG64 & nullValue, COMMON_NS::AbstractHdfProxy * proxy)
{
	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	setHdfProxy(proxy);

	// XML
	resqml2__IntegerHdf5Array* integerArray = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	eml20__Hdf5Dataset * resqmlHDF5dataset = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	resqmlHDF5dataset->HdfProxy = hdfProxy->newResqmlReference();
	resqmlHDF5dataset->PathInHdfFile = localFacePerCellIndexPair;
	integerArray->Values = resqmlHDF5dataset;
	integerArray->NullValue = nullValue;
	rep->LocalFacePerCellIndexPairs = integerArray;
}

void GridConnectionSetRepresentation::setLocalFacePerCellIndexPairs(const ULONG64 & cellIndexPairCount, int * localFacePerCellIndexPair, const LONG64 & nullValue, COMMON_NS::AbstractHdfProxy * proxy)
{
	const std::string uuid = getUuid();
	setLocalFacePerCellIndexPairsUsingExistingDataset("/RESQML/" + uuid + "/LocalFacePerCellIndexPairs", nullValue, proxy);

	// ************ HDF ************		
	hsize_t numValues[] = {cellIndexPairCount,2};
	hdfProxy->writeArrayNd(uuid, "LocalFacePerCellIndexPairs", H5T_NATIVE_INT, localFacePerCellIndexPair, numValues, 2);
}

bool GridConnectionSetRepresentation::isAssociatedToInterpretations() const
{
	return static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->ConnectionInterpretations != nullptr;
}

void GridConnectionSetRepresentation::getInterpretationIndexCumulativeCount(unsigned int * cumulativeCount) const
{
	if (isAssociatedToInterpretations()) {		
		_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
		if (rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
			hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength)->Values->PathInHdfFile, cumulativeCount);
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
		_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
		if (rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
			hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values->PathInHdfFile, interpretationIndices);
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
		_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
		if (rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
			return static_cast<resqml2__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->NullValue;
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
	return static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->Count;
}

unsigned int GridConnectionSetRepresentation::getCellIndexPairCountFromInterpretationIndex(const unsigned int & interpretationIndex) const
{
	unsigned int result = 0;
	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (rep->ConnectionInterpretations)
	{
		if (rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			const unsigned int faultIndexCount = hdfProxy->getElementCount(static_cast<resqml2__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values->PathInHdfFile);
			unsigned int * const faultIndices = new unsigned int[faultIndexCount];

			hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values->PathInHdfFile, faultIndices);
			for (unsigned int i = 0; i < faultIndexCount; ++i) {
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

void GridConnectionSetRepresentation::getGridConnectionSetInformationFromInterpretationIndex(ULONG64 * cellIndexPairs, unsigned short * gridIndexPairs, int * localFaceIndexPairs, const unsigned int & interpretationIndex) const
{
	unsigned int result = 0;

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

	_resqml2__GridConnectionSetRepresentation* const rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (rep->ConnectionInterpretations != nullptr)
	{
		// Get the fault indices information
		unsigned int * cumulativeCount = nullptr;
		if (rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			cumulativeCount = new unsigned int[totalCellIndexPairCount];
			hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength)->Values->PathInHdfFile, cumulativeCount);
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
		if (rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			faultIndices = new unsigned int[cumulativeCount[totalCellIndexPairCount-1]];
			hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values->PathInHdfFile, faultIndices);
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

std::string GridConnectionSetRepresentation::getInterpretationUuidFromIndex(const unsigned int & interpretationIndex) const
{
	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

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
	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (rep->ConnectionInterpretations != nullptr) {
		return rep->ConnectionInterpretations->FeatureInterpretation.size();
	}

	return 0;
}

ULONG64 GridConnectionSetRepresentation::getCellIndexPairs(ULONG64 * cellIndexPairs) const
{
	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (rep->CellIndexPairs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
		hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(rep->CellIndexPairs)->Values->PathInHdfFile, cellIndexPairs);
		return static_cast<resqml2__IntegerHdf5Array*>(rep->CellIndexPairs)->NullValue;
	}
	else {
		throw std::logic_error("Not yet implemented");
	}
}

bool GridConnectionSetRepresentation::isBasedOnMultiGrids() const 
{
	return static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->GridIndexPairs != nullptr && 
		static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->Grid.size() > 1;
}

void GridConnectionSetRepresentation::getGridIndexPairs(unsigned short * gridIndexPairs) const
{
	if (!isBasedOnMultiGrids()) {
		throw std::invalid_argument("This representation has no multiple grid support.");
	}

	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (rep->GridIndexPairs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
		hdfProxy->readArrayNdOfUShortValues(static_cast<resqml2__IntegerHdf5Array*>(rep->GridIndexPairs)->Values->PathInHdfFile, gridIndexPairs);
	}
	else {
		throw std::logic_error("Not implemented yet");
	}
}

bool GridConnectionSetRepresentation::hasLocalFacePerCell() const
{
	return static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->LocalFacePerCellIndexPairs != nullptr;
}

LONG64 GridConnectionSetRepresentation::getLocalFacePerCellIndexPairs(int * localFaceCellIndexPairs) const
{
	if (!hasLocalFacePerCell()) {
		throw std::invalid_argument("This representation has no local face per cell.");
	}

	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (rep->LocalFacePerCellIndexPairs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
		hdfProxy->readArrayNdOfIntValues(static_cast<resqml2__IntegerHdf5Array*>(rep->LocalFacePerCellIndexPairs)->Values->PathInHdfFile, localFaceCellIndexPairs);
		return static_cast<resqml2__IntegerHdf5Array*>(rep->LocalFacePerCellIndexPairs)->NullValue;
	}
	else {
		throw std::logic_error("Not implemented yet");
	}
}

void GridConnectionSetRepresentation::pushBackXmlSupportingGridRepresentation(RESQML2_NS::AbstractGridRepresentation * supportingGridRep)
{
	static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->Grid.push_back(supportingGridRep->newResqmlReference());
}

void GridConnectionSetRepresentation::setConnectionInterpretationIndices(unsigned int * interpretationIndices, const unsigned int & interpretationIndiceCount, const LONG64 & nullValue, COMMON_NS::AbstractHdfProxy * proxy)
{
	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
	if (rep->ConnectionInterpretations == nullptr) {
		rep->ConnectionInterpretations = soap_new_resqml2__ConnectionInterpretations(gsoapProxy2_0_1->soap, 1);
	}
	rep->ConnectionInterpretations->InterpretationIndices = soap_new_resqml2__ResqmlJaggedArray(gsoapProxy2_0_1->soap, 1);
	
	// Cumulative
	resqml2__IntegerHdf5Array* cumulativeLength = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength = cumulativeLength;
	cumulativeLength->NullValue = nullValue;
	cumulativeLength->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	cumulativeLength->Values->HdfProxy = proxy->newResqmlReference();
	cumulativeLength->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/InterpretationIndices/" + CUMULATIVE_LENGTH_DS_NAME;
	// Elements
	resqml2__IntegerHdf5Array* elements = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	rep->ConnectionInterpretations->InterpretationIndices->Elements = elements;
	elements->NullValue = nullValue;
	elements->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	elements->Values->HdfProxy = proxy->newResqmlReference();
	elements->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/InterpretationIndices/" + ELEMENTS_DS_NAME;

	// HDF
	unsigned int * cumulative = new unsigned int[interpretationIndiceCount];
	for (unsigned int i = 0; i < interpretationIndiceCount; ++i) {
		cumulative[i] = i + 1;
	}
	hdfProxy->writeItemizedListOfList(gsoapProxy2_0_1->uuid, "InterpretationIndices", H5T_NATIVE_UINT, cumulative, interpretationIndiceCount, H5T_NATIVE_UINT, interpretationIndices, interpretationIndiceCount);
	delete [] cumulative;
}

void GridConnectionSetRepresentation::pushBackXmlInterpretation(RESQML2_NS::AbstractFeatureInterpretation* interp)
{
	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
	if (rep->ConnectionInterpretations == nullptr) {
		rep->ConnectionInterpretations = soap_new_resqml2__ConnectionInterpretations(gsoapProxy2_0_1->soap, 1);
	}

	rep->ConnectionInterpretations->FeatureInterpretation.push_back(interp->newResqmlReference());
}

unsigned int GridConnectionSetRepresentation::getSupportingGridRepresentationCount() const
{
	return static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->Grid.size(); 
}

gsoap_resqml2_0_1::eml20__DataObjectReference* GridConnectionSetRepresentation::getSupportingGridRepresentationDor(unsigned int index) const
{
	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (index >= rep->Grid.size()) {
		throw range_error("The requested index is out of range of the available supporting grid representations.");
	}
	return rep->Grid[index];
}

