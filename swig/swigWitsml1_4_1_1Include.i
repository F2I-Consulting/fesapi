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
#include "witsml1_4_1_1/Well.h"
#include "witsml1_4_1_1/CoordinateReferenceSystem.h"
#include "witsml1_4_1_1/Wellbore.h"
%}

//************************
// STD::VECTOR DEFINITIONS
//************************

%include "std_vector.i"
namespace std {
	%template(WellboreVector) vector<witsml1_4_1_1::Wellbore*>;
	%template(TrajectoryVector) vector<witsml1_4_1_1::Trajectory*>;
	%template(LogVector) vector<witsml1_4_1_1::Log*>;
	%template(FormationMarkerVector) vector<witsml1_4_1_1::FormationMarker*>;
}

namespace gsoap_witsml1_4_1_1
{
	enum witsml1__WellStatus { witsml1__WellStatus__abandoned = 0, witsml1__WellStatus__active = 1, witsml1__WellStatus__active_x0020_x002d__x0020injecting = 2, witsml1__WellStatus__active_x0020_x002d__x0020producing = 3, witsml1__WellStatus__completed = 4, witsml1__WellStatus__drilling = 5, witsml1__WellStatus__partially_x0020plugged = 6, witsml1__WellStatus__permitted = 7, witsml1__WellStatus__plugged_x0020and_x0020abandoned = 8, witsml1__WellStatus__proposed = 9, witsml1__WellStatus__sold = 10, witsml1__WellStatus__suspended = 11, witsml1__WellStatus__temporarily_x0020abandoned = 12, witsml1__WellStatus__testing = 13, witsml1__WellStatus__tight = 14, witsml1__WellStatus__working_x0020over = 15, witsml1__WellStatus__unknown = 16 };
	enum witsml1__WellPurpose { witsml1__WellPurpose__appraisal = 0, witsml1__WellPurpose__appraisal_x0020_x002d__x0020confirmation_x0020appraisal = 1, witsml1__WellPurpose__appraisal_x0020_x002d__x0020exploratory_x0020appraisal = 2, witsml1__WellPurpose__exploration = 3, witsml1__WellPurpose__exploration_x0020_x002d__x0020deeper_pool_x0020wildcat = 4, witsml1__WellPurpose__exploration_x0020_x002d__x0020new_field_x0020wildcat = 5, witsml1__WellPurpose__exploration_x0020_x002d__x0020new_pool_x0020wildcat = 6, witsml1__WellPurpose__exploration_x0020_x002d__x0020outpost_x0020wildcat = 7, witsml1__WellPurpose__exploration_x0020_x002d__x0020shallower_pool_x0020wildcat = 8, witsml1__WellPurpose__development = 9, witsml1__WellPurpose__development_x0020_x002d__x0020infill_x0020development = 10, witsml1__WellPurpose__development_x0020_x002d__x0020injector = 11, witsml1__WellPurpose__development_x0020_x002d__x0020producer = 12, witsml1__WellPurpose__fluid_x0020storage = 13, witsml1__WellPurpose__fluid_x0020storage_x0020_x002d__x0020gas_x0020storage = 14, witsml1__WellPurpose__general_x0020srvc = 15, witsml1__WellPurpose__general_x0020srvc_x0020_x002d__x0020borehole_x0020re_acquisition = 16, witsml1__WellPurpose__general_x0020srvc_x0020_x002d__x0020observation = 17, witsml1__WellPurpose__general_x0020srvc_x0020_x002d__x0020relief = 18, witsml1__WellPurpose__general_x0020srvc_x0020_x002d__x0020research = 19, witsml1__WellPurpose__general_x0020srvc_x0020_x002d__x0020research_x0020_x002d__x0020drill_x0020test = 20, witsml1__WellPurpose__general_x0020srvc_x0020_x002d__x0020research_x0020_x002d__x0020strat_x0020test = 21, witsml1__WellPurpose__general_x0020srvc_x0020_x002d__x0020waste_x0020disposal = 22, witsml1__WellPurpose__mineral = 23, witsml1__WellPurpose__unknown = 24 };
	enum witsml1__WellFluid { witsml1__WellFluid__air = 0, witsml1__WellFluid__condensate = 1, witsml1__WellFluid__dry = 2, witsml1__WellFluid__gas = 3, witsml1__WellFluid__gas_water = 4, witsml1__WellFluid__non_x0020HC_x0020gas = 5, witsml1__WellFluid__non_x0020HC_x0020gas_x0020_x002d__x0020CO2 = 6, witsml1__WellFluid__oil = 7, witsml1__WellFluid__oil_gas = 8, witsml1__WellFluid__oil_water = 9, witsml1__WellFluid__steam = 10, witsml1__WellFluid__water = 11, witsml1__WellFluid__water_x0020_x002d__x0020brine = 12, witsml1__WellFluid__water_x0020_x002d__x0020fresh_x0020water = 13, witsml1__WellFluid__unknown = 14 };
	enum witsml1__WellDirection { witsml1__WellDirection__huff_n_puff = 0, witsml1__WellDirection__injector = 1, witsml1__WellDirection__producer = 2, witsml1__WellDirection__uncertain = 3, witsml1__WellDirection__unknown = 4 };
	enum witsml1__WellboreType { witsml1__WellboreType__bypass = 0, witsml1__WellboreType__initial = 1, witsml1__WellboreType__redrill = 2, witsml1__WellboreType__reentry = 3, witsml1__WellboreType__respud = 4, witsml1__WellboreType__sidetrack = 5, witsml1__WellboreType__unknown = 6 };
	enum witsml1__LengthUom { witsml1__LengthUom__m = 0, witsml1__LengthUom__angstrom = 1, witsml1__LengthUom__chBnA = 2, witsml1__LengthUom__chBnB = 3, witsml1__LengthUom__chCla = 4, witsml1__LengthUom__chSe = 5, witsml1__LengthUom__chUS = 6, witsml1__LengthUom__cm = 7, witsml1__LengthUom__dm = 8, witsml1__LengthUom__fathom = 9, witsml1__LengthUom__fm = 10, witsml1__LengthUom__ft = 11, witsml1__LengthUom__ftBnA = 12, witsml1__LengthUom__ftBnB = 13, witsml1__LengthUom__ftBr_x002865_x0029 = 14, witsml1__LengthUom__ftCla = 15, witsml1__LengthUom__ftGC = 16, witsml1__LengthUom__ftInd = 17, witsml1__LengthUom__ftInd_x002837_x0029 = 18, witsml1__LengthUom__ftInd_x002862_x0029 = 19, witsml1__LengthUom__ftInd_x002875_x0029 = 20, witsml1__LengthUom__ftMA = 21, witsml1__LengthUom__ftSe = 22, witsml1__LengthUom__ftUS = 23, witsml1__LengthUom__in = 24, witsml1__LengthUom__in_x002f10 = 25, witsml1__LengthUom__in_x002f16 = 26, witsml1__LengthUom__in_x002f32 = 27, witsml1__LengthUom__in_x002f64 = 28, witsml1__LengthUom__inUS = 29, witsml1__LengthUom__km = 30, witsml1__LengthUom__lkBnA = 31, witsml1__LengthUom__lkBnB = 32, witsml1__LengthUom__lkCla = 33, witsml1__LengthUom__lkSe = 34, witsml1__LengthUom__lkUS = 35, witsml1__LengthUom__mGer = 36, witsml1__LengthUom__mi = 37, witsml1__LengthUom__mil = 38, witsml1__LengthUom__miUS = 39, witsml1__LengthUom__mm = 40, witsml1__LengthUom__Mm = 41, witsml1__LengthUom__nautmi = 42, witsml1__LengthUom__nm = 43, witsml1__LengthUom__pm = 44, witsml1__LengthUom__um = 45, witsml1__LengthUom__yd = 46, witsml1__LengthUom__ydBnA = 47, witsml1__LengthUom__ydBnB = 48, witsml1__LengthUom__ydCla = 49, witsml1__LengthUom__ydIm = 50, witsml1__LengthUom__ydInd = 51, witsml1__LengthUom__ydInd_x002837_x0029 = 52, witsml1__LengthUom__ydInd_x002862_x0029 = 53, witsml1__LengthUom__ydInd_x002875_x0029 = 54, witsml1__LengthUom__ydSe = 55 };
	enum witsml1__ElevCodeEnum { witsml1__ElevCodeEnum__CF = 0, witsml1__ElevCodeEnum__CV = 1, witsml1__ElevCodeEnum__DF = 2, witsml1__ElevCodeEnum__GL = 3, witsml1__ElevCodeEnum__KB = 4, witsml1__ElevCodeEnum__RB = 5, witsml1__ElevCodeEnum__RT = 6, witsml1__ElevCodeEnum__SF = 7, witsml1__ElevCodeEnum__LAT = 8, witsml1__ElevCodeEnum__SL = 9, witsml1__ElevCodeEnum__MHHW = 10, witsml1__ElevCodeEnum__MHW = 11, witsml1__ElevCodeEnum__MLLW = 12, witsml1__ElevCodeEnum__MLW = 13, witsml1__ElevCodeEnum__MTL = 14, witsml1__ElevCodeEnum__KO = 15, witsml1__ElevCodeEnum__unknown = 16 };
	enum witsml1__WellVerticalCoordinateUom { witsml1__WellVerticalCoordinateUom__m = 0, witsml1__WellVerticalCoordinateUom__ft = 1, witsml1__WellVerticalCoordinateUom__ftUS = 2, witsml1__WellVerticalCoordinateUom__ftBr_x002865_x0029 = 3 };
	enum witsml1__LogIndexType { witsml1__LogIndexType__date_x0020time = 0, witsml1__LogIndexType__elapsed_x0020time = 1, witsml1__LogIndexType__length = 2, witsml1__LogIndexType__measured_x0020depth = 3, witsml1__LogIndexType__vertical_x0020depth = 4, witsml1__LogIndexType__other = 5, witsml1__LogIndexType__unknown = 6 };
	enum witsml1__MeasuredDepthUom { witsml1__MeasuredDepthUom__m = 0, witsml1__MeasuredDepthUom__ft = 1, witsml1__MeasuredDepthUom__ftUS = 2 };
	enum witsml1__PlaneAngleUom { witsml1__PlaneAngleUom__rad = 0, witsml1__PlaneAngleUom__c = 1, witsml1__PlaneAngleUom__ccgr = 2, witsml1__PlaneAngleUom__cgr = 3, witsml1__PlaneAngleUom__dega = 4, witsml1__PlaneAngleUom__gon = 5, witsml1__PlaneAngleUom__gr = 6, witsml1__PlaneAngleUom__Grad = 7, witsml1__PlaneAngleUom__krad = 8, witsml1__PlaneAngleUom__mila = 9, witsml1__PlaneAngleUom__mina = 10, witsml1__PlaneAngleUom__mrad = 11, witsml1__PlaneAngleUom__Mrad = 12, witsml1__PlaneAngleUom__mseca = 13, witsml1__PlaneAngleUom__seca = 14, witsml1__PlaneAngleUom__urad = 15 };
	enum witsml1__AziRef { witsml1__AziRef__magnetic_x0020north = 0, witsml1__AziRef__grid_x0020north = 1, witsml1__AziRef__true_x0020north = 2, witsml1__AziRef__unknown = 3 };
	enum witsml1__LogIndexDirection { witsml1__LogIndexDirection__decreasing = 0, witsml1__LogIndexDirection__increasing = 1, witsml1__LogIndexDirection__unknown = 2 };
	enum witsml1__WellboreShape { witsml1__WellboreShape__build_x0020and_x0020hold = 0, witsml1__WellboreShape__deviated = 1, witsml1__WellboreShape__double_x0020kickoff = 2, witsml1__WellboreShape__horizontal = 3, witsml1__WellboreShape__S_shaped = 4, witsml1__WellboreShape__vertical = 5, witsml1__WellboreShape__unknown = 6 };
	enum witsml1__PerLengthUom { witsml1__PerLengthUom__1_x002fm = 0, witsml1__PerLengthUom__1_x002fangstrom = 1, witsml1__PerLengthUom__1_x002fcm = 2, witsml1__PerLengthUom__1_x002fft = 3, witsml1__PerLengthUom__1_x002fin = 4, witsml1__PerLengthUom__1_x002fmi = 5, witsml1__PerLengthUom__1_x002fmm = 6, witsml1__PerLengthUom__1_x002fnm = 7, witsml1__PerLengthUom__1_x002fyd = 8 };
	enum witsml1__LogTraceOrigin { witsml1__LogTraceOrigin__realtime = 0, witsml1__LogTraceOrigin__modeled = 1, witsml1__LogTraceOrigin__unknown = 2 };
	enum witsml1__LogDataType { witsml1__LogDataType__byte = 0, witsml1__LogDataType__date_x0020time = 1, witsml1__LogDataType__double_ = 2, witsml1__LogDataType__float_ = 3, witsml1__LogDataType__int_ = 4, witsml1__LogDataType__long_ = 5, witsml1__LogDataType__short_ = 6, witsml1__LogDataType__string = 7, witsml1__LogDataType__string40 = 8, witsml1__LogDataType__string16 = 9, witsml1__LogDataType__unknown = 10 };
}

