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
#include "resqml2_0_1/PropertyKind.h"

#include <stdexcept>

#include "resqml2/AbstractValuesProperty.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

void PropertyKind::init(soap* soapContext, const std::string & guid, const std::string & title, const std::string & namingSystem)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREPropertyKind(soapContext, 1);
	_resqml2__PropertyKind* propType = getSpecializedGsoapProxy();

	propType->NamingSystem = namingSystem;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

PropertyKind::PropertyKind(soap* soapContext, const string & guid, const string & title,
	const string & namingSystem, const resqml2__ResqmlUom & uom, const resqml2__ResqmlPropertyKind & parentEnergisticsPropertyKind)
{
	init(soapContext, guid, title, namingSystem);
	static_cast<_resqml2__PropertyKind*>(gsoapProxy2_0_1)->RepresentativeUom = uom;

	resqml2__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml2__StandardPropertyKind(gsoapProxy2_0_1->soap, 1);
	xmlStandardPropKind->Kind = parentEnergisticsPropertyKind;
	static_cast<_resqml2__PropertyKind*>(gsoapProxy2_0_1)->ParentPropertyKind = xmlStandardPropKind;
}

PropertyKind::PropertyKind(soap* soapContext, const string & guid, const string & title,
	const string & namingSystem, const resqml2__ResqmlUom & uom, resqml2::PropertyKind * parentPropType)
{
	init(soapContext, guid, title, namingSystem);
	static_cast<_resqml2__PropertyKind*>(gsoapProxy2_0_1)->RepresentativeUom = uom;

	setParentPropertyKind(parentPropType);
}

PropertyKind::PropertyKind(soap* soapContext, const string & guid, const string & title,
	const string & namingSystem, const std::string & nonStandardUom, const resqml2__ResqmlPropertyKind & parentEnergisticsPropertyKind)
{
	init(soapContext, guid, title, namingSystem);
	static_cast<_resqml2__PropertyKind*>(gsoapProxy2_0_1)->RepresentativeUom = gsoap_resqml2_0_1::resqml2__ResqmlUom__Euc;
	pushBackExtraMetadata("Uom", nonStandardUom);

	resqml2__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml2__StandardPropertyKind(gsoapProxy2_0_1->soap, 1);
	xmlStandardPropKind->Kind = parentEnergisticsPropertyKind;
	static_cast<_resqml2__PropertyKind*>(gsoapProxy2_0_1)->ParentPropertyKind = xmlStandardPropKind;
}

PropertyKind::PropertyKind(soap* soapContext, const string & guid, const string & title,
	const string & namingSystem, const std::string & nonStandardUom, resqml2::PropertyKind * parentPropType)
{
	init(soapContext, guid, title, namingSystem);
	static_cast<_resqml2__PropertyKind*>(gsoapProxy2_0_1)->RepresentativeUom = gsoap_resqml2_0_1::resqml2__ResqmlUom__Euc;
	pushBackExtraMetadata("Uom", nonStandardUom);

	setParentPropertyKind(parentPropType);
}

_resqml2__PropertyKind* PropertyKind::getSpecializedGsoapProxy() const
{
	if (isPartial()) {
		throw logic_error("Partial object");
	}

	return static_cast<_resqml2__PropertyKind*>(gsoapProxy2_0_1);
}

void PropertyKind::setXmlParentPropertyKind(resqml2::PropertyKind* parentPropertyKind)
{
	_resqml2__PropertyKind* propType = getSpecializedGsoapProxy();

	resqml2__LocalPropertyKind* xmlLocalPropKind = soap_new_resqml2__LocalPropertyKind(gsoapProxy2_0_1->soap, 1);
	xmlLocalPropKind->LocalPropertyKind = parentPropertyKind->newResqmlReference();
	propType->ParentPropertyKind = xmlLocalPropKind;
}

bool PropertyKind::isChildOf(gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind standardPropKind) const
{
	if (!isParentAnEnergisticsPropertyKind()) {
		return getParentLocalPropertyKind()->isChildOf(standardPropKind);
	}
	else{
		if (getParentEnergisticsPropertyKind() == standardPropKind) {
			return true;
		}
		else if (epcDocument->getPropertyKindMapper() != nullptr) {
			return epcDocument->getPropertyKindMapper()->isChildOf(getParentEnergisticsPropertyKind(), standardPropKind);
		}
		else {
			throw std::invalid_argument("You must load the property kind mapping files if you want to get the standard parent property kind.");
		}
	}
}

bool PropertyKind::isAbstract() const
{
	return getSpecializedGsoapProxy()->IsAbstract;
}
