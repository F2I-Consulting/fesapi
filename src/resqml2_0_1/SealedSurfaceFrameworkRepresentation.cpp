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
#include "resqml2_0_1/SealedSurfaceFrameworkRepresentation.h"

#include <stdexcept>
#include <sstream>

#include "hdf5.h"

#include "resqml2/AbstractLocal3dCrs.h"
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace epc;
using namespace resqml2_0_1;
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
    setMetadata(guid, title, "", -1, "", "", -1, "", "");

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
		common::AbstractHdfProxy * proxy)
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
		common::AbstractHdfProxy * proxy)
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
		common::AbstractHdfProxy * proxy)
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
		const unsigned int & identicalNodesCount, int * identicalNodesIndexes, common::AbstractHdfProxy * proxy)
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
