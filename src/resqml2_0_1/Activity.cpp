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

#include "ActivityTemplate.h"
#include "StringTableLookup.h"

#include <algorithm>
#include <stdexcept>

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

Activity::Activity(RESQML2_NS::ActivityTemplate* activityTemplate, const string & guid, const string & title)
{
	if (activityTemplate == nullptr) {
		throw invalid_argument("The activity template of an activity must be not null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREActivity(activityTemplate->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setActivityTemplate(activityTemplate);
}

void Activity::pushBackParameter(const std::string title,
			const double & value, const resqml20__ResqmlUom & uom)
{
	RESQML2_NS::ActivityTemplate* activityTemplate = getActivityTemplate();
	if (activityTemplate->isAnExistingParameter(title) == false)
		throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
	LONG64 maxOccurs = activityTemplate->getParameterMaxOccurences(title);
	if (maxOccurs > -1 && maxOccurs <= getParameterCount(title))
		throw invalid_argument("The max number of occurences has already been reached for parameter " + title);
	if (dynamic_cast<RESQML2_0_1_NS::ActivityTemplate*>(activityTemplate) != nullptr)
	{
		vector<resqml20__ParameterKind> allowedKinds = static_cast<RESQML2_0_1_NS::ActivityTemplate*>(activityTemplate)->getParameterAllowedKinds(title);
		if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), resqml20__ParameterKind__floatingPoint) == allowedKinds.end())
			throw invalid_argument("The parameter template " + title + " does not allow a double datatype.");
	}

	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	resqml20__FloatingPointQuantityParameter* fpqp = soap_new_resqml20__FloatingPointQuantityParameter(activity->soap);
	fpqp->Title = title;
	fpqp->Value = value;
	fpqp->Uom = uom;
	activity->Parameter.push_back(fpqp);
}

void Activity::pushBackParameter(const std::string title, const std::string & value)
{
	RESQML2_NS::ActivityTemplate* activityTemplate = getActivityTemplate();
	if (activityTemplate->isAnExistingParameter(title) == false)
		throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
	LONG64 maxOccurs = activityTemplate->getParameterMaxOccurences(title);
	if (maxOccurs > -1 && maxOccurs <= getParameterCount(title))
		throw invalid_argument("The max number of occurences has already been reached for parameter " + title);
	if (dynamic_cast<RESQML2_0_1_NS::ActivityTemplate*>(activityTemplate) != nullptr)
	{
		vector<resqml20__ParameterKind> allowedKinds = static_cast<RESQML2_0_1_NS::ActivityTemplate*>(activityTemplate)->getParameterAllowedKinds(title);
		if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), resqml20__ParameterKind__string) == allowedKinds.end())
			throw invalid_argument("The parameter template " + title + " does not allow a string datatype.");
	}

	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	resqml20__StringParameter* sp = soap_new_resqml20__StringParameter(activity->soap);
	sp->Title = title;
	sp->Value = value;
	activity->Parameter.push_back(sp);
}

void Activity::pushBackParameter(const std::string title, const LONG64 & value)
{
	RESQML2_NS::ActivityTemplate* activityTemplate = getActivityTemplate();
	if (activityTemplate->isAnExistingParameter(title) == false)
		throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
	LONG64 maxOccurs = activityTemplate->getParameterMaxOccurences(title);
	if (maxOccurs > -1 && maxOccurs <= getParameterCount(title))
		throw invalid_argument("The max number of occurences has already been reached for parameter " + title);
	if (dynamic_cast<RESQML2_0_1_NS::ActivityTemplate*>(activityTemplate) != nullptr)
	{
		vector<resqml20__ParameterKind> allowedKinds = static_cast<RESQML2_0_1_NS::ActivityTemplate*>(activityTemplate)->getParameterAllowedKinds(title);
		if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), resqml20__ParameterKind__integer) == allowedKinds.end())
			throw invalid_argument("The parameter template " + title + " does not allow an integer datatype.");
	}

	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	resqml20__IntegerQuantityParameter* iqp = soap_new_resqml20__IntegerQuantityParameter(activity->soap);
	iqp->Title = title;
	iqp->Value = value;
	activity->Parameter.push_back(iqp);
}

