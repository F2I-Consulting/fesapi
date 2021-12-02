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

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../resqml2/AbstractIjkGridRepresentation.h"

#include "../resqml2_2/GenericFeatureInterpretation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

void SubRepresentation::init(COMMON_NS::DataObjectRepository* repo, const string & guid, const string & title, gsoap_eml2_3::eml23__IndexableElement elementKind)
{
	gsoapProxy2_3 = soap_new_resqml22__SubRepresentation(repo->getGsoapContext());
	static_cast<_resqml22__SubRepresentation*>(gsoapProxy2_3)->IndexableElement = elementKind;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(this);
}

SubRepresentation::SubRepresentation(COMMON_NS::DataObjectRepository* repo, const string & guid, const string & title, gsoap_eml2_3::eml23__IndexableElement elementKind)
{
	init(repo, guid, title, elementKind);
	setInterpretation(repo->createPartial<RESQML2_2_NS::GenericFeatureInterpretation>("", "Unknown interp"));
}

SubRepresentation::SubRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const string & guid, const string & title, gsoap_eml2_3::eml23__IndexableElement elementKind)
{
	if (interp == nullptr) {
		throw invalid_argument("The interpretation of the subrepresentation cannot be null.");
	}

	init(interp->getRepository(), guid, title, elementKind);

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

COMMON_NS::DataObjectReference SubRepresentation::getHdfProxyDor() const
{
	_resqml22__SubRepresentation* rep = getSpecializedGsoapProxy();

	return !rep->SubRepresentationPatch.empty() && rep->SubRepresentationPatch[0]->Indices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray
		? COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__IntegerExternalArray*>(rep->SubRepresentationPatch[0]->Indices)->Values->ExternalDataArrayPart[0]))
		: COMMON_NS::DataObjectReference();
}

void SubRepresentation::pushBackSubRepresentationPatch(uint64_t originIndex,
	unsigned int elementCountInSlowestDimension,
	unsigned int elementCountInMiddleDimension,
	unsigned int elementCountInFastestDimension, RESQML2_NS::AbstractIjkGridRepresentation* ijkGrid)
{
	_resqml22__SubRepresentation* rep = getSpecializedGsoapProxy();

	resqml22__SubRepresentationPatch* patch = soap_new_resqml22__SubRepresentationPatch(gsoapProxy2_3->soap);

	// XML
	rep->SubRepresentationPatch.push_back(patch);
	patch->Count = elementCountInSlowestDimension * elementCountInMiddleDimension * elementCountInFastestDimension;

	eml23__IntegerLatticeArray * integerArray = soap_new_eml23__IntegerLatticeArray(gsoapProxy2_3->soap);
	patch->Indices = integerArray;
	integerArray->StartValue = originIndex;

	eml23__IntegerConstantArray * offset = soap_new_eml23__IntegerConstantArray(gsoapProxy2_3->soap);
	offset->Count = elementCountInSlowestDimension - 1;
	offset->Value = 1;
	integerArray->Offset.push_back(offset);

	offset = soap_new_eml23__IntegerConstantArray(gsoapProxy2_3->soap);
	offset->Count = elementCountInMiddleDimension - 1;
	offset->Value = 1;
	integerArray->Offset.push_back(offset);

	offset = soap_new_eml23__IntegerConstantArray(gsoapProxy2_3->soap);
	offset->Count = elementCountInFastestDimension - 1;
	offset->Value = 1;
	integerArray->Offset.push_back(offset);

	patch->SupportingRepresentation.push_back(ijkGrid->newEml23Reference());
	getRepository()->addRelationship(this, ijkGrid);
}

void SubRepresentation::pushBackSubRepresentationPatch(uint64_t elementCount, int64_t* elementIndices,
	RESQML2_NS::AbstractRepresentation* supportingRep, EML2_NS::AbstractHdfProxy* proxy)
{
	const std::string elementDataset = "indices_patch" + std::to_string(getPatchCount());

	// HDF
	const hsize_t numValues = elementCount;
	proxy->writeArrayNdOfInt64Values(getHdfGroup(), elementDataset, elementIndices, &numValues, 1);

	pushBackRefToExistingDataset(elementCount, getHdfGroup() + "/" + elementDataset, -1, supportingRep, proxy);
}

void SubRepresentation::pushBackRefToExistingDataset(uint64_t elementCount, const std::string& elementDataset,
	int64_t nullValue, RESQML2_NS::AbstractRepresentation* supportingRep, EML2_NS::AbstractHdfProxy* proxy)
{
	if (elementCount == 0) {
		throw invalid_argument("The count of element cannot be zero.");
	}
	if (elementDataset.empty()) {
		throw invalid_argument("The dataset owning the elements cannot have an empty name.");
	}
	if (supportingRep == nullptr) {
		throw invalid_argument("The supporting representation cannot be null.");
	}

	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

	resqml22__SubRepresentationPatch* patch = soap_new_resqml22__SubRepresentationPatch(gsoapProxy2_3->soap);

	// XML
	_resqml22__SubRepresentation* rep = getSpecializedGsoapProxy();
	patch->Count = elementCount;

	eml23__IntegerExternalArray * integerArray = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	integerArray->NullValue = nullValue;
	integerArray->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	const std::string actualDatasetName = elementDataset.empty()
		? getHdfGroup() + "/indices_patch" + std::to_string(getPatchCount())
		: elementDataset;
	integerArray->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(actualDatasetName, proxy->getElementCount(actualDatasetName), proxy));
	patch->Indices = integerArray;

	patch->SupportingRepresentation.push_back(supportingRep->newEml23Reference());
	getRepository()->addRelationship(this, supportingRep);

	rep->SubRepresentationPatch.push_back(patch);
}