#ifdef SWIGJAVA
	%include "swigWitsml1_4_1_1JavaInclude.i"
#endif
#ifdef SWIGPYTHON

#endif
#ifdef SWIGCSHARP
	%include "swigWitsml1_4_1_1CsInclude.i"
#endif
#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace witsml1_4_1_1::AbstractObject;
	%nspace witsml1_4_1_1::CoordinateReferenceSystem;
	%nspace witsml1_4_1_1::Well;
	%nspace witsml1_4_1_1::Wellbore;
	%nspace witsml1_4_1_1::Trajectory;
	%nspace witsml1_4_1_1::Log;
	%nspace witsml1_4_1_1::FormationMarker;
#endif

namespace witsml1_4_1_1
{
	%nodefaultctor; // Disable creation of default constructors
	
	class CoordinateReferenceSystem;
#ifdef SWIGPYTHON
	%rename(Witsml1_4_1_1AbstractObject) AbstractObject;
#endif
	class AbstractObject
	{
	public:
		common::EpcDocument* getEpcDocument() const;
		std::string getXmlTag() const;
		
		const std::string & getTitle() const;
		std::string getUuid() const;
		time_t getCreation() const ;
		time_t getLastUpdate() const;
		
		class CoordinateReferenceSystem* getCoordinateReferenceSystem() const;
	};
	
