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
#include "resqml2/Activity.h"

#include "resqml2/ActivityTemplate.h"

#include <stdexcept>
#include <algorithm>

using namespace std;
using namespace RESQML2_NS;
using namespace epc;

const char* Activity::XML_TAG = "Activity";

vector<Relationship> Activity::getAllEpcRelationships() const
{
	vector<Relationship> result;

	RESQML2_NS::ActivityTemplate* activityTemplate = getActivityTemplate();
	if (activityTemplate != nullptr) {
		Relationship rel(activityTemplate->getPartNameInEpcDocument(), "", activityTemplate->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
	else
		throw domain_error("The activity template associated to the activity cannot be nullptr.");

	std::vector<AbstractObject*> resqmlObjectSet = getResqmlObjectSet();
	for (size_t i = 0; i < resqmlObjectSet.size(); ++i) {
		Relationship relResqmlObject(resqmlObjectSet[i]->getPartNameInEpcDocument(), "", resqmlObjectSet[i]->getUuid());
		relResqmlObject.setDestinationObjectType();
		result.push_back(relResqmlObject);
	}

	return result;
}

std::vector<COMMON_NS::AbstractObject*> Activity::getResqmlObjectSet() const
{
	std::vector<COMMON_NS::AbstractObject*> result;

	unsigned int paramCount = getParameterCount();

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
	return getEpcDocument()->getDataObjectByUuid<RESQML2_NS::ActivityTemplate>(getActivityTemplateDor()->UUID);
}

