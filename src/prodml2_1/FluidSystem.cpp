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

using namespace std;
using namespace PRODML2_1_NS;
using namespace gsoap_eml2_2;
using namespace COMMON_NS;

const char* FluidSystem::XML_TAG = "FluidSystem";
const char* FluidSystem::XML_NS = "prodml21";

FluidSystem::FluidSystem(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid,
	const std::string & title,
	double temperatureValue, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom temperatureUom,
	double pressureValue, gsoap_eml2_2::eml22__PressureUom pressureUom,
	gsoap_eml2_2::prodml21__ReservoirFluidKind reservoirFluidKind,
	double gasOilRatio, gsoap_eml2_2::eml22__VolumePerVolumeUom gasOilRatioUom)
{
	if (repo == nullptr) {
		throw invalid_argument("A repo must exist.");
	}

	gsoapProxy2_2 = soap_new_prodml21__FluidSystem(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	prodml21__FluidSystem* fs = static_cast<prodml21__FluidSystem*>(gsoapProxy2_2);

	fs->StandardConditions = soap_new_eml22__TemperaturePressure(repo->getGsoapContext());
	static_cast<eml22__TemperaturePressure*>(fs->StandardConditions)->Temperature = soap_new_eml22__ThermodynamicTemperatureMeasure(repo->getGsoapContext());
	static_cast<eml22__TemperaturePressure*>(fs->StandardConditions)->Temperature->__item = temperatureValue;
	static_cast<eml22__TemperaturePressure*>(fs->StandardConditions)->Temperature->uom = temperatureUom;
	static_cast<eml22__TemperaturePressure*>(fs->StandardConditions)->Pressure = soap_new_eml22__PressureMeasure(repo->getGsoapContext());
	static_cast<eml22__TemperaturePressure*>(fs->StandardConditions)->Pressure->__item = pressureValue;
	static_cast<eml22__TemperaturePressure*>(fs->StandardConditions)->Pressure->uom = gsoap_eml2_2::soap_eml22__PressureUom2s(repo->getGsoapContext(), pressureUom);

	fs->ReservoirFluidKind = reservoirFluidKind;

	fs->SolutionGOR = soap_new_eml22__VolumePerVolumeMeasure(repo->getGsoapContext());
	fs->SolutionGOR->__item = gasOilRatio;
	fs->SolutionGOR->uom = gsoap_eml2_2::soap_eml22__VolumePerVolumeUom2s(repo->getGsoapContext(), gasOilRatioUom);

	repo->addOrReplaceDataObject(this);
}

FluidSystem::FluidSystem(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid,
	const std::string & title,
	gsoap_eml2_2::eml22__ReferenceCondition referenceCondition,
	gsoap_eml2_2::prodml21__ReservoirFluidKind reservoirFluidKind,
	double gasOilRatio, gsoap_eml2_2::eml22__VolumePerVolumeUom gasOilRatioUom)
{
	if (repo == nullptr) {
		throw invalid_argument("A repo must exist.");
	}

	gsoapProxy2_2 = soap_new_prodml21__FluidSystem(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	prodml21__FluidSystem* fs = static_cast<prodml21__FluidSystem*>(gsoapProxy2_2);

	fs->StandardConditions = soap_new_eml22__ReferenceTemperaturePressure(repo->getGsoapContext());
	static_cast<eml22__ReferenceTemperaturePressure*>(fs->StandardConditions)->__union_ReferenceTemperaturePressure_ = SOAP_UNION_gsoap_eml2_2__eml22__union_ReferenceTemperaturePressure__ReferenceTempPres;
	static_cast<eml22__ReferenceTemperaturePressure*>(fs->StandardConditions)->union_ReferenceTemperaturePressure_.ReferenceTempPres = soap_new_std__string(repo->getGsoapContext());
	static_cast<eml22__ReferenceTemperaturePressure*>(fs->StandardConditions)->union_ReferenceTemperaturePressure_.ReferenceTempPres->assign(soap_eml22__ReferenceCondition2s(repo->getGsoapContext(), referenceCondition));

	fs->ReservoirFluidKind = reservoirFluidKind;

	fs->SolutionGOR = soap_new_eml22__VolumePerVolumeMeasure(repo->getGsoapContext());
	fs->SolutionGOR->__item = gasOilRatio;
	fs->SolutionGOR->uom = gsoap_eml2_2::soap_eml22__VolumePerVolumeUom2s(repo->getGsoapContext(), gasOilRatioUom);

	repo->addOrReplaceDataObject(this);
}

SETTER_OPTIONAL_ATTRIBUTE_IMPL(FluidSystem, gsoap_eml2_2::prodml21__FluidSystem, gsoapProxy2_2, PhasesPresent, gsoap_eml2_2::prodml21__PhasePresent, soap_new_prodml21__PhasePresent)
SETTER_OPTIONAL_ATTRIBUTE_IMPL(FluidSystem, ::prodml21__FluidSystem, gsoapProxy2_2, ReservoirLifeCycleState, gsoap_eml2_2::prodml21__ReservoirLifeCycleState, soap_new_prodml21__ReservoirLifeCycleState)
SETTER_OPTIONAL_ATTRIBUTE_IMPL(FluidSystem, gsoap_eml2_2::prodml21__FluidSystem, gsoapProxy2_2, Remark, std::string, soap_new_std__string)

double FluidSystem::getStandardTemperatureValue() const
{
	prodml21__FluidSystem* fs = static_cast<prodml21__FluidSystem*>(gsoapProxy2_2);
	if (fs->StandardConditions->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__TemperaturePressure) {
		return static_cast<eml22__TemperaturePressure*>(fs->StandardConditions)->Temperature->__item;
	}
	else if (fs->StandardConditions->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__ReferenceTemperaturePressure) {
		istringstream iss(*static_cast<eml22__ReferenceTemperaturePressure*>(fs->StandardConditions)->union_ReferenceTemperaturePressure_.ReferenceTempPres);
		int result;
		iss >> result;
		return result;
	}

	throw logic_error("Unrecognized datatype for StandardConditions.");
}

gsoap_eml2_2::eml22__ThermodynamicTemperatureUom FluidSystem::getStandardTemperatureUom() const
{
	prodml21__FluidSystem* fs = static_cast<prodml21__FluidSystem*>(gsoapProxy2_2);
	if (fs->StandardConditions->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__TemperaturePressure) {
		return static_cast<eml22__TemperaturePressure*>(fs->StandardConditions)->Temperature->uom;
	}
	else if (fs->StandardConditions->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__ReferenceTemperaturePressure) {
		const std::string str = *static_cast<eml22__ReferenceTemperaturePressure*>(fs->StandardConditions)->union_ReferenceTemperaturePressure_.ReferenceTempPres;
		if (str.find("degC") != std::string::npos) return gsoap_eml2_2::eml22__ThermodynamicTemperatureUom::degC;
		if (str.find("degF") != std::string::npos) return gsoap_eml2_2::eml22__ThermodynamicTemperatureUom::degF;
		throw logic_error("Unrecognized temperature uom in " + str);
	}

	throw logic_error("Unrecognized datatype for StandardConditions.");
}

double FluidSystem::getStandardPressureValue() const
{
	prodml21__FluidSystem* fs = static_cast<prodml21__FluidSystem*>(gsoapProxy2_2);
	if (fs->StandardConditions->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__TemperaturePressure) {
		return static_cast<eml22__TemperaturePressure*>(fs->StandardConditions)->Pressure->__item;
	}
	else if (fs->StandardConditions->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__ReferenceTemperaturePressure) {
		const std::string str = *static_cast<eml22__ReferenceTemperaturePressure*>(fs->StandardConditions)->union_ReferenceTemperaturePressure_.ReferenceTempPres;
		istringstream iss(str);
		int tempValue;
		iss >> tempValue;
		std::string  tempUom;
		iss >> tempUom;
		int pressureValue;
		iss >> pressureValue;
		return pressureValue;
	}

	throw logic_error("Unrecognized datatype for StandardConditions.");
}

gsoap_eml2_2::eml22__PressureUom FluidSystem::getStandardPressureUom() const
{
	prodml21__FluidSystem* fs = static_cast<prodml21__FluidSystem*>(gsoapProxy2_2);
	if (fs->StandardConditions->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__TemperaturePressure) {
		gsoap_eml2_2::eml22__PressureUom result;
		int conversion = soap_s2eml22__PressureUom(getGsoapContext(), static_cast<eml22__TemperaturePressure*>(fs->StandardConditions)->Pressure->uom.c_str(), &result);
		if (conversion != SOAP_OK) {
			throw invalid_argument("The pressure uom " + static_cast<eml22__TemperaturePressure*>(fs->StandardConditions)->Pressure->uom + " is not recognized yet");
		}
		return result;
	}
	else if (fs->StandardConditions->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__ReferenceTemperaturePressure) {
		const std::string str = *static_cast<eml22__ReferenceTemperaturePressure*>(fs->StandardConditions)->union_ReferenceTemperaturePressure_.ReferenceTempPres;
		if (str.find("bar") != std::string::npos) return gsoap_eml2_2::eml22__PressureUom::bar;
		if (str.find("atm") != std::string::npos) return gsoap_eml2_2::eml22__PressureUom::atm;
		if (str.find("Hg") != std::string::npos) return gsoap_eml2_2::eml22__PressureUom::inHg_x005b60degF_x005d;
		throw logic_error("Unrecognized pressure uom in " + str);
	}

	throw logic_error("Unrecognized datatype for StandardConditions.");
}

double FluidSystem::getSolutionGORValue() const {
	return static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->SolutionGOR->__item;
}

gsoap_eml2_2::eml22__VolumePerVolumeUom FluidSystem::getSolutionGORUom() const
{
	gsoap_eml2_2::eml22__VolumePerVolumeUom result;
	if (gsoap_eml2_2::soap_s2eml22__VolumePerVolumeUom(getGsoapContext(), static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->SolutionGOR->uom.c_str(), &result) == SOAP_OK) {
		return result;
	}
	throw logic_error("Cannot recognize the exotic volume per volume uom : " + static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->SolutionGOR->uom);
}

void FluidSystem::setSaturationPressure(double value, gsoap_eml2_2::eml22__PressureUom pressureUom, gsoap_eml2_2::prodml21__SaturationPointKind saturationPointKind)
{
	prodml21__FluidSystem* fs = static_cast<prodml21__FluidSystem*>(gsoapProxy2_2);
	if (fs->SaturationPressure == nullptr) {
		fs->SaturationPressure = soap_new_prodml21__SaturationPressure(getGsoapContext());
	}
	fs->SaturationPressure->kind = saturationPointKind;
	fs->SaturationPressure->uom = soap_eml22__PressureUom2s(getGsoapContext(), pressureUom);
	fs->SaturationPressure->__item = value;
}

bool FluidSystem::hasSaturationPressureValue() const
{
	return static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->SaturationPressure != nullptr;
}

double FluidSystem::getSaturationPressureValue() const
{
	if (!hasSaturationPressureValue()) {
		throw logic_error("There is no saturation pressure value");
	}
	return static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->SaturationPressure->__item;
}

 gsoap_eml2_2::eml22__PressureUom FluidSystem::getSaturationPressureUom() const
 {
	 if (!hasSaturationPressureValue()) {
		 throw logic_error("There is no saturation pressure value");
	 }
	 string uomStr = static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->SaturationPressure->uom;
	 gsoap_eml2_2::eml22__PressureUom result;
	 if (gsoap_eml2_2::soap_s2eml22__PressureUom(getGsoapContext(), uomStr.c_str(), &result) == SOAP_OK) {
		 return result;
	 }
	 throw logic_error("The exotic saturation pressure uom is not recognized : " + uomStr);
 }

gsoap_eml2_2::prodml21__SaturationPointKind FluidSystem::getSaturationPressurePointKind() const
{
	if (!hasSaturationPressureValue()) {
		throw logic_error("There is no saturation pressure value");
	}
	return static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->SaturationPressure->kind;
}

#define SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE_IMPL(componentName, attributeName, attributeDatatype, constructor)\
void FluidSystem::set##componentName##attributeName(const attributeDatatype& value)\
{\
	if (static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->componentName == nullptr) {\
		static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->componentName = soap_new_prodml21__##componentName(getGsoapContext());\
		static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->componentName->uid = "0";\
	}\
	static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->componentName->attributeName = constructor(getGsoapContext());\
	*static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->componentName->attributeName = value;\
}

#define SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(componentName, attributeName, uomDatatype, constructor)\
void FluidSystem::set##componentName##attributeName( double value, uomDatatype uom)\
{\
	if (static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->componentName == nullptr) {\
		static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->componentName = soap_new_prodml21__##componentName(getGsoapContext());\
		static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->componentName->uid = "0";\
	}\
	static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->componentName->attributeName = constructor(getGsoapContext());\
	static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->componentName->attributeName->__item = value;\
	static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->componentName->attributeName->uom = uom;\
}

#define SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES_IMPL(componentName)\
SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE_IMPL(componentName, Remark, std::string, soap_new_std__string)\
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(componentName, MassFraction, eml22__MassPerMassUom, soap_new_eml22__MassPerMassMeasure)\
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(componentName, MoleFraction, eml22__AmountOfSubstancePerAmountOfSubstanceUom, soap_new_eml22__AmountOfSubstancePerAmountOfSubstanceMeasure)

SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES_IMPL(FormationWater)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(FormationWater, Salinity, gsoap_eml2_2::eml22__MassPerMassUom, gsoap_eml2_2::soap_new_eml22__MassPerMassMeasure)
SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE_IMPL(FormationWater, SpecificGravity, double, soap_new_double)

SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES_IMPL(StockTankOil)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(StockTankOil, APIGravity, gsoap_eml2_2::eml22__APIGravityUom, gsoap_eml2_2::soap_new_eml22__APIGravityMeasure)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(StockTankOil, MolecularWeight, gsoap_eml2_2::eml22__MolecularWeightUom, gsoap_eml2_2::soap_new_eml22__MolecularWeightMeasure)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(StockTankOil, GrossEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom, gsoap_eml2_2::soap_new_eml22__EnergyPerMassMeasure)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(StockTankOil, NetEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom, gsoap_eml2_2::soap_new_eml22__EnergyPerMassMeasure)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(StockTankOil, GrossEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom, gsoap_eml2_2::soap_new_eml22__EnergyPerVolumeMeasure)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(StockTankOil, NetEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom, gsoap_eml2_2::soap_new_eml22__EnergyPerVolumeMeasure)

SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES_IMPL(NaturalGas)
SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE_IMPL(NaturalGas, GasGravity, double, soap_new_double)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(NaturalGas, MolecularWeight, gsoap_eml2_2::eml22__MolecularWeightUom, gsoap_eml2_2::soap_new_eml22__MolecularWeightMeasure)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(NaturalGas, GrossEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom, gsoap_eml2_2::soap_new_eml22__EnergyPerMassMeasure)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(NaturalGas, NetEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom, gsoap_eml2_2::soap_new_eml22__EnergyPerMassMeasure)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(NaturalGas, GrossEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom, gsoap_eml2_2::soap_new_eml22__EnergyPerVolumeMeasure)
SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE_IMPL(NaturalGas, NetEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom, gsoap_eml2_2::soap_new_eml22__EnergyPerVolumeMeasure)

void FluidSystem::setRockFluidOrganization(RESQML2_NS::RockFluidOrganizationInterpretation* rockFluidOrg)
{
	if (rockFluidOrg == nullptr) {
		throw std::invalid_argument("Cannot set a null rockFluidOrg");
	}
	if (!static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->RockFluidUnitFeature.empty()) {
		throw std::logic_error("A rock Fluid organization is already set for this fluid system.");
	}
	static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->RockFluidUnitFeature.push_back(rockFluidOrg->newEml22Reference());

	getRepository()->addRelationship(this, rockFluidOrg);
}

COMMON_NS::DataObjectReference FluidSystem::getRockFluidOrganizationDor() const
{
	if (static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->RockFluidUnitFeature.empty()) {
		return COMMON_NS::DataObjectReference();
	}
	else if (static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->RockFluidUnitFeature.size() > 1) {
		throw std::logic_error("This fluid system is assocaited to more than one rock Fluid organization. This is not supported.");
	}

	return COMMON_NS::DataObjectReference(static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->RockFluidUnitFeature[0]);
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

	throw out_of_range("The fluid Characterization index you are requesting is out of range.");
}

void FluidSystem::loadTargetRelationships()
{
	COMMON_NS::DataObjectReference dor = getRockFluidOrganizationDor();
	if (!dor.isEmpty()) {
		RESQML2_NS::RockFluidOrganizationInterpretation* rockFluidOrg = getRepository()->getDataObjectByUuid<RESQML2_NS::RockFluidOrganizationInterpretation>(dor.getUuid());
		if (rockFluidOrg == nullptr) {
			convertDorIntoRel<RESQML2_NS::RockFluidOrganizationInterpretation>(dor);
		}
		getRepository()->addRelationship(this, rockFluidOrg);
	}
}
