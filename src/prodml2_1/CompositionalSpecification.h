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

#include "PvtSpecification.h"

#include <limits>

/**
 * A macro that defines getter and setter fluid component property optional attribute
 *
 * @param 	vectorName		 	Name of the vector.
 * @param 	attributeName	 	Name of the attribute.
 * @param 	attributeDatatype	The attribute datatype.
 */
#define GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_OPTIONAL_ATTRIBUTE(vectorName, attributeName, attributeDatatype)\
	DLL_IMPORT_OR_EXPORT void set##vectorName##attributeName(unsigned int index, const attributeDatatype& value);\
	DLL_IMPORT_OR_EXPORT bool has##vectorName##attributeName(unsigned int index) const {\
		return	static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet != nullptr &&\
				static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet->vectorName.size() > index &&\
				static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet->vectorName[index]->attributeName != nullptr;\
	}\
	DLL_IMPORT_OR_EXPORT attributeDatatype get##vectorName##attributeName(unsigned int index) const {\
		if (!has##vectorName##attributeName(index)) { throw std::out_of_range("The index is out of range"); }\
		return *static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet->vectorName[index]->attributeName;\
	}

/**
 * A macro that defines getter and setter fluid component property measure attribute
 *
 * @param 	vectorName   	Name of the vector.
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 */
#define GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE(vectorName, attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT void set##vectorName##attributeName(unsigned int index, double value, uomDatatype uom);\
	DLL_IMPORT_OR_EXPORT double has##vectorName##attributeName(unsigned int index) const {\
		return	static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet != nullptr &&\
				static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet->vectorName.size() > index &&\
				static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet->vectorName[index]->attributeName != nullptr;\
	}\
	DLL_IMPORT_OR_EXPORT double get##vectorName##attributeName##Value(unsigned int index) const {\
		if (!has##vectorName##attributeName(index)) { throw std::out_of_range("The index is out of range"); }\
		return static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet->vectorName[index]->attributeName->__item;\
	}\
	DLL_IMPORT_OR_EXPORT uomDatatype get##vectorName##attributeName##Uom(unsigned int index) const {\
		if (!has##vectorName##attributeName(index)) { throw std::out_of_range("The index is out of range"); }\
		return static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet->vectorName[index]->attributeName->uom;\
	}

