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
	%nspace RESQML2_NS::AbstractLocal3dCrs;
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
	%nspace RESQML2_NS::DeviationSurveyRepresentation;
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
	%nspace RESQML2_NS::LocalDepth3dCrs;
	%nspace RESQML2_NS::LocalTime3dCrs;
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
	%nspace RESQML2_NS::GeologicUnitOccurrenceInterpretation;
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
	enum class resqml22__TimeSetKind {
		single_x0020time = 0,
		single_x0020time_x0020series = 1,
		equivalent_x0020times = 2,
		not_x0020a_x0020time_x0020set = 3
	};
	enum class eml23__WellboreDatumReference {
		ground_x0020level = 0,
		kelly_x0020bushing = 1,
		mean_x0020sea_x0020level = 2,
		derrick_x0020floor = 3,
		casing_x0020flange = 4,
		crown_x0020valve = 5,
		rotary_x0020bushing = 6,
		rotary_x0020table = 7,
		sea_x0020floor = 8,
		lowest_x0020astronomical_x0020tide = 9,
		mean_x0020higher_x0020high_x0020water = 10,
		mean_x0020high_x0020water = 11,
		mean_x0020lower_x0020low_x0020water = 12,
		mean_x0020low_x0020water = 13,
		mean_x0020tide_x0020level = 14,
		kickoff_x0020point = 15
	};
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
		interrupts = 1,
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
		contouring = 9,
		pillar = 10,
		break_x0020line = 11
	};
	enum class resqml22__IndexableElement {
		cells = 0,
		intervals_x0020from_x0020datum = 1,
		column_x0020edges = 2,
		columns = 3,
		contacts = 4,
		coordinate_x0020lines = 5,
		edges = 6,
		edges_x0020per_x0020column = 7,
		enumerated_x0020elements = 8,
		faces = 9,
		faces_x0020per_x0020cell = 10,
		interval_x0020edges = 11,
		intervals = 12,
		I0 = 13,
		I0_x0020edges = 14,
		J0 = 15,
		J0_x0020edges = 16,
		layers = 17,
		lines = 18,
		nodes = 19,
		nodes_x0020per_x0020cell = 20,
		nodes_x0020per_x0020edge = 21,
		nodes_x0020per_x0020face = 22,
		patches = 23,
		pillars = 24,
		regions = 25,
		representation = 26,
		subnodes = 27,
		triangles = 28
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
	%rename(resqml2_AbstractColorMap) AbstractColorMap;
#endif
	class AbstractColorMap : public COMMON_NS::AbstractObject
	{
	public:
		void setRgbColors(unsigned int colorCount,
			double const* rgbColors, double const* alphas = nullptr, std::vector<std::string> const& colorTitles = std::vector<std::string>(),
			double const* indices = nullptr);
		void setRgbColors(unsigned int colorCount,
			unsigned int const* rgbColors, double const* alphas = nullptr, std::vector<std::string> const& colorTitles = std::vector<std::string>(),
			double const* indices = nullptr);

		double getHue(double colorIndex) const;
		double getSaturation(double colorIndex) const;
		double getValue(double colorIndex) const;
		double getAlpha(double colorIndex) const;
		
		void getRgbColor(double colorIndex, double& red, double& green, double& blue) const;
		void getRgbColor(double colorIndex, unsigned int& red, unsigned int& green, unsigned int& blue) const;

		bool hasColorTitle(double colorIndex) const;
		std::string getColorTitle(double colorIndex) const;
	};
	
#if defined(SWIGPYTHON)
	%rename(resqml2_DiscreteColorMap) DiscreteColorMap;
#endif	
	class DiscreteColorMap : public AbstractColorMap
	{
	public:
		void setHsvColors(unsigned int colorCount, 
			double const * hsvColors, double const * alphas = nullptr, std::vector<std::string> const& colorTitles = std::vector<std::string>(),
			double const * indices = nullptr);

		unsigned int getColorCount() const;
	};
	
#if defined(SWIGPYTHON)
	%rename(resqml2_ContinuousColorMap) ContinuousColorMap;
#endif	
	class ContinuousColorMap : public AbstractColorMap 
	{
	public:
		void setHsvColors(unsigned int colorCount,
			double const* hsvColors, double const* alphas = nullptr, std::vector<std::string> const& colorTitles = std::vector<std::string>(),
			double const* indices = nullptr);

		unsigned int getColorCount() const;

		gsoap_eml2_3::resqml22__InterpolationDomain getInterpolationDomain();
		std::string getInterpolationDomainAsString();

		gsoap_eml2_3::resqml22__InterpolationMethod getInterpolationMethod();
		std::string getInterpolationMethodAsString();

		void setNanHsvColor(double hue, double saturation, double value, double alpha = 1, std::string const& colorTitle = "");
		void setNanRgbColor(double red, double green, double blue, double alpha = 1, std::string const& colorTitle = "");
		void setNanRgbColor(unsigned int red, unsigned int green, unsigned int blue, double alpha = 1, std::string const& colorTitle = "");
	};
	
#if defined(SWIGPYTHON)
	%rename(resqml2_AbstractLocal3dCrs) AbstractLocal3dCrs;
#endif	
	class AbstractLocal3dCrs : public COMMON_NS::AbstractObject
	{
	public:
		double getOriginOrdinal1() const;
		double getOriginOrdinal2() const;
		double getOriginDepthOrElevation() const;
		double getArealRotation() const;
		bool isDepthOriented() const;
		
		bool isProjectedCrsDefinedWithEpsg() const;
		bool isProjectedCrsUnknown() const;
		const std::string & getProjectedCrsUnknownReason() const;
		unsigned long long getProjectedCrsEpsgCode() const;
		
		bool isVerticalCrsDefinedWithEpsg() const;
		bool isVerticalCrsUnknown() const;
		const std::string & getVerticalCrsUnknownReason() const;
		unsigned long long getVerticalCrsEpsgCode() const;

		gsoap_resqml2_0_1::eml20__LengthUom getProjectedCrsUnit() const;
		std::string getProjectedCrsUnitAsString() const;
		gsoap_resqml2_0_1::eml20__LengthUom getVerticalCrsUnit() const;
		std::string getVerticalCrsUnitAsString() const;
		
		gsoap_resqml2_0_1::eml20__AxisOrder2d getAxisOrder() const;
		void setAxisOrder(gsoap_resqml2_0_1::eml20__AxisOrder2d axisOrder) const;
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_LocalDepth3dCrs) LocalDepth3dCrs;
#endif
	class LocalDepth3dCrs : public AbstractLocal3dCrs
	{
	public:
	};

#ifdef SWIGPYTHON
	%rename(resqml2_LocalTime3dCrs) LocalTime3dCrs;
#endif
	class LocalTime3dCrs : public AbstractLocal3dCrs
	{
	public:
		gsoap_resqml2_0_1::eml20__TimeUom getUnit() const;
		std::string getUnitAsString() const;
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_MdDatum) LocalTime3dCrs;
#endif
	class MdDatum : public COMMON_NS::AbstractObject
	{
	public:
		AbstractLocal3dCrs * getLocalCrs() const;

		virtual double getX() const = 0;
		virtual double getXInGlobalCrs() const = 0;
		virtual double getY() const = 0;
		virtual double getYInGlobalCrs() const = 0;
		virtual double getZ() const = 0;
		virtual double getZInGlobalCrs() const = 0;
		
		gsoap_eml2_3::eml23__WellboreDatumReference getOriginKind() const;
	};

	class AbstractFeatureInterpretation;
#ifdef SWIGPYTHON
	%rename(resqml2_AbstractFeature) AbstractFeature;
#endif
	class AbstractFeature : public COMMON_NS::AbstractObject
	{
	public:
		unsigned int getInterpretationCount() const;
		AbstractFeatureInterpretation* getInterpretation(unsigned int index) const;
	};

#ifdef SWIGPYTHON
	%rename(resqml2_AbstractTechnicalFeature) AbstractTechnicalFeature;
#endif
	class AbstractTechnicalFeature : public AbstractFeature
	{
	};

#ifdef SWIGPYTHON
	%rename(resqml2_BoundaryFeature) BoundaryFeature;
#endif	
	class BoundaryFeature : public AbstractFeature
	{
	};
	

#ifdef SWIGPYTHON
	%rename(resqml2_CulturalFeature) CulturalFeature;
#endif	
	class CulturalFeature : public AbstractTechnicalFeature
	{
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_Model) Model;
#endif	
	class Model : public AbstractFeature
	{
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_RockVolumeFeature) RockVolumeFeature;
#endif	
	class RockVolumeFeature : public AbstractFeature
	{
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_SeismicLatticeFeature) SeismicLatticeFeature;
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
	%rename(resqml2_SeismicLineSetFeature) SeismicLineSetFeature;
#endif
	class SeismicLineSetFeature : public AbstractTechnicalFeature
	{
	};

#ifdef SWIGPYTHON
	%rename(resqml2_AbstractSeismicLineFeature) AbstractSeismicLineFeature;
#endif	
	class AbstractSeismicLineFeature : public AbstractTechnicalFeature
	{
	public:
		void setSeismicLineSet(SeismicLineSetFeature * seisLineSet);
		SeismicLineSetFeature* getSeismicLineSet() const;
		
		unsigned int getTraceCount() const;
		
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
	%rename(resqml2_WellboreFeature) WellboreFeature;
#endif
	class WellboreFeature : public AbstractTechnicalFeature
	{
	public:
		WITSML2_0_NS::Wellbore* getWitsmlWellbore();
		void setWitsmlWellbore(WITSML2_0_NS::Wellbore * wellbore);
	};

	class AbstractRepresentation;
	class AbstractFeatureInterpretation : public COMMON_NS::AbstractObject
	{
	public:
		unsigned int						getRepresentationCount() const;
		AbstractFeature*				getInterpretedFeature();
		AbstractRepresentation* 	getRepresentation(unsigned int index) const;
		
		gsoap_resqml2_0_1::resqml20__Domain initDomain(gsoap_resqml2_0_1::resqml20__Domain defaultDomain) const;
		gsoap_resqml2_0_1::resqml20__Domain getDomain() const;
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_GenericFeatureInterpretation) GenericFeatureInterpretation;
#endif
	class GenericFeatureInterpretation : public AbstractFeatureInterpretation
	{
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_BoundaryFeatureInterpretation) BoundaryFeatureInterpretation;
#endif
	class BoundaryFeatureInterpretation : public AbstractFeatureInterpretation
	{
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_GeobodyBoundaryInterpretation) GeobodyBoundaryInterpretation;
#endif
	class GeobodyBoundaryInterpretation : public BoundaryFeatureInterpretation
	{
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_HorizonInterpretation) HorizonInterpretation;
#endif
	class HorizonInterpretation : public BoundaryFeatureInterpretation
	{
	};

#ifdef SWIGPYTHON
	%rename(resqml2_FaultInterpretation) FaultInterpretation;
#endif
	class FaultInterpretation : public BoundaryFeatureInterpretation
	{
	public:
	};

#ifdef SWIGPYTHON
	%rename(resqml2_FluidBoundaryInterpretation) FluidBoundaryInterpretation;
#endif
	class FluidBoundaryInterpretation : public BoundaryFeatureInterpretation
	{
	public:
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_GeobodyInterpretation) GeobodyInterpretation;
#endif
	class GeobodyInterpretation : public AbstractFeatureInterpretation
	{
	public :
		void set3dShape(gsoap_eml2_3::resqml22__Shape3d geobody3dShape);
		bool has3dShape() const;
		gsoap_eml2_3::resqml22__Shape3d get3dShape() const;
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_StratigraphicUnitInterpretation) StratigraphicUnitInterpretation;
#endif
	class StratigraphicUnitInterpretation : public AbstractFeatureInterpretation
	{
	public:
		bool hasDepositionMode() const;
		gsoap_resqml2_0_1::resqml20__DepositionMode getDepositionMode() const;
	};
	
	#ifdef SWIGPYTHON
	%rename(resqml2_AbstractOrganizationInterpretation) AbstractOrganizationInterpretation;
	#endif
	class AbstractOrganizationInterpretation : public AbstractFeatureInterpretation
	{
	public:
		/**
		* Indicates if this instance is a structural one.
		*/
		virtual bool isStructural() const;

		/**
		* Indicates if this instance is a structural one.
		*/
		virtual bool isStratigraphic() const;

		/**
		* Indicates if this instance is a structural one.
		*/
		virtual bool isRockFluid() const;
		
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
	%rename(resqml2_AbstractStratigraphicOrganizationInterpretation) AbstractStratigraphicOrganizationInterpretation;
	#endif
	class AbstractGridRepresentation;
	class AbstractStratigraphicOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	public:
		unsigned int getGridRepresentationCount() const;
		AbstractGridRepresentation* getGridRepresentation(unsigned int index) const;
		bool isAssociatedToGridRepresentation(AbstractGridRepresentation* gridRep) const;
	};
	
	class GeologicUnitOccurrenceInterpretation;	
#ifdef SWIGPYTHON
	%rename(resqml2_StratigraphicColumnRankInterpretation) StratigraphicColumnRankInterpretation;
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
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::GeologicUnitOccurrenceInterpretation, GeologicUnitOccurrenceInterpretation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::HorizonInterpretation, HorizonInterpretation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::StratigraphicColumn, StratigraphicColumn)
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_GeologicUnitOccurrenceInterpretation) GeologicUnitOccurrenceInterpretation;
#endif
	class GeologicUnitOccurrenceInterpretation : public AbstractStratigraphicOrganizationInterpretation
	{
	public:
		void setStratigraphicColumnRankInterpretation(StratigraphicColumnRankInterpretation * stratiColumnRankInterp);
		StratigraphicColumnRankInterpretation * getStratigraphicColumnRankInterpretation() const;
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::WellboreMarkerFrameRepresentation, WellboreMarkerFrameRepresentation)
	};

