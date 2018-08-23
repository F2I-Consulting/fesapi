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
#include "resqml2/AbstractValuesProperty.h"

#include <stdexcept>
#include <ostream>
#include <sstream>

#include "hdf5.h"

#include "resqml2/AbstractRepresentation.h"
#include "resqml2/PropertyKind.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "common/AbstractHdfProxy.h"

using namespace RESQML2_NS;
using namespace std;
using namespace epc;

unsigned int AbstractValuesProperty::getPatchCount() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractValuesProperty*>(gsoapProxy2_0_1)->PatchOfValues.size();
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

COMMON_NS::AbstractObject::hdfDatatypeEnum AbstractValuesProperty::getValuesHdfDatatype() const
{
	COMMON_NS::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr)
		return COMMON_NS::AbstractObject::UNKNOWN;

	hid_t dt = -1;
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractValuesProperty* prop = static_cast<gsoap_resqml2_0_1::resqml2__AbstractValuesProperty*>(gsoapProxy2_0_1);

		gsoap_resqml2_0_1::resqml2__PatchOfValues* firstPatch = prop->PatchOfValues[0];
		int valuesType = firstPatch->Values->soap_type();
		if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array) {
			return hdfProxy->getHdfDatatypeInDataset(static_cast<gsoap_resqml2_0_1::resqml2__BooleanHdf5Array*>(firstPatch->Values)->Values->PathInHdfFile);
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
			return hdfProxy->getHdfDatatypeInDataset(static_cast<gsoap_resqml2_0_1::resqml2__DoubleHdf5Array*>(firstPatch->Values)->Values->PathInHdfFile);
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
			return hdfProxy->getHdfDatatypeInDataset(static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(firstPatch->Values)->Values->PathInHdfFile);
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__StringHdf5Array) {
			return hdfProxy->getHdfDatatypeInDataset(static_cast<gsoap_resqml2_0_1::resqml2__StringHdf5Array*>(firstPatch->Values)->Values->PathInHdfFile);
		}
		else {
			return COMMON_NS::AbstractObject::UNKNOWN;
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string AbstractValuesProperty::pushBackRefToExistingIntegerDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName, const long & nullValue)
{
	setHdfProxy(hdfProxy);
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractValuesProperty* prop = static_cast<gsoap_resqml2_0_1::resqml2__AbstractValuesProperty*>(gsoapProxy2_0_1);

		gsoap_resqml2_0_1::resqml2__PatchOfValues* patch = gsoap_resqml2_0_1::soap_new_resqml2__PatchOfValues(gsoapProxy2_0_1->soap, 1);
		patch->RepresentationPatchIndex = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
		*(patch->RepresentationPatchIndex) = prop->PatchOfValues.size();

		// XML
		gsoap_resqml2_0_1::resqml2__IntegerHdf5Array* xmlValues = gsoap_resqml2_0_1::soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
		xmlValues->NullValue = nullValue;
		xmlValues->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
		xmlValues->Values->HdfProxy = hdfProxy->newResqmlReference();

		if (datasetName.empty()) {
			ostringstream ossForHdf;
			ossForHdf << "values_patch" << *(patch->RepresentationPatchIndex);
			xmlValues->Values->PathInHdfFile = "/RESQML/" + prop->uuid + "/" + ossForHdf.str();
		}
		else {
			xmlValues->Values->PathInHdfFile = datasetName;
		}

		patch->Values = xmlValues;

		prop->PatchOfValues.push_back(patch);

		return xmlValues->Values->PathInHdfFile;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string AbstractValuesProperty::getPathInHdfFileOfPatch(const unsigned int & patchIndex, LONG64 & nullValue) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The values property patch is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__PatchOfValues* patch = static_cast<gsoap_resqml2_0_1::resqml2__AbstractValuesProperty*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];

		nullValue = (numeric_limits<long>::min)();
		int valuesType = patch->Values->soap_type();
		if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array) {
			return static_cast<gsoap_resqml2_0_1::resqml2__BooleanHdf5Array*>(patch->Values)->Values->PathInHdfFile;
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
			return static_cast<gsoap_resqml2_0_1::resqml2__DoubleHdf5Array*>(patch->Values)->Values->PathInHdfFile;
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
			nullValue = static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(patch->Values)->NullValue;
			return static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(patch->Values)->Values->PathInHdfFile;
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__StringHdf5Array) {
			return static_cast<gsoap_resqml2_0_1::resqml2__StringHdf5Array*>(patch->Values)->Values->PathInHdfFile;
		}
		else {
			throw logic_error("The type of the property values is not implemented yet.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

long AbstractValuesProperty::getLongValuesOfPatch(const unsigned int & patchIndex, long * values)
{
	COMMON_NS::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr) {
		throw invalid_argument("The Hdf proxy cannot be nullptr.");
	}

	LONG64 nullValue = (numeric_limits<long long>::min)();
	hdfProxy->readArrayNdOfLongValues(getPathInHdfFileOfPatch(patchIndex, nullValue), values);

	return nullValue;
}

long AbstractValuesProperty::getNullValueOfPatch(const unsigned int & patchIndex)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__PatchOfValues* patch = static_cast<gsoap_resqml2_0_1::resqml2__AbstractValuesProperty*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];
		if (patch->Values->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
			return static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(patch->Values)->NullValue;
		}

		throw invalid_argument("The patch does not contain integer values.");
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

