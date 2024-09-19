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

#include <limits>
#include <sstream>
#include <stdexcept>

#include "../common/EnumStringMapper.h"
#include "../eml2/AbstractHdfProxy.h"
#include "../eml2/PropertyKind.h"

#include "../tools/Statistics.h"
#include "../resqml2/AbstractRepresentation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* DiscreteProperty::XML_NS = "resqml22";

DiscreteProperty::DiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_3::eml23__IndexableElement attachmentKind, EML2_NS::PropertyKind * localPropKind)
{
	if (dimension == 0) {
		throw invalid_argument("The dimension cannot be zero.");
	}

	gsoapProxy2_3 = soap_new_resqml22__DiscreteProperty(rep->getGsoapContext());	
	_resqml22__DiscreteProperty* prop = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3);
	prop->IndexableElement = attachmentKind;
	prop->ValueCountPerIndexableElement.push_back(dimension);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	rep->getRepository()->addDataObject(this);
	setRepresentation(rep);

	setPropertyKind(localPropKind);
}

std::string DiscreteProperty::pushBackRefToExistingIntegerDataset(EML2_NS::AbstractHdfProxy* proxy, const std::string & datasetName, int64_t nullValue, int64_t minimumValue, int64_t maximumValue)
{
	gsoap_eml2_3::resqml22__AbstractValuesProperty* prop = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3);

	// XML
	gsoap_eml2_3::eml23__IntegerExternalArray* xmlValues = gsoap_eml2_3::soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	xmlValues->NullValue = nullValue;
	xmlValues->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	auto* stats = gsoap_eml2_3::soap_new_eml23__IntegerArrayStatistics(gsoapProxy2_3->soap);
	stats->MinimumValue = gsoap_eml2_3::soap_new_LONG64(gsoapProxy2_3->soap);
	*stats->MinimumValue = minimumValue;
	stats->MaximumValue = gsoap_eml2_3::soap_new_LONG64(gsoapProxy2_3->soap);
	*stats->MaximumValue = maximumValue;
	xmlValues->Statistics.push_back(stats);

	auto* daPart = createExternalDataArrayPart(datasetName, proxy->getElementCount(datasetName), proxy);
	xmlValues->Values->ExternalDataArrayPart.push_back(daPart);

	prop->ValuesForPatch.push_back(xmlValues);

	return daPart->PathInExternalFile;
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
	const auto valuesforPatch = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3)->ValuesForPatch;
	if (valuesforPatch.size() != 1) return false;

	auto const* intArray = dynamic_cast<eml23__AbstractIntegerArray*>(valuesforPatch[0]);
	return intArray != nullptr && intArray->Statistics.size() > index && intArray->Statistics[index]->MinimumValue != nullptr;
}

int64_t DiscreteProperty::getMinimumValue(uint64_t index) const
{
	if (!hasMinimumValue(index)) {
		throw std::logic_error("This property has not minimum value at index " + std::to_string(index));
	}

	return *dynamic_cast<eml23__AbstractIntegerArray*>(static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3)->ValuesForPatch[0])->Statistics[index]->MinimumValue;
}

bool DiscreteProperty::hasMaximumValue(uint64_t index) const
{
	const auto valuesforPatch = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3)->ValuesForPatch;
	if (valuesforPatch.size() != 1) return false;

	auto const* intArray = dynamic_cast<eml23__AbstractIntegerArray*>(valuesforPatch[0]);
	return intArray != nullptr && intArray->Statistics.size() > index && intArray->Statistics[index]->MaximumValue != nullptr;
}

int64_t DiscreteProperty::getMaximumValue(uint64_t index) const
{
	if (!hasMaximumValue(index)) {
		throw std::logic_error("This property has not maximum value at index " + std::to_string(index));
	}

	return *dynamic_cast<eml23__AbstractIntegerArray*>(static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3)->ValuesForPatch[0])->Statistics[index]->MaximumValue;
}

void DiscreteProperty::setMinimumValue(int64_t value, uint64_t index) const
{
	const auto valuesforPatch = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3)->ValuesForPatch;
	if (valuesforPatch.size() != 1) throw std::logic_error("Setting minimum value on a multipatched or zero patched property is not supported yet.");

	auto const* intArray = dynamic_cast<eml23__AbstractIntegerArray*>(valuesforPatch[0]);
	if (intArray == nullptr) throw std::logic_error("Setting minimum value on a non integer array for a discrete property is not supported.");

	auto* stats = intArray->Statistics.size() <= index
		? gsoap_eml2_3::soap_new_eml23__IntegerArrayStatistics(gsoapProxy2_3->soap)
		: intArray->Statistics[index];

	auto* minValue = stats->MinimumValue == nullptr
		? soap_new_LONG64(gsoapProxy2_3->soap)
		: stats->MinimumValue;

	*minValue = value;
}

void DiscreteProperty::setMaximumValue(int64_t value, uint64_t index) const
{
	const auto valuesforPatch = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3)->ValuesForPatch;
	if (valuesforPatch.size() != 1) throw std::logic_error("Setting maximum value on a multipatched or zero patched property is not supported yet.");

	auto const* intArray = dynamic_cast<eml23__AbstractIntegerArray*>(valuesforPatch[0]);
	if (intArray == nullptr) throw std::logic_error("Setting maximum value on a non integer array for a discrete property is not supported.");

	auto* stats = intArray->Statistics.size() <= index
		? gsoap_eml2_3::soap_new_eml23__IntegerArrayStatistics(gsoapProxy2_3->soap)
		: intArray->Statistics[index];

	auto* maxValue = stats->MaximumValue == nullptr
		? soap_new_LONG64(gsoapProxy2_3->soap)
		: stats->MaximumValue;

	*maxValue = value;
}

size_t DiscreteProperty::getMinimumValueSize() const
{
	auto valuesforPatch = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3)->ValuesForPatch;
	if (valuesforPatch.size() != 1) return 0;

	auto const* intArray = dynamic_cast<eml23__AbstractIntegerArray*>(valuesforPatch[0]);
	if (intArray == nullptr) return 0;
	
	size_t result = 0;
	for (result = 0; result < intArray->Statistics.size(); ++result) {
		if (intArray->Statistics[result]->MinimumValue == nullptr) return result;
	}
	return result;
}

size_t DiscreteProperty::getMaximumValueSize() const
{
	auto valuesforPatch = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3)->ValuesForPatch;
	if (valuesforPatch.size() != 1) return 0;

	auto const* intArray = dynamic_cast<eml23__AbstractIntegerArray*>(valuesforPatch[0]);
	if (intArray == nullptr) return 0;

	size_t result = 0;
	for (result = 0; result < intArray->Statistics.size(); ++result) {
		if (intArray->Statistics[result]->MaximumValue == nullptr) return result;
	}
	return result;
}
