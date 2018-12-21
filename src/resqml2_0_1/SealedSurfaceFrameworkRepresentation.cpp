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
#include "resqml2_0_1/SealedSurfaceFrameworkRepresentation.h"

#include <stdexcept>
#include <sstream>

#include "hdf5.h"

#include "resqml2/AbstractLocal3dCrs.h"
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace epc;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* SealedSurfaceFrameworkRepresentation::XML_TAG = "SealedSurfaceFrameworkRepresentation";

SealedSurfaceFrameworkRepresentation::SealedSurfaceFrameworkRepresentation(
        StructuralOrganizationInterpretation* interp,
        const std::string & guid,
        const std::string & title
        ):
	RepresentationSetRepresentation(interp)
{
    if (!interp)
        throw invalid_argument("The structural organization interpretation cannot be null.");

    // proxy constructor
    gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORESealedSurfaceFrameworkRepresentation(interp->getGsoapContext(), 1);
    _resqml2__SealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml2__SealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

    orgRep->RepresentedInterpretation = soap_new_eml20__DataObjectReference(gsoapProxy2_0_1->soap, 1);
    orgRep->RepresentedInterpretation->UUID.assign(interp->getUuid());

    initMandatoryMetadata();
    setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	// XML relationships
    setInterpretation(interp);
}

void SealedSurfaceFrameworkRepresentation::pushBackSealedContactRepresentation(const gsoap_resqml2_0_1::resqml2__IdentityKind & kind)
{
    _resqml2__SealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml2__SealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

    resqml2__SealedContactRepresentationPart* contactRep = soap_new_resqml2__SealedContactRepresentationPart(gsoapProxy2_0_1->soap, 1);
    contactRep->Index = orgRep->SealedContactRepresentation.size();
    contactRep->IdentityKind = kind;
    orgRep->SealedContactRepresentation.push_back(contactRep);
}

void SealedSurfaceFrameworkRepresentation::pushBackSealedContactRepresentation(
        const gsoap_resqml2_0_1::resqml2__IdentityKind & kind,
        const unsigned int & patchCount,
        const unsigned int & identicalNodesCount,
        int * identicalNodes,
		COMMON_NS::AbstractHdfProxy * proxy)
{
    if (patchCount < 2)
        throw invalid_argument("Contact point count cannot be less than two.");
    if (identicalNodesCount <= 0)
        throw invalid_argument("The identical nodes count cannot be lesser or equal to zero.");
    if (!identicalNodes)
        throw invalid_argument("The array of identical nodes cannot be null.");
    if (!proxy)
        throw invalid_argument("The HDF proxy cannot be null.");

    setHdfProxy(proxy);
    _resqml2__SealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml2__SealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

    resqml2__SealedContactRepresentationPart* contactRep = soap_new_resqml2__SealedContactRepresentationPart(gsoapProxy2_0_1->soap, 1);
    contactRep->Index = orgRep->SealedContactRepresentation.size();
    orgRep->SealedContactRepresentation.push_back(contactRep);

    resqml2__IntegerHdf5Array * xmlListOfIdenticalNodes = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
    xmlListOfIdenticalNodes->NullValue = (std::numeric_limits<int>::max)();
    xmlListOfIdenticalNodes->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
    xmlListOfIdenticalNodes->Values->HdfProxy = proxy->newResqmlReference();
    ostringstream ossForHdf;
    ossForHdf << "listOfIdenticalNodes_contact" << contactRep->Index;
    xmlListOfIdenticalNodes->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/" + ossForHdf.str();
    contactRep->IdenticalNodeIndices = xmlListOfIdenticalNodes;
    // ************ HDF *************
    hsize_t dim[2] = {identicalNodesCount, patchCount};
    proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
        ossForHdf.str(), H5T_NATIVE_UINT,
        identicalNodes,
        dim, 2);
}

void SealedSurfaceFrameworkRepresentation::pushBackContactPatchInSealedContactRepresentation(
        const unsigned int & contactIndex,
        int * nodeIndicesOnSupportingRepresentation, const unsigned int & NodeCount,
        AbstractRepresentation * supportingRepresentation,
		COMMON_NS::AbstractHdfProxy * proxy)
{
	if (nodeIndicesOnSupportingRepresentation == nullptr) {
		throw invalid_argument("The array of node indices cannot be null.");
	}
	if (NodeCount <= 0) {
		throw invalid_argument("The nodes count cannot be lesser or equal to zero.");
	}
	if (supportingRepresentation == nullptr) {
		throw invalid_argument("The supporting representation cannot be null.");
	}

    setHdfProxy(proxy);
    _resqml2__SealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml2__SealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

	if (contactIndex >= orgRep->SealedContactRepresentation.size()) {
		throw invalid_argument("Invalid contact index.");
	}

    resqml2__SealedContactRepresentationPart* contactRep = static_cast<resqml2__SealedContactRepresentationPart*>(orgRep->SealedContactRepresentation[contactIndex]);

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

    resqml2__ContactPatch* contactPatch = soap_new_resqml2__ContactPatch(gsoapProxy2_0_1->soap, 1);
    contactPatch->PatchIndex = contactRep->Contact.size();
    contactPatch->Count = NodeCount;
    contactPatch->RepresentationIndex = representationIndex;

    resqml2__IntegerHdf5Array* xmlSupportingRepresentationNodes = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
    xmlSupportingRepresentationNodes->NullValue = (std::numeric_limits<int>::max)();
    xmlSupportingRepresentationNodes->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
    xmlSupportingRepresentationNodes->Values->HdfProxy = proxy->newResqmlReference();
    ostringstream ossForHdf;
    ossForHdf << "SupportingRepresentationNodes_contact" << contactIndex << "_patch" << contactPatch->PatchIndex;
    xmlSupportingRepresentationNodes->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/" + ossForHdf.str();
    contactPatch->SupportingRepresentationNodes = xmlSupportingRepresentationNodes;
    // ************ HDF *************
    hsize_t dim[1] = {NodeCount};
    proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
                        ossForHdf.str(), H5T_NATIVE_UINT,
                        nodeIndicesOnSupportingRepresentation,
                        dim, 1);

    // adding the contact patch to the contact representation
    contactRep->Contact.push_back(contactPatch);
}

