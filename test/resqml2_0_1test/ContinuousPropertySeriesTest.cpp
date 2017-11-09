#include "resqml2_0_1test/ContinuousPropertySeriesTest.h"

#include "catch.hpp"
#include "resqml2_0_1test/TimeSeriesTest.h"
#include "resqml2_0_1test/IjkGridExplicitRepresentationTest.h"

#include "resqml2/TimeSeries.h"
#include "resqml2_0_1/ContinuousPropertySeries.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"

using namespace std;
using namespace common;
using namespace resqml2_0_1test;
using namespace resqml2;

const char* ContinuousPropertySeriesTest::defaultUuid = "fcb1ba50-afe4-4d87-bc4c-d737a04de048";
const char* ContinuousPropertySeriesTest::defaultTitle = "Continuous Property Series Test";

ContinuousPropertySeriesTest::ContinuousPropertySeriesTest(const string & epcDocPath)
	: ContinuousPropertyTest(epcDocPath, defaultUuid, defaultTitle, IjkGridExplicitRepresentationTest::defaultUuid, IjkGridExplicitRepresentationTest::defaultTitle) {
}

ContinuousPropertySeriesTest::ContinuousPropertySeriesTest(EpcDocument * epcDoc, bool init)
	: ContinuousPropertyTest(epcDoc, defaultUuid, defaultTitle, IjkGridExplicitRepresentationTest::defaultUuid, IjkGridExplicitRepresentationTest::defaultTitle) {
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void ContinuousPropertySeriesTest::initEpcDocHandler() {
	// creating an IJK grid
	IjkGridExplicitRepresentationTest * ijkGridTest = new IjkGridExplicitRepresentationTest(this->epcDoc, true);
	resqml2_0_1::IjkGridExplicitRepresentation * ijkGrid = static_cast<resqml2_0_1::IjkGridExplicitRepresentation *>(this->epcDoc->getResqmlAbstractObjectByUuid(IjkGridExplicitRepresentationTest::defaultUuid));

	// creating the TimeSeries
	TimeSeriesTest * timeSeriesTest = new TimeSeriesTest(this->epcDoc, true);
	TimeSeries* timeSeries = static_cast<TimeSeries *>(this->epcDoc->getResqmlAbstractObjectByUuid(TimeSeriesTest::defaultUuid));

	// getting the hdf proxy
	AbstractHdfProxy* hdfProxy = this->epcDoc->getHdfProxySet()[0];

	// creating the ContinuousPropertySeries
	resqml2_0_1::ContinuousPropertySeries* continuousPropertySeries = epcDoc->createContinuousPropertySeries(
		ijkGrid, this->uuid, this->title,
		1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__cells,
		gsoap_resqml2_0_1::resqml2__ResqmlUom__m,
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__length,
		timeSeries);
	REQUIRE( continuousPropertySeries != nullptr );
	double valuesTime[6] = {0,1,2,3,3,4};
	continuousPropertySeries->pushBackDoubleHdf5Array1dOfValues(valuesTime, 6, hdfProxy);

	// cleaning
	delete timeSeriesTest;
	delete ijkGridTest;
}

void ContinuousPropertySeriesTest::readEpcDocHandler() {
	// reading dependencies
	IjkGridExplicitRepresentationTest * ijkGridTest = new IjkGridExplicitRepresentationTest(this->epcDoc, false);
	TimeSeriesTest * timeSeriesTest = new TimeSeriesTest(this->epcDoc, false);

	// getting the ContinuousPropertySeries
	resqml2_0_1::ContinuousPropertySeries* continuousPropertySeries = static_cast<resqml2_0_1::ContinuousPropertySeries*>(this->epcDoc->getResqmlAbstractObjectByUuid(uuid));

	// ************************************
	// reading the ContinuousPropertySeries

	// getElementCountPerValue
	REQUIRE( continuousPropertySeries->getElementCountPerValue() == 1 );

	// getAttachmentKind
	REQUIRE( continuousPropertySeries->getAttachmentKind() == gsoap_resqml2_0_1::resqml2__IndexableElements__cells );

	// getUom
	REQUIRE( continuousPropertySeries->getUom() == gsoap_resqml2_0_1::resqml2__ResqmlUom__m );

	// getEnergisticsPropertyKind
	REQUIRE( continuousPropertySeries->getEnergisticsPropertyKind() == gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__length );

	// getTimeSeries
	TimeSeries * timeSeries = static_cast<TimeSeries *>(this->epcDoc->getResqmlAbstractObjectByUuid(TimeSeriesTest::defaultUuid));
	REQUIRE( continuousPropertySeries->getTimeSeries() == timeSeries );

	// getValuesCountOfPatch
	REQUIRE( continuousPropertySeries->getValuesCountOfPatch(0) == 6 );

	double* values = new double[6];
	continuousPropertySeries->getDoubleValuesOfPatch(0, values);
	REQUIRE( values[0] == 0 );
	REQUIRE( values[1] == 1 );
	REQUIRE( values[2] == 2 );
	REQUIRE( values[3] == 3 );
	REQUIRE( values[4] == 3 );
	REQUIRE( values[5] == 4 );
	delete [] values;

	// cleaning
	delete ijkGridTest;
	delete timeSeriesTest;
}