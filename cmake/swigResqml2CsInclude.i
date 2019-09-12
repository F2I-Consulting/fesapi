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
Basically this file add methods resqml2_instantiate* which will create the right C# instance according to what it is exactly.
**********************************************************************/

%pragma(csharp) imclasscode=%{
public static f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject resqml2_instantiateConcreteObject(global::System.IntPtr cPtr, bool owner)
{
	f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject ret = null;
	if (cPtr == global::System.IntPtr.Zero) {
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
	
    string type = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
	if (type == "Activity")
    {
        ret = new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.Activity(cPtr, owner);
    }
	else if (type == "ActivityTemplate")
    {
        ret = new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.ActivityTemplate(cPtr, owner);
    }
    else if (type == "EpcExternalPartReference")
    {
        ret = new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.HdfProxy(cPtr, owner);
    }
    else if (type == "MdDatum")
    {
        ret = new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.MdDatum(cPtr, owner);
    }
    else if (type == "PropertyKind")
    {
        ret = new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PropertyKind(cPtr, owner);
    }
    else if (type == "PropertySet")
    {
        ret = new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PropertySet(cPtr, owner);
    }
    else if (type == "StratigraphicColumn")
    {
        ret = new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicColumn(cPtr, owner);
    }
    else if (type == "StringTableLookup")
    {
        ret = new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StringTableLookup(cPtr, owner);
    }
    else if (type == "TimeSeries")
    {
        ret = new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.TimeSeries(cPtr, owner);
    }
	else if (type == "Well")
	{
		ret = new f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.Well(cPtr, owner);
	}
	else if (type == "Wellbore")
	{
		ret = new f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.Wellbore(cPtr, owner);
	}
	else if (type == "WellCompletion")
	{
		ret = new f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.WellCompletion(cPtr, owner);
	}
	else if (type == "WellboreCompletion")
	{
		ret = new f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.WellboreCompletion(cPtr, owner);
	}else
	{
		throw new System.ArgumentException(string.Format("Encountered type '{0}' that is not known to be a Resqml or Witsml concrete class", type.ToString()));
	}
	
	return ret;
  }
  
  public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractFeature resqml2_instantiateConcreteFeature(global::System.IntPtr cPtr, bool owner)
  {
    if (cPtr == global::System.IntPtr.Zero) {
      return null;
    }
    string type = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
	if (type == "BoundaryFeature")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.BoundaryFeature(cPtr, owner);
    }  
    else if (type == "FluidBoundaryFeature")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.FluidBoundaryFeature(cPtr, owner);
    }
    else if (type == "FrontierFeature")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.FrontierFeature(cPtr, owner);
    }
    else if (type == "GeneticBoundaryFeature")
    {
		f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeneticBoundaryFeature result = new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeneticBoundaryFeature(cPtr, owner);
        return result.isAnHorizon() ? new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.Horizon(cPtr, owner) : result;
    }
    else if (type == "GeologicUnitFeature")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeologicUnitFeature(cPtr, owner);
    }
    else if (type == "OrganizationFeature")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.OrganizationFeature(cPtr, owner);
    }
    else if (type == "SeismicLatticeFeature")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SeismicLatticeFeature(cPtr, owner);
    }
    else if (type == "SeismicLineFeature")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SeismicLineFeature(cPtr, owner);
    }
    else if (type == "SeismicLineSetFeature")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SeismicLineSetFeature(cPtr, owner);
    }
    else if (type == "StratigraphicUnitFeature")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicUnitFeature(cPtr, owner);
    }
    else if (type == "TectonicBoundaryFeature")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.TectonicBoundaryFeature(cPtr, owner);
    }
    else if (type == "WellboreFeature")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreFeature(cPtr, owner);
    }
    else if (type == "GeobodyFeature")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeobodyFeature(cPtr, owner);
    }
	else
		return null;
  }
  
  public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractFeatureInterpretation resqml2_instantiateConcreteInterpretation(global::System.IntPtr cPtr, bool owner)
  {
	f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractFeatureInterpretation ret = resqml2_instantiateConcreteStratigraphicOrganizationInterpretation(cPtr, owner);
	if (ret != null) {
		return ret;
	}
  
    if (cPtr == global::System.IntPtr.Zero) {
      return null;
    }
    string type = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
	if (type == "BoundaryFeatureInterpretation")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.BoundaryFeatureInterpretation(cPtr, owner);
    }
    else if (type == "EarthModelInterpretation")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.EarthModelInterpretation(cPtr, owner);
    }
    else if (type == "FaultInterpretation")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.FaultInterpretation(cPtr, owner);
    }
    else if (type == "GenericFeatureInterpretation")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GenericFeatureInterpretation(cPtr, owner);
    }
    else if (type == "HorizonInterpretation")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.HorizonInterpretation(cPtr, owner);
    }
    else if (type == "StratigraphicColumnRankInterpretation")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicColumnRankInterpretation(cPtr, owner);
    }
    else if (type == "StratigraphicOccurrenceInterpretation")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicOccurrenceInterpretation(cPtr, owner);
    }
    else if (type == "StratigraphicUnitInterpretation")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicUnitInterpretation(cPtr, owner);
    }
    else if (type == "StructuralOrganizationInterpretation")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StructuralOrganizationInterpretation(cPtr, owner);
    }
    else if (type == "WellboreInterpretation")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreInterpretation(cPtr, owner);
    }
    else if (type == "GeobodyBoundaryInterpretation")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeobodyBoundaryInterpretation(cPtr, owner);
    }
    else if (type == "GeobodyInterpretation")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GeobodyInterpretation(cPtr, owner);
    }
	else
		return null;
  }
  
  public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractRepresentation resqml2_instantiateConcreteRepresentation(global::System.IntPtr cPtr, bool owner)
  {
	f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractRepresentation ret = resqml2_instantiateConcreteWellboreFrameRepresentation(cPtr, owner);
	if (ret != null) {
		return ret;
	}
	
	ret = resqml2_instantiateConcreteGridRepresentation(cPtr, owner);
	if (ret != null) {
		return ret;
	}
  
    if (cPtr == global::System.IntPtr.Zero) {
      return null;
    }
    string type = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
	
    if (type == "Grid2dRepresentation")
    {
       return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.Grid2dRepresentation(cPtr, owner);
    }
    else if (type == "GridConnectionSetRepresentation")
    {
       return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GridConnectionSetRepresentation(cPtr, owner);
    }
    else if (type == "NonSealedSurfaceFrameworkRepresentation")
    {
       return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.NonSealedSurfaceFrameworkRepresentation(cPtr, owner);
    }
    else if (type == "PlaneSetRepresentation")
    {
       return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PlaneSetRepresentation(cPtr, owner);
    }
    else if (type == "PointSetRepresentation")
    {
       return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PointSetRepresentation(cPtr, owner);
    }
    else if (type == "PolylineRepresentation")
    {
       return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PolylineRepresentation(cPtr, owner);
    }
    else if (type == "PolylineSetRepresentation")
    {
       return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PolylineSetRepresentation(cPtr, owner);
    }
    else if (type == "RepresentationSetRepresentation")
    {
       return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.RepresentationSetRepresentation(cPtr, owner);
    }
    else if (type == "SubRepresentation")
    {
       return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SubRepresentation(cPtr, owner);
    }
    else if (type == "TriangulatedSetRepresentation")
    {
       return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.TriangulatedSetRepresentation(cPtr, owner);
    }
    else if (type == "WellboreTrajectoryRepresentation")
    {
       return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreTrajectoryRepresentation(cPtr, owner);
    }
    else if (type == "DeviationSurveyRepresentation")
    {
       return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.DeviationSurveyRepresentation(cPtr, owner);
    }
	else
		return null;
  }
  
  public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractProperty resqml2_instantiateConcreteProperty(global::System.IntPtr cPtr, bool owner)
  {
    if (cPtr == global::System.IntPtr.Zero) {
      return null;
    }
    string type = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
    
    if (type == "CategoricalProperty")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.CategoricalProperty(cPtr, owner);
    }
	else if (type == "CategoricalPropertySeries")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.CategoricalPropertySeries(cPtr, owner);
    }
    else if (type == "CommentProperty")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.CommentProperty(cPtr, owner);
    }
    else if (type == "ContinuousProperty")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.ContinuousProperty(cPtr, owner);
    }
    else if (type == "ContinuousPropertySeries")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.ContinuousPropertySeries(cPtr, owner);
    }
    else if (type == "DiscreteProperty")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.DiscreteProperty(cPtr, owner);
    }
	else if (type == "DiscretePropertySeries")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.DiscretePropertySeries(cPtr, owner);
    }
	else
		return null;
  }
  
  public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreFrameRepresentation resqml2_instantiateConcreteWellboreFrameRepresentation(global::System.IntPtr cPtr, bool owner)
  {
    if (cPtr == global::System.IntPtr.Zero) {
      return null;
    }
    string type = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
	if (type == "WellboreFrameRepresentation")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreFrameRepresentation(cPtr, owner);
    }
    else if (type == "WellboreMarkerFrameRepresentation")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.WellboreMarkerFrameRepresentation(cPtr, owner);
    }
	else
		return null;
  }
  
  public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractLocal3dCrs resqml2_instantiateConcreteLocal3dCrs(global::System.IntPtr cPtr, bool owner)
  {
    if (cPtr == global::System.IntPtr.Zero) {
      return null;
    }
    string type = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
	
    if (type == "LocalDepth3dCrs")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.LocalDepth3dCrs(cPtr, owner);
    }
    else if (type == "LocalTime3dCrs")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.LocalTime3dCrs(cPtr, owner);
    }
	else
		return null;
  }
  
  public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.AbstractGridRepresentation resqml2_instantiateConcreteGridRepresentation(global::System.IntPtr cPtr, bool owner)
  {  
    if (cPtr == global::System.IntPtr.Zero) {
      return null;
    }
    string type = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));

    if (type == "UnstructuredGridRepresentation")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.UnstructuredGridRepresentation(cPtr, owner);
    }
	else if (type == "IjkGridRepresentation")
    {
		return resqml2_0_1_instantiateConcreteIjkGridRepresentation(cPtr, owner);
    }
	else
		return null;
  }
  
  public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.AbstractIjkGridRepresentation resqml2_0_1_instantiateConcreteIjkGridRepresentation(global::System.IntPtr cPtr, bool owner)
  {
    if (cPtr == global::System.IntPtr.Zero) {
      return null;
    }
    int type = fesapiPINVOKE.${FESAPI_RESQML2_0_1_NS}_AbstractIjkGridRepresentation_getGeometryKind(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));

    if (type == (int)f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.AbstractIjkGridRepresentation.geometryKind.EXPLICIT)
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.IjkGridExplicitRepresentation(cPtr, owner);
    }
    else if (type == (int)f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.AbstractIjkGridRepresentation.geometryKind.PARAMETRIC)
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.IjkGridParametricRepresentation(cPtr, owner);
    }
    else if (type == (int)f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.AbstractIjkGridRepresentation.geometryKind.LATTICE)
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.IjkGridLatticeRepresentation(cPtr, owner);
    }
    else // TODO : see if it is possible to return the object itself instead of a copy.
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.AbstractIjkGridRepresentation(cPtr, owner);
    }
  }
  
  public static f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.AbstractStratigraphicOrganizationInterpretation resqml2_instantiateConcreteStratigraphicOrganizationInterpretation(global::System.IntPtr cPtr, bool owner)
  {
    if (cPtr == global::System.IntPtr.Zero) {
      return null;
    }
    string type = $modulePINVOKE.${FESAPI_COMMON_NS}_AbstractObject_getXmlTag(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
	if (type == "StratigraphicOccurrenceInterpretation")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicOccurrenceInterpretation(cPtr, owner);
    }
	else if (type == "StratigraphicColumnRankInterpretation")
    {
        return new f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.StratigraphicColumnRankInterpretation(cPtr, owner);
    }
	else
		return null;
  }
