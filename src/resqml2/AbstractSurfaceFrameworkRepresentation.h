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

#include "RepresentationSetRepresentation.h"

namespace EML2_NS
{
	class AbstractHdfProxy;
}

namespace RESQML2_NS
{
	/**
	 * @brief	Parent class for a sealed or non-sealed surface framework representation. Each one
	 * 			instantiates a representation set representation. The difference between the sealed
	 * 			and non- sealed frameworks is that, in the non-sealed case, we do not have all of the
	 * 			contacts, or we have all of the contacts but they are not all sealed.
	 */
	class AbstractSurfaceFrameworkRepresentation : public RepresentationSetRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~AbstractSurfaceFrameworkRepresentation() = default;

		/**
		 * Pushes back a contact identity in this structural framework with implicit identical nodes.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 * @exception	std::logic_error	 	If the RESQML version is unknown.
		 *
		 * @param 		  	kind		  	The identity kind (colocation, previous colocation,
		 * 									equivalence or previous equivalence).
		 * @param 		  	contactCount  	The number of sealed contact representations involved within
		 * 									the identity.
		 * @param 		  	contactIndices	The indices of the sealed contact representations involved
		 * 									within the identity. Count is @p contactCount.
		 * @param [in,out]	proxy		  	The HDF proxy where to write the @p contactIndices values. If
		 * 									@c nullptr, then a default HDF proxy must be defined in the
		 * 									repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackContactIdentity(
			gsoap_resqml2_0_1::resqml20__IdentityKind kind,
			unsigned int contactCount, int const* contactIndices,
			EML2_NS::AbstractHdfProxy * proxy);

		/**
		 * Push back a contact identity in this structural framework.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 * @exception	std::logic_error	 	If the RESQML version is unknown.
		 *
		 * @param 		  	kind				 	The identity kind (colocation, previous colocation,
		 * 											equivalence or previous equivalence).
		 * @param 		  	contactCount		 	The number of sealed contact representations involved
		 * 											within the identity.
		 * @param 		  	contactIndices		 	The indices of the sealed contact representations
		 * 											involved within the identity. Count is @p
		 * 											contactCount.
		 * @param 		  	identicalNodesCount  	The number of identical nodes.
		 * @param 		  	identicalNodesIndexes	Indicates which nodes (identified by their common
		 * 											index in all contact representations) of the contact
		 * 											representations are identical. Count is @p
		 * 											identicalNodesCount.
		 * @param [in,out]	proxy				 	The HDF proxy where to write the @p contactIndices
		 * 											and @p identicalNodesIndexes values. Id f @c nullptr,
		 * 											then a default HDF proxy must be defined in the
		 * 											repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackContactIdentity(
			gsoap_resqml2_0_1::resqml20__IdentityKind kind,
			unsigned int contactCount, int const* contactIndices,
			unsigned int identicalNodesCount, int const* identicalNodesIndexes,
			EML2_NS::AbstractHdfProxy * proxy);

		/**
		 * Gets the count of contacts in this framework.
		 *
		 * @exception	std::range_error	If the count of contacts is strictly greater than unsigned
		 * 									int max.
		 *
		 * @returns	The count of contacts in this framework.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getContactCount() const = 0;

		/**
		 * Gets the count of contact identities in this framework.
		 *
		 * @exception	std::range_error	If the count of contacts identities is strictly greater than
		 * 									unsigned int max.
		 *
		 * @returns	The count of contact identities in this framework.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getContactIdentityCount() const;

		/**
		 * Gets the kind of a contact identity located at a particular index.
		 *
		 * @exception	std::out_of_range	If @p ciIndex is out of range.
		 * @exception	std::logic_error 	If the RESQML version is unknown.
		 *
		 * @param 	ciIndex	Zero-based index of the contact identity in the contact identity list.
		 *
		 * @returns	The kind of the contact identity at position @p ciIndex in the contact identity list.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__IdentityKind getContactIdentityKind(unsigned int ciIndex) const;

		/**
		 * Gets the count of contacts of a particular contact identity.
		 *
		 * @exception	std::out_of_range	If @p ciIndex is out of range.
		 * @exception	std::range_error 	If the count of contacts is strictly greater than unsigned
		 * 									int max.
		 * @exception	std::logic_error 	If the RESQML version is unknown.
		 *
		 * @param 	ciIndex	Zero-based index of the contact identity in the contact identity list.
		 *
		 * @returns	The count of contacts of the contact identity at position @p ciIndex.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getContactCountInContactIdentity(unsigned int ciIndex) const;

		/**
		 * Gets the contact indices of a particular contact identity. The returned indices are in the
		 * interval <tt>[0..</tt>getContactCount()<tt>[</tt>.
		 *
		 * @exception	std::out_of_range	If @p ciIndex is out of range.
		 * @exception	std::logic_error 	If the RESQML version is unknown.
		 *
		 * @param 	   	ciIndex			 	Zero-based index of the contact identity in the contact
		 * 									identity list.
		 * @param [out]	contactRepIndices	An array to receive contact indices. It must be preallocated
		 * 									with getContactCountInContactIdentity(). It won't be deleted
		 * 									by fesapi.
		 */
		DLL_IMPORT_OR_EXPORT void getContactIndices(unsigned int ciIndex, unsigned int * contactRepIndices) const;

