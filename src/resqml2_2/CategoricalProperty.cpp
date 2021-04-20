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
#include "CategoricalProperty.h"

#include <stdexcept>

#include "../eml2/PropertyKind.h"

#include "../resqml2/AbstractRepresentation.h"
#include "../resqml2/DoubleTableLookup.h"
#include "../resqml2/StringTableLookup.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* CategoricalProperty::XML_NS = "resqml22";

CategoricalProperty::CategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind,
	RESQML2_NS::StringTableLookup* strLookup, EML2_NS::PropertyKind * propKind)
{
	if (strLookup == nullptr) {
		throw invalid_argument("The string lookup table cannot be null.");
	}
	if (dimension == 0) {
		throw invalid_argument("The dimension cannot be zero.");
	}

	gsoapProxy2_3 = soap_new_resqml22__CategoricalProperty(rep->getGsoapContext());	
	_resqml22__CategoricalProperty* prop = static_cast<_resqml22__CategoricalProperty*>(gsoapProxy2_3);
	prop->IndexableElement = attachmentKind;
	if (dimension > 1) {
		prop->ValueCountPerIndexableElement = static_cast<uint64_t*>(soap_malloc(gsoapProxy2_3->soap, sizeof(uint64_t)));
		*prop->ValueCountPerIndexableElement = dimension;
	}

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	rep->getRepository()->addDataObject(this);
	setRepresentation(rep);

	setPropertyKind(propKind);

	prop->Lookup = strLookup->newEml23Reference();
	getRepository()->addRelationship(this, strLookup);
}

CategoricalProperty::CategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind,
	RESQML2_NS::DoubleTableLookup* dblLookup, EML2_NS::PropertyKind * propKind)
{
	if (dblLookup == nullptr) {
		throw invalid_argument("The double lookup table cannot be null.");
	}
	if (dimension == 0) {
		throw invalid_argument("The dimension cannot be zero.");
	}

	gsoapProxy2_3 = soap_new_resqml22__CategoricalProperty(rep->getGsoapContext());
	_resqml22__CategoricalProperty* prop = static_cast<_resqml22__CategoricalProperty*>(gsoapProxy2_3);
	prop->IndexableElement = attachmentKind;
	if (dimension > 1) {
		prop->ValueCountPerIndexableElement = static_cast<uint64_t*>(soap_malloc(gsoapProxy2_3->soap, sizeof(uint64_t)));
		*prop->ValueCountPerIndexableElement = dimension;
	}

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	rep->getRepository()->addDataObject(this);
	setRepresentation(rep);

	setPropertyKind(propKind);

	prop->Lookup = dblLookup->newEml23Reference();
	getRepository()->addRelationship(this, dblLookup);
}

COMMON_NS::DataObjectReference CategoricalProperty::getLookupDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<_resqml22__CategoricalProperty*>(gsoapProxy2_3)->Lookup);
}
