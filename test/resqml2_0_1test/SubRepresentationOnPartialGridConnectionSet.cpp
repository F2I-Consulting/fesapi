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
#include "resqml2_0_1test/SubRepresentationOnPartialGridConnectionSet.h"
#include "../config.h"
#include "../catch.hpp"
#include "resqml2_0_1/GridConnectionSetRepresentation.h"
#include "resqml2_0_1/SubRepresentation.h"
#include "resqml2/AbstractRepresentation.h"

using namespace std;
using namespace common;
using namespace resqml2_0_1test;
using namespace resqml2;

const char* SubRepresentationOnPartialGridConnectionSet::defaultUuid = "4c698ca0-ee35-4c68-9c52-9ddeb52eaa21";
const char* SubRepresentationOnPartialGridConnectionSet::defaultTitle = "SubRepresentation On Partial GridConnectionSet";

SubRepresentationOnPartialGridConnectionSet::SubRepresentationOnPartialGridConnectionSet(const string & epcDocPath)
	: AbstractRepresentationTest(epcDocPath, defaultUuid, defaultTitle) {
}

SubRepresentationOnPartialGridConnectionSet::SubRepresentationOnPartialGridConnectionSet(common::EpcDocument * epcDoc, bool init)
	: AbstractRepresentationTest(epcDoc, defaultUuid, defaultTitle) {
		if (init)
			this->initEpcDoc();
		else
			this->readEpcDoc();
}

void SubRepresentationOnPartialGridConnectionSet::initEpcDocHandler()
{
	// getting the hdf proxy
	AbstractHdfProxy* hdfProxy = this->epcDoc->getHdfProxySet()[0];

	resqml2::GridConnectionSetRepresentation* partialGcsr = this->epcDoc->createPartialGridConnectionSetRepresentation("00a7d22f-4746-409b-87dc-5bdb83660d27", "GCSR");
	REQUIRE(partialGcsr != nullptr);
	resqml2::SubRepresentation* subRep = epcDoc->createSubRepresentation(this->uuid, this->title);
	subRep->pushBackSupportingRepresentation(partialGcsr);

	ULONG64 elements[2] = { 1, 2 };
	subRep->pushBackSubRepresentationPatch(gsoap_resqml2_0_1::resqml2__IndexableElements__cells, 2, elements, hdfProxy);
}

void SubRepresentationOnPartialGridConnectionSet::readEpcDocHandler()
{
	// getting the subrep
	resqml2::SubRepresentation* subRep = epcDoc->getResqmlAbstractObjectByUuid<resqml2::SubRepresentation>(this->uuid);

	REQUIRE(subRep->getSupportingRepresentation(0)->isPartial());
	REQUIRE(subRep->getSupportingRepresentation(0)->getXmlTag().compare("GridConnectionSetRepresentation") == 0);
	REQUIRE(subRep->getSupportingRepresentation(0)->getUuid().compare("00a7d22f-4746-409b-87dc-5bdb83660d27") == 0);
	REQUIRE(subRep->getSupportingRepresentation(0)->getTitle().compare("GCSR") == 0);
}

