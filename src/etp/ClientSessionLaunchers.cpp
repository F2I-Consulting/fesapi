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

#include "ClientSessionLaunchers.h"

namespace
{
	std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> getRequestedProtocols() {
		Energistics::Etp::v12::Datatypes::Version protocolVersion;
		protocolVersion.major = 1;
		protocolVersion.minor = 2;
		protocolVersion.patch = 0;
		protocolVersion.revision = 0;

		std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> requestedProtocols;
		Energistics::Etp::v12::Datatypes::SupportedProtocol protocol;

		protocol.protocol = Energistics::Etp::v12::Datatypes::Protocol::Core;
		protocol.protocolVersion = protocolVersion;
		protocol.role = "server";
		requestedProtocols.push_back(protocol);

		protocol.protocol = Energistics::Etp::v12::Datatypes::Protocol::Discovery;
		protocol.protocolVersion = protocolVersion;
		protocol.role = "store";
		requestedProtocols.push_back(protocol);

		protocol.protocol = Energistics::Etp::v12::Datatypes::Protocol::Store;
		protocol.protocolVersion = protocolVersion;
		protocol.role = "store";
		requestedProtocols.push_back(protocol);

		protocol.protocol = Energistics::Etp::v12::Datatypes::Protocol::DataArray;
		protocol.protocolVersion = protocolVersion;
		protocol.role = "store";
		requestedProtocols.push_back(protocol);

		protocol.protocol = Energistics::Etp::v12::Datatypes::Protocol::StoreNotification;
		protocol.protocolVersion = protocolVersion;
		protocol.role = "store";
		requestedProtocols.push_back(protocol);


		return requestedProtocols;
	}
}

std::shared_ptr<ETP_NS::PlainClientSession> ETP_NS::ClientSessionLaunchers::createWsClientSession(const std::string & host, const std::string & port, const std::string & target, const std::string & authorization)
{
	return std::make_shared<PlainClientSession>(host, port, target.empty() ? "/" : target, authorization, getRequestedProtocols(), std::vector<Energistics::Etp::v12::Datatypes::SupportedDataObject>());
}

#ifdef WITH_ETP_SSL

namespace ssl = boost::asio::ssl;               // from <boost/asio/ssl.hpp>

std::shared_ptr<ETP_NS::SslClientSession> ETP_NS::ClientSessionLaunchers::createWssClientSession(const std::string & host, const std::string & port, const std::string & target, const std::string & authorization,
	const std::string & additionalCertificates)
{
	// The SSL context is required, and holds certificates
	ssl::context ctx{ ssl::context::sslv23_client };

	if (!additionalCertificates.empty()) {
		boost::system::error_code ec;
		ctx.add_certificate_authority(
			boost::asio::buffer(additionalCertificates.data(), additionalCertificates.size()), ec);
		if (ec) {
			std::cerr << "Cannot add certificates : " << additionalCertificates << std::endl;
			return nullptr;
		}
	}

	return std::make_shared<SslClientSession>(ctx, host, port, target.empty() ? "/" : target, authorization, getRequestedProtocols(), std::vector<Energistics::Etp::v12::Datatypes::SupportedDataObject>());
}
#endif
