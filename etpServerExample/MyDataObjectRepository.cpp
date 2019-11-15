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
#pragma once

#include "MyDataObjectRepository.h"

#include <chrono>

#include "etp/EtpException.h"
#include "etp/EtpHelpers.h"

#include "common/AbstractObject.h"

COMMON_NS::AbstractObject* MyDataObjectRepository::getObjectFromUri(const std::string & uri) const
{
	Energistics::Etp::v12::Datatypes::ErrorInfo error = ETP_NS::EtpHelpers::validateDataObjectUri(uri);
	if (error.m_code > -1) {
		throw ETP_NS::EtpException(error.m_code, error.m_message);
	}

	if (uri[6] != '/') {
		throw ETP_NS::EtpException(2, "The URI " + uri + " uses some dataspaces. This agent does not support dataspace.");
	}

	const size_t openingParenthesisPos = uri.find('(');
	const std::string uuid = uri.substr(openingParenthesisPos + 1, 36);
	const size_t comma = uri.find(',');
	const size_t closingParenthesisPos = comma == std::string::npos ? std::string::npos : uri.find(')');
	const std::string version = (comma == std::string::npos || closingParenthesisPos == std::string::npos) ? "" : uri.substr(comma + 1, closingParenthesisPos - comma - 1);

	COMMON_NS::AbstractObject* result = getDataObjectByUuidAndVersion(uuid, version);
	if (result == nullptr) {
		throw ETP_NS::EtpException(11, uuid + " version \"" + version + "\" cannot be resolved as a data object in this store.");
	}

	return result;
}

void MyDataObjectRepository::on_CreateDataObject(const std::vector<std::pair<std::chrono::time_point<std::chrono::system_clock>, COMMON_NS::AbstractObject*>>& created)
{
	for (auto session : sessions) {
		for (const auto& subscription : session->subscriptions) {
			if (subscription.second.m_context.m_uri == "eml:///") {
				for (const auto& oneCreated : created) {
					const std::vector<std::string>& filter = subscription.second.m_context.m_dataObjectTypes;
					if (filter.empty() ||
						std::find(filter.begin(), filter.end(), oneCreated.second->getQualifiedType()) != filter.end() ||
						std::find(filter.begin(), filter.end(), oneCreated.second->getXmlNamespace() + ".*") != filter.end()) {
						Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged msg;
						msg.m_change.m_changeKind = Energistics::Etp::v12::Datatypes::Object::ObjectChangeKind::insert;
						msg.m_change.m_changeTime = std::chrono::duration_cast<std::chrono::seconds>(oneCreated.first.time_since_epoch()).count(); // on most implementations, system clock epoch is the UNIX one.
						msg.m_change.m_dataObject = ETP_NS::EtpHelpers::buildEtpDataObjectFromEnergisticsObject(oneCreated.second, subscription.second.m_includeObjectData);
						session->send(msg, subscription.first);
					}
				}
			}
			else {
				const std::vector<COMMON_NS::AbstractObject*>& allSubscriptionObjs = getDataObjects(subscription.second);
				for (const auto& oneCreated : created) {
					if (std::find(allSubscriptionObjs.begin(), allSubscriptionObjs.end(), oneCreated.second) != allSubscriptionObjs.end()) {
						Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged msg;
						msg.m_change.m_changeKind = Energistics::Etp::v12::Datatypes::Object::ObjectChangeKind::insert;
						msg.m_change.m_changeTime = std::chrono::duration_cast<std::chrono::seconds>(oneCreated.first.time_since_epoch()).count(); // on most implementations, system clock epoch is the UNIX one.
						msg.m_change.m_dataObject = ETP_NS::EtpHelpers::buildEtpDataObjectFromEnergisticsObject(oneCreated.second, subscription.second.m_includeObjectData);
						session->send(msg, subscription.first);
					}
				}
			}
		}
	}
}

void MyDataObjectRepository::on_UpdateDataObject(const std::vector<std::pair<std::chrono::time_point<std::chrono::system_clock>, COMMON_NS::AbstractObject*>>& updated)
{
	for (auto session : sessions) {
		for (const auto& subscription : session->subscriptions) {
			if (subscription.second.m_context.m_uri == "eml:///") {
				for (const auto& oneUpdated : updated) {
					const std::vector<std::string>& filter = subscription.second.m_context.m_dataObjectTypes;
					if (filter.empty() ||
						std::find(filter.begin(), filter.end(), oneUpdated.second->getQualifiedType()) != filter.end() ||
						std::find(filter.begin(), filter.end(), oneUpdated.second->getXmlNamespace() + ".*") != filter.end()) {
						Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged msg;
						msg.m_change.m_changeKind = Energistics::Etp::v12::Datatypes::Object::ObjectChangeKind::update;
						msg.m_change.m_changeTime = std::chrono::duration_cast<std::chrono::seconds>(oneUpdated.first.time_since_epoch()).count(); // on most implementations, system clock epoch is the UNIX one.
						msg.m_change.m_dataObject = ETP_NS::EtpHelpers::buildEtpDataObjectFromEnergisticsObject(oneUpdated.second, subscription.second.m_includeObjectData);
						session->send(msg, subscription.first);
					}
				}
			}
			else {
				const std::vector<COMMON_NS::AbstractObject*>& allSubscriptionObjs = getDataObjects(subscription.second);
				for (const auto& oneUpdated : updated) {
					if (std::find(allSubscriptionObjs.begin(), allSubscriptionObjs.end(), oneUpdated.second) != allSubscriptionObjs.end()) {
						Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged msg;
						msg.m_change.m_changeKind = Energistics::Etp::v12::Datatypes::Object::ObjectChangeKind::update;
						msg.m_change.m_changeTime = std::chrono::duration_cast<std::chrono::seconds>(oneUpdated.first.time_since_epoch()).count(); // on most implementations, system clock epoch is the UNIX one.
						msg.m_change.m_dataObject = ETP_NS::EtpHelpers::buildEtpDataObjectFromEnergisticsObject(oneUpdated.second, subscription.second.m_includeObjectData);
						session->send(msg, subscription.first);
					}
				}
			}
		}
	}
}

std::vector<COMMON_NS::AbstractObject*> MyDataObjectRepository::getDataObjects(const Energistics::Etp::v12::Datatypes::Object::SubscriptionInfo& subscriptionInfo) const
{
	std::vector<COMMON_NS::AbstractObject*> result;
	COMMON_NS::AbstractObject* root = getObjectFromUri(subscriptionInfo.m_context.m_uri);
	if (root == nullptr) {
		return result;
	}

	if (subscriptionInfo.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self ||
		subscriptionInfo.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf ||
		subscriptionInfo.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {
		result.push_back(root);
	}

	if (subscriptionInfo.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf ||
		subscriptionInfo.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources) {
		const std::vector<COMMON_NS::AbstractObject*>& allSources = getSourceObjects(root, subscriptionInfo.m_context.m_depth, subscriptionInfo.m_context.m_dataObjectTypes);
		result.insert(result.end(), allSources.begin(), allSources.end());
	}
		
	if (subscriptionInfo.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf ||
		subscriptionInfo.m_scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets) {
		const std::vector<COMMON_NS::AbstractObject*>& allTargets = getTargetObjects(root, subscriptionInfo.m_context.m_depth, subscriptionInfo.m_context.m_dataObjectTypes);
		result.insert(result.end(), allTargets.begin(), allTargets.end());
	}

	return result;
}
