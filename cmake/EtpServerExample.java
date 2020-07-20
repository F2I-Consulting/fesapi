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

import com.f2i.energisticsStandardsApi.etp.PlainServer;

public class EtpServerExample {

	/**
	 * Loading the FesapiCpp native library
	 */
	static {
		try {
			System.loadLibrary("${ASSEMBLY_NAME}");
		}
		catch (UnsatisfiedLinkError e) {
			System.out.println("UnsatisfiedLinkError : " + e.toString());
		}
	}

	public static void main(String[] args) {
		MyServerInitializationParameters initParams = new MyServerInitializationParameters();
		PlainServer etpServer = new PlainServer(initParams);

		etpServer.listen("127.0.0.1", 8080, 2);
		
		System.out.println("FINISHED");
	}
}
