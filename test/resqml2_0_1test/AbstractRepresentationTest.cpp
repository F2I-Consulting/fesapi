#include "resqml2_0_1test/AbstractRepresentationTest.h"

#include "catch.hpp"

#include "EpcDocument.h"
#include "resqml2/AbstractRepresentation.h"

#include "proxies/stdsoap2.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace resqml2;

AbstractRepresentationTest::AbstractRepresentationTest(const std::string & epcDocPath, const string & uuid, const string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs) 
	: AbstractResqmlDataObjectTest(epcDocPath, uuid, title), xyzPointCountOfAllPatches(xyzPointCountOfAllPatches), xyzPointsOfAllPatchesInGlobalCrs(xyzPointsOfAllPatchesInGlobalCrs) {
}

AbstractRepresentationTest::AbstractRepresentationTest(common::EpcDocument* epcDoc, const string & uuid, const string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs)
	: AbstractResqmlDataObjectTest(epcDoc, uuid, title), xyzPointCountOfAllPatches(xyzPointCountOfAllPatches), xyzPointsOfAllPatchesInGlobalCrs(xyzPointsOfAllPatchesInGlobalCrs) {
}

void AbstractRepresentationTest::readEpcDoc() {
	AbstractObjectTest::readEpcDoc();

	// ****************
	// geometry testing

	if (this->xyzPointsOfAllPatchesInGlobalCrs != nullptr) {
		// checking number of points in the geometry
		AbstractRepresentation* representation = static_cast<AbstractRepresentation*>(this->epcDoc->getResqmlAbstractObjectByUuid(this->uuid));
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
