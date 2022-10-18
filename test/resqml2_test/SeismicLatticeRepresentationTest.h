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
#include <string>

namespace resqml2_test {
	class SeismicLatticeRepresentationTest : public commontest::AbstractTest {
	public:
		static constexpr char const* defaultUuidFeature = "3e04d513-7d2c-4cc3-853c-a3a651c5eb4a";
		static constexpr char const* defaultTitleFeature = "Seismic Lattice Feature";
		static constexpr char const* defaultUuidInterp = "3d7ae7ac-c605-493c-8067-547411fe30de";
		static constexpr char const* defaultTitleInterp = "Seismic Lattice Interp";
		static constexpr char const* defaultUuid = "c218fe9a-5080-4322-82fc-d7a1efb6da99";
		static constexpr char const* defaultTitle = "Seismic Grid 2d Representation";
		static constexpr char const* ijkLatticeGridUuid = "a0b270bf-c50c-4f74-a6df-169a5dcc13a7";

		/**
		* Creation of a testing object from an EPC document path. At serialize() call,
		* exising .epc file will be erased. 
		* @param repoPath the path of the .epc file (including .epc extension)
		*/
		SeismicLatticeRepresentationTest(const std::string & repoPath);

	protected:
		void initRepo();
		void readRepo();
	};
}
