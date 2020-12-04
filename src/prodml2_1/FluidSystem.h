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
#pragma once

#include "../common/AbstractObject.h"

#include "../MacroDefinitions.h"

namespace RESQML2_NS
{
	/** A rock fluid unit feature. */
	class RockFluidOrganizationInterpretation;
}

/**
 * A macro that defines getter fluid component attribute
 *
 * @param 	componentName		Name of the component.
 * @param 	attributeName	 	Name of the attribute.
 * @param 	attributeDatatype	The attribute datatype.
 */
#define GETTER_FLUID_COMPONENT_ATTRIBUTE(componentName, attributeName, attributeDatatype)\
	DLL_IMPORT_OR_EXPORT attributeDatatype get##componentName##attributeName() const {\
		if (static_cast<gsoap_eml2_2::prodml21__FluidSystem*>(gsoapProxy2_2)->componentName == nullptr) { throw std::logic_error("The component does not exist"); }\
		return static_cast<gsoap_eml2_2::prodml21__FluidSystem*>(gsoapProxy2_2)->componentName->attributeName;\
	}

 /**
  * A macro that defines getter and setter fluid component optional attribute
  *
  * @param 	componentName		Name of the component.
  * @param 	attributeName	 	Name of the attribute.
  * @param 	attributeDatatype	The attribute datatype.
  */
#define GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(componentName, attributeName, attributeDatatype)\
	DLL_IMPORT_OR_EXPORT void set##componentName##attributeName(const attributeDatatype& value);\
	DLL_IMPORT_OR_EXPORT bool has##componentName##attributeName() const {\
		return	static_cast<gsoap_eml2_2::prodml21__FluidSystem*>(gsoapProxy2_2)->componentName != nullptr &&\
				static_cast<gsoap_eml2_2::prodml21__FluidSystem*>(gsoapProxy2_2)->componentName->attributeName != nullptr;\
	}\
	DLL_IMPORT_OR_EXPORT attributeDatatype get##componentName##attributeName() const {\
		if (!has##componentName##attributeName()) { throw std::logic_error("This attribute in this component attribute does not exist"); }\
		return *static_cast<gsoap_eml2_2::prodml21__FluidSystem*>(gsoapProxy2_2)->componentName->attributeName;\
	}

  /**
   * A macro that defines getter and setter fluid component measure attribute
   *
   * @param 	componentName   Name of the component.
   * @param 	attributeName	Name of the attribute.
   * @param 	uomDatatype  	The uom datatype.
   */
#define GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(componentName, attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT void set##componentName##attributeName(double value, uomDatatype uom);\
	DLL_IMPORT_OR_EXPORT bool has##componentName##attributeName() const {\
		return	static_cast<gsoap_eml2_2::prodml21__FluidSystem*>(gsoapProxy2_2)->componentName != nullptr &&\
				static_cast<gsoap_eml2_2::prodml21__FluidSystem*>(gsoapProxy2_2)->componentName->attributeName != nullptr;\
	}\
	DLL_IMPORT_OR_EXPORT double get##componentName##attributeName##Value() const {\
		if (!has##componentName##attributeName()) { throw std::logic_error("This attribute in this component attribute does not exist"); }\
		return static_cast<gsoap_eml2_2::prodml21__FluidSystem*>(gsoapProxy2_2)->componentName->attributeName->__item;\
	}\
	DLL_IMPORT_OR_EXPORT uomDatatype get##componentName##attributeName##Uom() const {\
		if (!has##componentName##attributeName()) { throw std::logic_error("This attribute in this component attribute does not exist"); }\
		return static_cast<gsoap_eml2_2::prodml21__FluidSystem*>(gsoapProxy2_2)->componentName->attributeName->uom;\
	}

   /**
	* A macro that defines getter and setter fluid component common attributes
	*
	* @param 	componentName	Name of the component.
	*/
#define GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(componentName)\
	DLL_IMPORT_OR_EXPORT bool has##componentName() const {\
		return	static_cast<gsoap_eml2_2::prodml21__FluidSystem*>(gsoapProxy2_2)->componentName != nullptr;\
	}\
	GETTER_FLUID_COMPONENT_ATTRIBUTE(componentName, uid, std::string)\
	GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(componentName, Remark, std::string)\
	GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(componentName, MassFraction, gsoap_eml2_2::eml22__MassPerMassUom)\
	GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(componentName, MoleFraction, gsoap_eml2_2::eml22__AmountOfSubstancePerAmountOfSubstanceUom)


