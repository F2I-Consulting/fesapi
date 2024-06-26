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

#include "../AbstractTest.h"

namespace witsml2_test {
	class WellTest : public commontest::AbstractTest {
	public:
		static const char* defaultUuid;
		static const char* defaultTitle;
		static const time_t defaultTimestamp;

		/**
		* Creation of a testing object from an EPC document path. At serialize() call,
		* exising .epc file will be erased.
		* @param epcDocPath the path of the .epc file (including .epc extension)
		*/
		WellTest(const std::string & epcDocPath);

	protected:
		static constexpr char const* witsmlWellboreUuid = "2632b49d-b18a-4d83-a85d-d6a2bd879d20";
		static constexpr char const* resqmlWellboreFeatureUuid = "044823a6-2d42-4b32-9606-e7c1c4652804";

		void initRepo();
		void readRepo();
	};
}
