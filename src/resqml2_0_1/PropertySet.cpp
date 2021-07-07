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
#include "PropertySet.h"

#include "../resqml2/AbstractProperty.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* PropertySet::XML_NS = "resqml20";
const char* PropertySet::XML_TAG = "PropertySet";

PropertySet::PropertySet(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title,
	bool hasMultipleRealizations, bool hasSinglePropertyKind, gsoap_eml2_3::resqml22__TimeSetKind timeSetKind)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be NULL.");
	}
	if (timeSetKind == gsoap_eml2_3::resqml22__TimeSetKind::single_x0020time_x0020series) {
		throw invalid_argument("The single time series time set kind is not supported in V2.0.1");
	}

	// proxy constructor
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREPropertySet(repo->getGsoapContext());
	static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->HasMultipleRealizations = hasMultipleRealizations;
	static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->HasSinglePropertyKind = hasSinglePropertyKind;
	static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->TimeSetKind = timeSetKind == gsoap_eml2_3::resqml22__TimeSetKind::single_x0020time
		? gsoap_resqml2_0_1::resqml20__TimeSetKind::single_x0020time
		: static_cast<resqml20__TimeSetKind>(static_cast<std::underlying_type<gsoap_eml2_3::resqml22__TimeSetKind>::type>(timeSetKind) - 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(this);
}

void PropertySet::setParent(PropertySet * parent)
{
	if (parent == nullptr) {
		throw invalid_argument("The parent property set cannot be null.");
	}

	repository->addRelationship(this, parent);

	setXmlParent(parent);
}

PropertySet * PropertySet::getParent() const
{
	return static_cast<PropertySet*>(repository->getDataObjectByUuid(getParentDor().getUuid()));
}

std::vector<PropertySet *> PropertySet::getChildren() const
{
	return repository->getSourceObjects<PropertySet>(this);
}

unsigned int PropertySet::getChildrenCount() const
{
	const std::vector<PropertySet *> & children = getChildren();

	if (children.size() > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("Too much children in this property set");
	}

	return static_cast<unsigned int>(children.size());
}

PropertySet* PropertySet::getChildren(unsigned int index) const
{
	const std::vector<PropertySet *> & children = getChildren();

	if (index < children.size()) {
		return children[index];
	}

	throw out_of_range("The index of the child is out of range");
}

void PropertySet::pushBackProperty(RESQML2_NS::AbstractProperty * prop)
{
	if (prop == nullptr)
		throw invalid_argument("The property to push cannot be null.");

	pushBackXmlProperty(prop);

	repository->addRelationship(this, prop);
}

std::vector<RESQML2_NS::AbstractProperty *> PropertySet::getProperties() const
{
	return repository->getTargetObjects<RESQML2_NS::AbstractProperty>(this);
}

unsigned int PropertySet::getPropertyCount() const
{
	const std::vector<RESQML2_NS::AbstractProperty *> & props = getProperties();

	if (props.size() > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("Too much property in this property set");
	}

	return static_cast<unsigned int>(props.size());
}

RESQML2_NS::AbstractProperty* PropertySet::getProperty(unsigned int index) const
{
	const std::vector<RESQML2_NS::AbstractProperty *> & props = getProperties();

	if (index < props.size()) {
		return props[index];
	}

	throw out_of_range("The index of the property is out of range");
}

void PropertySet::loadTargetRelationships()
{
	COMMON_NS::DataObjectReference dor = getParentDor();
	if (!dor.isEmpty()) {
		PropertySet* propertySet = getRepository()->getDataObjectByUuid<PropertySet>(dor.getUuid());
		if (propertySet == nullptr) { // partial transfer
			getRepository()->createPartial(dor);
			propertySet = getRepository()->getDataObjectByUuid<PropertySet>(dor.getUuid());
			if (propertySet == nullptr) {
				throw invalid_argument("The DOR looks invalid.");
			}
		}
		repository->addRelationship(this, propertySet);
	}

	const std::vector<COMMON_NS::DataObjectReference>& propDors = getAllPropertiesDors();
	for (size_t i = 0; i < propDors.size(); ++i) {
		dor = propDors[i];
		RESQML2_NS::AbstractProperty* prop = getRepository()->getDataObjectByUuid<RESQML2_NS::AbstractProperty>(dor.getUuid());
		if (prop == nullptr) { // partial transfer
			getRepository()->createPartial(dor);
			prop = getRepository()->getDataObjectByUuid<RESQML2_NS::AbstractProperty>(dor.getUuid());
			if (prop == nullptr) {
				throw invalid_argument("The DOR looks invalid.");
			}
		}
		repository->addRelationship(this, prop);
	}
}

void PropertySet::setXmlParent(PropertySet * parent)
{
	static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->ParentSet.clear();
	static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->ParentSet.push_back(parent->newResqmlReference());
}

COMMON_NS::DataObjectReference PropertySet::getParentDor() const
{
	std::vector<COMMON_NS::DataObjectReference> parentVector;
	for (size_t i = 0; i < static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->ParentSet.size(); ++i) {
		parentVector.push_back(COMMON_NS::DataObjectReference(static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->ParentSet[i]));
	}

	return parentVector.size() == 1 ? parentVector[0] : COMMON_NS::DataObjectReference();
}

void PropertySet::pushBackXmlProperty(RESQML2_NS::AbstractProperty * prop)
{
	static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->Properties.push_back(prop->newResqmlReference());
}

bool PropertySet::hasMultipleRealizations() const
{
	return static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->HasMultipleRealizations;
}

bool PropertySet::hasSinglePropertyKind() const
{
	return static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->HasSinglePropertyKind;
}

gsoap_eml2_3::resqml22__TimeSetKind PropertySet::getTimeSetKind() const
{
	resqml20__TimeSetKind kind = static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->TimeSetKind;
	return kind == gsoap_resqml2_0_1::resqml20__TimeSetKind::single_x0020time
		? gsoap_eml2_3::resqml22__TimeSetKind::single_x0020time
		: static_cast<gsoap_eml2_3::resqml22__TimeSetKind>(static_cast<std::underlying_type<resqml20__TimeSetKind>::type>(kind) + 1);
}

std::vector<COMMON_NS::DataObjectReference> PropertySet::getAllPropertiesDors() const
{
	std::vector<COMMON_NS::DataObjectReference> result;
	for (size_t i = 0; i < static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->Properties.size(); ++i) {
		result.push_back(COMMON_NS::DataObjectReference(static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->Properties[i]));
	}

	return result;
}
