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

#include "../eml2/PropertyKind.h"
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

COMMON_NS::AbstractObject::hdfDatatypeEnum AbstractValuesProperty::getValuesHdfDatatype() const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(0, nullValue, dsPath);

	const hid_t dt = hdfProxy->getHdfDatatypeInDataset(dsPath);
	if (H5Tequal(dt, H5T_NATIVE_DOUBLE) > 0)
		return AbstractValuesProperty::DOUBLE;
	else if (H5Tequal(dt, H5T_NATIVE_FLOAT) > 0)
		return AbstractValuesProperty::FLOAT;
	else if (H5Tequal(dt, H5T_NATIVE_LLONG) > 0)
		return AbstractValuesProperty::LONG_64;
	else if (H5Tequal(dt, H5T_NATIVE_ULLONG) > 0)
		return AbstractValuesProperty::ULONG_64;
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

EML2_NS::AbstractHdfProxy * AbstractValuesProperty::getDatasetOfPatch(unsigned int patchIndex, LONG64 & nullValue, std::string & dsPath) const
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
			dsPath = static_cast<gsoap_eml2_3::eml23__FloatingPointExternalArray*>(patch)->Values->ExternalFileProxy[0]->PathInExternalFile;
			return getHdfProxyFromDataset(static_cast<gsoap_eml2_3::eml23__FloatingPointExternalArray*>(patch)->Values->ExternalFileProxy[0]);
		}
		int valuesType = patch->soap_type();
		if (valuesType == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray) {
			dsPath = static_cast<gsoap_eml2_3::eml23__BooleanExternalArray*>(patch)->Values->ExternalFileProxy[0]->PathInExternalFile;
			return getHdfProxyFromDataset(static_cast<gsoap_eml2_3::eml23__BooleanExternalArray*>(patch)->Values->ExternalFileProxy[0]);
		}
		else if (valuesType == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			dsPath = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(patch)->Values->ExternalFileProxy[0]->PathInExternalFile;
			nullValue = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(patch)->NullValue;
			return getHdfProxyFromDataset(static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(patch)->Values->ExternalFileProxy[0]);
		}
		else if (valuesType == SOAP_TYPE_gsoap_eml2_3_eml23__StringExternalArray) {
			dsPath = static_cast<gsoap_eml2_3::eml23__StringExternalArray*>(patch)->Values->ExternalFileProxy[0]->PathInExternalFile;
			return getHdfProxyFromDataset(static_cast<gsoap_eml2_3::eml23__StringExternalArray*>(patch)->Values->ExternalFileProxy[0]);
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
		if (dynamic_cast<gsoap_eml2_3::eml23__FloatingPointExternalArray*>(patch) != nullptr) {
			return static_cast<gsoap_eml2_3::eml23__FloatingPointExternalArray*>(patch)->Values->ExternalFileProxy[0]->EpcExternalPartReference;
		}
		int valuesType = patch->soap_type();
		if (valuesType == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray) {
			return static_cast<gsoap_eml2_3::eml23__BooleanExternalArray*>(patch)->Values->ExternalFileProxy[0]->EpcExternalPartReference;
		}
		else if (valuesType == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			return static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(patch)->Values->ExternalFileProxy[0]->EpcExternalPartReference;
		}
		else if (valuesType == SOAP_TYPE_gsoap_eml2_3_eml23__StringExternalArray) {
			return static_cast<gsoap_eml2_3::eml23__StringExternalArray*>(patch)->Values->ExternalFileProxy[0]->EpcExternalPartReference;
		}
		else {
			throw logic_error("The type of the property values is not implemented yet.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

unsigned int AbstractValuesProperty::getValuesCountOfDimensionOfPatch(unsigned int dimIndex, unsigned int patchIndex) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	std::vector<hsize_t> dims = hdfProxy->readArrayDimensions(dsPath);

	if (dimIndex < dims.size()) {
		return dims[dimIndex];
	}

	throw out_of_range("The dim index to get the count is out of range.");
}

unsigned int AbstractValuesProperty::getDimensionsCountOfPatch(unsigned int patchIndex) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	return hdfProxy->getDimensionCount(dsPath);
}

void AbstractValuesProperty::pushBackFacet(gsoap_eml2_3::eml23__FacetKind facet, const std::string & facetValue)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PropertyKindFacet* newFacet = gsoap_resqml2_0_1::soap_new_resqml20__PropertyKindFacet(gsoapProxy2_0_1->soap);
		if (facet == gsoap_eml2_3::eml23__FacetKind__side) {
			throw invalid_argument("The facet kind \"side\" is not supported in RESQML 2.0.1");
		}
		newFacet->Facet = facet == gsoap_eml2_3::eml23__FacetKind__conditions ? gsoap_resqml2_0_1::resqml20__Facet__conditions : static_cast<gsoap_resqml2_0_1::resqml20__Facet>(facet - 1);
		newFacet->Value = facetValue;
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->Facet.push_back(newFacet);
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::eml23__PropertyKindFacet* newFacet = gsoap_eml2_3::soap_new_eml23__PropertyKindFacet(gsoapProxy2_3->soap);
		newFacet->Facet = facet;
		newFacet->Facet = facetValue;
		static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->Facet.push_back(newFacet);
	}

	throw logic_error("Not implemented yet");
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
		return facetKind->Facet == gsoap_resqml2_0_1::resqml20__Facet__conditions ? gsoap_eml2_3::eml23__FacetKind__conditions : static_cast<gsoap_eml2_3::eml23__FacetKind>(facetKind->Facet + 1);
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

unsigned int AbstractValuesProperty::getValuesCountOfPatch (unsigned int patchIndex) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	return hdfProxy->getElementCount(dsPath);
}

void AbstractValuesProperty::loadTargetRelationships()
{
	AbstractProperty::loadTargetRelationships();

	for (size_t patchIndex = 0; patchIndex < getPatchCount(); ++patchIndex) {
		convertDorIntoRel(getHdfProxyDor(patchIndex));
	}
}
