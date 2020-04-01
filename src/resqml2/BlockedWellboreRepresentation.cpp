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
#include "BlockedWellboreRepresentation.h"

#include <stdexcept>

#include "../resqml2/AbstractGridRepresentation.h"

using namespace std;
using namespace RESQML2_NS;

const char* BlockedWellboreRepresentation::XML_TAG = "BlockedWellboreRepresentation";

void BlockedWellboreRepresentation::loadTargetRelationships()
{
	WellboreFrameRepresentation::loadTargetRelationships();

	// Supporting grid representation
	for (size_t i = 0; i < getSupportingGridRepresentationCount(); ++i) {
		convertDorIntoRel<RESQML2_NS::AbstractGridRepresentation>(getSupportingGridRepresentationDor(i));
	}

}

RESQML2_NS::AbstractGridRepresentation* BlockedWellboreRepresentation::getSupportingGridRepresentation(unsigned int index) const
{
	return repository->getDataObjectByUuid<RESQML2_NS::AbstractGridRepresentation>(getSupportingGridRepresentationDor(index).getUuid());
}
