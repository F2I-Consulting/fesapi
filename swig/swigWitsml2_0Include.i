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
#include "../src/witsml2_0/Well.h"
#include "../src/witsml2_0/WellCompletion.h"
#include "../src/witsml2_0/Wellbore.h"
#include "../src/witsml2_0/WellboreObject.h"
#include "../src/witsml2_0/WellboreCompletion.h"
#include "../src/witsml2_0/WellboreGeometry.h"
#include "../src/witsml2_0/Trajectory.h"
#include "../src/witsml2_0/Log.h"
#include "../src/witsml2_0/ChannelSet.h"
#include "../src/witsml2_0/Channel.h"
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
	void set##attributeName(double value, uomDatatype uom, const std::string & datum);\
	double get##attributeName##Value() const;\
	uomDatatype get##attributeName##Uom() const;\
	std::string get##attributeName##Datum() const;
#define GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(attributeName, uomDatatype)\
	GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	GETTER_PRESENCE_ATTRIBUTE(attributeName)

#define GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	void set##vectorName##attributeName(unsigned int index, const attributeDatatype & value);\
	attributeDatatype get##vectorName##attributeName(unsigned int index) const;	
	
#define GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	void set##vectorName##attributeName(unsigned int index, double value, uomDatatype uom);\
	double get##vectorName##attributeName##Value(unsigned int index) const;\
	uomDatatype get##vectorName##attributeName##Uom(unsigned int index) const;

#define GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName) bool has##vectorName##attributeName(unsigned int index) const;	
#define GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)	
	
#define GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)
	
#define GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	void set##vectorName##attributeName(unsigned int index, double value, uomDatatype uom, const std::string & datum);\
	double get##vectorName##attributeName##Value(unsigned int index) const;\
	uomDatatype get##vectorName##attributeName##Uom(unsigned int index) const;\
	std::string get##vectorName##attributeName##Datum(unsigned int index) const;
#define GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)

//************************
// STD::VECTOR DEFINITIONS
//************************

%include "std_vector.i"
namespace std {
	%template(WellVector) vector<WITSML2_0_NS::Well*>;
	%template(WellboreVector) vector<WITSML2_0_NS::Wellbore*>;
	%template(WellCompletionVector) vector<WITSML2_0_NS::WellCompletion*>;
	%template(WellboreCompletionVector) vector<WITSML2_0_NS::WellboreCompletion*>;
	%template(WellboreGeometryVector) vector<WITSML2_0_NS::WellboreGeometry*>;
	%template(TrajectoryVector) vector<WITSML2_0_NS::Trajectory*>;
	%template(LogVector) vector<WITSML2_0_NS::Log*>;
	%template(ChannelSetVector) vector<WITSML2_0_NS::ChannelSet*>;
	%template(ChannelVector) vector<WITSML2_0_NS::Channel*>;
}

