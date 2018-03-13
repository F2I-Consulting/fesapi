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

#include "resqml2_0_1/RepresentationSetRepresentation.h"

namespace RESQML2_NS {
	class AbstractHdfProxy;
}

namespace RESQML2_0_1_NS
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
			COMMON_NS::AbstractHdfProxy * proxy);

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
			COMMON_NS::AbstractHdfProxy * proxy);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		virtual std::string getHdfProxyUuid() const;
	};

} // namespace RESQML2_0_1_NS

