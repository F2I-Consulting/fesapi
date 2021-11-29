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
#include "SubRepresentation.h"

#include <limits>
#include <stdexcept>

#include <hdf5.h>

#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_NS;

const char* SubRepresentation::XML_TAG = "SubRepresentation";

uint64_t SubRepresentation::getXyzPointCountOfPatch(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	if (getElementKind() == gsoap_eml2_3::eml23__IndexableElement::nodes) {
		return getElementCountOfPatch(patchIndex);
	}
	else {
		throw logic_error("Not implemented yet.");
	}
}

void SubRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double *) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	throw logic_error("Not implemented yet");
}

AbstractRepresentation* SubRepresentation::getSupportingRepresentationOfPatch(unsigned int patchIndex) const
{
	return getRepository()->getDataObjectByUuid<AbstractRepresentation>(getSupportingRepresentationOfPatchDor(patchIndex).getUuid());
}
