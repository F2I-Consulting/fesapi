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

#include "../resqml2/NonSealedSurfaceFrameworkRepresentation.h"

/** . */
namespace RESQML2_2_NS
{
	/** A non sealed surface framework representation. */
	class NonSealedSurfaceFrameworkRepresentation : public RESQML2_NS::NonSealedSurfaceFrameworkRepresentation
	{
    public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT NonSealedSurfaceFrameworkRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::NonSealedSurfaceFrameworkRepresentation(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	interp	The structural organization interpretation the instance interprets.
		 * @param 		  	guid  	The guid to set to the horizon. If empty then a new guid will be
		 * 							generated.
		 * @param 		  	title 	A title for the instance to create.
		 */
		NonSealedSurfaceFrameworkRepresentation(RESQML2_NS::StructuralOrganizationInterpretation* interp, const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		NonSealedSurfaceFrameworkRepresentation(gsoap_eml2_3::_resqml22__NonSealedSurfaceFrameworkRepresentation* fromGsoap): RESQML2_NS::NonSealedSurfaceFrameworkRepresentation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~NonSealedSurfaceFrameworkRepresentation() {}

		/**
		 * Pushes back a contact representation in the structural framework
		 *
		 * @param 		  	pointCount	Number of points.
		 * @param [in,out]	points	  	If non-null, the points.
		 * @param [in,out]	proxy	  	(Optional) If non-null, the proxy.
		 * @param [in,out]	localCrs  	(Optional) If non-null, the local crs.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackNonSealedContactRepresentation(unsigned int pointCount, double const* points, EML2_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) final;
                
        /**
		* Pushes back a contact patch in a particular contact representation of the structural framework.
		* @param contactIndex							The index of the contact which will contain this contact patch.
		* @param nodeIndicesOnSupportingRepresentation	The nodes defining the contact patch on the supporting representation.
		* @param NodeCount								The node count of this contact patch.
		* @param supportingRepresentation 				The supporting representation of this contact patch.
		* @param proxy 									The hdf proxy for storing the nodes.
		*/
		/*
        void pushBackContactPatchInContactRepresentation(
        		const unsigned int & contactIndex,
                int * nodeIndicesOnSupportingRepresentation, const unsigned int & NodeCount,
                class AbstractRepresentation * supportingRepresentation,
                EML2_NS::AbstractHdfProxy* proxy);
                */

		/**
		 * Gets contact count
		 *
		 * @returns	The contact count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getContactCount() const final;
	};
}
