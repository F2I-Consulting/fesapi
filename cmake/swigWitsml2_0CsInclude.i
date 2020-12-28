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
%pragma(csharp) imclasscode=%{
  public static F2iConsulting.Fesapi.${FESAPI_WITSML2_0_NS}.AbstractObject witsml2_0_instantiateConcreteObject(global::System.IntPtr cPtr, bool owner)
  {
    F2iConsulting.Fesapi.${FESAPI_WITSML2_0_NS}.AbstractObject ret = null;
    if (cPtr == global::System.IntPtr.Zero) {
      return ret;
    }
	
    string type = $modulePINVOKE.${FESAPI_WITSML2_0_NS}_AbstractObject_getXmlTag(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
	if (type == "coordinateReferenceSystems")
    {
        ret = new F2iConsulting.Fesapi.${FESAPI_WITSML2_0_NS}.CoordinateReferenceSystem(cPtr, owner);
    }
    else if (type == "formationMarkers")
    {
        ret = new F2iConsulting.Fesapi.${FESAPI_WITSML2_0_NS}.FormationMarker(cPtr, owner);
    }
    else if (type == "logs")
    {
        ret = new F2iConsulting.Fesapi.${FESAPI_WITSML2_0_NS}.Log(cPtr, owner);
    }
    else if (type == "trajectorys")
    {
        ret = new F2iConsulting.Fesapi.${FESAPI_WITSML2_0_NS}.Trajectory(cPtr, owner);
    }
    else if (type == "wells")
    {
        ret = new F2iConsulting.Fesapi.${FESAPI_WITSML2_0_NS}.Well(cPtr, owner);
    }
    else if (type == "wellbores")
    {
        ret = new F2iConsulting.Fesapi.${FESAPI_WITSML2_0_NS}.Wellbore(cPtr, owner);
    }
	else
	{
		throw new System.ArgumentException(string.Format("Encountered type '{0}' that is not known to be a Witsml concrete class", type.ToString()));
	}
	
	return ret;
  }
%}

namespace WITSML2_0_NS
{	
	%typemap(csout, excode=SWIGEXCODE) AbstractObject*  {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.witsml2_0_instantiateConcreteObject(cPtr, $owner);$excode
		return ret;
	}
}

