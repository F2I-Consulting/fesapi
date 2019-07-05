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

#include "etp/PlainClientSession.h"

#include "etp/ProtocolHandlers/CoreHandlers.h"
#include "etp/ProtocolHandlers/DiscoveryHandlers.h"
#include "etp/ProtocolHandlers/StoreHandlers.h"
#include "etp/ProtocolHandlers/DataArrayHandlers.h"

namespace ETP_NS
{
	namespace ClientSessionLaunchers
	{
		DLL_IMPORT_OR_EXPORT std::shared_ptr<ETP_NS::PlainClientSession> createClientSession(const std::string & host, const std::string & port, const std::string & target, const std::string & authorization);
	}
}
