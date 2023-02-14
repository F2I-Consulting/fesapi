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

#include "../eml2/AbstractHdfProxy.h"

using namespace RESQML2_NS;
using namespace std;

uint64_t AbstractValuesProperty::getPatchCount() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->PatchOfValues.size();
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->ValuesForPatch.size();
	}

	throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
}

COMMON_NS::AbstractObject::numericalDatatypeEnum AbstractValuesProperty::getValuesHdfDatatype() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->PatchOfValues[0];

		switch (patch->Values->soap_type()) {
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray:
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray:
		{
			return COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE;
		}
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray:
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray:
		{
			return COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64;
		}
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		auto patch = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->ValuesForPatch[0];
		switch (patch->soap_type()) {
		case SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray:
		case SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray:
		{
			return COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE;
		}
		case SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray:
		case SOAP_TYPE_gsoap_eml2_3_eml23__IntegerLatticeArray:
		{
			return COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64;
		}
		}
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}

	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(0, nullValue, dsPath);

	return hdfProxy->getNumericalDatatype(dsPath);
}

uint64_t AbstractValuesProperty::getValuesCountOfDimensionOfPatch(uint64_t dimIndex, uint64_t patchIndex) const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];

		switch (patch->Values->soap_type()) {
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray:
		{
			return static_cast<gsoap_resqml2_0_1::resqml20__DoubleConstantArray*>(patch->Values)->Count;
		}
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray:
		{
			return static_cast<gsoap_resqml2_0_1::resqml20__DoubleLatticeArray*>(patch->Values)->Offset[dimIndex]->Count + 1;
		}
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray:
		{
			return static_cast<gsoap_resqml2_0_1::resqml20__IntegerConstantArray*>(patch->Values)->Count;
		}
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray:
		{
			return static_cast<gsoap_resqml2_0_1::resqml20__IntegerLatticeArray*>(patch->Values)->Offset[dimIndex]->Count + 1;
		}
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		auto patch = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->ValuesForPatch[patchIndex];
		switch (patch->soap_type()) {
		case SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray:
		{
			return static_cast<gsoap_eml2_3::eml23__FloatingPointConstantArray*>(patch)->Count;
		}
		case SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray:
		{
			return static_cast<gsoap_eml2_3::eml23__FloatingPointLatticeArray*>(patch)->Offset[dimIndex]->Count + 1;
		}
		case SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray:
		{
			return static_cast<gsoap_eml2_3::eml23__IntegerConstantArray*>(patch)->Count;
		}
		case SOAP_TYPE_gsoap_eml2_3_eml23__IntegerLatticeArray:
		{
			return static_cast<gsoap_eml2_3::eml23__IntegerLatticeArray*>(patch)->Offset[dimIndex]->Count + 1;
		}
		}
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}

	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	std::vector<uint32_t> dims = hdfProxy->getElementCountPerDimension(dsPath);

	if (dimIndex < dims.size()) {
		return dims[dimIndex];
	}

	throw out_of_range("The dim index to get the count is out of range.");
}

uint64_t AbstractValuesProperty::getDimensionsCountOfPatch(uint64_t patchIndex) const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];

		switch (patch->Values->soap_type()) {
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray:
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray:
		{
			return 1;
		}
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray:
		{
			return static_cast<gsoap_resqml2_0_1::resqml20__DoubleLatticeArray*>(patch->Values)->Offset.size();
		}
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray:
		{
			return static_cast<gsoap_resqml2_0_1::resqml20__IntegerLatticeArray*>(patch->Values)->Offset.size();
		}
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		auto patch = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->ValuesForPatch[patchIndex];
		switch (patch->soap_type()) {
		case SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray:
		case SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray:
		{
			return 1;
		}
		case SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray:
		{
			return static_cast<gsoap_eml2_3::eml23__FloatingPointLatticeArray*>(patch)->Offset.size();
		}
		case SOAP_TYPE_gsoap_eml2_3_eml23__IntegerLatticeArray:
		{
			return static_cast<gsoap_eml2_3::eml23__IntegerLatticeArray*>(patch)->Offset.size();
		}
		}
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}

	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	return hdfProxy->getDimensionCount(dsPath);
}

