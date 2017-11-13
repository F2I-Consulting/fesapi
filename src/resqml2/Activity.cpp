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
#include "resqml2/Activity.h"

#include "resqml2/ActivityTemplate.h"

#include <stdexcept>
#include <algorithm>

using namespace std;
using namespace resqml2;
using namespace epc;

const char* Activity::XML_TAG = "Activity";

vector<Relationship> Activity::getAllEpcRelationships() const
{
	vector<Relationship> result;

	resqml2::ActivityTemplate* activityTemplate = getActivityTemplate();
	if (activityTemplate != nullptr) {
		Relationship rel(activityTemplate->getPartNameInEpcDocument(), "", activityTemplate->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
	else
		throw domain_error("The activity template associated to the activity cannot be nullptr.");

	std::vector<AbstractObject*> resqmlObjectSet = getResqmlObjectSet();
	for (size_t i = 0; i < resqmlObjectSet.size(); ++i) {
		Relationship relResqmlObject(resqmlObjectSet[i]->getPartNameInEpcDocument(), "", resqmlObjectSet[i]->getUuid());
		relResqmlObject.setDestinationObjectType();
		result.push_back(relResqmlObject);
	}

	return result;
}

std::vector<common::AbstractObject*> Activity::getResqmlObjectSet() const
{
	std::vector<common::AbstractObject*> result;

	unsigned int paramCount = getParameterCount();

	for (unsigned int index=0; index < paramCount; ++index) {
		if (isAResqmlObjectParameter(index)) {
			common::AbstractObject* obj = getResqmlObjectParameterValue(index);
			if (std::find(result.begin(), result.end(), obj) == result.end()) {
				result.push_back(obj);
			}
		}
	}

	return result;
}

ActivityTemplate* Activity::getActivityTemplate() const
{
	return getEpcDocument()->getResqmlAbstractObjectByUuid<resqml2::ActivityTemplate>(getActivityTemplateDor()->UUID);
}
