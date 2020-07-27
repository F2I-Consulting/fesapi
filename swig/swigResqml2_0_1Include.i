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

#include "../src/resqml2_0_1/TimeSeries.h"

#include "../src/resqml2_0_1/PropertyKind.h"
#include "../src/resqml2_0_1/PropertySet.h"
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
	enum resqml20__ParameterKind {
		resqml20__ParameterKind__dataObject = 0,
		resqml20__ParameterKind__floatingPoint = 1,
		resqml20__ParameterKind__integer = 2,
		resqml20__ParameterKind__string = 3,
		resqml20__ParameterKind__timestamp = 4,
		resqml20__ParameterKind__subActivity = 5
	};
	enum resqml20__ThrowKind {
		resqml20__ThrowKind__reverse = 0,
		resqml20__ThrowKind__normal = 1,
		resqml20__ThrowKind__thrust = 2,
		resqml20__ThrowKind__strike_x0020and_x0020slip = 3,
		resqml20__ThrowKind__scissor = 4,
		resqml20__ThrowKind__variable = 5
	};
	enum resqml20__ResqmlPropertyKind {
		resqml20__ResqmlPropertyKind__absorbed_x0020dose = 0,
		resqml20__ResqmlPropertyKind__acceleration_x0020linear = 1,
		resqml20__ResqmlPropertyKind__activity_x0020_x0028of_x0020radioactivity_x0029 = 2,
		resqml20__ResqmlPropertyKind__amount_x0020of_x0020substance = 3,
		resqml20__ResqmlPropertyKind__amplitude = 4,
		resqml20__ResqmlPropertyKind__angle_x0020per_x0020length = 5,
		resqml20__ResqmlPropertyKind__angle_x0020per_x0020time = 6,
		resqml20__ResqmlPropertyKind__angle_x0020per_x0020volume = 7,
		resqml20__ResqmlPropertyKind__angular_x0020acceleration = 8,
		resqml20__ResqmlPropertyKind__area = 9,
		resqml20__ResqmlPropertyKind__area_x0020per_x0020area = 10,
		resqml20__ResqmlPropertyKind__area_x0020per_x0020volume = 11,
		resqml20__ResqmlPropertyKind__attenuation = 12,
		resqml20__ResqmlPropertyKind__attenuation_x0020per_x0020length = 13,
		resqml20__ResqmlPropertyKind__azimuth = 14,
		resqml20__ResqmlPropertyKind__bubble_x0020point_x0020pressure = 15,
		resqml20__ResqmlPropertyKind__bulk_x0020modulus = 16,
		resqml20__ResqmlPropertyKind__capacitance = 17,
		resqml20__ResqmlPropertyKind__categorical = 18,
		resqml20__ResqmlPropertyKind__cell_x0020length = 19,
		resqml20__ResqmlPropertyKind__charge_x0020density = 20,
		resqml20__ResqmlPropertyKind__chemical_x0020potential = 21,
		resqml20__ResqmlPropertyKind__code = 22,
		resqml20__ResqmlPropertyKind__compressibility = 23,
		resqml20__ResqmlPropertyKind__concentration_x0020of_x0020B = 24,
		resqml20__ResqmlPropertyKind__conductivity = 25,
		resqml20__ResqmlPropertyKind__continuous = 26,
		resqml20__ResqmlPropertyKind__cross_x0020section_x0020absorption = 27,
		resqml20__ResqmlPropertyKind__current_x0020density = 28,
		resqml20__ResqmlPropertyKind__Darcy_x0020flow_x0020coefficient = 29,
		resqml20__ResqmlPropertyKind__data_x0020transmission_x0020speed = 30,
		resqml20__ResqmlPropertyKind__delta_x0020temperature = 31,
		resqml20__ResqmlPropertyKind__density = 32,
		resqml20__ResqmlPropertyKind__depth = 33,
		resqml20__ResqmlPropertyKind__diffusion_x0020coefficient = 34,
		resqml20__ResqmlPropertyKind__digital_x0020storage = 35,
		resqml20__ResqmlPropertyKind__dimensionless = 36,
		resqml20__ResqmlPropertyKind__dip = 37,
		resqml20__ResqmlPropertyKind__discrete = 38,
		resqml20__ResqmlPropertyKind__dose_x0020equivalent = 39,
		resqml20__ResqmlPropertyKind__dose_x0020equivalent_x0020rate = 40,
		resqml20__ResqmlPropertyKind__dynamic_x0020viscosity = 41,
		resqml20__ResqmlPropertyKind__electric_x0020charge = 42,
		resqml20__ResqmlPropertyKind__electric_x0020conductance = 43,
		resqml20__ResqmlPropertyKind__electric_x0020current = 44,
		resqml20__ResqmlPropertyKind__electric_x0020dipole_x0020moment = 45,
		resqml20__ResqmlPropertyKind__electric_x0020field_x0020strength = 46,
		resqml20__ResqmlPropertyKind__electric_x0020polarization = 47,
		resqml20__ResqmlPropertyKind__electric_x0020potential = 48,
		resqml20__ResqmlPropertyKind__electrical_x0020resistivity = 49,
		resqml20__ResqmlPropertyKind__electrochemical_x0020equivalent = 50,
		resqml20__ResqmlPropertyKind__electromagnetic_x0020moment = 51,
		resqml20__ResqmlPropertyKind__energy_x0020length_x0020per_x0020area = 52,
		resqml20__ResqmlPropertyKind__energy_x0020length_x0020per_x0020time_x0020area_x0020temperature = 53,
		resqml20__ResqmlPropertyKind__energy_x0020per_x0020area = 54,
		resqml20__ResqmlPropertyKind__energy_x0020per_x0020length = 55,
		resqml20__ResqmlPropertyKind__equivalent_x0020per_x0020mass = 56,
		resqml20__ResqmlPropertyKind__equivalent_x0020per_x0020volume = 57,
		resqml20__ResqmlPropertyKind__exposure_x0020_x0028radioactivity_x0029 = 58,
		resqml20__ResqmlPropertyKind__fluid_x0020volume = 59,
		resqml20__ResqmlPropertyKind__force = 60,
		resqml20__ResqmlPropertyKind__force_x0020area = 61,
		resqml20__ResqmlPropertyKind__force_x0020length_x0020per_x0020length = 62,
		resqml20__ResqmlPropertyKind__force_x0020per_x0020force = 63,
		resqml20__ResqmlPropertyKind__force_x0020per_x0020length = 64,
		resqml20__ResqmlPropertyKind__force_x0020per_x0020volume = 'A',
		resqml20__ResqmlPropertyKind__formation_x0020volume_x0020factor = 'B',
		resqml20__ResqmlPropertyKind__frequency = 'C',
		resqml20__ResqmlPropertyKind__frequency_x0020interval = 'D',
		resqml20__ResqmlPropertyKind__gamma_x0020ray_x0020API_x0020unit = 'E',
		resqml20__ResqmlPropertyKind__heat_x0020capacity = 'F',
		resqml20__ResqmlPropertyKind__heat_x0020flow_x0020rate = 'G',
		resqml20__ResqmlPropertyKind__heat_x0020transfer_x0020coefficient = 'H',
		resqml20__ResqmlPropertyKind__illuminance = 'I',
		resqml20__ResqmlPropertyKind__index = 'J',
		resqml20__ResqmlPropertyKind__irradiance = 'K',
		resqml20__ResqmlPropertyKind__isothermal_x0020compressibility = 'L',
		resqml20__ResqmlPropertyKind__kinematic_x0020viscosity = 'M',
		resqml20__ResqmlPropertyKind__Lambda_x0020Rho = 'N',
		resqml20__ResqmlPropertyKind__Lame_x0020constant = 'O',
		resqml20__ResqmlPropertyKind__length = 'P',
		resqml20__ResqmlPropertyKind__length_x0020per_x0020length = 'Q',
		resqml20__ResqmlPropertyKind__length_x0020per_x0020temperature = 'R',
		resqml20__ResqmlPropertyKind__length_x0020per_x0020volume = 'S',
		resqml20__ResqmlPropertyKind__level_x0020of_x0020power_x0020intensity = 'T',
		resqml20__ResqmlPropertyKind__light_x0020exposure = 'U',
		resqml20__ResqmlPropertyKind__linear_x0020thermal_x0020expansion = 'V',
		resqml20__ResqmlPropertyKind__luminance = 'W',
		resqml20__ResqmlPropertyKind__luminous_x0020efficacy = 'X',
		resqml20__ResqmlPropertyKind__luminous_x0020flux = 'Y',
		resqml20__ResqmlPropertyKind__luminous_x0020intensity = 'Z',
		resqml20__ResqmlPropertyKind__magnetic_x0020dipole_x0020moment = 91,
		resqml20__ResqmlPropertyKind__magnetic_x0020field_x0020strength = 92,
		resqml20__ResqmlPropertyKind__magnetic_x0020flux = 93,
		resqml20__ResqmlPropertyKind__magnetic_x0020induction = 94,
		resqml20__ResqmlPropertyKind__magnetic_x0020permeability = 95,
		resqml20__ResqmlPropertyKind__magnetic_x0020vector_x0020potential = 96,
		resqml20__ResqmlPropertyKind__mass = 'a',
		resqml20__ResqmlPropertyKind__mass_x0020attenuation_x0020coefficient = 'b',
		resqml20__ResqmlPropertyKind__mass_x0020concentration = 'c',
		resqml20__ResqmlPropertyKind__mass_x0020flow_x0020rate = 'd',
		resqml20__ResqmlPropertyKind__mass_x0020length = 'e',
		resqml20__ResqmlPropertyKind__mass_x0020per_x0020energy = 'f',
		resqml20__ResqmlPropertyKind__mass_x0020per_x0020length = 'g',
		resqml20__ResqmlPropertyKind__mass_x0020per_x0020time_x0020per_x0020area = 'h',
		resqml20__ResqmlPropertyKind__mass_x0020per_x0020time_x0020per_x0020length = 'i',
		resqml20__ResqmlPropertyKind__mass_x0020per_x0020volume_x0020per_x0020length = 'j',
		resqml20__ResqmlPropertyKind__mobility = 'k',
		resqml20__ResqmlPropertyKind__modulus_x0020of_x0020compression = 'l',
		resqml20__ResqmlPropertyKind__molar_x0020concentration = 'm',
		resqml20__ResqmlPropertyKind__molar_x0020heat_x0020capacity = 'n',
		resqml20__ResqmlPropertyKind__molar_x0020volume = 'o',
		resqml20__ResqmlPropertyKind__mole_x0020per_x0020area = 'p',
		resqml20__ResqmlPropertyKind__mole_x0020per_x0020time = 'q',
		resqml20__ResqmlPropertyKind__mole_x0020per_x0020time_x0020per_x0020area = 'r',
		resqml20__ResqmlPropertyKind__moment_x0020of_x0020force = 's',
		resqml20__ResqmlPropertyKind__moment_x0020of_x0020inertia = 't',
		resqml20__ResqmlPropertyKind__moment_x0020of_x0020section = 'u',
		resqml20__ResqmlPropertyKind__momentum = 'v',
		resqml20__ResqmlPropertyKind__Mu_x0020Rho = 'w',
		resqml20__ResqmlPropertyKind__net_x0020to_x0020gross_x0020ratio = 'x',
		resqml20__ResqmlPropertyKind__neutron_x0020API_x0020unit = 'y',
		resqml20__ResqmlPropertyKind__nonDarcy_x0020flow_x0020coefficient = 'z',
		resqml20__ResqmlPropertyKind__operations_x0020per_x0020time = 123,
		resqml20__ResqmlPropertyKind__parachor = 124,
		resqml20__ResqmlPropertyKind__per_x0020area = 125,
		resqml20__ResqmlPropertyKind__per_x0020electric_x0020potential = 126,
		resqml20__ResqmlPropertyKind__per_x0020force = 127,
		resqml20__ResqmlPropertyKind__per_x0020length = 128,
		resqml20__ResqmlPropertyKind__per_x0020mass = 129,
		resqml20__ResqmlPropertyKind__per_x0020volume = 130,
		resqml20__ResqmlPropertyKind__permeability_x0020length = 131,
		resqml20__ResqmlPropertyKind__permeability_x0020rock = 132,
		resqml20__ResqmlPropertyKind__permeability_x0020thickness = 133,
		resqml20__ResqmlPropertyKind__permeance = 134,
		resqml20__ResqmlPropertyKind__permittivity = 135,
		resqml20__ResqmlPropertyKind__pH = 136,
		resqml20__ResqmlPropertyKind__plane_x0020angle = 137,
		resqml20__ResqmlPropertyKind__Poisson_x0020ratio = 138,
		resqml20__ResqmlPropertyKind__pore_x0020volume = 139,
		resqml20__ResqmlPropertyKind__porosity = 140,
		resqml20__ResqmlPropertyKind__potential_x0020difference_x0020per_x0020power_x0020drop = 141,
		resqml20__ResqmlPropertyKind__power = 142,
		resqml20__ResqmlPropertyKind__power_x0020per_x0020volume = 143,
		resqml20__ResqmlPropertyKind__pressure = 144,
		resqml20__ResqmlPropertyKind__pressure_x0020per_x0020time = 145,
		resqml20__ResqmlPropertyKind__pressure_x0020squared = 146,
		resqml20__ResqmlPropertyKind__pressure_x0020squared_x0020per_x0020force_x0020time_x0020per_x0020area = 147,
		resqml20__ResqmlPropertyKind__pressure_x0020time_x0020per_x0020volume = 148,
		resqml20__ResqmlPropertyKind__productivity_x0020index = 149,
		resqml20__ResqmlPropertyKind__property_x0020multiplier = 150,
		resqml20__ResqmlPropertyKind__quantity = 151,
		resqml20__ResqmlPropertyKind__quantity_x0020of_x0020light = 152,
		resqml20__ResqmlPropertyKind__radiance = 153,
		resqml20__ResqmlPropertyKind__radiant_x0020intensity = 154,
		resqml20__ResqmlPropertyKind__relative_x0020permeability = 155,
		resqml20__ResqmlPropertyKind__relative_x0020power = 156,
		resqml20__ResqmlPropertyKind__relative_x0020time = 157,
		resqml20__ResqmlPropertyKind__reluctance = 158,
		resqml20__ResqmlPropertyKind__resistance = 159,
		resqml20__ResqmlPropertyKind__resistivity_x0020per_x0020length = 160,
		resqml20__ResqmlPropertyKind__RESQML_x0020root_x0020property = 161,
		resqml20__ResqmlPropertyKind__Rock_x0020Impedance = 162,
		resqml20__ResqmlPropertyKind__rock_x0020permeability = 163,
		resqml20__ResqmlPropertyKind__rock_x0020volume = 164,
		resqml20__ResqmlPropertyKind__saturation = 165,
		resqml20__ResqmlPropertyKind__second_x0020moment_x0020of_x0020area = 166,
		resqml20__ResqmlPropertyKind__shear_x0020modulus = 167,
		resqml20__ResqmlPropertyKind__solid_x0020angle = 168,
		resqml20__ResqmlPropertyKind__solution_x0020gas_oil_x0020ratio = 169,
		resqml20__ResqmlPropertyKind__specific_x0020activity_x0020_x0028of_x0020radioactivity_x0029 = 170,
		resqml20__ResqmlPropertyKind__specific_x0020energy = 171,
		resqml20__ResqmlPropertyKind__specific_x0020heat_x0020capacity = 172,
		resqml20__ResqmlPropertyKind__specific_x0020productivity_x0020index = 173,
		resqml20__ResqmlPropertyKind__specific_x0020volume = 174,
		resqml20__ResqmlPropertyKind__surface_x0020density = 175,
		resqml20__ResqmlPropertyKind__temperature_x0020per_x0020length = 176,
		resqml20__ResqmlPropertyKind__temperature_x0020per_x0020time = 177,
		resqml20__ResqmlPropertyKind__thermal_x0020conductance = 178,
		resqml20__ResqmlPropertyKind__thermal_x0020conductivity = 179,
		resqml20__ResqmlPropertyKind__thermal_x0020diffusivity = 180,
		resqml20__ResqmlPropertyKind__thermal_x0020insulance = 181,
		resqml20__ResqmlPropertyKind__thermal_x0020resistance = 182,
		resqml20__ResqmlPropertyKind__thermodynamic_x0020temperature = 183,
		resqml20__ResqmlPropertyKind__thickness = 184,
		resqml20__ResqmlPropertyKind__time = 185,
		resqml20__ResqmlPropertyKind__time_x0020per_x0020length = 186,
		resqml20__ResqmlPropertyKind__time_x0020per_x0020volume = 187,
		resqml20__ResqmlPropertyKind__transmissibility = 188,
		resqml20__ResqmlPropertyKind__unit_x0020productivity_x0020index = 189,
		resqml20__ResqmlPropertyKind__unitless = 190,
		resqml20__ResqmlPropertyKind__vapor_x0020oil_gas_x0020ratio = 191,
		resqml20__ResqmlPropertyKind__velocity = 192,
		resqml20__ResqmlPropertyKind__volume = 193,
		resqml20__ResqmlPropertyKind__volume_x0020flow_x0020rate = 194,
		resqml20__ResqmlPropertyKind__volume_x0020length_x0020per_x0020time = 195,
		resqml20__ResqmlPropertyKind__volume_x0020per_x0020area = 196,
		resqml20__ResqmlPropertyKind__volume_x0020per_x0020length = 197,
		resqml20__ResqmlPropertyKind__volume_x0020per_x0020time_x0020per_x0020area = 198,
		resqml20__ResqmlPropertyKind__volume_x0020per_x0020time_x0020per_x0020length = 199,
		resqml20__ResqmlPropertyKind__volume_x0020per_x0020time_x0020per_x0020time = 200,
		resqml20__ResqmlPropertyKind__volume_x0020per_x0020time_x0020per_x0020volume = 201,
		resqml20__ResqmlPropertyKind__volume_x0020per_x0020volume = 202,
		resqml20__ResqmlPropertyKind__volumetric_x0020heat_x0020transfer_x0020coefficient = 203,
		resqml20__ResqmlPropertyKind__volumetric_x0020thermal_x0020expansion = 204,
		resqml20__ResqmlPropertyKind__work = 205,
		resqml20__ResqmlPropertyKind__Young_x0020modulus = 206
	};
}

