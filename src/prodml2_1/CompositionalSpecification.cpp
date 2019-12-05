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
#include "CompositionalSpecification.h"

using namespace PRODML2_1_NS;
using namespace gsoap_eml2_2;

void CompositionalSpecification::setMixingRule(gsoap_eml2_2::prodml21__MixingRule mixingRule)
{
	if (static_cast<prodml21__AbstractCompositionalModel*>(gsoapProxy)->MixingRule == nullptr) {
		static_cast<prodml21__AbstractCompositionalModel*>(gsoapProxy)->MixingRule = soap_new_prodml21__MixingRule(gsoapProxy->soap);
	}
	*static_cast<prodml21__AbstractCompositionalModel*>(gsoapProxy)->MixingRule = mixingRule;
}

void CompositionalSpecification::pushBackBinaryInteractionCoefficient(double value, const std::string & fluidComponent1Reference, const std::string & fluidComponent2Reference)
{
	if (static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->BinaryInteractionCoefficientSet == nullptr) {
		static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->BinaryInteractionCoefficientSet = soap_new_prodml21__BinaryInteractionCoefficientSet(gsoapProxy->soap);
	}

	prodml21__BinaryInteractionCoefficient* coefficent = soap_new_prodml21__BinaryInteractionCoefficient(gsoapProxy->soap);
	static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->BinaryInteractionCoefficientSet->BinaryInteractionCoefficient.push_back(coefficent);
	coefficent->__item = value;
	coefficent->fluidComponent1Reference = fluidComponent1Reference;
	if (!fluidComponent2Reference.empty()) {
		coefficent->fluidComponent2Reference = soap_new_std__string(gsoapProxy->soap);
		coefficent->fluidComponent2Reference->assign(fluidComponent2Reference);
	}
}

void CompositionalSpecification::pushBackFluidComponentProperty(const std::string & fluidComponentReference)
{
	if (static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet == nullptr) {
		static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet = soap_new_prodml21__ComponentPropertySet(gsoapProxy->soap);
	}

	prodml21__FluidComponentProperty* prop = soap_new_prodml21__FluidComponentProperty(gsoapProxy->soap);
	static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet->FluidComponentProperty.push_back(prop);
	prop->fluidComponentReference = fluidComponentReference;
}

#define SETTER_FLUID_COMPONENT_PROPERTY_OPTIONAL_ATTRIBUTE_IMPL(vectorName, attributeName, attributeDatatype, constructor)\
void CompositionalSpecification::set##vectorName##attributeName(unsigned int index, const attributeDatatype& value)\
{\
	if (static_cast<prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet == nullptr || index >= static_cast<prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet->vectorName.size()) {throw std::out_of_range("This index is out of range.");}\
	static_cast<prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet->vectorName[index]->attributeName = constructor(gsoapProxy->soap);\
	*static_cast<prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet->vectorName[index]->attributeName = value;\
}

#define SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE_IMPL(vectorName, attributeName, uomDatatype, constructor)\
void CompositionalSpecification::set##vectorName##attributeName(unsigned int index, double value, uomDatatype uom)\
{\
	if (static_cast<prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet == nullptr || index >= static_cast<prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet->vectorName.size()) {throw std::out_of_range("This index is out of range.");}\
	static_cast<prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet->vectorName[index]->attributeName = constructor(gsoapProxy->soap);\
	static_cast<prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet->vectorName[index]->attributeName->__item = value;\
	static_cast<prodml21__AbstractCompositionalModel*>(gsoapProxy)->ComponentPropertySet->vectorName[index]->attributeName->uom = uom;\
}

SETTER_FLUID_COMPONENT_PROPERTY_OPTIONAL_ATTRIBUTE_IMPL(FluidComponentProperty, AcentricFactor, double, soap_new_double)
SETTER_FLUID_COMPONENT_PROPERTY_OPTIONAL_ATTRIBUTE_IMPL(FluidComponentProperty, OmegaA, double, soap_new_double)
SETTER_FLUID_COMPONENT_PROPERTY_OPTIONAL_ATTRIBUTE_IMPL(FluidComponentProperty, OmegaB, double, soap_new_double)
SETTER_FLUID_COMPONENT_PROPERTY_OPTIONAL_ATTRIBUTE_IMPL(FluidComponentProperty, VolumeShiftParameter, double, soap_new_double)
SETTER_FLUID_COMPONENT_PROPERTY_OPTIONAL_ATTRIBUTE_IMPL(FluidComponentProperty, Parachor, double, soap_new_double)
SETTER_FLUID_COMPONENT_PROPERTY_OPTIONAL_ATTRIBUTE_IMPL(FluidComponentProperty, Remark, std::string, soap_new_std__string)

SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE_IMPL(FluidComponentProperty, CriticalPressure, std::string, gsoap_eml2_2::soap_new_eml22__PressureMeasure)
SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE_IMPL(FluidComponentProperty, CriticalTemperature, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom, gsoap_eml2_2::soap_new_eml22__ThermodynamicTemperatureMeasure)
SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE_IMPL(FluidComponentProperty, ReferenceTemperatureZJ, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom, gsoap_eml2_2::soap_new_eml22__ThermodynamicTemperatureMeasure)
SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE_IMPL(FluidComponentProperty, CriticalViscosity, gsoap_eml2_2::eml22__DynamicViscosityUom, gsoap_eml2_2::soap_new_eml22__DynamicViscosityMeasure)
SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE_IMPL(FluidComponentProperty, CompactVolume, std::string, gsoap_eml2_2::soap_new_eml22__VolumeMeasure)
SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE_IMPL(FluidComponentProperty, CriticalVolume, gsoap_eml2_2::eml22__MolarVolumeUom, gsoap_eml2_2::soap_new_eml22__MolarVolumeMeasure)
SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE_IMPL(FluidComponentProperty, PartialMolarVolume, gsoap_eml2_2::eml22__MolarVolumeUom, gsoap_eml2_2::soap_new_eml22__MolarVolumeMeasure)
SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE_IMPL(FluidComponentProperty, MassDensity, std::string, gsoap_eml2_2::soap_new_eml22__MassPerVolumeMeasure)
SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE_IMPL(FluidComponentProperty, PartialMolarDensity, std::string, gsoap_eml2_2::soap_new_eml22__MassPerVolumeMeasure)
SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE_IMPL(FluidComponentProperty, ReferenceDensityZJ, std::string, gsoap_eml2_2::soap_new_eml22__MassPerVolumeMeasure)
SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE_IMPL(FluidComponentProperty, ReferenceGravityZJ, gsoap_eml2_2::eml22__APIGravityUom, gsoap_eml2_2::soap_new_eml22__APIGravityMeasure)
SETTER_FLUID_COMPONENT_PROPERTY_MEASURE_ATTRIBUTE_IMPL(FluidComponentProperty, ViscousCompressibility, gsoap_eml2_2::eml22__ReciprocalPressureUom, gsoap_eml2_2::soap_new_eml22__ReciprocalPressureMeasure)
