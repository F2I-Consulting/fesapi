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
#include "RepresentationSetRepresentation.h"

#include <stdexcept>
#include <limits>

using namespace std;
using namespace RESQML2_NS;

const char* RepresentationSetRepresentation::XML_TAG = "RepresentationSetRepresentation";

void RepresentationSetRepresentation::loadTargetRelationships()
{
	AbstractRepresentation::loadTargetRelationships();

	const unsigned int repCount = getRepresentationCount();
	for (unsigned int i = 0; i < repCount; ++i)
	{
		COMMON_NS::DataObjectReference dor = getRepresentationDor(i);
		convertDorIntoRel(dor);
	}
}

ULONG64 RepresentationSetRepresentation::getXyzPointCountOfPatch(const unsigned int &) const
{
	throw logic_error("Not implemented yet.");
}

void RepresentationSetRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double *) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index patch is not in the allowed range of patch.");
	}

	// TODO Use getXyzPointsOfAllPatches on each included representation.
	throw logic_error("Not implemented yet.");
}

bool RepresentationSetRepresentation::isHomogeneous() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::_resqml20__RepresentationSetRepresentation*>(gsoapProxy2_0_1)->IsHomogeneous;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_eml2_3::_resqml22__RepresentationSetRepresentation*>(gsoapProxy2_3)->IsHomogeneous;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

unsigned int RepresentationSetRepresentation::getRepresentationCount() const
{
	size_t count = 0;
	if (gsoapProxy2_0_1 != nullptr) {
		count = static_cast<gsoap_resqml2_0_1::_resqml20__RepresentationSetRepresentation*>(gsoapProxy2_0_1)->Representation.size();
	}
	else if (gsoapProxy2_3 != nullptr) {
		count = static_cast<gsoap_eml2_3::_resqml22__RepresentationSetRepresentation*>(gsoapProxy2_3)->Representation.size();
	}
	else {
		throw logic_error("Not implemented yet");
	}

	if (count > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("The count is too big.");
	}

	return static_cast<unsigned int>(count);
}

RESQML2_NS::AbstractRepresentation* RepresentationSetRepresentation::getRepresentation(unsigned int index) const
{
	return repository->getDataObjectByUuid<RESQML2_NS::AbstractRepresentation>(getRepresentationDor(index).getUuid());
}

COMMON_NS::DataObjectReference RepresentationSetRepresentation::getRepresentationDor(unsigned int index) const
{
	if (index >= getRepresentationCount()) {
		throw out_of_range("The index of the representation to get is out of range in this representaiton set representation");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::_resqml20__RepresentationSetRepresentation*>(gsoapProxy2_0_1)->Representation[index]);
	}
	else if (gsoapProxy2_3 != nullptr) {
		return COMMON_NS::DataObjectReference(static_cast<gsoap_eml2_3::_resqml22__RepresentationSetRepresentation*>(gsoapProxy2_3)->Representation[index]);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void RepresentationSetRepresentation::pushBack(RESQML2_NS::AbstractRepresentation* rep)
{
	getRepository()->addRelationship(this, rep);

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::_resqml20__RepresentationSetRepresentation* rsr = static_cast<gsoap_resqml2_0_1::_resqml20__RepresentationSetRepresentation*>(gsoapProxy2_0_1);

		rsr->Representation.push_back(rep->newResqmlReference());
		if (isHomogeneous() && getRepresentationCount() > 1)
		{
			if (rep->getGsoapType() != getRepresentation(0)->getGsoapType()) {
				rsr->IsHomogeneous = false;
			}
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::_resqml22__RepresentationSetRepresentation* rsr = static_cast<gsoap_eml2_3::_resqml22__RepresentationSetRepresentation*>(gsoapProxy2_3);

		rsr->Representation.push_back(rep->newEml23Reference());
		if (isHomogeneous() && getRepresentationCount() > 1)
		{
			if (rep->getGsoapType() != getRepresentation(0)->getGsoapType()) {
				rsr->IsHomogeneous = false;
			}
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}
