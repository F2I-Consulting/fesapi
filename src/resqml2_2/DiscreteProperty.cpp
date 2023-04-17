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
	throw logic_error("Not implemented yet");
}

int64_t DiscreteProperty::getMinimumValue(uint64_t index) const
{
	throw logic_error("Not implemented yet");
}

bool DiscreteProperty::hasMaximumValue(uint64_t index) const
{
	throw logic_error("Not implemented yet");
}

int64_t DiscreteProperty::getMaximumValue(uint64_t index) const
{
	throw logic_error("Not implemented yet");
}

void DiscreteProperty::setMinimumValue(int64_t value, uint64_t index) const
{
	throw logic_error("Not implemented yet");
}

void DiscreteProperty::setMaximumValue(int64_t value, uint64_t index) const
{
	throw logic_error("Not implemented yet");
}

size_t DiscreteProperty::getMinimumValueSize() const
{
	throw logic_error("Not implemented yet");
}

size_t DiscreteProperty::getMaximumValueSize() const
{
	throw logic_error("Not implemented yet");
}
