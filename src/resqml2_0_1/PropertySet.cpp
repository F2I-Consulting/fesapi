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
#include "resqml2_0_1/PropertySet.h"

#include "resqml2/AbstractProperty.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

PropertySet::PropertySet(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title,
	bool hasMultipleRealizations, bool hasSinglePropertyKind, gsoap_resqml2_0_1::resqml20__TimeSetKind timeSetKind)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be NULL.");
	}

	// proxy constructor
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREPropertySet(repo->getGsoapContext(), 1);
	static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->HasMultipleRealizations = hasMultipleRealizations;
	static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->HasSinglePropertyKind = hasSinglePropertyKind;
	static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->TimeSetKind = timeSetKind;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addOrReplaceDataObject(this);
}

void PropertySet::setXmlParent(RESQML2_NS::PropertySet * parent)
{
	static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->ParentSet.clear();
	static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->ParentSet.push_back(parent->newResqmlReference());
}

gsoap_resqml2_0_1::eml20__DataObjectReference const * PropertySet::getParentDor() const
{
	const std::vector<eml20__DataObjectReference *> & parentVector = static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->ParentSet;

	return parentVector.size() == 1 ? parentVector[0] : nullptr;
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

std::vector<gsoap_resqml2_0_1::eml20__DataObjectReference *> PropertySet::getAllPropertiesDors() const
{
	return static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->Properties;
}
