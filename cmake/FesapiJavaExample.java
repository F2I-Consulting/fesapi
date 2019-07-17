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
package com.f2i.energisticsStandardsApi.example;

import java.util.UUID;
import com.f2i.energisticsStandardsApi.ConstGrid2dRepresentationVector;
import com.f2i.energisticsStandardsApi.LocalDepth3dCrsVector;
import com.f2i.energisticsStandardsApi.SWIGTYPE_p_double;
import com.f2i.energisticsStandardsApi.SWIGTYPE_p_unsigned_int;
import com.f2i.energisticsStandardsApi.SWIGTYPE_p_unsigned_short;
import com.f2i.energisticsStandardsApi.StringVector;
import com.f2i.energisticsStandardsApi.eml20__LengthUom;
import com.f2i.energisticsStandardsApi.eml21__LengthUom;
import com.f2i.energisticsStandardsApi.eml21__WellboreDatumReference;
import com.f2i.energisticsStandardsApi.fesapi;
import com.f2i.energisticsStandardsApi.resqml2__IndexableElements;
import com.f2i.energisticsStandardsApi.resqml2__InterpolationDomain;
import com.f2i.energisticsStandardsApi.resqml2__InterpolationMethod;
import com.f2i.energisticsStandardsApi.resqml2__ResqmlPropertyKind;
import com.f2i.energisticsStandardsApi.resqml2__ResqmlUom;
import com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractHdfProxy;
import com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.AbstractObject;
import com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.DataObjectRepository;
import com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.EpcDocument;
import com.f2i.energisticsStandardsApi.${FESAPI_COMMON_NS}.GraphicalInformationSet;
import com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.ContinuousColorMap;
import com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_2_NS}.DiscreteColorMap;
import com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_NS}.PropertyKind;
import com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.ContinuousProperty;
import com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.DiscreteProperty;
import com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.EarthModelInterpretation;
import com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.GenericFeatureInterpretation;
import com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.Grid2dRepresentation;
import com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.Horizon;
import com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.HorizonInterpretation;
import com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.IjkGridExplicitRepresentation;
import com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.LocalDepth3dCrs;
import com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.OrganizationFeature;
import com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.PolylineRepresentation;
import com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SeismicLatticeFeature;
import com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SeismicLineFeature;
import com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.SeismicLineSetFeature;
import com.f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS}.TriangulatedSetRepresentation;
import com.f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS}.Well;

public class FesapiJavaExample {
	private static Horizon horizon1;

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

	static void serializeWells(DataObjectRepository repo)
	{
		// WELL
		Well witsmlWell = repo.createWell("704a287c-5c24-4af3-a97b-bc6670f4e14f", "Well1");
		witsmlWell.setNameLegal("Legal Name");
		witsmlWell.setWaterDepth(0.0, eml21__LengthUom.eml21__LengthUom__0_x002e1_x0020ft);
		witsmlWell.setTimeZone(true, 0);
		witsmlWell.pushBackLocation("8cd3c8b2-face-4426-8aea-ae34870bd969", 275, 75, 0);
		witsmlWell.pushBackDatum("aa92fa8b-d6cc-459e-b456-27fec0c08b24", "well1 msl datum", eml21__WellboreDatumReference.eml21__WellboreDatumReference__kelly_x0020bushing, "Mean Sea Level", eml21__LengthUom.eml21__LengthUom__m, 0, 5100);
		witsmlWell.pushBackDatum("d3ac5401-d3e7-4474-b846-070673b210ae", "KB", eml21__WellboreDatumReference.eml21__WellboreDatumReference__kelly_x0020bushing, "Mean Sea Level", eml21__LengthUom.eml21__LengthUom__m, 15, 5100);
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
		SeismicLineFeature seismicLine = repo.createSeismicLine("117f9bf6-6bb0-49f2-9cee-46912300bff6", "Seismic line", 1, 0, 5);
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
		horizon1.setAge(300000000);

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
		PropertyKind  propType1 = repo.createPropertyKind("f7ad7cf5-f2e7-4daa-8b13-7b3df4edba3b", "propType1", "urn:resqml:f2i.com:testingAPI", resqml2__ResqmlUom.resqml2__ResqmlUom__Euc, resqml2__ResqmlPropertyKind.resqml2__ResqmlPropertyKind__continuous);
		ContinuousProperty contProp1 = repo.createContinuousProperty(h1i1SingleGrid2dRep, "fcaccfc7-10cb-4f73-800e-a381642478cb", "Horizon1 Interp1 Grid2dRep Prop1", 2,
				resqml2__IndexableElements.resqml2__IndexableElements__nodes, resqml2__ResqmlUom.resqml2__ResqmlUom__m, propType1);
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

		PropertyKind propType1 = repo.createPropertyKind("0a5f4400-fa3e-11e5-80a4-0002a5d5c51b", "cellIndex", "urn:resqml:f2i-consulting.com", resqml2__ResqmlUom.resqml2__ResqmlUom__Euc, resqml2__ResqmlPropertyKind.resqml2__ResqmlPropertyKind__discrete);
		OrganizationFeature earthModel = repo.createEarthModel("f2060ce0-fa3d-11e5-8620-0002a5d5c51b", "Grid");
		EarthModelInterpretation earthModelInterp = repo.createEarthModelInterpretation(earthModel, "f5cd7520-fa3d-11e5-b65b-0002a5d5c51b", "Grid interp");
		IjkGridExplicitRepresentation ijkgrid = repo.createIjkGridExplicitRepresentation(earthModelInterp, "df2103a0-fa3d-11e5-b8d4-0002a5d5c51b", "Two faulted sugar cubes (explicit geometry)", 2, 1, 1);
		DiscreteProperty discreteProp1 = repo.createDiscreteProperty(ijkgrid, "ee0857fe-23ad-4dd9-8300-21fa2e9fb572", "Two faulted sugar cubes cellIndex", 1,
				resqml2__IndexableElements.resqml2__IndexableElements__cells, propType1);

		SWIGTYPE_p_unsigned_short prop1Values = fesapi.new_UShortArray(2);
		try {
			fesapi.UShortArray_setitem(prop1Values, 0, 0);
			fesapi.UShortArray_setitem(prop1Values, 1, 1);
			discreteProp1.pushBackUShortHdf5Array3dOfValues(prop1Values, 2, 1, 1, hdfProxy, 1111);
		}
		finally {
			fesapi.delete_UShortArray(prop1Values);
		}

		graphicalInformationSet.setDiscreteColorMap(discreteProp1, discrColMap);


		// ********************
		// Continuous color map
		// ********************

		Horizon contColMapHrz = repo.createHorizon("b9ec6ec9-2766-4af7-889e-5565b5fa5022", "Horizon for continuous color map");
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
				resqml2__IndexableElements.resqml2__IndexableElements__nodes, "continuousColorMapIndex", resqml2__ResqmlPropertyKind.resqml2__ResqmlPropertyKind__continuous);
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

