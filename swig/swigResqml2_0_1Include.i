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
#include "../src/resqml2_0_1/BlockedWellboreRepresentation.h"

#include "../src/resqml2_0_1/LocalDepth3dCrs.h"
#include "../src/resqml2_0_1/LocalTime3dCrs.h"
#include "../src/resqml2_0_1/MdDatum.h"

#include "../src/resqml2_0_1/Horizon.h"
#include "../src/resqml2_0_1/TectonicBoundaryFeature.h"
#include "../src/resqml2_0_1/FrontierFeature.h"
#include "../src/resqml2_0_1/WellboreFeature.h"
#include "../src/resqml2_0_1/SeismicLineFeature.h"
#include "../src/resqml2_0_1/SeismicLineSetFeature.h"
#include "../src/resqml2_0_1/SeismicLatticeFeature.h"
#include "../src/resqml2_0_1/OrganizationFeature.h"
#include "../src/resqml2_0_1/StratigraphicUnitFeature.h"
#include "../src/resqml2_0_1/GeobodyFeature.h"
#include "../src/resqml2_0_1/FluidBoundaryFeature.h"
#include "../src/resqml2_0_1/StreamlinesFeature.h"

#include "../src/resqml2_0_1/StratigraphicColumn.h"
#include "../src/resqml2_0_1/BoundaryFeatureInterpretation.h"
#include "../src/resqml2_0_1/GenericFeatureInterpretation.h"
#include "../src/resqml2_0_1/HorizonInterpretation.h"
#include "../src/resqml2_0_1/FaultInterpretation.h"
#include "../src/resqml2_0_1/WellboreInterpretation.h"
#include "../src/resqml2_0_1/StratigraphicUnitInterpretation.h"
#include "../src/resqml2_0_1/StructuralOrganizationInterpretation.h"
#include "../src/resqml2_0_1/StratigraphicColumnRankInterpretation.h"
#include "../src/resqml2_0_1/StratigraphicOccurrenceInterpretation.h"
#include "../src/resqml2_0_1/EarthModelInterpretation.h"
#include "../src/resqml2_0_1/GeobodyBoundaryInterpretation.h"
#include "../src/resqml2_0_1/GeobodyInterpretation.h"
#include "../src/resqml2_0_1/RockFluidUnitFeature.h"
#include "../src/resqml2_0_1/RockFluidUnitInterpretation.h"
#include "../src/resqml2_0_1/RockFluidOrganizationInterpretation.h"

#include "../src/resqml2_0_1/PolylineSetRepresentation.h"
#include "../src/resqml2_0_1/PointSetRepresentation.h"
#include "../src/resqml2_0_1/PlaneSetRepresentation.h"
#include "../src/resqml2_0_1/PolylineRepresentation.h"
#include "../src/resqml2_0_1/Grid2dRepresentation.h"
#include "../src/resqml2_0_1/TriangulatedSetRepresentation.h"
#include "../src/resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "../src/resqml2_0_1/DeviationSurveyRepresentation.h"
#include "../src/resqml2_0_1/WellboreMarker.h"
#include "../src/resqml2_0_1/WellboreMarkerFrameRepresentation.h"
#include "../src/resqml2_0_1/WellboreFrameRepresentation.h"
#include "../src/resqml2_0_1/RepresentationSetRepresentation.h"
#include "../src/resqml2_0_1/NonSealedSurfaceFrameworkRepresentation.h"
#include "../src/resqml2_0_1/SealedSurfaceFrameworkRepresentation.h"
#include "../src/resqml2_0_1/SealedVolumeFrameworkRepresentation.h"

#include "../src/resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "../src/resqml2_0_1/IjkGridParametricRepresentation.h"
#include "../src/resqml2_0_1/IjkGridLatticeRepresentation.h"
#include "../src/resqml2_0_1/IjkGridNoGeometryRepresentation.h"
#include "../src/resqml2_0_1/UnstructuredGridRepresentation.h"
#include "../src/resqml2_0_1/SubRepresentation.h"
#include "../src/resqml2_0_1/GridConnectionSetRepresentation.h"
#include "../src/resqml2_0_1/StreamlinesRepresentation.h"

#include "../src/resqml2_0_1/TimeSeries.h"

#include "../src/resqml2_0_1/PropertyKind.h"
#include "../src/resqml2_0_1/PropertySet.h"
#include "../src/resqml2_0_1/DoubleTableLookup.h"
#include "../src/resqml2_0_1/StringTableLookup.h"
#include "../src/resqml2_0_1/DiscreteProperty.h"
#include "../src/resqml2_0_1/CategoricalProperty.h"
#include "../src/resqml2_0_1/CommentProperty.h"
#include "../src/resqml2_0_1/ContinuousProperty.h"
#include "../src/resqml2_0_1/PointsProperty.h"

