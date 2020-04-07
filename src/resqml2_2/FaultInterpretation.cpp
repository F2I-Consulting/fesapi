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

#include "../resqml2/BoundaryFeature.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

FaultInterpretation::FaultInterpretation(RESQML2_NS::BoundaryFeature * fault, const string & guid, const string & title)
{
	if (fault == nullptr) {
		throw invalid_argument("The interpreted fault cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__FaultInterpretation(fault->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretedFeature(fault);
}

FaultInterpretation::FaultInterpretation(RESQML2_NS::BoundaryFeature * fault, const string & guid, const string & title,
	RESQML2_NS::BoundaryFeature * chronoTop, RESQML2_NS::BoundaryFeature * chronoBtm)
{
	if (fault == nullptr) {
		throw invalid_argument("The interpreted fault cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__FaultInterpretation(fault->getGsoapContext());
	_resqml22__FaultInterpretation* interp = static_cast<_resqml22__FaultInterpretation*>(gsoapProxy2_3);

	auto interval = soap_new_resqml22__GeneticBoundaryBasedTimeInterval(interp->soap);
	interval->ChronoBottom = chronoBtm->newEml23Reference();
	interval->ChronoTop = chronoTop->newEml23Reference();
	interp->HasOccurredDuring = interval;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretedFeature(fault);
}

void FaultInterpretation::pushBackThrowInterpretation(gsoap_resqml2_0_1::resqml20__ThrowKind throwKind)
{
	_resqml22__FaultInterpretation* interp = static_cast<_resqml22__FaultInterpretation*>(gsoapProxy2_3);

	resqml22__FaultThrow * throwInterp = soap_new_resqml22__FaultThrow(gsoapProxy2_3->soap);
	throwInterp->Throw.push_back(gsoap_resqml2_0_1::soap_resqml20__ThrowKind2s(gsoapProxy2_3->soap, throwKind));

	interp->ThrowInterpretation.push_back(throwInterp);
}
