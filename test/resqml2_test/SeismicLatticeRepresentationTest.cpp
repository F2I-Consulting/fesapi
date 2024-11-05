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
#include "resqml2_test/SeismicLatticeRepresentationTest.h"

#include "../catch.hpp"

#include "resqml2/GenericFeatureInterpretation.h"
#include "resqml2/Grid2dRepresentation.h"
#include "resqml2/IjkGridLatticeRepresentation.h"
#include "resqml2/SeismicLatticeFeature.h"

using namespace std;
using namespace resqml2_test;
using namespace COMMON_NS;
using namespace RESQML2_NS;

SeismicLatticeRepresentationTest::SeismicLatticeRepresentationTest(const string & repoPath)
	: commontest::AbstractTest(repoPath)
{
}

void SeismicLatticeRepresentationTest::initRepo()
{
	SeismicLatticeFeature* seismicLattice = repo->createSeismicLattice(defaultUuidFeature, defaultTitleFeature, 2, 2, 150, 152, 4, 2);
	GenericFeatureInterpretation* seismicLatticeInterp = repo->createGenericFeatureInterpretation(seismicLattice, defaultUuidInterp, defaultTitleInterp);
	Grid2dRepresentation* seismicLatticeRep = repo->createGrid2dRepresentation(seismicLatticeInterp, defaultUuid, defaultTitle);
	seismicLatticeRep->setGeometryAsArray2dOfLatticePoints3d(4, 2, 0, 0, 0, 1, 0, 0, 0, 1, 0, 250, 200);

	// IJK seismic grid
	IjkGridLatticeRepresentation* ijkGrid = repo->createIjkGridLatticeRepresentation(ijkLatticeGridUuid, "seismic block", 4, 2, 10);
	ijkGrid->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape::vertical, gsoap_resqml2_0_1::resqml20__KDirection::down, true,
		.0, 1.0, 2.0,
		1, .0, .0, 1,
		.0, 1, .0, 2,
		.0, .0, 1, 3
	);
}

void SeismicLatticeRepresentationTest::readRepo()
{
	// Feature
	RESQML2_NS::SeismicLatticeFeature* feature = repo->getDataObjectByUuid<RESQML2_NS::SeismicLatticeFeature>(defaultUuidFeature);
	REQUIRE(feature->getCrosslineIncrement() == 2);
	REQUIRE(feature->getCrosslineOrigin() == 152);
	REQUIRE(feature->getInlineIncrement() == 2);
	REQUIRE(feature->getInlineOrigin() == 150);

	// Grid 2D
	RESQML2_NS::Grid2dRepresentation* rep = repo->getDataObjectByUuid<RESQML2_NS::Grid2dRepresentation>(defaultUuid);
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

	// IJK Grid
	IjkGridLatticeRepresentation* ijkGrid = repo->getDataObjectByUuid<RESQML2_NS::IjkGridLatticeRepresentation>(ijkLatticeGridUuid);
	REQUIRE(ijkGrid->getICellCount() == 4);
	REQUIRE(ijkGrid->getJCellCount() == 2);
	REQUIRE(ijkGrid->getKCellCount() == 10);

	REQUIRE(ijkGrid->getXOrigin() == .0);
	REQUIRE(ijkGrid->getYOrigin() == 1.0);
	REQUIRE(ijkGrid->getZOrigin() == 2.0);

	REQUIRE(ijkGrid->getXIOffset() == 1);
	REQUIRE(ijkGrid->getYIOffset() == .0);
	REQUIRE(ijkGrid->getZIOffset() == .0);

	REQUIRE(ijkGrid->getXJOffset() == .0);
	REQUIRE(ijkGrid->getYJOffset() == 1);
	REQUIRE(ijkGrid->getZJOffset() == .0);

	REQUIRE(ijkGrid->getXKOffset() == .0);
	REQUIRE(ijkGrid->getYKOffset() == .0);
	REQUIRE(ijkGrid->getZKOffset() == 1);

	REQUIRE(ijkGrid->getISpacing() == 1);
	REQUIRE(ijkGrid->getJSpacing() == 2);
	REQUIRE(ijkGrid->getKSpacing() == 3);
}
