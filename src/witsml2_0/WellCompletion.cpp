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
#include "witsml2_0/WellCompletion.h"
#include "witsml2_0/Well.h"

#include <stdexcept>

using namespace std;
using namespace WITSML2_0_NS;
using namespace gsoap_eml2_1;

const char* WellCompletion::XML_TAG = "WellCompletion";

WellCompletion::WellCompletion(Well* witsmlWell,
	const std::string & guid,
	const std::string & title)
{
	if (witsmlWell == nullptr) throw invalid_argument("A well must be associated to a well completion.");

	gsoapProxy2_1 = soap_new_witsml2__WellCompletion(witsmlWell->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setWell(witsmlWell);
}

gsoap_eml2_1::eml21__DataObjectReference* WellCompletion::getWellDor() const
{
	return static_cast<witsml2__WellCompletion*>(gsoapProxy2_1)->Well;
}

class Well* WellCompletion::getWell() const
{
	return getRepository()->getDataObjectByUuid<Well>(getWellDor()->Uuid);
}

void WellCompletion::setWell(Well* witsmlWell)
{
	if (witsmlWell == nullptr) {
		throw invalid_argument("Cannot set a null witsml Well to a witsml well completion");
	}
	if (getRepository() == nullptr) {
		witsmlWell->getRepository()->addOrReplaceDataObject(this);
	}

	getRepository()->addRelationship(this, witsmlWell);

	witsml2__WellCompletion* wellCompletion = static_cast<witsml2__WellCompletion*>(gsoapProxy2_1);
	wellCompletion->Well = witsmlWell->newEmlReference();
}

std::vector<WellboreCompletion const *> WellCompletion::getWellboreCompletions() const
{
	return getRepository()->getSourceObjects<WellboreCompletion>(this);
}

void WellCompletion::loadTargetRelationships() const
{
	convertDorIntoRel<Well>(getWellDor());
}
