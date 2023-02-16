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

using namespace std;
using namespace RESQML2_NS;

void SubRepresentation::pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement elementKind, uint64_t elementCount, uint64_t * elementIndices, EML2_NS::AbstractHdfProxy * proxy, short * supportingRepIndices)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	std::string supportingRepDataset = "";
	ostringstream ossForHdfSupRep;
	if (supportingRepIndices != nullptr) {
		ossForHdfSupRep << "subrepresentation_supportingRepresentationIndices_patch" << getPatchCount();
		supportingRepDataset = getHdfGroup() + "/" + ossForHdfSupRep.str();
	}
	const std::string subRepDatasetName = "subrepresentation_elementIndices0_patch" + std::to_string(getPatchCount());

	// Arbitrarily set null value to -1 since it has no interest to write element index null value in this method
	pushBackRefToExistingDataset(elementKind, elementCount, getHdfGroup() + "/" + subRepDatasetName, -1, proxy, supportingRepDataset);

	// ************ HDF ************
	proxy->writeArrayNdOfUInt64Values(getHdfGroup(), subRepDatasetName, elementIndices, &elementCount, 1);
	if (supportingRepIndices != nullptr) {
		proxy->writeArrayNd(getHdfGroup(), ossForHdfSupRep.str(), COMMON_NS::AbstractObject::numericalDatatypeEnum::INT16, supportingRepIndices, &elementCount, 1);
	}
}

void SubRepresentation::pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement elementKind, uint64_t elementCount,
	EML2_NS::AbstractHdfProxy * proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const std::string datasetName = "subrepresentation_elementIndices0_patch" + std::to_string(getPatchCount());

	// HDF
	proxy->createArrayNd(getHdfGroup(),
		datasetName,
		COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT64,
		&elementCount, 1);

	pushBackRefToExistingDataset(elementKind, elementCount, getHdfGroup() + "/" + datasetName, -1, proxy, "");
}

void SubRepresentation::setElementIndices(uint64_t* elementIndices, 
	uint64_t elementCount,
	uint64_t offset,
	EML2_NS::AbstractHdfProxy* proxy,
	unsigned int patchIndex)
{
	if (patchIndex >= getPatchCount() && patchIndex != (numeric_limits<unsigned int>::max)()) {
		throw out_of_range("The subrepresentation patch is out of range");
	}

	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

	ostringstream oss;
	oss << "subrepresentation_elementIndices0_patch";
	if (patchIndex == (numeric_limits<unsigned int>::max)()) {
		oss << getPatchCount() - 1;
	}
	else {
		oss << patchIndex;
	}

	// HDF
	proxy->writeArrayNdSlab(getHdfGroup(),
		oss.str(),
		COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT64,
		elementIndices,
		&elementCount,
		&offset,
		1);
}

void SubRepresentation::loadTargetRelationships()
{
	AbstractRepresentation::loadTargetRelationships();

	// Supporting representation
	const uint64_t supRepCount = getSupportingRepresentationCount();
	for (uint64_t supRepIndex = 0; supRepIndex < supRepCount; ++supRepIndex) {
		COMMON_NS::DataObjectReference dor = getSupportingRepresentationDor(supRepIndex);
		convertDorIntoRel<RESQML2_NS::AbstractRepresentation>(dor);
	}
}

uint64_t SubRepresentation::getXyzPointCountOfPatch(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	if (getElementKindOfPatch(patchIndex, 0) == gsoap_eml2_3::resqml22__IndexableElement::nodes) {
		return getElementCountOfPatch(patchIndex);
	}
	else {
		throw logic_error("Not implemented yet.");
	}
}

void SubRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double *) const
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

AbstractRepresentation* SubRepresentation::getSupportingRepresentation(uint64_t index) const
{
	return static_cast<AbstractRepresentation*>(repository->getDataObjectByUuid(getSupportingRepresentationDor(index).getUuid()));
}
