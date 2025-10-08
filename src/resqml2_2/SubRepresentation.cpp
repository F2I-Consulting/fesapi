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

#include <limits>
#include <sstream>
#include <stdexcept>

#include "../eml2/AbstractHdfProxy.h"
#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../resqml2/AbstractIjkGridRepresentation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* SubRepresentation::XML_NS = "resqml22";

void SubRepresentation::init(COMMON_NS::DataObjectRepository* repo, const string & guid, const string & title)
{
	gsoapProxy2_3 = soap_new_resqml22__SubRepresentation(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
}

SubRepresentation::SubRepresentation(COMMON_NS::DataObjectRepository* repo, const string & guid, const string & title)
{
	init(repo, guid, title);
}

SubRepresentation::SubRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const string & guid, const string & title)
{
	if (interp == nullptr) {
		throw invalid_argument("The interpretation of the subrepresentation cannot be null.");
	}

	init(interp->getRepository(), guid, title);

	// relationhsips
	setInterpretation(interp);
}

_resqml22__SubRepresentation* SubRepresentation::getSpecializedGsoapProxy() const
{
	if (isPartial()) {
		throw logic_error("Partial object");
	}

	return static_cast<_resqml22__SubRepresentation*>(gsoapProxy2_3);
}

void SubRepresentation::pushBackSubRepresentationPatch(gsoap_eml2_3::eml23__IndexableElement elementKind, uint64_t originIndex,
	unsigned int elementCountInSlowestDimension,
	unsigned int elementCountInMiddleDimension,
	unsigned int elementCountInFastestDimension)
{
	throw logic_error("Not implemented yet");
}

void SubRepresentation::pushBackRefToExistingDataset(gsoap_eml2_3::eml23__IndexableElement elementKind, uint64_t elementCount, const std::string & elementDataset,
	int64_t nullValue, EML2_NS::AbstractHdfProxy * proxy, const std::string & supportingRepDataset)
{
	throw logic_error("Not implemented yet");
}

void SubRepresentation::pushBackSubRepresentationPatch(gsoap_eml2_3::eml23__IndexableElement elementKind0, gsoap_eml2_3::eml23__IndexableElement elementKind1,
	uint64_t elementCount,
	uint64_t * elementIndices0, uint64_t * elementIndices1,
	EML2_NS::AbstractHdfProxy * proxy)
{
	throw logic_error("Not implemented yet");
}

COMMON_NS::DataObjectReference SubRepresentation::getHdfProxyDor() const
{
	throw logic_error("Not implemented yet");
}

gsoap_eml2_3::eml23__IndexableElement SubRepresentation::getElementKindOfPatch(uint64_t patchIndex, unsigned int elementIndicesIndex) const
{
	throw logic_error("Not implemented yet");
}

resqml22__SubRepresentationPatch* SubRepresentation::getSubRepresentationPatch(uint64_t patchIndex) const
{
	return getSpecializedGsoapProxy()->SubRepresentationPatch.at(patchIndex);
}

uint64_t SubRepresentation::getElementCountOfPatch(uint64_t patchIndex) const
{
	throw logic_error("Not implemented yet");
}

bool SubRepresentation::areElementIndicesPairwise(uint64_t patchIndex) const
{
	throw logic_error("Not implemented yet");
}

bool SubRepresentation::areElementIndicesBasedOnLattice(uint64_t patchIndex, unsigned int elementIndicesIndex) const
{
	throw logic_error("Not implemented yet");
}

int64_t SubRepresentation::getLatticeElementIndicesStartValue(uint64_t patchIndex, unsigned int elementIndicesIndex) const
{
	throw logic_error("Not implemented yet");
}

uint64_t SubRepresentation::getLatticeElementIndicesDimensionCount(uint64_t patchIndex, unsigned int elementIndicesIndex) const
{
	throw logic_error("Not implemented yet");
}

int64_t SubRepresentation::getLatticeElementIndicesOffsetValue(unsigned int latticeDimensionIndex, uint64_t patchIndex, unsigned int elementIndicesIndex) const
{
	throw logic_error("Not implemented yet");
}

uint64_t SubRepresentation::getLatticeElementIndicesOffsetCount(unsigned int latticeDimensionIndex, uint64_t patchIndex, unsigned int elementIndicesIndex) const
{
	throw logic_error("Not implemented yet");
}

void SubRepresentation::getElementIndicesOfPatch(uint64_t patchIndex, unsigned int elementIndicesIndex, uint64_t * elementIndices) const
{
	throw logic_error("Not implemented yet");
}

void SubRepresentation::getSupportingRepresentationIndicesOfPatch(uint64_t patchIndex, short * supportingRepresentationIndices) const
{
	throw logic_error("Not implemented yet");
}

uint64_t SubRepresentation::getPatchCount() const
{
	return getSpecializedGsoapProxy()->SubRepresentationPatch.size();
}

uint64_t SubRepresentation::getSupportingRepresentationCount() const
{
	throw logic_error("Not implemented yet");
}

COMMON_NS::DataObjectReference SubRepresentation::getSupportingRepresentationDor(uint64_t index) const
{
	throw logic_error("Not implemented yet");
}

void SubRepresentation::pushBackXmlSupportingRepresentation(RESQML2_NS::AbstractRepresentation const * supportingRep)
{
	throw logic_error("Not implemented yet");
}
