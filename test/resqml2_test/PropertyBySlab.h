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

#include "AbstractObjectTest.h"

namespace COMMON_NS {
	class DataObjectRepository;
}

namespace resqml2_test {
	class PropertyBySlab : public commontest::AbstractObjectTest {
	public:
		static const char* defaultContinuousPropComputeUuid;
		static const char* defaultDiscretePropComputeUuid;
		static const char* defaultPropNoComputeUuid;
		static const char* defaultDiscretePropNoComputeUuid;

		/**
		* Creation of a testing object from an EPC document path. At serialize() call,
		* exising .epc file will be erased.
		* @param repoPath the path of the .epc file (including .epc extension)
		*/
		PropertyBySlab(const std::string & repoPath);

		/**
		* Creation of a testing object from an existing EPC document.
		* @param repo an existing EPC document
		* @param init true if this object is created for initialization purpose else false if it is
		* created for reading purpose. According to init value a inirepo() or readRepo() is called.
		*/
		PropertyBySlab(COMMON_NS::DataObjectRepository * repo, bool init);
	protected:
		void initRepoHandler();
		void readRepoHandler();
	};
}

