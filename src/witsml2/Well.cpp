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
#include "Well.h"

#include "../eml2_3/VerticalCrs.h"

#include "../resqml2/WellboreFeature.h"

#include "../witsml2_1/WellCompletion.h"

#include "Wellbore.h"

using namespace WITSML2_NS;

std::vector<RESQML2_NS::WellboreFeature *> Well::getResqmlWellboreFeatureSet() const
{
	return getRepository()->getSourceObjects<RESQML2_NS::WellboreFeature>(this);
}

std::vector<Wellbore *> Well::getWellboreSet() const
{
	return getRepository()->getSourceObjects<Wellbore>(this);
}

std::vector<WITSML2_1_NS::WellCompletion *> Well::getWellcompletionSet() const
{
	return getRepository()->getSourceObjects<WITSML2_1_NS::WellCompletion>(this);
}

EML2_3_NS::VerticalCrs* Well::getGroundElevationDatum() const
{
	return dynamic_cast<EML2_3_NS::VerticalCrs*>(getRepository()->getDataObjectByUuid(getGroundElevationDatumDor().getUuid()));
}

EML2_3_NS::VerticalCrs* Well::getWellheadElevationDatum() const
{
	return dynamic_cast<EML2_3_NS::VerticalCrs*>(getRepository()->getDataObjectByUuid(getWellheadElevationDatumDor().getUuid()));
}

void Well::loadTargetRelationships()
{
	COMMON_NS::DataObjectReference dor = getGroundElevationDatumDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel(dor);
	}
	dor = getWellheadElevationDatumDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel(dor);
	}
}
