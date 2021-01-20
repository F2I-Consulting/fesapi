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
package com.f2i_consulting.fesapi.example;

import com.f2i_consulting.fesapi.MapStringString;
import com.f2i_consulting.fesapi.ResourceVector;
import com.f2i_consulting.fesapi.Energistics.Etp.v12.Datatypes.Object.Resource;
import com.f2i_consulting.fesapi.Energistics.Etp.v12.Protocol.Discovery.GetResourcesResponse;
import com.f2i_consulting.fesapi.Energistics.Etp.v12.Protocol.Store.GetDataObjects;
import com.f2i_consulting.fesapi.${FESAPI_ETP_NS}.AbstractSession;
import com.f2i_consulting.fesapi.${FESAPI_ETP_NS}.DiscoveryHandlers;

public class MyOwnDiscoveryProtocolHandlers extends DiscoveryHandlers {
	public MyOwnDiscoveryProtocolHandlers(AbstractSession mySession) {
		super(mySession);
	}

	@Override
	public void on_GetResourcesResponse(GetResourcesResponse msg, long correlationId){
		ResourceVector resources = msg.getResources();
		System.out.println(resources.size() + " resources received.");
		for (Resource resource : msg.getResources()) {
			System.out.println("*************************************************");
			System.out.println("uri : " + resource.getUri());
			System.out.println("data type : " + resource.getDataObjectType());
			System.out.println("name : " + resource.getName());
			System.out.println("*************************************************");
		}
		
        System.out.println("Asking to get the first dataobject");
        GetDataObjects gdo = new GetDataObjects();
        MapStringString uriMap = new MapStringString();
        uriMap.put("0", resources.get(0).getUri());
        gdo.setUris(uriMap);
        getSession().send(gdo, 0, 0x02);
	}
}
