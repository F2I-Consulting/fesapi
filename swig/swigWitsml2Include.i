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
%{
#include "../src/witsml2/Trajectory.h"
#include "../src/witsml2/Well.h"
#include "../src/witsml2/Wellbore.h"
#include "../src/witsml2/WellboreObject.h"
%}

#define GETTER_AND_SETTER_GENERIC_ATTRIBUTE(attributeDatatype, attributeName)\
	void set##attributeName(const attributeDatatype & value);\
	attributeDatatype get##attributeName() const;
#define GETTER_PRESENCE_ATTRIBUTE(attributeName) bool has##attributeName() const;
#define GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(attributeDatatype, attributeName)\
	GETTER_AND_SETTER_GENERIC_ATTRIBUTE(attributeDatatype, attributeName)\
	GETTER_PRESENCE_ATTRIBUTE(attributeName)

#define GETTER_AND_SETTER_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	void set##attributeName(double value, uomDatatype uom);\
	double get##attributeName##Value() const;\
	uomDatatype get##attributeName##Uom() const;
#define GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(attributeName, uomDatatype)\
	GETTER_AND_SETTER_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	GETTER_PRESENCE_ATTRIBUTE(attributeName)

#define GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	void set##attributeName(double value, uomDatatype uom);\
	double get##attributeName##Value() const;\
	uomDatatype get##attributeName##Uom() const;
#define GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(attributeName, uomDatatype)\
	GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	GETTER_PRESENCE_ATTRIBUTE(attributeName)

#define GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	void set##vectorName##attributeName(uint64_t index, const attributeDatatype & value);\
	attributeDatatype get##vectorName##attributeName(uint64_t index) const;	
	
#define GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	void set##vectorName##attributeName(uint64_t index, double value, uomDatatype uom);\
	double get##vectorName##attributeName##Value(uint64_t index) const;\
	uomDatatype get##vectorName##attributeName##Uom(uint64_t index) const;

#define GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName) bool has##vectorName##attributeName(uint64_t index) const;	
#define GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)	
	
#define GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)
	
#define GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	void set##vectorName##attributeName(uint64_t index, double value, uomDatatype uom);\
	double get##vectorName##attributeName##Value(uint64_t index) const;\
	uomDatatype get##vectorName##attributeName##Uom(uint64_t index) const;
#define GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)

