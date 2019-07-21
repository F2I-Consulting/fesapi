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

const char* Log::XML_TAG = "Log";

Log::Log(Wellbore* witsmlWellbore,
		const std::string & guid,
		const std::string & title)
{
	if (witsmlWellbore == nullptr) throw invalid_argument("A log must be associated to a well.");

	gsoapProxy2_2 = soap_new_witsml2__Log(witsmlWellbore->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setWellbore(witsmlWellbore);
}

gsoap_eml2_2::eml22__DataObjectReference* Log::getWellboreDor() const
{
	return static_cast<witsml2__Log*>(gsoapProxy2_2)->Wellbore;
}

class Wellbore* Log::getWellbore() const
{
	return getRepository()->getDataObjectByUuid<Wellbore>(getWellboreDor()->Uuid);
}

void Log::setWellbore(Wellbore* witsmlWellbore)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("Cannot set a null witsml Wellbore to a witsml log");
	}
	if (getRepository() == nullptr) {
		witsmlWellbore->getRepository()->addOrReplaceDataObject(this);
	}

	getRepository()->addRelationship(this, witsmlWellbore);

	// XML
	witsml2__Log* log = static_cast<witsml2__Log*>(gsoapProxy2_2);
	log->Wellbore = witsmlWellbore->newEml22Reference();
}

void Log::loadTargetRelationships()
{
	convertDorIntoRel<Wellbore>(getWellboreDor());
}