#ifdef SWIGPYTHON
	%rename(resqml2_StratigraphicColumn) StratigraphicColumn;
#endif
	class StratigraphicColumn : public COMMON_NS::AbstractObject
	{
	public:
		void pushBackStratiColumnRank(StratigraphicColumnRankInterpretation * stratiColumnRank);
		unsigned int getStratigraphicColumnRankInterpretationCount() const;
		StratigraphicColumnRankInterpretation* getStratigraphicColumnRankInterpretation(unsigned int index) const;
	};

#ifdef SWIGPYTHON
	%rename(resqml2_RockFluidUnitInterpretation) RockFluidUnitInterpretation;
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
	%rename(resqml2_RockFluidOrganizationInterpretation) RockFluidOrganizationInterpretation;
#endif
	class RockFluidOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	public:
		AbstractGridRepresentation* getGridRepresentation(unsigned int index) const;
		bool isAssociatedToGridRepresentation(AbstractGridRepresentation* gridRep) const;
		void pushBackRockFluidUnitInterpretation(RockFluidUnitInterpretation* rockFluidUnitInterpretation) = 0;
		unsigned int getRockFluidUnitInterpCount() const = 0;
		RockFluidUnitInterpretation* getRockFluidUnitInterpretation(unsigned int index) const;
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_StructuralOrganizationInterpretation) StructuralOrganizationInterpretation;
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
	%rename(resqml2_EarthModelInterpretation) EarthModelInterpretation;
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
		
		unsigned int getGeologicUnitOccurrenceCount() const;
		GeologicUnitOccurrenceInterpretation* getGeologicUnitOccurrence(unsigned int index) const;
		void pushBackGeologicUnitOccurrence(GeologicUnitOccurrenceInterpretation * occurence);
		
		unsigned int getRockFluidOrganizationInterpretationCount() const;
		void pushBackRockFluidOrganizationInterpretation(RockFluidOrganizationInterpretation* rockFluid);
		RockFluidOrganizationInterpretation* getRockFluidOrganizationInterpretation(unsigned int index) const;
	};

#ifdef SWIGPYTHON
	%rename(resqml2_WellboreInterpretation) WellboreInterpretation;
#endif
	class WellboreInterpretation : public AbstractFeatureInterpretation
	{
	public:
		bool isDrilled() const;
	};

	//************************************/
	//************ REPRESENTATION ********/
	//************************************/
	
	class AbstractValuesProperty;
	class PointsProperty;
	class RepresentationSetRepresentation;
	class SubRepresentation;
#ifdef SWIGPYTHON
	%rename(resqml2_AbstractRepresentation) AbstractRepresentation;
#endif
	class AbstractRepresentation : public COMMON_NS::AbstractObject
	{
	public:

		enum indexableElement { NODE = 0, EDGE = 1, FACE = 2, VOLUME = 3, PILLAR = 4 };
		
		AbstractFeatureInterpretation* getInterpretation() const;
		AbstractLocal3dCrs * getLocalCrs(unsigned int patchIndex);
		
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::AbstractValuesProperty, ValuesProperty)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PointsProperty, PointsProperty)
		
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::SubRepresentation, SubRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::SubRepresentation, FaultSubRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::RepresentationSetRepresentation, RepresentationSetRepresentation)

		virtual uint64_t getXyzPointCountOfPatch(unsigned int patchIndex) const = 0;
		uint64_t getXyzPointCountOfAllPatches() const;
		void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const;
		void getXyzPointsOfPatchInGlobalCrs(unsigned int patchIndex, double * xyzPoints) const;
		void getXyzPointsOfAllPatches(double * xyzPoints) const;
		bool isInSingleLocalCrs() const;
		bool isInSingleGlobalCrs() const;
		void getXyzPointsOfAllPatchesInGlobalCrs(double * xyzPoints) const;
		virtual unsigned int getPatchCount() const;
		
		AbstractRepresentation* getSeismicSupportOfPatch(unsigned int patchIndex);
		void getSeismicLineAbscissaOfPointsOfPatch(unsigned int patchIndex, double* values) const;
		void addSeismic2dCoordinatesToPatch(unsigned int patchIndex, double * lineAbscissa,
			AbstractRepresentation * seismicSupport, EML2_NS::AbstractHdfProxy * proxy);
		void getInlinesOfPointsOfPatch(unsigned int patchIndex, double * values) const;
		void getCrosslinesOfPointsOfPatch(unsigned int patchIndex, double * values) const;
		void addSeismic3dCoordinatesToPatch(unsigned int patchIndex, double * inlines, double * crosslines, unsigned int pointCount,
			AbstractRepresentation * seismicSupport, EML2_NS::AbstractHdfProxy * proxy);
		void addSeismic3dCoordinatesToPatch(unsigned int patchIndex, double startInline, double incrInline, unsigned int countInline,
			double startCrossline, double incrCrossline, unsigned int countCrossline,
			AbstractRepresentation * seismicSupport);

		void pushBackIntoRepresentationSet(RepresentationSetRepresentation * repSet);
	};
	
	class PolylineRepresentation;	
#ifdef SWIGPYTHON
	%rename(resqml2_AbstractSurfaceRepresentation) AbstractSurfaceRepresentation;
