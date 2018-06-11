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
#define SWIG_FILE_WITH_INIT // In case we use Python Swig Wrapping

#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "resqml2_0_1/LocalTime3dCrs.h"
#include "resqml2_0_1/MdDatum.h"

#include "resqml2_0_1/Horizon.h"
#include "resqml2_0_1/TectonicBoundaryFeature.h"
#include "resqml2_0_1/FrontierFeature.h"
#include "resqml2_0_1/WellboreFeature.h"
#include "resqml2_0_1/SeismicLineFeature.h"
#include "resqml2_0_1/SeismicLineSetFeature.h"
#include "resqml2_0_1/SeismicLatticeFeature.h"
#include "resqml2_0_1/OrganizationFeature.h"
#include "resqml2_0_1/StratigraphicUnitFeature.h"
#include "resqml2_0_1/GeobodyFeature.h"
#include "resqml2_0_1/FluidBoundaryFeature.h"

#include "resqml2_0_1/GenericFeatureInterpretation.h"
#include "resqml2_0_1/HorizonInterpretation.h"
#include "resqml2_0_1/FaultInterpretation.h"
#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/StratigraphicUnitInterpretation.h"
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"
#include "resqml2_0_1/StratigraphicColumnRankInterpretation.h"
#include "resqml2_0_1/StratigraphicOccurrenceInterpretation.h"
#include "resqml2_0_1/EarthModelInterpretation.h"
#include "resqml2_0_1/GeobodyBoundaryInterpretation.h"
#include "resqml2_0_1/GeobodyInterpretation.h"

#include "resqml2_0_1/PolylineSetRepresentation.h"
#include "resqml2_0_1/PointSetRepresentation.h"
#include "resqml2_0_1/PlaneSetRepresentation.h"
#include "resqml2_0_1/PolylineRepresentation.h"
#include "resqml2_0_1/Grid2dRepresentation.h"
#include "resqml2_0_1/Grid2dSetRepresentation.h"
#include "resqml2_0_1/TriangulatedSetRepresentation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2_0_1/DeviationSurveyRepresentation.h"
#include "resqml2_0_1/WellboreMarker.h"
#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"
#include "resqml2_0_1/NonSealedSurfaceFrameworkRepresentation.h"
#include "resqml2_0_1/SealedSurfaceFrameworkRepresentation.h"

#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "resqml2_0_1/IjkGridParametricRepresentation.h"
#include "resqml2_0_1/IjkGridLatticeRepresentation.h"
#include "resqml2_0_1/IjkGridNoGeometryRepresentation.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/SubRepresentation.h"
#include "resqml2_0_1/GridConnectionSetRepresentation.h"

#include "resqml2_0_1/TimeSeries.h"

#include "resqml2_0_1/PropertyKind.h"
#include "resqml2_0_1/StringTableLookup.h"
#include "resqml2_0_1/DiscreteProperty.h"
#include "resqml2_0_1/DiscretePropertySeries.h"
#include "resqml2_0_1/CategoricalProperty.h"
#include "resqml2_0_1/CategoricalPropertySeries.h"
#include "resqml2_0_1/CommentProperty.h"
#include "resqml2_0_1/ContinuousProperty.h"
#include "resqml2_0_1/ContinuousPropertySeries.h"

#include "resqml2_0_1/ActivityTemplate.h"

#include "resqml2_0_1/PropertyKindMapper.h"

#include "resqml2_0_1/HdfProxy.h"
%}

//************************
// STD::VECTOR DEFINITIONS
//************************

namespace RESQML2_0_1_NS {
	class LocalDepth3dCrs;
	class LocalTime3dCrs;
	class StratigraphicColumn;
	class StratigraphicColumnRankInterpretation;
	class TectonicBoundaryFeature;
	class Horizon;
	class GeobodyBoundaryInterpretation;
	class GeobodyFeature;
	class GeobodyInterpretation;
	class FrontierFeature;
	class StratigraphicUnitInterpretation;
	class HorizonInterpretation;
	class StratigraphicOccurrenceInterpretation;
	class PolylineSetRepresentation;
	class Grid2dSetRepresentation;
	class Grid2dRepresentation;
	class PolylineRepresentation;
	class PolylineSetRepresentation;
	class TriangulatedSetRepresentation;
	class SeismicLineFeature;
	class WellboreFeature;
	class WellboreTrajectoryRepresentation;
	class DeviationSurveyRepresentation;
	class WellboreMarkerFrameRepresentation;
	class UnstructuredGridRepresentation;
	class WellboreMarker;
	class IjkGridExplicitRepresentation;
	class IjkGridParametricRepresentation;
	class IjkGridLatticeRepresentation;
	class IjkGridNoGeometryRepresentation;
	class SubRepresentation;
}

// Don't try to create vector of polymorphic data unless you really know what you are doing.
// Use C array approach instead.
namespace std {
   %template(LocalDepth3dCrsVector) vector<RESQML2_0_1_NS::LocalDepth3dCrs*>;
   %template(LocalTime3dCrsVector) vector<RESQML2_0_1_NS::LocalTime3dCrs*>;
   %template(StratigraphicColumnVector) vector<RESQML2_0_1_NS::StratigraphicColumn*>;
   %template(StratigraphicColumnRankInterpretationVector) vector<RESQML2_0_1_NS::StratigraphicColumnRankInterpretation*>;
   %template(TectonicBoundaryFeatureVector) vector<RESQML2_0_1_NS::TectonicBoundaryFeature*>;
   %template(HorizonVector) vector<RESQML2_0_1_NS::Horizon*>;
   %template(GeobodyFeatureVector) vector<RESQML2_0_1_NS::GeobodyFeature*>;
   %template(FrontierVector) vector<RESQML2_0_1_NS::FrontierFeature*>;
   %template(StratigraphicUnitInterpretationVector) vector<RESQML2_0_1_NS::StratigraphicUnitInterpretation*>;
   %template(StratigraphicOccurrenceInterpretationVector) vector<RESQML2_0_1_NS::StratigraphicOccurrenceInterpretation*>;
   %template(HorizonInterpretationVector) vector<RESQML2_0_1_NS::HorizonInterpretation*>;
   %template(Grid2dSetRepresentationVector) vector<RESQML2_0_1_NS::Grid2dSetRepresentation*>;
   %template(Grid2dRepresentationVector) vector<RESQML2_0_1_NS::Grid2dRepresentation*>;
   %template(PolylineRepresentationVector) vector<RESQML2_0_1_NS::PolylineRepresentation*>;
   %template(PolylineSetRepresentationVector) vector<RESQML2_0_1_NS::PolylineSetRepresentation*>;
   %template(TriangulatedSetRepresentationVector) vector<RESQML2_0_1_NS::TriangulatedSetRepresentation*>;
   %template(SeismicLineFeatureVector) vector<RESQML2_0_1_NS::SeismicLineFeature*>;
   %template(WellboreFeatureVector) vector<RESQML2_0_1_NS::WellboreFeature*>;
   %template(WellboreTrajectoryRepresentationVector) vector<RESQML2_0_1_NS::WellboreTrajectoryRepresentation*>;
   %template(DeviationSurveyRepresentationVector) vector<RESQML2_0_1_NS::DeviationSurveyRepresentation*>;
   %template(WellboreMarkerFrameRepresentationVector) vector<RESQML2_0_1_NS::WellboreMarkerFrameRepresentation*>;
   %template(UnstructuredGridRepresentationVector) vector<RESQML2_0_1_NS::UnstructuredGridRepresentation*>;
   %template(WellboreMarkerVector) vector<RESQML2_0_1_NS::WellboreMarker*>;
   %template(IjkGridExplicitRepresentationVector) vector<RESQML2_0_1_NS::IjkGridExplicitRepresentation*>;
   %template(IjkGridParametricRepresentationVector) vector<RESQML2_0_1_NS::IjkGridParametricRepresentation*>;
   %template(IjkGridLatticeRepresentationVector) vector<RESQML2_0_1_NS::IjkGridLatticeRepresentation*>;
   %template(IjkGridNoGeometryRepresentationVector) vector<RESQML2_0_1_NS::IjkGridNoGeometryRepresentation*>;
}

namespace gsoap_resqml2_0_1
{
	enum eml20__AxisOrder2d {
		eml20__AxisOrder2d__easting_x0020northing = 0,
		eml20__AxisOrder2d__northing_x0020easting = 1,
		eml20__AxisOrder2d__westing_x0020southing = 2,
		eml20__AxisOrder2d__southing_x0020westing = 3,
		eml20__AxisOrder2d__northing_x0020westing = 4,
		eml20__AxisOrder2d__westing_x0020northing = 5
	};
	enum resqml2__GeologicBoundaryKind {
		resqml2__GeologicBoundaryKind__fault = 0,
		resqml2__GeologicBoundaryKind__geobody = 1,
		resqml2__GeologicBoundaryKind__horizon = 2
	};
	enum eml20__LengthUom {
		eml20__LengthUom__m = 'm',
		eml20__LengthUom__0_x002e1_x0020ft = 'n',
		eml20__LengthUom__0_x002e1_x0020ft_x005bUS_x005d = 'o',
		eml20__LengthUom__0_x002e1_x0020in = 'p',
		eml20__LengthUom__0_x002e1_x0020yd = 'q',
		eml20__LengthUom__1_x002f16_x0020in = 'r',
		eml20__LengthUom__1_x002f2_x0020ft = 's',
		eml20__LengthUom__1_x002f32_x0020in = 't',
		eml20__LengthUom__1_x002f64_x0020in = 'u',
		eml20__LengthUom__10_x0020ft = 'v',
		eml20__LengthUom__10_x0020in = 'w',
		eml20__LengthUom__10_x0020km = 'x',
		eml20__LengthUom__100_x0020ft = 'y',
		eml20__LengthUom__100_x0020km = 'z',
		eml20__LengthUom__1000_x0020ft = 123,
		eml20__LengthUom__30_x0020ft = 124,
		eml20__LengthUom__30_x0020m = 125,
		eml20__LengthUom__angstrom = 126,
		eml20__LengthUom__chain = 127,
		eml20__LengthUom__chain_x005bBnA_x005d = 128,
		eml20__LengthUom__chain_x005bBnB_x005d = 129,
		eml20__LengthUom__chain_x005bCla_x005d = 130,
		eml20__LengthUom__chain_x005bInd37_x005d = 131,
		eml20__LengthUom__chain_x005bSe_x005d = 132,
		eml20__LengthUom__chain_x005bSeT_x005d = 133,
		eml20__LengthUom__chain_x005bUS_x005d = 134,
		eml20__LengthUom__cm = 135,
		eml20__LengthUom__dam = 136,
		eml20__LengthUom__dm = 137,
		eml20__LengthUom__Em = 138,
		eml20__LengthUom__fathom = 139,
		eml20__LengthUom__fm = 140,
		eml20__LengthUom__ft = 141,
		eml20__LengthUom__ft_x005bBnA_x005d = 142,
		eml20__LengthUom__ft_x005bBnB_x005d = 143,
		eml20__LengthUom__ft_x005bBr36_x005d = 144,
		eml20__LengthUom__ft_x005bBr65_x005d = 145,
		eml20__LengthUom__ft_x005bCla_x005d = 146,
		eml20__LengthUom__ft_x005bGC_x005d = 147,
		eml20__LengthUom__ft_x005bInd_x005d = 148,
		eml20__LengthUom__ft_x005bInd37_x005d = 149,
		eml20__LengthUom__ft_x005bInd62_x005d = 150,
		eml20__LengthUom__ft_x005bInd75_x005d = 151,
		eml20__LengthUom__ft_x005bSe_x005d = 152,
		eml20__LengthUom__ft_x005bSeT_x005d = 153,
		eml20__LengthUom__ft_x005bUS_x005d = 154,
		eml20__LengthUom__fur_x005bUS_x005d = 155,
		eml20__LengthUom__Gm = 156,
		eml20__LengthUom__hm = 157,
		eml20__LengthUom__in = 158,
		eml20__LengthUom__in_x005bUS_x005d = 159,
		eml20__LengthUom__km = 160,
		eml20__LengthUom__link = 161,
		eml20__LengthUom__link_x005bBnA_x005d = 162,
		eml20__LengthUom__link_x005bBnB_x005d = 163,
		eml20__LengthUom__link_x005bCla_x005d = 164,
		eml20__LengthUom__link_x005bSe_x005d = 165,
		eml20__LengthUom__link_x005bSeT_x005d = 166,
		eml20__LengthUom__link_x005bUS_x005d = 167,
		eml20__LengthUom__m_x005bGer_x005d = 168,
		eml20__LengthUom__mi = 169,
		eml20__LengthUom__mi_x005bnaut_x005d = 170,
		eml20__LengthUom__mi_x005bnautUK_x005d = 171,
		eml20__LengthUom__mi_x005bUS_x005d = 172,
		eml20__LengthUom__mil = 173,
		eml20__LengthUom__Mm = 174,
		eml20__LengthUom__mm = 175,
		eml20__LengthUom__nm = 176,
		eml20__LengthUom__pm = 177,
		eml20__LengthUom__rod_x005bUS_x005d = 178,
		eml20__LengthUom__Tm = 179,
		eml20__LengthUom__um = 180,
		eml20__LengthUom__yd = 181,
		eml20__LengthUom__yd_x005bBnA_x005d = 182,
		eml20__LengthUom__yd_x005bBnB_x005d = 183,
		eml20__LengthUom__yd_x005bCla_x005d = 184,
		eml20__LengthUom__yd_x005bInd_x005d = 185,
		eml20__LengthUom__yd_x005bInd37_x005d = 186,
		eml20__LengthUom__yd_x005bInd62_x005d = 187,
		eml20__LengthUom__yd_x005bInd75_x005d = 188,
		eml20__LengthUom__yd_x005bSe_x005d = 189,
		eml20__LengthUom__yd_x005bSeT_x005d = 190,
		eml20__LengthUom__yd_x005bUS_x005d = 191
	};
	enum eml20__PlaneAngleUom {
		eml20__PlaneAngleUom__0_x002e001_x0020seca = 0,
		eml20__PlaneAngleUom__ccgr = 1,
		eml20__PlaneAngleUom__cgr = 2,
		eml20__PlaneAngleUom__dega = 3,
		eml20__PlaneAngleUom__gon = 4,
		eml20__PlaneAngleUom__krad = 5,
		eml20__PlaneAngleUom__mila = 6,
		eml20__PlaneAngleUom__mina = 7,
		eml20__PlaneAngleUom__Mrad = 8,
		eml20__PlaneAngleUom__mrad = 9,
		eml20__PlaneAngleUom__rad = 10,
		eml20__PlaneAngleUom__rev = 11,
		eml20__PlaneAngleUom__seca = 12,
		eml20__PlaneAngleUom__urad = 13
	};

