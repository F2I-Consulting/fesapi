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
#include "resqml2_0_1/Activity.h"

#include "resqml2_0_1/ActivityTemplate.h"

#include <algorithm>
#include <stdexcept>

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

Activity::Activity(resqml2::ActivityTemplate* activityTemplate, const string & guid, const string & title)
{
	if (activityTemplate == nullptr)
		throw invalid_argument("The activity template of an activity must be not null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREActivity(activityTemplate->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	setActivityTemplate(activityTemplate);
}

void Activity::pushBackParameter(const std::string title,
			const double & value, const resqml2__ResqmlUom & uom)
{
	resqml2::ActivityTemplate* activityTemplate = getActivityTemplate();
	if (activityTemplate->isAnExistingParameter(title) == false)
		throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
	LONG64 maxOccurs = activityTemplate->getParameterMaxOccurences(title);
	if (maxOccurs > -1 && maxOccurs <= getParameterCount(title))
		throw invalid_argument("The max number of occurences has already been reached for parameter " + title);
	if (dynamic_cast<resqml2_0_1::ActivityTemplate*>(activityTemplate) != nullptr)
	{
		vector<resqml2__ParameterKind> allowedKinds = static_cast<resqml2_0_1::ActivityTemplate*>(activityTemplate)->getParameterAllowedKinds(title);
		if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), resqml2__ParameterKind__floatingPoint) == allowedKinds.end())
			throw invalid_argument("The parameter template " + title + " does not allow a double datatype.");
	}

	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy2_0_1);

	resqml2__FloatingPointQuantityParameter* fpqp = soap_new_resqml2__FloatingPointQuantityParameter(activity->soap, 1);
	fpqp->Title = title;
	fpqp->Value = value;
	fpqp->Uom = uom;
	activity->Parameter.push_back(fpqp);
}

void Activity::pushBackParameter(const std::string title, const std::string & value)
{
	resqml2::ActivityTemplate* activityTemplate = getActivityTemplate();
	if (activityTemplate->isAnExistingParameter(title) == false)
		throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
	LONG64 maxOccurs = activityTemplate->getParameterMaxOccurences(title);
	if (maxOccurs > -1 && maxOccurs <= getParameterCount(title))
		throw invalid_argument("The max number of occurences has already been reached for parameter " + title);
	if (dynamic_cast<resqml2_0_1::ActivityTemplate*>(activityTemplate) != nullptr)
	{
		vector<resqml2__ParameterKind> allowedKinds = static_cast<resqml2_0_1::ActivityTemplate*>(activityTemplate)->getParameterAllowedKinds(title);
		if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), resqml2__ParameterKind__string) == allowedKinds.end())
			throw invalid_argument("The parameter template " + title + " does not allow a string datatype.");
	}

	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy2_0_1);

	resqml2__StringParameter* sp = soap_new_resqml2__StringParameter(activity->soap, 1);
	sp->Title = title;
	sp->Value = value;
	activity->Parameter.push_back(sp);
}

void Activity::pushBackParameter(const std::string title, const LONG64 & value)
{
	resqml2::ActivityTemplate* activityTemplate = getActivityTemplate();
	if (activityTemplate->isAnExistingParameter(title) == false)
		throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
	LONG64 maxOccurs = activityTemplate->getParameterMaxOccurences(title);
	if (maxOccurs > -1 && maxOccurs <= getParameterCount(title))
		throw invalid_argument("The max number of occurences has already been reached for parameter " + title);
	if (dynamic_cast<resqml2_0_1::ActivityTemplate*>(activityTemplate) != nullptr)
	{
		vector<resqml2__ParameterKind> allowedKinds = static_cast<resqml2_0_1::ActivityTemplate*>(activityTemplate)->getParameterAllowedKinds(title);
		if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), resqml2__ParameterKind__integer) == allowedKinds.end())
			throw invalid_argument("The parameter template " + title + " does not allow an integer datatype.");
	}

	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy2_0_1);

	resqml2__IntegerQuantityParameter* iqp = soap_new_resqml2__IntegerQuantityParameter(activity->soap, 1);
	iqp->Title = title;
	iqp->Value = value;
	activity->Parameter.push_back(iqp);
}

