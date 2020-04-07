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

namespace RESQML2_0_1_NS
{
	class NonSealedSurfaceFrameworkRepresentation : public AbstractSurfaceFrameworkRepresentation
	{
    public:
		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT NonSealedSurfaceFrameworkRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractSurfaceFrameworkRepresentation(partialObject) {}

        /**
		* Creates an instance of this class in a gsoap context.
		* @param interp     The structural organization interpretation the instance interprets.
		* @param guid		The guid to set to the horizon. If empty then a new guid will be generated.
		* @param title      A title for the instance to create.
		*/
		NonSealedSurfaceFrameworkRepresentation(class StructuralOrganizationInterpretation* interp, const std::string & guid, const std::string & title);
                
        /**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		NonSealedSurfaceFrameworkRepresentation(gsoap_resqml2_0_1::_resqml20__NonSealedSurfaceFrameworkRepresentation* fromGsoap): AbstractSurfaceFrameworkRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~NonSealedSurfaceFrameworkRepresentation() {}

		/**
		 * Pushes back a contact representation in the structural framework
		 */
		DLL_IMPORT_OR_EXPORT void pushBackNonSealedContactRepresentation(unsigned int pointCount, double * points, COMMON_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr);
                
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
                COMMON_NS::AbstractHdfProxy* proxy);
                */

		DLL_IMPORT_OR_EXPORT unsigned int getContactCount() const;

		DLL_IMPORT_OR_EXPORT virtual std::string getHdfProxyUuid() const;

		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		* Get the standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }
	};
}
