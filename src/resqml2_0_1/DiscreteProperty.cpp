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
#include "DiscreteProperty.h"

#include <sstream>
#include <stdexcept>

#include <hdf5.h>

#include "../common/AbstractHdfProxy.h"
#include "../common/EnumStringMapper.h"
#include "../common/PropertyKind.h"

#include "../tools/Statistics.h"
#include "../resqml2/AbstractRepresentation.h"
#include "PropertyKindMapper.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* DiscreteProperty::XML_TAG = "DiscreteProperty";

DiscreteProperty::DiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind, resqml20__ResqmlPropertyKind energisticsPropertyKind)
{
	if (rep == nullptr) {
		throw invalid_argument("The representation of this property values cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREDiscreteProperty(rep->getGsoapContext());	
	_resqml20__DiscreteProperty* prop = static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	resqml20__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml20__StandardPropertyKind(gsoapProxy2_0_1->soap);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	prop->PropertyKind = xmlStandardPropKind;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setRepresentation(rep);
}

DiscreteProperty::DiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind, COMMON_NS::PropertyKind * localPropKind)
{
	if (rep == nullptr) {
		throw invalid_argument("The representation of this property values cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREDiscreteProperty(rep->getGsoapContext());	
	_resqml20__DiscreteProperty* prop = static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setRepresentation(rep);

	setLocalPropertyKind(localPropKind);
}

void DiscreteProperty::pushBackLongHdf5Array1dOfValues(const LONG64 * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy,
	LONG64 nullValue, LONG64  minimumValue, LONG64  maximumValue)
{
	hsize_t valueCountPerDimension[1] = {valueCount};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackLongHdf5Array1dOfValues(const LONG64 * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy,
	LONG64 nullValue)
{
	hsize_t valueCountPerDimension[1] = {valueCount};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue);
}

void DiscreteProperty::pushBackIntHdf5Array1dOfValues(const int * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy,
	int nullValue, int  minimumValue, int  maximumValue)
{
	hsize_t valueCountPerDimension[1] = { valueCount };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackIntHdf5Array1dOfValues(const int * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy,
	int nullValue)
{
	hsize_t valueCountPerDimension[1] = { valueCount };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue);
}

void DiscreteProperty::pushBackShortHdf5Array1dOfValues(const short * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy,
	short nullValue, short  minimumValue, short  maximumValue)
{
	hsize_t valueCountPerDimension[1] = { valueCount };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackShortHdf5Array1dOfValues(const short * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy,
	short nullValue)
{
	hsize_t valueCountPerDimension[1] = { valueCount };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue);
}

void DiscreteProperty::pushBackCharHdf5Array1dOfValues(const char * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy,
	char nullValue, char  minimumValue, char  maximumValue)
{
	hsize_t valueCountPerDimension[1] = { valueCount };
	pushBackCharHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackCharHdf5Array1dOfValues(const char * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy,
	char nullValue)
{
	hsize_t valueCountPerDimension[1] = { valueCount };
	pushBackCharHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue);
}

void DiscreteProperty::pushBackLongHdf5Array2dOfValues(const LONG64 * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	LONG64 nullValue, LONG64  minimumValue, LONG64  maximumValue)
{
	hsize_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackLongHdf5Array2dOfValues(const LONG64 * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	LONG64 nullValue)
{
	hsize_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void DiscreteProperty::pushBackIntHdf5Array2dOfValues(const int * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	int nullValue, int  minimumValue, int  maximumValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackIntHdf5Array2dOfValues(const int * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	int nullValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void DiscreteProperty::pushBackShortHdf5Array2dOfValues(const short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	short nullValue, short  minimumValue, short  maximumValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackShortHdf5Array2dOfValues(const short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	short nullValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}


void DiscreteProperty::pushBackUShortHdf5Array2dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackUShortHdf5Array2dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, unsigned short nullValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void DiscreteProperty::pushBackCharHdf5Array2dOfValues(const char * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	char nullValue, char  minimumValue, char  maximumValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackCharHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackCharHdf5Array2dOfValues(const char * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	char nullValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackCharHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void DiscreteProperty::pushBackLongHdf5Array3dOfValues(const LONG64 * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	LONG64 nullValue, LONG64 minimumValue, LONG64 maximumValue)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackLongHdf5Array3dOfValues(const LONG64 * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	LONG64 nullValue)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void DiscreteProperty::pushBackIntHdf5Array3dOfValues(const int * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	int nullValue, int  minimumValue, int  maximumValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackIntHdf5Array3dOfValues(const int * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	int nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void DiscreteProperty::pushBackShortHdf5Array3dOfValues(const short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	short nullValue, short  minimumValue, short  maximumValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackShortHdf5Array3dOfValues(const short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	short nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void DiscreteProperty::pushBackUShortHdf5Array3dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	unsigned short nullValue, unsigned short  minimumValue, unsigned short  maximumValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackUShortHdf5Array3dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	unsigned short nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void DiscreteProperty::pushBackCharHdf5Array3dOfValues(const char * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	char nullValue, char  minimumValue, char  maximumValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackCharHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackCharHdf5Array3dOfValues(const char * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	char nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackCharHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

std::string DiscreteProperty::pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName, LONG64 nullValue)
{
	return pushBackRefToExistingIntegerDataset(hdfProxy, datasetName, nullValue);
}

std::string DiscreteProperty::pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* proxy, const std::string & datasetName, LONG64 nullValue, LONG64 minimumValue, LONG64 maximumValue)
{
	const string result = pushBackRefToExistingDataset(proxy, datasetName, nullValue);

	_resqml20__DiscreteProperty* prop = static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1);

	if (prop->Count == 1)
	{
		if (prop->MinimumValue.empty())
			prop->MinimumValue.push_back(minimumValue);
		else
			prop->MinimumValue[0] = minimumValue;

		if (prop->MaximumValue.empty())
			prop->MaximumValue.push_back(maximumValue);
		else
			prop->MaximumValue[0] = maximumValue;
	}

	return result;
}

void DiscreteProperty::pushBackLongHdf5ArrayOfValues(const LONG64 * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy * proxy,
	LONG64 nullValue, LONG64 minimumValue, LONG64 maximumValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const string datasetName = pushBackRefToExistingDataset(proxy, "", nullValue, minimumValue, maximumValue);

	// HDF
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_LLONG,
		values,
		numValues, numDimensionsInArray);
}

void DiscreteProperty::pushBackLongHdf5ArrayOfValues(const LONG64 * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy * proxy,
	LONG64 nullValue)
{
	size_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}

	pair<LONG64, LONG64> minMax = statistics::getMinMax(values, nullValue, numTotalValues);
	pushBackLongHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

void DiscreteProperty::pushBackIntHdf5ArrayOfValues(const int * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, int nullValue, int  minimumValue, int  maximumValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const string datasetName = pushBackRefToExistingDataset(proxy, "", nullValue, minimumValue, maximumValue);

	// HDF
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_INT,
		values,
		numValues, numDimensionsInArray);
}

void DiscreteProperty::pushBackIntHdf5ArrayOfValues(const int * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, int nullValue)
{
	hsize_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}

	pair<int, int> minMax = statistics::getMinMax(values, nullValue, numTotalValues);
	pushBackIntHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

void DiscreteProperty::pushBackShortHdf5ArrayOfValues(const short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, short nullValue, short  minimumValue, short  maximumValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const string datasetName = pushBackRefToExistingDataset(proxy, "", nullValue, minimumValue, maximumValue);

	// HDF
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_SHORT,
		values,
		numValues, numDimensionsInArray);
}

void DiscreteProperty::pushBackShortHdf5ArrayOfValues(const short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, short nullValue)
{
	hsize_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}

	pair<short, short> minMax = statistics::getMinMax(values, nullValue, numTotalValues);
	pushBackShortHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

void DiscreteProperty::pushBackUShortHdf5ArrayOfValues(const unsigned short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, unsigned short nullValue, unsigned short  minimumValue, unsigned short  maximumValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const string datasetName = pushBackRefToExistingDataset(proxy, "", nullValue, minimumValue, maximumValue);

	// HDF
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_USHORT,
		values,
		numValues, numDimensionsInArray);
}

void DiscreteProperty::pushBackUShortHdf5ArrayOfValues(const unsigned short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, unsigned short nullValue)
{
	hsize_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}

	pair<unsigned short, unsigned short> minMax = statistics::getMinMax(values, nullValue, numTotalValues);
	pushBackUShortHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

void DiscreteProperty::pushBackCharHdf5ArrayOfValues(const char * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, char nullValue, char  minimumValue, char  maximumValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const string datasetName = pushBackRefToExistingDataset(proxy, "", nullValue, minimumValue, maximumValue);

	// HDF
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_CHAR,
		values,
		numValues, numDimensionsInArray);
}

void DiscreteProperty::pushBackCharHdf5ArrayOfValues(const char * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, char nullValue)
{
	hsize_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}

	pair<char, char> minMax = statistics::getMinMax(values, nullValue, numTotalValues);
	pushBackCharHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

bool DiscreteProperty::validatePropertyKindAssociation(COMMON_NS::PropertyKind* pk)
{
	if (pk == nullptr) {
		throw invalid_argument("The property kind to validate cannot be null.");
	}

	if (!pk->isPartial()) {
		if (pk->isAbstract()) {
			repository->addWarning("The discrete property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (repository->getPropertyKindMapper() != nullptr) {
			if (pk->isParentPartial()) {
				repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the discrete property " + getUuid() + " is right because one if its parent property kind is abstract.");
				return true;
			}
			if (!pk->isChildOf(resqml20__ResqmlPropertyKind__discrete)) {
				if (!pk->isChildOf(resqml20__ResqmlPropertyKind__categorical)) {
					repository->addWarning("The discrete property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which does not derive from the discrete or categorical standard property kind. This property will be assumed to be a partial one.");
					changeToPartialObject();
					return false;
				}
				else {
					repository->addWarning("The discrete property " + getUuid() + " is associated to a categorical property kind " + pk->getUuid() + ".");
				}
			}
		}
		else {
			repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the discrete property " + getUuid() + " is right because no property kind mapping files have been loaded.");
		}
	}
	else {
		repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the discrete property " + getUuid() + " is right because it is abstract.");
	}

	return true;
}

bool DiscreteProperty::validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind pk)
{
	COMMON_NS::EnumStringMapper tmp;
	std::string pkName = tmp.getEnergisticsPropertyKindName(pk);

	PropertyKindMapper* pkMapper = repository->getPropertyKindMapper();
	if (pkMapper != nullptr) {
		if (pkMapper->isAbstract(pk)) {
			repository->addWarning("The discrete property " + getUuid() + " cannot be associated to a resqml property kind \"" + pkName + "\" which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (!pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind__discrete)) {
			if (!pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind__categorical)) {
				repository->addWarning("The discrete property " + getUuid() + " cannot be associated to a resqml property kind \"" + pkName + "\" which does not derive from the discrete or categorical standard property kind. This property will be assumed to be a partial one.");
				changeToPartialObject();
				return false;
			}
			else {
				getRepository()->addWarning("The discrete property " + getUuid() + " is associated to a categorical property kind.");
			}
		}
	}
	else {
		repository->addWarning("Cannot verify if the resqml property kind \"" + pkName + "\" of the discrete property " + getUuid() + " is right because no property kind mapping files have been loaded.");
	}

	return true;
}

LONG64 DiscreteProperty::getMinimumValue() const
{
	_resqml20__DiscreteProperty* prop = static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1);

	return prop->MinimumValue.empty() ? (std::numeric_limits<LONG64>::max)() : prop->MinimumValue[0];
}

LONG64 DiscreteProperty::getMaximumValue() const
{
	_resqml20__DiscreteProperty* prop = static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1);

	return prop->MaximumValue.empty() ? (std::numeric_limits<LONG64>::min)() : prop->MaximumValue[0];
}
