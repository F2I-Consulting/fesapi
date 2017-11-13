/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
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
