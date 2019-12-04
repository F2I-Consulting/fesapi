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

#include "PvtSpecification.h"

namespace RESQML2_0_1_NS
{
	class RockFluidUnitFeature;
}

#define GETTER_FLUID_COMPONENT_ATTRIBUTE(vectorName, attributeName, attributeDatatype)\
	DLL_IMPORT_OR_EXPORT attributeDatatype get##vectorName##attributeName(unsigned int index) const {\
		if (static_cast<gsoap_eml2_2::prodml21__FluidCharacterization*>(gsoapProxy2_2)->FluidComponentCatalog == nullptr ||\
			static_cast<gsoap_eml2_2::prodml21__FluidCharacterization*>(gsoapProxy2_2)->FluidComponentCatalog->vectorName.size() <= index) { throw std::out_of_range("The index is out of range"); }\
		return static_cast<gsoap_eml2_2::prodml21__FluidCharacterization*>(gsoapProxy2_2)->FluidComponentCatalog->vectorName[index]->attributeName;\
	}

#define GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(vectorName, attributeName, attributeDatatype)\
	DLL_IMPORT_OR_EXPORT void set##vectorName##attributeName(unsigned int index, const attributeDatatype& value);\
	DLL_IMPORT_OR_EXPORT bool has##vectorName##attributeName(unsigned int index) const {\
		return	static_cast<gsoap_eml2_2::prodml21__FluidCharacterization*>(gsoapProxy2_2)->FluidComponentCatalog != nullptr &&\
				static_cast<gsoap_eml2_2::prodml21__FluidCharacterization*>(gsoapProxy2_2)->FluidComponentCatalog->vectorName.size() > index &&\
				static_cast<gsoap_eml2_2::prodml21__FluidCharacterization*>(gsoapProxy2_2)->FluidComponentCatalog->vectorName[index]->attributeName != nullptr;\
	}\
	DLL_IMPORT_OR_EXPORT attributeDatatype get##vectorName##attributeName(unsigned int index) const {\
		if (!has##vectorName##attributeName(index)) { throw std::out_of_range("The index is out of range"); }\
		return *static_cast<gsoap_eml2_2::prodml21__FluidCharacterization*>(gsoapProxy2_2)->FluidComponentCatalog->vectorName[index]->attributeName;\
	}

#define GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(vectorName, attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT void set##vectorName##attributeName(unsigned int index, double value, uomDatatype uom);\
	DLL_IMPORT_OR_EXPORT double has##vectorName##attributeName(unsigned int index) const {\
		return	static_cast<gsoap_eml2_2::prodml21__FluidCharacterization*>(gsoapProxy2_2)->FluidComponentCatalog != nullptr &&\
				static_cast<gsoap_eml2_2::prodml21__FluidCharacterization*>(gsoapProxy2_2)->FluidComponentCatalog->vectorName.size() > index &&\
				static_cast<gsoap_eml2_2::prodml21__FluidCharacterization*>(gsoapProxy2_2)->FluidComponentCatalog->vectorName[index]->attributeName != nullptr;\
	}\
	DLL_IMPORT_OR_EXPORT double get##vectorName##attributeName##Value(unsigned int index) const {\
		if (!has##vectorName##attributeName(index)) { throw std::out_of_range("The index is out of range"); }\
		return static_cast<gsoap_eml2_2::prodml21__FluidCharacterization*>(gsoapProxy2_2)->FluidComponentCatalog->vectorName[index]->attributeName->__item;\
	}\
	DLL_IMPORT_OR_EXPORT uomDatatype get##vectorName##attributeName##Uom(unsigned int index) const {\
		if (!has##vectorName##attributeName(index)) { throw std::out_of_range("The index is out of range"); }\
		return static_cast<gsoap_eml2_2::prodml21__FluidCharacterization*>(gsoapProxy2_2)->FluidComponentCatalog->vectorName[index]->attributeName->uom;\
	}

