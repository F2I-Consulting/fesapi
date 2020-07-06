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
#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../resqml2/AbstractIjkGridRepresentation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

void SubRepresentation::init(COMMON_NS::DataObjectRepository* repo, const string & guid, const string & title)
{
	gsoapProxy2_3 = soap_new_resqml22__SubRepresentation(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addOrReplaceDataObject(this);
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

void SubRepresentation::pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement elementKind, ULONG64 originIndex,
	unsigned int elementCountInSlowestDimension,
	unsigned int elementCountInMiddleDimension,
	unsigned int elementCountInFastestDimension)
{
	_resqml22__SubRepresentation* rep = getSpecializedGsoapProxy();

	resqml22__SubRepresentationPatch* patch = soap_new_resqml22__SubRepresentationPatch(gsoapProxy2_3->soap);

	// XML
	rep->SubRepresentationPatch.push_back(patch);
	patch->Count = elementCountInSlowestDimension * elementCountInMiddleDimension * elementCountInFastestDimension;
	resqml22__ElementIndices* elements = soap_new_resqml22__ElementIndices(gsoapProxy2_3->soap);
	patch->ElementIndices.push_back(elements);
	elements->__ElementIndices_sequence = soap_new___resqml22__ElementIndices_sequence(gsoapProxy2_3->soap);
	elements->__ElementIndices_sequence->IndexableElement = elementKind;

	eml23__IntegerLatticeArray * integerArray = soap_new_eml23__IntegerLatticeArray(gsoapProxy2_3->soap);
	elements->__ElementIndices_sequence->Indices = integerArray;
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
}

void SubRepresentation::pushBackRefToExistingDataset(gsoap_eml2_3::resqml22__IndexableElement elementKind, ULONG64 elementCount, const std::string & elementDataset,
	LONG64 nullValue, EML2_NS::AbstractHdfProxy * proxy, const std::string & supportingRepDataset)
{
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
	resqml22__ElementIndices* elements = soap_new_resqml22__ElementIndices(gsoapProxy2_3->soap);
	patch->ElementIndices.push_back(elements);
	elements->__ElementIndices_sequence = soap_new___resqml22__ElementIndices_sequence(gsoapProxy2_3->soap);
	elements->__ElementIndices_sequence->IndexableElement = elementKind;

	eml23__IntegerExternalArray * integerArray = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	eml23__ExternalDataset * resqmlHDF5dataset = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	eml23__ExternalDatasetPart * dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	if (elementDataset.empty()) {
		ostringstream ossForHdf;
		ossForHdf << "subrepresentation_elementIndices0_patch" << getPatchCount();
		dsPart->PathInExternalFile = getHdfGroup() + "/" + ossForHdf.str();
	}
	else {
		dsPart->PathInExternalFile = elementDataset;
	}
	resqmlHDF5dataset->ExternalFileProxy.push_back(dsPart);
	integerArray->Values = resqmlHDF5dataset;
	integerArray->NullValue = nullValue;
	elements->__ElementIndices_sequence->Indices = integerArray;

	if (!supportingRepDataset.empty()) {
		integerArray = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
		resqmlHDF5dataset = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
		dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
		dsPart->EpcExternalPartReference = proxy->newEml23Reference();
		dsPart->PathInExternalFile = supportingRepDataset;
		resqmlHDF5dataset->ExternalFileProxy.push_back(dsPart);
		integerArray->Values = resqmlHDF5dataset;
		integerArray->NullValue = nullValue;
		elements->__ElementIndices_sequence->SupportingRepresentationIndex = integerArray;
	}

	rep->SubRepresentationPatch.push_back(patch);
}

void SubRepresentation::pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement elementKind0, gsoap_eml2_3::resqml22__IndexableElement elementKind1,
	ULONG64 elementCount,
	ULONG64 * elementIndices0, ULONG64 * elementIndices1,
	EML2_NS::AbstractHdfProxy * proxy)
{
	pushBackSubRepresentationPatch(elementKind0, elementCount, elementIndices0, proxy);

	_resqml22__SubRepresentation* rep = getSpecializedGsoapProxy();

	resqml22__SubRepresentationPatch* patch = rep->SubRepresentationPatch[getPatchCount() - 1];

	// XML
	resqml22__ElementIndices* elements = soap_new_resqml22__ElementIndices(gsoapProxy2_3->soap);
	patch->ElementIndices.push_back(elements);
	elements->__ElementIndices_sequence = soap_new___resqml22__ElementIndices_sequence(gsoapProxy2_3->soap);
	elements->__ElementIndices_sequence->IndexableElement = elementKind1;

	ostringstream ossForHdf;
	ossForHdf << "subrepresentation_elementIndices1_patch" << getPatchCount() - 1;
	eml23__IntegerExternalArray * integerArray = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	eml23__ExternalDataset * resqmlHDF5dataset = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	eml23__ExternalDatasetPart * dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = getHdfGroup() + "/" + ossForHdf.str();
	resqmlHDF5dataset->ExternalFileProxy.push_back(dsPart);
	integerArray->Values = resqmlHDF5dataset;
	integerArray->NullValue = (std::numeric_limits<unsigned int>::max)();
	elements->__ElementIndices_sequence->Indices = integerArray;

	// ************ HDF ************		
	hsize_t numValues = elementCount;
	proxy->writeArrayNdOfGSoapULong64Values(getHdfGroup(), ossForHdf.str(), elementIndices1, &numValues, 1);
}