/** . */
namespace PRODML2_1_NS
{
	/** A compositional specification. */
	class CompositionalSpecification : public PvtSpecification
	{
	public:

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		CompositionalSpecification(gsoap_eml2_2::prodml21__AbstractCompositionalModel* fromGsoap):PvtSpecification(fromGsoap)  {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~CompositionalSpecification() {}

		/**
		 * Query if this object has mixing rule
		 *
		 * @returns	True if mixing rule, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasMixingRule() const { return static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->MixingRule != nullptr; }

		/**
		 * Gets mixing rule
		 *
		 * @exception	std::invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @returns	The mixing rule.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_2::prodml21__MixingRule getMixingRule() const {
			if (!hasMixingRule()) { throw std::invalid_argument("There is no mixing rule to get"); }
			return *static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->MixingRule;
		}

		/**
		 * Sets mixing rule
		 *
		 * @param 	mixingRule	The mixing rule.
		 */
		DLL_IMPORT_OR_EXPORT void setMixingRule(gsoap_eml2_2::prodml21__MixingRule mixingRule);

		/**
		 * Gets binary interaction coefficient count
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @returns	The binary interaction coefficient count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getBinaryInteractionCoefficientCount() const {
			if (static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->BinaryInteractionCoefficientSet == nullptr) {
				return 0;
			}

			size_t count = static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->BinaryInteractionCoefficientSet->BinaryInteractionCoefficient.size();
			if (count > (std::numeric_limits<unsigned int>::max)()) {
				throw std::out_of_range("There are too much coefficient");
			}
			return static_cast<unsigned int>(count);
		}

		/**
		 * Gets binary interaction coefficient fluid component 1 reference
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The binary interaction coefficient fluid component 1 reference.
		 */
		DLL_IMPORT_OR_EXPORT std::string getBinaryInteractionCoefficientFluidComponent1Reference(unsigned int index) const
		{
			if (index >= getBinaryInteractionCoefficientCount()) {
				throw std::out_of_range("The index is out of range");
			}

			return static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->BinaryInteractionCoefficientSet->BinaryInteractionCoefficient[index]->fluidComponent1Reference;
		}

		/**
		 * Query if 'index' has binary interaction coefficient fluid component 2 reference
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if binary interaction coefficient fluid component 2 reference, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasBinaryInteractionCoefficientFluidComponent2Reference(unsigned int index) const
		{
			if (index >= getBinaryInteractionCoefficientCount()) {
				throw std::out_of_range("The index is out of range");
			}

			return static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->BinaryInteractionCoefficientSet->BinaryInteractionCoefficient[index]->fluidComponent2Reference != nullptr;
		}

		/**
		 * Gets binary interaction coefficient fluid component 2 reference
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The binary interaction coefficient fluid component 2 reference.
		 */
		DLL_IMPORT_OR_EXPORT std::string getBinaryInteractionCoefficientFluidComponent2Reference(unsigned int index) const
		{
			if (!hasBinaryInteractionCoefficientFluidComponent2Reference(index)) {
				throw std::out_of_range("There is no FluidComponent2Reference at this index");
			}

			return *static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->BinaryInteractionCoefficientSet->BinaryInteractionCoefficient[index]->fluidComponent2Reference;
		}

		/**
		 * Pushes a back binary interaction coefficient
		 *
		 * @param 	value						The value.
		 * @param 	fluidComponent1Reference	The fluid component 1 reference.
		 * @param 	fluidComponent2Reference	(Optional) The fluid component 2 reference.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackBinaryInteractionCoefficient(double value, const std::string & fluidComponent1Reference, const std::string & fluidComponent2Reference = "");

		/**
		 * Gets fluid component property count
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @returns	The fluid component property count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getFluidComponentPropertyCount() const {
			if (static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet == nullptr) {
				return 0;
			}

			size_t count = static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet->FluidComponentProperty.size();
			if (count > (std::numeric_limits<unsigned int>::max)()) {
				throw std::out_of_range("There are too much component property");
			}
			return static_cast<unsigned int>(count);
		}

		/**
		 * Pushes a back fluid component property
		 *
		 * @param 	fluidComponentReference	The fluid component reference.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFluidComponentProperty(const std::string & fluidComponentReference);

		/**
		 * Gets fluid component property fluid component reference
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The fluid component property fluid component reference.
		 */
		DLL_IMPORT_OR_EXPORT std::string getFluidComponentPropertyFluidComponentReference(unsigned int index) const{
			if (static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet == nullptr ||
				static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet->FluidComponentProperty.size() <= index) {
				throw std::out_of_range("The FluidComponentProperty at this index does not exist");
			}

			return static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet->FluidComponentProperty[index]->fluidComponentReference;
		}

		GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_OPTIONAL_ATTRIBUTE(FluidComponentProperty, AcentricFactor, double)
		GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_OPTIONAL_ATTRIBUTE(FluidComponentProperty, OmegaA, double)
		GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_OPTIONAL_ATTRIBUTE(FluidComponentProperty, OmegaB, double)
		GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_OPTIONAL_ATTRIBUTE(FluidComponentProperty, VolumeShiftParameter, double)
		GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_OPTIONAL_ATTRIBUTE(FluidComponentProperty, Parachor, double)
		GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_OPTIONAL_ATTRIBUTE(FluidComponentProperty, Remark, std::string)

		GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE(FluidComponentProperty, CriticalPressure, std::string)
		GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE(FluidComponentProperty, CriticalTemperature, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE(FluidComponentProperty, ReferenceTemperatureZJ, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE(FluidComponentProperty, CriticalViscosity, gsoap_eml2_2::eml22__DynamicViscosityUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE(FluidComponentProperty, CompactVolume, std::string)
		GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE(FluidComponentProperty, CriticalVolume, gsoap_eml2_2::eml22__MolarVolumeUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE(FluidComponentProperty, PartialMolarVolume, gsoap_eml2_2::eml22__MolarVolumeUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE(FluidComponentProperty, MassDensity, std::string)
		GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE(FluidComponentProperty, PartialMolarDensity, std::string)
		GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE(FluidComponentProperty, ReferenceDensityZJ, std::string)
		GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE(FluidComponentProperty, ReferenceGravityZJ, gsoap_eml2_2::eml22__APIGravityUom)
		GETTER_AND_SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE(FluidComponentProperty, ViscousCompressibility, gsoap_eml2_2::eml22__ReciprocalPressureUom)
	};
}