void Activity::pushBackParameter(const std::string title, AbstractObject* resqmlObject)
{
	if (resqmlObject == nullptr)
		throw invalid_argument("The resqml object must be non null.");
	resqml2::ActivityTemplate* activityTemplate = getActivityTemplate();
	if (activityTemplate->isAnExistingParameter(title) == false)
		throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
	LONG64 maxOccurs = activityTemplate->getParameterMaxOccurences(title);
	if (maxOccurs > -1 && maxOccurs <= getParameterCount(title))
		throw invalid_argument("The max number of occurences has already been reached for parameter " + title);
	if (dynamic_cast<resqml2_0_1::ActivityTemplate*>(activityTemplate) != nullptr)
	{
		vector<resqml2__ParameterKind> allowedKinds = static_cast<resqml2_0_1::ActivityTemplate*>(activityTemplate)->getParameterAllowedKinds(title);
		if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), resqml2__ParameterKind__dataObject) == allowedKinds.end())
			throw invalid_argument("The parameter template " + title + " does not allow a data object datatype.");
	}

	//Backward relationship
	common::AbstractObject::addActivityToResqmlObject(this, resqmlObject);

	// XML
	if (updateXml)
	{
		_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy2_0_1);

		resqml2__DataObjectParameter* dop = soap_new_resqml2__DataObjectParameter(activity->soap, 1);
		dop->Title = title;
		dop->DataObject = resqmlObject->newResqmlReference();
		activity->Parameter.push_back(dop);
	}
}

unsigned int Activity::getParameterCount() const
{
	return static_cast<_resqml2__Activity*>(gsoapProxy2_0_1)->Parameter.size();
}

unsigned int Activity::getParameterCount(const std::string & paramTitle) const
{
	return getParameterFromTitle(paramTitle).size();
}

const std::string & Activity::getParameterTitle(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->Title;
}

std::vector<unsigned int> Activity::getParameterIndexOfTitle(const std::string & paramTitle) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy2_0_1);

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

std::vector<resqml2__AbstractActivityParameter*> Activity::getParameterFromTitle(const std::string & paramTitle) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy2_0_1);

	std::vector<resqml2__AbstractActivityParameter*> params;
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
	vector<resqml2__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__FloatingPointQuantityParameter)
			return false;
	}

	return true;
}

bool Activity::isAFloatingPointQuantityParameter(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__FloatingPointQuantityParameter;
}

vector<double> Activity::getFloatingPointQuantityParameterValue(const std::string & paramTitle) const
{
	vector<resqml2__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	vector<double> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__FloatingPointQuantityParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non double values.");
		else
			result.push_back(static_cast<resqml2__FloatingPointQuantityParameter*>(param[i])->Value);
	}

	return result;
}

double Activity::getFloatingPointQuantityParameterValue(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__FloatingPointQuantityParameter)
		throw invalid_argument("The parameter index is not in the parameter range.");

	return static_cast<resqml2__FloatingPointQuantityParameter*>(activity->Parameter[index])->Value;
}

vector<resqml2__ResqmlUom> Activity::getFloatingPointQuantityParameterUom(const std::string & paramTitle) const
{
	vector<resqml2__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	vector<resqml2__ResqmlUom> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__FloatingPointQuantityParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non double values.");
		else
			result.push_back(static_cast<resqml2__FloatingPointQuantityParameter*>(param[i])->Uom);
	}

	return result;
}

gsoap_resqml2_0_1::resqml2__ResqmlUom Activity::getFloatingPointQuantityParameterUom(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__FloatingPointQuantityParameter)
		throw invalid_argument("The parameter index is not in the parameter range.");

	return static_cast<resqml2__FloatingPointQuantityParameter*>(activity->Parameter[index])->Uom;
}

/*****************************
********** INTEGER ***********
*****************************/
bool Activity::isAnIntegerQuantityParameter(const std::string & paramTitle) const
{
	vector<resqml2__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerQuantityParameter)
			return false;
	}

	return true;
}

bool Activity::isAnIntegerQuantityParameter(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerQuantityParameter;
}

