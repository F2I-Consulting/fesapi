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

#include "MyOwnEtpClientSession.h"
#include "etp/ProtocolHandlers/CoreHandlers.h"
#include "etp/ProtocolHandlers/DirectedDiscoveryHandlers.h"

MyOwnEtpClientSession::MyOwnEtpClientSession(boost::asio::io_context& ioc,
		const std::string & host, const std::string & port, const std::string & target,
		const std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> & requestedProtocols,
		const std::vector<std::string>& supportedObjects)
	: ETP_NS::ClientSession(ioc, host, port, target, requestedProtocols, supportedObjects)
{
	setCoreProtocolHandlers(std::make_shared<ETP_NS::CoreHandlers>(this));
	setDirectedDiscoveryProtocolHandlers(std::make_shared<ETP_NS::DirectedDiscoveryHandlers>(this));
}

void MyOwnEtpClientSession::do_when_finished()
{
	std::string command;
	std::cout << "What is your command ?" << std::endl;
	std::getline(std::cin, command);
	if (command == "quit") {
		close();
	}
	else if (command.substr(0, 10) == "GetContent") {
		Energistics::Etp::v12::Protocol::DirectedDiscovery::GetContent mb;
		mb.m_uri = command.size() > 11 ? command.substr(11) : "";
		sendAndDoRead(mb);
	}
}
