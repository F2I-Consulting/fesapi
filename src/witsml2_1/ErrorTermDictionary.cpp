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
#include <algorithm>

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_2;

const char* ErrorTermDictionary::XML_TAG = "ErrorTermDictionary";

ErrorTermDictionary::ErrorTermDictionary(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid,
	const std::string & title)
{
	if (repo == nullptr) throw invalid_argument("A ErrorTermDictionary must be associated to a repo.");

	gsoapProxy2_2 = soap_new_witsml2__ErrorTermDictionary(repo->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addOrReplaceDataObject(this);
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

	ErrorTerm* et = getRepository()->getDataObjectByUuid<ErrorTerm>(dict->ErrorTerm[index]->uuid);
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
	getRepository()->addRelationship(this, et);

	witsml2__ErrorTermDictionary* dict = static_cast<witsml2__ErrorTermDictionary*>(gsoapProxy2_2);
	dict->ErrorTerm.push_back(static_cast<witsml2__ErrorTerm*>(et->getGsoapProxy2_2()));
}

void ErrorTermDictionary::loadTargetRelationships() const
{
	witsml2__ErrorTermDictionary* dict = static_cast<witsml2__ErrorTermDictionary*>(gsoapProxy2_2);

	for (size_t index = 0; index < dict->ErrorTerm.size(); ++index) {
		ErrorTerm* et = getRepository()->getDataObjectByUuid<ErrorTerm>(dict->ErrorTerm[index]->uuid);
		if (et == nullptr) {
			et = new ErrorTerm(dict->ErrorTerm[index]);
			getRepository()->addOrReplaceDataObject(et);
		}
		getRepository()->addRelationship(this, et);
	}
}
