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
#include "GeobodyInterpretation.h"

#include <stdexcept>

#include "GeobodyFeature.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

GeobodyInterpretation::GeobodyInterpretation(RESQML2_NS::RockVolumeFeature * feature, const string & guid, const string & title)
{
	if (feature == nullptr) {
		throw invalid_argument("The interpreted feature cannot be null.");
	}
	if (!feature->isPartial() && feature->getXmlNamespace() == "resqml20" && dynamic_cast<RESQML2_0_1_NS::GeobodyFeature*>(feature) == nullptr) {
		throw invalid_argument("The interpreted feature must be a Geobody Feature if it is a RESQML 2.0.1 version.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREGeobodyInterpretation(feature->getGsoapContext());
	static_cast<_resqml20__GeobodyInterpretation*>(gsoapProxy2_0_1)->Domain = resqml20__Domain__mixed;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretedFeature(feature);
}

void GeobodyInterpretation::set3dShape(gsoap_eml2_3::resqml22__Shape3d geobody3dShape)
{
	_resqml20__GeobodyInterpretation* interp = static_cast<_resqml20__GeobodyInterpretation*>(gsoapProxy2_0_1);

	if (!has3dShape()) {
		interp->Geobody3dShape = static_cast<gsoap_resqml2_0_1::resqml20__Geobody3dShape*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(gsoap_resqml2_0_1::resqml20__Geobody3dShape)));
	}

	switch (geobody3dShape) {
	case gsoap_eml2_3::resqml22__Shape3d__channel: *interp->Geobody3dShape = resqml20__Geobody3dShape__channel; break;
	case gsoap_eml2_3::resqml22__Shape3d__delta: *interp->Geobody3dShape = resqml20__Geobody3dShape__delta; break;
	case gsoap_eml2_3::resqml22__Shape3d__dome: *interp->Geobody3dShape = resqml20__Geobody3dShape__dome; break;
	case gsoap_eml2_3::resqml22__Shape3d__dune: *interp->Geobody3dShape = resqml20__Geobody3dShape__dune; break;
	case gsoap_eml2_3::resqml22__Shape3d__dyke: *interp->Geobody3dShape = resqml20__Geobody3dShape__dyke; break;
	case gsoap_eml2_3::resqml22__Shape3d__fan: *interp->Geobody3dShape = resqml20__Geobody3dShape__fan; break;
	case gsoap_eml2_3::resqml22__Shape3d__reef: *interp->Geobody3dShape = resqml20__Geobody3dShape__reef; break;
	case gsoap_eml2_3::resqml22__Shape3d__sheet: *interp->Geobody3dShape = resqml20__Geobody3dShape__sheeth; break;
	case gsoap_eml2_3::resqml22__Shape3d__wedge: *interp->Geobody3dShape = resqml20__Geobody3dShape__wedge; break;
	default : throw invalid_argument("Unrecognized enum for v2.0.1");
	}
}

void GeobodyInterpretation::set3dShape201(gsoap_resqml2_0_1::resqml20__Geobody3dShape geobody3dShape)
{
	_resqml20__GeobodyInterpretation* interp = static_cast<_resqml20__GeobodyInterpretation*>(gsoapProxy2_0_1);

	if (!has3dShape()) {
		interp->Geobody3dShape = static_cast<gsoap_resqml2_0_1::resqml20__Geobody3dShape*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(gsoap_resqml2_0_1::resqml20__Geobody3dShape)));
	}

	*interp->Geobody3dShape = geobody3dShape;
}

bool GeobodyInterpretation::has3dShape() const
{
	return static_cast<_resqml20__GeobodyInterpretation*>(gsoapProxy2_0_1)->Geobody3dShape != nullptr;
}

gsoap_eml2_3::resqml22__Shape3d GeobodyInterpretation::get3dShape() const
{
	if (!has3dShape()) {
		throw invalid_argument("The geobody interpretation has not any 3d shape.");
	}
	switch (*static_cast<_resqml20__GeobodyInterpretation*>(gsoapProxy2_0_1)->Geobody3dShape) {
	case resqml20__Geobody3dShape__channel : return gsoap_eml2_3::resqml22__Shape3d__channel;
	case resqml20__Geobody3dShape__delta: return gsoap_eml2_3::resqml22__Shape3d__delta;
	case resqml20__Geobody3dShape__dome: return gsoap_eml2_3::resqml22__Shape3d__dome;
	case resqml20__Geobody3dShape__dune: return gsoap_eml2_3::resqml22__Shape3d__dune;
	case resqml20__Geobody3dShape__dyke: return gsoap_eml2_3::resqml22__Shape3d__dyke;
	case resqml20__Geobody3dShape__fan: return gsoap_eml2_3::resqml22__Shape3d__fan;
	case resqml20__Geobody3dShape__reef: return gsoap_eml2_3::resqml22__Shape3d__reef;
	case resqml20__Geobody3dShape__sheeth: return gsoap_eml2_3::resqml22__Shape3d__sheet;
	case resqml20__Geobody3dShape__wedge: return gsoap_eml2_3::resqml22__Shape3d__wedge;
	default: throw invalid_argument("Unrecognized enum for v2.2");
	}
}

gsoap_resqml2_0_1::resqml20__Geobody3dShape GeobodyInterpretation::get3dShape201() const
{
	if (!has3dShape()) {
		throw invalid_argument("The geobody interpretation has not any 3d shape.");
	}

	return *static_cast<_resqml20__GeobodyInterpretation*>(gsoapProxy2_0_1)->Geobody3dShape;
}
