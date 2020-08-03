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
#include "../src/prodml2_1/FluidSystem.h"
#include "../src/prodml2_1/FluidCharacterization.h"
#include "../src/prodml2_1/TimeSeriesData.h"
%}

namespace std {
	%template(FluidSystemVector) vector<PRODML2_1_NS::FluidSystem*>;
	%template(FluidCharacterizationVector) vector<PRODML2_1_NS::FluidCharacterization*>;
	%template(TimeSeriesDataVector) vector<PRODML2_1_NS::TimeSeriesData*>;
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
	%nspace PRODML2_1_NS::FluidSystem;
	%nspace PRODML2_1_NS::FluidCharacterization;
	%nspace PRODML2_1_NS::TimeSeriesData;
#endif

namespace gsoap_eml2_2
{
	enum eml22__AmountOfSubstancePerAmountOfSubstanceUom {
		eml22__AmountOfSubstancePerAmountOfSubstanceUom___x0025 = 0,
		eml22__AmountOfSubstancePerAmountOfSubstanceUom___x0025_x005bmolar_x005d = 1,
		eml22__AmountOfSubstancePerAmountOfSubstanceUom__Euc = 2,
		eml22__AmountOfSubstancePerAmountOfSubstanceUom__mol_x002fmol = 3,
		eml22__AmountOfSubstancePerAmountOfSubstanceUom__nEuc = 4,
		eml22__AmountOfSubstancePerAmountOfSubstanceUom__ppk = 5,
		eml22__AmountOfSubstancePerAmountOfSubstanceUom__ppm = 6
	};

	enum eml22__ThermodynamicTemperatureUom {
		eml22__ThermodynamicTemperatureUom__K = 'K',
		eml22__ThermodynamicTemperatureUom__degC = 'L',
		eml22__ThermodynamicTemperatureUom__degF = 'M',
		eml22__ThermodynamicTemperatureUom__degR = 'N'
	};
	
	enum eml22__PressureUom {
		eml22__PressureUom__0_x002e01_x0020lbf_x002fft2 = 0,
		eml22__PressureUom__at = 1,
		eml22__PressureUom__atm = 2,
		eml22__PressureUom__bar = 3,
		eml22__PressureUom__cmH2O_x005b4degC_x005d = 4,
		eml22__PressureUom__cPa = 5,
		eml22__PressureUom__dPa = 6,
		eml22__PressureUom__dyne_x002fcm2 = 7,
		eml22__PressureUom__EPa = 8,
		eml22__PressureUom__fPa = 9,
		eml22__PressureUom__GPa = 10,
		eml22__PressureUom__hbar = 11,
		eml22__PressureUom__inH2O_x005b39degF_x005d = 12,
		eml22__PressureUom__inH2O_x005b60degF_x005d = 13,
		eml22__PressureUom__inHg_x005b32degF_x005d = 14,
		eml22__PressureUom__inHg_x005b60degF_x005d = 15,
		eml22__PressureUom__kgf_x002fcm2 = 16,
		eml22__PressureUom__kgf_x002fm2 = 17,
		eml22__PressureUom__kgf_x002fmm2 = 18,
		eml22__PressureUom__kN_x002fm2 = 19,
		eml22__PressureUom__kPa = 20,
		eml22__PressureUom__kpsi = 21,
		eml22__PressureUom__lbf_x002fft2 = 22,
		eml22__PressureUom__mbar = 23,
		eml22__PressureUom__mmHg_x005b0degC_x005d = 24,
		eml22__PressureUom__mPa = 25,
		eml22__PressureUom__MPa = 26,
		eml22__PressureUom__Mpsi = 27,
		eml22__PressureUom__N_x002fm2 = 28,
		eml22__PressureUom__N_x002fmm2 = 29,
		eml22__PressureUom__nPa = 30,
		eml22__PressureUom__Pa = 31,
		eml22__PressureUom__pPa = 32,
		eml22__PressureUom__psi = 33,
		eml22__PressureUom__tonf_x005bUK_x005d_x002fft2 = 34,
		eml22__PressureUom__tonf_x005bUS_x005d_x002fft2 = 35,
		eml22__PressureUom__tonf_x005bUS_x005d_x002fin2 = 36,
		eml22__PressureUom__torr = 37,
		eml22__PressureUom__TPa = 38,
		eml22__PressureUom__ubar = 39,
		eml22__PressureUom__umHg_x005b0degC_x005d = 40,
		eml22__PressureUom__uPa = 41,
		eml22__PressureUom__upsi = 42
	};
	
	enum prodml21__ReservoirFluidKind {
		prodml21__ReservoirFluidKind__black_x0020oil = 0,
		prodml21__ReservoirFluidKind__critical_x0020or_x0020near_x0020critical = 1,
		prodml21__ReservoirFluidKind__dry_x0020gas = 2,
		prodml21__ReservoirFluidKind__heavy_x0020oil = 3,
		prodml21__ReservoirFluidKind__wet_x0020gas_x0020or_x0020condensate = 4,
		prodml21__ReservoirFluidKind__volatile_x0020oil = 5,
		prodml21__ReservoirFluidKind__unknown = 6
	};
	
