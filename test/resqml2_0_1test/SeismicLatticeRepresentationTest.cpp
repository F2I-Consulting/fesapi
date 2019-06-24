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
#include "resqml2_0_1test/SeismicLatticeRepresentationTest.h"
#include "../catch.hpp"
#include "resqml2_0_1/SeismicLatticeFeature.h"
#include "resqml2_0_1/GenericFeatureInterpretation.h"
#include "resqml2_0_1/Grid2dRepresentation.h"
#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "common/HdfProxy.h"
#include "resqml2_0_1test/LocalDepth3dCrsTest.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace COMMON_NS;
using namespace RESQML2_0_1_NS;

const char* SeismicLatticeRepresentationTest::defaultUuidFeature = "3e04d513-7d2c-4cc3-853c-a3a651c5eb4a";
const char* SeismicLatticeRepresentationTest::defaultTitleFeature = "Seismic Lattice Feature";
const char* SeismicLatticeRepresentationTest::defaultUuidInterp = "3d7ae7ac-c605-493c-8067-547411fe30de";
const char* SeismicLatticeRepresentationTest::defaultTitleInterp = "Seismic Lattice Interp";
const char* SeismicLatticeRepresentationTest::defaultUuid = "c218fe9a-5080-4322-82fc-d7a1efb6da99";
const char* SeismicLatticeRepresentationTest::defaultTitle = "Seismic Grid 2d Representation";

SeismicLatticeRepresentationTest::SeismicLatticeRepresentationTest(const string & repoPath)
	: commontest::AbstractObjectTest(repoPath)
{
}

SeismicLatticeRepresentationTest::SeismicLatticeRepresentationTest(DataObjectRepository* repo, bool init)
	: commontest::AbstractObjectTest(repo)
{
	if (init)
		initRepo();
	else
		readRepo();
}

void SeismicLatticeRepresentationTest::initRepoHandler()
{
	LocalDepth3dCrs * crs = repo->getDataObjectByUuid<LocalDepth3dCrs>(LocalDepth3dCrsTest::defaultUuid);
	if (crs == nullptr) {
		LocalDepth3dCrsTest crsTest(repo, true);
		crs = repo->getDataObjectByUuid<LocalDepth3dCrs>(LocalDepth3dCrsTest::defaultUuid);
	}

	SeismicLatticeFeature* seismicLattice = repo->createSeismicLattice(defaultUuidFeature, defaultTitleFeature, 2, 2, 150, 152, 4, 2);
	GenericFeatureInterpretation* seismicLatticeInterp = repo->createGenericFeatureInterpretation(seismicLattice, defaultUuidInterp, defaultTitleInterp);
	Grid2dRepresentation* seismicLatticeRep = repo->createGrid2dRepresentation(seismicLatticeInterp, crs, defaultUuid, defaultTitle);
	seismicLatticeRep->setGeometryAsArray2dOfLatticePoints3d(4, 2, 0, 0, 0, 1, 0, 0, 0, 1, 0, 250, 200);
}

void SeismicLatticeRepresentationTest::readRepoHandler()
{
	// Feature
	RESQML2_0_1_NS::SeismicLatticeFeature* feature = repo->getDataObjectByUuid<RESQML2_0_1_NS::SeismicLatticeFeature>(defaultUuidFeature);
	REQUIRE(feature->getCrosslineIncrement() == 2);
	REQUIRE(feature->getOriginCrossline() == 152);
	REQUIRE(feature->getInlineIncrement() == 2);
	REQUIRE(feature->getOriginInline() == 150);

	// Grid 2D
	RESQML2_0_1_NS::Grid2dRepresentation* rep = repo->getDataObjectByUuid<RESQML2_0_1_NS::Grid2dRepresentation>(defaultUuid);
	REQUIRE(rep->getSupportingRepresentation() == nullptr);
	REQUIRE(rep->getSeismicSupportOfPatch(0) == nullptr);
	REQUIRE((rep->isISpacingConstant() && rep->isJSpacingConstant()));
	REQUIRE(rep->getXOrigin() == .0);
	REQUIRE(rep->getXOriginInGlobalCrs() == 1000);
	REQUIRE(rep->getYOrigin() == .0);
	REQUIRE(rep->getYOriginInGlobalCrs() == 2000);
	REQUIRE(rep->getNodeCountAlongIAxis() == 4);
	REQUIRE(rep->getNodeCountAlongJAxis() == 2);
	REQUIRE(rep->getISpacing() == 250.0);
	REQUIRE(rep->getJSpacing() == 200.0);
	REQUIRE_THROWS(rep->getIndexOriginOnSupportingRepresentation());
	REQUIRE_THROWS(rep->getIndexOffsetOnSupportingRepresentation(0));
	REQUIRE_THROWS(rep->getNodeCountOnSupportingRepresentation(1));
}
