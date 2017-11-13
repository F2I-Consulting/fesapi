/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use,
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#include "resqml2_0_1/SubRepresentation.h"

#include <sstream>
#include <stdexcept>

#include "hdf5.h"

#include "resqml2/AbstractFeatureInterpretation.h"
#include "common/AbstractHdfProxy.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/AbstractIjkGridRepresentation.h"
#include "resqml2_0_1/DiscreteProperty.h"

using namespace std;
using namespace epc;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

void SubRepresentation::init(soap* soapContext, const string & guid, const string & title)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORESubRepresentation(soapContext, 1);
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();

	initMandatoryMetadata();
    setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

SubRepresentation::SubRepresentation(soap* soapContext,	const string & guid, const string & title) :
	resqml2::SubRepresentation(static_cast<resqml2::AbstractFeatureInterpretation*>(nullptr))
{
	init(soapContext, guid, title);
}

SubRepresentation::SubRepresentation(resqml2::AbstractFeatureInterpretation* interp,
	const string & guid, const string & title) :
	resqml2::SubRepresentation(interp)
{
	if (interp == nullptr) {
		throw invalid_argument("The interpretation of the subrepresentation cannot be null.");
	}

	init(interp->getGsoapContext(), guid, title);

	// relationhsips
	setInterpretation(interp);
}

_resqml2__SubRepresentation* SubRepresentation::getSpecializedGsoapProxy() const
{
	if (isPartial()) {
		throw logic_error("Partial object");
	}

	return static_cast<_resqml2__SubRepresentation*>(gsoapProxy2_0_1);
}

void SubRepresentation::pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind, const ULONG64 & originIndex,
	const unsigned int & elementCountInSlowestDimension,
	const unsigned int & elementCountInMiddleDimension,
	const unsigned int & elementCountInFastestDimension)
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();

	resqml2__SubRepresentationPatch* patch = soap_new_resqml2__SubRepresentationPatch(gsoapProxy2_0_1->soap, 1);

	// XML
	patch->PatchIndex = rep->SubRepresentationPatch.size();
	rep->SubRepresentationPatch.push_back(patch);
	patch->Count = elementCountInSlowestDimension * elementCountInMiddleDimension * elementCountInFastestDimension;
	resqml2__ElementIndices* elements = soap_new_resqml2__ElementIndices(gsoapProxy2_0_1->soap, 1);
	patch->ElementIndices.push_back(elements);
	elements->IndexableElement = elementKind;

	resqml2__IntegerLatticeArray * integerArray = soap_new_resqml2__IntegerLatticeArray(gsoapProxy2_0_1->soap, 1);
	elements->Indices = integerArray;
	integerArray->StartValue = originIndex;

	resqml2__IntegerConstantArray * offset = soap_new_resqml2__IntegerConstantArray(gsoapProxy2_0_1->soap, 1);
	offset->Count = elementCountInSlowestDimension - 1;
	offset->Value = 1;
	integerArray->Offset.push_back(offset);

	offset = soap_new_resqml2__IntegerConstantArray(gsoapProxy2_0_1->soap, 1);
	offset->Count = elementCountInMiddleDimension - 1;
	offset->Value = 1;
	integerArray->Offset.push_back(offset);

	offset = soap_new_resqml2__IntegerConstantArray(gsoapProxy2_0_1->soap, 1);
	offset->Count = elementCountInFastestDimension - 1;
	offset->Value = 1;
	integerArray->Offset.push_back(offset);
}

void SubRepresentation::pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind, const ULONG64 & elementCount, ULONG64 * elementIndices, common::AbstractHdfProxy * proxy, short * supportingRepIndices)
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();

	std::string supportingRepDataset = "";
	ostringstream ossForHdfSupRep;
	if (supportingRepIndices != nullptr) {
		ossForHdfSupRep << "subrepresentation_supportingRepresentationIndices_patch" << rep->SubRepresentationPatch.size();
		supportingRepDataset = "/RESQML/" + rep->uuid + "/" + ossForHdfSupRep.str();
	}
	ostringstream ossForHdf;
	ossForHdf << "subrepresentation_elementIndices0_patch" << rep->SubRepresentationPatch.size();

	pushBackRefToExistingDataset(elementKind, elementCount, "/RESQML/" + rep->uuid + "/" + ossForHdf.str(), (std::numeric_limits<unsigned int>::max)(), proxy, supportingRepDataset);

	// ************ HDF ************		
	hsize_t numValues[] = {elementCount};
	hdfProxy->writeArrayNdOfGSoapULong64Values(rep->uuid, ossForHdf.str(), elementIndices, numValues, 1);
	if (supportingRepIndices != nullptr) {
		hdfProxy->writeArrayNd(rep->uuid, ossForHdfSupRep.str(), H5T_NATIVE_SHORT, supportingRepIndices, numValues, 1);
	}
}

