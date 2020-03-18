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
#include "AbstractDiscreteOrCategoricalProperty.h"

#include <sstream>
#include <stdexcept>

#include <hdf5.h>

#include "../common/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_NS;

void AbstractDiscreteOrCategoricalProperty::pushBackLongHdf5Array1dOfValues(const LONG64 * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy,
	LONG64 nullValue)
{
	hsize_t valueCountPerDimension = valueCount;
	pushBackLongHdf5ArrayOfValues(values, &valueCountPerDimension, 1, proxy, nullValue);
}

void AbstractDiscreteOrCategoricalProperty::pushBackIntHdf5Array1dOfValues(const int * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy,
	int nullValue)
{
	hsize_t valueCountPerDimension = valueCount;
	pushBackIntHdf5ArrayOfValues(values, &valueCountPerDimension, 1, proxy, nullValue);
}

void AbstractDiscreteOrCategoricalProperty::pushBackShortHdf5Array1dOfValues(const short * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy,
	short nullValue)
{
	hsize_t valueCountPerDimension = valueCount;
	pushBackShortHdf5ArrayOfValues(values, &valueCountPerDimension, 1, proxy, nullValue);
}

void AbstractDiscreteOrCategoricalProperty::pushBackCharHdf5Array1dOfValues(const char * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy,
	char nullValue)
{
	hsize_t valueCountPerDimension = valueCount;
	pushBackCharHdf5ArrayOfValues(values, &valueCountPerDimension, 1, proxy, nullValue);
}

