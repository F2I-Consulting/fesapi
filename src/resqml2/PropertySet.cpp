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

#include <limits>

#include "AbstractProperty.h"

using namespace std;
using namespace RESQML2_NS;

const char* PropertySet::XML_TAG = "PropertySet";

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
