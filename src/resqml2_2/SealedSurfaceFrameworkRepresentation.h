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

#include "../resqml2/SealedSurfaceFrameworkRepresentation.h"

namespace RESQML2_2_NS
{
	/**
	 * A collection of contact, which are a list of contact patches and their identities. This
	 * collection of contact is completed by a set of representations gathered at the representation
	 * set representation level.
	 */
	class SealedSurfaceFrameworkRepresentation final : public RESQML2_NS::SealedSurfaceFrameworkRepresentation
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT SealedSurfaceFrameworkRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::SealedSurfaceFrameworkRepresentation(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The structural organization interpretation the instance interprets.
		 * @param 	  	guid  	The guid to set to the representation. If empty then a new guid will be
		 * 						generated.
		 * @param 	  	title 	A title for the instance to create.
		 */
		SealedSurfaceFrameworkRepresentation(RESQML2_NS::StructuralOrganizationInterpretation* interp,
			const std::string & guid,
			const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		SealedSurfaceFrameworkRepresentation(gsoap_eml2_3::_resqml22__SealedSurfaceFrameworkRepresentation* fromGsoap) : RESQML2_NS::SealedSurfaceFrameworkRepresentation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~SealedSurfaceFrameworkRepresentation() {}

		/**
		 * Push back a contact in the structural framework with implicit identical nodes.
		 * 
		 * After calling the following method, ContactPatch container of the newly pushed contact
		 * remains empty. After this call, do not forget to call the pushBackContactPatch method for
		 * each ContactPatch of the contact.
		 *
		 * @param 	kind	Identity kind.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind kind) final;

		/**
		 * Push back a contact in the structural framework.
		 * 
		 * After calling the following method, ContactPatch container of the newly pushed contact
		 * remains empty. After this call, do not forget to call the pushBackContactPatch method for
		 * each ContactPatch of the contact.
		 *
		 * @param 		  	kind			   	Identity kind.
		 * @param 		  	patchCount		   	The number of contact patch within this sealed contact.
		 * @param 		  	identicalNodesCount	The number of identical nodes along this sealed contact.
		 * @param [in,out]	identicalNodes	   	The patchCount x identicalNodesCount sized 1D array of
		 * 										identical nodes indices.
		 * @param [in,out]	proxy			   	The hdf proxy.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackContact(
			gsoap_resqml2_0_1::resqml20__IdentityKind kind,
			unsigned int patchCount,
			unsigned int identicalNodesCount,
			int const* identicalNodes,
			EML2_NS::AbstractHdfProxy * proxy) final;

		/**
		 * Push back a contact patch in a particular contact of the structural framework.
		 *
		 * @param 		  	contactIdx							 	The index of the contact which will
		 * 															contain this contact patch.
		 * @param [in,out]	nodeIndicesOnSupportingRepresentation	The nodes defining the contact patch
		 * 															on the supporting representation.
		 * @param 		  	nodeCount							 	The node count of this contact patch.
		 * @param [in,out]	supportingRepresentation			 	The supporting representation of this
		 * 															contact patch.
		 * @param [in,out]	proxy								 	If non-null, the proxy.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackContactPatch(
			unsigned int contactIdx,
			int const* nodeIndicesOnSupportingRepresentation, unsigned int nodeCount,
			RESQML2_NS::AbstractRepresentation * supportingRepresentation,
			EML2_NS::AbstractHdfProxy * proxy) final;

		DLL_IMPORT_OR_EXPORT unsigned int getContactCount() const final;

		/**
		 * Get the contact patch identity kind of a contact located at a particular index.
		 *
		 * @param 	contactIdx	The index of the contact in the contact list. It must be in the interval
		 * 						[0..getContactCount()[.
		 *
		 * @returns	The contact patch identity kind of the contact located at a particular index.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__IdentityKind getContactPatchIdentityKind(unsigned int contactIdx) const final;

		/**
		* Check if all nodes of contact patches are identical in a contact.
		*
		* @param contactIdx	The index of the contact in the contact list. It must be in the interval [0..getContactCount()[.
		* @return			True if all node of contact patches are identical else false.
		*/
		DLL_IMPORT_OR_EXPORT bool areAllContactPatchNodesIdentical(unsigned int contactIdx) const final;

		/**
		 * Get the count of identical nodes of a particular contact. Throw an exception if all nodes are
		 * identical (see areAllContactPatchNodesIdenticalInContactRep()).
		 *
		 * @param 	contactIdx	The index of the contact in the contact list. It must be in the interval
		 * 						[0..getContactCount()[.
		 *
		 * @returns	The count of identical nodes of a particular contact.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getIdenticalContactPatchNodeCount(unsigned int contactIdx) const final;

		/**
		 * Get the node indices of all contact patches which are identical. Throw an exception if all
		 * nodes are identical (see areAllContactPatchNodesIdenticalInContactRep()).
		 *
		 * @param 		  	contactIdx 	The index of the contact in the contact list. It must be in the
		 * 								interval [0..getContactCount()[.
		 * @param [in,out]	nodeIndices	This array must be preallocated with getIdenticalNodeCount(). It
		 * 								won't be deleted by fesapi. It will be filled in with the desired
		 * 								node indices.
		 */
		DLL_IMPORT_OR_EXPORT void getIdenticalContactPatchNodeIndices(unsigned int contactIdx, unsigned int * nodeIndices) const final;

		/**
		 * Get the count of contact patches in a particular contact represenation of this framework.
		 *
		 * @param 	contactIdx	The index of the contact in the contact list. It must be in the interval
		 * 						[0..getContactCount()[.
		 *
		 * @returns	The count of contact patches in a particular contact represenation in this framework.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getContactPatchCount(unsigned int contactIdx) const final;

		/**
		 * Get the representation (for instance the triangulated surface) where a particular contact
		 * patch has been defined.
		 *
		 * @param 	contactIdx	The index of the contact in the contact list. It must be in the interval
		 * 						[0..getContactCount()[.
		 * @param 	cpIndex   	The index of the contact patch in the contact. It must be in the interval
		 * 						[0..getContactPatchCount()[.
		 *
		 * @returns	The representation where the contact patch has been defined.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractRepresentation* getRepresentationOfContactPatch(unsigned int contactIdx, unsigned int cpIndex) const final;

		/**
		 * Get the representation index where a particular contact patch has been defined. The index is
		 * in the range [0..getRepresentationCount()[.
		 *
		 * @param 	contactIdx	The index of the contact in the contact list. It must be in the interval
		 * 						[0..getContactCount()[.
		 * @param 	cpIndex   	The index of the contact patch in the contact. It must be in the interval
		 * 						[0..getContactPatchCount()[.
		 *
		 * @returns	The representation index where the contact patch has been defined.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getRepresentationIndexOfContactPatch(unsigned int contactIdx, unsigned int cpIndex) const final;

		/**
		 * Get the count of nodes of a particular contact patch.
		 *
		 * @param 	contactIdx	The index of the contact in the contact list. It must be in the interval
		 * 						[0..getContactCount()[.
		 * @param 	cpIndex   	The index of the contact patch in the contact. It must be in the interval
		 * 						[0..getContactPatchCount()[.
		 *
		 * @returns	The count of nodes of a particular contact patch.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getContactPatchNodeCount(unsigned int contactIdx, unsigned int cpIndex) const final;

		/**
		 * Get the node indices of a particular contact patch. The returned indices are associated to
		 * the node array of the representation of the particular contact patch (see
		 * getRepresentationOfContactPatch()).
		 *
		 * @param 		  	contactIdx 	The index of the contact in the contact list. It must be in the
		 * 								interval [0..getContactCount()[.
		 * @param 		  	cpIndex	   	The index of the contact patch in the contact. It must be in the
		 * 								interval [0..getContactPatchCount()[.
		 * @param [in,out]	nodeIndices	This array must be preallocated with
		 * 								getNodeCountOfContactPatch(). It won't be deleted by fesapi. It
		 * 								will be filled in with the desired node indices.
		 */
		DLL_IMPORT_OR_EXPORT void getContactPatchNodeIndices(unsigned int contactIdx, unsigned int cpIndex, unsigned int * nodeIndices) const final;

	private:

		/**
		 * Get a contact from its index in this framework.
		 *
		 * @param 	contactIdx	The index of the contact in the contact list. It must be in the interval
		 * 						[0..getContactCount()[.
		 *
		 * @returns	A contact from its index in this framework.
		 */
		gsoap_eml2_3::resqml22__SealedContactRepresentationPart* getContact(unsigned int contactIdx) const;

		/**
		 * Get a contact patch from its index in a contact of this framework.
		 *
		 * @param 	contactIdx	The index of the contact in the contact list. It must be in the interval
		 * 						[0..getContactCount()[.
		 * @param 	cpIndex   	The index of the contact patch in the contact. It must be in the interval
		 * 						[0..getContactPatchCount()[.
		 *
		 * @returns	A contact patch from its index in a contact of this framework.
		 */
		gsoap_eml2_3::resqml22__ContactPatch* getContactPatch(unsigned int contactIdx, unsigned int cpIndex) const;
	};
}
