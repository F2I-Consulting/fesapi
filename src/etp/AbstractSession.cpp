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

#include "AbstractSession.h"

#include "EtpHelpers.h"

using namespace ETP_NS;

Energistics::Etp::v12::Datatypes::MessageHeader AbstractSession::decodeMessageHeader(avro::DecoderPtr decoder)
{
	Energistics::Etp::v12::Datatypes::MessageHeader receivedMh;
	avro::decode(*decoder, receivedMh);
#ifndef NDEBUG
	std::cout << "*************************************************" << std::endl;
	std::cout << "Message Header received : " << std::endl;
	std::cout << "protocol : " << receivedMh.protocol << std::endl;
	std::cout << "type : " << receivedMh.messageType << std::endl;
	std::cout << "id : " << receivedMh.messageId << std::endl;
	std::cout << "correlation id : " << receivedMh.correlationId << std::endl;
	std::cout << "flags : " << receivedMh.messageFlags << std::endl;
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

	avro::InputStreamPtr in = avro::memoryInputStream(static_cast<const uint8_t*>(receivedBuffer.data().data()), bytes_transferred);
	avro::DecoderPtr d = avro::binaryDecoder();
	d->init(*in);

	Energistics::Etp::v12::Datatypes::MessageHeader receivedMh = decodeMessageHeader(d);

	// Request for Acknowledge
	if ((receivedMh.messageFlags & 0x10) != 0) {
		Energistics::Etp::v12::Protocol::Core::Acknowledge acknowledge;
		acknowledge.protocolId = receivedMh.protocol;
		send(acknowledge, receivedMh.messageId, 0x02);
	}

	auto specificProtocolHandlerIt = specificProtocolHandlers.find(receivedMh.correlationId);
	if (receivedMh.messageType == Energistics::Etp::v12::Protocol::Core::Acknowledge::messageTypeId) { // Receive Acknowledge
		protocolHandlers[Energistics::Etp::v12::Datatypes::Protocol::Core]->decodeMessageBody(receivedMh, d);
	}
	else if (receivedMh.messageType == Energistics::Etp::v12::Protocol::Core::ProtocolException::messageTypeId) { // Receive Protocol Exception
		protocolHandlers[Energistics::Etp::v12::Datatypes::Protocol::Core]->decodeMessageBody(receivedMh, d);
	}
	else if (specificProtocolHandlerIt != specificProtocolHandlers.end()) {
		specificProtocolHandlerIt->second->decodeMessageBody(receivedMh, d);
		specificProtocolHandlers.erase(specificProtocolHandlerIt);
	}
	else if (receivedMh.protocol < protocolHandlers.size() && protocolHandlers[receivedMh.protocol] != nullptr) {
		protocolHandlers[receivedMh.protocol]->decodeMessageBody(receivedMh, d);
	}
	else {
		flushReceivingBuffer();
		send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(4, "The agent does not support the protocol " + std::to_string(receivedMh.protocol) + " identified in a message header."), receivedMh.messageId, 0x02);
	}

	do_read();
}

void AbstractSession::close()
{
	// Build Open Session message
	Energistics::Etp::v12::Protocol::Core::CloseSession closeSession;

	send(closeSession, 0, 0x02);
}
