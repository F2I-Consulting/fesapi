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
#include "WellboreTrajectoryRepresentation.h"

#include <stdexcept>
#include <limits>

#include "H5public.h"

#include "WellboreInterpretation.h"
#include "MdDatum.h"
#include "WellboreFrameRepresentation.h"
#include "AbstractLocal3dCrs.h"
#include "../common/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_NS;
using namespace gsoap_eml2_2;
using namespace COMMON_NS;

const char* WellboreTrajectoryRepresentation::XML_TAG = "WellboreTrajectoryRepresentation";

void WellboreTrajectoryRepresentation::loadTargetRelationships()
{
	AbstractRepresentation::loadTargetRelationships();

	COMMON_NS::DataObjectReference dor = getMdDatumDor();
	convertDorIntoRel<RESQML2_NS::MdDatum>(dor);

	dor = getDeviationSurveyDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<DeviationSurveyRepresentation>(dor);
	}

	dor = getParentTrajectoryDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<WellboreTrajectoryRepresentation>(dor);
	}
}

RESQML2_NS::MdDatum * WellboreTrajectoryRepresentation::getMdDatum() const
{
	return getRepository()->getDataObjectByUuid<RESQML2_NS::MdDatum>(getMdDatumDor().getUuid());
}

WellboreTrajectoryRepresentation* WellboreTrajectoryRepresentation::getParentTrajectory() const
{
	getRepository()->getDataObjectByUuid<WellboreTrajectoryRepresentation>(getParentTrajectoryDor().getUuid());
}

std::vector<WellboreTrajectoryRepresentation *> WellboreTrajectoryRepresentation::getChildrenTrajectorySet() const
{
	return getRepository()->getSourceObjects<WellboreTrajectoryRepresentation>(this);
}

std::vector<RESQML2_NS::WellboreFrameRepresentation *> WellboreTrajectoryRepresentation::getWellboreFrameRepresentationSet() const
{
	return getRepository()->getSourceObjects<RESQML2_NS::WellboreFrameRepresentation>(this);
}

unsigned int WellboreTrajectoryRepresentation::getWellboreFrameRepresentationCount() const
{
	const size_t result = getWellboreFrameRepresentationSet().size();
	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too much associated WellboreFrameRepresentation.");
	}

	return static_cast<unsigned int>(result);
}

RESQML2_NS::WellboreFrameRepresentation * WellboreTrajectoryRepresentation::getWellboreFrameRepresentation(unsigned int index) const
{
	const std::vector<RESQML2_NS::WellboreFrameRepresentation *>& wfrs = getWellboreFrameRepresentationSet();

	if (index >= wfrs.size()) {
		throw out_of_range("The index if out of range");
	}

	return wfrs[index];
}

DeviationSurveyRepresentation* WellboreTrajectoryRepresentation::getDeviationSurvey() const
{
	getRepository()->getDataObjectByUuid<DeviationSurveyRepresentation>(getDeviationSurveyDor().getUuid());
}
