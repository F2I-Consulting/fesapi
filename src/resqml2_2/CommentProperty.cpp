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
#include "CommentProperty.h"

#include <sstream>
#include <list>

#include "../eml2/AbstractHdfProxy.h"
#include "../common/EnumStringMapper.h"

#include "../resqml2/AbstractRepresentation.h"
#include "../eml2/PropertyKind.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* CommentProperty::XML_NS = "resqml22";

CommentProperty::CommentProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_3::eml23__IndexableElement attachmentKind, EML2_NS::PropertyKind * propKind)
{
	gsoapProxy2_3 = soap_new_resqml22__CommentProperty(rep->getGsoapContext());	
	_resqml22__CommentProperty* prop = static_cast<_resqml22__CommentProperty*>(gsoapProxy2_3);
	prop->IndexableElement = attachmentKind;
	prop->ValueCountPerIndexableElement.push_back(dimension);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	rep->getRepository()->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
	setRepresentation(rep);

	setPropertyKind(propKind);
}

std::string CommentProperty::pushBackRefToExistingDataset(EML2_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName)
{
	if (hdfProxy == nullptr) {
		hdfProxy = getRepository()->getDefaultHdfProxy();
		if (hdfProxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, hdfProxy);
	_resqml22__CommentProperty* prop = static_cast<_resqml22__CommentProperty*>(gsoapProxy2_3);

	// XML
	ostringstream oss;
	eml23__StringExternalArray* xmlValues = soap_new_eml23__StringExternalArray(gsoapProxy2_3->soap);
	xmlValues->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	std::string actualDataArrayName = datasetName.empty()
		? getHdfGroup() + "/values_patch" + std::to_string(prop->ValuesForPatch.size())
		: datasetName;
	xmlValues->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(actualDataArrayName, hdfProxy->getElementCount(actualDataArrayName), hdfProxy));

	prop->ValuesForPatch.push_back(xmlValues);

	return actualDataArrayName;
}

EML2_NS::AbstractHdfProxy* CommentProperty::getValuesHdfProxyAndDatasetPathOfPatch(unsigned int patchIndex, std::string& datasetPath) const
{
	// Look for the hdf where the comments are stored.
	_resqml22__CommentProperty* prop = static_cast<_resqml22__CommentProperty*>(gsoapProxy2_3);

	if (patchIndex >= prop->ValuesForPatch.size()) {
		throw std::out_of_range("The patch index is out of range.");
	}

	if (prop->ValuesForPatch[patchIndex]->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__StringExternalArray) {
		datasetPath = static_cast<eml23__StringExternalArray*>(prop->ValuesForPatch[patchIndex])->Values->ExternalDataArrayPart[0]->PathInExternalFile;
		return getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__StringExternalArray*>(prop->ValuesForPatch[patchIndex])->Values->ExternalDataArrayPart[0]);
	}

	return nullptr;
}
