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

#include <sstream>
#include <stdexcept>

#include <hdf5.h>

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../common/AbstractHdfProxy.h"
#include "UnstructuredGridRepresentation.h"
#include "../resqml2/AbstractIjkGridRepresentation.h"
#include "DiscreteProperty.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

void SubRepresentation::init(COMMON_NS::DataObjectRepository* repo, const string & guid, const string & title)
{
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORESubRepresentation(repo->getGsoapContext());

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

_resqml20__SubRepresentation* SubRepresentation::getSpecializedGsoapProxy() const
{
	if (isPartial()) {
		throw logic_error("Partial object");
	}

	return static_cast<_resqml20__SubRepresentation*>(gsoapProxy2_0_1);
}

void SubRepresentation::pushBackSubRepresentationPatch(gsoap_resqml2_0_1::resqml20__IndexableElements elementKind, ULONG64 originIndex,
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
	elements->IndexableElement = elementKind;

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

void SubRepresentation::pushBackSubRepresentationPatch(gsoap_resqml2_0_1::resqml20__IndexableElements elementKind, ULONG64 elementCount, ULONG64 * elementIndices, COMMON_NS::AbstractHdfProxy * proxy, short * supportingRepIndices)
{
	_resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();

	std::string supportingRepDataset = "";
	ostringstream ossForHdfSupRep;
	if (supportingRepIndices != nullptr) {
		ossForHdfSupRep << "subrepresentation_supportingRepresentationIndices_patch" << rep->SubRepresentationPatch.size();
		supportingRepDataset = getHdfGroup() + "/" + ossForHdfSupRep.str();
	}
	ostringstream ossForHdf;
	ossForHdf << "subrepresentation_elementIndices0_patch" << rep->SubRepresentationPatch.size();

	pushBackRefToExistingDataset(elementKind, elementCount, getHdfGroup() + "/" + ossForHdf.str(), (std::numeric_limits<unsigned int>::max)(), proxy, supportingRepDataset);

	// ************ HDF ************		
	hsize_t numValues = elementCount;
	proxy->writeArrayNdOfGSoapULong64Values(getHdfGroup(), ossForHdf.str(), elementIndices, &numValues, 1);
	if (supportingRepIndices != nullptr) {
		proxy->writeArrayNd(getHdfGroup(), ossForHdfSupRep.str(), H5T_NATIVE_SHORT, supportingRepIndices, &numValues, 1);
	}
}

void SubRepresentation::pushBackRefToExistingDataset(gsoap_resqml2_0_1::resqml20__IndexableElements elementKind, ULONG64 elementCount, const std::string & elementDataset,
	LONG64 nullValue, COMMON_NS::AbstractHdfProxy * proxy, const std::string & supportingRepDataset)
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
	elements->IndexableElement = elementKind;

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
		DiscreteProperty* discreteProp = getRepository()->createDiscreteProperty(this, "", "SupportingRepresentationIndex", 1, elementKind, resqml20__ResqmlPropertyKind__index);
		ostringstream oss;
		oss << "SubRepresentationPatch[" << rep->SubRepresentationPatch.size() - 1 << "]/ElementIndices/SupportingRepresentationIndex";
		pushBackExtraMetadata(oss.str(), discreteProp->getUuid());
		discreteProp->pushBackRefToExistingDataset(proxy, supportingRepDataset, nullValue);
	}
}

DiscreteProperty* SubRepresentation::getSupportingRepresentationIndicesDiscretePropOfPatch(unsigned int patchIndex) const
{
	ostringstream oss;
	oss << "SubRepresentationPatch[" << patchIndex << "]/ElementIndices/SupportingRepresentationIndex";
	vector<string> uuid = getExtraMetadata(oss.str());
	return getRepository()->getDataObjectByUuid<DiscreteProperty>(uuid[0]);
}

