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
#include "witsml2_0/ToolErrorModel.h"
#include "witsml2_0/ToolErrorTermSet.h"

#include <stdexcept>
#include <sstream>

using namespace std;
using namespace WITSML2_0_NS;
using namespace gsoap_eml2_1;
using namespace epc;

const char* ToolErrorModel::XML_TAG = "ToolErrorModel";

ToolErrorModel::ToolErrorModel(soap* soapContext,
		const std::string & guid,
		const std::string & title)
{
	if (soapContext == nullptr) throw invalid_argument("A Tool Error Model must be associated to a soap context.");

	gsoapProxy2_1 = soap_new_witsml2__ToolErrorModel(soapContext, 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

ToolErrorTermSet* ToolErrorModel::getToolErrorTermSet() const
{
	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_1);
	if (tem->UseErrorTermSet == nullptr) {
		return nullptr;
	}

	return getEpcDocument()->getResqmlAbstractObjectByUuid<ToolErrorTermSet>(*tem->UseErrorTermSet);
}

void ToolErrorModel::setToolErrorTermSet(ToolErrorTermSet* tets)
{
	if (tets == nullptr) {
		throw invalid_argument("Cannot set a null tool error term set to a tool error model");
	}

	// EPC
	tets->toolErrorModelSet.push_back(this);

	// XML
	if (updateXml) {
		witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_1);
		if (tem->UseErrorTermSet == nullptr) {
			tem->UseErrorTermSet = soap_new_std__string(gsoapProxy2_1->soap, 1);
		}
		tem->UseErrorTermSet->assign(tets->getUuid());
	}
}

void ToolErrorModel::setTypeSurveyTool(const gsoap_eml2_1::witsml2__TypeSurveyTool & typeSurveyTool)
{
	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_1);
	if (tem->TypeSurveyTool == nullptr) {
		tem->TypeSurveyTool = soap_new_witsml2__TypeSurveyTool(gsoapProxy2_1->soap, 1);
	}

	*tem->TypeSurveyTool = typeSurveyTool;
}

void ToolErrorModel::setAuthorization(const std::string & authority, const gsoap_eml2_1::witsml2__AuthorizationStatus & status)
{
	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_1);
	if (tem->Authorization == nullptr) {
		tem->Authorization = soap_new_witsml2__IscwsaAuthorizationData(gsoapProxy2_1->soap, 1);
	}
	tem->Authorization->Authority = authority;
	tem->Authorization->Status = status;
}

void ToolErrorModel::setAuthorizationVersion(const std::string & version)
{
	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_1);
	if (tem->Authorization == nullptr) {
		throw invalid_argument("You should first set an authorization.");
	}

	if (tem->Authorization->Version == nullptr) {
		tem->Authorization->Version = soap_new_std__string(gsoapProxy2_1->soap, 1);
	}
	tem->Authorization->Version->assign(version);
}

void ToolErrorModel::setAuthorizationComment(const std::string & comment) 
{
	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_1);
	if (tem->Authorization == nullptr) {
		throw invalid_argument("You should first set an authorization.");
	}

	if (tem->Authorization->Comment == nullptr) {
		tem->Authorization->Comment = soap_new_std__string(gsoapProxy2_1->soap, 1);
	}
	tem->Authorization->Comment->assign(comment);
}

void ToolErrorModel::setAuthorizationSource(const std::string & source)
{
	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_1);
	if (tem->Authorization == nullptr) {
		throw invalid_argument("You should first set an authorization.");
	}

	if (tem->Authorization->Source == nullptr) {
		tem->Authorization->Source = soap_new_std__string(gsoapProxy2_1->soap, 1);
	}
	tem->Authorization->Source->assign(source);
}

void ToolErrorModel::pushBackOperatingCondition(const std::string & parameter, const std::string & value)
{
	witsml2__IscwsaSurveyToolOperatingCondition* opCond = soap_new_witsml2__IscwsaSurveyToolOperatingCondition(gsoapProxy2_1->soap, 1);
	opCond->Parameter = soap_new_std__string(gsoapProxy2_1->soap, 1);
	opCond->Parameter->assign(parameter);
	opCond->Value = soap_new_std__string(gsoapProxy2_1->soap, 1);
	opCond->Value->assign(value);

	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_1);
	ostringstream oss;
	oss << tem->OperatingCondition.size();
	opCond->uid = oss.str();

	tem->OperatingCondition.push_back(opCond);
}

