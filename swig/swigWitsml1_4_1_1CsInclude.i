%pragma(csharp) imclasscode=%{
  public static f2i.energisticsStandardsApi.witsml1_4_1_1.AbstractObject witsml1_4_1_1_instantiateConcreteObject(global::System.IntPtr cPtr, bool owner)
  {
    f2i.energisticsStandardsApi.witsml1_4_1_1.AbstractObject ret = null;
    if (cPtr == global::System.IntPtr.Zero) {
      return ret;
    }
	
    string type = $modulePINVOKE.witsml1_4_1_1_AbstractObject_getXmlTag(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
	if (type == "coordinateReferenceSystems")
    {
        ret = new f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem(cPtr, owner);
    }
    else if (type == "formationMarkers")
    {
        ret = new f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker(cPtr, owner);
    }
    else if (type == "logs")
    {
        ret = new f2i.energisticsStandardsApi.witsml1_4_1_1.Log(cPtr, owner);
    }
    else if (type == "trajectorys")
    {
        ret = new f2i.energisticsStandardsApi.witsml1_4_1_1.Trajectory(cPtr, owner);
    }
    else if (type == "wells")
    {
        ret = new f2i.energisticsStandardsApi.witsml1_4_1_1.Well(cPtr, owner);
    }
    else if (type == "wellbores")
    {
        ret = new f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore(cPtr, owner);
    }
	else
	{
		throw new System.ArgumentException(string.Format("Encountered type '{0}' that is not known to be a Witsml concrete class", type.ToString()));
	}
	
	return ret;
  }
%}

namespace witsml1_4_1_1
{	
	%typemap(csout, excode=SWIGEXCODE) AbstractObject*  {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.witsml1_4_1_1_instantiateConcreteObject(cPtr, $owner);$excode
		return ret;
	}
}