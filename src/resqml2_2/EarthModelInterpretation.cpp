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
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* EarthModelInterpretation::XML_NS = "resqml22";

EarthModelInterpretation::EarthModelInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const string & title)
{
	if (orgFeat == nullptr) {
		throw invalid_argument("The interpreted organization feature cannot be nullptr.");
	}

	gsoapProxy2_3 = soap_new_resqml22__EarthModelInterpretation(orgFeat->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	orgFeat->getRepository()->addDataObject(this);
	setInterpretedFeature(orgFeat);
}

unsigned int EarthModelInterpretation::getStructuralOrganizationInterpretationCount() const
{
	const size_t result = static_cast<_resqml22__EarthModelInterpretation*>(gsoapProxy2_3)->Structure.size();
	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much structural organization.");
	}

	return static_cast<unsigned int>(result);
}

COMMON_NS::DataObjectReference EarthModelInterpretation::getStructuralOrganizationInterpertationDor(unsigned int index) const
{
	_resqml22__EarthModelInterpretation* earthModelInterpretation = static_cast<_resqml22__EarthModelInterpretation*>(gsoapProxy2_3);
	if (index < earthModelInterpretation->Structure.size()) {
		return COMMON_NS::DataObjectReference(earthModelInterpretation->Structure[index]);
	}
	else {
		throw std::out_of_range("The structural organization index is out of range.");
	}
}

void EarthModelInterpretation::pushBackStructuralOrganizationInterpretation(RESQML2_NS::StructuralOrganizationInterpretation * structOrganization)
{
	getRepository()->addRelationship(this, structOrganization);
        
	static_cast<_resqml22__EarthModelInterpretation*>(gsoapProxy2_3)->Structure.push_back(structOrganization->newEml23Reference());
}

bool EarthModelInterpretation::hasStratiColumn() const
{
	return static_cast<_resqml22__EarthModelInterpretation*>(gsoapProxy2_3)->StratigraphicColumn != nullptr;
}

void EarthModelInterpretation::setStratiColumn(RESQML2_NS::StratigraphicColumn * stratiColumn)
{
	getRepository()->addRelationship(this, stratiColumn);

	static_cast<_resqml22__EarthModelInterpretation*>(gsoapProxy2_3)->StratigraphicColumn = stratiColumn->newEml23Reference();
}

COMMON_NS::DataObjectReference EarthModelInterpretation::getStratiColumnDor() const
{
	return hasStratiColumn()
		? COMMON_NS::DataObjectReference(static_cast<_resqml22__EarthModelInterpretation*>(gsoapProxy2_3)->StratigraphicColumn)
		: COMMON_NS::DataObjectReference();
}

unsigned int EarthModelInterpretation::getGeologicUnitOccurrenceCount() const
{
	const size_t result = static_cast<_resqml22__EarthModelInterpretation*>(gsoapProxy2_3)->StratigraphicOccurrences.size();
	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much StratiOccurrences");
	}

	return static_cast<unsigned int>(result);
}

COMMON_NS::DataObjectReference EarthModelInterpretation::getGeologicUnitOccurrenceDor(unsigned int index) const
{
	_resqml22__EarthModelInterpretation* earthModelInterpretation = static_cast<_resqml22__EarthModelInterpretation*>(gsoapProxy2_3);
	if (index < earthModelInterpretation->StratigraphicOccurrences.size()) {
		return COMMON_NS::DataObjectReference(earthModelInterpretation->StratigraphicOccurrences[index]);
	}
	else {
		throw std::out_of_range("The strati occurence index is out of range.");
	}
}

void EarthModelInterpretation::pushBackGeologicUnitOccurrence(RESQML2_NS::GeologicUnitOccurrenceInterpretation * occurrence)
{
	getRepository()->addRelationship(this, occurrence);
		
	static_cast<_resqml22__EarthModelInterpretation*>(gsoapProxy2_3)->StratigraphicOccurrences.push_back(occurrence->newEml23Reference());
}

unsigned int EarthModelInterpretation::getRockFluidOrganizationInterpretationCount() const
{
	const size_t result = static_cast<_resqml22__EarthModelInterpretation*>(gsoapProxy2_3)->Fluid.size();
	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much Fluid organization");
	}

	return static_cast<unsigned int>(result);
}

void EarthModelInterpretation::pushBackRockFluidOrganizationInterpretation(RESQML2_NS::RockFluidOrganizationInterpretation* rockFluid)
{
	getRepository()->addRelationship(this, rockFluid);

	static_cast<_resqml22__EarthModelInterpretation*>(gsoapProxy2_3)->Fluid.push_back(rockFluid->newEml23Reference());
}

COMMON_NS::DataObjectReference EarthModelInterpretation::getRockFluidOrganizationInterpretationDor(unsigned int index) const
{
	_resqml22__EarthModelInterpretation* earthModelInterpretation = static_cast<_resqml22__EarthModelInterpretation*>(gsoapProxy2_3);
	if (index < earthModelInterpretation->Fluid.size()) {
		return COMMON_NS::DataObjectReference(earthModelInterpretation->Fluid[index]);
	}
	else {
		throw std::out_of_range("The Fluid organization index is out of range.");
	}
}
