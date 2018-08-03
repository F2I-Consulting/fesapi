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
#include "witsml2_1/Log.h"
#include "witsml2_1/Wellbore.h"

#include <stdexcept>

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_2;
using namespace epc;

const char* Log::XML_TAG = "Log";

Log::Log(Wellbore* witsmlWellbore,
		const std::string & guid,
		const std::string & title):resqmlWellboreFrameRepresentation(nullptr)
{
	if (witsmlWellbore == nullptr) throw invalid_argument("A log must be associated to a well.");

	gsoapProxy2_2 = soap_new_witsml2__Log(witsmlWellbore->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	setWellbore(witsmlWellbore);
}

gsoap_eml2_2::eml22__DataObjectReference* Log::getWellboreDor() const
{
	return static_cast<witsml2__Log*>(gsoapProxy2_2)->Wellbore;
}

class Wellbore* Log::getWellbore() const
{
	return getEpcDocument()->getResqmlAbstractObjectByUuid<Wellbore>(getWellboreDor()->Uuid);
}

void Log::setWellbore(Wellbore* witsmlWellbore)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("Cannot set a null witsml Wellbore to a witsml log");
	}

	// EPC
	witsmlWellbore->logSet.push_back(this);

	// XML
	if (updateXml) {
		witsml2__Log* log = static_cast<witsml2__Log*>(gsoapProxy2_2);
		log->Wellbore = witsmlWellbore->newEml22Reference();
	}
}

void Log::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	gsoap_eml2_2::eml22__DataObjectReference* dor = getWellboreDor();
	Wellbore* wellbore = epcDoc->getResqmlAbstractObjectByUuid<Wellbore>(dor->Uuid);
	/*
	if (well == nullptr) { // partial transfer
	getEpcDocument()->createPartial(dor);
	well = getEpcDocument()->getResqmlAbstractObjectByUuid<well>(dor->Uuid);
	}
	*/
	if (wellbore == nullptr) {
		throw invalid_argument("The DOR looks invalid.");
	}
	updateXml = false;
	setWellbore(wellbore);
	updateXml = true;
}

vector<Relationship> Log::getAllEpcRelationships() const
{
	vector<Relationship> result;

	// XML forward relationship
	Wellbore* wellbore = getWellbore();
	Relationship relWellbore(wellbore->getPartNameInEpcDocument(), "", wellbore->getUuid());
	relWellbore.setDestinationObjectType();
	result.push_back(relWellbore);

	// XML backward relationship
	if (resqmlWellboreFrameRepresentation != nullptr)
	{
		Relationship rel(resqmlWellboreFrameRepresentation->getPartNameInEpcDocument(), "", resqmlWellboreFrameRepresentation->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}
