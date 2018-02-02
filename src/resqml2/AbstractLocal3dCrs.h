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

namespace resqml2
{
	class DLL_IMPORT_OR_EXPORT AbstractLocal3dCrs : public common::AbstractObject
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractLocal3dCrs(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : common::AbstractObject(partialObject) {}

		AbstractLocal3dCrs() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractLocal3dCrs(gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs* fromGsoap):
			common::AbstractObject(fromGsoap) {}

		/**
		* Get the Z offset which is always equal to zero for a time CRS.
		* Don't mix zOffset vs depthOffset : the schema calls zOffset what is actually a depthOrElevationOffset.
		*/
		virtual double getZOffset() const = 0;

	public:

		/**
		* Destructor does nothing since the memory is manged by the gsoap context.
		*/
		virtual ~AbstractLocal3dCrs() {}

		/**
		* Add a geometrical representation which is based on this local CRS
		* Does not add the inverse relationship i.e. from the geometrical representation to this local CRS.
		*/
		void addRepresentation(class AbstractRepresentation* rep);

		/**
		* Get the first origin ordinal (usually called X) of the local CRS in the global projected CRS.
		*/
		double getOriginOrdinal1() const;

		/**
		* Get the second origin ordinal (usually called Y) of the local CRS in the global projected CRS.
		*/
		double getOriginOrdinal2() const;

		/**
		* Get the depth or elevation origin of this local CRS in the global vertical CRS.
		* If this local CRS is a time CRS, this value defines the Seismic Reference Datum.
		*/
		double getOriginDepthOrElevation() const;

		/**
		* Get the rotation in radians of the the local Y axis relative to the global projected axis which is 90 degrees counter-clockwise from the other global axis.
		* A positive value indicates a clockwise rotation from the global axis.
		* A negative value indicates a counterclockwise rotation form the global axis.
		*/
		double getArealRotation() const;

		/**
		* Indicates if the depth or elevation values given in this local CRS are depth ones or elevation ones.
		*/
		bool isDepthOriented() const;

		/**
		* Indicates either the associated projected Crs is identified by means of EPSG or not.
		*/
		bool isProjectedCrsDefinedWithEpsg() const;

		/**
		* Indicates either the associated projected Crs is unknown.
		*/
		virtual bool isProjectedCrsUnknown() const;

		/**
		* Get the reason why the projected Crs is unknown.
		*/
		const std::string & getProjectedCrsUnknownReason() const;

		/**
		* Get the EPSG code of the projected CRS
		*/
		unsigned long long getProjectedCrsEpsgCode() const;

		/**
		* Indicates either the associated vertical Crs is identified by means of EPSG or not.
		*/
		bool isVerticalCrsDefinedWithEpsg() const;

		/**
		* Indicates either the associated vertical Crs is unknown.
		*/
		bool isVerticalCrsUnknown() const;

		/**
		* Get the reason why the vertical Crs is unknown.
		*/
		const std::string & getVerticalCrsUnknownReason() const;

		/**
		* Get the EPSG code of the vertical CRS
		*/
		unsigned long long getVerticalCrsEpsgCode() const;

		/**
		 * Get the vertical crs unit as a string
		 */
		std::string getVerticalCrsUnitAsString() const;

		gsoap_resqml2_0_1::eml20__PlaneAngleUom getArealRotationUom() const;

		/**
		* Get the projected crs unit
		*/
		gsoap_resqml2_0_1::eml20__LengthUom getProjectedCrsUnit() const;

		/**
		* Get the projected crs unit as a string
		*/
		std::string getProjectedCrsUnitAsString() const;

		/**
		* Get the vertical crs unit
		*/
		gsoap_resqml2_0_1::eml20__LengthUom getVerticalCrsUnit() const;

		/**
		* Get the axis order of the projected Crs
		*/
		gsoap_resqml2_0_1::eml20__AxisOrder2d getAxisOrder() const;

		void convertXyzPointsToGlobalCrs(double * xyzPoints, const ULONG64 & xyzPointCount, bool withoutTranslation = false) const;

	protected:
		
		std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc) {}

		// XML backward relationship
		std::vector<class AbstractRepresentation*> repSet;
		std::vector<MdDatum*> mdDatumSet;

	private:
		/**
		* Add a md information which is based on this local CRS
		* Does not add the inverse relationship i.e. from the md information to this local CRS.
		*/
		void addMdDatum(MdDatum* mdInfo);

		friend void MdDatum::setLocalCrs(AbstractLocal3dCrs * localCrs);
	};
}

