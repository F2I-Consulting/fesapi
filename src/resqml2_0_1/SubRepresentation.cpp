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
#include "DiscreteProperty.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

SubRepresentation::SubRepresentation(gsoap_resqml2_0_1::_resqml20__SubRepresentation* fromGsoap): RESQML2_NS::SubRepresentation(fromGsoap) {
	std::string indexableEltStr = soap_resqml20__IndexableElements2s(fromGsoap->soap, fromGsoap->SubRepresentationPatch[0]->ElementIndices[0]->IndexableElement);
	if (gsoap_eml2_3::soap_s2eml23__IndexableElement(fromGsoap->soap, indexableEltStr.c_str(), &defaultIndexableElement) != SOAP_OK) {
		throw invalid_argument("The indexable element \"" + indexableEltStr + "\"of the subrepresentation is not supported yet");
	}
}

void SubRepresentation::init(COMMON_NS::DataObjectRepository* repo, const string & guid, const string & title)
{
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORESubRepresentation(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addDataObject(this);
}

SubRepresentation::SubRepresentation(COMMON_NS::DataObjectRepository* repo, const string & guid, const string & title, gsoap_eml2_3::eml23__IndexableElement defaultElementKind):
	defaultIndexableElement(defaultElementKind)
{
	init(repo, guid, title);
}

SubRepresentation::SubRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const string & guid, const string & title, gsoap_eml2_3::eml23__IndexableElement defaultElementKind) :
	defaultIndexableElement(defaultElementKind)
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

void SubRepresentation::pushBackSubRepresentationPatch(gsoap_eml2_3::eml23__IndexableElement elementKind, uint64_t originIndex,
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

void SubRepresentation::pushBackSubRepresentationPatch(uint64_t elementCount, int64_t* elementIndices,
	RESQML2_NS::AbstractRepresentation* supportingRep, EML2_NS::AbstractHdfProxy* proxy)
{
	uint64_t supportingRepIndex = pushBackSupportingRepresentation(supportingRep);
	if (supportingRepIndex > (std::numeric_limits<short>::max)()) {
		throw range_error("There are too much supporting representations.");
	}

	std::unique_ptr<short[]> supportingRepIndices(new short[elementCount]);
	std::fill(supportingRepIndices.get(), supportingRepIndices.get() + elementCount, static_cast<short>(supportingRepIndex));
	pushBackSubRepresentationPatch(defaultIndexableElement, elementCount, elementIndices, proxy, supportingRepIndices.get());
}

void SubRepresentation::pushBackSubRepresentationPatch(gsoap_eml2_3::eml23__IndexableElement elementKind, uint64_t elementCount, int64_t * elementIndices, EML2_NS::AbstractHdfProxy * proxy, short * supportingRepIndices)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	const auto patchCount = getPatchCount();
	// ************ HDF ************		
	hsize_t numValues = elementCount;
	proxy->writeArrayNdOfInt64Values(getHdfGroup(), "subrepresentation_elementIndices0_patch" + std::to_string(patchCount), elementIndices, &numValues, 1);
	if (supportingRepIndices != nullptr) {
		proxy->writeArrayNd(getHdfGroup(), "subrepresentation_supportingRepresentationIndices_patch" + std::to_string(patchCount), H5T_NATIVE_SHORT, supportingRepIndices, &numValues, 1);
	}

	const std::string supportingRepDataset = supportingRepIndices != nullptr ? getHdfGroup() + "/subrepresentation_supportingRepresentationIndices_patch" + std::to_string(patchCount) : "";
	// Arbitrarily set null value to -1 since it has no interest to write element index null value in this method
	pushBackRefToExistingDataset(elementKind, elementCount, getHdfGroup() + "/subrepresentation_elementIndices0_patch" + std::to_string(patchCount), -1, proxy, supportingRepDataset);
}