#include "../src/resqml2_0_1/Activity.h"
#include "../src/resqml2_0_1/ActivityTemplate.h"

#include "../src/resqml2_0_1/PropertyKindMapper.h"
%}

namespace gsoap_resqml2_0_1
{
	enum class resqml20__TimeSetKind {
		single_x0020time = 0,
		equivalent_x0020times = 1,
		not_x0020a_x0020time_x0020set = 2
	};
	enum class resqml20__ParameterKind {
		dataObject = 0,
		floatingPoint = 1,
		integer = 2,
		string = 3,
		timestamp = 4,
		subActivity = 5
	};
	enum class resqml20__ThrowKind {
		reverse = 0,
		normal = 1,
		thrust = 2,
		strike_x0020and_x0020slip = 3,
		scissor = 4,
		variable = 5
	};
	enum class resqml20__ResqmlPropertyKind {
		absorbed_x0020dose = 0,
		acceleration_x0020linear = 1,
		activity_x0020_x0028of_x0020radioactivity_x0029 = 2,
		amount_x0020of_x0020substance = 3,
		amplitude = 4,
		angle_x0020per_x0020length = 5,
		angle_x0020per_x0020time = 6,
		angle_x0020per_x0020volume = 7,
		angular_x0020acceleration = 8,
		area = 9,
		area_x0020per_x0020area = 10,
		area_x0020per_x0020volume = 11,
		attenuation = 12,
		attenuation_x0020per_x0020length = 13,
		azimuth = 14,
		bubble_x0020point_x0020pressure = 15,
		bulk_x0020modulus = 16,
		capacitance = 17,
		categorical = 18,
		cell_x0020length = 19,
		charge_x0020density = 20,
		chemical_x0020potential = 21,
		code = 22,
		compressibility = 23,
		concentration_x0020of_x0020B = 24,
		conductivity = 25,
		continuous = 26,
		cross_x0020section_x0020absorption = 27,
		current_x0020density = 28,
		Darcy_x0020flow_x0020coefficient = 29,
		data_x0020transmission_x0020speed = 30,
		delta_x0020temperature = 31,
		density = 32,
		depth = 33,
		diffusion_x0020coefficient = 34,
		digital_x0020storage = 35,
		dimensionless = 36,
		dip = 37,
		discrete = 38,
		dose_x0020equivalent = 39,
		dose_x0020equivalent_x0020rate = 40,
		dynamic_x0020viscosity = 41,
		electric_x0020charge = 42,
		electric_x0020conductance = 43,
		electric_x0020current = 44,
		electric_x0020dipole_x0020moment = 45,
		electric_x0020field_x0020strength = 46,
		electric_x0020polarization = 47,
		electric_x0020potential = 48,
		electrical_x0020resistivity = 49,
		electrochemical_x0020equivalent = 50,
		electromagnetic_x0020moment = 51,
		energy_x0020length_x0020per_x0020area = 52,
		energy_x0020length_x0020per_x0020time_x0020area_x0020temperature = 53,
		energy_x0020per_x0020area = 54,
		energy_x0020per_x0020length = 55,
		equivalent_x0020per_x0020mass = 56,
		equivalent_x0020per_x0020volume = 57,
		exposure_x0020_x0028radioactivity_x0029 = 58,
		fluid_x0020volume = 59,
		force = 60,
		force_x0020area = 61,
		force_x0020length_x0020per_x0020length = 62,
		force_x0020per_x0020force = 63,
		force_x0020per_x0020length = 64,
		force_x0020per_x0020volume =
#ifdef SWIGPYTHON
(int)
#endif
			'A',
		formation_x0020volume_x0020factor =
#ifdef SWIGPYTHON
(int)
#endif
			'B',
		frequency =
#ifdef SWIGPYTHON
(int)
#endif
			'C',
		frequency_x0020interval =
#ifdef SWIGPYTHON
(int)
#endif
			'D',
		gamma_x0020ray_x0020API_x0020unit =
#ifdef SWIGPYTHON
(int)
#endif
			'E',
		heat_x0020capacity =
#ifdef SWIGPYTHON
(int)
#endif
			'F',
		heat_x0020flow_x0020rate =
#ifdef SWIGPYTHON
(int)
#endif
			'G',
		heat_x0020transfer_x0020coefficient =
#ifdef SWIGPYTHON
(int)
#endif
			'H',
		illuminance =
#ifdef SWIGPYTHON
(int)
#endif
			'I',
		index =
#ifdef SWIGPYTHON
(int)
#endif
			'J',
		irradiance =
#ifdef SWIGPYTHON
(int)
#endif
			'K',
		isothermal_x0020compressibility =
#ifdef SWIGPYTHON
(int)
#endif
			'L',
		kinematic_x0020viscosity =
#ifdef SWIGPYTHON
(int)
#endif
			'M',
		Lambda_x0020Rho =
#ifdef SWIGPYTHON
(int)
#endif
			'N',
		Lame_x0020constant =
#ifdef SWIGPYTHON
(int)
#endif
			'O',
		length =
#ifdef SWIGPYTHON
(int)
#endif
			'P',
		length_x0020per_x0020length =
#ifdef SWIGPYTHON
(int)
#endif
			'Q',
		length_x0020per_x0020temperature =
#ifdef SWIGPYTHON
(int)
#endif
			'R',
		length_x0020per_x0020volume =
#ifdef SWIGPYTHON
(int)
#endif
			'S',
		level_x0020of_x0020power_x0020intensity =
#ifdef SWIGPYTHON
(int)
#endif
			'T',
		light_x0020exposure =
#ifdef SWIGPYTHON
(int)
#endif
			'U',
		linear_x0020thermal_x0020expansion =
#ifdef SWIGPYTHON
(int)
#endif
			'V',
		luminance =
#ifdef SWIGPYTHON
(int)
#endif
			'W',
		luminous_x0020efficacy =
#ifdef SWIGPYTHON
(int)
#endif
			'X',
		luminous_x0020flux =
#ifdef SWIGPYTHON
(int)
#endif
			'Y',
		luminous_x0020intensity =
#ifdef SWIGPYTHON
(int)
#endif
			'Z',
		magnetic_x0020dipole_x0020moment = 91,
		magnetic_x0020field_x0020strength = 92,
		magnetic_x0020flux = 93,
		magnetic_x0020induction = 94,
		magnetic_x0020permeability = 95,
		magnetic_x0020vector_x0020potential = 96,
		mass =
#ifdef SWIGPYTHON
(int)
#endif
			'a',
		mass_x0020attenuation_x0020coefficient =
#ifdef SWIGPYTHON
(int)
#endif
			'b',
		mass_x0020concentration =
#ifdef SWIGPYTHON
(int)
#endif
			'c',
		mass_x0020flow_x0020rate =
#ifdef SWIGPYTHON
(int)
#endif
			'd',
		mass_x0020length =
#ifdef SWIGPYTHON
(int)
#endif
			'e',
		mass_x0020per_x0020energy =
#ifdef SWIGPYTHON
(int)
#endif
			'f',
		mass_x0020per_x0020length =
#ifdef SWIGPYTHON
(int)
#endif
			'g',
		mass_x0020per_x0020time_x0020per_x0020area =
#ifdef SWIGPYTHON
(int)
#endif
			'h',
		mass_x0020per_x0020time_x0020per_x0020length =
#ifdef SWIGPYTHON
(int)
#endif
			'i',
		mass_x0020per_x0020volume_x0020per_x0020length =
#ifdef SWIGPYTHON
(int)
#endif
			'j',
		mobility =
#ifdef SWIGPYTHON
(int)
#endif
			'k',
		modulus_x0020of_x0020compression =
#ifdef SWIGPYTHON
(int)
#endif
			'l',
		molar_x0020concentration =
#ifdef SWIGPYTHON
(int)
#endif
			'm',
		molar_x0020heat_x0020capacity =
#ifdef SWIGPYTHON
(int)
#endif
			'n',
		molar_x0020volume =
#ifdef SWIGPYTHON
(int)
#endif
			'o',
		mole_x0020per_x0020area =
#ifdef SWIGPYTHON
(int)
#endif
			'p',
		mole_x0020per_x0020time =
#ifdef SWIGPYTHON
(int)
#endif
			'q',
		mole_x0020per_x0020time_x0020per_x0020area =
#ifdef SWIGPYTHON
(int)
#endif
			'r',
		moment_x0020of_x0020force =
#ifdef SWIGPYTHON
(int)
#endif
			's',
		moment_x0020of_x0020inertia =
#ifdef SWIGPYTHON
(int)
#endif
			't',
		moment_x0020of_x0020section =
#ifdef SWIGPYTHON
(int)
#endif
			'u',
		momentum =
#ifdef SWIGPYTHON
(int)
#endif
			'v',
		Mu_x0020Rho =
#ifdef SWIGPYTHON
(int)
#endif
			'w',
		net_x0020to_x0020gross_x0020ratio =
#ifdef SWIGPYTHON
(int)
#endif
			'x',
		neutron_x0020API_x0020unit =
#ifdef SWIGPYTHON
(int)
#endif
			'y',
		nonDarcy_x0020flow_x0020coefficient =
#ifdef SWIGPYTHON
(int)
#endif
			'z',
		operations_x0020per_x0020time = 123,
		parachor = 124,
		per_x0020area = 125,
		per_x0020electric_x0020potential = 126,
		per_x0020force = 127,
		per_x0020length = 128,
		per_x0020mass = 129,
		per_x0020volume = 130,
		permeability_x0020length = 131,
		permeability_x0020rock = 132,
		permeability_x0020thickness = 133,
		permeance = 134,
		permittivity = 135,
		pH = 136,
		plane_x0020angle = 137,
		Poisson_x0020ratio = 138,
		pore_x0020volume = 139,
		porosity = 140,
		potential_x0020difference_x0020per_x0020power_x0020drop = 141,
		power = 142,
		power_x0020per_x0020volume = 143,
		pressure = 144,
		pressure_x0020per_x0020time = 145,
		pressure_x0020squared = 146,
		pressure_x0020squared_x0020per_x0020force_x0020time_x0020per_x0020area = 147,
		pressure_x0020time_x0020per_x0020volume = 148,
		productivity_x0020index = 149,
		property_x0020multiplier = 150,
		quantity = 151,
		quantity_x0020of_x0020light = 152,
		radiance = 153,
		radiant_x0020intensity = 154,
		relative_x0020permeability = 155,
		relative_x0020power = 156,
		relative_x0020time = 157,
		reluctance = 158,
		resistance = 159,
		resistivity_x0020per_x0020length = 160,
		RESQML_x0020root_x0020property = 161,
		Rock_x0020Impedance = 162,
		rock_x0020permeability = 163,
		rock_x0020volume = 164,
		saturation = 165,
		second_x0020moment_x0020of_x0020area = 166,
		shear_x0020modulus = 167,
		solid_x0020angle = 168,
		solution_x0020gas_oil_x0020ratio = 169,
		specific_x0020activity_x0020_x0028of_x0020radioactivity_x0029 = 170,
		specific_x0020energy = 171,
		specific_x0020heat_x0020capacity = 172,
		specific_x0020productivity_x0020index = 173,
		specific_x0020volume = 174,
		surface_x0020density = 175,
		temperature_x0020per_x0020length = 176,
		temperature_x0020per_x0020time = 177,
		thermal_x0020conductance = 178,
		thermal_x0020conductivity = 179,
		thermal_x0020diffusivity = 180,
		thermal_x0020insulance = 181,
		thermal_x0020resistance = 182,
		thermodynamic_x0020temperature = 183,
		thickness = 184,
		time = 185,
		time_x0020per_x0020length = 186,
		time_x0020per_x0020volume = 187,
		transmissibility = 188,
		unit_x0020productivity_x0020index = 189,
		unitless = 190,
		vapor_x0020oil_gas_x0020ratio = 191,
		velocity = 192,
		volume = 193,
		volume_x0020flow_x0020rate = 194,
		volume_x0020length_x0020per_x0020time = 195,
		volume_x0020per_x0020area = 196,
		volume_x0020per_x0020length = 197,
		volume_x0020per_x0020time_x0020per_x0020area = 198,
		volume_x0020per_x0020time_x0020per_x0020length = 199,
		volume_x0020per_x0020time_x0020per_x0020time = 200,
		volume_x0020per_x0020time_x0020per_x0020volume = 201,
		volume_x0020per_x0020volume = 202,
		volumetric_x0020heat_x0020transfer_x0020coefficient = 203,
		volumetric_x0020thermal_x0020expansion = 204,
		work = 205,
		Young_x0020modulus = 206
	};
}

