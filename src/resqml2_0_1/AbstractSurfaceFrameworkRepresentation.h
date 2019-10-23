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

#include "resqml2/RepresentationSetRepresentation.h"

namespace RESQML2_0_1_NS
{
	/*
	* Parent class for a sealed or non-sealed surface framework representation. Each one instantiates a representation set representation.
	* The difference between the sealed and non-sealed frameworks is that, in the non-sealed case, we do not have all of the contacts, or we have all of the contacts but they are not all sealed.
	*/
	class AbstractSurfaceFrameworkRepresentation : public RESQML2_NS::RepresentationSetRepresentation
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT AbstractSurfaceFrameworkRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::RepresentationSetRepresentation(partialObject) {}

		/**
		* Default constructor
		*/
		AbstractSurfaceFrameworkRepresentation();

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractSurfaceFrameworkRepresentation(gsoap_resqml2_0_1::resqml20__AbstractSurfaceFrameworkRepresentation* fromGsoap) : RESQML2_NS::RepresentationSetRepresentation(fromGsoap) {}

		/**
		* Get a contact identity from its index in this framework.
		*
		* @param ciIndex	The index of the contact identity in the contact identity list. It must be in the interval [0..getContactIdentityCount()[.
		* @return			A contact identity from its index in this framework.
		*/
		gsoap_resqml2_0_1::resqml20__ContactIdentity* getContactIdentity(unsigned int ciIndex) const;

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractSurfaceFrameworkRepresentation() {}

		/**
		* Push back a contact identity in the structural framework with implicit identical nodes
		* @param kind			Identity kind.
		* @param contactCount	The number of sealed contacts involved within the identity.
		* @param contactIndices	The sealed contacts involved within the identity.
		* @param proxy			The hdf proxy.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackContactIdentity(
			gsoap_resqml2_0_1::resqml20__IdentityKind kind,
			unsigned int contactCount, int * contactIndices,
			COMMON_NS::AbstractHdfProxy * proxy);

		/**
		* Push back a contact identity in the structural framework
		* @param kind					Identity kind.
		* @param contactCount			The number of sealed contacts involved within the identity.
		* @param contactIndices			The sealed contacts involved within the identity.
		* @param identicalNodesCount	The number of identical nodes.
		* @param identicalNodesIndexes	The indices of the identical nodes.
		* @param proxy					The hdf proxy.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackContactIdentity(
			gsoap_resqml2_0_1::resqml20__IdentityKind kind,
			unsigned int contactCount, int * contactIndices,
			unsigned int identicalNodesCount, int * identicalNodesIndexes,
			COMMON_NS::AbstractHdfProxy * proxy);

		/**
		* Get the count of contacts in this framework.
		*
		* @return The count of contacts in this framework.
		*/
		DLL_IMPORT_OR_EXPORT virtual unsigned int getContactCount() const = 0;

		/**
		* Get the count of contact identity in this framework.
		* @return The count of contact identity in this framework.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getContactIdentityCount() const;

		/**
		* Get the kind of a contact identity located at a particular index.
		*
		* @param ciIndex	The index of the contact identity in the contact identity list. It must be in the interval [0..getContactIdentityCount()[.
		* @return The kind of the contact identity located at a particular index.
		*/
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__IdentityKind getContactIdentityKind(unsigned int ciIndex) const;

		/**
		* Get the count of contact of a particular contact identity.
		*
		* @param ciIndex	The index of the contact identity in the contact identity list. It must be in the interval [0..getContactIdentityCount()[.
		* @return			The count of contact of a particular contact identity.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getContactCountInContactIdentity(unsigned int ciIndex) const;

		/**
		* Get the contact indices of a particular contact identity.
		* The returned indices are in the interval [0..getContactCount()[
		* 
		* @param ciIndex			The index of the contact identity in the contact identity list. It must be in the interval [0..getContactIdentityCount()[.
		* @param contactRepIndices	This array must be preallocated with getContactCountOfContactIdentity(). It won't be deleted by fesapi.
		*							It will be filled in with the desired contact rep indices.
		*/
		DLL_IMPORT_OR_EXPORT void getContactIndices(unsigned int ciIndex, unsigned int * contactRepIndices) const;

		/*
		* Check if all nodes of contacts are identical in a contact identity.
		*
		* @param ciIndex	The index of the contact identity in the contact identity list. It must be in the interval [0..getContactIdentityCount()[.
		* @return			True if all node of contacts are identical else false.
		*/
		DLL_IMPORT_OR_EXPORT bool areAllContactNodesIdentical(unsigned int ciIndex) const;

		/**
		* Get the count of identical nodes of a particular contact identity.
		* Throw an exception if all nodes are identical (see areAllContactRepNodesIdenticalInContactIdentity()).
		*
		* @param ciIndex	The index of the contact identity in the contact identity list. It must be in the interval [0..getContactIdentityCount()[.
		* @return			The count of identical nodes of a particular contact identity.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getIdenticalContactNodeCount(unsigned int ciIndex) const;

		/**
		* Get the node indices of all contacts which are identical.
		* Throw an exception if all nodes are identical (see areAllContactRepNodesIdenticalInContactIdentity()).
		*
		* @param ciIndex		The index of the contact identity in the contact identity list. It must be in the interval [0..getContactIdentityCount()[.
		* @param nodeIndices	This array must be preallocated with getIdenticalContactlNodeCount(). It won't be deleted by fesapi.
		*						It will be filled in with the desired node indices.
		*/
		DLL_IMPORT_OR_EXPORT void getIdenticalContactNodeIndices(unsigned int ciIndex, unsigned int * nodeIndices) const;
	};
}
