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
#include "RockFluidUnitFeature.h"

#include "BoundaryFeature.h"

#include "../prodml2_3/FluidCharacterization.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* RockFluidUnitFeature::XML_TAG = "RockFluidUnitFeature";

RockFluidUnitFeature::RockFluidUnitFeature(COMMON_NS::DataObjectRepository* repo, const string & guid, const string & title, gsoap_resqml2_0_1::resqml20__Phase phase, BoundaryFeature* top, BoundaryFeature* bottom)
{
	if (repo == nullptr)
		throw invalid_argument("The repo cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORERockFluidUnitFeature(repo->getGsoapContext());
	_resqml20__RockFluidUnitFeature* rfuf = static_cast<_resqml20__RockFluidUnitFeature*>(gsoapProxy2_0_1);
	rfuf->Phase = phase;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
	setTop(top);
	setBottom(bottom);
}

void RockFluidUnitFeature::setTop(BoundaryFeature* top)
{
	getRepository()->addRelationship(this, top);

	static_cast<_resqml20__RockFluidUnitFeature*>(gsoapProxy2_0_1)->FluidBoundaryTop = top->newResqmlReference();
}

BoundaryFeature* RockFluidUnitFeature::getTop() const
{
	return repository->getDataObjectByUuid<BoundaryFeature>(static_cast<_resqml20__RockFluidUnitFeature*>(gsoapProxy2_0_1)->FluidBoundaryTop->UUID);
}

void RockFluidUnitFeature::setBottom(BoundaryFeature* bottom)
{
	getRepository()->addRelationship(this, bottom);

	static_cast<_resqml20__RockFluidUnitFeature*>(gsoapProxy2_0_1)->FluidBoundaryBottom = bottom->newResqmlReference();
}

BoundaryFeature* RockFluidUnitFeature::getBottom() const
{
	return repository->getDataObjectByUuid<BoundaryFeature>(static_cast<_resqml20__RockFluidUnitFeature*>(gsoapProxy2_0_1)->FluidBoundaryBottom->UUID);
}

std::vector<PRODML2_3_NS::FluidCharacterization *> RockFluidUnitFeature::getFluidCharacterizationSet() const
{
	return repository->getSourceObjects<PRODML2_3_NS::FluidCharacterization>(this);
}

void RockFluidUnitFeature::loadTargetRelationships()
{
	_resqml20__RockFluidUnitFeature* interp = static_cast<_resqml20__RockFluidUnitFeature*>(gsoapProxy2_0_1);

	COMMON_NS::DataObjectReference dor(interp->FluidBoundaryTop);
	if(!dor.isEmpty()) {
		convertDorIntoRel<BoundaryFeature>(dor);
	}

	dor = COMMON_NS::DataObjectReference(interp->FluidBoundaryBottom);
	if(!dor.isEmpty()) {
		convertDorIntoRel<BoundaryFeature>(dor);
	}
}