#define GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(vectorName)\
	GETTER_FLUID_COMPONENT_ATTRIBUTE(vectorName, uid, std::string)\
	GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(vectorName, Remark, std::string)\
	GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(vectorName, MassFraction, gsoap_eml2_2::eml22__MassPerMassUom)\
	GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(vectorName, MoleFraction, gsoap_eml2_2::eml22__AmountOfSubstancePerAmountOfSubstanceUom)

namespace PRODML2_1_NS
{
	/**
	* The fluid characterization data object describes the characteristics and properties of a fluid sample or fluid system under the conditions expected in a historical or future state.
	* Three basic formats are available to represent fluid characterization results for delivery to consumer applications:  
	* - Model (model kind + parameters)
	* - Tabular
	* - Set of Fluid Characterization Parameters 
	*/
	class FluidCharacterization : public COMMON_NS::AbstractObject
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT FluidCharacterization(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param repo	The dataobject repo where the underlying gsoap proxy is going to be created.
		* @param guid	The guid to set to this instance. If empty then a new guid will be generated.
		*/
		FluidCharacterization(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid,
			const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		FluidCharacterization(gsoap_eml2_2::prodml21__FluidCharacterization* fromGsoap):AbstractObject(fromGsoap)  {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~FluidCharacterization() {
			for (unsigned int i = 0; i < modelSpecifications.size(); ++i) {
				if (modelSpecifications[i] != nullptr) {
					delete modelSpecifications[i];
				}
			}
		}

		DLL_IMPORT_OR_EXPORT void setStandardConditions(double temperatureValue, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom temperatureUom,
			double pressureValue, gsoap_eml2_2::eml22__PressureUom pressureUom);

		DLL_IMPORT_OR_EXPORT bool hasStandardConditions() const;

		DLL_IMPORT_OR_EXPORT double getStandardTemperatureValue() const;
		DLL_IMPORT_OR_EXPORT gsoap_eml2_2::eml22__ThermodynamicTemperatureUom getStandardTemperatureUom() const;

		DLL_IMPORT_OR_EXPORT double getStandardPressureValue() const;
		DLL_IMPORT_OR_EXPORT gsoap_eml2_2::eml22__PressureUom getStandardPressureUom() const;

		DLL_IMPORT_OR_EXPORT void setRockFluidUnit(RESQML2_0_1_NS::RockFluidUnitFeature* rockFluidUnit);

		gsoap_eml2_2::eml22__DataObjectReference* getRockFluidUnitDor() const;

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::RockFluidUnitFeature* getRockFluidUnit() const;

		DLL_IMPORT_OR_EXPORT unsigned int getFormationWaterCount() const;
		DLL_IMPORT_OR_EXPORT void pushBackFormationWater(const std::string & uid);
		GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(FormationWater)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(FormationWater, Salinity, gsoap_eml2_2::eml22__MassPerMassUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(FormationWater, SpecificGravity, double)

		DLL_IMPORT_OR_EXPORT unsigned int getPureFluidComponentCount() const;
		DLL_IMPORT_OR_EXPORT void pushBackPureFluidComponent(const std::string & uid, gsoap_eml2_2::prodml21__PureComponentEnum kind, bool hydrocarbonFlag);
		GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(PureFluidComponent)
		GETTER_FLUID_COMPONENT_ATTRIBUTE(PureFluidComponent, Kind, std::string)
		GETTER_FLUID_COMPONENT_ATTRIBUTE(PureFluidComponent, HydrocarbonFlag, bool)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PureFluidComponent, MolecularWeight, gsoap_eml2_2::eml22__MolecularWeightUom)

		DLL_IMPORT_OR_EXPORT unsigned int getPlusFluidComponentCount() const;
		DLL_IMPORT_OR_EXPORT void pushBackPlusFluidComponent(const std::string & uid, gsoap_eml2_2::prodml21__PlusComponentEnum kind);
		GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(PlusFluidComponent)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(PlusFluidComponent, SpecificGravity, double)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(PlusFluidComponent, StartingCarbonNumber, ULONG64)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PlusFluidComponent, StartingBoilingPoint, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PlusFluidComponent, AvgDensity, std::string)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PlusFluidComponent, AvgMolecularWeight, gsoap_eml2_2::eml22__MolecularWeightUom)

		DLL_IMPORT_OR_EXPORT unsigned int getStockTankOilCount() const;
		DLL_IMPORT_OR_EXPORT void pushBackStockTankOil(const std::string & uid);
		GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(StockTankOil)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, APIGravity, gsoap_eml2_2::eml22__APIGravityUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, MolecularWeight, gsoap_eml2_2::eml22__MolecularWeightUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, GrossEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, NetEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, GrossEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, NetEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom)