COMMON_NS::DataObjectReference SubRepresentation::getHdfProxyDor() const
{
	_resqml22__SubRepresentation* rep = getSpecializedGsoapProxy();

	if (!rep->SubRepresentationPatch.empty()) {
		if (!rep->SubRepresentationPatch[0]->ElementIndices.empty()) {
			if (rep->SubRepresentationPatch[0]->ElementIndices[0]->__ElementIndices_sequence->Indices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
				return COMMON_NS::DataObjectReference(static_cast<eml23__IntegerExternalArray*>(rep->SubRepresentationPatch[0]->ElementIndices[0]->__ElementIndices_sequence->Indices)->Values->ExternalFileProxy[0]->EpcExternalPartReference);
			}
		}
	}

	return COMMON_NS::DataObjectReference();
}

RESQML2_NS::AbstractRepresentation::indexableElement SubRepresentation::getElementKindOfPatch(unsigned int patchIndex, unsigned int elementIndicesIndex) const
{
	_resqml22__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() > patchIndex) {
		if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() > elementIndicesIndex) {
			switch (rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->__ElementIndices_sequence->IndexableElement) {
			case resqml22__IndexableElement__nodes: return NODE;
			case resqml22__IndexableElement__edges:
			case resqml22__IndexableElement__intervals: return EDGE;
			case resqml22__IndexableElement__faces: return FACE;
			case resqml22__IndexableElement__cells: return VOLUME;
			case resqml22__IndexableElement__pillars: return PILLAR;
			default: throw invalid_argument("The indexable element of the subrepresentation is not supported yet");
			}
		}
		else {
			throw out_of_range("The elementIndices does not exist at this index.");
		}
	}
	else {
		throw out_of_range("The patch does not exist at this index.");
	}
}

resqml22__SubRepresentationPatch* SubRepresentation::getSubRepresentationPatch(unsigned int index) const
{
	_resqml22__SubRepresentation const* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() > index) {
		return rep->SubRepresentationPatch[index];
	}

	throw out_of_range("The patch does not exist at this index.");
}

ULONG64 SubRepresentation::getElementCountOfPatch(unsigned int patchIndex) const
{
	return getSubRepresentationPatch(patchIndex)->Count;
}

bool SubRepresentation::areElementIndicesPairwise(unsigned int patchIndex) const
{
	return getSubRepresentationPatch(patchIndex)->ElementIndices.size() == 2;
}

bool SubRepresentation::areElementIndicesBasedOnLattice(unsigned int patchIndex, unsigned int elementIndicesIndex) const
{
	return getSubRepresentationPatch(patchIndex)->ElementIndices[elementIndicesIndex]->__ElementIndices_sequence->Indices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerLatticeArray;
}

LONG64 SubRepresentation::getLatticeElementIndicesStartValue(unsigned int patchIndex, unsigned int elementIndicesIndex) const
{
	_resqml22__SubRepresentation* rep = getSpecializedGsoapProxy();

	if (!areElementIndicesBasedOnLattice(patchIndex, elementIndicesIndex)) {
		throw invalid_argument("The element indices are not based on a lattice.");
	}
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex) {
		throw out_of_range("The element indices index is out of range.");
	}

	eml23__IntegerLatticeArray* lattice = static_cast<eml23__IntegerLatticeArray*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->__ElementIndices_sequence->Indices);
	return lattice->StartValue;
}

unsigned int SubRepresentation::getLatticeElementIndicesDimensionCount(unsigned int patchIndex, unsigned int elementIndicesIndex) const
{
	_resqml22__SubRepresentation const * rep = getSpecializedGsoapProxy();

	if (!areElementIndicesBasedOnLattice(patchIndex, elementIndicesIndex)) {
		throw invalid_argument("The element indices are not based on a lattice.");
	}
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex) {
		throw out_of_range("The element indices index is out of range.");
	}

	eml23__IntegerLatticeArray* lattice = static_cast<eml23__IntegerLatticeArray*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->__ElementIndices_sequence->Indices);
	return lattice->Offset.size();
}

