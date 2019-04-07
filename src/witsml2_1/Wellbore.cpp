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
#include "witsml2_1/Wellbore.h"

#include <stdexcept>

#include "witsml2_1/Well.h"

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_2;
using namespace epc;

const char* Wellbore::XML_TAG = "Wellbore";

Wellbore::Wellbore(
			Well* witsmlWell,
			const std::string & guid,
			const std::string & title)
{
	if (witsmlWell == nullptr) {
		throw invalid_argument("A wellbore must be associated to a well.");
	}

	gsoapProxy2_2 = soap_new_witsml2__Wellbore(witsmlWell->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setWell(witsmlWell);
}

Wellbore::Wellbore(
		Well* witsmlWell,
		const std::string & guid,
		const std::string & title,
		gsoap_eml2_2::eml22__WellStatus statusWellbore,
		const bool & isActive,
		gsoap_eml2_2::witsml2__WellPurpose purposeWellbore,
		gsoap_eml2_2::witsml2__WellboreType typeWellbore,
		const bool & achievedTD
	)
{
	if (witsmlWell == nullptr) throw invalid_argument("A wellbore must be associated to a well.");

	gsoapProxy2_2 = soap_new_witsml2__Wellbore(witsmlWell->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setWell(witsmlWell);

	witsml2__Wellbore* wellbore = static_cast<witsml2__Wellbore*>(gsoapProxy2_2);

	wellbore->StatusWellbore = (eml22__WellStatus *)soap_malloc(wellbore->soap, sizeof(eml22__WellStatus));
	*wellbore->StatusWellbore = statusWellbore;

	wellbore->IsActive = (bool *)soap_malloc(wellbore->soap, sizeof(bool));
	*wellbore->IsActive = isActive;

	wellbore->PurposeWellbore = (witsml2__WellPurpose *)soap_malloc(wellbore->soap, sizeof(witsml2__WellPurpose));
	*wellbore->PurposeWellbore = purposeWellbore;

	wellbore->TypeWellbore = (witsml2__WellboreType *)soap_malloc(wellbore->soap, sizeof(witsml2__WellboreType));
	*wellbore->TypeWellbore = typeWellbore;

	wellbore->AchievedTD = (bool *)soap_malloc(wellbore->soap, sizeof(bool));
	*wellbore->AchievedTD = achievedTD;
}

gsoap_eml2_2::eml22__DataObjectReference* Wellbore::getWellDor() const
{
	return static_cast<witsml2__Wellbore*>(gsoapProxy2_2)->Well;
}

class Well* Wellbore::getWell() const
{
	return getEpcDocument()->getDataObjectByUuid<Well>(getWellDor()->Uuid);
}

void Wellbore::setWell(Well* witsmlWell)
{
	if (witsmlWell == nullptr) {
		throw invalid_argument("Cannot set a null witsml Well to a witsml wellbore");
	}

	// EPC
	witsmlWell->wellboreSet.push_back(this);

	// XML
	if (updateXml) {
		witsml2__Wellbore* wellbore = static_cast<witsml2__Wellbore*>(gsoapProxy2_2);
		wellbore->Well = witsmlWell->newEml22Reference();
	}
}

void Wellbore::setShape(const witsml2__WellboreShape & shape)
{
	witsml2__Wellbore* wellbore = static_cast<witsml2__Wellbore*>(gsoapProxy2_2);

	if (wellbore->Shape == nullptr) {
		wellbore->Shape = soap_new_witsml2__WellboreShape(gsoapProxy2_2->soap, 1);
	}
	*wellbore->Shape = shape;
}

void Wellbore::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	gsoap_eml2_2::eml22__DataObjectReference* dor = getWellDor();
	Well* well = epcDoc->getDataObjectByUuid<Well>(dor->Uuid);
	/*
	if (well == nullptr) { // partial transfer
		getEpcDocument()->createPartial(dor);
		well = getEpcDocument()->getDataObjectByUuid<well>(dor->Uuid);
	}
	*/
	if (well == nullptr) {
		throw invalid_argument("The DOR looks invalid.");
	}
	updateXml = false;
	setWell(well);
	updateXml = true;
}

vector<Relationship> Wellbore::getAllEpcRelationships() const
{
	vector<Relationship> result;

	// XML forward relationship
	Well* well = getWell();
	Relationship relWell(well->getPartNameInEpcDocument(), "", well->getUuid());
	relWell.setDestinationObjectType();
	result.push_back(relWell);

	// XML backward relationship
	for (size_t i = 0; i < trajectorySet.size(); ++i)
	{
		Relationship rel(trajectorySet[i]->getPartNameInEpcDocument(), "", trajectorySet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	for (size_t i = 0; i < logSet.size(); ++i)
	{
		Relationship rel(logSet[i]->getPartNameInEpcDocument(), "", logSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	for (size_t i = 0; i < wellboreMarkerSetSet.size(); ++i)
	{
		Relationship rel(wellboreMarkerSetSet[i]->getPartNameInEpcDocument(), "", wellboreMarkerSetSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}
