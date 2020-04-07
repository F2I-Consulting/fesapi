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

#include "AbstractSurfaceFrameworkRepresentation.h"

/** . */
namespace RESQML2_NS
{
	/**
	 * A collection of contact, which are a list of contact patches and their identities. This
	 * collection of contact is completed by a set of representations gathered at the representation
	 * set representation level.
	 */
	class SealedSurfaceFrameworkRepresentation : public AbstractSurfaceFrameworkRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~SealedSurfaceFrameworkRepresentation() {}

		/**
		 * Pushes back a contact in this structural framework with implicit identical nodes. After
		 * calling the following method, the contact patches container of the newly pushed contact
		 * remains empty. After this call, do not forget to call the pushBackContactPatch() method for
		 * each contact patch of the contact.
		 *
		 * @param 	kind	The identity kind (colocation, previous colocation, equivalence or previous
		 * 					equivalence) of the contact to push.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind kind) = 0;

		/**
		 * Pushes back a contact in this structural framework.After calling the following method, the
		 * contact patches container of the newly pushed contact remains empty. After this call, do not
		 * forget to call the pushBackContactPatch() method for each contact patch of the contact.
		 *
		 * @exception	std::invalid_argument	If @p patchCount is strictly lesser than @c 2.
		 * @exception	std::invalid_argument	If @p identicalNodesCount is @c 0.
		 * @exception	std::invalid_argument	If @p identicalNodes is @c nullptr.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 		  	kind			   	The identity kind (colocation, previous colocation,
		 * 										equivalence or previous equivalence) of the contact to
		 * 										push.
		 * @param 		  	patchCount		   	The number of contact patches within this sealed contact.
		 * @param 		  	identicalNodesCount	The number of identical nodes along this sealed contact.
		 * @param [in]	  	identicalNodes	   	A 1d array of identical nodes indices. The size of this
		 * 										array is @p patchCount <tt>*</tt> @p identicalNodesCount.
		 * 										It indicates which nodes (identified by their common
		 * 										index in all contact patches) of the contact patches are
		 * 										identical.
		 * @param [in,out]	proxy			   	The HDF proxy where to write the @p identicalNodes
		 * 										values. If @c nullptr, then a default HDF proxy must be
		 * 										defined in the repository.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackContact(
			gsoap_resqml2_0_1::resqml20__IdentityKind kind,
			unsigned int patchCount,
			unsigned int identicalNodesCount,
			int const* identicalNodes,
			EML2_NS::AbstractHdfProxy * proxy) = 0;

		/**
		 * Pushes back a contact patch in a particular contact of this structural framework.
		 *
		 * @exception	std::invalid_argument	If @p nodeIndicesOnSupportingRepresentation is @c nullptr.
		 * @exception	std::invalid_argument	If @p nodeCount is @c 0.
		 * @exception	std::invalid_argument	If @p supportingRepresentation is @c nullptr or if it is
		 * 										not referenced by this sealed surface framework.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 * @exception	std::out_of_range	 	If @p contactIdx is out of range.
		 *
		 * @param 		  	contactIdx							 	Zero-base index of the contact which will
		 * 															contain this contact patch.
		 * @param 		  	nodeIndicesOnSupportingRepresentation	The nodes defining the contact patch
		 * 															on the supporting representation.
		 * 															Size if @p nodeCount.
		 * @param 		  	nodeCount							 	The node count of this contact patch.
		 * @param [in]	  	supportingRepresentation			 	The supporting representation of this
		 * 															contact patch.
		 * @param [in,out]	proxy								 	The HDF proxy where to write the @p
		 * 															nodeIndicesOnSupportingRepresentation
		 * 															values. If @c nullptr, then a default
		 * 															HDF proxy must be defined in the
		 * 															repository.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackContactPatch(
			unsigned int contactIdx,
			int const* nodeIndicesOnSupportingRepresentation, unsigned int nodeCount,
			AbstractRepresentation * supportingRepresentation,
			EML2_NS::AbstractHdfProxy * proxy) = 0;

		DLL_IMPORT_OR_EXPORT virtual unsigned int getContactCount() const override = 0;

		/**
		 * Gets the identity kind of a particular contact.
		 *
		 * @exception	std::out_of_range	If @p contactIdx is out of range.
		 *
		 * @param 	contactIdx	Zero-based index of the contact for which we look for the identity kind.
		 *
		 * @returns	The identity kind of the contact located at a @p contactIdx.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::resqml20__IdentityKind getContactPatchIdentityKind(unsigned int contactIdx) const = 0;

		/**
		 * Checks if all nodes of contact patches are identical in a particular contact.
		 *
		 * @exception	std::out_of_range	If @p contactIdx is out of range.
		 *
		 * @param 	contactIdx	Zero-based index of the contact for which we want to check if all nodes
		 * 						of contact patches are identical.
		 *
		 * @returns	True if all nodes of contact patches are identical else false.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool areAllContactPatchNodesIdentical(unsigned int contactIdx) const = 0;

		/**
		 * Gets the count of identical nodes of a particular contact.
		 *
		 * @exception	std::invalid_argument	If all nodes of contact patches are identical (see
		 * 										areAllContactPatchNodesIdentical()).
		 * @exception	std::out_of_range	 	If @p contactIdx is out of range.
		 * @exception	std::range_error	 	If the count of identical nodes is strictly greater than
		 * 										unsigned int max.
		 *
		 * @param 	contactIdx	Zero-based index of the contact for which we look for the count of
		 * 						identical nodes.
		 *
		 * @returns	The count of identical nodes in the contact at position @p contactIdx.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getIdenticalContactPatchNodeCount(unsigned int contactIdx) const = 0;

		/**
		 * Gets the node indices of all contact patches which are identical in a particular contact.
		 *
		 * @exception	std::invalid_argument	If all nodes of contact patches are identical (see
		 * 										areAllContactPatchNodesIdentical()).
		 * @exception	std::out_of_range	 	If @p contactIdx is out of range.*.
		 *
		 * @param 	   	contactIdx 	Zero-based index of the contact for which we look for the identical
		 * 							nodes indices.
		 * @param [out]	nodeIndices	An array to receive the identical nodes indices. This array must be
		 * 							preallocated with getIdenticalContactPatchNodeCount().
		 */
		DLL_IMPORT_OR_EXPORT virtual void getIdenticalContactPatchNodeIndices(unsigned int contactIdx, unsigned int * nodeIndices) const = 0;

