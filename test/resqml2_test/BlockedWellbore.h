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

#include "AbstractTest.h"

namespace resqml2_test {
	class BlockedWellbore : public commontest::AbstractTest {
	public:
		static constexpr char const* defaultUuid = "442b1bed-c997-42ce-8b99-8e89a23edc0d";
		static constexpr char const* defaultTitle = "BlockedWellbore representation with null value";
		static constexpr char const* defaultUuidNoNullValue = "02318f5e-399e-43a0-9e7c-340b5954eaf2";
		static constexpr char const* defaultTitleNoNullValue = "BlockedWellbore representation without null value";
		static constexpr char const* defaultGridUuid = "0987a24d-24c0-49ea-bae3-f6c9d91a8d46";

		/**
		* Creation of a testing object from an EPC document path. At serialize() call,
		* exising .epc file will be erased. 
		* @param repoPath the path of the .epc file (including .epc extension)
		*/
		BlockedWellbore(const std::string & repoPath);

	protected:
		void initRepo();
		void readRepo();
	};
}
