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
#include "ActivityTemplate.h"

using namespace std;
using namespace EML2_3_NS;
using namespace gsoap_eml2_3;

ActivityTemplate::ActivityTemplate(COMMON_NS::DataObjectRepository * repo, const string & guid, const string & title)
{
	gsoapProxy2_3 = soap_new_eml23__ActivityTemplate(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
}

void ActivityTemplate::pushBackParameter(const std::string & title,
	bool isInput, bool isOutput,
	uint64_t minOccurs, int64_t maxOccurs)
{
	// Preconditions
	if (maxOccurs >= 0 && minOccurs > static_cast<unsigned int>(maxOccurs)) {
		throw invalid_argument("Maximum occurences of a parameter template must be at least equal to the minimum occurences of this same parameter template.");
	}

	eml23__ActivityTemplate* activityTemplate = static_cast<eml23__ActivityTemplate*>(gsoapProxy2_3);

	eml23__ParameterTemplate* param = soap_new_eml23__ParameterTemplate(gsoapProxy2_3->soap);
	param->Title = title;
	param->IsInput = isInput;
	param->IsOutput = isOutput;
	param->MinOccurs = minOccurs;
	param->MaxOccurs = maxOccurs;

	activityTemplate->Parameter.push_back(param);
}

void ActivityTemplate::pushBackParameter(const std::string & title,
	gsoap_resqml2_0_1::resqml20__ParameterKind kind,
	bool isInput, bool isOutput,
	uint64_t minOccurs, int64_t maxOccurs)
{
	pushBackParameter(title, isInput, isOutput, minOccurs, maxOccurs);

	eml23__ActivityTemplate* activityTemplate = static_cast<eml23__ActivityTemplate*>(gsoapProxy2_3);
	activityTemplate->Parameter[activityTemplate->Parameter.size() - 1]->AllowedKind.push_back(static_cast<gsoap_eml2_3::eml23__ActivityParameterKind>(kind));
}

void ActivityTemplate::pushBackParameter(const std::string & title,
	bool isInput, bool isOutput,
	uint64_t minOccurs, int64_t maxOccurs,
	std::string resqmlObjectContentType)
{
	pushBackParameter(title, gsoap_resqml2_0_1::resqml20__ParameterKind::dataObject, isInput, isOutput, minOccurs, maxOccurs);

	if (!resqmlObjectContentType.empty())
	{
		eml23__ActivityTemplate* activityTemplate = static_cast<eml23__ActivityTemplate*>(gsoapProxy2_3);
		activityTemplate->Parameter[activityTemplate->Parameter.size() - 1]->DataObjectContentType = soap_new_std__string(gsoapProxy2_3->soap);
		activityTemplate->Parameter[activityTemplate->Parameter.size() - 1]->DataObjectContentType->assign(resqmlObjectContentType);
	}
}

bool ActivityTemplate::isAnExistingParameter(const std::string & paramTitle) const
{
	eml23__ActivityTemplate* activityTemplate = static_cast<eml23__ActivityTemplate*>(gsoapProxy2_3);

	for (auto const* param : activityTemplate->Parameter) {
		if (param->Title == paramTitle) {
			return true;
		}
	}

	return false;
}

uint64_t ActivityTemplate::getParameterCount() const
{
	return static_cast<eml23__ActivityTemplate*>(gsoapProxy2_3)->Parameter.size();
}

std::string ActivityTemplate::getParameterTitle(uint64_t index) const
{
	eml23__ActivityTemplate* activityTemplate = static_cast<eml23__ActivityTemplate*>(gsoapProxy2_3);
	return activityTemplate->Parameter.at(index)->Title;
}

vector<gsoap_resqml2_0_1::resqml20__ParameterKind> ActivityTemplate::getParameterAllowedKinds(uint64_t index) const
{
	eml23__ActivityTemplate* activityTemplate = static_cast<eml23__ActivityTemplate*>(gsoapProxy2_3);

	vector<gsoap_resqml2_0_1::resqml20__ParameterKind> result;
	for (auto& pk : activityTemplate->Parameter.at(index)->AllowedKind) {
		result.push_back(static_cast<gsoap_resqml2_0_1::resqml20__ParameterKind>(pk));
	}

	return result;
}

vector<gsoap_resqml2_0_1::resqml20__ParameterKind> ActivityTemplate::getParameterAllowedKinds(const std::string & paramTitle) const
{
	eml23__ParameterTemplate* param = getParameterFromTitle(paramTitle);

	if (param == nullptr)
		throw range_error("The parameter template title is not in the parameter template range.");

	vector<gsoap_resqml2_0_1::resqml20__ParameterKind> result;
	for (auto& pk : param->AllowedKind) {
		result.push_back(static_cast<gsoap_resqml2_0_1::resqml20__ParameterKind>(pk));
	}

	return result;
}

bool ActivityTemplate::getParameterIsInput(uint64_t index) const
{
	eml23__ActivityTemplate* activityTemplate = static_cast<eml23__ActivityTemplate*>(gsoapProxy2_3);
	return activityTemplate->Parameter.at(index)->IsInput;
}

bool ActivityTemplate::getParameterIsInput(const std::string & paramTitle) const
{
	eml23__ParameterTemplate* param = getParameterFromTitle(paramTitle);

	if (param == nullptr)
		throw invalid_argument("There exists no " + paramTitle + " parameter in this activity.");

	return param->IsInput;
}

bool ActivityTemplate::getParameterIsOutput(uint64_t index) const
{
	eml23__ActivityTemplate* activityTemplate = static_cast<eml23__ActivityTemplate*>(gsoapProxy2_3);
	return activityTemplate->Parameter.at(index)->IsOutput;
}

bool ActivityTemplate::getParameterIsOutput(const std::string & paramTitle) const
{
	eml23__ParameterTemplate* param = getParameterFromTitle(paramTitle);

	if (param == nullptr)
		throw invalid_argument("There exists no " + paramTitle + " parameter in this activity.");

	return param->IsOutput;
}

int64_t ActivityTemplate::getParameterMinOccurences(uint64_t index) const
{
	eml23__ActivityTemplate* activityTemplate = static_cast<eml23__ActivityTemplate*>(gsoapProxy2_3);

	return activityTemplate->Parameter.at(index)->MinOccurs;
}

int64_t ActivityTemplate::getParameterMinOccurences(const std::string & paramTitle) const
{
	eml23__ParameterTemplate* param = getParameterFromTitle(paramTitle);

	if (param == nullptr)
		throw invalid_argument("There exists no " + paramTitle + " parameter in this activity.");

	return param->MinOccurs;
}

int64_t ActivityTemplate::getParameterMaxOccurences(uint64_t index) const
{
	eml23__ActivityTemplate* activityTemplate = static_cast<eml23__ActivityTemplate*>(gsoapProxy2_3);
	return activityTemplate->Parameter.at(index)->MaxOccurs;
}

int64_t ActivityTemplate::getParameterMaxOccurences(const std::string & paramTitle) const
{
	eml23__ParameterTemplate* param = getParameterFromTitle(paramTitle);

	if (param == nullptr)
		throw invalid_argument("There exists no " + paramTitle + " parameter in this activity.");

	return param->MaxOccurs;
}

gsoap_eml2_3::eml23__ParameterTemplate* ActivityTemplate::getParameterFromTitle(const std::string & paramTitle) const
{
	eml23__ActivityTemplate* activityTemplate = static_cast<eml23__ActivityTemplate*>(gsoapProxy2_3);

	eml23__ParameterTemplate* param = nullptr;
	for (size_t i = 0; i < activityTemplate->Parameter.size(); ++i) {
		if (activityTemplate->Parameter[i]->Title == paramTitle) {
			param = activityTemplate->Parameter[i];
			break;
		}
	}

	return param;
}
