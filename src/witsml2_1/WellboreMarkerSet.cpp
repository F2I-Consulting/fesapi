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
using namespace epc;

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
	return getEpcDocument()->getDataObjectByUuid<Wellbore>(getWellboreDor()->Uuid);
}

void WellboreMarkerSet::setWellbore(Wellbore* witsmlWellbore)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("Cannot set a null witsml Wellbore to a witsml wellbore marker set");
	}

	// EPC
	witsmlWellbore->wellboreMarkerSetSet.push_back(this);

	// XML
	if (updateXml) {
		witsml2__WellboreMarkerSet* wms = static_cast<witsml2__WellboreMarkerSet*>(gsoapProxy2_2);
		wms->Wellbore = witsmlWellbore->newEml22Reference();
	}
}

void WellboreMarkerSet::resolveTargetRelationships(COMMON_NS::EpcDocument* epcDoc)
{
	gsoap_eml2_2::eml22__DataObjectReference* dor = getWellboreDor();
	Wellbore* wellbore = epcDoc->getDataObjectByUuid<Wellbore>(dor->Uuid);
	/*
	if (well == nullptr) { // partial transfer
	getEpcDocument()->createPartial(dor);
	well = getEpcDocument()->getDataObjectByUuid<well>(dor->Uuid);
	}
	*/
	if (wellbore == nullptr) {
		throw invalid_argument("The DOR looks invalid.");
	}
	updateXml = false;
	setWellbore(wellbore);
	updateXml = true;
}

DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> WellboreMarkerSet::getAllSourceRelationships() const
{
	return vector<Relationship>();
}

DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> WellboreMarkerSet::getAllTargetRelationships() const
{
	vector<Relationship> result;

	// XML forward relationship
	Wellbore* wellbore = getWellbore();
	Relationship relWellbore(wellbore->getPartNameInEpcDocument(), "", wellbore->getUuid());
	relWellbore.setDestinationObjectType();
	result.push_back(relWellbore);

	return result;
}