namespace gsoap_eml2_3
{
enum class eml23__WellStatus {
	abandoned = 0,
	active = 1,
	active_x0020_x002d__x0020injecting = 2,
	active_x0020_x002d__x0020producing = 3,
	completed = 4,
	drilling = 5,
	partially_x0020plugged = 6,
	permitted = 7,
	plugged_x0020and_x0020abandoned = 8,
	proposed = 9,
	sold = 10,
	suspended = 11,
	temporarily_x0020abandoned = 12,
	testing = 13,
	tight = 14,
	working_x0020over = 15,
	unknown = 16
};
enum class witsml21__WellPurpose {
	appraisal = 0,
	appraisal_x0020_x002d__x0020confirmation_x0020appraisal = 1,
	appraisal_x0020_x002d__x0020exploratory_x0020appraisal = 2,
	exploration = 3,
	exploration_x0020_x002d__x0020deeper_pool_x0020wildcat = 4,
	exploration_x0020_x002d__x0020new_field_x0020wildcat = 5,
	exploration_x0020_x002d__x0020new_pool_x0020wildcat = 6,
	exploration_x0020_x002d__x0020outpost_x0020wildcat = 7,
	exploration_x0020_x002d__x0020shallower_pool_x0020wildcat = 8,
	development = 9,
	development_x0020_x002d__x0020infill_x0020development = 10,
	development_x0020_x002d__x0020injector = 11,
	development_x0020_x002d__x0020producer = 12,
	fluid_x0020storage = 13,
	fluid_x0020storage_x0020_x002d__x0020gas_x0020storage = 14,
	general_x0020srvc = 15,
	general_x0020srvc_x0020_x002d__x0020borehole_x0020re_acquisition = 16,
	general_x0020srvc_x0020_x002d__x0020observation = 17,
	general_x0020srvc_x0020_x002d__x0020relief = 18,
	general_x0020srvc_x0020_x002d__x0020research = 19,
	general_x0020srvc_x0020_x002d__x0020research_x0020_x002d__x0020drill_x0020test = 20,
	general_x0020srvc_x0020_x002d__x0020research_x0020_x002d__x0020strat_x0020test = 21,
	general_x0020srvc_x0020_x002d__x0020waste_x0020disposal = 22,
	mineral = 23
};
enum class witsml21__WellFluid {
	air = 0,
	condensate = 1,
	dry = 2,
	gas = 3,
	gas_water = 4,
	non_x0020HC_x0020gas = 5,
	non_x0020HC_x0020gas_x0020_x002d__x0020CO2 = 6,
	oil = 7,
	oil_gas = 8,
	oil_water = 9,
	steam = 10,
	water = 11,
	water_x0020_x002d__x0020brine = 12,
	water_x0020_x002d__x0020fresh_x0020water = 13
};
enum class witsml21__WellDirection {
	huff_n_puff = 0,
	injector = 1,
	producer = 2,
	uncertain = 3
};
enum class eml23__ReferencePointKind {
	casing_x0020flange = 0,
	crown_x0020valve = 1,
	derrick_x0020floor = 2,
	ground_x0020level = 3,
	kelly_x0020bushing = 4,
	kickoff_x0020point = 5,
	lowest_x0020astronomical_x0020tide = 6,
	mean_x0020high_x0020water = 7,
	mean_x0020higher_x0020high_x0020water = 8,
	mean_x0020low_x0020water = 9,
	mean_x0020lower_x0020low_x0020water = 10,
	mean_x0020sea_x0020level = 11,
	mean_x0020tide_x0020level = 12,
	rotary_x0020bushing = 13,
	rotary_x0020table = 14,
	seafloor = 15,
	wellhead = 16,
	well_x0020surface_x0020location = 17
};
enum class eml23__NorthReferenceKind {
	astronomic_x0020north = 0,
	compass_x0020north = 1,
	grid_x0020north = 2,
	magnetic_x0020north = 3,
	plant_x0020north = 4,
	true_x0020north = 5
};
enum class witsml21__WellboreType {
	bypass = 0,
	initial = 1,
	redrill = 2,
	reentry = 3,
	respud = 4,
	sidetrack = 5
};
enum class witsml21__WellboreShape {
	build_x0020and_x0020hold = 0,
	deviated = 1,
	double_x0020kickoff = 2,
	horizontal = 3,
	S_shaped = 4,
	vertical = 5
};
enum class witsml21__PhysicalStatus {
	closed = 0,
	open = 1,
	proposed = 2
};
enum class witsml21__TrajStationType {
	azimuth_x0020on_x0020plane = 0,
	buildrate_x0020to_x0020delta_MD = 1,
	buildrate_x0020to_x0020INCL = 2,
	buildrate_x0020to_x0020MD = 3,
	buildrate_x0020and_x0020turnrate_x0020to_x0020AZI = 4,
	buildrate_x0020and_x0020turnrate_x0020to_x0020delta_MD = 5,
	buildrate_x0020and_x0020turnrate_x0020to_x0020INCL = 6,
	buildrate_x0020and_x0020turnrate_x0020to_x0020INCL_x0020and_x0020AZI = 7,
	buildrate_x0020and_x0020turnrate_x0020to_x0020MD = 8,
	buildrate_x0020and_x0020turnrate_x0020to_x0020TVD = 9,
	buildrate_x0020TVD = 10,
	casing_x0020MD = 11,
	casing_x0020TVD = 12,
	DLS = 13,
	DLS_x0020to_x0020AZI_x0020and_x0020MD = 14,
	DLS_x0020to_x0020AZI_TVD = 15,
	DLS_x0020to_x0020INCL = 16,
	DLS_x0020to_x0020INCL_x0020and_x0020AZI = 17,
	DLS_x0020to_x0020INCL_x0020and_x0020MD = 18,
	DLS_x0020to_x0020INCL_x0020and_x0020TVD = 19,
	DLS_x0020to_x0020NS = 20,
	DLS_x0020and_x0020toolface_x0020to_x0020AZI = 21,
	DLS_x0020and_x0020toolface_x0020to_x0020delta_MD = 22,
	DLS_x0020and_x0020toolface_x0020to_x0020INCL = 23,
	DLS_x0020and_x0020toolface_x0020to_x0020INCL_AZI = 24,
	DLS_x0020and_x0020toolface_x0020to_x0020MD = 25,
	DLS_x0020and_x0020toolface_x0020to_x0020TVD = 26,
	extrapolated = 27,
	formation_x0020MD = 28,
	formation_x0020TVD = 29,
	hold_x0020to_x0020delta_MD = 30,
	hold_x0020to_x0020MD = 31,
	hold_x0020to_x0020TVD = 32,
	INCL_x0020AZI_x0020and_x0020TVD = 33,
	interpolated = 34,
	marker_x0020MD = 35,
	marker_x0020TVD = 36,
	MD_x0020and_x0020INCL = 37,
	MD_x0020INCL_x0020and_x0020AZI = 38,
	N_x0020E_x0020and_x0020TVD = 39,
	NS_x0020EW_x0020and_x0020TVD = 40,
	target_x0020center = 41,
	target_x0020offset = 42,
	tie_x0020in_x0020point = 43,
	turnrate_x0020to_x0020AZI = 44,
	turnrate_x0020to_x0020delta_MD = 45,
	turnrate_x0020to_x0020MD = 46,
	turnrate_x0020to_x0020TVD = 47,
	unknown = 48
};
enum class witsml21__TypeSurveyTool {
	gyroscopic_x0020inertial = 0,
	gyroscopic_x0020MWD = 1,
	gyroscopic_x0020north_x0020seeking = 2,
	magnetic_x0020multiple_shot = 3,
	magnetic_x0020MWD = 4,
	magnetic_x0020single_shot = 5
};
enum class witsml21__TrajStnCalcAlgorithm {
	average_x0020angle = 0,
	balanced_x0020tangential = 1,
	constant_x0020tool_x0020face = 2,
	custom = 3,
	inertial = 4,
	minimum_x0020curvature = 5,
	radius_x0020of_x0020curvature = 6,
	tangential = 7
};
enum class witsml21__TrajStationStatus {
	open = 0,
	rejected = 1,
	position = 2
};
enum class witsml21__HoleCasingType {
	blow_x0020out_x0020preventer = 0,
	casing = 1,
	conductor = 2,
	curved_x0020conductor = 3,
	liner = 4,
	open_x0020hole = 5,
	riser = 6,
	tubing = 7
};
enum class witsml21__ChannelDataKind {
	boolean = 0,
	bytes = 1,
	double_ = 2,
	float_ = 3,
	int_ = 4,
	long_ = 5,
	string = 6,
	measured_x0020depth = 7,
	true_x0020vertical_x0020depth = 8,
	pass_x0020indexed_x0020depth = 9,
	date_x0020time = 10,
	elapsed_x0020time = 11
};
}

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace WITSML2_NS::Trajectory;	
	%nspace WITSML2_NS::Well;
	%nspace WITSML2_NS::Wellbore;
	%nspace WITSML2_NS::WellboreObject;
