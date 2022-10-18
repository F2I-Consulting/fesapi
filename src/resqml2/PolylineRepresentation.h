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
	 * @brief	A representation made up of a single polyline or "polygonal chain", which may be
	 * 			closed or not. See definition here:
	 * 			http://en.wikipedia.org/wiki/Piecewise_linear_curve.
	 * 			
	 * 			BUSINESS RULE: To record a polyline the writer software must give the values of the
	 * 			geometry of each node in an order corresponding to the logical series of segments
	 * 			(edges). The geometry of a polyline must be a 1D array of points.
	 * 			
	 * 			A simple polygonal chain is one in which only consecutive (or the first and the last)
	 * 			segments intersect and only at their endpoints.
	 */
	class PolylineRepresentation : public AbstractRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~PolylineRepresentation() = default;

		/**
		 * Sets the geometry of this polyline representation.
		 *
		 * @exception	std::invalid_argument	If <tt>proxy == nullptr</tt> and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If <tt>localCrs == nullptr</tt> and no default local CRS
		 * 										id defined in the repository.
		 *
		 * @param [in]	  	points	  	The points which constitute the polyline. Ordered by xyz and then
		 * 								points. Size is <tt>3 * pointCount</tt>.
		 * @param 		  	pointCount	The count of points in the polyline.
		 * @param [in,out]	proxy	  	(Optional) The HDF proxy which defines where the xyz points will
		 * 								be stored. If @c nullptr (default), then the repository default
		 * 								HDF proxy will be used.
		 * @param [in]	  	localCrs  	(Optional) The local CRS where the points are given. If @c
		 * 								nullptr (default), then the repository default local CRS will be
		 * 								used.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setGeometry(double const* points, unsigned int pointCount, EML2_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) = 0;

		/**
		 * Indicates if this representation is a closed polyline or a non closed polyline. A closed
		 * polyline is one in which the first vertex coincides with the last one, or the first and the
		 * last vertices are connected by a line segment.
		 *
		 * @returns	True if this polyline representation is closed, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isClosed() const = 0;

		/**
		 * Indicates if this polyline is associated to a particular line role.
		 *
		 * @returns	True if this polyline has a line role, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool hasALineRole() const = 0;

		/**
		 * Indicates whether this instance corresponds to a seismic 2d line or not.
		 *
		 * @returns	True if is a seismic line, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isASeismicLine() const;

		/**
		 * Indicates whether this instance corresponds to a facies 2d line or not.
		 *
		 * @returns	True if it is a facies line, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAFaciesLine() const;

		/**
		 * Gets the line role of this polyline.
		 *
		 * @exception	std::logic_error	If this polyline has no line role (see hasALineRole()).
		 *
		 * @returns	The line role.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_eml2_3::resqml22__LineRole getLineRole() const = 0;

		/**
		 * Sets the line role of this instance.
		 *
		 * @param 	lineRole	The line role.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setLineRole(gsoap_eml2_3::resqml22__LineRole lineRole) = 0;

		DLL_IMPORT_OR_EXPORT uint64_t getPatchCount() const final {return 1;}

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
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
