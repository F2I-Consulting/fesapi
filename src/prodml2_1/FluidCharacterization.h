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

namespace RESQML2_NS
{
	/** A rock fluid unit feature. */
	class RockFluidUnitInterpretation;
}

/**
 * A macro that defines getter fluid component attribute
 *
 * @param 	vectorName		 	Name of the vector.
 * @param 	attributeName	 	Name of the attribute.
 * @param 	attributeDatatype	The attribute datatype.
 */
#define GETTER_FLUID_CATALOG_COMPONENT_ATTRIBUTE(vectorName, attributeName, attributeDatatype)\
	DLL_IMPORT_OR_EXPORT attributeDatatype get##vectorName##attributeName(unsigned int index) const {\
		if (static_cast<gsoap_eml2_2::prodml21__FluidCharacterization*>(gsoapProxy2_2)->FluidComponentCatalog == nullptr ||\
			static_cast<gsoap_eml2_2::prodml21__FluidCharacterization*>(gsoapProxy2_2)->FluidComponentCatalog->vectorName.size() <= index) { throw std::out_of_range("The index is out of range"); }\
		return static_cast<gsoap_eml2_2::prodml21__FluidCharacterization*>(gsoapProxy2_2)->FluidComponentCatalog->vectorName[index]->attributeName;\
	}

/**
 * A macro that defines getter and setter fluid component optional attribute
 *
 * @param 	vectorName		 	Name of the vector.
 * @param 	attributeName	 	Name of the attribute.
 * @param 	attributeDatatype	The attribute datatype.
 */
#define GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_OPTIONAL_ATTRIBUTE(vectorName, attributeName, attributeDatatype)\
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

/**
 * A macro that defines getter and setter fluid component measure attribute
 *
 * @param 	vectorName   	Name of the vector.
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 */
#define GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(vectorName, attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT void set##vectorName##attributeName(unsigned int index, double value, uomDatatype uom);\
	DLL_IMPORT_OR_EXPORT bool has##vectorName##attributeName(unsigned int index) const {\
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

/**
 * A macro that defines getter and setter fluid component common attributes
 *
 * @param 	vectorName	Name of the vector.
 */
#define GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_COMMON_ATTRIBUTES(vectorName)\
	GETTER_FLUID_CATALOG_COMPONENT_ATTRIBUTE(vectorName, uid, std::string)\
	GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_OPTIONAL_ATTRIBUTE(vectorName, Remark, std::string)\
	GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(vectorName, MassFraction, gsoap_eml2_2::eml22__MassPerMassUom)\
	GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(vectorName, MoleFraction, gsoap_eml2_2::eml22__AmountOfSubstancePerAmountOfSubstanceUom)

