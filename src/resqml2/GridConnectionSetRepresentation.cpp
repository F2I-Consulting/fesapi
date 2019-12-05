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
#include <stdexcept>

#include <hdf5.h>

#include "../resqml2_0_1/FaultInterpretation.h"
#include "../common/AbstractHdfProxy.h"
#include "AbstractLocal3dCrs.h"
#include "../resqml2_0_1/UnstructuredGridRepresentation.h"
#include "../resqml2_0_1/AbstractIjkGridRepresentation.h"
#include "../resqml2_0_1/StructuralOrganizationInterpretation.h"

using namespace std;
using namespace RESQML2_NS;
using namespace gsoap_resqml2_0_1;

const char* GridConnectionSetRepresentation::XML_TAG = "GridConnectionSetRepresentation";

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
		gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getSupportingGridRepresentationDor(i);
		RESQML2_NS::AbstractGridRepresentation* supportingGridRep = getRepository()->getDataObjectByUuid<RESQML2_NS::AbstractGridRepresentation>(dor->UUID);
		if (supportingGridRep == nullptr) { // partial transfer
			getRepository()->createPartial(dor);
			supportingGridRep = getRepository()->getDataObjectByUuid<RESQML2_NS::AbstractGridRepresentation>(dor->UUID);
			if (supportingGridRep == nullptr) {
				throw invalid_argument("The DOR looks invalid.");
			}
		}
		getRepository()->addRelationship(this, supportingGridRep);
	}

	if (isAssociatedToInterpretations()) {
		unsigned int interpCount = getInterpretationCount();
		for (unsigned int i = 0; i < interpCount; ++i) {
			RESQML2_NS::AbstractFeatureInterpretation* interp = getRepository()->getDataObjectByUuid<AbstractFeatureInterpretation>(getInterpretationUuidFromIndex(i));
			if (interp == nullptr) {
				throw logic_error("The referenced interpretation is either not a resqml grid interpretation or it is partial and not implemented yet");
			}
			getRepository()->addRelationship(this, interp);
		}
	}
}

void GridConnectionSetRepresentation::setCellIndexPairs(ULONG64 cellIndexPairCount, ULONG64 * cellIndexPair, ULONG64 cellIndexPairNullValue, COMMON_NS::AbstractHdfProxy * proxy, unsigned short gridIndexPairNullValue, unsigned short * gridIndexPair)
{
	if (cellIndexPairNullValue > (std::numeric_limits<LONG64>::max)()) {
		throw std::invalid_argument("The XML null value cannot be greater than a 64 bits signed integer cause of gsoap mappings");
	}
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const std::string uuid = getUuid();
	setCellIndexPairsUsingExistingDataset(cellIndexPairCount, "/RESQML/" + uuid + "/CellIndexPairs", cellIndexPairNullValue, proxy, gridIndexPairNullValue, gridIndexPair != nullptr ? "/RESQML/" + getUuid() + "/GridIndexPairs" : "");

	// ************ HDF ************		
	hsize_t numValues[] = { cellIndexPairCount, 2 };
	proxy->writeArrayNd(uuid, "CellIndexPairs", H5T_NATIVE_ULLONG, cellIndexPair, numValues, 2);
	if (gridIndexPair != nullptr) {
		proxy->writeArrayNd(uuid, "GridIndexPairs", H5T_NATIVE_USHORT, gridIndexPair, numValues, 2);
	}
}

ULONG64 GridConnectionSetRepresentation::getXyzPointCountOfPatch(const unsigned int &) const
{
	throw logic_error("Not implemented yet");
}

void GridConnectionSetRepresentation::getXyzPointsOfPatch(const unsigned int &, double *) const
{
	throw logic_error("Not implemented yet");
}

AbstractFeatureInterpretation * GridConnectionSetRepresentation::getInterpretationFromIndex(const unsigned int & interpretationIndex) const
{
	return static_cast<AbstractFeatureInterpretation*>(repository->getDataObjectByUuid(getInterpretationUuidFromIndex(interpretationIndex)));
}

AbstractGridRepresentation* GridConnectionSetRepresentation::getSupportingGridRepresentation(unsigned int index) const 
{
	return static_cast<AbstractGridRepresentation*>(repository->getDataObjectByUuid(getSupportingGridRepresentationUuid(index)));
}

std::string GridConnectionSetRepresentation::getSupportingGridRepresentationUuid(unsigned int index) const
{
	return getSupportingGridRepresentationDor(index)->UUID;
}

std::string GridConnectionSetRepresentation::getSupportingGridRepresentationTitle(unsigned int index) const
{
	return getSupportingGridRepresentationDor(index)->Title;
}

std::string GridConnectionSetRepresentation::getSupportingGridRepresentationContentType(unsigned int index) const
{
	return getSupportingGridRepresentationDor(index)->ContentType;
}
