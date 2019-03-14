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
#include "resqml2_0_1test/AbstractRepresentationTest.h"

#include "catch.hpp"

#include "common/EpcDocument.h"
#include "resqml2/AbstractRepresentation.h"

#include "proxies/stdsoap2.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace RESQML2_NS;

AbstractRepresentationTest::AbstractRepresentationTest(const std::string & epcDocPath, const string & uuid, const string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs) 
	: AbstractResqmlDataObjectTest(epcDocPath, uuid, title), xyzPointCountOfAllPatches(xyzPointCountOfAllPatches), xyzPointsOfAllPatchesInGlobalCrs(xyzPointsOfAllPatchesInGlobalCrs) {
}

AbstractRepresentationTest::AbstractRepresentationTest(COMMON_NS::EpcDocument* epcDoc, const string & uuid, const string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs)
	: AbstractResqmlDataObjectTest(epcDoc, uuid, title), xyzPointCountOfAllPatches(xyzPointCountOfAllPatches), xyzPointsOfAllPatchesInGlobalCrs(xyzPointsOfAllPatchesInGlobalCrs) {
}

void AbstractRepresentationTest::readEpcDoc() {
	AbstractObjectTest::readEpcDoc();

	// ****************
	// geometry testing

	if (this->xyzPointsOfAllPatchesInGlobalCrs != nullptr) {
		// checking number of points in the geometry
		AbstractRepresentation* representation = static_cast<AbstractRepresentation*>(this->epcDoc->getDataObjectByUuid(this->uuid));
		REQUIRE( representation->getXyzPointCountOfAllPatches() == this->xyzPointCountOfAllPatches );

		// checking values
		ULONG64 pointCount = 3*this->xyzPointCountOfAllPatches;
		double * xyzPoint = new double[pointCount];
		representation->getXyzPointsOfAllPatchesInGlobalCrs(xyzPoint);
		for (ULONG64 i=0; i<pointCount; ++i) {
			REQUIRE( this->xyzPointsOfAllPatchesInGlobalCrs[i] == xyzPoint[i] ); 
		}
		delete[] xyzPoint;
	}
}