unsigned long AbstractValuesProperty::getULongValuesOfPatch(const unsigned int & patchIndex, unsigned long * values)
{
	COMMON_NS::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr)
		throw invalid_argument("The Hdf proxy cannot be nullptr.");

	LONG64 nullValue = (numeric_limits<long long>::min)();
	hdfProxy->readArrayNdOfULongValues(getPathInHdfFileOfPatch(patchIndex, nullValue), values);

	return nullValue;
}

int AbstractValuesProperty::getIntValuesOfPatch(const unsigned int & patchIndex, int * values)
{
	COMMON_NS::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr) {
		throw invalid_argument("The hdf proxy does not exist");
	}

	LONG64 nullValue = (numeric_limits<long long>::min)();
	hdfProxy->readArrayNdOfIntValues(getPathInHdfFileOfPatch(patchIndex, nullValue), values);

	return nullValue;
}

int AbstractValuesProperty::getIntValuesOfPatch(
	const unsigned int& patchIndex,
	int* values,
	unsigned long long* numValuesInEachDimension,
	unsigned long long* offsetInEachDimension,
	const unsigned int& numArrayDimensions)
{
	COMMON_NS::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr) {
		throw invalid_argument("The hdf proxy does not exist");
	}

	LONG64 nullValue = (numeric_limits<long long>::min)();
	hdfProxy->readArrayNdOfIntValues(
		getPathInHdfFileOfPatch(patchIndex, nullValue),
		values,
		numValuesInEachDimension,
		offsetInEachDimension,
		numArrayDimensions);

	return nullValue;
}

void AbstractValuesProperty::getIntValuesOf3dPatch(
	const unsigned int& patchIndex,
	int* values,
	const unsigned int& valueCountInFastestDim,
	const unsigned int& valueCountInMiddleDim,
	const unsigned int& valueCountInSlowestDim,
	const unsigned int& offsetInFastestDim,
	const unsigned int& offsetInMiddleDim,
	const unsigned int& offsetInSlowestDim)
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

unsigned int AbstractValuesProperty::getUIntValuesOfPatch(const unsigned int & patchIndex, unsigned int * values)
{
	COMMON_NS::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr) {
		throw invalid_argument("The Hdf proxy cannot be nullptr.");
	}

	LONG64 nullValue = (numeric_limits<long long>::min)();
	hdfProxy->readArrayNdOfUIntValues(getPathInHdfFileOfPatch(patchIndex, nullValue), values);

	return nullValue;
}

short AbstractValuesProperty::getShortValuesOfPatch(const unsigned int & patchIndex, short * values)
{
	COMMON_NS::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr) {
		throw invalid_argument("The Hdf proxy cannot be nullptr.");
	}

	LONG64 nullValue = (numeric_limits<long long>::min)();
	hdfProxy->readArrayNdOfShortValues(getPathInHdfFileOfPatch(patchIndex, nullValue), values);

	return nullValue;
}

