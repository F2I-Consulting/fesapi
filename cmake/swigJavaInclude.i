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
Basically this file add methods resqml2_0_instantiate* which will create the right Java instance according to what it is exactly.
**********************************************************************/

%pragma(java) jniclasscode=%{
	
	private enum DataObjectName {
        ACTIVITY,
		ACTIVITYTEMPLATE,
		BLOCKEDWELLBOREREPRESENTATION,
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
		FLUIDBOUNDARYINTERPRETATION,
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
		ROCKFLUIDUNITFEATURE,
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
		STREAMLINESFEATURE,
		STREAMLINESREPRESENTATION,
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
		WELLCOMPLETION;
    }
	
	public static com.f2i_consulting.fesapi.${FESAPI_EML2_NS}.Activity eml2_instantiateActivity(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_Activity(cPtr, owner);
		}
${COMMENT_START}
		else if ("eml23".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_EML2_3_NS}.eml23_Activity(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_EML2_NS}.ActivityTemplate eml2_instantiateActivityTemplate(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_ActivityTemplate(cPtr, owner);
		}
${COMMENT_START}
		else if ("eml23".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_EML2_3_NS}.eml23_ActivityTemplate(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_EML2_NS}.AbstractHdfProxy eml2_instantiateEpcExternalPartReference(long cPtr, boolean owner)
	{
		return new com.f2i_consulting.fesapi.${FESAPI_EML2_NS}.AbstractHdfProxy(cPtr, owner);
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_EML2_NS}.PropertyKind eml2_instantiatePropertyKind(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_PropertyKind(cPtr, owner);
		}
		else if ("eml21".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_EML2_1_NS}.PropertyKind_eml21(cPtr, owner);
		}
${COMMENT_START}
		else if ("eml23".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_EML2_3_NS}.eml23_PropertyKind(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_EML2_NS}.TimeSeries eml2_instantiateTimeSeries(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_TimeSeries(cPtr, owner);
		}
