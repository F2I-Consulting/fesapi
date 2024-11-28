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

namespace EML2_NS
{
	/** @brief	Proxy class for an abstract local 3D coordinate reference system (CRS). */
	class AbstractLocal3dCrs : public COMMON_NS::AbstractObject
	{
	public:

		/** Destructor does nothing since the memory is manged by the gsoap context. */
		virtual ~AbstractLocal3dCrs() = default;

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
		 * Get the depth or elevation origin of this local CRS. This is Z offset of the origin of the
		 * local vertical axis relative to the vertical CRS origin. According to CRS type (depth or time)
		 * it corresponds to the depth or time datum. If this local CRS is a time CRS, this value
		 * defines the seismic reference datum. The unit of measure is defined by the unit of measure
		 * for the vertical CRS
		 *
		 * @returns	The origin depth or elevation.
		 */
		DLL_IMPORT_OR_EXPORT double getOriginDepthOrElevation() const;

		/**
		 * Get the rotation in radians of the local Y axis relative to the global projected Y axis which
		 * is 90 degrees counter-clockwise from the other global axis. A positive value indicates a
		 * clockwise rotation from the global axis. A negative value indicates a counterclockwise
		 * rotation form the global axis.
		 *
		 * @returns	The areal rotation.
		 */
		DLL_IMPORT_OR_EXPORT double getArealRotation() const;

		/**
		 * Indicates that Z values correspond to depth values and are increasing downward, as opposite
		 * to elevation values increasing upward. When the vertical CRS is known, it must correspond to
		 * the axis orientation of the vertical CRS.
		 *
		 * @returns	True if Z values are depth oriented, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isDepthOriented() const;

		/**
		 * Indicates either the associated projected CRS is identified by means of an EPSG code or not.
		 *
		 * @returns	True if the projected CRS is defined with an EPSG code, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isProjectedCrsDefinedWithEpsg() const;

		/**
		 * Indicates either the associated projected CRS is given in a WKT format or not.
		 *
		 * @returns	True if the projected CRS is given in a WKT format, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isProjectedCrsDefinedWithWkt() const;

		/**
		 * Indicates either the associated projected CRS is unknown or not.
		 *
		 * @returns	True if projected CRS is unknown, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isProjectedCrsUnknown() const;

		/**
		 * Gets the reason why the projected CRS is unknown.
		 *
		 * @exception	std::invalid_argument	If the associated projected CRS is not unknown.
		 *
		 * @returns	The projected CRS unknown reason.
		 */
		DLL_IMPORT_OR_EXPORT std::string getProjectedCrsUnknownReason() const;

		/**
		 * Gets the WKT of the projected CRS
		 *
		 * @exception	std::invalid_argument	If the associated projected CRS is not a WKT one.
		 *
		 * @returns	The projected CRS WKT.
		 */
		DLL_IMPORT_OR_EXPORT std::string getProjectedCrsWkt() const;

		/**
		 * Gets the EPSG code of the projected CRS
		 *
		 * @exception	std::invalid_argument	If the associated projected CRS is not an EPSG one.
		 *
		 * @returns	The projected CRS EPSG code.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getProjectedCrsEpsgCode() const;

		/**
		 * Indicates either the associated vertical CRS is identified by means of EPSG or not.
		 *
		 * @returns	True if the vertical CRS is defined with an EPSG code, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isVerticalCrsDefinedWithEpsg() const;

		/**
		 * Indicates either the associated vertical CRS is given in a WKT format or not.
		 *
		 * @returns	True if the vertical CRS is given in a WKT format, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isVerticalCrsDefinedWithWkt() const;

		/**
		 * Indicates either the associated vertical CRS is unknown or not.
		 *
		 * @returns	True if vertical CRS is unknown, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isVerticalCrsUnknown() const;

		/**
		 * Gets the reason why the vertical CRS is unknown.
		 *
		 * @exception	std::invalid_argument	If the associated vertical CRS is not unknown.
		 *
		 * @returns	The vertical CRS unknown reason.
		 */
		DLL_IMPORT_OR_EXPORT std::string getVerticalCrsUnknownReason() const;

