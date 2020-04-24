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

namespace RESQML2_NS
{
	/**
	 * A non sealed surface framework representation is collection of contact representations parts,
	 * which are a list of contact patches with no identity. This collection of contact
	 * representations is completed by a set of representations gathered at the representation set
	 * representation level.
	 */
	class NonSealedSurfaceFrameworkRepresentation : public AbstractSurfaceFrameworkRepresentation
	{
    public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~NonSealedSurfaceFrameworkRepresentation() {}

		/**
		 * Pushes back a contact representation in this structural framework
		 *
		 * @exception	std::invalid_argument	If @p pointCount is @c 0.
		 * @exception	std::invalid_argument	If @p points is @c nullptr.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If @p localCrs is @c nullptr and no default local 3d CRS
		 * 										is defined in the repository.
		 *
		 * @param 		  	pointCount	The number of points in the contact representation.
		 * @param [in]	  	points	  	The <tt>(x, y, z)</tt> points of the contact representation.
		 * 								Count is <tt>pointCount * 3</tt> and for each contact point
		 * 								<tt>(x, y, z) = (points[2i], points[2i+1], points[2i+2])</tt>.
		 * @param [in,out]	proxy	  	(Optional) The HDF proxy where the numerical values (contact
		 * 								points coordinates) are stored. If @c nullptr (default), then the
		 * 								default HDF proxy of the repository will be used.
		 * @param [in,out]	localCrs  	(Optional) The local 3d CRS on which the geometry of the contact
		 * 								representation is based on. If @c nullptr (default), then the
		 * 								default local 3d CRS of the repository will be used.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackNonSealedContactRepresentation(unsigned int pointCount, double const* points, EML2_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) = 0;
                
        /*
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

		DLL_IMPORT_OR_EXPORT virtual unsigned int getContactCount() const override = 0;

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
		DLL_IMPORT_OR_EXPORT NonSealedSurfaceFrameworkRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractSurfaceFrameworkRepresentation(partialObject) {}

		/**
		 * Default constructor
		 */
		NonSealedSurfaceFrameworkRepresentation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		NonSealedSurfaceFrameworkRepresentation(gsoap_resqml2_0_1::_resqml20__NonSealedSurfaceFrameworkRepresentation* fromGsoap) : AbstractSurfaceFrameworkRepresentation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		NonSealedSurfaceFrameworkRepresentation(gsoap_eml2_3::_resqml22__NonSealedSurfaceFrameworkRepresentation* fromGsoap) : AbstractSurfaceFrameworkRepresentation(fromGsoap) {}
	};
}