LONG64 SubRepresentation::getLatticeElementIndicesOffsetValue(unsigned int latticeDimensionIndex, unsigned int patchIndex, unsigned int elementIndicesIndex) const
{
	_resqml22__SubRepresentation* rep = getSpecializedGsoapProxy();

	if (!areElementIndicesBasedOnLattice(patchIndex, elementIndicesIndex))
		throw invalid_argument("The element indices are not based on a lattice.");
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex)
		throw out_of_range("The element indices index is out of range.");

	eml23__IntegerLatticeArray* lattice = static_cast<eml23__IntegerLatticeArray*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->__ElementIndices_sequence->Indices);
	if (lattice->Offset.size() <= latticeDimensionIndex)
		throw out_of_range("The lattice dimension index is out of range.");

	return lattice->Offset[latticeDimensionIndex]->Value;
}

ULONG64 SubRepresentation::getLatticeElementIndicesOffsetCount(unsigned int latticeDimensionIndex, unsigned int patchIndex, unsigned int elementIndicesIndex) const
{
	_resqml22__SubRepresentation* rep = getSpecializedGsoapProxy();

	if (!areElementIndicesBasedOnLattice(patchIndex, elementIndicesIndex)) {
		throw invalid_argument("The element indices are not based on a lattice.");
	}
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex) {
		throw out_of_range("The element indices index is out of range.");
	}

	eml23__IntegerLatticeArray* lattice = static_cast<eml23__IntegerLatticeArray*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->__ElementIndices_sequence->Indices);
	if (lattice->Offset.size() <= latticeDimensionIndex) {
		throw out_of_range("The lattice dimension index is out of range.");
	}

	return lattice->Offset[latticeDimensionIndex]->Count;
}

void SubRepresentation::getElementIndicesOfPatch(unsigned int patchIndex, unsigned int elementIndicesIndex, ULONG64 * elementIndices) const
{
	_resqml22__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() <= patchIndex) {
		throw out_of_range("The patch does not exist at this index.");
	}
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex) {
		throw out_of_range("The elementIndices does not exist at this index.");
	}

	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->__ElementIndices_sequence->Indices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		eml23__ExternalDatasetPart const * dsPart = static_cast<eml23__IntegerExternalArray*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->__ElementIndices_sequence->Indices)->Values->ExternalFileProxy[0];
		getHdfProxyFromDataset(dsPart)->readArrayNdOfULongValues(dsPart->PathInExternalFile, elementIndices);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void SubRepresentation::getSupportingRepresentationIndicesOfPatch(unsigned int patchIndex, short * supportingRepresentationIndices) const
{
	const _resqml22__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() <= patchIndex) {
		throw out_of_range("The patch does not exist at this index.");
	}

	if (getSupportingRepresentationCount() == 1 || rep->SubRepresentationPatch[patchIndex]->ElementIndices[0]->__ElementIndices_sequence->SupportingRepresentationIndex == nullptr) {
		const ULONG64 elementCount = getElementCountOfPatch(patchIndex);
		for (ULONG64 i = 0; i < elementCount; ++i) {
			supportingRepresentationIndices[i] = 0;
		}
		return;
	}
	else {
		if (rep->SubRepresentationPatch[patchIndex]->ElementIndices[0]->__ElementIndices_sequence->SupportingRepresentationIndex->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			eml23__ExternalDatasetPart const * dsPart = static_cast<eml23__IntegerExternalArray*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[0]->__ElementIndices_sequence->SupportingRepresentationIndex)->Values->ExternalFileProxy[0];
			getHdfProxyFromDataset(dsPart)->readArrayNdOfShortValues(dsPart->PathInExternalFile, supportingRepresentationIndices);
		}
		else {
			throw invalid_argument("Not implemented yet.");
		}
	}
}

unsigned int SubRepresentation::getPatchCount() const
{
	return getSpecializedGsoapProxy()->SubRepresentationPatch.size();
}

unsigned int SubRepresentation::getSupportingRepresentationCount() const
{
	return getSpecializedGsoapProxy()->SupportingRepresentation.size();
}

COMMON_NS::DataObjectReference SubRepresentation::getSupportingRepresentationDor(unsigned int index) const
{
	const unsigned int supRepCount = getSupportingRepresentationCount();

	if (supRepCount == 0) {
		throw invalid_argument("No supporting rep");
	}
	if (index >= supRepCount) {
		throw out_of_range("The index of the supporting represenation is out of range.");
	}

	return COMMON_NS::DataObjectReference(getSpecializedGsoapProxy()->SupportingRepresentation[index]);
}

void SubRepresentation::pushBackXmlSupportingRepresentation(RESQML2_NS::AbstractRepresentation const * supportingRep)
{
	getSpecializedGsoapProxy()->SupportingRepresentation.push_back(supportingRep->newEml23Reference());
}
