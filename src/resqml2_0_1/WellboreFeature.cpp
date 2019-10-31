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
#include "WellboreFeature.h"

#include <stdexcept>

#include "../witsml2_0/Well.h"
#include "../witsml2_0/Wellbore.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* WellboreFeature::XML_TAG = "WellboreFeature";

WellboreFeature::WellboreFeature(COMMON_NS::DataObjectRepository* repo, const string & guid, const std::string & title)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREWellboreFeature(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addOrReplaceDataObject(this);
}

void WellboreFeature::setWitsmlWellbore(WITSML2_0_NS::Wellbore * wellbore)
{
	getRepository()->addRelationship(this, wellbore);

	resqml20__obj_USCOREWellboreFeature* resqmlWellbore = static_cast<resqml20__obj_USCOREWellboreFeature*>(gsoapProxy2_0_1);
	resqmlWellbore->WitsmlWellbore = soap_new_resqml20__WitsmlWellboreReference(gsoapProxy2_0_1->soap);
	resqmlWellbore->WitsmlWellbore->WitsmlWellbore = wellbore->newResqmlReference();
	resqmlWellbore->WitsmlWellbore->WitsmlWell = wellbore->getWell()->newResqmlReference();
}

WITSML2_0_NS::Wellbore* WellboreFeature::getWitsmlWellbore() const
{
	resqml20__obj_USCOREWellboreFeature* resqmlWellbore = static_cast<resqml20__obj_USCOREWellboreFeature*>(gsoapProxy2_0_1);
	return resqmlWellbore->WitsmlWellbore != nullptr && resqmlWellbore->WitsmlWellbore->WitsmlWellbore
		? getRepository()->getDataObjectByUuid<WITSML2_0_NS::Wellbore>(resqmlWellbore->WitsmlWellbore->WitsmlWellbore->UUID)
		: nullptr;
}
