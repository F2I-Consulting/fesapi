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
#include <stdexcept>

using namespace std;
using namespace EML2_3_NS;
using namespace gsoap_eml2_3;

const char* Activity::XML_NS = "eml23";

Activity::Activity(EML2_NS::ActivityTemplate* activityTemplate, const string & guid, const string & title)
{
	if (activityTemplate == nullptr) {
		throw invalid_argument("The activity template of an activity must be not null.");
	}

	gsoapProxy2_3 = soap_new_eml23__Activity(activityTemplate->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setActivityTemplate(activityTemplate);
}

void Activity::pushBackParameter(const std::string title, double value, gsoap_resqml2_0_1::resqml20__ResqmlUom uom)
{
	EML2_NS::ActivityTemplate* activityTemplate = getActivityTemplate();
	if (!activityTemplate->isAnExistingParameter(title))
		throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
	LONG64 maxOccurs = activityTemplate->getParameterMaxOccurences(title);
	if (maxOccurs > -1 && maxOccurs <= getParameterCount(title))
		throw invalid_argument("The max number of occurrences has already been reached for parameter " + title);
	if (dynamic_cast<EML2_NS::ActivityTemplate*>(activityTemplate) != nullptr)
	{
		vector<gsoap_resqml2_0_1::resqml20__ParameterKind> allowedKinds = static_cast<EML2_NS::ActivityTemplate*>(activityTemplate)->getParameterAllowedKinds(title);
		if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), gsoap_resqml2_0_1::resqml20__ParameterKind__floatingPoint) == allowedKinds.end())
			throw invalid_argument("The parameter template " + title + " does not allow a double datatype.");
	}

	_eml23__Activity* activity = static_cast<_eml23__Activity*>(gsoapProxy2_3);

	eml23__DoubleQuantityParameter* fpqp = soap_new_eml23__DoubleQuantityParameter(activity->soap);
	fpqp->Title = title;
	fpqp->Value = value;
	fpqp->Uom = uom;
	activity->Parameter.push_back(fpqp);
}

void Activity::pushBackParameter(const std::string title, const std::string & value)
{
	EML2_NS::ActivityTemplate* activityTemplate = getActivityTemplate();
	if (activityTemplate->isAnExistingParameter(title) == false)
		throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
	LONG64 maxOccurs = activityTemplate->getParameterMaxOccurences(title);
	if (maxOccurs > -1 && maxOccurs <= getParameterCount(title))
		throw invalid_argument("The max number of occurrences has already been reached for parameter " + title);
	if (dynamic_cast<EML2_NS::ActivityTemplate*>(activityTemplate) != nullptr)
	{
		vector<gsoap_resqml2_0_1::resqml20__ParameterKind> allowedKinds = static_cast<EML2_NS::ActivityTemplate*>(activityTemplate)->getParameterAllowedKinds(title);
		if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), gsoap_resqml2_0_1::resqml20__ParameterKind__string) == allowedKinds.end())
			throw invalid_argument("The parameter template " + title + " does not allow a string datatype.");
	}

	_eml23__Activity* activity = static_cast<_eml23__Activity*>(gsoapProxy2_3);

	eml23__StringParameter* sp = soap_new_eml23__StringParameter(activity->soap);
	sp->Title = title;
	sp->Value = value;
	activity->Parameter.push_back(sp);
}

void Activity::pushBackParameter(const std::string title, LONG64 value)
{
	EML2_NS::ActivityTemplate* activityTemplate = getActivityTemplate();
	if (activityTemplate->isAnExistingParameter(title) == false)
		throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
	LONG64 maxOccurs = activityTemplate->getParameterMaxOccurences(title);
	if (maxOccurs > -1 && maxOccurs <= getParameterCount(title))
		throw invalid_argument("The max number of occurrences has already been reached for parameter " + title);
	if (dynamic_cast<EML2_NS::ActivityTemplate*>(activityTemplate) != nullptr)
	{
		vector<gsoap_resqml2_0_1::resqml20__ParameterKind> allowedKinds = static_cast<EML2_NS::ActivityTemplate*>(activityTemplate)->getParameterAllowedKinds(title);
		if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), gsoap_resqml2_0_1::resqml20__ParameterKind__integer) == allowedKinds.end())
			throw invalid_argument("The parameter template " + title + " does not allow an integer datatype.");
	}

	_eml23__Activity* activity = static_cast<_eml23__Activity*>(gsoapProxy2_3);

	eml23__IntegerQuantityParameter* iqp = soap_new_eml23__IntegerQuantityParameter(activity->soap);
	iqp->Title = title;
	iqp->Value = value;
	activity->Parameter.push_back(iqp);
}