	class CoordinateReferenceSystem : public AbstractObject
	{
	public:
		
	};
	
	class Well : public AbstractObject
	{
	public:
			
		const std::vector<class Wellbore*>& getWellbores() const;

		class Wellbore* createWellbore(
			const std::string & guid,
			const std::string & title);

		class Wellbore* createWellbore(
			const std::string & guid,
			const std::string & title,
			gsoap_witsml1_4_1_1::witsml1__WellStatus statusWellbore,
			const bool & isActive,
			gsoap_witsml1_4_1_1::witsml1__WellPurpose purposeWellbore,
			gsoap_witsml1_4_1_1::witsml1__WellboreType typeWellbore,
			const bool & achievedTD,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments
		);

		void setOperator(const std::string & operator_);

		double getWellHeadEastingLocationValue();
		gsoap_witsml1_4_1_1::witsml1__LengthUom getWellHeadEastingLocationUom();
		double getWellHeadNorthingLocationValue();
		gsoap_witsml1_4_1_1::witsml1__LengthUom getWellHeadNorthingLocationUom();
		
		void setEastingNorthingLocation(
			gsoap_witsml1_4_1_1::witsml1__LengthUom uom,
			const double & easting,
			const double & northing,
			class CoordinateReferenceSystem* wellCrs);

