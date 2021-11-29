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

#include "../common/AbstractObject.h"

namespace EML2_3_NS
{
	/** A local depth 3D crs. */
	class LocalEngineering2dCrs final : public COMMON_NS::AbstractObject
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT LocalEngineering2dCrs(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		 * Construct a LocalEngineering2dCrs deriving from an EPSG projected CRS
		 *
		 * @param [in,out]	repo		  		If non-null, the repo.
		 * @param 		  	guid		  		Unique identifier.
		 * @param 		  	title		  		The title.
		 * @param 		  	projectedEpsgCode	The EPSG code of the projected CRS
		 * @param 		  	originOrdinal1		The first origin ordinal.
		 * @param 		  	originOrdinal2		The second origin ordinal.
		 * @param 		  	projectedUom  		The projected uom.
		 * @param 		  	azimuth		 		The areal rotation regarding the north.
		 * @param 		  	azimuthUom			The unit of measure of the @p azimuth.
		 * @param 		  	azimuthReference	The kind of north reference of the @p azimuth.
		 * @param			axisOrder			The axis order of the projected CRS.
		 */
		LocalEngineering2dCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
			uint64_t projectedEpsgCode,
			double originOrdinal1, double originOrdinal2, gsoap_eml2_3::eml23__LengthUom projectedUom,
			double azimuth, gsoap_eml2_3::eml23__PlaneAngleUom azimuthUom, gsoap_eml2_3::eml23__NorthReferenceKind azimuthReference,
			gsoap_eml2_3::eml23__AxisOrder2d axisOrder);

		/**
		 * Construct a LocalEngineering2dCrs deriving from an unknown projected CRS
		 *
		 * @param [in,out]	repo		  		If non-null, the repo.
		 * @param 		  	guid		  		Unique identifier.
		 * @param 		  	title		  		The title.
		 * @param 		  	unknownReason		The reason why this CRS is unknown.
		 * @param 		  	originOrdinal1		The first origin ordinal.
		 * @param 		  	originOrdinal2		The second origin ordinal.
		 * @param 		  	projectedUom  		The projected uom.
		 * @param 		  	azimuth		 		The areal rotation regarding the north.
		 * @param 		  	azimuthUom			The unit of measure of the @p azimuth.
		 * @param 		  	azimuthReference	The kind of north reference of the @p azimuth.
		 * @param			axisOrder			The axis order of the projected CRS.
		 */
		LocalEngineering2dCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
			std::string unknownReason,
			double originOrdinal1, double originOrdinal2, gsoap_eml2_3::eml23__LengthUom projectedUom,
			double azimuth, gsoap_eml2_3::eml23__PlaneAngleUom azimuthUom, gsoap_eml2_3::eml23__NorthReferenceKind azimuthReference,
			gsoap_eml2_3::eml23__AxisOrder2d axisOrder);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		LocalEngineering2dCrs(gsoap_eml2_3::_eml23__LocalEngineering2dCrs* fromGsoap): COMMON_NS::AbstractObject(fromGsoap) {}

		/** Destructor does nothing since the memory is manged by the gsoap context. */
		~LocalEngineering2dCrs() = default;

		/**
		 * Gets the first origin ordinal of this local CRS. This is the X location of the origin of the
		 * local areal axes relative to the projected CRS origin. The unit of measure is defined by the
		 * unit of measure for the projected 2d CRS.
		 *
		 * @returns	The first origin ordinal of this local CRS.
		 */
		DLL_IMPORT_OR_EXPORT double getOriginOrdinal1() const;

		/**
		 * Gets the second origin ordinal of this local CRS. This is the Y location of the origin of the
		 * local areal axes relative to the projected CRS origin. The unit of measure is defined by the
		 * unit of measure for the projected 2d CRS.
		 *
		 * @returns	The second origin ordinal of this local CRS.
		 */
		DLL_IMPORT_OR_EXPORT double getOriginOrdinal2() const;

		/**
		 * Get the azimuth of this CRS.
		 *
		 * @returns	The azimuth.
		 */
		DLL_IMPORT_OR_EXPORT double getAzimuth() const;

		/**
		 * Get the azimuth uom of this CRS as a string.
		 *
		 * @returns	The azimuth uom.
		 */
		DLL_IMPORT_OR_EXPORT std::string getAzimuthUomAsString() const;

		/**
		 * Indicates either the associated projected CRS is identified by means of an EPSG code or not.
		 *
		 * @returns	True if the projected CRS is defined with an EPSG code, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isProjectedCrsDefinedWithEpsg() const;
		
		/**
		 * Indicates either the associated projected CRS is unknown or not.
		 *
		 * @returns	True if projected CRS is unknown, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isProjectedCrsUnknown() const;

		/**
		 * Gets the reason why the projected CRS is unknown.
		 *
		 * @exception	std::invalid_argument	If the associated projected CRS is not unknown.
		 *
		 * @returns	The projected CRS unknown reason.
		 */
		DLL_IMPORT_OR_EXPORT std::string getProjectedCrsUnknownReason() const;

		/**
		 * Gets the EPSG code of the projected CRS
		 *
		 * @exception	std::invalid_argument	If the associated projected CRS is not an EPSG one.
		 *
		 * @returns	The projected CRS EPSG code.
		 */
		DLL_IMPORT_OR_EXPORT int64_t getProjectedCrsEpsgCode() const;

		/**
		 * Gets the projected CRS unit of measure as a string
		 *
		 * @returns	The projected CRS unit of measure as string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getProjectedCrsUnitAsString() const;

		/**
		 * Gets the axis order of the projected CRS.
		 *
		 * @returns	The axis order of the projected CRS.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__AxisOrder2d getAxisOrder() const;

		/**
		 * Sets the axis order of the projected CRS. It defines the coordinate system axis order of the
		 * global projected CRS when the projected CRS is an unknown CRS, else it must correspond to the
		 * axis order of the projected CRS.
		 *
		 * @param 	axisOrder	The axis order to set.
		 */
		DLL_IMPORT_OR_EXPORT void setAxisOrder(gsoap_eml2_3::eml23__AxisOrder2d axisOrder) const;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "eml23";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

		void loadTargetRelationships() final {}

	private:
		void init(gsoap_eml2_3::eml23__LocalEngineering2dCrs* local2dCrs, const std::string& guid, const std::string& title,
			double originOrdinal1, double originOrdinal2, gsoap_eml2_3::eml23__LengthUom projectedUom,
			double azimuth, gsoap_eml2_3::eml23__PlaneAngleUom azimuthUom, gsoap_eml2_3::eml23__NorthReferenceKind azimuthReference,
			gsoap_eml2_3::eml23__AxisOrder2d axisOrder);
	};
}