	enum eml20__TimeUom {
		eml20__TimeUom__a = 'a',
		eml20__TimeUom__d = 'd',
		eml20__TimeUom__h = 'h',
		eml20__TimeUom__s = 's',
		eml20__TimeUom__1_x002f2_x0020ms = 't',
		eml20__TimeUom__100_x0020ka_x005bt_x005d = 'u',
		eml20__TimeUom__a_x005bt_x005d = 'v',
		eml20__TimeUom__ca = 'w',
		eml20__TimeUom__cs = 'x',
		eml20__TimeUom__ds = 'y',
		eml20__TimeUom__Ea_x005bt_x005d = 'z',
		eml20__TimeUom__fa = 123,
		eml20__TimeUom__Ga_x005bt_x005d = 124,
		eml20__TimeUom__hs = 125,
		eml20__TimeUom__ka_x005bt_x005d = 126,
		eml20__TimeUom__Ma_x005bt_x005d = 127,
		eml20__TimeUom__min_ = 128,
		eml20__TimeUom__ms = 129,
		eml20__TimeUom__na = 130,
		eml20__TimeUom__ns = 131,
		eml20__TimeUom__ps = 132,
		eml20__TimeUom__Ta_x005bt_x005d = 133,
		eml20__TimeUom__us = 134,
		eml20__TimeUom__wk = 135
	};
	enum resqml2__Geobody3dShape {
		resqml2__Geobody3dShape__dyke = 0,
		resqml2__Geobody3dShape__silt = 1,
		resqml2__Geobody3dShape__dome = 2,
		resqml2__Geobody3dShape__sheeth = 3,
		resqml2__Geobody3dShape__diapir = 4,
		resqml2__Geobody3dShape__batholith = 5,
		resqml2__Geobody3dShape__channel = 6,
		resqml2__Geobody3dShape__delta = 7,
		resqml2__Geobody3dShape__dune = 8,
		resqml2__Geobody3dShape__fan = 9,
		resqml2__Geobody3dShape__reef = 10,
		resqml2__Geobody3dShape__wedge = 11
	};
	enum resqml2__LineRole {
		resqml2__LineRole__fault_x0020center_x0020line = 0,
		resqml2__LineRole__pick = 1,
		resqml2__LineRole__inner_x0020ring = 2,
		resqml2__LineRole__outer_x0020ring = 3,
		resqml2__LineRole__trajectory = 4,
		resqml2__LineRole__interpretation_x0020line = 5,
		resqml2__LineRole__contact = 6,
		resqml2__LineRole__depositional_x0020line = 7,
		resqml2__LineRole__erosion_x0020line = 8,
		resqml2__LineRole__contouring = 9,
		resqml2__LineRole__pillar = 10
	};
	enum resqml2__ContactVerb {
		resqml2__ContactVerb__splits = 0,
		resqml2__ContactVerb__interrupts = 1,
		resqml2__ContactVerb__contains = 2,
		resqml2__ContactVerb__conforms = 3,
		resqml2__ContactVerb__erodes = 4,
		resqml2__ContactVerb__stops_x0020at = 5,
		resqml2__ContactVerb__crosses = 6,
		resqml2__ContactVerb__includes = 7
	};
	enum resqml2__ContactSide {
		resqml2__ContactSide__footwall = 0,
		resqml2__ContactSide__hanging_x0020wall = 1,
		resqml2__ContactSide__north = 2,
		resqml2__ContactSide__south = 3,
		resqml2__ContactSide__east = 4,
		resqml2__ContactSide__west = 5,
		resqml2__ContactSide__younger = 6,
		resqml2__ContactSide__older = 7,
		resqml2__ContactSide__both = 8
	};
	enum resqml2__ContactMode {
		resqml2__ContactMode__baselap = 0,
		resqml2__ContactMode__erosion = 1,
		resqml2__ContactMode__extended = 2,
		resqml2__ContactMode__proportional = 3
	};
	enum resqml2__ContactRelationship {
		resqml2__ContactRelationship__frontier_x0020feature_x0020to_x0020frontier_x0020feature = 0,
		resqml2__ContactRelationship__genetic_x0020boundary_x0020to_x0020frontier_x0020feature = 1,
		resqml2__ContactRelationship__genetic_x0020boundary_x0020to_x0020genetic_x0020boundary = 2,
		resqml2__ContactRelationship__genetic_x0020boundary_x0020to_x0020tectonic_x0020boundary = 3,
		resqml2__ContactRelationship__stratigraphic_x0020unit_x0020to_x0020frontier_x0020feature = 4,
		resqml2__ContactRelationship__stratigraphic_x0020unit_x0020to_x0020stratigraphic_x0020unit = 5,
		resqml2__ContactRelationship__tectonic_x0020boundary_x0020to_x0020frontier_x0020feature = 6,
		resqml2__ContactRelationship__tectonic_x0020boundary_x0020to_x0020genetic_x0020boundary = 7,
		resqml2__ContactRelationship__tectonic_x0020boundary_x0020to_x0020tectonic_x0020boundary = 8
	};
	enum resqml2__ThrowKind {
		resqml2__ThrowKind__reverse = 0,
		resqml2__ThrowKind__normal = 1,
		resqml2__ThrowKind__thrust = 2,
		resqml2__ThrowKind__strike_x0020and_x0020slip = 3,
		resqml2__ThrowKind__scissor = 4,
		resqml2__ThrowKind__variable = 5
	};
	enum resqml2__PillarShape {
		resqml2__PillarShape__vertical = 0,
		resqml2__PillarShape__straight = 1,
		resqml2__PillarShape__curved = 2
	};
	enum resqml2__KDirection {
		resqml2__KDirection__down = 0,
		resqml2__KDirection__up = 1,
		resqml2__KDirection__not_x0020monotonic = 2
	};
	enum resqml2__CellShape {
		resqml2__CellShape__tetrahedral = 0,
		resqml2__CellShape__pyramidal = 1,
		resqml2__CellShape__prism = 2,
		resqml2__CellShape__hexahedral = 3,
		resqml2__CellShape__polyhedral = 4
	};
	enum resqml2__MdReference {
		resqml2__MdReference__ground_x0020level = 0,
		resqml2__MdReference__kelly_x0020bushing = 1,
		resqml2__MdReference__mean_x0020sea_x0020level = 2,
		resqml2__MdReference__derrick_x0020floor = 3,
		resqml2__MdReference__casing_x0020flange = 4,
		resqml2__MdReference__arbitrary_x0020point = 5,
		resqml2__MdReference__crown_x0020valve = 6,
		resqml2__MdReference__rotary_x0020bushing = 7,
		resqml2__MdReference__rotary_x0020table = 8,
		resqml2__MdReference__sea_x0020floor = 9,
		resqml2__MdReference__lowest_x0020astronomical_x0020tide = 10,
		resqml2__MdReference__mean_x0020higher_x0020high_x0020water = 11,
		resqml2__MdReference__mean_x0020high_x0020water = 12,
		resqml2__MdReference__mean_x0020lower_x0020low_x0020water = 13,
		resqml2__MdReference__mean_x0020low_x0020water = 14,
		resqml2__MdReference__mean_x0020tide_x0020level = 15,
		resqml2__MdReference__kickoff_x0020point = 16
	};
	enum resqml2__IndexableElements {
		resqml2__IndexableElements__cells = 0,
		resqml2__IndexableElements__column_x0020edges = 1,
		resqml2__IndexableElements__columns = 2,
		resqml2__IndexableElements__contacts = 3,
		resqml2__IndexableElements__coordinate_x0020lines = 4,
		resqml2__IndexableElements__edges = 5,
		resqml2__IndexableElements__edges_x0020per_x0020column = 6,
		resqml2__IndexableElements__enumerated_x0020elements = 7,
		resqml2__IndexableElements__faces = 8,
		resqml2__IndexableElements__faces_x0020per_x0020cell = 9,
		resqml2__IndexableElements__interval_x0020edges = 10,
		resqml2__IndexableElements__intervals = 11,
		resqml2__IndexableElements__I0 = 12,
		resqml2__IndexableElements__I0_x0020edges = 13,
		resqml2__IndexableElements__J0 = 14,
		resqml2__IndexableElements__J0_x0020edges = 15,
		resqml2__IndexableElements__layers = 16,
		resqml2__IndexableElements__nodes = 17,
		resqml2__IndexableElements__nodes_x0020per_x0020cell = 18,
		resqml2__IndexableElements__nodes_x0020per_x0020edge = 19,
		resqml2__IndexableElements__nodes_x0020per_x0020face = 20,
		resqml2__IndexableElements__patches = 21,
		resqml2__IndexableElements__pillars = 22,
		resqml2__IndexableElements__regions = 23,
		resqml2__IndexableElements__representation = 24,
		resqml2__IndexableElements__subnodes = 25,
		resqml2__IndexableElements__triangles = 26
	};
	enum resqml2__ResqmlUom {
		resqml2__ResqmlUom__A = 'A',
		resqml2__ResqmlUom__a = 'a',
		resqml2__ResqmlUom__b = 'b',
		resqml2__ResqmlUom__B = 'B',
		resqml2__ResqmlUom__C = 'C',
		resqml2__ResqmlUom__d = 'd',
		resqml2__ResqmlUom__D = 'D',
		resqml2__ResqmlUom__F = 'F',
		resqml2__ResqmlUom__g = 'g',
		resqml2__ResqmlUom__H = 'H',
		resqml2__ResqmlUom__h = 'h',
		resqml2__ResqmlUom__J = 'J',
		resqml2__ResqmlUom__K = 'K',
		resqml2__ResqmlUom__L = 'L',
		resqml2__ResqmlUom__m = 'm',
		resqml2__ResqmlUom__N = 'N',
		resqml2__ResqmlUom__O = 'O',
		resqml2__ResqmlUom__P = 'P',
		resqml2__ResqmlUom__S = 'S',
		resqml2__ResqmlUom__s = 's',
		resqml2__ResqmlUom__t = 't',
		resqml2__ResqmlUom__T = 'T',
		resqml2__ResqmlUom__V = 'V',
		resqml2__ResqmlUom__W = 'W',
		resqml2__ResqmlUom___x0025 = 'u',
		resqml2__ResqmlUom___x0025_x005barea_x005d = 'v',
		resqml2__ResqmlUom___x0025_x005bmass_x005d = 'w',
		resqml2__ResqmlUom___x0025_x005bmolar_x005d = 'x',
		resqml2__ResqmlUom___x0025_x005bvol_x005d = 'y',
		resqml2__ResqmlUom___x0028bbl_x002fd_x0029_x002f_x0028bbl_x002fd_x0029 = 'z',
		resqml2__ResqmlUom___x0028m3_x002fd_x0029_x002f_x0028m3_x002fd_x0029 = 123,
		resqml2__ResqmlUom___x0028m3_x002fs_x0029_x002f_x0028m3_x002fs_x0029 = 124,
		resqml2__ResqmlUom__0_x002e001_x0020bbl_x002fft3 = 125,
		resqml2__ResqmlUom__0_x002e001_x0020bbl_x002fm3 = 126,
		resqml2__ResqmlUom__0_x002e001_x0020d_x002fft3 = 127,
		resqml2__ResqmlUom__0_x002e001_x0020gal_x005bUK_x005d_x002fbbl = 128,
		resqml2__ResqmlUom__0_x002e001_x0020gal_x005bUK_x005d_x002fgal_x005bUK_x005d = 129,
		resqml2__ResqmlUom__0_x002e001_x0020gal_x005bUS_x005d_x002fbbl = 130,
		resqml2__ResqmlUom__0_x002e001_x0020gal_x005bUS_x005d_x002fft3 = 131,
		resqml2__ResqmlUom__0_x002e001_x0020gal_x005bUS_x005d_x002fgal_x005bUS_x005d = 132,
		resqml2__ResqmlUom__0_x002e001_x0020h_x002fft = 133,
		resqml2__ResqmlUom__0_x002e001_x0020kPa2_x002fcP = 134,
		resqml2__ResqmlUom__0_x002e001_x0020lbm_x002fbbl = 135,
		resqml2__ResqmlUom__0_x002e001_x0020lbm_x002fgal_x005bUK_x005d = 136,
		resqml2__ResqmlUom__0_x002e001_x0020lbm_x002fgal_x005bUS_x005d = 137,
		resqml2__ResqmlUom__0_x002e001_x0020psi_x002fft = 138,
		resqml2__ResqmlUom__0_x002e001_x0020pt_x005bUK_x005d_x002fbbl = 139,
		resqml2__ResqmlUom__0_x002e001_x0020seca = 140,
		resqml2__ResqmlUom__0_x002e01_x0020bbl_x002fbbl = 141,
		resqml2__ResqmlUom__0_x002e01_x0020dega_x002fft = 142,
		resqml2__ResqmlUom__0_x002e01_x0020degF_x002fft = 143,
		resqml2__ResqmlUom__0_x002e01_x0020dm3_x002fkm = 144,
		resqml2__ResqmlUom__0_x002e01_x0020ft_x002fft = 145,
		resqml2__ResqmlUom__0_x002e01_x0020grain_x002fft3 = 146,
		resqml2__ResqmlUom__0_x002e01_x0020L_x002fkg = 147,
		resqml2__ResqmlUom__0_x002e01_x0020L_x002fkm = 148,
		resqml2__ResqmlUom__0_x002e01_x0020lbf_x002fft = 149,
		resqml2__ResqmlUom__0_x002e01_x0020lbf_x002fft2 = 150,
		resqml2__ResqmlUom__0_x002e01_x0020lbm_x002fft2 = 151,
		resqml2__ResqmlUom__0_x002e01_x0020psi_x002fft = 152,
		resqml2__ResqmlUom__0_x002e1_x0020ft = 153,
		resqml2__ResqmlUom__0_x002e1_x0020ft_x005bUS_x005d = 154,
		resqml2__ResqmlUom__0_x002e1_x0020gal_x005bUS_x005d_x002fbbl = 155,
		resqml2__ResqmlUom__0_x002e1_x0020in = 156,
		resqml2__ResqmlUom__0_x002e1_x0020L_x002fbbl = 157,
		resqml2__ResqmlUom__0_x002e1_x0020lbm_x002fbbl = 158,
		resqml2__ResqmlUom__0_x002e1_x0020pt_x005bUS_x005d_x002fbbl = 159,
		resqml2__ResqmlUom__0_x002e1_x0020yd = 160,
		resqml2__ResqmlUom__1_x002f_x0028kg_x002es_x0029 = 161,
		resqml2__ResqmlUom__1_x002f16_x0020in = 162,
		resqml2__ResqmlUom__1_x002f2_x0020ft = 163,
		resqml2__ResqmlUom__1_x002f2_x0020ms = 164,
		resqml2__ResqmlUom__1_x002f30_x0020cm3_x002fmin = 165,
		resqml2__ResqmlUom__1_x002f30_x0020dega_x002fft = 166,
		resqml2__ResqmlUom__1_x002f30_x0020dega_x002fm = 167,
		resqml2__ResqmlUom__1_x002f30_x0020lbf_x002fm = 168,
		resqml2__ResqmlUom__1_x002f30_x0020m_x002fm = 169,
		resqml2__ResqmlUom__1_x002f30_x0020N_x002fm = 170,
		resqml2__ResqmlUom__1_x002f32_x0020in = 171,
		resqml2__ResqmlUom__1_x002f64_x0020in = 172,
		resqml2__ResqmlUom__1_x002fa = 173,
		resqml2__ResqmlUom__1_x002fangstrom = 174,
		resqml2__ResqmlUom__1_x002fbar = 175,
		resqml2__ResqmlUom__1_x002fbbl = 176,
		resqml2__ResqmlUom__1_x002fcm = 177,
		resqml2__ResqmlUom__1_x002fd = 178,
		resqml2__ResqmlUom__1_x002fdegC = 179,
		resqml2__ResqmlUom__1_x002fdegF = 180,
		resqml2__ResqmlUom__1_x002fdegR = 181,
		resqml2__ResqmlUom__1_x002fft = 182,
		resqml2__ResqmlUom__1_x002fft2 = 183,
		resqml2__ResqmlUom__1_x002fft3 = 184,
		resqml2__ResqmlUom__1_x002fg = 185,
		resqml2__ResqmlUom__1_x002fgal_x005bUK_x005d = 186,
		resqml2__ResqmlUom__1_x002fgal_x005bUS_x005d = 187,
		resqml2__ResqmlUom__1_x002fH = 188,
		resqml2__ResqmlUom__1_x002fh = 189,
		resqml2__ResqmlUom__1_x002fin = 190,
		resqml2__ResqmlUom__1_x002fK = 191,
		resqml2__ResqmlUom__1_x002fkg = 192,
		resqml2__ResqmlUom__1_x002fkm2 = 193,
		resqml2__ResqmlUom__1_x002fkPa = 194,
		resqml2__ResqmlUom__1_x002fL = 195,
		resqml2__ResqmlUom__1_x002flbf = 196,
		resqml2__ResqmlUom__1_x002flbm = 197,
		resqml2__ResqmlUom__1_x002fm = 198,
		resqml2__ResqmlUom__1_x002fm2 = 199,
		resqml2__ResqmlUom__1_x002fm3 = 200,
		resqml2__ResqmlUom__1_x002fmi = 201,
		resqml2__ResqmlUom__1_x002fmi2 = 202,
		resqml2__ResqmlUom__1_x002fmin = 203,
		resqml2__ResqmlUom__1_x002fmm = 204,
		resqml2__ResqmlUom__1_x002fms = 205,
		resqml2__ResqmlUom__1_x002fN = 206,
		resqml2__ResqmlUom__1_x002fnm = 207,
		resqml2__ResqmlUom__1_x002fPa = 208,
		resqml2__ResqmlUom__1_x002fpPa = 209,
		resqml2__ResqmlUom__1_x002fpsi = 210,
		resqml2__ResqmlUom__1_x002fs = 211,
		resqml2__ResqmlUom__1_x002fupsi = 212,
		resqml2__ResqmlUom__1_x002fus = 213,
		resqml2__ResqmlUom__1_x002fuV = 214,
		resqml2__ResqmlUom__1_x002fV = 215,
		resqml2__ResqmlUom__1_x002fwk = 216,
		resqml2__ResqmlUom__1_x002fyd = 217,
		resqml2__ResqmlUom__10_x0020ft = 218,
		resqml2__ResqmlUom__10_x0020in = 219,
		resqml2__ResqmlUom__10_x0020km = 220,
		resqml2__ResqmlUom__10_x0020kN = 221,
		resqml2__ResqmlUom__10_x0020Mg_x002fm3 = 222,
		resqml2__ResqmlUom__100_x0020ft = 223,
		resqml2__ResqmlUom__100_x0020ka_x005bt_x005d = 224,
		resqml2__ResqmlUom__100_x0020km = 225,
		resqml2__ResqmlUom__1000_x0020bbl = 226,
		resqml2__ResqmlUom__1000_x0020bbl_x002eft_x002fd = 227,
		resqml2__ResqmlUom__1000_x0020bbl_x002fd = 228,
		resqml2__ResqmlUom__1000_x0020ft = 229,
		resqml2__ResqmlUom__1000_x0020ft_x002fh = 230,
		resqml2__ResqmlUom__1000_x0020ft_x002fs = 231,
		resqml2__ResqmlUom__1000_x0020ft3 = 232,
		resqml2__ResqmlUom__1000_x0020ft3_x002f_x0028d_x002eft_x0029 = 233,
		resqml2__ResqmlUom__1000_x0020ft3_x002f_x0028psi_x002ed_x0029 = 234,
		resqml2__ResqmlUom__1000_x0020ft3_x002fbbl = 235,
		resqml2__ResqmlUom__1000_x0020ft3_x002fd = 236,
		resqml2__ResqmlUom__1000_x0020gal_x005bUK_x005d = 237,
		resqml2__ResqmlUom__1000_x0020gal_x005bUS_x005d = 238,
		resqml2__ResqmlUom__1000_x0020lbf_x002eft = 239,
		resqml2__ResqmlUom__1000_x0020m3 = 240,
		resqml2__ResqmlUom__1000_x0020m3_x002f_x0028d_x002em_x0029 = 241,
		resqml2__ResqmlUom__1000_x0020m3_x002f_x0028h_x002em_x0029 = 242,
		resqml2__ResqmlUom__1000_x0020m3_x002fd = 243,
		resqml2__ResqmlUom__1000_x0020m3_x002fh = 244,
		resqml2__ResqmlUom__1000_x0020m3_x002fm3 = 245,
		resqml2__ResqmlUom__1000_x0020m4_x002fd = 246,
		resqml2__ResqmlUom__1E_6_x0020acre_x002eft_x002fbbl = 247,
		resqml2__ResqmlUom__1E_6_x0020bbl_x002fft3 = 248,
		resqml2__ResqmlUom__1E_6_x0020bbl_x002fm3 = 249,
		resqml2__ResqmlUom__1E_6_x0020gal_x005bUS_x005d = 250,
		resqml2__ResqmlUom__1E_6_x0020m3_x002f_x0028m3_x002edegC_x0029 = 251,
		resqml2__ResqmlUom__1E_6_x0020m3_x002f_x0028m3_x002edegF_x0029 = 252,
		resqml2__ResqmlUom__1E_9_x00201_x002fft = 253,
		resqml2__ResqmlUom__1E12_x0020ft3 = 254,
		resqml2__ResqmlUom__1E6_x0020_x0028ft3_x002fd_x0029_x002f_x0028bbl_x002fd_x0029 = 255,
		resqml2__ResqmlUom__1E6_x0020bbl = 256,
		resqml2__ResqmlUom__1E6_x0020bbl_x002f_x0028acre_x002eft_x0029 = 257,
		resqml2__ResqmlUom__1E6_x0020bbl_x002facre = 258,
		resqml2__ResqmlUom__1E6_x0020bbl_x002fd = 259,
		resqml2__ResqmlUom__1E6_x0020Btu_x005bIT_x005d = 260,
		resqml2__ResqmlUom__1E6_x0020Btu_x005bIT_x005d_x002fh = 261,
		resqml2__ResqmlUom__1E6_x0020ft3 = 262,
		resqml2__ResqmlUom__1E6_x0020ft3_x002f_x0028acre_x002eft_x0029 = 263,
		resqml2__ResqmlUom__1E6_x0020ft3_x002fbbl = 264,
		resqml2__ResqmlUom__1E6_x0020ft3_x002fd = 265,
		resqml2__ResqmlUom__1E6_x0020lbm_x002fa = 266,
		resqml2__ResqmlUom__1E6_x0020m3 = 267,
		resqml2__ResqmlUom__1E6_x0020m3_x002fd = 268,
		resqml2__ResqmlUom__1E9_x0020bbl = 269,
		resqml2__ResqmlUom__1E9_x0020ft3 = 270,
		resqml2__ResqmlUom__30_x0020ft = 271,
		resqml2__ResqmlUom__30_x0020m = 272,
		resqml2__ResqmlUom__A_x002eh = 273,
		resqml2__ResqmlUom__A_x002em2 = 274,
		resqml2__ResqmlUom__A_x002es = 275,
		resqml2__ResqmlUom__A_x002es_x002fkg = 276,
		resqml2__ResqmlUom__A_x002es_x002fm3 = 277,
		resqml2__ResqmlUom__A_x002fcm2 = 278,
		resqml2__ResqmlUom__A_x002fft2 = 279,
		resqml2__ResqmlUom__A_x002fm = 280,
		resqml2__ResqmlUom__A_x002fm2 = 281,
		resqml2__ResqmlUom__A_x002fmm = 282,
		resqml2__ResqmlUom__A_x002fmm2 = 283,
		resqml2__ResqmlUom__a_x005bt_x005d = 284,
		resqml2__ResqmlUom__acre = 285,
		resqml2__ResqmlUom__acre_x002eft = 286,
		resqml2__ResqmlUom__ag = 287,
		resqml2__ResqmlUom__aJ = 288,
		resqml2__ResqmlUom__angstrom = 289,
		resqml2__ResqmlUom__at = 290,
		resqml2__ResqmlUom__atm = 291,
		resqml2__ResqmlUom__atm_x002fft = 292,
		resqml2__ResqmlUom__atm_x002fh = 293,
		resqml2__ResqmlUom__atm_x002fhm = 294,
		resqml2__ResqmlUom__atm_x002fm = 295,
		resqml2__ResqmlUom__B_x002eW = 296,
		resqml2__ResqmlUom__b_x002fcm3 = 297,
		resqml2__ResqmlUom__B_x002fm = 298,
		resqml2__ResqmlUom__B_x002fO = 299,
		resqml2__ResqmlUom__bar = 300,
		resqml2__ResqmlUom__bar_x002fh = 301,
		resqml2__ResqmlUom__bar_x002fkm = 302,
		resqml2__ResqmlUom__bar_x002fm = 303,
		resqml2__ResqmlUom__bar2 = 304,
		resqml2__ResqmlUom__bar2_x002fcP = 305,
		resqml2__ResqmlUom__bbl = 306,
		resqml2__ResqmlUom__bbl_x002f_x0028acre_x002eft_x0029 = 307,
		resqml2__ResqmlUom__bbl_x002f_x0028d_x002eacre_x002eft_x0029 = 308,
		resqml2__ResqmlUom__bbl_x002f_x0028d_x002eft_x0029 = 309,
		resqml2__ResqmlUom__bbl_x002f_x0028ft_x002epsi_x002ed_x0029 = 310,
		resqml2__ResqmlUom__bbl_x002f_x0028kPa_x002ed_x0029 = 311,
		resqml2__ResqmlUom__bbl_x002f_x0028psi_x002ed_x0029 = 312,
		resqml2__ResqmlUom__bbl_x002facre = 313,
		resqml2__ResqmlUom__bbl_x002fbbl = 314,
		resqml2__ResqmlUom__bbl_x002fd = 315,
		resqml2__ResqmlUom__bbl_x002fd2 = 316,
		resqml2__ResqmlUom__bbl_x002fft = 317,
		resqml2__ResqmlUom__bbl_x002fft3 = 318,
		resqml2__ResqmlUom__bbl_x002fh = 319,
		resqml2__ResqmlUom__bbl_x002fh2 = 320,
		resqml2__ResqmlUom__bbl_x002fin = 321,
		resqml2__ResqmlUom__bbl_x002fm3 = 322,
		resqml2__ResqmlUom__bbl_x002fmi = 323,
		resqml2__ResqmlUom__bbl_x002fmin = 324,
		resqml2__ResqmlUom__bbl_x002fpsi = 325,
		resqml2__ResqmlUom__bbl_x002fton_x005bUK_x005d = 326,
		resqml2__ResqmlUom__bbl_x002fton_x005bUS_x005d = 327,
		resqml2__ResqmlUom__Bd = 328,
		resqml2__ResqmlUom__bit = 329,
		resqml2__ResqmlUom__bit_x002fs = 330,
		resqml2__ResqmlUom__Bq = 331,
		resqml2__ResqmlUom__Bq_x002fkg = 332,
		resqml2__ResqmlUom__Btu_x005bIT_x005d = 333,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002ein_x002f_x0028h_x002eft2_x002edegF_x0029 = 334,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002eft_x002edegF_x0029 = 335,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002eft2_x0029 = 336,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002eft2_x002edegF_x0029 = 337,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002eft2_x002edegR_x0029 = 338,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002eft3_x0029 = 339,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002eft3_x002edegF_x0029 = 340,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002em2_x002edegC_x0029 = 341,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028hp_x002eh_x0029 = 342,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028lbm_x002edegF_x0029 = 343,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028lbm_x002edegR_x0029 = 344,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028lbmol_x002edegF_x0029 = 345,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028s_x002eft2_x0029 = 346,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028s_x002eft2_x002edegF_x0029 = 347,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028s_x002eft3_x0029 = 348,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028s_x002eft3_x002edegF_x0029 = 349,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002fbbl = 350,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002fft3 = 351,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002fgal_x005bUK_x005d = 352,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002fgal_x005bUS_x005d = 353,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002fh = 354,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002flbm = 355,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002flbmol = 356,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002fmin = 357,
		resqml2__ResqmlUom__Btu_x005bIT_x005d_x002fs = 358,
		resqml2__ResqmlUom__Btu_x005bth_x005d = 359,
		resqml2__ResqmlUom__Btu_x005bUK_x005d = 360,
		resqml2__ResqmlUom__byte = 361,
		resqml2__ResqmlUom__byte_x002fs = 362,
		resqml2__ResqmlUom__C_x002em = 363,
		resqml2__ResqmlUom__C_x002fcm2 = 364,
		resqml2__ResqmlUom__C_x002fcm3 = 365,
		resqml2__ResqmlUom__C_x002fg = 366,
		resqml2__ResqmlUom__C_x002fkg = 367,
		resqml2__ResqmlUom__C_x002fm2 = 368,
		resqml2__ResqmlUom__C_x002fm3 = 369,
		resqml2__ResqmlUom__C_x002fmm2 = 370,
		resqml2__ResqmlUom__C_x002fmm3 = 371,
		resqml2__ResqmlUom__ca = 372,
		resqml2__ResqmlUom__cA = 373,
		resqml2__ResqmlUom__cal_x005bIT_x005d = 374,
		resqml2__ResqmlUom__cal_x005bth_x005d = 375,
		resqml2__ResqmlUom__cal_x005bth_x005d_x002f_x0028g_x002eK_x0029 = 376,
		resqml2__ResqmlUom__cal_x005bth_x005d_x002f_x0028h_x002ecm_x002edegC_x0029 = 377,
		resqml2__ResqmlUom__cal_x005bth_x005d_x002f_x0028h_x002ecm2_x0029 = 378,
		resqml2__ResqmlUom__cal_x005bth_x005d_x002f_x0028h_x002ecm2_x002edegC_x0029 = 379,
		resqml2__ResqmlUom__cal_x005bth_x005d_x002f_x0028h_x002ecm3_x0029 = 380,
		resqml2__ResqmlUom__cal_x005bth_x005d_x002f_x0028mol_x002edegC_x0029 = 381,
		resqml2__ResqmlUom__cal_x005bth_x005d_x002f_x0028s_x002ecm_x002edegC_x0029 = 382,
		resqml2__ResqmlUom__cal_x005bth_x005d_x002f_x0028s_x002ecm2_x002edegC_x0029 = 383,
		resqml2__ResqmlUom__cal_x005bth_x005d_x002f_x0028s_x002ecm3_x0029 = 384,
		resqml2__ResqmlUom__cal_x005bth_x005d_x002fcm3 = 385,
		resqml2__ResqmlUom__cal_x005bth_x005d_x002fg = 386,
		resqml2__ResqmlUom__cal_x005bth_x005d_x002fh = 387,
		resqml2__ResqmlUom__cal_x005bth_x005d_x002fkg = 388,
		resqml2__ResqmlUom__cal_x005bth_x005d_x002flbm = 389,
		resqml2__ResqmlUom__cal_x005bth_x005d_x002fmL = 390,
		resqml2__ResqmlUom__cal_x005bth_x005d_x002fmm3 = 391,
		resqml2__ResqmlUom__cC = 392,
		resqml2__ResqmlUom__ccal_x005bth_x005d = 393,
		resqml2__ResqmlUom__ccgr = 394,
		resqml2__ResqmlUom__cd = 395,
		resqml2__ResqmlUom__cd_x002fm2 = 396,
		resqml2__ResqmlUom__cEuc = 397,
		resqml2__ResqmlUom__ceV = 398,
		resqml2__ResqmlUom__cF = 399,
		resqml2__ResqmlUom__cg = 400,
		resqml2__ResqmlUom__cgauss = 401,
		resqml2__ResqmlUom__cgr = 402,
		resqml2__ResqmlUom__cGy = 403,
		resqml2__ResqmlUom__cH = 404,
		resqml2__ResqmlUom__chain = 405,
		resqml2__ResqmlUom__chain_x005bBnA_x005d = 406,
		resqml2__ResqmlUom__chain_x005bBnB_x005d = 407,
		resqml2__ResqmlUom__chain_x005bCla_x005d = 408,
		resqml2__ResqmlUom__chain_x005bInd37_x005d = 409,
		resqml2__ResqmlUom__chain_x005bSe_x005d = 410,
		resqml2__ResqmlUom__chain_x005bSeT_x005d = 411,
		resqml2__ResqmlUom__chain_x005bUS_x005d = 412,
		resqml2__ResqmlUom__cHz = 413,
		resqml2__ResqmlUom__Ci = 414,
		resqml2__ResqmlUom__cJ = 415,
		resqml2__ResqmlUom__cm = 416,
		resqml2__ResqmlUom__cm_x002fa = 417,
		resqml2__ResqmlUom__cm_x002fs = 418,
		resqml2__ResqmlUom__cm_x002fs2 = 419,
		resqml2__ResqmlUom__cm2 = 420,
		resqml2__ResqmlUom__cm2_x002fg = 421,
		resqml2__ResqmlUom__cm2_x002fs = 422,
		resqml2__ResqmlUom__cm3 = 423,
		resqml2__ResqmlUom__cm3_x002fcm3 = 424,
		resqml2__ResqmlUom__cm3_x002fg = 425,
		resqml2__ResqmlUom__cm3_x002fh = 426,
		resqml2__ResqmlUom__cm3_x002fL = 427,
		resqml2__ResqmlUom__cm3_x002fm3 = 428,
		resqml2__ResqmlUom__cm3_x002fmin = 429,
		resqml2__ResqmlUom__cm3_x002fs = 430,
		resqml2__ResqmlUom__cm4 = 431,
		resqml2__ResqmlUom__cmH2O_x005b4degC_x005d = 432,
		resqml2__ResqmlUom__cN = 433,
		resqml2__ResqmlUom__cohm = 434,
		resqml2__ResqmlUom__cP = 435,
		resqml2__ResqmlUom__cPa = 436,
		resqml2__ResqmlUom__crd = 437,
		resqml2__ResqmlUom__cS = 438,
		resqml2__ResqmlUom__cs = 439,
		resqml2__ResqmlUom__cSt = 440,
		resqml2__ResqmlUom__ct = 441,
		resqml2__ResqmlUom__cT = 442,
		resqml2__ResqmlUom__cu = 443,
		resqml2__ResqmlUom__cV = 444,
		resqml2__ResqmlUom__cW = 445,
		resqml2__ResqmlUom__cWb = 446,
		resqml2__ResqmlUom__cwt_x005bUK_x005d = 447,
		resqml2__ResqmlUom__cwt_x005bUS_x005d = 448,
		resqml2__ResqmlUom__D_x002eft = 449,
		resqml2__ResqmlUom__D_x002em = 450,
		resqml2__ResqmlUom__D_x002f_x0028Pa_x002es_x0029 = 451,
		resqml2__ResqmlUom__d_x002fbbl = 452,
		resqml2__ResqmlUom__D_x002fcP = 453,
		resqml2__ResqmlUom__d_x002fft3 = 454,
		resqml2__ResqmlUom__d_x002fm3 = 455,
		resqml2__ResqmlUom__D_x005bAPI_x005d = 456,
		resqml2__ResqmlUom__dA = 457,
		resqml2__ResqmlUom__dam = 458,
		resqml2__ResqmlUom__daN = 459,
		resqml2__ResqmlUom__daN_x002em = 460,
		resqml2__ResqmlUom__dAPI = 461,
		resqml2__ResqmlUom__dB = 462,
		resqml2__ResqmlUom__dB_x002eMW = 463,
		resqml2__ResqmlUom__dB_x002emW = 464,
		resqml2__ResqmlUom__dB_x002eW = 465,
		resqml2__ResqmlUom__dB_x002fft = 466,
		resqml2__ResqmlUom__dB_x002fkm = 467,
		resqml2__ResqmlUom__dB_x002fm = 468,
		resqml2__ResqmlUom__dB_x002fO = 469,
		resqml2__ResqmlUom__dC = 470,
		resqml2__ResqmlUom__dcal_x005bth_x005d = 471,
		resqml2__ResqmlUom__dega = 472,
		resqml2__ResqmlUom__dega_x002fft = 473,
		resqml2__ResqmlUom__dega_x002fh = 474,
		resqml2__ResqmlUom__dega_x002fm = 475,
		resqml2__ResqmlUom__dega_x002fmin = 476,
		resqml2__ResqmlUom__dega_x002fs = 477,
		resqml2__ResqmlUom__degC = 478,
		resqml2__ResqmlUom__degC_x002em2_x002eh_x002fkcal_x005bth_x005d = 479,
		resqml2__ResqmlUom__degC_x002fft = 480,
		resqml2__ResqmlUom__degC_x002fh = 481,
		resqml2__ResqmlUom__degC_x002fhm = 482,
		resqml2__ResqmlUom__degC_x002fkm = 483,
		resqml2__ResqmlUom__degC_x002fkPa = 484,
		resqml2__ResqmlUom__degC_x002fm = 485,
		resqml2__ResqmlUom__degC_x002fmin = 486,
		resqml2__ResqmlUom__degC_x002fs = 487,
		resqml2__ResqmlUom__degF = 488,
		resqml2__ResqmlUom__degF_x002eft2_x002eh_x002fBtu_x005bIT_x005d = 489,
		resqml2__ResqmlUom__degF_x002fft = 490,
		resqml2__ResqmlUom__degF_x002fh = 491,
		resqml2__ResqmlUom__degF_x002fm = 492,
		resqml2__ResqmlUom__degF_x002fmin = 493,
		resqml2__ResqmlUom__degF_x002fpsi = 494,
		resqml2__ResqmlUom__degF_x002fs = 495,
		resqml2__ResqmlUom__degR = 496,
		resqml2__ResqmlUom__dEuc = 497,
		resqml2__ResqmlUom__deV = 498,
		resqml2__ResqmlUom__dF = 499,
		resqml2__ResqmlUom__dgauss = 500,
		resqml2__ResqmlUom__dGy = 501,
		resqml2__ResqmlUom__dH = 502,
		resqml2__ResqmlUom__dHz = 503,
		resqml2__ResqmlUom__dJ = 504,
		resqml2__ResqmlUom__dm = 505,
		resqml2__ResqmlUom__dm_x002fs = 506,
		resqml2__ResqmlUom__dm3 = 507,
		resqml2__ResqmlUom__dm3_x002f_x0028kW_x002eh_x0029 = 508,
		resqml2__ResqmlUom__dm3_x002fkg = 509,
		resqml2__ResqmlUom__dm3_x002fkmol = 510,
		resqml2__ResqmlUom__dm3_x002fm = 511,
		resqml2__ResqmlUom__dm3_x002fm3 = 512,
		resqml2__ResqmlUom__dm3_x002fMJ = 513,
		resqml2__ResqmlUom__dm3_x002fs = 514,
		resqml2__ResqmlUom__dm3_x002fs2 = 515,
		resqml2__ResqmlUom__dm3_x002ft = 516,
		resqml2__ResqmlUom__dN = 517,
		resqml2__ResqmlUom__dN_x002em = 518,
		resqml2__ResqmlUom__dohm = 519,
		resqml2__ResqmlUom__dP = 520,
		resqml2__ResqmlUom__dPa = 521,
		resqml2__ResqmlUom__drd = 522,
		resqml2__ResqmlUom__ds = 523,
		resqml2__ResqmlUom__dS = 524,
		resqml2__ResqmlUom__dT = 525,
		resqml2__ResqmlUom__dV = 526,
		resqml2__ResqmlUom__dW = 527,
		resqml2__ResqmlUom__dWb = 528,
		resqml2__ResqmlUom__dyne = 529,
		resqml2__ResqmlUom__dyne_x002ecm2 = 530,
		resqml2__ResqmlUom__dyne_x002es_x002fcm2 = 531,
		resqml2__ResqmlUom__dyne_x002fcm = 532,
		resqml2__ResqmlUom__dyne_x002fcm2 = 533,
		resqml2__ResqmlUom__EA = 534,
		resqml2__ResqmlUom__Ea_x005bt_x005d = 535,
		resqml2__ResqmlUom__EC = 536,
		resqml2__ResqmlUom__Ecal_x005bth_x005d = 537,
		resqml2__ResqmlUom__EEuc = 538,
		resqml2__ResqmlUom__EeV = 539,
		resqml2__ResqmlUom__EF = 540,
		resqml2__ResqmlUom__Eg = 541,
		resqml2__ResqmlUom__Egauss = 542,
		resqml2__ResqmlUom__EGy = 543,
		resqml2__ResqmlUom__EH = 544,
		resqml2__ResqmlUom__EHz = 545,
		resqml2__ResqmlUom__EJ = 546,
		resqml2__ResqmlUom__EJ_x002fa = 547,
		resqml2__ResqmlUom__Em = 548,
		resqml2__ResqmlUom__EN = 549,
		resqml2__ResqmlUom__Eohm = 550,
		resqml2__ResqmlUom__EP = 551,
		resqml2__ResqmlUom__EPa = 552,
		resqml2__ResqmlUom__Erd = 553,
		resqml2__ResqmlUom__erg = 554,
		resqml2__ResqmlUom__erg_x002fa = 555,
		resqml2__ResqmlUom__erg_x002fcm2 = 556,
		resqml2__ResqmlUom__erg_x002fcm3 = 557,
		resqml2__ResqmlUom__erg_x002fg = 558,
		resqml2__ResqmlUom__erg_x002fkg = 559,
		resqml2__ResqmlUom__erg_x002fm3 = 560,
		resqml2__ResqmlUom__ES = 561,
		resqml2__ResqmlUom__ET = 562,
		resqml2__ResqmlUom__Euc = 563,
		resqml2__ResqmlUom__eV = 564,
		resqml2__ResqmlUom__EW = 565,
		resqml2__ResqmlUom__EWb = 566,
		resqml2__ResqmlUom__F_x002fm = 567,
		resqml2__ResqmlUom__fa = 568,
		resqml2__ResqmlUom__fA = 569,
		resqml2__ResqmlUom__fathom = 570,
		resqml2__ResqmlUom__fC = 571,
		resqml2__ResqmlUom__fcal_x005bth_x005d = 572,
		resqml2__ResqmlUom__fEuc = 573,
		resqml2__ResqmlUom__feV = 574,
		resqml2__ResqmlUom__fF = 575,
		resqml2__ResqmlUom__fg = 576,
		resqml2__ResqmlUom__fgauss = 577,
		resqml2__ResqmlUom__fGy = 578,
		resqml2__ResqmlUom__fH = 579,
		resqml2__ResqmlUom__fHz = 580,
		resqml2__ResqmlUom__fJ = 581,
		resqml2__ResqmlUom__floz_x005bUK_x005d = 582,
		resqml2__ResqmlUom__floz_x005bUS_x005d = 583,
		resqml2__ResqmlUom__fm = 584,
		resqml2__ResqmlUom__fN = 585,
		resqml2__ResqmlUom__fohm = 586,
		resqml2__ResqmlUom__footcandle = 587,
		resqml2__ResqmlUom__footcandle_x002es = 588,
		resqml2__ResqmlUom__fP = 589,
		resqml2__ResqmlUom__fPa = 590,
		resqml2__ResqmlUom__frd = 591,
		resqml2__ResqmlUom__fS = 592,
		resqml2__ResqmlUom__ft = 593,
		resqml2__ResqmlUom__fT = 594,
		resqml2__ResqmlUom__ft_x002fbbl = 595,
		resqml2__ResqmlUom__ft_x002fd = 596,
		resqml2__ResqmlUom__ft_x002fdegF = 597,
		resqml2__ResqmlUom__ft_x002fft = 598,
		resqml2__ResqmlUom__ft_x002fft3 = 599,
		resqml2__ResqmlUom__ft_x002fgal_x005bUS_x005d = 600,
		resqml2__ResqmlUom__ft_x002fh = 601,
		resqml2__ResqmlUom__ft_x002fin = 602,
		resqml2__ResqmlUom__ft_x002flbm = 603,
		resqml2__ResqmlUom__ft_x002fm = 604,
		resqml2__ResqmlUom__ft_x002fmi = 605,
		resqml2__ResqmlUom__ft_x002fmin = 606,
		resqml2__ResqmlUom__ft_x002fms = 607,
		resqml2__ResqmlUom__ft_x002fpsi = 608,
		resqml2__ResqmlUom__ft_x002fs = 609,
		resqml2__ResqmlUom__ft_x002fs2 = 610,
		resqml2__ResqmlUom__ft_x002fus = 611,
		resqml2__ResqmlUom__ft_x005bBnA_x005d = 612,
		resqml2__ResqmlUom__ft_x005bBnB_x005d = 613,
		resqml2__ResqmlUom__ft_x005bBr36_x005d = 614,
		resqml2__ResqmlUom__ft_x005bBr65_x005d = 615,
		resqml2__ResqmlUom__ft_x005bCla_x005d = 616,
		resqml2__ResqmlUom__ft_x005bGC_x005d = 617,
		resqml2__ResqmlUom__ft_x005bInd_x005d = 618,
		resqml2__ResqmlUom__ft_x005bInd37_x005d = 619,
		resqml2__ResqmlUom__ft_x005bInd62_x005d = 620,
		resqml2__ResqmlUom__ft_x005bInd75_x005d = 621,
		resqml2__ResqmlUom__ft_x005bSe_x005d = 622,
		resqml2__ResqmlUom__ft_x005bSeT_x005d = 623,
		resqml2__ResqmlUom__ft_x005bUS_x005d = 624,
		resqml2__ResqmlUom__ft2 = 625,
		resqml2__ResqmlUom__ft2_x002fh = 626,
		resqml2__ResqmlUom__ft2_x002fin3 = 627,
		resqml2__ResqmlUom__ft2_x002flbm = 628,
		resqml2__ResqmlUom__ft2_x002fs = 629,
		resqml2__ResqmlUom__ft3 = 630,
		resqml2__ResqmlUom__ft3_x002f_x0028d_x002eft_x0029 = 631,
		resqml2__ResqmlUom__ft3_x002f_x0028ft_x002epsi_x002ed_x0029 = 632,
		resqml2__ResqmlUom__ft3_x002f_x0028min_x002eft2_x0029 = 633,
		resqml2__ResqmlUom__ft3_x002f_x0028s_x002eft2_x0029 = 634,
		resqml2__ResqmlUom__ft3_x002fbbl = 635,
		resqml2__ResqmlUom__ft3_x002fd = 636,
		resqml2__ResqmlUom__ft3_x002fd2 = 637,
		resqml2__ResqmlUom__ft3_x002fft = 638,
		resqml2__ResqmlUom__ft3_x002fft2 = 639,
		resqml2__ResqmlUom__ft3_x002fft3 = 640,
		resqml2__ResqmlUom__ft3_x002fh = 641,
		resqml2__ResqmlUom__ft3_x002fh2 = 642,
		resqml2__ResqmlUom__ft3_x002fkg = 643,
		resqml2__ResqmlUom__ft3_x002flbm = 644,
		resqml2__ResqmlUom__ft3_x002flbmol = 645,
		resqml2__ResqmlUom__ft3_x002fmin = 646,
		resqml2__ResqmlUom__ft3_x002fmin2 = 647,
		resqml2__ResqmlUom__ft3_x002frad = 648,
		resqml2__ResqmlUom__ft3_x002fs = 649,
		resqml2__ResqmlUom__ft3_x002fs2 = 650,
		resqml2__ResqmlUom__ft3_x002fsack_x005b94lbm_x005d = 651,
		resqml2__ResqmlUom__fur_x005bUS_x005d = 652,
		resqml2__ResqmlUom__fV = 653,
		resqml2__ResqmlUom__fW = 654,
		resqml2__ResqmlUom__fWb = 655,
		resqml2__ResqmlUom__g_x002eft_x002f_x0028cm3_x002es_x0029 = 656,
		resqml2__ResqmlUom__g_x002em_x002f_x0028cm3_x002es_x0029 = 657,
		resqml2__ResqmlUom__g_x002fcm3 = 658,
		resqml2__ResqmlUom__g_x002fcm4 = 659,
		resqml2__ResqmlUom__g_x002fdm3 = 660,
		resqml2__ResqmlUom__g_x002fgal_x005bUK_x005d = 661,
		resqml2__ResqmlUom__g_x002fgal_x005bUS_x005d = 662,
		resqml2__ResqmlUom__g_x002fkg = 663,
		resqml2__ResqmlUom__g_x002fL = 664,
		resqml2__ResqmlUom__g_x002fm3 = 665,
		resqml2__ResqmlUom__g_x002fmol = 666,
		resqml2__ResqmlUom__g_x002fs = 667,
		resqml2__ResqmlUom__g_x002ft = 668,
		resqml2__ResqmlUom__GA = 669,
		resqml2__ResqmlUom__Ga_x005bt_x005d = 670,
		resqml2__ResqmlUom__Gal = 671,
		resqml2__ResqmlUom__gal_x005bUK_x005d = 672,
		resqml2__ResqmlUom__gal_x005bUK_x005d_x002f_x0028h_x002eft_x0029 = 673,
		resqml2__ResqmlUom__gal_x005bUK_x005d_x002f_x0028h_x002eft2_x0029 = 674,
		resqml2__ResqmlUom__gal_x005bUK_x005d_x002f_x0028h_x002ein_x0029 = 675,
		resqml2__ResqmlUom__gal_x005bUK_x005d_x002f_x0028h_x002ein2_x0029 = 676,
		resqml2__ResqmlUom__gal_x005bUK_x005d_x002f_x0028min_x002eft_x0029 = 677,
		resqml2__ResqmlUom__gal_x005bUK_x005d_x002f_x0028min_x002eft2_x0029 = 678,
		resqml2__ResqmlUom__gal_x005bUK_x005d_x002fd = 679,
		resqml2__ResqmlUom__gal_x005bUK_x005d_x002fft3 = 680,
		resqml2__ResqmlUom__gal_x005bUK_x005d_x002fh = 681,
		resqml2__ResqmlUom__gal_x005bUK_x005d_x002fh2 = 682,
		resqml2__ResqmlUom__gal_x005bUK_x005d_x002flbm = 683,
		resqml2__ResqmlUom__gal_x005bUK_x005d_x002fmi = 684,
		resqml2__ResqmlUom__gal_x005bUK_x005d_x002fmin = 685,
		resqml2__ResqmlUom__gal_x005bUK_x005d_x002fmin2 = 686,
		resqml2__ResqmlUom__gal_x005bUS_x005d = 687,
		resqml2__ResqmlUom__gal_x005bUS_x005d_x002f_x0028h_x002eft_x0029 = 688,
		resqml2__ResqmlUom__gal_x005bUS_x005d_x002f_x0028h_x002eft2_x0029 = 689,
		resqml2__ResqmlUom__gal_x005bUS_x005d_x002f_x0028h_x002ein_x0029 = 690,
		resqml2__ResqmlUom__gal_x005bUS_x005d_x002f_x0028h_x002ein2_x0029 = 691,
		resqml2__ResqmlUom__gal_x005bUS_x005d_x002f_x0028min_x002eft_x0029 = 692,
		resqml2__ResqmlUom__gal_x005bUS_x005d_x002f_x0028min_x002eft2_x0029 = 693,
		resqml2__ResqmlUom__gal_x005bUS_x005d_x002fbbl = 694,
		resqml2__ResqmlUom__gal_x005bUS_x005d_x002fd = 695,
		resqml2__ResqmlUom__gal_x005bUS_x005d_x002fft = 696,
		resqml2__ResqmlUom__gal_x005bUS_x005d_x002fft3 = 697,
		resqml2__ResqmlUom__gal_x005bUS_x005d_x002fh = 698,
		resqml2__ResqmlUom__gal_x005bUS_x005d_x002fh2 = 699,
		resqml2__ResqmlUom__gal_x005bUS_x005d_x002flbm = 700,
		resqml2__ResqmlUom__gal_x005bUS_x005d_x002fmi = 701,
		resqml2__ResqmlUom__gal_x005bUS_x005d_x002fmin = 702,
		resqml2__ResqmlUom__gal_x005bUS_x005d_x002fmin2 = 703,
		resqml2__ResqmlUom__gal_x005bUS_x005d_x002fsack_x005b94lbm_x005d = 704,
		resqml2__ResqmlUom__gal_x005bUS_x005d_x002fton_x005bUK_x005d = 705,
		resqml2__ResqmlUom__gal_x005bUS_x005d_x002fton_x005bUS_x005d = 706,
		resqml2__ResqmlUom__gAPI = 707,
		resqml2__ResqmlUom__gauss = 708,
		resqml2__ResqmlUom__gauss_x002fcm = 709,
		resqml2__ResqmlUom__GBq = 710,
		resqml2__ResqmlUom__GC = 711,
		resqml2__ResqmlUom__Gcal_x005bth_x005d = 712,
		resqml2__ResqmlUom__GEuc = 713,
		resqml2__ResqmlUom__GeV = 714,
		resqml2__ResqmlUom__gf = 715,
		resqml2__ResqmlUom__GF = 716,
		resqml2__ResqmlUom__Gg = 717,
		resqml2__ResqmlUom__Ggauss = 718,
		resqml2__ResqmlUom__GGy = 719,
		resqml2__ResqmlUom__GH = 720,
		resqml2__ResqmlUom__GHz = 721,
		resqml2__ResqmlUom__GJ = 722,
		resqml2__ResqmlUom__Gm = 723,
		resqml2__ResqmlUom__gn = 724,
		resqml2__ResqmlUom__GN = 725,
		resqml2__ResqmlUom__Gohm = 726,
		resqml2__ResqmlUom__gon = 727,
		resqml2__ResqmlUom__GP = 728,
		resqml2__ResqmlUom__GPa = 729,
		resqml2__ResqmlUom__GPa_x002fcm = 730,
		resqml2__ResqmlUom__GPa2 = 731,
		resqml2__ResqmlUom__grain = 732,
		resqml2__ResqmlUom__grain_x002fft3 = 733,
		resqml2__ResqmlUom__grain_x002fgal_x005bUS_x005d = 734,
		resqml2__ResqmlUom__Grd = 735,
		resqml2__ResqmlUom__GS = 736,
		resqml2__ResqmlUom__GT = 737,
		resqml2__ResqmlUom__GV = 738,
		resqml2__ResqmlUom__GW = 739,
		resqml2__ResqmlUom__GW_x002eh = 740,
		resqml2__ResqmlUom__GWb = 741,
		resqml2__ResqmlUom__Gy = 742,
		resqml2__ResqmlUom__h_x002fft3 = 743,
		resqml2__ResqmlUom__h_x002fkm = 744,
		resqml2__ResqmlUom__H_x002fm = 745,
		resqml2__ResqmlUom__h_x002fm3 = 746,
		resqml2__ResqmlUom__ha = 747,
		resqml2__ResqmlUom__ha_x002em = 748,
		resqml2__ResqmlUom__hbar = 749,
		resqml2__ResqmlUom__hg = 750,
		resqml2__ResqmlUom__hL = 751,
		resqml2__ResqmlUom__hm = 752,
		resqml2__ResqmlUom__hN = 753,
		resqml2__ResqmlUom__hp = 754,
		resqml2__ResqmlUom__hp_x002eh = 755,
		resqml2__ResqmlUom__hp_x002eh_x002fbbl = 756,
		resqml2__ResqmlUom__hp_x002eh_x002flbm = 757,
		resqml2__ResqmlUom__hp_x002fft3 = 758,
		resqml2__ResqmlUom__hp_x002fin2 = 759,
		resqml2__ResqmlUom__hp_x005belec_x005d = 760,
		resqml2__ResqmlUom__hp_x005bhyd_x005d = 761,
		resqml2__ResqmlUom__hp_x005bhyd_x005d_x002fin2 = 762,
		resqml2__ResqmlUom__hp_x005bmetric_x005d = 763,
		resqml2__ResqmlUom__hp_x005bmetric_x005d_x002eh = 764,
		resqml2__ResqmlUom__hs = 765,
		resqml2__ResqmlUom__Hz = 766,
		resqml2__ResqmlUom__in = 767,
		resqml2__ResqmlUom__in_x002f_x0028in_x002edegF_x0029 = 768,
		resqml2__ResqmlUom__in_x002fa = 769,
		resqml2__ResqmlUom__in_x002fmin = 770,
		resqml2__ResqmlUom__in_x002fs = 771,
		resqml2__ResqmlUom__in_x002fs2 = 772,
		resqml2__ResqmlUom__in_x005bUS_x005d = 773,
		resqml2__ResqmlUom__in2 = 774,
		resqml2__ResqmlUom__in2_x002fft2 = 775,
		resqml2__ResqmlUom__in2_x002fin2 = 776,
		resqml2__ResqmlUom__in2_x002fs = 777,
		resqml2__ResqmlUom__in3 = 778,
		resqml2__ResqmlUom__in3_x002fft = 779,
		resqml2__ResqmlUom__in4 = 780,
		resqml2__ResqmlUom__inH2O_x005b39degF_x005d = 781,
		resqml2__ResqmlUom__inH2O_x005b60degF_x005d = 782,
		resqml2__ResqmlUom__inHg_x005b32degF_x005d = 783,
		resqml2__ResqmlUom__inHg_x005b60degF_x005d = 784,
		resqml2__ResqmlUom__J_x002em_x002f_x0028s_x002em2_x002eK_x0029 = 785,
		resqml2__ResqmlUom__J_x002em_x002fm2 = 786,
		resqml2__ResqmlUom__J_x002f_x0028g_x002eK_x0029 = 787,
		resqml2__ResqmlUom__J_x002f_x0028kg_x002eK_x0029 = 788,
		resqml2__ResqmlUom__J_x002f_x0028mol_x002eK_x0029 = 789,
		resqml2__ResqmlUom__J_x002f_x0028s_x002em2_x002edegC_x0029 = 790,
		resqml2__ResqmlUom__J_x002fcm2 = 791,
		resqml2__ResqmlUom__J_x002fdm3 = 792,
		resqml2__ResqmlUom__J_x002fg = 793,
		resqml2__ResqmlUom__J_x002fK = 794,
		resqml2__ResqmlUom__J_x002fkg = 795,
		resqml2__ResqmlUom__J_x002fm = 796,
		resqml2__ResqmlUom__J_x002fm2 = 797,
		resqml2__ResqmlUom__J_x002fm3 = 798,
		resqml2__ResqmlUom__J_x002fmol = 799,
		resqml2__ResqmlUom__J_x002fs = 800,
		resqml2__ResqmlUom__K_x002em2_x002fkW = 801,
		resqml2__ResqmlUom__K_x002em2_x002fW = 802,
		resqml2__ResqmlUom__K_x002fkm = 803,
		resqml2__ResqmlUom__K_x002fm = 804,
		resqml2__ResqmlUom__K_x002fPa = 805,
		resqml2__ResqmlUom__K_x002fs = 806,
		resqml2__ResqmlUom__K_x002fW = 807,
		resqml2__ResqmlUom__kA = 808,
		resqml2__ResqmlUom__ka_x005bt_x005d = 809,
		resqml2__ResqmlUom__kC = 810,
		resqml2__ResqmlUom__kcal_x005bth_x005d = 811,
		resqml2__ResqmlUom__kcal_x005bth_x005d_x002em_x002fcm2 = 812,
		resqml2__ResqmlUom__kcal_x005bth_x005d_x002f_x0028h_x002em_x002edegC_x0029 = 813,
		resqml2__ResqmlUom__kcal_x005bth_x005d_x002f_x0028h_x002em2_x002edegC_x0029 = 814,
		resqml2__ResqmlUom__kcal_x005bth_x005d_x002f_x0028kg_x002edegC_x0029 = 815,
		resqml2__ResqmlUom__kcal_x005bth_x005d_x002fcm3 = 816,
		resqml2__ResqmlUom__kcal_x005bth_x005d_x002fg = 817,
		resqml2__ResqmlUom__kcal_x005bth_x005d_x002fh = 818,
		resqml2__ResqmlUom__kcal_x005bth_x005d_x002fkg = 819,
		resqml2__ResqmlUom__kcal_x005bth_x005d_x002fm3 = 820,
		resqml2__ResqmlUom__kcal_x005bth_x005d_x002fmol = 821,
		resqml2__ResqmlUom__kcd = 822,
		resqml2__ResqmlUom__kdyne = 823,
		resqml2__ResqmlUom__kEuc = 824,
		resqml2__ResqmlUom__keV = 825,
		resqml2__ResqmlUom__kF = 826,
		resqml2__ResqmlUom__kg = 827,
		resqml2__ResqmlUom__kg_x002em = 828,
		resqml2__ResqmlUom__kg_x002em_x002fcm2 = 829,
		resqml2__ResqmlUom__kg_x002em_x002fs = 830,
		resqml2__ResqmlUom__kg_x002em2 = 831,
		resqml2__ResqmlUom__kg_x002f_x0028kW_x002eh_x0029 = 832,
		resqml2__ResqmlUom__kg_x002f_x0028m_x002es_x0029 = 833,
		resqml2__ResqmlUom__kg_x002f_x0028m2_x002es_x0029 = 834,
		resqml2__ResqmlUom__kg_x002fd = 835,
		resqml2__ResqmlUom__kg_x002fdm3 = 836,
		resqml2__ResqmlUom__kg_x002fdm4 = 837,
		resqml2__ResqmlUom__kg_x002fh = 838,
		resqml2__ResqmlUom__kg_x002fJ = 839,
		resqml2__ResqmlUom__kg_x002fkg = 840,
		resqml2__ResqmlUom__kg_x002fL = 841,
		resqml2__ResqmlUom__kg_x002fm = 842,
		resqml2__ResqmlUom__kg_x002fm2 = 843,
		resqml2__ResqmlUom__kg_x002fm3 = 844,
		resqml2__ResqmlUom__kg_x002fm4 = 845,
		resqml2__ResqmlUom__kg_x002fmin = 846,
		resqml2__ResqmlUom__kg_x002fMJ = 847,
		resqml2__ResqmlUom__kg_x002fmol = 848,
		resqml2__ResqmlUom__kg_x002fs = 849,
		resqml2__ResqmlUom__kg_x002fsack_x005b94lbm_x005d = 850,
		resqml2__ResqmlUom__kg_x002ft = 851,
		resqml2__ResqmlUom__kgauss = 852,
		resqml2__ResqmlUom__kgf = 853,
		resqml2__ResqmlUom__kgf_x002em = 854,
		resqml2__ResqmlUom__kgf_x002em_x002fcm2 = 855,
		resqml2__ResqmlUom__kgf_x002em_x002fm = 856,
		resqml2__ResqmlUom__kgf_x002em2 = 857,
		resqml2__ResqmlUom__kgf_x002es_x002fm2 = 858,
		resqml2__ResqmlUom__kgf_x002fcm = 859,
		resqml2__ResqmlUom__kgf_x002fcm2 = 860,
		resqml2__ResqmlUom__kgf_x002fkgf = 861,
		resqml2__ResqmlUom__kgf_x002fm2 = 862,
		resqml2__ResqmlUom__kgf_x002fmm2 = 863,
		resqml2__ResqmlUom__kGy = 864,
		resqml2__ResqmlUom__kH = 865,
		resqml2__ResqmlUom__kHz = 866,
		resqml2__ResqmlUom__Kibyte = 867,
		resqml2__ResqmlUom__kJ = 868,
		resqml2__ResqmlUom__kJ_x002em_x002f_x0028h_x002em2_x002eK_x0029 = 869,
		resqml2__ResqmlUom__kJ_x002f_x0028h_x002em2_x002eK_x0029 = 870,
		resqml2__ResqmlUom__kJ_x002f_x0028kg_x002eK_x0029 = 871,
		resqml2__ResqmlUom__kJ_x002f_x0028kmol_x002eK_x0029 = 872,
		resqml2__ResqmlUom__kJ_x002fdm3 = 873,
		resqml2__ResqmlUom__kJ_x002fkg = 874,
		resqml2__ResqmlUom__kJ_x002fkmol = 875,
		resqml2__ResqmlUom__kJ_x002fm3 = 876,
		resqml2__ResqmlUom__klbf = 877,
		resqml2__ResqmlUom__klbm = 878,
		resqml2__ResqmlUom__klbm_x002fin = 879,
		resqml2__ResqmlUom__klx = 880,
		resqml2__ResqmlUom__km = 881,
		resqml2__ResqmlUom__km_x002fcm = 882,
		resqml2__ResqmlUom__km_x002fdm3 = 883,
		resqml2__ResqmlUom__km_x002fh = 884,
		resqml2__ResqmlUom__km_x002fL = 885,
		resqml2__ResqmlUom__km_x002fs = 886,
		resqml2__ResqmlUom__km2 = 887,
		resqml2__ResqmlUom__km3 = 888,
		resqml2__ResqmlUom__kmol = 889,
		resqml2__ResqmlUom__kmol_x002fh = 890,
		resqml2__ResqmlUom__kmol_x002fm3 = 891,
		resqml2__ResqmlUom__kmol_x002fs = 892,
		resqml2__ResqmlUom__kN = 893,
		resqml2__ResqmlUom__kN_x002em = 894,
		resqml2__ResqmlUom__kN_x002em2 = 895,
		resqml2__ResqmlUom__kN_x002fm = 896,
		resqml2__ResqmlUom__kN_x002fm2 = 897,
		resqml2__ResqmlUom__knot = 898,
		resqml2__ResqmlUom__kohm = 899,
		resqml2__ResqmlUom__kohm_x002em = 900,
		resqml2__ResqmlUom__kP = 901,
		resqml2__ResqmlUom__kPa = 902,
		resqml2__ResqmlUom__kPa_x002es_x002fm = 903,
		resqml2__ResqmlUom__kPa_x002fh = 904,
		resqml2__ResqmlUom__kPa_x002fhm = 905,
		resqml2__ResqmlUom__kPa_x002fm = 906,
		resqml2__ResqmlUom__kPa_x002fmin = 907,
		resqml2__ResqmlUom__kPa2 = 908,
		resqml2__ResqmlUom__kPa2_x002fcP = 909,
		resqml2__ResqmlUom__kpsi = 910,
		resqml2__ResqmlUom__kpsi2 = 911,
		resqml2__ResqmlUom__krad = 912,
		resqml2__ResqmlUom__krd = 913,
		resqml2__ResqmlUom__kS = 914,
		resqml2__ResqmlUom__kS_x002fm = 915,
		resqml2__ResqmlUom__kT = 916,
		resqml2__ResqmlUom__kV = 917,
		resqml2__ResqmlUom__kW = 918,
		resqml2__ResqmlUom__kW_x002eh = 919,
		resqml2__ResqmlUom__kW_x002eh_x002f_x0028kg_x002edegC_x0029 = 920,
		resqml2__ResqmlUom__kW_x002eh_x002fdm3 = 921,
		resqml2__ResqmlUom__kW_x002eh_x002fkg = 922,
		resqml2__ResqmlUom__kW_x002eh_x002fm3 = 923,
		resqml2__ResqmlUom__kW_x002f_x0028m2_x002eK_x0029 = 924,
		resqml2__ResqmlUom__kW_x002f_x0028m3_x002eK_x0029 = 925,
		resqml2__ResqmlUom__kW_x002fcm2 = 926,
		resqml2__ResqmlUom__kW_x002fm2 = 927,
		resqml2__ResqmlUom__kW_x002fm3 = 928,
		resqml2__ResqmlUom__kWb = 929,
		resqml2__ResqmlUom__L_x002f_x0028bar_x002emin_x0029 = 930,
		resqml2__ResqmlUom__L_x002fh = 931,
		resqml2__ResqmlUom__L_x002fkg = 932,
		resqml2__ResqmlUom__L_x002fkmol = 933,
		resqml2__ResqmlUom__L_x002fm = 934,
		resqml2__ResqmlUom__L_x002fm3 = 935,
		resqml2__ResqmlUom__L_x002fmin = 936,
		resqml2__ResqmlUom__L_x002fmol = 937,
		resqml2__ResqmlUom__L_x002fs = 938,
		resqml2__ResqmlUom__L_x002fs2 = 939,
		resqml2__ResqmlUom__L_x002ft = 940,
		resqml2__ResqmlUom__L_x002fton_x005bUK_x005d = 941,
		resqml2__ResqmlUom__lbf = 942,
		resqml2__ResqmlUom__lbf_x002eft = 943,
		resqml2__ResqmlUom__lbf_x002eft_x002fbbl = 944,
		resqml2__ResqmlUom__lbf_x002eft_x002fgal_x005bUS_x005d = 945,
		resqml2__ResqmlUom__lbf_x002eft_x002fin = 946,
		resqml2__ResqmlUom__lbf_x002eft_x002fin2 = 947,
		resqml2__ResqmlUom__lbf_x002eft_x002flbm = 948,
		resqml2__ResqmlUom__lbf_x002eft_x002fmin = 949,
		resqml2__ResqmlUom__lbf_x002eft_x002fs = 950,
		resqml2__ResqmlUom__lbf_x002ein = 951,
		resqml2__ResqmlUom__lbf_x002ein_x002fin = 952,
		resqml2__ResqmlUom__lbf_x002ein2 = 953,
		resqml2__ResqmlUom__lbf_x002es_x002fft2 = 954,
		resqml2__ResqmlUom__lbf_x002es_x002fin2 = 955,
		resqml2__ResqmlUom__lbf_x002fft = 956,
		resqml2__ResqmlUom__lbf_x002fft2 = 957,
		resqml2__ResqmlUom__lbf_x002fft3 = 958,
		resqml2__ResqmlUom__lbf_x002fgal_x005bUS_x005d = 959,
		resqml2__ResqmlUom__lbf_x002fin = 960,
		resqml2__ResqmlUom__lbf_x002flbf = 961,
		resqml2__ResqmlUom__lbm = 962,
		resqml2__ResqmlUom__lbm_x002eft = 963,
		resqml2__ResqmlUom__lbm_x002eft_x002fs = 964,
		resqml2__ResqmlUom__lbm_x002eft2 = 965,
		resqml2__ResqmlUom__lbm_x002eft2_x002fs2 = 966,
		resqml2__ResqmlUom__lbm_x002f_x0028ft_x002eh_x0029 = 967,
		resqml2__ResqmlUom__lbm_x002f_x0028ft_x002es_x0029 = 968,
		resqml2__ResqmlUom__lbm_x002f_x0028ft2_x002eh_x0029 = 969,
		resqml2__ResqmlUom__lbm_x002f_x0028ft2_x002es_x0029 = 970,
		resqml2__ResqmlUom__lbm_x002f_x0028gal_x005bUK_x005d_x002eft_x0029 = 971,
		resqml2__ResqmlUom__lbm_x002f_x0028gal_x005bUS_x005d_x002eft_x0029 = 972,
		resqml2__ResqmlUom__lbm_x002f_x0028hp_x002eh_x0029 = 973,
		resqml2__ResqmlUom__lbm_x002fbbl = 974,
		resqml2__ResqmlUom__lbm_x002fd = 975,
		resqml2__ResqmlUom__lbm_x002fft = 976,
		resqml2__ResqmlUom__lbm_x002fft2 = 977,
		resqml2__ResqmlUom__lbm_x002fft3 = 978,
		resqml2__ResqmlUom__lbm_x002fft4 = 979,
		resqml2__ResqmlUom__lbm_x002fgal_x005bUK_x005d = 980,
		resqml2__ResqmlUom__lbm_x002fgal_x005bUS_x005d = 981,
		resqml2__ResqmlUom__lbm_x002fh = 982,
		resqml2__ResqmlUom__lbm_x002fin3 = 983,
		resqml2__ResqmlUom__lbm_x002flbmol = 984,
		resqml2__ResqmlUom__lbm_x002fmin = 985,
		resqml2__ResqmlUom__lbm_x002fs = 986,
		resqml2__ResqmlUom__lbmol = 987,
		resqml2__ResqmlUom__lbmol_x002f_x0028h_x002eft2_x0029 = 988,
		resqml2__ResqmlUom__lbmol_x002f_x0028s_x002eft2_x0029 = 989,
		resqml2__ResqmlUom__lbmol_x002fft3 = 990,
		resqml2__ResqmlUom__lbmol_x002fgal_x005bUK_x005d = 991,
		resqml2__ResqmlUom__lbmol_x002fgal_x005bUS_x005d = 992,
		resqml2__ResqmlUom__lbmol_x002fh = 993,
		resqml2__ResqmlUom__lbmol_x002fs = 994,
		resqml2__ResqmlUom__link = 995,
		resqml2__ResqmlUom__link_x005bBnA_x005d = 996,
		resqml2__ResqmlUom__link_x005bBnB_x005d = 997,
		resqml2__ResqmlUom__link_x005bCla_x005d = 998,
		resqml2__ResqmlUom__link_x005bSe_x005d = 999,
		resqml2__ResqmlUom__link_x005bSeT_x005d = 1000,
		resqml2__ResqmlUom__link_x005bUS_x005d = 1001,
		resqml2__ResqmlUom__lm = 1002,
		resqml2__ResqmlUom__lm_x002es = 1003,
		resqml2__ResqmlUom__lm_x002fm2 = 1004,
		resqml2__ResqmlUom__lm_x002fW = 1005,
		resqml2__ResqmlUom__lx = 1006,
		resqml2__ResqmlUom__lx_x002es = 1007,
		resqml2__ResqmlUom__m_x002f_x0028m_x002eK_x0029 = 1008,
		resqml2__ResqmlUom__m_x002fcm = 1009,
		resqml2__ResqmlUom__m_x002fd = 1010,
		resqml2__ResqmlUom__m_x002fh = 1011,
		resqml2__ResqmlUom__m_x002fK = 1012,
		resqml2__ResqmlUom__m_x002fkg = 1013,
		resqml2__ResqmlUom__m_x002fkm = 1014,
		resqml2__ResqmlUom__m_x002fkPa = 1015,
		resqml2__ResqmlUom__m_x002fm = 1016,
		resqml2__ResqmlUom__m_x002fm3 = 1017,
		resqml2__ResqmlUom__m_x002fmin = 1018,
		resqml2__ResqmlUom__m_x002fms = 1019,
		resqml2__ResqmlUom__m_x002fPa = 1020,
		resqml2__ResqmlUom__m_x002fs = 1021,
		resqml2__ResqmlUom__m_x002fs2 = 1022,
		resqml2__ResqmlUom__m_x005bGer_x005d = 1023,
		resqml2__ResqmlUom__m2 = 1024,
		resqml2__ResqmlUom__m2_x002f_x0028kPa_x002ed_x0029 = 1025,
		resqml2__ResqmlUom__m2_x002f_x0028Pa_x002es_x0029 = 1026,
		resqml2__ResqmlUom__m2_x002fcm3 = 1027,
		resqml2__ResqmlUom__m2_x002fd = 1028,
		resqml2__ResqmlUom__m2_x002fg = 1029,
		resqml2__ResqmlUom__m2_x002fh = 1030,
		resqml2__ResqmlUom__m2_x002fkg = 1031,
		resqml2__ResqmlUom__m2_x002fm2 = 1032,
		resqml2__ResqmlUom__m2_x002fm3 = 1033,
		resqml2__ResqmlUom__m2_x002fmol = 1034,
		resqml2__ResqmlUom__m2_x002fs = 1035,
		resqml2__ResqmlUom__m3 = 1036,
		resqml2__ResqmlUom__m3_x002f_x0028bar_x002ed_x0029 = 1037,
		resqml2__ResqmlUom__m3_x002f_x0028bar_x002eh_x0029 = 1038,
		resqml2__ResqmlUom__m3_x002f_x0028bar_x002emin_x0029 = 1039,
		resqml2__ResqmlUom__m3_x002f_x0028d_x002em_x0029 = 1040,
		resqml2__ResqmlUom__m3_x002f_x0028h_x002em_x0029 = 1041,
		resqml2__ResqmlUom__m3_x002f_x0028ha_x002em_x0029 = 1042,
		resqml2__ResqmlUom__m3_x002f_x0028kPa_x002ed_x0029 = 1043,
		resqml2__ResqmlUom__m3_x002f_x0028kPa_x002eh_x0029 = 1044,
		resqml2__ResqmlUom__m3_x002f_x0028kW_x002eh_x0029 = 1045,
		resqml2__ResqmlUom__m3_x002f_x0028m3_x002eK_x0029 = 1046,
		resqml2__ResqmlUom__m3_x002f_x0028Pa_x002es_x0029 = 1047,
		resqml2__ResqmlUom__m3_x002f_x0028psi_x002ed_x0029 = 1048,
		resqml2__ResqmlUom__m3_x002f_x0028s_x002eft_x0029 = 1049,
		resqml2__ResqmlUom__m3_x002f_x0028s_x002em_x0029 = 1050,
		resqml2__ResqmlUom__m3_x002f_x0028s_x002em2_x0029 = 1051,
		resqml2__ResqmlUom__m3_x002f_x0028s_x002em3_x0029 = 1052,
		resqml2__ResqmlUom__m3_x002fbbl = 1053,
		resqml2__ResqmlUom__m3_x002fd = 1054,
		resqml2__ResqmlUom__m3_x002fd2 = 1055,
		resqml2__ResqmlUom__m3_x002fg = 1056,
		resqml2__ResqmlUom__m3_x002fh = 1057,
		resqml2__ResqmlUom__m3_x002fJ = 1058,
		resqml2__ResqmlUom__m3_x002fkg = 1059,
		resqml2__ResqmlUom__m3_x002fkm = 1060,
		resqml2__ResqmlUom__m3_x002fkmol = 1061,
		resqml2__ResqmlUom__m3_x002fkPa = 1062,
		resqml2__ResqmlUom__m3_x002fm = 1063,
		resqml2__ResqmlUom__m3_x002fm2 = 1064,
		resqml2__ResqmlUom__m3_x002fm3 = 1065,
		resqml2__ResqmlUom__m3_x002fmin = 1066,
		resqml2__ResqmlUom__m3_x002fmol = 1067,
		resqml2__ResqmlUom__m3_x002fPa = 1068,
		resqml2__ResqmlUom__m3_x002frad = 1069,
		resqml2__ResqmlUom__m3_x002frev = 1070,
		resqml2__ResqmlUom__m3_x002fs = 1071,
		resqml2__ResqmlUom__m3_x002fs2 = 1072,
		resqml2__ResqmlUom__m3_x002ft = 1073,
		resqml2__ResqmlUom__m3_x002fton_x005bUK_x005d = 1074,
		resqml2__ResqmlUom__m3_x002fton_x005bUS_x005d = 1075,
		resqml2__ResqmlUom__m4 = 1076,
		resqml2__ResqmlUom__m4_x002fs = 1077,
		resqml2__ResqmlUom__mA = 1078,
		resqml2__ResqmlUom__MA = 1079,
		resqml2__ResqmlUom__mA_x002fcm2 = 1080,
		resqml2__ResqmlUom__mA_x002fft2 = 1081,
		resqml2__ResqmlUom__Ma_x005bt_x005d = 1082,
		resqml2__ResqmlUom__mbar = 1083,
		resqml2__ResqmlUom__MBq = 1084,
		resqml2__ResqmlUom__mC = 1085,
		resqml2__ResqmlUom__MC = 1086,
		resqml2__ResqmlUom__mC_x002fm2 = 1087,
		resqml2__ResqmlUom__Mcal_x005bth_x005d = 1088,
		resqml2__ResqmlUom__mcal_x005bth_x005d = 1089,
		resqml2__ResqmlUom__mCi = 1090,
		resqml2__ResqmlUom__mD = 1091,
		resqml2__ResqmlUom__mD_x002eft = 1092,
		resqml2__ResqmlUom__mD_x002eft2_x002f_x0028lbf_x002es_x0029 = 1093,
		resqml2__ResqmlUom__mD_x002ein2_x002f_x0028lbf_x002es_x0029 = 1094,
		resqml2__ResqmlUom__mD_x002em = 1095,
		resqml2__ResqmlUom__mD_x002f_x0028Pa_x002es_x0029 = 1096,
		resqml2__ResqmlUom__mD_x002fcP = 1097,
		resqml2__ResqmlUom__MEuc = 1098,
		resqml2__ResqmlUom__mEuc = 1099,
		resqml2__ResqmlUom__meV = 1100,
		resqml2__ResqmlUom__MeV = 1101,
		resqml2__ResqmlUom__mF = 1102,
		resqml2__ResqmlUom__MF = 1103,
		resqml2__ResqmlUom__Mg = 1104,
		resqml2__ResqmlUom__mg = 1105,
		resqml2__ResqmlUom__Mg_x002fa = 1106,
		resqml2__ResqmlUom__Mg_x002fd = 1107,
		resqml2__ResqmlUom__mg_x002fdm3 = 1108,
		resqml2__ResqmlUom__mg_x002fg = 1109,
		resqml2__ResqmlUom__mg_x002fgal_x005bUS_x005d = 1110,
		resqml2__ResqmlUom__Mg_x002fh = 1111,
		resqml2__ResqmlUom__Mg_x002fin = 1112,
		resqml2__ResqmlUom__mg_x002fJ = 1113,
		resqml2__ResqmlUom__mg_x002fkg = 1114,
		resqml2__ResqmlUom__mg_x002fL = 1115,
		resqml2__ResqmlUom__Mg_x002fm2 = 1116,
		resqml2__ResqmlUom__Mg_x002fm3 = 1117,
		resqml2__ResqmlUom__mg_x002fm3 = 1118,
		resqml2__ResqmlUom__Mg_x002fmin = 1119,
		resqml2__ResqmlUom__mGal = 1120,
		resqml2__ResqmlUom__Mgauss = 1121,
		resqml2__ResqmlUom__mgauss = 1122,
		resqml2__ResqmlUom__Mgf = 1123,
		resqml2__ResqmlUom__mgn = 1124,
		resqml2__ResqmlUom__MGy = 1125,
		resqml2__ResqmlUom__mGy = 1126,
		resqml2__ResqmlUom__MH = 1127,
		resqml2__ResqmlUom__mH = 1128,
		resqml2__ResqmlUom__mHz = 1129,
		resqml2__ResqmlUom__MHz = 1130,
		resqml2__ResqmlUom__mi = 1131,
		resqml2__ResqmlUom__mi_x002fgal_x005bUK_x005d = 1132,
		resqml2__ResqmlUom__mi_x002fgal_x005bUS_x005d = 1133,
		resqml2__ResqmlUom__mi_x002fh = 1134,
		resqml2__ResqmlUom__mi_x002fin = 1135,
		resqml2__ResqmlUom__mi_x005bnaut_x005d = 1136,
		resqml2__ResqmlUom__mi_x005bnautUK_x005d = 1137,
		resqml2__ResqmlUom__mi_x005bUS_x005d = 1138,
		resqml2__ResqmlUom__mi_x005bUS_x005d2 = 1139,
		resqml2__ResqmlUom__mi2 = 1140,
		resqml2__ResqmlUom__mi3 = 1141,
		resqml2__ResqmlUom__Mibyte = 1142,
		resqml2__ResqmlUom__mil = 1143,
		resqml2__ResqmlUom__mil_x002fa = 1144,
		resqml2__ResqmlUom__mila = 1145,
		resqml2__ResqmlUom__min_ = 1146,
		resqml2__ResqmlUom__min_x002fft = 1147,
		resqml2__ResqmlUom__min_x002fm = 1148,
		resqml2__ResqmlUom__mina = 1149,
		resqml2__ResqmlUom__mJ = 1150,
		resqml2__ResqmlUom__MJ = 1151,
		resqml2__ResqmlUom__MJ_x002fa = 1152,
		resqml2__ResqmlUom__mJ_x002fcm2 = 1153,
		resqml2__ResqmlUom__MJ_x002fkg = 1154,
		resqml2__ResqmlUom__MJ_x002fkmol = 1155,
		resqml2__ResqmlUom__MJ_x002fm = 1156,
		resqml2__ResqmlUom__mJ_x002fm2 = 1157,
		resqml2__ResqmlUom__MJ_x002fm3 = 1158,
		resqml2__ResqmlUom__mL = 1159,
		resqml2__ResqmlUom__mL_x002fgal_x005bUK_x005d = 1160,
		resqml2__ResqmlUom__mL_x002fgal_x005bUS_x005d = 1161,
		resqml2__ResqmlUom__mL_x002fmL = 1162,
		resqml2__ResqmlUom__Mm = 1163,
		resqml2__ResqmlUom__mm = 1164,
		resqml2__ResqmlUom__mm_x002f_x0028mm_x002eK_x0029 = 1165,
		resqml2__ResqmlUom__mm_x002fa = 1166,
		resqml2__ResqmlUom__mm_x002fs = 1167,
		resqml2__ResqmlUom__mm2 = 1168,
		resqml2__ResqmlUom__mm2_x002fmm2 = 1169,
		resqml2__ResqmlUom__mm2_x002fs = 1170,
		resqml2__ResqmlUom__mm3 = 1171,
		resqml2__ResqmlUom__mm3_x002fJ = 1172,
		resqml2__ResqmlUom__mmHg_x005b0degC_x005d = 1173,
		resqml2__ResqmlUom__mmol = 1174,
		resqml2__ResqmlUom__mN = 1175,
		resqml2__ResqmlUom__MN = 1176,
		resqml2__ResqmlUom__mN_x002em2 = 1177,
		resqml2__ResqmlUom__mN_x002fkm = 1178,
		resqml2__ResqmlUom__mN_x002fm = 1179,
		resqml2__ResqmlUom__mohm = 1180,
		resqml2__ResqmlUom__Mohm = 1181,
		resqml2__ResqmlUom__mol = 1182,
		resqml2__ResqmlUom__mol_x002em2_x002f_x0028mol_x002es_x0029 = 1183,
		resqml2__ResqmlUom__mol_x002f_x0028s_x002em2_x0029 = 1184,
		resqml2__ResqmlUom__mol_x002fm2 = 1185,
		resqml2__ResqmlUom__mol_x002fm3 = 1186,
		resqml2__ResqmlUom__mol_x002fmol = 1187,
		resqml2__ResqmlUom__mol_x002fs = 1188,
		resqml2__ResqmlUom__mP = 1189,
		resqml2__ResqmlUom__MP = 1190,
		resqml2__ResqmlUom__MPa = 1191,
		resqml2__ResqmlUom__mPa = 1192,
		resqml2__ResqmlUom__mPa_x002es = 1193,
		resqml2__ResqmlUom__MPa_x002es_x002fm = 1194,
		resqml2__ResqmlUom__MPa_x002fh = 1195,
		resqml2__ResqmlUom__MPa_x002fm = 1196,
		resqml2__ResqmlUom__Mpsi = 1197,
		resqml2__ResqmlUom__mrad = 1198,
		resqml2__ResqmlUom__Mrad = 1199,
		resqml2__ResqmlUom__Mrd = 1200,
		resqml2__ResqmlUom__mrd = 1201,
		resqml2__ResqmlUom__mrem = 1202,
		resqml2__ResqmlUom__mrem_x002fh = 1203,
		resqml2__ResqmlUom__MS = 1204,
		resqml2__ResqmlUom__mS = 1205,
		resqml2__ResqmlUom__ms = 1206,
		resqml2__ResqmlUom__ms_x002fcm = 1207,
		resqml2__ResqmlUom__mS_x002fcm = 1208,
		resqml2__ResqmlUom__ms_x002fft = 1209,
		resqml2__ResqmlUom__ms_x002fin = 1210,
		resqml2__ResqmlUom__mS_x002fm = 1211,
		resqml2__ResqmlUom__ms_x002fm = 1212,
		resqml2__ResqmlUom__ms_x002fs = 1213,
		resqml2__ResqmlUom__mSv = 1214,
		resqml2__ResqmlUom__mSv_x002fh = 1215,
		resqml2__ResqmlUom__mT = 1216,
		resqml2__ResqmlUom__mT_x002fdm = 1217,
		resqml2__ResqmlUom__MV = 1218,
		resqml2__ResqmlUom__mV = 1219,
		resqml2__ResqmlUom__mV_x002fft = 1220,
		resqml2__ResqmlUom__mV_x002fm = 1221,
		resqml2__ResqmlUom__MW = 1222,
		resqml2__ResqmlUom__mW = 1223,
		resqml2__ResqmlUom__MW_x002eh = 1224,
		resqml2__ResqmlUom__MW_x002eh_x002fkg = 1225,
		resqml2__ResqmlUom__MW_x002eh_x002fm3 = 1226,
		resqml2__ResqmlUom__mW_x002fm2 = 1227,
		resqml2__ResqmlUom__mWb = 1228,
		resqml2__ResqmlUom__MWb = 1229,
		resqml2__ResqmlUom__N_x002em = 1230,
		resqml2__ResqmlUom__N_x002em_x002fm = 1231,
		resqml2__ResqmlUom__N_x002em2 = 1232,
		resqml2__ResqmlUom__N_x002es_x002fm2 = 1233,
		resqml2__ResqmlUom__N_x002fm = 1234,
		resqml2__ResqmlUom__N_x002fm2 = 1235,
		resqml2__ResqmlUom__N_x002fm3 = 1236,
		resqml2__ResqmlUom__N_x002fmm2 = 1237,
		resqml2__ResqmlUom__N_x002fN = 1238,
		resqml2__ResqmlUom__nA = 1239,
		resqml2__ResqmlUom__na = 1240,
		resqml2__ResqmlUom__nAPI = 1241,
		resqml2__ResqmlUom__nC = 1242,
		resqml2__ResqmlUom__ncal_x005bth_x005d = 1243,
		resqml2__ResqmlUom__nCi = 1244,
		resqml2__ResqmlUom__nEuc = 1245,
		resqml2__ResqmlUom__neV = 1246,
		resqml2__ResqmlUom__nF = 1247,
		resqml2__ResqmlUom__ng = 1248,
		resqml2__ResqmlUom__ng_x002fg = 1249,
		resqml2__ResqmlUom__ng_x002fmg = 1250,
		resqml2__ResqmlUom__ngauss = 1251,
		resqml2__ResqmlUom__nGy = 1252,
		resqml2__ResqmlUom__nH = 1253,
		resqml2__ResqmlUom__nHz = 1254,
		resqml2__ResqmlUom__nJ = 1255,
		resqml2__ResqmlUom__nm = 1256,
		resqml2__ResqmlUom__nm_x002fs = 1257,
		resqml2__ResqmlUom__nN = 1258,
		resqml2__ResqmlUom__nohm = 1259,
		resqml2__ResqmlUom__nohm_x002emil2_x002fft = 1260,
		resqml2__ResqmlUom__nohm_x002emm2_x002fm = 1261,
		resqml2__ResqmlUom__nP = 1262,
		resqml2__ResqmlUom__nPa = 1263,
		resqml2__ResqmlUom__nrd = 1264,
		resqml2__ResqmlUom__nS = 1265,
		resqml2__ResqmlUom__ns = 1266,
		resqml2__ResqmlUom__ns_x002fft = 1267,
		resqml2__ResqmlUom__ns_x002fm = 1268,
		resqml2__ResqmlUom__nT = 1269,
		resqml2__ResqmlUom__nV = 1270,
		resqml2__ResqmlUom__nW = 1271,
		resqml2__ResqmlUom__nWb = 1272,
		resqml2__ResqmlUom__Oe = 1273,
		resqml2__ResqmlUom__ohm = 1274,
		resqml2__ResqmlUom__ohm_x002ecm = 1275,
		resqml2__ResqmlUom__ohm_x002em = 1276,
		resqml2__ResqmlUom__ohm_x002em2_x002fm = 1277,
		resqml2__ResqmlUom__ohm_x002fm = 1278,
		resqml2__ResqmlUom__ozf = 1279,
		resqml2__ResqmlUom__ozm = 1280,
		resqml2__ResqmlUom__ozm_x005btroy_x005d = 1281,
		resqml2__ResqmlUom__pA = 1282,
		resqml2__ResqmlUom__Pa = 1283,
		resqml2__ResqmlUom__Pa_x002es = 1284,
		resqml2__ResqmlUom__Pa_x002es_x002em3_x002fkg = 1285,
		resqml2__ResqmlUom__Pa_x002es_x002fm3 = 1286,
		resqml2__ResqmlUom__Pa_x002es2_x002fm3 = 1287,
		resqml2__ResqmlUom__Pa_x002fh = 1288,
		resqml2__ResqmlUom__Pa_x002fm = 1289,
		resqml2__ResqmlUom__Pa_x002fm3 = 1290,
		resqml2__ResqmlUom__Pa_x002fs = 1291,
		resqml2__ResqmlUom__Pa2 = 1292,
		resqml2__ResqmlUom__Pa2_x002f_x0028Pa_x002es_x0029 = 1293,
		resqml2__ResqmlUom__pC = 1294,
		resqml2__ResqmlUom__pcal_x005bth_x005d = 1295,
		resqml2__ResqmlUom__pCi = 1296,
		resqml2__ResqmlUom__pCi_x002fg = 1297,
		resqml2__ResqmlUom__pdl = 1298,
		resqml2__ResqmlUom__pdl_x002ecm2 = 1299,
		resqml2__ResqmlUom__pdl_x002eft = 1300,
		resqml2__ResqmlUom__pdl_x002fcm = 1301,
		resqml2__ResqmlUom__pEuc = 1302,
		resqml2__ResqmlUom__peV = 1303,
		resqml2__ResqmlUom__pF = 1304,
		resqml2__ResqmlUom__pg = 1305,
		resqml2__ResqmlUom__pgauss = 1306,
		resqml2__ResqmlUom__pGy = 1307,
		resqml2__ResqmlUom__pHz = 1308,
		resqml2__ResqmlUom__pJ = 1309,
		resqml2__ResqmlUom__pm = 1310,
		resqml2__ResqmlUom__pN = 1311,
		resqml2__ResqmlUom__pohm = 1312,
		resqml2__ResqmlUom__pP = 1313,
		resqml2__ResqmlUom__pPa = 1314,
		resqml2__ResqmlUom__ppk = 1315,
		resqml2__ResqmlUom__ppm = 1316,
		resqml2__ResqmlUom__ppm_x005bmass_x005d = 1317,
		resqml2__ResqmlUom__ppm_x005bvol_x005d = 1318,
		resqml2__ResqmlUom__ppm_x005bvol_x005d_x002fdegC = 1319,
		resqml2__ResqmlUom__ppm_x005bvol_x005d_x002fdegF = 1320,
		resqml2__ResqmlUom__prd = 1321,
		resqml2__ResqmlUom__ps = 1322,
		resqml2__ResqmlUom__pS = 1323,
		resqml2__ResqmlUom__psi = 1324,
		resqml2__ResqmlUom__psi_x002ed_x002fbbl = 1325,
		resqml2__ResqmlUom__psi_x002es = 1326,
		resqml2__ResqmlUom__psi_x002fft = 1327,
		resqml2__ResqmlUom__psi_x002fh = 1328,
		resqml2__ResqmlUom__psi_x002fm = 1329,
		resqml2__ResqmlUom__psi_x002fmin = 1330,
		resqml2__ResqmlUom__psi2 = 1331,
		resqml2__ResqmlUom__psi2_x002ed_x002f_x0028cP_x002eft3_x0029 = 1332,
		resqml2__ResqmlUom__psi2_x002fcP = 1333,
		resqml2__ResqmlUom__pT = 1334,
		resqml2__ResqmlUom__pt_x005bUK_x005d = 1335,
		resqml2__ResqmlUom__pt_x005bUK_x005d_x002f_x0028hp_x002eh_x0029 = 1336,
		resqml2__ResqmlUom__pt_x005bUS_x005d = 1337,
		resqml2__ResqmlUom__pV = 1338,
		resqml2__ResqmlUom__pW = 1339,
		resqml2__ResqmlUom__pWb = 1340,
		resqml2__ResqmlUom__qt_x005bUK_x005d = 1341,
		resqml2__ResqmlUom__qt_x005bUS_x005d = 1342,
		resqml2__ResqmlUom__quad = 1343,
		resqml2__ResqmlUom__quad_x002fa = 1344,
		resqml2__ResqmlUom__rad = 1345,
		resqml2__ResqmlUom__rad_x002fft = 1346,
		resqml2__ResqmlUom__rad_x002fft3 = 1347,
		resqml2__ResqmlUom__rad_x002fm = 1348,
		resqml2__ResqmlUom__rad_x002fm3 = 1349,
		resqml2__ResqmlUom__rad_x002fs = 1350,
		resqml2__ResqmlUom__rad_x002fs2 = 1351,
		resqml2__ResqmlUom__rd = 1352,
		resqml2__ResqmlUom__rem = 1353,
		resqml2__ResqmlUom__rem_x002fh = 1354,
		resqml2__ResqmlUom__rev = 1355,
		resqml2__ResqmlUom__rev_x002fft = 1356,
		resqml2__ResqmlUom__rev_x002fm = 1357,
		resqml2__ResqmlUom__rev_x002fs = 1358,
		resqml2__ResqmlUom__rod_x005bUS_x005d = 1359,
		resqml2__ResqmlUom__rpm = 1360,
		resqml2__ResqmlUom__rpm_x002fs = 1361,
		resqml2__ResqmlUom__s_x002fcm = 1362,
		resqml2__ResqmlUom__s_x002fft = 1363,
		resqml2__ResqmlUom__s_x002fft3 = 1364,
		resqml2__ResqmlUom__s_x002fin = 1365,
		resqml2__ResqmlUom__s_x002fkg = 1366,
		resqml2__ResqmlUom__s_x002fL = 1367,
		resqml2__ResqmlUom__S_x002fm = 1368,
		resqml2__ResqmlUom__s_x002fm = 1369,
		resqml2__ResqmlUom__s_x002fm3 = 1370,
		resqml2__ResqmlUom__s_x002fqt_x005bUK_x005d = 1371,
		resqml2__ResqmlUom__s_x002fqt_x005bUS_x005d = 1372,
		resqml2__ResqmlUom__s_x002fs = 1373,
		resqml2__ResqmlUom__sack_x005b94lbm_x005d = 1374,
		resqml2__ResqmlUom__seca = 1375,
		resqml2__ResqmlUom__section = 1376,
		resqml2__ResqmlUom__sr = 1377,
		resqml2__ResqmlUom__St = 1378,
		resqml2__ResqmlUom__Sv = 1379,
		resqml2__ResqmlUom__Sv_x002fh = 1380,
		resqml2__ResqmlUom__Sv_x002fs = 1381,
		resqml2__ResqmlUom__t_x002fa = 1382,
		resqml2__ResqmlUom__t_x002fd = 1383,
		resqml2__ResqmlUom__t_x002fh = 1384,
		resqml2__ResqmlUom__T_x002fm = 1385,
		resqml2__ResqmlUom__t_x002fm3 = 1386,
		resqml2__ResqmlUom__t_x002fmin = 1387,
		resqml2__ResqmlUom__TA = 1388,
		resqml2__ResqmlUom__Ta_x005bt_x005d = 1389,
		resqml2__ResqmlUom__TBq = 1390,
		resqml2__ResqmlUom__TC = 1391,
		resqml2__ResqmlUom__Tcal_x005bth_x005d = 1392,
		resqml2__ResqmlUom__TD_x005bAPI_x005d = 1393,
		resqml2__ResqmlUom__TD_x005bAPI_x005d_x002em = 1394,
		resqml2__ResqmlUom__TD_x005bAPI_x005d_x002f_x0028Pa_x002es_x0029 = 1395,
		resqml2__ResqmlUom__TEuc = 1396,
		resqml2__ResqmlUom__TeV = 1397,
		resqml2__ResqmlUom__TF = 1398,
		resqml2__ResqmlUom__Tg = 1399,
		resqml2__ResqmlUom__Tgauss = 1400,
		resqml2__ResqmlUom__TGy = 1401,
		resqml2__ResqmlUom__TH = 1402,
		resqml2__ResqmlUom__therm_x005bEC_x005d = 1403,
		resqml2__ResqmlUom__therm_x005bUK_x005d = 1404,
		resqml2__ResqmlUom__therm_x005bUS_x005d = 1405,
		resqml2__ResqmlUom__THz = 1406,
		resqml2__ResqmlUom__TJ = 1407,
		resqml2__ResqmlUom__TJ_x002fa = 1408,
		resqml2__ResqmlUom__Tm = 1409,
		resqml2__ResqmlUom__TN = 1410,
		resqml2__ResqmlUom__Tohm = 1411,
		resqml2__ResqmlUom__ton_x005bUK_x005d = 1412,
		resqml2__ResqmlUom__ton_x005bUK_x005d_x002fa = 1413,
		resqml2__ResqmlUom__ton_x005bUK_x005d_x002fd = 1414,
		resqml2__ResqmlUom__ton_x005bUK_x005d_x002fh = 1415,
		resqml2__ResqmlUom__ton_x005bUK_x005d_x002fmin = 1416,
		resqml2__ResqmlUom__ton_x005bUS_x005d = 1417,
		resqml2__ResqmlUom__ton_x005bUS_x005d_x002fa = 1418,
		resqml2__ResqmlUom__ton_x005bUS_x005d_x002fd = 1419,
		resqml2__ResqmlUom__ton_x005bUS_x005d_x002fft2 = 1420,
		resqml2__ResqmlUom__ton_x005bUS_x005d_x002fh = 1421,
		resqml2__ResqmlUom__ton_x005bUS_x005d_x002fmin = 1422,
		resqml2__ResqmlUom__tonf_x005bUK_x005d = 1423,
		resqml2__ResqmlUom__tonf_x005bUK_x005d_x002eft2 = 1424,
		resqml2__ResqmlUom__tonf_x005bUK_x005d_x002fft = 1425,
		resqml2__ResqmlUom__tonf_x005bUK_x005d_x002fft2 = 1426,
		resqml2__ResqmlUom__tonf_x005bUS_x005d = 1427,
		resqml2__ResqmlUom__tonf_x005bUS_x005d_x002eft = 1428,
		resqml2__ResqmlUom__tonf_x005bUS_x005d_x002eft2 = 1429,
		resqml2__ResqmlUom__tonf_x005bUS_x005d_x002emi = 1430,
		resqml2__ResqmlUom__tonf_x005bUS_x005d_x002emi_x002fbbl = 1431,
		resqml2__ResqmlUom__tonf_x005bUS_x005d_x002emi_x002fft = 1432,
		resqml2__ResqmlUom__tonf_x005bUS_x005d_x002fft = 1433,
		resqml2__ResqmlUom__tonf_x005bUS_x005d_x002fft2 = 1434,
		resqml2__ResqmlUom__tonf_x005bUS_x005d_x002fin2 = 1435,
		resqml2__ResqmlUom__tonRefrig = 1436,
		resqml2__ResqmlUom__torr = 1437,
		resqml2__ResqmlUom__TP = 1438,
		resqml2__ResqmlUom__TPa = 1439,
		resqml2__ResqmlUom__Trd = 1440,
		resqml2__ResqmlUom__TS = 1441,
		resqml2__ResqmlUom__TT = 1442,
		resqml2__ResqmlUom__TV = 1443,
		resqml2__ResqmlUom__TW = 1444,
		resqml2__ResqmlUom__TW_x002eh = 1445,
		resqml2__ResqmlUom__TWb = 1446,
		resqml2__ResqmlUom__uA = 1447,
		resqml2__ResqmlUom__uA_x002fcm2 = 1448,
		resqml2__ResqmlUom__uA_x002fin2 = 1449,
		resqml2__ResqmlUom__ubar = 1450,
		resqml2__ResqmlUom__uC = 1451,
		resqml2__ResqmlUom__ucal_x005bth_x005d = 1452,
		resqml2__ResqmlUom__ucal_x005bth_x005d_x002f_x0028s_x002ecm2_x0029 = 1453,
		resqml2__ResqmlUom__ucal_x005bth_x005d_x002fs = 1454,
		resqml2__ResqmlUom__uCi = 1455,
		resqml2__ResqmlUom__uEuc = 1456,
		resqml2__ResqmlUom__ueV = 1457,
		resqml2__ResqmlUom__uF = 1458,
		resqml2__ResqmlUom__uF_x002fm = 1459,
		resqml2__ResqmlUom__ug = 1460,
		resqml2__ResqmlUom__ug_x002fcm3 = 1461,
		resqml2__ResqmlUom__ug_x002fg = 1462,
		resqml2__ResqmlUom__ug_x002fmg = 1463,
		resqml2__ResqmlUom__ugauss = 1464,
		resqml2__ResqmlUom__uGy = 1465,
		resqml2__ResqmlUom__uH = 1466,
		resqml2__ResqmlUom__uH_x002fm = 1467,
		resqml2__ResqmlUom__uHz = 1468,
		resqml2__ResqmlUom__uJ = 1469,
		resqml2__ResqmlUom__um = 1470,
		resqml2__ResqmlUom__um_x002fs = 1471,
		resqml2__ResqmlUom__um2 = 1472,
		resqml2__ResqmlUom__um2_x002em = 1473,
		resqml2__ResqmlUom__umHg_x005b0degC_x005d = 1474,
		resqml2__ResqmlUom__umol = 1475,
		resqml2__ResqmlUom__uN = 1476,
		resqml2__ResqmlUom__uohm = 1477,
		resqml2__ResqmlUom__uohm_x002fft = 1478,
		resqml2__ResqmlUom__uohm_x002fm = 1479,
		resqml2__ResqmlUom__uP = 1480,
		resqml2__ResqmlUom__uPa = 1481,
		resqml2__ResqmlUom__upsi = 1482,
		resqml2__ResqmlUom__urad = 1483,
		resqml2__ResqmlUom__urd = 1484,
		resqml2__ResqmlUom__us = 1485,
		resqml2__ResqmlUom__uS = 1486,
		resqml2__ResqmlUom__us_x002fft = 1487,
		resqml2__ResqmlUom__us_x002fin = 1488,
		resqml2__ResqmlUom__us_x002fm = 1489,
		resqml2__ResqmlUom__uT = 1490,
		resqml2__ResqmlUom__uV = 1491,
		resqml2__ResqmlUom__uV_x002fft = 1492,
		resqml2__ResqmlUom__uV_x002fm = 1493,
		resqml2__ResqmlUom__uW = 1494,
		resqml2__ResqmlUom__uW_x002fm3 = 1495,
		resqml2__ResqmlUom__uWb = 1496,
		resqml2__ResqmlUom__V_x002fB = 1497,
		resqml2__ResqmlUom__V_x002fdB = 1498,
		resqml2__ResqmlUom__V_x002fm = 1499,
		resqml2__ResqmlUom__W_x002em2_x002eK_x002f_x0028J_x002eK_x0029 = 1500,
		resqml2__ResqmlUom__W_x002f_x0028m_x002eK_x0029 = 1501,
		resqml2__ResqmlUom__W_x002f_x0028m2_x002eK_x0029 = 1502,
		resqml2__ResqmlUom__W_x002f_x0028m2_x002esr_x0029 = 1503,
		resqml2__ResqmlUom__W_x002f_x0028m3_x002eK_x0029 = 1504,
		resqml2__ResqmlUom__W_x002fcm2 = 1505,
		resqml2__ResqmlUom__W_x002fK = 1506,
		resqml2__ResqmlUom__W_x002fkW = 1507,
		resqml2__ResqmlUom__W_x002fm2 = 1508,
		resqml2__ResqmlUom__W_x002fm3 = 1509,
		resqml2__ResqmlUom__W_x002fmm2 = 1510,
		resqml2__ResqmlUom__W_x002fsr = 1511,
		resqml2__ResqmlUom__W_x002fW = 1512,
		resqml2__ResqmlUom__Wb = 1513,
		resqml2__ResqmlUom__Wb_x002em = 1514,
		resqml2__ResqmlUom__Wb_x002fm = 1515,
		resqml2__ResqmlUom__Wb_x002fmm = 1516,
		resqml2__ResqmlUom__wk = 1517,
		resqml2__ResqmlUom__yd = 1518,
		resqml2__ResqmlUom__yd_x005bBnA_x005d = 1519,
		resqml2__ResqmlUom__yd_x005bBnB_x005d = 1520,
		resqml2__ResqmlUom__yd_x005bCla_x005d = 1521,
		resqml2__ResqmlUom__yd_x005bInd_x005d = 1522,
		resqml2__ResqmlUom__yd_x005bInd37_x005d = 1523,
		resqml2__ResqmlUom__yd_x005bInd62_x005d = 1524,
		resqml2__ResqmlUom__yd_x005bInd75_x005d = 1525,
		resqml2__ResqmlUom__yd_x005bSe_x005d = 1526,
		resqml2__ResqmlUom__yd_x005bSeT_x005d = 1527,
		resqml2__ResqmlUom__yd_x005bUS_x005d = 1528,
		resqml2__ResqmlUom__yd2 = 1529,
		resqml2__ResqmlUom__yd3 = 1530
	};
	enum resqml2__ResqmlPropertyKind {
		resqml2__ResqmlPropertyKind__absorbed_x0020dose = 0,
		resqml2__ResqmlPropertyKind__acceleration_x0020linear = 1,
		resqml2__ResqmlPropertyKind__activity_x0020_x0028of_x0020radioactivity_x0029 = 2,
		resqml2__ResqmlPropertyKind__amount_x0020of_x0020substance = 3,
		resqml2__ResqmlPropertyKind__amplitude = 4,
		resqml2__ResqmlPropertyKind__angle_x0020per_x0020length = 5,
		resqml2__ResqmlPropertyKind__angle_x0020per_x0020time = 6,
		resqml2__ResqmlPropertyKind__angle_x0020per_x0020volume = 7,
		resqml2__ResqmlPropertyKind__angular_x0020acceleration = 8,
		resqml2__ResqmlPropertyKind__area = 9,
		resqml2__ResqmlPropertyKind__area_x0020per_x0020area = 10,
		resqml2__ResqmlPropertyKind__area_x0020per_x0020volume = 11,
		resqml2__ResqmlPropertyKind__attenuation = 12,
		resqml2__ResqmlPropertyKind__attenuation_x0020per_x0020length = 13,
		resqml2__ResqmlPropertyKind__azimuth = 14,
		resqml2__ResqmlPropertyKind__bubble_x0020point_x0020pressure = 15,
		resqml2__ResqmlPropertyKind__bulk_x0020modulus = 16,
		resqml2__ResqmlPropertyKind__capacitance = 17,
		resqml2__ResqmlPropertyKind__categorical = 18,
		resqml2__ResqmlPropertyKind__cell_x0020length = 19,
		resqml2__ResqmlPropertyKind__charge_x0020density = 20,
		resqml2__ResqmlPropertyKind__chemical_x0020potential = 21,
		resqml2__ResqmlPropertyKind__code = 22,
		resqml2__ResqmlPropertyKind__compressibility = 23,
		resqml2__ResqmlPropertyKind__concentration_x0020of_x0020B = 24,
		resqml2__ResqmlPropertyKind__conductivity = 25,
		resqml2__ResqmlPropertyKind__continuous = 26,
		resqml2__ResqmlPropertyKind__cross_x0020section_x0020absorption = 27,
		resqml2__ResqmlPropertyKind__current_x0020density = 28,
		resqml2__ResqmlPropertyKind__Darcy_x0020flow_x0020coefficient = 29,
		resqml2__ResqmlPropertyKind__data_x0020transmission_x0020speed = 30,
		resqml2__ResqmlPropertyKind__delta_x0020temperature = 31,
		resqml2__ResqmlPropertyKind__density = 32,
		resqml2__ResqmlPropertyKind__depth = 33,
		resqml2__ResqmlPropertyKind__diffusion_x0020coefficient = 34,
		resqml2__ResqmlPropertyKind__digital_x0020storage = 35,
		resqml2__ResqmlPropertyKind__dimensionless = 36,
		resqml2__ResqmlPropertyKind__dip = 37,
		resqml2__ResqmlPropertyKind__discrete = 38,
		resqml2__ResqmlPropertyKind__dose_x0020equivalent = 39,
		resqml2__ResqmlPropertyKind__dose_x0020equivalent_x0020rate = 40,
		resqml2__ResqmlPropertyKind__dynamic_x0020viscosity = 41,
		resqml2__ResqmlPropertyKind__electric_x0020charge = 42,
		resqml2__ResqmlPropertyKind__electric_x0020conductance = 43,
		resqml2__ResqmlPropertyKind__electric_x0020current = 44,
		resqml2__ResqmlPropertyKind__electric_x0020dipole_x0020moment = 45,
		resqml2__ResqmlPropertyKind__electric_x0020field_x0020strength = 46,
		resqml2__ResqmlPropertyKind__electric_x0020polarization = 47,
		resqml2__ResqmlPropertyKind__electric_x0020potential = 48,
		resqml2__ResqmlPropertyKind__electrical_x0020resistivity = 49,
		resqml2__ResqmlPropertyKind__electrochemical_x0020equivalent = 50,
		resqml2__ResqmlPropertyKind__electromagnetic_x0020moment = 51,
		resqml2__ResqmlPropertyKind__energy_x0020length_x0020per_x0020area = 52,
		resqml2__ResqmlPropertyKind__energy_x0020length_x0020per_x0020time_x0020area_x0020temperature = 53,
		resqml2__ResqmlPropertyKind__energy_x0020per_x0020area = 54,
		resqml2__ResqmlPropertyKind__energy_x0020per_x0020length = 55,
		resqml2__ResqmlPropertyKind__equivalent_x0020per_x0020mass = 56,
		resqml2__ResqmlPropertyKind__equivalent_x0020per_x0020volume = 57,
		resqml2__ResqmlPropertyKind__exposure_x0020_x0028radioactivity_x0029 = 58,
		resqml2__ResqmlPropertyKind__fluid_x0020volume = 59,
		resqml2__ResqmlPropertyKind__force = 60,
		resqml2__ResqmlPropertyKind__force_x0020area = 61,
		resqml2__ResqmlPropertyKind__force_x0020length_x0020per_x0020length = 62,
		resqml2__ResqmlPropertyKind__force_x0020per_x0020force = 63,
		resqml2__ResqmlPropertyKind__force_x0020per_x0020length = 64,
		resqml2__ResqmlPropertyKind__force_x0020per_x0020volume = 'A',
		resqml2__ResqmlPropertyKind__formation_x0020volume_x0020factor = 'B',
		resqml2__ResqmlPropertyKind__frequency = 'C',
		resqml2__ResqmlPropertyKind__frequency_x0020interval = 'D',
		resqml2__ResqmlPropertyKind__gamma_x0020ray_x0020API_x0020unit = 'E',
		resqml2__ResqmlPropertyKind__heat_x0020capacity = 'F',
		resqml2__ResqmlPropertyKind__heat_x0020flow_x0020rate = 'G',
		resqml2__ResqmlPropertyKind__heat_x0020transfer_x0020coefficient = 'H',
		resqml2__ResqmlPropertyKind__illuminance = 'I',
		resqml2__ResqmlPropertyKind__index = 'J',
		resqml2__ResqmlPropertyKind__irradiance = 'K',
		resqml2__ResqmlPropertyKind__isothermal_x0020compressibility = 'L',
		resqml2__ResqmlPropertyKind__kinematic_x0020viscosity = 'M',
		resqml2__ResqmlPropertyKind__Lambda_x0020Rho = 'N',
		resqml2__ResqmlPropertyKind__Lame_x0020constant = 'O',
		resqml2__ResqmlPropertyKind__length = 'P',
		resqml2__ResqmlPropertyKind__length_x0020per_x0020length = 'Q',
		resqml2__ResqmlPropertyKind__length_x0020per_x0020temperature = 'R',
		resqml2__ResqmlPropertyKind__length_x0020per_x0020volume = 'S',
		resqml2__ResqmlPropertyKind__level_x0020of_x0020power_x0020intensity = 'T',
		resqml2__ResqmlPropertyKind__light_x0020exposure = 'U',
		resqml2__ResqmlPropertyKind__linear_x0020thermal_x0020expansion = 'V',
		resqml2__ResqmlPropertyKind__luminance = 'W',
		resqml2__ResqmlPropertyKind__luminous_x0020efficacy = 'X',
		resqml2__ResqmlPropertyKind__luminous_x0020flux = 'Y',
		resqml2__ResqmlPropertyKind__luminous_x0020intensity = 'Z',
		resqml2__ResqmlPropertyKind__magnetic_x0020dipole_x0020moment = 91,
		resqml2__ResqmlPropertyKind__magnetic_x0020field_x0020strength = 92,
		resqml2__ResqmlPropertyKind__magnetic_x0020flux = 93,
		resqml2__ResqmlPropertyKind__magnetic_x0020induction = 94,
		resqml2__ResqmlPropertyKind__magnetic_x0020permeability = 95,
		resqml2__ResqmlPropertyKind__magnetic_x0020vector_x0020potential = 96,
		resqml2__ResqmlPropertyKind__mass = 'a',
		resqml2__ResqmlPropertyKind__mass_x0020attenuation_x0020coefficient = 'b',
		resqml2__ResqmlPropertyKind__mass_x0020concentration = 'c',
		resqml2__ResqmlPropertyKind__mass_x0020flow_x0020rate = 'd',
		resqml2__ResqmlPropertyKind__mass_x0020length = 'e',
		resqml2__ResqmlPropertyKind__mass_x0020per_x0020energy = 'f',
		resqml2__ResqmlPropertyKind__mass_x0020per_x0020length = 'g',
		resqml2__ResqmlPropertyKind__mass_x0020per_x0020time_x0020per_x0020area = 'h',
		resqml2__ResqmlPropertyKind__mass_x0020per_x0020time_x0020per_x0020length = 'i',
		resqml2__ResqmlPropertyKind__mass_x0020per_x0020volume_x0020per_x0020length = 'j',
		resqml2__ResqmlPropertyKind__mobility = 'k',
		resqml2__ResqmlPropertyKind__modulus_x0020of_x0020compression = 'l',
		resqml2__ResqmlPropertyKind__molar_x0020concentration = 'm',
		resqml2__ResqmlPropertyKind__molar_x0020heat_x0020capacity = 'n',
		resqml2__ResqmlPropertyKind__molar_x0020volume = 'o',
		resqml2__ResqmlPropertyKind__mole_x0020per_x0020area = 'p',
		resqml2__ResqmlPropertyKind__mole_x0020per_x0020time = 'q',
		resqml2__ResqmlPropertyKind__mole_x0020per_x0020time_x0020per_x0020area = 'r',
		resqml2__ResqmlPropertyKind__moment_x0020of_x0020force = 's',
		resqml2__ResqmlPropertyKind__moment_x0020of_x0020inertia = 't',
		resqml2__ResqmlPropertyKind__moment_x0020of_x0020section = 'u',
		resqml2__ResqmlPropertyKind__momentum = 'v',
		resqml2__ResqmlPropertyKind__Mu_x0020Rho = 'w',
		resqml2__ResqmlPropertyKind__net_x0020to_x0020gross_x0020ratio = 'x',
		resqml2__ResqmlPropertyKind__neutron_x0020API_x0020unit = 'y',
		resqml2__ResqmlPropertyKind__nonDarcy_x0020flow_x0020coefficient = 'z',
		resqml2__ResqmlPropertyKind__operations_x0020per_x0020time = 123,
		resqml2__ResqmlPropertyKind__parachor = 124,
		resqml2__ResqmlPropertyKind__per_x0020area = 125,
		resqml2__ResqmlPropertyKind__per_x0020electric_x0020potential = 126,
		resqml2__ResqmlPropertyKind__per_x0020force = 127,
		resqml2__ResqmlPropertyKind__per_x0020length = 128,
		resqml2__ResqmlPropertyKind__per_x0020mass = 129,
		resqml2__ResqmlPropertyKind__per_x0020volume = 130,
		resqml2__ResqmlPropertyKind__permeability_x0020length = 131,
		resqml2__ResqmlPropertyKind__permeability_x0020rock = 132,
		resqml2__ResqmlPropertyKind__permeability_x0020thickness = 133,
		resqml2__ResqmlPropertyKind__permeance = 134,
		resqml2__ResqmlPropertyKind__permittivity = 135,
		resqml2__ResqmlPropertyKind__pH = 136,
		resqml2__ResqmlPropertyKind__plane_x0020angle = 137,
		resqml2__ResqmlPropertyKind__Poisson_x0020ratio = 138,
		resqml2__ResqmlPropertyKind__pore_x0020volume = 139,
		resqml2__ResqmlPropertyKind__porosity = 140,
		resqml2__ResqmlPropertyKind__potential_x0020difference_x0020per_x0020power_x0020drop = 141,
		resqml2__ResqmlPropertyKind__power = 142,
		resqml2__ResqmlPropertyKind__power_x0020per_x0020volume = 143,
		resqml2__ResqmlPropertyKind__pressure = 144,
		resqml2__ResqmlPropertyKind__pressure_x0020per_x0020time = 145,
		resqml2__ResqmlPropertyKind__pressure_x0020squared = 146,
		resqml2__ResqmlPropertyKind__pressure_x0020squared_x0020per_x0020force_x0020time_x0020per_x0020area = 147,
		resqml2__ResqmlPropertyKind__pressure_x0020time_x0020per_x0020volume = 148,
		resqml2__ResqmlPropertyKind__productivity_x0020index = 149,
		resqml2__ResqmlPropertyKind__property_x0020multiplier = 150,
		resqml2__ResqmlPropertyKind__quantity = 151,
		resqml2__ResqmlPropertyKind__quantity_x0020of_x0020light = 152,
		resqml2__ResqmlPropertyKind__radiance = 153,
		resqml2__ResqmlPropertyKind__radiant_x0020intensity = 154,
		resqml2__ResqmlPropertyKind__relative_x0020permeability = 155,
		resqml2__ResqmlPropertyKind__relative_x0020power = 156,
		resqml2__ResqmlPropertyKind__relative_x0020time = 157,
		resqml2__ResqmlPropertyKind__reluctance = 158,
		resqml2__ResqmlPropertyKind__resistance = 159,
		resqml2__ResqmlPropertyKind__resistivity_x0020per_x0020length = 160,
		resqml2__ResqmlPropertyKind__RESQML_x0020root_x0020property = 161,
		resqml2__ResqmlPropertyKind__Rock_x0020Impedance = 162,
		resqml2__ResqmlPropertyKind__rock_x0020permeability = 163,
		resqml2__ResqmlPropertyKind__rock_x0020volume = 164,
		resqml2__ResqmlPropertyKind__saturation = 165,
		resqml2__ResqmlPropertyKind__second_x0020moment_x0020of_x0020area = 166,
		resqml2__ResqmlPropertyKind__shear_x0020modulus = 167,
		resqml2__ResqmlPropertyKind__solid_x0020angle = 168,
		resqml2__ResqmlPropertyKind__solution_x0020gas_oil_x0020ratio = 169,
		resqml2__ResqmlPropertyKind__specific_x0020activity_x0020_x0028of_x0020radioactivity_x0029 = 170,
		resqml2__ResqmlPropertyKind__specific_x0020energy = 171,
		resqml2__ResqmlPropertyKind__specific_x0020heat_x0020capacity = 172,
		resqml2__ResqmlPropertyKind__specific_x0020productivity_x0020index = 173,
		resqml2__ResqmlPropertyKind__specific_x0020volume = 174,
		resqml2__ResqmlPropertyKind__surface_x0020density = 175,
		resqml2__ResqmlPropertyKind__temperature_x0020per_x0020length = 176,
		resqml2__ResqmlPropertyKind__temperature_x0020per_x0020time = 177,
		resqml2__ResqmlPropertyKind__thermal_x0020conductance = 178,
		resqml2__ResqmlPropertyKind__thermal_x0020conductivity = 179,
		resqml2__ResqmlPropertyKind__thermal_x0020diffusivity = 180,
		resqml2__ResqmlPropertyKind__thermal_x0020insulance = 181,
		resqml2__ResqmlPropertyKind__thermal_x0020resistance = 182,
		resqml2__ResqmlPropertyKind__thermodynamic_x0020temperature = 183,
		resqml2__ResqmlPropertyKind__thickness = 184,
		resqml2__ResqmlPropertyKind__time = 185,
		resqml2__ResqmlPropertyKind__time_x0020per_x0020length = 186,
		resqml2__ResqmlPropertyKind__time_x0020per_x0020volume = 187,
		resqml2__ResqmlPropertyKind__transmissibility = 188,
		resqml2__ResqmlPropertyKind__unit_x0020productivity_x0020index = 189,
		resqml2__ResqmlPropertyKind__unitless = 190,
		resqml2__ResqmlPropertyKind__vapor_x0020oil_gas_x0020ratio = 191,
		resqml2__ResqmlPropertyKind__velocity = 192,
		resqml2__ResqmlPropertyKind__volume = 193,
		resqml2__ResqmlPropertyKind__volume_x0020flow_x0020rate = 194,
		resqml2__ResqmlPropertyKind__volume_x0020length_x0020per_x0020time = 195,
		resqml2__ResqmlPropertyKind__volume_x0020per_x0020area = 196,
		resqml2__ResqmlPropertyKind__volume_x0020per_x0020length = 197,
		resqml2__ResqmlPropertyKind__volume_x0020per_x0020time_x0020per_x0020area = 198,
		resqml2__ResqmlPropertyKind__volume_x0020per_x0020time_x0020per_x0020length = 199,
		resqml2__ResqmlPropertyKind__volume_x0020per_x0020time_x0020per_x0020time = 200,
		resqml2__ResqmlPropertyKind__volume_x0020per_x0020time_x0020per_x0020volume = 201,
		resqml2__ResqmlPropertyKind__volume_x0020per_x0020volume = 202,
		resqml2__ResqmlPropertyKind__volumetric_x0020heat_x0020transfer_x0020coefficient = 203,
		resqml2__ResqmlPropertyKind__volumetric_x0020thermal_x0020expansion = 204,
		resqml2__ResqmlPropertyKind__work = 205,
		resqml2__ResqmlPropertyKind__Young_x0020modulus = 206
	};
	enum resqml2__FluidContact {
		resqml2__FluidContact__free_x0020water_x0020contact = 0,
		resqml2__FluidContact__gas_x0020oil_x0020contact = 1,
		resqml2__FluidContact__gas_x0020water_x0020contact = 2,
		resqml2__FluidContact__seal = 3,
		resqml2__FluidContact__water_x0020oil_x0020contact = 4
	};
	enum resqml2__SurfaceRole {
		resqml2__SurfaceRole__map = 0,
		resqml2__SurfaceRole__pick = 1
	};
	enum resqml2__Facet {
		resqml2__Facet__conditions = 0,
		resqml2__Facet__direction = 1,
		resqml2__Facet__netgross = 2,
		resqml2__Facet__qualifier = 3,
		resqml2__Facet__statistics = 4,
		resqml2__Facet__what = 5
	};
	enum resqml2__Domain {
		resqml2__Domain__depth = 0,
		resqml2__Domain__time = 1,
		resqml2__Domain__mixed = 2
	};
}