	enum eml22__VolumePerVolumeUom {
		eml22__VolumePerVolumeUom___x0025 = 0,
		eml22__VolumePerVolumeUom___x0025_x005bvol_x005d = 1,
		eml22__VolumePerVolumeUom__0_x002e001_x0020bbl_x002fft3 = 2,
		eml22__VolumePerVolumeUom__0_x002e001_x0020bbl_x002fm3 = 3,
		eml22__VolumePerVolumeUom__0_x002e001_x0020gal_x005bUK_x005d_x002fbbl = 4,
		eml22__VolumePerVolumeUom__0_x002e001_x0020gal_x005bUK_x005d_x002fgal_x005bUK_x005d = 5,
		eml22__VolumePerVolumeUom__0_x002e001_x0020gal_x005bUS_x005d_x002fbbl = 6,
		eml22__VolumePerVolumeUom__0_x002e001_x0020gal_x005bUS_x005d_x002fft3 = 7,
		eml22__VolumePerVolumeUom__0_x002e001_x0020gal_x005bUS_x005d_x002fgal_x005bUS_x005d = 8,
		eml22__VolumePerVolumeUom__0_x002e001_x0020pt_x005bUK_x005d_x002fbbl = 9,
		eml22__VolumePerVolumeUom__0_x002e01_x0020bbl_x002fbbl = 10,
		eml22__VolumePerVolumeUom__0_x002e1_x0020gal_x005bUS_x005d_x002fbbl = 11,
		eml22__VolumePerVolumeUom__0_x002e1_x0020L_x002fbbl = 12,
		eml22__VolumePerVolumeUom__0_x002e1_x0020pt_x005bUS_x005d_x002fbbl = 13,
		eml22__VolumePerVolumeUom__1000_x0020ft3_x002fbbl = 14,
		eml22__VolumePerVolumeUom__1000_x0020m3_x002fm3 = 15,
		eml22__VolumePerVolumeUom__1E_6_x0020acre_x002eft_x002fbbl = 16,
		eml22__VolumePerVolumeUom__1E_6_x0020bbl_x002fft3 = 17,
		eml22__VolumePerVolumeUom__1E_6_x0020bbl_x002fm3 = 18,
		eml22__VolumePerVolumeUom__1E6_x0020bbl_x002f_x0028acre_x002eft_x0029 = 19,
		eml22__VolumePerVolumeUom__1E6_x0020ft3_x002f_x0028acre_x002eft_x0029 = 20,
		eml22__VolumePerVolumeUom__1E6_x0020ft3_x002fbbl = 21,
		eml22__VolumePerVolumeUom__bbl_x002f_x0028acre_x002eft_x0029 = 22,
		eml22__VolumePerVolumeUom__bbl_x002fbbl = 23,
		eml22__VolumePerVolumeUom__bbl_x002fft3 = 24,
		eml22__VolumePerVolumeUom__bbl_x002fm3 = 25,
		eml22__VolumePerVolumeUom__cEuc = 26,
		eml22__VolumePerVolumeUom__cm3_x002fcm3 = 27,
		eml22__VolumePerVolumeUom__cm3_x002fL = 28,
		eml22__VolumePerVolumeUom__cm3_x002fm3 = 29,
		eml22__VolumePerVolumeUom__dm3_x002fm3 = 30,
		eml22__VolumePerVolumeUom__Euc = 31,
		eml22__VolumePerVolumeUom__ft3_x002fbbl = 32,
		eml22__VolumePerVolumeUom__ft3_x002fft3 = 33,
		eml22__VolumePerVolumeUom__gal_x005bUK_x005d_x002fft3 = 34,
		eml22__VolumePerVolumeUom__gal_x005bUS_x005d_x002fbbl = 35,
		eml22__VolumePerVolumeUom__gal_x005bUS_x005d_x002fft3 = 36,
		eml22__VolumePerVolumeUom__L_x002fm3 = 37,
		eml22__VolumePerVolumeUom__m3_x002f_x0028ha_x002em_x0029 = 38,
		eml22__VolumePerVolumeUom__m3_x002fbbl = 39,
		eml22__VolumePerVolumeUom__m3_x002fm3 = 40,
		eml22__VolumePerVolumeUom__mL_x002fgal_x005bUK_x005d = 41,
		eml22__VolumePerVolumeUom__mL_x002fgal_x005bUS_x005d = 42,
		eml22__VolumePerVolumeUom__mL_x002fmL = 43,
		eml22__VolumePerVolumeUom__ppk = 44,
		eml22__VolumePerVolumeUom__ppm = 45,
		eml22__VolumePerVolumeUom__ppm_x005bvol_x005d = 46
	};
	
	enum eml22__MassPerMassUom {
		eml22__MassPerMassUom___x0025 = 0,
		eml22__MassPerMassUom___x0025_x005bmass_x005d = 1,
		eml22__MassPerMassUom__Euc = 2,
		eml22__MassPerMassUom__g_x002fkg = 3,
		eml22__MassPerMassUom__g_x002ft = 4,
		eml22__MassPerMassUom__kg_x002fkg = 5,
		eml22__MassPerMassUom__kg_x002fsack_x005b94lbm_x005d = 6,
		eml22__MassPerMassUom__kg_x002ft = 7,
		eml22__MassPerMassUom__mg_x002fg = 8,
		eml22__MassPerMassUom__mg_x002fkg = 9,
		eml22__MassPerMassUom__ng_x002fg = 10,
		eml22__MassPerMassUom__ng_x002fmg = 11,
		eml22__MassPerMassUom__ppk = 12,
		eml22__MassPerMassUom__ppm = 13,
		eml22__MassPerMassUom__ppm_x005bmass_x005d = 14,
		eml22__MassPerMassUom__ug_x002fg = 15,
		eml22__MassPerMassUom__ug_x002fmg = 16
	};
	
