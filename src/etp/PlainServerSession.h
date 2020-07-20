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

#include "AbstractPlainOrSslServerSession.h"

namespace ETP_NS
{
	class PlainServerSession : public AbstractPlainOrSslServerSession<PlainServerSession>
	{
	private:
		websocket::stream<tcp::socket> ws_;

	public:
		DLL_IMPORT_OR_EXPORT PlainServerSession(tcp::socket socket);

		virtual ~PlainServerSession() {}

		// Called by the base class
		DLL_IMPORT_OR_EXPORT websocket::stream<tcp::socket>& ws() { return ws_; }

		DLL_IMPORT_OR_EXPORT bool run(boost::beast::http::request<boost::beast::http::string_body> req) {
			on_handshake(boost::system::error_code(), std::move(req));
			return true;
		}
	};
}
