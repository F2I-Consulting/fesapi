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
#include "Log.h"

#include <sstream>
#include <stdexcept>
#include <limits>

#include "Wellbore.h"
#include "ChannelSet.h"

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_3;

const char* Log::XML_TAG = "Log";

Log::Log(WITSML2_NS::Wellbore* witsmlWellbore,
	const std::string & guid,
	const std::string & title,
	bool isActive)
{
	if (witsmlWellbore == nullptr) throw invalid_argument("A wellbore must be associated to a log.");

	gsoapProxy2_3 = soap_new_witsml21__Log(witsmlWellbore->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	static_cast<witsml21__Log*>(gsoapProxy2_3)->ActiveStatus = isActive ? eml23__ActiveStatusKind::active : eml23__ActiveStatusKind::inactive;

	witsmlWellbore->getRepository()->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
	setWellbore(witsmlWellbore);
}

void Log::pushBackChannelSet(ChannelSet * channelSet)
{
	if (channelSet == nullptr) {
		throw invalid_argument("You cannot push back a null channel set.");
	}
	static_cast<witsml21__Log*>(gsoapProxy2_3)->ChannelSet.push_back(static_cast<witsml21__ChannelSet*>(channelSet->getEml23GsoapProxy()));

	getRepository()->addRelationship(this, channelSet);
}

std::vector<ChannelSet*> Log::getChannelSets() const
{
	return getRepository()->getTargetObjects<ChannelSet>(this);
}

#define SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(attributeDatatype, attributeName, constructor)\
void Log::set##attributeName(const attributeDatatype & attributeName) {\
	if (static_cast<witsml21__Log*>(gsoapProxy2_3)->attributeName == nullptr) { static_cast<witsml21__Log*>(gsoapProxy2_3)->attributeName = constructor(gsoapProxy2_3->soap, 1); }\
	*static_cast<witsml21__Log*>(gsoapProxy2_3)->attributeName = attributeName;\
}

SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, RunNumber, gsoap_eml2_3::soap_new_std__string)
SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, PassNumber, gsoap_eml2_3::soap_new_std__string)
SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, LoggingToolClassLongName, gsoap_eml2_3::soap_new_std__string)

void Log::loadTargetRelationships()
{
	WellboreObject::loadTargetRelationships();

	const std::vector<witsml21__ChannelSet *>& channelSets = static_cast<witsml21__Log*>(gsoapProxy2_3)->ChannelSet;

	for (witsml21__ChannelSet* channelSet : channelSets) {
		COMMON_NS::AbstractObject* channelSetWrapper = getRepository()->getDataObjectByUuid<ChannelSet>(channelSet->uuid);
		if (channelSetWrapper == nullptr) {
			channelSetWrapper = getRepository()->addOrReplaceDataObject(std::unique_ptr<COMMON_NS::AbstractObject>(new ChannelSet(channelSet)));
			channelSetWrapper->loadTargetRelationships();
		}
		getRepository()->addRelationship(this, channelSetWrapper);
	}
}
