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

#include <hdf5.h>

#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_NS;

void SubRepresentation::pushBackSubRepresentationPatch(uint64_t elementCount, RESQML2_NS::AbstractRepresentation* supportingRep,
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

	pushBackRefToExistingDataset(elementCount, getHdfGroup() + "/" + datasetName, -1, supportingRep, proxy);
}

void SubRepresentation::setElementIndices(uint64_t const* elementIndices, 
	uint64_t elementCount,
	uint64_t offset,
	EML2_NS::AbstractHdfProxy* proxy,
	uint64_t patchIndex)
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

	// HDF
	proxy->writeArrayNdSlab(getHdfGroup(),
		"subrepresentation_elementIndices0_patch" + std::to_string(patchIndex == (numeric_limits<uint64_t>::max)() ? getPatchCount() - 1 : patchIndex),
		COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT64,
		elementIndices,
		&elementCount,
		&offset,
		1);
}

uint64_t SubRepresentation::getXyzPointCountOfPatch(uint64_t patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	if (getElementKind() == gsoap_eml2_3::eml23__IndexableElement::nodes) {
		return getElementCountOfPatch(patchIndex);
	}
	else {
		throw logic_error("Not implemented yet.");
	}
}

void SubRepresentation::getXyzPointsOfPatch(uint64_t patchIndex, double *) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	throw logic_error("Not implemented yet");
}

AbstractRepresentation* SubRepresentation::getSupportingRepresentationOfPatch(uint64_t patchIndex) const
{
	return getRepository()->getDataObjectByUuid<AbstractRepresentation>(getSupportingRepresentationOfPatchDor(patchIndex).getUuid());
}
