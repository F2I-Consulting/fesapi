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
#include "ToolErrorModelDictionary.h"
#include "ToolErrorModel.h"
#include "ErrorTerm.h"

#include <stdexcept>
#include <sstream>
#include <algorithm>

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_3;

ToolErrorModelDictionary::ToolErrorModelDictionary(COMMON_NS::DataObjectRepository* repo,
	const std::string& guid,
	const std::string& title)
{
	if (repo == nullptr) throw invalid_argument("A Tool Error Model Dictionary must be associated to a repo.");

	gsoapProxy2_3 = soap_new_witsml21__ToolErrorModelDictionary(repo->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addOrReplaceDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
}

std::string ToolErrorModelDictionary::getToolErrorModelUuid(uint64_t index) const
{
	cannotBePartial();
	return static_cast<witsml21__ToolErrorModelDictionary*>(gsoapProxy2_3)->ToolErrorModel.at(index)->uuid;
}

ToolErrorModel* ToolErrorModelDictionary::getToolErrorModel(uint64_t index) const {
	witsml21__ToolErrorModelDictionary* dict = static_cast<witsml21__ToolErrorModelDictionary*>(gsoapProxy2_3);

	ToolErrorModel* tem = getRepository()->getDataObjectByUuid<ToolErrorModel>(dict->ToolErrorModel[index]->uuid);
	return tem == nullptr ? new WITSML2_1_NS::ToolErrorModel(dict->ToolErrorModel[index]) : tem;
}

std::vector<ToolErrorModel*> ToolErrorModelDictionary::getToolErrorModels() const {
	std::vector<ToolErrorModel*> result;

	for (size_t index = 0; index < static_cast<witsml21__ToolErrorModelDictionary*>(gsoapProxy2_3)->ToolErrorModel.size(); ++index) {
		result.push_back(getToolErrorModel(index));
	}

	return result;
}

void ToolErrorModelDictionary::pushBackToolErrorModel(ToolErrorModel* tem)
{
	getRepository()->addRelationship(this, tem);

	witsml21__ToolErrorModelDictionary* dict = static_cast<witsml21__ToolErrorModelDictionary*>(gsoapProxy2_3);
	dict->ToolErrorModel.push_back(static_cast<witsml21__ToolErrorModel*>(tem->getEml23GsoapProxy()));
}

void ToolErrorModelDictionary::loadTargetRelationships()
{
	witsml21__ToolErrorModelDictionary* dict = static_cast<witsml21__ToolErrorModelDictionary*>(gsoapProxy2_3);

	for (auto* tem : dict->ToolErrorModel) {
		COMMON_NS::AbstractObject* temWrapper = getRepository()->getDataObjectByUuid<ToolErrorModel>(tem->uuid);
		if (temWrapper == nullptr) {
			temWrapper = getRepository()->addOrReplaceDataObject(std::unique_ptr<COMMON_NS::AbstractObject>{new ToolErrorModel(tem)});
		}
		getRepository()->addRelationship(this, temWrapper);
	}
}
