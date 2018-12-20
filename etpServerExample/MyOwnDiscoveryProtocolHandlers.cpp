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
#include "MyOwnDiscoveryProtocolHandlers.h"

#include "common/AbstractHdfProxy.h"
#include "resqml2_0_1/TriangulatedSetRepresentation.h"
#include "resqml2_0_1/Grid2dRepresentation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "resqml2_0_1/IjkGridParametricRepresentation.h"

void MyOwnDiscoveryProtocolHandlers::on_GetEmlColonSlashSlash(const Energistics::Etp::v12::Protocol::Discovery::GetTreeResources & gr,  int64_t correlationId,
	std::vector<Energistics::Etp::v12::Datatypes::Object::Resource> & result)
{
	Energistics::Etp::v12::Datatypes::Object::Resource resource;
	resource.m_objectNotifiable = false;
	resource.m_contentType = std::string();

	if (gr.m_context.m_depth >= 0) {
		// Self
		if (gr.m_context.m_depth == 0) {
			resource.m_uri = gr.m_context.m_uri;
			resource.m_name = "eml://";
			resource.m_resourceType = Energistics::Etp::v12::Datatypes::Object::ResourceKind::UriProtocol;
			resource.m_contentCount.set_int(2); // the two supported Uri Protocols
			if (gr.m_context.m_contentTypes.empty() || std::find(gr.m_context.m_contentTypes.begin(), gr.m_context.m_contentTypes.end(), std::string()) != gr.m_context.m_contentTypes.end()) {
				result.push_back(resource);
			}
		}
		else {
			Energistics::Etp::v12::Protocol::Discovery::GetTreeResources nextGr = gr;
			--nextGr.m_context.m_depth;

			nextGr.m_context.m_uri = "eml://resqml20";
			on_GetEmlColonSlashSlashResqml20(nextGr, correlationId, result, true);
			nextGr.m_context.m_uri = "eml://eml20";
			on_GetEmlColonSlashSlashEml20(nextGr, correlationId, result, true);
		}
	}
}

void MyOwnDiscoveryProtocolHandlers::on_GetEmlColonSlashSlashResqml20(const Energistics::Etp::v12::Protocol::Discovery::GetTreeResources & gr, int64_t correlationId,
	std::vector<Energistics::Etp::v12::Datatypes::Object::Resource> & result, bool self)
{
	Energistics::Etp::v12::Datatypes::Object::Resource resource;
	resource.m_objectNotifiable = false;
	resource.m_contentType = "";

	if (gr.m_context.m_depth >= 0) {
		// Self
		if (gr.m_context.m_depth == 0) {
			resource.m_uri = gr.m_context.m_uri;
			resource.m_name = "RESQML2.0 Uri Protocol";
			resource.m_resourceType = Energistics::Etp::v12::Datatypes::Object::ResourceKind::UriProtocol;
			resource.m_contentCount.set_int(4); // the current four supported RESQML 2.0 datatypes
			if (gr.m_context.m_contentTypes.empty() || std::find(gr.m_context.m_contentTypes.begin(), gr.m_context.m_contentTypes.end(), std::string()) != gr.m_context.m_contentTypes.end()) {
				result.push_back(resource);
			}
		}
		else {
			Energistics::Etp::v12::Protocol::Discovery::GetTreeResources nextGr = gr;
			--nextGr.m_context.m_depth;

			const std::string uriPrefix = "eml://resqml20/obj_";
			MyOwnEtpServerSession* mySession = static_cast<MyOwnEtpServerSession*>(session);

			auto objectsGroupedByContentType = mySession->epcDoc.getResqmlObjectsGroupedByContentType();
			for (auto it = objectsGroupedByContentType.begin(); it != objectsGroupedByContentType.end(); ++it) {
				nextGr.m_context.m_uri = uriPrefix + it->second[0]->getXmlTag();
				on_GetFolder(nextGr, correlationId, result, true);
			}
		}
	}
}

