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
#include "DiscreteProperty.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* SubRepresentation::XML_NS = "resqml20";

void SubRepresentation::init(COMMON_NS::DataObjectRepository* repo, const string & guid, const string & title)
{
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORESubRepresentation(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addDataObject(this);
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

_resqml20__SubRepresentation* SubRepresentation::getSpecializedGsoapProxy() const
{
	if (isPartial()) {
		throw logic_error("Partial object");
	}

	return static_cast<_resqml20__SubRepresentation*>(gsoapProxy2_0_1);
}

void SubRepresentation::pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement elementKind, uint64_t originIndex,
	unsigned int elementCountInSlowestDimension,
	unsigned int elementCountInMiddleDimension,
	unsigned int elementCountInFastestDimension)
{
	_resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();

	resqml20__SubRepresentationPatch* patch = soap_new_resqml20__SubRepresentationPatch(gsoapProxy2_0_1->soap);

	// XML
	patch->PatchIndex = rep->SubRepresentationPatch.size();
	rep->SubRepresentationPatch.push_back(patch);
	patch->Count = elementCountInSlowestDimension * elementCountInMiddleDimension * elementCountInFastestDimension;
	resqml20__ElementIndices* elements = soap_new_resqml20__ElementIndices(gsoapProxy2_0_1->soap);
	patch->ElementIndices.push_back(elements);
	elements->IndexableElement = mapIndexableElement(elementKind);

	resqml20__IntegerLatticeArray * integerArray = soap_new_resqml20__IntegerLatticeArray(gsoapProxy2_0_1->soap);
	elements->Indices = integerArray;
	integerArray->StartValue = originIndex;

	resqml20__IntegerConstantArray * offset = soap_new_resqml20__IntegerConstantArray(gsoapProxy2_0_1->soap);
	offset->Count = elementCountInSlowestDimension - 1;
	offset->Value = 1;
	integerArray->Offset.push_back(offset);

	offset = soap_new_resqml20__IntegerConstantArray(gsoapProxy2_0_1->soap);
	offset->Count = elementCountInMiddleDimension - 1;
	offset->Value = 1;
	integerArray->Offset.push_back(offset);

	offset = soap_new_resqml20__IntegerConstantArray(gsoapProxy2_0_1->soap);
	offset->Count = elementCountInFastestDimension - 1;
	offset->Value = 1;
	integerArray->Offset.push_back(offset);
}

void SubRepresentation::pushBackRefToExistingDataset(gsoap_eml2_3::resqml22__IndexableElement elementKind, uint64_t elementCount, const std::string & elementDataset,
	int64_t nullValue, EML2_NS::AbstractHdfProxy * proxy, const std::string & supportingRepDataset)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

	resqml20__SubRepresentationPatch* patch = soap_new_resqml20__SubRepresentationPatch(gsoapProxy2_0_1->soap);

	// XML
	_resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();
	patch->PatchIndex = rep->SubRepresentationPatch.size();
	rep->SubRepresentationPatch.push_back(patch);
	patch->Count = elementCount;
	resqml20__ElementIndices* elements = soap_new_resqml20__ElementIndices(gsoapProxy2_0_1->soap);
	patch->ElementIndices.push_back(elements);
	elements->IndexableElement = mapIndexableElement(elementKind);

	resqml20__IntegerHdf5Array * integerArray = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	eml20__Hdf5Dataset * resqmlHDF5dataset = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	resqmlHDF5dataset->HdfProxy = proxy->newResqmlReference();
	if (elementDataset.empty()) {
		ostringstream ossForHdf;
		ossForHdf << "subrepresentation_elementIndices0_patch" << patch->PatchIndex;
		resqmlHDF5dataset->PathInHdfFile = getHdfGroup() + "/" + ossForHdf.str();
	}
	else {
		resqmlHDF5dataset->PathInHdfFile = elementDataset;
	}
	integerArray->Values = resqmlHDF5dataset;
	integerArray->NullValue = nullValue;
	elements->Indices = integerArray;

	if (!supportingRepDataset.empty()) {
		RESQML2_0_1_NS::DiscreteProperty* discreteProp = getRepository()->createDiscreteProperty(this, "", "SupportingRepresentationIndex", 1, elementKind, resqml20__ResqmlPropertyKind::index);
		ostringstream oss;
		oss << "SubRepresentationPatch[" << rep->SubRepresentationPatch.size() - 1 << "]/ElementIndices/SupportingRepresentationIndex";
		pushBackExtraMetadata(oss.str(), discreteProp->getUuid());
		discreteProp->pushBackRefToExistingIntegerDataset(proxy, supportingRepDataset, nullValue);
	}
}

