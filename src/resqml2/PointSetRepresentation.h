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

/** . */
namespace RESQML2_NS
{
	/** A point set representation. */
	class PointSetRepresentation : public AbstractRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~PointSetRepresentation() {}

		/**
		 * Push back a new patch of polylines
		 *
		 * @param 		  	xyzPointCount	The XYZ point count in this patch.
		 * @param [in,out]	xyzPoints	 	The XYZ values of the points of the patch. Ordered by XYZ and
		 * 									then by xyzPointCount. It must be three times xyzPointCount.
		 * @param [in,out]	proxy		 	(Optional) The HDF proxy which defines where the XYZ points
		 * 									will be stored.
		 * @param [in,out]	localCrs	 	(Optional) The local CRS wher the points are given.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackGeometryPatch(
			unsigned int xyzPointCount, double const * xyzPoints,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) = 0;

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
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