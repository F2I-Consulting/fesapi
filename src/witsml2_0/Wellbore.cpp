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
#include "Wellbore.h"

#include "../witsml2/Well.h"

#include "../resqml2_0_1/WellboreFeature.h"

#include "WellboreCompletion.h"
#include "WellboreGeometry.h"
#include "Trajectory.h"
#include "Log.h"


using namespace std;
using namespace WITSML2_0_NS;
using namespace gsoap_eml2_1;

Wellbore::Wellbore(WITSML2_NS::Well* witsmlWell, const std::string & guid, const std::string & title)
{
	if (witsmlWell == nullptr) {
		throw invalid_argument("A wellbore must be associated to a well.");
	}

	gsoapProxy2_1 = soap_new_witsml20__Wellbore(witsmlWell->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	witsmlWell->getRepository()->addDataObject(this);
	setWell(witsmlWell);
}

Wellbore::Wellbore(
	WITSML2_NS::Well* witsmlWell,
	const std::string & guid,
	const std::string & title,
	gsoap_eml2_1::eml21__WellStatus statusWellbore,
	bool isActive,
	bool achievedTD)
{
	if (witsmlWell == nullptr) {
		throw invalid_argument("A wellbore must be associated to a well.");
	}

	gsoapProxy2_1 = soap_new_witsml20__Wellbore(witsmlWell->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	witsml20__Wellbore* wellbore = static_cast<witsml20__Wellbore*>(gsoapProxy2_1);

	wellbore->StatusWellbore = (eml21__WellStatus *)soap_malloc(wellbore->soap, sizeof(eml21__WellStatus));
	*wellbore->StatusWellbore = statusWellbore;

	wellbore->IsActive = (bool *)soap_malloc(wellbore->soap, sizeof(bool));
	*wellbore->IsActive = isActive;

	wellbore->AchievedTD = (bool *)soap_malloc(wellbore->soap, sizeof(bool));
	*wellbore->AchievedTD = achievedTD;

	witsmlWell->getRepository()->addDataObject(this);
	setWell(witsmlWell);
}

COMMON_NS::DataObjectReference Wellbore::getWellDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<witsml20__Wellbore*>(gsoapProxy2_1)->Well);
}

void Wellbore::setWell(WITSML2_NS::Well* witsmlWell)
{
	if (witsmlWell == nullptr) {
		throw invalid_argument("Cannot set a null witsml Well to a witsml wellbore");
	}
	witsml20__Wellbore* wellbore = static_cast<witsml20__Wellbore*>(gsoapProxy2_1);
	wellbore->Well = witsmlWell->newEmlReference();

	getRepository()->addRelationship(this, witsmlWell);
}

GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Wellbore, Number, gsoap_eml2_1::soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Wellbore, SuffixAPI, gsoap_eml2_1::soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Wellbore, NumGovt, gsoap_eml2_1::soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(gsoap_eml2_1::eml21__WellStatus, Wellbore, StatusWellbore, gsoap_eml2_1::soap_new_eml21__WellStatus)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(bool, Wellbore, IsActive, gsoap_eml2_1::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(gsoap_eml2_1::witsml20__WellPurpose, Wellbore, PurposeWellbore, gsoap_eml2_1::soap_new_witsml20__WellPurpose)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(gsoap_eml2_1::witsml20__WellboreType, Wellbore, TypeWellbore, gsoap_eml2_1::soap_new_witsml20__WellboreType)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(gsoap_eml2_1::witsml20__WellboreShape, Wellbore, Shape, gsoap_eml2_1::soap_new_witsml20__WellboreShape)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(bool, Wellbore, AchievedTD, gsoap_eml2_1::soap_new_bool)
GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(Wellbore, Md, eml21__LengthUom, gsoap_eml2_1::soap_new_witsml20__MeasuredDepthCoord)
GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(Wellbore, MdBit, eml21__LengthUom, gsoap_eml2_1::soap_new_witsml20__MeasuredDepthCoord)
GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(Wellbore, MdKickoff, eml21__LengthUom, gsoap_eml2_1::soap_new_witsml20__MeasuredDepthCoord)
GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(Wellbore, MdPlanned, eml21__LengthUom, gsoap_eml2_1::soap_new_witsml20__MeasuredDepthCoord)
GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(Wellbore, MdSubSeaPlanned, eml21__LengthUom, gsoap_eml2_1::soap_new_witsml20__MeasuredDepthCoord)
