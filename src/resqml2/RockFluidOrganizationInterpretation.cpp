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
#include "RockFluidOrganizationInterpretation.h"

#include <algorithm>
#include <limits>

#include "RockFluidUnitInterpretation.h"
#include "AbstractGridRepresentation.h"

using namespace std;
using namespace RESQML2_NS;
using namespace gsoap_resqml2_0_1;

std::vector<AbstractGridRepresentation *> RockFluidOrganizationInterpretation::getGridRepresentationSet() const
{
	return getRepository()->getSourceObjects<AbstractGridRepresentation>(this);
}

unsigned int RockFluidOrganizationInterpretation::getGridRepresentationCount() const
{
	const size_t count = getGridRepresentationSet().size();
	if (count > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("Too much grid representations.");
	}

	return static_cast<unsigned int>(count);
}

AbstractGridRepresentation * RockFluidOrganizationInterpretation::getGridRepresentation(unsigned int index) const
{
	const std::vector<AbstractGridRepresentation *>& gridRepresentationSet = getGridRepresentationSet();

	if (index >= gridRepresentationSet.size()) {
		throw out_of_range("The index of the grid representation to get is out of range.");
	}

	return gridRepresentationSet[index];
}

bool RockFluidOrganizationInterpretation::isAssociatedToGridRepresentation(AbstractGridRepresentation* gridRep) const
{
	const std::vector<AbstractGridRepresentation *>& gridRepresentationSet = getGridRepresentationSet();
	return find(gridRepresentationSet.begin(), gridRepresentationSet.end(), gridRep) != gridRepresentationSet.end();
}

RockFluidUnitInterpretation* RockFluidOrganizationInterpretation::getRockFluidUnitInterpretation(unsigned int index) const
{
	return repository->getDataObjectByUuid<RockFluidUnitInterpretation>(getRockFluidUnitInterpretationDor(index).getUuid());
}

void RockFluidOrganizationInterpretation::loadTargetRelationships()
{
	AbstractOrganizationInterpretation::loadTargetRelationships();

	for (unsigned int i = 0; i < getRockFluidUnitInterpCount(); ++i) {
		COMMON_NS::DataObjectReference dor = getRockFluidUnitInterpretationDor(i);
		if (!dor.isEmpty()) {
			convertDorIntoRel<RockFluidUnitInterpretation>(dor);
		}
	}
}
