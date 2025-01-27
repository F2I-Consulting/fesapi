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
#include "WellCompletion.h"

#include "../witsml2/Well.h"
#include "WellboreCompletion.h"

#include <stdexcept>

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_3;

const char* WellCompletion::XML_TAG = "WellCompletion";

WellCompletion::WellCompletion(WITSML2_NS::Well* witsmlWell,
	const std::string & guid,
	const std::string & title)
{
	if (witsmlWell == nullptr) {
		throw invalid_argument("A well must be associated to a well completion.");
	}

	gsoapProxy2_3 = soap_new_witsml21__WellCompletion(witsmlWell->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	witsmlWell->getRepository()->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
	setWell(witsmlWell);
}

COMMON_NS::DataObjectReference WellCompletion::getWellDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<witsml21__WellCompletion*>(gsoapProxy2_3)->Well);
}

WITSML2_NS::Well* WellCompletion::getWell() const
{
	return getRepository()->getDataObjectByUuid<WITSML2_NS::Well>(getWellDor().getUuid());
}

void WellCompletion::setWell(WITSML2_NS::Well* witsmlWell)
{
	if (witsmlWell == nullptr) {
		throw invalid_argument("Cannot set a null witsml Well to a witsml well completion");
	}

	witsml21__WellCompletion* wellCompletion = static_cast<witsml21__WellCompletion*>(gsoapProxy2_3);
	wellCompletion->Well = witsmlWell->newEml23Reference();

	getRepository()->addRelationship(this, witsmlWell);
}

std::vector<WellboreCompletion *> WellCompletion::getWellboreCompletions() const
{
	return getRepository()->getSourceObjects<WellboreCompletion>(this);
}

void WellCompletion::loadTargetRelationships()
{
	convertDorIntoRel<WITSML2_NS::Well>(getWellDor());
}
