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
#include "MyOwnStoreProtocolHandlers.h"
#include "etp/ProtocolHandlers/DataArrayHandlers.h"

MyOwnEtpClientSession::MyOwnEtpClientSession(boost::asio::io_context& ioc,
		const std::string & host, const std::string & port, const std::string & target,
		const std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> & requestedProtocols,
		const std::vector<std::string>& supportedObjects)
	: ETP_NS::ClientSession(ioc, host, port, target, requestedProtocols, supportedObjects),
	  epcDoc("", COMMON_NS::EpcDocument::OVERWRITE)
{
	setCoreProtocolHandlers(std::make_shared<ETP_NS::CoreHandlers>(this));
	setDirectedDiscoveryProtocolHandlers(std::make_shared<ETP_NS::DirectedDiscoveryHandlers>(this));
	setStoreProtocolHandlers(std::make_shared<MyOwnStoreProtocolHandlers>(this));
	setDataArrayProtocolHandlers(std::make_shared<ETP_NS::DataArrayHandlers>(this));
}

MyOwnEtpClientSession::~MyOwnEtpClientSession()
{
	epcDoc.close();
}

void MyOwnEtpClientSession::do_when_finished()
{
	std::string command;
	std::cout << "What is your command (""quit"" for closing connection)?" << std::endl;
	std::getline(std::cin, command);
	if (command == "quit") {
		close();
	}
	else if (command.substr(0, 10) == "GetContent") {
		Energistics::Etp::v12::Protocol::DirectedDiscovery::GetContent mb;
		mb.m_uri = command.size() > 11 ? command.substr(11) : "";
		sendAndDoRead(mb);
	}
	else if (command.substr(0, 10) == "GetSources") {
		Energistics::Etp::v12::Protocol::DirectedDiscovery::GetSources mb;
		mb.m_uri = command.size() > 11 ? command.substr(11) : "";
		sendAndDoRead(mb);
	}
	else if (command.substr(0, 10) == "GetTargets") {
		Energistics::Etp::v12::Protocol::DirectedDiscovery::GetTargets mb;
		mb.m_uri = command.size() > 11 ? command.substr(11) : "";
		sendAndDoRead(mb);
	}
	else if (command.substr(0, 9) == "GetObject") {
		Energistics::Etp::v12::Protocol::Store::GetObject getO;
		getO.m_uri = command.size() > 10 ? command.substr(10) : "";
		sendAndDoRead(getO);
	}
	else if (command.substr(0, 12) == "GetDataArray") {
		Energistics::Etp::v12::Protocol::DataArray::GetDataArray gda;
		size_t lastSpace = command.rfind(' ');
		gda.m_uri = command.size() > 13 ? command.substr(13, lastSpace-13) : "";
		++lastSpace;
		gda.m_pathInResource = command.substr(lastSpace);
		std::cout << gda.m_pathInResource << std::endl;
		sendAndDoRead(gda);
	}
	else {
		std::cout << "WRONG COMMAND!!! Please retry" << std::endl;
		std::cout << "List of available commands :" << std::endl;
		std::cout << "GetContent folderUri" << std::endl;
		std::cout << "GetSources dataObjectURI" << std::endl;
		std::cout << "GetTargets dataObjectURI" << std::endl;
		std::cout << "GetObject dataObjectURI" << std::endl;
		std::cout << "GetDataArray epcExternalPartURI datasetPathInEpcExternalPart" << std::endl;
		do_when_finished();
	}
}
