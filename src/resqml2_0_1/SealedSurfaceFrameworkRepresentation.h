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
#pragma once

#include "resqml2_0_1/RepresentationSetRepresentation.h"

namespace resqml2 {
	class AbstractHdfProxy;
}

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT SealedSurfaceFrameworkRepresentation : public RepresentationSetRepresentation
	{

	public:

		/**
		* Only to be used in partial transfer context
		*/
		SealedSurfaceFrameworkRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RepresentationSetRepresentation(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 * @param interp    The structural organization interpretation the instance interprets.
		 * @param guid      The guid to set to the representation. If empty then a new guid will be generated.
		 * @param title     A title for the instance to create.
		 */
		SealedSurfaceFrameworkRepresentation(class StructuralOrganizationInterpretation* interp,
								const std::string & guid,
								const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 */
		SealedSurfaceFrameworkRepresentation(gsoap_resqml2_0_1::_resqml2__SealedSurfaceFrameworkRepresentation* fromGsoap): RepresentationSetRepresentation(fromGsoap) {}

		/**
		 * Destructor does nothing since the memory is managed by the gsoap context.
		 */
		~SealedSurfaceFrameworkRepresentation() {}

		/**
		 * Pushes back a contact representation in the structural framework with implicit identical nodes.
		 *
		 * After calling the following method, ContactPatch containter of the newly pushed SealedContactRepresentation
		 * remains empty. After this call, do not forget to call the pushBackContactPatch method for each ContactPatch of
		 * the SealedContactRepresentation.
		 *
		 * @param kind  Identity kind.
		 */
		void pushBackSealedContactRepresentation(const gsoap_resqml2_0_1::resqml2__IdentityKind & kind);

		/**
		 * Pushes back a contact representation in the structural framework.
		 *
		 * After calling the following method, ContactPatch containter of the newly pushed SealedContactRepresentation
		 * remains empty. After this call, do not forget to call the pushBackContactPatch method for each ContactPatch of
		 * the SealedContactRepresentation.
		 *
		 * @param kind                  Identity kind.
		 * @param patchCount            The number of contact patch within this sealed contact representation
		 * @param identicalNodesCount   The number of identical nodes along this sealed contact representation
		 * @param identicalNodes        The patchCount x identicalNodesCount sized 1D array of identical nodes indices
		 * @param proxy                 The hdf proxy
		 */
		void pushBackSealedContactRepresentation(
			const gsoap_resqml2_0_1::resqml2__IdentityKind & kind,
			const unsigned int & patchCount,
			const unsigned int & identicalNodesCount,
			int * identicalNodes,
			common::AbstractHdfProxy * proxy);

		/**
		 * Pushes back a contact patch in a particular sealed contact representation of the structural framework.
		 * @param contactIndex							The index of the contact which will contain this contact patch.
		 * @param nodeIndicesOnSupportingRepresentation	The nodes defining the contact patch on the supporting representation.
		 * @param NodeCount								The node count of this contact patch.
		 * @param supportingRepresentation 				The supporting representation of this contact patch.
		 */
		 void pushBackContactPatchInSealedContactRepresentation(
			const unsigned int & contactIndex,
			int * nodeIndicesOnSupportingRepresentation, const unsigned int & NodeCount,
			class AbstractRepresentation * supportingRepresentation,
			common::AbstractHdfProxy * proxy);

		 /**
		  * Push back a contact identity in the structural framework with implicit identical nodes
		  * @param kind                                 Identity kind.
		  * @param sealedContactRepresentationsCount    The number of sealed contact representations involved within the identity.
		  * @param sealedContactRepresentationsIndexes  The sealed contact representations involved within the identity.
		  * @param proxy                                The hdf proxy.
		  */
		 void pushBackContactIdentity(
			const gsoap_resqml2_0_1::resqml2__IdentityKind & kind,
			const unsigned int & sealedContactRepresentationsCount, int * sealedContactRepresentationsIndexes,
			common::AbstractHdfProxy * proxy);

		 /**
		  * Push back a contact identity in the structural framework
		  * @param kind                                 Identity kind.
		  * @param sealedContactRepresentationsCount    The number of sealed contact representations involved within the identity.
		  * @param sealedContactRepresentationsIndexes  The sealed contact representations involved within the identity.
		  * @param identicalNodesCount                  The number of identical nodes.
		  * @param identicalNodesIndexes                The indexes of the identical nodes.
		  * @param proxy                                The hdf proxy.
		  */
		 void pushBackContactIdentity(
			const gsoap_resqml2_0_1::resqml2__IdentityKind & kind,
			const unsigned int & sealedContactRepresentationsCount, int * sealedContactRepresentationsIndexes,
			const unsigned int & identicalNodesCount, int * identicalNodesIndexes,
			common::AbstractHdfProxy * proxy);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		virtual std::string getHdfProxyUuid() const;
	};

} // namespace resqml2_0_1