void SealedSurfaceFrameworkRepresentation::pushBackContactIdentity(
        const gsoap_resqml2_0_1::resqml2__IdentityKind & kind,
        const unsigned int & sealedContactRepresentationsCount, int * sealedContactRepresentationsIndexes,
		COMMON_NS::AbstractHdfProxy * proxy)
{
    _resqml2__SealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml2__SealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

    resqml2__ContactIdentity * contactIdentity = soap_new_resqml2__ContactIdentity(gsoapProxy2_0_1->soap, 1);
    contactIdentity->IdentityKind = kind;

    // ListOfContactRepresentations handling
    resqml2__IntegerHdf5Array * xmlListOfContactRepresentations = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
    xmlListOfContactRepresentations->NullValue = (std::numeric_limits<int>::max)();
    xmlListOfContactRepresentations->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
    xmlListOfContactRepresentations->Values->HdfProxy = proxy->newResqmlReference();
    ostringstream ossForHdfContactRepresentations;
    ossForHdfContactRepresentations << "contactIdentity_listOfContactRep_" << orgRep->ContactIdentity.size() ;
    xmlListOfContactRepresentations->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/" + ossForHdfContactRepresentations.str();
    contactIdentity->ListOfContactRepresentations = xmlListOfContactRepresentations;
    // ************ HDF *************
    hsize_t dimContactRepresentations[1] = {sealedContactRepresentationsCount};
    proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
        ossForHdfContactRepresentations.str(), H5T_NATIVE_UINT,
        sealedContactRepresentationsIndexes,
        dimContactRepresentations, 1);

    orgRep->ContactIdentity.push_back(contactIdentity);
}

void SealedSurfaceFrameworkRepresentation::pushBackContactIdentity(
        const gsoap_resqml2_0_1::resqml2__IdentityKind & kind,
        const unsigned int & sealedContactRepresentationsCount, int * sealedContactRepresentationsIndexes,
		const unsigned int & identicalNodesCount, int * identicalNodesIndexes, COMMON_NS::AbstractHdfProxy * proxy)
{
    _resqml2__SealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml2__SealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

    resqml2__ContactIdentity * contactIdentity = soap_new_resqml2__ContactIdentity(gsoapProxy2_0_1->soap, 1);
    contactIdentity->IdentityKind = kind;

    // ListOfContactRepresentations handling
    resqml2__IntegerHdf5Array * xmlListOfContactRepresentations = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
    xmlListOfContactRepresentations->NullValue = (std::numeric_limits<int>::max)();
    xmlListOfContactRepresentations->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
    xmlListOfContactRepresentations->Values->HdfProxy = proxy->newResqmlReference();
    ostringstream ossForHdfContactRepresentations;
    ossForHdfContactRepresentations << "contactIdentity_listOfContactRep_" << orgRep->ContactIdentity.size() ;
    xmlListOfContactRepresentations->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/" + ossForHdfContactRepresentations.str();
    contactIdentity->ListOfContactRepresentations = xmlListOfContactRepresentations;
    // ************ HDF *************
    hsize_t dimContactRepresentations[1] = {sealedContactRepresentationsCount};
    proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
        ossForHdfContactRepresentations.str(), H5T_NATIVE_UINT,
        sealedContactRepresentationsIndexes,
        dimContactRepresentations, 1);

    // ListOfIdenticalNodes handling
    resqml2__IntegerHdf5Array * xmlListOfIdenticalNodes = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
    xmlListOfIdenticalNodes->NullValue = (std::numeric_limits<int>::max)();
    xmlListOfIdenticalNodes->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
    xmlListOfIdenticalNodes->Values->HdfProxy = proxy->newResqmlReference();
    ostringstream ossForHdfIdenticalNodes;
    ossForHdfIdenticalNodes << "contactIdentity_listOfIdenticalNodes_" << orgRep->ContactIdentity.size() ;
    xmlListOfIdenticalNodes->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/" + ossForHdfIdenticalNodes.str();
    contactIdentity->ListOfIdenticalNodes = xmlListOfIdenticalNodes;
    // ************ HDF *************
    hsize_t dimIdenticalNodes[2] = {identicalNodesCount, sealedContactRepresentationsCount};
    proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
        ossForHdfIdenticalNodes.str(), H5T_NATIVE_UINT,
        identicalNodesIndexes,
        dimIdenticalNodes, 2);

    orgRep->ContactIdentity.push_back(contactIdentity);
}

std::string SealedSurfaceFrameworkRepresentation::getHdfProxyUuid() const
{
    string result = "";
    _resqml2__SealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml2__SealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

    if (orgRep->SealedContactRepresentation.size() > 0 && static_cast<resqml2__SealedContactRepresentationPart*>(orgRep->SealedContactRepresentation[0])->IdenticalNodeIndices != nullptr)
    {
        resqml2__SealedContactRepresentationPart *sealedContactRep = static_cast<resqml2__SealedContactRepresentationPart*>(orgRep->SealedContactRepresentation[0]);
        result = static_cast<resqml2__IntegerHdf5Array *>(sealedContactRep->IdenticalNodeIndices)->Values->HdfProxy->UUID;
    }

    return result;
}

