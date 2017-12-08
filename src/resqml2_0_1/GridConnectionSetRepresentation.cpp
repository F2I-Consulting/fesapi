/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use,
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
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
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

void GridConnectionSetRepresentation::init(soap* soapContext, const std::string & guid, const std::string & title)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREGridConnectionSetRepresentation(soapContext, 1);
    _resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

    initMandatoryMetadata();
    setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

GridConnectionSetRepresentation::GridConnectionSetRepresentation(soap* soapContext,
	const std::string & guid, const std::string & title):
	resqml2::GridConnectionSetRepresentation(static_cast<resqml2::AbstractFeatureInterpretation*>(nullptr))
{
	init(soapContext, guid, title);
}

GridConnectionSetRepresentation::GridConnectionSetRepresentation(resqml2::AbstractFeatureInterpretation* interp,
	const string & guid, const string & title):
	resqml2::GridConnectionSetRepresentation(interp)
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

void GridConnectionSetRepresentation::setCellIndexPairsUsingExistingDataset(const ULONG64 & cellIndexPairCount, const std::string & cellIndexPair, const ULONG64 & nullValue, common::AbstractHdfProxy * proxy, const std::string & gridIndexPair)
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

void GridConnectionSetRepresentation::setLocalFacePerCellIndexPairsUsingExistingDataset(const std::string & localFacePerCellIndexPair, common::AbstractHdfProxy * proxy)
{
	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	setHdfProxy(proxy);

	// XML
	resqml2__IntegerHdf5Array* integerArray = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	eml20__Hdf5Dataset * resqmlHDF5dataset = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	resqmlHDF5dataset->HdfProxy = hdfProxy->newResqmlReference();
	resqmlHDF5dataset->PathInHdfFile = localFacePerCellIndexPair;
	integerArray->Values = resqmlHDF5dataset;
	integerArray->NullValue = -1;
	rep->LocalFacePerCellIndexPairs = integerArray;
}

void GridConnectionSetRepresentation::setLocalFacePerCellIndexPairs(const ULONG64 & cellIndexPairCount, int * localFacePerCellIndexPair, common::AbstractHdfProxy * proxy)
{
	const std::string uuid = getUuid();
	setLocalFacePerCellIndexPairsUsingExistingDataset("/RESQML/" + uuid + "/LocalFacePerCellIndexPairs", proxy);

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
			throw std::logic_error("Not yet implemented");
		}
	}

	throw std::invalid_argument("There are no fault associated to the cell connections.");
}

void GridConnectionSetRepresentation::getInterpretationIndices(unsigned int * interpretationIndices) const
{
	if (isAssociatedToInterpretations()) {
		_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
		if (rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
			hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values->PathInHdfFile, interpretationIndices);
		}
		else {
			throw std::logic_error("Not yet implemented");
		}
	}

	throw std::invalid_argument("There are no fault associated to the cell connections.");
}

LONG64 GridConnectionSetRepresentation::getInterpretationIndexNullValue() const
{
	if (isAssociatedToInterpretations()) {
		_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);
		if (rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
			return static_cast<resqml2__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->NullValue;
		}
		else {
			throw std::logic_error("Not yet implemented");
		}
	}

	throw std::invalid_argument("There are no fault associated to the cell connections.");
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

void GridConnectionSetRepresentation::getGridConnectionSetInformationFromInterpretationIndex(ULONG64 * cellIndexPairs, ULONG64 * gridIndexPairs, int * localFaceIndexPairs, const unsigned int & interpretationIndex) const
{
	unsigned int result = 0;

	//load global information into memory
	const ULONG64 totalCellIndexPairCount = getCellIndexPairCount();
	ULONG64 * const totalCellIndexPairs = new ULONG64[totalCellIndexPairCount*2];
	getCellIndexPairs(totalCellIndexPairs);
	ULONG64 * totalGridIndexPairs = nullptr;
	if (gridIndexPairs != nullptr)
	{
		totalGridIndexPairs = new ULONG64[totalCellIndexPairCount * 2];
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

void GridConnectionSetRepresentation::getGridIndexPairs(ULONG64 * gridIndexPairs) const
{
	if (!isBasedOnMultiGrids()) {
		throw std::invalid_argument("This representation has no multiple grid support.");
	}

	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (rep->GridIndexPairs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
		hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(rep->GridIndexPairs)->Values->PathInHdfFile, gridIndexPairs);
	}
	else {
		throw std::logic_error("Not yet implemented");
	}
}

bool GridConnectionSetRepresentation::hasLocalFacePerCell() const
{
	return static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->LocalFacePerCellIndexPairs != nullptr;
}

void GridConnectionSetRepresentation::getLocalFacePerCellIndexPairs(int * localFaceCellIndexPairs) const
{
	if (!hasLocalFacePerCell()) {
		throw std::invalid_argument("This representation has no local face per cell.");
	}

	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1);

	if (rep->LocalFacePerCellIndexPairs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
		hdfProxy->readArrayNdOfIntValues(static_cast<resqml2__IntegerHdf5Array*>(rep->LocalFacePerCellIndexPairs)->Values->PathInHdfFile, localFaceCellIndexPairs);
	}
	else {
		throw std::logic_error("Not yet implemented");
	}
}

void GridConnectionSetRepresentation::pushBackXmlSupportingGridRepresentation(resqml2::AbstractGridRepresentation * supportingGridRep)
{
	static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy2_0_1)->Grid.push_back(supportingGridRep->newResqmlReference());
}

void GridConnectionSetRepresentation::setConnectionInterpretationIndices(unsigned int * interpretationIndices, const unsigned int & interpretationIndiceCount, const ULONG64 & nullValue, common::AbstractHdfProxy * proxy)
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

void GridConnectionSetRepresentation::pushBackXmlInterpretation(resqml2::AbstractFeatureInterpretation* interp)
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