void MyOwnDiscoveryProtocolHandlers::on_GetEmlColonSlashSlashEml20(const Energistics::Etp::v12::Protocol::Discovery::GetTreeResources & gr, int64_t correlationId,
	std::vector<Energistics::Etp::v12::Datatypes::Object::Resource> & result, bool self)
{
	Energistics::Etp::v12::Datatypes::Object::Resource resource;
	resource.m_objectNotifiable = false;
	resource.m_contentType = "";

	if (gr.m_context.m_depth >= 0) {
		// Self
		if (gr.m_context.m_depth == 0) {
			resource.m_uri = gr.m_context.m_uri;
			resource.m_name = "EML2.0 Uri Protocol";
			resource.m_resourceType = Energistics::Etp::v12::Datatypes::Object::ResourceKind::UriProtocol;
			resource.m_contentCount.set_int(1); // the only supported EML 2.0 datatype (HdfProxy)
			if (gr.m_context.m_contentTypes.empty() || std::find(gr.m_context.m_contentTypes.begin(), gr.m_context.m_contentTypes.end(), std::string()) != gr.m_context.m_contentTypes.end()) {
				result.push_back(resource);
			}
		}
		else {
			Energistics::Etp::v12::Protocol::Discovery::GetTreeResources nextGr = gr;
			--nextGr.m_context.m_depth;

			const std::string uriPrefix = "eml://eml20/obj_";

			nextGr.m_context.m_uri = uriPrefix + COMMON_NS::EpcExternalPartReference::XML_TAG;
			on_GetFolder(nextGr, correlationId, result, true);
		}
	}
}

void MyOwnDiscoveryProtocolHandlers::on_GetFolder(const Energistics::Etp::v12::Protocol::Discovery::GetTreeResources & gr, int64_t correlationId,
	std::vector<Energistics::Etp::v12::Datatypes::Object::Resource> & result, bool self)
{
	Energistics::Etp::v12::Datatypes::Object::Resource resource;
	resource.m_objectNotifiable = false;
	resource.m_contentType = "";

	std::string resqml20Datatype = tokenize(gr.m_context.m_uri, '/')[3];
	if (gr.m_context.m_depth >= 0) {
		MyOwnEtpServerSession* mySession = static_cast<MyOwnEtpServerSession*>(session);

		// Self
		if (gr.m_context.m_depth == 0) {
			resource.m_uri = gr.m_context.m_uri;
			resource.m_name = resqml20Datatype + " Folder";
			resource.m_resourceType = Energistics::Etp::v12::Datatypes::Object::ResourceKind::Folder;

			if (resqml20Datatype.substr(4) == COMMON_NS::EpcExternalPartReference::XML_TAG) {
				resource.m_contentCount.set_int(mySession->epcDoc.getHdfProxySet().size());
			}
			else {
				resource.m_contentCount.set_int(mySession->epcDoc.getResqmlObjectsByContentType("application/x-resqml+xml;version=2.0;type=" + resqml20Datatype).size());
			}
/*
			else {
				Energistics::Etp::v12::Protocol::Core::ProtocolException error;
				error.m_errorCode = 14;
				error.m_errorMessage = "The URI " + gr.m_context.m_uri + "  targets a data object " + resqml20Datatype + " which is not supported by this store.";

				session->send(error);
			}
			*/
			if (gr.m_context.m_contentTypes.empty() || std::find(gr.m_context.m_contentTypes.begin(), gr.m_context.m_contentTypes.end(), std::string()) != gr.m_context.m_contentTypes.end()) {
				result.push_back(resource);
			}
		}
		else {
			// Content
			Energistics::Etp::v12::Protocol::Discovery::GetGraphResources nextGr;
			nextGr.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self;
			nextGr.m_groupByType = false;
			nextGr.m_context.m_depth = 0;

			if (resqml20Datatype.substr(4) == COMMON_NS::EpcExternalPartReference::XML_TAG) {
				for (const auto & obj : mySession->epcDoc.getHdfProxySet()) {
					if (!obj->isPartial()) {
						nextGr.m_context.m_uri = gr.m_context.m_uri + '(' + obj->getUuid() + ')';
						on_GetDataObject(nextGr, correlationId, result);
					}
				}
			}
			else {
				auto objs = mySession->epcDoc.getResqmlObjectsByContentType("application/x-resqml+xml;version=2.0;type=" + resqml20Datatype);
				for (const auto & obj : objs) {
					if (!obj->isPartial()) {
						nextGr.m_context.m_uri = gr.m_context.m_uri + '(' + obj->getUuid() + ')';
						on_GetDataObject(nextGr, correlationId, result);
					}
				}
			}
		}
	}
}