#endif
	class AbstractSurfaceRepresentation : public AbstractRepresentation
	{
	public:
		void setSurfaceRole(gsoap_resqml2_0_1::resqml20__SurfaceRole surfaceRole);
		gsoap_resqml2_0_1::resqml20__SurfaceRole getSurfaceRole() const;
		void pushBackOuterRing(PolylineRepresentation * outerRing);
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_Grid2dRepresentation) Grid2dRepresentation;
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
		
		int getIndexOriginOnSupportingRepresentation() const;
		int getIndexOriginOnSupportingRepresentation(unsigned int dimension) const;
		int getNodeCountOnSupportingRepresentation(unsigned int dimension) const;
		int getIndexOffsetOnSupportingRepresentation(unsigned int dimension) const;
		
		void setGeometryAsArray2dOfLatticePoints3d(
			unsigned int numPointsInFastestDirection, unsigned int numPointsInSlowestDirection,
			double xOrigin, double yOrigin, double zOrigin,
			double xOffsetInFastestDirection, double yOffsetInFastestDirection, double zOffsetInFastestDirection,
			double xOffsetInSlowestDirection, double yOffsetInSlowestDirection, double zOffsetInSlowestDirection,
			double spacingInFastestDirection, double spacingInSlowestDirection, AbstractLocal3dCrs * localCrs = nullptr);

		void setGeometryAsArray2dOfExplicitZ(
			double * zValues,
			unsigned int numI, unsigned int numJ, EML2_NS::AbstractHdfProxy* proxy,
			Grid2dRepresentation * supportingGrid2dRepresentation, AbstractLocal3dCrs * localCrs = nullptr,
			unsigned int startIndexI = 0, unsigned int startIndexJ = 0,
			int indexIncrementI = 1, int indexIncrementJ = 1);

		void setGeometryAsArray2dOfExplicitZ(
			double * zValues,
			unsigned int numI, unsigned int numJ, EML2_NS::AbstractHdfProxy* proxy,
			double originX, double originY, double originZ,
			double offsetIX, double offsetIY, double offsetIZ, double spacingI,
			double offsetJX, double offsetJY, double offsetJZ, double spacingJ, AbstractLocal3dCrs * localCrs = nullptr);
		
		Grid2dRepresentation*  getSupportingRepresentation();
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_PolylineSetRepresentation) PolylineSetRepresentation;
#endif
	class PolylineSetRepresentation : public AbstractRepresentation
	{
	public:
		unsigned int getPolylineCountOfPatch(unsigned int patchIndex) const;
		unsigned int getPolylineCountOfAllPatches() const;
		void getNodeCountPerPolylineInPatch(unsigned int patchIndex, unsigned int * nodeCountPerPolyline) const;
		void getNodeCountPerPolylineOfAllPatches(unsigned int * nodeCountPerPolyline) const;
		void pushBackGeometryPatch(
			unsigned int * nodeCountPerPolyline, double * nodes,
			unsigned int polylineCount, bool allPolylinesClosedFlag,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, AbstractLocal3dCrs* localCrs = nullptr);

		void pushBackGeometryPatch(
			unsigned int * nodeCountPerPolyline, double * nodes,
			unsigned int polylineCount, bool * polylineClosedFlags,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, AbstractLocal3dCrs* localCrs = nullptr);
				
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
	%rename(resqml2_PointSetRepresentation) PointSetRepresentation;
#endif
	class PointSetRepresentation : public AbstractRepresentation
	{
	public:
		void pushBackGeometryPatch(
			unsigned int xyzPointCount, double * xyzPoints,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, AbstractLocal3dCrs * localCrs = nullptr);
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_PlaneSetRepresentation) PlaneSetRepresentation;
#endif
	class PlaneSetRepresentation : public AbstractRepresentation
	{
	public:
		void pushBackHorizontalPlaneGeometryPatch(double zCoordinate, AbstractLocal3dCrs* localCrs = nullptr);

		void pushBackTiltedPlaneGeometryPatch(
			double x1, double y1, double z1,
			double x2, double y2, double z2,
			double x3, double y3, double z3,
			AbstractLocal3dCrs* localCrs = nullptr);
	};

#ifdef SWIGPYTHON
	%rename(resqml2_PolylineRepresentation) PolylineRepresentation;
#endif
	class PolylineRepresentation : public AbstractRepresentation
	{
	public:
		void setGeometry(double * points, unsigned int pointCount, EML2_NS::AbstractHdfProxy* proxy = nullptr, AbstractLocal3dCrs* localCrs = nullptr);
		bool isClosed() const;
		bool hasALineRole() const;
		gsoap_eml2_3::resqml22__LineRole getLineRole() const;
		void setLineRole(gsoap_eml2_3::resqml22__LineRole lineRole);
	};

#ifdef SWIGPYTHON
	%rename(resqml2_TriangulatedSetRepresentation) TriangulatedSetRepresentation;
#endif
	class TriangulatedSetRepresentation : public AbstractSurfaceRepresentation
	{
	public:
		unsigned int getTriangleCountOfPatch(unsigned int patchIndex) const;
		unsigned int getTriangleCountOfAllPatches() const;
		void getTriangleNodeIndicesOfPatch(unsigned int patchIndex, unsigned int * triangleNodeIndices) const;
		void getTriangleNodeIndicesOfAllPatches(unsigned int * triangleNodeIndices) const;
		void pushBackTrianglePatch(unsigned int nodeCount, double * nodes, unsigned int triangleCount, unsigned int * triangleNodeIndices, EML2_NS::AbstractHdfProxy* proxy = nullptr, AbstractLocal3dCrs* localCrs = nullptr);
	};

#ifdef SWIGPYTHON
	%rename(resqml2_RepresentationSetRepresentation) RepresentationSetRepresentation;
#endif	
	class RepresentationSetRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:
		bool isHomogeneous() const;
		unsigned int 						getRepresentationCount() const;
		AbstractRepresentation*				getRepresentation(unsigned int index) const;
	};
		
#ifdef SWIGPYTHON
	%rename(resqml2_AbstractSurfaceFrameworkRepresentation) AbstractSurfaceFrameworkRepresentation;
#endif
	class AbstractSurfaceFrameworkRepresentation : public RepresentationSetRepresentation
	{
	public:
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_NonSealedSurfaceFrameworkRepresentation) NonSealedSurfaceFrameworkRepresentation;
#endif
	class NonSealedSurfaceFrameworkRepresentation : public AbstractSurfaceFrameworkRepresentation
	{
	public:
		void pushBackNonSealedContactRepresentation(unsigned int pointCount, double * points, EML2_NS::AbstractHdfProxy* proxy = nullptr, AbstractLocal3dCrs* localCrs = nullptr);
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_SubRepresentation) SubRepresentation;
#endif
	class SubRepresentation : public AbstractRepresentation
	{
	public:
		void pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement elementKind, uint64_t originIndex,
			unsigned int elementCountInSlowestDimension,
			unsigned int elementCountInMiddleDimension,
			unsigned int elementCountInFastestDimension);
		void pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement elementKind, uint64_t elementCount, uint64_t* elementIndices, EML2_NS::AbstractHdfProxy* proxy = nullptr, short* supportingRepIndices = nullptr);
		void pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement elementKind0, gsoap_eml2_3::resqml22__IndexableElement elementKind1,
			uint64_t elementCount,
			uint64_t * elementIndices0, uint64_t * elementIndices1,
			EML2_NS::AbstractHdfProxy* proxy = nullptr) = 0;
		
		bool areElementIndicesPairwise(unsigned int patchIndex) const;
		bool areElementIndicesBasedOnLattice(unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const;

		int64_t getLatticeElementIndicesStartValue(unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const;
		unsigned int getLatticeElementIndicesDimensionCount(unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const;
		int64_t getLatticeElementIndicesOffsetValue(unsigned int latticeDimensionIndex, unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const;
		uint64_t getLatticeElementIndicesOffsetCount(unsigned int latticeDimensionIndex, unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const;
		
		AbstractRepresentation::indexableElement getElementKindOfPatch(unsigned int patchIndex, unsigned int elementIndicesIndex) const;
		uint64_t getElementCountOfPatch(unsigned int patchIndex) const;
		void getElementIndicesOfPatch(unsigned int patchIndex, unsigned int elementIndicesIndex, uint64_t * elementIndices) const;
		

		void pushBackSupportingRepresentation(AbstractRepresentation * supportingRep);
		unsigned int getSupportingRepresentationCount() const = 0;
		AbstractRepresentation* getSupportingRepresentation(unsigned int index) const;
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_SealedSurfaceFrameworkRepresentation) SealedSurfaceFrameworkRepresentation;
#endif
	class SealedSurfaceFrameworkRepresentation : public AbstractSurfaceFrameworkRepresentation
	{
	public:
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_SealedVolumeFrameworkRepresentation) SealedVolumeFrameworkRepresentation;
#endif
	class SealedVolumeFrameworkRepresentation : public RepresentationSetRepresentation
	{
	public:
		SealedSurfaceFrameworkRepresentation* getSealedStructuralFramework() const;
		void setSealedSurfaceFramework(SealedSurfaceFrameworkRepresentation* ssf);
		
		void setInterpretationOfVolumeRegion(unsigned int regionIndex, StratigraphicUnitInterpretation * stratiUnitInterp);
		
		void pushBackVolumeRegion(StratigraphicUnitInterpretation * stratiUnitInterp,
			unsigned int externalShellFaceCount,
			unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, char const* faceSide);
		pushBackInternalShell(unsigned int regionIndex,
			unsigned int internalShellFaceCount,
			unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, char const* faceSide);
			
		unsigned int getRegionCount() const;

		unsigned int getInternalShellCount(unsigned int regionIndex) const;

		unsigned int getFaceCountOfExternalShell(unsigned int regionIndex) const;
		unsigned int getFaceCountOfInternalShell(unsigned int regionIndex, unsigned int internalShellIndex) const;

		RESQML2_NS::AbstractRepresentation* getRepOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex);
		RESQML2_NS::AbstractRepresentation* getRepOfInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex);

		unsigned int getRepPatchIndexOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex);
		unsigned int getRepPatchIndexOfInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex);

		bool getSideFlagOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex);
		bool getSideFlagOfInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex);
	};
	
	class GridConnectionSetRepresentation;
	class AbstractColumnLayerGridRepresentation;
	class AbstractIjkGridRepresentation;
	class UnstructuredGridRepresentation;