namespace PRODML2_1_NS
{
	/**
	 * The fluid characterization data object describes the characteristics and properties of a
	 * fluid sample or fluid system under the conditions expected in a historical or future state.
	 * Three basic formats are available to represent fluid characterization results for delivery to
	 * consumer applications:  
	 * - Model (model kind + parameters)
	 * - Tabular
	 * - Set of Fluid Characterization Parameters
	 */
	class FluidCharacterization : public COMMON_NS::AbstractObject
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT FluidCharacterization(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	repo 	The dataobject repo where the underlying gsoap proxy is going to be
		 * 							created.
		 * @param 		  	guid 	The guid to set to this instance. If empty then a new guid will be
		 * 							generated.
		 * @param 		  	title	The title.
		 */
		FluidCharacterization(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid,
			const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		FluidCharacterization(gsoap_eml2_2::prodml21__FluidCharacterization* fromGsoap):AbstractObject(fromGsoap)  {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~FluidCharacterization() {
			for (size_t i = 0; i < modelSpecifications.size(); ++i) {
				if (modelSpecifications[i] != nullptr) {
					delete modelSpecifications[i];
				}
			}
		}

		GETTER_SETTER_OPTIONAL_ATTRIBUTE(gsoap_eml2_2::prodml21__FluidCharacterization, gsoapProxy2_2, FluidCharacterizationType, std::string)
		GETTER_SETTER_OPTIONAL_ATTRIBUTE(gsoap_eml2_2::prodml21__FluidCharacterization, gsoapProxy2_2, IntendedUsage, std::string)
		GETTER_SETTER_OPTIONAL_ATTRIBUTE(gsoap_eml2_2::prodml21__FluidCharacterization, gsoapProxy2_2, Remark, std::string)

		/**
		 * Sets standard conditions
		 *
		 * @param 	temperatureValue	The temperature value.
		 * @param 	temperatureUom  	The temperature uom.
		 * @param 	pressureValue   	The pressure value.
		 * @param 	pressureUom			The pressure uom.
		 */
		DLL_IMPORT_OR_EXPORT void setStandardConditions(double temperatureValue, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom temperatureUom,
			double pressureValue, gsoap_eml2_2::eml22__PressureUom pressureUom);

		/**
		 * Query if this object has standard conditions
		 *
		 * @returns	True if standard conditions, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasStandardConditions() const;

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
		 * Sets rock fluid unit
		 *
		 * @param [in,out]	rockFluidUnit	If non-null, the rock fluid unit.
		 */
		DLL_IMPORT_OR_EXPORT void setRockFluidUnit(RESQML2_NS::RockFluidUnitInterpretation* rockFluidUnit);

		/**
		 * Gets rock fluid unit dor
		 *
		 * @returns	Empty if it fails, else the rock fluid unit dor.
		 */
		COMMON_NS::DataObjectReference getRockFluidUnitDor() const;

		/**
		 * Gets rock fluid unit
		 *
		 * @returns	Null if it fails, else the rock fluid unit.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::RockFluidUnitInterpretation* getRockFluidUnit() const;

		/**
		 * Gets formation water count
		 *
		 * @returns	The formation water count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getFormationWaterCount() const;

		/**
		 * Pushes a back formation water
		 *
		 * @param 	uid	The UID.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFormationWater(const std::string & uid);
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_COMMON_ATTRIBUTES(FormationWater)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(FormationWater, Salinity, gsoap_eml2_2::eml22__MassPerMassUom)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_OPTIONAL_ATTRIBUTE(FormationWater, SpecificGravity, double)

		/**
		 * Gets pure fluid component count
		 *
		 * @returns	The pure fluid component count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPureFluidComponentCount() const;

		/**
		 * Pushes a back pure fluid component
		 *
		 * @param 	uid			   	The UID.
		 * @param 	kind		   	The kind.
		 * @param 	hydrocarbonFlag	True to hydrocarbon flag.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackPureFluidComponent(const std::string & uid, gsoap_eml2_2::prodml21__PureComponentEnum kind, bool hydrocarbonFlag);
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_COMMON_ATTRIBUTES(PureFluidComponent)
		GETTER_FLUID_CATALOG_COMPONENT_ATTRIBUTE(PureFluidComponent, Kind, std::string)
		GETTER_FLUID_CATALOG_COMPONENT_ATTRIBUTE(PureFluidComponent, HydrocarbonFlag, bool)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(PureFluidComponent, MolecularWeight, gsoap_eml2_2::eml22__MolecularWeightUom)

		/**
		 * Gets plus fluid component count
		 *
		 * @returns	The plus fluid component count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPlusFluidComponentCount() const;

		/**
		 * Pushes a back plus fluid component
		 *
		 * @param 	uid 	The UID.
		 * @param 	kind	The kind.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackPlusFluidComponent(const std::string & uid, gsoap_eml2_2::prodml21__PlusComponentEnum kind);
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_COMMON_ATTRIBUTES(PlusFluidComponent)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_OPTIONAL_ATTRIBUTE(PlusFluidComponent, SpecificGravity, double)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_OPTIONAL_ATTRIBUTE(PlusFluidComponent, StartingCarbonNumber, uint64_t)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(PlusFluidComponent, StartingBoilingPoint, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(PlusFluidComponent, AvgDensity, std::string)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(PlusFluidComponent, AvgMolecularWeight, gsoap_eml2_2::eml22__MolecularWeightUom)

		/**
		 * Gets stock tank oil count
		 *
		 * @returns	The stock tank oil count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getStockTankOilCount() const;

		/**
		 * Pushes a back stock tank oil
		 *
		 * @param 	uid	The UID.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackStockTankOil(const std::string & uid);
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_COMMON_ATTRIBUTES(StockTankOil)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, APIGravity, gsoap_eml2_2::eml22__APIGravityUom)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, MolecularWeight, gsoap_eml2_2::eml22__MolecularWeightUom)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, GrossEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, NetEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, GrossEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(StockTankOil, NetEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom)

		/**
		 * Gets natural gas count
		 *
		 * @returns	The natural gas count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getNaturalGasCount() const;

		/**
		 * Pushes a back natural gas
		 *
		 * @param 	uid	The UID.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackNaturalGas(const std::string & uid);
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_COMMON_ATTRIBUTES(NaturalGas)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_OPTIONAL_ATTRIBUTE(NaturalGas, GasGravity, double)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, MolecularWeight, gsoap_eml2_2::eml22__MolecularWeightUom)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, GrossEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, NetEnergyContentPerUnitMass, gsoap_eml2_2::eml22__EnergyPerMassUom)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, GrossEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(NaturalGas, NetEnergyContentPerUnitVolume, gsoap_eml2_2::eml22__EnergyPerVolumeUom)

		/**
		 * Gets pseudo fluid component count
		 *
		 * @returns	The pseudo fluid component count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPseudoFluidComponentCount() const;

		/**
		 * Pushes a back pseudo fluid component
		 *
		 * @param 	uid 	The UID.
		 * @param 	kind	The kind.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackPseudoFluidComponent(const std::string & uid, gsoap_eml2_2::prodml21__PseudoComponentEnum kind);
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_COMMON_ATTRIBUTES(PseudoFluidComponent)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_OPTIONAL_ATTRIBUTE(PseudoFluidComponent, SpecificGravity, double)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_OPTIONAL_ATTRIBUTE(PseudoFluidComponent, StartingCarbonNumber, uint64_t)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_OPTIONAL_ATTRIBUTE(PseudoFluidComponent, EndingCarbonNumber, uint64_t)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, StartingBoilingPoint, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, EndingBoilingPoint, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, AvgBoilingPoint, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, AvgDensity, std::string)
		GETTER_AND_SETTER_FLUID_CATALOG_COMPONENT_MEASURE_ATTRIBUTE(PseudoFluidComponent, AvgMolecularWeight, gsoap_eml2_2::eml22__MolecularWeightUom)

		/** Values that represent model specifications */
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

		/**
		 * Gets model count
		 *
		 * @returns	The model count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getModelCount() const;

		/**
		 * Pushes a back model
		 *
		 * @param 	uid	The UID. If empty, it will be set to its index in this Fluid Characterization
		 */
		DLL_IMPORT_OR_EXPORT void pushBackModel(const std::string & uid = "");

		/**
		 * Gets model specification
		 *
		 * @param 	modelIndex	Zero-based index of the model.
		 *
		 * @returns	Null if it fails, else the model specification.
		 */
		DLL_IMPORT_OR_EXPORT PvtSpecification* getModelSpecification(unsigned int modelIndex) { return modelSpecifications[modelIndex]; }

		/**
		 * Return the PvtSpecification according to the kind. Please downcast it and set all attributes
		 * which you want.
		 *
		 * @param 	modelIndex	Zero-based index of the model.
		 * @param 	kind	  	The kind.
		 *
		 * @returns	Null if it fails, else a pointer to a PvtSpecification.
		 */
		DLL_IMPORT_OR_EXPORT PvtSpecification* initModelSpecification(unsigned int modelIndex, ModelSpecification kind);

		GETTER_SETTER_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_2::prodml21__FluidCharacterization, gsoapProxy2_2, FluidCharacterizationModel, Name, std::string)
		GETTER_SETTER_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_2::prodml21__FluidCharacterization, gsoapProxy2_2, FluidCharacterizationModel, Remark, std::string)
		GETTER_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_2::prodml21__FluidCharacterization, gsoapProxy2_2, FluidCharacterizationModel, ReferenceTemperature, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)
		GETTER_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_2::prodml21__FluidCharacterization, gsoapProxy2_2, FluidCharacterizationModel, ReferenceStockTankTemperature, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)

		/**
		 * Gets the table format count
		 *
		 * @returns	The table format count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getTableFormatCount() const;

		/**
		* Pushes a table format
		*
		* @param 	uid	The UID. If empty, it will be set to its index in this Fluid Characterization
		*/
		DLL_IMPORT_OR_EXPORT void pushBackTableFormat(const std::string & uid = "");

		/**
		 * Gets the uom of a table format column
		 *
		 * @param	tableFormatUid	The uid of the table format.
		 * @param	columnIndex		The zero-based index of the column.
		 * @returns	The uom of a table format column
		 */
		DLL_IMPORT_OR_EXPORT std::string getTableFormatColumnUom(const std::string & tableFormatUid, unsigned int columnIndex) const;

		/**
		 * Gets the property kind of a table format column
		 *
		 * @param	tableFormatUid	The uid of the table format.
		 * @param	columnIndex		The zero-based index of the column.
		 * @returns	The property kind of a table format column
		 */
		DLL_IMPORT_OR_EXPORT std::string getTableFormatColumnProperty(const std::string & tableFormatUid, unsigned int columnIndex) const;

		/**
		* Pushes a table format colum
		*
		* @param	tableFormatIndex	Zero-based index of the table format.
		* @param 	uom					The uom associated to the values of this column
		* @param	fluidProperty		The property that this column contains
		*/
		DLL_IMPORT_OR_EXPORT void pushBackTableFormatColumn(unsigned int tableFormatIndex, const std::string & uom, gsoap_eml2_2::prodml21__OutputFluidProperty fluidProperty);

		/**
		* Pushes a table format colum
		*
		* @param	tableFormatIndex	Zero-based index of the table format.
		* @param 	uom					The uom associated to the values of this column
		* @param	fluidProperty		The non standard property name that this column contains
		*/
		DLL_IMPORT_OR_EXPORT void pushBackTableFormatColumn(unsigned int tableFormatIndex, const std::string & uom, const std::string & fluidProperty);

		/**
		 * Gets the table count
		 *
		 * @param	modelIndex		Zero-based index of the model in this fluid characterization.
		 * @returns	The table count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getTableCount(unsigned int modelIndex) const;

		/**
		 * Gets the name of a table.
		 *
		 * @param	modelIndex		Zero-based index of the model in this fluid characterization.
		 * @param 	tableIndex		Zero-based index of the table in a model of this fluid characterization.
		 * @returns	The name of a table.
		 */
		DLL_IMPORT_OR_EXPORT std::string getTableName(unsigned int modelIndex, unsigned int tableIndex) const;

		/**
		 * Gets the uid of the table format of a table.
		 *
		 * @param	modelIndex		Zero-based index of the model in this fluid characterization.
		 * @param 	tableIndex		Zero-based index of the table in a model of this fluid characterization.
		 * @returns	The uid of the table format of a table.
		 */
		DLL_IMPORT_OR_EXPORT std::string getTableFormatUid(unsigned int modelIndex, unsigned int tableIndex) const;

		/**
		* Pushes back a table
		*
		* @param	modelIndex		Zero-based index of the model.
		* @param 	name			The name of this table.
		* @param 	tableFormatUid	The UID of the table format this table is using.The table format defines the semantic of the colums and values.
		* @param 	uid				The UID of this table. If empty, it will be set to its index in this Fluid Characterization
		*/
		DLL_IMPORT_OR_EXPORT void pushBackTable(unsigned int modelIndex, const std::string & name, const std::string & tableFormatUid, const std::string & uid = "");

		/**
		 * Gets the table row count
		 *
		 * @param	modelIndex		Zero-based index of the model in this fluid characterization.
		 * @param 	tableIndex		Zero-based index of the table in a model of this fluid characterization.
		 * @returns	The table row count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getTableRowCount(unsigned int modelIndex, unsigned int tableIndex) const;

		/**
		 * Gets the content of a row of a table.
		 *
		 * @param	modelIndex		Zero-based index of the model in this fluid characterization.
		 * @param 	tableIndex		Zero-based index of the table in a model of this fluid characterization.
		 * @param 	rowIndex		Zero-based index of the row of the table in a model of this fluid characterization.
		 * @returns	The content of a row of a table.
		 */
		DLL_IMPORT_OR_EXPORT std::string getTableRowContent(unsigned int modelIndex, unsigned int tableIndex, unsigned int rowIndex) const;

		/**
		* Pushes back a row in a table of a model
		*
		* @param	modelIndex		Zero-based index of the model in this fluid characterization.
		* @param 	tableIndex		Zero-based index of the table in a model of this fluid characterization.
		* @param 	rowContent		The string containing the content of the row in the table.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackTableRow(unsigned int modelIndex, unsigned int tableIndex, const std::string & rowContent);

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
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

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

	private:
		/** The model specifications */
		std::vector<PvtSpecification*> modelSpecifications;
	};
}
