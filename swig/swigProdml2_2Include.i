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
#include "../src/prodml2_2/FluidSystem.h"
#include "../src/prodml2_2/FluidCharacterization.h"
#include "../src/prodml2_2/TimeSeriesData.h"
%}

namespace std {
	%template(FluidSystemVector) vector<PRODML2_2_NS::FluidSystem*>;
	%template(FluidCharacterizationVector) vector<PRODML2_2_NS::FluidCharacterization*>;
	%template(TimeSeriesDataVector) vector<PRODML2_2_NS::TimeSeriesData*>;
}

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace PRODML2_2_NS::FluidSystem;
	%nspace PRODML2_2_NS::FluidCharacterization;
	%nspace PRODML2_2_NS::TimeSeriesData;
#endif

namespace gsoap_eml2_3
{
enum class eml23__AmountOfSubstancePerAmountOfSubstanceUom {
	_x0025 = 0,
	_x0025_x005bmolar_x005d = 1,
	Euc = 2,
	mol_x002fmol = 3,
	nEuc = 4,
	ppk = 5,
	ppm = 6
};
enum class eml23__ThermodynamicTemperatureUom {
	K = 
#ifdef SWIGPYTHON
(int)
#endif
		'K',
	degC = 
#ifdef SWIGPYTHON
(int)
#endif
		'L',
	degF = 
#ifdef SWIGPYTHON
(int)
#endif
		'M',
	degR = 
#ifdef SWIGPYTHON
(int)
#endif
		'N'
};
enum class eml23__PressureUom {
	_0_x002e01_x0020lbf_x002fft2 = 0,
	at = 1,
	atm = 2,
	bar = 3,
	cmH2O_x005b4degC_x005d = 4,
	cPa = 5,
	dPa = 6,
	dyne_x002fcm2 = 7,
	EPa = 8,
	fPa = 9,
	GPa = 10,
	hbar = 11,
	inH2O_x005b39degF_x005d = 12,
	inH2O_x005b60degF_x005d = 13,
	inHg_x005b32degF_x005d = 14,
	inHg_x005b60degF_x005d = 15,
	kgf_x002fcm2 = 16,
	kgf_x002fm2 = 17,
	kgf_x002fmm2 = 18,
	kN_x002fm2 = 19,
	kPa = 20,
	kpsi = 21,
	lbf_x002fft2 = 22,
	mbar = 23,
	mmHg_x005b0degC_x005d = 24,
	mPa = 25,
	MPa = 26,
	Mpsi = 27,
	N_x002fm2 = 28,
	N_x002fmm2 = 29,
	nPa = 30,
	Pa = 31,
	pPa = 32,
	psi = 33,
	tonf_x005bUK_x005d_x002fft2 = 34,
	tonf_x005bUS_x005d_x002fft2 = 35,
	tonf_x005bUS_x005d_x002fin2 = 36,
	torr = 37,
	TPa = 38,
	ubar = 39,
	umHg_x005b0degC_x005d = 40,
	uPa = 41,
	upsi = 42
};
enum class prodml22__ReservoirFluidKind {
	black_x0020oil = 0,
	critical_x0020or_x0020near_x0020critical = 1,
	dry_x0020gas = 2,
	heavy_x0020oil = 3,
	wet_x0020gas_x0020or_x0020condensate = 4,
	volatile_x0020oil = 5,
	unknown = 6
};
enum class eml23__VolumePerVolumeUom {
	_x0025 = 0,
	_x0025_x005bvol_x005d = 1,
	_0_x002e001_x0020bbl_x002fft3 = 2,
	_0_x002e001_x0020bbl_x002fm3 = 3,
	_0_x002e001_x0020gal_x005bUK_x005d_x002fbbl = 4,
	_0_x002e001_x0020gal_x005bUK_x005d_x002fgal_x005bUK_x005d = 5,
	_0_x002e001_x0020gal_x005bUS_x005d_x002fbbl = 6,
	_0_x002e001_x0020gal_x005bUS_x005d_x002fft3 = 7,
	_0_x002e001_x0020gal_x005bUS_x005d_x002fgal_x005bUS_x005d = 8,
	_0_x002e001_x0020pt_x005bUK_x005d_x002fbbl = 9,
	_0_x002e01_x0020bbl_x002fbbl = 10,
	_0_x002e1_x0020gal_x005bUS_x005d_x002fbbl = 11,
	_0_x002e1_x0020L_x002fbbl = 12,
	_0_x002e1_x0020pt_x005bUS_x005d_x002fbbl = 13,
	_1000_x0020ft3_x002fbbl = 14,
	_1000_x0020m3_x002fm3 = 15,
	_1E_6_x0020acre_x002eft_x002fbbl = 16,
	_1E_6_x0020bbl_x002fft3 = 17,
	_1E_6_x0020bbl_x002fm3 = 18,
	_1E6_x0020bbl_x002f_x0028acre_x002eft_x0029 = 19,
	_1E6_x0020ft3_x002f_x0028acre_x002eft_x0029 = 20,
	_1E6_x0020ft3_x002fbbl = 21,
	bbl_x002f_x0028acre_x002eft_x0029 = 22,
	bbl_x002fbbl = 23,
	bbl_x002fft3 = 24,
	bbl_x002fm3 = 25,
	cEuc = 26,
	cm3_x002fcm3 = 27,
	cm3_x002fL = 28,
	cm3_x002fm3 = 29,
	dm3_x002fm3 = 30,
	Euc = 31,
	ft3_x002fbbl = 32,
	ft3_x002fft3 = 33,
	gal_x005bUK_x005d_x002fft3 = 34,
	gal_x005bUS_x005d_x002fbbl = 35,
	gal_x005bUS_x005d_x002fft3 = 36,
	L_x002fm3 = 37,
	m3_x002f_x0028ha_x002em_x0029 = 38,
	m3_x002fbbl = 39,
	m3_x002fm3 = 40,
	mL_x002fgal_x005bUK_x005d = 41,
	mL_x002fgal_x005bUS_x005d = 42,
	mL_x002fmL = 43,
	ppk = 44,
	ppm = 45,
	ppm_x005bvol_x005d = 46
};
enum class eml23__MassPerMassUom {
	_x0025 = 0,
	_x0025_x005bmass_x005d = 1,
	Euc = 2,
	g_x002fkg = 3,
	g_x002ft = 4,
	kg_x002fkg = 5,
	kg_x002fsack_x005b94lbm_x005d = 6,
	kg_x002ft = 7,
	mg_x002fg = 8,
	mg_x002fkg = 9,
	ng_x002fg = 10,
	ng_x002fmg = 11,
	ppk = 12,
	ppm = 13,
	ppm_x005bmass_x005d = 14,
	ug_x002fg = 15,
	ug_x002fmg = 16
};
enum class prodml22__PureComponentKind {
	_1_2_4_trimethylbenzene = 0,
	_2_dimethylbutane = 1,
	_3_dimethylbutane = 2,
	ar = 3,
	c1 = 4,
	c2 = 5,
	c3 = 6,
	co2 = 7,
	cos = 8,
	h2 = 9,
	h2o = 10,
	h2s = 11,
	he = 12,
	hg = 13,
	i_c4 = 14,
	i_c5 = 15,
	n2 = 16,
	n_c10 = 17,
	n_c4 = 18,
	n_c5 = 19,
	n_c6 = 20,
	n_c7 = 21,
	n_c8 = 22,
	n_c9 = 23,
	neo_c5 = 24,
	ra = 25,
	benzene = 26,
	_2_methylpentane = 27,
	_3_methylpentane = 28,
	_2_methylhexane = 29,
	_3_methylhexane = 30,
	_2_methylheptane = 31,
	_3_methylheptane = 32,
	cyclohexane = 33,
	ethylbenzene = 34,
	ethylcyclohexane = 35,
	methylcyclohexane = 36,
	methylcyclopentane = 37,
	toluene = 38,
	m_xylene = 39,
	o_xylene = 40,
	p_xylene = 41
};
enum class eml23__MolecularWeightUom {
	g_x002fmol = 0,
	kg_x002fmol = 1,
	lbm_x002flbmol = 2
};
enum class prodml22__PlusComponentKind {
	c10_x002b = 0,
	c11_x002b = 1,
	c12_x002b = 2,
	c20_x002b = 3,
	c25_x002b = 4,
	c30_x002b = 5,
	c36_x002b = 6,
	c5_x002b = 7,
	c6_x002b = 8,
	c7_x002b = 9,
	c8_x002b = 10,
	c9_x002b = 11
};
enum class eml23__APIGravityUom {
	dAPI = 0
};
enum class eml23__EnergyPerMassUom {
	Btu_x005bIT_x005d_x002flbm = 0,
	cal_x005bth_x005d_x002fg = 1,
	cal_x005bth_x005d_x002fkg = 2,
	cal_x005bth_x005d_x002flbm = 3,
	erg_x002fg = 4,
	erg_x002fkg = 5,
	hp_x002eh_x002flbm = 6,
	J_x002fg = 7,
	J_x002fkg = 8,
	kcal_x005bth_x005d_x002fg = 9,
	kcal_x005bth_x005d_x002fkg = 10,
	kJ_x002fkg = 11,
	kW_x002eh_x002fkg = 12,
	lbf_x002eft_x002flbm = 13,
	MJ_x002fkg = 14,
	MW_x002eh_x002fkg = 15
};
enum class eml23__EnergyPerVolumeUom {
	Btu_x005bIT_x005d_x002fbbl = 0,
	Btu_x005bIT_x005d_x002fft3 = 1,
	Btu_x005bIT_x005d_x002fgal_x005bUK_x005d = 2,
	Btu_x005bIT_x005d_x002fgal_x005bUS_x005d = 3,
	cal_x005bth_x005d_x002fcm3 = 4,
	cal_x005bth_x005d_x002fmL = 5,
	cal_x005bth_x005d_x002fmm3 = 6,
	erg_x002fcm3 = 7,
	erg_x002fm3 = 8,
	hp_x002eh_x002fbbl = 9,
	J_x002fdm3 = 10,
	J_x002fm3 = 11,
	kcal_x005bth_x005d_x002fcm3 = 12,
	kcal_x005bth_x005d_x002fm3 = 13,
	kJ_x002fdm3 = 14,
	kJ_x002fm3 = 15,
	kW_x002eh_x002fdm3 = 16,
	kW_x002eh_x002fm3 = 17,
	lbf_x002eft_x002fbbl = 18,
	lbf_x002eft_x002fgal_x005bUS_x005d = 19,
	MJ_x002fm3 = 20,
	MW_x002eh_x002fm3 = 21,
	tonf_x005bUS_x005d_x002emi_x002fbbl = 22
};
enum class prodml22__PseudoComponentKind {
	c10 = 0,
	c11 = 1,
	c12 = 2,
	c13 = 3,
	c14 = 4,
	c15 = 5,
	c16 = 6,
	c17 = 7,
	c18 = 8,
	c19 = 9,
	c20 = 10,
	c21 = 11,
	c22 = 12,
	c23 = 13,
	c24 = 14,
	c25 = 15,
	c26 = 16,
	c27 = 17,
	c28 = 18,
	c29 = 19,
	c2_c4_x002bn2 = 20,
	c30 = 21,
	c31 = 22,
	c32 = 23,
	c33 = 24,
	c34 = 25,
	c35 = 26,
	c4 = 27,
	c5 = 28,
	c6 = 29,
	c7 = 30,
	c8 = 31,
	c9 = 32,
	rsh = 33
};
enum class prodml22__OutputFluidProperty {
	Compressibility = 0,
	Density = 1,
	Derivative_x0020of_x0020Density_x0020w_x002er_x002et_x0020Pressure = 2,
	Derivative_x0020of_x0020Density_x0020w_x002er_x002et_x0020Temperature = 3,
	Enthalpy = 4,
	Entropy = 5,
	Expansion_x0020Factor = 6,
	Formation_x0020Volume_x0020Factor = 7,
	Gas_Oil_x0020Interfacial_x0020Tension = 8,
	Gas_Water_x0020Interfacial_x0020Tension = 9,
	Index = 10,
	K_x0020value = 11,
	Misc_x0020Bank_x0020Critical_x0020Solvent_x0020Saturation = 12,
	Misc_x0020Bank_x0020Phase_x0020Density = 13,
	Misc_x0020Bank_x0020Phase_x0020Viscosity = 14,
	Miscibility_x0020Parameter_x0020_x0028Alpha_x0029 = 15,
	Mixing_x0020Parameter_x0020Oil_Gas = 16,
	Normalized_x0020Pseudo_x0020Pressure = 17,
	Oil_Gas_x0020Ratio = 18,
	Oil_Water_x0020Interfacial_x0020Tension = 19,
	Parachor = 20,
	Pressure = 21,
	Pseudo_x0020Pressure = 22,
	P_T_x0020Cross_x0020Term = 23,
	Saturation_x0020Pressure = 24,
	Solution_x0020GOR = 25,
	Solvent_x0020Density = 26,
	Specific_x0020Heat = 27,
	Temperature = 28,
	Thermal_x0020Conductivity = 29,
	Viscosity = 30,
	Viscosity_x0020Compressibility = 31,
	Water_x0020vapor_x0020mass_x0020fraction_x0020in_x0020gas_x0020phase = 32,
	Z_x0020Factor = 33
};
enum class prodml22__TimeSeriesKeyword {
	asset_x0020identifier = 0,
	flow = 1,
	product = 2,
	qualifier = 3,
	subqualifier = 4,
	unknown = 5
};

enum class eml23__MeasureClass {
	absorbed_x0020dose = 0,
	activity_x0020of_x0020radioactivity = 1,
	activity_x0020of_x0020radioactivity_x0020per_x0020volume = 2,
	amount_x0020of_x0020substance = 3,
	amount_x0020of_x0020substance_x0020per_x0020amount_x0020of_x0020substance = 4,
	amount_x0020of_x0020substance_x0020per_x0020area = 5,
	amount_x0020of_x0020substance_x0020per_x0020time = 6,
	amount_x0020of_x0020substance_x0020per_x0020time_x0020per_x0020area = 7,
	amount_x0020of_x0020substance_x0020per_x0020volume = 8,
	angle_x0020per_x0020length = 9,
	angle_x0020per_x0020volume = 10,
	angular_x0020acceleration = 11,
	angular_x0020velocity = 12,
	api_x0020gamma_x0020ray = 13,
	api_x0020gravity = 14,
	api_x0020neutron = 15,
	area = 16,
	area_x0020per_x0020amount_x0020of_x0020substance = 17,
	area_x0020per_x0020area = 18,
	area_x0020per_x0020count = 19,
	area_x0020per_x0020mass = 20,
	area_x0020per_x0020time = 21,
	area_x0020per_x0020volume = 22,
	attenuation_x0020per_x0020frequency_x0020interval = 23,
	capacitance = 24,
	cation_x0020exchange_x0020capacity = 25,
	data_x0020transfer_x0020speed = 26,
	diffusion_x0020coefficient = 27,
	diffusive_x0020time_x0020of_x0020flight = 28,
	digital_x0020storage = 29,
	dimensionless = 30,
	dipole_x0020moment = 31,
	dose_x0020equivalent = 32,
	dynamic_x0020viscosity = 33,
	electric_x0020charge = 34,
	electric_x0020charge_x0020per_x0020area = 35,
	electric_x0020charge_x0020per_x0020mass = 36,
	electric_x0020charge_x0020per_x0020volume = 37,
	electric_x0020conductance = 38,
	electric_x0020conductivity = 39,
	electric_x0020current = 40,
	electric_x0020current_x0020density = 41,
	electric_x0020field_x0020strength = 42,
	electric_x0020potential_x0020difference = 43,
	electric_x0020resistance = 44,
	electric_x0020resistance_x0020per_x0020length = 45,
	electrical_x0020resistivity = 46,
	electromagnetic_x0020moment = 47,
	energy = 48,
	energy_x0020length_x0020per_x0020area = 49,
	energy_x0020length_x0020per_x0020time_x0020area_x0020temperature = 50,
	energy_x0020per_x0020area = 51,
	energy_x0020per_x0020length = 52,
	energy_x0020per_x0020mass = 53,
	energy_x0020per_x0020mass_x0020per_x0020time = 54,
	energy_x0020per_x0020volume = 55,
	force = 56,
	force_x0020area = 57,
	force_x0020length_x0020per_x0020length = 58,
	force_x0020per_x0020force = 59,
	force_x0020per_x0020length = 60,
	force_x0020per_x0020volume = 61,
	frequency = 62,
	frequency_x0020interval = 63,
	heat_x0020capacity = 64,
	heat_x0020flow_x0020rate = 
#ifdef SWIGPYTHON
(int)
#endif
		'A',
	heat_x0020transfer_x0020coefficient = 
#ifdef SWIGPYTHON
(int)
#endif
		'B',
	illuminance = 
#ifdef SWIGPYTHON
(int)
#endif
		'C',
	inductance = 
#ifdef SWIGPYTHON
(int)
#endif
		'D',
	isothermal_x0020compressibility = 
#ifdef SWIGPYTHON
(int)
#endif
		'E',
	kinematic_x0020viscosity = 
#ifdef SWIGPYTHON
(int)
#endif
		'F',
	length = 
#ifdef SWIGPYTHON
(int)
#endif
		'G',
	length_x0020per_x0020angle = 
#ifdef SWIGPYTHON
(int)
#endif
		'H',
	length_x0020per_x0020length = 
#ifdef SWIGPYTHON
(int)
#endif
		'I',
	length_x0020per_x0020mass = 
#ifdef SWIGPYTHON
(int)
#endif
		'J',
	length_x0020per_x0020pressure = 
#ifdef SWIGPYTHON
(int)
#endif
		'K',
	length_x0020per_x0020temperature = 
#ifdef SWIGPYTHON
(int)
#endif
		'L',
	length_x0020per_x0020time = 
#ifdef SWIGPYTHON
(int)
#endif
		'M',
	length_x0020per_x0020volume = 
#ifdef SWIGPYTHON
(int)
#endif
		'N',
	light_x0020exposure = 
#ifdef SWIGPYTHON
(int)
#endif
		'O',
	linear_x0020acceleration = 
#ifdef SWIGPYTHON
(int)
#endif
		'P',
	linear_x0020thermal_x0020expansion = 
#ifdef SWIGPYTHON
(int)
#endif
		'Q',
	logarithmic_x0020power_x0020ratio = 
#ifdef SWIGPYTHON
(int)
#endif
		'R',
	logarithmic_x0020power_x0020ratio_x0020per_x0020length = 
#ifdef SWIGPYTHON
(int)
#endif
		'S',
	luminance = 
#ifdef SWIGPYTHON
(int)
#endif
		'T',
	luminous_x0020efficacy = 
#ifdef SWIGPYTHON
(int)
#endif
		'U',
	luminous_x0020flux = 
#ifdef SWIGPYTHON
(int)
#endif
		'V',
	luminous_x0020intensity = 
#ifdef SWIGPYTHON
(int)
#endif
		'W',
	magnetic_x0020dipole_x0020moment = 
#ifdef SWIGPYTHON
(int)
#endif
		'X',
	magnetic_x0020field_x0020strength = 
#ifdef SWIGPYTHON
(int)
#endif
		'Y',
	magnetic_x0020flux = 
#ifdef SWIGPYTHON
(int)
#endif
		'Z',
	magnetic_x0020flux_x0020density = 91,
	magnetic_x0020flux_x0020density_x0020per_x0020length = 92,
	magnetic_x0020permeability = 93,
	magnetic_x0020vector_x0020potential = 94,
	mass = 95,
	mass_x0020length = 96,
	mass_x0020per_x0020area = 
#ifdef SWIGPYTHON
(int)
#endif
		'a',
	mass_x0020per_x0020energy = 
#ifdef SWIGPYTHON
(int)
#endif
		'b',
	mass_x0020per_x0020length = 
#ifdef SWIGPYTHON
(int)
#endif
		'c',
	mass_x0020per_x0020mass = 
#ifdef SWIGPYTHON
(int)
#endif
		'd',
	mass_x0020per_x0020time = 
#ifdef SWIGPYTHON
(int)
#endif
		'e',
	mass_x0020per_x0020time_x0020per_x0020area = 
#ifdef SWIGPYTHON
(int)
#endif
		'f',
	mass_x0020per_x0020time_x0020per_x0020length = 
#ifdef SWIGPYTHON
(int)
#endif
		'g',
	mass_x0020per_x0020volume = 
#ifdef SWIGPYTHON
(int)
#endif
		'h',
	mass_x0020per_x0020volume_x0020per_x0020length = 
#ifdef SWIGPYTHON
(int)
#endif
		'i',
	mass_x0020per_x0020volume_x0020per_x0020pressure = 
#ifdef SWIGPYTHON
(int)
#endif
		'j',
	mass_x0020per_x0020volume_x0020per_x0020temperature = 
#ifdef SWIGPYTHON
(int)
#endif
		'k',
	mobility = 
#ifdef SWIGPYTHON
(int)
#endif
		'l',
	molar_x0020energy = 
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
	molecular_x0020weight = 
#ifdef SWIGPYTHON
(int)
#endif
		'p',
	moment_x0020of_x0020force = 
#ifdef SWIGPYTHON
(int)
#endif
		'q',
	moment_x0020of_x0020inertia = 
#ifdef SWIGPYTHON
(int)
#endif
		'r',
	momentum = 
#ifdef SWIGPYTHON
(int)
#endif
		's',
	normalized_x0020power = 
#ifdef SWIGPYTHON
(int)
#endif
		't',
	permeability_x0020length = 
#ifdef SWIGPYTHON
(int)
#endif
		'u',
	permeability_x0020rock = 
#ifdef SWIGPYTHON
(int)
#endif
		'v',
	permittivity = 
#ifdef SWIGPYTHON
(int)
#endif
		'w',
	plane_x0020angle = 
#ifdef SWIGPYTHON
(int)
#endif
		'x',
	potential_x0020difference_x0020per_x0020power_x0020drop = 
#ifdef SWIGPYTHON
(int)
#endif
		'y',
	power = 
#ifdef SWIGPYTHON
(int)
#endif
		'z',
	power_x0020per_x0020area = 123,
	power_x0020per_x0020power = 124,
	power_x0020per_x0020volume = 125,
	pressure = 126,
	pressure_x0020per_x0020flowrate = 127,
	pressure_x0020per_x0020flowrate_x0020squared = 128,
	pressure_x0020per_x0020pressure = 129,
	pressure_x0020per_x0020time = 130,
	pressure_x0020per_x0020volume = 131,
	pressure_x0020squared = 132,
	pressure_x0020squared_x0020per_x0020force_x0020time_x0020per_x0020area = 133,
	pressure_x0020time_x0020per_x0020volume = 134,
	quantity_x0020of_x0020light = 135,
	radiance = 136,
	radiant_x0020intensity = 137,
	reciprocal_x0020area = 138,
	reciprocal_x0020electric_x0020potential_x0020difference = 139,
	reciprocal_x0020force = 140,
	reciprocal_x0020length = 141,
	reciprocal_x0020mass = 142,
	reciprocal_x0020mass_x0020time = 143,
	reciprocal_x0020pressure = 144,
	reciprocal_x0020time = 145,
	reciprocal_x0020volume = 146,
	reluctance = 147,
	second_x0020moment_x0020of_x0020area = 148,
	signaling_x0020event_x0020per_x0020time = 149,
	solid_x0020angle = 150,
	specific_x0020heat_x0020capacity = 151,
	temperature_x0020interval = 152,
	temperature_x0020interval_x0020per_x0020length = 153,
	temperature_x0020interval_x0020per_x0020pressure = 154,
	temperature_x0020interval_x0020per_x0020time = 155,
	thermal_x0020conductance = 156,
	thermal_x0020conductivity = 157,
	thermal_x0020diffusivity = 158,
	thermal_x0020insulance = 159,
	thermal_x0020resistance = 160,
	thermodynamic_x0020temperature = 161,
	thermodynamic_x0020temperature_x0020per_x0020thermodynamic_x0020temperature = 162,
	time = 163,
	time_x0020per_x0020length = 164,
	time_x0020per_x0020mass = 165,
	time_x0020per_x0020time = 166,
	time_x0020per_x0020volume = 167,
	vertical_x0020coordinate = 168,
	volume = 169,
	volume_x0020flow_x0020rate_x0020per_x0020volume_x0020flow_x0020rate = 170,
	volume_x0020per_x0020area = 171,
	volume_x0020per_x0020length = 172,
	volume_x0020per_x0020mass = 173,
	volume_x0020per_x0020pressure = 174,
	volume_x0020per_x0020rotation = 175,
	volume_x0020per_x0020time = 176,
	volume_x0020per_x0020time_x0020length = 177,
	volume_x0020per_x0020time_x0020per_x0020area = 178,
	volume_x0020per_x0020time_x0020per_x0020length = 179,
	volume_x0020per_x0020time_x0020per_x0020pressure = 180,
	volume_x0020per_x0020time_x0020per_x0020pressure_x0020length = 181,
	volume_x0020per_x0020time_x0020per_x0020time = 182,
	volume_x0020per_x0020time_x0020per_x0020volume = 183,
	volume_x0020per_x0020volume = 184,
	volumetric_x0020heat_x0020transfer_x0020coefficient = 185,
	volumetric_x0020thermal_x0020expansion = 186,
	unitless = 187
};
enum class prodml22__ValueStatus {
	access_x0020denied = 0,
	bad = 1,
	bad_x0020calibration = 2,
	calculation_x0020failure = 3,
	comm_x0020failure = 4,
	device_x0020failure = 5,
	frozen = 6,
	not_x0020available = 7,
	overflow = 8,
	questionable = 9,
	range_x0020limit = 10,
	sensor_x0020failure = 11,
	substituted = 12,
	timeout = 13
};
}

