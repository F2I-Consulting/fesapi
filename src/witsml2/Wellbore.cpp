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
#include "Wellbore.h"

#include "../resqml2/WellboreFeature.h"

#include "../witsml2_1/WellboreCompletion.h"
#include "../witsml2_1/WellboreGeometry.h"
#include "../witsml2_1/Log.h"

#include "Trajectory.h"
#include "Well.h"

using namespace WITSML2_NS;

Well* Wellbore::getWell() const
{
	return getRepository()->getDataObjectByUuid<Well>(getWellDor().getUuid());
}

void Wellbore::loadTargetRelationships()
{
	convertDorIntoRel<Well>(getWellDor());
}

std::vector<RESQML2_NS::WellboreFeature*> Wellbore::getResqmlWellboreFeatureSet() const
{
	return getRepository()->getSourceObjects<RESQML2_NS::WellboreFeature>(this);
}

std::vector<WITSML2_1_NS::WellboreCompletion *> Wellbore::getWellboreCompletionSet() const
{
	return getRepository()->getSourceObjects<WITSML2_1_NS::WellboreCompletion>(this);
}

std::vector<Trajectory *> Wellbore::getTrajectorySet() const
{
	return getRepository()->getSourceObjects<Trajectory>(this);
}

std::vector<WITSML2_1_NS::WellboreGeometry *> Wellbore::getWellboreGeometrySet() const
{
	return getRepository()->getSourceObjects<WITSML2_1_NS::WellboreGeometry>(this);
}

std::vector<WITSML2_1_NS::Log *> Wellbore::getLogSet() const
{
	return getRepository()->getSourceObjects<WITSML2_1_NS::Log>(this);
}
