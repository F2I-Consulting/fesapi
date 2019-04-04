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

#include "etp/AbstractSession.h"

#include <regex>

using namespace ETP_NS;

Energistics::Etp::v12::Datatypes::MessageHeader AbstractSession::decodeMessageHeader(avro::DecoderPtr decoder)
{
	Energistics::Etp::v12::Datatypes::MessageHeader receivedMh;
	avro::decode(*decoder, receivedMh);
#ifndef NDEBUG
	std::cout << "*************************************************" << std::endl;
	std::cout << "Message Header received : " << std::endl;
	std::cout << "protocol : " << receivedMh.m_protocol << std::endl;
	std::cout << "type : " << receivedMh.m_messageType << std::endl;
	std::cout << "id : " << receivedMh.m_messageId << std::endl;
	std::cout << "correlation id : " << receivedMh.m_correlationId << std::endl;
	std::cout << "flags : " << receivedMh.m_messageFlags << std::endl;
	std::cout << "*************************************************" << std::endl;
#endif

	return receivedMh;
}

void AbstractSession::on_read(boost::system::error_code ec, std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);

	// This indicates that the web socket (and consequently etp) session was closed
	if(ec == websocket::error::closed) {
		std::cout << "The other endpoint closed the web socket (and consequently etp) connection." << std::endl;
		webSocketSessionClosed = true;
		flushReceivingBuffer();
		return;
	}

	if(ec) {
		std::cerr << "on_read : error code number " << ec.value() << " -> " << ec.message() << std::endl;
		return;
	}

	if (bytes_transferred == 0) return;

	std::auto_ptr<avro::InputStream> in = avro::memoryInputStream(static_cast<const uint8_t*>(receivedBuffer.data().data()), bytes_transferred);
	avro::DecoderPtr d = avro::binaryDecoder();
	d->init(*in);

	Energistics::Etp::v12::Datatypes::MessageHeader receivedMh = decodeMessageHeader(d);

	// Request for Acknowledge
	if ((receivedMh.m_messageFlags & 0x10) != 0) {
		Energistics::Etp::v12::Protocol::Core::Acknowledge acknowledge;
		acknowledge.protocolId = receivedMh.m_protocol;
		send(acknowledge, receivedMh.m_messageId);
	}


	if (receivedMh.m_messageType == Energistics::Etp::v12::Protocol::Core::Acknowledge::messageTypeId) { // Receive Acknowledge
		protocolHandlers[Energistics::Etp::v12::Datatypes::Protocol::Core]->decodeMessageBody(receivedMh, d);
	}
	else if (receivedMh.m_messageType == Energistics::Etp::v12::Protocol::Core::ProtocolException::messageTypeId) { // Receive Protocol Exception
		protocolHandlers[Energistics::Etp::v12::Datatypes::Protocol::Core]->decodeMessageBody(receivedMh, d);
	}
	else if (receivedMh.m_protocol < protocolHandlers.size() && protocolHandlers[receivedMh.m_protocol] != nullptr) {
		protocolHandlers[receivedMh.m_protocol]->decodeMessageBody(receivedMh, d);
	}
	else {
		flushReceivingBuffer();

		Energistics::Etp::v12::Protocol::Core::ProtocolException error;
		error.m_errorCode = 4;
		error.m_errorMessage = "The agent does not support the protocol " + std::to_string(receivedMh.m_protocol) + " identified in a message header.";

		send(error);
	}

	do_read();
}

void AbstractSession::close()
{
	// Build Open Session message
	Energistics::Etp::v12::Protocol::Core::CloseSession closeSession;

	send(closeSession);
}

bool AbstractSession::validateUri(const std::string & uri, bool sendException)
{
	bool result = std::regex_match(uri, std::regex("^eml://((witsml|resqml|prodml|eml)([0-9]{2}))?/?", std::regex::ECMAScript)) ||
			std::regex_match(uri, std::regex("^eml://(witsml|resqml|prodml|eml)([0-9]{2})/obj_[a-zA-Z0-9]+", std::regex::ECMAScript)) ||
			std::regex_match(uri, std::regex("^eml://(witsml|resqml|prodml|eml)([0-9]{2})/obj_[a-zA-Z0-9]+[(][a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12}[)]", std::regex::ECMAScript));
	if (!result) {
		std::cerr << "The URI \"" + uri + "\"  is invalid." << std::endl;
	}

	if (!result && sendException) {
		Energistics::Etp::v12::Protocol::Core::ProtocolException error;
		error.m_errorCode = 9;
		error.m_errorMessage = "The URI " + uri + "  is invalid.";

		send(error);
	}

	return result;
}

bool AbstractSession::validateDataObjectUri(const std::string & uri, bool sendException)
{
	bool result = std::regex_match(uri, std::regex("^eml://(witsml|resqml|prodml|eml)([0-9]{2})/obj_[a-zA-Z0-9]+[(][a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12}[)]", std::regex::ECMAScript));
	if (!result) {
		std::cerr << "The data object URI \"" + uri + "\"  is invalid." << std::endl;
	}

	if (!result && sendException) {
		Energistics::Etp::v12::Protocol::Core::ProtocolException error;
		error.m_errorCode = 9;
		error.m_errorMessage = "The data object URI " + uri + "  is invalid.";

		send(error);
	}

	return result;
}