resqml22__SubRepresentationPatch* SubRepresentation::getSubRepresentationPatch(uint64_t index) const
{
	_resqml22__SubRepresentation const* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() > index) {
		return rep->SubRepresentationPatch[index];
	}

	throw out_of_range("The patch does not exist at this index.");
}

uint64_t SubRepresentation::getElementCountOfPatch(uint64_t patchIndex) const
{
	return getSubRepresentationPatch(patchIndex)->Count;
}

bool SubRepresentation::areElementIndicesBasedOnLattice(uint64_t patchIndex) const
{
	return getSubRepresentationPatch(patchIndex)->Indices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerLatticeArray;
}

int64_t SubRepresentation::getLatticeElementIndicesStartValue(uint64_t patchIndex) const
{
	_resqml22__SubRepresentation* rep = getSpecializedGsoapProxy();

	if (!areElementIndicesBasedOnLattice(patchIndex)) {
		throw invalid_argument("The element indices are not based on a lattice.");
	}

	eml23__IntegerLatticeArray* lattice = static_cast<eml23__IntegerLatticeArray*>(rep->SubRepresentationPatch[patchIndex]->Indices);
	return lattice->StartValue;
}

uint64_t SubRepresentation::getLatticeElementIndicesDimensionCount(uint64_t patchIndex) const
{
	_resqml22__SubRepresentation const * rep = getSpecializedGsoapProxy();

	if (!areElementIndicesBasedOnLattice(patchIndex)) {
		throw invalid_argument("The element indices are not based on a lattice.");
	}

	eml23__IntegerLatticeArray* lattice = static_cast<eml23__IntegerLatticeArray*>(rep->SubRepresentationPatch[patchIndex]->Indices);
	return lattice->Offset.size();
}

int64_t SubRepresentation::getLatticeElementIndicesOffsetValue(unsigned int latticeDimensionIndex, uint64_t patchIndex) const
{
	if (!areElementIndicesBasedOnLattice(patchIndex)) {
		throw invalid_argument("The element indices are not based on a lattice.");
	}

	eml23__IntegerLatticeArray* lattice = static_cast<eml23__IntegerLatticeArray*>(getSpecializedGsoapProxy()->SubRepresentationPatch[patchIndex]->Indices);
	if (lattice->Offset.size() <= latticeDimensionIndex) {
		throw out_of_range("The lattice dimension index is out of range.");
	}

	return lattice->Offset[latticeDimensionIndex]->Value;
}

uint64_t SubRepresentation::getLatticeElementIndicesOffsetCount(unsigned int latticeDimensionIndex, uint64_t patchIndex) const
{
	if (!areElementIndicesBasedOnLattice(patchIndex)) {
		throw invalid_argument("The element indices are not based on a lattice.");
	}

	eml23__IntegerLatticeArray* lattice = static_cast<eml23__IntegerLatticeArray*>(getSpecializedGsoapProxy()->SubRepresentationPatch[patchIndex]->Indices);
	if (lattice->Offset.size() <= latticeDimensionIndex) {
		throw out_of_range("The lattice dimension index is out of range.");
	}

	return lattice->Offset[latticeDimensionIndex]->Count;
}

int64_t SubRepresentation::getElementIndicesOfPatch(uint64_t patchIndex, int64_t * elementIndices) const
{
	_resqml22__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() <= patchIndex) {
		throw out_of_range("The patch does not exist at this index.");
	}

	if (rep->SubRepresentationPatch[patchIndex]->Indices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		eml23__ExternalDataArrayPart const * daPart = static_cast<eml23__IntegerExternalArray*>(rep->SubRepresentationPatch[patchIndex]->Indices)->Values->ExternalDataArrayPart[0];
		getOrCreateHdfProxyFromDataArrayPart(daPart)->readArrayNdOfInt64Values(daPart->PathInExternalFile, elementIndices);
		return static_cast<eml23__IntegerExternalArray*>(rep->SubRepresentationPatch[patchIndex]->Indices)->NullValue;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

uint64_t SubRepresentation::getPatchCount() const
{
	return getSpecializedGsoapProxy()->SubRepresentationPatch.size();
}

COMMON_NS::DataObjectReference SubRepresentation::getSupportingRepresentationOfPatchDor(uint64_t patchIndex) const
{
	const uint64_t supRepCount = getPatchCount();

	if (supRepCount == 0) {
		throw invalid_argument("No supporting rep");
	}
	if (patchIndex >= supRepCount) {
		throw out_of_range("The index \"" +std::to_string(patchIndex) + "\" of the supporting representation is out of range.");
	}

	return COMMON_NS::DataObjectReference(getSpecializedGsoapProxy()->SubRepresentationPatch[patchIndex]->SupportingRepresentation[0]);
}

void SubRepresentation::loadTargetRelationships()
{
	AbstractRepresentation::loadTargetRelationships();

	// Supporting representation
	const uint64_t patchCount = getPatchCount();
	for (uint64_t patchIndex = 0; patchIndex < patchCount; ++patchIndex) {
		COMMON_NS::DataObjectReference dor = getSupportingRepresentationOfPatchDor(patchIndex);
		convertDorIntoRel<RESQML2_NS::AbstractRepresentation>(dor);
	}
}
