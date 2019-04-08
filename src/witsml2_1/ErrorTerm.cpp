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
#include "witsml2_1/ErrorTerm.h"

#include "witsml2_1/WeightingFunction.h"
#include "witsml2_1/ToolErrorModel.h"

#include <stdexcept>
#include <sstream>

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_2;
using namespace epc;

const char* ErrorTerm::XML_TAG = "ErrorTerm";

ErrorTerm::ErrorTerm(soap* soapContext,
		const std::string & guid,
		const std::string & title,
		gsoap_eml2_2::witsml2__ErrorPropagationMode propagationMode,
		WeightingFunction* weightingFunction) : errorTermDictionary(nullptr)
{
	if (soapContext == nullptr) throw invalid_argument("An Error Term must be associated to a soap context.");

	gsoapProxy2_2 = soap_new_witsml2__ErrorTerm(soapContext, 1);
	static_cast<witsml2__ErrorTerm*>(gsoapProxy2_2)->PropagationMode = propagationMode;
	setWeightingFunction(weightingFunction);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");
}

bool ErrorTerm::isTopLevelElement() const
{
	return errorTermDictionary == nullptr;
}

std::string ErrorTerm::getWeightingFunctionUuid() const
{
	return static_cast<witsml2__ErrorTerm*>(gsoapProxy2_2)->WeightingFunction->Uuid;
}

WeightingFunction* ErrorTerm::getWeightingFunction() const
{
	return epcDocument->getDataObjectByUuid<WeightingFunction>(getWeightingFunctionUuid());
}

void ErrorTerm::setWeightingFunction(WeightingFunction* weightingFunction)
{
	if (weightingFunction == nullptr)
		throw invalid_argument("The weighting function cannot be null.");

	// EPC
	if (std::find(weightingFunction->errorTermSet.begin(), weightingFunction->errorTermSet.end(), this) == weightingFunction->errorTermSet.end()) {
		weightingFunction->errorTermSet.push_back(this);
	}

	// XMl
	if (updateXml)
	{
		if (gsoapProxy2_2 != nullptr) {
			static_cast<witsml2__ErrorTerm*>(gsoapProxy2_2)->WeightingFunction = weightingFunction->newEml22Reference();
		}
		else {
			throw logic_error("Not implemented yet");
		}
	}
}

void ErrorTerm::resolveTargetRelationships(COMMON_NS::EpcDocument* epcDoc)
{
	WeightingFunction* weightingFunction = epcDoc->getDataObjectByUuid<WeightingFunction>(getWeightingFunctionUuid());

	updateXml = false;
	setWeightingFunction(weightingFunction);
	updateXml = true;
}

DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> ErrorTerm::getAllSourceRelationships() const
{
	witsml2__ErrorTerm* et = static_cast<witsml2__ErrorTerm*>(gsoapProxy2_2);
	vector<Relationship> result;

	// XML backward relationship
	for (size_t i = 0; i < toolErrorModelSet.size(); ++i)
	{
		Relationship relTem(toolErrorModelSet[i]->getPartNameInEpcDocument(), "", toolErrorModelSet[i]->getUuid());
		relTem.setSourceObjectType();
		result.push_back(relTem);
	}

	if (errorTermDictionary != nullptr) {
		Relationship rel(errorTermDictionary->getPartNameInEpcDocument(), "", errorTermDictionary->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> ErrorTerm::getAllTargetRelationships() const
{
	witsml2__ErrorTerm* et = static_cast<witsml2__ErrorTerm*>(gsoapProxy2_2);
	vector<Relationship> result;

	// XML Forward relationship
	WeightingFunction* weightingFunction = getWeightingFunction();
	Relationship rel(weightingFunction->getPartNameInEpcDocument(), "", weightingFunction->getUuid());
	rel.setDestinationObjectType();
	result.push_back(rel);

	return result;
}
