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
#include "FaultSingleAndMultiPatchTriangulatedSetRepresentationTest.h"
#include "FaultSinglePatchTriangulatedSetRepresentationTest.h"
#include "FaultMultiPatchTriangulatedSetRepresentationTest.h"
#include "../catch.hpp"

using namespace std;
using namespace COMMON_NS;
using namespace commontest;
using namespace resqml2_0_1test;

FaultSingleAndMultiPatchTriangulatedSetRepresentationTest::FaultSingleAndMultiPatchTriangulatedSetRepresentationTest(const string & epcDocPath)
	: AbstractTest(epcDocPath)
{
}

FaultSingleAndMultiPatchTriangulatedSetRepresentationTest::FaultSingleAndMultiPatchTriangulatedSetRepresentationTest(EpcDocument * epcDocument, bool init)
	: AbstractTest(epcDocument)
{
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void FaultSingleAndMultiPatchTriangulatedSetRepresentationTest::initEpcDoc()
{
	// creating dependencies
	FaultSinglePatchTriangulatedSetRepresentationTest* faultSinglePatchRep = new FaultSinglePatchTriangulatedSetRepresentationTest(this->epcDoc, true);
	FaultMultiPatchTriangulatedSetRepresentationTest* faultMultiPatchRep = new FaultMultiPatchTriangulatedSetRepresentationTest(this->epcDoc, true);

	// cleaning
	delete faultSinglePatchRep;
	delete faultMultiPatchRep;
}

void FaultSingleAndMultiPatchTriangulatedSetRepresentationTest::readEpcDoc()
{
	// reading dependencies
	FaultSinglePatchTriangulatedSetRepresentationTest* faultSinglePatchRep = new FaultSinglePatchTriangulatedSetRepresentationTest(this->epcDoc, false);
	FaultMultiPatchTriangulatedSetRepresentationTest* faultMultiPatchRep = new FaultMultiPatchTriangulatedSetRepresentationTest(this->epcDoc, false);

	// cleaning
	delete faultSinglePatchRep;
	delete faultMultiPatchRep;
}