		ContinuousColorMap contColMap = repo.createContinuousColorMap("a207faa2-963e-48d6-b3ad-53f6c1fc4dd4", "Continuous color map", resqml2__InterpolationDomain.resqml2__InterpolationDomain__rgb, resqml2__InterpolationMethod.resqml2__InterpolationMethod__linear);
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

	private static void serialize()
	{
		EpcDocument pck = new EpcDocument("testingPackageJava.epc");
		DataObjectRepository repo = new DataObjectRepository();
		
		try {
			// WITSML
			serializeWells(repo);

			// RESQML
			LocalDepth3dCrs crs = repo.createLocalDepth3dCrs(UUID.randomUUID().toString(), "UTF8 Crs title", 0.0, 0.0, 0.0, 0.0, eml20__LengthUom.eml20__LengthUom__m, 5215, eml20__LengthUom.eml20__LengthUom__m, "Unknown", false);
			repo.setDefaultCrs(crs);
			AbstractHdfProxy hdfProxy = repo.createHdfProxy("", "Hdf Proxy", pck.getStorageDirectory(), pck.getName() + ".h5", DataObjectRepository.openingMode.OVERWRITE);
			repo.setDefaultHdfProxy(hdfProxy);

			serializeBoundaries(repo, hdfProxy);

			serializeGraphicalInformationSet(repo, hdfProxy);

			pck.serializeFrom(repo);
		}
		finally {
			pck.close();
			repo.clear();
		}
	}

	private static void deserialize()
	{
		EpcDocument pck = new EpcDocument("testingPackageJava.epc");
		DataObjectRepository repo = new DataObjectRepository();

		try {
			String status = pck.deserializeInto(repo);
			if (!status.isEmpty()) {
				System.out.println("Status : " + status);
			}

			LocalDepth3dCrsVector crs_set = repo.getLocalDepth3dCrsSet();
			System.out.println("CRS title is " + crs_set.get(0).getTitle());

			ConstGrid2dRepresentationVector horizonGrid2dSet = repo.getHorizonGrid2dRepSet();
			System.out.println("HORIZONS GRID 2D REP");
			for (int i = 0; i < horizonGrid2dSet.size(); i++) {
				Grid2dRepresentation horizonGrid2d = horizonGrid2dSet.get(i);

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

			System.out.println("WITSML WELL");
			Well witsmlWell = (Well) repo.getDataObjectByUuid("704a287c-5c24-4af3-a97b-bc6670f4e14f");
			System.out.println("Well title is : " + witsmlWell.getTitle());
			System.out.println("Location projected X : " + witsmlWell.getLocationProjectedX(0));
			System.out.println("Location projected Y : " + witsmlWell.getLocationProjectedY(0));
			System.out.println("\tnameLegal : " + witsmlWell.getNameLegal());
			System.out.println("\twaterDepth : " + witsmlWell.getWaterDepthValue() + " (" + witsmlWell.getWaterDepthUom() + ")");
			if (witsmlWell.hasTimeZone())
			{
				System.out.println("\ttimeZone : " + witsmlWell.getTimeZoneHours() + " hours");
			}

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
		}
		finally {
			pck.close();
			repo.clear();
		}
	}

	public static void main(String[] args) {
		serialize();
		deserialize();
	}
}
