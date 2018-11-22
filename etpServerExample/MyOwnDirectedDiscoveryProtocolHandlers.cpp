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

#include "common/AbstractHdfProxy.h"
#include "resqml2_0_1/TriangulatedSetRepresentation.h"
#include "resqml2_0_1/Grid2dRepresentation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "resqml2_0_1/IjkGridParametricRepresentation.h"

void MyOwnDirectedDiscoveryProtocolHandlers::on_GetContent(const Energistics::Etp::v12::Protocol::DirectedDiscovery::GetContent & gc, int64_t correlationId)
{
	if (!session->validateUri(gc.m_uri, true)) {
		return;
	}

	std::cout << "received uri : " << gc.m_uri << std::endl;

	Energistics::Etp::v12::Protocol::DirectedDiscovery::GetResourcesResponse mb;
	Energistics::Etp::v12::Datatypes::Object::GraphResource resource;
	resource.m_objectNotifiable = false;
	resource.m_contentType = "";

	//***********************
	// Response to eml://
	//***********************
	if (gc.m_uri == "eml://") {
		// RESQML2.0
		resource.m_uri = "eml://resqml20";
		resource.m_name = "RESQML2.0 Protocol";
		resource.m_resourceType = Energistics::Etp::v12::Datatypes::Object::ResourceKind::UriProtocol;
		resource.m_contentCount.set_int(4); // the four supported RESQML dataobject type
		mb.m_resource = resource;
		session->send(mb, correlationId, 0x01);

		// EML2.0
		resource.m_uri = "eml://eml20";
		resource.m_name = "EML2.0 Protocol";
		resource.m_contentCount.set_int(1); // Hdf Proxy
		mb.m_resource = resource;
		session->send(mb, correlationId, 0x01 | 0x02);

		return;
	}

	const std::string uriPrefix = "eml://resqml20/obj_";
	std::string path = gc.m_uri.substr(6);

	resource.m_resourceType = Energistics::Etp::v12::Datatypes::Object::ResourceKind::Folder;
	if (path == "resqml20" || path == "resqml20/") {

		//***********************
		// Response to eml://resqml20
		//***********************

		// Triangulated Set Representation
		resource.m_uri = uriPrefix + RESQML2_0_1_NS::TriangulatedSetRepresentation::XML_TAG;
		resource.m_name = RESQML2_0_1_NS::TriangulatedSetRepresentation::XML_TAG;
		resource.m_name += " Folder";
		resource.m_contentCount.set_int(static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getAllTriangulatedSetRepSet().size());
		mb.m_resource = resource;
		session->send(mb, correlationId, 0x01);

		// Grid 2d Representation
		resource.m_uri = uriPrefix + RESQML2_0_1_NS::Grid2dRepresentation::XML_TAG;
		resource.m_name = RESQML2_0_1_NS::Grid2dRepresentation::XML_TAG ;
		resource.m_name += " Folder";
		resource.m_contentCount.set_int(static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getAllGrid2dRepresentationSet().size());
		mb.m_resource = resource;
		session->send(mb, correlationId, 0x01);

		// Wellbore trajectory
		resource.m_uri = uriPrefix + RESQML2_0_1_NS::WellboreTrajectoryRepresentation::XML_TAG;
		resource.m_name = RESQML2_0_1_NS::WellboreTrajectoryRepresentation::XML_TAG;
		resource.m_name += " Folder";
		resource.m_contentCount.set_int(static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getWellboreTrajectoryRepresentationSet().size());
		mb.m_resource = resource;
		session->send(mb, correlationId, 0x01);

		// IJK Grid
		resource.m_uri = uriPrefix + RESQML2_0_1_NS::AbstractIjkGridRepresentation::XML_TAG;
		resource.m_name = RESQML2_0_1_NS::AbstractIjkGridRepresentation::XML_TAG;
		resource.m_name += " Folder";
		resource.m_contentCount.set_int(static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getIjkGridRepresentationSet().size());
		mb.m_resource = resource;
		session->send(mb, correlationId, 0x01 | 0x02);
	}
	else if (path == "eml20" || path == "eml20/") {

		//***********************
		// Response to eml://eml20
		//***********************

		resource.m_uri = uriPrefix + COMMON_NS::EpcExternalPartReference::XML_TAG;
		resource.m_name = COMMON_NS::EpcExternalPartReference::XML_TAG;
		resource.m_name +=" Folder";
		resource.m_contentCount.set_int(static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getHdfProxySet().size());
		mb.m_resource = resource;
		session->send(mb, correlationId, 0x01 | 0x02);
	}
	else {

		//***********************
		// Response to a folder
		//***********************

		std::vector<std::string> tokens = tokenize(path, '/');
		if (tokens[0] != "resqml20" && tokens[0] != "eml20") {
			Energistics::Etp::v12::Protocol::Core::ProtocolException error;
			error.m_errorCode = 2;
			error.m_errorMessage = "The URI " + gc.m_uri + "  uses some dataspaces or witsml or prodml. This agent does not support dataspace.";

			session->send(error);
			return;
		}

		MyOwnEtpServerSession* mySession = static_cast<MyOwnEtpServerSession*>(session);
		tokens[1] = tokens[1].substr(4);
		if (tokens[1] == RESQML2_0_1_NS::TriangulatedSetRepresentation::XML_TAG) {
			sendGraphResourcesFromObjects(mySession->epcDoc.getAllTriangulatedSetRepSet(), correlationId);
		}
		else if (tokens[1] == RESQML2_0_1_NS::Grid2dRepresentation::XML_TAG) {
			sendGraphResourcesFromObjects(mySession->epcDoc.getAllGrid2dRepresentationSet(), correlationId);
		}
		else if (tokens[1] == RESQML2_0_1_NS::WellboreTrajectoryRepresentation::XML_TAG) {
			sendGraphResourcesFromObjects(mySession->epcDoc.getWellboreTrajectoryRepresentationSet(), correlationId);
		}
		else if (tokens[1] == RESQML2_0_1_NS::AbstractIjkGridRepresentation::XML_TAG) {
			sendGraphResourcesFromObjects(mySession->epcDoc.getIjkGridRepresentationSet(), correlationId);
		}
		else if (tokens[1] == COMMON_NS::EpcExternalPartReference::XML_TAG) {
			sendGraphResourcesFromObjects(mySession->epcDoc.getHdfProxySet(), correlationId);
		}
		else {
			Energistics::Etp::v12::Protocol::Core::ProtocolException error;
			error.m_errorCode = 14;
			error.m_errorMessage = "The URI " + gc.m_uri + "  targets a data object " + tokens[1] + " which is not supported by this agent.";

			session->send(error);
		}
	}
}

