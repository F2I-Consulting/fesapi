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
#include "witsml2_1/WellboreMarkerSet.h"

#include <stdexcept>

#include "witsml2_1/Well.h"

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_2;

const char* WellboreMarkerSet::XML_TAG = "WellboreMarkerSet";

WellboreMarkerSet::WellboreMarkerSet(
	Wellbore* witsmlWellbore,
	const std::string & guid,
	const std::string & title,
	const std::string & mdDatum,
	const double & mdBaseSample,
	const double & mdTopSample)
{
	if (witsmlWellbore == nullptr) throw invalid_argument("A wellbore marker set must be associated to a well.");

	gsoapProxy2_2 = soap_new_witsml2__WellboreMarkerSet(witsmlWellbore->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setWellbore(witsmlWellbore);
}

gsoap_eml2_2::eml22__DataObjectReference* WellboreMarkerSet::getWellboreDor() const
{
	return static_cast<witsml2__WellboreMarkerSet*>(gsoapProxy2_2)->Wellbore;
}

class Wellbore* WellboreMarkerSet::getWellbore() const
{
	return getRepository()->getDataObjectByUuid<Wellbore>(getWellboreDor()->Uuid);
}

void WellboreMarkerSet::setWellbore(Wellbore* witsmlWellbore)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("Cannot set a null witsml Wellbore to a witsml wellbore marker set");
	}
	if (getRepository() == nullptr) {
		witsmlWellbore->getRepository()->addOrReplaceDataObject(this);
	}

	// EPC
	getRepository()->addRelationship(this, witsmlWellbore);

	// XML
	witsml2__WellboreMarkerSet* wms = static_cast<witsml2__WellboreMarkerSet*>(gsoapProxy2_2);
	wms->Wellbore = witsmlWellbore->newEml22Reference();
}

void WellboreMarkerSet::loadTargetRelationships()
{
	convertDorIntoRel<Wellbore>(getWellboreDor());
}
