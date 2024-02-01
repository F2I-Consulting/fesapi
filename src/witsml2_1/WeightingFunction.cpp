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
#include "WeightingFunction.h"

#include "ToolErrorModel.h"

#include <stdexcept>
#include <sstream>

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_3;

const char* WeightingFunction::XML_TAG = "WeightingFunction";

WeightingFunction::WeightingFunction(COMMON_NS::DataObjectRepository * repo,
		const std::string & guid,
		const std::string & title,
		const std::string & depthFormula,
		const std::string & inclinationFormula,
		const std::string & azimuthFormula)
{
	if (repo == nullptr) throw invalid_argument("A Weighting Function must be associated to a repo.");

	gsoapProxy2_3 = soap_new_witsml21__WeightingFunction(repo->getGsoapContext(), 1);
	static_cast<witsml21__WeightingFunction*>(gsoapProxy2_3)->DepthFormula = depthFormula;
	static_cast<witsml21__WeightingFunction*>(gsoapProxy2_3)->InclinationFormula = inclinationFormula;

	witsml21__AzimuthFormula* aziFormula = soap_new_witsml21__AzimuthFormula(repo->getGsoapContext(), 1);
	static_cast<witsml21__WeightingFunction*>(gsoapProxy2_3)->AzimuthFormula = aziFormula;
	aziFormula->Formula = azimuthFormula;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addOrReplaceDataObject(this);
}

bool WeightingFunction::isTopLevelElement() const
{
	return getRepository()->getSourceObjects<WeightingFunctionDictionary>(this).empty();
}

void WeightingFunction::setKind(gsoap_eml2_3::witsml21__ErrorKind errorKind)
{
	static_cast<witsml21__WeightingFunction*>(gsoapProxy2_3)->Kind = soap_new_witsml21__ErrorKind(gsoapProxy2_3->soap, 1);
	*static_cast<witsml21__WeightingFunction*>(gsoapProxy2_3)->Kind = errorKind;
}

void WeightingFunction::pushBackSource(const std::string & source)
{
	if (!source.empty()) {
		static_cast<witsml21__WeightingFunction*>(gsoapProxy2_3)->Source.push_back(source);
	}
}

void WeightingFunction::setSingularityNorthFormula(const std::string & singularityNorthFormula)
{
	if (!singularityNorthFormula.empty()) {
		static_cast<witsml21__WeightingFunction*>(gsoapProxy2_3)->SingularityNorthFormula = soap_new_std__string(gsoapProxy2_3->soap, 1);
		static_cast<witsml21__WeightingFunction*>(gsoapProxy2_3)->SingularityNorthFormula->assign(singularityNorthFormula);
	}
}

void WeightingFunction::setSingularityEastFormula(const std::string & singularityEastFormula)
{
	if (!singularityEastFormula.empty()) {
		static_cast<witsml21__WeightingFunction*>(gsoapProxy2_3)->SingularityEastFormula = soap_new_std__string(gsoapProxy2_3->soap, 1);
		static_cast<witsml21__WeightingFunction*>(gsoapProxy2_3)->SingularityEastFormula->assign(singularityEastFormula);
	}
}

void WeightingFunction::setSingularityVerticalFormula(const std::string & singularityVerticalFormula)
{
	if (!singularityVerticalFormula.empty()) {
		static_cast<witsml21__WeightingFunction*>(gsoapProxy2_3)->SingularityVerticalFormula = soap_new_std__string(gsoapProxy2_3->soap, 1);
		static_cast<witsml21__WeightingFunction*>(gsoapProxy2_3)->SingularityVerticalFormula->assign(singularityVerticalFormula);
	}
}
