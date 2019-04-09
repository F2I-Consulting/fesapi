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
using namespace epc;

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
	return getEpcDocument()->getDataObjectByUuid<Well>(getWellDor()->Uuid);
}

void WellCompletion::setWell(Well* witsmlWell)
{
	if (witsmlWell == nullptr) {
		throw invalid_argument("Cannot set a null witsml Well to a witsml well completion");
	}

	// EPC
	witsmlWell->wellCompletionSet.push_back(this);

	// XML
	if (updateXml) {
		witsml2__WellCompletion* wellCompletion = static_cast<witsml2__WellCompletion*>(gsoapProxy2_1);
		wellCompletion->Well = witsmlWell->newEmlReference();
	}
}

std::vector<epc::Relationship> WellCompletion::getAllSourceRelationships() const
{
	vector<Relationship> result;

	// XML backward relationship
	for (size_t i = 0; i < wellboreCompletionSet.size(); ++i)
	{
		Relationship relWellboreCompletion(wellboreCompletionSet[i]->getPartNameInEpcDocument(), "", wellboreCompletionSet[i]->getUuid());
		relWellboreCompletion.setSourceObjectType();
		result.push_back(relWellboreCompletion);
	}

	return result;
}

std::vector<epc::Relationship> WellCompletion::getAllTargetRelationships() const
{
	vector<Relationship> result;

	// XML forward relationship
	Well* well = getWell();
	Relationship relWell(well->getPartNameInEpcDocument(), "", well->getUuid());
	relWell.setDestinationObjectType();
	result.push_back(relWell);

	return result;
}

void WellCompletion::resolveTargetRelationships(COMMON_NS::EpcDocument * epcDoc)
{
	gsoap_eml2_1::eml21__DataObjectReference* dor = getWellDor();
	Well* well = epcDoc->getDataObjectByUuid<Well>(dor->Uuid);

	if (well == nullptr) {
		throw invalid_argument("The DOR looks invalid.");
	}
	updateXml = false;
	setWell(well);
	updateXml = true;
}
