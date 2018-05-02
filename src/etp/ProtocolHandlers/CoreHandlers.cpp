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
#include  "etp/ProtocolHandlers/CoreHandlers.h"

#include "etp/AbstractSession.h"

using namespace ETP_NS;

void CoreHandlers::decodeMessageBody(const Energistics ::Datatypes::MessageHeader & mh, avro::DecoderPtr d)
{
	if (mh.m_protocol != Energistics::Datatypes::Protocols::Core) {
		std::cerr << "Error : This message header does not belong to the protocol Core" << std::endl;
		return;
	}

	if (mh.m_messageType == 1) {
		Energistics::Protocol::Core::RequestSession rs;
		avro::decode(*d, rs);
		on_RequestSession(rs);
	}
	else if (mh.m_messageType == 2) {
		Energistics::Protocol::Core::OpenSession os;
		avro::decode(*d, os);
		on_OpenSession(os);
	}
	else if (mh.m_messageType == 5) {
		Energistics::Protocol::Core::CloseSession cs;
		avro::decode(*d, cs);
		on_CloseSession(cs);
	}
	else if (mh.m_messageType == 1000) {
		Energistics::Protocol::Core::ProtocolException pe;
		avro::decode(*d, pe);
		on_ProtocolException(pe);
	}
	else {
		sendExceptionCode3();
	}
}

void CoreHandlers::on_RequestSession(const Energistics::Protocol::Core::RequestSession & rs)
{
	Energistics::Protocol::Core::ProtocolException error;
	error.m_errorCode = 2;
	error.m_errorMessage = "The Core::on_RequestSession method has not been overriden by the agent.";

	session->send(error);
}

void CoreHandlers::on_OpenSession(const Energistics::Protocol::Core::OpenSession & os)
{
	session->do_when_finished();
}

void CoreHandlers::on_CloseSession(const Energistics::Protocol::Core::CloseSession & cs)
{
	std::cout << "Close session after received request." << std::endl;
	session->do_close();
}

void CoreHandlers::on_ProtocolException(const Energistics::Protocol::Core::ProtocolException & pe)
{
	std::cout << "EXCEPTION with error code "  << pe.m_errorCode << " : " << pe.m_errorMessage << std::endl;

	session->do_when_finished();
}