		void setWestingSouthingLocation(
			gsoap_witsml1_4_1_1::witsml1__LengthUom uom,
			const double & westing,
			const double & southing,
			class CoordinateReferenceSystem* wellCrs);

		void setProjectedXProjectedYLocation(
			gsoap_witsml1_4_1_1::witsml1__LengthUom uom,
			const double & projectedX,
			const double & projectedY,
			class CoordinateReferenceSystem* wellCrs);
		
		void pushBackDatum(
			const std::string & guid, 
			const std::string & title,
			gsoap_witsml1_4_1_1::witsml1__ElevCodeEnum code,
			const unsigned int & datumIndex,
			gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom elevationUnit,
			const double & elevation);

		void pushBackDatum(
			const std::string & guid, 
			const std::string & title,
			gsoap_witsml1_4_1_1::witsml1__ElevCodeEnum code,
			const std::string & refNamingSystem,
			const std::string & refCode,
			const std::string & refName);
			
		unsigned int getDatumCount() const;
	};
	
	class Wellbore : public AbstractObject
	{
	public:
		class Trajectory* createTrajectory(
			const std::string & guid,
			const std::string & title);

		class Trajectory* createTrajectory(
			const std::string & guid,
			const std::string & title,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments);

		class Log* createLog(
			const std::string & guid,
			const std::string & title,
			gsoap_witsml1_4_1_1::witsml1__LogIndexType indexType,
			const std::string & indexCurve);

