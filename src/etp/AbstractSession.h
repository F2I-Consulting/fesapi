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
#include "etp/ProtocolHandlers/DirectedDiscoveryHandlers.h"
#include "etp/ProtocolHandlers/StoreHandlers.h"
#include "etp/ProtocolHandlers/DataArrayHandlers.h"

using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>
namespace websocket = boost::beast::websocket;  // from <boost/beast/websocket.hpp>

namespace {
	std::vector<std::string> tokenize(const std::string & str, char delimiter) {
		std::vector<std::string> tokens;
		std::stringstream ss(str);
		std::string token;
		while(getline(ss, token, delimiter)) {
			tokens.push_back(token);
		}

		return tokens;
	}
}

namespace ETP_NS
{
	class AbstractSession : public std::enable_shared_from_this<AbstractSession>
	{
	protected:
	    websocket::stream<tcp::socket> ws;
	    boost::beast::flat_buffer receivedBuffer;
	    long long messageId = 1;
	    std::vector<std::shared_ptr<ETP_NS::ProtocolHandlers>> protocolHandlers;
	    bool closed;
	    std::vector<std::vector<uint8_t> > queue;

	    // For client session
	    AbstractSession(boost::asio::io_context& ioc) : ws(ioc), closed(true) {
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

		/**
		 * Reads the message header currently stored in the decoder.
		 * @param decoder	Must be initialized with stream containing a coded message header.
		 */
		Energistics::Etp::v12::Datatypes::MessageHeader decodeMessageHeader(avro::DecoderPtr decoder);

		template<typename T> void encode(const T & mb, int64_t correlationId = 0, int32_t messageFlags = 0)
		{
			// Build message header
			Energistics::Etp::v12::Datatypes::MessageHeader mh;
			mh.m_protocol = mb.protocolId;
			mh.m_messageType = mb.messageTypeId;
			mh.m_correlationId = correlationId;
			mh.m_messageId = messageId++;
			mh.m_messageFlags = messageFlags;

#ifndef NDEBUG
			std::cout << "*************************************************" << std::endl;
			std::cout << "Message Header sent : " << std::endl;
			std::cout << "protocol : " << mh.m_protocol << std::endl;
			std::cout << "type : " << mh.m_messageType << std::endl;
			std::cout << "id : " << mh.m_messageId << std::endl;
			std::cout << "correlation id : " << mh.m_correlationId << std::endl;
			std::cout << "flags : " << mh.m_messageFlags << std::endl;
			std::cout << "*************************************************" << std::endl;
#endif

			std::auto_ptr<avro::OutputStream> out = avro::memoryOutputStream();
			avro::EncoderPtr e = avro::binaryEncoder();
			e->init(*out);
			avro::encode(*e, mh);
			avro::encode(*e, mb);
			queue.push_back(*avro::snapshot(*out).get());
		}

	public:

		virtual ~AbstractSession() {	}

		void flushReceivingBuffer() {
			receivedBuffer.consume(receivedBuffer.size());
		}

		/**
		 * Set the Core protocol handlers
		 */
	    void setCoreProtocolHandlers(std::shared_ptr<CoreHandlers> coreHandlers) {
	    	if (protocolHandlers.empty()) {
	    		protocolHandlers.push_back(coreHandlers);
	    	}
	    	else {
	    		protocolHandlers[Energistics::Etp::v12::Datatypes::Protocols::Core] = coreHandlers;
	    	}
	    }

	    /**
		 * Set the Discovery protocol handlers
		 */
		void setDiscoveryProtocolHandlers(std::shared_ptr<DiscoveryHandlers> discoveryHandlers) {
			while (protocolHandlers.size() < Energistics::Etp::v12::Datatypes::Protocols::Discovery + 1) {
				protocolHandlers.push_back(nullptr);
			}
			protocolHandlers[Energistics::Etp::v12::Datatypes::Protocols::Discovery] = discoveryHandlers;
		}

		/**
		 * Set the Directed Discovery protocol handlers
		 */
		void setDirectedDiscoveryProtocolHandlers(std::shared_ptr<DirectedDiscoveryHandlers> directedDiscoveryHandlers) {
			while (protocolHandlers.size() < Energistics::Etp::v12::Datatypes::Protocols::DirectedDiscovery + 1) {
				protocolHandlers.push_back(nullptr);
			}
			protocolHandlers[Energistics::Etp::v12::Datatypes::Protocols::DirectedDiscovery] = directedDiscoveryHandlers;
		}

		/**
		 * Set the Store protocol handlers
		 */
		void setStoreProtocolHandlers(std::shared_ptr<StoreHandlers> storeHandlers) {
			while (protocolHandlers.size() < Energistics::Etp::v12::Datatypes::Protocols::Store + 1) {
				protocolHandlers.push_back(nullptr);
			}
			protocolHandlers[Energistics::Etp::v12::Datatypes::Protocols::Store] = storeHandlers;
		}

		/**
		 * Set the Data Array protocol handlers
		 */
		void setDataArrayProtocolHandlers(std::shared_ptr<DataArrayHandlers> dataArrayHandlers) {
			while (protocolHandlers.size() < Energistics::Etp::v12::Datatypes::Protocols::DataArray + 1) {
				protocolHandlers.push_back(nullptr);
			}
			protocolHandlers[Energistics::Etp::v12::Datatypes::Protocols::DataArray] = dataArrayHandlers;
		}

		void close();

		/**
		 * Create a default ETP message header from the ETP message body.
		 * Encode this created default ETP message header + the ETP message body into the session buffer.
		 * Write/send this session buffer on the web socket.
		 * @param mb The ETP message body to send
		 */
		template<typename T> void send(const T & mb, int64_t correlationId = 0, int32_t messageFlags = 0)
		{
			encode(mb, correlationId, messageFlags); // put the message to write in the queue

			if(queue.size() == 1) {
				do_write();
			}

			if ((messageFlags & 0x02) != 0 || (messageFlags & 0x01) == 0) {
				do_when_finished();
			}
		}

		/**
		 * Create a default ETP message header from the ETP message body.
		 * Encode this created default ETP message header + the ETP message body into the session buffer.
		 * Write/send this session buffer on the web socket and then read an answer.
		 * @param mb The ETP message body to send
		 */
		template<typename T> void sendAndDoRead(const T & mb, int64_t correlationId = 0, int32_t messageFlags = 0)
		{
			encode(mb, correlationId, messageFlags); // put the message to write in the queue
			if(queue.size() == 1) {
				do_write();
			}

			do_read();
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

		void on_write(boost::system::error_code ec, std::size_t bytes_transferred) {
			if(ec) {
				std::cerr << "on_write : " << ec.message() << std::endl;
			}

			// Remove the message from the queue
			queue.erase(queue.begin());

			if(! queue.empty()) {
				do_write();
			}
		}

		void on_close(boost::system::error_code ec) {
			if(ec) {
				std::cerr << "on_close : " << ec.message() << std::endl;
			}

			// If we get here then the connection is closed gracefully
#ifndef NDEBUG
			std::cout << "!!! CLOSED !!!" << std::endl;
#endif

			closed = true;
		}

		bool validateUri(const std::string & uri, bool sendException = false);
		bool validateDataObjectUri(const std::string & uri, bool sendException = false);
	};
}
