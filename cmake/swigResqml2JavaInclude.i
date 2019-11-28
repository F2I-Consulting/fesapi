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
  public static com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject resqml2_instantiateConcreteObject(long cPtr, boolean owner)
  {
	com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject ret = null;
	if (cPtr == 0) {
		return ret;
	}
	
	ret = resqml2_instantiateConcreteFeature(cPtr, owner);
	if (ret != null) {
		return ret;
	}
	
	ret = resqml2_instantiateConcreteInterpretation(cPtr, owner);
	if (ret != null) {
		return ret;
	}
	
	ret = resqml2_instantiateConcreteRepresentation(cPtr, owner);
	if (ret != null) {
		return ret;
	}
	
	ret = resqml2_instantiateConcreteProperty(cPtr, owner);
	if (ret != null) {
		return ret;
	}
	
	ret = resqml2_instantiateConcreteLocal3dCrs(cPtr, owner);
	if (ret != null) {
		return ret;
	}
	
    String type = ${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
    if (type.equals("Activity"))
    {
        ret = new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.Activity(cPtr, owner);
    }
    else if (type.equals("ActivityTemplate"))
    {
        ret = new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.ActivityTemplate(cPtr, owner);
    }
    else if (type.equals("EpcExternalPartReference"))
    {
        ret = new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.HdfProxy(cPtr, owner);
    }
    else if (type.equals("MdDatum"))
    {
        ret = new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.MdDatum(cPtr, owner);
    }
    else if (type.equals("PropertyKind"))
    {
        ret = new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.PropertyKind(cPtr, owner);
    }
    else if (type.equals("PropertySet"))
    {
        ret = new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PropertySet(cPtr, owner);
    }
    else if (type.equals("StratigraphicColumn"))
    {
        ret = new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicColumn(cPtr, owner);
    }
    else if (type.equals("StringTableLookup"))
    {
        ret = new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StringTableLookup(cPtr, owner);
    }
    else if (type.equals("TimeSeries"))
    {
        ret = new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.TimeSeries(cPtr, owner);
    }
	else if (type.equals("Well"))
	{
		ret = new com.f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.Well(cPtr, owner);
	}
	else if (type.equals("Wellbore"))
	{
		ret = new com.f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.Wellbore(cPtr, owner);
	}
	else if (type.equals("WellCompletion"))
	{
		ret = new com.f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.WellCompletion(cPtr, owner);
	}
	else if (type.equals("WellboreCompletion"))
	{
		ret = new com.f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.WellboreCompletion(cPtr, owner);
	}
	else if (type.equals("WellboreGeometry"))
	{
		ret = new com.f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.WellboreGeometry(cPtr, owner);
	}
	else if (type.equals("Trajectory"))
	{
		ret = new com.f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.Trajectory(cPtr, owner);
	}
	else if (type.equals("Log"))
	{
		ret = new com.f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.Log(cPtr, owner);
	}
	else if (type.equals("ChannelSet"))
	{
		ret = new com.f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.ChannelSet(cPtr, owner);
	}
	else if (type.equals("Channel"))
	{
		ret = new com.f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.Channel(cPtr, owner);
	}
	else
    {
	throw new IllegalArgumentException("Encountered type " + type + " that is not known to be a RESQML or WITSML concrete class");
    }
    
    return ret;
  }
  
  public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractFeature resqml2_instantiateConcreteFeature(long cPtr, boolean owner)
  {
    if (cPtr == 0) {
      return null;
    }
    String type = ${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
    if (type.equals("BoundaryFeature"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.BoundaryFeature(cPtr, owner);
    }  
    else if (type.equals("FluidBoundaryFeature"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.FluidBoundaryFeature(cPtr, owner);
    }
    else if (type.equals("FrontierFeature"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.FrontierFeature(cPtr, owner);
    }
    else if (type.equals("GeneticBoundaryFeature"))
    {
		com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeneticBoundaryFeature result = new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeneticBoundaryFeature(cPtr, owner);
        return result.isAnHorizon() ? new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.Horizon(cPtr, owner) : result;
    }
    else if (type.equals("GeologicUnitFeature"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeologicUnitFeature(cPtr, owner);
    }
    else if (type.equals("OrganizationFeature"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.OrganizationFeature(cPtr, owner);
    }
    else if (type.equals("SeismicLatticeFeature"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SeismicLatticeFeature(cPtr, owner);
    }
    else if (type.equals("SeismicLineFeature"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SeismicLineFeature(cPtr, owner);
    }
    else if (type.equals("SeismicLineSetFeature"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SeismicLineSetFeature(cPtr, owner);
    }
    else if (type.equals("StratigraphicUnitFeature"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicUnitFeature(cPtr, owner);
    }
    else if (type.equals("TectonicBoundaryFeature"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.TectonicBoundaryFeature(cPtr, owner);
    }
    else if (type.equals("WellboreFeature"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreFeature(cPtr, owner);
    }
    else if (type.equals("GeobodyFeature"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeobodyFeature(cPtr, owner);
    }
	else
		return null;
  }
  
  public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractFeatureInterpretation resqml2_instantiateConcreteInterpretation(long cPtr, boolean owner)
  {
	com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractFeatureInterpretation ret = resqml2_instantiateConcreteStratigraphicOrganizationInterpretation(cPtr, owner);
	if (ret != null) {
		return ret;
	}
  
    if (cPtr == 0) {
      return null;
    }
    String type = ${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
	if (type.equals("BoundaryFeatureInterpretation"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.BoundaryFeatureInterpretation(cPtr, owner);
    }
    else if (type.equals("EarthModelInterpretation"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.EarthModelInterpretation(cPtr, owner);
    }
    else if (type.equals("FaultInterpretation"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.FaultInterpretation(cPtr, owner);
    }
    else if (type.equals("GenericFeatureInterpretation"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GenericFeatureInterpretation(cPtr, owner);
    }
    else if (type.equals("HorizonInterpretation"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.HorizonInterpretation(cPtr, owner);
    }
    else if (type.equals("StratigraphicColumnRankInterpretation"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicColumnRankInterpretation(cPtr, owner);
    }
    else if (type.equals("StratigraphicOccurrenceInterpretation"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicOccurrenceInterpretation(cPtr, owner);
    }
    else if (type.equals("StratigraphicUnitInterpretation"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicUnitInterpretation(cPtr, owner);
    }
    else if (type.equals("StructuralOrganizationInterpretation"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StructuralOrganizationInterpretation(cPtr, owner);
    }
    else if (type.equals("WellboreInterpretation"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreInterpretation(cPtr, owner);
    }
    else if (type.equals("GeobodyBoundaryInterpretation"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeobodyBoundaryInterpretation(cPtr, owner);
    }
    else if (type.equals("GeobodyInterpretation"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeobodyInterpretation(cPtr, owner);
    }
	else
		return null;
  }
  
  public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractRepresentation resqml2_instantiateConcreteRepresentation(long cPtr, boolean owner)
  {
	com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractRepresentation ret = resqml2_0_1_instantiateConcreteWellboreFrameRepresentation(cPtr, owner);
	if (ret != null) {
		return ret;
	}
  
    if (cPtr == 0) {
      return null;
    }
    String type = ${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
	
    if (type.equals("Grid2dRepresentation"))
    {
       return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.Grid2dRepresentation(cPtr, owner);
    }
    else if (type.equals("GridConnectionSetRepresentation"))
    {
       return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GridConnectionSetRepresentation(cPtr, owner);
    }
    else if (type.equals("IjkGridRepresentation"))
    {
		return resqml2_0_1_instantiateConcreteIjkGridRepresentation(cPtr, owner);
    }
    else if (type.equals("NonSealedSurfaceFrameworkRepresentation"))
    {
       return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.NonSealedSurfaceFrameworkRepresentation(cPtr, owner);
    }
    else if (type.equals("PlaneSetRepresentation"))
    {
       return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PlaneSetRepresentation(cPtr, owner);
    }
    else if (type.equals("PointSetRepresentation"))
    {
       return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PointSetRepresentation(cPtr, owner);
    }
    else if (type.equals("PolylineRepresentation"))
    {
       return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PolylineRepresentation(cPtr, owner);
    }
    else if (type.equals("PolylineSetRepresentation"))
    {
       return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PolylineSetRepresentation(cPtr, owner);
    }
    else if (type.equals("RepresentationSetRepresentation"))
    {
       return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.RepresentationSetRepresentation(cPtr, owner);
    }
    else if (type.equals("SubRepresentation"))
    {
       return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SubRepresentation(cPtr, owner);
    }
    else if (type.equals("TriangulatedSetRepresentation"))
    {
       return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.TriangulatedSetRepresentation(cPtr, owner);
    }
    else if (type.equals("UnstructuredGridRepresentation"))
    {
       return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.UnstructuredGridRepresentation(cPtr, owner);
    }
    else if (type.equals("WellboreTrajectoryRepresentation"))
    {
       return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreTrajectoryRepresentation(cPtr, owner);
    }
    else if (type.equals("DeviationSurveyRepresentation"))
    {
       return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.DeviationSurveyRepresentation(cPtr, owner);
    }
	else
		return null;
  }
  
  public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractProperty resqml2_instantiateConcreteProperty(long cPtr, boolean owner)
  {
    if (cPtr == 0) {
      return null;
    }
    String type = ${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
    
    if (type.equals("CategoricalProperty"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.CategoricalProperty(cPtr, owner);
    }
	else if (type.equals("CategoricalPropertySeries"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.CategoricalPropertySeries(cPtr, owner);
    }
    else if (type.equals("CommentProperty"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.CommentProperty(cPtr, owner);
    }
    else if (type.equals("ContinuousProperty"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.ContinuousProperty(cPtr, owner);
    }
    else if (type.equals("ContinuousPropertySeries"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.ContinuousPropertySeries(cPtr, owner);
    }
    else if (type.equals("DiscreteProperty"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.DiscreteProperty(cPtr, owner);
    }
	else if (type.equals("DiscretePropertySeries"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.DiscretePropertySeries(cPtr, owner);
    }
	else
		return null;
  }
  
  public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreFrameRepresentation resqml2_0_1_instantiateConcreteWellboreFrameRepresentation(long cPtr, boolean owner)
  {
    if (cPtr == 0) {
      return null;
    }
    String type = ${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
	if (type.equals("WellboreFrameRepresentation"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreFrameRepresentation(cPtr, owner);
    }
    else if (type.equals("WellboreMarkerFrameRepresentation"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreMarkerFrameRepresentation(cPtr, owner);
    }
	else
		return null;
  }
  
  public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.WellboreFrameRepresentation resqml2_instantiateConcreteWellboreFrameRepresentation(long cPtr, boolean owner)
  {
	return resqml2_0_1_instantiateConcreteWellboreFrameRepresentation(cPtr, owner);
  }
  
  public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractLocal3dCrs resqml2_instantiateConcreteLocal3dCrs(long cPtr, boolean owner)
  {
    if (cPtr == 0) {
      return null;
    }
    String type = ${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
	
    if (type.equals("LocalDepth3dCrs"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.LocalDepth3dCrs(cPtr, owner);
    }
    else if (type.equals("LocalTime3dCrs"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.LocalTime3dCrs(cPtr, owner);
    }
    else
	return null;
  }
  
  public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractGridRepresentation resqml2_instantiateConcreteGridRepresentation(long cPtr, boolean owner)
  {  
    if (cPtr == 0) {
      return null;
    }
    String type = ${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));

    if (type.equals("UnstructuredGridRepresentation"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.UnstructuredGridRepresentation(cPtr, owner);
    }
    else if (type.equals("IjkGridRepresentation"))
    {
		return resqml2_0_1_instantiateConcreteIjkGridRepresentation(cPtr, owner);
    }
    else
		return null;
  }
  
  public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.AbstractIjkGridRepresentation resqml2_0_1_instantiateConcreteIjkGridRepresentation(long cPtr, boolean owner)
  {
    if (cPtr == 0) { return null; }
    com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.AbstractIjkGridRepresentation.geometryKind type = com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.AbstractIjkGridRepresentation.geometryKind
        .swigToEnum(${FESAPI_RESQML2_0_1_NS}_AbstractIjkGridRepresentation_getGeometryKind(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.AbstractIjkGridRepresentation(cPtr, false)));

    if (type == com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.AbstractIjkGridRepresentation.geometryKind.EXPLICIT) {
      return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.IjkGridExplicitRepresentation(cPtr, owner);
    }
    else if (type == com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.AbstractIjkGridRepresentation.geometryKind.PARAMETRIC) {
      return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.IjkGridParametricRepresentation(cPtr, owner);
    }
    else if (type == com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.AbstractIjkGridRepresentation.geometryKind.LATTICE) {
      return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.IjkGridLatticeRepresentation(cPtr, owner);
    }
    else // TODO : see if it is possible to return the object itself instead of a copy.
    {
      return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.AbstractIjkGridRepresentation(cPtr, owner);
    }
  }
  
  public static com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.AbstractStratigraphicOrganizationInterpretation resqml2_instantiateConcreteStratigraphicOrganizationInterpretation(long cPtr, boolean owner)
  {
    if (cPtr == 0) {
      return null;
    }
    String type = ${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(cPtr, new com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject(cPtr, false));
	if (type.equals("StratigraphicOccurrenceInterpretation"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicOccurrenceInterpretation(cPtr, owner);
    }
	else if (type.equals("StratigraphicColumnRankInterpretation"))
    {
        return new com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicColumnRankInterpretation(cPtr, owner);
    }
	else
		return null;
  }
%}

namespace COMMON_NS
{
	%typemap(javaout) AbstractObject*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.resqml2_instantiateConcreteObject(cPtr, $owner);
		return ret;
	}
	
	%typemap(javaimports) SWIGTYPE %{
		import com.f2i.energisticsStandardsApi.*;
	%}
}

namespace RESQML2_NS
{		
	%typemap(javaout) AbstractFeature*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.resqml2_instantiateConcreteFeature(cPtr, $owner);
		return ret;
	}
	
	%typemap(javaout) AbstractFeatureInterpretation*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.resqml2_instantiateConcreteInterpretation(cPtr, $owner);
		return ret;
	}
	
	%typemap(javaout) AbstractRepresentation*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.resqml2_instantiateConcreteRepresentation(cPtr, $owner);
		return ret;
	}
	
	%typemap(javaout) AbstractGridRepresentation*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.resqml2_instantiateConcreteGridRepresentation(cPtr, $owner);
		return ret;
	}
	
	%typemap(javaout) AbstractLocal3dCrs*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.resqml2_instantiateConcreteLocal3dCrs(cPtr, $owner);
		return ret;
	}
	
	%typemap(javaout) AbstractProperty*, AbstractValuesProperty*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.resqml2_instantiateConcreteProperty(cPtr, $owner);
		return ret;
	}

	%typemap(javaout) WellboreFrameRepresentation*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.resqml2_instantiateConcreteWellboreFrameRepresentation(cPtr, $owner);
		return ret;
	}

	%typemap(javaimports) SWIGTYPE %{
		import com.f2i.energisticsStandardsApi.*;
	%}
}

namespace RESQML2_0_1_NS
{	
	%typemap(javaout) AbstractIjkGridRepresentation*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.resqml2_0_1_instantiateConcreteIjkGridRepresentation(cPtr, $owner);
		return ret;
	}
	
	%typemap(javaout) AbstractStratigraphicOrganizationInterpretation*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.resqml2_instantiateConcreteStratigraphicOrganizationInterpretation(cPtr, $owner);
		return ret;
	}

	%typemap(javaimports) SWIGTYPE %{
		import com.f2i.energisticsStandardsApi.*;
	%}
}

