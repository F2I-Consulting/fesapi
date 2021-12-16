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

#include <stdexcept>

#include "StratigraphicUnitInterpretation.h"
#include "HorizonInterpretation.h"
#include "StratigraphicOccurrenceInterpretation.h"
#include "StratigraphicColumn.h"

using namespace std;
using namespace RESQML2_NS;

const char* StratigraphicColumnRankInterpretation::XML_TAG = "StratigraphicColumnRankInterpretation";
		
void StratigraphicColumnRankInterpretation::loadTargetRelationships()
{
	AbstractStratigraphicOrganizationInterpretation::loadTargetRelationships();

	unsigned int count = getStratigraphicUnitInterpretationCount();
	for (unsigned int i = 0; i < count; ++i) {
		convertDorIntoRel<StratigraphicUnitInterpretation>(getStratigraphicUnitInterpretationDor(i));
	}

	count = getHorizonInterpretationCount();
	for (unsigned int i = 0; i < count; ++i) {
		convertDorIntoRel<RESQML2_NS::HorizonInterpretation>(getHorizonInterpretationDor(i));
	}
}

StratigraphicUnitInterpretation* StratigraphicColumnRankInterpretation::getStratigraphicUnitInterpretation(unsigned int index) const
{
	return getRepository()->getDataObjectByUuid<StratigraphicUnitInterpretation>(getStratigraphicUnitInterpretationDor(index).getUuid());
}

std::vector<StratigraphicUnitInterpretation *> StratigraphicColumnRankInterpretation::getStratigraphicUnitInterpretationSet() const
{
	return getRepository()->getTargetObjects<StratigraphicUnitInterpretation>(this);
}

std::vector<StratigraphicOccurrenceInterpretation *> StratigraphicColumnRankInterpretation::getStratigraphicOccurrenceInterpretationSet() const
{
	return getRepository()->getSourceObjects<StratigraphicOccurrenceInterpretation>(this);
}

HorizonInterpretation* StratigraphicColumnRankInterpretation::getHorizonInterpretation(unsigned int index) const
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
