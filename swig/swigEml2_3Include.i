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
#include "../src/eml2_3/ColumnBasedTable.h"
#include "../src/eml2_3/GraphicalInformationSet.h"
#include "../src/eml2_3/LocalEngineeringCompoundCrs.h"
#include "../src/eml2_3/PropertyKind.h"
#include "../src/eml2_3/ReferencePointInALocalEngineeringCompoundCrs.h"
#include "../src/eml2_3/TimeSeries.h"
%}

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace EML2_3_NS::Activity;
	%nspace EML2_3_NS::ActivityTemplate;
	%nspace EML2_3_NS::ColumnBasedTable;
	%nspace EML2_3_NS::GraphicalInformationSet;
	%nspace EML2_3_NS::LocalEngineeringCompoundCrs;
	%nspace EML2_3_NS::PropertyKind;
	%nspace EML2_3_NS::ReferencePointInALocalEngineeringCompoundCrs;
	%nspace EML2_3_NS::TimeSeries;
#endif

namespace std {
	%template(GraphicalInformationSetVector) vector<EML2_3_NS::GraphicalInformationSet*>;
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
	%rename(Eml23_ColumnBasedTable) ColumnBasedTable;
#endif
	class ColumnBasedTable : public EML2_NS::ColumnBasedTable
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
	%rename(Eml23_LocalEngineeringCompoundCrs) LocalEngineeringCompoundCrs;
#endif
	class LocalEngineeringCompoundCrs : public EML2_NS::LocalEngineeringCompoundCrs
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
	%rename(Eml23_ReferencePointInALocalEngineeringCompoundCrs) ReferencePointInALocalEngineeringCompoundCrs;
#endif
	class ReferencePointInALocalEngineeringCompoundCrs : public EML2_NS::ReferencePointInALocalEngineeringCompoundCrs
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