#define GETTER_FLUID_COMPONENT_ATTRIBUTE(vectorName, attributeName, attributeDatatype)\
	attributeDatatype get##vectorName##attributeName(unsigned int index) const;

#define GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(vectorName, attributeName, attributeDatatype)\
	void set##vectorName##attributeName(unsigned int index, const attributeDatatype& value);\
	bool has##vectorName##attributeName(unsigned int index);\
	attributeDatatype get##vectorName##attributeName(unsigned int index) const;

#define GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(vectorName, attributeName, uomDatatype)\
	void set##vectorName##attributeName(unsigned int index, double value, uomDatatype uom);\
	double has##vectorName##attributeName(unsigned int index) const;\
	double get##vectorName##attributeName##Value(unsigned int index) const;\
	uomDatatype get##vectorName##attributeName##Uom(unsigned int index) const;

#define GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(vectorName)\
	GETTER_FLUID_COMPONENT_ATTRIBUTE(vectorName, uid, std::string)\
	GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(vectorName, Remark, std::string)\
	GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(vectorName, MassFraction, gsoap_eml2_3::eml23__MassPerMassUom)\
	GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(vectorName, MoleFraction, gsoap_eml2_3::eml23__AmountOfSubstancePerAmountOfSubstanceUom)

namespace PRODML2_2_NS
{
	%nodefaultctor; // Disable creation of default constructors

