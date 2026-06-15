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

#include "../resqml2/AbstractRepresentation.h"

#include "DiscreteProperty.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

namespace {
	RESQML2_NS::AbstractValuesProperty* getOrCreateFakeProperty(COMMON_NS::DataObjectRepository& repo) {
		COMMON_NS::AbstractObject* fakeProp = repo.getDataObjectByUuid(RESQML2_0_1_NS::PropertySet::FAKE_PROP_UUID);
		if (fakeProp != nullptr) {
			if (auto* temp = dynamic_cast<RESQML2_NS::AbstractValuesProperty*>(fakeProp)) {
				return temp;
			}
			else {
				throw invalid_argument("The Fake property UUID is already used but no as a property");
			}
		}

		auto allReps = repo.getDataObjects<RESQML2_NS::AbstractRepresentation>();
		if (allReps.empty()) {
			throw new logic_error("Please add first a representation before creating a property set");
		}
		auto* firstRep = allReps.at(0);
		RESQML2_0_1_NS::DiscreteProperty* fakeDiscreteProp = repo.createDiscreteProperty(
			firstRep, RESQML2_0_1_NS::PropertySet::FAKE_PROP_UUID, "Fake Property", 1, gsoap_eml2_3::eml23__IndexableElement::representation, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::index);
		fakeDiscreteProp->pushBackIntegerConstantArrayOfValues(-1, 1);

		return fakeDiscreteProp;
	}
}

PropertySet::PropertySet(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title,
	bool hasMultipleRealizations, bool hasSinglePropertyKind, gsoap_resqml2_0_1::resqml20__TimeSetKind timeSetKind)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be NULL.");
	}

	// proxy constructor
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREPropertySet(repo->getGsoapContext());
	static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->HasMultipleRealizations = hasMultipleRealizations;
	static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->HasSinglePropertyKind = hasSinglePropertyKind;
	static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->TimeSetKind = timeSetKind;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});

	auto* fakeProp = getOrCreateFakeProperty(*repo);
	pushBackXmlProperty(fakeProp);
	repository->addRelationship(this, fakeProp);
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

PropertySet* PropertySet::getChildren(uint64_t index) const
{
	const std::vector<PropertySet *> & children = getChildren();
	return children.at(index);
}

void PropertySet::pushBackProperty(RESQML2_NS::AbstractProperty * prop)
{
	if (prop == nullptr) {
		throw invalid_argument("The property to push cannot be null.");
	}

	// Check if we need to remove the fake property
	if (getPropertyCount() == 0) {
		auto* repo = getRepository();
		static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->Properties.clear();
		auto* fakeProp = repo->getDataObjectByUuid(FAKE_PROP_UUID);
		if (fakeProp == nullptr) { // Defensive code
			throw std::logic_error("The fake property should exist since an empty property set is not allowed per RESQML spec");
		}
		if (fakeProp == prop) { // Defensive code
			throw std::invalid_argument("It is not allowed to push back the fake property since the latter is automatically managed");
		}
		repo->deleteRelationship(this, fakeProp);
		if (repo->getSourceObjects(fakeProp).empty()) {
			repo->cascadeDeleteDataObject(fakeProp);
		}
	}

	pushBackXmlProperty(prop);

	repository->addRelationship(this, prop);
}

std::vector<RESQML2_NS::AbstractProperty *> PropertySet::getProperties() const
{
	auto props = repository->getTargetObjects<RESQML2_NS::AbstractProperty>(this);
	return props.size() == 1 && props[0]->getUuid() == FAKE_PROP_UUID
		? std::vector<RESQML2_NS::AbstractProperty*>()
		: props;
}

uint64_t PropertySet::getPropertyCount() const noexcept
{
	return getProperties().size();
}

RESQML2_NS::AbstractProperty* PropertySet::getProperty(uint64_t index) const
{
	return getProperties().at(index);
}

void PropertySet::loadTargetRelationships()
{
	COMMON_NS::DataObjectReference dor = getParentDor();
	if (!dor.isEmpty()) {
		if (dor.getUuid() != getUuid()) {
			convertDorIntoRel(dor);
		}
		else {
			getRepository()->addWarning("The property set " + getUuid() + " cannot be its parent. It will be made as partial.");
			changeToPartialObject();
			return;
		}
	}

	auto allPropsDors = getAllPropertiesDors();
	if (allPropsDors.empty()) {
		getRepository()->addWarning("The property set " + getUuid() + " has no property at all. It will be made as partial.");
		changeToPartialObject();
		return;
	}

	for (auto dor2 : allPropsDors) {
		if (!dor2.isEmpty()) {
			convertDorIntoRel(dor2);
		}
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

gsoap_resqml2_0_1::resqml20__TimeSetKind PropertySet::getTimeSetKind() const
{
	return static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->TimeSetKind;
}

std::vector<COMMON_NS::DataObjectReference> PropertySet::getAllPropertiesDors() const
{
	std::vector<COMMON_NS::DataObjectReference> result;
	for (auto* dor : static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->Properties) {
		result.push_back(COMMON_NS::DataObjectReference(dor));
	}

	return result;
}
