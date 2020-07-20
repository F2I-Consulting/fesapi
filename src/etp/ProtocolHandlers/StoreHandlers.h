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
	class DLL_IMPORT_OR_EXPORT StoreHandlers : public ProtocolHandlers
	{
	public:
		StoreHandlers(AbstractSession* mySession): ProtocolHandlers(mySession) {}
		virtual ~StoreHandlers() {}

	    void decodeMessageBody(const Energistics::Etp::v12::Datatypes::MessageHeader & mh, avro::DecoderPtr d);

	    virtual void on_GetDataObjects(const Energistics::Etp::v12::Protocol::Store::GetDataObjects & msg, int64_t correlationId);
		virtual void on_GetDataObjectsResponse(const Energistics::Etp::v12::Protocol::Store::GetDataObjectsResponse & msg, int64_t correlationId);
	    virtual void on_PutDataObjects(const Energistics::Etp::v12::Protocol::Store::PutDataObjects & msg, int64_t correlationId);
		virtual void on_PutDataObjectsResponse(const Energistics::Etp::v12::Protocol::Store::PutDataObjectsResponse & msg, int64_t correlationId);
	    virtual void on_DeleteDataObjects(const Energistics::Etp::v12::Protocol::Store::DeleteDataObjects & msg, int64_t correlationId);
		virtual void on_DeleteDataObjectsResponse(const Energistics::Etp::v12::Protocol::Store::DeleteDataObjectsResponse & msg, int64_t correlationId);
	};
}
