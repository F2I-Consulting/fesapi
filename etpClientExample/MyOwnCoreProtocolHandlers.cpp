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

#include "etp/EtpHdfProxy.h"

#include <resqml2_0_1/AbstractIjkGridRepresentation.h>
#include <resqml2_0_1/ContinuousPropertySeries.h>

void setSessionToEtpHdfProxy(MyOwnEtpClientSession* myOwnEtpSession) {
	COMMON_NS::EpcDocument& epcDoc = myOwnEtpSession->epcDoc;
	for (const auto & hdfProxy : epcDoc.getHdfProxySet())
	{
		ETP_NS::EtpHdfProxy* etpHdfProxy = dynamic_cast<ETP_NS::EtpHdfProxy*>(hdfProxy);
		if (etpHdfProxy != nullptr && etpHdfProxy->getSession() == nullptr) {
			etpHdfProxy->setSession(myOwnEtpSession->getIoContext(), myOwnEtpSession->getHost(), myOwnEtpSession->getPort(), myOwnEtpSession->getTarget());
		}
	}
}

void askUser(MyOwnEtpClientSession* session)
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
		else if (command.substr(0, 16) == "GetTargetObjects") {
			Energistics::Etp::v12::Protocol::DirectedDiscovery::GetTargets mb;
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
		else if (command.substr(0, 16) == "GetXyzOfIjkGrids") {
			setSessionToEtpHdfProxy(session);
			COMMON_NS::EpcDocument& epcDoc = session->epcDoc;
			auto ijkGridSet = epcDoc.getIjkGridRepresentationSet();
			for (const auto & ijkGrid : ijkGridSet) {
				if (ijkGrid->isPartial()) {
					std::cout << "Partial Ijk Grid " << ijkGrid->getTitle() << " : " << ijkGrid->getUuid() << std::endl;
					continue;
				}
				else {
					std::cout << "Ijk Grid " << ijkGrid->getTitle() << " : " << ijkGrid->getUuid() << std::endl;
					if (ijkGrid->getGeometryKind() == RESQML2_0_1_NS::AbstractIjkGridRepresentation::NO_GEOMETRY) {
						std::cout << "This IJK Grid has got no geometry." << std::endl;
						continue;
					}
				}

				//*****************
				//*** GEOMETRY ****
				//*****************
				auto xyzPointCount = ijkGrid->getXyzPointCountOfPatch(0);
				std::unique_ptr<double[]> xyzPoints(new double[xyzPointCount*3]);
				ijkGrid->getXyzPointsOfPatchInGlobalCrs(0, xyzPoints.get());
				for (auto xyzPointIndex = 0; xyzPointIndex < xyzPointCount && xyzPointIndex < 20; ++xyzPointIndex) {
					std::cout << "XYZ Point Index " << xyzPointIndex << " : " << xyzPoints[xyzPointIndex*3] << "," << xyzPoints[xyzPointIndex * 3 + 1] << "," << xyzPoints[xyzPointIndex * 3 + 2] << std::endl;
				}

				//*****************
				//*** PROPERTY ****
				//*****************
				auto propSet = ijkGrid->getPropertySet();
				for (const auto & prop : propSet) {
					RESQML2_0_1_NS::ContinuousProperty* continuousProp = dynamic_cast<RESQML2_0_1_NS::ContinuousProperty*>(prop);
					if (continuousProp != nullptr && dynamic_cast<RESQML2_0_1_NS::ContinuousPropertySeries*>(continuousProp) == nullptr &&
						continuousProp->getAttachmentKind() == gsoap_resqml2_0_1::resqml2__IndexableElements::resqml2__IndexableElements__cells) {
						std::cout << "Continuous property " << prop->getTitle() << " : " << prop->getUuid() << std::endl;
						auto cellCount = ijkGrid->getCellCount();
						std::unique_ptr<double[]> values(new double[cellCount * continuousProp->getElementCountPerValue()]);
						continuousProp->getDoubleValuesOfPatch(0, values.get());
						for (auto cellIndex = 0; cellIndex < cellCount; ++cellIndex) {
							for (auto elementIndex = 0; elementIndex < continuousProp->getElementCountPerValue(); ++elementIndex) {
								std::cout << "Cell Index " << cellIndex << " : " << values[cellIndex] << std::endl;
							}
						}
					}
					else {
						std::cout << "Non continuous property " << prop->getTitle() << " : " << prop->getUuid() << std::endl;
					}
				}
				std::cout << std::endl;
			}
		}
		else if (command.substr(0, 4) == "List") {
			std::cout << "*** START LISTING ***" << std::endl;
			COMMON_NS::EpcDocument& epcDoc = session->epcDoc;
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
		else if (command.substr(0, 4) != "quit") {
			std::cout << "List of available commands :" << std::endl;
			std::cout << "\tList" << std::endl << "\t\tList the objects which have been got from ETP to the in memory epc" << std::endl << std::endl;
			std::cout << "\tGetContent folderUri" << std::endl << "\t\tGet content of a folder in an ETP store" << std::endl << std::endl;
			std::cout << "\tGetSources dataObjectURI" << std::endl << "\t\tGet dataobject sources of a dataobject in an ETP store" << std::endl << std::endl;
			std::cout << "\tGetTargets dataObjectURI" << std::endl << "\t\tGet dataobject targets of a dataobject in an ETP store" << std::endl << std::endl;
			std::cout << "\tGetObject dataObjectURI" << std::endl << "\t\tGet the object from an ETP store and store it into the in memory epc (only create partial TARGET relationships, not any SOURCE relationships)" << std::endl << std::endl;
			std::cout << "\tGetSourceObjects dataObjectURI" << std::endl << "\t\tGet the source objects of another object from an ETP store and store it into the in memory epc" << std::endl << std::endl;
			std::cout << "\tGetTargetObjects dataObjectURI" << std::endl << "\t\tGet the target objects of another object from an ETP store and store it into the in memory epc" << std::endl << std::endl;
			std::cout << "\tGetDataArray epcExternalPartURI datasetPathInEpcExternalPart" << std::endl << "\t\tGet the numerical values from a dataset included in an EpcExternalPart over ETP." << std::endl << std::endl;
			std::cout << "\GetXyzOfIjkGrids" << std::endl << "\t\tGet all the XYZ points of the retrieved IJK grids and also their continuous property values." << std::endl << std::endl;
			std::cout << "\tquit" << std::endl << "\t\tQuit the session." << std::endl << std::endl;
		}
	}

	session->close();
	session->epcDoc.close();
}

void MyOwnCoreProtocolHandlers::on_OpenSession(const Energistics::Etp::v12::Protocol::Core::OpenSession & os)
{
	static_cast<MyOwnEtpClientSession*>(session)->epcDoc.open("../../fakeForEtpClient.epc", COMMON_NS::EpcDocument::ETP);
	// Ask the user about what he wants to do on another thread
	// The main thread is on reading mode
	std::thread askUserThread(askUser, static_cast<MyOwnEtpClientSession*>(session));
	askUserThread.detach(); // Detach the thread since we don't want it to be a blocking one.
}
