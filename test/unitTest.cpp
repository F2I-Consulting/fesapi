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
#include "eml2/AbstractHdfProxy.h"

#include "EpcDocumentTest.h"
#include "DateTimeTest.h"
#include "resqml2_test/LocalDepth3dCrsTest.h"
#include "resqml2_test/HorizonInterpretationTest.h"
#include "resqml2_test/FaultSinglePatchTriangulatedSetRepresentationTest.h"
#include "resqml2_test/FaultMultiPatchTriangulatedSetRepresentationTest.h"
#include "resqml2_test/ActivityTemplateGenericCreationTest.h"
#include "resqml2_test/ActivityCreationTest.h"
#include "resqml2_test/OneTetrahedronUnstructuredGridRepresentationTest.h"
#include "resqml2_test/UnstructuredGridTest.h"
#include "resqml2_test/TimeSeriesTest.h"
#include "resqml2_test/CommentProperty.h"
#include "resqml2_test/ContinuousPropertyOnWellFrameTest.h"
#include "resqml2_test/GridConnectionSetOnPartialGridSet.h"
#include "resqml2_test/WellboreTrajectoryRepresentationTest.h"
#include "resqml2_test/WellboreMarkerFrameRepresentationTest.h"
#include "resqml2_test/WellboreFrameRepresentationTest.h"
#include "resqml2_test/WellboreRegularFrameRepresentationTest.h"
#include "resqml2_test/DiscretePropertyUsingLocalKindOnWellFrameTest.h"
#include "resqml2_test/SeismicLatticeRepresentationTest.h"
#include "resqml2_test/Grid2dRepresentationTest.h"
#include "resqml2_test/HorizonOnSeismicLine.h"
#include "resqml2_test/CompressedIjkGridExplicitRepresentationTest.h"
#include "resqml2_test/RightHanded4x3x2ExplicitIjkGrid.h"
#include "resqml2_test/FourSugarsParametricIjkGridWithGap.h"
#include "resqml2_test/BigIjkGridExplicitRepresentationTest.h"
#include "resqml2_test/BigIjkGridParametricRepresentationTest.h"
#include "resqml2_test/SubRepresentationOnPartialGridConnectionSet.h"
#include "resqml2_test/LgrOnRightHanded4x3x2ExplicitIjkGrid.h"
#include "resqml2_test/InterpretationDomain.h"
#include "resqml2_2test/DiscreteColorMapTest.h"
#include "resqml2_2test/ContinuousColorMapTest.h"
#include "resqml2_test/MultirealPropertyTest.h"
#include "resqml2_test/CategoricalProperty.h"
#include "resqml2_test/ContinuousProperty.h"
#include "resqml2_test/DiscreteProperty.h"
#include "resqml2_test/PointsProperty.h"
#include "resqml2_test/PropertyBySlab.h"
#include "resqml2_test/Streamlines.h"
#include "witsml2_test/WellTest.h"
#include "witsml2_test/Trajectory.h"
#include "witsml2_test/Perforation.h"
#include "witsml2_test/WellboreGeometryTest.h"
#if WITH_RESQML2_2
#include "eml2_3test/GraphicalInformationSetTest.h"
#include "resqml2_2test/DiscreteColorMapTest.h"
#include "resqml2_2test/ContinuousColorMapTest.h"
#include "resqml2_2test/WellboreFrameRepresentationTest.h"
#include "resqml2_2test/WellboreRegularFrameRepresentationTest.h"
#include "resqml2_2test/SeismicWellboreFrameRepresentationTest.h"
#include "resqml2_2test/SeismicWellboreRegularFrameRepresentationTest.h"
using namespace resqml2_2test;
#endif
using namespace commontest;
using namespace resqml2_test;
using namespace witsml2_test;

