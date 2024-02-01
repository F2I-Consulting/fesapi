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
#include "ChannelSet.h"

#include <sstream>

#include "Log.h"
#include "Channel.h"

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_3;

ChannelSet::ChannelSet(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title,
	bool isActive)
{
	gsoapProxy2_3 = soap_new_witsml21__ChannelSet(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	static_cast<witsml21__ChannelSet*>(gsoapProxy2_3)->ActiveStatus = isActive ? eml23__ActiveStatusKind::active : eml23__ActiveStatusKind::inactive;

	repo->addDataObject(this);
}

void ChannelSet::pushBackChannelIndex(gsoap_eml2_3::eml23__DataIndexKind indexKind, gsoap_eml2_3::eml23__UnitOfMeasure uom, const std::string & mnemonic, bool isIncreasing)
{
	witsml21__ChannelIndex* const index = soap_new_witsml21__ChannelIndex(getGsoapContext());

	index->IndexKind = indexKind;
	index->Uom = gsoap_eml2_3::soap_eml23__UnitOfMeasure2s(getGsoapContext(), uom);
	index->Mnemonic = mnemonic;
	index->Direction = isIncreasing ? gsoap_eml2_3::eml23__IndexDirection::increasing : gsoap_eml2_3::eml23__IndexDirection::decreasing;

	static_cast<witsml21__ChannelSet*>(gsoapProxy2_3)->Index.push_back(index);
}

void ChannelSet::pushBackChannel(Channel * channel)
{
	if (channel == nullptr) {
		throw invalid_argument("You cannot push back a null channel.");
	}
	static_cast<witsml21__ChannelSet*>(gsoapProxy2_3)->Channel.push_back(static_cast<witsml21__Channel*>(channel->getEml23GsoapProxy()));

	getRepository()->addRelationship(this, channel);
}

std::vector<Log*> ChannelSet::getLogs() const
{
	return getRepository()->getSourceObjects<Log>(this);
}

std::vector<Channel*> ChannelSet::getChannels() const
{
	return getRepository()->getTargetObjects<Channel>(this);
}

void ChannelSet::setDataAsJsonArray(const std::string & jsonArray)
{
	static_cast<witsml21__ChannelSet*>(gsoapProxy2_3)->Data = soap_new_witsml21__ChannelData(getGsoapContext());
	static_cast<witsml21__ChannelSet*>(gsoapProxy2_3)->Data->Data = soap_new_std__string(getGsoapContext());
	static_cast<witsml21__ChannelSet*>(gsoapProxy2_3)->Data->Data->assign(jsonArray);
}

void ChannelSet::setDataAsFileUri(const std::string & fileUri)
{
	static_cast<witsml21__ChannelSet*>(gsoapProxy2_3)->Data = soap_new_witsml21__ChannelData(getGsoapContext());
	static_cast<witsml21__ChannelSet*>(gsoapProxy2_3)->Data->FileUri = soap_new_std__string(getGsoapContext());
	static_cast<witsml21__ChannelSet*>(gsoapProxy2_3)->Data->FileUri->assign(fileUri);
}

bool ChannelSet::hasDataAsJsonArray() const
{
	return static_cast<witsml21__ChannelSet*>(gsoapProxy2_3)->Data != nullptr && static_cast<witsml21__ChannelSet*>(gsoapProxy2_3)->Data->Data != nullptr;
}

bool ChannelSet::hasDataAsFileUri() const
{
	return static_cast<witsml21__ChannelSet*>(gsoapProxy2_3)->Data != nullptr && static_cast<witsml21__ChannelSet*>(gsoapProxy2_3)->Data->FileUri != nullptr;
}

const std::string& ChannelSet::getDataAsJsonArray() const
{
	if (!hasDataAsJsonArray()) {
		throw logic_error("There is no Data as Json Array");
	}

	return *(static_cast<witsml21__ChannelSet*>(gsoapProxy2_3)->Data->Data);
}

const std::string& ChannelSet::getDataAsFileUri() const
{
	if (!hasDataAsFileUri()) {
		throw logic_error("There is no Data as file URI");
	}

	return *(static_cast<witsml21__ChannelSet*>(gsoapProxy2_3)->Data->FileUri);
}

#define SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(attributeDatatype, attributeName, constructor)\
void ChannelSet::set##attributeName(const attributeDatatype & attributeName) {\
	if (static_cast<witsml21__ChannelSet*>(gsoapProxy2_3)->attributeName == nullptr) { static_cast<witsml21__ChannelSet*>(gsoapProxy2_3)->attributeName = constructor(gsoapProxy2_3->soap, 1); }\
	*static_cast<witsml21__ChannelSet*>(gsoapProxy2_3)->attributeName = attributeName;\
}

SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, RunNumber, gsoap_eml2_3::soap_new_std__string)
SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, PassNumber, gsoap_eml2_3::soap_new_std__string)
SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, LoggingToolClassLongName, gsoap_eml2_3::soap_new_std__string)

void ChannelSet::loadTargetRelationships()
{
	WellboreObject::loadTargetRelationships();

	const std::vector<witsml21__Channel *>& channels = static_cast<witsml21__ChannelSet*>(gsoapProxy2_3)->Channel;

	for (size_t i = 0; i < channels.size(); ++i) {
		Channel* channel = getRepository()->getDataObjectByUuid<Channel>(channels[i]->uuid);
		if (channel == nullptr) {
			channel = new Channel(channels[i]);
			getRepository()->addOrReplaceDataObject(channel);
			channel->loadTargetRelationships();
		}
		getRepository()->addRelationship(this, channel);
	}
}
