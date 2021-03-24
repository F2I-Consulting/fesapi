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
#include "Channel.h"

#include <stdexcept>

#include "../eml2/PropertyKind.h"

#include "Well.h"
#include "ChannelSet.h"

using namespace std;
using namespace WITSML2_0_NS;
using namespace gsoap_eml2_1;

const char* Channel::XML_TAG = "Channel";

Channel::Channel(EML2_NS::PropertyKind * propertyKind,
	const std::string & guid, const std::string & title,
	const std::string & mnemonic, gsoap_eml2_1::eml21__UnitOfMeasure uom, gsoap_eml2_1::witsml20__EtpDataType dataType, gsoap_eml2_1::witsml20__ChannelStatus growingStatus,
	const std::string & timeDepth, const std::string & loggingCompanyName)
{
	if (propertyKind == nullptr) {
		throw invalid_argument("A channel must be associated to a property kind.");
	}

	gsoapProxy2_1 = soap_new_witsml20__Channel(propertyKind->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	static_cast<witsml20__Channel*>(gsoapProxy2_1)->Mnemonic = mnemonic;
	static_cast<witsml20__Channel*>(gsoapProxy2_1)->Uom = gsoap_eml2_1::soap_eml21__UnitOfMeasure2s(propertyKind->getGsoapContext(), uom);
	static_cast<witsml20__Channel*>(gsoapProxy2_1)->DataType = dataType;
	static_cast<witsml20__Channel*>(gsoapProxy2_1)->GrowingStatus = growingStatus;
	static_cast<witsml20__Channel*>(gsoapProxy2_1)->TimeDepth = timeDepth;
	static_cast<witsml20__Channel*>(gsoapProxy2_1)->LoggingCompanyName = loggingCompanyName;

	setPropertyKind(propertyKind);
}

void Channel::pushBackChannelIndex(gsoap_eml2_1::witsml20__ChannelIndexType indexType, gsoap_eml2_1::eml21__UnitOfMeasure uom, const std::string & mnemonic, bool isIncreasing, const std::string & datum)
{
	witsml20__ChannelIndex* const index = soap_new_witsml20__ChannelIndex(getGsoapContext());

	index->IndexType = indexType;
	index->Uom = gsoap_eml2_1::soap_eml21__UnitOfMeasure2s(getGsoapContext(), uom);
	index->Mnemonic = mnemonic;
	index->Direction = isIncreasing ? gsoap_eml2_1::witsml20__IndexDirection::increasing : gsoap_eml2_1::witsml20__IndexDirection::decreasing;
	if (!datum.empty()) {
		index->DatumReference = soap_new_std__string(getGsoapContext());
		index->DatumReference->assign(datum);
	}

	static_cast<witsml20__Channel*>(gsoapProxy2_1)->Index.push_back(index);
}

COMMON_NS::DataObjectReference Channel::getPropertyKindDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<witsml20__Channel*>(gsoapProxy2_1)->ChannelClass);
}

std::vector<ChannelSet*> Channel::getChannelSets() const
{
	return getRepository()->getSourceObjects<ChannelSet>(this);
}

EML2_NS::PropertyKind* Channel::getPropertyKind() const
{
	return getRepository()->getDataObjectByUuid<EML2_NS::PropertyKind>(getPropertyKindDor().getUuid());
}

GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IMPL(std::string, Channel, Mnemonic)
GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IMPL(std::string, Channel, Uom)
GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IMPL(gsoap_eml2_1::witsml20__EtpDataType, Channel, DataType)
GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IMPL(gsoap_eml2_1::witsml20__ChannelStatus, Channel, GrowingStatus)

#define SETTER_GENERIC_ATTRIBUTE_IMPL(attributeDatatype, attributeName)\
void Channel::set##attributeName(const attributeDatatype & attributeName) {\
	static_cast<witsml20__Channel*>(gsoapProxy2_1)->attributeName = attributeName;\
}

#define SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(attributeDatatype, attributeName, constructor)\
void Channel::set##attributeName(const attributeDatatype & attributeName) {\
	if (static_cast<witsml20__Channel*>(gsoapProxy2_1)->attributeName == nullptr) { static_cast<witsml20__Channel*>(gsoapProxy2_1)->attributeName = constructor(gsoapProxy2_1->soap, 1); }\
	*static_cast<witsml20__Channel*>(gsoapProxy2_1)->attributeName = attributeName;\
}

SETTER_GENERIC_ATTRIBUTE_IMPL(std::string, TimeDepth)
SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, RunNumber, gsoap_eml2_1::soap_new_std__string)
SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, PassNumber, gsoap_eml2_1::soap_new_std__string)
SETTER_GENERIC_ATTRIBUTE_IMPL(std::string, LoggingCompanyName)
SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, LoggingCompanyCode, gsoap_eml2_1::soap_new_std__string)
SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, ToolName, gsoap_eml2_1::soap_new_std__string)
SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, ToolClass, gsoap_eml2_1::soap_new_std__string)

void Channel::loadTargetRelationships()
{
	WellboreObject::loadTargetRelationships();

	convertDorIntoRel<EML2_NS::PropertyKind>(getPropertyKindDor());
}