#endif

namespace WITSML2_NS
{
	%nodefaultctor; // Disable creation of default constructors
	
	/** 
	 * @brief	Contains all information that is the same for all wellbores (sidetracks). 
	 */
#if defined(SWIGPYTHON)
	%rename(Witsml2_Well) Well;
#endif
	/** 
	 * @brief	Contains all information that is the same for all wellbores (sidetracks). 
	 */
	class Well : public COMMON_NS::AbstractObject
	{
	public:
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NameLegal)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NumLicense)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NumGovt)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Field)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Country)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, State)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, County)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Region)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, District)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Block)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, OperatorDiv)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NumAPI)

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::eml23__WellStatus, StatusWell)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::witsml21__WellPurpose, PurposeWell)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::witsml21__WellFluid, FluidWell)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::witsml21__WellDirection, DirectionWell)

		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(WaterDepth, gsoap_eml2_3::eml23__LengthUom)
		GETTER_PRESENCE_ATTRIBUTE(GroundElevation)

		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(PcInterest, gsoap_eml2_3::eml23__DimensionlessUom)

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimLicense)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimSpud)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimPa)

		/**
		* @brief	Sets the ground level elevation (land rigs)
		*
		* @exception	std::invalid_argument	If @p value is undefined.
		*
		* @param 	value		The elevation value.
		* @param 	uom  		The elevation unit of measure.
		* @param	verticalCrs	The vertical CRS which is used as the datum for the ground elevation
		*/
		virtual void setGroundElevation(double value, gsoap_eml2_3::eml23__LengthUom uom, EML2_3_NS::VerticalCrs* verticalCrs) = 0;

		/**
		 * @brief	Gets the ground level elevation value
		 *
		 * @exception	std::invalid_argument	If the ground elevation does not exist.
		 *
		 * @returns	The ground level elevation value.
		 */
		virtual double getGroundElevationValue() const = 0;

		/**
		 * @brief	Gets the ground level elevation unit of measure
		 *
		 * @exception	std::invalid_argument	If the ground elevation does not exist.
		 *
		 * @returns	The ground level elevation unit of measure.
		 */
		virtual gsoap_eml2_3::eml23__LengthUom getGroundElevationUom() const = 0;

		/**
		 * Gets the vertical CRS which acts as the datum of this ground elevation.
		 *
		 * @returns	The vertical CRS which acts as the datum of this ground elevation..
		 */
		EML2_3_NS::VerticalCrs* getGroundElevationDatum() const;

		/**
		* @brief	Sets the well head elevation
		*
		* @exception	std::invalid_argument	If @p value is undefined.
		*
		* @param 	value		The elevation value.
		* @param 	uom  		The elevation unit of measure.
		* @param	verticalCrs	The vertical CRS which is used as the datum for the well head elevation
		*/
		virtual void setWellheadElevation(double value, gsoap_eml2_3::eml23__LengthUom uom, EML2_3_NS::VerticalCrs* verticalCrs) = 0;

		/**
		 * @brief	Gets the well head elevation value
		 *
		 * @exception	std::invalid_argument	If the well head elevation does not exist.
		 *
		 * @returns	The well head elevation value.
		 */
		virtual double getWellheadElevationValue() const = 0;

		/**
		 * @brief	Gets the well head elevation unit of measure
		 *
		 * @exception	std::invalid_argument	If the well head elevation does not exist.
		 *
		 * @returns	The well head elevation unit of measure.
		 */
		virtual gsoap_eml2_3::eml23__LengthUom getWellheadElevationUom() const = 0;

		/**
		 * Gets the vertical CRS which acts as the datum of this well head elevation.
		 *
		 * @returns	The vertical CRS which acts as the datum of this well head elevation..
		 */
		EML2_3_NS::VerticalCrs* getWellheadElevationDatum() const;

		/**
		* Set the time zone in which the well is located.It is the deviation in hours and minutes from
		* UTC.This should be the normal time zone at the well and not a seasonally-adjusted value,
		* such as daylight savings time
		*
		* @param 	direction	True means the time zone is a positive offset from UTC, false means the
		* 						time zone is a negative offset from UTC.
		* @param 	hours	 	The deviation hours from UTC.
		* @param 	minutes		The deviation minutes from UTC.
		*/
		void setTimeZone(bool direction, unsigned short hours, unsigned short minutes);
		GETTER_PRESENCE_ATTRIBUTE(TimeZone)

		/**
			* Get the time zone direction in which the well is located.
			*
			* @returns	True means the time zone is a positive offset from UTC, false means the time zone is
			* 			a negative offset from UTC. If the time zone is Z then an arbitrary '+' is returned.
			*/
		bool getTimeZoneDirection() const;

		/**
		 * Get the time zone hour(s) in which the well is located. Must be used with
		 * getTimeZoneDirection and getTimeZoneMinute() to have the complete time zone.
		 *
		 * @returns	the deviation hour(s) from UTC.
		 */
		unsigned short getTimeZoneHours() const;

		/**
		 * Get the time zone minute(s) in which the well is located. Must be used with
		 * getTimeZoneDirection and getTimeZoneHour() to have the complete time zone.
		 *
		 * @returns	the deviation minute(s) from UTC.
		 */
		unsigned short getTimeZoneMinutes() const;
		
		/**
			* Gets location projected x coordinate
			*
			* @param 	locationIndex	Zero-based index of the location.
			*
			* @returns	The location projected x coordinate.
			*/
		double getLocationProjectedX(uint64_t locationIndex);

		/**
		 * Gets location projected y coordinate
		 *
		 * @param 	locationIndex	Zero-based index of the location.
		 *
		 * @returns	The location projected y coordinate.
		 */
		double getLocationProjectedY(uint64_t locationIndex);

		/**
		 * Pushes a back location
		 *
		 * @param 	projectedX		The projected x coordinate.
		 * @param 	projectedY		The projected y coordinate.
		 * @param 	crs				The CRS of the X and Y coordinates.
		 */
		void pushBackLocation(double projectedX, double projectedY, EML2_3_NS::LocalEngineering2dCrs* crs);

		/**
		 * Get location count
		 *
		 * @returns	An int.
		 */
		uint64_t geLocationCount() const;
		
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::WellboreFeature, ResqmlWellboreFeature)
		SWIG_GETTER_DATAOBJECTS(WITSML2_NS::Wellbore, Wellbore)
		SWIG_GETTER_DATAOBJECTS(WITSML2_1_NS::WellCompletion, Wellcompletion)
	};

