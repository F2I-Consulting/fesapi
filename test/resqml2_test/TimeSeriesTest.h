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
	class TimeSeriesTest : public commontest::AbstractTest {
	public:
		static constexpr char const* timeSeriesUuid = "d443d5b4-1c95-48c6-a239-98f50f6151f7";
		static constexpr char const* prop1Uuid = "481c8393-e9f4-403f-a119-d68affaa96e8";
		static constexpr char const* prop2Uuid = "43b0f9e7-c39c-43fc-aafe-7948f5a43a2b";
		static constexpr char const* prop3Uuid = "f24666e7-fede-411c-af41-376b19f933a7";
		static constexpr char const* partialGridUuid = "9d5b27b3-6d67-4c56-8600-2e7377b771e3";
		static constexpr char const* rep1Uuid = "8c515fe5-025f-49dd-b613-b1b020b97f6d";
		static constexpr char const* rep2Uuid = "87cb4efd-69c0-4c21-a2f6-ba34f5b65ef7";
		static constexpr char const* rep3Uuid = "2dad71a9-e83f-4160-9fa5-7d54afae46af";

		/**
		* Creation of a testing object from an EPC document path. At serialize() call,
		* exising .epc file will be erased.
		* @param repoPath the path of the .epc file (including .epc extension)
		*/
		TimeSeriesTest(const std::string & repoPath);

	private:

		void buildTimeSeriesProp();
		void buildTimeSeriesRep();

		void initRepo() final;
		void readRepo() final;
	};
}
