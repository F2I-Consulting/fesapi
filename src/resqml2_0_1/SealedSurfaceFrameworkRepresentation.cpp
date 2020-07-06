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
#include "SealedSurfaceFrameworkRepresentation.h"

#include <limits>
#include <stdexcept>
#include <sstream>

#include "H5Tpublic.h"

#include "../resqml2/StructuralOrganizationInterpretation.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

SealedSurfaceFrameworkRepresentation::SealedSurfaceFrameworkRepresentation(
	RESQML2_NS::StructuralOrganizationInterpretation* interp,
    const std::string & guid,
    const std::string & title)
{
	if (interp == nullptr) {
		throw invalid_argument("The structural organization interpretation cannot be null.");
	}

    // proxy constructor
    gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORESealedSurfaceFrameworkRepresentation(interp->getGsoapContext());
    _resqml20__SealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml20__SealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

    orgRep->IsHomogeneous = true;

    initMandatoryMetadata();
    setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

    setInterpretation(interp);
}

void SealedSurfaceFrameworkRepresentation::pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind kind)
{
    _resqml20__SealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml20__SealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

    resqml20__SealedContactRepresentationPart* contactRep = soap_new_resqml20__SealedContactRepresentationPart(gsoapProxy2_0_1->soap);
    contactRep->Index = orgRep->SealedContactRepresentation.size();
    contactRep->IdentityKind = kind;
    orgRep->SealedContactRepresentation.push_back(contactRep);
}

void SealedSurfaceFrameworkRepresentation::pushBackContact(
        gsoap_resqml2_0_1::resqml20__IdentityKind kind,
        unsigned int patchCount,
        unsigned int identicalNodesCount,
        int const* identicalNodes,
		EML2_NS::AbstractHdfProxy * proxy)
{
	if (patchCount < 2) {
		throw invalid_argument("Contact patch count cannot be less than two.");
	}
	if (identicalNodesCount == 0) {
		throw invalid_argument("The identical nodes count cannot be zero.");
	}
	if (identicalNodes == nullptr) {
		throw invalid_argument("The array of identical nodes cannot be null.");
	}
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

	pushBackContact(kind);
	resqml20__SealedContactRepresentationPart* contactRep = static_cast<_resqml20__SealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1)->SealedContactRepresentation.back();

    resqml20__IntegerHdf5Array * xmlListOfIdenticalNodes = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
    xmlListOfIdenticalNodes->NullValue = (std::numeric_limits<int>::max)();
    xmlListOfIdenticalNodes->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
    xmlListOfIdenticalNodes->Values->HdfProxy = proxy->newResqmlReference();
    ostringstream ossForHdf;
    ossForHdf << "listOfIdenticalNodes_contact" << contactRep->Index;
    xmlListOfIdenticalNodes->Values->PathInHdfFile = getHdfGroup() + "/" + ossForHdf.str();
    contactRep->IdenticalNodeIndices = xmlListOfIdenticalNodes;
    // ************ HDF *************
    hsize_t dim[2] = {identicalNodesCount, patchCount};
    proxy->writeArrayNd(getHdfGroup(),
        ossForHdf.str(), H5T_NATIVE_UINT,
        identicalNodes,
        dim, 2);
}

void SealedSurfaceFrameworkRepresentation::pushBackContactPatch(
    unsigned int contactIndex,
    int const* nodeIndicesOnSupportingRepresentation, unsigned int nodeCount,
	RESQML2_NS::AbstractRepresentation * supportingRepresentation,
	EML2_NS::AbstractHdfProxy * proxy)
{
	if (nodeIndicesOnSupportingRepresentation == nullptr) {
		throw invalid_argument("The array of node indices cannot be null.");
	}
	if (nodeCount == 0) {
		throw invalid_argument("The nodes count cannot be zero.");
	}
	if (supportingRepresentation == nullptr) {
		throw invalid_argument("The supporting representation cannot be null.");
	}
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

    _resqml20__SealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml20__SealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

	if (contactIndex >= orgRep->SealedContactRepresentation.size()) {
		throw out_of_range("Invalid contact index.");
	}

    resqml20__SealedContactRepresentationPart* contactRep = static_cast<resqml20__SealedContactRepresentationPart*>(orgRep->SealedContactRepresentation[contactIndex]);

    // we look for the supporting representation index
    int representationIndex = -1;
	const unsigned int representationCount = getRepresentationCount();
	for (unsigned int i = 0; i < representationCount; ++i) {
		if (getRepresentation(i)->getUuid() == supportingRepresentation->getUuid()) {
			representationIndex = i;
			break;
		}
	}
	if (representationIndex == -1) {
		throw invalid_argument("The supporting representation is not referenced by the sealed surface framework");
	}

    resqml20__ContactPatch* contactPatch = soap_new_resqml20__ContactPatch(gsoapProxy2_0_1->soap);
    contactPatch->PatchIndex = contactRep->Contact.size();
    contactPatch->Count = nodeCount;
    contactPatch->RepresentationIndex = representationIndex;

    resqml20__IntegerHdf5Array* xmlSupportingRepresentationNodes = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
    xmlSupportingRepresentationNodes->NullValue = (std::numeric_limits<int>::max)();
    xmlSupportingRepresentationNodes->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
    xmlSupportingRepresentationNodes->Values->HdfProxy = proxy->newResqmlReference();
    ostringstream ossForHdf;
    ossForHdf << "SupportingRepresentationNodes_contact" << contactIndex << "_patch" << contactPatch->PatchIndex;
    xmlSupportingRepresentationNodes->Values->PathInHdfFile = getHdfGroup() + "/" + ossForHdf.str();
    contactPatch->SupportingRepresentationNodes = xmlSupportingRepresentationNodes;
    // ************ HDF *************
    hsize_t dim = nodeCount;
    proxy->writeArrayNd(getHdfGroup(),
                        ossForHdf.str(), H5T_NATIVE_UINT,
                        nodeIndicesOnSupportingRepresentation,
                        &dim, 1);

    // adding the contact patch to the contact representation
    contactRep->Contact.push_back(contactPatch);
}

