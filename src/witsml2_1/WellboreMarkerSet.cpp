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
#include "WellboreMarkerSet.h"

#include <stdexcept>

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_3;

WellboreMarkerSet::WellboreMarkerSet(
	WITSML2_NS::Wellbore* witsmlWellbore,
	const std::string & guid,
	const std::string & title,
	double mdBaseSample,
	double mdTopSample,
	eml23__LengthUom mdUom)
{
	gsoapProxy2_3 = soap_new_witsml21__WellboreMarkerSet(witsmlWellbore->getGsoapContext());

	static_cast<witsml21__WellboreMarkerSet*>(gsoapProxy2_3)->MarkerSetInterval = soap_new_eml23__MdInterval(witsmlWellbore->getGsoapContext());
	static_cast<witsml21__WellboreMarkerSet*>(gsoapProxy2_3)->MarkerSetInterval->MdMin = mdTopSample;
	static_cast<witsml21__WellboreMarkerSet*>(gsoapProxy2_3)->MarkerSetInterval->MdMax = mdBaseSample;
	static_cast<witsml21__WellboreMarkerSet*>(gsoapProxy2_3)->MarkerSetInterval->Uom = soap_eml23__LengthUom2s(gsoapProxy2_3->soap, mdUom);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	if (witsmlWellbore != nullptr) {
		setWellbore(witsmlWellbore);
	}
}

COMMON_NS::DataObjectReference WellboreMarkerSet::getWellboreDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<witsml21__WellboreMarkerSet*>(gsoapProxy2_3)->Wellbore);
}

void WellboreMarkerSet::setWellbore(WITSML2_NS::Wellbore* witsmlWellbore)
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
	witsml21__WellboreMarkerSet* wms = static_cast<witsml21__WellboreMarkerSet*>(gsoapProxy2_3);
	wms->Wellbore = witsmlWellbore->newEml23Reference();
}
