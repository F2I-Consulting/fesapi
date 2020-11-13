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
#include "resqml2_test/CommentProperty.h"

#include "catch.hpp"
#include "resqml2_test/WellboreFrameRepresentationTest.h"

#include "resqml2/CommentProperty.h"
#include "resqml2_0_1/WellboreFrameRepresentation.h"
#include "eml2/AbstractHdfProxy.h"

using namespace std;
using namespace COMMON_NS;
using namespace EML2_NS;
using namespace resqml2_test;

const char* CommentProperty::defaultUuid = "3e01e290-7df3-450e-ad93-2f88e79fe2fe";
const char* CommentProperty::defaultTitle = "Comment Property on well frame Test";

CommentProperty::CommentProperty(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
}

void CommentProperty::initRepo() {
	// creating an IJK grid
	RESQML2_NS::WellboreFrameRepresentation * frame = repo->createPartial<RESQML2_0_1_NS::WellboreFrameRepresentation>(WellboreFrameRepresentationTest::defaultUuid, "");

	// getting the hdf proxy
	EML2_NS::AbstractHdfProxy* hdfProxy = repo->getHdfProxySet()[0];

	// creating the ContinuousProperty
	auto propertyKind = repo->createPropertyKind("", "comment", gsoap_eml2_1::eml21__QuantityClassKind__not_x0020a_x0020measure);
	RESQML2_NS::CommentProperty* commentProperty = repo->createCommentProperty(
		frame, defaultUuid, defaultTitle,
		1,
		gsoap_eml2_3::resqml22__IndexableElement__nodes,
		propertyKind);
	REQUIRE(commentProperty != nullptr);
	std::vector<string> values;
	values.push_back("test0");
	values.push_back("test1Iregular");
	values.push_back("test2");
	values.push_back("");
	values.push_back("test4End");
	commentProperty->pushBackStringHdf5ArrayOfValues(values, hdfProxy);
}

void CommentProperty::readRepo() {
	// getting the ContinuousPropertySeries
	RESQML2_NS::CommentProperty* commentProperty = repo->getDataObjectByUuid<RESQML2_NS::CommentProperty>(defaultUuid);

	// ************************************
	// reading the ContinuousProperty

	// getElementCountPerValue
	REQUIRE(commentProperty->getElementCountPerValue() == 1);

	// getAttachmentKind
	REQUIRE(commentProperty->getAttachmentKind() == gsoap_eml2_3::resqml22__IndexableElement__nodes);

	std::vector<string> values = commentProperty->getStringValuesOfPatch(0);
	REQUIRE(values.size() == 5);
	REQUIRE(values[0] == "test0");
	REQUIRE(values[1] == "test1Iregular");
	REQUIRE(values[2] == "test2");
	REQUIRE(values[3].empty());
	REQUIRE(values[4] == "test4End");
}
