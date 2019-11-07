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

#include "etp/EtpHelpers.h"

#include "common/AbstractHdfProxy.h"
#include "resqml2_0_1/TriangulatedSetRepresentation.h"
#include "resqml2_0_1/Grid2dRepresentation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "resqml2_0_1/IjkGridParametricRepresentation.h"
/*
void MyOwnDiscoveryProtocolHandlers::on_GetEmlColonSlashSlash(const Energistics::Etp::v12::Protocol::Discovery::GetNamespaces & gn, int64_t correlationId,
	std::vector<std::string> & result)
{
	Energistics::Etp::v12::Datatypes::Object::Resource resource;
	resource.m_contentType = std::string();

	const auto & objectsGroupedByContentType = repo->getDataObjectsGroupedByContentType();

	// EML 2.0
	int32_t contentCount = 0;
	for (auto it = objectsGroupedByContentType.begin(); it != objectsGroupedByContentType.end(); ++it) {
		if (it->first.find("x-resqml+xml;version=2.0") != std::string::npos) {
			++contentCount;
		}
	}
	if (contentCount > 0) {
		result.push_back("eml://resqml20");
	}
	contentCount = 0;
	for (auto it = objectsGroupedByContentType.begin(); it != objectsGroupedByContentType.end(); ++it) {
		if (it->first.find("x-eml+xml;version=2.0") != std::string::npos) {
			++contentCount;
		}
	}
	if (contentCount > 0) {
		result.push_back("eml://eml20");
	}

	// EML 2.1
	contentCount = 0;
	for (auto it = objectsGroupedByContentType.begin(); it != objectsGroupedByContentType.end(); ++it) {
		if (it->first.find("x-witsml+xml;version=2.0") != std::string::npos) {
			++contentCount;
		}
	}
	if (contentCount > 0) {
		result.push_back("eml://witsml20");
	}
	contentCount = 0;
	for (auto it = objectsGroupedByContentType.begin(); it != objectsGroupedByContentType.end(); ++it) {
		if (it->first.find("x-eml+xml;version=2.1") != std::string::npos) {
			++contentCount;
		}
	}
	if (contentCount > 0) {
		result.push_back("eml://eml21");
	}

	// EML 2.2
	contentCount = 0;
	for (auto it = objectsGroupedByContentType.begin(); it != objectsGroupedByContentType.end(); ++it) {
		if (it->first.find("x-witsml+xml;version=2.1") != std::string::npos) {
			++contentCount;
		}
	}
	if (contentCount > 0) {
		result.push_back("eml://witsml21");
	}
	contentCount = 0;
	for (auto it = objectsGroupedByContentType.begin(); it != objectsGroupedByContentType.end(); ++it) {
		if (it->first.find("x-resqml+xml;version=2.2") != std::string::npos) {
			++contentCount;
		}
	}
	if (contentCount > 0) {
		result.push_back("eml://resqml22");
	}
	contentCount = 0;
	for (auto it = objectsGroupedByContentType.begin(); it != objectsGroupedByContentType.end(); ++it) {
		if (it->first.find("x-eml+xml;version=2.2") != std::string::npos) {
			++contentCount;
		}
	}
	if (contentCount > 0) {
		result.push_back("eml://eml22");
	}
}
*/
void MyOwnDiscoveryProtocolHandlers::on_GetDataObject(const Energistics::Etp::v12::Protocol::Discovery::GetResources & msg, int64_t correlationId,
	std::vector<Energistics::Etp::v12::Datatypes::Object::Resource> & result)
{
	Energistics::Etp::v12::Datatypes::Object::Resource resource;
	resource.m_dataObjectType = "";

	if (msg.m_context.m_depth >= 0) {
		const size_t openingParenthesis = msg.m_context.m_uri.find('(', 5);
		COMMON_NS::AbstractObject* obj = repo->getDataObjectByUuid(msg.m_context.m_uri.substr(openingParenthesis + 1, 36));
		if (obj == nullptr) {
			Energistics::Etp::v12::Protocol::Core::ProtocolException pe;
			Energistics::Etp::v12::Datatypes::ErrorInfo error;
			error.m_code = 9;
			error.m_message = "The URI " + msg.m_context.m_uri + " targets something which does not exist.";
			pe.m_error.set_ErrorInfo(error);

			session->send(pe, correlationId, 0x01);
			return;
		}

		// Self
		if (msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self ||
			msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf ||
			msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {

			time_t lastUpdate = -1;
			if (!msg.m_lastChangedFilter.is_null() && !obj->isPartial()) {
				lastUpdate = obj->getLastUpdate();
				if (lastUpdate < 0) {
					lastUpdate = obj->getCreation();
				}
			}
			if ((msg.m_context.m_dataObjectTypes.empty() || std::find(msg.m_context.m_dataObjectTypes.begin(), msg.m_context.m_dataObjectTypes.end(), obj->getQualifiedType()) != msg.m_context.m_dataObjectTypes.end()) &&
				(msg.m_lastChangedFilter.is_null() || lastUpdate >= msg.m_lastChangedFilter.get_long())) {
				result.push_back(ETP_NS::EtpHelpers::buildEtpResourceFromEnergisticsObject(obj, msg.m_countObjects));
			}
		}

		if (msg.m_context.m_depth >= 1) {
			// Target
			if (msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets ||
				msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {
				Energistics::Etp::v12::Protocol::Discovery::GetResources nextGr = msg;
				--nextGr.m_context.m_depth;
				nextGr.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf;

				for (const auto & targetObj : repo->getTargetObjects(obj)) {
					nextGr.m_context.m_uri = msg.m_context.m_uri.substr(0, openingParenthesis) + '(' + targetObj->getUuid() + ')';
					on_GetDataObject(nextGr, correlationId, result);
				}
			}

			// Source
			if (msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources ||
				msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf) {
				Energistics::Etp::v12::Protocol::Discovery::GetResources nextGr = msg;
				--nextGr.m_context.m_depth;
				nextGr.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf;
				
				for (const auto & sourceObj : repo->getSourceObjects(obj)) {
					nextGr.m_context.m_uri = msg.m_context.m_uri.substr(0, openingParenthesis) + '(' + sourceObj->getUuid() + ')';
					on_GetDataObject(nextGr, correlationId, result);
				}
			}
		}
	}
}

void MyOwnDiscoveryProtocolHandlers::on_GetResources(const Energistics::Etp::v12::Protocol::Discovery::GetResources & msg, int64_t correlationId)
{
	std::cout << "Discovery graph resource received uri : " << msg.m_context.m_uri << std::endl;

	if (msg.m_context.m_depth < 0) {
		session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(5, "The requested depth cannot be inferior to zero."), correlationId, 0x01 | 0x02);
		return;
	}

	Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse mb;
	if (msg.m_context.m_uri.back() == ')') { // dataobject
		if (session->validateDataObjectUri(msg.m_context.m_uri, true).m_code > -1) {
			return;
		}

		on_GetDataObject(msg, correlationId, mb.m_resources);
	}
	else { // eml, dataspace
		if (session->validateUri(msg.m_context.m_uri, true).m_code > -1) {
			return;
		}

		Energistics::Etp::v12::Protocol::Discovery::GetResources nextGr = msg;
		--nextGr.m_context.m_depth;
		if (msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources ||
			msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf) {
			nextGr.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf;
		}
		else if (msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets ||
			msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {
			nextGr.m_scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf;
		}

		std::unordered_map< std::string, std::vector<COMMON_NS::AbstractObject*> > groupedDataObj;
		if (msg.m_context.m_uri == "eml:///") {
			groupedDataObj = repo->getDataObjectsGroupedByDataType();
		}
		else {
			Energistics::Etp::v12::Protocol::Core::ProtocolException pe;
			Energistics::Etp::v12::Datatypes::ErrorInfo error;
			error.m_code = 9;
			error.m_message = "The URI " + msg.m_context.m_uri + " targets something which does not exist.";
			pe.m_error.set_ErrorInfo(error);

			session->send(pe, correlationId, 0x01 | 0x02);
			return;
		}

		for (const auto & pair : groupedDataObj) {
			for (const auto & obj : pair.second) {
				nextGr.m_context.m_uri = ETP_NS::EtpHelpers::buildUriFromEnergisticsObject(obj);
				on_GetDataObject(nextGr, correlationId, mb.m_resources);
			}
		}
	}

	session->send(mb, correlationId, 0x01 | 0x02);
}
/*
void MyOwnDiscoveryProtocolHandlers::on_GetDataspaces(const Energistics::Etp::v12::Protocol::Discovery::GetDataspaces & msg, int64_t correlationId)
{
	std::cout << "Discovery dataspace received uri : " << msg.m_uri << std::endl;

	if (session->validateUri(msg.m_uri, true).m_code > -1) {
		return;
	}

	Energistics::Etp::v12::Protocol::Discovery::GetDataspacesResponse mb;

	session->send(mb, correlationId, 0x01 | 0x02);
}

void MyOwnDiscoveryProtocolHandlers::on_GetNamespaces(const Energistics::Etp::v12::Protocol::Discovery::GetNamespaces & msg, int64_t correlationId)
{
	std::cout << "Discovery namespace received" << std::endl;

	Energistics::Etp::v12::Protocol::Discovery::GetNamespacesResponse mb;
	on_GetEmlColonSlashSlash(msg, correlationId, mb.m_uris);

	session->send(mb, correlationId, 0x01 | 0x02);
}
*/
void MyOwnDiscoveryProtocolHandlers::on_GetSupportedTypes(const Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypes & msg, int64_t correlationId)
{
	std::cout << "Discovery supported types received uri " << msg.m_uri  << std::endl;

	// We don't support model discovery use case.
	if (msg.m_returnEmptyTypes) {
		Energistics::Etp::v12::Protocol::Core::ProtocolException pe;
		Energistics::Etp::v12::Datatypes::ErrorInfo error;
		error.m_code = 7;
		error.m_message = "ReturnEmptyTypes attribute is not supported by the agent.";
		pe.m_error.set_ErrorInfo(error);

		session->send(pe, correlationId, 0x01);
	}

	if (session->validateUri(msg.m_uri, true).m_code > -1) {
		return;
	}

	Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypesResponse response;
	if (msg.m_uri.back() == ')') { // dataobject
		const size_t openingParenthesis = msg.m_uri.find('(', 5);
		COMMON_NS::AbstractObject* obj = repo->getDataObjectByUuid(msg.m_uri.substr(openingParenthesis + 1, 36));

		if (obj == nullptr) {
			Energistics::Etp::v12::Protocol::Core::ProtocolException pe;
			Energistics::Etp::v12::Datatypes::ErrorInfo error;
			error.m_code = 9;
			error.m_message = "The URI " + msg.m_uri + "  targets something which does not exist.";
			pe.m_error.set_ErrorInfo(error);

			session->send(pe, correlationId, 0x01 | 0x02);
			return;
		}

		// SELF
		if (msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self ||
			msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf ||
			msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf) {
			auto sameCt = repo->getDataObjectsByContentType(obj->getContentType());
			Energistics::Etp::v12::Datatypes::Object::SupportedType st;
			st.m_dataObjectType = obj->getQualifiedType();
			if (msg.m_countObjects) {
				st.m_objectCount.set_int(sameCt.size());
			}
			else {
				st.m_objectCount.set_null();
			}
			response.m_supportedTypes.push_back(st);
		}

		std::vector< COMMON_NS::AbstractObject * > groupedByRel;
		std::unordered_map< std::string, std::vector<COMMON_NS::AbstractObject*> > groupedByTargets;
		if (msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets ||
			msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {
			groupedByRel = repo->getTargetObjects(obj);
		}
		else if (msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources ||
			msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf) {
			groupedByRel = repo->getSourceObjects(obj);
		}

		for (const auto & rel : groupedByRel) {
			groupedByTargets[rel->getQualifiedType()].push_back(rel);
		}
		for (const auto & dataObjectType : groupedByTargets) {
			Energistics::Etp::v12::Datatypes::Object::SupportedType st;
			st.m_dataObjectType = dataObjectType.first;
			if (msg.m_countObjects) {
				st.m_objectCount.set_int(dataObjectType.second.size());
			}
			else {
				st.m_objectCount.set_null();
			}
			response.m_supportedTypes.push_back(st);
		}
	}
	else { // eml or dataspace 
		// msg.m_scope is irrelevant
		std::unordered_map< std::string, std::vector<COMMON_NS::AbstractObject*> > groupedDataObj;
		if (msg.m_uri == "eml:///") {
			groupedDataObj = repo->getDataObjectsGroupedByDataType();
		}
		else {
			Energistics::Etp::v12::Protocol::Core::ProtocolException pe;
			Energistics::Etp::v12::Datatypes::ErrorInfo error;
			error.m_code = 9;
			error.m_message = "The URI " + msg.m_uri + "  targets something which does not exist.";
			pe.m_error.set_ErrorInfo(error);

			session->send(pe, correlationId, 0x01 | 0x02);
			return;
		}

		for (const auto & obj : groupedDataObj) {
			Energistics::Etp::v12::Datatypes::Object::SupportedType st;
			st.m_dataObjectType = obj.first;
			if (msg.m_countObjects) {
				st.m_objectCount.set_int(obj.second.size());
			}
			else {
				st.m_objectCount.set_null();
			}
			response.m_supportedTypes.push_back(st);
		}
	}

	session->send(response, correlationId, 0x01 | 0x02);
}