namespace WITSML1_4_1_1_NS {
	class Wellbore;
	class Trajectory;
	class Log;
	class FormationMarker;
}

#ifdef SWIGPYTHON
namespace RESQML2_0_1_NS
{
	%typemap(out) WellboreFrameRepresentation* {
		// Check potential downcasting
		swig_type_info * const outtype = SWIG_TypeQuery(("resqml2_0_1::" + result->getXmlTag() + " *").c_str());
		resultobj = SWIG_NewPointerObj(SWIG_as_voidptr(result), outtype, 0);
	}
}
#endif
#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace RESQML2_0_1_NS::Activity;
	%nspace RESQML2_0_1_NS::ActivityTemplate;
	%nspace RESQML2_0_1_NS::LocalDepth3dCrs;
	%nspace RESQML2_0_1_NS::LocalTime3dCrs ;
	%nspace RESQML2_0_1_NS::MdDatum;
	%nspace RESQML2_0_1_NS::AbstractGeologicFeature;
	%nspace RESQML2_0_1_NS::GeologicUnitFeature;
	%nspace RESQML2_0_1_NS::BoundaryFeature;
	%nspace RESQML2_0_1_NS::GeneticBoundaryFeature;
	%nspace RESQML2_0_1_NS::Horizon;
	%nspace RESQML2_0_1_NS::GeobodyBoundaryInterpretation;
	%nspace RESQML2_0_1_NS::GeobodyFeature;
	%nspace RESQML2_0_1_NS:: GeobodyInterpretation;
	%nspace RESQML2_0_1_NS::TectonicBoundaryFeature;
	%nspace RESQML2_0_1_NS::AbstractTechnicalFeature;
	%nspace RESQML2_0_1_NS::SeismicLineSetFeature;
	%nspace RESQML2_0_1_NS::SeismicLineFeature;
	%nspace RESQML2_0_1_NS::SeismicLatticeFeature;
	%nspace RESQML2_0_1_NS::WellboreFeature;
	%nspace RESQML2_0_1_NS::OrganizationFeature;
	%nspace RESQML2_0_1_NS::GenericFeatureInterpretation;
	%nspace RESQML2_0_1_NS::BoundaryFeatureInterpretation;
	%nspace RESQML2_0_1_NS::FaultInterpretation;
	%nspace RESQML2_0_1_NS::HorizonInterpretation;
	%nspace RESQML2_0_1_NS::WellboreInterpretation;
	%nspace RESQML2_0_1_NS::AbstractOrganizationInterpretation;
	%nspace RESQML2_0_1_NS::StructuralOrganizationInterpretation;
	%nspace RESQML2_0_1_NS::StratigraphicUnitFeature;
	%nspace RESQML2_0_1_NS::StratigraphicUnitInterpretation;
	%nspace RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation;
	%nspace RESQML2_0_1_NS::StratigraphicColumnRankInterpretation;
	%nspace RESQML2_0_1_NS::StratigraphicOccurrenceInterpretation;
	%nspace RESQML2_0_1_NS::StratigraphicColumn;
	%nspace RESQML2_0_1_NS::EarthModelInterpretation;
	%nspace RESQML2_0_1_NS::SubRepresentation;
	%nspace RESQML2_0_1_NS::PolylineSetRepresentation;
	%nspace RESQML2_0_1_NS::PointSetRepresentation;
	%nspace RESQML2_0_1_NS::PolylineRepresentation;
	%nspace RESQML2_0_1_NS::AbstractSurfaceRepresentation;
	%nspace RESQML2_0_1_NS::Grid2dRepresentation;
	%nspace RESQML2_0_1_NS::Grid2dSetRepresentation;
	%nspace RESQML2_0_1_NS::TriangulatedSetRepresentation;
	%nspace RESQML2_0_1_NS::WellboreTrajectoryRepresentation;
	%nspace RESQML2_0_1_NS::DeviationSurveyRepresentation;
	%nspace RESQML2_0_1_NS::WellboreFrameRepresentation;
	%nspace RESQML2_0_1_NS::WellboreMarker;
	%nspace RESQML2_0_1_NS::WellboreMarkerFrameRepresentation;
	%nspace RESQML2_0_1_NS::RepresentationSetRepresentation;
	%nspace RESQML2_0_1_NS::NonSealedSurfaceFrameworkRepresentation;
	%nspace RESQML2_0_1_NS::SealedSurfaceFrameworkRepresentation;
	%nspace RESQML2_0_1_NS::UnstructuredGridRepresentation;
	%nspace RESQML2_0_1_NS::GridConnectionSetRepresentation;
	%nspace RESQML2_0_1_NS::TimeSeries;
	%nspace RESQML2_0_1_NS::PropertyKind;
	%nspace RESQML2_0_1_NS::StringTableLookup;
	%nspace RESQML2_0_1_NS::CommentProperty;
	%nspace RESQML2_0_1_NS::ContinuousProperty;
	%nspace RESQML2_0_1_NS::ContinuousPropertySeries;
	%nspace RESQML2_0_1_NS::DiscreteProperty;
	%nspace RESQML2_0_1_NS::DiscretePropertySeries;
	%nspace RESQML2_0_1_NS::CategoricalProperty;
	%nspace RESQML2_0_1_NS::CategoricalPropertySeries;
	%nspace RESQML2_0_1_NS::PropertyKindMapper;
	%nspace RESQML2_0_1_NS::FrontierFeature;
	%nspace RESQML2_0_1_NS::PlaneSetRepresentation;
	%nspace RESQML2_0_1_NS::FluidBoundaryFeature;
	%nspace RESQML2_0_1_NS::AbstractIjkGridRepresentation;
	%nspace RESQML2_0_1_NS::IjkGridExplicitRepresentation;
	%nspace RESQML2_0_1_NS::IjkGridLatticeRepresentation;
	%nspace RESQML2_0_1_NS::IjkGridParametricRepresentation;
	%nspace RESQML2_0_1_NS::IjkGridNoGeometryRepresentation;
	%nspace RESQML2_0_1_NS::HdfProxy;
