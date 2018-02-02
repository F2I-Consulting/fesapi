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
%pragma(java) jniclasscode=%{
  public static com.f2i.energisticsStandardsApi.witsml1_4_1_1.AbstractObject witsml1_4_1_1_instantiateConcreteObject(long cPtr, boolean owner)
  {
    com.f2i.energisticsStandardsApi.witsml1_4_1_1.AbstractObject ret = null;
    if (cPtr == 0) {
      return ret;
    }
	
    String type = witsml1_4_1_1_AbstractObject_getXmlTag(cPtr, new com.f2i.energisticsStandardsApi.witsml1_4_1_1.AbstractObject(cPtr, false));
    if (type.equals("coordinateReferenceSystems"))
    {
        ret = new com.f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem(cPtr, owner);
    }
    else if (type.equals("formationMarkers"))
    {
        ret = new com.f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker(cPtr, owner);
    }
    else if (type.equals("logs"))
    {
        ret = new com.f2i.energisticsStandardsApi.witsml1_4_1_1.Log(cPtr, owner);
    }
    else if (type.equals("trajectorys"))
    {
        ret = new com.f2i.energisticsStandardsApi.witsml1_4_1_1.Trajectory(cPtr, owner);
    }
    else if (type.equals("wells"))
    {
        ret = new com.f2i.energisticsStandardsApi.witsml1_4_1_1.Well(cPtr, owner);
    }
    else if (type.equals("wellbores"))
    {
        ret = new com.f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore(cPtr, owner);
    }
	else
	{
		throw new IllegalArgumentException("Encountered type " + type + " that is not known to be a Resqml concrete class");
	}
	
	return ret;
  }
%}

namespace witsml1_4_1_1
{	
	%typemap(javaout) AbstractObject*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.witsml1_4_1_1_instantiateConcreteObject(cPtr, $owner);
		return ret;
	}
}


