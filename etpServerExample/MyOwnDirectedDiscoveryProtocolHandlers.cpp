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
#include "MyOwnDiscoveryProtocolHandlers.h"

#include "resqml2_0_1/TriangulatedSetRepresentation.h"
#include "resqml2_0_1/Grid2dRepresentation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "resqml2_0_1/IjkGridParametricRepresentation.h"

void MyOwnDiscoveryProtocolHandlers::on_GetResources(const Energistics::Protocol::Discovery::GetResources & gr, int64_t correlationId)
{
	if (!validateUri(gr.m_uri)) {
		Energistics::Protocol::Core::ProtocolException error;
		error.m_errorCode = 9;
		error.m_errorMessage = "The URI " + gr.m_uri + "  is invalid.";

		session->sendAndDoWhenFinished(error);
		return;
	}

	std::cout << "received uri : " << gr.m_uri << std::endl;

	Energistics::Protocol::Discovery::GetResourcesResponse mb;
	Energistics::Datatypes::Object::Resource resource;
	resource.m_channelSubscribable = false;
	resource.m_objectNotifiable = false;
	resource.m_contentType = "";
	if (gr.m_uri == "eml://") {
		// RESQML2.0
		resource.m_uri = gr.m_uri + "resqml20";
		resource.m_name = "RESQML2.0 Protocol";
		resource.m_resourceType = "UriProtocol";
		resource.m_hasChildren = 4;
		resource.m_lastChanged = 0;
		mb.m_resource = resource;
		session->send(mb);

		// EML2.0
		resource.m_uri = gr.m_uri + "eml20";
		resource.m_contentType = "application/x-eml+xml;version=2.0";
		resource.m_name = "EML2.0 Protocol";
		mb.m_resource = resource;
		session->sendAndDoWhenFinished(mb);

		return;
	}

	std::string path = gr.m_uri.substr(6);
	if (path == "resqml20" || path == "resqml20/") {
		resource.m_resourceType = "Folder";

		// Triangulated Set Representation
		resource.m_uri = gr.m_uri + "resqml20/" + resqml2_0_1::TriangulatedSetRepresentation::XML_TAG;
		resource.m_name = resqml2_0_1::TriangulatedSetRepresentation::XML_TAG;
		resource.m_name +=" Folder";
		resource.m_lastChanged = 0;
		resource.m_hasChildren = static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getAllTriangulatedSetRepSet().size();
		mb.m_resource = resource;
		session->send(mb);

		// Grid 2d Representation
		resource.m_uri = gr.m_uri + "resqml20/" + resqml2_0_1::Grid2dRepresentation::XML_TAG;
		resource.m_name = resqml2_0_1::Grid2dRepresentation::XML_TAG ;
		resource.m_name +=" Folder";
		resource.m_lastChanged = 0;
		resource.m_hasChildren = static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getHorizonGrid2dRepSet().size();
		mb.m_resource = resource;
		session->send(mb);

		// Wellbore trajectory
		resource.m_uri = gr.m_uri + "resqml20/" + resqml2_0_1::WellboreTrajectoryRepresentation::XML_TAG;
		resource.m_name = resqml2_0_1::WellboreTrajectoryRepresentation::XML_TAG;
		resource.m_name +=" Folder";
		resource.m_lastChanged = 0;
		resource.m_hasChildren = static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getWellboreTrajectoryRepresentationSet().size();
		mb.m_resource = resource;
		session->send(mb);

		// IJK grid
		resource.m_uri = gr.m_uri + "resqml20/" + resqml2_0_1::AbstractIjkGridRepresentation::XML_TAG;
		resource.m_name = resqml2_0_1::AbstractIjkGridRepresentation::XML_TAG;
		resource.m_name +=" Folder";
		resource.m_lastChanged = 0;
		resource.m_hasChildren = static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getIjkGridRepresentationSet().size();
		mb.m_resource = resource;
		session->sendAndDoWhenFinished(mb);

	}
	else if (path == "eml20" || path == "eml20/") {
		// HDF proxy
		Energistics::Protocol::Core::ProtocolException error;
		error.m_errorCode = 9;
		error.m_errorMessage = "Not sure it is clever to send HDF proxies.";

		session->sendAndDoWhenFinished(error);
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
			Energistics::Protocol::Core::ProtocolException error;
			error.m_errorCode = 9;
			error.m_errorMessage = "The URI " + gr.m_uri + "  uses some dataspaces. This agent does not support dataspace.";

			session->sendAndDoWhenFinished(error);
			return;
		}

		if (tokens.size() == 2) {
			if (tokens[1] == resqml2_0_1::TriangulatedSetRepresentation::XML_TAG) {
				resource.m_contentType = "application/x-resqml+xml;version=2.0;type=obj_";
				resource.m_contentType += resqml2_0_1::TriangulatedSetRepresentation::XML_TAG;
				auto repSet = static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getAllTriangulatedSetRepSet();
				for (auto i = 0; i < repSet.size(); ++i) {
					resource.m_uri = gr.m_uri + "resqml20/" + resqml2_0_1::TriangulatedSetRepresentation::XML_TAG + "(" + repSet[i]->getUuid() + ")";
					resource.m_name = repSet[i]->getTitle();
					resource.m_lastChanged = repSet[i]->getLastUpdate() == -1 ? repSet[i]->getCreation() : repSet[i]->getLastUpdate();
					resource.m_hasChildren = 0;
					mb.m_resource = resource;
					session->send(mb);
				}
			}
			else if (tokens[1] == resqml2_0_1::Grid2dRepresentation::XML_TAG) {
				resource.m_contentType = "application/x-resqml+xml;version=2.0;type=obj_";
				resource.m_contentType += resqml2_0_1::Grid2dRepresentation::XML_TAG;
				auto repSet = static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getHorizonGrid2dRepSet();
				for (auto i = 0; i < repSet.size(); ++i) {
					resource.m_uri = gr.m_uri + "resqml20/" + resqml2_0_1::Grid2dRepresentation::XML_TAG + "(" + repSet[i]->getUuid() + ")";
					resource.m_name = repSet[i]->getTitle();
					resource.m_lastChanged = repSet[i]->getLastUpdate() == -1 ? repSet[i]->getCreation() : repSet[i]->getLastUpdate();
					resource.m_hasChildren = false;
					mb.m_resource = resource;
					session->send(mb);
				}
			}
			else if (tokens[1] == resqml2_0_1::WellboreTrajectoryRepresentation::XML_TAG) {
				resource.m_contentType = "application/x-resqml+xml;version=2.0;type=obj_";
				resource.m_contentType += resqml2_0_1::WellboreTrajectoryRepresentation::XML_TAG;
				auto repSet = static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getWellboreTrajectoryRepresentationSet();
				for (auto i = 0; i < repSet.size(); ++i) {
					resource.m_uri = gr.m_uri + "resqml20/" + resqml2_0_1::WellboreTrajectoryRepresentation::XML_TAG + "(" + repSet[i]->getUuid() + ")";
					resource.m_name = repSet[i]->getTitle();
					resource.m_lastChanged = repSet[i]->getLastUpdate() == -1 ? repSet[i]->getCreation() : repSet[i]->getLastUpdate();
					resource.m_hasChildren = 0;
					mb.m_resource = resource;
					session->send(mb);
				}
			}
			else if (tokens[1] == resqml2_0_1::AbstractIjkGridRepresentation::XML_TAG) {
				resource.m_contentType = "application/x-resqml+xml;version=2.0;type=obj_";
				resource.m_contentType += resqml2_0_1::AbstractIjkGridRepresentation::XML_TAG;
				auto repSet = static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getIjkGridExplicitRepresentationSet();
				for (auto i = 0; i < repSet.size(); ++i) {
					resource.m_uri = gr.m_uri + "resqml20/" + resqml2_0_1::AbstractIjkGridRepresentation::XML_TAG + "(" + repSet[i]->getUuid() + ")";
					resource.m_name = repSet[i]->getTitle();
					resource.m_lastChanged = repSet[i]->getLastUpdate() == -1 ? repSet[i]->getCreation() : repSet[i]->getLastUpdate();
					resource.m_hasChildren = 0;
					mb.m_resource = resource;
					session->send(mb);
				}
				auto repSet2 = static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getIjkGridParametricRepresentationSet();
				for (auto i = 0; i < repSet2.size(); ++i) {
					resource.m_uri = gr.m_uri + "resqml20/" + resqml2_0_1::AbstractIjkGridRepresentation::XML_TAG + "(" + repSet2[i]->getUuid() + ")";
					resource.m_name = repSet2[i]->getTitle();
					resource.m_lastChanged = repSet2[i]->getLastUpdate() == -1 ? repSet2[i]->getCreation() : repSet2[i]->getLastUpdate();
					resource.m_hasChildren = 0;
					mb.m_resource = resource;
					session->send(mb);
				}
			}
			else {
				Energistics::Protocol::Core::ProtocolException error;
				error.m_errorCode = 9;
				error.m_errorMessage = "The URI " + gr.m_uri + "  targets a data bject " + tokens[1] + " which is not supported by this agent.";

				session->sendAndDoWhenFinished(error);
				return;
			}
			session->do_when_finished();
		}
		else {
			Energistics::Protocol::Core::ProtocolException error;
			error.m_errorCode = 9;
			error.m_errorMessage = "The URI " + gr.m_uri + "  is not workable by the agent. Maybe more than one hierarchical level is used.";

			session->sendAndDoWhenFinished(error);
			return;
		}
	}
}