DiscreteProperty* SubRepresentation::getSupportingRepresentationIndicesDiscretePropOfPatch(unsigned int patchIndex) const
{
	ostringstream oss;
	oss << "SubRepresentationPatch[" << patchIndex << "]/ElementIndices/SupportingRepresentationIndex";
	vector<string> uuid = getExtraMetadata(oss.str());
	return getRepository()->getDataObjectByUuid<DiscreteProperty>(uuid[0]);
}

void SubRepresentation::pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement elementKind0, gsoap_eml2_3::resqml22__IndexableElement elementKind1,
	uint64_t elementCount,
	uint64_t * elementIndices0, uint64_t * elementIndices1,
	EML2_NS::AbstractHdfProxy * proxy)
{
	pushBackSubRepresentationPatch(elementKind0, elementCount, elementIndices0, proxy);

	_resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();

	resqml20__SubRepresentationPatch* patch = rep->SubRepresentationPatch[rep->SubRepresentationPatch.size() - 1];

	// XML
	resqml20__ElementIndices* elements = soap_new_resqml20__ElementIndices(gsoapProxy2_0_1->soap);
	patch->ElementIndices.push_back(elements);
	elements->IndexableElement = mapIndexableElement(elementKind1);

	ostringstream ossForHdf;
	ossForHdf << "subrepresentation_elementIndices1_patch" << patch->PatchIndex;
	resqml20__IntegerHdf5Array * integerArray = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	eml20__Hdf5Dataset * resqmlHDF5dataset = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	resqmlHDF5dataset->HdfProxy = proxy->newResqmlReference();
	resqmlHDF5dataset->PathInHdfFile = getHdfGroup() + "/" + ossForHdf.str();
	integerArray->Values = resqmlHDF5dataset;
	integerArray->NullValue = -1; // Arbitrarily decided to something almost impossible since it has no interest to write index null value in this method
	elements->Indices = integerArray;

	// ************ HDF ************		
	hsize_t numValues = elementCount;
	proxy->writeArrayNdOfUInt64Values(getHdfGroup(), ossForHdf.str(), elementIndices1, &numValues, 1);
}

COMMON_NS::DataObjectReference SubRepresentation::getHdfProxyDor() const
{
	_resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();

	if (!rep->SubRepresentationPatch.empty()) {
		if (!rep->SubRepresentationPatch[0]->ElementIndices.empty()) {
			if (rep->SubRepresentationPatch[0]->ElementIndices[0]->Indices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
				return COMMON_NS::DataObjectReference(static_cast<resqml20__IntegerHdf5Array*>(rep->SubRepresentationPatch[0]->ElementIndices[0]->Indices)->Values->HdfProxy);
			}
		}
	}

	return COMMON_NS::DataObjectReference();
}

gsoap_eml2_3::resqml22__IndexableElement SubRepresentation::getElementKindOfPatch(unsigned int patchIndex, unsigned int elementIndicesIndex) const
{
	_resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() > patchIndex) {
		if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() > elementIndicesIndex) {
			gsoap_resqml2_0_1::resqml20__IndexableElements ie201 = rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->IndexableElement;
			if (ie201 == gsoap_resqml2_0_1::resqml20__IndexableElements::cells) {
				return gsoap_eml2_3::resqml22__IndexableElement::cells;
			}
			else if (static_cast<int>(ie201) < 17) {
				return static_cast<gsoap_eml2_3::resqml22__IndexableElement>(static_cast<int>(ie201) + 1);
			}
			else {
				return static_cast<gsoap_eml2_3::resqml22__IndexableElement>(static_cast<int>(ie201) + 2);
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

gsoap_resqml2_0_1::resqml20__SubRepresentationPatch* SubRepresentation::getSubRepresentationPatch(unsigned int index) const
{
	_resqml20__SubRepresentation const* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() > index) {
		return rep->SubRepresentationPatch[index];
	}

	throw out_of_range("The patch does not exist at this index.");
}

uint64_t SubRepresentation::getElementCountOfPatch(unsigned int patchIndex) const
{
	return getSubRepresentationPatch(patchIndex)->Count;
}

bool SubRepresentation::areElementIndicesPairwise(unsigned int patchIndex) const
{
	return getSubRepresentationPatch(patchIndex)->ElementIndices.size() == 2;
}

bool SubRepresentation::areElementIndicesBasedOnLattice(unsigned int patchIndex, unsigned int elementIndicesIndex) const
{
	return getSubRepresentationPatch(patchIndex)->ElementIndices[elementIndicesIndex]->Indices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray;
}

int64_t SubRepresentation::getLatticeElementIndicesStartValue(unsigned int patchIndex, unsigned int elementIndicesIndex) const
{
	_resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();

	if (!areElementIndicesBasedOnLattice(patchIndex, elementIndicesIndex)) {
		throw invalid_argument("The element indices are not based on a lattice.");
	}
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex) {
		throw out_of_range("The element indices index is out of range.");
	}

	resqml20__IntegerLatticeArray* lattice = static_cast<resqml20__IntegerLatticeArray*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices);
	return lattice->StartValue;
}

