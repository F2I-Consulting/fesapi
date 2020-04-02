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
	/** A polyline representation. */
	class PolylineRepresentation : public AbstractRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~PolylineRepresentation() {}

		/**
		 * Sets a geometry
		 *
		 * @param [in,out]	points	  	The points which constitute the polyline. Ordered by XYZ and then
		 * 								points.
		 * @param 		  	pointCount	The count of points in the polyline. Must be three times the
		 * 								count of the array of doubles "points".
		 * @param [in,out]	proxy	  	(Optional) The HDf proxy defining the HDF file where the double
		 * 								array will be stored.
		 * @param [in,out]	localCrs  	(Optional) If non-null, the local crs.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setGeometry(double const* points, unsigned int pointCount, EML2_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) = 0;

		/**
		 * Indicates if the representaiton is a closed polyline or a non closed polyline.
		 *
		 * @returns	True if closed, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isClosed() const = 0;

		/**
		 * Indicates if the polyline is associated to a particular LineRole.
		 *
		 * @returns	True if a line role, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool hasALineRole() const = 0;

		/**
		 * Indicates wether the instance corresponds to a seismic 2D line or not.
		 *
		 * @returns	True if a seismic line, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isASeismicLine() const;

		/**
		 * Indicates wether the instance corresponds to a facies 2d line or not.
		 *
		 * @returns	True if the facies line, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAFaciesLine() const;

		/**
		 * Get the role of this polyline. Throw an exception if the polyline has no role (see method
		 * hasALineRole).
		 *
		 * @returns	The line role.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_eml2_3::resqml22__LineRole getLineRole() const = 0;

		/**
		 * Set the line role of this instance
		 *
		 * @param 	lineRole	The line role.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setLineRole(gsoap_eml2_3::resqml22__LineRole lineRole) = 0;

		/**
		 * Gets patch count
		 *
		 * @returns	The patch count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const {return 1;}

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
		DLL_IMPORT_OR_EXPORT PolylineRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractRepresentation(partialObject) {}

		/**
		 * Default constructor
		 */
		PolylineRepresentation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PolylineRepresentation(gsoap_resqml2_0_1::_resqml20__PolylineRepresentation* fromGsoap) : AbstractRepresentation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PolylineRepresentation(gsoap_eml2_3::_resqml22__PolylineRepresentation* fromGsoap) : AbstractRepresentation(fromGsoap) {}

		/**
		 * Initializes this object
		 *
		 * @param [in,out]	repo		If non-null, the repo.
		 * @param 		  	guid		Unique identifier.
		 * @param 		  	title   	The title.
		 * @param 		  	isClosed	(Optional) True if is closed, false if not.
		 */
		void init(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, bool isClosed = false);
	};
}
