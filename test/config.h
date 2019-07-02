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

#include "proxies/stdsoap2.h"

namespace commontest {
	// AbstractObject
	static const char* authorityAlias = "Authorithy Alias Test";
	static const char* titleAlias = "Alias Test";

	// GraphicalInformationSet
	static const char* uuidGraphicalInformationSet = "bd361c0b-627d-4b72-a157-a8d6c5845475";
	static const char* titleGraphicalInformationSet = "Graphical Information Set Test";
}

namespace resqml2_0_1test {
	// HdfProxy
	static const char* uuidHdfProxy = "75f5b460-3ccb-4102-a06e-e9c1019769b2";
	static const char* titleHdfProxy = "Hdf Proxy Test";
	
	// LocalTime3dCrs
	static const char* uuidLocalTime3dCrs = "e37f861a-5f2c-4a8a-b62c-4c987cf280e1";
	static const char* titleLocalTime3dCrs = "Local Time 3d Crs Test";
	
	// Fault
	static const char* uuidFault = "8e5874d1-c434-46d1-9d6f-7fef83bf7b70";
	static const char* titleFault = "Fault Test";

	// Horizon
	static const char* uuidHorizon0 = "35ea54a9-63d8-4520-a4be-8eb7afff3a4f";
	static const char* titleHorizon0 = "Horizon 0";
	static const char* uuidHorizon1 = "2012cd8f-9175-4a80-b690-15882d2469cc";
	static const char* titleHorizon1 = "Horizon 1";
	
	// FaultInterpretation
	static const char* uuidFaultInterpretation = "c6a20f6f-4f12-44c1-b3a9-0a1db83eff7e";
	static const char* titleFaultInterpretation = "Fault Interpretation Test";

	// Horizon Interp
	static const char* uuidHorizon0Interp = "4068e875-af33-4a12-87c1-89953cc675cc";
	static const char* titleHorizon0Interp = "Horizon 0 Interp";
	static const char* uuidHorizon1Interp = "681d4b48-9355-41a2-998d-dcdc0cad4903";
	static const char* titleHorizon1Interp = "Horizon 1 Interp";
	
	// Single patch Fault TriangulatedSetRepresentation
	static const char* uuidFaultSinglePatchTriangulatedSetRepresentation = "321d2b25-66fe-4749-8fad-c5cef401586e";
	static const char* titleFaultSinglePatchTriangulatedSetRepresentation = "Fault Single Patch Triangulated Set Representation Test";
	static const ULONG64 nodesCountFaultSinglePatchTriangulatedSetRepresentation = 18;
	static double nodesFaultSinglePatchTriangulatedSetRepresentation[] = {
		150, 0, 200, 
		150, 100, 200,
		150, 200, 200,
		250, 0, 300,
		250, 100, 300,
		250, 200, 300,
		300, 0, 350,
		300, 100, 350,
		300, 200, 350,
		450, 0, 500,
		450, 100, 500,
		450, 200, 500,
		500, 0, 550,
		500, 100, 550,
		500, 200, 550,
		600, 0, 650,
		600, 100, 650,
		600, 200, 650};
	
	// Multi patches Fault TriangulatedSetRepresentation
	static const char* uuidFaultMultiPatchTriangulatedSetRepresentation = "c8520931-6a4e-457a-92e6-da0c1fb74ad0";
	static const char* titleFaultMultiPatchTriangulatedSetRepresentation = "Fault Multi Patch Triangulated Set Representation Test";
	
	// One tetrahedron UnstructuredGridRepresentation
	static const char* uuidOneTetrahedronUnstructuredGridRepresentation = "6f1d493d-3da5-43ab-8f57-a508f9590eb8";
	static const char* titleOneTetrahedronUnstructuredGridRepresentation = "One Tetrahedron Unstructured Grid Representation Test";
	static const ULONG64 nodesCountOneTetrahedronUnstructuredGridRepresentation = 4;
	static double nodesOneTetrahedronUnstructuredGridRepresentation[] = {0,0,300, 700,0,350, 0,150,300, 0,0,500};

	// Partial UstructuredGridRepresentation
	static const char* uuidPartialUnstructuredGridRepresentation = "94da1dd5-a82b-4c88-a86b-2dc930c17125";
	static const char* titlePartialUnstructuredGridRepresentation = "Partial Unstructured Grid Representation Test";
}

namespace resqml2_2test {
	// DiscreteColorMap
	static const char* uuidDiscreteColorMap = "e5e1a185-6437-460b-8f65-7f48e9db2653";
	static const char* titleDiscreteColorMap = "Discrete Color Map Test";

	// ContinuousColorMap
	static const char* uuidContinuousColorMap = "eb20132f-1e99-42c3-bfaf-40e317b5bc8b";
	static const char* titleContinuousColorMap = "Continuous Color Map Test";
}

namespace witsml2_0test {
	// Well
	static const char* uuidWell = "4b4ef814-a891-46f5-bf10-3cc30be396a5";
	static const char* titleWell = "Witsml Well Test";
	// Trajecotry
	static const char* uuidTraj = "b4f02547-9fca-49ef-83a9-c96a802c857e";
	static const char* titleTraj = "Witsml Trajectory Test";
}