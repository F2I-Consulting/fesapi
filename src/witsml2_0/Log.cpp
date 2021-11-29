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
using namespace WITSML2_0_NS;
using namespace gsoap_eml2_1;

Log::Log(WITSML2_NS::Wellbore* witsmlWellbore,
	const std::string & guid,
	const std::string & title)
{
	if (witsmlWellbore == nullptr) throw invalid_argument("A wellbore must be associated to a log.");

	gsoapProxy2_1 = soap_new_witsml20__Log(witsmlWellbore->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	witsmlWellbore->getRepository()->addDataObject(this);
	setWellbore(witsmlWellbore);
}

void Log::pushBackChannelSet(ChannelSet * channelSet)
{
	if (channelSet == nullptr) {
		throw invalid_argument("You cannot push back a null channel set.");
	}
	static_cast<witsml20__Log*>(gsoapProxy2_1)->ChannelSet.push_back(static_cast<witsml20__ChannelSet*>(channelSet->getEml21GsoapProxy()));

	getRepository()->addRelationship(this, channelSet);
}

std::vector<ChannelSet*> Log::getChannelSets() const
{
	return getRepository()->getTargetObjects<ChannelSet>(this);
}

#define SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(attributeDatatype, attributeName, constructor)\
void Log::set##attributeName(const attributeDatatype & attributeName) {\
	if (static_cast<witsml20__Log*>(gsoapProxy2_1)->attributeName == nullptr) { static_cast<witsml20__Log*>(gsoapProxy2_1)->attributeName = constructor(gsoapProxy2_1->soap); }\
	*static_cast<witsml20__Log*>(gsoapProxy2_1)->attributeName = attributeName;\
}

SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, TimeDepth, gsoap_eml2_1::soap_new_std__string)
SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, RunNumber, gsoap_eml2_1::soap_new_std__string)
SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, PassNumber, gsoap_eml2_1::soap_new_std__string)
SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, LoggingCompanyName, gsoap_eml2_1::soap_new_std__string)
SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, LoggingCompanyCode, gsoap_eml2_1::soap_new_std__string)
SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, ToolName, gsoap_eml2_1::soap_new_std__string)
SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, ToolClass, gsoap_eml2_1::soap_new_std__string)

void Log::loadTargetRelationships()
{
	WellboreObject::loadTargetRelationships();

	const std::vector<witsml20__ChannelSet *>& channelSets = static_cast<witsml20__Log*>(gsoapProxy2_1)->ChannelSet;

	for (size_t i = 0; i < channelSets.size(); ++i) {
		ChannelSet* channelSet = getRepository()->getDataObjectByUuid<ChannelSet>(channelSets[i]->uuid);
		if (channelSet == nullptr) {
			channelSet = new ChannelSet(channelSets[i]);
			getRepository()->addOrReplaceDataObject(channelSet);
			channelSet->loadTargetRelationships();
		}
		getRepository()->addRelationship(this, channelSet);
	}
}