void SubRepresentation::pushBackSubRepresentationPatch(gsoap_eml2_3::eml23__IndexableElement elementKind0, gsoap_eml2_3::eml23__IndexableElement elementKind1,
	uint64_t elementCount,
	int64_t * elementIndices0, int64_t * elementIndices1,
	EML2_NS::AbstractHdfProxy * proxy)
{
	pushBackSubRepresentationPatch(elementKind0, elementCount, elementIndices0, proxy);

	_resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();

	resqml20__SubRepresentationPatch* patch = rep->SubRepresentationPatch[rep->SubRepresentationPatch.size() - 1];

	// XML
	resqml20__ElementIndices* elements = soap_new_resqml20__ElementIndices(gsoapProxy2_0_1->soap);
	patch->ElementIndices.push_back(elements);
	elements->IndexableElement = mapIndexableElement(elementKind1);

	resqml20__IntegerHdf5Array * integerArray = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	eml20__Hdf5Dataset * resqmlHDF5dataset = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	resqmlHDF5dataset->HdfProxy = proxy->newResqmlReference();
	resqmlHDF5dataset->PathInHdfFile = getHdfGroup() + "/subrepresentation_elementIndices1_patch" + std::to_string(patch->PatchIndex);
	integerArray->Values = resqmlHDF5dataset;
	integerArray->NullValue = -1; // Arbitrarily decided to something almost impossible since it has no interest to write index null value in this method
	elements->Indices = integerArray;

	// ************ HDF ************		
	hsize_t numValues = elementCount;
	proxy->writeArrayNdOfInt64Values(getHdfGroup(), "subrepresentation_elementIndices1_patch" + std::to_string(patch->PatchIndex), elementIndices1, &numValues, 1);
}

void SubRepresentation::pushBackRefToExistingDataset(gsoap_eml2_3::eml23__IndexableElement elementKind, uint64_t elementCount, const std::string & elementDataset,
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
		resqmlHDF5dataset->PathInHdfFile = getHdfGroup() + "/subrepresentation_elementIndices0_patch" + std::to_string(patch->PatchIndex);
	}
	else {
		resqmlHDF5dataset->PathInHdfFile = elementDataset;
	}
	integerArray->Values = resqmlHDF5dataset;
	integerArray->NullValue = nullValue;
	elements->Indices = integerArray;

	if (!supportingRepDataset.empty()) {
		RESQML2_0_1_NS::DiscreteProperty* discreteProp = getRepository()->createDiscreteProperty(this, "", "SupportingRepresentationIndex", elementKind, resqml20__ResqmlPropertyKind::index);
		pushBackExtraMetadata("SubRepresentationPatch[" + std::to_string(rep->SubRepresentationPatch.size() - 1) + "]/ElementIndices/SupportingRepresentationIndex", discreteProp->getUuid());
		discreteProp->pushBackRefToExistingIntegerDataset(proxy, supportingRepDataset, nullValue);
	}
}

void SubRepresentation::pushBackRefToExistingDataset(uint64_t elementCount, const std::string& elementDataset,
	int64_t nullValue, RESQML2_NS::AbstractRepresentation* supportingRep, EML2_NS::AbstractHdfProxy* proxy) {
	const auto supRepCount = getSupportingRepresentationCount();
	if (supRepCount > 1 ||
		(supRepCount == 1 && getSupportingRepresentationDor(0).getUuid() != supportingRep->getUuid())) {
		throw std::invalid_argument("Downcast your instance to v2.0 namespace and use the dedicated other pushBackRefToExistingDataset if your subrepresentation depends on more than one representation.");
	}
	else {
		if (supRepCount == 0) {
			pushBackSupportingRepresentation(supportingRep);
		}
		pushBackRefToExistingDataset(defaultIndexableElement, elementCount, elementDataset, nullValue, proxy);
	}
}

