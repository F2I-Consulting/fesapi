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
	class FaultSinglePatchTriangulatedSetRepresentationTest : public commontest::AbstractTest {
	public:

		static constexpr char const* defaultUuid = "110124ae-ff4e-478c-90c1-30900e01485e";
		static constexpr char const* defaultTitle = "FaultSinglePatchTriangulatedSetRepresentationTest";

		/**
		* Creation of a testing object from an EPC document path. At serialize() call,
		* exising .epc file will be erased. 
		* @param repoPath the path of the .epc file (including .epc extension)
		*/
		FaultSinglePatchTriangulatedSetRepresentationTest(const std::string & repoPath);

	protected:
		void initRepo();
		void readRepo();

	private:
		static constexpr double nodesFaultSinglePatchTriangulatedSetRepresentation[] = {
			150, 0, 200,
			150, 100, 200,
			150, 200, 200,
			250, 0, 300,
			250, 100, 300,
			250, 200, 300,
			300, 0, 350,
			300, 100, 350,
			300, 200, 350,
			450, 0, 500,
			450, 100, 500,
			450, 200, 500,
			500, 0, 550,
			500, 100, 550,
			500, 200, 550,
			600, 0, 650,
			600, 100, 650,
			600, 200, 650 };
		static constexpr uint32_t triangleNodeIndexFault[60] = { 0,4,3, 0,1,4, 1,2,4, 2,5,4,
			3,7,6, 3,4,7, 4,5,7, 5,8,7,
			6,10,9, 6,7,10, 7,8,10, 8,11,10,
			9,13,12, 9,10,13, 10,11,13, 11,14,13,
			12,16,15, 12,13,16, 13,14,16, 14,17,16 };
	};
}
