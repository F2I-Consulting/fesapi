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

#include <hdf5.h>

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
	gsoap_eml2_3::resqml22__IndexableElement attachmentKind, EML2_NS::PropertyKind * localPropKind,
	std::vector<int> dimensions)
{
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

	setPropertyKind(localPropKind);
}

std::string DiscreteProperty::pushBackRefToExistingIntegerDataset(EML2_NS::AbstractHdfProxy* proxy, const std::string & datasetName, int64_t nullValue, int64_t minimumValue, int64_t maximumValue)
{
	const string result = AbstractValuesProperty::pushBackRefToExistingIntegerDataset(proxy, datasetName, nullValue);

	_resqml22__DiscreteProperty* prop = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3);

	if (prop->ValueCountPerIndexableElement.empty() || (prop->ValueCountPerIndexableElement.size() == 1 && prop->ValueCountPerIndexableElement[0] == 1))
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

int64_t DiscreteProperty::getNullValue(unsigned int patchIndex) const
{
	_resqml22__DiscreteProperty* prop = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3);

	auto abstractIntArray = prop->ValuesForPatch[patchIndex == (numeric_limits<unsigned int>::max)() ? prop->ValuesForPatch.size() - 1 : patchIndex];
	if (abstractIntArray->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		return (std::numeric_limits<int64_t>::max)();
	}

	return static_cast<eml23__IntegerExternalArray*>(abstractIntArray)->NullValue;
}

bool DiscreteProperty::hasMinimumValue(unsigned int index) const
{
	return static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3)->MinimumValue.size() > index;
}

int64_t DiscreteProperty::getMinimumValue(unsigned int index) const
{
	if (!hasMinimumValue(index)) {
		throw std::logic_error("This property has not minimum value at index " + std::to_string(index));
	}

	return static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3)->MinimumValue[index];
}

bool DiscreteProperty::hasMaximumValue(unsigned int index) const
{
	return static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3)->MaximumValue.size() > index;
}

int64_t DiscreteProperty::getMaximumValue(unsigned int index) const
{
	if (!hasMaximumValue(index)) {
		throw std::logic_error("This property has not maximum value at index " + std::to_string(index));
	}

	return static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3)->MaximumValue[index];
}

void DiscreteProperty::setMinimumValue(int64_t value, unsigned int index) const
{
	_resqml22__DiscreteProperty* prop = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3);

	while (prop->MinimumValue.size() <= index) {
		prop->MinimumValue.push_back((std::numeric_limits<int64_t>::max)());
	}

	prop->MinimumValue[index] = value;
}

void DiscreteProperty::setMaximumValue(int64_t value, unsigned int index) const
{
	_resqml22__DiscreteProperty* prop = static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3);

	while (prop->MaximumValue.size() <= index) {
		prop->MaximumValue.push_back((std::numeric_limits<int64_t>::min)());
	}

	prop->MaximumValue[index] = value;
}

size_t DiscreteProperty::getMinimumValueSize() const
{
	return static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3)->MinimumValue.size();
}

size_t DiscreteProperty::getMaximumValueSize() const
{
	return static_cast<_resqml22__DiscreteProperty*>(gsoapProxy2_3)->MaximumValue.size();
}