void MyOwnDiscoveryProtocolHandlers::on_GetDataObject(const Energistics::Etp::v12::Protocol::Discovery::GetGraphResources & gr, int64_t correlationId,
	std::vector<Energistics::Etp::v12::Datatypes::Object::Resource> & result)
{
	Energistics::Etp::v12::Datatypes::Object::Resource resource;
	resource.m_objectNotifiable = false;
	resource.m_contentType = "";

	if (gr.m_context.m_depth >= 0) {
		MyOwnEtpServerSession* mySession = static_cast<MyOwnEtpServerSession*>(session);

		const size_t openingParenthesis = gr.m_context.m_uri.find('(', 5);
		COMMON_NS::AbstractObject* obj = mySession->epcDoc.getResqmlAbstractObjectByUuid(gr.m_context.m_uri.substr(openingParenthesis + 1, 36));

		// Self
		if (gr.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self ||
			gr.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf ||
			gr.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {
			if (gr.m_context.m_contentTypes.empty() || std::find(gr.m_context.m_contentTypes.begin(), gr.m_context.m_contentTypes.end(), obj->getContentType()) != gr.m_context.m_contentTypes.end()) {
				result.push_back(buildResourceFromObject(obj));
			}
		}

		if (gr.m_context.m_depth >= 1) {
			// Target
			if (gr.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets ||
				gr.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {
				Energistics::Etp::v12::Protocol::Discovery::GetGraphResources nextGr = gr;
				--nextGr.m_context.m_depth;
				nextGr.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf;

				for (const auto & targetUuid : obj->getAllTargetRelationshipUuids()) {
					nextGr.m_context.m_uri = gr.m_context.m_uri.substr(0, openingParenthesis) + '(' + targetUuid + ')';
					on_GetDataObject(nextGr, correlationId, result);
				}
			}
			// Source
			else if (gr.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources ||
				gr.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf) {
				Energistics::Etp::v12::Protocol::Discovery::GetGraphResources nextGr = gr;
				--nextGr.m_context.m_depth;
				nextGr.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf;
				
				for (const auto & targetUuid : obj->getAllSourceRelationshipUuids()) {
					nextGr.m_context.m_uri = gr.m_context.m_uri.substr(0, openingParenthesis) + '(' + targetUuid + ')';
					on_GetDataObject(nextGr, correlationId, result);
				}
			}
		}
	}
}

void MyOwnDiscoveryProtocolHandlers::on_GetTreeResources(const Energistics::Etp::v12::Protocol::Discovery::GetTreeResources & gr, int64_t correlationId)
{
	std::cout << "Discovery tree resource received uri : " << gr.m_context.m_uri << std::endl;

	if (!session->validateUri(gr.m_context.m_uri, true)) {
		return;
	}

	Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse mb;

	if (gr.m_context.m_uri == "eml://") {
		on_GetEmlColonSlashSlash(gr, correlationId, mb.m_resources);
	}
	else {
		const std::string path = gr.m_context.m_uri.substr(6);
		if (path == "resqml20" || path == "resqml20/") {
			on_GetEmlColonSlashSlashResqml20(gr, correlationId, mb.m_resources);
		}
		else if (path == "eml20" || path == "eml20/") {
			on_GetEmlColonSlashSlashEml20(gr, correlationId, mb.m_resources);
		}
		else {
			on_GetFolder(gr, correlationId, mb.m_resources);
		}
	}

	session->send(mb, correlationId, 0x01 | 0x02);
}

void MyOwnDiscoveryProtocolHandlers::on_GetGraphResources(const Energistics::Etp::v12::Protocol::Discovery::GetGraphResources & gr, int64_t correlationId)
{
	std::cout << "Discovery graph resource received uri : " << gr.m_context.m_uri << std::endl;

	if (!session->validateDataObjectUri(gr.m_context.m_uri, true)) {
		return;
	}

	Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse mb;
	on_GetDataObject(gr, correlationId, mb.m_resources);

	session->send(mb, correlationId, 0x01 | 0x02);
}