void Activity::pushBackParameter(const std::string title, AbstractObject* resqmlObject)
{
	if (resqmlObject == nullptr)
		throw invalid_argument("The resqml object must be non null.");
	RESQML2_NS::ActivityTemplate* activityTemplate = getActivityTemplate();
	if (activityTemplate->isAnExistingParameter(title) == false)
		throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
	LONG64 maxOccurs = activityTemplate->getParameterMaxOccurences(title);
	if (maxOccurs > -1 && maxOccurs <= getParameterCount(title))
		throw invalid_argument("The max number of occurences has already been reached for parameter " + title);
	if (dynamic_cast<RESQML2_0_1_NS::ActivityTemplate*>(activityTemplate) != nullptr)
	{
		vector<resqml20__ParameterKind> allowedKinds = static_cast<RESQML2_0_1_NS::ActivityTemplate*>(activityTemplate)->getParameterAllowedKinds(title);
		if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), resqml20__ParameterKind__dataObject) == allowedKinds.end())
			throw invalid_argument("The parameter template " + title + " does not allow a data object datatype.");
	}

	getRepository()->addRelationship(this, resqmlObject);

	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	resqml20__DataObjectParameter* dop = soap_new_resqml20__DataObjectParameter(activity->soap);
	dop->Title = title;
	dop->DataObject = resqmlObject->newResqmlReference();
	activity->Parameter.push_back(dop);
}

unsigned int Activity::getParameterCount() const
{
	return static_cast<_resqml20__Activity*>(gsoapProxy2_0_1)->Parameter.size();
}

unsigned int Activity::getParameterCount(const std::string & paramTitle) const
{
	return getParameterFromTitle(paramTitle).size();
}

const std::string & Activity::getParameterTitle(const unsigned int & index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->Title;
}

std::vector<unsigned int> Activity::getParameterIndexOfTitle(const std::string & paramTitle) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

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

std::vector<resqml20__AbstractActivityParameter*> Activity::getParameterFromTitle(const std::string & paramTitle) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	std::vector<resqml20__AbstractActivityParameter*> params;
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
	vector<resqml20__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__FloatingPointQuantityParameter)
			return false;
	}

	return true;
}

bool Activity::isAFloatingPointQuantityParameter(const unsigned int & index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__FloatingPointQuantityParameter;
}

vector<double> Activity::getFloatingPointQuantityParameterValue(const std::string & paramTitle) const
{
	vector<resqml20__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	vector<double> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__FloatingPointQuantityParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non double values.");
		else
			result.push_back(static_cast<resqml20__FloatingPointQuantityParameter*>(param[i])->Value);
	}

	return result;
}

double Activity::getFloatingPointQuantityParameterValue(const unsigned int & index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__FloatingPointQuantityParameter)
		throw invalid_argument("The parameter index is not in the parameter range.");

	return static_cast<resqml20__FloatingPointQuantityParameter*>(activity->Parameter[index])->Value;
}

vector<resqml20__ResqmlUom> Activity::getFloatingPointQuantityParameterUom(const std::string & paramTitle) const
{
	vector<resqml20__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	vector<resqml20__ResqmlUom> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__FloatingPointQuantityParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non double values.");
		else
			result.push_back(static_cast<resqml20__FloatingPointQuantityParameter*>(param[i])->Uom);
	}

	return result;
}

gsoap_resqml2_0_1::resqml20__ResqmlUom Activity::getFloatingPointQuantityParameterUom(const unsigned int & index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__FloatingPointQuantityParameter)
		throw invalid_argument("The parameter index is not in the parameter range.");

	return static_cast<resqml20__FloatingPointQuantityParameter*>(activity->Parameter[index])->Uom;
}

/*****************************
********** INTEGER ***********
*****************************/
bool Activity::isAnIntegerQuantityParameter(const std::string & paramTitle) const
{
	vector<resqml20__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerQuantityParameter)
			return false;
	}

	return true;
}

