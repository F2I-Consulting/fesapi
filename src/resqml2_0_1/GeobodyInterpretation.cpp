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
#include "resqml2_0_1/GeobodyInterpretation.h"

#include "resqml2_0_1/GeobodyFeature.h"

#include <stdexcept>

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* GeobodyInterpretation::XML_TAG = "GeobodyInterpretation";

GeobodyInterpretation::GeobodyInterpretation(GeobodyFeature * feature, const string & guid, const string & title)
{
	if (!feature)
		throw invalid_argument("The interpreted feature cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREGeobodyInterpretation(feature->getGsoapContext(), 1);
	static_cast<_resqml2__GeobodyInterpretation*>(gsoapProxy2_0_1)->Domain = resqml2__Domain__mixed;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	setInterpretedFeature(feature);
}

void GeobodyInterpretation::set3dShape(gsoap_resqml2_0_1::resqml2__Geobody3dShape geobody3dShape)
{
	_resqml2__GeobodyInterpretation* interp = static_cast<_resqml2__GeobodyInterpretation*>(gsoapProxy2_0_1);

	if (!has3dShape()) {
		interp->Geobody3dShape = static_cast<gsoap_resqml2_0_1::resqml2__Geobody3dShape*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(gsoap_resqml2_0_1::resqml2__Geobody3dShape)));
	}

	*interp->Geobody3dShape = geobody3dShape;
}

bool GeobodyInterpretation::has3dShape() const
{
	return static_cast<_resqml2__GeobodyInterpretation*>(gsoapProxy2_0_1)->Geobody3dShape != nullptr;
}

gsoap_resqml2_0_1::resqml2__Geobody3dShape GeobodyInterpretation::get3dShape() const
{
	if (!has3dShape()) {
		throw invalid_argument("The geobody interpretation has not any 3d shape.");
	}

	return *static_cast<_resqml2__GeobodyInterpretation*>(gsoapProxy2_0_1)->Geobody3dShape;
}

