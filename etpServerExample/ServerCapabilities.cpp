#include "ServerCapabilities.h"

#include <boost/beast/websocket/stream.hpp>

std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> makeEndpointCapabilities()
{
	std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> result;

	Energistics::Etp::v12::Datatypes::DataValue value;

	value.item.set_int(16000000);
	result["maxWebSocketMessagePayloadSize"] = value;

	value.item.set_boolean(false);
	result["SupportsAlternateRequestUris"] = value;

	return result;
}

std::vector<std::string> makeSupportedEncodings()
{
	return std::vector<std::string>(1, "binary");
}

std::vector<Energistics::Etp::v12::Datatypes::SupportedDataObject> makeSupportedDataObjects()
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

std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> makeSupportedProtocols()
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