void Activity::pushBackParameter(const std::string title, AbstractObject* resqmlObject)
{
	if (resqmlObject == nullptr)
		throw invalid_argument("The resqml object must be non null.");
	EML2_NS::ActivityTemplate* activityTemplate = getActivityTemplate();
	if (activityTemplate->isAnExistingParameter(title) == false)
		throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
	LONG64 maxOccurs = activityTemplate->getParameterMaxOccurences(title);
	if (maxOccurs > -1 && maxOccurs <= getParameterCount(title))
		throw invalid_argument("The max number of occurrences has already been reached for parameter " + title);
	if (dynamic_cast<EML2_NS::ActivityTemplate*>(activityTemplate) != nullptr)
	{
		vector<gsoap_resqml2_0_1::resqml20__ParameterKind> allowedKinds = static_cast<EML2_NS::ActivityTemplate*>(activityTemplate)->getParameterAllowedKinds(title);
		if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), gsoap_resqml2_0_1::resqml20__ParameterKind__dataObject) == allowedKinds.end())
			throw invalid_argument("The parameter template " + title + " does not allow a data object datatype.");
	}

	getRepository()->addRelationship(this, resqmlObject);

	_eml23__Activity* activity = static_cast<_eml23__Activity*>(gsoapProxy2_3);

	eml23__DataObjectParameter* dop = soap_new_eml23__DataObjectParameter(activity->soap);
	dop->Title = title;
	dop->DataObject = resqmlObject->newEml23Reference();
	activity->Parameter.push_back(dop);
}

unsigned int Activity::getParameterCount() const
{
	return static_cast<_eml23__Activity*>(gsoapProxy2_3)->Parameter.size();
}

unsigned int Activity::getParameterCount(const std::string & paramTitle) const
{
	return getParameterFromTitle(paramTitle).size();
}

const std::string & Activity::getParameterTitle(unsigned int index) const
{
	_eml23__Activity* activity = static_cast<_eml23__Activity*>(gsoapProxy2_3);

	if (activity->Parameter.size() <= index)
		throw out_of_range("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->Title;
}

std::vector<unsigned int> Activity::getParameterIndexOfTitle(const std::string & paramTitle) const
{
	_eml23__Activity* activity = static_cast<_eml23__Activity*>(gsoapProxy2_3);

	vector<unsigned int> paramIndex;
	for (unsigned int i = 0; i < activity->Parameter.size(); ++i)
	{
		if (activity->Parameter[i]->Title == paramTitle)
		{
			paramIndex.push_back(i);
		}
	}

	return paramIndex;
}

std::vector<gsoap_eml2_3::eml23__AbstractActivityParameter*> Activity::getParameterFromTitle(const std::string & paramTitle) const
{
	_eml23__Activity* activity = static_cast<_eml23__Activity*>(gsoapProxy2_3);

	std::vector<gsoap_eml2_3::eml23__AbstractActivityParameter*> params;
	for (unsigned int i = 0; i < activity->Parameter.size(); ++i)
	{
		if (activity->Parameter[i]->Title == paramTitle)
		{
			params.push_back(activity->Parameter[i]);
		}
	}

	return params;
}

/*****************************
********** DOUBLE ************
*****************************/
bool Activity::isAFloatingPointQuantityParameter(const std::string & paramTitle) const
{
	std::vector<gsoap_eml2_3::eml23__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw invalid_argument("There exists no " + paramTitle + " parameter in this activity.");

	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__DoubleQuantityParameter)
			return false;
	}

	return true;
}

