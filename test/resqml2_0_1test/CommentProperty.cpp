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
#include "resqml2_0_1test/CommentProperty.h"

#include "catch.hpp"
#include "resqml2_0_1test/WellboreFrameRepresentationTest.h"

#include "resqml2_0_1/CommentProperty.h"
#include "resqml2_0_1/WellboreFrameRepresentation.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace COMMON_NS;
using namespace RESQML2_NS;
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
	RESQML2_0_1_NS::WellboreFrameRepresentation * frame = static_cast<RESQML2_0_1_NS::WellboreFrameRepresentation *>(this->epcDoc->getResqmlAbstractObjectByUuid(WellboreFrameRepresentationTest::defaultUuid));

	// getting the hdf proxy
	AbstractHdfProxy* hdfProxy = this->epcDoc->getHdfProxySet()[0];

	// creating the ContinuousProperty
	RESQML2_0_1_NS::CommentProperty* commentProperty = epcDoc->createCommentProperty(
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
	RESQML2_0_1_NS::CommentProperty* commentProperty = this->epcDoc->getResqmlAbstractObjectByUuid<RESQML2_0_1_NS::CommentProperty>(uuid);

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