namespace WITSML2_0_NS {
	class Wellbore;
}

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace RESQML2_0_1_NS::Activity;
	%nspace RESQML2_0_1_NS::ActivityTemplate;
	%nspace RESQML2_0_1_NS::BlockedWellboreRepresentation;
	%nspace RESQML2_0_1_NS::BoundaryFeature;
	%nspace RESQML2_0_1_NS::BoundaryFeatureInterpretation;
	%nspace RESQML2_0_1_NS::CategoricalProperty;
	%nspace RESQML2_0_1_NS::CommentProperty;
	%nspace RESQML2_0_1_NS::ContinuousProperty;
	%nspace RESQML2_0_1_NS::DeviationSurveyRepresentation;
	%nspace RESQML2_0_1_NS::DiscreteProperty;
	%nspace RESQML2_0_1_NS::DoubleTableLookup;
	%nspace RESQML2_0_1_NS::EarthModelInterpretation;
	%nspace RESQML2_0_1_NS::FaultInterpretation;
	%nspace RESQML2_0_1_NS::FluidBoundaryFeature;
	%nspace RESQML2_0_1_NS::FrontierFeature;
	%nspace RESQML2_0_1_NS::GenericFeatureInterpretation;
	%nspace RESQML2_0_1_NS::GeneticBoundaryFeature;
	%nspace RESQML2_0_1_NS::GeobodyBoundaryInterpretation;
	%nspace RESQML2_0_1_NS::GeobodyFeature;
	%nspace RESQML2_0_1_NS::GeobodyInterpretation;
	%nspace RESQML2_0_1_NS::GeologicUnitFeature;
	%nspace RESQML2_0_1_NS::Grid2dRepresentation;
	%nspace RESQML2_0_1_NS::GridConnectionSetRepresentation;
	%nspace RESQML2_0_1_NS::Horizon;
	%nspace RESQML2_0_1_NS::HorizonInterpretation;
	%nspace RESQML2_0_1_NS::IjkGridExplicitRepresentation;
	%nspace RESQML2_0_1_NS::IjkGridLatticeRepresentation;
	%nspace RESQML2_0_1_NS::IjkGridNoGeometryRepresentation;
	%nspace RESQML2_0_1_NS::IjkGridParametricRepresentation;
	%nspace RESQML2_0_1_NS::LocalDepth3dCrs;
	%nspace RESQML2_0_1_NS::LocalTime3dCrs ;
	%nspace RESQML2_0_1_NS::MdDatum;
	%nspace RESQML2_0_1_NS::NonSealedSurfaceFrameworkRepresentation;
	%nspace RESQML2_0_1_NS::OrganizationFeature;
	%nspace RESQML2_0_1_NS::PlaneSetRepresentation;
	%nspace RESQML2_0_1_NS::PointSetRepresentation;
	%nspace RESQML2_0_1_NS::PointsProperty;
	%nspace RESQML2_0_1_NS::PolylineRepresentation;
	%nspace RESQML2_0_1_NS::PolylineSetRepresentation;
	%nspace RESQML2_0_1_NS::PropertyKind;
	%nspace RESQML2_0_1_NS::PropertyKindMapper;
	%nspace RESQML2_0_1_NS::PropertySet;
	%nspace RESQML2_0_1_NS::RepresentationSetRepresentation;
	%nspace RESQML2_0_1_NS::RockFluidUnitFeature;
	%nspace RESQML2_0_1_NS::RockFluidUnitInterpretation;
	%nspace RESQML2_0_1_NS::RockFluidOrganizationInterpretation;
	%nspace RESQML2_0_1_NS::SealedSurfaceFrameworkRepresentation;
	%nspace RESQML2_0_1_NS::SealedVolumeFrameworkRepresentation;
	%nspace RESQML2_0_1_NS::SeismicLatticeFeature;
	%nspace RESQML2_0_1_NS::SeismicLineFeature;
	%nspace RESQML2_0_1_NS::SeismicLineSetFeature;
	%nspace RESQML2_0_1_NS::StratigraphicColumn;
	%nspace RESQML2_0_1_NS::StratigraphicColumnRankInterpretation;
	%nspace RESQML2_0_1_NS::StratigraphicOccurrenceInterpretation;
	%nspace RESQML2_0_1_NS::StratigraphicUnitFeature;
	%nspace RESQML2_0_1_NS::StratigraphicUnitInterpretation;
	%nspace RESQML2_0_1_NS::StreamlinesFeature;
	%nspace RESQML2_0_1_NS::StreamlinesRepresentation;
	%nspace RESQML2_0_1_NS::StringTableLookup;
	%nspace RESQML2_0_1_NS::StructuralOrganizationInterpretation;
	%nspace RESQML2_0_1_NS::SubRepresentation;
	%nspace RESQML2_0_1_NS::TectonicBoundaryFeature;
	%nspace RESQML2_0_1_NS::TimeSeries;
	%nspace RESQML2_0_1_NS::TriangulatedSetRepresentation;
	%nspace RESQML2_0_1_NS::UnstructuredGridRepresentation;
	%nspace RESQML2_0_1_NS::WellboreFeature;
	%nspace RESQML2_0_1_NS::WellboreFrameRepresentation;
	%nspace RESQML2_0_1_NS::WellboreInterpretation;
	%nspace RESQML2_0_1_NS::WellboreMarker;
	%nspace RESQML2_0_1_NS::WellboreMarkerFrameRepresentation;
	%nspace RESQML2_0_1_NS::WellboreTrajectoryRepresentation;