void SubRepresentation::pushBackRefToExistingDataset(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind, const ULONG64 & elementCount, const std::string & elementDataset,
	const LONG64 & nullValue, common::AbstractHdfProxy * proxy, const std::string & supportingRepDataset)
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();
	
  setHdfProxy(proxy);
  
  resqml2__SubRepresentationPatch* patch = soap_new_resqml2__SubRepresentationPatch(gsoapProxy2_0_1->soap, 1);

  // XML
  patch->PatchIndex = rep->SubRepresentationPatch.size();
  rep->SubRepresentationPatch.push_back(patch);
  patch->Count = elementCount;
  resqml2__ElementIndices* elements = soap_new_resqml2__ElementIndices(gsoapProxy2_0_1->soap, 1);
  patch->ElementIndices.push_back(elements);
  elements->IndexableElement = elementKind;

  resqml2__IntegerHdf5Array * integerArray = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
  eml20__Hdf5Dataset * resqmlHDF5dataset = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
  resqmlHDF5dataset->HdfProxy = hdfProxy->newResqmlReference();
  if (elementDataset.empty()) {
    ostringstream ossForHdf;
    ossForHdf << "subrepresentation_elementIndices0_patch" << patch->PatchIndex;
    resqmlHDF5dataset->PathInHdfFile = "/RESQML/" + rep->uuid + "/" + ossForHdf.str();
  }
  else {
	  resqmlHDF5dataset->PathInHdfFile = elementDataset;
  }
  integerArray->Values = resqmlHDF5dataset;
  integerArray->NullValue = nullValue;
  elements->Indices = integerArray;

  if (!supportingRepDataset.empty()) {
	  DiscreteProperty* discreteProp = getEpcDocument()->createDiscreteProperty(this, "", "SupportingRepresentationIndex", 1, elementKind, resqml2__ResqmlPropertyKind__index);
	  ostringstream oss;
	  oss << "SubRepresentationPatch[" << rep->SubRepresentationPatch.size() - 1 << "]/ElementIndices/SupportingRepresentationIndex";
	  pushBackExtraMetadata(oss.str(), discreteProp->getUuid());
	  discreteProp->pushBackRefToExistingDataset(proxy, supportingRepDataset, nullValue);
  }
}

DiscreteProperty* SubRepresentation::getSupportingRepresentationIndicesDiscretePropOfPatch(const unsigned int & patchIndex) const
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();

	ostringstream oss;
	oss << "SubRepresentationPatch[" << patchIndex << "]/ElementIndices/SupportingRepresentationIndex";
	vector<string> uuid = getExtraMetadata(oss.str());
	return getEpcDocument()->getResqmlAbstractObjectByUuid<DiscreteProperty>(uuid[0]);
}

void SubRepresentation::pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind0, const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind1,
	const ULONG64 & elementCount,
	ULONG64 * elementIndices0, ULONG64 * elementIndices1,
	common::AbstractHdfProxy * proxy)
{
	pushBackSubRepresentationPatch(elementKind0, elementCount, elementIndices0, proxy);

	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();

	resqml2__SubRepresentationPatch* patch = rep->SubRepresentationPatch[rep->SubRepresentationPatch.size() - 1];

	// XML
	resqml2__ElementIndices* elements = soap_new_resqml2__ElementIndices(gsoapProxy2_0_1->soap, 1);
	patch->ElementIndices.push_back(elements);
	elements->IndexableElement = elementKind1;
	
	ostringstream ossForHdf;
	ossForHdf << "subrepresentation_elementIndices1_patch" << patch->PatchIndex;
	resqml2__IntegerHdf5Array * integerArray = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
    eml20__Hdf5Dataset * resqmlHDF5dataset = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
    resqmlHDF5dataset->HdfProxy = hdfProxy->newResqmlReference();
    resqmlHDF5dataset->PathInHdfFile = "/RESQML/" + rep->uuid + "/" + ossForHdf.str();
	integerArray->Values = resqmlHDF5dataset;
	integerArray->NullValue = (std::numeric_limits<unsigned int>::max)();
	elements->Indices = integerArray;

	// ************ HDF ************		
	hsize_t numValues[] = {elementCount};
	hdfProxy->writeArrayNdOfGSoapULong64Values(rep->uuid, ossForHdf.str(), elementIndices1, numValues, 1);
}

string SubRepresentation::getHdfProxyUuid() const
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();

	if (!rep->SubRepresentationPatch.empty()) {
		if (!rep->SubRepresentationPatch[0]->ElementIndices.empty()) {
			if (rep->SubRepresentationPatch[0]->ElementIndices[0]->Indices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
				return static_cast<resqml2__IntegerHdf5Array*>(rep->SubRepresentationPatch[0]->ElementIndices[0]->Indices)->Values->HdfProxy->UUID;
			}
		}
	}

	return "";
}

resqml2::AbstractRepresentation::indexableElement SubRepresentation::getElementKindOfPatch(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex) const
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() > patchIndex) {
		if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() > elementIndicesIndex) {
			switch (rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->IndexableElement) {
			case resqml2__IndexableElements__nodes: return NODE;
			case resqml2__IndexableElements__edges:
			case resqml2__IndexableElements__intervals: return EDGE;
			case resqml2__IndexableElements__faces: return FACE;
			case resqml2__IndexableElements__cells: return VOLUME;
			case resqml2__IndexableElements__pillars: return PILLAR;
			default: throw invalid_argument("The indexable element of the subrepresentation is not supported yet");
			}
		}
		else {
			throw range_error("The elementIndices does not exist at this index.");
		}
	}
	else {
		throw range_error("The patch does not exist at this index.");
	}
}

