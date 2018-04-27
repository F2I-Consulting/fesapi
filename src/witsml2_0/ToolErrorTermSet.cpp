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
#include "witsml2_0/ToolErrorTermSet.h"
#include "witsml2_0/ToolErrorModel.h"

#include <stdexcept>
#include <sstream>

using namespace std;
using namespace WITSML2_0_NS;
using namespace gsoap_eml2_1;
using namespace epc;

const char* ToolErrorTermSet::XML_TAG = "ToolErrorTermSet";

ToolErrorTermSet::ToolErrorTermSet(soap* soapContext,
		const std::string & guid,
		const std::string & title)
{
	if (soapContext == nullptr) throw invalid_argument("A Tool Error Term Set must be associated to a soap context.");

	gsoapProxy2_1 = soap_new_witsml2__ToolErrorTermSet(soapContext, 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

vector<Relationship> ToolErrorTermSet::getAllEpcRelationships() const
{
	vector<Relationship> result;

	// XML backward relationship
	for (size_t i = 0; i < toolErrorModelSet.size(); ++i)
	{
		Relationship rel(toolErrorModelSet[i]->getPartNameInEpcDocument(), "", toolErrorModelSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

void ToolErrorTermSet::pushBackTerm(const std::string & name, const std::string & label,
	const std::string & weightingFunction, const std::string & weightingFunctionSource, const std::string & weightingFunctionComment,
	const gsoap_eml2_1::witsml2__ErrorTermSource & type,
	const std::string & depthFormula, const std::string & inclinationFormula, const std::string & azimuthFormula,
	const std::string & singularityNorthFormula, const std::string & singularityEastFormula, const std::string & singularityVerticalFormula)
{
	witsml2__ToolErrorTermSet* tets = static_cast<witsml2__ToolErrorTermSet*>(gsoapProxy2_1);

	witsml2__IscwsaErrorTerm* term = soap_new_witsml2__IscwsaErrorTerm(gsoapProxy2_1->soap, 1);
	ostringstream oss;
	oss << tets->ErrorTerm.size();
	term->uid = oss.str();
	tets->ErrorTerm.push_back(term);

	term->Name = name;
	term->Label = label;
	term->Type = soap_new_witsml2__ErrorTermSource(gsoapProxy2_1->soap, 1);
	*term->Type = type;

	witsml2__IscwsaErrorCoefficient* coeff = soap_new_witsml2__IscwsaErrorCoefficient(gsoapProxy2_1->soap, 1);
	oss.clear();
	oss.str("");
	oss << term->ErrorCoefficient.size();
	coeff->uid = oss.str();
	term->ErrorCoefficient.push_back(coeff);

	// Weighting function
	if (!weightingFunction.empty()) {
		eml21__ExtensionNameValue* enm = soap_new_eml21__ExtensionNameValue(gsoapProxy2_1->soap, 1);
		enm->Name = "Weighting Function";
		enm->Value = soap_new_eml21__StringMeasure(gsoapProxy2_1->soap, 1);
		enm->Value->__item = weightingFunction;
		coeff->ExtensionNameValue.push_back(enm);
	}

	if (!weightingFunctionSource.empty()) {
		eml21__ExtensionNameValue* enm = soap_new_eml21__ExtensionNameValue(gsoapProxy2_1->soap, 1);
		enm->Name = "Weighting Function Source";
		enm->Value = soap_new_eml21__StringMeasure(gsoapProxy2_1->soap, 1);
		enm->Value->__item = weightingFunctionSource;
		coeff->ExtensionNameValue.push_back(enm);
	}

	if (!weightingFunctionComment.empty()) {
		eml21__ExtensionNameValue* enm = soap_new_eml21__ExtensionNameValue(gsoapProxy2_1->soap, 1);
		enm->Name = "Weighting Function Comment";
		enm->Value = soap_new_eml21__StringMeasure(gsoapProxy2_1->soap, 1);
		enm->Value->__item = weightingFunctionComment;
		coeff->ExtensionNameValue.push_back(enm);
	}

	// Singularity formulas
	if (!singularityNorthFormula.empty()) {
		eml21__ExtensionNameValue* enm = soap_new_eml21__ExtensionNameValue(gsoapProxy2_1->soap, 1);
		enm->Name = "Singularity North Formula";
		enm->Value = soap_new_eml21__StringMeasure(gsoapProxy2_1->soap, 1);
		enm->Value->__item = singularityNorthFormula;
		coeff->ExtensionNameValue.push_back(enm);
	}

	if (!singularityEastFormula.empty()) {
		eml21__ExtensionNameValue* enm = soap_new_eml21__ExtensionNameValue(gsoapProxy2_1->soap, 1);
		enm->Name = "Singularity East Formula";
		enm->Value = soap_new_eml21__StringMeasure(gsoapProxy2_1->soap, 1);
		enm->Value->__item = weightingFunctionSource;
		coeff->ExtensionNameValue.push_back(enm);
	}

	if (!singularityVerticalFormula.empty()) {
		eml21__ExtensionNameValue* enm = soap_new_eml21__ExtensionNameValue(gsoapProxy2_1->soap, 1);
		enm->Name = "Singularity Vertical Formula";
		enm->Value = soap_new_eml21__StringMeasure(gsoapProxy2_1->soap, 1);
		enm->Value->__item = weightingFunctionComment;
		coeff->ExtensionNameValue.push_back(enm);
	}

	// Formulas
	if (!depthFormula.empty()) {
		witsml2__Depth* depth = soap_new_witsml2__Depth(gsoapProxy2_1->soap, 1);
		depth->Depth = depthFormula;
		oss.clear();
		oss.str("");
		oss << coeff->AbstractIscwsaErrorCoefficient.size();
		depth->uid = oss.str();
		coeff->AbstractIscwsaErrorCoefficient.push_back(depth);
	}

	if (!inclinationFormula.empty()) {
		witsml2__Inc* inc = soap_new_witsml2__Inc(gsoapProxy2_1->soap, 1);
		inc->Inc = inclinationFormula;
		oss.clear();
		oss.str("");
		oss << coeff->AbstractIscwsaErrorCoefficient.size();
		inc->uid = oss.str();
		coeff->AbstractIscwsaErrorCoefficient.push_back(inc);
	}

	if (!azimuthFormula.empty()) {
		witsml2__Azi* azi = soap_new_witsml2__Azi(gsoapProxy2_1->soap, 1);
		azi->Azi = azimuthFormula;
		oss.clear();
		oss.str("");
		oss << coeff->AbstractIscwsaErrorCoefficient.size();
		azi->uid = oss.str();
		coeff->AbstractIscwsaErrorCoefficient.push_back(azi);
	}
}
