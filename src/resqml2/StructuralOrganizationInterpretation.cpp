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
#include "StructuralOrganizationInterpretation.h"

#include <stdexcept>

#include "FaultInterpretation.h"
#include "HorizonInterpretation.h"

using namespace std;
using namespace RESQML2_NS;

const char* StructuralOrganizationInterpretation::XML_TAG = "StructuralOrganizationInterpretation";

RESQML2_NS::FaultInterpretation* StructuralOrganizationInterpretation::getFaultInterpretation(unsigned int index) const
{
	return repository->getDataObjectByUuid<RESQML2_NS::FaultInterpretation>(getFaultInterpretationDor(index).getUuid());
}

RESQML2_NS::HorizonInterpretation* StructuralOrganizationInterpretation::getHorizonInterpretation(unsigned int index) const
{
	return repository->getDataObjectByUuid<RESQML2_NS::HorizonInterpretation>(getHorizonInterpretationDor(index).getUuid());
}

RESQML2_NS::AbstractFeatureInterpretation* StructuralOrganizationInterpretation::getTopFrontierInterpretation(unsigned int index) const
{
	return repository->getDataObjectByUuid<RESQML2_NS::AbstractFeatureInterpretation>(getTopFrontierInterpretationDor(index).getUuid());
}

RESQML2_NS::AbstractFeatureInterpretation* StructuralOrganizationInterpretation::getBottomFrontierInterpretation(unsigned int index) const
{
	return repository->getDataObjectByUuid<RESQML2_NS::AbstractFeatureInterpretation>(getBottomFrontierInterpretationDor(index).getUuid());
}

RESQML2_NS::AbstractFeatureInterpretation* StructuralOrganizationInterpretation::getSideFrontierInterpretation(unsigned int index) const
{
	return repository->getDataObjectByUuid<RESQML2_NS::AbstractFeatureInterpretation>(getSideFrontierInterpretationDor(index).getUuid());
}
		
void StructuralOrganizationInterpretation::loadTargetRelationships()
{
	AbstractOrganizationInterpretation::loadTargetRelationships();

	size_t count = getFaultInterpretationCount();
	for (size_t i = 0; i < count; ++i) {
		convertDorIntoRel<RESQML2_NS::FaultInterpretation>(getFaultInterpretationDor(i));
	}

	count = getHorizonInterpretationCount();
	for (size_t i = 0; i < count; ++i) {
		convertDorIntoRel<RESQML2_NS::HorizonInterpretation>(getHorizonInterpretationDor(i));
	}

	count = getTopFrontierInterpretationCount();
	for (size_t i = 0; i < count; ++i) {
		convertDorIntoRel<RESQML2_NS::AbstractFeatureInterpretation>(getTopFrontierInterpretationDor(i));
	}

	count = getBottomFrontierInterpretationCount();
	for (size_t i = 0; i < count; ++i) {
		convertDorIntoRel<RESQML2_NS::AbstractFeatureInterpretation>(getBottomFrontierInterpretationDor(i));
	}

	count = getSideFrontierInterpretationCount();
	for (size_t i = 0; i < count; ++i) {
		convertDorIntoRel<RESQML2_NS::AbstractFeatureInterpretation>(getSideFrontierInterpretationDor(i));
	}
}
