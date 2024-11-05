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
#include "FluidSystem.h"

#include <stdexcept>

#include "FluidCharacterization.h"

#include "../resqml2/RockFluidOrganizationInterpretation.h"
#include "../resqml2/StratigraphicOccurrenceInterpretation.h"

using namespace std;
using namespace PRODML2_2_NS;
using namespace gsoap_eml2_3;
using namespace COMMON_NS;

FluidSystem::FluidSystem(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid,
	const std::string & title,
	double temperatureValue, gsoap_eml2_3::eml23__ThermodynamicTemperatureUom temperatureUom,
	double pressureValue, gsoap_eml2_3::eml23__PressureUom pressureUom,
	gsoap_eml2_3::prodml22__ReservoirFluidKind reservoirFluidKind,
	double gasOilRatio, gsoap_eml2_3::eml23__VolumePerVolumeUom gasOilRatioUom)
{
	if (repo == nullptr) {
		throw invalid_argument("A repo must exist.");
	}

	gsoapProxy2_3 = soap_new_prodml22__FluidSystem(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	prodml22__FluidSystem* fs = static_cast<prodml22__FluidSystem*>(gsoapProxy2_3);

	fs->StandardConditions = soap_new_eml23__TemperaturePressure(repo->getGsoapContext());
	static_cast<eml23__TemperaturePressure*>(fs->StandardConditions)->Temperature = soap_new_eml23__ThermodynamicTemperatureMeasure(repo->getGsoapContext());
	static_cast<eml23__TemperaturePressure*>(fs->StandardConditions)->Temperature->__item = temperatureValue;
	static_cast<eml23__TemperaturePressure*>(fs->StandardConditions)->Temperature->uom = temperatureUom;
	static_cast<eml23__TemperaturePressure*>(fs->StandardConditions)->Pressure = soap_new_eml23__PressureMeasure(repo->getGsoapContext());
	static_cast<eml23__TemperaturePressure*>(fs->StandardConditions)->Pressure->__item = pressureValue;
	static_cast<eml23__TemperaturePressure*>(fs->StandardConditions)->Pressure->uom = gsoap_eml2_3::soap_eml23__PressureUom2s(repo->getGsoapContext(), pressureUom);

	fs->ReservoirFluidKind = reservoirFluidKind;

	fs->SolutionGOR = soap_new_eml23__VolumePerVolumeMeasure(repo->getGsoapContext());
	fs->SolutionGOR->__item = gasOilRatio;
	fs->SolutionGOR->uom = gsoap_eml2_3::soap_eml23__VolumePerVolumeUom2s(repo->getGsoapContext(), gasOilRatioUom);

	repo->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
}

FluidSystem::FluidSystem(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid,
	const std::string & title,
	gsoap_eml2_3::eml23__ReferenceCondition referenceCondition,
	gsoap_eml2_3::prodml22__ReservoirFluidKind reservoirFluidKind,
	double gasOilRatio, gsoap_eml2_3::eml23__VolumePerVolumeUom gasOilRatioUom)
{
	if (repo == nullptr) {
		throw invalid_argument("A repo must exist.");
	}

	gsoapProxy2_3 = soap_new_prodml22__FluidSystem(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	prodml22__FluidSystem* fs = static_cast<prodml22__FluidSystem*>(gsoapProxy2_3);

	fs->StandardConditions = soap_new_eml23__ReferenceTemperaturePressure(repo->getGsoapContext());
	static_cast<eml23__ReferenceTemperaturePressure*>(fs->StandardConditions)->ReferenceTempPres = soap_eml23__ReferenceCondition2s(repo->getGsoapContext(), referenceCondition);

	fs->ReservoirFluidKind = reservoirFluidKind;

	fs->SolutionGOR = soap_new_eml23__VolumePerVolumeMeasure(repo->getGsoapContext());
	fs->SolutionGOR->__item = gasOilRatio;
	fs->SolutionGOR->uom = gsoap_eml2_3::soap_eml23__VolumePerVolumeUom2s(repo->getGsoapContext(), gasOilRatioUom);

	repo->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
}

SETTER_OPTIONAL_ATTRIBUTE_IMPL(FluidSystem, gsoap_eml2_3::prodml22__FluidSystem, gsoapProxy2_3, PhasesPresent, gsoap_eml2_3::prodml22__PhasePresent, soap_new_prodml22__PhasePresent)
SETTER_OPTIONAL_ATTRIBUTE_IMPL(FluidSystem, ::prodml22__FluidSystem, gsoapProxy2_3, ReservoirLifeCycleState, gsoap_eml2_3::prodml22__ReservoirLifeCycleState, soap_new_prodml22__ReservoirLifeCycleState)
SETTER_OPTIONAL_ATTRIBUTE_IMPL(FluidSystem, gsoap_eml2_3::prodml22__FluidSystem, gsoapProxy2_3, Remark, std::string, soap_new_std__string)

double FluidSystem::getStandardTemperatureValue() const
{
	prodml22__FluidSystem* fs = static_cast<prodml22__FluidSystem*>(gsoapProxy2_3);
	if (fs->StandardConditions->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__TemperaturePressure) {
		return static_cast<eml23__TemperaturePressure*>(fs->StandardConditions)->Temperature->__item;
	}

	throw logic_error("Unrecognized datatype for StandardConditions.");
}

gsoap_eml2_3::eml23__ThermodynamicTemperatureUom FluidSystem::getStandardTemperatureUom() const
{
	prodml22__FluidSystem* fs = static_cast<prodml22__FluidSystem*>(gsoapProxy2_3);
	if (fs->StandardConditions->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__TemperaturePressure) {
		return static_cast<eml23__TemperaturePressure*>(fs->StandardConditions)->Temperature->uom;
	}

	throw logic_error("Unrecognized datatype for StandardConditions.");
}

double FluidSystem::getStandardPressureValue() const
{
	prodml22__FluidSystem* fs = static_cast<prodml22__FluidSystem*>(gsoapProxy2_3);
	if (fs->StandardConditions->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__TemperaturePressure) {
		return static_cast<eml23__TemperaturePressure*>(fs->StandardConditions)->Pressure->__item;
	}

	throw logic_error("Unrecognized datatype for StandardConditions.");
}

gsoap_eml2_3::eml23__PressureUom FluidSystem::getStandardPressureUom() const
{
	prodml22__FluidSystem* fs = static_cast<prodml22__FluidSystem*>(gsoapProxy2_3);
	if (fs->StandardConditions->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__TemperaturePressure) {
		gsoap_eml2_3::eml23__PressureUom result;
		int conversion = soap_s2eml23__PressureUom(getGsoapContext(), static_cast<eml23__TemperaturePressure*>(fs->StandardConditions)->Pressure->uom.c_str(), &result);
		if (conversion != SOAP_OK) {
			throw invalid_argument("The pressure uom " + static_cast<eml23__TemperaturePressure*>(fs->StandardConditions)->Pressure->uom + " is not recognized yet");
		}
		return result;
	}

	throw logic_error("Unrecognized datatype for StandardConditions.");
}

double FluidSystem::getSolutionGORValue() const {
	return static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->SolutionGOR->__item;
}

gsoap_eml2_3::eml23__VolumePerVolumeUom FluidSystem::getSolutionGORUom() const
{
	gsoap_eml2_3::eml23__VolumePerVolumeUom result;
	if (gsoap_eml2_3::soap_s2eml23__VolumePerVolumeUom(getGsoapContext(), static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->SolutionGOR->uom.c_str(), &result) == SOAP_OK) {
		return result;
	}
	throw logic_error("Cannot recognize the exotic volume per volume uom : " + static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->SolutionGOR->uom);
}

void FluidSystem::setSaturationPressure(double value, gsoap_eml2_3::eml23__PressureUom pressureUom, gsoap_eml2_3::prodml22__SaturationPointKind saturationPointKind)
{
	prodml22__FluidSystem* fs = static_cast<prodml22__FluidSystem*>(gsoapProxy2_3);
	if (fs->SaturationPressure == nullptr) {
		fs->SaturationPressure = soap_new_prodml22__SaturationPressure(getGsoapContext());
	}
	fs->SaturationPressure->kind = saturationPointKind;
	fs->SaturationPressure->uom = soap_eml23__PressureUom2s(getGsoapContext(), pressureUom);
	fs->SaturationPressure->__item = value;
}

bool FluidSystem::hasSaturationPressureValue() const
{
	return static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->SaturationPressure != nullptr;
}

double FluidSystem::getSaturationPressureValue() const
{
	if (!hasSaturationPressureValue()) {
		throw logic_error("There is no saturation pressure value");
	}
	return static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->SaturationPressure->__item;
}

 gsoap_eml2_3::eml23__PressureUom FluidSystem::getSaturationPressureUom() const
 {
	 if (!hasSaturationPressureValue()) {
		 throw logic_error("There is no saturation pressure value");
	 }
	 string uomStr = static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->SaturationPressure->uom;
	 gsoap_eml2_3::eml23__PressureUom result;
	 if (gsoap_eml2_3::soap_s2eml23__PressureUom(getGsoapContext(), uomStr.c_str(), &result) == SOAP_OK) {
		 return result;
	 }
	 throw logic_error("The exotic saturation pressure uom is not recognized : " + uomStr);
 }

gsoap_eml2_3::prodml22__SaturationPointKind FluidSystem::getSaturationPressurePointKind() const
{
	if (!hasSaturationPressureValue()) {
		throw logic_error("There is no saturation pressure value");
	}
	return static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->SaturationPressure->kind;
}

#define SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE_IMPL(componentName, attributeName, attributeDatatype, constructor)\
void FluidSystem::set##componentName##attributeName(const attributeDatatype& value)\
{\
	if (static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->componentName == nullptr) {\
		static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->componentName = soap_new_prodml22__##componentName(getGsoapContext());\
		static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->componentName->uid = "0";\
	}\
	static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->componentName->attributeName = constructor(getGsoapContext());\
	*static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->componentName->attributeName = value;\
}

#define SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(componentName, attributeName, uomDatatype, constructor)\
void FluidSystem::set##componentName##attributeName( double value, uomDatatype uom)\
{\
	if (static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->componentName == nullptr) {\
		static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->componentName = soap_new_prodml22__##componentName(getGsoapContext());\
		static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->componentName->uid = "0";\
	}\
	static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->componentName->attributeName = constructor(getGsoapContext());\
	static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->componentName->attributeName->__item = value;\
	static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->componentName->attributeName->uom = uom;\
}

#define SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES_IMPL(componentName)\
SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE_IMPL(componentName, Remark, std::string, soap_new_std__string)\
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(componentName, MassFraction, eml23__MassPerMassUom, soap_new_eml23__MassPerMassMeasure)\
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(componentName, MoleFraction, eml23__AmountOfSubstancePerAmountOfSubstanceUom, soap_new_eml23__AmountOfSubstancePerAmountOfSubstanceMeasure)

SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES_IMPL(FormationWater)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(FormationWater, Salinity, gsoap_eml2_3::eml23__MassPerMassUom, gsoap_eml2_3::soap_new_eml23__MassPerMassMeasure)
SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE_IMPL(FormationWater, SpecificGravity, double, soap_new_double)

SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES_IMPL(StockTankOil)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(StockTankOil, APIGravity, gsoap_eml2_3::eml23__APIGravityUom, gsoap_eml2_3::soap_new_eml23__APIGravityMeasure)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(StockTankOil, MolecularWeight, gsoap_eml2_3::eml23__MolecularWeightUom, gsoap_eml2_3::soap_new_eml23__MolecularWeightMeasure)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(StockTankOil, GrossEnergyContentPerUnitMass, gsoap_eml2_3::eml23__EnergyPerMassUom, gsoap_eml2_3::soap_new_eml23__EnergyPerMassMeasure)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(StockTankOil, NetEnergyContentPerUnitMass, gsoap_eml2_3::eml23__EnergyPerMassUom, gsoap_eml2_3::soap_new_eml23__EnergyPerMassMeasure)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(StockTankOil, GrossEnergyContentPerUnitVolume, gsoap_eml2_3::eml23__EnergyPerVolumeUom, gsoap_eml2_3::soap_new_eml23__EnergyPerVolumeMeasure)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(StockTankOil, NetEnergyContentPerUnitVolume, gsoap_eml2_3::eml23__EnergyPerVolumeUom, gsoap_eml2_3::soap_new_eml23__EnergyPerVolumeMeasure)

SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES_IMPL(NaturalGas)
SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE_IMPL(NaturalGas, GasGravity, double, soap_new_double)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(NaturalGas, MolecularWeight, gsoap_eml2_3::eml23__MolecularWeightUom, gsoap_eml2_3::soap_new_eml23__MolecularWeightMeasure)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(NaturalGas, GrossEnergyContentPerUnitMass, gsoap_eml2_3::eml23__EnergyPerMassUom, gsoap_eml2_3::soap_new_eml23__EnergyPerMassMeasure)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(NaturalGas, NetEnergyContentPerUnitMass, gsoap_eml2_3::eml23__EnergyPerMassUom, gsoap_eml2_3::soap_new_eml23__EnergyPerMassMeasure)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(NaturalGas, GrossEnergyContentPerUnitVolume, gsoap_eml2_3::eml23__EnergyPerVolumeUom, gsoap_eml2_3::soap_new_eml23__EnergyPerVolumeMeasure)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(NaturalGas, NetEnergyContentPerUnitVolume, gsoap_eml2_3::eml23__EnergyPerVolumeUom, gsoap_eml2_3::soap_new_eml23__EnergyPerVolumeMeasure)

void FluidSystem::setRockFluidOrganization(RESQML2_NS::RockFluidOrganizationInterpretation* rockFluidOrg)
{
	if (rockFluidOrg == nullptr) {
		throw std::invalid_argument("Cannot set a null rockFluidOrg");
	}
	if (static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->RockFluidOrganizationInterpretation != nullptr) {
		throw std::logic_error("A rock Fluid organization is already set for this fluid system.");
	}
	static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->RockFluidOrganizationInterpretation = rockFluidOrg->newEml23Reference();

	getRepository()->addRelationship(this, rockFluidOrg);
}

COMMON_NS::DataObjectReference FluidSystem::getRockFluidOrganizationDor() const
{
	if (static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->RockFluidOrganizationInterpretation == nullptr) {
		return COMMON_NS::DataObjectReference();
	}

	return COMMON_NS::DataObjectReference(static_cast<prodml22__FluidSystem*>(gsoapProxy2_3)->RockFluidOrganizationInterpretation);
}

RESQML2_NS::RockFluidOrganizationInterpretation* FluidSystem::getRockFluidOrganization() const
{
	return getRepository()->getDataObjectByUuid<RESQML2_NS::RockFluidOrganizationInterpretation>(getRockFluidOrganizationDor().getUuid());
}

std::vector<FluidCharacterization *> FluidSystem::getFluidCharacterizationSet() const
{
	return repository->getSourceObjects<FluidCharacterization>(this);
}

uint64_t FluidSystem::getFluidCharacterizationCount() const
{
	return repository->getSourceObjects<FluidCharacterization>(this).size();
}

FluidCharacterization * FluidSystem::getFluidCharacterization(uint64_t index) const
{
	const std::vector<FluidCharacterization*>& fluidCharacterizationSet = getFluidCharacterizationSet();

	if (fluidCharacterizationSet.size() > index) {
		return fluidCharacterizationSet[index];
	}

	throw out_of_range("The Fluid Characterization index you are requesting is out of range.");
}

void FluidSystem::loadTargetRelationships()
{
	COMMON_NS::DataObjectReference dor = getRockFluidOrganizationDor();
	if (!dor.isEmpty()) {
		try {
			RESQML2_NS::RockFluidOrganizationInterpretation* rockFluidOrg = getRepository()->getDataObjectByUuid<RESQML2_NS::RockFluidOrganizationInterpretation>(dor.getUuid());
			if (rockFluidOrg == nullptr) {
				convertDorIntoRel<RESQML2_NS::RockFluidOrganizationInterpretation>(dor);
				rockFluidOrg = getRepository()->getDataObjectByUuid<RESQML2_NS::RockFluidOrganizationInterpretation>(dor.getUuid());
			}
			getRepository()->addRelationship(this, rockFluidOrg);
		}
		// See http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-500-106-0-R-sv2010.html
		// A RockFluidOrganizationInterpretation can gather only one RockFluidUnitInterpretation Index/ geologicUnitInterpretation; it should be multiple (i.e., cardinality is 1..1 but should be 1..*).
		// To address this issue, if more than one RockFluidOrganizationInterpretation is needed, use StratigraphicOccurrenceInterpretations with OrganizationKind attributes set to "fluid".
		catch (...) {
			RESQML2_NS::StratigraphicOccurrenceInterpretation* rockFluidOrg = getRepository()->getDataObjectByUuid<RESQML2_NS::StratigraphicOccurrenceInterpretation>(dor.getUuid());
			if (rockFluidOrg == nullptr) {
				convertDorIntoRel<RESQML2_NS::StratigraphicOccurrenceInterpretation>(dor);
				rockFluidOrg = getRepository()->getDataObjectByUuid<RESQML2_NS::StratigraphicOccurrenceInterpretation>(dor.getUuid());
			}
			getRepository()->addRelationship(this, rockFluidOrg);
		}
	}
}
