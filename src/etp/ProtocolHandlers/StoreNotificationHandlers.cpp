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
#include  "etp/ProtocolHandlers/StoreNotificationHandlers.h"

#include "etp/AbstractSession.h"
#include "etp/EtpHelpers.h"

using namespace ETP_NS;

void StoreNotificationHandlers::decodeMessageBody(const Energistics::Etp::v12::Datatypes::MessageHeader & mh, avro::DecoderPtr d)
{
	if (mh.m_protocol != Energistics::Etp::v12::Datatypes::Protocol::StoreNotification) {
		std::cerr << "Error : This message header does not belong to the protocol Store" << std::endl;
		return;
	}

	if (mh.m_messageType == Energistics::Etp::v12::Protocol::StoreNotification::SubscribeNotifications::messageTypeId) {
		Energistics::Etp::v12::Protocol::StoreNotification::SubscribeNotifications msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_SubscribeNotifications(msg, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::StoreNotification::UnsubscribeNotifications::messageTypeId) {
		Energistics::Etp::v12::Protocol::StoreNotification::UnsubscribeNotifications msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_UnsubscribeNotifications(msg, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::StoreNotification::UnsolicitedStoreNotifications::messageTypeId) {
		Energistics::Etp::v12::Protocol::StoreNotification::UnsolicitedStoreNotifications msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_UnsolicitedStoreNotifications(msg, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::StoreNotification::SubscriptionEnded::messageTypeId) {
		Energistics::Etp::v12::Protocol::StoreNotification::SubscriptionEnded msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_SubscriptionEnded(msg, mh.m_correlationId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged::messageTypeId) {
		Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_ObjectChanged(msg, mh.m_correlationId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::StoreNotification::ObjectDeleted::messageTypeId) {
		Energistics::Etp::v12::Protocol::StoreNotification::ObjectDeleted msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_ObjectDeleted(msg, mh.m_correlationId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::StoreNotification::ObjectAccessRevoked::messageTypeId) {
		Energistics::Etp::v12::Protocol::StoreNotification::ObjectAccessRevoked msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_ObjectAccessRevoked(msg, mh.m_correlationId);
	}
	else {
		session->flushReceivingBuffer();
		sendExceptionCode3();
	}
}

void StoreNotificationHandlers::on_SubscribeNotifications(const Energistics::Etp::v12::Protocol::StoreNotification::SubscribeNotifications & msg, int64_t correlationId)
{
	std::cout << "on_SubscribeNotifications" << std::endl;

	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The StoreHandlers::on_SubscribeNotifications method has not been overriden by the agent."));
}

void StoreNotificationHandlers::on_UnsubscribeNotifications(const Energistics::Etp::v12::Protocol::StoreNotification::UnsubscribeNotifications & msg, int64_t correlationId)
{
	std::cout << "on_UnsubscribeNotifications" << std::endl;

	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The StoreHandlers::on_UnsubscribeNotifications method has not been overriden by the agent."));
}

void StoreNotificationHandlers::on_UnsolicitedStoreNotifications(const Energistics::Etp::v12::Protocol::StoreNotification::UnsolicitedStoreNotifications & msg, int64_t correlationId)
{
	std::cout << "on_UnsolicitedStoreNotifications" << std::endl;

	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The StoreHandlers::on_UnsolicitedStoreNotifications method has not been overriden by the agent."));
}

void StoreNotificationHandlers::on_SubscriptionEnded(const Energistics::Etp::v12::Protocol::StoreNotification::SubscriptionEnded & msg, int64_t correlationId)
{
	std::cout << "on_SubscriptionEnded" << std::endl;

	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The StoreHandlers::on_SubscriptionEnded method has not been overriden by the agent."));
}

void StoreNotificationHandlers::on_ObjectChanged(const Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged & msg, int64_t correlationId)
{
	std::cout << "on_ObjectChanged" << std::endl;

	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The StoreHandlers::on_ObjectChanged method has not been overriden by the agent."));
}

void StoreNotificationHandlers::on_ObjectDeleted(const Energistics::Etp::v12::Protocol::StoreNotification::ObjectDeleted & msg, int64_t correlationId)
{
	std::cout << "on_ObjectDeleted" << std::endl;

	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The StoreHandlers::on_ObjectDeleted method has not been overriden by the agent."));
}

void StoreNotificationHandlers::on_ObjectAccessRevoked(const Energistics::Etp::v12::Protocol::StoreNotification::ObjectAccessRevoked & msg, int64_t correlationId)
{
	std::cout << "on_ObjectAccessRevoked" << std::endl;

	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The StoreHandlers::on_ObjectAccessRevoked method has not been overriden by the agent."));
}
