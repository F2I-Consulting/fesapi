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
#include "witsml2_1/ErrorTermDictionary.h"
#include "witsml2_1/ErrorTerm.h"
#include "witsml2_1/WeightingFunction.h"

#include <stdexcept>
#include <sstream>

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_2;
using namespace epc;

const char* ErrorTermDictionary::XML_TAG = "ErrorTermDictionary";

ErrorTermDictionary::ErrorTermDictionary(soap* soapContext,
	const std::string & guid,
	const std::string & title)
{
	if (soapContext == nullptr) throw invalid_argument("A ErrorTermDictionary must be associated to a soap context.");

	gsoapProxy2_2 = soap_new_witsml2__ErrorTermDictionary(soapContext, 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");
}

std::string ErrorTermDictionary::getErrorTermUuid(unsigned long index) const
{
	if (gsoapProxy2_2 != nullptr) {
		witsml2__ErrorTermDictionary* dict = static_cast<witsml2__ErrorTermDictionary*>(gsoapProxy2_2);
		if (index < dict->ErrorTerm.size()) {
			return dict->ErrorTerm[index]->uuid;
		}
		else{
			throw range_error("The index of ErrorTerm is out of range");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

ErrorTerm* ErrorTermDictionary::getErrorTerm(unsigned long index) const {
	witsml2__ErrorTermDictionary* dict = static_cast<witsml2__ErrorTermDictionary*>(gsoapProxy2_2);

	ErrorTerm* et = getEpcDocument()->getDataObjectByUuid<ErrorTerm>(dict->ErrorTerm[index]->uuid);
	return et == nullptr ? new WITSML2_1_NS::ErrorTerm(dict->ErrorTerm[index]) : et;
}

std::vector<ErrorTerm*> ErrorTermDictionary::getErrorTerms() const {
	std::vector<ErrorTerm*> result;

	witsml2__ErrorTermDictionary* dict = static_cast<witsml2__ErrorTermDictionary*>(gsoapProxy2_2);
	for (size_t index = 0; index < dict->ErrorTerm.size(); ++index) {
		result.push_back(getErrorTerm(index));
	}

	return result;
}

void ErrorTermDictionary::pushBackErrorTerm(ErrorTerm* et)
{
	if (updateXml && et->errorTermDictionary != nullptr) {
		throw invalid_argument("Cannot modify the existing dictionary of a ErrorTerm");
	}
	et->errorTermDictionary = this;

	if (updateXml)
	{
		witsml2__ErrorTermDictionary* dict = static_cast<witsml2__ErrorTermDictionary*>(gsoapProxy2_2);
		dict->ErrorTerm.push_back(static_cast<witsml2__ErrorTerm*>(et->getGsoapProxy2_2()));
	}
}

void ErrorTermDictionary::resolveTargetRelationships(COMMON_NS::EpcDocument* epcDoc)
{
	witsml2__ErrorTermDictionary* dict = static_cast<witsml2__ErrorTermDictionary*>(gsoapProxy2_2);

	updateXml = false;
	for (size_t index = 0; index < dict->ErrorTerm.size(); ++index) {
		ErrorTerm* et = epcDoc->getDataObjectByUuid<ErrorTerm>(getErrorTermUuid(index));
		pushBackErrorTerm(et);
		et->resolveTargetRelationships(epcDoc);
	}
	updateXml = true;
}

DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> ErrorTermDictionary::getAllSourceRelationships() const
{
	return vector<Relationship>();
}

DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> ErrorTermDictionary::getAllTargetRelationships() const
{
	vector<Relationship> result;
	witsml2__ErrorTermDictionary* dict = static_cast<witsml2__ErrorTermDictionary*>(gsoapProxy2_2);

	vector<string> uuidAlreadyInserted;
	// XML forward relationship
	for (size_t index = 0; index < dict->ErrorTerm.size(); ++index) {
		ErrorTerm* et = getEpcDocument()->getDataObjectByUuid<ErrorTerm>(getErrorTermUuid(index));
		string weightingFunctionUuid = et->getWeightingFunctionUuid();
		if (std::find(uuidAlreadyInserted.begin(), uuidAlreadyInserted.end(), weightingFunctionUuid) == uuidAlreadyInserted.end()) {
			Relationship rel(et->getWeightingFunction()->getPartNameInEpcDocument(), "", weightingFunctionUuid);
			rel.setDestinationObjectType();
			result.push_back(rel);
			uuidAlreadyInserted.push_back(weightingFunctionUuid);
		}
	}

	return result;
}