	class FluidSystem : public COMMON_NS::AbstractObject
	{
	public:
		gsoap_eml2_3::prodml22__ReservoirFluidKind getReservoirFluidKind() const;
	};
	
	/**
	 * The fluid characterization data object describes the characteristics and properties of a
	 * fluid sample or fluid system under the conditions expected in a historical or future state.
	 * Three basic formats are available to represent fluid characterization results for delivery to
	 * consumer applications:  
	 * - Model (model kind + parameters)
	 * - Tabular
	 * - Set of Fluid Characterization Parameters
	 */
	class FluidCharacterization : public COMMON_NS::AbstractObject
	{
	public:
		/**
		 * Sets standard conditions
		 *
		 * @param 	temperatureValue	The temperature value.
		 * @param 	temperatureUom  	The temperature uom.
		 * @param 	pressureValue   	The pressure value.
		 * @param 	pressureUom			The pressure uom.
		 */
		void setStandardConditions(double temperatureValue, gsoap_eml2_3::eml23__ThermodynamicTemperatureUom temperatureUom,
			double pressureValue, gsoap_eml2_3::eml23__PressureUom pressureUom);

		/**
		 * Query if this object has standard conditions
		 *
		 * @returns	True if standard conditions, false if not.
		 */
		bool hasStandardConditions() const;

