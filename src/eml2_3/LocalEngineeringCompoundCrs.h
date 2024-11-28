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

#include "../eml2/AbstractLocal3dCrs.h"

namespace EML2_3_NS
{
	class LocalEngineering2dCrs;
	class VerticalCrs;

	/** A local Engineering compound CRS is based on a LocalEngineering2dCRS + a vertical CRS. */
	class LocalEngineeringCompoundCrs final : public EML2_NS::AbstractLocal3dCrs
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT LocalEngineeringCompoundCrs(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : EML2_NS::AbstractLocal3dCrs(partialObject) {}

		/**
		 * @brief	Creates a local depth 3d CRS which is fully identified by means of EPSG code.
		 *
		 * @exception	std::invalid_argument	If <tt>projectedEpsgCode == 0 || verticalEpsgCode ==
		 * 										0</tt>.
		 *
		 * @param [in,out]	repo			 	The repo where the underlying gsoap proxy is going to be
		 * 										created.
		 * @param 		  	guid			 	The guid to set to the local 3d crs. If empty then a new
		 * 										guid will be generated.
		 * @param 		  	title			 	A title for the instance to create.
		 * @param 		  	originOrdinal1   	The local CRS origin coordinate on the first axis of the projected CRS.
		 * @param 		  	originOrdinal2   	The local CRS origin coordinate on the second axis of the projected CRS.
		 * @param 		  	originOrdinal3   	The local CRS origin coordinate on the axis of the vertical CRS.
		 * @param 		  	arealRotation	 	The areal rotation in radians regarding the projected crs.
		 * @param 		  	projectedUom	 	The unit of measure of the projected axis of this
		 * 										instance.
		 * @param 		  	projectedEpsgCode	The epsg code of the associated projected CRS.
		 * @param 		  	verticalUom		 	The unit of measure of the vertical axis of this instance.
		 * @param 		  	verticalEpsgCode 	The epsg code of the associated vertical CRS.
		 * @param 		  	isUpOriented	 	If true, indicates that this local depth CRS is actually a
		 * 										local elevation CRS and that the associated vertical CRS is
		 *										an elevation one as well.
		 */
		LocalEngineeringCompoundCrs(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, uint64_t projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, uint64_t verticalEpsgCode, bool isUpOriented);

		/**
		 * Creates a local depth 3d CRS which is fully defined by a string representation.
		 *
		 * @param [in,out]	repo				  	The repo where the underlying gsoap proxy is going to
		 * 											be created.
		 * @param 		  	guid				  	The guid to set to the local 3d crs. If empty then a
		 * 											new guid will be generated.
		 * @param 		  	title				  	A title for the instance to create.
		 * @param 		  	originOrdinal1   		The local CRS origin coordinate on the first axis of the projected CRS.
		 * @param 		  	originOrdinal2   		The local CRS origin coordinate on the second axis of the projected CRS.
		 * @param 		  	originOrdinal3   		The local CRS origin coordinate on the axis of the vertical CRS.
		 * @param 		  	arealRotation		  	The areal rotation in radians regarding the projected
		 * 											crs.
		 * @param 		  	projectedUom		  	The unit of measure of the projected axis of this
		 * 											instance.
		 * @param		 	projectedDefinition		If starting with "PROJCRS" or "PROJCS" then it gives the WKT definition of the projected CRS.
		 *											Otherwise, it defines why this projected CRS should be considered as unknown.
		 * @param 		  	verticalUom			  	The unit of measure of the vertical axis of this
		 * 											instance.
		 * @param			verticalDefinition	 	If starting with "VERT" then it gives the WKT definition of the vertical CRS.
		 *											Otherwise, it defines why this vertical CRS should be considered as unknown.
		 * @param 		  	isUpOriented		  	If true, indicates that this local depth CRS is actually a
		 * 											local elevation CRS and that the associated vertical CRS is
		 *											an elevation one as well.
		 */
		LocalEngineeringCompoundCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string& projectedDefinition,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string& verticalDefinition, bool isUpOriented);

