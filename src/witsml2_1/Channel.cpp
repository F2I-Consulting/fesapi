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
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_3;

const char* Channel::XML_TAG = "Channel";

Channel::Channel(EML2_NS::PropertyKind * propertyKind,
	const std::string & guid, const std::string & title,
	const std::string & mnemonic, gsoap_eml2_3::eml23__UnitOfMeasure uom, gsoap_eml2_3::witsml21__ChannelDataKind dataType,
	bool isActive)
{
	if (propertyKind == nullptr) {
		throw invalid_argument("A channel must be associated to a property kind.");
	}

	gsoapProxy2_3 = soap_new_witsml21__Channel(propertyKind->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	auto* channel = static_cast<witsml21__Channel*>(gsoapProxy2_3);

	channel->Mnemonic = mnemonic;
	channel->Uom = gsoap_eml2_3::soap_eml23__UnitOfMeasure2s(propertyKind->getGsoapContext(), uom);
	channel->DataKind = dataType;

	channel->LoggingCompany = soap_new_eml23__DataObjectReference(gsoapProxy2_3->soap);
	channel->LoggingCompany->Uuid.assign("00000000-0000-0000-0000-000000000002");
	channel->LoggingCompany->QualifiedType.assign("eml23.BusinessAssociate");
	channel->LoggingCompany->Title.assign("Fake Business Associate");
	
	channel->ActiveStatus = isActive ? eml23__ActiveStatusKind::active : eml23__ActiveStatusKind::inactive;

	propertyKind->getRepository()->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
	setPropertyKind(propertyKind);
}

void Channel::pushBackChannelIndex(gsoap_eml2_3::eml23__DataIndexKind indexKind, gsoap_eml2_3::eml23__UnitOfMeasure uom, const std::string & mnemonic, bool isIncreasing)
{
	witsml21__ChannelIndex* const index = soap_new_witsml21__ChannelIndex(getGsoapContext());

	index->IndexKind = indexKind;
	index->Uom = gsoap_eml2_3::soap_eml23__UnitOfMeasure2s(getGsoapContext(), uom);
	index->Mnemonic = mnemonic;
	index->Direction = isIncreasing ? gsoap_eml2_3::eml23__IndexDirection::increasing : gsoap_eml2_3::eml23__IndexDirection::decreasing;

	static_cast<witsml21__Channel*>(gsoapProxy2_3)->Index.push_back(index);
}

COMMON_NS::DataObjectReference Channel::getPropertyKindDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<witsml21__Channel*>(gsoapProxy2_3)->ChannelPropertyKind);
}

std::vector<ChannelSet*> Channel::getChannelSets() const
{
	return getRepository()->getSourceObjects<ChannelSet>(this);
}

EML2_NS::PropertyKind* Channel::getPropertyKind() const
{
	return getRepository()->getDataObjectByUuid<EML2_NS::PropertyKind>(getPropertyKindDor().getUuid());
}

void Channel::setPropertyKind(EML2_NS::PropertyKind* propKind)
{
	if (propKind == nullptr) {
		throw std::invalid_argument("Cannot set a null witsml propKind to a witsml log/channelset/channel");
	}

	static_cast<witsml21__Channel*>(gsoapProxy2_3)->ChannelPropertyKind = propKind->newEml23Reference();

	getRepository()->addRelationship(this, propKind);
}

GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IMPL(std::string, Channel, Mnemonic)
GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IMPL(std::string, Channel, Uom)
GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IMPL(gsoap_eml2_3::witsml21__ChannelDataKind, Channel, DataKind)

#define SETTER_GENERIC_ATTRIBUTE_IMPL(attributeDatatype, attributeName)\
void Channel::set##attributeName(const attributeDatatype & attributeName) {\
	static_cast<witsml21__Channel*>(gsoapProxy2_3)->attributeName = attributeName;\
}

#define SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(attributeDatatype, attributeName, constructor)\
void Channel::set##attributeName(const attributeDatatype & attributeName) {\
	if (static_cast<witsml21__Channel*>(gsoapProxy2_3)->attributeName == nullptr) { static_cast<witsml21__Channel*>(gsoapProxy2_3)->attributeName = constructor(gsoapProxy2_3->soap, 1); }\
	*static_cast<witsml21__Channel*>(gsoapProxy2_3)->attributeName = attributeName;\
}

SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, RunNumber, gsoap_eml2_3::soap_new_std__string)
SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, PassNumber, gsoap_eml2_3::soap_new_std__string)

void Channel::loadTargetRelationships()
{
	WellboreObject::loadTargetRelationships();

	convertDorIntoRel<EML2_NS::PropertyKind>(getPropertyKindDor());
}
