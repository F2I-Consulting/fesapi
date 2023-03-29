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

#include "AbstractRepresentation.h"

namespace RESQML2_NS
{
	/**
	 * @brief	A representation that consists of one or more node patches. Each node patch is an
	 * 			array of xyz coordinates for the 3D points. There is no implied linkage between the
	 * 			multiple patches.
	 */
	class PointSetRepresentation : public AbstractRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~PointSetRepresentation() = default;

		/**
		 * Pushes back a new patch of points.
		 *
		 * @exception	std::invalid_argument	If <tt>proxy == nullptr</tt> and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If <tt>localCrs == nullptr</tt> and no default local CRS
		 * 										id defined in the repository.
		 *
		 * @param 		  	xyzPointCount	The xyz points count in this patch.
		 * @param [in]	  	xyzPoints	 	The xyz values of the points of the patch. Ordered by xyz and
		 * 									then by @p xyzPointCount. Size is <tt>3 * xyzPointCount</tt>.
		 * @param [in,out]	proxy		 	(Optional) The HDF proxy which defines where the xyz points
		 * 									will be stored. If @c nullptr (default), then the repository
		 * 									default HDF proxy will be used.
		 * @param [in]	  	localCrs	 	(Optional) The local CRS where the points are given. If @c
		 * 									nullptr (default), then the repository default local CRS will
		 * 									be used.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackGeometryPatch(
			unsigned int xyzPointCount, double const * xyzPoints,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) = 0;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "PointSetRepresentation";

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT PointSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractRepresentation(partialObject) {}

		PointSetRepresentation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PointSetRepresentation(gsoap_resqml2_0_1::_resqml20__PointSetRepresentation* fromGsoap) : RESQML2_NS::AbstractRepresentation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PointSetRepresentation(gsoap_eml2_3::_resqml22__PointSetRepresentation* fromGsoap) : RESQML2_NS::AbstractRepresentation(fromGsoap) {}
	};
}
