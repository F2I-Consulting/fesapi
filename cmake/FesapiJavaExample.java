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
package com.f2i_consulting.example;

import java.io.File;
import java.util.UUID;
import java.util.stream.LongStream;

import com.f2i_consulting.fesapi.SWIGTYPE_p_double;
import com.f2i_consulting.fesapi.SWIGTYPE_p_unsigned_int;
import com.f2i_consulting.fesapi.SWIGTYPE_p_unsigned_short;
import com.f2i_consulting.fesapi.StringVector;
import com.f2i_consulting.fesapi.eml20__LengthUom;
import com.f2i_consulting.fesapi.eml20__TimeUom;
import com.f2i_consulting.fesapi.eml21__LengthUom;
import com.f2i_consulting.fesapi.eml21__MassPerLengthUom;
import com.f2i_consulting.fesapi.eml21__WellStatus;
import com.f2i_consulting.fesapi.eml21__WellboreDatumReference;
import com.f2i_consulting.fesapi.eml23__WellboreDatumReference;
import com.f2i_consulting.fesapi.fesapi;
import com.f2i_consulting.fesapi.resqml20__ResqmlPropertyKind;
import com.f2i_consulting.fesapi.resqml20__ResqmlUom;
import com.f2i_consulting.fesapi.resqml22__IndexableElement;
${COMMENT_START}
import com.f2i_consulting.fesapi.resqml22__InterpolationDomain;
import com.f2i_consulting.fesapi.resqml22__InterpolationMethod;
${COMMENT_END}
import com.f2i_consulting.fesapi.resqml22__TimeSetKind;
import com.f2i_consulting.fesapi.witsml20__ChannelStatus;
import com.f2i_consulting.fesapi.witsml20__HoleCasingType;
import com.f2i_consulting.fesapi.witsml20__WellboreShape;
import com.f2i_consulting.fesapi.witsml20__WellboreType;
import com.f2i_consulting.fesapi.common.AbstractObject;
import com.f2i_consulting.fesapi.common.AbstractObject.numericalDatatypeEnum;
import com.f2i_consulting.fesapi.common.DataObjectRepository;
import com.f2i_consulting.fesapi.common.DataObjectRepository.EnergisticsStandard;
import com.f2i_consulting.fesapi.common.EpcDocument;
import com.f2i_consulting.fesapi.eml2.AbstractHdfProxy;
import com.f2i_consulting.fesapi.eml2.PropertyKind;
import com.f2i_consulting.fesapi.eml2.GraphicalInformationSet;
import com.f2i_consulting.fesapi.resqml2.AbstractIjkGridRepresentation;
import com.f2i_consulting.fesapi.resqml2.AbstractRepresentation;
import com.f2i_consulting.fesapi.resqml2.AbstractSeismicLineFeature;
import com.f2i_consulting.fesapi.resqml2.AbstractValuesProperty;
import com.f2i_consulting.fesapi.resqml2.BoundaryFeature;
import com.f2i_consulting.fesapi.resqml2.CommentProperty;
import com.f2i_consulting.fesapi.resqml2.ContinuousProperty;
import com.f2i_consulting.fesapi.resqml2.DiscreteProperty;
import com.f2i_consulting.fesapi.resqml2.EarthModelInterpretation;
import com.f2i_consulting.fesapi.resqml2.GenericFeatureInterpretation;
import com.f2i_consulting.fesapi.resqml2.Grid2dRepresentation;
import com.f2i_consulting.fesapi.resqml2.HorizonInterpretation;
import com.f2i_consulting.fesapi.resqml2.IjkGridExplicitRepresentation;
import com.f2i_consulting.fesapi.resqml2.LocalDepth3dCrs;
import com.f2i_consulting.fesapi.resqml2.LocalTime3dCrs;
import com.f2i_consulting.fesapi.resqml2.MdDatum;
import com.f2i_consulting.fesapi.resqml2.Model;
import com.f2i_consulting.fesapi.resqml2.PolylineRepresentation;
import com.f2i_consulting.fesapi.resqml2.PropertySet;
import com.f2i_consulting.fesapi.resqml2.SeismicLatticeFeature;
import com.f2i_consulting.fesapi.resqml2.SeismicLineSetFeature;
import com.f2i_consulting.fesapi.resqml2.TriangulatedSetRepresentation;
import com.f2i_consulting.fesapi.resqml2.WellboreFeature;
import com.f2i_consulting.fesapi.resqml2.WellboreFrameRepresentation;
import com.f2i_consulting.fesapi.resqml2.WellboreInterpretation;
import com.f2i_consulting.fesapi.resqml2.WellboreTrajectoryRepresentation;
import com.f2i_consulting.fesapi.resqml2.ContinuousColorMap;
import com.f2i_consulting.fesapi.resqml2.DiscreteColorMap;
import com.f2i_consulting.fesapi.resqml2.SeismicWellboreFrameRepresentation;
import com.f2i_consulting.fesapi.resqml2_0_1.Resqml20_Horizon;
import com.f2i_consulting.fesapi.witsml2.Well;
import com.f2i_consulting.fesapi.witsml2.Wellbore;
import com.f2i_consulting.fesapi.witsml2_0.Witsml20_WellboreGeometry;

public class FesapiJavaExample {
	private static String storageDirectory = System.getProperty("user.dir"); 
	private static String epcName = "testingPackageJava"; 
	
	private static BoundaryFeature horizon1;
	private static IjkGridExplicitRepresentation ijkgrid;
	private static PropertyKind cellIndexPropKind;

	/**
	 * Loading the FesapiCpp native library
	 */
	static {
		try {
			System.loadLibrary("${ASSEMBLY_NAME}");
		}
		catch (UnsatisfiedLinkError e) {
			System.out.println("UnsatisfiedLinkError : " + e.toString());
		}
	}

