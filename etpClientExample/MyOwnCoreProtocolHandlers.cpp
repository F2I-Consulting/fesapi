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

#include <etp/EtpHdfProxy.h>
#include <etp/EtpHelpers.h>

#include <resqml2_0_1/LocalDepth3dCrs.h>
#include <resqml2_0_1/IjkGridExplicitRepresentation.h>
#include <resqml2_0_1/ContinuousPropertySeries.h>

#include <tools/GuidTools.h>

#include "MyOwnDiscoveryProtocolHandlers.h"

MyOwnCoreProtocolHandlers::~MyOwnCoreProtocolHandlers() {
}

void printHelp()
{
	std::cout << "List of available commands :" << std::endl;
	std::cout << "\tList" << std::endl << "\t\tList the objects which have been got from ETP to the in-memory epc" << std::endl << std::endl;
	//std::cout << "\tGetDataspaces URI depth(default 1)" << std::endl << std::endl;
	std::cout << "\tGetResources URI scope(default self) depth(default 1) countObjects(true or false, default is true) getObject(true or false, default is false) dataTypeFilter,dataTypeFilter,...(default noFilter)" << std::endl << std::endl;
	std::cout << "\tGetDataObjects dataObjectURI,dataObjectURI,..." << std::endl << "\t\tGet the objects from an ETP store and store them into the in memory epc (only create partial TARGET relationships, not any SOURCE relationships)" << std::endl << std::endl;
	std::cout << "\tPutDataObject" << std::endl << "\t\tCreate an IJK Grid on the fly and put/push it to the store" << std::endl << std::endl;
	std::cout << "\tGetSourceObjects dataObjectURI" << std::endl << "\t\tGet the source objects of another object from an ETP store and put it into the in memory epc" << std::endl << std::endl;
	std::cout << "\tGetTargetObjects dataObjectURI" << std::endl << "\t\tGet the target objects of another object from an ETP store and put it into the in memory epc" << std::endl << std::endl;
	std::cout << "\tGetResourceObjects dataObjectURI" << std::endl << "\t\tGet the object, its source and its target objects from an ETP store and put it into the in memory epc" << std::endl << std::endl;
	std::cout << "\tGetDataArrays epcExternalPartURI datasetPathInEpcExternalPart" << std::endl << "\t\tGet the numerical values from a dataset included in an EpcExternalPart over ETP." << std::endl << std::endl;
	std::cout << "\tSubscribeNotif URI scope(default self) depth(default 1) receiveXML(true or false, default is true) startTime(default is now) dataTypeFilter,dataTypeFilter,...(default noFilter)" << std::endl << "\t\tSubscribe to notifications." << std::endl << std::endl;
	std::cout << "\tquit" << std::endl << "\t\tQuit the session." << std::endl << std::endl;
}

