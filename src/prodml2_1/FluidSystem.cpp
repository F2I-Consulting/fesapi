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
	static_cast<eml22__TemperaturePressure*>(fs->StandardConditions)->Pressure->uom = pressureUom;

	fs->ReservoirFluidKind = reservoirFluidKind;

	fs->SolutionGOR = soap_new_eml22__VolumePerVolumeMeasure(repo->getGsoapContext());
	fs->SolutionGOR->__item = temperatureValue;
	fs->SolutionGOR->uom = temperatureUom;

	repo->addOrReplaceDataObject(this);
}