	private static void serializeWells(DataObjectRepository repo)
	{
		// WELL
		Well witsmlWell = repo.createWell("704a287c-5c24-4af3-a97b-bc6670f4e14f", "Well1");
		witsmlWell.setNameLegal("Legal Name");
		witsmlWell.setWaterDepth(0.0, eml21__LengthUom.ft);
		witsmlWell.setTimeZone(true, 0, 0);
		witsmlWell.pushBackLocation("8cd3c8b2-face-4426-8aea-ae34870bd969", 275, 75, 0);
		witsmlWell.pushBackDatum("aa92fa8b-d6cc-459e-b456-27fec0c08b24", "well1 msl datum", eml21__WellboreDatumReference.kelly_x0020bushing, "Mean Sea Level", eml21__LengthUom.m, 0, 5100);
		witsmlWell.pushBackDatum("d3ac5401-d3e7-4474-b846-070673b210ae", "KB", eml21__WellboreDatumReference.kelly_x0020bushing, "Mean Sea Level", eml21__LengthUom.m, 15, 5100);
	
		// WELLBORE
		Wellbore witsmlWellbore = repo.createWellbore(witsmlWell, "3bd60188-5688-43df-89bb-935fe86a813f", "Wellbore1");
		witsmlWellbore.setNumber("Wb1");
		witsmlWellbore.setStatusWellbore(eml21__WellStatus.completed);
		witsmlWellbore.setIsActive(false);
		witsmlWellbore.setTypeWellbore(witsml20__WellboreType.initial);
		witsmlWellbore.setShape(witsml20__WellboreShape.vertical);
		witsmlWellbore.setAchievedTD(true);
		witsmlWellbore.setMd(1000, eml21__LengthUom.m, "d3ac5401-d3e7-4474-b846-070673b210ae");
		witsmlWellbore.setMdPlanned(1000, eml21__LengthUom.m, "d3ac5401-d3e7-4474-b846-070673b210ae");

		// Geometry
		Witsml20_WellboreGeometry witsmlWbGeom = repo.createWellboreGeometry(witsmlWellbore, "c9dc03e9-722c-478b-b0ae-b2dd9da67c11", "My wellbore geometry", witsml20__ChannelStatus.closed);
		witsmlWbGeom.setMdBase(0, eml21__LengthUom.m, "d3ac5401-d3e7-4474-b846-070673b210ae");
		witsmlWbGeom.pushBackSection();
		witsmlWbGeom.setWellboreGeometrySectionTypeHoleCasing(0, witsml20__HoleCasingType.casing);
		witsmlWbGeom.setWellboreGeometrySectionOdSection(0, 30, eml21__LengthUom.in);
		witsmlWbGeom.setWellboreGeometrySectionMdInterval(0, 0, 250, "d3ac5401-d3e7-4474-b846-070673b210ae", eml21__LengthUom.m);
		witsmlWbGeom.setWellboreGeometrySectionTvdInterval(0, 0, 250, "d3ac5401-d3e7-4474-b846-070673b210ae", eml21__LengthUom.m);
		witsmlWbGeom.pushBackSection();
		witsmlWbGeom.setWellboreGeometrySectionTypeHoleCasing(1, witsml20__HoleCasingType.casing);
		witsmlWbGeom.setWellboreGeometrySectionCurveConductor(1, false);
		witsmlWbGeom.setWellboreGeometrySectionDiaDrift(1, 17.5, eml21__LengthUom.in);
		witsmlWbGeom.setWellboreGeometrySectionFactFric(1, 0.25);
		witsmlWbGeom.setWellboreGeometrySectionGrade(1, "L80");
		witsmlWbGeom.setWellboreGeometrySectionIdSection(1, 18, eml21__LengthUom.in);
		witsmlWbGeom.setWellboreGeometrySectionOdSection(1, 20, eml21__LengthUom.in);
		witsmlWbGeom.setWellboreGeometrySectionWtPerLen(1, 123, eml21__MassPerLengthUom.lbm_x002fft);
		witsmlWbGeom.setWellboreGeometrySectionTvdInterval(1, 0, 990, "d3ac5401-d3e7-4474-b846-070673b210ae", eml21__LengthUom.m);
		
		// Features
		WellboreFeature wellbore1 = repo.createWellboreFeature("22d5b48f-f789-46e7-a454-6d8bd05afd0b", "Wellbore1");
		
		// Interpretations
		WellboreInterpretation wellbore1Interp1 = repo.createWellboreInterpretation(wellbore1, "dc7840fe-e5a3-4b53-a1df-18040bc4d0c0", "Wellbore1 Interp1", false);

		// Representation
		MdDatum mdInfo = repo.createMdDatum("36e91de5-7833-4b6d-90d0-1d643c0adece", "md Info", repo.getDefaultCrs(), eml23__WellboreDatumReference.mean_x0020sea_x0020level, 275, 75, 0);

		//Geometry	
		WellboreTrajectoryRepresentation w1i1TrajRep = repo.createWellboreTrajectoryRepresentation(wellbore1Interp1, "acd2cdcf-bb5d-48da-bd0e-9aeff3e52180", "Wellbore1 Interp1 TrajRep", mdInfo);
		SWIGTYPE_p_double controlPoints = fesapi.new_DoubleArray(12);
		SWIGTYPE_p_double trajectoryTangentVectors = fesapi.new_DoubleArray(12);
		SWIGTYPE_p_double trajectoryMds = fesapi.new_DoubleArray(4);
		try {
			fesapi.DoubleArray_setitem(controlPoints, 0, 275);
			fesapi.DoubleArray_setitem(controlPoints, 1, 75);
			fesapi.DoubleArray_setitem(controlPoints, 2, 0);
			fesapi.DoubleArray_setitem(controlPoints, 3, 275);
			fesapi.DoubleArray_setitem(controlPoints, 4, 75);
			fesapi.DoubleArray_setitem(controlPoints, 5, 325);
			fesapi.DoubleArray_setitem(controlPoints, 6, 275);
			fesapi.DoubleArray_setitem(controlPoints, 7, 75);
			fesapi.DoubleArray_setitem(controlPoints, 8, 500);
			fesapi.DoubleArray_setitem(controlPoints, 9, 275);
			fesapi.DoubleArray_setitem(controlPoints, 10, 75);
			fesapi.DoubleArray_setitem(controlPoints, 11, 1000);
			fesapi.DoubleArray_setitem(trajectoryTangentVectors, 0, 0);
			fesapi.DoubleArray_setitem(trajectoryTangentVectors, 1, 0);
			fesapi.DoubleArray_setitem(trajectoryTangentVectors, 2, 1);
			fesapi.DoubleArray_setitem(trajectoryTangentVectors, 3, 0);
			fesapi.DoubleArray_setitem(trajectoryTangentVectors, 4, 0);
			fesapi.DoubleArray_setitem(trajectoryTangentVectors, 5, 1);
			fesapi.DoubleArray_setitem(trajectoryTangentVectors, 6, 0);
			fesapi.DoubleArray_setitem(trajectoryTangentVectors, 7, 0);
			fesapi.DoubleArray_setitem(trajectoryTangentVectors, 8, 1);
			fesapi.DoubleArray_setitem(trajectoryTangentVectors, 9, 0);
			fesapi.DoubleArray_setitem(trajectoryTangentVectors, 10, 0);
			fesapi.DoubleArray_setitem(trajectoryTangentVectors, 11, 1);
			fesapi.DoubleArray_setitem(trajectoryMds, 0, 0);
			fesapi.DoubleArray_setitem(trajectoryMds, 1, 325);
			fesapi.DoubleArray_setitem(trajectoryMds, 2, 500);
			fesapi.DoubleArray_setitem(trajectoryMds, 3, 1000);
			w1i1TrajRep.setGeometry(controlPoints, trajectoryTangentVectors, trajectoryMds, 4, 0, repo.getDefaultHdfProxy());			
		}
		finally {
			fesapi.delete_DoubleArray(controlPoints);
			fesapi.delete_DoubleArray(trajectoryTangentVectors);
			fesapi.delete_DoubleArray(trajectoryMds);
		}
		
		// WellboreFeature frame
		WellboreFrameRepresentation w1i1FrameRep = repo.createWellboreFrameRepresentation(wellbore1Interp1, "d873e243-d893-41ab-9a3e-d20b851c099f", "Wellbore1 Interp1 FrameRep", w1i1TrajRep);
		SWIGTYPE_p_double logMds = fesapi.new_DoubleArray(5);
		try {
			fesapi.DoubleArray_setitem(logMds, 0, 0);
			fesapi.DoubleArray_setitem(logMds, 1, 250);
			fesapi.DoubleArray_setitem(logMds, 2, 500);
			fesapi.DoubleArray_setitem(logMds, 3, 750);
			fesapi.DoubleArray_setitem(logMds, 4, 1000);
			w1i1FrameRep.setMdValues(logMds, 5, repo.getDefaultHdfProxy());					
		}
		finally {
			fesapi.delete_DoubleArray(logMds);
		}
	
		WellboreFrameRepresentation w1i1RegularFrameRep = repo.createWellboreFrameRepresentation(wellbore1Interp1, "a54b8399-d3ba-4d4b-b215-8d4f8f537e66", "Wellbore1 Interp1 Regular FrameRep", w1i1TrajRep);
		w1i1RegularFrameRep.setMdValues(0, 200, 6);
${COMMENT_START}
		// SeismicWellboreFrameRepresentation
		LocalTime3dCrs localTime3dCrs = repo.createLocalTime3dCrs("", "Default local time CRS", 1.0, 0.1, 15, .0, eml20__LengthUom.m, 23031, eml20__TimeUom.s, eml20__LengthUom.m, "Unknown", false);
				
		SeismicWellboreFrameRepresentation w1i1SeismicFrameRep = repo.createSeismicWellboreFrameRepresentation(
			wellbore1Interp1, "dcbeea2e-8327-4c5b-97e3-bdced0680de5", "Wellbore1 Interp1 SeismicFrameRep",
			w1i1TrajRep,
			0.,
			0.,
			localTime3dCrs);
		w1i1SeismicFrameRep.setMdValues(logMds, 5, repo.getDefaultHdfProxy());
		SWIGTYPE_p_double logTimes = fesapi.new_DoubleArray(5);
		try {
			fesapi.DoubleArray_setitem(logTimes, 0, 0);
			fesapi.DoubleArray_setitem(logTimes, 1, 10);
			fesapi.DoubleArray_setitem(logTimes, 2, 20);
			fesapi.DoubleArray_setitem(logTimes, 3, 25);
			fesapi.DoubleArray_setitem(logTimes, 4, 30);
			w1i1SeismicFrameRep.setTimeValues(logTimes, 5, repo.getDefaultHdfProxy());				
		}
		finally {
			fesapi.delete_DoubleArray(logTimes);
		}
		
		SeismicWellboreFrameRepresentation w1i1RegularSeismicFrameRep = repo.createSeismicWellboreFrameRepresentation(
			wellbore1Interp1, "7f1b75ff-1226-4c0a-a531-8f71661da419", "Wellbore1 Interp1 Regular SeismicFrameRep",
			w1i1TrajRep,
			0.,
			0.,
			localTime3dCrs);
		w1i1RegularSeismicFrameRep.setMdValues(0, 200, 6);
		w1i1RegularSeismicFrameRep.setTimeValues(0., 10., 6);
${COMMENT_END}
	}

