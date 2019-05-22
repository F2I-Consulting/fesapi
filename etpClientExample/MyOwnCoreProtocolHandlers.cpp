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

#include "MyOwnDiscoveryProtocolHandlers.h"
#include "MyOwnEtpPlainClientSession.h"
#ifdef WITH_ETP_SSL
#include "ssl/MyOwnEtpSslClientSession.h"
#endif

#include "etp/EtpHdfProxy.h"
#include "etp/EtpHelpers.h"

#include <resqml2_0_1/LocalDepth3dCrs.h>
#include <resqml2_0_1/IjkGridExplicitRepresentation.h>
#include <resqml2_0_1/ContinuousPropertySeries.h>

void setSessionToEtpHdfProxy(ETP_NS::AbstractSession* myOwnEtpSession) {
	COMMON_NS::EpcDocument& epcDoc = dynamic_cast<MyOwnEtpClientSessionEpcBased*>(myOwnEtpSession)->epcDoc;
	for (const auto & hdfProxy : epcDoc.getHdfProxySet())
	{
		ETP_NS::EtpHdfProxy* etpHdfProxy = dynamic_cast<ETP_NS::EtpHdfProxy*>(hdfProxy);
		if (etpHdfProxy != nullptr && etpHdfProxy->getSession() == nullptr) {
			if (dynamic_cast<MyOwnEtpPlainClientSession*>(myOwnEtpSession) != nullptr) {
				etpHdfProxy->setSession(myOwnEtpSession->getIoContext(),
					static_cast<MyOwnEtpPlainClientSession*>(myOwnEtpSession)->getHost(),
					static_cast<MyOwnEtpPlainClientSession*>(myOwnEtpSession)->getPort(),
					static_cast<MyOwnEtpPlainClientSession*>(myOwnEtpSession)->getTarget());
			}
#ifdef WITH_ETP_SSL
			else if (dynamic_cast<MyOwnEtpSslClientSession*>(myOwnEtpSession) != nullptr) {
				etpHdfProxy->setSession(myOwnEtpSession->getIoContext(),
					static_cast<MyOwnEtpSslClientSession*>(myOwnEtpSession)->getHost(),
					static_cast<MyOwnEtpSslClientSession*>(myOwnEtpSession)->getPort(),
					static_cast<MyOwnEtpSslClientSession*>(myOwnEtpSession)->getTarget());
			}
#endif
		}
	}
}

void printHelp()
{
	std::cout << "List of available commands :" << std::endl;
	std::cout << "\tList" << std::endl << "\t\tList the objects which have been got from ETP to the in-memory epc" << std::endl << std::endl;
	std::cout << "\tGetTreeResources dataObjectURI depth(default 1) getObject(true or false, default is false) contentTypeFilter,contentTypeFilter,...(default noFilter)" << std::endl << std::endl;
	std::cout << "\tGetGraphResources dataObjectURI scope(default self) depth(default 1) getObject(true or false, default is false) contentTypeFilter,contentTypeFilter,...(default noFilter)" << std::endl << std::endl;
	std::cout << "\tGetDataObject dataObjectURI,dataObjectURI,..." << std::endl << "\t\tGet the objects from an ETP store and store them into the in memory epc (only create partial TARGET relationships, not any SOURCE relationships)" << std::endl << std::endl;
	std::cout << "\tPutDataObject" << std::endl << "\t\tCreate an IJK Grid on the fly and put/push it to the store" << std::endl << std::endl;
	std::cout << "\tGetSourceObjects dataObjectURI" << std::endl << "\t\tGet the source objects of another object from an ETP store and put it into the in memory epc" << std::endl << std::endl;
	std::cout << "\tGetTargetObjects dataObjectURI" << std::endl << "\t\tGet the target objects of another object from an ETP store and put it into the in memory epc" << std::endl << std::endl;
	std::cout << "\tGetResourceObjects dataObjectURI" << std::endl << "\t\tGet the object, its source and its target objects from an ETP store and put it into the in memory epc" << std::endl << std::endl;
	std::cout << "\tGetDataArray epcExternalPartURI datasetPathInEpcExternalPart" << std::endl << "\t\tGet the numerical values from a dataset included in an EpcExternalPart over ETP." << std::endl << std::endl;
	std::cout << "\tquit" << std::endl << "\t\tQuit the session." << std::endl << std::endl;
}

