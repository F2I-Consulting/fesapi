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

#include "resqml2_0_1/AbstractSurfaceRepresentation.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT PolylineRepresentation : public resqml2::AbstractRepresentation
	{
	private :
		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry2_0_1(const unsigned int & patchIndex) const;

		/**
		 * Push back a representation for which the current instance is it outer ring.
		 * Does not add the inverse relationship i.e. from the representaiton to this outer ring.
		 */
		void pushBackRepresentationOuterRing(AbstractSurfaceRepresentation* rep) {outerRingOfSet.push_back(rep);}
		friend void AbstractSurfaceRepresentation::pushBackOuterRing(PolylineRepresentation * outerRing);

		/**
		 * Push back a representation for which the current instance is it inner ring.
		 * Does not add the inverse relationship i.e. from the representaiton to this inner ring.
		 */
		void pushBackRepresentationInnerRing(AbstractSurfaceRepresentation* rep) {innerRingOfSet.push_back(rep);}

		// Backward relationships
		std::vector<AbstractSurfaceRepresentation*> outerRingOfSet;
		std::vector<AbstractSurfaceRepresentation*> innerRingOfSet;

		void init(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed = false);

	public:

		/**
		* Only to be used in partial transfer context
		*/
		PolylineRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : resqml2::AbstractRepresentation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp					The interpretation which this representation represents.
		* @param crs					The local 3d crs where this representation is given.
		* @param guid					The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param roleKind				Indicates the role of this representation.
		* @param isClosed				Indicates wether this line representaiton is closed or not.
		*/
		PolylineRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__LineRole & roleKind,
			bool isClosed = false);

		/**
		* Creates an instance of this class in a gsoap context.
		* @param crs					The local 3d crs where this representation is given.
		* @param guid					The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param isClosed				Indicates wether this line representaiton is closed or not.
		*/
		PolylineRepresentation(resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed = false);

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp					The interpretation which this representation represents.
		* @param crs					The local 3d crs where this representation is given.
		* @param guid					The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param isClosed				Indicates wether this line representaiton is closed or not.
		*/
		PolylineRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed = false);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		PolylineRepresentation(gsoap_resqml2_0_1::_resqml2__PolylineRepresentation* fromGsoap) : resqml2::AbstractRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~PolylineRepresentation() {}

		std::string getHdfProxyUuid() const;

		/**
		* Get the xyz point count in a given patch.
		*/
		ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		 * @param points		The points which constitute the polyline. Ordered by XYZ and then points.
		 * @param pointCount	The count of points in the polyline. Must be three times the count of the array of doubles "points".
		 * @param proxy			The HDf proxy defining the HDF file where the double array will be stored.
		 */
		void setGeometry(double * points, const unsigned int & pointCount, common::AbstractHdfProxy* proxy);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		/**
		* Indicates if the representaiton is a closed polyline or a non closed polyline.
		*/
		bool isClosed() const;

		/**
		* Indicates if the polyline is associated to a particular LineRole.
		*/
		bool hasALineRole() const;
		
		/**
		* Indicates wether the instance corresponds to a seismic 2D line or not.
		*/
		bool isASeismicLine() const;

		/**
		* Indicates wether the instance corresponds to a facies 2d line or not.
		*/
		bool isAFaciesLine() const;

		/**
		* Get the role of this polyline.
		* Throw an exception if the polyline has no role (see method hasALineRole).
		*/
        gsoap_resqml2_0_1::resqml2__LineRole getLineRole() const;

		/**
		* Set the line role of this instance
		*/
		void setLineRole(const gsoap_resqml2_0_1::resqml2__LineRole & lineRole);

		unsigned int getPatchCount() const {return 1;}

	protected:
		std::vector<epc::Relationship> getAllEpcRelationships() const;
	};
}

