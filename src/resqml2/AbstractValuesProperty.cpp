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

unsigned int AbstractValuesProperty::getPatchCount() const
{
	size_t result = 0;
	if (gsoapProxy2_0_1 != nullptr) {
		result = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->PatchOfValues.size();
	}
	else {
		throw logic_error("Not implemented yet");
	}

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw out_of_range("The count of the patches is too big.");
	}

	return static_cast<unsigned int>(result);
}

AbstractValuesProperty::hdfDatatypeEnum AbstractValuesProperty::getValuesHdfDatatype() const
{
	gsoap_resqml2_0_1::eml20__Hdf5Dataset* dataset = nullptr;
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues const * firstPatch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->PatchOfValues[0];
		const int valuesType = firstPatch->Values->soap_type();
		if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array) {
			dataset = static_cast<gsoap_resqml2_0_1::resqml20__BooleanHdf5Array*>(firstPatch->Values)->Values;
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
			dataset = static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(firstPatch->Values)->Values;
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			dataset = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(firstPatch->Values)->Values;
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__StringHdf5Array) {
			dataset = static_cast<gsoap_resqml2_0_1::resqml20__StringHdf5Array*>(firstPatch->Values)->Values;
		}
		else {
			return AbstractValuesProperty::UNKNOWN;
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}

	COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
	const hid_t dt = hdfProxy->getHdfDatatypeInDataset(dataset->PathInHdfFile);
	if (H5Tequal(dt, H5T_NATIVE_DOUBLE) > 0)
		return AbstractValuesProperty::DOUBLE;
	else if (H5Tequal(dt, H5T_NATIVE_FLOAT) > 0)
		return AbstractValuesProperty::FLOAT;
	else if (H5Tequal(dt, H5T_NATIVE_LLONG) > 0)
		return AbstractValuesProperty::LONG;
	else if (H5Tequal(dt, H5T_NATIVE_ULLONG) > 0)
		return AbstractValuesProperty::ULONG;
	else if (H5Tequal(dt, H5T_NATIVE_INT) > 0)
		return AbstractValuesProperty::INT;
	else if (H5Tequal(dt, H5T_NATIVE_UINT) > 0)
		return AbstractValuesProperty::UINT;
	else if (H5Tequal(dt, H5T_NATIVE_SHORT) > 0)
		return AbstractValuesProperty::SHORT;
	else if (H5Tequal(dt, H5T_NATIVE_USHORT) > 0)
		return AbstractValuesProperty::USHORT;
	else if (H5Tequal(dt, H5T_NATIVE_CHAR) > 0)
		return AbstractValuesProperty::CHAR;
	else if (H5Tequal(dt, H5T_NATIVE_UCHAR) > 0)
		return AbstractValuesProperty::UCHAR;

	return AbstractValuesProperty::UNKNOWN; // unknwown datatype...
}

std::string AbstractValuesProperty::pushBackRefToExistingIntegerDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName, LONG64 nullValue)
{
	if (hdfProxy == nullptr) {
		hdfProxy = getRepository()->getDefaultHdfProxy();
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

gsoap_resqml2_0_1::eml20__Hdf5Dataset const * AbstractValuesProperty::getDatasetOfPatch(unsigned int patchIndex, LONG64 & nullValue) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The values property patch is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];

		nullValue = (numeric_limits<long>::min)();
		int valuesType = patch->Values->soap_type();
		if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array) {
			return static_cast<gsoap_resqml2_0_1::resqml20__BooleanHdf5Array*>(patch->Values)->Values;
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
			return static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(patch->Values)->Values;
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			nullValue = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(patch->Values)->NullValue;
			return static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(patch->Values)->Values;
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__StringHdf5Array) {
			return static_cast<gsoap_resqml2_0_1::resqml20__StringHdf5Array*>(patch->Values)->Values;
		}
		else {
			throw logic_error("The type of the property values is not implemented yet.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

long AbstractValuesProperty::getLongValuesOfPatch(unsigned int patchIndex, long * values) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);
	COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);

	hdfProxy->readArrayNdOfLongValues(dataset->PathInHdfFile, values);

	return nullValue;
}