	enum prodml21__PureComponentEnum {
		prodml21__PureComponentEnum__1_2_4_trimethylbenzene = 0,
		prodml21__PureComponentEnum__2_dimethylbutane = 1,
		prodml21__PureComponentEnum__3_dimethylbutane = 2,
		prodml21__PureComponentEnum__ar = 3,
		prodml21__PureComponentEnum__c1 = 4,
		prodml21__PureComponentEnum__c2 = 5,
		prodml21__PureComponentEnum__c3 = 6,
		prodml21__PureComponentEnum__co2 = 7,
		prodml21__PureComponentEnum__h2 = 8,
		prodml21__PureComponentEnum__h2o = 9,
		prodml21__PureComponentEnum__h2s = 10,
		prodml21__PureComponentEnum__he = 11,
		prodml21__PureComponentEnum__hg = 12,
		prodml21__PureComponentEnum__i_c4 = 13,
		prodml21__PureComponentEnum__i_c5 = 14,
		prodml21__PureComponentEnum__n2 = 15,
		prodml21__PureComponentEnum__n_c10 = 16,
		prodml21__PureComponentEnum__n_c4 = 17,
		prodml21__PureComponentEnum__n_c5 = 18,
		prodml21__PureComponentEnum__n_c6 = 19,
		prodml21__PureComponentEnum__n_c7 = 20,
		prodml21__PureComponentEnum__n_c8 = 21,
		prodml21__PureComponentEnum__n_c9 = 22,
		prodml21__PureComponentEnum__neo_c5 = 23,
		prodml21__PureComponentEnum__benzene = 24,
		prodml21__PureComponentEnum__2_methylpentane = 25,
		prodml21__PureComponentEnum__3_methylpentane = 26,
		prodml21__PureComponentEnum__2_methylhexane = 27,
		prodml21__PureComponentEnum__3_methylhexane = 28,
		prodml21__PureComponentEnum__2_methylheptane = 29,
		prodml21__PureComponentEnum__3_methylheptane = 30,
		prodml21__PureComponentEnum__cyclohexane = 31,
		prodml21__PureComponentEnum__ethylbenzene = 32,
		prodml21__PureComponentEnum__ethylcyclohexane = 33,
		prodml21__PureComponentEnum__methylcyclohexane = 34,
		prodml21__PureComponentEnum__methylcyclopentane = 35,
		prodml21__PureComponentEnum__toluene = 36,
		prodml21__PureComponentEnum__m_xylene = 37,
		prodml21__PureComponentEnum__o_xylene = 38,
		prodml21__PureComponentEnum__p_xylene = 39
	};

	enum eml22__MolecularWeightUom {
		eml22__MolecularWeightUom__g_x002fmol = 0,
		eml22__MolecularWeightUom__kg_x002fmol = 1,
		eml22__MolecularWeightUom__lbm_x002flbmol = 2
	};
	
	enum prodml21__PlusComponentEnum {
		prodml21__PlusComponentEnum__c10_x002b = 0,
		prodml21__PlusComponentEnum__c11_x002b = 1,
		prodml21__PlusComponentEnum__c12_x002b = 2,
		prodml21__PlusComponentEnum__c20_x002b = 3,
		prodml21__PlusComponentEnum__c25_x002b = 4,
		prodml21__PlusComponentEnum__c30_x002b = 5,
		prodml21__PlusComponentEnum__c36_x002b = 6,
		prodml21__PlusComponentEnum__c5_x002b = 7,
		prodml21__PlusComponentEnum__c6_x002b = 8,
		prodml21__PlusComponentEnum__c7_x002b = 9,
		prodml21__PlusComponentEnum__c8_x002b = 10,
		prodml21__PlusComponentEnum__c9_x002b = 11
	};
	
	enum eml22__APIGravityUom {
		eml22__APIGravityUom__dAPI = 0
	};
	
	enum eml22__EnergyPerMassUom {
		eml22__EnergyPerMassUom__Btu_x005bIT_x005d_x002flbm = 0,
		eml22__EnergyPerMassUom__cal_x005bth_x005d_x002fg = 1,
		eml22__EnergyPerMassUom__cal_x005bth_x005d_x002fkg = 2,
		eml22__EnergyPerMassUom__cal_x005bth_x005d_x002flbm = 3,
		eml22__EnergyPerMassUom__erg_x002fg = 4,
		eml22__EnergyPerMassUom__erg_x002fkg = 5,
		eml22__EnergyPerMassUom__hp_x002eh_x002flbm = 6,
		eml22__EnergyPerMassUom__J_x002fg = 7,
		eml22__EnergyPerMassUom__J_x002fkg = 8,
		eml22__EnergyPerMassUom__kcal_x005bth_x005d_x002fg = 9,
		eml22__EnergyPerMassUom__kcal_x005bth_x005d_x002fkg = 10,
		eml22__EnergyPerMassUom__kJ_x002fkg = 11,
		eml22__EnergyPerMassUom__kW_x002eh_x002fkg = 12,
		eml22__EnergyPerMassUom__lbf_x002eft_x002flbm = 13,
		eml22__EnergyPerMassUom__MJ_x002fkg = 14,
		eml22__EnergyPerMassUom__MW_x002eh_x002fkg = 15
	};
	
