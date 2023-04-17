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

#include "../witsml2/Wellbore.h"

using namespace std;
using namespace RESQML2_NS;

WITSML2_NS::Wellbore* WellboreFeature::getWitsmlWellbore() const
{
	cannotBePartial();
	return repository->getDataObjectByUuid<WITSML2_NS::Wellbore>(getWitsmlWellboreDor().getUuid());
}

void WellboreFeature::loadTargetRelationships()
{
	COMMON_NS::DataObjectReference dor = getWitsmlWellboreDor();
	WITSML2_NS::Wellbore* witsmlWellbore = getRepository()->getDataObjectByUuid<WITSML2_NS::Wellbore>(dor.getUuid());
	if (witsmlWellbore == nullptr) { // partial transfer
		getRepository()->createPartial(dor);
		witsmlWellbore = getRepository()->getDataObjectByUuid<WITSML2_NS::Wellbore>(dor.getUuid());
	}
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("The DOR looks invalid.");
	}
	repository->addRelationship(this, witsmlWellbore);
}