#ifdef SWIGPYTHON
	%rename(resqml2_AbstractGridRepresentation) AbstractGridRepresentation;
#endif
	class AbstractGridRepresentation : public AbstractRepresentation
	{
	public:
		unsigned int getGridConnectionSetRepresentationCount() const;
		GridConnectionSetRepresentation* getGridConnectionSetRepresentation(unsigned int index) const;
		virtual uint64_t getCellCount() const = 0;
		
		AbstractGridRepresentation* getParentGrid() const;
		unsigned int getChildGridCount() const;
		AbstractGridRepresentation* getChildGrid(unsigned int index) const;
		void setParentWindow(uint64_t * cellIndices, uint64_t cellIndexCount, UnstructuredGridRepresentation* parentGrid, EML2_NS::AbstractHdfProxy * proxy = nullptr);
		void setParentWindow(unsigned int * columnIndices, unsigned int columnIndexCount,
			unsigned int kLayerIndexRegridStart,
			unsigned int * childCellCountPerInterval, unsigned int * parentCellCountPerInterval,  unsigned int intervalCount,
			class AbstractColumnLayerGridRepresentation* parentGrid,
			EML2_NS::AbstractHdfProxy * proxy = nullptr, double * childCellWeights = nullptr);
		void setParentWindow(
			unsigned int iCellIndexRegridStart, unsigned int * childCellCountPerIInterval, unsigned int * parentCellCountPerIInterval,  unsigned int iIntervalCount,
			unsigned int jCellIndexRegridStart, unsigned int * childCellCountPerJInterval, unsigned int * parentCellCountPerJInterval,  unsigned int jIntervalCount,
			unsigned int kCellIndexRegridStart, unsigned int * childCellCountPerKInterval, unsigned int * parentCellCountPerKInterval,  unsigned int kIntervalCount,
			AbstractIjkGridRepresentation* parentGrid, EML2_NS::AbstractHdfProxy * proxy = nullptr, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);
		void setParentWindow(
			unsigned int iCellIndexRegridStart, unsigned int constantChildCellCountPerIInterval, unsigned int constantParentCellCountPerIInterval, unsigned int iIntervalCount,
			unsigned int jCellIndexRegridStart, unsigned int constantChildCellCountPerJInterval, unsigned int constantParentCellCountPerJInterval, unsigned int jIntervalCount,
			unsigned int kCellIndexRegridStart, unsigned int constantChildCellCountPerKInterval, unsigned int constantParentCellCountPerKInterval, unsigned int kIntervalCount,
			AbstractIjkGridRepresentation* parentGrid, EML2_NS::AbstractHdfProxy * proxy = nullptr, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);
		void setParentWindow(
			unsigned int iCellIndexRegridStart, unsigned int iChildCellCount, unsigned int iParentCellCount,
			unsigned int jCellIndexRegridStart, unsigned int jChildCellCount, unsigned int jParentCellCount,
			unsigned int kCellIndexRegridStart, unsigned int kChildCellCount, unsigned int kParentCellCount,
			AbstractIjkGridRepresentation* parentGrid, EML2_NS::AbstractHdfProxy * proxy = nullptr, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);
		void setForcedNonRegridedParentCell(uint64_t * cellIndices, uint64_t cellIndexCount);	
		int64_t getParentCellIndexCount() const;
		void getParentCellIndices(uint64_t * parentCellIndices) const;
		int64_t getParentColumnIndexCount() const;
		void getParentColumnIndices(uint64_t * parentColumnIndices) const;
		uint64_t getRegridStartIndexOnParentGrid(char dimension) const;
		uint64_t getRegridIntervalCount(char dimension) const;
		bool isRegridCellCountPerIntervalConstant(char dimension, bool childVsParentCellCount) const;
		uint64_t getRegridConstantCellCountPerInterval(char dimension, bool childVsParentCellCount) const;
		void getRegridCellCountPerInterval(char dimension, uint64_t * childCellCountPerInterval, bool childVsParentCellCount) const;
		bool hasRegridChildCellWeights(char dimension) const;
		void getRegridChildCellWeights(char dimension, double * childCellWeights) const;
		bool hasForcedNonRegridedParentCell() const;

		void setCellAssociationWithStratigraphicOrganizationInterpretation(int64_t * stratiUnitIndices, int64_t nullValue, RESQML2_NS::AbstractStratigraphicOrganizationInterpretation* stratiOrgInterp);
		RESQML2_NS::AbstractStratigraphicOrganizationInterpretation* getStratigraphicOrganizationInterpretation() const;
		bool hasCellStratigraphicUnitIndices() const;
		int64_t getCellStratigraphicUnitIndices(int64_t * stratiUnitIndices);
		
		bool isTruncated() const;
		uint64_t getTruncatedFaceCount() const;
		void getNodeIndicesOfTruncatedFaces(uint64_t * nodeIndices) const;
		void getCumulativeNodeCountPerTruncatedFace(uint64_t * nodeCountPerFace) const;
		void getNodeCountPerTruncatedFace(uint64_t * nodeCountPerFace) const;
		uint64_t getTruncatedCellCount() const;
		void getTruncatedCellIndices(uint64_t* cellIndices) const;
		void getTruncatedFaceIndicesOfTruncatedCells(uint64_t * faceIndices) const;
		void getCumulativeTruncatedFaceCountPerTruncatedCell(uint64_t * cumulativeFaceCountPerCell) const;
		void getTruncatedFaceCountPerTruncatedCell(uint64_t * faceCountPerCell) const;
		void getNonTruncatedFaceIndicesOfTruncatedCells(uint64_t * faceIndices) const;
		void getCumulativeNonTruncatedFaceCountPerTruncatedCell(uint64_t * cumulativeFaceCountPerCell) const;
		void getNonTruncatedFaceCountPerTruncatedCell(uint64_t * faceCountPerCell) const;
		void getTruncatedFaceIsRightHanded(unsigned char* cellFaceIsRightHanded) const;
	};

#ifdef SWIGPYTHON
	%rename(resqml2_UnstructuredGridRepresentation) UnstructuredGridRepresentation;
