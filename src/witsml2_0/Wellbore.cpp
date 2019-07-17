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
#include "witsml2_0/Wellbore.h"
#include "witsml2_0/Well.h"

#include <stdexcept>

using namespace std;
using namespace WITSML2_0_NS;
using namespace gsoap_eml2_1;

const char* Wellbore::XML_TAG = "Wellbore";

Wellbore::Wellbore( Well* witsmlWell, const std::string & guid, const std::string & title)
{
	if (witsmlWell == nullptr) throw invalid_argument("A wellbore must be associated to a well.");

	gsoapProxy2_1 = soap_new_witsml2__Wellbore(witsmlWell->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setWell(witsmlWell);
}

Wellbore::Wellbore(
		Well* witsmlWell,
		const std::string & guid,
		const std::string & title,
		gsoap_eml2_1::eml21__WellStatus statusWellbore,
		bool isActive,
		bool achievedTD
	)
{
	if (witsmlWell == nullptr) throw invalid_argument("A wellbore must be associated to a well.");

	gsoapProxy2_1 = soap_new_witsml2__Wellbore(witsmlWell->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	witsml2__Wellbore* wellbore = static_cast<witsml2__Wellbore*>(gsoapProxy2_1);

	wellbore->StatusWellbore = (eml21__WellStatus *)soap_malloc(wellbore->soap, sizeof(eml21__WellStatus));
	*wellbore->StatusWellbore = statusWellbore;

	wellbore->IsActive = (bool *)soap_malloc(wellbore->soap, sizeof(bool));
	*wellbore->IsActive = isActive;

	wellbore->AchievedTD = (bool *)soap_malloc(wellbore->soap, sizeof(bool));
	*wellbore->AchievedTD = achievedTD;

	setWell(witsmlWell);
}

gsoap_eml2_1::eml21__DataObjectReference* Wellbore::getWellDor() const
{
	return static_cast<witsml2__Wellbore*>(gsoapProxy2_1)->Well;
}

class Well* Wellbore::getWell() const
{
	return getRepository()->getDataObjectByUuid<Well>(getWellDor()->Uuid);
}


void Wellbore::setWell(Well* witsmlWell)
{
	if (witsmlWell == nullptr) {
		throw invalid_argument("Cannot set a null witsml Well to a witsml wellbore");
	}
	if (getRepository() == nullptr) {
		witsmlWell->getRepository()->addOrReplaceDataObject(this);
	}

	getRepository()->addRelationship(this, witsmlWell);

	witsml2__Wellbore* wellbore = static_cast<witsml2__Wellbore*>(gsoapProxy2_1);
	wellbore->Well = witsmlWell->newEmlReference();
}

void Wellbore::setShape(witsml2__WellboreShape shape)
{
	witsml2__Wellbore* wellbore = static_cast<witsml2__Wellbore*>(gsoapProxy2_1);

	if (wellbore->Shape == nullptr) {
		wellbore->Shape = soap_new_witsml2__WellboreShape(gsoapProxy2_1->soap, 1);
	}
	*wellbore->Shape = shape;
}

void Wellbore::loadTargetRelationships()
{
	convertDorIntoRel<Well>(getWellDor());
}

std::vector<RESQML2_0_1_NS::WellboreFeature *> Wellbore::getResqmlWellboreFeature() const
{
	return getRepository()->getSourceObjects<RESQML2_0_1_NS::WellboreFeature>(this);
}

std::vector<WellboreCompletion *> Wellbore::getWellboreCompletions() const
{
	return getRepository()->getSourceObjects<WellboreCompletion>(this);
}

std::vector<Trajectory *> Wellbore::getTrajectories() const
{
	return getRepository()->getSourceObjects<Trajectory>(this);
}
