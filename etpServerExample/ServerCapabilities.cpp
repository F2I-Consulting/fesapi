#include "ServerCapabilities.h"

#include <boost/beast/websocket/stream.hpp>

std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> makeEndpointCapabilities()
{
	std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> result;

	Energistics::Etp::v12::Datatypes::DataValue value;

	value.m_item.set_int(16000000);
	result["maxWebSocketMessagePayloadSize"] = value;

	value.m_item.set_boolean(false);
	result["SupportsAlternateRequestUris"] = value;

	return result;
}

std::vector<std::string> makeSupportedObjects()
{
	std::vector<std::string> result;
	result.push_back("resqml20.*");
	result.push_back("eml20.*");

	result.push_back("witsml20.Well");
	result.push_back("witsml20.Wellbore");
	result.push_back("witsml20.Trajectory");
	result.push_back("witsml20.WellCompletion");
	result.push_back("witsml20.WellboreCompletion");
	result.push_back("witsml20.WellboreGeometry");
	result.push_back("witsml20.Log");
	result.push_back("witsml20.ChannelSet");
	result.push_back("witsml20.Channel");

	result.push_back("prodml21.FluidSystem");
	result.push_back("prodml21.FluidCharacterization");

	result.push_back("witsml21.ErrorTerm");
	result.push_back("witsml21.ErrorTermDictionary");
	result.push_back("witsml21.ToolErrorModel");
	result.push_back("witsml21.ToolErrorModelDictionary");
	result.push_back("witsml21.WeightingFunction");
	result.push_back("witsml21.WeightingFunctionDictionary");

	return result;
}

std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> makeSupportedProtocols()
{
	std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> result;
	Energistics::Etp::v12::Datatypes::Version protocolVersion;
	protocolVersion.m_major = 1;
	protocolVersion.m_minor = 2;
	protocolVersion.m_patch = 0;
	protocolVersion.m_revision = 0;

	Energistics::Etp::v12::Datatypes::SupportedProtocol protocol;
	protocol.m_protocol = Energistics::Etp::v12::Datatypes::Protocol::Core;
	protocol.m_protocolVersion = protocolVersion;
	protocol.m_role = "server";
	result.push_back(protocol);

	protocol.m_protocol = Energistics::Etp::v12::Datatypes::Protocol::Discovery;
	protocol.m_protocolVersion = protocolVersion;
	protocol.m_role = "store";
	result.push_back(protocol);

	protocol.m_protocol = Energistics::Etp::v12::Datatypes::Protocol::Store;
	protocol.m_protocolVersion = protocolVersion;
	protocol.m_role = "store";
	result.push_back(protocol);

	protocol.m_protocol = Energistics::Etp::v12::Datatypes::Protocol::StoreNotification;
	protocol.m_protocolVersion = protocolVersion;
	protocol.m_role = "store";
	Energistics::Etp::v12::Datatypes::DataValue value;
	value.m_item.set_int((std::numeric_limits<int>::max)());
	protocol.m_protocolCapabilities["MaxDataArraySize"] = value;
	result.push_back(protocol);

	protocol.m_protocolCapabilities.clear();
	protocol.m_protocol = Energistics::Etp::v12::Datatypes::Protocol::DataArray;
	protocol.m_protocolVersion = protocolVersion;
	protocol.m_role = "store";
	result.push_back(protocol);

	return result;
}