void ToolErrorModel::pushBackOperatingCondition(const std::string & parameter,
	const double & min, const std::string & minUom,
	const double & max, const std::string & maxUom)
{
	witsml2__IscwsaSurveyToolOperatingCondition* opCond = soap_new_witsml2__IscwsaSurveyToolOperatingCondition(gsoapProxy2_1->soap, 1);
	opCond->Parameter = soap_new_std__string(gsoapProxy2_1->soap, 1);
	opCond->Parameter->assign(parameter);
	opCond->Min = soap_new_eml21__GenericMeasure(gsoapProxy2_1->soap, 1);
	opCond->Min->__item = min;
	opCond->Min->uom = minUom;
	opCond->Max = soap_new_eml21__GenericMeasure(gsoapProxy2_1->soap, 1);
	opCond->Max->__item = max;
	opCond->Max->uom = maxUom;

	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_1);
	ostringstream oss;
	oss << tem->OperatingCondition.size();
	opCond->uid = oss.str();

	tem->OperatingCondition.push_back(opCond);
}

void ToolErrorModel::pushBackTermValue(const std::string & term, const gsoap_eml2_1::witsml2__ErrorPropagationMode & errorPropagationMode,
	const double & value, const std::string & uom,
	const std::string & p1, const std::string & p2, const std::string & p3)
{
	witsml2__IscwsaErrorTermValue* termValue = soap_new_witsml2__IscwsaErrorTermValue(gsoapProxy2_1->soap, 1);
	termValue->Term = term;
	termValue->Prop = errorPropagationMode;
	termValue->Value = soap_new_witsml2__MeasureOrQuantity(gsoapProxy2_1->soap, 1);
	termValue->Value->__item = value;
	termValue->Value->uom = uom;

	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_1);
	ostringstream oss;
	oss << tem->ErrorTermValue.size();
	termValue->uid = oss.str();

	if (!p1.empty()) {
		eml21__ExtensionNameValue* enm = soap_new_eml21__ExtensionNameValue(gsoapProxy2_1->soap, 1);
		enm->Name = "p1";
		enm->Value = soap_new_eml21__StringMeasure(gsoapProxy2_1->soap, 1);
		enm->Value->__item = p1;
		termValue->ExtensionNameValue.push_back(enm);
	}

	if (!p2.empty()) {
		eml21__ExtensionNameValue* enm = soap_new_eml21__ExtensionNameValue(gsoapProxy2_1->soap, 1);
		enm->Name = "p2";
		enm->Value = soap_new_eml21__StringMeasure(gsoapProxy2_1->soap, 1);
		enm->Value->__item = p2;
		termValue->ExtensionNameValue.push_back(enm);
	}

	if (!p3.empty()) {
		eml21__ExtensionNameValue* enm = soap_new_eml21__ExtensionNameValue(gsoapProxy2_1->soap, 1);
		enm->Name = "p3";
		enm->Value = soap_new_eml21__StringMeasure(gsoapProxy2_1->soap, 1);
		enm->Value->__item = p3;
		termValue->ExtensionNameValue.push_back(enm);
	}

	tem->ErrorTermValue.push_back(termValue);
}

void ToolErrorModel::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	ToolErrorTermSet* tets = getToolErrorTermSet();
	if (tets != nullptr) {
		updateXml = false;
		setToolErrorTermSet(tets);
		updateXml = true;
	}
}

vector<Relationship> ToolErrorModel::getAllEpcRelationships() const
{
	vector<Relationship> result;

	// XML forward relationship
	ToolErrorTermSet* tets = getToolErrorTermSet();
	if (tets != nullptr) {
		Relationship relTest(tets->getPartNameInEpcDocument(), "", tets->getUuid());
		relTest.setDestinationObjectType();
		result.push_back(relTest);
	}

	return result;
}
