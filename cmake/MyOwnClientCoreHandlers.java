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

import com.f2i_consulting.fesapi.Energistics.Etp.v12.Datatypes.Object.ContextScopeKind;
import com.f2i_consulting.fesapi.Energistics.Etp.v12.Protocol.Core.OpenSession;
import com.f2i_consulting.fesapi.Energistics.Etp.v12.Protocol.Discovery.GetResources;
import com.f2i_consulting.fesapi.${FESAPI_ETP_NS}.AbstractSession;
import com.f2i_consulting.fesapi.${FESAPI_ETP_NS}.CoreHandlers;

public class MyOwnClientCoreHandlers extends CoreHandlers {
	public MyOwnClientCoreHandlers(AbstractSession mySession) {
		super(mySession);
	}

	@Override
	public void on_OpenSession(OpenSession os, long correlationId) {
		System.out.println("Opened a session");
		
        System.out.println("Asking all dataobjects");
		GetResources mb = new GetResources();
		mb.getContext().setUri("eml:///");
		mb.getContext().setDepth(1);
		mb.setScope(ContextScopeKind.self);
		mb.setCountObjects(true);

		getSession().send(mb);
	}
}
