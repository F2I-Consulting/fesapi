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
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_3;

WellboreMarker::WellboreMarker(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid,
	const std::string & title,
	double md, gsoap_eml2_3::eml23__LengthUom mdUom)
{
	if (repo == nullptr) throw invalid_argument("A repository must be provided.");

	gsoapProxy2_3 = soap_new_witsml21__WellboreMarker(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	static_cast<witsml21__WellboreMarker*>(gsoapProxy2_3)->Md = soap_new_eml23__MeasuredDepth(repo->getGsoapContext());
	static_cast<witsml21__WellboreMarker*>(gsoapProxy2_3)->Md->MeasuredDepth = soap_new_eml23__LengthMeasureExt(repo->getGsoapContext());
	static_cast<witsml21__WellboreMarker*>(gsoapProxy2_3)->Md->MeasuredDepth->__item = md;
	static_cast<witsml21__WellboreMarker*>(gsoapProxy2_3)->Md->MeasuredDepth->uom = soap_eml23__LengthUom2s(repo->getGsoapContext(), mdUom);

	repo->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
}

WellboreMarker::WellboreMarker(WITSML2_NS::Wellbore* witsmlWellbore,
	const std::string & guid,
	const std::string & title,
	double md, gsoap_eml2_3::eml23__LengthUom mdUom)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("The WITSML wellbore cannot be nullptr.");
	}

	auto* soapCtx = witsmlWellbore->getGsoapContext();
	gsoapProxy2_3 = soap_new_witsml21__WellboreMarker(soapCtx);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	witsmlWellbore->getRepository()->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
	setWellbore(witsmlWellbore);

	static_cast<witsml21__WellboreMarker*>(gsoapProxy2_3)->Md = soap_new_eml23__MeasuredDepth(soapCtx);
	static_cast<witsml21__WellboreMarker*>(gsoapProxy2_3)->Md->MeasuredDepth = soap_new_eml23__LengthMeasureExt(soapCtx);
	static_cast<witsml21__WellboreMarker*>(gsoapProxy2_3)->Md->MeasuredDepth->__item = md;
	static_cast<witsml21__WellboreMarker*>(gsoapProxy2_3)->Md->MeasuredDepth->uom = soap_eml23__LengthUom2s(soapCtx, mdUom);
}

COMMON_NS::DataObjectReference WellboreMarker::getWellboreDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<witsml21__WellboreMarker*>(gsoapProxy2_3)->Wellbore);
}

void WellboreMarker::setWellbore(WITSML2_NS::Wellbore* witsmlWellbore)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("Cannot set a null WITSML wellbore to a WITSML WellboreMarker");
	}

	static_cast<witsml21__WellboreMarker*>(gsoapProxy2_3)->Wellbore = witsmlWellbore->newEml23Reference();

	getRepository()->addRelationship(this, witsmlWellbore);
}

GETTER_AND_SETTER_MEASURED_DEPTH_OPTIONAL_ATTRIBUTE_IMPL(WellboreMarker, Md, eml23__LengthUom, gsoap_eml2_3::soap_new_eml23__MeasuredDepth)

GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(WellboreMarker, DipAngle, gsoap_eml2_3::eml23__PlaneAngleUom, gsoap_eml2_3::soap_eml23__PlaneAngleUom2s, gsoap_eml2_3::soap_new_eml23__PlaneAngleMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(WellboreMarker, DipDirection, gsoap_eml2_3::eml23__PlaneAngleUom, gsoap_eml2_3::soap_eml23__PlaneAngleUom2s, gsoap_eml2_3::soap_new_eml23__PlaneAngleMeasure)
