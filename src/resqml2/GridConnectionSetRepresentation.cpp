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
#include "resqml2/GridConnectionSetRepresentation.h"

#include <algorithm>
#if defined(__gnu_linux__) || defined(__APPLE__) 
#include <stdexcept>
#endif 

#include "hdf5.h"

#include "resqml2_0_1/FaultInterpretation.h"
#include "common/AbstractHdfProxy.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/AbstractIjkGridRepresentation.h"
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"

using namespace std;
using namespace epc;
using namespace RESQML2_NS;
using namespace gsoap_resqml2_0_1;

const char* GridConnectionSetRepresentation::XML_TAG = "GridConnectionSetRepresentation";

std::string GridConnectionSetRepresentation::getXmlTag() const
{
	return XML_TAG;
}

vector<Relationship> GridConnectionSetRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractRepresentation::getAllEpcRelationships();

	const unsigned int supportingGridCount = getSupportingGridRepresentationCount();
	for (unsigned int i = 0; i < supportingGridCount; ++i)
	{
		AbstractGridRepresentation* grid = getSupportingGridRepresentation(i);
		Relationship relSupportingGrid(grid->getPartNameInEpcDocument(), "", grid->getUuid());
		relSupportingGrid.setDestinationObjectType();
		result.push_back(relSupportingGrid);
	}
    
	const unsigned int interpCount = getInterpretationCount();
	for (unsigned int i = 0; i < interpCount; ++i)
	{
		AbstractFeatureInterpretation* interp = getInterpretationFromIndex(i);
		Relationship relInterp(interp->getPartNameInEpcDocument(), "", interp->getUuid());
		relInterp.setDestinationObjectType();
		result.push_back(relInterp);
	}

	return result;
}

void GridConnectionSetRepresentation::pushBackSupportingGridRepresentation(AbstractGridRepresentation * supportingGridRep)
{
	if (supportingGridRep == nullptr) {
		throw invalid_argument("The supporting Grid Representation cannot be null.");
	}

	// EPC
	supportingGridRep->gridConnectionSetRepresentationSet.push_back(this);

	// XML
	if (updateXml) {
		pushBackXmlSupportingGridRepresentation(supportingGridRep);
	}
}

void GridConnectionSetRepresentation::pushBackInterpretation(AbstractFeatureInterpretation* interp)
{
	if (interp == nullptr) {
		throw invalid_argument("The interpretation to push back cannot be null.");
	}

	if (std::find(interp->gridConnectionSetRepresentationSet.begin(), interp->gridConnectionSetRepresentationSet.end(), this) == interp->gridConnectionSetRepresentationSet.end()) {
		interp->gridConnectionSetRepresentationSet.push_back(this);
	}

	if (updateXml) {
		pushBackXmlInterpretation(interp);
	}
}

void GridConnectionSetRepresentation::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	AbstractRepresentation::importRelationshipSetFromEpc(epcDoc);

	// Supporting grid representation
	unsigned int supportingGridCount = getSupportingGridRepresentationCount();
	for (unsigned int i = 0; i < supportingGridCount; ++i) {
		gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getSupportingGridRepresentationDor(i);
		RESQML2_NS::AbstractGridRepresentation* supportingGridRep = epcDoc->getResqmlAbstractObjectByUuid<RESQML2_NS::AbstractGridRepresentation>(dor->UUID);
		if (supportingGridRep == nullptr) { // partial transfer
			getEpcDocument()->createPartial(dor);
			supportingGridRep = getEpcDocument()->getResqmlAbstractObjectByUuid<RESQML2_NS::AbstractGridRepresentation>(dor->UUID);
		}
		if (supportingGridRep == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
		updateXml = false;
		pushBackSupportingGridRepresentation(supportingGridRep);
		updateXml = true;
	}

	if (isAssociatedToInterpretations()) {
		updateXml = false;
		unsigned int interpCount = getInterpretationCount();
		for (unsigned int i = 0; i < interpCount; ++i) {
			RESQML2_NS::AbstractFeatureInterpretation* interp = epcDocument->getResqmlAbstractObjectByUuid<AbstractFeatureInterpretation>(getInterpretationUuidFromIndex(i));
			if (interp == nullptr) {
				throw logic_error("The referenced interpretation is either not a resqml grid interpretation or it is partial and not implemented yet");
			}
			else {
				pushBackInterpretation(interp);
			}
		}
		updateXml = true;
	}
}

void GridConnectionSetRepresentation::setCellIndexPairs(const ULONG64 & cellIndexPairCount, ULONG64 * cellIndexPair, const LONG64 & nullValue, COMMON_NS::AbstractHdfProxy * proxy, unsigned short * gridIndexPair)
{
	const std::string uuid = getUuid();
	setCellIndexPairsUsingExistingDataset(cellIndexPairCount, "/RESQML/" + getUuid() + "/CellIndexPairs", nullValue, proxy, gridIndexPair != nullptr ? "/RESQML/" + getUuid() + "/GridIndexPairs" : "");

	// ************ HDF ************		
	hsize_t numValues[] = { cellIndexPairCount, 2 };
	hdfProxy->writeArrayNd(uuid, "CellIndexPairs", H5T_NATIVE_ULLONG, cellIndexPair, numValues, 2);
	if (gridIndexPair != nullptr) {
		hdfProxy->writeArrayNd(uuid, "GridIndexPairs", H5T_NATIVE_USHORT, gridIndexPair, numValues, 2);
	}
}

ULONG64 GridConnectionSetRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	throw logic_error("Not implemented yet");
}

void GridConnectionSetRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	throw logic_error("Not implemented yet");
}

AbstractFeatureInterpretation * GridConnectionSetRepresentation::getInterpretationFromIndex(const unsigned int & interpretationIndex) const
{
	return static_cast<AbstractFeatureInterpretation*>(epcDocument->getResqmlAbstractObjectByUuid(getInterpretationUuidFromIndex(interpretationIndex)));
}

AbstractGridRepresentation* GridConnectionSetRepresentation::getSupportingGridRepresentation(unsigned int index) const 
{
	return static_cast<AbstractGridRepresentation*>(epcDocument->getResqmlAbstractObjectByUuid(getSupportingGridRepresentationUuid(index)));
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