bool Activity::isAFloatingPointQuantityParameter(unsigned int index) const
{
	_eml23__Activity* activity = static_cast<_eml23__Activity*>(gsoapProxy2_3);

	if (activity->Parameter.size() <= index)
		throw out_of_range("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__DoubleQuantityParameter;
}

vector<double> Activity::getFloatingPointQuantityParameterValue(const std::string & paramTitle) const
{
	std::vector<gsoap_eml2_3::eml23__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw invalid_argument("There exists no " + paramTitle + " parameter in this activity.");

	vector<double> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__DoubleQuantityParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non double values.");
		else
			result.push_back(static_cast<eml23__DoubleQuantityParameter*>(param[i])->Value);
	}

	return result;
}

double Activity::getFloatingPointQuantityParameterValue(unsigned int index) const
{
	_eml23__Activity* activity = static_cast<_eml23__Activity*>(gsoapProxy2_3);

	if (activity->Parameter.size() <= index)
		throw out_of_range("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__DoubleQuantityParameter)
		throw invalid_argument("The parameter at index is not a floating point quantity parameter.");

	return static_cast<eml23__DoubleQuantityParameter*>(activity->Parameter[index])->Value;
}

vector<gsoap_resqml2_0_1::resqml20__ResqmlUom> Activity::getFloatingPointQuantityParameterUom(const std::string & paramTitle) const
{
	std::vector<gsoap_eml2_3::eml23__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	vector<gsoap_resqml2_0_1::resqml20__ResqmlUom> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__DoubleQuantityParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non double values.");
		
		gsoap_resqml2_0_1::resqml20__ResqmlUom uom;
		gsoap_resqml2_0_1::soap_s2resqml20__ResqmlUom(gsoapProxy2_3->soap, static_cast<eml23__DoubleQuantityParameter*>(param[i])->Uom.c_str(), &uom);
		result.push_back(uom);
	}

	return result;
}

gsoap_resqml2_0_1::resqml20__ResqmlUom Activity::getFloatingPointQuantityParameterUom(unsigned int index) const
{
	_eml23__Activity* activity = static_cast<_eml23__Activity*>(gsoapProxy2_3);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__DoubleQuantityParameter)
		throw invalid_argument("The parameter index is not in the parameter range.");

	gsoap_resqml2_0_1::resqml20__ResqmlUom uom;
	gsoap_resqml2_0_1::soap_s2resqml20__ResqmlUom(gsoapProxy2_3->soap, static_cast<eml23__DoubleQuantityParameter*>(activity->Parameter[index])->Uom.c_str(), &uom);
	return uom;
}

/*****************************
********** INTEGER ***********
*****************************/
bool Activity::isAnIntegerQuantityParameter(const std::string & paramTitle) const
{
	vector<gsoap_eml2_3::eml23__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw invalid_argument("There exists no " + paramTitle + " parameter in this activity.");

	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__IntegerQuantityParameter)
			return false;
	}

	return true;
}

bool Activity::isAnIntegerQuantityParameter(unsigned int index) const
{
	_eml23__Activity* activity = static_cast<_eml23__Activity*>(gsoapProxy2_3);

	if (activity->Parameter.size() <= index)
		throw out_of_range("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerQuantityParameter;
}

vector<LONG64> Activity::getIntegerQuantityParameterValue(const std::string & paramTitle) const
{
	vector<gsoap_eml2_3::eml23__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw invalid_argument("There exists no " + paramTitle + " parameter in this activity.");

	vector<LONG64> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__IntegerQuantityParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non integer values.");
		else
			result.push_back(static_cast<eml23__IntegerQuantityParameter*>(param[i])->Value);
	}

	return result;
}

LONG64 Activity::getIntegerQuantityParameterValue(unsigned int index) const
{
	_eml23__Activity* activity = static_cast<_eml23__Activity*>(gsoapProxy2_3);

	if (activity->Parameter.size() <= index)
		throw out_of_range("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__IntegerQuantityParameter)
		throw invalid_argument("The parameter at index is not an integer quantity parameter.");

	return static_cast<eml23__IntegerQuantityParameter*>(activity->Parameter[index])->Value;
}

/*****************************
********** STRING ************
*****************************/
bool Activity::isAStringParameter(const std::string & paramTitle) const
{
	vector<gsoap_eml2_3::eml23__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw invalid_argument("There exists no " + paramTitle + " parameter in this activity.");

	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__StringParameter)
			return false;
	}

	return true;
}

