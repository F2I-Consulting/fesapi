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

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <common/EpcDocument.h>

#include <etp/EtpHdfProxy.h>
#include <etp/EtpHelpers.h>
#include <etp/PlainClientSession.h>

#include <resqml2/ContinuousProperty.h>
#include <resqml2/IjkGridExplicitRepresentation.h>
#include <resqml2/PointSetRepresentation.h>

#include <resqml2_0_1/LocalDepth3dCrs.h>

#include "MyOwnDiscoveryProtocolHandlers.h"
#include "MyOwnStoreProtocolHandlers.h"

void printHelp()
{
	std::cout << "List of available commands :" << std::endl;
	std::cout << "\tPing" << std::endl << "\t\tPing the server" << std::endl << std::endl;
	std::cout << "\tList" << std::endl << "\t\tList the objects which have been got from ETP to the in-memory epc" << std::endl << std::endl;
	std::cout << "\tPutXmldAndHdfAtOnce" << std::endl << "\t\tPut a dummy point set representation to the store sending XML and HDF5 points at once." << std::endl << std::endl;
	std::cout << "\tGetResources URI scope(default self) depth(default 1) countObjects(true or false, default is true) getObject(true or false, default is false) dataTypeFilter,dataTypeFilter,...(default noFilter)" << std::endl << std::endl;
	std::cout << "\tGetDataObjects dataObjectURI,dataObjectURI,..." << std::endl << "\t\tGet the objects from an ETP store and store them into the in memory epc (only create partial TARGET relationships, not any SOURCE relationships)" << std::endl << std::endl;
	std::cout << "\tGetXYZPoints URI" << std::endl << "\t\tGet the XYZ points of a rep from store and print some of them." << std::endl << std::endl;
	std::cout << "\tPutDataObject UUID" << std::endl << "\t\tPut the XML part of a dataobject which is on the client side (use \"Load\" command to laod some dataobjects on client side) to the store" << std::endl << std::endl;
	std::cout << "\tGetSourceObjects dataObjectURI" << std::endl << "\t\tGet the source objects of another object from an ETP store and put it into the in memory epc" << std::endl << std::endl;
	std::cout << "\tGetTargetObjects dataObjectURI" << std::endl << "\t\tGet the target objects of another object from an ETP store and put it into the in memory epc" << std::endl << std::endl;
	std::cout << "\tGetResourceObjects dataObjectURI" << std::endl << "\t\tGet the object, its source and its target objects from an ETP store and put it into the in memory epc" << std::endl << std::endl;
	std::cout << "\tGetDataArray epcExternalPartURI datasetPathInEpcExternalPart" << std::endl << "\t\tGet the numerical values from a dataset included in an EpcExternalPart over ETP." << std::endl << std::endl;
	std::cout << "\tPutDataArray epcExternalPartURI datasetPathInEpcExternalPart" << std::endl << "\t\tPut a dummy {0,1,2,3,4,5,6,7,8,9} integer array in a particular store epcExternalPartURI at a particular dataset path" << std::endl << std::endl;
	std::cout << "\tSubscribeNotif URI scope(default self) depth(default 1) receiveXML(true or false, default is true) startTime(default is now) dataTypeFilter,dataTypeFilter,...(default noFilter)" << std::endl << "\t\tSubscribe to notifications." << std::endl << std::endl;
	std::cout << "\tLoad epcDocument" << std::endl << "\t\tLoad an EPC document into the DataObjectRepository." << std::endl << std::endl;
	std::cout << "\tquit" << std::endl << "\t\tQuit the session." << std::endl << std::endl;
}

