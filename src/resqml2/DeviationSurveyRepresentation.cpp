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
#include "DeviationSurveyRepresentation.h"

#include <stdexcept>
#include <limits>

#include "WellboreTrajectoryRepresentation.h"
#include "MdDatum.h"

using namespace std;
using namespace RESQML2_NS;
using namespace COMMON_NS;

const char* DeviationSurveyRepresentation::XML_TAG = "DeviationSurveyRepresentation";

void DeviationSurveyRepresentation::loadTargetRelationships()
{
	AbstractRepresentation::loadTargetRelationships();

	convertDorIntoRel<MdDatum>(getMdDatumDor());
}

MdDatum * DeviationSurveyRepresentation::getMdDatum() const
{
	return getRepository()->getDataObjectByUuid<MdDatum>(getMdDatumDor().getUuid());
}

vector<WellboreFrameRepresentation *> DeviationSurveyRepresentation::getWellboreFrameRepresentationSet() const
{
	vector<WellboreFrameRepresentation *> result;

	const vector<WellboreTrajectoryRepresentation *>& trajectories = getWellboreTrajectoryRepresentationSet();
	for (size_t index = 0; index < trajectories.size(); ++index) {
		if (trajectories[index]->getMdDatumDor().getUuid() == getMdDatumDor().getUuid() && trajectories[index]->getMdUom() == getMdUom()) {
			vector<WellboreFrameRepresentation *> tmp = trajectories[index]->getWellboreFrameRepresentationSet();
			result.insert(result.end(), tmp.begin(), tmp.end());
		}
	}

	return result;
}

unsigned int DeviationSurveyRepresentation::getWellboreFrameRepresentationCount() const
{
	const vector<WellboreTrajectoryRepresentation *>& trajectories = getWellboreTrajectoryRepresentationSet();
	unsigned int result = 0;
	for (size_t index = 0; index < trajectories.size(); ++index) {
		if (trajectories[index]->getMdDatumDor().getUuid() == getMdDatumDor().getUuid() && trajectories[index]->getMdUom() == getMdUom()) {
			result += trajectories[index]->getWellboreFrameRepresentationCount();
		}
	}

	return result;
}

WellboreFrameRepresentation * DeviationSurveyRepresentation::getWellboreFrameRepresentation(unsigned int index) const
{
	const vector<WellboreTrajectoryRepresentation *>& trajectories = getWellboreTrajectoryRepresentationSet();
	for (size_t trajIndex = 0; trajIndex < trajectories.size(); ++trajIndex) {
		WellboreTrajectoryRepresentation * traj = trajectories[trajIndex];
		if (traj->getMdDatumDor().getUuid() == getMdDatumDor().getUuid() && traj->getMdUom() == getMdUom()) {
			unsigned int count = traj->getWellboreFrameRepresentationCount();
			if (index < count) {
				return traj->getWellboreFrameRepresentation(index);
			}
			else {
				index -= count;
			}
		}
	}

	throw out_of_range("The index is out of range");
}

std::vector<WellboreTrajectoryRepresentation *> DeviationSurveyRepresentation::getWellboreTrajectoryRepresentationSet() const
{
	return getRepository()->getSourceObjects<WellboreTrajectoryRepresentation>(this);
}

unsigned int DeviationSurveyRepresentation::getWellboreTrajectoryRepresentationCount() const
{
	const size_t result = getWellboreTrajectoryRepresentationSet().size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw out_of_range("There are too many associated WellboreTrajectoryRepresentation.");
	}

	return static_cast<unsigned int>(result);
}

WellboreTrajectoryRepresentation * DeviationSurveyRepresentation::getWellboreTrajectoryRepresentation(unsigned int index) const
{
	const std::vector<WellboreTrajectoryRepresentation *>& wbTrajectoryRepSet = getWellboreTrajectoryRepresentationSet();

	if (index >= wbTrajectoryRepSet.size()) {
		throw out_of_range("The index is out of range");
	}

	return wbTrajectoryRepSet[index];
}
