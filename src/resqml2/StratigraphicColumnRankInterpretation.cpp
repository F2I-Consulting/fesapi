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
#include "StratigraphicColumnRankInterpretation.h"

#include "StratigraphicUnitInterpretation.h"
#include "HorizonInterpretation.h"
#include "GeologicUnitOccurrenceInterpretation.h"
#include "StratigraphicColumn.h"

using namespace std;
using namespace RESQML2_NS;
		
void StratigraphicColumnRankInterpretation::loadTargetRelationships()
{
	AbstractStratigraphicOrganizationInterpretation::loadTargetRelationships();

	uint64_t count = getStratigraphicUnitInterpretationCount();
	for (uint64_t i = 0; i < count; ++i) {
		convertDorIntoRel<StratigraphicUnitInterpretation>(getStratigraphicUnitInterpretationDor(i));
	}

	count = getHorizonInterpretationCount();
	for (uint64_t i = 0; i < count; ++i) {
		convertDorIntoRel<RESQML2_NS::HorizonInterpretation>(getHorizonInterpretationDor(i));
	}
}

std::vector<StratigraphicUnitInterpretation *> StratigraphicColumnRankInterpretation::getStratigraphicUnitInterpretationSet() const
{
	return getRepository()->getTargetObjects<StratigraphicUnitInterpretation>(this);
}

std::vector<GeologicUnitOccurrenceInterpretation *> StratigraphicColumnRankInterpretation::getGeologicUnitOccurrenceInterpretationSet() const
{
	return getRepository()->getSourceObjects<GeologicUnitOccurrenceInterpretation>(this);
}

HorizonInterpretation* StratigraphicColumnRankInterpretation::getHorizonInterpretation(uint64_t index) const
{
	return getRepository()->getDataObjectByUuid<HorizonInterpretation>(getHorizonInterpretationDor(index).getUuid());
}

std::vector<HorizonInterpretation *> StratigraphicColumnRankInterpretation::getHorizonInterpretationSet() const
{
	return getRepository()->getTargetObjects<HorizonInterpretation>(this);
}

std::vector<StratigraphicColumn *> StratigraphicColumnRankInterpretation::getStratigraphicColumnSet() const
{
	return getRepository()->getSourceObjects<StratigraphicColumn>(this);
}
