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
#include "SealedVolumeFrameworkRepresentation.h"

#include "SealedSurfaceFrameworkRepresentation.h"
#include "StratigraphicUnitInterpretation.h"

using namespace std;
using namespace RESQML2_NS;

const char* SealedVolumeFrameworkRepresentation::XML_TAG = "SealedVolumeFrameworkRepresentation";

void SealedVolumeFrameworkRepresentation::setSealedSurfaceFramework(SealedSurfaceFrameworkRepresentation* ssf)
{
	if (ssf == nullptr) {
		throw invalid_argument("Cannot set a null SealedSurfaceFrameworkRepresentation");
	}
	if (getRepository() == nullptr) {
		ssf->getRepository()->addOrReplaceDataObject(this);
	}

	getRepository()->addRelationship(this, ssf);

	setXmlSealedSurfaceFramework(ssf);
}

void SealedVolumeFrameworkRepresentation::setInterpretationOfVolumeRegion(unsigned int regionIndex, StratigraphicUnitInterpretation * stratiUnitInterp)
{
	if (stratiUnitInterp == nullptr) {
		throw invalid_argument("Cannot set a null strati Unit Interpretation");
	}

	if (regionIndex >= getRegionCount()) {
		throw out_of_range("The region index is out of range.");
	}

	getRepository()->addRelationship(this, stratiUnitInterp);

	setXmlInterpretationOfVolumeRegion(regionIndex, stratiUnitInterp);
}

SealedSurfaceFrameworkRepresentation* SealedVolumeFrameworkRepresentation::getSealedStructuralFramework() const
{
	return repository->getDataObjectByUuid<SealedSurfaceFrameworkRepresentation>(getSealedStructuralFrameworkDor().getUuid());
}

StratigraphicUnitInterpretation* SealedVolumeFrameworkRepresentation::getStratiUnitInterp(unsigned int regionIndex) const
{
	return repository->getDataObjectByUuid<StratigraphicUnitInterpretation>(getStratiUnitInterpDor(regionIndex).getUuid());
}

void SealedVolumeFrameworkRepresentation::loadTargetRelationships()
{
	RESQML2_NS::RepresentationSetRepresentation::loadTargetRelationships();

	convertDorIntoRel<SealedSurfaceFrameworkRepresentation>(getSealedStructuralFrameworkDor());

	const unsigned int count = getRegionCount();
	for (unsigned int regionIdx = 0; regionIdx < count; ++regionIdx) {
		convertDorIntoRel<StratigraphicUnitInterpretation>(getStratiUnitInterpDor(regionIdx));
	}
}
