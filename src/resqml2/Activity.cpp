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
#include "Activity.h"

#include "ActivityTemplate.h"

#include <stdexcept>
#include <algorithm>

using namespace std;
using namespace RESQML2_NS;

const char* Activity::XML_TAG = "Activity";

std::vector<COMMON_NS::AbstractObject*> Activity::getResqmlObjectSet() const
{
	std::vector<COMMON_NS::AbstractObject*> result;

	const unsigned int paramCount = getParameterCount();
	for (unsigned int index=0; index < paramCount; ++index) {
		if (isAResqmlObjectParameter(index)) {
			COMMON_NS::AbstractObject* obj = getResqmlObjectParameterValue(index);
			if (std::find(result.begin(), result.end(), obj) == result.end()) {
				result.push_back(obj);
			}
		}
	}

	return result;
}

ActivityTemplate* Activity::getActivityTemplate() const
{
	return getRepository()->getDataObjectByUuid<RESQML2_NS::ActivityTemplate>(getActivityTemplateDor().getUuid());
}

void Activity::loadTargetRelationships()
{
	COMMON_NS::DataObjectReference dor = getActivityTemplateDor();
	RESQML2_NS::ActivityTemplate* targetObj = getRepository()->getDataObjectByUuid<ActivityTemplate>(dor.getUuid());
	if (targetObj == nullptr) { // partial transfer
		getRepository()->createPartial(dor);
		targetObj = getRepository()->getDataObjectByUuid<ActivityTemplate>(dor.getUuid());
		if (targetObj == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
	}
	repository->addRelationship(this, targetObj);
}