		/**
		 * Gets the count of contact patches in a particular contact of this framework.
		 *
		 * @exception	std::out_of_range	If @p contactIdx is out of range.
		 * @exception	std::range_error 	If the count of identical nodes is strictly greater than
		 * 									unsigned int max.
		 *
		 * @param 	contactIdx	Zero-based index of the contact for which we look for the contact patches
		 * 						count.
		 *
		 * @returns	The count of contact patches in the contact at position @p contactIdx.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getContactPatchCount(unsigned int contactIdx) const = 0;

		/**
		 * Gets the representation (for instance the triangulated surface) where a particular contact
		 * patch has been defined.
		 *
		 * @exception	std::out_of_range	If @p contactIdx or @p cpIndex is out of range.
		 * @exception	std::range_error 	If the index of the representation provided in the contact
		 * 									patch is strictly greater than unsigned int max.
		 *
		 * @param 	contactIdx	Zero-based index of the contact in the contact list.
		 * @param 	cpIndex   	Zero-based index of the contact patch in the contact.
		 *
		 * @returns	The representation where the contact patch has been defined.
		 */
		DLL_IMPORT_OR_EXPORT virtual RESQML2_NS::AbstractRepresentation* getRepresentationOfContactPatch(unsigned int contactIdx, unsigned int cpIndex) const = 0;

		/**
		 * Gets the representation index where a particular contact patch has been defined. The index is
		 * in the range <tt>[0..</tt>getRepresentationCount()<tt>[</tt>.
		 *
		 * @exception	std::out_of_range	If @p contactIdx or @p cpIndex is out of range.
		 * @exception	std::range_error 	If the representation index is strictly greater than unsigned
		 * 									int max.
		 *
		 * @param 	contactIdx	Zero-based index of the contact in the contact list.
		 * @param 	cpIndex   	Zero-based index of the contact patch in the contact.
		 *
		 * @returns	The representation index where the contact patch has been defined.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getRepresentationIndexOfContactPatch(unsigned int contactIdx, unsigned int cpIndex) const = 0;

		/**
		 * Get the count of nodes of a particular contact patch.
		 *
		 * @exception	std::out_of_range	If @p contactIdx or @p cpIndex is out of range.
		 * @exception	std::range_error 	If the count of nodes is strictly greater than unsigned int
		 * 									max.
		 *
		 * @param 	contactIdx	Zero-based index of the contact in the contact list.
		 * @param 	cpIndex   	Zero-based index of the contact patch in the contact.
		 *
		 * @returns	The count of nodes of a particular contact patch.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getContactPatchNodeCount(unsigned int contactIdx, unsigned int cpIndex) const = 0;

		/**
		 * Gets the nodes indices of a particular contact patch. The returned indices are associated to
		 * the node array of the representation of the particular contact patch (see
		 * getRepresentationOfContactPatch()).
		 *
		 * @exception	std::out_of_range	If @p contactIdx or @p cpIndex is out of range.
		 *
		 * @param 	   	contactIdx 	Zero-based index of the contact in the contact list.
		 * @param 	   	cpIndex	   	Zero-based index of the contact patch in the contact.
		 * @param [out]	nodeIndices	An array to received the nodes indices. This array must be
		 * 							preallocated with getContactPatchNodeCount(). It won't be deleted by
		 * 							fesapi.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getContactPatchNodeIndices(unsigned int contactIdx, unsigned int cpIndex, unsigned int * nodeIndices) const = 0;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT SealedSurfaceFrameworkRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractSurfaceFrameworkRepresentation(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	interp	The structural organization interpretation the instance interprets.
		 * @param 		  	guid  	The guid to set to the representation. If empty then a new guid will
		 * 							be generated.
		 * @param 		  	title 	A title for the instance to create.
		 */
		SealedSurfaceFrameworkRepresentation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		SealedSurfaceFrameworkRepresentation(gsoap_resqml2_0_1::_resqml20__SealedSurfaceFrameworkRepresentation* fromGsoap) : AbstractSurfaceFrameworkRepresentation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		SealedSurfaceFrameworkRepresentation(gsoap_eml2_3::_resqml22__SealedSurfaceFrameworkRepresentation* fromGsoap) : AbstractSurfaceFrameworkRepresentation(fromGsoap) {}
	};

}
