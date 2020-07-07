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
#include "AbstractSurfaceRepresentation.h"

#include "PolylineRepresentation.h"

using namespace std;
using namespace RESQML2_NS;

void AbstractSurfaceRepresentation::loadTargetRelationships()
{
	AbstractRepresentation::loadTargetRelationships();

	for (size_t i = 0; i < getBoundariesCount(); ++i) {
		COMMON_NS::DataObjectReference dor = getOuterRingDor(i);
		if (!dor.isEmpty()) {
			convertDorIntoRel(dor);
		}
	}
}

unsigned int AbstractSurfaceRepresentation::getBoundariesCount() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractSurfaceRepresentation*>(gsoapProxy2_0_1)->Boundaries.size();
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_eml2_3::resqml22__AbstractSurfaceRepresentation*>(gsoapProxy2_3)->Boundaries.size();
	}

	throw std::logic_error("Unsupported version of RESQML");
}

COMMON_NS::DataObjectReference AbstractSurfaceRepresentation::getOuterRingDor(unsigned int index) const
{
	if (index >= getBoundariesCount()) {
		throw std::out_of_range("The index is out of range");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		auto boundaries = static_cast<gsoap_resqml2_0_1::resqml20__AbstractSurfaceRepresentation*>(gsoapProxy2_0_1)->Boundaries;
		return boundaries[index]->OuterRing == nullptr
			? COMMON_NS::DataObjectReference()
			: COMMON_NS::DataObjectReference(boundaries[index]->OuterRing);
	}
	else if (gsoapProxy2_3 != nullptr) {
		auto boundaries = static_cast<gsoap_eml2_3::resqml22__AbstractSurfaceRepresentation*>(gsoapProxy2_3)->Boundaries;
		return boundaries[index]->OuterRing == nullptr
			? COMMON_NS::DataObjectReference()
			: COMMON_NS::DataObjectReference(boundaries[index]->OuterRing);
	}
	else {
		throw std::logic_error("Unsupported version of RESQML");
	}
}

void AbstractSurfaceRepresentation::pushBackOuterRing(PolylineRepresentation * outerRing)
{
	if (outerRing == nullptr) {
		throw std::invalid_argument("outerRing cannot be nullptr.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractSurfaceRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml20__AbstractSurfaceRepresentation*>(gsoapProxy2_0_1);

		gsoap_resqml2_0_1::resqml20__PatchBoundaries * boundary = gsoap_resqml2_0_1::soap_new_resqml20__PatchBoundaries(gsoapProxy2_0_1->soap);
		boundary->ReferencedPatch = rep->Boundaries.size();
		boundary->OuterRing = outerRing->newResqmlReference();
		rep->Boundaries.push_back(boundary);
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__AbstractSurfaceRepresentation* rep = static_cast<gsoap_eml2_3::resqml22__AbstractSurfaceRepresentation*>(gsoapProxy2_3);
	
		gsoap_eml2_3::resqml22__PatchBoundaries * boundary = gsoap_eml2_3::soap_new_resqml22__PatchBoundaries(gsoapProxy2_3->soap);
		boundary->ReferencedPatch = rep->Boundaries.size();
		boundary->OuterRing = outerRing->newEml23Reference();
		rep->Boundaries.push_back(boundary);
	}
	else {
		throw std::logic_error("Unsupported version of RESQML");
	}

	getRepository()->addRelationship(this, outerRing);
}

void AbstractSurfaceRepresentation::setSurfaceRole(gsoap_resqml2_0_1::resqml20__SurfaceRole surfaceRole)
{
	if (gsoapProxy2_0_1 != nullptr) {
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractSurfaceRepresentation*>(gsoapProxy2_0_1)->SurfaceRole = surfaceRole;
	}
	else if (gsoapProxy2_3 != nullptr) {
		static_cast<gsoap_eml2_3::resqml22__AbstractSurfaceRepresentation*>(gsoapProxy2_3)->SurfaceRole = static_cast<gsoap_eml2_3::resqml22__SurfaceRole>(surfaceRole);
	}
	else {
		throw std::logic_error("Unsupported version of RESQML");
	}
}

gsoap_resqml2_0_1::resqml20__SurfaceRole AbstractSurfaceRepresentation::getSurfaceRole() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractSurfaceRepresentation*>(gsoapProxy2_0_1)->SurfaceRole;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__SurfaceRole>(
			static_cast<gsoap_eml2_3::resqml22__AbstractSurfaceRepresentation*>(gsoapProxy2_3)->SurfaceRole
		);
	}
	else {
		throw std::logic_error("Unsupported version of RESQML");
	}
}
