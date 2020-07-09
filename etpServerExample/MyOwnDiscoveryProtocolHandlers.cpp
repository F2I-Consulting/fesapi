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

#include "eml2/AbstractHdfProxy.h"
#include "resqml2_0_1/TriangulatedSetRepresentation.h"
#include "resqml2_0_1/Grid2dRepresentation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "resqml2_0_1/IjkGridParametricRepresentation.h"

#include "MyDataObjectRepository.h"

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
void MyOwnDiscoveryProtocolHandlers::on_GetDataObjects(const Energistics::Etp::v12::Protocol::Discovery::GetResources & msg, int64_t correlationId,
	std::vector<Energistics::Etp::v12::Datatypes::Object::Resource> & result)
{
	Energistics::Etp::v12::Datatypes::Object::Resource resource;
	resource.m_dataObjectType = "";

	if (msg.m_context.m_depth >= 0) {
		const size_t dataspacePos = msg.m_context.m_uri.find("dataspace");
		const size_t openingParenthesis = dataspacePos != std::string::npos ? msg.m_context.m_uri.find('(', dataspacePos + 10) : msg.m_context.m_uri.find('(', 5);
		COMMON_NS::AbstractObject* obj = repo->getDataObjectByUuid(msg.m_context.m_uri.substr(openingParenthesis + 1, 36));
		if (obj == nullptr) {
			Energistics::Etp::v12::Protocol::Core::ProtocolException pe;
			Energistics::Etp::v12::Datatypes::ErrorInfo error;
			error.m_code = 9;
			error.m_message = "The URI " + msg.m_context.m_uri + " targets something which does not exist.";
			pe.m_error.set_ErrorInfo(error);

			session->send(pe, correlationId);
			return;
		}

		// Self
		if (msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self ||
			msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf ||
			msg.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {

			time_t lastUpdate = -1;
			if (msg.m_storeLastWriteFilter && !obj->isPartial()) {
				lastUpdate = obj->getLastUpdate();
				if (lastUpdate < 0) {
					lastUpdate = obj->getCreation();
				}
				lastUpdate *= 1e6; // ETP Last update must be in micro seconds.
			}
			std::string qualifiedType = obj->getQualifiedType();
			std::string namespaceStar = qualifiedType.substr(0, qualifiedType.find(".") + 1) + "*";
			if ((msg.m_context.m_dataObjectTypes.empty() || std::find(msg.m_context.m_dataObjectTypes.begin(), msg.m_context.m_dataObjectTypes.end(), qualifiedType) != msg.m_context.m_dataObjectTypes.end()
				|| std::find(msg.m_context.m_dataObjectTypes.begin(), msg.m_context.m_dataObjectTypes.end(), namespaceStar) != msg.m_context.m_dataObjectTypes.end())
				&& (!msg.m_storeLastWriteFilter || lastUpdate >= msg.m_storeLastWriteFilter.get())) {
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
					on_GetDataObjects(nextGr, correlationId, result);
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
					on_GetDataObjects(nextGr, correlationId, result);
				}
			}
		}
	}
}

void MyOwnDiscoveryProtocolHandlers::on_GetResources(const Energistics::Etp::v12::Protocol::Discovery::GetResources & msg, int64_t correlationId)
{
	std::cout << "Discovery graph resource received uri : " << msg.m_context.m_uri << std::endl;

	if (msg.m_context.m_depth < 0) {
		session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(5, "The requested depth cannot be inferior to zero."), correlationId, 0x02);
		return;
	}

	Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse mb;
	if ((msg.m_context.m_uri.find("eml2") != std::string::npos ||
		msg.m_context.m_uri.find("resqml2") != std::string::npos ||
		msg.m_context.m_uri.find("witsml2") != std::string::npos ||
		msg.m_context.m_uri.find("prodml2") != std::string::npos) &&
		msg.m_context.m_uri.back() == ')') { // dataobject
		if (ETP_NS::EtpHelpers::validateDataObjectUri(msg.m_context.m_uri, session).m_code > -1) {
			return;
		}

		on_GetDataObjects(msg, correlationId, mb.m_resources);
	}
	else { // eml, dataspace
		if (ETP_NS::EtpHelpers::validateUri(msg.m_context.m_uri, session).m_code > -1) {
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
		if (msg.m_context.m_uri == "eml:///" || msg.m_context.m_uri == "eml:/" ||
			msg.m_context.m_uri == "eml:///dataspace()" || msg.m_context.m_uri == "eml:/dataspace()") {
			groupedDataObj = repo->getDataObjectsGroupedByDataType();
		}
		else {
			Energistics::Etp::v12::Protocol::Core::ProtocolException pe;
			Energistics::Etp::v12::Datatypes::ErrorInfo error;
			error.m_code = 9;
			error.m_message = "The URI " + msg.m_context.m_uri + " targets something which does not exist.";
			pe.m_error.set_ErrorInfo(error);

			session->send(pe, correlationId, 0x02);
			return;
		}

		for (const auto & pair : groupedDataObj) {
			for (const auto & obj : pair.second) {
				nextGr.m_context.m_uri = ETP_NS::EtpHelpers::buildUriFromEnergisticsObject(obj);
				on_GetDataObjects(nextGr, correlationId, mb.m_resources);
			}
		}
	}

	session->send(mb, correlationId, 0x02);
}
