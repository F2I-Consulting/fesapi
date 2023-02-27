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
#include "Activity.h"

#include "../eml2/ActivityTemplate.h"

#include <algorithm>

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

Activity::Activity(EML2_NS::ActivityTemplate* activityTemplate, const string & guid, const string & title)
{
	if (activityTemplate == nullptr) {
		throw invalid_argument("The activity template of an activity must be not null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREActivity(activityTemplate->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	activityTemplate->getRepository()->addDataObject(this);
	setActivityTemplate(activityTemplate);
}

void Activity::pushBackParameter(const std::string& title, double value, resqml20__ResqmlUom uom)
{
	EML2_NS::ActivityTemplate* activityTemplate = getActivityTemplate();
	if (!activityTemplate->isPartial()) {
		if (!activityTemplate->isAnExistingParameter(title)) {
			throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
		}
		int64_t maxOccurs = activityTemplate->getParameterMaxOccurences(title);
		if (maxOccurs > -1 && static_cast<uint64_t>(maxOccurs) <= getParameterCount(title)) {
			throw invalid_argument("The max number of occurrences has already been reached for parameter " + title);
		}
		vector<resqml20__ParameterKind> allowedKinds = activityTemplate->getParameterAllowedKinds(title);
		if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), resqml20__ParameterKind::floatingPoint) == allowedKinds.end()) {
			throw invalid_argument("The parameter template " + title + " does not allow a double datatype.");
		}
	}

	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	resqml20__FloatingPointQuantityParameter* fpqp = soap_new_resqml20__FloatingPointQuantityParameter(activity->soap);
	fpqp->Title = title;
	fpqp->Value = value;
	fpqp->Uom = uom;
	activity->Parameter.push_back(fpqp);
}

void Activity::pushBackParameter(const std::string& title, const std::string & value)
{
	EML2_NS::ActivityTemplate* activityTemplate = getActivityTemplate();
	if (!activityTemplate->isPartial()) {
		if (activityTemplate->isAnExistingParameter(title) == false)
			throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
		int64_t maxOccurs = activityTemplate->getParameterMaxOccurences(title);
		if (maxOccurs > -1 && static_cast<uint64_t>(maxOccurs) <= getParameterCount(title))
			throw invalid_argument("The max number of occurrences has already been reached for parameter " + title);
		vector<resqml20__ParameterKind> allowedKinds = activityTemplate->getParameterAllowedKinds(title);
		if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), resqml20__ParameterKind::string) == allowedKinds.end())
			throw invalid_argument("The parameter template " + title + " does not allow a string datatype.");
	}

	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	resqml20__StringParameter* sp = soap_new_resqml20__StringParameter(activity->soap);
	sp->Title = title;
	sp->Value = value;
	activity->Parameter.push_back(sp);
}

void Activity::pushBackParameter(const std::string& title, int64_t value)
{
	EML2_NS::ActivityTemplate* activityTemplate = getActivityTemplate();
	if (!activityTemplate->isPartial()) {
		if (activityTemplate->isAnExistingParameter(title) == false)
			throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
		int64_t maxOccurs = activityTemplate->getParameterMaxOccurences(title);
		if (maxOccurs > -1 && static_cast<uint64_t>(maxOccurs) <= getParameterCount(title))
			throw invalid_argument("The max number of occurrences has already been reached for parameter " + title);
		vector<resqml20__ParameterKind> allowedKinds = activityTemplate->getParameterAllowedKinds(title);
		if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), resqml20__ParameterKind::integer) == allowedKinds.end())
			throw invalid_argument("The parameter template " + title + " does not allow an integer datatype.");
	}

	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	resqml20__IntegerQuantityParameter* iqp = soap_new_resqml20__IntegerQuantityParameter(activity->soap);
	iqp->Title = title;
	iqp->Value = value;
	activity->Parameter.push_back(iqp);
}

void Activity::pushBackParameter(const std::string& title, AbstractObject* resqmlObject)
{
	if (resqmlObject == nullptr) {
		throw invalid_argument("The RESQML object must be non null.");
	}
	EML2_NS::ActivityTemplate* activityTemplate = getActivityTemplate();
	if (!activityTemplate->isPartial()) {
		if (activityTemplate->isAnExistingParameter(title) == false) {
			throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
		}

		int64_t maxOccurs = activityTemplate->getParameterMaxOccurences(title);
		if (maxOccurs > -1 && static_cast<uint64_t>(maxOccurs) <= getParameterCount(title)) {
			throw invalid_argument("The max number of occurrences has already been reached for parameter " + title);
		}

		vector<resqml20__ParameterKind> allowedKinds = activityTemplate->getParameterAllowedKinds(title);
		if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), resqml20__ParameterKind::dataObject) == allowedKinds.end()) {
			throw invalid_argument("The parameter template " + title + " does not allow a data object datatype.");
		}
	}

	getRepository()->addRelationship(this, resqmlObject);

	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	resqml20__DataObjectParameter* dop = soap_new_resqml20__DataObjectParameter(activity->soap);
	dop->Title = title;
	dop->DataObject = resqmlObject->newResqmlReference();
	activity->Parameter.push_back(dop);
}

