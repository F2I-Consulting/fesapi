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

namespace RESQML2_0_1_NS
{
	class PolylineRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	private :
		gsoap_resqml2_0_1::resqml20__PointGeometry* getPointGeometry2_0_1(unsigned int patchIndex) const;

		void init(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, bool isClosed = false);

	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT PolylineRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractRepresentation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp					The interpretation which this representation represents.
		* @param guid					The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param roleKind				Indicates the role of this representation.
		* @param isClosed				Indicates wether this line representaiton is closed or not.
		*/
		PolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__LineRole roleKind,
			bool isClosed = false);

		/**
		* Creates an instance of this class in a gsoap context.
		* @param guid					The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param isClosed				Indicates wether this line representaiton is closed or not.
		*/
		PolylineRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title, bool isClosed = false);

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp					The interpretation which this representation represents.
		* @param crs					The local 3d crs where this representation is given.
		* @param guid					The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param isClosed				Indicates wether this line representaiton is closed or not.
		*/
		PolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, bool isClosed = false);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		PolylineRepresentation(gsoap_resqml2_0_1::_resqml20__PolylineRepresentation* fromGsoap) : RESQML2_NS::AbstractRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~PolylineRepresentation() {}

		gsoap_resqml2_0_1::eml20__DataObjectReference* getHdfProxyDor() const;

		/**
		* Get the xyz point count in a given patch.
		*/
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		 * @param points		The points which constitute the polyline. Ordered by XYZ and then points.
		 * @param pointCount	The count of points in the polyline. Must be three times the count of the array of doubles "points".
		 * @param proxy			The HDf proxy defining the HDF file where the double array will be stored.
		 */
		DLL_IMPORT_OR_EXPORT void setGeometry(double * points, unsigned int pointCount, COMMON_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr);

		/**
		* Indicates if the representaiton is a closed polyline or a non closed polyline.
		*/
		DLL_IMPORT_OR_EXPORT bool isClosed() const;

		/**
		* Indicates if the polyline is associated to a particular LineRole.
		*/
		DLL_IMPORT_OR_EXPORT bool hasALineRole() const;
		
		/**
		* Indicates wether the instance corresponds to a seismic 2D line or not.
		*/
		DLL_IMPORT_OR_EXPORT bool isASeismicLine() const;

		/**
		* Indicates wether the instance corresponds to a facies 2d line or not.
		*/
		DLL_IMPORT_OR_EXPORT bool isAFaciesLine() const;

		/**
		* Get the role of this polyline.
		* Throw an exception if the polyline has no role (see method hasALineRole).
		*/
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__LineRole getLineRole() const;

		/**
		* Set the line role of this instance
		*/
		DLL_IMPORT_OR_EXPORT void setLineRole(gsoap_resqml2_0_1::resqml20__LineRole lineRole);

		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const {return 1;}

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
