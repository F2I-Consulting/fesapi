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

#include "common/AbstractObject.h"
#include "etp/EtpHelpers.h"

#include "MyDataObjectRepository.h"

void MyOwnDiscoveryProtocolHandlers::getDataObjectResource(const Energistics::Etp::v12::Protocol::Discovery::GetResources & msg, int64_t correlationId,
	std::vector<Energistics::Etp::v12::Datatypes::Object::Resource> & result)
{
	if (msg.context.depth >= 0) {
		const size_t dataspacePos = msg.context.uri.find("eml:///dataspace");
		if (dataspacePos != std::string::npos) {
			Energistics::Etp::v12::Protocol::Core::ProtocolException pe;
			Energistics::Etp::v12::Datatypes::ErrorInfo error;
			error.code = 9;
			error.message = "The URI " + msg.context.uri + " defines a datspace which does not exist on this store.";
			pe.error.emplace(error);

			session->send(pe, correlationId);
			return;
		}

		const size_t openingParenthesis = msg.context.uri.find('(', 13); // 13 for "eml:///eml20.*" assuming the shortest namespace is eml20 and the shortest datatype is a minimum of one letter
		COMMON_NS::AbstractObject* obj = repo->getDataObjectByUuid(msg.context.uri.substr(openingParenthesis + 1, 36));
		if (obj == nullptr) {
			Energistics::Etp::v12::Protocol::Core::ProtocolException pe;
			Energistics::Etp::v12::Datatypes::ErrorInfo error;
			error.code = 9;
			error.message = "The URI " + msg.context.uri + " targets something which does not exist.";
			pe.error.emplace(error);

			session->send(pe, correlationId);
			return;
		}

		// Self
		if (msg.scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self ||
			msg.scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf ||
			msg.scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {

			std::string qualifiedType = obj->getQualifiedType();
			std::string namespaceStar = qualifiedType.substr(0, qualifiedType.find(".") + 1) + "*";
			if (msg.context.dataObjectTypes.empty() || std::find(msg.context.dataObjectTypes.begin(), msg.context.dataObjectTypes.end(), qualifiedType) != msg.context.dataObjectTypes.end()
				|| std::find(msg.context.dataObjectTypes.begin(), msg.context.dataObjectTypes.end(), namespaceStar) != msg.context.dataObjectTypes.end()) {
				result.push_back(ETP_NS::EtpHelpers::buildEtpResourceFromEnergisticsObject(obj, msg.countObjects));
			}
		}

		if (msg.context.depth >= 1 && msg.context.navigableEdges != Energistics::Etp::v12::Datatypes::Object::RelationshipKind::Secondary) {
			// Target
			if (msg.scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets ||
				msg.scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {
				Energistics::Etp::v12::Protocol::Discovery::GetResources nextGr = msg;
				--nextGr.context.depth;
				nextGr.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf;

				for (const auto* targetObj : repo->getTargetObjects(obj)) {
					nextGr.context.uri = msg.context.uri.substr(0, openingParenthesis) + '(' + targetObj->getUuid() + ')';
					getDataObjectResource(nextGr, correlationId, result);
				}
			}

			// Source
			if (msg.scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources ||
				msg.scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf) {
				Energistics::Etp::v12::Protocol::Discovery::GetResources nextGr = msg;
				--nextGr.context.depth;
				nextGr.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf;
				
				for (const auto* sourceObj : repo->getSourceObjects(obj)) {
					nextGr.context.uri = msg.context.uri.substr(0, openingParenthesis) + '(' + sourceObj->getUuid() + ')';
					getDataObjectResource(nextGr, correlationId, result);
				}
			}
		}
	}
}

void MyOwnDiscoveryProtocolHandlers::on_GetResources(const Energistics::Etp::v12::Protocol::Discovery::GetResources & msg, int64_t correlationId)
{
	std::cout << "Discovery graph resource received uri : " << msg.context.uri << std::endl;

	if (msg.context.depth < 0) {
		session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(5, "The requested depth cannot be inferior to zero."), correlationId, 0x02);
		return;
	}

	if (msg.storeLastWriteFilter) {
		session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "This end point does not support store last write filter yet."), correlationId, 0x02);
		return;
	}

	if (msg.includeEdges) {
		session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "This end point does not support include edges yet."), correlationId, 0x02);
		return;
	}

	Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse mb;
	if ((msg.context.uri.find("eml2") != std::string::npos ||
		msg.context.uri.find("resqml2") != std::string::npos ||
		msg.context.uri.find("witsml2") != std::string::npos ||
		msg.context.uri.find("prodml2") != std::string::npos) &&
		msg.context.uri.back() == ')') { // dataobject
		if (ETP_NS::EtpHelpers::validateDataObjectUri(msg.context.uri, session).code > -1) {
			return;
		}

		getDataObjectResource(msg, correlationId, mb.resources);
	}
	else { // eml, dataspace
		if (ETP_NS::EtpHelpers::validateUri(msg.context.uri, session).code > -1) {
			return;
		}

		Energistics::Etp::v12::Protocol::Discovery::GetResources nextGr = msg;
		--nextGr.context.depth;
		if (msg.scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources ||
			msg.scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf) {
			nextGr.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf;
		}
		else if (msg.scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets ||
			msg.scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {
			nextGr.scope = Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf;
		}

		std::unordered_map< std::string, std::vector<COMMON_NS::AbstractObject*> > groupedDataObj;
		if (msg.context.uri == "eml:///") {
			groupedDataObj = repo->getDataObjectsGroupedByDataType();
		}
		else {
			Energistics::Etp::v12::Protocol::Core::ProtocolException pe;
			Energistics::Etp::v12::Datatypes::ErrorInfo error;
			error.code = 9;
			error.message = "The URI " + msg.context.uri + " targets something which does not exist.";
			pe.error.emplace(error);

			session->send(pe, correlationId, 0x02);
			return;
		}

		for (const auto & pair : groupedDataObj) {
			for (const auto* obj : pair.second) {
				nextGr.context.uri = ETP_NS::EtpHelpers::buildUriFromEnergisticsObject(obj);
				getDataObjectResource(nextGr, correlationId, mb.resources);
			}
		}
	}

	session->send(mb, correlationId, 0x02);
}
