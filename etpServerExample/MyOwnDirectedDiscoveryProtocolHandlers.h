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

#include "etp/ProtocolHandlers/DirectedDiscoveryHandlers.h"

#include "MyOwnEtpServerSession.h"

class MyOwnDirectedDiscoveryProtocolHandlers : public ETP_NS::DirectedDiscoveryHandlers
{
public:
	MyOwnDirectedDiscoveryProtocolHandlers(MyOwnEtpServerSession* mySession): ETP_NS::DirectedDiscoveryHandlers(mySession) {}
	~MyOwnDirectedDiscoveryProtocolHandlers() {}

	void on_GetContent(const Energistics::Etp::v12::Protocol::DirectedDiscovery::GetContent & gc, int64_t correlationId);
	//void on_GetSourceFolders(const Energistics::Etp::v12::Protocol::DirectedDiscovery::GetSourceFolders & gsf);
	//void on_GetTargetFolders(const Energistics::Etp::v12::Protocol::DirectedDiscovery::GetTargetFolders & gtf);
};