#endif

namespace RESQML2_0_1_NS
{
	%nodefaultctor; // Disable creation of default constructors
	
	/*********************************
	************ Activity ************
	*********************************/

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_ActivityTemplate) ActivityTemplate;
#endif
	class ActivityTemplate : public EML2_NS::ActivityTemplate
	{
	public:
		void pushBackParameter(const std::string & title,
			gsoap_resqml2_0_1::resqml20__ParameterKind kind,
			bool isInput, bool isOutput,
			unsigned int minOccurs, int maxOccurs);
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_Activity) Activity;
#endif
	class Activity : public EML2_NS::Activity
	{
	public:
		void pushBackParameter(const std::string title,
			double value, gsoap_resqml2_0_1::resqml20__ResqmlUom uom = gsoap_resqml2_0_1::resqml20__ResqmlUom__Euc);
		
		gsoap_resqml2_0_1::resqml20__ResqmlUom getFloatingPointQuantityParameterUom(unsigned int index) const;
	};

	//************************************/
	//************ CRS *******************/
	//************************************/
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_LocalDepth3dCrs) LocalDepth3dCrs;
#endif
	class LocalDepth3dCrs : public RESQML2_NS::LocalDepth3dCrs
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_LocalTime3dCrs) LocalTime3dCrs;
#endif
	class LocalTime3dCrs : public RESQML2_NS::LocalTime3dCrs
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_MdDatum) MdDatum;
#endif
	class MdDatum : public RESQML2_NS::MdDatum
	{
	public:
	};
	
	//************************************/
	//************ FEATURE ***************/
	//************************************/

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_BoundaryFeature) BoundaryFeature;
#endif
	class BoundaryFeature : public RESQML2_NS::BoundaryFeature
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_GeologicUnitFeature) GeologicUnitFeature;
#endif
	class GeologicUnitFeature : public RESQML2_NS::RockVolumeFeature
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_GeneticBoundaryFeature) GeneticBoundaryFeature;
#endif
	class GeneticBoundaryFeature : public BoundaryFeature
	{
	public:
		bool isAnHorizon() const;
		void setAge(unsigned int age);
		bool hasAnAge() const;
		uint64_t getAge() const;
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_Horizon) Horizon;
#endif
	class Horizon : public GeneticBoundaryFeature
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_TectonicBoundaryFeature) TectonicBoundaryFeature;
#endif
	class TectonicBoundaryFeature : public BoundaryFeature
	{
	public:
		bool isAFracture() const;
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_SeismicLineSetFeature) SeismicLineSetFeature;
#endif
	class SeismicLineSetFeature : public RESQML2_NS::SeismicLineSetFeature
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_SeismicLineFeature) SeismicLineFeature;
#endif
	class SeismicLineFeature : public RESQML2_NS::AbstractSeismicLineFeature
	{
	public:
		int64_t getTraceIndexIncrement() const;
		int64_t getFirstTraceIndex() const;
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_SeismicLatticeFeature) SeismicLatticeFeature;
#endif
	class SeismicLatticeFeature : public RESQML2_NS::SeismicLatticeFeature
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_WellboreFeature) WellboreFeature;
#endif
	class WellboreFeature : public RESQML2_NS::WellboreFeature
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_OrganizationFeature) OrganizationFeature;
#endif
	class OrganizationFeature : public RESQML2_NS::Model
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_FrontierFeature) FrontierFeature;
#endif
	class FrontierFeature : public RESQML2_NS::CulturalFeature
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_StratigraphicUnitFeature) StratigraphicUnitFeature;
#endif
	class StratigraphicUnitFeature : public GeologicUnitFeature
	{
	public:
	};
	
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_GeobodyFeature) GeobodyFeature;
#endif
	class GeobodyFeature : public GeologicUnitFeature
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_FluidBoundaryFeature) FluidBoundaryFeature;
#endif
	class FluidBoundaryFeature : public BoundaryFeature
	{
	public:
	};

	//************************************/
	//************ INTERPRETATION ********/
	//************************************/
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_GenericFeatureInterpretation) GenericFeatureInterpretation;
#endif
	class GenericFeatureInterpretation : public RESQML2_NS::GenericFeatureInterpretation
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_BoundaryFeatureInterpretation) BoundaryFeatureInterpretation;
#endif
	class BoundaryFeatureInterpretation : public RESQML2_NS::BoundaryFeatureInterpretation
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_FaultInterpretation) FaultInterpretation;
#endif
	class FaultInterpretation : public RESQML2_NS::FaultInterpretation
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_HorizonInterpretation) HorizonInterpretation;
#endif
	class HorizonInterpretation : public RESQML2_NS::HorizonInterpretation
	{
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_GeobodyBoundaryInterpretation) GeobodyBoundaryInterpretation;
#endif
	class GeobodyBoundaryInterpretation : public RESQML2_NS::GeobodyBoundaryInterpretation
	{
	};
	
	class WellboreTrajectoryRepresentation;
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_WellboreInterpretation) WellboreInterpretation;
#endif
	class WellboreInterpretation : public RESQML2_NS::WellboreInterpretation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_StratigraphicUnitInterpretation) StratigraphicUnitInterpretation;
