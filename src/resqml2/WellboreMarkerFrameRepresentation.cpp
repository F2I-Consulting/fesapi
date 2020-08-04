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
#include "WellboreMarkerFrameRepresentation.h"

#include <stdexcept>

#include "WellboreMarker.h"
#include "StratigraphicOccurrenceInterpretation.h"

using namespace std;
using namespace RESQML2_NS;

const char* WellboreMarkerFrameRepresentation::XML_TAG = "WellboreMarkerFrameRepresentation";

StratigraphicOccurrenceInterpretation* WellboreMarkerFrameRepresentation::getStratigraphicOccurrenceInterpretation() const
{
	return getRepository()->getDataObjectByUuid<StratigraphicOccurrenceInterpretation>(getStratigraphicOccurrenceInterpretationDor().getUuid());
}

void WellboreMarkerFrameRepresentation::loadTargetRelationships()
{
	WellboreFrameRepresentation::loadTargetRelationships();

	COMMON_NS::DataObjectReference dor = getStratigraphicOccurrenceInterpretationDor();

	if (!dor.isEmpty()) {
		convertDorIntoRel<StratigraphicOccurrenceInterpretation>(dor);
	}
}

std::vector<WellboreMarker *> WellboreMarkerFrameRepresentation::getWellboreMarkerSet() const
{
	return getRepository()->getSourceObjects<WellboreMarker>(this);
}