unsigned short AbstractValuesProperty::getUShortValuesOfPatch(const unsigned int & patchIndex, unsigned short * values)
{
	COMMON_NS::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr) {
		throw invalid_argument("The Hdf proxy cannot be nullptr.");
	}

	LONG64 nullValue = (numeric_limits<long long>::min)();
	hdfProxy->readArrayNdOfUShortValues(getPathInHdfFileOfPatch(patchIndex, nullValue), values);

	return nullValue;
}

char AbstractValuesProperty::getCharValuesOfPatch(const unsigned int & patchIndex, char * values)
{
	COMMON_NS::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr) {
		throw invalid_argument("The Hdf proxy cannot be nullptr.");
	}

	LONG64 nullValue = (numeric_limits<long long>::min)();
	hdfProxy->readArrayNdOfCharValues(getPathInHdfFileOfPatch(patchIndex, nullValue), values);

	return nullValue;
}

unsigned char AbstractValuesProperty::getUCharValuesOfPatch(const unsigned int & patchIndex, unsigned char * values)
{
	COMMON_NS::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr) {
		throw invalid_argument("The Hdf proxy cannot be nullptr.");
	}

	LONG64 nullValue = (numeric_limits<long long>::min)();
	hdfProxy->readArrayNdOfUCharValues(getPathInHdfFileOfPatch(patchIndex, nullValue), values);

	return nullValue;
}

unsigned int AbstractValuesProperty::getValuesCountOfDimensionOfPatch(const unsigned int & dimIndex, const unsigned int & patchIndex)
{
	COMMON_NS::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr) {
		throw invalid_argument("The Hdf proxy cannot be nullptr.");
	}

	LONG64 nullValue = (numeric_limits<long long>::min)();
	std::vector<hsize_t> dims = hdfProxy->readArrayDimensions(getPathInHdfFileOfPatch(patchIndex, nullValue));

	if (dimIndex < dims.size())
		return dims[dimIndex];
	else{
		throw range_error("The dim index to get the count is out of range.");
	}
}

unsigned int AbstractValuesProperty::getDimensionsCountOfPatch(const unsigned int & patchIndex)
{
	COMMON_NS::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr) {
		throw invalid_argument("The Hdf proxy cannot be nullptr.");
	}

	LONG64 nullValue = (numeric_limits<long long>::min)();
	return hdfProxy->getDimensionCount(getPathInHdfFileOfPatch(patchIndex, nullValue));
}

void AbstractValuesProperty::pushBackFacet(const gsoap_resqml2_0_1::resqml2__Facet & facet, const std::string & facetValue)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__PropertyKindFacet* newFacet = gsoap_resqml2_0_1::soap_new_resqml2__PropertyKindFacet(gsoapProxy2_0_1->soap, 1);
		newFacet->Facet = facet;
		newFacet->Value = facetValue;
		static_cast<gsoap_resqml2_0_1::resqml2__AbstractValuesProperty*>(gsoapProxy2_0_1)->Facet.push_back(newFacet);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

