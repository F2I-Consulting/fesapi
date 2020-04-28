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

#include "../resqml2/RockVolumeFeature.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

GeobodyInterpretation::GeobodyInterpretation(RESQML2_NS::RockVolumeFeature * feature, const string & guid, const string & title)
{
	if (!feature)
		throw invalid_argument("The interpreted feature cannot be null.");

	gsoapProxy2_3 = soap_new_resqml22__GeobodyInterpretation(feature->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setInterpretedFeature(feature);
}

void GeobodyInterpretation::set3dShape(gsoap_eml2_3::resqml22__Shape3d geobody3dShape)
{
	_resqml22__GeobodyInterpretation* interp = static_cast<_resqml22__GeobodyInterpretation*>(gsoapProxy2_3);

	if (!has3dShape()) {
		interp->GeologicUnit3dShape = soap_new_std__string(gsoapProxy2_3->soap);
	}

	*interp->GeologicUnit3dShape = gsoap_eml2_3::soap_resqml22__Shape3d2s(gsoapProxy2_3->soap, geobody3dShape);
}

bool GeobodyInterpretation::has3dShape() const
{
	return static_cast<_resqml22__GeobodyInterpretation*>(gsoapProxy2_3)->GeologicUnit3dShape != nullptr;
}

gsoap_eml2_3::resqml22__Shape3d GeobodyInterpretation::get3dShape() const
{
	if (!has3dShape()) {
		throw invalid_argument("The geobody interpretation has not any 3d shape.");
	}

	gsoap_eml2_3::resqml22__Shape3d result;
	soap_s2resqml22__Shape3d(gsoapProxy2_3->soap, static_cast<_resqml22__GeobodyInterpretation*>(gsoapProxy2_3)->GeologicUnit3dShape->c_str(), &result);
	return result;
}
