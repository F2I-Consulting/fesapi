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
	%nspace RESQML2_NS::PropertySet;
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
	enum resqml20__ResqmlUom {
		resqml20__ResqmlUom__A = 65,
		resqml20__ResqmlUom__a = 97,
		resqml20__ResqmlUom__b = 98,
		resqml20__ResqmlUom__B = 66,
		resqml20__ResqmlUom__C = 67,
		resqml20__ResqmlUom__d = 100,
		resqml20__ResqmlUom__D = 68,
		resqml20__ResqmlUom__F = 70,
		resqml20__ResqmlUom__g = 103,
		resqml20__ResqmlUom__H = 72,
		resqml20__ResqmlUom__h = 104,
		resqml20__ResqmlUom__J = 74,
		resqml20__ResqmlUom__K = 75,
		resqml20__ResqmlUom__L = 76,
		resqml20__ResqmlUom__m = 109,
		resqml20__ResqmlUom__N = 78,
		resqml20__ResqmlUom__O = 79,
		resqml20__ResqmlUom__P = 80,
		resqml20__ResqmlUom__S = 83,
		resqml20__ResqmlUom__s = 115,
		resqml20__ResqmlUom__t = 116,
		resqml20__ResqmlUom__T = 84,
		resqml20__ResqmlUom__V = 86,
		resqml20__ResqmlUom__W = 87,
		resqml20__ResqmlUom___x0025 = 117,
		resqml20__ResqmlUom___x0025_x005barea_x005d = 118,
		resqml20__ResqmlUom___x0025_x005bmass_x005d = 119,
		resqml20__ResqmlUom___x0025_x005bmolar_x005d = 120,
		resqml20__ResqmlUom___x0025_x005bvol_x005d = 121,
		resqml20__ResqmlUom___x0028bbl_x002fd_x0029_x002f_x0028bbl_x002fd_x0029 = 122,
		resqml20__ResqmlUom___x0028m3_x002fd_x0029_x002f_x0028m3_x002fd_x0029 = 123,
		resqml20__ResqmlUom___x0028m3_x002fs_x0029_x002f_x0028m3_x002fs_x0029 = 124,
		resqml20__ResqmlUom__0_x002e001_x0020bbl_x002fft3 = 125,
		resqml20__ResqmlUom__0_x002e001_x0020bbl_x002fm3 = 126,
		resqml20__ResqmlUom__0_x002e001_x0020d_x002fft3 = 127,
		resqml20__ResqmlUom__0_x002e001_x0020gal_x005bUK_x005d_x002fbbl = 128,
		resqml20__ResqmlUom__0_x002e001_x0020gal_x005bUK_x005d_x002fgal_x005bUK_x005d = 129,
		resqml20__ResqmlUom__0_x002e001_x0020gal_x005bUS_x005d_x002fbbl = 130,
		resqml20__ResqmlUom__0_x002e001_x0020gal_x005bUS_x005d_x002fft3 = 131,
		resqml20__ResqmlUom__0_x002e001_x0020gal_x005bUS_x005d_x002fgal_x005bUS_x005d = 132,
		resqml20__ResqmlUom__0_x002e001_x0020h_x002fft = 133,
		resqml20__ResqmlUom__0_x002e001_x0020kPa2_x002fcP = 134,
		resqml20__ResqmlUom__0_x002e001_x0020lbm_x002fbbl = 135,
		resqml20__ResqmlUom__0_x002e001_x0020lbm_x002fgal_x005bUK_x005d = 136,
		resqml20__ResqmlUom__0_x002e001_x0020lbm_x002fgal_x005bUS_x005d = 137,
		resqml20__ResqmlUom__0_x002e001_x0020psi_x002fft = 138,
		resqml20__ResqmlUom__0_x002e001_x0020pt_x005bUK_x005d_x002fbbl = 139,
		resqml20__ResqmlUom__0_x002e001_x0020seca = 140,
		resqml20__ResqmlUom__0_x002e01_x0020bbl_x002fbbl = 141,
		resqml20__ResqmlUom__0_x002e01_x0020dega_x002fft = 142,
		resqml20__ResqmlUom__0_x002e01_x0020degF_x002fft = 143,
		resqml20__ResqmlUom__0_x002e01_x0020dm3_x002fkm = 144,
		resqml20__ResqmlUom__0_x002e01_x0020ft_x002fft = 145,
		resqml20__ResqmlUom__0_x002e01_x0020grain_x002fft3 = 146,
		resqml20__ResqmlUom__0_x002e01_x0020L_x002fkg = 147,
		resqml20__ResqmlUom__0_x002e01_x0020L_x002fkm = 148,
		resqml20__ResqmlUom__0_x002e01_x0020lbf_x002fft = 149,
		resqml20__ResqmlUom__0_x002e01_x0020lbf_x002fft2 = 150,
		resqml20__ResqmlUom__0_x002e01_x0020lbm_x002fft2 = 151,
		resqml20__ResqmlUom__0_x002e01_x0020psi_x002fft = 152,
		resqml20__ResqmlUom__0_x002e1_x0020ft = 153,
		resqml20__ResqmlUom__0_x002e1_x0020ft_x005bUS_x005d = 154,
		resqml20__ResqmlUom__0_x002e1_x0020gal_x005bUS_x005d_x002fbbl = 155,
		resqml20__ResqmlUom__0_x002e1_x0020in = 156,
		resqml20__ResqmlUom__0_x002e1_x0020L_x002fbbl = 157,
		resqml20__ResqmlUom__0_x002e1_x0020lbm_x002fbbl = 158,
		resqml20__ResqmlUom__0_x002e1_x0020pt_x005bUS_x005d_x002fbbl = 159,
		resqml20__ResqmlUom__0_x002e1_x0020yd = 160,
		resqml20__ResqmlUom__1_x002f_x0028kg_x002es_x0029 = 161,
		resqml20__ResqmlUom__1_x002f16_x0020in = 162,
		resqml20__ResqmlUom__1_x002f2_x0020ft = 163,
		resqml20__ResqmlUom__1_x002f2_x0020ms = 164,
		resqml20__ResqmlUom__1_x002f30_x0020cm3_x002fmin = 165,
		resqml20__ResqmlUom__1_x002f30_x0020dega_x002fft = 166,
		resqml20__ResqmlUom__1_x002f30_x0020dega_x002fm = 167,
		resqml20__ResqmlUom__1_x002f30_x0020lbf_x002fm = 168,
		resqml20__ResqmlUom__1_x002f30_x0020m_x002fm = 169,
		resqml20__ResqmlUom__1_x002f30_x0020N_x002fm = 170,
		resqml20__ResqmlUom__1_x002f32_x0020in = 171,
		resqml20__ResqmlUom__1_x002f64_x0020in = 172,
		resqml20__ResqmlUom__1_x002fa = 173,
		resqml20__ResqmlUom__1_x002fangstrom = 174,
		resqml20__ResqmlUom__1_x002fbar = 175,
		resqml20__ResqmlUom__1_x002fbbl = 176,
		resqml20__ResqmlUom__1_x002fcm = 177,
		resqml20__ResqmlUom__1_x002fd = 178,
		resqml20__ResqmlUom__1_x002fdegC = 179,
		resqml20__ResqmlUom__1_x002fdegF = 180,
		resqml20__ResqmlUom__1_x002fdegR = 181,
		resqml20__ResqmlUom__1_x002fft = 182,
		resqml20__ResqmlUom__1_x002fft2 = 183,
		resqml20__ResqmlUom__1_x002fft3 = 184,
		resqml20__ResqmlUom__1_x002fg = 185,
		resqml20__ResqmlUom__1_x002fgal_x005bUK_x005d = 186,
		resqml20__ResqmlUom__1_x002fgal_x005bUS_x005d = 187,
		resqml20__ResqmlUom__1_x002fH = 188,
		resqml20__ResqmlUom__1_x002fh = 189,
		resqml20__ResqmlUom__1_x002fin = 190,
		resqml20__ResqmlUom__1_x002fK = 191,
		resqml20__ResqmlUom__1_x002fkg = 192,
		resqml20__ResqmlUom__1_x002fkm2 = 193,
		resqml20__ResqmlUom__1_x002fkPa = 194,
		resqml20__ResqmlUom__1_x002fL = 195,
		resqml20__ResqmlUom__1_x002flbf = 196,
		resqml20__ResqmlUom__1_x002flbm = 197,
		resqml20__ResqmlUom__1_x002fm = 198,
		resqml20__ResqmlUom__1_x002fm2 = 199,
		resqml20__ResqmlUom__1_x002fm3 = 200,
		resqml20__ResqmlUom__1_x002fmi = 201,
		resqml20__ResqmlUom__1_x002fmi2 = 202,
		resqml20__ResqmlUom__1_x002fmin = 203,
		resqml20__ResqmlUom__1_x002fmm = 204,
		resqml20__ResqmlUom__1_x002fms = 205,
		resqml20__ResqmlUom__1_x002fN = 206,
		resqml20__ResqmlUom__1_x002fnm = 207,
		resqml20__ResqmlUom__1_x002fPa = 208,
		resqml20__ResqmlUom__1_x002fpPa = 209,
		resqml20__ResqmlUom__1_x002fpsi = 210,
		resqml20__ResqmlUom__1_x002fs = 211,
		resqml20__ResqmlUom__1_x002fupsi = 212,
		resqml20__ResqmlUom__1_x002fus = 213,
		resqml20__ResqmlUom__1_x002fuV = 214,
		resqml20__ResqmlUom__1_x002fV = 215,
		resqml20__ResqmlUom__1_x002fwk = 216,
		resqml20__ResqmlUom__1_x002fyd = 217,
		resqml20__ResqmlUom__10_x0020ft = 218,
		resqml20__ResqmlUom__10_x0020in = 219,
		resqml20__ResqmlUom__10_x0020km = 220,
		resqml20__ResqmlUom__10_x0020kN = 221,
		resqml20__ResqmlUom__10_x0020Mg_x002fm3 = 222,
		resqml20__ResqmlUom__100_x0020ft = 223,
		resqml20__ResqmlUom__100_x0020ka_x005bt_x005d = 224,
		resqml20__ResqmlUom__100_x0020km = 225,
		resqml20__ResqmlUom__1000_x0020bbl = 226,
		resqml20__ResqmlUom__1000_x0020bbl_x002eft_x002fd = 227,
		resqml20__ResqmlUom__1000_x0020bbl_x002fd = 228,
		resqml20__ResqmlUom__1000_x0020ft = 229,
		resqml20__ResqmlUom__1000_x0020ft_x002fh = 230,
		resqml20__ResqmlUom__1000_x0020ft_x002fs = 231,
		resqml20__ResqmlUom__1000_x0020ft3 = 232,
		resqml20__ResqmlUom__1000_x0020ft3_x002f_x0028d_x002eft_x0029 = 233,
		resqml20__ResqmlUom__1000_x0020ft3_x002f_x0028psi_x002ed_x0029 = 234,
		resqml20__ResqmlUom__1000_x0020ft3_x002fbbl = 235,
		resqml20__ResqmlUom__1000_x0020ft3_x002fd = 236,
		resqml20__ResqmlUom__1000_x0020gal_x005bUK_x005d = 237,
		resqml20__ResqmlUom__1000_x0020gal_x005bUS_x005d = 238,
		resqml20__ResqmlUom__1000_x0020lbf_x002eft = 239,
		resqml20__ResqmlUom__1000_x0020m3 = 240,
		resqml20__ResqmlUom__1000_x0020m3_x002f_x0028d_x002em_x0029 = 241,
		resqml20__ResqmlUom__1000_x0020m3_x002f_x0028h_x002em_x0029 = 242,
		resqml20__ResqmlUom__1000_x0020m3_x002fd = 243,
		resqml20__ResqmlUom__1000_x0020m3_x002fh = 244,
		resqml20__ResqmlUom__1000_x0020m3_x002fm3 = 245,
		resqml20__ResqmlUom__1000_x0020m4_x002fd = 246,
		resqml20__ResqmlUom__1E_6_x0020acre_x002eft_x002fbbl = 247,
		resqml20__ResqmlUom__1E_6_x0020bbl_x002fft3 = 248,
		resqml20__ResqmlUom__1E_6_x0020bbl_x002fm3 = 249,
		resqml20__ResqmlUom__1E_6_x0020gal_x005bUS_x005d = 250,
		resqml20__ResqmlUom__1E_6_x0020m3_x002f_x0028m3_x002edegC_x0029 = 251,
		resqml20__ResqmlUom__1E_6_x0020m3_x002f_x0028m3_x002edegF_x0029 = 252,
		resqml20__ResqmlUom__1E_9_x00201_x002fft = 253,
		resqml20__ResqmlUom__1E12_x0020ft3 = 254,
		resqml20__ResqmlUom__1E6_x0020_x0028ft3_x002fd_x0029_x002f_x0028bbl_x002fd_x0029 = 255,
		resqml20__ResqmlUom__1E6_x0020bbl = 256,
		resqml20__ResqmlUom__1E6_x0020bbl_x002f_x0028acre_x002eft_x0029 = 257,
		resqml20__ResqmlUom__1E6_x0020bbl_x002facre = 258,
		resqml20__ResqmlUom__1E6_x0020bbl_x002fd = 259,
		resqml20__ResqmlUom__1E6_x0020Btu_x005bIT_x005d = 260,
		resqml20__ResqmlUom__1E6_x0020Btu_x005bIT_x005d_x002fh = 261,
		resqml20__ResqmlUom__1E6_x0020ft3 = 262,
		resqml20__ResqmlUom__1E6_x0020ft3_x002f_x0028acre_x002eft_x0029 = 263,
		resqml20__ResqmlUom__1E6_x0020ft3_x002fbbl = 264,
		resqml20__ResqmlUom__1E6_x0020ft3_x002fd = 265,
		resqml20__ResqmlUom__1E6_x0020lbm_x002fa = 266,
		resqml20__ResqmlUom__1E6_x0020m3 = 267,
		resqml20__ResqmlUom__1E6_x0020m3_x002fd = 268,
		resqml20__ResqmlUom__1E9_x0020bbl = 269,
		resqml20__ResqmlUom__1E9_x0020ft3 = 270,
		resqml20__ResqmlUom__30_x0020ft = 271,
		resqml20__ResqmlUom__30_x0020m = 272,
		resqml20__ResqmlUom__A_x002eh = 273,
		resqml20__ResqmlUom__A_x002em2 = 274,
		resqml20__ResqmlUom__A_x002es = 275,
		resqml20__ResqmlUom__A_x002es_x002fkg = 276,
		resqml20__ResqmlUom__A_x002es_x002fm3 = 277,
		resqml20__ResqmlUom__A_x002fcm2 = 278,
		resqml20__ResqmlUom__A_x002fft2 = 279,
		resqml20__ResqmlUom__A_x002fm = 280,
		resqml20__ResqmlUom__A_x002fm2 = 281,
		resqml20__ResqmlUom__A_x002fmm = 282,
		resqml20__ResqmlUom__A_x002fmm2 = 283,
		resqml20__ResqmlUom__a_x005bt_x005d = 284,
		resqml20__ResqmlUom__acre = 285,
		resqml20__ResqmlUom__acre_x002eft = 286,
		resqml20__ResqmlUom__ag = 287,
		resqml20__ResqmlUom__aJ = 288,
		resqml20__ResqmlUom__angstrom = 289,
		resqml20__ResqmlUom__at = 290,
		resqml20__ResqmlUom__atm = 291,
		resqml20__ResqmlUom__atm_x002fft = 292,
		resqml20__ResqmlUom__atm_x002fh = 293,
		resqml20__ResqmlUom__atm_x002fhm = 294,
		resqml20__ResqmlUom__atm_x002fm = 295,
		resqml20__ResqmlUom__B_x002eW = 296,
		resqml20__ResqmlUom__b_x002fcm3 = 297,
		resqml20__ResqmlUom__B_x002fm = 298,
		resqml20__ResqmlUom__B_x002fO = 299,
		resqml20__ResqmlUom__bar = 300,
		resqml20__ResqmlUom__bar_x002fh = 301,
		resqml20__ResqmlUom__bar_x002fkm = 302,
		resqml20__ResqmlUom__bar_x002fm = 303,
		resqml20__ResqmlUom__bar2 = 304,
		resqml20__ResqmlUom__bar2_x002fcP = 305,
		resqml20__ResqmlUom__bbl = 306,
		resqml20__ResqmlUom__bbl_x002f_x0028acre_x002eft_x0029 = 307,
		resqml20__ResqmlUom__bbl_x002f_x0028d_x002eacre_x002eft_x0029 = 308,
		resqml20__ResqmlUom__bbl_x002f_x0028d_x002eft_x0029 = 309,
		resqml20__ResqmlUom__bbl_x002f_x0028ft_x002epsi_x002ed_x0029 = 310,
		resqml20__ResqmlUom__bbl_x002f_x0028kPa_x002ed_x0029 = 311,
		resqml20__ResqmlUom__bbl_x002f_x0028psi_x002ed_x0029 = 312,
		resqml20__ResqmlUom__bbl_x002facre = 313,
		resqml20__ResqmlUom__bbl_x002fbbl = 314,
		resqml20__ResqmlUom__bbl_x002fd = 315,
		resqml20__ResqmlUom__bbl_x002fd2 = 316,
		resqml20__ResqmlUom__bbl_x002fft = 317,
		resqml20__ResqmlUom__bbl_x002fft3 = 318,
		resqml20__ResqmlUom__bbl_x002fh = 319,
		resqml20__ResqmlUom__bbl_x002fh2 = 320,
		resqml20__ResqmlUom__bbl_x002fin = 321,
		resqml20__ResqmlUom__bbl_x002fm3 = 322,
		resqml20__ResqmlUom__bbl_x002fmi = 323,
		resqml20__ResqmlUom__bbl_x002fmin = 324,
		resqml20__ResqmlUom__bbl_x002fpsi = 325,
		resqml20__ResqmlUom__bbl_x002fton_x005bUK_x005d = 326,
		resqml20__ResqmlUom__bbl_x002fton_x005bUS_x005d = 327,
		resqml20__ResqmlUom__Bd = 328,
		resqml20__ResqmlUom__bit = 329,
		resqml20__ResqmlUom__bit_x002fs = 330,
		resqml20__ResqmlUom__Bq = 331,
		resqml20__ResqmlUom__Bq_x002fkg = 332,
		resqml20__ResqmlUom__Btu_x005bIT_x005d = 333,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002ein_x002f_x0028h_x002eft2_x002edegF_x0029 = 334,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002eft_x002edegF_x0029 = 335,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002eft2_x0029 = 336,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002eft2_x002edegF_x0029 = 337,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002eft2_x002edegR_x0029 = 338,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002eft3_x0029 = 339,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002eft3_x002edegF_x0029 = 340,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002em2_x002edegC_x0029 = 341,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028hp_x002eh_x0029 = 342,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028lbm_x002edegF_x0029 = 343,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028lbm_x002edegR_x0029 = 344,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028lbmol_x002edegF_x0029 = 345,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028s_x002eft2_x0029 = 346,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028s_x002eft2_x002edegF_x0029 = 347,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028s_x002eft3_x0029 = 348,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028s_x002eft3_x002edegF_x0029 = 349,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002fbbl = 350,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002fft3 = 351,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002fgal_x005bUK_x005d = 352,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002fgal_x005bUS_x005d = 353,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002fh = 354,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002flbm = 355,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002flbmol = 356,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002fmin = 357,
		resqml20__ResqmlUom__Btu_x005bIT_x005d_x002fs = 358,
		resqml20__ResqmlUom__Btu_x005bth_x005d = 359,
		resqml20__ResqmlUom__Btu_x005bUK_x005d = 360,
		resqml20__ResqmlUom__byte = 361,
		resqml20__ResqmlUom__byte_x002fs = 362,
		resqml20__ResqmlUom__C_x002em = 363,
		resqml20__ResqmlUom__C_x002fcm2 = 364,
		resqml20__ResqmlUom__C_x002fcm3 = 365,
		resqml20__ResqmlUom__C_x002fg = 366,
		resqml20__ResqmlUom__C_x002fkg = 367,
		resqml20__ResqmlUom__C_x002fm2 = 368,
		resqml20__ResqmlUom__C_x002fm3 = 369,
		resqml20__ResqmlUom__C_x002fmm2 = 370,
		resqml20__ResqmlUom__C_x002fmm3 = 371,
		resqml20__ResqmlUom__ca = 372,
		resqml20__ResqmlUom__cA = 373,
		resqml20__ResqmlUom__cal_x005bIT_x005d = 374,
		resqml20__ResqmlUom__cal_x005bth_x005d = 375,
		resqml20__ResqmlUom__cal_x005bth_x005d_x002f_x0028g_x002eK_x0029 = 376,
		resqml20__ResqmlUom__cal_x005bth_x005d_x002f_x0028h_x002ecm_x002edegC_x0029 = 377,
		resqml20__ResqmlUom__cal_x005bth_x005d_x002f_x0028h_x002ecm2_x0029 = 378,
		resqml20__ResqmlUom__cal_x005bth_x005d_x002f_x0028h_x002ecm2_x002edegC_x0029 = 379,
		resqml20__ResqmlUom__cal_x005bth_x005d_x002f_x0028h_x002ecm3_x0029 = 380,
		resqml20__ResqmlUom__cal_x005bth_x005d_x002f_x0028mol_x002edegC_x0029 = 381,
		resqml20__ResqmlUom__cal_x005bth_x005d_x002f_x0028s_x002ecm_x002edegC_x0029 = 382,
		resqml20__ResqmlUom__cal_x005bth_x005d_x002f_x0028s_x002ecm2_x002edegC_x0029 = 383,
		resqml20__ResqmlUom__cal_x005bth_x005d_x002f_x0028s_x002ecm3_x0029 = 384,
		resqml20__ResqmlUom__cal_x005bth_x005d_x002fcm3 = 385,
		resqml20__ResqmlUom__cal_x005bth_x005d_x002fg = 386,
		resqml20__ResqmlUom__cal_x005bth_x005d_x002fh = 387,
		resqml20__ResqmlUom__cal_x005bth_x005d_x002fkg = 388,
		resqml20__ResqmlUom__cal_x005bth_x005d_x002flbm = 389,
		resqml20__ResqmlUom__cal_x005bth_x005d_x002fmL = 390,
		resqml20__ResqmlUom__cal_x005bth_x005d_x002fmm3 = 391,
		resqml20__ResqmlUom__cC = 392,
		resqml20__ResqmlUom__ccal_x005bth_x005d = 393,
		resqml20__ResqmlUom__ccgr = 394,
		resqml20__ResqmlUom__cd = 395,
		resqml20__ResqmlUom__cd_x002fm2 = 396,
		resqml20__ResqmlUom__cEuc = 397,
		resqml20__ResqmlUom__ceV = 398,
		resqml20__ResqmlUom__cF = 399,
		resqml20__ResqmlUom__cg = 400,
		resqml20__ResqmlUom__cgauss = 401,
		resqml20__ResqmlUom__cgr = 402,
		resqml20__ResqmlUom__cGy = 403,
		resqml20__ResqmlUom__cH = 404,
		resqml20__ResqmlUom__chain = 405,
		resqml20__ResqmlUom__chain_x005bBnA_x005d = 406,
		resqml20__ResqmlUom__chain_x005bBnB_x005d = 407,
		resqml20__ResqmlUom__chain_x005bCla_x005d = 408,
		resqml20__ResqmlUom__chain_x005bInd37_x005d = 409,
		resqml20__ResqmlUom__chain_x005bSe_x005d = 410,
		resqml20__ResqmlUom__chain_x005bSeT_x005d = 411,
		resqml20__ResqmlUom__chain_x005bUS_x005d = 412,
		resqml20__ResqmlUom__cHz = 413,
		resqml20__ResqmlUom__Ci = 414,
		resqml20__ResqmlUom__cJ = 415,
		resqml20__ResqmlUom__cm = 416,
		resqml20__ResqmlUom__cm_x002fa = 417,
		resqml20__ResqmlUom__cm_x002fs = 418,
		resqml20__ResqmlUom__cm_x002fs2 = 419,
		resqml20__ResqmlUom__cm2 = 420,
		resqml20__ResqmlUom__cm2_x002fg = 421,
		resqml20__ResqmlUom__cm2_x002fs = 422,
		resqml20__ResqmlUom__cm3 = 423,
		resqml20__ResqmlUom__cm3_x002fcm3 = 424,
		resqml20__ResqmlUom__cm3_x002fg = 425,
		resqml20__ResqmlUom__cm3_x002fh = 426,
		resqml20__ResqmlUom__cm3_x002fL = 427,
		resqml20__ResqmlUom__cm3_x002fm3 = 428,
		resqml20__ResqmlUom__cm3_x002fmin = 429,
		resqml20__ResqmlUom__cm3_x002fs = 430,
		resqml20__ResqmlUom__cm4 = 431,
		resqml20__ResqmlUom__cmH2O_x005b4degC_x005d = 432,
		resqml20__ResqmlUom__cN = 433,
		resqml20__ResqmlUom__cohm = 434,
		resqml20__ResqmlUom__cP = 435,
		resqml20__ResqmlUom__cPa = 436,
		resqml20__ResqmlUom__crd = 437,
		resqml20__ResqmlUom__cS = 438,
		resqml20__ResqmlUom__cs = 439,
		resqml20__ResqmlUom__cSt = 440,
		resqml20__ResqmlUom__ct = 441,
		resqml20__ResqmlUom__cT = 442,
		resqml20__ResqmlUom__cu = 443,
		resqml20__ResqmlUom__cV = 444,
		resqml20__ResqmlUom__cW = 445,
		resqml20__ResqmlUom__cWb = 446,
		resqml20__ResqmlUom__cwt_x005bUK_x005d = 447,
		resqml20__ResqmlUom__cwt_x005bUS_x005d = 448,
		resqml20__ResqmlUom__D_x002eft = 449,
		resqml20__ResqmlUom__D_x002em = 450,
		resqml20__ResqmlUom__D_x002f_x0028Pa_x002es_x0029 = 451,
		resqml20__ResqmlUom__d_x002fbbl = 452,
		resqml20__ResqmlUom__D_x002fcP = 453,
		resqml20__ResqmlUom__d_x002fft3 = 454,
		resqml20__ResqmlUom__d_x002fm3 = 455,
		resqml20__ResqmlUom__D_x005bAPI_x005d = 456,
		resqml20__ResqmlUom__dA = 457,
		resqml20__ResqmlUom__dam = 458,
		resqml20__ResqmlUom__daN = 459,
		resqml20__ResqmlUom__daN_x002em = 460,
		resqml20__ResqmlUom__dAPI = 461,
		resqml20__ResqmlUom__dB = 462,
		resqml20__ResqmlUom__dB_x002eMW = 463,
		resqml20__ResqmlUom__dB_x002emW = 464,
		resqml20__ResqmlUom__dB_x002eW = 465,
		resqml20__ResqmlUom__dB_x002fft = 466,
		resqml20__ResqmlUom__dB_x002fkm = 467,
		resqml20__ResqmlUom__dB_x002fm = 468,
		resqml20__ResqmlUom__dB_x002fO = 469,
		resqml20__ResqmlUom__dC = 470,
		resqml20__ResqmlUom__dcal_x005bth_x005d = 471,
		resqml20__ResqmlUom__dega = 472,
		resqml20__ResqmlUom__dega_x002fft = 473,
		resqml20__ResqmlUom__dega_x002fh = 474,
		resqml20__ResqmlUom__dega_x002fm = 475,
		resqml20__ResqmlUom__dega_x002fmin = 476,
		resqml20__ResqmlUom__dega_x002fs = 477,
		resqml20__ResqmlUom__degC = 478,
		resqml20__ResqmlUom__degC_x002em2_x002eh_x002fkcal_x005bth_x005d = 479,
		resqml20__ResqmlUom__degC_x002fft = 480,
		resqml20__ResqmlUom__degC_x002fh = 481,
		resqml20__ResqmlUom__degC_x002fhm = 482,
		resqml20__ResqmlUom__degC_x002fkm = 483,
		resqml20__ResqmlUom__degC_x002fkPa = 484,
		resqml20__ResqmlUom__degC_x002fm = 485,
		resqml20__ResqmlUom__degC_x002fmin = 486,
		resqml20__ResqmlUom__degC_x002fs = 487,
		resqml20__ResqmlUom__degF = 488,
		resqml20__ResqmlUom__degF_x002eft2_x002eh_x002fBtu_x005bIT_x005d = 489,
		resqml20__ResqmlUom__degF_x002fft = 490,
		resqml20__ResqmlUom__degF_x002fh = 491,
		resqml20__ResqmlUom__degF_x002fm = 492,
		resqml20__ResqmlUom__degF_x002fmin = 493,
		resqml20__ResqmlUom__degF_x002fpsi = 494,
		resqml20__ResqmlUom__degF_x002fs = 495,
		resqml20__ResqmlUom__degR = 496,
		resqml20__ResqmlUom__dEuc = 497,
		resqml20__ResqmlUom__deV = 498,
		resqml20__ResqmlUom__dF = 499,
		resqml20__ResqmlUom__dgauss = 500,
		resqml20__ResqmlUom__dGy = 501,
		resqml20__ResqmlUom__dH = 502,
		resqml20__ResqmlUom__dHz = 503,
		resqml20__ResqmlUom__dJ = 504,
		resqml20__ResqmlUom__dm = 505,
		resqml20__ResqmlUom__dm_x002fs = 506,
		resqml20__ResqmlUom__dm3 = 507,
		resqml20__ResqmlUom__dm3_x002f_x0028kW_x002eh_x0029 = 508,
		resqml20__ResqmlUom__dm3_x002fkg = 509,
		resqml20__ResqmlUom__dm3_x002fkmol = 510,
		resqml20__ResqmlUom__dm3_x002fm = 511,
		resqml20__ResqmlUom__dm3_x002fm3 = 512,
		resqml20__ResqmlUom__dm3_x002fMJ = 513,
		resqml20__ResqmlUom__dm3_x002fs = 514,
		resqml20__ResqmlUom__dm3_x002fs2 = 515,
		resqml20__ResqmlUom__dm3_x002ft = 516,
		resqml20__ResqmlUom__dN = 517,
		resqml20__ResqmlUom__dN_x002em = 518,
		resqml20__ResqmlUom__dohm = 519,
		resqml20__ResqmlUom__dP = 520,
		resqml20__ResqmlUom__dPa = 521,
		resqml20__ResqmlUom__drd = 522,
		resqml20__ResqmlUom__ds = 523,
		resqml20__ResqmlUom__dS = 524,
		resqml20__ResqmlUom__dT = 525,
		resqml20__ResqmlUom__dV = 526,
		resqml20__ResqmlUom__dW = 527,
		resqml20__ResqmlUom__dWb = 528,
		resqml20__ResqmlUom__dyne = 529,
		resqml20__ResqmlUom__dyne_x002ecm2 = 530,
		resqml20__ResqmlUom__dyne_x002es_x002fcm2 = 531,
		resqml20__ResqmlUom__dyne_x002fcm = 532,
		resqml20__ResqmlUom__dyne_x002fcm2 = 533,
		resqml20__ResqmlUom__EA = 534,
		resqml20__ResqmlUom__Ea_x005bt_x005d = 535,
		resqml20__ResqmlUom__EC = 536,
		resqml20__ResqmlUom__Ecal_x005bth_x005d = 537,
		resqml20__ResqmlUom__EEuc = 538,
		resqml20__ResqmlUom__EeV = 539,
		resqml20__ResqmlUom__EF = 540,
		resqml20__ResqmlUom__Eg = 541,
		resqml20__ResqmlUom__Egauss = 542,
		resqml20__ResqmlUom__EGy = 543,
		resqml20__ResqmlUom__EH = 544,
		resqml20__ResqmlUom__EHz = 545,
		resqml20__ResqmlUom__EJ = 546,
		resqml20__ResqmlUom__EJ_x002fa = 547,
		resqml20__ResqmlUom__Em = 548,
		resqml20__ResqmlUom__EN = 549,
		resqml20__ResqmlUom__Eohm = 550,
		resqml20__ResqmlUom__EP = 551,
		resqml20__ResqmlUom__EPa = 552,
		resqml20__ResqmlUom__Erd = 553,
		resqml20__ResqmlUom__erg = 554,
		resqml20__ResqmlUom__erg_x002fa = 555,
		resqml20__ResqmlUom__erg_x002fcm2 = 556,
		resqml20__ResqmlUom__erg_x002fcm3 = 557,
		resqml20__ResqmlUom__erg_x002fg = 558,
		resqml20__ResqmlUom__erg_x002fkg = 559,
		resqml20__ResqmlUom__erg_x002fm3 = 560,
		resqml20__ResqmlUom__ES = 561,
		resqml20__ResqmlUom__ET = 562,
		resqml20__ResqmlUom__Euc = 563,
		resqml20__ResqmlUom__eV = 564,
		resqml20__ResqmlUom__EW = 565,
		resqml20__ResqmlUom__EWb = 566,
		resqml20__ResqmlUom__F_x002fm = 567,
		resqml20__ResqmlUom__fa = 568,
		resqml20__ResqmlUom__fA = 569,
		resqml20__ResqmlUom__fathom = 570,
		resqml20__ResqmlUom__fC = 571,
		resqml20__ResqmlUom__fcal_x005bth_x005d = 572,
		resqml20__ResqmlUom__fEuc = 573,
		resqml20__ResqmlUom__feV = 574,
		resqml20__ResqmlUom__fF = 575,
		resqml20__ResqmlUom__fg = 576,
		resqml20__ResqmlUom__fgauss = 577,
		resqml20__ResqmlUom__fGy = 578,
		resqml20__ResqmlUom__fH = 579,
		resqml20__ResqmlUom__fHz = 580,
		resqml20__ResqmlUom__fJ = 581,
		resqml20__ResqmlUom__floz_x005bUK_x005d = 582,
		resqml20__ResqmlUom__floz_x005bUS_x005d = 583,
		resqml20__ResqmlUom__fm = 584,
		resqml20__ResqmlUom__fN = 585,
		resqml20__ResqmlUom__fohm = 586,
		resqml20__ResqmlUom__footcandle = 587,
		resqml20__ResqmlUom__footcandle_x002es = 588,
		resqml20__ResqmlUom__fP = 589,
		resqml20__ResqmlUom__fPa = 590,
		resqml20__ResqmlUom__frd = 591,
		resqml20__ResqmlUom__fS = 592,
		resqml20__ResqmlUom__ft = 593,
		resqml20__ResqmlUom__fT = 594,
		resqml20__ResqmlUom__ft_x002fbbl = 595,
		resqml20__ResqmlUom__ft_x002fd = 596,
		resqml20__ResqmlUom__ft_x002fdegF = 597,
		resqml20__ResqmlUom__ft_x002fft = 598,
		resqml20__ResqmlUom__ft_x002fft3 = 599,
		resqml20__ResqmlUom__ft_x002fgal_x005bUS_x005d = 600,
		resqml20__ResqmlUom__ft_x002fh = 601,
		resqml20__ResqmlUom__ft_x002fin = 602,
		resqml20__ResqmlUom__ft_x002flbm = 603,
		resqml20__ResqmlUom__ft_x002fm = 604,
		resqml20__ResqmlUom__ft_x002fmi = 605,
		resqml20__ResqmlUom__ft_x002fmin = 606,
		resqml20__ResqmlUom__ft_x002fms = 607,
		resqml20__ResqmlUom__ft_x002fpsi = 608,
		resqml20__ResqmlUom__ft_x002fs = 609,
		resqml20__ResqmlUom__ft_x002fs2 = 610,
		resqml20__ResqmlUom__ft_x002fus = 611,
		resqml20__ResqmlUom__ft_x005bBnA_x005d = 612,
		resqml20__ResqmlUom__ft_x005bBnB_x005d = 613,
		resqml20__ResqmlUom__ft_x005bBr36_x005d = 614,
		resqml20__ResqmlUom__ft_x005bBr65_x005d = 615,
		resqml20__ResqmlUom__ft_x005bCla_x005d = 616,
		resqml20__ResqmlUom__ft_x005bGC_x005d = 617,
		resqml20__ResqmlUom__ft_x005bInd_x005d = 618,
		resqml20__ResqmlUom__ft_x005bInd37_x005d = 619,
		resqml20__ResqmlUom__ft_x005bInd62_x005d = 620,
		resqml20__ResqmlUom__ft_x005bInd75_x005d = 621,
		resqml20__ResqmlUom__ft_x005bSe_x005d = 622,
		resqml20__ResqmlUom__ft_x005bSeT_x005d = 623,
		resqml20__ResqmlUom__ft_x005bUS_x005d = 624,
		resqml20__ResqmlUom__ft2 = 625,
		resqml20__ResqmlUom__ft2_x002fh = 626,
		resqml20__ResqmlUom__ft2_x002fin3 = 627,
		resqml20__ResqmlUom__ft2_x002flbm = 628,
		resqml20__ResqmlUom__ft2_x002fs = 629,
		resqml20__ResqmlUom__ft3 = 630,
		resqml20__ResqmlUom__ft3_x002f_x0028d_x002eft_x0029 = 631,
		resqml20__ResqmlUom__ft3_x002f_x0028ft_x002epsi_x002ed_x0029 = 632,
		resqml20__ResqmlUom__ft3_x002f_x0028min_x002eft2_x0029 = 633,
		resqml20__ResqmlUom__ft3_x002f_x0028s_x002eft2_x0029 = 634,
		resqml20__ResqmlUom__ft3_x002fbbl = 635,
		resqml20__ResqmlUom__ft3_x002fd = 636,
		resqml20__ResqmlUom__ft3_x002fd2 = 637,
		resqml20__ResqmlUom__ft3_x002fft = 638,
		resqml20__ResqmlUom__ft3_x002fft2 = 639,
		resqml20__ResqmlUom__ft3_x002fft3 = 640,
		resqml20__ResqmlUom__ft3_x002fh = 641,
		resqml20__ResqmlUom__ft3_x002fh2 = 642,
		resqml20__ResqmlUom__ft3_x002fkg = 643,
		resqml20__ResqmlUom__ft3_x002flbm = 644,
		resqml20__ResqmlUom__ft3_x002flbmol = 645,
		resqml20__ResqmlUom__ft3_x002fmin = 646,
		resqml20__ResqmlUom__ft3_x002fmin2 = 647,
		resqml20__ResqmlUom__ft3_x002frad = 648,
		resqml20__ResqmlUom__ft3_x002fs = 649,
		resqml20__ResqmlUom__ft3_x002fs2 = 650,
		resqml20__ResqmlUom__ft3_x002fsack_x005b94lbm_x005d = 651,
		resqml20__ResqmlUom__fur_x005bUS_x005d = 652,
		resqml20__ResqmlUom__fV = 653,
		resqml20__ResqmlUom__fW = 654,
		resqml20__ResqmlUom__fWb = 655,
		resqml20__ResqmlUom__g_x002eft_x002f_x0028cm3_x002es_x0029 = 656,
		resqml20__ResqmlUom__g_x002em_x002f_x0028cm3_x002es_x0029 = 657,
		resqml20__ResqmlUom__g_x002fcm3 = 658,
		resqml20__ResqmlUom__g_x002fcm4 = 659,
		resqml20__ResqmlUom__g_x002fdm3 = 660,
		resqml20__ResqmlUom__g_x002fgal_x005bUK_x005d = 661,
		resqml20__ResqmlUom__g_x002fgal_x005bUS_x005d = 662,
		resqml20__ResqmlUom__g_x002fkg = 663,
		resqml20__ResqmlUom__g_x002fL = 664,
		resqml20__ResqmlUom__g_x002fm3 = 665,
		resqml20__ResqmlUom__g_x002fmol = 666,
		resqml20__ResqmlUom__g_x002fs = 667,
		resqml20__ResqmlUom__g_x002ft = 668,
		resqml20__ResqmlUom__GA = 669,
		resqml20__ResqmlUom__Ga_x005bt_x005d = 670,
		resqml20__ResqmlUom__Gal = 671,
		resqml20__ResqmlUom__gal_x005bUK_x005d = 672,
		resqml20__ResqmlUom__gal_x005bUK_x005d_x002f_x0028h_x002eft_x0029 = 673,
		resqml20__ResqmlUom__gal_x005bUK_x005d_x002f_x0028h_x002eft2_x0029 = 674,
		resqml20__ResqmlUom__gal_x005bUK_x005d_x002f_x0028h_x002ein_x0029 = 675,
		resqml20__ResqmlUom__gal_x005bUK_x005d_x002f_x0028h_x002ein2_x0029 = 676,
		resqml20__ResqmlUom__gal_x005bUK_x005d_x002f_x0028min_x002eft_x0029 = 677,
		resqml20__ResqmlUom__gal_x005bUK_x005d_x002f_x0028min_x002eft2_x0029 = 678,
		resqml20__ResqmlUom__gal_x005bUK_x005d_x002fd = 679,
		resqml20__ResqmlUom__gal_x005bUK_x005d_x002fft3 = 680,
		resqml20__ResqmlUom__gal_x005bUK_x005d_x002fh = 681,
		resqml20__ResqmlUom__gal_x005bUK_x005d_x002fh2 = 682,
		resqml20__ResqmlUom__gal_x005bUK_x005d_x002flbm = 683,
		resqml20__ResqmlUom__gal_x005bUK_x005d_x002fmi = 684,
		resqml20__ResqmlUom__gal_x005bUK_x005d_x002fmin = 685,
		resqml20__ResqmlUom__gal_x005bUK_x005d_x002fmin2 = 686,
		resqml20__ResqmlUom__gal_x005bUS_x005d = 687,
		resqml20__ResqmlUom__gal_x005bUS_x005d_x002f_x0028h_x002eft_x0029 = 688,
		resqml20__ResqmlUom__gal_x005bUS_x005d_x002f_x0028h_x002eft2_x0029 = 689,
		resqml20__ResqmlUom__gal_x005bUS_x005d_x002f_x0028h_x002ein_x0029 = 690,
		resqml20__ResqmlUom__gal_x005bUS_x005d_x002f_x0028h_x002ein2_x0029 = 691,
		resqml20__ResqmlUom__gal_x005bUS_x005d_x002f_x0028min_x002eft_x0029 = 692,
		resqml20__ResqmlUom__gal_x005bUS_x005d_x002f_x0028min_x002eft2_x0029 = 693,
		resqml20__ResqmlUom__gal_x005bUS_x005d_x002fbbl = 694,
		resqml20__ResqmlUom__gal_x005bUS_x005d_x002fd = 695,
		resqml20__ResqmlUom__gal_x005bUS_x005d_x002fft = 696,
		resqml20__ResqmlUom__gal_x005bUS_x005d_x002fft3 = 697,
		resqml20__ResqmlUom__gal_x005bUS_x005d_x002fh = 698,
		resqml20__ResqmlUom__gal_x005bUS_x005d_x002fh2 = 699,
		resqml20__ResqmlUom__gal_x005bUS_x005d_x002flbm = 700,
		resqml20__ResqmlUom__gal_x005bUS_x005d_x002fmi = 701,
		resqml20__ResqmlUom__gal_x005bUS_x005d_x002fmin = 702,
		resqml20__ResqmlUom__gal_x005bUS_x005d_x002fmin2 = 703,
		resqml20__ResqmlUom__gal_x005bUS_x005d_x002fsack_x005b94lbm_x005d = 704,
		resqml20__ResqmlUom__gal_x005bUS_x005d_x002fton_x005bUK_x005d = 705,
		resqml20__ResqmlUom__gal_x005bUS_x005d_x002fton_x005bUS_x005d = 706,
		resqml20__ResqmlUom__gAPI = 707,
		resqml20__ResqmlUom__gauss = 708,
		resqml20__ResqmlUom__gauss_x002fcm = 709,
		resqml20__ResqmlUom__GBq = 710,
		resqml20__ResqmlUom__GC = 711,
		resqml20__ResqmlUom__Gcal_x005bth_x005d = 712,
		resqml20__ResqmlUom__GEuc = 713,
		resqml20__ResqmlUom__GeV = 714,
		resqml20__ResqmlUom__gf = 715,
		resqml20__ResqmlUom__GF = 716,
		resqml20__ResqmlUom__Gg = 717,
		resqml20__ResqmlUom__Ggauss = 718,
		resqml20__ResqmlUom__GGy = 719,
		resqml20__ResqmlUom__GH = 720,
		resqml20__ResqmlUom__GHz = 721,
		resqml20__ResqmlUom__GJ = 722,
		resqml20__ResqmlUom__Gm = 723,
		resqml20__ResqmlUom__gn = 724,
		resqml20__ResqmlUom__GN = 725,
		resqml20__ResqmlUom__Gohm = 726,
		resqml20__ResqmlUom__gon = 727,
		resqml20__ResqmlUom__GP = 728,
		resqml20__ResqmlUom__GPa = 729,
		resqml20__ResqmlUom__GPa_x002fcm = 730,
		resqml20__ResqmlUom__GPa2 = 731,
		resqml20__ResqmlUom__grain = 732,
		resqml20__ResqmlUom__grain_x002fft3 = 733,
		resqml20__ResqmlUom__grain_x002fgal_x005bUS_x005d = 734,
		resqml20__ResqmlUom__Grd = 735,
		resqml20__ResqmlUom__GS = 736,
		resqml20__ResqmlUom__GT = 737,
		resqml20__ResqmlUom__GV = 738,
		resqml20__ResqmlUom__GW = 739,
		resqml20__ResqmlUom__GW_x002eh = 740,
		resqml20__ResqmlUom__GWb = 741,
		resqml20__ResqmlUom__Gy = 742,
		resqml20__ResqmlUom__h_x002fft3 = 743,
		resqml20__ResqmlUom__h_x002fkm = 744,
		resqml20__ResqmlUom__H_x002fm = 745,
		resqml20__ResqmlUom__h_x002fm3 = 746,
		resqml20__ResqmlUom__ha = 747,
		resqml20__ResqmlUom__ha_x002em = 748,
		resqml20__ResqmlUom__hbar = 749,
		resqml20__ResqmlUom__hg = 750,
		resqml20__ResqmlUom__hL = 751,
		resqml20__ResqmlUom__hm = 752,
		resqml20__ResqmlUom__hN = 753,
		resqml20__ResqmlUom__hp = 754,
		resqml20__ResqmlUom__hp_x002eh = 755,
		resqml20__ResqmlUom__hp_x002eh_x002fbbl = 756,
		resqml20__ResqmlUom__hp_x002eh_x002flbm = 757,
		resqml20__ResqmlUom__hp_x002fft3 = 758,
		resqml20__ResqmlUom__hp_x002fin2 = 759,
		resqml20__ResqmlUom__hp_x005belec_x005d = 760,
		resqml20__ResqmlUom__hp_x005bhyd_x005d = 761,
		resqml20__ResqmlUom__hp_x005bhyd_x005d_x002fin2 = 762,
		resqml20__ResqmlUom__hp_x005bmetric_x005d = 763,
		resqml20__ResqmlUom__hp_x005bmetric_x005d_x002eh = 764,
		resqml20__ResqmlUom__hs = 765,
		resqml20__ResqmlUom__Hz = 766,
		resqml20__ResqmlUom__in = 767,
		resqml20__ResqmlUom__in_x002f_x0028in_x002edegF_x0029 = 768,
		resqml20__ResqmlUom__in_x002fa = 769,
		resqml20__ResqmlUom__in_x002fmin = 770,
		resqml20__ResqmlUom__in_x002fs = 771,
		resqml20__ResqmlUom__in_x002fs2 = 772,
		resqml20__ResqmlUom__in_x005bUS_x005d = 773,
		resqml20__ResqmlUom__in2 = 774,
		resqml20__ResqmlUom__in2_x002fft2 = 775,
		resqml20__ResqmlUom__in2_x002fin2 = 776,
		resqml20__ResqmlUom__in2_x002fs = 777,
		resqml20__ResqmlUom__in3 = 778,
		resqml20__ResqmlUom__in3_x002fft = 779,
		resqml20__ResqmlUom__in4 = 780,
		resqml20__ResqmlUom__inH2O_x005b39degF_x005d = 781,
		resqml20__ResqmlUom__inH2O_x005b60degF_x005d = 782,
		resqml20__ResqmlUom__inHg_x005b32degF_x005d = 783,
		resqml20__ResqmlUom__inHg_x005b60degF_x005d = 784,
		resqml20__ResqmlUom__J_x002em_x002f_x0028s_x002em2_x002eK_x0029 = 785,
		resqml20__ResqmlUom__J_x002em_x002fm2 = 786,
		resqml20__ResqmlUom__J_x002f_x0028g_x002eK_x0029 = 787,
		resqml20__ResqmlUom__J_x002f_x0028kg_x002eK_x0029 = 788,
		resqml20__ResqmlUom__J_x002f_x0028mol_x002eK_x0029 = 789,
		resqml20__ResqmlUom__J_x002f_x0028s_x002em2_x002edegC_x0029 = 790,
		resqml20__ResqmlUom__J_x002fcm2 = 791,
		resqml20__ResqmlUom__J_x002fdm3 = 792,
		resqml20__ResqmlUom__J_x002fg = 793,
		resqml20__ResqmlUom__J_x002fK = 794,
		resqml20__ResqmlUom__J_x002fkg = 795,
		resqml20__ResqmlUom__J_x002fm = 796,
		resqml20__ResqmlUom__J_x002fm2 = 797,
		resqml20__ResqmlUom__J_x002fm3 = 798,
		resqml20__ResqmlUom__J_x002fmol = 799,
		resqml20__ResqmlUom__J_x002fs = 800,
		resqml20__ResqmlUom__K_x002em2_x002fkW = 801,
		resqml20__ResqmlUom__K_x002em2_x002fW = 802,
		resqml20__ResqmlUom__K_x002fkm = 803,
		resqml20__ResqmlUom__K_x002fm = 804,
		resqml20__ResqmlUom__K_x002fPa = 805,
		resqml20__ResqmlUom__K_x002fs = 806,
		resqml20__ResqmlUom__K_x002fW = 807,
		resqml20__ResqmlUom__kA = 808,
		resqml20__ResqmlUom__ka_x005bt_x005d = 809,
		resqml20__ResqmlUom__kC = 810,
		resqml20__ResqmlUom__kcal_x005bth_x005d = 811,
		resqml20__ResqmlUom__kcal_x005bth_x005d_x002em_x002fcm2 = 812,
		resqml20__ResqmlUom__kcal_x005bth_x005d_x002f_x0028h_x002em_x002edegC_x0029 = 813,
		resqml20__ResqmlUom__kcal_x005bth_x005d_x002f_x0028h_x002em2_x002edegC_x0029 = 814,
		resqml20__ResqmlUom__kcal_x005bth_x005d_x002f_x0028kg_x002edegC_x0029 = 815,
		resqml20__ResqmlUom__kcal_x005bth_x005d_x002fcm3 = 816,
		resqml20__ResqmlUom__kcal_x005bth_x005d_x002fg = 817,
		resqml20__ResqmlUom__kcal_x005bth_x005d_x002fh = 818,
		resqml20__ResqmlUom__kcal_x005bth_x005d_x002fkg = 819,
		resqml20__ResqmlUom__kcal_x005bth_x005d_x002fm3 = 820,
		resqml20__ResqmlUom__kcal_x005bth_x005d_x002fmol = 821,
		resqml20__ResqmlUom__kcd = 822,
		resqml20__ResqmlUom__kdyne = 823,
		resqml20__ResqmlUom__kEuc = 824,
		resqml20__ResqmlUom__keV = 825,
		resqml20__ResqmlUom__kF = 826,
		resqml20__ResqmlUom__kg = 827,
		resqml20__ResqmlUom__kg_x002em = 828,
		resqml20__ResqmlUom__kg_x002em_x002fcm2 = 829,
		resqml20__ResqmlUom__kg_x002em_x002fs = 830,
		resqml20__ResqmlUom__kg_x002em2 = 831,
		resqml20__ResqmlUom__kg_x002f_x0028kW_x002eh_x0029 = 832,
		resqml20__ResqmlUom__kg_x002f_x0028m_x002es_x0029 = 833,
		resqml20__ResqmlUom__kg_x002f_x0028m2_x002es_x0029 = 834,
		resqml20__ResqmlUom__kg_x002fd = 835,
		resqml20__ResqmlUom__kg_x002fdm3 = 836,
		resqml20__ResqmlUom__kg_x002fdm4 = 837,
		resqml20__ResqmlUom__kg_x002fh = 838,
		resqml20__ResqmlUom__kg_x002fJ = 839,
		resqml20__ResqmlUom__kg_x002fkg = 840,
		resqml20__ResqmlUom__kg_x002fL = 841,
		resqml20__ResqmlUom__kg_x002fm = 842,
		resqml20__ResqmlUom__kg_x002fm2 = 843,
		resqml20__ResqmlUom__kg_x002fm3 = 844,
		resqml20__ResqmlUom__kg_x002fm4 = 845,
		resqml20__ResqmlUom__kg_x002fmin = 846,
		resqml20__ResqmlUom__kg_x002fMJ = 847,
		resqml20__ResqmlUom__kg_x002fmol = 848,
		resqml20__ResqmlUom__kg_x002fs = 849,
		resqml20__ResqmlUom__kg_x002fsack_x005b94lbm_x005d = 850,
		resqml20__ResqmlUom__kg_x002ft = 851,
		resqml20__ResqmlUom__kgauss = 852,
		resqml20__ResqmlUom__kgf = 853,
		resqml20__ResqmlUom__kgf_x002em = 854,
		resqml20__ResqmlUom__kgf_x002em_x002fcm2 = 855,
		resqml20__ResqmlUom__kgf_x002em_x002fm = 856,
		resqml20__ResqmlUom__kgf_x002em2 = 857,
		resqml20__ResqmlUom__kgf_x002es_x002fm2 = 858,
		resqml20__ResqmlUom__kgf_x002fcm = 859,
		resqml20__ResqmlUom__kgf_x002fcm2 = 860,
		resqml20__ResqmlUom__kgf_x002fkgf = 861,
		resqml20__ResqmlUom__kgf_x002fm2 = 862,
		resqml20__ResqmlUom__kgf_x002fmm2 = 863,
		resqml20__ResqmlUom__kGy = 864,
		resqml20__ResqmlUom__kH = 865,
		resqml20__ResqmlUom__kHz = 866,
		resqml20__ResqmlUom__Kibyte = 867,
		resqml20__ResqmlUom__kJ = 868,
		resqml20__ResqmlUom__kJ_x002em_x002f_x0028h_x002em2_x002eK_x0029 = 869,
		resqml20__ResqmlUom__kJ_x002f_x0028h_x002em2_x002eK_x0029 = 870,
		resqml20__ResqmlUom__kJ_x002f_x0028kg_x002eK_x0029 = 871,
		resqml20__ResqmlUom__kJ_x002f_x0028kmol_x002eK_x0029 = 872,
		resqml20__ResqmlUom__kJ_x002fdm3 = 873,
		resqml20__ResqmlUom__kJ_x002fkg = 874,
		resqml20__ResqmlUom__kJ_x002fkmol = 875,
		resqml20__ResqmlUom__kJ_x002fm3 = 876,
		resqml20__ResqmlUom__klbf = 877,
		resqml20__ResqmlUom__klbm = 878,
		resqml20__ResqmlUom__klbm_x002fin = 879,
		resqml20__ResqmlUom__klx = 880,
		resqml20__ResqmlUom__km = 881,
		resqml20__ResqmlUom__km_x002fcm = 882,
		resqml20__ResqmlUom__km_x002fdm3 = 883,
		resqml20__ResqmlUom__km_x002fh = 884,
		resqml20__ResqmlUom__km_x002fL = 885,
		resqml20__ResqmlUom__km_x002fs = 886,
		resqml20__ResqmlUom__km2 = 887,
		resqml20__ResqmlUom__km3 = 888,
		resqml20__ResqmlUom__kmol = 889,
		resqml20__ResqmlUom__kmol_x002fh = 890,
		resqml20__ResqmlUom__kmol_x002fm3 = 891,
		resqml20__ResqmlUom__kmol_x002fs = 892,
		resqml20__ResqmlUom__kN = 893,
		resqml20__ResqmlUom__kN_x002em = 894,
		resqml20__ResqmlUom__kN_x002em2 = 895,
		resqml20__ResqmlUom__kN_x002fm = 896,
		resqml20__ResqmlUom__kN_x002fm2 = 897,
		resqml20__ResqmlUom__knot = 898,
		resqml20__ResqmlUom__kohm = 899,
		resqml20__ResqmlUom__kohm_x002em = 900,
		resqml20__ResqmlUom__kP = 901,
		resqml20__ResqmlUom__kPa = 902,
		resqml20__ResqmlUom__kPa_x002es_x002fm = 903,
		resqml20__ResqmlUom__kPa_x002fh = 904,
		resqml20__ResqmlUom__kPa_x002fhm = 905,
		resqml20__ResqmlUom__kPa_x002fm = 906,
		resqml20__ResqmlUom__kPa_x002fmin = 907,
		resqml20__ResqmlUom__kPa2 = 908,
		resqml20__ResqmlUom__kPa2_x002fcP = 909,
		resqml20__ResqmlUom__kpsi = 910,
		resqml20__ResqmlUom__kpsi2 = 911,
		resqml20__ResqmlUom__krad = 912,
		resqml20__ResqmlUom__krd = 913,
		resqml20__ResqmlUom__kS = 914,
		resqml20__ResqmlUom__kS_x002fm = 915,
		resqml20__ResqmlUom__kT = 916,
		resqml20__ResqmlUom__kV = 917,
		resqml20__ResqmlUom__kW = 918,
		resqml20__ResqmlUom__kW_x002eh = 919,
		resqml20__ResqmlUom__kW_x002eh_x002f_x0028kg_x002edegC_x0029 = 920,
		resqml20__ResqmlUom__kW_x002eh_x002fdm3 = 921,
		resqml20__ResqmlUom__kW_x002eh_x002fkg = 922,
		resqml20__ResqmlUom__kW_x002eh_x002fm3 = 923,
		resqml20__ResqmlUom__kW_x002f_x0028m2_x002eK_x0029 = 924,
		resqml20__ResqmlUom__kW_x002f_x0028m3_x002eK_x0029 = 925,
		resqml20__ResqmlUom__kW_x002fcm2 = 926,
		resqml20__ResqmlUom__kW_x002fm2 = 927,
		resqml20__ResqmlUom__kW_x002fm3 = 928,
		resqml20__ResqmlUom__kWb = 929,
		resqml20__ResqmlUom__L_x002f_x0028bar_x002emin_x0029 = 930,
		resqml20__ResqmlUom__L_x002fh = 931,
		resqml20__ResqmlUom__L_x002fkg = 932,
		resqml20__ResqmlUom__L_x002fkmol = 933,
		resqml20__ResqmlUom__L_x002fm = 934,
		resqml20__ResqmlUom__L_x002fm3 = 935,
		resqml20__ResqmlUom__L_x002fmin = 936,
		resqml20__ResqmlUom__L_x002fmol = 937,
		resqml20__ResqmlUom__L_x002fs = 938,
		resqml20__ResqmlUom__L_x002fs2 = 939,
		resqml20__ResqmlUom__L_x002ft = 940,
		resqml20__ResqmlUom__L_x002fton_x005bUK_x005d = 941,
		resqml20__ResqmlUom__lbf = 942,
		resqml20__ResqmlUom__lbf_x002eft = 943,
		resqml20__ResqmlUom__lbf_x002eft_x002fbbl = 944,
		resqml20__ResqmlUom__lbf_x002eft_x002fgal_x005bUS_x005d = 945,
		resqml20__ResqmlUom__lbf_x002eft_x002fin = 946,
		resqml20__ResqmlUom__lbf_x002eft_x002fin2 = 947,
		resqml20__ResqmlUom__lbf_x002eft_x002flbm = 948,
		resqml20__ResqmlUom__lbf_x002eft_x002fmin = 949,
		resqml20__ResqmlUom__lbf_x002eft_x002fs = 950,
		resqml20__ResqmlUom__lbf_x002ein = 951,
		resqml20__ResqmlUom__lbf_x002ein_x002fin = 952,
		resqml20__ResqmlUom__lbf_x002ein2 = 953,
		resqml20__ResqmlUom__lbf_x002es_x002fft2 = 954,
		resqml20__ResqmlUom__lbf_x002es_x002fin2 = 955,
		resqml20__ResqmlUom__lbf_x002fft = 956,
		resqml20__ResqmlUom__lbf_x002fft2 = 957,
		resqml20__ResqmlUom__lbf_x002fft3 = 958,
		resqml20__ResqmlUom__lbf_x002fgal_x005bUS_x005d = 959,
		resqml20__ResqmlUom__lbf_x002fin = 960,
		resqml20__ResqmlUom__lbf_x002flbf = 961,
		resqml20__ResqmlUom__lbm = 962,
		resqml20__ResqmlUom__lbm_x002eft = 963,
		resqml20__ResqmlUom__lbm_x002eft_x002fs = 964,
		resqml20__ResqmlUom__lbm_x002eft2 = 965,
		resqml20__ResqmlUom__lbm_x002eft2_x002fs2 = 966,
		resqml20__ResqmlUom__lbm_x002f_x0028ft_x002eh_x0029 = 967,
		resqml20__ResqmlUom__lbm_x002f_x0028ft_x002es_x0029 = 968,
		resqml20__ResqmlUom__lbm_x002f_x0028ft2_x002eh_x0029 = 969,
		resqml20__ResqmlUom__lbm_x002f_x0028ft2_x002es_x0029 = 970,
		resqml20__ResqmlUom__lbm_x002f_x0028gal_x005bUK_x005d_x002eft_x0029 = 971,
		resqml20__ResqmlUom__lbm_x002f_x0028gal_x005bUS_x005d_x002eft_x0029 = 972,
		resqml20__ResqmlUom__lbm_x002f_x0028hp_x002eh_x0029 = 973,
		resqml20__ResqmlUom__lbm_x002fbbl = 974,
		resqml20__ResqmlUom__lbm_x002fd = 975,
		resqml20__ResqmlUom__lbm_x002fft = 976,
		resqml20__ResqmlUom__lbm_x002fft2 = 977,
		resqml20__ResqmlUom__lbm_x002fft3 = 978,
		resqml20__ResqmlUom__lbm_x002fft4 = 979,
		resqml20__ResqmlUom__lbm_x002fgal_x005bUK_x005d = 980,
		resqml20__ResqmlUom__lbm_x002fgal_x005bUS_x005d = 981,
		resqml20__ResqmlUom__lbm_x002fh = 982,
		resqml20__ResqmlUom__lbm_x002fin3 = 983,
		resqml20__ResqmlUom__lbm_x002flbmol = 984,
		resqml20__ResqmlUom__lbm_x002fmin = 985,
		resqml20__ResqmlUom__lbm_x002fs = 986,
		resqml20__ResqmlUom__lbmol = 987,
		resqml20__ResqmlUom__lbmol_x002f_x0028h_x002eft2_x0029 = 988,
		resqml20__ResqmlUom__lbmol_x002f_x0028s_x002eft2_x0029 = 989,
		resqml20__ResqmlUom__lbmol_x002fft3 = 990,
		resqml20__ResqmlUom__lbmol_x002fgal_x005bUK_x005d = 991,
		resqml20__ResqmlUom__lbmol_x002fgal_x005bUS_x005d = 992,
		resqml20__ResqmlUom__lbmol_x002fh = 993,
		resqml20__ResqmlUom__lbmol_x002fs = 994,
		resqml20__ResqmlUom__link = 995,
		resqml20__ResqmlUom__link_x005bBnA_x005d = 996,
		resqml20__ResqmlUom__link_x005bBnB_x005d = 997,
		resqml20__ResqmlUom__link_x005bCla_x005d = 998,
		resqml20__ResqmlUom__link_x005bSe_x005d = 999,
		resqml20__ResqmlUom__link_x005bSeT_x005d = 1000,
		resqml20__ResqmlUom__link_x005bUS_x005d = 1001,
		resqml20__ResqmlUom__lm = 1002,
		resqml20__ResqmlUom__lm_x002es = 1003,
		resqml20__ResqmlUom__lm_x002fm2 = 1004,
		resqml20__ResqmlUom__lm_x002fW = 1005,
		resqml20__ResqmlUom__lx = 1006,
		resqml20__ResqmlUom__lx_x002es = 1007,
		resqml20__ResqmlUom__m_x002f_x0028m_x002eK_x0029 = 1008,
		resqml20__ResqmlUom__m_x002fcm = 1009,
		resqml20__ResqmlUom__m_x002fd = 1010,
		resqml20__ResqmlUom__m_x002fh = 1011,
		resqml20__ResqmlUom__m_x002fK = 1012,
		resqml20__ResqmlUom__m_x002fkg = 1013,
		resqml20__ResqmlUom__m_x002fkm = 1014,
		resqml20__ResqmlUom__m_x002fkPa = 1015,
		resqml20__ResqmlUom__m_x002fm = 1016,
		resqml20__ResqmlUom__m_x002fm3 = 1017,
		resqml20__ResqmlUom__m_x002fmin = 1018,
		resqml20__ResqmlUom__m_x002fms = 1019,
		resqml20__ResqmlUom__m_x002fPa = 1020,
		resqml20__ResqmlUom__m_x002fs = 1021,
		resqml20__ResqmlUom__m_x002fs2 = 1022,
		resqml20__ResqmlUom__m_x005bGer_x005d = 1023,
		resqml20__ResqmlUom__m2 = 1024,
		resqml20__ResqmlUom__m2_x002f_x0028kPa_x002ed_x0029 = 1025,
		resqml20__ResqmlUom__m2_x002f_x0028Pa_x002es_x0029 = 1026,
		resqml20__ResqmlUom__m2_x002fcm3 = 1027,
		resqml20__ResqmlUom__m2_x002fd = 1028,
		resqml20__ResqmlUom__m2_x002fg = 1029,
		resqml20__ResqmlUom__m2_x002fh = 1030,
		resqml20__ResqmlUom__m2_x002fkg = 1031,
		resqml20__ResqmlUom__m2_x002fm2 = 1032,
		resqml20__ResqmlUom__m2_x002fm3 = 1033,
		resqml20__ResqmlUom__m2_x002fmol = 1034,
		resqml20__ResqmlUom__m2_x002fs = 1035,
		resqml20__ResqmlUom__m3 = 1036,
		resqml20__ResqmlUom__m3_x002f_x0028bar_x002ed_x0029 = 1037,
		resqml20__ResqmlUom__m3_x002f_x0028bar_x002eh_x0029 = 1038,
		resqml20__ResqmlUom__m3_x002f_x0028bar_x002emin_x0029 = 1039,
		resqml20__ResqmlUom__m3_x002f_x0028d_x002em_x0029 = 1040,
		resqml20__ResqmlUom__m3_x002f_x0028h_x002em_x0029 = 1041,
		resqml20__ResqmlUom__m3_x002f_x0028ha_x002em_x0029 = 1042,
		resqml20__ResqmlUom__m3_x002f_x0028kPa_x002ed_x0029 = 1043,
		resqml20__ResqmlUom__m3_x002f_x0028kPa_x002eh_x0029 = 1044,
		resqml20__ResqmlUom__m3_x002f_x0028kW_x002eh_x0029 = 1045,
		resqml20__ResqmlUom__m3_x002f_x0028m3_x002eK_x0029 = 1046,
		resqml20__ResqmlUom__m3_x002f_x0028Pa_x002es_x0029 = 1047,
		resqml20__ResqmlUom__m3_x002f_x0028psi_x002ed_x0029 = 1048,
		resqml20__ResqmlUom__m3_x002f_x0028s_x002eft_x0029 = 1049,
		resqml20__ResqmlUom__m3_x002f_x0028s_x002em_x0029 = 1050,
		resqml20__ResqmlUom__m3_x002f_x0028s_x002em2_x0029 = 1051,
		resqml20__ResqmlUom__m3_x002f_x0028s_x002em3_x0029 = 1052,
		resqml20__ResqmlUom__m3_x002fbbl = 1053,
		resqml20__ResqmlUom__m3_x002fd = 1054,
		resqml20__ResqmlUom__m3_x002fd2 = 1055,
		resqml20__ResqmlUom__m3_x002fg = 1056,
		resqml20__ResqmlUom__m3_x002fh = 1057,
		resqml20__ResqmlUom__m3_x002fJ = 1058,
		resqml20__ResqmlUom__m3_x002fkg = 1059,
		resqml20__ResqmlUom__m3_x002fkm = 1060,
		resqml20__ResqmlUom__m3_x002fkmol = 1061,
		resqml20__ResqmlUom__m3_x002fkPa = 1062,
		resqml20__ResqmlUom__m3_x002fm = 1063,
		resqml20__ResqmlUom__m3_x002fm2 = 1064,
		resqml20__ResqmlUom__m3_x002fm3 = 1065,
		resqml20__ResqmlUom__m3_x002fmin = 1066,
		resqml20__ResqmlUom__m3_x002fmol = 1067,
		resqml20__ResqmlUom__m3_x002fPa = 1068,
		resqml20__ResqmlUom__m3_x002frad = 1069,
		resqml20__ResqmlUom__m3_x002frev = 1070,
		resqml20__ResqmlUom__m3_x002fs = 1071,
		resqml20__ResqmlUom__m3_x002fs2 = 1072,
		resqml20__ResqmlUom__m3_x002ft = 1073,
		resqml20__ResqmlUom__m3_x002fton_x005bUK_x005d = 1074,
		resqml20__ResqmlUom__m3_x002fton_x005bUS_x005d = 1075,
		resqml20__ResqmlUom__m4 = 1076,
		resqml20__ResqmlUom__m4_x002fs = 1077,
		resqml20__ResqmlUom__mA = 1078,
		resqml20__ResqmlUom__MA = 1079,
		resqml20__ResqmlUom__mA_x002fcm2 = 1080,
		resqml20__ResqmlUom__mA_x002fft2 = 1081,
		resqml20__ResqmlUom__Ma_x005bt_x005d = 1082,
		resqml20__ResqmlUom__mbar = 1083,
		resqml20__ResqmlUom__MBq = 1084,
		resqml20__ResqmlUom__mC = 1085,
		resqml20__ResqmlUom__MC = 1086,
		resqml20__ResqmlUom__mC_x002fm2 = 1087,
		resqml20__ResqmlUom__Mcal_x005bth_x005d = 1088,
		resqml20__ResqmlUom__mcal_x005bth_x005d = 1089,
		resqml20__ResqmlUom__mCi = 1090,
		resqml20__ResqmlUom__mD = 1091,
		resqml20__ResqmlUom__mD_x002eft = 1092,
		resqml20__ResqmlUom__mD_x002eft2_x002f_x0028lbf_x002es_x0029 = 1093,
		resqml20__ResqmlUom__mD_x002ein2_x002f_x0028lbf_x002es_x0029 = 1094,
		resqml20__ResqmlUom__mD_x002em = 1095,
		resqml20__ResqmlUom__mD_x002f_x0028Pa_x002es_x0029 = 1096,
		resqml20__ResqmlUom__mD_x002fcP = 1097,
		resqml20__ResqmlUom__MEuc = 1098,
		resqml20__ResqmlUom__mEuc = 1099,
		resqml20__ResqmlUom__meV = 1100,
		resqml20__ResqmlUom__MeV = 1101,
		resqml20__ResqmlUom__mF = 1102,
		resqml20__ResqmlUom__MF = 1103,
		resqml20__ResqmlUom__Mg = 1104,
		resqml20__ResqmlUom__mg = 1105,
		resqml20__ResqmlUom__Mg_x002fa = 1106,
		resqml20__ResqmlUom__Mg_x002fd = 1107,
		resqml20__ResqmlUom__mg_x002fdm3 = 1108,
		resqml20__ResqmlUom__mg_x002fg = 1109,
		resqml20__ResqmlUom__mg_x002fgal_x005bUS_x005d = 1110,
		resqml20__ResqmlUom__Mg_x002fh = 1111,
		resqml20__ResqmlUom__Mg_x002fin = 1112,
		resqml20__ResqmlUom__mg_x002fJ = 1113,
		resqml20__ResqmlUom__mg_x002fkg = 1114,
		resqml20__ResqmlUom__mg_x002fL = 1115,
		resqml20__ResqmlUom__Mg_x002fm2 = 1116,
		resqml20__ResqmlUom__Mg_x002fm3 = 1117,
		resqml20__ResqmlUom__mg_x002fm3 = 1118,
		resqml20__ResqmlUom__Mg_x002fmin = 1119,
		resqml20__ResqmlUom__mGal = 1120,
		resqml20__ResqmlUom__Mgauss = 1121,
		resqml20__ResqmlUom__mgauss = 1122,
		resqml20__ResqmlUom__Mgf = 1123,
		resqml20__ResqmlUom__mgn = 1124,
		resqml20__ResqmlUom__MGy = 1125,
		resqml20__ResqmlUom__mGy = 1126,
		resqml20__ResqmlUom__MH = 1127,
		resqml20__ResqmlUom__mH = 1128,
		resqml20__ResqmlUom__mHz = 1129,
		resqml20__ResqmlUom__MHz = 1130,
		resqml20__ResqmlUom__mi = 1131,
		resqml20__ResqmlUom__mi_x002fgal_x005bUK_x005d = 1132,
		resqml20__ResqmlUom__mi_x002fgal_x005bUS_x005d = 1133,
		resqml20__ResqmlUom__mi_x002fh = 1134,
		resqml20__ResqmlUom__mi_x002fin = 1135,
		resqml20__ResqmlUom__mi_x005bnaut_x005d = 1136,
		resqml20__ResqmlUom__mi_x005bnautUK_x005d = 1137,
		resqml20__ResqmlUom__mi_x005bUS_x005d = 1138,
		resqml20__ResqmlUom__mi_x005bUS_x005d2 = 1139,
		resqml20__ResqmlUom__mi2 = 1140,
		resqml20__ResqmlUom__mi3 = 1141,
		resqml20__ResqmlUom__Mibyte = 1142,
		resqml20__ResqmlUom__mil = 1143,
		resqml20__ResqmlUom__mil_x002fa = 1144,
		resqml20__ResqmlUom__mila = 1145,
		resqml20__ResqmlUom__min_ = 1146,
		resqml20__ResqmlUom__min_x002fft = 1147,
		resqml20__ResqmlUom__min_x002fm = 1148,
		resqml20__ResqmlUom__mina = 1149,
		resqml20__ResqmlUom__mJ = 1150,
		resqml20__ResqmlUom__MJ = 1151,
		resqml20__ResqmlUom__MJ_x002fa = 1152,
		resqml20__ResqmlUom__mJ_x002fcm2 = 1153,
		resqml20__ResqmlUom__MJ_x002fkg = 1154,
		resqml20__ResqmlUom__MJ_x002fkmol = 1155,
		resqml20__ResqmlUom__MJ_x002fm = 1156,
		resqml20__ResqmlUom__mJ_x002fm2 = 1157,
		resqml20__ResqmlUom__MJ_x002fm3 = 1158,
		resqml20__ResqmlUom__mL = 1159,
		resqml20__ResqmlUom__mL_x002fgal_x005bUK_x005d = 1160,
		resqml20__ResqmlUom__mL_x002fgal_x005bUS_x005d = 1161,
		resqml20__ResqmlUom__mL_x002fmL = 1162,
		resqml20__ResqmlUom__Mm = 1163,
		resqml20__ResqmlUom__mm = 1164,
		resqml20__ResqmlUom__mm_x002f_x0028mm_x002eK_x0029 = 1165,
		resqml20__ResqmlUom__mm_x002fa = 1166,
		resqml20__ResqmlUom__mm_x002fs = 1167,
		resqml20__ResqmlUom__mm2 = 1168,
		resqml20__ResqmlUom__mm2_x002fmm2 = 1169,
		resqml20__ResqmlUom__mm2_x002fs = 1170,
		resqml20__ResqmlUom__mm3 = 1171,
		resqml20__ResqmlUom__mm3_x002fJ = 1172,
		resqml20__ResqmlUom__mmHg_x005b0degC_x005d = 1173,
		resqml20__ResqmlUom__mmol = 1174,
		resqml20__ResqmlUom__mN = 1175,
		resqml20__ResqmlUom__MN = 1176,
		resqml20__ResqmlUom__mN_x002em2 = 1177,
		resqml20__ResqmlUom__mN_x002fkm = 1178,
		resqml20__ResqmlUom__mN_x002fm = 1179,
		resqml20__ResqmlUom__mohm = 1180,
		resqml20__ResqmlUom__Mohm = 1181,
		resqml20__ResqmlUom__mol = 1182,
		resqml20__ResqmlUom__mol_x002em2_x002f_x0028mol_x002es_x0029 = 1183,
		resqml20__ResqmlUom__mol_x002f_x0028s_x002em2_x0029 = 1184,
		resqml20__ResqmlUom__mol_x002fm2 = 1185,
		resqml20__ResqmlUom__mol_x002fm3 = 1186,
		resqml20__ResqmlUom__mol_x002fmol = 1187,
		resqml20__ResqmlUom__mol_x002fs = 1188,
		resqml20__ResqmlUom__mP = 1189,
		resqml20__ResqmlUom__MP = 1190,
		resqml20__ResqmlUom__MPa = 1191,
		resqml20__ResqmlUom__mPa = 1192,
		resqml20__ResqmlUom__mPa_x002es = 1193,
		resqml20__ResqmlUom__MPa_x002es_x002fm = 1194,
		resqml20__ResqmlUom__MPa_x002fh = 1195,
		resqml20__ResqmlUom__MPa_x002fm = 1196,
		resqml20__ResqmlUom__Mpsi = 1197,
		resqml20__ResqmlUom__mrad = 1198,
		resqml20__ResqmlUom__Mrad = 1199,
		resqml20__ResqmlUom__Mrd = 1200,
		resqml20__ResqmlUom__mrd = 1201,
		resqml20__ResqmlUom__mrem = 1202,
		resqml20__ResqmlUom__mrem_x002fh = 1203,
		resqml20__ResqmlUom__MS = 1204,
		resqml20__ResqmlUom__mS = 1205,
		resqml20__ResqmlUom__ms = 1206,
		resqml20__ResqmlUom__ms_x002fcm = 1207,
		resqml20__ResqmlUom__mS_x002fcm = 1208,
		resqml20__ResqmlUom__ms_x002fft = 1209,
		resqml20__ResqmlUom__ms_x002fin = 1210,
		resqml20__ResqmlUom__mS_x002fm = 1211,
		resqml20__ResqmlUom__ms_x002fm = 1212,
		resqml20__ResqmlUom__ms_x002fs = 1213,
		resqml20__ResqmlUom__mSv = 1214,
		resqml20__ResqmlUom__mSv_x002fh = 1215,
		resqml20__ResqmlUom__mT = 1216,
		resqml20__ResqmlUom__mT_x002fdm = 1217,
		resqml20__ResqmlUom__MV = 1218,
		resqml20__ResqmlUom__mV = 1219,
		resqml20__ResqmlUom__mV_x002fft = 1220,
		resqml20__ResqmlUom__mV_x002fm = 1221,
		resqml20__ResqmlUom__MW = 1222,
		resqml20__ResqmlUom__mW = 1223,
		resqml20__ResqmlUom__MW_x002eh = 1224,
		resqml20__ResqmlUom__MW_x002eh_x002fkg = 1225,
		resqml20__ResqmlUom__MW_x002eh_x002fm3 = 1226,
		resqml20__ResqmlUom__mW_x002fm2 = 1227,
		resqml20__ResqmlUom__mWb = 1228,
		resqml20__ResqmlUom__MWb = 1229,
		resqml20__ResqmlUom__N_x002em = 1230,
		resqml20__ResqmlUom__N_x002em_x002fm = 1231,
		resqml20__ResqmlUom__N_x002em2 = 1232,
		resqml20__ResqmlUom__N_x002es_x002fm2 = 1233,
		resqml20__ResqmlUom__N_x002fm = 1234,
		resqml20__ResqmlUom__N_x002fm2 = 1235,
		resqml20__ResqmlUom__N_x002fm3 = 1236,
		resqml20__ResqmlUom__N_x002fmm2 = 1237,
		resqml20__ResqmlUom__N_x002fN = 1238,
		resqml20__ResqmlUom__nA = 1239,
		resqml20__ResqmlUom__na = 1240,
		resqml20__ResqmlUom__nAPI = 1241,
		resqml20__ResqmlUom__nC = 1242,
		resqml20__ResqmlUom__ncal_x005bth_x005d = 1243,
		resqml20__ResqmlUom__nCi = 1244,
		resqml20__ResqmlUom__nEuc = 1245,
		resqml20__ResqmlUom__neV = 1246,
		resqml20__ResqmlUom__nF = 1247,
		resqml20__ResqmlUom__ng = 1248,
		resqml20__ResqmlUom__ng_x002fg = 1249,
		resqml20__ResqmlUom__ng_x002fmg = 1250,
		resqml20__ResqmlUom__ngauss = 1251,
		resqml20__ResqmlUom__nGy = 1252,
		resqml20__ResqmlUom__nH = 1253,
		resqml20__ResqmlUom__nHz = 1254,
		resqml20__ResqmlUom__nJ = 1255,
		resqml20__ResqmlUom__nm = 1256,
		resqml20__ResqmlUom__nm_x002fs = 1257,
		resqml20__ResqmlUom__nN = 1258,
		resqml20__ResqmlUom__nohm = 1259,
		resqml20__ResqmlUom__nohm_x002emil2_x002fft = 1260,
		resqml20__ResqmlUom__nohm_x002emm2_x002fm = 1261,
		resqml20__ResqmlUom__nP = 1262,
		resqml20__ResqmlUom__nPa = 1263,
		resqml20__ResqmlUom__nrd = 1264,
		resqml20__ResqmlUom__nS = 1265,
		resqml20__ResqmlUom__ns = 1266,
		resqml20__ResqmlUom__ns_x002fft = 1267,
		resqml20__ResqmlUom__ns_x002fm = 1268,
		resqml20__ResqmlUom__nT = 1269,
		resqml20__ResqmlUom__nV = 1270,
		resqml20__ResqmlUom__nW = 1271,
		resqml20__ResqmlUom__nWb = 1272,
		resqml20__ResqmlUom__Oe = 1273,
		resqml20__ResqmlUom__ohm = 1274,
		resqml20__ResqmlUom__ohm_x002ecm = 1275,
		resqml20__ResqmlUom__ohm_x002em = 1276,
		resqml20__ResqmlUom__ohm_x002em2_x002fm = 1277,
		resqml20__ResqmlUom__ohm_x002fm = 1278,
		resqml20__ResqmlUom__ozf = 1279,
		resqml20__ResqmlUom__ozm = 1280,
		resqml20__ResqmlUom__ozm_x005btroy_x005d = 1281,
		resqml20__ResqmlUom__pA = 1282,
		resqml20__ResqmlUom__Pa = 1283,
		resqml20__ResqmlUom__Pa_x002es = 1284,
		resqml20__ResqmlUom__Pa_x002es_x002em3_x002fkg = 1285,
		resqml20__ResqmlUom__Pa_x002es_x002fm3 = 1286,
		resqml20__ResqmlUom__Pa_x002es2_x002fm3 = 1287,
		resqml20__ResqmlUom__Pa_x002fh = 1288,
		resqml20__ResqmlUom__Pa_x002fm = 1289,
		resqml20__ResqmlUom__Pa_x002fm3 = 1290,
		resqml20__ResqmlUom__Pa_x002fs = 1291,
		resqml20__ResqmlUom__Pa2 = 1292,
		resqml20__ResqmlUom__Pa2_x002f_x0028Pa_x002es_x0029 = 1293,
		resqml20__ResqmlUom__pC = 1294,
		resqml20__ResqmlUom__pcal_x005bth_x005d = 1295,
		resqml20__ResqmlUom__pCi = 1296,
		resqml20__ResqmlUom__pCi_x002fg = 1297,
		resqml20__ResqmlUom__pdl = 1298,
		resqml20__ResqmlUom__pdl_x002ecm2 = 1299,
		resqml20__ResqmlUom__pdl_x002eft = 1300,
		resqml20__ResqmlUom__pdl_x002fcm = 1301,
		resqml20__ResqmlUom__pEuc = 1302,
		resqml20__ResqmlUom__peV = 1303,
		resqml20__ResqmlUom__pF = 1304,
		resqml20__ResqmlUom__pg = 1305,
		resqml20__ResqmlUom__pgauss = 1306,
		resqml20__ResqmlUom__pGy = 1307,
		resqml20__ResqmlUom__pHz = 1308,
		resqml20__ResqmlUom__pJ = 1309,
		resqml20__ResqmlUom__pm = 1310,
		resqml20__ResqmlUom__pN = 1311,
		resqml20__ResqmlUom__pohm = 1312,
		resqml20__ResqmlUom__pP = 1313,
		resqml20__ResqmlUom__pPa = 1314,
		resqml20__ResqmlUom__ppk = 1315,
		resqml20__ResqmlUom__ppm = 1316,
		resqml20__ResqmlUom__ppm_x005bmass_x005d = 1317,
		resqml20__ResqmlUom__ppm_x005bvol_x005d = 1318,
		resqml20__ResqmlUom__ppm_x005bvol_x005d_x002fdegC = 1319,
		resqml20__ResqmlUom__ppm_x005bvol_x005d_x002fdegF = 1320,
		resqml20__ResqmlUom__prd = 1321,
		resqml20__ResqmlUom__ps = 1322,
		resqml20__ResqmlUom__pS = 1323,
		resqml20__ResqmlUom__psi = 1324,
		resqml20__ResqmlUom__psi_x002ed_x002fbbl = 1325,
		resqml20__ResqmlUom__psi_x002es = 1326,
		resqml20__ResqmlUom__psi_x002fft = 1327,
		resqml20__ResqmlUom__psi_x002fh = 1328,
		resqml20__ResqmlUom__psi_x002fm = 1329,
		resqml20__ResqmlUom__psi_x002fmin = 1330,
		resqml20__ResqmlUom__psi2 = 1331,
		resqml20__ResqmlUom__psi2_x002ed_x002f_x0028cP_x002eft3_x0029 = 1332,
		resqml20__ResqmlUom__psi2_x002fcP = 1333,
		resqml20__ResqmlUom__pT = 1334,
		resqml20__ResqmlUom__pt_x005bUK_x005d = 1335,
		resqml20__ResqmlUom__pt_x005bUK_x005d_x002f_x0028hp_x002eh_x0029 = 1336,
		resqml20__ResqmlUom__pt_x005bUS_x005d = 1337,
		resqml20__ResqmlUom__pV = 1338,
		resqml20__ResqmlUom__pW = 1339,
		resqml20__ResqmlUom__pWb = 1340,
		resqml20__ResqmlUom__qt_x005bUK_x005d = 1341,
		resqml20__ResqmlUom__qt_x005bUS_x005d = 1342,
		resqml20__ResqmlUom__quad = 1343,
		resqml20__ResqmlUom__quad_x002fa = 1344,
		resqml20__ResqmlUom__rad = 1345,
		resqml20__ResqmlUom__rad_x002fft = 1346,
		resqml20__ResqmlUom__rad_x002fft3 = 1347,
		resqml20__ResqmlUom__rad_x002fm = 1348,
		resqml20__ResqmlUom__rad_x002fm3 = 1349,
		resqml20__ResqmlUom__rad_x002fs = 1350,
		resqml20__ResqmlUom__rad_x002fs2 = 1351,
		resqml20__ResqmlUom__rd = 1352,
		resqml20__ResqmlUom__rem = 1353,
		resqml20__ResqmlUom__rem_x002fh = 1354,
		resqml20__ResqmlUom__rev = 1355,
		resqml20__ResqmlUom__rev_x002fft = 1356,
		resqml20__ResqmlUom__rev_x002fm = 1357,
		resqml20__ResqmlUom__rev_x002fs = 1358,
		resqml20__ResqmlUom__rod_x005bUS_x005d = 1359,
		resqml20__ResqmlUom__rpm = 1360,
		resqml20__ResqmlUom__rpm_x002fs = 1361,
		resqml20__ResqmlUom__s_x002fcm = 1362,
		resqml20__ResqmlUom__s_x002fft = 1363,
		resqml20__ResqmlUom__s_x002fft3 = 1364,
		resqml20__ResqmlUom__s_x002fin = 1365,
		resqml20__ResqmlUom__s_x002fkg = 1366,
		resqml20__ResqmlUom__s_x002fL = 1367,
		resqml20__ResqmlUom__S_x002fm = 1368,
		resqml20__ResqmlUom__s_x002fm = 1369,
		resqml20__ResqmlUom__s_x002fm3 = 1370,
		resqml20__ResqmlUom__s_x002fqt_x005bUK_x005d = 1371,
		resqml20__ResqmlUom__s_x002fqt_x005bUS_x005d = 1372,
		resqml20__ResqmlUom__s_x002fs = 1373,
		resqml20__ResqmlUom__sack_x005b94lbm_x005d = 1374,
		resqml20__ResqmlUom__seca = 1375,
		resqml20__ResqmlUom__section = 1376,
		resqml20__ResqmlUom__sr = 1377,
		resqml20__ResqmlUom__St = 1378,
		resqml20__ResqmlUom__Sv = 1379,
		resqml20__ResqmlUom__Sv_x002fh = 1380,
		resqml20__ResqmlUom__Sv_x002fs = 1381,
		resqml20__ResqmlUom__t_x002fa = 1382,
		resqml20__ResqmlUom__t_x002fd = 1383,
		resqml20__ResqmlUom__t_x002fh = 1384,
		resqml20__ResqmlUom__T_x002fm = 1385,
		resqml20__ResqmlUom__t_x002fm3 = 1386,
		resqml20__ResqmlUom__t_x002fmin = 1387,
		resqml20__ResqmlUom__TA = 1388,
		resqml20__ResqmlUom__Ta_x005bt_x005d = 1389,
		resqml20__ResqmlUom__TBq = 1390,
		resqml20__ResqmlUom__TC = 1391,
		resqml20__ResqmlUom__Tcal_x005bth_x005d = 1392,
		resqml20__ResqmlUom__TD_x005bAPI_x005d = 1393,
		resqml20__ResqmlUom__TD_x005bAPI_x005d_x002em = 1394,
		resqml20__ResqmlUom__TD_x005bAPI_x005d_x002f_x0028Pa_x002es_x0029 = 1395,
		resqml20__ResqmlUom__TEuc = 1396,
		resqml20__ResqmlUom__TeV = 1397,
		resqml20__ResqmlUom__TF = 1398,
		resqml20__ResqmlUom__Tg = 1399,
		resqml20__ResqmlUom__Tgauss = 1400,
		resqml20__ResqmlUom__TGy = 1401,
		resqml20__ResqmlUom__TH = 1402,
		resqml20__ResqmlUom__therm_x005bEC_x005d = 1403,
		resqml20__ResqmlUom__therm_x005bUK_x005d = 1404,
		resqml20__ResqmlUom__therm_x005bUS_x005d = 1405,
		resqml20__ResqmlUom__THz = 1406,
		resqml20__ResqmlUom__TJ = 1407,
		resqml20__ResqmlUom__TJ_x002fa = 1408,
		resqml20__ResqmlUom__Tm = 1409,
		resqml20__ResqmlUom__TN = 1410,
		resqml20__ResqmlUom__Tohm = 1411,
		resqml20__ResqmlUom__ton_x005bUK_x005d = 1412,
		resqml20__ResqmlUom__ton_x005bUK_x005d_x002fa = 1413,
		resqml20__ResqmlUom__ton_x005bUK_x005d_x002fd = 1414,
		resqml20__ResqmlUom__ton_x005bUK_x005d_x002fh = 1415,
		resqml20__ResqmlUom__ton_x005bUK_x005d_x002fmin = 1416,
		resqml20__ResqmlUom__ton_x005bUS_x005d = 1417,
		resqml20__ResqmlUom__ton_x005bUS_x005d_x002fa = 1418,
		resqml20__ResqmlUom__ton_x005bUS_x005d_x002fd = 1419,
		resqml20__ResqmlUom__ton_x005bUS_x005d_x002fft2 = 1420,
		resqml20__ResqmlUom__ton_x005bUS_x005d_x002fh = 1421,
		resqml20__ResqmlUom__ton_x005bUS_x005d_x002fmin = 1422,
		resqml20__ResqmlUom__tonf_x005bUK_x005d = 1423,
		resqml20__ResqmlUom__tonf_x005bUK_x005d_x002eft2 = 1424,
		resqml20__ResqmlUom__tonf_x005bUK_x005d_x002fft = 1425,
		resqml20__ResqmlUom__tonf_x005bUK_x005d_x002fft2 = 1426,
		resqml20__ResqmlUom__tonf_x005bUS_x005d = 1427,
		resqml20__ResqmlUom__tonf_x005bUS_x005d_x002eft = 1428,
		resqml20__ResqmlUom__tonf_x005bUS_x005d_x002eft2 = 1429,
		resqml20__ResqmlUom__tonf_x005bUS_x005d_x002emi = 1430,
		resqml20__ResqmlUom__tonf_x005bUS_x005d_x002emi_x002fbbl = 1431,
		resqml20__ResqmlUom__tonf_x005bUS_x005d_x002emi_x002fft = 1432,
		resqml20__ResqmlUom__tonf_x005bUS_x005d_x002fft = 1433,
		resqml20__ResqmlUom__tonf_x005bUS_x005d_x002fft2 = 1434,
		resqml20__ResqmlUom__tonf_x005bUS_x005d_x002fin2 = 1435,
		resqml20__ResqmlUom__tonRefrig = 1436,
		resqml20__ResqmlUom__torr = 1437,
		resqml20__ResqmlUom__TP = 1438,
		resqml20__ResqmlUom__TPa = 1439,
		resqml20__ResqmlUom__Trd = 1440,
		resqml20__ResqmlUom__TS = 1441,
		resqml20__ResqmlUom__TT = 1442,
		resqml20__ResqmlUom__TV = 1443,
		resqml20__ResqmlUom__TW = 1444,
		resqml20__ResqmlUom__TW_x002eh = 1445,
		resqml20__ResqmlUom__TWb = 1446,
		resqml20__ResqmlUom__uA = 1447,
		resqml20__ResqmlUom__uA_x002fcm2 = 1448,
		resqml20__ResqmlUom__uA_x002fin2 = 1449,
		resqml20__ResqmlUom__ubar = 1450,
		resqml20__ResqmlUom__uC = 1451,
		resqml20__ResqmlUom__ucal_x005bth_x005d = 1452,
		resqml20__ResqmlUom__ucal_x005bth_x005d_x002f_x0028s_x002ecm2_x0029 = 1453,
		resqml20__ResqmlUom__ucal_x005bth_x005d_x002fs = 1454,
		resqml20__ResqmlUom__uCi = 1455,
		resqml20__ResqmlUom__uEuc = 1456,
		resqml20__ResqmlUom__ueV = 1457,
		resqml20__ResqmlUom__uF = 1458,
		resqml20__ResqmlUom__uF_x002fm = 1459,
		resqml20__ResqmlUom__ug = 1460,
		resqml20__ResqmlUom__ug_x002fcm3 = 1461,
		resqml20__ResqmlUom__ug_x002fg = 1462,
		resqml20__ResqmlUom__ug_x002fmg = 1463,
		resqml20__ResqmlUom__ugauss = 1464,
		resqml20__ResqmlUom__uGy = 1465,
		resqml20__ResqmlUom__uH = 1466,
		resqml20__ResqmlUom__uH_x002fm = 1467,
		resqml20__ResqmlUom__uHz = 1468,
		resqml20__ResqmlUom__uJ = 1469,
		resqml20__ResqmlUom__um = 1470,
		resqml20__ResqmlUom__um_x002fs = 1471,
		resqml20__ResqmlUom__um2 = 1472,
		resqml20__ResqmlUom__um2_x002em = 1473,
		resqml20__ResqmlUom__umHg_x005b0degC_x005d = 1474,
		resqml20__ResqmlUom__umol = 1475,
		resqml20__ResqmlUom__uN = 1476,
		resqml20__ResqmlUom__uohm = 1477,
		resqml20__ResqmlUom__uohm_x002fft = 1478,
		resqml20__ResqmlUom__uohm_x002fm = 1479,
		resqml20__ResqmlUom__uP = 1480,
		resqml20__ResqmlUom__uPa = 1481,
		resqml20__ResqmlUom__upsi = 1482,
		resqml20__ResqmlUom__urad = 1483,
		resqml20__ResqmlUom__urd = 1484,
		resqml20__ResqmlUom__us = 1485,
		resqml20__ResqmlUom__uS = 1486,
		resqml20__ResqmlUom__us_x002fft = 1487,
		resqml20__ResqmlUom__us_x002fin = 1488,
		resqml20__ResqmlUom__us_x002fm = 1489,
		resqml20__ResqmlUom__uT = 1490,
		resqml20__ResqmlUom__uV = 1491,
		resqml20__ResqmlUom__uV_x002fft = 1492,
		resqml20__ResqmlUom__uV_x002fm = 1493,
		resqml20__ResqmlUom__uW = 1494,
		resqml20__ResqmlUom__uW_x002fm3 = 1495,
		resqml20__ResqmlUom__uWb = 1496,
		resqml20__ResqmlUom__V_x002fB = 1497,
		resqml20__ResqmlUom__V_x002fdB = 1498,
		resqml20__ResqmlUom__V_x002fm = 1499,
		resqml20__ResqmlUom__W_x002em2_x002eK_x002f_x0028J_x002eK_x0029 = 1500,
		resqml20__ResqmlUom__W_x002f_x0028m_x002eK_x0029 = 1501,
		resqml20__ResqmlUom__W_x002f_x0028m2_x002eK_x0029 = 1502,
		resqml20__ResqmlUom__W_x002f_x0028m2_x002esr_x0029 = 1503,
		resqml20__ResqmlUom__W_x002f_x0028m3_x002eK_x0029 = 1504,
		resqml20__ResqmlUom__W_x002fcm2 = 1505,
		resqml20__ResqmlUom__W_x002fK = 1506,
		resqml20__ResqmlUom__W_x002fkW = 1507,
		resqml20__ResqmlUom__W_x002fm2 = 1508,
		resqml20__ResqmlUom__W_x002fm3 = 1509,
		resqml20__ResqmlUom__W_x002fmm2 = 1510,
		resqml20__ResqmlUom__W_x002fsr = 1511,
		resqml20__ResqmlUom__W_x002fW = 1512,
		resqml20__ResqmlUom__Wb = 1513,
		resqml20__ResqmlUom__Wb_x002em = 1514,
		resqml20__ResqmlUom__Wb_x002fm = 1515,
		resqml20__ResqmlUom__Wb_x002fmm = 1516,
		resqml20__ResqmlUom__wk = 1517,
		resqml20__ResqmlUom__yd = 1518,
		resqml20__ResqmlUom__yd_x005bBnA_x005d = 1519,
		resqml20__ResqmlUom__yd_x005bBnB_x005d = 1520,
		resqml20__ResqmlUom__yd_x005bCla_x005d = 1521,
		resqml20__ResqmlUom__yd_x005bInd_x005d = 1522,
		resqml20__ResqmlUom__yd_x005bInd37_x005d = 1523,
		resqml20__ResqmlUom__yd_x005bInd62_x005d = 1524,
		resqml20__ResqmlUom__yd_x005bInd75_x005d = 1525,
		resqml20__ResqmlUom__yd_x005bSe_x005d = 1526,
		resqml20__ResqmlUom__yd_x005bSeT_x005d = 1527,
		resqml20__ResqmlUom__yd_x005bUS_x005d = 1528,
		resqml20__ResqmlUom__yd2 = 1529,
		resqml20__ResqmlUom__yd3 = 1530
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
	enum eml20__LengthUom {
		eml20__LengthUom__m = 109,
		eml20__LengthUom__0_x002e1_x0020ft = 110,
		eml20__LengthUom__0_x002e1_x0020ft_x005bUS_x005d = 111,
		eml20__LengthUom__0_x002e1_x0020in = 112,
		eml20__LengthUom__0_x002e1_x0020yd = 113,
		eml20__LengthUom__1_x002f16_x0020in = 114,
		eml20__LengthUom__1_x002f2_x0020ft = 115,
		eml20__LengthUom__1_x002f32_x0020in = 116,
		eml20__LengthUom__1_x002f64_x0020in = 117,
		eml20__LengthUom__10_x0020ft = 118,
		eml20__LengthUom__10_x0020in = 119,
		eml20__LengthUom__10_x0020km = 120,
		eml20__LengthUom__100_x0020ft = 121,
		eml20__LengthUom__100_x0020km = 122,
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
	enum eml20__TimeUom {
		eml20__TimeUom__a = 97,
		eml20__TimeUom__d = 100,
		eml20__TimeUom__h = 104,
		eml20__TimeUom__s = 115,
		eml20__TimeUom__1_x002f2_x0020ms = 116,
		eml20__TimeUom__100_x0020ka_x005bt_x005d = 117,
		eml20__TimeUom__a_x005bt_x005d = 118,
		eml20__TimeUom__ca = 119,
		eml20__TimeUom__cs = 120,
		eml20__TimeUom__ds = 121,
		eml20__TimeUom__Ea_x005bt_x005d = 122,
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
	enum eml20__AxisOrder2d {
		eml20__AxisOrder2d__easting_x0020northing = 0,
		eml20__AxisOrder2d__northing_x0020easting = 1,
		eml20__AxisOrder2d__westing_x0020southing = 2,
		eml20__AxisOrder2d__southing_x0020westing = 3,
		eml20__AxisOrder2d__northing_x0020westing = 4,
		eml20__AxisOrder2d__westing_x0020northing = 5
	};
	enum resqml20__GeologicBoundaryKind {
		resqml20__GeologicBoundaryKind__fault = 0,
		resqml20__GeologicBoundaryKind__geobody = 1,
		resqml20__GeologicBoundaryKind__horizon = 2
	};
	enum resqml20__KDirection {
		resqml20__KDirection__down = 0,
		resqml20__KDirection__up = 1,
		resqml20__KDirection__not_x0020monotonic = 2
	};
	enum resqml20__CellShape {
		resqml20__CellShape__tetrahedral = 0,
		resqml20__CellShape__pyramidal = 1,
		resqml20__CellShape__prism = 2,
		resqml20__CellShape__hexahedral = 3,
		resqml20__CellShape__polyhedral = 4
	};
	enum resqml20__SurfaceRole {
		resqml20__SurfaceRole__map = 0,
		resqml20__SurfaceRole__pick = 1
	};
	enum resqml20__ContactSide {
		resqml20__ContactSide__footwall = 0,
		resqml20__ContactSide__hanging_x0020wall = 1,
		resqml20__ContactSide__north = 2,
		resqml20__ContactSide__south = 3,
		resqml20__ContactSide__east = 4,
		resqml20__ContactSide__west = 5,
		resqml20__ContactSide__younger = 6,
		resqml20__ContactSide__older = 7,
		resqml20__ContactSide__both = 8
	};
	enum resqml20__DepositionMode {
		resqml20__DepositionMode__proportional_x0020between_x0020top_x0020and_x0020bottom = 0,
		resqml20__DepositionMode__parallel_x0020to_x0020bottom = 1,
		resqml20__DepositionMode__parallel_x0020to_x0020top = 2,
		resqml20__DepositionMode__parallel_x0020to_x0020another_x0020boundary = 3
	};
	enum resqml20__Domain {
		resqml20__Domain__depth = 0,
		resqml20__Domain__time = 1,
		resqml20__Domain__mixed = 2
	};
	enum resqml20__PillarShape {
		resqml20__PillarShape__vertical = 0,
		resqml20__PillarShape__straight = 1,
		resqml20__PillarShape__curved = 2
	};
	enum resqml20__FluidContact {
		resqml20__FluidContact__free_x0020water_x0020contact = 0,
		resqml20__FluidContact__gas_x0020oil_x0020contact = 1,
		resqml20__FluidContact__gas_x0020water_x0020contact = 2,
		resqml20__FluidContact__seal = 3,
		resqml20__FluidContact__water_x0020oil_x0020contact = 4
	};
}
namespace gsoap_eml2_3
{
	enum resqml22__TimeSetKind {
		resqml22__TimeSetKind__single_x0020time = 0,
		resqml22__TimeSetKind__single_x0020time_x0020series = 1,
		resqml22__TimeSetKind__equivalent_x0020times = 2,
		resqml22__TimeSetKind__not_x0020a_x0020time_x0020set = 3
	};
	enum eml23__WellboreDatumReference {
		eml23__WellboreDatumReference__ground_x0020level = 0,
		eml23__WellboreDatumReference__kelly_x0020bushing = 1,
		eml23__WellboreDatumReference__mean_x0020sea_x0020level = 2,
		eml23__WellboreDatumReference__derrick_x0020floor = 3,
		eml23__WellboreDatumReference__casing_x0020flange = 4,
		eml23__WellboreDatumReference__crown_x0020valve = 5,
		eml23__WellboreDatumReference__rotary_x0020bushing = 6,
		eml23__WellboreDatumReference__rotary_x0020table = 7,
		eml23__WellboreDatumReference__sea_x0020floor = 8,
		eml23__WellboreDatumReference__lowest_x0020astronomical_x0020tide = 9,
		eml23__WellboreDatumReference__mean_x0020higher_x0020high_x0020water = 10,
		eml23__WellboreDatumReference__mean_x0020high_x0020water = 11,
		eml23__WellboreDatumReference__mean_x0020lower_x0020low_x0020water = 12,
		eml23__WellboreDatumReference__mean_x0020low_x0020water = 13,
		eml23__WellboreDatumReference__mean_x0020tide_x0020level = 14,
		eml23__WellboreDatumReference__kickoff_x0020point = 15
	};
	enum resqml22__Shape3d {
		resqml22__Shape3d__sheet = 0,
		resqml22__Shape3d__dyke = 1,
		resqml22__Shape3d__dome = 2,
		resqml22__Shape3d__mushroom = 3,
		resqml22__Shape3d__channel = 4,
		resqml22__Shape3d__delta = 5,
		resqml22__Shape3d__dune = 6,
		resqml22__Shape3d__fan = 7,
		resqml22__Shape3d__reef = 8,
		resqml22__Shape3d__wedge = 9
	};
	enum resqml22__ContactVerb {
		resqml22__ContactVerb__stops = 0,
		resqml22__ContactVerb__interrupts = 1,
		resqml22__ContactVerb__crosses = 2
	};
	enum resqml22__ContactMode {
		resqml22__ContactMode__conformable = 0,
		resqml22__ContactMode__extended = 1,
		resqml22__ContactMode__unconformable = 2
	};
	enum resqml22__Phase {
		resqml22__Phase__aquifer = 0,
		resqml22__Phase__gas_x0020cap = 1,
		resqml22__Phase__oil_x0020column = 2,
		resqml22__Phase__seal = 3
	};
	enum resqml22__LineRole {
		resqml22__LineRole__fault_x0020center_x0020line = 0,
		resqml22__LineRole__pick = 1,
		resqml22__LineRole__inner_x0020ring = 2,
		resqml22__LineRole__outer_x0020ring = 3,
		resqml22__LineRole__trajectory = 4,
		resqml22__LineRole__interpretation_x0020line = 5,
		resqml22__LineRole__contact = 6,
		resqml22__LineRole__depositional_x0020line = 7,
		resqml22__LineRole__erosion_x0020line = 8,
		resqml22__LineRole__contouring = 9,
		resqml22__LineRole__pillar = 10,
		resqml22__LineRole__break_x0020line = 11
	};
	enum resqml22__IndexableElement {
		resqml22__IndexableElement__cells = 0,
		resqml22__IndexableElement__intervals_x0020from_x0020datum = 1,
		resqml22__IndexableElement__column_x0020edges = 2,
		resqml22__IndexableElement__columns = 3,
		resqml22__IndexableElement__contacts = 4,
		resqml22__IndexableElement__coordinate_x0020lines = 5,
		resqml22__IndexableElement__edges = 6,
		resqml22__IndexableElement__edges_x0020per_x0020column = 7,
		resqml22__IndexableElement__enumerated_x0020elements = 8,
		resqml22__IndexableElement__faces = 9,
		resqml22__IndexableElement__faces_x0020per_x0020cell = 10,
		resqml22__IndexableElement__interval_x0020edges = 11,
		resqml22__IndexableElement__intervals = 12,
		resqml22__IndexableElement__I0 = 13,
		resqml22__IndexableElement__I0_x0020edges = 14,
		resqml22__IndexableElement__J0 = 15,
		resqml22__IndexableElement__J0_x0020edges = 16,
		resqml22__IndexableElement__layers = 17,
		resqml22__IndexableElement__lines = 18,
		resqml22__IndexableElement__nodes = 19,
		resqml22__IndexableElement__nodes_x0020per_x0020cell = 20,
		resqml22__IndexableElement__nodes_x0020per_x0020edge = 21,
		resqml22__IndexableElement__nodes_x0020per_x0020face = 22,
		resqml22__IndexableElement__patches = 23,
		resqml22__IndexableElement__pillars = 24,
		resqml22__IndexableElement__regions = 25,
		resqml22__IndexableElement__representation = 26,
		resqml22__IndexableElement__subnodes = 27,
		resqml22__IndexableElement__triangles = 28
	};
	enum eml23__FacetKind {
		eml23__FacetKind__conditions = 0,
		eml23__FacetKind__side = 1,
		eml23__FacetKind__direction = 2,
		eml23__FacetKind__netgross = 3,
		eml23__FacetKind__qualifier = 4,
		eml23__FacetKind__statistics = 5,
		eml23__FacetKind__what = 6
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
	
	class StratigraphicOccurrenceInterpretation;	
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
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::StratigraphicOccurrenceInterpretation, StratigraphicOccurrenceInterpretation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::HorizonInterpretation, HorizonInterpretation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::StratigraphicColumn, StratigraphicColumn)
	};
	
#ifdef SWIGPYTHON
	%rename(resqml2_StratigraphicOccurrenceInterpretation) StratigraphicOccurrenceInterpretation;
#endif
	class StratigraphicOccurrenceInterpretation : public AbstractStratigraphicOrganizationInterpretation
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
		
		unsigned int getStratiOccurrenceCount() const;
		StratigraphicOccurrenceInterpretation* getStratiOccurrence(unsigned int index) const;
		void pushBackStratiOccurrence(StratigraphicOccurrenceInterpretation * stratiOccurence);
		
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
		void pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement elementKind, uint64_t elementCount, uint64_t* elementIndices, EML2_NS::AbstractHdfProxy* proxy, short* supportingRepIndices = nullptr);
		void pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement elementKind0, gsoap_eml2_3::resqml22__IndexableElement elementKind1,
			uint64_t elementCount,
			uint64_t * elementIndices0, uint64_t * elementIndices1,
			EML2_NS::AbstractHdfProxy* proxy) = 0;
		
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
			unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide);
		pushBackInternalShell(unsigned int regionIndex,
			unsigned int internalShellFaceCount,
			unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide);
			
		unsigned int getRegionCount() const final;

		unsigned int getInternalShellCount(unsigned int regionIndex) const final;

		unsigned int getFaceCountOfExternalShell(unsigned int regionIndex) const final;
		unsigned int getFaceCountOfInternalShell(unsigned int regionIndex, unsigned int internalShellIndex) const final;

		RESQML2_NS::AbstractRepresentation* getRepOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const final;
		RESQML2_NS::AbstractRepresentation* getRepOfInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const final;

		unsigned int getRepPatchIndexOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const final;
		unsigned int getRepPatchIndexOfInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const final;

		bool getSideFlagOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const final;
		bool getSideFlagOfInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const final;
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

		void setCellAssociationWithStratigraphicOrganizationInterpretation(uint64_t * stratiUnitIndices, uint64_t nullValue, RESQML2_NS::AbstractStratigraphicOrganizationInterpretation* stratiOrgInterp);
		RESQML2_NS::AbstractStratigraphicOrganizationInterpretation* getStratigraphicOrganizationInterpretation() const;
		bool hasCellStratigraphicUnitIndices() const;
		uint64_t getCellStratigraphicUnitIndices(uint64_t * stratiUnitIndices);
		
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
		
		void setIntervalAssociationWithStratigraphicOrganizationInterpretation(uint64_t * stratiUnitIndices, uint64_t nullValue, RESQML2_NS::AbstractStratigraphicOrganizationInterpretation* stratiOrgInterp, EML2_NS::AbstractHdfProxy * hdfProxy);
		RESQML2_NS::AbstractStratigraphicOrganizationInterpretation* getStratigraphicOrganizationInterpretation() const;
		bool hasIntervalStratigraphicUnitIndices() const;
		uint64_t getIntervalStratigraphicUnitIndices(uint64_t * stratiUnitIndices);
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
		 * @exception	std::out_of_range	 	If @p iCell @c > getICellCount(), @p jCell @c >
		 * 										getJCellCount() or @p kCell @c > getKCellCount().
		 * @exception	std::out_of_range	 	If @p corner @c > 7.
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
		 * @exception	std::out_of_range	 	If @p kInterfaceStart @c > getKCellCount() or @p
		 * 										kInterfaceEnd @c > getKCellCount() + getKGapsCount().
		 * @exception	std::range_error	 	If @p kInterfaceStart @c > @p kInterfaceEnd.
		 * @exception	std::invalid_argument	If @p xyzPoints is @c nullptr.
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
		void getGridConnectionSetInformationFromInterpretationIndex(uint64_t * cellIndexPairs, unsigned short * gridIndexPairs, int * localFaceIndexPairs, unsigned int interpretationIndex) const;
		bool hasLocalFacePerCell() const;
		int64_t getLocalFacePerCellIndexPairs(int * localFacePerCellIndexPairs) const;
		bool isBasedOnMultiGrids() const;
		void getGridIndexPairs(unsigned short * gridIndexPairs) const;
		
		void pushBackSupportingGridRepresentation(AbstractGridRepresentation * supportingGridRep);
		
		void setCellIndexPairs(uint64_t cellIndexPairCount, uint64_t * cellIndexPair, uint64_t cellIndexPairNullValue, EML2_NS::AbstractHdfProxy * proxy);
		void setCellIndexPairs(uint64_t cellIndexPairCount, uint64_t * cellIndexPair, uint64_t cellIndexPairNullValue, EML2_NS::AbstractHdfProxy * proxy, unsigned short gridIndexPairNullValue, unsigned short * gridIndexPair);
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
		int64_t getCellIndices(uint64_t * cellIndices) const;

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
	
	class AbstractProperty;
