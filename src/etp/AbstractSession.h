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

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "nsDefinitions.h"

#include "etp/EtpMessages.h"
#include "etp/ProtocolHandlers/CoreHandlers.h"
#include "etp/ProtocolHandlers/DiscoveryHandlers.h"

using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>
namespace websocket = boost::beast::websocket;  // from <boost/beast/websocket.hpp>

namespace ETP_NS
{
	class AbstractSession : public std::enable_shared_from_this<AbstractSession>
	{
	protected:
	    websocket::stream<tcp::socket> ws;
	    boost::beast::flat_buffer receivedBuffer;
	    boost::shared_ptr<std::vector<uint8_t> > bytesToSend;
	    long long messageId = 1;
	    std::vector<std::shared_ptr<ETP_NS::ProtocolHandlers>> protocolHandlers;
	    bool closed;

	    // For client session
	    AbstractSession(boost::asio::io_context& ioc) : ws(ioc), closed(true){
	    	setCoreProtocolHandlers(std::make_shared<CoreHandlers>(this));
	    }
	    // For server session
	    AbstractSession(tcp::socket socket) : ws(std::move(socket)), closed(true) {
	    	setCoreProtocolHandlers(std::make_shared<CoreHandlers>(this));
	    }

		virtual void run() = 0;

		/**
		 * Write the current buffer on the web socket
		 */
		virtual void do_write() = 0;
		virtual void do_writeAndRead() = 0;

		/**
		 * Reads the message header currently stored in the decoder.
		 * @param decoder	Must be initialized with stream containing a coded message header.
		 */
		Energistics ::Datatypes::MessageHeader decodeMessageHeader(avro::DecoderPtr decoder, bool print = false);

		template<typename T> void encode(const T & mb)
		{
			// Build message header
			Energistics ::Datatypes::MessageHeader mh;
			mh.m_protocol = mb.protocolId;
			mh.m_messageType = mb.messageTypeId;
			mh.m_correlationId = 0;
			mh.m_messageId = messageId++;
			mh.m_messageFlags = 0;

			std::auto_ptr<avro::OutputStream> out = avro::memoryOutputStream();
			avro::EncoderPtr e = avro::binaryEncoder();
			e->init(*out);
			avro::encode(*e, mh);
			avro::encode(*e, mb);
			bytesToSend = avro::snapshot(*out);
		}

	public:

		virtual ~AbstractSession() {	}

		/**
		 * Set the Core protocol handlers
		 */
	    void setCoreProtocolHandlers(std::shared_ptr<CoreHandlers> coreHandlers) {
	    	if (protocolHandlers.empty()) {
	    		protocolHandlers.push_back(coreHandlers);
	    	}
	    	else {
	    		protocolHandlers[0] = coreHandlers;
	    	}
	    }

	    /**
		 * Set the Discovery protocol handlers
		 */
		void setDiscoveryProtocolHandlers(std::shared_ptr<DiscoveryHandlers> discoveryHandlers) {
			while (protocolHandlers.size() < 4) {
				protocolHandlers.push_back(nullptr);
			}
			protocolHandlers[3] = discoveryHandlers;
		}

		void close();

		/**
		 * Create a default ETP message header from the ETP message body.
		 * Encode this created default ETP message header + the ETP message body into the session buffer.
		 * Write/send this session buffer on the web socket.
		 * @param mb The ETP message body to send
		 */
		template<typename T> void send(const T & mb)
		{
			encode(mb);
			do_write();
		}

		/**
		 * Create a default ETP message header from the ETP message body.
		 * Encode this created default ETP message header + the ETP message body into the session buffer.
		 * Write/send this session buffer on the web socket and then read an answer.
		 * @param mb The ETP message body to send
		 */
		template<typename T> void sendAndDoRead(const T & mb)
		{
			encode(mb);
			do_writeAndRead();
		}

		/**
		 * This method is called once all exchanges are done.
		 * It is typically implemented by a read method (wait for something to read)
		 */
		virtual void do_when_finished() = 0;

		/**
		 * Close the web socket (without sending any ETP message)
		 */
		virtual void do_close() = 0;

		/**
		 * Read what is on the websocket
		 */
		virtual void do_read() = 0;

		/**
		 * This method is called each time a message is received on the web socket
		 */
		void on_read(boost::system::error_code ec, std::size_t bytes_transferred);

		/**
		 * This method is called each time a message is received on the web socket
		 */
		void on_write(boost::system::error_code ec, std::size_t bytes_transferred) {
			do_when_finished();
		};
		void on_writeAndRead(boost::system::error_code ec, std::size_t bytes_transferred) {
			do_read();
		};

		void on_close(boost::system::error_code ec) {
			if(ec) {
				std::cerr << "on_close : " << ec.message() << std::endl;
			}

			// If we get here then the connection is closed gracefully
			std::cout << "!!! CLOSED !!!" << std::endl;

			closed = true;
		}
	};
}