namespace PRODML2_1_NS
{
	/** A fluid system. */
	class FluidSystem : public COMMON_NS::AbstractObject
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT FluidSystem(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>repo == nullptr</tt>.
		 *
		 * @param [in,out]	repo			  	The dataobject repo where the underlying gsoap proxy is
		 * 										going to be created.
		 * @param 		  	guid			  	The guid to set to this instance. If empty then a new
		 * 										guid will be generated.
		 * @param 		  	title			  	The title.
		 * @param 		  	temperatureValue  	The temperature value in standard conditions.
		 * @param 		  	temperatureUom	  	The temperature uom.
		 * @param 		  	pressureValue	  	The pressure value in standard conditions.
		 * @param 		  	pressureUom		  	The pressure uom.
		 * @param 		  	reservoirFluidKind	The reservoir fluid kind.
		 * @param 		  	gasOilRatio		  	The gas oil ratio.
		 * @param 		  	gasOilRatioUom	  	The gas oil ratio uom.
		 */
		FluidSystem(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid,
			const std::string & title,
			double temperatureValue, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom temperatureUom,
			double pressureValue, gsoap_eml2_2::eml22__PressureUom pressureUom,
			gsoap_eml2_2::prodml21__ReservoirFluidKind reservoirFluidKind,
			double gasOilRatio, gsoap_eml2_2::eml22__VolumePerVolumeUom gasOilRatioUom);

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>repo == nullptr</tt>.
		 *
		 * @param [in,out]	repo			  	The dataobject repo where the underlying gsoap proxy is
		 * 										going to be created.
		 * @param 		  	guid			  	The guid to set to this instance. If empty then a new
		 * 										guid will be generated.
		 * @param 		  	title			  	The title.
		 * @param 		  	referenceCondition	A wellknown couple of temperature-pressure in standard conditions.
		 * @param 		  	reservoirFluidKind	The reservoir fluid kind.
		 * @param 		  	gasOilRatio		  	The gas oil ratio.
		 * @param 		  	gasOilRatioUom	  	The gas oil ratio uom.
		 */
		FluidSystem(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_2::eml22__ReferenceCondition referenceCondition,
			gsoap_eml2_2::prodml21__ReservoirFluidKind reservoirFluidKind,
			double gasOilRatio, gsoap_eml2_2::eml22__VolumePerVolumeUom gasOilRatioUom);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		FluidSystem(gsoap_eml2_2::prodml21__FluidSystem* fromGsoap):AbstractObject(fromGsoap)  {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~FluidSystem() = default;
		
		GETTER_SETTER_ATTRIBUTE(gsoap_eml2_2::prodml21__FluidSystem, gsoapProxy2_2, ReservoirFluidKind, gsoap_eml2_2::prodml21__ReservoirFluidKind)

		GETTER_SETTER_OPTIONAL_ATTRIBUTE(gsoap_eml2_2::prodml21__FluidSystem, gsoapProxy2_2, PhasesPresent, gsoap_eml2_2::prodml21__PhasePresent)
		GETTER_SETTER_OPTIONAL_ATTRIBUTE(gsoap_eml2_2::prodml21__FluidSystem, gsoapProxy2_2, ReservoirLifeCycleState, gsoap_eml2_2::prodml21__ReservoirLifeCycleState)
		GETTER_SETTER_OPTIONAL_ATTRIBUTE(gsoap_eml2_2::prodml21__FluidSystem, gsoapProxy2_2, Remark, std::string)

		/**
		 * Gets standard temperature value
		 *
		 * @returns	The standard temperature value.
		 */
		DLL_IMPORT_OR_EXPORT double getStandardTemperatureValue() const;

		/**
		 * Gets standard temperature uom
		 *
		 * @returns	The standard temperature uom.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_2::eml22__ThermodynamicTemperatureUom getStandardTemperatureUom() const;

		/**
		 * Gets standard pressure value
		 *
		 * @returns	The standard pressure value.
		 */
		DLL_IMPORT_OR_EXPORT double getStandardPressureValue() const;

		/**
		 * Gets standard pressure uom
		 *
		 * @returns	The standard pressure uom.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_2::eml22__PressureUom getStandardPressureUom() const;

		/**
		 * Gets solution gas-oil ratio value
		 *
		 * @returns	The solution gas-oil ratio value.
		 */
		DLL_IMPORT_OR_EXPORT double getSolutionGORValue() const;

		/**
		 * Gets solution gas-oil ratio uom
		 *
		 * @returns	The solution gas-oil ratio uom.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_2::eml22__VolumePerVolumeUom getSolutionGORUom() const;

		/**
		 * Sets the saturation pressure of this fluid system
		 */
		DLL_IMPORT_OR_EXPORT void setSaturationPressure(double value, gsoap_eml2_2::eml22__PressureUom pressureUom, gsoap_eml2_2::prodml21__SaturationPointKind saturationPointKind);

		/**
		 * Checks if this fluid system has a defined saturation pressure
		 *
		 * @returns	True if this fluid system has a defined saturation pressure else false.
		 */
		DLL_IMPORT_OR_EXPORT bool hasSaturationPressureValue() const;

		/**
		 * Gets the saturation pressure of this fluid system
		 *
		 * @returns	The saturation pressure of this fluid system.
		 */
		DLL_IMPORT_OR_EXPORT double getSaturationPressureValue() const;

		/**
		 * Gets the saturation pressure uom of this fluid system
		 *
		 * @returns	The saturation pressure uom of this fluid system.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_2::eml22__PressureUom getSaturationPressureUom() const;

		/**
		 * Gets the saturation pressure point kind of this fluid system
		 *
		 * @returns	The saturation pressure point kind of this fluid system.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_2::prodml21__SaturationPointKind getSaturationPressurePointKind() const;

		/**
		 * Formation water
		 */
		GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(FormationWater)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(FormationWater, Salinity, gsoap_eml2_2::eml22__MassPerMassUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(FormationWater, SpecificGravity, double)

		/**
		 * Stock tank oil
		 */
		GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(StockTankOil)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, APIGravity, gsoap_eml2_2::eml22__APIGravityUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, MolecularWeight, gsoap_eml2_2::eml22__MolecularWeightUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, GrossEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, NetEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, GrossEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, NetEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom)

		/**
		 * Natural gas
		 */
		GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(NaturalGas)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(NaturalGas, GasGravity, double)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, MolecularWeight, gsoap_eml2_2::eml22__MolecularWeightUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, GrossEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, NetEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, GrossEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, NetEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom)

		/**
		* Sets the associated Rock fluid organization
		*
		* @param [in,out]	rockFluidUnit	If non-null, the rock fluid unit.
		*/
		DLL_IMPORT_OR_EXPORT void setRockFluidOrganization(RESQML2_NS::RockFluidOrganizationInterpretation* rockFluidOrg);

		/**
		 * Gets the associated Rock fluid organization dor
		 *
		 * @returns	Empty if it fails, else the associated Rock fluid organization dor.
		 */
		COMMON_NS::DataObjectReference getRockFluidOrganizationDor() const;

		/**
		 * Gets the associated Rock fluid organization
		 *
		 * @returns	Null if it fails, else the associated Rock fluid organization.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::RockFluidOrganizationInterpretation* getRockFluidOrganization() const;

		/**
		 * Gets all the fluid characterizations of this fluid system.
		 *
		 * @returns	A vector of all the fluid characterizations of this fluid system.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<class FluidCharacterization *> getFluidCharacterizationSet() const;

		/**
		 * Get the fluid characterizations count of this fluid system.
		 *
		 * @returns	The fluid characterizations count of this fluid system.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getFluidCharacterizationCount() const;

		/**
		 * Gets a particular fluid characterization of this fluid system according to its position in the
		 * fluid characterizations ordering.
		 *
		 * @exception	std::out_of_range	If @p index is out of the range of the representation set.
		 *
		 * @param 	index	Zero-based index of the fluid characterization we look for.
		 *
		 * @returns	A pointer to the fluid characterization at @p index.
		 */
		DLL_IMPORT_OR_EXPORT class FluidCharacterization * getFluidCharacterization(uint64_t index) const;

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

		/** Loads target relationships */
		void loadTargetRelationships() final;
	};
}