void askUser(std::shared_ptr<ETP_NS::AbstractSession> session, COMMON_NS::DataObjectRepository* repo)
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
		
		/*
		if (commandTokens[0] == "GetDataspaces") {
			Energistics::Etp::v12::Protocol::Discovery::GetDataspaces mb;
			mb.m_uri = commandTokens[1];
			mb.m_depth = 1;
			if (commandTokens.size() > 2) {
				mb.m_depth = std::stoi(commandTokens[2]);
			}
			session->send(mb);
			continue;
		}
		else*/
		if (commandTokens[0] == "GetResources") {
			Energistics::Etp::v12::Protocol::Discovery::GetResources mb;
			mb.m_context.m_uri = commandTokens[1];
			mb.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self;
			mb.m_context.m_depth = 1;
			mb.m_countObjects = true;

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

					if (commandTokens.size() > 4) {
						if (commandTokens[4] == "false" || commandTokens[4] == "False" || commandTokens[4] == "FALSE") {
							mb.m_countObjects = false;
						}

						if (commandTokens.size() > 6) {
							mb.m_context.m_dataObjectTypes = tokenize(commandTokens[6], ',');
						}
					}
				}
			}

			if (commandTokens.size() > 5 && (commandTokens[5] == "true" || commandTokens[5] == "True" || commandTokens[5] == "TRUE")) {
				std::static_pointer_cast<MyOwnDiscoveryProtocolHandlers>(session->getDiscoveryProtocolHandlers())->getObjectWhenDiscovered.push_back(session->send(mb));
			}
			else {
				session->send(mb);
			}
			continue;
		}
		else if (commandTokens[0] == "GetDataObjects") {
			Energistics::Etp::v12::Protocol::Store::GetDataObjects getO;
			std::vector<std::string> tokens = tokenize(commandTokens[1], ',');
			std::map<std::string, std::string> tokenMaps;
			for (size_t i = 0; i < tokens.size(); ++i) {
				tokenMaps[std::to_string(i)] = tokens[i];
			}
			getO.m_uris = tokenMaps;
			session->send(getO);
		}
		else if (commandTokens[0] == "PutDataObject") {
			Energistics::Etp::v12::Protocol::Store::PutDataObjects putDataObjects;
			
			// Fake the creation of an IJK Grid
			COMMON_NS::DataObjectRepository repo;
			COMMON_NS::AbstractHdfProxy* hdfProxy = repo.createHdfProxy("", "Hdf Proxy", "../..", "fakeForIjkGrid.h5", COMMON_NS::DataObjectRepository::openingMode::OVERWRITE);
			repo.setDefaultHdfProxy(hdfProxy);

			RESQML2_0_1_NS::LocalDepth3dCrs* local3dCrs = repo.createLocalDepth3dCrs("f951f4b7-684a-4c1b-bcd7-bc61d939b328", "Default local CRS", .0, .0, .0, .0, gsoap_resqml2_0_1::eml20__LengthUom__m, 23031, gsoap_resqml2_0_1::eml20__LengthUom__m, "Unknown", false);
			repo.setDefaultCrs(local3dCrs);

			RESQML2_0_1_NS::IjkGridExplicitRepresentation* ijkgrid = repo.createIjkGridExplicitRepresentation("", "Put IJK Grid", 2, 1, 1);
			double nodes[48] = { 0, 0, 300, 375, 0, 300, 700, 0, 350, 0, 150, 300, 375, 150, 300, 700, 150, 350, /* SPLIT*/ 375, 0, 350, 375, 150, 350,
				0, 0, 500, 375, 0, 500, 700, 0, 550, 0, 150, 500, 375, 150, 500, 700, 150, 550, /* SPLIT*/ 375, 0, 550, 375, 150, 550 };
			unsigned int pillarOfCoordinateLine[2] = { 1, 4 };
			unsigned int splitCoordinateLineColumnCumulativeCount[2] = { 1, 2 };
			unsigned int splitCoordinateLineColumns[2] = { 1, 1 };
			ijkgrid->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape__vertical, gsoap_resqml2_0_1::resqml20__KDirection__down, false, nodes, hdfProxy,
				2, pillarOfCoordinateLine, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns);

			Energistics::Etp::v12::Datatypes::Object::DataObject dataObject = ETP_NS::EtpHelpers::buildEtpDataObjectFromEnergisticsObject(ijkgrid);
			putDataObjects.m_dataObjects["0"] = dataObject;

			session->send(putDataObjects, 0, 0x10); // 0x10 requires Acknowledge from the store
		}
		else if (commandTokens[0] == "SubscribeNotif") {
			Energistics::Etp::v12::Protocol::StoreNotification::SubscribeNotifications mb;
			mb.m_request.m_context.m_uri = commandTokens[1];
			mb.m_request.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self;
			mb.m_request.m_context.m_depth = 1;
			mb.m_request.m_startTime = std::time(nullptr);
			mb.m_request.m_requestUuid.m_array = GuidTools::generateUidAsByteArray();

			if (commandTokens.size() > 2) {
				if (commandTokens[2] == "self")
					mb.m_request.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self;
				else if (commandTokens[2] == "sources")
					mb.m_request.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources;
				else if (commandTokens[2] == "sourcesOrSelf")
					mb.m_request.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf;
				else if (commandTokens[2] == "targets")
					mb.m_request.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets;
				else if (commandTokens[2] == "targetsOrSelf")
					mb.m_request.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf;

				if (commandTokens.size() > 3) {
					mb.m_request.m_context.m_depth = std::stoi(commandTokens[3]);

					if (commandTokens.size() > 4) {
						mb.m_request.m_includeObjectData = commandTokens[4] == "true";

						if (commandTokens.size() > 5) {
							if (commandTokens[5] != "now") {
								mb.m_request.m_startTime = std::stoll(commandTokens[5]);
							}

							if (commandTokens.size() > 6) {
								mb.m_request.m_context.m_dataObjectTypes = tokenize(commandTokens[6], ',');
							}
						}
					}
				}
			}

			session->send(mb);

			continue;
		}

		if (commandTokens.size() == 1) {
			if (commandTokens[0] == "GetXyzOfIjkGrids") {
				//setSessionToEtpHdfProxy(session);
				auto ijkGridSet = repo->getIjkGridRepresentationSet();
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
						RESQML2_0_1_NS::ContinuousProperty const * continuousProp = dynamic_cast<RESQML2_0_1_NS::ContinuousProperty const *>(prop);
						if (continuousProp != nullptr && dynamic_cast<RESQML2_0_1_NS::ContinuousPropertySeries const *>(continuousProp) == nullptr &&
							continuousProp->getAttachmentKind() == gsoap_resqml2_0_1::resqml20__IndexableElements::resqml20__IndexableElements__cells) {
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
				for (const auto& entryPair : repo->getDataObjects()) {
					for (const auto obj : entryPair.second) {
						if (!obj->isPartial()) {
							std::cout << entryPair.first << " : " << obj->getTitle() << std::endl;
							std::cout << "*** SOURCE REL ***" << std::endl;
							for (auto srcObj : obj->getRepository()->getSourceObjects(obj)) {
								std::cout << srcObj->getUuid() << " : " << srcObj->getXmlTag() << std::endl;
							}
							std::cout << "*** TARGET REL ***" << std::endl;
							for (auto targetObj : obj->getRepository()->getTargetObjects(obj)) {
								std::cout << targetObj->getUuid() << " : " << targetObj->getXmlTag() << std::endl;
							}
							std::cout << std::endl;
						}
						else {
							std::cout << "PARTIAL " << entryPair.first << " : " << obj->getTitle() << std::endl;
						}
					}
				}
				std::cout << "*** END LISTING ***" << std::endl;
			}
		}
		else if (commandTokens.size() == 2) {
			if (commandTokens[0] == "GetSourceObjects") {
				Energistics::Etp::v12::Protocol::Discovery::GetResources mb;
				mb.m_context.m_uri = commandTokens[1];
				mb.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources;
				mb.m_context.m_depth = 1;

				std::static_pointer_cast<MyOwnDiscoveryProtocolHandlers>(session->getDiscoveryProtocolHandlers())->getObjectWhenDiscovered.push_back(session->send(mb));
			}
			else if (commandTokens[0] == "GetTargetObjects") {
				Energistics::Etp::v12::Protocol::Discovery::GetResources mb;
				mb.m_context.m_uri = commandTokens[1];
				mb.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets;
				mb.m_context.m_depth = 1;

				std::static_pointer_cast<MyOwnDiscoveryProtocolHandlers>(session->getDiscoveryProtocolHandlers())->getObjectWhenDiscovered.push_back(session->send(mb));
			}
			else if (commandTokens[0] == "GetResourceObjects") {
				Energistics::Etp::v12::Protocol::Discovery::GetResources mb;
				mb.m_context.m_uri = commandTokens[1];
				mb.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf;
				mb.m_context.m_depth = 1;
				std::static_pointer_cast<MyOwnDiscoveryProtocolHandlers>(session->getDiscoveryProtocolHandlers())->getObjectWhenDiscovered.push_back(session->send(mb));

				mb.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources;
				std::static_pointer_cast<MyOwnDiscoveryProtocolHandlers>(session->getDiscoveryProtocolHandlers())->getObjectWhenDiscovered.push_back(session->send(mb));
			}
		}
		else if (commandTokens.size() == 3) {
			if (commandTokens[0] == "GetDataArrays") {
				Energistics::Etp::v12::Protocol::DataArray::GetDataArrays gda;
				gda.m_dataArrays["0"].m_uri = commandTokens[1];
				gda.m_dataArrays["0"].m_pathInResource = commandTokens[2];
				std::cout << gda.m_dataArrays["0"].m_pathInResource << std::endl;
				session->send(gda);
			}
		}
	}

	session->close();
}

void MyOwnCoreProtocolHandlers::on_OpenSession(const Energistics::Etp::v12::Protocol::Core::OpenSession & os, int64_t correlationId)
{
	// Ask the user about what he wants to do on another thread
	// The main thread is on reading mode
	std::thread askUserThread(askUser, session, repo);
	askUserThread.detach(); // Detach the thread since we don't want it to be a blocking one.
}
