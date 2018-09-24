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

#include "MyOwnDirectedDiscoveryProtocolHandlers.h"
#include "MyOwnStoreProtocolHandlers.h"
#include "etp/ProtocolHandlers/CoreHandlers.h"
#include "etp/ProtocolHandlers/DirectedDiscoveryHandlers.h"
#include "etp/ProtocolHandlers/DataArrayHandlers.h"

#include "EtpHdfProxy.h"

namespace // anonymous namespace. Use only in that file.
{
	//partial
	COMMON_NS::AbstractHdfProxy* default_builder(soap* soapContext, const std::string & guid, const std::string & title)
	{
		gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject = gsoap_resqml2_0_1::soap_new_eml20__DataObjectReference(soapContext, 1);
		partialObject->Title = title;
		partialObject->UUID = guid;
		partialObject->ContentType = "application/x-resqml+xml;version=2.0;type=obj_EpcExternalPartReference";
		return new EtpHdfProxy(partialObject);
	}
}

MyOwnEtpClientSession::MyOwnEtpClientSession(boost::asio::io_context& ioc,
		const std::string & host, const std::string & port, const std::string & target,
		const std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> & requestedProtocols,
		const std::vector<std::string>& supportedObjects)
	: ETP_NS::ClientSession(ioc, host, port, target, requestedProtocols, supportedObjects),
	  epcDoc("../../fakeForEtpClient.epc", COMMON_NS::EpcDocument::OVERWRITE)
{
	epcDoc.set_hdf_proxy_builder(&default_builder);

	setCoreProtocolHandlers(std::make_shared<ETP_NS::CoreHandlers>(this));
	setDirectedDiscoveryProtocolHandlers(std::make_shared<MyOwnDirectedDiscoveryProtocolHandlers>(this));
	setStoreProtocolHandlers(std::make_shared<MyOwnStoreProtocolHandlers>(this));
	setDataArrayProtocolHandlers(std::make_shared<ETP_NS::DataArrayHandlers>(this));
}

MyOwnEtpClientSession::~MyOwnEtpClientSession()
{
	epcDoc.close();
}

void MyOwnEtpClientSession::do_when_finished()
{
	//clean
	std::static_pointer_cast<MyOwnDirectedDiscoveryProtocolHandlers>(protocolHandlers[Energistics::Etp::v12::Datatypes::Protocols::DirectedDiscovery])->getObjectWhenDiscovered = false;

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
	else if (command.substr(0, 16) == "GetSourceObjects") {
		std::static_pointer_cast<MyOwnDirectedDiscoveryProtocolHandlers>(protocolHandlers[Energistics::Etp::v12::Datatypes::Protocols::DirectedDiscovery])->getObjectWhenDiscovered = true;
		Energistics::Etp::v12::Protocol::DirectedDiscovery::GetSources mb;
		mb.m_uri = command.size() > 17 ? command.substr(17) : "";
		sendAndDoRead(mb);
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
	else if (command.substr(0, 12) == "List") {
		std::cout << "*** START LISTING ***" << std::endl;
		for (const auto& entryPair : epcDoc.getResqmlAbstractObjectSet()) {
			if (!entryPair.second->isPartial()) {
				std::cout << entryPair.first << " : " << entryPair.second->getTitle() << std::endl;
				std::cout << "*** SOURCE REL ***" << std::endl;
				for (const auto& rel : entryPair.second->getAllSourceRelationships()) {
					std::cout << rel.getId() << " : " << rel.getType() << std::endl;
				}
				std::cout << "*** TARGET REL ***" << std::endl;
				for (const auto& rel : entryPair.second->getAllTargetRelationships()) {
					std::cout << rel.getId() << " : " << rel.getType() << std::endl;
				}
				std::cout << std::endl;
			}
			else {
				std::cout << "PARTIAL " << entryPair.first << " : " << entryPair.second->getTitle() << std::endl;
			}
		}
		std::cout << "*** END LISTING ***" << std::endl;
		do_when_finished();
	}
	else {
		std::cout << "WRONG COMMAND!!! Please retry" << std::endl;
		std::cout << "List of available commands :" << std::endl;
		std::cout << "List -> list the objects which have been got from ETP to the in memory epc" << std::endl;
		std::cout << "GetContent folderUri -> get content of a folder in an ETP store" << std::endl;
		std::cout << "GetSources dataObjectURI  -> get dataobject sources of a dataobject in an ETP store" << std::endl;
		std::cout << "GetTargets dataObjectURI  -> get dataobject targets of a dataobject in an ETP store" << std::endl;
		std::cout << "GetObject dataObjectURI  -> get the object from an ETP store and store it into the in memory epc (only create partial TARGET relationships, not any SOURCE relationships)" << std::endl;
		std::cout << "GetDataArray epcExternalPartURI datasetPathInEpcExternalPart  -> get the numerical values from a dataset included in an EpcExternalPart over ETP." << std::endl;
		do_when_finished();
	}
}
