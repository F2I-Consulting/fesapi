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
#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#endif

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"

#include "common/DataObjectRepository.h"
#include "common/AbstractHdfProxy.h"

#include "EpcDocumentTest.h"
#include "GraphicalInformationSetTest.h"
#include "resqml2_0_1test/LocalDepth3dCrsTest.h"
#include "resqml2_0_1test/HorizonInterpretationTest.h"
#include "resqml2_0_1test/FaultSinglePatchTriangulatedSetRepresentationTest.h"
#include "resqml2_0_1test/FaultMultiPatchTriangulatedSetRepresentationTest.h"
#include "resqml2_0_1test/ActivityTemplateGenericCreationTest.h"
#include "resqml2_0_1test/ActivityCreationTest.h"
#include "resqml2_0_1test/OneTetrahedronUnstructuredGridRepresentationTest.h"
#include "resqml2_0_1test/TimeSeriesTest.h"
#include "resqml2_0_1test/CommentProperty.h"
#include "resqml2_0_1test/ContinuousPropertyOnWellFrameTest.h"
#include "resqml2_0_1test/GridConnectionSetOnPartialGridSet.h"
#include "resqml2_0_1test/WellboreMarkerFrameRepresentationTest.h"
#include "resqml2_0_1test/WellboreFrameRepresentationTest.h"
#include "resqml2_0_1test/WellboreRegularFrameRepresentationTest.h"
#include "resqml2_0_1test/DiscretePropertyUsingLocalKindOnWellFrameTest.h"
#include "resqml2_0_1test/SeismicLatticeRepresentationTest.h"
#include "resqml2_0_1test/Grid2dRepresentationTest.h"
#include "resqml2_0_1test/HorizonOnSeismicLine.h"
#include "resqml2_0_1test/CompressedIjkGridExplicitRepresentationTest.h"
#include "resqml2_0_1test/RightHanded4x3x2ExplicitIjkGrid.h"
#include "resqml2_0_1test/BigIjkGridExplicitRepresentationTest.h"
#include "resqml2_0_1test/BigIjkGridParametricRepresentationTest.h"
#include "resqml2_0_1test/SubRepresentationOnPartialGridConnectionSet.h"
#include "resqml2_0_1test/LgrOnRightHanded4x3x2ExplicitIjkGrid.h"
#include "resqml2_0_1test/InterpretationDomain.h"
#include "resqml2_2test/DiscreteColorMapTest.h"
#include "resqml2_2test/ContinuousColorMapTest.h"
#include "resqml2_0_1test/MultirealPropertyTest.h"
#include "resqml2_0_1test/DiscreteProperty.h"
#include "resqml2_0_1test/PropertyBySlab.h"
#include "witsml2_0test/WellTest.h"
#include "witsml2_0test/Trajectory.h"
#include "witsml2_0test/Perforation.h"
#include "witsml2_0test/WellboreGeometryTest.h"

#if WITH_EXPERIMENTAL
#include "GraphicalInformationSetTest.h"
#include "resqml2_2test/DiscreteColorMapTest.h"
#include "resqml2_2test/ContinuousColorMapTest.h"
#include "resqml2_2test/WellboreFrameRepresentationTest.h"
#include "resqml2_2test/WellboreRegularFrameRepresentationTest.h"
#include "resqml2_2test/SeismicWellboreFrameRepresentationTest.h"
#include "resqml2_2test/SeismicWellboreRegularFrameRepresentationTest.h"
using namespace resqml2_2test;
#endif

using namespace commontest;
using namespace resqml2_0_1test;
using namespace resqml2_2test;
using namespace witsml2_0test;

