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
#include "WeightingFunctionDictionary.h"
#include "WeightingFunction.h"

#include <stdexcept>
#include <sstream>

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_3;

WeightingFunctionDictionary::WeightingFunctionDictionary(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid,
	const std::string & title)
{
	if (repo == nullptr) throw invalid_argument("A WeightingFunctionDictionary must be associated to a repo.");

	gsoapProxy2_3 = soap_new_witsml21__WeightingFunctionDictionary(repo->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addOrReplaceDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
}

std::string WeightingFunctionDictionary::getWeightingFunctionUuid(uint64_t index) const
{
	cannotBePartial();
	return static_cast<witsml21__WeightingFunctionDictionary*>(gsoapProxy2_3)->WeightingFunction.at(index)->uuid;
}

WeightingFunction* WeightingFunctionDictionary::getWeightingFunction(uint64_t index) const {
	witsml21__WeightingFunctionDictionary* dict = static_cast<witsml21__WeightingFunctionDictionary*>(gsoapProxy2_3);

	WeightingFunction* wf = getRepository()->getDataObjectByUuid<WeightingFunction>(dict->WeightingFunction[index]->uuid);
	return wf == nullptr ? new WITSML2_1_NS::WeightingFunction(dict->WeightingFunction[index]) : wf;
}

std::vector<WeightingFunction*> WeightingFunctionDictionary::getWeightingFunctions() const {
	std::vector<WeightingFunction*> result;

	witsml21__WeightingFunctionDictionary* dict = static_cast<witsml21__WeightingFunctionDictionary*>(gsoapProxy2_3);
	for (size_t index = 0; index < dict->WeightingFunction.size(); ++index) {
		result.push_back(getWeightingFunction(index));
	}

	return result;
}

void WeightingFunctionDictionary::pushBackWeightingFunction(WeightingFunction* wf)
{
	getRepository()->addRelationship(this, wf);

	witsml21__WeightingFunctionDictionary* dict = static_cast<witsml21__WeightingFunctionDictionary*>(gsoapProxy2_3);
	dict->WeightingFunction.push_back(static_cast<witsml21__WeightingFunction*>(wf->getEml23GsoapProxy()));
}

void WeightingFunctionDictionary::loadTargetRelationships()
{
	witsml21__WeightingFunctionDictionary* dict = static_cast<witsml21__WeightingFunctionDictionary*>(gsoapProxy2_3);

	for (auto wf : dict->WeightingFunction) {
		COMMON_NS::AbstractObject* wfWrapper = getRepository()->getDataObjectByUuid<WeightingFunction>(wf->uuid);
		if (wfWrapper == nullptr) {
			 wfWrapper = getRepository()->addOrReplaceDataObject(std::unique_ptr<COMMON_NS::AbstractObject>(new WeightingFunction(wf)));
		}
		getRepository()->addRelationship(this, wfWrapper);
	}
}
