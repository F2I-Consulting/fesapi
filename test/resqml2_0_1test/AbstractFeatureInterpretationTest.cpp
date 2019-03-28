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
#include "AbstractFeatureInterpretationTest.h"
#include "resqml2/AbstractFeatureInterpretation.h"
#include "resqml2/AbstractFeature.h"
#include "../catch.hpp"
#include "AbstractObjectTest.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace RESQML2_NS;

AbstractFeatureInterpretationTest::AbstractFeatureInterpretationTest(const string & epcDocPath, const string & uuid, const string & title, const string & uuidFeature, const string & titleFeature)
	: AbstractResqmlDataObjectTest(epcDocPath, uuid, title), uuidFeature(uuidFeature), titleFeature(titleFeature) {
}

AbstractFeatureInterpretationTest::AbstractFeatureInterpretationTest(COMMON_NS::EpcDocument * epcDoc, const string & uuid, const string & title, const string & uuidFeature, const string & titleFeature)
	: AbstractResqmlDataObjectTest(epcDoc, uuid, title), uuidFeature(uuidFeature), titleFeature(titleFeature) {
}

void AbstractFeatureInterpretationTest::readEpcDoc()
{
	AbstractObjectTest::readEpcDoc();

	// remark: following REQUIRE directives are not redundant with "cascade testing" since they cover the partial reference case.
	AbstractFeatureInterpretation* interpretation = static_cast<AbstractFeatureInterpretation*>(epcDoc->getDataObjectByUuid(this->uuid));
	REQUIRE( interpretation->getInterpretedFeature()->getUuid() == uuidFeature );
	REQUIRE( interpretation->getInterpretedFeature()->getTitle() == titleFeature );
}
