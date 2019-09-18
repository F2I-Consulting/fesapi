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
	class PointSetRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	private :
		gsoap_resqml2_0_1::resqml20__PointGeometry* getPointGeometry2_0_1(unsigned int patchIndex) const;

	public:

		/**
		* Only to be used in partial transfer context
		*/
		PointSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractRepresentation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp							The interpretation this representation represents.
		* @param guid							The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title							A title for the instance to create.
		*/
		PointSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
				const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		PointSetRepresentation(gsoap_resqml2_0_1::_resqml20__PointSetRepresentation* fromGsoap) : RESQML2_NS::AbstractRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~PointSetRepresentation() {}

		gsoap_resqml2_0_1::eml20__DataObjectReference* getHdfProxyDor() const;

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const {return XML_TAG;}

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
		 * Get the number of triangle patch
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const;

		/**
		* Push back a new patch of polylines
		* @param xyzPointCount	The XYZ point count in this patch.
		* @param xyzPoints		The XYZ values of the points of the patch. Ordered by XYZ and then by xyzPointCount. It must be three times xyzPointCount.
		* @param localCrs		The local CRS wher the points are given.
		* @param proxy			The HDF proxy which defines where the XYZ points will be stored.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackGeometryPatch(
			unsigned int xyzPointCount, double * xyzPoints,
			COMMON_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr);
	};
}