#endif
	class StratigraphicUnitInterpretation : public RESQML2_NS::StratigraphicUnitInterpretation
	{
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_GeobodyInterpretation) GeobodyInterpretation;
#endif
	class GeobodyInterpretation : public RESQML2_NS::GeobodyInterpretation
	{
	public :
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_StructuralOrganizationInterpretation) StructuralOrganizationInterpretation;
#endif
	class StructuralOrganizationInterpretation : public RESQML2_NS::StructuralOrganizationInterpretation
	{
	public:
	};
	
	class StratigraphicOccurrenceInterpretation;	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_StratigraphicColumnRankInterpretation) StratigraphicColumnRankInterpretation;
#endif
	class StratigraphicColumnRankInterpretation : public RESQML2_NS::StratigraphicColumnRankInterpretation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_RockFluidUnitFeature) RockFluidUnitFeature;
#endif	
	class RockFluidUnitFeature : public GeologicUnitFeature
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_RockFluidUnitInterpretation) RockFluidUnitInterpretation;
#endif	
	class RockFluidUnitInterpretation : public RESQML2_NS::RockFluidUnitInterpretation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_RockFluidOrganizationInterpretation) RockFluidOrganizationInterpretation;
#endif
	class RockFluidOrganizationInterpretation : public RESQML2_NS::RockFluidOrganizationInterpretation
	{
	public:
	};
	
	class WellboreMarkerFrameRepresentation;	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_StratigraphicOccurrenceInterpretation) StratigraphicOccurrenceInterpretation;