void MyOwnDirectedDiscoveryProtocolHandlers::sendGraphResourcesFromRelationships(const std::vector<std::string> & uuids, int64_t correlationId)
{
	if (uuids.empty()) {
		Energistics::Etp::v12::Protocol::Core::ProtocolException error;
		error.m_errorCode = 11;
		error.m_errorMessage = "This data object has not got this kind of relationship.";

		session->send(error);
		return;
	}

	Energistics::Etp::v12::Protocol::DirectedDiscovery::GetResourcesResponse mb;
	for (auto i = 0; i < uuids.size(); ++i) {
		mb.m_resource = buildGraphResourceFromObject(static_cast<MyOwnEtpServerSession*>(session)->epcDoc.getResqmlAbstractObjectByUuid(uuids[i]));
		session->send(mb, correlationId, i == uuids.size() - 1 ? (0x01 | 0x02) : 0x01);
	}
}

void MyOwnDirectedDiscoveryProtocolHandlers::on_GetSources(const Energistics::Etp::v12::Protocol::DirectedDiscovery::GetSources & gs, int64_t correlationId)
{
	std::cout << "received uri : " << gs.m_uri << std::endl;

	COMMON_NS::AbstractObject* obj = static_cast<MyOwnEtpServerSession*>(session)->getObjectFromUri(gs.m_uri);
	if (obj == nullptr) {
		return;
	}

	sendGraphResourcesFromRelationships(obj->getAllSourceRelationshipUuids(), correlationId);
}

void MyOwnDirectedDiscoveryProtocolHandlers::on_GetTargets(const Energistics::Etp::v12::Protocol::DirectedDiscovery::GetTargets & gt, int64_t correlationId)
{
	std::cout << "received uri : " << gt.m_uri << std::endl;

	COMMON_NS::AbstractObject* obj = static_cast<MyOwnEtpServerSession*>(session)->getObjectFromUri(gt.m_uri);
	if (obj == nullptr) {
		return;
	}

	sendGraphResourcesFromRelationships(obj->getAllTargetRelationshipUuids(), correlationId);
}