#endif
	class UnstructuredGridRepresentation : public AbstractGridRepresentation
	{
	public:
		void getCellFaceIsRightHanded(unsigned char* cellFaceIsRightHanded) const;
	
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
		unsigned int getFaceCountOfCell(uint64_t cellIndex) const;
		unsigned int getNodeCountOfFaceOfCell(uint64_t cellIndex, unsigned int localFaceIndex) const;
		uint64_t const * getNodeIndicesOfFaceOfCell(uint64_t cellIndex, unsigned int localFaceIndex) const;
		void unloadGeometry();
		
		void setGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points, uint64_t pointCount, EML2_NS::AbstractHdfProxy* proxy,
			const std::string& faceIndicesPerCell, const std::string& faceIndicesCumulativeCountPerCell,
			uint64_t faceCount, const std::string& nodeIndicesPerFace, const std::string& nodeIndicesCumulativeCountPerFace,
			gsoap_resqml2_0_1::resqml20__CellShape cellShape, AbstractLocal3dCrs * localCrs = nullptr);

		void setGeometry(unsigned char * cellFaceIsRightHanded, double * points, uint64_t pointCount, EML2_NS::AbstractHdfProxy* proxy,
			uint64_t * faceIndicesPerCell, uint64_t * faceIndicesCumulativeCountPerCell,
			uint64_t faceCount, uint64_t * nodeIndicesPerFace, uint64_t * nodeIndicesCumulativeCountPerFace,
			gsoap_resqml2_0_1::resqml20__CellShape cellShape, AbstractLocal3dCrs * localCrs = nullptr);

		void setTetrahedraOnlyGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
			uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractHdfProxy* proxy,
			const std::string& faceIndicesPerCell, const std::string& nodeIndicesPerFace, AbstractLocal3dCrs * localCrs = nullptr);

		void setTetrahedraOnlyGeometry(unsigned char * cellFaceIsRightHanded, double * points,
			uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractHdfProxy* proxy,
			uint64_t * faceIndicesPerCell, uint64_t * nodeIndicesPerFace, AbstractLocal3dCrs * localCrs = nullptr);

		void setHexahedraOnlyGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
			uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractHdfProxy* proxy,
			const std::string& faceIndicesPerCell, const std::string& nodeIndicesPerFace, AbstractLocal3dCrs * localCrs = nullptr);

		void setHexahedraOnlyGeometry(unsigned char * cellFaceIsRightHanded, double * points,
			uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractHdfProxy* proxy,
			uint64_t * faceIndicesPerCell, uint64_t * nodeIndicesPerFace, AbstractLocal3dCrs * localCrs = nullptr);
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_AbstractColumnLayerGridRepresentation) AbstractColumnLayerGridRepresentation;
#endif
	class AbstractColumnLayerGridRepresentation : public AbstractGridRepresentation
	{
	public:
		unsigned int getKCellCount() const;
		void setKCellCount(unsigned int kCount);
		
		void setIntervalAssociationWithStratigraphicOrganizationInterpretation(int64_t * stratiUnitIndices, int64_t nullValue, RESQML2_NS::AbstractStratigraphicOrganizationInterpretation* stratiOrgInterp, EML2_NS::AbstractHdfProxy * hdfProxy);
		RESQML2_NS::AbstractStratigraphicOrganizationInterpretation* getStratigraphicOrganizationInterpretation() const;
		bool hasIntervalStratigraphicUnitIndices() const;
		int64_t getIntervalStratigraphicUnitIndices(int64_t * stratiUnitIndices);
		gsoap_resqml2_0_1::resqml20__PillarShape getMostComplexPillarGeometry() const;
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_AbstractIjkGridRepresentation) AbstractIjkGridRepresentation;
#endif
	class AbstractIjkGridRepresentation : public AbstractColumnLayerGridRepresentation
	{
	public:
		enum geometryKind { UNKNOWN = 0, EXPLICIT = 1, PARAMETRIC = 2, LATTICE = 3, NO_GEOMETRY = 4 };
	
		unsigned int getICellCount() const;
		void setICellCount(unsigned int iCount);
		unsigned int getJCellCount() const;
		void setJCellCount(unsigned int jCount);
		
		unsigned int getColumnCount() const;
		unsigned int getPillarCount() const;
		
		unsigned int getKGapsCount() const;
		void getKGaps(bool * kGaps) const;
		
		unsigned int getIPillarFromGlobalIndex(unsigned int globalIndex) const;
		unsigned int getJPillarFromGlobalIndex(unsigned int globalIndex) const;
		unsigned int getGlobalIndexPillarFromIjIndex(unsigned int iPillar, unsigned int jPillar) const;
		unsigned int getIColumnFromGlobalIndex(unsigned int globalIndex) const;
		unsigned int getJColumnFromGlobalIndex(unsigned int globalIndex) const;
		unsigned int getGlobalIndexColumnFromIjIndex(unsigned int iColumn, unsigned int jColumn) const;
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

		void getPillarsOfSplitCoordinateLines(unsigned int * pillarIndices, bool reverseIAxis = false, bool reverseJAxis = false) const;
		void getColumnsOfSplitCoordinateLines(unsigned int * columnIndices, bool reverseIAxis = false, bool reverseJAxis = false) const;
		void getColumnCountOfSplitCoordinateLines(unsigned int * columnIndexCountPerSplitCoordinateLine) const;
		unsigned long getSplitCoordinateLineCount() const;
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
		
		void getPillarGeometryIsDefined(bool * pillarGeometryIsDefined, bool reverseIAxis = false, bool reverseJAxis = false) const;
		bool hasEnabledCellInformation() const;
		void getEnabledCells(bool * enabledCells, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;
		void setEnabledCells(unsigned char* enabledCells, EML2_NS::AbstractHdfProxy* proxy = nullptr);
		
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
		
		virtual bool isNodeGeometryCompressed() const;
		
		gsoap_resqml2_0_1::resqml20__KDirection getKDirection() const;
		
		virtual geometryKind getGeometryKind() const = 0;
	};
	
	
#ifdef SWIGPYTHON
	%rename(resqml2_IjkGridLatticeRepresentation) IjkGridLatticeRepresentation;
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
			double directionKX, double directionKY, double directionKZ, double spacingK, AbstractLocal3dCrs * localCrs = nullptr);

		void addSeismic3dCoordinatesToPatch(
			unsigned int patchIndex,
			double startInline, double incrInline, unsigned int countInline,
			double startCrossline, double incrCrossline, unsigned int countCrossline,
			unsigned int countSample, AbstractRepresentation * seismicSupport);
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_IjkGridExplicitRepresentation) IjkGridExplicitRepresentation;
#endif
	class IjkGridExplicitRepresentation : public AbstractIjkGridRepresentation
	{
	public:
		void setGeometryAsCoordinateLineNodes(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			double * points, EML2_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned long splitCoordinateLineCount = 0, unsigned int * pillarOfCoordinateLine = nullptr,
			unsigned int * splitCoordinateLineColumnCumulativeCount = nullptr, unsigned int * splitCoordinateLineColumns = nullptr,
			char * definedPillars = nullptr, AbstractLocal3dCrs * localCrs = nullptr);

		void setGeometryAsCoordinateLineNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & points, EML2_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned long splitCoordinateLineCount = 0, const std::string & pillarOfCoordinateLine = "",
			const std::string & splitCoordinateLineColumnCumulativeCount = "", const std::string & splitCoordinateLineColumns = "",
			const std::string & definedPillars = "", AbstractLocal3dCrs * localCrs = nullptr);
	};

