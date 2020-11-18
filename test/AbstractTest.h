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

#include "common/DataObjectRepository.h"

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

		virtual ~AbstractTest() = default;

		/**
		 * This methods runs a serailization test. It handles the creation of an EPC document,
		 * calls initRepo() and serialize the EPC document. The EPC document is deleted at the very end
		 * of this method.
		 */
		void serialize();

		/** 
		 * This methods runs a deserialization test. It handles the deserialization of an existing EPC document
		 * and calls readRepo(). The EPC document is deleted at the very end of this method.
		 */
		void deserialize();
	
		/** 
		 * As initialization differs from one unit test to another, it is virtual in this most general testing class.
		 */ 
		virtual void initRepo() = 0;

		/** 
		 * As reading differs from one unit test to another, it is virtual in this most general testing class.
		 */
		virtual void readRepo() = 0;

		COMMON_NS::DataObjectRepository::EnergisticsStandard defaultEmlVersion;
		COMMON_NS::DataObjectRepository::EnergisticsStandard defaultResqmlVersion;

	protected:
		COMMON_NS::DataObjectRepository* repo;
		const std::string epcDocPath;
	};
}
