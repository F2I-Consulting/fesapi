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
#include "witsml2_1/WeightingFunction.h"

#include "witsml2_1/ToolErrorModel.h"

#include <stdexcept>
#include <sstream>

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_2;
using namespace epc;

const char* WeightingFunction::XML_TAG = "WeightingFunction";

WeightingFunction::WeightingFunction(soap* soapContext,
		const std::string & guid,
		const std::string & title,
		const std::string & depthFormula,
		const std::string & inclinationFormula,
		const std::string & azimuthFormula) : weightingFunctionDictionary(nullptr)
{
	if (soapContext == nullptr) throw invalid_argument("A Weighting Function must be associated to a soap context.");

	gsoapProxy2_2 = soap_new_witsml2__WeightingFunction(soapContext, 1);
	static_cast<witsml2__WeightingFunction*>(gsoapProxy2_2)->DepthFormula = depthFormula;
	static_cast<witsml2__WeightingFunction*>(gsoapProxy2_2)->InclinationFormula = inclinationFormula;

	witsml2__AzimuthFormula* aziFormula = soap_new_witsml2__AzimuthFormula(soapContext, 1);
	static_cast<witsml2__WeightingFunction*>(gsoapProxy2_2)->AzimuthFormula = aziFormula;
	aziFormula->Formula = azimuthFormula;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");
}

bool WeightingFunction::isTopLevelElement() const
{
	return weightingFunctionDictionary == nullptr;
}

void WeightingFunction::setKind(gsoap_eml2_2::witsml2__ErrorKind errorKind)
{
	static_cast<witsml2__WeightingFunction*>(gsoapProxy2_2)->Kind = soap_new_witsml2__ErrorKind(gsoapProxy2_2->soap, 1);
	*static_cast<witsml2__WeightingFunction*>(gsoapProxy2_2)->Kind = errorKind;
}

void WeightingFunction::pushBackSource(const std::string & source)
{
	if (!source.empty()) {
		static_cast<witsml2__WeightingFunction*>(gsoapProxy2_2)->Source.push_back(source);
	}
}

void WeightingFunction::resolveTargetRelationships(COMMON_NS::EpcDocument* epcDoc) {}

DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> WeightingFunction::getAllSourceRelationships() const
{
	vector<Relationship> result;

	// XML backward relationship
	for (size_t i = 0; i < errorTermSet.size(); ++i) {
		Relationship rel(errorTermSet[i]->getPartNameInEpcDocument(), "", errorTermSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	if (weightingFunctionDictionary != nullptr) {
		Relationship rel(weightingFunctionDictionary->getPartNameInEpcDocument(), "", weightingFunctionDictionary->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> WeightingFunction::getAllTargetRelationships() const
{
	return vector<Relationship>();
}

void WeightingFunction::setSingularityNorthFormula(const std::string & singularityNorthFormula)
{
	if (!singularityNorthFormula.empty()) {
		static_cast<witsml2__WeightingFunction*>(gsoapProxy2_2)->SingularityNorthFormula = soap_new_std__string(gsoapProxy2_2->soap, 1);
		static_cast<witsml2__WeightingFunction*>(gsoapProxy2_2)->SingularityNorthFormula->assign(singularityNorthFormula);
	}
}

void WeightingFunction::setSingularityEastFormula(const std::string & singularityEastFormula)
{
	if (!singularityEastFormula.empty()) {
		static_cast<witsml2__WeightingFunction*>(gsoapProxy2_2)->SingularityEastFormula = soap_new_std__string(gsoapProxy2_2->soap, 1);
		static_cast<witsml2__WeightingFunction*>(gsoapProxy2_2)->SingularityEastFormula->assign(singularityEastFormula);
	}
}

void WeightingFunction::setSingularityVerticalFormula(const std::string & singularityVerticalFormula)
{
	if (!singularityVerticalFormula.empty()) {
		static_cast<witsml2__WeightingFunction*>(gsoapProxy2_2)->SingularityVerticalFormula = soap_new_std__string(gsoapProxy2_2->soap, 1);
		static_cast<witsml2__WeightingFunction*>(gsoapProxy2_2)->SingularityVerticalFormula->assign(singularityVerticalFormula);
	}
}