DiscreteProperty* SubRepresentation::getSupportingRepresentationIndicesDiscretePropOfPatch(uint64_t patchIndex) const
{
	vector<string> uuid = getExtraMetadata("SubRepresentationPatch[" + std::to_string(patchIndex) + "]/ElementIndices/SupportingRepresentationIndex");
	return getRepository()->getDataObjectByUuid<DiscreteProperty>(uuid[0]);
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

gsoap_eml2_3::eml23__IndexableElement SubRepresentation::getElementKindOfPatch(uint64_t patchIndex, unsigned int elementIndicesIndex) const
{
	_resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() > patchIndex) {
		if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() > elementIndicesIndex) {
			std::string indexableEltStr = soap_resqml20__IndexableElements2s(rep->soap, rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->IndexableElement);
			gsoap_eml2_3::eml23__IndexableElement result;
			if (gsoap_eml2_3::soap_s2eml23__IndexableElement(rep->soap, indexableEltStr.c_str(), &result) == SOAP_OK) {
				return result;
			}
			throw invalid_argument("The indexable element \"" + indexableEltStr + "\"of the subrepresentation is not supported yet");
		}
		else {
			throw out_of_range("The elementIndices does not exist at this index.");
		}
	}
	else {
		throw out_of_range("The patch does not exist at this index.");
	}
}

gsoap_eml2_3::eml23__IndexableElement SubRepresentation::getElementKind() const
{
	gsoap_eml2_3::eml23__IndexableElement result = getElementKindOfPatch(0, 0);
	if (areElementIndicesPairwise(0)) {
		gsoap_eml2_3::eml23__IndexableElement tmp = getElementKindOfPatch(0, 1);
		if (tmp != result) {
			throw invalid_argument("There are multiple element kinds in this subrepresentation. Please downcast to RESQML2.0 namespace if necessary and use dedicated methods.");
		}
	}

	const uint64_t patchCount = getPatchCount();
	for (uint64_t patchIndex = 1; patchIndex < patchCount; ++patchIndex) {
		gsoap_eml2_3::eml23__IndexableElement tmp = getElementKindOfPatch(patchIndex, 0);
		if (tmp != result) {
			throw invalid_argument("There are multiple element kinds in this subrepresentation. Please downcast to RESQML2.0 namespace if necessary and use dedicated methods.");
		}
		if (areElementIndicesPairwise(patchIndex)) {
			tmp = getElementKindOfPatch(patchIndex, 1);
			if (tmp != result) {
				throw invalid_argument("There are multiple element kinds in this subrepresentation. Please downcast to RESQML2.0 namespace if necessary and use dedicated methods.");
			}
		}
	}

	return result;
}

gsoap_resqml2_0_1::resqml20__SubRepresentationPatch* SubRepresentation::getSubRepresentationPatch(uint64_t index) const
{
	return getSpecializedGsoapProxy()->SubRepresentationPatch.at(index);
}

uint64_t SubRepresentation::getElementCountOfPatch(uint64_t patchIndex) const
{
	return getSubRepresentationPatch(patchIndex)->Count;
}

bool SubRepresentation::areElementIndicesPairwise(uint64_t patchIndex) const
{
	return getSubRepresentationPatch(patchIndex)->ElementIndices.size() == 2;
}

bool SubRepresentation::areElementIndicesBasedOnLattice(uint64_t patchIndex, unsigned int elementIndicesIndex) const
{
	return getSubRepresentationPatch(patchIndex)->ElementIndices[elementIndicesIndex]->Indices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray;
}

int64_t SubRepresentation::getLatticeElementIndicesStartValue(uint64_t patchIndex, unsigned int elementIndicesIndex) const
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

uint64_t SubRepresentation::getLatticeElementIndicesDimensionCount(uint64_t patchIndex, unsigned int elementIndicesIndex) const
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

int64_t SubRepresentation::getLatticeElementIndicesOffsetValue(unsigned int latticeDimensionIndex, uint64_t patchIndex, unsigned int elementIndicesIndex) const
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

uint64_t SubRepresentation::getLatticeElementIndicesOffsetCount(unsigned int latticeDimensionIndex, uint64_t patchIndex, unsigned int elementIndicesIndex) const
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

