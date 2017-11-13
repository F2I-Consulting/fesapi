#include "resqml2_0_1test/CommentProperty.h"

#include "catch.hpp"
#include "resqml2_0_1test/WellboreFrameRepresentationTest.h"

#include "resqml2_0_1/CommentProperty.h"
#include "resqml2_0_1/WellboreFrameRepresentation.h"
#include "resqml2/AbstractHdfProxy.h"

using namespace std;
using namespace common;
using namespace resqml2;
using namespace resqml2_0_1test;

const char* CommentProperty::defaultUuid = "3e01e290-7df3-450e-ad93-2f88e79fe2fe";
const char* CommentProperty::defaultTitle = "Comment Property on well frame Test";

CommentProperty::CommentProperty(const string & epcDocPath)
	: AbstractValuesPropertyTest(epcDocPath, defaultUuid, defaultTitle, WellboreFrameRepresentationTest::defaultUuid, WellboreFrameRepresentationTest::defaultTitle) {
}

CommentProperty::CommentProperty(EpcDocument * epcDoc, bool init)
	: AbstractValuesPropertyTest(epcDoc, defaultUuid, defaultTitle, WellboreFrameRepresentationTest::defaultUuid, WellboreFrameRepresentationTest::defaultTitle) {
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void CommentProperty::initEpcDocHandler() {
	// creating an IJK grid
	WellboreFrameRepresentationTest * frameTest = new WellboreFrameRepresentationTest(this->epcDoc, true);
	resqml2_0_1::WellboreFrameRepresentation * frame = static_cast<resqml2_0_1::WellboreFrameRepresentation *>(this->epcDoc->getResqmlAbstractObjectByUuid(WellboreFrameRepresentationTest::defaultUuid));

	// getting the hdf proxy
	AbstractHdfProxy* hdfProxy = this->epcDoc->getHdfProxySet()[0];

	// creating the ContinuousProperty
	resqml2_0_1::CommentProperty* commentProperty = epcDoc->createCommentProperty(
		frame, this->uuid, this->title,
		1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__nodes,
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__length); // TODO : modify for a comment prop kind!!
	REQUIRE(commentProperty != nullptr);
	std::vector<string> values;
	values.push_back("test0");
	values.push_back("test1Iregular");
	values.push_back("test2");
	values.push_back("");
	values.push_back("test4End");
	commentProperty->pushBackStringHdf5ArrayOfValues(values, hdfProxy);

	// cleaning
	delete frameTest;
}

void CommentProperty::readEpcDocHandler() {
	// reading dependencies
	WellboreFrameRepresentationTest * frameTest = new WellboreFrameRepresentationTest(this->epcDoc, false);

	// getting the ContinuousPropertySeries
	resqml2_0_1::CommentProperty* commentProperty = this->epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::CommentProperty>(uuid);

	// ************************************
	// reading the ContinuousProperty

	// getElementCountPerValue
	REQUIRE(commentProperty->getElementCountPerValue() == 1);

	// getAttachmentKind
	REQUIRE(commentProperty->getAttachmentKind() == gsoap_resqml2_0_1::resqml2__IndexableElements__nodes);

	std::vector<string> values = commentProperty->getStringValuesOfPatch(0);
	REQUIRE(values.size() == 5);
	REQUIRE(values[0] == "test0");
	REQUIRE(values[1] == "test1Iregular");
	REQUIRE(values[2] == "test2");
	REQUIRE(values[3].empty());
	REQUIRE(values[4] == "test4End");

	// cleaning
	delete frameTest;
}