LONG64 AbstractValuesProperty::getNullValueOfPatch(unsigned int patchIndex) const
{
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

unsigned long AbstractValuesProperty::getULongValuesOfPatch(unsigned int patchIndex, unsigned long * values) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);
	COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);

	hdfProxy->readArrayNdOfULongValues(dataset->PathInHdfFile, values);

	return nullValue;
}

int AbstractValuesProperty::getIntValuesOfPatch(unsigned int patchIndex, int * values) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);
	COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);

	hdfProxy->readArrayNdOfIntValues(dataset->PathInHdfFile, values);

	return nullValue;
}

int AbstractValuesProperty::getIntValuesOfPatch(
	unsigned int patchIndex,
	int* values,
	unsigned long long* numValuesInEachDimension,
	unsigned long long* offsetInEachDimension,
	unsigned int numArrayDimensions) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);
	COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
	hdfProxy->readArrayNdOfIntValues(
		dataset->PathInHdfFile,
		values,
		numValuesInEachDimension,
		offsetInEachDimension,
		numArrayDimensions);

	return nullValue;
}

void AbstractValuesProperty::getIntValuesOf3dPatch(
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

unsigned int AbstractValuesProperty::getUIntValuesOfPatch(unsigned int patchIndex, unsigned int * values) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);
	COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);

	hdfProxy->readArrayNdOfUIntValues(dataset->PathInHdfFile, values);

	return nullValue;
}

short AbstractValuesProperty::getShortValuesOfPatch(unsigned int patchIndex, short * values) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);
	COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);

	hdfProxy->readArrayNdOfShortValues(dataset->PathInHdfFile, values);

	return nullValue;
}

unsigned short AbstractValuesProperty::getUShortValuesOfPatch(unsigned int patchIndex, unsigned short * values) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);
	COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);

	hdfProxy->readArrayNdOfUShortValues(dataset->PathInHdfFile, values);

	return nullValue;
}

char AbstractValuesProperty::getCharValuesOfPatch(unsigned int patchIndex, char * values) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);
	COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);

	hdfProxy->readArrayNdOfCharValues(dataset->PathInHdfFile, values);

	return nullValue;
}

unsigned char AbstractValuesProperty::getUCharValuesOfPatch(unsigned int patchIndex, unsigned char * values) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);
	COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);

	hdfProxy->readArrayNdOfUCharValues(dataset->PathInHdfFile, values);

	return nullValue;
}

unsigned int AbstractValuesProperty::getValuesCountOfDimensionOfPatch(unsigned int dimIndex, unsigned int patchIndex) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);
	COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);

	std::vector<hsize_t> dims = hdfProxy->readArrayDimensions(dataset->PathInHdfFile);

	if (dimIndex < dims.size())
		return dims[dimIndex];
	else{
		throw out_of_range("The dim index to get the count is out of range.");
	}
}

unsigned int AbstractValuesProperty::getDimensionsCountOfPatch(unsigned int patchIndex) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);
	COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);

	return hdfProxy->getDimensionCount(dataset->PathInHdfFile);
}

void AbstractValuesProperty::pushBackFacet(const gsoap_resqml2_0_1::resqml20__Facet & facet, const std::string & facetValue)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PropertyKindFacet* newFacet = gsoap_resqml2_0_1::soap_new_resqml20__PropertyKindFacet(gsoapProxy2_0_1->soap);
		newFacet->Facet = facet;
		newFacet->Value = facetValue;
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->Facet.push_back(newFacet);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