	enum eml22__EnergyPerVolumeUom {
		eml22__EnergyPerVolumeUom__Btu_x005bIT_x005d_x002fbbl = 0,
		eml22__EnergyPerVolumeUom__Btu_x005bIT_x005d_x002fft3 = 1,
		eml22__EnergyPerVolumeUom__Btu_x005bIT_x005d_x002fgal_x005bUK_x005d = 2,
		eml22__EnergyPerVolumeUom__Btu_x005bIT_x005d_x002fgal_x005bUS_x005d = 3,
		eml22__EnergyPerVolumeUom__cal_x005bth_x005d_x002fcm3 = 4,
		eml22__EnergyPerVolumeUom__cal_x005bth_x005d_x002fmL = 5,
		eml22__EnergyPerVolumeUom__cal_x005bth_x005d_x002fmm3 = 6,
		eml22__EnergyPerVolumeUom__erg_x002fcm3 = 7,
		eml22__EnergyPerVolumeUom__erg_x002fm3 = 8,
		eml22__EnergyPerVolumeUom__hp_x002eh_x002fbbl = 9,
		eml22__EnergyPerVolumeUom__J_x002fdm3 = 10,
		eml22__EnergyPerVolumeUom__J_x002fm3 = 11,
		eml22__EnergyPerVolumeUom__kcal_x005bth_x005d_x002fcm3 = 12,
		eml22__EnergyPerVolumeUom__kcal_x005bth_x005d_x002fm3 = 13,
		eml22__EnergyPerVolumeUom__kJ_x002fdm3 = 14,
		eml22__EnergyPerVolumeUom__kJ_x002fm3 = 15,
		eml22__EnergyPerVolumeUom__kW_x002eh_x002fdm3 = 16,
		eml22__EnergyPerVolumeUom__kW_x002eh_x002fm3 = 17,
		eml22__EnergyPerVolumeUom__lbf_x002eft_x002fbbl = 18,
		eml22__EnergyPerVolumeUom__lbf_x002eft_x002fgal_x005bUS_x005d = 19,
		eml22__EnergyPerVolumeUom__MJ_x002fm3 = 20,
		eml22__EnergyPerVolumeUom__MW_x002eh_x002fm3 = 21,
		eml22__EnergyPerVolumeUom__tonf_x005bUS_x005d_x002emi_x002fbbl = 22
	};
	
	enum prodml21__PseudoComponentEnum {
		prodml21__PseudoComponentEnum__c10 = 0,
		prodml21__PseudoComponentEnum__c11 = 1,
		prodml21__PseudoComponentEnum__c12 = 2,
		prodml21__PseudoComponentEnum__c13 = 3,
		prodml21__PseudoComponentEnum__c14 = 4,
		prodml21__PseudoComponentEnum__c15 = 5,
		prodml21__PseudoComponentEnum__c16 = 6,
		prodml21__PseudoComponentEnum__c17 = 7,
		prodml21__PseudoComponentEnum__c18 = 8,
		prodml21__PseudoComponentEnum__c19 = 9,
		prodml21__PseudoComponentEnum__c20 = 10,
		prodml21__PseudoComponentEnum__c21 = 11,
		prodml21__PseudoComponentEnum__c22 = 12,
		prodml21__PseudoComponentEnum__c23 = 13,
		prodml21__PseudoComponentEnum__c24 = 14,
		prodml21__PseudoComponentEnum__c25 = 15,
		prodml21__PseudoComponentEnum__c26 = 16,
		prodml21__PseudoComponentEnum__c27 = 17,
		prodml21__PseudoComponentEnum__c28 = 18,
		prodml21__PseudoComponentEnum__c29 = 19,
		prodml21__PseudoComponentEnum__c2_c4_x002bn2 = 20,
		prodml21__PseudoComponentEnum__c30 = 21,
		prodml21__PseudoComponentEnum__c31 = 22,
		prodml21__PseudoComponentEnum__c32 = 23,
		prodml21__PseudoComponentEnum__c33 = 24,
		prodml21__PseudoComponentEnum__c34 = 25,
		prodml21__PseudoComponentEnum__c35 = 26,
		prodml21__PseudoComponentEnum__c4 = 27,
		prodml21__PseudoComponentEnum__c5 = 28,
		prodml21__PseudoComponentEnum__c6 = 29,
		prodml21__PseudoComponentEnum__c7 = 30,
		prodml21__PseudoComponentEnum__c8 = 31,
		prodml21__PseudoComponentEnum__c9 = 32
	};
		
