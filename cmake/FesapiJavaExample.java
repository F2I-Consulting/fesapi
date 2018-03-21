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

import java.util.UUID;

import com.f2i.energisticsStandardsApi.LocalDepth3dCrsVector;
import com.f2i.energisticsStandardsApi.eml20__LengthUom;
import com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.EpcDocument;
import com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.LocalDepth3dCrs;

public class FesapiJavaExample {
	/**
	 * Loading the FesapiCpp native library
	 */
	static {
		System.loadLibrary("${CPP_LIBRARY_NAME}.${Fesapi_VERSION}");
	}
	
	private static void serialize()
	{
		EpcDocument epc = new EpcDocument("testingPackageJava.epc");
	
	    try {
	    	LocalDepth3dCrs crs = epc.createLocalDepth3dCrs(UUID.randomUUID().toString(), "UTF8 Crs title : éàç : олег1", 0.0, 0.0, 0.0, 0.0, eml20__LengthUom.eml20__LengthUom__m, 5215, eml20__LengthUom.eml20__LengthUom__m, "Unknown", false);
	        epc.serialize();
	    }
	    finally {
	        epc.close();
	    }
	}
	
	private static void deserialize()
	{
		EpcDocument epc = new EpcDocument("testingPackageJava.epc");
	
	    try {
	    	String status = epc.deserialize();
	    	if (!status.isEmpty()) {
	    		System.out.println("Status : " + status);
	    	}
	        LocalDepth3dCrsVector crs_set = epc.getLocalDepth3dCrsSet();
	        System.out.println("CRS title is " + crs_set.get(0).getTitle());
	    }
	    finally {
	        epc.close();
	    }
	}
	
	public static void main(String[] args) {
		serialize();
	    deserialize();
	}
}