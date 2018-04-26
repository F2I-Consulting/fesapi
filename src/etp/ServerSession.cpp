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

#include "etp/ServerSession.h"

#include <boost/beast/http.hpp>
#include <boost/asio/bind_executor.hpp>

#include "tools/GuidTools.h"

using namespace ETP_NS;

ServerSession::ServerSession(tcp::socket socket)
	: AbstractSession(std::move(socket)),
	  strand(ws.get_executor())
{
	ws.binary(true);
}

void ServerSession::run()
{
	// Accept the websocket handshake
	ws.async_accept_ex(
			[](websocket::response_type& m)
				{
					m.insert(boost::beast::http::field::sec_websocket_protocol, "energistics-tp");
				},
		boost::asio::bind_executor(
			strand,
			std::bind(
				&ServerSession::on_accept,
				std::static_pointer_cast<ServerSession>(shared_from_this()),
				std::placeholders::_1)));
}

void ServerSession::on_accept(boost::system::error_code ec)
{
	if(ec) {
		std::cerr << "on_accept : " << ec.message() << std::endl;
	}

	// Read a message
	do_read();
}

void ServerSession::do_read()
{
	std::cerr << "DO READ " << std::endl;
	// Read a message into our buffer
	std::cout << "Current buffer size : " <<  receivedBuffer.size() << std::endl;
	ws.async_read(
		receivedBuffer,
		boost::asio::bind_executor(
			strand,
			std::bind(
				&ServerSession::on_read,
				std::static_pointer_cast<ServerSession>(shared_from_this()),
				std::placeholders::_1,
				std::placeholders::_2)));
}

void ServerSession::on_read(
	boost::system::error_code ec,
	std::size_t bytes_transferred)
{
	std::cerr << std::endl << "***************************READ " << bytes_transferred << " bytes" << std::endl;
	if (bytes_transferred == 0) return;

	boost::ignore_unused(bytes_transferred);

	// This indicates that the session was closed
	if(ec == websocket::error::closed) {
		std::cout << "Client closed connection." << std::endl;
		return;
	}

	if(ec) {
		std::cerr << "on_read : " << ec.message() << std::endl;
	}

	// Echo the message
	std::auto_ptr<avro::InputStream> in = avro::memoryInputStream(static_cast<const uint8_t*>(receivedBuffer.data().data()), bytes_transferred);
	avro::DecoderPtr d = avro::binaryDecoder();
	d->init(*in);

	Energistics ::Datatypes::MessageHeader receivedMh;
	avro::decode(*d, receivedMh);
	std::cout << '(' << receivedMh.m_correlationId << ", " << receivedMh.m_messageId << ')' << std::endl;

	if (receivedMh.m_protocol == Energistics::Datatypes::Protocols::Core && receivedMh.m_messageType == Energistics::Protocol::Core::RequestSession::messageTypeId) {
		Energistics::Protocol::Core::RequestSession rs;
		avro::decode(*d, rs);
		std::cout << '(' << rs.m_applicationName << ", " << rs.m_applicationVersion << ')' << std::endl;

		// Build Message Header
		Energistics ::Datatypes::MessageHeader sentMh;
		sentMh.m_protocol = Energistics::Datatypes::Protocols::Core;
		sentMh.m_messageType = Energistics::Protocol::Core::OpenSession::messageTypeId;
		sentMh.m_correlationId = receivedMh.m_messageId;
		sentMh.m_messageId = messageId++;
		sentMh.m_messageFlags = 0;
		//Encode into avro
		std::auto_ptr<avro::OutputStream> out = avro::memoryOutputStream();
		avro::EncoderPtr e = avro::binaryEncoder();
		e->init(*out);
		avro::encode(*e, sentMh);

		// Build Open Session message
		Energistics::Protocol::Core::OpenSession openSession;
		openSession.m_applicationName = "F2I ETP Server";
		openSession.m_applicationVersion = "0.0";
		openSession.m_sessionId = tools::GuidTools::generateUidAsString();
		std::vector<Energistics::Datatypes::SupportedProtocol> supportedProtocols;
		Energistics::Datatypes::SupportedProtocol protocol;
		protocol.m_protocol = Energistics::Datatypes::Protocols::Discovery;
		Energistics::Datatypes::Version protocolVersion;
		protocolVersion.m_major = 1;
		protocolVersion.m_minor = 1;
		protocolVersion.m_patch = 0;
		protocolVersion.m_revision = 0;
		protocol.m_protocolVersion = protocolVersion;
		protocol.m_role = "store";
		supportedProtocols.push_back(protocol);
		openSession.m_supportedProtocols = supportedProtocols;
		std::vector<std::string> supportedObjects;
		supportedObjects.push_back("application/x-resqml+xml;version=2.0;type=*");
		openSession.m_supportedObjects = supportedObjects;
		avro::encode(*e, openSession);
		bytesToSend = avro::snapshot(*out);

		// Answer with open session
		std::cout << "WRITE" << std::endl;
		ws.async_write(
				boost::asio::buffer(*bytesToSend),
			boost::asio::bind_executor(
				strand,
				std::bind(
					&ServerSession::on_write,
					std::static_pointer_cast<ServerSession>(shared_from_this()),
					std::placeholders::_1,
					std::placeholders::_2)));
	}
	else if (receivedMh.m_protocol == Energistics::Datatypes::Protocols::Core && receivedMh.m_messageType == Energistics::Protocol::Core::CloseSession::messageTypeId) {
		Energistics::Protocol::Core::CloseSession cs;
		avro::decode(*d, cs);

		std::cout << "Close session after received request." << std::endl;
		close();
	}

	// Clear the buffer
	receivedBuffer.consume(receivedBuffer.size());
}

void ServerSession::on_write(
	boost::system::error_code ec,
	std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);

	if(ec) {
		std::cerr << "on_write : " << ec.message() << std::endl;
	}

	// Do another read
	do_read();
}

void ServerSession::close()
{
	ws.async_close(websocket::close_code::normal,
			boost::asio::bind_executor(
						strand,
		std::bind(
			&ServerSession::on_close,
			std::static_pointer_cast<ServerSession>(shared_from_this()),
			std::placeholders::_1)));
}

void ServerSession::on_close(boost::system::error_code ec)
{
	if(ec) {
		std::cerr << "on_close : " << ec.message() << std::endl;
	}

	// If we get here then the connection is closed gracefully
	std::cout << "!!! CLOSED !!!" << std::endl;
}
