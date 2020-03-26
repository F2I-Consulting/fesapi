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

#include "AbstractSurfaceRepresentation.h"

/** . */
namespace RESQML2_NS
{
	/** A plane set representation. */
	class PlaneSetRepresentation : public AbstractSurfaceRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~PlaneSetRepresentation() {}
		
		COMMON_NS::DataObjectReference getHdfProxyDor() const { return COMMON_NS::DataObjectReference(); }

		/**
		 * Push back a new patch which is an horizontal plane
		 *
		 * @param 		  	zCoordinate	The Z coordinate of the horizontal plane.
		 * @param [in,out]	localCrs   	(Optional) If non-null, the local crs.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackHorizontalPlaneGeometryPatch(double zCoordinate, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) = 0;

		/**
		 * Push back a new patch which is not a horizontal plane. It s geometry is given by means of 3
		 * XYZ points.
		 *
		 * @param 		  	x1			The first x value.
		 * @param 		  	y1			The first y value.
		 * @param 		  	z1			The first z value.
		 * @param 		  	x2			The second x value.
		 * @param 		  	y2			The second y value.
		 * @param 		  	z2			The second z value.
		 * @param 		  	x3			The third double.
		 * @param 		  	y3			The third double.
		 * @param 		  	z3			The third double.
		 * @param [in,out]	localCrs	(Optional) If non-null, the local crs.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackTiltedPlaneGeometryPatch(
			double x1, double y1, double z1,
			double x2, double y2, double z2,
			double x3, double y3, double z3,
			RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) = 0;

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
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }
		
	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT PlaneSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractSurfaceRepresentation(partialObject) {}

		/**
		 * Default constructor
		 */
		PlaneSetRepresentation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PlaneSetRepresentation(gsoap_resqml2_0_1::_resqml20__PlaneSetRepresentation* fromGsoap) : AbstractSurfaceRepresentation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PlaneSetRepresentation(gsoap_eml2_3::_resqml22__PlaneSetRepresentation* fromGsoap) : AbstractSurfaceRepresentation(fromGsoap) {}
	};
}