#endif

namespace RESQML2_0_1_NS
{
	%nodefaultctor; // Disable creation of default constructors
	
	//************************************
	//************ HDF *******************
	//************************************
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_HdfProxy) HdfProxy;
#endif
	class HdfProxy : public COMMON_NS::HdfProxy
	{
	public:
	};
	
	//************************************
	//************ Activity **************
	//************************************

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_ActivityTemplate) ActivityTemplate;
#endif
	class ActivityTemplate : public RESQML2_NS::ActivityTemplate
	{
	public:
		void pushBackParameter(const std::string title,
			const gsoap_resqml2_0_1::resqml2__ParameterKind & kind,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const int & maxOccurs);
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_Activity) Activity;
#endif
	class Activity : public RESQML2_NS::Activity
	{
	public:
		void pushBackParameter(const std::string title,
			const double & value, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom = gsoap_resqml2_0_1::resqml2__ResqmlUom__Euc);
		
		gsoap_resqml2_0_1::resqml2__ResqmlUom getFloatingPointQuantityParameterUom(const unsigned int & index) const;
	};

	//************************************
	//************ CRS *******************
	//************************************
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_LocalDepth3dCrs) LocalDepth3dCrs;
#endif
	class LocalDepth3dCrs : public RESQML2_NS::AbstractLocal3dCrs
	{
	public:
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_LocalTime3dCrs) LocalTime3dCrs;
#endif
	class LocalTime3dCrs : public RESQML2_NS::AbstractLocal3dCrs
	{
	public:
		gsoap_resqml2_0_1::eml20__TimeUom getUnit() const;
		std::string getUnitAsString() const;
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_MdDatum) MdDatum;
#endif
	class MdDatum : public RESQML2_NS::MdDatum
	{
	public:
		gsoap_resqml2_0_1::resqml2__MdReference getOriginKind() const;
	};
	
	//************************************
	//************ FEATURE ***************
	//************************************

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_AbstractGeologicFeature) AbstractGeologicFeature;
#endif
	class AbstractGeologicFeature : public RESQML2_NS::AbstractFeature
	{
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_BoundaryFeature) BoundaryFeature;
#endif
	class BoundaryFeature : public AbstractGeologicFeature
	{
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_GeologicUnitFeature) GeologicUnitFeature;
#endif
	class GeologicUnitFeature : public AbstractGeologicFeature
	{
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_GeneticBoundaryFeature) GeneticBoundaryFeature;
#endif
	class GeneticBoundaryFeature : public BoundaryFeature
	{
	public:
		bool isAnHorizon() const;
		void setAge(const ULONG64 & age);
		bool hasAnAge() const;
		ULONG64 getAge() const;
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_Horizon) Horizon;
#endif
	class Horizon : public GeneticBoundaryFeature
	{
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_TectonicBoundaryFeature) TectonicBoundaryFeature;
#endif
	class TectonicBoundaryFeature : public BoundaryFeature
	{
	public:
		bool isAFracture() const;
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_AbstractTechnicalFeature) AbstractTechnicalFeature;
#endif
	class AbstractTechnicalFeature : public RESQML2_NS::AbstractFeature
	{
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_SeismicLineSetFeature) SeismicLineSetFeature;
#endif
	class SeismicLineSetFeature : public AbstractTechnicalFeature
	{
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_SeismicLineFeature) SeismicLineFeature;
#endif
	class SeismicLineFeature : public AbstractTechnicalFeature
	{
	public:
		int getTraceIndexIncrement() const;
		int getFirstTraceIndex() const;
		unsigned int getTraceCount() const;
		
		SeismicLineSetFeature* getSeismicLineSet();
		void setSeismicLineSet(class SeismicLineSetFeature * seisLineSet);
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_SeismicLatticeFeature) SeismicLatticeFeature;
#endif
	class SeismicLatticeFeature : public AbstractTechnicalFeature
	{
	public:
		int getCrosslineIncrement() const;
		int getInlineIncrement() const;
		int getOriginCrossline() const;
		int getOriginInline() const;
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_WellboreFeature) WellboreFeature;
#endif
	class WellboreFeature : public AbstractTechnicalFeature
	{
	public:
		WITSML1_4_1_1_NS::Wellbore* getWitsmlWellbore();
		void setWitsmlWellbore(WITSML1_4_1_1_NS::Wellbore * wellbore);
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_OrganizationFeature) OrganizationFeature;
#endif
	class OrganizationFeature : public AbstractGeologicFeature
	{
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_FrontierFeature) FrontierFeature;
#endif
	class FrontierFeature : public AbstractTechnicalFeature
	{
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_StratigraphicUnitFeature) StratigraphicUnitFeature;
#endif
	class StratigraphicUnitFeature : public GeologicUnitFeature
	{
	public:
	};
	
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_GeobodyFeature) GeobodyFeature;
#endif
	class GeobodyFeature : public GeologicUnitFeature
	{
	public:
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_FluidBoundaryFeature) FluidBoundaryFeature;
#endif
	class FluidBoundaryFeature : public BoundaryFeature
	{
	public:
	};

	//************************************
	//************ INTERPRETATION ********
	//************************************
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_GenericFeatureInterpretation) GenericFeatureInterpretation;
#endif
	class GenericFeatureInterpretation : public RESQML2_NS::AbstractFeatureInterpretation
	{
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_BoundaryFeatureInterpretation) BoundaryFeatureInterpretation;
#endif
	class BoundaryFeatureInterpretation : public RESQML2_NS::AbstractFeatureInterpretation
	{
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_FaultInterpretation) FaultInterpretation;
#endif
	class FaultInterpretation : public BoundaryFeatureInterpretation
	{
	public: 
		void pushBackThrowInterpretation(const gsoap_resqml2_0_1::resqml2__ThrowKind & throwKind);
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_HorizonInterpretation) HorizonInterpretation;
#endif
	class HorizonInterpretation : public BoundaryFeatureInterpretation
	{
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_GeobodyBoundaryInterpretation) GeobodyBoundaryInterpretation;
#endif
	class GeobodyBoundaryInterpretation : public BoundaryFeatureInterpretation
	{
	};
	
	class WellboreTrajectoryRepresentation;
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_WellboreInterpretation) WellboreInterpretation;
#endif
	class WellboreInterpretation : public RESQML2_NS::AbstractFeatureInterpretation
	{
	public:
		bool isDrilled() const;
		std::vector<WellboreTrajectoryRepresentation*> getWellboreTrajectoryRepresentationSet() const;
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_StratigraphicUnitInterpretation) StratigraphicUnitInterpretation;
#endif
	class StratigraphicUnitInterpretation : public RESQML2_NS::AbstractFeatureInterpretation
	{
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_GeobodyInterpretation) GeobodyInterpretation;
#endif
	class GeobodyInterpretation : public RESQML2_NS::AbstractFeatureInterpretation
	{
	public :
		void set3dShape(gsoap_resqml2_0_1::resqml2__Geobody3dShape geobody3dShape);
		bool has3dShape() const;
		gsoap_resqml2_0_1::resqml2__Geobody3dShape get3dShape() const;
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_AbstractOrganizationInterpretation) AbstractOrganizationInterpretation;
#endif
	class AbstractOrganizationInterpretation : public RESQML2_NS::AbstractFeatureInterpretation
	{
	public:
		void pushBackBinaryContact(const gsoap_resqml2_0_1::resqml2__ContactRelationship & kind, RESQML2_NS::AbstractFeatureInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactVerb & verb, RESQML2_NS::AbstractFeatureInterpretation* directObject);
		void pushBackBinaryContact(const gsoap_resqml2_0_1::resqml2__ContactRelationship & kind, RESQML2_NS::AbstractFeatureInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactVerb & verb, RESQML2_NS::AbstractFeatureInterpretation* directObject,
				const gsoap_resqml2_0_1::resqml2__ContactSide & directObjectQualifier);
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_StructuralOrganizationInterpretation) StructuralOrganizationInterpretation;
#endif
	class StructuralOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	public:
		void pushBackFaultInterpretation(FaultInterpretation * faultInterpretation);
		void pushBackHorizonInterpretation(HorizonInterpretation * horizonInterpretation, const int & stratigraphicRank);
		void pushBackTopFrontierInterpretation(RESQML2_NS::AbstractFeatureInterpretation * topFrontierInterpretation);
        void pushBackBottomFrontierInterpretation(RESQML2_NS::AbstractFeatureInterpretation * bottomFrontierInterpretation);
        void pushBackSideFrontierInterpretation(RESQML2_NS::AbstractFeatureInterpretation * sideFrontierInterpretation);
		
		unsigned int getFaultInterpretationCount() const;
		FaultInterpretation* getFaultInterpretation(const unsigned int & index);
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_AbstractStratigraphicOrganizationInterpretation) AbstractStratigraphicOrganizationInterpretation;
#endif
	class AbstractStratigraphicOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	public:
		unsigned int getGridRepresentationCount() const;
		RESQML2_NS::AbstractGridRepresentation* getGridRepresentation(const unsigned int & index) const;
		bool isAssociatedToGridRepresentation(RESQML2_NS::AbstractGridRepresentation* gridRep) const;
	};
	
	class StratigraphicOccurrenceInterpretation;	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_StratigraphicColumnRankInterpretation) StratigraphicColumnRankInterpretation;
