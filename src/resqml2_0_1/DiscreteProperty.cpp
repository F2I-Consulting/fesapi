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
#include "resqml2_0_1/DiscreteProperty.h"

#include <sstream>
#include <stdexcept>

#include "hdf5.h"

#include "tools/Statistics.h"
#include "resqml2/AbstractRepresentation.h"
#include "resqml2/PropertyKind.h"
#include "common/AbstractHdfProxy.h"
#include "resqml2_0_1/PropertyKindMapper.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

const char* DiscreteProperty::XML_TAG = "DiscreteProperty";

DiscreteProperty::DiscreteProperty(resqml2::AbstractRepresentation * rep, const string & guid, const string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const resqml2__ResqmlPropertyKind & energisticsPropertyKind)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREDiscreteProperty(rep->getGsoapContext(), 1);	
	_resqml2__DiscreteProperty* prop = static_cast<_resqml2__DiscreteProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	resqml2__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml2__StandardPropertyKind(gsoapProxy2_0_1->soap, 1);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	prop->PropertyKind = xmlStandardPropKind;

	setRepresentation(rep);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

DiscreteProperty::DiscreteProperty(resqml2::AbstractRepresentation * rep, const string & guid, const string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, resqml2::PropertyKind * localPropKind)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREDiscreteProperty(rep->getGsoapContext(), 1);	
	_resqml2__DiscreteProperty* prop = static_cast<_resqml2__DiscreteProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	setRepresentation(rep);

	setLocalPropertyKind(localPropKind);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

void DiscreteProperty::pushBackLongHdf5Array1dOfValues(long * values, const ULONG64 & valueCount, common::AbstractHdfProxy * proxy,
		const long & nullValue, const long &  minimumValue, const long &  maximumValue)
{
	hsize_t valueCountPerDimension[1] = {valueCount};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackLongHdf5Array1dOfValues(long * values, const ULONG64 & valueCount, common::AbstractHdfProxy * proxy,
	const long & nullValue)
{
	hsize_t valueCountPerDimension[1] = {valueCount};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue);
}

void DiscreteProperty::pushBackIntHdf5Array1dOfValues(int * values, const ULONG64 & valueCount, common::AbstractHdfProxy * proxy,
	const int & nullValue, const int &  minimumValue, const int &  maximumValue)
{
	hsize_t valueCountPerDimension[1] = { valueCount };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackIntHdf5Array1dOfValues(int * values, const ULONG64 & valueCount, common::AbstractHdfProxy * proxy,
	const int & nullValue)
{
	hsize_t valueCountPerDimension[1] = { valueCount };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue);
}

void DiscreteProperty::pushBackShortHdf5Array1dOfValues(short * values, const ULONG64 & valueCount, common::AbstractHdfProxy * proxy,
	const short & nullValue, const short &  minimumValue, const short &  maximumValue)
{
	hsize_t valueCountPerDimension[1] = { valueCount };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackShortHdf5Array1dOfValues(short * values, const ULONG64 & valueCount, common::AbstractHdfProxy * proxy,
	const short & nullValue)
{
	hsize_t valueCountPerDimension[1] = { valueCount };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue);
}

void DiscreteProperty::pushBackCharHdf5Array1dOfValues(char * values, const ULONG64 & valueCount, common::AbstractHdfProxy * proxy,
	const char & nullValue, const char &  minimumValue, const char &  maximumValue)
{
	hsize_t valueCountPerDimension[1] = { valueCount };
	pushBackCharHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackCharHdf5Array1dOfValues(char * values, const ULONG64 & valueCount, common::AbstractHdfProxy * proxy,
	const char & nullValue)
{
	hsize_t valueCountPerDimension[1] = { valueCount };
	pushBackCharHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue);
}

