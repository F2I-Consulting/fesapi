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
#include "MyOwnDirectedDiscoveryProtocolHandlers.h"

#include "resqml2_0_1/TriangulatedSetRepresentation.h"
#include "resqml2_0_1/Grid2dRepresentation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "resqml2_0_1/IjkGridParametricRepresentation.h"

void MyOwnDirectedDiscoveryProtocolHandlers::on_GetContent(const Energistics::Etp::v12::Protocol::DirectedDiscovery::GetContent & gc, int64_t correlationId)
{
	if (!validateUri(gc.m_uri)) {
		Energistics::Etp::v12::Protocol::Core::ProtocolException error;
		error.m_errorCode = 9;
		error.m_errorMessage = "The URI " + gc.m_uri + "  is invalid.";

		session->send(error);
		return;
	}

	std::cout << "received uri : " << gc.m_uri << std::endl;

	Energistics::Etp::v12::Protocol::DirectedDiscovery::GetResourcesResponse mb;
	Energistics::Etp::v12::Datatypes::Object::GraphResource resource;
	resource.m_channelSubscribable = false;
	resource.m_objectNotifiable = false;
	resource.m_contentType = "";
	if (gc.m_uri == "eml://") {
		// RESQML2.0
		resource.m_uri = gc.m_uri + "resqml20";
		resource.m_name = "RESQML2.0 Protocol";
		resource.m_resourceType = "UriProtocol";
		resource.m_sourceCount = -1;
		resource.m_targetCount = -1;
		resource.m_contentCount = 4; // the four supported RESQML dataobject type
		mb.m_resource = resource;
		session->send(mb, correlationId, 0x01);

		// EML2.0
		resource.m_uri = gc.m_uri + "eml20";
		resource.m_name = "EML2.0 Protocol";
		resource.m_contentCount = 1; // Hdf Proxy
		mb.m_resource = resource;
		session->send(mb, correlationId, 0x01 | 0x02);

		return;
	}

	std::string path = gc.m_uri.substr(6);
	if (path == "resqml20" || path == "resqml20/") {
		resource.m_resourceType = "Folder";
		resource.m_sourceCount = -1;
		resource.m_targetCount = -1;

		// Triangulated Set Representation
		resource.m_uri = gc.m_uri + "resqml20/" + resqml2_0_1::TriangulatedSetRepresentation::XML_TAG;
		resource.m_name = resqml2_0_1::TriangulatedSetRepresentation::XML_TAG;
		resource.m_name +=" Folder";
		resource.m_contentCount = static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getAllTriangulatedSetRepSet().size();
		mb.m_resource = resource;
		session->send(mb, correlationId, 0x01);

		// Grid 2d Representation
		resource.m_uri = gc.m_uri + "resqml20/" + resqml2_0_1::Grid2dRepresentation::XML_TAG;
		resource.m_name = resqml2_0_1::Grid2dRepresentation::XML_TAG ;
		resource.m_name +=" Folder";
		resource.m_contentCount = static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getHorizonGrid2dRepSet().size();
		mb.m_resource = resource;
		session->send(mb, correlationId, 0x01);

		// Wellbore trajectory
		resource.m_uri = gc.m_uri + "resqml20/" + resqml2_0_1::WellboreTrajectoryRepresentation::XML_TAG;
		resource.m_name = resqml2_0_1::WellboreTrajectoryRepresentation::XML_TAG;
		resource.m_name +=" Folder";
		resource.m_contentCount = static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getWellboreTrajectoryRepresentationSet().size();
		mb.m_resource = resource;
		session->send(mb, correlationId, 0x01);

		// IJK Grid
		resource.m_uri = gc.m_uri + "resqml20/" + resqml2_0_1::AbstractIjkGridRepresentation::XML_TAG;
		resource.m_name = resqml2_0_1::AbstractIjkGridRepresentation::XML_TAG;
		resource.m_name +=" Folder";
		resource.m_contentCount = static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getIjkGridRepresentationSet().size();
		mb.m_resource = resource;
		session->send(mb, correlationId, 0x01 | 0x02);

	}
	else if (path == "eml20" || path == "eml20/") {
		// HDF proxy
		Energistics::Etp::v12::Protocol::Core::ProtocolException error;
		error.m_errorCode = 9;
		error.m_errorMessage = "HDF proxies are not supported yet.";

		session->send(error);
		return;
	}
	else {
		// Tokenize
		std::vector<std::string> tokens;
		std::stringstream ss(path);
		std::string token;
		while(getline(ss, token, '/')) {
			tokens.push_back(token);
		}

		if (tokens[0] != "resqml20" && tokens[0] != "eml20") {
			Energistics::Etp::v12::Protocol::Core::ProtocolException error;
			error.m_errorCode = 9;
			error.m_errorMessage = "The URI " + gc.m_uri + "  uses some dataspaces. This agent does not support dataspace.";

			session->send(error);
			return;
		}

		if (tokens.size() == 2) {
			resource.m_contentCount = -1;
			if (tokens[1] == resqml2_0_1::TriangulatedSetRepresentation::XML_TAG) {
				resource.m_contentType = "application/x-resqml+xml;version=2.0;type=obj_";
				resource.m_contentType += resqml2_0_1::TriangulatedSetRepresentation::XML_TAG;
				auto repSet = static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getAllTriangulatedSetRepSet();
				for (auto i = 0; i < repSet.size(); ++i) {
					resource.m_uri = gc.m_uri + "resqml20/" + resqml2_0_1::TriangulatedSetRepresentation::XML_TAG + "(" + repSet[i]->getUuid() + ")";
					resource.m_name = repSet[i]->getTitle();
					resource.m_lastChanged = repSet[i]->getLastUpdate() == -1 ? repSet[i]->getCreation() : repSet[i]->getLastUpdate();
					resource.m_sourceCount = repSet[i]->getAllSourceRelationships().size();
					resource.m_targetCount = repSet[i]->getAllTargetRelationships().size();
					mb.m_resource = resource;
					session->send(mb, correlationId, i == repSet.size() - 1 ? (0x01 | 0x02) : 0x01);
				}
			}
			else if (tokens[1] == resqml2_0_1::Grid2dRepresentation::XML_TAG) {
				resource.m_contentType = "application/x-resqml+xml;version=2.0;type=obj_";
				resource.m_contentType += resqml2_0_1::Grid2dRepresentation::XML_TAG;
				auto repSet = static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getHorizonGrid2dRepSet();
				for (auto i = 0; i < repSet.size(); ++i) {
					resource.m_uri = gc.m_uri + "resqml20/" + resqml2_0_1::Grid2dRepresentation::XML_TAG + "(" + repSet[i]->getUuid() + ")";
					resource.m_name = repSet[i]->getTitle();
					resource.m_lastChanged = repSet[i]->getLastUpdate() == -1 ? repSet[i]->getCreation() : repSet[i]->getLastUpdate();
					resource.m_sourceCount = repSet[i]->getAllSourceRelationships().size();
					resource.m_targetCount = repSet[i]->getAllTargetRelationships().size();
					mb.m_resource = resource;
					session->send(mb, correlationId, i == repSet.size() - 1 ? (0x01 | 0x02) : 0x01);
				}
			}
			else if (tokens[1] == resqml2_0_1::WellboreTrajectoryRepresentation::XML_TAG) {
				resource.m_contentType = "application/x-resqml+xml;version=2.0;type=obj_";
				resource.m_contentType += resqml2_0_1::WellboreTrajectoryRepresentation::XML_TAG;
				auto repSet = static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getWellboreTrajectoryRepresentationSet();
				for (auto i = 0; i < repSet.size(); ++i) {
					resource.m_uri = gc.m_uri + "resqml20/" + resqml2_0_1::WellboreTrajectoryRepresentation::XML_TAG + "(" + repSet[i]->getUuid() + ")";
					resource.m_name = repSet[i]->getTitle();
					resource.m_lastChanged = repSet[i]->getLastUpdate() == -1 ? repSet[i]->getCreation() : repSet[i]->getLastUpdate();
					resource.m_sourceCount = repSet[i]->getAllSourceRelationships().size();
					resource.m_targetCount = repSet[i]->getAllTargetRelationships().size();
					mb.m_resource = resource;
					session->send(mb, correlationId, i == repSet.size() - 1 ? (0x01 | 0x02) : 0x01);
				}
			}
			else if (tokens[1] == resqml2_0_1::AbstractIjkGridRepresentation::XML_TAG) {
				resource.m_contentType = "application/x-resqml+xml;version=2.0;type=obj_";
				resource.m_contentType += resqml2_0_1::AbstractIjkGridRepresentation::XML_TAG;
				auto repSet = static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getIjkGridExplicitRepresentationSet();
				for (auto i = 0; i < repSet.size(); ++i) {
					resource.m_uri = gc.m_uri + "resqml20/" + resqml2_0_1::AbstractIjkGridRepresentation::XML_TAG + "(" + repSet[i]->getUuid() + ")";
					resource.m_name = repSet[i]->getTitle();
					resource.m_lastChanged = repSet[i]->getLastUpdate() == -1 ? repSet[i]->getCreation() : repSet[i]->getLastUpdate();
					resource.m_sourceCount = repSet[i]->getAllSourceRelationships().size();
					resource.m_targetCount = repSet[i]->getAllTargetRelationships().size();
					mb.m_resource = resource;
					session->send(mb, correlationId, i == repSet.size() - 1 ? (0x01 | 0x02) : 0x01);
				}
				auto repSet2 = static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getIjkGridParametricRepresentationSet();
				for (auto i = 0; i < repSet2.size(); ++i) {
					resource.m_uri = gc.m_uri + "resqml20/" + resqml2_0_1::AbstractIjkGridRepresentation::XML_TAG + "(" + repSet2[i]->getUuid() + ")";
					resource.m_name = repSet2[i]->getTitle();
					resource.m_lastChanged = repSet2[i]->getLastUpdate() == -1 ? repSet2[i]->getCreation() : repSet2[i]->getLastUpdate();
					resource.m_sourceCount = repSet[i]->getAllSourceRelationships().size();
					resource.m_targetCount = repSet[i]->getAllTargetRelationships().size();
					mb.m_resource = resource;
					session->send(mb, correlationId, i == repSet.size() - 1 ? (0x01 | 0x02) : 0x01);
				}
			}
			else {
				Energistics::Etp::v12::Protocol::Core::ProtocolException error;
				error.m_errorCode = 9;
				error.m_errorMessage = "The URI " + gc.m_uri + "  targets a data object " + tokens[1] + " which is not supported by this agent.";

				session->send(error);
				return;
			}
		}
		else {
			Energistics::Etp::v12::Protocol::Core::ProtocolException error;
			error.m_errorCode = 9;
			error.m_errorMessage = "The URI " + gc.m_uri + "  is not workable by the agent. Maybe more than one hierarchical level is used.";

			session->send(error);
			return;
		}
	}
}
