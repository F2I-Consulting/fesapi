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
	class DLL_IMPORT_OR_EXPORT DataArrayHandlers : public ProtocolHandlers
	{
	public:
		DataArrayHandlers(AbstractSession* mySession): ProtocolHandlers(mySession) {}
		virtual ~DataArrayHandlers() {}

	    void decodeMessageBody(const Energistics::Etp::v12::Datatypes::MessageHeader & mh, avro::DecoderPtr d);

	    virtual void on_GetDataArrays(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrays & gda, int64_t correlationId);
		virtual void on_GetDataArraysResponse(Energistics::Etp::v12::Protocol::DataArray::GetDataArraysResponse & gdar);
	    virtual void on_PutDataArrays(const Energistics::Etp::v12::Protocol::DataArray::PutDataArrays & pda, int64_t correlationId);
		virtual void on_PutDataArraysResponse(const Energistics::Etp::v12::Protocol::DataArray::PutDataArraysResponse & msg, int64_t correlationId);
	    virtual void on_GetDataSubarrays(const Energistics::Etp::v12::Protocol::DataArray::GetDataSubarrays & msg, int64_t correlationId);
		virtual void on_GetDataSubarraysResponse(const Energistics::Etp::v12::Protocol::DataArray::GetDataSubarraysResponse & msg);
	    virtual void on_PutDataSubarrays(const Energistics::Etp::v12::Protocol::DataArray::PutDataSubarrays & msg, int64_t correlationId);
		virtual void on_PutDataSubarraysResponse(const Energistics::Etp::v12::Protocol::DataArray::PutDataSubarraysResponse & msg, int64_t correlationId);
		virtual void on_GetDataArrayMetadata(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadata & gdam, int64_t correlationId);
		virtual void on_GetDataArrayMetadataResponse(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadataResponse & gdamr);
		virtual void on_PutUninitializedDataArrays(const Energistics::Etp::v12::Protocol::DataArray::PutUninitializedDataArrays & msg, int64_t correlationId);
		virtual void on_PutUninitializedDataArraysResponse(const Energistics::Etp::v12::Protocol::DataArray::PutUninitializedDataArraysResponse & msg);
	};
}
