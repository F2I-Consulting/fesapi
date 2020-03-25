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
#include "SubRepresentation.h"

#include <sstream>
#include <stdexcept>

#include "AbstractFeatureInterpretation.h"
#include "../eml2/AbstractHdfProxy.h"
#include "../resqml2_0_1/UnstructuredGridRepresentation.h"
#include "AbstractIjkGridRepresentation.h"

using namespace std;
using namespace RESQML2_NS;

const char* SubRepresentation::XML_TAG = "SubRepresentation";

void SubRepresentation::loadTargetRelationships()
{
	AbstractRepresentation::loadTargetRelationships();

	// Supporting representation
	const unsigned int supRepCount = getSupportingRepresentationCount();
	for (unsigned int supRepIndex = 0; supRepIndex < supRepCount; ++supRepIndex) {
		gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getSupportingRepresentationDor(supRepIndex);
		RESQML2_NS::AbstractRepresentation* supportingRep = getRepository()->getDataObjectByUuid<RESQML2_NS::AbstractRepresentation>(dor->UUID);
		if (supportingRep == nullptr) { // partial transfer
			getRepository()->createPartial(dor);
			supportingRep = getRepository()->getDataObjectByUuid<RESQML2_NS::AbstractRepresentation>(dor->UUID);
			if (supportingRep == nullptr) {
				throw invalid_argument("The DOR looks invalid.");
			}
		}
		getRepository()->addRelationship(this, supportingRep);
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

void SubRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double *) const
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

	getRepository()->addRelationship(this, supportingRep);

	pushBackXmlSupportingRepresentation(supportingRep);
}

AbstractRepresentation* SubRepresentation::getSupportingRepresentation(unsigned int index) const
{
	return static_cast<AbstractRepresentation*>(repository->getDataObjectByUuid(getSupportingRepresentationUuid(index)));
}

std::string SubRepresentation::getSupportingRepresentationUuid(unsigned int index) const
{
	return getSupportingRepresentationDor(index)->UUID;
}

std::string SubRepresentation::getSupportingRepresentationTitle(unsigned int index) const
{
	return getSupportingRepresentationDor(index)->Title;
}

std::string SubRepresentation::getSupportingRepresentationContentType(unsigned int index) const
{
	return getSupportingRepresentationDor(index)->ContentType;
}
