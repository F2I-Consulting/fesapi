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

#include "../common/AbstractHdfProxy.h"
#include "../common/EnumStringMapper.h"

#include "../resqml2/AbstractRepresentation.h"
#include "../common/PropertyKind.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

CommentProperty::CommentProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, COMMON_NS::PropertyKind * propKind)
{
	if (dimension == 0) {
		throw invalid_argument("The dimension cannot be zero.");
	}

	gsoapProxy2_3 = soap_new_resqml22__CommentProperty(rep->getGsoapContext());	
	_resqml22__CommentProperty* prop = static_cast<_resqml22__CommentProperty*>(gsoapProxy2_3);
	prop->IndexableElement = attachmentKind;
	if (dimension > 1) {
		prop->ValueCountPerIndexableElement = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_3->soap, sizeof(ULONG64)));
		*prop->ValueCountPerIndexableElement = dimension;
	}

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setRepresentation(rep);

	setPropertyKind(propKind);
}

std::string CommentProperty::pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName, LONG64)
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
	xmlValues->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	auto dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = hdfProxy->newEml23Reference();

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

COMMON_NS::AbstractHdfProxy* CommentProperty::getValuesHdfProxyAndDatasetPathOfPatch(unsigned int patchIndex, std::string & datasetPath) const
{
	// Look for the hdf where the comments are stored.
	_resqml22__CommentProperty* prop = static_cast<_resqml22__CommentProperty*>(gsoapProxy2_3);

	if (patchIndex >= prop->ValuesForPatch.size()) {
		throw std::out_of_range("The patch index is out of range.");
	}

	if (prop->ValuesForPatch[patchIndex]->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__StringExternalArray) {
		eml23__ExternalDatasetPart const * dsPart = static_cast<eml23__StringExternalArray*>(prop->ValuesForPatch[patchIndex])->Values->ExternalFileProxy[0];
		datasetPath = dsPart->PathInExternalFile;
		return getHdfProxyFromDataset(dsPart);
	}

	return nullptr;
}