	private static void serializeBoundaries(DataObjectRepository repo, AbstractHdfProxy hdfProxy) {
		// Seismic Lattice
		SeismicLatticeFeature seismicLattice = repo.createSeismicLattice("eb6a5e97-4d86-4809-b136-051f34cfcb51", "Seismic lattice", 2, 2, 150, 152, 4, 2);
		GenericFeatureInterpretation seismicLatticeInterp = repo.createGenericFeatureInterpretation(seismicLattice, "97816427-6ef6-4776-b21c-5b93c8a6310a", "Seismic lattice Interp");
		Grid2dRepresentation seismicLatticeRep = repo.createGrid2dRepresentation(seismicLatticeInterp, "aa5b90f1-2eab-4fa6-8720-69dd4fd51a4d", "Seismic lattice Rep");
		seismicLatticeRep.setGeometryAsArray2dOfLatticePoints3d(4, 2, 0, 0, 0, 1, 0, 2, 0, 1, 3, 250, 200);

		// Seismic Line Set
		SeismicLineSetFeature seismicLineSet = repo.createSeismicLineSet("53c6a0be-c901-4bb6-845b-fba79745da02", "Seismic line Set");

		// Seismic Line
		AbstractSeismicLineFeature seismicLine = null;
		if (repo.getDefaultResqmlVersion() == EnergisticsStandard.RESQML2_0_1) {
			seismicLine = repo.createSeismicLine("117f9bf6-6bb0-49f2-9cee-46912300bff6", "Seismic line", 1, 0, 5);
		}
		else {
${COMMENT_START}
			seismicLine = repo.createShotPointLine("117f9bf6-6bb0-49f2-9cee-46912300bff6", "Seismic line");
${COMMENT_END}
		}
		seismicLine.setSeismicLineSet(seismicLineSet);
		GenericFeatureInterpretation seismicLineInterp = repo.createGenericFeatureInterpretation(seismicLine, "", "Seismic line Interp");
		PolylineRepresentation seismicLineRep = repo.createPolylineRepresentation(seismicLineInterp, "", "Seismic line Rep");
		SWIGTYPE_p_double seismicLinePoints = fesapi.new_DoubleArray(15);
		try {
			fesapi.DoubleArray_setitem(seismicLinePoints, 0, 0);
			fesapi.DoubleArray_setitem(seismicLinePoints, 1, 100);
			fesapi.DoubleArray_setitem(seismicLinePoints, 2, 0);
			fesapi.DoubleArray_setitem(seismicLinePoints, 3, 150);
			fesapi.DoubleArray_setitem(seismicLinePoints, 4, 110);
			fesapi.DoubleArray_setitem(seismicLinePoints, 5, 0);
			fesapi.DoubleArray_setitem(seismicLinePoints, 6, 300);
			fesapi.DoubleArray_setitem(seismicLinePoints, 7, 120);
			fesapi.DoubleArray_setitem(seismicLinePoints, 8, 0);
			fesapi.DoubleArray_setitem(seismicLinePoints, 9, 450);
			fesapi.DoubleArray_setitem(seismicLinePoints, 10, 130);
			fesapi.DoubleArray_setitem(seismicLinePoints, 11, 0);
			fesapi.DoubleArray_setitem(seismicLinePoints, 12, 600);
			fesapi.DoubleArray_setitem(seismicLinePoints, 13, 140);
			fesapi.DoubleArray_setitem(seismicLinePoints, 14, 0);
			seismicLineRep.setGeometry(seismicLinePoints, 5, hdfProxy);
		}
		finally {
			fesapi.delete_DoubleArray(seismicLinePoints);
		}

		// Features
		horizon1 = repo.createHorizon("35d7b57e-e5ff-4062-95af-ba2d7c4ce347", "Horizon1");
		if (horizon1 instanceof Resqml20_Horizon) {
			((Resqml20_Horizon)horizon1).setAge(300000000);
		}

		// Interpretations
		HorizonInterpretation horizon1Interp1 = repo.createHorizonInterpretation(horizon1, "ac12dc12-4951-459b-b585-90f48aa88a5a", "Horizon1 Interp1");

		// Horizon Representations
		PolylineRepresentation h1i1SinglePolylineRep = repo.createPolylineRepresentation(horizon1Interp1, "", "Horizon1 Interp1 SinglePolylineRep");

		SWIGTYPE_p_double h1i1SinglePolylineRepPoints = fesapi.new_DoubleArray(12);
		try {
			fesapi.DoubleArray_setitem(h1i1SinglePolylineRepPoints, 0, 0);
			fesapi.DoubleArray_setitem(h1i1SinglePolylineRepPoints, 1, 100);
			fesapi.DoubleArray_setitem(h1i1SinglePolylineRepPoints, 2, 300);
			fesapi.DoubleArray_setitem(h1i1SinglePolylineRepPoints, 3, 150);
			fesapi.DoubleArray_setitem(h1i1SinglePolylineRepPoints, 4, 110);
			fesapi.DoubleArray_setitem(h1i1SinglePolylineRepPoints, 5, 300);
			fesapi.DoubleArray_setitem(h1i1SinglePolylineRepPoints, 6, 450);
			fesapi.DoubleArray_setitem(h1i1SinglePolylineRepPoints, 7, 130);
			fesapi.DoubleArray_setitem(h1i1SinglePolylineRepPoints, 8, 350);
			fesapi.DoubleArray_setitem(h1i1SinglePolylineRepPoints, 9, 600);
			fesapi.DoubleArray_setitem(h1i1SinglePolylineRepPoints, 10, 140);
			fesapi.DoubleArray_setitem(h1i1SinglePolylineRepPoints, 11, 350);
			h1i1SinglePolylineRep.setGeometry(h1i1SinglePolylineRepPoints, 4, hdfProxy);
		}
		finally {
			fesapi.delete_DoubleArray(h1i1SinglePolylineRepPoints);
		}

		SWIGTYPE_p_double seismicLineAbscissa = fesapi.new_DoubleArray(4);
		try {
			fesapi.DoubleArray_setitem(seismicLineAbscissa, 0, 0.0);
			fesapi.DoubleArray_setitem(seismicLineAbscissa, 1, 1.0);
			fesapi.DoubleArray_setitem(seismicLineAbscissa, 2, 3.0);
			fesapi.DoubleArray_setitem(seismicLineAbscissa, 3, 4.0);
			h1i1SinglePolylineRep.addSeismic2dCoordinatesToPatch(0, seismicLineAbscissa, seismicLineRep, hdfProxy);
		}
		finally {
			fesapi.delete_DoubleArray(seismicLineAbscissa);
		}
		
		PropertyKind commentPropType = repo.createPropertyKind("0845ad74-2673-408e-b125-8dabc26ae552", "comment prop type", "urn:resqml:f2i.com:testingAPI", resqml20__ResqmlUom.Euc, resqml20__ResqmlPropertyKind.RESQML_x0020root_x0020property);
		CommentProperty commentProperty = repo.createCommentProperty(h1i1SinglePolylineRep, "ab70d9ca-7745-474a-8b43-f2cf7ed11838", "My comment property", 1, resqml22__IndexableElement.nodes, commentPropType);
		StringVector myComments = new StringVector();
		myComments.add("Comment0");
		myComments.add("Comment1");
		myComments.add("Comment2");
		myComments.add("Comment3");
		commentProperty.pushBackStringHdf5ArrayOfValues(myComments, hdfProxy);

		Grid2dRepresentation h1i1SingleGrid2dRep = repo.createGrid2dRepresentation(horizon1Interp1, "7281e7b0-ca21-477d-b118-e9b7200e2809", "Horizon1 Interp1 Grid2dRep");
		SWIGTYPE_p_double zValues = fesapi.new_DoubleArray(8);
		try {
			fesapi.DoubleArray_setitem(zValues, 0, 300.0);
			fesapi.DoubleArray_setitem(zValues, 1, 300.0);
			fesapi.DoubleArray_setitem(zValues, 2, 350.0);
			fesapi.DoubleArray_setitem(zValues, 3, 350.0);
			fesapi.DoubleArray_setitem(zValues, 4, 300.0);
			fesapi.DoubleArray_setitem(zValues, 5, 300.0);
			fesapi.DoubleArray_setitem(zValues, 6, 350.0);
			fesapi.DoubleArray_setitem(zValues, 7, 350.0);
			h1i1SingleGrid2dRep.setGeometryAsArray2dOfExplicitZ(zValues, 4, 2, hdfProxy, seismicLatticeRep);
		}
		finally {
			fesapi.delete_DoubleArray(zValues);
		}

		// Horizon 1 triangulated representation
		TriangulatedSetRepresentation h1i1triRep = repo.createTriangulatedSetRepresentation(horizon1Interp1,
				"0c49b40a-632a-457a-b519-a178f40a397d",
				"Horizon1 Interp1 TriRep");
		// Patch 0
		SWIGTYPE_p_double explicitPointsHor1Patch0 = fesapi.new_DoubleArray(15);
		SWIGTYPE_p_unsigned_int triangleNodeIndexHorPatch0 = fesapi.new_UIntArray(9);
		try {
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 0, 0);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 1, 100);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 2, 0);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 3, 150);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 4, 110);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 5, 0);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 6, 300);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 7, 120);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 8, 0);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 9, 450);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 10, 130);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 11, 0);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 12, 600);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 13, 140);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 14, 0);

			fesapi.UIntArray_setitem(triangleNodeIndexHorPatch0, 0, 0);
			fesapi.UIntArray_setitem(triangleNodeIndexHorPatch0, 1, 1);
			fesapi.UIntArray_setitem(triangleNodeIndexHorPatch0, 2, 3);
			fesapi.UIntArray_setitem(triangleNodeIndexHorPatch0, 3, 1);
			fesapi.UIntArray_setitem(triangleNodeIndexHorPatch0, 4, 4);
			fesapi.UIntArray_setitem(triangleNodeIndexHorPatch0, 5, 3);
			fesapi.UIntArray_setitem(triangleNodeIndexHorPatch0, 6, 1);
			fesapi.UIntArray_setitem(triangleNodeIndexHorPatch0, 7, 2);
			fesapi.UIntArray_setitem(triangleNodeIndexHorPatch0, 8, 4);

			h1i1triRep.pushBackTrianglePatch(5, explicitPointsHor1Patch0, 3, triangleNodeIndexHorPatch0, hdfProxy);
		}
		finally {
			fesapi.delete_DoubleArray(explicitPointsHor1Patch0);
			fesapi.delete_UIntArray(triangleNodeIndexHorPatch0);
		}
		// Patch 1
		SWIGTYPE_p_double explicitPointsHor1Patch1 = fesapi.new_DoubleArray(15);
		SWIGTYPE_p_unsigned_int triangleNodeIndexHorPatch1 = fesapi.new_UIntArray(9);
		try {
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 0, 300);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 1, 0);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 2, 350);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 3, 300);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 4, 100);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 5, 350);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 6, 300);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 7, 200);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 8, 350);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 9, 700);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 10, 0);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 11, 350);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 12, 700);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 13, 200);
			fesapi.DoubleArray_setitem(explicitPointsHor1Patch0, 14, 350);

			fesapi.UIntArray_setitem(triangleNodeIndexHorPatch0, 0, 5);
			fesapi.UIntArray_setitem(triangleNodeIndexHorPatch0, 1, 6);
			fesapi.UIntArray_setitem(triangleNodeIndexHorPatch0, 2, 8);
			fesapi.UIntArray_setitem(triangleNodeIndexHorPatch0, 3, 6);
			fesapi.UIntArray_setitem(triangleNodeIndexHorPatch0, 4, 9);
			fesapi.UIntArray_setitem(triangleNodeIndexHorPatch0, 5, 8);
			fesapi.UIntArray_setitem(triangleNodeIndexHorPatch0, 6, 6);
			fesapi.UIntArray_setitem(triangleNodeIndexHorPatch0, 7, 7);
			fesapi.UIntArray_setitem(triangleNodeIndexHorPatch0, 8, 9);

			h1i1triRep.pushBackTrianglePatch(5, explicitPointsHor1Patch1, 3, triangleNodeIndexHorPatch1, hdfProxy);
		}
		finally {
			fesapi.delete_DoubleArray(explicitPointsHor1Patch1);
			fesapi.delete_UIntArray(triangleNodeIndexHorPatch1);
		}

		//
		// Properties
		//
		PropertyKind  propType1 = repo.createPropertyKind("f7ad7cf5-f2e7-4daa-8b13-7b3df4edba3b", "propType1", "urn:resqml:f2i.com:testingAPI", resqml20__ResqmlUom.Euc, resqml20__ResqmlPropertyKind.continuous);
		ContinuousProperty contProp1 = repo.createContinuousProperty(h1i1SingleGrid2dRep, "fcaccfc7-10cb-4f73-800e-a381642478cb", "Horizon1 Interp1 Grid2dRep Prop1", 2,
				resqml22__IndexableElement.nodes, "exoticMeter", propType1);
		SWIGTYPE_p_double prop1Values = fesapi.new_DoubleArray(16);
		try {
			fesapi.DoubleArray_setitem(prop1Values, 0, 301);
			fesapi.DoubleArray_setitem(prop1Values, 1, 302);
			fesapi.DoubleArray_setitem(prop1Values, 2, 301);
			fesapi.DoubleArray_setitem(prop1Values, 3, 302);
			fesapi.DoubleArray_setitem(prop1Values, 4, 351);
			fesapi.DoubleArray_setitem(prop1Values, 5, 352);
			fesapi.DoubleArray_setitem(prop1Values, 6, 351);
			fesapi.DoubleArray_setitem(prop1Values, 7, 352);
			fesapi.DoubleArray_setitem(prop1Values, 8, 301);
			fesapi.DoubleArray_setitem(prop1Values, 9, 302);
			fesapi.DoubleArray_setitem(prop1Values, 10, 301);
			fesapi.DoubleArray_setitem(prop1Values, 11, 302);
			fesapi.DoubleArray_setitem(prop1Values, 12, 351);
			fesapi.DoubleArray_setitem(prop1Values, 13, 352);
			fesapi.DoubleArray_setitem(prop1Values, 14, 351);
			fesapi.DoubleArray_setitem(prop1Values, 15, 352);

			contProp1.pushBackDoubleHdf5Array2dOfValues(prop1Values, 2, 8, hdfProxy);
		}
		finally {
			fesapi.delete_DoubleArray(prop1Values);
		}
	}
	
	private static void serializeIjkGrid(DataObjectRepository repo, AbstractHdfProxy hdfProxy)
	{
		cellIndexPropKind = repo.createPropertyKind("0a5f4400-fa3e-11e5-80a4-0002a5d5c51b", "cellIndex", "urn:resqml:f2i-consulting.com", resqml20__ResqmlUom.Euc, resqml20__ResqmlPropertyKind.discrete);
		Model earthModel = repo.createEarthModel("f2060ce0-fa3d-11e5-8620-0002a5d5c51b", "Grid");
		EarthModelInterpretation earthModelInterp = repo.createEarthModelInterpretation(earthModel, "f5cd7520-fa3d-11e5-b65b-0002a5d5c51b", "Grid interp");
		ijkgrid = repo.createIjkGridExplicitRepresentation(earthModelInterp, "df2103a0-fa3d-11e5-b8d4-0002a5d5c51b", "Two faulted sugar cubes (explicit geometry)", 2, 1, 1);
		DiscreteProperty discreteProp1 = repo.createDiscreteProperty(ijkgrid, "ee0857fe-23ad-4dd9-8300-21fa2e9fb572", "Two faulted sugar cubes cellIndex", 1,
				resqml22__IndexableElement.cells, cellIndexPropKind);

		SWIGTYPE_p_unsigned_short propValues = fesapi.new_UShortArray(2);
		try {
			fesapi.UShortArray_setitem(propValues, 0, 0);
			fesapi.UShortArray_setitem(propValues, 1, 1);
			discreteProp1.pushBackUShortHdf5Array3dOfValues(propValues, 2, 1, 1, hdfProxy, 1111);
		}
		finally {
			fesapi.delete_UShortArray(propValues);
		}
		
		DiscreteProperty discreteProp2 = repo.createDiscreteProperty(ijkgrid, "", "Two faulted sugar cubes other cellIndex", 1,
				resqml22__IndexableElement.cells, cellIndexPropKind);

		propValues = fesapi.new_UShortArray(2);
		try {
			fesapi.UShortArray_setitem(propValues, 0, 10);
			fesapi.UShortArray_setitem(propValues, 1, 11);
			discreteProp2.pushBackUShortHdf5Array3dOfValues(propValues, 2, 1, 1, hdfProxy, 1111);
		}
		finally {
			fesapi.delete_UShortArray(propValues);
		}
		
		PropertySet propSet = repo.createPropertySet("", "Testing property set", false, true, resqml22__TimeSetKind.not_x0020a_x0020time_x0020set);
		propSet.pushBackProperty(discreteProp1);
		propSet.pushBackProperty(discreteProp2);
	}
