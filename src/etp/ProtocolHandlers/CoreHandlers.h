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
	class DLL_IMPORT_OR_EXPORT CoreHandlers : public ProtocolHandlers
	{
	public:
		CoreHandlers(AbstractSession* mySession):
			ProtocolHandlers(mySession) {}
		virtual ~CoreHandlers() = default;

	    void decodeMessageBody(const Energistics::Etp::v12::Datatypes::MessageHeader & mh, avro::DecoderPtr d) override;

	    virtual void on_RequestSession(const Energistics::Etp::v12::Protocol::Core::RequestSession & rs, int64_t correlationId);
	    virtual void on_OpenSession(const Energistics::Etp::v12::Protocol::Core::OpenSession & os, int64_t correlationId);
	    virtual void on_CloseSession(const Energistics::Etp::v12::Protocol::Core::CloseSession & cs, int64_t correlationId);
	    virtual void on_ProtocolException(const Energistics::Etp::v12::Protocol::Core::ProtocolException & pe, int64_t correlationId);
		virtual void on_Acknowledge(const Energistics::Etp::v12::Protocol::Core::Acknowledge & ack, int64_t correlationId);
		virtual void on_Ping(const Energistics::Etp::v12::Protocol::Core::Ping & ping, int64_t correlationId);
		virtual void on_Pong(const Energistics::Etp::v12::Protocol::Core::Pong & pong, int64_t correlationId);

	};
}
