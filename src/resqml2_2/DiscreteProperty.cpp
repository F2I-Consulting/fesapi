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

#include <algorithm>

#include <hdf5.h>

#include "../common/EnumStringMapper.h"

#include "../eml2/AbstractHdfProxy.h"
#include "../eml2/ColumnBasedTable.h"
#include "../eml2/PropertyKind.h"

#include "../resqml2/AbstractRepresentation.h"

#include "../tools/Statistics.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

DiscreteProperty::DiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	gsoap_eml2_3::eml23__IndexableElement attachmentKind, EML2_NS::PropertyKind * propKind,
	std::vector<int> dimensions)
{
	if (rep == nullptr) {
		throw invalid_argument("The representation of this property values cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__DiscreteProperty(rep->getGsoapContext());	
	_resqml22__DiscreteProperty* prop = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3);
	prop->IndexableElement = attachmentKind;
	if (dimensions.empty()) {
		prop->ValueCountPerIndexableElement = { 1 };
	}
	else {
		for (auto dim : dimensions) {
			prop->ValueCountPerIndexableElement.push_back(dim);
		}
	}

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	rep->getRepository()->addDataObject(this);
	setRepresentation(rep);

	setPropertyKind(propKind);
}

DiscreteProperty::DiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	gsoap_eml2_3::eml23__IndexableElement attachmentKind, EML2_NS ::ColumnBasedTable* strLookup,
	EML2_NS::PropertyKind * propKind,
	std::vector<int> dimensions)
{
	if (rep == nullptr) {
		throw invalid_argument("The representation of this property values cannot be null.");
	}
	if (strLookup == nullptr) {
		throw invalid_argument("The string lookup table cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__DiscreteProperty(rep->getGsoapContext());
	_resqml22__DiscreteProperty* prop = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3);
	prop->IndexableElement = attachmentKind;
	if (dimensions.empty()) {
		prop->ValueCountPerIndexableElement = { 1 };
	}
	else {
		for (auto dim : dimensions) {
			prop->ValueCountPerIndexableElement.push_back(dim);
		}
	}

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	rep->getRepository()->addDataObject(this);
	setRepresentation(rep);

	setPropertyKind(propKind);

	prop->CategoryLookup = strLookup->newEml23Reference();
	getRepository()->addRelationship(this, strLookup);
}

int64_t DiscreteProperty::getNullValue(uint64_t patchIndex) const
{
	_resqml22__DiscreteProperty* prop = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3);

	auto abstractIntArray = prop->ValuesForPatch[patchIndex == (numeric_limits<uint64_t>::max)() ? prop->ValuesForPatch.size() - 1 : patchIndex];
	if (abstractIntArray->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		return (std::numeric_limits<int64_t>::max)();
	}

	return static_cast<eml23__IntegerExternalArray*>(abstractIntArray)->NullValue;
}

bool DiscreteProperty::hasMinimumValue(uint64_t index) const
{
	_resqml22__DiscreteProperty* prop = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3);

	for (auto* patch : prop->ValuesForPatch) {
		if (patch->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			gsoap_eml2_3::eml23__IntegerExternalArray* integerPatch = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(patch);
			if (integerPatch->Statistics.size() <= index ||
				integerPatch->Statistics[index]->MinimumValue == nullptr) {
				return false;
			}
		}
	}

	return true;
}

int64_t DiscreteProperty::getMinimumValue(uint64_t index) const
{
	if (!hasMinimumValue(index)) {
		throw std::logic_error("This property has not minimum value at index " + std::to_string(index));
	}

	int64_t result = (std::numeric_limits<int64_t>::max)();

	_resqml22__DiscreteProperty const* prop = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3);

	for (auto const* patch : prop->ValuesForPatch) {
		if (patch->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			gsoap_eml2_3::eml23__IntegerExternalArray const* integerPatch = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(patch);
			result = (std::min)(result, *integerPatch->Statistics[index]->MinimumValue);
		}
	}

	return result;
}

bool DiscreteProperty::hasMaximumValue(uint64_t index) const
{
	_resqml22__DiscreteProperty* prop = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3);

	for (auto* patch : prop->ValuesForPatch) {
		if (patch->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			gsoap_eml2_3::eml23__IntegerExternalArray* integerPatch = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(patch);
			if (integerPatch->Statistics.size() <= index ||
				integerPatch->Statistics[index]->MaximumValue == nullptr) {
				return false;
			}
		}
	}

	return true;
}

int64_t DiscreteProperty::getMaximumValue(uint64_t index) const
{
	if (!hasMinimumValue(index)) {
		throw std::logic_error("This property has not minimum value at index " + std::to_string(index));
	}

	int64_t result = (std::numeric_limits<int64_t>::lowest)();

	_resqml22__DiscreteProperty const* prop = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3);

	for (auto const* patch : prop->ValuesForPatch) {
		if (patch->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			gsoap_eml2_3::eml23__IntegerExternalArray const* integerPatch = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(patch);
			result = (std::max)(result, *integerPatch->Statistics[index]->MaximumValue);
		}
	}

	return result;
}

void DiscreteProperty::setMinimumValue(int64_t value, uint64_t index) const
{
	_resqml22__DiscreteProperty* prop = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3);

	for (auto* patch : prop->ValuesForPatch) {
		if (patch->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			gsoap_eml2_3::eml23__IntegerExternalArray* integerPatch = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(patch);
			while (integerPatch->Statistics.size() <= index) {
				integerPatch->Statistics.push_back(soap_new_eml23__IntegerArrayStatistics(gsoapProxy2_3->soap));
			}
			if (integerPatch->Statistics[index]->MinimumValue == nullptr) {
				integerPatch->Statistics[index]->MinimumValue = soap_new_LONG64(gsoapProxy2_3->soap);
			}
			*integerPatch->Statistics[index]->MinimumValue = value;
		}
	}
}

void DiscreteProperty::setMaximumValue(int64_t value, uint64_t index) const
{
	_resqml22__DiscreteProperty* prop = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3);

	for (auto* patch : prop->ValuesForPatch) {
		if (patch->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			gsoap_eml2_3::eml23__IntegerExternalArray* integerPatch = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(patch);
			while (integerPatch->Statistics.size() <= index) {
				integerPatch->Statistics.push_back(soap_new_eml23__IntegerArrayStatistics(gsoapProxy2_3->soap));
			}
			if (integerPatch->Statistics[index]->MaximumValue == nullptr) {
				integerPatch->Statistics[index]->MaximumValue = soap_new_LONG64(gsoapProxy2_3->soap);
			}
			*integerPatch->Statistics[index]->MaximumValue = value;
		}
	}
}