unsigned int SubRepresentation::getLatticeElementIndicesDimensionCount(unsigned int patchIndex, unsigned int elementIndicesIndex) const
{
	_resqml20__SubRepresentation const * rep = getSpecializedGsoapProxy();

	if (!areElementIndicesBasedOnLattice(patchIndex, elementIndicesIndex)) {
		throw invalid_argument("The element indices are not based on a lattice.");
	}
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex) {
		throw out_of_range("The element indices index is out of range.");
	}

	resqml20__IntegerLatticeArray* lattice = static_cast<resqml20__IntegerLatticeArray*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices);
	return lattice->Offset.size();
}

int64_t SubRepresentation::getLatticeElementIndicesOffsetValue(unsigned int latticeDimensionIndex, unsigned int patchIndex, unsigned int elementIndicesIndex) const
{
	_resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();

	if (!areElementIndicesBasedOnLattice(patchIndex, elementIndicesIndex))
		throw invalid_argument("The element indices are not based on a lattice.");
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex)
		throw out_of_range("The element indices index is out of range.");

	resqml20__IntegerLatticeArray* lattice = static_cast<resqml20__IntegerLatticeArray*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices);
	if (lattice->Offset.size() <= latticeDimensionIndex)
		throw out_of_range("The lattice dimension index is out of range.");

	return lattice->Offset[latticeDimensionIndex]->Value;
}

uint64_t SubRepresentation::getLatticeElementIndicesOffsetCount(unsigned int latticeDimensionIndex, unsigned int patchIndex, unsigned int elementIndicesIndex) const
{
	_resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();

	if (!areElementIndicesBasedOnLattice(patchIndex, elementIndicesIndex)) {
		throw invalid_argument("The element indices are not based on a lattice.");
	}
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex) {
		throw out_of_range("The element indices index is out of range.");
	}

	resqml20__IntegerLatticeArray* lattice = static_cast<resqml20__IntegerLatticeArray*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices);
	if (lattice->Offset.size() <= latticeDimensionIndex) {
		throw out_of_range("The lattice dimension index is out of range.");
	}

	return lattice->Offset[latticeDimensionIndex]->Count;
}

void SubRepresentation::getElementIndicesOfPatch(unsigned int patchIndex, unsigned int elementIndicesIndex, uint64_t * elementIndices) const
{
	_resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() <= patchIndex) {
		throw out_of_range("The patch does not exist at this index.");
	}
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex) {
		throw out_of_range("The elementIndices does not exist at this index.");
	}

	readArrayNdOfUInt64Values(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices, elementIndices);
}

void SubRepresentation::getSupportingRepresentationIndicesOfPatch(unsigned int patchIndex, short * supportingRepresentationIndices) const
{
	const _resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() <= patchIndex) {
		throw out_of_range("The patch does not exist at this index.");
	}

	if (getSupportingRepresentationCount() == 1) {
		const uint64_t elementCount = getElementCountOfPatch(patchIndex);
		for (uint64_t i = 0; i < elementCount; ++i) {
			supportingRepresentationIndices[i] = 0;
		}
		return;
	}

	DiscreteProperty* prop = getSupportingRepresentationIndicesDiscretePropOfPatch(patchIndex);
	prop->getShortValuesOfPatch(0, supportingRepresentationIndices);
}

unsigned int SubRepresentation::getPatchCount() const
{
	return getSpecializedGsoapProxy()->SubRepresentationPatch.size();
}

unsigned int SubRepresentation::getSupportingRepresentationCount() const
{
	_resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SupportingRepresentation == nullptr) {
		return 0;
	}

	const size_t count = getExtraMetadata("SupportingRepresentation").size();
	return count < 2 ? 1 : count;
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

	if (supRepCount == 1) {
		return getSpecializedGsoapProxy()->SupportingRepresentation;
	}

	eml20__DataObjectReference* result = soap_new_eml20__DataObjectReference(getGsoapContext());
	result->ContentType = getSpecializedGsoapProxy()->SupportingRepresentation->ContentType;
	result->Title = getSpecializedGsoapProxy()->SupportingRepresentation->Title;
	result->UUID = getExtraMetadata("SupportingRepresentation")[index];
	return COMMON_NS::DataObjectReference(result);
}

void SubRepresentation::pushBackXmlSupportingRepresentation(RESQML2_NS::AbstractRepresentation const * supportingRep)
{
	_resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SupportingRepresentation == nullptr) {
		rep->SupportingRepresentation = supportingRep->newResqmlReference();
	}
	else {
		if (getSupportingRepresentationCount() == 1) {
			// Copy the supporting rep into the extrametadata
			pushBackExtraMetadata("SupportingRepresentation", rep->SupportingRepresentation->UUID);
		}
		// push back the new supporting rep
		pushBackExtraMetadata("SupportingRepresentation", supportingRep->getUuid());
	}
}
