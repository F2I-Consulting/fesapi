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
#include "MyOwnStoreNotificationProtocolHandlers.h"

#include <memory>

#include <etp/AbstractSession.h>
#include <etp/EtpHelpers.h>

#include "MyDataObjectRepository.h"

MyOwnStoreNotificationProtocolHandlers::MyOwnStoreNotificationProtocolHandlers(ETP_NS::AbstractSession* mySession, MyDataObjectRepository* repo_) :
	ETP_NS::StoreNotificationHandlers(mySession), repo(repo_) {}

void MyOwnStoreNotificationProtocolHandlers::on_SubscribeNotifications(const Energistics::Etp::v12::Protocol::StoreNotification::SubscribeNotifications & msg, int64_t messageId)
{
	for (const auto& subscriptionInfo : msg.request) {
		session->subscriptions[messageId] = subscriptionInfo.second;

		auto journal = repo->getJournal();
		auto startime = subscriptionInfo.second.startTime;
		const auto firstInJournal = std::find_if(journal.begin(), journal.end(),
			[startime](const std::tuple<std::chrono::time_point<std::chrono::system_clock>, COMMON_NS::DataObjectReference, COMMON_NS::DataObjectRepository::CUD>& entry) {
			return std::chrono::duration_cast<std::chrono::seconds>(std::get<0>(entry).time_since_epoch()).count() > startime; });
		std::vector<std::pair<std::chrono::time_point<std::chrono::system_clock>, COMMON_NS::AbstractObject*>> created;
		std::vector<std::pair<std::chrono::time_point<std::chrono::system_clock>, COMMON_NS::AbstractObject*>> updated;
		for (auto it = firstInJournal; it != journal.end(); ++it) {
			COMMON_NS::AbstractObject* obj = repo->getDataObjectByUuidAndVersion(std::get<1>(*it).getUuid(), std::get<1>(*it).getVersion());
			if (std::get<2>(*it) == COMMON_NS::DataObjectRepository::CREATED) {
				created.push_back(std::make_pair(std::get<0>(*it), obj));
			}
			else if (std::get<2>(*it) == COMMON_NS::DataObjectRepository::UPDATED) {
				updated.push_back(std::make_pair(std::get<0>(*it), obj));
			}
		}

		if (!created.empty()) {
			repo->on_CreateDataObject(created);
		}
		if (!updated.empty()) {
			repo->on_UpdateDataObject(created);
		}
	}
}
