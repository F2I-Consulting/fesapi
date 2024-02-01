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
#include "WellboreMarker.h"

#include <stdexcept>

#include "../witsml2_1/WellboreMarker.h"

#include "WellboreMarkerFrameRepresentation.h"
#include "BoundaryFeatureInterpretation.h"

using namespace std;
using namespace RESQML2_NS;

RESQML2_NS::BoundaryFeatureInterpretation* WellboreMarker::getBoundaryFeatureInterpretation() const
{
	return getWellboreMarkerFrameRepresentation()->getRepository()->getDataObjectByUuid<RESQML2_NS::BoundaryFeatureInterpretation>(getBoundaryFeatureInterpretationDor().getUuid());
}

WellboreMarkerFrameRepresentation const * WellboreMarker::getWellboreMarkerFrameRepresentation() const
{
	const vector<WellboreMarkerFrameRepresentation *> wmfr = getRepository()->getTargetObjects<WellboreMarkerFrameRepresentation>(this);
	return wmfr.size() == 1 ? wmfr[0] : nullptr;
}

WITSML2_1_NS::WellboreMarker* WellboreMarker::getWitsmlWellboreMarker() const
{
	return getWellboreMarkerFrameRepresentation()->getRepository()->getDataObjectByUuid<WITSML2_1_NS::WellboreMarker>(getWitsmlWellboreMarkerDor().getUuid());
}

bool WellboreMarker::hasDipAngle() const
{
	WITSML2_1_NS::WellboreMarker* witsmlMarker = getWitsmlWellboreMarker();
	if (witsmlMarker == nullptr) {
		return false;
	}

	return witsmlMarker == nullptr
		? false
		: witsmlMarker->hasDipAngle();
}

double WellboreMarker::getDipAngleValue() const
{
	if (!hasDipAngle()) {
		throw std::logic_error("There is no dip angle");
	}

	return getWitsmlWellboreMarker()->getDipAngleValue();
}

gsoap_eml2_3::eml23__PlaneAngleUom WellboreMarker::getDipAngleUom() const
{
	if (!hasDipAngle()) {
		throw std::logic_error("There is no dip angle");
	}

	return getWitsmlWellboreMarker()->getDipAngleUom();
}
string WellboreMarker::getDipAngleUomAsString() const
{
	if (!hasDipAngle()) {
		throw std::logic_error("There is no dip angle");
	}

	return getWitsmlWellboreMarker()->getDipAngleUomAsString();
}

bool WellboreMarker::hasDipDirection() const
{
	WITSML2_1_NS::WellboreMarker* witsmlMarker = getWitsmlWellboreMarker();
	if (witsmlMarker == nullptr) {
		return false;
	}

	return witsmlMarker == nullptr
		? false
		: witsmlMarker->hasDipDirection();
}

double WellboreMarker::getDipDirectionValue() const
{
	if (!hasDipDirection()) {
		throw std::logic_error("There is no dip direction");
	}

	return getWitsmlWellboreMarker()->getDipDirectionValue();
}

gsoap_eml2_3::eml23__PlaneAngleUom WellboreMarker::getDipDirectionUom() const
{
	if (!hasDipDirection()) {
		throw std::logic_error("There is no dip direction");
	}

	return getWitsmlWellboreMarker()->getDipDirectionUom();
}

string WellboreMarker::getDipDirectionUomAsString() const
{
	if (!hasDipDirection()) {
		throw std::logic_error("There is no dip angle");
	}

	return getWitsmlWellboreMarker()->getDipDirectionUomAsString();
}

void WellboreMarker::loadTargetRelationships()
{
	COMMON_NS::DataObjectReference dor = getBoundaryFeatureInterpretationDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<BoundaryFeatureInterpretation>(dor);
	}

	dor = getWitsmlWellboreMarkerDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<WITSML2_1_NS::WellboreMarker>(dor);
	}
}