uint64_t Activity::getParameterCount() const
{
	return static_cast<_resqml20__Activity*>(gsoapProxy2_0_1)->Parameter.size();
}

uint64_t Activity::getParameterCount(const std::string & paramTitle) const
{
	return getParameterFromTitle(paramTitle).size();
}

std::string Activity::getParameterTitle(uint64_t index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	return activity->Parameter.at(index)->Title;
}

std::vector<uint64_t> Activity::getParameterIndexOfTitle(const std::string & paramTitle) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	vector<uint64_t> paramIndex;
	for (uint64_t i = 0; i < activity->Parameter.size(); ++i) {
		if (activity->Parameter[i]->Title == paramTitle) {
			paramIndex.push_back(i);
		}
	}

	return paramIndex;
}

std::vector<resqml20__AbstractActivityParameter*> Activity::getParameterFromTitle(const std::string & paramTitle) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	std::vector<resqml20__AbstractActivityParameter*> params;
	for (auto* activityParam : activity->Parameter) {
		if (activityParam->Title == paramTitle) {
			params.push_back(activityParam);
		}
	}

	return params;
}

/*****************************
********** DOUBLE ************
*****************************/
bool Activity::isAFloatingPointQuantityParameter(const std::string & paramTitle) const
{
	vector<resqml20__AbstractActivityParameter*> params = getParameterFromTitle(paramTitle);

	if (params.empty()) {
		throw invalid_argument("There exists no " + paramTitle + " parameter in this activity.");
	}

	for (const auto* param : params) 	{
		if (param->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__FloatingPointQuantityParameter) {
			return false;
		}
	}

	return true;
}

bool Activity::isAFloatingPointQuantityParameter(uint64_t index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	return activity->Parameter.at(index)->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__FloatingPointQuantityParameter;
}

vector<double> Activity::getFloatingPointQuantityParameterValue(const std::string & paramTitle) const
{
	vector<resqml20__AbstractActivityParameter*> params = getParameterFromTitle(paramTitle);

	if (params.size() < 1)
		throw invalid_argument("There exists no " + paramTitle + " parameter in this activity.");

	vector<double> result;
	for (auto const* param : params) {
		if (param->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__FloatingPointQuantityParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non double values.");
		else
			result.push_back(static_cast<resqml20__FloatingPointQuantityParameter const*>(param)->Value);
	}

	return result;
}

double Activity::getFloatingPointQuantityParameterValue(uint64_t index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.at(index)->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__FloatingPointQuantityParameter)
		throw invalid_argument("The parameter at index is not a floating point quantity parameter.");

	return static_cast<resqml20__FloatingPointQuantityParameter*>(activity->Parameter[index])->Value;
}

vector<resqml20__ResqmlUom> Activity::getFloatingPointQuantityParameterUom(const std::string & paramTitle) const
{
	vector<resqml20__AbstractActivityParameter*> params = getParameterFromTitle(paramTitle);

	if (params.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	vector<resqml20__ResqmlUom> result;
	for (auto const* param : params) {
		if (param->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__FloatingPointQuantityParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non double values.");
		else
			result.push_back(static_cast<resqml20__FloatingPointQuantityParameter const*>(param)->Uom);
	}

	return result;
}

gsoap_resqml2_0_1::resqml20__ResqmlUom Activity::getFloatingPointQuantityParameterUom(uint64_t index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.at(index)->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__FloatingPointQuantityParameter)
		throw invalid_argument("The parameter index is not in the parameter range.");

	return static_cast<resqml20__FloatingPointQuantityParameter*>(activity->Parameter[index])->Uom;
}

/*****************************
********** INTEGER ***********
*****************************/
bool Activity::isAnIntegerQuantityParameter(const std::string & paramTitle) const
{
	vector<resqml20__AbstractActivityParameter*> params = getParameterFromTitle(paramTitle);

	if (params.size() < 1)
		throw invalid_argument("There exists no " + paramTitle + " parameter in this activity.");

	for (auto const* param : params) {
		if (param->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerQuantityParameter)
			return false;
	}

	return true;
}

bool Activity::isAnIntegerQuantityParameter(uint64_t index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	return activity->Parameter.at(index)->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerQuantityParameter;
}

vector<int32_t> Activity::getIntegerQuantityParameterValue(const std::string & paramTitle) const
{
	vector<resqml20__AbstractActivityParameter*> params = getParameterFromTitle(paramTitle);

	if (params.size() < 1)
		throw invalid_argument("There exists no " + paramTitle + " parameter in this activity.");

	vector<int64_t> result;
	for (auto const* param : params) {
		if (param->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerQuantityParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non integer values.");
		else
			result.push_back(static_cast<resqml20__IntegerQuantityParameter const*>(param)->Value);
	}

	return result;
}

int64_t Activity::getIntegerQuantityParameterValue(uint64_t index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.at(index)->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerQuantityParameter)
		throw invalid_argument("The parameter at index is not an integer quantity parameter.");

	return static_cast<resqml20__IntegerQuantityParameter*>(activity->Parameter[index])->Value;
}

/*****************************
********** STRING ************
*****************************/
bool Activity::isAStringParameter(const std::string & paramTitle) const
{	
	vector<resqml20__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw invalid_argument("There exists no " + paramTitle + " parameter in this activity.");

	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__StringParameter)
			return false;
	}

	return true;
}

