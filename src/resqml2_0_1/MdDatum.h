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

#include "resqml2/MdDatum.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT MdDatum : public resqml2::MdDatum
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		MdDatum(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : resqml2::MdDatum(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param soapContext				The soap context where the underlying gsoap proxy is going to be created.
		* @param guid						The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param locCrs						The local CRS where the ordinal are given
		* @param originKind					Indicates the kind of the MD reference point.
		* @param referenceLocationOrdinal1	The location of the MD reference point on the first axis of the local 3d CRS.
		* @param referenceLocationOrdinal2	The location of the MD reference point on the second axis of the local 3d CRS.
		* @param referenceLocationOrdinal3	The location of the MD reference point on the third axis of the local 3d CRS.
		*/
		MdDatum(soap* soapContext, const std::string & guid, const std::string & title,
			resqml2::AbstractLocal3dCrs * locCrs, const gsoap_resqml2_0_1::resqml2__MdReference & originKind,
			const double & referenceLocationOrdinal1, const double & referenceLocationOrdinal2, const double & referenceLocationOrdinal3);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		MdDatum(gsoap_resqml2_0_1::_resqml2__MdDatum* fromGsoap) :resqml2::MdDatum(fromGsoap) {}

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
		double getX() const;
		double getXInGlobalCrs() const;

		/**
		* Getter of the second ordinal of the reference location.
		*/
		double getY() const;
		double getYInGlobalCrs() const;

		/**
		* Getter of the third ordinal of the reference location.
		*/
		double getZ() const;
		double getZInGlobalCrs() const;

		/**
		* Getter of the origin kind of the MD.
		*/
		gsoap_resqml2_0_1::resqml2__MdReference getOriginKind() const;

	protected:

		void setXmlLocalCrs(resqml2::AbstractLocal3dCrs * localCrs);

		// XML backward relationship
		std::vector<class WellboreTrajectoryRepresentation*> wellboreTrajectoryRepresentationSet;
	};
}

