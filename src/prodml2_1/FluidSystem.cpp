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
	static_cast<eml22__TemperaturePressure*>(fs->StandardConditions)->Temperature->__item = temperatureValue;
	static_cast<eml22__TemperaturePressure*>(fs->StandardConditions)->Temperature->uom = temperatureUom;
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
		if (str.find("degC") != std::string::npos) return gsoap_eml2_2::eml22__ThermodynamicTemperatureUom__degC;
		if (str.find("degF") != std::string::npos) return gsoap_eml2_2::eml22__ThermodynamicTemperatureUom__degF;
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
		if (str.find("bar") != std::string::npos) return gsoap_eml2_2::eml22__PressureUom__bar;
		if (str.find("atm") != std::string::npos) return gsoap_eml2_2::eml22__PressureUom__atm;
		if (str.find("Hg") != std::string::npos) return gsoap_eml2_2::eml22__PressureUom__inHg_x005b60degF_x005d;
		throw logic_error("Unrecognized pressure uom in " + str);
	}

	throw logic_error("Unrecognized datatype for StandardConditions.");
}

double FluidSystem::getSolutionGORValue() const {
	return static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->SolutionGOR->__item;
}

gsoap_eml2_2::eml22__VolumePerVolumeUom FluidSystem::getSolutionGORUom() const {
	gsoap_eml2_2::eml22__VolumePerVolumeUom* result;
	gsoap_eml2_2::soap_s2eml22__VolumePerVolumeUom(getGsoapContext(), static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->SolutionGOR->uom.c_str(), result);
	if (result == nullptr) {
		throw logic_error("Cannot recognize the exotic volume per volume uom : " + static_cast<prodml21__FluidSystem*>(gsoapProxy2_2)->SolutionGOR->uom);
	}

	return *result;
}