bool Activity::isAStringParameter(uint64_t index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	return activity->Parameter.at(index)->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__StringParameter;
}

vector<string> Activity::getStringParameterValue(const std::string & paramTitle) const
{
	vector<resqml20__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		invalid_argument("There exists no " + paramTitle + " parameter in this activity.");

	vector<string> result;
	for (size_t i = 0; i < param.size(); ++i) {
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__StringParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non string values.");
		else
			result.push_back(static_cast<resqml20__StringParameter*>(param[i])->Value);
	}

	return result;
}

std::string Activity::getStringParameterValue(uint64_t index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.at(index)->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__StringParameter)
		throw invalid_argument("The parameter at index is not a string parameter.");

	return static_cast<resqml20__StringParameter*>(activity->Parameter[index])->Value;
}

/*****************************
********** OBJECT ************
*****************************/
bool Activity::isAResqmlObjectParameter(const std::string & paramTitle) const
{
	vector<resqml20__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw invalid_argument("There exists no " + paramTitle + " parameter in this activity.");

	for (size_t i = 0; i < param.size(); ++i) {
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DataObjectParameter)
			return false;
	}

	return true;
}

bool Activity::isAResqmlObjectParameter(uint64_t index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	return activity->Parameter.at(index)->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DataObjectParameter;
}

vector<COMMON_NS::AbstractObject*> Activity::getResqmlObjectParameterValue(const std::string & paramTitle) const
{
	vector<resqml20__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		invalid_argument("There exists no " + paramTitle + " parameter in this activity.");

	vector<COMMON_NS::AbstractObject*> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DataObjectParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non RESQML object values.");
		else
			result.push_back(getRepository()->getDataObjectByUuid(static_cast<resqml20__DataObjectParameter*>(param[i])->DataObject->UUID));
	}

	return result;
}

COMMON_NS::AbstractObject* Activity::getResqmlObjectParameterValue(uint64_t index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.at(index)->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DataObjectParameter)
		throw invalid_argument("The parameter at index is not a RESQML object parameter.");

	return getRepository()->getDataObjectByUuid(static_cast<resqml20__DataObjectParameter*>(activity->Parameter[index])->DataObject->UUID);
}

void Activity::setActivityTemplate(EML2_NS::ActivityTemplate * activityTemplate)
{
	if (activityTemplate == nullptr) {
		return;
	}

	static_cast<_resqml20__Activity*>(gsoapProxy2_0_1)->ActivityDescriptor = activityTemplate->newResqmlReference();

	getRepository()->addRelationship(this, activityTemplate);
}

COMMON_NS::DataObjectReference Activity::getActivityTemplateDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<_resqml20__Activity*>(gsoapProxy2_0_1)->ActivityDescriptor);
}

std::string Activity::getXmlNamespaceVersion() const
{
	return "2.0.1";
}

void Activity::loadTargetRelationships()
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	// Activity template
	COMMON_NS::DataObjectReference dor = getActivityTemplateDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<EML2_NS::ActivityTemplate>(dor);
	}

	for (size_t i = 0; i < activity->Parameter.size(); ++i) {
		if (activity->Parameter[i]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DataObjectParameter) {
			convertDorIntoRel(COMMON_NS::DataObjectReference(static_cast<resqml20__DataObjectParameter*>(activity->Parameter[i])->DataObject));
		}
	}
}
