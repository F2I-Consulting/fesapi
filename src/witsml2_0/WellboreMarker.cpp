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
#include "WellboreMarker.h"

#include <limits>
#include <stdexcept>

#include "Wellbore.h"

using namespace std;
using namespace WITSML2_0_NS;
using namespace gsoap_eml2_1;

const char* WellboreMarker::XML_TAG = "WellboreMarker";

WellboreMarker::WellboreMarker(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid,
	const std::string & title,
	double md, gsoap_eml2_1::eml21__LengthUom mdUom, const std::string & mdDatum)
{
	if (repo == nullptr) throw invalid_argument("A repository must be provided.");

	gsoapProxy2_1 = soap_new_witsml20__WellboreMarker(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	static_cast<witsml20__WellboreMarker*>(gsoapProxy2_1)->Md = soap_new_witsml20__MeasuredDepthCoord(repo->getGsoapContext());
	static_cast<witsml20__WellboreMarker*>(gsoapProxy2_1)->Md->__item = md;
	static_cast<witsml20__WellboreMarker*>(gsoapProxy2_1)->Md->uom = mdUom;
	static_cast<witsml20__WellboreMarker*>(gsoapProxy2_1)->Md->datum = mdDatum;
}

WellboreMarker::WellboreMarker(Wellbore* witsmlWellbore,
	const std::string & guid,
	const std::string & title,
	double md, gsoap_eml2_1::eml21__LengthUom mdUom, const std::string & mdDatum)
{
	if (witsmlWellbore == nullptr) throw invalid_argument("A wellbore must be associated to a wellbore trajectory.");

	gsoapProxy2_1 = soap_new_witsml20__WellboreMarker(witsmlWellbore->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setWellbore(witsmlWellbore);

	static_cast<witsml20__WellboreMarker*>(gsoapProxy2_1)->Md = soap_new_witsml20__MeasuredDepthCoord(witsmlWellbore->getGsoapContext());
	static_cast<witsml20__WellboreMarker*>(gsoapProxy2_1)->Md->__item = md;
	static_cast<witsml20__WellboreMarker*>(gsoapProxy2_1)->Md->uom = mdUom;
	static_cast<witsml20__WellboreMarker*>(gsoapProxy2_1)->Md->datum = mdDatum;
}

COMMON_NS::DataObjectReference WellboreMarker::getWellboreDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<witsml20__WellboreMarker*>(gsoapProxy2_1)->Wellbore);
}

void WellboreMarker::setWellbore(Wellbore* witsmlWellbore)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("Cannot set a null witsml wellbore to a witsml WellboreMarker");
	}
	if (getRepository() == nullptr) {
		witsmlWellbore->getRepository()->addOrReplaceDataObject(this);
	}

	static_cast<witsml20__WellboreMarker*>(gsoapProxy2_1)->Wellbore = witsmlWellbore->newEmlReference();

	getRepository()->addRelationship(this, witsmlWellbore);
}

GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(WellboreMarker, Md, eml21__LengthUom, gsoap_eml2_1::soap_new_witsml20__MeasuredDepthCoord)

GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(WellboreMarker, DipAngle, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_eml2_1::soap_new_eml21__PlaneAngleMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(WellboreMarker, DipDirection, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_eml2_1::soap_new_eml21__PlaneAngleMeasure)