#ifdef SWIGPYTHON
	%rename(resqml2_IjkGridParametricRepresentation) IjkGridParametricRepresentation;
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
			EML2_NS::AbstractHdfProxy* proxy = nullptr, AbstractLocal3dCrs * localCrs = nullptr);

		void setGeometryAsParametricNonSplittedPillarNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, AbstractLocal3dCrs * localCrs = nullptr);

		void setGeometryAsParametricSplittedPillarNodes(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, bool isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, unsigned int controlPointMaxCountPerPillar, short * pillarKind, EML2_NS::AbstractHdfProxy* proxy,
			unsigned long splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
			unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns, AbstractLocal3dCrs * localCrs = nullptr);

		void setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars, EML2_NS::AbstractHdfProxy* proxy,
			unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
			const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, AbstractLocal3dCrs * localCrs = nullptr);

		void setGeometryAsParametricSplittedPillarNodes(bool isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, unsigned int controlPointCountPerPillar, short pillarKind, EML2_NS::AbstractHdfProxy* proxy,
			unsigned long splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
			unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns, AbstractLocal3dCrs * localCrs = nullptr);

		void setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointCountPerPillar, short pillarKind, EML2_NS::AbstractHdfProxy* proxy,
			unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
			const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, AbstractLocal3dCrs * localCrs = nullptr);
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_IjkGridNoGeometryRepresentation) IjkGridNoGeometryRepresentation;
#endif	
	class IjkGridNoGeometryRepresentation : public AbstractIjkGridRepresentation
	{
	public:
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_GridConnectionSetRepresentation) GridConnectionSetRepresentation;
#endif
	class GridConnectionSetRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:
		bool isAssociatedToInterpretations() const;
		void getInterpretationIndexCumulativeCount(unsigned int * cumulativeCount) const;
		void getInterpretationIndices(unsigned int * interpretationIndices) const;
		int64_t getInterpretationIndexNullValue() const;
	
		uint64_t getCellIndexPairCount() const;
		unsigned int getCellIndexPairCountFromInterpretationIndex(unsigned int interpretationIndex) const;
		
		int64_t getCellIndexPairs(int64_t * cellIndexPairs) const;
		void getGridConnectionSetInformationFromInterpretationIndex(int64_t * cellIndexPairs, unsigned short * gridIndexPairs, int * localFaceIndexPairs, unsigned int interpretationIndex) const;
		bool hasLocalFacePerCell() const;
		int64_t getLocalFacePerCellIndexPairs(int * localFacePerCellIndexPairs) const;
		bool isBasedOnMultiGrids() const;
		void getGridIndexPairs(unsigned short * gridIndexPairs) const;
		
		void pushBackSupportingGridRepresentation(AbstractGridRepresentation * supportingGridRep);
		
		void setCellIndexPairs(uint64_t cellIndexPairCount, int64_t * cellIndexPair, int64_t cellIndexPairNullValue = -1, EML2_NS::AbstractHdfProxy * proxy = nullptr);
		void setCellIndexPairs(uint64_t cellIndexPairCount, int64_t * cellIndexPair, int64_t cellIndexPairNullValue, EML2_NS::AbstractHdfProxy * proxy, uint16_t gridIndexPairNullValue, uint16_t const * gridIndexPair);
		void setLocalFacePerCellIndexPairs(uint64_t cellIndexPairCount, int * localFacePerCellIndexPair, int nullValue, EML2_NS::AbstractHdfProxy * proxy);
		void setConnectionInterpretationIndices(unsigned int * interpretationIndices, unsigned int interpretationIndiceCount, unsigned int nullValue, EML2_NS::AbstractHdfProxy * proxy);
		void pushBackInterpretation(AbstractFeatureInterpretation* interp);
		
		std::string getInterpretationUuidFromIndex(unsigned int interpretationIndex) const;
		AbstractFeatureInterpretation * getInterpretationFromIndex(unsigned int interpretationIndex) const;
		unsigned int getInterpretationCount() const;
		
		unsigned int getSupportingGridRepresentationCount() const;
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
	%rename(resqml2_StreamlinesFeature) StreamlinesFeature;
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
	%rename(resqml2_StreamlinesRepresentation) StreamlinesRepresentation;
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
		uint32_t getLineCount() const;

		/**
		 * Gets the count of wellbore trajectories of this streamlines representation.
		 *
		 * @exception	std::range_error	If the count of wellbore trajectories is strictly
		 * 									greater than unsigned int max.
		 *
		 * @returns	The count of wellbore trajectories.
		 */
		uint16_t getWellboreTrajectoryCount() const;

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
		RESQML2_NS::WellboreTrajectoryRepresentation* getWellboreTrajectory(uint16_t index);

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
			EML2_NS::AbstractHdfProxy* hdfProxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr);

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
		uint16_t getGridRepresentationCount() const;

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
		RESQML2_NS::AbstractGridRepresentation* getGridRepresentation(uint16_t index) const;
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_AbstractProperty) AbstractProperty;
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
		COMMON_NS::AbstractObject::hdfDatatypeEnum getValuesHdfDatatype() const;

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
		unsigned int getValuesCountOfPatch(unsigned int patchIndex) const;

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
		unsigned int getValuesCountOfDimensionOfPatch(unsigned int dimIndex, unsigned int patchIndex) const;

		/**
		 * Gets the count of dimensions of the underlying HDF5 dataset of a given patch of this property.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	patchIndex	The index of the patch we want to count the dimensions from.
		 *
		 * @returns	The number of values, 0 otherwise.
		 */
		unsigned int getDimensionsCountOfPatch(unsigned int patchIndex) const;
		
		std::string getPropertyKindDescription() const;
		std::string getPropertyKindAsString() const;
		std::string getPropertyKindParentAsString() const;
		bool isAssociatedToOneStandardEnergisticsPropertyKind() const;
		
		EML2_NS::PropertyKind* getPropertyKind() const;
		
		unsigned int getElementCountPerValue() const;
		
		gsoap_eml2_3::resqml22__IndexableElement getAttachmentKind() const;
		
		std::vector<RESQML2_NS::PropertySet *> getPropertySets() const;
		unsigned int getPropertySetCount() const;
		RESQML2_NS::PropertySet * getPropertySet(unsigned int index) const;
		
		bool hasRealizationIndices() const;
		std::vector<unsigned int> getRealizationIndices() const;
		void setRealizationIndices(int64_t startRealizationIndex, int64_t countRealizationIndices);
		void setRealizationIndices(const std::vector<unsigned int> & realizationIndices, EML2_NS::AbstractHdfProxy* hdfProxy = nullptr);
		
		void setTimeSeries(EML2_NS::TimeSeries * ts);
		EML2_NS::TimeSeries* getTimeSeries() const;
		void setTimeIndices(unsigned int startTimeIndex, unsigned int countTimeIndices, EML2_NS::TimeSeries* ts, bool useInterval = false);
		unsigned int getTimeIndexStart() const;
		unsigned int getTimeIndicesCount() const;
		bool useInterval() const;
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_AbstractValuesProperty) AbstractValuesProperty;
#endif
	class AbstractValuesProperty : public RESQML2_NS::AbstractProperty
	{
	public:
		unsigned int getValuesCountOfPatch (unsigned int patchIndex) const;

		void pushBackFacet(gsoap_eml2_3::eml23__FacetKind facet, const std::string & facetValue);
		unsigned int getFacetCount() const const;
		gsoap_eml2_3::eml23__FacetKind getFacetKind(unsigned int index) const;
		std::string getFacetValue(unsigned int index) const;
		
		//****************************/
		//****** INTEGER *************/
		//****************************/

		/**
		 * @brief	Adds a 1d array of explicit long values to the property values.
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
		void pushBackLongHdf5Array1dOfValues(const int64_t * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue);

		/**
		 * Adds a 1d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array1dOfValues
		 */
		void pushBackIntHdf5Array1dOfValues(const int * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, int nullValue);

		/**
		 * Adds a 1d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array1dOfValues
		 */
		void pushBackShortHdf5Array1dOfValues(const short * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, short nullValue);

		/**
		 * Adds a 1d array of explicit char values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array1dOfValues
		 */
		void pushBackCharHdf5Array1dOfValues(const char * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, char nullValue);

		/**
		 * @brief Adds a 2d array of explicit long values to the property values.
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
		void pushBackLongHdf5Array2dOfValues(const int64_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue);

		/**
		 * Adds a 2d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array2dOfValues
		 */
		void pushBackIntHdf5Array2dOfValues(const int * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int nullValue);

		/**
		 * Adds a 2d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array2dOfValues
		 */
		void pushBackShortHdf5Array2dOfValues(const short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, short nullValue);

		/**
		 * Adds a 2d array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array2dOfValues
		 */
		void pushBackUShortHdf5Array2dOfValues(const unsigned short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue);

		/**
		 * Adds a 2d array of explicit char values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array2dOfValues
		 */
		void pushBackCharHdf5Array2dOfValues(const char * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, char nullValue);

		/**
		 * @brief Adds a 3d array of explicit long values to the property values.
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
		void pushBackLongHdf5Array3dOfValues(const int64_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue);

		/**
		 * Adds a 3d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array3dOfValues
		 */
		void pushBackIntHdf5Array3dOfValues(const int * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int nullValue);

		/**
		 * Adds a 3d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array3dOfValues
		 */
		void pushBackShortHdf5Array3dOfValues(const short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, short nullValue);

		/**
		 * Adds a 3d array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array3dOfValues
		 */
		void pushBackUShortHdf5Array3dOfValues(const unsigned short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue);

		/**
		 * Adds a 3d array of explicit char values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array3dOfValues
		 */
		void pushBackCharHdf5Array3dOfValues(const char * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, char nullValue);

		/**
		 * @brief	Adds an nd array of explicit long values to the property values.
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
		void pushBackLongHdf5ArrayOfValues(const int64_t * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue);

		/**
		 * Adds an nd array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackLongHdf5ArrayOfValues
		 */
		void pushBackIntHdf5ArrayOfValues(const int * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int nullValue);

		/**
		 * Adds an nd array of explicit short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5ArrayOfValues
		 */
		void pushBackShortHdf5ArrayOfValues(const short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, short nullValue);

		/**
		 * Adds an nd array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5ArrayOfValues
		 */
		void pushBackUShortHdf5ArrayOfValues(const unsigned short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue);

		/**
		 * Adds an nd array of explicit char values to the property values.
		 *
		 * @copydetails pushBackLongHdf5ArrayOfValues
		 */
		void pushBackCharHdf5ArrayOfValues(const char * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, char nullValue);

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
		 * Gets all the values of a given patch of this instance. Values are supposed to be long ones.
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
		int64_t getLongValuesOfPatch(unsigned int patchIndex, int64_t * values) const;

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
		int64_t getNullValueOfPatch(unsigned int patchIndex) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be integer ones.
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
		int getIntValuesOfPatch(unsigned int patchIndex, int * values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be unsigned
		 * integer ones.
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
		unsigned int getUIntValuesOfPatch(unsigned int patchIndex, unsigned int * values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be short ones.
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
		short getShortValuesOfPatch(unsigned int patchIndex, short * values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be unsigned
		 * short ones.
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
		unsigned short getUShortValuesOfPatch(unsigned int patchIndex, unsigned short * values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be char ones.
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
		char getCharValuesOfPatch(unsigned int patchIndex, char * values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be unsigned
		 * char ones.
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
		unsigned char getUCharValuesOfPatch(unsigned int patchIndex, unsigned char * values) const;

		//***********************************/
		//*** INTEGER For hyperslabbing *****/
		//***********************************/

		/**
		 * Creates an nd array of explicit long 64 bits values into the property values. No values are
		 * written to this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param [in]	  	numValues		  	The number of property values ordered by dimension of the
		 * 										array to write. It is ordered from slowest dimension to
		 * 										fastest dimension.
		 * @param 		  	numArrayDimensions	The number of dimensions of the array to write.
		 * @param 		  	nullValue		  	(Optional) The null value. Default value is long 64 bits
		 * 										maximum value.
		 * @param [in,out]	proxy			  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If @c nullptr (default value),
		 * 										a default HDF proxy must be defined into the data object
		 * 										repository.
		 */
		void pushBackLongHdf5ArrayOfValues(
			unsigned long long* numValues,
			unsigned int numArrayDimensions,
			int64_t nullValue = std::numeric_limits<int64_t>::max(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Creates a 3d array of explicit long 64 values into the property values. No values are written
		 * to this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 		  	valueCountInFastestDim	The number of values in the fastest dimension (mainly
		 * 											I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values in the middle dimension (mainly
		 * 											J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values in the slowest dimension (mainly
		 * 											K dimension).
		 * @param 		  	nullValue			  	(Optional) The null value. Default value is long 64
		 * 											bits maximum value.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @p nullptr
		 * 											(default value), a default HDF proxy must be defined
		 * 											into the data object repository.
		 */
		void pushBackLongHdf5Array3dOfValues(
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			int64_t nullValue = std::numeric_limits<int64_t>::max(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds a 3d array of explicit long 64 bits values into the property values. Since this methods
		 * only pushes back values into an existing array, it is to be used along with
		 * pushBackLongHdf5Array3dOfValues().
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
		void setValuesOfLongHdf5Array3dOfValues(
			int64_t* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned int patchIndex = std::numeric_limits<unsigned int>::max());

		/**
		 * Adds an nd array of explicit long 64 bits values into to the property values. Since this
		 * methods only pushes back values into an existing array, it is to be used along with
		 * pushBackLongHdf5ArrayOfValues().
		 *
		 * @exception	std::invalid_argument	If @p proxy is null and no default HDF proxy is defined
		 * 										into the data object repository.
		 * @exception	std::out_of_range	 	If @p patchIndex is strictly greater than patch count and
		 * 										different from unsigned int maximum value.
		 *
		 * @param [in]	  	values			  	All the property values to set ordered according to the
		 * 										topology of the representation it is based on.
		 * @param 		  	numValues		  	The number of property values ordered by dimension of the
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
		void setValuesOfLongHdf5ArrayOfValues(
			int64_t* values,
			unsigned long long const * numValues,
			unsigned long long const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned int patchIndex = std::numeric_limits<unsigned int>::max());

		/**
		 * Gets some of the values of a given patch of this instance. Values are supposed to be long 64
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
		void getLongValuesOfPatch(
			unsigned int patchIndex,
			int64_t* values,
			unsigned long long const * numValuesInEachDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned int numArrayDimensions
		) const;

		/**
		 * Gets some of the values of a given patch of this instance. Values are supposed to be long 64
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
		void getLongValuesOf3dPatch(
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
			unsigned long long* numValuesInEachDimension,
			unsigned long long* offsetInEachDimension,
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
		void pushBackDoubleHdf5ArrayOfValues(double const * values, unsigned long long const * numValues, unsigned int numArrayDimensions, EML2_NS::AbstractHdfProxy* proxy = nullptr);

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
		void pushBackFloatHdf5ArrayOfValues(float const * values, unsigned long long const * numValues, unsigned int numArrayDimensions, EML2_NS::AbstractHdfProxy* proxy = nullptr);

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
		virtual std::string pushBackRefToExistingFloatingPointDataset(EML2_NS::AbstractHdfProxy* proxy, const std::string & datasetName = "");

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
		 * @param [in,out]	proxy			  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If @c nullptr (default), a
		 * 										default HDF proxy must be defined into the data object
		 * 										repository.
		 */
		void pushBackFloatHdf5ArrayOfValues(
			unsigned long long const * numValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr
		);

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
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default), a default HDF proxy must be defined into
		 * 											the data object repository.
		 */
		void pushBackFloatHdf5Array3dOfValues(
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr
		);

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
		void setValuesOfFloatHdf5Array3dOfValues(
			float const * values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned int patchIndex = std::numeric_limits<unsigned int>::max()
		);

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
			unsigned long long const * numValues,
			unsigned long long const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned int patchIndex = std::numeric_limits<unsigned int>::max()
		);

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
			unsigned long long const * numValuesInEachDimension,
			unsigned long long const * offsetInEachDimension,
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
	%rename(resqml2_CommentProperty) CommentProperty;
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
	%rename(resqml2_ContinuousProperty) ContinuousProperty;
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
		void pushBackDoubleHdf5ArrayOfValues(double const * values, unsigned long long const * numValues, unsigned int numArrayDimensions,
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
		void pushBackFloatHdf5ArrayOfValues(float const * values, unsigned long long const * numValues, unsigned int numArrayDimensions,
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

		//***************************/
		//*** For hyperslabbing *****/
		//***************************/

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
		void pushBackFloatHdf5ArrayOfValues(
			unsigned long long const * numValues,
			unsigned int numArrayDimensions,
			float * minimumValue, float * maximumValue,
			EML2_NS::AbstractHdfProxy* proxy = nullptr
		);

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
		void pushBackFloatHdf5Array3dOfValues(
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			float minimumValue, float maximumValue,
			EML2_NS::AbstractHdfProxy* proxy = nullptr
		);

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
			unsigned int patchIndex = std::numeric_limits<unsigned int>::max()
		);

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
			unsigned long long const * numValues,
			unsigned long long const * offsetValues,
			unsigned int numArrayDimensions,
			bool computeMinMax,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned int patchIndex = std::numeric_limits<unsigned int>::max()
		);
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_DiscreteProperty) DiscreteProperty;
#endif
	class DiscreteProperty : public AbstractValuesProperty
	{
	public:
		void pushBackLongHdf5Array1dOfValues(const int64_t * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue, int64_t minimumValue, int64_t maximumValue);
		void pushBackIntHdf5Array1dOfValues(const int * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, int nullValue, int minimumValue, int maximumValue);
		void pushBackShortHdf5Array1dOfValues(const short * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, short nullValue, short minimumValue, short maximumValue);
		void pushBackCharHdf5Array1dOfValues(const char * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, char nullValue, char minimumValue, char maximumValue);

		void pushBackLongHdf5Array2dOfValues(const int64_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue, int64_t minimumValue, int64_t maximumValue);
		void pushBackIntHdf5Array2dOfValues(const int * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int nullValue, int minimumValue, int maximumValue);
		void pushBackShortHdf5Array2dOfValues(const short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, short nullValue, short minimumValue, short maximumValue);
		void pushBackUShortHdf5Array2dOfValues(const unsigned short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue);
		void pushBackCharHdf5Array2dOfValues(const char * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, char nullValue, char minimumValue, char maximumValue);

		void pushBackLongHdf5Array3dOfValues(const int64_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue, int64_t minimumValue, int64_t maximumValue);
		void pushBackIntHdf5Array3dOfValues(const int * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int nullValue, int minimumValue, int maximumValue);
		void pushBackShortHdf5Array3dOfValues(const short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, short nullValue, short minimumValue, short maximumValue);
		void pushBackUShortHdf5Array3dOfValues(const unsigned short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue);
		void pushBackCharHdf5Array3dOfValues(const char * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, char nullValue, char minimumValue, char maximumValue);

		void pushBackLongHdf5ArrayOfValues(const int64_t * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue, int64_t minimumValue, int64_t maximumValue);
		void pushBackIntHdf5ArrayOfValues(const int * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int nullValue, int minimumValue, int maximumValue);
		void pushBackShortHdf5ArrayOfValues(const short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, short nullValue, short minimumValue, short maximumValue);
		void pushBackUShortHdf5ArrayOfValues(const unsigned short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue);
		void pushBackCharHdf5ArrayOfValues(const char * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, char nullValue, char minimumValue, char maximumValue);
		
		void pushBackLongHdf5ArrayOfValues(
			unsigned long long* numValues,
			unsigned int numArrayDimensions,
			int64_t* minimumValue, int64_t* maximumValue,
			int64_t nullValue = std::numeric_limits<int64_t>::max(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr);

		void pushBackLongHdf5Array3dOfValues(
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			int64_t minimumValue, int64_t maximumValue,
			int64_t nullValue = std::numeric_limits<int64_t>::max(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr);

		void setValuesOfLongHdf5Array3dOfValues(
			int64_t* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			bool computeMinMax,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned int patchIndex = std::numeric_limits<unsigned int>::max());

		void setValuesOfLongHdf5ArrayOfValues(
			int64_t* values,
			unsigned long long const * numValues,
			unsigned long long const * offsetValues,
			unsigned int numArrayDimensions,
			bool computeMinMax,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned int patchIndex = std::numeric_limits<unsigned int>::max());
		
		bool hasMinimumValue() const;
		int64_t getMinimumValue() const;
		bool hasMaximumValue() const;
		int64_t getMaximumValue() const;
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_DoubleTableLookup) DoubleTableLookup;
#endif	
	class DoubleTableLookup : public COMMON_NS::AbstractObject
	{
	public:
		bool containsKey(double key);
	
		unsigned int getItemCount() const;
		double getKeyAtIndex(unsigned int index) const;
		double getValueAtIndex(unsigned int index) const;
		double getValueAtKey(double key);
		
		void addValue(double key, double longValue);
		void setValue(double key, double longValue);
		
		double getMinimumValue();
		double getMaximumValue();
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_StringTableLookup) StringTableLookup;
#endif	
	class StringTableLookup : public COMMON_NS::AbstractObject
	{
	public:
		bool containsKey(long longValue);
	
		unsigned int getItemCount() const;
		long getKeyAtIndex(unsigned int index) const;
		std::string getStringValueAtIndex(unsigned int index) const;
		std::string getStringValue(long longValue);
		
		void addValue(const std::string & strValue, long longValue);
		void setValue(const std::string & strValue, long longValue);
		
		int64_t getMinimumValue();
		int64_t getMaximumValue();
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_CategoricalProperty) CategoricalProperty;
#endif
	class CategoricalProperty : public AbstractValuesProperty
	{
	public:
		DoubleTableLookup* getDoubleLookup();
		StringTableLookup* getStringLookup();
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_PointsProperty) PointsProperty;
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
		void pushBackArrayOfXyzPoints(double const * xyzPoints, unsigned long long const * pointCountByDimension, unsigned int numArrayDimensions, EML2_NS::AbstractHdfProxy* proxy = nullptr);

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
	class DeviationSurveyRepresentation;
#ifdef SWIGPYTHON
	%rename(resqml2_WellboreTrajectoryRepresentation) WellboreTrajectoryRepresentation;
#endif
	class  WellboreTrajectoryRepresentation : public AbstractRepresentation
	{
	public:
		unsigned int getWellboreFrameRepresentationCount() const;
		WellboreFrameRepresentation* getWellboreFrameRepresentation(unsigned int index) const;
		
		/**
		 * Sets the minimal geometry of the representation by means of start and end MDs.
		 *
		 * @param 	startMd	The start MD of the trajectory. Uom is the same as the one for the associated
		 * 					MdDatum coordinates.
		 * @param 	endMd  	The end MD of the trajectory. Uom is the same as the one for the associated
		 * 					MdDatum coordinates.
		 */
		virtual void setMinimalGeometry(double startMd, double endMd) = 0;

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
		virtual void setGeometry(double const* controlPoints, double startMd, double endMd, unsigned int controlPointCount, int lineKind, EML2_NS::AbstractHdfProxy* proxy = nullptr, AbstractLocal3dCrs* localCrs = nullptr) = 0;

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
		virtual void setGeometry(double const* controlPoints, double const* controlPointParameters, unsigned int controlPointCount, int lineKind,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, AbstractLocal3dCrs* localCrs = nullptr) = 0;

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
		virtual void setGeometry(double const* controlPoints,
			double const* tangentVectors, double const* controlPointParameters, unsigned int controlPointCount, int lineKind,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, AbstractLocal3dCrs* localCrs = nullptr) = 0;

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
			double const* inclinations, double const* azimuths, double const* controlPointParameters, unsigned int controlPointCount, int lineKind,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, AbstractLocal3dCrs* localCrs = nullptr);
			
		/**
		 * Sets the MD datum of this trajectory.
		 *
		 * @exception	std::invalid_argument	If @p mdDatum is @c nullptr.
		 *
		 * @param [in]	mdDatum	The MD damtum to set to this trajectory. It cannot be null.
		 */
		virtual void setMdDatum(MdDatum * mdDatum) = 0;
		
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
		virtual bool hasGeometry() const = 0;
		
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
		virtual int getGeometryKind() const = 0;

		/**
		 * Indicates if the wellbore trajectory has got tangent vectors attached to each trajectory
		 * station. Tangent vectors ussually transport inclination and azimuth of a trajectory station.
		 *
		 * @exception	std::logic_error	If the geometry of this trajectory is not a parametric line.
		 *
		 * @returns	True if there is some tangent vectors, false if not.
		 */
		virtual bool hasTangentVectors() const = 0;
		
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
		virtual void getTangentVectors(double* tangentVectors) = 0;

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
		virtual bool hasMdValues() const = 0;
		
		/**
		 * Gets the unit of measure of the MDs along this trajectory.
		 *
		 * @returns	The unit of measure of the MDs along this trajectory.
		 */
		virtual gsoap_resqml2_0_1::eml20__LengthUom getMdUom() const = 0;
		
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
		virtual void getMdValues(double* values) const = 0;
		
		/**
		 * Gets the starting MD of this wellbore trajectory. Range may often be from kickoff to TD, but
		 * this is not necessary.
		 *
		 * @returns	The start MD.
		 */
		virtual double getStartMd() const = 0;

		/**
		 * Gets the ending MD of this wellbore trajectory. Range may often be from kickoff to TD, but
		 * this is not necessary.
		 *
		 * @returns	The end MD.
		 */
		virtual double getFinishMd() const = 0;
			
		void addParentTrajectory(double kickoffMd, double parentMd, WellboreTrajectoryRepresentation* parentTrajRep);
		WellboreTrajectoryRepresentation* getParentTrajectory() const;
		double getParentTrajectoryMd() const;
		
		void setDeviationSurvey(DeviationSurveyRepresentation* deviationSurvey);
		DeviationSurveyRepresentation* getDeviationSurvey() const;
	};

#ifdef SWIGPYTHON
	%rename(resqml2_WellboreFrameRepresentation) WellboreFrameRepresentation;
#endif
	class WellboreFrameRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:
		void setMdValues(double const * mdValues, unsigned int mdValueCount, EML2_NS::AbstractHdfProxy* proxy = nullptr);
		void setMdValues(double firstMdValue, double incrementMdValue, unsigned int mdValueCount);

		bool areMdValuesRegularlySpaced() const;
		double getMdConstantIncrementValue() const;
		double getMdFirstValue() const;
		unsigned int getMdValuesCount() const;
		AbstractValuesProperty::hdfDatatypeEnum getMdHdfDatatype() const;
		void getMdAsDoubleValues(double * values) const;
		void getMdAsFloatValues(float * values) const;

		WellboreTrajectoryRepresentation* getWellboreTrajectory() const;
	};
	
#if defined(SWIGPYTHON)
	%rename(resqml2_SeismicWellboreFrameRepresentation) SeismicWellboreFrameRepresentation;
#endif
	class SeismicWellboreFrameRepresentation : public WellboreFrameRepresentation
	{
	public:
		void setTimeValues(double const * timeValues, unsigned int timeValueCount, EML2_NS::AbstractHdfProxy* proxy = nullptr);
		void setTimeValues(double firstTimeValue, double incrementTimeValue, unsigned int timeValueCount);

		bool areTimeValuesRegularlySpaced() const;
		double getTimeConstantIncrementValue() const;
		double getTimeFirstValue() const;
		unsigned int getTimeValuesCount() const;
		AbstractValuesProperty::hdfDatatypeEnum getTimeHdfDatatype() const;
		void getTimeAsDoubleValues(double* values) const;
		void getTimeAsFloatValues(float* values) const;
		double getSeismicReferenceDatum() const;
		double getWeatheringVelocity() const;
	};

	/**
	 * @brief	A blocked wellbore representation. This is the information that allows you to locate,
	 * 			on one or several grids (existing or planned), the intersection of volume (cells) and
	 * 			surface (faces) elements with a wellbore trajectory (existing or planned).
	 */
#ifdef SWIGPYTHON
	%rename(resqml2_BlockedWellboreRepresentation) BlockedWellboreRepresentation;
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
		 * @exception	std::invalid_argument	If <tt>cellCount == 0</tt>.
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
		 * 															grid.
		 * @param 		  	cellCount								The number of non-null entries in @p
		 * 															gridIndices.
		 * @param 		  	cellIndices								An array containing the intersected
		 * 															cell index for each non-null entry in @p
		 * 															gridIndices. They are ordered according
		 * 															to non-null entries of @p gridIndices.
		 * 															The array length must equal @p cellCount.
		 *															The null value is arbitrarily set to -1 since
		 *															it has no interest. Indeed corresponding gridIndex
		 *															already informs about the presence or not of a cell.
		 * @param 		  	localFacePairPerCellIndices				An array containing, for each cell,
		 * 															the entry and exit intersection faces of
		 * 															the trajectory in the cell. The array
		 * 															dimension must equal <tt>2 *
		 * 															cellCount</tt>.
		 * @param 		  	localFacePairPerCellIndicesNullValue	The null value used in @p
		 * 															localFacePerCellIndices in order to
		 * 															indicate that it corresponds to a missing
		 * 															intersection, e.g., when a trajectory
		 * 															originates or terminates within a cell.
		 * @param [in,out]	hdfProxy								The HDF proxy where the numerical
		 * 															values will be stored. It must be already
		 * 															opened for writing and won't be closed.It
		 * 															cannot be @c nullptr.
		 */
		void setIntervalGridCells(unsigned int const* gridIndices, unsigned int gridIndicesNullValue,
			unsigned int cellCount, int64_t const* cellIndices,
			unsigned char const* localFacePairPerCellIndices, unsigned char localFacePairPerCellIndicesNullValue, EML2_NS::AbstractHdfProxy * hdfProxy);

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
		int64_t getGridIndices(unsigned int * gridIndices) const;

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
		unsigned int getSupportingGridRepresentationCount() const;

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
		RESQML2_NS::AbstractGridRepresentation* getSupportingGridRepresentation(unsigned int index) const;

		/**
		 * Get the DOR of the supporting grid representation located at a specific index of this blocked
		 * wellbore representation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt>
		 * 									getSupportingGridRepresentationCount().
		 *
		 * @param 	index	Zero-based index of the supporting grid representation we look for.
		 *
		 * @returns	The DOR of the supporting grid representation at position @p index.
		 */
		COMMON_NS::DataObjectReference getSupportingGridRepresentationDor(unsigned int index) const;
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_WellboreMarkerFrameRepresentation) WellboreMarkerFrameRepresentation;
#endif
	class WellboreMarkerFrameRepresentation : public WellboreFrameRepresentation
	{
	public:		
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::WellboreMarker, WellboreMarker)
		void setIntervalStratigraphicUnits(unsigned int * stratiUnitIndices, unsigned int nullValue, class GeologicUnitOccurrenceInterpretation* occurrenceInterp, EML2_NS::AbstractHdfProxy* proxy);
		GeologicUnitOccurrenceInterpretation* getGeologicUnitOccurrenceInterpretation();
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_WellboreMarker) WellboreMarker;
#endif
	class WellboreMarker : public COMMON_NS::AbstractObject
	{
	public:
		bool hasAGeologicBoundaryKind() const;
		gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind getGeologicBoundaryKind() const;
		WellboreMarkerFrameRepresentation const * getWellboreMarkerFrameRepresentation() const;
		BoundaryFeatureInterpretation* getBoundaryFeatureInterpretation() const;
		void setBoundaryFeatureInterpretation(BoundaryFeatureInterpretation* interp);
		WITSML2_0_NS::WellboreMarker* getWitsmlWellboreMarker() const;
		virtual void setWitsmlWellboreMarker(WITSML2_0_NS::WellboreMarker * wellboreMarker) = 0;
		bool hasDipAngle() const;
		double getDipAngleValue() const;
		gsoap_eml2_1::eml21__PlaneAngleUom getDipAngleUom() const;
		std::string getDipAngleUomAsString() const;
		bool hasDipDirection() const;
		double getDipDirectionValue() const;
		gsoap_eml2_1::eml21__PlaneAngleUom getDipDirectionUom() const;
		std::string getDipDirectionUomAsString() const;
	};

#ifdef SWIGPYTHON
	%rename(resqml2_DeviationSurveyRepresentation) DeviationSurveyRepresentation;
#endif
	class DeviationSurveyRepresentation : public AbstractRepresentation
	{
	public:
		void setGeometry(double * firstStationLocation, uint64_t stationCount,
			gsoap_resqml2_0_1::eml20__LengthUom mdUom, double * mds,
			gsoap_resqml2_0_1::eml20__PlaneAngleUom angleUom, double * azimuths, double * inclinations,
			EML2_NS::AbstractHdfProxy* proxy);

		MdDatum * getMdDatum() const;

		bool isFinal() const;

		gsoap_resqml2_0_1::eml20__LengthUom getMdUom() const;
		gsoap_resqml2_0_1::eml20__PlaneAngleUom getAngleUom() const;

		void getMdValues(double* values) const;
		void getInclinations(double* values) const;
		void getAzimuths(double* values) const;

		unsigned int getWellboreFrameRepresentationCount() const;
		WellboreFrameRepresentation* getWellboreFrameRepresentation(unsigned int index) const;

		unsigned int getWellboreTrajectoryRepresentationCount() const;
		WellboreTrajectoryRepresentation* getWellboreTrajectoryRepresentation(unsigned int index) const;
	};
}

%include "swigResqml2_0_1Include.i"
#ifdef WITH_RESQML2_2
%include "swigResqml2_2Include.i"
#endif