namespace gsoap_eml2_1
{
	enum eml21__WellStatus { eml21__WellStatus__abandoned = 0, eml21__WellStatus__active = 1, eml21__WellStatus__active_x0020_x002d__x0020injecting = 2, eml21__WellStatus__active_x0020_x002d__x0020producing = 3, eml21__WellStatus__completed = 4, eml21__WellStatus__drilling = 5, eml21__WellStatus__partially_x0020plugged = 6, eml21__WellStatus__permitted = 7, eml21__WellStatus__plugged_x0020and_x0020abandoned = 8, eml21__WellStatus__proposed = 9, eml21__WellStatus__sold = 10, eml21__WellStatus__suspended = 11, eml21__WellStatus__temporarily_x0020abandoned = 12, eml21__WellStatus__testing = 13, eml21__WellStatus__tight = 14, eml21__WellStatus__working_x0020over = 15, eml21__WellStatus__unknown = 16 }; 
	enum witsml20__WellPurpose { witsml20__WellPurpose__appraisal = 0, witsml20__WellPurpose__appraisal_x0020_x002d__x0020confirmation_x0020appraisal = 1, witsml20__WellPurpose__appraisal_x0020_x002d__x0020exploratory_x0020appraisal = 2, witsml20__WellPurpose__exploration = 3, witsml20__WellPurpose__exploration_x0020_x002d__x0020deeper_pool_x0020wildcat = 4, witsml20__WellPurpose__exploration_x0020_x002d__x0020new_field_x0020wildcat = 5, witsml20__WellPurpose__exploration_x0020_x002d__x0020new_pool_x0020wildcat = 6, witsml20__WellPurpose__exploration_x0020_x002d__x0020outpost_x0020wildcat = 7, witsml20__WellPurpose__exploration_x0020_x002d__x0020shallower_pool_x0020wildcat = 8, witsml20__WellPurpose__development = 9, witsml20__WellPurpose__development_x0020_x002d__x0020infill_x0020development = 10, witsml20__WellPurpose__development_x0020_x002d__x0020injector = 11, witsml20__WellPurpose__development_x0020_x002d__x0020producer = 12, witsml20__WellPurpose__fluid_x0020storage = 13, witsml20__WellPurpose__fluid_x0020storage_x0020_x002d__x0020gas_x0020storage = 14, witsml20__WellPurpose__general_x0020srvc = 15, witsml20__WellPurpose__general_x0020srvc_x0020_x002d__x0020borehole_x0020re_acquisition = 16, witsml20__WellPurpose__general_x0020srvc_x0020_x002d__x0020observation = 17, witsml20__WellPurpose__general_x0020srvc_x0020_x002d__x0020relief = 18, witsml20__WellPurpose__general_x0020srvc_x0020_x002d__x0020research = 19, witsml20__WellPurpose__general_x0020srvc_x0020_x002d__x0020research_x0020_x002d__x0020drill_x0020test = 20, witsml20__WellPurpose__general_x0020srvc_x0020_x002d__x0020research_x0020_x002d__x0020strat_x0020test = 21, witsml20__WellPurpose__general_x0020srvc_x0020_x002d__x0020waste_x0020disposal = 22, witsml20__WellPurpose__mineral = 23 };
	enum witsml20__WellFluid { witsml20__WellFluid__air = 0, witsml20__WellFluid__condensate = 1, witsml20__WellFluid__dry = 2, witsml20__WellFluid__gas = 3, witsml20__WellFluid__gas_water = 4, witsml20__WellFluid__non_x0020HC_x0020gas = 5, witsml20__WellFluid__non_x0020HC_x0020gas_x0020_x002d__x0020CO2 = 6, witsml20__WellFluid__oil = 7, witsml20__WellFluid__oil_gas = 8, witsml20__WellFluid__oil_water = 9, witsml20__WellFluid__steam = 10, witsml20__WellFluid__water = 11, witsml20__WellFluid__water_x0020_x002d__x0020brine = 12, witsml20__WellFluid__water_x0020_x002d__x0020fresh_x0020water = 13 };
	enum witsml20__WellDirection { witsml20__WellDirection__huff_n_puff = 0, witsml20__WellDirection__injector = 1, witsml20__WellDirection__producer = 2, witsml20__WellDirection__uncertain = 3 };
	enum eml21__WellboreDatumReference { eml21__WellboreDatumReference__ground_x0020level = 0, eml21__WellboreDatumReference__kelly_x0020bushing = 1, eml21__WellboreDatumReference__mean_x0020sea_x0020level = 2, eml21__WellboreDatumReference__derrick_x0020floor = 3, eml21__WellboreDatumReference__casing_x0020flange = 4, eml21__WellboreDatumReference__crown_x0020valve = 5, eml21__WellboreDatumReference__rotary_x0020bushing = 6, eml21__WellboreDatumReference__rotary_x0020table = 7, eml21__WellboreDatumReference__sea_x0020floor = 8, eml21__WellboreDatumReference__lowest_x0020astronomical_x0020tide = 9, eml21__WellboreDatumReference__mean_x0020higher_x0020high_x0020water = 10, eml21__WellboreDatumReference__mean_x0020high_x0020water = 11, eml21__WellboreDatumReference__mean_x0020lower_x0020low_x0020water = 12, eml21__WellboreDatumReference__mean_x0020low_x0020water = 13, eml21__WellboreDatumReference__mean_x0020tide_x0020level = 14,eml21__WellboreDatumReference__kickoff_x0020point = 15 };
	enum witsml20__WellboreType { witsml20__WellboreType__bypass = 0, witsml20__WellboreType__initial = 1, witsml20__WellboreType__redrill = 2, witsml20__WellboreType__reentry = 3, witsml20__WellboreType__respud = 4, witsml20__WellboreType__sidetrack = 5 };
	enum witsml20__WellboreShape { witsml20__WellboreShape__build_x0020and_x0020hold = 0, witsml20__WellboreShape__deviated = 1, witsml20__WellboreShape__double_x0020kickoff = 2, witsml20__WellboreShape__horizontal = 3, witsml20__WellboreShape__S_shaped = 4, witsml20__WellboreShape__vertical = 5 };
	enum witsml20__PerforationStatus { witsml20__PerforationStatus__open = 0, witsml20__PerforationStatus__proposed = 1, witsml20__PerforationStatus__squeezed = 2 };
	enum witsml20__ElevCodeEnum { witsml20__ElevCodeEnum__CF = 0, witsml20__ElevCodeEnum__CV = 1, witsml20__ElevCodeEnum__DF = 2, witsml20__ElevCodeEnum__GL = 3, witsml20__ElevCodeEnum__KB = 4, witsml20__ElevCodeEnum__RB = 5, witsml20__ElevCodeEnum__RT = 6, witsml20__ElevCodeEnum__SF = 7, witsml20__ElevCodeEnum__LAT = 8, witsml20__ElevCodeEnum__SL = 9, witsml20__ElevCodeEnum__MHHW = 10, witsml20__ElevCodeEnum__MHW = 11, witsml20__ElevCodeEnum__MLLW = 12, witsml20__ElevCodeEnum__MLW = 13, witsml20__ElevCodeEnum__MTL = 14, witsml20__ElevCodeEnum__KO = 15, witsml20__ElevCodeEnum__unknown = 16};
	enum witsml20__TrajStationType {
		witsml20__TrajStationType__azimuth_x0020on_x0020plane = 0,
		witsml20__TrajStationType__buildrate_x0020to_x0020delta_MD = 1,
		witsml20__TrajStationType__buildrate_x0020to_x0020INCL = 2,
		witsml20__TrajStationType__buildrate_x0020to_x0020MD = 3,
		witsml20__TrajStationType__buildrate_x0020and_x0020turnrate_x0020to_x0020AZI = 4,
		witsml20__TrajStationType__buildrate_x0020and_x0020turnrate_x0020to_x0020delta_MD = 5,
		witsml20__TrajStationType__buildrate_x0020and_x0020turnrate_x0020to_x0020INCL = 6,
		witsml20__TrajStationType__buildrate_x0020and_x0020turnrate_x0020to_x0020INCL_x0020and_x0020AZI = 7,
		witsml20__TrajStationType__buildrate_x0020and_x0020turnrate_x0020to_x0020MD = 8,
		witsml20__TrajStationType__buildrate_x0020and_x0020turnrate_x0020to_x0020TVD = 9,
		witsml20__TrajStationType__buildrate_x0020TVD = 10,
		witsml20__TrajStationType__casing_x0020MD = 11,
		witsml20__TrajStationType__casing_x0020TVD = 12,
		witsml20__TrajStationType__DLS = 13,
		witsml20__TrajStationType__DLS_x0020to_x0020AZI_x0020and_x0020MD = 14,
		witsml20__TrajStationType__DLS_x0020to_x0020AZI_TVD = 15,
		witsml20__TrajStationType__DLS_x0020to_x0020INCL = 16,
		witsml20__TrajStationType__DLS_x0020to_x0020INCL_x0020and_x0020AZI = 17,
		witsml20__TrajStationType__DLS_x0020to_x0020INCL_x0020and_x0020MD = 18,
		witsml20__TrajStationType__DLS_x0020to_x0020INCL_x0020and_x0020TVD = 19,
		witsml20__TrajStationType__DLS_x0020to_x0020NS = 20,
		witsml20__TrajStationType__DLS_x0020and_x0020toolface_x0020to_x0020AZI = 21,
		witsml20__TrajStationType__DLS_x0020and_x0020toolface_x0020to_x0020delta_MD = 22,
		witsml20__TrajStationType__DLS_x0020and_x0020toolface_x0020to_x0020INCL = 23,
		witsml20__TrajStationType__DLS_x0020and_x0020toolface_x0020to_x0020INCL_AZI = 24,
		witsml20__TrajStationType__DLS_x0020and_x0020toolface_x0020to_x0020MD = 25,
		witsml20__TrajStationType__DLS_x0020and_x0020toolface_x0020to_x0020TVD = 26,
		witsml20__TrajStationType__formation_x0020MD = 27,
		witsml20__TrajStationType__formation_x0020TVD = 28,
		witsml20__TrajStationType__hold_x0020to_x0020delta_MD = 29,
		witsml20__TrajStationType__hold_x0020to_x0020MD = 30,
		witsml20__TrajStationType__hold_x0020to_x0020TVD = 31,
		witsml20__TrajStationType__INCL_x0020AZI_x0020and_x0020TVD = 32,
		witsml20__TrajStationType__interpolated = 33,
		witsml20__TrajStationType__marker_x0020MD = 34,
		witsml20__TrajStationType__marker_x0020TVD = 35,
		witsml20__TrajStationType__MD_x0020and_x0020INCL = 36,
		witsml20__TrajStationType__MD_x0020INCL_x0020and_x0020AZI = 37,
		witsml20__TrajStationType__N_x0020E_x0020and_x0020TVD = 38,
		witsml20__TrajStationType__NS_x0020EW_x0020and_x0020TVD = 39,
		witsml20__TrajStationType__target_x0020center = 40,
		witsml20__TrajStationType__target_x0020offset = 41,
		witsml20__TrajStationType__tie_x0020in_x0020point = 42,
		witsml20__TrajStationType__turnrate_x0020to_x0020AZI = 43,
		witsml20__TrajStationType__turnrate_x0020to_x0020delta_MD = 44,
		witsml20__TrajStationType__turnrate_x0020to_x0020MD = 45,
		witsml20__TrajStationType__turnrate_x0020to_x0020TVD = 46,
		witsml20__TrajStationType__unknown = 47
	};
	enum witsml20__ChannelStatus {
		witsml20__ChannelStatus__active = 0,
		witsml20__ChannelStatus__closed = 1,
		witsml20__ChannelStatus__inactive = 2
	};
	enum witsml20__AziRef {
		witsml20__AziRef__magnetic_x0020north = 0,
		witsml20__AziRef__grid_x0020north = 1,
		witsml20__AziRef__true_x0020north = 2
	};
	enum witsml20__TypeSurveyTool {
		witsml20__TypeSurveyTool__gyroscopic_x0020inertial = 0,
		witsml20__TypeSurveyTool__gyroscopic_x0020MWD = 1,
		witsml20__TypeSurveyTool__gyroscopic_x0020north_x0020seeking = 2,
		witsml20__TypeSurveyTool__magnetic_x0020multiple_shot = 3,
		witsml20__TypeSurveyTool__magnetic_x0020MWD = 4,
		witsml20__TypeSurveyTool__magnetic_x0020single_shot = 5
	};
	enum witsml20__TrajStnCalcAlgorithm {
		witsml20__TrajStnCalcAlgorithm__average_x0020angle = 0,
		witsml20__TrajStnCalcAlgorithm__balanced_x0020tangential = 1,
		witsml20__TrajStnCalcAlgorithm__constant_x0020tool_x0020face = 2,
		witsml20__TrajStnCalcAlgorithm__custom = 3,
		witsml20__TrajStnCalcAlgorithm__inertial = 4,
		witsml20__TrajStnCalcAlgorithm__minimum_x0020curvature = 5,
		witsml20__TrajStnCalcAlgorithm__radius_x0020of_x0020curvature = 6,
		witsml20__TrajStnCalcAlgorithm__tangential = 7
	};
	enum witsml20__TrajStationStatus {
		witsml20__TrajStationStatus__open = 0,
		witsml20__TrajStationStatus__rejected = 1,
		witsml20__TrajStationStatus__position = 2
	};
	enum witsml20__HoleCasingType {
		witsml20__HoleCasingType__blow_x0020out_x0020preventer = 0,
		witsml20__HoleCasingType__casing = 1,
		witsml20__HoleCasingType__conductor = 2,
		witsml20__HoleCasingType__curved_x0020conductor = 3,
		witsml20__HoleCasingType__liner = 4,
		witsml20__HoleCasingType__open_x0020hole = 5,
		witsml20__HoleCasingType__riser = 6,
		witsml20__HoleCasingType__tubing = 7
	};
	enum witsml20__EtpDataType {
		witsml20__EtpDataType__boolean = 0,
		witsml20__EtpDataType__bytes = 1,
		witsml20__EtpDataType__double_ = 2,
		witsml20__EtpDataType__float_ = 3,
		witsml20__EtpDataType__int_ = 4,
		witsml20__EtpDataType__long_ = 5,
		witsml20__EtpDataType__null = 6,
		witsml20__EtpDataType__string = 7,
		witsml20__EtpDataType__vector = 8
	};
	enum witsml20__ChannelIndexType {
		witsml20__ChannelIndexType__measured_x0020depth = 0,
		witsml20__ChannelIndexType__true_x0020vertical_x0020depth = 1,
		witsml20__ChannelIndexType__pass_x0020indexed_x0020depth = 2,
		witsml20__ChannelIndexType__date_x0020time = 3,
		witsml20__ChannelIndexType__elapsed_x0020time = 4,
		witsml20__ChannelIndexType__temperature = 5,
		witsml20__ChannelIndexType__pressure = 6
	};
	enum eml21__UnitOfMeasure {
		eml21__UnitOfMeasure__A = 'A',
		eml21__UnitOfMeasure__a = 'a',
		eml21__UnitOfMeasure__b = 'b',
		eml21__UnitOfMeasure__B = 'B',
		eml21__UnitOfMeasure__C = 'C',
		eml21__UnitOfMeasure__D = 'D',
		eml21__UnitOfMeasure__d = 'd',
		eml21__UnitOfMeasure__F = 'F',
		eml21__UnitOfMeasure__g = 'g',
		eml21__UnitOfMeasure__H = 'H',
		eml21__UnitOfMeasure__h = 'h',
		eml21__UnitOfMeasure__J = 'J',
		eml21__UnitOfMeasure__K = 'K',
		eml21__UnitOfMeasure__L = 'L',
		eml21__UnitOfMeasure__m = 'm',
		eml21__UnitOfMeasure__N = 'N',
		eml21__UnitOfMeasure__O = 'O',
		eml21__UnitOfMeasure__P = 'P',
		eml21__UnitOfMeasure__S = 'S',
		eml21__UnitOfMeasure__s = 's',
		eml21__UnitOfMeasure__t = 't',
		eml21__UnitOfMeasure__T = 'T',
		eml21__UnitOfMeasure__V = 'V',
		eml21__UnitOfMeasure__W = 'W',
		eml21__UnitOfMeasure___x0025 = 'u',
		eml21__UnitOfMeasure___x0025_x005barea_x005d = 'v',
		eml21__UnitOfMeasure___x0025_x005bmass_x005d = 'w',
		eml21__UnitOfMeasure___x0025_x005bmolar_x005d = 'x',
		eml21__UnitOfMeasure___x0025_x005bvol_x005d = 'y',
		eml21__UnitOfMeasure___x0028bbl_x002fd_x0029_x002f_x0028bbl_x002fd_x0029 = 'z',
		eml21__UnitOfMeasure___x0028m3_x002fd_x0029_x002f_x0028m3_x002fd_x0029 = 123,
		eml21__UnitOfMeasure___x0028m3_x002fs_x0029_x002f_x0028m3_x002fs_x0029 = 124,
		eml21__UnitOfMeasure__0_x002e001_x0020bbl_x002fft3 = 125,
		eml21__UnitOfMeasure__0_x002e001_x0020bbl_x002fm3 = 126,
		eml21__UnitOfMeasure__0_x002e001_x0020d_x002fft3 = 127,
		eml21__UnitOfMeasure__0_x002e001_x0020gal_x005bUK_x005d_x002fbbl = 128,
		eml21__UnitOfMeasure__0_x002e001_x0020gal_x005bUK_x005d_x002fgal_x005bUK_x005d = 129,
		eml21__UnitOfMeasure__0_x002e001_x0020gal_x005bUS_x005d_x002fbbl = 130,
		eml21__UnitOfMeasure__0_x002e001_x0020gal_x005bUS_x005d_x002fft3 = 131,
		eml21__UnitOfMeasure__0_x002e001_x0020gal_x005bUS_x005d_x002fgal_x005bUS_x005d = 132,
		eml21__UnitOfMeasure__0_x002e001_x0020h_x002fft = 133,
		eml21__UnitOfMeasure__0_x002e001_x0020kPa2_x002fcP = 134,
		eml21__UnitOfMeasure__0_x002e001_x0020lbm_x002fbbl = 135,
		eml21__UnitOfMeasure__0_x002e001_x0020lbm_x002fgal_x005bUK_x005d = 136,
		eml21__UnitOfMeasure__0_x002e001_x0020lbm_x002fgal_x005bUS_x005d = 137,
		eml21__UnitOfMeasure__0_x002e001_x0020psi_x002fft = 138,
		eml21__UnitOfMeasure__0_x002e001_x0020pt_x005bUK_x005d_x002fbbl = 139,
		eml21__UnitOfMeasure__0_x002e001_x0020seca = 140,
		eml21__UnitOfMeasure__0_x002e01_x0020bbl_x002fbbl = 141,
		eml21__UnitOfMeasure__0_x002e01_x0020dega_x002fft = 142,
		eml21__UnitOfMeasure__0_x002e01_x0020degF_x002fft = 143,
		eml21__UnitOfMeasure__0_x002e01_x0020dm3_x002fkm = 144,
		eml21__UnitOfMeasure__0_x002e01_x0020ft_x002fft = 145,
		eml21__UnitOfMeasure__0_x002e01_x0020grain_x002fft3 = 146,
		eml21__UnitOfMeasure__0_x002e01_x0020L_x002fkg = 147,
		eml21__UnitOfMeasure__0_x002e01_x0020L_x002fkm = 148,
		eml21__UnitOfMeasure__0_x002e01_x0020lbf_x002fft = 149,
		eml21__UnitOfMeasure__0_x002e01_x0020lbf_x002fft2 = 150,
		eml21__UnitOfMeasure__0_x002e01_x0020lbm_x002fft2 = 151,
		eml21__UnitOfMeasure__0_x002e01_x0020psi_x002fft = 152,
		eml21__UnitOfMeasure__0_x002e1_x0020ft = 153,
		eml21__UnitOfMeasure__0_x002e1_x0020ft_x005bUS_x005d = 154,
		eml21__UnitOfMeasure__0_x002e1_x0020gal_x005bUS_x005d_x002fbbl = 155,
		eml21__UnitOfMeasure__0_x002e1_x0020in = 156,
		eml21__UnitOfMeasure__0_x002e1_x0020L_x002fbbl = 157,
		eml21__UnitOfMeasure__0_x002e1_x0020lbm_x002fbbl = 158,
		eml21__UnitOfMeasure__0_x002e1_x0020pt_x005bUS_x005d_x002fbbl = 159,
		eml21__UnitOfMeasure__0_x002e1_x0020yd = 160,
		eml21__UnitOfMeasure__1_x002f_x0028kg_x002es_x0029 = 161,
		eml21__UnitOfMeasure__1_x002f16_x0020in = 162,
		eml21__UnitOfMeasure__1_x002f2_x0020ft = 163,
		eml21__UnitOfMeasure__1_x002f2_x0020ms = 164,
		eml21__UnitOfMeasure__1_x002f30_x0020cm3_x002fmin = 165,
		eml21__UnitOfMeasure__1_x002f30_x0020dega_x002fft = 166,
		eml21__UnitOfMeasure__1_x002f30_x0020dega_x002fm = 167,
		eml21__UnitOfMeasure__1_x002f30_x0020lbf_x002fm = 168,
		eml21__UnitOfMeasure__1_x002f30_x0020m_x002fm = 169,
		eml21__UnitOfMeasure__1_x002f30_x0020N_x002fm = 170,
		eml21__UnitOfMeasure__1_x002f32_x0020in = 171,
		eml21__UnitOfMeasure__1_x002f64_x0020in = 172,
		eml21__UnitOfMeasure__1_x002fa = 173,
		eml21__UnitOfMeasure__1_x002fangstrom = 174,
		eml21__UnitOfMeasure__1_x002fbar = 175,
		eml21__UnitOfMeasure__1_x002fbbl = 176,
		eml21__UnitOfMeasure__1_x002fcm = 177,
		eml21__UnitOfMeasure__1_x002fd = 178,
		eml21__UnitOfMeasure__1_x002fdegC = 179,
		eml21__UnitOfMeasure__1_x002fdegF = 180,
		eml21__UnitOfMeasure__1_x002fdegR = 181,
		eml21__UnitOfMeasure__1_x002fft = 182,
		eml21__UnitOfMeasure__1_x002fft2 = 183,
		eml21__UnitOfMeasure__1_x002fft3 = 184,
		eml21__UnitOfMeasure__1_x002fg = 185,
		eml21__UnitOfMeasure__1_x002fgal_x005bUK_x005d = 186,
		eml21__UnitOfMeasure__1_x002fgal_x005bUS_x005d = 187,
		eml21__UnitOfMeasure__1_x002fh = 188,
		eml21__UnitOfMeasure__1_x002fH = 189,
		eml21__UnitOfMeasure__1_x002fin = 190,
		eml21__UnitOfMeasure__1_x002fK = 191,
		eml21__UnitOfMeasure__1_x002fkg = 192,
		eml21__UnitOfMeasure__1_x002fkm2 = 193,
		eml21__UnitOfMeasure__1_x002fkPa = 194,
		eml21__UnitOfMeasure__1_x002fL = 195,
		eml21__UnitOfMeasure__1_x002flbf = 196,
		eml21__UnitOfMeasure__1_x002flbm = 197,
		eml21__UnitOfMeasure__1_x002fm = 198,
		eml21__UnitOfMeasure__1_x002fm2 = 199,
		eml21__UnitOfMeasure__1_x002fm3 = 200,
		eml21__UnitOfMeasure__1_x002fmi = 201,
		eml21__UnitOfMeasure__1_x002fmi2 = 202,
		eml21__UnitOfMeasure__1_x002fmin = 203,
		eml21__UnitOfMeasure__1_x002fmm = 204,
		eml21__UnitOfMeasure__1_x002fms = 205,
		eml21__UnitOfMeasure__1_x002fN = 206,
		eml21__UnitOfMeasure__1_x002fnm = 207,
		eml21__UnitOfMeasure__1_x002fPa = 208,
		eml21__UnitOfMeasure__1_x002fpPa = 209,
		eml21__UnitOfMeasure__1_x002fpsi = 210,
		eml21__UnitOfMeasure__1_x002fs = 211,
		eml21__UnitOfMeasure__1_x002fupsi = 212,
		eml21__UnitOfMeasure__1_x002fus = 213,
		eml21__UnitOfMeasure__1_x002fuV = 214,
		eml21__UnitOfMeasure__1_x002fV = 215,
		eml21__UnitOfMeasure__1_x002fwk = 216,
		eml21__UnitOfMeasure__1_x002fyd = 217,
		eml21__UnitOfMeasure__10_x0020ft = 218,
		eml21__UnitOfMeasure__10_x0020in = 219,
		eml21__UnitOfMeasure__10_x0020km = 220,
		eml21__UnitOfMeasure__10_x0020kN = 221,
		eml21__UnitOfMeasure__10_x0020Mg_x002fm3 = 222,
		eml21__UnitOfMeasure__100_x0020ft = 223,
		eml21__UnitOfMeasure__100_x0020ka_x005bt_x005d = 224,
		eml21__UnitOfMeasure__100_x0020km = 225,
		eml21__UnitOfMeasure__1000_x0020bbl = 226,
		eml21__UnitOfMeasure__1000_x0020bbl_x002eft_x002fd = 227,
		eml21__UnitOfMeasure__1000_x0020bbl_x002fd = 228,
		eml21__UnitOfMeasure__1000_x0020ft = 229,
		eml21__UnitOfMeasure__1000_x0020ft_x002fh = 230,
		eml21__UnitOfMeasure__1000_x0020ft_x002fs = 231,
		eml21__UnitOfMeasure__1000_x0020ft3 = 232,
		eml21__UnitOfMeasure__1000_x0020ft3_x002f_x0028d_x002eft_x0029 = 233,
		eml21__UnitOfMeasure__1000_x0020ft3_x002f_x0028psi_x002ed_x0029 = 234,
		eml21__UnitOfMeasure__1000_x0020ft3_x002fbbl = 235,
		eml21__UnitOfMeasure__1000_x0020ft3_x002fd = 236,
		eml21__UnitOfMeasure__1000_x0020gal_x005bUK_x005d = 237,
		eml21__UnitOfMeasure__1000_x0020gal_x005bUS_x005d = 238,
		eml21__UnitOfMeasure__1000_x0020lbf_x002eft = 239,
		eml21__UnitOfMeasure__1000_x0020m3 = 240,
		eml21__UnitOfMeasure__1000_x0020m3_x002f_x0028d_x002em_x0029 = 241,
		eml21__UnitOfMeasure__1000_x0020m3_x002f_x0028h_x002em_x0029 = 242,
		eml21__UnitOfMeasure__1000_x0020m3_x002fd = 243,
		eml21__UnitOfMeasure__1000_x0020m3_x002fh = 244,
		eml21__UnitOfMeasure__1000_x0020m3_x002fm3 = 245,
		eml21__UnitOfMeasure__1000_x0020m4_x002fd = 246,
		eml21__UnitOfMeasure__1E12_x0020ft3 = 247,
		eml21__UnitOfMeasure__1E6_x0020_x0028ft3_x002fd_x0029_x002f_x0028bbl_x002fd_x0029 = 248,
		eml21__UnitOfMeasure__1E_6_x0020acre_x002eft_x002fbbl = 249,
		eml21__UnitOfMeasure__1E6_x0020bbl = 250,
		eml21__UnitOfMeasure__1E6_x0020bbl_x002f_x0028acre_x002eft_x0029 = 251,
		eml21__UnitOfMeasure__1E6_x0020bbl_x002facre = 252,
		eml21__UnitOfMeasure__1E6_x0020bbl_x002fd = 253,
		eml21__UnitOfMeasure__1E_6_x0020bbl_x002fft3 = 254,
		eml21__UnitOfMeasure__1E_6_x0020bbl_x002fm3 = 255,
		eml21__UnitOfMeasure__1E6_x0020Btu_x005bIT_x005d = 256,
		eml21__UnitOfMeasure__1E6_x0020Btu_x005bIT_x005d_x002fh = 257,
		eml21__UnitOfMeasure__1E6_x0020ft3 = 258,
		eml21__UnitOfMeasure__1E6_x0020ft3_x002f_x0028acre_x002eft_x0029 = 259,
		eml21__UnitOfMeasure__1E6_x0020ft3_x002fbbl = 260,
		eml21__UnitOfMeasure__1E6_x0020ft3_x002fd = 261,
		eml21__UnitOfMeasure__1E_6_x0020gal_x005bUS_x005d = 262,
		eml21__UnitOfMeasure__1E6_x0020lbm_x002fa = 263,
		eml21__UnitOfMeasure__1E6_x0020m3 = 264,
		eml21__UnitOfMeasure__1E_6_x0020m3_x002f_x0028m3_x002edegC_x0029 = 265,
		eml21__UnitOfMeasure__1E_6_x0020m3_x002f_x0028m3_x002edegF_x0029 = 266,
		eml21__UnitOfMeasure__1E6_x0020m3_x002fd = 267,
		eml21__UnitOfMeasure__1E_9_x00201_x002fft = 268,
		eml21__UnitOfMeasure__1E9_x0020bbl = 269,
		eml21__UnitOfMeasure__1E9_x0020ft3 = 270,
		eml21__UnitOfMeasure__30_x0020ft = 271,
		eml21__UnitOfMeasure__30_x0020m = 272,
		eml21__UnitOfMeasure__A_x002eh = 273,
		eml21__UnitOfMeasure__A_x002em2 = 274,
		eml21__UnitOfMeasure__A_x002es = 275,
		eml21__UnitOfMeasure__A_x002es_x002fkg = 276,
		eml21__UnitOfMeasure__A_x002es_x002fm3 = 277,
		eml21__UnitOfMeasure__A_x002fcm2 = 278,
		eml21__UnitOfMeasure__A_x002fft2 = 279,
		eml21__UnitOfMeasure__A_x002fm = 280,
		eml21__UnitOfMeasure__A_x002fm2 = 281,
		eml21__UnitOfMeasure__A_x002fmm = 282,
		eml21__UnitOfMeasure__A_x002fmm2 = 283,
		eml21__UnitOfMeasure__a_x005bt_x005d = 284,
		eml21__UnitOfMeasure__acre = 285,
		eml21__UnitOfMeasure__acre_x002eft = 286,
		eml21__UnitOfMeasure__ag = 287,
		eml21__UnitOfMeasure__aJ = 288,
		eml21__UnitOfMeasure__angstrom = 289,
		eml21__UnitOfMeasure__at = 290,
		eml21__UnitOfMeasure__atm = 291,
		eml21__UnitOfMeasure__atm_x002fft = 292,
		eml21__UnitOfMeasure__atm_x002fh = 293,
		eml21__UnitOfMeasure__atm_x002fhm = 294,
		eml21__UnitOfMeasure__atm_x002fm = 295,
		eml21__UnitOfMeasure__B_x002eW = 296,
		eml21__UnitOfMeasure__b_x002fcm3 = 297,
		eml21__UnitOfMeasure__B_x002fm = 298,
		eml21__UnitOfMeasure__B_x002fO = 299,
		eml21__UnitOfMeasure__bar = 300,
		eml21__UnitOfMeasure__bar_x002fh = 301,
		eml21__UnitOfMeasure__bar_x002fkm = 302,
		eml21__UnitOfMeasure__bar_x002fm = 303,
		eml21__UnitOfMeasure__bar2 = 304,
		eml21__UnitOfMeasure__bar2_x002fcP = 305,
		eml21__UnitOfMeasure__bbl = 306,
		eml21__UnitOfMeasure__bbl_x002f_x0028acre_x002eft_x0029 = 307,
		eml21__UnitOfMeasure__bbl_x002f_x0028d_x002eacre_x002eft_x0029 = 308,
		eml21__UnitOfMeasure__bbl_x002f_x0028d_x002eft_x0029 = 309,
		eml21__UnitOfMeasure__bbl_x002f_x0028ft_x002epsi_x002ed_x0029 = 310,
		eml21__UnitOfMeasure__bbl_x002f_x0028kPa_x002ed_x0029 = 311,
		eml21__UnitOfMeasure__bbl_x002f_x0028psi_x002ed_x0029 = 312,
		eml21__UnitOfMeasure__bbl_x002facre = 313,
		eml21__UnitOfMeasure__bbl_x002fbbl = 314,
		eml21__UnitOfMeasure__bbl_x002fd = 315,
		eml21__UnitOfMeasure__bbl_x002fd2 = 316,
		eml21__UnitOfMeasure__bbl_x002fft = 317,
		eml21__UnitOfMeasure__bbl_x002fft3 = 318,
		eml21__UnitOfMeasure__bbl_x002fh = 319,
		eml21__UnitOfMeasure__bbl_x002fh2 = 320,
		eml21__UnitOfMeasure__bbl_x002fin = 321,
		eml21__UnitOfMeasure__bbl_x002fm3 = 322,
		eml21__UnitOfMeasure__bbl_x002fmi = 323,
		eml21__UnitOfMeasure__bbl_x002fmin = 324,
		eml21__UnitOfMeasure__bbl_x002fpsi = 325,
		eml21__UnitOfMeasure__bbl_x002fton_x005bUK_x005d = 326,
		eml21__UnitOfMeasure__bbl_x002fton_x005bUS_x005d = 327,
		eml21__UnitOfMeasure__Bd = 328,
		eml21__UnitOfMeasure__bit = 329,
		eml21__UnitOfMeasure__bit_x002fs = 330,
		eml21__UnitOfMeasure__Bq = 331,
		eml21__UnitOfMeasure__Bq_x002fkg = 332,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d = 333,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002ein_x002f_x0028h_x002eft2_x002edegF_x0029 = 334,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002f_x0028h_x002eft_x002edegF_x0029 = 335,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002f_x0028h_x002eft2_x0029 = 336,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002f_x0028h_x002eft2_x002edegF_x0029 = 337,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002f_x0028h_x002eft2_x002edegR_x0029 = 338,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002f_x0028h_x002eft3_x0029 = 339,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002f_x0028h_x002eft3_x002edegF_x0029 = 340,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002f_x0028h_x002em2_x002edegC_x0029 = 341,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002f_x0028hp_x002eh_x0029 = 342,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002f_x0028lbm_x002edegF_x0029 = 343,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002f_x0028lbm_x002edegR_x0029 = 344,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002f_x0028lbmol_x002edegF_x0029 = 345,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002f_x0028s_x002eft2_x0029 = 346,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002f_x0028s_x002eft2_x002edegF_x0029 = 347,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002f_x0028s_x002eft3_x0029 = 348,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002f_x0028s_x002eft3_x002edegF_x0029 = 349,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002fbbl = 350,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002fft3 = 351,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002fgal_x005bUK_x005d = 352,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002fgal_x005bUS_x005d = 353,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002fh = 354,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002flbm = 355,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002flbmol = 356,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002fmin = 357,
		eml21__UnitOfMeasure__Btu_x005bIT_x005d_x002fs = 358,
		eml21__UnitOfMeasure__Btu_x005bth_x005d = 359,
		eml21__UnitOfMeasure__Btu_x005bUK_x005d = 360,
		eml21__UnitOfMeasure__byte = 361,
		eml21__UnitOfMeasure__byte_x002fs = 362,
		eml21__UnitOfMeasure__C_x002em = 363,
		eml21__UnitOfMeasure__C_x002fcm2 = 364,
		eml21__UnitOfMeasure__C_x002fcm3 = 365,
		eml21__UnitOfMeasure__C_x002fg = 366,
		eml21__UnitOfMeasure__C_x002fkg = 367,
		eml21__UnitOfMeasure__C_x002fm2 = 368,
		eml21__UnitOfMeasure__C_x002fm3 = 369,
		eml21__UnitOfMeasure__C_x002fmm2 = 370,
		eml21__UnitOfMeasure__C_x002fmm3 = 371,
		eml21__UnitOfMeasure__ca = 372,
		eml21__UnitOfMeasure__cA = 373,
		eml21__UnitOfMeasure__cal_x005bIT_x005d = 374,
		eml21__UnitOfMeasure__cal_x005bth_x005d = 375,
		eml21__UnitOfMeasure__cal_x005bth_x005d_x002f_x0028g_x002eK_x0029 = 376,
		eml21__UnitOfMeasure__cal_x005bth_x005d_x002f_x0028h_x002ecm_x002edegC_x0029 = 377,
		eml21__UnitOfMeasure__cal_x005bth_x005d_x002f_x0028h_x002ecm2_x0029 = 378,
		eml21__UnitOfMeasure__cal_x005bth_x005d_x002f_x0028h_x002ecm2_x002edegC_x0029 = 379,
		eml21__UnitOfMeasure__cal_x005bth_x005d_x002f_x0028h_x002ecm3_x0029 = 380,
		eml21__UnitOfMeasure__cal_x005bth_x005d_x002f_x0028mol_x002edegC_x0029 = 381,
		eml21__UnitOfMeasure__cal_x005bth_x005d_x002f_x0028s_x002ecm_x002edegC_x0029 = 382,
		eml21__UnitOfMeasure__cal_x005bth_x005d_x002f_x0028s_x002ecm2_x002edegC_x0029 = 383,
		eml21__UnitOfMeasure__cal_x005bth_x005d_x002f_x0028s_x002ecm3_x0029 = 384,
		eml21__UnitOfMeasure__cal_x005bth_x005d_x002fcm3 = 385,
		eml21__UnitOfMeasure__cal_x005bth_x005d_x002fg = 386,
		eml21__UnitOfMeasure__cal_x005bth_x005d_x002fh = 387,
		eml21__UnitOfMeasure__cal_x005bth_x005d_x002fkg = 388,
		eml21__UnitOfMeasure__cal_x005bth_x005d_x002flbm = 389,
		eml21__UnitOfMeasure__cal_x005bth_x005d_x002fmL = 390,
		eml21__UnitOfMeasure__cal_x005bth_x005d_x002fmm3 = 391,
		eml21__UnitOfMeasure__cC = 392,
		eml21__UnitOfMeasure__ccal_x005bth_x005d = 393,
		eml21__UnitOfMeasure__ccgr = 394,
		eml21__UnitOfMeasure__cd = 395,
		eml21__UnitOfMeasure__cd_x002fm2 = 396,
		eml21__UnitOfMeasure__cEuc = 397,
		eml21__UnitOfMeasure__ceV = 398,
		eml21__UnitOfMeasure__cF = 399,
		eml21__UnitOfMeasure__cg = 400,
		eml21__UnitOfMeasure__cgauss = 401,
		eml21__UnitOfMeasure__cgr = 402,
		eml21__UnitOfMeasure__cGy = 403,
		eml21__UnitOfMeasure__cH = 404,
		eml21__UnitOfMeasure__chain = 405,
		eml21__UnitOfMeasure__chain_x005bBnA_x005d = 406,
		eml21__UnitOfMeasure__chain_x005bBnB_x005d = 407,
		eml21__UnitOfMeasure__chain_x005bCla_x005d = 408,
		eml21__UnitOfMeasure__chain_x005bInd37_x005d = 409,
		eml21__UnitOfMeasure__chain_x005bSe_x005d = 410,
		eml21__UnitOfMeasure__chain_x005bSeT_x005d = 411,
		eml21__UnitOfMeasure__chain_x005bUS_x005d = 412,
		eml21__UnitOfMeasure__cHz = 413,
		eml21__UnitOfMeasure__Ci = 414,
		eml21__UnitOfMeasure__cJ = 415,
		eml21__UnitOfMeasure__cm = 416,
		eml21__UnitOfMeasure__cm_x002fa = 417,
		eml21__UnitOfMeasure__cm_x002fs = 418,
		eml21__UnitOfMeasure__cm_x002fs2 = 419,
		eml21__UnitOfMeasure__cm2 = 420,
		eml21__UnitOfMeasure__cm2_x002fg = 421,
		eml21__UnitOfMeasure__cm2_x002fs = 422,
		eml21__UnitOfMeasure__cm3 = 423,
		eml21__UnitOfMeasure__cm3_x002fcm3 = 424,
		eml21__UnitOfMeasure__cm3_x002fg = 425,
		eml21__UnitOfMeasure__cm3_x002fh = 426,
		eml21__UnitOfMeasure__cm3_x002fL = 427,
		eml21__UnitOfMeasure__cm3_x002fm3 = 428,
		eml21__UnitOfMeasure__cm3_x002fmin = 429,
		eml21__UnitOfMeasure__cm3_x002fs = 430,
		eml21__UnitOfMeasure__cm4 = 431,
		eml21__UnitOfMeasure__cmH2O_x005b4degC_x005d = 432,
		eml21__UnitOfMeasure__cN = 433,
		eml21__UnitOfMeasure__cohm = 434,
		eml21__UnitOfMeasure__cP = 435,
		eml21__UnitOfMeasure__cPa = 436,
		eml21__UnitOfMeasure__crd = 437,
		eml21__UnitOfMeasure__cS = 438,
		eml21__UnitOfMeasure__cs = 439,
		eml21__UnitOfMeasure__cSt = 440,
		eml21__UnitOfMeasure__ct = 441,
		eml21__UnitOfMeasure__cT = 442,
		eml21__UnitOfMeasure__cu = 443,
		eml21__UnitOfMeasure__cV = 444,
		eml21__UnitOfMeasure__cW = 445,
		eml21__UnitOfMeasure__cWb = 446,
		eml21__UnitOfMeasure__cwt_x005bUK_x005d = 447,
		eml21__UnitOfMeasure__cwt_x005bUS_x005d = 448,
		eml21__UnitOfMeasure__D_x002eft = 449,
		eml21__UnitOfMeasure__D_x002em = 450,
		eml21__UnitOfMeasure__D_x002f_x0028Pa_x002es_x0029 = 451,
		eml21__UnitOfMeasure__d_x002fbbl = 452,
		eml21__UnitOfMeasure__D_x002fcP = 453,
		eml21__UnitOfMeasure__d_x002fft3 = 454,
		eml21__UnitOfMeasure__d_x002fm3 = 455,
		eml21__UnitOfMeasure__D_x005bAPI_x005d = 456,
		eml21__UnitOfMeasure__dA = 457,
		eml21__UnitOfMeasure__dam = 458,
		eml21__UnitOfMeasure__daN = 459,
		eml21__UnitOfMeasure__daN_x002em = 460,
		eml21__UnitOfMeasure__dAPI = 461,
		eml21__UnitOfMeasure__dB = 462,
		eml21__UnitOfMeasure__dB_x002emW = 463,
		eml21__UnitOfMeasure__dB_x002eMW = 464,
		eml21__UnitOfMeasure__dB_x002eW = 465,
		eml21__UnitOfMeasure__dB_x002fft = 466,
		eml21__UnitOfMeasure__dB_x002fkm = 467,
		eml21__UnitOfMeasure__dB_x002fm = 468,
		eml21__UnitOfMeasure__dB_x002fO = 469,
		eml21__UnitOfMeasure__dC = 470,
		eml21__UnitOfMeasure__dcal_x005bth_x005d = 471,
		eml21__UnitOfMeasure__dega = 472,
		eml21__UnitOfMeasure__dega_x002fft = 473,
		eml21__UnitOfMeasure__dega_x002fh = 474,
		eml21__UnitOfMeasure__dega_x002fm = 475,
		eml21__UnitOfMeasure__dega_x002fmin = 476,
		eml21__UnitOfMeasure__dega_x002fs = 477,
		eml21__UnitOfMeasure__degC = 478,
		eml21__UnitOfMeasure__degC_x002em2_x002eh_x002fkcal_x005bth_x005d = 479,
		eml21__UnitOfMeasure__degC_x002fft = 480,
		eml21__UnitOfMeasure__degC_x002fh = 481,
		eml21__UnitOfMeasure__degC_x002fhm = 482,
		eml21__UnitOfMeasure__degC_x002fkm = 483,
		eml21__UnitOfMeasure__degC_x002fkPa = 484,
		eml21__UnitOfMeasure__degC_x002fm = 485,
		eml21__UnitOfMeasure__degC_x002fmin = 486,
		eml21__UnitOfMeasure__degC_x002fs = 487,
		eml21__UnitOfMeasure__degF = 488,
		eml21__UnitOfMeasure__degF_x002eft2_x002eh_x002fBtu_x005bIT_x005d = 489,
		eml21__UnitOfMeasure__degF_x002fft = 490,
		eml21__UnitOfMeasure__degF_x002fh = 491,
		eml21__UnitOfMeasure__degF_x002fm = 492,
		eml21__UnitOfMeasure__degF_x002fmin = 493,
		eml21__UnitOfMeasure__degF_x002fpsi = 494,
		eml21__UnitOfMeasure__degF_x002fs = 495,
		eml21__UnitOfMeasure__degR = 496,
		eml21__UnitOfMeasure__dEuc = 497,
		eml21__UnitOfMeasure__deV = 498,
		eml21__UnitOfMeasure__dF = 499,
		eml21__UnitOfMeasure__dgauss = 500,
		eml21__UnitOfMeasure__dGy = 501,
		eml21__UnitOfMeasure__dH = 502,
		eml21__UnitOfMeasure__dHz = 503,
		eml21__UnitOfMeasure__dJ = 504,
		eml21__UnitOfMeasure__dm = 505,
		eml21__UnitOfMeasure__dm_x002fs = 506,
		eml21__UnitOfMeasure__dm3 = 507,
		eml21__UnitOfMeasure__dm3_x002f_x0028kW_x002eh_x0029 = 508,
		eml21__UnitOfMeasure__dm3_x002fkg = 509,
		eml21__UnitOfMeasure__dm3_x002fkmol = 510,
		eml21__UnitOfMeasure__dm3_x002fm = 511,
		eml21__UnitOfMeasure__dm3_x002fm3 = 512,
		eml21__UnitOfMeasure__dm3_x002fMJ = 513,
		eml21__UnitOfMeasure__dm3_x002fs = 514,
		eml21__UnitOfMeasure__dm3_x002fs2 = 515,
		eml21__UnitOfMeasure__dm3_x002ft = 516,
		eml21__UnitOfMeasure__dN = 517,
		eml21__UnitOfMeasure__dN_x002em = 518,
		eml21__UnitOfMeasure__dohm = 519,
		eml21__UnitOfMeasure__dP = 520,
		eml21__UnitOfMeasure__dPa = 521,
		eml21__UnitOfMeasure__drd = 522,
		eml21__UnitOfMeasure__ds = 523,
		eml21__UnitOfMeasure__dS = 524,
		eml21__UnitOfMeasure__dT = 525,
		eml21__UnitOfMeasure__dV = 526,
		eml21__UnitOfMeasure__dW = 527,
		eml21__UnitOfMeasure__dWb = 528,
		eml21__UnitOfMeasure__dyne = 529,
		eml21__UnitOfMeasure__dyne_x002ecm2 = 530,
		eml21__UnitOfMeasure__dyne_x002es_x002fcm2 = 531,
		eml21__UnitOfMeasure__dyne_x002fcm = 532,
		eml21__UnitOfMeasure__dyne_x002fcm2 = 533,
		eml21__UnitOfMeasure__EA = 534,
		eml21__UnitOfMeasure__Ea_x005bt_x005d = 535,
		eml21__UnitOfMeasure__EC = 536,
		eml21__UnitOfMeasure__Ecal_x005bth_x005d = 537,
		eml21__UnitOfMeasure__EEuc = 538,
		eml21__UnitOfMeasure__EeV = 539,
		eml21__UnitOfMeasure__EF = 540,
		eml21__UnitOfMeasure__Eg = 541,
		eml21__UnitOfMeasure__Egauss = 542,
		eml21__UnitOfMeasure__EGy = 543,
		eml21__UnitOfMeasure__EH = 544,
		eml21__UnitOfMeasure__EHz = 545,
		eml21__UnitOfMeasure__EJ = 546,
		eml21__UnitOfMeasure__EJ_x002fa = 547,
		eml21__UnitOfMeasure__Em = 548,
		eml21__UnitOfMeasure__EN = 549,
		eml21__UnitOfMeasure__Eohm = 550,
		eml21__UnitOfMeasure__EP = 551,
		eml21__UnitOfMeasure__EPa = 552,
		eml21__UnitOfMeasure__Erd = 553,
		eml21__UnitOfMeasure__erg = 554,
		eml21__UnitOfMeasure__erg_x002fa = 555,
		eml21__UnitOfMeasure__erg_x002fcm2 = 556,
		eml21__UnitOfMeasure__erg_x002fcm3 = 557,
		eml21__UnitOfMeasure__erg_x002fg = 558,
		eml21__UnitOfMeasure__erg_x002fkg = 559,
		eml21__UnitOfMeasure__erg_x002fm3 = 560,
		eml21__UnitOfMeasure__ES = 561,
		eml21__UnitOfMeasure__ET = 562,
		eml21__UnitOfMeasure__Euc = 563,
		eml21__UnitOfMeasure__eV = 564,
		eml21__UnitOfMeasure__EW = 565,
		eml21__UnitOfMeasure__EWb = 566,
		eml21__UnitOfMeasure__F_x002fm = 567,
		eml21__UnitOfMeasure__fa = 568,
		eml21__UnitOfMeasure__fA = 569,
		eml21__UnitOfMeasure__fathom = 570,
		eml21__UnitOfMeasure__fC = 571,
		eml21__UnitOfMeasure__fcal_x005bth_x005d = 572,
		eml21__UnitOfMeasure__fEuc = 573,
		eml21__UnitOfMeasure__feV = 574,
		eml21__UnitOfMeasure__fF = 575,
		eml21__UnitOfMeasure__fg = 576,
		eml21__UnitOfMeasure__fgauss = 577,
		eml21__UnitOfMeasure__fGy = 578,
		eml21__UnitOfMeasure__fH = 579,
		eml21__UnitOfMeasure__fHz = 580,
		eml21__UnitOfMeasure__fJ = 581,
		eml21__UnitOfMeasure__floz_x005bUK_x005d = 582,
		eml21__UnitOfMeasure__floz_x005bUS_x005d = 583,
		eml21__UnitOfMeasure__fm = 584,
		eml21__UnitOfMeasure__fN = 585,
		eml21__UnitOfMeasure__fohm = 586,
		eml21__UnitOfMeasure__footcandle = 587,
		eml21__UnitOfMeasure__footcandle_x002es = 588,
		eml21__UnitOfMeasure__fP = 589,
		eml21__UnitOfMeasure__fPa = 590,
		eml21__UnitOfMeasure__frd = 591,
		eml21__UnitOfMeasure__fS = 592,
		eml21__UnitOfMeasure__ft = 593,
		eml21__UnitOfMeasure__fT = 594,
		eml21__UnitOfMeasure__ft_x002fbbl = 595,
		eml21__UnitOfMeasure__ft_x002fd = 596,
		eml21__UnitOfMeasure__ft_x002fdegF = 597,
		eml21__UnitOfMeasure__ft_x002fft = 598,
		eml21__UnitOfMeasure__ft_x002fft3 = 599,
		eml21__UnitOfMeasure__ft_x002fgal_x005bUS_x005d = 600,
		eml21__UnitOfMeasure__ft_x002fh = 601,
		eml21__UnitOfMeasure__ft_x002fin = 602,
		eml21__UnitOfMeasure__ft_x002flbm = 603,
		eml21__UnitOfMeasure__ft_x002fm = 604,
		eml21__UnitOfMeasure__ft_x002fmi = 605,
		eml21__UnitOfMeasure__ft_x002fmin = 606,
		eml21__UnitOfMeasure__ft_x002fms = 607,
		eml21__UnitOfMeasure__ft_x002fpsi = 608,
		eml21__UnitOfMeasure__ft_x002fs = 609,
		eml21__UnitOfMeasure__ft_x002fs2 = 610,
		eml21__UnitOfMeasure__ft_x002fus = 611,
		eml21__UnitOfMeasure__ft_x005bBnA_x005d = 612,
		eml21__UnitOfMeasure__ft_x005bBnB_x005d = 613,
		eml21__UnitOfMeasure__ft_x005bBr36_x005d = 614,
		eml21__UnitOfMeasure__ft_x005bBr65_x005d = 615,
		eml21__UnitOfMeasure__ft_x005bCla_x005d = 616,
		eml21__UnitOfMeasure__ft_x005bGC_x005d = 617,
		eml21__UnitOfMeasure__ft_x005bInd_x005d = 618,
		eml21__UnitOfMeasure__ft_x005bInd37_x005d = 619,
		eml21__UnitOfMeasure__ft_x005bInd62_x005d = 620,
		eml21__UnitOfMeasure__ft_x005bInd75_x005d = 621,
		eml21__UnitOfMeasure__ft_x005bSe_x005d = 622,
		eml21__UnitOfMeasure__ft_x005bSeT_x005d = 623,
		eml21__UnitOfMeasure__ft_x005bUS_x005d = 624,
		eml21__UnitOfMeasure__ft2 = 625,
		eml21__UnitOfMeasure__ft2_x002fh = 626,
		eml21__UnitOfMeasure__ft2_x002fin3 = 627,
		eml21__UnitOfMeasure__ft2_x002flbm = 628,
		eml21__UnitOfMeasure__ft2_x002fs = 629,
		eml21__UnitOfMeasure__ft3 = 630,
		eml21__UnitOfMeasure__ft3_x002f_x0028d_x002eft_x0029 = 631,
		eml21__UnitOfMeasure__ft3_x002f_x0028ft_x002epsi_x002ed_x0029 = 632,
		eml21__UnitOfMeasure__ft3_x002f_x0028min_x002eft2_x0029 = 633,
		eml21__UnitOfMeasure__ft3_x002f_x0028s_x002eft2_x0029 = 634,
		eml21__UnitOfMeasure__ft3_x002fbbl = 635,
		eml21__UnitOfMeasure__ft3_x002fd = 636,
		eml21__UnitOfMeasure__ft3_x002fd2 = 637,
		eml21__UnitOfMeasure__ft3_x002fft = 638,
		eml21__UnitOfMeasure__ft3_x002fft2 = 639,
		eml21__UnitOfMeasure__ft3_x002fft3 = 640,
		eml21__UnitOfMeasure__ft3_x002fh = 641,
		eml21__UnitOfMeasure__ft3_x002fh2 = 642,
		eml21__UnitOfMeasure__ft3_x002fkg = 643,
		eml21__UnitOfMeasure__ft3_x002flbm = 644,
		eml21__UnitOfMeasure__ft3_x002flbmol = 645,
		eml21__UnitOfMeasure__ft3_x002fmin = 646,
		eml21__UnitOfMeasure__ft3_x002fmin2 = 647,
		eml21__UnitOfMeasure__ft3_x002frad = 648,
		eml21__UnitOfMeasure__ft3_x002fs = 649,
		eml21__UnitOfMeasure__ft3_x002fs2 = 650,
		eml21__UnitOfMeasure__ft3_x002fsack_x005b94lbm_x005d = 651,
		eml21__UnitOfMeasure__fur_x005bUS_x005d = 652,
		eml21__UnitOfMeasure__fV = 653,
		eml21__UnitOfMeasure__fW = 654,
		eml21__UnitOfMeasure__fWb = 655,
		eml21__UnitOfMeasure__g_x002eft_x002f_x0028cm3_x002es_x0029 = 656,
		eml21__UnitOfMeasure__g_x002em_x002f_x0028cm3_x002es_x0029 = 657,
		eml21__UnitOfMeasure__g_x002fcm3 = 658,
		eml21__UnitOfMeasure__g_x002fcm4 = 659,
		eml21__UnitOfMeasure__g_x002fdm3 = 660,
		eml21__UnitOfMeasure__g_x002fgal_x005bUK_x005d = 661,
		eml21__UnitOfMeasure__g_x002fgal_x005bUS_x005d = 662,
		eml21__UnitOfMeasure__g_x002fkg = 663,
		eml21__UnitOfMeasure__g_x002fL = 664,
		eml21__UnitOfMeasure__g_x002fm3 = 665,
		eml21__UnitOfMeasure__g_x002fmol = 666,
		eml21__UnitOfMeasure__g_x002fs = 667,
		eml21__UnitOfMeasure__g_x002ft = 668,
		eml21__UnitOfMeasure__GA = 669,
		eml21__UnitOfMeasure__Ga_x005bt_x005d = 670,
		eml21__UnitOfMeasure__Gal = 671,
		eml21__UnitOfMeasure__gal_x005bUK_x005d = 672,
		eml21__UnitOfMeasure__gal_x005bUK_x005d_x002f_x0028h_x002eft_x0029 = 673,
		eml21__UnitOfMeasure__gal_x005bUK_x005d_x002f_x0028h_x002eft2_x0029 = 674,
		eml21__UnitOfMeasure__gal_x005bUK_x005d_x002f_x0028h_x002ein_x0029 = 675,
		eml21__UnitOfMeasure__gal_x005bUK_x005d_x002f_x0028h_x002ein2_x0029 = 676,
		eml21__UnitOfMeasure__gal_x005bUK_x005d_x002f_x0028min_x002eft_x0029 = 677,
		eml21__UnitOfMeasure__gal_x005bUK_x005d_x002f_x0028min_x002eft2_x0029 = 678,
		eml21__UnitOfMeasure__gal_x005bUK_x005d_x002fd = 679,
		eml21__UnitOfMeasure__gal_x005bUK_x005d_x002fft3 = 680,
		eml21__UnitOfMeasure__gal_x005bUK_x005d_x002fh = 681,
		eml21__UnitOfMeasure__gal_x005bUK_x005d_x002fh2 = 682,
		eml21__UnitOfMeasure__gal_x005bUK_x005d_x002flbm = 683,
		eml21__UnitOfMeasure__gal_x005bUK_x005d_x002fmi = 684,
		eml21__UnitOfMeasure__gal_x005bUK_x005d_x002fmin = 685,
		eml21__UnitOfMeasure__gal_x005bUK_x005d_x002fmin2 = 686,
		eml21__UnitOfMeasure__gal_x005bUS_x005d = 687,
		eml21__UnitOfMeasure__gal_x005bUS_x005d_x002f_x0028h_x002eft_x0029 = 688,
		eml21__UnitOfMeasure__gal_x005bUS_x005d_x002f_x0028h_x002eft2_x0029 = 689,
		eml21__UnitOfMeasure__gal_x005bUS_x005d_x002f_x0028h_x002ein_x0029 = 690,
		eml21__UnitOfMeasure__gal_x005bUS_x005d_x002f_x0028h_x002ein2_x0029 = 691,
		eml21__UnitOfMeasure__gal_x005bUS_x005d_x002f_x0028min_x002eft_x0029 = 692,
		eml21__UnitOfMeasure__gal_x005bUS_x005d_x002f_x0028min_x002eft2_x0029 = 693,
		eml21__UnitOfMeasure__gal_x005bUS_x005d_x002fbbl = 694,
		eml21__UnitOfMeasure__gal_x005bUS_x005d_x002fd = 695,
		eml21__UnitOfMeasure__gal_x005bUS_x005d_x002fft = 696,
		eml21__UnitOfMeasure__gal_x005bUS_x005d_x002fft3 = 697,
		eml21__UnitOfMeasure__gal_x005bUS_x005d_x002fh = 698,
		eml21__UnitOfMeasure__gal_x005bUS_x005d_x002fh2 = 699,
		eml21__UnitOfMeasure__gal_x005bUS_x005d_x002flbm = 700,
		eml21__UnitOfMeasure__gal_x005bUS_x005d_x002fmi = 701,
		eml21__UnitOfMeasure__gal_x005bUS_x005d_x002fmin = 702,
		eml21__UnitOfMeasure__gal_x005bUS_x005d_x002fmin2 = 703,
		eml21__UnitOfMeasure__gal_x005bUS_x005d_x002fsack_x005b94lbm_x005d = 704,
		eml21__UnitOfMeasure__gal_x005bUS_x005d_x002fton_x005bUK_x005d = 705,
		eml21__UnitOfMeasure__gal_x005bUS_x005d_x002fton_x005bUS_x005d = 706,
		eml21__UnitOfMeasure__gAPI = 707,
		eml21__UnitOfMeasure__gauss = 708,
		eml21__UnitOfMeasure__gauss_x002fcm = 709,
		eml21__UnitOfMeasure__GBq = 710,
		eml21__UnitOfMeasure__GC = 711,
		eml21__UnitOfMeasure__Gcal_x005bth_x005d = 712,
		eml21__UnitOfMeasure__GEuc = 713,
		eml21__UnitOfMeasure__GeV = 714,
		eml21__UnitOfMeasure__gf = 715,
		eml21__UnitOfMeasure__GF = 716,
		eml21__UnitOfMeasure__Gg = 717,
		eml21__UnitOfMeasure__Ggauss = 718,
		eml21__UnitOfMeasure__GGy = 719,
		eml21__UnitOfMeasure__GH = 720,
		eml21__UnitOfMeasure__GHz = 721,
		eml21__UnitOfMeasure__GJ = 722,
		eml21__UnitOfMeasure__Gm = 723,
		eml21__UnitOfMeasure__GN = 724,
		eml21__UnitOfMeasure__gn = 725,
		eml21__UnitOfMeasure__Gohm = 726,
		eml21__UnitOfMeasure__gon = 727,
		eml21__UnitOfMeasure__GP = 728,
		eml21__UnitOfMeasure__GPa = 729,
		eml21__UnitOfMeasure__GPa_x002fcm = 730,
		eml21__UnitOfMeasure__GPa2 = 731,
		eml21__UnitOfMeasure__grain = 732,
		eml21__UnitOfMeasure__grain_x002fft3 = 733,
		eml21__UnitOfMeasure__grain_x002fgal_x005bUS_x005d = 734,
		eml21__UnitOfMeasure__Grd = 735,
		eml21__UnitOfMeasure__GS = 736,
		eml21__UnitOfMeasure__GT = 737,
		eml21__UnitOfMeasure__GV = 738,
		eml21__UnitOfMeasure__GW = 739,
		eml21__UnitOfMeasure__GW_x002eh = 740,
		eml21__UnitOfMeasure__GWb = 741,
		eml21__UnitOfMeasure__Gy = 742,
		eml21__UnitOfMeasure__h_x002fft3 = 743,
		eml21__UnitOfMeasure__h_x002fkm = 744,
		eml21__UnitOfMeasure__H_x002fm = 745,
		eml21__UnitOfMeasure__h_x002fm3 = 746,
		eml21__UnitOfMeasure__ha = 747,
		eml21__UnitOfMeasure__ha_x002em = 748,
		eml21__UnitOfMeasure__hbar = 749,
		eml21__UnitOfMeasure__hg = 750,
		eml21__UnitOfMeasure__hL = 751,
		eml21__UnitOfMeasure__hm = 752,
		eml21__UnitOfMeasure__hN = 753,
		eml21__UnitOfMeasure__hp = 754,
		eml21__UnitOfMeasure__hp_x002eh = 755,
		eml21__UnitOfMeasure__hp_x002eh_x002fbbl = 756,
		eml21__UnitOfMeasure__hp_x002eh_x002flbm = 757,
		eml21__UnitOfMeasure__hp_x002fft3 = 758,
		eml21__UnitOfMeasure__hp_x002fin2 = 759,
		eml21__UnitOfMeasure__hp_x005belec_x005d = 760,
		eml21__UnitOfMeasure__hp_x005bhyd_x005d = 761,
		eml21__UnitOfMeasure__hp_x005bhyd_x005d_x002fin2 = 762,
		eml21__UnitOfMeasure__hp_x005bmetric_x005d = 763,
		eml21__UnitOfMeasure__hp_x005bmetric_x005d_x002eh = 764,
		eml21__UnitOfMeasure__hs = 765,
		eml21__UnitOfMeasure__Hz = 766,
		eml21__UnitOfMeasure__in = 767,
		eml21__UnitOfMeasure__in_x002f_x0028in_x002edegF_x0029 = 768,
		eml21__UnitOfMeasure__in_x002fa = 769,
		eml21__UnitOfMeasure__in_x002fmin = 770,
		eml21__UnitOfMeasure__in_x002fs = 771,
		eml21__UnitOfMeasure__in_x002fs2 = 772,
		eml21__UnitOfMeasure__in_x005bUS_x005d = 773,
		eml21__UnitOfMeasure__in2 = 774,
		eml21__UnitOfMeasure__in2_x002fft2 = 775,
		eml21__UnitOfMeasure__in2_x002fin2 = 776,
		eml21__UnitOfMeasure__in2_x002fs = 777,
		eml21__UnitOfMeasure__in3 = 778,
		eml21__UnitOfMeasure__in3_x002fft = 779,
		eml21__UnitOfMeasure__in4 = 780,
		eml21__UnitOfMeasure__inH2O_x005b39degF_x005d = 781,
		eml21__UnitOfMeasure__inH2O_x005b60degF_x005d = 782,
		eml21__UnitOfMeasure__inHg_x005b32degF_x005d = 783,
		eml21__UnitOfMeasure__inHg_x005b60degF_x005d = 784,
		eml21__UnitOfMeasure__J_x002em_x002f_x0028s_x002em2_x002eK_x0029 = 785,
		eml21__UnitOfMeasure__J_x002em_x002fm2 = 786,
		eml21__UnitOfMeasure__J_x002f_x0028g_x002eK_x0029 = 787,
		eml21__UnitOfMeasure__J_x002f_x0028kg_x002eK_x0029 = 788,
		eml21__UnitOfMeasure__J_x002f_x0028mol_x002eK_x0029 = 789,
		eml21__UnitOfMeasure__J_x002f_x0028s_x002em2_x002edegC_x0029 = 790,
		eml21__UnitOfMeasure__J_x002fcm2 = 791,
		eml21__UnitOfMeasure__J_x002fdm3 = 792,
		eml21__UnitOfMeasure__J_x002fg = 793,
		eml21__UnitOfMeasure__J_x002fK = 794,
		eml21__UnitOfMeasure__J_x002fkg = 795,
		eml21__UnitOfMeasure__J_x002fm = 796,
		eml21__UnitOfMeasure__J_x002fm2 = 797,
		eml21__UnitOfMeasure__J_x002fm3 = 798,
		eml21__UnitOfMeasure__J_x002fmol = 799,
		eml21__UnitOfMeasure__J_x002fs = 800,
		eml21__UnitOfMeasure__K_x002em2_x002fkW = 801,
		eml21__UnitOfMeasure__K_x002em2_x002fW = 802,
		eml21__UnitOfMeasure__K_x002fkm = 803,
		eml21__UnitOfMeasure__K_x002fm = 804,
		eml21__UnitOfMeasure__K_x002fPa = 805,
		eml21__UnitOfMeasure__K_x002fs = 806,
		eml21__UnitOfMeasure__K_x002fW = 807,
		eml21__UnitOfMeasure__kA = 808,
		eml21__UnitOfMeasure__ka_x005bt_x005d = 809,
		eml21__UnitOfMeasure__kC = 810,
		eml21__UnitOfMeasure__kcal_x005bth_x005d = 811,
		eml21__UnitOfMeasure__kcal_x005bth_x005d_x002em_x002fcm2 = 812,
		eml21__UnitOfMeasure__kcal_x005bth_x005d_x002f_x0028h_x002em_x002edegC_x0029 = 813,
		eml21__UnitOfMeasure__kcal_x005bth_x005d_x002f_x0028h_x002em2_x002edegC_x0029 = 814,
		eml21__UnitOfMeasure__kcal_x005bth_x005d_x002f_x0028kg_x002edegC_x0029 = 815,
		eml21__UnitOfMeasure__kcal_x005bth_x005d_x002fcm3 = 816,
		eml21__UnitOfMeasure__kcal_x005bth_x005d_x002fg = 817,
		eml21__UnitOfMeasure__kcal_x005bth_x005d_x002fh = 818,
		eml21__UnitOfMeasure__kcal_x005bth_x005d_x002fkg = 819,
		eml21__UnitOfMeasure__kcal_x005bth_x005d_x002fm3 = 820,
		eml21__UnitOfMeasure__kcal_x005bth_x005d_x002fmol = 821,
		eml21__UnitOfMeasure__kcd = 822,
		eml21__UnitOfMeasure__kdyne = 823,
		eml21__UnitOfMeasure__kEuc = 824,
		eml21__UnitOfMeasure__keV = 825,
		eml21__UnitOfMeasure__kF = 826,
		eml21__UnitOfMeasure__kg = 827,
		eml21__UnitOfMeasure__kg_x002em = 828,
		eml21__UnitOfMeasure__kg_x002em_x002fcm2 = 829,
		eml21__UnitOfMeasure__kg_x002em_x002fs = 830,
		eml21__UnitOfMeasure__kg_x002em2 = 831,
		eml21__UnitOfMeasure__kg_x002f_x0028kW_x002eh_x0029 = 832,
		eml21__UnitOfMeasure__kg_x002f_x0028m_x002es_x0029 = 833,
		eml21__UnitOfMeasure__kg_x002f_x0028m2_x002es_x0029 = 834,
		eml21__UnitOfMeasure__kg_x002fd = 835,
		eml21__UnitOfMeasure__kg_x002fdm3 = 836,
		eml21__UnitOfMeasure__kg_x002fdm4 = 837,
		eml21__UnitOfMeasure__kg_x002fh = 838,
		eml21__UnitOfMeasure__kg_x002fJ = 839,
		eml21__UnitOfMeasure__kg_x002fkg = 840,
		eml21__UnitOfMeasure__kg_x002fL = 841,
		eml21__UnitOfMeasure__kg_x002fm = 842,
		eml21__UnitOfMeasure__kg_x002fm2 = 843,
		eml21__UnitOfMeasure__kg_x002fm3 = 844,
		eml21__UnitOfMeasure__kg_x002fm4 = 845,
		eml21__UnitOfMeasure__kg_x002fmin = 846,
		eml21__UnitOfMeasure__kg_x002fMJ = 847,
		eml21__UnitOfMeasure__kg_x002fmol = 848,
		eml21__UnitOfMeasure__kg_x002fs = 849,
		eml21__UnitOfMeasure__kg_x002fsack_x005b94lbm_x005d = 850,
		eml21__UnitOfMeasure__kg_x002ft = 851,
		eml21__UnitOfMeasure__kgauss = 852,
		eml21__UnitOfMeasure__kgf = 853,
		eml21__UnitOfMeasure__kgf_x002em = 854,
		eml21__UnitOfMeasure__kgf_x002em_x002fcm2 = 855,
		eml21__UnitOfMeasure__kgf_x002em_x002fm = 856,
		eml21__UnitOfMeasure__kgf_x002em2 = 857,
		eml21__UnitOfMeasure__kgf_x002es_x002fm2 = 858,
		eml21__UnitOfMeasure__kgf_x002fcm = 859,
		eml21__UnitOfMeasure__kgf_x002fcm2 = 860,
		eml21__UnitOfMeasure__kgf_x002fkgf = 861,
		eml21__UnitOfMeasure__kgf_x002fm2 = 862,
		eml21__UnitOfMeasure__kgf_x002fmm2 = 863,
		eml21__UnitOfMeasure__kGy = 864,
		eml21__UnitOfMeasure__kH = 865,
		eml21__UnitOfMeasure__kHz = 866,
		eml21__UnitOfMeasure__Kibyte = 867,
		eml21__UnitOfMeasure__kJ = 868,
		eml21__UnitOfMeasure__kJ_x002em_x002f_x0028h_x002em2_x002eK_x0029 = 869,
		eml21__UnitOfMeasure__kJ_x002f_x0028h_x002em2_x002eK_x0029 = 870,
		eml21__UnitOfMeasure__kJ_x002f_x0028kg_x002eK_x0029 = 871,
		eml21__UnitOfMeasure__kJ_x002f_x0028kmol_x002eK_x0029 = 872,
		eml21__UnitOfMeasure__kJ_x002fdm3 = 873,
		eml21__UnitOfMeasure__kJ_x002fkg = 874,
		eml21__UnitOfMeasure__kJ_x002fkmol = 875,
		eml21__UnitOfMeasure__kJ_x002fm3 = 876,
		eml21__UnitOfMeasure__klbf = 877,
		eml21__UnitOfMeasure__klbm = 878,
		eml21__UnitOfMeasure__klbm_x002fin = 879,
		eml21__UnitOfMeasure__klx = 880,
		eml21__UnitOfMeasure__km = 881,
		eml21__UnitOfMeasure__km_x002fcm = 882,
		eml21__UnitOfMeasure__km_x002fdm3 = 883,
		eml21__UnitOfMeasure__km_x002fh = 884,
		eml21__UnitOfMeasure__km_x002fL = 885,
		eml21__UnitOfMeasure__km_x002fs = 886,
		eml21__UnitOfMeasure__km2 = 887,
		eml21__UnitOfMeasure__km3 = 888,
		eml21__UnitOfMeasure__kmol = 889,
		eml21__UnitOfMeasure__kmol_x002fh = 890,
		eml21__UnitOfMeasure__kmol_x002fm3 = 891,
		eml21__UnitOfMeasure__kmol_x002fs = 892,
		eml21__UnitOfMeasure__kN = 893,
		eml21__UnitOfMeasure__kN_x002em = 894,
		eml21__UnitOfMeasure__kN_x002em2 = 895,
		eml21__UnitOfMeasure__kN_x002fm = 896,
		eml21__UnitOfMeasure__kN_x002fm2 = 897,
		eml21__UnitOfMeasure__knot = 898,
		eml21__UnitOfMeasure__kohm = 899,
		eml21__UnitOfMeasure__kohm_x002em = 900,
		eml21__UnitOfMeasure__kP = 901,
		eml21__UnitOfMeasure__kPa = 902,
		eml21__UnitOfMeasure__kPa_x002es_x002fm = 903,
		eml21__UnitOfMeasure__kPa_x002fh = 904,
		eml21__UnitOfMeasure__kPa_x002fhm = 905,
		eml21__UnitOfMeasure__kPa_x002fm = 906,
		eml21__UnitOfMeasure__kPa_x002fmin = 907,
		eml21__UnitOfMeasure__kPa2 = 908,
		eml21__UnitOfMeasure__kPa2_x002fcP = 909,
		eml21__UnitOfMeasure__kpsi = 910,
		eml21__UnitOfMeasure__kpsi2 = 911,
		eml21__UnitOfMeasure__krad = 912,
		eml21__UnitOfMeasure__krd = 913,
		eml21__UnitOfMeasure__kS = 914,
		eml21__UnitOfMeasure__kS_x002fm = 915,
		eml21__UnitOfMeasure__kT = 916,
		eml21__UnitOfMeasure__kV = 917,
		eml21__UnitOfMeasure__kW = 918,
		eml21__UnitOfMeasure__kW_x002eh = 919,
		eml21__UnitOfMeasure__kW_x002eh_x002f_x0028kg_x002edegC_x0029 = 920,
		eml21__UnitOfMeasure__kW_x002eh_x002fdm3 = 921,
		eml21__UnitOfMeasure__kW_x002eh_x002fkg = 922,
		eml21__UnitOfMeasure__kW_x002eh_x002fm3 = 923,
		eml21__UnitOfMeasure__kW_x002f_x0028m2_x002eK_x0029 = 924,
		eml21__UnitOfMeasure__kW_x002f_x0028m3_x002eK_x0029 = 925,
		eml21__UnitOfMeasure__kW_x002fcm2 = 926,
		eml21__UnitOfMeasure__kW_x002fm2 = 927,
		eml21__UnitOfMeasure__kW_x002fm3 = 928,
		eml21__UnitOfMeasure__kWb = 929,
		eml21__UnitOfMeasure__L_x002f_x0028bar_x002emin_x0029 = 930,
		eml21__UnitOfMeasure__L_x002fh = 931,
		eml21__UnitOfMeasure__L_x002fkg = 932,
		eml21__UnitOfMeasure__L_x002fkmol = 933,
		eml21__UnitOfMeasure__L_x002fm = 934,
		eml21__UnitOfMeasure__L_x002fm3 = 935,
		eml21__UnitOfMeasure__L_x002fmin = 936,
		eml21__UnitOfMeasure__L_x002fmol = 937,
		eml21__UnitOfMeasure__L_x002fs = 938,
		eml21__UnitOfMeasure__L_x002fs2 = 939,
		eml21__UnitOfMeasure__L_x002ft = 940,
		eml21__UnitOfMeasure__L_x002fton_x005bUK_x005d = 941,
		eml21__UnitOfMeasure__lbf = 942,
		eml21__UnitOfMeasure__lbf_x002eft = 943,
		eml21__UnitOfMeasure__lbf_x002eft_x002fbbl = 944,
		eml21__UnitOfMeasure__lbf_x002eft_x002fgal_x005bUS_x005d = 945,
		eml21__UnitOfMeasure__lbf_x002eft_x002fin = 946,
		eml21__UnitOfMeasure__lbf_x002eft_x002fin2 = 947,
		eml21__UnitOfMeasure__lbf_x002eft_x002flbm = 948,
		eml21__UnitOfMeasure__lbf_x002eft_x002fmin = 949,
		eml21__UnitOfMeasure__lbf_x002eft_x002fs = 950,
		eml21__UnitOfMeasure__lbf_x002ein = 951,
		eml21__UnitOfMeasure__lbf_x002ein_x002fin = 952,
		eml21__UnitOfMeasure__lbf_x002ein2 = 953,
		eml21__UnitOfMeasure__lbf_x002es_x002fft2 = 954,
		eml21__UnitOfMeasure__lbf_x002es_x002fin2 = 955,
		eml21__UnitOfMeasure__lbf_x002fft = 956,
		eml21__UnitOfMeasure__lbf_x002fft2 = 957,
		eml21__UnitOfMeasure__lbf_x002fft3 = 958,
		eml21__UnitOfMeasure__lbf_x002fgal_x005bUS_x005d = 959,
		eml21__UnitOfMeasure__lbf_x002fin = 960,
		eml21__UnitOfMeasure__lbf_x002flbf = 961,
		eml21__UnitOfMeasure__lbm = 962,
		eml21__UnitOfMeasure__lbm_x002eft = 963,
		eml21__UnitOfMeasure__lbm_x002eft_x002fs = 964,
		eml21__UnitOfMeasure__lbm_x002eft2 = 965,
		eml21__UnitOfMeasure__lbm_x002eft2_x002fs2 = 966,
		eml21__UnitOfMeasure__lbm_x002f_x0028ft_x002eh_x0029 = 967,
		eml21__UnitOfMeasure__lbm_x002f_x0028ft_x002es_x0029 = 968,
		eml21__UnitOfMeasure__lbm_x002f_x0028ft2_x002eh_x0029 = 969,
		eml21__UnitOfMeasure__lbm_x002f_x0028ft2_x002es_x0029 = 970,
		eml21__UnitOfMeasure__lbm_x002f_x0028gal_x005bUK_x005d_x002eft_x0029 = 971,
		eml21__UnitOfMeasure__lbm_x002f_x0028gal_x005bUS_x005d_x002eft_x0029 = 972,
		eml21__UnitOfMeasure__lbm_x002f_x0028hp_x002eh_x0029 = 973,
		eml21__UnitOfMeasure__lbm_x002fbbl = 974,
		eml21__UnitOfMeasure__lbm_x002fd = 975,
		eml21__UnitOfMeasure__lbm_x002fft = 976,
		eml21__UnitOfMeasure__lbm_x002fft2 = 977,
		eml21__UnitOfMeasure__lbm_x002fft3 = 978,
		eml21__UnitOfMeasure__lbm_x002fft4 = 979,
		eml21__UnitOfMeasure__lbm_x002fgal_x005bUK_x005d = 980,
		eml21__UnitOfMeasure__lbm_x002fgal_x005bUS_x005d = 981,
		eml21__UnitOfMeasure__lbm_x002fh = 982,
		eml21__UnitOfMeasure__lbm_x002fin3 = 983,
		eml21__UnitOfMeasure__lbm_x002flbmol = 984,
		eml21__UnitOfMeasure__lbm_x002fmin = 985,
		eml21__UnitOfMeasure__lbm_x002fs = 986,
		eml21__UnitOfMeasure__lbmol = 987,
		eml21__UnitOfMeasure__lbmol_x002f_x0028h_x002eft2_x0029 = 988,
		eml21__UnitOfMeasure__lbmol_x002f_x0028s_x002eft2_x0029 = 989,
		eml21__UnitOfMeasure__lbmol_x002fft3 = 990,
		eml21__UnitOfMeasure__lbmol_x002fgal_x005bUK_x005d = 991,
		eml21__UnitOfMeasure__lbmol_x002fgal_x005bUS_x005d = 992,
		eml21__UnitOfMeasure__lbmol_x002fh = 993,
		eml21__UnitOfMeasure__lbmol_x002fs = 994,
		eml21__UnitOfMeasure__link = 995,
		eml21__UnitOfMeasure__link_x005bBnA_x005d = 996,
		eml21__UnitOfMeasure__link_x005bBnB_x005d = 997,
		eml21__UnitOfMeasure__link_x005bCla_x005d = 998,
		eml21__UnitOfMeasure__link_x005bSe_x005d = 999,
		eml21__UnitOfMeasure__link_x005bSeT_x005d = 1000,
		eml21__UnitOfMeasure__link_x005bUS_x005d = 1001,
		eml21__UnitOfMeasure__lm = 1002,
		eml21__UnitOfMeasure__lm_x002es = 1003,
		eml21__UnitOfMeasure__lm_x002fm2 = 1004,
		eml21__UnitOfMeasure__lm_x002fW = 1005,
		eml21__UnitOfMeasure__lx = 1006,
		eml21__UnitOfMeasure__lx_x002es = 1007,
		eml21__UnitOfMeasure__m_x002f_x0028m_x002eK_x0029 = 1008,
		eml21__UnitOfMeasure__m_x002fcm = 1009,
		eml21__UnitOfMeasure__m_x002fd = 1010,
		eml21__UnitOfMeasure__m_x002fh = 1011,
		eml21__UnitOfMeasure__m_x002fK = 1012,
		eml21__UnitOfMeasure__m_x002fkg = 1013,
		eml21__UnitOfMeasure__m_x002fkm = 1014,
		eml21__UnitOfMeasure__m_x002fkPa = 1015,
		eml21__UnitOfMeasure__m_x002fm = 1016,
		eml21__UnitOfMeasure__m_x002fm3 = 1017,
		eml21__UnitOfMeasure__m_x002fmin = 1018,
		eml21__UnitOfMeasure__m_x002fms = 1019,
		eml21__UnitOfMeasure__m_x002fPa = 1020,
		eml21__UnitOfMeasure__m_x002fs = 1021,
		eml21__UnitOfMeasure__m_x002fs2 = 1022,
		eml21__UnitOfMeasure__m_x005bGer_x005d = 1023,
		eml21__UnitOfMeasure__m2 = 1024,
		eml21__UnitOfMeasure__m2_x002f_x0028kPa_x002ed_x0029 = 1025,
		eml21__UnitOfMeasure__m2_x002f_x0028Pa_x002es_x0029 = 1026,
		eml21__UnitOfMeasure__m2_x002fcm3 = 1027,
		eml21__UnitOfMeasure__m2_x002fd = 1028,
		eml21__UnitOfMeasure__m2_x002fg = 1029,
		eml21__UnitOfMeasure__m2_x002fh = 1030,
		eml21__UnitOfMeasure__m2_x002fkg = 1031,
		eml21__UnitOfMeasure__m2_x002fm2 = 1032,
		eml21__UnitOfMeasure__m2_x002fm3 = 1033,
		eml21__UnitOfMeasure__m2_x002fmol = 1034,
		eml21__UnitOfMeasure__m2_x002fs = 1035,
		eml21__UnitOfMeasure__m3 = 1036,
		eml21__UnitOfMeasure__m3_x002f_x0028bar_x002ed_x0029 = 1037,
		eml21__UnitOfMeasure__m3_x002f_x0028bar_x002eh_x0029 = 1038,
		eml21__UnitOfMeasure__m3_x002f_x0028bar_x002emin_x0029 = 1039,
		eml21__UnitOfMeasure__m3_x002f_x0028d_x002em_x0029 = 1040,
		eml21__UnitOfMeasure__m3_x002f_x0028h_x002em_x0029 = 1041,
		eml21__UnitOfMeasure__m3_x002f_x0028ha_x002em_x0029 = 1042,
		eml21__UnitOfMeasure__m3_x002f_x0028kPa_x002ed_x0029 = 1043,
		eml21__UnitOfMeasure__m3_x002f_x0028kPa_x002eh_x0029 = 1044,
		eml21__UnitOfMeasure__m3_x002f_x0028kW_x002eh_x0029 = 1045,
		eml21__UnitOfMeasure__m3_x002f_x0028m3_x002eK_x0029 = 1046,
		eml21__UnitOfMeasure__m3_x002f_x0028Pa_x002es_x0029 = 1047,
		eml21__UnitOfMeasure__m3_x002f_x0028psi_x002ed_x0029 = 1048,
		eml21__UnitOfMeasure__m3_x002f_x0028s_x002eft_x0029 = 1049,
		eml21__UnitOfMeasure__m3_x002f_x0028s_x002em_x0029 = 1050,
		eml21__UnitOfMeasure__m3_x002f_x0028s_x002em2_x0029 = 1051,
		eml21__UnitOfMeasure__m3_x002f_x0028s_x002em3_x0029 = 1052,
		eml21__UnitOfMeasure__m3_x002fbbl = 1053,
		eml21__UnitOfMeasure__m3_x002fd = 1054,
		eml21__UnitOfMeasure__m3_x002fd2 = 1055,
		eml21__UnitOfMeasure__m3_x002fg = 1056,
		eml21__UnitOfMeasure__m3_x002fh = 1057,
		eml21__UnitOfMeasure__m3_x002fJ = 1058,
		eml21__UnitOfMeasure__m3_x002fkg = 1059,
		eml21__UnitOfMeasure__m3_x002fkm = 1060,
		eml21__UnitOfMeasure__m3_x002fkmol = 1061,
		eml21__UnitOfMeasure__m3_x002fkPa = 1062,
		eml21__UnitOfMeasure__m3_x002fm = 1063,
		eml21__UnitOfMeasure__m3_x002fm2 = 1064,
		eml21__UnitOfMeasure__m3_x002fm3 = 1065,
		eml21__UnitOfMeasure__m3_x002fmin = 1066,
		eml21__UnitOfMeasure__m3_x002fmol = 1067,
		eml21__UnitOfMeasure__m3_x002fPa = 1068,
		eml21__UnitOfMeasure__m3_x002frad = 1069,
		eml21__UnitOfMeasure__m3_x002frev = 1070,
		eml21__UnitOfMeasure__m3_x002fs = 1071,
		eml21__UnitOfMeasure__m3_x002fs2 = 1072,
		eml21__UnitOfMeasure__m3_x002ft = 1073,
		eml21__UnitOfMeasure__m3_x002fton_x005bUK_x005d = 1074,
		eml21__UnitOfMeasure__m3_x002fton_x005bUS_x005d = 1075,
		eml21__UnitOfMeasure__m4 = 1076,
		eml21__UnitOfMeasure__m4_x002fs = 1077,
		eml21__UnitOfMeasure__mA = 1078,
		eml21__UnitOfMeasure__MA = 1079,
		eml21__UnitOfMeasure__mA_x002fcm2 = 1080,
		eml21__UnitOfMeasure__mA_x002fft2 = 1081,
		eml21__UnitOfMeasure__Ma_x005bt_x005d = 1082,
		eml21__UnitOfMeasure__mbar = 1083,
		eml21__UnitOfMeasure__MBq = 1084,
		eml21__UnitOfMeasure__mC = 1085,
		eml21__UnitOfMeasure__MC = 1086,
		eml21__UnitOfMeasure__mC_x002fm2 = 1087,
		eml21__UnitOfMeasure__mcal_x005bth_x005d = 1088,
		eml21__UnitOfMeasure__Mcal_x005bth_x005d = 1089,
		eml21__UnitOfMeasure__mCi = 1090,
		eml21__UnitOfMeasure__mD = 1091,
		eml21__UnitOfMeasure__mD_x002eft = 1092,
		eml21__UnitOfMeasure__mD_x002eft2_x002f_x0028lbf_x002es_x0029 = 1093,
		eml21__UnitOfMeasure__mD_x002ein2_x002f_x0028lbf_x002es_x0029 = 1094,
		eml21__UnitOfMeasure__mD_x002em = 1095,
		eml21__UnitOfMeasure__mD_x002f_x0028Pa_x002es_x0029 = 1096,
		eml21__UnitOfMeasure__mD_x002fcP = 1097,
		eml21__UnitOfMeasure__MEuc = 1098,
		eml21__UnitOfMeasure__mEuc = 1099,
		eml21__UnitOfMeasure__meV = 1100,
		eml21__UnitOfMeasure__MeV = 1101,
		eml21__UnitOfMeasure__MF = 1102,
		eml21__UnitOfMeasure__mF = 1103,
		eml21__UnitOfMeasure__mg = 1104,
		eml21__UnitOfMeasure__Mg = 1105,
		eml21__UnitOfMeasure__Mg_x002fa = 1106,
		eml21__UnitOfMeasure__Mg_x002fd = 1107,
		eml21__UnitOfMeasure__mg_x002fdm3 = 1108,
		eml21__UnitOfMeasure__mg_x002fg = 1109,
		eml21__UnitOfMeasure__mg_x002fgal_x005bUS_x005d = 1110,
		eml21__UnitOfMeasure__Mg_x002fh = 1111,
		eml21__UnitOfMeasure__Mg_x002fin = 1112,
		eml21__UnitOfMeasure__mg_x002fJ = 1113,
		eml21__UnitOfMeasure__mg_x002fkg = 1114,
		eml21__UnitOfMeasure__mg_x002fL = 1115,
		eml21__UnitOfMeasure__Mg_x002fm2 = 1116,
		eml21__UnitOfMeasure__mg_x002fm3 = 1117,
		eml21__UnitOfMeasure__Mg_x002fm3 = 1118,
		eml21__UnitOfMeasure__Mg_x002fmin = 1119,
		eml21__UnitOfMeasure__mGal = 1120,
		eml21__UnitOfMeasure__mgauss = 1121,
		eml21__UnitOfMeasure__Mgauss = 1122,
		eml21__UnitOfMeasure__Mgf = 1123,
		eml21__UnitOfMeasure__mgn = 1124,
		eml21__UnitOfMeasure__MGy = 1125,
		eml21__UnitOfMeasure__mGy = 1126,
		eml21__UnitOfMeasure__mH = 1127,
		eml21__UnitOfMeasure__MH = 1128,
		eml21__UnitOfMeasure__mHz = 1129,
		eml21__UnitOfMeasure__MHz = 1130,
		eml21__UnitOfMeasure__mi = 1131,
		eml21__UnitOfMeasure__mi_x002fgal_x005bUK_x005d = 1132,
		eml21__UnitOfMeasure__mi_x002fgal_x005bUS_x005d = 1133,
		eml21__UnitOfMeasure__mi_x002fh = 1134,
		eml21__UnitOfMeasure__mi_x002fin = 1135,
		eml21__UnitOfMeasure__mi_x005bnaut_x005d = 1136,
		eml21__UnitOfMeasure__mi_x005bnautUK_x005d = 1137,
		eml21__UnitOfMeasure__mi_x005bUS_x005d = 1138,
		eml21__UnitOfMeasure__mi_x005bUS_x005d2 = 1139,
		eml21__UnitOfMeasure__mi2 = 1140,
		eml21__UnitOfMeasure__mi3 = 1141,
		eml21__UnitOfMeasure__Mibyte = 1142,
		eml21__UnitOfMeasure__mil = 1143,
		eml21__UnitOfMeasure__mil_x002fa = 1144,
		eml21__UnitOfMeasure__mila = 1145,
		eml21__UnitOfMeasure__min_ = 1146,
		eml21__UnitOfMeasure__min_x002fft = 1147,
		eml21__UnitOfMeasure__min_x002fm = 1148,
		eml21__UnitOfMeasure__mina = 1149,
		eml21__UnitOfMeasure__mJ = 1150,
		eml21__UnitOfMeasure__MJ = 1151,
		eml21__UnitOfMeasure__MJ_x002fa = 1152,
		eml21__UnitOfMeasure__mJ_x002fcm2 = 1153,
		eml21__UnitOfMeasure__MJ_x002fkg = 1154,
		eml21__UnitOfMeasure__MJ_x002fkmol = 1155,
		eml21__UnitOfMeasure__MJ_x002fm = 1156,
		eml21__UnitOfMeasure__mJ_x002fm2 = 1157,
		eml21__UnitOfMeasure__MJ_x002fm3 = 1158,
		eml21__UnitOfMeasure__mL = 1159,
		eml21__UnitOfMeasure__mL_x002fgal_x005bUK_x005d = 1160,
		eml21__UnitOfMeasure__mL_x002fgal_x005bUS_x005d = 1161,
		eml21__UnitOfMeasure__mL_x002fmL = 1162,
		eml21__UnitOfMeasure__mm = 1163,
		eml21__UnitOfMeasure__Mm = 1164,
		eml21__UnitOfMeasure__mm_x002f_x0028mm_x002eK_x0029 = 1165,
		eml21__UnitOfMeasure__mm_x002fa = 1166,
		eml21__UnitOfMeasure__mm_x002fs = 1167,
		eml21__UnitOfMeasure__mm2 = 1168,
		eml21__UnitOfMeasure__mm2_x002fmm2 = 1169,
		eml21__UnitOfMeasure__mm2_x002fs = 1170,
		eml21__UnitOfMeasure__mm3 = 1171,
		eml21__UnitOfMeasure__mm3_x002fJ = 1172,
		eml21__UnitOfMeasure__mmHg_x005b0degC_x005d = 1173,
		eml21__UnitOfMeasure__mmol = 1174,
		eml21__UnitOfMeasure__MN = 1175,
		eml21__UnitOfMeasure__mN = 1176,
		eml21__UnitOfMeasure__mN_x002em2 = 1177,
		eml21__UnitOfMeasure__mN_x002fkm = 1178,
		eml21__UnitOfMeasure__mN_x002fm = 1179,
		eml21__UnitOfMeasure__Mohm = 1180,
		eml21__UnitOfMeasure__mohm = 1181,
		eml21__UnitOfMeasure__mol = 1182,
		eml21__UnitOfMeasure__mol_x002em2_x002f_x0028mol_x002es_x0029 = 1183,
		eml21__UnitOfMeasure__mol_x002f_x0028s_x002em2_x0029 = 1184,
		eml21__UnitOfMeasure__mol_x002fm2 = 1185,
		eml21__UnitOfMeasure__mol_x002fm3 = 1186,
		eml21__UnitOfMeasure__mol_x002fmol = 1187,
		eml21__UnitOfMeasure__mol_x002fs = 1188,
		eml21__UnitOfMeasure__MP = 1189,
		eml21__UnitOfMeasure__mP = 1190,
		eml21__UnitOfMeasure__mPa = 1191,
		eml21__UnitOfMeasure__MPa = 1192,
		eml21__UnitOfMeasure__mPa_x002es = 1193,
		eml21__UnitOfMeasure__MPa_x002es_x002fm = 1194,
		eml21__UnitOfMeasure__MPa_x002fh = 1195,
		eml21__UnitOfMeasure__MPa_x002fm = 1196,
		eml21__UnitOfMeasure__Mpsi = 1197,
		eml21__UnitOfMeasure__Mrad = 1198,
		eml21__UnitOfMeasure__mrad = 1199,
		eml21__UnitOfMeasure__mrd = 1200,
		eml21__UnitOfMeasure__Mrd = 1201,
		eml21__UnitOfMeasure__mrem = 1202,
		eml21__UnitOfMeasure__mrem_x002fh = 1203,
		eml21__UnitOfMeasure__ms = 1204,
		eml21__UnitOfMeasure__MS = 1205,
		eml21__UnitOfMeasure__mS = 1206,
		eml21__UnitOfMeasure__mS_x002fcm = 1207,
		eml21__UnitOfMeasure__ms_x002fcm = 1208,
		eml21__UnitOfMeasure__ms_x002fft = 1209,
		eml21__UnitOfMeasure__ms_x002fin = 1210,
		eml21__UnitOfMeasure__mS_x002fm = 1211,
		eml21__UnitOfMeasure__ms_x002fm = 1212,
		eml21__UnitOfMeasure__ms_x002fs = 1213,
		eml21__UnitOfMeasure__mSv = 1214,
		eml21__UnitOfMeasure__mSv_x002fh = 1215,
		eml21__UnitOfMeasure__mT = 1216,
		eml21__UnitOfMeasure__mT_x002fdm = 1217,
		eml21__UnitOfMeasure__MV = 1218,
		eml21__UnitOfMeasure__mV = 1219,
		eml21__UnitOfMeasure__mV_x002fft = 1220,
		eml21__UnitOfMeasure__mV_x002fm = 1221,
		eml21__UnitOfMeasure__mW = 1222,
		eml21__UnitOfMeasure__MW = 1223,
		eml21__UnitOfMeasure__MW_x002eh = 1224,
		eml21__UnitOfMeasure__MW_x002eh_x002fkg = 1225,
		eml21__UnitOfMeasure__MW_x002eh_x002fm3 = 1226,
		eml21__UnitOfMeasure__mW_x002fm2 = 1227,
		eml21__UnitOfMeasure__MWb = 1228,
		eml21__UnitOfMeasure__mWb = 1229,
		eml21__UnitOfMeasure__N_x002em = 1230,
		eml21__UnitOfMeasure__N_x002em_x002fm = 1231,
		eml21__UnitOfMeasure__N_x002em2 = 1232,
		eml21__UnitOfMeasure__N_x002es_x002fm2 = 1233,
		eml21__UnitOfMeasure__N_x002fm = 1234,
		eml21__UnitOfMeasure__N_x002fm2 = 1235,
		eml21__UnitOfMeasure__N_x002fm3 = 1236,
		eml21__UnitOfMeasure__N_x002fmm2 = 1237,
		eml21__UnitOfMeasure__N_x002fN = 1238,
		eml21__UnitOfMeasure__na = 1239,
		eml21__UnitOfMeasure__nA = 1240,
		eml21__UnitOfMeasure__nAPI = 1241,
		eml21__UnitOfMeasure__nC = 1242,
		eml21__UnitOfMeasure__ncal_x005bth_x005d = 1243,
		eml21__UnitOfMeasure__nCi = 1244,
		eml21__UnitOfMeasure__nEuc = 1245,
		eml21__UnitOfMeasure__neV = 1246,
		eml21__UnitOfMeasure__nF = 1247,
		eml21__UnitOfMeasure__ng = 1248,
		eml21__UnitOfMeasure__ng_x002fg = 1249,
		eml21__UnitOfMeasure__ng_x002fmg = 1250,
		eml21__UnitOfMeasure__ngauss = 1251,
		eml21__UnitOfMeasure__nGy = 1252,
		eml21__UnitOfMeasure__nH = 1253,
		eml21__UnitOfMeasure__nHz = 1254,
		eml21__UnitOfMeasure__nJ = 1255,
		eml21__UnitOfMeasure__nm = 1256,
		eml21__UnitOfMeasure__nm_x002fs = 1257,
		eml21__UnitOfMeasure__nN = 1258,
		eml21__UnitOfMeasure__nohm = 1259,
		eml21__UnitOfMeasure__nohm_x002emil2_x002fft = 1260,
		eml21__UnitOfMeasure__nohm_x002emm2_x002fm = 1261,
		eml21__UnitOfMeasure__nP = 1262,
		eml21__UnitOfMeasure__nPa = 1263,
		eml21__UnitOfMeasure__nrd = 1264,
		eml21__UnitOfMeasure__ns = 1265,
		eml21__UnitOfMeasure__nS = 1266,
		eml21__UnitOfMeasure__ns_x002fft = 1267,
		eml21__UnitOfMeasure__ns_x002fm = 1268,
		eml21__UnitOfMeasure__nT = 1269,
		eml21__UnitOfMeasure__nV = 1270,
		eml21__UnitOfMeasure__nW = 1271,
		eml21__UnitOfMeasure__nWb = 1272,
		eml21__UnitOfMeasure__Oe = 1273,
		eml21__UnitOfMeasure__ohm = 1274,
		eml21__UnitOfMeasure__ohm_x002ecm = 1275,
		eml21__UnitOfMeasure__ohm_x002em = 1276,
		eml21__UnitOfMeasure__ohm_x002em2_x002fm = 1277,
		eml21__UnitOfMeasure__ohm_x002fm = 1278,
		eml21__UnitOfMeasure__ozf = 1279,
		eml21__UnitOfMeasure__ozm = 1280,
		eml21__UnitOfMeasure__ozm_x005btroy_x005d = 1281,
		eml21__UnitOfMeasure__Pa = 1282,
		eml21__UnitOfMeasure__pA = 1283,
		eml21__UnitOfMeasure__Pa_x002es = 1284,
		eml21__UnitOfMeasure__Pa_x002es_x002em3_x002fkg = 1285,
		eml21__UnitOfMeasure__Pa_x002es_x002fm3 = 1286,
		eml21__UnitOfMeasure__Pa_x002es2_x002fm3 = 1287,
		eml21__UnitOfMeasure__Pa_x002fh = 1288,
		eml21__UnitOfMeasure__Pa_x002fm = 1289,
		eml21__UnitOfMeasure__Pa_x002fm3 = 1290,
		eml21__UnitOfMeasure__Pa_x002fs = 1291,
		eml21__UnitOfMeasure__Pa2 = 1292,
		eml21__UnitOfMeasure__Pa2_x002f_x0028Pa_x002es_x0029 = 1293,
		eml21__UnitOfMeasure__pC = 1294,
		eml21__UnitOfMeasure__pcal_x005bth_x005d = 1295,
		eml21__UnitOfMeasure__pCi = 1296,
		eml21__UnitOfMeasure__pCi_x002fg = 1297,
		eml21__UnitOfMeasure__pdl = 1298,
		eml21__UnitOfMeasure__pdl_x002ecm2 = 1299,
		eml21__UnitOfMeasure__pdl_x002eft = 1300,
		eml21__UnitOfMeasure__pdl_x002fcm = 1301,
		eml21__UnitOfMeasure__pEuc = 1302,
		eml21__UnitOfMeasure__peV = 1303,
		eml21__UnitOfMeasure__pF = 1304,
		eml21__UnitOfMeasure__pg = 1305,
		eml21__UnitOfMeasure__pgauss = 1306,
		eml21__UnitOfMeasure__pGy = 1307,
		eml21__UnitOfMeasure__pHz = 1308,
		eml21__UnitOfMeasure__pJ = 1309,
		eml21__UnitOfMeasure__pm = 1310,
		eml21__UnitOfMeasure__pN = 1311,
		eml21__UnitOfMeasure__pohm = 1312,
		eml21__UnitOfMeasure__pP = 1313,
		eml21__UnitOfMeasure__pPa = 1314,
		eml21__UnitOfMeasure__ppk = 1315,
		eml21__UnitOfMeasure__ppm = 1316,
		eml21__UnitOfMeasure__ppm_x005bmass_x005d = 1317,
		eml21__UnitOfMeasure__ppm_x005bvol_x005d = 1318,
		eml21__UnitOfMeasure__ppm_x005bvol_x005d_x002fdegC = 1319,
		eml21__UnitOfMeasure__ppm_x005bvol_x005d_x002fdegF = 1320,
		eml21__UnitOfMeasure__prd = 1321,
		eml21__UnitOfMeasure__pS = 1322,
		eml21__UnitOfMeasure__ps = 1323,
		eml21__UnitOfMeasure__psi = 1324,
		eml21__UnitOfMeasure__psi_x002ed_x002fbbl = 1325,
		eml21__UnitOfMeasure__psi_x002es = 1326,
		eml21__UnitOfMeasure__psi_x002fft = 1327,
		eml21__UnitOfMeasure__psi_x002fh = 1328,
		eml21__UnitOfMeasure__psi_x002fm = 1329,
		eml21__UnitOfMeasure__psi_x002fmin = 1330,
		eml21__UnitOfMeasure__psi2 = 1331,
		eml21__UnitOfMeasure__psi2_x002ed_x002f_x0028cP_x002eft3_x0029 = 1332,
		eml21__UnitOfMeasure__psi2_x002fcP = 1333,
		eml21__UnitOfMeasure__pT = 1334,
		eml21__UnitOfMeasure__pt_x005bUK_x005d = 1335,
		eml21__UnitOfMeasure__pt_x005bUK_x005d_x002f_x0028hp_x002eh_x0029 = 1336,
		eml21__UnitOfMeasure__pt_x005bUS_x005d = 1337,
		eml21__UnitOfMeasure__pV = 1338,
		eml21__UnitOfMeasure__pW = 1339,
		eml21__UnitOfMeasure__pWb = 1340,
		eml21__UnitOfMeasure__qt_x005bUK_x005d = 1341,
		eml21__UnitOfMeasure__qt_x005bUS_x005d = 1342,
		eml21__UnitOfMeasure__quad = 1343,
		eml21__UnitOfMeasure__quad_x002fa = 1344,
		eml21__UnitOfMeasure__rad = 1345,
		eml21__UnitOfMeasure__rad_x002fft = 1346,
		eml21__UnitOfMeasure__rad_x002fft3 = 1347,
		eml21__UnitOfMeasure__rad_x002fm = 1348,
		eml21__UnitOfMeasure__rad_x002fm3 = 1349,
		eml21__UnitOfMeasure__rad_x002fs = 1350,
		eml21__UnitOfMeasure__rad_x002fs2 = 1351,
		eml21__UnitOfMeasure__rd = 1352,
		eml21__UnitOfMeasure__rem = 1353,
		eml21__UnitOfMeasure__rem_x002fh = 1354,
		eml21__UnitOfMeasure__rev = 1355,
		eml21__UnitOfMeasure__rev_x002fft = 1356,
		eml21__UnitOfMeasure__rev_x002fm = 1357,
		eml21__UnitOfMeasure__rev_x002fs = 1358,
		eml21__UnitOfMeasure__rod_x005bUS_x005d = 1359,
		eml21__UnitOfMeasure__rpm = 1360,
		eml21__UnitOfMeasure__rpm_x002fs = 1361,
		eml21__UnitOfMeasure__s_x002fcm = 1362,
		eml21__UnitOfMeasure__s_x002fft = 1363,
		eml21__UnitOfMeasure__s_x002fft3 = 1364,
		eml21__UnitOfMeasure__s_x002fin = 1365,
		eml21__UnitOfMeasure__s_x002fkg = 1366,
		eml21__UnitOfMeasure__s_x002fL = 1367,
		eml21__UnitOfMeasure__s_x002fm = 1368,
		eml21__UnitOfMeasure__S_x002fm = 1369,
		eml21__UnitOfMeasure__s_x002fm3 = 1370,
		eml21__UnitOfMeasure__s_x002fqt_x005bUK_x005d = 1371,
		eml21__UnitOfMeasure__s_x002fqt_x005bUS_x005d = 1372,
		eml21__UnitOfMeasure__s_x002fs = 1373,
		eml21__UnitOfMeasure__sack_x005b94lbm_x005d = 1374,
		eml21__UnitOfMeasure__seca = 1375,
		eml21__UnitOfMeasure__section = 1376,
		eml21__UnitOfMeasure__sr = 1377,
		eml21__UnitOfMeasure__St = 1378,
		eml21__UnitOfMeasure__Sv = 1379,
		eml21__UnitOfMeasure__Sv_x002fh = 1380,
		eml21__UnitOfMeasure__Sv_x002fs = 1381,
		eml21__UnitOfMeasure__t_x002fa = 1382,
		eml21__UnitOfMeasure__t_x002fd = 1383,
		eml21__UnitOfMeasure__t_x002fh = 1384,
		eml21__UnitOfMeasure__T_x002fm = 1385,
		eml21__UnitOfMeasure__t_x002fm3 = 1386,
		eml21__UnitOfMeasure__t_x002fmin = 1387,
		eml21__UnitOfMeasure__TA = 1388,
		eml21__UnitOfMeasure__Ta_x005bt_x005d = 1389,
		eml21__UnitOfMeasure__TBq = 1390,
		eml21__UnitOfMeasure__TC = 1391,
		eml21__UnitOfMeasure__Tcal_x005bth_x005d = 1392,
		eml21__UnitOfMeasure__TD_x005bAPI_x005d = 1393,
		eml21__UnitOfMeasure__TD_x005bAPI_x005d_x002em = 1394,
		eml21__UnitOfMeasure__TD_x005bAPI_x005d_x002f_x0028Pa_x002es_x0029 = 1395,
		eml21__UnitOfMeasure__TEuc = 1396,
		eml21__UnitOfMeasure__TeV = 1397,
		eml21__UnitOfMeasure__TF = 1398,
		eml21__UnitOfMeasure__Tg = 1399,
		eml21__UnitOfMeasure__Tgauss = 1400,
		eml21__UnitOfMeasure__TGy = 1401,
		eml21__UnitOfMeasure__TH = 1402,
		eml21__UnitOfMeasure__therm_x005bEC_x005d = 1403,
		eml21__UnitOfMeasure__therm_x005bUK_x005d = 1404,
		eml21__UnitOfMeasure__therm_x005bUS_x005d = 1405,
		eml21__UnitOfMeasure__THz = 1406,
		eml21__UnitOfMeasure__TJ = 1407,
		eml21__UnitOfMeasure__TJ_x002fa = 1408,
		eml21__UnitOfMeasure__Tm = 1409,
		eml21__UnitOfMeasure__TN = 1410,
		eml21__UnitOfMeasure__Tohm = 1411,
		eml21__UnitOfMeasure__ton_x005bUK_x005d = 1412,
		eml21__UnitOfMeasure__ton_x005bUK_x005d_x002fa = 1413,
		eml21__UnitOfMeasure__ton_x005bUK_x005d_x002fd = 1414,
		eml21__UnitOfMeasure__ton_x005bUK_x005d_x002fh = 1415,
		eml21__UnitOfMeasure__ton_x005bUK_x005d_x002fmin = 1416,
		eml21__UnitOfMeasure__ton_x005bUS_x005d = 1417,
		eml21__UnitOfMeasure__ton_x005bUS_x005d_x002fa = 1418,
		eml21__UnitOfMeasure__ton_x005bUS_x005d_x002fd = 1419,
		eml21__UnitOfMeasure__ton_x005bUS_x005d_x002fft2 = 1420,
		eml21__UnitOfMeasure__ton_x005bUS_x005d_x002fh = 1421,
		eml21__UnitOfMeasure__ton_x005bUS_x005d_x002fmin = 1422,
		eml21__UnitOfMeasure__tonf_x005bUK_x005d = 1423,
		eml21__UnitOfMeasure__tonf_x005bUK_x005d_x002eft2 = 1424,
		eml21__UnitOfMeasure__tonf_x005bUK_x005d_x002fft = 1425,
		eml21__UnitOfMeasure__tonf_x005bUK_x005d_x002fft2 = 1426,
		eml21__UnitOfMeasure__tonf_x005bUS_x005d = 1427,
		eml21__UnitOfMeasure__tonf_x005bUS_x005d_x002eft = 1428,
		eml21__UnitOfMeasure__tonf_x005bUS_x005d_x002eft2 = 1429,
		eml21__UnitOfMeasure__tonf_x005bUS_x005d_x002emi = 1430,
		eml21__UnitOfMeasure__tonf_x005bUS_x005d_x002emi_x002fbbl = 1431,
		eml21__UnitOfMeasure__tonf_x005bUS_x005d_x002emi_x002fft = 1432,
		eml21__UnitOfMeasure__tonf_x005bUS_x005d_x002fft = 1433,
		eml21__UnitOfMeasure__tonf_x005bUS_x005d_x002fft2 = 1434,
		eml21__UnitOfMeasure__tonf_x005bUS_x005d_x002fin2 = 1435,
		eml21__UnitOfMeasure__tonRefrig = 1436,
		eml21__UnitOfMeasure__torr = 1437,
		eml21__UnitOfMeasure__TP = 1438,
		eml21__UnitOfMeasure__TPa = 1439,
		eml21__UnitOfMeasure__Trd = 1440,
		eml21__UnitOfMeasure__TS = 1441,
		eml21__UnitOfMeasure__TT = 1442,
		eml21__UnitOfMeasure__TV = 1443,
		eml21__UnitOfMeasure__TW = 1444,
		eml21__UnitOfMeasure__TW_x002eh = 1445,
		eml21__UnitOfMeasure__TWb = 1446,
		eml21__UnitOfMeasure__uA = 1447,
		eml21__UnitOfMeasure__uA_x002fcm2 = 1448,
		eml21__UnitOfMeasure__uA_x002fin2 = 1449,
		eml21__UnitOfMeasure__ubar = 1450,
		eml21__UnitOfMeasure__uC = 1451,
		eml21__UnitOfMeasure__ucal_x005bth_x005d = 1452,
		eml21__UnitOfMeasure__ucal_x005bth_x005d_x002f_x0028s_x002ecm2_x0029 = 1453,
		eml21__UnitOfMeasure__ucal_x005bth_x005d_x002fs = 1454,
		eml21__UnitOfMeasure__uCi = 1455,
		eml21__UnitOfMeasure__uEuc = 1456,
		eml21__UnitOfMeasure__ueV = 1457,
		eml21__UnitOfMeasure__uF = 1458,
		eml21__UnitOfMeasure__uF_x002fm = 1459,
		eml21__UnitOfMeasure__ug = 1460,
		eml21__UnitOfMeasure__ug_x002fcm3 = 1461,
		eml21__UnitOfMeasure__ug_x002fg = 1462,
		eml21__UnitOfMeasure__ug_x002fmg = 1463,
		eml21__UnitOfMeasure__ugauss = 1464,
		eml21__UnitOfMeasure__uGy = 1465,
		eml21__UnitOfMeasure__uH = 1466,
		eml21__UnitOfMeasure__uH_x002fm = 1467,
		eml21__UnitOfMeasure__uHz = 1468,
		eml21__UnitOfMeasure__uJ = 1469,
		eml21__UnitOfMeasure__um = 1470,
		eml21__UnitOfMeasure__um_x002fs = 1471,
		eml21__UnitOfMeasure__um2 = 1472,
		eml21__UnitOfMeasure__um2_x002em = 1473,
		eml21__UnitOfMeasure__umHg_x005b0degC_x005d = 1474,
		eml21__UnitOfMeasure__umol = 1475,
		eml21__UnitOfMeasure__uN = 1476,
		eml21__UnitOfMeasure__uohm = 1477,
		eml21__UnitOfMeasure__uohm_x002fft = 1478,
		eml21__UnitOfMeasure__uohm_x002fm = 1479,
		eml21__UnitOfMeasure__uP = 1480,
		eml21__UnitOfMeasure__uPa = 1481,
		eml21__UnitOfMeasure__upsi = 1482,
		eml21__UnitOfMeasure__urad = 1483,
		eml21__UnitOfMeasure__urd = 1484,
		eml21__UnitOfMeasure__us = 1485,
		eml21__UnitOfMeasure__uS = 1486,
		eml21__UnitOfMeasure__us_x002fft = 1487,
		eml21__UnitOfMeasure__us_x002fin = 1488,
		eml21__UnitOfMeasure__us_x002fm = 1489,
		eml21__UnitOfMeasure__uT = 1490,
		eml21__UnitOfMeasure__uV = 1491,
		eml21__UnitOfMeasure__uV_x002fft = 1492,
		eml21__UnitOfMeasure__uV_x002fm = 1493,
		eml21__UnitOfMeasure__uW = 1494,
		eml21__UnitOfMeasure__uW_x002fm3 = 1495,
		eml21__UnitOfMeasure__uWb = 1496,
		eml21__UnitOfMeasure__V_x002fB = 1497,
		eml21__UnitOfMeasure__V_x002fdB = 1498,
		eml21__UnitOfMeasure__V_x002fm = 1499,
		eml21__UnitOfMeasure__W_x002em2_x002eK_x002f_x0028J_x002eK_x0029 = 1500,
		eml21__UnitOfMeasure__W_x002f_x0028m_x002eK_x0029 = 1501,
		eml21__UnitOfMeasure__W_x002f_x0028m2_x002eK_x0029 = 1502,
		eml21__UnitOfMeasure__W_x002f_x0028m2_x002esr_x0029 = 1503,
		eml21__UnitOfMeasure__W_x002f_x0028m3_x002eK_x0029 = 1504,
		eml21__UnitOfMeasure__W_x002fcm2 = 1505,
		eml21__UnitOfMeasure__W_x002fK = 1506,
		eml21__UnitOfMeasure__W_x002fkW = 1507,
		eml21__UnitOfMeasure__W_x002fm2 = 1508,
		eml21__UnitOfMeasure__W_x002fm3 = 1509,
		eml21__UnitOfMeasure__W_x002fmm2 = 1510,
		eml21__UnitOfMeasure__W_x002fsr = 1511,
		eml21__UnitOfMeasure__W_x002fW = 1512,
		eml21__UnitOfMeasure__Wb = 1513,
		eml21__UnitOfMeasure__Wb_x002em = 1514,
		eml21__UnitOfMeasure__Wb_x002fm = 1515,
		eml21__UnitOfMeasure__Wb_x002fmm = 1516,
		eml21__UnitOfMeasure__wk = 1517,
		eml21__UnitOfMeasure__yd = 1518,
		eml21__UnitOfMeasure__yd_x005bBnA_x005d = 1519,
		eml21__UnitOfMeasure__yd_x005bBnB_x005d = 1520,
		eml21__UnitOfMeasure__yd_x005bCla_x005d = 1521,
		eml21__UnitOfMeasure__yd_x005bInd_x005d = 1522,
		eml21__UnitOfMeasure__yd_x005bInd37_x005d = 1523,
		eml21__UnitOfMeasure__yd_x005bInd62_x005d = 1524,
		eml21__UnitOfMeasure__yd_x005bInd75_x005d = 1525,
		eml21__UnitOfMeasure__yd_x005bSe_x005d = 1526,
		eml21__UnitOfMeasure__yd_x005bSeT_x005d = 1527,
		eml21__UnitOfMeasure__yd_x005bUS_x005d = 1528,
		eml21__UnitOfMeasure__yd2 = 1529,
		eml21__UnitOfMeasure__yd3 = 1530
	};
	enum eml21__AnglePerLengthUom {
		eml21__AnglePerLengthUom__0_x002e01_x0020dega_x002fft = 0,
		eml21__AnglePerLengthUom__1_x002f30_x0020dega_x002fft = 1,
		eml21__AnglePerLengthUom__1_x002f30_x0020dega_x002fm = 2,
		eml21__AnglePerLengthUom__dega_x002fft = 3,
		eml21__AnglePerLengthUom__dega_x002fm = 4,
		eml21__AnglePerLengthUom__rad_x002fft = 5,
		eml21__AnglePerLengthUom__rad_x002fm = 6,
		eml21__AnglePerLengthUom__rev_x002fft = 7,
		eml21__AnglePerLengthUom__rev_x002fm = 8
	};
	enum eml21__LengthUom { eml21__LengthUom__m = 'm', eml21__LengthUom__0_x002e1_x0020ft = 'n', eml21__LengthUom__0_x002e1_x0020ft_x005bUS_x005d = 'o', eml21__LengthUom__0_x002e1_x0020in = 'p', eml21__LengthUom__0_x002e1_x0020yd = 'q', eml21__LengthUom__1_x002f16_x0020in = 'r', eml21__LengthUom__1_x002f2_x0020ft = 's', eml21__LengthUom__1_x002f32_x0020in = 't', eml21__LengthUom__1_x002f64_x0020in = 'u', eml21__LengthUom__10_x0020ft = 'v', eml21__LengthUom__10_x0020in = 'w', eml21__LengthUom__10_x0020km = 'x', eml21__LengthUom__100_x0020ft = 'y', eml21__LengthUom__100_x0020km = 'z', eml21__LengthUom__1000_x0020ft = 123, eml21__LengthUom__30_x0020ft = 124, eml21__LengthUom__30_x0020m = 125, eml21__LengthUom__angstrom = 126, eml21__LengthUom__chain = 127, eml21__LengthUom__chain_x005bBnA_x005d = 128, eml21__LengthUom__chain_x005bBnB_x005d = 129, eml21__LengthUom__chain_x005bCla_x005d = 130, eml21__LengthUom__chain_x005bInd37_x005d = 131, eml21__LengthUom__chain_x005bSe_x005d = 132, eml21__LengthUom__chain_x005bSeT_x005d = 133, eml21__LengthUom__chain_x005bUS_x005d = 134, eml21__LengthUom__cm = 135, eml21__LengthUom__dam = 136, eml21__LengthUom__dm = 137, eml21__LengthUom__Em = 138, eml21__LengthUom__fathom = 139, eml21__LengthUom__fm = 140, eml21__LengthUom__ft = 141, eml21__LengthUom__ft_x005bBnA_x005d = 142, eml21__LengthUom__ft_x005bBnB_x005d = 143, eml21__LengthUom__ft_x005bBr36_x005d = 144, eml21__LengthUom__ft_x005bBr65_x005d = 145, eml21__LengthUom__ft_x005bCla_x005d = 146, eml21__LengthUom__ft_x005bGC_x005d = 147, eml21__LengthUom__ft_x005bInd_x005d = 148, eml21__LengthUom__ft_x005bInd37_x005d = 149, eml21__LengthUom__ft_x005bInd62_x005d = 150, eml21__LengthUom__ft_x005bInd75_x005d = 151, eml21__LengthUom__ft_x005bSe_x005d = 152, eml21__LengthUom__ft_x005bSeT_x005d = 153, eml21__LengthUom__ft_x005bUS_x005d = 154, eml21__LengthUom__fur_x005bUS_x005d = 155, eml21__LengthUom__Gm = 156, eml21__LengthUom__hm = 157, eml21__LengthUom__in = 158, eml21__LengthUom__in_x005bUS_x005d = 159, eml21__LengthUom__km = 160, eml21__LengthUom__link = 161, eml21__LengthUom__link_x005bBnA_x005d = 162, eml21__LengthUom__link_x005bBnB_x005d = 163, eml21__LengthUom__link_x005bCla_x005d = 164, eml21__LengthUom__link_x005bSe_x005d = 165, eml21__LengthUom__link_x005bSeT_x005d = 166, eml21__LengthUom__link_x005bUS_x005d = 167, eml21__LengthUom__m_x005bGer_x005d = 168, eml21__LengthUom__mi = 169, eml21__LengthUom__mi_x005bnaut_x005d = 170, eml21__LengthUom__mi_x005bnautUK_x005d = 171, eml21__LengthUom__mi_x005bUS_x005d = 172, eml21__LengthUom__mil = 173, eml21__LengthUom__mm = 174, eml21__LengthUom__Mm = 175, eml21__LengthUom__nm = 176, eml21__LengthUom__pm = 177, eml21__LengthUom__rod_x005bUS_x005d = 178, eml21__LengthUom__Tm = 179, eml21__LengthUom__um = 180, eml21__LengthUom__yd = 181, eml21__LengthUom__yd_x005bBnA_x005d = 182, eml21__LengthUom__yd_x005bBnB_x005d = 183, eml21__LengthUom__yd_x005bCla_x005d = 184, eml21__LengthUom__yd_x005bInd_x005d = 185, eml21__LengthUom__yd_x005bInd37_x005d = 186, eml21__LengthUom__yd_x005bInd62_x005d = 187, eml21__LengthUom__yd_x005bInd75_x005d = 188, eml21__LengthUom__yd_x005bSe_x005d = 189, eml21__LengthUom__yd_x005bSeT_x005d = 190, eml21__LengthUom__yd_x005bUS_x005d = 191 };
	enum eml21__LinearAccelerationUom {
		eml21__LinearAccelerationUom__cm_x002fs2 = 0,
		eml21__LinearAccelerationUom__ft_x002fs2 = 1,
		eml21__LinearAccelerationUom__Gal = 2,
		eml21__LinearAccelerationUom__gn = 3,
		eml21__LinearAccelerationUom__in_x002fs2 = 4,
		eml21__LinearAccelerationUom__m_x002fs2 = 5,
		eml21__LinearAccelerationUom__mGal = 6,
		eml21__LinearAccelerationUom__mgn = 7
	};
	enum eml21__MagneticFluxDensityUom {
		eml21__MagneticFluxDensityUom__T = 'T',
		eml21__MagneticFluxDensityUom__cgauss = 'U',
		eml21__MagneticFluxDensityUom__cT = 'V',
		eml21__MagneticFluxDensityUom__dgauss = 'W',
		eml21__MagneticFluxDensityUom__dT = 'X',
		eml21__MagneticFluxDensityUom__Egauss = 'Y',
		eml21__MagneticFluxDensityUom__ET = 'Z',
		eml21__MagneticFluxDensityUom__fgauss = 91,
		eml21__MagneticFluxDensityUom__fT = 92,
		eml21__MagneticFluxDensityUom__gauss = 93,
		eml21__MagneticFluxDensityUom__Ggauss = 94,
		eml21__MagneticFluxDensityUom__GT = 95,
		eml21__MagneticFluxDensityUom__kgauss = 96,
		eml21__MagneticFluxDensityUom__kT = 'a',
		eml21__MagneticFluxDensityUom__mgauss = 'b',
		eml21__MagneticFluxDensityUom__Mgauss = 'c',
		eml21__MagneticFluxDensityUom__mT = 'd',
		eml21__MagneticFluxDensityUom__ngauss = 'e',
		eml21__MagneticFluxDensityUom__nT = 'f',
		eml21__MagneticFluxDensityUom__pgauss = 'g',
		eml21__MagneticFluxDensityUom__pT = 'h',
		eml21__MagneticFluxDensityUom__Tgauss = 'i',
		eml21__MagneticFluxDensityUom__TT = 'j',
		eml21__MagneticFluxDensityUom__ugauss = 'k',
		eml21__MagneticFluxDensityUom__uT = 'l'
	};
	enum eml21__MassPerLengthUom {
		eml21__MassPerLengthUom__kg_x002em_x002fcm2 = 0,
		eml21__MassPerLengthUom__kg_x002fm = 1,
		eml21__MassPerLengthUom__klbm_x002fin = 2,
		eml21__MassPerLengthUom__lbm_x002fft = 3,
		eml21__MassPerLengthUom__Mg_x002fin = 4
	};
	enum eml21__PlaneAngleUom { eml21__PlaneAngleUom__0_x002e001_x0020seca = 0, eml21__PlaneAngleUom__ccgr = 1, eml21__PlaneAngleUom__cgr = 2, eml21__PlaneAngleUom__dega = 3, eml21__PlaneAngleUom__gon = 4, eml21__PlaneAngleUom__krad = 5, eml21__PlaneAngleUom__mila = 6, eml21__PlaneAngleUom__mina = 7, eml21__PlaneAngleUom__Mrad = 8, eml21__PlaneAngleUom__mrad = 9, eml21__PlaneAngleUom__rad = 10, eml21__PlaneAngleUom__rev = 11, eml21__PlaneAngleUom__seca = 12, eml21__PlaneAngleUom__urad = 13 };
	enum eml21__VerticalCoordinateUom { eml21__VerticalCoordinateUom__m = 'm', eml21__VerticalCoordinateUom__ft = 'n', eml21__VerticalCoordinateUom__ftUS = 'o', eml21__VerticalCoordinateUom__ftBr_x002865_x0029 = 'p' };
}

