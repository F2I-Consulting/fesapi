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
#include "resqml2/PropertyKind.h"

#include <stdexcept>

#include "resqml2/AbstractValuesProperty.h"

using namespace std;
using namespace resqml2;
using namespace epc;

const char* PropertyKind::XML_TAG = "PropertyKind";

const std::string & PropertyKind::getNamingSystem() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::_resqml2__PropertyKind*>(gsoapProxy2_0_1)->NamingSystem;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

const gsoap_resqml2_0_1::resqml2__ResqmlUom & PropertyKind::getUom() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::_resqml2__PropertyKind*>(gsoapProxy2_0_1)->RepresentativeUom;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string PropertyKind::getUomAsString() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return gsoap_resqml2_0_1::soap_resqml2__ResqmlUom2s(gsoapProxy2_0_1->soap, getUom());
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string PropertyKind::getParentAsString() const
{
	if (!isParentAnEnergisticsPropertyKind()) {
		return getParentLocalPropertyKindTitle();
	}
	else
	{
		gsoap_resqml2_0_1::_resqml2__PropertyKind* propType = static_cast<gsoap_resqml2_0_1::_resqml2__PropertyKind*>(gsoapProxy2_0_1);
		return epcDocument->getEnergisticsPropertyKindName(static_cast<gsoap_resqml2_0_1::resqml2__StandardPropertyKind*>(propType->ParentPropertyKind)->Kind);
	}
}

bool PropertyKind::isParentAnEnergisticsPropertyKind() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::_resqml2__PropertyKind*>(gsoapProxy2_0_1)->ParentPropertyKind->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__StandardPropertyKind;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind PropertyKind::getParentEnergisticsPropertyKind() const
{
	if (isParentAnEnergisticsPropertyKind())
	{
		if (gsoapProxy2_0_1 != nullptr) {
			gsoap_resqml2_0_1::_resqml2__PropertyKind* propKind = static_cast<gsoap_resqml2_0_1::_resqml2__PropertyKind*>(gsoapProxy2_0_1);
			return static_cast<gsoap_resqml2_0_1::resqml2__StandardPropertyKind*>(propKind->ParentPropertyKind)->Kind;
		}
		else {
			throw logic_error("Not implemented yet");
		}
	}
	
	throw invalid_argument("The property kind parent of this property kind is not an Energistics one.");
}

PropertyKind* PropertyKind::getParentLocalPropertyKind() const
{
	return static_cast<PropertyKind*>(epcDocument->getResqmlAbstractObjectByUuid(getParentLocalPropertyKindUuid()));
}

gsoap_resqml2_0_1::eml20__DataObjectReference* PropertyKind::getParentLocalPropertyKindDor() const
{
	if (isParentAnEnergisticsPropertyKind()) {
		throw invalid_argument("The property kind parent of this property kind is not a local one.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::_resqml2__PropertyKind* propKind = static_cast<gsoap_resqml2_0_1::_resqml2__PropertyKind*>(gsoapProxy2_0_1);
		return static_cast<gsoap_resqml2_0_1::resqml2__LocalPropertyKind*>(propKind->ParentPropertyKind)->LocalPropertyKind;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string PropertyKind::getParentLocalPropertyKindUuid() const
{
	return getParentLocalPropertyKindDor()->UUID;
}

std::string PropertyKind::getParentLocalPropertyKindTitle() const
{
	return getParentLocalPropertyKindDor()->Title;
}

void PropertyKind::setParentPropertyKind(PropertyKind* parentPropertyKind)
{
	parentPropertyKind->childPropertyKind.push_back(this);

	if (updateXml) {
		setXmlParentPropertyKind(parentPropertyKind);
	}
}

vector<Relationship> PropertyKind::getAllEpcRelationships() const
{
	gsoap_resqml2_0_1::_resqml2__PropertyKind* propType = static_cast<gsoap_resqml2_0_1::_resqml2__PropertyKind*>(gsoapProxy2_0_1);

	vector<Relationship> result;

	// forward relationships
	if (!isParentAnEnergisticsPropertyKind())
	{
		const PropertyKind* const parentPropertyKind = getParentLocalPropertyKind();
		Relationship rel(parentPropertyKind->getPartNameInEpcDocument(), "", parentPropertyKind->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}

	// backwards relationships
	for (size_t i = 0; i < propertySet.size(); ++i) {
		Relationship rel(propertySet[i]->getPartNameInEpcDocument(), "", propertySet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	for (size_t i = 0; i < childPropertyKind.size(); ++i) {
		Relationship rel(childPropertyKind[i]->getPartNameInEpcDocument(), "", childPropertyKind[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

void PropertyKind::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	if (isParentAnEnergisticsPropertyKind()) {
		return;
	}

	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getParentLocalPropertyKindDor();
	resqml2::PropertyKind* parentPk = epcDoc->getResqmlAbstractObjectByUuid<PropertyKind>(dor->UUID);
	if (parentPk == nullptr) {
		epcDoc->createPartial(dor);
		parentPk = epcDoc->getResqmlAbstractObjectByUuid<PropertyKind>(dor->UUID);
		if (parentPk == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
	}
	parentPk->childPropertyKind.push_back(this);
}
