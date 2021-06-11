/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
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
// Acknowledgements: the serializeOrganizations function have been provided by Geosiris

#ifdef _WIN32
// ************************
// For memory leak
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
// ************************
#endif

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "version_config.h"

#include "proxies/stdsoap2.h"

#include "common/EpcDocument.h"
#include "common/EnumStringMapper.h"
#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "resqml2_0_1/LocalTime3dCrs.h"
#include "resqml2_0_1/FrontierFeature.h"
#include "resqml2_0_1/Horizon.h"
#include "resqml2_0_1/GeobodyFeature.h"
#include "resqml2_0_1/TectonicBoundaryFeature.h"
#include "resqml2_0_1/GenericFeatureInterpretation.h"
#include "resqml2_0_1/FluidBoundaryFeature.h"
#include "resqml2_0_1/HorizonInterpretation.h"
#include "resqml2_0_1/GeobodyInterpretation.h"
#include "resqml2_0_1/GeobodyBoundaryInterpretation.h"
#include "resqml2_0_1/FaultInterpretation.h"
#include "resqml2_0_1/TriangulatedSetRepresentation.h"
#include "resqml2_0_1/PolylineSetRepresentation.h"
#include "resqml2_0_1/PointSetRepresentation.h"
#include "resqml2_0_1/PlaneSetRepresentation.h"
#include "resqml2_0_1/OrganizationFeature.h"
#include "resqml2_0_1/EarthModelInterpretation.h"
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"
#include "resqml2_0_1/StratigraphicUnitInterpretation.h"
#include "resqml2_0_1/Grid2dRepresentation.h"
#include "resqml2_0_1/SeismicLatticeFeature.h"
#include "resqml2_0_1/SeismicLineSetFeature.h"
#include "resqml2_0_1/SeismicLineFeature.h"
#include "resqml2_0_1/WellboreFeature.h"
#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2_0_1/MdDatum.h"
#include "resqml2_0_1/PolylineRepresentation.h"
#include "resqml2_0_1/PropertyKind.h"
#include "resqml2_0_1/WellboreMarker.h"
#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"
#include "resqml2_0_1/PropertySet.h"
#include "resqml2_0_1/ContinuousProperty.h"
#include "resqml2_0_1/DiscreteProperty.h"
#include "resqml2_0_1/PointsProperty.h"
#include "resqml2_0_1/CategoricalProperty.h"
#include "resqml2/DoubleTableLookup.h"
#include "resqml2/StringTableLookup.h"
#include "resqml2/GridConnectionSetRepresentation.h"
#include "resqml2/IjkGridExplicitRepresentation.h"
#include "resqml2/IjkGridParametricRepresentation.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/SealedSurfaceFrameworkRepresentation.h"
#include "resqml2_0_1/SubRepresentation.h"
#include "resqml2_0_1/TimeSeries.h"
#include "resqml2_0_1/RockFluidOrganizationInterpretation.h"
#include "resqml2_0_1/RockFluidUnitInterpretation.h"
#include "resqml2_0_1/RockFluidUnitFeature.h"
#include "resqml2_0_1/PropertyKindMapper.h"

#include "resqml2_0_1/Activity.h"
#include "resqml2_0_1/ActivityTemplate.h"
#if WITH_RESQML2_2
#include "eml2_3/GraphicalInformationSet.h"
#include "resqml2_2/DiscreteColorMap.h"
#include "resqml2_2/ContinuousColorMap.h"
#include "resqml2_2/FluidBoundaryInterpretation.h"
#include "resqml2_2/MdDatum.h"
#include "resqml2_2/RockVolumeFeature.h"
#include "resqml2_2/SeismicWellboreFrameRepresentation.h"
#include "resqml2_2/ShotPointLineFeature.h"
#include "resqml2_2/WellboreMarker.h"
#include "resqml2_2/WellboreMarkerFrameRepresentation.h"
#endif
#include "resqml2/SealedVolumeFrameworkRepresentation.h"
#include "resqml2/StratigraphicColumn.h"
#include "resqml2/StratigraphicColumnRankInterpretation.h"
#include "resqml2/StratigraphicOccurrenceInterpretation.h"

#include "eml2/AbstractHdfProxy.h"
#include "eml2/PropertyKind.h"
#include "eml2/TimeSeries.h"

#include "witsml2_0/Well.h"
#include "witsml2_0/Wellbore.h"
#include "witsml2_0/Trajectory.h"
#include "witsml2_0/WellCompletion.h"
#include "witsml2_0/WellboreCompletion.h"
#include "witsml2_0/WellboreGeometry.h"
#include "witsml2_0/WellboreMarker.h"
#include "witsml2_0/Log.h"
#include "witsml2_0/ChannelSet.h"
#include "witsml2_0/Channel.h"

#include "prodml2_1/FluidSystem.h"
#include "prodml2_1/FluidCharacterization.h"
#include "prodml2_1/FrictionTheorySpecification.h"
#include "prodml2_1/TimeSeriesData.h"

#include "HdfProxyFactoryExample.h"

using namespace std;

RESQML2_NS::BoundaryFeature* horizon1 = nullptr;
RESQML2_NS::BoundaryFeature* horizon2 = nullptr;
RESQML2_NS::BoundaryFeature* fault1 = nullptr;
RESQML2_NS::HorizonInterpretation* horizon1Interp1 = nullptr;
RESQML2_NS::HorizonInterpretation* horizon2Interp1 = nullptr;
RESQML2_NS::FaultInterpretation* fault1Interp1 = nullptr;
RESQML2_NS::Grid2dRepresentation* h1i1SingleGrid2dRep = nullptr;
RESQML2_NS::PolylineSetRepresentation* f1i1PolyLineRep = nullptr;
RESQML2_NS::TriangulatedSetRepresentation* f1i1triRepSinglePatch = nullptr;
RESQML2_NS::TriangulatedSetRepresentation* f1i1triRep = nullptr;
RESQML2_NS::TriangulatedSetRepresentation* h1i1triRep = nullptr;
RESQML2_NS::TriangulatedSetRepresentation* h2i1triRep = nullptr;
RESQML2_NS::TriangulatedSetRepresentation* xMinusFrontierRep = nullptr;
RESQML2_NS::TriangulatedSetRepresentation* xPlusFrontierRep = nullptr;
RESQML2_NS::TriangulatedSetRepresentation* yMinusFrontierRep = nullptr;
RESQML2_NS::TriangulatedSetRepresentation* yPlusFrontierRep = nullptr;
RESQML2_NS::WellboreTrajectoryRepresentation* w1i1TrajRep = nullptr;
RESQML2_NS::LocalDepth3dCrs* local3dCrs = nullptr;
RESQML2_NS::LocalTime3dCrs* localTime3dCrs = nullptr;
RESQML2_NS::WellboreFeature* wellbore1 = nullptr;
RESQML2_NS::WellboreInterpretation* wellbore1Interp1 = nullptr;
RESQML2_NS::StratigraphicColumnRankInterpretation* stratiColumnRank0 = nullptr;
RESQML2_NS::SealedSurfaceFrameworkRepresentation* sealedSurfaceFramework = nullptr;
RESQML2_NS::IjkGridExplicitRepresentation* ijkgrid = nullptr;
EML2_NS::PropertyKind* propType1 = nullptr;
RESQML2_NS::DiscreteProperty* discreteProp1 = nullptr;
RESQML2_NS::ContinuousProperty* contColMapContProp = nullptr;
RESQML2_NS::RockFluidOrganizationInterpretation* rockFluidOrgInterp = nullptr;
RESQML2_NS::RockFluidUnitInterpretation* gasCapInterp = nullptr;
RESQML2_NS::RockFluidUnitInterpretation* oilColumnInterp = nullptr;
RESQML2_NS::RockFluidUnitInterpretation* aquiferInterp = nullptr;

WITSML2_NS::Well* witsmlWell = nullptr;
WITSML2_NS::Wellbore* witsmlWellbore = nullptr;
WITSML2_0_NS::WellboreMarker* witsmlWellboreMarker = nullptr;

void serializeWitsmlWells(COMMON_NS::DataObjectRepository * pck)
{
	// WELL
	witsmlWell = pck->createWell("704a287c-5c24-4af3-a97b-bc6670f4e14f", "Well1");
	witsmlWell->setNameLegal("Legal Name");
	witsmlWell->pushBackLocation("8cd3c8b2-face-4426-8aea-ae34870bd969", 275, 75, 23031);
	witsmlWell->pushBackDatum("aa92fa8b-d6cc-459e-b456-27fec0c08b24", "well1 msl datum", gsoap_eml2_1::eml21__WellboreDatumReference::kelly_x0020bushing, "Mean Sea Level", gsoap_eml2_1::eml21__LengthUom::m, 0, 5100);
	witsmlWell->pushBackDatum("d3ac5401-d3e7-4474-b846-070673b210ae", "KB", gsoap_eml2_1::eml21__WellboreDatumReference::kelly_x0020bushing, "Mean Sea Level", gsoap_eml2_1::eml21__LengthUom::m, 15, 5100);

	// WELLBORE
	witsmlWellbore = pck->createWellbore(witsmlWell, "3bd60188-5688-43df-89bb-935fe86a813f", "Wellbore1");
	witsmlWellbore->setNumber("Wb1");
	witsmlWellbore->setStatusWellbore(gsoap_eml2_1::eml21__WellStatus::completed);
	witsmlWellbore->setIsActive(false);
	witsmlWellbore->setTypeWellbore(gsoap_eml2_1::witsml20__WellboreType::initial);
	witsmlWellbore->setShape(gsoap_eml2_1::witsml20__WellboreShape::vertical);
	witsmlWellbore->setAchievedTD(true);
	witsmlWellbore->setMd(1000, gsoap_eml2_1::eml21__LengthUom::m, "d3ac5401-d3e7-4474-b846-070673b210ae");
	witsmlWellbore->setMdPlanned(1000, gsoap_eml2_1::eml21__LengthUom::m, "d3ac5401-d3e7-4474-b846-070673b210ae");

	// TRAJECTORY
	WITSML2_NS::Trajectory* witsmlTrajectory = pck->createTrajectory(
		witsmlWellbore, "4e76e1de-eff1-4458-805e-a6a877fa333b", "My trajectory", gsoap_eml2_1::witsml20__ChannelStatus::closed);
	witsmlTrajectory->setMdMn(.0, gsoap_eml2_1::eml21__LengthUom::m, "d3ac5401-d3e7-4474-b846-070673b210ae");
	witsmlTrajectory->setMdMx(1000., gsoap_eml2_1::eml21__LengthUom::m, "d3ac5401-d3e7-4474-b846-070673b210ae");
	witsmlTrajectory->setDefinitive(true);
	witsmlTrajectory->setFinalTraj(true);
	witsmlTrajectory->setServiceCompany("F2I-CONSULTING");

	witsmlTrajectory->pushBackTrajectoryStation(gsoap_eml2_1::witsml20__TrajStationType::N_x0020E_x0020and_x0020TVD, 0, gsoap_eml2_1::eml21__LengthUom::m, "d3ac5401-d3e7-4474-b846-070673b210ae");
	witsmlTrajectory->setTrajectoryStationManuallyEntered(0, true);
	witsmlTrajectory->setTrajectoryStationDispNs(0, .0, gsoap_eml2_1::eml21__LengthUom::m);
	witsmlTrajectory->setTrajectoryStationDispEw(0, .0, gsoap_eml2_1::eml21__LengthUom::m);
	witsmlTrajectory->setTrajectoryStationTvd(0, .0, gsoap_eml2_1::eml21__LengthUom::m, "d3ac5401-d3e7-4474-b846-070673b210ae");
	witsmlTrajectory->pushBackTrajectoryStation(gsoap_eml2_1::witsml20__TrajStationType::N_x0020E_x0020and_x0020TVD, 325, gsoap_eml2_1::eml21__LengthUom::m, "d3ac5401-d3e7-4474-b846-070673b210ae");
	witsmlTrajectory->setTrajectoryStationManuallyEntered(1, true);
	witsmlTrajectory->setTrajectoryStationDispNs(1, 325, gsoap_eml2_1::eml21__LengthUom::m);
	witsmlTrajectory->setTrajectoryStationDispEw(1, 325, gsoap_eml2_1::eml21__LengthUom::m);
	witsmlTrajectory->setTrajectoryStationTvd(1, 325, gsoap_eml2_1::eml21__LengthUom::m, "d3ac5401-d3e7-4474-b846-070673b210ae");
	witsmlTrajectory->pushBackTrajectoryStation(gsoap_eml2_1::witsml20__TrajStationType::N_x0020E_x0020and_x0020TVD, 500, gsoap_eml2_1::eml21__LengthUom::m, "d3ac5401-d3e7-4474-b846-070673b210ae");
	witsmlTrajectory->setTrajectoryStationManuallyEntered(2, true);
	witsmlTrajectory->setTrajectoryStationDispNs(2, 500, gsoap_eml2_1::eml21__LengthUom::m);
	witsmlTrajectory->setTrajectoryStationDispEw(2, 500, gsoap_eml2_1::eml21__LengthUom::m);
	witsmlTrajectory->setTrajectoryStationTvd(2, 500, gsoap_eml2_1::eml21__LengthUom::m, "d3ac5401-d3e7-4474-b846-070673b210ae");
	witsmlTrajectory->pushBackTrajectoryStation(gsoap_eml2_1::witsml20__TrajStationType::N_x0020E_x0020and_x0020TVD, 1000, gsoap_eml2_1::eml21__LengthUom::m, "d3ac5401-d3e7-4474-b846-070673b210ae");
	witsmlTrajectory->setTrajectoryStationManuallyEntered(3, true);
	witsmlTrajectory->setTrajectoryStationDispNs(3, 1000, gsoap_eml2_1::eml21__LengthUom::m);
	witsmlTrajectory->setTrajectoryStationDispEw(3, 1000, gsoap_eml2_1::eml21__LengthUom::m);
	witsmlTrajectory->setTrajectoryStationTvd(3, 1000, gsoap_eml2_1::eml21__LengthUom::m, "d3ac5401-d3e7-4474-b846-070673b210ae");

	// Geometry
	WITSML2_0_NS::WellboreGeometry* witsmlWbGeom = pck->createWellboreGeometry(witsmlWellbore, "c9dc03e9-722c-478b-b0ae-b2dd9da67c11", "My wellbore geometry", gsoap_eml2_1::witsml20__ChannelStatus::closed);
	witsmlWbGeom->setMdBase(0, gsoap_eml2_1::eml21__LengthUom::m, "d3ac5401-d3e7-4474-b846-070673b210ae");
	witsmlWbGeom->pushBackSection();
	witsmlWbGeom->setWellboreGeometrySectionTypeHoleCasing(0, gsoap_eml2_1::witsml20__HoleCasingType::casing);
	witsmlWbGeom->setWellboreGeometrySectionOdSection(0, 30, gsoap_eml2_1::eml21__LengthUom::in);
	witsmlWbGeom->setWellboreGeometrySectionMdInterval(0, 0, 250, "d3ac5401-d3e7-4474-b846-070673b210ae", gsoap_eml2_1::eml21__LengthUom::m);
	witsmlWbGeom->setWellboreGeometrySectionTvdInterval(0, 0, 250, "d3ac5401-d3e7-4474-b846-070673b210ae", gsoap_eml2_1::eml21__LengthUom::m);
	witsmlWbGeom->pushBackSection();
	witsmlWbGeom->setWellboreGeometrySectionTypeHoleCasing(1, gsoap_eml2_1::witsml20__HoleCasingType::casing);
	witsmlWbGeom->setWellboreGeometrySectionCurveConductor(1, false);
	witsmlWbGeom->setWellboreGeometrySectionDiaDrift(1, 17.5, gsoap_eml2_1::eml21__LengthUom::in);
	witsmlWbGeom->setWellboreGeometrySectionFactFric(1, 0.25);
	witsmlWbGeom->setWellboreGeometrySectionGrade(1, "L80");
	witsmlWbGeom->setWellboreGeometrySectionIdSection(1, 18, gsoap_eml2_1::eml21__LengthUom::in);
	witsmlWbGeom->setWellboreGeometrySectionOdSection(1, 20, gsoap_eml2_1::eml21__LengthUom::in);
	witsmlWbGeom->setWellboreGeometrySectionWtPerLen(1, 123, gsoap_eml2_1::eml21__MassPerLengthUom::lbm_x002fft);
	witsmlWbGeom->setWellboreGeometrySectionTvdInterval(1, 0, 990, "d3ac5401-d3e7-4474-b846-070673b210ae", gsoap_eml2_1::eml21__LengthUom::m);

	// Log
	//EML2_NS::PropertyKind* channelPk = pck->createPartial<WITSML2_0_NS::PropertyKind>("eac77e0f-d13a-4821-9a48-0c4b229ae06e", "My channel prop kind");
	EML2_NS::PropertyKind* channelPk = pck->createPropertyKind("eac77e0f-d13a-4821-9a48-0c4b229ae06e", "My channel prop kind", gsoap_eml2_1::eml21__QuantityClassKind::thermodynamic_x0020temperature);
	WITSML2_0_NS::Channel* channel = pck->createChannel(channelPk, "c3ff6f85-f111-4603-840a-ae8bdc46e0c8", "My channel",
		"my mnemo", gsoap_eml2_1::eml21__UnitOfMeasure::K, gsoap_eml2_1::witsml20__EtpDataType::double_, gsoap_eml2_1::witsml20__ChannelStatus::closed, "Depth", "F2I-CONSULTING");
	channel->pushBackChannelIndex(gsoap_eml2_1::witsml20__ChannelIndexType::measured_x0020depth, gsoap_eml2_1::eml21__UnitOfMeasure::m, "MD");
	WITSML2_0_NS::ChannelSet* channelSet = pck->createChannelSet("00e8ffda-bb07-46db-8c22-8947282d7535", "My channel set");
	channelSet->pushBackChannelIndex(gsoap_eml2_1::witsml20__ChannelIndexType::measured_x0020depth, gsoap_eml2_1::eml21__UnitOfMeasure::m, "MD");
	channelSet->pushBackChannel(channel);
	channelSet->setDataAsJsonArray("[\n\
		[[0],[300]],\n\
		[[500],[305]],\n\
		[[1000],[310]]\n\
		]");
	WITSML2_0_NS::Log* witsmlLog = pck->createLog(witsmlWellbore, "24093183-5a06-4bea-8c69-3e9769971014", "My log");
	witsmlLog->pushBackChannelSet(channelSet);
	witsmlLog->setTimeDepth("Depth");
	witsmlLog->setLoggingCompanyName("F2I-CONSULTING");
	witsmlLog->setLoggingCompanyCode("F2I");

	// Marker
	witsmlWellboreMarker = pck->createWellboreMarker(witsmlWellbore, "08b18514-e0c8-4667-850b-4ddd1cb785b5", "WITSML marker", 350, gsoap_eml2_1::eml21__LengthUom::m, "36e91de5-7833-4b6d-90d0-1d643c0adece");
	witsmlWellboreMarker->setDipAngle(5, gsoap_eml2_1::eml21__PlaneAngleUom::dega);
	witsmlWellboreMarker->setDipDirection(10, gsoap_eml2_1::eml21__PlaneAngleUom::dega);
}

void serializeWells(COMMON_NS::DataObjectRepository * pck, EML2_NS::AbstractHdfProxy* hdfProxy)
{
	serializeWitsmlWells(pck);

	// Features
	wellbore1 = pck->createWellboreFeature("22d5b48f-f789-46e7-a454-6d8bd05afd0b", "Wellbore1");
	if (dynamic_cast<WITSML2_0_NS::Wellbore*>(witsmlWellbore) != nullptr) {
		wellbore1->setWitsmlWellbore(static_cast<WITSML2_0_NS::Wellbore*>(witsmlWellbore));
	}

	// Interpretations
	wellbore1Interp1 = pck->createWellboreInterpretation(wellbore1, "dc7840fe-e5a3-4b53-a1df-18040bc4d0c0", "Wellbore1 Interp1", false);

	// Representation
	RESQML2_NS::MdDatum* mdInfo = pck->createMdDatum("36e91de5-7833-4b6d-90d0-1d643c0adece", "md Info", local3dCrs, gsoap_eml2_3::eml23__WellboreDatumReference::mean_x0020sea_x0020level, 275, 75, 0);

	//Geometry	
	w1i1TrajRep = pck->createWellboreTrajectoryRepresentation(wellbore1Interp1, "acd2cdcf-bb5d-48da-bd0e-9aeff3e52180", "Wellbore1 Interp1 TrajRep", mdInfo);
	double controlPoints[12] = { 275, 75, 0, 275, 75, 325, 275, 75, 500, 275, 75, 1000 };
	double trajectoryTangentVectors[12] = { 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 };
	double trajectoryMds[4] = { 0, 325, 500, 1000 };
	w1i1TrajRep->setGeometry(controlPoints, trajectoryTangentVectors, trajectoryMds, 4, 0, hdfProxy);

	// WellboreFeature frame
	RESQML2_NS::WellboreFrameRepresentation* w1i1FrameRep = pck->createWellboreFrameRepresentation(wellbore1Interp1, "d873e243-d893-41ab-9a3e-d20b851c099f", "Wellbore1 Interp1 FrameRep", w1i1TrajRep);
	double logMds[5] = { 0, 250, 500, 750, 1000 };
	w1i1FrameRep->setMdValues(logMds, 5, hdfProxy);

	RESQML2_NS::WellboreFrameRepresentation* w1i1RegularFrameRep = pck->createWellboreFrameRepresentation(wellbore1Interp1, "a54b8399-d3ba-4d4b-b215-8d4f8f537e66", "Wellbore1 Interp1 Regular FrameRep", w1i1TrajRep);
	w1i1RegularFrameRep->setMdValues(0, 200, 6);

	EML2_NS::PropertyKind* unitNumberPropType = nullptr;
	if (pck->getDefaultResqmlVersion() == COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_0_1) {
		unitNumberPropType = pck->createPropertyKind("358aac23-b377-4349-9e72-bff99a6edf34", "Unit number", "F2I", gsoap_resqml2_0_1::resqml20__ResqmlUom::Euc, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::discrete);
	}
#if WITH_RESQML2_2
	else {
		unitNumberPropType = pck->createPropertyKind("358aac23-b377-4349-9e72-bff99a6edf34", "Unit number", gsoap_eml2_1::eml21__QuantityClassKind::not_x0020a_x0020measure);
	}
#endif

	RESQML2_NS::DiscreteProperty* discreteProp = pck->createDiscreteProperty(w1i1FrameRep, "61c2917c-2334-4205-824e-d4f4a0cf6d8e", "Wellbore1 Interp1 FrameRep IntervalIndex", 1,
		gsoap_eml2_3::resqml22__IndexableElement::intervals, unitNumberPropType);
	char unitNumbers[5] = { 0, 1, 2, 3, 4 };
	discreteProp->pushBackCharHdf5Array1dOfValues(unitNumbers, 5, hdfProxy, -1);
#if WITH_RESQML2_2
	// SeismicWellboreFrameRepresentation
	RESQML2_NS::SeismicWellboreFrameRepresentation* w1i1SeismicFrameRep = pck->createSeismicWellboreFrameRepresentation(
		wellbore1Interp1, "dcbeea2e-8327-4c5b-97e3-bdced0680de5", "Wellbore1 Interp1 SeismicFrameRep",
		w1i1TrajRep,
		0.,
		0.,
		localTime3dCrs);
	w1i1SeismicFrameRep->setMdValues(logMds, 5, hdfProxy);
	double logTimes[5] = { 0., 10., 20., 25., 30. };
	w1i1SeismicFrameRep->setTimeValues(logTimes, 5, hdfProxy);

	RESQML2_NS::SeismicWellboreFrameRepresentation* w1i1RegularSeismicFrameRep = pck->createSeismicWellboreFrameRepresentation(
		wellbore1Interp1, "7f1b75ff-1226-4c0a-a531-8f71661da419", "Wellbore1 Interp1 Regular SeismicFrameRep",
		w1i1TrajRep,
		0.,
		0.,
		localTime3dCrs);
	w1i1RegularSeismicFrameRep->setMdValues(0, 200, 6);
	w1i1RegularSeismicFrameRep->setTimeValues(0., 10., 6);
#endif
}

void serializePerforations(COMMON_NS::DataObjectRepository * pck)
{
	if (witsmlWell == nullptr) {
		std::cout << "No WITSML export have been operated" << endl;
		return;
	}

	// WELL COMPLETION
	WITSML2_0_NS::WellCompletion* wellCompletion = pck->createWellCompletion(witsmlWell, "6593d580-2f44-4b18-97ce-8a9cf42a0414", "WellCompletion1");
	// WELLBORE COMPLETION
	WITSML2_0_NS::WellboreCompletion* wellboreCompletion = pck->createWellboreCompletion(witsmlWellbore, wellCompletion, "7bda8ecf-2037-4dc7-8c59-db6ca09f2008", "WellboreCompletion1", "wellCompletionName");

	wellboreCompletion->pushBackPerforation("Mean Sea Level", gsoap_eml2_1::eml21__LengthUom::m, 1970, 1980, "myId");
	wellboreCompletion->pushBackPerforation("Mean Sea Level", gsoap_eml2_1::eml21__LengthUom::m, 1990, 2000);
	wellboreCompletion->pushBackPerforationHistory(0);
	wellboreCompletion->setPerforationHistoryStatus(0, 0, gsoap_eml2_1::witsml20__PerforationStatus::open);
	wellboreCompletion->setPerforationHistoryTopMd(0, 0, "Mean Sea Level", gsoap_eml2_1::eml21__LengthUom::m, 1970);
	wellboreCompletion->setPerforationHistoryBaseMd(0, 0, "Mean Sea Level", gsoap_eml2_1::eml21__LengthUom::m, 1980);
	wellboreCompletion->setPerforationHistoryStartDate(0, 0, 407568645);
	wellboreCompletion->setPerforationHistoryEndDate(0, 0, 1514764800);
	wellboreCompletion->pushBackPerforationHistory(0);
	wellboreCompletion->setPerforationHistoryStatus(1, 0, gsoap_eml2_1::witsml20__PerforationStatus::squeezed);
	wellboreCompletion->setPerforationHistoryTopMd(1, 0, "Mean Sea Level", gsoap_eml2_1::eml21__LengthUom::m, 1970);
	wellboreCompletion->setPerforationHistoryBaseMd(1, 0, "Mean Sea Level", gsoap_eml2_1::eml21__LengthUom::m, 1980);
	wellboreCompletion->setPerforationHistoryStartDate(1, 0, 1514764800);
	wellboreCompletion->pushBackPerforationHistory(1);
	wellboreCompletion->setPerforationHistoryStatus(0, 1, gsoap_eml2_1::witsml20__PerforationStatus::open);
	wellboreCompletion->setPerforationHistoryStartDate(0, 1, 410104800);
	wellboreCompletion->pushBackPerforationHistory(1);
	wellboreCompletion->setPerforationHistoryStatus(1, 1, gsoap_eml2_1::witsml20__PerforationStatus::squeezed);
	wellboreCompletion->setPerforationHistoryStartDate(1, 1, 1514764800);
}
#if WITH_RESQML2_2
void serializeGraphicalInformationSet(COMMON_NS::DataObjectRepository * repo, EML2_NS::AbstractHdfProxy * hdfProxy)
{
	EML2_NS::GraphicalInformationSet* graphicalInformationSet = repo->createGraphicalInformationSet("be17c053-9189-4bc0-9db1-75aa51a026cd", "Graphical Information Set");

	// *************
	// Default color
	// *************

	// fault1 representation is blue
	graphicalInformationSet->setDefaultHsvColor(fault1, 240., 1., 1., 1., "blue");
	graphicalInformationSet->setDefaultHsvColor(fault1Interp1, 240., 1., 1., 1., "blue");
	graphicalInformationSet->setDefaultHsvColor(f1i1triRepSinglePatch, 240., 1., 1., 1., "blue");
	graphicalInformationSet->setDefaultHsvColor(f1i1triRep, 240., 1., 1., 1., "blue");
	graphicalInformationSet->setDefaultHsvColor(f1i1PolyLineRep, 240., 1., 1., 1., "blue");

	// horizon1 representation is red
	graphicalInformationSet->setDefaultHsvColor(horizon1, 0., 1., 1., 1., "red");
	graphicalInformationSet->setDefaultHsvColor(horizon1Interp1, 0., 1., 1., 1., "red");
	graphicalInformationSet->setDefaultHsvColor(h1i1triRep, 0., 1., 1., 1., "red");

	// horizon2 representation is green
	graphicalInformationSet->setDefaultHsvColor(horizon2, 120., 1., 1., 1., "green");
	graphicalInformationSet->setDefaultHsvColor(horizon2Interp1, 120., 1., 1., 1., "green");
	graphicalInformationSet->setDefaultHsvColor(h2i1triRep, 120., 1., 1., 1., "green");
	graphicalInformationSet->setDefaultHsvColor(h1i1SingleGrid2dRep, 120., 1., 1., 1., "green");

	// ******************
	// Discrete color map
	// ******************

	// associating a discrete color map to property kind propType1
	RESQML2_NS::DiscreteColorMap* propKindDiscrColMap = repo->createDiscreteColorMap("d808d79c-2cad-4c4f-9712-3b3ab4aa3f4a", "Property kind discrete color map");
	unsigned int propKindDiscrColMapRgbColors[9] = { 0, 0, 255, 255, 255, 255, 255, 0, 0 };
	double propKindDiscrColMapAlphas[3] = { 1., 1., 1. };
	vector<string> propKindDiscrColMapTitles = { "blue", "white", "red" };
	propKindDiscrColMap->setRgbColors(3, propKindDiscrColMapRgbColors, propKindDiscrColMapAlphas, propKindDiscrColMapTitles);
	graphicalInformationSet->setDiscreteColorMap(propType1, propKindDiscrColMap);

	// associating a discrete color map to dicreteProp1
	RESQML2_NS::DiscreteColorMap* discrColMap = repo->createDiscreteColorMap("3daf4661-ae8f-4357-adee-0b0159bdd0a9", "Discrete color map");
	unsigned int discrColMapRgbColors[18] = { 255, 0, 0, 0, 255, 0, 0, 0, 255, 169, 84, 27, 0, 0, 0, 255, 255, 255 };
	double discrColMapAlphas[6] = { 1., 1., 1., 1., 1., 1. };
	vector<string> discrColMapTitles = { "red", "green", "blue", "orange", "black", "white" };
	discrColMap->setRgbColors(6, discrColMapRgbColors, discrColMapAlphas, discrColMapTitles);
	graphicalInformationSet->setDiscreteColorMap(discreteProp1, discrColMap);

	// creating a new discrete property of type propType1 without associating it to a discrete color map.
	// Thus, its associated discrete color map remains the one associated to propType1
	RESQML2_NS::DiscreteProperty* discreteProp2 = repo->createDiscreteProperty(ijkgrid, "1e2822ef-b6cb-4123-bdf4-c99df84a896f", "Another two faulted sugar cubes cellIndex", 1,
		gsoap_eml2_3::resqml22__IndexableElement::cells, propType1);
	unsigned short prop2Values[2] = { 0, 1 };
	discreteProp2->pushBackUShortHdf5Array3dOfValues(prop2Values, 2, 1, 1, hdfProxy, -1);

	// ********************
	// Continuous color map
	// ********************

	RESQML2_NS::BoundaryFeature* contColMapHrz = repo->createHorizon("b9ec6ec9-2766-4af7-889e-5565b5fa5022", "Horizon for continuous color map");
	RESQML2_NS::HorizonInterpretation* contColMapHrzInterp = repo->createHorizonInterpretation(contColMapHrz, "34b69c81-6cfa-4531-be5b-f6bd9b74802f", "Horizon interpretation for continuous color map");
	RESQML2_NS::Grid2dRepresentation* contColMapGrid2dRep = repo->createGrid2dRepresentation(contColMapHrzInterp, "4e56b0e4-2cd1-4efa-97dd-95f72bcf9f80", "100x10 grid 2d for continuous color map");
	const unsigned int numPointInFastestDirection = 50;
	const unsigned int numPointsInSlowestDirection = 100;
	contColMapGrid2dRep->setGeometryAsArray2dOfLatticePoints3d(numPointInFastestDirection, numPointsInSlowestDirection,
		0., 0., 0.,
		1., 0., 0.,
		0., 1., 0.,
		1., 1.);

	auto standardOrientationPropKind = repo->createPropertyKind("b8e9afa0-7930-483b-931f-e5cf2008d03b", "orientation", gsoap_eml2_1::eml21__QuantityClassKind::plane_x0020angle);
	contColMapContProp = repo->createContinuousProperty(contColMapGrid2dRep, "c2be50b6-08d2-461b-81a4-73dbb04ba605", "Continuous property for continuous color map", 2,
		gsoap_eml2_3::resqml22__IndexableElement::nodes, "continuousColorMapIndex", standardOrientationPropKind);
	std::unique_ptr<double[]> values(new double[numPointInFastestDirection * numPointsInSlowestDirection]);
	for (size_t slowestIndex = 0; slowestIndex < numPointsInSlowestDirection; ++slowestIndex) {
		for (size_t fastestIndex = 0; fastestIndex < numPointInFastestDirection; ++fastestIndex) {
			values[fastestIndex + slowestIndex * numPointInFastestDirection] = fastestIndex * (1. / (numPointInFastestDirection - 1));
		}
	}
	contColMapContProp->pushBackDoubleHdf5Array2dOfValues(values.get(), numPointInFastestDirection, numPointsInSlowestDirection, hdfProxy);

	RESQML2_NS::ContinuousColorMap* contColMap = repo->createContinuousColorMap("a207faa2-963e-48d6-b3ad-53f6c1fc4dd4", "Continuous color map", gsoap_eml2_3::resqml22__InterpolationDomain::rgb, gsoap_eml2_3::resqml22__InterpolationMethod::linear);
	unsigned int contColMapRgbColors[6] = { 0, 255, 0, 255, 0, 0 };
	vector<string> contColMapColTitles = { "green", "red" };
	double contColMapAlphas[2] = { 1., 1. };
	contColMap->setRgbColors(2, contColMapRgbColors, contColMapAlphas, contColMapColTitles);
	graphicalInformationSet->setContinuousColorMap(contColMapContProp, contColMap);
	graphicalInformationSet->setColorMapMinMax(contColMapContProp, 0., 1.);
	graphicalInformationSet->setValueVectorIndex(contColMapContProp, 1);
}
#endif
void serializeStratigraphicModel(COMMON_NS::DataObjectRepository * pck, EML2_NS::AbstractHdfProxy* hdfProxy)
{
	// Build the Stratigraphic column
	RESQML2_NS::StratigraphicColumn* stratiColumn = pck->createStratigraphicColumn("7f6666a0-fa3b-11e5-a509-0002a5d5c51b", "Stratigraphic column");
	RESQML2_NS::Model* stratiModelFeature = pck->createStratigraphicModel("7fcde2b5-d184-4481-b31e-32aafbdc4b7f", "stratiModel");
	pck->createStratigraphicOccurrenceInterpretationInApparentDepth(stratiModelFeature, "2426e574-1ea3-4f20-9deb-669c15a17625", "stratiModel Interp");
	stratiColumnRank0 = pck->createStratigraphicColumnRankInterpretationInApparentDepth(stratiModelFeature, "ba06f220-fa3b-11e5-928c-0002a5d5c51b", "Stratigraphic column rank 0", 0);
	RESQML2_NS::StratigraphicColumnRankInterpretation* stratiColumnRank1 = pck->createStratigraphicColumnRankInterpretationInApparentDepth(stratiModelFeature, "9d2d19cf-aedb-4766-9691-758d536456ba", "Stratigraphic column rank 1", 1);
	stratiColumn->pushBackStratiColumnRank(stratiColumnRank0);
	stratiColumn->pushBackStratiColumnRank(stratiColumnRank1);
	RESQML2_NS::RockVolumeFeature* stratiUnitAFeature = nullptr;
	RESQML2_NS::RockVolumeFeature* stratiUnitBFeature = nullptr;
	RESQML2_NS::RockVolumeFeature* stratiUnitB1Feature = nullptr;
	RESQML2_NS::RockVolumeFeature* stratiUnitB2Feature = nullptr;
	if (pck->getDefaultResqmlVersion() == COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_0_1) {
		stratiUnitAFeature = pck->createStratigraphicUnitFeature("0426c6a0-fa3c-11e5-8b9c-0002a5d5c51b", "Unit A");
		stratiUnitBFeature = pck->createStratigraphicUnitFeature("273a92c0-fa3c-11e5-85f8-0002a5d5c51b", "Unit B");
		stratiUnitB1Feature = pck->createStratigraphicUnitFeature("0b7cc266-4280-4696-b9dc-5d17017797e2", "Unit B1");
		stratiUnitB2Feature = pck->createStratigraphicUnitFeature("87255cf5-033f-4fa4-941b-7947b434f4c2", "Unit B2");

	}
#if WITH_RESQML2_2
	else {
		stratiUnitAFeature = pck->createRockVolumeFeature("0426c6a0-fa3c-11e5-8b9c-0002a5d5c51b", "Unit A");
		stratiUnitBFeature = pck->createRockVolumeFeature("273a92c0-fa3c-11e5-85f8-0002a5d5c51b", "Unit B");
		stratiUnitB1Feature = pck->createRockVolumeFeature("0b7cc266-4280-4696-b9dc-5d17017797e2", "Unit B1");
		stratiUnitB2Feature = pck->createRockVolumeFeature("87255cf5-033f-4fa4-941b-7947b434f4c2", "Unit B2");
	}
#endif
	RESQML2_NS::StratigraphicUnitInterpretation* stratiUnitAInterp = pck->createStratigraphicUnitInterpretation(stratiUnitAFeature, "1a919b40-fa3c-11e5-a72c-0002a5d5c51b", "Unit A interp");
	RESQML2_NS::StratigraphicUnitInterpretation* stratiUnitBInterp = pck->createStratigraphicUnitInterpretation(stratiUnitBFeature, "2b9169c0-fa3c-11e5-ae2c-0002a5d5c51b", "Unit B interp");
	RESQML2_NS::StratigraphicUnitInterpretation* stratiUnitB1Interp = pck->createStratigraphicUnitInterpretation(stratiUnitB1Feature, "7d7ab0bc-554d-48f5-ab5c-3bb7b66696e5", "Unit B1 interp");
	RESQML2_NS::StratigraphicUnitInterpretation* stratiUnitB2Interp = pck->createStratigraphicUnitInterpretation(stratiUnitB2Feature, "34c37be0-964f-41a8-ba78-db5147744927", "Unit B2 interp");

	// Build a minimal Stratigraphic column to allow the definition of a minimal sealed volume framework
	RESQML2_NS::StratigraphicColumn* minimalStratiColumn = pck->createStratigraphicColumn("90f375b7-6865-4a69-943e-f2328fdbbb7e", "Minimal Stratigraphic column");
	RESQML2_NS::Model* minimalStratiModelFeature = pck->createStratigraphicModel("ea021981-1b79-435f-9f26-8bf03472efcf", "Minimal stratiModel");
	RESQML2_NS::StratigraphicColumnRankInterpretation* minimalStratiColumnRank = pck->createStratigraphicColumnRankInterpretationInApparentDepth(minimalStratiModelFeature, "31b0b787-31df-4b87-8830-a3863eb9842c", "Minimal Stratigraphic column rank ", 0);
	minimalStratiColumn->pushBackStratiColumnRank(minimalStratiColumnRank);

	// Build the stratigraphic column ranks
	stratiColumnRank0->pushBackStratiUnitInterpretation(stratiUnitAInterp);
	stratiColumnRank1->pushBackStratiUnitInterpretation(stratiUnitAInterp);
	stratiColumnRank0->pushBackStratiUnitInterpretation(stratiUnitBInterp);
	stratiColumnRank1->pushBackStratiUnitInterpretation(stratiUnitB1Interp);
	stratiColumnRank1->pushBackStratiUnitInterpretation(stratiUnitB2Interp);
	minimalStratiColumnRank->pushBackStratiUnitInterpretation(stratiUnitB1Interp);
	stratiColumnRank0->pushBackStratigraphicBinaryContact(stratiUnitAInterp, gsoap_eml2_3::resqml22__ContactMode::conformable, stratiUnitBInterp, gsoap_eml2_3::resqml22__ContactMode::conformable, horizon2Interp1);

	// WellboreFeature marker frame
	if (wellbore1Interp1 != nullptr) {
		RESQML2_NS::WellboreMarkerFrameRepresentation* wmf = pck->createWellboreMarkerFrameRepresentation(wellbore1Interp1, "657d5e6b-1752-425d-b3e7-237037fa11eb", "Wellbore Marker Frame", w1i1TrajRep);
		double markerMdValues[2] = { 350, 550 };
		wmf->setMdValues(markerMdValues, 2, hdfProxy);
		RESQML2_NS::WellboreMarker* marker0 = pck->createWellboreMarker(wmf, "624f9f17-6797-4d78-b3fc-9ca2c8174bcd", "", gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind::horizon);
		marker0->setBoundaryFeatureInterpretation(horizon1Interp1);
		marker0->setWitsmlWellboreMarker(witsmlWellboreMarker);
		RESQML2_NS::WellboreMarker* marker1 = pck->createWellboreMarker(wmf, "3611725e-4d9b-4d3e-87e6-58fcd238f5a8", "testing Fault", gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind::fault);
		marker1->setBoundaryFeatureInterpretation(fault1Interp1);
	}

	// ***********************
	// Sealed volume framework
	// ***********************
	RESQML2_NS::SealedVolumeFrameworkRepresentation* svf = pck->createSealedVolumeFrameworkRepresentation(stratiColumnRank1, "c7ed87c2-9a46-4e3d-8f0f-b25d4d72892a", "Minimal Sealed volume framework", sealedSurfaceFramework);

	// Add the surfaces.
	f1i1triRep->pushBackIntoRepresentationSet(svf);
	h1i1triRep->pushBackIntoRepresentationSet(svf);
	h2i1triRep->pushBackIntoRepresentationSet(svf);
	xMinusFrontierRep->pushBackIntoRepresentationSet(svf);
	xPlusFrontierRep->pushBackIntoRepresentationSet(svf);
	yMinusFrontierRep->pushBackIntoRepresentationSet(svf);
	yPlusFrontierRep->pushBackIntoRepresentationSet(svf);

	//Region 2
	std::vector<unsigned int> region2RepIndices = { 1, 0, 0, 2, 3, 5, 6 }; // face order => top, x plus, btm, x minus, y minus, y plus
	std::vector<unsigned int> region2PatchIndices = { 0, 1, 2, 0, 0, 0, 0 };
	bool region2Sides[7] = { false, false, false, true, true, true, true }; //Top face is true, bottom face is false and Frontiers are always on true side flag in this example.
	svf->pushBackVolumeRegion(stratiUnitB1Interp, 7, region2RepIndices.data(), region2PatchIndices.data(), region2Sides);

	//Region 5
	std::vector<unsigned int> region5RepIndices = { 1, 4, 2, 0, 0, 5, 6 };
	std::vector<unsigned int> region5PatchIndices = { 1, 0, 1, 3, 2, 1, 1 };
	bool region5Sides[7] = { false, true, true, true, true, true, true };
	svf->pushBackVolumeRegion(stratiUnitB1Interp, 7, region5RepIndices.data(), region5PatchIndices.data(), region5Sides);
}

void serializeGeobody(COMMON_NS::DataObjectRepository * pck, EML2_NS::AbstractHdfProxy* hdfProxy)
{
	// 2D
	RESQML2_NS::BoundaryFeature* geobodyBoundary = pck->createGeobodyBoundaryFeature("6d3c158c-303f-4b0d-bfc0-9ce4102ea616", "Geobody boundary");
	RESQML2_NS::GeobodyBoundaryInterpretation* geobodyBoundaryInterp = pck->createGeobodyBoundaryInterpretation(geobodyBoundary, "12c301a4-3e8b-401a-aca3-8d6f02d5d6d5", "Geobody boundary interp");
	RESQML2_NS::PointSetRepresentation* geobodyBoundaryPointSetRep = pck->createPointSetRepresentation(geobodyBoundaryInterp, "fbc5466c-94cd-46ab-8b48-2ae2162b372f", "Geobody boundary PointSetRep");
	double geobodyBoundaryPointCoords[18] = { 10, 70, 310, 11, 21, 280, 150, 30, 310, 400, 0, 365, 450, 75, 341, 475, 100, 352 };
	geobodyBoundaryPointSetRep->pushBackGeometryPatch(6, geobodyBoundaryPointCoords, hdfProxy);

	// 3D
	RESQML2_NS::RockVolumeFeature* geobody = pck->createGeobodyFeature("e221f9da-ead3-4a9d-8324-fc2e6606cb01", "Geobody");
	RESQML2_NS::GeobodyInterpretation* geobodyInterp = pck->createGeobodyInterpretation(geobody, "d445041f-6364-44e7-a7f8-ade5a93bfd49", "Geobody interp");
	RESQML2_NS::PointSetRepresentation* geobodyGraphNode = pck->createPointSetRepresentation(geobodyInterp, "8442a6b7-a97b-431e-abda-f72cf7ef346f", "Geobody graph node");
	double geobodyPointCoords[18] = { 50, 30, 330, 10, 28, 3000, 100, 50, 350, 300, 100, 400, 400, 20, 400, 400, 300, 400 };
	geobodyGraphNode->pushBackGeometryPatch(6, geobodyPointCoords, hdfProxy);
	//RESQML2_NS::SubRepresentation* geobodyGraphEdge = pck->createSubRepresentation(geobodyBoundaryInterp, "7e0450aa-c39d-49f8-bee4-62fc42bb849d", "Geobody graph edge");
}

void serializeBoundaries(COMMON_NS::DataObjectRepository * pck, EML2_NS::AbstractHdfProxy* hdfProxy)
{
	// Seismic Lattice
	RESQML2_NS::SeismicLatticeFeature* seismicLattice = pck->createSeismicLattice("eb6a5e97-4d86-4809-b136-051f34cfcb51", "Seismic lattice", 2, 2, 150, 152, 4, 2);
	RESQML2_NS::GenericFeatureInterpretation* seismicLatticeInterp = pck->createGenericFeatureInterpretation(seismicLattice, "97816427-6ef6-4776-b21c-5b93c8a6310a", "Seismic lattice Interp");
	RESQML2_NS::Grid2dRepresentation* seismicLatticeRep = pck->createGrid2dRepresentation(seismicLatticeInterp, "aa5b90f1-2eab-4fa6-8720-69dd4fd51a4d", "Seismic lattice Rep");
	seismicLatticeRep->setGeometryAsArray2dOfLatticePoints3d(4, 2, 0, 0, 0, 1, 0, 2, 0, 1, 3, 250, 200);

	// Seismic Line Set
	RESQML2_NS::SeismicLineSetFeature* seismicLineSet = pck->createSeismicLineSet("53c6a0be-c901-4bb6-845b-fba79745da02", "Seismic line Set");

	// Seismic Line
	RESQML2_NS::AbstractSeismicLineFeature* seismicLine = nullptr;
	if (pck->getDefaultResqmlVersion() == COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_0_1) {
		seismicLine = pck->createSeismicLine("117f9bf6-6bb0-49f2-9cee-46912300bff6", "Seismic line", 1, 0, 5);
	}
#if WITH_RESQML2_2
	else {
		seismicLine = pck->createShotPointLine("117f9bf6-6bb0-49f2-9cee-46912300bff6", "Seismic line");
	}
#endif
	seismicLine->setSeismicLineSet(seismicLineSet);
	RESQML2_NS::GenericFeatureInterpretation* seismicLineInterp = pck->createGenericFeatureInterpretation(seismicLine, "", "Seismic line Interp");
	RESQML2_NS::PolylineRepresentation* seismicLineRep = pck->createPolylineRepresentation(seismicLineInterp, "", "Seismic line Rep");
	double seismicLinePoints[15] = { 0, 100, 0, 150, 110, 0, 300, 120, 0, 450, 130, 0, 600, 140, 0 };
	seismicLineRep->setGeometry(seismicLinePoints, 5, hdfProxy);

	// Features
	//BoundaryFeature* bf = pck->createBoundaryFeature("", "testingBoundaryFeature");
	horizon1 = pck->createHorizon("35d7b57e-e5ff-4062-95af-ba2d7c4ce347", "Horizon1");
	tm timeStruct;
	timeStruct.tm_hour = 15;
	timeStruct.tm_min = 2;
	timeStruct.tm_sec = 35;
	timeStruct.tm_mday = 8;
	timeStruct.tm_mon = 1;
	timeStruct.tm_year = 0;
	timeStruct.tm_isdst = -1;
	mktime(&timeStruct);
	horizon1->setCreation(timeStruct);
	if (dynamic_cast<RESQML2_0_1_NS::Horizon*>(horizon1) != nullptr) {
		static_cast<RESQML2_0_1_NS::Horizon*>(horizon1)->setAge(300000000);
	}
	horizon2 = pck->createHorizon("fd7950a6-f62e-4e47-96c4-048820a61c59", "Horizon2");
	horizon2->setVersion("my version");
	fault1 = pck->createFault("1424bcc2-3d9d-4f30-b1f9-69dcb897e33b", "Fault1");
	fault1->setMetadata("", "philippe", 148526020, "philippe", "", 148526100, "");

	// Interpretations
	//BoundaryFeatureInterpretation* bfi = pck->createBoundaryFeatureInterpretation(bf, "", "testingBoundaryFeatureInterp");
	horizon1Interp1 = pck->createHorizonInterpretation(horizon1, "ac12dc12-4951-459b-b585-90f48aa88a5a", "Horizon1 Interp1");
	horizon2Interp1 = pck->createHorizonInterpretation(horizon2, "06993923-6331-4fad-bceb-fc79b05adfd7", "Horizon2 Interp1");
	fault1Interp1 = pck->createFaultInterpretation(fault1, "ba224651-7dd3-4952-85b0-cff6fe37508d", "Fault1 Interp1");

	//**************
	// Horizon Representations
	//**************
	RESQML2_NS::PolylineRepresentation* h1i1SinglePolylineRep = pck->createPolylineRepresentation(horizon1Interp1, "", "Horizon1 Interp1 SinglePolylineRep");
	double h1i1SinglePolylineRepPoints[12] = { 0, 100, 300, 150, 110, 300, 450, 130, 350, 600, 140, 350 };
	h1i1SinglePolylineRep->setGeometry(h1i1SinglePolylineRepPoints, 4, hdfProxy);
	double seismicLineAbscissa[4] = { 0.0, 1.0, 3.0, 4.0 };
	h1i1SinglePolylineRep->addSeismic2dCoordinatesToPatch(0, seismicLineAbscissa, seismicLineRep, hdfProxy);

#if defined(OFFICIAL)
	h1i1SingleGrid2dRep = pck->createGrid2dRepresentation(horizon1Interp1, local3dCrs, "", "Horizon1 Interp1 Grid2dRep");
	double zValues[8] = { 300, 300, 350, 350, 300, 300, 350, 350 };
	h1i1SingleGrid2dRep->setGeometryAsArray2dOfExplicitZ(zValues, 4, 2, hdfProxy, seismicLatticeRep);
#else
	h1i1SingleGrid2dRep = pck->createGrid2dRepresentation(horizon1Interp1, "", "Horizon1 Interp1 Grid2dRep");
	double zValues[8] = { 300, 300, 350, 350, 300, 300, 350, 350 };
	h1i1SingleGrid2dRep->setGeometryAsArray2dOfExplicitZ(zValues, 4, 2, hdfProxy, seismicLatticeRep, localTime3dCrs);
#endif

	RESQML2_NS::PointSetRepresentation* h1i1PointSetRep = pck->createPointSetRepresentation(horizon1Interp1, "", "Horizon1 Interp1 PointSetRep");
	double pointCoords[18] = { 10, 70, 301, 11, 21, 299, 150, 30, 301, 400, 0, 351, 450, 75, 340, 475, 100, 350 };
	h1i1PointSetRep->pushBackGeometryPatch(6, pointCoords, hdfProxy);

	// Horizon 1 triangulated representation
	h1i1triRep = pck->createTriangulatedSetRepresentation(horizon1Interp1,
		"0c49b40a-632a-457a-b519-a178f40a397d",
		"Horizon1 Interp1 TriRep");
	// Patch 0
	double explicitPointsHor1Patch0[15] = { 250, 0, 300, 250, 100, 300, 250, 200, 300, 0, 0, 300, 0, 200, 300 };
	unsigned int triangleNodeIndexHorPatch0[9] = { 0, 1, 3, 1, 4, 3, 1, 2, 4 };
	h1i1triRep->pushBackTrianglePatch(5, explicitPointsHor1Patch0, 3, triangleNodeIndexHorPatch0, hdfProxy);
	// Patch 1
	double explicitPointsHor1Patch1[15] = { 300, 0, 350, 300, 100, 350, 300, 200, 350, 700, 0, 350, 700, 200, 350 };
	unsigned int triangleNodeIndexHorPatch1[9] = { 5, 6, 8, 6, 9, 8, 6, 7, 9 };
	h1i1triRep->pushBackTrianglePatch(5, explicitPointsHor1Patch1, 3, triangleNodeIndexHorPatch1, hdfProxy);

	// Horizon 2 triangulated representation
	h2i1triRep = pck->createTriangulatedSetRepresentation(horizon2Interp1,
		"ea6943d0-30b0-47fd-80ad-a3cf019a8c92",
		"Horizon2 Interp1 TriRep");
	// Patch 0 (no seismic support)
	double explicitPointsHor2Patch0[15] = { 450, 0, 500, 450, 100, 500, 450, 200, 500, 0, 0, 500, 0, 200, 500 };
	h2i1triRep->pushBackTrianglePatch(5, explicitPointsHor2Patch0, 3, triangleNodeIndexHorPatch0, hdfProxy);
	// Patch 1 (seismic support)
	double explicitPointsHor2Patch1[15] = { 500, 0, 550, 500, 100, 550, 500, 200, 550, 700, 0, 550, 700, 200, 550 };
	h2i1triRep->pushBackTrianglePatch(5, explicitPointsHor2Patch1, 3, triangleNodeIndexHorPatch1, hdfProxy);
	double inlines[5] = { 0, 1, 2, 3, 4 }; // dummy values
	double crosslines[5] = { 10, 11, 12, 13, 14 }; // dummy values
	h2i1triRep->addSeismic3dCoordinatesToPatch(1, inlines, crosslines, 5, seismicLatticeRep, hdfProxy);

	// TriRep without interp
	RESQML2_NS::TriangulatedSetRepresentation* triRepWithoutInterp = pck->createTriangulatedSetRepresentation("eb0b55a5-9562-4642-946b-d2ec57172daf", "TriRep without interp");
	triRepWithoutInterp->pushBackTrianglePatch(5, explicitPointsHor2Patch0, 3, triangleNodeIndexHorPatch0, hdfProxy);

	//**************
	// Fault Representations
	//**************

	// Single patch triangulated representation
	f1i1triRepSinglePatch = pck->createTriangulatedSetRepresentation(fault1Interp1,
		"d8a03d57-8bf3-4f75-8645-ef2fbfa5d1e3",
		"Fault1 Interp1 TriRep Single Patch");
	//hsize_t dimExplicitPointsFault1 [1] = {6};
	double explicitPointsFault1[54] = { 150, 0, 200, 150, 100, 200, 150, 200, 200,
		250, 0, 300, 250, 100, 300, 250, 200, 300,
		300, 0, 350, 300, 100, 350, 300, 200, 350,
		450, 0, 500, 450, 100, 500, 450, 200, 500,
		500, 0, 550, 500, 100, 550, 500, 200, 550,
		600, 0, 650, 600, 100, 650, 600, 200, 650 };
	unsigned int triangleNodeIndexFault[60] = { 0, 4, 3, 0, 1, 4, 1, 2, 4, 2, 5, 4,
		3, 7, 6, 3, 4, 7, 4, 5, 7, 5, 8, 7,
		6, 10, 9, 6, 7, 10, 7, 8, 10, 8, 11, 10,
		9, 13, 12, 9, 10, 13, 10, 11, 13, 11, 14, 13,
		12, 16, 15, 12, 13, 16, 13, 14, 16, 14, 17, 16 };
	f1i1triRepSinglePatch->pushBackTrianglePatch(18, explicitPointsFault1, 20, triangleNodeIndexFault, hdfProxy);

	// multi patch triangulated representation
	f1i1triRep = pck->createTriangulatedSetRepresentation(fault1Interp1,
		"1a4112fa-c4ef-4c8d-aed0-47d9273bebc5",
		"Fault1 Interp1 TriRep");
	// Patch 0
	double explicitPointsFault1Patch0[18] = { 150, 0, 200, 150, 100, 200, 150, 200, 200,
		250, 0, 300, 250, 100, 300, 250, 200, 300 };
	unsigned int triangleNodeIndexFaultPatch0[12] = { 0, 4, 3, 0, 1, 4, 1, 2, 4, 2, 5, 4 };
	f1i1triRep->pushBackTrianglePatch(6, explicitPointsFault1Patch0, 4, triangleNodeIndexFaultPatch0, hdfProxy);
	// Patch 1
	double explicitPointsFault1Patch1[18] = { 250, 0, 300, 250, 100, 300, 250, 200, 300,
		300, 0, 350, 300, 100, 350, 300, 200, 350 };
	unsigned int triangleNodeIndexFaultPatch1[12] = { 6, 10, 9, 6, 7, 10, 7, 8, 10, 8, 11, 10 };
	f1i1triRep->pushBackTrianglePatch(6, explicitPointsFault1Patch1, 4, triangleNodeIndexFaultPatch1, hdfProxy);
	// Patch 2
	double explicitPointsFault1Patch2[18] = { 300, 0, 350, 300, 100, 350, 300, 200, 350,
		450, 0, 500, 450, 100, 500, 450, 200, 500 };
	unsigned int triangleNodeIndexFaultPatch2[12] = { 12, 16, 15, 12, 13, 16, 13, 14, 16, 14, 17, 16 };
	f1i1triRep->pushBackTrianglePatch(6, explicitPointsFault1Patch2, 4, triangleNodeIndexFaultPatch2, hdfProxy);
	// Patch 3
	double explicitPointsFault1Patch3[18] = { 450, 0, 500, 450, 100, 500, 450, 200, 500,
		500, 0, 550, 500, 100, 550, 500, 200, 550 };
	unsigned int triangleNodeIndexFaultPatch3[12] = { 18, 22, 21, 18, 19, 22, 19, 20, 22, 20, 23, 22 };
	f1i1triRep->pushBackTrianglePatch(6, explicitPointsFault1Patch3, 4, triangleNodeIndexFaultPatch3, hdfProxy);
	// Patch 4
	double explicitPointsFault1Patch4[18] = { 500, 0, 550, 500, 100, 550, 500, 200, 550,
		600, 0, 650, 600, 100, 650, 600, 200, 650 };
	unsigned int triangleNodeIndexFaultPatch4[12] = { 24, 28, 27, 24, 25, 28, 25, 26, 28, 26, 29, 28 };
	f1i1triRep->pushBackTrianglePatch(6, explicitPointsFault1Patch4, 4, triangleNodeIndexFaultPatch4, hdfProxy);

	// Fault polyline rep
	f1i1PolyLineRep = pck->createPolylineSetRepresentation(
		fault1Interp1,
		"65c59595-bf48-451e-94aa-120ebdf28d8b",
		"Fault1 Interp1 PolylineRep");
	unsigned int numNodesPerPolylinePerPatch[2] = { 3, 2 };
	double polylinePoints[15] = { 150, 0, 200, 300, 0, 350, 450, 0, 500, 150, 200, 200, 450, 200, 500 };
	f1i1PolyLineRep->pushBackGeometryPatch(numNodesPerPolylinePerPatch, polylinePoints, 2, false, hdfProxy);
	f1i1PolyLineRep->addSeismic3dCoordinatesToPatch(0, inlines, crosslines, 5, seismicLatticeRep, hdfProxy);

	//**************
	// Properties
	//**************

	if (pck->getDefaultResqmlVersion() == COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_0_1) {
		propType1 =  pck->createPropertyKind("f7ad7cf5-f2e7-4daa-8b13-7b3df4edba3b", "propType1", "F2I", gsoap_resqml2_0_1::resqml20__ResqmlUom::m, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::length);
	}
#if WITH_RESQML2_2
	else {
		propType1 = pck->createPropertyKind("f7ad7cf5-f2e7-4daa-8b13-7b3df4edba3b", "propType1", gsoap_eml2_1::eml21__QuantityClassKind::length);
	}
#endif
	RESQML2_NS::ContinuousProperty* contProp1 = pck->createContinuousProperty(h1i1SingleGrid2dRep, "fcaccfc7-10cb-4f73-800e-a381642478cb", "Horizon1 Interp1 Grid2dRep Prop1", 1,
		gsoap_eml2_3::resqml22__IndexableElement::nodes, "exoticMeter", propType1);
	float prop1Values[16] = { 301, 302, 301, 302, 351, 352, 351, 352, 301, 302, 301, 302, 351, 352, 351, 352 };
	contProp1->pushBackFloatHdf5Array2dOfValues(prop1Values, 2, 8, hdfProxy);

	EML2_NS::PropertyKind * propType2 = nullptr;
	if (pck->getDefaultResqmlVersion() == COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_0_1) {
		propType2 = pck->createPropertyKind("7372f8f6-b1fd-4263-b9a8-699d9cbf7da6", "propType2", "F2I", gsoap_resqml2_0_1::resqml20__ResqmlUom::K, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::thermodynamic_x0020temperature);
	}
#if WITH_RESQML2_2
	else {
		propType2 = pck->createPropertyKind("7372f8f6-b1fd-4263-b9a8-699d9cbf7da6", "propType2", gsoap_eml2_1::eml21__QuantityClassKind::thermodynamic_x0020temperature);
	}
#endif
	RESQML2_NS::ContinuousProperty* contProp2 = pck->createContinuousProperty(h1i1SingleGrid2dRep, "d3efb337-19f8-4b91-8b4f-3698afe17f01", "Horizon1 Interp1 Grid2dRep Prop2", 1,
		gsoap_eml2_3::resqml22__IndexableElement::nodes, gsoap_resqml2_0_1::resqml20__ResqmlUom::ft, propType2);
	double prop2Values[8] = { 302, 302, 352, 352, 302, 302, 352, 352 };
	contProp2->pushBackDoubleHdf5Array1dOfValues(prop2Values, 8, hdfProxy);
}

void serializeGrid(COMMON_NS::DataObjectRepository * pck, EML2_NS::AbstractHdfProxy* hdfProxy)
{
	RESQML2_NS::Model * earthModel = pck->createEarthModel("f2060ce0-fa3d-11e5-8620-0002a5d5c51b", "Grid");
	RESQML2_NS::EarthModelInterpretation * earthModelInterp = pck->createEarthModelInterpretation(earthModel, "f5cd7520-fa3d-11e5-b65b-0002a5d5c51b", "Grid interp");

	// ONE SUGAR
	RESQML2_NS::IjkGridExplicitRepresentation* singleCellIjkgrid = pck->createIjkGridExplicitRepresentation("e69bfe00-fa3d-11e5-b5eb-0002a5d5c51b", "One unfaulted sugar cube", 1, 1, 1);
	double singleCellIjkgridNodes[24] = { 0, 0, 300, 700, 0, 350, 0, 150, 300, 700, 150, 350,
		0, 0, 500, 700, 0, 550, 0, 150, 500, 700, 150, 550 };
	singleCellIjkgrid->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape::vertical, gsoap_resqml2_0_1::resqml20__KDirection::down, false, singleCellIjkgridNodes, hdfProxy);

	// ONE SUGAR PARAMETRIC
	RESQML2_NS::IjkGridParametricRepresentation* singleCellIjkgridParametric = pck->createIjkGridParametricRepresentation(earthModelInterp, "53bb70fe-2eef-4691-b4fe-14541e3a57eb", "One unfaulted sugar cube (parametric geometry)", 1, 1, 1);
	double singleCellParameters[8] = { 300, 300, 300, 300, 500, 500, 500, 500 };
	double singleCellControlPoints[12] = { 0, 0, 300, 700, 0, 300, 0, 150, 300, 700, 150, 300 };
	short singleCellPillarKind[4] = { 0, 0, 0, 0 };
	singleCellIjkgridParametric->setGeometryAsParametricNonSplittedPillarNodes(gsoap_resqml2_0_1::resqml20__PillarShape::vertical, false,
		singleCellParameters, singleCellControlPoints, NULL, 1, singleCellPillarKind, hdfProxy);

	// TWO SUGARS EXPLICIT
	ijkgrid = pck->createIjkGridExplicitRepresentation(earthModelInterp, "df2103a0-fa3d-11e5-b8d4-0002a5d5c51b", "Two faulted sugar cubes (explicit geometry)", 2, 1, 1);
	double nodes[48] = { 0, 0, 300, 375, 0, 300, 700, 0, 350, 0, 150, 300, 375, 150, 300, 700, 150, 350, /* SPLIT*/ 375, 0, 350, 375, 150, 350,
		0, 0, 500, 375, 0, 500, 700, 0, 550, 0, 150, 500, 375, 150, 500, 700, 150, 550, /* SPLIT*/ 375, 0, 550, 375, 150, 550 };
	unsigned int pillarOfCoordinateLine[2] = { 1, 4 };
	unsigned int splitCoordinateLineColumnCumulativeCount[2] = { 1, 2 };
	unsigned int splitCoordinateLineColumns[2] = { 1, 1 };
	ijkgrid->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape::vertical, gsoap_resqml2_0_1::resqml20__KDirection::down, false, nodes, hdfProxy,
		2, pillarOfCoordinateLine, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns);

	// FOUR SUGARS PARAMETRIC
	RESQML2_NS::IjkGridParametricRepresentation* ijkgridParametric = pck->createIjkGridParametricRepresentation(earthModelInterp, "37c45c00-fa3e-11e5-a21e-0002a5d5c51b", "Four faulted sugar cubes (parametric geometry)", 2, 1, 2);
	double parameters[24] = { 300, 300, 350, 300, 300, 350, /* SPLIT*/ 350, 350,
		400, 400, 450, 400, 400, 450, /* SPLIT*/ 450, 450,
		500, 500, 550, 500, 500, 550, /* SPLIT*/ 550, 550 };
	double controlPoints[18] = { 0, 0, 300, 375, 0, 300, 700, 0, 350, 0, 150, 300, 375, 150, 300, 700, 150, 350 };
	ijkgridParametric->setGeometryAsParametricSplittedPillarNodes(false, parameters, controlPoints, NULL, 1, 0, hdfProxy,
		2, pillarOfCoordinateLine, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns);

	// FOUR SUGARS PARAMETRIC STRAIGHT
	RESQML2_NS::IjkGridParametricRepresentation* ijkgridParametricStraight = pck->createIjkGridParametricRepresentation(earthModelInterp, "f68235af-1d7a-4e24-93a8-10739b15ca40", "Four faulted sugar cubes (straight parametric geometry)", 2, 1, 2);
	double controlPointsParametricStraight[36] = { 0, 0, 300, 375, 0, 300, 700, 0, 350, 0, 150, 300, 375, 150, 300, 700, 150, 350,
		0, 0, 500, 375, 0, 500, 700, 0, 550, 0, 150, 500, 375, 150, 500, 700, 150, 550 };
	double controlPointsParameters[12] = { 300, 300, 350, 300, 300, 350,
		500, 500, 550, 500, 500, 550 };
	ijkgridParametricStraight->setGeometryAsParametricSplittedPillarNodes(false, parameters, controlPointsParametricStraight, controlPointsParameters, 2, 1, hdfProxy,
		2, pillarOfCoordinateLine, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns);

	// FOUR SUGARS PARAMETRIC different line kind and one cubic pillar
	RESQML2_NS::IjkGridParametricRepresentation* ijkgridParametricNotSameLineKind = pck->createIjkGridParametricRepresentation("3ce91933-4f6f-4f35-b0ac-4ba4672f0a87", "Four faulted sugar cubes with one cubic pillar", 2, 1, 2);
	const double nan = numeric_limits<double>::quiet_NaN();
	double controlPointsNotSameLineKind[54] = { 0, 0, 300, 375, 0, 300, 700, 0, 350, 0, 150, 300, 375, 150, 300, 700, 150, 350,
		50, 30, 1000, 400, 0, 400, nan, nan, nan, nan, nan, nan, nan, nan, nan, nan, nan, nan,
		nan, nan, nan, 450, 0, 600, nan, nan, nan, nan, nan, nan, nan, nan, nan, nan, nan, nan };
	double controlPointParametersNotSameLineKind[18] = { 300, 300, 350, 300, 300, 350,
		1000, 400, nan, nan, nan, nan,
		nan, 600, nan, nan, nan, nan };
	short pillarKind[6] = { 1, 4, 0, 0, 0, 0 };
	ijkgridParametricNotSameLineKind->setGeometryAsParametricSplittedPillarNodes(gsoap_resqml2_0_1::resqml20__PillarShape::straight, false, parameters, controlPointsNotSameLineKind, controlPointParametersNotSameLineKind, 3, pillarKind, hdfProxy,
		2, pillarOfCoordinateLine, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns);

	// FOUR SUGARS PARAMETRIC different line kind an one cubic pillar : A copy
	RESQML2_NS::IjkGridParametricRepresentation* ijkgridParametricNotSameLineKindCopy = pck->createIjkGridParametricRepresentation("46efd88c-87e1-4e00-bbdd-4c7bcc941749", "Copy of Four faulted sugar cubes with one cubic pillar", 2, 1, 2);
	const std::string hdfDatasetPrefix = "/" + ijkgridParametricNotSameLineKind->getXmlNamespace() + "/" + ijkgridParametricNotSameLineKind->getUuid();
	ijkgridParametricNotSameLineKindCopy->setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(gsoap_resqml2_0_1::resqml20__PillarShape::straight, gsoap_resqml2_0_1::resqml20__KDirection::down, false,
		hdfDatasetPrefix + "/PointParameters", hdfDatasetPrefix + "/ControlPoints", hdfDatasetPrefix + "/controlPointParameters", 3, hdfDatasetPrefix + "/LineKindIndices", hdfDatasetPrefix + "/PillarGeometryIsDefined", hdfProxy,
		2, hdfDatasetPrefix + "/PillarIndices",
		hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + CUMULATIVE_LENGTH_DS_NAME, hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + ELEMENTS_DS_NAME);

	// 4*3*2 explicit grid Left Handed
	RESQML2_NS::IjkGridExplicitRepresentation* ijkgrid432 = pck->createIjkGridExplicitRepresentation("e96c2bde-e3ae-4d51-b078-a8e57fb1e667", "Four by Three by Two Left Handed", 4, 3, 2);
	double nodes432[216] = {
		0, 0, 300, 150, 0, 300, 375, 0, 300, 550, 0, 350, 700, 0, 350, //IJ0K0
		0, 50, 300, 150, 50, 300, 375, 50, 300, 550, 50, 350, 700, 50, 350, //IJ1K0
		0, 100, 300, 150, 100, 300, 375, 100, 300, 550, 100, 350, 700, 100, 350, //IJ2K0
		0, 150, 300, 150, 150, 300, 375, 150, 300, 550, 150, 350, 700, 150, 350, //IJ3K0
		375, 0, 350, 375, 50, 350, 375, 100, 350, 375, 150, 350, // SPLIT K0
		0, 0, 400, 150, 0, 400, 375, 0, 400, 550, 0, 450, 700, 0, 450, //IJ0K1
		0, 50, 400, 150, 50, 400, 375, 50, 400, 550, 50, 450, 700, 50, 450, //IJ1K1
		0, 100, 400, 150, 100, 400, 375, 100, 400, 550, 100, 450, 700, 100, 450, //IJ2K1
		0, 150, 400, 150, 150, 400, 375, 150, 400, 550, 150, 450, 700, 150, 450, //IJ3K1
		375, 0, 450, 375, 50, 450, 375, 100, 450, 375, 150, 450, // SPLIT K1
		0, 0, 500, 150, 0, 500, 375, 0, 500, 550, 0, 550, 700, 0, 550, //IJ0K2
		0, 50, 500, 150, 50, 500, 375, 50, 500, 550, 50, 550, 700, 50, 550, //IJ1K2
		0, 100, 500, 150, 100, 500, 375, 100, 500, 550, 100, 550, 700, 100, 550, //IJ2K2
		0, 150, 500, 150, 150, 500, 375, 150, 500, 550, 150, 550, 700, 150, 550, //IJ3K2
		375, 0, 550, 375, 50, 550, 375, 100, 550, 375, 150, 550 // SPLIT K2
	};
	unsigned int pillarOfCoordinateLine432[4] = { 2, 7, 12, 17 };
	unsigned int splitCoordinateLineColumnCumulativeCount432[4] = { 1, 3, 5, 6 };
	unsigned int splitCoordinateLineColumns432[6] = { 2, 2, 6, 6, 10, 10 };
	ijkgrid432->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape::vertical, gsoap_resqml2_0_1::resqml20__KDirection::down, false, nodes432, hdfProxy,
		4, pillarOfCoordinateLine432, splitCoordinateLineColumnCumulativeCount432, splitCoordinateLineColumns432);

	// 4*3*2 explicit grid Right Handed
	RESQML2_NS::IjkGridExplicitRepresentation* ijkgrid432rh = pck->createIjkGridExplicitRepresentation("4fc004e1-0f7d-46a8-935e-588f790a6f84", "Four by Three by Two Right Handed", 4, 3, 2);
	double nodes432rh[216] = {
		0, 150, 300, 150, 150, 300, 375, 150, 300, 550, 150, 350, 700, 150, 350, //IJ0K0
		0, 100, 300, 150, 100, 300, 375, 100, 300, 550, 100, 350, 700, 100, 350, //IJ1K0
		0, 50, 300, 150, 50, 300, 375, 50, 300, 550, 50, 350, 700, 50, 350, //IJ2K0
		0, 0, 300, 150, 0, 300, 375, 0, 300, 550, 0, 350, 700, 0, 350, //IJ3K0
		375, 0, 350, 375, 50, 350, 375, 100, 350, 375, 150, 350, // SPLIT K0
		0, 150, 400, 150, 150, 400, 375, 150, 400, 550, 150, 450, 700, 150, 450, //IJ0K1
		0, 100, 400, 150, 100, 400, 375, 100, 400, 550, 100, 450, 700, 100, 450, //IJ1K1
		0, 50, 400, 150, 50, 400, 375, 50, 400, 550, 50, 450, 700, 50, 450, //IJ2K1
		0, 0, 400, 150, 0, 400, 375, 0, 400, 550, 0, 450, 700, 0, 450, //IJ3K1
		375, 0, 450, 375, 50, 450, 375, 100, 450, 375, 150, 450, // SPLIT K1
		0, 150, 500, 150, 150, 500, 375, 150, 500, 550, 150, 550, 700, 150, 550, //IJ0K2
		0, 100, 500, 150, 100, 500, 375, 100, 500, 550, 100, 550, 700, 100, 550, //IJ1K2
		0, 50, 500, 150, 50, 500, 375, 50, 500, 550, 50, 550, 700, 50, 550, //IJ2K2
		0, 0, 500, 150, 0, 500, 375, 0, 500, 550, 0, 550, 700, 0, 550, //IJ3K2
		375, 0, 550, 375, 50, 550, 375, 100, 550, 375, 150, 550 // SPLIT K2
	};
	unsigned int pillarOfCoordinateLine432rh[4] = { 17, 12, 7, 2 };
	unsigned int splitCoordinateLineColumnCumulativeCount432rh[4] = { 1, 3, 5, 6 };
	unsigned int splitCoordinateLineColumns432rh[6] = { 10, 10, 6, 6, 2, 2 };
	ijkgrid432rh->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape::vertical, gsoap_resqml2_0_1::resqml20__KDirection::down, true, nodes432rh, hdfProxy,
		4, pillarOfCoordinateLine432rh, splitCoordinateLineColumnCumulativeCount432rh, splitCoordinateLineColumns432rh);
	unsigned char enabledCells32rh[24] = {
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0
	};
	ijkgrid432rh->setEnabledCells(enabledCells32rh);

	// 4*3*2 explicit grid with gap layer
	bool kgap[1] = { true };
	RESQML2_NS::IjkGridExplicitRepresentation* ijkgrid432gap = pck->createIjkGridExplicitRepresentation("c14755a5-e3b3-4272-99e5-fc20993b79a0", "Four by Three by Two with gap layer", 4, 3, 2, kgap);
	double nodes432gap[288] = {
		0, 150, 300, 150, 150, 300, 375, 150, 300, 550, 150, 350, 700, 150, 350, //IJ0K0
		0, 100, 300, 150, 100, 300, 375, 100, 300, 550, 100, 350, 700, 100, 350, //IJ1K0
		0, 50, 300, 150, 50, 300, 375, 50, 300, 550, 50, 350, 700, 50, 350, //IJ2K0
		0, 0, 300, 150, 0, 300, 375, 0, 300, 550, 0, 350, 700, 0, 350, //IJ3K0
		375, 0, 350, 375, 50, 350, 375, 100, 350, 375, 150, 350, // SPLIT K0
		
		0, 150, 360, 150, 150, 360, 375, 150, 360, 550, 150, 410, 700, 150, 410, //IJ0K1
		0, 100, 360, 150, 100, 360, 375, 100, 360, 550, 100, 410, 700, 100, 410, //IJ1K1
		0, 50, 360, 150, 50, 360, 375, 50, 360, 550, 50, 410, 700, 50, 410, //IJ2K1
		0, 0, 360, 150, 0, 360, 375, 0, 360, 550, 0, 410, 700, 0, 410, //IJ3K1
		375, 0, 410, 375, 50, 410, 375, 100, 410, 375, 150, 410, // SPLIT K1
		// K Gap Layer
		0, 150, 400, 150, 150, 400, 375, 150, 400, 550, 150, 450, 700, 150, 450, //IJ0K1
		0, 100, 400, 150, 100, 400, 375, 100, 400, 550, 100, 450, 700, 100, 450, //IJ1K1
		0, 50, 400, 150, 50, 400, 375, 50, 400, 550, 50, 450, 700, 50, 450, //IJ2K1
		0, 0, 400, 150, 0, 400, 375, 0, 400, 550, 0, 450, 700, 0, 450, //IJ3K1
		375, 0, 450, 375, 50, 450, 375, 100, 450, 375, 150, 450, // SPLIT K1

		0, 150, 500, 150, 150, 500, 375, 150, 500, 550, 150, 550, 700, 150, 550, //IJ0K3
		0, 100, 500, 150, 100, 500, 375, 100, 500, 550, 100, 550, 700, 100, 550, //IJ1K3
		0, 50, 500, 150, 50, 500, 375, 50, 500, 550, 50, 550, 700, 50, 550, //IJ2K3
		0, 0, 500, 150, 0, 500, 375, 0, 500, 550, 0, 550, 700, 0, 550, //IJ3K3
		375, 0, 550, 375, 50, 550, 375, 100, 550, 375, 150, 550 // SPLIT K3
	};
	unsigned int pillarOfCoordinateLine432gap[4] = { 17, 12, 7, 2 };
	unsigned int splitCoordinateLineColumnCumulativeCount432gap[4] = { 1, 3, 5, 6 };
	unsigned int splitCoordinateLineColumns432gap[6] = { 10, 10, 6, 6, 2, 2 };
	ijkgrid432gap->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape::vertical, gsoap_resqml2_0_1::resqml20__KDirection::down, true, nodes432gap, hdfProxy,
		4, pillarOfCoordinateLine432gap, splitCoordinateLineColumnCumulativeCount432gap, splitCoordinateLineColumns432gap);
	unsigned char enabledCells32gap[24] = {
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0
	};
	ijkgrid432gap->setEnabledCells(enabledCells32gap);

	//**************
	// Subrepresentations
	//**************
	if (fault1Interp1 != nullptr)
	{
		RESQML2_NS::SubRepresentation * faultSubRep = pck->createSubRepresentation(fault1Interp1, "ff248280-fa3d-11e5-a35c-0002a5d5c51b", "Fault Subrep In Grid");
		faultSubRep->pushBackSupportingRepresentation(ijkgrid);
		uint64_t faultPillar[2] = { 1, 4 };
		faultSubRep->pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement::pillars, 2, faultPillar, hdfProxy);
	}

	RESQML2_NS::SubRepresentation * actnum = pck->createSubRepresentation("323001d0-468c-41d7-abec-7d12c3c9428b", "ACTNUM");
	actnum->pushBackSupportingRepresentation(ijkgrid432);
	uint64_t actnumValues[21] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
		12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22
	};
	actnum->pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement::cells, 21, actnumValues, hdfProxy);

	// Double grid subrep
	RESQML2_NS::SubRepresentation * doubleGridSubrep = pck->createSubRepresentation("f6d23b9c-e45d-4638-9601-ae3b682129a0", "TEST MULTI GRIDS SUBREP");
	doubleGridSubrep->pushBackSupportingRepresentation(ijkgrid432);
	doubleGridSubrep->pushBackSupportingRepresentation(ijkgrid);
	uint64_t doubleGridSubrepValues[23] = {
		1, 4,
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
		12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22
	};
	short doubleGridSubrepSupportingRepIndices[23] = {
		0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};

	doubleGridSubrep->pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement::cells, 23, doubleGridSubrepValues, hdfProxy, doubleGridSubrepSupportingRepIndices);

	//**************
	// Grid Connection
	//**************
	RESQML2_NS::GridConnectionSetRepresentation * gridConnSet = pck->createGridConnectionSetRepresentation("03bb6fc0-fa3e-11e5-8c09-0002a5d5c51b", "GridConnectionSetRepresentation");
	gridConnSet->pushBackSupportingGridRepresentation(ijkgrid);
	int64_t cellConn[6] = { 0, 9999, 0, 1, 9999, 1 };
	gridConnSet->setCellIndexPairs(3, cellConn, 9999, hdfProxy);
	int localFacePerCellIndexPairs[6] = { 3, 9999, 3, 5, 9999, 5 };
	gridConnSet->setLocalFacePerCellIndexPairs(3, localFacePerCellIndexPairs, -1, hdfProxy);

	if (fault1Interp1 != nullptr)
	{
		// link to fault
		gridConnSet->pushBackInterpretation(fault1Interp1);
		unsigned int faultIndices = 0;
		gridConnSet->setConnectionInterpretationIndices(&faultIndices, 1, 9999, hdfProxy);
	}

	RESQML2_NS::GridConnectionSetRepresentation * gridConnSet432 = pck->createGridConnectionSetRepresentation("20b480a8-5e3b-4336-8f6e-1b3099c2c60f", "GridConnectionSetRepresentation");
	gridConnSet432->pushBackSupportingGridRepresentation(ijkgrid432);
	int64_t cellConn432[30] = {
		1, 9999, 5, 9999, 9, 9999,
		1, 2, 5, 6, 9, 10,
		13, 2, 17, 6, 21, 10,
		13, 14, 17, 18, 21, 22,
		9999, 14, 9999, 18, 9999, 22
	};
	gridConnSet432->setCellIndexPairs(15, cellConn432, 9999, hdfProxy);
	int localFacePerCellIndexPairs432[30] = {
		3, 9999, 3, 9999, 3, 9999,
		3, 5, 3, 5, 3, 5,
		3, 5, 3, 5, 3, 5,
		3, 5, 3, 5, 3, 5,
		9999, 5, 9999, 5, 9999, 5
	};
	gridConnSet432->setLocalFacePerCellIndexPairs(15, localFacePerCellIndexPairs432, -1, hdfProxy);

	RESQML2_NS::GridConnectionSetRepresentation * gridConnSet432rh = pck->createGridConnectionSetRepresentation("a3d1462a-04e3-4374-921b-a4a1e9ba3ea3", "GridConnectionSetRepresentation");
	gridConnSet432rh->pushBackSupportingGridRepresentation(ijkgrid432rh);
	gridConnSet432rh->setCellIndexPairs(15, cellConn432, 9999, hdfProxy);
	gridConnSet432rh->setLocalFacePerCellIndexPairs(15, localFacePerCellIndexPairs432, -1, hdfProxy);

	//**************
	// Discrete Properties
	//**************
	if (pck->getDefaultResqmlVersion() == COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_0_1) {
		propType1 = pck->createPropertyKind("0a5f4400-fa3e-11e5-80a4-0002a5d5c51b", "cellIndex", "F2I", gsoap_resqml2_0_1::resqml20__ResqmlUom::Euc, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::discrete);
	}
#if WITH_RESQML2_2
	else {
		propType1 = pck->createPropertyKind("0a5f4400-fa3e-11e5-80a4-0002a5d5c51b", "cellIndex", gsoap_eml2_1::eml21__QuantityClassKind::not_x0020a_x0020measure);
	}
#endif
	discreteProp1 = pck->createDiscreteProperty(ijkgrid, "ee0857fe-23ad-4dd9-8300-21fa2e9fb572", "Two faulted sugar cubes cellIndex", 1,
		gsoap_eml2_3::resqml22__IndexableElement::cells, propType1);
	unsigned short prop1Values[2] = { 0, 1 };
	discreteProp1->pushBackUShortHdf5Array3dOfValues(prop1Values, 2, 1, 1, hdfProxy, 1111);
	RESQML2_NS::DiscreteProperty* discreteProp2 = pck->createDiscreteProperty(ijkgrid, "da73937c-2c60-4e10-8917-5154fde4ded5", "Two faulted sugar cubes other cellIndex", 1,
		gsoap_eml2_3::resqml22__IndexableElement::cells, propType1);
	int64_t prop2Values[2] = { 10, 11 };
	discreteProp2->pushBackLongHdf5Array3dOfValues(prop2Values, 2, 1, 1, hdfProxy, 1111);

	RESQML2_NS::PropertySet* propSet = pck->createPropertySet("", "Testing property set", false, true,gsoap_eml2_3::resqml22__TimeSetKind::not_x0020a_x0020time_x0020set);
	propSet->pushBackProperty(discreteProp1);
	propSet->pushBackProperty(discreteProp2);

	RESQML2_NS::DiscreteProperty* discreteProp1OnIjkgridParametric = pck->createDiscreteProperty(ijkgridParametric, "eb3dbf6c-5745-4e41-9d09-672f6fbab414", "Four sugar cubes cellIndex", 1,
		gsoap_eml2_3::resqml22__IndexableElement::cells, propType1);
	unsigned short prop1ValuesOnIjkgridParametric[4] = { 0, 1, 2, 3 };
	discreteProp1OnIjkgridParametric->pushBackUShortHdf5Array3dOfValues(prop1ValuesOnIjkgridParametric, 2, 1, 2, hdfProxy, 1111, 0, 3);
	//Move this prop to another same ninjnk ijk grid
	discreteProp1OnIjkgridParametric->setRepresentation(ijkgridParametricNotSameLineKind);

	RESQML2_NS::DiscreteProperty* discreteProp432 = pck->createDiscreteProperty(ijkgrid432, "f9447f76-34c5-4967-a3ee-4f400f96dba6", "4x3x2 grid cellIndex", 1,
		gsoap_eml2_3::resqml22__IndexableElement::cells, propType1);
	LONG64 discreteProp432Values[24] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
		12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 };
	//hdfProxy->setMaxChunkSize(192/2); // Create two chunks
	discreteProp432->pushBackLongHdf5Array3dOfValues(discreteProp432Values, 4, 3, 2, hdfProxy, 1111);

	//**************
	// Time Series
	//**************
	EML2_NS::TimeSeries * timeSeries = pck->createTimeSeries("1187d8a0-fa3e-11e5-ac3a-0002a5d5c51b", "Testing time series");
	tm timeStruct;
	timeStruct.tm_hour = 15;
	timeStruct.tm_min = 2;
	timeStruct.tm_sec = 35;
	timeStruct.tm_mday = 8;
	timeStruct.tm_mon = 1;
	timeStruct.tm_year = 0;
	timeStruct.tm_isdst = -1;
	mktime(&timeStruct); 
	timeSeries->pushBackTimestamp(timeStruct);
	timeSeries->pushBackTimestamp(1409753895);
	timeSeries->pushBackTimestamp(1441289895);
	if (pck->getDefaultResqmlVersion() == COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_0_1) {
		RESQML2_NS::ContinuousProperty* continuousPropTime0 = pck->createContinuousProperty(ijkgrid, "18027a00-fa3e-11e5-8255-0002a5d5c51b", "Time Series Property", 1,
			gsoap_eml2_3::resqml22__IndexableElement::cells, gsoap_resqml2_0_1::resqml20__ResqmlUom::m, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::length);
		RESQML2_NS::ContinuousProperty* continuousPropTime1 = pck->createContinuousProperty(ijkgrid, "1ba54340-fa3e-11e5-9534-0002a5d5c51b", "Time Series Property", 1,
			gsoap_eml2_3::resqml22__IndexableElement::cells, gsoap_resqml2_0_1::resqml20__ResqmlUom::m, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::length);
		RESQML2_NS::ContinuousProperty* continuousPropTime2 = pck->createContinuousProperty(ijkgrid, "203db720-fa3e-11e5-bf9d-0002a5d5c51b", "Time Series Property ", 1,
			gsoap_eml2_3::resqml22__IndexableElement::cells, gsoap_resqml2_0_1::resqml20__ResqmlUom::m, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::length);
		continuousPropTime0->setTimeIndices(0, 1, timeSeries);
		double valuesTime0[2] = { 0, 1 };
		continuousPropTime0->pushBackDoubleHdf5Array3dOfValues(valuesTime0, 2, 1, 1, hdfProxy);
		continuousPropTime1->setTimeIndices(1, 1, timeSeries);
		double valuesTime1[2] = { 2, 3 };
		continuousPropTime1->pushBackDoubleHdf5Array3dOfValues(valuesTime1, 2, 1, 1, hdfProxy);
		continuousPropTime2->setTimeIndices(2, 1, timeSeries);
		double valuesTime2[2] = { 3, 4 };
		continuousPropTime2->pushBackDoubleHdf5Array3dOfValues(valuesTime2, 2, 1, 1, hdfProxy);
	}
	else {
		EML2_NS::PropertyKind * standardLengthPropKind = nullptr;
		if (pck->getDefaultResqmlVersion() == COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_0_1) {
			standardLengthPropKind = pck->createPropertyKind("4a305182-221e-4205-9e7c-a36b06fa5b3d", "length", "F2I", gsoap_resqml2_0_1::resqml20__ResqmlUom::m, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::length);
		}
#if WITH_RESQML2_2
		else {
			standardLengthPropKind = pck->createPropertyKind("4a305182-221e-4205-9e7c-a36b06fa5b3d", "length", gsoap_eml2_1::eml21__QuantityClassKind::length);
		}
#endif
		RESQML2_NS::ContinuousProperty* dynamicContinuousProp = pck->createContinuousProperty(ijkgrid, "18027a00-fa3e-11e5-8255-0002a5d5c51b", "Time Series Property", 1,
			gsoap_eml2_3::resqml22__IndexableElement::cells, gsoap_resqml2_0_1::resqml20__ResqmlUom::m, standardLengthPropKind);
		dynamicContinuousProp->setTimeIndices(0, 3, timeSeries);
		double valuesTime[6] = { 0, 1, 2, 3, 3, 4 };
		unsigned long long dimensions[4] = { 2, 1, 1, 3 };
		dynamicContinuousProp->pushBackDoubleHdf5ArrayOfValues(
			valuesTime, dimensions, 4, hdfProxy);
	}

	//**************
	// Categorical Properties
	//**************

	RESQML2_NS::StringTableLookup* stringTableLookup = pck->createStringTableLookup("62245eb4-dbf4-4871-97de-de9e4f4597be", "My String Table Lookup");
	stringTableLookup->addValue("Cell index 0", 0);
	stringTableLookup->addValue("Cell index 1", 1);
	RESQML2_NS::CategoricalProperty* categoricalProp = pck->createCategoricalProperty(ijkgrid, "23b85de7-639c-48a5-a80d-e0fe76da416a", "Two faulted sugar cubes cellIndex (categorical)", 1,
		gsoap_eml2_3::resqml22__IndexableElement::cells, stringTableLookup, propType1);
	categoricalProp->pushBackUShortHdf5Array3dOfValues(prop1Values, 2, 1, 1, hdfProxy, 1111);

	// Relative permeability
	RESQML2_NS::ContinuousProperty* waterSat = pck->createContinuousProperty(ijkgrid, "cbbc24b1-9a4b-4088-9d0e-e254088d3840", "Water saturation", 1,
		gsoap_eml2_3::resqml22__IndexableElement::cells, gsoap_resqml2_0_1::resqml20__ResqmlUom::_x0025, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::saturation);
	double waterSatValues[2] = { 0.35, 0.85 };
	waterSat->pushBackDoubleHdf5Array3dOfValues(waterSatValues, 2, 1, 1, hdfProxy);

	RESQML2_NS::DoubleTableLookup* waterRelPermTable = pck->createDoubleTableLookup("c51039fb-3178-41d3-86d7-5e5a74c5a46b", "My String Table Lookup");
	waterRelPermTable->addValue(.0, .0);
	waterRelPermTable->addValue(0.22, 0.005);
	waterRelPermTable->addValue(0.75, 0.46);
	waterRelPermTable->addValue(1.0, 1.0);
	RESQML2_NS::CategoricalProperty* waterRelPerm = pck->createCategoricalProperty(ijkgrid, "dd4eae66-fe52-4086-a023-5b2c423543d5", "Water Relative Permeability", 1,
		gsoap_eml2_3::resqml22__IndexableElement::cells, waterRelPermTable, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::relative_x0020permeability);
	waterRelPerm->pushBackRefToExistingFloatingPointDataset(nullptr, "/resqml20/cbbc24b1-9a4b-4088-9d0e-e254088d3840/values_patch0");

	//**************
	// Points Properties
	//**************

	RESQML2_NS::PointsProperty* pointsProp = pck->createPointsProperty(ijkgrid, "fdf3e92b-1ac2-4589-832d-69ee7c167db7", "Cell center", 1,
		gsoap_eml2_3::resqml22__IndexableElement::cells, local3dCrs);
	double cellCenters[6] = { 185, 75, 400, 560, 75, 450 };
	pointsProp->pushBackArray3dOfXyzPoints(cellCenters, 2, 1, 1, hdfProxy);

	//**************
	// LGR
	//**************

	RESQML2_NS::IjkGridExplicitRepresentation* lgrGrid = pck->createIjkGridExplicitRepresentation("2aec1720-fa3e-11e5-a116-0002a5d5c51b", "LGR", 2, 1, 3);
	lgrGrid->setParentWindow(
		0, 2, 1,
		0, 1, 1,
		0, 3, 1,
		ijkgrid);

	//**************
	// Stratigraphy
	//**************
	int64_t stratiUnitIndice = 0;
	ijkgrid->setIntervalAssociationWithStratigraphicOrganizationInterpretation(&stratiUnitIndice, 1000, stratiColumnRank0);

	// Partial transfer
	RESQML2_NS::UnstructuredGridRepresentation* partialGrid = pck->createPartial<RESQML2_0_1_NS::UnstructuredGridRepresentation>("5cc3ee47-4bd5-4d82-ae3e-ed64e6d8d1eb", "Partial Grid");
	RESQML2_NS::ContinuousProperty* continuousProp1 = pck->createContinuousProperty(partialGrid, "cd627946-0f89-48fa-b99c-bdb35d8ac4aa", "Testing partial property", 1,
		gsoap_eml2_3::resqml22__IndexableElement::cells, gsoap_resqml2_0_1::resqml20__ResqmlUom::m, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::length);
	double continuousProp1Values[6] = { 0, 1, 2, 3, 4, 5 };
	continuousProp1->pushBackDoubleHdf5Array1dOfValues(continuousProp1Values, 6, hdfProxy);

	// sub rep of a partial unstructured grid
	RESQML2_NS::SubRepresentation * subRepOfUnstructuredGrid = pck->createSubRepresentation("6b48c8d0-d60e-42b5-994c-2d4d4f3d0765", "Subrep On Partial grid");
	subRepOfUnstructuredGrid->pushBackSupportingRepresentation(partialGrid);
	uint64_t nodeIndex[2] = { 0, 1 };
	subRepOfUnstructuredGrid->pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement::nodes, 2, nodeIndex, hdfProxy);

	// creating the unstructured grid
	RESQML2_NS::UnstructuredGridRepresentation* unstructuredGrid = pck->createUnstructuredGridRepresentation("9283cd33-5e52-4110-b7b1-616abde2b303", "One tetrahedron + prism grid", 2);

	double unstructuredGridPoints[] = { 0, 0, 300, 375, 0, 300, 0, 150, 300, // points for shared face between tetra and wedge
		0, 0, 500, // point for tetra
		0, 0, 0, 375, 0, 0, 0, 150, 0 }; // points for wedge

	// The point indices of each face.
	uint64_t nodeIndicesPerFace[27] = { 0, 1, 2, // shared face
		1, 2, 3, 0, 1, 3, 0, 2, 3, // faces for tetra
		0, 2, 6, 4, 2, 1, 5, 6, 0, 1, 5, 4, 4, 5, 6 //  faces for wedge
	};
	// The cumulative count of points per face i.e. first face contains 3 points, second face contains 6-3=3 points, third face contains 9-6=3 points etc...
	uint64_t nodeIndicesCumulativeCountPerFace[8] = { 3, // shared face
		6, 9, 12, // faces for tetra
		16, 20, 24, 27 //  faces for wedge
	};
	// The face indices of each cell. 
	uint64_t faceIndicesPerCell[9] = { 0, 1, 2, 3, // tetra
		0, 4, 5, 6, 7 }; //wedge
	uint64_t faceIndicesCumulativeCountPerCell[2] = { 4, 9 };
	// Exporting the right handness of each face of each cell is mandatory. However, it is often ignored by the readers. Dummy values
	unsigned char faceRightHandness[9] = { 0, 0, 1, 1, 1, 0, 1, 0, 0 };

	unstructuredGrid->setGeometry(faceRightHandness, unstructuredGridPoints, 7, nullptr, faceIndicesPerCell, faceIndicesCumulativeCountPerCell, 8, nodeIndicesPerFace, nodeIndicesCumulativeCountPerFace,
		gsoap_resqml2_0_1::resqml20__CellShape::prism);

	if (pck->getDefaultResqmlVersion() == COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_0_1) {

		// Create the property
		RESQML2_NS::ContinuousProperty* unstructuredGridProp = pck->createContinuousProperty(unstructuredGrid, "7444c6cb-dd53-4100-b252-2eacbbd9500c", "My polyhedra property", 1,
			gsoap_eml2_3::resqml22__IndexableElement::cells, gsoap_resqml2_0_1::resqml20__ResqmlUom::m, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::length);

		// Fill the property
		double propValues[2] = { 12.3, 45.6 };
		unstructuredGridProp->pushBackDoubleHdf5Array1dOfValues(propValues, 2);
	}
	else {
		EML2_NS::PropertyKind * standardLengthPropKind = nullptr;
		if (pck->getDefaultResqmlVersion() == COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_0_1) {
			standardLengthPropKind = pck->createPropertyKind("4a305182-221e-4205-9e7c-a36b06fa5b3d", "length", "F2I", gsoap_resqml2_0_1::resqml20__ResqmlUom::m, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::length);
		}
#if WITH_RESQML2_2
		else {
			standardLengthPropKind = pck->createPropertyKind("4a305182-221e-4205-9e7c-a36b06fa5b3d", "length", gsoap_eml2_1::eml21__QuantityClassKind::length);
		}
#endif
		RESQML2_NS::ContinuousProperty* unstructuredGridProp = pck->createContinuousProperty(unstructuredGrid, "7444c6cb-dd53-4100-b252-2eacbbd9500c", "My polyhedra property", 1,
			gsoap_eml2_3::resqml22__IndexableElement::cells, gsoap_resqml2_0_1::resqml20__ResqmlUom::m, standardLengthPropKind);

		// Fill the property
		double propValues[2] = { 12.3, 45.6 };
		unstructuredGridProp->pushBackDoubleHdf5Array1dOfValues(propValues, 2);
	}
}

void serializeRepresentationSetRepresentation(COMMON_NS::DataObjectRepository * pck, EML2_NS::AbstractHdfProxy*)
{
	RESQML2_NS::RepresentationSetRepresentation* result = pck->createRepresentationSetRepresentation("", "Testing Representation set");
	std::cout << "is homogeneous : " << result->isHomogeneous() << std::endl;
	f1i1triRepSinglePatch->pushBackIntoRepresentationSet(result);
	std::cout << "is homogeneous : " << result->isHomogeneous() << std::endl;
	f1i1triRep->pushBackIntoRepresentationSet(result);
	std::cout << "is homogeneous : " << result->isHomogeneous() << std::endl;
	h1i1triRep->pushBackIntoRepresentationSet(result);
	std::cout << "is homogeneous : " << result->isHomogeneous() << std::endl;
	h2i1triRep->pushBackIntoRepresentationSet(result);
	std::cout << "is homogeneous : " << result->isHomogeneous() << std::endl;
	w1i1TrajRep->pushBackIntoRepresentationSet(result);
	std::cout << "is homogeneous : " << result->isHomogeneous() << std::endl;
}

void serializeStructuralModel(COMMON_NS::DataObjectRepository & pck, EML2_NS::AbstractHdfProxy* hdfProxy)
{
	// =========================================================================
	// =========================================================================
	// Organization features
	RESQML2_NS::Model * structOrg1 = pck.createStructuralModel("446068f6-33d8-40f4-9bec-2640fb7df23e", "StructuralOrg1");
	structOrg1->setOriginator("Geosiris");
	structOrg1->setEditor("F2I");

	// =========================================================================
	// =========================================================================
	// Organization interpretations
	RESQML2_NS::StructuralOrganizationInterpretation * structuralOrganizationInterpretation = pck.createStructuralOrganizationInterpretationInApparentDepth(structOrg1, "456f31e2-f79a-400c-91a9-ffd1fc939d32", "StructuralOrg1 Interp1");
	structuralOrganizationInterpretation->setOriginator("Geosiris");
	structuralOrganizationInterpretation->setEditor("F2I");
	structuralOrganizationInterpretation->pushBackFaultInterpretation(fault1Interp1);
	structuralOrganizationInterpretation->pushBackHorizonInterpretation(horizon1Interp1, 0);
	structuralOrganizationInterpretation->pushBackHorizonInterpretation(horizon2Interp1, 0);

	// =========================================================================
	// =========================================================================
	// EarthModel
	RESQML2_NS::Model * earthModelOrg = pck.createEarthModel("cb8848cd-8df6-4373-8cdd-fdf5f944b6ab", "EarthModelOrg");
	earthModelOrg->setOriginator("Geosiris");
	earthModelOrg->setEditor("F2I");
	RESQML2_NS::EarthModelInterpretation * earthModel = pck.createEarthModelInterpretation(earthModelOrg, "03bb3a50-c206-4aee-8343-dbea84011850", "EarthModel");
	earthModel->setOriginator("Geosiris");
	earthModel->setEditor("F2I");
	earthModel->pushBackStructuralOrganizationInterpretation(structuralOrganizationInterpretation);

	// =========================================================================
	// Add frontiers
	RESQML2_NS::CulturalFeature* xPlusFrontier = pck.createCultural("e062ee65-8296-44c0-adf9-14cef0c2eb27", "X Plus Frontier");
	RESQML2_NS::GenericFeatureInterpretation* xPlusFrontierInterp = pck.createGenericFeatureInterpretation(xPlusFrontier, "e888c38b-86d5-41ae-9aaa-a7a41d0f4554", "X Plus Frontier Interp");
	RESQML2_NS::CulturalFeature* xMinusFrontier = pck.createCultural("0f979db7-1189-47f4-827f-f61f9d163655", "X Minus Frontier");
	RESQML2_NS::GenericFeatureInterpretation* xMinusFrontierInterp = pck.createGenericFeatureInterpretation(xMinusFrontier, "cdbf2692-ab91-4529-8878-c10348a263a6", "X Minus Frontier Interp");
	RESQML2_NS::CulturalFeature* yPlusFrontier = pck.createCultural("f50de712-10cd-40e1-ae71-fe36a5a78453", "Y Plus Frontier");
	RESQML2_NS::GenericFeatureInterpretation* yPlusFrontierInterp = pck.createGenericFeatureInterpretation(yPlusFrontier, "ef1b0d82-52f5-4394-9b1a-ea92fffa8548", "Y Plus Frontier Interp");
	RESQML2_NS::CulturalFeature* yMinusFrontier = pck.createCultural("d4820ef8-2698-407f-84c7-c36396e19d08", "Y Minus Frontier");
	RESQML2_NS::GenericFeatureInterpretation* yMinusFrontierInterp = pck.createGenericFeatureInterpretation(yMinusFrontier, "74977015-731a-4e66-8fba-7c42cc44faa0", "Y Minus Frontier Interp");

	// =========================================================================
	// Binary contact interpretation

	// Contact 0: fault1Interp1 HANGING_WALL_SIDE STOPS horizon1Interp1 BOTH_SIDES
	structuralOrganizationInterpretation->pushBackBinaryContact(fault1Interp1, gsoap_resqml2_0_1::resqml20__ContactSide::hanging_x0020wall,
		gsoap_eml2_3::resqml22__ContactVerb::interrupts,
		horizon1Interp1, gsoap_resqml2_0_1::resqml20__ContactSide::both);
	// Contact 1: fault1Interp1 FOOT_WALL_SIDE STOPS horizon1Interp1 BOTH_SIDES
	structuralOrganizationInterpretation->pushBackBinaryContact(fault1Interp1, gsoap_resqml2_0_1::resqml20__ContactSide::footwall,
		gsoap_eml2_3::resqml22__ContactVerb::interrupts,
		horizon1Interp1, gsoap_resqml2_0_1::resqml20__ContactSide::both);
	// Contact 2: fault1Interp1 HANGING_WALL_SIDE STOPS horizon2Interp1 BOTH_SIDES
	structuralOrganizationInterpretation->pushBackBinaryContact(fault1Interp1, gsoap_resqml2_0_1::resqml20__ContactSide::hanging_x0020wall,
		gsoap_eml2_3::resqml22__ContactVerb::interrupts,
		horizon2Interp1, gsoap_resqml2_0_1::resqml20__ContactSide::both);
	// Contact 3: fault1Interp1 FOOT_WALL_SIDE STOPS horizon2Interp1 BOTH_SIDES
	structuralOrganizationInterpretation->pushBackBinaryContact(fault1Interp1, gsoap_resqml2_0_1::resqml20__ContactSide::footwall,
		gsoap_eml2_3::resqml22__ContactVerb::interrupts,
		horizon2Interp1, gsoap_resqml2_0_1::resqml20__ContactSide::both);

	// Contact 4: horizon1Interp1 STOPS AT yMinusFrontierInterp
	structuralOrganizationInterpretation->pushBackBinaryContact(yMinusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		horizon1Interp1);
	// Contact 5: fault1Interp1 STOPS AT yMinusFrontierInterp (part above horizon1Interp1)
	structuralOrganizationInterpretation->pushBackBinaryContact(yMinusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		fault1Interp1);
	// Contact 6: horizon2Interp1 STOPS AT yMinusFrontierInterp
	structuralOrganizationInterpretation->pushBackBinaryContact(yMinusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		horizon2Interp1);

	// Contact 7: horizon1Interp1 STOPS AT yPlusFrontierInterp
	structuralOrganizationInterpretation->pushBackBinaryContact(yPlusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		horizon1Interp1);
	// Contact 8: fault1Interp1 STOPS AT yPlusFrontierInterp (part above horizon1Interp1)
	structuralOrganizationInterpretation->pushBackBinaryContact(yPlusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		fault1Interp1);
	// Contact 9: horizon2Interp1 STOPS AT yPlusFrontierInterp
	structuralOrganizationInterpretation->pushBackBinaryContact(yPlusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		horizon2Interp1);

	// Contact 10: horizon1Interp1 STOPS AT xMinusFrontierInterp
	structuralOrganizationInterpretation->pushBackBinaryContact(xMinusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		horizon1Interp1);
	// Contact 11: horizon2Interp1 STOPS AT xMinusFrontierInterp
	structuralOrganizationInterpretation->pushBackBinaryContact(xMinusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		horizon2Interp1);
	// Contact 12: xMinusFrontierInterp STOPS AT yMinusFrontierInterp
	structuralOrganizationInterpretation->pushBackBinaryContact(yMinusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		xMinusFrontierInterp);
	// Contact 13: xMinusFrontierInterp STOPS AT yPlusFrontierInterp
	structuralOrganizationInterpretation->pushBackBinaryContact(yPlusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		xMinusFrontierInterp);

	// Contact 14: fault1Interp1 STOPS AT yMinusFrontierInterp (part below horizon1Interp1)
	structuralOrganizationInterpretation->pushBackBinaryContact(yMinusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		fault1Interp1);
	// Contact 15: fault1Interp1 STOPS AT yPlusFrontierInterp (part above horizon1Interp1)
	structuralOrganizationInterpretation->pushBackBinaryContact(yPlusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		fault1Interp1);

	// Contact 16: horizon1Interp1 STOPS AT yMinusFrontierInterp
	structuralOrganizationInterpretation->pushBackBinaryContact(yMinusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		horizon1Interp1);
	// Contact 17: fault1Interp1 STOPS AT yMinusFrontierInterp (part below horizon2Interp1)
	structuralOrganizationInterpretation->pushBackBinaryContact(yMinusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		fault1Interp1);
	// Contact 18: horizon2Interp1 STOPS AT yMinusFrontierInterp
	structuralOrganizationInterpretation->pushBackBinaryContact(yMinusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		horizon2Interp1);

	// Contact 19: horizon1Interp1 STOPS AT yPlusFrontierInterp
	structuralOrganizationInterpretation->pushBackBinaryContact(yPlusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		horizon1Interp1);
	// Contact 20: fault1Interp1 STOPS AT yPlusFrontierInterp (part below horizon2Interp1)
	structuralOrganizationInterpretation->pushBackBinaryContact(yPlusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		fault1Interp1);
	// Contact 21: horizon2Interp1 STOPS AT yPlusFrontierInterp
	structuralOrganizationInterpretation->pushBackBinaryContact(yPlusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		horizon2Interp1);

	// Contact 22: horizon1Interp1 STOPS AT xPlusFrontierInterp
	structuralOrganizationInterpretation->pushBackBinaryContact(xPlusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		horizon1Interp1);
	// Contact 23: horizon2Interp1 STOPS AT xPlusFrontierInterp
	structuralOrganizationInterpretation->pushBackBinaryContact(xPlusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		horizon2Interp1);
	// Contact 24: xPlusFrontierInterp STOPS AT yMinusFrontierInterp
	structuralOrganizationInterpretation->pushBackBinaryContact(yMinusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		xPlusFrontierInterp);
	// Contact 25: xPlusFrontierInterp STOPS AT yPlusFrontierInterp
	structuralOrganizationInterpretation->pushBackBinaryContact(yPlusFrontierInterp,
		gsoap_eml2_3::resqml22__ContactVerb::stops,
		xPlusFrontierInterp);

	// =========================================================================
	// =========================================================================
	// SurfaceFramework
	//    SurfaceFramework* structuralOrganizationInterpretationSurfaceFramework = pck.createSurfaceFramework(structuralOrganizationInterpretation, "", "StructuralOrg1 Interp1 Interp1 SurfFrmwk", true);
	//    structuralOrganizationInterpretationSurfaceFramework->pushBackRepresentation(f1i1triRep);
	//    structuralOrganizationInterpretationSurfaceFramework->pushBackRepresentation(h1i1triRep);
	//    structuralOrganizationInterpretationSurfaceFramework->pushBackRepresentation(h2i1triRep);

	// Single Patch Fault 1
	RESQML2_NS::SealedSurfaceFrameworkRepresentation* singlePatchFault1SealedSurfaceFramework = pck.createSealedSurfaceFrameworkRepresentation(structuralOrganizationInterpretation, "df673451-d6f2-4e4d-ad86-eaaf131c458f", "Single Patch Fault1 StructuralOrg1 Interp1 Interp1 SealedSurfFrmwk");
	singlePatchFault1SealedSurfaceFramework->setOriginator("Geosiris");
	singlePatchFault1SealedSurfaceFramework->setEditor("F2I");
	f1i1triRepSinglePatch->pushBackIntoRepresentationSet(singlePatchFault1SealedSurfaceFramework);
	h1i1triRep->pushBackIntoRepresentationSet(singlePatchFault1SealedSurfaceFramework);
	h2i1triRep->pushBackIntoRepresentationSet(singlePatchFault1SealedSurfaceFramework);

	// Multipatch Fault 1
	sealedSurfaceFramework = pck.createSealedSurfaceFrameworkRepresentation(structuralOrganizationInterpretation, "c89011a9-0fd8-42cd-b992-96785ed01f6f", "StructuralOrg1 Interp1 Interp1 SealedSurfFrmwk");
	sealedSurfaceFramework->setOriginator("Geosiris");
	sealedSurfaceFramework->setEditor("F2I");
	f1i1triRep->pushBackIntoRepresentationSet(sealedSurfaceFramework);
	h1i1triRep->pushBackIntoRepresentationSet(sealedSurfaceFramework); // Top frontier of the corresponding sealedVolumeFramework
	h2i1triRep->pushBackIntoRepresentationSet(sealedSurfaceFramework); // Btm frontier of the corresponding sealedVolumeFramework
	xMinusFrontierRep = pck.createTriangulatedSetRepresentation(xMinusFrontierInterp, "0a327e2e-105c-4068-a325-a6c5e3de135f", "X Minus frontier rep");
	double xMinusFrontierRepNodes[18] = { 0, 0, 300, 0, 200, 300, 0, 0, 350, 0, 200, 350, 0, 0, 500, 0, 200, 500 };
	unsigned int xMinusFrontierRepTriangles[12] = { 0, 1, 2, 1, 3, 2, 2,3,4, 3,5,4 };
	xMinusFrontierRep->pushBackTrianglePatch(6, xMinusFrontierRepNodes, 4, xMinusFrontierRepTriangles, hdfProxy);
	xMinusFrontierRep->pushBackIntoRepresentationSet(sealedSurfaceFramework);
	xPlusFrontierRep = pck.createTriangulatedSetRepresentation(xPlusFrontierInterp, "6e678338-3b53-49b6-8801-faee493e0c42", "X Plus frontier rep");
	double xPlusFrontierRepRepNodes[18] = { 700, 0, 350, 700, 200, 350, 700, 0, 500, 700, 200, 500, 700, 0, 550, 700, 200, 550 };
	unsigned int xPlusFrontierRepRepTriangles[12] = { 0, 1, 2, 1, 3, 2, 2,3,4, 3,5,4 };
	xPlusFrontierRep->pushBackTrianglePatch(6, xPlusFrontierRepRepNodes, 4, xPlusFrontierRepRepTriangles, hdfProxy);
	xPlusFrontierRep->pushBackIntoRepresentationSet(sealedSurfaceFramework);
	yPlusFrontierRep = pck.createTriangulatedSetRepresentation(yPlusFrontierInterp, "e960aea8-72e2-495d-8253-60fda5620921", "Y Plus frontier rep");
	double yPlusFrontierRepNodesPatch0[18] = { 0, 200, 300, 250, 200, 300, 0, 200, 350, 300, 200, 350, 0, 200, 500, 450, 200, 500 };
	unsigned int yPlusFrontierRepTrianglesPatch0[12] = { 0,1,2, 1,3,2, 2,3,4, 3,5,4 };
	yPlusFrontierRep->pushBackTrianglePatch(6, yPlusFrontierRepNodesPatch0, 4, yPlusFrontierRepTrianglesPatch0, hdfProxy);
	double yPlusFrontierRepNodesPatch1[18] = { 300, 200, 350, 700, 200, 350, 450, 200, 500, 700, 200, 500, 500, 200, 550, 700, 200, 550 };
	unsigned int yPlusFrontierRepTrianglesPatch1[12] = { 6,7,8, 7,9,8, 8,9,10, 9,11,10 };
	yPlusFrontierRep->pushBackTrianglePatch(6, yPlusFrontierRepNodesPatch1, 4, yPlusFrontierRepTrianglesPatch1, hdfProxy);
	yPlusFrontierRep->pushBackIntoRepresentationSet(sealedSurfaceFramework);
	yMinusFrontierRep = pck.createTriangulatedSetRepresentation(yMinusFrontierInterp, "38f64a1c-356f-4d30-a9ce-4cd3b8d6ec40", "Y Minus frontier rep");
	double yMinusFrontierRepNodesPatch0[18] = { 0, 0, 300, 250, 0, 300, 0, 0, 350, 300, 0, 350, 0, 0, 500, 450, 0, 500 };
	unsigned int yMinusFrontierRepTrianglesPatch0[12] = { 0,1,2, 1,3,2, 2,3,4, 3,5,4 };
	yMinusFrontierRep->pushBackTrianglePatch(6, yMinusFrontierRepNodesPatch0, 4, yMinusFrontierRepTrianglesPatch0, hdfProxy);
	double yMinusFrontierRepNodesPatch1[18] = { 300, 0, 350, 700, 0, 350, 450, 0, 500, 700, 0, 500, 500, 0, 550, 700, 0, 550 };
	unsigned int yMinusFrontierRepTrianglesPatch1[12] = { 6,7,8, 7,9,8, 8,9,10, 9,11,10 };
	yMinusFrontierRep->pushBackTrianglePatch(6, yMinusFrontierRepNodesPatch1, 4, yMinusFrontierRepTrianglesPatch1, hdfProxy);
	yMinusFrontierRep->pushBackIntoRepresentationSet(sealedSurfaceFramework);

	// =========================================================================
	// =========================================================================
	// Binary contact representations

	// ===================================
	// Single Patch Fault 1 Representation

	// Contact 0
	// nbPatch * nbIdenticalNodes = 9
	//int contactIdenticalNodes[9] = {
	//	0, 0, 0,
	//	1, 1, 1,
	//	2, 2, 2
	//};
	//sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml__IdentityKind__COLOCATION, 3, 3, contactIdenticalNodes, hdfProxy);
	singlePatchFault1SealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);

	// Contact 0 Patch 0
	int indexSetContact0Patch0[3] = { 3, 4, 5 };
	singlePatchFault1SealedSurfaceFramework->pushBackContactPatch(
		0,
		indexSetContact0Patch0,
		3,
		f1i1triRepSinglePatch, hdfProxy);

	// Contact 0 Patch 1
	int indexSetContact0Patch1[3] = { 0, 1, 2 };
	singlePatchFault1SealedSurfaceFramework->pushBackContactPatch(
		0,
		indexSetContact0Patch1,
		3,
		h1i1triRep, hdfProxy);

	// Contact 0 Patch 2
	int indexSetContact0Patch2[3] = { 3, 4, 5 };
	singlePatchFault1SealedSurfaceFramework->pushBackContactPatch(
		0,
		indexSetContact0Patch2,
		3,
		f1i1triRepSinglePatch, hdfProxy);

	// Contact 1
	//sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml__IdentityKind__COLOCATION, 3, 3, contactIdenticalNodes, hdfProxy);
	singlePatchFault1SealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);

	// Contact 1 Patch 0
	int indexSetContact1Patch0[3] = { 6, 7, 8 };
	singlePatchFault1SealedSurfaceFramework->pushBackContactPatch(
		1,
		indexSetContact1Patch0,
		3,
		f1i1triRepSinglePatch, hdfProxy);

	// Contact 1 Patch 1
	int indexSetContact1Patch1[3] = { 5, 6, 7 };
	singlePatchFault1SealedSurfaceFramework->pushBackContactPatch(
		1,
		indexSetContact1Patch1,
		3,
		h1i1triRep, hdfProxy);

	// Contact 1 Patch 2
	int indexSetContact1Patch2[3] = { 6, 7, 8 };
	singlePatchFault1SealedSurfaceFramework->pushBackContactPatch(
		1,
		indexSetContact1Patch2,
		3,
		f1i1triRepSinglePatch, hdfProxy);

	// Contact 2
	//sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml__IdentityKind__COLOCATION, 3, 3, contactIdenticalNodes, hdfProxy);
	singlePatchFault1SealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);

	// Contact 2 Patch 0
	int indexSetContact2Patch0[3] = { 9, 10, 11 };
	singlePatchFault1SealedSurfaceFramework->pushBackContactPatch(
		2,
		indexSetContact2Patch0,
		3,
		f1i1triRepSinglePatch, hdfProxy);

	// Contact 2 Patch 1
	int indexSetContact2Patch1[3] = { 0, 1, 2 };
	singlePatchFault1SealedSurfaceFramework->pushBackContactPatch(
		2,
		indexSetContact2Patch1,
		3,
		h2i1triRep, hdfProxy);

	// Contact 2 Patch 2
	int indexSetContact2Patch2[3] = { 9, 10, 11 };
	singlePatchFault1SealedSurfaceFramework->pushBackContactPatch(
		2,
		indexSetContact2Patch2,
		3,
		f1i1triRepSinglePatch, hdfProxy);

	// Contact 3
	//sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml__IdentityKind__COLOCATION, 3, 3, contactIdenticalNodes, hdfProxy);
	singlePatchFault1SealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);

	// Contact 3 Patch 0
	int indexSetContact3Patch0[3] = { 12, 13, 14 };
	singlePatchFault1SealedSurfaceFramework->pushBackContactPatch(
		3,
		indexSetContact3Patch0,
		3,
		f1i1triRepSinglePatch, hdfProxy);

	// Contact 3 Patch 1
	int indexSetContact3Patch1[3] = { 5, 6, 7 };
	singlePatchFault1SealedSurfaceFramework->pushBackContactPatch(
		3,
		indexSetContact3Patch1,
		3,
		h2i1triRep, hdfProxy);

	// Contact 3 Patch 2
	int indexSetContact3Patch2[3] = { 12, 13, 14 };
	singlePatchFault1SealedSurfaceFramework->pushBackContactPatch(
		3,
		indexSetContact3Patch2,
		3,
		f1i1triRepSinglePatch, hdfProxy);

	// ================================
	// Multiatch Fault 1 Representation

	// Contact 0
	// nbPatch * nbIdenticalNodes = 9
	//    int contactIdenticalNodes[9] = {
	//        0,0,0,
	//        1,1,1,
	//        2,2,2
	//    };
	//sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml__IdentityKind__COLOCATION, 3, 3, contactIdenticalNodes, hdfProxy);
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);

	// Contact 0 Patch 0
	//int * indexSetContact0Patch0 = new int[3];
	indexSetContact0Patch0[0] = 3;
	indexSetContact0Patch0[1] = 4;
	indexSetContact0Patch0[2] = 5;
	sealedSurfaceFramework->pushBackContactPatch(
		0,
		indexSetContact0Patch0,
		3,
		f1i1triRep, hdfProxy);

	// Contact 0 Patch 1
	//int * indexSetContact0Patch1 = new int[3];
	indexSetContact0Patch1[0] = 0;
	indexSetContact0Patch1[1] = 1;
	indexSetContact0Patch1[2] = 2;
	sealedSurfaceFramework->pushBackContactPatch(
		0,
		indexSetContact0Patch1,
		3,
		h1i1triRep, hdfProxy);

	// Contact 0 Patch 2
	//int * indexSetContact0Patch2 = new int[3];
	indexSetContact0Patch2[0] = 6;
	indexSetContact0Patch2[1] = 7;
	indexSetContact0Patch2[2] = 8;
	sealedSurfaceFramework->pushBackContactPatch(
		0,
		indexSetContact0Patch2,
		3,
		f1i1triRep, hdfProxy);

	// Contact 1
	//sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml__IdentityKind__COLOCATION, 3, 3, contactIdenticalNodes, hdfProxy);
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);

	// Contact 1 Patch 0
	//int * indexSetContact1Patch0 = new int[3];
	indexSetContact1Patch0[0] = 9;
	indexSetContact1Patch0[1] = 10;
	indexSetContact1Patch0[2] = 11;
	sealedSurfaceFramework->pushBackContactPatch(
		1,
		indexSetContact1Patch0,
		3,
		f1i1triRep, hdfProxy);

	// Contact 1 Patch 1
	//int * indexSetContact1Patch1 = new int[3];
	indexSetContact1Patch1[0] = 5;
	indexSetContact1Patch1[1] = 6;
	indexSetContact1Patch1[2] = 7;
	sealedSurfaceFramework->pushBackContactPatch(
		1,
		indexSetContact1Patch1,
		3,
		h1i1triRep, hdfProxy);

	// Contact 1 Patch 2
	//int * indexSetContact1Patch2 = new int[3];
	indexSetContact1Patch2[0] = 12;
	indexSetContact1Patch2[1] = 13;
	indexSetContact1Patch2[2] = 14;
	sealedSurfaceFramework->pushBackContactPatch(
		1,
		indexSetContact1Patch2,
		3,
		f1i1triRep, hdfProxy);

	// Contact 2
	//sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml__IdentityKind__COLOCATION, 3, 3, contactIdenticalNodes, hdfProxy);
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);

	// Contact 2 Patch 0
	//int * indexSetContact2Patch0 = new int[3];
	indexSetContact2Patch0[0] = 15;
	indexSetContact2Patch0[1] = 16;
	indexSetContact2Patch0[2] = 17;
	sealedSurfaceFramework->pushBackContactPatch(
		2,
		indexSetContact2Patch0,
		3,
		f1i1triRep, hdfProxy);

	// Contact 2 Patch 1
	//int * indexSetContact2Patch1 = new int[3];
	indexSetContact2Patch1[0] = 0;
	indexSetContact2Patch1[1] = 1;
	indexSetContact2Patch1[2] = 2;
	sealedSurfaceFramework->pushBackContactPatch(
		2,
		indexSetContact2Patch1,
		3,
		h2i1triRep, hdfProxy);

	// Contact 2 Patch 2
	//int * indexSetContact2Patch2 = new int[3];
	indexSetContact2Patch2[0] = 18;
	indexSetContact2Patch2[1] = 19;
	indexSetContact2Patch2[2] = 20;
	sealedSurfaceFramework->pushBackContactPatch(
		2,
		indexSetContact2Patch2,
		3,
		f1i1triRep, hdfProxy);

	// Contact 3
	//sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml__IdentityKind__COLOCATION, 3, 3, contactIdenticalNodes, hdfProxy);
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);

	// Contact 3 Patch 0
	//int * indexSetContact3Patch0 = new int[3];
	indexSetContact3Patch0[0] = 21;
	indexSetContact3Patch0[1] = 22;
	indexSetContact3Patch0[2] = 23;
	sealedSurfaceFramework->pushBackContactPatch(
		3,
		indexSetContact3Patch0,
		3,
		f1i1triRep, hdfProxy);

	// Contact 3 Patch 1
	//int * indexSetContact3Patch1 = new int[3];
	indexSetContact3Patch1[0] = 5;
	indexSetContact3Patch1[1] = 6;
	indexSetContact3Patch1[2] = 7;
	sealedSurfaceFramework->pushBackContactPatch(
		3,
		indexSetContact3Patch1,
		3,
		h2i1triRep, hdfProxy);

	// Contact 3 Patch 2
	//int * indexSetContact3Patch2 = new int[3];
	indexSetContact3Patch2[0] = 24;
	indexSetContact3Patch2[1] = 25;
	indexSetContact3Patch2[2] = 26;
	sealedSurfaceFramework->pushBackContactPatch(
		3,
		indexSetContact3Patch2,
		3,
		f1i1triRep, hdfProxy);

	// Contact 4: horizon1Interp1 STOPS AT yMinusFrontierInterp
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	int twoIndicesContact[2] = { 3, 0 };
	sealedSurfaceFramework->pushBackContactPatch(4, twoIndicesContact, 2, h1i1triRep, hdfProxy);
	twoIndicesContact[0] = 0;
	twoIndicesContact[1] = 1;
	sealedSurfaceFramework->pushBackContactPatch(4, twoIndicesContact, 2, yMinusFrontierRep, hdfProxy);
	// Contact 5: fault1Interp1 STOPS AT yMinusFrontierInterp (part above horizon1Interp1)
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	twoIndicesContact[0] = 6;
	twoIndicesContact[1] = 9;
	sealedSurfaceFramework->pushBackContactPatch(5, twoIndicesContact, 2, f1i1triRep, hdfProxy);
	twoIndicesContact[0] = 1;
	twoIndicesContact[1] = 3;
	sealedSurfaceFramework->pushBackContactPatch(5, twoIndicesContact, 2, yMinusFrontierRep, hdfProxy);
	// Contact 6: horizon2Interp1 STOPS AT yMinusFrontierInterp
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	twoIndicesContact[0] = 3;
	twoIndicesContact[1] = 0;
	sealedSurfaceFramework->pushBackContactPatch(6, twoIndicesContact, 2, h2i1triRep, hdfProxy);
	twoIndicesContact[0] = 4;
	twoIndicesContact[1] = 5;
	sealedSurfaceFramework->pushBackContactPatch(6, twoIndicesContact, 2, yMinusFrontierRep, hdfProxy);

	// Contact 7: horizon1Interp1 STOPS AT yPlusFrontierInterp
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	twoIndicesContact[0] = 4;
	twoIndicesContact[1] = 2;
	sealedSurfaceFramework->pushBackContactPatch(7, twoIndicesContact, 2, h1i1triRep, hdfProxy);
	twoIndicesContact[0] = 0;
	twoIndicesContact[1] = 1;
	sealedSurfaceFramework->pushBackContactPatch(7, twoIndicesContact, 2, yPlusFrontierRep, hdfProxy);
	// Contact 8: fault1Interp1 STOPS AT yPlusFrontierInterp (part above horizon1Interp1)
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	twoIndicesContact[0] = 8;
	twoIndicesContact[1] = 11;
	sealedSurfaceFramework->pushBackContactPatch(8, twoIndicesContact, 2, f1i1triRep, hdfProxy);
	twoIndicesContact[0] = 1;
	twoIndicesContact[1] = 3;
	sealedSurfaceFramework->pushBackContactPatch(8, twoIndicesContact, 2, yPlusFrontierRep, hdfProxy);
	// Contact 9: horizon2Interp1 STOPS AT yPlusFrontierInterp
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	twoIndicesContact[0] = 4;
	twoIndicesContact[1] = 2;
	sealedSurfaceFramework->pushBackContactPatch(9, twoIndicesContact, 2, h2i1triRep, hdfProxy);
	twoIndicesContact[0] = 4;
	twoIndicesContact[1] = 5;
	sealedSurfaceFramework->pushBackContactPatch(9, twoIndicesContact, 2, yPlusFrontierRep, hdfProxy);

	// Contact 10: horizon1Interp1 STOPS AT xMinusFrontierInterp
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	twoIndicesContact[0] = 3;
	twoIndicesContact[1] = 4;
	sealedSurfaceFramework->pushBackContactPatch(10, twoIndicesContact, 2, h1i1triRep, hdfProxy);
	twoIndicesContact[0] = 0;
	twoIndicesContact[1] = 1;
	sealedSurfaceFramework->pushBackContactPatch(10, twoIndicesContact, 2, xMinusFrontierRep, hdfProxy);
	// Contact 11: horizon2Interp1 STOPS AT xMinusFrontierInterp
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	twoIndicesContact[0] = 3;
	twoIndicesContact[1] = 4;
	sealedSurfaceFramework->pushBackContactPatch(11, twoIndicesContact, 2, h2i1triRep, hdfProxy);
	twoIndicesContact[0] = 4;
	twoIndicesContact[1] = 5;
	sealedSurfaceFramework->pushBackContactPatch(11, twoIndicesContact, 2, xMinusFrontierRep, hdfProxy);
	// Contact 12: xMinusFrontierInterp STOPS AT yMinusFrontierInterp
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	int threeIndicesContact[3] = { 0,2,4 };
	sealedSurfaceFramework->pushBackContactPatch(12, threeIndicesContact, 2, yMinusFrontierRep, hdfProxy);
	threeIndicesContact[0] = 0;
	threeIndicesContact[1] = 2;
	threeIndicesContact[2] = 4;
	sealedSurfaceFramework->pushBackContactPatch(12, threeIndicesContact, 2, xMinusFrontierRep, hdfProxy);
	// Contact 13: xMinusFrontierInterp STOPS AT yPlusFrontierInterp
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	threeIndicesContact[0] = 0;
	threeIndicesContact[1] = 2;
	threeIndicesContact[2] = 4;
	sealedSurfaceFramework->pushBackContactPatch(13, threeIndicesContact, 2, yPlusFrontierRep, hdfProxy);
	threeIndicesContact[0] = 1;
	threeIndicesContact[1] = 3;
	threeIndicesContact[2] = 5;
	sealedSurfaceFramework->pushBackContactPatch(13, threeIndicesContact, 2, xMinusFrontierRep, hdfProxy);

	// Contact 14: fault1Interp1 STOPS AT yMinusFrontierInterp (part below horizon1Interp1)
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	twoIndicesContact[0] = 12;
	twoIndicesContact[1] = 15;
	sealedSurfaceFramework->pushBackContactPatch(14, twoIndicesContact, 2, f1i1triRep, hdfProxy);
	twoIndicesContact[0] = 3;
	twoIndicesContact[1] = 5;
	sealedSurfaceFramework->pushBackContactPatch(14, twoIndicesContact, 2, yMinusFrontierRep, hdfProxy);
	twoIndicesContact[0] = 6;
	twoIndicesContact[1] = 8;
	sealedSurfaceFramework->pushBackContactPatch(14, twoIndicesContact, 2, yMinusFrontierRep, hdfProxy);
	// Contact 15: fault1Interp1 STOPS AT yPlusFrontierInterp (part above horizon1Interp1)
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	twoIndicesContact[0] = 14;
	twoIndicesContact[1] = 17;
	sealedSurfaceFramework->pushBackContactPatch(15, twoIndicesContact, 2, f1i1triRep, hdfProxy);
	twoIndicesContact[0] = 3;
	twoIndicesContact[1] = 5;
	sealedSurfaceFramework->pushBackContactPatch(15, twoIndicesContact, 2, yPlusFrontierRep, hdfProxy);
	twoIndicesContact[0] = 6;
	twoIndicesContact[1] = 8;
	sealedSurfaceFramework->pushBackContactPatch(15, twoIndicesContact, 2, yPlusFrontierRep, hdfProxy);

	// Contact 16: horizon1Interp1 STOPS AT yMinusFrontierInterp
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	twoIndicesContact[0] = 5;
	twoIndicesContact[1] = 8;
	sealedSurfaceFramework->pushBackContactPatch(16, twoIndicesContact, 2, h1i1triRep, hdfProxy);
	twoIndicesContact[0] = 6;
	twoIndicesContact[1] = 7;
	sealedSurfaceFramework->pushBackContactPatch(16, twoIndicesContact, 2, yMinusFrontierRep, hdfProxy);
	// Contact 17: fault1Interp1 STOPS AT yMinusFrontierInterp (part below horizon2Interp1)
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	twoIndicesContact[0] = 18;
	twoIndicesContact[1] = 21;
	sealedSurfaceFramework->pushBackContactPatch(17, twoIndicesContact, 2, f1i1triRep, hdfProxy);
	twoIndicesContact[0] = 8;
	twoIndicesContact[1] = 10;
	sealedSurfaceFramework->pushBackContactPatch(17, twoIndicesContact, 2, yMinusFrontierRep, hdfProxy);
	// Contact 18: horizon2Interp1 STOPS AT yMinusFrontierInterp
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	twoIndicesContact[0] = 5;
	twoIndicesContact[1] = 8;
	sealedSurfaceFramework->pushBackContactPatch(18, twoIndicesContact, 2, h2i1triRep, hdfProxy);
	twoIndicesContact[0] = 10;
	twoIndicesContact[1] = 11;
	sealedSurfaceFramework->pushBackContactPatch(18, twoIndicesContact, 2, yMinusFrontierRep, hdfProxy);

	// Contact 19: horizon1Interp1 STOPS AT yPlusFrontierInterp
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	twoIndicesContact[0] = 7;
	twoIndicesContact[1] = 9;
	sealedSurfaceFramework->pushBackContactPatch(19, twoIndicesContact, 2, h1i1triRep, hdfProxy);
	twoIndicesContact[0] = 6;
	twoIndicesContact[1] = 7;
	sealedSurfaceFramework->pushBackContactPatch(19, twoIndicesContact, 2, yPlusFrontierRep, hdfProxy);
	// Contact 20: fault1Interp1 STOPS AT yPlusFrontierInterp (part below horizon2Interp1)
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	twoIndicesContact[0] = 20;
	twoIndicesContact[1] = 23;
	sealedSurfaceFramework->pushBackContactPatch(20, twoIndicesContact, 2, f1i1triRep, hdfProxy);
	twoIndicesContact[0] = 8;
	twoIndicesContact[1] = 10;
	sealedSurfaceFramework->pushBackContactPatch(20, twoIndicesContact, 2, yPlusFrontierRep, hdfProxy);
	// Contact 21: horizon2Interp1 STOPS AT yPlusFrontierInterp
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	twoIndicesContact[0] = 7;
	twoIndicesContact[1] = 9;
	sealedSurfaceFramework->pushBackContactPatch(21, twoIndicesContact, 2, h2i1triRep, hdfProxy);
	twoIndicesContact[0] = 10;
	twoIndicesContact[1] = 11;
	sealedSurfaceFramework->pushBackContactPatch(21, twoIndicesContact, 2, yPlusFrontierRep, hdfProxy);

	// Contact 22: horizon1Interp1 STOPS AT xPlusFrontierInterp
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	twoIndicesContact[0] = 8;
	twoIndicesContact[1] = 9;
	sealedSurfaceFramework->pushBackContactPatch(22, twoIndicesContact, 2, h1i1triRep, hdfProxy);
	twoIndicesContact[0] = 0;
	twoIndicesContact[1] = 1;
	sealedSurfaceFramework->pushBackContactPatch(22, twoIndicesContact, 2, xPlusFrontierRep, hdfProxy);
	// Contact 23: horizon2Interp1 STOPS AT xPlusFrontierInterp
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	twoIndicesContact[0] = 8;
	twoIndicesContact[1] = 9;
	sealedSurfaceFramework->pushBackContactPatch(23, twoIndicesContact, 2, h2i1triRep, hdfProxy);
	twoIndicesContact[0] = 4;
	twoIndicesContact[1] = 5;
	sealedSurfaceFramework->pushBackContactPatch(23, twoIndicesContact, 2, xPlusFrontierRep, hdfProxy);
	// Contact 24: xPlusFrontierInterp STOPS AT yMinusFrontierInterp
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	threeIndicesContact[0] = 7;
	threeIndicesContact[1] = 9;
	threeIndicesContact[2] = 11;
	sealedSurfaceFramework->pushBackContactPatch(24, threeIndicesContact, 2, yMinusFrontierRep, hdfProxy);
	threeIndicesContact[0] = 0;
	threeIndicesContact[1] = 2;
	threeIndicesContact[2] = 4;
	sealedSurfaceFramework->pushBackContactPatch(24, threeIndicesContact, 2, xPlusFrontierRep, hdfProxy);
	// Contact 25: xPlusFrontierInterp STOPS AT yPlusFrontierInterp
	sealedSurfaceFramework->pushBackContact(gsoap_resqml2_0_1::resqml20__IdentityKind::colocation);
	threeIndicesContact[0] = 7;
	threeIndicesContact[1] = 9;
	threeIndicesContact[2] = 11;
	sealedSurfaceFramework->pushBackContactPatch(25, threeIndicesContact, 2, yPlusFrontierRep, hdfProxy);
	threeIndicesContact[0] = 1;
	threeIndicesContact[1] = 3;
	threeIndicesContact[2] = 5;
	sealedSurfaceFramework->pushBackContactPatch(25, threeIndicesContact, 2, xPlusFrontierRep, hdfProxy);

	// =========================================================================
	// =========================================================================
	// Contact identities

	// ====================
	// Single Patch Fault 1

	// Contact 0 and 1 was previously colocated
	int contact_0_1_contactRepresentations[2] = { 0, 1 };
	//    int contact_0_1_IdenticalNodes[6] =
	//    {
	//        0, 0,
	//        1, 1,
	//        2, 2,
	//    };
	//    sealedSurfaceFramework->pushBackContactIdentity(
	//            gsoap_resqml2_0_1::resqml__IdentityKind__PREVIOUS_USCORECOLOCATION,
	//            2, contact_0_1_contactRepresentations,
	//            3, contact_0_1_IdenticalNodes, hdfProxy);
	singlePatchFault1SealedSurfaceFramework->pushBackContactIdentity(
		gsoap_resqml2_0_1::resqml20__IdentityKind::previous_x0020colocation,
		2, contact_0_1_contactRepresentations,
		hdfProxy);

	// Contact 2 and 3 was previously colocated
	int contact_2_3_contactRepresentations[2] = { 2, 3 };
	//    int contact_2_3_IdenticalNodes[6] =
	//    {
	//        0, 0,
	//        1, 1,
	//        2, 2,
	//    };
	//    sealedSurfaceFramework->pushBackContactIdentity(
	//            gsoap_resqml2_0_1::resqml__IdentityKind__PREVIOUS_USCORECOLOCATION,
	//            2, contact_2_3_contactRepresentations,
	//            3, contact_2_3_IdenticalNodes, hdfProxy);
	singlePatchFault1SealedSurfaceFramework->pushBackContactIdentity(
		gsoap_resqml2_0_1::resqml20__IdentityKind::previous_x0020colocation,
		2, contact_2_3_contactRepresentations,
		hdfProxy);

	// ==================
	// Multipatch Fault 1

	// Contact 0 and 1 was previously colocated
	//int * contact_0_1_contactRepresentations = new int[2];
	//contact_0_1_contactRepresentations[0] = 0;
	//contact_0_1_contactRepresentations[1] = 1;
	//    int contact_0_1_IdenticalNodes[6] =
	//    {
	//        0, 0,
	//        1, 1,
	//        2, 2,
	//    };
	//    sealedSurfaceFramework->pushBackContactIdentity(
	//            gsoap_resqml2_0_1::resqml__IdentityKind__PREVIOUS_USCORECOLOCATION,
	//            2, contact_0_1_contactRepresentations,
	//            3, contact_0_1_IdenticalNodes, hdfProxy);
	sealedSurfaceFramework->pushBackContactIdentity(
		gsoap_resqml2_0_1::resqml20__IdentityKind::previous_x0020colocation,
		2, contact_0_1_contactRepresentations,
		hdfProxy);

	// Contact 2 and 3 was previously colocated
	//int * contact_2_3_contactRepresentations = new int[2];
	//contact_2_3_contactRepresentations[0] = 2;
	//contact_2_3_contactRepresentations[1] = 3;
	//    int contact_2_3_IdenticalNodes[6] =
	//    {
	//        0, 0,
	//        1, 1,
	//        2, 2,
	//    };
	//    sealedSurfaceFramework->pushBackContactIdentity(
	//            gsoap_resqml2_0_1::resqml__IdentityKind__PREVIOUS_USCORECOLOCATION,
	//            2, contact_2_3_contactRepresentations,
	//            3, contact_2_3_IdenticalNodes, hdfProxy);
	sealedSurfaceFramework->pushBackContactIdentity(
		gsoap_resqml2_0_1::resqml20__IdentityKind::previous_x0020colocation,
		2, contact_2_3_contactRepresentations,
		hdfProxy);
}

void serializeActivities(COMMON_NS::DataObjectRepository * epcDoc)
{
	/********************
	* Activity Template
	********************/

	EML2_NS::ActivityTemplate* genericCreationActivityTemplate = epcDoc->createActivityTemplate("a41c63bf-78cb-454b-8018-c9df060c5cf3", "GenericCreationActivity");
	genericCreationActivityTemplate->pushBackParameter("CreationInput", true, false, 0, -1);
	genericCreationActivityTemplate->pushBackParameter("CreationOutput", false, true, 1, -1);

	/********************
	* Activities
	********************/
	EML2_NS::Activity* pickingActivity = epcDoc->createActivity(genericCreationActivityTemplate, "", "Seismic picking");
	pickingActivity->pushBackParameter("CreationOutput", horizon1);
	pickingActivity->pushBackParameter("CreationOutput", horizon1Interp1);
	pickingActivity->pushBackParameter("CreationOutput", h1i1SingleGrid2dRep);
	pickingActivity->pushBackParameter("CreationOutput", fault1);
	pickingActivity->pushBackParameter("CreationOutput", fault1Interp1);
	pickingActivity->pushBackParameter("CreationOutput", f1i1PolyLineRep);

	EML2_NS::Activity* h1triangulationActivity = epcDoc->createActivity(genericCreationActivityTemplate, "", "Triangulation");
	h1triangulationActivity->pushBackParameter("CreationInput", h1i1SingleGrid2dRep);
	h1triangulationActivity->pushBackParameter("CreationOutput", h1i1triRep);

	EML2_NS::Activity* f1TriangulationActivity1 = epcDoc->createActivity(genericCreationActivityTemplate, "", "Triangulation");
	f1TriangulationActivity1->pushBackParameter("CreationInput", f1i1PolyLineRep);
	f1TriangulationActivity1->pushBackParameter("CreationOutput", f1i1triRepSinglePatch);

	EML2_NS::Activity* f1TriangulationActivity2 = epcDoc->createActivity(genericCreationActivityTemplate, "", "Triangulation");
	f1TriangulationActivity2->pushBackParameter("CreationInput", f1i1PolyLineRep);
	f1TriangulationActivity2->pushBackParameter("CreationOutput", f1i1triRep);

}

void serializeRockFluidOrganization(COMMON_NS::DataObjectRepository & pck, EML2_NS::AbstractHdfProxy*)
{
	// Feature level
	RESQML2_NS::BoundaryFeature* gasOilContactFeature = nullptr;
	RESQML2_NS::BoundaryFeature* waterOilContactFeature = nullptr;
	RESQML2_NS::RockVolumeFeature* gasCapFeature = nullptr;
	RESQML2_NS::RockVolumeFeature* oilColumnFeature = nullptr;
	RESQML2_NS::RockVolumeFeature* aquiferFeature = nullptr;
	if (pck.getDefaultResqmlVersion() == COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_0_1) {
		gasOilContactFeature = pck.createFluidBoundaryFeature("cd400fa2-4c8b-11e9-be79-3f8079258eaa", "Gas Oil Contact Feature", gsoap_resqml2_0_1::resqml20__FluidContact::gas_x0020oil_x0020contact);
		waterOilContactFeature = pck.createFluidBoundaryFeature("d332b298-4c8b-11e9-80d8-c760b2e2530d", "Water Oil Contact Feature", gsoap_resqml2_0_1::resqml20__FluidContact::water_x0020oil_x0020contact);
		gasCapFeature = pck.createRockFluidUnit("18a714da-4bf2-11e9-a17e-e74cb7f87d2a", "Gas Cap Feature", gsoap_resqml2_0_1::resqml20__Phase::gas_x0020cap,
			pck.createPartial<RESQML2_0_1_NS::FluidBoundaryFeature>("", ""),
			static_cast<RESQML2_0_1_NS::FluidBoundaryFeature*>(gasOilContactFeature));
		oilColumnFeature = pck.createRockFluidUnit("7e7180c4-39df-42be-9ab4-03b054fd8d47", "Oil Column Feature", gsoap_resqml2_0_1::resqml20__Phase::oil_x0020column,
			static_cast<RESQML2_0_1_NS::FluidBoundaryFeature*>(gasOilContactFeature),
			static_cast<RESQML2_0_1_NS::FluidBoundaryFeature*>(waterOilContactFeature));
		aquiferFeature = pck.createRockFluidUnit("ade43494-9e45-4497-9220-d0f82d1a1f56", "Aquifer Feature", gsoap_resqml2_0_1::resqml20__Phase::aquifer,
			static_cast<RESQML2_0_1_NS::FluidBoundaryFeature*>(waterOilContactFeature),
			pck.createPartial<RESQML2_0_1_NS::FluidBoundaryFeature>("", ""));
	}
#if WITH_RESQML2_2
	else {
		gasOilContactFeature = pck.createBoundaryFeature("cd400fa2-4c8b-11e9-be79-3f8079258eaa", "Gas Oil Contact Feature");
		waterOilContactFeature = pck.createBoundaryFeature("d332b298-4c8b-11e9-80d8-c760b2e2530d", "Water Oil Contact Feature");
		gasCapFeature = pck.createRockVolumeFeature("18a714da-4bf2-11e9-a17e-e74cb7f87d2a", "Gas Cap Feature");
		oilColumnFeature = pck.createRockVolumeFeature("7e7180c4-39df-42be-9ab4-03b054fd8d47", "Oil Column Feature");
		aquiferFeature = pck.createRockVolumeFeature("ade43494-9e45-4497-9220-d0f82d1a1f56", "Aquifer Feature");
	}
#endif

	// Interpretation level
	gasCapInterp = pck.createRockFluidUnitInterpretation(gasCapFeature, "4b73172a-4bf1-11e9-a9f6-9b2813cc56e1", "Gas Cap Interp");
	gasCapInterp->setPhase(gsoap_eml2_3::resqml22__Phase::gas_x0020cap);
	oilColumnInterp = pck.createRockFluidUnitInterpretation(oilColumnFeature, "2491fbe5-bbaf-43f5-906e-6d8cbf033890", "Oil Column Interp");
	gasCapInterp->setPhase(gsoap_eml2_3::resqml22__Phase::oil_x0020column);
	aquiferInterp = pck.createRockFluidUnitInterpretation(aquiferFeature, "d2477e2e-8c50-4605-a80d-619e74e20f03", "Aquifer Interp");
	gasCapInterp->setPhase(gsoap_eml2_3::resqml22__Phase::aquifer);

	// Gas Oil Contact interp
	RESQML2_NS::AbstractFeatureInterpretation* gasOilContactInterp = nullptr;
	if (pck.getDefaultResqmlVersion() == COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_0_1) {
		gasOilContactInterp = pck.createGenericFeatureInterpretation(gasOilContactFeature, "0ab8f2f4-4c96-11e9-999e-c3449b44fef5", "Gas Oil Contact interp");
	}
#if WITH_RESQML2_2
	else {
		gasOilContactInterp = pck.createFluidBoundaryInterpretation(gasOilContactFeature, "0ab8f2f4-4c96-11e9-999e-c3449b44fef5", "Gas Oil Contact interp", gsoap_eml2_3::resqml22__FluidContact::gas_x0020oil_x0020contact);
	}
#endif
	gasOilContactInterp->pushBackExtraMetadata("Capillary Pressure value", "0");
	gasOilContactInterp->pushBackExtraMetadata("Capillary Pressure uom", "bar");
	RESQML2_NS::PlaneSetRepresentation* gasOilContactRep = pck.createPlaneSetRepresentation(gasOilContactInterp, "ae1d618c-4c96-11e9-8f12-cf7f4da2a08d", "Gas Oil Contact Plane Rep");
	gasOilContactRep->pushBackHorizontalPlaneGeometryPatch(500);

	// Water Oil Contact interp
	RESQML2_NS::AbstractFeatureInterpretation* waterOilContactInterp = nullptr;
	if (pck.getDefaultResqmlVersion() == COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_0_1) {
		waterOilContactInterp = pck.createGenericFeatureInterpretation(waterOilContactFeature, "1371efae-4c96-11e9-bcdd-37d8112fd19e", "Water Oil Contact interp");
	}
#if WITH_RESQML2_2
	else {
		waterOilContactInterp = pck.createFluidBoundaryInterpretation(waterOilContactFeature, "1371efae-4c96-11e9-bcdd-37d8112fd19e", "Water Oil Contact interp", gsoap_eml2_3::resqml22__FluidContact::water_x0020oil_x0020contact);
	}
#endif
	waterOilContactInterp->pushBackExtraMetadata("Capillary Pressure value", "0");
	waterOilContactInterp->pushBackExtraMetadata("Capillary Pressure uom", "bar");
	RESQML2_NS::PlaneSetRepresentation* waterOilContactRep = pck.createPlaneSetRepresentation(waterOilContactInterp, "b54cc3b2-4c96-11e9-b33d-ef2c41476266", "Water Oil Contact Plane Rep");
	waterOilContactRep->pushBackHorizontalPlaneGeometryPatch(3200);

	// Assemble all fluid units and fluid boundaries together in a model
	RESQML2_NS::Model* rockFluidOrgFeature = pck.createRockFluidModel("311587dd-7abc-425b-a364-908d0508ed61", "Region 1");
	rockFluidOrgInterp = pck.createRockFluidOrganizationInterpretation(rockFluidOrgFeature, "b5bbfe42-4a63-11e9-9eeb-4f036e6e8141", "Region 1 interp");
	rockFluidOrgInterp->pushBackExtraMetadata("Initial Pressure value", "337");
	rockFluidOrgInterp->pushBackExtraMetadata("Initial Pressure uom", "bar");
	rockFluidOrgInterp->pushBackExtraMetadata("Datum depth value", "3060");
	rockFluidOrgInterp->pushBackExtraMetadata("Datum depth uom", "m");
	rockFluidOrgInterp->pushBackRockFluidUnitInterpretation(gasCapInterp);
	rockFluidOrgInterp->pushBackRockFluidUnitInterpretation(oilColumnInterp);
	rockFluidOrgInterp->pushBackRockFluidUnitInterpretation(aquiferInterp);
	rockFluidOrgInterp->pushBackBinaryContact(gasCapInterp, gsoap_eml2_3::resqml22__ContactVerb::stops, oilColumnInterp, gasOilContactInterp);
	rockFluidOrgInterp->pushBackBinaryContact(oilColumnInterp, gsoap_eml2_3::resqml22__ContactVerb::stops, aquiferInterp, waterOilContactInterp);

	// Link between ijk grid and rock fuid org
	/*
	RESQML2_NS::IjkGridExplicitRepresentation* singleCellIjkgrid = pck.getDataObjectByUuid<RESQML2_NS::IjkGridExplicitRepresentation>("e69bfe00-fa3d-11e5-b5eb-0002a5d5c51b");
	uint64_t rockFluidUnitIndice = 0;
	singleCellIjkgrid->setCellAssociationWithRockFluidOrganizationInterpretation(&rockFluidUnitIndice, 1000, rockFluidOrgInterp);
	*/
}

PRODML2_1_NS::FluidSystem* serializeFluidSystem(COMMON_NS::DataObjectRepository & pck)
{
	PRODML2_1_NS::FluidSystem* fluidSystem = pck.createFluidSystem("e8ae6cf8-c4a4-40bf-a3c7-5bf5d0a5b1dd", "Fluid system Region 1",
		std::numeric_limits<double>::quiet_NaN(), gsoap_eml2_2::eml22__ThermodynamicTemperatureUom::degF, std::numeric_limits<double>::quiet_NaN(), gsoap_eml2_2::eml22__PressureUom::psi,
		gsoap_eml2_2::prodml21__ReservoirFluidKind::black_x0020oil, std::numeric_limits<double>::quiet_NaN(), gsoap_eml2_2::eml22__VolumePerVolumeUom::ft3_x002fbbl);

	fluidSystem->setPhasesPresent(gsoap_eml2_2::prodml21__PhasePresent::gas_x0020and_x0020oil_x0020and_x0020water);
	
	//fluidSystem->setReservoirLifeCycleState(gsoap_eml2_2::prodml21__ReservoirLifeCycleState__primary_x0020production);
	fluidSystem->setStockTankOilAPIGravity((141.5/0.8989209)-131.5, gsoap_eml2_2::eml22__APIGravityUom::dAPI);
	/*
	fluidSystem->setNaturalGasGasGravity(0.8);
	fluidSystem->setRemark("This data comes from the official PRODML PVT Eenrgistics documentation");
	*/

	fluidSystem->setRockFluidOrganization(rockFluidOrgInterp);

	return fluidSystem;
}

void serializeOilFluidCharacCharacterization(COMMON_NS::DataObjectRepository & pck, PRODML2_1_NS::FluidSystem* fluidSystem = nullptr)
{
	PRODML2_1_NS::FluidCharacterization* oilFluidCharac = pck.createFluidCharacterization("656aa27f-5373-4c7f-9469-a57890e2b5d8", "Oil Fluid Characterization");
	oilFluidCharac->setRockFluidUnit(oilColumnInterp);
	oilFluidCharac->pushBackModel();

	oilFluidCharac->pushBackParameter(0, 882, gsoap_eml2_2::eml22__UnitOfMeasure::kg_x002fm3, gsoap_eml2_2::prodml21__OutputFluidProperty::Density, gsoap_eml2_2::prodml21__ThermodynamicPhase::oleic);

	// Black Oil Variation with Depth
	oilFluidCharac->pushBackTableFormat();
	oilFluidCharac->pushBackTableFormatColumn(0, "m", "Depth from MSL");
	oilFluidCharac->pushBackTableFormatColumn(0, gsoap_eml2_2::eml22__UnitOfMeasure::bar, gsoap_eml2_2::prodml21__OutputFluidProperty::Saturation_x0020Pressure);

	oilFluidCharac->pushBackTable(0, "Black Oil Variation with Depth", std::to_string(oilFluidCharac->getTableFormatCount() - 1));
	oilFluidCharac->pushBackTableRow(0, 0, { 2600, 333.25 });
	oilFluidCharac->pushBackTableRow(0, 0, { 2638.9, 320.6866 });
	oilFluidCharac->pushBackTableRow(0, 0, { 2677.8, 309.6418 });
	oilFluidCharac->pushBackTableRow(0, 0, { 2716.7, 299.7015 });
	oilFluidCharac->pushBackTableRow(0, 0, { 2755.6, 290.8657 });
	oilFluidCharac->pushBackTableRow(0, 0, { 2794.4, 282.7201 });
	oilFluidCharac->pushBackTableRow(0, 0, { 2833.3, 275.2649 });
	oilFluidCharac->pushBackTableRow(0, 0, { 2872, 268.5 });
	oilFluidCharac->pushBackTableRow(0, 0, { 2872.2, 268.5 });
	oilFluidCharac->pushBackTableRow(0, 0, { 2911.1, 262.1493 });
	oilFluidCharac->pushBackTableRow(0, 0, { 2950, 256.2127 });

	// Saturated Oil Table
	oilFluidCharac->pushBackTableFormat();
	oilFluidCharac->pushBackTableFormatColumn(1, gsoap_eml2_2::eml22__UnitOfMeasure::bar, gsoap_eml2_2::prodml21__OutputFluidProperty::Pressure);
	oilFluidCharac->pushBackTableFormatColumn(1, gsoap_eml2_2::eml22__UnitOfMeasure::m3_x002fm3, gsoap_eml2_2::prodml21__OutputFluidProperty::Formation_x0020Volume_x0020Factor);
	oilFluidCharac->pushBackTableFormatColumn(1, gsoap_eml2_2::eml22__UnitOfMeasure::cP, gsoap_eml2_2::prodml21__OutputFluidProperty::Viscosity);
	oilFluidCharac->pushBackTableFormatColumn(1, gsoap_eml2_2::eml22__UnitOfMeasure::m3_x002fm3, gsoap_eml2_2::prodml21__OutputFluidProperty::Solution_x0020GOR);

	oilFluidCharac->pushBackTable(0, "Saturated Oil Table", std::to_string(oilFluidCharac->getTableFormatCount() - 1));
	oilFluidCharac->pushBackTableRow(0, 1, { 268.5, 1.51746, 0.464, 156.9 }, true);
	oilFluidCharac->pushBackTableRow(0, 1, { 250, 1.48274, 0.502, 143.5 }, true);
	oilFluidCharac->pushBackTableRow(0, 1, { 200, 1.39808, 0.618, 110.7 }, true);
	oilFluidCharac->pushBackTableRow(0, 1, { 150, 1.32163, 0.763, 81.5 }, true);
	oilFluidCharac->pushBackTableRow(0, 1, { 100, 1.24802, 0.953, 54.3 }, true);
	oilFluidCharac->pushBackTableRow(0, 1, { 50, 1.17014, 1.224, 27.4 }, true);

	// Undersaturated Oil Table
	oilFluidCharac->pushBackTableFormat();
	oilFluidCharac->pushBackTableFormatColumn(2, gsoap_eml2_2::eml22__UnitOfMeasure::bar, gsoap_eml2_2::prodml21__OutputFluidProperty::Saturation_x0020Pressure);
	oilFluidCharac->pushBackTableFormatColumn(2, gsoap_eml2_2::eml22__UnitOfMeasure::bar, gsoap_eml2_2::prodml21__OutputFluidProperty::Pressure);
	oilFluidCharac->pushBackTableFormatColumn(2, gsoap_eml2_2::eml22__UnitOfMeasure::m3_x002fm3, gsoap_eml2_2::prodml21__OutputFluidProperty::Formation_x0020Volume_x0020Factor);
	oilFluidCharac->pushBackTableFormatColumn(2, gsoap_eml2_2::eml22__UnitOfMeasure::cP, gsoap_eml2_2::prodml21__OutputFluidProperty::Viscosity);

	oilFluidCharac->pushBackTable(0, "Undersaturated Oil Table", std::to_string(oilFluidCharac->getTableFormatCount() - 1));
	oilFluidCharac->pushBackTableRow(0, 2, { 50, 100, 1.16296, 1.31 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 50, 150, 1.15664, 1.393 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 50, 200, 1.15103, 1.472 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 50, 250, 1.14598, 1.548 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 50, 268.5, 1.14425, 1.576 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 50, 300, 1.14143, 1.621 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 50, 350, 1.13728, 1.692 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 50, 400, 1.13349, 1.76 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 50, 450, 1.13001, 1.826 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 50, 500, 1.12679, 1.889 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 50, 550, 1.12381, 1.95 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 50, 600, 1.12103, 2.01 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 50, 650, 1.11844, 2.067 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 100, 150, 1.23902, 1.027 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 100, 200, 1.23114, 1.099 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 100, 250, 1.22415, 1.169 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 100, 268.5, 1.22175, 1.194 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 100, 300, 1.21789, 1.236 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 100, 350, 1.21225, 1.301 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 100, 400, 1.20713, 1.364 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 100, 450, 1.20245, 1.425 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 100, 500, 1.19815, 1.485 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 100, 550, 1.19419, 1.542 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 100, 600, 1.19052, 1.598 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 100, 650, 1.18712, 1.652 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 150, 200, 1.31096, 0.826 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 150, 250, 1.30163, 0.888 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 150, 268.5, 1.29846, 0.91 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 150, 300, 1.29336, 0.947 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 150, 350, 1.28597, 1.005 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 150, 400, 1.27932, 1.062 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 150, 450, 1.27328, 1.117 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 150, 500, 1.26776, 1.171 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 150, 550, 1.26271, 1.223 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 150, 600, 1.25804, 1.274 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 150, 650, 1.25373, 1.323 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 200, 250, 1.38574, 0.671 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 200, 268.5, 1.38158, 0.69 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 200, 300, 1.37494, 0.723 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 200, 350, 1.36539, 0.774 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 200, 400, 1.35685, 0.823 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 200, 450, 1.34916, 0.871 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 200, 500, 1.34218, 0.919 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 200, 550, 1.33581, 0.965 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 200, 600, 1.32997, 1.01 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 200, 650, 1.32459, 1.055 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 250, 268.5, 1.47728, 0.519 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 250, 300, 1.4686, 0.546 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 250, 350, 1.45623, 0.589 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 250, 400, 1.44528, 0.631 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 250, 450, 1.43549, 0.673 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 250, 500, 1.42667, 0.714 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 250, 550, 1.41867, 0.754 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 250, 600, 1.41136, 0.793 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 250, 650, 1.40466, 0.832 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 268.5, 300, 1.50785, 0.49 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 268.5, 350, 1.49419, 0.53 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 268.5, 400, 1.48215, 0.57 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 268.5, 450, 1.47142, 0.609 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 268.5, 500, 1.46178, 0.647 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 268.5, 550, 1.45306, 0.685 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 268.5, 600, 1.44511, 0.722 }, false);
	oilFluidCharac->pushBackTableRow(0, 2, { 268.5, 650, 1.43783, 0.758 }, false);

	if (fluidSystem != nullptr) {
		oilFluidCharac->setFluidSystem(fluidSystem);
	}
}

void serializeGasFluidCharacCharacterization(COMMON_NS::DataObjectRepository & pck, PRODML2_1_NS::FluidSystem* fluidSystem = nullptr)
{
	PRODML2_1_NS::FluidCharacterization* gasFluidCharac = pck.createFluidCharacterization("5ea0eeb2-a287-4a2e-9362-1d2491e491b2", "Gas Fluid Characterization");
	gasFluidCharac->setRockFluidUnit(gasCapInterp);
	gasFluidCharac->pushBackModel();

	// Saturated Gas Table
	gasFluidCharac->pushBackTableFormat();
	gasFluidCharac->pushBackTableFormatColumn(0, gsoap_eml2_2::eml22__UnitOfMeasure::bar, gsoap_eml2_2::prodml21__OutputFluidProperty::Pressure);
	gasFluidCharac->pushBackTableFormatColumn(0, gsoap_eml2_2::eml22__UnitOfMeasure::m3_x002fm3, gsoap_eml2_2::prodml21__OutputFluidProperty::Formation_x0020Volume_x0020Factor);
	gasFluidCharac->pushBackTableFormatColumn(0, gsoap_eml2_2::eml22__UnitOfMeasure::cP, gsoap_eml2_2::prodml21__OutputFluidProperty::Viscosity);

	gasFluidCharac->pushBackTable(0, "Saturated Gas Table", std::to_string(gasFluidCharac->getTableFormatCount() - 1));
	gasFluidCharac->pushBackTableRow(0, 0, { 350, 0.003929, 0.034856 }, true);
	gasFluidCharac->pushBackTableRow(0, 0, { 300, 0.004302, 0.031551 }, true);
	gasFluidCharac->pushBackTableRow(0, 0, { 268.5, 0.004624, 0.029292 }, true);
	gasFluidCharac->pushBackTableRow(0, 0, { 250, 0.00487, 0.027202 }, true);
	gasFluidCharac->pushBackTableRow(0, 0, { 200, 0.005876, 0.02232 }, true);
	gasFluidCharac->pushBackTableRow(0, 0, { 150, 0.007763, 0.018581 }, true);
	gasFluidCharac->pushBackTableRow(0, 0, { 100, 0.011846, 0.015991 }, true);
	gasFluidCharac->pushBackTableRow(0, 0, { 50, 0.024734, 0.014335 }, true);

	if (fluidSystem != nullptr) {
		gasFluidCharac->setFluidSystem(fluidSystem);
	}
}

void serializeWaterFluidCharacCharacterization(COMMON_NS::DataObjectRepository & pck, PRODML2_1_NS::FluidSystem* fluidSystem = nullptr)
{
	PRODML2_1_NS::FluidCharacterization* waterFluidCharac = pck.createFluidCharacterization("8bea1d3f-9599-4a45-b88c-8196aef3f397", "Water Fluid Characterization");
	waterFluidCharac->setRockFluidUnit(aquiferInterp);
	waterFluidCharac->pushBackModel();

	waterFluidCharac->pushBackParameter(0, 1101.3, gsoap_eml2_2::eml22__UnitOfMeasure::kg_x002fm3, gsoap_eml2_2::prodml21__OutputFluidProperty::Density, gsoap_eml2_2::prodml21__ThermodynamicPhase::aqueous);
	waterFluidCharac->pushBackParameter(0, 313000, gsoap_eml2_2::eml22__UnitOfMeasure::_1_x002fbar, gsoap_eml2_2::prodml21__OutputFluidProperty::Compressibility, gsoap_eml2_2::prodml21__ThermodynamicPhase::aqueous);
	waterFluidCharac->pushBackParameter(0, 0.38509, gsoap_eml2_2::eml22__UnitOfMeasure::cP, gsoap_eml2_2::prodml21__OutputFluidProperty::Viscosity, gsoap_eml2_2::prodml21__ThermodynamicPhase::aqueous);
	waterFluidCharac->pushBackParameter(0, 1.03382, gsoap_eml2_2::eml22__UnitOfMeasure::m3_x002fm3, gsoap_eml2_2::prodml21__OutputFluidProperty::Formation_x0020Volume_x0020Factor, gsoap_eml2_2::prodml21__ThermodynamicPhase::aqueous);
	waterFluidCharac->pushBackParameter(0, 978000, gsoap_eml2_2::eml22__UnitOfMeasure::_1_x002fbar, gsoap_eml2_2::prodml21__OutputFluidProperty::Viscosity_x0020Compressibility, gsoap_eml2_2::prodml21__ThermodynamicPhase::aqueous);
	waterFluidCharac->pushBackParameter(0, 268.5, gsoap_eml2_2::eml22__UnitOfMeasure::bar, gsoap_eml2_2::prodml21__OutputFluidProperty::Pressure, gsoap_eml2_2::prodml21__ThermodynamicPhase::aqueous);

	if (fluidSystem != nullptr) {
		waterFluidCharac->setFluidSystem(fluidSystem);
	}
}

void serializeTabularFluidCharacterization(COMMON_NS::DataObjectRepository & pck, PRODML2_1_NS::FluidSystem* fluidSystem = nullptr)
{
	serializeOilFluidCharacCharacterization(pck, fluidSystem);	
	serializeGasFluidCharacCharacterization(pck, fluidSystem);	
	serializeWaterFluidCharacCharacterization(pck, fluidSystem);	
}

void serializeCompositionalFluidCharacterization(COMMON_NS::DataObjectRepository & pck, PRODML2_1_NS::FluidSystem* fluidSystem = nullptr)
{
	PRODML2_1_NS::FluidCharacterization* fluidCharac = pck.createFluidCharacterization("6f5f6146-6f8b-4222-b322-9dbef1e7e4cf", "my compositional Fluid Characterization");

	fluidCharac->pushBackFormationWater("h2o");
	fluidCharac->setFormationWaterSpecificGravity(0, 1.02);
	fluidCharac->setFormationWaterSalinity(0, 80000, gsoap_eml2_2::eml22__MassPerMassUom::ppm);

	fluidCharac->pushBackPureFluidComponent("c1", gsoap_eml2_2::prodml21__PureComponentEnum::c1, false);
	fluidCharac->setPureFluidComponentMolecularWeight(0, 16.04, gsoap_eml2_2::eml22__MolecularWeightUom::g_x002fmol);

	fluidCharac->pushBackPseudoFluidComponent("c2-3", gsoap_eml2_2::prodml21__PseudoComponentEnum::c2_c4_x002bn2);
	fluidCharac->setPseudoFluidComponentStartingCarbonNumber(0, 2);
	fluidCharac->setPseudoFluidComponentEndingCarbonNumber(0, 3);

	fluidCharac->pushBackModel("0");
	fluidCharac->setFluidCharacterizationModelName(0, "F2I Good Oil No. 4 EOS Demonstration");
	fluidCharac->setFluidCharacterizationModelReferenceTemperature(0, 60, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom::degF);

	PRODML2_1_NS::PvtSpecification* spec = fluidCharac->initModelSpecification(0, PRODML2_1_NS::FluidCharacterization::SrkEos);
	PRODML2_1_NS::CompositionalSpecification* srkEosSpec = dynamic_cast<PRODML2_1_NS::CompositionalSpecification*>(spec);
	srkEosSpec->pushBackCoefficient(1, gsoap_eml2_2::prodml21__PvtModelParameterKind::a1);
	srkEosSpec->setMixingRule(gsoap_eml2_2::prodml21__MixingRule::classical);
	srkEosSpec->pushBackFluidComponentProperty("h2o");
	srkEosSpec->pushBackFluidComponentProperty("c1");
	srkEosSpec->pushBackFluidComponentProperty("c2-3");
	srkEosSpec->setFluidComponentPropertyCriticalPressure(2, 666.6, "psi");
	srkEosSpec->setFluidComponentPropertyCriticalTemperature(2, 121.9, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom::degC);
	srkEosSpec->setFluidComponentPropertyCriticalVolume(2, 2.607, gsoap_eml2_2::eml22__MolarVolumeUom::ft3_x002flbmol);
	srkEosSpec->setFluidComponentPropertyAcentricFactor(2, 0.1140);
	srkEosSpec->setFluidComponentPropertyParachor(2, 126.03);

	if (fluidSystem != nullptr)
		fluidCharac->setFluidSystem(fluidSystem);
}

void serializeTimeSeriesData(COMMON_NS::DataObjectRepository & pck)
{
	PRODML2_1_NS::TimeSeriesData* timeSeriesData = pck.createTimeSeriesData("25d2e0d8-dffa-414d-b7cd-f871cb436781", "my Time Series Data");

	timeSeriesData->pushBackKeywordValue(gsoap_eml2_2::prodml21__TimeSeriesKeyword::asset_x0020identifier, "prodml://f2i-consulting.com/manifold(HDR01)");
	timeSeriesData->pushBackKeywordValue(gsoap_eml2_2::prodml21__TimeSeriesKeyword::flow, "production");
	timeSeriesData->pushBackKeywordValue(gsoap_eml2_2::prodml21__TimeSeriesKeyword::product, "oil");
	timeSeriesData->pushBackKeywordValue(gsoap_eml2_2::prodml21__TimeSeriesKeyword::qualifier, "measured");

	timeSeriesData->setUom(gsoap_resqml2_0_1::resqml20__ResqmlUom::psi);
	timeSeriesData->setMeasureClass(gsoap_eml2_2::eml22__MeasureClass::pressure);

	timeSeriesData->pushBackDoubleValue(747.7316, 1328706000, gsoap_eml2_2::prodml21__ValueStatus::frozen);
	timeSeriesData->pushBackDoubleValue(747.7316, 1328706060, gsoap_eml2_2::prodml21__ValueStatus::frozen);
	timeSeriesData->pushBackDoubleValue(747.7316, 1328706120, gsoap_eml2_2::prodml21__ValueStatus::frozen);
	timeSeriesData->pushBackDoubleValue(747.7316, 1328706180, gsoap_eml2_2::prodml21__ValueStatus::frozen);
	timeSeriesData->pushBackDoubleValue(746.7316, 1328706241);
	timeSeriesData->pushBackDoubleValue(745.7316, 1328706242);
	timeSeriesData->pushBackDoubleValue(746.003, 1328706243);
	timeSeriesData->pushBackDoubleValue(748.613, 1328706244);
	timeSeriesData->pushBackStringValue("My testing string", 1328706245);
}

void deserializePropertyKindMappingFiles(COMMON_NS::DataObjectRepository * pck)
{
	RESQML2_0_1_NS::PropertyKindMapper* ptMapper = pck->getPropertyKindMapper();

	std::cout << "Application property kind name for azimuth : " << ptMapper->getApplicationPropertyKindNameFromResqmlStandardPropertyKindName(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::azimuth, "Petrel") << std::endl;
	std::cout << "Application property kind name for azimuth : " << ptMapper->getApplicationPropertyKindNameFromResqmlStandardPropertyKindName(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::gamma_x0020ray_x0020API_x0020unit, "Petrel") << std::endl;
	std::cout << "Application property kind name for azimuth : " << ptMapper->getApplicationPropertyKindNameFromResqmlStandardPropertyKindName(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::gamma_x0020ray_x0020API_x0020unit, "Sismage") << std::endl;
	std::cout << "Application property kind name for dip : " << ptMapper->getApplicationPropertyKindNameFromResqmlStandardPropertyKindName(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::dip, "myApplication") << std::endl;

	std::cout << "Standard property for Petrel \"Dip Azimuth\" : " << static_cast<int>(ptMapper->getResqmlStandardPropertyKindNameFromApplicationPropertyKindName("Dip Azimuth", "Petrel")) << std::endl;
	std::cout << "Standard property for Application property Absolute temperature : " << static_cast<int>(ptMapper->getResqmlStandardPropertyKindNameFromApplicationPropertyKindName("Absolute temperature", "myApplication")) << std::endl;

	std::cout << "Application property kind for unknown local property type uuid  : " << ptMapper->getApplicationPropertyKindNameFromResqmlLocalPropertyKindUuid("unknownUuid", "myApplication") << std::endl;
	std::cout << "Application property kind for local property type 959cf4e1-d485-5225-bbdb-f53c16cc0c3c (VShale) : " << ptMapper->getApplicationPropertyKindNameFromResqmlLocalPropertyKindUuid("959cf4e1-d485-5225-bbdb-f53c16cc0c3c", "Sismage") << std::endl;

	ptMapper->addResqmlLocalPropertyKindToEpcDocumentFromApplicationPropertyKindName("Elevation depth", "Petrel");
}

void deserializeActivity(COMMON_NS::AbstractObject const * resqmlObject)
{
	if (!resqmlObject->getActivitySet().empty()) {
		cout << "Activities for object " << resqmlObject->getTitle() << endl;
	}
	for (size_t i = 0; i < resqmlObject->getActivitySet().size(); ++i)
	{
		EML2_NS::Activity const * activity = resqmlObject->getActivitySet()[i];
		cout << "Activity : " << activity->getTitle() << endl;
		cout << "Activity Template : " << activity->getActivityTemplate()->getTitle() << endl;
		for (unsigned int j = 0; j < activity->getActivityTemplate()->getParameterCount(); ++j)
		{
			string paramTitle = activity->getActivityTemplate()->getParameterTitle(j);
			cout << "Parameter : " << paramTitle << endl;
			cout << "Parameter min occurs : " << activity->getActivityTemplate()->getParameterMinOccurences(paramTitle) << endl;
			cout << "Parameter max occurs : " << activity->getActivityTemplate()->getParameterMaxOccurences(paramTitle) << endl;
			cout << "Parameter is input : " << activity->getActivityTemplate()->getParameterIsInput(paramTitle) << endl;
			cout << "Parameter is output : " << activity->getActivityTemplate()->getParameterIsOutput(paramTitle) << endl;
			if (activity->getParameterCount(paramTitle) > 0) {
				if (activity->isAFloatingPointQuantityParameter(paramTitle)) {
					vector<double> vals = activity->getFloatingPointQuantityParameterValue(paramTitle);
					for (size_t k = 0; k < vals.size(); ++k) {
						cout << "Double value : " << vals[k] << endl;
					}
				}
				else if (activity->isAnIntegerQuantityParameter(paramTitle)) {
					vector<int64_t> vals = activity->getIntegerQuantityParameterValue(paramTitle);
					for (size_t k = 0; k < vals.size(); ++k) {
						cout << "Integer value : " << vals[k] << endl;
					}
				}
				else if (activity->isAStringParameter(paramTitle)) {
					vector<string> vals = activity->getStringParameterValue(paramTitle);
					for (size_t k = 0; k < vals.size(); ++k) {
						cout << "String value : " << vals[k] << endl;
					}
				}
				else if (activity->isAResqmlObjectParameter(paramTitle)) {
					vector<COMMON_NS::AbstractObject*> vals = activity->getResqmlObjectParameterValue(paramTitle);
					for (size_t k = 0; k < vals.size(); ++k) {
						cout << "Object title : " << vals[k]->getTitle() << endl;
					}
				}
				else {
					const vector<unsigned int> & paramIndex = activity->getParameterIndexOfTitle(paramTitle);
					for (size_t k = 0; k < paramIndex.size(); ++k) {
						if (activity->isAFloatingPointQuantityParameter(paramIndex[k]))
							cout << "Floating Point value : " << activity->getFloatingPointQuantityParameterValue(paramIndex[k]);
						else if (activity->isAnIntegerQuantityParameter(paramIndex[k]))
							cout << "Integer value : " << activity->getIntegerQuantityParameterValue(paramIndex[k]);
						else if (activity->isAStringParameter(paramIndex[k]))
							cout << "String value : " << activity->getStringParameterValue(paramIndex[k]);
						else if (activity->isAResqmlObjectParameter(paramIndex[k]))
							cout << "Object title : " << activity->getResqmlObjectParameterValue(paramIndex[k])->getTitle();
					}
				}
			}
			else
				cout << "No provided parameter in the activity." << endl;
		}
		cout << endl;
	}
}

bool serialize(const string & filePath)
{
	COMMON_NS::EpcDocument pck(filePath);
	COMMON_NS::DataObjectRepository repo;
#if WITH_RESQML2_2
	repo.setDefaultStandard(COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_2);
	repo.setDefaultStandard(COMMON_NS::DataObjectRepository::EnergisticsStandard::EML2_3);
#endif

	COMMON_NS::AbstractObject::setFormat("F2I-CONSULTING", "Fesapi Example", FESAPI_VERSION);

	EML2_NS::AbstractHdfProxy* hdfProxy = repo.createHdfProxy("", "Hdf Proxy", pck.getStorageDirectory(), pck.getName() + ".h5", COMMON_NS::DataObjectRepository::openingMode::OVERWRITE);
	//hdfProxy->setCompressionLevel(6);
	repo.setDefaultHdfProxy(hdfProxy);

	local3dCrs = repo.createLocalDepth3dCrs("", "Default local CRS", .0, .0, .0, .0, gsoap_resqml2_0_1::eml20__LengthUom::m, 23031, gsoap_resqml2_0_1::eml20__LengthUom::m, "Unknown", false);
	localTime3dCrs = repo.createLocalTime3dCrs("", "Default local time CRS", 1.0, 0.1, 15, .0, gsoap_resqml2_0_1::eml20__LengthUom::m, 23031, gsoap_resqml2_0_1::eml20__TimeUom::s, gsoap_resqml2_0_1::eml20__LengthUom::m, "Unknown", false); // CRS translation is just for testing;
	repo.setDefaultCrs(local3dCrs);

	// Comment or uncomment below domains/lines you want wether to test or not
	serializeWells(&repo, hdfProxy);
	serializePerforations(&repo);
	serializeBoundaries(&repo, hdfProxy);
	serializeGeobody(&repo, hdfProxy);
	serializeStructuralModel(repo, hdfProxy);
	serializeStratigraphicModel(&repo, hdfProxy);
	serializeGrid(&repo, hdfProxy);
	serializeActivities(&repo);
	serializeRepresentationSetRepresentation(&repo, hdfProxy);
	serializeRockFluidOrganization(repo, hdfProxy);
	PRODML2_1_NS::FluidSystem* fluidSystem = serializeFluidSystem(repo);
	serializeTabularFluidCharacterization(repo, fluidSystem);
	serializeCompositionalFluidCharacterization(repo);
	serializeTimeSeriesData(repo);
#if WITH_RESQML2_2
	serializeGraphicalInformationSet(&repo, hdfProxy);
#endif
	// Add an extended core property before to serialize
	pck.setExtendedCoreProperty("F2I-ExtendedCoreProp", "TestingVersion");

	hdfProxy->close();

	cout << "Start serialization of " << pck.getName() << " in " << (pck.getStorageDirectory().empty() ? "working directory." : pck.getStorageDirectory()) << endl;
	pck.serializeFrom(repo);

	// Check HDF proxy factory
	repo.setHdfProxyFactory(new HdfProxyFactoryExample());
	auto exoticHdfPox = repo.createHdfProxy("", "Dummy Exotic HDF proxy", "", "", COMMON_NS::DataObjectRepository::openingMode::READ_ONLY);
	double dummyPoints[3] = { 1.0, 2.0, 3.0 };
	repo.createPointSetRepresentation("", "")->pushBackGeometryPatch(1, dummyPoints, exoticHdfPox);

	return true;
}

void showAllMetadata(COMMON_NS::AbstractObject const * obj, const std::string & prefix = "")
{
	std::cout << prefix << "Title is : " << obj->getTitle() << std::endl;
	std::cout << prefix << "Guid is : " << obj->getUuid() << std::endl;
	if (!obj->isPartial()) {
		for (unsigned int i = 0; i < obj->getAliasCount(); ++i) {
			std::cout << prefix << "Alias is : " << obj->getAliasAuthorityAtIndex(i) << ":" << obj->getAliasTitleAtIndex(i) << std::endl;
		}
		for (unsigned int i = 0; i < obj->getExtraMetadataCount(); ++i) {
			std::cout << prefix << "Extrametadata is : " << obj->getExtraMetadataKeyAtIndex(i) << ":" << obj->getExtraMetadataStringValueAtIndex(i) << std::endl;
		}
		time_t creation = obj->getCreation();
		std::cout << prefix << "Creation date is (unix timestamp) : " << creation << std::endl;
		tm creationTm = obj->getCreationAsTimeStructure();
		std::cout << prefix << "Creation date is (struct tm) : " << 1900 + creationTm.tm_year << "-" << creationTm.tm_mon + 1 << "-" << creationTm.tm_mday << "T" << creationTm.tm_hour << ":" << creationTm.tm_min << ":" << creationTm.tm_sec << std::endl;
		if (!obj->getVersion().empty()) {
			std::cout << prefix << "version is : " << obj->getVersion() << std::endl;
		}
		std::cout << prefix << "--------------------------------------------------" << std::endl;

	}
	else {
		std::cout << prefix << "IS PARTIAL!" << std::endl;
	}
}

void showAllProperties(RESQML2_NS::AbstractRepresentation const * rep, bool* enabledCells = nullptr)
{
	std::vector<RESQML2_NS::AbstractProperty *> propertySet = rep->getPropertySet();
	if (!propertySet.empty()) {
		cout << "PROPERTIES" << std::endl;
	}
	for (size_t propIndex = 0; propIndex < propertySet.size(); ++propIndex) {
		std::cout << "\t--------------------------------------------------" << std::endl;
		RESQML2_NS::AbstractProperty const * prop = propertySet[propIndex];
		showAllMetadata(prop, "\t");

		std::vector<RESQML2_NS::PropertySet *> propSets = prop->getPropertySets();
		for (size_t propSetIndex = 0; propSetIndex < propSets.size(); ++propSetIndex) {
			RESQML2_NS::PropertySet* propSet = propSets[propSetIndex];
			std::cout << "\tContained in property set : ";
			showAllMetadata(propSet, "\t");
		}

		std::cout << "\tProperty kind is : " << prop->getPropertyKindAsString() << std::endl;
		if (prop->isAssociatedToOneStandardEnergisticsPropertyKind()) {
			std::cout << "\tProperty kind is an Energistics one" << std::endl;
		}
		else {
			std::cout << "\tProperty kind is not an Energistics one" << std::endl;
			auto pk = prop->getPropertyKind();
			auto pk201 = dynamic_cast<RESQML2_0_1_NS::PropertyKind*>(pk);
			if (pk201 != nullptr && pk201->isParentAnEnergisticsPropertyKind()) {
				std::cout << "\t\tProperty kind parent is an Energistics one" << std::endl;
				std::cout << "\t\tProperty kind parent is : " << pk->getParentAsString() << std::endl;
			}
			else {
				std::cout << "\t\tProperty kind parent is not an Energistics one" << std::endl;
				std::cout << "\t\tProperty kind parent is : " << pk->getParentPropertyKind()->getTitle() << std::endl;
			}
		}

		// Dimension
		unsigned int dimCount = prop->getDimensionsCountOfPatch(0);
		std::cout << "\tDimension count is : " << dimCount << std::endl;
		for (unsigned int dimIndex = 0; dimIndex < dimCount; ++dimIndex) {
			std::cout << "\tValues count in dimension " << dimIndex << " is : " << prop->getValuesCountOfDimensionOfPatch(dimIndex, 0) << std::endl;
		}
		unsigned int valueCount = prop->getValuesCountOfPatch(0);
		std::cout << "\tValues count in all dimensions is : " << valueCount << std::endl;

		// Datatype
		std::cout << "\tDatatype is : " << prop->getValuesHdfDatatype() << std::endl;
		if (prop->getValuesHdfDatatype() == 0) {
			cerr << "\tERROR !!!!! The hdf datatype is unknown" << endl;
			cout << "\tPress enter to continue..." << endl;
			cin.get();
		}
		else if (prop->getValuesHdfDatatype() > 2) {
			if (dynamic_cast<RESQML2_NS::DiscreteProperty const *>(prop) == nullptr && dynamic_cast<RESQML2_NS::CategoricalProperty const *>(prop) == nullptr) {
				cerr << "\tERROR !!!!! Only categorical or Discrete properties should be associated to an integer dataset." << endl;
				cout << "\tTrying to convert.." << endl;
				std::unique_ptr<double[]> values(new double[valueCount]);
				static_cast<RESQML2_NS::ContinuousProperty const *>(prop)->getDoubleValuesOfPatch(0, values.get());
				std::cout << "\tFirst value is " << values[0] << endl;
				std::cout << "\tSecond value is " << values[1] << endl;
				cout << "\tPress enter to continue..." << endl;
				cin.get();
			}
			else {
				if (dynamic_cast<RESQML2_NS::DiscreteProperty const *>(prop) != nullptr) {
					RESQML2_NS::DiscreteProperty const * discreteProp = static_cast<RESQML2_NS::DiscreteProperty const *>(prop);
					if (discreteProp->hasMinimumValue() && discreteProp->hasMinimumValue()) {
						std::cout << "\tMax value is " << discreteProp->getMaximumValue() << endl;
						std::cout << "\tMin value is " << discreteProp->getMinimumValue() << endl;
					}
				}
				else { //RESQML2_NS::CategoricalProperty
					RESQML2_NS::StringTableLookup* stl = static_cast<RESQML2_NS::CategoricalProperty const *>(prop)->getStringLookup();
					if (stl == nullptr) {
						cerr << "\tERROR !!!!! An integer categorical property should be associated to a string table lookup." << endl;
						cout << "\tPress enter to continue..." << endl;
						cin.get();
					}
					const unsigned int itemCount = stl->getItemCount();
					std::cout << "\tAssociated String Table lookup" << endl;
					for (unsigned int itemIndex = 0; itemIndex < itemCount; ++itemIndex) {
						std::cout << stl->getKeyAtIndex(itemIndex) << "->" << stl->getStringValueAtIndex(itemIndex) << endl;
					}
				}
				std::unique_ptr<int64_t[]> values(new int64_t[valueCount]);
				static_cast<RESQML2_NS::AbstractValuesProperty const *>(prop)->getLongValuesOfPatch(0, values.get());
				std::cout << "\tFirst value is " << values[0] << endl;
				std::cout << "\tSecond value is " << values[1] << endl;
			}
		}
		else {
			if (dynamic_cast<RESQML2_NS::ContinuousProperty const *>(prop) != nullptr) {
				RESQML2_NS::ContinuousProperty const * continuousProp = static_cast<RESQML2_NS::ContinuousProperty const *>(prop);
				const double maxValue = continuousProp->getMaximumValue();
				const double minValue = continuousProp->getMinimumValue();
				std::cout << "\tMax value is " << maxValue << endl;
				std::cout << "\tMin value is " << minValue << endl;
				std::unique_ptr<double[]> values(new double[valueCount]);
				continuousProp->getDoubleValuesOfPatch(0, values.get());
				std::cout << "\tFirst value is " << values[0] << endl;
				std::cout << "\tSecond value is " << values[1] << endl;

				if (continuousProp->getElementCountPerValue() == 1) {
					for (size_t cellIndex = 0; cellIndex < valueCount; ++cellIndex) {
						if (enabledCells != nullptr && !enabledCells[cellIndex]) {
							continue;
						}
						if (values[cellIndex] > maxValue || values[cellIndex] < minValue) {
							std::cerr << "\tERROR of min max range on : cell " << cellIndex << " has value " << values[cellIndex] << endl;
						}
					}
				}
			}
			else if (dynamic_cast<RESQML2_NS::PointsProperty const *>(prop) != nullptr) {
				RESQML2_NS::PointsProperty const * pointsProp = static_cast<RESQML2_NS::PointsProperty const *>(prop);
				std::unique_ptr<double[]> values(new double[pointsProp->getXyzPointCountOfPatch(0) * 3]);
				pointsProp->getXyzPointsOfPatch(0, values.get());
				std::cout << "\tFirst point is " << values[0] << ", " << values[1] << ", " << values[2] << endl;
				std::cout << "\tSecond point is " << values[3] << ", " << values[4] << ", " << values[5] << endl;
			}
			else if (dynamic_cast<RESQML2_NS::CategoricalProperty const *>(prop) != nullptr) {
				RESQML2_NS::DoubleTableLookup* stl = static_cast<RESQML2_NS::CategoricalProperty const *>(prop)->getDoubleLookup();
				if (stl == nullptr) {
					cerr << "\tERROR !!!!! A floating point categorical property should be associated to a double table lookup." << endl;
					cout << "\tPress enter to continue..." << endl;
					cin.get();
				}
				const unsigned int itemCount = stl->getItemCount();
				std::cout << "\tAssociated Double Table lookup" << endl;
				for (unsigned int itemIndex = 0; itemIndex < itemCount; ++itemIndex) {
					std::cout << stl->getKeyAtIndex(itemIndex) << "->" << stl->getValueAtIndex(itemIndex) << endl;
				}
				std::unique_ptr<double[]> values(new double[valueCount]);
				static_cast<RESQML2_NS::AbstractValuesProperty const *>(prop)->getDoubleValuesOfPatch(0, values.get());
				std::cout << "\tFirst value is " << values[0] << endl;
				std::cout << "\tSecond value is " << values[1] << endl;
			}
			else {
				cerr << "\tERROR !!!!! The discrete or comment property is linked to a floating point HDF5 dataset." << endl;
				cout << "\tTrying to convert.." << endl;
				std::unique_ptr<int64_t[]> values(new int64_t[valueCount]);
				dynamic_cast<RESQML2_NS::AbstractValuesProperty const *>(prop)->getLongValuesOfPatch(0, values.get());
				std::cout << "\tFirst value is " << values[0] << endl;
				std::cout << "\tSecond value is " << values[1] << endl;
				cout << "\tPress enter to continue..." << endl;
				cin.get();
			}
		}

		// Time Series
		if (prop->getTimeIndicesCount() != 0) {
			std::cout << "\tThis property is a dynamic one" << std::endl;
			std::cout << "\tTime index start is " << prop->getTimeIndexStart() << std::endl;
			std::cout << "\tTime index count is " << prop->getTimeIndicesCount() << std::endl;
		}
	}

	std::cout << "\t--------------------------------------------------" << std::endl;
}

void showAllSubRepresentations(const vector<RESQML2_NS::SubRepresentation *> & subRepSet)
{
	if (!subRepSet.empty()) {
		cout << "SUBREPRESENTATIONS" << std::endl;
	}
	std::cout << "\t--------------------------------------------------" << std::endl;
	for (size_t subRepIndex = 0; subRepIndex < subRepSet.size(); ++subRepIndex)
	{
		showAllMetadata(subRepSet[subRepIndex], "\t");
		if (!subRepSet[subRepIndex]->isPartial()) {
			const uint64_t indiceCount = subRepSet[subRepIndex]->getElementCountOfPatch(0);

			// element indices
			std::unique_ptr<uint64_t[]> elementIndices(new uint64_t[indiceCount]);
			subRepSet[subRepIndex]->getElementIndicesOfPatch(0, 0, elementIndices.get());
			for (unsigned int i = 0; i < indiceCount && i < 10; ++i) {
				std::cout << "Element indice at position " << i << " : " << elementIndices[i] << std::endl;
			}

			// Supporting rep indices
			std::unique_ptr<short[]> supRepIndices (new short[indiceCount]);
			subRepSet[subRepIndex]->getSupportingRepresentationIndicesOfPatch(0, supRepIndices.get());
			for (unsigned int i = 0; i < indiceCount && i < 10; ++i) {
				std::cout << "Supporting rep indice at position " << i << " : " << supRepIndices[i] << std::endl;
			}

		}
		else {
			std::cout << "IS PARTIAL!" << std::endl;
		}

		showAllProperties(subRepSet[subRepIndex]);
	}
}

void deserializeStratiColumn(RESQML2_NS::StratigraphicColumn * stratiColumn, const COMMON_NS::EnumStringMapper & enumStrMapper)
{
	showAllMetadata(stratiColumn);
	for (size_t i = 0; i < stratiColumn->getStratigraphicColumnRankInterpretationSet().size(); ++i)
	{
		std::cout << "\tCOLUMN RANK INTERP" << std::endl;
		RESQML2_NS::StratigraphicColumnRankInterpretation const * stratiColumnRankInterp = stratiColumn->getStratigraphicColumnRankInterpretationSet()[i];
		showAllMetadata(stratiColumnRankInterp);
		if (stratiColumnRankInterp->isAChronoStratiRank())
			cout << "This is a chrono rank!" << endl;
		else
			cout << "This is not a chrono rank!" << endl;
		unsigned int contactCount = stratiColumnRankInterp->getContactCount();
		for (unsigned int contactIndex = 0; contactIndex < contactCount; ++contactIndex) {
			cout << "SUBJECT : " << endl;
			showAllMetadata(stratiColumnRankInterp->getSubjectOfContact(contactIndex));
			cout << "DIRECT OBJECT : " << endl;
			showAllMetadata(stratiColumnRankInterp->getDirectObjectOfContact(contactIndex));
		}

		vector<RESQML2_NS::StratigraphicOccurrenceInterpretation*> soiSet = stratiColumnRankInterp->getStratigraphicOccurrenceInterpretationSet();
		for (size_t soiIndex = 0; soiIndex < soiSet.size(); ++soiIndex) {
			vector<RESQML2_NS::WellboreMarkerFrameRepresentation *> markerFrameSet = soiSet[soiIndex]->getWellboreMarkerFrameRepresentationSet();
			for (size_t markerFrameIndex = 0; markerFrameIndex < markerFrameSet.size(); ++markerFrameIndex) {
				RESQML2_NS::WellboreMarkerFrameRepresentation * markerFrame = markerFrameSet[markerFrameIndex];
				showAllMetadata(markerFrame);
				vector<RESQML2_NS::WellboreMarker *> markerSet = markerFrame->getWellboreMarkerSet();
				std::unique_ptr<double[]> doubleMds(new double[markerFrame->getMdValuesCount()]);
				markerFrame->getMdAsDoubleValues(doubleMds.get());
				for (size_t mIndex = 0; mIndex < markerSet.size(); ++mIndex) {
					if (doubleMds[mIndex] == doubleMds[mIndex]) {
						cout << doubleMds[mIndex] << endl;
					}
					else {
						cout << "NaN" << endl;
					}
					if (markerSet[mIndex]->hasDipAngle()) {
						cout << "dip Angle " << markerSet[mIndex]->getDipAngleValue() << " " << enumStrMapper.planeAngleUomToString(markerSet[mIndex]->getDipAngleUom()) << endl;
					}
					if (markerSet[mIndex]->hasDipDirection()) {
						cout << "dip Direction " << markerSet[mIndex]->getDipDirectionValue() << " " << enumStrMapper.planeAngleUomToString(markerSet[mIndex]->getDipDirectionUom()) << endl;
					}
				}
			}
		}
	}
}

void deserializeSealedSurfaceFramework(const COMMON_NS::DataObjectRepository & pck)
{
	const std::vector<RESQML2_NS::SealedSurfaceFrameworkRepresentation*> ssfVec = pck.getDataObjects<RESQML2_NS::SealedSurfaceFrameworkRepresentation>();

	for (size_t ssfIndex = 0; ssfIndex < ssfVec.size(); ++ssfIndex) {
		std::cout << "\tSEALED SURFACE FRAMEWORK" << std::endl;
		RESQML2_NS::SealedSurfaceFrameworkRepresentation* ssf = ssfVec[ssfIndex];
		showAllMetadata(ssf);

		std::cout << "\tCONTAINED REPRESENTATIONS" << std::endl;
		const unsigned int repCount = ssf->getRepresentationCount();
		for (unsigned int repIdx = 0; repIdx < repCount; ++repIdx) {
			showAllMetadata(ssf->getRepresentation(repIdx));
		}

		std::cout << "\tCONTACT (REPRESENTATION) IDENTITY" << std::endl;
		const unsigned int ciCount = ssf->getContactIdentityCount();
		for (unsigned int ciIdx = 0; ciIdx < ciCount; ++ciIdx) {
			std::cout << "\t\tidentity kind (0->coloc, 1->preColoc, 2->eq, 3->preEq) : " << static_cast<std::underlying_type<gsoap_resqml2_0_1::resqml20__IdentityKind>::type>(ssf->getContactIdentityKind(ciIdx)) << std::endl;
			const unsigned int ciContactRepCount = ssf->getContactCountInContactIdentity(ciIdx);
			std::unique_ptr<unsigned int[]> cicrIndices(new unsigned int[ciContactRepCount]);
			ssf->getContactIndices(ciIdx, cicrIndices.get());
			std::cout << "\t\tcontact rep indices : ";
			for (unsigned int cicrIdx = 0; cicrIdx < ciContactRepCount; ++cicrIdx) {
				std::cout << cicrIndices[cicrIdx] << " ";
			}
			std::cout << std::endl;

			if (ssf->areAllContactNodesIdentical(ciIdx)) {
				std::cout << "\t\tAll nodes are identical." << endl;
			}
			else {
				const unsigned int ciIdenticalNodeCount = ssf->getIdenticalContactNodeCount(ciIdx);
				std::unique_ptr<unsigned int[]> ciIdenticalNodeIndices(new unsigned int[ciIdenticalNodeCount]);
				ssf->getIdenticalContactNodeIndices(ciIdx, ciIdenticalNodeIndices.get());
				std::cout << "\t\tIdentical nodes : ";
				for (unsigned int identicalNodesIdx = 0; identicalNodesIdx < ciIdenticalNodeCount; ++identicalNodesIdx) {
					std::cout << ciIdenticalNodeIndices[identicalNodesIdx] << " ";
				}
				std::cout << std::endl;
			}
		}

		std::cout << "\tCONTACT REPRESENTATIONS" << std::endl;;
		const unsigned int crCount = ssf->getContactCount();
		for (unsigned int crIdx = 0; crIdx < crCount; ++crIdx) {
			std::cout << "\t\tidentity kind (0->coloc, 1->preColoc, 2->eq, 3->preEq) : " << static_cast<std::underlying_type<gsoap_resqml2_0_1::resqml20__IdentityKind>::type>(ssf->getContactPatchIdentityKind(crIdx)) << std::endl;
			if (ssf->areAllContactPatchNodesIdentical(crIdx)) {
				std::cout << "\t\tAll nodes are identical." << endl;
			}
			else {
				const unsigned int crIdenticalNodeCount = ssf->getIdenticalContactPatchNodeCount(crIdx);
				std::unique_ptr<unsigned int[]> crIdenticalNodeIndices(new unsigned int[crIdenticalNodeCount]);
				ssf->getIdenticalContactPatchNodeIndices(crIdx, crIdenticalNodeIndices.get());
				std::cout << "\t\tIdentical nodes : ";
				for (unsigned int identicalNodesIdx = 0; identicalNodesIdx < crIdenticalNodeCount; ++identicalNodesIdx) {
					std::cout << crIdenticalNodeIndices[identicalNodesIdx] << " ";
				}
				std::cout << std::endl;
			}

			std::cout << "\t\tCONTACT PATCHES" << std::endl;;
			const unsigned int cpCount = ssf->getContactPatchCount(crIdx);
			for (unsigned int cpIdx = 0; cpIdx < cpCount; ++cpIdx) {
				showAllMetadata(ssf->getRepresentationOfContactPatch(crIdx, cpIdx));
				const unsigned int cpNodeCount = ssf->getContactPatchNodeCount(crIdx, cpIdx);
				std::unique_ptr<unsigned int[]> cpNodeIndices(new unsigned int[cpNodeCount]);
				ssf->getContactPatchNodeIndices(crIdx, cpIdx, cpNodeIndices.get());
				std::cout << "\t\tcontact patch indices : ";
				for (unsigned int cpNodeIdx = 0; cpNodeIdx < cpNodeCount; ++cpNodeIdx) {
					std::cout << cpNodeIndices[cpNodeIdx] << " ";
				}
				std::cout << std::endl;
			}
		}
	}
}

void deserializeSealedVolumeFramework(const COMMON_NS::DataObjectRepository & pck)
{
	const std::vector<RESQML2_NS::SealedVolumeFrameworkRepresentation*> svfVec = pck.getDataObjects<RESQML2_NS::SealedVolumeFrameworkRepresentation>();

	for (size_t svfIndex = 0; svfIndex < svfVec.size(); ++svfIndex) {
		std::cout << "\tSEALED VOLUME FRAMEWORK" << std::endl;
		RESQML2_NS::SealedVolumeFrameworkRepresentation* svf = svfVec[svfIndex];
		showAllMetadata(svf);

		std::cout << "\tis based on sealed structural framework " << endl;
		showAllMetadata(svf->getSealedStructuralFramework());

		std::cout << "\t\tCONTAINED REGIONS" << std::endl;
		const unsigned int regionCount = svf->getRegionCount();
		for (unsigned int regionIdx = 0; regionIdx < regionCount; ++regionIdx) {
			showAllMetadata(svf->getStratiUnitInterp(regionIdx));

			const unsigned int faceCount = svf->getFaceCountOfExternalShell(regionIdx);
			for (unsigned int faceIdx = 0; faceIdx < faceCount; ++faceIdx) {
				std::cout << "\t\tFace index " << faceIdx << " is the patch " << svf->getRepPatchIndexOfExternalShellFace(regionIdx, faceIdx) << " with side " << svf->getSideFlagOfExternalShellFace(regionIdx, faceIdx) << " of surface representation" << std::endl;
				showAllMetadata(svf->getRepOfExternalShellFace(regionIdx, faceIdx));
			}
		}

	}
}

void deserializeGeobody(COMMON_NS::DataObjectRepository * pck)
{
	//2d
	std::vector<RESQML2_NS::BoundaryFeature*> geobodyBoundarySet = pck->getGeobodyBoundarySet();
	for (size_t i = 0; i < geobodyBoundarySet.size(); ++i) {
		showAllMetadata(geobodyBoundarySet[i]);
		cout << "interp count : " << geobodyBoundarySet[i]->getInterpretationCount() << endl;
	}

	//3d
	std::vector<RESQML2_NS::RockVolumeFeature*> geobodySet = pck->getGeobodySet();
	for (size_t i = 0; i < geobodySet.size(); ++i) {
		showAllMetadata(geobodySet[i]);
		cout << "interp count : " << geobodySet[i]->getInterpretationCount() << endl;
	}
}

void deserializeFluidBoundary(COMMON_NS::DataObjectRepository & pck)
{
	std::vector<RESQML2_0_1_NS::FluidBoundaryFeature*> fbfSet = pck.getDataObjects<RESQML2_0_1_NS::FluidBoundaryFeature>();
	for (size_t fbfIndex = 0; fbfIndex < fbfSet.size(); ++fbfIndex) {
		RESQML2_0_1_NS::FluidBoundaryFeature* fluidBoundary = fbfSet[fbfIndex];
		if (fluidBoundary == nullptr) return;
		showAllMetadata(fluidBoundary);
		if (!fluidBoundary->isPartial()) {
			showAllMetadata(fluidBoundary->getInterpretation(0));
			RESQML2_NS::PlaneSetRepresentation const * rep = static_cast<RESQML2_NS::PlaneSetRepresentation const*>(fluidBoundary->getInterpretation(0)->getRepresentation(0));
			showAllMetadata(rep);
			uint64_t ptCount = rep->getXyzPointCountOfAllPatches();
			std::unique_ptr<double[]> allXyzPoints(new double[ptCount * 3]);
			rep->getXyzPointsOfAllPatchesInGlobalCrs(allXyzPoints.get());
			for (size_t i = 0; i < ptCount; ++i) {
				std::cout << "Point " << i << " X=" << allXyzPoints[i * 3] << std::endl;
				std::cout << "Point " << i << " Y=" << allXyzPoints[i * 3 + 1] << std::endl;
				std::cout << "Point " << i << " Z=" << allXyzPoints[i * 3 + 2] << std::endl;
			}
		}
	}
}

void deserializeRockFluidOrganization(COMMON_NS::DataObjectRepository & pck)
{
	std::vector<RESQML2_NS::RockFluidOrganizationInterpretation*> rockFluidOrgInterpSet = pck.getDataObjects<RESQML2_NS::RockFluidOrganizationInterpretation>();
	for (size_t rfoiIndex = 0; rfoiIndex < rockFluidOrgInterpSet.size(); ++rfoiIndex) {
		RESQML2_NS::RockFluidOrganizationInterpretation* rockFluidOrgInterp = rockFluidOrgInterpSet[rfoiIndex];
		showAllMetadata(rockFluidOrgInterp);
		for (unsigned int i = 0; i < rockFluidOrgInterp->getGridRepresentationCount(); ++i) {
			RESQML2_NS::AbstractGridRepresentation const * grid = rockFluidOrgInterp->getGridRepresentation(i);
			showAllMetadata(grid);
		}

		for (unsigned int unitIndex = 0; unitIndex < rockFluidOrgInterp->getRockFluidUnitInterpCount(); ++unitIndex) {
			RESQML2_NS::RockFluidUnitInterpretation* rockFluidInterp = rockFluidOrgInterp->getRockFluidUnitInterpretation(unitIndex);
			showAllMetadata(rockFluidInterp);

			RESQML2_NS::AbstractFeature* rockFluidFeature = rockFluidInterp->getInterpretedFeature();
			showAllMetadata(rockFluidFeature);

			if (dynamic_cast<RESQML2_0_1_NS::RockFluidUnitFeature*>(rockFluidFeature) != nullptr) {
				RESQML2_0_1_NS::BoundaryFeature* top = static_cast<RESQML2_0_1_NS::RockFluidUnitFeature*>(rockFluidFeature)->getTop();
				showAllMetadata(top);

				RESQML2_0_1_NS::BoundaryFeature* bottom = static_cast<RESQML2_0_1_NS::RockFluidUnitFeature*>(rockFluidFeature)->getBottom();
				showAllMetadata(bottom);
			}
		}
	}
}

void deserializeFluidCharacterization(COMMON_NS::DataObjectRepository & pck)
{
	std::vector<PRODML2_1_NS::FluidCharacterization*> fluidCharacterization = pck.getDataObjects<PRODML2_1_NS::FluidCharacterization>();
	for (size_t fcIndex = 0; fcIndex < fluidCharacterization.size(); ++fcIndex) {
		PRODML2_1_NS::FluidCharacterization* fc = fluidCharacterization[fcIndex];
		showAllMetadata(fc);
		RESQML2_NS::RockFluidUnitInterpretation* rfu = fc->getRockFluidUnit();
		if (rfu != nullptr) {
			std::cout << "connected wiht rock fluid unit " << std::endl;
			showAllMetadata(rfu);
		}
		for (unsigned int i = 0; i < fc->getFormationWaterCount(); ++i) {
			std::cout << "FORMATION WATER " << std::endl;
			if (fc->hasFormationWaterMassFraction(i)) { cout << "MassFraction: " << fc->getFormationWaterMassFractionValue(i) << std::endl; }
			if (fc->hasFormationWaterMoleFraction(i)) { cout << "MoleFraction: " << fc->getFormationWaterMoleFractionValue(i) << std::endl; }
			if (fc->hasFormationWaterSalinity(i)) { cout << "Salinity: " << fc->getFormationWaterSalinityValue(i) << std::endl; }
			if (fc->hasFormationWaterSpecificGravity(i)) { cout << "SpecificGravity: " << fc->getFormationWaterSpecificGravity(i) << std::endl; }
			if (fc->hasFormationWaterRemark(i)) { cout << "Remark: " << fc->getFormationWaterRemark(i) << std::endl; }
		}
		for (unsigned int i = 0; i < fc->getPureFluidComponentCount(); ++i) {
			std::cout << "PURE FLUID COMPONENT " << std::endl;
			if (fc->hasPureFluidComponentMassFraction(i)) { cout << "MassFraction: " << fc->getPureFluidComponentMassFractionValue(i) << std::endl; }
			if (fc->hasPureFluidComponentMolecularWeight(i)) { cout << "MolecularWeight: " << fc->getPureFluidComponentMolecularWeightValue(i) << std::endl; }
			if (fc->hasPureFluidComponentMoleFraction(i)) { cout << "MoleFraction: " << fc->getPureFluidComponentMoleFractionValue(i) << std::endl; }
			if (fc->hasPureFluidComponentRemark(i)) { cout << "Remark: " << fc->getPureFluidComponentRemark(i) << std::endl; }
		}

		for (unsigned int modelIndex = 0; modelIndex < fc->getModelCount(); ++modelIndex) {
			std::cout << "MODEL " << std::endl;
			if (fc->hasFluidCharacterizationModelName(modelIndex)) { cout << "name: " << fc->getFluidCharacterizationModelName(modelIndex) << std::endl; }
			if (fc->hasFluidCharacterizationModelReferenceStockTankTemperature(modelIndex)) {
				cout << "ReferenceStockTankTemperature: " << fc->getFluidCharacterizationModelReferenceStockTankTemperatureValue(modelIndex) << std::endl;
			}
			if (fc->hasFluidCharacterizationModelReferenceTemperature(modelIndex)) {
				cout << "ReferenceTemperature: " << fc->getFluidCharacterizationModelReferenceTemperatureValue(modelIndex) << std::endl;
			}
			if (fc->hasFluidCharacterizationModelRemark(modelIndex)) { cout << "Remark: " << fc->getFluidCharacterizationModelRemark(modelIndex) << std::endl; }

			PRODML2_1_NS::PvtSpecification* spec = fc->getModelSpecification(modelIndex);
			if (spec != nullptr) {
				if (dynamic_cast<PRODML2_1_NS::CompositionalSpecification*>(spec) != nullptr) {
					PRODML2_1_NS::CompositionalSpecification* compoSpec = static_cast<PRODML2_1_NS::CompositionalSpecification*>(spec);
					for (unsigned int coeffIndex = 0; coeffIndex < compoSpec->getCoefficientCount(); ++coeffIndex) {
						cout << "coeff value: " << compoSpec->getCoefficientValue(coeffIndex) << std::endl;
						cout << "coeff kind: " << static_cast<int>(compoSpec->getCoefficientKind(coeffIndex)) << std::endl;
						if (compoSpec->hasCoefficientName(modelIndex)) { cout << "Name: " << compoSpec->getCoefficientName(coeffIndex) << std::endl; }
					}
					for (unsigned int coeffIndex = 0; coeffIndex < compoSpec->getBinaryInteractionCoefficientCount(); ++coeffIndex) {
						cout << "fluid compo 1 ref: " << compoSpec->getBinaryInteractionCoefficientFluidComponent1Reference(coeffIndex) << std::endl;
						if (compoSpec->hasBinaryInteractionCoefficientFluidComponent2Reference(modelIndex)) { cout << "fluid compo 2 ref: " << compoSpec->getBinaryInteractionCoefficientFluidComponent2Reference(coeffIndex) << std::endl; }
					}
					for (unsigned int propIndex = 0; propIndex < compoSpec->getFluidComponentPropertyCount(); ++propIndex) {
						cout << "fluid compo ref: " << compoSpec->getFluidComponentPropertyFluidComponentReference(propIndex) << std::endl;
						if (compoSpec->hasFluidComponentPropertyAcentricFactor(propIndex)) { cout << "AcentricFactor: " << compoSpec->getFluidComponentPropertyAcentricFactor(propIndex) << std::endl; }
						if (compoSpec->hasFluidComponentPropertyCompactVolume(propIndex)) { cout << "CompactVolume: " << compoSpec->getFluidComponentPropertyCompactVolumeValue(propIndex) << " " << compoSpec->getFluidComponentPropertyCompactVolumeUom(propIndex) << std::endl; }
						if (compoSpec->hasFluidComponentPropertyCriticalPressure(propIndex)) { cout << "CriticalPressure: " << compoSpec->getFluidComponentPropertyCriticalPressureValue(propIndex) << " " << compoSpec->getFluidComponentPropertyCriticalPressureUom(propIndex) << std::endl; }
						if (compoSpec->hasFluidComponentPropertyCriticalTemperature(propIndex)) { cout << "CriticalTemperature: " << compoSpec->getFluidComponentPropertyCriticalTemperatureValue(propIndex) << " " << static_cast<int>(compoSpec->getFluidComponentPropertyCriticalTemperatureUom(propIndex)) << std::endl; }
						if (compoSpec->hasFluidComponentPropertyCriticalViscosity(propIndex)) { cout << "CriticalViscosity: " << compoSpec->getFluidComponentPropertyCriticalViscosityValue(propIndex) << " " << static_cast<int>(compoSpec->getFluidComponentPropertyCriticalViscosityUom(propIndex)) << std::endl; }
						if (compoSpec->hasFluidComponentPropertyCriticalVolume(propIndex)) { cout << "CriticalVolume: " << compoSpec->getFluidComponentPropertyCriticalVolumeValue(propIndex) << " " << static_cast<int>(compoSpec->getFluidComponentPropertyCriticalVolumeUom(propIndex)) << std::endl; }
						if (compoSpec->hasFluidComponentPropertyMassDensity(propIndex)) { cout << "MassDensity: " << compoSpec->getFluidComponentPropertyMassDensityValue(propIndex) << " " << compoSpec->getFluidComponentPropertyMassDensityUom(propIndex) << std::endl; }
					}
				}
			}
		}
	}
}

void deserializeTimeSeriesData(COMMON_NS::DataObjectRepository & pck)
{
	std::vector<PRODML2_1_NS::TimeSeriesData*> timeSeriesDataSet = pck.getDataObjects<PRODML2_1_NS::TimeSeriesData>();
	for (size_t timeSeriesDataSetIdx = 0; timeSeriesDataSetIdx < timeSeriesDataSet.size(); ++timeSeriesDataSetIdx) {
		PRODML2_1_NS::TimeSeriesData* tsd = timeSeriesDataSet[timeSeriesDataSetIdx];
		showAllMetadata(tsd);

		for (unsigned int i = 0; i < tsd->getKeywordCount(); ++i) {
			std::cout << "KEYWORD " << static_cast<int>(tsd->getKeyword(i)) << " : " << tsd->getKeywordValue(i) << std::endl;
		}
		std::cout << "UOM : " << tsd->getUomAsString() << std::endl;
		std::cout << "Measure class : " << tsd->getMeasureClassAsString() << std::endl;

		for (unsigned int i = 0; i < tsd->getValueCount(); ++i) {
			if (tsd->isStringValue(i)) {
				std::cout << "String value: " << tsd->getStringValue(i) << " timestamp: " << tsd->getValueTimestamp(i) << std::endl;
			}
			else if (tsd->isDoubleValue(i)) {
				std::cout << "Double value: " << tsd->getDoubleValue(i) << " timestamp: " << tsd->getValueTimestamp(i);
				if (tsd->hasValueStatus(i)) {
					std::cout << " status: " << static_cast<int>(tsd->getValueStatus(i));
				}
				std::cout << std::endl;
			}
		}
	}
}

/**
* Deserialize IJK grid explicit and parametric representations packed in a given EPC document.
* This method read grid geometry by using hyperslabbing methods. Each grid is read interface by interface
* and then layer by layer.
* @param pck	An EPC document containing the IJK grid to deserialize.
*/
void deserializeGridHyperslabbingInterfaceSequence(const COMMON_NS::DataObjectRepository & pck)
{
	cout << endl << "BEGIN: IJK GRID REP (hyperslabbing)" << std::endl;
	unsigned int ijkGridCount = pck.getIjkGridRepresentationCount();
	for (unsigned int ijkGridIdx = 0; ijkGridIdx < ijkGridCount; ++ijkGridIdx)
	{
		RESQML2_NS::AbstractIjkGridRepresentation* ijkGrid = pck.getIjkGridRepresentation(ijkGridIdx);

		if (ijkGrid->getGeometryKind() != RESQML2_NS::AbstractIjkGridRepresentation::NO_GEOMETRY)
		{
			if (ijkGrid->getGeometryKind() == RESQML2_NS::AbstractIjkGridRepresentation::EXPLICIT || ijkGrid->getGeometryKind() == RESQML2_NS::AbstractIjkGridRepresentation::PARAMETRIC) {
				cout << "--------------------------------------------------" << std::endl;
				showAllMetadata(ijkGrid);
				if (ijkGrid->isPartial()) {
					continue;
				}

				ijkGrid->loadSplitInformation();

				if (ijkGrid->getKGapsCount() > 0) {

					// here, we read a grid interface by interface. Each interface is read
					// in i then j direction
					cout << "INTERFACE BY INTERFACE" << std::endl;

					std::unique_ptr<bool[]> gapAfterLayer(new bool[ijkGrid->getKCellCount() - 1]);
					ijkGrid->getKGaps(gapAfterLayer.get());
					
					unsigned int kLayer = 0;
					unsigned int cornerShift = 0;

					for (unsigned int kInterface = 0; kInterface < ijkGrid->getKCellCount() + 1 + ijkGrid->getKGapsCount(); kInterface++) {
						cout << "INTERFACE: " << kInterface << std::endl;

						std::unique_ptr<double[]> interfaceXyzPoints(new double[ijkGrid->getXyzPointCountOfKInterface() * 3]);
						ijkGrid->getXyzPointsOfKInterface(kInterface, interfaceXyzPoints.get());

						for (unsigned int j = 0; j < ijkGrid->getJCellCount(); ++j) {
							for (unsigned int i = 0; i < ijkGrid->getICellCount(); ++i) {
								cout << "CELL (" << i << ", " << j << ", " << kLayer << ")" << std::endl;

								uint64_t xyzPointIndex;
								double x, y, z;
								uint64_t indexShift = kInterface * ijkGrid->getXyzPointCountOfKInterface() * 3;

								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kLayer, 0 + cornerShift) * 3 - indexShift;
								x = interfaceXyzPoints[xyzPointIndex];
								y = interfaceXyzPoints[xyzPointIndex + 1];
								z = interfaceXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (0, 0, " << ((cornerShift == 0) ? "0" : "1") << "): " << x << " " << y << " " << z << std::endl;

								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kLayer, 1 + cornerShift) * 3 - indexShift;
								x = interfaceXyzPoints[xyzPointIndex];
								y = interfaceXyzPoints[xyzPointIndex + 1];
								z = interfaceXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (1, 0, " << ((cornerShift == 0) ? "0" : "1") << "): " << x << " " << y << " " << z << std::endl;

								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kLayer, 2 + cornerShift) * 3 - indexShift;
								x = interfaceXyzPoints[xyzPointIndex];
								y = interfaceXyzPoints[xyzPointIndex + 1];
								z = interfaceXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (1, 1, " << ((cornerShift == 0) ? "0" : "1") << "): " << x << " " << y << " " << z << std::endl;

								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kLayer, 3 + cornerShift) * 3 - indexShift;
								x = interfaceXyzPoints[xyzPointIndex];
								y = interfaceXyzPoints[xyzPointIndex + 1];
								z = interfaceXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (0, 1, " << ((cornerShift == 0) ? "0" : "1") << "): " << x << " " << y << " " << z << std::endl;
							}
						}

						if (cornerShift == 4 || (!gapAfterLayer[kLayer] && kInterface != ijkGrid->getKCellCount() + ijkGrid->getKGapsCount() - 1)) {
							kLayer++;
							cornerShift = 0;
						}
						else {
							cornerShift = 4;
						}
					}

					// here, we read a grid layer by layer. Each layer is read in i,
					// then j direction.
					cout << "--------------------------------------------------" << std::endl;
					cout << "LAYER BY LAYER" << std::endl;

					int kInterface = 0;

					for (unsigned int kLayer = 0; kLayer < ijkGrid->getKCellCount(); kLayer++)
					{
						cout << "LAYER: " << kLayer << std::endl;

						std::unique_ptr<double[]> layerXyzPoints(new double[ijkGrid->getXyzPointCountOfKInterface() * 3 * 2]);

						ijkGrid->getXyzPointsOfKInterfaceSequence(kInterface, kInterface + 1, layerXyzPoints.get());

						for (unsigned int j = 0; j < ijkGrid->getJCellCount(); j++)
						{
							for (unsigned int i = 0; i < ijkGrid->getICellCount(); i++)
							{
								cout << "CELL (" << i << ", " << j << ", " << kLayer << ")" << std::endl;

								uint64_t xyzPointIndex;
								double x, y, z;
								uint64_t indexShift = kInterface * ijkGrid->getXyzPointCountOfKInterface() * 3;

								// Corner (0, 0, 0)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kLayer, 0) * 3 - indexShift;
								x = layerXyzPoints[xyzPointIndex];
								y = layerXyzPoints[xyzPointIndex + 1];
								z = layerXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (0, 0, 0): " << x << " " << y << " " << z << std::endl;

								// Corner (1, 0, 0)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kLayer, 1) * 3 - indexShift;
								x = layerXyzPoints[xyzPointIndex];
								y = layerXyzPoints[xyzPointIndex + 1];
								z = layerXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (1, 0, 0): " << x << " " << y << " " << z << std::endl;

								// Corner (1, 1, 0)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kLayer, 2) * 3 - indexShift;
								x = layerXyzPoints[xyzPointIndex];
								y = layerXyzPoints[xyzPointIndex + 1];
								z = layerXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (1, 1, 0): " << x << " " << y << " " << z << std::endl;

								// Corner (0, 1, 0)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kLayer, 3) * 3 - indexShift;
								x = layerXyzPoints[xyzPointIndex];
								y = layerXyzPoints[xyzPointIndex + 1];
								z = layerXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (0, 1, 0): " << x << " " << y << " " << z << std::endl;

								// Corner (0, 0, 1)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kLayer, 4) * 3 - indexShift;
								x = layerXyzPoints[xyzPointIndex];
								y = layerXyzPoints[xyzPointIndex + 1];
								z = layerXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (0, 0, 1): " << x << " " << y << " " << z << std::endl;

								// Corner (1, 0, 1)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kLayer, 5) * 3 - indexShift;
								x = layerXyzPoints[xyzPointIndex];
								y = layerXyzPoints[xyzPointIndex + 1];
								z = layerXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (1, 0, 1): " << x << " " << y << " " << z << std::endl;

								// Corner (1, 1, 1)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kLayer, 6) * 3 - indexShift;
								x = layerXyzPoints[xyzPointIndex];
								y = layerXyzPoints[xyzPointIndex + 1];
								z = layerXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (1, 1, 1): " << x << " " << y << " " << z << std::endl;

								// Corner (0, 1, 1)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kLayer, 7) * 3 - indexShift;
								x = layerXyzPoints[xyzPointIndex];
								y = layerXyzPoints[xyzPointIndex + 1];
								z = layerXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (0, 1, 1): " << x << " " << y << " " << z << std::endl;
							}
						}

						kInterface = gapAfterLayer[kLayer] ? kInterface + 2 : kInterface + 1;
					}
				}
				else { // no K gap
					// here, we read a grid interface by interface. Each interface is read
					// in i then j direction
					cout << "INTERFACE BY INTERFACE" << std::endl;

					for (unsigned int kInterface = 0; kInterface < ijkGrid->getKCellCount(); kInterface++) {
						cout << "INTERFACE: " << kInterface << std::endl;

						std::unique_ptr<double[]> interfaceXyzPoints(new double[ijkGrid->getXyzPointCountOfKInterface() * 3]);
						ijkGrid->getXyzPointsOfKInterface(kInterface, interfaceXyzPoints.get());

						for (unsigned int j = 0; j < ijkGrid->getJCellCount(); j++) {
							for (unsigned int i = 0; i < ijkGrid->getICellCount(); i++) {
								cout << "CELL (" << i << ", " << j << ", " << kInterface << ")" << std::endl;

								uint64_t xyzPointIndex;
								double x, y, z;
								uint64_t indexShift = kInterface * ijkGrid->getXyzPointCountOfKInterface() * 3;

								// Corner (0, 0, 0)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kInterface, 0) * 3 - indexShift;
								x = interfaceXyzPoints[xyzPointIndex];
								y = interfaceXyzPoints[xyzPointIndex + 1];
								z = interfaceXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (0, 0, 0): " << x << " " << y << " " << z << std::endl;

								// Corner (1, 0, 0)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kInterface, 1) * 3 - indexShift;
								x = interfaceXyzPoints[xyzPointIndex];
								y = interfaceXyzPoints[xyzPointIndex + 1];
								z = interfaceXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (1, 0, 0): " << x << " " << y << " " << z << std::endl;

								// Corner (1, 1, 0)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kInterface, 2) * 3 - indexShift;
								x = interfaceXyzPoints[xyzPointIndex];
								y = interfaceXyzPoints[xyzPointIndex + 1];
								z = interfaceXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (1, 1, 0): " << x << " " << y << " " << z << std::endl;

								// Corner (0, 1, 0)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kInterface, 3) * 3 - indexShift;
								x = interfaceXyzPoints[xyzPointIndex];
								y = interfaceXyzPoints[xyzPointIndex + 1];
								z = interfaceXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (0, 1, 0): " << x << " " << y << " " << z << std::endl;

							}
						}
					}

					// last interface differs from the other because of  getXyzPointIndexFromCellCorner usage
					cout << "INTERFACE: " << ijkGrid->getKCellCount() << std::endl;

					std::unique_ptr<double[]> interfaceXyzPoints(new double[ijkGrid->getXyzPointCountOfKInterface() * 3]);
					ijkGrid->getXyzPointsOfKInterface(ijkGrid->getKCellCount(), interfaceXyzPoints.get());

					for (unsigned int i = 0; i < ijkGrid->getICellCount(); i++)
					{
						for (unsigned int j = 0; j < ijkGrid->getJCellCount(); j++)
						{
							cout << "CELL (" << i << ", " << j << ", " << ijkGrid->getKCellCount() - 1 << ")" << std::endl;

							uint64_t xyzPointIndex;
							double x, y, z;
							uint64_t indexShift = ijkGrid->getKCellCount() * ijkGrid->getXyzPointCountOfKInterface() * 3;

							// Corner (0, 0, 1)
							xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, ijkGrid->getKCellCount() - 1, 4) * 3 - indexShift;
							x = interfaceXyzPoints[xyzPointIndex];
							y = interfaceXyzPoints[xyzPointIndex + 1];
							z = interfaceXyzPoints[xyzPointIndex + 2];
							cout << "CORNER (0, 0, 1): " << x << " " << y << " " << z << std::endl;

							// Corner (1, 0, 1)
							xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, ijkGrid->getKCellCount() - 1, 5) * 3 - indexShift;
							x = interfaceXyzPoints[xyzPointIndex];
							y = interfaceXyzPoints[xyzPointIndex + 1];
							z = interfaceXyzPoints[xyzPointIndex + 2];
							cout << "CORNER (1, 0, 1): " << x << " " << y << " " << z << std::endl;

							// Corner (1, 1, 1)
							xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, ijkGrid->getKCellCount() - 1, 6) * 3 - indexShift;
							x = interfaceXyzPoints[xyzPointIndex];
							y = interfaceXyzPoints[xyzPointIndex + 1];
							z = interfaceXyzPoints[xyzPointIndex + 2];
							cout << "CORNER (1, 1, 1): " << x << " " << y << " " << z << std::endl;

							// Corner (0, 1, 1)
							xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, ijkGrid->getKCellCount() - 1, 7) * 3 - indexShift;
							x = interfaceXyzPoints[xyzPointIndex];
							y = interfaceXyzPoints[xyzPointIndex + 1];
							z = interfaceXyzPoints[xyzPointIndex + 2];
							cout << "CORNER (0, 1, 1): " << x << " " << y << " " << z << std::endl;
						}
					}

					// here, we read a grid layer by layer. Each layer is read in i,
					// then j direction.
					cout << "--------------------------------------------------" << std::endl;
					cout << "LAYER BY LAYER" << std::endl;

					for (unsigned int kInterface = 0; kInterface < ijkGrid->getKCellCount(); kInterface++)
					{
						cout << "LAYER: " << kInterface << std::endl;

						std::unique_ptr<double[]> layerXyzPoints(new double[ijkGrid->getXyzPointCountOfKInterface() * 3 * 2]);
						ijkGrid->getXyzPointsOfKInterfaceSequence(kInterface, kInterface + 1, layerXyzPoints.get());

						for (unsigned int j = 0; j < ijkGrid->getJCellCount(); j++)
						{
							for (unsigned int i = 0; i < ijkGrid->getICellCount(); i++)
							{
								cout << "CELL (" << i << ", " << j << ", " << kInterface << ")" << std::endl;

								uint64_t xyzPointIndex;
								double x, y, z;
								uint64_t indexShift = kInterface * ijkGrid->getXyzPointCountOfKInterface() * 3;

								// Corner (0, 0, 0)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kInterface, 0) * 3 - indexShift;
								x = layerXyzPoints[xyzPointIndex];
								y = layerXyzPoints[xyzPointIndex + 1];
								z = layerXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (0, 0, 0): " << x << " " << y << " " << z << std::endl;

								// Corner (1, 0, 0)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kInterface, 1) * 3 - indexShift;
								x = layerXyzPoints[xyzPointIndex];
								y = layerXyzPoints[xyzPointIndex + 1];
								z = layerXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (1, 0, 0): " << x << " " << y << " " << z << std::endl;

								// Corner (1, 1, 0)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kInterface, 2) * 3 - indexShift;
								x = layerXyzPoints[xyzPointIndex];
								y = layerXyzPoints[xyzPointIndex + 1];
								z = layerXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (1, 1, 0): " << x << " " << y << " " << z << std::endl;

								// Corner (0, 1, 0)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kInterface, 3) * 3 - indexShift;
								x = layerXyzPoints[xyzPointIndex];
								y = layerXyzPoints[xyzPointIndex + 1];
								z = layerXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (0, 1, 0): " << x << " " << y << " " << z << std::endl;

								// Corner (0, 0, 1)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kInterface, 4) * 3 - indexShift;
								x = layerXyzPoints[xyzPointIndex];
								y = layerXyzPoints[xyzPointIndex + 1];
								z = layerXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (0, 0, 1): " << x << " " << y << " " << z << std::endl;

								// Corner (1, 0, 1)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kInterface, 5) * 3 - indexShift;
								x = layerXyzPoints[xyzPointIndex];
								y = layerXyzPoints[xyzPointIndex + 1];
								z = layerXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (1, 0, 1): " << x << " " << y << " " << z << std::endl;

								// Corner (1, 1, 1)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kInterface, 6) * 3 - indexShift;
								x = layerXyzPoints[xyzPointIndex];
								y = layerXyzPoints[xyzPointIndex + 1];
								z = layerXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (1, 1, 1): " << x << " " << y << " " << z << std::endl;

								// Corner (0, 1, 1)
								xyzPointIndex = ijkGrid->getXyzPointIndexFromCellCorner(i, j, kInterface, 7) * 3 - indexShift;
								x = layerXyzPoints[xyzPointIndex];
								y = layerXyzPoints[xyzPointIndex + 1];
								z = layerXyzPoints[xyzPointIndex + 2];
								cout << "CORNER (0, 1, 1): " << x << " " << y << " " << z << std::endl;
							}
						}
					}
				}

				ijkGrid->unloadSplitInformation();

			}
			else
				cout << "Only explicit and parametric geometry is handled yet" << std::endl;
		}
	}
	cout << endl << "END: IJK GRID REP (hyperslabbing)" << endl;
}

/**
* Display the cell geometry of an IJK grid block.
* @param ijkGrid			An IJK grid.
* @param iInterfaceStart	Sarting i interface of the block.
* @param iInterfaceEnd		Ending i interface of the block.
* @param jInterfaceStart	Sarting j interface of the block.
* @param jInterfaceEnd		Ending j interface of the block.
* @param kInterfaceStart	Sarting k interface of the block.
* @param kInterfaceEnd		Ending k interface of the block.
* @param xyzPoints			The geometry of the block.
*/
void displayBlockCellGeometry(RESQML2_NS::AbstractIjkGridRepresentation* ijkGrid,
	unsigned int iInterfaceStart, unsigned int iInterfaceEnd,
	unsigned int jInterfaceStart, unsigned int jInterfaceEnd,
	unsigned int kInterfaceStart, unsigned int kInterfaceEnd,
	double* xyzPoints)
{
	if (xyzPoints == nullptr)
		throw invalid_argument("xyzPoints == nullptr");

	unsigned kLayerStart = kInterfaceStart;
	unsigned kLayerEnd = kInterfaceEnd - 1;
	unsigned int kInterfaceEndLayer;
	bool kInterfaceEndIsTop;

	if (ijkGrid->getKGapsCount() > 0) {
		std::unique_ptr<bool[]> gapAfterLayer(new bool[ijkGrid->getKCellCount() - 1]);
		ijkGrid->getKGaps(gapAfterLayer.get());

		unsigned int kInterface = 0;
		unsigned int kInterfaceStartLayer;
		bool kInterfaceStartIsBottom;
		for (unsigned int kLayer = 0; kLayer < ijkGrid->getKCellCount(); kLayer++) {
			if (kInterfaceStart == kInterface) {
				kInterfaceStartLayer = kLayer;
				kInterfaceStartIsBottom = true;
			}
			else if (kInterfaceStart == kInterface + 1) {
				kInterfaceStartLayer = kLayer;
				kInterfaceStartIsBottom = false;
			}

			if (kInterfaceEnd == kInterface) {
				kInterfaceEndLayer = kLayer;
				kInterfaceEndIsTop = false;
				break;
			}
			else if (kInterfaceEnd == kInterface + 1) {
				kInterfaceEndLayer = kLayer;
				kInterfaceEndIsTop = true;
				break;
			}

			kInterface = gapAfterLayer[kLayer] ? kInterface + 2 : kInterface + 1;
		}

		kLayerStart = kInterfaceStartLayer;
		if (!kInterfaceStartIsBottom) {
			for (unsigned int j = jInterfaceStart; j < jInterfaceEnd; j++)
			{
				for (unsigned int i = iInterfaceStart; i < iInterfaceEnd; i++)
				{
					cout << "CELL (" << i << ", " << j << ", " << kInterfaceStartLayer << ")" << std::endl;

					double x, y, z;

					// Corner (0, 0, 1)
					ijkGrid->getXyzPointOfBlockFromCellCorner(i, j, kInterfaceStartLayer, 4, xyzPoints, x, y, z);
					cout << "CORNER (0, 0, 1): " << x << " " << y << " " << z << std::endl;

					// Corner (1, 0, 1)
					ijkGrid->getXyzPointOfBlockFromCellCorner(i, j, kInterfaceStartLayer, 5, xyzPoints, x, y, z);
					cout << "CORNER (1, 0, 1): " << x << " " << y << " " << z << std::endl;

					// Corner (1, 1, 1)
					ijkGrid->getXyzPointOfBlockFromCellCorner(i, j, kInterfaceStartLayer, 6, xyzPoints, x, y, z);
					cout << "CORNER (1, 1, 1): " << x << " " << y << " " << z << std::endl;

					// Corner (0, 1, 1)
					ijkGrid->getXyzPointOfBlockFromCellCorner(i, j, kInterfaceStartLayer, 7, xyzPoints, x, y, z);
					cout << "CORNER (0, 1, 1): " << x << " " << y << " " << z << std::endl;
				}
			}

			kLayerStart++;
		}

		kLayerEnd = kInterfaceEndLayer;
		if (!kInterfaceEndIsTop) {
			kLayerEnd--;
		}
	}

	for (unsigned int k = kLayerStart; k <= kLayerEnd; k++)
	{
		cout << "LAYER: " << k << std::endl;

		for (unsigned int j = jInterfaceStart; j < jInterfaceEnd; j++)
		{
			for (unsigned int i = iInterfaceStart; i < iInterfaceEnd; i++)
			{
				cout << "CELL (" << i << ", " << j << ", " << k << ")" << std::endl;

				double x, y, z;

				// Corner (0, 0, 0)
				ijkGrid->getXyzPointOfBlockFromCellCorner(i, j, k, 0, xyzPoints, x, y, z);
				cout << "CORNER (0, 0, 0): " << x << " " << y << " " << z << std::endl;

				// Corner (1, 0, 0)
				ijkGrid->getXyzPointOfBlockFromCellCorner(i, j, k, 1, xyzPoints, x, y, z);
				cout << "CORNER (1, 0, 0): " << x << " " << y << " " << z << std::endl;

				// Corner (1, 1, 0)
				ijkGrid->getXyzPointOfBlockFromCellCorner(i, j, k, 2, xyzPoints, x, y, z);
				cout << "CORNER (1, 1, 0): " << x << " " << y << " " << z << std::endl;

				// Corner (0, 1, 0)
				ijkGrid->getXyzPointOfBlockFromCellCorner(i, j, k, 3, xyzPoints, x, y, z);
				cout << "CORNER (0, 1, 0): " << x << " " << y << " " << z << std::endl;

				// Corner (0, 0, 1)
				ijkGrid->getXyzPointOfBlockFromCellCorner(i, j, k, 4, xyzPoints, x, y, z);
				cout << "CORNER (0, 0, 1): " << x << " " << y << " " << z << std::endl;

				// Corner (1, 0, 1)
				ijkGrid->getXyzPointOfBlockFromCellCorner(i, j, k, 5, xyzPoints, x, y, z);
				cout << "CORNER (1, 0, 1): " << x << " " << y << " " << z << std::endl;

				// Corner (1, 1, 1)
				ijkGrid->getXyzPointOfBlockFromCellCorner(i, j, k, 6, xyzPoints, x, y, z);
				cout << "CORNER (1, 1, 1): " << x << " " << y << " " << z << std::endl;

				// Corner (0, 1, 1)
				ijkGrid->getXyzPointOfBlockFromCellCorner(i, j, k, 7, xyzPoints, x, y, z);
				cout << "CORNER (0, 1, 1): " << x << " " << y << " " << z << std::endl;
			}
		}
	}

	if (ijkGrid->getKGapsCount()>0 && !kInterfaceEndIsTop && kInterfaceEnd != kInterfaceStart) {
		for (unsigned int j = jInterfaceStart; j < jInterfaceEnd; j++)
		{
			for (unsigned int i = iInterfaceStart; i < iInterfaceEnd; i++)
			{
				cout << "CELL (" << i << ", " << j << ", " << kInterfaceEndLayer << ")" << std::endl;

				double x, y, z;

				// Corner (0, 0, 0)
				ijkGrid->getXyzPointOfBlockFromCellCorner(i, j, kInterfaceEndLayer, 0, xyzPoints, x, y, z);
				cout << "CORNER (0, 0, 0): " << x << " " << y << " " << z << std::endl;

				// Corner (1, 0, 0)
				ijkGrid->getXyzPointOfBlockFromCellCorner(i, j, kInterfaceEndLayer, 1, xyzPoints, x, y, z);
				cout << "CORNER (1, 0, 0): " << x << " " << y << " " << z << std::endl;

				// Corner (1, 1, 0)
				ijkGrid->getXyzPointOfBlockFromCellCorner(i, j, kInterfaceEndLayer, 2, xyzPoints, x, y, z);
				cout << "CORNER (1, 1, 0): " << x << " " << y << " " << z << std::endl;

				// Corner (0, 1, 0)
				ijkGrid->getXyzPointOfBlockFromCellCorner(i, j, kInterfaceEndLayer, 3, xyzPoints, x, y, z);
				cout << "CORNER (0, 1, 0): " << x << " " << y << " " << z << std::endl;
			}
		}
	}
}

/**
* Deserialize IJK grid explicit representations packed in a given EPC document.
* This method read grid geometry block by using hyperslabbing methods. Each block is read
* layer by layer.
* @param pck	An EPC document containing the IJK grid to deserialize.
*/
void deserializeGridHyperslabbingBlock(const COMMON_NS::DataObjectRepository & pck)
{
	cout << endl << "BEGIN: IJK GRID REP (block hyperslabbing)" << endl;

	// ONE SUGAR
	RESQML2_NS::AbstractIjkGridRepresentation* ijkGrid = pck.getDataObjectByUuid<RESQML2_NS::AbstractIjkGridRepresentation>("e69bfe00-fa3d-11e5-b5eb-0002a5d5c51b");
	if (ijkGrid == nullptr) {
		return;
	}

	cout << "--------------------------------------------------" << std::endl;
	showAllMetadata(ijkGrid);
	cout << "--------------------------------------------------" << std::endl;

	ijkGrid->loadSplitInformation();

	unsigned int iInterfaceStart = 0;
	unsigned int iInterfaceEnd = 1;
	unsigned int jInterfaceStart = 0;
	unsigned int jInterfaceEnd = 1;
	unsigned int kInterfaceStart = 0;
	unsigned int kInterfaceEnd = 1;

	ijkGrid->loadBlockInformation(iInterfaceStart, iInterfaceEnd, jInterfaceStart, jInterfaceEnd, kInterfaceStart, kInterfaceEnd);

	uint64_t xyzPointCountOfBlock = ijkGrid->getXyzPointCountOfBlock();

	std::unique_ptr<double[]> xyzPoints(new double[xyzPointCountOfBlock * 3]);
	ijkGrid->getXyzPointsOfBlock(xyzPoints.get());

	// Keep for testing
	/*cout << "All xyz points:" << endl;
	for (unsigned int index = 0; index < xyzPointCountOfBlock; ++index)
	std::cout << "(" << xyzPoints[3 * index] << " " << xyzPoints[3 * index + 1] << " " << xyzPoints[3 * index + 2] << ") ";
	std::cout << std::endl;*/

	displayBlockCellGeometry(ijkGrid,
		iInterfaceStart, iInterfaceEnd,
		jInterfaceStart, jInterfaceEnd,
		kInterfaceStart, kInterfaceEnd,
		xyzPoints.get()
	);

	ijkGrid->unloadSplitInformation();

	// ONE SUGAR PARAMETRIC
	ijkGrid = pck.getDataObjectByUuid<RESQML2_NS::AbstractIjkGridRepresentation>("53bb70fe-2eef-4691-b4fe-14541e3a57eb");
	if (ijkGrid == nullptr) {
		return;
	}

	cout << "--------------------------------------------------" << std::endl;
	showAllMetadata(ijkGrid);
	cout << "--------------------------------------------------" << std::endl;

	ijkGrid->loadSplitInformation();

	ijkGrid->loadBlockInformation(iInterfaceStart, iInterfaceEnd, jInterfaceStart, jInterfaceEnd, kInterfaceStart, kInterfaceEnd);

	ijkGrid->getXyzPointsOfBlock(xyzPoints.get());

	// Keep for testing
	/*cout << "All xyz points:" << endl;
	for (unsigned int index = 0; index < xyzPointCountOfBlock; ++index)
	std::cout << "(" << xyzPoints[3 * index] << " " << xyzPoints[3 * index + 1] << " " << xyzPoints[3 * index + 2] << ") ";
	std::cout << std::endl;*/

	displayBlockCellGeometry(ijkGrid,
		iInterfaceStart, iInterfaceEnd,
		jInterfaceStart, jInterfaceEnd,
		kInterfaceStart, kInterfaceEnd,
		xyzPoints.get()
	);

	ijkGrid->unloadSplitInformation();

	// Four by Three by Two Left Handed (e96c2bde-e3ae-4d51-b078-a8e57fb1e667)
	ijkGrid = pck.getDataObjectByUuid<RESQML2_NS::AbstractIjkGridRepresentation>("e96c2bde-e3ae-4d51-b078-a8e57fb1e667");

	cout << std::endl;
	cout << "--------------------------------------------------" << std::endl;
	showAllMetadata(ijkGrid);
	cout << "--------------------------------------------------" << std::endl;

	ijkGrid->loadSplitInformation();

	// 2*3*2 sized block with:
	//
	// kInterface = 0
	//  -- ** ** --
	// |  *  *  *  |
	//  -- ** ** --
	// |  *  *  *  |
	//  -- ** ** --
	// |  *  *  *  |
	//  -- ** ** --
	//
	// kInterface = 1
	//  -- ** ** --
	// |  *  *  *  |
	//  -- ** ** --
	// |  *  *  *  |
	//  -- ** ** --
	// |  *  *  *  |
	//  -- ** ** --
	//
	// kInterface = 2
	//  -- ** ** --
	// |  *  *  *  |
	//  -- ** ** --
	// |  *  *  *  |
	//  -- ** ** --
	// |  *  *  *  |
	//  -- ** ** --

	std::cout << "block 2*3*2" << std::endl;

	iInterfaceStart = 1;
	iInterfaceEnd = 3;
	jInterfaceStart = 0;
	jInterfaceEnd = 3;
	kInterfaceStart = 0;
	kInterfaceEnd = 2;

	ijkGrid->loadBlockInformation(iInterfaceStart, iInterfaceEnd, jInterfaceStart, jInterfaceEnd, kInterfaceStart, kInterfaceEnd);

	xyzPointCountOfBlock = ijkGrid->getXyzPointCountOfBlock();

	xyzPoints = std::unique_ptr<double[]>(new double[xyzPointCountOfBlock * 3]);
	ijkGrid->getXyzPointsOfBlock(xyzPoints.get());

	displayBlockCellGeometry(ijkGrid,
		iInterfaceStart, iInterfaceEnd,
		jInterfaceStart, jInterfaceEnd,
		kInterfaceStart, kInterfaceEnd,
		xyzPoints.get()
	);

	cout << "--------------------------------------------------" << std::endl;

	// 1*1*1 sized block with:
	//
	// kInterface = 0
	//  -- -- -- --
	// |  |  |  |  |
	//  -- -- -- --
	// |  |  |  |  |
	//  -- -- -- --
	// |  |  |  |  |
	//  -- -- -- --
	//
	// kInterface = 1
	//  -- -- -- --
	// |  |  |  |  |
	//  -- -- ** --
	// |  |  *  *  |
	//  -- -- ** --
	// |  |  |  |  |
	//  -- -- -- --
	//
	// kInterface = 2
	//  -- -- -- --
	// |  |  |  |  |
	//  -- -- ** --
	// |  |  *  *  |
	//  -- -- ** --
	// |  |  |  |  |
	//  -- -- -- --

	std::cout << "block 1*1*1" << std::endl;

	iInterfaceStart = 2;
	iInterfaceEnd = 3;
	jInterfaceStart = 1;
	jInterfaceEnd = 2;
	kInterfaceStart = 1;
	kInterfaceEnd = 2;

	ijkGrid->loadBlockInformation(iInterfaceStart, iInterfaceEnd, jInterfaceStart, jInterfaceEnd, kInterfaceStart, kInterfaceEnd);

	xyzPointCountOfBlock = ijkGrid->getXyzPointCountOfBlock();

	xyzPoints = std::unique_ptr<double[]>(new double[xyzPointCountOfBlock * 3]);
	ijkGrid->getXyzPointsOfBlock(xyzPoints.get());

	displayBlockCellGeometry(ijkGrid,
		iInterfaceStart, iInterfaceEnd,
		jInterfaceStart, jInterfaceEnd,
		kInterfaceStart, kInterfaceEnd,
		xyzPoints.get()
	);

	cout << "--------------------------------------------------" << std::endl;

	// 4*3*2 sized block with:
	//
	// kInterface = 0
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	//
	// kInterface = 1
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	//
	// kInterface = 2
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **

	std::cout << "block 4*3*2" << std::endl;

	iInterfaceStart = 0;
	iInterfaceEnd = 4;
	jInterfaceStart = 0;
	jInterfaceEnd = 3;
	kInterfaceStart = 0;
	kInterfaceEnd = 2;

	ijkGrid->loadBlockInformation(iInterfaceStart, iInterfaceEnd, jInterfaceStart, jInterfaceEnd, kInterfaceStart, kInterfaceEnd);

	xyzPointCountOfBlock = ijkGrid->getXyzPointCountOfBlock();

	xyzPoints = std::unique_ptr<double[]>(new double[xyzPointCountOfBlock * 3]);
	ijkGrid->getXyzPointsOfBlock(xyzPoints.get());

	displayBlockCellGeometry(ijkGrid,
		iInterfaceStart, iInterfaceEnd,
		jInterfaceStart, jInterfaceEnd,
		kInterfaceStart, kInterfaceEnd,
		xyzPoints.get()
	);

	ijkGrid->unloadSplitInformation();

	// Four faulted sugar cubes(parametric geometry) (37c45c00-fa3e-11e5-a21e-0002a5d5c51b)
	ijkGrid = pck.getDataObjectByUuid<RESQML2_NS::AbstractIjkGridRepresentation>("37c45c00-fa3e-11e5-a21e-0002a5d5c51b");

	cout << std::endl;
	cout << "--------------------------------------------------" << std::endl;
	showAllMetadata(ijkGrid);
	cout << "--------------------------------------------------" << std::endl;

	ijkGrid->loadSplitInformation();

	// 1*1*1 sized block with:
	//
	// kInterface = 0
	//  -- -- 
	// |  |  |
	//  -- --
	//
	// kInterface = 1
	//  -- ** 
	// |  *  *
	//  -- **
	//
	// kInterface = 2
	//  -- ** 
	// |  *  *
	//  -- **

	std::cout << "block 1*1*1" << std::endl;

	iInterfaceStart = 1;
	iInterfaceEnd = 2;
	jInterfaceStart = 0;
	jInterfaceEnd = 1;
	kInterfaceStart = 1;
	kInterfaceEnd = 2;

	ijkGrid->loadBlockInformation(iInterfaceStart, iInterfaceEnd, jInterfaceStart, jInterfaceEnd, kInterfaceStart, kInterfaceEnd);

	xyzPointCountOfBlock = ijkGrid->getXyzPointCountOfBlock();

	xyzPoints = std::unique_ptr<double[]>(new double[xyzPointCountOfBlock * 3]);
	ijkGrid->getXyzPointsOfBlock(xyzPoints.get());

	displayBlockCellGeometry(ijkGrid,
		iInterfaceStart, iInterfaceEnd,
		jInterfaceStart, jInterfaceEnd,
		kInterfaceStart, kInterfaceEnd,
		xyzPoints.get()
	);

	cout << "--------------------------------------------------" << std::endl;

	// 1*1*2 sized block with:
	//
	// kInterface = 0
	//  ** -- 
	// *  *  |
	//  ** --
	//
	// kInterface = 1
	//  ** -- 
	// *  *  |
	//  ** --
	//
	// kInterface = 2
	//  ** -- 
	// *  *  |
	//  ** --

	std::cout << "block 1*1*2" << std::endl;

	iInterfaceStart = 0;
	iInterfaceEnd = 1;
	jInterfaceStart = 0;
	jInterfaceEnd = 1;
	kInterfaceStart = 0;
	kInterfaceEnd = 2;

	ijkGrid->loadBlockInformation(iInterfaceStart, iInterfaceEnd, jInterfaceStart, jInterfaceEnd, kInterfaceStart, kInterfaceEnd);

	xyzPointCountOfBlock = ijkGrid->getXyzPointCountOfBlock();

	xyzPoints = std::unique_ptr<double[]>(new double[xyzPointCountOfBlock * 3]);
	ijkGrid->getXyzPointsOfBlock(xyzPoints.get());

	displayBlockCellGeometry(ijkGrid,
		iInterfaceStart, iInterfaceEnd,
		jInterfaceStart, jInterfaceEnd,
		kInterfaceStart, kInterfaceEnd,
		xyzPoints.get()
	);

	ijkGrid->unloadSplitInformation();

	// Four faulted sugar cubes (straight parametric geometry) (f68235af-1d7a-4e24-93a8-10739b15ca40)
	ijkGrid = (pck.getDataObjectByUuid<RESQML2_NS::AbstractIjkGridRepresentation>("f68235af-1d7a-4e24-93a8-10739b15ca40"));

	cout << std::endl;
	cout << "--------------------------------------------------" << std::endl;
	showAllMetadata(ijkGrid);
	cout << "--------------------------------------------------" << std::endl;

	ijkGrid->loadSplitInformation();

	// 1*1*1 sized block with:
	//
	// kInterface = 0
	//  -- -- 
	// |  |  |
	//  -- --
	//
	// kInterface = 1
	//  -- ** 
	// |  *  *
	//  -- **
	//
	// kInterface = 2
	//  -- ** 
	// |  *  *
	//  -- **

	std::cout << "block 1*1*1" << std::endl;

	iInterfaceStart = 1;
	iInterfaceEnd = 2;
	jInterfaceStart = 0;
	jInterfaceEnd = 1;
	kInterfaceStart = 1;
	kInterfaceEnd = 2;

	ijkGrid->loadBlockInformation(iInterfaceStart, iInterfaceEnd, jInterfaceStart, jInterfaceEnd, kInterfaceStart, kInterfaceEnd);

	xyzPointCountOfBlock = ijkGrid->getXyzPointCountOfBlock();

	xyzPoints = std::unique_ptr<double[]>(new double[xyzPointCountOfBlock * 3]);
	ijkGrid->getXyzPointsOfBlock(xyzPoints.get());

	// Keep for testing
	/*cout << "All xyz points:" << endl;
	for (unsigned int index = 0; index < xyzPointCountOfBlock; ++index)
	std::cout << "(" << xyzPoints[3 * index] << " " << xyzPoints[3 * index + 1] << " " << xyzPoints[3 * index + 2] << ") ";
	std::cout << std::endl;*/

	displayBlockCellGeometry(ijkGrid,
		iInterfaceStart, iInterfaceEnd,
		jInterfaceStart, jInterfaceEnd,
		kInterfaceStart, kInterfaceEnd,
		xyzPoints.get()
	);

	cout << "--------------------------------------------------" << std::endl;

	// 1*1*2 sized block with:
	//
	// kInterface = 0
	//  ** -- 
	// *  *  |
	//  ** --
	//
	// kInterface = 1
	//  ** -- 
	// *  *  |
	//  ** --
	//
	// kInterface = 2
	//  ** -- 
	// *  *  |
	//  ** --

	std::cout << "block 1*1*2" << std::endl;

	iInterfaceStart = 0;
	iInterfaceEnd = 1;
	jInterfaceStart = 0;
	jInterfaceEnd = 1;
	kInterfaceStart = 0;
	kInterfaceEnd = 2;

	ijkGrid->loadBlockInformation(iInterfaceStart, iInterfaceEnd, jInterfaceStart, jInterfaceEnd, kInterfaceStart, kInterfaceEnd);

	xyzPointCountOfBlock = ijkGrid->getXyzPointCountOfBlock();

	xyzPoints = std::unique_ptr<double[]>(new double[xyzPointCountOfBlock * 3]);
	ijkGrid->getXyzPointsOfBlock(xyzPoints.get());

	displayBlockCellGeometry(ijkGrid,
		iInterfaceStart, iInterfaceEnd,
		jInterfaceStart, jInterfaceEnd,
		kInterfaceStart, kInterfaceEnd,
		xyzPoints.get()
	);

	cout << "--------------------------------------------------" << std::endl;

	// 2*1*2 sized block with:
	//
	// kInterface = 0
	//  ** ** 
	// *  *  *
	//  ** **
	//
	// kInterface = 1
	//  ** ** 
	// *  *  *
	//  ** **
	//
	// kInterface = 2
	//  ** ** 
	// *  *  *
	//  ** **

	std::cout << "block 2*1*2" << std::endl;

	iInterfaceStart = 0;
	iInterfaceEnd = 2;
	jInterfaceStart = 0;
	jInterfaceEnd = 1;
	kInterfaceStart = 0;
	kInterfaceEnd = 2;

	ijkGrid->loadBlockInformation(iInterfaceStart, iInterfaceEnd, jInterfaceStart, jInterfaceEnd, kInterfaceStart, kInterfaceEnd);

	xyzPointCountOfBlock = ijkGrid->getXyzPointCountOfBlock();

	xyzPoints = std::unique_ptr<double[]>(new double[xyzPointCountOfBlock * 3]);
	ijkGrid->getXyzPointsOfBlock(xyzPoints.get());

	displayBlockCellGeometry(ijkGrid,
		iInterfaceStart, iInterfaceEnd,
		jInterfaceStart, jInterfaceEnd,
		kInterfaceStart, kInterfaceEnd,
		xyzPoints.get()
	);

	ijkGrid->unloadSplitInformation();

	// 4*3*2 explicit grid 4fc004e1-0f7d-46a8-935e-588f790a6f84
	ijkGrid = (pck.getDataObjectByUuid<RESQML2_NS::AbstractIjkGridRepresentation>("4fc004e1-0f7d-46a8-935e-588f790a6f84"));

	cout << std::endl;
	cout << "--------------------------------------------------" << std::endl;
	showAllMetadata(ijkGrid);
	cout << "--------------------------------------------------" << std::endl;

	ijkGrid->loadSplitInformation();

	// 4*3*2 sized block with (complete grid):
	//
	// kInterface = 0
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	//
	// kInterface = 1
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	//
	// kInterface = 2
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **

	std::cout << "block 4*3*2" << std::endl;

	iInterfaceStart = 0;
	iInterfaceEnd = 4;
	jInterfaceStart = 0;
	jInterfaceEnd = 3;
	kInterfaceStart = 0;
	kInterfaceEnd = 2;

	ijkGrid->loadBlockInformation(iInterfaceStart, iInterfaceEnd, jInterfaceStart, jInterfaceEnd, kInterfaceStart, kInterfaceEnd);

	xyzPointCountOfBlock = ijkGrid->getXyzPointCountOfBlock();

	xyzPoints = std::unique_ptr<double[]>(new double[xyzPointCountOfBlock * 3]);
	ijkGrid->getXyzPointsOfBlock(xyzPoints.get());

	displayBlockCellGeometry(ijkGrid,
		iInterfaceStart, iInterfaceEnd,
		jInterfaceStart, jInterfaceEnd,
		kInterfaceStart, kInterfaceEnd,
		xyzPoints.get()
	);

	ijkGrid->unloadSplitInformation();

	// 4*3*2 explicit grid with gap layer c14755a5-e3b3-4272-99e5-fc20993b79a0
	ijkGrid = (pck.getDataObjectByUuid<RESQML2_NS::AbstractIjkGridRepresentation>("c14755a5-e3b3-4272-99e5-fc20993b79a0"));

	cout << std::endl;
	cout << "--------------------------------------------------" << std::endl;
	showAllMetadata(ijkGrid);
	cout << "--------------------------------------------------" << std::endl;

	ijkGrid->loadSplitInformation();

	// 4*3*3 sized block with (complete grid):
	//
	// kInterface = 0
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	//
	// kInterface = 1
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	//
	// kInterface = 2
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	//
	// kInterface = 3
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **
	// *  *  *  *  *
	//  ** ** ** **

	std::cout << "block 4*3*3" << std::endl;

	iInterfaceStart = 0;
	iInterfaceEnd = 4;
	jInterfaceStart = 0;
	jInterfaceEnd = 3;
	kInterfaceStart = 0;
	kInterfaceEnd = 3;

	ijkGrid->loadBlockInformation(iInterfaceStart, iInterfaceEnd, jInterfaceStart, jInterfaceEnd, kInterfaceStart, kInterfaceEnd);

	xyzPointCountOfBlock = ijkGrid->getXyzPointCountOfBlock();

	xyzPoints = std::unique_ptr<double[]>(new double[xyzPointCountOfBlock * 3]);
	ijkGrid->getXyzPointsOfBlock(xyzPoints.get());

	displayBlockCellGeometry(ijkGrid,
		iInterfaceStart, iInterfaceEnd,
		jInterfaceStart, jInterfaceEnd,
		kInterfaceStart, kInterfaceEnd,
		xyzPoints.get()
	);

	cout << "--------------------------------------------------" << std::endl;

	// 2*1*1 sized block with
	//
	// kInterface = 0
	//  -- -- -- --
	// |  |  |  |  |
	//  -- -- -- --
	// |  |  |  |  |
	//  -- -- -- --
	// |  |  |  |  |
	//  -- -- -- --
	//
	// kInterface = 1
	//  -- -- -- --
	// |  |  |  |  |
	//  -- ** ** --
	// |  *  *  *  |
	//  -- ** ** --
	// |  |  |  |  |
	//  -- -- -- --
	//
	// kInterface = 2
	//  -- -- -- --
	// |  |  |  |  |
	//  -- ** ** --
	// |  *  *  *  |
	//  -- ** ** --
	// |  |  |  |  |
	//  -- -- -- --
	//
	// kInterface = 3
	//  -- -- -- --
	// |  |  |  |  |
	//  -- -- -- --
	// |  |  |  |  |
	//  -- -- -- --
	// |  |  |  |  |
	//  -- -- -- --

	std::cout << "block 2*1*1" << std::endl;

	iInterfaceStart = 1;
	iInterfaceEnd = 3;
	jInterfaceStart = 1;
	jInterfaceEnd = 2;
	kInterfaceStart = 1;
	kInterfaceEnd = 2;

	ijkGrid->loadBlockInformation(iInterfaceStart, iInterfaceEnd, jInterfaceStart, jInterfaceEnd, kInterfaceStart, kInterfaceEnd);

	xyzPointCountOfBlock = ijkGrid->getXyzPointCountOfBlock();

	xyzPoints = std::unique_ptr<double[]>(new double[xyzPointCountOfBlock * 3]);
	ijkGrid->getXyzPointsOfBlock(xyzPoints.get());

	displayBlockCellGeometry(ijkGrid,
		iInterfaceStart, iInterfaceEnd,
		jInterfaceStart, jInterfaceEnd,
		kInterfaceStart, kInterfaceEnd,
		xyzPoints.get()
	);

	ijkGrid->unloadSplitInformation();

	cout << endl << "END: IJK GRID REP (block hyperslabbing)" << endl;
}

/**
* This method provides a time comparison betweeen hyperslabbed and non-hyperslabbed versions of IJK grid geometry reading.
* This method is relevant only if the pillar information loading is forced at each
* IjkGridParametricRepresentation::getXyzPointsOfKInterfaceSequenceOfPatch call!
* @param ijkGrid	an IJK grid representation
* @param nbIter	number of geometry reading iteration
*/
void ijkGridHyperslabingTiming(RESQML2_NS::AbstractIjkGridRepresentation* ijkGrid, unsigned int nbIter)
{
	if (ijkGrid == nullptr) {
		throw invalid_argument("discretePropertyHyperslabingTiming: ijkGrid is nullptr.");
	}

	cout << endl << "BEGIN: IJK GRID REP (hyperslabbed and non-hyperslabbed geometry reading comparison)" << std::endl << std::endl;
	cout.precision(17);

	ijkGrid->loadSplitInformation();
	std::unique_ptr<double[]> xyzPoints(new double[ijkGrid->getXyzPointCountOfAllPatches() * 3]);

	unsigned int iCellCount = ijkGrid->getICellCount();
	unsigned int jCellCount = ijkGrid->getJCellCount();
	unsigned int kCellCount = ijkGrid->getKCellCount();

	std::cout << "iCellCount = " << iCellCount << std::endl;
	std::cout << "jCellCount = " << jCellCount << std::endl;
	std::cout << "kCellCount = " << kCellCount << std::endl;

	ijkGrid->loadBlockInformation(0, iCellCount, 0, jCellCount, 0, kCellCount);

	time_t timeStart, timeEnd;
	clock_t nonHyperslabClockDuration = 0;
	clock_t hyperslabClockDuration = 0;
	clock_t blockHyperslabClockDuration = 0;
	double nonHyperslabTimeDuration = 0;
	double hyperslabTimeDuration = 0;
	double blockHyperslabTimeDuration = 0;

	const unsigned int smoothingConstant = 10;

	for (unsigned int i = 0; i < smoothingConstant; ++i)
	{
		clock_t clockStart, clockEnd;

		// non hyperslabbing
		clockStart = clock();
		time(&timeStart);
		for (unsigned int n = 0; n < nbIter; ++n)
			ijkGrid->getXyzPointsOfPatch(0, xyzPoints.get());
		clockEnd = clock();
		time(&timeEnd);
		nonHyperslabClockDuration += clockEnd - clockStart;
		nonHyperslabTimeDuration += difftime(timeEnd, timeStart);

		//// keep track for debug
		//for (unsigned int i = 0; i < ijkGrid->getXyzPointCountOfAllPatches(); ++i)
		//	std::cout << "(" << xyzPoints[i] << ", " << xyzPoints[i + 1] << ", " << xyzPoints[i + 2] << ")";
		//std::cout << std::endl;

		// k interface sequence hyperslabbing
		clockStart = clock();
		time(&timeStart);
		for (unsigned int n = 0; n < nbIter; ++n)
			ijkGrid->getXyzPointsOfKInterfaceSequence(0, kCellCount, xyzPoints.get());
		clockEnd = clock();
		time(&timeEnd);
		hyperslabClockDuration += clockEnd - clockStart;
		hyperslabTimeDuration += difftime(timeEnd, timeStart);

		// block hyperslabbing
		clockStart = clock();
		time(&timeStart);
		for (unsigned int n = 0; n < nbIter; ++n)
			ijkGrid->getXyzPointsOfBlock(xyzPoints.get());
		clockEnd = clock();
		time(&timeEnd);
		blockHyperslabClockDuration += clockEnd - clockStart;
		blockHyperslabTimeDuration += difftime(timeEnd, timeStart);
	}

	nonHyperslabClockDuration /= smoothingConstant;
	hyperslabClockDuration /= smoothingConstant;
	blockHyperslabClockDuration /= smoothingConstant;
	nonHyperslabTimeDuration /= smoothingConstant;
	hyperslabTimeDuration /= smoothingConstant;
	blockHyperslabTimeDuration /= smoothingConstant;

	// results
	std::cout << "Be careful: in the case of parametric grids, following results are relevant only if pillar information" << std::endl;
	std::cout << " loading is forced at each call of IjkGridParametricRepresentation::getXyzPointsOfKInterfaceSequenceOfPatch method" << std::endl;
	std::cout << "Non hyperslab:	geometry of " << ijkGrid->getTitle() << " have been read " << nbIter << " times in " << nonHyperslabClockDuration << " ticks (CPU time)" << std::endl;
	std::cout << "k-interface hyperslab: geometry of " << ijkGrid->getTitle() << " have been read " << nbIter << " times in " << hyperslabClockDuration << " ticks (CPU time)" << std::endl;
	std::cout << "Block hperslab: geometry of " << ijkGrid->getTitle() << " have been read " << nbIter << " times in " << blockHyperslabClockDuration << " ticks (CPU time)" << std::endl;
	std::cout << "k-interface hyperslab version took " << (hyperslabClockDuration * 100) / nonHyperslabClockDuration << " % of non hyperslab version" << std::endl;
	std::cout << "block hyperslab version took " << (blockHyperslabClockDuration * 100) / nonHyperslabClockDuration << " % of non hyperslab version" << std::endl;
	std::cout << "block hyperslab version took " << (blockHyperslabClockDuration * 100) / hyperslabClockDuration << " % of k-interface hyperslab version" << std::endl << std::endl;;

	std::cout << "Non hyperslab: geometry of " << ijkGrid->getTitle() << " have been read " << nbIter << " times in " << fixed << nonHyperslabTimeDuration << " seconds" << std::endl;
	std::cout << "k-interface hyperslab: geometry of " << ijkGrid->getTitle() << " have been read " << nbIter << " times in " << fixed << hyperslabTimeDuration << " seconds" << std::endl;
	std::cout << "block hyperslab: geometry of " << ijkGrid->getTitle() << " have been read " << nbIter << " times in " << fixed << blockHyperslabTimeDuration << " seconds" << std::endl;
	std::cout << "k-interface hyperslab version took " << (hyperslabTimeDuration * 100) / nonHyperslabTimeDuration << " % of non hyperslab version" << std::endl;
	std::cout << "block hyperslab version took " << (blockHyperslabTimeDuration * 100) / nonHyperslabTimeDuration << " % of non hyperslab version" << std::endl;
	std::cout << "block hyperslab version took " << (blockHyperslabTimeDuration * 100) / hyperslabTimeDuration << " % of k-interface hyperslab version" << std::endl;

	ijkGrid->unloadSplitInformation();

	std::cout << endl << "END: IJK GRID REP (hyperslabbed and non-hyperslabbed geometry reading comparison)" << std::endl;
}

/**
* This method provides a time comparison betweeen hyperslabbed and non-hyperslabbed versions of IJK grid discrete property reading.
* It is assumed that poperty is cell centric.
* @param ijkGrid	an IJK grid representation
* @param prop		a dicrete property
* @param nbIter		number of geometry reading iteration
*/
void discretePropertyHyperslabingTiming(RESQML2_NS::AbstractIjkGridRepresentation* ijkGrid, RESQML2_NS::DiscreteProperty* prop, unsigned int nbIter)
{
	if (ijkGrid == nullptr)
		throw invalid_argument("discretePropertyHyperslabingTiming: ijkGrid is nullptr.");
	if (prop == nullptr)
		throw invalid_argument("discretePropertyHyperslabingTiming: prop is nullptr.");

	std::cout << endl << "BEGIN: IJK GRID REP (hyperslabbed and non-hyperslabbed property reading comparison)" << std::endl << std::endl;
	std::cout.precision(17);

	int* values = new int[prop->getValuesCountOfPatch(0)];

	unsigned long long* numValuesInEachDimension = new unsigned long long[3];
	numValuesInEachDimension[0] = ijkGrid->getKCellCount();
	numValuesInEachDimension[1] = ijkGrid->getJCellCount();
	numValuesInEachDimension[2] = ijkGrid->getICellCount();
	unsigned long long* offsetInEachDimension = new unsigned long long[3];
	offsetInEachDimension[0] = 0;
	offsetInEachDimension[1] = 0;
	offsetInEachDimension[2] = 0;

	time_t timeStart, timeEnd;
	clock_t nonHyperslabClockDuration = 0;
	double nonHyperslabTImeDuration = 0;
	clock_t hyperslabClockDuration = 0;
	double hyperslabTimeDuration = 0;

	const unsigned int smoothingConstant = 20;

	for (unsigned int i = 0; i < smoothingConstant; ++i)
	{
		clock_t clockStart, clockEnd;

		// non hyperslabbing
		clockStart = clock();
		time(&timeStart);
		for (unsigned int n = 0; n < nbIter; ++n)
			prop->getIntValuesOfPatch(0, values);
		clockEnd = clock();
		time(&timeEnd);
		nonHyperslabClockDuration = clockEnd - clockStart;
		nonHyperslabTImeDuration = difftime(timeEnd, timeStart);

		// hyperslabbing
		clockStart = clock();
		time(&timeStart);
		for (unsigned int n = 0; n < nbIter; ++n)
			prop->getIntValuesOfPatch(0, values, numValuesInEachDimension, offsetInEachDimension, 3);
		clockEnd = clock();
		time(&timeEnd);
		hyperslabClockDuration = clockEnd - clockStart;
		hyperslabTimeDuration = difftime(timeEnd, timeStart);
	}

	delete[] numValuesInEachDimension;
	delete[] offsetInEachDimension;

	nonHyperslabClockDuration /= smoothingConstant;
	nonHyperslabTImeDuration /= smoothingConstant;
	hyperslabClockDuration /= smoothingConstant;
	hyperslabTimeDuration /= smoothingConstant;

	// results
	std::cout << "Non hyperslab: property " << prop->getTitle() << " have been read " << nbIter << " times in " << nonHyperslabClockDuration << " ticks (CPU time)" << std::endl;
	std::cout << "Hyperslab:     property " << prop->getTitle() << " have been read " << nbIter << " times in " << hyperslabClockDuration << " ticks (CPU time)" << std::endl;
	double result = (hyperslabClockDuration * 100) / nonHyperslabClockDuration;
	std::cout << "hyperslab version took " << result << " % of non hyperslab version" << std::endl;
	std::cout << "Non hyperslab: property " << ijkGrid->getTitle() << " have been read " << nbIter << " times in " << fixed << nonHyperslabTImeDuration << " seconds" << std::endl;
	std::cout << "Hyperslab:     property " << ijkGrid->getTitle() << " have been read " << nbIter << " times in " << fixed << hyperslabTimeDuration << " seconds" << std::endl;
	result = (hyperslabTimeDuration * 100) / nonHyperslabTImeDuration;
	std::cout << "hyperslab version took " << result << " % of non hyperslab version" << std::endl;

	delete[] values;

	std::cout << endl << "END: IJK GRID REP (hyperslabbed and non-hyperslabbed property reading comparison)" << std::endl;
}

void deserializeLog(COMMON_NS::DataObjectRepository & repo)
{
	cout << endl << "Log" << endl;

	std::vector<WITSML2_NS::Well*> witsmlWells = repo.getDataObjects<WITSML2_NS::Well>();
	for (size_t wellIdx = 0; wellIdx < witsmlWells.size(); ++wellIdx) {
		cout << "witsml well: " << witsmlWells[wellIdx]->getTitle() << " (" << witsmlWells[wellIdx]->getUuid() << ")" << std::endl;
		std::vector<WITSML2_NS::Wellbore*> witsmlWellbores = witsmlWells[wellIdx]->getWellboreSet();
		for (size_t wellboreIdx = 0; wellboreIdx < witsmlWellbores.size(); ++wellboreIdx) {
			cout << "witsml wellbore: " << witsmlWellbores[wellboreIdx]->getTitle() << " (" << witsmlWellbores[wellboreIdx]->getUuid() << ")" << std::endl;
			std::vector<WITSML2_0_NS::Log*> wbLogs = witsmlWellbores[wellboreIdx]->getLogSet();
			for (size_t wbLogIdx = 0; wbLogIdx < wbLogs.size(); ++wbLogIdx) {
				WITSML2_0_NS::Log* wbLog = wbLogs[wbLogIdx];
				cout << "witsml log: " << wbLog->getTitle() << " (" << wbLog->getUuid() << ")" << std::endl;
				if (wbLog->hasTimeDepth()) { cout << "TimeDepth: " << wbLog->getTimeDepth() << std::endl; }
				if (wbLog->hasRunNumber()) { cout << "RunNumber: " << wbLog->getRunNumber() << std::endl; }
				if (wbLog->hasPassNumber()) { cout << "PassNumber: " << wbLog->getPassNumber() << std::endl; }
				if (wbLog->hasLoggingCompanyName()) { cout << "LoggingCompanyName: " << wbLog->getLoggingCompanyName() << std::endl; }
				if (wbLog->hasLoggingCompanyCode()) { cout << "LoggingCompanyCode: " << wbLog->getLoggingCompanyCode() << std::endl; }
				std::vector<WITSML2_0_NS::ChannelSet*> channelSets = wbLog->getChannelSets();
				for (size_t channelSetIdx = 0; channelSetIdx < channelSets.size(); ++channelSetIdx) {
					WITSML2_0_NS::ChannelSet* channelSet = channelSets[channelSetIdx];
					cout << "witsml channelSet: " << channelSet->getTitle() << " (" << channelSet->getUuid() << ")" << std::endl;
					if (channelSet->hasTimeDepth()) { cout << "TimeDepth: " << channelSet->getTimeDepth() << std::endl; }
					if (channelSet->hasRunNumber()) { cout << "RunNumber: " << channelSet->getRunNumber() << std::endl; }
					if (channelSet->hasPassNumber()) { cout << "PassNumber: " << channelSet->getPassNumber() << std::endl; }
					if (channelSet->hasLoggingCompanyName()) { cout << "LoggingCompanyName: " << channelSet->getLoggingCompanyName() << std::endl; }
					if (channelSet->hasLoggingCompanyCode()) { cout << "LoggingCompanyCode: " << channelSet->getLoggingCompanyCode() << std::endl; }
					if (channelSet->hasDataAsFileUri()) { cout << "Data As File Uri: " << channelSet->getDataAsFileUri() << std::endl; }
					if (channelSet->hasDataAsJsonArray()) { cout << "Data As Json Array: " << channelSet->getDataAsJsonArray() << std::endl; }
					for (size_t channelIndexIdx = 0; channelIndexIdx < channelSet->getChannelIndexCount(); ++channelIndexIdx) {
						cout << "IndexType: " << static_cast<int>(channelSet->getChannelIndexType(channelIndexIdx)) << std::endl;
						cout << "Uom: " << channelSet->getChannelIndexUom(channelIndexIdx) << std::endl;
						cout << "IsIncreasing: " << channelSet->getChannelIndexIsIncreasing(channelIndexIdx) << std::endl;
						cout << "Mnemo: " << channelSet->getChannelIndexMnemonic(channelIndexIdx) << std::endl;
						cout << "Datum: " << channelSet->getChannelIndexDatum(channelIndexIdx) << std::endl;
					}
					std::vector<WITSML2_0_NS::Channel*> channels = channelSet->getChannels();
					for (size_t channelIdx = 0; channelIdx < channels.size(); ++channelIdx) {
						WITSML2_0_NS::Channel* channel = channels[channelIdx];
						cout << "witsml channel: " << channel->getTitle() << " (" << channel->getUuid() << ")" << std::endl;
						if (channel->hasTimeDepth()) { cout << "TimeDepth: " << channel->getTimeDepth() << std::endl; }
						if (channel->hasRunNumber()) { cout << "RunNumber: " << channel->getRunNumber() << std::endl; }
						if (channel->hasPassNumber()) { cout << "PassNumber: " << channel->getPassNumber() << std::endl; }
						if (channel->hasLoggingCompanyName()) { cout << "LoggingCompanyName: " << channel->getLoggingCompanyName() << std::endl; }
						if (channel->hasLoggingCompanyCode()) { cout << "LoggingCompanyCode: " << channel->getLoggingCompanyCode() << std::endl; }
						for (size_t channelIndexIdx = 0; channelIndexIdx < channel->getChannelIndexCount(); ++channelIndexIdx) {
							cout << "IndexType: " << static_cast<int>(channel->getChannelIndexType(channelIndexIdx)) << std::endl;
							cout << "Uom: " << channel->getChannelIndexUom(channelIndexIdx) << std::endl;
							cout << "IsIncreasing: " << channel->getChannelIndexIsIncreasing(channelIndexIdx) << std::endl;
							cout << "Mnemo: " << channel->getChannelIndexMnemonic(channelIndexIdx) << std::endl;
							cout << "Datum: " << channel->getChannelIndexDatum(channelIndexIdx) << std::endl;
						}
						cout << "witsml channel prop kind : " << channel->getPropertyKind()->getTitle() << " (" << channel->getPropertyKind()->getUuid() << ")" << std::endl;
					}
				}
			}
		}
	}
}

void deserializeWbGeometry(COMMON_NS::DataObjectRepository & repo)
{
	cout << endl << "WELLBORE GEOMETRY" << endl;

	std::vector<WITSML2_NS::Well*> witsmlWells = repo.getDataObjects<WITSML2_NS::Well>();
	for (size_t wellIdx = 0; wellIdx < witsmlWells.size(); ++wellIdx) {
		cout << "witsml well: " << witsmlWells[wellIdx]->getTitle() << " (" << witsmlWells[wellIdx]->getUuid() << ")" << std::endl;
		std::vector<WITSML2_NS::Wellbore*> witsmlWellbores = witsmlWells[wellIdx]->getWellboreSet();
		for (size_t wellboreIdx = 0; wellboreIdx < witsmlWellbores.size(); ++wellboreIdx) {
			cout << "witsml wellbore: " << witsmlWellbores[wellboreIdx]->getTitle() << " (" << witsmlWellbores[wellboreIdx]->getUuid() << ")" << std::endl;
			std::vector<WITSML2_0_NS::WellboreGeometry*> wbGeoms = witsmlWellbores[wellboreIdx]->getWellboreGeometrySet();
			for (size_t wbGeomIdx = 0; wbGeomIdx < wbGeoms.size(); ++wbGeomIdx) {
				WITSML2_0_NS::WellboreGeometry* wbGeom = wbGeoms[wbGeomIdx];
				cout << "witsml wellbore geom: " << wbGeom->getTitle() << " (" << wbGeom->getUuid() << ")" << std::endl;
				if (wbGeom->hasDepthWaterMean()) { cout << "DepthWaterMean: " << wbGeom->getDepthWaterMeanValue() << " " << static_cast<int>(wbGeom->getDepthWaterMeanUom()) << std::endl; }
				if (wbGeom->hasGapAir()) { cout << "GapAir: " << wbGeom->getGapAirValue() << " " << static_cast<int>(wbGeom->getGapAirUom()) << std::endl; }
				if (wbGeom->hasMdBase()) { cout << "MdBase: " << wbGeom->getMdBaseValue() << " " << static_cast<int>(wbGeom->getMdBaseUom()) << " datum=" << wbGeom->getMdBaseDatum() << std::endl; }
				for (size_t sectionIdx = 0; sectionIdx < wbGeom->getSectionCount(); ++sectionIdx) {
					std::cout << "Section " << sectionIdx << endl;
					if (wbGeom->hasWellboreGeometrySectionCurveConductor(sectionIdx)) { cout << "CurveConductor: " << wbGeom->getWellboreGeometrySectionCurveConductor(sectionIdx) << std::endl; }
					if (wbGeom->hasWellboreGeometrySectionDiaDrift(sectionIdx)) { cout << "DiaDrift: " << wbGeom->getWellboreGeometrySectionDiaDriftValue(sectionIdx) << " " << static_cast<int>(wbGeom->getWellboreGeometrySectionDiaDriftUom(sectionIdx)) << std::endl; }
					if (wbGeom->hasWellboreGeometrySectionFactFric(sectionIdx)) { cout << "FactFric: " << wbGeom->getWellboreGeometrySectionFactFric(sectionIdx) << std::endl; }
					if (wbGeom->hasWellboreGeometrySectionGrade(sectionIdx)) { cout << "Grade: " << wbGeom->getWellboreGeometrySectionGrade(sectionIdx) << std::endl; }
					if (wbGeom->hasWellboreGeometrySectionIdSection(sectionIdx)) { cout << "IdSection: " << wbGeom->getWellboreGeometrySectionIdSectionValue(sectionIdx) << " " << static_cast<int>(wbGeom->getWellboreGeometrySectionIdSectionUom(sectionIdx)) << std::endl; }
					if (wbGeom->hasWellboreGeometrySectionOdSection(sectionIdx)) { cout << "OdSection: " << wbGeom->getWellboreGeometrySectionOdSectionValue(sectionIdx) << " " << static_cast<int>(wbGeom->getWellboreGeometrySectionOdSectionUom(sectionIdx)) << std::endl; }
					if (wbGeom->hasWellboreGeometrySectionTypeHoleCasing(sectionIdx)) { cout << "TypeHoleCasing: " << static_cast<int>(wbGeom->getWellboreGeometrySectionTypeHoleCasing(sectionIdx)) << std::endl; }
					if (wbGeom->hasWellboreGeometrySectionMdInterval(sectionIdx)) {
						cout << "Base md: " << wbGeom->getWellboreGeometrySectionMdIntervalBase(sectionIdx) << " " << static_cast<int>(wbGeom->getWellboreGeometrySectionMdIntervalBaseUom(sectionIdx)) << std::endl;
						cout << "Top md: " << wbGeom->getWellboreGeometrySectionMdIntervalTop(sectionIdx) << " " << static_cast<int>(wbGeom->getWellboreGeometrySectionMdIntervalTopUom(sectionIdx)) << std::endl;
						cout << "datum: " << wbGeom->getWellboreGeometrySectionMdIntervaldatum(sectionIdx) << std::endl;
					}
					if (wbGeom->hasWellboreGeometrySectionTvdInterval(sectionIdx)) {
						cout << "Base Tvd: " << wbGeom->getWellboreGeometrySectionTvdIntervalBase(sectionIdx) << " " << static_cast<int>(wbGeom->getWellboreGeometrySectionTvdIntervalBaseUom(sectionIdx)) << std::endl;
						cout << "Top Tvd: " << wbGeom->getWellboreGeometrySectionTvdIntervalTop(sectionIdx) << " " << static_cast<int>(wbGeom->getWellboreGeometrySectionTvdIntervalTopUom(sectionIdx)) << std::endl;
						cout << "datum: " << wbGeom->getWellboreGeometrySectionTvdIntervaldatum(sectionIdx) << std::endl;
					}
				}
			}
		}
	}
}

void deserializePerforations(COMMON_NS::DataObjectRepository & pck)
{
	cout << endl << "PERFORATIONS" << endl;

	WITSML2_0_NS::WellboreCompletion* wellboreCompletion = pck.getDataObjectByUuid<WITSML2_0_NS::WellboreCompletion>("7bda8ecf-2037-4dc7-8c59-db6ca09f2008");
	if (wellboreCompletion == nullptr) {
		return;
	}

	cout << "deserializing WellboreCompletion: " << wellboreCompletion->getTitle() << " (" << wellboreCompletion->getUuid() << ")" << std::endl;

	WITSML2_0_NS::WellCompletion* wellCompletion = wellboreCompletion->getWellCompletion();
	std::cout << "Associated with witsml well completion " << wellCompletion->getTitle()
		<< " with GUID " << wellCompletion->getUuid() << " and witsml well " << wellCompletion->getWell()->getTitle()
		<< " with GUID " << wellCompletion->getWell()->getUuid() << std::endl;

	witsmlWellbore = wellboreCompletion->getWellbore();
	std::cout << "Associated with witsml well bore " << witsmlWellbore->getTitle()
		<< " with GUID " << witsmlWellbore->getUuid() << " and witsml well " << witsmlWellbore->getWell()->getTitle()
		<< " with GUID " << witsmlWellbore->getWell()->getUuid() << std::endl;

	for (unsigned int perforationIndex = 0; perforationIndex < wellboreCompletion->getPerforationCount(); ++perforationIndex)
	{
		cout << std::endl << "perforation " << perforationIndex << " with uid \"" << wellboreCompletion->getPerforationUid(perforationIndex) << "\":" << std::endl;
		if (wellboreCompletion->hasPerforationMdDatum(perforationIndex))
		{
			cout << "datum: " << wellboreCompletion->getPerforationMdDatum(perforationIndex) << std::endl;
		}
		if (wellboreCompletion->hasPerforationMdUnit(perforationIndex))
		{
			cout << "md unit: " << wellboreCompletion->getPerforationMdUnitAsString(perforationIndex) << std::endl;
		}
		if (wellboreCompletion->hasPerforationTopMd(perforationIndex))
		{
			cout << "top md: " << wellboreCompletion->getPerforationTopMd(perforationIndex) << std::endl;
		}
		if (wellboreCompletion->hasPerforationBaseMd(perforationIndex))
		{
			cout << "base md: " << wellboreCompletion->getPerforationBaseMd(perforationIndex) << std::endl;
		}

		for (unsigned int historyIndex = 0; historyIndex < wellboreCompletion->getPerforationHistoryCount(perforationIndex); ++historyIndex)
		{
			cout << "history entry " << historyIndex << ":" << std::endl;
			if (wellboreCompletion->hasPerforationHistoryStatus(historyIndex, perforationIndex))
			{
				cout << "\tstatus: " << wellboreCompletion->getPerforationHistoryStatusToString(historyIndex, perforationIndex) << std::endl;
			}
			if (wellboreCompletion->hasPerforationHistoryStartDate(historyIndex, perforationIndex))
			{
				cout << "\tstart date: " << wellboreCompletion->getPerforationHistoryStartDate(historyIndex, perforationIndex) << std::endl;
			}
			if (wellboreCompletion->hasPerforationHistoryEndDate(historyIndex, perforationIndex))
			{
				cout << "\tend date: " << wellboreCompletion->getPerforationHistoryEndDate(historyIndex, perforationIndex) << std::endl;
			}
			if (wellboreCompletion->hasPerforationHistoryMdDatum(historyIndex, perforationIndex))
			{
				cout << "\tdatum: " << wellboreCompletion->getPerforationHistoryMdDatum(historyIndex, perforationIndex) << std::endl;
			}
			if (wellboreCompletion->hasPerforationHistoryMdUnit(historyIndex, perforationIndex))
			{
				cout << "\tmd unit: " << wellboreCompletion->getPerforationHistoryMdUnitAsString(historyIndex, perforationIndex) << std::endl;
			}
			if (wellboreCompletion->hasPerforationHistoryTopMd(historyIndex, perforationIndex))
			{
				cout << "\ttop md: " << wellboreCompletion->getPerforationHistoryTopMd(historyIndex, perforationIndex) << std::endl;
			}
			if (wellboreCompletion->hasPerforationHistoryBaseMd(historyIndex, perforationIndex))
			{
				cout << "\tbase md: " << wellboreCompletion->getPerforationHistoryBaseMd(historyIndex, perforationIndex) << std::endl;
			}
		}
	}
}
#if WITH_RESQML2_2
void deserializeGraphicalInformationSet(COMMON_NS::DataObjectRepository & pck)
{
	std::cout << "GRAPHICAL INFORMATIONS" << std::endl;

	std::vector<EML2_3_NS::GraphicalInformationSet*> gisSet = pck.getDataObjects<EML2_3_NS::GraphicalInformationSet>();
	for (unsigned int gisIndex = 0; gisIndex < gisSet.size(); ++gisIndex) {
		EML2_3_NS::GraphicalInformationSet* graphicalInformationSet = gisSet[gisIndex];
		for (unsigned int i = 0; i < graphicalInformationSet->getGraphicalInformationSetCount(); ++i)
		{
			COMMON_NS::AbstractObject* targetObject = graphicalInformationSet->getTargetObject(i);

			std::cout << "graphical information for: " << targetObject->getTitle() << std::endl;

			if (graphicalInformationSet->hasDefaultColor(targetObject)) {
				std::cout << "default hue: " << graphicalInformationSet->getDefaultHue(targetObject) << std::endl;
				std::cout << "default saturation: " << graphicalInformationSet->getDefaultSaturation(targetObject) << std::endl;
				std::cout << "default value: " << graphicalInformationSet->getDefaultValue(targetObject) << std::endl;
				std::cout << "default alpha: " << graphicalInformationSet->getDefaultAlpha(targetObject) << std::endl;
				if (graphicalInformationSet->hasDefaultColorTitle(targetObject)) {
					std::cout << "default color title: " << graphicalInformationSet->getDefaultColorTitle(targetObject) << std::endl;
				}
			}

			if (graphicalInformationSet->hasDiscreteColorMap(targetObject)) {
				RESQML2_NS::DiscreteColorMap* discreteColorMap = graphicalInformationSet->getDiscreteColorMap(targetObject);
				std::cout << "discrete color map title: " << discreteColorMap->getTitle() << std::endl;
				unsigned int r, g, b;
				for (unsigned int colorIndex = 0; colorIndex < discreteColorMap->getColorCount(); ++colorIndex) {
					discreteColorMap->getRgbColor(colorIndex, r, g, b);
					std::cout << colorIndex << ": (" << r << ", " << g << ", " << b << ", ";
					std::cout << discreteColorMap->getAlpha(colorIndex);
					if (discreteColorMap->hasColorTitle(colorIndex)) {
						std::cout << ", " << discreteColorMap->getColorTitle(colorIndex);
					}
					std::cout << ")" << std::endl;
				}
				if (graphicalInformationSet->hasColorMapMinMax(targetObject)) {
					std::cout << "min: " << graphicalInformationSet->getColorMapMin(targetObject) << std::endl;
					std::cout << "max: " << graphicalInformationSet->getColorMapMax(targetObject) << std::endl;
				}
				if (graphicalInformationSet->hasValueVectorIndex(targetObject)) {
					std::cout << "value vector index: " << graphicalInformationSet->getValueVectorIndex(targetObject) << std::endl;
				}
			}

			if (graphicalInformationSet->hasContinuousColorMap(targetObject)) {
				RESQML2_NS::ContinuousColorMap* continuousColorMap = graphicalInformationSet->getContinuousColorMap(targetObject);
				std::cout << "continuous color map title: " << continuousColorMap->getTitle() << std::endl;
				unsigned int r, g, b;
				for (unsigned int mapIndex = 0; mapIndex < continuousColorMap->getColorCount(); ++mapIndex) {
					continuousColorMap->getRgbColor(mapIndex, r, g, b);
					std::cout << mapIndex << ": (" << r << ", " << g << ", " << b << ", ";
					std::cout << continuousColorMap->getAlpha(mapIndex);
					if (continuousColorMap->hasColorTitle(mapIndex)) {
						std::cout << ", " << continuousColorMap->getColorTitle(mapIndex);
					}
					std::cout << ")" << std::endl;
				}
				if (graphicalInformationSet->hasColorMapMinMax(targetObject)) {
					std::cout << "min: " << graphicalInformationSet->getColorMapMin(targetObject) << std::endl;
					std::cout << "max: " << graphicalInformationSet->getColorMapMax(targetObject) << std::endl;
				}
				if (graphicalInformationSet->hasValueVectorIndex(targetObject)) {
					std::cout << "value vector index: " << graphicalInformationSet->getValueVectorIndex(targetObject) << std::endl;
				}
			}
		}
	}
}
#endif

void deserializeIjkGrid(const COMMON_NS::DataObjectRepository & repo)
{
	std::cout << endl << "IJK GRID REP" << endl;
	unsigned int ijkGridCount = repo.getIjkGridRepresentationCount();
	for (unsigned int ijkGridIdx = 0; ijkGridIdx < ijkGridCount; ++ijkGridIdx)
	{
		RESQML2_NS::AbstractIjkGridRepresentation* ijkGrid = repo.getIjkGridRepresentation(ijkGridIdx);

		showAllMetadata(ijkGrid);
		if (ijkGrid->isPartial()) {
			showAllProperties(ijkGrid);
			continue;
		}
		std::cout << "This ijk grid is ";
		if (!ijkGrid->isNodeGeometryCompressed()) {
			std::cout << "not ";
		}
		std::cout << "compressed." << std::endl;

		if (ijkGrid->getGeometryKind() != RESQML2_NS::AbstractIjkGridRepresentation::NO_GEOMETRY)
		{
			std::cout << "Most complex pillar geometry is ";
			gsoap_resqml2_0_1::resqml20__PillarShape mostcomplexPillarGeom = ijkGrid->getMostComplexPillarGeometry();
			if (mostcomplexPillarGeom == gsoap_resqml2_0_1::resqml20__PillarShape::vertical) {
				std::cout << "vertical";
			}
			else if (mostcomplexPillarGeom == gsoap_resqml2_0_1::resqml20__PillarShape::straight) {
				std::cout << "straight";
			}
			else if (mostcomplexPillarGeom == gsoap_resqml2_0_1::resqml20__PillarShape::curved) {
				std::cout << "curved";
			}
			std::cout << std::endl;

			auto kGapCount = ijkGrid->getKGapsCount();
			std::cout << " K Gap Count" << kGapCount << std::endl;
			if (kGapCount > 0) {
				std::unique_ptr<bool[]> kGapAfterLayer(new bool[ijkGrid->getKCellCount() - 1]);
				for (size_t kIndex = 0; kIndex < ijkGrid->getKCellCount() - 1; ++kIndex) {
					std::cout << "There is ";
					if (!kGapAfterLayer[kIndex]) {
						std::cout << "NOT ";
					}
					std::cout << "a K gap after K layer " << kIndex << std::endl;
				}
			}

			if (ijkGrid->getGeometryKind() == RESQML2_NS::AbstractIjkGridRepresentation::LATTICE) {
				std::cout << "This 3d grid has a lattice geometry." << std::endl;
			}
			else {
				if (ijkGrid->getGeometryKind() == RESQML2_NS::AbstractIjkGridRepresentation::PARAMETRIC)
				{
					std::cout << "This 3d grid has a parametric geometry." << std::endl;
					RESQML2_NS::IjkGridParametricRepresentation* paramIjkGrid = static_cast<RESQML2_NS::IjkGridParametricRepresentation*>(ijkGrid);
					if (paramIjkGrid->isParametricLineKindConstant())
					{
						std::cout << "Constant parametric line kind : " << paramIjkGrid->getConstantParametricLineKind() << std::endl;
					}
					else
					{
						std::cout << "Non constant parametric line kind" << std::endl;
						std::unique_ptr<short[]> pillarKind(new short[paramIjkGrid->getPillarCount()]);
						paramIjkGrid->getParametricLineKind(pillarKind.get());
						for (size_t pillarIndex = 0; pillarIndex < paramIjkGrid->getPillarCount() && pillarIndex < 10; ++pillarIndex) {
							cout << "Pillar index " << pillarIndex << " with kind " << pillarKind[pillarIndex] << endl;
						}
						std::unique_ptr<bool[]> pillarIsDefined(new bool[paramIjkGrid->getPillarCount()]);
						paramIjkGrid->getPillarGeometryIsDefined(pillarIsDefined.get());
						for (size_t pillarIndex = 0; pillarIndex < paramIjkGrid->getPillarCount() && pillarIndex < 10; ++pillarIndex) {
							cout << "Pillar index " << pillarIndex << " is defined : " << pillarIsDefined[pillarIndex] << endl;
						}
					}

					unsigned int patchCount = ijkGrid->getPatchCount();
					for (unsigned int currentPatch = 0; currentPatch < patchCount; ++currentPatch) {
						uint64_t nbVertex = ijkGrid->getXyzPointCountOfPatch(currentPatch);

						std::unique_ptr<double[]> xyzPts(new double[nbVertex * 3]);
						ijkGrid->getXyzPointsOfPatch(currentPatch, xyzPts.get());

						for (size_t vIndex = 0; vIndex < nbVertex && vIndex < 10; ++vIndex) {
							double x = xyzPts[vIndex * 3];
							double y = xyzPts[vIndex * 3 + 1];
							double z = xyzPts[vIndex * 3 + 2];
							std::cout << x << " " << y << " " << z << std::endl;
						}
					}
					/*
					uint64_t pointCountByInterface = paramIjkGrid->getXyzPointCountOfKInterfaceOfPatch(0);
					double* interfaceXyzPoints = new double[pointCountByInterface * 3];
					paramIjkGrid->getXyzPointsOfKInterfaceOfPatch(0, 0, interfaceXyzPoints);
					delete[] interfaceXyzPoints;
					*/
				}
				else if (ijkGrid->getGeometryKind() == RESQML2_NS::AbstractIjkGridRepresentation::EXPLICIT)
				{
					std::cout << "This 3d grid has an explicit geometry." << std::endl;
				}
				else
				{
					std::cout << "This 3d grid has an unknown geometry." << std::endl;
				}

				// read whole points
				uint64_t xyzPointCount = ijkGrid->getXyzPointCountOfAllPatches();
				std::cout << "\t XYZ points count :" << xyzPointCount << std::endl;
				std::cout << "\t Start reading XYZ points..." << std::endl;
				std::unique_ptr<double[]> xyzPoints(new double[xyzPointCount * 3]);
				ijkGrid->getXyzPointsOfAllPatches(xyzPoints.get());
				std::cout << "\t Stop reading XYZ points :" << std::endl;

				// read points by cell corner
				ijkGrid->loadSplitInformation();

				for (unsigned int cellCorner = 0; cellCorner < 8; ++cellCorner) {
					auto ptIndex = ijkGrid->getXyzPointIndexFromCellCorner(0, 0, 0, cellCorner);
					std::cout << " Cell 0,0,0 corner " << cellCorner << " is at index " << ptIndex << std::endl;
					std::cout << " Cell 0,0,0 corner " << cellCorner << " is  " << xyzPoints[ptIndex*3] << " " << xyzPoints[ptIndex * 3 + 1] << " " << xyzPoints[ptIndex * 3 + 2] << std::endl;
				}

				if (ijkGrid->getKCellCount() > 1) {
					for (unsigned int cellCorner = 0; cellCorner < 8; ++cellCorner) {
						auto ptIndex = ijkGrid->getXyzPointIndexFromCellCorner(0, 0, 1, cellCorner);
						std::cout << " Cell 0,0,1 corner " << cellCorner << " is at index " << ptIndex << std::endl;
						std::cout << " Cell 0,0,1 corner " << cellCorner << " is  " << xyzPoints[ptIndex * 3] << " " << xyzPoints[ptIndex * 3 + 1] << " " << xyzPoints[ptIndex * 3 + 2] << std::endl;
					}
				}

				ijkGrid->unloadSplitInformation();

				std::cout << "Split coordinate line count is : " << ijkGrid->getSplitCoordinateLineCount() << std::endl;
			}
		}
		else
			std::cout << "This 3d grid has no geometry." << std::endl;

		if (ijkGrid->getInterpretation())
		{
			std::cout << "Interpretation is : " << ijkGrid->getInterpretation()->getTitle() << std::endl;
			if (ijkGrid->getInterpretation()->getInterpretedFeature())
				std::cout << "Feature is : " << ijkGrid->getInterpretation()->getInterpretedFeature()->getTitle() << std::endl;
			else
				std::cout << " NO Feature" << std::endl;
		}
		else
			std::cout << " NO interpretation" << std::endl;

		for (unsigned int subRepIndex = 0; subRepIndex < ijkGrid->getFaultSubRepresentationCount(); ++subRepIndex)
		{
			std::cout << "Fault Subrep is : " << ijkGrid->getFaultSubRepresentation(subRepIndex)->getTitle() << std::endl;
		}

		showAllSubRepresentations(ijkGrid->getSubRepresentationSet());

		//*****************************
		// TRUNCATION
		//*****************************
		if (ijkGrid->isTruncated()) {
			std::cout << "This grid is truncated" << std::endl;
			std::cout << "Truncated face count : " << ijkGrid->getTruncatedFaceCount() << std::endl;
			std::cout << "Truncated cell count : " << ijkGrid->getTruncatedCellCount() << std::endl;

			uint64_t* cellIndices = new uint64_t[ijkGrid->getTruncatedCellCount()];
			ijkGrid->getTruncatedCellIndices(cellIndices);
			for (uint64_t index = 0; index < ijkGrid->getTruncatedCellCount() && index < 10; ++index) {
				cout << "truncated cell Indices : " << cellIndices[index] << endl;
			}
			delete[] cellIndices;

			uint64_t* cumNodeCount = new uint64_t[ijkGrid->getTruncatedFaceCount()];
			ijkGrid->getCumulativeNodeCountPerTruncatedFace(cumNodeCount);
			for (uint64_t index = 0; index < ijkGrid->getTruncatedFaceCount() && index < 10; ++index) {
				cout << "CumulativeNodeCountPerTruncatedFace : " << cumNodeCount[index] << endl;
			}
			uint64_t* nodeIndicesPerTruncFace = new uint64_t[cumNodeCount[ijkGrid->getTruncatedFaceCount() - 1]];
			ijkGrid->getNodeIndicesOfTruncatedFaces(nodeIndicesPerTruncFace);
			for (uint64_t index = 0; index < cumNodeCount[ijkGrid->getTruncatedFaceCount() - 1] && index < 10; ++index) {
				cout << "nodeIndicesPerTruncFace : " << nodeIndicesPerTruncFace[index] << endl;
			}
			delete[] cumNodeCount;
			delete[] nodeIndicesPerTruncFace;

			uint64_t* cumFaceCount = new uint64_t[ijkGrid->getTruncatedCellCount()];
			ijkGrid->getCumulativeTruncatedFaceCountPerTruncatedCell(cumFaceCount);
			for (uint64_t index = 0; index < ijkGrid->getTruncatedCellCount() && index < 10; ++index) {
				cout << "CumulativeTruncatedFaceCountPerTruncatedCell : " << cumFaceCount[index] << endl;
			}
			uint64_t* faceIndicesPerTruncCell = new uint64_t[cumFaceCount[ijkGrid->getTruncatedCellCount() - 1]];
			ijkGrid->getTruncatedFaceIndicesOfTruncatedCells(faceIndicesPerTruncCell);
			for (uint64_t index = 0; index < cumFaceCount[ijkGrid->getTruncatedCellCount() - 1] && index < 10; ++index) {
				cout << "faceIndicesPerTruncCell : " << faceIndicesPerTruncCell[index] << endl;
			}
			delete[] cumFaceCount;
			delete[] faceIndicesPerTruncCell;

			uint64_t* cumNonTruncFaceCount = new uint64_t[ijkGrid->getTruncatedCellCount()];
			ijkGrid->getCumulativeNonTruncatedFaceCountPerTruncatedCell(cumNonTruncFaceCount);
			for (uint64_t index = 0; index < ijkGrid->getTruncatedCellCount() && index < 10; ++index) {
				cout << "CumulativeNonTruncatedFaceCountPerTruncatedCell : " << cumNonTruncFaceCount[index] << endl;
			}
			uint64_t* nonTruncfaceIndicesPerTruncCell = new uint64_t[cumNonTruncFaceCount[ijkGrid->getTruncatedCellCount() - 1]];
			ijkGrid->getNonTruncatedFaceIndicesOfTruncatedCells(nonTruncfaceIndicesPerTruncCell);
			for (uint64_t index = 0; index < cumNonTruncFaceCount[ijkGrid->getTruncatedCellCount() - 1] && index < 10; ++index) {
				cout << "nonTruncfaceIndicesPerTruncCell : " << nonTruncfaceIndicesPerTruncCell[index] << endl;
			}
			delete[] cumNonTruncFaceCount;
			delete[] nonTruncfaceIndicesPerTruncCell;

			unsigned char* rightHandnessTruncFace = new unsigned char[ijkGrid->getTruncatedFaceCount()];
			ijkGrid->getTruncatedFaceIsRightHanded(rightHandnessTruncFace);
			for (uint64_t index = 0; index < ijkGrid->getTruncatedFaceCount() && index < 10; ++index) {
				cout << "rightHandnessTruncFace : " << rightHandnessTruncFace[index] << endl;
			}
			delete[] rightHandnessTruncFace;
		}

		//*****************************
		// GRID CONNECTION SET 
		//*****************************
		unsigned int gridConnectionSetCount = ijkGrid->getGridConnectionSetRepresentationCount();
		std::cout << "Grid Connection Count is : " << gridConnectionSetCount << std::endl;
		if (gridConnectionSetCount > 0) {
			RESQML2_NS::GridConnectionSetRepresentation const * gridConnectionSet = ijkGrid->getGridConnectionSetRepresentation(0);
			unsigned int faultInterpOfGridConnCount = gridConnectionSet->getInterpretationCount();
			std::cout << "Interpretation Count of this grid connection set is : " << faultInterpOfGridConnCount << endl;
			if (faultInterpOfGridConnCount > 0)
			{
				RESQML2_NS::AbstractFeatureInterpretation* faultInterpOfGridConn = gridConnectionSet->getInterpretationFromIndex(0);
				std::cout << "Interpretation of this grid connection set is : " << faultInterpOfGridConn->getTitle() << " With UUID " << faultInterpOfGridConn->getUuid() << endl;
			}

			int* localFacePerCellIndexPairs = new int[gridConnectionSet->getCellIndexPairCount() * 2];
			int64_t gcsNullValue = gridConnectionSet->getLocalFacePerCellIndexPairs(localFacePerCellIndexPairs);
			std::cout << "Null Value for LocalFacePerCellIndexPairs : " << gcsNullValue << endl;
			delete[] localFacePerCellIndexPairs;
		}

		//*****************************
		// LGR 
		//*****************************
		if (ijkGrid->getParentGrid() != NULL)
		{
			std::cout << "\t PARENT WINDOW" << std::endl;
			if (ijkGrid->getParentGrid()->getXmlTag() == RESQML2_NS::AbstractIjkGridRepresentation::XML_TAG)
			{
				for (char dimension = 'i'; dimension < 'l'; ++dimension) {
					std::cout << "\t\t DIMENSION :" << dimension << std::endl;
					std::cout << "\t\t Regrid start at :" << ijkGrid->getRegridStartIndexOnParentGrid(dimension) << std::endl;
					std::cout << "\t\t Interval count is :" << ijkGrid->getRegridIntervalCount(dimension) << std::endl;
					if (ijkGrid->isRegridCellCountPerIntervalConstant('i', false)) {
						std::cout << "\t\t Constant parent cell count per interval :" << ijkGrid->getRegridConstantCellCountPerInterval(dimension, false) << std::endl;
					}
					else {
						std::cout << "\t\t Non constant parent cell count per interval" << std::endl;
					}
					if (ijkGrid->isRegridCellCountPerIntervalConstant('i', true)) {
						std::cout << "\t\t Constant child cell count per interval :" << ijkGrid->getRegridConstantCellCountPerInterval(dimension, true) << std::endl;
					}
					else {
						std::cout << "\t\t Non constant child cell count per interval" << std::endl;
					}
				}
			}/*
			 else if (ijkGrid->getParentGrid()->getXmlTag() == UnstructuredColumnLayerGridRepresentation::XML_TAG)
			 {
			 std::cout << "\t\t Refined columns count :" << ijkGrid->getParentColumnIndexCount() << std::endl;
			 }*/
			else if (ijkGrid->getParentGrid()->getXmlTag() == RESQML2_NS::UnstructuredGridRepresentation::XML_TAG)
			{
				std::cout << "\t\t Refined cells count :" << ijkGrid->getParentCellIndexCount() << std::endl;
			}
		}

		//*****************************
		// STRATIGRAPHY 
		//*****************************
		cout << "\t STRATIGRAPHY" << std::endl;
		if (ijkGrid->hasIntervalStratigraphicUnitIndices())
		{
			cout << "\t\t Linked with strati : " << ijkGrid->getStratigraphicOrganizationInterpretation()->getTitle() << endl;
			std::unique_ptr<int64_t[]> stratiIndices(new int64_t[ijkGrid->getKCellCount()]);
			ijkGrid->getIntervalStratigraphicUnitIndices(stratiIndices.get());
			for (size_t i = 0; i < ijkGrid->getKCellCount(); ++i) {
				cout << "\t\t K layer " << i << " is linked to strati layer " << stratiIndices[i] << endl;
			}
		}
		else
		{
			cout << "\t\t No link with stratigraphy." << endl;
		}

		std::unique_ptr<bool[]> enabledCells;
		if (ijkGrid->hasEnabledCellInformation()) {
			std::cout << "Has enabled/disabled cell information" << std::endl;
			enabledCells = std::unique_ptr<bool[]>(new bool[ijkGrid->getCellCount()]);
			ijkGrid->getEnabledCells(enabledCells.get());
		}
		showAllProperties(ijkGrid, enabledCells.get());
	}

	// Testing k-layers hyperslabbing
	deserializeGridHyperslabbingInterfaceSequence(repo);

	// Testing block hyperslabbing
	deserializeGridHyperslabbingBlock(repo);


	// ====================
	// Timing hyperslabbing (time consuming)

	//// 4*3*2 explicit grid Left Handed
	//AbstractIjkGridRepresentation* ijkgrid432 = static_cast<AbstractIjkGridRepresentation*>(pck.getDataObjectByUuid("e96c2bde-e3ae-4d51-b078-a8e57fb1e667"));
	//ijkGridHyperslabingTiming(ijkgrid432, 250000);

	//// FOUR SUGARS PARAMETRIC
	//AbstractIjkGridRepresentation* ijkgridParametric = static_cast<AbstractIjkGridRepresentation*>(pck.getDataObjectByUuid("37c45c00-fa3e-11e5-a21e-0002a5d5c51b"));
	//ijkGridHyperslabingTiming(ijkgridParametric, 250000);

	//// Four sugar cubes cellIndex
	//DiscreteProperty* discreteProp1OnIjkgridParametric = static_cast<DiscreteProperty*>(pck.getDataObjectByUuid("eb3dbf6c-5745-4e41-9d09-672f6fbab414"));
	//discretePropertyHyperslabingTiming(ijkgridParametric, discreteProp1OnIjkgridParametric, 250000);

	// ====================
}

void deserialize(const string & inputFile)
{
	COMMON_NS::EpcDocument pck(inputFile);
	cout << "EXTENDED CORE PROPERTIES" << endl;
	for (auto& pair : pck.getExtendedCoreProperty()) {
		cout << pair.first.c_str() << " " << pair.second.c_str() << endl;
	}

	cout << "Start deserialization of " << pck.getName() << " in " << (pck.getStorageDirectory().empty() ? "working directory." : pck.getStorageDirectory()) << endl;
	COMMON_NS::DataObjectRepository repo;
	// Comment the line above and uncomment one of the below lines depending on you OS if you want to check property kind validity
	//COMMON_NS::DataObjectRepository repo("C:/Users/Philippe/dev/fesapiEnv/fesapi/resources");
	//COMMON_NS::DataObjectRepository repo("/home/philippe/dev/fesapi/resources");
	const string resqmlResult = pck.deserializeInto(repo);
	if (!resqmlResult.empty()) {
		cerr << resqmlResult << endl;
		repo.clearWarnings();
	}
	pck.close();

	const unsigned int hdfProxyCount = repo.getHdfProxyCount();
	cout << "There are " << hdfProxyCount << " hdf files associated to this epc document." << endl;
	for (unsigned int hdfProxyIndex = 0; hdfProxyIndex < hdfProxyCount; ++hdfProxyIndex) {
		cout << "Hdf file relative path : " << repo.getHdfProxy(hdfProxyIndex)->getRelativePath() << endl;
	}
	for (size_t warningIndex = 0; warningIndex < repo.getWarnings().size(); ++warningIndex) {
		cout << "Warning #" << warningIndex << " : " << repo.getWarnings()[warningIndex] << endl;
	}

#if !defined(OFFICIAL)
	//deserializePropertyKindMappingFiles(&pck);
#endif

	COMMON_NS::EnumStringMapper enumStrMapper;
	cout << "MAPPING ENUM VS STRING" << endl;
	cout << "rock permeability == " << enumStrMapper.getEnergisticsPropertyKindName(enumStrMapper.getEnergisticsPropertyKind("rock permeability")) << endl;
	cout << "m (meter) == " << enumStrMapper.getEnergisticsUnitOfMeasureName(enumStrMapper.getEnergisticsUnitOfMeasure("m")) << endl;

	cout << "CRS" << endl;
	vector<RESQML2_NS::LocalDepth3dCrs*> depthCrsSet = repo.getLocalDepth3dCrsSet();
	for (size_t i = 0; i < depthCrsSet.size(); ++i) {
		cout << "Title is : " << depthCrsSet[i]->getTitle() << endl;
		if (depthCrsSet[i]->isProjectedCrsDefinedWithEpsg())
			cout << "Projected : EPSG " << depthCrsSet[i]->getProjectedCrsEpsgCode() << endl;
		else if (depthCrsSet[i]->isProjectedCrsUnknown())
			cout << "Projected : Unknown." << "Reason is:" << depthCrsSet[i]->getProjectedCrsUnknownReason() << endl;
	}
	vector<RESQML2_NS::LocalTime3dCrs*> timeCrsSet = repo.getLocalTime3dCrsSet();
	for (size_t i = 0; i < timeCrsSet.size(); ++i) {
		cout << "Title is : " << timeCrsSet[i]->getTitle() << endl;
		if (timeCrsSet[i]->isVerticalCrsDefinedWithEpsg())
			cout << "Vertical : EPSG one" << endl;
		else if (timeCrsSet[i]->isVerticalCrsUnknown())
			cout << "Vertical : Unknown." << "Reason is:" << timeCrsSet[i]->getVerticalCrsUnknownReason() << endl;
	}
	cout << endl;

	deserializeGeobody(&repo);
	deserializeFluidBoundary(repo);
	deserializeRockFluidOrganization(repo);
	deserializeFluidCharacterization(repo);
	deserializeTimeSeriesData(repo);

	std::vector<RESQML2_NS::BoundaryFeature*> faultSet = repo.getFaultSet();
	std::vector<RESQML2_NS::PolylineSetRepresentation *> faultPolyRepSet = repo.getFaultPolylineSetRepresentationSet();
	std::vector<RESQML2_NS::TriangulatedSetRepresentation *> faultTriRepSet = repo.getFaultTriangulatedSetRepresentationSet();
	std::vector<RESQML2_NS::BoundaryFeature*> horizonSet = repo.getHorizonSet();
	std::vector<RESQML2_NS::Grid2dRepresentation *> horizonGrid2dSet = repo.getHorizonGrid2dRepresentationSet();
	std::vector<RESQML2_NS::TriangulatedSetRepresentation *> horizonTriRepSet = repo.getHorizonTriangulatedSetRepresentationSet();
	std::vector<RESQML2_NS::TriangulatedSetRepresentation*> unclassifiedTriRepSet = repo.getUnclassifiedTriangulatedSetRepresentationSet();
	std::vector<RESQML2_NS::PolylineRepresentation *> horizonSinglePolylineRepSet = repo.getHorizonPolylineRepresentationSet();
	std::vector<RESQML2_NS::WellboreFeature*> wellboreSet = repo.getWellboreSet();
	std::vector<RESQML2_NS::WellboreTrajectoryRepresentation *> wellboreCubicTrajSet = repo.getWellboreTrajectoryRepresentationSet();
	std::vector<RESQML2_NS::UnstructuredGridRepresentation*> unstructuredGridRepSet = repo.getUnstructuredGridRepresentationSet();
	std::vector<EML2_NS::TimeSeries*> timeSeriesSet = repo.getTimeSeriesSet();
	std::vector<RESQML2_NS::StratigraphicColumn*> stratiColumnSet = repo.getStratigraphicColumnSet();
	std::vector<RESQML2_NS::RepresentationSetRepresentation*> representationSetRepresentationSet = repo.getRepresentationSetRepresentationSet();
	std::vector<RESQML2_NS::SubRepresentation*> subRepresentationSet = repo.getSubRepresentationSet();
	std::vector<RESQML2_NS::PolylineSetRepresentation *> frontierPolyRepSet = repo.getCulturalPolylineSetRepresentationSet();

	std::cout << "RepresentationSetRepresentation" << endl;
	for (auto* representationSetRepresentation : representationSetRepresentationSet) {
		showAllMetadata(representationSetRepresentation);
		std::cout << "Is homogeneous : " << representationSetRepresentation->isHomogeneous() << std::endl;
		std::cout << "Representation count : " << representationSetRepresentation->getRepresentationCount() << std::endl;
		showAllMetadata(representationSetRepresentation->getRepresentation(0));
		std::cout << "--------------------------------------------------" << std::endl;
	}

	std::cout << "FAULTS" << endl;
	for (auto* faultFeature : faultSet) {
		showAllMetadata(faultFeature);
		std::cout << "InterpretationCount : " << faultFeature->getInterpretationCount() << std::endl;
	}

	std::cout << faultPolyRepSet.size() << " FAULT POLYLINE SET REP" << endl;
	for (auto* faultPolyRep : faultPolyRepSet) {
		showAllMetadata(faultPolyRep);
		uint64_t nodeCount = faultPolyRep->getXyzPointCountOfAllPatches();
		std::unique_ptr<double[]> allXyzPoints(new double[nodeCount * 3]);
		faultPolyRep->getXyzPointsOfAllPatchesInGlobalCrs(allXyzPoints.get());
		for (uint64_t nodeIndex = 0; nodeIndex < 6; nodeIndex += 3) {
			std::cout << allXyzPoints[nodeIndex] << " " << allXyzPoints[nodeIndex + 1] << " " << allXyzPoints[nodeIndex + 2] << endl;
		}
		deserializeActivity(faultPolyRep);

		if (faultPolyRep->areAllPolylinesClosedOfAllPatches()) {
			std::cout << "All polylines of the fault are closed" << endl;
		}
		/*
		std::cout << "\tSEISMIC INFO" << endl;
		double* inlines = new double[nodeCount];
		faultPolyRep->getInlinesOfPointsOfPatch(0, inlines);
		for (unsigned int index = 0; index < nodeCount; index++)
		{
		std::cout << "\tinline : " << inlines[index] << std::endl;
		}
		delete [] inlines;
		double* crosslines = new double[nodeCount];;
		faultPolyRep->getCrosslinesOfPointsOfPatch(0, crosslines);
		for (unsigned int index = 0; index < nodeCount; index++)
		{
		std::cout << "\tcrossline : " << crosslines[index] << std::endl;
		}
		delete [] crosslines;
		*/

		showAllProperties(faultPolyRep);

		for (size_t gsrIndex = 0; gsrIndex < faultPolyRep->getInterpretation()->getGridConnectionSetRepresentationSet().size(); ++gsrIndex) {
			std::cout << "This fault polyline rep is linked to a grid connection set." << std::endl;
		}
	}

	std::cout << frontierPolyRepSet.size() << " FRONTIER POLYLINE SET REP" << endl;
	for (auto* frontierPolyRep : frontierPolyRepSet) {
		showAllMetadata(frontierPolyRep);

		std::unique_ptr<bool[]> closedFlag(new bool[frontierPolyRep->getPolylineCountOfPatch(0)]);
		frontierPolyRep->getClosedFlagPerPolylineOfPatch(0, closedFlag.get());
		for (unsigned int j = 0; j < frontierPolyRep->getPolylineCountOfPatch(0); ++j) {
			std::cout << "closed flag : " << closedFlag[j] << endl;
		}
	}

	std::cout << "FAULTS TRI REP" << endl;
	for (auto* faultTriRep : faultTriRepSet) {
		showAllMetadata(faultTriRep);

		uint64_t pointCount = faultTriRep->getXyzPointCountOfAllPatches();
		unsigned int triangleCount = faultTriRep->getTriangleCountOfAllPatches();
		cout << "point Count " << pointCount << endl;
		cout << "triangle Count " << triangleCount << endl;

		std::cout << "\tFAULTS TRI REP GEOMETRY" << endl;
		std::unique_ptr<double[]> xyzPoints(new double[pointCount * 3]);
		faultTriRep->getXyzPointsOfAllPatchesInGlobalCrs(xyzPoints.get());
		std::unique_ptr<unsigned int[]> triangleIndices(new unsigned int[triangleCount * 3]);
		faultTriRep->getTriangleNodeIndicesOfAllPatches(triangleIndices.get());
		for (size_t j = 0; j < 5; j++) {
			std::cout << "\txyzPoints : " << xyzPoints[j] << std::endl;
			std::cout << "\ttriangleIndices : " << triangleIndices[j] << std::endl;
			std::cout << "\t--------------------------------------------------" << std::endl;
		}
		deserializeActivity(faultTriRep);

		showAllProperties(faultTriRep);
	}

	std::cout << "HORIZONS" << endl;
	for (auto* horFeature : horizonSet) {
		showAllMetadata(horFeature);
		if (dynamic_cast<RESQML2_0_1_NS::Horizon*>(horFeature) != nullptr && static_cast<RESQML2_0_1_NS::Horizon*>(horFeature)->hasAnAge()) {
			cout << "Age " << static_cast<RESQML2_0_1_NS::Horizon*>(horFeature)->getAge() << " years" << endl;
		}
		std::cout << std::endl;
		std::cout << "InterpretationCount : " << horFeature->getInterpretationCount() << std::endl;
	}

	std::cout << "HORIZONS GRID 2D REP" << endl;
	for (auto* horizonGrid2d : horizonGrid2dSet) {
		showAllMetadata(horizonGrid2d);

		cout << "X origin " << horizonGrid2d->getXOriginInGlobalCrs() << endl;
		cout << "Y origin " << horizonGrid2d->getYOriginInGlobalCrs() << endl;

		cout << "I Node Count " << horizonGrid2d->getNodeCountAlongIAxis() << endl;
		cout << "J Node Count " << horizonGrid2d->getNodeCountAlongJAxis() << endl;
		std::unique_ptr<double[]> zValues(new double[horizonGrid2d->getNodeCountAlongIAxis() * horizonGrid2d->getNodeCountAlongJAxis()]);
		horizonGrid2d->getZValuesInGlobalCrs(zValues.get());
		std::cout << "First zValue is : " << zValues[0] << std::endl;
		std::cout << "Second zValue is : " << zValues[1] << std::endl;
		std::cout << "Third zValue is : " << zValues[2] << std::endl;
		std::cout << "Fourth zValue is : " << zValues[3] << std::endl;
		std::cout << "Fifth zValue is : " << zValues[4] << std::endl;
		if (horizonGrid2d->getSupportingRepresentation() != nullptr) {
			horizonGrid2d->getSupportingRepresentation()->getZValuesInGlobalCrs(zValues.get());
			std::cout << "Supporting Representation first zValue is : " << zValues[0] << std::endl;
			std::cout << "Supporting Representation second zValue is : " << zValues[1] << std::endl;
			std::cout << "Supporting Representation third zValue is : " << zValues[2] << std::endl;
			std::cout << "Supporting Representation fourth zValue is : " << zValues[3] << std::endl;
			std::cout << "Supporting Representation fifth zValue is : " << zValues[4] << std::endl;
		}
		cout << "XIOffset : " << horizonGrid2d->getXIOffsetInGlobalCrs() << endl;
		cout << "YIOffset : " << horizonGrid2d->getYIOffsetInGlobalCrs() << endl;
		cout << "XJOffset : " << horizonGrid2d->getXJOffsetInGlobalCrs() << endl;
		cout << "YJOffset : " << horizonGrid2d->getYJOffsetInGlobalCrs() << endl;
		if (horizonGrid2d->isISpacingConstant()) {
			cout << "Spacing in I is constant : " << horizonGrid2d->getISpacing() << endl;
		}
		else {
			cout << "Spacing in I is not constant." << endl;
		}
		if (horizonGrid2d->isJSpacingConstant()) {
			cout << "Spacing in J is constant : " << horizonGrid2d->getJSpacing() << endl;
		}
		else {
			cout << "Spacing in J is not constant." << endl;
		}

		deserializeActivity(horizonGrid2d);
		showAllProperties(horizonGrid2d);
	}

	std::cout << "HORIZONS TRI REP" << endl;
	for (auto* horizonTriRep : horizonTriRepSet) {
		showAllMetadata(horizonTriRep);

		const uint64_t pointCount = horizonTriRep->getXyzPointCountOfAllPatches();
		unsigned int triangleCount = horizonTriRep->getTriangleCountOfAllPatches();
		cout << "point Count " << pointCount << endl;
		cout << "triangle Count " << triangleCount << endl;

		std::cout << "\tHORIZONS TRI REP GEOMETRY" << endl;
		std::unique_ptr<double[]> xyzPoints(new double[pointCount * 3]);
		horizonTriRep->getXyzPointsOfAllPatchesInGlobalCrs(xyzPoints.get());
		std::unique_ptr<unsigned int[]> triangleIndices(new unsigned int[triangleCount * 3]);
		horizonTriRep->getTriangleNodeIndicesOfAllPatches(triangleIndices.get());
		for (unsigned int j = 0; j < 5; j++)
		{
			std::cout << "\txyzPoints : " << xyzPoints[j] << std::endl;
			std::cout << "\ttriangleIndices : " << triangleIndices[j] << std::endl;
			std::cout << "\t--------------------------------------------------" << std::endl;
		}

		const unsigned int patchCount = horizonTriRep->getPatchCount();
		for (unsigned int patchIndex = 0; patchIndex < patchCount; ++patchIndex) {
			RESQML2_NS::AbstractRepresentation* seismicSupport = horizonTriRep->getSeismicSupportOfPatch(patchIndex);
			if (seismicSupport != nullptr) {
				const uint64_t pointCountForPatch = horizonTriRep->getXyzPointCountOfPatch(patchIndex);
				cout << "Seismic support of patch " << patchIndex << " is : " << seismicSupport->getTitle() << endl;
				std::unique_ptr<double[]> inlines(new double[pointCountForPatch]);
				horizonTriRep->getInlinesOfPointsOfPatch(patchIndex, inlines.get());
				for (unsigned int index = 0; index < pointCountForPatch; index++) {
					std::cout << "\tinline : " << inlines[index] << std::endl;
				}
				std::unique_ptr<double[]> crosslines(new double[pointCountForPatch]);
				horizonTriRep->getCrosslinesOfPointsOfPatch(patchIndex, crosslines.get());
				for (unsigned int index = 0; index < pointCountForPatch; index++) {
					std::cout << "\tcrossline : " << crosslines[index] << std::endl;
				}
			}
			else {
				cout << "No seismic support for patch " << patchIndex << endl;
			}
		}

		deserializeActivity(horizonTriRep);
		showAllProperties(horizonTriRep);
	}

	std::cout << "UNCLASSIFIED TRI REP" << endl;
	for (auto* unclassifiedTriRep : unclassifiedTriRepSet) {
		showAllMetadata(unclassifiedTriRep);
		deserializeActivity(unclassifiedTriRep);
		showAllProperties(unclassifiedTriRep);
	}

	std::cout << "HORIZONS SINGLE POLYLINE REP" << endl;
	for (auto* horizonSinglePolylineRep : horizonSinglePolylineRepSet)
	{
		showAllMetadata(horizonSinglePolylineRep);

		const unsigned int patchCount = horizonSinglePolylineRep->getPatchCount();
		for (unsigned int patchIndex = 0; patchIndex < patchCount; ++patchIndex) {
			RESQML2_NS::AbstractRepresentation* seismicSupport = horizonSinglePolylineRep->getSeismicSupportOfPatch(patchIndex);
			if (seismicSupport != nullptr) {
				cout << "Seismic support of patch " << patchIndex << " is : " << seismicSupport->getTitle() << endl;
				std::unique_ptr<double[]> lineAbscissa(new double[horizonSinglePolylineRep->getXyzPointCountOfPatch(patchIndex)]);
				horizonSinglePolylineRep->getSeismicLineAbscissaOfPointsOfPatch(patchIndex, lineAbscissa.get());

				for (uint64_t j = 0; j < horizonSinglePolylineRep->getXyzPointCountOfPatch(patchIndex); j++) {
					std::cout << "line Abscissa : " << lineAbscissa[j] << std::endl;
				}
			}
		}

		showAllProperties(horizonSinglePolylineRep);
	}

	deserializeSealedSurfaceFramework(repo);
	deserializeSealedVolumeFramework(repo);

	std::cout << "STRATI COLUMN" << endl;
	for (auto* stratiColumn : stratiColumnSet) {
		deserializeStratiColumn(stratiColumn, enumStrMapper);
	}

	std::cout << "WELLBORES" << endl;
	for (auto* wellbore : wellboreSet)
	{
		showAllMetadata(wellbore);
		witsmlWellbore = wellbore->getWitsmlWellbore();
		if (witsmlWellbore != nullptr) {
			std::cout << "Associated with witsml well bore " << witsmlWellbore->getTitle()
				<< " with GUID " << witsmlWellbore->getUuid() << " and witsml well " << witsmlWellbore->getWell()->getTitle()
				<< " with GUID " << witsmlWellbore->getWell()->getUuid() << std::endl;
		}
		for (auto* interp : wellbore->getInterpretationSet()) {
			for (auto* rep : interp->getRepresentationSet()) {
				if (rep->getXmlTag() == RESQML2_NS::WellboreMarkerFrameRepresentation::XML_TAG) {
					RESQML2_NS::WellboreMarkerFrameRepresentation const * wmf = static_cast<RESQML2_NS::WellboreMarkerFrameRepresentation const *>(rep);
					for (auto* marker : wmf->getWellboreMarkerSet()) {
						std::cout << "marker : " << marker->getTitle() << std::endl;
						if (marker->getBoundaryFeatureInterpretation() != nullptr) {
							std::cout << "marker boundary feature : " << marker->getBoundaryFeatureInterpretation()->getTitle() << std::endl;
						}
					}

					for (auto* prop : wmf->getPropertySet()) {
						if (prop->getXmlTag() == RESQML2_NS::CategoricalProperty::XML_TAG) {
							RESQML2_NS::CategoricalProperty const * catVal = static_cast<RESQML2_NS::CategoricalProperty const *>(prop);
							if (catVal->getValuesHdfDatatype() == RESQML2_NS::AbstractValuesProperty::LONG_64) {
								std::cout << "Hdf datatype is NATIVE LONG" << std::endl;
								std::unique_ptr<int64_t[]> tmp(new int64_t[wmf->getMdValuesCount()]);
								catVal->getLongValuesOfPatch(0, tmp.get());
								for (size_t ind = 0; ind < 2; ind++) {
									std::cout << "Value " << ind << " : " << tmp[ind] << std::endl;
								}
							}
							else if (catVal->getValuesHdfDatatype() == RESQML2_NS::AbstractValuesProperty::INT) {
								std::cout << "Hdf datatype is NATIVE INT" << std::endl;
							}
						}
					}
				}
			}
		}
	}

	deserializePerforations(repo);
	deserializeWbGeometry(repo);
	deserializeLog(repo);

	std::cout << endl << "WELLBORES CUBIC TRAJ" << endl;
	for (auto* wellboreCubicTraj : wellboreCubicTrajSet)
	{
		showAllMetadata(wellboreCubicTraj);
		std::cout << "MD Datum is : " << wellboreCubicTraj->getMdDatum()->getTitle() << std::endl;
		std::cout << "--------------------------------------------------" << std::endl;
		if (wellboreCubicTraj->getXyzPointCountOfAllPatches() == 0) {
			break;
		}
		std::unique_ptr<double[]> mdValues(new double[wellboreCubicTraj->getXyzPointCountOfAllPatches()]);
		wellboreCubicTraj->getMdValues(mdValues.get());
		std::unique_ptr<double[]> xyzPt(new double[wellboreCubicTraj->getXyzPointCountOfAllPatches() * 3]);
		wellboreCubicTraj->getXyzPointsOfAllPatchesInGlobalCrs(xyzPt.get());
		for (size_t j = 0; j < wellboreCubicTraj->getXyzPointCountOfAllPatches() * 3 && j < 10; j += 3) {
			cout << "Trajectory station : MD=" << mdValues[j / 3] << " X=" << xyzPt[j] << " Y=" << xyzPt[j + 1] << " Z=" << xyzPt[j + 2] << endl;
		}
		std::cout << "LOGS" << endl;
		std::cout << "--------------------------------------------------" << std::endl;
		std::vector<RESQML2_NS::WellboreFrameRepresentation *> wellboreFrameSet = wellboreCubicTraj->getWellboreFrameRepresentationSet();
		for (auto* wellboreFrame : wellboreFrameSet) {
			showAllMetadata(wellboreFrame);
			std::cout << "Value Count : " << wellboreFrame->getMdValuesCount() << endl;
			if (wellboreFrame->areMdValuesRegularlySpaced()) {
				std::cout << "Regularly spaced" << std::endl;
				std::cout << "First Value : " << wellboreFrame->getMdFirstValue() << endl;
				std::cout << "Increment : " << wellboreFrame->getMdConstantIncrementValue() << endl;
			}
			else {
				std::cout << "Iregularly spaced" << std::endl;
			}
			if (wellboreFrame->getMdHdfDatatype() == RESQML2_NS::AbstractValuesProperty::DOUBLE) {
				std::cout << "Hdf datatype is NATIVE DOUBLE" << std::endl;
			}
			else if (wellboreFrame->getMdHdfDatatype() == RESQML2_NS::AbstractValuesProperty::FLOAT) {
				std::cout << "Hdf datatype is NATIVE FLOAT" << std::endl;
			}
			else if (wellboreFrame->getMdHdfDatatype() == RESQML2_NS::AbstractValuesProperty::UNKNOWN) {
				std::cout << "Hdf datatype is UNKNOWN" << std::endl;
			}
			std::cout << std::endl;
			if (dynamic_cast<RESQML2_NS::WellboreMarkerFrameRepresentation*>(wellboreFrame) != nullptr) {
				auto* markerFrame = static_cast<RESQML2_NS::WellboreMarkerFrameRepresentation*>(wellboreFrame);
				showAllMetadata(markerFrame);
				vector<RESQML2_NS::WellboreMarker*> markerSet = markerFrame->getWellboreMarkerSet();
				std::unique_ptr<double[]> doubleMds(new double[markerFrame->getMdValuesCount()]);
				markerFrame->getMdAsDoubleValues(doubleMds.get());
				for (size_t mIndex = 0; mIndex < markerSet.size(); ++mIndex) {
					if (doubleMds[mIndex] == doubleMds[mIndex]) {
						cout << doubleMds[mIndex] << endl;
					}
					else {
						cout << "NaN" << endl;
					}
					if (markerSet[mIndex]->hasDipAngle()) {
						cout << "dip Angle " << markerSet[mIndex]->getDipAngleValue() << " " << enumStrMapper.planeAngleUomToString(markerSet[mIndex]->getDipAngleUom()) << endl;
					}
					if (markerSet[mIndex]->hasDipDirection()) {
						cout << "dip Direction " << markerSet[mIndex]->getDipDirectionValue() << " " << enumStrMapper.planeAngleUomToString(markerSet[mIndex]->getDipDirectionUom()) << endl;
					}
				}
			}
#if WITH_RESQML2_2
			if (wellboreFrame->getXmlTag() == "SeismicWellboreFrameRepresentation") {
				RESQML2_2_NS::SeismicWellboreFrameRepresentation* seismicWellboreFrame = static_cast<RESQML2_2_NS::SeismicWellboreFrameRepresentation*>(wellboreFrame);
				std::cout << "Seismic reference datum : " << seismicWellboreFrame->getSeismicReferenceDatum() << std::endl;
				std::cout << "Weathering velocity : " << seismicWellboreFrame->getWeatheringVelocity() << std::endl;
				if (seismicWellboreFrame->areTimeValuesRegularlySpaced()) {
					std::cout << "Time values regularly spaced" << std::endl;
					std::cout << "First Value : " << seismicWellboreFrame->getTimeFirstValue() << endl;
					std::cout << "Increment : " << seismicWellboreFrame->getTimeConstantIncrementValue() << endl;
				}
				else {
					std::cout << "Time values iregularly spaced" << std::endl;
				}
				if (seismicWellboreFrame->getTimeHdfDatatype() == RESQML2_NS::AbstractValuesProperty::DOUBLE) {
					std::cout << "Hdf datatype is NATIVE DOUBLE" << std::endl;
				}
				else if (seismicWellboreFrame->getTimeHdfDatatype() == RESQML2_NS::AbstractValuesProperty::FLOAT) {
					std::cout << "Hdf datatype is NATIVE FLOAT" << std::endl;
				}
				else if (seismicWellboreFrame->getTimeHdfDatatype() == RESQML2_NS::AbstractValuesProperty::UNKNOWN) {
					std::cout << "Hdf datatype is UNKNOWN" << std::endl;
				}
				std::cout << std::endl;
			}
#endif
		}
	}

	deserializeIjkGrid(repo);

	std::cout << endl << "UNSTRUCTURED GRID REP" << endl;
	for (auto* unstructuredGridRep :  unstructuredGridRepSet) {
		showAllMetadata(unstructuredGridRep);
		if (!unstructuredGridRep->isPartial() && unstructuredGridRep->hasGeometry()) {
			std::cout << "Node count is : " << unstructuredGridRep->getXyzPointCountOfPatch(0) << std::endl;

			uint64_t faceCount = 0;
			if (!unstructuredGridRep->isFaceCountOfCellsConstant()) {
				std::unique_ptr<uint64_t[]> faceCountOfCells(new uint64_t[unstructuredGridRep->getCellCount()]);
				unstructuredGridRep->getCumulativeFaceCountPerCell(faceCountOfCells.get());
				std::cout << "Face count of cell 0 is : " << faceCountOfCells[0] << std::endl;
				if (unstructuredGridRep->getCellCount() > 1)
					std::cout << "Face count of cell 1 is : " << faceCountOfCells[1] - faceCountOfCells[0] << std::endl;
				faceCount = faceCountOfCells[unstructuredGridRep->getCellCount() - 1];
			}
			else {
				std::cout << "Face count of cell is constant : " << unstructuredGridRep->getConstantFaceCountOfCells() << std::endl;
				faceCount = unstructuredGridRep->getConstantFaceCountOfCells() * unstructuredGridRep->getCellCount();
			}
			if (!unstructuredGridRep->isNodeCountOfFacesConstant()) 	{
				std::unique_ptr<uint64_t[]> nodeCountOfFaces(new uint64_t[faceCount]);
				unstructuredGridRep->getCumulativeNodeCountPerFace(nodeCountOfFaces.get());
				std::cout << "Node count of face 0 is : " << nodeCountOfFaces[0] << std::endl;
				if (faceCount > 1)
					std::cout << "Node count of face 1 is : " << nodeCountOfFaces[1] - nodeCountOfFaces[0] << std::endl;
			}
			else {
				std::cout << "Node count of face is constant : " << unstructuredGridRep->getConstantNodeCountOfFaces() << std::endl;
			}


			std::cout << "Reading XYZ points" << std::endl;
			std::unique_ptr<double[]> gridPoints(new double[unstructuredGridRep->getXyzPointCountOfPatch(0) * 3]);
			unstructuredGridRep->getXyzPointsOfAllPatchesInGlobalCrs(gridPoints.get());
			std::cout << "DONE" << std::endl;
			std::cout << "--------------------------------------------------" << std::endl;

			unstructuredGridRep->loadGeometry();

			std::cout << "In memory" << std::endl;
			for (uint64_t cellIndex = 0; cellIndex < unstructuredGridRep->getCellCount(); ++cellIndex) {
				std::cout << "Face count of cell " << cellIndex << " is : " << unstructuredGridRep->getFaceCountOfCell(cellIndex) << std::endl;
				for (unsigned int faceIndex = 0; faceIndex < unstructuredGridRep->getFaceCountOfCell(cellIndex); ++faceIndex) {
					std::cout << "Node count of face " << faceIndex << " of cell " << cellIndex << " is : " << unstructuredGridRep->getNodeCountOfFaceOfCell(cellIndex, faceIndex) << std::endl;
					for (unsigned int nodeIndex = 0; nodeIndex < unstructuredGridRep->getNodeCountOfFaceOfCell(cellIndex, faceIndex); ++nodeIndex) {
						std::cout << "Node indice " << nodeIndex << " of face " << faceIndex << " of cell " << cellIndex << " is : " << unstructuredGridRep->getNodeIndicesOfFaceOfCell(cellIndex, faceIndex)[nodeIndex] << std::endl;
						std::cout << "X= " <<  gridPoints.get()[unstructuredGridRep->getNodeIndicesOfFaceOfCell(cellIndex, faceIndex)[nodeIndex] * 3] << " Y= " <<  gridPoints.get()[unstructuredGridRep->getNodeIndicesOfFaceOfCell(cellIndex, faceIndex)[nodeIndex] * 3+1 ] << " Z= " <<  gridPoints.get()[unstructuredGridRep->getNodeIndicesOfFaceOfCell(cellIndex, faceIndex)[nodeIndex] * 3+ 2 ] << std::endl;
					}
				}
			}

			unstructuredGridRep->unloadGeometry();

			showAllProperties(unstructuredGridRep);
		}

		showAllSubRepresentations(unstructuredGridRep->getSubRepresentationSet());
	}

	std::cout << endl << "ONLY PARTIAL SUBREPRESENTATIONS" << endl;
	vector<RESQML2_NS::SubRepresentation *> onlyPartialSubReps;
	for (auto* subRep : subRepresentationSet) {
		if (subRep->isPartial()) {
			onlyPartialSubReps.push_back(subRep);
		}
	}
	showAllSubRepresentations(onlyPartialSubReps);

	std::cout << endl << "TIME SERIES" << endl;
	for (auto* timeSeries : timeSeriesSet) {
		showAllMetadata(timeSeries);
		for (unsigned int j = 0; j < timeSeries->getTimestampCount(); ++j) {
			time_t creation = timeSeries->getTimestamp(j);
			std::cout << "Timestamp " << j << " is (unix timestamp) : " << creation << std::endl;
			tm creationTm = timeSeries->getTimestampAsTimeStructure(j);
			std::cout << "Timestamp " << j << " is (struct tm) : " << 1900 + creationTm.tm_year << "-" << creationTm.tm_mon + 1 << "-" << creationTm.tm_mday << "T" << creationTm.tm_hour << ":" << creationTm.tm_min << ":" << creationTm.tm_sec << std::endl;
		}
		for (size_t j = 0; j < timeSeries->getPropertySet().size(); ++j) 	{
			std::cout << endl << "\tPROPERTIES" << endl;
			showAllMetadata(timeSeries->getPropertySet()[j]);
		}
	}

#if WITH_RESQML2_2
	deserializeGraphicalInformationSet(repo);
#endif

	std::cout << endl << repo.getWarnings().size() << " WARNING(S)" << endl;
	for (size_t i = 0; i < repo.getWarnings().size(); ++i) {
		std::cout << i << " - " << repo.getWarnings()[i] << endl;
	}
}

// filepath is defined in a macro to better check memory leak
#define filePath "../../testingPackageCpp.epc"
int main()
{
	//try {
	if (serialize(filePath)) {
		deserialize(filePath);
	}
	/*}
	catch (const std::invalid_argument & Exp)
	{
	std::cerr << "Error : " << Exp.what() << ".\n";
	return 1;
	}*/

#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