#ifdef SWIGPYTHON
	%rename(resqml2_PropertySet) PropertySet;
#endif
	class PropertySet : public COMMON_NS::AbstractObject
	{
	public:
		void setParent(PropertySet * parent);
		PropertySet * getParent() const;

		unsigned int getChildrenCount() const;
		PropertySet* getChildren(unsigned int index) const;

		void pushBackProperty(RESQML2_NS::AbstractProperty * prop);

		unsigned int getPropertyCount() const;
		AbstractProperty* getProperty(unsigned int index) const;

		bool hasMultipleRealizations() const;
		bool hasSinglePropertyKind() const;
		gsoap_eml2_3::resqml22__TimeSetKind getTimeSetKind() const;
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
		void setRealizationIndices(uint64_t startRealizationIndex, uint64_t countRealizationIndices);
		void setRealizationIndices(const std::vector<unsigned int> & realizationIndices, EML2_NS::AbstractHdfProxy* hdfProxy = nullptr);
		
		void setTimeSeries(EML2_NS::TimeSeries * ts);
		EML2_NS::TimeSeries* getTimeSeries() const;
		void setTimeIndices(uint64_t startTimeIndex, uint64_t countTimeIndices, EML2_NS::TimeSeries* ts, bool useInterval = false);
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
		 * Gets all the values of a given patch of this instance. Values are supposed to be unsigned
		 * long ones.
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
		uint64_t getULongValuesOfPatch(unsigned int patchIndex, uint64_t * values) const;

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
	
#ifdef SWIGPYTHON
	%rename(resqml2_WellboreMarkerFrameRepresentation) WellboreMarkerFrameRepresentation;
#endif
	class WellboreMarkerFrameRepresentation : public WellboreFrameRepresentation
	{
	public:		
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::WellboreMarker, WellboreMarker)
		void setIntervalStratigraphicUnits(unsigned int * stratiUnitIndices, unsigned int nullValue, class StratigraphicOccurrenceInterpretation* stratiOccurrenceInterp, EML2_NS::AbstractHdfProxy* proxy);
		StratigraphicOccurrenceInterpretation* getStratigraphicOccurrenceInterpretation();
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
