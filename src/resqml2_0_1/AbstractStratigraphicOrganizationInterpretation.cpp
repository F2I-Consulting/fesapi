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
#include "resqml2_0_1/AbstractStratigraphicOrganizationInterpretation.h"

#include <stdexcept>
#include <algorithm>

using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace std;
using namespace epc;

unsigned int AbstractStratigraphicOrganizationInterpretation::getGridRepresentationCount() const
{
	return gridRepresentationSet.size();
}

RESQML2_NS::AbstractGridRepresentation* AbstractStratigraphicOrganizationInterpretation::getGridRepresentation(const unsigned int & index) const
{
	if (index >= getGridRepresentationCount()) {
		throw range_error("The index of the grid representation to get is out of range.");
	}

	return gridRepresentationSet[index];
}

bool AbstractStratigraphicOrganizationInterpretation::isAssociatedToGridRepresentation(RESQML2_NS::AbstractGridRepresentation* gridRep) const
{
	return find(gridRepresentationSet.begin(), gridRepresentationSet.end(), gridRep) != gridRepresentationSet.end();
}

vector<Relationship> AbstractStratigraphicOrganizationInterpretation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractOrganizationInterpretation::getAllEpcRelationships();

	for (size_t i = 0; i < gridRepresentationSet.size(); ++i) {
		Relationship relRep(gridRepresentationSet[i]->getPartNameInEpcDocument(), "", gridRepresentationSet[i]->getUuid());
		relRep.setSourceObjectType();
		result.push_back(relRep);
	}

	return result;
}

