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
	class DLL_IMPORT_OR_EXPORT DiscoveryHandlers : public ProtocolHandlers
	{
	public:
		DiscoveryHandlers(std::shared_ptr<AbstractSession> mySession): ProtocolHandlers(mySession) {}

	    void decodeMessageBody(const Energistics::Etp::v12::Datatypes::MessageHeader & mh, avro::DecoderPtr d);

		//virtual void on_GetDataspaces(const Energistics::Etp::v12::Protocol::Discovery::GetDataspaces & msg, int64_t correlationId);
		//virtual void on_GetDataspacesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetDataspacesResponse & msg, int64_t correlationId);
		//virtual void on_GetNamespaces(const Energistics::Etp::v12::Protocol::Discovery::GetNamespaces & msg, int64_t correlationId);
		//virtual void on_GetNamespacesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetNamespacesResponse & msg, int64_t correlationId);
		virtual void on_GetSupportedTypes(const Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypes & msg, int64_t correlationId);
		virtual void on_GetSupportedTypesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypesResponse & msg, int64_t correlationId);
		virtual void on_GetResources(const Energistics::Etp::v12::Protocol::Discovery::GetResources & msg, int64_t correlationId);
		virtual void on_GetResourcesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse & msg, int64_t correlationId);

		virtual ~DiscoveryHandlers() {}
	};
}
