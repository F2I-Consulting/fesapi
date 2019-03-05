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
#pragma once

#include "resqml2_0_1/AbstractSurfaceFrameworkRepresentation.h"

namespace RESQML2_NS {
	class AbstractHdfProxy;
}

namespace RESQML2_0_1_NS
{
	/**
	* A collection of contact representations parts, which are a list of contact patches and their identities.
	* This collection of contact representations is completed by a set of representations gathered at the representation set representation level.
	*/
	class DLL_IMPORT_OR_EXPORT SealedSurfaceFrameworkRepresentation : public AbstractSurfaceFrameworkRepresentation
	{
	private:
		/**
		* Get a contact representation from its index in this framework.
		*
		* @param crIndex	The index of the contact representation in the contact representation list. It must be in the interval [0..getContactRepCount()[.
		* @return			A contact representation from its index in this framework.
		*/
		gsoap_resqml2_0_1::resqml2__SealedContactRepresentationPart* getContactRepresentation(unsigned int crIndex) const;

		/**
		* Get a contact patch from its index in a contact representation of this framework.
		*
		* @param crIndex	The index of the contact representation in the contact representation list. It must be in the interval [0..getContactRepCount()[.
		* @param cpIndex	The index of the contact patch in the contact representation. It must be in the interval [0..getContactPatchCount()[.
		* @return			A contact patch from its index in a contact representation of this framework.
		*/
		gsoap_resqml2_0_1::resqml2__ContactPatch* getContactPatch(unsigned int crIndex, unsigned int cpIndex) const;

	public:

		/**
		* Only to be used in partial transfer context
		*/
		SealedSurfaceFrameworkRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractSurfaceFrameworkRepresentation(partialObject) {}

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
		SealedSurfaceFrameworkRepresentation(gsoap_resqml2_0_1::_resqml2__SealedSurfaceFrameworkRepresentation* fromGsoap) : AbstractSurfaceFrameworkRepresentation(fromGsoap) {}

		/**
		 * Destructor does nothing since the memory is managed by the gsoap context.
		 */
		~SealedSurfaceFrameworkRepresentation() {}

		/**
		 * Pushes back a contact representation in the structural framework with implicit identical nodes.
		 *
		 * After calling the following method, ContactPatch container of the newly pushed SealedContactRepresentation
		 * remains empty. After this call, do not forget to call the pushBackContactPatch method for each ContactPatch of
		 * the SealedContactRepresentation.
		 *
		 * @param kind  Identity kind.
		 */
		void pushBackSealedContactRepresentation(const gsoap_resqml2_0_1::resqml2__IdentityKind & kind);

		/**
		 * Pushes back a contact representation in the structural framework.
		 *
		 * After calling the following method, ContactPatch container of the newly pushed SealedContactRepresentation
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
			COMMON_NS::AbstractHdfProxy * proxy);

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
			COMMON_NS::AbstractHdfProxy * proxy);

		unsigned int getContactRepCount() const;

		/**
		* Get the contact patch identity kind of a contact representation located at a particular index.
		*
		* @param crIndex	The index of the contact representation in the contact representation list. It must be in the interval [0..getContactRepCount()[.
		* @return			The contact patch identity kind of the contact representation located at a particular index.
		*/
		gsoap_resqml2_0_1::resqml2__IdentityKind getContactPatchIdentityKind(unsigned int crIndex) const;

		/*
		* Check if all nodes of contact patches are identical in a contact representation.
		*
		* @param crIndex	The index of the contact representation in the contact representation list. It must be in the interval [0..getContactRepCount()[.
		* @return			True if all node of contact patches are identical else false.
		*/
		bool areAllContactPatchNodesIdenticalInContactRep(unsigned int crIndex) const;

		/**
		* Get the count of identical nodes of a particular contact representation.
		* Throw an exception if all nodes are identical (see areAllContactPatchNodesIdenticalInContactRep()).
		*
		* @param crIndex	The index of the contact representation in the contact representation list. It must be in the interval [0..getContactRepCount()[.
		* @return			The count of identical nodes of a particular contact representation.
		*/
		unsigned int getIdenticalNodeCountOfContactRep(unsigned int crIndex) const;

		/**
		* Get the node indices of all contact representations which are identical.
		* Throw an exception if all nodes are identical (see areAllContactPatchNodesIdenticalInContactRep()).
		*
		* @param crIndex		The index of the contact representation in the contact representation list. It must be in the interval [0..getContactRepCount()[.
		* @param nodeIndices	This array must be preallocated with getIdenticalNodeCountOfContactRep(). It won't be deleted by fesapi.
		*						It will be filled in with the desired node indices.
		*/
		void getIdenticalNodeIndicesOfContactRep(unsigned int crIndex, unsigned int * nodeIndices) const;

		/**
		* Get the count of contact patches in a particular contact represenation of this framework.
		*
		* @param crIndex	The index of the contact representation in the contact representation list. It must be in the interval [0..getContactRepCount()[.
		* @return			The count of contact patches in a particular contact represenation in this framework.
		*/
		unsigned int getContactPatchCount(unsigned int crIndex) const;

		/**
		* Get the representation (for instance the triangulated surface) where a particular contact patch has been defined.
		*
		* @param crIndex	The index of the contact representation in the contact representation list. It must be in the interval [0..getContactRepCount()[.
		* @param cpIndex	The index of the contact patch in the contact representation. It must be in the interval [0..getContactPatchCount()[.
		* @return			The representation where the contact patch has been defined.
		*/
		RESQML2_NS::AbstractRepresentation* getRepresentationOfContactPatch(unsigned int crIndex, unsigned int cpIndex) const;

		/**
		* Get the count of nodes of a particular contact patch.
		*
		* @param crIndex	The index of the contact representation in the contact representation list. It must be in the interval [0..getContactRepCount()[.
		* @param cpIndex	The index of the contact patch in the contact representation. It must be in the interval [0..getContactPatchCount()[.
		* @return			The count of nodes of a particular contact patch.
		*/
		unsigned int getNodeCountOfContactPatch(unsigned int crIndex, unsigned int cpIndex) const;

		/**
		* Get the node indices of a particular contact patch.
		* The returned indices are associated to the node array of the representation of the particular contact patch (see getRepresentationOfContactPatch()).
		*
		* @param crIndex		The index of the contact representation in the contact representation list. It must be in the interval [0..getContactRepCount()[.
		* @param cpIndex		The index of the contact patch in the contact representation. It must be in the interval [0..getContactPatchCount()[.
		* @param nodeIndices	This array must be preallocated with getNodeCountOfContactPatch(). It won't be deleted by fesapi.
		*						It will be filled in with the desired node indices.
		*/
		void getNodeIndicesOfContactPatch(unsigned int crIndex, unsigned int cpIndex, unsigned int * nodeIndices) const;

		static const char* XML_TAG;
		virtual std::string getXmlTag() const { return XML_TAG; }

		virtual std::string getHdfProxyUuid() const;
	};

}