EML2_NS::AbstractHdfProxy * AbstractValuesProperty::getDatasetOfPatch(uint64_t patchIndex, int64_t & nullValue, std::string & dsPath) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];

		nullValue = (numeric_limits<int64_t>::min)();
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
		nullValue = (numeric_limits<int64_t>::min)();
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
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}
}

COMMON_NS::DataObjectReference AbstractValuesProperty::getHdfProxyDor(uint64_t patchIndex) const
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
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}

	return COMMON_NS::DataObjectReference();
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
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}
}

uint64_t AbstractValuesProperty::getFacetCount() const
{
	size_t result;
	if (gsoapProxy2_0_1 != nullptr) {
		result = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->Facet.size();
	}
	else if (gsoapProxy2_3 != nullptr) {
		result = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->Facet.size();
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}

	return result;
}

gsoap_eml2_3::eml23__FacetKind AbstractValuesProperty::getFacetKind(uint64_t index) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		auto facetKind = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->Facet.at(index);
		return facetKind->Facet == gsoap_resqml2_0_1::resqml20__Facet::conditions ? gsoap_eml2_3::eml23__FacetKind::conditions : static_cast<gsoap_eml2_3::eml23__FacetKind>(static_cast<int>(facetKind->Facet) + 1);
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->Facet.at(index)->Kind;
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}
}

std::string AbstractValuesProperty::getFacetValue(uint64_t index) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->Facet.at(index)->Value;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->Facet.at(index)->Facet;
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}
}

void AbstractValuesProperty::pushBackIntegerConstantArrayOfValues(int64_t value, uint64_t valueCount)
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractValuesProperty* prop = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1);

		gsoap_resqml2_0_1::resqml20__PatchOfValues* patch = gsoap_resqml2_0_1::soap_new_resqml20__PatchOfValues(gsoapProxy2_0_1->soap);
		patch->RepresentationPatchIndex = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
		*(patch->RepresentationPatchIndex) = prop->PatchOfValues.size();

		// XML
		gsoap_resqml2_0_1::resqml20__IntegerConstantArray* xmlValues = gsoap_resqml2_0_1::soap_new_resqml20__IntegerConstantArray(gsoapProxy2_0_1->soap);
		xmlValues->Count = valueCount;
		xmlValues->Value = value;

		patch->Values = xmlValues;

		prop->PatchOfValues.push_back(patch);
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__AbstractValuesProperty* prop = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3);

		// XML
		gsoap_eml2_3::eml23__IntegerConstantArray* xmlValues = gsoap_eml2_3::soap_new_eml23__IntegerConstantArray(gsoapProxy2_3->soap);
		xmlValues->Count = valueCount;
		xmlValues->Value = value;

		prop->ValuesForPatch.push_back(xmlValues);
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}
}

void AbstractValuesProperty::pushBackIntHdf5Array1dOfValues(const int * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy * proxy,
	int nullValue)
{
	pushBackIntHdf5ArrayOfValues(values, &valueCount, 1, proxy, nullValue);
}

void AbstractValuesProperty::pushBackShortHdf5Array1dOfValues(const short * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy * proxy,
	short nullValue)
{
	pushBackShortHdf5ArrayOfValues(values, &valueCount, 1, proxy, nullValue);
}

void AbstractValuesProperty::pushBackInt8Hdf5Array1dOfValues(const int8_t * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy * proxy,
	int8_t nullValue)
{
	pushBackInt8Hdf5ArrayOfValues(values, &valueCount, 1, proxy, nullValue);
}