		/**
		 * @brief	Creates a local depth 3d CRS which is identified by an EPSG code for its projected
		 * 			part and which is defined by a string representation for its vertical part.
		 *
		 * @exception	std::invalid_argument	If <tt>projectedEpsgCode == 0</tt>.
		 *
		 * @param [in,out]	repo				 	The repo where the underlying gsoap proxy is going to
		 * 											be created.
		 * @param 		  	guid				 	The guid to set to the local 3d crs. If empty then a
		 * 											new guid will be generated.
		 * @param 		  	title				 	A title for the instance to create.
		 * @param 		  	originOrdinal1			The local CRS origin coordinate on the first axis of the projected CRS.
		 * @param 		  	originOrdinal2			The local CRS origin coordinate on the second axis of the projected CRS.
		 * @param 		  	originOrdinal3			The local CRS origin coordinate on the axis of the vertical CRS.
		 * @param 		  	arealRotation		 	The areal rotation in radians regarding the projected
		 * 											crs.
		 * @param 		  	projectedUom		 	The unit of measure of the projected axis of this
		 * 											instance.
		 * @param 		  	projectedEpsgCode	 	The epsg code of the associated projected CRS.
		 * @param 		  	verticalUom			 	The unit of measure of the vertical axis of this
		 * 											instance.
		 * @param			verticalDefinition	 	If starting with "VERT" then it gives the WKT definition of the vertical CRS.
		 *											Otherwise, it defines why this vertical CRS should be considered as unknown.
		 * @param 		  	isUpOriented		 	If true, indicates that this local depth CRS is actually a
		 * 											local elevation CRS and that the associated vertical CRS is
		 *											an elevation one as well.
		 */
		LocalEngineeringCompoundCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, uint64_t projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string& verticalDefinition, bool isUpOriented);

		/**
		 * @brief	Creates a local depth 3d CRS which is defined by a string representation for its projected part and which is
		 * 			identified by an EPSG code for its vertical part.
		 *
		 * @exception	std::invalid_argument	If <tt>verticalEpsgCode == 0</tt>.
		 *
		 * @param [in]	repo				  	The repo where the underlying gsoap proxy is going to
		 * 										be created.
		 * @param 	  	guid				  	The guid to set to the local 3d crs. If empty then a new
		 * 										guid will be generated.
		 * @param 	  	title				  	A title for the instance to create.
		 * @param 		originOrdinal1   		The local CRS origin coordinate on the first axis of the projected CRS.
		 * @param 		originOrdinal2   		The local CRS origin coordinate on the second axis of the projected CRS.
		 * @param 		originOrdinal3			The local CRS origin coordinate on the axis of the vertical CRS.
		 * @param 	  	arealRotation		  	The areal rotation in radians regarding the projected crs.
		 * @param 	  	projectedUom		  	The unit of measure of the projected axis of this
		 * 										instance.
		 * @param	 	projectedDefinition		If starting with "PROJCRS" or "PROJCS" then it gives the WKT definition of the projected CRS.
		 *										Otherwise, it defines why this projected CRS should be considered as unknown.
		 * @param 	  	verticalUom			  	The unit of measure of the vertical axis of this instance.
		 * @param 	  	verticalEpsgCode	  	The epsg code of the associated vertical CRS.
		 * @param 	  	isUpOriented		  	If true, indicates that this local depth CRS is actually a
		 * 										local elevation CRS and that the associated vertical CRS is
		 *										an elevation one as well.
		 */
		LocalEngineeringCompoundCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string& projectedDefinition,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, uint64_t verticalEpsgCode, bool isUpOriented);

		/**
		 * @brief	Creates a local time 3d CRS which is fully identified by means of EPSG code.
		 *
		 * @exception	std::invalid_argument	If <tt>projectedEpsgCode == 0 || verticalEpsgCode ==
		 * 										0</tt>.
		 *
		 * @param [in]	repo			 	The repo where the underlying gsoap proxy is going to be
		 * 									created.
		 * @param 	  	guid			 	The guid to set to the local 3d crs. If empty then a new guid
		 * 									will be generated.
		 * @param 	  	title			 	A title for the instance to create.
		 * @param 		originOrdinal1   	The local CRS origin coordinate on the first axis of the projected CRS.
		 * @param 		originOrdinal2   	The local CRS origin coordinate on the second axis of the projected CRS.
		 * @param 		originOrdinal3   	The local CRS origin coordinate on the axis of the vertical CRS.
		 *									It generally represents the Seismic Reference Datum.
		 * @param 	  	arealRotation	 	The areal rotation in radians regarding the projected crs.
		 * @param 	  	projectedUom	 	The unit of measure of the projected axis of this instance.
		 * @param 	  	projectedEpsgCode	The EPSG code of the associated projected CRS.
		 * @param 	  	timeUom			 	The unit of measure of the Z offset of this instance.
		 * @param 	  	verticalUom		 	The unit of measure of the vertical axis of this instance.
		 * @param 	  	verticalEpsgCode 	The EPSG code of the associated vertical CRS.
		 * @param 	  	isUpOriented	 	Indicates if the axis of the associated vertical CRS is up oriented or not.
		 *									It is important to rightly place @p originOrdinal3 in the space.
		 */
		LocalEngineeringCompoundCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, uint64_t projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, uint64_t verticalEpsgCode, bool isUpOriented);

		/**
		 * Creates a local time 3d CRS which is fully defined by a string representation.
		 *
		 * @param [in,out]	repo				  	The repo where the underlying gsoap proxy is going to
		 * 											be created.
		 * @param 		  	guid				  	The guid to set to the local 3d crs. If empty then a
		 * 											new guid will be generated.
		 * @param 		  	title				  	A title for the instance to create.
		 * @param 		  	originOrdinal1   		The local CRS origin coordinate on the first axis of the projected CRS.
		 * @param 		  	originOrdinal2   		The local CRS origin coordinate on the second axis of the projected CRS.
		 * @param 		  	originOrdinal3   		The local CRS origin coordinate on the axis of the vertical CRS.
		 *											It generally represents the Seismic Reference Datum.
		 * @param 		  	arealRotation		  	The areal rotation in radians regarding the projected
		 * 											crs.
		 * @param 		  	projectedUom		  	The unit of measure of the projected axis of this
		 * 											instance.
		 * @param 			projectedDefinition		If starting with "PROJCRS" or "PROJCS" then it gives the WKT definition of the projected CRS.
		 *											Otherwise, it defines why this projected CRS should be considered as unknown.
		 * @param 		  	timeUom				  	The unit of measure of the Z offset of this instance.
		 * @param 		  	verticalUom			  	The unit of measure of the vertical axis of this
		 * 											instance.
		 * @param		 	verticalDefinition	 	If starting with "VERT" then it gives the WKT definition of the vertical CRS.
		 *											Otherwise, it defines why this vertical CRS should be considered as unknown.
		 * @param 	  		isUpOriented	 		Indicates if the axis of the associated vertical CRS is up oriented or not.
		 *											It is important to rightly place @p originOrdinal3 in the space.
		 */
		LocalEngineeringCompoundCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string& projectedDefinition,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string& verticalDefinition, bool isUpOriented);

		/**
		 * @brief	Creates a local depth 3d CRS which is identified by an EPSG code for its projected
		 * 			part and which is defined by a string representation for its vertical part.
		 *
		 * @exception	std::invalid_argument	If <tt>projectedEpsgCode == 0</tt>.
		 *
		 * @param [in]	repo				 	The repo where the underlying gsoap proxy is going to
		 * 										be created.
		 * @param 	  	guid				 	The guid to set to the local 3d crs. If empty then a new
		 * 										guid will be generated.
		 * @param 	  	title				 	A title for the instance to create.
		 * @param 		originOrdinal1   		The local CRS origin coordinate on the first axis of the projected CRS.
		 * @param 		originOrdinal2   		The local CRS origin coordinate on the second axis of the projected CRS.
		 * @param 		originOrdinal3   		The local CRS origin coordinate on the axis of the vertical CRS.
		 *										It generally represents the Seismic Reference Datum.
		 * @param 	  	arealRotation		 	The areal rotation in radians regarding the projected crs.
		 * @param 	  	projectedUom		 	The unit of measure of the projected axis of this
		 * 										instance.
		 * @param 	  	projectedEpsgCode	 	The EPSG code of the associated projected CRS.
		 * @param 	  	timeUom				 	The unit of measure of the Z offset of this instance.
		 * @param 	  	verticalUom			 	The unit of measure of the vertical axis of this instance.
		 * @param	 	verticalDefinition	 	If starting with "VERT" then it gives the WKT definition of the vertical CRS.
		 *										Otherwise, it defines why this vertical CRS should be considered as unknown.
		 * @param 	  	isUpOriented	 		Indicates if the axis of the associated vertical CRS is up oriented or not.
		 *										It is important to rightly place @p originOrdinal3 in the space.
		 */
		LocalEngineeringCompoundCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, uint64_t projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string& verticalDefinition, bool isUpOriented);

		/**
		 * @brief	Creates a local time 3d CRS which is defined by a string representation for its projected part and which is
		 * 			identified by an EPSG code for its vertical part.
		 *
		 * @exception	std::invalid_argument	If <tt>verticalEpsgCode == 0</tt>.
		 *
		 * @param [in]	repo				  	The repo where the underlying gsoap proxy is going to
		 * 											be created.
		 * @param 	  	guid				  	The guid to set to the local 3d crs. If empty then a new
		 * 										guid will be generated.
		 * @param 	  	title				  	A title for the instance to create.
		 * @param 		originOrdinal1   		The local CRS origin coordinate on the first axis of the projected CRS.
		 * @param 		originOrdinal2   		The local CRS origin coordinate on the second axis of the projected CRS.
		 * @param 		originOrdinal3   		The local CRS origin coordinate on the axis of the vertical CRS.
		 *										It generally represents the Seismic Reference Datum.
		 * @param 	  	arealRotation		  	The areal rotation in radians regarding the projected crs.
		 * @param 	  	projectedUom		  	The unit of measure of the projected axis of this
		 * 										instance.
		 * @param 		projectedDefinition		If starting with "PROJCRS" or "PROJCS" then it gives the WKT definition of the projected CRS.
		 *										Otherwise, it defines why this projected CRS should be considered as unknown.
		 * @param 	  	timeUom				  	The unit of measure of the Z offset of this instance.
		 * @param 	  	verticalUom			  	The unit of measure of the vertical axis of this instance.
		 * @param 	  	verticalEpsgCode	  	The EPSG code of the associated vertical CRS.
		 * @param 	  	isUpOriented	 		Indicates if the axis of the associated vertical CRS is up oriented or not.
		 *										It is important to rightly place @p originOrdinal3 in the space.
		 */
		LocalEngineeringCompoundCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string& projectedDefinition,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, uint64_t verticalEpsgCode, bool isUpOriented);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		LocalEngineeringCompoundCrs(gsoap_eml2_3::_eml23__LocalEngineeringCompoundCrs* fromGsoap): EML2_NS::AbstractLocal3dCrs(fromGsoap) {}

		/** Destructor does nothing since the memory is manged by the gsoap context. */
		~LocalEngineeringCompoundCrs() = default;

		DLL_IMPORT_OR_EXPORT bool isATimeCrs() const final { return static_cast<gsoap_eml2_3::_eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->VerticalAxis->IsTime; }

		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::eml20__TimeUom getTimeUom() const final;

		DLL_IMPORT_OR_EXPORT LocalEngineering2dCrs* getLocalEngineering2dCrs() const;

		DLL_IMPORT_OR_EXPORT VerticalCrs* getVerticalCrs() const;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "eml23";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "LocalEngineeringCompoundCrs";

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

		/** Loads target relationships */
		void loadTargetRelationships() final;

	private:

		/**
		 * Initializes this object
		 *
		 * @param [in,out]	repo		  			If non-null, the repo.
		 * @param 		  	guid		  			Unique identifier.
		 * @param 		  	title		  			The title.
		 * @param 		  	projectedEpsgCode		The EPSG code of the associated projected CRS. Ignored if @p unknownProjectedReason is not empty.
		 * @param 		  	unknownProjectedReason	The reason why the projected CRS is unkown.
		 * @param 		  	originOrdinal1			The first origin ordinal.
		 * @param 		  	originOrdinal2			The second origin ordinal.
		 * @param 		  	projectedUom  			The projected uom.
		 * @param 		  	azimuth		 			The areal rotation regarding the north.
		 * @param 		  	azimuthUom				The unit of measure of the @p azimuth.
		 * @param 		  	azimuthReference		The kind of north reference of the @p azimuth.
		 * @param			axisOrder				The axis order of the projected CRS.
		 * @param 		  	verticalEpsgCode		The EPSG code of the associated vertical CRS. Ignored if @p unknwownVerticalReason is not empty.
		 * @param 		  	unknwownVerticalReason	The reason why the vertical CRS is unkown.
		 * @param 		  	originOrdinal3			The third origin ordinal.
		 * @param 		  	verticalUom				The vertical uom.
		 * @param 		  	isUpOriented  			True if is up oriented, false if not.
		 */
		void init(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			uint64_t projectedEpsgCode, std::string unknownProjectedReason,
			double originOrdinal1, double originOrdinal2, gsoap_resqml2_0_1::eml20__LengthUom projectedUom,
			double azimuth, gsoap_eml2_3::eml23__PlaneAngleUom azimuthUom, gsoap_eml2_3::eml23__NorthReferenceKind azimuthReference,
			gsoap_eml2_3::eml23__AxisOrder2d axisOrder,
			uint64_t verticalEpsgCode, std::string unknwownVerticalReason,
			double originOrdinal3,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, bool isUpOriented);

		/**
		 * Initializes this object
		 *
		 * @param [in,out]	repo		  			If non-null, the repo.
		 * @param 		  	guid		  			Unique identifier.
		 * @param 		  	title		  			The title.
		 * @param 		  	projectedEpsgCode		The EPSG code of the associated projected CRS. Ignored if @p unknownProjectedReason is not empty.
		 * @param 		  	unknownProjectedReason	The reason why the projected CRS is unkown.
		 * @param 		  	originOrdinal1			The first origin ordinal.
		 * @param 		  	originOrdinal2			The second origin ordinal.
		 * @param 		  	projectedUom  			The projected uom.
		 * @param 		  	azimuth		 			The areal rotation regarding the north.
		 * @param 		  	azimuthUom				The unit of measure of the @p azimuth.
		 * @param 		  	azimuthReference		The kind of north reference of the @p azimuth.
		 * @param			axisOrder				The axis order of the projected CRS.
		 * @param 		  	verticalEpsgCode		The EPSG code of the associated vertical CRS. Ignored if @p unknwownVerticalReason is not empty.
		 * @param 		  	unknwownVerticalReason	The reason why the vertical CRS is unkown.
		 * @param 		  	originOrdinal3			The third origin ordinal.
		 * @param 		  	verticalUom				The vertical uom.
		 * @param 		  	isUpOriented  			True if is up oriented, false if not.
		 */
		void init(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			uint64_t projectedEpsgCode, std::string unknownProjectedReason,
			double originOrdinal1, double originOrdinal2, gsoap_resqml2_0_1::eml20__LengthUom projectedUom,
			double azimuth, gsoap_eml2_3::eml23__PlaneAngleUom azimuthUom, gsoap_eml2_3::eml23__NorthReferenceKind azimuthReference,
			gsoap_eml2_3::eml23__AxisOrder2d axisOrder,
			uint64_t verticalEpsgCode, std::string unknwownVerticalReason,
			double originOrdinal3,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom, bool isUpOriented);

		/**
		 * Get z coordinate offset
		 *
		 * @returns	The z coordinate offset.
		 */
		double getZOffset() const { return isATimeCrs() ? .0 : getOriginDepthOrElevation(); }
	};
}
