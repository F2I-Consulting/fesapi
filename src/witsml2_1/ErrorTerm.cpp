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
#include "ErrorTerm.h"

#include "WeightingFunction.h"
#include "ToolErrorModel.h"

#include <stdexcept>
#include <sstream>
#include <algorithm>

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_3;

const char* ErrorTerm::XML_TAG = "ErrorTerm";

ErrorTerm::ErrorTerm(COMMON_NS::DataObjectRepository * repo,
		const std::string & guid,
		const std::string & title,
		gsoap_eml2_3::witsml21__ErrorPropagationMode propagationMode,
		WeightingFunction* weightingFunction)
{
	if (repo == nullptr) throw invalid_argument("An Error Term must be associated to a repo.");

	gsoapProxy2_3 = soap_new_witsml21__ErrorTerm(repo->getGsoapContext(), 1);
	static_cast<witsml21__ErrorTerm*>(gsoapProxy2_3)->PropagationMode = propagationMode;
	setWeightingFunction(weightingFunction);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addOrReplaceDataObject(this);
}

bool ErrorTerm::isTopLevelElement() const
{
	return getRepository()->getSourceObjects<ErrorTermDictionary>(this).empty();
}

gsoap_eml2_3::eml23__DataObjectReference* ErrorTerm::getWeightingFunctionDor() const
{
	return static_cast<witsml21__ErrorTerm*>(gsoapProxy2_3)->WeightingFunction;
}

WeightingFunction* ErrorTerm::getWeightingFunction() const
{
	return getRepository()->getDataObjectByUuid<WeightingFunction>(getWeightingFunctionDor()->Uuid);
}

void ErrorTerm::setWeightingFunction(WeightingFunction* weightingFunction)
{
	if (weightingFunction == nullptr)
		throw invalid_argument("The weighting function cannot be null.");

	getRepository()->addRelationship(this, weightingFunction);

	// XMl
	if (gsoapProxy2_3 != nullptr) {
		static_cast<witsml21__ErrorTerm*>(gsoapProxy2_3)->WeightingFunction = weightingFunction->newEml23Reference();
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void ErrorTerm::loadTargetRelationships()
{
	convertDorIntoRel<WeightingFunction>(getWeightingFunctionDor());
}