int64_t SubRepresentation::getElementIndicesOfPatch(uint64_t patchIndex, unsigned int elementIndicesIndex, int64_t * elementIndices) const
{
	_resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() <= patchIndex) {
		throw out_of_range("The patch does not exist at this index.");
	}
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex) {
		throw out_of_range("The elementIndices does not exist at this index.");
	}

	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices)->Values;
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfInt64Values(dataset->PathInHdfFile, elementIndices);
		return static_cast<resqml20__IntegerHdf5Array*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices)->NullValue;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void SubRepresentation::getSupportingRepresentationIndicesOfPatch(uint64_t patchIndex, short * supportingRepresentationIndices) const
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
	if (prop == nullptr) {
		throw std::invalid_argument("The subrepresentation patch inde " + std::to_string(patchIndex) + " has not got any supportingRepresentationIndices");
	}
	prop->getShortValuesOfPatch(0, supportingRepresentationIndices);
}

uint64_t SubRepresentation::getPatchCount() const
{
	return getSpecializedGsoapProxy()->SubRepresentationPatch.size();
}

uint64_t SubRepresentation::pushBackSupportingRepresentation(AbstractRepresentation * supportingRep)
{
	if (supportingRep == nullptr) {
		throw invalid_argument("The supporting Representation cannot be null.");
	}

	const auto supportingRepCount = getSupportingRepresentationCount();
	for (unsigned int i = 0; i < supportingRepCount; ++i) {
		if (getSupportingRepresentationDor(i).getUuid() == supportingRep->getUuid()) {
			return i;
		}
	}

	getRepository()->addRelationship(this, supportingRep);

	pushBackXmlSupportingRepresentation(supportingRep);
	return getSupportingRepresentationCount() - 1;
}

void SubRepresentation::pushBackSubRepresentationPatch(uint64_t originIndex,
	unsigned int elementCountInSlowestDimension,
	unsigned int elementCountInMiddleDimension,
	unsigned int elementCountInFastestDimension, RESQML2_NS::AbstractIjkGridRepresentation* ijkGrid) {
	pushBackSupportingRepresentation(ijkGrid);
	pushBackSubRepresentationPatch(defaultIndexableElement, originIndex, elementCountInSlowestDimension, elementCountInMiddleDimension, elementCountInFastestDimension);
}

uint64_t SubRepresentation::getSupportingRepresentationCount() const
{
	_resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SupportingRepresentation == nullptr) {
		return 0;
	}

	const size_t count = getExtraMetadata("SupportingRepresentation").size();
	return count < 2 ? 1 : count;
}

COMMON_NS::DataObjectReference SubRepresentation::getSupportingRepresentationDor(uint64_t index) const
{
	const uint64_t supRepCount = getSupportingRepresentationCount();

	if (supRepCount == 0) {
		throw invalid_argument("No supporting rep");
	}
	if (index >= supRepCount) {
		throw out_of_range("The index of the supporting representation is out of range.");
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

COMMON_NS::DataObjectReference SubRepresentation::getSupportingRepresentationOfPatchDor(uint64_t patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The patch index " + std::to_string(patchIndex) + " is out of range.");
	}
	if (getSupportingRepresentationCount() == 0) {
		throw invalid_argument("There is not associated supporting represenation at all in this subrepresentation.");
	}

	if (getSupportingRepresentationCount() == 1) {
		return getSupportingRepresentationDor(0);
	}

	const auto elementCount = getElementCountOfPatch(patchIndex);
	std::unique_ptr<short[]> supportingRepIndices(new short[elementCount]);
	getSupportingRepresentationIndicesOfPatch(patchIndex, supportingRepIndices.get());
	short uniqueSubRepIndex = supportingRepIndices[0];
	for (auto i = 1; i < elementCount; ++i) {
		if (supportingRepIndices[i] != uniqueSubRepIndex) {
			throw logic_error("Downcast your instance to v2.0 namespace and use the dedicated getSupportingRepresentationIndicesOfPatch method if your subrepresentation patch depends on more than one representation");
		}
	}
	return getSupportingRepresentationDor(uniqueSubRepIndex);
}

RESQML2_NS::AbstractRepresentation* SubRepresentation::getSupportingRepresentation(uint64_t index) const
{
	return static_cast<AbstractRepresentation*>(repository->getDataObjectByUuid(getSupportingRepresentationDor(index).getUuid()));
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