vector<LONG64> Activity::getIntegerQuantityParameterValue(const std::string & paramTitle) const
{
	vector<resqml2__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	vector<LONG64> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerQuantityParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non double values.");
		else
			result.push_back(static_cast<resqml2__IntegerQuantityParameter*>(param[i])->Value);
	}

	return result;
}

LONG64 Activity::getIntegerQuantityParameterValue(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerQuantityParameter)
		throw invalid_argument("The parameter index is not in the parameter range.");

	return static_cast<resqml2__IntegerQuantityParameter*>(activity->Parameter[index])->Value;
}

/*****************************
********** STRING ************
*****************************/
bool Activity::isAStringParameter(const std::string & paramTitle) const
{	
	vector<resqml2__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__StringParameter)
			return false;
	}

	return true;
}

bool Activity::isAStringParameter(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__StringParameter;
}

vector<string> Activity::getStringParameterValue(const std::string & paramTitle) const
{
	vector<resqml2__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	vector<string> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__StringParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non double values.");
		else
			result.push_back(static_cast<resqml2__StringParameter*>(param[i])->Value);
	}

	return result;
}

const std::string & Activity::getStringParameterValue(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__StringParameter)
		throw invalid_argument("The parameter index is not in the parameter range.");

	return static_cast<resqml2__StringParameter*>(activity->Parameter[index])->Value;
}

/*****************************
********** OBJECT ************
*****************************/
bool Activity::isAResqmlObjectParameter(const std::string & paramTitle) const
{
	vector<resqml2__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DataObjectParameter)
			return false;
	}

	return true;
}

bool Activity::isAResqmlObjectParameter(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DataObjectParameter;
}

vector<common::AbstractObject*> Activity::getResqmlObjectParameterValue(const std::string & paramTitle) const
{
	vector<resqml2__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	vector<common::AbstractObject*> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DataObjectParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non double values.");
		else
			result.push_back(getEpcDocument()->getResqmlAbstractObjectByUuid(static_cast<resqml2__DataObjectParameter*>(param[i])->DataObject->UUID));
	}

	return result;
}

common::AbstractObject* Activity::getResqmlObjectParameterValue(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy2_0_1);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DataObjectParameter)
		throw invalid_argument("The parameter index is not in the parameter range.");

	return getEpcDocument()->getResqmlAbstractObjectByUuid(static_cast<resqml2__DataObjectParameter*>(activity->Parameter[index])->DataObject->UUID);
}

void Activity::setActivityTemplate(resqml2::ActivityTemplate * activityTemplate)
{
	if (activityTemplate == nullptr)
	{
		return;
	}

	// Backward relationship
	activityTemplate->activityInstanceSet.push_back(this);

	// XML
	if (updateXml)
	{
		static_cast<_resqml2__Activity*>(gsoapProxy2_0_1)->ActivityDescriptor = activityTemplate->newResqmlReference();
	}
}

gsoap_resqml2_0_1::eml20__DataObjectReference* Activity::getActivityTemplateDor() const
{
	return static_cast<_resqml2__Activity*>(gsoapProxy2_0_1)->ActivityDescriptor;
}

std::string Activity::getResqmlVersion() const
{
	return "2.0.1";
}

void Activity::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy2_0_1);

	// Activity template
	resqml2::ActivityTemplate* activityTemplate = epcDoc->getResqmlAbstractObjectByUuid<resqml2::ActivityTemplate>(activity->ActivityDescriptor->UUID);
	if (activityTemplate != nullptr) {
		updateXml = false;
		setActivityTemplate(static_cast<resqml2::ActivityTemplate*>(activityTemplate));
		updateXml = true;
	}
	else {
		throw logic_error("The referenced activity template does not look to be an activity template.");
	}

	for (size_t i = 0; i < activity->Parameter.size(); ++i) {
		if (activity->Parameter[i]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DataObjectParameter) {
			resqml2__DataObjectParameter* dop = static_cast<resqml2__DataObjectParameter*>(activity->Parameter[i]);
			if (dop->DataObject == nullptr) {
				throw domain_error("The resqml object of a data object parameter cannot be null.");
			}

			updateXml = false;
			pushBackParameter(dop->Title, epcDoc->getResqmlAbstractObjectByUuid(dop->DataObject->UUID));
			updateXml = true;
		}
	}
}
