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
#include "ServerInitializationParameters.h"

using namespace ETP_NS;

std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> ServerInitializationParameters::makeEndpointCapabilities() const
{
	std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> result;

	Energistics::Etp::v12::Datatypes::DataValue value;

	value.item.set_int(16000000);
	result["maxWebSocketMessagePayloadSize"] = value;

	value.item.set_boolean(false);
	result["SupportsAlternateRequestUris"] = value;

	return result;
}

std::vector<std::string> ServerInitializationParameters::makeSupportedEncodings() const
{
	return std::vector<std::string>(1, "binary");
}

std::vector<Energistics::Etp::v12::Datatypes::SupportedDataObject> ServerInitializationParameters::makeSupportedDataObjects() const
{
	std::vector<Energistics::Etp::v12::Datatypes::SupportedDataObject> result;

	Energistics::Etp::v12::Datatypes::SupportedDataObject supportedDataObject;
	supportedDataObject.qualifiedType = "resqml20.*";
	result.push_back(supportedDataObject);

	supportedDataObject.qualifiedType = "eml20.*";
	result.push_back(supportedDataObject);

	supportedDataObject.qualifiedType = "witsml20.Well";
	result.push_back(supportedDataObject);
	supportedDataObject.qualifiedType = "witsml20.Wellbore";
	result.push_back(supportedDataObject);
	supportedDataObject.qualifiedType = "witsml20.Trajectory";
	result.push_back(supportedDataObject);
	supportedDataObject.qualifiedType = "witsml20.WellCompletion";
	result.push_back(supportedDataObject);
	supportedDataObject.qualifiedType = "witsml20.WellboreCompletion";
	result.push_back(supportedDataObject);
	supportedDataObject.qualifiedType = "witsml20.WellboreGeometry";
	result.push_back(supportedDataObject);
	supportedDataObject.qualifiedType = "witsml20.Log";
	result.push_back(supportedDataObject);
	supportedDataObject.qualifiedType = "witsml20.ChannelSet";
	result.push_back(supportedDataObject);
	supportedDataObject.qualifiedType = "witsml20.Channel";
	result.push_back(supportedDataObject);

	supportedDataObject.qualifiedType = "prodml21.FluidSystem";
	result.push_back(supportedDataObject);
	supportedDataObject.qualifiedType = "prodml21.FluidCharacterization";
	result.push_back(supportedDataObject);

	supportedDataObject.qualifiedType = "witsml21.ErrorTerm";
	result.push_back(supportedDataObject);
	supportedDataObject.qualifiedType = "witsml21.ErrorTermDictionary";
	result.push_back(supportedDataObject);
	supportedDataObject.qualifiedType = "witsml21.ToolErrorModel";
	result.push_back(supportedDataObject);
	supportedDataObject.qualifiedType = "witsml21.ToolErrorModelDictionary";
	result.push_back(supportedDataObject);
	supportedDataObject.qualifiedType = "witsml21.WeightingFunction";
	result.push_back(supportedDataObject);
	supportedDataObject.qualifiedType = "witsml21.WeightingFunctionDictionary";
	result.push_back(supportedDataObject);

	return result;
}

std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> ServerInitializationParameters::makeSupportedProtocols() const
{
	std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> result;
	Energistics::Etp::v12::Datatypes::Version protocolVersion;
	protocolVersion.major = 1;
	protocolVersion.minor = 2;
	protocolVersion.patch = 0;
	protocolVersion.revision = 0;

	Energistics::Etp::v12::Datatypes::SupportedProtocol protocol;
	protocol.protocol = Energistics::Etp::v12::Datatypes::Protocol::Core;
	protocol.protocolVersion = protocolVersion;
	protocol.role = "server";
	result.push_back(protocol);

	protocol.protocol = Energistics::Etp::v12::Datatypes::Protocol::Discovery;
	protocol.protocolVersion = protocolVersion;
	protocol.role = "store";
	result.push_back(protocol);

	protocol.protocol = Energistics::Etp::v12::Datatypes::Protocol::Store;
	protocol.protocolVersion = protocolVersion;
	protocol.role = "store";
	result.push_back(protocol);

	protocol.protocol = Energistics::Etp::v12::Datatypes::Protocol::StoreNotification;
	protocol.protocolVersion = protocolVersion;
	protocol.role = "store";
	Energistics::Etp::v12::Datatypes::DataValue value;
	value.item.set_int((std::numeric_limits<int>::max)());
	protocol.protocolCapabilities["MaxDataArraySize"] = value;
	result.push_back(protocol);

	protocol.protocolCapabilities.clear();
	protocol.protocol = Energistics::Etp::v12::Datatypes::Protocol::DataArray;
	protocol.protocolVersion = protocolVersion;
	protocol.role = "store";
	result.push_back(protocol);

	return result;
}
