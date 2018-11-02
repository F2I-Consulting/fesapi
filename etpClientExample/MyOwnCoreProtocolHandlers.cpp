/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agceements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"; you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agceed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-----------------------------------------------------------------------*/
#include "MyOwnCoreProtocolHandlers.h"

#include <thread>

#include "MyOwnDirectedDiscoveryProtocolHandlers.h"

void askUser(ETP_NS::AbstractSession* session)
{
	std::string buffer;

	std::cout << "What is your command (""quit"" for closing connection)?" << std::endl;
	std::string command;
	while (command != "quit")
	{
		std::getline(std::cin, command);
		if (command.substr(0, 10) == "GetContent") {
			Energistics::Etp::v12::Protocol::DirectedDiscovery::GetContent mb;
			mb.m_uri = command.size() > 11 ? command.substr(11) : "";
			session->send(mb);
		}
		else if (command.substr(0, 10) == "GetSources") {
			Energistics::Etp::v12::Protocol::DirectedDiscovery::GetSources mb;
			mb.m_uri = command.size() > 11 ? command.substr(11) : "";
			session->send(mb);
		}
		else if (command.substr(0, 10) == "GetTargets") {
			Energistics::Etp::v12::Protocol::DirectedDiscovery::GetTargets mb;
			mb.m_uri = command.size() > 11 ? command.substr(11) : "";
			session->send(mb);
		}
		else if (command.substr(0, 9) == "GetObject") {
			Energistics::Etp::v12::Protocol::Store::GetObject_ getO;
			getO.m_uri = command.size() > 10 ? command.substr(10) : "";
			session->send(getO);
		}
		else if (command.substr(0, 16) == "GetSourceObjects") {
			Energistics::Etp::v12::Protocol::DirectedDiscovery::GetSources mb;
			mb.m_uri = command.size() > 17 ? command.substr(17) : "";
			std::static_pointer_cast<MyOwnDirectedDiscoveryProtocolHandlers>(session->getDirectedDiscoveryProtocolHandlers())->getObjectWhenDiscovered.push_back(session->send(mb));
		}
		else if (command.substr(0, 12) == "GetDataArray") {
			Energistics::Etp::v12::Protocol::DataArray::GetDataArray gda;
			size_t lastSpace = command.rfind(' ');
			gda.m_uri = command.size() > 13 ? command.substr(13, lastSpace-13) : "";
			++lastSpace;
			gda.m_pathInResource = command.substr(lastSpace);
			std::cout << gda.m_pathInResource << std::endl;
			session->send(gda);
		}
		else if (command.substr(0, 12) == "List") {
			std::cout << "*** START LISTING ***" << std::endl;
			COMMON_NS::EpcDocument& epcDoc = static_cast<MyOwnEtpClientSession*>(session)->epcDoc;
			for (const auto& entryPair : epcDoc.getResqmlAbstractObjectSet()) {
				if (!entryPair.second->isPartial()) {
					std::cout << entryPair.first << " : " << entryPair.second->getTitle() << std::endl;
					std::cout << "*** SOURCE REL ***" << std::endl;
					for (const auto& uuid : entryPair.second->getAllSourceRelationshipUuids()) {
						std::cout << uuid << " : " << epcDoc.getResqmlAbstractObjectByUuid(uuid)->getXmlTag() << std::endl;
					}
					std::cout << "*** TARGET REL ***" << std::endl;
					for (const auto& uuid : entryPair.second->getAllTargetRelationshipUuids()) {
						std::cout << uuid << " : " << epcDoc.getResqmlAbstractObjectByUuid(uuid)->getXmlTag() << std::endl;
					}
					std::cout << std::endl;
				}
				else {
					std::cout << "PARTIAL " << entryPair.first << " : " << entryPair.second->getTitle() << std::endl;
				}
			}
			std::cout << "*** END LISTING ***" << std::endl;
		}
		else {
			std::cout << "List of available commands :" << std::endl;
			std::cout << "\tList" << std::endl << "\t\tList the objects which have been got from ETP to the in memory epc" << std::endl << std::endl;
			std::cout << "\tGetContent folderUri" << std::endl << "\t\tGet content of a folder in an ETP store" << std::endl << std::endl;
			std::cout << "\tGetSources dataObjectURI" << std::endl << "\t\tGet dataobject sources of a dataobject in an ETP store" << std::endl << std::endl;
			std::cout << "\tGetTargets dataObjectURI" << std::endl << "\t\tGet dataobject targets of a dataobject in an ETP store" << std::endl << std::endl;
			std::cout << "\tGetObject dataObjectURI" << std::endl << "\t\tGet the object from an ETP store and store it into the in memory epc (only create partial TARGET relationships, not any SOURCE relationships)" << std::endl << std::endl;
			std::cout << "\tGetDataArray epcExternalPartURI datasetPathInEpcExternalPart" << std::endl << "\t\tGet the numerical values from a dataset included in an EpcExternalPart over ETP." << std::endl << std::endl;
		}
	}

	session->close();
}

void MyOwnCoreProtocolHandlers::on_OpenSession(const Energistics::Etp::v12::Protocol::Core::OpenSession & os)
{
	// Ask the user about what he wants to do on another thread
	// The main thread iso n reading mode
	std::thread askUserThread(askUser, session);
	askUserThread.detach(); // Detach the thread since we don't want it to be a blocking one.
}