		class Log* createLog(
			const std::string & guid,
			const std::string & title,
			gsoap_witsml1_4_1_1::witsml1__LogIndexType indexType,
			const std::string & indexCurve,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments);
		
		class FormationMarker* createFormationMarker(
			const std::string & guid,
			const std::string & title,
			const unsigned int & mdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mdUom,
			const double & mdTopSample);

		class FormationMarker* createFormationMarker(
			const std::string & guid,
			const std::string & title,
			const unsigned int & mdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mdUom,
			const double & mdTopSample,
			const unsigned int & tvdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom tvdUom,
			const double & tvdTopSample,
			gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom dipUom,
			const double & dip,
			gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom dipDirectionUom,
			const double & dipDirection,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments);
			
		Well* getWell();
		
		resqml2_0_1::WellboreFeature* getResqmlWellboreFeature();
		
		const std::vector<Trajectory*>& getTrajectories() const;

		const std::vector<Log*>& getLogs() const;

		const std::vector<FormationMarker*>& getFormationMarkers() const;
		
		void setShape(const gsoap_witsml1_4_1_1::witsml1__WellboreShape & shape);
	};
	
	class Trajectory : public AbstractObject
	{
	public:
		double getMdDatumElevation();
		gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom getMdDatumElevationUom();
		std::string getMdDatumName();

		unsigned int getTrajectoryStationCount() const;
		
		void getMds(double * mds) const;
		gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom getMdUom() const;

		unsigned int getInclinometries(double * incls) const;
		gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom getInclinometryUom() const;

		unsigned int getAzimuths(double * azims) const;
		gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom getAzimuthUom() const;
		gsoap_witsml1_4_1_1::witsml1__AziRef getAzimuthReference() const;

		unsigned int getEastings(double * eastings) const;
		gsoap_witsml1_4_1_1::witsml1__LengthUom getEastingUom() const;

		unsigned int getNorthings(double * northings) const;
		gsoap_witsml1_4_1_1::witsml1__LengthUom getNorthingUom() const;

		unsigned int getTvds(double * tvds) const;
		gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom getTvdUom() const;
	
		void setTrajectoryStations(
			const unsigned int & trajectoryStationCount,
			const unsigned int & mdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mDUom,
			double * mDSet,
			gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom	angleUom,
			double * inclSet,
			gsoap_witsml1_4_1_1::witsml1__AziRef aziRef,
			double * aziSet);
	
