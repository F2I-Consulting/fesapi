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

#include <hdf5.h>

#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_NS;

const char* SubRepresentation::XML_TAG = "SubRepresentation";

void SubRepresentation::pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement elementKind, ULONG64 elementCount, ULONG64 * elementIndices, EML2_NS::AbstractHdfProxy * proxy, short * supportingRepIndices)
{
	std::string supportingRepDataset = "";
	ostringstream ossForHdfSupRep;
	if (supportingRepIndices != nullptr) {
		ossForHdfSupRep << "subrepresentation_supportingRepresentationIndices_patch" << getPatchCount();
		supportingRepDataset = getHdfGroup() + "/" + ossForHdfSupRep.str();
	}
	ostringstream ossForHdf;
	ossForHdf << "subrepresentation_elementIndices0_patch" << getPatchCount();

	pushBackRefToExistingDataset(elementKind, elementCount, getHdfGroup() + "/" + ossForHdf.str(), (std::numeric_limits<unsigned int>::max)(), proxy, supportingRepDataset);

	// ************ HDF ************		
	hsize_t numValues = elementCount;
	proxy->writeArrayNdOfGSoapULong64Values(getHdfGroup(), ossForHdf.str(), elementIndices, &numValues, 1);
	if (supportingRepIndices != nullptr) {
		proxy->writeArrayNd(getHdfGroup(), ossForHdfSupRep.str(), H5T_NATIVE_SHORT, supportingRepIndices, &numValues, 1);
	}
}

void SubRepresentation::loadTargetRelationships()
{
	AbstractRepresentation::loadTargetRelationships();

	// Supporting representation
	const unsigned int supRepCount = getSupportingRepresentationCount();
	for (unsigned int supRepIndex = 0; supRepIndex < supRepCount; ++supRepIndex) {
		COMMON_NS::DataObjectReference dor = getSupportingRepresentationDor(supRepIndex);
		convertDorIntoRel<RESQML2_NS::AbstractRepresentation>(dor);
	}
}

ULONG64 SubRepresentation::getXyzPointCountOfPatch(unsigned int patchIndex) const
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

AbstractRepresentation* SubRepresentation::getSupportingRepresentation(unsigned int index) const
{
	return static_cast<AbstractRepresentation*>(repository->getDataObjectByUuid(getSupportingRepresentationDor(index).getUuid()));
}
