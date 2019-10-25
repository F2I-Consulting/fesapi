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

#include "../resqml2/MdDatum.h"

namespace RESQML2_0_1_NS
{
	class MdDatum : public RESQML2_NS::MdDatum
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT MdDatum(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::MdDatum(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param repo					The repo where the underlying gsoap proxy is going to be created.
		* @param guid						The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param locCrs						The local CRS where the ordinal are given
		* @param originKind					Indicates the kind of the MD reference point.
		* @param referenceLocationOrdinal1	The location of the MD reference point on the first axis of the local 3d CRS.
		* @param referenceLocationOrdinal2	The location of the MD reference point on the second axis of the local 3d CRS.
		* @param referenceLocationOrdinal3	The location of the MD reference point on the third axis of the local 3d CRS.
		*/
		MdDatum(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			RESQML2_NS::AbstractLocal3dCrs * locCrs, gsoap_resqml2_0_1::resqml20__MdReference originKind,
			double referenceLocationOrdinal1, double referenceLocationOrdinal2, double referenceLocationOrdinal3);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		MdDatum(gsoap_resqml2_0_1::_resqml20__MdDatum* fromGsoap) :RESQML2_NS::MdDatum(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~MdDatum() {}

		/**
		* Get the Local 3d CRS dor where the reference point ordinals are given
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getLocalCrsDor() const;

		/**
		* Getter of the first ordinal of the reference location.
		*/
		DLL_IMPORT_OR_EXPORT double getX() const;
		DLL_IMPORT_OR_EXPORT double getXInGlobalCrs() const;

		/**
		* Getter of the second ordinal of the reference location.
		*/
		DLL_IMPORT_OR_EXPORT double getY() const;
		DLL_IMPORT_OR_EXPORT double getYInGlobalCrs() const;

		/**
		* Getter of the third ordinal of the reference location.
		*/
		DLL_IMPORT_OR_EXPORT double getZ() const;
		DLL_IMPORT_OR_EXPORT double getZInGlobalCrs() const;

		/**
		* Getter of the origin kind of the MD.
		*/
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__MdReference getOriginKind() const;

	protected:

		void setXmlLocalCrs(RESQML2_NS::AbstractLocal3dCrs * localCrs);

		// XML backward relationship
		std::vector<class WellboreTrajectoryRepresentation*> wellboreTrajectoryRepresentationSet;
	};
}
