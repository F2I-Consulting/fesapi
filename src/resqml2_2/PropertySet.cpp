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
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

PropertySet::PropertySet(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title,
	bool hasMultipleRealizations, bool hasSinglePropertyKind, gsoap_eml2_3::resqml22__TimeSetKind timeSetKind)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be NULL.");
	}

	// proxy constructor
	gsoapProxy2_3 = soap_new_resqml22__PropertySet(repo->getGsoapContext());
	static_cast<_resqml22__PropertySet*>(gsoapProxy2_3)->HasMultipleRealizations = hasMultipleRealizations;
	static_cast<_resqml22__PropertySet*>(gsoapProxy2_3)->HasSinglePropertyKind = hasSinglePropertyKind;
	static_cast<_resqml22__PropertySet*>(gsoapProxy2_3)->TimeSetKind = timeSetKind;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addOrReplaceDataObject(this);
}

void PropertySet::setXmlParent(RESQML2_NS::PropertySet * parent)
{
	static_cast<_resqml22__PropertySet*>(gsoapProxy2_3)->ParentSet.clear();
	static_cast<_resqml22__PropertySet*>(gsoapProxy2_3)->ParentSet.push_back(parent->newEml23Reference());
}

COMMON_NS::DataObjectReference PropertySet::getParentDor() const
{
	std::vector<COMMON_NS::DataObjectReference> parentVector;
	for (size_t i = 0; i < static_cast<_resqml22__PropertySet*>(gsoapProxy2_3)->ParentSet.size(); ++i) {
		parentVector.push_back(COMMON_NS::DataObjectReference(static_cast<_resqml22__PropertySet*>(gsoapProxy2_3)->ParentSet[i]));
	}

	return parentVector.size() == 1 ? parentVector[0] : COMMON_NS::DataObjectReference();
}

void PropertySet::pushBackXmlProperty(RESQML2_NS::AbstractProperty * prop)
{
	static_cast<_resqml22__PropertySet*>(gsoapProxy2_3)->Properties.push_back(prop->newEml23Reference());
}

bool PropertySet::hasMultipleRealizations() const
{
	return static_cast<_resqml22__PropertySet*>(gsoapProxy2_3)->HasMultipleRealizations;
}

bool PropertySet::hasSinglePropertyKind() const
{
	return static_cast<_resqml22__PropertySet*>(gsoapProxy2_3)->HasSinglePropertyKind;
}

gsoap_eml2_3::resqml22__TimeSetKind PropertySet::getTimeSetKind() const
{
	return static_cast<_resqml22__PropertySet*>(gsoapProxy2_3)->TimeSetKind;
}

std::vector<COMMON_NS::DataObjectReference> PropertySet::getAllPropertiesDors() const
{
	std::vector<COMMON_NS::DataObjectReference> result;
	for (size_t i = 0; i < static_cast<_resqml22__PropertySet*>(gsoapProxy2_3)->Properties.size(); ++i) {
		result.push_back(COMMON_NS::DataObjectReference(static_cast<_resqml22__PropertySet*>(gsoapProxy2_3)->Properties[i]));
	}

	return result;
}
