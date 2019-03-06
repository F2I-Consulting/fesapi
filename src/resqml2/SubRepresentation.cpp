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
#include "resqml2/SubRepresentation.h"

#include <sstream>
#include <stdexcept>

#include "hdf5.h"

#include "resqml2/AbstractFeatureInterpretation.h"
#include "common/AbstractHdfProxy.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/AbstractIjkGridRepresentation.h"

using namespace std;
using namespace epc;
using namespace RESQML2_NS;

const char* SubRepresentation::XML_TAG = "SubRepresentation";

vector<Relationship> SubRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractRepresentation::getAllEpcRelationships();

	const unsigned int supRepCount = getSupportingRepresentationCount();
	for (unsigned int supRepIndex = 0; supRepIndex < supRepCount; ++supRepIndex) {
		AbstractRepresentation* supportingRep = getSupportingRepresentation(supRepIndex);
		if (!supportingRep->isPartial())
		{
			Relationship rel(supportingRep->getPartNameInEpcDocument(), "", supportingRep->getUuid());
			rel.setDestinationObjectType();
			result.push_back(rel);
		}
	}
    
	return result;
}

void SubRepresentation::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	AbstractRepresentation::importRelationshipSetFromEpc(epcDoc);

	// Supporting representation
	const unsigned int supRepCount = getSupportingRepresentationCount();
	for (unsigned int supRepIndex = 0; supRepIndex < supRepCount; ++supRepIndex) {
		gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getSupportingRepresentationDor(supRepIndex);
		RESQML2_NS::AbstractRepresentation* supportingRep = epcDoc->getDataObjectByUuid<RESQML2_NS::AbstractRepresentation>(dor->UUID);
		if (supportingRep == nullptr) { // partial transfer
			getEpcDocument()->createPartial(dor);
			supportingRep = getEpcDocument()->getDataObjectByUuid<RESQML2_NS::AbstractRepresentation>(dor->UUID);
		}
		if (supportingRep == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
		updateXml = false;
		supportingRep->pushBackSubRepresentation(this);
		updateXml = true;
	}
}

ULONG64 SubRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	if (getElementKindOfPatch(patchIndex, 0) == NODE) {
		return getElementCountOfPatch(patchIndex);
	}
	else {
		throw logic_error("Not implemented yet.");
	}
}

void SubRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	throw logic_error("Not implemented yet");
}

void SubRepresentation::pushBackSupportingRepresentation(AbstractRepresentation * supportingRep)
{
	if (supportingRep == nullptr) {
		throw invalid_argument("The supporting Representation cannot be null.");
	}

	// EPC
	supportingRep->pushBackSubRepresentation(this);

	// XML
	if (updateXml) {
		pushBackXmlSupportingRepresentation(supportingRep);
	}
}

AbstractRepresentation* SubRepresentation::getSupportingRepresentation(unsigned int index) const
{
	return static_cast<AbstractRepresentation*>(epcDocument->getDataObjectByUuid(getSupportingRepresentationUuid(index)));
}

std::string SubRepresentation::getSupportingRepresentationUuid(unsigned int index) const
{
	return getSupportingRepresentationDor(index)->UUID;
}

std::string SubRepresentation::getSupportingRepresentationTitle(unsigned int index) const
{
	return getSupportingRepresentationDor(index)->Title;
}

std::string SubRepresentation::getSupportingRepresentationContentType() const
{
	return getSupportingRepresentationDor(0)->ContentType;
}

