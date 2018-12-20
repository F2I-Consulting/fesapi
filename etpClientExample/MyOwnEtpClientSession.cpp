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

#include "MyOwnCoreProtocolHandlers.h"
#include "MyOwnDiscoveryProtocolHandlers.h"
#include "MyOwnStoreProtocolHandlers.h"
#include "etp/ProtocolHandlers/DataArrayHandlers.h"

MyOwnEtpClientSession::MyOwnEtpClientSession(boost::asio::io_context& ioc,
		const std::string & host, const std::string & port, const std::string & target,
		const std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> & requestedProtocols,
		const std::vector<std::string>& supportedObjects)
	: ETP_NS::ClientSession(ioc, host, port, target, requestedProtocols, supportedObjects)
{
	setCoreProtocolHandlers(std::make_shared<MyOwnCoreProtocolHandlers>(this));
	setDiscoveryProtocolHandlers(std::make_shared<MyOwnDiscoveryProtocolHandlers>(this));
	setStoreProtocolHandlers(std::make_shared<MyOwnStoreProtocolHandlers>(this));
	setDataArrayProtocolHandlers(std::make_shared<ETP_NS::DataArrayHandlers>(this));
}
