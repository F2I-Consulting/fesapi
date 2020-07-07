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
#include "GeobodyBoundaryInterpretation.h"

#include <stdexcept>

#include "../resqml2/BoundaryFeature.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

GeobodyBoundaryInterpretation::GeobodyBoundaryInterpretation(RESQML2_NS::BoundaryFeature * geobodyBoundary, const string & guid, const string & title)
{
	if (geobodyBoundary == nullptr) {
		throw invalid_argument("The interpreted geobody boundary cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__GeobodyBoundaryInterpretation(geobodyBoundary->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretedFeature(geobodyBoundary);
}
