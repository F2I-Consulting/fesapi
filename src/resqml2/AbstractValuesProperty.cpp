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

#include <stdexcept>
#include <ostream>
#include <sstream>

#include <hdf5.h>

#include "../common/PropertyKind.h"

#include "AbstractRepresentation.h"
#include "AbstractLocal3dCrs.h"
#include "../common/AbstractHdfProxy.h"

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

	const hid_t dt = getHdfProxyFromDataset(dataset)->getHdfDatatypeInDataset(dataset->PathInHdfFile);
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

unsigned int AbstractValuesProperty::getValuesCountOfDimensionOfPatch(unsigned int dimIndex, unsigned int patchIndex) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);
	COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);

	std::vector<hsize_t> dims = hdfProxy->readArrayDimensions(dataset->PathInHdfFile);

	if (dimIndex < dims.size()) {
		return dims[dimIndex];
	}

	throw out_of_range("The dim index to get the count is out of range.");
}

unsigned int AbstractValuesProperty::getDimensionsCountOfPatch(unsigned int patchIndex) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);

	return getHdfProxyFromDataset(dataset)->getDimensionCount(dataset->PathInHdfFile);
}

void AbstractValuesProperty::pushBackFacet(const gsoap_resqml2_0_1::resqml20__Facet & facet, const std::string & facetValue)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PropertyKindFacet* newFacet = gsoap_resqml2_0_1::soap_new_resqml20__PropertyKindFacet(gsoapProxy2_0_1->soap);
		newFacet->Facet = facet;
		newFacet->Value = facetValue;
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->Facet.push_back(newFacet);
	}

	throw logic_error("Not implemented yet");
}

unsigned int AbstractValuesProperty::getFacetCount() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		const size_t result = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->Facet.size();

		if (result > (std::numeric_limits<unsigned int>::max)()) {
			throw std::range_error("There are too much facets");
		}

		return static_cast<unsigned int>(result);
	}

	throw logic_error("Not implemented yet");
}

gsoap_resqml2_0_1::resqml20__Facet AbstractValuesProperty::getFacet(unsigned int index) const
{
	if (index >= getFacetCount()) {
		throw out_of_range("The facet index is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1)->Facet[index]->Facet;
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
	
	throw logic_error("Not implemented yet");
}

unsigned int AbstractValuesProperty::getValuesCountOfPatch (unsigned int patchIndex) const
{
	LONG64 nullValue = (numeric_limits<LONG64>::min)();
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = getDatasetOfPatch(patchIndex, nullValue);

	return getHdfProxyFromDataset(dataset)->getElementCount(dataset->PathInHdfFile);
}

void AbstractValuesProperty::loadTargetRelationships()
{
	AbstractProperty::loadTargetRelationships();

	gsoap_resqml2_0_1::resqml20__AbstractValuesProperty* prop = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1);
	
	for (size_t patchIndex = 0; patchIndex < prop->PatchOfValues.size(); ++patchIndex) {
		auto* patchValues = prop->PatchOfValues[patchIndex]->Values;

		switch (patchValues->soap_type()) {
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array:
			convertDorIntoRel<COMMON_NS::AbstractHdfProxy>(COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__BooleanHdf5Array*>(patchValues)->Values->HdfProxy));
			break;
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array:
			convertDorIntoRel<COMMON_NS::AbstractHdfProxy>(COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(patchValues)->Values->HdfProxy));
			break;
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array:
			convertDorIntoRel<COMMON_NS::AbstractHdfProxy>(COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(patchValues)->Values->HdfProxy));
			break;
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__StringHdf5Array:
			convertDorIntoRel<COMMON_NS::AbstractHdfProxy>(COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__StringHdf5Array*>(patchValues)->Values->HdfProxy));
			break;
		default:
			throw logic_error("The type of the property values is not implemented yet.");
		}
	}
}
