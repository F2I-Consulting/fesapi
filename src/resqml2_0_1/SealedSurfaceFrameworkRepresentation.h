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

#include "resqml2_0_1/SealedVolumeFrameworkRepresentation.h"

namespace RESQML2_NS {
	class AbstractHdfProxy;
}

namespace RESQML2_0_1_NS
{
	/**
	* A collection of contact, which are a list of contact patches and their identities.
	* This collection of contact is completed by a set of representations gathered at the representation set representation level.
	*/
	class DLL_IMPORT_OR_EXPORT SealedSurfaceFrameworkRepresentation : public AbstractSurfaceFrameworkRepresentation
	{
	private:
		/**
		* Get a contact from its index in this framework.
		*
		* @param contactIdx	The index of the contact in the contact list. It must be in the interval [0..getContactCount()[.
		* @return			A contact from its index in this framework.
		*/
		gsoap_resqml2_0_1::resqml2__SealedContactRepresentationPart* getContact(unsigned int contactIdx) const;

		/**
		* Get a contact patch from its index in a contact of this framework.
		*
		* @param contactIdx	The index of the contact in the contact list. It must be in the interval [0..getContactCount()[.
		* @param cpIndex	The index of the contact patch in the contact. It must be in the interval [0..getContactPatchCount()[.
		* @return			A contact patch from its index in a contact of this framework.
		*/
		gsoap_resqml2_0_1::resqml2__ContactPatch* getContactPatch(unsigned int contactIdx, unsigned int cpIndex) const;
		
		friend void SealedVolumeFrameworkRepresentation::setSealedSurfaceFramework(SealedSurfaceFrameworkRepresentation* ssf);
		std::vector<SealedVolumeFrameworkRepresentation*> svfSet;

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
		 * Push back a contact in the structural framework with implicit identical nodes.
		 *
		 * After calling the following method, ContactPatch container of the newly pushed contact
		 * remains empty. After this call, do not forget to call the pushBackContactPatch method for each ContactPatch of
		 * the contact.
		 *
		 * @param kind  Identity kind.
		 */
		void pushBackContact(gsoap_resqml2_0_1::resqml2__IdentityKind kind);

		/**
		 * Push back a contact in the structural framework.
		 *
		 * After calling the following method, ContactPatch container of the newly pushed contact
		 * remains empty. After this call, do not forget to call the pushBackContactPatch method for each ContactPatch of
		 * the contact.
		 *
		 * @param kind                  Identity kind.
		 * @param patchCount            The number of contact patch within this sealed contact
		 * @param identicalNodesCount   The number of identical nodes along this sealed contact
		 * @param identicalNodes        The patchCount x identicalNodesCount sized 1D array of identical nodes indices
		 * @param proxy                 The hdf proxy
		 */
		void pushBackContact(
			gsoap_resqml2_0_1::resqml2__IdentityKind kind,
			unsigned int patchCount,
			unsigned int identicalNodesCount,
			int * identicalNodes,
			COMMON_NS::AbstractHdfProxy * proxy);

		/**
		 * Push back a contact patch in a particular contact of the structural framework.
		 * @param contactIdx							The index of the contact which will contain this contact patch.
		 * @param nodeIndicesOnSupportingRepresentation	The nodes defining the contact patch on the supporting representation.
		 * @param nodeCount								The node count of this contact patch.
		 * @param supportingRepresentation 				The supporting representation of this contact patch.
		 */
		void pushBackContactPatch(
			unsigned int contactIdx,
			int * nodeIndicesOnSupportingRepresentation, unsigned int nodeCount,
			class AbstractRepresentation * supportingRepresentation,
			COMMON_NS::AbstractHdfProxy * proxy);

		unsigned int getContactCount() const;

