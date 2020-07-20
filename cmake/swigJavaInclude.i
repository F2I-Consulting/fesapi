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
		EARTHMODELINTERPRETATION,
		EPCEXTERNALPARTREFERENCE,
		FAULTINTERPRETATION,
		FLUIDBOUNDARYFEATURE,
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
		WELLBOREMARKERFRAMEREPRESENTATION,
		WELLBORETRAJECTORYREPRESENTATION,
		WELLCOMPLETION;
    }
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_EML2_NS}.Activity eml2_instantiateActivity(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.Activity_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("eml23".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_EML2_3_NS}.Activity_eml23(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_EML2_NS}.ActivityTemplate eml2_instantiateActivityTemplate(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.ActivityTemplate_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("eml23".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_EML2_3_NS}.ActivityTemplate_eml23(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_EML2_NS}.HdfProxy eml2_instantiateEpcExternalPartReference(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("eml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_EML2_0_NS}.HdfProxy_eml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("eml23".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_EML2_3_NS}.HdfProxy_eml23(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_EML2_NS}.PropertyKind eml2_instantiatePropertyKind(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PropertyKind_resqml20(cPtr, owner);
		}
		else if ("eml21".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_EML2_1_NS}.PropertyKind_eml21(cPtr, owner);
		}
${COMMENT_START}
		else if ("eml23".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_EML2_3_NS}.PropertyKind_eml23(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_EML2_NS}.TimeSeries eml2_instantiateTimeSeries(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.TimeSeries_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("eml23".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_EML2_3_NS}.TimeSeries_eml23(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.BoundaryFeature resqml2_instantiateBoundaryFeature(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.BoundaryFeature_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.BoundaryFeature_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.WellboreFeature resqml2_instantiateWellboreFeature(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreFeature_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.WellboreFeature_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.SeismicLatticeFeature resqml2_instantiateSeismicLatticeFeature(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SeismicLatticeFeature_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.SeismicLatticeFeature_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.SeismicLineSetFeature resqml2_instantiateSeismicLineSetFeature(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SeismicLineSetFeature_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.SeismicLineSetFeature_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.StratigraphicColumn resqml2_instantiateStratigraphicColumn(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicColumn_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.StratigraphicColumn_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.BoundaryFeatureInterpretation resqml2_instantiateBoundaryFeatureInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.BoundaryFeatureInterpretation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.BoundaryFeatureInterpretation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.EarthModelInterpretation resqml2_instantiateEarthModelInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.EarthModelInterpretation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.EarthModelInterpretation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.FaultInterpretation resqml2_instantiateFaultInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.FaultInterpretation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.FaultInterpretation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.GeobodyBoundaryInterpretation resqml2_instantiateGeobodyBoundaryInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeobodyBoundaryInterpretation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.GeobodyBoundaryInterpretation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.GeobodyInterpretation resqml2_instantiateGeobodyInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeobodyInterpretation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.GeobodyInterpretation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.GenericFeatureInterpretation resqml2_instantiateGenericFeatureInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GenericFeatureInterpretation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.GenericFeatureInterpretation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.HorizonInterpretation resqml2_instantiateHorizonInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.HorizonInterpretation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.HorizonInterpretation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.StratigraphicColumnRankInterpretation resqml2_instantiateStratigraphicColumnRankInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicColumnRankInterpretation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.StratigraphicColumnRankInterpretation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.StratigraphicOccurrenceInterpretation resqml2_instantiateStratigraphicOccurrenceInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicOccurrenceInterpretation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.StratigraphicOccurrenceInterpretation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.StratigraphicUnitInterpretation resqml2_instantiateStratigraphicUnitInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicUnitInterpretation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.StratigraphicUnitInterpretation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.StructuralOrganizationInterpretation resqml2_instantiateStructuralOrganizationInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StructuralOrganizationInterpretation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.StructuralOrganizationInterpretation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.WellboreInterpretation resqml2_instantiateWellboreInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreInterpretation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.WellboreInterpretation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.DeviationSurveyRepresentation resqml2_instantiateDeviationSurveyRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.DeviationSurveyRepresentation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.DeviationSurveyRepresentation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.Grid2dRepresentation resqml2_instantiateGrid2dRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.Grid2dRepresentation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.Grid2dRepresentation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.GridConnectionSetRepresentation resqml2_instantiateGridConnectionSetRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GridConnectionSetRepresentation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.GridConnectionSetRepresentation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.NonSealedSurfaceFrameworkRepresentation resqml2_instantiateNonSealedSurfaceFrameworkRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.NonSealedSurfaceFrameworkRepresentation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.NonSealedSurfaceFrameworkRepresentation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.SealedSurfaceFrameworkRepresentation resqml2_instantiateSealedSurfaceFrameworkRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SealedSurfaceFrameworkRepresentation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.SealedSurfaceFrameworkRepresentation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.SealedVolumeFrameworkRepresentation resqml2_instantiateSealedVolumeFrameworkRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SealedVolumeFrameworkRepresentation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.SealedVolumeFrameworkRepresentation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.PlaneSetRepresentation resqml2_instantiatePlaneSetRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PlaneSetRepresentation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.PlaneSetRepresentation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.PointSetRepresentation resqml2_instantiatePointSetRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PointSetRepresentation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.PointSetRepresentation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.PolylineRepresentation resqml2_instantiatePolylineRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PolylineRepresentation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.PolylineRepresentation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.PolylineSetRepresentation resqml2_instantiatePolylineSetRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PolylineSetRepresentation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.PolylineSetRepresentation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.RepresentationSetRepresentation resqml2_instantiateRepresentationSetRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.RepresentationSetRepresentation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.RepresentationSetRepresentation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.RockFluidOrganizationInterpretation resqml2_instantiateRockFluidOrganizationInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.RockFluidOrganizationInterpretation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.RockFluidOrganizationInterpretation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.RockFluidUnitInterpretation resqml2_instantiateRockFluidUnitInterpretation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.RockFluidUnitInterpretation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.RockFluidUnitInterpretation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.SubRepresentation resqml2_instantiateSubRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SubRepresentation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.SubRepresentation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.TriangulatedSetRepresentation resqml2_instantiateTriangulatedSetRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.TriangulatedSetRepresentation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.TriangulatedSetRepresentation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.UnstructuredGridRepresentation resqml2_instantiateUnstructuredGridRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.UnstructuredGridRepresentation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.UnstructuredGridRepresentation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.WellboreTrajectoryRepresentation resqml2_instantiateWellboreTrajectoryRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreTrajectoryRepresentation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.WellboreTrajectoryRepresentation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
  
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation resqml2_instantiateConcreteIjkGridRepresentation(long cPtr, boolean owner)
	{
		if (cPtr == 0) { return null; }
		
		com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation.geometryKind type = com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation.geometryKind
			.swigToEnum(${FESAPI_RESQML2_NS}_AbstractIjkGridRepresentation_getGeometryKind(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation(cPtr, false)));
		String xmlNs = common_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.common.AbstractObject(cPtr, false));

		if (type == com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation.geometryKind.EXPLICIT) {
			if ("resqml20".equals(xmlNs)) {
				return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.IjkGridExplicitRepresentation_resqml20(cPtr, owner);
			}
${COMMENT_START}
			else if ("resqml22".equals(xmlNs)) {
				return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.IjkGridExplicitRepresentation_resqml22(cPtr, owner);
			}
${COMMENT_END}
		}
		else if (type == com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation.geometryKind.PARAMETRIC) {
			if ("resqml20".equals(xmlNs)) {
				return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.IjkGridParametricRepresentation_resqml20(cPtr, owner);
			}
${COMMENT_START}
			else if ("resqml22".equals(xmlNs)) {
				return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.IjkGridParametricRepresentation_resqml22(cPtr, owner);
			}
${COMMENT_END}
		}
		else if (type == com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation.geometryKind.LATTICE) {
			if ("resqml20".equals(xmlNs)) {
				return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.IjkGridLatticeRepresentation_resqml20(cPtr, owner);
			}
${COMMENT_START}
			else if ("resqml22".equals(xmlNs)) {
				return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.IjkGridLatticeRepresentation_resqml22(cPtr, owner);
			}
${COMMENT_END}
		}
		else // TODO : see if it is possible to return the object itself instead of a copy.
		{
		  return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractIjkGridRepresentation(cPtr, owner);
		}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.CategoricalProperty resqml2_instantiateCategoricalProperty(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.CategoricalProperty_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.CategoricalProperty_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.CommentProperty resqml2_instantiateCommentProperty(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.CommentProperty_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.CommentProperty_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.ContinuousProperty resqml2_instantiateContinuousProperty(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.ContinuousProperty_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.ContinuousProperty_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.DiscreteProperty resqml2_instantiateDiscreteProperty(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.DiscreteProperty_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.DiscreteProperty_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.WellboreFrameRepresentation resqml2_instantiateWellboreFrameRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreFrameRepresentation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.WellboreFrameRepresentation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.WellboreMarkerFrameRepresentation resqml2_instantiateWellboreMarkerFrameRepresentation(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreMarkerFrameRepresentation_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.WellboreMarkerFrameRepresentation_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.LocalDepth3dCrs resqml2_instantiateLocalDepth3dCrs(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.LocalDepth3dCrs_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.LocalDepth3dCrs_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}
	
	public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.LocalTime3dCrs resqml2_instantiateLocalTime3dCrs(long cPtr, boolean owner)
	{
		String xmlNs = ${FESAPI_COMMON_NS}_AbstractObject_getXmlNamespace(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
		if ("resqml20".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.LocalTime3dCrs_resqml20(cPtr, owner);
		}
${COMMENT_START}
		else if ("resqml22".equals(xmlNs)) {
			return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.LocalTime3dCrs_resqml22(cPtr, owner);
		}
${COMMENT_END}
		
		return null;
	}


  public static com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject eml2_instantiateConcreteObject(long cPtr, boolean owner)
  {
	com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject ret = null;
	if (cPtr == 0) {
		return ret;
	}

	String type = ${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
	DataObjectName dataObjName = DataObjectName.valueOf(type.toUpperCase());
	switch (dataObjName) {
		case ACTIVITY : return eml2_instantiateActivity(cPtr, owner);
		case ACTIVITYTEMPLATE : return eml2_instantiateActivityTemplate(cPtr, owner);
		case BOUNDARYFEATURE : return resqml2_instantiateBoundaryFeature(cPtr, owner);
		case BOUNDARYFEATUREINTERPRETATION : return resqml2_instantiateBoundaryFeatureInterpretation(cPtr, owner);
		case CATEGORICALPROPERTY : return resqml2_instantiateCategoricalProperty(cPtr, owner);
		case CHANNEL : return new com.f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.Channel(cPtr, owner);
		case CHANNELSET : return new com.f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.ChannelSet(cPtr, owner);
${COMMENT_START}
		case CMPLINEFEATURE : return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.CmpLineFeature_resqml22(cPtr, owner);
${COMMENT_END}
		case COMMENTPROPERTY : return resqml2_instantiateCommentProperty(cPtr, owner);
${COMMENT_START}
		case CONTINUOUSCOLORMAP : return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.ContinuousColorMap_resqml22(cPtr, owner);
${COMMENT_END}
		case CONTINUOUSPROPERTY : return resqml2_instantiateContinuousProperty(cPtr, owner);
${COMMENT_START}
		case CULTURALFEATURE : return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.CulturalFeature_resqml22(cPtr, owner);
${COMMENT_END}
		case DEVIATIONSURVEYREPRESENTATION : return resqml2_instantiateDeviationSurveyRepresentation(cPtr, owner);
${COMMENT_START}
		case DISCRETECOLORMAP : return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.DiscreteColorMap_resqml22(cPtr, owner);
${COMMENT_END}
		case DISCRETEPROPERTY : return resqml2_instantiateDiscreteProperty(cPtr, owner);
		case EARTHMODELINTERPRETATION : return resqml2_instantiateEarthModelInterpretation(cPtr, owner);
		case EPCEXTERNALPARTREFERENCE : return eml2_instantiateEpcExternalPartReference(cPtr, owner);
		case FAULTINTERPRETATION : return resqml2_instantiateFaultInterpretation(cPtr, owner);
		case FLUIDBOUNDARYFEATURE : return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.FluidBoundaryFeature_resqml20(cPtr, owner);
		case FRONTIERFEATURE : return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.FrontierFeature_resqml20(cPtr, owner);
		case GENETICBOUNDARYFEATURE :
			com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeneticBoundaryFeature_resqml20 result = new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeneticBoundaryFeature_resqml20(cPtr, owner);
			return result.isAnHorizon() ? new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.Horizon_resqml20(cPtr, owner) : result;
		case GEOBODYFEATURE : return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeobodyFeature_resqml20(cPtr, owner);
		case GEOBODYBOUNDARYINTERPRETATION : return resqml2_instantiateGeobodyBoundaryInterpretation(cPtr, owner);
		case GEOBODYINTERPRETATION : return resqml2_instantiateGeobodyInterpretation(cPtr, owner);
		case GENERICFEATUREINTERPRETATION : return resqml2_instantiateGenericFeatureInterpretation(cPtr, owner);
		case GEOLOGICUNITFEATURE : return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeologicUnitFeature_resqml20(cPtr, owner);
${COMMENT_START}
		case GRAPHICALINFORMATIONSET : return new com.f2i.energisticsStandardsApi.${FESAPI_EML2_3_NS}.GraphicalInformationSet_eml23(cPtr, owner);
${COMMENT_END}
		case GRID2DREPRESENTATION : return resqml2_instantiateGrid2dRepresentation(cPtr, owner);
		case GRIDCONNECTIONSETREPRESENTATION : return resqml2_instantiateGridConnectionSetRepresentation(cPtr, owner);
		case HORIZONINTERPRETATION : return resqml2_instantiateHorizonInterpretation(cPtr, owner);
		case IJKGRIDREPRESENTATION : return resqml2_instantiateConcreteIjkGridRepresentation(cPtr, owner);
		case LOCALDEPTH3DCRS : return resqml2_instantiateLocalDepth3dCrs(cPtr, owner);
		case LOCALTIME3DCRS : return resqml2_instantiateLocalTime3dCrs(cPtr, owner);
		case LOG : return new com.f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.Log(cPtr, owner);
		case MDDATUM : return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.MdDatum_resqml20(cPtr, owner);
${COMMENT_START}
		case MODEL : return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.Model_resqml22(cPtr, owner);
${COMMENT_END}
		case NONSEALEDSURFACEFRAMEWORKREPRESENTATION : return resqml2_instantiateNonSealedSurfaceFrameworkRepresentation(cPtr, owner);
		case ORGANIZATIONFEATURE : return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.OrganizationFeature_resqml20(cPtr, owner);
		case PLANESETREPRESENTATION : return resqml2_instantiatePlaneSetRepresentation(cPtr, owner);
		case POINTSETREPRESENTATION : return resqml2_instantiatePointSetRepresentation(cPtr, owner);
		case POLYLINEREPRESENTATION : return resqml2_instantiatePolylineRepresentation(cPtr, owner);
		case POLYLINESETREPRESENTATION : return resqml2_instantiatePolylineSetRepresentation(cPtr, owner);
		case PROPERTYKIND : return eml2_instantiatePropertyKind(cPtr, owner);
		case PROPERTYSET : return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PropertySet_resqml20(cPtr, owner);
		case REPRESENTATIONSETREPRESENTATION : return resqml2_instantiateRepresentationSetRepresentation(cPtr, owner);
		case ROCKFLUIDORGANIZATIONINTERPRETATION : return resqml2_instantiateRockFluidOrganizationInterpretation(cPtr, owner);
		case ROCKFLUIDUNITINTERPRETATION : return resqml2_instantiateRockFluidUnitInterpretation(cPtr, owner);
${COMMENT_START}
		case ROCKVOLUMEFEATURE : return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.RockVolumeFeature_resqml22(cPtr, owner);
${COMMENT_END}
		case SEALEDSURFACEFRAMEWORKREPRESENTATION : return resqml2_instantiateSealedSurfaceFrameworkRepresentation(cPtr, owner);
		case SEALEDVOLUMEFRAMEWORKREPRESENTATION : return resqml2_instantiateSealedVolumeFrameworkRepresentation(cPtr, owner);
		case SEISMICLATTICEFEATURE : return resqml2_instantiateSeismicLatticeFeature(cPtr, owner);
		case SEISMICLINEFEATURE : return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SeismicLineFeature_resqml20(cPtr, owner);
		case SEISMICLINESETFEATURE : return resqml2_instantiateSeismicLineSetFeature(cPtr, owner);
${COMMENT_START}
		case SEISMICWELLBOREFRAMEREPRESENTATION : return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.SeismicWellboreFrameRepresentation_resqml22(cPtr, owner);
		case SHOTPOINTLINEFEATURE : return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.ShotPointLineFeature_resqml22(cPtr, owner);
${COMMENT_END}
		case STRATIGRAPHICCOLUMN : return resqml2_instantiateStratigraphicColumn(cPtr, owner);
		case STRATIGRAPHICCOLUMNRANKINTERPRETATION : return resqml2_instantiateStratigraphicColumnRankInterpretation(cPtr, owner);
		case STRATIGRAPHICOCCURRENCEINTERPRETATION : return resqml2_instantiateStratigraphicOccurrenceInterpretation(cPtr, owner);
		case STRATIGRAPHICUNITFEATURE : return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicUnitFeature_resqml20(cPtr, owner);
		case STRATIGRAPHICUNITINTERPRETATION : return resqml2_instantiateStratigraphicUnitInterpretation(cPtr, owner);
		case STRINGTABLELOOKUP : return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StringTableLookup_resqml20(cPtr, owner);
		case STRUCTURALORGANIZATIONINTERPRETATION : return resqml2_instantiateStructuralOrganizationInterpretation(cPtr, owner);
		case SUBREPRESENTATION : return resqml2_instantiateSubRepresentation(cPtr, owner);
		case TECTONICBOUNDARYFEATURE : return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.TectonicBoundaryFeature_resqml20(cPtr, owner);
		case TIMESERIES : return eml2_instantiateTimeSeries(cPtr, owner);
		case TRAJECTORY : return new com.f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.Trajectory(cPtr, owner);
		case TRIANGULATEDSETREPRESENTATION : return resqml2_instantiateTriangulatedSetRepresentation(cPtr, owner);
		case UNSTRUCTUREDGRIDREPRESENTATION : return resqml2_instantiateUnstructuredGridRepresentation(cPtr, owner);
		case WELL : return new com.f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.Well(cPtr, owner);
		case WELLBORE : return new com.f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.Wellbore(cPtr, owner);
		case WELLBORECOMPLETION : return new com.f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.WellboreCompletion(cPtr, owner);
		case WELLBOREFEATURE : return resqml2_instantiateWellboreFeature(cPtr, owner);
		case WELLBOREFRAMEREPRESENTATION : return resqml2_instantiateWellboreFrameRepresentation(cPtr, owner);
		case WELLBOREGEOMETRY : return new com.f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.WellboreGeometry(cPtr, owner);
		case WELLBOREINTERPRETATION : return resqml2_instantiateWellboreInterpretation(cPtr, owner);
		case WELLBOREMARKERFRAMEREPRESENTATION : return resqml2_instantiateWellboreMarkerFrameRepresentation(cPtr, owner);
		case WELLBORETRAJECTORYREPRESENTATION : return resqml2_instantiateWellboreTrajectoryRepresentation(cPtr, owner);
		case WELLCOMPLETION : return new com.f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.WellCompletion(cPtr, owner);
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
		import com.f2i.energisticsStandardsApi.*;
	%}
}

namespace EML2_NS
{
	%typemap(javaout) Activity*, ActivityTemplate*, EpcExternalPartReference*, AbstractHdfProxy*, HdfProxy*, PropertyKind*, TimeSeries* 
#ifdef WITH_RESQML2_2
										,GraphicalInformationSet*
#endif
	{
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.eml2_instantiateConcreteObject(cPtr, $owner);
		return ret;
	}
	
	%typemap(javaimports) SWIGTYPE %{
		import com.f2i.energisticsStandardsApi.*;
	%}
}

namespace RESQML2_NS
{		
	%typemap(javaout) 	AbstractFeature*, AbstractFeatureInterpretation*, AbstractRepresentation*, AbstractGridRepresentation*, AbstractLocal3dCrs*,
						AbstractProperty*, AbstractValuesProperty*, AbstractDiscreteOrCategoricalProperty*,
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
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.eml2_instantiateConcreteObject(cPtr, $owner);
		return ret;
	}

	%typemap(javaimports) SWIGTYPE %{
		import com.f2i.energisticsStandardsApi.*;
	%}
}
