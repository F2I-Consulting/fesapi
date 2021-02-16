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

#include "../resqml2_0_1/WellboreFeature.h"

#include "Trajectory.h"
#include "Well.h"

#include "../Witsml2_0/WellboreCompletion.h"
#include "../Witsml2_0/WellboreGeometry.h"
#include "../Witsml2_0/Log.h"

using namespace WITSML2_NS;

Well* Wellbore::getWell() const
{
	return getRepository()->getDataObjectByUuid<Well>(getWellDor().getUuid());
}

void Wellbore::loadTargetRelationships()
{
	convertDorIntoRel<Well>(getWellDor());
}

std::vector<RESQML2_0_1_NS::WellboreFeature *> Wellbore::getResqmlWellboreFeature() const
{
	return getRepository()->getSourceObjects<RESQML2_0_1_NS::WellboreFeature>(this);
}

std::vector<WITSML2_0_NS::WellboreCompletion *> Wellbore::getWellboreCompletions() const
{
	return getRepository()->getSourceObjects<WITSML2_0_NS::WellboreCompletion>(this);
}

std::vector<Trajectory *> Wellbore::getTrajectories() const
{
	return getRepository()->getSourceObjects<Trajectory>(this);
}

std::vector<WITSML2_0_NS::WellboreGeometry *> Wellbore::getWellboreGeometries() const
{
	return getRepository()->getSourceObjects<WITSML2_0_NS::WellboreGeometry>(this);
}

std::vector<WITSML2_0_NS::Log *> Wellbore::getLogs() const
{
	return getRepository()->getSourceObjects<WITSML2_0_NS::Log>(this);
}
