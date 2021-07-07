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
#include "ContinuousProperty.h"

#include <limits>

#include "../common/EnumStringMapper.h"

#include "../eml2/AbstractHdfProxy.h"
#include "../eml2/PropertyKind.h"

#include "../resqml2/AbstractRepresentation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* ContinuousProperty::XML_NS = "resqml22";

void ContinuousProperty::init(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	gsoap_eml2_3::resqml22__IndexableElement attachmentKind,
	std::vector<int> dimensions)
{
	gsoapProxy2_3 = soap_new_resqml22__ContinuousProperty(rep->getGsoapContext());
	_resqml22__ContinuousProperty* prop = static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_3);
	prop->IndexableElement = attachmentKind;
	if (dimensions.empty()) {
		prop->ValueCountPerIndexableElement = { 1 };
	}
	else {
		for (auto dim : dimensions) {
			prop->ValueCountPerIndexableElement.push_back(dim);
		}
	}

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	rep->getRepository()->addDataObject(this);
	setRepresentation(rep);
}

ContinuousProperty::ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	gsoap_eml2_3::resqml22__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, EML2_NS::PropertyKind * localPropKind,
	std::vector<int> dimensions)
{
	init(rep, guid, title, attachmentKind, dimensions);

	static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_3)->Uom = gsoap_resqml2_0_1::soap_resqml20__ResqmlUom2s(gsoapProxy2_3->soap, uom);

	setPropertyKind(localPropKind);
}

ContinuousProperty::ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	gsoap_eml2_3::resqml22__IndexableElement attachmentKind, const std::string & nonStandardUom, EML2_NS::PropertyKind * localPropKind,
	std::vector<int> dimensions)
{
	init(rep, guid, title, attachmentKind, dimensions);

	static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_3)->Uom = nonStandardUom;

	setPropertyKind(localPropKind);
}

gsoap_resqml2_0_1::resqml20__ResqmlUom ContinuousProperty::getUom() const
{
	gsoap_resqml2_0_1::resqml20__ResqmlUom result;
	const int tmp = gsoap_resqml2_0_1::soap_s2resqml20__ResqmlUom(gsoapProxy2_3->soap, static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_3)->Uom.c_str(), &result);

	return tmp != SOAP_OK ? gsoap_resqml2_0_1::resqml20__ResqmlUom::Euc : result;
}

std::string ContinuousProperty::getUomAsString() const
{
	return static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_3)->Uom;
}

double ContinuousProperty::getMinimumValue(unsigned int index) const
{
	_resqml22__ContinuousProperty* prop = static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_3);

	return prop->MinimumValue.size() <= index ? std::numeric_limits<double>::quiet_NaN() : prop->MinimumValue[index];
}

double ContinuousProperty::getMaximumValue(unsigned int index) const
{
	_resqml22__ContinuousProperty* prop = static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_3);

	return prop->MaximumValue.size() <= index ? std::numeric_limits<double>::quiet_NaN() : prop->MaximumValue[index];
}

void ContinuousProperty::setMinimumValue(double value, unsigned int index) const
{
	_resqml22__ContinuousProperty* prop = static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_3);

	while (prop->MinimumValue.size() <= index) {
		prop->MinimumValue.push_back(std::numeric_limits<double>::quiet_NaN());
	}

	prop->MinimumValue[index] = value;
}

void ContinuousProperty::setMaximumValue(double value, unsigned int index) const
{
	_resqml22__ContinuousProperty* prop = static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_3);

	while (prop->MaximumValue.size() <= index) {
		prop->MaximumValue.push_back(std::numeric_limits<double>::quiet_NaN());
	}

	prop->MaximumValue[index] = value;
}

size_t ContinuousProperty::getMinimumValueSize() const
{
	return static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_3)->MinimumValue.size();
}

size_t ContinuousProperty::getMaximumValueSize() const
{
	return static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_3)->MaximumValue.size();
}
