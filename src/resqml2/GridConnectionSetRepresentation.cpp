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
#include "GridConnectionSetRepresentation.h"

#include <algorithm>

#include <hdf5.h>

#include "../eml2/AbstractHdfProxy.h"

#include "AbstractFeatureInterpretation.h"
#include "AbstractGridRepresentation.h"

using namespace std;
using namespace RESQML2_NS;
using namespace gsoap_resqml2_0_1;

void GridConnectionSetRepresentation::pushBackSupportingGridRepresentation(AbstractGridRepresentation * supportingGridRep)
{
	if (supportingGridRep == nullptr) {
		throw invalid_argument("The supporting Grid Representation cannot be null.");
	}

	getRepository()->addRelationship(this, supportingGridRep);

	pushBackXmlSupportingGridRepresentation(supportingGridRep);
}

void GridConnectionSetRepresentation::pushBackInterpretation(AbstractFeatureInterpretation* interp)
{
	if (interp == nullptr) {
		throw invalid_argument("The interpretation to push back cannot be null.");
	}

	getRepository()->addRelationship(this, interp);

	pushBackXmlInterpretation(interp);
}

void GridConnectionSetRepresentation::loadTargetRelationships()
{
	AbstractRepresentation::loadTargetRelationships();

	// Supporting grid representation
	const uint64_t supportingGridCount = getSupportingGridRepresentationCount();
	for (uint64_t i = 0; i < supportingGridCount; ++i) {
		COMMON_NS::DataObjectReference dor = getSupportingGridRepresentationDor(i);
		if (!dor.isEmpty()) {
			convertDorIntoRel(dor);
		}
	}

	if (isAssociatedToInterpretations()) {
		const uint64_t interpCount = getInterpretationCount();
		for (uint64_t i = 0; i < interpCount; ++i) {
			COMMON_NS::DataObjectReference dor = getInterpretationDorFromIndex(i);
			if (!dor.isEmpty()) {
				convertDorIntoRel(dor);
			}
		}
	}
}

void GridConnectionSetRepresentation::setCellIndexPairs(uint64_t cellIndexPairCount, int64_t const* cellIndexPair, int64_t cellIndexPairNullValue, EML2_NS::AbstractHdfProxy * proxy, uint16_t gridIndexPairNullValue, uint16_t const* gridIndexPair)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	// ************ HDF ************		
	hsize_t numValues[2] = { cellIndexPairCount, 2 };
	proxy->writeArrayNd(getHdfGroup(), "CellIndexPairs", COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64, cellIndexPair, numValues, 2);
	if (gridIndexPair != nullptr) {
		proxy->writeArrayNd(getHdfGroup(), "GridIndexPairs", COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT16, gridIndexPair, numValues, 2);
	}

	setCellIndexPairsUsingExistingDataset(cellIndexPairCount, getHdfGroup() + "/CellIndexPairs", cellIndexPairNullValue, proxy, gridIndexPairNullValue, gridIndexPair != nullptr ? getHdfGroup() + "/GridIndexPairs" : "");
}

void GridConnectionSetRepresentation::setLocalFacePerCellIndexPairs(int const* localFacePerCellIndexPair, int nullValue, EML2_NS::AbstractHdfProxy * proxy)
{
	if (gsoapProxy2_0_1 != nullptr && nullValue != -1) {
		throw invalid_argument("The null value must be -1 in RESQML2.0.1");
	}
	const hsize_t cellIndexPairCount = getCellIndexPairCount();
	if (cellIndexPairCount == 0) {
		throw logic_error("You must set some cell connections before to set local face connections");
	}

	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	// ************ HDF ************		
	hsize_t numValues[2] = { cellIndexPairCount, 2 };
	proxy->writeArrayNd(getHdfGroup(), "LocalFacePerCellIndexPairs", COMMON_NS::AbstractObject::numericalDatatypeEnum::INT32, localFacePerCellIndexPair, numValues, 2);

	setLocalFacePerCellIndexPairsUsingExistingDataset(getHdfGroup() + "/LocalFacePerCellIndexPairs", nullValue, proxy);
}

uint64_t GridConnectionSetRepresentation::getXyzPointCountOfPatch(uint64_t) const
{
	throw logic_error("Not implemented yet");
}

void GridConnectionSetRepresentation::getXyzPointsOfPatch(uint64_t, double *) const
{
	throw logic_error("Not implemented yet");
}

AbstractFeatureInterpretation * GridConnectionSetRepresentation::getInterpretationFromIndex(uint64_t interpretationIndex) const
{
	return repository->getDataObjectByUuid<AbstractFeatureInterpretation>(getInterpretationUuidFromIndex(interpretationIndex));
}

AbstractGridRepresentation* GridConnectionSetRepresentation::getSupportingGridRepresentation(uint64_t index) const
{
	return repository->getDataObjectByUuid<AbstractGridRepresentation>(getSupportingGridRepresentationDor(index).getUuid());
}
