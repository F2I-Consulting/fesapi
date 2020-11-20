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

namespace RESQML2_0_1_NS
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
		 * 
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
		SealedSurfaceFrameworkRepresentation(gsoap_resqml2_0_1::_resqml20__SealedSurfaceFrameworkRepresentation* fromGsoap) : RESQML2_NS::SealedSurfaceFrameworkRepresentation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~SealedSurfaceFrameworkRepresentation() = default;

		DLL_IMPORT_OR_EXPORT void pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind kind) final;

		DLL_IMPORT_OR_EXPORT void pushBackContact(
			gsoap_resqml2_0_1::resqml20__IdentityKind kind,
			unsigned int patchCount,
			unsigned int identicalNodesCount,
			int const* identicalNodes,
			EML2_NS::AbstractHdfProxy * proxy) final;

		DLL_IMPORT_OR_EXPORT void pushBackContactPatch(
			unsigned int contactIdx,
			int const* nodeIndicesOnSupportingRepresentation, unsigned int nodeCount,
			RESQML2_NS::AbstractRepresentation * supportingRepresentation,
			EML2_NS::AbstractHdfProxy * proxy) final;

		DLL_IMPORT_OR_EXPORT unsigned int getContactCount() const final;

		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__IdentityKind getContactPatchIdentityKind(unsigned int contactIdx) const final;

		DLL_IMPORT_OR_EXPORT bool areAllContactPatchNodesIdentical(unsigned int contactIdx) const final;

		DLL_IMPORT_OR_EXPORT unsigned int getIdenticalContactPatchNodeCount(unsigned int contactIdx) const final;

		DLL_IMPORT_OR_EXPORT void getIdenticalContactPatchNodeIndices(unsigned int contactIdx, unsigned int * nodeIndices) const final;

		DLL_IMPORT_OR_EXPORT unsigned int getContactPatchCount(unsigned int contactIdx) const final;

		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractRepresentation* getRepresentationOfContactPatch(unsigned int contactIdx, unsigned int cpIndex) const final;

		DLL_IMPORT_OR_EXPORT unsigned int getRepresentationIndexOfContactPatch(unsigned int contactIdx, unsigned int cpIndex) const final;

		DLL_IMPORT_OR_EXPORT unsigned int getContactPatchNodeCount(unsigned int contactIdx, unsigned int cpIndex) const final;

		/**
		* Get the node indices of a particular contact patch.
		* The returned indices are associated to the node array of the representation of the particular contact patch (see getRepresentationOfContactPatch()).
		*
		* @param contactIdx		The index of the contact in the contact list. It must be in the interval [0..getContactCount()[.
		* @param cpIndex		The index of the contact patch in the contact. It must be in the interval [0..getContactPatchCount()[.
		* @param nodeIndices	This array must be preallocated with getNodeCountOfContactPatch(). It won't be deleted by fesapi.
		*						It will be filled in with the desired node indices.
		*/
		DLL_IMPORT_OR_EXPORT void getContactPatchNodeIndices(unsigned int contactIdx, unsigned int cpIndex, unsigned int * nodeIndices) const final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

	private:

		/**
		 * Get a contact from its index in this framework.
		 *
		 * @param 	contactIdx	The index of the contact in the contact list. It must be in the interval
		 * 						[0..getContactCount()[.
		 *
		 * @returns	A contact from its index in this framework.
		 */
		gsoap_resqml2_0_1::resqml20__SealedContactRepresentationPart* getContact(unsigned int contactIdx) const;

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
		gsoap_resqml2_0_1::resqml20__ContactPatch* getContactPatch(unsigned int contactIdx, unsigned int cpIndex) const;
	};
}
