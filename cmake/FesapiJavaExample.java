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

import com.f2i.energisticsStandardsApi.Grid2dRepresentationVector;
import com.f2i.energisticsStandardsApi.LocalDepth3dCrsVector;
import com.f2i.energisticsStandardsApi.SWIGTYPE_p_double;
import com.f2i.energisticsStandardsApi.SWIGTYPE_p_unsigned_int;
import com.f2i.energisticsStandardsApi.TriangulatedSetRepresentationVector;
import com.f2i.energisticsStandardsApi.eml20__LengthUom;
import com.f2i.energisticsStandardsApi.fesapi;
import com.f2i.energisticsStandardsApi.fesapiJNI;
import com.f2i.energisticsStandardsApi.resqml2__IndexableElements;
import com.f2i.energisticsStandardsApi.resqml2__ResqmlPropertyKind;
import com.f2i.energisticsStandardsApi.resqml2__ResqmlUom;
import com.f2i.energisticsStandardsApi.witsml1__ElevCodeEnum;
import com.f2i.energisticsStandardsApi.witsml1__LengthUom;
import com.f2i.energisticsStandardsApi.witsml1__WellVerticalCoordinateUom;
import com.f2i.energisticsStandardsApi.common.AbstractHdfProxy;
import com.f2i.energisticsStandardsApi.common.EpcDocument;
import com.f2i.energisticsStandardsApi.resqml2.PropertyKind;
import com.f2i.energisticsStandardsApi.resqml2_0_1.ContinuousProperty;
import com.f2i.energisticsStandardsApi.resqml2_0_1.FaultInterpretation;
import com.f2i.energisticsStandardsApi.resqml2_0_1.GenericFeatureInterpretation;
import com.f2i.energisticsStandardsApi.resqml2_0_1.Grid2dRepresentation;
import com.f2i.energisticsStandardsApi.resqml2_0_1.Horizon;
import com.f2i.energisticsStandardsApi.resqml2_0_1.HorizonInterpretation;
import com.f2i.energisticsStandardsApi.resqml2_0_1.LocalDepth3dCrs;
import com.f2i.energisticsStandardsApi.resqml2_0_1.PointSetRepresentation;
import com.f2i.energisticsStandardsApi.resqml2_0_1.PolylineRepresentation;
import com.f2i.energisticsStandardsApi.resqml2_0_1.SeismicLatticeFeature;
import com.f2i.energisticsStandardsApi.resqml2_0_1.SeismicLineFeature;
import com.f2i.energisticsStandardsApi.resqml2_0_1.SeismicLineSetFeature;
import com.f2i.energisticsStandardsApi.resqml2_0_1.TectonicBoundaryFeature;
import com.f2i.energisticsStandardsApi.resqml2_0_1.TriangulatedSetRepresentation;
import com.f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem;
import com.f2i.energisticsStandardsApi.witsml1_4_1_1.Well;

public class FesapiJavaExample {
	/**
	 * Loading the FesapiCpp native library
	 */
	static {
		try {
			System.loadLibrary("${CPP_LIBRARY_NAME}.${Fesapi_VERSION}");
		}
		catch (UnsatisfiedLinkError e) {
			System.out.println("UnsatisfiedLinkError : " + e.toString());
	    }
	}
	
	static void serializeWells(EpcDocument pck)
	{
		CoordinateReferenceSystem witsmlCrs = pck.createCoordinateReferenceSystem("", "witsmlCrs", "EPSG", "5715", "", -1, -1, "");
		
		// WELL
		Well witsmlWell = pck.createWell("", "Well1", "00:00");
		witsmlWell.setEastingNorthingLocation(witsml1__LengthUom.witsml1__LengthUom__m, 275, 75, witsmlCrs);
		witsmlWell.pushBackDatum("", "well1 msl datum", witsml1__ElevCodeEnum.witsml1__ElevCodeEnum__KB, "EPSG", "5100", "Mean Sea Level");
		witsmlWell.pushBackDatum("", "well1 datum", witsml1__ElevCodeEnum.witsml1__ElevCodeEnum__KB, 0, witsml1__WellVerticalCoordinateUom.witsml1__WellVerticalCoordinateUom__m, 15);
	}
	