namespace WITSML2_0_NS {
	class Wellbore;
}

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
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
	%nspace RESQML2_0_1_NS::BoundaryFeature;
	%nspace RESQML2_0_1_NS::BoundaryFeatureInterpretation;
	%nspace RESQML2_0_1_NS::CategoricalProperty;
	%nspace RESQML2_0_1_NS::CommentProperty;
	%nspace RESQML2_0_1_NS::ContinuousProperty;
	%nspace RESQML2_0_1_NS::DeviationSurveyRepresentation;
	%nspace RESQML2_0_1_NS::DiscreteProperty;
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
	
	//***********************************/
	//************ Activity *************/
	//***********************************/

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(ActivityTemplate_resqml20) ActivityTemplate;
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
	%rename(Activity_resqml20) Activity;
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
	%rename(LocalDepth3dCrs_resqml20) LocalDepth3dCrs;
#endif
	class LocalDepth3dCrs : public RESQML2_NS::LocalDepth3dCrs
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(LocalTime3dCrs_resqml20) LocalTime3dCrs;
#endif
	class LocalTime3dCrs : public RESQML2_NS::LocalTime3dCrs
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(MdDatum_resqml20) MdDatum;
#endif
	class MdDatum : public RESQML2_NS::MdDatum
	{
	public:
	};
	
	//************************************/
	//************ FEATURE ***************/
	//************************************/

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(BoundaryFeature_resqml20) BoundaryFeature;
#endif
	class BoundaryFeature : public RESQML2_NS::BoundaryFeature
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(GeologicUnitFeature_resqml20) GeologicUnitFeature;
#endif
	class GeologicUnitFeature : public RESQML2_NS::RockVolumeFeature
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(GeneticBoundaryFeature_resqml20) GeneticBoundaryFeature;
#endif
	class GeneticBoundaryFeature : public BoundaryFeature
	{
	public:
		bool isAnHorizon() const;
		void setAge(unsigned int age);
		bool hasAnAge() const;
		ULONG64 getAge() const;
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Horizon_resqml20) Horizon;
#endif
	class Horizon : public GeneticBoundaryFeature
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(TectonicBoundaryFeature_resqml20) TectonicBoundaryFeature;
#endif
	class TectonicBoundaryFeature : public BoundaryFeature
	{
	public:
		bool isAFracture() const;
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(SeismicLineSetFeature_resqml20) SeismicLineSetFeature;
#endif
	class SeismicLineSetFeature : public RESQML2_NS::SeismicLineSetFeature
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(SeismicLineFeature_resqml20) SeismicLineFeature;
#endif
	class SeismicLineFeature : public RESQML2_NS::AbstractSeismicLineFeature
	{
	public:
		int getTraceIndexIncrement() const;
		int getFirstTraceIndex() const;
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(SeismicLatticeFeature_resqml20) SeismicLatticeFeature;
#endif
	class SeismicLatticeFeature : public RESQML2_NS::SeismicLatticeFeature
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(WellboreFeature_resqml20) WellboreFeature;
#endif
	class WellboreFeature : public RESQML2_NS::WellboreFeature
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(OrganizationFeature_resqml20) OrganizationFeature;
#endif
	class OrganizationFeature : public RESQML2_NS::Model
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(FrontierFeature_resqml20) FrontierFeature;
#endif
	class FrontierFeature : public RESQML2_NS::CulturalFeature
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(StratigraphicUnitFeature_resqml20) StratigraphicUnitFeature;
#endif
	class StratigraphicUnitFeature : public GeologicUnitFeature
	{
	public:
	};
	
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(GeobodyFeature_resqml20) GeobodyFeature;
#endif
	class GeobodyFeature : public GeologicUnitFeature
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(FluidBoundaryFeature_resqml20) FluidBoundaryFeature;
#endif
	class FluidBoundaryFeature : public BoundaryFeature
	{
	public:
	};

	//************************************/
	//************ INTERPRETATION ********/
	//************************************/
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(GenericFeatureInterpretation_resqml20) GenericFeatureInterpretation;
#endif
	class GenericFeatureInterpretation : public RESQML2_NS::GenericFeatureInterpretation
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(BoundaryFeatureInterpretation_resqml20) BoundaryFeatureInterpretation;
#endif
	class BoundaryFeatureInterpretation : public RESQML2_NS::BoundaryFeatureInterpretation
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(FaultInterpretation_resqml20) FaultInterpretation;
#endif
	class FaultInterpretation : public RESQML2_NS::FaultInterpretation
	{
	public: 
		void pushBackThrowInterpretation(gsoap_resqml2_0_1::resqml20__ThrowKind throwKind);
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(HorizonInterpretation_resqml20) HorizonInterpretation;
#endif
	class HorizonInterpretation : public RESQML2_NS::HorizonInterpretation
	{
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(GeobodyBoundaryInterpretation_resqml20) GeobodyBoundaryInterpretation;
#endif
	class GeobodyBoundaryInterpretation : public RESQML2_NS::GeobodyBoundaryInterpretation
	{
	};
	
	class WellboreTrajectoryRepresentation;
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(WellboreInterpretation_resqml20) WellboreInterpretation;
#endif
	class WellboreInterpretation : public RESQML2_NS::WellboreInterpretation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(StratigraphicUnitInterpretation_resqml20) StratigraphicUnitInterpretation;
#endif
	class StratigraphicUnitInterpretation : public RESQML2_NS::StratigraphicUnitInterpretation
	{
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(GeobodyInterpretation_resqml20) GeobodyInterpretation;
#endif
	class GeobodyInterpretation : public RESQML2_NS::GeobodyInterpretation
	{
	public :
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(StructuralOrganizationInterpretation_resqml20) StructuralOrganizationInterpretation;
#endif
	class StructuralOrganizationInterpretation : public RESQML2_NS::StructuralOrganizationInterpretation
	{
	public:
	};
	
	class StratigraphicOccurrenceInterpretation;	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(StratigraphicColumnRankInterpretation_resqml20) StratigraphicColumnRankInterpretation;
#endif
	class StratigraphicColumnRankInterpretation : public RESQML2_NS::StratigraphicColumnRankInterpretation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(RockFluidUnitInterpretation_resqml20) RockFluidUnitInterpretation;
#endif	
	class RockFluidUnitInterpretation : public RESQML2_NS::RockFluidUnitInterpretation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(RockFluidOrganizationInterpretation_resqml20) RockFluidOrganizationInterpretation;
#endif
	class RockFluidOrganizationInterpretation : public RESQML2_NS::RockFluidOrganizationInterpretation
	{
	public:
	};
	
	class WellboreMarkerFrameRepresentation;	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(StratigraphicOccurrenceInterpretation_resqml20) StratigraphicOccurrenceInterpretation;
#endif
	class StratigraphicOccurrenceInterpretation : public RESQML2_NS::StratigraphicOccurrenceInterpretation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(StratigraphicColumn_resqml20) StratigraphicColumn;
#endif
	class StratigraphicColumn : public RESQML2_NS::StratigraphicColumn
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(EarthModelInterpretation_resqml20) EarthModelInterpretation;
#endif
	class EarthModelInterpretation : public RESQML2_NS::EarthModelInterpretation
	{
	public:
	};

	//************************************/
	//************ REPRESENTATION ********/
	//************************************/

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(SubRepresentation_resqml20) SubRepresentation;
#endif	
	class SubRepresentation : public RESQML2_NS::SubRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(PolylineSetRepresentation_resqml20) PolylineSetRepresentation;
#endif
	class PolylineSetRepresentation : public RESQML2_NS::PolylineSetRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(PointSetRepresentation_resqml20) PointSetRepresentation;
#endif
	class PointSetRepresentation : public RESQML2_NS::PointSetRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(PlaneSetRepresentation_resqml20) PlaneSetRepresentation;
#endif
	class PlaneSetRepresentation : public RESQML2_NS::PlaneSetRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(PolylineRepresentation_resqml20) PolylineRepresentation;
#endif
	class PolylineRepresentation : public RESQML2_NS::PolylineRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Grid2dRepresentation_resqml20) Grid2dRepresentation;
#endif
	class Grid2dRepresentation : public RESQML2_NS::Grid2dRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(TriangulatedSetRepresentation_resqml20) TriangulatedSetRepresentation;
#endif
	class TriangulatedSetRepresentation : public RESQML2_NS::TriangulatedSetRepresentation
	{
	public:
	};
	
	class WellboreFrameRepresentation;
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(WellboreTrajectoryRepresentation_resqml20) WellboreTrajectoryRepresentation;
#endif
	class  WellboreTrajectoryRepresentation : public RESQML2_NS::WellboreTrajectoryRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(DeviationSurveyRepresentation_resqml20) DeviationSurveyRepresentation;
#endif
	class DeviationSurveyRepresentation : public RESQML2_NS::DeviationSurveyRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(WellboreFrameRepresentation_resqml20) WellboreFrameRepresentation;
#endif
	class WellboreFrameRepresentation : public RESQML2_NS::WellboreFrameRepresentation
	{
	public:
//		void setWitsmlLog(WITSML1_4_1_1_NS::Log * witsmlLogToSet);
//		WITSML1_4_1_1_NS::Log* getWitsmlLog();
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(WellboreMarker_resqml20) WellboreMarker;
#endif
	class WellboreMarker : public RESQML2_NS::WellboreMarker
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(WellboreMarkerFrameRepresentation_resqml20) WellboreMarkerFrameRepresentation;
#endif
	class WellboreMarkerFrameRepresentation : public RESQML2_NS::WellboreMarkerFrameRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(RepresentationSetRepresentation_resqml20) RepresentationSetRepresentation;
#endif
	class RepresentationSetRepresentation : public RESQML2_NS::RepresentationSetRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(NonSealedSurfaceFrameworkRepresentation_resqml20) NonSealedSurfaceFrameworkRepresentation;
#endif
	class NonSealedSurfaceFrameworkRepresentation : public RESQML2_NS::NonSealedSurfaceFrameworkRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(SealedSurfaceFrameworkRepresentation_resqml20) SealedSurfaceFrameworkRepresentation;
#endif
	class SealedSurfaceFrameworkRepresentation : public RESQML2_NS::SealedSurfaceFrameworkRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(SealedVolumeFrameworkRepresentation_resqml20) SealedVolumeFrameworkRepresentation;
#endif
	class SealedVolumeFrameworkRepresentation : public RESQML2_NS::SealedVolumeFrameworkRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(UnstructuredGridRepresentation_resqml20) UnstructuredGridRepresentation;
#endif
	class UnstructuredGridRepresentation : public RESQML2_NS::UnstructuredGridRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(IjkGridLatticeRepresentation_resqml20) IjkGridLatticeRepresentation;
#endif
	class IjkGridLatticeRepresentation : public RESQML2_NS::IjkGridLatticeRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(IjkGridExplicitRepresentation_resqml20) IjkGridExplicitRepresentation;
#endif
	class IjkGridExplicitRepresentation : public RESQML2_NS::IjkGridExplicitRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(IjkGridParametricRepresentation_resqml20) IjkGridParametricRepresentation;
#endif	
	class IjkGridParametricRepresentation : public RESQML2_NS::IjkGridParametricRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(IjkGridNoGeometryRepresentation_resqml20) IjkGridNoGeometryRepresentation;
#endif	
	class IjkGridNoGeometryRepresentation : public RESQML2_NS::IjkGridNoGeometryRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(GridConnectionSetRepresentation_resqml20) GridConnectionSetRepresentation;
#endif	
	class GridConnectionSetRepresentation : public RESQML2_NS::GridConnectionSetRepresentation
	{
	public:
	};

	//************************************/
	//************** PROPERTY ************/
	//************************************/
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(TimeSeries_resqml20) TimeSeries;
#endif	
	class TimeSeries : public EML2_NS::TimeSeries
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(PropertyKind_resqml20) PropertyKind;
#endif	
	class PropertyKind : public EML2_NS::PropertyKind
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(StringTableLookup_resqml20) StringTableLookup;
#endif	
	class StringTableLookup : public RESQML2_NS::StringTableLookup
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(PropertySet_resqml20) PropertySet;
#endif	
	class PropertySet : public RESQML2_NS::PropertySet
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(CommentProperty_resqml20) CommentProperty;
#endif	
	class CommentProperty : public RESQML2_NS::CommentProperty
	{
	public:
		gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind() const;
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(ContinuousProperty_resqml20) ContinuousProperty;
#endif
	class ContinuousProperty : public RESQML2_NS::ContinuousProperty
	{
	public:
		gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind() const;
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(DiscreteProperty_resqml20) DiscreteProperty;
#endif
	class DiscreteProperty : public RESQML2_NS::DiscreteProperty
	{
	public:
		gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind() const;
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(CategoricalProperty_resqml20) CategoricalProperty;
#endif
	class CategoricalProperty : public RESQML2_NS::CategoricalProperty
	{
	public:
		gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind() const;
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(PointsProperty_resqml20) PointsProperty;
#endif
	class PointsProperty : public RESQML2_NS::PointsProperty
	{
	public:
		gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind() const;
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(PropertyKindMapper_resqml20) PropertyKindMapper;
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

