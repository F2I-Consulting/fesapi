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
#include "../src/eml2_3/HdfProxy.h"
#include "../src/eml2_3/PropertyKind.h"
#include "../src/eml2_3/TimeSeries.h"
%}

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace EML2_3_NS::Activity;
	%nspace EML2_3_NS::ActivityTemplate;
	%nspace EML2_3_NS::GraphicalInformationSet;
	%nspace EML2_3_NS::HdfProxy;
	%nspace EML2_3_NS::PropertyKind;
	%nspace EML2_3_NS::TimeSeries;
#endif

namespace EML2_3_NS
{
	%nodefaultctor; // Disable creation of default constructors

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Activity_eml23) Activity;
#endif
	class Activity : public EML2_NS::Activity
	{
	public:
	};	
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(ActivityTemplate_eml23) ActivityTemplate;
#endif
	class ActivityTemplate : public EML2_NS::ActivityTemplate
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(GraphicalInformationSet_eml23) GraphicalInformationSet;
#endif
	class GraphicalInformationSet : public EML2_NS::GraphicalInformationSet
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(HdfProxy_eml23) HdfProxy;
#endif
	class HdfProxy : public EML2_NS::HdfProxy
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(PropertyKind_eml23) PropertyKind;
#endif
	class PropertyKind : public EML2_NS::PropertyKind
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(TimeSeries_eml23) TimeSeries;
#endif
	class TimeSeries : public EML2_NS::TimeSeries
	{
	public:
	};
	
}
