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
#include "witsml2_1/ToolErrorModelDictionary.h"
#include "witsml2_1/ToolErrorModel.h"
#include "witsml2_1/ErrorTerm.h"

#include <stdexcept>
#include <sstream>
#include <algorithm>

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_2;

const char* ToolErrorModelDictionary::XML_TAG = "ToolErrorModelDictionary";

ToolErrorModelDictionary::ToolErrorModelDictionary(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid,
	const std::string & title)
{
	if (repo == nullptr) throw invalid_argument("A Tool Error Model Dictionary must be associated to a repo.");

	gsoapProxy2_2 = soap_new_witsml2__ToolErrorModelDictionary(repo->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addOrReplaceDataObject(this);
}

std::string ToolErrorModelDictionary::getToolErrorModelUuid(unsigned long index) const
{
	if (gsoapProxy2_2 != nullptr) {
		witsml2__ToolErrorModelDictionary* dict = static_cast<witsml2__ToolErrorModelDictionary*>(gsoapProxy2_2);
		if (index < dict->ToolErrorModel.size()) {
			return dict->ToolErrorModel[index]->uuid;
		}
		else{
			throw range_error("The index of tool error model is out of range");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

ToolErrorModel* ToolErrorModelDictionary::getToolErrorModel(unsigned long index) const {
	witsml2__ToolErrorModelDictionary* dict = static_cast<witsml2__ToolErrorModelDictionary*>(gsoapProxy2_2);

	ToolErrorModel* tem = getRepository()->getDataObjectByUuid<ToolErrorModel>(dict->ToolErrorModel[index]->uuid);
	return tem == nullptr ? new WITSML2_1_NS::ToolErrorModel(dict->ToolErrorModel[index]) : tem;
}

std::vector<ToolErrorModel*> ToolErrorModelDictionary::getToolErrorModels() const {
	std::vector<ToolErrorModel*> result;

	witsml2__ToolErrorModelDictionary* dict = static_cast<witsml2__ToolErrorModelDictionary*>(gsoapProxy2_2);
	for (size_t index = 0; index < dict->ToolErrorModel.size(); ++index) {
		result.push_back(getToolErrorModel(index));
	}

	return result;
}

void ToolErrorModelDictionary::pushBackToolErrorModel(ToolErrorModel* tem)
{
	getRepository()->addRelationship(this, tem);

	witsml2__ToolErrorModelDictionary* dict = static_cast<witsml2__ToolErrorModelDictionary*>(gsoapProxy2_2);
	dict->ToolErrorModel.push_back(static_cast<witsml2__ToolErrorModel*>(tem->getGsoapProxy2_2()));
}

void ToolErrorModelDictionary::loadTargetRelationships()
{
	witsml2__ToolErrorModelDictionary* dict = static_cast<witsml2__ToolErrorModelDictionary*>(gsoapProxy2_2);

	for (size_t index = 0; index < dict->ToolErrorModel.size(); ++index) {
		ToolErrorModel* tem = getRepository()->getDataObjectByUuid<ToolErrorModel>(dict->ToolErrorModel[index]->uuid);
		if (tem == nullptr) {
			tem = new ToolErrorModel(dict->ToolErrorModel[index]);
			getRepository()->addOrReplaceDataObject(tem);
		}
		getRepository()->addRelationship(this, tem);
	}
}
