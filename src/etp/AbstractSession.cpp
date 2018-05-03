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

#include "tools/GuidTools.h"

using namespace ETP_NS;

Energistics::Datatypes::MessageHeader AbstractSession::decodeMessageHeader(avro::DecoderPtr decoder, bool print)
{
	Energistics ::Datatypes::MessageHeader receivedMh;
	avro::decode(*decoder, receivedMh);
	if (print) {
		std::cout << "*************************************************" << std::endl;
		std::cout << "Message Header received : " << std::endl;
		std::cout << "protocol : " << receivedMh.m_protocol << std::endl;
		std::cout << "type : " << receivedMh.m_messageType << std::endl;
		std::cout << "id : " << receivedMh.m_messageId << std::endl;
		std::cout << "correlation id : " << receivedMh.m_correlationId << std::endl;
		std::cout << "flags : " << receivedMh.m_messageFlags << std::endl;
		std::cout << "*************************************************" << std::endl;
	}

	return receivedMh;
}

void AbstractSession::on_read(boost::system::error_code ec, std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);

	// This indicates that the session was closed
	if(ec == websocket::error::closed) {
		std::cout << "The other endpoint closed connection." << std::endl;
		closed = true;
		return;
	}

	if(ec) {
		std::cerr << "on_read : " << ec.message() << std::endl;
	}

	if (bytes_transferred == 0) return;

	std::auto_ptr<avro::InputStream> in = avro::memoryInputStream(static_cast<const uint8_t*>(receivedBuffer.data().data()), bytes_transferred);
	avro::DecoderPtr d = avro::binaryDecoder();
	d->init(*in);

	Energistics ::Datatypes::MessageHeader receivedMh = decodeMessageHeader(d, true);

	if (receivedMh.m_protocol < protocolHandlers.size() && protocolHandlers[receivedMh.m_protocol] != nullptr) {
		protocolHandlers[receivedMh.m_protocol]->decodeMessageBody(receivedMh, d);
	}
	else {
		Energistics::Protocol::Core::ProtocolException error;
		error.m_errorCode = 4;
		error.m_errorMessage = "The agent does not support the protocol identified in a message header.";

		send(error);
	}

	// Clear the buffer
	receivedBuffer.consume(receivedBuffer.size());
}

void AbstractSession::close()
{
	// Build Open Session message
	Energistics::Protocol::Core::CloseSession closeSession;

	sendAndDoRead(closeSession);
}