%}

namespace COMMON_NS
{	
	%typemap(csout, excode=SWIGEXCODE) AbstractObject*  {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.resqml2_instantiateConcreteObject(cPtr, $owner);$excode
		return ret;
	}
}

namespace RESQML2_NS
{		
	%typemap(csout, excode=SWIGEXCODE) AbstractFeature*  {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.resqml2_instantiateConcreteFeature(cPtr, $owner);$excode
		return ret;
	}
	
	%typemap(csout, excode=SWIGEXCODE) AbstractFeatureInterpretation*  {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.resqml2_instantiateConcreteInterpretation(cPtr, $owner);$excode
		return ret;
	}
	
	%typemap(csout, excode=SWIGEXCODE) AbstractRepresentation*  {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.resqml2_instantiateConcreteRepresentation(cPtr, $owner);$excode
		return ret;
	}
	
	%typemap(csout, excode=SWIGEXCODE) AbstractGridRepresentation*  {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.resqml2_instantiateConcreteGridRepresentation(cPtr, $owner);$excode
		return ret;
	}
	
	%typemap(csout, excode=SWIGEXCODE) AbstractLocal3dCrs*  {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.resqml2_instantiateConcreteLocal3dCrs(cPtr, $owner);$excode
		return ret;
	}
	
	%typemap(csout, excode=SWIGEXCODE) AbstractProperty*, AbstractValuesProperty*   {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.resqml2_instantiateConcreteProperty(cPtr, $owner);$excode
		return ret;
	}
}

namespace RESQML2_0_1_NS
{	
	%typemap(csout, excode=SWIGEXCODE) WellboreFrameRepresentation*  {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.resqml2_instantiateConcreteWellboreFrameRepresentation(cPtr, $owner);$excode
		return ret;
	}
	
	%typemap(csout, excode=SWIGEXCODE) AbstractIjkGridRepresentation*  {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.resqml2_0_1_instantiateConcreteIjkGridRepresentation(cPtr, $owner);$excode
		return ret;
	}
	
	%typemap(csout, excode=SWIGEXCODE) AbstractStratigraphicOrganizationInterpretation*   {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.resqml2_instantiateConcreteStratigraphicOrganizationInterpretation(cPtr, $owner);$excode
		return ret;
	}
}