		/**
		 * Gets standard temperature value
		 *
		 * @returns	The standard temperature value.
		 */
		double getStandardTemperatureValue() const;

		/**
		 * Gets standard temperature uom
		 *
		 * @returns	The standard temperature uom.
		 */
		gsoap_eml2_3::eml23__ThermodynamicTemperatureUom getStandardTemperatureUom() const;

		/**
		 * Gets standard pressure value
		 *
		 * @returns	The standard pressure value.
		 */
		double getStandardPressureValue() const;

		/**
		 * Gets standard pressure uom
		 *
		 * @returns	The standard pressure uom.
		 */
		gsoap_eml2_3::eml23__PressureUom getStandardPressureUom() const;
		
		/**
		 * Gets rock fluid unit
		 *
		 * @returns	Null if it fails, else the rock fluid unit.
		 */
		RESQML2_NS::RockFluidUnitInterpretation* getRockFluidUnit() const;
		
		/**
		 * Gets formation water count
		 *
		 * @returns	The formation water count.
		 */
		unsigned int getFormationWaterCount() const;

		/**
		 * Pushes a back formation water
		 *
		 * @param 	uid	The UID.
		 */
		void pushBackFormationWater(const std::string & uid);
		GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(FormationWater)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(FormationWater, Salinity, gsoap_eml2_3::eml23__MassPerMassUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(FormationWater, SpecificGravity, double)

		/**
		 * Gets pure fluid component count
		 *
		 * @returns	The pure fluid component count.
		 */
		unsigned int getPureFluidComponentCount() const;

		/**
		 * Pushes a back pure fluid component
		 *
		 * @param 	uid			   	The UID.
		 * @param 	kind		   	The kind.
		 * @param 	hydrocarbonFlag	True to hydrocarbon flag.
		 */
		void pushBackPureFluidComponent(const std::string & uid, gsoap_eml2_3::prodml22__PureComponentKind kind, bool hydrocarbonFlag);
		GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(PureFluidComponent)
		GETTER_FLUID_COMPONENT_ATTRIBUTE(PureFluidComponent, Kind, std::string)
		GETTER_FLUID_COMPONENT_ATTRIBUTE(PureFluidComponent, HydrocarbonFlag, bool)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PureFluidComponent, MolecularWeight, gsoap_eml2_3::eml23__MolecularWeightUom)

