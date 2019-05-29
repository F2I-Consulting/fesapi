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
#pragma once

#include <iostream>

#include "nsDefinitions.h"

namespace COMMON_NS {
	class EpcDocument;
}

namespace commontest {
	/**
	 * This abstract class is the most top level testing class. Every test class must derive from it.  
	 */
	class AbstractTest {
	public:
		/**
		 * Creation of a testing object from an EPC document path. At serialize() call,
		 * exising .epc file will be erased. 
		 * @param epcDocPath the path of the .epc file (including .epc extension)
		 */
		AbstractTest(const std::string & epcDocPath);
		
		/**
		 * Creation of a testing object from an existing EPC document.
		 * @param epcDoc an existing EPC document
		 */
		AbstractTest(COMMON_NS::EpcDocument * epcDoc);

		virtual ~AbstractTest() {}

		/**
		 * This methods runs a serailization test. It handles the creation of an EPC document,
		 * calls initEpcDoc() and serialize the EPC document. The EPC document is deleted at the very end
		 * of this method.
		 */
		void serialize();

		/** 
		 * This methods runs a deserialization test. It handles the deserialization of an existing EPC document
		 * and calls readEpcDoc(). The EPC document is deleted at the very end of this method.
		 */
		void deserialize();
	
		/** 
		 * As initialization differs from one unit test to another, it is virtual in this most general testing class.
		 */ 
		virtual void initEpcDoc() = 0;

		/** 
		 * As reading differs from one unit test to another, it is virtual in this most general testing class.
		 */
		virtual void readEpcDoc() = 0;
	protected:
		COMMON_NS::EpcDocument* epcDoc;
		const std::string epcDocPath;
	};
}