		void setEastingNorthingTrajectoryStations(
			const unsigned int & trajectoryStationCount,
			const unsigned int & mdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mDUom,
			double * mDSet,
			const unsigned int & tvdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom tVDUom,
			double * tVDSet,
			gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom	angleUom,
			double * inclSet,
			gsoap_witsml1_4_1_1::witsml1__AziRef aziRef,
			double * aziSet,
			gsoap_witsml1_4_1_1::witsml1__LengthUom locationUom,
			double * locationEastingSet,
			double * locationNorthingSet,
			class CoordinateReferenceSystem* wellCrs);

		void setWestingSouthingTrajectoryStations(
			const unsigned int & trajectoryStationCount,
			const unsigned int & mdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mDUom,
			double * mDSet,
			const unsigned int & tvdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom tVDUom,
			double * tVDSet,
			gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom	angleUom,
			double * inclSet,
			gsoap_witsml1_4_1_1::witsml1__AziRef aziRef,
			double * aziSet,
			gsoap_witsml1_4_1_1::witsml1__LengthUom locationUom,
			double * locationWestingSet,
			double * locationSouthingSet,
			class CoordinateReferenceSystem* wellCrs);

		void setProjectedXProjectedYTrajectoryStations(
			const unsigned int & trajectoryStationCount,
			const unsigned int & mdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mDUom,
			double * mDSet,
			const unsigned int & tvdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom tVDUom,
			double * tVDSet,
			gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom	angleUom,
			double * inclSet,
			gsoap_witsml1_4_1_1::witsml1__AziRef aziRef,
			double * aziSet,
			gsoap_witsml1_4_1_1::witsml1__LengthUom locationUom,
			double * locationProjectedXSet,
			double * locationProjectedYSet,
			class CoordinateReferenceSystem* wellCrs);
			
		Wellbore* getWellbore();
		
		resqml2_0_1::WellboreTrajectoryRepresentation* getResqmlWellboreTrajectoryRepresentation() const;		
	};
	
	class Log : public AbstractObject
	{
	public:
		gsoap_witsml1_4_1_1::witsml1__LogIndexType getIndexType();
		std::string getIndexMnemonic();
		std::string getDataDelimiter() const;
		const std::vector<std::string> & getData() const;
		std::vector<std::string> getMnemonicSet();
	
		void setValues(
			const std::string & description,
			const std::string & dataDelimiter,
			const std::string & startEndIncrementUOM,
			const double & startIndex,
			const double & endIndex,
			const double & stepIncrement,
			gsoap_witsml1_4_1_1::witsml1__LogIndexDirection direction,
			const std::string & mnemonicList,
			const std::string & unitList,
			std::vector<std::string> const & data);
		
		unsigned int getLogCurveCount() const;
		std::string getLogCurveMnemonic(const unsigned int & logCurveIndex) const;
		gsoap_witsml1_4_1_1::witsml1__LogDataType getLogCurveDataType(const unsigned int & logCurveIndex) const;
		std::string getLogCurveUom(const unsigned int & logCurveIndex) const;
		
		void pushBackLogCurveInfo(const std::string & mnemonic, gsoap_witsml1_4_1_1::witsml1__LogDataType typeLogData);

		void pushBackLogCurveInfo(
			const std::string & namingSystem,
			const std::string & mnemonic,
			const std::string & classWitsml,
			const std::string & unit,
			const int & datumIndex,
			const std::string & minMaxIndexUOM,
			const double & minIndex,
			const double & maxIndex,
			const std::string & curveDescription,
			gsoap_witsml1_4_1_1::witsml1__PerLengthUom perLengthUOM,
			const double & densData,
			gsoap_witsml1_4_1_1::witsml1__LogTraceOrigin traceOrigin,
			gsoap_witsml1_4_1_1::witsml1__LogDataType typeLogData);

		Wellbore* getWellbore();
		
		resqml2_0_1::WellboreFrameRepresentation* getResqmlWellboreFrameRepresentation() const;
	};
	
	class FormationMarker : public AbstractObject
	{
	public:
		Wellbore* getWellbore();
		resqml2_0_1::WellboreMarkerFrameRepresentation* getResqmlWellboreMarkerFrameRepresentation() const;
	};
}