#endif
	class StratigraphicColumnRankInterpretation : public AbstractStratigraphicOrganizationInterpretation
	{
	public:
		void pushBackStratiUnitInterpretation(StratigraphicUnitInterpretation * stratiUnitInterpretation);
		void pushBackStratigraphicBinaryContact(StratigraphicUnitInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactMode & subjectContactMode,
			StratigraphicUnitInterpretation* directObject, const gsoap_resqml2_0_1::resqml2__ContactMode & directObjectMode,
			class HorizonInterpretation * partOf = NULL);
			
		unsigned int getContactCount() const;
		gsoap_resqml2_0_1::resqml2__ContactMode getSubjectContactModeOfContact(const unsigned int & contactIndex) const;
		gsoap_resqml2_0_1::resqml2__ContactMode getDirectObjectContactModeOfContact(const unsigned int & contactIndex) const;
		HorizonInterpretation* getHorizonInterpretationOfContact(const unsigned int & contactIndex) const;
		bool isAChronoStratiRank() const;
		StratigraphicUnitInterpretation* getSubjectOfContact(const unsigned int & contactIndex) const;
		StratigraphicUnitInterpretation* getDirectObjectOfContact(const unsigned int & contactIndex) const;
		const std::vector<StratigraphicUnitInterpretation*>& getStratigraphicUnitInterpretationSet() const;
        const std::vector<HorizonInterpretation*>& getHorizonInterpretationSet() const;
		const std::vector<StratigraphicOccurrenceInterpretation*>& getStratigraphicOccurrenceInterpretationSet() const;
		const std::vector<StratigraphicColumn*> & getStratigraphicColumnSet() const;
	};
	
	class WellboreMarkerFrameRepresentation;	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_StratigraphicOccurrenceInterpretation) StratigraphicOccurrenceInterpretation;
