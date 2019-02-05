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

#include "resqml2/AbstractRepresentation.h"

namespace RESQML2_0_1_NS
{
	class DLL_IMPORT_OR_EXPORT PlaneSetRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	private :
		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry2_0_1(const unsigned int & patchIndex) const {return nullptr;}

	public:

		/**
		* Only to be used in partial transfer context
		*/
		PlaneSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractRepresentation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp							The interpretation this representation represents.
		* @param crs							The local CRS where the geometry of this representation is given.
		* @param guid							The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title							A title for the instance to create.
		*/
		PlaneSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
				const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		PlaneSetRepresentation(gsoap_resqml2_0_1::_resqml2__PlaneSetRepresentation* fromGsoap) : RESQML2_NS::AbstractRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~PlaneSetRepresentation() {}

		std::string getHdfProxyUuid() const {return "";};

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		/**
		* Get the Local 3d CRS dor where the reference point ordinals are given
		* It assumes there is only one CRS used by this instance.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getLocalCrsDor() const;

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
		 * Get the number of triangle patch
		 */
		unsigned int getPatchCount() const;

		/**
		* Push back a new patch which is an horizontal plane
		* @param zCoordinate	The Z coordinate of the horizontal plane
		*/
		void pushBackHorizontalPlaneGeometryPatch(const double & zCoordinate);

		/**
		* Push back a new patch which is not a horizontal plane. It s geometry is given by means of 3 XYZ points.
		*/
		void pushBackTiltedPlaneGeometryPatch(const double & x1, const double & y1, const double & z1,
			const double & x2, const double & y2, const double & z2,
			const double & x3, const double & y3, const double & z3);
	};
}

