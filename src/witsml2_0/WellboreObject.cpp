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
#include "witsml2_0/WellboreObject.h"

#include "witsml2_0/Wellbore.h"

#include <stdexcept>

using namespace std;
using namespace WITSML2_0_NS;
using namespace gsoap_eml2_1;
using namespace epc;

Wellbore* WellboreObject::getWellbore() const
{
	return getRepository()->getDataObjectByUuid<Wellbore>(getWellboreDor()->Uuid);
}

void WellboreObject::resolveTargetRelationships(COMMON_NS::DataObjectRepository* epcDoc)
{
	gsoap_eml2_1::eml21__DataObjectReference* dor = getWellboreDor();
	Wellbore* wellbore = epcDoc->getDataObjectByUuid<Wellbore>(dor->Uuid);
	if (wellbore == nullptr) { // partial transfer
		getRepository()->createPartial(dor);
		wellbore = getRepository()->getDataObjectByUuid<Wellbore>(dor->Uuid);
	}
	if (wellbore == nullptr) {
		throw invalid_argument("The DOR looks invalid.");
	}

	updateXml = false;
	setWellbore(wellbore);
	updateXml = true;
}

vector<Relationship> WellboreObject::getAllEpcRelationships() const
{
	vector<Relationship> result;

	Wellbore* wellbore = getWellbore();
	Relationship relWellbore(wellbore->getPartNameInEpcDocument(), "", wellbore->getUuid());
	relWellbore.setDestinationObjectType();
	result.push_back(relWellbore);

	return result;
}
