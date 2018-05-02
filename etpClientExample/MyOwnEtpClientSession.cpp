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

#include "MyOwnEtpClientSession.h"

MyOwnEtpClientSession::MyOwnEtpClientSession(boost::asio::io_context& ioc,
		const std::string & host, const std::string & port,
		const std::vector<Energistics::Datatypes::SupportedProtocol> & requestedProtocols,
		const std::vector<std::string>& supportedObjects)
	: ETP_NS::ClientSession(ioc, host, port, requestedProtocols, supportedObjects)
{
}

void MyOwnEtpClientSession::do_when_finished()
{
	std::string command;
	std::cout << "What is your command ?" << std::endl;
	std::cin >> command;
	if (command == "quit") {
		close();
	}
	else if (command == "GetResources") {
		Energistics::Protocol::Discovery::GetResources mb;
		mb.m_uri = "testURI";
		sendAndDoRead(mb);
	}
}