void AbstractDiscreteOrCategoricalProperty::pushBackLongHdf5Array2dOfValues(const LONG64 * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	LONG64 nullValue)
{
	hsize_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void AbstractDiscreteOrCategoricalProperty::pushBackIntHdf5Array2dOfValues(const int * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	int nullValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void AbstractDiscreteOrCategoricalProperty::pushBackShortHdf5Array2dOfValues(const short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	short nullValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void AbstractDiscreteOrCategoricalProperty::pushBackUShortHdf5Array2dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, unsigned short nullValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void AbstractDiscreteOrCategoricalProperty::pushBackCharHdf5Array2dOfValues(const char * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	char nullValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackCharHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void AbstractDiscreteOrCategoricalProperty::pushBackLongHdf5Array3dOfValues(const LONG64 * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	LONG64 nullValue)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void AbstractDiscreteOrCategoricalProperty::pushBackIntHdf5Array3dOfValues(const int * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	int nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void AbstractDiscreteOrCategoricalProperty::pushBackShortHdf5Array3dOfValues(const short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	short nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void AbstractDiscreteOrCategoricalProperty::pushBackUShortHdf5Array3dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	unsigned short nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void AbstractDiscreteOrCategoricalProperty::pushBackCharHdf5Array3dOfValues(const char * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	char nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackCharHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

std::string AbstractDiscreteOrCategoricalProperty::pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName, LONG64 nullValue)
{
	if (hdfProxy == nullptr) {
		hdfProxy = getRepository()->getDefaultHdfProxy();
		if (hdfProxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, hdfProxy);
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractValuesProperty* prop = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1);

		gsoap_resqml2_0_1::resqml20__PatchOfValues* patch = gsoap_resqml2_0_1::soap_new_resqml20__PatchOfValues(gsoapProxy2_0_1->soap);
		patch->RepresentationPatchIndex = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
		*(patch->RepresentationPatchIndex) = prop->PatchOfValues.size();

		// XML
		gsoap_resqml2_0_1::resqml20__IntegerHdf5Array* xmlValues = gsoap_resqml2_0_1::soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
		xmlValues->NullValue = nullValue;
		xmlValues->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		xmlValues->Values->HdfProxy = hdfProxy->newResqmlReference();

		if (datasetName.empty()) {
			ostringstream ossForHdf;
			ossForHdf << "values_patch" << *(patch->RepresentationPatchIndex);
			xmlValues->Values->PathInHdfFile = getHdfGroup() + "/" + ossForHdf.str();
		}
		else {
			xmlValues->Values->PathInHdfFile = datasetName;
		}

		patch->Values = xmlValues;

		prop->PatchOfValues.push_back(patch);

		return xmlValues->Values->PathInHdfFile;
	}

	throw logic_error("Not implemented yet");
}

void AbstractDiscreteOrCategoricalProperty::pushBackLongHdf5ArrayOfValues(const LONG64 * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy * proxy, LONG64 nullValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	if (gsoapProxy2_0_1 != nullptr) {
		proxy->writeArrayNd(getHdfGroup(),
			pushBackRefToExistingDataset(proxy, "", nullValue),
			H5T_NATIVE_LLONG,
			values,
			numValues, numDimensionsInArray);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractDiscreteOrCategoricalProperty::pushBackIntHdf5ArrayOfValues(const int * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, int nullValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	if (gsoapProxy2_0_1 != nullptr) {
		proxy->writeArrayNd(getHdfGroup(),
			pushBackRefToExistingDataset(proxy, "", nullValue),
			H5T_NATIVE_INT,
			values,
			numValues, numDimensionsInArray);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractDiscreteOrCategoricalProperty::pushBackShortHdf5ArrayOfValues(const short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, short nullValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	if (gsoapProxy2_0_1 != nullptr) {
		proxy->writeArrayNd(getHdfGroup(),
			pushBackRefToExistingDataset(proxy, "", nullValue),
			H5T_NATIVE_SHORT,
			values,
			numValues, numDimensionsInArray);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractDiscreteOrCategoricalProperty::pushBackUShortHdf5ArrayOfValues(const unsigned short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, unsigned short nullValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	if (gsoapProxy2_0_1 != nullptr) {
		proxy->writeArrayNd(getHdfGroup(),
			pushBackRefToExistingDataset(proxy, "", nullValue),
			H5T_NATIVE_USHORT,
			values,
			numValues, numDimensionsInArray);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractDiscreteOrCategoricalProperty::pushBackCharHdf5ArrayOfValues(const char * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, char nullValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	if (gsoapProxy2_0_1 != nullptr) {
		proxy->writeArrayNd(getHdfGroup(),
			pushBackRefToExistingDataset(proxy, "", nullValue),
			H5T_NATIVE_CHAR,
			values,
			numValues, numDimensionsInArray);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

LONG64 AbstractDiscreteOrCategoricalProperty::getLongValuesOfPatch(unsigned int patchIndex, LONG64 * values) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);

	getHdfProxyFromDataset(dataset)->readArrayNdOfLongValues(dataset->PathInHdfFile, values);

	return nullValue;
}

LONG64 AbstractDiscreteOrCategoricalProperty::getNullValueOfPatch(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];
		if (patch->Values->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			return static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(patch->Values)->NullValue;
		}

		throw invalid_argument("The patch does not contain integer values.");
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

ULONG64 AbstractDiscreteOrCategoricalProperty::getULongValuesOfPatch(unsigned int patchIndex, ULONG64 * values) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);

	getHdfProxyFromDataset(dataset)->readArrayNdOfULongValues(dataset->PathInHdfFile, values);

	return nullValue;
}

int AbstractDiscreteOrCategoricalProperty::getIntValuesOfPatch(unsigned int patchIndex, int * values) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);

	getHdfProxyFromDataset(dataset)->readArrayNdOfIntValues(dataset->PathInHdfFile, values);

	return nullValue;
}

unsigned int AbstractDiscreteOrCategoricalProperty::getUIntValuesOfPatch(unsigned int patchIndex, unsigned int * values) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);

	getHdfProxyFromDataset(dataset)->readArrayNdOfUIntValues(dataset->PathInHdfFile, values);

	return nullValue;
}

short AbstractDiscreteOrCategoricalProperty::getShortValuesOfPatch(unsigned int patchIndex, short * values) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);

	getHdfProxyFromDataset(dataset)->readArrayNdOfShortValues(dataset->PathInHdfFile, values);

	return nullValue;
}

unsigned short AbstractDiscreteOrCategoricalProperty::getUShortValuesOfPatch(unsigned int patchIndex, unsigned short * values) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);

	getHdfProxyFromDataset(dataset)->readArrayNdOfUShortValues(dataset->PathInHdfFile, values);

	return nullValue;
}

char AbstractDiscreteOrCategoricalProperty::getCharValuesOfPatch(unsigned int patchIndex, char * values) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);

	getHdfProxyFromDataset(dataset)->readArrayNdOfCharValues(dataset->PathInHdfFile, values);

	return nullValue;
}

unsigned char AbstractDiscreteOrCategoricalProperty::getUCharValuesOfPatch(unsigned int patchIndex, unsigned char * values) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);

	getHdfProxyFromDataset(dataset)->readArrayNdOfUCharValues(dataset->PathInHdfFile, values);

	return nullValue;
}

void AbstractDiscreteOrCategoricalProperty::pushBackLongHdf5Array3dOfValues(
	ULONG64 valueCountInFastestDim,
	ULONG64 valueCountInMiddleDim,
	ULONG64 valueCountInSlowestDim,
	LONG64 nullValue,
	COMMON_NS::AbstractHdfProxy* proxy)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackLongHdf5ArrayOfValues(valueCountPerDimension, 3, nullValue, proxy);
}

void AbstractDiscreteOrCategoricalProperty::setValuesOfLongHdf5Array3dOfValues(
	LONG64* values,
	ULONG64 valueCountInFastestDim,
	ULONG64 valueCountInMiddleDim,
	ULONG64 valueCountInSlowestDim,
	ULONG64 offsetInFastestDim,
	ULONG64 offsetInMiddleDim,
	ULONG64 offsetInSlowestDim,
	COMMON_NS::AbstractHdfProxy * proxy,
	unsigned int patchIndex)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	hsize_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };
	setValuesOfLongHdf5ArrayOfValues(
		values,
		valueCountPerDimension,
		offsetPerDimension,
		3,
		proxy,
		patchIndex
	);
}