bool Activity::isAnIntegerQuantityParameter(const unsigned int & index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerQuantityParameter;
}

vector<LONG64> Activity::getIntegerQuantityParameterValue(const std::string & paramTitle) const
{
	vector<resqml20__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	vector<LONG64> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerQuantityParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non double values.");
		else
			result.push_back(static_cast<resqml20__IntegerQuantityParameter*>(param[i])->Value);
	}

	return result;
}

LONG64 Activity::getIntegerQuantityParameterValue(const unsigned int & index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerQuantityParameter)
		throw invalid_argument("The parameter index is not in the parameter range.");

	return static_cast<resqml20__IntegerQuantityParameter*>(activity->Parameter[index])->Value;
}

/*****************************
********** STRING ************
*****************************/
bool Activity::isAStringParameter(const std::string & paramTitle) const
{	
	vector<resqml20__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__StringParameter)
			return false;
	}

	return true;
}

bool Activity::isAStringParameter(const unsigned int & index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__StringParameter;
}

vector<string> Activity::getStringParameterValue(const std::string & paramTitle) const
{
	vector<resqml20__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	vector<string> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__StringParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non double values.");
		else
			result.push_back(static_cast<resqml20__StringParameter*>(param[i])->Value);
	}

	return result;
}

const std::string & Activity::getStringParameterValue(const unsigned int & index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__StringParameter)
		throw invalid_argument("The parameter index is not in the parameter range.");

	return static_cast<resqml20__StringParameter*>(activity->Parameter[index])->Value;
}

/*****************************
********** OBJECT ************
*****************************/
bool Activity::isAResqmlObjectParameter(const std::string & paramTitle) const
{
	vector<resqml20__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DataObjectParameter)
			return false;
	}

	return true;
}

bool Activity::isAResqmlObjectParameter(const unsigned int & index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DataObjectParameter;
}

vector<COMMON_NS::AbstractObject*> Activity::getResqmlObjectParameterValue(const std::string & paramTitle) const
{
	vector<resqml20__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	vector<COMMON_NS::AbstractObject*> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DataObjectParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non double values.");
		else
			result.push_back(getRepository()->getDataObjectByUuid(static_cast<resqml20__DataObjectParameter*>(param[i])->DataObject->UUID));
	}

	return result;
}

COMMON_NS::AbstractObject* Activity::getResqmlObjectParameterValue(const unsigned int & index) const
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DataObjectParameter)
		throw invalid_argument("The parameter index is not in the parameter range.");

	return getRepository()->getDataObjectByUuid(static_cast<resqml20__DataObjectParameter*>(activity->Parameter[index])->DataObject->UUID);
}

void Activity::setActivityTemplate(RESQML2_NS::ActivityTemplate * activityTemplate)
{
	if (activityTemplate == nullptr) {
		return;
	}
	if (getRepository() == nullptr) {
		activityTemplate->getRepository()->addOrReplaceDataObject(this);
	}

	getRepository()->addRelationship(this, activityTemplate);

	static_cast<_resqml20__Activity*>(gsoapProxy2_0_1)->ActivityDescriptor = activityTemplate->newResqmlReference();
}

gsoap_resqml2_0_1::eml20__DataObjectReference* Activity::getActivityTemplateDor() const
{
	return static_cast<_resqml20__Activity*>(gsoapProxy2_0_1)->ActivityDescriptor;
}

std::string Activity::getXmlNamespaceVersion() const
{
	return "2.0.1";
}

void Activity::loadTargetRelationships()
{
	_resqml20__Activity* activity = static_cast<_resqml20__Activity*>(gsoapProxy2_0_1);

	// Activity template
	if (activity->ActivityDescriptor != nullptr) {
		convertDorIntoRel<ActivityTemplate>(activity->ActivityDescriptor);
	}

	for (size_t i = 0; i < activity->Parameter.size(); ++i) {
		if (activity->Parameter[i]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DataObjectParameter) {
			convertDorIntoRel(static_cast<resqml20__DataObjectParameter*>(activity->Parameter[i])->DataObject);
		}
	}
}
