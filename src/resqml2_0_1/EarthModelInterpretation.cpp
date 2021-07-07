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
#include "EarthModelInterpretation.h"

#include <limits>
#include <stdexcept>

#include "../resqml2/Model.h"
#include "../resqml2/StructuralOrganizationInterpretation.h"
#include "../resqml2/StratigraphicColumn.h"
#include "../resqml2/GeologicUnitOccurrenceInterpretation.h"
#include "../resqml2/RockFluidOrganizationInterpretation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* EarthModelInterpretation::XML_NS = "resqml20";

EarthModelInterpretation::EarthModelInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const string & title)

{
	if (orgFeat == nullptr) {
		throw invalid_argument("The interpreted organization feature cannot be nullptr.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREEarthModelInterpretation(orgFeat->getGsoapContext());
	_resqml20__EarthModelInterpretation* interp = static_cast<_resqml20__EarthModelInterpretation*>(gsoapProxy2_0_1);

	interp->Domain = resqml20__Domain::mixed;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	orgFeat->getRepository()->addDataObject(this);
	setInterpretedFeature(orgFeat);
}

unsigned int EarthModelInterpretation::getStructuralOrganizationInterpretationCount() const
{
	return static_cast<_resqml20__EarthModelInterpretation*>(gsoapProxy2_0_1)->Structure != nullptr ? 1 : 0;
}

COMMON_NS::DataObjectReference EarthModelInterpretation::getStructuralOrganizationInterpertationDor(unsigned int index) const
{
	if (index >= getStructuralOrganizationInterpretationCount()) {
		throw std::out_of_range("A RESQML 2.0.1 earth model interpretation can only have up to 1 structural organization interpretation.");
	}

	return COMMON_NS::DataObjectReference(static_cast<_resqml20__EarthModelInterpretation*>(gsoapProxy2_0_1)->Structure);
}

void EarthModelInterpretation::pushBackStructuralOrganizationInterpretation(RESQML2_NS::StructuralOrganizationInterpretation * structOrganization)
{
	if (getStructuralOrganizationInterpretationCount() > 0) {
		throw std::range_error("A RESQML 2.0.1 earth model interpretation can only have up to 1 structural organization interpretation.");
	}

	getRepository()->addRelationship(this, structOrganization);

	static_cast<_resqml20__EarthModelInterpretation*>(gsoapProxy2_0_1)->Structure = structOrganization->newResqmlReference();
}

bool EarthModelInterpretation::hasStratiColumn() const
{
	return static_cast<_resqml20__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicColumn != nullptr;
}

void EarthModelInterpretation::setStratiColumn(RESQML2_NS::StratigraphicColumn * stratiColumn)
{
	getRepository()->addRelationship(this, stratiColumn);

	static_cast<_resqml20__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicColumn = stratiColumn->newResqmlReference();
}

COMMON_NS::DataObjectReference EarthModelInterpretation::getStratiColumnDor() const
{
	return hasStratiColumn()
		? COMMON_NS::DataObjectReference(static_cast<_resqml20__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicColumn)
		: COMMON_NS::DataObjectReference();
}

unsigned int EarthModelInterpretation::getGeologicUnitOccurrenceCount() const
{
	const size_t result = static_cast<_resqml20__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicOccurrences.size();
	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much GeologicUnitiOccurence ");
	}

	return static_cast<unsigned int>(result);
}

COMMON_NS::DataObjectReference EarthModelInterpretation::getGeologicUnitOccurrenceDor(unsigned int index) const
{
	_resqml20__EarthModelInterpretation* earthModelInterpretation = static_cast<_resqml20__EarthModelInterpretation*>(gsoapProxy2_0_1);
	if (index < earthModelInterpretation->StratigraphicOccurrences.size()) {
		return COMMON_NS::DataObjectReference(earthModelInterpretation->StratigraphicOccurrences[index]);
	}
	else {
		throw std::out_of_range("The strati occurence index is out of range.");
	}
}

void EarthModelInterpretation::pushBackGeologicUnitOccurrence(RESQML2_NS::GeologicUnitOccurrenceInterpretation* occurence)
{
	getRepository()->addRelationship(this, occurence);
		
	static_cast<_resqml20__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicOccurrences.push_back(occurence->newResqmlReference());
}

unsigned int EarthModelInterpretation::getRockFluidOrganizationInterpretationCount() const
{
	return static_cast<_resqml20__EarthModelInterpretation*>(gsoapProxy2_0_1)->Fluid != nullptr ? 1 : 0;
}

void EarthModelInterpretation::pushBackRockFluidOrganizationInterpretation(RESQML2_NS::RockFluidOrganizationInterpretation* rockFluid)
{
	if (getRockFluidOrganizationInterpretationCount() > 0) {
		throw std::range_error("A RESQML 2.0.1 earth model interpretation can only have up to 1 rock fluid organization interpretation.");
	}

	getRepository()->addRelationship(this, rockFluid);

	static_cast<_resqml20__EarthModelInterpretation*>(gsoapProxy2_0_1)->Structure = rockFluid->newResqmlReference();
}

COMMON_NS::DataObjectReference EarthModelInterpretation::getRockFluidOrganizationInterpretationDor(unsigned int index) const
{
	if (index >= getRockFluidOrganizationInterpretationCount()) {
		throw std::out_of_range("A RESQML 2.0.1 earth model interpretation can only have up to 1 rock fluid organization interpretation.");
	}

	return COMMON_NS::DataObjectReference(static_cast<_resqml20__EarthModelInterpretation*>(gsoapProxy2_0_1)->Fluid);
}
		