unsigned int AbstractValuesProperty::getFacetCount() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractValuesProperty*>(gsoapProxy2_0_1)->Facet.size();
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::resqml2__Facet AbstractValuesProperty::getFacet(const unsigned int & index) const
{
	if (index >= getFacetCount()) {
		throw out_of_range("The facet index is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractValuesProperty*>(gsoapProxy2_0_1)->Facet[index]->Facet;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string AbstractValuesProperty::getFacetValue(const unsigned int & index) const
{
	if (index >= getFacetCount()){
		throw out_of_range("The facet index is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractValuesProperty*>(gsoapProxy2_0_1)->Facet[index]->Value;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

unsigned int AbstractValuesProperty::getValuesCountOfPatch (const unsigned int & patchIndex)
{
	COMMON_NS::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr) {
		throw invalid_argument("The Hdf proxy cannot be nullptr.");
	}

	LONG64 nullValue = (numeric_limits<long long>::min)();
	return hdfProxy->getElementCount(getPathInHdfFileOfPatch(patchIndex, nullValue));
}

void AbstractValuesProperty::createLongHdf5Array3dOfValues(
	const unsigned int& valueCountInFastestDim, 
	const unsigned int& valueCountInMiddleDim, 
	const unsigned int& valueCountInSlowestDim, 
	COMMON_NS::AbstractHdfProxy* proxy)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	createLongHdf5ArrayOfValues(valueCountPerDimension, 3, proxy);
}

void AbstractValuesProperty::pushBackLongHdf5SlabArray3dOfValues(
	long* values, 
	const unsigned int& valueCountInFastestDim, 
	const unsigned int& valueCountInMiddleDim, 
	const unsigned int& valueCountInSlowestDim, 
	const unsigned int& offsetInFastestDim, 
	const unsigned int& offsetInMiddleDim, 
	const unsigned int& offsetInSlowestDim,
	COMMON_NS::AbstractHdfProxy * proxy)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	hsize_t offsetPerDimension[3] = {offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim};
	pushBackLongHdf5SlabArrayOfValues(
		values, 
		valueCountPerDimension, 
		offsetPerDimension, 
		3, 
		proxy
	);
}

void AbstractValuesProperty::createLongHdf5ArrayOfValues(
	hsize_t* numValues, 
	const unsigned int& numArrayDimensions, 
	COMMON_NS::AbstractHdfProxy* proxy)
{
	setHdfProxy(proxy);

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractValuesProperty* prop = static_cast<gsoap_resqml2_0_1::resqml2__AbstractValuesProperty*>(gsoapProxy2_0_1);

		gsoap_resqml2_0_1::resqml2__PatchOfValues* patch = gsoap_resqml2_0_1::soap_new_resqml2__PatchOfValues(gsoapProxy2_0_1->soap, 1);
		patch->RepresentationPatchIndex = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
		*(patch->RepresentationPatchIndex) = prop->PatchOfValues.size();

		// XML
		gsoap_resqml2_0_1::resqml2__IntegerHdf5Array* xmlValues = gsoap_resqml2_0_1::soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
		xmlValues->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
		xmlValues->Values->HdfProxy = proxy->newResqmlReference();
		std::ostringstream ossForHdf;
		ossForHdf << "values_patch" << *(patch->RepresentationPatchIndex);
		xmlValues->Values->PathInHdfFile = "/RESQML/" + getUuid() + "/" + ossForHdf.str();
		patch->Values = xmlValues;

		prop->PatchOfValues.push_back(patch);
	}
	else {
		throw logic_error("Not implemented yet");
	}

	// HDF

	ostringstream oss;
	oss << "values_patch" << getPatchCount() - 1;
	proxy->createArrayNd(getUuid(),
		oss.str(),
		H5T_NATIVE_LONG,
		numValues, numArrayDimensions);
}

void AbstractValuesProperty::pushBackLongHdf5SlabArrayOfValues(
	long* values, hsize_t* numValuesInEachDimension,
	hsize_t* offsetInEachDimension, const unsigned int& numArrayDimensions, 
	COMMON_NS::AbstractHdfProxy* proxy)
{
	ostringstream oss;
	oss << "values_patch" << getPatchCount() - 1;

	// HDF
	proxy->writeArrayNdSlab(getUuid(),
		oss.str(),
		H5T_NATIVE_LONG,
		values,
		numValuesInEachDimension, 
		offsetInEachDimension, 
		numArrayDimensions);
}

void AbstractValuesProperty::getLongValuesOfPatch(
	const unsigned int& patchIndex, 
	long* values, 
	hsize_t* numValuesInEachDimension,
	hsize_t* offsetInEachDimension, 
	const unsigned int& numArrayDimensions)
{
	COMMON_NS::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr) {
		throw invalid_argument("The hdf proxy does not exist");
	}

	LONG64 nullValue = (numeric_limits<long long>::min)();
	hdfProxy->readArrayNdOfLongValues(
		getPathInHdfFileOfPatch(patchIndex, nullValue),
		values, 
		numValuesInEachDimension,
		offsetInEachDimension,
		numArrayDimensions);
}

void AbstractValuesProperty::getLongValuesOf3dPatch(
	const unsigned int& patchIndex, 
	long* values, 
	const unsigned int& valueCountInFastestDim, 
	const unsigned int& valueCountInMiddleDim, 
	const unsigned int& valueCountInSlowestDim, 
	const unsigned int& offsetInFastestDim, 
	const unsigned int& offsetInMiddleDim, 
	const unsigned int& offsetInSlowestDim)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	hsize_t offsetPerDimension[3] = {offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim};

	getLongValuesOfPatch(
		patchIndex,
		values, 
		valueCountPerDimension, 
		offsetPerDimension, 
		3
	);
}