#endif
	class StratigraphicOccurrenceInterpretation : public RESQML2_NS::StratigraphicOccurrenceInterpretation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_StratigraphicColumn) StratigraphicColumn;
#endif
	class StratigraphicColumn : public RESQML2_NS::StratigraphicColumn
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_EarthModelInterpretation) EarthModelInterpretation;
#endif
	class EarthModelInterpretation : public RESQML2_NS::EarthModelInterpretation
	{
	public:
	};

	//************************************/
	//************ REPRESENTATION ********/
	//************************************/

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_SubRepresentation) SubRepresentation;
#endif	
	class SubRepresentation : public RESQML2_NS::SubRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_PolylineSetRepresentation) PolylineSetRepresentation;
#endif
	class PolylineSetRepresentation : public RESQML2_NS::PolylineSetRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_PointSetRepresentation) PointSetRepresentation;
#endif
	class PointSetRepresentation : public RESQML2_NS::PointSetRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_PlaneSetRepresentation) PlaneSetRepresentation;
#endif
	class PlaneSetRepresentation : public RESQML2_NS::PlaneSetRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_PolylineRepresentation) PolylineRepresentation;
#endif
	class PolylineRepresentation : public RESQML2_NS::PolylineRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_Grid2dRepresentation) Grid2dRepresentation;
