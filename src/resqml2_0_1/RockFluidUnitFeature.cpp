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
#include "resqml2_0_1/RockFluidUnitFeature.h"
#include "resqml2_0_1/FluidBoundaryFeature.h"
#include "tools/Misc.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* RockFluidUnitFeature::XML_TAG = "RockFluidUnitFeature";

RockFluidUnitFeature::RockFluidUnitFeature(soap* soapContext, const string & guid, const string & title, gsoap_resqml2_0_1::resqml2__Phase phase, FluidBoundaryFeature* fluidBoundaryTop, FluidBoundaryFeature* fluidBoundaryBottom)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORERockFluidUnitFeature(soapContext, 1);
	_resqml2__RockFluidUnitFeature* rfuf = static_cast<_resqml2__RockFluidUnitFeature*>(gsoapProxy2_0_1);
	rfuf->Phase = phase;
	rfuf->FluidBoundaryTop = fluidBoundaryTop->newResqmlReference();
	rfuf->FluidBoundaryBottom = fluidBoundaryBottom->newResqmlReference();

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());
}

void RockFluidUnitFeature::setFluidBoundaryTop(FluidBoundaryFeature* fluidBoundaryFeature)
{
	// epc
	fluidBoundaryFeature->rockFluidUnitFeature = this;

	//XML
	if(updateXml) {
		static_cast<_resqml2__RockFluidUnitFeature*>(gsoapProxy2_0_1)->FluidBoundaryTop = fluidBoundaryFeature->newResqmlReference();
	}
}

FluidBoundaryFeature* RockFluidUnitFeature::getFluidBoundaryTop() const
{
	return epcDocument->getDataObjectByUuid<FluidBoundaryFeature>(static_cast<_resqml2__RockFluidUnitFeature*>(gsoapProxy2_0_1)->FluidBoundaryTop->UUID);
}

void RockFluidUnitFeature::setFluidBoundaryBottom(FluidBoundaryFeature* fluidBoundaryFeature)
{
	// epc
	fluidBoundaryFeature->rockFluidUnitFeature = this;

	//XML
	if(updateXml) {
		static_cast<_resqml2__RockFluidUnitFeature*>(gsoapProxy2_0_1)->FluidBoundaryBottom = fluidBoundaryFeature->newResqmlReference();
	}
}

FluidBoundaryFeature* RockFluidUnitFeature::getFluidBoundaryBottom() const
{
	return epcDocument->getDataObjectByUuid<FluidBoundaryFeature>(static_cast<_resqml2__RockFluidUnitFeature*>(gsoapProxy2_0_1)->FluidBoundaryBottom->UUID);
}

vector<Relationship> RockFluidUnitFeature::getAllEpcRelationships() const
{
	vector<Relationship> result =  GeologicUnitFeature::getAllEpcRelationships();

	_resqml2__RockFluidUnitFeature* interp = static_cast<_resqml2__RockFluidUnitFeature*>(gsoapProxy2_0_1);

	if (interp->FluidBoundaryTop != nullptr)
	{
		Relationship rel(misc::getPartNameFromReference(interp->FluidBoundaryTop), "", interp->FluidBoundaryTop->UUID);
		rel.setDestinationObjectType();
		result.push_back(rel);
	}

	if (interp->FluidBoundaryBottom != nullptr)
	{
		Relationship rel(misc::getPartNameFromReference(interp->FluidBoundaryBottom), "", interp->FluidBoundaryBottom->UUID);
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
	return result;
}

void RockFluidUnitFeature::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	GeologicUnitFeature::importRelationshipSetFromEpc(epcDoc);

	_resqml2__RockFluidUnitFeature* interp = static_cast<_resqml2__RockFluidUnitFeature*>(gsoapProxy2_0_1);

	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = interp->FluidBoundaryTop;
	if(dor != nullptr)
	{
		FluidBoundaryFeature* feature = epcDoc->getDataObjectByUuid<FluidBoundaryFeature>(dor->UUID);
		if (feature == nullptr) { // partial transfer
			getEpcDocument()->createPartial(dor);
			feature = getEpcDocument()->getDataObjectByUuid<FluidBoundaryFeature>(dor->UUID);
		}
		if (feature == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
		updateXml = false;
		setFluidBoundaryTop(feature);
		updateXml = true;
	}

	dor = interp->FluidBoundaryBottom;
	if(dor != nullptr)
	{
		FluidBoundaryFeature* feature = epcDoc->getDataObjectByUuid<FluidBoundaryFeature>(dor->UUID);
		if (feature == nullptr) { // partial transfer
			getEpcDocument()->createPartial(dor);
			feature = getEpcDocument()->getDataObjectByUuid<FluidBoundaryFeature>(dor->UUID);
		}
		if (feature == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
		updateXml = false;
		setFluidBoundaryBottom(feature);
		updateXml = true;
	}
}