unsigned int AbstractValuesProperty::getFacetCount() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->Facet.size();
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::resqml20__Facet AbstractValuesProperty::getFacet(unsigned int index) const
{
	if (index >= getFacetCount()) {
		throw out_of_range("The facet index is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->Facet[index]->Facet;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string AbstractValuesProperty::getFacetValue(unsigned int index) const
{
	if (index >= getFacetCount()){
		throw out_of_range("The facet index is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->Facet[index]->Value;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

unsigned int AbstractValuesProperty::getValuesCountOfPatch (unsigned int patchIndex) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);
	COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);

	return hdfProxy->getElementCount(dataset->PathInHdfFile);
}

void AbstractValuesProperty::createLongHdf5Array3dOfValues(
	unsigned int valueCountInFastestDim, 
	unsigned int valueCountInMiddleDim, 
	unsigned int valueCountInSlowestDim, 
	COMMON_NS::AbstractHdfProxy* proxy)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	createLongHdf5ArrayOfValues(valueCountPerDimension, 3, proxy);
}

void AbstractValuesProperty::pushBackLongHdf5SlabArray3dOfValues(
	long* values, 
	unsigned int valueCountInFastestDim, 
	unsigned int valueCountInMiddleDim, 
	unsigned int valueCountInSlowestDim, 
	unsigned int offsetInFastestDim, 
	unsigned int offsetInMiddleDim, 
	unsigned int offsetInSlowestDim,
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
	unsigned int numArrayDimensions, 
	COMMON_NS::AbstractHdfProxy* proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
	}
	getRepository()->addRelationship(this, proxy);

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractValuesProperty* prop = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1);

		gsoap_resqml2_0_1::resqml20__PatchOfValues* patch = gsoap_resqml2_0_1::soap_new_resqml20__PatchOfValues(gsoapProxy2_0_1->soap);
		patch->RepresentationPatchIndex = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
		*(patch->RepresentationPatchIndex) = prop->PatchOfValues.size();

		// XML
		gsoap_resqml2_0_1::resqml20__IntegerHdf5Array* xmlValues = gsoap_resqml2_0_1::soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
		xmlValues->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
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
	hsize_t* offsetInEachDimension, unsigned int numArrayDimensions, 
	COMMON_NS::AbstractHdfProxy* proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
	}
	getRepository()->addRelationship(this, proxy);

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
	unsigned int patchIndex, 
	long* values, 
	hsize_t* numValuesInEachDimension,
	hsize_t* offsetInEachDimension, 
	unsigned int numArrayDimensions) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);
	COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);

	hdfProxy->readArrayNdOfLongValues(
		dataset->PathInHdfFile,
		values, 
		numValuesInEachDimension,
		offsetInEachDimension,
		numArrayDimensions);
}

void AbstractValuesProperty::getLongValuesOf3dPatch(
	unsigned int patchIndex, 
	long* values, 
	unsigned int valueCountInFastestDim, 
	unsigned int valueCountInMiddleDim, 
	unsigned int valueCountInSlowestDim, 
	unsigned int offsetInFastestDim, 
	unsigned int offsetInMiddleDim, 
	unsigned int offsetInSlowestDim) const
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

void AbstractValuesProperty::loadTargetRelationships()
{
	AbstractProperty::loadTargetRelationships();

	gsoap_resqml2_0_1::resqml20__AbstractValuesProperty* prop = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1);
	
	for (size_t patchIndex = 0; patchIndex < prop->PatchOfValues.size(); ++patchIndex) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues* patch = prop->PatchOfValues[patchIndex];

		gsoap_resqml2_0_1::eml20__DataObjectReference const * dor = nullptr;

		int valuesType = patch->Values->soap_type();
		if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array) {
			dor = static_cast<gsoap_resqml2_0_1::resqml20__BooleanHdf5Array*>(patch->Values)->Values->HdfProxy;
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
			dor = static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(patch->Values)->Values->HdfProxy;
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			dor = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(patch->Values)->Values->HdfProxy;
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__StringHdf5Array) {
			dor = static_cast<gsoap_resqml2_0_1::resqml20__StringHdf5Array*>(patch->Values)->Values->HdfProxy;
		}
		else {
			throw logic_error("The type of the property values is not implemented yet.");
		}
		convertDorIntoRel<COMMON_NS::AbstractHdfProxy>(dor);
	}
}
