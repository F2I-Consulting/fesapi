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
package com.f2i.energisticsStandardsApi.example;

import com.f2i.energisticsStandardsApi.Energistics.Etp.v12.Datatypes.Object.DataObject;
import com.f2i.energisticsStandardsApi.Energistics.Etp.v12.Protocol.Store.GetDataObjectsResponse;
import com.f2i.energisticsStandardsApi.${FESAPI_ETP_NS}.AbstractSession;
import com.f2i.energisticsStandardsApi.${FESAPI_ETP_NS}.StoreHandlers;

public class MyOwnStoreProtocolHandlers extends StoreHandlers {
	public MyOwnStoreProtocolHandlers(AbstractSession mySession) {
		super(mySession);
	}

	@Override
	public void on_GetDataObjectsResponse(GetDataObjectsResponse msg, long correlationId){
		for (DataObject dataObj : msg.getDataObjects().values()) {
			System.out.println("*************************************************");
			System.out.println("Resource received : ");
			System.out.println("uri : " + dataObj.getResource().getUri());
			System.out.println("datatype : " + dataObj.getResource().getDataObjectType());
			System.out.println("name : " + dataObj.getResource().getName());
			System.out.println("xml : " + dataObj.getData());
			System.out.println("*************************************************");
		}
		
        System.out.println("Asking to close");
		getSession().close();
	}
}
