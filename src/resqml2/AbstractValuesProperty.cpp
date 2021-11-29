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
#include "AbstractValuesProperty.h"

#include <limits>
#include <stdexcept>

#include <hdf5.h>

#include "../eml2/AbstractHdfProxy.h"

using namespace RESQML2_NS;
using namespace std;

unsigned int AbstractValuesProperty::getPatchCount() const
{
	size_t result = 0;
	if (gsoapProxy2_0_1 != nullptr) {
		result = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->PatchOfValues.size();
	}
	else if (gsoapProxy2_3 != nullptr) {
		result = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->ValuesForPatch.size();
	}
	else {
		throw logic_error("Not implemented yet");
	}

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw out_of_range("The count of the patches is too big.");
	}

	return static_cast<unsigned int>(result);
}

EML2_NS::AbstractHdfProxy * AbstractValuesProperty::getDatasetOfPatch(unsigned int patchIndex, int64_t & nullValue, std::string & dsPath) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];

		nullValue = (numeric_limits<long>::min)();
		int valuesType = patch->Values->soap_type();
		if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array) {
			dsPath = static_cast<gsoap_resqml2_0_1::resqml20__BooleanHdf5Array*>(patch->Values)->Values->PathInHdfFile;
			return getHdfProxyFromDataset(static_cast<gsoap_resqml2_0_1::resqml20__BooleanHdf5Array*>(patch->Values)->Values);
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
			dsPath = static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(patch->Values)->Values->PathInHdfFile;
			return getHdfProxyFromDataset(static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(patch->Values)->Values);
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			dsPath = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(patch->Values)->Values->PathInHdfFile;
			nullValue = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(patch->Values)->NullValue;
			return getHdfProxyFromDataset(static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(patch->Values)->Values);
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__StringHdf5Array) {
			dsPath = static_cast<gsoap_resqml2_0_1::resqml20__StringHdf5Array*>(patch->Values)->Values->PathInHdfFile;
			return getHdfProxyFromDataset(static_cast<gsoap_resqml2_0_1::resqml20__StringHdf5Array*>(patch->Values)->Values);
		}
		else {
			throw logic_error("The type of the property values is not implemented yet.");
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		nullValue = (numeric_limits<long>::min)();
		auto patch = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->ValuesForPatch[patchIndex];
		if (dynamic_cast<gsoap_eml2_3::eml23__FloatingPointExternalArray*>(patch) != nullptr) {
			dsPath = static_cast<gsoap_eml2_3::eml23__FloatingPointExternalArray*>(patch)->Values->ExternalDataArrayPart[0]->PathInExternalFile;
			return getOrCreateHdfProxyFromDataArrayPart(static_cast<gsoap_eml2_3::eml23__FloatingPointExternalArray*>(patch)->Values->ExternalDataArrayPart[0]);
		}
		int valuesType = patch->soap_type();
		if (valuesType == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray) {
			dsPath = static_cast<gsoap_eml2_3::eml23__BooleanExternalArray*>(patch)->Values->ExternalDataArrayPart[0]->PathInExternalFile;
			return getOrCreateHdfProxyFromDataArrayPart(static_cast<gsoap_eml2_3::eml23__BooleanExternalArray*>(patch)->Values->ExternalDataArrayPart[0]);
		}
		else if (valuesType == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			dsPath = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(patch)->Values->ExternalDataArrayPart[0]->PathInExternalFile;
			nullValue = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(patch)->NullValue;
			return getOrCreateHdfProxyFromDataArrayPart(static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(patch)->Values->ExternalDataArrayPart[0]);
		}
		else if (valuesType == SOAP_TYPE_gsoap_eml2_3_eml23__StringExternalArray) {
			dsPath = static_cast<gsoap_eml2_3::eml23__StringExternalArray*>(patch)->Values->ExternalDataArrayPart[0]->PathInExternalFile;
			return getOrCreateHdfProxyFromDataArrayPart(static_cast<gsoap_eml2_3::eml23__StringExternalArray*>(patch)->Values->ExternalDataArrayPart[0]);
		}
		else {
			throw logic_error("The type of the property values is not implemented yet.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

COMMON_NS::DataObjectReference AbstractValuesProperty::getHdfProxyDor(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];

		int valuesType = patch->Values->soap_type();
		if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array) {
			return static_cast<gsoap_resqml2_0_1::resqml20__BooleanHdf5Array*>(patch->Values)->Values->HdfProxy;
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
			return static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(patch->Values)->Values->HdfProxy;
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			return static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(patch->Values)->Values->HdfProxy;
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__StringHdf5Array) {
			return static_cast<gsoap_resqml2_0_1::resqml20__StringHdf5Array*>(patch->Values)->Values->HdfProxy;
		}
		else {
			throw logic_error("The type of the property values is not implemented yet.");
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		auto patch = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->ValuesForPatch[patchIndex];

		int valuesType = patch->soap_type();
		if (valuesType == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray) {
			return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<gsoap_eml2_3::eml23__BooleanExternalArray*>(patch)->Values->ExternalDataArrayPart[0]));
		}
		else if (valuesType == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray) {
			return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<gsoap_eml2_3::eml23__FloatingPointExternalArray*>(patch)->Values->ExternalDataArrayPart[0]));
		}
		else if (valuesType == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(patch)->Values->ExternalDataArrayPart[0]));
		}
		else if (valuesType == SOAP_TYPE_gsoap_eml2_3_eml23__StringExternalArray) {
			return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<gsoap_eml2_3::eml23__StringExternalArray*>(patch)->Values->ExternalDataArrayPart[0]));
		}
		else {
			throw logic_error("The type of the property values is not implemented yet.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractValuesProperty::pushBackFacet(gsoap_eml2_3::eml23__FacetKind facet, const std::string & facetValue)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PropertyKindFacet* newFacet = gsoap_resqml2_0_1::soap_new_resqml20__PropertyKindFacet(gsoapProxy2_0_1->soap);
		if (facet == gsoap_eml2_3::eml23__FacetKind::side) {
			throw invalid_argument("The facet kind \"side\" is not supported in RESQML 2.0.1");
		}
		newFacet->Facet = facet == gsoap_eml2_3::eml23__FacetKind::conditions ? gsoap_resqml2_0_1::resqml20__Facet::conditions : static_cast<gsoap_resqml2_0_1::resqml20__Facet>(static_cast<int>(facet) - 1);
		newFacet->Value = facetValue;
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->Facet.push_back(newFacet);
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::eml23__PropertyKindFacet* newFacet = gsoap_eml2_3::soap_new_eml23__PropertyKindFacet(gsoapProxy2_3->soap);
		newFacet->Facet = gsoap_eml2_3::soap_eml23__FacetKind2s(gsoapProxy2_3->soap, facet);
		newFacet->Facet = facetValue;
		static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->Facet.push_back(newFacet);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

unsigned int AbstractValuesProperty::getFacetCount() const
{
	size_t result;
	if (gsoapProxy2_0_1 != nullptr) {
		result = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->Facet.size();
	}
	else if (gsoapProxy2_3 != nullptr) {
		result = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->Facet.size();
	}
	else {
		throw logic_error("Not implemented yet");
	}

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much facets");
	}

	return static_cast<unsigned int>(result);
}

gsoap_eml2_3::eml23__FacetKind AbstractValuesProperty::getFacetKind(unsigned int index) const
{
	if (index >= getFacetCount()) {
		throw out_of_range("The facet index is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		auto facetKind = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->Facet[index];
		return facetKind->Facet == gsoap_resqml2_0_1::resqml20__Facet::conditions ? gsoap_eml2_3::eml23__FacetKind::conditions : static_cast<gsoap_eml2_3::eml23__FacetKind>(static_cast<int>(facetKind->Facet) + 1);
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->Facet[index]->Kind;
	}

	throw logic_error("Not implemented yet");
}

std::string AbstractValuesProperty::getFacetValue(unsigned int index) const
{
	if (index >= getFacetCount()){
		throw out_of_range("The facet index is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->Facet[index]->Value;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->Facet[index]->Facet;
	}
	
	throw logic_error("Not implemented yet");
}

void AbstractValuesProperty::pushBackLongHdf5Array1dOfValues(const int64_t * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy * proxy,
	int64_t nullValue)
{
	hsize_t valueCountPerDimension = valueCount;
	pushBackLongHdf5ArrayOfValues(values, &valueCountPerDimension, 1, proxy, nullValue);
}

void AbstractValuesProperty::pushBackIntHdf5Array1dOfValues(const int * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy * proxy,
	int nullValue)
{
	hsize_t valueCountPerDimension = valueCount;
	pushBackIntHdf5ArrayOfValues(values, &valueCountPerDimension, 1, proxy, nullValue);
}

void AbstractValuesProperty::pushBackShortHdf5Array1dOfValues(const short * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy * proxy,
	short nullValue)
{
	hsize_t valueCountPerDimension = valueCount;
	pushBackShortHdf5ArrayOfValues(values, &valueCountPerDimension, 1, proxy, nullValue);
}

void AbstractValuesProperty::pushBackCharHdf5Array1dOfValues(const char * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy * proxy,
	char nullValue)
{
	hsize_t valueCountPerDimension = valueCount;
	pushBackCharHdf5ArrayOfValues(values, &valueCountPerDimension, 1, proxy, nullValue);
}

void AbstractValuesProperty::pushBackLongHdf5Array2dOfValues(const int64_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	int64_t nullValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void AbstractValuesProperty::pushBackIntHdf5Array2dOfValues(const int * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	int nullValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void AbstractValuesProperty::pushBackShortHdf5Array2dOfValues(const short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	short nullValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void AbstractValuesProperty::pushBackUShortHdf5Array2dOfValues(const unsigned short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void AbstractValuesProperty::pushBackCharHdf5Array2dOfValues(const char * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	char nullValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackCharHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void AbstractValuesProperty::pushBackLongHdf5Array3dOfValues(const int64_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	int64_t nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void AbstractValuesProperty::pushBackIntHdf5Array3dOfValues(const int * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	int nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void AbstractValuesProperty::pushBackShortHdf5Array3dOfValues(const short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	short nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void AbstractValuesProperty::pushBackUShortHdf5Array3dOfValues(const unsigned short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	unsigned short nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void AbstractValuesProperty::pushBackCharHdf5Array3dOfValues(const char * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	char nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackCharHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

std::string AbstractValuesProperty::pushBackRefToExistingIntegerDataset(EML2_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName, int64_t nullValue)
{
	if (hdfProxy == nullptr) {
		hdfProxy = getRepository()->getDefaultHdfProxy();
		if (hdfProxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	if (datasetName.empty()) {
		throw std::invalid_argument("The property dataset name cannot be empty.");
	}
	if (gsoapProxy2_0_1 != nullptr && hdfProxy->getXmlNamespace() == "eml23") {
		throw std::invalid_argument("You cannot associate a RESQML 2.0.1 dataobject to an EML 2.3 HDF proxy (which is no more a dataobject by the way).");
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
		xmlValues->Values->PathInHdfFile = datasetName;

		patch->Values = xmlValues;

		prop->PatchOfValues.push_back(patch);

		return xmlValues->Values->PathInHdfFile;
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__AbstractValuesProperty* prop = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3);

		// XML
		gsoap_eml2_3::eml23__IntegerExternalArray* xmlValues = gsoap_eml2_3::soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
		xmlValues->NullValue = nullValue;
		xmlValues->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);

		auto* daPart = createExternalDataArrayPart(datasetName, hdfProxy->getElementCount(datasetName), hdfProxy);
		xmlValues->Values->ExternalDataArrayPart.push_back(daPart);

		prop->ValuesForPatch.push_back(xmlValues);

		return daPart->PathInExternalFile;
	}

	throw logic_error("Unrecognized RESQML version");
}

std::string AbstractValuesProperty::pushBackRefToExistingFloatingPointDataset(EML2_NS::AbstractHdfProxy* proxy, const std::string & datasetName)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	if (datasetName.empty()) {
		throw std::invalid_argument("The property dataset name cannot be empty.");
	}
	if (gsoapProxy2_0_1 != nullptr && proxy->getXmlNamespace() == "eml23") {
		throw std::invalid_argument("You cannot associate a RESQML 2.0.1 dataobject to an EML 2.3 HDF proxy (which is no more a dataobject by the way).");
	}

	getRepository()->addRelationship(this, proxy);
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractValuesProperty* prop = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1);

		gsoap_resqml2_0_1::resqml20__PatchOfValues* patch = gsoap_resqml2_0_1::soap_new_resqml20__PatchOfValues(gsoapProxy2_0_1->soap);
		patch->RepresentationPatchIndex = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
		*(patch->RepresentationPatchIndex) = prop->PatchOfValues.size();

		// XML
		gsoap_resqml2_0_1::resqml20__DoubleHdf5Array* xmlValues = gsoap_resqml2_0_1::soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
		xmlValues->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		xmlValues->Values->HdfProxy = proxy->newResqmlReference();
		xmlValues->Values->PathInHdfFile = datasetName;

		patch->Values = xmlValues;

		prop->PatchOfValues.push_back(patch);

		return xmlValues->Values->PathInHdfFile;
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::_resqml22__ContinuousProperty* prop = static_cast<gsoap_eml2_3::_resqml22__ContinuousProperty*>(gsoapProxy2_3);

		// XML
		gsoap_eml2_3::eml23__FloatingPointExternalArray* xmlValues = gsoap_eml2_3::soap_new_eml23__FloatingPointExternalArray(gsoapProxy2_3->soap);
		xmlValues->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);

		auto* daPart = createExternalDataArrayPart(datasetName, proxy->getElementCount(datasetName), proxy);
		xmlValues->Values->ExternalDataArrayPart.push_back(daPart);

		prop->ValuesForPatch.push_back(xmlValues);

		return daPart->PathInExternalFile;
	}

	throw logic_error("Unrecognized RESQML version");
}

void AbstractValuesProperty::pushBackLongHdf5ArrayOfValues(const int64_t * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy * proxy, int64_t nullValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	const std::string datasetName = "values_patch" + std::to_string(getPatchCount());

	proxy->writeArrayNd(getHdfGroup(),
		datasetName,
		H5T_NATIVE_INT64,
		values,
		numValues, numDimensionsInArray);

	pushBackRefToExistingIntegerDataset(proxy, getHdfGroup() + "/" + datasetName, nullValue);
}

void AbstractValuesProperty::pushBackIntHdf5ArrayOfValues(const int * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int nullValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	const std::string datasetName = "values_patch" + std::to_string(getPatchCount());

	proxy->writeArrayNd(getHdfGroup(),
		datasetName,
		H5T_NATIVE_INT,
		values,
		numValues, numDimensionsInArray);

	pushBackRefToExistingIntegerDataset(proxy, getHdfGroup() + "/" + datasetName, nullValue);
}

void AbstractValuesProperty::pushBackShortHdf5ArrayOfValues(const short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, short nullValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	const std::string datasetName = "values_patch" + std::to_string(getPatchCount());

	proxy->writeArrayNd(getHdfGroup(),
		datasetName,
		H5T_NATIVE_SHORT,
		values,
		numValues, numDimensionsInArray);

	pushBackRefToExistingIntegerDataset(proxy, getHdfGroup() + "/" + datasetName, nullValue);
}

void AbstractValuesProperty::pushBackUShortHdf5ArrayOfValues(const unsigned short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	const std::string datasetName = "values_patch" + std::to_string(getPatchCount());

	proxy->writeArrayNd(getHdfGroup(),
		datasetName,
		H5T_NATIVE_USHORT,
		values,
		numValues, numDimensionsInArray);

	pushBackRefToExistingIntegerDataset(proxy, getHdfGroup() + "/" + datasetName, nullValue);
}

void AbstractValuesProperty::pushBackCharHdf5ArrayOfValues(const char * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, char nullValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	const std::string datasetName = "values_patch" + std::to_string(getPatchCount());

	proxy->writeArrayNd(getHdfGroup(),
		datasetName,
		H5T_NATIVE_CHAR,
		values,
		numValues, numDimensionsInArray);

	pushBackRefToExistingIntegerDataset(proxy, getHdfGroup() + "/" + datasetName, nullValue);
}

int64_t AbstractValuesProperty::getLongValuesOfPatch(unsigned int patchIndex, int64_t * values) const
{
	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	hdfProxy->readArrayNdOfInt64Values(dsPath, values);

	return nullValue;
}

int64_t AbstractValuesProperty::getNullValueOfPatch(unsigned int patchIndex) const
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
	else if (gsoapProxy2_3 != nullptr) {
		auto patch = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->ValuesForPatch[patchIndex];
		if (patch->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			return static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(patch)->NullValue;
		}

		throw invalid_argument("The patch does not contain integer values.");
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

int32_t AbstractValuesProperty::getIntValuesOfPatch(unsigned int patchIndex, int32_t * values) const
{
	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	hdfProxy->readArrayNdOfIntValues(dsPath, values);

	if (nullValue < (std::numeric_limits<int32_t>::lowest)() || nullValue > (std::numeric_limits<int32_t>::max)()) {
		throw range_error("The null value is not in the int32_t range");
	}

	return static_cast<int32_t>(nullValue);
}

uint32_t AbstractValuesProperty::getUIntValuesOfPatch(unsigned int patchIndex, uint32_t * values) const
{
	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	hdfProxy->readArrayNdOfUIntValues(dsPath, values);

	if (nullValue < (std::numeric_limits<uint32_t>::lowest)() || nullValue >(std::numeric_limits<uint32_t>::max)()) {
		throw range_error("The null value is not in the uint32_t range");
	}

	return static_cast<uint32_t>(nullValue);
}

int16_t AbstractValuesProperty::getShortValuesOfPatch(unsigned int patchIndex, int16_t * values) const
{
	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	hdfProxy->readArrayNdOfShortValues(dsPath, values);

	if (nullValue < (std::numeric_limits<int16_t>::lowest)() || nullValue >(std::numeric_limits<int16_t>::max)()) {
		throw range_error("The null value is not in the int16_t range");
	}

	return static_cast<int16_t>(nullValue);
}

uint16_t AbstractValuesProperty::getUShortValuesOfPatch(unsigned int patchIndex, uint16_t * values) const
{
	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	hdfProxy->readArrayNdOfUShortValues(dsPath, values);

	if (nullValue < (std::numeric_limits<uint16_t>::lowest)() || nullValue >(std::numeric_limits<uint16_t>::max)()) {
		throw range_error("The null value is not in the uint16_t range");
	}

	return static_cast<uint16_t>(nullValue);
}

char AbstractValuesProperty::getCharValuesOfPatch(unsigned int patchIndex, char * values) const
{
	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	hdfProxy->readArrayNdOfCharValues(dsPath, values);

	if (nullValue < (std::numeric_limits<char>::lowest)() || nullValue >(std::numeric_limits<char>::max)()) {
		throw range_error("The null value is not in the char range");
	}

	return static_cast<char>(nullValue);
}

uint8_t AbstractValuesProperty::getUCharValuesOfPatch(unsigned int patchIndex, uint8_t * values) const
{
	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	hdfProxy->readArrayNdOfUCharValues(dsPath, values);

	if (nullValue < (std::numeric_limits<uint8_t>::lowest)() || nullValue >(std::numeric_limits<uint8_t>::max)()) {
		throw range_error("The null value is not in the uint8_t range");
	}

	return static_cast<uint8_t>(nullValue);
}

void AbstractValuesProperty::pushBackLongHdf5Array3dOfValues(
	uint64_t valueCountInFastestDim,
	uint64_t valueCountInMiddleDim,
	uint64_t valueCountInSlowestDim,
	int64_t nullValue,
	EML2_NS::AbstractHdfProxy* proxy)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackLongHdf5ArrayOfValues(valueCountPerDimension, 3, nullValue, proxy);
}

void AbstractValuesProperty::setValuesOfLongHdf5Array3dOfValues(
	int64_t* values,
	uint64_t valueCountInFastestDim,
	uint64_t valueCountInMiddleDim,
	uint64_t valueCountInSlowestDim,
	uint64_t offsetInFastestDim,
	uint64_t offsetInMiddleDim,
	uint64_t offsetInSlowestDim,
	EML2_NS::AbstractHdfProxy * proxy,
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

void AbstractValuesProperty::pushBackLongHdf5ArrayOfValues(
	hsize_t* numValues,
	unsigned int numArrayDimensions,
	int64_t nullValue,
	EML2_NS::AbstractHdfProxy* proxy)
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
		xmlValues->Values->PathInHdfFile = getHdfGroup() + "/values_patch" + std::to_string(getPatchCount());
		patch->Values = xmlValues;

		prop->PatchOfValues.push_back(patch);
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__AbstractValuesProperty* prop = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3);

		size_t valueCount = numValues[0];
		for (size_t dimIndex = 1; dimIndex < numArrayDimensions; ++dimIndex) {
			valueCount *= numValues[dimIndex];
		}

		// XML
		gsoap_eml2_3::eml23__IntegerExternalArray* xmlValues = gsoap_eml2_3::soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
		xmlValues->NullValue = nullValue;
		xmlValues->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
		auto* daPart = createExternalDataArrayPart(getHdfGroup() +"/values_patch" + std::to_string(getPatchCount()), valueCount, proxy);
		xmlValues->Values->ExternalDataArrayPart.push_back(daPart);

		prop->ValuesForPatch.push_back(xmlValues);
	}
	else {
		throw logic_error("Not implemented yet");
	}

	// HDF
	proxy->createArrayNd(getHdfGroup(),
		"values_patch" + std::to_string(getPatchCount() - 1),
		H5T_NATIVE_INT64,
		numValues, numArrayDimensions);
}

void AbstractValuesProperty::setValuesOfLongHdf5ArrayOfValues(
	int64_t* values, hsize_t const * numValuesInEachDimension,
	hsize_t const * offsetInEachDimension, unsigned int numArrayDimensions,
	EML2_NS::AbstractHdfProxy* proxy,
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

	// HDF
	proxy->writeArrayNdSlab(getHdfGroup(),
		"values_patch" + std::to_string(patchIndex == (numeric_limits<unsigned int>::max)() ? getPatchCount() - 1 : patchIndex),
		H5T_NATIVE_INT64,
		values,
		numValuesInEachDimension,
		offsetInEachDimension,
		numArrayDimensions);
}

void AbstractValuesProperty::getLongValuesOfPatch(
	unsigned int patchIndex,
	int64_t* values,
	hsize_t const * numValuesInEachDimension,
	hsize_t const * offsetInEachDimension,
	unsigned int numArrayDimensions) const
{
	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	hdfProxy->readArrayNdOfInt64Values(
		dsPath,
		values,
		numValuesInEachDimension,
		offsetInEachDimension,
		numArrayDimensions);
}

void AbstractValuesProperty::getLongValuesOf3dPatch(
	unsigned int patchIndex,
	int64_t* values,
	uint64_t valueCountInFastestDim,
	uint64_t valueCountInMiddleDim,
	uint64_t valueCountInSlowestDim,
	uint64_t offsetInFastestDim,
	uint64_t offsetInMiddleDim,
	uint64_t offsetInSlowestDim) const
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

int32_t AbstractValuesProperty::getIntValuesOfPatch(
	unsigned int patchIndex,
	int32_t* values,
	unsigned long long* numValuesInEachDimension,
	unsigned long long* offsetInEachDimension,
	unsigned int numArrayDimensions) const
{
	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	hdfProxy->readArrayNdOfIntValues(
		dsPath,
		values,
		numValuesInEachDimension,
		offsetInEachDimension,
		numArrayDimensions);

	if (nullValue < (std::numeric_limits<int32_t>::lowest)() || nullValue > (std::numeric_limits<int32_t>::max)()) {
		throw range_error("The null value is not in the int32_t range");
	}

	return static_cast<int32_t>(nullValue);
}

void AbstractValuesProperty::getIntValuesOf3dPatch(
	unsigned int patchIndex,
	int32_t* values,
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

//***********************************
//****** FLOATING POINT *************
//***********************************

void AbstractValuesProperty::pushBackDoubleHdf5Array1dOfValues(const double * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy * proxy)
{
	const hsize_t valueCountPerDimension = valueCount;
	pushBackDoubleHdf5ArrayOfValues(values, &valueCountPerDimension, 1, proxy);
}

void AbstractValuesProperty::pushBackDoubleHdf5Array2dOfValues(const double * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy)
{
	const hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy);
}

void AbstractValuesProperty::pushBackDoubleHdf5Array3dOfValues(const double * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy)
{
	const hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy);
}

void AbstractValuesProperty::pushBackDoubleHdf5ArrayOfValues(double const * values, unsigned long long const * numValues, unsigned int numArrayDimensions, EML2_NS::AbstractHdfProxy * proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const std::string datasetName = "values_patch" + std::to_string(getPatchCount());

	// HDF
	proxy->writeArrayNd(getHdfGroup(),
		datasetName,
		H5T_NATIVE_DOUBLE,
		values,
		numValues, numArrayDimensions);

	pushBackRefToExistingFloatingPointDataset(proxy, getHdfGroup() + "/" + datasetName);
}

void AbstractValuesProperty::pushBackFloatHdf5Array1dOfValues(const float * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy * proxy)
{
	const hsize_t valueCountPerDimension = valueCount;
	pushBackFloatHdf5ArrayOfValues(values, &valueCountPerDimension, 1, proxy);
}

void AbstractValuesProperty::pushBackFloatHdf5Array2dOfValues(const float * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy)
{
	const hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy);
}

void AbstractValuesProperty::pushBackFloatHdf5Array3dOfValues(const float * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy)
{
	const hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy);
}

void AbstractValuesProperty::pushBackFloatHdf5Array3dOfValues(
	uint64_t valueCountInFastestDim,
	uint64_t valueCountInMiddleDim,
	uint64_t valueCountInSlowestDim,
	EML2_NS::AbstractHdfProxy* proxy)
{
	const hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackFloatHdf5ArrayOfValues(valueCountPerDimension, 3, proxy);
}

void AbstractValuesProperty::setValuesOfFloatHdf5Array3dOfValues(
	float const * values,
	uint64_t valueCountInFastestDim,
	uint64_t valueCountInMiddleDim,
	uint64_t valueCountInSlowestDim,
	uint64_t offsetInFastestDim,
	uint64_t offsetInMiddleDim,
	uint64_t offsetInSlowestDim,
	EML2_NS::AbstractHdfProxy* proxy,
	unsigned int patchIndex)
{
	const hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	const hsize_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };
	setValuesOfFloatHdf5ArrayOfValues(
		values,
		valueCountPerDimension,
		offsetPerDimension,
		3,
		proxy,
		patchIndex
	);
}

void AbstractValuesProperty::pushBackFloatHdf5ArrayOfValues(float const * values, unsigned long long const * numValues, unsigned int numArrayDimensions, EML2_NS::AbstractHdfProxy * proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const std::string datasetName = "values_patch" + std::to_string(getPatchCount());

	// HDF
	proxy->writeArrayNd(getHdfGroup(),
		datasetName,
		H5T_NATIVE_FLOAT,
		values,
		numValues, numArrayDimensions);

	pushBackRefToExistingFloatingPointDataset(proxy, getHdfGroup() + "/" + datasetName);
}

void AbstractValuesProperty::pushBackFloatHdf5ArrayOfValues(
	unsigned long long const * numValues,
	unsigned int numArrayDimensions,
	EML2_NS::AbstractHdfProxy* proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const std::string datasetName = "values_patch" + std::to_string(getPatchCount());

	// HDF
	proxy->createArrayNd(getHdfGroup(),
		datasetName,
		H5T_NATIVE_FLOAT,
		numValues, numArrayDimensions);

	pushBackRefToExistingFloatingPointDataset(proxy, getHdfGroup() + "/" + datasetName);
}

void AbstractValuesProperty::setValuesOfFloatHdf5ArrayOfValues(
	float const * values, unsigned long long const * numValuesInEachDimension,
	unsigned long long const * offsetInEachDimension, unsigned int numArrayDimensions,
	EML2_NS::AbstractHdfProxy* proxy,
	unsigned int patchIndex)
{
	if (patchIndex >= getPatchCount() && patchIndex != (numeric_limits<unsigned int>::max)()) {
		throw out_of_range("The values property patch is out of range");
	}

	// HDF
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	proxy->writeArrayNdSlab(
		getHdfGroup(),
		"values_patch" + std::to_string(patchIndex == (numeric_limits<unsigned int>::max)() ? getPatchCount() - 1 : patchIndex),
		H5T_NATIVE_FLOAT,
		values,
		numValuesInEachDimension,
		offsetInEachDimension,
		numArrayDimensions);
}

void AbstractValuesProperty::getDoubleValuesOfPatch(unsigned int patchIndex, double * values) const
{
	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string datasetPath;
	EML2_NS::AbstractHdfProxy* hdfProxy = getDatasetOfPatch(patchIndex, nullValue, datasetPath);

	hdfProxy->readArrayNdOfDoubleValues(datasetPath, values);
}

void AbstractValuesProperty::getFloatValuesOfPatch(unsigned int patchIndex, float * values) const
{
	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string datasetPath;
	EML2_NS::AbstractHdfProxy* hdfProxy = getDatasetOfPatch(patchIndex, nullValue, datasetPath);

	hdfProxy->readArrayNdOfFloatValues(datasetPath, values);
}

void AbstractValuesProperty::getFloatValuesOfPatch(
	unsigned int patchIndex,
	float* values,
	unsigned long long const * numValuesInEachDimension,
	unsigned long long const * offsetInEachDimension,
	unsigned int numArrayDimensions) const
{
	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string datasetPath;
	EML2_NS::AbstractHdfProxy* hdfProxy = getDatasetOfPatch(patchIndex, nullValue, datasetPath);

	hdfProxy->readArrayNdOfFloatValues(
		datasetPath,
		values,
		numValuesInEachDimension,
		offsetInEachDimension,
		numArrayDimensions);
}

void AbstractValuesProperty::getFloatValuesOf3dPatch(
	unsigned int patchIndex,
	float* values,
	uint64_t valueCountInFastestDim,
	uint64_t valueCountInMiddleDim,
	uint64_t valueCountInSlowestDim,
	uint64_t offsetInFastestDim,
	uint64_t offsetInMiddleDim,
	uint64_t offsetInSlowestDim) const
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	hsize_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };

	getFloatValuesOfPatch(
		patchIndex,
		values,
		valueCountPerDimension,
		offsetPerDimension,
		3
	);
}