void DiscreteProperty::pushBackLongHdf5Array2dOfValues(long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
			const long & nullValue, const long &  minimumValue, const long &  maximumValue)
{
	hsize_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackLongHdf5Array2dOfValues(long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
	const long & nullValue)
{
	hsize_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void DiscreteProperty::pushBackIntHdf5Array2dOfValues(int * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
	const int & nullValue, const int &  minimumValue, const int &  maximumValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackIntHdf5Array2dOfValues(int * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
	const int & nullValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void DiscreteProperty::pushBackShortHdf5Array2dOfValues(short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
	const short & nullValue, const short &  minimumValue, const short &  maximumValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackShortHdf5Array2dOfValues(short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
	const short & nullValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}


void DiscreteProperty::pushBackUShortHdf5Array2dOfValues(unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const unsigned short & nullValue, const unsigned short & minimumValue, const unsigned short & maximumValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackUShortHdf5Array2dOfValues(unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const unsigned short & nullValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void DiscreteProperty::pushBackCharHdf5Array2dOfValues(char * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
	const char & nullValue, const char &  minimumValue, const char &  maximumValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackCharHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackCharHdf5Array2dOfValues(char * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
	const char & nullValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackCharHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void DiscreteProperty::pushBackLongHdf5Array3dOfValues(long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
			const long & nullValue, const long &  minimumValue, const long &  maximumValue)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackLongHdf5Array3dOfValues(long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
	const long & nullValue)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void DiscreteProperty::pushBackIntHdf5Array3dOfValues(int * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
	const int & nullValue, const int &  minimumValue, const int &  maximumValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackIntHdf5Array3dOfValues(int * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
	const int & nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void DiscreteProperty::pushBackShortHdf5Array3dOfValues(short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
	const short & nullValue, const short &  minimumValue, const short &  maximumValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackShortHdf5Array3dOfValues(short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
	const short & nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void DiscreteProperty::pushBackUShortHdf5Array3dOfValues(unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
	const unsigned short & nullValue, const unsigned short &  minimumValue, const unsigned short &  maximumValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackUShortHdf5Array3dOfValues(unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
	const unsigned short & nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void DiscreteProperty::pushBackCharHdf5Array3dOfValues(char * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
	const char & nullValue, const char &  minimumValue, const char &  maximumValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackCharHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackCharHdf5Array3dOfValues(char * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
	const char & nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackCharHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

std::string DiscreteProperty::pushBackRefToExistingDataset(common::AbstractHdfProxy* hdfProxy, const std::string & datasetName, const long & nullValue)
{
	return pushBackRefToExistingIntegerDataset(hdfProxy, datasetName, nullValue);
}

std::string DiscreteProperty::pushBackRefToExistingDataset(common::AbstractHdfProxy* proxy, const std::string & datasetName, const long & nullValue, const long &  minimumValue, const long &  maximumValue)
{
	const string result = pushBackRefToExistingDataset(proxy, datasetName, nullValue);

	_resqml2__DiscreteProperty* prop = static_cast<_resqml2__DiscreteProperty*>(gsoapProxy2_0_1);

	if (prop->Count == 1)
	{
		if (prop->MinimumValue.size() == 0)
			prop->MinimumValue.push_back(minimumValue);
		else
			prop->MinimumValue[0] = minimumValue;

		if (prop->MaximumValue.size() == 0)
			prop->MaximumValue.push_back(maximumValue);
		else
			prop->MaximumValue[0] = maximumValue;
	}

	return result;
}

void DiscreteProperty::pushBackLongHdf5ArrayOfValues(long * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy * proxy,
	const long & nullValue, const long & minimumValue, const long & maximumValue)
{
	const string datasetName = pushBackRefToExistingDataset(proxy, "", nullValue, minimumValue, maximumValue);

	// HDF
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_LONG,
		values,
		numValues, numDimensionsInArray);
}

void DiscreteProperty::pushBackLongHdf5ArrayOfValues(long * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy * proxy,
	const long & nullValue)
{
	size_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}

	pair<long, long> minMax = statistics::getMinMax(values, nullValue, numTotalValues);
	pushBackLongHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

void DiscreteProperty::pushBackIntHdf5ArrayOfValues(int * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy* proxy, const int & nullValue, const int &  minimumValue, const int &  maximumValue)
{
	const string datasetName = pushBackRefToExistingDataset(proxy, "", nullValue, minimumValue, maximumValue);

	// HDF
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_INT,
		values,
		numValues, numDimensionsInArray);
}

void DiscreteProperty::pushBackIntHdf5ArrayOfValues(int * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy* proxy, const int & nullValue)
{
	hsize_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}

	pair<int, int> minMax = statistics::getMinMax(values, nullValue, numTotalValues);
	pushBackIntHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

void DiscreteProperty::pushBackShortHdf5ArrayOfValues(short * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy* proxy, const short & nullValue, const short &  minimumValue, const short &  maximumValue)
{
	const string datasetName = pushBackRefToExistingDataset(proxy, "", nullValue, minimumValue, maximumValue);

	// HDF
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_SHORT,
		values,
		numValues, numDimensionsInArray);
}

void DiscreteProperty::pushBackShortHdf5ArrayOfValues(short * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy* proxy, const short & nullValue)
{
	hsize_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}

	pair<short, short> minMax = statistics::getMinMax(values, nullValue, numTotalValues);
	pushBackShortHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

void DiscreteProperty::pushBackUShortHdf5ArrayOfValues(unsigned short * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy* proxy, const unsigned short & nullValue, const unsigned short &  minimumValue, const unsigned short &  maximumValue)
{
	const string datasetName = pushBackRefToExistingDataset(proxy, "", nullValue, minimumValue, maximumValue);

	// HDF
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_USHORT,
		values,
		numValues, numDimensionsInArray);
}

void DiscreteProperty::pushBackUShortHdf5ArrayOfValues(unsigned short * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy* proxy, const unsigned short & nullValue)
{
	hsize_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}

	pair<unsigned short, unsigned short> minMax = statistics::getMinMax(values, nullValue, numTotalValues);
	pushBackUShortHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

void DiscreteProperty::pushBackCharHdf5ArrayOfValues(char * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy* proxy, const char & nullValue, const char &  minimumValue, const char &  maximumValue)
{
	const string datasetName = pushBackRefToExistingDataset(proxy, "", nullValue, minimumValue, maximumValue);

	// HDF
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_CHAR,
		values,
		numValues, numDimensionsInArray);
}

void DiscreteProperty::pushBackCharHdf5ArrayOfValues(char * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy* proxy, const char & nullValue)
{
	hsize_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}

	pair<char, char> minMax = statistics::getMinMax(values, nullValue, numTotalValues);
	pushBackCharHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

bool DiscreteProperty::validatePropertyKindAssociation(resqml2::PropertyKind* pk)
{
	if (pk == nullptr) {
		throw invalid_argument("The property kind to validate cannot be null.");
	}

	if (!pk->isPartial()) {
		if (pk->isAbstract()) {
			epcDocument->addWarning("The discrete property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (epcDocument->getPropertyKindMapper() != nullptr) {
			if (!pk->isChildOf(resqml2__ResqmlPropertyKind__discrete)) {
				if (!pk->isChildOf(resqml2__ResqmlPropertyKind__categorical)) {
					epcDocument->addWarning("The discrete property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which does not derive from the discrete or categorical standard property kind. This property will be assumed to be a partial one.");
					changeToPartialObject();
					return false;
				}
				else {
					epcDocument->addWarning("The discrete property " + getUuid() + " is associated to a categorical property kind " + pk->getUuid() + ".");
				}
			}
		}
		else {
			epcDocument->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the categorical property " + getUuid() + " is right because no property kind mapping files have been loaded.");
		}
	}

	return true;
}

bool DiscreteProperty::validatePropertyKindAssociation(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & pk)
{
	PropertyKindMapper* pkMapper = epcDocument->getPropertyKindMapper();
	if (pkMapper != nullptr) {
		if (pkMapper->isAbstract(pk)) {
			epcDocument->addWarning("The discrete property " + getUuid() + " cannot be associated to a resqml property kind \"" + epcDocument->getEnergisticsPropertyKindName(pk) + "\" which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (!pkMapper->isChildOf(pk, resqml2__ResqmlPropertyKind__discrete)) {
			if (!pkMapper->isChildOf(pk, resqml2__ResqmlPropertyKind__categorical)) {
				epcDocument->addWarning("The discrete property " + getUuid() + " cannot be associated to a resqml property kind \"" + epcDocument->getEnergisticsPropertyKindName(pk) + "\" which does not derive from the discrete or categorical standard property kind. This property will be assumed to be a partial one.");
				changeToPartialObject();
				return false;
			}
			else {
				getEpcDocument()->addWarning("The discrete property " + getUuid() + " is associated to a categorical property kind.");
			}
		}
	}
	else {
		epcDocument->addWarning("Cannot verify if the resqml property kind \"" + epcDocument->getEnergisticsPropertyKindName(pk) + "\" of the discrete property " + getUuid() + " is right because no property kind mapping files have been loaded.");
	}

	return true;
}
