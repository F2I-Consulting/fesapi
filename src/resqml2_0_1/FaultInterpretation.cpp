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
#include "FaultInterpretation.h"

#include <limits>
#include <stdexcept>

#include "TectonicBoundaryFeature.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* FaultInterpretation::XML_NS = "resqml20";

FaultInterpretation::FaultInterpretation(RESQML2_NS::BoundaryFeature * fault, const string & guid, const string & title)
{
	if (fault == nullptr) {
		throw invalid_argument("The interpreted fault cannot be null.");
	}
	if (!fault->isPartial() && dynamic_cast<RESQML2_0_1_NS::TectonicBoundaryFeature*>(fault) != nullptr && static_cast<RESQML2_0_1_NS::TectonicBoundaryFeature*>(fault)->isAFracture()) {
		throw invalid_argument("The interpreted fault cannot be a fracture.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREFaultInterpretation(fault->getGsoapContext());
	_resqml20__FaultInterpretation* interp = static_cast<_resqml20__FaultInterpretation*>(gsoapProxy2_0_1);
	interp->Domain = resqml20__Domain::mixed;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	fault->getRepository()->addDataObject(this);
	setInterpretedFeature(fault);
}

FaultInterpretation::FaultInterpretation(RESQML2_NS::BoundaryFeature * fault, const string & guid, const string & title,
	RESQML2_NS::BoundaryFeature * chronoTop, RESQML2_NS::BoundaryFeature * chronoBtm)
{
	if (fault == nullptr) {
		throw invalid_argument("The interpreted fault cannot be null.");
	}
	if (dynamic_cast<RESQML2_0_1_NS::TectonicBoundaryFeature*>(fault) != nullptr && static_cast<RESQML2_0_1_NS::TectonicBoundaryFeature*>(fault)->isAFracture()) {
		throw invalid_argument("The interpreted fault cannot be a fracture.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREFaultInterpretation(fault->getGsoapContext());	
	_resqml20__FaultInterpretation* interp = static_cast<_resqml20__FaultInterpretation*>(gsoapProxy2_0_1);
	interp->Domain = resqml20__Domain::mixed;

	interp->HasOccuredDuring = soap_new_resqml20__TimeInterval(interp->soap);
	interp->HasOccuredDuring->ChronoBottom = chronoBtm->newResqmlReference();
	interp->HasOccuredDuring->ChronoTop = chronoTop->newResqmlReference();

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	fault->getRepository()->addDataObject(this);
	setInterpretedFeature(fault);
}

void FaultInterpretation::pushBackThrowInterpretation(gsoap_resqml2_0_1::resqml20__ThrowKind throwKind)
{
	_resqml20__FaultInterpretation* interp = static_cast<_resqml20__FaultInterpretation*>(gsoapProxy2_0_1);

	resqml20__FaultThrow * throwInterp = soap_new_resqml20__FaultThrow(gsoapProxy2_0_1->soap);
	throwInterp->Throw.push_back(throwKind);

	interp->ThrowInterpretation.push_back(throwInterp);
}
