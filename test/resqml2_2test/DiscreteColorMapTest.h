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
#include <iostream>

namespace resqml2_2test {
	class DiscreteColorMapTest : public commontest::AbstractTest {
	public:
		static char const* defaultUuid;
		static char const* defaultTitle;
		static char const* uuidOrganizationFeature;
		static char const* titleOrganizationFeature;
		static char const* uuidEarthModelInterpretation;
		static char const* titleEarthModelInterpretation;
		static char const* uuidLocalDepth3dCrs;
		static char const* titleLocalDepth3dCrs;
		static char const* uuidIjkGridExplicitRepresentation;
		static char const* titleIjkGridExplicitRepresentation;
		static char const* uuidPropertyKind;
		static char const* titlePropertyKind;
		static char const* uuidDiscreteProperty;
		static char const* titleDiscreteProperty;
		static char const* uuidGraphicalInformationSet;
		static char const* titleGraphicalInformationSet;
		static char const* uuidPropertyKindDiscreteColorMap;
		static char const* titlePropertyKindDiscreteColorMap;

		DiscreteColorMapTest(const std::string & repoPath);

	protected:
		void initRepo();
		void readRepo();
	};
}