gsoap_resqml2_0_1::resqml2__SubRepresentationPatch* SubRepresentation::getSubRepresentationPatch(const unsigned int & index) const
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() > index) {
		return rep->SubRepresentationPatch[index];
	}
	else {
		throw range_error("The patch does not exist at this index.");
	}
}

ULONG64 SubRepresentation::getElementCountOfPatch(const unsigned int & patchIndex) const
{
	return getSubRepresentationPatch(patchIndex)->Count;
}

bool SubRepresentation::areElementIndicesPairwise(const unsigned int & patchIndex) const
{
	return getSubRepresentationPatch(patchIndex)->ElementIndices.size() == 2;
}

bool SubRepresentation::areElementIndicesBasedOnLattice(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex) const
{
	return getSubRepresentationPatch(patchIndex)->ElementIndices[elementIndicesIndex]->Indices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerLatticeArray;
}

LONG64 SubRepresentation::getLatticeElementIndicesStartValue(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex) const
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();

	if (areElementIndicesBasedOnLattice(patchIndex, elementIndicesIndex) == false) {
		throw invalid_argument("The element indices are not based on a lattice.");
	}
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex) {
		throw range_error("The element indices index is out of range.");
	}

	resqml2__IntegerLatticeArray* lattice = static_cast<resqml2__IntegerLatticeArray*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices);
	return lattice->StartValue;
}

unsigned int SubRepresentation::getLatticeElementIndicesDimensionCount(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex) const
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();

	if (areElementIndicesBasedOnLattice(patchIndex, elementIndicesIndex) == false)
		throw invalid_argument("The element indices are not based on a lattice.");
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex)
		throw range_error("The element indices index is out of range.");

	resqml2__IntegerLatticeArray* lattice = static_cast<resqml2__IntegerLatticeArray*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices);
	return lattice->Offset.size();
}

LONG64 SubRepresentation::getLatticeElementIndicesOffsetValue(const unsigned int & latticeDimensionIndex, const unsigned int & patchIndex, const unsigned int & elementIndicesIndex) const
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();

	if (areElementIndicesBasedOnLattice(patchIndex, elementIndicesIndex) == false)
		throw invalid_argument("The element indices are not based on a lattice.");
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex)
		throw range_error("The element indices index is out of range.");

	resqml2__IntegerLatticeArray* lattice = static_cast<resqml2__IntegerLatticeArray*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices);
	if (lattice->Offset.size() <= latticeDimensionIndex)
		throw range_error("The lattice dimension index is out of range.");

	return lattice->Offset[latticeDimensionIndex]->Value;
}

ULONG64 SubRepresentation::getLatticeElementIndicesOffsetCount(const unsigned int & latticeDimensionIndex, const unsigned int & patchIndex, const unsigned int & elementIndicesIndex) const
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();

	if (!areElementIndicesBasedOnLattice(patchIndex, elementIndicesIndex)) {
		throw invalid_argument("The element indices are not based on a lattice.");
	}
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex) {
		throw range_error("The element indices index is out of range.");
	}

	resqml2__IntegerLatticeArray* lattice = static_cast<resqml2__IntegerLatticeArray*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices);
	if (lattice->Offset.size() <= latticeDimensionIndex) {
		throw range_error("The lattice dimension index is out of range.");
	}

	return lattice->Offset[latticeDimensionIndex]->Count;
}

void SubRepresentation::getElementIndicesOfPatch(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex, ULONG64 * elementIndices) const
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() <= patchIndex) {
		throw range_error("The patch does not exist at this index.");
	}
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex) {
		throw range_error("The elementIndices does not exist at this index.");
	}

	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
		hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices)->Values->PathInHdfFile, elementIndices);
	}
	else {
		throw logic_error("Not yet implemented");
	}
}

void SubRepresentation::getSupportingRepresentationIndicesOfPatch(const unsigned int & patchIndex, short * supportingRepresentationIndices) const
{
	const _resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() <= patchIndex) {
		throw range_error("The patch does not exist at this index.");
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
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();
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
		throw range_error("The index of the supporting represenation is out of range.");
	}

	if (supRepCount == 1) {
		return getSpecializedGsoapProxy()->SupportingRepresentation;
	}

	eml20__DataObjectReference* result = soap_new_eml20__DataObjectReference(getGsoapContext(), 1);
	result->ContentType = getSpecializedGsoapProxy()->SupportingRepresentation->ContentType;
	result->Title = getSpecializedGsoapProxy()->SupportingRepresentation->Title;
	result->UUID = getExtraMetadata("SupportingRepresentation")[index];
	return result;
}

void SubRepresentation::pushBackXmlSupportingRepresentation(resqml2::AbstractRepresentation * supportingRep)
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SupportingRepresentation == nullptr) {
		rep->SupportingRepresentation = supportingRep->newResqmlReference();
		supportingRep->pushBackSubRepresentation(this);
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
