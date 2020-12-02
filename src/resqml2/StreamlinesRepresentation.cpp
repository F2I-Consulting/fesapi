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
#include "StreamlinesRepresentation.h"

#include "AbstractGridRepresentation.h"
#include "WellboreTrajectoryRepresentation.h"

using namespace RESQML2_NS;

const char* StreamlinesRepresentation::XML_TAG = "StreamlinesRepresentation";

RESQML2_NS::WellboreTrajectoryRepresentation* StreamlinesRepresentation::getWellboreTrajectory(uint16_t index) const
{
	return repository->getDataObjectByUuid<RESQML2_NS::WellboreTrajectoryRepresentation>(getWellboreTrajectoryDor(index).getUuid());
}

RESQML2_NS::AbstractGridRepresentation* StreamlinesRepresentation::getGridRepresentation(uint16_t index) const
{
	return repository->getDataObjectByUuid<RESQML2_NS::AbstractGridRepresentation>(getGridRepresentationDor(index).getUuid());
}

void StreamlinesRepresentation::loadTargetRelationships()
{
	AbstractRepresentation::loadTargetRelationships();

	unsigned int relCount = getWellboreTrajectoryCount();
	for (unsigned int i = 0; i < relCount; ++i) {
		COMMON_NS::DataObjectReference dor = getWellboreTrajectoryDor(i);
		convertDorIntoRel(dor);
	}

	relCount = getGridRepresentationCount();
	for (unsigned int i = 0; i < relCount; ++i) {
		COMMON_NS::DataObjectReference dor = getGridRepresentationDor(i);
		convertDorIntoRel(dor);
	}
}