//#ifdef SWIGJAVA
//	%include "swigWitsml2_0JavaInclude.i"
//#endif
#ifdef SWIGPYTHON

#endif
//#ifdef SWIGCSHARP
//	%include "swigWitsml2_0CsInclude.i"
//#endif
#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace WITSML2_0_NS::AbstractObject;
	
	%nspace WITSML2_0_NS::Well;
	%nspace WITSML2_0_NS::WellCompletion;
	
	%nspace WITSML2_0_NS::Wellbore;
	%nspace WITSML2_0_NS::WellboreObject;
	%nspace WITSML2_0_NS::WellboreCompletion;
	%nspace WITSML2_0_NS::WellboreGeometry;
	%nspace WITSML2_0_NS::Trajectory;
	%nspace WITSML2_0_NS::Log;
	%nspace WITSML2_0_NS::ChannelSet;
	%nspace WITSML2_0_NS::Channel;
#endif

namespace WITSML2_0_NS
{
	%nodefaultctor; // Disable creation of default constructors

#ifdef SWIGPYTHON
	%rename(Witsml2_0AbstractObject) AbstractObject;
#endif
	class AbstractObject : public COMMON_NS::AbstractObject
	{
	public:
		std::string getXmlTag() const;
	
		std::string getXmlNamespace() const;