bool Activity::isAStringParameter(unsigned int index) const
{
	_eml23__Activity* activity = static_cast<_eml23__Activity*>(gsoapProxy2_3);

	if (activity->Parameter.size() <= index)
		throw out_of_range("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__StringParameter;
}

vector<string> Activity::getStringParameterValue(const std::string & paramTitle) const
{
	vector<gsoap_eml2_3::eml23__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		invalid_argument("There exists no " + paramTitle + " parameter in this activity.");

	vector<string> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__StringParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non string values.");
		else
			result.push_back(static_cast<eml23__StringParameter*>(param[i])->Value);
	}

	return result;
}

const std::string & Activity::getStringParameterValue(unsigned int index) const
{
	_eml23__Activity* activity = static_cast<_eml23__Activity*>(gsoapProxy2_3);

	if (activity->Parameter.size() <= index)
		throw out_of_range("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__StringParameter)
		throw invalid_argument("The parameter at index is not a string parameter.");

	return static_cast<eml23__StringParameter*>(activity->Parameter[index])->Value;
}

/*****************************
********** OBJECT ************
*****************************/
bool Activity::isAResqmlObjectParameter(const std::string & paramTitle) const
{
	vector<gsoap_eml2_3::eml23__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1) {
		throw invalid_argument("There exists no " + paramTitle + " parameter in this activity.");
	}

	for (unsigned int i = 0; i < param.size(); ++i) {
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__DataObjectParameter)
			return false;
	}

	return true;
}

bool Activity::isAResqmlObjectParameter(unsigned int index) const
{
	_eml23__Activity* activity = static_cast<_eml23__Activity*>(gsoapProxy2_3);

	if (activity->Parameter.size() <= index)
		throw out_of_range("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__DataObjectParameter;
}

vector<COMMON_NS::AbstractObject*> Activity::getResqmlObjectParameterValue(const std::string & paramTitle) const
{
	vector<gsoap_eml2_3::eml23__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		invalid_argument("There exists no " + paramTitle + " parameter in this activity.");

	vector<COMMON_NS::AbstractObject*> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__DataObjectParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non RESQML object values.");
		else
			result.push_back(getRepository()->getDataObjectByUuid(static_cast<eml23__DataObjectParameter*>(param[i])->DataObject->Uuid));
	}

	return result;
}

COMMON_NS::AbstractObject* Activity::getResqmlObjectParameterValue(unsigned int index) const
{
	_eml23__Activity* activity = static_cast<_eml23__Activity*>(gsoapProxy2_3);

	if (activity->Parameter.size() <= index)
		throw out_of_range("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__DataObjectParameter)
		throw invalid_argument("The parameter at index is not a RESQML object parameter.");

	return getRepository()->getDataObjectByUuid(static_cast<eml23__DataObjectParameter*>(activity->Parameter[index])->DataObject->Uuid);
}

void Activity::setActivityTemplate(EML2_NS::ActivityTemplate * activityTemplate)
{
	if (activityTemplate == nullptr) {
		return;
	}
	if (getRepository() == nullptr) {
		activityTemplate->getRepository()->addOrReplaceDataObject(this);
	}

	getRepository()->addRelationship(this, activityTemplate);

	static_cast<_eml23__Activity*>(gsoapProxy2_3)->ActivityDescriptor = activityTemplate->newEml23Reference();
}

COMMON_NS::DataObjectReference Activity::getActivityTemplateDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<_eml23__Activity*>(gsoapProxy2_3)->ActivityDescriptor);
}

void Activity::loadTargetRelationships()
{
	_eml23__Activity* activity = static_cast<_eml23__Activity*>(gsoapProxy2_3);

	// Activity template
	COMMON_NS::DataObjectReference dor = getActivityTemplateDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<EML2_NS::ActivityTemplate>(dor);
	}

	for (size_t i = 0; i < activity->Parameter.size(); ++i) {
		if (activity->Parameter[i]->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__DataObjectParameter) {
			convertDorIntoRel(COMMON_NS::DataObjectReference(static_cast<eml23__DataObjectParameter*>(activity->Parameter[i])->DataObject));
		}
	}
}
