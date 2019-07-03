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
#include "resqml2_0_1/HorizonInterpretation.h"

#include <algorithm>
#include <stdexcept>

#include "resqml2_0_1/Horizon.h"
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* HorizonInterpretation::XML_TAG = "HorizonInterpretation";

HorizonInterpretation::HorizonInterpretation(Horizon * horizon, const string & guid, const string & title)
{
	if (horizon == nullptr) {
		throw invalid_argument("The interpreted horizon cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREHorizonInterpretation(horizon->getGsoapContext(), 1);

	static_cast<_resqml2__HorizonInterpretation*>(gsoapProxy2_0_1)->Domain = resqml2__Domain__mixed;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretedFeature(horizon);
}
