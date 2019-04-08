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
#include "MyOwnEtpClientSessionEpcBased.h"

class MyOwnEtpPlainClientSession : public ETP_NS::PlainClientSession, public MyOwnEtpClientSessionEpcBased
{
public:
	/**
	 * @param host					The IP address on which the server is listening for etp (websocket) connection
	 * @param port					The port on which the server is listening for etp (websocket) connection
	 * @param target				Usually "/" but a server can decide to serve etp on a particular target
	 * @param requestedProtocols	An array of protocol IDs that the client expects to communicate on for this session. If the server does not support all of the protocols, the client may or may not continue with the protocols that are supported.
	 * @param supportedObjects		A list of the Data Objects supported by the client. This list MUST be empty if the client is a customer. This field MUST be supplied if the client is a Store and is requesting a customer role for the server.
	 */
	MyOwnEtpPlainClientSession(boost::asio::io_context& ioc,
			const std::string & host, const std::string & port, const std::string & target, const std::string & authorization,
			const std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> & requestedProtocols,
			const std::vector<std::string>& supportedObjects);

	~MyOwnEtpPlainClientSession() {}
};