void AbstractValuesProperty::pushBackIntHdf5Array2dOfValues(const int * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	int nullValue)
{
	uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void AbstractValuesProperty::pushBackShortHdf5Array2dOfValues(const short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	short nullValue)
{
	uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void AbstractValuesProperty::pushBackUShortHdf5Array2dOfValues(const unsigned short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue)
{
	uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void AbstractValuesProperty::pushBackInt8Hdf5Array2dOfValues(const int8_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	int8_t nullValue)
{
	uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackInt8Hdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void AbstractValuesProperty::pushBackIntHdf5Array3dOfValues(const int * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	int nullValue)
{
	uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void AbstractValuesProperty::pushBackShortHdf5Array3dOfValues(const short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	short nullValue)
{
	uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void AbstractValuesProperty::pushBackUShortHdf5Array3dOfValues(const unsigned short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	unsigned short nullValue)
{
	uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void AbstractValuesProperty::pushBackInt8Hdf5Array3dOfValues(const int8_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	int8_t nullValue)
{
	uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackInt8Hdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
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
		throw std::invalid_argument("You cannot associate a RESQML 2.0.1 property to an EML 2.3 HDF proxy (which is no more a dataobject by the way).");
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
		xmlValues->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
		auto dsPart = gsoap_eml2_3::soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
		dsPart->EpcExternalPartReference = hdfProxy->newEml23Reference();

		if (datasetName.empty()) {
			ostringstream ossForHdf;
			ossForHdf << "values_patch" << getPatchCount();
			dsPart->PathInExternalFile = getHdfGroup() + "/" + ossForHdf.str();
		}
		else {
			dsPart->PathInExternalFile = datasetName;
		}

		xmlValues->Values->ExternalFileProxy.push_back(dsPart);

		prop->ValuesForPatch.push_back(xmlValues);

		return dsPart->PathInExternalFile;
	}

	throw logic_error("Unrecognized RESQML version");
}

std::string AbstractValuesProperty::pushBackRefToExistingFloatingPointDataset(EML2_NS::AbstractHdfProxy* proxy, const std::string & datasetName)
{
	cannotBePartial();

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
		throw std::invalid_argument("You cannot associate a RESQML 2.0.1 property to an EML 2.3 HDF proxy (which is no more a dataobject by the way).");
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
		ostringstream oss;
		gsoap_eml2_3::eml23__FloatingPointExternalArray* xmlValues = gsoap_eml2_3::soap_new_eml23__FloatingPointExternalArray(gsoapProxy2_3->soap);
		xmlValues->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
		auto dsPart = gsoap_eml2_3::soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
		dsPart->EpcExternalPartReference = proxy->newEml23Reference();

		if (datasetName.empty()) {
			ostringstream ossForHdf;
			ossForHdf << "values_patch" << prop->ValuesForPatch.size();
			dsPart->PathInExternalFile = getHdfGroup() + "/" + ossForHdf.str();
		}
		else {
			dsPart->PathInExternalFile = datasetName;
		}
		xmlValues->Values->ExternalFileProxy.push_back(dsPart);

		prop->ValuesForPatch.push_back(xmlValues);

		return dsPart->PathInExternalFile;
	}

	throw logic_error("Unrecognized RESQML version");
}

void AbstractValuesProperty::pushBackInt64Hdf5ArrayOfValues(const int64_t * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy * proxy, int64_t nullValue)
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
		COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64,
		values,
		numValues, numDimensionsInArray);

	pushBackRefToExistingIntegerDataset(proxy, getHdfGroup() + "/" + datasetName, nullValue);
}

void AbstractValuesProperty::pushBackIntHdf5ArrayOfValues(const int * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int nullValue)
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
		COMMON_NS::AbstractObject::numericalDatatypeEnum::INT32,
		values,
		numValues, numDimensionsInArray);

	pushBackRefToExistingIntegerDataset(proxy, getHdfGroup() + "/" + datasetName, nullValue);
}

void AbstractValuesProperty::pushBackShortHdf5ArrayOfValues(const short * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, short nullValue)
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
		COMMON_NS::AbstractObject::numericalDatatypeEnum::INT16,
		values,
		numValues, numDimensionsInArray);

	pushBackRefToExistingIntegerDataset(proxy, getHdfGroup() + "/" + datasetName, nullValue);
}

void AbstractValuesProperty::pushBackUShortHdf5ArrayOfValues(const unsigned short * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue)
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
		COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT16,
		values,
		numValues, numDimensionsInArray);

	pushBackRefToExistingIntegerDataset(proxy, getHdfGroup() + "/" + datasetName, nullValue);
}

void AbstractValuesProperty::pushBackInt8Hdf5ArrayOfValues(const int8_t * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue)
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
		COMMON_NS::AbstractObject::numericalDatatypeEnum::INT8,
		values,
		numValues, numDimensionsInArray);

	pushBackRefToExistingIntegerDataset(proxy, getHdfGroup() + "/" + datasetName, nullValue);
}

