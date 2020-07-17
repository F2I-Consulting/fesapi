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

#include "ProtocolHandlers.h"

namespace ETP_NS
{
	class DLL_IMPORT_OR_EXPORT StoreNotificationHandlers : public ProtocolHandlers
	{
	public:
		StoreNotificationHandlers(AbstractSession* mySession): ProtocolHandlers(mySession) {}
		virtual ~StoreNotificationHandlers() {}

	    void decodeMessageBody(const Energistics::Etp::v12::Datatypes::MessageHeader & mh, avro::DecoderPtr d);

	    virtual void on_SubscribeNotifications(const Energistics::Etp::v12::Protocol::StoreNotification::SubscribeNotifications & msg, int64_t messageId);
	    virtual void on_UnsubscribeNotifications(const Energistics::Etp::v12::Protocol::StoreNotification::UnsubscribeNotifications & msg, int64_t messageId, int64_t correlationId);
		virtual void on_UnsolicitedStoreNotifications(const Energistics::Etp::v12::Protocol::StoreNotification::UnsolicitedStoreNotifications & msg, int64_t correlationId);
		virtual void on_SubscriptionEnded(const Energistics::Etp::v12::Protocol::StoreNotification::SubscriptionEnded & msg, int64_t correlationId);
	    virtual void on_ObjectChanged(const Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged & msg, int64_t correlationId);
	    virtual void on_ObjectDeleted(const Energistics::Etp::v12::Protocol::StoreNotification::ObjectDeleted & msg, int64_t correlationId);
		virtual void on_ObjectAccessRevoked(const Energistics::Etp::v12::Protocol::StoreNotification::ObjectAccessRevoked & msg, int64_t correlationId);
	};
}