		DLL_IMPORT_OR_EXPORT unsigned int getNaturalGasCount() const;
		DLL_IMPORT_OR_EXPORT void pushBackNaturalGas(const std::string & uid);
		GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(NaturalGas)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(NaturalGas, GasGravity, double)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, MolecularWeight, gsoap_eml2_2::eml22__MolecularWeightUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, GrossEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, NetEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, GrossEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, NetEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom)

		DLL_IMPORT_OR_EXPORT unsigned int getPseudoFluidComponentCount() const;
		DLL_IMPORT_OR_EXPORT void pushBackPseudoFluidComponent(const std::string & uid, gsoap_eml2_2::prodml21__PseudoComponentEnum kind);
		GETTER_AND_SETTER_FLUID_COMPONENT_COMMON_ATTRIBUTES(PseudoFluidComponent)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(PseudoFluidComponent, SpecificGravity, double)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(PseudoFluidComponent, StartingCarbonNumber, ULONG64)
		GETTER_AND_SETTER_FLUID_COMPONENT_OPTIONAL_ATTRIBUTE(PseudoFluidComponent, EndingCarbonNumber, ULONG64)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, StartingBoilingPoint, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, EndingBoilingPoint, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, AvgBoilingPoint, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, AvgDensity, std::string)
		GETTER_AND_SETTER_FLUID_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, AvgMolecularWeight, gsoap_eml2_2::eml22__MolecularWeightUom)

		enum ModelSpecification {
			CompositionalThermal = 0,
			SrkEos = 1,
			PengRobinson76Eos = 2,
			PengRobinson78Eos = 3,
			LohrenzBrayClarkCorrelation = 4,
			CSPedersen87 = 5,
			CSPedersen84 = 6,
			FrictionTheory = 7,
			CorrelationThermal = 8,
			BergmanSuttonBubblePoint = 9,
			DeGhettoBubblePoint = 10,
			StandingBubblePoint = 11,
			DindorukChristmanBubblePoint = 12,
			PetroskyFarshadBubblePoint = 13
		};

		DLL_IMPORT_OR_EXPORT unsigned int getModelCount() const;
		DLL_IMPORT_OR_EXPORT void pushBackModel(const std::string & uid);

		DLL_IMPORT_OR_EXPORT PvtSpecification* getModelSpecification(unsigned int modelIndex) { return modelSpecifications[modelIndex]; }
		/**
		* Return the PvtSpecification according to the kind. Please downcast it and set all attributes which you want.
		*/
		DLL_IMPORT_OR_EXPORT PvtSpecification* setModelSpecification(unsigned int modelIndex, ModelSpecification kind);

		GETTER_SETTER_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_2::prodml21__FluidCharacterization, gsoapProxy2_2, FluidCharacterizationModel, Name, std::string)
		GETTER_SETTER_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_2::prodml21__FluidCharacterization, gsoapProxy2_2, FluidCharacterizationModel, Remark, std::string)
		GETTER_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_2::prodml21__FluidCharacterization, gsoapProxy2_2, FluidCharacterizationModel, ReferenceTemperature, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)
		GETTER_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_2::prodml21__FluidCharacterization, gsoapProxy2_2, FluidCharacterizationModel, ReferenceStockTankTemperature, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)

		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		* Get the standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

		std::string getXmlNamespace() const { return "prodml21"; }

		void loadTargetRelationships();

	private:
		std::vector<PvtSpecification*> modelSpecifications;
	};
}