${COMMENT_START}
	private static void serializeGraphicalInformationSet(DataObjectRepository repo, AbstractHdfProxy hdfProxy)
	{
		GraphicalInformationSet graphicalInformationSet = repo.createGraphicalInformationSet("be17c053-9189-4bc0-9db1-75aa51a026cd", "Graphical Information Set");

		// *************
		// Default color
		// *************

		// horizon1 representation is red
		graphicalInformationSet.setDefaultHsvColor(horizon1, 0., 1., 1., 1., "red");

		// ******************
		// Discrete color map
		// ******************

		// associating a discrete color map to dicreteProp1
		DiscreteColorMap discrColMap = repo.createDiscreteColorMap("3daf4661-ae8f-4357-adee-0b0159bdd0a9", "Discrete color map");
		SWIGTYPE_p_unsigned_int discrColMapRgbColors = fesapi.new_UIntArray(18);
		SWIGTYPE_p_double discrColMapAlphas = fesapi.new_DoubleArray(6);
		try {
			fesapi.UIntArray_setitem(discrColMapRgbColors, 0, 255);
			fesapi.UIntArray_setitem(discrColMapRgbColors, 1, 0);
			fesapi.UIntArray_setitem(discrColMapRgbColors, 2, 0);
			fesapi.UIntArray_setitem(discrColMapRgbColors, 3, 0);
			fesapi.UIntArray_setitem(discrColMapRgbColors, 4, 255);
			fesapi.UIntArray_setitem(discrColMapRgbColors, 5, 0);
			fesapi.UIntArray_setitem(discrColMapRgbColors, 6, 0);
			fesapi.UIntArray_setitem(discrColMapRgbColors, 7, 0);
			fesapi.UIntArray_setitem(discrColMapRgbColors, 8, 255);
			fesapi.UIntArray_setitem(discrColMapRgbColors, 9, 169);
			fesapi.UIntArray_setitem(discrColMapRgbColors, 10, 84);
			fesapi.UIntArray_setitem(discrColMapRgbColors, 11, 27);
			fesapi.UIntArray_setitem(discrColMapRgbColors, 12, 0);
			fesapi.UIntArray_setitem(discrColMapRgbColors, 13, 0);
			fesapi.UIntArray_setitem(discrColMapRgbColors, 14, 0);
			fesapi.UIntArray_setitem(discrColMapRgbColors, 15, 255);
			fesapi.UIntArray_setitem(discrColMapRgbColors, 16, 255);
			fesapi.UIntArray_setitem(discrColMapRgbColors, 17, 255);

			fesapi.DoubleArray_setitem(discrColMapAlphas, 0, 1.);
			fesapi.DoubleArray_setitem(discrColMapAlphas, 1, 1.);
			fesapi.DoubleArray_setitem(discrColMapAlphas, 2, 1.);
			fesapi.DoubleArray_setitem(discrColMapAlphas, 3, 1.);
			fesapi.DoubleArray_setitem(discrColMapAlphas, 4, 1.);
			fesapi.DoubleArray_setitem(discrColMapAlphas, 5, 1.);

			StringVector discrColMapTitles = new StringVector();
			discrColMapTitles.add("red");
			discrColMapTitles.add("green");
			discrColMapTitles.add("blue");
			discrColMapTitles.add("orange");
			discrColMapTitles.add("black");
			discrColMapTitles.add("white");

			discrColMap.setRgbColors(6, discrColMapRgbColors, discrColMapAlphas, discrColMapTitles);
		}
		finally {
			fesapi.delete_UIntArray(discrColMapRgbColors);
			fesapi.delete_DoubleArray(discrColMapAlphas);
		}

		DiscreteProperty discreteProp2 = repo.createDiscreteProperty(ijkgrid, "1e2822ef-b6cb-4123-bdf4-c99df84a896f", "Another two faulted sugar cubes cellIndex", 1,
				resqml22__IndexableElement.cells, cellIndexPropKind);
		SWIGTYPE_p_unsigned_short propValues = fesapi.new_UShortArray(2);
		try {
			fesapi.UShortArray_setitem(propValues, 0, 10);
			fesapi.UShortArray_setitem(propValues, 1, 11);
			discreteProp2.pushBackUShortHdf5Array3dOfValues(propValues, 2, 1, 1, hdfProxy, 1111);
		}
		finally {
			fesapi.delete_UShortArray(propValues);
		}
	
		graphicalInformationSet.setDiscreteColorMap(discreteProp2, discrColMap);


		// ********************
		// Continuous color map
		// ********************

		BoundaryFeature contColMapHrz = repo.createHorizon("b9ec6ec9-2766-4af7-889e-5565b5fa5022", "Horizon for continuous color map");
		HorizonInterpretation contColMapHrzInterp = repo.createHorizonInterpretation(contColMapHrz, "34b69c81-6cfa-4531-be5b-f6bd9b74802f", "Horizon interpretation for continuous color map");
		Grid2dRepresentation contColMapGrid2dRep = repo.createGrid2dRepresentation(contColMapHrzInterp, "4e56b0e4-2cd1-4efa-97dd-95f72bcf9f80", "100x10 grid 2d for continuous color map");
		int numPointInFastestDirection = 50;
		int numPointsInSlowestDirection = 100;
		contColMapGrid2dRep.setGeometryAsArray2dOfLatticePoints3d(numPointInFastestDirection, numPointsInSlowestDirection,
				0., 0., 0.,
				1., 0., 0.,
				0., 1., 0.,
				1., 1.);

		ContinuousProperty contColMapContProp = repo.createContinuousProperty(contColMapGrid2dRep, "c2be50b6-08d2-461b-81a4-73dbb04ba605", "Continuous property for continuous color map", 2,
				resqml22__IndexableElement.nodes, "continuousColorMapIndex", resqml20__ResqmlPropertyKind.continuous);
		SWIGTYPE_p_double values = fesapi.new_DoubleArray(numPointInFastestDirection * numPointsInSlowestDirection);
		try {
			for (int slowestIndex = 0; slowestIndex < numPointsInSlowestDirection; ++slowestIndex) {
				for (int fastestIndex = 0; fastestIndex < numPointInFastestDirection; ++fastestIndex) {
					fesapi.DoubleArray_setitem(values, fastestIndex + slowestIndex * numPointInFastestDirection, fastestIndex * (1. / (numPointInFastestDirection - 1)));
				}
			}
		}
		finally {
			fesapi.delete_DoubleArray(values);
		}
		contColMapContProp.pushBackDoubleHdf5Array2dOfValues(values, numPointInFastestDirection, numPointsInSlowestDirection, hdfProxy);

		ContinuousColorMap contColMap = repo.createContinuousColorMap("a207faa2-963e-48d6-b3ad-53f6c1fc4dd4", "Continuous color map", resqml22__InterpolationDomain.rgb, resqml22__InterpolationMethod.linear);
		SWIGTYPE_p_unsigned_int contColMapRgbColors = fesapi.new_UIntArray(6);
		SWIGTYPE_p_double contColMapAlphas = fesapi.new_DoubleArray(2);
		try {
			fesapi.UIntArray_setitem(contColMapRgbColors, 0, 0);
			fesapi.UIntArray_setitem(contColMapRgbColors, 1, 255);
			fesapi.UIntArray_setitem(contColMapRgbColors, 2, 0);
			fesapi.UIntArray_setitem(contColMapRgbColors, 3, 255);
			fesapi.UIntArray_setitem(contColMapRgbColors, 4, 0);
			fesapi.UIntArray_setitem(contColMapRgbColors, 5, 0);

			fesapi.DoubleArray_setitem(contColMapAlphas, 0, 1.);
			fesapi.DoubleArray_setitem(contColMapAlphas, 1, 1.);

			StringVector contColMapColTitles = new StringVector();
			contColMapColTitles.add("green");
			contColMapColTitles.add("red");

			contColMap.setRgbColors(2, contColMapRgbColors, contColMapAlphas, contColMapColTitles);
		}
		finally {
			fesapi.delete_UIntArray(contColMapRgbColors);
			fesapi.delete_DoubleArray(contColMapAlphas);
		}

		graphicalInformationSet.setContinuousColorMap(contColMapContProp, contColMap);
	}
