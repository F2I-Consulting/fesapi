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
	class DiscreteProperty : public commontest::AbstractTest {
	public:

		static constexpr char const* defaultInt8PropUuid = "5aa6a9d4-253e-43a8-bdf5-621e5df2d425";
		static constexpr char const* defaultUInt8PropUuid = "a5bd7738-d36b-4e1c-bf56-8bcf6ea1e7b2";
		static constexpr char const* defaultInt16PropUuid = "61acbc7f-fb9b-4578-800e-f310e947b865";
		static constexpr char const* defaultUInt16PropUuid = "0eae558f-e57b-47b1-9772-a336e99fd714";
		static constexpr char const* defaultInt32PropUuid = "a0721fbe-fb09-4d0f-aab3-315eca8e416e";
		static constexpr char const* defaultUInt32PropUuid = "6262b43a-451f-4dcd-9388-efc22c3b8dc7";
		static constexpr char const* defaultInt64PropUuid = "eda57b20-4639-4541-87b9-c2b44b46c336";
		static constexpr char const* defaultUInt64PropUuid = "63f34e26-8d45-4a87-9ce7-dee72cf34e9a";

		/**
		* Creation of a testing object from an EPC document path. At serialize() call,
		* exising .epc file will be erased.
		* @param repoPath the path of the .epc file (including .epc extension)
		*/
		DiscreteProperty(const std::string & repoPath);

	protected:
		void initRepo();
		void readRepo();
	};
}