unsigned int SealedSurfaceFrameworkRepresentation::getContactCount() const
{
	_resqml20__SealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml20__SealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

	if (orgRep->SealedContactRepresentation.size() > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too much contact representations for fesapi");
	}

	return static_cast<unsigned int>(orgRep->SealedContactRepresentation.size());
}

gsoap_resqml2_0_1::resqml20__SealedContactRepresentationPart* SealedSurfaceFrameworkRepresentation::getContact(unsigned int crIndex) const
{
	if (crIndex >= getContactCount()) {
		throw out_of_range("The index of the contact representation is out of range.");
	}

	return static_cast<_resqml20__SealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1)->SealedContactRepresentation[crIndex];
}

gsoap_resqml2_0_1::resqml20__IdentityKind SealedSurfaceFrameworkRepresentation::getContactPatchIdentityKind(unsigned int crIndex) const
{
	return getContact(crIndex)->IdentityKind;
}

bool SealedSurfaceFrameworkRepresentation::areAllContactPatchNodesIdentical(unsigned int crIndex) const
{
	return getContact(crIndex)->IdenticalNodeIndices == nullptr;
}

unsigned int SealedSurfaceFrameworkRepresentation::getIdenticalContactPatchNodeCount(unsigned int crIndex) const
{
	if (areAllContactPatchNodesIdentical(crIndex)) {
		throw invalid_argument("The nodes are all identical");
	}

	ULONG64 result = getCountOfIntegerArray(getContact(crIndex)->IdenticalNodeIndices);
	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too much identical nodes for fesapi");
	}

	return static_cast<unsigned int>(result);
}

void SealedSurfaceFrameworkRepresentation::getIdenticalContactPatchNodeIndices(unsigned int crIndex, unsigned int * nodeIndices) const
{
	if (areAllContactPatchNodesIdentical(crIndex)) {
		throw invalid_argument("The nodes are all identical");
	}

	readArrayNdOfUIntValues(getContact(crIndex)->IdenticalNodeIndices, nodeIndices);
}

unsigned int SealedSurfaceFrameworkRepresentation::getContactPatchCount(unsigned int crIndex) const
{
	resqml20__SealedContactRepresentationPart* contactRep = getContact(crIndex);

	if (contactRep->Contact.size() > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too much contact patches for fesapi");
	}

	return static_cast<unsigned int>(contactRep->Contact.size());
}

gsoap_resqml2_0_1::resqml20__ContactPatch* SealedSurfaceFrameworkRepresentation::getContactPatch(unsigned int crIndex, unsigned int cpIndex) const
{
	resqml20__SealedContactRepresentationPart* contactRep = getContact(crIndex);

	if (cpIndex >= getContactPatchCount(crIndex)) {
		throw out_of_range("The index of the contact patch is out of range.");
	}

	return contactRep->Contact[cpIndex];
}

RESQML2_NS::AbstractRepresentation* SealedSurfaceFrameworkRepresentation::getRepresentationOfContactPatch(unsigned int contactIdx, unsigned int cpIndex) const
{
	return getRepresentation(getRepresentationIndexOfContactPatch(contactIdx, cpIndex));
}

unsigned int SealedSurfaceFrameworkRepresentation::getRepresentationIndexOfContactPatch(unsigned int contactIdx, unsigned int cpIndex) const
{
	const ULONG64 index = getContactPatch(contactIdx, cpIndex)->RepresentationIndex;

	if (index > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("The index of the representation is too big.");
	}

	return static_cast<unsigned int>(index);
}

unsigned int SealedSurfaceFrameworkRepresentation::getContactPatchNodeCount(unsigned int crIndex, unsigned int cpIndex) const
{
	ULONG64 result = getCountOfIntegerArray(getContactPatch(crIndex, cpIndex)->SupportingRepresentationNodes);
	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too much nodes in this contact patch for fesapi");
	}

	return static_cast<unsigned int>(result);
}

void SealedSurfaceFrameworkRepresentation::getContactPatchNodeIndices(unsigned int crIndex, unsigned int cpIndex, unsigned int * nodeIndices) const
{
	readArrayNdOfUIntValues(getContactPatch(crIndex, cpIndex)->SupportingRepresentationNodes, nodeIndices);
}
