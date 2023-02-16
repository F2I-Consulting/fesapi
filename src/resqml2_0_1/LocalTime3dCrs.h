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

#include "../resqml2/LocalTime3dCrs.h"

namespace RESQML2_0_1_NS
{
	/** A local time 3D crs. */
	class LocalTime3dCrs final : public RESQML2_NS::LocalTime3dCrs
	{
	private:

		/**
		 * Initializes this object
		 *
		 * @param [in,out]	repo		  	If non-null, the repo.
		 * @param 		  	guid		  	Unique identifier.
		 * @param 		  	title		  	The title.
		 * @param 		  	originOrdinal1	The first origin ordinal.
		 * @param 		  	originOrdinal2	The second origin ordinal.
		 * @param 		  	originOrdinal3	The third origin ordinal.
		 * @param 		  	arealRotation 	The areal rotation.
		 * @param 		  	projectedUom  	The projected uom.
		 * @param 		  	timeUom		  	The time uom.
		 * @param 		  	verticalUom   	The vertical uom.
		 * @param 		  	isUpOriented  	True if is up oriented, false if not.
		 */
		void init(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, bool isUpOriented);

		/**
		 * Get z coordinate offset
		 *
		 * @returns	The z coordinate offset.
		 */
		double getZOffset() const { return .0; }

	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT LocalTime3dCrs(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::LocalTime3dCrs(partialObject) {}

		/**
		 * @brief	Creates a local depth 3d CRS which is fully identified by means of EPSG code.
		 *
		 * @exception	std::invalid_argument	If <tt>projectedEpsgCode == 0 || verticalEpsgCode ==
		 * 										0</tt>.
		 *
		 * @param [in]	repo			 	The repo where the underlying gsoap proxy is going to be
		 * 									created.
		 * @param 	  	guid			 	The guid to set to the local 3d crs. If empty then a new guid
		 * 									will be generated.
		 * @param 	  	title			 	A title for the instance to create.
		 * @param 	  	originOrdinal1   	The offset of the global 2d crs on its first axis.
		 * @param 	  	originOrdinal2   	The offset of the global 2d crs on its second axis.
		 * @param 	  	originOrdinal3   	The offset in depth of the local CRS regarding the depth
		 * 									origin of the vertical CRS.
		 * @param 	  	arealRotation	 	The areal rotation in radians regarding the projected crs.
		 * @param 	  	projectedUom	 	The unit of measure of the projected axis of this instance.
		 * @param 	  	projectedEpsgCode	The epsg code of the associated projected CRS.
		 * @param 	  	timeUom			 	The unit of measure of the Z offset of this instance.
		 * @param 	  	verticalUom		 	The unit of measure of the vertical axis of this instance.
		 * @param 	  	verticalEpsgCode 	The epsg code of the associated vertical CRS.
		 * @param 	  	isUpOriented	 	If true, indicates that the Z offset if an elevation when
		 * 									positive. If false, the Z offset is a depth when positive.
		 */
		LocalTime3dCrs(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, uint64_t projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom,  unsigned int verticalEpsgCode, bool isUpOriented);

		/**
		 * Creates a local depth 3d CRS which is fully unknown.
		 *
		 * @param [in,out]	repo				  	The repo where the underlying gsoap proxy is going to
		 * 											be created.
		 * @param 		  	guid				  	The guid to set to the local 3d crs. If empty then a
		 * 											new guid will be generated.
		 * @param 		  	title				  	A title for the instance to create.
		 * @param 		  	originOrdinal1		  	The offset of the global 2d crs on its first axis.
		 * @param 		  	originOrdinal2		  	The offset of the global 2d crs on its second axis.
		 * @param 		  	originOrdinal3		  	The offset in depth of the local CRS regarding the
		 * 											depth origin of the vertical CRS.
		 * @param 		  	arealRotation		  	The areal rotation in radians regarding the projected
		 * 											crs.
		 * @param 		  	projectedUom		  	The unit of measure of the projected axis of this
		 * 											instance.
		 * @param 		  	projectedUnknownReason	Indicates why the projected CRS cannot be provided
		 * 											using EPSG or GML.
		 * @param 		  	timeUom				  	The unit of measure of the Z offset of this instance.
		 * @param 		  	verticalUom			  	The unit of measure of the vertical axis of this
		 * 											instance.
		 * @param 		  	verticalUnknownReason 	Indicates why the vertical CRS cannot be provided
		 * 											using EPSG or GML.
		 * @param 		  	isUpOriented		  	If true, indicates that the Z offset if an elevation
		 * 											when positive. If false, the Z offset is a depth when
		 * 											positive.
		 */
		LocalTime3dCrs(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string & projectedUnknownReason,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string & verticalUnknownReason, bool isUpOriented);

		/**
		 * @brief	Creates a local depth 3d CRS which is identified by an EPSG code for its projected
		 * 			part and which is unkown for its vertial part.
		 *
		 * @exception	std::invalid_argument	If <tt>projectedEpsgCode == 0</tt>.
		 *
		 * @param [in]	repo				 	The repo where the underlying gsoap proxy is going to
		 * 										be created.
		 * @param 	  	guid				 	The guid to set to the local 3d crs. If empty then a new
		 * 										guid will be generated.
		 * @param 	  	title				 	A title for the instance to create.
		 * @param 	  	originOrdinal1		 	The offset of the global 2d crs on its first axis.
		 * @param 	  	originOrdinal2		 	The offset of the global 2d crs on its second axis.
		 * @param 	  	originOrdinal3		 	The offset in depth of the local CRS regarding the depth
		 * 										origin of the vertical CRS.
		 * @param 	  	arealRotation		 	The areal rotation in radians regarding the projected crs.
		 * @param 	  	projectedUom		 	The unit of measure of the projected axis of this
		 * 										instance.
		 * @param 	  	projectedEpsgCode	 	The epsg code of the associated projected CRS.
		 * @param 	  	timeUom				 	The unit of measure of the Z offset of this instance.
		 * @param 	  	verticalUom			 	The unit of measure of the vertical axis of this instance.
		 * @param 	  	verticalUnknownReason	Indicates why the vertical CRS cannot be provided using
		 * 										EPSG or GML.
		 * @param 	  	isUpOriented		 	If true, indicates that the Z offset if an elevation when
		 * 										positive. If false, the Z offset is a depth when positive.
		 */
		LocalTime3dCrs(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, uint64_t projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string & verticalUnknownReason, bool isUpOriented);

		/**
		 * @brief	Creates a local depth 3d CRS which unkown for its projected part and which is
		 * 			identified by an EPSG code for its vertical part.
		 *
		 * @exception	std::invalid_argument	If <tt>verticalEpsgCode == 0</tt>.
		 *
		 * @param [in]	repo				  	The repo where the underlying gsoap proxy is going to
		 * 											be created.
		 * @param 	  	guid				  	The guid to set to the local 3d crs. If empty then a new
		 * 										guid will be generated.
		 * @param 	  	title				  	A title for the instance to create.
		 * @param 	  	originOrdinal1		  	The offset of the global 2d crs on its first axis.
		 * @param 	  	originOrdinal2		  	The offset of the global 2d crs on its second axis.
		 * @param 	  	originOrdinal3		  	The offset in depth of the local CRS regarding the depth
		 * 										origin of the vertical CRS.
		 * @param 	  	arealRotation		  	The areal rotation in radians regarding the projected crs.
		 * @param 	  	projectedUom		  	The unit of measure of the projected axis of this
		 * 										instance.
		 * @param 	  	projectedUnknownReason	Indicates why the projected CRS cannot be provided using
		 * 										EPSG or GML.
		 * @param 	  	timeUom				  	The unit of measure of the Z offset of this instance.
		 * @param 	  	verticalUom			  	The unit of measure of the vertical axis of this instance.
		 * @param 	  	verticalEpsgCode	  	The epsg code of the associated vertical CRS.
		 * @param 	  	isUpOriented		  	If true, indicates that the Z offset if an elevation when
		 * 										positive. If false, the Z offset is a depth when positive.
		 */
		LocalTime3dCrs(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string & projectedUnknownReason,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, unsigned int verticalEpsgCode, bool isUpOriented);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		LocalTime3dCrs(gsoap_resqml2_0_1::_resqml20__LocalTime3dCrs* fromGsoap): RESQML2_NS::LocalTime3dCrs(fromGsoap) {}

		/** Destructor does nothing since the memory is manged by the gsoap context. */
		~LocalTime3dCrs() = default;

		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::eml20__TimeUom getUnit() const final;

		DLL_IMPORT_OR_EXPORT std::string getUnitAsString() const final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
