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
#include "resqml2/ActivityTemplate.h"

#include <stdexcept>

using namespace std;
using namespace RESQML2_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* ActivityTemplate::XML_TAG = "ActivityTemplate";

vector<Relationship> ActivityTemplate::getAllEpcRelationships() const
{
	vector<Relationship> result;

	for (size_t i = 0; i < activityInstanceSet.size(); ++i)
	{
		Relationship rel(activityInstanceSet[i]->getPartNameInEpcDocument(), "", activityInstanceSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

void ActivityTemplate::resolveTargetRelationships(COMMON_NS::DataObjectRepository *)
{}
