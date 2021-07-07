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
#include "GeologicUnitOccurrenceInterpretation.h"

#include <stdexcept>

#include "../resqml2/Model.h"
#include "../resqml2/StratigraphicColumnRankInterpretation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* GeologicUnitOccurrenceInterpretation::XML_NS = "resqml22";
const char* GeologicUnitOccurrenceInterpretation::XML_TAG = "GeologicUnitOccurrenceInterpretation";

GeologicUnitOccurrenceInterpretation::GeologicUnitOccurrenceInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__OrderingCriteria orderingCriteria)
{
	if (orgFeat == nullptr) {
		throw invalid_argument("The interpreted organization feature cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__GeologicUnitOccurrenceInterpretation(orgFeat->getGsoapContext());
	static_cast<_resqml22__GeologicUnitOccurrenceInterpretation*>(gsoapProxy2_3)->AscendingOrderingCriteria = static_cast<resqml22__OrderingCriteria>(orderingCriteria);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	orgFeat->getRepository()->addDataObject(this);
	setInterpretedFeature(orgFeat);
}

void GeologicUnitOccurrenceInterpretation::setStratigraphicColumnRankInterpretation(RESQML2_NS::StratigraphicColumnRankInterpretation * stratiColumnRankInterp)
{
	getRepository()->addRelationship(this, stratiColumnRankInterp);

	_resqml22__GeologicUnitOccurrenceInterpretation* interp = static_cast<_resqml22__GeologicUnitOccurrenceInterpretation*>(gsoapProxy2_3);
	interp->IsOccurrenceOf = stratiColumnRankInterp->newEml23Reference();
}

COMMON_NS::DataObjectReference GeologicUnitOccurrenceInterpretation::getStratigraphicColumnRankInterpretationDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<_resqml22__GeologicUnitOccurrenceInterpretation*>(gsoapProxy2_3)->IsOccurrenceOf);
}