	enum prodml21__OutputFluidProperty {
		prodml21__OutputFluidProperty__Compressibility = 0,
		prodml21__OutputFluidProperty__Density = 1,
		prodml21__OutputFluidProperty__Derivative_x0020of_x0020Density_x0020w_x002er_x002et_x0020Pressure = 2,
		prodml21__OutputFluidProperty__Derivative_x0020of_x0020Density_x0020w_x002er_x002et_x0020Temperature = 3,
		prodml21__OutputFluidProperty__Enthalpy = 4,
		prodml21__OutputFluidProperty__Entropy = 5,
		prodml21__OutputFluidProperty__Expansion_x0020Factor = 6,
		prodml21__OutputFluidProperty__Formation_x0020Volume_x0020Factor = 7,
		prodml21__OutputFluidProperty__Gas_Oil_x0020Interfacial_x0020Tension = 8,
		prodml21__OutputFluidProperty__Gas_Water_x0020Interfacial_x0020Tension = 9,
		prodml21__OutputFluidProperty__Index = 10,
		prodml21__OutputFluidProperty__K_x0020value = 11,
		prodml21__OutputFluidProperty__Misc_x0020Bank_x0020Critical_x0020Solvent_x0020Saturation = 12,
		prodml21__OutputFluidProperty__Misc_x0020Bank_x0020Phase_x0020Density = 13,
		prodml21__OutputFluidProperty__Misc_x0020Bank_x0020Phase_x0020Viscosity = 14,
		prodml21__OutputFluidProperty__Miscibility_x0020Parameter_x0020_x0028Alpha_x0029 = 15,
		prodml21__OutputFluidProperty__Mixing_x0020Parameter_x0020Oil_Gas = 16,
		prodml21__OutputFluidProperty__Normalized_x0020Pseudo_x0020Pressure = 17,
		prodml21__OutputFluidProperty__Oil_Gas_x0020Ratio = 18,
		prodml21__OutputFluidProperty__Oil_Water_x0020Interfacial_x0020Tension = 19,
		prodml21__OutputFluidProperty__Parachor = 20,
		prodml21__OutputFluidProperty__Pressure = 21,
		prodml21__OutputFluidProperty__Pseudo_x0020Pressure = 22,
		prodml21__OutputFluidProperty__P_T_x0020Cross_x0020Term = 23,
		prodml21__OutputFluidProperty__Saturation_x0020Pressure = 24,
		prodml21__OutputFluidProperty__Solution_x0020GOR = 25,
		prodml21__OutputFluidProperty__Solvent_x0020Density = 26,
		prodml21__OutputFluidProperty__Specific_x0020Heat = 27,
		prodml21__OutputFluidProperty__Temperature = 28,
		prodml21__OutputFluidProperty__Thermal_x0020Conductivity = 29,
		prodml21__OutputFluidProperty__Viscosity = 30,
		prodml21__OutputFluidProperty__Viscosity_x0020Compressibility = 31,
		prodml21__OutputFluidProperty__Water_x0020vapor_x0020mass_x0020fraction_x0020in_x0020gas_x0020phase = 32,
		prodml21__OutputFluidProperty__Z_x0020Factor = 33
	};
	
	enum prodml21__TimeSeriesKeyword {
		prodml21__TimeSeriesKeyword__asset_x0020identifier = 0,
		prodml21__TimeSeriesKeyword__flow = 1,
		prodml21__TimeSeriesKeyword__product = 2,
		prodml21__TimeSeriesKeyword__qualifier = 3,
		prodml21__TimeSeriesKeyword__subqualifier = 4,
		prodml21__TimeSeriesKeyword__unknown = 5
	};
		