		/**
		 * Checks if all nodes of contacts are identical in a particular contact identity.
		 *
		 * @exception	std::out_of_range	If @p ciIndex is out of range.
		 * @exception	std::logic_error 	If the RESQML version is unknown.
		 *
		 * @param 	ciIndex	Zero-based index of the contact identity in the contact identity list.
		 *
		 * @returns	True if all nodes of contacts are identical else false.
		 */
		DLL_IMPORT_OR_EXPORT bool areAllContactNodesIdentical(unsigned int ciIndex) const;

		/**
		 * Gets the count of all identical nodes of a particular contact identity.
		 *
		 * @exception	std::invalid_argument	If all nodes are identical (see
		 * 										areAllContactNodesIdentical()).
		 * @exception	std::out_of_range	 	If @p ciIndex is out of range.
		 * @exception	std::logic_error	 	If the RESQML version is unknown.
		 * @exception	std::range_error	 	If the count of identical nodes is strictly greater than
		 * 										<tt>unsigned int</tt> max.
		 *
		 * @param 	ciIndex	Zero-based index of the contact identity in the contact identity list.
		 *
		 * @returns	The count of identical nodes of a particular contact identity.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getIdenticalContactNodeCount(unsigned int ciIndex) const;

		/**
		 * Gets the indices of all identical nodes of a particular contact identity.
		 *
		 * @exception	std::invalid_argument	If if all nodes are identical (see
		 * 										areAllContactRepNodesIdenticalInContactIdentity()).
		 * @exception	std::out_of_range	 	If @p ciIndex is out of range.
		 * @exception	std::logic_error	 	If the RESQML version is unknown.
		 *
		 * @param 	   	ciIndex	   	ciIndex	Zero-based index of the contact identity in the contact
		 * 							identity list.
		 * @param [out]	nodeIndices	An array to receive the identical nodes indices. It must be
		 * 							preallocated with a count of getIdenticalContactNodeCount(). It won't
		 * 							be deleted by fesapi.
		 */
		DLL_IMPORT_OR_EXPORT void getIdenticalContactNodeIndices(unsigned int ciIndex, unsigned int * nodeIndices) const;

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT AbstractSurfaceFrameworkRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RepresentationSetRepresentation(partialObject) {}

		/** Default constructor */
		AbstractSurfaceFrameworkRepresentation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractSurfaceFrameworkRepresentation(gsoap_resqml2_0_1::resqml20__AbstractSurfaceFrameworkRepresentation* fromGsoap) : RepresentationSetRepresentation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractSurfaceFrameworkRepresentation(gsoap_eml2_3::resqml22__AbstractSurfaceFrameworkRepresentation* fromGsoap) : RepresentationSetRepresentation(fromGsoap) {}

		/**
		 * Get a v2.0.1 contact identity from its index in this framework.
		 *
		 * @param 	ciIndex	The index of the contact identity in the contact identity list. It must be in
		 * 					the interval [0..getContactIdentityCount()[.
		 *
		 * @returns	A contact identity from its index in this framework.
		 */
		gsoap_resqml2_0_1::resqml20__ContactIdentity* getContactIdentity201(unsigned int ciIndex) const;

		/**
		 * Get a v2.2 contact identity from its index in this framework.
		 *
		 * @param 	ciIndex	The index of the contact identity in the contact identity list. It must be in
		 * 					the interval [0..getContactIdentityCount()[.
		 *
		 * @returns	A contact identity from its index in this framework.
		 */
		gsoap_eml2_3::resqml22__ContactIdentity* getContactIdentity22(unsigned int ciIndex) const;
	};
}
