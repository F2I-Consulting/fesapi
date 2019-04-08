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

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_2;
using namespace epc;

const char* ToolErrorModelDictionary::XML_TAG = "ToolErrorModelDictionary";

ToolErrorModelDictionary::ToolErrorModelDictionary(soap* soapContext,
	const std::string & guid,
	const std::string & title)
{
	if (soapContext == nullptr) throw invalid_argument("A Tool Error Model Dictionary must be associated to a soap context.");

	gsoapProxy2_2 = soap_new_witsml2__ToolErrorModelDictionary(soapContext, 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");
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

	ToolErrorModel* tem = getEpcDocument()->getDataObjectByUuid<ToolErrorModel>(dict->ToolErrorModel[index]->uuid);
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
	if (updateXml && tem->toolErrorModelDictionary != nullptr) {
		throw invalid_argument("Cannot modify the existing dictionary of a tool error model");
	}
	tem->toolErrorModelDictionary = this;

	if (updateXml) {
		witsml2__ToolErrorModelDictionary* dict = static_cast<witsml2__ToolErrorModelDictionary*>(gsoapProxy2_2);
		dict->ToolErrorModel.push_back(static_cast<witsml2__ToolErrorModel*>(tem->getGsoapProxy2_2()));
	}
}

void ToolErrorModelDictionary::resolveTargetRelationships(COMMON_NS::EpcDocument* epcDoc)
{
	witsml2__ToolErrorModelDictionary* dict = static_cast<witsml2__ToolErrorModelDictionary*>(gsoapProxy2_2);

	updateXml = false;
	for (size_t index = 0; index < dict->ToolErrorModel.size(); ++index) {
		ToolErrorModel* tem = epcDoc->getDataObjectByUuid<ToolErrorModel>(getToolErrorModelUuid(index));
		pushBackToolErrorModel(tem);
		tem->resolveTargetRelationships(epcDoc);
	}
	updateXml = true;
}

DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> ToolErrorModelDictionary::getAllSourceRelationships() const
{
	return vector<Relationship>();
}

DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> ToolErrorModelDictionary::getAllTargetRelationships() const
{
	vector<Relationship> result;
	witsml2__ToolErrorModelDictionary* dict = static_cast<witsml2__ToolErrorModelDictionary*>(gsoapProxy2_2);

	vector<string> uuidAlreadyInserted;
	// XML forward relationship
	for (size_t index = 0; index < dict->ToolErrorModel.size(); ++index) {
		ToolErrorModel* tem = getEpcDocument()->getDataObjectByUuid<ToolErrorModel>(getToolErrorModelUuid(index));
		std::vector<ErrorTerm*> ets = tem->getErrorTermSet();
		for (size_t subIndex = 0; subIndex < ets.size(); ++subIndex) {
			string errorTermUuid = ets[subIndex]->getUuid();
			if (std::find(uuidAlreadyInserted.begin(), uuidAlreadyInserted.end(), errorTermUuid) == uuidAlreadyInserted.end()) {
				Relationship rel(ets[subIndex]->getPartNameInEpcDocument(), "", errorTermUuid);
				rel.setDestinationObjectType();
				result.push_back(rel);
				uuidAlreadyInserted.push_back(errorTermUuid);
			}
		}
	}

	return result;
}