#if defined(SWIGPYTHON)
	%rename(Witsml2_Wellbore) Wellbore;
#endif
	/** 
	 * @brief	A wellbore represents the path from surface to a unique bottomhole location.
	 */
	class Wellbore : public COMMON_NS::AbstractObject
	{
	public:
		Well* getWell() const;
		void setWell(Well* witsmlWell);

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Number);
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, SuffixAPI);
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NumGovt);
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::eml23__WellStatus, StatusWellbore);
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::witsml21__WellPurpose, PurposeWellbore);
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::witsml21__WellboreType, TypeWellbore);
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::witsml21__WellboreShape, Shape);
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::witsml21__WellFluid, FluidWellbore)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, AchievedTD);
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(Md, gsoap_eml2_3::eml23__LengthUom);
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdBit, gsoap_eml2_3::eml23__LengthUom);
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdKickoff, gsoap_eml2_3::eml23__LengthUom);
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdPlanned, gsoap_eml2_3::eml23__LengthUom);
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdSubSeaPlanned, gsoap_eml2_3::eml23__LengthUom);
		
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::WellboreFeature, ResqmlWellboreFeature)
		
		SWIG_GETTER_DATAOBJECTS(WITSML2_NS::Trajectory, Trajectory)
		SWIG_GETTER_DATAOBJECTS(WITSML2_1_NS::WellboreCompletion, WellboreCompletion)
		SWIG_GETTER_DATAOBJECTS(WITSML2_1_NS::WellboreGeometry, WellboreGeometry)
		SWIG_GETTER_DATAOBJECTS(WITSML2_1_NS::Log, Log)
	};
	