#endif
	class Grid2dRepresentation : public RESQML2_NS::Grid2dRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_TriangulatedSetRepresentation) TriangulatedSetRepresentation;
#endif
	class TriangulatedSetRepresentation : public RESQML2_NS::TriangulatedSetRepresentation
	{
	public:
	};
	
	class WellboreFrameRepresentation;
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_WellboreTrajectoryRepresentation) WellboreTrajectoryRepresentation;
#endif
	class  WellboreTrajectoryRepresentation : public RESQML2_NS::WellboreTrajectoryRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_DeviationSurveyRepresentation) DeviationSurveyRepresentation;
#endif
	class DeviationSurveyRepresentation : public RESQML2_NS::DeviationSurveyRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_WellboreFrameRepresentation) WellboreFrameRepresentation;
#endif
	class WellboreFrameRepresentation : public RESQML2_NS::WellboreFrameRepresentation
	{
	public:
//		void setWitsmlLog(WITSML1_4_1_1_NS::Log * witsmlLogToSet);
//		WITSML1_4_1_1_NS::Log* getWitsmlLog();
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_WellboreMarker) WellboreMarker;
#endif
	class WellboreMarker : public RESQML2_NS::WellboreMarker
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_WellboreMarkerFrameRepresentation) WellboreMarkerFrameRepresentation;
#endif
	class WellboreMarkerFrameRepresentation : public RESQML2_NS::WellboreMarkerFrameRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_RepresentationSetRepresentation) RepresentationSetRepresentation;
#endif
	class RepresentationSetRepresentation : public RESQML2_NS::RepresentationSetRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_NonSealedSurfaceFrameworkRepresentation) NonSealedSurfaceFrameworkRepresentation;