void askUser(ETP_NS::AbstractSession* session)
{
	std::string buffer;

	std::cout << "What is your command (""quit"" for closing connection)?" << std::endl;
	std::string command;
	while (command != "quit")
	{
		std::getline(std::cin, command);
		auto commandTokens = tokenize(command, ' ');

		if (commandTokens.empty()) {
			printHelp();
			continue;
		}
		if (commandTokens[0] == "quit") {
			continue;
		}
		
		if (commandTokens[0] == "GetTreeResources") {
			Energistics::Etp::v12::Protocol::Discovery::GetTreeResources mb;
			mb.m_context.m_uri = commandTokens[1];
			mb.m_context.m_depth = 1;

			if (commandTokens.size() > 2) {
				mb.m_context.m_depth = std::stoi(commandTokens[2]);

				if (commandTokens.size() > 4) {
					mb.m_context.m_contentTypes = tokenize(commandTokens[4], ',');
				}
			}

			if (commandTokens.size() > 3 && (commandTokens[3] == "true" || commandTokens[3] == "True" || commandTokens[3] == "TRUE")) {
				std::static_pointer_cast<MyOwnDiscoveryProtocolHandlers>(session->getDiscoveryProtocolHandlers())->getObjectWhenDiscovered.push_back(session->send(mb));
			}
			else {
				session->send(mb);
			}
			continue;
		}
		else if (commandTokens[0] == "GetGraphResources") {
			Energistics::Etp::v12::Protocol::Discovery::GetGraphResources mb;
			mb.m_context.m_uri = commandTokens[1];
			mb.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self;
			mb.m_context.m_depth = 1;
			mb.m_groupByType = false;

			if (commandTokens.size() > 2) {
				if (commandTokens[2] == "self")
					mb.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self;
				else if (commandTokens[2] == "sources")
					mb.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources;
				else if (commandTokens[2] == "sourcesOrSelf")
					mb.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf;
				else if (commandTokens[2] == "targets")
					mb.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets;
				else if (commandTokens[2] == "targetsOrSelf")
					mb.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf;

				if (commandTokens.size() > 3) {
					mb.m_context.m_depth = std::stoi(commandTokens[3]);

					if (commandTokens.size() > 5) {
						mb.m_context.m_contentTypes = tokenize(commandTokens[5], ',');
					}
				}
			}

			if (commandTokens.size() > 4) {
				std::static_pointer_cast<MyOwnDiscoveryProtocolHandlers>(session->getDiscoveryProtocolHandlers())->getObjectWhenDiscovered.push_back(session->send(mb));
			}
			else {
				session->send(mb);
			}
			continue;
		}
		else if (commandTokens[0] == "GetDataObject") {
			Energistics::Etp::v12::Protocol::Store::GetDataObjects getO;
			getO.m_uris = tokenize(commandTokens[1], ',');
			session->send(getO);
		}
		else if (commandTokens[0] == "PutDataObject") {
			Energistics::Etp::v12::Protocol::Store::PutDataObjects putDataObjects;
			
			// Fake the creation of an IJK Grid
			COMMON_NS::EpcDocument epcDoc("../../fakeForIjkGrid.epc", COMMON_NS::EpcDocument::OVERWRITE);
			COMMON_NS::AbstractHdfProxy* hdfProxy = epcDoc.createHdfProxy("", "Hdf Proxy", epcDoc.getStorageDirectory(), epcDoc.getName() + ".h5");

			RESQML2_0_1_NS::LocalDepth3dCrs* local3dCrs = epcDoc.createLocalDepth3dCrs("f951f4b7-684a-4c1b-bcd7-bc61d939b328", "Default local CRS", .0, .0, .0, .0, gsoap_resqml2_0_1::eml20__LengthUom__m, 23031, gsoap_resqml2_0_1::eml20__LengthUom__m, "Unknown", false);

			RESQML2_0_1_NS::IjkGridExplicitRepresentation* ijkgrid = epcDoc.createIjkGridExplicitRepresentation(local3dCrs, "", "Put IJK Grid", 2, 1, 1);
			double nodes[48] = { 0, 0, 300, 375, 0, 300, 700, 0, 350, 0, 150, 300, 375, 150, 300, 700, 150, 350, /* SPLIT*/ 375, 0, 350, 375, 150, 350,
				0, 0, 500, 375, 0, 500, 700, 0, 550, 0, 150, 500, 375, 150, 500, 700, 150, 550, /* SPLIT*/ 375, 0, 550, 375, 150, 550 };
			unsigned int pillarOfCoordinateLine[2] = { 1, 4 };
			unsigned int splitCoordinateLineColumnCumulativeCount[2] = { 1, 2 };
			unsigned int splitCoordinateLineColumns[2] = { 1, 1 };
			ijkgrid->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml2__PillarShape__vertical, gsoap_resqml2_0_1::resqml2__KDirection__down, false, nodes, hdfProxy,
				2, pillarOfCoordinateLine, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns);

			Energistics::Etp::v12::Datatypes::Object::DataObject dataObject = ETP_NS::EtpHelpers::buildEtpDataObjectFromEnergisticsObject(ijkgrid);
			putDataObjects.m_dataObjects.push_back(dataObject);

			session->send(putDataObjects, 0, 0x10); // 0x10 requires Acknowledge from the store
		}

		if (commandTokens.size() == 1) {
			if (commandTokens[0] == "GetXyzOfIjkGrids") {
				setSessionToEtpHdfProxy(session);
				COMMON_NS::EpcDocument& epcDoc = dynamic_cast<MyOwnEtpClientSessionEpcBased*>(session)->epcDoc;
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
					std::unique_ptr<double[]> xyzPoints(new double[xyzPointCount * 3]);
					ijkGrid->getXyzPointsOfPatchInGlobalCrs(0, xyzPoints.get());
					for (auto xyzPointIndex = 0; xyzPointIndex < xyzPointCount && xyzPointIndex < 20; ++xyzPointIndex) {
						std::cout << "XYZ Point Index " << xyzPointIndex << " : " << xyzPoints[xyzPointIndex * 3] << "," << xyzPoints[xyzPointIndex * 3 + 1] << "," << xyzPoints[xyzPointIndex * 3 + 2] << std::endl;
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
								for (unsigned int elementIndex = 0; elementIndex < continuousProp->getElementCountPerValue(); ++elementIndex) {
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
			else if (commandTokens[0] == "List") {
				std::cout << "*** START LISTING ***" << std::endl;
				COMMON_NS::EpcDocument& epcDoc = dynamic_cast<MyOwnEtpClientSessionEpcBased*>(session)->epcDoc;
				for (const auto& entryPair : epcDoc.getDataObjectSet()) {
					if (!entryPair.second->isPartial()) {
						std::cout << entryPair.first << " : " << entryPair.second->getTitle() << std::endl;
						std::cout << "*** SOURCE REL ***" << std::endl;
						for (const auto& uuid : entryPair.second->getAllSourceRelationshipUuids()) {
							std::cout << uuid << " : " << epcDoc.getDataObjectByUuid(uuid)->getXmlTag() << std::endl;
						}
						std::cout << "*** TARGET REL ***" << std::endl;
						for (const auto& uuid : entryPair.second->getAllTargetRelationshipUuids()) {
							std::cout << uuid << " : " << epcDoc.getDataObjectByUuid(uuid)->getXmlTag() << std::endl;
						}
						std::cout << std::endl;
					}
					else {
						std::cout << "PARTIAL " << entryPair.first << " : " << entryPair.second->getTitle() << std::endl;
					}
				}
				std::cout << "*** END LISTING ***" << std::endl;
			}
		}
		else if (commandTokens.size() == 2) {
			if (commandTokens[0] == "GetSourceObjects") {
				Energistics::Etp::v12::Protocol::Discovery::GetGraphResources mb;
				mb.m_context.m_uri = commandTokens[1];
				mb.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources;
				mb.m_context.m_depth = 1;
				mb.m_groupByType = false;

				std::static_pointer_cast<MyOwnDiscoveryProtocolHandlers>(session->getDiscoveryProtocolHandlers())->getObjectWhenDiscovered.push_back(session->send(mb));
			}
			else if (commandTokens[0] == "GetTargetObjects") {
				Energistics::Etp::v12::Protocol::Discovery::GetGraphResources mb;
				mb.m_context.m_uri = commandTokens[1];
				mb.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets;
				mb.m_context.m_depth = 1;
				mb.m_groupByType = false;

				std::static_pointer_cast<MyOwnDiscoveryProtocolHandlers>(session->getDiscoveryProtocolHandlers())->getObjectWhenDiscovered.push_back(session->send(mb));
			}
			else if (commandTokens[0] == "GetResourceObjects") {
				Energistics::Etp::v12::Protocol::Discovery::GetGraphResources mb;
				mb.m_context.m_uri = commandTokens[1];
				mb.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf;
				mb.m_context.m_depth = 1;
				mb.m_groupByType = false;
				std::static_pointer_cast<MyOwnDiscoveryProtocolHandlers>(session->getDiscoveryProtocolHandlers())->getObjectWhenDiscovered.push_back(session->send(mb));

				mb.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources;
				std::static_pointer_cast<MyOwnDiscoveryProtocolHandlers>(session->getDiscoveryProtocolHandlers())->getObjectWhenDiscovered.push_back(session->send(mb));
			}
		}
		else if (commandTokens.size() == 3) {
			if (commandTokens[0] == "GetDataArray") {
				Energistics::Etp::v12::Protocol::DataArray::GetDataArrays gda;
				gda.m_dataArrays["0"].m_uri = commandTokens[1];
				gda.m_dataArrays["0"].m_pathInResource = commandTokens[2];
				std::cout << gda.m_dataArrays["0"].m_pathInResource << std::endl;
				session->send(gda);
			}
		}
	}

	session->close();
	dynamic_cast<MyOwnEtpClientSessionEpcBased*>(session)->epcDoc.close();
}

void MyOwnCoreProtocolHandlers::on_OpenSession(const Energistics::Etp::v12::Protocol::Core::OpenSession & os, int64_t correlationId)
{
	dynamic_cast<MyOwnEtpClientSessionEpcBased*>(session)->epcDoc.open("../../fakeForEtpClient.epc", COMMON_NS::EpcDocument::ETP);
	// Ask the user about what he wants to do on another thread
	// The main thread is on reading mode
	std::thread askUserThread(askUser, session);
	askUserThread.detach(); // Detach the thread since we don't want it to be a blocking one.
}