bool AbstractValuesProperty::hasConstantValues(uint64_t patchIndex) const {
	cannotBePartial();
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		auto const* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty const*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];
		return patch->Values->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray ||
			patch->Values->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray;
	}
	else if (gsoapProxy2_3 != nullptr) {
		auto const* patch = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty const*>(gsoapProxy2_3)->ValuesForPatch[patchIndex];
		return patch->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray ||
			patch->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray;
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}
}

int64_t AbstractValuesProperty::getInt64ConstantValuesOfPatch(uint64_t patchIndex) const {
	if (!hasConstantValues(patchIndex)) {
		throw std::invalid_argument("The property " + getUuid() + " has not got constant values");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		auto const* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty const*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];
		if (patch->Values->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray) {
			return static_cast<gsoap_resqml2_0_1::resqml20__IntegerConstantArray const*>(patch->Values)->Value;
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		auto const* patch = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty const*>(gsoapProxy2_3)->ValuesForPatch[patchIndex];
		if (patch->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray) {
			return static_cast<gsoap_eml2_3::eml23__IntegerConstantArray const*>(patch)->Value;
		}
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}

	throw std::invalid_argument("The property " + getUuid() + " has constant values which are not integer ones.");
}

double AbstractValuesProperty::getDoubleConstantValuesOfPatch(uint64_t patchIndex) const {
	if (!hasConstantValues(patchIndex)) {
		throw std::invalid_argument("The property " + getUuid() + " has not got constant values");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		auto const* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty const*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];
		if (patch->Values->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray) {
			return static_cast<gsoap_resqml2_0_1::resqml20__DoubleConstantArray const*>(patch->Values)->Value;
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		auto const* patch = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty const*>(gsoapProxy2_3)->ValuesForPatch[patchIndex];
		if (patch->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray) {
			return static_cast<gsoap_eml2_3::eml23__FloatingPointConstantArray const*>(patch)->Value;
		}
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}

	throw std::invalid_argument("The property " + getUuid() + " has constant values which are not floating point ones.");
}

int64_t AbstractValuesProperty::getInt64ValuesOfPatch(uint64_t patchIndex, int64_t * values) const
{
	cannotBePartial();
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues const* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty const*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];
		auto const* xmlArray = dynamic_cast<gsoap_resqml2_0_1::resqml20__AbstractIntegerArray const*>(patch->Values);
		if (xmlArray != nullptr) {
			return readArrayNdOfInt64Values(xmlArray, values);
		}
		else {
			throw logic_error("Reading integer values from a non integer array is not supported.");
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::eml23__AbstractValueArray const* xmlValues = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->ValuesForPatch[patchIndex];
		auto const* xmlArray = dynamic_cast<gsoap_eml2_3::eml23__AbstractIntegerArray const*>(xmlValues);
		if (xmlArray != nullptr) {
			return readArrayNdOfInt64Values(xmlArray, values);
		}
		else {
			throw logic_error("Reading integer values from a non integer array is not supported.");
		}
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}
}

