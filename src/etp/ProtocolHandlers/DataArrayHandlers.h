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

#include "etp/ProtocolHandlers/ProtocolHandlers.h"

namespace ETP_NS
{
	class DLL_IMPORT_OR_EXPORT DataArrayHandlers : public ProtocolHandlers
	{
	public:
		DataArrayHandlers(AbstractSession* mySession): ProtocolHandlers(mySession) {}

	    void decodeMessageBody(const Energistics::Etp::v12::Datatypes::MessageHeader & mh, avro::DecoderPtr d);

	    virtual void on_GetDataArray(const Energistics::Etp::v12::Protocol::DataArray::GetDataArray & gda, int64_t correlationId);
	    virtual void on_PutDataArray(const Energistics::Etp::v12::Protocol::DataArray::PutDataArray & pda, int64_t correlationId);
	    virtual void on_GetDataArraySlice(const Energistics::Etp::v12::Protocol::DataArray::GetDataArraySlice & gdas, int64_t correlationId);
	    virtual void on_PutDataArraySlice(const Energistics::Etp::v12::Protocol::DataArray::PutDataArraySlice & pdas, int64_t correlationId);
		virtual void on_DescribeDataArray(const Energistics::Etp::v12::Protocol::DataArray::DescribeDataArray & dda, int64_t correlationId);
		virtual void on_DataArrayMetadata(const Energistics::Etp::v12::Protocol::DataArray::DataArrayMetadata & dam);
	    virtual void on_DataArray(Energistics::Etp::v12::Protocol::DataArray::DataArray & da);

		virtual ~DataArrayHandlers() {}
	};
}
