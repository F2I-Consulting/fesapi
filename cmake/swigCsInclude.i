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
/**********************************************************************
This file add special SWIG management of the C++ polymorphic datatype.
Basically this file add methods resqml2_0_instantiate* which will create the right C# instance according to what it is exactly.
**********************************************************************/

%pragma(csharp) imclasscode=%{
	
	private enum DataObjectName {
        ACTIVITY,
		ACTIVITYTEMPLATE,
		BOUNDARYFEATURE,
		BOUNDARYFEATUREINTERPRETATION,		
		CATEGORICALPROPERTY,
		CHANNEL,
		CHANNELSET,
		CMPLINEFEATURE,
		COMMENTPROPERTY,
		CONTINUOUSCOLORMAP,
		CONTINUOUSPROPERTY,
		CULTURALFEATURE,
		DEVIATIONSURVEYREPRESENTATION,
		DISCRETECOLORMAP,
		DISCRETEPROPERTY,
		DOUBLETABLELOOKUP,
		EARTHMODELINTERPRETATION,
		EPCEXTERNALPARTREFERENCE,
		FAULTINTERPRETATION,
		FLUIDBOUNDARYFEATURE,
		FLUIDCHARACTERIZATION,
		FLUIDSYSTEM,
		FRONTIERFEATURE,
		GENERICFEATUREINTERPRETATION,
		GENETICBOUNDARYFEATURE,
		GEOBODYBOUNDARYINTERPRETATION,
		GEOBODYFEATURE,
		GEOBODYINTERPRETATION,
		GEOLOGICUNITFEATURE,
		GRAPHICALINFORMATIONSET,
		GRID2DREPRESENTATION,
		GRIDCONNECTIONSETREPRESENTATION,
		HORIZONINTERPRETATION,
		IJKGRIDREPRESENTATION,
		LOCALDEPTH3DCRS,
		LOCALTIME3DCRS,
		LOG,
		MDDATUM,
		MODEL,
		NONSEALEDSURFACEFRAMEWORKREPRESENTATION,
		ORGANIZATIONFEATURE,
		PLANESETREPRESENTATION,
		POINTSETREPRESENTATION,
		POINTSPROPERTY,
		POLYLINEREPRESENTATION,
		POLYLINESETREPRESENTATION,
		PROPERTYKIND,
		PROPERTYSET,
		REPRESENTATIONSETREPRESENTATION,
		ROCKFLUIDORGANIZATIONINTERPRETATION,
		ROCKFLUIDUNITINTERPRETATION,
		ROCKVOLUMEFEATURE,
		SEALEDSURFACEFRAMEWORKREPRESENTATION,
		SEALEDVOLUMEFRAMEWORKREPRESENTATION,
		SEISMICLATTICEFEATURE,
		SEISMICLINEFEATURE,
		SEISMICLINESETFEATURE,
		SEISMICWELLBOREFRAMEREPRESENTATION,
		SHOTPOINTLINEFEATURE,
		STRATIGRAPHICCOLUMN,
		STRATIGRAPHICCOLUMNRANKINTERPRETATION,
		STRATIGRAPHICOCCURRENCEINTERPRETATION,
		STRATIGRAPHICUNITFEATURE,
		STRATIGRAPHICUNITINTERPRETATION,
		STRINGTABLELOOKUP,
		STRUCTURALORGANIZATIONINTERPRETATION,
		SUBREPRESENTATION,
		TECTONICBOUNDARYFEATURE,
		TIMESERIES,
		TIMESERIESDATA,
		TRAJECTORY,
		TRIANGULATEDSETREPRESENTATION,
		UNSTRUCTUREDGRIDREPRESENTATION,
		WELL,
		WELLBORE,
		WELLBORECOMPLETION,
		WELLBOREFEATURE,
		WELLBOREFRAMEREPRESENTATION,
		WELLBOREGEOMETRY,
		WELLBOREINTERPRETATION,
		WELLBOREMARKER,
		WELLBOREMARKERFRAMEREPRESENTATION,
		WELLBORETRAJECTORYREPRESENTATION,
		WELLCOMPLETION
    }
	
	public static f2i.energisticsStandardsApi.${FESAPI_EML2_NS}.Activity eml2_instantiateActivity(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.Activity(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("eml23")) {
			return new f2i.energisticsStandardsApi.${FESAPI_EML2_3_NS}.Activity(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_EML2_NS}.ActivityTemplate eml2_instantiateActivityTemplate(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.ActivityTemplate(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("eml23")) {
			return new f2i.energisticsStandardsApi.${FESAPI_EML2_3_NS}.ActivityTemplate(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_EML2_NS}.AbstractHdfProxy eml2_instantiateEpcExternalPartReference(global::System.IntPtr cPtr, bool owner)
	{
		return new f2i.energisticsStandardsApi.${FESAPI_EML2_NS}.AbstractHdfProxy(cPtr, owner);
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_EML2_NS}.PropertyKind eml2_instantiatePropertyKind(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PropertyKind(cPtr, owner);
		}
		else if (xmlNs.Equals("eml21")) {
			return new f2i.energisticsStandardsApi.${FESAPI_EML2_1_NS}.PropertyKind(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("eml23")) {
			return new f2i.energisticsStandardsApi.${FESAPI_EML2_3_NS}.PropertyKind(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_EML2_NS}.TimeSeries eml2_instantiateTimeSeries(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.TimeSeries(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("eml23")) {
			return new f2i.energisticsStandardsApi.${FESAPI_EML2_3_NS}.TimeSeries(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.BoundaryFeature resqml2_instantiateBoundaryFeature(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.BoundaryFeature(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.BoundaryFeature(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.WellboreFeature resqml2_instantiateWellboreFeature(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreFeature(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.WellboreFeature(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.SeismicLatticeFeature resqml2_instantiateSeismicLatticeFeature(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SeismicLatticeFeature(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.SeismicLatticeFeature(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.SeismicLineSetFeature resqml2_instantiateSeismicLineSetFeature(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SeismicLineSetFeature(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.SeismicLineSetFeature(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.StratigraphicColumn resqml2_instantiateStratigraphicColumn(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicColumn(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.StratigraphicColumn(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.BoundaryFeatureInterpretation resqml2_instantiateBoundaryFeatureInterpretation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.BoundaryFeatureInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.BoundaryFeatureInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.EarthModelInterpretation resqml2_instantiateEarthModelInterpretation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.EarthModelInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.EarthModelInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.FaultInterpretation resqml2_instantiateFaultInterpretation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.FaultInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.FaultInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.GeobodyBoundaryInterpretation resqml2_instantiateGeobodyBoundaryInterpretation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeobodyBoundaryInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.GeobodyBoundaryInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.GeobodyInterpretation resqml2_instantiateGeobodyInterpretation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeobodyInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.GeobodyInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.GenericFeatureInterpretation resqml2_instantiateGenericFeatureInterpretation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GenericFeatureInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.GenericFeatureInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.HorizonInterpretation resqml2_instantiateHorizonInterpretation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.HorizonInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.HorizonInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.StratigraphicColumnRankInterpretation resqml2_instantiateStratigraphicColumnRankInterpretation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicColumnRankInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.StratigraphicColumnRankInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.StratigraphicOccurrenceInterpretation resqml2_instantiateStratigraphicOccurrenceInterpretation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicOccurrenceInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.StratigraphicOccurrenceInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.StratigraphicUnitInterpretation resqml2_instantiateStratigraphicUnitInterpretation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicUnitInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.StratigraphicUnitInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.StructuralOrganizationInterpretation resqml2_instantiateStructuralOrganizationInterpretation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StructuralOrganizationInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.StructuralOrganizationInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.WellboreInterpretation resqml2_instantiateWellboreInterpretation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.WellboreInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.DeviationSurveyRepresentation resqml2_instantiateDeviationSurveyRepresentation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.DeviationSurveyRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.DeviationSurveyRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.Grid2dRepresentation resqml2_instantiateGrid2dRepresentation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.Grid2dRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.Grid2dRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.GridConnectionSetRepresentation resqml2_instantiateGridConnectionSetRepresentation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GridConnectionSetRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.GridConnectionSetRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.NonSealedSurfaceFrameworkRepresentation resqml2_instantiateNonSealedSurfaceFrameworkRepresentation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.NonSealedSurfaceFrameworkRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.NonSealedSurfaceFrameworkRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.SealedSurfaceFrameworkRepresentation resqml2_instantiateSealedSurfaceFrameworkRepresentation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SealedSurfaceFrameworkRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.SealedSurfaceFrameworkRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.SealedVolumeFrameworkRepresentation resqml2_instantiateSealedVolumeFrameworkRepresentation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SealedVolumeFrameworkRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.SealedVolumeFrameworkRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.PlaneSetRepresentation resqml2_instantiatePlaneSetRepresentation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PlaneSetRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.PlaneSetRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.PointSetRepresentation resqml2_instantiatePointSetRepresentation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PointSetRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.PointSetRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.PointsProperty resqml2_instantiatePointsProperty(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PointsProperty(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.PointsProperty(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.PolylineRepresentation resqml2_instantiatePolylineRepresentation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PolylineRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.PolylineRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.PolylineSetRepresentation resqml2_instantiatePolylineSetRepresentation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PolylineSetRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.PolylineSetRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.RepresentationSetRepresentation resqml2_instantiateRepresentationSetRepresentation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.RepresentationSetRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.RepresentationSetRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.RockFluidOrganizationInterpretation resqml2_instantiateRockFluidOrganizationInterpretation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.RockFluidOrganizationInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.RockFluidOrganizationInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.RockFluidUnitInterpretation resqml2_instantiateRockFluidUnitInterpretation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.RockFluidUnitInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.RockFluidUnitInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.SubRepresentation resqml2_instantiateSubRepresentation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SubRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.SubRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.TriangulatedSetRepresentation resqml2_instantiateTriangulatedSetRepresentation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.TriangulatedSetRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.TriangulatedSetRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.UnstructuredGridRepresentation resqml2_instantiateUnstructuredGridRepresentation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.UnstructuredGridRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.UnstructuredGridRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.WellboreTrajectoryRepresentation resqml2_instantiateWellboreTrajectoryRepresentation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreTrajectoryRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.WellboreTrajectoryRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
  
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation resqml2_instantiateConcreteIjkGridRepresentation(global::System.IntPtr cPtr, bool owner)
	{
		if (cPtr == global::System.IntPtr.Zero) {
		  return null;
		}
		
		int type = fesapiPINVOKE.${FESAPI_RESQML2_NS}_AbstractIjkGridRepresentation_getGeometryKind(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (type == (int)f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation.geometryKind.EXPLICIT) {
			if (xmlNs.Equals("resqml20")) {
				return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.IjkGridExplicitRepresentation(cPtr, owner);
			}
${COMMENT_START}
			else if (xmlNs.Equals("resqml22")) {
				return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.IjkGridExplicitRepresentation(cPtr, owner);
			}
${COMMENT_END}
		}
		else if (type == (int)f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation.geometryKind.PARAMETRIC) {
			if (xmlNs.Equals("resqml20")) {
				return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.IjkGridParametricRepresentation(cPtr, owner);
			}
${COMMENT_START}
			else if (xmlNs.Equals("resqml22")) {
				return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.IjkGridParametricRepresentation(cPtr, owner);
			}
${COMMENT_END}
		}
		else if (type == (int)f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation.geometryKind.LATTICE) {
			if (xmlNs.Equals("resqml20")) {
				return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.IjkGridLatticeRepresentation(cPtr, owner);
			}
${COMMENT_START}
			else if (xmlNs.Equals("resqml22")) {
				return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.IjkGridLatticeRepresentation(cPtr, owner);
			}
${COMMENT_END}
		}
		else // TODO : see if it is possible to return the object itself instead of a copy.
		{
		  return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation(cPtr, owner);
		}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.CategoricalProperty resqml2_instantiateCategoricalProperty(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.CategoricalProperty(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.CategoricalProperty(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.CommentProperty resqml2_instantiateCommentProperty(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.CommentProperty(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.CommentProperty(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.ContinuousProperty resqml2_instantiateContinuousProperty(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.ContinuousProperty(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.ContinuousProperty(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.DiscreteProperty resqml2_instantiateDiscreteProperty(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.DiscreteProperty(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.DiscreteProperty(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.WellboreFrameRepresentation resqml2_instantiateWellboreFrameRepresentation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreFrameRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.WellboreFrameRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.WellboreMarker resqml2_instantiateWellboreMarker(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreMarker(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.WellboreMarker(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.WellboreMarkerFrameRepresentation resqml2_instantiateWellboreMarkerFrameRepresentation(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreMarkerFrameRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.WellboreMarkerFrameRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.LocalDepth3dCrs resqml2_instantiateLocalDepth3dCrs(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.LocalDepth3dCrs(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.LocalDepth3dCrs(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.LocalTime3dCrs resqml2_instantiateLocalTime3dCrs(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.LocalTime3dCrs(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.LocalTime3dCrs(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.DoubleTableLookup resqml2_instantiateDoubleTableLookup(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.DoubleTableLookup(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.DoubleTableLookup(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.StringTableLookup resqml2_instantiateStringTableLookup(global::System.IntPtr cPtr, bool owner)
	{
		string xmlNs = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
		if (xmlNs.Equals("resqml20")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StringTableLookup(cPtr, owner);
		}
${COMMENT_START}
		else if (xmlNs.Equals("resqml22")) {
			return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.StringTableLookup(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}

  public static f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject eml2_instantiateConcreteObject(global::System.IntPtr cPtr, bool owner)
  {
	f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject ret = null;
	if (cPtr == global::System.IntPtr.Zero) {
		return ret;
	}

	string type = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
    DataObjectName dataObjName = (DataObjectName) System.Enum.Parse(typeof(DataObjectName), type, true);
	switch (dataObjName) {
		case DataObjectName.ACTIVITY : return eml2_instantiateActivity(cPtr, owner);
		case DataObjectName.ACTIVITYTEMPLATE : return eml2_instantiateActivityTemplate(cPtr, owner);
		case DataObjectName.BOUNDARYFEATURE : return resqml2_instantiateBoundaryFeature(cPtr, owner);
		case DataObjectName.BOUNDARYFEATUREINTERPRETATION : return resqml2_instantiateBoundaryFeatureInterpretation(cPtr, owner);
		case DataObjectName.CATEGORICALPROPERTY : return resqml2_instantiateCategoricalProperty(cPtr, owner);
		case DataObjectName.CHANNEL : return new f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.Channel(cPtr, owner);
		case DataObjectName.CHANNELSET : return new f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.ChannelSet(cPtr, owner);
${COMMENT_START}
		case DataObjectName.CMPLINEFEATURE : return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.CmpLineFeature(cPtr, owner);
${COMMENT_END}
		case DataObjectName.COMMENTPROPERTY : return resqml2_instantiateCommentProperty(cPtr, owner);
${COMMENT_START}
		case DataObjectName.CONTINUOUSCOLORMAP : return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.ContinuousColorMap(cPtr, owner);
${COMMENT_END}
		case DataObjectName.CONTINUOUSPROPERTY : return resqml2_instantiateContinuousProperty(cPtr, owner);
${COMMENT_START}
		case DataObjectName.CULTURALFEATURE : return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.CulturalFeature(cPtr, owner);
${COMMENT_END}
		case DataObjectName.DEVIATIONSURVEYREPRESENTATION : return resqml2_instantiateDeviationSurveyRepresentation(cPtr, owner);
${COMMENT_START}
		case DataObjectName.DISCRETECOLORMAP : return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.DiscreteColorMap(cPtr, owner);
${COMMENT_END}
		case DataObjectName.DISCRETEPROPERTY : return resqml2_instantiateDiscreteProperty(cPtr, owner);
		case DataObjectName.DOUBLETABLELOOKUP : return resqml2_instantiateDoubleTableLookup(cPtr, owner);
		case DataObjectName.EARTHMODELINTERPRETATION : return resqml2_instantiateEarthModelInterpretation(cPtr, owner);
		case DataObjectName.EPCEXTERNALPARTREFERENCE : return eml2_instantiateEpcExternalPartReference(cPtr, owner);
		case DataObjectName.FAULTINTERPRETATION : return resqml2_instantiateFaultInterpretation(cPtr, owner);
		case DataObjectName.FLUIDBOUNDARYFEATURE : return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.FluidBoundaryFeature(cPtr, owner);
		case DataObjectName.FLUIDCHARACTERIZATION : return new f2i.energisticsStandardsApi.${FESAPI_PRODML2_1_NS}.FluidCharacterization(cPtr, owner);
		case DataObjectName.FLUIDSYSTEM : return new f2i.energisticsStandardsApi.${FESAPI_PRODML2_1_NS}.FluidSystem(cPtr, owner);
		case DataObjectName.FRONTIERFEATURE : return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.FrontierFeature(cPtr, owner);
		case DataObjectName.GENETICBOUNDARYFEATURE :
			f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeneticBoundaryFeature result = new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeneticBoundaryFeature(cPtr, owner);
			return result.isAnHorizon() ? new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.Horizon(cPtr, owner) : result;
		case DataObjectName.GEOBODYFEATURE : return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeobodyFeature(cPtr, owner);
		case DataObjectName.GEOBODYBOUNDARYINTERPRETATION : return resqml2_instantiateGeobodyBoundaryInterpretation(cPtr, owner);
		case DataObjectName.GEOBODYINTERPRETATION : return resqml2_instantiateGeobodyInterpretation(cPtr, owner);
		case DataObjectName.GENERICFEATUREINTERPRETATION : return resqml2_instantiateGenericFeatureInterpretation(cPtr, owner);
		case DataObjectName.GEOLOGICUNITFEATURE : return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeologicUnitFeature(cPtr, owner);
${COMMENT_START}
		case DataObjectName.GRAPHICALINFORMATIONSET : return new f2i.energisticsStandardsApi.${FESAPI_EML2_3_NS}.GraphicalInformationSet(cPtr, owner);
${COMMENT_END}
		case DataObjectName.GRID2DREPRESENTATION : return resqml2_instantiateGrid2dRepresentation(cPtr, owner);
		case DataObjectName.GRIDCONNECTIONSETREPRESENTATION : return resqml2_instantiateGridConnectionSetRepresentation(cPtr, owner);
		case DataObjectName.HORIZONINTERPRETATION : return resqml2_instantiateHorizonInterpretation(cPtr, owner);
		case DataObjectName.IJKGRIDREPRESENTATION : return resqml2_instantiateConcreteIjkGridRepresentation(cPtr, owner);
		case DataObjectName.LOCALDEPTH3DCRS : return resqml2_instantiateLocalDepth3dCrs(cPtr, owner);
		case DataObjectName.LOCALTIME3DCRS : return resqml2_instantiateLocalTime3dCrs(cPtr, owner);
		case DataObjectName.LOG : return new f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.Log(cPtr, owner);
		case DataObjectName.MDDATUM : return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.MdDatum(cPtr, owner);
${COMMENT_START}
		case DataObjectName.MODEL : return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.Model(cPtr, owner);
${COMMENT_END}
		case DataObjectName.NONSEALEDSURFACEFRAMEWORKREPRESENTATION : return resqml2_instantiateNonSealedSurfaceFrameworkRepresentation(cPtr, owner);
		case DataObjectName.ORGANIZATIONFEATURE : return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.OrganizationFeature(cPtr, owner);
		case DataObjectName.PLANESETREPRESENTATION : return resqml2_instantiatePlaneSetRepresentation(cPtr, owner);
		case DataObjectName.POINTSETREPRESENTATION : return resqml2_instantiatePointSetRepresentation(cPtr, owner);
		case DataObjectName.POINTSPROPERTY : return resqml2_instantiatePointSetRepresentation(cPtr, owner);
		case DataObjectName.POLYLINEREPRESENTATION : return resqml2_instantiatePolylineRepresentation(cPtr, owner);
		case DataObjectName.POLYLINESETREPRESENTATION : return resqml2_instantiatePolylineSetRepresentation(cPtr, owner);
		case DataObjectName.PROPERTYKIND : return eml2_instantiatePropertyKind(cPtr, owner);
		case DataObjectName.PROPERTYSET : return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PropertySet(cPtr, owner);
		case DataObjectName.REPRESENTATIONSETREPRESENTATION : return resqml2_instantiateRepresentationSetRepresentation(cPtr, owner);
		case DataObjectName.ROCKFLUIDORGANIZATIONINTERPRETATION : return resqml2_instantiateRockFluidOrganizationInterpretation(cPtr, owner);
		case DataObjectName.ROCKFLUIDUNITINTERPRETATION : return resqml2_instantiateRockFluidUnitInterpretation(cPtr, owner);
${COMMENT_START}
		case DataObjectName.ROCKVOLUMEFEATURE : return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.RockVolumeFeature(cPtr, owner);
${COMMENT_END}
		case DataObjectName.SEALEDSURFACEFRAMEWORKREPRESENTATION : return resqml2_instantiateSealedSurfaceFrameworkRepresentation(cPtr, owner);
		case DataObjectName.SEALEDVOLUMEFRAMEWORKREPRESENTATION : return resqml2_instantiateSealedVolumeFrameworkRepresentation(cPtr, owner);
		case DataObjectName.SEISMICLATTICEFEATURE : return resqml2_instantiateSeismicLatticeFeature(cPtr, owner);
		case DataObjectName.SEISMICLINEFEATURE : return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SeismicLineFeature(cPtr, owner);
		case DataObjectName.SEISMICLINESETFEATURE : return resqml2_instantiateSeismicLineSetFeature(cPtr, owner);
${COMMENT_START}
		case DataObjectName.SEISMICWELLBOREFRAMEREPRESENTATION : return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.SeismicWellboreFrameRepresentation(cPtr, owner);
		case DataObjectName.SHOTPOINTLINEFEATURE : return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.ShotPointLineFeature(cPtr, owner);
${COMMENT_END}
		case DataObjectName.STRATIGRAPHICCOLUMN : return resqml2_instantiateStratigraphicColumn(cPtr, owner);
		case DataObjectName.STRATIGRAPHICCOLUMNRANKINTERPRETATION : return resqml2_instantiateStratigraphicColumnRankInterpretation(cPtr, owner);
		case DataObjectName.STRATIGRAPHICOCCURRENCEINTERPRETATION : return resqml2_instantiateStratigraphicOccurrenceInterpretation(cPtr, owner);
		case DataObjectName.STRATIGRAPHICUNITFEATURE : return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicUnitFeature(cPtr, owner);
		case DataObjectName.STRATIGRAPHICUNITINTERPRETATION : return resqml2_instantiateStratigraphicUnitInterpretation(cPtr, owner);
		case DataObjectName.STRINGTABLELOOKUP : return resqml2_instantiateStringTableLookup(cPtr, owner);
		case DataObjectName.STRUCTURALORGANIZATIONINTERPRETATION : return resqml2_instantiateStructuralOrganizationInterpretation(cPtr, owner);
		case DataObjectName.SUBREPRESENTATION : return resqml2_instantiateSubRepresentation(cPtr, owner);
		case DataObjectName.TECTONICBOUNDARYFEATURE : return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.TectonicBoundaryFeature(cPtr, owner);
		case DataObjectName.TIMESERIES : return eml2_instantiateTimeSeries(cPtr, owner);
		case DataObjectName.TIMESERIESDATA : return new f2i.energisticsStandardsApi.${FESAPI_PRODML2_1_NS}.TimeSeriesData(cPtr, owner);
		case DataObjectName.TRAJECTORY : return new f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.Trajectory(cPtr, owner);
		case DataObjectName.TRIANGULATEDSETREPRESENTATION : return resqml2_instantiateTriangulatedSetRepresentation(cPtr, owner);
		case DataObjectName.UNSTRUCTUREDGRIDREPRESENTATION : return resqml2_instantiateUnstructuredGridRepresentation(cPtr, owner);
		case DataObjectName.WELL : return new f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.Well(cPtr, owner);
		case DataObjectName.WELLBORE : return new f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.Wellbore(cPtr, owner);
		case DataObjectName.WELLBORECOMPLETION : return new f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.WellboreCompletion(cPtr, owner);
		case DataObjectName.WELLBOREFEATURE : return resqml2_instantiateWellboreFeature(cPtr, owner);
		case DataObjectName.WELLBOREFRAMEREPRESENTATION : return resqml2_instantiateWellboreFrameRepresentation(cPtr, owner);
		case DataObjectName.WELLBOREGEOMETRY : return new f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.WellboreGeometry(cPtr, owner);
		case DataObjectName.WELLBOREINTERPRETATION : return resqml2_instantiateWellboreInterpretation(cPtr, owner);
		case DataObjectName.WELLBOREMARKER : return resqml2_instantiateWellboreMarker(cPtr, owner);
		case DataObjectName.WELLBOREMARKERFRAMEREPRESENTATION : return resqml2_instantiateWellboreMarkerFrameRepresentation(cPtr, owner);
		case DataObjectName.WELLBORETRAJECTORYREPRESENTATION : return resqml2_instantiateWellboreTrajectoryRepresentation(cPtr, owner);
		case DataObjectName.WELLCOMPLETION : return new f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.WellCompletion(cPtr, owner);
		default : throw new System.ArgumentException("Encountered type " + type + " that is not known to be a RESQML or WITSML concrete class");
    }
  }
%}

namespace COMMON_NS
{
	%typemap(csout, excode=SWIGEXCODE) AbstractObject*  {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.eml2_instantiateConcreteObject(cPtr, $owner);$excode
		return ret;
	}
}

namespace EML2_NS
{
	%typemap(csout, excode=SWIGEXCODE) 	Activity*, ActivityTemplate*, EpcExternalPartReference*, PropertyKind*, TimeSeries*
#ifdef WITH_RESQML2_2
										,GraphicalInformationSet*
#endif
	{
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.eml2_instantiateConcreteObject(cPtr, $owner);$excode
		return ret;
	}
}

namespace RESQML2_NS
{		
	%typemap(csout, excode=SWIGEXCODE)	AbstractFeature*, AbstractFeatureInterpretation*, AbstractRepresentation*, AbstractGridRepresentation*, AbstractLocal3dCrs*,
										AbstractProperty*, AbstractValuesProperty*,
										AbstractIjkGridRepresentation*, AbstractStratigraphicOrganizationInterpretation*,
#ifdef WITH_RESQML2_2
										AbstractColorMap*,
#endif
										BlockedWellboreRepresentation*,
										BoundaryFeature*,
										BoundaryFeatureInterpretation*,
										CategoricalProperty*,
#ifdef WITH_RESQML2_2
										CmpLineFeature*,
#endif
										CommentProperty*,
#ifdef WITH_RESQML2_2
										ContinuousColorMap*,
#endif
										ContinuousProperty*,
										CulturalFeature*,
										DeviationSurveyRepresentation*,
#ifdef WITH_RESQML2_2
										DiscreteColorMap*,
#endif
										DiscreteProperty*,
										DoubleTableLookup*,
										EarthModelInterpretation*,
										FaultInterpretation*,
										GenericFeatureInterpretation*,
										GeobodyBoundaryInterpretation*,
										GeobodyInterpretation*,
										Grid2dRepresentation*,
										GridConnectionSetRepresentation*,
										HorizonInterpretation*,
										IjkGridExplicitRepresentation*,
										IjkGridLatticeRepresentation*,
										IjkGridNoGeometryRepresentation*,
										IjkGridParametricRepresentation*,
										LocalDepth3dCrs*,
										LocalTime3dCrs*,
										MdDatum*,
										Model*,
										NonSealedSurfaceFrameworkRepresentation*,
										PlaneSetRepresentation*,
										PointSetRepresentation*,
										PointsProperty*,
										PolylineRepresentation*,
										PolylineSetRepresentation*,
										PropertySet*,
										RepresentationSetRepresentation*,
										RockFluidOrganizationInterpretation*,
										RockFluidUnitInterpretation*,
										RockVolumeFeature*,
										SealedSurfaceFrameworkRepresentation*,
										SealedVolumeFrameworkRepresentation*,
										SeismicLatticeFeature*,
										SeismicLineSetFeature*,
#ifdef WITH_RESQML2_2
										SeismicWellboreFrameRepresentation*,
										ShotPointLineFeature*,
#endif
										StratigraphicColumn*,
										StratigraphicColumnRankInterpretation*,
										StratigraphicOccurrenceInterpretation*,
										StratigraphicUnitInterpretation*,
										StringTableLookup*,
										StructuralOrganizationInterpretation*,
										SubRepresentation*,
										TriangulatedSetRepresentation*,
										UnstructuredGridRepresentation*,
										WellboreFeature*,
										WellboreFrameRepresentation*,
										WellboreInterpretation*,
										WellboreMarker*,
										WellboreMarkerFrameRepresentation*,
										WellboreTrajectoryRepresentation*
	{
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.eml2_instantiateConcreteObject(cPtr, $owner);$excode
		return ret;
	}
}