int64_t AbstractValuesProperty::getNullValueOfPatch(uint64_t patchIndex) const
{
	cannotBePartial();
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];
		if (patch->Values->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			return static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(patch->Values)->NullValue;
		}
		else if (patch->Values->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray) {
			return static_cast<gsoap_resqml2_0_1::resqml20__IntegerConstantArray const*>(patch->Values)->Value != (std::numeric_limits<int64_t>::max)()
				? (std::numeric_limits<int64_t>::max)()
				: (std::numeric_limits<int64_t>::min)();
		}
		else if (patch->Values->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray) {
			return (std::numeric_limits<int64_t>::max)();
		}
		else if (patch->Values->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerRangeArray) {
			return (std::numeric_limits<int64_t>::max)();
		}

		throw invalid_argument("The patch does not contain integer values.");
	}
	else if (gsoapProxy2_3 != nullptr) {
		auto patch = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->ValuesForPatch[patchIndex];
		if (patch->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			return static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(patch)->NullValue;
		}
		else if (patch->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray) {
			return static_cast<gsoap_eml2_3::eml23__IntegerConstantArray const*>(patch)->Value != (std::numeric_limits<int64_t>::max)()
				? (std::numeric_limits<int64_t>::max)()
				: (std::numeric_limits<int64_t>::min)();
		}
		else if (patch->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerLatticeArray) {
			return (std::numeric_limits<int64_t>::max)();
		}
		else if (patch->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerRangeArray) {
			return (std::numeric_limits<int64_t>::max)();
		}

		throw invalid_argument("The patch does not contain integer values.");
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

int32_t AbstractValuesProperty::getIntValuesOfPatch(uint64_t patchIndex, int32_t * values) const
{
	cannotBePartial();
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues const* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty const*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];
		auto const* xmlArray = dynamic_cast<gsoap_resqml2_0_1::resqml20__AbstractIntegerArray const*>(patch->Values);
		if (xmlArray != nullptr) {
			return readArrayNdOfInt32Values(xmlArray, values);
		}
		else {
			throw logic_error("Reading integer values from a non integer array is not supported.");
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::eml23__AbstractValueArray const* xmlValues = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->ValuesForPatch[patchIndex];
		auto const* xmlArray = dynamic_cast<gsoap_eml2_3::eml23__AbstractIntegerArray const*>(xmlValues);
		if (xmlArray != nullptr) {
			return readArrayNdOfInt32Values(xmlArray, values);
		}
		else {
			throw logic_error("Reading integer values from a non integer array is not supported.");
		}
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}
}

uint32_t AbstractValuesProperty::getUIntValuesOfPatch(uint64_t patchIndex, uint32_t * values) const
{
	cannotBePartial();
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues const* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty const*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];
		auto const* xmlArray = dynamic_cast<gsoap_resqml2_0_1::resqml20__AbstractIntegerArray const*>(patch->Values);
		if (xmlArray != nullptr) {
			return readArrayNdOfUInt32Values(xmlArray, values);
		}
		else {
			throw logic_error("Reading integer values from a non integer array is not supported.");
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::eml23__AbstractValueArray const* xmlValues = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->ValuesForPatch[patchIndex];
		auto const* xmlArray = dynamic_cast<gsoap_eml2_3::eml23__AbstractIntegerArray const*>(xmlValues);
		if (xmlArray != nullptr) {
			return readArrayNdOfUInt32Values(xmlArray, values);
		}
		else {
			throw logic_error("Reading integer values from a non integer array is not supported.");
		}
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}
}

int16_t AbstractValuesProperty::getShortValuesOfPatch(uint64_t patchIndex, int16_t * values) const
{
	cannotBePartial();
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues const* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty const*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];
		auto const* xmlArray = dynamic_cast<gsoap_resqml2_0_1::resqml20__AbstractIntegerArray const*>(patch->Values);
		if (xmlArray != nullptr) {
			return readArrayNdOfInt16Values(xmlArray, values);
		}
		else {
			throw logic_error("Reading integer values from a non integer array is not supported.");
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::eml23__AbstractValueArray const* xmlValues = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->ValuesForPatch[patchIndex];
		auto const* xmlArray = dynamic_cast<gsoap_eml2_3::eml23__AbstractIntegerArray const*>(xmlValues);
		if (xmlArray != nullptr) {
			return readArrayNdOfInt16Values(xmlArray, values);
		}
		else {
			throw logic_error("Reading integer values from a non integer array is not supported.");
		}
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}
}

uint16_t AbstractValuesProperty::getUShortValuesOfPatch(uint64_t patchIndex, uint16_t * values) const
{
	cannotBePartial();
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues const* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty const*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];
		auto const* xmlArray = dynamic_cast<gsoap_resqml2_0_1::resqml20__AbstractIntegerArray const*>(patch->Values);
		if (xmlArray != nullptr) {
			return readArrayNdOfUInt16Values(xmlArray, values);
		}
		else {
			throw logic_error("Reading integer values from a non integer array is not supported.");
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::eml23__AbstractValueArray const* xmlValues = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->ValuesForPatch[patchIndex];
		auto const* xmlArray = dynamic_cast<gsoap_eml2_3::eml23__AbstractIntegerArray const*>(xmlValues);
		if (xmlArray != nullptr) {
			return readArrayNdOfUInt16Values(xmlArray, values);
		}
		else {
			throw logic_error("Reading integer values from a non integer array is not supported.");
		}
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}
}