		std::string getContentType() const;

		std::string getPartNameInEpcDocument() const;
	};
	
	class Wellbore;
	class WellCompletion;
	class Well : public AbstractObject
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
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Operator)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, OperatorDiv)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, OriginalOperator)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NumAPI)

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::eml21__WellStatus, StatusWell)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::witsml20__WellPurpose, PurposeWell)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::witsml20__WellFluid, FluidWell)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::witsml20__WellDirection, DirectionWell)

		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(WaterDepth, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(GroundElevation, gsoap_eml2_1::eml21__LengthUom)

		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(PcInterest, gsoap_eml2_1::eml21__DimensionlessUom)

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimLicense)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimSpud)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimPa)
		
		void setTimeZone(bool direction, unsigned short hours, unsigned short minutes = 0);
		GETTER_PRESENCE_ATTRIBUTE(TimeZone)
		bool getTimeZoneDirection() const;
		unsigned short getTimeZoneHours() const;
		unsigned short getTimeZoneMinutes() const;
		
		double getLocationProjectedX(unsigned int locationIndex);
		double getLocationProjectedY(unsigned int locationIndex);
		void pushBackLocation(
			const std::string & guid,
			double projectedX,
			double projectedY,
			unsigned int projectedCrsEpsgCode);
		unsigned int geLocationCount() const;
		
		void pushBackDatum(
			const std::string & guid, 
			const std::string & title,
			gsoap_eml2_1::eml21__WellboreDatumReference code,
			const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom elevationUnit,
			double elevation,
			unsigned int verticalCrsEpsgCode);
		
		unsigned int getDatumCount() const;
		
		std::vector<RESQML2_0_1_NS::WellboreFeature *> getResqmlWellboreFeatures() const;

		std::vector<Wellbore *> getWellbores() const;

		std::vector<WellCompletion *> getWellcompletions() const;
	};
	
	class WellboreCompletion;
	class WellboreGeometry;
	class Trajectory;
	class Wellbore : public AbstractObject 
	{
	public:
		class Well* getWell() const;

		void setWell(class Well* witsmlWell);

		std::vector<RESQML2_0_1_NS::WellboreFeature *> getResqmlWellboreFeature() const;

		std::vector<class WellboreCompletion *> getWellboreCompletions() const;
		std::vector<class Trajectory *> getTrajectories() const;
		std::vector<WellboreGeometry *> getWellboreGeometries() const;

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Number);
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, SuffixAPI);
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NumGovt);
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::eml21__WellStatus, StatusWellbore);
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, IsActive);
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::witsml20__WellPurpose, PurposeWellbore);
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::witsml20__WellboreType, TypeWellbore);
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::witsml20__WellboreShape, Shape);
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, AchievedTD);
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(Md, gsoap_eml2_1::eml21__LengthUom);
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdBit, gsoap_eml2_1::eml21__LengthUom);
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdKickoff, gsoap_eml2_1::eml21__LengthUom);
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdPlanned, gsoap_eml2_1::eml21__LengthUom);
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdSubSeaPlanned, gsoap_eml2_1::eml21__LengthUom);
	};
	
	class WellboreCompletion;
	class WellCompletion : public AbstractObject
	{
	public:
		
		class Well* getWell() const;

		void setWell(class Well* witsmlWell);
		
		std::vector<class WellboreCompletion *> getWellboreCompletions() const;
	};
	
	class WellboreObject : public AbstractObject
	{
	public:
		Wellbore* getWellbore() const;
		virtual void setWellbore(class Wellbore* witsmlWellbore) = 0;
	};
	
	class WellboreCompletion : public WellboreObject
	{
	public:
		class Wellbore* getWellbore() const;

		class WellCompletion* getWellCompletion() const;
		void setWellCompletion(class WellCompletion* wellCompletion);

		void pushBackPerforation(const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom MdUnit,
			double TopMd,
			double BaseMd, 
			const std::string & guid = "");

		void pushBackPerforationHistory(unsigned int index,
			const std::string & guid = "");
			
		void pushBackPerforationHistory(unsigned int index,
			gsoap_eml2_1::witsml20__PerforationStatus perforationStatus,
			time_t startDate,
			const std::string & guid = "");	

		unsigned int getPerforationCount() const;
		
		std::string getPerforationUid(unsigned int index) const;

		bool hasPerforationMdDatum(unsigned int index) const;
	
		std::string getPerforationMdDatum(unsigned int index) const;
		
		bool hasPerforationMdUnit(unsigned int index) const;
		
		gsoap_eml2_1::eml21__LengthUom getPerforationMdUnit(unsigned int index) const;
		
		std::string getPerforationMdUnitAsString(unsigned int index) const;
		
		bool hasPerforationTopMd(unsigned int index) const;
		
		double getPerforationTopMd(unsigned int index) const;

		bool hasPerforationBaseMd(unsigned int index) const;

		double getPerforationBaseMd(unsigned int index) const;

		unsigned int getPerforationHistoryCount(unsigned int index) const;

		bool hasPerforationHistoryStatus(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		gsoap_eml2_1::witsml20__PerforationStatus getPerforationHistoryStatus(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		std::string getPerforationHistoryStatusToString(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		void setPerforationHistoryStatus(unsigned int historyIndex,
			unsigned int perforationIndex, 
			gsoap_eml2_1::witsml20__PerforationStatus perforationStatus);

		bool hasPerforationHistoryStartDate(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		time_t getPerforationHistoryStartDate(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		void setPerforationHistoryStartDate(unsigned int historyIndex,
			unsigned int perforationIndex, time_t startDate) const;

		bool hasPerforationHistoryEndDate(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		time_t getPerforationHistoryEndDate(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		void setPerforationHistoryEndDate(unsigned int historyIndex,
			unsigned int perforationIndex, time_t endDate) const;
		
		bool hasPerforationHistoryMdDatum(unsigned int historyIndex,
			unsigned int perforationIndex) const;
		
		std::string getPerforationHistoryMdDatum(unsigned int historyIndex,
			unsigned int perforationIndex) const;
		
		bool hasPerforationHistoryMdUnit(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		gsoap_eml2_1::eml21__LengthUom getPerforationHistoryMdUnit(unsigned int historyIndex,
			unsigned int perforationIndex) const;
			
		std::string getPerforationHistoryMdUnitAsString(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		bool hasPerforationHistoryTopMd(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		double getPerforationHistoryTopMd(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		void setPerforationHistoryTopMd(unsigned int historyIndex,
			unsigned int perforationIndex,
			const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom MdUnit,
			double TopMd);
		
		bool hasPerforationHistoryBaseMd(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		double getPerforationHistoryBaseMd(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		void setPerforationHistoryBaseMd(unsigned int historyIndex,
			unsigned int perforationIndex,
			const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom MdUnit,
			double BaseMd);
			
		bool hasPerforationHistoryComment(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		std::string getPerforationHistoryComment(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		void setPerforationHistoryComment(unsigned int historyIndex,
			unsigned int perforationIndex,
			const std::string & comment);
	};
	
	class WellboreGeometry : public WellboreObject
	{
	public:
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdBase, gsoap_eml2_1::eml21__LengthUom)

		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(GapAir, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(DepthWaterMean, gsoap_eml2_1::eml21__LengthUom)

		//***************************************
		//************** SECTION ****************
		//***************************************

		// Mandatory
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(std::string, WellboreGeometrySection, uid)

		// Optional bool
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, WellboreGeometrySection, CurveConductor)

		// Optional double
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(double, WellboreGeometrySection, FactFric)

		// Optional string
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(std::string, WellboreGeometrySection, Grade)

		// Optional enum
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_1::witsml20__HoleCasingType, WellboreGeometrySection, TypeHoleCasing)

		// Optional Length Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, IdSection, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, OdSection, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, DiaDrift, gsoap_eml2_1::eml21__LengthUom)

		// Optional Mass per Length Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, WtPerLen, gsoap_eml2_1::eml21__MassPerLengthUom)

		void setWellboreGeometrySectionMdInterval(unsigned int index, double top, double base, const std::string & datum, gsoap_eml2_1::eml21__LengthUom uom);
		double getWellboreGeometrySectionMdIntervalTop(unsigned int index) const;
		gsoap_eml2_1::eml21__LengthUom getWellboreGeometrySectionMdIntervalTopUom(unsigned int index) const;
		double getWellboreGeometrySectionMdIntervalBase(unsigned int index) const;
		gsoap_eml2_1::eml21__LengthUom getWellboreGeometrySectionMdIntervalBaseUom(unsigned int index) const;
		std::string getWellboreGeometrySectionMdIntervaldatum(unsigned int index) const;
		bool hasWellboreGeometrySectionMdInterval(unsigned int index) const;

		void setWellboreGeometrySectionTvdInterval(unsigned int index, double top, double base, const std::string & datum, gsoap_eml2_1::eml21__LengthUom uom);
		double getWellboreGeometrySectionTvdIntervalTop(unsigned int index) const;
		gsoap_eml2_1::eml21__LengthUom getWellboreGeometrySectionTvdIntervalTopUom(unsigned int index) const;
		double getWellboreGeometrySectionTvdIntervalBase(unsigned int index) const;
		gsoap_eml2_1::eml21__LengthUom getWellboreGeometrySectionTvdIntervalBaseUom(unsigned int index) const;
		std::string getWellboreGeometrySectionTvdIntervaldatum(unsigned int index) const;
		bool hasWellboreGeometrySectionTvdInterval(unsigned int index) const;

		void pushBackSection(const std::string & uid = "");
		unsigned int getSectionCount() const;
	};
	
	class Trajectory : public WellboreObject
	{
	public:
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(gsoap_eml2_1::witsml20__ChannelStatus, GrowingStatus)

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimTrajStart)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimTrajEnd)

		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdMn, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdMx, gsoap_eml2_1::eml21__LengthUom)

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, ServiceCompany)

		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(MagDeclUsed, gsoap_eml2_1::eml21__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(GridConUsed, gsoap_eml2_1::eml21__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(AziVertSect, gsoap_eml2_1::eml21__PlaneAngleUom)

		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(DispNsVertSectOrig, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(DispEwVertSectOrig, gsoap_eml2_1::eml21__LengthUom)

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, Definitive)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, Memory)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, FinalTraj)

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::witsml20__AziRef, AziRef)

		//***************************************
		// ******* TRAJECTORY STATIONS **********
		//***************************************

		// Mandatory
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(std::string, TrajectoryStation, uid)
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(gsoap_eml2_1::witsml20__TrajStationType, TrajectoryStation, TypeTrajStation)
		GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Md, gsoap_eml2_1::eml21__LengthUom)

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
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(std::string, TrajectoryStation, Target)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(std::string, TrajectoryStation, MagModelUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(std::string, TrajectoryStation, MagModelValid)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(std::string, TrajectoryStation, GeoModelUsed)

		// Optional timestamp
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(time_t, TrajectoryStation, DTimStn)

		// Optional enum
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_1::witsml20__TypeSurveyTool, TrajectoryStation, TypeSurveyTool)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_1::witsml20__TrajStnCalcAlgorithm, TrajectoryStation, CalcAlgorithm)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_1::witsml20__TrajStationStatus, TrajectoryStation, StatusTrajStation)

		// Optional Length Measure
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Tvd, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, DispNs, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, DispEw, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, VertSect, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, MdDelta, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, TvdDelta, gsoap_eml2_1::eml21__LengthUom)

		// Optional Plane Angle Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Incl, gsoap_eml2_1::eml21__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Azi, gsoap_eml2_1::eml21__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Mtf, gsoap_eml2_1::eml21__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Gtf, gsoap_eml2_1::eml21__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, DipAngleUncert, gsoap_eml2_1::eml21__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, MagDipAngleReference, gsoap_eml2_1::eml21__PlaneAngleUom)

		// Optional Angle per Length Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Dls, gsoap_eml2_1::eml21__AnglePerLengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, RateTurn, gsoap_eml2_1::eml21__AnglePerLengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, RateBuild, gsoap_eml2_1::eml21__AnglePerLengthUom)

		// Optional Linear Acceleration Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, GravTotalUncert, gsoap_eml2_1::eml21__LinearAccelerationUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, GravTotalFieldReference, gsoap_eml2_1::eml21__LinearAccelerationUom)

		// Optional Magnetic Flux Density Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, MagTotalUncert, gsoap_eml2_1::eml21__MagneticFluxDensityUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, MagTotalFieldReference, gsoap_eml2_1::eml21__MagneticFluxDensityUom)

		void pushBackTrajectoryStation(gsoap_eml2_1::witsml20__TrajStationType kind, double mdValue, gsoap_eml2_1::eml21__LengthUom uom, const std::string & datum, const std::string & uid = "");
		unsigned int getTrajectoryStationCount() const;
	};
	
	template <class T>
	class ChannelMetaDataObject : public WellboreObject
	{
	public:

		COMMON_NS::PropertyKind* getPropertyKind() const;
		void setPropertyKind(COMMON_NS::PropertyKind* propKind);
	};
	%template(ChannelMetaDataLog) ChannelMetaDataObject<gsoap_eml2_1::witsml20__Log>;
	%template(ChannelMetaDataChannelSet) ChannelMetaDataObject<gsoap_eml2_1::witsml20__ChannelSet>;
	%template(ChannelMetaDataChannel) ChannelMetaDataObject<gsoap_eml2_1::witsml20__Channel>;
	
	template <class T>
	class ChannelIndexDataObject : public ChannelMetaDataObject<T>
	{
	public:
		virtual void pushBackChannelIndex(gsoap_eml2_1::witsml20__ChannelIndexType indexType, gsoap_eml2_1::eml21__UnitOfMeasure uom, const std::string & mnemonic, bool isIncreasing = true, const std::string & datum = "") = 0;

		unsigned int getChannelIndexCount() const {
			return static_cast<T*>(gsoapProxy2_1)->Index.size();
		}

		gsoap_eml2_1::witsml20__ChannelIndexType getChannelIndexType(unsigned int index) {
			if (index >= getChannelIndexCount()) {
				throw std::out_of_range("The channel index is out of range");
			}
			return static_cast<T*>(gsoapProxy2_1)->Index[index]->IndexType;
		}

		std::string getChannelIndexUom(unsigned int index) {
			if (index >= getChannelIndexCount()) {
				throw std::out_of_range("The channel index is out of range");
			}
			return static_cast<T*>(gsoapProxy2_1)->Index[index]->Uom;
		}

		bool getChannelIndexIsIncreasing(unsigned int index) {
			if (index >= getChannelIndexCount()) {
				throw std::out_of_range("The channel index is out of range");
			}
			return static_cast<T*>(gsoapProxy2_1)->Index[index]->Direction == gsoap_eml2_1::witsml20__IndexDirection__increasing;
		}

		std::string getChannelIndexMnemonic(unsigned int index) {
			if (index >= getChannelIndexCount()) {
				throw std::out_of_range("The channel index is out of range");
			}
			return static_cast<T*>(gsoapProxy2_1)->Index[index]->Mnemonic;
		}

		std::string getChannelIndexDatum(unsigned int index) {
			if (index >= getChannelIndexCount()) {
				throw std::out_of_range("The channel index is out of range");
			}
			return static_cast<T*>(gsoapProxy2_1)->Index[index]->DatumReference == nullptr ? "" : *static_cast<T*>(gsoapProxy2_1)->Index[index]->DatumReference;
		}
	};
	%template(ChannelIndexDataChannelSet) ChannelIndexDataObject<gsoap_eml2_1::witsml20__ChannelSet>;
	%template(ChannelIndexDataChannel) ChannelIndexDataObject<gsoap_eml2_1::witsml20__Channel>;
	
	class ChannelSet;
	class Log : public ChannelMetaDataObject<gsoap_eml2_1::witsml20__Log>
	{
	public:
		void pushBackChannelSet(class ChannelSet * channelSet);
		std::vector<ChannelSet*> getChannelSets() const;
	};
	
	class Channel;
	class ChannelSet : public ChannelIndexDataObject<gsoap_eml2_1::witsml20__ChannelSet>
	{
	public:
		void pushBackChannel(class Channel * channel);

		void setDataAsJsonArray(const std::string & jsonArray);
		void setDataAsFileUri(const std::string & fileUri);

		bool hasDataAsJsonArray() const;
		bool hasDataAsFileUri() const;

		const std::string & getDataAsJsonArray() const;
		const std::string & getDataAsFileUri() const;

		std::vector<class Log*> getLogs() const;
		std::vector<class Channel*> getChannels() const;
	};
	
	class Channel : public ChannelIndexDataObject<gsoap_eml2_1::witsml20__Channel>
	{
	public:
		std::vector<class ChannelSet*> getChannelSets() const;
		COMMON_NS::PropertyKind* getPropertyKind() const;

		gsoap_eml2_1::eml21__DataObjectReference* getPropertyKindDor() const;

		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(std::string, Mnemonic)
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(std::string, Uom)
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(gsoap_eml2_1::witsml20__EtpDataType, DataType)
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(gsoap_eml2_1::witsml20__ChannelStatus, GrowingStatus)
	};
}

