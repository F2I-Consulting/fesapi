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
#include <sstream>

#include <hdf5.h>

#include "../common/AbstractHdfProxy.h"
#include "../common/EnumStringMapper.h"
#include "../common/PropertyKind.h"

#include "../resqml2/AbstractRepresentation.h"
#include "../resqml2/StringTableLookup.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

CategoricalProperty::CategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind,
	RESQML2_NS::StringTableLookup* strLookup, COMMON_NS::PropertyKind * propKind)
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
		prop->ValueCountPerIndexableElement = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_3->soap, sizeof(ULONG64)));
		*prop->ValueCountPerIndexableElement = dimension;
	}

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	prop->Lookup = strLookup->newEml23Reference();
	getRepository()->addRelationship(this, strLookup);

	setRepresentation(rep);

	setPropertyKind(propKind);
}

COMMON_NS::DataObjectReference CategoricalProperty::getStringLookupDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<_resqml22__CategoricalProperty*>(gsoapProxy2_3)->Lookup);
}