${COMMENT_START}
		else if ("eml23".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_EML2_3_NS}.eml23_TimeSeries(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_WITSML2_NS}.Trajectory witsml2_instantiateTrajectory(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("witsml14".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_WITSML1_4_NS}.witsml14_Trajectory(cPtr, owner);
		}
		else if ("witsml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_WITSML2_0_NS}.witsml20_Trajectory(cPtr, owner);
		}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.BlockedWellboreRepresentation resqml2_instantiateBlockedWellboreRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_BlockedWellboreRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_BlockedWellboreRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.BoundaryFeature resqml2_instantiateBoundaryFeature(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_BoundaryFeature(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_BoundaryFeature(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.WellboreFeature resqml2_instantiateWellboreFeature(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_WellboreFeature(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_WellboreFeature(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.SeismicLatticeFeature resqml2_instantiateSeismicLatticeFeature(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_SeismicLatticeFeature(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_SeismicLatticeFeature(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.SeismicLineSetFeature resqml2_instantiateSeismicLineSetFeature(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_SeismicLineSetFeature(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_SeismicLineSetFeature(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.StratigraphicColumn resqml2_instantiateStratigraphicColumn(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_StratigraphicColumn(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_StratigraphicColumn(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.BoundaryFeatureInterpretation resqml2_instantiateBoundaryFeatureInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_BoundaryFeatureInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_BoundaryFeatureInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.EarthModelInterpretation resqml2_instantiateEarthModelInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_EarthModelInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_EarthModelInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.FaultInterpretation resqml2_instantiateFaultInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_FaultInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_FaultInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.GeobodyBoundaryInterpretation resqml2_instantiateGeobodyBoundaryInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_GeobodyBoundaryInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_GeobodyBoundaryInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.GeobodyInterpretation resqml2_instantiateGeobodyInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_GeobodyInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_GeobodyInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.GenericFeatureInterpretation resqml2_instantiateGenericFeatureInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_GenericFeatureInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_GenericFeatureInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.HorizonInterpretation resqml2_instantiateHorizonInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_HorizonInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_HorizonInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.StratigraphicColumnRankInterpretation resqml2_instantiateStratigraphicColumnRankInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_StratigraphicColumnRankInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_StratigraphicColumnRankInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.AbstractOrganizationInterpretation resqml2_instantiateStratigraphicOccurrenceInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.AbstractOrganizationInterpretation tmp = new com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.AbstractOrganizationInterpretation(cPtr, owner);
			if (tmp.isRockFluid()) {
				return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_RockFluidOrganizationInterpretation(cPtr, owner);
			}
			else {
				return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_StratigraphicOccurrenceInterpretation(cPtr, owner);
			}
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_StratigraphicOccurrenceInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.StratigraphicUnitInterpretation resqml2_instantiateStratigraphicUnitInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_StratigraphicUnitInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_StratigraphicUnitInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.StructuralOrganizationInterpretation resqml2_instantiateStructuralOrganizationInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_StructuralOrganizationInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_StructuralOrganizationInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.WellboreInterpretation resqml2_instantiateWellboreInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_WellboreInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_WellboreInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.DeviationSurveyRepresentation resqml2_instantiateDeviationSurveyRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_DeviationSurveyRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_DeviationSurveyRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.Grid2dRepresentation resqml2_instantiateGrid2dRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_Grid2dRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_Grid2dRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.GridConnectionSetRepresentation resqml2_instantiateGridConnectionSetRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_GridConnectionSetRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_GridConnectionSetRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.NonSealedSurfaceFrameworkRepresentation resqml2_instantiateNonSealedSurfaceFrameworkRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_NonSealedSurfaceFrameworkRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_NonSealedSurfaceFrameworkRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.SealedSurfaceFrameworkRepresentation resqml2_instantiateSealedSurfaceFrameworkRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_SealedSurfaceFrameworkRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_SealedSurfaceFrameworkRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.SealedVolumeFrameworkRepresentation resqml2_instantiateSealedVolumeFrameworkRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_SealedVolumeFrameworkRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_SealedVolumeFrameworkRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.PlaneSetRepresentation resqml2_instantiatePlaneSetRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_PlaneSetRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_PlaneSetRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.PointSetRepresentation resqml2_instantiatePointSetRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_PointSetRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_PointSetRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.PointsProperty resqml2_instantiatePointsProperty(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_PointsProperty(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_PointsProperty(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.PolylineRepresentation resqml2_instantiatePolylineRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_PolylineRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_PolylineRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.PolylineSetRepresentation resqml2_instantiatePolylineSetRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_PolylineSetRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_PolylineSetRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.RepresentationSetRepresentation resqml2_instantiateRepresentationSetRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_RepresentationSetRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_RepresentationSetRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.RockFluidOrganizationInterpretation resqml2_instantiateRockFluidOrganizationInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_RockFluidOrganizationInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_RockFluidOrganizationInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.RockFluidUnitInterpretation resqml2_instantiateRockFluidUnitInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_RockFluidUnitInterpretation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_RockFluidUnitInterpretation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.SubRepresentation resqml2_instantiateSubRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_SubRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_SubRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.TriangulatedSetRepresentation resqml2_instantiateTriangulatedSetRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_TriangulatedSetRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_TriangulatedSetRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.UnstructuredGridRepresentation resqml2_instantiateUnstructuredGridRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_UnstructuredGridRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_UnstructuredGridRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.WellboreTrajectoryRepresentation resqml2_instantiateWellboreTrajectoryRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_WellboreTrajectoryRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_WellboreTrajectoryRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
  
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation resqml2_instantiateConcreteIjkGridRepresentation(long cPtr, boolean owner)
	{
		if (cPtr == 0) { return null; }
		
		com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation.geometryKind type = com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation.geometryKind
			.swigToEnum(${FESAPI_RESQML2_NS}_AbstractIjkGridRepresentation_getGeometryKind(cPtr, new com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation(cPtr, false)));
		String xmlNs = common_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.common.AbstractObject(cPtr, false));

		if (type == com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation.geometryKind.EXPLICIT) {
			if ("resqml20".equals(xmlNs)) {
				return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_IjkGridExplicitRepresentation(cPtr, owner);
			}
${COMMENT_START}
			else if ("resqml22".equals(xmlNs)) {
				return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_IjkGridExplicitRepresentation(cPtr, owner);
			}
${COMMENT_END}
		}
		else if (type == com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation.geometryKind.PARAMETRIC) {
			if ("resqml20".equals(xmlNs)) {
				return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_IjkGridParametricRepresentation(cPtr, owner);
			}
${COMMENT_START}
			else if ("resqml22".equals(xmlNs)) {
				return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_IjkGridParametricRepresentation(cPtr, owner);
			}
${COMMENT_END}
		}
		else if (type == com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation.geometryKind.LATTICE) {
			if ("resqml20".equals(xmlNs)) {
				return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_IjkGridLatticeRepresentation(cPtr, owner);
			}
${COMMENT_START}
			else if ("resqml22".equals(xmlNs)) {
				return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_IjkGridLatticeRepresentation(cPtr, owner);
			}
${COMMENT_END}
		}
		else // TODO : see if it is possible to return the object itself instead of a copy.
		{
		  return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation(cPtr, owner);
		}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.CategoricalProperty resqml2_instantiateCategoricalProperty(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_CategoricalProperty(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_CategoricalProperty(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.CommentProperty resqml2_instantiateCommentProperty(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_CommentProperty(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_CommentProperty(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.ContinuousProperty resqml2_instantiateContinuousProperty(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_ContinuousProperty(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_ContinuousProperty(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.DiscreteProperty resqml2_instantiateDiscreteProperty(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_DiscreteProperty(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_DiscreteProperty(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.WellboreFrameRepresentation resqml2_instantiateWellboreFrameRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_WellboreFrameRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_WellboreFrameRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.WellboreMarker resqml2_instantiateWellboreMarker(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_WellboreMarker(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_WellboreMarker(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.WellboreMarkerFrameRepresentation resqml2_instantiateWellboreMarkerFrameRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_WellboreMarkerFrameRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_WellboreMarkerFrameRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.LocalDepth3dCrs resqml2_instantiateLocalDepth3dCrs(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_LocalDepth3dCrs(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_LocalDepth3dCrs(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.LocalTime3dCrs resqml2_instantiateLocalTime3dCrs(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_LocalTime3dCrs(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_LocalTime3dCrs(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.DoubleTableLookup resqml2_instantiateDoubleTableLookup(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_DoubleTableLookup(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_DoubleTableLookup(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.StringTableLookup resqml2_instantiateStringTableLookup(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_StringTableLookup(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_StringTableLookup(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.StreamlinesFeature resqml2_instantiateStreamlinesFeature(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_StreamlinesFeature(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_StreamlinesFeature(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i_consulting.fesapi.${FESAPI_RESQML2_NS}.StreamlinesRepresentation resqml2_instantiateStreamlinesRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_StreamlinesRepresentation(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_StreamlinesRepresentation(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}

  public static com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject eml2_instantiateConcreteObject(long cPtr, boolean owner)
  {
	com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject ret = null;
	if (cPtr == 0) {
		return ret;
	}

	String type = ${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(cPtr, new com.f2i_consulting.fesapi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
	DataObjectName dataObjName = DataObjectName.valueOf(type.toUpperCase());
	switch (dataObjName) {
		case ACTIVITY : return eml2_instantiateActivity(cPtr, owner);
		case ACTIVITYTEMPLATE : return eml2_instantiateActivityTemplate(cPtr, owner);
		case BLOCKEDWELLBOREREPRESENTATION : return resqml2_instantiateBlockedWellboreRepresentation(cPtr, owner);
		case BOUNDARYFEATURE : return resqml2_instantiateBoundaryFeature(cPtr, owner);
		case BOUNDARYFEATUREINTERPRETATION : return resqml2_instantiateBoundaryFeatureInterpretation(cPtr, owner);
		case CATEGORICALPROPERTY : return resqml2_instantiateCategoricalProperty(cPtr, owner);
		case CHANNEL : return new com.f2i_consulting.fesapi.${FESAPI_WITSML2_0_NS}.witsml20_Channel(cPtr, owner);
		case CHANNELSET : return new com.f2i_consulting.fesapi.${FESAPI_WITSML2_0_NS}.witsml20_ChannelSet(cPtr, owner);
${COMMENT_START}
		case CMPLINEFEATURE : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_CmpLineFeature(cPtr, owner);
${COMMENT_END}
		case COMMENTPROPERTY : return resqml2_instantiateCommentProperty(cPtr, owner);
${COMMENT_START}
		case CONTINUOUSCOLORMAP : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_ContinuousColorMap(cPtr, owner);
${COMMENT_END}
		case CONTINUOUSPROPERTY : return resqml2_instantiateContinuousProperty(cPtr, owner);
${COMMENT_START}
		case CULTURALFEATURE : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_CulturalFeature(cPtr, owner);
${COMMENT_END}
		case DEVIATIONSURVEYREPRESENTATION : return resqml2_instantiateDeviationSurveyRepresentation(cPtr, owner);
${COMMENT_START}
		case DISCRETECOLORMAP : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_DiscreteColorMap(cPtr, owner);
${COMMENT_END}
		case DISCRETEPROPERTY : return resqml2_instantiateDiscreteProperty(cPtr, owner);
		case DOUBLETABLELOOKUP : return resqml2_instantiateDoubleTableLookup(cPtr, owner);
		case EARTHMODELINTERPRETATION : return resqml2_instantiateEarthModelInterpretation(cPtr, owner);
		case EPCEXTERNALPARTREFERENCE : return eml2_instantiateEpcExternalPartReference(cPtr, owner);
		case FAULTINTERPRETATION : return resqml2_instantiateFaultInterpretation(cPtr, owner);
		case FLUIDBOUNDARYFEATURE : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_FluidBoundaryFeature(cPtr, owner);
${COMMENT_START}
		case FLUIDBOUNDARYINTERPRETATION : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_FluidBoundaryInterpretation(cPtr, owner);
${COMMENT_END}
		case FLUIDCHARACTERIZATION : return new com.f2i_consulting.fesapi.${FESAPI_PRODML2_1_NS}.FluidCharacterization(cPtr, owner);
		case FLUIDSYSTEM : return new com.f2i_consulting.fesapi.${FESAPI_PRODML2_1_NS}.FluidSystem(cPtr, owner);
		case FRONTIERFEATURE : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_FrontierFeature(cPtr, owner);
		case GENETICBOUNDARYFEATURE :
			com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_GeneticBoundaryFeature result = new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_GeneticBoundaryFeature(cPtr, owner);
			return result.isAnHorizon() ? new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_Horizon(cPtr, owner) : result;
		case GEOBODYFEATURE : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_GeobodyFeature(cPtr, owner);
		case GEOBODYBOUNDARYINTERPRETATION : return resqml2_instantiateGeobodyBoundaryInterpretation(cPtr, owner);
		case GEOBODYINTERPRETATION : return resqml2_instantiateGeobodyInterpretation(cPtr, owner);
		case GENERICFEATUREINTERPRETATION : return resqml2_instantiateGenericFeatureInterpretation(cPtr, owner);
		case GEOLOGICUNITFEATURE : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_GeologicUnitFeature(cPtr, owner);
${COMMENT_START}
		case GRAPHICALINFORMATIONSET : return new com.f2i_consulting.fesapi.${FESAPI_EML2_3_NS}.eml23_GraphicalInformationSet(cPtr, owner);
${COMMENT_END}
		case GRID2DREPRESENTATION : return resqml2_instantiateGrid2dRepresentation(cPtr, owner);
		case GRIDCONNECTIONSETREPRESENTATION : return resqml2_instantiateGridConnectionSetRepresentation(cPtr, owner);
		case HORIZONINTERPRETATION : return resqml2_instantiateHorizonInterpretation(cPtr, owner);
		case IJKGRIDREPRESENTATION : return resqml2_instantiateConcreteIjkGridRepresentation(cPtr, owner);
		case LOCALDEPTH3DCRS : return resqml2_instantiateLocalDepth3dCrs(cPtr, owner);
		case LOCALTIME3DCRS : return resqml2_instantiateLocalTime3dCrs(cPtr, owner);
		case LOG : return new com.f2i_consulting.fesapi.${FESAPI_WITSML2_0_NS}.witsml20_Log(cPtr, owner);
		case MDDATUM : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_MdDatum(cPtr, owner);
${COMMENT_START}
		case MODEL : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_Model(cPtr, owner);
${COMMENT_END}
		case NONSEALEDSURFACEFRAMEWORKREPRESENTATION : return resqml2_instantiateNonSealedSurfaceFrameworkRepresentation(cPtr, owner);
		case ORGANIZATIONFEATURE : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_OrganizationFeature(cPtr, owner);
		case PLANESETREPRESENTATION : return resqml2_instantiatePlaneSetRepresentation(cPtr, owner);
		case POINTSETREPRESENTATION : return resqml2_instantiatePointSetRepresentation(cPtr, owner);
		case POINTSPROPERTY : return resqml2_instantiatePointsProperty(cPtr, owner);
		case POLYLINEREPRESENTATION : return resqml2_instantiatePolylineRepresentation(cPtr, owner);
		case POLYLINESETREPRESENTATION : return resqml2_instantiatePolylineSetRepresentation(cPtr, owner);
		case PROPERTYKIND : return eml2_instantiatePropertyKind(cPtr, owner);
		case PROPERTYSET : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_PropertySet(cPtr, owner);
		case REPRESENTATIONSETREPRESENTATION : return resqml2_instantiateRepresentationSetRepresentation(cPtr, owner);
		case ROCKFLUIDORGANIZATIONINTERPRETATION : return resqml2_instantiateRockFluidOrganizationInterpretation(cPtr, owner);
		case ROCKFLUIDUNITFEATURE : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_RockFluidUnitFeature(cPtr, owner);
		case ROCKFLUIDUNITINTERPRETATION : return resqml2_instantiateRockFluidUnitInterpretation(cPtr, owner);
${COMMENT_START}
		case ROCKVOLUMEFEATURE : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_RockVolumeFeature(cPtr, owner);
${COMMENT_END}
		case SEALEDSURFACEFRAMEWORKREPRESENTATION : return resqml2_instantiateSealedSurfaceFrameworkRepresentation(cPtr, owner);
		case SEALEDVOLUMEFRAMEWORKREPRESENTATION : return resqml2_instantiateSealedVolumeFrameworkRepresentation(cPtr, owner);
		case SEISMICLATTICEFEATURE : return resqml2_instantiateSeismicLatticeFeature(cPtr, owner);
		case SEISMICLINEFEATURE : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_SeismicLineFeature(cPtr, owner);
		case SEISMICLINESETFEATURE : return resqml2_instantiateSeismicLineSetFeature(cPtr, owner);
${COMMENT_START}
		case SEISMICWELLBOREFRAMEREPRESENTATION : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_SeismicWellboreFrameRepresentation(cPtr, owner);
		case SHOTPOINTLINEFEATURE : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_2_NS}.resqml22_ShotPointLineFeature(cPtr, owner);
${COMMENT_END}
		case STRATIGRAPHICCOLUMN : return resqml2_instantiateStratigraphicColumn(cPtr, owner);
		case STRATIGRAPHICCOLUMNRANKINTERPRETATION : return resqml2_instantiateStratigraphicColumnRankInterpretation(cPtr, owner);
		case STRATIGRAPHICOCCURRENCEINTERPRETATION : return resqml2_instantiateStratigraphicOccurrenceInterpretation(cPtr, owner);
		case STRATIGRAPHICUNITFEATURE : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_StratigraphicUnitFeature(cPtr, owner);
		case STRATIGRAPHICUNITINTERPRETATION : return resqml2_instantiateStratigraphicUnitInterpretation(cPtr, owner);
		case STREAMLINESFEATURE : return resqml2_instantiateStreamlinesFeature(cPtr, owner);
		case STREAMLINESREPRESENTATION : return resqml2_instantiateStreamlinesRepresentation(cPtr, owner);
		case STRINGTABLELOOKUP : return resqml2_instantiateStringTableLookup(cPtr, owner);
		case STRUCTURALORGANIZATIONINTERPRETATION : return resqml2_instantiateStructuralOrganizationInterpretation(cPtr, owner);
		case SUBREPRESENTATION : return resqml2_instantiateSubRepresentation(cPtr, owner);
		case TECTONICBOUNDARYFEATURE : return new com.f2i_consulting.fesapi.${FESAPI_RESQML2_0_1_NS}.resqml20_TectonicBoundaryFeature(cPtr, owner);
		case TIMESERIES : return eml2_instantiateTimeSeries(cPtr, owner);
		case TIMESERIESDATA : return new com.f2i_consulting.fesapi.${FESAPI_PRODML2_1_NS}.TimeSeriesData(cPtr, owner);
		case TRAJECTORY : return witsml2_instantiateTrajectory(cPtr, owner);
		case TRIANGULATEDSETREPRESENTATION : return resqml2_instantiateTriangulatedSetRepresentation(cPtr, owner);
		case UNSTRUCTUREDGRIDREPRESENTATION : return resqml2_instantiateUnstructuredGridRepresentation(cPtr, owner);
		case WELL : return new com.f2i_consulting.fesapi.${FESAPI_WITSML2_0_NS}.witsml20_Well(cPtr, owner);
		case WELLBORE : return new com.f2i_consulting.fesapi.${FESAPI_WITSML2_0_NS}.witsml20_Wellbore(cPtr, owner);
		case WELLBORECOMPLETION : return new com.f2i_consulting.fesapi.${FESAPI_WITSML2_0_NS}.witsml20_WellboreCompletion(cPtr, owner);
		case WELLBOREFEATURE : return resqml2_instantiateWellboreFeature(cPtr, owner);
		case WELLBOREFRAMEREPRESENTATION : return resqml2_instantiateWellboreFrameRepresentation(cPtr, owner);
		case WELLBOREGEOMETRY : return new com.f2i_consulting.fesapi.${FESAPI_WITSML2_0_NS}.witsml20_WellboreGeometry(cPtr, owner);
		case WELLBOREINTERPRETATION : return resqml2_instantiateWellboreInterpretation(cPtr, owner);
		case WELLBOREMARKER : return resqml2_instantiateWellboreMarker(cPtr, owner);
		case WELLBOREMARKERFRAMEREPRESENTATION : return resqml2_instantiateWellboreMarkerFrameRepresentation(cPtr, owner);
		case WELLBORETRAJECTORYREPRESENTATION : return resqml2_instantiateWellboreTrajectoryRepresentation(cPtr, owner);
		case WELLCOMPLETION : return new com.f2i_consulting.fesapi.${FESAPI_WITSML2_0_NS}.witsml20_WellCompletion(cPtr, owner);
		default : throw new IllegalArgumentException("Encountered type " + type + " that is not known to be a RESQML or WITSML concrete class");
    }
  }
%}

namespace COMMON_NS
{
	%typemap(javaout) COMMON_NS::AbstractObject*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.eml2_instantiateConcreteObject(cPtr, $owner);
		return ret;
	}
	
	%typemap(javaimports) SWIGTYPE %{
		import com.f2i_consulting.fesapi.*;
	%}
}

namespace EML2_NS
{
	%typemap(javaout) Activity*, ActivityTemplate*, EpcExternalPartReference*, PropertyKind*, TimeSeries* 
#ifdef WITH_RESQML2_2
										,GraphicalInformationSet*
#endif
	{
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.eml2_instantiateConcreteObject(cPtr, $owner);
		return ret;
	}
	
	%typemap(javaimports) SWIGTYPE %{
		import com.f2i_consulting.fesapi.*;
	%}
}

namespace WITSML2_NS
{
	%typemap(javaout) Trajectory*, Well*, Wellbore*, WellboreObject*
	{
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.eml2_instantiateConcreteObject(cPtr, $owner);
		return ret;
	}
	
	%typemap(javaimports) SWIGTYPE %{
		import com.f2i_consulting.fesapi.*;
	%}
}

namespace RESQML2_NS
{		
	%typemap(javaout) 	AbstractFeature*, AbstractFeatureInterpretation*, AbstractRepresentation*, AbstractGridRepresentation*, AbstractLocal3dCrs*,
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
#ifdef WITH_RESQML2_2
						FluidBoundaryInterpretation*,
#endif
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
						StreamlinesFeature*,
						StreamlinesRepresentation*,
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
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.eml2_instantiateConcreteObject(cPtr, $owner);
		return ret;
	}

	%typemap(javaimports) SWIGTYPE %{
		import com.f2i_consulting.fesapi.*;
	%}
}