void askUser(ETP_NS::AbstractSession* session, COMMON_NS::DataObjectRepository* repo)
{
	std::string buffer;

	std::cout << "What is your command (\"quit\" for closing connection)?" << std::endl;
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
			
		if (commandTokens[0] == "Load") {
			COMMON_NS::EpcDocument epcDoc(commandTokens[1]);
			epcDoc.deserializeInto(*repo);
			std::cout << "LOADED!" << std::endl;
			continue;
		}
		else if (commandTokens[0] == "GetResources") {
			Energistics::Etp::v12::Protocol::Discovery::GetResources mb;
			mb.context.uri = commandTokens[1];
			mb.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self;
			mb.context.depth = 1;
			mb.context.navigableEdges = Energistics::Etp::v12::Datatypes::Object::RelationshipKind::Primary;
			mb.countObjects = true;

			if (commandTokens.size() > 2) {
				if (commandTokens[2] == "self")
					mb.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self;
				else if (commandTokens[2] == "sources")
					mb.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources;
				else if (commandTokens[2] == "sourcesOrSelf")
					mb.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf;
				else if (commandTokens[2] == "targets")
					mb.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets;
				else if (commandTokens[2] == "targetsOrSelf")
					mb.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf;

				if (commandTokens.size() > 3) {
					mb.context.depth = std::stoi(commandTokens[3]);

					if (commandTokens.size() > 4) {
						if (commandTokens[4] == "false" || commandTokens[4] == "False" || commandTokens[4] == "FALSE") {
							mb.countObjects = false;
						}

						if (commandTokens.size() > 6) {
							mb.context.dataObjectTypes = tokenize(commandTokens[6], ',');
						}
					}
				}
			}

			if (commandTokens.size() > 5 && (commandTokens[5] == "true" || commandTokens[5] == "True" || commandTokens[5] == "TRUE")) {
				std::static_pointer_cast<MyOwnDiscoveryProtocolHandlers>(session->getDiscoveryProtocolHandlers())->getObjectWhenDiscovered.push_back(session->send(mb, 0, 0x02));
			}
			else {
				session->send(mb, 0, 0x02);
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
			getO.uris = tokenMaps;
			session->send(getO, 0, 0x02);
		}
		else if (commandTokens[0] == "GetXYZPoints") {
			/* This works in a blocking way i.e. getXyzPointCountOfPatch will return only when the store would have answered back.
			HDF proxy factory and custom HDF proxy are used for that. See main.cpp for setting the custom HDF proxy factory.
			You should also look at MyOwnStoreProtocolHandlers::on_GetDataObjectsResponse which allows to set the session information to the HDF proxy.
			We could have hard set those information thanks to HDF proxy factory.

			If you would want non blocking approach, please see GetDataArrays which require more work to fill in the arguments.
			*/
			std::string uuid = commandTokens[1].substr(commandTokens[1].find("(") + 1, 36);
			auto* rep = repo->getDataObjectByUuid<RESQML2_NS::AbstractRepresentation>(uuid);
			if (rep == nullptr) {
				std::cerr << " The URI " << commandTokens[1] << " does not correspond to a representation which is on client side. Please get first this dataobject from the store before to call GetXYZPoints on it." << std::endl;
				continue;
			}
			auto xyzPointCount = rep->getXyzPointCountOfPatch(0);
			std::unique_ptr<double[]> xyzPoints(new double[xyzPointCount * 3]);
			rep->getXyzPointsOfPatch(0, xyzPoints.get());
			for (auto xyzPointIndex = 0; xyzPointIndex < xyzPointCount && xyzPointIndex < 20; ++xyzPointIndex) {
				std::cout << "XYZ Point Index " << xyzPointIndex << " : " << xyzPoints[xyzPointIndex * 3] << "," << xyzPoints[xyzPointIndex * 3 + 1] << "," << xyzPoints[xyzPointIndex * 3 + 2] << std::endl;
			}
		}
		else if (commandTokens[0] == "PutDataObject") {		
			auto* dataObj = repo->getDataObjectByUuid(commandTokens[1]);
			if (dataObj != nullptr) {
				Energistics::Etp::v12::Protocol::Store::PutDataObjects putDataObjects;
				Energistics::Etp::v12::Datatypes::Object::DataObject dataObject = ETP_NS::EtpHelpers::buildEtpDataObjectFromEnergisticsObject(dataObj);
				putDataObjects.dataObjects["0"] = dataObject;

				session->send(putDataObjects, 0, 0x10 | 0x02); // 0x10 requires Acknowledge from the store
			}			
		}
		else if (commandTokens[0] == "SubscribeNotif") {
			Energistics::Etp::v12::Protocol::StoreNotification::SubscribeNotifications mb;
			Energistics::Etp::v12::Datatypes::Object::SubscriptionInfo subscriptionInfo;
			subscriptionInfo.context.uri = commandTokens[1];
			subscriptionInfo.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self;
			subscriptionInfo.context.depth = 1;
			subscriptionInfo.startTime = std::time(nullptr);
			boost::uuids::random_generator gen;
			boost::uuids::uuid uuid = gen();
			std::move(std::begin(uuid.data), std::end(uuid.data), subscriptionInfo.requestUuid.array.begin());

			if (commandTokens.size() > 2) {
				if (commandTokens[2] == "self")
					subscriptionInfo.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self;
				else if (commandTokens[2] == "sources")
					subscriptionInfo.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources;
				else if (commandTokens[2] == "sourcesOrSelf")
					subscriptionInfo.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf;
				else if (commandTokens[2] == "targets")
					subscriptionInfo.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets;
				else if (commandTokens[2] == "targetsOrSelf")
					subscriptionInfo.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf;

				if (commandTokens.size() > 3) {
					subscriptionInfo.context.depth = std::stoi(commandTokens[3]);

					if (commandTokens.size() > 4) {
						subscriptionInfo.includeObjectData = commandTokens[4] == "true";

						if (commandTokens.size() > 5) {
							if (commandTokens[5] != "now") {
								subscriptionInfo.startTime = std::stoll(commandTokens[5]);
							}

							if (commandTokens.size() > 6) {
								subscriptionInfo.context.dataObjectTypes = tokenize(commandTokens[6], ',');
							}
						}
					}
				}
			}

			mb.request["0"] = subscriptionInfo;

			session->send(mb, 0, 0x02);

			continue;
		}

		if (commandTokens.size() == 1) {
			if (commandTokens[0] == "Ping") {
				Energistics::Etp::v12::Protocol::Core::Ping ping;
				ping.currentDateTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
				session->send(ping, 0, 0x02); // 0x10 requires Acknowledge from the store
				std::cout << "PING at " << ping.currentDateTime << std::endl;
			}
			else if (commandTokens[0] == "List") {
				std::cout << "*** START LISTING ***" << std::endl;
				for (const auto& entryPair : repo->getDataObjects()) {
					for (const auto* obj : entryPair.second) {
						if (!obj->isPartial()) {
							std::cout << "******************" << entryPair.first << " : " << obj->getTitle() << "******************" << std::endl;
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
			else if (commandTokens[0] == "PutXmldAndHdfAtOnce") {
				// Create the point set representation, an ETP HDF proxy if necessary and a partial crs
				RESQML2_NS::PointSetRepresentation* h1i1PointSetRep = repo->createPointSetRepresentation("", "Horizon1 Interp1 PointSetRep");
				auto* crs = repo->createPartial<RESQML2_0_1_NS::LocalDepth3dCrs>("", "");
				if (repo->getDefaultHdfProxy() == nullptr) {
					auto* etpHdfProxy = repo->createHdfProxy("", "", "", "", COMMON_NS::DataObjectRepository::openingMode::READ_WRITE);
					auto* plainClientSession = dynamic_cast<ETP_NS::PlainClientSession*>(session);
					if (plainClientSession != nullptr) {
						(dynamic_cast<ETP_NS::EtpHdfProxy*>(etpHdfProxy))->setSession(plainClientSession->getIoContext(), plainClientSession->getHost(), plainClientSession->getPort(), plainClientSession->getTarget());
					}
					repo->setDefaultHdfProxy(etpHdfProxy);
				}

				// Create and push the numeical values to the store
				// Internally it uses the ETP Hdf proxy set as the default HDF proxy of the repository in main.cpp.
				// pushBackGeometryPatch is a blocking method. If you want non blopcking method, you need to use PutDataArray directly.
				double pointCoords[18] = { 10, 70, 301, 11, 21, 299, 150, 30, 301, 400, 0, 351, 450, 75, 340, 475, 100, 350 };
				h1i1PointSetRep->pushBackGeometryPatch(6, pointCoords, nullptr, crs);

				// Now send the XML part
				Energistics::Etp::v12::Protocol::Store::PutDataObjects putDataObjects;
				Energistics::Etp::v12::Datatypes::Object::DataObject dataObject = ETP_NS::EtpHelpers::buildEtpDataObjectFromEnergisticsObject(h1i1PointSetRep);
				putDataObjects.dataObjects["0"] = dataObject;

				session->send(putDataObjects, 0, 0x02 | 0x10); // 0x10 requires Acknowledge from the store
			}
		}
		else if (commandTokens.size() == 2) {
			if (commandTokens[0] == "GetSourceObjects") {
				Energistics::Etp::v12::Protocol::Discovery::GetResources mb;
				mb.context.uri = commandTokens[1];
				mb.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources;
				mb.context.depth = 1;
				mb.context.navigableEdges = Energistics::Etp::v12::Datatypes::Object::RelationshipKind::Primary;
				mb.countObjects = true;

				std::static_pointer_cast<MyOwnDiscoveryProtocolHandlers>(session->getDiscoveryProtocolHandlers())->getObjectWhenDiscovered.push_back(session->send(mb, 0, 0x02));
			}
			else if (commandTokens[0] == "GetTargetObjects") {
				Energistics::Etp::v12::Protocol::Discovery::GetResources mb;
				mb.context.uri = commandTokens[1];
				mb.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets;
				mb.context.depth = 1;
				mb.context.navigableEdges = Energistics::Etp::v12::Datatypes::Object::RelationshipKind::Primary;
				mb.countObjects = true;

				std::static_pointer_cast<MyOwnDiscoveryProtocolHandlers>(session->getDiscoveryProtocolHandlers())->getObjectWhenDiscovered.push_back(session->send(mb, 0, 0x02));
			}
			else if (commandTokens[0] == "GetResourceObjects") {
				Energistics::Etp::v12::Protocol::Discovery::GetResources mb;
				mb.context.uri = commandTokens[1];
				mb.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf;
				mb.context.depth = 1;
				mb.context.navigableEdges = Energistics::Etp::v12::Datatypes::Object::RelationshipKind::Primary;
				mb.countObjects = true;
				std::static_pointer_cast<MyOwnDiscoveryProtocolHandlers>(session->getDiscoveryProtocolHandlers())->getObjectWhenDiscovered.push_back(session->send(mb, 0, 0x02));

				mb.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources;
				std::static_pointer_cast<MyOwnDiscoveryProtocolHandlers>(session->getDiscoveryProtocolHandlers())->getObjectWhenDiscovered.push_back(session->send(mb, 0, 0x02));
			}
		}
		else if (commandTokens.size() == 3) {
			if (commandTokens[0] == "GetDataArray") {
				Energistics::Etp::v12::Protocol::DataArray::GetDataArrays gda;
				gda.dataArrays["0"].uri = commandTokens[1];
				gda.dataArrays["0"].pathInResource = commandTokens[2];
				std::cout << gda.dataArrays["0"].pathInResource << std::endl;
				session->send(gda);
			}
			else if (commandTokens[0] == "PutDataArray") {
				Energistics::Etp::v12::Protocol::DataArray::PutDataArrays pda;
				pda.dataArrays["0"].uid.uri = commandTokens[1];
				pda.dataArrays["0"].uid.pathInResource = commandTokens[2];

				std::vector<int64_t> dimensions = { 10 };
				pda.dataArrays["0"].array.dimensions = dimensions;

				Energistics::Etp::v12::Datatypes::AnyArray data;
				Energistics::Etp::v12::Datatypes::ArrayOfInt arrayOfInt;
				arrayOfInt.values = { 0,1,2,3,4,5,6,7,8,9 };
				data.item.set_ArrayOfInt(arrayOfInt);
				pda.dataArrays["0"].array.data = data;

				session->send(pda, 0, 0x02);
			}
		}
	}

	for (auto* hdfProxy : repo->getHdfProxySet()) {
		hdfProxy->close();
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
