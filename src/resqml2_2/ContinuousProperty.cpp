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

#include "../eml2/AbstractHdfProxy.h"
#include "../common/EnumStringMapper.h"

#include "../resqml2/AbstractRepresentation.h"
#include "../eml2/PropertyKind.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

void ContinuousProperty::init(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind)
{
	if (dimension == 0) {
		throw invalid_argument("The dimension cannot be zero.");
	}

	gsoapProxy2_3 = soap_new_resqml22__ContinuousProperty(rep->getGsoapContext());
	_resqml22__ContinuousProperty* prop = static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_3);
	prop->IndexableElement = attachmentKind;
	if (dimension > 1) {
		prop->ValueCountPerIndexableElement = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_3->soap, sizeof(ULONG64)));
		*prop->ValueCountPerIndexableElement = dimension;
	}

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setRepresentation(rep);
}

ContinuousProperty::ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, EML2_NS::PropertyKind * localPropKind)
{
	init(rep, guid, title, dimension, attachmentKind);

	static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_3)->Uom = gsoap_resqml2_0_1::soap_resqml20__ResqmlUom2s(gsoapProxy2_3->soap, uom);

	setPropertyKind(localPropKind);
}

ContinuousProperty::ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, const std::string & nonStandardUom, EML2_NS::PropertyKind * localPropKind)
{
	init(rep, guid, title, dimension, attachmentKind);

	static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_3)->Uom = nonStandardUom;

	setPropertyKind(localPropKind);
}

gsoap_resqml2_0_1::resqml20__ResqmlUom ContinuousProperty::getUom() const
{
	gsoap_resqml2_0_1::resqml20__ResqmlUom result;
	gsoap_resqml2_0_1::soap_s2resqml20__ResqmlUom(gsoapProxy2_3->soap, static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_3)->Uom.c_str(), &result);
	return result;
}

std::string ContinuousProperty::pushBackRefToExistingDataset(EML2_NS::AbstractHdfProxy* proxy, const std::string & datasetName)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);
	_resqml22__ContinuousProperty* prop = static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_3);

	// XML
	ostringstream oss;
	eml23__FloatingPointExternalArray* xmlValues = soap_new_eml23__FloatingPointExternalArray(gsoapProxy2_3->soap);
	xmlValues->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	auto dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();

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

EML2_NS::AbstractHdfProxy* ContinuousProperty::getValuesHdfProxyAndDatasetPathOfPatch(unsigned int patchIndex, std::string & datasetPath) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	_resqml22__ContinuousProperty* prop = static_cast<_resqml22__ContinuousProperty*>(gsoapProxy2_3);
	if (dynamic_cast<eml23__FloatingPointExternalArray*>(prop->ValuesForPatch[patchIndex]) != nullptr) {
		eml23__ExternalDatasetPart * dsPart = static_cast<eml23__FloatingPointExternalArray*>(prop->ValuesForPatch[patchIndex])->Values->ExternalFileProxy[0];
		datasetPath = dsPart->PathInExternalFile;
		return getHdfProxyFromDataset(dsPart);
	}

	return nullptr;
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