int8_t AbstractValuesProperty::getInt8ValuesOfPatch(uint64_t patchIndex, int8_t* values) const
{
	if (isPartial()) {
		throw logic_error("You cannot read values from a partial property.");
	}
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues const* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty const*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];
		auto const* xmlArray = dynamic_cast<gsoap_resqml2_0_1::resqml20__AbstractIntegerArray const*>(patch->Values);
		if (xmlArray != nullptr) {
			return readArrayNdOfInt8Values(xmlArray, values);
		}
		else {
			throw logic_error("Reading integer values from a non integer array is not supported.");
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::eml23__AbstractValueArray const* xmlValues = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->ValuesForPatch[patchIndex];
		auto const* xmlArray = dynamic_cast<gsoap_eml2_3::eml23__AbstractIntegerArray const*>(xmlValues);
		if (xmlArray != nullptr) {
			return readArrayNdOfInt8Values(xmlArray, values);
		}
		else {
			throw logic_error("Reading integer values from a non integer array is not supported.");
		}
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}
}

uint8_t AbstractValuesProperty::getUInt8ValuesOfPatch(uint64_t patchIndex, uint8_t* values) const
{
	cannotBePartial();
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues const* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty const*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];
		auto const* xmlArray = dynamic_cast<gsoap_resqml2_0_1::resqml20__AbstractIntegerArray const*>(patch->Values);
		if (xmlArray != nullptr) {
			return readArrayNdOfUInt8Values(xmlArray, values);
		}
		else {
			throw logic_error("Reading integer values from a non integer array is not supported.");
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::eml23__AbstractValueArray const* xmlValues = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->ValuesForPatch[patchIndex];
		auto const* xmlArray = dynamic_cast<gsoap_eml2_3::eml23__AbstractIntegerArray const*>(xmlValues);
		if (xmlArray != nullptr) {
			return readArrayNdOfUInt8Values(xmlArray, values);
		}
		else {
			throw logic_error("Reading integer values from a non integer array is not supported.");
		}
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}
}

void AbstractValuesProperty::setValuesOfHdf5ArrayOfValues(
	COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
	void const* values,
	uint64_t const * numValues,
	uint64_t const * offsetValues,
	unsigned int numArrayDimensions,
	EML2_NS::AbstractHdfProxy* proxy,
	uint64_t patchIndex)
{
	if (patchIndex >= getPatchCount() && patchIndex != (numeric_limits<uint64_t>::max)()) {
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
		"values_patch" + std::to_string(patchIndex == (numeric_limits<uint64_t>::max)() ? getPatchCount() - 1 : patchIndex),
		datatype,
		values,
		numValues,
		offsetValues,
		numArrayDimensions);
}

void AbstractValuesProperty::getInt64ValuesOfPatch(
	uint64_t patchIndex,
	int64_t* values,
	uint64_t const * numValuesInEachDimension,
	uint64_t const * offsetInEachDimension,
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

void AbstractValuesProperty::getInt64ValuesOf3dPatch(
	uint64_t patchIndex,
	int64_t* values,
	uint64_t valueCountInFastestDim,
	uint64_t valueCountInMiddleDim,
	uint64_t valueCountInSlowestDim,
	uint64_t offsetInFastestDim,
	uint64_t offsetInMiddleDim,
	uint64_t offsetInSlowestDim) const
{
	const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	const uint64_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };

	getInt64ValuesOfPatch(
		patchIndex,
		values,
		valueCountPerDimension,
		offsetPerDimension,
		3
	);
}

int32_t AbstractValuesProperty::getIntValuesOfPatch(
	uint64_t patchIndex,
	int32_t* values,
	const uint64_t* numValuesInEachDimension,
	const uint64_t* offsetInEachDimension,
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

	if (nullValue < (std::numeric_limits<int32_t>::lowest)() || nullValue >(std::numeric_limits<int32_t>::max)()) {
		throw range_error("The null value is not in the int32_t range");
	}

	return static_cast<int32_t>(nullValue);
}