void AbstractDiscreteOrCategoricalProperty::pushBackLongHdf5ArrayOfValues(
	hsize_t* numValues,
	unsigned int numArrayDimensions,
	LONG64 nullValue,
	COMMON_NS::AbstractHdfProxy* proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractValuesProperty* prop = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1);

		gsoap_resqml2_0_1::resqml20__PatchOfValues* patch = gsoap_resqml2_0_1::soap_new_resqml20__PatchOfValues(gsoapProxy2_0_1->soap);
		patch->RepresentationPatchIndex = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
		*(patch->RepresentationPatchIndex) = prop->PatchOfValues.size();

		// XML
		gsoap_resqml2_0_1::resqml20__IntegerHdf5Array* xmlValues = gsoap_resqml2_0_1::soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
		xmlValues->NullValue = nullValue;
		xmlValues->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		xmlValues->Values->HdfProxy = proxy->newResqmlReference();
		std::ostringstream ossForHdf;
		ossForHdf << "values_patch" << *(patch->RepresentationPatchIndex);
		xmlValues->Values->PathInHdfFile = getHdfGroup() + "/" + ossForHdf.str();
		patch->Values = xmlValues;

		prop->PatchOfValues.push_back(patch);
	}
	else {
		throw logic_error("Not implemented yet");
	}

	// HDF
	ostringstream oss;
	oss << "values_patch" << getPatchCount() - 1;
	proxy->createArrayNd(getHdfGroup(),
		oss.str(),
		H5T_NATIVE_LLONG,
		numValues, numArrayDimensions);
}

void AbstractDiscreteOrCategoricalProperty::setValuesOfLongHdf5ArrayOfValues(
	LONG64* values, hsize_t const * numValuesInEachDimension,
	hsize_t const * offsetInEachDimension, unsigned int numArrayDimensions,
	COMMON_NS::AbstractHdfProxy* proxy,
	unsigned int patchIndex)
{
	if (patchIndex >= getPatchCount() && patchIndex != (numeric_limits<unsigned int>::max)()) {
		throw out_of_range("The values property patch is out of range");
	}

	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

	ostringstream oss;
	oss << "values_patch";
	if (patchIndex == (numeric_limits<unsigned int>::max)()) {
		oss << static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty *>(gsoapProxy2_0_1)->PatchOfValues.size() - 1;
	}
	else {
		oss << patchIndex;
	}

	// HDF
	proxy->writeArrayNdSlab(getHdfGroup(),
		oss.str(),
		H5T_NATIVE_LLONG,
		values,
		numValuesInEachDimension,
		offsetInEachDimension,
		numArrayDimensions);
}

void AbstractDiscreteOrCategoricalProperty::getLongValuesOfPatch(
	unsigned int patchIndex,
	LONG64* values,
	hsize_t const * numValuesInEachDimension,
	hsize_t const * offsetInEachDimension,
	unsigned int numArrayDimensions) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);

	getHdfProxyFromDataset(dataset)->readArrayNdOfLongValues(
		dataset->PathInHdfFile,
		values,
		numValuesInEachDimension,
		offsetInEachDimension,
		numArrayDimensions);
}

void AbstractDiscreteOrCategoricalProperty::getLongValuesOf3dPatch(
	unsigned int patchIndex,
	LONG64* values,
	ULONG64 valueCountInFastestDim,
	ULONG64 valueCountInMiddleDim,
	ULONG64 valueCountInSlowestDim,
	ULONG64 offsetInFastestDim,
	ULONG64 offsetInMiddleDim,
	ULONG64 offsetInSlowestDim) const
{
	const hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	const hsize_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };

	getLongValuesOfPatch(
		patchIndex,
		values,
		valueCountPerDimension,
		offsetPerDimension,
		3
	);
}

int AbstractDiscreteOrCategoricalProperty::getIntValuesOfPatch(
	unsigned int patchIndex,
	int* values,
	unsigned long long* numValuesInEachDimension,
	unsigned long long* offsetInEachDimension,
	unsigned int numArrayDimensions) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);
	getHdfProxyFromDataset(dataset)->readArrayNdOfIntValues(
		dataset->PathInHdfFile,
		values,
		numValuesInEachDimension,
		offsetInEachDimension,
		numArrayDimensions);

	return nullValue;
}

void AbstractDiscreteOrCategoricalProperty::getIntValuesOf3dPatch(
	unsigned int patchIndex,
	int* values,
	unsigned int valueCountInFastestDim,
	unsigned int valueCountInMiddleDim,
	unsigned int valueCountInSlowestDim,
	unsigned int offsetInFastestDim,
	unsigned int offsetInMiddleDim,
	unsigned int offsetInSlowestDim) const
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	hsize_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };

	getIntValuesOfPatch(
		patchIndex,
		values,
		valueCountPerDimension,
		offsetPerDimension,
		3
	);
}
