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

void MyOwnDiscoveryProtocolHandlers::on_GetEmlColonSlashSlash(const Energistics::Etp::v12::Protocol::Discovery::GetResources2 & gr,  int64_t correlationId,
	std::vector<Energistics::Etp::v12::Datatypes::Object::Resource2> & result)
{
	Energistics::Etp::v12::Datatypes::Object::Resource2 resource;
	resource.m_objectNotifiable = false;
	resource.m_contentType = "";

	if (gr.m_context.m_depth >= 0) {
		// Self
		if (gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self ||
			gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf ||
			gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {
			resource.m_uri = gr.m_context.m_uri;
			resource.m_name = "eml://";
			resource.m_resourceType = Energistics::Etp::v12::Datatypes::Object::ResourceKind::UriProtocol;
			resource.m_contentCount.set_int(2); // the two supported Uri Protocols
			if (gr.m_context.m_contentTypes.empty() || std::find(gr.m_context.m_contentTypes.begin(), gr.m_context.m_contentTypes.end(), std::string()) != gr.m_context.m_contentTypes.end()) {
				result.push_back(resource);
			}
		}

		// Target
		if (gr.m_context.m_depth >= 1 &&
			(gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets ||
			gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf)) {
			Energistics::Etp::v12::Protocol::Discovery::GetResources2 nextGr = gr;
			--nextGr.m_context.m_depth;
			nextGr.m_context.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf;

			nextGr.m_context.m_uri = "eml://resqml20";
			on_GetEmlColonSlashSlashResqml20(nextGr, correlationId, result);
			nextGr.m_context.m_uri = "eml://eml20";
			on_GetEmlColonSlashSlashEml20(nextGr, correlationId, result);
		}
	}
}

void MyOwnDiscoveryProtocolHandlers::on_GetEmlColonSlashSlashResqml20(const Energistics::Etp::v12::Protocol::Discovery::GetResources2 & gr, int64_t correlationId,
	std::vector<Energistics::Etp::v12::Datatypes::Object::Resource2> & result)
{
	Energistics::Etp::v12::Datatypes::Object::Resource2 resource;
	resource.m_objectNotifiable = false;
	resource.m_contentType = "";

	if (gr.m_context.m_depth >= 0) {
		// Self
		if (gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self ||
			gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf ||
			gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {
			resource.m_uri = gr.m_context.m_uri;
			resource.m_name = "RESQML2.0 Uri Protocol";
			resource.m_resourceType = Energistics::Etp::v12::Datatypes::Object::ResourceKind::UriProtocol;
			resource.m_contentCount.set_int(4); // the current four supported RESQML 2.0 datatypes
			if (gr.m_context.m_contentTypes.empty() || std::find(gr.m_context.m_contentTypes.begin(), gr.m_context.m_contentTypes.end(), std::string()) != gr.m_context.m_contentTypes.end()) {
				result.push_back(resource);
			}
		}

		if (gr.m_context.m_depth >= 1) {
			// Target
			if (gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets ||
				gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {
				Energistics::Etp::v12::Protocol::Discovery::GetResources2 nextGr = gr;
				--nextGr.m_context.m_depth;
				nextGr.m_context.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf;

				const std::string uriPrefix = "eml://resqml20/obj_";

				nextGr.m_context.m_uri = uriPrefix + RESQML2_0_1_NS::TriangulatedSetRepresentation::XML_TAG;
				on_GetFolder(nextGr, correlationId, result);

				nextGr.m_context.m_uri = uriPrefix + RESQML2_0_1_NS::Grid2dRepresentation::XML_TAG;
				on_GetFolder(nextGr, correlationId, result);

				nextGr.m_context.m_uri = uriPrefix + RESQML2_0_1_NS::WellboreTrajectoryRepresentation::XML_TAG;
				on_GetFolder(nextGr, correlationId, result);

				nextGr.m_context.m_uri = uriPrefix + RESQML2_0_1_NS::AbstractIjkGridRepresentation::XML_TAG;
				on_GetFolder(nextGr, correlationId, result);
			}
			// Source
			else if (gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources ||
				gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf) {
				Energistics::Etp::v12::Protocol::Discovery::GetResources2 nextGr = gr;
				--nextGr.m_context.m_depth;
				nextGr.m_context.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self;
				nextGr.m_context.m_uri = "eml://";
				on_GetEmlColonSlashSlash(nextGr, correlationId, result);
			}
		}
	}
}

void MyOwnDiscoveryProtocolHandlers::on_GetEmlColonSlashSlashEml20(const Energistics::Etp::v12::Protocol::Discovery::GetResources2 & gr, int64_t correlationId,
	std::vector<Energistics::Etp::v12::Datatypes::Object::Resource2> & result)
{
	Energistics::Etp::v12::Datatypes::Object::Resource2 resource;
	resource.m_objectNotifiable = false;
	resource.m_contentType = "";

	if (gr.m_context.m_depth >= 0) {
		// Self
		if (gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self ||
			gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf ||
			gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {
			resource.m_uri = gr.m_context.m_uri;
			resource.m_name = "EML2.0 Uri Protocol";
			resource.m_resourceType = Energistics::Etp::v12::Datatypes::Object::ResourceKind::UriProtocol;
			resource.m_contentCount.set_int(1); // the only supported EML 2.0 datatype (HdfProxy)
			if (gr.m_context.m_contentTypes.empty() || std::find(gr.m_context.m_contentTypes.begin(), gr.m_context.m_contentTypes.end(), std::string()) != gr.m_context.m_contentTypes.end()) {
				result.push_back(resource);
			}
		}

		if (gr.m_context.m_depth >= 1) {
			// Target
			if (gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets ||
				gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {
				Energistics::Etp::v12::Protocol::Discovery::GetResources2 nextGr = gr;
				--nextGr.m_context.m_depth;
				nextGr.m_context.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf;

				const std::string uriPrefix = "eml://eml20/obj_";

				nextGr.m_context.m_uri = uriPrefix + COMMON_NS::EpcExternalPartReference::XML_TAG;
				on_GetFolder(nextGr, correlationId, result);
			}
			// Source
			else if (gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources ||
				gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf) {
				Energistics::Etp::v12::Protocol::Discovery::GetResources2 nextGr = gr;
				--nextGr.m_context.m_depth;
				nextGr.m_context.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self;
				nextGr.m_context.m_uri = "eml://";
				on_GetEmlColonSlashSlash(nextGr, correlationId, result);
			}
		}
	}
}

void MyOwnDiscoveryProtocolHandlers::on_GetFolder(const Energistics::Etp::v12::Protocol::Discovery::GetResources2 & gr, int64_t correlationId,
	std::vector<Energistics::Etp::v12::Datatypes::Object::Resource2> & result)
{
	Energistics::Etp::v12::Datatypes::Object::Resource2 resource;
	resource.m_objectNotifiable = false;
	resource.m_contentType = "";

	std::string resqml20Datatype = tokenize(gr.m_context.m_uri, '/')[3].substr(4);
	if (gr.m_context.m_depth >= 0) {
		MyOwnEtpServerSession* mySession = static_cast<MyOwnEtpServerSession*>(session);

		// Self
		if (gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self ||
			gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf ||
			gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {
			resource.m_uri = gr.m_context.m_uri;
			resource.m_name = resqml20Datatype + " Folder";
			resource.m_resourceType = Energistics::Etp::v12::Datatypes::Object::ResourceKind::Folder;

			
			if (resqml20Datatype == RESQML2_0_1_NS::TriangulatedSetRepresentation::XML_TAG) {
				resource.m_contentCount.set_int(mySession->epcDoc.getAllTriangulatedSetRepSet().size());
			}
			else if (resqml20Datatype == RESQML2_0_1_NS::Grid2dRepresentation::XML_TAG) {
				resource.m_contentCount.set_int(mySession->epcDoc.getAllGrid2dRepresentationSet().size());
			}
			else if (resqml20Datatype == RESQML2_0_1_NS::WellboreTrajectoryRepresentation::XML_TAG) {
				resource.m_contentCount.set_int(mySession->epcDoc.getWellboreTrajectoryRepresentationSet().size());
			}
			else if (resqml20Datatype == RESQML2_0_1_NS::AbstractIjkGridRepresentation::XML_TAG) {
				resource.m_contentCount.set_int(mySession->epcDoc.getIjkGridRepresentationCount());
			}
			else if (resqml20Datatype == COMMON_NS::EpcExternalPartReference::XML_TAG) {
				resource.m_contentCount.set_int(mySession->epcDoc.getHdfProxyCount());
			}
			else {
				Energistics::Etp::v12::Protocol::Core::ProtocolException error;
				error.m_errorCode = 14;
				error.m_errorMessage = "The URI " + gr.m_context.m_uri + "  targets a data object " + resqml20Datatype + " which is not supported by this store.";

				session->send(error);
			}
			if (gr.m_context.m_contentTypes.empty() || std::find(gr.m_context.m_contentTypes.begin(), gr.m_context.m_contentTypes.end(), std::string()) != gr.m_context.m_contentTypes.end()) {
				result.push_back(resource);
			}
		}

		if (gr.m_context.m_depth >= 1) {
			// Target
			if (gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets ||
				gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {
				Energistics::Etp::v12::Protocol::Discovery::GetResources2 nextGr = gr;
				--nextGr.m_context.m_depth;
				nextGr.m_context.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf;

				if (resqml20Datatype == RESQML2_0_1_NS::TriangulatedSetRepresentation::XML_TAG) {
					for (const auto & obj : mySession->epcDoc.getAllTriangulatedSetRepSet()) {
						nextGr.m_context.m_uri = gr.m_context.m_uri + '(' + obj->getUuid() + ')';
						on_GetDataObject(nextGr, correlationId, result);
					}
				}
				else if (resqml20Datatype == RESQML2_0_1_NS::Grid2dRepresentation::XML_TAG) {
					for (const auto & obj : mySession->epcDoc.getAllGrid2dRepresentationSet()) {
						nextGr.m_context.m_uri = gr.m_context.m_uri + '(' + obj->getUuid() + ')';
						on_GetDataObject(nextGr, correlationId, result);
					}
				}
				else if (resqml20Datatype == RESQML2_0_1_NS::WellboreTrajectoryRepresentation::XML_TAG) {
					for (const auto & obj : mySession->epcDoc.getWellboreTrajectoryRepresentationSet()) {
						nextGr.m_context.m_uri = gr.m_context.m_uri + '(' + obj->getUuid() + ')';
						on_GetDataObject(nextGr, correlationId, result);
					}
				}
				else if (resqml20Datatype == RESQML2_0_1_NS::AbstractIjkGridRepresentation::XML_TAG) {
					for (const auto & obj : mySession->epcDoc.getIjkGridRepresentationSet()) {
						nextGr.m_context.m_uri = gr.m_context.m_uri + '(' + obj->getUuid() + ')';
						on_GetDataObject(nextGr, correlationId, result);
					}
				}
				else if (resqml20Datatype == COMMON_NS::EpcExternalPartReference::XML_TAG) {
					for (const auto & obj : mySession->epcDoc.getHdfProxySet()) {
						nextGr.m_context.m_uri = gr.m_context.m_uri + '(' + obj->getUuid() + ')';
						on_GetDataObject(nextGr, correlationId, result);
					}
				}
			}
			// Source
			else if (gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources ||
				gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf) {
				Energistics::Etp::v12::Protocol::Discovery::GetResources2 nextGr = gr;
				--nextGr.m_context.m_depth;
				nextGr.m_context.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf;
				if (resqml20Datatype == COMMON_NS::EpcExternalPartReference::XML_TAG) {
					nextGr.m_context.m_uri = "eml://eml20";
					on_GetEmlColonSlashSlashEml20(nextGr, correlationId, result);
				}
				else {
					nextGr.m_context.m_uri = "eml://resqml20";
					on_GetEmlColonSlashSlashResqml20(nextGr, correlationId, result);
				}
			}
		}
	}
}

void MyOwnDiscoveryProtocolHandlers::on_GetDataObject(const Energistics::Etp::v12::Protocol::Discovery::GetResources2 & gr, int64_t correlationId,
	std::vector<Energistics::Etp::v12::Datatypes::Object::Resource2> & result)
{
	Energistics::Etp::v12::Datatypes::Object::Resource2 resource;
	resource.m_objectNotifiable = false;
	resource.m_contentType = "";

	if (gr.m_context.m_depth >= 0) {
		MyOwnEtpServerSession* mySession = static_cast<MyOwnEtpServerSession*>(session);

		const size_t openingParenthesis = gr.m_context.m_uri.find('(', 5);
		COMMON_NS::AbstractObject* obj = mySession->epcDoc.getResqmlAbstractObjectByUuid(gr.m_context.m_uri.substr(openingParenthesis + 1, 36));

		// Self
		if (gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self ||
			gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf ||
			gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {
			if (gr.m_context.m_contentTypes.empty() || std::find(gr.m_context.m_contentTypes.begin(), gr.m_context.m_contentTypes.end(), obj->getContentType()) != gr.m_context.m_contentTypes.end()) {
				result.push_back(buildResourceFromObject(obj));
			}
		}

		if (gr.m_context.m_depth >= 1) {
			// Target
			if (gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets ||
				gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {
				Energistics::Etp::v12::Protocol::Discovery::GetResources2 nextGr = gr;
				--nextGr.m_context.m_depth;
				nextGr.m_context.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf;

				for (const auto & targetUuid : obj->getAllTargetRelationshipUuids()) {
					nextGr.m_context.m_uri = gr.m_context.m_uri.substr(0, openingParenthesis) + '(' + targetUuid + ')';
					on_GetDataObject(nextGr, correlationId, result);
				}
			}
			// Source
			else if (gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources ||
				gr.m_context.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf) {
				Energistics::Etp::v12::Protocol::Discovery::GetResources2 nextGr = gr;
				--nextGr.m_context.m_depth;
				nextGr.m_context.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf;
				
				for (const auto & targetUuid : obj->getAllSourceRelationshipUuids()) {
					nextGr.m_context.m_uri = gr.m_context.m_uri.substr(0, openingParenthesis) + '(' + targetUuid + ')';
					on_GetDataObject(nextGr, correlationId, result);
				}
			}
		}
	}
}

void MyOwnDiscoveryProtocolHandlers::on_GetResources(const Energistics::Etp::v12::Protocol::Discovery::GetResources2 & gr, int64_t correlationId)
{
	std::cout << "received uri : " << gr.m_context.m_uri << std::endl;

	if (!session->validateUri(gr.m_context.m_uri, true)) {
		return;
	}

	Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse2 mb;

	if (gr.m_context.m_uri == "eml://") {
		on_GetEmlColonSlashSlash(gr, correlationId, mb.m_resource);
	}
	else {
		const std::string path = gr.m_context.m_uri.substr(6);
		if (path == "resqml20" || path == "resqml20/") {
			on_GetEmlColonSlashSlashResqml20(gr, correlationId, mb.m_resource);
		}
		else if (path == "eml20" || path == "eml20/") {
			on_GetEmlColonSlashSlashEml20(gr, correlationId, mb.m_resource);
		}
		else if (path[path.size() - 1] == ')') {
			on_GetDataObject(gr, correlationId, mb.m_resource);
		}
		else {
			on_GetFolder(gr, correlationId, mb.m_resource);
		}
	}

	session->send(mb, correlationId);
}
