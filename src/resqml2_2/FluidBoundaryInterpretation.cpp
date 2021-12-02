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
#include "FluidBoundaryInterpretation.h"

#include "../resqml2/BoundaryFeature.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* FluidBoundaryInterpretation::XML_NS = "resqml22";

FluidBoundaryInterpretation::FluidBoundaryInterpretation(RESQML2_NS::BoundaryFeature * feature, const string & guid, const string & title, gsoap_eml2_3::resqml22__FluidContact fluidContact)
{
	if (feature == nullptr) {
		throw invalid_argument("The interpreted feature cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__FluidBoundaryInterpretation(feature->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	static_cast<resqml22__FluidBoundaryInterpretation*>(gsoapProxy2_3)->FluidContact = fluidContact;

	feature->getRepository()->addDataObject(this);
	setInterpretedFeature(feature);
}
