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
#include  "StoreNotificationHandlers.h"

#include "../AbstractSession.h"
#include "../EtpHelpers.h"

#include "../../tools/date.h"

using namespace ETP_NS;

void StoreNotificationHandlers::decodeMessageBody(const Energistics::Etp::v12::Datatypes::MessageHeader & mh, avro::DecoderPtr d)
{
	if (mh.protocol != Energistics::Etp::v12::Datatypes::Protocol::StoreNotification) {
		std::cerr << "Error : This message header does not belong to the protocol Store" << std::endl;
		return;
	}

	if (mh.messageType == Energistics::Etp::v12::Protocol::StoreNotification::SubscribeNotifications::messageTypeId) {
		Energistics::Etp::v12::Protocol::StoreNotification::SubscribeNotifications msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_SubscribeNotifications(msg, mh.messageId);
	}
	else if (mh.messageType == Energistics::Etp::v12::Protocol::StoreNotification::UnsubscribeNotifications::messageTypeId) {
		Energistics::Etp::v12::Protocol::StoreNotification::UnsubscribeNotifications msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_UnsubscribeNotifications(msg, mh.messageId, mh.correlationId);
	}
	else if (mh.messageType == Energistics::Etp::v12::Protocol::StoreNotification::UnsolicitedStoreNotifications::messageTypeId) {
		Energistics::Etp::v12::Protocol::StoreNotification::UnsolicitedStoreNotifications msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_UnsolicitedStoreNotifications(msg, mh.messageId);
	}
	else if (mh.messageType == Energistics::Etp::v12::Protocol::StoreNotification::SubscriptionEnded::messageTypeId) {
		Energistics::Etp::v12::Protocol::StoreNotification::SubscriptionEnded msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_SubscriptionEnded(msg, mh.correlationId);
	}
	else if (mh.messageType == Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged::messageTypeId) {
		Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_ObjectChanged(msg, mh.correlationId);
	}
	else if (mh.messageType == Energistics::Etp::v12::Protocol::StoreNotification::ObjectDeleted::messageTypeId) {
		Energistics::Etp::v12::Protocol::StoreNotification::ObjectDeleted msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_ObjectDeleted(msg, mh.correlationId);
	}
	else if (mh.messageType == Energistics::Etp::v12::Protocol::StoreNotification::ObjectAccessRevoked::messageTypeId) {
		Energistics::Etp::v12::Protocol::StoreNotification::ObjectAccessRevoked msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_ObjectAccessRevoked(msg, mh.correlationId);
	}
	else {
		session->flushReceivingBuffer();
		session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(3, "The message type ID " + std::to_string(mh.messageType) + " is invalid for the store notification protocol."), mh.messageId, 0x02);
	}
}

void StoreNotificationHandlers::on_SubscribeNotifications(const Energistics::Etp::v12::Protocol::StoreNotification::SubscribeNotifications &, int64_t)
{
	std::cout << "on_SubscribeNotifications" << std::endl;

	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The StoreHandlers::on_SubscribeNotifications method has not been overriden by the agent."), 0x02);
}

void StoreNotificationHandlers::on_UnsubscribeNotifications(const Energistics::Etp::v12::Protocol::StoreNotification::UnsubscribeNotifications & msg, int64_t messageId, int64_t)
{
	std::cout << "on_UnsubscribeNotifications" << std::endl;

	int64_t toRemove = (std::numeric_limits<int64_t>::max)();
	for (const auto& pair : session->subscriptions) {
		if (pair.second.requestUuid.array == msg.requestUuid.array) {
			toRemove = pair.first;
			break;
		}
	}

	if (toRemove != (std::numeric_limits<int64_t>::max)()) {
		session->subscriptions.erase(toRemove);
	}
	else {
		session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(5, "The subscription request UUID is unknown by the store."), messageId, 0x02);
	}
}

void StoreNotificationHandlers::on_UnsolicitedStoreNotifications(const Energistics::Etp::v12::Protocol::StoreNotification::UnsolicitedStoreNotifications &, int64_t)
{
	std::cout << "Received UnsolicitedStoreNotifications" << std::endl;
}

void StoreNotificationHandlers::on_SubscriptionEnded(const Energistics::Etp::v12::Protocol::StoreNotification::SubscriptionEnded &, int64_t)
{
	std::cout << "Received SubscriptionEnded " << std::endl;
}

void StoreNotificationHandlers::on_ObjectChanged(const Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged & msg, int64_t)
{
	switch (msg.change.changeKind) {
	case Energistics::Etp::v12::Datatypes::Object::ObjectChangeKind::authorized: std::cout << "authorized "; break;
	case Energistics::Etp::v12::Datatypes::Object::ObjectChangeKind::insert: std::cout << "insert "; break;
	case Energistics::Etp::v12::Datatypes::Object::ObjectChangeKind::update: std::cout << "update "; break;
	}

	auto duration = std::chrono::microseconds(msg.change.changeTime);
	std::cout << "on " << date::format("%FT%TZ", date::floor<std::chrono::microseconds>(duration)) << std::endl;

	printDataObject(msg.change.dataObject);

	std::cout << std::endl;
}

void StoreNotificationHandlers::on_ObjectDeleted(const Energistics::Etp::v12::Protocol::StoreNotification::ObjectDeleted &, int64_t correlationId)
{
	std::cout << "on_ObjectDeleted" << std::endl;

	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The StoreHandlers::on_ObjectDeleted method has not been overriden by the agent."), correlationId, 0x02);
}

void StoreNotificationHandlers::on_ObjectAccessRevoked(const Energistics::Etp::v12::Protocol::StoreNotification::ObjectAccessRevoked &, int64_t correlationId)
{
	std::cout << "on_ObjectAccessRevoked" << std::endl;

	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The StoreHandlers::on_ObjectAccessRevoked method has not been overriden by the agent."), correlationId, 0x02);
}
