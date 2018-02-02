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
#include "FaultInterpretationTest.h"
#include "FaultTest.h"
#include "resqml2_0_1/TectonicBoundaryFeature.h"
#include "resqml2_0_1/FaultInterpretation.h"
#include "../catch.hpp"
#include "../config.h"
#include "AbstractObjectTest.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

FaultInterpretationTest::FaultInterpretationTest(const string & epcDocPath)
	: BoundaryFeatureInterpretationTest(epcDocPath, uuidFaultInterpretation, titleFaultInterpretation, uuidFault, titleFault)
{
}

FaultInterpretationTest::FaultInterpretationTest(EpcDocument * epcDoc, bool init)
	: BoundaryFeatureInterpretationTest(epcDoc, uuidFaultInterpretation, titleFaultInterpretation, uuidFault, titleFault)
{
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void FaultInterpretationTest::initEpcDocHandler()
{
	// creating dependencies
	FaultTest* faultTest = new FaultTest(this->epcDoc, true);

	TectonicBoundaryFeature* fault = static_cast<TectonicBoundaryFeature*>(this->epcDoc->getResqmlAbstractObjectByUuid(uuidFault));
	FaultInterpretation* FaultInterp = this->epcDoc->createFaultInterpretation(fault, this->uuid, this->title);
	REQUIRE( FaultInterp != nullptr );

	// cleaning
	delete faultTest;
}

void FaultInterpretationTest::readEpcDocHandler()
{
	// reading dependencies
	FaultTest* faultTest = new FaultTest(this->epcDoc, false);

	// cleaning
	delete faultTest;
}

