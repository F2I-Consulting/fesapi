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
#include "../src/resqml2/AbstractColorMap.h"
#include "../src/resqml2/CmpLineFeature.h"
#include "../src/resqml2/ContinuousColorMap.h"
#include "../src/resqml2/DiscreteColorMap.h"
#include "../src/resqml2/FluidBoundaryInterpretation.h"
#include "../src/resqml2/RockFluidUnitInterpretation.h"
#include "../src/resqml2/SeismicWellboreFrameRepresentation.h"
#include "../src/resqml2/ShotPointLineFeature.h"
#include "../src/resqml2/StratigraphicColumn.h"
#include "../src/resqml2/StratigraphicColumnRankInterpretation.h"
#include "../src/resqml2/UnstructuredGridRepresentation.h"
%}

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace RESQML2_NS::AbstractColorMap;	
	%nspace RESQML2_NS::AbstractColumnLayerGridRepresentation;
	%nspace RESQML2_NS::AbstractFeature;
	%nspace RESQML2_NS::AbstractFeatureInterpretation;
	%nspace RESQML2_NS::AbstractGridRepresentation;
	%nspace RESQML2_NS::AbstractIjkGridRepresentation;
	%nspace RESQML2_NS::AbstractOrganizationInterpretation;
	%nspace RESQML2_NS::AbstractProperty;
	%nspace RESQML2_NS::AbstractRepresentation;
	%nspace RESQML2_NS::AbstractSeismicLineFeature;
	%nspace RESQML2_NS::AbstractStratigraphicOrganizationInterpretation;
	%nspace RESQML2_NS::AbstractSurfaceFrameworkRepresentation;
	%nspace RESQML2_NS::AbstractSurfaceRepresentation;
	%nspace RESQML2_NS::AbstractTechnicalFeature;
	%nspace RESQML2_NS::AbstractValuesProperty;
	%nspace RESQML2_NS::BlockedWellboreRepresentation;
	%nspace RESQML2_NS::BoundaryFeature;
	%nspace RESQML2_NS::BoundaryFeatureInterpretation;
	%nspace RESQML2_NS::CategoricalProperty;
	%nspace RESQML2_NS::CmpLineFeature;
	%nspace RESQML2_NS::CommentProperty;
	%nspace RESQML2_NS::ContinuousColorMap;
	%nspace RESQML2_NS::ContinuousProperty;
	%nspace RESQML2_NS::CulturalFeature;
	%nspace RESQML2_NS::DiscreteColorMap;
	%nspace RESQML2_NS::DiscreteProperty;
	%nspace RESQML2_NS::DoubleTableLookup;
	%nspace RESQML2_NS::EarthModelInterpretation;
	%nspace RESQML2_NS::FaultInterpretation;
	%nspace RESQML2_NS::FluidBoundaryInterpretation;
	%nspace RESQML2_NS::GenericFeatureInterpretation;
	%nspace RESQML2_NS::GeobodyBoundaryInterpretation;
	%nspace RESQML2_NS::GeobodyInterpretation;
	%nspace RESQML2_NS::Grid2dRepresentation;
	%nspace RESQML2_NS::GridConnectionSetRepresentation;
	%nspace RESQML2_NS::HorizonInterpretation;
	%nspace RESQML2_NS::IjkGridExplicitRepresentation;
	%nspace RESQML2_NS::IjkGridLatticeRepresentation;
	%nspace RESQML2_NS::IjkGridNoGeometryRepresentation;
	%nspace RESQML2_NS::IjkGridParametricRepresentation;
	%nspace RESQML2_NS::MdDatum;
	%nspace RESQML2_NS::Model;
	%nspace RESQML2_NS::NonSealedSurfaceFrameworkRepresentation;
	%nspace RESQML2_NS::PlaneSetRepresentation;
	%nspace RESQML2_NS::PointSetRepresentation;
	%nspace RESQML2_NS::PointsProperty;
	%nspace RESQML2_NS::PolylineRepresentation;
	%nspace RESQML2_NS::PolylineSetRepresentation;
	%nspace RESQML2_NS::RepresentationSetRepresentation;
	%nspace RESQML2_NS::RockFluidOrganizationInterpretation;
	%nspace RESQML2_NS::RockFluidUnitInterpretation;
	%nspace RESQML2_NS::RockVolumeFeature;
	%nspace RESQML2_NS::SealedSurfaceFrameworkRepresentation;
	%nspace RESQML2_NS::SealedVolumeFrameworkRepresentation;
	%nspace RESQML2_NS::SeismicLatticeFeature;
	%nspace RESQML2_NS::SeismicLineSetFeature;
	%nspace RESQML2_NS::SeismicWellboreFrameRepresentation;
	%nspace RESQML2_NS::ShotPointLineFeature;
	%nspace RESQML2_NS::StratigraphicColumn;
	%nspace RESQML2_NS::StratigraphicColumnRankInterpretation;
	%nspace RESQML2_NS::StratigraphicOccurrenceInterpretation;
	%nspace RESQML2_NS::StratigraphicUnitInterpretation;
	%nspace RESQML2_NS::StreamlinesFeature;
	%nspace RESQML2_NS::StreamlinesRepresentation;
	%nspace RESQML2_NS::StringTableLookup;
	%nspace RESQML2_NS::StructuralOrganizationInterpretation;
	%nspace RESQML2_NS::SubRepresentation;
	%nspace RESQML2_NS::TriangulatedSetRepresentation;
	%nspace RESQML2_NS::UnstructuredGridRepresentation;
	%nspace RESQML2_NS::WellboreFeature;
	%nspace RESQML2_NS::WellboreFrameRepresentation;
	%nspace RESQML2_NS::WellboreInterpretation;
	%nspace RESQML2_NS::WellboreMarker;
	%nspace RESQML2_NS::WellboreMarkerFrameRepresentation;
	%nspace RESQML2_NS::WellboreTrajectoryRepresentation;
#endif

namespace gsoap_resqml2_0_1
{	
	enum class resqml20__ResqmlUom {
		A =
#ifdef SWIGPYTHON
(int)
#endif
			'A',
		a =
#ifdef SWIGPYTHON
(int)
#endif
			'a',
		b =
#ifdef SWIGPYTHON
(int)
#endif
			'b',
		B =
#ifdef SWIGPYTHON
(int)
#endif
			'B',
		C =
#ifdef SWIGPYTHON
(int)
#endif
			'C',
		d =
#ifdef SWIGPYTHON
(int)
#endif
			'd',
		D =
#ifdef SWIGPYTHON
(int)
#endif
			'D',
		F =
#ifdef SWIGPYTHON
(int)
#endif
			'F',
		g =
#ifdef SWIGPYTHON
(int)
#endif
			'g',
		H =
#ifdef SWIGPYTHON
(int)
#endif
			'H',
		h =
#ifdef SWIGPYTHON
(int)
#endif
			'h',
		J =
#ifdef SWIGPYTHON
(int)
#endif
			'J',
		K =
#ifdef SWIGPYTHON
(int)
#endif
			'K',
		L =
#ifdef SWIGPYTHON
(int)
#endif
			'L',
		m =
#ifdef SWIGPYTHON
(int)
#endif
			'm',
		N =
#ifdef SWIGPYTHON
(int)
#endif
			'N',
		O =
#ifdef SWIGPYTHON
(int)
#endif
			'O',
		P =
#ifdef SWIGPYTHON
(int)
#endif
			'P',
		S =
#ifdef SWIGPYTHON
(int)
#endif
			'S',
		s =
#ifdef SWIGPYTHON
(int)
#endif
			's',
		t =
#ifdef SWIGPYTHON
(int)
#endif
			't',
		T =
#ifdef SWIGPYTHON
(int)
#endif
			'T',
		V =
#ifdef SWIGPYTHON
(int)
#endif
			'V',
		W =
#ifdef SWIGPYTHON
(int)
#endif
			'W',
		_x0025 =
#ifdef SWIGPYTHON
(int)
#endif
			'u',
		_x0025_x005barea_x005d =
#ifdef SWIGPYTHON
(int)
#endif
			'v',
		_x0025_x005bmass_x005d =
#ifdef SWIGPYTHON
(int)
#endif
			'w',
		_x0025_x005bmolar_x005d =
#ifdef SWIGPYTHON
(int)
#endif
			'x',
		_x0025_x005bvol_x005d =
#ifdef SWIGPYTHON
(int)
#endif
			'y',
		_x0028bbl_x002fd_x0029_x002f_x0028bbl_x002fd_x0029 =
#ifdef SWIGPYTHON
(int)
#endif
			'z',
		_x0028m3_x002fd_x0029_x002f_x0028m3_x002fd_x0029 = 123,
		_x0028m3_x002fs_x0029_x002f_x0028m3_x002fs_x0029 = 124,
		_0_x002e001_x0020bbl_x002fft3 = 125,
		_0_x002e001_x0020bbl_x002fm3 = 126,
		_0_x002e001_x0020d_x002fft3 = 127,
		_0_x002e001_x0020gal_x005bUK_x005d_x002fbbl = 128,
		_0_x002e001_x0020gal_x005bUK_x005d_x002fgal_x005bUK_x005d = 129,
		_0_x002e001_x0020gal_x005bUS_x005d_x002fbbl = 130,
		_0_x002e001_x0020gal_x005bUS_x005d_x002fft3 = 131,
		_0_x002e001_x0020gal_x005bUS_x005d_x002fgal_x005bUS_x005d = 132,
		_0_x002e001_x0020h_x002fft = 133,
		_0_x002e001_x0020kPa2_x002fcP = 134,
		_0_x002e001_x0020lbm_x002fbbl = 135,
		_0_x002e001_x0020lbm_x002fgal_x005bUK_x005d = 136,
		_0_x002e001_x0020lbm_x002fgal_x005bUS_x005d = 137,
		_0_x002e001_x0020psi_x002fft = 138,
		_0_x002e001_x0020pt_x005bUK_x005d_x002fbbl = 139,
		_0_x002e001_x0020seca = 140,
		_0_x002e01_x0020bbl_x002fbbl = 141,
		_0_x002e01_x0020dega_x002fft = 142,
		_0_x002e01_x0020degF_x002fft = 143,
		_0_x002e01_x0020dm3_x002fkm = 144,
		_0_x002e01_x0020ft_x002fft = 145,
		_0_x002e01_x0020grain_x002fft3 = 146,
		_0_x002e01_x0020L_x002fkg = 147,
		_0_x002e01_x0020L_x002fkm = 148,
		_0_x002e01_x0020lbf_x002fft = 149,
		_0_x002e01_x0020lbf_x002fft2 = 150,
		_0_x002e01_x0020lbm_x002fft2 = 151,
		_0_x002e01_x0020psi_x002fft = 152,
		_0_x002e1_x0020ft = 153,
		_0_x002e1_x0020ft_x005bUS_x005d = 154,
		_0_x002e1_x0020gal_x005bUS_x005d_x002fbbl = 155,
		_0_x002e1_x0020in = 156,
		_0_x002e1_x0020L_x002fbbl = 157,
		_0_x002e1_x0020lbm_x002fbbl = 158,
		_0_x002e1_x0020pt_x005bUS_x005d_x002fbbl = 159,
		_0_x002e1_x0020yd = 160,
		_1_x002f_x0028kg_x002es_x0029 = 161,
		_1_x002f16_x0020in = 162,
		_1_x002f2_x0020ft = 163,
		_1_x002f2_x0020ms = 164,
		_1_x002f30_x0020cm3_x002fmin = 165,
		_1_x002f30_x0020dega_x002fft = 166,
		_1_x002f30_x0020dega_x002fm = 167,
		_1_x002f30_x0020lbf_x002fm = 168,
		_1_x002f30_x0020m_x002fm = 169,
		_1_x002f30_x0020N_x002fm = 170,
		_1_x002f32_x0020in = 171,
		_1_x002f64_x0020in = 172,
		_1_x002fa = 173,
		_1_x002fangstrom = 174,
		_1_x002fbar = 175,
		_1_x002fbbl = 176,
		_1_x002fcm = 177,
		_1_x002fd = 178,
		_1_x002fdegC = 179,
		_1_x002fdegF = 180,
		_1_x002fdegR = 181,
		_1_x002fft = 182,
		_1_x002fft2 = 183,
		_1_x002fft3 = 184,
		_1_x002fg = 185,
		_1_x002fgal_x005bUK_x005d = 186,
		_1_x002fgal_x005bUS_x005d = 187,
		_1_x002fH = 188,
		_1_x002fh = 189,
		_1_x002fin = 190,
		_1_x002fK = 191,
		_1_x002fkg = 192,
		_1_x002fkm2 = 193,
		_1_x002fkPa = 194,
		_1_x002fL = 195,
		_1_x002flbf = 196,
		_1_x002flbm = 197,
		_1_x002fm = 198,
		_1_x002fm2 = 199,
		_1_x002fm3 = 200,
		_1_x002fmi = 201,
		_1_x002fmi2 = 202,
		_1_x002fmin = 203,
		_1_x002fmm = 204,
		_1_x002fms = 205,
		_1_x002fN = 206,
		_1_x002fnm = 207,
		_1_x002fPa = 208,
		_1_x002fpPa = 209,
		_1_x002fpsi = 210,
		_1_x002fs = 211,
		_1_x002fupsi = 212,
		_1_x002fus = 213,
		_1_x002fuV = 214,
		_1_x002fV = 215,
		_1_x002fwk = 216,
		_1_x002fyd = 217,
		_10_x0020ft = 218,
		_10_x0020in = 219,
		_10_x0020km = 220,
		_10_x0020kN = 221,
		_10_x0020Mg_x002fm3 = 222,
		_100_x0020ft = 223,
		_100_x0020ka_x005bt_x005d = 224,
		_100_x0020km = 225,
		_1000_x0020bbl = 226,
		_1000_x0020bbl_x002eft_x002fd = 227,
		_1000_x0020bbl_x002fd = 228,
		_1000_x0020ft = 229,
		_1000_x0020ft_x002fh = 230,
		_1000_x0020ft_x002fs = 231,
		_1000_x0020ft3 = 232,
		_1000_x0020ft3_x002f_x0028d_x002eft_x0029 = 233,
		_1000_x0020ft3_x002f_x0028psi_x002ed_x0029 = 234,
		_1000_x0020ft3_x002fbbl = 235,
		_1000_x0020ft3_x002fd = 236,
		_1000_x0020gal_x005bUK_x005d = 237,
		_1000_x0020gal_x005bUS_x005d = 238,
		_1000_x0020lbf_x002eft = 239,
		_1000_x0020m3 = 240,
		_1000_x0020m3_x002f_x0028d_x002em_x0029 = 241,
		_1000_x0020m3_x002f_x0028h_x002em_x0029 = 242,
		_1000_x0020m3_x002fd = 243,
		_1000_x0020m3_x002fh = 244,
		_1000_x0020m3_x002fm3 = 245,
		_1000_x0020m4_x002fd = 246,
		_1E_6_x0020acre_x002eft_x002fbbl = 247,
		_1E_6_x0020bbl_x002fft3 = 248,
		_1E_6_x0020bbl_x002fm3 = 249,
		_1E_6_x0020gal_x005bUS_x005d = 250,
		_1E_6_x0020m3_x002f_x0028m3_x002edegC_x0029 = 251,
		_1E_6_x0020m3_x002f_x0028m3_x002edegF_x0029 = 252,
		_1E_9_x00201_x002fft = 253,
		_1E12_x0020ft3 = 254,
		_1E6_x0020_x0028ft3_x002fd_x0029_x002f_x0028bbl_x002fd_x0029 = 255,
		_1E6_x0020bbl = 256,
		_1E6_x0020bbl_x002f_x0028acre_x002eft_x0029 = 257,
		_1E6_x0020bbl_x002facre = 258,
		_1E6_x0020bbl_x002fd = 259,
		_1E6_x0020Btu_x005bIT_x005d = 260,
		_1E6_x0020Btu_x005bIT_x005d_x002fh = 261,
		_1E6_x0020ft3 = 262,
		_1E6_x0020ft3_x002f_x0028acre_x002eft_x0029 = 263,
		_1E6_x0020ft3_x002fbbl = 264,
		_1E6_x0020ft3_x002fd = 265,
		_1E6_x0020lbm_x002fa = 266,
		_1E6_x0020m3 = 267,
		_1E6_x0020m3_x002fd = 268,
		_1E9_x0020bbl = 269,
		_1E9_x0020ft3 = 270,
		_30_x0020ft = 271,
		_30_x0020m = 272,
		A_x002eh = 273,
		A_x002em2 = 274,
		A_x002es = 275,
		A_x002es_x002fkg = 276,
		A_x002es_x002fm3 = 277,
		A_x002fcm2 = 278,
		A_x002fft2 = 279,
		A_x002fm = 280,
		A_x002fm2 = 281,
		A_x002fmm = 282,
		A_x002fmm2 = 283,
		a_x005bt_x005d = 284,
		acre = 285,
		acre_x002eft = 286,
		ag = 287,
		aJ = 288,
		angstrom = 289,
		at = 290,
		atm = 291,
		atm_x002fft = 292,
		atm_x002fh = 293,
		atm_x002fhm = 294,
		atm_x002fm = 295,
		B_x002eW = 296,
		b_x002fcm3 = 297,
		B_x002fm = 298,
		B_x002fO = 299,
		bar = 300,
		bar_x002fh = 301,
		bar_x002fkm = 302,
		bar_x002fm = 303,
		bar2 = 304,
		bar2_x002fcP = 305,
		bbl = 306,
		bbl_x002f_x0028acre_x002eft_x0029 = 307,
		bbl_x002f_x0028d_x002eacre_x002eft_x0029 = 308,
		bbl_x002f_x0028d_x002eft_x0029 = 309,
		bbl_x002f_x0028ft_x002epsi_x002ed_x0029 = 310,
		bbl_x002f_x0028kPa_x002ed_x0029 = 311,
		bbl_x002f_x0028psi_x002ed_x0029 = 312,
		bbl_x002facre = 313,
		bbl_x002fbbl = 314,
		bbl_x002fd = 315,
		bbl_x002fd2 = 316,
		bbl_x002fft = 317,
		bbl_x002fft3 = 318,
		bbl_x002fh = 319,
		bbl_x002fh2 = 320,
		bbl_x002fin = 321,
		bbl_x002fm3 = 322,
		bbl_x002fmi = 323,
		bbl_x002fmin = 324,
		bbl_x002fpsi = 325,
		bbl_x002fton_x005bUK_x005d = 326,
		bbl_x002fton_x005bUS_x005d = 327,
		Bd = 328,
		bit = 329,
		bit_x002fs = 330,
		Bq = 331,
		Bq_x002fkg = 332,
		Btu_x005bIT_x005d = 333,
		Btu_x005bIT_x005d_x002ein_x002f_x0028h_x002eft2_x002edegF_x0029 = 334,
		Btu_x005bIT_x005d_x002f_x0028h_x002eft_x002edegF_x0029 = 335,
		Btu_x005bIT_x005d_x002f_x0028h_x002eft2_x0029 = 336,
		Btu_x005bIT_x005d_x002f_x0028h_x002eft2_x002edegF_x0029 = 337,
		Btu_x005bIT_x005d_x002f_x0028h_x002eft2_x002edegR_x0029 = 338,
		Btu_x005bIT_x005d_x002f_x0028h_x002eft3_x0029 = 339,
		Btu_x005bIT_x005d_x002f_x0028h_x002eft3_x002edegF_x0029 = 340,
		Btu_x005bIT_x005d_x002f_x0028h_x002em2_x002edegC_x0029 = 341,
		Btu_x005bIT_x005d_x002f_x0028hp_x002eh_x0029 = 342,
		Btu_x005bIT_x005d_x002f_x0028lbm_x002edegF_x0029 = 343,
		Btu_x005bIT_x005d_x002f_x0028lbm_x002edegR_x0029 = 344,
		Btu_x005bIT_x005d_x002f_x0028lbmol_x002edegF_x0029 = 345,
		Btu_x005bIT_x005d_x002f_x0028s_x002eft2_x0029 = 346,
		Btu_x005bIT_x005d_x002f_x0028s_x002eft2_x002edegF_x0029 = 347,
		Btu_x005bIT_x005d_x002f_x0028s_x002eft3_x0029 = 348,
		Btu_x005bIT_x005d_x002f_x0028s_x002eft3_x002edegF_x0029 = 349,
		Btu_x005bIT_x005d_x002fbbl = 350,
		Btu_x005bIT_x005d_x002fft3 = 351,
		Btu_x005bIT_x005d_x002fgal_x005bUK_x005d = 352,
		Btu_x005bIT_x005d_x002fgal_x005bUS_x005d = 353,
		Btu_x005bIT_x005d_x002fh = 354,
		Btu_x005bIT_x005d_x002flbm = 355,
		Btu_x005bIT_x005d_x002flbmol = 356,
		Btu_x005bIT_x005d_x002fmin = 357,
		Btu_x005bIT_x005d_x002fs = 358,
		Btu_x005bth_x005d = 359,
		Btu_x005bUK_x005d = 360,
		byte = 361,
		byte_x002fs = 362,
		C_x002em = 363,
		C_x002fcm2 = 364,
		C_x002fcm3 = 365,
		C_x002fg = 366,
		C_x002fkg = 367,
		C_x002fm2 = 368,
		C_x002fm3 = 369,
		C_x002fmm2 = 370,
		C_x002fmm3 = 371,
		ca = 372,
		cA = 373,
		cal_x005bIT_x005d = 374,
		cal_x005bth_x005d = 375,
		cal_x005bth_x005d_x002f_x0028g_x002eK_x0029 = 376,
		cal_x005bth_x005d_x002f_x0028h_x002ecm_x002edegC_x0029 = 377,
		cal_x005bth_x005d_x002f_x0028h_x002ecm2_x0029 = 378,
		cal_x005bth_x005d_x002f_x0028h_x002ecm2_x002edegC_x0029 = 379,
		cal_x005bth_x005d_x002f_x0028h_x002ecm3_x0029 = 380,
		cal_x005bth_x005d_x002f_x0028mol_x002edegC_x0029 = 381,
		cal_x005bth_x005d_x002f_x0028s_x002ecm_x002edegC_x0029 = 382,
		cal_x005bth_x005d_x002f_x0028s_x002ecm2_x002edegC_x0029 = 383,
		cal_x005bth_x005d_x002f_x0028s_x002ecm3_x0029 = 384,
		cal_x005bth_x005d_x002fcm3 = 385,
		cal_x005bth_x005d_x002fg = 386,
		cal_x005bth_x005d_x002fh = 387,
		cal_x005bth_x005d_x002fkg = 388,
		cal_x005bth_x005d_x002flbm = 389,
		cal_x005bth_x005d_x002fmL = 390,
		cal_x005bth_x005d_x002fmm3 = 391,
		cC = 392,
		ccal_x005bth_x005d = 393,
		ccgr = 394,
		cd = 395,
		cd_x002fm2 = 396,
		cEuc = 397,
		ceV = 398,
		cF = 399,
		cg = 400,
		cgauss = 401,
		cgr = 402,
		cGy = 403,
		cH = 404,
		chain = 405,
		chain_x005bBnA_x005d = 406,
		chain_x005bBnB_x005d = 407,
		chain_x005bCla_x005d = 408,
		chain_x005bInd37_x005d = 409,
		chain_x005bSe_x005d = 410,
		chain_x005bSeT_x005d = 411,
		chain_x005bUS_x005d = 412,
		cHz = 413,
		Ci = 414,
		cJ = 415,
		cm = 416,
		cm_x002fa = 417,
		cm_x002fs = 418,
		cm_x002fs2 = 419,
		cm2 = 420,
		cm2_x002fg = 421,
		cm2_x002fs = 422,
		cm3 = 423,
		cm3_x002fcm3 = 424,
		cm3_x002fg = 425,
		cm3_x002fh = 426,
		cm3_x002fL = 427,
		cm3_x002fm3 = 428,
		cm3_x002fmin = 429,
		cm3_x002fs = 430,
		cm4 = 431,
		cmH2O_x005b4degC_x005d = 432,
		cN = 433,
		cohm = 434,
		cP = 435,
		cPa = 436,
		crd = 437,
		cS = 438,
		cs = 439,
		cSt = 440,
		ct = 441,
		cT = 442,
		cu = 443,
		cV = 444,
		cW = 445,
		cWb = 446,
		cwt_x005bUK_x005d = 447,
		cwt_x005bUS_x005d = 448,
		D_x002eft = 449,
		D_x002em = 450,
		D_x002f_x0028Pa_x002es_x0029 = 451,
		d_x002fbbl = 452,
		D_x002fcP = 453,
		d_x002fft3 = 454,
		d_x002fm3 = 455,
		D_x005bAPI_x005d = 456,
		dA = 457,
		dam = 458,
		daN = 459,
		daN_x002em = 460,
		dAPI = 461,
		dB = 462,
		dB_x002eMW = 463,
		dB_x002emW = 464,
		dB_x002eW = 465,
		dB_x002fft = 466,
		dB_x002fkm = 467,
		dB_x002fm = 468,
		dB_x002fO = 469,
		dC = 470,
		dcal_x005bth_x005d = 471,
		dega = 472,
		dega_x002fft = 473,
		dega_x002fh = 474,
		dega_x002fm = 475,
		dega_x002fmin = 476,
		dega_x002fs = 477,
		degC = 478,
		degC_x002em2_x002eh_x002fkcal_x005bth_x005d = 479,
		degC_x002fft = 480,
		degC_x002fh = 481,
		degC_x002fhm = 482,
		degC_x002fkm = 483,
		degC_x002fkPa = 484,
		degC_x002fm = 485,
		degC_x002fmin = 486,
		degC_x002fs = 487,
		degF = 488,
		degF_x002eft2_x002eh_x002fBtu_x005bIT_x005d = 489,
		degF_x002fft = 490,
		degF_x002fh = 491,
		degF_x002fm = 492,
		degF_x002fmin = 493,
		degF_x002fpsi = 494,
		degF_x002fs = 495,
		degR = 496,
		dEuc = 497,
		deV = 498,
		dF = 499,
		dgauss = 500,
		dGy = 501,
		dH = 502,
		dHz = 503,
		dJ = 504,
		dm = 505,
		dm_x002fs = 506,
		dm3 = 507,
		dm3_x002f_x0028kW_x002eh_x0029 = 508,
		dm3_x002fkg = 509,
		dm3_x002fkmol = 510,
		dm3_x002fm = 511,
		dm3_x002fm3 = 512,
		dm3_x002fMJ = 513,
		dm3_x002fs = 514,
		dm3_x002fs2 = 515,
		dm3_x002ft = 516,
		dN = 517,
		dN_x002em = 518,
		dohm = 519,
		dP = 520,
		dPa = 521,
		drd = 522,
		ds = 523,
		dS = 524,
		dT = 525,
		dV = 526,
		dW = 527,
		dWb = 528,
		dyne = 529,
		dyne_x002ecm2 = 530,
		dyne_x002es_x002fcm2 = 531,
		dyne_x002fcm = 532,
		dyne_x002fcm2 = 533,
		EA = 534,
		Ea_x005bt_x005d = 535,
		EC = 536,
		Ecal_x005bth_x005d = 537,
		EEuc = 538,
		EeV = 539,
		EF = 540,
		Eg = 541,
		Egauss = 542,
		EGy = 543,
		EH = 544,
		EHz = 545,
		EJ = 546,
		EJ_x002fa = 547,
		Em = 548,
		EN = 549,
		Eohm = 550,
		EP = 551,
		EPa = 552,
		Erd = 553,
		erg = 554,
		erg_x002fa = 555,
		erg_x002fcm2 = 556,
		erg_x002fcm3 = 557,
		erg_x002fg = 558,
		erg_x002fkg = 559,
		erg_x002fm3 = 560,
		ES = 561,
		ET = 562,
		Euc = 563,
		eV = 564,
		EW = 565,
		EWb = 566,
		F_x002fm = 567,
		fa = 568,
		fA = 569,
		fathom = 570,
		fC = 571,
		fcal_x005bth_x005d = 572,
		fEuc = 573,
		feV = 574,
		fF = 575,
		fg = 576,
		fgauss = 577,
		fGy = 578,
		fH = 579,
		fHz = 580,
		fJ = 581,
		floz_x005bUK_x005d = 582,
		floz_x005bUS_x005d = 583,
		fm = 584,
		fN = 585,
		fohm = 586,
		footcandle = 587,
		footcandle_x002es = 588,
		fP = 589,
		fPa = 590,
		frd = 591,
		fS = 592,
		ft = 593,
		fT = 594,
		ft_x002fbbl = 595,
		ft_x002fd = 596,
		ft_x002fdegF = 597,
		ft_x002fft = 598,
		ft_x002fft3 = 599,
		ft_x002fgal_x005bUS_x005d = 600,
		ft_x002fh = 601,
		ft_x002fin = 602,
		ft_x002flbm = 603,
		ft_x002fm = 604,
		ft_x002fmi = 605,
		ft_x002fmin = 606,
		ft_x002fms = 607,
		ft_x002fpsi = 608,
		ft_x002fs = 609,
		ft_x002fs2 = 610,
		ft_x002fus = 611,
		ft_x005bBnA_x005d = 612,
		ft_x005bBnB_x005d = 613,
		ft_x005bBr36_x005d = 614,
		ft_x005bBr65_x005d = 615,
		ft_x005bCla_x005d = 616,
		ft_x005bGC_x005d = 617,
		ft_x005bInd_x005d = 618,
		ft_x005bInd37_x005d = 619,
		ft_x005bInd62_x005d = 620,
		ft_x005bInd75_x005d = 621,
		ft_x005bSe_x005d = 622,
		ft_x005bSeT_x005d = 623,
		ft_x005bUS_x005d = 624,
		ft2 = 625,
		ft2_x002fh = 626,
		ft2_x002fin3 = 627,
		ft2_x002flbm = 628,
		ft2_x002fs = 629,
		ft3 = 630,
		ft3_x002f_x0028d_x002eft_x0029 = 631,
		ft3_x002f_x0028ft_x002epsi_x002ed_x0029 = 632,
		ft3_x002f_x0028min_x002eft2_x0029 = 633,
		ft3_x002f_x0028s_x002eft2_x0029 = 634,
		ft3_x002fbbl = 635,
		ft3_x002fd = 636,
		ft3_x002fd2 = 637,
		ft3_x002fft = 638,
		ft3_x002fft2 = 639,
		ft3_x002fft3 = 640,
		ft3_x002fh = 641,
		ft3_x002fh2 = 642,
		ft3_x002fkg = 643,
		ft3_x002flbm = 644,
		ft3_x002flbmol = 645,
		ft3_x002fmin = 646,
		ft3_x002fmin2 = 647,
		ft3_x002frad = 648,
		ft3_x002fs = 649,
		ft3_x002fs2 = 650,
		ft3_x002fsack_x005b94lbm_x005d = 651,
		fur_x005bUS_x005d = 652,
		fV = 653,
		fW = 654,
		fWb = 655,
		g_x002eft_x002f_x0028cm3_x002es_x0029 = 656,
		g_x002em_x002f_x0028cm3_x002es_x0029 = 657,
		g_x002fcm3 = 658,
		g_x002fcm4 = 659,
		g_x002fdm3 = 660,
		g_x002fgal_x005bUK_x005d = 661,
		g_x002fgal_x005bUS_x005d = 662,
		g_x002fkg = 663,
		g_x002fL = 664,
		g_x002fm3 = 665,
		g_x002fmol = 666,
		g_x002fs = 667,
		g_x002ft = 668,
		GA = 669,
		Ga_x005bt_x005d = 670,
		Gal = 671,
		gal_x005bUK_x005d = 672,
		gal_x005bUK_x005d_x002f_x0028h_x002eft_x0029 = 673,
		gal_x005bUK_x005d_x002f_x0028h_x002eft2_x0029 = 674,
		gal_x005bUK_x005d_x002f_x0028h_x002ein_x0029 = 675,
		gal_x005bUK_x005d_x002f_x0028h_x002ein2_x0029 = 676,
		gal_x005bUK_x005d_x002f_x0028min_x002eft_x0029 = 677,
		gal_x005bUK_x005d_x002f_x0028min_x002eft2_x0029 = 678,
		gal_x005bUK_x005d_x002fd = 679,
		gal_x005bUK_x005d_x002fft3 = 680,
		gal_x005bUK_x005d_x002fh = 681,
		gal_x005bUK_x005d_x002fh2 = 682,
		gal_x005bUK_x005d_x002flbm = 683,
		gal_x005bUK_x005d_x002fmi = 684,
		gal_x005bUK_x005d_x002fmin = 685,
		gal_x005bUK_x005d_x002fmin2 = 686,
		gal_x005bUS_x005d = 687,
		gal_x005bUS_x005d_x002f_x0028h_x002eft_x0029 = 688,
		gal_x005bUS_x005d_x002f_x0028h_x002eft2_x0029 = 689,
		gal_x005bUS_x005d_x002f_x0028h_x002ein_x0029 = 690,
		gal_x005bUS_x005d_x002f_x0028h_x002ein2_x0029 = 691,
		gal_x005bUS_x005d_x002f_x0028min_x002eft_x0029 = 692,
		gal_x005bUS_x005d_x002f_x0028min_x002eft2_x0029 = 693,
		gal_x005bUS_x005d_x002fbbl = 694,
		gal_x005bUS_x005d_x002fd = 695,
		gal_x005bUS_x005d_x002fft = 696,
		gal_x005bUS_x005d_x002fft3 = 697,
		gal_x005bUS_x005d_x002fh = 698,
		gal_x005bUS_x005d_x002fh2 = 699,
		gal_x005bUS_x005d_x002flbm = 700,
		gal_x005bUS_x005d_x002fmi = 701,
		gal_x005bUS_x005d_x002fmin = 702,
		gal_x005bUS_x005d_x002fmin2 = 703,
		gal_x005bUS_x005d_x002fsack_x005b94lbm_x005d = 704,
		gal_x005bUS_x005d_x002fton_x005bUK_x005d = 705,
		gal_x005bUS_x005d_x002fton_x005bUS_x005d = 706,
		gAPI = 707,
		gauss = 708,
		gauss_x002fcm = 709,
		GBq = 710,
		GC = 711,
		Gcal_x005bth_x005d = 712,
		GEuc = 713,
		GeV = 714,
		gf = 715,
		GF = 716,
		Gg = 717,
		Ggauss = 718,
		GGy = 719,
		GH = 720,
		GHz = 721,
		GJ = 722,
		Gm = 723,
		gn = 724,
		GN = 725,
		Gohm = 726,
		gon = 727,
		GP = 728,
		GPa = 729,
		GPa_x002fcm = 730,
		GPa2 = 731,
		grain = 732,
		grain_x002fft3 = 733,
		grain_x002fgal_x005bUS_x005d = 734,
		Grd = 735,
		GS = 736,
		GT = 737,
		GV = 738,
		GW = 739,
		GW_x002eh = 740,
		GWb = 741,
		Gy = 742,
		h_x002fft3 = 743,
		h_x002fkm = 744,
		H_x002fm = 745,
		h_x002fm3 = 746,
		ha = 747,
		ha_x002em = 748,
		hbar = 749,
		hg = 750,
		hL = 751,
		hm = 752,
		hN = 753,
		hp = 754,
		hp_x002eh = 755,
		hp_x002eh_x002fbbl = 756,
		hp_x002eh_x002flbm = 757,
		hp_x002fft3 = 758,
		hp_x002fin2 = 759,
		hp_x005belec_x005d = 760,
		hp_x005bhyd_x005d = 761,
		hp_x005bhyd_x005d_x002fin2 = 762,
		hp_x005bmetric_x005d = 763,
		hp_x005bmetric_x005d_x002eh = 764,
		hs = 765,
		Hz = 766,
		in = 767,
		in_x002f_x0028in_x002edegF_x0029 = 768,
		in_x002fa = 769,
		in_x002fmin = 770,
		in_x002fs = 771,
		in_x002fs2 = 772,
		in_x005bUS_x005d = 773,
		in2 = 774,
		in2_x002fft2 = 775,
		in2_x002fin2 = 776,
		in2_x002fs = 777,
		in3 = 778,
		in3_x002fft = 779,
		in4 = 780,
		inH2O_x005b39degF_x005d = 781,
		inH2O_x005b60degF_x005d = 782,
		inHg_x005b32degF_x005d = 783,
		inHg_x005b60degF_x005d = 784,
		J_x002em_x002f_x0028s_x002em2_x002eK_x0029 = 785,
		J_x002em_x002fm2 = 786,
		J_x002f_x0028g_x002eK_x0029 = 787,
		J_x002f_x0028kg_x002eK_x0029 = 788,
		J_x002f_x0028mol_x002eK_x0029 = 789,
		J_x002f_x0028s_x002em2_x002edegC_x0029 = 790,
		J_x002fcm2 = 791,
		J_x002fdm3 = 792,
		J_x002fg = 793,
		J_x002fK = 794,
		J_x002fkg = 795,
		J_x002fm = 796,
		J_x002fm2 = 797,
		J_x002fm3 = 798,
		J_x002fmol = 799,
		J_x002fs = 800,
		K_x002em2_x002fkW = 801,
		K_x002em2_x002fW = 802,
		K_x002fkm = 803,
		K_x002fm = 804,
		K_x002fPa = 805,
		K_x002fs = 806,
		K_x002fW = 807,
		kA = 808,
		ka_x005bt_x005d = 809,
		kC = 810,
		kcal_x005bth_x005d = 811,
		kcal_x005bth_x005d_x002em_x002fcm2 = 812,
		kcal_x005bth_x005d_x002f_x0028h_x002em_x002edegC_x0029 = 813,
		kcal_x005bth_x005d_x002f_x0028h_x002em2_x002edegC_x0029 = 814,
		kcal_x005bth_x005d_x002f_x0028kg_x002edegC_x0029 = 815,
		kcal_x005bth_x005d_x002fcm3 = 816,
		kcal_x005bth_x005d_x002fg = 817,
		kcal_x005bth_x005d_x002fh = 818,
		kcal_x005bth_x005d_x002fkg = 819,
		kcal_x005bth_x005d_x002fm3 = 820,
		kcal_x005bth_x005d_x002fmol = 821,
		kcd = 822,
		kdyne = 823,
		kEuc = 824,
		keV = 825,
		kF = 826,
		kg = 827,
		kg_x002em = 828,
		kg_x002em_x002fcm2 = 829,
		kg_x002em_x002fs = 830,
		kg_x002em2 = 831,
		kg_x002f_x0028kW_x002eh_x0029 = 832,
		kg_x002f_x0028m_x002es_x0029 = 833,
		kg_x002f_x0028m2_x002es_x0029 = 834,
		kg_x002fd = 835,
		kg_x002fdm3 = 836,
		kg_x002fdm4 = 837,
		kg_x002fh = 838,
		kg_x002fJ = 839,
		kg_x002fkg = 840,
		kg_x002fL = 841,
		kg_x002fm = 842,
		kg_x002fm2 = 843,
		kg_x002fm3 = 844,
		kg_x002fm4 = 845,
		kg_x002fmin = 846,
		kg_x002fMJ = 847,
		kg_x002fmol = 848,
		kg_x002fs = 849,
		kg_x002fsack_x005b94lbm_x005d = 850,
		kg_x002ft = 851,
		kgauss = 852,
		kgf = 853,
		kgf_x002em = 854,
		kgf_x002em_x002fcm2 = 855,
		kgf_x002em_x002fm = 856,
		kgf_x002em2 = 857,
		kgf_x002es_x002fm2 = 858,
		kgf_x002fcm = 859,
		kgf_x002fcm2 = 860,
		kgf_x002fkgf = 861,
		kgf_x002fm2 = 862,
		kgf_x002fmm2 = 863,
		kGy = 864,
		kH = 865,
		kHz = 866,
		Kibyte = 867,
		kJ = 868,
		kJ_x002em_x002f_x0028h_x002em2_x002eK_x0029 = 869,
		kJ_x002f_x0028h_x002em2_x002eK_x0029 = 870,
		kJ_x002f_x0028kg_x002eK_x0029 = 871,
		kJ_x002f_x0028kmol_x002eK_x0029 = 872,
		kJ_x002fdm3 = 873,
		kJ_x002fkg = 874,
		kJ_x002fkmol = 875,
		kJ_x002fm3 = 876,
		klbf = 877,
		klbm = 878,
		klbm_x002fin = 879,
		klx = 880,
		km = 881,
		km_x002fcm = 882,
		km_x002fdm3 = 883,
		km_x002fh = 884,
		km_x002fL = 885,
		km_x002fs = 886,
		km2 = 887,
		km3 = 888,
		kmol = 889,
		kmol_x002fh = 890,
		kmol_x002fm3 = 891,
		kmol_x002fs = 892,
		kN = 893,
		kN_x002em = 894,
		kN_x002em2 = 895,
		kN_x002fm = 896,
		kN_x002fm2 = 897,
		knot = 898,
		kohm = 899,
		kohm_x002em = 900,
		kP = 901,
		kPa = 902,
		kPa_x002es_x002fm = 903,
		kPa_x002fh = 904,
		kPa_x002fhm = 905,
		kPa_x002fm = 906,
		kPa_x002fmin = 907,
		kPa2 = 908,
		kPa2_x002fcP = 909,
		kpsi = 910,
		kpsi2 = 911,
		krad = 912,
		krd = 913,
		kS = 914,
		kS_x002fm = 915,
		kT = 916,
		kV = 917,
		kW = 918,
		kW_x002eh = 919,
		kW_x002eh_x002f_x0028kg_x002edegC_x0029 = 920,
		kW_x002eh_x002fdm3 = 921,
		kW_x002eh_x002fkg = 922,
		kW_x002eh_x002fm3 = 923,
		kW_x002f_x0028m2_x002eK_x0029 = 924,
		kW_x002f_x0028m3_x002eK_x0029 = 925,
		kW_x002fcm2 = 926,
		kW_x002fm2 = 927,
		kW_x002fm3 = 928,
		kWb = 929,
		L_x002f_x0028bar_x002emin_x0029 = 930,
		L_x002fh = 931,
		L_x002fkg = 932,
		L_x002fkmol = 933,
		L_x002fm = 934,
		L_x002fm3 = 935,
		L_x002fmin = 936,
		L_x002fmol = 937,
		L_x002fs = 938,
		L_x002fs2 = 939,
		L_x002ft = 940,
		L_x002fton_x005bUK_x005d = 941,
		lbf = 942,
		lbf_x002eft = 943,
		lbf_x002eft_x002fbbl = 944,
		lbf_x002eft_x002fgal_x005bUS_x005d = 945,
		lbf_x002eft_x002fin = 946,
		lbf_x002eft_x002fin2 = 947,
		lbf_x002eft_x002flbm = 948,
		lbf_x002eft_x002fmin = 949,
		lbf_x002eft_x002fs = 950,
		lbf_x002ein = 951,
		lbf_x002ein_x002fin = 952,
		lbf_x002ein2 = 953,
		lbf_x002es_x002fft2 = 954,
		lbf_x002es_x002fin2 = 955,
		lbf_x002fft = 956,
		lbf_x002fft2 = 957,
		lbf_x002fft3 = 958,
		lbf_x002fgal_x005bUS_x005d = 959,
		lbf_x002fin = 960,
		lbf_x002flbf = 961,
		lbm = 962,
		lbm_x002eft = 963,
		lbm_x002eft_x002fs = 964,
		lbm_x002eft2 = 965,
		lbm_x002eft2_x002fs2 = 966,
		lbm_x002f_x0028ft_x002eh_x0029 = 967,
		lbm_x002f_x0028ft_x002es_x0029 = 968,
		lbm_x002f_x0028ft2_x002eh_x0029 = 969,
		lbm_x002f_x0028ft2_x002es_x0029 = 970,
		lbm_x002f_x0028gal_x005bUK_x005d_x002eft_x0029 = 971,
		lbm_x002f_x0028gal_x005bUS_x005d_x002eft_x0029 = 972,
		lbm_x002f_x0028hp_x002eh_x0029 = 973,
		lbm_x002fbbl = 974,
		lbm_x002fd = 975,
		lbm_x002fft = 976,
		lbm_x002fft2 = 977,
		lbm_x002fft3 = 978,
		lbm_x002fft4 = 979,
		lbm_x002fgal_x005bUK_x005d = 980,
		lbm_x002fgal_x005bUS_x005d = 981,
		lbm_x002fh = 982,
		lbm_x002fin3 = 983,
		lbm_x002flbmol = 984,
		lbm_x002fmin = 985,
		lbm_x002fs = 986,
		lbmol = 987,
		lbmol_x002f_x0028h_x002eft2_x0029 = 988,
		lbmol_x002f_x0028s_x002eft2_x0029 = 989,
		lbmol_x002fft3 = 990,
		lbmol_x002fgal_x005bUK_x005d = 991,
		lbmol_x002fgal_x005bUS_x005d = 992,
		lbmol_x002fh = 993,
		lbmol_x002fs = 994,
		link = 995,
		link_x005bBnA_x005d = 996,
		link_x005bBnB_x005d = 997,
		link_x005bCla_x005d = 998,
		link_x005bSe_x005d = 999,
		link_x005bSeT_x005d = 1000,
		link_x005bUS_x005d = 1001,
		lm = 1002,
		lm_x002es = 1003,
		lm_x002fm2 = 1004,
		lm_x002fW = 1005,
		lx = 1006,
		lx_x002es = 1007,
		m_x002f_x0028m_x002eK_x0029 = 1008,
		m_x002fcm = 1009,
		m_x002fd = 1010,
		m_x002fh = 1011,
		m_x002fK = 1012,
		m_x002fkg = 1013,
		m_x002fkm = 1014,
		m_x002fkPa = 1015,
		m_x002fm = 1016,
		m_x002fm3 = 1017,
		m_x002fmin = 1018,
		m_x002fms = 1019,
		m_x002fPa = 1020,
		m_x002fs = 1021,
		m_x002fs2 = 1022,
		m_x005bGer_x005d = 1023,
		m2 = 1024,
		m2_x002f_x0028kPa_x002ed_x0029 = 1025,
		m2_x002f_x0028Pa_x002es_x0029 = 1026,
		m2_x002fcm3 = 1027,
		m2_x002fd = 1028,
		m2_x002fg = 1029,
		m2_x002fh = 1030,
		m2_x002fkg = 1031,
		m2_x002fm2 = 1032,
		m2_x002fm3 = 1033,
		m2_x002fmol = 1034,
		m2_x002fs = 1035,
		m3 = 1036,
		m3_x002f_x0028bar_x002ed_x0029 = 1037,
		m3_x002f_x0028bar_x002eh_x0029 = 1038,
		m3_x002f_x0028bar_x002emin_x0029 = 1039,
		m3_x002f_x0028d_x002em_x0029 = 1040,
		m3_x002f_x0028h_x002em_x0029 = 1041,
		m3_x002f_x0028ha_x002em_x0029 = 1042,
		m3_x002f_x0028kPa_x002ed_x0029 = 1043,
		m3_x002f_x0028kPa_x002eh_x0029 = 1044,
		m3_x002f_x0028kW_x002eh_x0029 = 1045,
		m3_x002f_x0028m3_x002eK_x0029 = 1046,
		m3_x002f_x0028Pa_x002es_x0029 = 1047,
		m3_x002f_x0028psi_x002ed_x0029 = 1048,
		m3_x002f_x0028s_x002eft_x0029 = 1049,
		m3_x002f_x0028s_x002em_x0029 = 1050,
		m3_x002f_x0028s_x002em2_x0029 = 1051,
		m3_x002f_x0028s_x002em3_x0029 = 1052,
		m3_x002fbbl = 1053,
		m3_x002fd = 1054,
		m3_x002fd2 = 1055,
		m3_x002fg = 1056,
		m3_x002fh = 1057,
		m3_x002fJ = 1058,
		m3_x002fkg = 1059,
		m3_x002fkm = 1060,
		m3_x002fkmol = 1061,
		m3_x002fkPa = 1062,
		m3_x002fm = 1063,
		m3_x002fm2 = 1064,
		m3_x002fm3 = 1065,
		m3_x002fmin = 1066,
		m3_x002fmol = 1067,
		m3_x002fPa = 1068,
		m3_x002frad = 1069,
		m3_x002frev = 1070,
		m3_x002fs = 1071,
		m3_x002fs2 = 1072,
		m3_x002ft = 1073,
		m3_x002fton_x005bUK_x005d = 1074,
		m3_x002fton_x005bUS_x005d = 1075,
		m4 = 1076,
		m4_x002fs = 1077,
		mA = 1078,
		MA = 1079,
		mA_x002fcm2 = 1080,
		mA_x002fft2 = 1081,
		Ma_x005bt_x005d = 1082,
		mbar = 1083,
		MBq = 1084,
		mC = 1085,
		MC = 1086,
		mC_x002fm2 = 1087,
		Mcal_x005bth_x005d = 1088,
		mcal_x005bth_x005d = 1089,
		mCi = 1090,
		mD = 1091,
		mD_x002eft = 1092,
		mD_x002eft2_x002f_x0028lbf_x002es_x0029 = 1093,
		mD_x002ein2_x002f_x0028lbf_x002es_x0029 = 1094,
		mD_x002em = 1095,
		mD_x002f_x0028Pa_x002es_x0029 = 1096,
		mD_x002fcP = 1097,
		MEuc = 1098,
		mEuc = 1099,
		meV = 1100,
		MeV = 1101,
		mF = 1102,
		MF = 1103,
		Mg = 1104,
		mg = 1105,
		Mg_x002fa = 1106,
		Mg_x002fd = 1107,
		mg_x002fdm3 = 1108,
		mg_x002fg = 1109,
		mg_x002fgal_x005bUS_x005d = 1110,
		Mg_x002fh = 1111,
		Mg_x002fin = 1112,
		mg_x002fJ = 1113,
		mg_x002fkg = 1114,
		mg_x002fL = 1115,
		Mg_x002fm2 = 1116,
		Mg_x002fm3 = 1117,
		mg_x002fm3 = 1118,
		Mg_x002fmin = 1119,
		mGal = 1120,
		Mgauss = 1121,
		mgauss = 1122,
		Mgf = 1123,
		mgn = 1124,
		MGy = 1125,
		mGy = 1126,
		MH = 1127,
		mH = 1128,
		mHz = 1129,
		MHz = 1130,
		mi = 1131,
		mi_x002fgal_x005bUK_x005d = 1132,
		mi_x002fgal_x005bUS_x005d = 1133,
		mi_x002fh = 1134,
		mi_x002fin = 1135,
		mi_x005bnaut_x005d = 1136,
		mi_x005bnautUK_x005d = 1137,
		mi_x005bUS_x005d = 1138,
		mi_x005bUS_x005d2 = 1139,
		mi2 = 1140,
		mi3 = 1141,
		Mibyte = 1142,
		mil = 1143,
		mil_x002fa = 1144,
		mila = 1145,
		min_ = 1146,
		min_x002fft = 1147,
		min_x002fm = 1148,
		mina = 1149,
		mJ = 1150,
		MJ = 1151,
		MJ_x002fa = 1152,
		mJ_x002fcm2 = 1153,
		MJ_x002fkg = 1154,
		MJ_x002fkmol = 1155,
		MJ_x002fm = 1156,
		mJ_x002fm2 = 1157,
		MJ_x002fm3 = 1158,
		mL = 1159,
		mL_x002fgal_x005bUK_x005d = 1160,
		mL_x002fgal_x005bUS_x005d = 1161,
		mL_x002fmL = 1162,
		Mm = 1163,
		mm = 1164,
		mm_x002f_x0028mm_x002eK_x0029 = 1165,
		mm_x002fa = 1166,
		mm_x002fs = 1167,
		mm2 = 1168,
		mm2_x002fmm2 = 1169,
		mm2_x002fs = 1170,
		mm3 = 1171,
		mm3_x002fJ = 1172,
		mmHg_x005b0degC_x005d = 1173,
		mmol = 1174,
		mN = 1175,
		MN = 1176,
		mN_x002em2 = 1177,
		mN_x002fkm = 1178,
		mN_x002fm = 1179,
		mohm = 1180,
		Mohm = 1181,
		mol = 1182,
		mol_x002em2_x002f_x0028mol_x002es_x0029 = 1183,
		mol_x002f_x0028s_x002em2_x0029 = 1184,
		mol_x002fm2 = 1185,
		mol_x002fm3 = 1186,
		mol_x002fmol = 1187,
		mol_x002fs = 1188,
		mP = 1189,
		MP = 1190,
		MPa = 1191,
		mPa = 1192,
		mPa_x002es = 1193,
		MPa_x002es_x002fm = 1194,
		MPa_x002fh = 1195,
		MPa_x002fm = 1196,
		Mpsi = 1197,
		mrad = 1198,
		Mrad = 1199,
		Mrd = 1200,
		mrd = 1201,
		mrem = 1202,
		mrem_x002fh = 1203,
		MS = 1204,
		mS = 1205,
		ms = 1206,
		ms_x002fcm = 1207,
		mS_x002fcm = 1208,
		ms_x002fft = 1209,
		ms_x002fin = 1210,
		mS_x002fm = 1211,
		ms_x002fm = 1212,
		ms_x002fs = 1213,
		mSv = 1214,
		mSv_x002fh = 1215,
		mT = 1216,
		mT_x002fdm = 1217,
		MV = 1218,
		mV = 1219,
		mV_x002fft = 1220,
		mV_x002fm = 1221,
		MW = 1222,
		mW = 1223,
		MW_x002eh = 1224,
		MW_x002eh_x002fkg = 1225,
		MW_x002eh_x002fm3 = 1226,
		mW_x002fm2 = 1227,
		mWb = 1228,
		MWb = 1229,
		N_x002em = 1230,
		N_x002em_x002fm = 1231,
		N_x002em2 = 1232,
		N_x002es_x002fm2 = 1233,
		N_x002fm = 1234,
		N_x002fm2 = 1235,
		N_x002fm3 = 1236,
		N_x002fmm2 = 1237,
		N_x002fN = 1238,
		nA = 1239,
		na = 1240,
		nAPI = 1241,
		nC = 1242,
		ncal_x005bth_x005d = 1243,
		nCi = 1244,
		nEuc = 1245,
		neV = 1246,
		nF = 1247,
		ng = 1248,
		ng_x002fg = 1249,
		ng_x002fmg = 1250,
		ngauss = 1251,
		nGy = 1252,
		nH = 1253,
		nHz = 1254,
		nJ = 1255,
		nm = 1256,
		nm_x002fs = 1257,
		nN = 1258,
		nohm = 1259,
		nohm_x002emil2_x002fft = 1260,
		nohm_x002emm2_x002fm = 1261,
		nP = 1262,
		nPa = 1263,
		nrd = 1264,
		nS = 1265,
		ns = 1266,
		ns_x002fft = 1267,
		ns_x002fm = 1268,
		nT = 1269,
		nV = 1270,
		nW = 1271,
		nWb = 1272,
		Oe = 1273,
		ohm = 1274,
		ohm_x002ecm = 1275,
		ohm_x002em = 1276,
		ohm_x002em2_x002fm = 1277,
		ohm_x002fm = 1278,
		ozf = 1279,
		ozm = 1280,
		ozm_x005btroy_x005d = 1281,
		pA = 1282,
		Pa = 1283,
		Pa_x002es = 1284,
		Pa_x002es_x002em3_x002fkg = 1285,
		Pa_x002es_x002fm3 = 1286,
		Pa_x002es2_x002fm3 = 1287,
		Pa_x002fh = 1288,
		Pa_x002fm = 1289,
		Pa_x002fm3 = 1290,
		Pa_x002fs = 1291,
		Pa2 = 1292,
		Pa2_x002f_x0028Pa_x002es_x0029 = 1293,
		pC = 1294,
		pcal_x005bth_x005d = 1295,
		pCi = 1296,
		pCi_x002fg = 1297,
		pdl = 1298,
		pdl_x002ecm2 = 1299,
		pdl_x002eft = 1300,
		pdl_x002fcm = 1301,
		pEuc = 1302,
		peV = 1303,
		pF = 1304,
		pg = 1305,
		pgauss = 1306,
		pGy = 1307,
		pHz = 1308,
		pJ = 1309,
		pm = 1310,
		pN = 1311,
		pohm = 1312,
		pP = 1313,
		pPa = 1314,
		ppk = 1315,
		ppm = 1316,
		ppm_x005bmass_x005d = 1317,
		ppm_x005bvol_x005d = 1318,
		ppm_x005bvol_x005d_x002fdegC = 1319,
		ppm_x005bvol_x005d_x002fdegF = 1320,
		prd = 1321,
		ps = 1322,
		pS = 1323,
		psi = 1324,
		psi_x002ed_x002fbbl = 1325,
		psi_x002es = 1326,
		psi_x002fft = 1327,
		psi_x002fh = 1328,
		psi_x002fm = 1329,
		psi_x002fmin = 1330,
		psi2 = 1331,
		psi2_x002ed_x002f_x0028cP_x002eft3_x0029 = 1332,
		psi2_x002fcP = 1333,
		pT = 1334,
		pt_x005bUK_x005d = 1335,
		pt_x005bUK_x005d_x002f_x0028hp_x002eh_x0029 = 1336,
		pt_x005bUS_x005d = 1337,
		pV = 1338,
		pW = 1339,
		pWb = 1340,
		qt_x005bUK_x005d = 1341,
		qt_x005bUS_x005d = 1342,
		quad = 1343,
		quad_x002fa = 1344,
		rad = 1345,
		rad_x002fft = 1346,
		rad_x002fft3 = 1347,
		rad_x002fm = 1348,
		rad_x002fm3 = 1349,
		rad_x002fs = 1350,
		rad_x002fs2 = 1351,
		rd = 1352,
		rem = 1353,
		rem_x002fh = 1354,
		rev = 1355,
		rev_x002fft = 1356,
		rev_x002fm = 1357,
		rev_x002fs = 1358,
		rod_x005bUS_x005d = 1359,
		rpm = 1360,
		rpm_x002fs = 1361,
		s_x002fcm = 1362,
		s_x002fft = 1363,
		s_x002fft3 = 1364,
		s_x002fin = 1365,
		s_x002fkg = 1366,
		s_x002fL = 1367,
		S_x002fm = 1368,
		s_x002fm = 1369,
		s_x002fm3 = 1370,
		s_x002fqt_x005bUK_x005d = 1371,
		s_x002fqt_x005bUS_x005d = 1372,
		s_x002fs = 1373,
		sack_x005b94lbm_x005d = 1374,
		seca = 1375,
		section = 1376,
		sr = 1377,
		St = 1378,
		Sv = 1379,
		Sv_x002fh = 1380,
		Sv_x002fs = 1381,
		t_x002fa = 1382,
		t_x002fd = 1383,
		t_x002fh = 1384,
		T_x002fm = 1385,
		t_x002fm3 = 1386,
		t_x002fmin = 1387,
		TA = 1388,
		Ta_x005bt_x005d = 1389,
		TBq = 1390,
		TC = 1391,
		Tcal_x005bth_x005d = 1392,
		TD_x005bAPI_x005d = 1393,
		TD_x005bAPI_x005d_x002em = 1394,
		TD_x005bAPI_x005d_x002f_x0028Pa_x002es_x0029 = 1395,
		TEuc = 1396,
		TeV = 1397,
		TF = 1398,
		Tg = 1399,
		Tgauss = 1400,
		TGy = 1401,
		TH = 1402,
		therm_x005bEC_x005d = 1403,
		therm_x005bUK_x005d = 1404,
		therm_x005bUS_x005d = 1405,
		THz = 1406,
		TJ = 1407,
		TJ_x002fa = 1408,
		Tm = 1409,
		TN = 1410,
		Tohm = 1411,
		ton_x005bUK_x005d = 1412,
		ton_x005bUK_x005d_x002fa = 1413,
		ton_x005bUK_x005d_x002fd = 1414,
		ton_x005bUK_x005d_x002fh = 1415,
		ton_x005bUK_x005d_x002fmin = 1416,
		ton_x005bUS_x005d = 1417,
		ton_x005bUS_x005d_x002fa = 1418,
		ton_x005bUS_x005d_x002fd = 1419,
		ton_x005bUS_x005d_x002fft2 = 1420,
		ton_x005bUS_x005d_x002fh = 1421,
		ton_x005bUS_x005d_x002fmin = 1422,
		tonf_x005bUK_x005d = 1423,
		tonf_x005bUK_x005d_x002eft2 = 1424,
		tonf_x005bUK_x005d_x002fft = 1425,
		tonf_x005bUK_x005d_x002fft2 = 1426,
		tonf_x005bUS_x005d = 1427,
		tonf_x005bUS_x005d_x002eft = 1428,
		tonf_x005bUS_x005d_x002eft2 = 1429,
		tonf_x005bUS_x005d_x002emi = 1430,
		tonf_x005bUS_x005d_x002emi_x002fbbl = 1431,
		tonf_x005bUS_x005d_x002emi_x002fft = 1432,
		tonf_x005bUS_x005d_x002fft = 1433,
		tonf_x005bUS_x005d_x002fft2 = 1434,
		tonf_x005bUS_x005d_x002fin2 = 1435,
		tonRefrig = 1436,
		torr = 1437,
		TP = 1438,
		TPa = 1439,
		Trd = 1440,
		TS = 1441,
		TT = 1442,
		TV = 1443,
		TW = 1444,
		TW_x002eh = 1445,
		TWb = 1446,
		uA = 1447,
		uA_x002fcm2 = 1448,
		uA_x002fin2 = 1449,
		ubar = 1450,
		uC = 1451,
		ucal_x005bth_x005d = 1452,
		ucal_x005bth_x005d_x002f_x0028s_x002ecm2_x0029 = 1453,
		ucal_x005bth_x005d_x002fs = 1454,
		uCi = 1455,
		uEuc = 1456,
		ueV = 1457,
		uF = 1458,
		uF_x002fm = 1459,
		ug = 1460,
		ug_x002fcm3 = 1461,
		ug_x002fg = 1462,
		ug_x002fmg = 1463,
		ugauss = 1464,
		uGy = 1465,
		uH = 1466,
		uH_x002fm = 1467,
		uHz = 1468,
		uJ = 1469,
		um = 1470,
		um_x002fs = 1471,
		um2 = 1472,
		um2_x002em = 1473,
		umHg_x005b0degC_x005d = 1474,
		umol = 1475,
		uN = 1476,
		uohm = 1477,
		uohm_x002fft = 1478,
		uohm_x002fm = 1479,
		uP = 1480,
		uPa = 1481,
		upsi = 1482,
		urad = 1483,
		urd = 1484,
		us = 1485,
		uS = 1486,
		us_x002fft = 1487,
		us_x002fin = 1488,
		us_x002fm = 1489,
		uT = 1490,
		uV = 1491,
		uV_x002fft = 1492,
		uV_x002fm = 1493,
		uW = 1494,
		uW_x002fm3 = 1495,
		uWb = 1496,
		V_x002fB = 1497,
		V_x002fdB = 1498,
		V_x002fm = 1499,
		W_x002em2_x002eK_x002f_x0028J_x002eK_x0029 = 1500,
		W_x002f_x0028m_x002eK_x0029 = 1501,
		W_x002f_x0028m2_x002eK_x0029 = 1502,
		W_x002f_x0028m2_x002esr_x0029 = 1503,
		W_x002f_x0028m3_x002eK_x0029 = 1504,
		W_x002fcm2 = 1505,
		W_x002fK = 1506,
		W_x002fkW = 1507,
		W_x002fm2 = 1508,
		W_x002fm3 = 1509,
		W_x002fmm2 = 1510,
		W_x002fsr = 1511,
		W_x002fW = 1512,
		Wb = 1513,
		Wb_x002em = 1514,
		Wb_x002fm = 1515,
		Wb_x002fmm = 1516,
		wk = 1517,
		yd = 1518,
		yd_x005bBnA_x005d = 1519,
		yd_x005bBnB_x005d = 1520,
		yd_x005bCla_x005d = 1521,
		yd_x005bInd_x005d = 1522,
		yd_x005bInd37_x005d = 1523,
		yd_x005bInd62_x005d = 1524,
		yd_x005bInd75_x005d = 1525,
		yd_x005bSe_x005d = 1526,
		yd_x005bSeT_x005d = 1527,
		yd_x005bUS_x005d = 1528,
		yd2 = 1529,
		yd3 = 1530
	};	
	enum class eml20__PlaneAngleUom {
		_0_x002e001_x0020seca = 0,
		ccgr = 1,
		cgr = 2,
		dega = 3,
		gon = 4,
		krad = 5,
		mila = 6,
		mina = 7,
		Mrad = 8,
		mrad = 9,
		rad = 10,
		rev = 11,
		seca = 12,
		urad = 13
	};
	enum class eml20__LengthUom {
		m =
#ifdef SWIGPYTHON
(int)
#endif
			'm',
		_0_x002e1_x0020ft =
#ifdef SWIGPYTHON
(int)
#endif
			'n',
		_0_x002e1_x0020ft_x005bUS_x005d =
#ifdef SWIGPYTHON
(int)
#endif
			'o',
		_0_x002e1_x0020in =
#ifdef SWIGPYTHON
(int)
#endif
			'p',
		_0_x002e1_x0020yd =
#ifdef SWIGPYTHON
(int)
#endif
			'q',
		_1_x002f16_x0020in =
#ifdef SWIGPYTHON
(int)
#endif
			'r',
		_1_x002f2_x0020ft =
#ifdef SWIGPYTHON
(int)
#endif
			's',
		_1_x002f32_x0020in =
#ifdef SWIGPYTHON
(int)
#endif
			't',
		_1_x002f64_x0020in =
#ifdef SWIGPYTHON
(int)
#endif
			'u',
		_10_x0020ft =
#ifdef SWIGPYTHON
(int)
#endif
			'v',
		_10_x0020in =
#ifdef SWIGPYTHON
(int)
#endif
			'w',
		_10_x0020km =
#ifdef SWIGPYTHON
(int)
#endif
			'x',
		_100_x0020ft =
#ifdef SWIGPYTHON
(int)
#endif
			'y',
		_100_x0020km =
#ifdef SWIGPYTHON
(int)
#endif
			'z',
		_1000_x0020ft = 123,
		_30_x0020ft = 124,
		_30_x0020m = 125,
		angstrom = 126,
		chain = 127,
		chain_x005bBnA_x005d = 128,
		chain_x005bBnB_x005d = 129,
		chain_x005bCla_x005d = 130,
		chain_x005bInd37_x005d = 131,
		chain_x005bSe_x005d = 132,
		chain_x005bSeT_x005d = 133,
		chain_x005bUS_x005d = 134,
		cm = 135,
		dam = 136,
		dm = 137,
		Em = 138,
		fathom = 139,
		fm = 140,
		ft = 141,
		ft_x005bBnA_x005d = 142,
		ft_x005bBnB_x005d = 143,
		ft_x005bBr36_x005d = 144,
		ft_x005bBr65_x005d = 145,
		ft_x005bCla_x005d = 146,
		ft_x005bGC_x005d = 147,
		ft_x005bInd_x005d = 148,
		ft_x005bInd37_x005d = 149,
		ft_x005bInd62_x005d = 150,
		ft_x005bInd75_x005d = 151,
		ft_x005bSe_x005d = 152,
		ft_x005bSeT_x005d = 153,
		ft_x005bUS_x005d = 154,
		fur_x005bUS_x005d = 155,
		Gm = 156,
		hm = 157,
		in = 158,
		in_x005bUS_x005d = 159,
		km = 160,
		link = 161,
		link_x005bBnA_x005d = 162,
		link_x005bBnB_x005d = 163,
		link_x005bCla_x005d = 164,
		link_x005bSe_x005d = 165,
		link_x005bSeT_x005d = 166,
		link_x005bUS_x005d = 167,
		m_x005bGer_x005d = 168,
		mi = 169,
		mi_x005bnaut_x005d = 170,
		mi_x005bnautUK_x005d = 171,
		mi_x005bUS_x005d = 172,
		mil = 173,
		Mm = 174,
		mm = 175,
		nm = 176,
		pm = 177,
		rod_x005bUS_x005d = 178,
		Tm = 179,
		um = 180,
		yd = 181,
		yd_x005bBnA_x005d = 182,
		yd_x005bBnB_x005d = 183,
		yd_x005bCla_x005d = 184,
		yd_x005bInd_x005d = 185,
		yd_x005bInd37_x005d = 186,
		yd_x005bInd62_x005d = 187,
		yd_x005bInd75_x005d = 188,
		yd_x005bSe_x005d = 189,
		yd_x005bSeT_x005d = 190,
		yd_x005bUS_x005d = 191
	};
	enum class eml20__TimeUom {
		a =
#ifdef SWIGPYTHON
(int)
#endif
			'a',
		d =
#ifdef SWIGPYTHON
(int)
#endif
			'd',
		h =
#ifdef SWIGPYTHON
(int)
#endif
			'h',
		s =
#ifdef SWIGPYTHON
(int)
#endif
			's',
		_1_x002f2_x0020ms =
#ifdef SWIGPYTHON
(int)
#endif
			't',
		_100_x0020ka_x005bt_x005d =
#ifdef SWIGPYTHON
(int)
#endif
			'u',
		a_x005bt_x005d =
#ifdef SWIGPYTHON
(int)
#endif
			'v',
		ca =
#ifdef SWIGPYTHON
(int)
#endif
			'w',
		cs =
#ifdef SWIGPYTHON
(int)
#endif
			'x',
		ds =
#ifdef SWIGPYTHON
(int)
#endif
			'y',
		Ea_x005bt_x005d =
#ifdef SWIGPYTHON
(int)
#endif
			'z',
		fa = 123,
		Ga_x005bt_x005d = 124,
		hs = 125,
		ka_x005bt_x005d = 126,
		Ma_x005bt_x005d = 127,
		min_ = 128,
		ms = 129,
		na = 130,
		ns = 131,
		ps = 132,
		Ta_x005bt_x005d = 133,
		us = 134,
		wk = 135
	};
	enum class eml20__AxisOrder2d {
		easting_x0020northing = 0,
		northing_x0020easting = 1,
		westing_x0020southing = 2,
		southing_x0020westing = 3,
		northing_x0020westing = 4,
		westing_x0020northing = 5
	};
	enum class resqml20__GeologicBoundaryKind {
		fault = 0,
		geobody = 1,
		horizon = 2
	};
	enum class resqml20__KDirection {
		down = 0,
		up = 1,
		not_x0020monotonic = 2
	};
	enum class resqml20__CellShape {
		tetrahedral = 0,
		pyramidal = 1,
		prism = 2,
		hexahedral = 3,
		polyhedral = 4
	};
	enum class resqml20__SurfaceRole {
		map = 0,
		pick = 1
	};
	enum class resqml20__ContactSide {
		footwall = 0,
		hanging_x0020wall = 1,
		north = 2,
		south = 3,
		east = 4,
		west = 5,
		younger = 6,
		older = 7,
		both = 8
	};
	enum class resqml20__DepositionMode {
		proportional_x0020between_x0020top_x0020and_x0020bottom = 0,
		parallel_x0020to_x0020bottom = 1,
		parallel_x0020to_x0020top = 2,
		parallel_x0020to_x0020another_x0020boundary = 3
	};
	enum class resqml20__Domain {
		depth = 0,
		time = 1,
		mixed = 2
	};
	enum class resqml20__PillarShape {
		vertical = 0,
		straight = 1,
		curved = 2
	};
	enum class resqml20__FluidContact {
		free_x0020water_x0020contact = 0,
		gas_x0020oil_x0020contact = 1,
		gas_x0020water_x0020contact = 2,
		seal = 3,
		water_x0020oil_x0020contact = 4
	};
}
namespace gsoap_eml2_3
{
	enum class resqml22__Shape3d {
		sheet = 0,
		dyke = 1,
		dome = 2,
		mushroom = 3,
		channel = 4,
		delta = 5,
		dune = 6,
		fan = 7,
		reef = 8,
		wedge = 9
	};
	enum class resqml22__ContactVerb {
		stops = 0,
		splits = 1,
		crosses = 2
	};
	enum class resqml22__ContactMode {
		conformable = 0,
		extended = 1,
		unconformable = 2
	};
	enum class resqml22__Phase {
		aquifer = 0,
		gas_x0020cap = 1,
		oil_x0020column = 2,
		seal = 3
	};
	enum class resqml22__LineRole {
		fault_x0020center_x0020line = 0,
		pick = 1,
		inner_x0020ring = 2,
		outer_x0020ring = 3,
		trajectory = 4,
		interpretation_x0020line = 5,
		contact = 6,
		depositional_x0020line = 7,
		erosion_x0020line = 8,
		contour = 9,
		pillar = 10,
		break_x0020line = 11,
		structural_x0020closure = 12,
		culture = 13
	};
	enum class eml23__FacetKind {
		conditions = 0,
		side = 1,
		direction = 2,
		netgross = 3,
		qualifier = 4,
		statistics = 5,
		what = 6
	};
}

namespace RESQML2_NS
{
	%nodefaultctor; // Disable creation of default constructors

#if defined(SWIGPYTHON)
	%rename(Resqml2_AbstractColorMap) AbstractColorMap;
#endif
	class AbstractColorMap : public COMMON_NS::AbstractObject
	{
	public:

		/**
		* https://en.wikipedia.org/wiki/HSV_color_space
		* @param colorCount		the size (number of colors) of the color map
		* @param hsvColors		array (of size colorCount * 3) of HSV colors with hsvColors[3*i] is the hue, hsvColors[3*i + 1] is the saturation and hsvColors[3*i + 2] is the value of the ith color (hue is in range [0, 360] while saturation and value are in range [0, 1])
		* @param alphas			array (of size colorCount) of numeric values in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). If alphas == nullptr (default value), default alpha value is 1.
		* @param indices		array (of size colorCount) of color indices. These indices are cast to unsigned int in the case of a discrete color map. If indices 
		* @param colorTitles	vector (of size colorCount) of color titles. Titles are not set if colorTitles is empty (default value)= nullptr (default value), indices are set from 0 to colorCount - 1
		*/
		virtual void setHsvColors(uint64_t colorCount,
			double const* hsvColors, double const* alphas = nullptr, double const* indices = nullptr,
			std::vector<std::string> const& colorTitles = std::vector<std::string>()) = 0;

		/**
		* https://en.wikipedia.org/wiki/HSV_color_space
		* @param colorCount		the size (number of colors) of the color map
		* @param rgbColors		array (of size colorCount * 3) of RGB colors with rgbColors[3*i] is red component, rgbColors[3*i + 1] is green component and rgbColors[3*i + 2] is blue component of the ith color (red, green and blue are in range [0, 1])
		* @param alphas			array (of size colorCount) of numeric values in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). If alphas == nullptr (default value), default alpha value is 1.
		* @param indices		array (of size colorCount) of color indices. These indices are cast to unsigned int in the case of a discrete color map. If indices == nullptr (default value), indices are set from 0 to colorCount - 1
		* @param colorTitles	vector (of size colorCount) of color titles. Titles are not set if colorTitles is empty (default value)
		*/
		void setRgbColors(uint64_t colorCount,
			double const* rgbColors, double const* alphas = nullptr,
			double const* indices = nullptr, std::vector<std::string> const& colorTitles = std::vector<std::string>());

		/**
		* https://en.wikipedia.org/wiki/HSV_color_space
		* @param colorCount		the size (number of colors) of the color map
		* @param rgbColors		array (of size colorCount * 3) of RGB colors with hsvColors[3*i] is red componant, hsvColors[3*i + 1] is green component and hsvColors[3*i + 2] is blue component of the ith color (red, green and blue are in range [0, 255])
		* @param alphas			array (of size colorCount) of numeric values in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). If alphas == nullptr (default value), default alpha value is 1.
		* @param indices		array (of size colorCount) of color indices. These indices are cast to unsigned int in the case of a discrete color map. If indices == nullptr (default value), indices are set from 0 to colorCount - 1
		* @param colorTitles	vector (of size colorCount) of color titles. Titles are not set if colorTitles is empty (default value)
		*/
		void setRgbColors(uint64_t colorCount,
			uint8_t const* rgbColors, double const* alphas = nullptr,
			double const* indices = nullptr, std::vector<std::string> const& colorTitles = std::vector<std::string>());

		/**
		 * @brief	Gets color count
		 *
		 * @returns	The color count.
		 */
		uint64_t getColorCount() const;
		
		/**
		 * @param colorIndex	index of a color in the color map.
		 * @return				hue in the range [0, 360]
		 */
		double getHue(uint64_t colorIndex) const;

		/**
		 * @param colorIndex	index of a color in the color map.
		 * @return				saturation in the range [0, 1]
		 */
		double getSaturation(uint64_t colorIndex) const;

		/**
		 * @param colorIndex	index of a color in the color map.
		 * @return				value in the range [0, 1]
		 */
		double getValue(uint64_t colorIndex) const;

		/**
		 * @param colorIndex	index of a color in the color map.
		 * @return				alpha in the range [0, 1] (0 means transparent and 1 means opaque)
		 */
		double getAlpha(uint64_t colorIndex) const;

		/**
		 * @param colorIndex	index of a color in the color map.
		 * @param red			(output parameter) red value in the range [0, 1]
		 * @param green			(output parameter) green value in the range [0, 1]
		 * @param blue			(output parameter) blue value in the range [0, 1]
		 */
		void getRgbColor(uint64_t colorIndex, double& red, double& green, double& blue) const;

		/**
		 * @param colorIndex	index of a color in the color map.
		 * @param red			(output parameter) red value in the range [0, 255]
		 * @param green			(output parameter) green value in the range [0, 255]
		 * @param blue			(output parameter) blue value in the range [0, 255]
		 */
		void getRgbColor(uint64_t colorIndex, uint8_t& red, uint8_t& green, uint8_t& blue) const;

		/**
		 * @brief	Queries if 'colorIndex' has color title
		 *
		 * @param 	colorIndex	Zero-based index of the color.
		 *
		 * @returns	True if color title, false if not.
		 */
		bool hasColorTitle(uint64_t colorIndex) const;

		/**
		 * @brief	Gets color title
		 *
		 * @param 	colorIndex	Zero-based index of the color.
		 *
		 * @returns	The color title.
		 */
		std::string getColorTitle(uint64_t colorIndex) const;

		/**
		 * @brief	Sets the NullColor value of a continuous color map
		 *
		 * @param 	hue		  	hue in the range [0, 360].
		 * @param 	saturation	saturation in the range [0, 1].
		 * @param 	value	  	value in the range [0, 1].
		 * @param 	alpha	  	(Optional) alpha in the range [0, 1] (0 means transparent and 1 means
		 * 						opaque). Default alpha value is 1.
		 * @param 	colorTitle	(Optional) color title. It is not set if empty string (default value)
		 */
		void setNullHsvColor(double hue, double saturation, double value, double alpha = 1, std::string const& colorTitle = "");

		/**
		 * @brief	Sets the NullColor value of a continuous color map
		 *
		 * @param 	red		  	red value in the range [0, 1].
		 * @param 	green	  	green value in the range [0, 1].
		 * @param 	blue	  	blue value in the range [0, 1].
		 * @param 	alpha	  	(Optional) alpha in the range [0, 1] (0 means transparent and 1 means
		 * 						opaque). Default alpha value is 1.
		 * @param 	colorTitle	(Optional) color title. It is not set if empty string (default value)
		 */
		void setNullRgbColor(double red, double green, double blue, double alpha = 1, std::string const& colorTitle = "");

		/**
		 * @brief	Sets the NullColor value of a continuous color map
		 *
		 * @param 	red		  	red value in the range [0, 255].
		 * @param 	green	  	green value in the range [0, 255].
		 * @param 	blue	  	blue value in the range [0, 255].
		 * @param 	alpha	  	(Optional) alpha in the range [0, 1] (0 means transparent and 1 means
		 * 						opaque). Default alpha value is 1.
		 * @param 	colorTitle	(Optional) color title. It is not set if empty string (default value)
		 */
		void setNullRgbColor(uint8_t red, uint8_t green, uint8_t blue, double alpha = 1, std::string const& colorTitle = "");

		/**
		 * @brief	checks if the color map has a definition for the color of Null values.
		 */
		bool hasNullColor() const { return static_cast<gsoap_eml2_3::resqml22__ContinuousColorMap const*>(gsoapProxy2_3)->NullColor != nullptr; }

		/**
		 * @return				hue in the range [0, 360]
		 */
		double getNullHue() const;

		/**
		 * @return				saturation in the range [0, 1]
		 */
		double getNullSaturation() const;

		/**
		 * @return				value in the range [0, 1]
		 */
		double getNullValue() const;

		/**
		 * @return				alpha in the range [0, 1] (0 means transparent and 1 means opaque)
		 */
		double getNullAlpha() const;
	};
	
#if defined(SWIGPYTHON)
	%rename(Resqml2_DiscreteColorMap) DiscreteColorMap;
#endif	
	class DiscreteColorMap : public AbstractColorMap
	{
	public:

		/**
		 * @brief	Gets the location of a color of the color map
		 *
		 * @param 	colorIndex	Zero-based index of the color.
		 *
		 * @returns	The color location in the color map.
		 */
		int64_t getColorLocationInColorMap(uint64_t colorIndex) const;
	};
	
#if defined(SWIGPYTHON)
	%rename(Resqml2_ContinuousColorMap) ContinuousColorMap;
#endif	
	class ContinuousColorMap : public AbstractColorMap 
	{
	public:
		gsoap_eml2_3::resqml22__InterpolationDomain getInterpolationDomain();
		std::string getInterpolationDomainAsString();

		gsoap_eml2_3::resqml22__InterpolationMethod getInterpolationMethod();
		std::string getInterpolationMethodAsString();

		/**
		 * @brief	Gets the location of a color of the color map
		 *
		 * @param 	colorIndex	Zero-based index of the color.
		 *
		 * @returns	The color location in the color map.
		 */
		double getColorLocationInColorMap(uint64_t colorIndex) const;
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_MdDatum) MdDatum;
#endif
	class MdDatum : public COMMON_NS::AbstractObject
	{
	public:
		EML2_NS::AbstractLocal3dCrs * getLocalCrs() const;

		double getX() const;
		double getXInGlobalCrs() const;
		double getY() const;
		double getYInGlobalCrs() const;
		double getZ() const;
		double getZInGlobalCrs() const;
		
		gsoap_eml2_3::eml23__ReferencePointKind getKind() const;
	};

	class AbstractFeatureInterpretation;
#ifdef SWIGPYTHON
	%rename(Resqml2_AbstractFeature) AbstractFeature;
#endif
	class AbstractFeature : public COMMON_NS::AbstractObject
	{
	public:
		uint64_t getInterpretationCount() const;
		AbstractFeatureInterpretation* getInterpretation(uint64_t index) const;
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_AbstractTechnicalFeature) AbstractTechnicalFeature;
#endif
	class AbstractTechnicalFeature : public AbstractFeature
	{
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_BoundaryFeature) BoundaryFeature;
#endif	
	class BoundaryFeature : public AbstractFeature
	{
	};
	

#ifdef SWIGPYTHON
	%rename(Resqml2_CulturalFeature) CulturalFeature;
#endif	
	class CulturalFeature : public AbstractTechnicalFeature
	{
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_Model) Model;
#endif	
	class Model : public AbstractFeature
	{
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_RockVolumeFeature) RockVolumeFeature;
#endif	
	class RockVolumeFeature : public AbstractFeature
	{
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_SeismicLatticeFeature) SeismicLatticeFeature;
#endif
	class SeismicLatticeFeature : public AbstractTechnicalFeature
	{
	public:

		/**
		 * Gets the crossline annotated index increment between two consecutive crosslines.
		 *
		 * @returns	The crossline increment.
		 */
		int64_t getCrosslineIncrement() const;

		/**
		 * Gets the inline annotated index increment between two consecutive inlines.
		 *
		 * @returns	The inline increment.
		 */
		int64_t getInlineIncrement() const;

		/**
		 * Gets the annotated index of the first crossline.
		 *
		 * @returns	The origin crossline.
		 */
		int64_t getCrosslineOrigin() const;

		/**
		 * Gets the annotated index of the first inline.
		 *
		 * @returns	The origin inline.
		 */
		int64_t getInlineOrigin() const;
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_SeismicLineSetFeature) SeismicLineSetFeature;
#endif
	class SeismicLineSetFeature : public AbstractTechnicalFeature
	{
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_AbstractSeismicLineFeature) AbstractSeismicLineFeature;
#endif	
	class AbstractSeismicLineFeature : public AbstractTechnicalFeature
	{
	public:
		void setSeismicLineSet(SeismicLineSetFeature * seisLineSet);
		SeismicLineSetFeature* getSeismicLineSet() const;
		
		uint64_t getTraceCount() const;
		
		void setTraceLabels(const std::vector<std::string> & values, EML2_NS::AbstractHdfProxy * proxy);
		std::vector<std::string> getTraceLabels() const;
	};
	
#ifdef SWIGPYTHON
	%rename(ShotPointLineFeature_resqml2) ShotPointLineFeature;
#endif
	class ShotPointLineFeature : public AbstractSeismicLineFeature
	{
	public:
	};

#ifdef SWIGPYTHON
	%rename(CmpLineFeature_resqml2) CmpLineFeature;
#endif
	class CmpLineFeature : public AbstractSeismicLineFeature
	{
	public:
		void setShotPointLine(class ShotPointLineFeature* shotPointLine);
		ShotPointLineFeature* getShotPointLine() const;
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_WellboreFeature) WellboreFeature;
#endif
	class WellboreFeature : public AbstractTechnicalFeature
	{
	public:
		WITSML2_NS::Wellbore* getWitsmlWellbore();
		void setWitsmlWellbore(WITSML2_NS::Wellbore * wellbore);
	};

	class AbstractRepresentation;
	class AbstractFeatureInterpretation : public COMMON_NS::AbstractObject
	{
	public:

		/**
		 * Get the representation count of this interpretation.
		 *
		 * @exception	std::range_error	If the representation count is strictly greater than unsigned
		 * 									int max.
		 *
		 * @returns	The representation count.
		 */
		uint64_t						getRepresentationCount() const;

		/**
		 * Gets the feature this instance interprets
		 *
		 * @returns	A pointer to the interpreted feature.
		 */
		AbstractFeature*				getInterpretedFeature();

		/**
		 * Gets a particular representation of this interpretation according to its position in the
		 * representations ordering.
		 *
		 * @exception	std::out_of_range	If @p index is out of the range of the representation set.
		 *
		 * @param 	index	Zero-based index of the representation we look for.
		 *
		 * @returns	A pointer to the representation at @p index.
		 */
		AbstractRepresentation* 	getRepresentation(uint64_t index) const;
		
		/**
		 * Initializes the domain of the interpretation by looking at the local CRS domain of its
		 * representations.
		 *
		 * @param 	defaultDomain	The default domain to set when no representation is associated to
		 * 							this interpretation.
		 *
		 * @returns	The domain that have been set to this interpretation (either deduced from its
		 * 			representation or @p defaultDomain).
		 */
		gsoap_resqml2_0_1::resqml20__Domain initDomain(gsoap_resqml2_0_1::resqml20__Domain defaultDomain) const;

		/**
		 * Gets the domain of this interpretation.
		 *
		 * @returns	The domain of this interpretation.
		 */
		gsoap_resqml2_0_1::resqml20__Domain getDomain() const;
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_GenericFeatureInterpretation) GenericFeatureInterpretation;
#endif
	class GenericFeatureInterpretation : public AbstractFeatureInterpretation
	{
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_BoundaryFeatureInterpretation) BoundaryFeatureInterpretation;
#endif
	class BoundaryFeatureInterpretation : public AbstractFeatureInterpretation
	{
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_GeobodyBoundaryInterpretation) GeobodyBoundaryInterpretation;
#endif
	class GeobodyBoundaryInterpretation : public BoundaryFeatureInterpretation
	{
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_HorizonInterpretation) HorizonInterpretation;
#endif
	class HorizonInterpretation : public BoundaryFeatureInterpretation
	{
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_FaultInterpretation) FaultInterpretation;
#endif
	class FaultInterpretation : public BoundaryFeatureInterpretation
	{
	public:
		/**
		 * Pushes back a new throw interpretation for this fault interpretation. More than one throw
		 * kind is necessary if for example the throw is reverse at a time period and then normal at
		 * another time period.
		 *
		 * @param 	throwKind	The throw kind to push back.
		 */
		void pushBackThrowInterpretation(gsoap_resqml2_0_1::resqml20__ThrowKind throwKind);
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_FluidBoundaryInterpretation) FluidBoundaryInterpretation;
#endif
	class FluidBoundaryInterpretation : public BoundaryFeatureInterpretation
	{
	public:
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_GeobodyInterpretation) GeobodyInterpretation;
#endif
	class GeobodyInterpretation : public AbstractFeatureInterpretation
	{
	public :
		void set3dShape(gsoap_eml2_3::resqml22__Shape3d geobody3dShape);
		bool has3dShape() const;
		gsoap_eml2_3::resqml22__Shape3d get3dShape() const;
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_StratigraphicUnitInterpretation) StratigraphicUnitInterpretation;
#endif
	class StratigraphicUnitInterpretation : public AbstractFeatureInterpretation
	{
	public:
		bool hasDepositionMode() const;
		gsoap_resqml2_0_1::resqml20__DepositionMode getDepositionMode() const;
	};
	
	#ifdef SWIGPYTHON
	%rename(Resqml2_AbstractOrganizationInterpretation) AbstractOrganizationInterpretation;
	#endif
	class AbstractOrganizationInterpretation : public AbstractFeatureInterpretation
	{
	public:
		/**
		* Indicates if this instance is a structural one.
		*/
		bool isStructural() const;

		/**
		* Indicates if this instance is a structural one.
		*/
		bool isStratigraphic() const;

		/**
		* Indicates if this instance is a structural one.
		*/
		bool isRockFluid() const;
		
		/**
		 * Adds a binary contact to this organization interpretation by means of a simple sentence.
		 *
		 * @exception	std::invalid_argument	If @p subject or @p directObject is @c nullptr.
		 *
		 * @param [in]	subject			The subject of the sentence that defines how the contact was
		 * 								constructed.
		 * @param 	  	verb			The verb of the sentence that defines how the contact was
		 * 								constructed.
		 * @param [in]	directObject	The direct object of the sentence that defines how the contact
		 * 								was constructed.
		 */
		void pushBackBinaryContact(AbstractFeatureInterpretation* subject, gsoap_eml2_3::resqml22__ContactVerb verb, AbstractFeatureInterpretation* directObject);

		/**
		 * Adds a binary contact to this organization interpretation by means of a simple sentence.
		 *
		 * @exception	std::invalid_argument	If @p subject or @p directObject is @c nullptr.
		 *
		 * @param [in]	subject			The subject of the sentence that defines how the contact was
		 * 								constructed.
		 * @param 	  	verb			The verb of the sentence that defines how the contact was
		 * 								constructed.
		 * @param [in]	directObject	The direct object of the sentence that defines how the contact
		 * 								was constructed.
		 * @param [in]	partOf			indicates the interpertation this contact is part of
		 */
		void pushBackBinaryContact(AbstractFeatureInterpretation* subject, gsoap_eml2_3::resqml22__ContactVerb verb, AbstractFeatureInterpretation* directObject, AbstractFeatureInterpretation* partOf);
		
		
		/**
		 * Adds a binary contact to the organization interpretation by means of a sentence where the
		 * direct object can be qualified.
		 *
		 * @exception	std::invalid_argument	If @p subject or @p directObject is @c nullptr.
		 *
		 * @param [in]	subject				 	The subject of the sentence that defines how the contact
		 * 										was constructed.
		 * @param 	  	verb				 	The verb of the sentence that defines how the contact was
		 * 										constructed.
		 * @param [in]	directObject		 	The direct object of the sentence that defines how the
		 * 										contact was constructed.
		 * @param 	  	directObjectQualifier	The direct object qualifier defining its contact side
		 * 										(footwall, hanging wall, north, south, etc.).
		 */
		void pushBackBinaryContact(AbstractFeatureInterpretation* subject, gsoap_eml2_3::resqml22__ContactVerb verb, AbstractFeatureInterpretation* directObject,
			gsoap_resqml2_0_1::resqml20__ContactSide directObjectQualifier);
			
		/**
		 * Adds a binary contact to the organization interpretation by means of a sentence where both
		 * the subject and the direct object can be qualified.
		 *
		 * @exception	std::invalid_argument	If @p subject or @p directObject is @c nullptr.
		 *
		 * @param [in]	subject				 	The subject of the sentence that defines how the contact
		 * 										was constructed.
		 * @param 	  	subjectQualifier	 	The subject qualifier defining its contact side (footwall,
		 * 										hanging wall, north, south, etc.).
		 * @param 	  	verb				 	The verb of the sentence that defines how the contact was
		 * 										constructed.
		 * @param [in]	directObject		 	The direct object of the sentence that defines how the
		 * 										contact was constructed.
		 * @param 	  	directObjectQualifier	The direct object qualifier defining its contact side
		 * 										(footwall, hanging wall, north, south, etc.).
		 */
		void pushBackBinaryContact(AbstractFeatureInterpretation* subject, gsoap_resqml2_0_1::resqml20__ContactSide subjectQualifier,
			gsoap_eml2_3::resqml22__ContactVerb verb,
			AbstractFeatureInterpretation* directObject, gsoap_resqml2_0_1::resqml20__ContactSide directObjectQualifier);
	};
	
	#ifdef SWIGPYTHON
	%rename(Resqml2_AbstractStratigraphicOrganizationInterpretation) AbstractStratigraphicOrganizationInterpretation;
	#endif
	class AbstractGridRepresentation;
	class AbstractStratigraphicOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	public:
		unsigned int getGridRepresentationCount() const;
		AbstractGridRepresentation* getGridRepresentation(unsigned int index) const;
		bool isAssociatedToGridRepresentation(AbstractGridRepresentation* gridRep) const;
	};
	
	class StratigraphicOccurrenceInterpretation;	
#ifdef SWIGPYTHON
	%rename(Resqml2_StratigraphicColumnRankInterpretation) StratigraphicColumnRankInterpretation;
#endif
	class StratigraphicColumnRankInterpretation : public AbstractStratigraphicOrganizationInterpretation
	{
	public:
		void pushBackStratiUnitInterpretation(StratigraphicUnitInterpretation * stratiUnitInterpretation);
		void pushBackStratigraphicBinaryContact(StratigraphicUnitInterpretation* subject, gsoap_eml2_3::resqml22__ContactMode subjectContactMode,
			StratigraphicUnitInterpretation* directObject, gsoap_eml2_3::resqml22__ContactMode directObjectMode,
			HorizonInterpretation * partOf = nullptr);
			
		unsigned int getContactCount() const;
		gsoap_eml2_3::resqml22__ContactMode getSubjectContactModeOfContact(unsigned int contactIndex) const;
		gsoap_eml2_3::resqml22__ContactMode getDirectObjectContactModeOfContact(unsigned int contactIndex) const;
		HorizonInterpretation* getHorizonInterpretationOfContact(unsigned int contactIndex) const;
		bool isAChronoStratiRank() const;
		StratigraphicUnitInterpretation* getSubjectOfContact(unsigned int contactIndex) const;
		StratigraphicUnitInterpretation* getDirectObjectOfContact(unsigned int contactIndex) const;
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::StratigraphicUnitInterpretation, StratigraphicUnitInterpretation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::StratigraphicOccurrenceInterpretation, StratigraphicOccurrenceInterpretation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::HorizonInterpretation, HorizonInterpretation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::StratigraphicColumn, StratigraphicColumn)
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_StratigraphicOccurrenceInterpretation) StratigraphicOccurrenceInterpretation;
#endif
	class StratigraphicOccurrenceInterpretation : public AbstractStratigraphicOrganizationInterpretation
	{
	public:
		void setStratigraphicColumnRankInterpretation(StratigraphicColumnRankInterpretation * stratiColumnRankInterp);
		StratigraphicColumnRankInterpretation * getStratigraphicColumnRankInterpretation() const;
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::WellboreMarkerFrameRepresentation, WellboreMarkerFrameRepresentation)
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_StratigraphicColumn) StratigraphicColumn;
#endif
	class StratigraphicColumn : public COMMON_NS::AbstractObject
	{
	public:
		void pushBackStratiColumnRank(StratigraphicColumnRankInterpretation * stratiColumnRank);
		unsigned int getStratigraphicColumnRankInterpretationCount() const;
		StratigraphicColumnRankInterpretation* getStratigraphicColumnRankInterpretation(unsigned int index) const;
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_RockFluidUnitInterpretation) RockFluidUnitInterpretation;
#endif	
	class RockFluidUnitInterpretation : public AbstractFeatureInterpretation
	{
	public:
		/**
		 * Indicates if this instance has a phase information.
		 *
		 * @returns	True if there exists a phase information, false if not.
		 */
		bool hasPhase() const;

		/**
		 * Gets the phase information of this rock fluid unit interpretation.
		 *
		 * @exception	std::logic_error	If no phase information exists in this rock fluid unit
		 * 									interpretation (please use hasPhase() before calling this
		 * 									method).  
		 *
		 * @returns	The phase of this rock fluid unit interpretation.
		 */
		gsoap_eml2_3::resqml22__Phase getPhase() const;

		/**
		 * Sets the phase information of this rock fluid unit interpretation.
		 *
		 * @param phase	The phase of this rock fluid unit interpretation.
		 */
		void setPhase(gsoap_eml2_3::resqml22__Phase phase) const;
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_RockFluidOrganizationInterpretation) RockFluidOrganizationInterpretation;
#endif
	class RockFluidOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	public:
		/**
		 * Gets the count of grid representations associated to this rock fluid organization.
		 *
		 * @exception	std::range_error	If the count of associated grid representations is strictly
		 * 									greater than unsigned int max.
		 *
		 * @returns	The count of grid representations associated to this rock fluid organization.
		 */
		uint64_t getGridRepresentationCount() const;

		/**
		 * Gets a grid representation associated to this rock fluid organization by means of its index.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getGridRepresentationCount().
		 *
		 * @param 	index	Zero-based index of the grid representation to get in the array of grid
		 * 					representations of this rock fluid organization.
		 *
		 * @returns	The associated grid representation at position @p index.
		 */
		AbstractGridRepresentation* getGridRepresentation(uint64_t index) const;

		/**
		 * Checks whether a given grid representation is associated to this rock fluid organization.
		 *
		 * @param [in]	gridRep	The grid representation for which we want to know if it is associated to
		 * 						this rock fluid organization.
		 *
		 * @returns	True if @p gridRep is associated to this rock fluid organization, false if not.
		 */
		bool isAssociatedToGridRepresentation(AbstractGridRepresentation* gridRep) const;

		/**
		 * Pushes back a rock fluid unit interpretation in this rock fluid organization.
		 *
		 * @exception	std::invalid_argument	If <tt>rockFluidUnitInterpretation == nullptr</tt>.
		 *
		 * @param [in]	rockFluidUnitInterpretation	The rock fluid unit interpretation to push back.
		 */
		void pushBackRockFluidUnitInterpretation(RockFluidUnitInterpretation* rockFluidUnitInterpretation);

		/**
		 * Gets the count of rock fluid unit interpretations of this rock fluid organization.
		 *
		 * @returns	The count of rock fluid unit interpretations of this rock fluid organization.
		 */
		uint64_t getRockFluidUnitInterpCount() const;

		/**
		 * Gets a rock fluid unit interpretation of this rock fluid organization by means of
		 * its index.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getRockFluidUnitInterpCount().
		 *
		 * @param 	index	Zero-based index of the rock fluid unit interpretation we look for.
		 *
		 * @returns	The rock fluid unit interpretation at position @p index.
		 */
		RockFluidUnitInterpretation* getRockFluidUnitInterpretation(uint64_t index) const;
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_StructuralOrganizationInterpretation) StructuralOrganizationInterpretation;
#endif
	class StructuralOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	public:
		void pushBackFaultInterpretation(FaultInterpretation * faultInterpretation);
		void pushBackHorizonInterpretation(HorizonInterpretation * horizonInterpretation, const int & stratigraphicRank);
		void pushBackTopFrontierInterpretation(AbstractFeatureInterpretation * topFrontierInterpretation);
        void pushBackBottomFrontierInterpretation(AbstractFeatureInterpretation * bottomFrontierInterpretation);
        void pushBackSideFrontierInterpretation(AbstractFeatureInterpretation * sideFrontierInterpretation);
		
		unsigned int getFaultInterpretationCount() const;
		FaultInterpretation* getFaultInterpretation(unsigned int index);
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_EarthModelInterpretation) EarthModelInterpretation;
#endif
	class EarthModelInterpretation : public AbstractFeatureInterpretation
	{
	public:
		unsigned int getStructuralOrganizationInterpretationCount() const;
		StructuralOrganizationInterpretation* getStructuralOrganizationInterpertation(unsigned int index) const;
		void pushBackStructuralOrganizationInterpretation(StructuralOrganizationInterpretation * structOrganization);
		
		bool hasStratiColumn() const;
		void setStratiColumn(StratigraphicColumn * stratiColumn);
		StratigraphicColumn* getStratiColumn() const;
		
		unsigned int getStratiOccurrenceCount() const;
		StratigraphicOccurrenceInterpretation* getStratiOccurrence(unsigned int index) const;
		void pushBackStratiOccurrence(StratigraphicOccurrenceInterpretation * stratiOccurence);
		
		unsigned int getRockFluidOrganizationInterpretationCount() const;
		void pushBackRockFluidOrganizationInterpretation(RockFluidOrganizationInterpretation* rockFluid);
		RockFluidOrganizationInterpretation* getRockFluidOrganizationInterpretation(unsigned int index) const;
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_WellboreInterpretation) WellboreInterpretation;
#endif
	class WellboreInterpretation : public AbstractFeatureInterpretation
	{
	public:
		bool isDrilled() const;
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::WellboreTrajectoryRepresentation, WellboreTrajectoryRepresentation);
	};

	//************************************/
	//************ REPRESENTATION ********/
	//************************************/
	
	class AbstractValuesProperty;
	class PointsProperty;
	class RepresentationSetRepresentation;
	class SubRepresentation;
#ifdef SWIGPYTHON
	%rename(Resqml2_AbstractRepresentation) AbstractRepresentation;
#endif
	class AbstractRepresentation : public COMMON_NS::AbstractObject
	{
	public:
		/** 
		 * Gets the interpretation associated to this representation.
		 *
		 * @returns Null pointer if no interpretation is associated to this representation. Otherwise
		 * 			the associated interpretation.
		 */
		AbstractFeatureInterpretation* getInterpretation() const;
		
		/**
		 * Gets the local 3d CRS associated to a given patch of this representation in read and write
		 * access.
		 * 
		 * @exception std::out_of_range	If @p patchIndex is out of range.
		 * 								
		 * @param patchIndex	Zero-based index of the patch for which we look for the local CRS.
		 * 						
		 * @returns Null if it fails, else the local CRS associated to the @p patchIndex patch.
		 */
		EML2_NS::AbstractLocal3dCrs * getLocalCrs(uint64_t patchIndex);
		
		/**
		 * Set a time index in a time series for all point geometries of all existing patches of this representation.
		 *
		 * @param 	timeIndex	The time index of the time to associate to this representation.
		 * @param 	timeSeries	The time series containing the time of the representation at @p timeIndex.
		 */
		void setTimeIndex(uint64_t timeIndex, EML2_NS::TimeSeries* timeSeries);
		
		/**
		 * @brief Gets the time index of this representation in the associated TimeSeries.
		 *		Be sure to first check that a TimeSeries is associated this representation by calling getTimeSeriesDor or getTimeSeries;
		 *
		 * @exception	std::logic_error	If this representation is partial. Or if the representation is not associated to any TimeSeries.
		 *
		 * @returns	The time index of this representation in the associated TimeSeries.
		 */
		uint64_t getTimeIndex() const;
		/**
		 * Gets the TimeSeries associated to this representation.
		 *
		 * @returns Null if it fails, else the TimeSeries associated to this representation.
		 */
		EML2_NS::TimeSeries* getTimeSeries() const;
		
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::AbstractValuesProperty, ValuesProperty)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PointsProperty, PointsProperty)
		
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::SubRepresentation, SubRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::SubRepresentation, FaultSubRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::RepresentationSetRepresentation, RepresentationSetRepresentation)

		/**
		 * Get the xyz point count in a given patch of this representation.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of range.
		 * @exception	std::logic_error 	If this representation is partial.
		 *
		 * @param 	patchIndex	Zero-based index of the patch from which we look for the xyz points.
		 *
		 * @returns	The xyz point count of the patch at position @p patchIndex.
		 */
		uint64_t getXyzPointCountOfPatch(unsigned int patchIndex) const;
		
		/**
		 * Get the xyz point count of all patches of this representation.
		 *
		 * @returns	The xyz point count of all patches.
		 */
		uint64_t getXyzPointCountOfAllPatches() const;
		
		/**
		 * @brief	Gets all the xyz points of a particular patch of this representation. xyz points are
		 * 			given in the local CRS.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of range.
		 * @exception	std::logic_error 	If this representation is partial.
		 *
		 * @param 	   	patchIndex	Zero-based index of the patch from which we look for the xyz points.
		 * @param [out]	xyzPoints 	A linearized 2d array where the first (quickest) dimension is the
		 * 							coordinate dimension (x, y or z) and second dimension is vertex
		 * 							dimension. It must be preallocated with a size of <tt>3 *
		 * 							getXyzPointCountOfPatch(patchIndex)</tt>.
		 */
		void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const;
		
		/**
		 * @brief Gets all the xyz points of a particular patch of this representation. xyz points are given in
		 * the global CRS.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of range.
		 *
		 * @param 	   	patchIndex	Zero-based index of the patch from which we look for the xyz points.
		 * @param [out]	xyzPoints 	A linearized 2d array where the first (quickest) dimension is the
		 * 							coordinate dimension (x, y or z) and second dimension is vertex
		 * 							dimension. It must be preallocated with a size of <tt>3 *
		 * 							getXyzPointCountOfPatch(patchIndex)</tt>.
		 */
		void getXyzPointsOfPatchInGlobalCrs(unsigned int patchIndex, double * xyzPoints) const;
		
		/**
		 * @brief Gets all the xyz points of all patches of this representation. xyz points are given in the
		 * local CRS.
		 *
		 * @param [out]	xyzPoints	A linearized 2d array where the first (quickest) dimension is the
		 * 							coordinate dimension (x, y or z) and second dimension is vertex
		 * 							dimension. It must be preallocated with a size of <tt>3 *
		 * 							getXyzPointCountOfAllPatches()</tt>.
		 */
		void getXyzPointsOfAllPatches(double * xyzPoints) const;
		
		/**
		 * Checks if all of the patches (geometries) of this representation are defined in a same local
		 * CRS.
		 *
		 * @returns	True if this representation is defined in a single local CRS, false if not.
		 */
		bool isInSingleLocalCrs() const;
		
		/**
		 * Checks if all of the patches (geometries) of this representation are defined in a same global
		 * CRS.
		 *
		 * @returns	True if this representation is defined in a single global CRS, false if not.
		 */
		bool isInSingleGlobalCrs() const;
		
		/**
		 * Gets all the xyz points of all patches of this individual representation. xyz points are
		 * given in the global CRS.
		 *
		 * @param [out]	xyzPoints	A linearized 2d array where the first (quickest) dimension is the
		 * 							coordinate dimension (x, y or Z) and second dimension is vertex
		 * 							dimension. Thus, its size is 3*(3*[count of all xyz points]). It must
		 * 							be preallocated.
		 */
		void getXyzPointsOfAllPatchesInGlobalCrs(double * xyzPoints) const;
		
		/**
		 * Gets the patch count.
		 *
		 * @returns	The patch count.
		 */
		uint64_t getPatchCount() const;
		
		/**
		 * Gets the seismic support of a specific patch of this representation.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of the patch count range.
		 *
		 * @param 	patchIndex	Zero-based index of the patch from which we look for the seismic support.
		 *
		 * @returns	Null if no seismic information have been provided for the patch at position @p
		 * 			patchIndex. Else, its seismic support.
		 */
		AbstractRepresentation* getSeismicSupportOfPatch(unsigned int patchIndex);
		
		/**
		 * Gets all the abscissa of the points of a specific patch related to 2d seismic line.
		 *
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 * @exception	std::invalid_argument	If the patch at position @p patchIndex has no seismic
		 * 										information.
		 *
		 * @param 	   	patchIndex	The index of the geometry patch which stores the seismic coordinates.
		 * @param [out]	values	  	The array where the abscissa are going to be stored. The count of
		 * 							this array must be equal to <tt>getXyzPointCountOfPatch(patchIndex)</tt>.
		 */
		void getSeismicLineAbscissaOfPointsOfPatch(unsigned int patchIndex, double* values) const;
		
		/**
		 * Adds seismic 2d coordinates to an existing point geometry patch.
		 *
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 * @exception	std::invalid_argument	If @p patchIndex does not identify a point geometry patch.
		 * @exception	std::invalid_argument	If there already exists some seismic 3d coordinates for
		 * 										the geometry patch at position @p patchIndex.
		 *
		 * @param 		  	patchIndex	  	The index of the geometry patch which receives the seismic
		 * 									coordinates.
		 * @param [in,out]	lineAbscissa  	The abscissa of each points of the patch on the seismic line.
		 * 									The count of this array must be equal to
		 * 									<tt>getXyzPointCountOfPatch(patchIndex)</tt>.
		 * @param [in,out]	seismicSupport	The representation of the seismic line.
		 * @param [in,out]	proxy		  	The HDF proxy where to write the @p lineAbscissa values. It
		 * 									must be already opened for writing and won't be closed in
		 * 									this method.
		 */
		void addSeismic2dCoordinatesToPatch(unsigned int patchIndex, double * lineAbscissa,
			AbstractRepresentation * seismicSupport, EML2_NS::AbstractHdfProxy * proxy);
		
		/**
		 * Gets all the inline coordinates of the points of a specific patch related to seismic lattice.
		 *
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 * @exception	std::invalid_argument	If the patch at position @p patchIndex has no seismic
		 * 										information.
		 *
		 * @param 	   	patchIndex	The index of the geometry patch which stores the seismic coordinates.
		 * @param [out]	values	  	The array where the inlines coordinates are going to be stored. The
		 * 							count of this array must be equal to
		 * 							<tt>getXyzPointCountOfPatch(patchIndex)</tt>.
		 */
		void getInlinesOfPointsOfPatch(unsigned int patchIndex, double * values) const;
		
		/**
		 * Gets all the crossline coordinates of the points of a specific patch related to seismic
		 * lattice.
		 *
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 * @exception	std::invalid_argument	If the patch at position @p patchIndex has no seismic
		 * 										information.
		 *
		 * @param 	   	patchIndex	The index of the geometry patch which stores the seismic coordinates.
		 * @param [out]	values	  	The array where the crossline coordinates are going to be stored. The
		 * 							count of this array must be equal to
		 * 							<tt>getXyzPointCountOfPatch(patchIndex)</tt>.
		 */
		void getCrosslinesOfPointsOfPatch(unsigned int patchIndex, double * values) const;
		
		/**
		 * Adds seismic 3d coordinates to an existing point geometry patch.
		 *
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 * @exception	std::invalid_argument	If @p patchIndex does not identify a point geometry patch.
		 * @exception	std::invalid_argument	If there already exists some seismic 2d coordinates for
		 * 										the geometry patch at position @p patchIndex.
		 *
		 * @param 		   	patchIndex	  	The index of the geometry patch which receives the seismic
		 * 									coordinates.
		 * @param [in]	   	inlines		  	The sequence of trace or inter-trace inline positions that
		 * 									correspond to the geometry coordinates. It must be in the
		 * 									same order than @p crosslines.
		 * @param [in]	   	crosslines	  	The sequence of trace or inter-trace crossline positions that
		 * 									correspond to the geometry coordinates. It must be in the
		 * 									same order than @p inlines.
		 * @param 		   	pointCount	  	Number of points. It is the size of both @p inlines and @p
		 * 									crosslines.
		 * @param [in]	   	seismicSupport	The representation of the seismic line.
		 * @param [in, out]	proxy		  	The HDF proxy where to write the @p inlines and @p crosslines
		 * 									values. It must be already opened for writing and won't be
		 * 									closed in this method.
		 */
		void addSeismic3dCoordinatesToPatch(unsigned int patchIndex, double * inlines, double * crosslines, uint64_t pointCount,
			AbstractRepresentation * seismicSupport, EML2_NS::AbstractHdfProxy * proxy);

		/**
		 * Adds seismic 3d coordinates to an existing point geometry patch.
		 *
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 * @exception	std::invalid_argument	If @p patchIndex does not identify a point geometry patch.
		 * @exception	std::invalid_argument	If there already exists some seismic 2d coordinates for
		 * 										the geometry patch at position @p patchIndex.
		 *
		 * @param 	  	patchIndex	  	The index of the geometry patch which receives the seismic
		 * 								coordinates.
		 * @param 	  	startInline   	The first inline.
		 * @param 	  	incrInline	  	The inline increment.
		 * @param 	  	countInline   	The inline count.
		 * @param 	  	startCrossline	The first crossline.
		 * @param 	  	incrCrossline 	The crossline increment.
		 * @param 	  	countCrossline	The crossline count.
		 * @param [in]	seismicSupport	The representation of the seismic line.
		 */
		void addSeismic3dCoordinatesToPatch(unsigned int patchIndex, double startInline, double incrInline, unsigned int countInline,
			double startCrossline, double incrCrossline, unsigned int countCrossline,
			AbstractRepresentation * seismicSupport);

		/**
		 * Pushes back this representation into a representation set representation.
		 *
		 * @exception	std::invalid_argument	If @p repSet is null.
		 *
		 * @param [in]	repSet	The representation set representation which will contain this
		 * 							representation.
		 */
		void pushBackIntoRepresentationSet(RepresentationSetRepresentation * repSet);
	};
	
	class PolylineRepresentation;	
#ifdef SWIGPYTHON
	%rename(Resqml2_AbstractSurfaceRepresentation) AbstractSurfaceRepresentation;
#endif
	class AbstractSurfaceRepresentation : public AbstractRepresentation
	{
	public:
		void setSurfaceRole(gsoap_resqml2_0_1::resqml20__SurfaceRole surfaceRole);
		gsoap_resqml2_0_1::resqml20__SurfaceRole getSurfaceRole() const;
		void pushBackOuterRing(PolylineRepresentation * outerRing);
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_Grid2dRepresentation) Grid2dRepresentation;
#endif
	class Grid2dRepresentation : public AbstractSurfaceRepresentation
	{
	public:
		uint64_t getNodeCountAlongIAxis() const;
		uint64_t getNodeCountAlongJAxis() const;
		
		double getXOrigin() const;
		double getYOrigin() const;
		double getZOrigin() const;
		double getXOriginInGlobalCrs() const;
		double getYOriginInGlobalCrs() const;
		double getZOriginInGlobalCrs() const;
		double getXJOffset() const;
		double getYJOffset() const;
		double getZJOffset() const;
		double getXJOffsetInGlobalCrs() const;
		double getYJOffsetInGlobalCrs() const;
		double getZJOffsetInGlobalCrs() const;
		double getXIOffset() const;
		double getYIOffset() const;
		double getZIOffset() const;
		double getXIOffsetInGlobalCrs() const;
		double getYIOffsetInGlobalCrs() const;
		double getZIOffsetInGlobalCrs() const;
		bool isJSpacingConstant() const;
		bool isISpacingConstant() const;
		void getJSpacing(double* const jSpacings) const;
		double getJSpacing() const;
		void getISpacing(double* const iSpacings) const;
		double getISpacing() const;
		
		void getZValues(double * values) const;
		void getZValuesInGlobalCrs(double * values) const;

		/**
		 * Gets the index of the origin of the current geometry on the supporting representation. The
		 * index is given by means of the formula <tt>iOrigin + jOrigin *
		 * iNodeCountOnSupportingRepresentation</tt>
		 *
		 * @exception	std::logic_error	If no supporting representation is associated to this 2d grid
		 * 									representation.
		 *
		 * @returns	The index of the origin on the supporting representation.
		 */
		uint64_t getIndexOriginOnSupportingRepresentation() const;

		/**
		 * Gets the index of the origin of the current geometry on a particular dimension of the
		 * supporting representation.
		 *
		 * @exception	std::logic_error	 	If no supporting representation is associated to this 2d
		 * 										grid representation.
		 * @exception	std::invalid_argument	If @p dimension differs from @c 0 or @c 1.
		 *
		 * @param 	dimension	The dimension for which we look for the index of the origin. It can be @c
		 * 						0 for J (slowest) dimension or @c 1 for I (fastest) dimension.
		 *
		 * @returns	The index of the origin on the supporting representation on the dimension @p dimension.
		 */
		int getIndexOriginOnSupportingRepresentation(unsigned int dimension) const;

		/**
		 * Gets the number of nodes of the current geometry which is extracted from a particular
		 * dimension of the supporting representation.
		 *
		 * @exception	std::logic_error 	If no supporting representation is associated to this 2d grid
		 * 									representation.
		 * @exception	std::out_of_range	If @p dimension is out of range.
		 *
		 * @param 	dimension	The dimension for which we look for the number of nodes.
		 *
		 * @returns	The number of nodes on the dimension @p dimension.
		 */
		uint64_t getNodeCountOnSupportingRepresentation(unsigned int dimension) const;
		
		/**
		 * @brief	Gets the index offset of the nodes of the current geometry on a particular dimension
		 * 			of the supporting representation.
		 *
		 * @exception	std::logic_error 	If no supporting representation is associated to this 2d grid
		 * 									representation.
		 * @exception	std::out_of_range	If @p dimension is out of range.
		 *
		 * @param 	dimension	The dimension for which we look for the index offset.
		 *
		 * @returns	The index offset on the dimension @p dimension.
		 */
		int64_t getIndexOffsetOnSupportingRepresentation(unsigned int dimension) const;
		
		void setGeometryAsArray2dOfLatticePoints3d(
			unsigned int numPointsInFastestDirection, unsigned int numPointsInSlowestDirection,
			double xOrigin, double yOrigin, double zOrigin,
			double xOffsetInFastestDirection, double yOffsetInFastestDirection, double zOffsetInFastestDirection,
			double xOffsetInSlowestDirection, double yOffsetInSlowestDirection, double zOffsetInSlowestDirection,
			double spacingInFastestDirection, double spacingInSlowestDirection, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		void setGeometryAsArray2dOfExplicitZ(
			double * zValues,
			unsigned int numI, unsigned int numJ, EML2_NS::AbstractHdfProxy* proxy,
			Grid2dRepresentation * supportingGrid2dRepresentation, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr,
			unsigned int startIndexI = 0, unsigned int startIndexJ = 0,
			int indexIncrementI = 1, int indexIncrementJ = 1);

		void setGeometryAsArray2dOfExplicitZ(
			double * zValues,
			unsigned int numI, unsigned int numJ, EML2_NS::AbstractHdfProxy* proxy,
			double originX, double originY, double originZ,
			double offsetIX, double offsetIY, double offsetIZ, double spacingI,
			double offsetJX, double offsetJY, double offsetJZ, double spacingJ, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);
		
		Grid2dRepresentation*  getSupportingRepresentation();
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_PolylineSetRepresentation) PolylineSetRepresentation;
#endif
	class PolylineSetRepresentation : public AbstractRepresentation
	{
	public:
		uint64_t getPolylineCountOfPatch(uint64_t patchIndex) const;
		uint64_t getPolylineCountOfAllPatches() const;
		void getNodeCountPerPolylineInPatch(unsigned int patchIndex, unsigned int * nodeCountPerPolyline) const;
		void getNodeCountPerPolylineOfAllPatches(unsigned int * nodeCountPerPolyline) const;
		void pushBackGeometryPatch(
			unsigned int * nodeCountPerPolyline, double * nodes,
			uint64_t polylineCount, bool allPolylinesClosedFlag,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, EML2_NS::AbstractLocal3dCrs* localCrs = nullptr);

		void pushBackGeometryPatch(
			unsigned int * nodeCountPerPolyline, double * nodes,
			uint64_t polylineCount, bool * polylineClosedFlags,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, EML2_NS::AbstractLocal3dCrs* localCrs = nullptr);
				
		bool areAllPolylinesClosedOfPatch(unsigned int patchIndex) const;
		bool areAllPolylinesClosedOfAllPatches() const;
		bool areAllPolylinesNonClosedOfPatch(unsigned int patchIndex) const;
		bool areAllPolylinesNonClosedOfAllPatches() const;
		void getClosedFlagPerPolylineOfPatch(unsigned int patchIndex, bool * closedFlagPerPolyline) const;
		void getClosedFlagPerPolylineOfAllPatches(bool * closedFlagPerPolyline) const;
		bool hasALineRole() const;
		gsoap_eml2_3::resqml22__LineRole getLineRole() const;
		void setLineRole(gsoap_eml2_3::resqml22__LineRole lineRole);
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_PointSetRepresentation) PointSetRepresentation;
#endif
	class PointSetRepresentation : public AbstractRepresentation
	{
	public:
		/**
		 * Pushes back a new patch of XYZ points.
		 *
		 * @exception	std::invalid_argument	If <tt>proxy == nullptr</tt> and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If <tt>localCrs == nullptr</tt> and no default local CRS
		 * 										is defined in the repository.
		 *
		 * @param 		  	xyzPointCount	The xyz points count in this patch.
		 * @param [in]	  	xyzPoints	 	The xyz values of the points of the patch. Ordered by xyz and
		 * 									then by @p xyzPointCount. Size is <tt>3 * xyzPointCount</tt>.
		 * @param [in,out]	proxy		 	(Optional) The HDF proxy which defines where the xyz points
		 * 									will be stored. If @c nullptr (default), then the repository
		 * 									default HDF proxy will be used.
		 * @param [in]	  	localCrs	 	(Optional) The local CRS where the points are given. If @c
		 * 									nullptr (default), then the repository default local CRS will
		 * 									be used.
		 */
		virtual void pushBackXyzGeometryPatch(
			uint64_t xyzPointCount, double const * xyzPoints,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr) = 0;

		/**
		 * Pushes back a new patch of XY points.
		 *
		 * @exception	std::invalid_argument	If <tt>proxy == nullptr</tt> and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If <tt>localCrs == nullptr</tt> and no default local CRS
		 * 										is defined in the repository.
		 *
		 * @param 		  	xyPointCount	The xy points count in this patch.
		 * @param [in]	  	xyPoints	 	The xy values of the points of the patch. Ordered by xy and
		 * 									then by @p xyPointCount. Size is <tt>2 * xyPointCount</tt>.
		 * @param [in,out]	proxy		 	(Optional) The HDF proxy which defines where the xy points
		 * 									will be stored. If @c nullptr (default), then the repository
		 * 									default HDF proxy will be used.
		 * @param [in]	  	localCrs	 	(Optional) The local CRS where the points are given. If @c
		 * 									nullptr (default), then the repository default local CRS will
		 * 									be used.
		 */
		virtual void pushBackXyGeometryPatch(
			uint64_t xyPointCount, double const* xyPoints,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, EML2_NS::AbstractLocal3dCrs* localCrs = nullptr) = 0;

		/**
		 * Check if a point set representation patch is in 2 dimensions (i.e XY) instead of 3 dimensions (i.e XYZ)
		 * 
		 * @param [in]	  	patchIndex	 	The index of the patch 
		 */
		virtual bool isIn2D(uint64_t patchIndex) const = 0;
		
		/**
		 * Get all the XY points of a particular patch of this representation. XY points are given in
		 * the local CRS. You probably want to check first if the patch in in 2D using method bool isIn2D(uint64_t patchIndex).
		 *
		 * @param 		  	patchIndex	Zero-based index of the patch.
		 * @param [in,out]	xyPoints 	A linearized 2d array where the first (quickest) dimension is
		 * 								coordinate dimension (XY) and second dimension is vertex
		 * 								dimension. It must be pre allocated.
		 */
		virtual void getXyPointsOfPatch(uint64_t patchIndex, double* xyPoints) const = 0;
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_PlaneSetRepresentation) PlaneSetRepresentation;
#endif
	class PlaneSetRepresentation : public AbstractRepresentation
	{
	public:
		void pushBackHorizontalPlaneGeometryPatch(double zCoordinate, EML2_NS::AbstractLocal3dCrs* localCrs = nullptr);

		void pushBackTiltedPlaneGeometryPatch(
			double x1, double y1, double z1,
			double x2, double y2, double z2,
			double x3, double y3, double z3,
			EML2_NS::AbstractLocal3dCrs* localCrs = nullptr);
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_PolylineRepresentation) PolylineRepresentation;
#endif
	class PolylineRepresentation : public AbstractRepresentation
	{
	public:
		void setGeometry(double * points, unsigned int pointCount, EML2_NS::AbstractHdfProxy* proxy = nullptr, EML2_NS::AbstractLocal3dCrs* localCrs = nullptr);
		bool isClosed() const;
		bool hasALineRole() const;
		gsoap_eml2_3::resqml22__LineRole getLineRole() const;
		void setLineRole(gsoap_eml2_3::resqml22__LineRole lineRole);
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_TriangulatedSetRepresentation) TriangulatedSetRepresentation;
#endif
	class TriangulatedSetRepresentation : public AbstractSurfaceRepresentation
	{
	public:
		uint64_t getTriangleCountOfPatch(unsigned int patchIndex) const;
		uint64_t getTriangleCountOfAllPatches() const;
		void getTriangleNodeIndicesOfPatch(unsigned int patchIndex, unsigned int * triangleNodeIndices) const;
		void getTriangleNodeIndicesOfAllPatches(unsigned int * triangleNodeIndices) const;
		void pushBackTrianglePatch(unsigned int nodeCount, double * nodes, unsigned int triangleCount, unsigned int * triangleNodeIndices, EML2_NS::AbstractHdfProxy* proxy = nullptr, EML2_NS::AbstractLocal3dCrs* localCrs = nullptr);
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_RepresentationSetRepresentation) RepresentationSetRepresentation;
#endif	
	class RepresentationSetRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:
		bool isHomogeneous() const;
		uint64_t 						getRepresentationCount() const;
		AbstractRepresentation*			getRepresentation(uint64_t index) const;
	};
		
#ifdef SWIGPYTHON
	%rename(Resqml2_AbstractSurfaceFrameworkRepresentation) AbstractSurfaceFrameworkRepresentation;
#endif
	class AbstractSurfaceFrameworkRepresentation : public RepresentationSetRepresentation
	{
	public:
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_NonSealedSurfaceFrameworkRepresentation) NonSealedSurfaceFrameworkRepresentation;
#endif
	class NonSealedSurfaceFrameworkRepresentation : public AbstractSurfaceFrameworkRepresentation
	{
	public:
		void pushBackNonSealedContactRepresentation(unsigned int pointCount, double * points, EML2_NS::AbstractHdfProxy* proxy = nullptr, EML2_NS::AbstractLocal3dCrs* localCrs = nullptr);
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_SubRepresentation) SubRepresentation;
#endif
	class SubRepresentation : public AbstractRepresentation
	{
	public:
		void pushBackSubRepresentationPatch(gsoap_eml2_3::eml23__IndexableElement elementKind, uint64_t originIndex,
			unsigned int elementCountInSlowestDimension,
			unsigned int elementCountInMiddleDimension,
			unsigned int elementCountInFastestDimension);
		void pushBackSubRepresentationPatch(gsoap_eml2_3::eml23__IndexableElement elementKind, uint64_t elementCount, uint64_t* elementIndices, EML2_NS::AbstractHdfProxy* proxy = nullptr, short* supportingRepIndices = nullptr);
		void pushBackSubRepresentationPatch(gsoap_eml2_3::eml23__IndexableElement elementKind0, gsoap_eml2_3::eml23__IndexableElement elementKind1,
			uint64_t elementCount,
			uint64_t * elementIndices0, uint64_t * elementIndices1,
			EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Pushes back a new patch (without pairwise elements) in this sub-representation.
		 * The pushed patch is uninitialized and values must be set to this new patch afterwards.
		 *
		 * @param 	  	elementKind				The kind of (indexable) elements which constitutes the
		 * 										sub-representation patch.
		 * @param [in]	elementIndices			The indices of the elements in the supporting
		 * 										representation.
		 * @param [in]	proxy					The HDF proxy where the numerical values (indices)
		 * 										are stored.
		 */
		void pushBackSubRepresentationPatch(gsoap_eml2_3::eml23__IndexableElement elementKind, uint64_t elementCount,
			EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Set the element indices of an already created SubRepresentationPatch 
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 * @exception	std::out_of_range	 	If @p patchIndex is strictly greater than patch count and
		 * 										different from unsigned int maximum value.
		 *
		 * @param [in]	  	elementIndices		  	All the element indices to set in the already created SubRepresentationPatch.
		 * @param 		  	elementCount			The number of elements to write.
		 * @param 		  	offset	  				The offset value.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the element
		 * 											indices. It must be already opened for writing and
		 * 											won't be closed in this method. If @p nullptr
		 * 											(default value), a default HDF proxy must be defined
		 * 											into the data object repository.
		 * @param 		  	patchIndex			  	(Optional) Zero-based index of the patch where to
		 * 											write the element indices. If not provided, its
		 * 											default value is by convention set to unsigned int
		 * 											maximum value and the element indices will be written
		 * 											in the last subrepresentation patch (the one with the
		 * 											greatest index).
		 */	
		void setElementIndices(uint64_t* elementIndices, 
			uint64_t elementCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned int patchIndex = std::numeric_limits<unsigned int>::max());

		bool areElementIndicesPairwise(unsigned int patchIndex) const;
		bool areElementIndicesBasedOnLattice(unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const;

		int64_t getLatticeElementIndicesStartValue(unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const;
		uint64_t getLatticeElementIndicesDimensionCount(unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const;
		int64_t getLatticeElementIndicesOffsetValue(unsigned int latticeDimensionIndex, unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const;
		uint64_t getLatticeElementIndicesOffsetCount(unsigned int latticeDimensionIndex, unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const;

		gsoap_eml2_3::eml23__IndexableElement getElementKindOfPatch(unsigned int patchIndex, unsigned int elementIndicesIndex) const;
		uint64_t getElementCountOfPatch(unsigned int patchIndex) const;
		void getElementIndicesOfPatch(unsigned int patchIndex, unsigned int elementIndicesIndex, uint64_t * elementIndices) const;

		void pushBackSupportingRepresentation(AbstractRepresentation * supportingRep);
		uint64_t getSupportingRepresentationCount() const;
		AbstractRepresentation* getSupportingRepresentation(uint64_t index) const;
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_SealedSurfaceFrameworkRepresentation) SealedSurfaceFrameworkRepresentation;
#endif
	class SealedSurfaceFrameworkRepresentation : public AbstractSurfaceFrameworkRepresentation
	{
	public:
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_SealedVolumeFrameworkRepresentation) SealedVolumeFrameworkRepresentation;
#endif
	class SealedVolumeFrameworkRepresentation : public RepresentationSetRepresentation
	{
	public:
		SealedSurfaceFrameworkRepresentation* getSealedStructuralFramework() const;
		void setSealedSurfaceFramework(SealedSurfaceFrameworkRepresentation* ssf);
		
		void setInterpretationOfVolumeRegion(uint64_t regionindex, StratigraphicUnitInterpretation * stratiUnitInterp);
		
		void pushBackVolumeRegion(StratigraphicUnitInterpretation * stratiUnitInterp,
			unsigned int externalShellFaceCount,
			unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide);
		pushBackInternalShell(uint64_t regionindex,
			unsigned int internalShellFaceCount,
			unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide);

		/** 
		 * Gets the stratigraphic unit interpretation a particular region of this framework represents.
		 *
		 * @exception	std::out_of_range	 	If <tt>regionIndex &gt;=</tt> getRegionCount().
		 *
		 * @param	regionIndex	Zero-based index of the region.
		 * 						
		 * @returns The stratigraphic unit interpretation represented by the region at position @p regionIndex. 
		 */
		StratigraphicUnitInterpretation* getStratiUnitInterp(uint64_t regionIndex) const;

		uint64_t getRegionCount() const final;

		uint64_t getInternalShellCount(uint64_t regionindex) const final;

		uint64_t getFaceCountOfExternalShell(uint64_t regionindex) const final;
		uint64_t getFaceCountOfInternalShell(uint64_t regionindex, unsigned int internalShellIndex) const final;

		RESQML2_NS::AbstractRepresentation* getRepOfExternalShellFace(uint64_t regionindex, unsigned int faceIndex) const final;
		RESQML2_NS::AbstractRepresentation* getRepOfInternalShellFace(uint64_t regionindex, unsigned int internalShellIndex, unsigned int faceIndex) const final;

		uint64_t getRepPatchIndexOfExternalShellFace(uint64_t regionindex, unsigned int faceIndex) const final;
		uint64_t getRepPatchIndexOfInternalShellFace(uint64_t regionindex, unsigned int internalShellIndex, unsigned int faceIndex) const final;

		bool getSideFlagOfExternalShellFace(uint64_t regionindex, unsigned int faceIndex) const final;
		bool getSideFlagOfInternalShellFace(uint64_t regionindex, unsigned int internalShellIndex, unsigned int faceIndex) const final;
	};
	
	class GridConnectionSetRepresentation;
	class AbstractColumnLayerGridRepresentation;
	class AbstractIjkGridRepresentation;
	class UnstructuredGridRepresentation;
#ifdef SWIGPYTHON
	%rename(Resqml2_AbstractGridRepresentation) AbstractGridRepresentation;
#endif
	class AbstractGridRepresentation : public AbstractRepresentation
	{
	public:
		/**
		 * Gets the count of grid connection set representations associated to this grid instance.
		 *
		 * @exception	std::range_error	If the count of grid connection set representations is
		 * 									strictly greater than unsigned int max.
		 *
		 * @returns	The count of grid connection set representations associated to this grid instance.
		 */
		uint64_t getGridConnectionSetRepresentationCount() const;
		
		/**
		 * Gets a particular grid connection set representation associated to this grid representation.
		 *
		 * @exception	std::out_of_range	If @p index is out of range (greater than {@link getGridConnectionSetRepresentationCount()}).
		 *
		 * @param 	index	Zero-based index of the grid connection set representation we look for.
		 *
		 * @returns	The grid connection set representation at position @p index.
		 */
		 GridConnectionSetRepresentation* getGridConnectionSetRepresentation(uint64_t index) const;

		/**
		 * Gets the total count of cells in the grid.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error	If the count is strictly greater than unsigned int max.
		 *
		 * @returns	The total count of cells in the grid.
		*/
		uint64_t getCellCount() const;

		/**
		 * Gets the parent grid of this grid.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	If the parent window of this grid is neither an IJK, column
		 * 									layer nor cell window.
		 *
		 * @returns	nullptr if this grid is not a child grid (not an LGR), otherwise the parent grid.
		 */
		AbstractGridRepresentation* getParentGrid() const;

		/**
		 * Gets the count of child grids of this grid.
		 *
		 * @exception	std::range_error	If the count of child grids is strictly greater than unsigned
		 * 									int max.
		 *
		 * @returns	The count of child grids of this grid.
		 */
		uint64_t getChildGridCount() const;

		/**
		 * Gets a particular child grid of this grid.
		 *
		 * @exception	std::out_of_range	If <tt>index >=</tt> getChildGridCount().
		 *
		 * @param 	index	Zero-based index of the the child grid we look for.
		 *
		 * @returns	The child grid at position @p index.
		 */
		AbstractGridRepresentation* getChildGrid(uint64_t index) const;

		/**
		 * Indicates that this grid takes place into another unstructured parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p cellIndexCount is 0 or @p cellIndices is nullptr or
		 * 										@p parentGrid is nullptr.
		 * @exception	std::invalid_argument	If <tt>cellIndexCount &gt; 1</tt> and @p proxy is
		 * 										nullptr and no default HDF proxy is defined in the
		 * 										repository.
		 *
		 * @param [in]	  	cellIndices   	Identifies the cells (of the parent grid) which are regridded.
		 * @param 		  	cellIndexCount	Identifies the count of cells (of the parent grid) which are
		 * 									regridded.
		 * @param [in]	  	parentGrid	  	The parent grid which is regridded.
		 * @param [in,out]	proxy		  	(Optional) The HDF proxy where to store the numerical values.
		 * 									If nullptr (default), then the proxy will be the default
		 * 									proxy of the repository. This parameter is unused if @p
		 * 									cellIndexCount is 1 since no numerical value need to be store
		 * 									in an HDF proxy (pure XML).
		 */
		void setParentWindow(uint64_t * cellIndices, uint64_t cellIndexCount, UnstructuredGridRepresentation* parentGrid, EML2_NS::AbstractHdfProxy * proxy = nullptr);

		/**
		 * Indicates that this grid takes place into another column layer parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p columnIndices is nullptr or @p columnIndexCount is
		 * 										0 or
		 * 										@p childCellCountPerInterval is nullptr or @p
		 * 										parentCellCountPerInterval is nullptr or @p intervalCount
		 * 										is 0 or @p parentGrid is nullptr.
		 * @exception	std::invalid_argument	If an HDF proxy is required to store numerical values but
		 * 										@p proxy is nullptr and no default HDF proxy is defined
		 * 										in the repository.
		 *
		 * @param [in]	  	columnIndices			  	Identifies the columns (of the parent grid) which
		 * 												are regridded. The size is @p columnIndexCount.
		 * @param 		  	columnIndexCount		  	Identifies the count of columns (of the parent
		 * 												grid) which are regridded.
		 * @param 		  	kLayerIndexRegridStart	  	K index of the first K layer of all above parent
		 * 												grid columns to be regridded.
		 * @param [in]	  	childCellCountPerInterval 	The count of cells per K interval in this (child)
		 * 												grid. The size is @p intervalCount.
		 * @param [in]	  	parentCellCountPerInterval	The count of cells per K interval in the parent
		 * 												grid. The size is @p intervalCount.
		 * @param 		  	intervalCount			  	The count of intervals on K dimension. Intervals
		 * 												are portions of cells to regrid which does not
		 * 												overlap with each others. Intervals are the same
		 * 												for all the regridded columns.
		 * @param [in]	  	parentGrid				  	The parent grid which is regridded.
		 * @param [in,out]	proxy					  	(Optional) The HDF proxy where to store the
		 * 												numerical values. If nullptr (default), then the
		 * 												proxy will be the default proxy of the
		 * 												repository. This parameter is unused if no
		 * 												numerical value need to be store in an HDF proxy
		 * 												(pure XML).
		 * @param [in]	  	childCellWeights		  	(Optional) The weights that are proportional to
		 * 												the relative K sizes of child cells within each K
		 * 												interval. This is useful to set up child cells of
		 * 												different K sizes inside the intervals. The
		 * 												weights need not to be normalized. The count of
		 * 												double values must be equal to the count of all
		 * 												child cells on K dimension (sum of child cells
		 * 												per interval). Default value is nullptr.
		 */
		void setParentWindow(unsigned int * columnIndices, uint64_t columnIndexCount,
			unsigned int kLayerIndexRegridStart,
			unsigned int * childCellCountPerInterval, unsigned int * parentCellCountPerInterval, uint64_t intervalCount,
			class AbstractColumnLayerGridRepresentation* parentGrid,
			EML2_NS::AbstractHdfProxy * proxy = nullptr, double * childCellWeights = nullptr);

		/**
		 * Indicates that this grid takes place into another IJK parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p childCellCountPerIInterval is nullptr or @p
		 * 										parentCellCountPerIInterval is nullptr or @p
		 * 										iIntervalCount is 0 or @p childCellCountPerJInterval is
		 * 										nullptr or @p parentCellCountPerJInterval is nullptr or
		 * 										@p jIntervalCount is 0 or @p childCellCountPerKInterval
		 * 										is nullptr or @p parentCellCountPerKInterval is nullptr
		 * 										or @p kIntervalCount is 0 or @p parentGrid is nullptr.
		 * @exception	std::invalid_argument	If an HDF proxy is required to store numerical values but
		 * 										@p proxy is nullptr and no default HDF proxy is defined
		 * 										in the repository.
		 *
		 * @param 		  	iCellIndexRegridStart	   	I index of the first parent grid cell to be
		 * 												regridded.
		 * @param [in]	  	childCellCountPerIInterval 	The count of cells per I interval in this (child)
		 * 												grid. The size is @p iIntervalCount.
		 * @param [in]	  	parentCellCountPerIInterval	The count of cells per I interval in the parent
		 * 												grid. The size is @p iIntervalCount.
		 * @param 		  	iIntervalCount			   	The count of intervals on I dimension. Intervals
		 * 												are portions of cells to regrid which does not
		 * 												overlap with each others.
		 * @param 		  	jCellIndexRegridStart	   	J index of the first parent grid cell to be
		 * 												regridded.
		 * @param [in]	  	childCellCountPerJInterval 	The count of cells per J interval in this (child)
		 * 												grid. The size is @p jIntervalCount.
		 * @param [in]	  	parentCellCountPerJInterval	The count of cells per J interval in the parent
		 * 												grid. The size is @p jIntervalCount.
		 * @param 		  	jIntervalCount			   	The count of intervals on J dimension. Intervals
		 * 												are portions of cells to regrid which does not
		 * 												overlap with each others.
		 * @param 		  	kCellIndexRegridStart	   	K index of the first parent grid cell to be
		 * 												regridded.
		 * @param [in]	  	childCellCountPerKInterval 	The count of cells per K interval in this (child)
		 * 												grid. The size is @p kIntervalCount.
		 * @param [in]	  	parentCellCountPerKInterval	The count of cells per K interval in the parent
		 * 												grid. The size is @p kIntervalCount.
		 * @param 		  	kIntervalCount			   	The count of intervals on K dimension. Intervals
		 * 												are portions of cells to regrid which does not
		 * 												overlap with each others.
		 * @param [in]	  	parentGrid				   	The parent grid which is regridded.
		 * @param [in,out]	proxy					   	(Optional) The HDF proxy where to store the
		 * 												numerical values. If nullptr (default), then the
		 * 												proxy will be the default proxy of the
		 * 												repository. This parameter is unused if no
		 * 												numerical value need to be store in an HDF proxy
		 * 												(pure XML).
		 * @param [in]	  	iChildCellWeights		   	(Optional) The weights that are proportional to
		 * 												the relative I sizes of child cells within each I
		 * 												interval. This is useful to set up child cells of
		 * 												different I sizes inside the intervals. The
		 * 												weights need not to be normalized. The count of
		 * 												double values must be equal to the count of all
		 * 												child cells on I dimension (sum of child cells
		 * 												per interval). Default value is nullptr.
		 * @param [in]	  	jChildCellWeights		   	(Optional) The weights that are proportional to
		 * 												the relative J sizes of child cells within each J
		 * 												interval. This is useful to set up child cells of
		 * 												different J sizes inside the intervals. The
		 * 												weights need not to be normalized. The count of
		 * 												double values must be equal to the count of all
		 * 												child cells on J dimension (sum of child cells
		 * 												per interval). Default value is nullptr.
		 * @param [in]	  	kChildCellWeights		   	(Optional) The weights that are proportional to
		 * 												the relative K sizes of child cells within each K
		 * 												interval. This is useful to set up child cells of
		 * 												different K sizes inside the intervals. The
		 * 												weights need not to be normalized. The count of
		 * 												double values must be equal to the count of all
		 * 												child cells on K dimension (sum of child cells
		 * 												per interval). Default value is nullptr.
		 */
		void setParentWindow(
			unsigned int iCellIndexRegridStart, unsigned int * childCellCountPerIInterval, unsigned int * parentCellCountPerIInterval, uint64_t iIntervalCount,
			unsigned int jCellIndexRegridStart, unsigned int * childCellCountPerJInterval, unsigned int * parentCellCountPerJInterval, uint64_t jIntervalCount,
			unsigned int kCellIndexRegridStart, unsigned int * childCellCountPerKInterval, unsigned int * parentCellCountPerKInterval, uint64_t kIntervalCount,
			AbstractIjkGridRepresentation* parentGrid, EML2_NS::AbstractHdfProxy * proxy = nullptr, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);

		/**
		 * @brief	Indicates that this grid takes place into another IJK parent grid. This method
		 * 			assumes that the count of cells per regrid interval is constant in both child and
		 * 			parent grids.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p constantChildCellCountPerIInterval is 0 or @p
		 * 										constantParentCellCountPerIInterval is 0 or @p
		 * 										iIntervalCount is 0 or
		 * 										@p constantChildCellCountPerJInterval is 0 or @p
		 * 										constantParentCellCountPerJInterval is 0 or @p
		 * 										jIntervalCount is 0 or
		 * 										@p constantChildCellCountPerKInterval is 0 or @p
		 * 										constantParentCellCountPerKInterval is 0 or @p
		 * 										kIntervalCount is 0 or
		 * 										@p parentGrid is nullptr.
		 * @exception	std::invalid_argument	If an HDF proxy is required to store numerical values but
		 * 										@p proxy is nullptr and no default HDF proxy is defined
		 * 										in the repository.
		 *
		 * @param 		  	iCellIndexRegridStart			   	I index of the first parent grid cell to
		 * 														be regridded.
		 * @param 		  	constantChildCellCountPerIInterval 	The constant count of cells per I
		 * 														interval in this (child) grid.
		 * @param 		  	constantParentCellCountPerIInterval	The constant count of cells per I
		 * 														interval in the parent grid.
		 * @param 		  	iIntervalCount					   	The count of intervals on I dimension.
		 * 														Intervals are portions of cells to regrid
		 * 														which does not overlap with each others.
		 * @param 		  	jCellIndexRegridStart			   	J index of the first parent grid cell to
		 * 														be regridded.
		 * @param 		  	constantChildCellCountPerJInterval 	The constant count of cells per J
		 * 														interval in this (child) grid.
		 * @param 		  	constantParentCellCountPerJInterval	The constant count of cells per J
		 * 														interval in the parent grid.
		 * @param 		  	jIntervalCount					   	The count of intervals on J dimension.
		 * 														Intervals are portions of cells to regrid
		 * 														which does not overlap with each others.
		 * @param 		  	kCellIndexRegridStart			   	K index of the first parent grid cell to
		 * 														be regridded.
		 * @param 		  	constantChildCellCountPerKInterval 	The constant count of cells per K
		 * 														interval in this (child) grid.
		 * @param 		  	constantParentCellCountPerKInterval	The constant count of cells per K
		 * 														interval in the parent grid.
		 * @param 		  	kIntervalCount					   	The count of intervals on K dimension.
		 * 														Intervals are portions of cells to regrid
		 * 														which does not overlap with each others.
		 * @param [in]	  	parentGrid						   	The parent grid which is regridded.
		 * @param [in,out]	proxy							   	(Optional) The HDF proxy where to store
		 * 														the numerical values. If nullptr
		 * 														(default), then the proxy will be the
		 * 														default proxy of the repository. This
		 * 														parameter is unused if no numerical value
		 * 														need to be store in an HDF proxy (pure
		 * 														XML).
		 * @param [in]	  	iChildCellWeights				   	(Optional) The weights that are
		 * 														proportional to the relative I sizes of
		 * 														child cells within each I interval. This
		 * 														is useful to set up child cells of
		 * 														different I sizes inside the intervals.
		 * 														The weights need not to be normalized.
		 * 														The count of double values must be equal
		 * 														to the count of all child cells on I
		 * 														dimension
		 * 														(<tt>constantChildCellCountPerIInterval *
		 * 														iIntervalCount</tt>). Default value is
		 * 														nullptr.
		 * @param [in]	  	jChildCellWeights				   	(Optional) The weights that are
		 * 														proportional to the relative J sizes of
		 * 														child cells within each J interval. This
		 * 														is useful to set up child cells of
		 * 														different J sizes inside the intervals.
		 * 														The weights need not to be normalized.
		 * 														The count of double values must be equal
		 * 														to the count of all child cells on J
		 * 														dimension
		 * 														(<tt>constantChildCellCountPerJInterval</tt>
		 * 														<tt>* jIntervalCount</tt>).
		 * @param [in]	  	kChildCellWeights				   	(Optional) The weights that are
		 * 														proportional to the relative K sizes of
		 * 														child cells within each K interval. This
		 * 														is useful to set up child cells of
		 * 														different K sizes inside the intervals.
		 * 														The weights need not to be normalized.
		 * 														The count of double values must be equal
		 * 														to the count of all child cells on K
		 * 														dimension
		 * 														(<tt>constantChildCellCountPerKInterval</tt>
		 * 														<tt>* kIntervalCount</tt>).
		 */
		void setParentWindow(
			unsigned int iCellIndexRegridStart, unsigned int constantChildCellCountPerIInterval, unsigned int constantParentCellCountPerIInterval, uint64_t iIntervalCount,
			unsigned int jCellIndexRegridStart, unsigned int constantChildCellCountPerJInterval, unsigned int constantParentCellCountPerJInterval, uint64_t jIntervalCount,
			unsigned int kCellIndexRegridStart, unsigned int constantChildCellCountPerKInterval, unsigned int constantParentCellCountPerKInterval, uint64_t kIntervalCount,
			AbstractIjkGridRepresentation* parentGrid, EML2_NS::AbstractHdfProxy * proxy = nullptr, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);

		/**
		 * Indicates that this grid takes place into another IJK parent grid. This method assumes that
		 * there is only one regrid interval per dimension.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p iChildCellCount is 0 or @p iParentCellCount is 0 or
		 * 										@p jChildCellCount is 0 or @p jParentCellCount is 0 or @p
		 * 										kChildCellCount is 0 or @p kParentCellCount is 0 or @p
		 * 										parentGrid is nullptr.
		 * @exception	std::invalid_argument	If an HDF proxy is required to store numerical values but
		 * 										@p proxy is nullptr and no default HDF proxy is defined
		 * 										in the repository.
		 *
		 * @param 		  	iCellIndexRegridStart	I index of the first parent grid cell to
		 * 											be regridded.
		 * @param 		  	iChildCellCount		 	The count of cells for the unique I interval in this
		 * 											(child) grid.
		 * @param 		  	iParentCellCount	 	The count of cells for the unique I interval in the
		 * 											parent grid.
		 * @param 		  	jCellIndexRegridStart	J index of the first parent grid cell to
		 * 											be regridded.
		 * @param 		  	jChildCellCount		 	The count of cells for the unique J interval in this
		 * 											(child) grid.
		 * @param 		  	jParentCellCount	 	The count of cells for the unique J interval in the
		 * 											parent grid.
		 * @param 		  	kCellIndexRegridStart	K index of the first parent grid cell to
		 * 											be regridded.
		 * @param 		  	kChildCellCount		 	The count of cells for the unique K interval in this
		 * 											(child) grid.
		 * @param 		  	kParentCellCount	 	The count of cells for the unique K interval in the
		 * 											parent grid.
		 * @param [in]	  	parentGrid			 	The parent grid which is regridded.
		 * @param [in,out]	proxy				 	(Optional) The HDF proxy where to store the numerical
		 * 											values. If nullptr (default), then the proxy will be
		 * 											the default proxy of the repository. This parameter
		 * 											is unused if no numerical value need to be store in
		 * 											an HDF proxy (pure XML).
		 * @param [in]	  	iChildCellWeights	 	(Optional) The weights that are proportional to the
		 * 											relative I sizes of child cells. This is useful to
		 * 											set up child cells of different I sizes inside the
		 * 											unique interval. The weights need not to be
		 * 											normalized. The count of double values must be equal
		 * 											to @p iChildCellCount. Default value is nullptr.
		 * @param [in]	  	jChildCellWeights	 	(Optional) The weights that are proportional to the
		 * 											relative J sizes of child cells. This is useful to
		 * 											set up child cells of different J sizes inside the
		 * 											unique interval. The weights need not to be
		 * 											normalized. The count of double values must be equal
		 * 											to @p jChildCellCount. Default value is nullptr.
		 * @param [in]	  	kChildCellWeights	 	(Optional) The weights that are proportional to the
		 * 											relative K sizes of child cells. This is useful to
		 * 											set up child cells of different K sizes inside the
		 * 											unique interval. The weights need not to be
		 * 											normalized. The count of double values must be equal
		 * 											to @p kChildCellCount. Default value is nullptr.
		 */
		void setParentWindow(
			unsigned int iCellIndexRegridStart, unsigned int iChildCellCount, unsigned int iParentCellCount,
			unsigned int jCellIndexRegridStart, unsigned int jChildCellCount, unsigned int jParentCellCount,
			unsigned int kCellIndexRegridStart, unsigned int kChildCellCount, unsigned int kParentCellCount,
			AbstractIjkGridRepresentation* parentGrid, EML2_NS::AbstractHdfProxy * proxy = nullptr, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);

		/**
		 * When a parent windows has been defined, this method allows to force some parent cells to be
		 * noted as non regridded. It mainly allows non-rectangular local grids to be specified.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is neither an IJK nor a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If @p cellIndices is nullptr or @p cellIndexCount is 0.
		 * @exception	std::invalid_argument	If an HDF proxy is required and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param [in]	cellIndices   	The indices of the parent cells to be noted as non regridded. The
		 * 								size is @p cellIndexCount.
		 * @param 	  	cellIndexCount	Number of cells to be noted as non regridded.
		 */
		void setForcedNonRegridedParentCell(uint64_t * cellIndices, uint64_t cellIndexCount);

		/**
		 * Set optional cell overlap information between the current grid (the child) and the parent
		 * grid. Use this data-object when the child grid has an explicitly defined geometry, and these
		 * relationships cannot be inferred from the regrid descriptions. An overlap volume information
		 * can be associated to each overlapping (parent cell, child cell) pair.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined.
		 * @exception	std::invalid_argument	If @p parentChildCellPairCount is 0 or
		 * 										@p parentChildCellPair is nullptr.
		 * @exception	std::invalid_argument	If no default HDF proxy is defined in the repository.
		 *
		 * @param 	  	parentChildCellPairCount	Number of (parent cell, child cell) pairs that
		 * 											overlap.
		 * @param [in]	parentChildCellPair			The (parent cell index, child cell index) pair for
		 * 											each overlap. The size is <tt>2 *
		 * 											parentChildCellPairCount</tt>.
		 * 											<tt>parentChildCellPair[2i]</tt> are parent cell indices
		 * 											and <tt>parentChildCellPair[2i+1]</tt> are child cell
		 * 											indices.
		 * @param 	  	volumeUom					The volume unit of measure.
		 * @param [in]	overlapVolumes				(Optional) The overlapping volume for each (parent
		 * 											cell, child cell) that overlaps. Size is @p
		 * 											parentChildCellPairCount. Default value is nullptr.
		 */
		void setCellOverlap(uint64_t parentChildCellPairCount, uint64_t* parentChildCellPair,
			const std::string& volumeUom, double* overlapVolumes = nullptr);	

		/**
		 * Gets the count of parent grid cells which are regridded. Please only run this method for an
		 * unstructured parent grid. Please use regrid information for IJK parent grid or (regrid information
		 * and columIndexCount) for strict column layer parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is not an unstructured parent window.
		 * @exception std::invalid_argument		If the list of regridded cells is not stored in an HDF5 file.
		 *
		 * @returns	The count of parent grid cells which are regridded.
		 */
		uint64_t getParentCellIndexCount() const;

		/**
		 * Gets the indices of the parent grid cells which are regridded. Please only run this method
		 * for an unstructured parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is not an unstructured parent window.
		 * @exception	std::invalid_argument	If the list of regridded cells is not stored in an HDF5
		 * 										file.
		 *
		 * @param [out]	parentCellIndices	An array for receiving the regridded cells indices. This
		 * 									array must have been preallocated with a size of 
		 * 									getParentCellIndexCount().
		 */
		void getParentCellIndices(uint64_t * parentCellIndices) const;

		/**
		 * Gets the count of parent grid columns which are regridded. Please only run this method for a
		 * strict column layer parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is not a column layer parent window.
		 * @exception	std::invalid_argument	If the list of regridded cells is not stored in an HDF5
		 * 										file.
		 *
		 * @returns	The count of parent grid columns which are regridded.
		 */
		uint64_t getParentColumnIndexCount() const;

		/**
		 * Gets the indices of the parent grid columns which are regridded. Please only run this method
		 * for a strict column layer parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is not a column layer parent window.
		 * @exception	std::invalid_argument	If the list of regridded cells is not stored in an HDF5
		 * 										file.
		 *
		 * @param [out]	parentColumnIndices	An array for collecting the regridded column indices. This
		 * 									array must have been preallocated with a size of
		 * 										getParentColumnIndexCount().
		 */
		void getParentColumnIndices(uint64_t * parentColumnIndices) const;

		/**
		 * Get the I, J or K index of the first parent grid cell to be regridded. Please only run this
		 * method for an IJK parent grid or a strict column layer parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is neither an IJK nor a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If @p dimension differs from 'i', 'j' or 'k' (upper or
		 * 										lower case) for an IJK parent window or if it differs
		 * 										from 'k' (upper or lower case) for a column layer parent
		 * 										window.
		 *
		 * @param 	dimension	The dimension of the index we look for. It must be either 'i', 'j' or 'k'
		 * 						(upper or lower case) for an IJK parent grid or 'k' for a strict column
		 * 						layer parent grid.
		 *
		 * @returns	The regrid start index on the parent grid in dimension @p dimension.
		 */
		uint64_t getRegridStartIndexOnParentGrid(char dimension) const;

		/**
		 * Gets the count of intervals which are regridded on a particular dimension. Intervals are
		 * portions of cells to regrid which does not overlap with each others. Please only run this
		 * method for an IJK parent grid or a strict column layer parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is neither an IJK nor a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If @p dimension differs from 'i', 'j' or 'k' (upper or
		 * 										lower case) for an IJK parent window or if it differs
		 * 										from 'k' (upper or lower case) for a column layer parent
		 * 										window.
		 *
		 * @param 	dimension	The dimension of the interval count we look for. It must be either 'i',
		 * 						'j' or 'k' (upper or lower case) for an IJK parent grid or 'k' for a
		 * 						strict column layer parent grid.
		 *
		 * @returns	The regrid interval count in dimension @p dimension.
		 */
		uint64_t getRegridIntervalCount(char dimension) const;

		/**
		 * Checks if the cell count per interval (in the child grid or in the parent grid) is constant
		 * against a particular dimension. Intervals are portions of cells to regrid which does not
		 * overlap with each others. Please only run this method for an IJK parent grid or a strict
		 * column layer parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is neither an IJK nor a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If @p dimension differs from 'i', 'j' or 'k' (upper or
		 * 										lower case) for an IJK parent window or if it differs
		 * 										from 'k' (upper or lower case) for a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If there exists no regrid interval in dimension @p
		 * 										dimension.
		 *
		 * @param 	dimension			  	The dimension of the interval we look for. It must be either
		 * 									'i', 'j' ou 'k' (upper or lower case) for an IJK parent grid
		 * 									or 'k' for a strict column layer parent grid.
		 * @param 	childVsParentCellCount	If true, checks if the child cell count per interval is
		 * 									constant. If false, checks if the parent cell count per
		 * 									interval is constant.
		 *
		 * @returns	True if the regrid cell count per interval is constant in dimension @p dimension,
		 * 			false if not.
		 */
		bool isRegridCellCountPerIntervalConstant(char dimension, bool childVsParentCellCount) const;

		/**
		 * Gets the constant cell count per interval (in the child grid or in the parent grid) against a
		 * particular dimension. Intervals are portions of cells to regrid which does not overlap with
		 * each others. Please only run this method for an IJK parent grid or a strict column layer
		 * parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the cell count per interval in dimension @p dimension
		 * 										is neither an integer constant array nor a HDF5 integer
		 * 										array.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is neither an IJK nor a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If @p dimension differs from 'i', 'j' or 'k' (upper or
		 * 										lower case) for an IJK parent window or if it differs
		 * 										from 'k' (upper or lower case) for a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If there exists no regrid interval in dimension @p
		 * 										dimension.
		 *
		 * @param 	dimension			  	The dimension of the interval we look for. It must be either
		 * 									'i', 'j' ou 'k' (upper or lower case) for an IJK parent grid
		 * 									or 'k' for a strict column layer parent grid.
		 * @param 	childVsParentCellCount	If true, gets the constant child cell count per interval. If
		 * 									false, gets the constant parent cell count per interval.
		 *
		 * @returns	The regrid constant cell count per interval in dimension @p dimension.
		 */
		uint64_t getRegridConstantCellCountPerInterval(char dimension, bool childVsParentCellCount) const;

		/**
		 * Gets the regrid cell count per interval (in the child grid or in the parent grid) against a
		 * particular dimension. Intervals are portions of cells to regrid which does not overlap with
		 * each others. Please only run this method for an IJK parent grid or a strict column layer
		 * parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the cell count per interval in dimension @p dimension
		 * 										is neither an integer constant array nor a HDF5 integer
		 * 										array.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is neither an IJK nor a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If @p dimension differs from 'i', 'j' or 'k' (upper or
		 * 										lower case) for an IJK parent window or if it differs
		 * 										from 'k' (upper or lower case) for a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If there exists no regrid interval in dimension @p
		 * 										dimension.
		 *
		 * @param 	  	dimension				 	The dimension of the interval we look for. It must be
		 * 											either 'i', 'j' ou 'k' (upper or lower case) for an
		 * 											IJK parent grid or 'k' for a strict column layer
		 * 											parent grid.
		 * @param [in]	childCellCountPerInterval	An array to receive the regrid cell count per
		 * 											interval. It must have been preallocated with a size
		 * 											of getRegridIntervalCount().
		 * @param 	  	childVsParentCellCount   	If true, gets the child cell count per interval. If
		 * 											false, gets the parent cell count per interval.
		 */
		void getRegridCellCountPerInterval(char dimension, uint64_t * childCellCountPerInterval, bool childVsParentCellCount) const;

		/**
		 * Checks if regrid child cell weights have been defined for a given dimension. Please only run
		 * this method for an IJK parent grid or a strict column layer parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is neither an IJK nor a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If @p dimension differs from 'i', 'j' or 'k' (upper or
		 * 										lower case) for an IJK parent window or if it differs
		 * 										from 'k' (upper or lower case) for a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If there exists no regrid interval in dimension @p
		 * 										dimension.
		 *
		 * @param 	dimension	The dimension from which we look for regrid child cell weights. It must
		 * 						be either 'i', 'j' ou 'k' (upper or lower case) for an IJK parent grid or
		 * 						'k' for a strict column layer parent grid.
		 *
		 * @returns	True if regrid child cell weights have been defined in dimension @p dimension, false
		 * 			if not.
		 */
		bool hasRegridChildCellWeights(char dimension) const;

		/**
		 * Gets the regrid child cell weights for a given dimension. Please only run this method for an
		 * IJK parent grid or a strict column layer parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is neither an IJK nor a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If @p dimension differs from 'i', 'j' or 'k' (upper or
		 * 										lower case) for an IJK parent window or if it differs
		 * 										from 'k' (upper or lower case) for a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If there exists no regrid interval in dimension @p
		 * 										dimension.
		 * @exception	std::invalid_argument	If the regrid child cell weights in dimension @p
		 * 										dimension are not stored in an HDF5 file.
		 *
		 * @param 		  	dimension			The dimension from which we look for regrid child cell
		 * 										weights. It must be either 'i', 'j' ou 'k' (upper or lower
		 * 										case) for an IJK parent grid or 'k' for a strict column layer
		 * 										parent grid.
		 * @param [in,out]	childCellWeights	An array for receiving the regrid child cell weights. It
		 * 										must have been preallocated with a size equal to the sum of
		 * 										regrid child cell count per interval (using
		 * 										getRegridCellCountPerInterval()).
		 */
		void getRegridChildCellWeights(char dimension, double * childCellWeights) const;

		/**
		 * When a parent windows has been defined, this method checks if some parent cells have been
		 * noted to be forced not to be regridded. It mainly occurs in case of non-rectangular local
		 * grids.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined.
		 *
		 * @returns	True if some parent cells have been forced not to be regridded, false if not.
		 */
		bool hasForcedNonRegridedParentCell() const;

		/**
		 * Sets the stratigraphic organization interpretation which is associated to this grid
		 * representation.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no default HDF proxy is defined in the repository.
		 *
		 * @param [in]	stratiUnitIndices	Index of the stratigraphic unit of a given stratigraphic
		 * 									column for each cell. Array length is the number of cells in
		 * 									the grid or the blocked well.
		 * @param 	  	nullValue		 	The value which is used to tell the association between a
		 * 									cell and a stratigraphic unit is unavailable.
		 * @param [in]	stratiOrgInterp  	The stratigraphic organization interpretation which is
		 * 									associated to this grid representation.
		 */
		void setCellAssociationWithStratigraphicOrganizationInterpretation(int64_t * stratiUnitIndices, int64_t nullValue, RESQML2_NS::AbstractStratigraphicOrganizationInterpretation* stratiOrgInterp);
		
		/**
		 * Gets the stratigraphic organization interpretation which is associated to this grid.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @returns	nullptr if no stratigraphic organization interpretation is associated to this grid
		 * 			representation. Otherwise return the associated stratigraphic organization
		 * 			interpretation.
		 */
		RESQML2_NS::AbstractStratigraphicOrganizationInterpretation* getStratigraphicOrganizationInterpretation() const;

		/**
		 * Queries if there exists some association between stratigraphic unit indices and the cells of
		 * this grid.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @returns	True if this grid representation has got some association between stratigraphic unit
		 * 			indices and cells.
		 */
		bool hasCellStratigraphicUnitIndices() const;

		/**
		 * Gets the stratigraphic unit indices (regarding the associated stratigraphic organization
		 * interpretation) of each cell of this grid representation.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the associated stratigraphic unit indices are not
		 * 										stored in a HDF5 integer array.
		 * @exception	std::invalid_argument	If the cells of this grid are not associated with
		 * 										stratigraphic units indices.
		 *
		 * @param [out]	stratiUnitIndices	An array to receive the stratigraphic unit indices associated
		 * 									to the cells of this grid. It must be preallocated with a
		 * 									count equal to getCellCount(). It will be filled in with the
		 * 									stratigraphic unit indices ordered as grid cells are ordered.
		 *
		 * @returns	The null value. The null value is used to tell the association between a cell and
		 * 			stratigraphic unit is unavailable.
		 */
		int64_t getCellStratigraphicUnitIndices(int64_t * stratiUnitIndices);

		/**
		 * Indicates whether this grid instance contains truncated pillars or not.
		 *
		 * @returns	True if truncated pillars exist, false if not.
		 */
		bool isTruncated() const;

		/**
		 * Gets the truncated face count. It does not include face of truncated cells which are not
		 * truncated.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 *
		 * @returns	The truncated face count.
		 */
		uint64_t getTruncatedFaceCount() const;

		/**
		 * Gets all the node indices of the truncated faces.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the node indices of the truncated faces are not stored
		 * 										in a HDF5 integer array.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 *
		 * @param [out]	nodeIndices	An array to receive the node indices of the truncated faces. It must
		 * 							be preallocated with the last value returned by
		 * 							getCumulativeNodeCountOfTruncatedFaces().
		 */
		void getNodeIndicesOfTruncatedFaces(uint64_t * nodeIndices) const;

		/**
		 * Gets the cumulative node count per truncated face. First value is the count of nodes in the
		 * first face. Second value is the count of nodes in the first and in the second face. Third
		 * value is the count of nodes in the first and in the second and in the third face. Etc... The
		 * length of the output array is equal to getTruncatedFaceCount(). A single node count should be
		 * at least 3.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 * @exception	std::range_error	 	If the cumulative length of nodes count per cells is
		 * 										constant (it is stored in a constant integer array).
		 *
		 * @param [in]	nodeCountPerFace	An array to receive the cumulative node count per truncated
		 * 									face. It must be preallocated with getTruncatedFaceCount()
		 * 									(equals to last value of
		 * 									getCumulativeTruncatedFaceCountPerTruncatedCell())
		 */
		void getCumulativeNodeCountPerTruncatedFace(uint64_t * nodeCountPerFace) const;

		/**
		 * Get the node count per truncated face. This method is less efficient than
		 * getCumulativeNodeCountPerTruncatedFace(). First value is the count of nodes in the first
		 * face. Second value is the count of nodes in the second face. etc...
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 * @exception	std::range_error	 	If the cumulative length of nodes count per cells is
		 * 										constant (it is stored in a constant integer array).
		 *
		 * @param [out]	nodeCountPerFace	An array to receive the node count per truncated face. It
		 * 									must be preallocated with getTruncatedFaceCount() (equals to last
		 * 									value of getCumulativeTruncatedFaceCountPerTruncatedCell()).
		 */
		void getNodeCountPerTruncatedFace(uint64_t * nodeCountPerFace) const;

		/**
		 * Gets the truncated cell count.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 *
		 * @returns	The truncated cell count.
		 */
		uint64_t getTruncatedCellCount() const;

		/**
		 * Gets the parent cell index for each of the truncation cells.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the parent cell indices are stored neither in a HDF5
		 * 										integer array nor in a constant integer array.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 *
		 * @param [out]	cellIndices	An array to receive the parent cell index of each truncation cell. It
		 * 							must be preallocated with getTruncatedCellCount.
		 */
		void getTruncatedCellIndices(uint64_t* cellIndices) const;

		/**
		 * Gets all the truncated face indices of all the truncated cells. It does not get the non
		 * truncated face indices of a truncated cell. Please use
		 * getNonTruncatedFaceIndicesOfTruncatedCells() in addition to this method in order to get the
		 * full list of face indices for a truncated cell.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the truncated face indices are not stored in a HDF5
		 * 										integer array.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 *
		 * @param [out]	faceIndices	An array to receive the truncated face indices of all the truncated
		 * 							cells. It must be preallocated with the last value returned by
		 * 							getCumulativeTruncatedFaceCountPerTruncatedCell()
		 */
		void getTruncatedFaceIndicesOfTruncatedCells(uint64_t * faceIndices) const;

		/**
		 * Gets the cumulative truncated face count per truncated cell. It does not take into account
		 * the non truncated face of a truncated cell. First value is the count of faces in the first
		 * cell. Second value is the count of faces in the first and in the second cell. Third value is
		 * the count of faces in the first and in the second and in the third cell. Etc... The length of
		 * the output array is equal to getTruncatedCellCount(). A single face count should be at least
		 * 4.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 * @exception	std::range_error	 	If the cumulative length of truncated faces count per
		 * 										cells is constant (it is stored in a constant integer
		 * 										array) while there is more than one cell in the grid.
		 *
		 * @param [out]	cumulativeFaceCountPerCell	An array to receive the cumulative truncated face
		 * 											count per truncated cell. It must be pre allocated
		 * 											with getTruncatedCellCount().
		 */
		void getCumulativeTruncatedFaceCountPerTruncatedCell(uint64_t * cumulativeFaceCountPerCell) const;

		/**
		 * Gets the truncated face count per truncated cell. This method is less efficient than
		 * getCumulativeTruncatedFaceCountPerTruncatedCell(). First value is the count of faces in the
		 * first cell. Second value is the count of faces in the second cell. etc...
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 * @exception	std::range_error	 	If the cumulative length of faces count per cells is
		 * 										constant (it is stored in a constant integer array) while
		 * 										there is more than one cell in the grid.
		 *
		 * @param [out]	faceCountPerCell	An array to receive the truncated face count per truncated
		 * 									cell. It must be preallocated with getTruncatedCellCount()
		 */
		void getTruncatedFaceCountPerTruncatedCell(uint64_t * faceCountPerCell) const;

		/**
		 * Gets all the non truncated face indices of all the truncated cells. It does not get the
		 * truncated face indices of a truncated cell. Please use
		 * getTruncatedFaceIndicesOfTruncatedCells() in addition to this method in order to get the full
		 * list of face indices for a truncated cell.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the non truncated face indices are not stored in a
		 * 										HDF5 integer array.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 *
		 * @param [out]	faceIndices	An array to receive the non truncated face indices of all the
		 * 							truncated cells.It must be pre allocated with the last value returned
		 * 							by getCumulativeNonTruncatedFaceCountPerTruncatedCell()
		 */
		void getNonTruncatedFaceIndicesOfTruncatedCells(uint64_t * faceIndices) const;

		/**
		 * Get the cumulative non truncated face count per truncated cell. It does not take into account
		 * the truncated face indices of a truncated cell. First value is the count of faces in the
		 * first cell. Second value is the count of faces in the first and in the second cell. Third
		 * value is the count of faces in the first and in the second and in the third cell. Etc...
		 * Count of this array is equal to getTruncatedCellCount(). A single face count should be at
		 * least 4.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 * @exception	std::range_error	 	If the cumulative length of non truncated faces count per
		 * 										cells is constant (it is stored in a constant integer
		 * 										array) while there is more than one cell in the grid.
		 *
		 * @param [out]	cumulativeFaceCountPerCell	An array to receive the cumulative non truncated face
		 * 											count per truncated cell. It must be preallocated with
		 * 												getTruncatedCellCount()
		 */
		void getCumulativeNonTruncatedFaceCountPerTruncatedCell(uint64_t * cumulativeFaceCountPerCell) const;

		/**
		 * Gets the non truncated face count per cell. This method is less efficient than
		 * getCumulativeNonTruncatedFaceCountPerTruncatedCell(). First value is the count of faces in
		 * the first cell. Second value is the count of faces in the second cell. etc...
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 * @exception	std::range_error	 	If the cumulative length of non truncated faces count per
		 * 										cells is constant (it is stored in a constant integer
		 * 										array) while there is more than one cell in the grid.
		 *
		 * @param [out]	faceCountPerCell	An array to receive the non truncated face count per
		 * 									truncated cell. It must be pre allocated with
		 * 									getTruncatedCellCount()
		 */
		void getNonTruncatedFaceCountPerTruncatedCell(uint64_t * faceCountPerCell) const;

		/**
		 * Retrieves the orientation of each truncated face (i.e. if each truncated face is right handed
		 * or not).
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the orientation of the truncated faces is neither
		 * 										stored in a HDF5 boolean array nor in a boolean constant
		 * 										array.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 *
		 * @param [out]	cellFaceIsRightHanded	An array to receive the orientation of truncated faces.
		 * 										Value '0' means left handed and value other than '0'
		 * 										means right handed. It must be preallocated with
		 * 										getTruncatedFaceCount()
		 */
		void getTruncatedFaceIsRightHanded(uint8_t* cellFaceIsRightHanded) const;
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_UnstructuredGridRepresentation) UnstructuredGridRepresentation;
#endif
	class UnstructuredGridRepresentation : public AbstractGridRepresentation
	{
	public:
		void getCellFaceIsRightHanded(uint8_t* cellFaceIsRightHanded) const;
	
		uint64_t getFaceCount() const;
		void getFaceIndicesOfCells(uint64_t * faceIndices) const;
		void getCumulativeFaceCountPerCell(uint64_t * faceCountPerCell) const;
		uint64_t const * getCumulativeFaceCountPerCell() const;
		void getFaceCountPerCell(uint64_t * faceCountPerCell) const;
		bool isFaceCountOfCellsConstant() const;
		unsigned int getConstantFaceCountOfCells() const;
		
		void getNodeIndicesOfFaces(uint64_t * nodeIndices) const;
		void getCumulativeNodeCountPerFace(uint64_t * nodeCountPerFace) const;
		void getNodeCountPerFace(uint64_t * nodeCountPerFace) const;
		bool isNodeCountOfFacesConstant() const;
		unsigned int getConstantNodeCountOfFaces() const;
		
		void loadGeometry();
		uint64_t getFaceCountOfCell(uint64_t cellIndex) const;
		uint64_t getNodeCountOfFaceOfCell(uint64_t cellIndex, unsigned int localFaceIndex) const;
		uint64_t const * getNodeIndicesOfFaceOfCell(uint64_t cellIndex, unsigned int localFaceIndex) const;
		void unloadGeometry();
		
		void setGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points, uint64_t pointCount, EML2_NS::AbstractHdfProxy* proxy,
			const std::string& faceIndicesPerCell, const std::string& faceIndicesCumulativeCountPerCell,
			uint64_t faceCount, const std::string& nodeIndicesPerFace, const std::string& nodeIndicesCumulativeCountPerFace,
			gsoap_resqml2_0_1::resqml20__CellShape cellShape, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		void setGeometry(uint8_t * cellFaceIsRightHanded, double * points, uint64_t pointCount, EML2_NS::AbstractHdfProxy* proxy,
			uint64_t * faceIndicesPerCell, uint64_t * faceIndicesCumulativeCountPerCell,
			uint64_t faceCount, uint64_t * nodeIndicesPerFace, uint64_t * nodeIndicesCumulativeCountPerFace,
			gsoap_resqml2_0_1::resqml20__CellShape cellShape, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		void setTetrahedraOnlyGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
			uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractHdfProxy* proxy,
			const std::string& faceIndicesPerCell, const std::string& nodeIndicesPerFace, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		void setTetrahedraOnlyGeometry(uint8_t * cellFaceIsRightHanded, double * points,
			uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractHdfProxy* proxy,
			uint64_t * faceIndicesPerCell, uint64_t * nodeIndicesPerFace, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		void setHexahedraOnlyGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
			uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractHdfProxy* proxy,
			const std::string& faceIndicesPerCell, const std::string& nodeIndicesPerFace, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		void setHexahedraOnlyGeometry(uint8_t * cellFaceIsRightHanded, double * points,
			uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractHdfProxy* proxy,
			uint64_t * faceIndicesPerCell, uint64_t * nodeIndicesPerFace, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_AbstractColumnLayerGridRepresentation) AbstractColumnLayerGridRepresentation;
#endif
	class AbstractColumnLayerGridRepresentation : public AbstractGridRepresentation
	{
	public:
		/**
		 * Gets the K layer count of this grid
		 *
		 * @exception	std::logic_error	If this grid is partial or if the underlying gSOAP instance
		 * 									is not a RESQML2.0 one.
		 *
		 * @returns	The K layer count of this grid.
		 */
		uint64_t getKCellCount() const;

		/**
		 * Sets the K layer count of this grid
		 *
		 * @exception	std::logic_error	If this grid is partial or if the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @param 	kCount	The K layer count to set to this grid.
		 */
		void setKCellCount(uint64_t kCount);

		void setIntervalAssociationWithStratigraphicOrganizationInterpretation(int64_t * stratiUnitIndices, int64_t nullValue, RESQML2_NS::AbstractStratigraphicOrganizationInterpretation* stratiOrgInterp, EML2_NS::AbstractHdfProxy * hdfProxy);
		RESQML2_NS::AbstractStratigraphicOrganizationInterpretation* getStratigraphicOrganizationInterpretation() const;
		bool hasIntervalStratigraphicUnitIndices() const;
		int64_t getIntervalStratigraphicUnitIndices(int64_t * stratiUnitIndices);
		gsoap_resqml2_0_1::resqml20__PillarShape getMostComplexPillarGeometry() const;
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_AbstractIjkGridRepresentation) AbstractIjkGridRepresentation;
#endif
	class AbstractIjkGridRepresentation : public AbstractColumnLayerGridRepresentation
	{
	public:
		enum class geometryKind { UNKNOWN = 0, EXPLICIT = 1, PARAMETRIC = 2, LATTICE = 3, NO_GEOMETRY = 4 };
	
		/**
		 * Gets the count of cells in the I direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error	If the count is strictly greater than unsigned int max.
		 *
		 * @returns	The count of cell in the I direction.
		 */
		unsigned int getICellCount() const;

		/**
		 * Sets the count of cells in the I direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @param 	iCount	The count of cells to set in the I direction.
		 */
		void setICellCount(unsigned int iCount);

		/**
		 * Gets the count of cells in the J direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error	If the count is strictly greater than unsigned int max.
		 *
		 * @returns	The count of cell in the J direction.
		 */
		unsigned int getJCellCount() const;

		/**
		 * @brief	Sets the count of cells in the J direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @param 	jCount	The count of cells to set in the J direction.
		 */
		void setJCellCount(unsigned int jCount);

		/**
		 * Gets the count of columns in this grid.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error	If the count of cells in I or J direction is
		 * 									strictly greater than unsigned int max.
		 *
		 * @returns	The column count.
		 */
		unsigned int getColumnCount() const;

		/**
		 * Gets the count of pillars in this grid.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error	If the count of cells in I or J direction is
		 * 									strictly greater than unsigned int max.
		 *
		 * @returns	The pillar count.
		 */
		unsigned int getPillarCount() const;

		/**
		 * Gets the count of K layer gaps in this grid.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error	If the count of cells in I or J direction is
		 * 									strictly greater than unsigned int max.
		 *
		 * @returns	The K Layer gaps count.
		 */
		uint64_t getKGapsCount() const;

		/**
		* For each K Layer except the last one, indicate wether there is a layer or not after it.
		*
		* @param [out]	kGaps	An array for receiving the information about kGaps.
		*						It must have a count of getKCellCount() - 1. It won't be free. A false value in
		* 						@p kGaps means that the corresponding k layer has no gaps just after it.
		*						A true value means that the corresponding k layer has a gap just after it.
		*/
		void getKGaps(bool * kGaps) const;

		/**
		 * Gets the count of faces in this grid. This method requires you have already loaded the split
		 * information thanks to loadSplitInformation().
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::range_error	 	If the count of cells in I, J or K
		 * 										direction is strictly greater than unsigned int max.
		 * @exception	std::invalid_argument	If there is no geometry on this grid.
		 *
		 * @returns	The face count.
		 */
		uint64_t getFaceCount() const;

		/**
		 * Gets the I index of a pillar from its global index in this grid. The global (or
		 * linearized) index of a given pillar is <tt>i pillar + j pillar * (nI pillar)</tt> where
		 * <tt>i pillar</tt> and <tt>j pillar</tt> are respectively the I and J indices of the
		 * pillar and <tt>nI pillar</tt> is the count of pillars in the I direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error 	If the count of cells in I or J direction is
		 * 									strictly greater than unsigned int max.
		 * @exception	std::out_of_range	If @p globalIndex is out of range (greater than or equal to
		 * 									getPillarCount()).
		 *
		 * @param 	globalIndex	The global index of the pillar for which we want to get the I index.
		 *
		 * @returns	The I index of the pillar.
		 */
		unsigned int getIPillarFromGlobalIndex(unsigned int globalIndex) const;

		/**
		 * Gets the J index of a pillar from its global index in this grid. The global (or
		 * linearized) index of a given pillar is <tt>i pillar + j pillar * (nI pillar)</tt> where
		 * <tt>i pillar</tt> and <tt>j pillar</tt> are respectively the I and J indices of the
		 * pillar and <tt>nI pillar</tt> is the count of pillars in the I direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error 	If the count of cells in I or J direction is
		 * 									strictly greater than unsigned int max.
		 * @exception	std::out_of_range	If @p globalIndex is out of range (greater than or equal to
		 * 									getPillarCount()).
		 *
		 * @param 	globalIndex	The global index of the pillar for which we want to get the J index.
		 *
		 * @returns	The J index of the pillar.
		 */
		unsigned int getJPillarFromGlobalIndex(unsigned int globalIndex) const;

		/**
		 * Gets the global index of a pillar from its I and J indices in the grid. The global (or
		 * linearized) index of a given pillar is <tt>i pillar + j pillar * (nI pillar)</tt> where
		 * <tt>i pillar</tt> and <tt>j pillar</tt> are respectively the I and J indices of the
		 * pillar and <tt>nI pillar</tt> is the count of pillars in the I direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error 	If the count of cells in I or J direction is strictly greater
		 * 									than unsigned int max.
		 * @exception	std::out_of_range	If @p iPillar is strictly greater than getICellCount().
		 * @exception	std::out_of_range	If @p jPillar is strictly greater than getJCellCount().
		 *
		 * @param 	iPillar	The I index of the pillar.
		 * @param 	jPillar	The J index of the pillar.
		 *
		 * @returns	The global index of the pillar.
		 */
		unsigned int getGlobalIndexPillarFromIjIndex(unsigned int iPillar, unsigned int jPillar) const;

		/**
		 * Gets the I index of a column from its global index in the grid. The global (or linearized)
		 * index of a given column is <tt>i column + j column * (nI cell)</tt> where
		 * <tt>i column</tt> and <tt>j column</tt> are respectively the I and J indices of the
		 * column and <tt>nI cell</tt> is the count of cells in the I direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error 	If the count of cells in I or J direction is strictly greater
		 * 									than unsigned int max.
		 * @exception	std::out_of_range	If @p globalIndex is out of range (greater than or equal to
		 * 									getColumnCount()).
		 *
		 * @param 	globalIndex	The global index of the column for which we want to get the I index.
		 *
		 * @returns	The I index of the column.
		 */
		unsigned int getIColumnFromGlobalIndex(unsigned int globalIndex) const;

		/**
		 * Gets the J index of a column from its global index in the grid. The global (or linearized)
		 * index of a given column is <tt>i column + j column * (nI cell)</tt> where
		 * <tt>i column</tt> and <tt>j column</tt> are respectively the I and J indices of the
		 * column and <tt>nI cell</tt> is the count of cells in the I direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error 	If the count of cells in I or J direction is strictly greater
		 * 									than unsigned int max.
		 * @exception	std::out_of_range	If @p globalIndex is out of range (greater than or equal to
		 * 									getColumnCount()).
		 *
		 * @param 	globalIndex	The global index of the column for which we want to get the J index.
		 *
		 * @returns	The J index of the column.
		 */
		unsigned int getJColumnFromGlobalIndex(unsigned int globalIndex) const;

		/**
		 * Gets the global index of a column from its I and J indices in the grid. The global (or
		 * linearized) index of a given column is <tt>i column + j column * (nI cell)</tt> where
		 * <tt>i column</tt> and <tt>j column</tt> are respectively the I and J indices of the
		 * column and <tt>nI cell</tt> is the count of cells in the I direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error 	If the count of cells in I or J direction is strictly greater
		 * 									than unsigned int max.
		 * @exception	std::out_of_range	If @p iColumn is greater than or equal to getICellCount().
		 * @exception	std::out_of_range	If @p jColumn is greater than or equal to getJCellCount().
		 *
		 * @param 	iColumn	The I index of the column.
		 * @param 	jColumn	The J index of the column.
		 *
		 * @returns	The global index of the column.
		 */
		unsigned int getGlobalIndexColumnFromIjIndex(unsigned int iColumn, unsigned int jColumn) const;

		/**
		 * Gets the global index of a cell from its I, J and K indices in the grid.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error 	If the count of cells in I, J or K direction is strictly
		 * 									greater than unsigned int max.
		 * @exception	std::out_of_range	If @p iCell is greater than or equal to getICellCount().
		 * @exception	std::out_of_range	If @p jCell is greater than or equal to getJCellCount().
		 * @exception	std::out_of_range	If @p kCell is greater than or equal to getKCellCount().
		 *
		 * @param 	iCell	The I index of the cell.
		 * @param 	jCell	The J index of the cell.
		 * @param 	kCell	The K index of the cell.
		 *
		 * @returns	The global index of the cell.
		 */
		unsigned int getGlobalIndexCellFromIjkIndex(unsigned int iCell, unsigned int jCell, unsigned int kCell) const;

		/**
		 * Queries if this grid is right handed, as determined by the triple product of tangent vectors
		 * in the I, J, and K directions.
		 *
		 * @exception	std::logic_error	If this grid has no geometry. Or, if it is in an unrecognized
		 * 									version of RESQML.
		 *
		 * @returns	True if this grid is right handed, false if it is not.
		 */
		bool isRightHanded() const;

		/**
		 * Gets all the pillars which correspond to all split coordinate lines. The order of the pillars
		 * corresponds to the order of the split coordinate lines.
		 *
		 * @exception	std::invalid_argument	If the HDF proxy is missing.
		 * @exception	std::invalid_argument	If there is no geometry or no split coordinate line in
		 * 										this grid.
		 * @exception	std::logic_error	 	If the indices of the pillars corresponding to the split
		 * 										coordinate lines are not stored within an HDF5 integer
		 * 										array.
		 *
		 * @param [out]	pillarIndices	An array for receiving the indices of the pillars corresponding
		 * 								to the split coordinate lines. It must be preallocated with a
		 * 								size of getSplitCoordinateLineCount().
		 * @param 	   	reverseIAxis 	(Optional) True to reverse I axis. Default value is false.
		 * @param 	   	reverseJAxis 	(Optional) True to reverse J axis. Default value is false.
		 */
		void getPillarsOfSplitCoordinateLines(unsigned int * pillarIndices, bool reverseIAxis = false, bool reverseJAxis = false) const;

		/**
		 * Gets all the columns impacted by all the split coordinate lines. The order of the columns
		 * corresponds to the order of the split coordinate lines.
		 *
		 * @exception	std::invalid_argument	If the HDF proxy is missing.
		 * @exception	std::invalid_argument	If there is no geometry or no split coordinate line in
		 * 										this grid.
		 * @exception	std::logic_error	 	If the indices of the columns impacted by the split
		 * 										coordinate lines are not stored within an HDF5 integer
		 * 										array.
		 *
		 * @param [out]	columnIndices	An array for receiving the indices of the columns impacted by the
		 * 								split coordinate lines. It must be preallocated with a size equal
		 * 								to the last value of the array outputted from
		 * 								getColumnCountOfSplitCoordinateLines().
		 * @param 	   	reverseIAxis 	(Optional) True to reverse i axis. Default value is false.
		 * @param 	   	reverseJAxis 	(Optional) True to reverse j axis. Default value is false.
		 */
		void getColumnsOfSplitCoordinateLines(unsigned int * columnIndices, bool reverseIAxis = false, bool reverseJAxis = false) const;

		/**
		 * Gets the cumulative count of columns impacted by all the split coordinate lines. The order of
		 * the cumulative count values corresponds to the order of the split coordinates lines.
		 *
		 * @exception	std::invalid_argument	If the HDF proxy is missing.
		 * @exception	std::invalid_argument	If there is no geometry or no split coordinate line in
		 * 										this grid.
		 * @exception	std::logic_error	 	If the cumulative count of the columns impacted by the
		 * 										split coordinate lines are not stored within an HDF5
		 * 										integer array.
		 *
		 * @param [out]	columnIndexCountPerSplitCoordinateLine	An array for receiving the cumulative
		 * 														count of columns impacted by the split
		 * 														coordinate lines.
		 */
		void getColumnCountOfSplitCoordinateLines(unsigned int * columnIndexCountPerSplitCoordinateLine) const;

		/**
		 * Gets the split coordinate lines count.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this IJK grid.
		 * @exception	std::range_error	 	If the count of split coordinate lines is strictly
		 * 										greater than unsigned int max.
		 *
		 * @returns	The split coordinate lines count.
		 */
		uint64_t getSplitCoordinateLineCount() const;

		/**
		 * Gets the split coordinate lines count within the block. Block information must be loaded thanks
		 * to loadBlockInformation().
		 *
		 * @exception	std::invalid_argument	If the block information is not loaded.
		 *
		 * @returns	The split coordinate lines count within the block.
		 */
		uint64_t getBlockSplitCoordinateLineCount() const;
		
		/**
		 * Gets the split nodes count.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this IJK grid.
		 *
		 * @returns	The split nodes count.
		 */
		uint64_t getSplitNodeCount() const;
		
		/**
		 * Loads the split information into memory to speed up processes. Be aware that you must unload
		 * by yourself this memory thanks to unloadSplitInformation().
		 */
		void loadSplitInformation();
		/** Unloads the split information from memory. */
		void unloadSplitInformation();
		
		/**
		 * @brief	Checks either a given column edge is splitted or not. This method requires that you
		 * 			have already loaded the split information.
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::invalid_argument	If the split information is not loaded.
		 * @exception	std::out_of_range	 	If @p iColumn is strictly greater than getICellCount().
		 * @exception	std::out_of_range	 	If @p iColumn is strictly greater than getJCellCount().
		 * @exception	std::out_of_range	 	If @p edge is strictly greater than 3.
		 *
		 * @param 	iColumn	The I index of the column.
		 * @param 	jColumn	The J index of the column.
		 * @param 	edge   	0 for edge from i to i+1, lower j connection; 1 for edge from j to j+1, upper
		 * 					i connection; 2 for edge from i+1 to i, upper j connection; 3 for edge from
		 * 					j+1 to j, lower i connection.
		 *
		 * @returns	True if the column edge is splitted, false if not.
		 */
		bool isColumnEdgeSplitted(unsigned int iColumn, unsigned int jColumn, unsigned int edge) const;

		/**
		 * @brief	Gets the XYZ point index in the HDF dataset from the corner of a cell. This method
		 * 			requires that you have already loaded the split information.
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::invalid_argument	If the split information is not loaded.
		 * @exception	std::out_of_range	 	If @p iCell > getICellCount(), @p jCell >
		 * 										getJCellCount() or @p kCell > getKCellCount().
		 * @exception	std::out_of_range	 	If @p corner > 7.
		 *
		 * @param 	iCell 	The I index of the cell.
		 * @param 	jCell 	The J index of the cell.
		 * @param 	kCell 	The K index of the cell.
		 * @param 	corner	Index of the corner: 0 for (0,0,0); 1 for (1,0,0); 2 for (1,1,0); 3 for (0,1,
		 * 					0); 4 for (0,0,1); 5 for (1,0,1); 6 for (1,1,1); 7 for (0,1,1).
		 *
		 * @returns	The index of the XYZ point in the HDF dataset corresponding to the corner of the
		 * 			cell. Keep in mind to multiply the result by 3 to get the X index since the points
		 * 			are triplet of values.
		 */
		uint64_t getXyzPointIndexFromCellCorner(unsigned int iCell, unsigned int jCell, unsigned int kCell, unsigned int corner) const;
		
		/**
		 * Tells for each pillar if its geometry is defined. This method only looks at the corresponding
		 * @c PillarGeometryIsDefined attribute in the gSOAP proxy.
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::range_error	 	If the count of cells in I or J direction is strictly
		 * 										greater than unsigned int max.
		 * @exception	std::invalid_argument	If there is no geometry on this IJK grid.
		 * @exception	std::invalid_argument	If the values indicating for each pillar if its geometry
		 * 										is defined are neither stored in an HDF5 boolean array
		 * 										nor in a boolean constant array.
		 *
		 * @param [out]	pillarGeometryIsDefined	An array for receiving a boolean value for each pillar
		 * 										indicating if its geometry is defined or not. It must be
		 * 										preallocated with a size of getPillarCount().
		 * @param 	   	reverseIAxis		   	(Optional) True to reverse i axis. Default value is false.
		 * @param 	   	reverseJAxis		   	(Optional) True to reverse j axis. Default value is false.
		 */
		void getPillarGeometryIsDefined(bool * pillarGeometryIsDefined, bool reverseIAxis = false, bool reverseJAxis = false) const;
		
		/**
		 * Indicates if this grid contains a flag on each cell indicating if its geometry is defined or not
		 * (i.e. meaning that at least one of the coordinates of at least one of the cell vertex is NaN).
		 * Do not mix this flag with the active one : http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-000-289-0-C-sv2010.html
		 *
		 * @returns	True if this grid contains a flag on each cell indicating if its geometry is defined or not, false if not.
		 */
		bool hasCellGeometryIsDefinedFlags() const;

		/**
		 * Get the flags for each cell indicating if its geometry is defined or not
		 * (i.e. meaning that at least one of the coordinates of at least one of the cell vertex is NaN).
		 * Do not mix this flag with the active one : http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-000-289-0-C-sv2010.html
		 *
		 * @exception	std::invalid_argument	If this grid has no geometry or no CellGeometryIsDefined flags.
		 * @exception	std::invalid_argument	If the CellGeometryIsDefined flags are neither
		 * 										stored in an HDF5 boolean array nor in a boolean constant
		 * 										array.
		 *
		 * @param [out]	cellGeometryIsDefinedFlags	An array for receiving the information about CellGeometryIsDefined flags.
		 *								It must have a count of getCellCount() and must follow the
		 * 								index ordering I then J then K. It won't be free. A zero value in
		 * 								@p cellGeometryIsDefinedFlags means that the corresponding cell geometry is not defined. A non
		 * 								zero value means that the corresponding cell geometry is defined.
		 * @param 	   	reverseIAxis	(Optional) True to reverse i axis. Default value is false.
		 * @param 	   	reverseJAxis	(Optional) True to reverse j axis. Default value is false.
		 * @param 	   	reverseKAxis	(Optional) True to reverse k axis. Default value is false.
		 */
		void getCellGeometryIsDefinedFlags(bool * cellGeometryIsDefinedFlags, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;
		
		/**
		 * Sets the flags for each cell indicating if its geometry is defined or not
		 * (i.e. meaning that at least one of the coordinates of at least one of the cell vertex is NaN).
		 * Do not mix this flag with the active one : http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-000-289-0-C-sv2010.html
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If this grid has no geometry.
		 *
		 * @param [in]	  	cellGeometryIsDefinedFlags	An array containing the CellGeometryIsDefined flags.
		 *									It must have a count of getCellCount() and must follow the
		 * 									index ordering I then J then K. A zero value in
		 * 									@p cellGeometryIsDefinedFlags means that the corresponding cell geometry is not defined. A non
		 * 									zero value means that the corresponding cell geometry is defined.
		 * @param [in]		proxy			(Optional) The HDF proxy for writing the @p cellGeometryIsDefinedFlags
		 * 									values. If @c nullptr (default), then the default HDF proxy will be
		 * 									used.
		 */
		void setCellGeometryIsDefinedFlags(uint8_t* cellGeometryIsDefinedFlags, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Set to "defined" the flags for each cell indicating if its geometry is defined or not
		 * (i.e. meaning that at least one of the coordinates of at least one of the cell vertex is NaN).
		 * Do not mix this flag with the active one : http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-000-289-0-C-sv2010.html
		 */
		void setAllCellGeometryFlagsToDefined();
		
		/**
		 * Get the XYZ points count in each K layer interface.
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::range_error	 	If the count of cells in I or J direction is strictly
		 * 										greater than unsigned int max.
		 * @exception	std::invalid_argument	If there is no geometry on this IJK grid.
		 * @exception	std::range_error	 	If the count of split coordinate lines is strictly
		 * 										greater than unsigned int max.
		 *
		 * @returns	The XYZ point count of each K layer interface.
		 */
		uint64_t getXyzPointCountOfKInterface() const;
		/*
		 * Gets all the XYZ points of a particular K interface. XYZ points are given in the local CRS.
		 * This method is not const since it is optimized in order not to recompute the pillar
		 * information but to get it as input.
		 *
		 * @param 		  	kInterface	The K interface index starting from zero to kCellCount.
		 * @param [out]	xyzPoints 		A linearized 2d array where the first (quickest) dimension is
		 * 								coordinate dimension (XYZ) and second dimension is vertex
		 * 								dimension. It must be pre allocated with a size of
		 * 								<tt>3 * getXyzPointCountOfKInterface()</tt>.
		 */
		void getXyzPointsOfKInterface(unsigned int kInterface, double * xyzPoints);
		/**
		 * @brief Gets all the XYZ points of a particular sequence of K interfaces. XYZ points are given in the
		 * local CRS.
		 *
		 * @exception	std::out_of_range	 	If @p kInterfaceStart > getKCellCount() or @p
		 * 										kInterfaceEnd > getKCellCount() + getKGapsCount().
		 * @exception	std::range_error	 	If @p kInterfaceStart > @p kInterfaceEnd.
		 * @exception	std::invalid_argument	If @p xyzPoints is nullptr.
		 *
		 * @param 	   	kInterfaceStart	The K index of the starting interface taken from zero to
		 * 								getKCellCount().
		 * @param 	   	kInterfaceEnd  	The K index of the ending interface taken from zero to
		 * 								getKCellCount() + getKGapsCount().
		 * @param [out]	xyzPoints	   	A linearized 2d array where the first (quickest) dimension is
		 * 								coordinate dimension (XYZ) and second dimension is vertex
		 * 								dimension. It must be preallocated with a size of
		 * 								<tt>3 *</tt> getXyzPointCountOfKInterface() <tt>*
		 * 								(kInterfaceEnd - kInterfaceStart + 1)</tt>.
		 */
		void getXyzPointsOfKInterfaceSequence(unsigned int kInterfaceStart, unsigned int kInterfaceEnd, double * xyzPoints);
		
		bool isNodeGeometryCompressed() const;
		
		gsoap_resqml2_0_1::resqml20__KDirection getKDirection() const;
		
		geometryKind getGeometryKind() const;
	};
	
	
#ifdef SWIGPYTHON
	%rename(Resqml2_IjkGridLatticeRepresentation) IjkGridLatticeRepresentation;
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

		void setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry,
			gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind,
			bool isRightHanded,
			double originX, double originY, double originZ,
			double directionIX, double directionIY, double directionIZ, double spacingI,
			double directionJX, double directionJY, double directionJZ, double spacingJ,
			double directionKX, double directionKY, double directionKZ, double spacingK, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		void addSeismic3dCoordinatesToPatch(
			unsigned int patchIndex,
			double startInline, double incrInline, unsigned int countInline,
			double startCrossline, double incrCrossline, unsigned int countCrossline,
			unsigned int countSample, AbstractRepresentation * seismicSupport);
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_IjkGridExplicitRepresentation) IjkGridExplicitRepresentation;
#endif
	class IjkGridExplicitRepresentation : public AbstractIjkGridRepresentation
	{
	public:
		/**
		 * @brief Sets the geometry of this IJK grid as explicit coordinate line nodes. See RESQML Usage,
		 * Technical guide and Enterprise Architect diagrams for details.
		 *
		 * @exception	std::invalid_argument	If @p points is @c nullptr.
		 * @exception	std::invalid_argument	If <tt>(splitCoordinateLineCount != 0 &amp;&amp;
		 * 										(pillarOfCoordinateLine == nullptr ||
		 * 										splitCoordinateLineColumnCumulativeCount == nullptr ||
		 * 										splitCoordinateLineColumns == nullptr))</tt>.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If @p localCrs is @c nullptr and no default local 3d CRS
		 * 										is defined.
		 *
		 * @param 		  	mostComplexPillarGeometry					The most complex pillar geometry
		 * 																which occurs on this reservoir grid.
		 * @param 		  	kDirectionKind								The direction of the K axis on
		 * 																the earth. It is not directly related
		 * 																to Z of the vertical CRS but to the
		 * 																physical earth (as the vertical CRS
		 * 																is).
		 * @param 		  	isRightHanded								Indicates that the IJK grid is
		 * 																right handed, as determined by the
		 * 																triple product of tangent vectors in
		 * 																the I, J, and K directions.
		 * @param [in]	  	points										XYZ double triplets ordered by i
		 * 																then j then split then k. Count must
		 * 																be <tt>((iCellCount+1) *
		 * 																(jCellCount+1) +
		 * 																splitCoordinateLineCount) *
		 * 																kCellCount</tt>.
		 * @param [in,out]	proxy										(Optional) The HDF proxy where
		 * 																all numerical values will be stored.
		 * 																If @c nullptr, then the default HDF
		 * 																proxy of the repository will be used.
		 * @param 		  	splitCoordinateLineCount					(Optional) The count of split
		 * 																coordinate line. A grid pillar is
		 * 																splitted in up to 4 coordinate lines.
		 * @param [in]	  	pillarOfCoordinateLine						(Optional) For each split
		 * 																coordinate line, indicates which
		 * 																pillar it belongs to. Pillars are
		 * 																identified by their absolute 1d index
		 * 																<tt>(iPillar + jPillar *
		 * 																iPillarCount)</tt> where
		 * 																<tt>iPillarCount ==
		 * 																iCellCount+1</tt>. Count is
		 * 																splitCoordinateLineCount.
		 * @param [in]	  	splitCoordinateLineColumnCumulativeCount	(Optional) For each split
		 * 																coordinate line, indicates how many
		 * 																columns of the ijk grid are incident
		 * 																to it (minimum is one and maximum is
		 * 																3) + the count of all incident
		 * 																columns of previous spit coordinate
		 * 																lines in the array. For example
		 * 																<tt>{1, 4, 6}</tt> would mean that
		 * 																the first split coordinate line is
		 * 																incident to only one column, the
		 * 																second split coordinate line is
		 * 																incident to <tt>4 - 1 = 3</tt>
		 * 																columns and the third column is
		 * 																incident to <tt>6 - 4 = 2</tt>
		 * 																columns. Count is
		 * 																splitCoordinateLineCount.
		 * @param [in]	  	splitCoordinateLineColumns					(Optional) For each split
		 * 																coordinate line, indicates which
		 * 																columns are incident to it. Count is
		 * 																the last value in the
		 * 																splitCoordinateLineColumnCumulativeCount
		 * 																array. Columns are identified by
		 * 																their absolute 1d index
		 * 																<tt>(iColumn</tt>
		 * 																<tt> + jColumn * iColumnCount)</tt>
		 * 																where
		 * 																Column == Cell.
		 * @param [in]	  	definedPillars								(Optional) For each pillar : 0 if
		 * 																pillar is not defined (i.e points
		 * 																equal to NaN) else the pillar is
		 * 																defined.  This information overrides
		 * 																any pillar geometry information. If
		 * 																null, then all pillars are assumed to
		 * 																be defined.
		 * @param [in]	  	localCrs									(Optional) The local CRS where
		 * 																the points are given. If @c nullptr
		 * 																(default) then the default CRS of the
		 * 																repository will be used.
		 */
		void setGeometryAsCoordinateLineNodes(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			double const* points, EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t splitCoordinateLineCount = 0, unsigned int const* pillarOfCoordinateLine = nullptr,
			unsigned int const* splitCoordinateLineColumnCumulativeCount = nullptr, unsigned int const* splitCoordinateLineColumns = nullptr,
			int8_t const* definedPillars = nullptr, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		void setGeometryAsCoordinateLineNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & points, EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t splitCoordinateLineCount = 0, const std::string & pillarOfCoordinateLine = "",
			const std::string & splitCoordinateLineColumnCumulativeCount = "", const std::string & splitCoordinateLineColumns = "",
			const std::string & definedPillars = "", EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_IjkGridParametricRepresentation) IjkGridParametricRepresentation;
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

		void setGeometryAsParametricNonSplittedPillarNodes(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, bool isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, unsigned int controlPointMaxCountPerPillar, short * pillarKind,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		void setGeometryAsParametricNonSplittedPillarNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		void setGeometryAsParametricSplittedPillarNodes(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, bool isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, unsigned int controlPointMaxCountPerPillar, short * pillarKind, EML2_NS::AbstractHdfProxy* proxy,
			uint64_t splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
			unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		void setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars, EML2_NS::AbstractHdfProxy* proxy,
			uint64_t splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
			const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		void setGeometryAsParametricSplittedPillarNodes(bool isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, unsigned int controlPointCountPerPillar, short pillarKind, EML2_NS::AbstractHdfProxy* proxy,
			uint64_t splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
			unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		void setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointCountPerPillar, short pillarKind, EML2_NS::AbstractHdfProxy* proxy,
			uint64_t splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
			const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_IjkGridNoGeometryRepresentation) IjkGridNoGeometryRepresentation;
#endif	
	class IjkGridNoGeometryRepresentation : public AbstractIjkGridRepresentation
	{
	public:
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_GridConnectionSetRepresentation) GridConnectionSetRepresentation;
#endif
	class GridConnectionSetRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:
		/**
		 * Indicates whether the cell connections are associated to interpretation or not.
		 *
		 * @returns	True if associated to interpretations, false if not.
		 */
		bool isAssociatedToInterpretations() const;

		/**
		 * Gets the (fault) interpretation index cumulative counts of this grid connection
		 * representation.
		 *
		 * @exception	std::invalid_argument	If this grid connection set representation does not
		 * 										contain any (fault) interpretation association.
		 * @exception	std::logic_error	 	If the intepretation indices cumulative counts are not
		 * 										stored in a HDF5 integer array.
		 *
		 * @param [out]	cumulativeCount	A buffer for receiving the cumulative counts. Must be
		 * 								preallocated with a size of getCellIndexPairCount(). The number
		 * 								of interpretations associated to the connection at index @c i is
		 * 								<tt>cumulativeCount[i]</tt>.
		 */
		void getInterpretationIndexCumulativeCount(uint64_t* cumulativeCount) const;

		/**
		 * Gets the (fault) interpretation indices of this grid connection representation.
		 *
		 * @exception	std::invalid_argument	If this grid connection set representation does not
		 * 										contain any (fault) interpretation association.
		 * @exception	std::logic_error	 	If the intepretation indices are not stored in a HDF5
		 * 										integer array.
		 *
		 * @param [out]	interpretationIndices	A buffer for receiving the interpretation indices. It
		 * 										must be preallocated with a size equals to the last value
		 * 										of @c cumulativeCount after calling
		 * 										<tt>getInterpretationIndexCumulativeCount(cumulativeCount).</tt>
		 */
		void getInterpretationIndices(int64_t * interpretationIndices) const;

		/**
		 * Gets the null value for interpretation index.
		 *
		 * @exception	std::invalid_argument	If this grid connection set representation does not
		 * 										contain any (fault) interpretation association.
		 * @exception	std::logic_error	 	If the intepretation indices are not stored in a HDF5
		 * 										integer array.
		 *
		 * @returns	The interpretation index null value.
		 */
		int64_t getInterpretationIndexNullValue() const;
		
		/**
		 * Gets the cell index pair count of this grid connection set representation.
		 *
		 * @returns	The cell index pair count.
		 */
		uint64_t getCellIndexPairCount() const;

		/**
		 * @brief	Gets the count of cell index pairs which correspond to a particular interpretation or to no interpretation.
		 *
		 * @exception	std::invalid_argument	If the HDF5 library could not read the count of
		 * 										interpretation indices associated to this grid connection
		 * 										set representation.
		 * @exception	std::logic_error	 	If the intepretation indices are not stored in a HDF5
		 * 										integer array.
		 * @exception	std::out_of_range	 	If @p interpretationIndex is out of range.
		 *
		 * @param 	interpretationIndex	The index of an interpretation in the collection of feature
		 * 								interpretation of this grid connection set.
		 *								Or -1 for having cell index pair count which are not associated to any interpretation at all.
		 *
		 * @returns	The count of cell index pairs which correspond to the interpretation at index @p
		 * 			interpretationIndex or to no interpretation.
		 */
		uint64_t getCellIndexPairCountFromInterpretationIndex(int64_t interpretationIndex) const;
		
		/**
		 * Gets the cell index pairs of this grid connection set representation
		 *
		 * @exception	logic_error	If the cell index pairs are not stored in a HDF5 integer array.
		 *
		 * @param [out]	cellIndexPairs	A buffer for receiving the cell index pairs. It must be
		 * 								preallocated with a size of <tt>2 * getCellIndexPairCount()</tt>.
		 * 								Two consecutive values <tt>cellIndexPairs[i]</tt> and
		 * 								<tt>cellIndexPairs[i+1]</tt> constitute a pair of cell index.
		 *
		 * @returns	The null value.
		 */
		int64_t getCellIndexPairs(int64_t * cellIndexPairs) const;
		
		/**
		 * Gets the cell index pairs, the grid index pairs (optional) and the local face index pairs
		 * (optional) which correspond to a particular interpretation or to no interpretation.
		 *
		 * @exception	std::logic_error	 	If the intepretation indices or interpretation indices
		 * 										cumulative counts are not stored in a HDF5 integer array.
		 * @exception	std::out_of_range	 	If @p interpretationIndex is out of range.
		 *
		 * @param [out]	  	cellIndexPairs	   	Mandatory buffer to receive the cell index pairs. Must be
		 * 										preallocated with
		 * 										<tt>2 * getCellIndexPairCountFromInterpretationIndex(interpretationIndex)</tt>.
		 * @param [in,out]	gridIndexPairs	   	Optional buffer to receive the grid index pairs. Please
		 * 										set to @p nullptr for not collecting these pairs. Must be
		 * 										preallocated with
		 * 										<tt>2 * getCellIndexPairCountFromInterpretationIndex(interpretationIndex)</tt>.
		 * @param [in,out]	localFaceIndexPairs	Optional buffer to receive the local face index pairs.
		 * 										Please set to @p nullptr for not collecting these pairs.
		 * 										Must be preallocated with
		 * 										<tt>2 * getCellIndexPairCountFromInterpretationIndex(interpretationIndex)</tt>.
		 *										See http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-000-252-0-C-sv2010.html for IJK cell face index convention.
		 * @param 		  	interpretationIndex	The index of an interpretation in the collection of
		 * 										feature interpretation of this grid connection set.
		 *										Or -1 for having information for cells which are not associated to any interpretation at all.
		 */
		void getGridConnectionSetInformationFromInterpretationIndex(int64_t * cellIndexPairs, unsigned short * gridIndexPairs, int * localFaceIndexPairs, int64_t interpretationIndex) const;

		/**
		 * Indicates if this grid connection set representation contains information on the connected
		 * faces of the cell pairs.
		 *
		 * @returns	True if there exists information on connected faces, false if not.
		 */
		bool hasLocalFacePerCell() const;

		/**
		 * Gets the local face per cell index pairs of this grid connection representation. Please check
		 * that this grid connection set representation has local face per cell index pairs thanks to
		 * hasLocalFacePerCell() before calling this method.
		 *
		 * @exception	std::invalid_argument	If this representation has no local face per cell pair.
		 * @exception	std::logic_error	 	If the local face per cell index pairs are not stored
		 * 										in a HDF5 integer array.
		 *
		 * @param [out]	localFacePerCellIndexPairs	A buffer for receiving the local face per cell index
		 * 											pairs. It must be preallocated with a size of
		 * 											<tt>getCellIndexPairCount()*2</tt> and won't be freed
		 * 											by FESAPI.
		 *											See http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-000-252-0-C-sv2010.html for IJK cell face index convention.
		 *
		 * @returns	The null value used in @p localFacePerCellIndexPairs.
		 */
		int64_t getLocalFacePerCellIndexPairs(int * localFacePerCellIndexPairs) const;
		
		/**
		 * Indicates if this grid connection set representation is based on several grids.
		 *
		 * @returns	True if it is based on several grids, false if not.
		 */
		bool isBasedOnMultiGrids() const;
		
		/**
		 * Gets the grid index pairs of this grid connection representation. Please check that this grid
		 * connection set representation is based on several grids thanks to isBasedOnMultiGrids()
		 * before calling this method.
		 *
		 * @exception	std::invalid_argument	If this representation is not based on several grids.
		 * @exception	std::logic_error	 	If the grid index pairs are not stored in a HDF5 integer
		 * 										array.
		 *
		 * @param [out]	gridIndexPairs	A buffer for receiving the grid index pairs. It must be
		 * 								preallocated with a size <tt>getCellIndexPairCount()*2</tt> and
		 * 								won't be freed by fesapi.
		 */
		void getGridIndexPairs(unsigned short * gridIndexPairs) const;
		
		/**
		 * Pushes back a grid representation which is one of the support of this representation. Pushes
		 * back this representation as a grid connection information of the grid representation as well.
		 *
		 * @exception	std::invalid_argument	If @p supportingGridRep is @c nullptr.
		 *
		 * @param [in]	supportingGridRep	The supporting grid representation to push back.
		 */
		void pushBackSupportingGridRepresentation(AbstractGridRepresentation * supportingGridRep);
		
		/**
		 * @brief	Sets the cell index pairs of this grid connection set representation.
		 *			If this instance is supported by a single grid, then optional gridIndex* parameters are not needed.
		 *			Default cell index null value is set to -1.
		 *
		 * @exception	std::invalid_argument	If @p cellIndexPairCount is 0.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If @p cellIndexPairNullValue is strictly greater than
		 * 										uint64_t max. The XML null value cannot be greater than a
		 * 										64 bits signed integer cause of gSOAP mappings.
		 *
		 * @param 		  	cellIndexPairCount	  	The count of cell index pairs. It is half the size of
		 * 											@p cellIndexPair (and of @p gridIndexPair if used).
		 * @param [in]	  	cellIndexPair		  	All the cell index pair in a 1d array where the cell
		 * 											indices go faster than the pair.
		 * @param 		  	cellIndexPairNullValue	(Optional) The integer null value used in @p cellIndexPair.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where the numerical values (cell
		 * 											indices) are stored. If @c nullptr, then the default
		 * 											HDF proxy of the repository will be used.
		 * @param 		  	gridIndexPairNullValue	(Optional) The integer null value used in @p
		 * 											gridIndexPair. 
		 * @param [in]	  	gridIndexPair		  	(Optional) All the grid index pair in a 1d array
		 * 											where the grid indices go faster than the pair. The
		 * 											grid at an index must correspond to the cell at the
		 * 											same index in the @p cellIndexPair array.
		 */
		void setCellIndexPairs(uint64_t cellIndexPairCount, int64_t * cellIndexPair, int64_t cellIndexPairNullValue = -1, EML2_NS::AbstractHdfProxy * proxy = nullptr);
		
		/**
		 * @brief	Sets the cell index pairs of this grid connection set representation.
		 *			If this instance is supported by a single grid, then optional gridIndex* parameters are not needed.
		 *			Default cell index null value is set to -1.
		 *
		 * @exception	std::invalid_argument	If @p cellIndexPairCount is 0.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If @p cellIndexPairNullValue is strictly greater than
		 * 										uint64_t max. The XML null value cannot be greater than a
		 * 										64 bits signed integer cause of gSOAP mappings.
		 *
		 * @param 		  	cellIndexPairCount	  	The count of cell index pairs. It is half the size of
		 * 											@p cellIndexPair (and of @p gridIndexPair if used).
		 * @param [in]	  	cellIndexPair		  	All the cell index pair in a 1d array where the cell
		 * 											indices go faster than the pair.
		 * @param 		  	cellIndexPairNullValue	(Optional) The integer null value used in @p cellIndexPair.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where the numerical values (cell
		 * 											indices) are stored. If @c nullptr, then the default
		 * 											HDF proxy of the repository will be used.
		 * @param 		  	gridIndexPairNullValue	(Optional) The integer null value used in @p
		 * 											gridIndexPair. 
		 * @param [in]	  	gridIndexPair		  	(Optional) All the grid index pair in a 1d array
		 * 											where the grid indices go faster than the pair. The
		 * 											grid at an index must correspond to the cell at the
		 * 											same index in the @p cellIndexPair array.
		 */
		void setCellIndexPairs(uint64_t cellIndexPairCount, int64_t * cellIndexPair, int64_t cellIndexPairNullValue, EML2_NS::AbstractHdfProxy * proxy, uint16_t gridIndexPairNullValue, uint16_t const * gridIndexPair);
		
		/**
		 * @brief Sets the local face per cell index pairs of this grid connection set representation. Local
		 * face-per-cell indices are used because global face indices need not have been defined. The
		 * numerical values will be written as a new HDF5 dataset in an existing HDF5 file.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *				std::logic_error		If the cell index pairs have not been set yet.
		 *
		 * @param [in]	  	localFacePerCellIndexPair	All the local face per cell index pairs in a 1d
		 * 												array where the local face per cell indices go
		 * 												faster than the pair. The local face per cell at
		 * 												an index must correspond to the cell at the same
		 * 												index in the 1d array containing the cell index
		 * 												pairs.
		 *												See http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-000-252-0-C-sv2010.html for IJK cell face index convention.
		 * @param 		  	nullValue				 	The null value in @p localFacePerCellIndexPair.
		 * @param [in,out]	proxy					 	The HDF proxy where the numerical values (cell
		 * 												indices) are stored. If @c nullptr, then the
		 * 												default HDF proxy of the repository will be used.
		 */
		void setLocalFacePerCellIndexPairs(int * localFacePerCellIndexPair, int nullValue, EML2_NS::AbstractHdfProxy * proxy = nullptr);
		
		/**
		 * For each connection in this grid connection set representation, allows to map zero to several
		 * feature interpretation. 
		 *
		 * @exception	std::logic_error		If <tt>getCellIndexPairs() == 0</tt>.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param [in]	  	cumulativeInterpCount	 	For each connection, the cumulative count of the
		 * 												associated interpretations. Count must be equal to getCellIndexPairs().
		 * @param [in]	  	interpIndices			 	The index of the interpretation associated to cell index pairs.
		 * 												The count of this array is @p
		 * 												cumulativeInterpCount[cumulativeInterpCount.size() - 1]. The nullValue is -1.
		 *												Interpretation index is related to pushBackInterpretation.
		 * @param [in,out]	proxy					 	The Hdf proxy where the numerical values will be
		 * 												stored.
		 */
		void setConnectionInterpretationIndices(uint64_t const* cumulativeInterpCount, int64_t const* interpIndices, EML2_NS::AbstractHdfProxy * proxy = nullptr);
		
		/**
		 * Pushes back an interpretation which can be mapped with some connections.
		 * Do not use this method when you assign a single interpreation to all connections. Use
		 *
		 * @exception	std::invalid_argument	If @p interp is @c nullptr.
		 *
		 * @param [in]	interp	The interpretation to push back.
		 */
		void pushBackInterpretation(AbstractFeatureInterpretation* interp);

		/**
		 * For each connection in this grid connection set representation, associate the same interpretation.
		 *
		 * @exception	std::logic_error		If <tt>getCellIndexPairs() == 0</tt>.
		 * @exception	std::logic_error		If interpretation has already been pushed into this instance.
		 *
		 * @param [in]	  	interp				The interpretation to associate to all connections.
		 * @param [in,out]	proxy				The Hdf proxy where the numerical values will be stored.
		 */
		void setInterpretationForAllConnections(class AbstractFeatureInterpretation* interp, EML2_NS::AbstractHdfProxy * proxy = nullptr);

		/**
		 * Gets the UUID of a particular (fault) interpretation of this grid connection set.
		 *
		 * @exception	std::invalid_argument	If this grid connection set representation does not
		 * 										contain fault interpretation association.
		 * @exception	std::invalid_argument	If the associated feature interpretation at position @p
		 * 										interpretationIndex is not a fault one. This is legal but
		 * 										not yet implemented.
		 * @exception	std::out_of_range	 	If @p interpretationIndex is out of range.
		 *
		 * @param 	interpretationIndex	The index of a (fault) interpretation in the collection of
		 * 								feature interpretation of this grid connection set.
		 *
		 * @returns	The UUID of the (fault) interpretation at index @p interpretationIndex.
		 */
		std::string getInterpretationUuidFromIndex(unsigned int interpretationIndex) const;

		/**
		 * Gets a particular (fault) interpretation of this grid connection set.
		 *
		 * @exception	std::invalid_argument	If this grid connection set representation does not
		 * 										contain fault interpretation association.
		 * @exception	std::invalid_argument	If the associated feature interpretation at position @p
		 * 										interpretationIndex is not a fault one. This is legal but
		 * 										not yet implemented.
		 * @exception	std::out_of_range	 	If @p interpretationIndex is out of range.
		 *
		 * @param 	interpretationIndex	The index of a (fault) interpretation in the collection of
		 * 								feature interpretation of this grid connection set.
		 *
		 * @returns	The (fault) interpretation at index @p interpretationIndex.
		 */
		AbstractFeatureInterpretation * getInterpretationFromIndex(int64_t interpretationIndex) const;

		/**
		 * Get the count of interpretations in this grid connection set.
		 *
		 * @exception	range_error	If the count of associated interpretations is strictly greater than
		 * 							unsigned int.
		 *
		 * @returns	The interpretation count.
		 */
		uint64_t getInterpretationCount() const;

		/**
		 * Gets the count of supporting grid representations of this grid connection representation.
		 *
		 * @exception	std::range_error	If the count of supporting grid representations is strictly
		 * 									greater than unsigned int maximum value.
		 *
		 * @returns	The supporting grid representation count.
		 */
		unsigned int getSupportingGridRepresentationCount() const;

		/**
		 * Gets the supporting grid representation located at a specific index of this grid connection set
		 * representation.
		 * 
		 * @exception std::out_of_range If @p index is out of range.
		 * 								
		 * @param	index	Zero-based index of the supporting grid representation we look for.
		 * 
		 * @returns The supporting grid representation at position @p index.
		 */
		AbstractGridRepresentation* getSupportingGridRepresentation(unsigned int index);
	};
	
	/**
	 * @brief	Specification of the vector field upon which the streamlines are based.
	 *
	 * 			Streamlines are commonly used to trace the flow of phases (water / oil / gas / total)
	 *			based upon their flux at a specified time. They may also be used for trace components
	 *			for compositional simulation, e.g., CO2, or temperatures for thermal simulation.
	 */
#ifdef SWIGPYTHON
	%rename(Resqml2_StreamlinesFeature) StreamlinesFeature;
#endif	
	class StreamlinesFeature : public AbstractTechnicalFeature
	{
	public:
		/**
		 * Gets the Time series associated to this streamlines feature.
		 *
		 * @exception	std::logic_error	If this feature is partial or if this feature is standard invalid.
		 *
		 * @returns	The associated streamlines feature.
		 */
		EML2_NS::TimeSeries* getTimeSeries() const;

		/**
		 * Gets the time index in the Time series associated to this streamlines feature.
		 *
		 * @exception	std::logic_error	If this feature is partial.
		 *
		 * @returns	the time index in the Time series associated to this streamlines feature
		 */
		uint64_t getTimeIndex() const;
	};
	
	/**
	 * @brief	Representation of streamlines associated with a streamline feature and interpretation.
	 *			Use the StreamlinesFeature to specify the vector field that supports the streamlines, i.e., describes what flux is being traced.
	 *			Use the Generic Feature  Interpretation to distinguish between shared and differing interpretations.
	 */
#ifdef SWIGPYTHON
	%rename(Resqml2_StreamlinesRepresentation) StreamlinesRepresentation;
#endif	
	class StreamlinesRepresentation : public AbstractRepresentation
	{
	public:
		/**
		 * Gets the count of line contained in this streamlines representation.
		 *
		 * @exception	std::logic_error	If this feature is partial.
		 *
		 * @returns	The count of line contained in this streamlines representation.
		*/
		uint64_t getLineCount() const;

		/**
		 * Gets the count of wellbore trajectories of this streamlines representation.
		 *
		 * @exception	std::range_error	If the count of wellbore trajectories is strictly
		 * 									greater than unsigned int max.
		 *
		 * @returns	The count of wellbore trajectories.
		 */
		uint64_t getWellboreTrajectoryCount() const;

		/**
		 * Gets the wellbore trajectory located at a specific index of this streamlines
		 * representation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt>
		 * 									getWellboreTrajectoryCount().
		 *
		 * @param 	index	Zero-based index of the wellbore trajectory we look for.
		 *
		 * @returns	The wellbore trajectory at position @p index.
		 */
		RESQML2_NS::WellboreTrajectoryRepresentation* getWellboreTrajectory(uint64_t index);

		/**
		 * @brief	Gets all the wellbore indices which are injectors.
		 *			Null values signify that that line does not initiate at an injector, e.g., it may come from fluid expansion or an aquifer.
		 *
		 * @param [in/out]	injectorPerLine 	The 0-based injector wellbore index defined by the order of the wellbore in the list of WellboreTrajectoryRepresentation references.
		 *									It must be preallocated with a size getWellboreTrajectories().size() and it won't be freed by FESAPI.
		 *
		 * @returns	The null value used in injectorPerLine.
		 */
		uint32_t getInjectorPerLine(uint32_t* injectorPerLine) const;

		/**
		 * @brief	Gets all the wellbore indices which are producers.
		 *			Null values signify that that line does not terminate at a producer, e.g., it may approach a stagnation area.
		 *
		 * @param [in/out]	injectorPerLine 	The 0-based injector wellbore index defined by the order of the wellbore in the list of WellboreTrajectoryRepresentation references.
		 *									It must be preallocated with a size getWellboreTrajectories().size() and it won't be freed by FESAPI.
		 *
		 * @returns	The null value used in producerPerLine.
		 */
		uint32_t getProducerPerLine(uint32_t* producerPerLine) const;

		/**
		 * Gets the node count per line.
		 *
		 * @param [out]	nodeCountPerPolyline	A preallocated array to receive the node count per
		 * 										line. Its size must be
		 * 										<tt>getLineCount(patchIndex)</tt>.
		 */
		void getNodeCountPerLine(uint32_t * nodeCountPerPolyline) const;

		/**
		 * Gets the interval count per line.
		 *
		 * @param [out]	intervalCountPerPolyline	A preallocated array to receive the interval count per
		 * 											line. Its size must be
		 * 											<tt>getLineCount(patchIndex)</tt>.
		 */
		void getIntervalCountPerLine(uint32_t * intervalCountPerPolyline) const;

		/**
		 * Gets the total interval count in this streamlines representation.
		 *
		 * @param [out]	nodeCountPerPolyline	A preallocated array to receive the node count per
		 * 										line. Its size must be
		 * 										<tt>getLineCount(patchIndex)</tt>.
		 */
		uint64_t getIntervalCount() const;

		/**
		 * Sets the geometry of the streamlines representation.
		 *
		 * @exception	std::invalid_argument	If <tt>proxy == nullptr</tt> and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If <tt>localCrs == nullptr</tt> and no default local CRS
		 * 										id defined in the repository.
		 *
		 * @param [in]	  	nodeCountPerPolyline  	The node count per polyline in this representation. It is
		 * 											ordered by polyline. There must be getLineCount()
		 * 											values in this array.
		 * @param [in]	  	xyzPoints			  	The xyz values of the nodes. Ordered by xyz, then by
		 * 											node and then by polyline. It must be three times the
		 * 											total count of nodes.
		 *											If the streamlines are associated to grids then the there must be one point
		 *											one each face intersected by the a line + the start and end point.
		 * @param [in,out]	hdfProxy			  	(Optional) The HDF proxy which defines where the
		 * 											nodes will be stored. If @c nullptr (default), then
		 * 											the repository default HDF proxy will be used.
		 * @param [in]	  	localCrs			  	(Optional) The local CRS where the points are
		 * 											defined. If @c nullptr (default value), then the
		 * 											repository default local CRS will be used.
		 */
		void setGeometry(
			uint32_t const * nodeCountPerPolyline, double const * xyzPoints,
			EML2_NS::AbstractHdfProxy* hdfProxy = nullptr, EML2_NS::AbstractLocal3dCrs* localCrs = nullptr);

		/**
		 * For each interval of the lines of the representation, gets the index of the grid it is associated to.
		 *
		 * @exception	std::range_error	If the grid indices are stored in an integer constant array
		 * 									and if the the constant value is strictly superior than uint16_t maximum value.
		 * @exception	std::logic_error	If the grid indices are neither stored in a HDF5 integer
		 * 									array nor in an integer constant array.
		 *
		 * @param [out]	gridIndices	An array for receiving the grids indices. The size of this array is
		 * 							getIntervalCount.
		 *
		 * @returns	The null value used in @p gridIndices in order to indicate that an interval does not
		 * 			correspond to any intersected grid.
		 */
		uint16_t getGridIndices(uint16_t * gridIndices) const;

		/**
		 * For each interval of the lines of the representation, gets the index of the cell it is associated to.
		 * Cell index in in the scope of the associated grid at the same index.
		 *
		 * @exception	std::range_error	If the cell indices are stored in an integer constant array
		 * 									and if the the constant value is strictly superior than uint64_t maximum value.
		 * @exception	std::logic_error	If the * indices are neither stored in a HDF5 integer
		 * 									array nor in an integer constant array.
		 *
		 * @param [out]	cellIndices	An array for receiving the cell indices. The size of this array is
		 * 							getIntervalCount.
		 *
		 * @returns	The null value used in @p cellIndices in order to indicate that an interval does not
		 * 			correspond to any intersected grid.
		 */
		int64_t getCellIndices(int64_t * cellIndices) const;

		/**
		 * For each interval of the lines of the representation, gets the entry and exit intersection faces of the line in the cell.
		 *
		 * @exception	std::range_error	If the grid indices are stored in an integer constant array
		 * 									and if the the constant value is strictly superior than uint8_t maximum value.
		 * @exception	std::logic_error	If the grid indices are neither stored in a HDF5 integer
		 * 									array nor in an integer constant array.
		 *
		 * @param [out]	gridIndices	An array for receiving the local Face Pair Per Cell Indices. The size of this array is twice
		 * 							getIntervalCount.
		 *
		 * @returns	The null value used in @p localFacePairPerCellIndices in order to indicate that a line interval does not intersect a face in this cell.
		 */
		uint8_t getLocalFacePairPerCellIndices(uint8_t * localFacePairPerCellIndices) const;

		/**
		 * Gets the count of grid representations of this streamlines representation.
		 *
		 * @exception	std::range_error	If the count of grid representations is strictly
		 * 									greater than unsigned int max.
		 *
		 * @returns	The count of grid representation.
		 */
		uint64_t getGridRepresentationCount() const;

		/**
		 * Gets the grid representation located at a specific index of this streamlines
		 * representation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt>
		 * 									getGridRepresentationCount().
		 *
		 * @param 	index	Zero-based index of the grid representation we look for.
		 *
		 * @returns	The grid representation at position @p index.
		 */
		RESQML2_NS::AbstractGridRepresentation* getGridRepresentation(uint64_t index) const;
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_AbstractProperty) AbstractProperty;
#endif
	class AbstractProperty: public COMMON_NS::AbstractObject
	{
	public:
		AbstractRepresentation* getRepresentation();
		void setRepresentation(AbstractRepresentation * rep);
		
		/**
		 * Get the values data type in the HDF dataset
		 *
		 * @returns	The data type of the values if successful, else @c UNKNOWN.
		 */
		COMMON_NS::AbstractObject::numericalDatatypeEnum getValuesHdfDatatype() const;
		
		/**
		 * Get the number of values in each dimension into the underlying HDF5 dataset.
		 * uint32_t is returned instead of uint64_t cause of some SWIG usage. I cannot SWIG port std::vector<uint64_t>
		 * @param 	patchIndex	The index of the patch we want to count the values from.
		 */
		std::vector<uint32_t> getValuesCountPerDimensionOfPatch(uint64_t patchIndex) const;

		/**
		 * Gets the count of all values contained into the underlying HDF5 dataset of a given patch of
		 * this property.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	patchIndex	The index of the patch we want to count the values from.
		 *
		 * @returns	The count of values of the @p patchIndex patch.
		 */
		uint64_t getValuesCountOfPatch(uint64_t patchIndex) const;

		/**
		 * Gets the count of values on a specific dimension of the underlying HDF5 dataset of a given
		 * patch of this property.
		 *
		 * @exception	std::out_of_range	If @p dimIndex is strictly greater than dimension count.
		 * @exception	std::range_error 	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	dimIndex  	The index of the dimension we want to count the values from.
		 * @param 	patchIndex	The index of the patch we want to count the values from.
		 *
		 * @returns	The count of values in the @p dimIndex dimension of @p patchIndex patch.
		 */
		uint64_t getValuesCountOfDimensionOfPatch(uint64_t dimIndex, uint64_t patchIndex) const;

		/**
		 * Gets the count of dimensions of the underlying HDF5 dataset of a given patch of this property.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	patchIndex	The index of the patch we want to count the dimensions from.
		 *
		 * @returns	The number of values, 0 otherwise.
		 */
		uint64_t getDimensionsCountOfPatch(uint64_t patchIndex) const;
		
		std::string getPropertyKindDescription() const;
		std::string getPropertyKindAsString() const;
		std::string getPropertyKindParentAsString() const;
		bool isAssociatedToOneStandardEnergisticsPropertyKind() const;
		
		EML2_NS::PropertyKind* getPropertyKind() const;
		
		/**
		 * Gets the count of elements per property value. If the property is a scalar one then it should
		 * be one. If it is a vectorial one, then it should be more than one. It is not possible to have
		 * some tensor property values (more dimensions than a vector)
		 *
		 * @returns	The element count per value.
		 */
		uint64_t getElementCountPerValue() const;
		
		/**
		 * Gets the kind of elements on which the property values are attached to
		 *
		 * @returns	The kind of elements on which the property values are attached to.
		 */
		gsoap_eml2_3::eml23__IndexableElement getAttachmentKind() const;
		
		/**
		 * Gets the count of property sets which contain this property
		 *
		 * @exception	std::range_error	If the count of property sets is strictly greater than
		 * 									unsigned int max.
		 *
		 * @returns	The count of property sets which contain this property.
		 */
		uint64_t getPropertySetCount() const;

		/**
		 * Gets a given property set taken from all property sets which contain this property
		 *
		 * @exception	std::out_of_range	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the property set we look for.
		 *
		 * @returns	The property set at @p index.
		 */
		RESQML2_0_1_NS::PropertySet * getPropertySet(uint64_t index) const;
		
		bool hasRealizationIndices() const;
		std::vector<unsigned int> getRealizationIndices() const;
		void setRealizationIndices(int64_t startRealizationIndex, int64_t countRealizationIndices);
		void setRealizationIndices(const std::vector<unsigned int> & realizationIndices, EML2_NS::AbstractHdfProxy* hdfProxy = nullptr);
		
		/*
		 * Sets the time series associated to the current property
		 *
		 * @exception	invalid_argument	If @p ts is null or if the current property has no time
		 * 									indices.
		 *
		 * @param [in]	ts	The time series to associate to this property
		 */
		void setTimeSeries(EML2_NS::TimeSeries * ts);

		/**
		 * Set a single associated timestamp for this property.
		 * RESQML2.0.1	: Must be used with and after setTimeSeries.
		 * RESQML2.2	: If, used the property must contain values for a single timestamp (as in 2.0.1). It cannot be used with setTimeSeries.
		 *
		 * @exception	invalid_argument	Regarding RESQML2.0.1, this method cannot be called if setTimeSeries has not been called before.
		 *
		 * @param [in]	timestamp	The single timestamps to associate to this property
		 * @param [in]	yearOffset	Indicates that the dateTime attribute must be translated according to this value.
		 */
		void setSingleTimestamp(time_t timestamp, LONG64 yearOffset = 0);

		/**
		 * Get a single associated timestamp for this property.
		 *
		 * @return	-1 if there is not a single timestamp related to this property meaning that no timestamp is present or more than one (i.e. a whole time series)
		 */
		time_t getSingleTimestamp() const;

		/**
		 * Gets the time series which is associated to this property
		 *
		 * @returns	Null pointer if no time series is associated to this property. Otherwise returns the
		 * 			associated time series.
		 */
		EML2_NS::TimeSeries* getTimeSeries() const;

		/**
		 * Check if the values are given at each time index or between each time index.
		 */
		bool useInterval() const;
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_AbstractValuesProperty) AbstractValuesProperty;
#endif
	class AbstractValuesProperty : public RESQML2_NS::AbstractProperty
	{
	public:
		void pushBackFacet(gsoap_eml2_3::eml23__FacetKind facet, const std::string & facetValue);
		unsigned int getFacetCount() const const;
		gsoap_eml2_3::eml23__FacetKind getFacetKind(unsigned int index) const;
		std::string getFacetValue(unsigned int index) const;
		
		//****************************/
		//****** INTEGER *************/
		//****************************/

		/**
		 * @brief	Adds a 1d array of explicit int 64 bits values to the property values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values	  	All the property values to set ordered according to the topology
		 * 								of the representation it is based on.
		 * @param 		  	valueCount	The number of values to write.
		 * @param [in,out]	proxy	  	The HDF proxy where to write the property values. It must be
		 * 								already opened for writing and won't be closed in this method. If
		 * 								@c nullptr, then a default HDF proxy must be defined in the
		 * 								repository.
		 * @param 		  	nullValue 	The null value.
		 */
		void pushBackInt64Hdf5Array1dOfValues(const int64_t * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue);

		/**
		 * Adds a 1d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array1dOfValues
		 */
		void pushBackInt32Hdf5Array1dOfValues(const int * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, int nullValue);

		/**
		 * Adds a 1d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array1dOfValues
		 */
		void pushBackInt16Hdf5Array1dOfValues(const short * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, short nullValue);

		/**
		 * Adds a 1d array of explicit char values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array1dOfValues
		 */
		void pushBackInt8Hdf5Array1dOfValues(const int8_t * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue);

		/**
		 * @brief Adds a 2d array of explicit int 64 bits values to the property values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values				  	All the property values to set ordered according to
		 * 											the topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly J dimension).
		 * @param [in,out]	proxy				  	The HDF proxy where to write the property values. It
		 * 											must be already opened for writing and won't be
		 * 											closed in this method. If @c nullptr, then a default
		 * 											HDF proxy must be defined in the repository.
		 * @param 		  	nullValue			  	The null value.
		 */
		void pushBackInt64Hdf5Array2dOfValues(const int64_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue);

		/**
		 * Adds a 2d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array2dOfValues
		 */
		void pushBackInt32Hdf5Array2dOfValues(const int * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int nullValue);

		/**
		 * Adds a 2d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array2dOfValues
		 */
		void pushBackInt16Hdf5Array2dOfValues(const short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, short nullValue);

		/**
		 * Adds a 2d array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array2dOfValues
		 */
		void pushBackUInt16Hdf5Array2dOfValues(const unsigned short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue);

		/**
		 * Adds a 2d array of explicit char values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array2dOfValues
		 */
		void pushBackInt8Hdf5Array2dOfValues(const int8_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue);

		/**
		 * @brief Adds a 3d array of explicit int 64 bits values to the property values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values				  	All the property values to set ordered according the
		 * 											topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values to write in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param [in,out]	proxy				  	The HDF proxy where to write the property values. It
		 * 											must be already opened for writing and won't be
		 * 											closed in this method. If @c nullptr, then a default
		 * 											HDF proxy must be defined in the repository.
		 * @param 		  	nullValue			  	The null value.
		 */
		void pushBackInt64Hdf5Array3dOfValues(const int64_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue);

		/**
		 * Adds a 3d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array3dOfValues
		 */
		void pushBackInt32Hdf5Array3dOfValues(const int * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int nullValue);

		/**
		 * Adds a 3d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array3dOfValues
		 */
		void pushBackInt16Hdf5Array3dOfValues(const short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, short nullValue);

		/**
		 * Adds a 3d array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array3dOfValues
		 */
		void pushBackUInt16Hdf5Array3dOfValues(const unsigned short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue);

		/**
		 * Adds a 3d array of explicit char values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array3dOfValues
		 */
		void pushBackInt8Hdf5Array3dOfValues(const int8_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue);

		/**
		 * @brief	Adds an nd array of explicit int 64 bits values to the property values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values					All the property values to set ordered according the
		 * 											topology of the representation it is based on.
		 * @param [in]	  	numValues				The number of property values ordered by dimension of
		 * 											the array to write.
		 * @param 		  	numDimensionsInArray	The number of dimensions in the array to write.
		 * @param [in,out]	proxy					The HDF proxy where to write the property values. It
		 * 											must be already opened for writing and won't be closed in
		 * 											this method. If @c nullptr, then a default HDF proxy must
		 * 											be defined in the repository.
		 * @param 		  	nullValue				The null value.
		 */
		virtual void pushBackInt64Hdf5ArrayOfValues(const int64_t * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue);

		/**
		 * Adds an nd array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues
		 */
		virtual void pushBackInt32Hdf5ArrayOfValues(const int * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int nullValue);

		/**
		 * Adds an nd array of explicit short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues
		 */
		virtual void pushBackInt16Hdf5ArrayOfValues(const short * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, short nullValue);

		/**
		 * Adds an nd array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues
		 */
		virtual void pushBackUInt16Hdf5ArrayOfValues(const unsigned short * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue);

		/**
		 * Adds an nd array of explicit int8_t values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues
		 */
		virtual void pushBackInt8Hdf5ArrayOfValues(const int8_t * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue);

		/**
		 * Pushes back a new patch of values for this property where the values have not to be written
		 * in the HDF5 file.The reason can be that the values already exist in an external file (only
		 * HDF5 for now) or that the writing of the values in the external file is differed in time.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p hdfProxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param [in]	hdfProxy 	The HDF5 proxy where the values are already or will be stored. If @c
		 * 							nullptr, then a default HDF proxy must be defined in the repository.
		 * @param 	  	dataset  	(Optional) If not provided during the method call, the dataset will
		 * 							be named the same as the dataset naming convention of fesapi :
		 * 							<tt>getHdfGroup() + "/values_patch" + patchIndex</tt>
		 * @param 	  	nullValue	(Optional) Only relevant for integer HDF5 datasets. Indeed, RESQML
		 * 							(and fesapi) forces null value for floating point to be @c NaN value.
		 *
		 * @returns	The name of the HDF5 dataset.
		 */
		std::string pushBackRefToExistingIntegerDataset(EML2_NS::AbstractHdfProxy* hdfProxy, const std::string & dataset = "", int64_t nullValue = std::numeric_limits<int64_t>::max());

		/**
		 * Check if this property has all its values set to a constant ones.
		 * This method does not check if all given values are the same constant ones.
		 * It only checks if the property has been written using the optimized constant array.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want to check the values from.
		 *
		 * @returns	True if the property has been written using the optimized constant array.
		 */
		bool hasConstantValues(uint64_t patchIndex) const;

		/**
		 * Get the constant value of all values of this property as an integer one.
		 * This method does not check if all given values are the same constant ones.
		 * It only checks if the property has been written using the optimized constant array.
		 *
		 * @exception	std::logic_error 		If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range		If @p patchIndex is strictly greater than patch count.
		 * @exception	std::invalid_argument	If the property does not have any integer constant value.
		 *
		 * @param 	   	patchIndex	The index of the patch we want to get the constant value from.
		 *
		 * @returns	The constant value of all values of this property as an integer one.
		 */
		int64_t getInt64ConstantValuesOfPatch(uint64_t patchIndex) const;

		/**
		 * Get the constant value of all values of this property as a double one.
		 * This method does not check if all given values are the same constant ones.
		 * It only checks if the property has been written using the optimized constant array.
		 *
		 * @exception	std::logic_error 		If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range		If @p patchIndex is strictly greater than patch count.
		 * @exception	std::invalid_argument	If the property does not have any double constant value.
		 *
		 * @param 	   	patchIndex	The index of the patch we want to get the constant value from.
		 *
		 * @returns	The constant value of all values of this property as a double one.
		 */
		double getDoubleConstantValuesOfPatch(uint64_t patchIndex) const;

		/**
		 * Gets the null value of a given patch of this instance. Values are supposed to be integer ones.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::range_error	 	If @p patchIndex is strictly greater than patch count.
		 * @exception	std::invalid_argument	If the @p patchIndex patch does not contain integer
		 * 										values.
		 *
		 * @param 	patchIndex	The index of the patch we want the values from.
		 *
		 * @returns	the null value.
		 */
		int64_t getNullValueOfPatch(uint64_t patchIndex) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be signed 64 bits integer.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values. Size is
		 * 							<tt>getValuesCountOfPatch(patchIndex)</tt>.
		 *
		 * @returns	The null value.
		 */
		int64_t getInt64ValuesOfPatch(uint64_t patchIndex, int64_t * values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be unsigned 64 bits integer.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values. Size is
		 * 							<tt>getValuesCountOfPatch(patchIndex)</tt>.
		 *
		 * @returns	The null value.
		 */
		uint64_t getUInt64ValuesOfPatch(uint64_t patchIndex, uint64_t* values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be signed 32 bits integer.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values. Size is
		 * 							<tt>getValuesCountOfPatch(patchIndex)</tt>
		 *
		 * @returns	The null value.
		 */
		int32_t getInt32ValuesOfPatch(uint64_t patchIndex, int32_t * values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be unsigned 32 bits integer.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values. Size is
		 * 							<tt>getValuesCountOfPatch(patchIndex)</tt>
		 *
		 * @returns	The null value.
		 */
		uint32_t getUInt32ValuesOfPatch(uint64_t patchIndex, uint32_t * values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be signed 16 bits integer.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values. Size is
		 * 							<tt>getValuesCountOfPatch(patchIndex)</tt>
		 *
		 * @returns	The null value.
		 */
		int16_t getInt16ValuesOfPatch(uint64_t patchIndex, int16_t * values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be unsigned 16 bits integer.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values. Size is
		 * 							<tt>getValuesCountOfPatch(patchIndex)</tt>
		 *
		 * @returns	The null value.
		 */
		uint16_t getUInt16ValuesOfPatch(uint64_t patchIndex, uint16_t * values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be signed 8 bits integer.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values. Size is
		 * 							<tt>getValuesCountOfPatch(patchIndex)</tt>
		 *
		 * @returns	The null value.
		 */
		int8_t getInt8ValuesOfPatch(uint64_t patchIndex, int8_t* values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be unsigned 8 bits integer.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values. Size is
		 * 							<tt>getValuesCountOfPatch(patchIndex)</tt>
		 *
		 * @returns	The null value.
		 */
		uint8_t getUInt8ValuesOfPatch(uint64_t patchIndex, uint8_t* values) const;

		//***********************************
		//*** Writing with hyperslabbing *****
		//***********************************
		
		/**
		 * Create an nd array of values to the property values. No values are written to
		 * this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 			datatype			The datatype of the values 
		 * @param 		  	numValues		  	The number of property values ordered by dimension of the
		 * 										array to write.  It is ordered from slowest dimension to
		 * 										fastest dimension.
		 * @param 		  	numArrayDimensions	The number of dimensions of the array to write.
		 * @param 			nullvalue			The integer null value in case we create an integer array.
		 * 										It is ignored if the @p datatype is a floating point one.
		 * @param [in,out]	proxy			  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If @c nullptr (default), a
		 * 										default HDF proxy must be defined into the data object
		 * 										repository.
		 */
		void pushBackHdf5ArrayOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			uint64_t const * numValues,
			unsigned int numArrayDimensions,
			int64_t nullValue = std::numeric_limits<int64_t>::max(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Creates a 1d array of explicit double values to the property values. No values are written to
		 * this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 		  	valueCount			The number of values to write).
		 * @param 			nullvalue			The integer null value in case we create an integer array.
		 * 										It is ignored if the @p datatype is a floating point one.
		 * @param [in,out]	proxy				(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and
		 * 										won't be closed in this method. If @c nullptr
		 * 										(default), a default HDF proxy must be defined into
		 * 										the data object repository.
		 */
		void pushBackHdf5Array1dOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			uint64_t valueCount,
			int64_t nullValue = std::numeric_limits<int64_t>::max(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Creates a 2d array of explicit double values to the property values. No values are written to
		 * this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param 			nullvalue			The integer null value in case we create an integer array.
		 * 										It is ignored if the @p datatype is a floating point one.
		 * @param [in,out]	proxy					(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default), a default HDF proxy must be defined into
		 * 											the data object repository.
		 */
		void pushBackHdf5Array2dOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			int64_t nullValue = std::numeric_limits<int64_t>::max(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Creates a 3d array of explicit float values to the property values. No values are written to
		 * this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 			datatype				The datatype of the values 
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values to write in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param 			nullvalue			The integer null value in case we create an integer array.
		 * 										It is ignored if the @p datatype is a floating point one.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default), a default HDF proxy must be defined into
		 * 											the data object repository.
		 */
		void pushBackHdf5Array3dOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			int64_t nullValue = std::numeric_limits<int64_t>::max(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr);
		
		/**
		 * Adds an nd array of explicit int 64 bits values into to the property values. Since this
		 * methods only pushes back values into an existing array, it is to be used along with
		 * pushBackInt64Hdf5ArrayOfValues().
		 *
		 * @exception	std::invalid_argument	If @p proxy is null and no default HDF proxy is defined
		 * 										into the data object repository.
		 * @exception	std::out_of_range	 	If @p patchIndex is strictly greater than patch count and
		 * 										different from unsigned int maximum value.
		 *
		 * @param [in]	  	values			  	All the property values to set ordered according to the
		 * 										topology of the representation it is based on.
		 * @param 		  	numValues		  	The number of property values ordered by dimension of the
		 * 										array to write. It is ordered from slowest dimension to
		 * 										fastest dimension.
		 * @param 		  	offsetValues	  	The offset values ordered by dimension of the array to
		 * 										write. It is ordered from slowest dimension to fastest
		 * 										dimension.
		 * @param 		  	numArrayDimensions	The number of dimensions of the array to write.
		 * @param [in,out]	proxy			  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If null (default value), a
		 * 										default HDF proxy must be defined into the data object
		 * 										repository.
		 * @param 		  	patchIndex		  	(Optional) Zero-based index of the patch where to write
		 * 										the property values. If not provided, its default value
		 * 										is by convention set to unsigned int maximum value and
		 * 										the property values will be written in the last property
		 * 										values patch (the one with the greatest index).
		 */
		void setValuesOfInt64Hdf5ArrayOfValues(
			int64_t const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfUInt64Hdf5ArrayOfValues(
			uint64_t const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfInt32Hdf5ArrayOfValues(
			int32_t const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfUInt32Hdf5ArrayOfValues(
			uint32_t const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfInt16Hdf5ArrayOfValues(
			int16_t const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfUInt16Hdf5ArrayOfValues(
			uint16_t const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfInt8Hdf5ArrayOfValues(
			int8_t const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfUInt8Hdf5ArrayOfValues(
			uint8_t const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfDoubleHdf5ArrayOfValues(
			double const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfFloatHdf5ArrayOfValues(
			float const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());

		/**
		 * Adds a 1d array of explicit int 64 bits values into the property values. Since this methods
		 * only pushes back values into an existing array, it is to be used along with
		 * pushBackInt64Hdf5Array3dOfValues().
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 * @exception	std::out_of_range	 	If @p patchIndex is strictly greater than patch count and
		 * 										different from unsigned int maximum value.
		 *
		 * @param [in]	  	values				  	All the property values to set ordered according to
		 * 											the topology of the representation it is based on.
		 * @param 		  	valueCount				The number of values to write.
		 * @param 		  	offset	  				The offset value.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @p nullptr
		 * 											(default value), a default HDF proxy must be defined
		 * 											into the data object repository.
		 * @param 		  	patchIndex			  	(Optional) Zero-based index of the patch where to
		 * 											write the property values. If not provided, its
		 * 											default value is by convention set to unsigned int
		 * 											maximum value and the property values will be written
		 * 											in the last property values patch (the one with the
		 * 											greatest index).
		 */
		void setValuesOfInt64Hdf5Array1dOfValues(
			int64_t const* values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfUInt64Hdf5Array1dOfValues(
			uint64_t const* values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfInt32Hdf5Array1dOfValues(
			int32_t const* values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfUInt32Hdf5Array1dOfValues(
			uint32_t const* values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfInt16Hdf5Array1dOfValues(
			int16_t const* values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfUInt16Hdf5Array1dOfValues(
			uint16_t const* values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfInt8Hdf5Array1dOfValues(
			int8_t const* values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfUInt8Hdf5Array1dOfValues(
			uint8_t const* values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfDoubleHdf5Array1dOfValues(
			double const * values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfFloatHdf5Array1dOfValues(
			float const * values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());

		/**
		 * Adds a 2d array of explicit values into the property values. Since this methods
		 * only pushes back values into an existing array, it is to be used along with
		 * pushBackInt64Hdf5Array2dOfValues().
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 * @exception	std::out_of_range	 	If @p patchIndex is strictly greater than patch count and
		 * 										different from unsigned int maximum value.
		 *
		 * @param [in]	  	values				  	All the property values to set ordered according to
		 * 											the topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly J dimension).
		 * @param 		  	offsetInFastestDim	  	The offset value for writing in the fastest dimension
		 * 											(mainly I dimension).
		 * @param 		  	offsetInSlowestDim	  	The offset value for writing in the slowest dimension
		 * 											(mainly J dimension).		 
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @p nullptr
		 * 											(default value), a default HDF proxy must be defined
		 * 											into the data object repository.
		 * @param 		  	patchIndex			  	(Optional) Zero-based index of the patch where to
		 * 											write the property values. If not provided, its
		 * 											default value is by convention set to unsigned int
		 * 											maximum value and the property values will be written
		 * 											in the last property values patch (the one with the
		 * 											greatest index).
		 */
		void setValuesOfInt64Hdf5Array2dOfValues(
			int64_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfUInt64Hdf5Array2dOfValues(
			uint64_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfInt32Hdf5Array2dOfValues(
			int32_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfUInt32Hdf5Array2dOfValues(
			uint32_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfInt16Hdf5Array2dOfValues(
			int16_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfUInt16Hdf5Array2dOfValues(
			uint16_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfInt8Hdf5Array2dOfValues(
			int8_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfUInt8Hdf5Array2dOfValues(
			uint8_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfDoubleHdf5Array2dOfValues(
			double const * values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfFloatHdf5Array2dOfValues(
			float const * values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());

		/**
		 * Adds a 3d array of explicit int 64 bits values into the property values. Since this methods
		 * only pushes back values into an existing array, it is to be used along with
		 * pushBackInt64Hdf5Array3dOfValues().
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 * @exception	std::out_of_range	 	If @p patchIndex is strictly greater than patch count and
		 * 										different from unsigned int maximum value.
		 *
		 * @param [in]	  	values				  	All the property values to set ordered according to
		 * 											the topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values to write in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param 		  	offsetInFastestDim	  	The offset value for writing in the fastest dimension
		 * 											(mainly I dimension).
		 * @param 		  	offsetInMiddleDim	  	The offset value for writing in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	offsetInSlowestDim	  	The offset value for writing in the slowest dimension
		 * 											(mainly K dimension).
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @p nullptr
		 * 											(default value), a default HDF proxy must be defined
		 * 											into the data object repository.
		 * @param 		  	patchIndex			  	(Optional) Zero-based index of the patch where to
		 * 											write the property values. If not provided, its
		 * 											default value is by convention set to unsigned int
		 * 											maximum value and the property values will be written
		 * 											in the last property values patch (the one with the
		 * 											greatest index).
		 */
		void setValuesOfInt64Hdf5Array3dOfValues(
			int64_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfUInt64Hdf5Array3dOfValues(
			uint64_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfInt32Hdf5Array3dOfValues(
			int32_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfUInt32Hdf5Array3dOfValues(
			uint32_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfInt16Hdf5Array3dOfValues(
			int16_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfUInt16Hdf5Array3dOfValues(
			uint16_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfInt8Hdf5Array3dOfValues(
			int8_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfUInt8Hdf5Array3dOfValues(
			uint8_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfDoubleHdf5Array3dOfValues(
			double const * values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfFloatHdf5Array3dOfValues(
			float const * values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());

		//***********************************/
		//*** INTEGER For hyperslabbing *****/
		//***********************************/

		/**
		 * Gets some of the values of a given patch of this instance. Values are supposed to be int 64
		 * bits ones.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex					The index of the patch we want the values from.
		 * @param [out]	values						The array (pointer) of values which must be
		 * 											preallocated. Size is
		 * 											<tt>getValuesCountOfPatch(patchIndex)</tt>.
		 * @param 	   	numValuesInEachDimension	The number of property values ordered by dimension of
		 * 											the array to read. It is ordered from slowest dimension
		 * 											to fastest dimension.
		 * @param 	   	offsetInEachDimension   	The offset values ordered by dimension of the array
		 * 											to read. It is ordered from slowest dimension to fastest
		 * 											dimension.
		 * @param 	   	numArrayDimensions			The number of dimensions of the array to write.
		 */
		void getInt64ValuesOfPatch(
			unsigned int patchIndex,
			int64_t* values,
			uint64_t const * numValuesInEachDimension,
			uint64_t const * offsetInEachDimension,
			unsigned int numArrayDimensions
		) const;

		/**
		 * Gets some of the values of a given patch of this instance. Values are supposed to be int 64
		 * bits ones.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex			  	The index of the patch we want the values from.
		 * @param [out]	values				  	The array (pointer) of values must be preallocated. Size
		 * 										is <tt>getValuesCountOfPatch(patchIndex)</tt>.
		 * @param 	   	valueCountInFastestDim	The number of values to read in the fastest dimension
		 * 										(mainly I dimension).
		 * @param 	   	valueCountInMiddleDim 	The number of values to read in the middle dimension
		 * 										(mainly J dimension).
		 * @param 	   	valueCountInSlowestDim	The number of values to read in the slowest dimension
		 * 										(mainly K dimension).
		 * @param 	   	offsetInFastestDim	  	The offset value for reading in the fastest dimension
		 * 										(mainly I dimension).
		 * @param 	   	offsetInMiddleDim	  	The offset value for reading in the middle dimension
		 * 										(mainly J dimension).
		 * @param 	   	offsetInSlowestDim	  	The offset value for reading in the slowest dimension
		 * 										(mainly K dimension).
		 */
		void getInt64ValuesOf3dPatch(
			unsigned int patchIndex,
			int64_t* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim
		) const;

		/**
		 * Gets some of the values of a given patch of this instance. Values are supposed to be integer
		 * ones.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex					The index of the patch we want the values from.
		 * @param [out]	values						The array (pointer) of values which must be
		 * 											preallocated. Size is
		 * 											<tt>getValuesCountOfPatch(patchIndex)</tt>.
		 * @param [in] 	numValuesInEachDimension	The number of property values ordered by
		 * 											dimension of the array to read. It is ordered from
		 * 											slowest dimension to fastest dimension.
		 * @param [in] 	offsetInEachDimension   	The offset values ordered by dimension of the
		 * 											array to read. It is ordered from slowest dimension to
		 * 											fastest dimension.
		 * @param 	   	numArrayDimensions			The number of dimensions of the array to read.
		 *
		 * @returns	The null value.
		 */
		int getIntValuesOfPatch(
			unsigned int patchIndex,
			int* values,
			const uint64_t* numValuesInEachDimension,
			const uint64_t* offsetInEachDimension,
			unsigned int numArrayDimensions
		) const;

		/**
		 * Gets some of the values of a given patch of this instance. Values are supposed to be integer
		 * ones.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex			  	The index of the patch we want the values from.
		 * @param [out]	values				  	The array (pointer) of values must be preallocated. Size
		 * 										is <tt>getValuesCountOfPatch(patchIndex)</tt>.
		 * @param 	   	valueCountInFastestDim	The number of values to read in the fastest dimension
		 * 										(mainly I dimension).
		 * @param 	   	valueCountInMiddleDim 	The number of values to read in the middle dimension
		 * 										(mainly J dimension).
		 * @param 	   	valueCountInSlowestDim	The number of values to read in the slowest dimension
		 * 										(mainly K dimension).
		 * @param 	   	offsetInFastestDim	  	The offset value for reading in the fastest dimension
		 * 										(mainly I dimension).
		 * @param 	   	offsetInMiddleDim	  	The offset value for reading in the middle dimension
		 * 										(mainly J dimension).
		 * @param 	   	offsetInSlowestDim	  	The offset value for reading in the slowest dimension
		 * 										(mainly K dimension).
		 */
		void getIntValuesOf3dPatch(
			unsigned int patchIndex,
			int* values,
			unsigned int valueCountInFastestDim,
			unsigned int valueCountInMiddleDim,
			unsigned int valueCountInSlowestDim,
			unsigned int offsetInFastestDim,
			unsigned int offsetInMiddleDim,
			unsigned int offsetInSlowestDim
		) const;

		//***********************************/
		//****** FLOATING POINT *************/
		//***********************************/

		/**
		 * @brief Adds a 1d array of explicit double values to the property values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values			All the property values to set ordered according the topology
		 * 									of the representation it is based on.
		 * @param 		  	valueCount  	The number of values to write.
		 * @param [in,out]	proxy			(Optional) The HDF proxy where to write the property values.
		 * 									It must be already opened for writing and won't be closed in this
		 * 									method. If @c nullptr (default value), then a default HDF proxy
		 * 									must be defined in the repository.
		 */
		void pushBackDoubleHdf5Array1dOfValues(const double * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief Adds a 2d array of explicit double values to the property values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values				  	All the property values to set ordered according the
		 * 											topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly J dimension).
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default value), then a default HDF proxy must be
		 * 											defined in the repository.
		 */
		void pushBackDoubleHdf5Array2dOfValues(const double * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief Adds a 3d array of explicit double values to the property values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values				  	All the property values to set ordered according the
		 * 											topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values to write in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default value), then a default HDF proxy must be
		 * 											defined in the repository.
		 */
		void pushBackDoubleHdf5Array3dOfValues(const double * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief Adds an nd array of explicit double values to the property values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values			  	All the property values to set ordered according the
		 * 										topology of the representation it is based on.
		 * @param 		  	numValues		  	The number of property values ordered by dimension of the
		 * 										array to write.
		 * @param 		  	numArrayDimensions	The number of dimensions of the array to write.
		 * @param [in,out]	proxy			  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If @c nullptr (default value),
		 * 										then a default HDF proxy must be defined in the
		 * 										repository.
		 */
		void pushBackDoubleHdf5ArrayOfValues(double const * values, uint64_t const * numValues, unsigned int numArrayDimensions, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds a 1d array of explicit float values to the property values.
		 *
		 * @copydetails pushBackDoubleHdf5Array1dOfValues
		 */
		void pushBackFloatHdf5Array1dOfValues(const float * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds a 2d array of explicit float values to the property values.
		 *
		 * @copydetails pushBackDoubleHdf5Array2dOfValues
		 */
		void pushBackFloatHdf5Array2dOfValues(const float * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds a 3d array of explicit float values to the property values.
		 *
		 * @copydetails pushBackDoubleHdf5Array3dOfValues
		 */
		void pushBackFloatHdf5Array3dOfValues(const float * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds an nd array of explicit float values to the property values.
		 *
		 * @exception std::invalid_argument If <tt> minimumValue == nullptr </tt> and <tt> maximumValue != nullptr </tt>.
		 * @exception std::invalid_argument	If <tt> minimumValue != nullptr </tt> and <tt> maximumValue == nullptr </tt>.
		 *
		 * @copydetails	pushBackDoubleHdf5ArrayOfValues
		 */
		void pushBackFloatHdf5ArrayOfValues(float const * values, uint64_t const * numValues, unsigned int numArrayDimensions, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Pushes back a reference to an existing (or a "to exist") HDF dataset in a particular HDF
		 * proxy. The reason can be that the values already exist in an external file (only HDF5 for
		 * now) or that the writing of the values in the external file is differed in time.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param [in]	proxy	   	The HDF5 proxy where the values are already or will be stored. If
		 * 							@c nullptr, then a default HDF proxy must be defined in the
		 * 							repository.
		 * @param 	  	datasetName	(Optional) The HDF5 dataset name where the values are stored. If
		 * 							empty, the dataset will be named the same as the dataset naming
		 * 							convention of fesapi :
		 * 							<tt>getHdfGroup() + "/values_patch" + patchIndex</tt>
		 *
		 * @returns	The name of the referenced HDF5 dataset.
		 */
		std::string pushBackRefToExistingFloatingPointDataset(EML2_NS::AbstractHdfProxy* proxy, const std::string & datasetName = "");

		/**
		 * Gets all the values of a particular patch of this instance which are supposed to be double
		 * ones.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values. Size is
		 * 							<tt>getValuesCountOfPatch(patchIndex)</tt>.
		 */
		void getDoubleValuesOfPatch(unsigned int patchIndex, double * values) const;

		/**
		 * Gets all the values of a particular patch of this instance which are supposed to be float
		 * ones.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values. Size is
		 * 							<tt>getValuesCountOfPatch(patchIndex)</tt>.
		 */
		void getFloatValuesOfPatch(unsigned int patchIndex, float * values) const;

		//******************************************/
		//*** For FLOATING POINT hyperslabbing *****/
		//******************************************/

		/**
		 * Get some of the values of a particular patch of the instance as float ones. This method makes
		 * use of HDF5 hyperslabbing.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex					The index of the patch we want the values from.
		 * @param [out]	values						The array (pointer) of values must be
		 * 											preallocated. Size is
		 * 											<tt>getValuesCountOfPatch(patchIndex)</tt>.
		 * @param 	   	numValuesInEachDimension	The number of property values ordered by dimension of
		 * 											the array to read. It is ordered from slowest dimension
		 * 											to fastest dimension.
		 * @param 	   	offsetInEachDimension   	The offset values ordered by dimension of the array
		 * 											to read. It is ordered from slowest dimension to fastest
		 * 											dimension.
		 * @param 	   	numArrayDimensions			The number of dimensions of the HDF5 array to read.
		 */
		void getFloatValuesOfPatch(
			unsigned int patchIndex,
			float* values,
			uint64_t const * numValuesInEachDimension,
			uint64_t const * offsetInEachDimension,
			unsigned int numArrayDimensions
		) const;

		/**
		 * Get some of the values of a particular patch of the instance as float ones. This method makes
		 * use of HDF5 hyperslabbing.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 		  	patchIndex			  	The index of the patch we want the values from.
		 * @param [in,out]	values				  	The array (pointer) of values must be preallocated.
		 * 											Size is <tt>getValuesCountOfPatch(patchIndex)</tt>.
		 * @param 		  	valueCountInFastestDim	The number of values to read in the fastest dimension
		 * 											(mainly I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values to read in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to read in the slowest dimension
		 * 											(mainly K dimension).
		 * @param 		  	offsetInFastestDim	  	The offset value for reading in the fastest dimension
		 * 											(mainly I dimension).
		 * @param 		  	offsetInMiddleDim	  	The offset value for reading in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	offsetInSlowestDim	  	The offset value for reading in the slowest dimension
		 * 											(mainly K dimension).
		 */
		void getFloatValuesOf3dPatch(
			unsigned int patchIndex,
			float* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim
		) const;
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_CommentProperty) CommentProperty;
#endif	
	class CommentProperty : public AbstractValuesProperty
	{
	public:
		void pushBackStringHdf5ArrayOfValues(const std::vector<std::string> & values, EML2_NS::AbstractHdfProxy * proxy);
		std::vector<std::string> getStringValuesOfPatch(unsigned int patchIndex);
		
		/**
		 * Pushes back a new patch of values for this property where the values have not to be written in
		 * the HDF5 file. The reason can be that the values already exist in an external file (only HDF5
		 * for now) or that the writing of the values in the external file is differed in time.
		 *
		 * @exception	std::invalid_argument	If @p hdfProxy is null.
		 *
		 * @param [in]	hdfProxy   	The HDF5 proxy where the values are already or will be stored. It
		 * 							cannot be null.
		 * @param 	  	datasetName	(Optional) If not provided during the method call, the dataset will
		 * 							be named the same as the dataset naming convention of fesapi:
		 * 							<tt>"/RESQML/" + prop-&gt;uuid + "/values_patch" + patchIndex</tt>
		 * @param 	  	nullValue  	(Optional) Not used for comment properties.
		 *
		 * @returns	The name of the HDF5 dataset.
		 */
		std::string pushBackRefToExistingDataset(EML2_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName = "");
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_ContinuousProperty) ContinuousProperty;
#endif
	class ContinuousProperty : public AbstractValuesProperty
	{
	public:

		gsoap_resqml2_0_1::resqml20__ResqmlUom getUom() const;
		std::string getUomAsString() const;
		
		/**
		 * @brief Adds a 1d array of explicit double values to the property values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values			All the property values to set ordered according the topology
		 * 									of the representation it is based on.
		 * @param 		  	valueCount  	The number of values to write.
		 * @param 		  	minimumValue	The minimum value of the values to add. If @c NaN is
		 * 									provided then both minimum and maximum values will be computed
		 * 									from the values.
		 * @param 		  	maximumValue	The maximum value of the values to add. If @c NaN is
		 * 									provided then both maximum and minimum values will be computed
		 * 									from the values.
		 * @param [in,out]	proxy			(Optional) The HDF proxy where to write the property values.
		 * 									It must be already opened for writing and won't be closed in this
		 * 									method. If @c nullptr (default value), then a default HDF proxy
		 * 									must be defined in the repository.
		 */
		void pushBackDoubleHdf5Array1dOfValues(const double * values, uint64_t valueCount,
			double minimumValue, double maximumValue, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief Adds a 2d array of explicit double values to the property values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values				  	All the property values to set ordered according the
		 * 											topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly J dimension).
		 * @param 		  	minimumValue		  	The minimum value of the values to add. If
		 * 											@c NaN is provided then both minimum and maximum
		 * 											values will be computed from the values.
		 * @param 		  	maximumValue		  	The maximum value of the values to add. If
		 * 											@c NaN is provided then both maximum and minimum
		 * 											values will be computed from the values.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default value), then a default HDF proxy must be
		 * 											defined in the repository.
		 */
		void pushBackDoubleHdf5Array2dOfValues(const double * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim,
			double minimumValue, double maximumValue, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief Adds a 3d array of explicit double values to the property values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values				  	All the property values to set ordered according the
		 * 											topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values to write in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param 		  	minimumValue		  	The minimum value of the values to add. If
		 * 											@c NaN is provided then both minimum and maximum
		 * 											values will be computed from the values.
		 * @param 		  	maximumValue		  	The maximum value of the values to add. If
		 * 											@c NaN is provided then both maximum and minimum
		 * 											values will be computed from the values.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default value), then a default HDF proxy must be
		 * 											defined in the repository.
		 */
		void pushBackDoubleHdf5Array3dOfValues(const double * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim,
			double minimumValue, double maximumValue, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief Adds an nd array of explicit double values to the property values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values			  	All the property values to set ordered according the
		 * 										topology of the representation it is based on.
		 * @param 		  	numValues		  	The number of property values ordered by dimension of the
		 * 										array to write.
		 * @param 		  	numArrayDimensions	The number of dimensions of the array to write.
		 * @param [in,out]	proxy			  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If @c nullptr (default value),
		 * 										then a default HDF proxy must be defined in the
		 * 										repository.
		 * @param [in]	  	minimumValue	  	The minimum value (or value vector) of the
		 * 										values to add. If @c nullptr is provided for both @p
		 * 										minimumValue and @p maximumValue and if the dimension of
		 * 										value is 1 then both minimum and maximum values will be
		 * 										computed from the values.
		 * @param [in]	  	maximumValue	  	The maximum value (or value vector) of the
		 * 										values to add. If @ nullptr is provided for both @p
		 * 										maximumValue and @p minimumValue and if the dimension of
		 * 										value is 1 then both maximum and minimum values will be
		 * 										computed from the values.
		 */
		void pushBackDoubleHdf5ArrayOfValues(double const * values, uint64_t const * numValues, unsigned int numArrayDimensions,
			double * minimumValue, double * maximumValue, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds a 1d array of explicit float values to the property values.
		 *
		 * @copydetails pushBackDoubleHdf5Array1dOfValues
		 */
		void pushBackFloatHdf5Array1dOfValues(const float * values, uint64_t valueCount,
			float minimumValue, float maximumValue, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds a 2d array of explicit float values to the property values.
		 *
		 * @copydetails pushBackDoubleHdf5Array2dOfValues
		 */
		void pushBackFloatHdf5Array2dOfValues(const float * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim,
			float minimumValue, float maximumValue, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds a 3d array of explicit float values to the property values.
		 *
		 * @copydetails pushBackDoubleHdf5Array3dOfValues
		 */
		void pushBackFloatHdf5Array3dOfValues(const float * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim,
			float minimumValue, float maximumValue, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds an nd array of explicit float values to the property values.
		 * 
		 * @exception std::invalid_argument If <tt> minimumValue == nullptr </tt> and <tt> maximumValue != nullptr </tt>.
		 * @exception std::invalid_argument	If <tt> minimumValue != nullptr </tt> and <tt> maximumValue == nullptr </tt>.
		 * 									
		 * @copydetails	pushBackDoubleHdf5ArrayOfValues
		 */
		void pushBackFloatHdf5ArrayOfValues(float const * values, uint64_t const * numValues, unsigned int numArrayDimensions,
			float * minimumValue, float * maximumValue, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief	Gets the minimum value of a non vector property or the minimum value of one given
		 * 			value of a vector property. This minimum value is read (it is not computed).
		 *
		 * @param 	index	(Optional) @c 0 (default value, corresponding to the non vector property case) or
		 * 					zero-based index of the vector value for which we look for the minimum value
		 * 					(vector property case).
		 *
		 * @returns	The minimum value of the non vector property or the minimum value at position @p
		 * 			index of the vector value or @c NaN if @p index is out of range (strictly
		 * 			greater than @p 0 for a non vector property or greater than the vector size for a
		 * 			vector property).
		 */
		double getMinimumValue(unsigned int index = 0) const;

		/**
		 * @brief	Gets the maximum value of a non vector property or the maximum value of one given
		 * 			value of a vector property. This maximum value is read (it is not computed).
		 *
		 * @param 	index	(Optional) @c 0 (default value, corresponding to the non vector property case) or
		 * 					zero-based index of the vector value for which we look for the maximum value
		 * 					(vector property case).
		 *
		 * @returns	The maximum value of the non vector property or the maximum value at position @p
		 * 			index of the vector value or @c NaN if @p index is out of range (strictly
		 * 			greater than @p 0 for a non vector property or greater than the vector size for a
		 * 			vector property).
		 */
		double getMaximumValue(unsigned int index = 0) const;

		/**
		 * @brief	Sets the minimum value of a non vector property or the minimum value of one given
		 * 			value of a vector property.
		 *
		 * @param 	value	The minimum value to set.
		 * @param 	index	(Optional)  @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we want to set the
		 * 					minimum value (vector property case).
		 */
		void setMinimumValue(double value, unsigned int index = 0) const;

		/**
		 * @brief	Sets the maximum value of a non vector property or the maximum value of one given
		 * 			value of a vector property.
		 *
		 * @param 	value	The maximum value to set.
		 * @param 	index	(Optional)  @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we want to set the
		 * 					maximum value (vector property case).
		 */
		void setMaximumValue(double value, unsigned int index = 0) const;

		//******************************************/
		//*** For FLOATING POINT hyperslabbing *****/
		//******************************************/

		/**
		 * Create an nd array of explicit float values to the property values. No values are written to
		 * this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 		  	numValues		  	The number of property values ordered by dimension of the
		 * 										array to write.  It is ordered from slowest dimension to
		 * 										fastest dimension.
		 * @param 		  	numArrayDimensions	The number of dimensions of the array to write.
		 * @param [in]	  	minimumValue	  	The minimum value (or value vector) of the
		 * 										values to add. If @c nullptr (default) is provided then
		 * 										neither minimum nor maximum value will be set.
		 * @param [in]	  	maximumValue	  	The maximum value (or value vector) of the
		 * 										values to add. If @c nullptr (default) is provided then
		 * 										neither maximum nor minimum value will be set.
		 * @param [in,out]	proxy			  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If @c nullptr (default), a
		 * 										default HDF proxy must be defined into the data object
		 * 										repository.
		 */
		void pushBackHdf5ArrayOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			uint64_t const * numValues,
			unsigned int numArrayDimensions,
			double * minimumValue, double * maximumValue,
			EML2_NS::AbstractHdfProxy* proxy = nullptr
		);
		using AbstractValuesProperty::pushBackHdf5ArrayOfValues;

		/**
		 * Creates a 1d array of explicit double values to the property values. No values are written to
		 * this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 			datatype			The datatype of the values 
		 * @param 		  	valueCount			The number of values to write).
		 * @param 		  	minimumValue		The minimum value of the values to add. If
		 * 										@c NaN is provided (default) then neither minimum nor
		 * 										maximum value will be set.
		 * @param 		  	maximumValue		The maximum value of the values to add. If
		 * 										@c NaN is provided (default) then neither maximum nor
		 * 										minimum value will be set.
		 * @param [in,out]	proxy				(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and
		 * 										won't be closed in this method. If @c nullptr
		 * 										(default), a default HDF proxy must be defined into
		 * 										the data object repository.
		 */
		void pushBackHdf5Array1dOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			uint64_t valueCount,
			double minimumValue, double maximumValue,
			EML2_NS::AbstractHdfProxy* proxy = nullptr
		);
		using AbstractValuesProperty::pushBackHdf5Array1dOfValues;

		/**
		 * Creates a 2d array of explicit double values to the property values. No values are written to
		 * this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param 		  	minimumValue		  	The minimum value of the values to add. If
		 * 											@c NaN is provided (default) then neither minimum nor
		 * 											maximum value will be set.
		 * @param 		  	maximumValue		  	The maximum value of the values to add. If
		 * 											@c NaN is provided (default) then neither maximum nor
		 * 											minimum value will be set.
		 * @param [in,out]	proxy					(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default), a default HDF proxy must be defined into
		 * 											the data object repository.
		 */
		void pushBackHdf5Array2dOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			double minimumValue, double maximumValue,
			EML2_NS::AbstractHdfProxy* proxy = nullptr
		);
		using AbstractValuesProperty::pushBackHdf5Array2dOfValues;

		/**
		 * Creates a 3d array of explicit float values to the property values. No values are written to
		 * this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values to write in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param 		  	minimumValue		  	The minimum value of the values to add. If
		 * 											@c NaN is provided (default) then neither minimum nor
		 * 											maximum value will be set.
		 * @param 		  	maximumValue		  	The maximum value of the values to add. If
		 * 											@c NaN is provided (default) then neither maximum nor
		 * 											minimum value will be set.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default), a default HDF proxy must be defined into
		 * 											the data object repository.
		 */
		void pushBackHdf5Array3dOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			double minimumValue, double maximumValue,
			EML2_NS::AbstractHdfProxy* proxy = nullptr
		);
		using AbstractValuesProperty::pushBackHdf5Array3dOfValues;

		/**
		 * Sets some values of an existing 3d array of explicit float values of a particular patch. This
		 * method makes use of HDF5 hyperslabbing. Since this methods only pushes back values into an
		 * existing array, it is to be used along with pushBackFloatHdf5Array3dOfValues().
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 * @exception	std::out_of_range	 	If @p patchIndex is strictly greater than patch count and
		 * 										different from unsigned int maximum value.
		 *
		 * @param 		  	values				  	All the property values to set ordered according to
		 * 											the topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values to write in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param 		  	offsetInFastestDim	  	The offset value for writing in the fastest dimension
		 * 											(mainly I dimension).
		 * @param 		  	offsetInMiddleDim	  	The offset value for writing in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	offsetInSlowestDim	  	The offset value for writing in the slowest dimension
		 * 											(mainly K dimension).
		 * @param 		  	computeMinMax		  	True if FESAPI needs to compute
		 * 											the min and  max from the given @p values in order to
		 * 											set them.
		 * @param [in,out]	proxy				  	The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @p nullptr
		 * 											(default), a default HDF proxy must be defined into
		 * 											the data object repository.
		 * @param 		  	patchIndex			  	(Optional) Zero-based index of the patch where to
		 * 											write the property values. If not provided, its
		 * 											default value is by convention set to unsigned int
		 * 											maximum value and the property values will be written
		 * 											in the last property values patch (the one with the
		 * 											greatest index).
		 */
		void setValuesOfFloatHdf5Array3dOfValues(
			float const * values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			bool computeMinMax,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfDoubleHdf5Array3dOfValues(
			double const * values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			bool computeMinMax,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());

		/**
		 * Set some values of an existing 3d array of explicit float values of a particular patch.  This
		 * method makes use of HDF5 hyperslabbing. This method is to be used along with one of the
		 * pushBackFloatHdf5ArrayOfValues() methods which do not write any value.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 * @exception	std::out_of_range	 	If @p patchIndex is strictly greater than patch count and
		 * 										different from unsigned int maximum value.
		 *
		 * @param 		  	values			  	All the property values to set ordered according to the
		 * 										topology of the representation it is based on.
		 * @param 		  	numValues		  	The number of property values ordered by dimension of the
		 * 										array to write. It is ordered from slowest dimension to
		 * 										fastest dimension.
		 * @param 		  	offsetValues	  	The offset values ordered by dimension of the array to
		 * 										write. It is ordered from slowest dimension to fastest
		 * 										dimension.
		 * @param 		  	numArrayDimensions	The number of dimensions of the array to write.
		 * @param 		  	computeMinMax	  	True if FESAPI needs to compute the
		 * 										min and  max from the given @p values in order to set
		 * 										them.
		 * @param [in,out]	proxy			  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If @p nullptr (default), a
		 * 										default HDF proxy must be defined into the data object
		 * 										repository.
		 * @param 		  	patchIndex		  	(Optional) Zero-based index of the patch where to write
		 * 										the property values. If not provided, its default value
		 * 										is by convention set to unsigned int maximum value and
		 * 										the property values will be written in the last property
		 * 										values patch (the one with the greatest index).
		 */
		void setValuesOfFloatHdf5ArrayOfValues(
			float const * values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			bool computeMinMax,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfDoubleHdf5ArrayOfValues(
			double const * values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			bool computeMinMax,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_DiscreteProperty) DiscreteProperty;
#endif
	/**
	 * Proxy class for a discrete  property. Such property contains discrete integer values;
	 * typically used to store any type of index. So that the value range can be known before
	 * accessing all values, it also optionally stores the minimum and maximum value in the range.
	 */
	class DiscreteProperty : public AbstractValuesProperty
	{
	public:
		/**
		 * @brief Adds a 1d array of explicit int 64 bits values to the property values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values			All the property values to set ordered according to the
		 * 									topology of the representation it is based on.
		 * @param 		  	valueCount  	The number of values to write.
		 * @param [in,out]	proxy			The HDF proxy where to write the property values. It must be
		 * 									already opened for writing and won't be closed in this method. If
		 * 									@c nullptr, then a default HDF proxy must be defined in the
		 * 									repository.
		 * @param 		  	nullValue   	The null value.
		 * @param 		  	minimumValue	The minimum value of the values to add.
		 * @param 		  	maximumValue	The maximum value of the values to add.
		 */
		void pushBackInt64Hdf5Array1dOfValues(const int64_t * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue, int64_t minimumValue, int64_t maximumValue);

		/**
		 * Adds a 1d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array1dOfValues
		 */
		void pushBackInt32Hdf5Array1dOfValues(const int * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, int nullValue, int minimumValue, int maximumValue);

		/**
		 * Adds a 1d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array1dOfValues
		 */
		void pushBackInt16Hdf5Array1dOfValues(const short * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, short nullValue, short minimumValue, short maximumValue);

		/**
		 * Adds a 1d array of explicit int8_t values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array1dOfValues
		 */
		void pushBackInt8Hdf5Array1dOfValues(const int8_t * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue, int8_t minimumValue, int8_t maximumValue);

		/**
		 * @brief Adds a 2d array of explicit int 64 bits values to the property values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values				  	All the property values to set ordered according to
		 * 											the topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly J dimension).
		 * @param [in,out]	proxy				  	The HDF proxy where to write the property values. It
		 * 											must be already opened for writing and won't be
		 * 											closed in this method. If @c nullptr, then a default
		 * 											HDF proxy must be defined in the repository.
		 * @param 		  	nullValue			  	The null value.
		 * @param 		  	minimumValue		  	The minimum value of the values to add.
		 * @param 		  	maximumValue		  	The maximum value of the values to add.
		 */
		void pushBackInt64Hdf5Array2dOfValues(const int64_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue, int64_t minimumValue, int64_t maximumValue);
		
		/**
		 * Adds a 2d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array2dOfValues
		 */
		void pushBackInt32Hdf5Array2dOfValues(const int * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int nullValue, int minimumValue, int maximumValue);
		
		/**
		 * Adds a 2d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array2dOfValues
		 */
		void pushBackInt16Hdf5Array2dOfValues(const short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, short nullValue, short minimumValue, short maximumValue);
		
		/**
		 * Adds a 2d array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array2dOfValues
		 */
		void pushBackUInt16Hdf5Array2dOfValues(const unsigned short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue);
		
		/**
		 * Adds a 2d array of explicit int8_t values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array2dOfValues
		 */
		void pushBackInt8Hdf5Array2dOfValues(const int8_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue, int8_t minimumValue, int8_t maximumValue);

		/**
		 * @brief Adds a 3d array of explicit int 64 bits values to the property values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values				  	All the property values to set ordered according the
		 * 											topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values to write in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param [in,out]	proxy				  	The HDF proxy where to write the property values. It
		 * 											must be already opened for writing and won't be
		 * 											closed in this method. If @c nullptr, then a default
		 * 											HDF proxy must be defined in the repository.
		 * @param 		  	nullValue			  	The null value.
		 * @param 		  	minimumValue		  	The minimum value of the values to add.
		 * @param 		  	maximumValue		  	The maximum value of the values to add.
		 */
		void pushBackInt64Hdf5Array3dOfValues(const int64_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue, int64_t minimumValue, int64_t maximumValue);
		
		/**
		 * Adds a 3d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array3dOfValues
		 */
		void pushBackInt32Hdf5Array3dOfValues(const int * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int nullValue, int minimumValue, int maximumValue);
		
		/**
		 * Adds a 3d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array3dOfValues
		 */
		void pushBackInt16Hdf5Array3dOfValues(const short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, short nullValue, short minimumValue, short maximumValue);
		
		/**
		 * Adds a 3d array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array3dOfValues
		 */
		void pushBackUInt16Hdf5Array3dOfValues(const unsigned short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue);
		
		/**
		 * Adds a 3d array of explicit int8_t values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array3dOfValues
		 */
		void pushBackInt8Hdf5Array3dOfValues(const int8_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue, int8_t minimumValue, int8_t maximumValue);

		/**
		 * @brief Adds an nd array of explicit int 64 bits values to the property values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values					All the property values to set ordered according the
		 * 											topology of the representation it is based on.
		 * @param [in]	  	numValues				The number of property values ordered by dimension of
		 * 											the array to write.
		 * @param 		  	numDimensionsInArray	The number of dimensions in the array to write.
		 * @param [in,out]	proxy					The HDF proxy where to write the property values. It
		 * 											must be already opened for writing and won't be closed in
		 * 											this method. If @c nullptr, then a default HDF proxy must
		 * 											be defined in the repository.
		 * @param 		  	nullValue				The null value.
		 */
		 void pushBackInt64Hdf5ArrayOfValues(const int64_t * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue, int64_t minimumValue, int64_t maximumValue);
		
		/**
		 * Adds an nd array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues
		 */
		void pushBackInt32Hdf5ArrayOfValues(const int * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int nullValue, int minimumValue, int maximumValue);
		
		/**
		 * Adds an nd array of explicit short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues
		 */
		void pushBackInt16Hdf5ArrayOfValues(const short * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, short nullValue, short minimumValue, short maximumValue);
		
		/**
		 * Adds an nd array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues
		 */
		void pushBackUInt16Hdf5ArrayOfValues(const unsigned short * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue);
		
		/**
		 * Adds an nd array of explicit int8_t values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues
		 */
		void pushBackInt8Hdf5ArrayOfValues(const int8_t * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue, int8_t minimumValue, int8_t maximumValue);
		
		/**
		 * Creates an nd array of explicit int 64 bits values into the property values. No values are
		 * written to this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 			datatype			The datatype of the values 
		 * @param [in]	  	numValues		  	The number of property values ordered by dimension of the
		 * 										array to write. It is ordered from slowest dimension to
		 * 										fastest dimension.
		 * @param 		  	numArrayDimensions	The number of dimensions of the array to write.
		 * @param [in]	  	minimumValue	  	If non-nullptr, a pointer to the minimum values. If non-
		 * 										nullptr, the count of minimum values is this property
		 * 										count.
		 * @param [in]	  	maximumValue	  	If non-nullptr, a pointer to the maximum values. If non-
		 * 										nullptr, the count of maximum values is this property
		 * 										count.
		 * @param 		  	nullValue		  	(Optional) The null value. Default value is int 64 bits
		 * 										maximum value.
		 * @param [in,out]	proxy			  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If @c nullptr (default), a
		 * 										default HDF proxy must be defined into the data object
		 * 										repository.
		 */
		void pushBackHdf5ArrayOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			const uint64_t* numValues,
			unsigned int numArrayDimensions,
			int64_t* minimumValue, int64_t* maximumValue,
			int64_t nullValue = std::numeric_limits<int64_t>::max(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr);
		using AbstractValuesProperty::pushBackHdf5ArrayOfValues;

		/**
		 * Creates a 1d array of values into the property values. No values are written
		 * to this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 			datatype			The datatype of the values 
		 * @param 		  	valueCount			The count of values.
		 * @param 		  	minimumValue		  	The minimum value of the values in the HDF5 dataset.
		 * @param 		  	maximumValue		  	The maximum value of the values in the HDF5 dataset.
		 * @param 		  	nullValue			  	(Optional) The null value. Default value is int 64
		 * 											bits maximum value.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @p nullptr
		 * 											(default), a default HDF proxy must be defined into
		 * 											the data object repository.
		 */
		void pushBackHdf5Array1dOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			uint64_t valueCount,
			int64_t minimumValue, int64_t maximumValue,
			int64_t nullValue = std::numeric_limits<int64_t>::max(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr);
		using AbstractValuesProperty::pushBackHdf5Array1dOfValues;

		/**
		 * Creates a 2d array of explicit int 64 values into the property values. No values are written
		 * to this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 			datatype			The datatype of the values 
		 * @param 		  	valueCountInFastestDim	The number of values in the fastest dimension (mainly
		 * 											I dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values in the slowest dimension (mainly
		 * 											K dimension).
		 * @param 		  	minimumValue		  	The minimum value of the values in the HDF5 dataset.
		 * @param 		  	maximumValue		  	The maximum value of the values in the HDF5 dataset.
		 * @param 		  	nullValue			  	(Optional) The null value. Default value is int 64
		 * 											bits maximum value.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @p nullptr
		 * 											(default), a default HDF proxy must be defined into
		 * 											the data object repository.
		 */
		void pushBackHdf5Array2dOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			int64_t minimumValue, int64_t maximumValue,
			int64_t nullValue = std::numeric_limits<int64_t>::max(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr);
		using AbstractValuesProperty::pushBackHdf5Array2dOfValues;

		/**
		 * Creates a 3d array of explicit int 64 values into the property values. No values are written
		 * to this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 			datatype			The datatype of the values 
		 * @param 		  	valueCountInFastestDim	The number of values in the fastest dimension (mainly
		 * 											I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values in the middle dimension (mainly
		 * 											J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values in the slowest dimension (mainly
		 * 											K dimension).
		 * @param 		  	minimumValue		  	The minimum value of the values in the HDF5 dataset.
		 * @param 		  	maximumValue		  	The maximum value of the values in the HDF5 dataset.
		 * @param 		  	nullValue			  	(Optional) The null value. Default value is int 64
		 * 											bits maximum value.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @p nullptr
		 * 											(default), a default HDF proxy must be defined into
		 * 											the data object repository.
		 */
		void pushBackHdf5Array3dOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			int64_t minimumValue, int64_t maximumValue,
			int64_t nullValue = std::numeric_limits<int64_t>::max(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr);
		using AbstractValuesProperty::pushBackHdf5Array3dOfValues;

		/**
		 * Adds a 3d array of explicit int 64 bits values into the property values. Since this methods
		 * only pushes back values into an existing array, it is to be used along with
		 * pushBackInt64Hdf5Array3dOfValues().
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 * @exception	std::out_of_range	 	If @p patchIndex is strictly greater than patch count and
		 * 										different from unsigned int maximum value.
		 *
		 * @param [in]	  	values				  	All the property values to set ordered according to
		 * 											the topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values to write in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param 		  	offsetInFastestDim	  	The offset value for writing in the fastest dimension
		 * 											(mainly I dimension).
		 * @param 		  	offsetInMiddleDim	  	The offset value for writing in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	offsetInSlowestDim	  	The offset value for writing in the slowest dimension
		 * 											(mainly K dimension).
		 * @param 		  	computeMinMax		  	True if FESAPI needs to compute the min and  max from
		 * 											the given @p values in order to set them.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @p nullptr
		 * 											(default), a default HDF proxy must be defined into
		 * 											the data object repository.
		 * @param 		  	patchIndex			  	(Optional) Zero-based index of the patch where to
		 * 											write the property values. If not provided, its
		 * 											default value is by convention set to unsigned int
		 * 											maximum value and the property values will be written
		 * 											in the last property values patch (the one with the
		 * 											greatest index).
		 */
		void setValuesOfInt64Hdf5Array3dOfValues(
			int64_t* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			bool computeMinMax,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfInt32Hdf5Array3dOfValues(
			int32_t* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			bool computeMinMax,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		using AbstractValuesProperty::setValuesOfInt32Hdf5Array3dOfValues;

		/**
		 * Adds an nd array of explicit int 64 bits values into to the property values. Since this
		 * methods only pushes back values into an existing array, it is to be used along with
		 * pushBackInt64Hdf5ArrayOfValues().
		 *
		 * @exception	std::invalid_argument	If @p proxy is null and no default HDF proxy is defined
		 * 										into the data object repository.
		 * @exception	std::out_of_range	 	If @p patchIndex is strictly greater than patch count and
		 * 										different from unsigned int maximum value.
		 *
		 * @param [in]	  	values			  	All the property values to set ordered according to the
		 * 										topology of the representation it is based on.
		 * @param 		  	numValues		  	The number of property values ordered by dimension of the
		 * 										array to write. It is ordered from slowest dimension to
		 * 										fastest dimension.
		 * @param 		  	offsetValues	  	The offset values ordered by dimension of the array to
		 * 										write. It is ordered from slowest dimension to fastest
		 * 										dimension.
		 * @param 		  	numArrayDimensions	The number of dimensions of the array to write.
		 * @param 		  	computeMinMax	  	True to compute and to set minimum and maximum values.
		 * @param [in,out]	proxy			  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If null (default value), a
		 * 										default HDF proxy must be defined into the data object
		 * 										repository.
		 * @param 		  	patchIndex		  	(Optional) Zero-based index of the patch where to write
		 * 										the property values. If not provided, its default value
		 * 										is by convention set to unsigned int maximum value and
		 * 										the property values will be written in the last property
		 * 										values patch (the one with the greatest index).
		 */
		void setValuesOfInt64Hdf5ArrayOfValues(
			int64_t* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			bool computeMinMax,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		void setValuesOfInt32Hdf5ArrayOfValues(
			int32_t* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			bool computeMinMax,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = std::numeric_limits<uint64_t >::max());
		using AbstractValuesProperty::setValuesOfInt32Hdf5ArrayOfValues;
		
		/**
		 * @brief	Checks if a non vector property or a given value of a vector property has got a
		 * 			minimum value already computed (or set).
		 *
		 * @param 	index	(Optional) @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we want to know if a
		 * 					minimum value exists (vector property case).
		 *
		 * @returns	True if there exists a minimum value, false if not.
		 */
		bool hasMinimumValue(uint64_t index = 0) const;

		/**
		 * @brief	Gets the minimum value of a non vector property or the minimum value of one given
		 * 			value of a vector property. This minimum value is read (it is not computed).
		 *
		 * @exception	std::logic_error	If this property has no minimum value.
		 *
		 * @param 	index	(Optional) @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we look for the
		 * 					minimum value (vector property case).
		 *
		 * @returns	The minimum value of the non vector property or the minimum value at position @p
		 * 			index of the vector value or @c NaN if @p index is out of range (strictly greater
		 * 			than @p 0 for a non vector property or greater than the vector size for a vector
		 * 			property).
		 */
		int64_t getMinimumValue(uint64_t index = 0) const;

		/**
		 * @brief	Checks if a non vector property or a given value of a vector property has got a
		 * 			maximum value already computed (or set).
		 *
		 * @param 	index	(Optional) @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we want to know if a
		 * 					maximum value exists (vector property case).
		 *
		 * @returns	True if there exists a maximum value, false if not.
		 */
		bool hasMaximumValue(uint64_t index = 0) const;

		/**
		 * @brief	Gets the maximum value of a non vector property or the maximum value of one given
		 * 			value of a vector property. This maximum value is read (it is not computed).
		 *
		 * @exception	std::logic_error	If this property has no maximum value.
		 *
		 * @param 	index	(Optional) @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we look for the
		 * 					maximum value (vector property case).
		 *
		 * @returns	The maximum value of the non vector property or the maximum value at position @p
		 * 			index of the vector value or @c NaN if @p index is out of range (strictly greater
		 * 			than @p 0 for a non vector property or greater than the vector size for a vector
		 * 			property).
		 */
		int64_t getMaximumValue(uint64_t index = 0) const;

		/**
		 * @brief	Sets the minimum value of a non vector property or the minimum value of one given
		 * 			value of a vector property.
		 *
		 * @param 	value	The minimum value to set.
		 * @param 	index	(Optional)  @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we want to set the
		 * 					minimum value (vector property case).
		 */
		void setMinimumValue(int64_t value, uint64_t index = 0) const;

		/**
		 * @brief	Sets the maximum value of a non vector property or the maximum value of one given
		 * 			value of a vector property.
		 *
		 * @param 	value	The maximum value to set.
		 * @param 	index	(Optional)  @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we want to set the
		 * 					maximum value (vector property case).
		 */
		void setMaximumValue(int64_t value, uint64_t index = 0) const;
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_DoubleTableLookup) DoubleTableLookup;
#endif	
	/**
	 * @brief	Defines a function for table lookups. For example, used for linear interpolation, such as PVT.
	 * 			
	 * 			Used for categorical properties, which also may use a double table lookup.
	 */
	class DoubleTableLookup : public COMMON_NS::AbstractObject
	{
	public:
		/**
		 * Checks whether a key is contained within this double table lookup.
		 *
		 * @param 	key	A key.
		 *
		 * @returns	True if @p key is a key of this double table lookup, false if not.
		 */
		bool containsKey(double key);

		/**
		 * Gets the count of items in the double table lookup (in its map).
		 *
		 * @returns	The count of items.
		 */
		uint64_t getItemCount() const;

		/**
		 * Gets the key of a key/value pair at a particular index of this double table lookup (in its
		 * map).
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getItemCount().
		 *
		 * @param 	index	Zero-based index of the key/value pair.
		 *
		 * @returns	The key of the key/value pair at position @p index.
		 */
		double getKeyAtIndex(uint64_t index) const;

		/**
		 * Gets the value of a key/value pair at a particular index of this double table lookup
		 * (in its map).
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getItemCount().
		 *
		 * @param 	index	Zero-based index of the key/value pair.
		 *
		 * @returns	The value of the key/value pair at position @p index.
		 */
		 double getValueAtIndex(uint64_t index) const;

		/**
		 * Gets a value from its associated key.
		 *
		 * @param 	longValue	A key.
		 *
		 * @returns	The value corresponding to the key @p longValue if it exists, NaN if
		 * 			not.
		 */
		double getValueAtKey(double key);

		/**
		 * Adds a key/value pair to this double table lookup. No verification that the key already exists is done.
		 *
		 * @param 	key		A key.
		 * @param 	value	Teh associated value.
		 */
		void addValue(double key, double longValue);

		/**
		 * Modifies the value associated to a key. If the key does not exist, nothing is
		 * done.
		 *
		 * @param 	key		A key.
		 * @param 	value	Teh associated value.
		 */
		void setValue(double key, double longValue);

		/**
		 * Gets the minimum key in this double table lookup. It reads it from file.
		 *
		 * @returns	The minimum key if some key/value pairs exists in this double table lookup, otherwise
		 * 			the double maximum value.
		 */
		double getMinimumValue();

		/**
		 * Gets the maximum key in this double table lookup. It reads it from file.
		 *
		 * @returns	The maximum key if some key/value pairs exists in this double table lookup, otherwise
		 * 			the double lowest value.
		 */
		double getMaximumValue();
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_StringTableLookup) StringTableLookup;
#endif	
	class StringTableLookup : public COMMON_NS::AbstractObject
	{
	public:
		/**
		 * Checks whether a key is contained within this string lookup.
		 *
		 * @param 	key	A key.
		 *
		 * @returns	True if @p longValue is a key of this string table lookup, false if not.
		 */
		bool containsKey(int64_t key);

		/**
		 * Gets the count of items in the string table lookup (in its map).
		 *
		 * @returns	The count of items.
		 */
		uint64_t getItemCount() const;

		/**
		 * Gets the key of a key/value pair at a particular index of this string table lookup (in its
		 * map).
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getItemCount().
		 *
		 * @param 	index	Zero-based index of the key/value pair.
		 *
		 * @returns	The key of the key/value pair at position @p index.
		 */
		int64_t getKeyAtIndex(uint64_t index) const;

		/**
		 * Gets the string value of a key/value pair at a particular index of this string table lookup
		 * (in its map).
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getItemCount().
		 *
		 * @param 	index	Zero-based index of the key/value pair.
		 *
		 * @returns	The string value of the key/value pair at position @p index.
		 */
		std::string getStringValueAtIndex(uint64_t index) const;

		/**
		 * Gets a string value from its associated key.
		 *
		 * @param 	key	A key.
		 *
		 * @returns	The string value corresponding to the key @p longValue if it exists, empty string if
		 * 			not.
		 */
		std::string getStringValue(int64_t key);

		/**
		 * Adds a key/value pair to this string table lookup. No verification that the key (or string
		 * value) already exists is done.
		 *
		 * @param 	strValue 	A string value.
		 * @param 	longValue	A key.
		 */
		void addValue(const std::string & strValue, int64_t key);

		/**
		 * Modifies the string value associated to a key. If the key does not exist, nothing is
		 * done.
		 *
		 * @param 	strValue 	The new string value.
		 * @param 	longValue	A key.
		 */
		void setValue(const std::string & strValue, int64_t key);

		/**
		 * Gets the minimum key in this string table lookup. It reads it from file.
		 *
		 * @returns	The minimum key if some key/value pairs exists in this string table lookup, otherwise
		 * 			the int64_t maximum value.
		 */
		int64_t getMinimumValue();

		/**
		 * Gets the maximum key in this string table lookup. It reads it from file.
		 *
		 * @returns	The maximum key if some key/value pairs exists in this string table lookup, otherwise
		 * 			the int64_t minimum value.
		 */
		int64_t getMaximumValue();
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_CategoricalProperty) CategoricalProperty;
#endif
	class CategoricalProperty : public AbstractValuesProperty
	{
	public:
		DoubleTableLookup* getDoubleLookup();
		StringTableLookup* getStringLookup();
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_PointsProperty) PointsProperty;
#endif
	class PointsProperty : public RESQML2_NS::AbstractProperty
	{
	public:
		/**
		 * Get the xyz point count in a given patch of this property.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of range.
		 * @exception	std::logic_error 	If this representation is partial.
		 *
		 * @param 	patchIndex	Zero-based index of the patch from which we look for the xyz points.
		 *
		 * @returns	The xyz point count of the patch at position @p patchIndex.
		 */
		uint64_t getXyzPointCountOfPatch(unsigned int patchIndex) const;

		/**
		 * Get the xyz point count of all patches of this property.
		 *
		 * @returns	The xyz point count of all patches.
		 */
		uint64_t getXyzPointCountOfAllPatches() const;

		/**
		 * @brief	Gets all the xyz points of a particular patch of this property. xyz points are
		 * 			given in the local CRS.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of range.
		 * @exception	std::logic_error 	If this property is partial.
		 *
		 * @param 	   	patchIndex	Zero-based index of the patch from which we look for the xyz points.
		 * @param [out]	xyzPoints 	A linearized 2d array where the first (quickest) dimension is the
		 * 							coordinate dimension (x, y or z) and second dimension is vertex
		 * 							dimension. It must be preallocated with a size of <tt>3 *
		 * 							getXyzPointCountOfPatch(patchIndex)</tt>.
		 */
		void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const;

		/**
		 * @brief Gets all the xyz points of a particular patch of this property. xyz points are given in
		 * the global CRS.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of range.
		 *
		 * @param 	   	patchIndex	Zero-based index of the patch from which we look for the xyz points.
		 * @param [out]	xyzPoints 	A linearized 2d array where the first (quickest) dimension is the
		 * 							coordinate dimension (x, y or z) and second dimension is vertex
		 * 							dimension. It must be preallocated with a size of <tt>3 *
		 * 							getXyzPointCountOfPatch(patchIndex)</tt>.
		 */
		void getXyzPointsOfPatchInGlobalCrs(unsigned int patchIndex, double * xyzPoints) const;

		/**
		 * @brief Gets all the xyz points of all patches of this property. xyz points are given in the
		 * local CRS.
		 *
		 * @param [out]	xyzPoints	A linearized 2d array where the first (quickest) dimension is the
		 * 							coordinate dimension (x, y or z) and second dimension is vertex
		 * 							dimension. It must be preallocated with a size of <tt>3 *
		 * 							getXyzPointCountOfAllPatches()</tt>.
		 */
		void getXyzPointsOfAllPatches(double * xyzPoints) const;

		/**
		 * Gets all the xyz points of all patches of this property. xyz points are
		 * given in the global CRS.
		 *
		 * @param [out]	xyzPoints	A linearized 2d array where the first (quickest) dimension is the
		 * 							coordinate dimension (x, y or Z) and second dimension is vertex
		 * 							dimension. Thus, its size is 3*(3*[count of all xyz points]). It must
		 * 							be preallocated.
		 */
		void getXyzPointsOfAllPatchesInGlobalCrs(double * xyzPoints) const;

		/**
		 * @brief Adds a 1d array of points (in local CRS) to the property.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	xyzPoints		All the property values to set ordered according the topology
		 * 									of the representation it is based on.
		 * @param 		  	pointCount  	The number of points to write.
		 * @param [in,out]	proxy			(Optional) The HDF proxy where to write the property points.
		 * 									It must be already opened for writing and won't be closed in this
		 * 									method. If @c nullptr (default value), then a default HDF proxy
		 * 									must be defined in the repository.
		 */
		void pushBackArray1dOfXyzPoints(const double * xyzPoints, uint64_t pointCount, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief Adds a 2d array of points (in local CRS) to the property.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	xyzPoints				All the property values to set ordered according the
		 * 											topology of the representation it is based on.
		 * @param 		  	pointCountInFastestDim	The number of points to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	pointCountInSlowestDim	The number of points to write in the slowest
		 * 											dimension (mainly J dimension).
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											points. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default value), then a default HDF proxy must be
		 * 											defined in the repository.
		 */
		void pushBackArray2dOfXyzPoints(const double * xyzPoints, uint64_t pointCountInFastestDim, uint64_t pointCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief Adds a 3d array of points (in local CRS) to the property.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	xyzPoints				All the property values to set ordered according the
		 * 											topology of the representation it is based on.
		 * @param 		  	pointCountInFastestDim	The number of points to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	pointCountInMiddleDim 	The number of points to write in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	pointCountInSlowestDim	The number of points to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											points. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default value), then a default HDF proxy must be
		 * 											defined in the repository.
		 */
		void pushBackArray3dOfXyzPoints(const double * xyzPoints, uint64_t pointCountInFastestDim, uint64_t pointCountInMiddleDim, uint64_t pointCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief Adds an nd array of points (in local CRS) to the property.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	xyzPoints				All the property values to set ordered according the
		 * 											topology of the representation it is based on.
		 * @param 		  	pointCountByDimension	The number of property points ordered by dimension of the
		 * 											array to write.
		 * @param 		  	numArrayDimensions		The number of dimensions of the array to write.
		 * @param [in,out]	proxy			  		(Optional) The HDF proxy where to write the property
		 * 											points. It must be already opened for writing and won't
		 * 											be closed in this method. If @c nullptr (default value),
		 * 											then a default HDF proxy must be defined in the
		 * 											repository.
		 */
		void pushBackArrayOfXyzPoints(double const * xyzPoints, uint64_t const * pointCountByDimension, uint32_t numArrayDimensions, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Pushes back a reference to an existing (or a "to exist") HDF dataset in a particular HDF
		 * proxy. The reason can be that the values already exist in an external file (only HDF5 for
		 * now) or that the writing of the values in the external file is differed in time.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param [in]	proxy	   	The HDF5 proxy where the values are already or will be stored. If
		 * 							@c nullptr, then a default HDF proxy must be defined in the
		 * 							repository.
		 * @param 	  	datasetName	(Optional) The HDF5 dataset name where the values are stored. If
		 * 							empty, the dataset will be named the same as the dataset naming
		 * 							convention of fesapi :
		 * 							<tt>getHdfGroup() + "/points_patch" + patchIndex</tt>
		 *
		 * @returns	The name of the referenced HDF5 dataset.
		 */
		std::string pushBackRefToExistingDataset(EML2_NS::AbstractHdfProxy* proxy, const std::string & datasetName = "");
	};
	
	/************************************
	************** Well ****************
	************************************/
	
	class WellboreFrameRepresentation;
#ifdef SWIGPYTHON
	%rename(Resqml2_WellboreTrajectoryRepresentation) WellboreTrajectoryRepresentation;
#endif
	class  WellboreTrajectoryRepresentation : public AbstractRepresentation
	{
	public:
		/**
		 * Gets the count of wellbore frame representations which are associated with this wellbore
		 * trajectory.
		 *
		 * @returns	The count of associated wellbore frame representations.
		 */
		uint64_t getWellboreFrameRepresentationCount() const;
		
		/**
		 * Gets a particular wellbore frame representation of this wellbore trajectory representation
		 * according to its position in the repository.
		 * 
		 * @exception std::out_of_range If <tt>index >=</tt> getWellboreFrameRepresentationCount().
		 * 								
		 * @returns The associated wellbore frame representation at position @p index.
		 */
		WellboreFrameRepresentation* getWellboreFrameRepresentation(uint64_t index) const;
		
		/**
		 * Sets the minimal geometry of the representation by means of start and end MDs.
		 *
		 * @param 	startMd	The start MD of the trajectory. Uom is the same as the one for the associated
		 * 					MdDatum coordinates.
		 * @param 	endMd  	The end MD of the trajectory. Uom is the same as the one for the associated
		 * 					MdDatum coordinates.
		 */
		void setMinimalGeometry(double startMd, double endMd);

		/**
		 * Sets the geometry of the representation by means of a parametric line without MD information
		 * (only start and end MDs).
		 *
		 * @exception	std::invalid_argument	If @p controlPoints is @c nullptr.
		 * @exception	std::invalid_argument	If @p controlPointCount is 0.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If @p localCrs is @c nullptr and no default CRS is
		 * 										defined in the repository.
		 *
		 * @param [in]	  	controlPoints	 	All the control points of the cubic parametric line in
		 * 										the order of the MDs. Count is <tt>controlPointCount *
		 * 										3</tt> and for each control point <tt>(x,y,z) =
		 * 										(controlPoints[2i], controlPoints[2i+1],
		 * 										controlPoints[2i+2])</tt>.
		 * @param 		  	startMd			 	The start MD of the trajectory.
		 * @param 		  	endMd			 	The end MD of the trajectory.
		 * @param 		  	controlPointCount	The count of control points and control point parameters
		 * 										per cubic parametric line.
		 * @param 		  	lineKind		 	Integer indicating the parametric line kind: 0 for
		 * 										vertical, 1 for linear spline, 2 for natural cubic spline,
		 * 										3 for cubic spline, 4 for z linear cubic spline, 5 for
		 * 										minimum-curvature spline, (-1) for null: no line.
		 * @param [in,out]	proxy			 	(Optional) The HDF proxy which indicates in which HDF5
		 * 										file the control points and its parameters will be
		 * 										stored. It must be already opened for writing and won't
		 * 										be closed. If null, then the default HDF Proxy of the
		 * 										data object repository will be arbitrarily selected for
		 * 										writing.
		 * @param [in]	  	localCrs		 	(Optional) The local CRS where the control points are
		 * 										given. If @c nullptr (default), then the default Local
		 * 										CRS of the data object repository will be arbitrarily
		 * 										selected.
		 */
		void setGeometry(double const* controlPoints, double startMd, double endMd, uint64_t controlPointCount, int lineKind, EML2_NS::AbstractHdfProxy* proxy = nullptr, EML2_NS::AbstractLocal3dCrs* localCrs = nullptr);

		/**
		 * Sets the geometry of the representation by means of a parametric line with MD information.
		 *
		 * @exception	std::invalid_argument	If @p controlPoints is @c nullptr.
		 * @exception	std::invalid_argument	If @p controlPointParameters is @c nullptr.
		 * @exception	std::invalid_argument	If @p controlPointCount is 0.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If @p localCrs is @c nullptr and no default CRS is
		 * 										defined in the repository.
		 *
		 * @param [in]	  	controlPoints		  	All the control points of the cubic parametric line
		 * 											in the order of the MDs. Count is
		 * 											<tt>controlPointCount * 3</tt> and for each control
		 * 											point <tt>(x,y, z) = (controlPoints[2i],
		 * 											controlPoints[2i+1], controlPoints[2i+2])</tt>.
		 * @param [in]	  	controlPointParameters	The arrays of control point parameters (ordered
		 * 											regarding the control points). It corresponds to the
		 * 											MD values in a WellboreFeature context. Count is @p
		 * 											controlPointCount.
		 * @param 		  	controlPointCount	  	The count of control points and control point
		 * 											parameters per cubic parametric line.
		 * @param 		  	lineKind			  	Integer indicating the parametric line kind: 0 for
		 * 											vertical, 1 for linear spline, 2 for natural cubic
		 * 											spline, 3 for cubic spline, 4 for z linear cubic
		 * 											spline, 5 for minimum-curvature spline, (-1) for
		 * 											null: no line.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy which indicates in which
		 * 											HDF5 file the control points and its parameters will
		 * 											be stored. It must be already opened for writing and
		 * 											won't be closed. If null, then the default HDF Proxy
		 * 											of the DataObject repository will be arbitrarily
		 * 											selected for writing.
		 * @param [in]	  	localCrs			  	(Optional) The local CRS where the control points are
		 * 											given. If @c nullptr (default), then the default
		 * 											Local CRS of the DataObject repository will be
		 * 											arbitrarily selected.
		 */
		void setGeometry(double const* controlPoints, double const* controlPointParameters, uint64_t controlPointCount, int lineKind,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, EML2_NS::AbstractLocal3dCrs* localCrs = nullptr);

		/**
		 * Sets the geometry of the representation by means of a parametric line with MD and tangent
		 * vector information.
		 *
		 * @exception	std::invalid_argument	If @p controlPoints is @c nullptr.
		 * @exception	std::invalid_argument	If @p tangentVectors is @c nullptr.
		 * @exception	std::invalid_argument	If @p controlPointParameters is @c nullptr.
		 * @exception	std::invalid_argument	If @p controlPointCount is 0.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If @p localCrs is @c nullptr and no default CRS is
		 * 										defined in the repository.
		 *
		 * @param [in]	  	controlPoints		  	All the control points of the cubic parametric line
		 * 											in the ascending order of the MDs. Count is
		 * 											<tt>controlPointCount * 3</tt> and for each control
		 * 											point <tt>(x,y, z) = (controlPoints[2i],
		 * 											controlPoints[2i+1], controlPoints[2i+2])</tt>.
		 * @param [in]	  	tangentVectors		  	All the tangent vectors of all the control points of
		 * 											all the cubic parametric lines. They are ordered
		 * 											according to the control points. Count is
		 * 											<tt>controlPointCount * 3</tt> and for each tangent
		 * 											vector <tt>(u,v, w) = (tangentVectors[2i],
		 * 											tangentVectors[2i+1], tangentVectors[2i+2])</tt>.
		 * @param [in]	  	controlPointParameters	The arrays of control point parameters (ordered
		 * 											regarding the control points). It corresponds to the
		 * 											MD values in this context. Count is @p controlPointCount.
		 * @param 		  	controlPointCount	  	The count of control points and control point
		 * 											parameters and tangent vectors per cubic parametric
		 * 											line.
		 * @param 		  	lineKind			  	Integer indicating the parametric line kind: 0 for
		 * 											vertical, 1 for linear spline, 2 for natural cubic
		 * 											spline, 3 for cubic spline, 4 for z linear cubic
		 * 											spline, 5 for minimum-curvature spline, (-1) for
		 * 											null: no line.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy which indicates in which
		 * 											HDF5 file the parameters and the tangent vectors will
		 * 											be stored. It must be already opened for writing and
		 * 											won't be closed. If null, then the default HDF Proxy
		 * 											of the DataObject repository will be arbitrarily
		 * 											selected for writing.
		 * @param [in]	  	localCrs			  	(Optional) The local CRS where the control points are
		 * 											given. If @c nullptr, then the default Local CRS of
		 * 											the DataObject repository will be arbitrarily
		 * 											selected.
		 */
		void setGeometry(double const* controlPoints,
			double const* tangentVectors, double const* controlPointParameters, uint64_t controlPointCount, int lineKind,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, EML2_NS::AbstractLocal3dCrs* localCrs = nullptr);

		/**
		 * Sets the geometry of the representation by means of a parametric line with MD and tangent
		 * vector information.
		 *
		 * @exception	std::invalid_argument	If @p controlPoints is @c nullptr.
		 * @exception	std::invalid_argument	If @p tangentVectors is @c nullptr.
		 * @exception	std::invalid_argument	If @p controlPointParameters is @c nullptr.
		 * @exception	std::invalid_argument	If @p controlPointCount is 0.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If @p localCrs is @c nullptr and no default CRS is
		 * 										defined in the repository.
		 *
		 * @param [in]	  	controlPoints		  	All the control points of the cubic parametric line
		 * 											in the ascending order of the MDs. Count is
		 * 											<tt>controlPointCount * 3</tt> and for each control
		 * 											point <tt>(x,y, z) = (controlPoints[2i],
		 * 											controlPoints[2i+1], controlPoints[2i+2])</tt>.
		 * @param [in]	  	inclinations		  	All the inclinations (angle against vertical) in radians of all the trajectory stations
		 *											of the cubic parametric line. They are ordered
		 * 											according to the control points. Count is <tt>controlPointCount</tt>.
		 * @param [in]	  	azimuths			  	All the azimuths (clockwise angle against grid north) in radians of all the trajectory stations
		 *											of the cubic parametric line. They are ordered
		 * 											according to the control points. Count is <tt>controlPointCount</tt>.
		 * @param [in]	  	controlPointParameters	The arrays of control point parameters (ordered
		 * 											regarding the control points). It corresponds to the
		 * 											MD values in this context. Count is @p controlPointCount.
		 * @param 		  	controlPointCount	  	The count of control points and control point
		 * 											parameters and tangent vectors per cubic parametric
		 * 											line. Control points correspond to the trajectory stations.
		 * @param 		  	lineKind			  	Integer indicating the parametric line kind: 0 for
		 * 											vertical, 1 for linear spline, 2 for natural cubic
		 * 											spline, 3 for cubic spline, 4 for z linear cubic
		 * 											spline, 5 for minimum-curvature spline, (-1) for
		 * 											null: no line.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy which indicates in which
		 * 											HDF5 file the parameters and the tangent vectors will
		 * 											be stored. It must be already opened for writing and
		 * 											won't be closed. If null, then the default HDF Proxy
		 * 											of the DataObject repository will be arbitrarily
		 * 											selected for writing.
		 * @param [in]	  	localCrs			  	(Optional) The local CRS where the control points are
		 * 											given. If @c nullptr, then the default Local CRS of
		 * 											the DataObject repository will be arbitrarily
		 * 											selected.
		 */
		void setGeometry(double const* controlPoints,
			double const* inclinations, double const* azimuths, double const* controlPointParameters, uint64_t controlPointCount, int lineKind,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, EML2_NS::AbstractLocal3dCrs* localCrs = nullptr);
			
		/**
		 * Sets the MD datum of this trajectory.
		 *
		 * @exception	std::invalid_argument	If @p mdDatum is @c nullptr.
		 *
		 * @param [in]	mdDatum	The MD damtum to set to this trajectory. It cannot be null.
		 */
		void setMdDatum(MdDatum * mdDatum);
		
		/**
		 * Gets the MD information associated to this wellbore trajectory representation.
		 *
		 * @returns	The associated MD information.
		 */
		RESQML2_NS::MdDatum * getMdDatum() const;

		/**
		 * Queries if this trajectory has a geometry.
		 *
		 * @returns	True if this trajectory has a geometry, false if not.
		 */
		bool hasGeometry() const;
		
		/**
		 * Gets the geometry kind.
		 *
		 * @exception	std::logic_error 	If this trajectory has no geometry.
		 * @exception	std::logic_error 	If the geometry of this trajectory is not a parametric line.
		 * @exception	std::out_of_range	If the geometry kind index is not in the range <tt>[-1,
		 * 									5]</tt>.
		 *
		 * @returns	0 for vertical, 1 for linear spline, 2 for natural cubic spline, 3 for cubic spline,
		 * 			4 for z linear cubic spline, 5 for minimum-curvature spline, (-1) for null: no line.
		 */
		int getGeometryKind() const;

		/**
		 * Indicates if the wellbore trajectory has got tangent vectors attached to each trajectory
		 * station. Tangent vectors ussually transport inclination and azimuth of a trajectory station.
		 *
		 * @exception	std::logic_error	If the geometry of this trajectory is not a parametric line.
		 *
		 * @returns	True if there is some tangent vectors, false if not.
		 */
		bool hasTangentVectors() const;
		
		/**
		 * Gets the tangent vectors associated to each trajectory station of this trajectory.
		 *
		 * @exception	std::invalid_argument	If this trajectory has no tanget vector.
		 * @exception	std::invalid_argument	If the HDF proxy is missing.
		 *
		 * @param [out]	tangentVectors	A buffer for receiving the tangent vectors. It must be
		 * 								preallocated with size of <tt>3 * </tt>
		 * 								getXyzPointCountOfAllPatches(). It won't be freed by FESAPI.
		 */
		void getTangentVectors(double* tangentVectors);

		/**
		 * Gets the inclination (angle against vertical) and the azimuths (clockwise angle against grid north)
		 *both in radians for each trajectory station of this trajectory.
		 *
		 * @exception	std::invalid_argument	If this trajectory has no tangent vector.
		 * @exception	std::invalid_argument	If the HDF proxy is missing.
		 *
		 * @param [out]	inclinations	A buffer for receiving the inclinations. It must be
		 * 								preallocated with size getXyzPointCountOfAllPatches().
		 *								It won't be freed by FESAPI.
		 * @param [out]	azimuths		A buffer for receiving the azimuths. It must be
		 * 								preallocated with size getXyzPointCountOfAllPatches().
		 *								It won't be freed by FESAPI.
		 */
		void getInclinationsAndAzimuths(double * inclinations, double * azimuths);

		/**
		 * Indicates if the wellbore trajectory has got MD values attached to each trajectory station.
		 *
		 * @exception	std::logic_error	If the geometry of this trajectory is not a parametric line.
		 *
		 * @returns	True if there is some MD values, false if not.
		 */
		bool hasMdValues() const;
		
		/**
		 * Gets the unit of measure of the MDs along this trajectory.
		 *
		 * @returns	The unit of measure of the MDs along this trajectory.
		 */
		gsoap_resqml2_0_1::eml20__LengthUom getMdUom() const;

		/**
		 * Gets the unit of measure of the MDs along this trajectory as a string.
		 *
		 * @returns	The unit of measure of the MDs along this trajectory as a string.
		 */
		std::string getMdUomAsString() const;
		
		/**
		 * Gets the MD double values associated to each trajectory station of this trajectory.
		 *
		 * @exception	std::invalid_argument	If this trajectory has no MD value.
		 * @exception	std::invalid_argument	If the HDF proxy is missing.
		 * @exception	std::invalid_argument	If MD values are not defined using the right data
		 * 										structure.
		 *
		 * @param [out]	values	A buffer for receiving the MD values. It must be preallocated with size
		 * 						of getXyzPointCountOfAllPatches().
		 */
		void getMdValues(double* values) const;

		/**
		 * Converts an array MD values an array of corresponding XYZ values according to this trajectory.
		 *
		 * @param [in]	mdValues	An array containing all MD values we want to convert.
		 * @param [in]	mdCount		The count of MD values in @p mdValues
		 * @param [out]	xyzValues	A buffer for receiving the XYZ values converted from @p mdValues. It must be preallocated with a size of 3*mdCount.
		 */
		void convertMdValuesToXyzValues(double* mdValues, uint64_t mdCount, double* xyzValues) const;
		
		/**
		 * Gets the starting MD of this wellbore trajectory. Range may often be from kickoff to TD, but
		 * this is not necessary.
		 *
		 * @returns	The start MD.
		 */
		double getStartMd() const;

		/**
		 * Gets the ending MD of this wellbore trajectory. Range may often be from kickoff to TD, but
		 * this is not necessary.
		 *
		 * @returns	The end MD.
		 */
		double getFinishMd() const;
			
		void addParentTrajectory(double kickoffMd, double parentMd, WellboreTrajectoryRepresentation* parentTrajRep);
		WellboreTrajectoryRepresentation* getParentTrajectory() const;
		double getParentTrajectoryMd() const;
	};

#ifdef SWIGPYTHON
	%rename(Resqml2_WellboreFrameRepresentation) WellboreFrameRepresentation;
#endif
	class WellboreFrameRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:

		/**
		 * Sets the measured depth (MD) values of this wellbore frame representation as a 1d array of explicit values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	mdValues		All the MD values to set from top to bottom of the wellbore
		 * 									trajectory. Size if @p mdValueCount.
		 * @param 		  	mdValueCount	The MD values count.
		 * @param [in,out]	proxy			(Optional) The HDF proxy where to write the MD values. It
		 * 									must be already opened for writing and won't be closed in this
		 * 									method. If @c nullptr, then a default HDF proxy must be defined
		 * 									in the repository.
		 */
		void setMdValues(double const * mdValues, uint64_t mdValueCount, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Sets the measured depth (MD) values of this wellbore frame representation as a regular
		 * discretization along the wellbore trajectory.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @param 	firstMdValue		The first MD value.
		 * @param 	incrementMdValue	The increment value between two MDs.
		 * @param 	mdValueCount		The count of MD values in this wellbore frame representation.
		 */
		void setMdValues(double firstMdValue, double incrementMdValue, unsigned int mdValueCount);

		/**
		 * Indicates either the MDs are regularly spaced or not (useful for optimization). Does not
		 * check the regularity if the writer has used a generic array to store regular MDs.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @returns	True if MD values are regularly spaced, false if not.
		 */
		bool areMdValuesRegularlySpaced() const;

		/**
		 * Indicates the increment value between two MDs in case of regularly spaced MDs. Please check
		 * the regularity of MDs with areMdValuesRegularlySpaced() before using this method.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If the MD values are not regularly spaced.
		 *
		 * @returns	The MD constant increment value.
		 */
		double getMdConstantIncrementValue() const;

		/**
		 * Returns the first MD value of this wellbore frame representation.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the MD values are neither stored in a HDF5 double
		 * 										array nor in a double lattice array.
		 * @exception	std::invalid_argument	If the MD values are stored in a HDF5 double array and
		 * 										the HDF proxy is missing.
		 *
		 * @returns	The first MD value.
		 */
		double getMdFirstValue() const;

		/**
		 * Gets the number of MD values in this wellbore frame representation.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @returns	The MD values count.
		 */
		unsigned int getMdValuesCount() const;

		/**
		 * Gets the MD datatype in the HDF dataset.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If the MD values are stored in a HDF5 double array and
		 * 										the HDF proxy is missing.
		 *
		 * @returns	The MD datatype in the HDF dataset if MD values are actually stored in a HDF dataset.
		 * 			Returns @c DOUBLE if MD values are stored as a regular discretization along the
		 * 			wellbore trajectory.
		 */
		COMMON_NS::AbstractObject::numericalDatatypeEnum getMdHdfDatatype() const;

		/**
		 * Gets all the MD values of this instance which are supposed to be double ones.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the MD values are neither stored in a HDF5 double
		 * 										array nor in a double lattice array.
		 * @exception	std::invalid_argument	If the MD values are stored in a HDF5 double array and
		 * 										the HDF proxy is missing.
		 *
		 * @param [out]	values	A buffer to receive the MD values ordered from top to bottom of the
		 * 						wellbore trajectory. It must be preallocated with size of
		 * 						getMdValuesCount().
		 */
		void getMdAsDoubleValues(double * values) const;

		/**
		 * Gets all the MD values of this instance which are supposed to be float ones.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the MD values are neither stored in a HDF5 double
		 * 										array nor in a double lattice array.
		 * @exception	std::invalid_argument	If the MD values are stored in a HDF5 double array and
		 * 										the HDF proxy is missing.
		 *
		 * @param [out]	values	A buffer to receive the MD values ordered from top to bottom of the
		 * 						wellbore trajectory. It must be preallocated with size of
		 * 						getMdValuesCount().
		 */
		void getMdAsFloatValues(float * values) const;

		/** 
		 * Gets the associated RESQML wellbore trajectory. 
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * 
		 * @return The associated RESQML wellbore trajectory.
		 */
		WellboreTrajectoryRepresentation* getWellboreTrajectory() const;
	};
	
#if defined(SWIGPYTHON)
	%rename(Resqml2_SeismicWellboreFrameRepresentation) SeismicWellboreFrameRepresentation;
#endif
	class SeismicWellboreFrameRepresentation : public WellboreFrameRepresentation
	{
	public:
	
		/**
		* Set the time values of this SeismicWellboreFrameRepresentation frame to an array 1d of explicit values.
		* @param timeValues		All the time values to set from top of the well trajectory to bottom.
		* @param timeValueCount	The time values count. It must be the same that the md values count.
		* @param proxy			The HDF proxy where to write the time values. It must be already opened for writing and won't be closed in this method.
		*/
		void setTimeValues(double const * timeValues, uint64_t timeValueCount, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		* Set the time values of this WellboreFrameRepresentation frame as a regular discretization along the wellbore trajectory.
		* @param firstTimeValue		The first time value.
		* @param incrementTimeValue	The increment value between two time values. It must be the same that the md values count.
		* @param timeValueCount		The count of time values in this WellboreFrameRepresentation.
		*/
		void setTimeValues(double firstTimeValue, double incrementTimeValue, unsigned int timeValueCount);

		/**
		* Indicates either the times are regularly spaced or not (useful for optimization)
		* Does not verify if the writer has used a generic array to store regular times.
		*/
		bool areTimeValuesRegularlySpaced() const;

		/**
		* Indicates the increment value between two times only if the times are regularly spaced.
		* Please use areTimeValuesRegularlySpaced before using this method.
		*/
		double getTimeConstantIncrementValue() const;

		/**
		* Returns the first time value of this SeismicWellboreFrameRepresentation
		*/
		double getTimeFirstValue() const;

		/**
		* Get the number of time values in this seismic wellbore frame.
		*/
		unsigned int getTimeValuesCount() const;

		/**
		* Get the time values datatype in the HDF dataset
		*/
		COMMON_NS::AbstractObject::numericalDatatypeEnum getTimeHdfDatatype() const;

		/**
		* Get all the time values of the instance which are supposed to be double ones.
		*/
		void getTimeAsDoubleValues(double* values) const;

		/**
		* Get all the time values of the instance which are supposed to be float ones.
		*/
		void getTimeAsFloatValues(float* values) const;

		/**
		* Gets the Local Time CRS of this seismic wellbore frame.
		 * 
		 * @returns Local Time CRS of this seismic wellbore frame.
		*/
		EML2_NS::AbstractLocal3dCrs* getTimeCrs() const;

		/**
		* Returns the seismic reference datum
		*/
		double getSeismicReferenceDatum() const;

		/**
		* Returns the weathering velocity
		*/
		double getWeatheringVelocity() const;
	};

	/**
	 * @brief	A blocked wellbore representation. This is the information that allows you to locate,
	 * 			on one or several grids (existing or planned), the intersection of volume (cells) and
	 * 			surface (faces) elements with a wellbore trajectory (existing or planned).
	 */
#ifdef SWIGPYTHON
	%rename(Resqml2_BlockedWellboreRepresentation) BlockedWellboreRepresentation;
#endif
	class BlockedWellboreRepresentation : public RESQML2_NS::WellboreFrameRepresentation
	{
	public:
		/**
		 * Sets all information about the intersected grid cells. You must first provide MD values of
		 * the frame before to use this method.
		 *
		 * @exception	std::invalid_argument	If @p gridIndices, @p cellIndices, @p
		 * 										localFacePairPerCellIndices or @p hdfProxy is @c nullptr.
		 * @exception	std::logic_error	 	If MD values of the frame have not been provided before
		 * 										using this method.
		 *
		 * @param 		  	gridIndices								An array containing for each interval
		 * 															of the wellbore frame, the index of the
		 * 															grid it is associated to. The size of
		 * 															this array is the interval count of the
		 * 															wellbore frame representation. @p
		 * 															cellCount must equal the number of non-
		 * 															null entries in this array. The
		 * 															associated grids (and there indices) are
		 * 															defined using
		 * 															pushBackSupportingGridRepresentation()
		 * 															method.
		 * @param 		  	gridIndicesNullValue					The null value used in @p gridIndices
		 * 															in order to indicate that an interval
		 * 															does not correspond to any intersected
		 * 															grid. Generally -1.
		 * @param 		  	cellIndices								An array containing the intersected
		 * 															cell index for each entry in @p gridIndices.
		 * 															The size of this array is the interval count of the
		 * 															wellbore frame representation.
		 *															The null value will be set to @p gridIndicesNullValue
		 *															already informs about the presence or not of a cell.
		 * @param 		  	localFacePairPerCellIndices				An array containing, for each cell,
		 * 															the entry and exit intersection faces of
		 * 															the trajectory in the cell. The array
		 * 															dimension must equal <tt>2 *
		 * 															intervalCount</tt>.
		 * @param 		  	localFacePairPerCellIndicesNullValue	The null value used in @p
		 * 															localFacePerCellIndices in order to
		 * 															indicate that it corresponds to a missing
		 * 															intersection, e.g., when a trajectory
		 * 															originates or terminates within a cell.
		 * @param [in,out]	hdfProxy								The HDF proxy where the numerical
		 * 															values will be stored. If set to nullptr,
		 *															the default HdfProxy will be used instead.
		 */
		void setIntervalGridCells(int8_t const* gridIndices, int8_t gridIndicesNullValue, int64_t const* cellIndices,
			int8_t const* localFacePairPerCellIndices, int8_t localFacePairPerCellIndicesNullValue, EML2_NS::AbstractHdfProxy * hdfProxy = nullptr);

		/**
		 * Gets the cell count, that is to say the number of non-null entries in the grid indices array.
		 *
		 * @returns	The cell count.
		 */
		uint64_t getCellCount() const;

		/**
		 * For each interval of the wellbore frame, gets the index of the grid it is associated to.
		 *
		 * @exception	std::range_error	If the grid indices are stored in an integer constant array
		 * 									and if the the constant value is strictly superior than unsigned
		 * 									int maximum value.
		 * @exception	std::logic_error	If the grid indices are neither stored in a HDF5 integer
		 * 									array nor in an integer constant array.
		 *
		 * @param [out]	gridIndices	An array for receiving the grids indices. The size of this array is
		 * 							the interval count of the wellbore frame representation. The
		 * 							associated grids (and there indices) are defined using
		 * 							pushBackSupportingGridRepresentation() method.
		 *
		 * @returns	The null value used in @p gridIndices in order to indicate that an interval does not
		 * 			correspond to any intersected grid.
		 */
		int8_t getGridIndices(int8_t * gridIndices) const;

		/**
		 * For each interval of the wellbore frame, gets the index of the cell it is associated to.
		 *
		 * @exception	std::range_error	If the cell indices are stored in an integer constant array
		 * 									and if the the constant value is strictly superior than
		 * 									int64_t maximum value.
		 * @exception	std::logic_error	If the cell indices are neither stored in a HDF5 integer
		 * 									array nor in an integer constant array.
		 *
		 * @param [out]	gridIndices	An array for receiving the cell indices. The size of this array is
		 * 							the interval count of the wellbore frame representation.
		 *
		 * @returns	The null value used in @p cellIndices in order to indicate that an interval does not
		 * 			correspond to any intersected cell.
		 */
		int64_t getCellIndices(int64_t* cellIndices) const;

		/**
		 * For each interval of the wellbore frame, gets the index of the entry and exit local face it is associated to.
		 *
		 * @exception	std::range_error	If the local face indices are stored in an integer constant array
		 * 									and if the the constant value is strictly superior than
		 * 									char maximum value.
		 * @exception	std::logic_error	If the local face indices are neither stored in a HDF5 integer
		 * 									array nor in an integer constant array.
		 *
		 * @param [out]	gridIndices	An array for receiving the local face indices. The size of this array is twice
		 * 							the interval count of the wellbore frame representation.
		 *
		 * @returns	The null value used in @p localFacePairPerCellIndices in order to indicate that no face is intersected.
		 */
		int8_t getLocalFacePairPerCellIndices(int8_t* localFacePairPerCellIndices) const;

		/**
		 * Pushes back a grid representation which is one of the support of this representation.
		 *
		 * @exception	std::invalid_argument	If <tt>supportingGridRep == nullptr</tt>.
		 *
		 * @param [in]	supportingGridRep	The supporting grid representation to push back.
		 */
		void pushBackSupportingGridRepresentation(RESQML2_NS::AbstractGridRepresentation * supportingGridRep);

		/**
		 * Gets the count of supporting grid representations of this blocked wellbore representation.
		 *
		 * @exception	std::range_error	If the count of supporting grid representations is strictly
		 * 									greater than unsigned int max.
		 *
		 * @returns	The count of supporting grid representation.
		 */
		uint64_t getSupportingGridRepresentationCount() const;

		/**
		 * Gets the supporting grid representation located at a specific index of this blocked wellbore
		 * representation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt>
		 * 									getSupportingGridRepresentationCount().
		 *
		 * @param 	index	Zero-based index of the supporting grid representation we look for.
		 *
		 * @returns	The supporting grid representation at position @p index.
		 */
		RESQML2_NS::AbstractGridRepresentation* getSupportingGridRepresentation(uint64_t index) const;
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_WellboreMarkerFrameRepresentation) WellboreMarkerFrameRepresentation;
#endif
	class WellboreMarkerFrameRepresentation : public WellboreFrameRepresentation
	{
	public:		
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::WellboreMarker, WellboreMarker)
		void setIntervalStratigraphicUnits(unsigned int * stratiUnitIndices, unsigned int nullValue, class StratigraphicOccurrenceInterpretation* stratiOccurrenceInterp, EML2_NS::AbstractHdfProxy* proxy);
		StratigraphicOccurrenceInterpretation* getStratigraphicOccurrenceInterpretation();
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_WellboreMarker) WellboreMarker;
#endif
	class WellboreMarker : public COMMON_NS::AbstractObject
	{
	public:
		bool hasAGeologicBoundaryKind() const;
		gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind getGeologicBoundaryKind() const;
		WellboreMarkerFrameRepresentation const * getWellboreMarkerFrameRepresentation() const;
		BoundaryFeatureInterpretation* getBoundaryFeatureInterpretation() const;
		void setBoundaryFeatureInterpretation(BoundaryFeatureInterpretation* interp);
		WITSML2_1_NS::WellboreMarker* getWitsmlWellboreMarker() const;
		void setWitsmlWellboreMarker(WITSML2_1_NS::WellboreMarker * wellboreMarker);
		bool hasDipAngle() const;
		double getDipAngleValue() const;
		gsoap_eml2_3::eml23__PlaneAngleUom getDipAngleUom() const;
		std::string getDipAngleUomAsString() const;
		bool hasDipDirection() const;
		double getDipDirectionValue() const;
		gsoap_eml2_3::eml23__PlaneAngleUom getDipDirectionUom() const;
		std::string getDipDirectionUomAsString() const;
	};
}

%include "swigResqml2_0_1Include.i"
#ifdef WITH_RESQML2_2
%include "swigResqml2_2Include.i"
#endif
