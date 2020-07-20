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

#include "etp/ProtocolHandlers/DataArrayHandlers.h"

class MyDataObjectRepository;

class MyOwnDataArrayProtocolHandlers : public ETP_NS::DataArrayHandlers
{
private:
	MyDataObjectRepository* repo;

public:
	MyOwnDataArrayProtocolHandlers(ETP_NS::AbstractSession* mySession, MyDataObjectRepository* repo_): ETP_NS::DataArrayHandlers(mySession), repo(repo_) {}
	~MyOwnDataArrayProtocolHandlers() {}

    void on_GetDataArrays(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrays & gda, int64_t correlationId);
	void on_PutDataArrays(const Energistics::Etp::v12::Protocol::DataArray::PutDataArrays & pda, int64_t correlationId);
	void on_GetDataArrayMetadata(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadata & gdam, int64_t correlationId);
};