void SubRepresentation::pushBackSubRepresentationPatch(gsoap_resqml2_0_1::resqml20__IndexableElements elementKind0, gsoap_resqml2_0_1::resqml20__IndexableElements elementKind1,
	ULONG64 elementCount,
	ULONG64 * elementIndices0, ULONG64 * elementIndices1,
	COMMON_NS::AbstractHdfProxy * proxy)
{
	pushBackSubRepresentationPatch(elementKind0, elementCount, elementIndices0, proxy);

	_resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();

	resqml20__SubRepresentationPatch* patch = rep->SubRepresentationPatch[rep->SubRepresentationPatch.size() - 1];

	// XML
	resqml20__ElementIndices* elements = soap_new_resqml20__ElementIndices(gsoapProxy2_0_1->soap);
	patch->ElementIndices.push_back(elements);
	elements->IndexableElement = elementKind1;

	ostringstream ossForHdf;
	ossForHdf << "subrepresentation_elementIndices1_patch" << patch->PatchIndex;
	resqml20__IntegerHdf5Array * integerArray = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	eml20__Hdf5Dataset * resqmlHDF5dataset = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	resqmlHDF5dataset->HdfProxy = proxy->newResqmlReference();
	resqmlHDF5dataset->PathInHdfFile = getHdfGroup() + "/" + ossForHdf.str();
	integerArray->Values = resqmlHDF5dataset;
	integerArray->NullValue = (std::numeric_limits<unsigned int>::max)();
	elements->Indices = integerArray;

	// ************ HDF ************		
	hsize_t numValues = elementCount;
	proxy->writeArrayNdOfGSoapULong64Values(getHdfGroup(), ossForHdf.str(), elementIndices1, &numValues, 1);
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

RESQML2_NS::AbstractRepresentation::indexableElement SubRepresentation::getElementKindOfPatch(unsigned int patchIndex, unsigned int elementIndicesIndex) const
{
	_resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() > patchIndex) {
		if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() > elementIndicesIndex) {
			switch (rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->IndexableElement) {
			case resqml20__IndexableElements__nodes: return NODE;
			case resqml20__IndexableElements__edges:
			case resqml20__IndexableElements__intervals: return EDGE;
			case resqml20__IndexableElements__faces: return FACE;
			case resqml20__IndexableElements__cells: return VOLUME;
			case resqml20__IndexableElements__pillars: return PILLAR;
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

gsoap_resqml2_0_1::resqml20__SubRepresentationPatch* SubRepresentation::getSubRepresentationPatch(unsigned int index) const
{
	_resqml20__SubRepresentation const* rep = getSpecializedGsoapProxy();
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
	return getSubRepresentationPatch(patchIndex)->ElementIndices[elementIndicesIndex]->Indices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray;
}

LONG64 SubRepresentation::getLatticeElementIndicesStartValue(unsigned int patchIndex, unsigned int elementIndicesIndex) const
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

LONG64 SubRepresentation::getLatticeElementIndicesOffsetValue(unsigned int latticeDimensionIndex, unsigned int patchIndex, unsigned int elementIndicesIndex) const
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

ULONG64 SubRepresentation::getLatticeElementIndicesOffsetCount(unsigned int latticeDimensionIndex, unsigned int patchIndex, unsigned int elementIndicesIndex) const
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

void SubRepresentation::getElementIndicesOfPatch(unsigned int patchIndex, unsigned int elementIndicesIndex, ULONG64 * elementIndices) const
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
		COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfULongValues(dataset->PathInHdfFile, elementIndices);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void SubRepresentation::getSupportingRepresentationIndicesOfPatch(unsigned int patchIndex, short * supportingRepresentationIndices) const
{
	const _resqml20__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() <= patchIndex) {
		throw out_of_range("The patch does not exist at this index.");
	}

	if (getSupportingRepresentationCount() == 1) {
		const ULONG64 elementCount = getElementCountOfPatch(patchIndex);
		for (ULONG64 i = 0; i < elementCount; ++i) {
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

gsoap_resqml2_0_1::eml20__DataObjectReference* SubRepresentation::getSupportingRepresentationDor(unsigned int index) const
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
	return result;
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