#if defined(SWIGPYTHON)
	%rename(Witsml2_WellboreObject) WellboreObject;
#endif
	/**
	 * The class is the super class for all wellbore objects (all top level objects pointing to
	 * Wellbore)
	 */
	class WellboreObject : public COMMON_NS::AbstractObject
	{
	public:
		Wellbore* getWellbore() const;
		void setWellbore(Wellbore* witsmlWellbore) = 0;
	};
	
#if defined(SWIGPYTHON)
	%rename(Witsml2_Trajectory) Trajectory;
#endif
	/** 
	 * @brief	It contains many trajectory stations to capture the information about individual survey points.
	 */
	class Trajectory : public WellboreObject
	{
	public:
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimTrajStart)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimTrajEnd)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::eml23__NorthReferenceKind, AziRef)

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, Definitive)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, Memory)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, FinalTraj)

		//***************************************/
		// ******* TRAJECTORY STATIONS **********/
		//***************************************/

		// Mandatory
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(std::string, TrajectoryStation, uid)
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(gsoap_eml2_3::witsml21__TrajStationType, TrajectoryStation, TypeTrajStation)
		GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Md, gsoap_eml2_3::eml23__LengthUom)
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(time_t, TrajectoryStation, Creation)
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(time_t, TrajectoryStation, LastUpdate)

		// Optional bool
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, ManuallyEntered)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, GravAccelCorUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, MagXAxialCorUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, SagCorUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, MagDrlstrCorUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, InfieldRefCorUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, InterpolatedInfieldRefCorUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, InHoleRefCorUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, AxialMagInterferenceCorUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, CosagCorUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, MSACorUsed)

		// Optional string
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(std::string, TrajectoryStation, MagModelUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(std::string, TrajectoryStation, MagModelValid)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(std::string, TrajectoryStation, GeoModelUsed)

		// Optional timestamp
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(time_t, TrajectoryStation, DTimStn)

		// Optional enum
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_3::witsml21__TypeSurveyTool, TrajectoryStation, TypeSurveyTool)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_3::witsml21__TrajStnCalcAlgorithm, TrajectoryStation, CalcAlgorithm)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_3::witsml21__TrajStationStatus, TrajectoryStation, StatusTrajStation)

		// Optional Length Measure
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Tvd, gsoap_eml2_3::eml23__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, DispNs, gsoap_eml2_3::eml23__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, DispEw, gsoap_eml2_3::eml23__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, VertSect, gsoap_eml2_3::eml23__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, MdDelta, gsoap_eml2_3::eml23__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, TvdDelta, gsoap_eml2_3::eml23__LengthUom)

		// Optional Plane Angle Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Incl, gsoap_eml2_3::eml23__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Azi, gsoap_eml2_3::eml23__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Mtf, gsoap_eml2_3::eml23__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Gtf, gsoap_eml2_3::eml23__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, DipAngleUncert, gsoap_eml2_3::eml23__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, MagDipAngleReference, gsoap_eml2_3::eml23__PlaneAngleUom)

		// Optional Angle per Length Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Dls, gsoap_eml2_3::eml23__AnglePerLengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, RateTurn, gsoap_eml2_3::eml23__AnglePerLengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, RateBuild, gsoap_eml2_3::eml23__AnglePerLengthUom)

		// Optional Linear Acceleration Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, GravTotalUncert, gsoap_eml2_3::eml23__LinearAccelerationUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, GravTotalFieldReference, gsoap_eml2_3::eml23__LinearAccelerationUom)

		// Optional Magnetic Flux Density Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, MagTotalUncert, gsoap_eml2_3::eml23__MagneticFluxDensityUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, MagTotalFieldReference, gsoap_eml2_3::eml23__MagneticFluxDensityUom)

		void pushBackTrajectoryStation(gsoap_eml2_3::witsml21__TrajStationType kind, double mdValue, gsoap_eml2_3::eml23__LengthUom uom, const std::string & uid = "");
		unsigned int getTrajectoryStationCount() const;
	};
}

%include "swigWitsml2_1Include.i"
