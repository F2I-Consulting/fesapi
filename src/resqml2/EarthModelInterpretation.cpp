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
#include "EarthModelInterpretation.h"

#include <stdexcept>

#include "StructuralOrganizationInterpretation.h"
#include "StratigraphicColumn.h"
#include "StratigraphicOccurrenceInterpretation.h"
#include "RockFluidOrganizationInterpretation.h"

using namespace std;
using namespace RESQML2_NS;

const char* EarthModelInterpretation::XML_TAG = "EarthModelInterpretation";

StructuralOrganizationInterpretation* EarthModelInterpretation::getStructuralOrganizationInterpertation(unsigned int index) const
{
	return repository->getDataObjectByUuid<StructuralOrganizationInterpretation>(getStructuralOrganizationInterpertationDor(index).getUuid());
}

StratigraphicColumn* EarthModelInterpretation::getStratiColumn() const
{
	return repository->getDataObjectByUuid<StratigraphicColumn>(getStratiColumnDor().getUuid());
}

StratigraphicOccurrenceInterpretation* EarthModelInterpretation::getStratiOccurrence(unsigned int index) const
{
	return repository->getDataObjectByUuid<StratigraphicOccurrenceInterpretation>(getStratiOccurrenceDor(index).getUuid());
}

RockFluidOrganizationInterpretation* EarthModelInterpretation::getRockFluidOrganizationInterpretation(unsigned int index) const
{
	return repository->getDataObjectByUuid<RockFluidOrganizationInterpretation>(getRockFluidOrganizationInterpretationDor(index).getUuid());
}
		
void EarthModelInterpretation::loadTargetRelationships()
{
	AbstractFeatureInterpretation::loadTargetRelationships();

	COMMON_NS::DataObjectReference dor = getStratiColumnDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<StratigraphicColumn>(dor);
	}
	
	unsigned int count = getStructuralOrganizationInterpretationCount();
	for (unsigned int i = 0; i < count; ++i) {
		convertDorIntoRel<StructuralOrganizationInterpretation>(getStructuralOrganizationInterpertationDor(i));
	}

	count = getStratiOccurrenceCount();
	for (unsigned int i = 0; i < count; ++i) {
		convertDorIntoRel<StratigraphicOccurrenceInterpretation>(getStratiOccurrenceDor(i));
	}

	count = getRockFluidOrganizationInterpretationCount();
	for (unsigned int i = 0; i < count; ++i) {
		convertDorIntoRel<RockFluidOrganizationInterpretation>(getRockFluidOrganizationInterpretationDor(i));
	}
}