	private static void serializeBoundaries(EpcDocument pck, LocalDepth3dCrs crs, AbstractHdfProxy hdfProxy) {
		// Seismic Lattice
		SeismicLatticeFeature seismicLattice = pck.createSeismicLattice("eb6a5e97-4d86-4809-b136-051f34cfcb51", "Seismic lattice", 2, 2, 150, 152, 4, 2);
		GenericFeatureInterpretation seismicLatticeInterp = pck.createGenericFeatureInterpretation(seismicLattice, "97816427-6ef6-4776-b21c-5b93c8a6310a", "Seismic lattice Interp");
		Grid2dRepresentation seismicLatticeRep = pck.createGrid2dRepresentation(seismicLatticeInterp, crs, "aa5b90f1-2eab-4fa6-8720-69dd4fd51a4d", "Seismic lattice Rep");
		seismicLatticeRep.setGeometryAsArray2dOfLatticePoints3d(4, 2, 0, 0, 0, 1, 0, 2, 0, 1, 3, 250, 200);

		// Seismic Line Set
		SeismicLineSetFeature seismicLineSet = pck.createSeismicLineSet("53c6a0be-c901-4bb6-845b-fba79745da02", "Seismic line Set");

		// Seismic Line
		SeismicLineFeature seismicLine = pck.createSeismicLine("117f9bf6-6bb0-49f2-9cee-46912300bff6", "Seismic line", 1, 0, 5);
		seismicLine.setSeismicLineSet(seismicLineSet);
		GenericFeatureInterpretation seismicLineInterp = pck.createGenericFeatureInterpretation(seismicLine, "", "Seismic line Interp");
		PolylineRepresentation seismicLineRep = pck.createPolylineRepresentation(seismicLineInterp, crs, "", "Seismic line Rep");
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
		Horizon horizon1 = pck.createHorizon("35d7b57e-e5ff-4062-95af-ba2d7c4ce347", "Horizon1");
		horizon1.setAge(300000000);

		// Interpretations
		HorizonInterpretation horizon1Interp1 = pck.createHorizonInterpretation(horizon1, "ac12dc12-4951-459b-b585-90f48aa88a5a", "Horizon1 Interp1");

		// Horizon Representations
		PolylineRepresentation h1i1SinglePolylineRep = pck.createPolylineRepresentation(horizon1Interp1, crs, "", "Horizon1 Interp1 SinglePolylineRep");

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

		Grid2dRepresentation h1i1SingleGrid2dRep = pck.createGrid2dRepresentation(horizon1Interp1, crs, "", "Horizon1 Interp1 Grid2dRep");
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
		TriangulatedSetRepresentation h1i1triRep = pck.createTriangulatedSetRepresentation(horizon1Interp1, crs,
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
		PropertyKind  propType1 = pck.createPropertyKind("f7ad7cf5-f2e7-4daa-8b13-7b3df4edba3b", "propType1", "urn:resqml:f2i.com:testingAPI", resqml2__ResqmlUom.resqml2__ResqmlUom__Euc, resqml2__ResqmlPropertyKind.resqml2__ResqmlPropertyKind__continuous);
		ContinuousProperty contProp1 = pck.createContinuousProperty(h1i1SingleGrid2dRep, "fcaccfc7-10cb-4f73-800e-a381642478cb", "Horizon1 Interp1 Grid2dRep Prop1", 2,
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
	
	private static void serialize()
	{
		EpcDocument pck = new EpcDocument("testingPackageJava.epc", EpcDocument.openingMode.OVERWRITE);
	
	    try {
	    	// WITSML
	    	serializeWells(pck);
	    	
	    	// RESQML
	    	LocalDepth3dCrs crs = pck.createLocalDepth3dCrs(UUID.randomUUID().toString(), "UTF8 Crs title : éàç : олег1", 0.0, 0.0, 0.0, 0.0, eml20__LengthUom.eml20__LengthUom__m, 5215, eml20__LengthUom.eml20__LengthUom__m, "Unknown", false);
	    	AbstractHdfProxy hdfProxy = pck.createHdfProxy("", "Hdf Proxy", pck.getStorageDirectory(), pck.getName() + ".h5");
	    	
	    	serializeBoundaries(pck, crs, hdfProxy);
	    	
	    	pck.serialize();
	    }
	    finally {
	    	pck.close();
	    }
	}

	private static void deserialize()
	{
		EpcDocument pck = new EpcDocument("testingPackageJava.epc");
	
	    try {
	    	String status = pck.deserialize();
	    	if (!status.isEmpty()) {
	    		System.out.println("Status : " + status);
	    	}
	    	
	        LocalDepth3dCrsVector crs_set = pck.getLocalDepth3dCrsSet();
	        System.out.println("CRS title is " + crs_set.get(0).getTitle());

	    	Grid2dRepresentationVector horizonGrid2dSet = pck.getHorizonGrid2dRepSet();
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
        			horizonGrid2d.getSupportingRepresentation().getZValuesInGlobalCrs(zValues);
        			System.out.println("Supporting Representation first zValue is : " + fesapi.DoubleArray_getitem(zValues, 0));
        			System.out.println("Supporting Representation second zValue is : " + fesapi.DoubleArray_getitem(zValues, 1));
        			System.out.println("Supporting Representation third zValue is : " + fesapi.DoubleArray_getitem(zValues, 2));
        			System.out.println("Supporting Representation fourth zValue is : " + fesapi.DoubleArray_getitem(zValues, 3));
        			System.out.println("Supporting Representation fifth zValue is : " + fesapi.DoubleArray_getitem(zValues, 4));
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
	    }
	    finally {
	        pck.close();
	    }
	}
	
	public static void main(String[] args) {
		serialize();
	    deserialize();
	}
}
