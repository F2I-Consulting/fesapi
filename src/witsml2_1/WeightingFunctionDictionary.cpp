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
#include "witsml2_1/WeightingFunctionDictionary.h"
#include "witsml2_1/WeightingFunction.h"

#include <stdexcept>
#include <sstream>

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_2;
using namespace epc;

const char* WeightingFunctionDictionary::XML_TAG = "WeightingFunctionDictionary";

WeightingFunctionDictionary::WeightingFunctionDictionary(soap* soapContext,
	const std::string & guid,
	const std::string & title)
{
	if (soapContext == nullptr) throw invalid_argument("A WeightingFunctionDictionary must be associated to a soap context.");

	gsoapProxy2_2 = soap_new_witsml2__WeightingFunctionDictionary(soapContext, 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");
}

std::string WeightingFunctionDictionary::getWeightingFunctionUuid(unsigned long index) const
{
	if (gsoapProxy2_2 != nullptr) {
		witsml2__WeightingFunctionDictionary* dict = static_cast<witsml2__WeightingFunctionDictionary*>(gsoapProxy2_2);
		if (index < dict->WeightingFunction.size()) {
			return dict->WeightingFunction[index]->uuid;
		}
		else{
			throw range_error("The index of Weighting Function is out of range");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

WeightingFunction* WeightingFunctionDictionary::getWeightingFunction(unsigned long index) const {
	witsml2__WeightingFunctionDictionary* dict = static_cast<witsml2__WeightingFunctionDictionary*>(gsoapProxy2_2);

	WeightingFunction* wf = getEpcDocument()->getDataObjectByUuid<WeightingFunction>(dict->WeightingFunction[index]->uuid);
	return wf == nullptr ? new WITSML2_1_NS::WeightingFunction(dict->WeightingFunction[index]) : wf;
}

std::vector<WeightingFunction*> WeightingFunctionDictionary::getWeightingFunctions() const {
	std::vector<WeightingFunction*> result;

	witsml2__WeightingFunctionDictionary* dict = static_cast<witsml2__WeightingFunctionDictionary*>(gsoapProxy2_2);
	for (size_t index = 0; index < dict->WeightingFunction.size(); ++index) {
		result.push_back(getWeightingFunction(index));
	}

	return result;
}

void WeightingFunctionDictionary::pushBackWeightingFunction(WeightingFunction* wf)
{
	if (updateXml && wf->weightingFunctionDictionary != nullptr) {
		throw invalid_argument("Cannot modify the existing dictionary of a weighting function");
	}
	wf->weightingFunctionDictionary = this;

	if (updateXml)
	{
		witsml2__WeightingFunctionDictionary* dict = static_cast<witsml2__WeightingFunctionDictionary*>(gsoapProxy2_2);
		dict->WeightingFunction.push_back(static_cast<witsml2__WeightingFunction*>(wf->getGsoapProxy2_2()));
	}
}

void WeightingFunctionDictionary::resolveTargetRelationships(COMMON_NS::EpcDocument* epcDoc)
{
	witsml2__WeightingFunctionDictionary* dict = static_cast<witsml2__WeightingFunctionDictionary*>(gsoapProxy2_2);

	updateXml = false;
	for (size_t index = 0; index < dict->WeightingFunction.size(); ++index) {
		WeightingFunction* wf = epcDoc->getDataObjectByUuid<WeightingFunction>(getWeightingFunctionUuid(index));
		pushBackWeightingFunction(wf);
		wf->resolveTargetRelationships(epcDoc);
	}
	updateXml = true;
}

DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> WeightingFunctionDictionary::getAllSourceRelationships() const
{
	return vector<Relationship>();
}

DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> WeightingFunctionDictionary::getAllTargetRelationships() const
{
	return vector<Relationship>();
}
