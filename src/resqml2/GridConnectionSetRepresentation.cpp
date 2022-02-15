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
	unsigned int supportingGridCount = getSupportingGridRepresentationCount();
	for (unsigned int i = 0; i < supportingGridCount; ++i) {
		COMMON_NS::DataObjectReference dor = getSupportingGridRepresentationDor(i);
		if (!dor.isEmpty()) {
			convertDorIntoRel(dor);
		}
	}

	if (isAssociatedToInterpretations()) {
		unsigned int interpCount = getInterpretationCount();
		for (unsigned int i = 0; i < interpCount; ++i) {
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
	proxy->writeArrayNd(getHdfGroup(), "CellIndexPairs", H5T_NATIVE_INT64, cellIndexPair, numValues, 2);
	if (gridIndexPair != nullptr) {
		proxy->writeArrayNd(getHdfGroup(), "GridIndexPairs", H5T_NATIVE_UINT16, gridIndexPair, numValues, 2);
	}

	setCellIndexPairsUsingExistingDataset(cellIndexPairCount, getHdfGroup() + "/CellIndexPairs", cellIndexPairNullValue, proxy, gridIndexPairNullValue, gridIndexPair != nullptr ? getHdfGroup() + "/GridIndexPairs" : "");
}

void GridConnectionSetRepresentation::setLocalFacePerCellIndexPairs(uint64_t cellIndexPairCount, int const* localFacePerCellIndexPair, int nullValue, EML2_NS::AbstractHdfProxy * proxy)
{
	if (gsoapProxy2_0_1 != nullptr && nullValue != -1) {
		throw invalid_argument("The null value must be -1 in RESQML2.0.1");
	}

	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	// ************ HDF ************		
	hsize_t numValues[2] = { cellIndexPairCount,2 };
	proxy->writeArrayNd(getHdfGroup(), "LocalFacePerCellIndexPairs", H5T_NATIVE_INT, localFacePerCellIndexPair, numValues, 2);

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

AbstractFeatureInterpretation * GridConnectionSetRepresentation::getInterpretationFromIndex(unsigned int interpretationIndex) const
{
	return repository->getDataObjectByUuid<AbstractFeatureInterpretation>(getInterpretationUuidFromIndex(interpretationIndex));
}

AbstractGridRepresentation* GridConnectionSetRepresentation::getSupportingGridRepresentation(unsigned int index) const 
{
	return repository->getDataObjectByUuid<AbstractGridRepresentation>(getSupportingGridRepresentationDor(index).getUuid());
}