void AbstractValuesProperty::getIntValuesOf3dPatch(
	uint64_t patchIndex,
	int32_t* values,
	unsigned int valueCountInFastestDim,
	unsigned int valueCountInMiddleDim,
	unsigned int valueCountInSlowestDim,
	unsigned int offsetInFastestDim,
	unsigned int offsetInMiddleDim,
	unsigned int offsetInSlowestDim) const
{
	uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	uint64_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };

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

void AbstractValuesProperty::pushBackFloatingPointConstantArrayOfValues(double value, uint64_t valueCount)
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractValuesProperty* prop = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1);

		gsoap_resqml2_0_1::resqml20__PatchOfValues* patch = gsoap_resqml2_0_1::soap_new_resqml20__PatchOfValues(gsoapProxy2_0_1->soap);
		patch->RepresentationPatchIndex = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
		*(patch->RepresentationPatchIndex) = prop->PatchOfValues.size();

		// XML
		gsoap_resqml2_0_1::resqml20__DoubleConstantArray* xmlValues = gsoap_resqml2_0_1::soap_new_resqml20__DoubleConstantArray(gsoapProxy2_0_1->soap);
		xmlValues->Count = valueCount;
		xmlValues->Value = value;

		patch->Values = xmlValues;

		prop->PatchOfValues.push_back(patch);
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__AbstractValuesProperty* prop = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3);

		// XML
		gsoap_eml2_3::eml23__FloatingPointConstantArray* xmlValues = gsoap_eml2_3::soap_new_eml23__FloatingPointConstantArray(gsoapProxy2_3->soap);
		xmlValues->Count = valueCount;
		xmlValues->Value = value;

		prop->ValuesForPatch.push_back(xmlValues);
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}
}

void AbstractValuesProperty::pushBackDoubleHdf5Array1dOfValues(const double * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy * proxy)
{
	pushBackDoubleHdf5ArrayOfValues(values, &valueCount, 1, proxy);
}

void AbstractValuesProperty::pushBackDoubleHdf5Array2dOfValues(const double * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy)
{
	const uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy);
}

void AbstractValuesProperty::pushBackDoubleHdf5Array3dOfValues(const double * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy)
{
	const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy);
}

void AbstractValuesProperty::pushBackDoubleHdf5ArrayOfValues(double const * values, uint64_t const * numValues, unsigned int numArrayDimensions, EML2_NS::AbstractHdfProxy * proxy)
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
		COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE,
		values,
		numValues, numArrayDimensions);

	pushBackRefToExistingFloatingPointDataset(proxy, getHdfGroup() + "/" + datasetName);
}

void AbstractValuesProperty::pushBackFloatHdf5Array1dOfValues(const float * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy * proxy)
{
	pushBackFloatHdf5ArrayOfValues(values, &valueCount, 1, proxy);
}

void AbstractValuesProperty::pushBackFloatHdf5Array2dOfValues(const float * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy)
{
	const uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy);
}

void AbstractValuesProperty::pushBackFloatHdf5Array3dOfValues(const float * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy)
{
	const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy);
}

void AbstractValuesProperty::pushBackFloatHdf5ArrayOfValues(float const * values, uint64_t const * numValues, unsigned int numArrayDimensions, EML2_NS::AbstractHdfProxy * proxy)
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
		COMMON_NS::AbstractObject::numericalDatatypeEnum::FLOAT,
		values,
		numValues,
		numArrayDimensions);

	pushBackRefToExistingFloatingPointDataset(proxy, getHdfGroup() + "/" + datasetName);
}

void AbstractValuesProperty::pushBackHdf5ArrayOfValues(
	COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
	uint64_t const * numValues,
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
	const std::string datasetName = "values_patch" + std::to_string(getPatchCount());

	// HDF
	proxy->createArrayNd(getHdfGroup(),
		datasetName,
		datatype,
		numValues, numArrayDimensions);

	if (datatype == COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE || datatype == COMMON_NS::AbstractObject::numericalDatatypeEnum::FLOAT) {
		pushBackRefToExistingFloatingPointDataset(proxy, getHdfGroup() + "/" + datasetName);
	}
	else if (datatype == COMMON_NS::AbstractObject::numericalDatatypeEnum::UNKNOWN) {
		throw std::invalid_argument("The datatype cannot be unknown");
	}
	else {
		pushBackRefToExistingIntegerDataset(proxy, getHdfGroup() + "/" + datasetName, nullValue);
	}
}

