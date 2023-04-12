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
#include "../src/eml2_3/Activity.h"
#include "../src/eml2_3/ActivityTemplate.h"
#include "../src/eml2_3/GraphicalInformationSet.h"
#include "../src/eml2_3/PropertyKind.h"
#include "../src/eml2_3/TimeSeries.h"
%}

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace EML2_3_NS::Activity;
	%nspace EML2_3_NS::ActivityTemplate;
	%nspace EML2_3_NS::GraphicalInformationSet;
	%nspace EML2_3_NS::PropertyKind;
	%nspace EML2_3_NS::TimeSeries;
#endif

namespace std {
	%template(GraphicalInformationSetVector) vector<EML2_3_NS::GraphicalInformationSet*>;
}

namespace gsoap_eml2_3 {
	enum class eml23__IndexableElement {
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
	enum class eml23__LengthUom {
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
		mm = 174,
		Mm = 175,
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
	enum class eml23__MassPerLengthUom {
		kg_x002em_x002fcm2 = 0,
		kg_x002fm = 1,
		klbm_x002fin = 2,
		lbm_x002fft = 3,
		Mg_x002fin = 4
	};
	enum class eml23__PlaneAngleUom {
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
}

namespace EML2_3_NS
{
	%nodefaultctor; // Disable creation of default constructors

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Eml23_Activity) Activity;
#endif
	class Activity : public EML2_NS::Activity
	{
	public:
	};	
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Eml23_ActivityTemplate) ActivityTemplate;
#endif
	class ActivityTemplate : public EML2_NS::ActivityTemplate
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Eml23_GraphicalInformationSet) GraphicalInformationSet;
#endif
	class GraphicalInformationSet : public EML2_NS::GraphicalInformationSet
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Eml23_PropertyKind) PropertyKind;
#endif
	class PropertyKind : public EML2_NS::PropertyKind
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Eml23_TimeSeries) TimeSeries;
#endif
	class TimeSeries : public EML2_NS::TimeSeries
	{
	public:
	};
	
}
