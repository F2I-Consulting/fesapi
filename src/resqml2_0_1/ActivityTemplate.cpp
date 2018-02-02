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
#include "resqml2_0_1/ActivityTemplate.h"

#include <stdexcept>

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* ActivityTemplate::XML_TAG = "ActivityTemplate";

ActivityTemplate::ActivityTemplate(soap* soapContext, const string & guid, const string & title)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREActivityTemplate(soapContext, 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

void ActivityTemplate::pushBackParameter(const std::string title,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const int & maxOccurs)
{
	// Preconditions
	if (minOccurs > maxOccurs)
		throw invalid_argument("Maximum occurences of a parameter template must be at least equal to the minimum occurences of this same parameter template.");

	_resqml2__ActivityTemplate* activityTemplate = static_cast<_resqml2__ActivityTemplate*>(gsoapProxy2_0_1);

	resqml2__ParameterTemplate* param =soap_new_resqml2__ParameterTemplate(gsoapProxy2_0_1->soap, 1);
	param->Title = title;
	param->IsInput = isInput;
	param->IsOutput = isOutput;
	param->MinOccurs = minOccurs;
	param->MaxOccurs = maxOccurs;

	activityTemplate->Parameter.push_back(param);
}

void ActivityTemplate::pushBackParameter(const std::string title,
			const resqml2__ParameterKind & kind,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const int & maxOccurs)
{
	pushBackParameter(title, isInput, isOutput, minOccurs, maxOccurs);

	_resqml2__ActivityTemplate* activityTemplate = static_cast<_resqml2__ActivityTemplate*>(gsoapProxy2_0_1);
	activityTemplate->Parameter[activityTemplate->Parameter.size()-1]->AllowedKind.push_back(kind);
}

void ActivityTemplate::pushBackParameter(const std::string title,
	const bool & isInput, const bool isOutput,
	const unsigned int & minOccurs, const int & maxOccurs,
	const std::string & resqmlObjectContentType)
{
	pushBackParameter(title, resqml2__ParameterKind__dataObject, isInput, isOutput, minOccurs, maxOccurs);

	if (resqmlObjectContentType.size() > 0)
	{
		_resqml2__ActivityTemplate* activityTemplate = static_cast<_resqml2__ActivityTemplate*>(gsoapProxy2_0_1);
		activityTemplate->Parameter[activityTemplate->Parameter.size()-1]->DataObjectContentType = soap_new_std__string(gsoapProxy2_0_1->soap, 1);
		activityTemplate->Parameter[activityTemplate->Parameter.size()-1]->DataObjectContentType->assign(resqmlObjectContentType);
	}
}

bool ActivityTemplate::isAnExistingParameter(const std::string & paramTitle) const
{
	_resqml2__ActivityTemplate* activityTemplate = static_cast<_resqml2__ActivityTemplate*>(gsoapProxy2_0_1);

	for (unsigned int i = 0; i < activityTemplate->Parameter.size(); ++i)
	{
		if (activityTemplate->Parameter[i]->Title == paramTitle)
			return true;
	}

	return false;
}

const unsigned int ActivityTemplate::getParameterCount() const
{
	return static_cast<_resqml2__ActivityTemplate*>(gsoapProxy2_0_1)->Parameter.size();
}

const std::string & ActivityTemplate::getParameterTitle(const unsigned int & index) const
{
	_resqml2__ActivityTemplate* activityTemplate = static_cast<_resqml2__ActivityTemplate*>(gsoapProxy2_0_1);

	if (activityTemplate->Parameter.size() <= index)
		throw range_error("The parameter template index is not in the parameter range.");

	return activityTemplate->Parameter[index]->Title;
}

const vector<resqml2__ParameterKind> & ActivityTemplate::getParameterAllowedKinds(const unsigned int & index) const
{
	_resqml2__ActivityTemplate* activityTemplate = static_cast<_resqml2__ActivityTemplate*>(gsoapProxy2_0_1);

	if (activityTemplate->Parameter.size() <= index)
		throw range_error("The parameter template index is not in the parameter range.");

	return activityTemplate->Parameter[index]->AllowedKind;
}

const vector<resqml2__ParameterKind> & ActivityTemplate::getParameterAllowedKinds(const std::string & paramTitle) const
{
	resqml2__ParameterTemplate* param = getParameterFromTitle(paramTitle);

	if (param == nullptr)
		throw range_error("The parameter template title is not in the parameter template range.");

	return param->AllowedKind;
}

const bool & ActivityTemplate::getParameterIsInput(const unsigned int & index) const
{
	_resqml2__ActivityTemplate* activityTemplate = static_cast<_resqml2__ActivityTemplate*>(gsoapProxy2_0_1);

	if (activityTemplate->Parameter.size() <= index)
		throw range_error("The parameter template index is not in the parameter range.");

	return activityTemplate->Parameter[index]->IsInput;
}

const bool & ActivityTemplate::getParameterIsInput(const std::string & paramTitle) const
{
	resqml2__ParameterTemplate* param = getParameterFromTitle(paramTitle);

	if (param == nullptr)
		throw range_error("The parameter template title is not in the parameter template range.");

	return param->IsInput;
}

const bool & ActivityTemplate::getParameterIsOutput(const unsigned int & index) const
{
	_resqml2__ActivityTemplate* activityTemplate = static_cast<_resqml2__ActivityTemplate*>(gsoapProxy2_0_1);

	if (activityTemplate->Parameter.size() <= index)
		throw range_error("The parameter template index is not in the parameter range.");

	return activityTemplate->Parameter[index]->IsOutput;
}

const bool & ActivityTemplate::getParameterIsOutput(const std::string & paramTitle) const
{
	resqml2__ParameterTemplate* param = getParameterFromTitle(paramTitle);

	if (param == nullptr)
		throw range_error("The parameter template title is not in the parameter template range.");

	return param->IsOutput;
}

const LONG64 ActivityTemplate::getParameterMinOccurences(const unsigned int & index) const
{
	_resqml2__ActivityTemplate* activityTemplate = static_cast<_resqml2__ActivityTemplate*>(gsoapProxy2_0_1);

	if (activityTemplate->Parameter.size() <= index)
		throw range_error("The parameter template index is not in the parameter range.");

	return activityTemplate->Parameter[index]->MinOccurs;
}

const LONG64 ActivityTemplate::getParameterMinOccurences(const std::string & paramTitle) const
{
	resqml2__ParameterTemplate* param = getParameterFromTitle(paramTitle);

	if (param == nullptr)
		throw range_error("The parameter template title is not in the parameter template range.");

	return param->MinOccurs;
}

const LONG64 ActivityTemplate::getParameterMaxOccurences(const unsigned int & index) const
{
	_resqml2__ActivityTemplate* activityTemplate = static_cast<_resqml2__ActivityTemplate*>(gsoapProxy2_0_1);

	if (activityTemplate->Parameter.size() <= index)
		throw range_error("The parameter template index is not in the parameter range.");

	return activityTemplate->Parameter[index]->MaxOccurs;
}

const LONG64 ActivityTemplate::getParameterMaxOccurences(const std::string & paramTitle) const
{
	resqml2__ParameterTemplate* param = getParameterFromTitle(paramTitle);

	if (param == nullptr)
		throw range_error("The parameter template title is not in the parameter template range.");

	return param->MaxOccurs;
}

std::string ActivityTemplate::getResqmlVersion() const
{
	return "2.0.1";
}

resqml2__ParameterTemplate* ActivityTemplate::getParameterFromTitle(const std::string & paramTitle) const
{
	_resqml2__ActivityTemplate* activityTemplate = static_cast<_resqml2__ActivityTemplate*>(gsoapProxy2_0_1);

	resqml2__ParameterTemplate* param = nullptr;
	for (unsigned int i = 0; i < activityTemplate->Parameter.size(); ++i)
	{
		if (activityTemplate->Parameter[i]->Title == paramTitle)
		{
			param = activityTemplate->Parameter[i];
			break;
		}
	}

	return param;
}

vector<Relationship> ActivityTemplate::getAllEpcRelationships() const
{
	vector<Relationship> result;

	for (unsigned int i = 0; i < activityInstanceSet.size(); ++i)
	{
		Relationship rel(activityInstanceSet[i]->getPartNameInEpcDocument(), "", activityInstanceSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