${COMMENT_END}
	private static void serialize()
	{		
		try (DataObjectRepository repo = new DataObjectRepository()) {
			LocalDepth3dCrs crs = repo.createLocalDepth3dCrs(UUID.randomUUID().toString(), "UTF8 Crs title", 0.0, 0.0, 0.0, 0.0, eml20__LengthUom.m, 5215, eml20__LengthUom.m, "Unknown", false);
			repo.setDefaultCrs(crs);
			AbstractHdfProxy hdfProxy = repo.createHdfProxy("", "Hdf Proxy", storageDirectory, epcName + ".h5", DataObjectRepository.openingMode.OVERWRITE);
			repo.setDefaultHdfProxy(hdfProxy);
			
			// WITSML
			serializeWells(repo);

			// RESQML
			serializeBoundaries(repo, hdfProxy);			
			serializeIjkGrid(repo, hdfProxy);
${COMMENT_START}
			serializeGraphicalInformationSet(repo, hdfProxy);
${COMMENT_END}

			try (EpcDocument pck = new EpcDocument(storageDirectory + File.separator + epcName + ".epc")) {
				pck.serializeFrom(repo);
			}
		}
	}

	private static void deserialize()
	{
		try (DataObjectRepository repo = new DataObjectRepository()) {
			try (EpcDocument pck = new EpcDocument(storageDirectory + File.separator + epcName + ".epc")) {
				String status = pck.deserializeInto(repo);
				if (!status.isEmpty()) {
					System.out.println("Status : " + status);
				}
			}

			LongStream.range(0, repo.getLocalDepth3dCrsCount()).forEach(index -> System.out.println("CRS title is " + repo.getLocalDepth3dCrs(index).getTitle()));

			System.out.println("HORIZONS GRID 2D REP");
			for (long i = 0; i < repo.getHorizonGrid2dRepresentationCount(); i++) {
				Grid2dRepresentation horizonGrid2d = repo.getHorizonGrid2dRepresentation(i);

				System.out.println("X origin " + horizonGrid2d.getXOriginInGlobalCrs());
				System.out.println("Y origin " + horizonGrid2d.getYOriginInGlobalCrs());

				System.out.println("I Node Count " + horizonGrid2d.getNodeCountAlongIAxis());
				System.out.println("J Node Count " + horizonGrid2d.getNodeCountAlongJAxis());
				SWIGTYPE_p_double zValues = fesapi.new_DoubleArray(horizonGrid2d.getNodeCountAlongIAxis() * horizonGrid2d.getNodeCountAlongJAxis());
				try {
					horizonGrid2d.getZValuesInGlobalCrs(zValues);
					System.out.println("First zValue is : " + fesapi.DoubleArray_getitem(zValues, 0));
					System.out.println("Second zValue is : " + fesapi.DoubleArray_getitem(zValues, 1));
					System.out.println("Third zValue is : " + fesapi.DoubleArray_getitem(zValues, 2));
					System.out.println("Fourth zValue is : " + fesapi.DoubleArray_getitem(zValues, 3));
					System.out.println("Fifth zValue is : " + fesapi.DoubleArray_getitem(zValues, 4));
				}
				finally {
					fesapi.delete_DoubleArray(zValues);
				}
				System.out.println("XIOffset : " + horizonGrid2d.getXIOffsetInGlobalCrs());
				System.out.println("YIOffset : " + horizonGrid2d.getYIOffsetInGlobalCrs());
				System.out.println("XJOffset : " + horizonGrid2d.getXJOffsetInGlobalCrs());
				System.out.println("YJOffset : " + horizonGrid2d.getYJOffsetInGlobalCrs());
				if (horizonGrid2d.isISpacingConstant()) {
					System.out.println("Spacing in I is constant : " + horizonGrid2d.getISpacing());
				}
				else {
					System.out.println("Spacing in I is not constant.");
				}
				if (horizonGrid2d.isJSpacingConstant()) {
					System.out.println("Spacing in J is constant : " + horizonGrid2d.getJSpacing());
				}
				else {
					System.out.println("Spacing in J is not constant.");
				}
			}
			
			long horizonPolylineCount = repo.getHorizonPolylineRepresentationCount();
			for (long i = 0; i < horizonPolylineCount; i++) {
				PolylineRepresentation horizonPolyline = repo.getHorizonPolylineRepresentation(i);
				long propCount = horizonPolyline.getValuesPropertyCount();
				for (long j = 0; j < propCount; j++) {
					AbstractValuesProperty prop = horizonPolyline.getValuesProperty(j);
					if (prop instanceof CommentProperty) {
						StringVector myComments = ((CommentProperty)prop).getStringValuesOfPatch(0);
						for (int k = 0; k < myComments.size(); k++) {
							System.out.println(myComments.get(k));
						}
					}
				}
			}

			deserializeWell(repo);

			deserializeIjkGrid(repo);
${COMMENT_START}
			System.out.println("GRAPHICAL INFORMATIONS");
			GraphicalInformationSet graphicalInformationSet = (GraphicalInformationSet) repo.getDataObjectByUuid("be17c053-9189-4bc0-9db1-75aa51a026cd");
			for (int i = 0; i < graphicalInformationSet.getGraphicalInformationSetCount(); ++i)
			{
				AbstractObject targetObject = graphicalInformationSet.getTargetObject(i);

				System.out.println("graphical information for: " + targetObject.getTitle());

				if (graphicalInformationSet.hasDefaultColor(targetObject)) {
					System.out.println("default hue: " + graphicalInformationSet.getDefaultHue(targetObject));
					System.out.println("default saturation: " + graphicalInformationSet.getDefaultSaturation(targetObject));
					System.out.println("default value: " + graphicalInformationSet.getDefaultValue(targetObject));
					System.out.println("default alpha: " + graphicalInformationSet.getDefaultAlpha(targetObject));
					if (graphicalInformationSet.hasDefaultColorTitle(targetObject)) {
						System.out.println("default color title: " + graphicalInformationSet.getDefaultColorTitle(targetObject));
					}
				}

				if (graphicalInformationSet.hasDiscreteColorMap(targetObject)) {
					DiscreteColorMap discreteColorMap = graphicalInformationSet.getDiscreteColorMap(targetObject);
					System.out.println("discrete color map title: " + discreteColorMap.getTitle());
					SWIGTYPE_p_unsigned_int r = fesapi.new_UIntArray(1);
					SWIGTYPE_p_unsigned_int g = fesapi.new_UIntArray(1);
					SWIGTYPE_p_unsigned_int b = fesapi.new_UIntArray(1);
					for (int colorIndex = 0; colorIndex < discreteColorMap.getColorCount(); ++colorIndex) {
						discreteColorMap.getRgbColor(colorIndex, r, g, b);
						System.out.print(colorIndex  + ": (" + fesapi.UIntArray_getitem(r, 0) + ", " + fesapi.UIntArray_getitem(g, 0) + ", " + fesapi.UIntArray_getitem(b, 0) + ", ");
						System.out.print(discreteColorMap.getAlpha(colorIndex));
						if (discreteColorMap.hasColorTitle(colorIndex)) {
							System.out.print(", " + discreteColorMap.getColorTitle(colorIndex));
						}
						System.out.println(")");
					}
				}

				if (graphicalInformationSet.hasContinuousColorMap(targetObject)) {
					ContinuousColorMap continuousColorMap = graphicalInformationSet.getContinuousColorMap(targetObject);
					System.out.println("continuous color map title: " + continuousColorMap.getTitle());
					SWIGTYPE_p_double r = fesapi.new_DoubleArray(1);
					SWIGTYPE_p_double g = fesapi.new_DoubleArray(1);
					SWIGTYPE_p_double b = fesapi.new_DoubleArray(1);

					for (int colorIndex = 0; colorIndex < continuousColorMap.getColorCount(); ++colorIndex) {
						continuousColorMap.getRgbColor(colorIndex, r, g, b);
						System.out.print(colorIndex + ": (" + fesapi.DoubleArray_getitem(r, 0) + ", " + fesapi.DoubleArray_getitem(g, 0) + ", " + fesapi.DoubleArray_getitem(b, 0) + ", ");
						System.out.print(continuousColorMap.getAlpha(colorIndex));
						if (continuousColorMap.hasColorTitle(colorIndex)) {
							System.out.print(", " + continuousColorMap.getColorTitle(colorIndex));
						}
						System.out.println(")");
					}
				}
			}
${COMMENT_END}			
		}
	}
	
	private static void showAllProperties(AbstractRepresentation rep)
	{
		long propCount = rep.getValuesPropertyCount();
		if (propCount > 0) {
			System.out.println("PROPERTIES");
		}
		for (long propIndex = 0; propIndex < propCount; ++propIndex) {
			AbstractValuesProperty propVal = rep.getValuesProperty(propIndex);
			System.out.println("\tProperty : " + propVal.getTitle());

			long propSetCount = propVal.getPropertySetCount();
			for (long propSetIndex = 0; propSetIndex < propSetCount; ++propSetIndex) {
				PropertySet propSet = propVal.getPropertySet(propSetIndex);
				System.out.println("\tContained in property set : " + propSet.getTitle());
			}
		}
	}

	private static void deserializeWell(DataObjectRepository repo) {
		for (int wellIdx = 0; wellIdx < repo.getWitsmlWellCount(); ++wellIdx) {
			Well witsmlWell = repo.getWitsmlWell(wellIdx);
			System.out.println("witsml Well: " + witsmlWell.getTitle() + " (" + witsmlWell.getUuid() + ")");
			System.out.println("Location projected X : " + witsmlWell.getLocationProjectedX(0));
			System.out.println("Location projected Y : " + witsmlWell.getLocationProjectedY(0));
			System.out.println("\tnameLegal : " + witsmlWell.getNameLegal());
			System.out.println("\twaterDepth : " + witsmlWell.getWaterDepthValue() + " (" + witsmlWell.getWaterDepthUom() + ")");
			if (witsmlWell.hasTimeZone())
			{
				System.out.println("\ttimeZone : " + witsmlWell.getTimeZoneHours() + " hours");
			}
			for (int wellboreIdx = 0; wellboreIdx < witsmlWell.getWellboreCount(); ++wellboreIdx) {
				Wellbore witsmlWellbore = witsmlWell.getWellbore(wellboreIdx);
				System.out.println("witsml wellbore: " + witsmlWellbore.getTitle() + " (" + witsmlWellbore.getUuid() + ")");
				for (int wbGeomIdx = 0; wbGeomIdx < witsmlWellbore.getWellboreGeometryCount(); ++wbGeomIdx) {
					Witsml20_WellboreGeometry wbGeom = witsmlWellbore.getWellboreGeometry(wbGeomIdx);
					System.out.println("witsml wellbore geom: " + wbGeom.getTitle() + " (" + wbGeom.getUuid() + ")");
					if (wbGeom.hasDepthWaterMean()) { System.out.println("DepthWaterMean: " + wbGeom.getDepthWaterMeanValue() + " " + wbGeom.getDepthWaterMeanUom()); }
					if (wbGeom.hasGapAir()) { System.out.println("GapAir: " + wbGeom.getGapAirValue() + " " + wbGeom.getGapAirUom()); }
					if (wbGeom.hasMdBase()) { System.out.println("MdBase: " + wbGeom.getMdBaseValue() + " " + wbGeom.getMdBaseUom() + " datum=" + wbGeom.getMdBaseDatum()); }
					for (int sectionIdx = 0; sectionIdx < wbGeom.getSectionCount(); ++sectionIdx) {
						System.out.println("Section " + sectionIdx);
						if (wbGeom.hasWellboreGeometrySectionCurveConductor(sectionIdx)) { System.out.println("CurveConductor: " + wbGeom.getWellboreGeometrySectionCurveConductor(sectionIdx)); }
						if (wbGeom.hasWellboreGeometrySectionDiaDrift(sectionIdx)) { System.out.println("DiaDrift: " + wbGeom.getWellboreGeometrySectionDiaDriftValue(sectionIdx) + " " + wbGeom.getWellboreGeometrySectionDiaDriftUom(sectionIdx)); }
						if (wbGeom.hasWellboreGeometrySectionFactFric(sectionIdx)) { System.out.println("FactFric: " + wbGeom.getWellboreGeometrySectionFactFric(sectionIdx)); }
						if (wbGeom.hasWellboreGeometrySectionGrade(sectionIdx)) { System.out.println("Grade: " + wbGeom.getWellboreGeometrySectionGrade(sectionIdx)); }
						if (wbGeom.hasWellboreGeometrySectionIdSection(sectionIdx)) { System.out.println("IdSection: " + wbGeom.getWellboreGeometrySectionIdSectionValue(sectionIdx) + " " + wbGeom.getWellboreGeometrySectionIdSectionUom(sectionIdx)); }
						if (wbGeom.hasWellboreGeometrySectionOdSection(sectionIdx)) { System.out.println("OdSection: " + wbGeom.getWellboreGeometrySectionOdSectionValue(sectionIdx) + " " + wbGeom.getWellboreGeometrySectionOdSectionUom(sectionIdx)); }
						if (wbGeom.hasWellboreGeometrySectionTypeHoleCasing(sectionIdx)) { System.out.println("TypeHoleCasing: " + wbGeom.getWellboreGeometrySectionTypeHoleCasing(sectionIdx)); }
						if (wbGeom.hasWellboreGeometrySectionMdInterval(sectionIdx)) {
							System.out.println("Base md: " + wbGeom.getWellboreGeometrySectionMdIntervalBase(sectionIdx) + " " + wbGeom.getWellboreGeometrySectionMdIntervalBaseUom(sectionIdx));
							System.out.println("Top md: " + wbGeom.getWellboreGeometrySectionMdIntervalTop(sectionIdx) + " " + wbGeom.getWellboreGeometrySectionMdIntervalTopUom(sectionIdx));
							System.out.println("datum: " + wbGeom.getWellboreGeometrySectionMdIntervaldatum(sectionIdx));
						}
						if (wbGeom.hasWellboreGeometrySectionTvdInterval(sectionIdx)) {
							System.out.println("Base Tvd: " + wbGeom.getWellboreGeometrySectionTvdIntervalBase(sectionIdx) + " " + wbGeom.getWellboreGeometrySectionTvdIntervalBaseUom(sectionIdx));
							System.out.println("Top Tvd: " + wbGeom.getWellboreGeometrySectionTvdIntervalTop(sectionIdx) + " " + wbGeom.getWellboreGeometrySectionTvdIntervalTopUom(sectionIdx));
							System.out.println("datum: " + wbGeom.getWellboreGeometrySectionTvdIntervaldatum(sectionIdx));
						}
					}
				}
			}
		}
		
		System.out.println("WellboreFrameRepresentation");
		for (int trajIndex = 0; trajIndex < repo.getWellboreTrajectoryRepresentationCount(); trajIndex++) {
			WellboreTrajectoryRepresentation wellboreTraj = repo.getWellboreTrajectoryRepresentation(trajIndex);
			System.out.println("wbf count = " + wellboreTraj.getWellboreFrameRepresentationCount());
			for (int wbfIndex = 0; wbfIndex < wellboreTraj.getWellboreFrameRepresentationCount(); wbfIndex++) {
				WellboreFrameRepresentation wbf = wellboreTraj.getWellboreFrameRepresentation(wbfIndex);
				
				System.out.println("WellboreFrameRepresentation title : " + wbf.getTitle());
				System.out.println("WellboreFrameRepresentation uuid : " + wbf.getUuid());
				
				System.out.println("Value Count : " + wbf.getMdValuesCount());
				if (wbf.areMdValuesRegularlySpaced()) {
					System.out.println("Regularly spaced");
					System.out.println("First Value : " + wbf.getMdFirstValue());
					System.out.println("Increment : " + wbf.getMdConstantIncrementValue());
				}
				else {
					System.out.println("Iregularly spaced");
				}
				if (wbf.getMdHdfDatatype() == numericalDatatypeEnum.DOUBLE)
					System.out.println("Hdf datatype is NATIVE DOUBLE");
				else if (wbf.getMdHdfDatatype() == numericalDatatypeEnum.FLOAT)
					System.out.println("Hdf datatype is NATIVE FLOAT");
				else if (wbf.getMdHdfDatatype() == numericalDatatypeEnum.UNKNOWN)
					System.out.println("Hdf datatype is UNKNOWN");
				if (wbf.getXmlTag().equals("SeismicWellboreFrameRepresentation")) {
					SeismicWellboreFrameRepresentation swbf = (SeismicWellboreFrameRepresentation) wbf;
					
					System.out.println("Seismic reference datum : " + swbf.getSeismicReferenceDatum());
					System.out.println("Weathering velocity : " + swbf.getWeatheringVelocity());
					if (swbf.areTimeValuesRegularlySpaced()) {
						System.out.println("Time values regularly spaced");
						System.out.println("First Value : " + swbf.getTimeFirstValue());
						System.out.println("Increment : " + swbf.getTimeConstantIncrementValue());
					}
					else {
						System.out.println("Time values iregularly spaced");
					}
					if (swbf.getTimeHdfDatatype() == numericalDatatypeEnum.DOUBLE)
						System.out.println("Hdf datatype is NATIVE DOUBLE");
					else if (swbf.getTimeHdfDatatype() == numericalDatatypeEnum.FLOAT)
						System.out.println("Hdf datatype is NATIVE FLOAT");
					else if (swbf.getTimeHdfDatatype() == numericalDatatypeEnum.UNKNOWN)
						System.out.println("Hdf datatype is UNKNOWN");
				}
			}
		}
	}
	
	private static void deserializeIjkGrid(DataObjectRepository repo) {
		System.out.println("IJK GRID REP");
		long ijkGridCount = repo.getIjkGridRepresentationCount();
		for (long ijkGridIdx = 0; ijkGridIdx < ijkGridCount; ++ijkGridIdx)
		{
			AbstractIjkGridRepresentation ijkGrid = repo.getIjkGridRepresentation(ijkGridIdx);
			System.out.println("\tIjk Grid : " + ijkGrid.getTitle());
			showAllProperties(ijkGrid);
		}
	}

	public static void main(String[] args) {
		serialize();
		deserialize();
	}
}
