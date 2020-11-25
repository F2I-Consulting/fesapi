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
	std::pair<std::string, std::string> uuidAndVersion = ETP_NS::EtpHelpers::getUuidAndVersionFromUri(uri);

	COMMON_NS::AbstractObject* result = getDataObjectByUuidAndVersion(uuidAndVersion.first, uuidAndVersion.second);
	if (result == nullptr) {
		throw ETP_NS::EtpException(11, uuidAndVersion.first + " version \"" + uuidAndVersion.second + "\" cannot be resolved as a data object in this store.");
	}

	return result;
}

void MyDataObjectRepository::on_CreateDataObject(const std::vector<std::pair<std::chrono::time_point<std::chrono::system_clock>, COMMON_NS::AbstractObject*>>& created)
{
	for (auto session : sessions) {
		for (const auto& subscription : session->subscriptions) {
			if (subscription.second.context.uri == "eml:///") {
				for (const auto& oneCreated : created) {
					const std::vector<std::string>& filter = subscription.second.context.dataObjectTypes;
					if (filter.empty() ||
						std::find(filter.begin(), filter.end(), oneCreated.second->getQualifiedType()) != filter.end() ||
						std::find(filter.begin(), filter.end(), oneCreated.second->getXmlNamespace() + ".*") != filter.end()) {
						Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged msg;
						msg.change.changeKind = Energistics::Etp::v12::Datatypes::Object::ObjectChangeKind::insert;
						msg.change.changeTime = std::chrono::duration_cast<std::chrono::seconds>(oneCreated.first.time_since_epoch()).count(); // on most implementations, system clock epoch is the UNIX one.
						msg.change.dataObject = ETP_NS::EtpHelpers::buildEtpDataObjectFromEnergisticsObject(oneCreated.second, subscription.second.includeObjectData);
						session->send(msg, subscription.first);
					}
				}
			}
			else {
				const std::vector<COMMON_NS::AbstractObject*>& allSubscriptionObjs = getDataObjects(subscription.second);
				for (const auto& oneCreated : created) {
					if (std::find(allSubscriptionObjs.begin(), allSubscriptionObjs.end(), oneCreated.second) != allSubscriptionObjs.end()) {
						Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged msg;
						msg.change.changeKind = Energistics::Etp::v12::Datatypes::Object::ObjectChangeKind::insert;
						msg.change.changeTime = std::chrono::duration_cast<std::chrono::seconds>(oneCreated.first.time_since_epoch()).count(); // on most implementations, system clock epoch is the UNIX one.
						msg.change.dataObject = ETP_NS::EtpHelpers::buildEtpDataObjectFromEnergisticsObject(oneCreated.second, subscription.second.includeObjectData);
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
			if (subscription.second.context.uri == "eml:///") {
				for (const auto& oneUpdated : updated) {
					const std::vector<std::string>& filter = subscription.second.context.dataObjectTypes;
					if (filter.empty() ||
						std::find(filter.begin(), filter.end(), oneUpdated.second->getQualifiedType()) != filter.end() ||
						std::find(filter.begin(), filter.end(), oneUpdated.second->getXmlNamespace() + ".*") != filter.end()) {
						Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged msg;
						msg.change.changeKind = Energistics::Etp::v12::Datatypes::Object::ObjectChangeKind::update;
						msg.change.changeTime = std::chrono::duration_cast<std::chrono::seconds>(oneUpdated.first.time_since_epoch()).count(); // on most implementations, system clock epoch is the UNIX one.
						msg.change.dataObject = ETP_NS::EtpHelpers::buildEtpDataObjectFromEnergisticsObject(oneUpdated.second, subscription.second.includeObjectData);
						session->send(msg, subscription.first);
					}
				}
			}
			else {
				const std::vector<COMMON_NS::AbstractObject*>& allSubscriptionObjs = getDataObjects(subscription.second);
				for (const auto& oneUpdated : updated) {
					if (std::find(allSubscriptionObjs.begin(), allSubscriptionObjs.end(), oneUpdated.second) != allSubscriptionObjs.end()) {
						Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged msg;
						msg.change.changeKind = Energistics::Etp::v12::Datatypes::Object::ObjectChangeKind::update;
						msg.change.changeTime = std::chrono::duration_cast<std::chrono::seconds>(oneUpdated.first.time_since_epoch()).count(); // on most implementations, system clock epoch is the UNIX one.
						msg.change.dataObject = ETP_NS::EtpHelpers::buildEtpDataObjectFromEnergisticsObject(oneUpdated.second, subscription.second.includeObjectData);
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
	COMMON_NS::AbstractObject* root = getObjectFromUri(subscriptionInfo.context.uri);
	if (root == nullptr) {
		return result;
	}

	if (subscriptionInfo.scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::self ||
		subscriptionInfo.scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf ||
		subscriptionInfo.scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf) {
		result.push_back(root);
	}

	if (subscriptionInfo.scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sourcesOrSelf ||
		subscriptionInfo.scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::sources) {
		const std::vector<COMMON_NS::AbstractObject*>& allSources = getSourceObjects(root, subscriptionInfo.context.depth, subscriptionInfo.context.dataObjectTypes);
		result.insert(result.end(), allSources.begin(), allSources.end());
	}
		
	if (subscriptionInfo.scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targetsOrSelf ||
		subscriptionInfo.scope == Energistics::Etp::v12::Datatypes::Object::ContextScopeKind::targets) {
		const std::vector<COMMON_NS::AbstractObject*>& allTargets = getTargetObjects(root, subscriptionInfo.context.depth, subscriptionInfo.context.dataObjectTypes);
		result.insert(result.end(), allTargets.begin(), allTargets.end());
	}

	return result;
}