void AbstractValuesProperty::pushBackHdf5Array1dOfValues(
	COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
	uint64_t valueCount,
	int64_t nullValue,
	EML2_NS::AbstractHdfProxy* proxy)
{
	pushBackHdf5ArrayOfValues(datatype, &valueCount, 1, nullValue, proxy);
}

void AbstractValuesProperty::pushBackHdf5Array2dOfValues(
	COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
	uint64_t valueCountInFastestDim,
	uint64_t valueCountInSlowestDim,
	int64_t nullValue,
	EML2_NS::AbstractHdfProxy* proxy)
{
	const uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackHdf5ArrayOfValues(datatype, valueCountPerDimension, 2, nullValue, proxy);
}

void AbstractValuesProperty::pushBackHdf5Array3dOfValues(
	COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
	uint64_t valueCountInFastestDim,
	uint64_t valueCountInMiddleDim,
	uint64_t valueCountInSlowestDim,
	int64_t nullValue,
	EML2_NS::AbstractHdfProxy* proxy)
{
	const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackHdf5ArrayOfValues(datatype, valueCountPerDimension, 3, nullValue, proxy);
}

void AbstractValuesProperty::getDoubleValuesOfPatch(uint64_t patchIndex, double * values) const
{
	cannotBePartial();
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues const* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty const*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];
		auto const* xmlArrayOfDouble = dynamic_cast<gsoap_resqml2_0_1::resqml20__AbstractDoubleArray const*>(patch->Values);
		if (xmlArrayOfDouble != nullptr) {
			readArrayNdOfDoubleValues(xmlArrayOfDouble, values);
			return;
		}
		else {
			throw logic_error("Reading double values from a non double array is not supported.");
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::eml23__AbstractValueArray const* xmlValues = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->ValuesForPatch[patchIndex];
		auto const* xmlArrayOfFloatingPoints = dynamic_cast<gsoap_eml2_3::eml23__AbstractFloatingPointArray const*>(xmlValues);
		if (xmlArrayOfFloatingPoints != nullptr) {
			readArrayNdOfDoubleValues(xmlArrayOfFloatingPoints, values);
			return;
		}
		else {
			throw logic_error("Reading double values from a non floating point array is not supported.");
		}
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}
}

void AbstractValuesProperty::getFloatValuesOfPatch(uint64_t patchIndex, float * values) const
{
	cannotBePartial();
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PatchOfValues const* patch = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty const*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex];
		auto const* xmlArrayOfDouble = dynamic_cast<gsoap_resqml2_0_1::resqml20__AbstractDoubleArray const*>(patch->Values);
		if (xmlArrayOfDouble != nullptr) {
			readArrayNdOfFloatValues(xmlArrayOfDouble, values);
			return;
		}
		else {
			throw logic_error("Reading float values from a non double array is not supported.");
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::eml23__AbstractValueArray const* xmlValues = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->ValuesForPatch[patchIndex];
		auto const* xmlArrayOfFloatingPoints = dynamic_cast<gsoap_eml2_3::eml23__AbstractFloatingPointArray const*>(xmlValues);
		if (xmlArrayOfFloatingPoints != nullptr) {
			readArrayNdOfFloatValues(xmlArrayOfFloatingPoints, values);
			return;
		}
		else {
			throw logic_error("Reading float values from a non floating point array is not supported.");
		}
	}
	else {
		throw logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
	}
}

void AbstractValuesProperty::getFloatValuesOfPatch(
	uint64_t patchIndex,
	float* values,
	uint64_t const * numValuesInEachDimension,
	uint64_t const * offsetInEachDimension,
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
	uint64_t patchIndex,
	float* values,
	uint64_t valueCountInFastestDim,
	uint64_t valueCountInMiddleDim,
	uint64_t valueCountInSlowestDim,
	uint64_t offsetInFastestDim,
	uint64_t offsetInMiddleDim,
	uint64_t offsetInSlowestDim) const
{
	uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	uint64_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };

	getFloatValuesOfPatch(
		patchIndex,
		values,
		valueCountPerDimension,
		offsetPerDimension,
		3
	);
}
