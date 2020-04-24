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

namespace RESQML2_NS
{
	/**
	 * Defines a plane representation, which can be made up of multiple patches. Commonly
	 * represented features are fluid contacts or frontiers. Common geometries of this
	 * representation are titled or horizontal planes.
	 * 
	 * BUSINESS RULE: If the plane representation is made up of multiple patches, then you must
	 * specify the outer rings for each plane patch.
	 */
	class PlaneSetRepresentation : public AbstractSurfaceRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~PlaneSetRepresentation() {}

		/**
		 * @copybrief AbstractRepresentation::getHdfProxyDor
		 *
		 * @returns	Empty DOR since plane set representation values do not rely a HDF proxy (it is XML
		 * 			only).
		 */
		COMMON_NS::DataObjectReference getHdfProxyDor() const { return COMMON_NS::DataObjectReference(); }

		/**
		 * Pushes back a new patch which is an horizontal plane.
		 *
		 * @exception	std::invalid_argument	If <tt>localCrs == nullptr</tt> and no default CRS is
		 * 										defined in the repository.
		 *
		 * @param 	  	zCoordinate	The z coordinate of the horizontal plane.
		 * @param [in]	localCrs   	(Optional) If non-null, the local CRS. If @c nullptr (default), the
		 * 							repository default local CRS will be used.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackHorizontalPlaneGeometryPatch(double zCoordinate, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) = 0;

		/**
		 * Pushs back a new patch which is not a horizontal plane. Its geometry is given by means of 3
		 * xyz points.
		 *
		 * @exception	std::invalid_argument	If <tt>localCrs == nullptr</tt> and no default CRS is
		 * 										defined in the repository.
		 *
		 * @param 	  	x1			The x value of the first point.
		 * @param 	  	y1			The y value of the first point.
		 * @param 	  	z1			The z value of the first point.
		 * @param 	  	x2			The x value of the second point.
		 * @param 	  	y2			The y value of the second point.
		 * @param 	  	z2			The z value of the second point.
		 * @param 	  	x3			The x value of the third point.
		 * @param 	  	y3			The y value of the third point.
		 * @param 	  	z3			The z value of the third point.
		 * @param [in]	localCrs	(Optional) If non-null, the local CRS. If @c nullptr (default), the
		 * 							repository default local CRS will be used.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackTiltedPlaneGeometryPatch(
			double x1, double y1, double z1,
			double x2, double y2, double z2,
			double x3, double y3, double z3,
			RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) = 0;

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
