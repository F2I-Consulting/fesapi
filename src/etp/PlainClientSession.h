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

#include "AbstractClientSession.h"

namespace ETP_NS
{
	class PlainClientSession : public AbstractClientSession<PlainClientSession>
	{
	private:
		websocket::stream<tcp::socket> ws_;

	public:
		DLL_IMPORT_OR_EXPORT PlainClientSession(): ws_(ioc) {}

		DLL_IMPORT_OR_EXPORT PlainClientSession(
			const std::string & host, const std::string & port, const std::string & target, const std::string & authorization,
			const std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> & requestedProtocols,
			const std::vector<Energistics::Etp::v12::Datatypes::SupportedDataObject>& supportedDataObjects);

		virtual ~PlainClientSession() = default;

		// Called by the base class
		DLL_IMPORT_OR_EXPORT websocket::stream<tcp::socket>& ws() { return ws_; }

		void on_resolve(boost::system::error_code ec, tcp::resolver::results_type results)
		{
			if (ec) {
				std::cerr << "on_resolve : " << ec.message() << std::endl;
			}

			// Make the connection on the IP address we get from a lookup
			boost::asio::async_connect(
				ws_.next_layer(),
				results.begin(),
				results.end(),
				std::bind(
					&AbstractClientSession::on_connect,
					std::static_pointer_cast<AbstractClientSession>(shared_from_this()),
					std::placeholders::_1));
		}
	};
}