#endif
	class NonSealedSurfaceFrameworkRepresentation : public RESQML2_NS::NonSealedSurfaceFrameworkRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_SealedSurfaceFrameworkRepresentation) SealedSurfaceFrameworkRepresentation;
#endif
	class SealedSurfaceFrameworkRepresentation : public RESQML2_NS::SealedSurfaceFrameworkRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_SealedVolumeFrameworkRepresentation) SealedVolumeFrameworkRepresentation;
#endif
	class SealedVolumeFrameworkRepresentation : public RESQML2_NS::SealedVolumeFrameworkRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_UnstructuredGridRepresentation) UnstructuredGridRepresentation;
#endif
	class UnstructuredGridRepresentation : public RESQML2_NS::UnstructuredGridRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_IjkGridLatticeRepresentation) IjkGridLatticeRepresentation;
#endif
	class IjkGridLatticeRepresentation : public RESQML2_NS::IjkGridLatticeRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_IjkGridExplicitRepresentation) IjkGridExplicitRepresentation;
#endif
	class IjkGridExplicitRepresentation : public RESQML2_NS::IjkGridExplicitRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_IjkGridParametricRepresentation) IjkGridParametricRepresentation;
#endif	
	class IjkGridParametricRepresentation : public RESQML2_NS::IjkGridParametricRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_IjkGridNoGeometryRepresentation) IjkGridNoGeometryRepresentation;
#endif	
	class IjkGridNoGeometryRepresentation : public RESQML2_NS::IjkGridNoGeometryRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_GridConnectionSetRepresentation) GridConnectionSetRepresentation;
#endif	
	class GridConnectionSetRepresentation : public RESQML2_NS::GridConnectionSetRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_BlockedWellboreRepresentation) BlockedWellboreRepresentation;
#endif	
	class BlockedWellboreRepresentation : public RESQML2_NS::BlockedWellboreRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_StreamlinesFeature) StreamlinesFeature;
#endif	
	class StreamlinesFeature : public RESQML2_NS::StreamlinesFeature
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_StreamlinesRepresentation) StreamlinesRepresentation;
#endif	
	class StreamlinesRepresentation : public RESQML2_NS::StreamlinesRepresentation
	{
	public:
	};

	//************************************/
	//************** PROPERTY ************/
	//************************************/
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_TimeSeries) TimeSeries;
#endif	
	class TimeSeries : public EML2_NS::TimeSeries
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_PropertyKind) PropertyKind;
#endif	
	class PropertyKind : public EML2_NS::PropertyKind
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_DoubleTableLookup) DoubleTableLookup;
#endif	
	class DoubleTableLookup : public RESQML2_NS::DoubleTableLookup
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_StringTableLookup) StringTableLookup;
#endif	
	class StringTableLookup : public RESQML2_NS::StringTableLookup
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_PropertySet) PropertySet;
#endif	
	class PropertySet : public RESQML2_NS::PropertySet
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_CommentProperty) CommentProperty;
#endif	
	class CommentProperty : public RESQML2_NS::CommentProperty
	{
	public:
		gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind() const;
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_ContinuousProperty) ContinuousProperty;
#endif
	class ContinuousProperty : public RESQML2_NS::ContinuousProperty
	{
	public:
		gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind() const;
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_DiscreteProperty) DiscreteProperty;
#endif
	class DiscreteProperty : public RESQML2_NS::DiscreteProperty
	{
	public:
		gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind() const;
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_CategoricalProperty) CategoricalProperty;
#endif
	class CategoricalProperty : public RESQML2_NS::CategoricalProperty
	{
	public:
		gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind() const;
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_PointsProperty) PointsProperty;
#endif
	class PointsProperty : public RESQML2_NS::PointsProperty
	{
	public:
		gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind() const;
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml20_PropertyKindMapper) PropertyKindMapper;
#endif
	class PropertyKindMapper
	{
	public:
		std::string loadMappingFilesFromDirectory(const std::string & directory);
		std::string getApplicationPropertyKindNameFromResqmlStandardPropertyKindName(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind resqmlStandardPropertyKindName, const std::string & application) const;
		gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getResqmlStandardPropertyKindNameFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application) const;
		std::string getApplicationPropertyKindNameFromResqmlLocalPropertyKindUuid(const std::string & resqmlLocalPropertyKindUuid, const std::string & application) const;
		std::string getResqmlLocalPropertyKindUuidFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application) const;
		PropertyKind* addResqmlLocalPropertyKindToEpcDocumentFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application);
		bool isChildOf(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind child, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind parent) const;
		bool isAbstract(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind resqmlStandardPropertyKindName) const;
	};
}

