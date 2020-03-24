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
#include <sstream>

#include <hdf5.h>

#include "../common/AbstractHdfProxy.h"
#include "../common/EnumStringMapper.h"

#include "../resqml2/AbstractRepresentation.h"
#include "../common/PropertyKind.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_2;

void ContinuousProperty::init(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	unsigned int dimension, gsoap_eml2_2::resqml22__IndexableElement attachmentKind)
{
	if (dimension == 0) {
		throw invalid_argument("The dimension cannot be zero.");
	}

	gsoapProxy2_2 = soap_new_resqml22__ContinuousProperty(rep->getGsoapContext());
	_resqml22__ContinuousProperty* prop = static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_2);
	prop->IndexableElement = attachmentKind;
	if (dimension > 1) {
		prop->ValueCountPerIndexableElement = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_2->soap, sizeof(ULONG64)));
		*prop->ValueCountPerIndexableElement = dimension;
	}

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setRepresentation(rep);
}

ContinuousProperty::ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_2::resqml22__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, COMMON_NS::PropertyKind * localPropKind)
{
	init(rep, guid, title, dimension, attachmentKind);

	static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_2)->Uom = gsoap_resqml2_0_1::soap_resqml20__ResqmlUom2s(gsoapProxy2_2->soap, uom);

	setPropertyKind(localPropKind);
}

ContinuousProperty::ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_2::resqml22__IndexableElement attachmentKind, const std::string & nonStandardUom, COMMON_NS::PropertyKind * localPropKind)
{
	init(rep, guid, title, dimension, attachmentKind);

	static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_2)->Uom = nonStandardUom;

	setPropertyKind(localPropKind);
}

gsoap_resqml2_0_1::resqml20__ResqmlUom ContinuousProperty::getUom() const
{
	gsoap_resqml2_0_1::resqml20__ResqmlUom result;
	gsoap_resqml2_0_1::soap_s2resqml20__ResqmlUom(gsoapProxy2_2->soap, static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_2)->Uom.c_str(), &result);
	return result;
}

std::string ContinuousProperty::pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* proxy, const std::string & datasetName)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);
	_resqml22__ContinuousProperty* prop = static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_2);

	// XML
	ostringstream oss;
	eml22__FloatingPointExternalArray* xmlValues = soap_new_eml22__FloatingPointExternalArray(gsoapProxy2_2->soap);
	xmlValues->Values = soap_new_eml22__ExternalDataset(gsoapProxy2_2->soap);
	auto dsPart = soap_new_eml22__ExternalDatasetPart(gsoapProxy2_2->soap);
	dsPart->EpcExternalPartReference = proxy->newEml22Reference();

	if (datasetName.empty()) {
		ostringstream ossForHdf;
		ossForHdf << "values_patch" << prop->ValuesForPatch.size();
		dsPart->PathInExternalFile = getHdfGroup() + "/" + ossForHdf.str();
	}
	else {
		dsPart->PathInExternalFile = datasetName;
	}
	xmlValues->Values->ExternalFileProxy.push_back(dsPart);

	prop->ValuesForPatch.push_back(xmlValues);

	return dsPart->PathInExternalFile;
}

COMMON_NS::AbstractHdfProxy* ContinuousProperty::getValuesHdfProxyAndDatasetPathOfPatch(unsigned int patchIndex, std::string & datasetPath) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	_resqml22__ContinuousProperty* prop = static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_2);
	if (dynamic_cast<eml22__FloatingPointExternalArray*>(prop->ValuesForPatch[patchIndex]) != nullptr) {
		eml22__ExternalDatasetPart * dsPart = static_cast<eml22__FloatingPointExternalArray*>(prop->ValuesForPatch[patchIndex])->Values->ExternalFileProxy[0];
		datasetPath = dsPart->PathInExternalFile;
		return getHdfProxyFromDataset(dsPart);
	}

	return nullptr;
}

double ContinuousProperty::getMinimumValue(unsigned int index) const
{
	_resqml22__ContinuousProperty* prop = static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_2);

	return prop->MinimumValue.size() <= index ? std::numeric_limits<double>::quiet_NaN() : prop->MinimumValue[index];
}

double ContinuousProperty::getMaximumValue(unsigned int index) const
{
	_resqml22__ContinuousProperty* prop = static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_2);

	return prop->MaximumValue.size() <= index ? std::numeric_limits<double>::quiet_NaN() : prop->MaximumValue[index];
}

void ContinuousProperty::setMinimumValue(double value, unsigned int index) const
{
	_resqml22__ContinuousProperty* prop = static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_2);

	while (prop->MinimumValue.size() <= index) {
		prop->MinimumValue.push_back(std::numeric_limits<double>::quiet_NaN());
	}

	prop->MinimumValue[index] = value;
}

void ContinuousProperty::setMaximumValue(double value, unsigned int index) const
{
	_resqml22__ContinuousProperty* prop = static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_2);

	while (prop->MaximumValue.size() <= index) {
		prop->MaximumValue.push_back(std::numeric_limits<double>::quiet_NaN());
	}

	prop->MaximumValue[index] = value;
}

size_t ContinuousProperty::getMinimumValueSize() const
{
	return static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_2)->MinimumValue.size();
}

size_t ContinuousProperty::getMaximumValueSize() const
{
	return static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_2)->MaximumValue.size();
}
