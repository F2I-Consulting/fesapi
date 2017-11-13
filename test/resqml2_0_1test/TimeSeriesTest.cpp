#include "TimeSeriesTest.h"
#include "../config.h"
#include "../catch.hpp"
#include "resqml2/TimeSeries.h"

using namespace std;
using namespace common;
using namespace resqml2_0_1test;
using namespace resqml2;

const char* TimeSeriesTest::defaultUuid = "0b8fc144-8e71-4f2a-a062-60c2d17fdc12";
const char* TimeSeriesTest::inputTile = "Time Series";

TimeSeriesTest::TimeSeriesTest(const string & epcDocPath)
	: AbstractResqmlDataObjectTest(epcDocPath, defaultUuid, inputTile) {
}

TimeSeriesTest::TimeSeriesTest(EpcDocument * epcDoc, bool init)
	: AbstractResqmlDataObjectTest(epcDoc, defaultUuid, inputTile) {
		if (init)
			this->initEpcDoc();
		else
			this->readEpcDoc();
}

void TimeSeriesTest::initEpcDocHandler() {
	TimeSeries* timeSeries = this->epcDoc->createTimeSeries(this->uuid, this->title);
	REQUIRE( timeSeries != nullptr );

	timeSeries->pushBackTimestamp(1378217895);
	timeSeries->pushBackTimestamp(1409753895);
	timeSeries->pushBackTimestamp(1441289895);
}

void TimeSeriesTest::readEpcDocHandler() {
	vector<TimeSeries*> timeSeriesSet = this->epcDoc->getTimeSeriesSet();
	REQUIRE(timeSeriesSet.size() == 1);

	// getting the TimeSeries
	TimeSeries* timeSeries = timeSeriesSet[0];

	// **********************
	// reading the TimeSeries

	// getTimestampIndex
	REQUIRE( timeSeries->getTimestampIndex(1378217895) == 0 );
	REQUIRE( timeSeries->getTimestampIndex(1409753895) == 1 );
	REQUIRE( timeSeries->getTimestampIndex(1441289895) == 2 );

	// getTimestampCount
	REQUIRE( timeSeries->getTimestampCount() == 3);

	// getTimestamp
	REQUIRE( timeSeries->getTimestamp(0) == 1378217895 );
	REQUIRE( timeSeries->getTimestamp(1) == 1409753895 );
	REQUIRE( timeSeries->getTimestamp(2) == 1441289895 );
}