		/**
		 * Gets plus fluid component count
		 *
		 * @returns	The plus fluid component count.
		 */
		unsigned int getPlusFluidComponentCount() const;

		/**
		 * Pushes a back plus fluid component
		 *
		 * @param 	uid 	The UID.
		 * @param 	kind	The kind.
		 */
		void pushBackPlusFluidComponent(const std::string & uid, gsoap_eml2_3::prodml22__PlusComponentKind kind);
		GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(PlusFluidComponent)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(PlusFluidComponent, SpecificGravity, double)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(PlusFluidComponent, StartingCarbonNumber, uint64_t)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PlusFluidComponent, StartingBoilingPoint, gsoap_eml2_3::eml23__ThermodynamicTemperatureUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PlusFluidComponent, AvgDensity, std::string)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PlusFluidComponent, AvgMolecularWeight, gsoap_eml2_3::eml23__MolecularWeightUom)

		/**
		 * Gets stock tank oil count
		 *
		 * @returns	The stock tank oil count.
		 */
		unsigned int getStockTankOilCount() const;

		/**
		 * Pushes a back stock tank oil
		 *
		 * @param 	uid	The UID.
		 */
		void pushBackStockTankOil(const std::string & uid);
		GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(StockTankOil)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, APIGravity, gsoap_eml2_3::eml23__APIGravityUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, MolecularWeight, gsoap_eml2_3::eml23__MolecularWeightUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, GrossEnergyContentPerUnitMass, gsoap_eml2_3::eml23__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, NetEnergyContentPerUnitMass, gsoap_eml2_3::eml23__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, GrossEnergyContentPerUnitVolume, gsoap_eml2_3::eml23__EnergyPerVolumeUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, NetEnergyContentPerUnitVolume, gsoap_eml2_3::eml23__EnergyPerVolumeUom)

		/**
		 * Gets natural gas count
		 *
		 * @returns	The natural gas count.
		 */
		unsigned int getNaturalGasCount() const;

		/**
		 * Pushes a back natural gas
		 *
		 * @param 	uid	The UID.
		 */
		void pushBackNaturalGas(const std::string & uid);
		GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(NaturalGas)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(NaturalGas, GasGravity, double)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, MolecularWeight, gsoap_eml2_3::eml23__MolecularWeightUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, GrossEnergyContentPerUnitMass, gsoap_eml2_3::eml23__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, NetEnergyContentPerUnitMass, gsoap_eml2_3::eml23__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, GrossEnergyContentPerUnitVolume, gsoap_eml2_3::eml23__EnergyPerVolumeUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, NetEnergyContentPerUnitVolume, gsoap_eml2_3::eml23__EnergyPerVolumeUom)

		/**
		 * Gets pseudo fluid component count
		 *
		 * @returns	The pseudo fluid component count.
		 */
		unsigned int getPseudoFluidComponentCount() const;

		/**
		 * Pushes a back pseudo fluid component
		 *
		 * @param 	uid 	The UID.
		 * @param 	kind	The kind.
		 */
		void pushBackPseudoFluidComponent(const std::string & uid, gsoap_eml2_3::prodml22__PseudoComponentKind kind);
		GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(PseudoFluidComponent)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(PseudoFluidComponent, SpecificGravity, double)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(PseudoFluidComponent, StartingCarbonNumber, uint64_t)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(PseudoFluidComponent, EndingCarbonNumber, uint64_t)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, StartingBoilingPoint, gsoap_eml2_3::eml23__ThermodynamicTemperatureUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, EndingBoilingPoint, gsoap_eml2_3::eml23__ThermodynamicTemperatureUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, AvgBoilingPoint, gsoap_eml2_3::eml23__ThermodynamicTemperatureUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, AvgDensity, std::string)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, AvgMolecularWeight, gsoap_eml2_3::eml23__MolecularWeightUom)
		
		/**
		 * Gets model count
		 *
		 * @returns	The model count.
		 */
		unsigned int getModelCount() const;

		/**
		 * Pushes a back model
		 *
		 * @param 	uid	The UID. If empty, it will be set to its index in this Fluid Characterization
		 */
		void pushBackModel(const std::string & uid = "");
		
		GETTER_SETTER_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_3::prodml22__FluidCharacterization, gsoapProxy2_2, Model, Name, std::string)
		GETTER_SETTER_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_3::prodml22__FluidCharacterization, gsoapProxy2_2, Model, Remark, std::string)
		GETTER_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_3::prodml22__FluidCharacterization, gsoapProxy2_2, Model, ReferenceTemperature, gsoap_eml2_3::eml23__ThermodynamicTemperatureUom)
		GETTER_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_3::prodml22__FluidCharacterization, gsoapProxy2_2, Model, ReferenceStockTankTemperature, gsoap_eml2_3::eml23__ThermodynamicTemperatureUom)
		
		/**
		 * Gets the table format count
		 *
		 * @returns	The table format count.
		 */
		void getTableFormatCount() const;
		
		/**
		* Pushes a table format
		*
		* @param 	uid	The UID. If empty, it will be set to its index in this Fluid Characterization
		*/
		void pushBackTableFormat(const std::string & uid = "");
		
		/**
		 * Gets the uom of a table format column
		 *
		 * @param	tableFormatUid	The uid of the table format.
		 * @param	columnIndex		The zero-based index of the column.
		 * @returns	The uom of a table format column
		 */
		std::string getTableFormatColumnUom(const std::string & tableFormatUid, unsigned int columnIndex) const;

		/**
		 * Gets the property kind of a table format column
		 *
		 * @param	tableFormatUid	The uid of the table format.
		 * @param	columnIndex		The zero-based index of the column.
		 * @returns	The property kind of a table format column
		 */
		std::string getTableFormatColumnProperty(const std::string & tableFormatUid, unsigned int columnIndex) const;
		
		/**
		* Pushes a table format colum
		*
		* @param	tableFormatIndex	Zero-based index of the table format.
		* @param 	uom					The uom associated to the values of this column
		* @param	fluidProperty		The property that this column contains
		*/
		void pushBackTableFormatColumn(unsigned int tableFormatIndex, gsoap_eml2_3::eml23__UnitOfMeasure uom, gsoap_eml2_3::prodml22__OutputFluidProperty fluidProperty);
			
		/**
		* Pushes a table format colum
		*
		* @param	tableFormatIndex	Zero-based index of the table format.
		* @param 	uom					The uom associated to the values of this column
		* @param	fluidProperty		The non standard property name that this column contains
		*/
		void pushBackTableFormatColumn(unsigned int tableFormatIndex, const std::string & uom, const std::string & fluidProperty);
		
		/**
		 * Gets the table count
		 *
		 * @param	modelIndex		Zero-based index of the model in this fluid characterization.
		 * @returns	The table count.
		 */
		unsigned int getTableCount(unsigned int modelIndex) const;
		
		/**
		 * Gets the name of a table.
		 *
		 * @param	modelIndex		Zero-based index of the model in this fluid characterization.
		 * @param 	tableIndex		Zero-based index of the table in a model of this fluid characterization.
		 * @returns	The name of a table.
		 */
		std::string getTableName(unsigned int modelIndex, unsigned int tableIndex) const;
		
		/**
		 * Gets the uid of the table format of a table.
		 *
		 * @param	modelIndex		Zero-based index of the model in this fluid characterization.
		 * @param 	tableIndex		Zero-based index of the table in a model of this fluid characterization.
		 * @returns	The uid of the table format of a table.
		 */
		std::string getTableFormatUid(unsigned int modelIndex, unsigned int tableIndex) const;
		
		/**
		* Pushes back a table
		*
		* @param	modelIndex		Zero-based index of the model.
		* @param 	name			The name of this table.
		* @param 	tableFormatUid	The UID of the table format this table is using.The table format defines the semantic of the colums and values.
		* @param 	uid				The UID of this table. If empty, it will be set to its index in this Fluid Characterization
		*/
		void pushBackTable(unsigned int modelIndex, const std::string & name, const std::string & tableFormatUid, const std::string & uid = "");
		
		/**
		 * Gets the table row count
		 *
		 * @param	modelIndex		Zero-based index of the model in this fluid characterization.
		 * @param 	tableIndex		Zero-based index of the table in a model of this fluid characterization.
		 * @returns	The table row count.
		 */
		unsigned int getTableRowCount(unsigned int modelIndex, unsigned int tableIndex) const;

		/**
		 * Gets the content of a row of a table.
		 *
		 * @param	modelIndex		Zero-based index of the model in this fluid characterization.
		 * @param 	tableIndex		Zero-based index of the table in a model of this fluid characterization.
		 * @param 	rowIndex		Zero-based index of the row of the table in a model of this fluid characterization.
		 * @returns	The content of a row of a table.
		 */
		std::string getTableRowContent(unsigned int modelIndex, unsigned int tableIndex, unsigned int rowIndex) const;
		
		/**
		* Pushes back a row in a table of a model without indicating if the data are either saturated or under-saturated.
		*
		* @param	modelIndex		Zero-based index of the model in this fluid characterization.
		* @param 	tableIndex		Zero-based index of the table in a model of this fluid characterization.
		* @param 	rowContent		The values representing the content of the row in the table.
		*/
		void pushBackTableRow(unsigned int modelIndex, unsigned int tableIndex, const std::vector<double> & rowContent);
		
		/**
		* Pushes back a row in a table of a model indicating if the data are either saturated or under-saturated.
		*
		* @param	modelIndex		Zero-based index of the model in this fluid characterization.
		* @param 	tableIndex		Zero-based index of the table in a model of this fluid characterization.
		* @param 	rowContent		The values representing the content of the row in the table.
		* @param	isSaturated		True if the data correspond to saturated data, false if the data correspond to undersaturated data
		*/
		void pushBackTableRow(unsigned int modelIndex, unsigned int tableIndex, const std::vector<double> & rowContent, bool isSaturated);

		/**
		* Pushes back an phase-unrelated parameter in a model.
		*
		* @param	modelIndex		Zero-based index of the model in this fluid characterization.
		* @param 	value			The value of the parameter
		* @param 	uom				The uom associated to the value of this parameter
		* @param	fluidProperty	The property kind of this value
		*/
		void pushBackParameter(unsigned int modelIndex, double value, gsoap_eml2_3::eml23__UnitOfMeasure uom, gsoap_eml2_3::prodml22__OutputFluidProperty fluidProperty);

		/**
		* Pushes back a phase related parameter in a model.
		*
		* @param	modelIndex		Zero-based index of the model in this fluid characterization.
		* @param 	value			The value of the parameter
		* @param 	uom				The uom associated to the value of this parameter
		* @param	fluidProperty	The property kind of this value
		* @param	phase			The pahse associated to the parameter
		*/
		void pushBackParameter(unsigned int modelIndex, double value, gsoap_eml2_3::eml23__UnitOfMeasure uom, gsoap_eml2_3::prodml22__OutputFluidProperty fluidProperty, gsoap_eml2_3::prodml22__ThermodynamicPhase phase);
	};
	
	/** The time series data object is intended for use in transferring time series of data, e.g. from a historian. 
	 * The Time Series data object describes a context free, time based series of measurement data for the 
	 * purpose of targeted exchanges between consumers and providers of data services. This is intended for 
	 * use in support of smart fields or high-frequency historian type interactions, not reporting. It provides a 
	 * flat view of the data and uses a set of keyword-value pairs to define the business identity of the series, 
	 * as described in the following generalized hierarchy.
	 */
	class TimeSeriesData : public COMMON_NS::AbstractObject
	{
	public:
		/**
		* The keyword value pairs are used to characterize the underlying nature of the values. The key value may provide part of the unique identity of an instance of a concept or it may characterize the underlying concept.
		* @param	keyword	One of this enumerated value
		*   - asset identifier :	A formatted URI identifier of the asset (facility) related to the value. This captures the 
		*							kind of asset as well as the unique identifier of the asset within a specified context 
		*							(the authority). The identifier may define a hierarchy of assets.
		*   - qualifier :			A qualifier of the meaning of the value. This is used to distinguish between variations 
		*							of an underlying meaning based on the method of creating the value (e.g., measured 
		*							versus simulated). The values associated with this keyword must be from the list 
		*							defined by type FlowQualifier. 
		*	- subqualifier :		A specialization of a qualifier. The values associated with this keyword must be from 
		*							the list defined by type FlowSubQualifier. 
		*	- product :				The type of product that is represented by the value. This is generally used with 
		*							things like volume or flow rate. It is generally meaningless for things like temperature 
		*							or pressure. The values associated with this keyword must be from the list defined by 
		*							type ReportingProduct. 
		*	- flow :				Defines the part of the flow network where the asset is located. This is most useful in 
		*							situations (e.g., reporting) where detailed knowledge of the network configuration is 
		*							not needed. Basically, this classifies different segments of the flow network based on 
		*							its purpose within the context of the whole network. The values associated with this 
		*							keyword must be from the list defined by type ReportingFlow.
		* @param	value	The string value associated to the keyword
		*/
		void pushBackKeywordValue(gsoap_eml2_3::prodml22__TimeSeriesKeyword keyword, const std::string & value);

		/**
		* Set the uom of the data of the time series.
		*
		* @param uom	The unit of measure taken from the standard Energistics
		 * 				units of measure catalog. Please check
		 * 				COMMON_NS::EnumStringMapper::getEnergisticsUnitOfMeasure in order
		 * 				to minimize the use of non standard unit of measure.
		*/
		void setUom(gsoap_resqml2_0_1::resqml20__ResqmlUom uom);

		/**
		* Set the measure class of the data of the time series.
		*
		* @param measureClass	The measure class to set.
		*/
		void setMeasureClass(gsoap_eml2_3::eml23__MeasureClass measureClass);

		/**
		* Push back a new value (i.e data) in the time series
		*
		* @param value	The value to push back.
		* @param value	(Optional) The time of the value to push back.
		*/
		void pushBackDoubleValue(double value, time_t timestamp = -1);

		/**
		* Push back a new value (i.e data) in the time series
		*
		* @param value	The value to push back.
		* @param value	The time of the value to push back.
		* @param value	The status of the value to push back.
		*/
		void pushBackDoubleValue(double value, time_t timestamp, gsoap_eml2_3::prodml22__ValueStatus status);

		/**
		* Push back a new value (i.e data) in the time series
		*
		* @param value	The value to push back.
		* @param value	(Optional) The time of the value to push back.
		*/
		void pushBackStringValue(const std::string & value, time_t timestamp = -1);

		/**
		 * Gets the unit of measure of the values of this time series as a string.
		 *
		 * @returns	The unit of measure of the values of this time series as a string. Returns empty string if no uom is stored.
		 */
		std::string getUomAsString() const;

		/**
		 * Gets the measure class of the values of this time series as a string.
		 *
		 * @returns	The measure class of the values of this time series as a string. Returns empty string if no measure class is stored.
		 */
		std::string getMeasureClassAsString() const;

		/**
		* Get the count of value in this time series
		*/
		unsigned int getValueCount() const;

		/**
		* Check if a value at a particular index is a double one.
		*
		* @param index	The index of the value in this timeseries
		* @return true if the value at this index is a double one
		*/
		bool isDoubleValue(unsigned int index) const;

		/**
		* Check if a value at a particular index is a string one.
		*
		* @param index	The index of the value in this timeseries
		* @return true if the value at this index is a string one
		*/
		bool isStringValue(unsigned int index) const;

		/**
		* Get a double value at a particular index.
		*
		* @param index	The index of the value in this timeseries
		* @return the double value at a particular index
		*/
		double getDoubleValue(unsigned int index) const;

		/**
		* Get a string value at a particular index.
		*
		* @param index	The index of the value in this timeseries
		* @return the string value at a particular index
		*/
		std::string getStringValue(unsigned int index) const;

		/**
		* Get the timestamp associated to a value at a particular index.
		*
		* @param index	The index of the value in this timeseries
		* @return the timestamp associated to a value at a particular index. -1 if no timesteamp is provided for this value.
		*/
		time_t getValueTimestamp(unsigned int index) const;

		/**
		* Check if a value at a particular index has a status.
		*
		* @param index	The index of the value in this timeseries
		* @return true if the value at this index has a status
		*/
		bool hasValueStatus(unsigned int index) const;

		/**
		* Get the status associated to a value at a particular index.
		*
		* @param index	The index of the value in this timeseries
		* @return the status associated to a value at a particular index.
		*/
		gsoap_eml2_3::prodml22__ValueStatus getValueStatus(unsigned int index) const;

		/**
		* Get the count of keywords in this time series
		*/
		unsigned int getKeywordCount() const;

		/**
		* Get a keyword at a particular index.
		*
		* @param index	The index of the keyword in this timeseries
		* @return the keyword at a particular index
		*/
		gsoap_eml2_3::prodml22__TimeSeriesKeyword getKeyword(unsigned int index) const;

		/**
		* Get the value of a keyword at a particular index.
		*
		* @param index	The index of the value in this timeseries
		* @return the value of a keyword at a particular index.
		*/
		std::string getKeywordValue(unsigned int index) const;
	};
}