#define FESAPI_TEST2_2(name, tags, classTest)  TEST_CASE(#name " 2_2", tags)\
{\
	classTest test("../../" #classTest "2_2.epc");\
	test.defaultEmlVersion = COMMON_NS::DataObjectRepository::EnergisticsStandard::EML2_3;\
	test.defaultResqmlVersion = COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_2;\
	test.serialize();\
	test.deserialize();\
}

#define FESAPI_TEST2_0(name, tags, classTest)  TEST_CASE(#name " 2_0", tags)\
{\
	classTest test("../../" #classTest "2_0.epc");\
	test.defaultEmlVersion = COMMON_NS::DataObjectRepository::EnergisticsStandard::EML2_0;\
	test.defaultResqmlVersion = COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_0_1;\
	test.serialize();\
	test.deserialize();\
}

#if WITH_RESQML2_2
	#define FESAPI_TEST(name, tags, classTest)\
		FESAPI_TEST2_0(name, tags, classTest)\
		FESAPI_TEST2_2(name, tags, classTest)
#else
	#define FESAPI_TEST(name, tags, classTest)  FESAPI_TEST2_0(name, tags, classTest)
#endif

#if WITH_RESQML2_2
FESAPI_TEST2_2("Export and import graphical information set", "[graphical information]", GraphicalInformationSetTest)
FESAPI_TEST2_2("Export and import discrete color map on a discrete property", "[graphical information][color map][discrete color map]", DiscreteColorMapTest)
FESAPI_TEST2_2("Export and import continuous color map on a discrete property", "[graphical information][color map][continuous color map]", ContinuousColorMapTest)
FESAPI_TEST2_2("Export and import wellbore frame", "[well]", resqml2_2test::WellboreFrameRepresentationTest)
FESAPI_TEST2_2("Export and import regular wellbore frame", "[well]", resqml2_2test::WellboreRegularFrameRepresentationTest)
FESAPI_TEST2_2("Export and import seismic wellbore frame", "[well]", SeismicWellboreFrameRepresentationTest)
FESAPI_TEST2_2("Export and import regular seismic wellbore frame", "[well]", SeismicWellboreRegularFrameRepresentationTest)
#endif
TEST_CASE("Export and import an empty EPC document", "[epc]")
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
	EML2_NS::AbstractHdfProxy* hdfProxy = repo.createHdfProxy("", "Hdf Proxy Test", "../../", "testingFile.h5", COMMON_NS::DataObjectRepository::openingMode::READ_ONLY);
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

FESAPI_TEST("Export and import of date time", "[datetime]", DateTimeTest)

FESAPI_TEST("Export and import a local depth 3d crs", "[crs]", LocalDepth3dCrsTest)

// INTERPRETATION
FESAPI_TEST("Export and import an horizon interpretation", "[interpretation]", HorizonInterpretationTest)
FESAPI_TEST("Export a multi domains interpretation", "[interpretation]", InterpretationDomain)

// TRIANGULATION
FESAPI_TEST("Export and import a single patch triangulated set fault representation", "[representation]", FaultSinglePatchTriangulatedSetRepresentationTest)
FESAPI_TEST("Export and import a multi patch triangulated set fault representation", "[representation]", FaultMultiPatchTriangulatedSetRepresentationTest)

// ACTIVITY
FESAPI_TEST("Export and import a generic creation activity template", "[activity]", ActivityTemplateGenericCreationTest)
FESAPI_TEST("Export and import an activity", "[activity]", ActivityCreationTest)

// GRID
FESAPI_TEST("Export and import a compressed ijk grid", "[grid]", CompressedIjkGridExplicitRepresentationTest)

FESAPI_TEST("Export and import a 4*3*2 explicit right handed ijk grid", "[grid]", RightHanded4x3x2ExplicitIjkGrid)
FESAPI_TEST("Export and import a 2*1*2 parametric ijk grid with one gap layer", "[grid]", FourSugarsParametricIjkGridWithGap)

FESAPI_TEST("Export and import a LGR on a 4*3*2 explicit right handed ijk grid", "[grid]", LgrOnRightHanded4x3x2ExplicitIjkGrid)

FESAPI_TEST("Export and import a singel tetra grid", "[grid]", OneTetrahedronUnstructuredGridRepresentationTest)
FESAPI_TEST("Export and import an unstructured grid", "[grid]", UnstructuredGridTest)

FESAPI_TEST("Export and import a subrepresentation on a partial grid connection set", "[grid]", SubRepresentationOnPartialGridConnectionSet)

FESAPI_TEST("Export and import streamlines on a partial grid", "[grid]", Streamlines)

// fail
//FESAPI_TEST("Export and import grid connection set on partial grid", "[grid]", GridConnectionSetOnPartialGridSet)

TEST_CASE("Export and import a big explicit ijk grid", "[grid][property]")
{
	BigIjkGridExplicitRepresentationTest test("../../BigIjkGridExplicitRepresentationTest.epc", 10, 10, 5, 9, 0., 100., 0., 100., 0., 50., 10);
	test.serialize();
	test.deserialize();
}

TEST_CASE("Export and import a big parametric ijk grid", "[grid][property]")
{
	BigIjkGridParametricRepresentationTest test("../../BigIjkGridParametricRepresentationTest.epc", 20, 20, 10, 10, 0., 100., 0., 100., 0., 50., 10);
	test.serialize();
	test.deserialize();
}

// PROPERTY
FESAPI_TEST("Export and import continuous properties on a partial grid", "[property]", ContinuousProperty)


// RESQML WELL
FESAPI_TEST("Export and import a wellbore trajectory", "[well][trajectory]", WellboreTrajectoryRepresentationTest)
FESAPI_TEST("Export and import a wellbore marker frame", "[well][stratigraphy]", WellboreMarkerFrameRepresentationTest)
FESAPI_TEST("Export and import a wellbore frame (regular md spacings)", "[well]", resqml2_test::WellboreRegularFrameRepresentationTest)

FESAPI_TEST("Export and import a wellbore frame (irregular md spacings) with a single continuous property on node", "[well][property]", ContinuousPropertyOnWellFrameTest)
FESAPI_TEST("Export and import a wellbore frame (irregular md spacings) with a single comment property on node", "[well][property]", CommentProperty)
FESAPI_TEST("Export and import a wellbore frame (irregular md spacings) with a single discrete property on node using a local property kind", "[well][property]", DiscretePropertyUsingLocalKindOnWellFrameTest)
// WITSML WELL
FESAPI_TEST("Export and import a WITSML well", "[well]", WellTest)
FESAPI_TEST("Export and import a WITSML trajectory", "[well]", Trajectory)
FESAPI_TEST("Export and import a WITSML perforation", "[well]", Perforation)
FESAPI_TEST("Export and import a WITSML Wellbore Geometry", "[well]", WellboreGeometryTest)

// SEISMIC
FESAPI_TEST("Export and import a seismic lattice feature", "[seismic]", SeismicLatticeRepresentationTest)
FESAPI_TEST("Export and import a seismic horizon grid 2d rep", "[seismic]", Grid2dRepresentationTest)
FESAPI_TEST("Export and import an horizon on a seismic line", "[seismic]", HorizonOnSeismicLine)

FESAPI_TEST("Export and import some multi realization properties", "[property]", MultirealPropertyTest)
FESAPI_TEST("Check categorical property", "[property]", CategoricalProperty)
FESAPI_TEST("Check discrete property datatypes", "[property]", DiscreteProperty)
FESAPI_TEST("Check points property", "[property]", PointsProperty)
FESAPI_TEST("Export and import properties using slab", "[property]", PropertyBySlab)
FESAPI_TEST("Export and import a time series", "[property]", TimeSeriesTest)