	enum eml22__MeasureClass {
		eml22__MeasureClass__absorbed_x0020dose = 0,
		eml22__MeasureClass__activity_x0020of_x0020radioactivity = 1,
		eml22__MeasureClass__amount_x0020of_x0020substance = 2,
		eml22__MeasureClass__amount_x0020of_x0020substance_x0020per_x0020amount_x0020of_x0020substance = 3,
		eml22__MeasureClass__amount_x0020of_x0020substance_x0020per_x0020area = 4,
		eml22__MeasureClass__amount_x0020of_x0020substance_x0020per_x0020time = 5,
		eml22__MeasureClass__amount_x0020of_x0020substance_x0020per_x0020time_x0020per_x0020area = 6,
		eml22__MeasureClass__amount_x0020of_x0020substance_x0020per_x0020volume = 7,
		eml22__MeasureClass__angle_x0020per_x0020length = 8,
		eml22__MeasureClass__angle_x0020per_x0020volume = 9,
		eml22__MeasureClass__angular_x0020acceleration = 10,
		eml22__MeasureClass__angular_x0020velocity = 11,
		eml22__MeasureClass__api_x0020gamma_x0020ray = 12,
		eml22__MeasureClass__api_x0020gravity = 13,
		eml22__MeasureClass__api_x0020neutron = 14,
		eml22__MeasureClass__area = 15,
		eml22__MeasureClass__area_x0020per_x0020amount_x0020of_x0020substance = 16,
		eml22__MeasureClass__area_x0020per_x0020area = 17,
		eml22__MeasureClass__area_x0020per_x0020count = 18,
		eml22__MeasureClass__area_x0020per_x0020mass = 19,
		eml22__MeasureClass__area_x0020per_x0020time = 20,
		eml22__MeasureClass__area_x0020per_x0020volume = 21,
		eml22__MeasureClass__attenuation_x0020per_x0020frequency_x0020interval = 22,
		eml22__MeasureClass__capacitance = 23,
		eml22__MeasureClass__cation_x0020exchange_x0020capacity = 24,
		eml22__MeasureClass__data_x0020transfer_x0020speed = 25,
		eml22__MeasureClass__diffusion_x0020coefficient = 26,
		eml22__MeasureClass__diffusive_x0020time_x0020of_x0020flight = 27,
		eml22__MeasureClass__digital_x0020storage = 28,
		eml22__MeasureClass__dimensionless = 29,
		eml22__MeasureClass__dipole_x0020moment = 30,
		eml22__MeasureClass__dose_x0020equivalent = 31,
		eml22__MeasureClass__dynamic_x0020viscosity = 32,
		eml22__MeasureClass__electric_x0020charge = 33,
		eml22__MeasureClass__electric_x0020charge_x0020per_x0020area = 34,
		eml22__MeasureClass__electric_x0020charge_x0020per_x0020mass = 35,
		eml22__MeasureClass__electric_x0020charge_x0020per_x0020volume = 36,
		eml22__MeasureClass__electric_x0020conductance = 37,
		eml22__MeasureClass__electric_x0020conductivity = 38,
		eml22__MeasureClass__electric_x0020current = 39,
		eml22__MeasureClass__electric_x0020current_x0020density = 40,
		eml22__MeasureClass__electric_x0020field_x0020strength = 41,
		eml22__MeasureClass__electric_x0020potential_x0020difference = 42,
		eml22__MeasureClass__electric_x0020resistance = 43,
		eml22__MeasureClass__electric_x0020resistance_x0020per_x0020length = 44,
		eml22__MeasureClass__electrical_x0020resistivity = 45,
		eml22__MeasureClass__electromagnetic_x0020moment = 46,
		eml22__MeasureClass__energy = 47,
		eml22__MeasureClass__energy_x0020length_x0020per_x0020area = 48,
		eml22__MeasureClass__energy_x0020length_x0020per_x0020time_x0020area_x0020temperature = 49,
		eml22__MeasureClass__energy_x0020per_x0020area = 50,
		eml22__MeasureClass__energy_x0020per_x0020length = 51,
		eml22__MeasureClass__energy_x0020per_x0020mass = 52,
		eml22__MeasureClass__energy_x0020per_x0020mass_x0020per_x0020time = 53,
		eml22__MeasureClass__energy_x0020per_x0020volume = 54,
		eml22__MeasureClass__force = 55,
		eml22__MeasureClass__force_x0020area = 56,
		eml22__MeasureClass__force_x0020length_x0020per_x0020length = 57,
		eml22__MeasureClass__force_x0020per_x0020force = 58,
		eml22__MeasureClass__force_x0020per_x0020length = 59,
		eml22__MeasureClass__force_x0020per_x0020volume = 60,
		eml22__MeasureClass__frequency = 61,
		eml22__MeasureClass__frequency_x0020interval = 62,
		eml22__MeasureClass__heat_x0020capacity = 63,
		eml22__MeasureClass__heat_x0020flow_x0020rate = 64,
		eml22__MeasureClass__heat_x0020transfer_x0020coefficient = 'A',
		eml22__MeasureClass__illuminance = 'B',
		eml22__MeasureClass__inductance = 'C',
		eml22__MeasureClass__isothermal_x0020compressibility = 'D',
		eml22__MeasureClass__kinematic_x0020viscosity = 'E',
		eml22__MeasureClass__length = 'F',
		eml22__MeasureClass__length_x0020per_x0020length = 'G',
		eml22__MeasureClass__length_x0020per_x0020mass = 'H',
		eml22__MeasureClass__length_x0020per_x0020pressure = 'I',
		eml22__MeasureClass__length_x0020per_x0020temperature = 'J',
		eml22__MeasureClass__length_x0020per_x0020time = 'K',
		eml22__MeasureClass__length_x0020per_x0020volume = 'L',
		eml22__MeasureClass__light_x0020exposure = 'M',
		eml22__MeasureClass__linear_x0020acceleration = 'N',
		eml22__MeasureClass__linear_x0020thermal_x0020expansion = 'O',
		eml22__MeasureClass__logarithmic_x0020power_x0020ratio = 'P',
		eml22__MeasureClass__logarithmic_x0020power_x0020ratio_x0020per_x0020length = 'Q',
		eml22__MeasureClass__luminance = 'R',
		eml22__MeasureClass__luminous_x0020efficacy = 'S',
		eml22__MeasureClass__luminous_x0020flux = 'T',
		eml22__MeasureClass__luminous_x0020intensity = 'U',
		eml22__MeasureClass__magnetic_x0020dipole_x0020moment = 'V',
		eml22__MeasureClass__magnetic_x0020field_x0020strength = 'W',
		eml22__MeasureClass__magnetic_x0020flux = 'X',
		eml22__MeasureClass__magnetic_x0020flux_x0020density = 'Y',
		eml22__MeasureClass__magnetic_x0020flux_x0020density_x0020per_x0020length = 'Z',
		eml22__MeasureClass__magnetic_x0020permeability = 91,
		eml22__MeasureClass__magnetic_x0020vector_x0020potential = 92,
		eml22__MeasureClass__mass = 93,
		eml22__MeasureClass__mass_x0020length = 94,
		eml22__MeasureClass__mass_x0020per_x0020area = 95,
		eml22__MeasureClass__mass_x0020per_x0020energy = 96,
		eml22__MeasureClass__mass_x0020per_x0020length = 'a',
		eml22__MeasureClass__mass_x0020per_x0020mass = 'b',
		eml22__MeasureClass__mass_x0020per_x0020time = 'c',
		eml22__MeasureClass__mass_x0020per_x0020time_x0020per_x0020area = 'd',
		eml22__MeasureClass__mass_x0020per_x0020time_x0020per_x0020length = 'e',
		eml22__MeasureClass__mass_x0020per_x0020volume = 'f',
		eml22__MeasureClass__mass_x0020per_x0020volume_x0020per_x0020length = 'g',
		eml22__MeasureClass__mass_x0020per_x0020volume_x0020per_x0020pressure = 'h',
		eml22__MeasureClass__mass_x0020per_x0020volume_x0020per_x0020temperature = 'i',
		eml22__MeasureClass__mobility = 'j',
		eml22__MeasureClass__molar_x0020energy = 'k',
		eml22__MeasureClass__molar_x0020heat_x0020capacity = 'l',
		eml22__MeasureClass__molar_x0020volume = 'm',
		eml22__MeasureClass__molecular_x0020weight = 'n',
		eml22__MeasureClass__moment_x0020of_x0020force = 'o',
		eml22__MeasureClass__moment_x0020of_x0020inertia = 'p',
		eml22__MeasureClass__momentum = 'q',
		eml22__MeasureClass__normalized_x0020power = 'r',
		eml22__MeasureClass__permeability_x0020length = 's',
		eml22__MeasureClass__permeability_x0020rock = 't',
		eml22__MeasureClass__permittivity = 'u',
		eml22__MeasureClass__plane_x0020angle = 'v',
		eml22__MeasureClass__potential_x0020difference_x0020per_x0020power_x0020drop = 'w',
		eml22__MeasureClass__power = 'x',
		eml22__MeasureClass__power_x0020per_x0020area = 'y',
		eml22__MeasureClass__power_x0020per_x0020power = 'z',
		eml22__MeasureClass__power_x0020per_x0020volume = 123,
		eml22__MeasureClass__pressure = 124,
		eml22__MeasureClass__pressure_x0020per_x0020pressure = 125,
		eml22__MeasureClass__pressure_x0020per_x0020time = 126,
		eml22__MeasureClass__pressure_x0020per_x0020volume = 127,
		eml22__MeasureClass__pressure_x0020squared = 128,
		eml22__MeasureClass__pressure_x0020squared_x0020per_x0020force_x0020time_x0020per_x0020area = 129,
		eml22__MeasureClass__pressure_x0020time_x0020per_x0020volume = 130,
		eml22__MeasureClass__quantity_x0020of_x0020light = 131,
		eml22__MeasureClass__radiance = 132,
		eml22__MeasureClass__radiant_x0020intensity = 133,
		eml22__MeasureClass__reciprocal_x0020area = 134,
		eml22__MeasureClass__reciprocal_x0020electric_x0020potential_x0020difference = 135,
		eml22__MeasureClass__reciprocal_x0020force = 136,
		eml22__MeasureClass__reciprocal_x0020length = 137,
		eml22__MeasureClass__reciprocal_x0020mass = 138,
		eml22__MeasureClass__reciprocal_x0020mass_x0020time = 139,
		eml22__MeasureClass__reciprocal_x0020pressure = 140,
		eml22__MeasureClass__reciprocal_x0020time = 141,
		eml22__MeasureClass__reciprocal_x0020volume = 142,
		eml22__MeasureClass__reluctance = 143,
		eml22__MeasureClass__second_x0020moment_x0020of_x0020area = 144,
		eml22__MeasureClass__signaling_x0020event_x0020per_x0020time = 145,
		eml22__MeasureClass__solid_x0020angle = 146,
		eml22__MeasureClass__specific_x0020heat_x0020capacity = 147,
		eml22__MeasureClass__temperature_x0020interval = 148,
		eml22__MeasureClass__temperature_x0020interval_x0020per_x0020length = 149,
		eml22__MeasureClass__temperature_x0020interval_x0020per_x0020pressure = 150,
		eml22__MeasureClass__temperature_x0020interval_x0020per_x0020time = 151,
		eml22__MeasureClass__thermal_x0020conductance = 152,
		eml22__MeasureClass__thermal_x0020conductivity = 153,
		eml22__MeasureClass__thermal_x0020diffusivity = 154,
		eml22__MeasureClass__thermal_x0020insulance = 155,
		eml22__MeasureClass__thermal_x0020resistance = 156,
		eml22__MeasureClass__thermodynamic_x0020temperature = 157,
		eml22__MeasureClass__thermodynamic_x0020temperature_x0020per_x0020thermodynamic_x0020temperature = 158,
		eml22__MeasureClass__time = 159,
		eml22__MeasureClass__time_x0020per_x0020length = 160,
		eml22__MeasureClass__time_x0020per_x0020mass = 161,
		eml22__MeasureClass__time_x0020per_x0020time = 162,
		eml22__MeasureClass__time_x0020per_x0020volume = 163,
		eml22__MeasureClass__vertical_x0020coordinate = 164,
		eml22__MeasureClass__volume = 165,
		eml22__MeasureClass__volume_x0020flow_x0020rate_x0020per_x0020volume_x0020flow_x0020rate = 166,
		eml22__MeasureClass__volume_x0020per_x0020area = 167,
		eml22__MeasureClass__volume_x0020per_x0020length = 168,
		eml22__MeasureClass__volume_x0020per_x0020mass = 169,
		eml22__MeasureClass__volume_x0020per_x0020pressure = 170,
		eml22__MeasureClass__volume_x0020per_x0020rotation = 171,
		eml22__MeasureClass__volume_x0020per_x0020time = 172,
		eml22__MeasureClass__volume_x0020per_x0020time_x0020length = 173,
		eml22__MeasureClass__volume_x0020per_x0020time_x0020per_x0020area = 174,
		eml22__MeasureClass__volume_x0020per_x0020time_x0020per_x0020length = 175,
		eml22__MeasureClass__volume_x0020per_x0020time_x0020per_x0020pressure = 176,
		eml22__MeasureClass__volume_x0020per_x0020time_x0020per_x0020pressure_x0020length = 177,
		eml22__MeasureClass__volume_x0020per_x0020time_x0020per_x0020time = 178,
		eml22__MeasureClass__volume_x0020per_x0020time_x0020per_x0020volume = 179,
		eml22__MeasureClass__volume_x0020per_x0020volume = 180,
		eml22__MeasureClass__volumetric_x0020heat_x0020transfer_x0020coefficient = 181,
		eml22__MeasureClass__volumetric_x0020thermal_x0020expansion = 182,
		eml22__MeasureClass__unitless = 183
	};
	