#endif
	class StratigraphicOccurrenceInterpretation : public AbstractStratigraphicOrganizationInterpretation
	{
	public:
		void setStratigraphicColumnRankInterpretation(StratigraphicColumnRankInterpretation * stratiColumnRankInterp);
		StratigraphicColumnRankInterpretation * getStratigraphicColumnRankInterpretation() const;
		std::string getStratigraphicColumnRankInterpretationUuid() const;
		
		std::vector<class WellboreMarkerFrameRepresentation*> getWellboreMarkerFrameRepresentationSet() const;
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_StratigraphicColumn) StratigraphicColumn;
#endif
	class StratigraphicColumn : public COMMON_NS::AbstractObject
	{
	public:
		void pushBackStratiColumnRank(StratigraphicColumnRankInterpretation * stratiColumnRank);
		std::vector<class StratigraphicColumnRankInterpretation*> getStratigraphicColumnRankInterpretationSet() const;
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_EarthModelInterpretation) EarthModelInterpretation;
#endif
	class EarthModelInterpretation : public RESQML2_NS::AbstractFeatureInterpretation
	{
	public:
		void setStructuralOrganizationInterpretation(StructuralOrganizationInterpretation * structOrganization);
		void setStratiColumn(StratigraphicColumn * stratiColumn);
	};

	//************************************
	//************ REPRESENTATION ********
	//************************************

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_SubRepresentation) SubRepresentation;
#endif	
	class SubRepresentation : public RESQML2_NS::SubRepresentation
	{
	public:
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_PolylineSetRepresentation) PolylineSetRepresentation;
#endif
	class PolylineSetRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:
		unsigned int getPolylineCountOfPatch(const unsigned int & patchIndex) const;
		unsigned int getPolylineCountOfAllPatches() const;
		void getNodeCountPerPolylineInPatch(const unsigned int & patchIndex, unsigned int * nodeCountPerPolyline) const;
		void getNodeCountPerPolylineOfAllPatches(unsigned int * nodeCountPerPolyline) const;
		void pushBackGeometryPatch(
				unsigned int * NodeCountPerPolyline, double * nodes,
				const unsigned int & polylineCount, const bool & allPolylinesClosedFlag,
				COMMON_NS::AbstractHdfProxy * proxy);
		void pushBackGeometryPatch(
				unsigned int * NodeCountPerPolyline, double * nodes,
				const unsigned int & polylineCount, bool * polylineClosedFlags,
				COMMON_NS::AbstractHdfProxy * proxy);
				
		bool areAllPolylinesClosedOfPatch(const unsigned int & patchIndex) const;
		bool areAllPolylinesClosedOfAllPatches() const;
		bool areAllPolylinesNonClosedOfPatch(const unsigned int & patchIndex) const;
		bool areAllPolylinesNonClosedOfAllPatches() const;
		void getClosedFlagPerPolylineOfPatch(const unsigned int & patchIndex, bool * closedFlagPerPolyline) const;
		void getClosedFlagPerPolylineOfAllPatches(bool * closedFlagPerPolyline) const;
		bool hasALineRole() const;
		gsoap_resqml2_0_1::resqml2__LineRole getLineRole() const;
		void setLineRole(const gsoap_resqml2_0_1::resqml2__LineRole & lineRole);
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_PointSetRepresentation) PointSetRepresentation;
#endif
	class PointSetRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:
		void pushBackGeometryPatch(
			const unsigned int & xyzPointCount, double * xyzPoints,
			COMMON_NS::AbstractHdfProxy * proxy);
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_PlaneSetRepresentation) PlaneSetRepresentation;
#endif
	class PlaneSetRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:
		void pushBackHorizontalPlaneGeometryPatch(const double & zCoordinate);
		void pushBackTiltedPlaneGeometryPatch(const double & x1, const double & y1, const double & z1,
			const double & x2, const double & y2, const double & z2,
			const double & x3, const double & y3, const double & z3);
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_PolylineRepresentation) PolylineRepresentation;
#endif
	class PolylineRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:
		void setGeometry(double * points, const unsigned int & pointCount, COMMON_NS::AbstractHdfProxy * proxy);
		bool isClosed() const;
		bool hasALineRole() const;
		gsoap_resqml2_0_1::resqml2__LineRole getLineRole() const;
		void setLineRole(const gsoap_resqml2_0_1::resqml2__LineRole & lineRole);
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_AbstractSurfaceRepresentation) AbstractSurfaceRepresentation;
#endif
	class AbstractSurfaceRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:
		void setSurfaceRole(const gsoap_resqml2_0_1::resqml2__SurfaceRole & surfaceRole);
		const gsoap_resqml2_0_1::resqml2__SurfaceRole & getSurfaceRole() const;
		void pushBackOuterRing(PolylineRepresentation * outerRing);
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_Grid2dRepresentation) Grid2dRepresentation;
#endif
	class Grid2dRepresentation : public AbstractSurfaceRepresentation
	{
	public:
		ULONG64 getNodeCountAlongIAxis() const;
		ULONG64 getNodeCountAlongJAxis() const;
		
		double getXOrigin() const;
		double getYOrigin() const;
		double getXOriginInGlobalCrs() const;
		double getYOriginInGlobalCrs() const;
		double getXJOffset() const;
		double getYJOffset() const;
		double getXJOffsetInGlobalCrs() const;
		double getYJOffsetInGlobalCrs() const;
		double getXIOffset() const;
		double getYIOffset() const;
		double getXIOffsetInGlobalCrs() const;
		double getYIOffsetInGlobalCrs() const;
		bool isJSpacingConstant() const;
		bool isISpacingConstant() const;
		void getJSpacing(double* const jSpacings) const;
		double getJSpacing() const;
		void getISpacing(double* const iSpacings) const;
		double getISpacing() const;
		
		void getZValues(double * values) const;
		void getZValuesInGlobalCrs(double * values) const;
		
		int getIndexOriginOnSupportingRepresentation() const;
		int getIndexOriginOnSupportingRepresentation(const unsigned int & dimension) const;
		int getNodeCountOnSupportingRepresentation(const unsigned int & dimension) const;
		int getIndexOffsetOnSupportingRepresentation(const unsigned int & dimension) const;
		
		void setGeometryAsArray2dOfLatticePoints3d(
			const unsigned int & numPointsInFastestDirection, const unsigned int & numPointsInSlowestDirection,
			const double & xOrigin, const double & yOrigin, const double & zOrigin,
			const double & xOffsetInFastestDirection, const double & yOffsetInFastestDirection, const double & zOffsetInFastestDirection,
			const double & xOffsetInSlowestDirection, const double & yOffsetInSlowestDirection, const double & zOffsetInSlowestDirection,
			const double & spacingInFastestDirection, const double & spacingInSlowestDirection);

		void setGeometryAsArray2dOfExplicitZ(
			double * zValues,
			const unsigned int & numI, const unsigned int & numJ, COMMON_NS::AbstractHdfProxy * proxy,
			Grid2dRepresentation * supportingGrid2dRepresentation,
			const unsigned int & startIndexI = 0, const unsigned int & startIndexJ = 0,
			const int & indexIncrementI = 1, const int & indexIncrementJ = 1);
			
		void setGeometryAsArray2dOfExplicitZ(
			double * zValues,
			const unsigned int & numI, const unsigned int & numJ, COMMON_NS::AbstractHdfProxy * proxy,
			const double & originX, const double & originY, const double & originZ,
			const double & offsetIX, const double & offsetIY, const double & offsetIZ, const double & spacingI,
			const double & offsetJX, const double & offsetJY, const double & offsetJZ, const double & spacingJ);
		
		Grid2dRepresentation*  getSupportingRepresentation();
		std::string getSupportingRepresentationUuid() const;
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_Grid2dSetRepresentation) Grid2dSetRepresentation;
#endif
	class Grid2dSetRepresentation : public AbstractSurfaceRepresentation
	{
	public:
		unsigned int getNodeCountAlongIAxis(const unsigned int & patchIndex) const;
		unsigned int getNodeCountAlongJAxis(const unsigned int & patchIndex) const;
		
		void getZValuesOfPatch(const unsigned int & patchIndex, double* values) const;
		void getZValuesOfPatchInGlobalCrs(const unsigned int & patchIndex, double* values) const;
		void pushBackGeometryPatch(
				double * zValues,
				const unsigned int & numI, const unsigned int & numJ, COMMON_NS::AbstractHdfProxy * proxy,
				Grid2dRepresentation * supportingGrid2dRepresentation,
				const unsigned int & startIndexI = 0, const unsigned int & startIndexJ = 0,
				const int & indexIncrementI = 1, const int & indexIncrementJ = 1);
		
		std::string getSupportingRepresentationUuid(const unsigned int & patchIndex) const;
		Grid2dRepresentation * getSupportingRepresentation(const unsigned int & patchIndex) {return supportingRepresentationSet[patchIndex];}
		int getIndexOriginOnSupportingRepresentation(const unsigned int & patchIndex, const unsigned int & dimension) const;
		int getNodeCountOnSupportingRepresentation(const unsigned int & patchIndex, const unsigned int & dimension) const;
		int getIndexOffsetOnSupportingRepresentation(const unsigned int & patchIndex, const unsigned int & dimension) const;
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_TriangulatedSetRepresentation) TriangulatedSetRepresentation;
#endif
	class TriangulatedSetRepresentation : public AbstractSurfaceRepresentation
	{
	public:
		unsigned int getTriangleCountOfPatch(const unsigned int & patchIndex) const;
		unsigned int getTriangleCountOfAllPatches() const;
		void getTriangleNodeIndicesOfPatch(const unsigned int & patchIndex, unsigned int * triangleNodeIndices) const;
		void getTriangleNodeIndicesOfAllPatches(unsigned int * triangleNodeIndices) const;
		void pushBackTrianglePatch(const unsigned int & NodeCount, double * nodes, const unsigned int & triangleCount, unsigned int * triangleNodeIndices, COMMON_NS::AbstractHdfProxy * proxy);
	};
	
	class WellboreFrameRepresentation;
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_WellboreTrajectoryRepresentation) WellboreTrajectoryRepresentation;
#endif
	class  WellboreTrajectoryRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:
		unsigned int getWellboreFrameRepresentationCount() const;
		WellboreFrameRepresentation* getWellboreFrameRepresentation(const unsigned int & index) const;
		
		std::string getMdDatumUuid() const;
		RESQML2_NS::MdDatum * getMdDatum() const;
		
		void setGeometry(double * controlPoints, const double & startMd, const double & endMd, const unsigned int & controlPointCount, const int & lineKind, class COMMON_NS::AbstractHdfProxy * proxy);
		void setGeometry(double * controlPoints,
			double* controlPointParameters, const unsigned int & controlPointCount,
			COMMON_NS::AbstractHdfProxy * proxy);
		void setGeometry(double * controlPoints,
			double * tangentVectors, double* controlPointParameters, const unsigned int & controlPointCount,
			COMMON_NS::AbstractHdfProxy * proxy);
			
		void addParentTrajectory(const double & kickoffMd, const double & parentMd, WellboreTrajectoryRepresentation* parentTrajRep);
		WellboreTrajectoryRepresentation* getParentTrajectory() const;
		const double& getParentTrajectoryMd() const;
		const std::vector<WellboreTrajectoryRepresentation*> & getChildrenTrajectorySet() const;

		bool hasGeometry() const;
		int getGeometryKind() const;

		bool hasTangentVectors() const;
		void getTangentVectors(double* tangentVectors);

		bool hasMdValues() const;
		gsoap_resqml2_0_1::eml20__LengthUom getMdUom() const;
		void getMdValues(double* values);
		double getStartMd() const;
		double getFinishMd() const;
		
		void setDeviationSurvey(class DeviationSurveyRepresentation* deviationSurvey);
		class DeviationSurveyRepresentation* getDeviationSurvey() const;

		void setWitsmlTrajectory(WITSML1_4_1_1_NS::Trajectory * witsmlTraj);
		WITSML1_4_1_1_NS::Trajectory * getWitsmlTrajectory();
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_DeviationSurveyRepresentation) DeviationSurveyRepresentation;
#endif
	class DeviationSurveyRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:
		void setGeometry(double * firstStationLocation, const ULONG64 & stationCount,
			const gsoap_resqml2_0_1::eml20__LengthUom & mdUom, double * mds,
			const gsoap_resqml2_0_1::eml20__PlaneAngleUom & angleUom, double * azimuths, double * inclinations,
			COMMON_NS::AbstractHdfProxy* proxy);

		RESQML2_NS::MdDatum * getMdDatum() const;
		std::string getMdDatumUuid() const;

		bool isFinal() const;

		gsoap_resqml2_0_1::eml20__LengthUom getMdUom() const;
		gsoap_resqml2_0_1::eml20__PlaneAngleUom getAngleUom() const;

		void getMdValues(double* values);
		void getInclinations(double* values);
		void getAzimuths(double* values);

		unsigned int getWellboreFrameRepresentationCount() const;
		class WellboreFrameRepresentation* getWellboreFrameRepresentation(unsigned int index) const;

		unsigned int getWellboreTrajectoryRepresentationCount() const;
		WellboreTrajectoryRepresentation* getWellboreTrajectoryRepresentation(const unsigned int & index) const;
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_WellboreFrameRepresentation) WellboreFrameRepresentation;
#endif
	class WellboreFrameRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:
		void setMdValues(double * mdValues, const unsigned int & mdValueCount, class COMMON_NS::AbstractHdfProxy * proxy);
		void setMdValues(const double & firstMdValue, const double & incrementMdValue, const unsigned int & mdValueCount);

		bool areMdValuesRegularlySpaced() const;
		double getMdConstantIncrementValue() const;
		double getMdFirstValue() const;

		unsigned int getMdValuesCount() const;
		RESQML2_NS::AbstractValuesProperty::hdfDatatypeEnum getMdHdfDatatype() const;
		void getMdAsDoubleValues(double * values);
		void getMdAsFloatValues(float * values);
		
		std::string getWellboreTrajectoryUuid() const;
		WellboreTrajectoryRepresentation* getWellboreTrajectory();

		void setWitsmlLog(WITSML1_4_1_1_NS::Log * witsmlLogToSet);
		WITSML1_4_1_1_NS::Log* getWitsmlLog();
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_WellboreMarker) WellboreMarker;
#endif
	class WellboreMarker : public COMMON_NS::AbstractObject
	{
	public:
		bool hasAGeologicBoundaryKind();
		gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind getGeologicBoundaryKind();
		BoundaryFeatureInterpretation* getBoundaryFeatureInterpretation() const;
		std::string getBoundaryFeatureInterpretationUuid() const;
		void setBoundaryFeatureInterpretation(BoundaryFeatureInterpretation* interp);
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_WellboreMarkerFrameRepresentation) WellboreMarkerFrameRepresentation;
#endif
	class WellboreMarkerFrameRepresentation : public WellboreFrameRepresentation
	{
	public:
		WellboreMarker* pushBackNewWellboreMarker(const std::string & guid, const std::string & title);
		WellboreMarker* pushBackNewWellboreMarker(const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind & geologicBoundaryKind);
		
		unsigned int getWellboreMarkerCount();
		const std::vector<WellboreMarker*> & getWellboreMarkerSet() const;

		void setIntervalStratigraphicUnits(unsigned int * stratiUnitIndices, const unsigned int & nullValue, class StratigraphicOccurrenceInterpretation* stratiOccurenceInterp);
		StratigraphicOccurrenceInterpretation* getStratigraphicOccurrenceInterpretation();

		void setWitsmlFormationMarker(const unsigned int & resqmlMarkerIndex, WITSML1_4_1_1_NS::FormationMarker * witsmlFormationMarker);
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_RepresentationSetRepresentation) RepresentationSetRepresentation;
#endif
	class RepresentationSetRepresentation : public RESQML2_NS::RepresentationSetRepresentation
	{
	public:
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_NonSealedSurfaceFrameworkRepresentation) NonSealedSurfaceFrameworkRepresentation;
#endif
	class NonSealedSurfaceFrameworkRepresentation : public RepresentationSetRepresentation
	{
	public:
		void pushBackNonSealedContactRepresentation(const unsigned int & pointCount, double * points, RESQML2_NS::AbstractLocal3dCrs* localCrs, COMMON_NS::AbstractHdfProxy * proxy);
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_SealedSurfaceFrameworkRepresentation) SealedSurfaceFrameworkRepresentation;
#endif
	class SealedSurfaceFrameworkRepresentation : public RepresentationSetRepresentation
	{
	public:
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_UnstructuredGridRepresentation) UnstructuredGridRepresentation;
#endif
	class UnstructuredGridRepresentation : public RESQML2_NS::AbstractGridRepresentation
	{
	public:
		void getCellFaceIsRightHanded(unsigned char* cellFaceIsRightHanded) const;
	
		ULONG64 getFaceCount() const;
		void getFaceIndicesOfCells(ULONG64 * faceIndices) const;
		void getCumulativeFaceCountPerCell(ULONG64 * faceCountPerCell) const;
		void getFaceCountPerCell(ULONG64 * faceCountPerCell) const;
		bool isFaceCountOfCellsConstant() const;
		unsigned int getConstantFaceCountOfCells() const;
		
		void getNodeIndicesOfFaces(ULONG64 * nodeIndices) const;
		void getCumulativeNodeCountPerFace(ULONG64 * nodeCountPerFace) const;
		void getNodeCountPerFace(ULONG64 * nodeCountPerFace) const;
		bool isNodeCountOfFacesConstant() const;
		unsigned int getConstantNodeCountOfFaces() const;
		
		void loadGeometry();
		unsigned int getFaceCountOfCell(const ULONG64 & cellIndex) const;
		unsigned int getNodeCountOfFaceOfCell(const ULONG64 & cellIndex, const unsigned int & localFaceIndex) const;
		ULONG64 * getNodeIndicesOfFaceOfCell(const ULONG64 & cellIndex, const unsigned int & localFaceIndex) const;
		void unloadGeometry();
		
		void setGeometry(unsigned char * cellFaceIsRightHanded, double * points, ULONG64 pointCount, class COMMON_NS::AbstractHdfProxy * proxy,
			ULONG64 * faceIndicesPerCell, ULONG64 * faceIndicesCumulativeCountPerCell,
			ULONG64 faceCount, ULONG64 * nodeIndicesPerFace, ULONG64 * nodeIndicesCumulativeCountPerFace,
			const gsoap_resqml2_0_1::resqml2__CellShape & cellShape);
		void setTetrahedraOnlyGeometry(unsigned char * cellFaceIsRightHanded, double * points, ULONG64 pointCount, ULONG64 faceCount, class COMMON_NS::AbstractHdfProxy * proxy,
			ULONG64 * faceIndicesPerCell, ULONG64 * nodeIndicesPerFace);
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_AbstractIjkGridRepresentation) AbstractIjkGridRepresentation;
#endif
	class AbstractIjkGridRepresentation : public RESQML2_NS::AbstractColumnLayerGridRepresentation
	{
	public:
		enum geometryKind { UNKNOWN = 0, EXPLICIT = 1, PARAMETRIC = 2, LATTICE = 3, NO_GEOMETRY = 4 };
	
		unsigned int getICellCount() const;
		void setICellCount(const unsigned int & iCount);
		unsigned int getJCellCount() const;
		void setJCellCount(const unsigned int & jCount);
		
		unsigned int getColumnCount() const;
		unsigned int getPillarCount() const;

		bool isRightHanded() const;

		void getPillarsOfSplitCoordinateLines(unsigned int * pillarIndices, bool reverseIAxis = false, bool reverseJAxis = false) const;
		void getColumnsOfSplitCoordinateLines(unsigned int * columnIndices, bool reverseIAxis = false, bool reverseJAxis = false) const;
		void getColumnCountOfSplitCoordinateLines(unsigned int * columnIndexCountPerSplitCoordinateLine) const;
		unsigned long getSplitCoordinateLineCount() const;
		
		void loadSplitInformation();
		void unloadSplitInformation();
		ULONG64 getXyzPointIndexFromCellCorner(const unsigned int & iCell, const unsigned int & jCell, const unsigned int & kCell, const unsigned int & corner) const;
		
		void getPillarGeometryIsDefined(bool * pillarGeometryIsDefined, bool reverseIAxis = false, bool reverseJAxis = false) const;
		bool hasEnabledCellInformation() const;
		void getEnabledCells(bool * enabledCells, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;
		void setEnabledCells(unsigned char* enabledCells);
		
		void getXyzPointsOfKInterfaceOfPatch(const unsigned int & kInterface, const unsigned int & patchIndex, double * xyzPoints);
		virtual void getXyzPointsOfKInterfaceSequenceOfPatch(const unsigned int & kInterfaceStart, const unsigned int & kInterfaceEnd, const unsigned int & patchIndex, double * xyzPoints);
		
		gsoap_resqml2_0_1::resqml2__KDirection getKDirection() const;
		
		virtual geometryKind getGeometryKind() const = 0;
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_IjkGridLatticeRepresentation) IjkGridLatticeRepresentation;
#endif
	class IjkGridLatticeRepresentation : public AbstractIjkGridRepresentation
	{
	public:
		bool isASeismicCube() const;
		bool isAFaciesCube() const;
		
		double getXOrigin() const;
		double getYOrigin() const;
		double getZOrigin() const;
		double getXOriginInGlobalCrs() const;
		double getYOriginInGlobalCrs() const;
		double getZOriginInGlobalCrs() const;
        	double getXIOffset() const;
        	double getYIOffset() const;
        	double getZIOffset() const;
        	double getXJOffset() const;
        	double getYJOffset() const;
        	double getZJOffset() const;
        	double getXKOffset() const;
        	double getYKOffset() const;
        	double getZKOffset() const;
		double getISpacing() const;
        	double getJSpacing() const;
        	double getKSpacing() const;
        	int getOriginInline() const;
        	int getOriginCrossline() const;
        	int getInlineIOffset() const;
        	int getInlineJOffset() const;
        	int getInlineKOffset() const;
        	int getCrosslineIOffset() const;
        	int getCrosslineJOffset() const;
        	int getCrosslineKOffset() const;

		void setGeometryAsCoordinateLineNodes(const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry,
						const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind,
						const bool & isRightHanded,
						const double & originX, const double & originY, const double & originZ,
						const double & directionIX, const double & directionIY, const double & directionIZ, const double & spacingI,
						const double & directionJX, const double & directionJY, const double & directionJZ, const double & spacingJ,
						const double & directionKX, const double & directionKY, const double & directionKZ, const double & spacingK);

		void addSeismic3dCoordinatesToPatch(
						const unsigned int patchIndex,
						const double & startInline, const double & incrInline, const unsigned int & countInline,
						const double & startCrossline, const double & incrCrossline, const unsigned int & countCrossline,
			            const unsigned int & countSample, RESQML2_NS::AbstractRepresentation * seismicSupport);
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_IjkGridExplicitRepresentation) IjkGridExplicitRepresentation;
#endif
	class IjkGridExplicitRepresentation : public AbstractIjkGridRepresentation
	{
	public:
		void setGeometryAsCoordinateLineNodes(
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			double * points, class COMMON_NS::AbstractHdfProxy * proxy,
			const unsigned long & splitCoordinateLineCount = 0, unsigned int * pillarOfCoordinateLine = nullptr,
			unsigned int * splitCoordinateLineColumnCumulativeCount = nullptr, unsigned int * splitCoordinateLineColumns = nullptr,
			char * definedPillars = nullptr);
			
			void setGeometryAsCoordinateLineNodesUsingExistingDatasets(
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			const std::string & points, COMMON_NS::AbstractHdfProxy* proxy,
			const unsigned long & splitCoordinateLineCount = 0, const std::string & pillarOfCoordinateLine = "",
			const std::string & splitCoordinateLineColumnCumulativeCount = "", const std::string & splitCoordinateLineColumns = "",
			const std::string & definedPillars = "");
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_IjkGridParametricRepresentation) IjkGridParametricRepresentation;
#endif	
	class IjkGridParametricRepresentation : public AbstractIjkGridRepresentation
	{
	public:
		unsigned int getControlPointMaxCountPerPillar() const;
		void getControlPoints(double * controlPoints, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;
		bool hasControlPointParameters() const;
		void getControlPointParameters(double * controlPointParameters, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;
		void getParametricLineKind(short * pillarKind, bool reverseIAxis = false, bool reverseJAxis= false) const;
		void getParametersOfNodes(double * parameters, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;

		void setGeometryAsParametricSplittedPillarNodes(
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, const unsigned int & controlPointMaxCountPerPillar, short * pillarKind, COMMON_NS::AbstractHdfProxy* proxy,
			const unsigned long & splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
			unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns);

		void setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, const unsigned int & controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars, COMMON_NS::AbstractHdfProxy* proxy,
			const unsigned long & splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
			const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns);

		void setGeometryAsParametricSplittedPillarNodes(
			const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, const unsigned int & controlPointCountPerPillar, short pillarKind, COMMON_NS::AbstractHdfProxy* proxy,
			const unsigned long & splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
			unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns);


		void setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
			const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, const unsigned int & controlPointCountPerPillar, short pillarKind, COMMON_NS::AbstractHdfProxy* proxy,
			const unsigned long & splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
			const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns);
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_IjkGridNoGeometryRepresentation) IjkGridNoGeometryRepresentation;
#endif	
	class IjkGridNoGeometryRepresentation : public AbstractIjkGridRepresentation
	{
	public:
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_GridConnectionSetRepresentation) GridConnectionSetRepresentation;
#endif	
	class GridConnectionSetRepresentation : public RESQML2_NS::GridConnectionSetRepresentation
	{
	public:
	};

	//************************************
	//************** PROPERTY ************
	//************************************	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_TimeSeries) TimeSeries;
#endif	
	class TimeSeries : public RESQML2_NS::TimeSeries
	{
	public:
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_PropertyKind) PropertyKind;
#endif	
	class PropertyKind : public RESQML2_NS::PropertyKind
	{
	public:
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_StringTableLookup) StringTableLookup;
#endif	
	class StringTableLookup : public COMMON_NS::AbstractObject
	{
	public:
		unsigned int getItemCount() const;
		long getKeyAtIndex(const unsigned int & index) const;
		std::string getStringValueAtIndex(const unsigned int & index) const;
		std::string getStringValue(const long & longValue);
		
		void addValue(const std::string & strValue, const long & longValue);
		void setValue(const std::string & strValue, const long & longValue);
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_CommentProperty) CommentProperty;
#endif	
	class CommentProperty : public RESQML2_NS::AbstractValuesProperty
	{
	public:
		void pushBackStringHdf5ArrayOfValues(const std::vector<std::string> & values, COMMON_NS::AbstractHdfProxy * proxy);
		std::vector<std::string> getStringValuesOfPatch(const unsigned int & patchIndex);
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_ContinuousProperty) ContinuousProperty;
#endif
	class ContinuousProperty : public RESQML2_NS::AbstractValuesProperty
	{
	public:

		const gsoap_resqml2_0_1::resqml2__ResqmlUom & getUom() const;
		std::string getUomAsString() const;
		
		void pushBackDoubleHdf5Array1dOfValues(double * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy* proxy,
			const double & minimumValue = std::numeric_limits<double>::quiet_NaN(), const double & maximumValue = std::numeric_limits<double>::quiet_NaN());
		void pushBackDoubleHdf5Array2dOfValues(double * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy,
			const double & minimumValue = std::numeric_limits<double>::quiet_NaN(), const double & maximumValue = std::numeric_limits<double>::quiet_NaN());
		void pushBackDoubleHdf5Array3dOfValues(double * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy,
			const double & minimumValue = std::numeric_limits<double>::quiet_NaN(), const double & maximumValue = std::numeric_limits<double>::quiet_NaN());
		void pushBackDoubleHdf5ArrayOfValues(double * values, unsigned long long * numValues, const unsigned int & numArrayDimensions, COMMON_NS::AbstractHdfProxy* proxy,
			double * minimumValue = nullptr, double * maximumValue = nullptr);
		void pushBackFloatHdf5Array1dOfValues(float * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy* proxy,
			const float & minimumValue = std::numeric_limits<float>::quiet_NaN(), const float & maximumValue = std::numeric_limits<float>::quiet_NaN());
		void pushBackFloatHdf5Array2dOfValues(float * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy,
			const float & minimumValue = std::numeric_limits<float>::quiet_NaN(), const float & maximumValue = std::numeric_limits<float>::quiet_NaN());
		void pushBackFloatHdf5Array3dOfValues(float * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy,
			const float & minimumValue = std::numeric_limits<float>::quiet_NaN(), const float & maximumValue = std::numeric_limits<float>::quiet_NaN());
		void pushBackFloatHdf5ArrayOfValues(float * values, unsigned long long * numValues, const unsigned int & numArrayDimensions, COMMON_NS::AbstractHdfProxy* proxy,
			float * minimumValue = nullptr, float * maximumValue = nullptr);


		void pushBackFloatHdf5ArrayOfValues(
			unsigned long long* numValues,
			const unsigned int& numArrayDimensions, 
			COMMON_NS::AbstractHdfProxy* proxy
		);
		void pushBackFloatHdf5ArrayOfValues(
			const ULONG64& valueCountInFastestDim,
			const ULONG64& valueCountInMiddleDim,
			const ULONG64& valueCountInSlowestDim,
			COMMON_NS::AbstractHdfProxy* proxy
		);
		void setValuesOfFloatHdf5ArrayOfValues(
			float* values, 
			const ULONG64& valueCountInFastestDim,
			const ULONG64& valueCountInMiddleDim,
			const ULONG64& valueCountInSlowestDim,
			const ULONG64& offsetInFastestDim,
			const ULONG64& offsetInMiddleDim,
			const ULONG64& offsetInSlowestDim,
			COMMON_NS::AbstractHdfProxy* proxy,
			unsigned int patchIndex = std::numeric_limits<unsigned int>::max()
		);
		void setValuesOfFloatHdf5ArrayOfValues(
			float * values, 
			unsigned long long * numValues,
			unsigned long long * offsetValues,
			const unsigned int & numArrayDimensions, 
			COMMON_NS::AbstractHdfProxy* proxy,
			unsigned int patchIndex = std::numeric_limits<unsigned int>::max()
		);

		void getDoubleValuesOfPatch(const unsigned int & patchIndex, double * values);
		void getFloatValuesOfPatch(const unsigned int & patchIndex, float * values);

		void getFloatValuesOfPatch(
			const unsigned int& patchIndex, 
			float* values, 
			unsigned long long* numValuesInEachDimension,
			unsigned long long* offsetInEachDimension,
			const unsigned int& numArrayDimensions
		);
		void getFloatValuesOf3dPatch(
			const unsigned int& patchIndex, 
			float* values, 
			const ULONG64& valueCountInFastestDim,
			const ULONG64& valueCountInMiddleDim,
			const ULONG64& valueCountInSlowestDim,
			const ULONG64& offsetInFastestDim,
			const ULONG64& offsetInMiddleDim,
			const ULONG64& offsetInSlowestDim
		);

		double getMinimumValue();
		double getMaximumValue();
		
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_ContinuousPropertySeries) ContinuousPropertySeries;
#endif
	class ContinuousPropertySeries : public ContinuousProperty
	{
	public:
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_DiscreteProperty) DiscreteProperty;
#endif
	class DiscreteProperty : public RESQML2_NS::AbstractValuesProperty
	{
	public:
		void pushBackLongHdf5Array1dOfValues(long * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy* proxy, const long & nullValue, const long & minimumValue, const long & maximumValue);
		void pushBackLongHdf5Array1dOfValues(long * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy* proxy, const long & nullValue);
		void pushBackIntHdf5Array1dOfValues(int * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy* proxy, const int & nullValue, const int & minimumValue, const int & maximumValue);
		void pushBackIntHdf5Array1dOfValues(int * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy* proxy, const int & nullValue);
		void pushBackShortHdf5Array1dOfValues(short * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy* proxy, const short & nullValue, const short & minimumValue, const short & maximumValue);
		void pushBackShortHdf5Array1dOfValues(short * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy* proxy, const short & nullValue);
		void pushBackCharHdf5Array1dOfValues(char * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy* proxy, const char & nullValue, const char & minimumValue, const char & maximumValue);
		void pushBackCharHdf5Array1dOfValues(char * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy* proxy, const char & nullValue);
		
		void pushBackLongHdf5Array2dOfValues(long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const long & nullValue, const long & minimumValue, const long & maximumValue);
		void pushBackLongHdf5Array2dOfValues(long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const long & nullValue);
		void pushBackIntHdf5Array2dOfValues(int * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const int & nullValue, const int & minimumValue, const int & maximumValue);
		void pushBackIntHdf5Array2dOfValues(int * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const int & nullValue);
		void pushBackShortHdf5Array2dOfValues(short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const short & nullValue, const short & minimumValue, const short & maximumValue);
		void pushBackShortHdf5Array2dOfValues(short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const short & nullValue);
		void pushBackUShortHdf5Array2dOfValues(unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const unsigned short & nullValue, const unsigned short & minimumValue, const unsigned short & maximumValue);
		void pushBackUShortHdf5Array2dOfValues(unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const unsigned short & nullValue);
		void pushBackCharHdf5Array2dOfValues(char * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const char & nullValue, const char & minimumValue, const char & maximumValue);
		void pushBackCharHdf5Array2dOfValues(char * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const char & nullValue);
		
		void pushBackLongHdf5Array3dOfValues(long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const long & nullValue, const long & minimumValue, const long & maximumValue);
		void pushBackLongHdf5Array3dOfValues(long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const long & nullValue);
		void pushBackIntHdf5Array3dOfValues(int * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const int & nullValue, const int & minimumValue, const int & maximumValue);
		void pushBackIntHdf5Array3dOfValues(int * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const int & nullValue);
		void pushBackShortHdf5Array3dOfValues(short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const short & nullValue, const short & minimumValue, const short & maximumValue);
		void pushBackShortHdf5Array3dOfValues(short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const short & nullValue);
		void pushBackUShortHdf5Array3dOfValues(unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const unsigned short & nullValue, const unsigned short & minimumValue, const unsigned short & maximumValue);
		void pushBackUShortHdf5Array3dOfValues(unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const unsigned short & nullValue);
		void pushBackCharHdf5Array3dOfValues(char * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const char & nullValue, const char & minimumValue, const char & maximumValue);
		void pushBackCharHdf5Array3dOfValues(char * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const char & nullValue);
		
		void pushBackLongHdf5ArrayOfValues(long * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const long & nullValue, const long & minimumValue, const long & maximumValue);
		void pushBackLongHdf5ArrayOfValues(long * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const long & nullValue);
		void pushBackIntHdf5ArrayOfValues(int * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const int & nullValue, const int & minimumValue, const int & maximumValue);
		void pushBackIntHdf5ArrayOfValues(int * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const int & nullValue);
		void pushBackShortHdf5ArrayOfValues(short * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const short & nullValue, const short & minimumValue, const short & maximumValue);
		void pushBackShortHdf5ArrayOfValues(short * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const short & nullValue);
		void pushBackUShortHdf5ArrayOfValues(unsigned short * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const unsigned short & nullValue, const unsigned short & minimumValue, const unsigned short & maximumValue);
		void pushBackUShortHdf5ArrayOfValues(unsigned short * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const unsigned short & nullValue);
		void pushBackCharHdf5ArrayOfValues(char * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const char & nullValue, const char & minimumValue, const char & maximumValue);
		void pushBackCharHdf5ArrayOfValues(char * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const char & nullValue);
		
		LONG64 getMinimumValue();
		LONG64 getMaximumValue();
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_DiscretePropertySeries) DiscretePropertySeries;
#endif
	class DiscretePropertySeries : public DiscreteProperty
	{
	public:
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_CategoricalProperty) CategoricalProperty;
#endif
	class CategoricalProperty : public RESQML2_NS::AbstractValuesProperty
	{
	public:
		std::string getStringLookupUuid() const;
		StringTableLookup* getStringLookup();
		
		void pushBackLongHdf5Array1dOfValues(long * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy * proxy, const long & nullValue);
		void pushBackUShortHdf5Array1dOfValues(unsigned short * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy * proxy, const long & nullValue);

		void pushBackLongHdf5Array2dOfValues(long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy, const long & nullValue);
		void pushBackUShortHdf5Array2dOfValues(unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy, const long & nullValue);
		
		void pushBackLongHdf5Array3dOfValues(long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy, const long & nullValue);
		void pushBackUShortHdf5Array3dOfValues(unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy, const long & nullValue);
		
		void pushBackLongHdf5ArrayOfValues(long * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const long & nullValue);
		void pushBackUShortHdf5ArrayOfValues(unsigned short * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const unsigned short & nullValue);		
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_CategoricalPropertySeries) CategoricalPropertySeries;
#endif
	class CategoricalPropertySeries : public CategoricalProperty
	{
	public:
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_0_1_PropertyKindMapper) PropertyKindMapper;
#endif
	class PropertyKindMapper
	{
	public:
		PropertyKindMapper(COMMON_NS::EpcDocument * epcDoc);

		std::string loadMappingFilesFromDirectory(const std::string & directory);
		std::string getApplicationPropertyKindNameFromResqmlStandardPropertyKindName(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & resqmlStandardPropertyKindName, const std::string & application) const;
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind getResqmlStandardPropertyKindNameFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application) const;
		std::string getApplicationPropertyKindNameFromResqmlLocalPropertyKindUuid(const std::string & resqmlLocalPropertyKindUuid, const std::string & application) const;
		std::string getResqmlLocalPropertyKindUuidFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application) const;
		PropertyKind* addResqmlLocalPropertyKindToEpcDocumentFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application);
		bool isChildOf(gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind child, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind parent) const;
		bool isAbstract(gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind resqmlStandardPropertyKindName) const;
	};
}

