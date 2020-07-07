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

PropertySet::PropertySet(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title,
	bool hasMultipleRealizations, bool hasSinglePropertyKind, gsoap_eml2_3::resqml22__TimeSetKind timeSetKind)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be NULL.");
	}
	if (timeSetKind == gsoap_eml2_3::resqml22__TimeSetKind__single_x0020time_x0020series) {
		throw invalid_argument("The single time series time set kind is not supported in V2.0.1");
	}

	// proxy constructor
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREPropertySet(repo->getGsoapContext());
	static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->HasMultipleRealizations = hasMultipleRealizations;
	static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->HasSinglePropertyKind = hasSinglePropertyKind;
	static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->TimeSetKind = timeSetKind == gsoap_eml2_3::resqml22__TimeSetKind__single_x0020time
		? gsoap_resqml2_0_1::resqml20__TimeSetKind__single_x0020time
		: static_cast<resqml20__TimeSetKind>(timeSetKind-1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addOrReplaceDataObject(this);
}

void PropertySet::setXmlParent(RESQML2_NS::PropertySet * parent)
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
	auto kind = static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->TimeSetKind;
	return kind == gsoap_resqml2_0_1::resqml20__TimeSetKind__single_x0020time
		? gsoap_eml2_3::resqml22__TimeSetKind__single_x0020time
		: static_cast<gsoap_eml2_3::resqml22__TimeSetKind>(kind+1);
}

std::vector<COMMON_NS::DataObjectReference> PropertySet::getAllPropertiesDors() const
{
	std::vector<COMMON_NS::DataObjectReference> result;
	for (size_t i = 0; i < static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->Properties.size(); ++i) {
		result.push_back(COMMON_NS::DataObjectReference(static_cast<_resqml20__PropertySet*>(gsoapProxy2_0_1)->Properties[i]));
	}

	return result;
}