	enum prodml21__ValueStatus {
		prodml21__ValueStatus__access_x0020denied = 0,
		prodml21__ValueStatus__bad = 1,
		prodml21__ValueStatus__bad_x0020calibration = 2,
		prodml21__ValueStatus__calculation_x0020failure = 3,
		prodml21__ValueStatus__comm_x0020failure = 4,
		prodml21__ValueStatus__device_x0020failure = 5,
		prodml21__ValueStatus__frozen = 6,
		prodml21__ValueStatus__not_x0020available = 7,
		prodml21__ValueStatus__overflow = 8,
		prodml21__ValueStatus__questionable = 9,
		prodml21__ValueStatus__range_x0020limit = 10,
		prodml21__ValueStatus__sensor_x0020failure = 11,
		prodml21__ValueStatus__substituted = 12,
		prodml21__ValueStatus__timeout = 13
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
	GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(vectorName, MassFraction, gsoap_eml2_2::eml22__MassPerMassUom)\
	GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(vectorName, MoleFraction, gsoap_eml2_2::eml22__AmountOfSubstancePerAmountOfSubstanceUom)

namespace PRODML2_1_NS
{
	%nodefaultctor; // Disable creation of default constructors

	class FluidSystem : public COMMON_NS::AbstractObject
	{
	public:
		gsoap_eml2_2::prodml21__ReservoirFluidKind getReservoirFluidKind() const;
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
		void setStandardConditions(double temperatureValue, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom temperatureUom,
			double pressureValue, gsoap_eml2_2::eml22__PressureUom pressureUom);

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
		gsoap_eml2_2::eml22__ThermodynamicTemperatureUom getStandardTemperatureUom() const;

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
		gsoap_eml2_2::eml22__PressureUom getStandardPressureUom() const;
		
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
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(FormationWater, Salinity, gsoap_eml2_2::eml22__MassPerMassUom)
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
		void pushBackPureFluidComponent(const std::string & uid, gsoap_eml2_2::prodml21__PureComponentEnum kind, bool hydrocarbonFlag);
		GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(PureFluidComponent)
		GETTER_FLUID_COMPONENT_ATTRIBUTE(PureFluidComponent, Kind, std::string)
		GETTER_FLUID_COMPONENT_ATTRIBUTE(PureFluidComponent, HydrocarbonFlag, bool)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PureFluidComponent, MolecularWeight, gsoap_eml2_2::eml22__MolecularWeightUom)

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
		void pushBackPlusFluidComponent(const std::string & uid, gsoap_eml2_2::prodml21__PlusComponentEnum kind);
		GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(PlusFluidComponent)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(PlusFluidComponent, SpecificGravity, double)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(PlusFluidComponent, StartingCarbonNumber, ULONG64)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PlusFluidComponent, StartingBoilingPoint, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PlusFluidComponent, AvgDensity, std::string)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PlusFluidComponent, AvgMolecularWeight, gsoap_eml2_2::eml22__MolecularWeightUom)

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
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, APIGravity, gsoap_eml2_2::eml22__APIGravityUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, MolecularWeight, gsoap_eml2_2::eml22__MolecularWeightUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, GrossEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, NetEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, GrossEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, NetEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom)

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
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, MolecularWeight, gsoap_eml2_2::eml22__MolecularWeightUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, GrossEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, NetEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, GrossEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, NetEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom)

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
		void pushBackPseudoFluidComponent(const std::string & uid, gsoap_eml2_2::prodml21__PseudoComponentEnum kind);
		GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(PseudoFluidComponent)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(PseudoFluidComponent, SpecificGravity, double)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(PseudoFluidComponent, StartingCarbonNumber, ULONG64)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(PseudoFluidComponent, EndingCarbonNumber, ULONG64)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, StartingBoilingPoint, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, EndingBoilingPoint, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, AvgBoilingPoint, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, AvgDensity, std::string)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, AvgMolecularWeight, gsoap_eml2_2::eml22__MolecularWeightUom)
		
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
		
		GETTER_SETTER_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_2::prodml21__FluidCharacterization, gsoapProxy2_2, FluidCharacterizationModel, Name, std::string)
		GETTER_SETTER_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_2::prodml21__FluidCharacterization, gsoapProxy2_2, FluidCharacterizationModel, Remark, std::string)
		GETTER_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_2::prodml21__FluidCharacterization, gsoapProxy2_2, FluidCharacterizationModel, ReferenceTemperature, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)
		GETTER_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_2::prodml21__FluidCharacterization, gsoapProxy2_2, FluidCharacterizationModel, ReferenceStockTankTemperature, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)
		
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
		void pushBackTableFormatColumn(unsigned int tableFormatIndex, const std::string & uom, gsoap_eml2_2::prodml21__OutputFluidProperty fluidProperty);
			
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
		* Pushes back a row in a table of a model
		*
		* @param	modelIndex		Zero-based index of the model in this fluid characterization.
		* @param 	tableIndex		Zero-based index of the table in a model of this fluid characterization.
		* @param 	rowContent		The string containing the content of the row in the table .
		*/
		void pushBackTableRow(unsigned int modelIndex, unsigned int tableIndex, const std::string & rowContent);
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
		void pushBackKeywordValue(gsoap_eml2_2::prodml21__TimeSeriesKeyword keyword, const std::string & value);

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
		void setMeasureClass(gsoap_eml2_2::eml22__MeasureClass measureClass);

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
		void pushBackDoubleValue(double value, time_t timestamp, gsoap_eml2_2::prodml21__ValueStatus status);

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
		gsoap_eml2_2::prodml21__ValueStatus getValueStatus(unsigned int index) const;

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
		gsoap_eml2_2::prodml21__TimeSeriesKeyword getKeyword(unsigned int index) const;

		/**
		* Get the value of a keyword at a particular index.
		*
		* @param index	The index of the value in this timeseries
		* @return the value of a keyword at a particular index.
		*/
		std::string getKeywordValue(unsigned int index) const;
	};
}