#define FESAPI_TEST(name, tags, classTest)  TEST_CASE(name, tags)\
{\
	classTest test("../../" #classTest ".epc");\
	test.serialize();\
	test.deserialize();\
}
/*
TEST_CASE( "Deserialize an EPC document", "[epc]")
{
	EpcDocumentTest test("../../testingPackageCpp.epc");
	test.deserialize();
}
*/

#if WITH_EXPERIMENTAL
FESAPI_TEST("Export and import graphical information set", "[graphical information]", GraphicalInformationSetTest)
FESAPI_TEST("Export and import discrete color map on a discrete property", "[graphical information][color map][discrete color map]", DiscreteColorMapTest)
FESAPI_TEST("Export and import continuous color map on a discrete property", "[graphical information][color map][continuous color map]", ContinuousColorMapTest)
FESAPI_TEST("Export and import wellbore frame", "[well]", resqml2_2test::WellboreFrameRepresentationTest)
FESAPI_TEST("Export and import regular wellbore frame", "[well]", resqml2_2test::WellboreRegularFrameRepresentationTest)
FESAPI_TEST("Export and import seismic wellbore frame", "[well]", SeismicWellboreFrameRepresentationTest)
FESAPI_TEST("Export and import regular seismic wellbore frame", "[well]", SeismicWellboreRegularFrameRepresentationTest)
#endif

TEST_CASE("Export and import an empty EPC document", "[repo]")
{
	EpcDocumentTest testIn("../../EpcDocumentTest");
	testIn.serialize();

	// Check that the epc file extension has properly been added at previous step.

	EpcDocumentTest testOut("../../EpcDocumentTest.epc");
	testOut.deserialize();	
}

TEST_CASE("Test hdf5 opening mode", "[hdf]")
{
	std::remove("../../testingFile.h5");

	COMMON_NS::DataObjectRepository repo;
	COMMON_NS::AbstractHdfProxy* hdfProxy = repo.createHdfProxy("", "Hdf Proxy Test", "../../", "testingFile.h5", COMMON_NS::DataObjectRepository::openingMode::READ_ONLY);
	REQUIRE_THROWS(hdfProxy->open());
	hdfProxy->setOpeningMode(COMMON_NS::DataObjectRepository::openingMode::READ_WRITE_DO_NOT_CREATE);
	REQUIRE_THROWS(hdfProxy->open());
	hdfProxy->setOpeningMode(COMMON_NS::DataObjectRepository::openingMode::READ_WRITE);
	REQUIRE_NOTHROW(hdfProxy->open());
	hdfProxy->close();
	hdfProxy->setOpeningMode(COMMON_NS::DataObjectRepository::openingMode::OVERWRITE);
	REQUIRE_NOTHROW(hdfProxy->open());
	hdfProxy->close();
	hdfProxy->setOpeningMode(COMMON_NS::DataObjectRepository::openingMode::READ_WRITE_DO_NOT_CREATE);
	REQUIRE_NOTHROW(hdfProxy->open());
	hdfProxy->close();
	hdfProxy->setOpeningMode(COMMON_NS::DataObjectRepository::openingMode::READ_ONLY);
	REQUIRE_NOTHROW(hdfProxy->open());
	hdfProxy->close();
}

FESAPI_TEST("Export and import a local depth 3d crs", "[crs]", LocalDepth3dCrsTest)

FESAPI_TEST("Export and import an horizon interpretation", "[interpretation]", HorizonInterpretationTest)

FESAPI_TEST("Export and import a single patch triangulated set fault representation", "[representation]", FaultSinglePatchTriangulatedSetRepresentationTest)

FESAPI_TEST("Export and import a multi patch triangulated set fault representation", "[representation]", FaultMultiPatchTriangulatedSetRepresentationTest)

FESAPI_TEST("Export a multi domains interpreation", "[interpretation]", InterpretationDomain)

FESAPI_TEST("Export and import a generic creation activity template", "[activity]", ActivityTemplateGenericCreationTest)

FESAPI_TEST("Export and import an activity", "[activity]", ActivityCreationTest)

FESAPI_TEST("Export and import a compressed ijk grid", "[grid]", CompressedIjkGridExplicitRepresentationTest)

FESAPI_TEST("Export and import a 4*3*2 explicit right handed ijk grid", "[grid]", RightHanded4x3x2ExplicitIjkGrid)

TEST_CASE("Export and import a big explicit ijk grid", "[grid][property]")
{
	BigIjkGridExplicitRepresentationTest* test = new BigIjkGridExplicitRepresentationTest("../../BigIjkGridExplicitRepresentationTest.epc", 10, 10, 5, 9, 0., 100., 0., 100., 0., 50., 10);
	test->serialize();
	test->deserialize();
	delete test;
}

TEST_CASE("Export and import a big parametric ijk grid", "[grid][property]")
{
	BigIjkGridParametricRepresentationTest* test = new BigIjkGridParametricRepresentationTest("../../BigIjkGridParametricRepresentationTest.epc", 20, 20, 10, 10, 0., 100., 0., 100., 0., 50., 10);
	test->serialize();
	test->deserialize();
	delete test;
}

FESAPI_TEST("Export and import a LGR on a 4*3*2 explicit right handed ijk grid", "[grid]", LgrOnRightHanded4x3x2ExplicitIjkGrid)

FESAPI_TEST("Export and import an unstructured grid", "[grid]", OneTetrahedronUnstructuredGridRepresentationTest)

FESAPI_TEST("Export and import a subrepresentation on a partial grid connection set", "[grid]", SubRepresentationOnPartialGridConnectionSet)


// fail
//FESAPI_TEST("Export and import grid connection set on partial grid", "[property]", GridConnectionSetOnPartialGridSet)

FESAPI_TEST("Export and import a wellbore marker frame", "[well][stratigraphy]", WellboreMarkerFrameRepresentationTest)

FESAPI_TEST("Export and import a wellbore frame (regular md spacings)", "[well]", resqml2_0_1test::WellboreRegularFrameRepresentationTest)

FESAPI_TEST("Export and import a wellbore frame (irregular md spacings) with a single continuous property on node", "[well][property]", ContinuousPropertyOnWellFrameTest)
FESAPI_TEST("Export and import a wellbore frame (irregular md spacings) with a single comment property on node", "[well][property]", CommentProperty)

FESAPI_TEST("Export and import a wellbore frame (irregular md spacings) with a single discrete property on node using a local property kind", "[well][property]", DiscretePropertyUsingLocalKindOnWellFrameTest)

FESAPI_TEST("Export and import a seismic lattice feature", "[seismic]", SeismicLatticeRepresentationTest)
FESAPI_TEST("Export and import a seismic horizon grid 2d rep", "[seismic]", Grid2dRepresentationTest)
FESAPI_TEST("Export and import an horizon on a seismic line", "[seismic]", HorizonOnSeismicLine)

FESAPI_TEST("Export and import a WITSML well", "[well]", WellTest)
FESAPI_TEST("Export and import a WITSML trajectory", "[well]", Trajectory)
FESAPI_TEST("Export and import a WITSML perforation", "[well]", Perforation)
FESAPI_TEST("Export and import a WITSML Wellbore Geometry", "[well]", WellboreGeometryTest)

FESAPI_TEST("Export and import some multi realization properties", "[property]", MultirealPropertyTest)
FESAPI_TEST("Check discrete property datatypes", "[property]", DiscreteProperty)
FESAPI_TEST("Export and import properties using slab", "[property]", PropertyBySlab)
FESAPI_TEST("Export and import a time series", "[property]", TimeSeriesTest)