		/**
		* Get the contact patch identity kind of a contact located at a particular index.
		*
		* @param contactIdx	The index of the contact in the contact list. It must be in the interval [0..getContactCount()[.
		* @return			The contact patch identity kind of the contact located at a particular index.
		*/
		gsoap_resqml2_0_1::resqml2__IdentityKind getContactPatchIdentityKind(unsigned int contactIdx) const;

		/*
		* Check if all nodes of contact patches are identical in a contact.
		*
		* @param contactIdx	The index of the contact in the contact list. It must be in the interval [0..getContactCount()[.
		* @return			True if all node of contact patches are identical else false.
		*/
		bool areAllContactPatchNodesIdentical(unsigned int contactIdx) const;

		/**
		* Get the count of identical nodes of a particular contact.
		* Throw an exception if all nodes are identical (see areAllContactPatchNodesIdenticalInContactRep()).
		*
		* @param contactIdx	The index of the contact in the contact list. It must be in the interval [0..getContactCount()[.
		* @return			The count of identical nodes of a particular contact.
		*/
		unsigned int getIdenticalContactPatchNodeCount(unsigned int contactIdx) const;

		/**
		* Get the node indices of all contact patches which are identical.
		* Throw an exception if all nodes are identical (see areAllContactPatchNodesIdenticalInContactRep()).
		*
		* @param contactIdx		The index of the contact in the contact list. It must be in the interval [0..getContactCount()[.
		* @param nodeIndices	This array must be preallocated with getIdenticalNodeCount(). It won't be deleted by fesapi.
		*						It will be filled in with the desired node indices.
		*/
		void getIdenticalContactPatchNodeIndices(unsigned int contactIdx, unsigned int * nodeIndices) const;

		/**
		* Get the count of contact patches in a particular contact represenation of this framework.
		*
		* @param contactIdx	The index of the contact in the contact list. It must be in the interval [0..getContactCount()[.
		* @return			The count of contact patches in a particular contact represenation in this framework.
		*/
		unsigned int getContactPatchCount(unsigned int contactIdx) const;

		/**
		* Get the representation (for instance the triangulated surface) where a particular contact patch has been defined.
		*
		* @param contactIdx	The index of the contact in the contact list. It must be in the interval [0..getContactCount()[.
		* @param cpIndex	The index of the contact patch in the contact. It must be in the interval [0..getContactPatchCount()[.
		* @return			The representation where the contact patch has been defined.
		*/
		RESQML2_NS::AbstractRepresentation* getRepresentationOfContactPatch(unsigned int contactIdx, unsigned int cpIndex) const;

		/**
		* Get the count of nodes of a particular contact patch.
		*
		* @param contactIdx	The index of the contact in the contact list. It must be in the interval [0..getContactCount()[.
		* @param cpIndex	The index of the contact patch in the contact. It must be in the interval [0..getContactPatchCount()[.
		* @return			The count of nodes of a particular contact patch.
		*/
		unsigned int getContactPatchNodeCount(unsigned int contactIdx, unsigned int cpIndex) const;

		/**
		* Get the node indices of a particular contact patch.
		* The returned indices are associated to the node array of the representation of the particular contact patch (see getRepresentationOfContactPatch()).
		*
		* @param contactIdx		The index of the contact in the contact list. It must be in the interval [0..getContactCount()[.
		* @param cpIndex		The index of the contact patch in the contact. It must be in the interval [0..getContactPatchCount()[.
		* @param nodeIndices	This array must be preallocated with getNodeCountOfContactPatch(). It won't be deleted by fesapi.
		*						It will be filled in with the desired node indices.
		*/
		void getContactPatchNodeIndices(unsigned int contactIdx, unsigned int cpIndex, unsigned int * nodeIndices) const;

		std::vector<epc::Relationship> getAllSourceRelationships() const;

		static const char* XML_TAG;
		std::string getXmlTag() const { return XML_TAG; }

		virtual gsoap_resqml2_0_1::eml20__DataObjectReference* getHdfProxyDor() const;
	};

}
