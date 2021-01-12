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

import com.f2i_consulting.fesapi.StringVector;
import com.f2i_consulting.fesapi.uint8_t16Array;
import com.f2i_consulting.fesapi.Energistics.Etp.v12.Datatypes.Uuid;
import com.f2i_consulting.fesapi.Energistics.Etp.v12.Protocol.Core.OpenSession;
import com.f2i_consulting.fesapi.${FESAPI_ETP_NS}.AbstractSession;
import com.f2i_consulting.fesapi.${FESAPI_ETP_NS}.CoreHandlers;

public class MyOwnServerCoreHandlers extends CoreHandlers {
	public MyOwnServerCoreHandlers(AbstractSession mySession) {
		super(mySession);
	}

	@Override
	public void on_RequestSession(com.f2i_consulting.fesapi.Energistics.Etp.v12.Protocol.Core.RequestSession rs, long correlationId) {
		System.out.println("Requested a session");
		
        MyServerInitializationParameters serverInitializationParams = new MyServerInitializationParameters();

		// Build Open Session message
		OpenSession openSession = new OpenSession();
		openSession.setApplicationName(serverInitializationParams.getApplicationName());
		openSession.setApplicationVersion(serverInitializationParams.getApplicationVersion());
		uint8_t16Array intArray = new uint8_t16Array();
		intArray.fill((short) 0); 
		Uuid uuid = new Uuid();
		uuid.setArray(intArray);
		openSession.setServerInstanceId(uuid);
		openSession.setSupportedFormats(new StringVector(1, "xml"));
		openSession.setSupportedProtocols(serverInitializationParams.makeSupportedProtocols());
		openSession.setEndpointCapabilities(serverInitializationParams.makeEndpointCapabilities());
		openSession.setSupportedDataObjects(serverInitializationParams.makeSupportedDataObjects());

		getSession().send(openSession, correlationId, 0x02);
	}
}