		/**
		 * Gets the WKT of the vertical CRS
		 *
		 * @exception	std::invalid_argument	If the associated projected CRS is not a WKT one.
		 *
		 * @returns	The vertical CRS WKT.
		 */
		DLL_IMPORT_OR_EXPORT std::string getVerticalCrsWkt() const;

		/**
		 * Gets the EPSG code of the vertical CRS
		 *
		 * @exception	std::invalid_argument	If the associated projected CRS is not an EPSG one.
		 *
		 * @returns	The vertical CRS EPSG code.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getVerticalCrsEpsgCode() const;

		/**
		 * Gets the areal rotation unit of measure.
		 *
		 * @returns	The areal rotation unit of measure.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::eml20__PlaneAngleUom getArealRotationUom() const;

		/**
		 * Gets the projected CRS unit of measure.
		 *
		 * @returns	The projected CRS unit unit of measure.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::eml20__LengthUom getProjectedCrsUnit() const;

		/**
		 * Gets the projected CRS unit of measure as a string
		 *
		 * @returns	The projected CRS unit of measure as string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getProjectedCrsUnitAsString() const;

		/**
		 * Gets the vertical CRS unit of measure.
		 *
		 * @returns	The vertical CRS unit of measure.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::eml20__LengthUom getVerticalCrsUnit() const;

		/**
		 * Gets the vertical CRS unit of measure as a string
		 *
		 * @returns	The vertical CRS unit of measure as string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getVerticalCrsUnitAsString() const;

		/**
		 * Check if the third axis of this local 3d CRS is in timeor not.
		 *
		 * @returns	True if this local 3d CRS is a time one. False if it is a depth/elevation one.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isATimeCrs() const = 0;

		/**
		 * Gets the unit of measure of the third axis of this local CRS if it is a time CRS.
		 * Otherwise throw an exception (if isATimeCrs() returns false)
		 *
		 * @returns	The time unit of measure of the third axis.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::eml20__TimeUom getTimeUom() const = 0;

		/**
		 * Gets the unit of measure as a sting of the third axis of this local CRS if it is a time CRS.
		 * Otherwise throw an exception (if isATimeCrs() returns false)
		 *
		 * @returns	The time unit of measure of the third axis.
		 */
		DLL_IMPORT_OR_EXPORT std::string getTimeUomAsString() const;

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
		 * Convert some xyz points from local to global CRS.
		 *
		 * @param [in,out]	xyzPoints		  	An array of xyz points. The i-th point is defined by
		 * 										<tt>(x, y, z) = (xyzPoints[i], xyzPoints[i+1],
		 * 										xyzPoints[i+2])</tt>.
		 * @param 		  	xyzPointCount	  	The number of xyz points. Must be equal to the size of @p
		 * 										xyzPoints divided by 3.
		 * @param 		  	withoutTranslation	(Optional) True to only compute the rotation (no
		 * 										translation is computed). Default value if false.
		 */
		DLL_IMPORT_OR_EXPORT void convertXyzPointsToGlobalCrs(double * xyzPoints, uint64_t xyzPointCount, bool withoutTranslation = false) const;

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		AbstractLocal3dCrs(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/** Default constructor */
		AbstractLocal3dCrs() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractLocal3dCrs(gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs* fromGsoap) :
			COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractLocal3dCrs(gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs* fromGsoap) :
			COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		 * Get the Z offset which is always equal to zero for a time CRS. Don't mix zOffset vs
		 * depthOffset : the schema calls zOffset what is actually a depthOrElevationOffset.
		 *
		 * @returns	The z coordinate offset.
		 */
		virtual double getZOffset() const = 0;
	};
}
