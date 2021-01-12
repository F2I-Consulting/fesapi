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

#include "../nsDefinitions.h"

#include "EtpMessages.h"
#include "ProtocolHandlers/CoreHandlers.h"
#include "ProtocolHandlers/DiscoveryHandlers.h"
#include "ProtocolHandlers/StoreHandlers.h"
#include "ProtocolHandlers/StoreNotificationHandlers.h"
#include "ProtocolHandlers/DataArrayHandlers.h"

#include <unordered_map>

#if defined(_WIN32) && !defined(FESAPI_STATIC)
	#ifndef DLL_IMPORT_OR_EXPORT
		#if defined(FesapiCpp_EXPORTS) || defined(FesapiCppUnderDev_EXPORTS)
			#define DLL_IMPORT_OR_EXPORT __declspec(dllexport)
		#else
			#define DLL_IMPORT_OR_EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#define DLL_IMPORT_OR_EXPORT
#endif

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
		boost::beast::flat_buffer receivedBuffer;
	    std::vector<std::shared_ptr<ETP_NS::ProtocolHandlers>> protocolHandlers;
		std::unordered_map<int64_t, std::shared_ptr<ETP_NS::ProtocolHandlers>> specificProtocolHandlers;
	    bool webSocketSessionClosed; // open with the websocket handshake
		bool etpSessionClosed; // open with the requestSession and openSession message
		std::vector<std::vector<uint8_t> > sendingQueue;
		int64_t messageId;

	    AbstractSession() : receivedBuffer(), protocolHandlers(), specificProtocolHandlers(),
			webSocketSessionClosed(true), etpSessionClosed(true),
			sendingQueue() {}

		/**
		 * Write the current buffer on the web socket
		 */
		virtual void do_write() = 0;

		/**
		 * Reads the message header currently stored in the decoder.
		 * @param decoder	Must be initialized with stream containing a coded message header.
		 */
		Energistics::Etp::v12::Datatypes::MessageHeader decodeMessageHeader(avro::DecoderPtr decoder);

		/**
		* Return the current message id and increment it for next call.
		*/
		int64_t incrementMessageId() {
			int64_t result = messageId;
			messageId += 2;
			return  result;
		}

		template<typename T> int64_t encode(const T & mb, int64_t correlationId = 0, int32_t messageFlags = 0)
		{
			// Build message header
			Energistics::Etp::v12::Datatypes::MessageHeader mh;
			mh.protocol = mb.protocolId;
			mh.messageType = mb.messageTypeId;
			mh.correlationId = correlationId;
			mh.messageId = incrementMessageId();
			mh.messageFlags = messageFlags;

#ifndef NDEBUG
			std::cout << "*************************************************" << std::endl;
			std::cout << "Message Header sent : " << std::endl;
			std::cout << "protocol : " << mh.protocol << std::endl;
			std::cout << "type : " << mh.messageType << std::endl;
			std::cout << "id : " << mh.messageId << std::endl;
			std::cout << "correlation id : " << mh.correlationId << std::endl;
			std::cout << "flags : " << mh.messageFlags << std::endl;
			std::cout << "*************************************************" << std::endl;
#endif

			avro::OutputStreamPtr out = avro::memoryOutputStream();
			avro::EncoderPtr e = avro::binaryEncoder();
			e->init(*out);
			avro::encode(*e, mh);
			avro::encode(*e, mb);
			sendingQueue.push_back(*avro::snapshot(*out).get());
			e->flush();

			return mh.messageId;
		}

	public:

		virtual ~AbstractSession() = default;

		/**
		* The list of subscriptions recorded by customers on this session.
		*/
		std::unordered_map<int64_t, Energistics::Etp::v12::Datatypes::Object::SubscriptionInfo> subscriptions;

		virtual boost::asio::io_context& getIoContext() = 0;

		void flushReceivingBuffer() {
			receivedBuffer.consume(receivedBuffer.size());
		}

		/**
		 * Set the Core protocol handlers
		 */
		DLL_IMPORT_OR_EXPORT void setCoreProtocolHandlers(std::shared_ptr<CoreHandlers> coreHandlers) {
	    	if (protocolHandlers.empty()) {
	    		protocolHandlers.push_back(coreHandlers);
	    	}
	    	else {
	    		protocolHandlers[Energistics::Etp::v12::Datatypes::Protocol::Core] = coreHandlers;
	    	}
	    }

	    /**
		 * Set the Discovery protocol handlers
		 */
		DLL_IMPORT_OR_EXPORT void setDiscoveryProtocolHandlers(std::shared_ptr<DiscoveryHandlers> discoveryHandlers) {
			while (protocolHandlers.size() < Energistics::Etp::v12::Datatypes::Protocol::Discovery + 1) {
				protocolHandlers.push_back(nullptr);
			}
			protocolHandlers[Energistics::Etp::v12::Datatypes::Protocol::Discovery] = discoveryHandlers;
		}

		DLL_IMPORT_OR_EXPORT std::shared_ptr<ETP_NS::ProtocolHandlers> getDiscoveryProtocolHandlers() {
			return protocolHandlers.size() > Energistics::Etp::v12::Datatypes::Protocol::Discovery ?
				protocolHandlers[Energistics::Etp::v12::Datatypes::Protocol::Discovery] :
				nullptr;
		}

		/**
		 * Set the Store protocol handlers
		 */
		DLL_IMPORT_OR_EXPORT void setStoreProtocolHandlers(std::shared_ptr<StoreHandlers> storeHandlers) {
			while (protocolHandlers.size() < Energistics::Etp::v12::Datatypes::Protocol::Store + 1) {
				protocolHandlers.push_back(nullptr);
			}
			protocolHandlers[Energistics::Etp::v12::Datatypes::Protocol::Store] = storeHandlers;
		}

		DLL_IMPORT_OR_EXPORT std::shared_ptr<ETP_NS::ProtocolHandlers> getStoreProtocolHandlers() {
			return protocolHandlers.size() > Energistics::Etp::v12::Datatypes::Protocol::Store ?
				protocolHandlers[Energistics::Etp::v12::Datatypes::Protocol::Store] :
				nullptr;
		}

		/**
		* Set the StoreNotification protocol handlers
		*/
		DLL_IMPORT_OR_EXPORT void setStoreNotificationProtocolHandlers(std::shared_ptr<ETP_NS::StoreNotificationHandlers> storeNotificationHandlers) {
			while (protocolHandlers.size() < Energistics::Etp::v12::Datatypes::Protocol::StoreNotification + 1) {
				protocolHandlers.push_back(nullptr);
			}
			protocolHandlers[Energistics::Etp::v12::Datatypes::Protocol::StoreNotification] = storeNotificationHandlers;
		}

		DLL_IMPORT_OR_EXPORT std::shared_ptr<ETP_NS::ProtocolHandlers> getStoreNotificationProtocolHandlers() {
			return protocolHandlers.size() > Energistics::Etp::v12::Datatypes::Protocol::StoreNotification ?
				protocolHandlers[Energistics::Etp::v12::Datatypes::Protocol::StoreNotification] :
				nullptr;
		}

		/**
		 * Set the Data Array protocol handlers
		 */
		DLL_IMPORT_OR_EXPORT void setDataArrayProtocolHandlers(std::shared_ptr<DataArrayHandlers> dataArrayHandlers) {
			while (protocolHandlers.size() < Energistics::Etp::v12::Datatypes::Protocol::DataArray + 1) {
				protocolHandlers.push_back(nullptr);
			}
			protocolHandlers[Energistics::Etp::v12::Datatypes::Protocol::DataArray] = dataArrayHandlers;
		}

		DLL_IMPORT_OR_EXPORT void close();

		/**
		 * Create a default ETP message header from the ETP message body.
		 * Encode this created default ETP message header + the ETP message body into the session buffer.
		 * Write/send this session buffer on the web socket.
		 * @param mb The ETP message body to send
		 * @param correlationId The ID of the message which this messag is answering to.
		 * @param messageFlags The message flags to be sent within the header
		 */
		template<typename T> int64_t send(const T & mb, int64_t correlationId = 0, int32_t messageFlags = 0)
		{
			int64_t msgId = encode(mb, correlationId, messageFlags); // put the message to write in the queue

			if(sendingQueue.size() == 1) {
				do_write();
			}

			return msgId;
		}

		/**
		* Send a message and register a specific handler for the response.
		*/
		template<typename T> int64_t sendWithSpecificHandler(const T & mb, std::shared_ptr<ETP_NS::ProtocolHandlers> specificHandler, int64_t correlationId = 0, int32_t messageFlags = 0)
		{
			int64_t msgId = send(mb, correlationId, messageFlags);
			specificProtocolHandlers[msgId] = specificHandler;

			return msgId;
		}

		DLL_IMPORT_OR_EXPORT void sendCloseFrame() {
			std::vector<uint8_t> empty;
			sendingQueue.push_back(empty);

			if (sendingQueue.size() == 1) {
				do_write();
			}
		}

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
		DLL_IMPORT_OR_EXPORT void on_read(boost::system::error_code ec, std::size_t bytes_transferred);

		void on_write(boost::system::error_code ec, std::size_t) {
			if(ec) {
				std::cerr << "on_write : " << ec.message() << std::endl;
			}

			// Remove the message from the queue
			sendingQueue.erase(sendingQueue.begin());

			if(! sendingQueue.empty()) {
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
			webSocketSessionClosed = true;
		}

		DLL_IMPORT_OR_EXPORT bool isWebSocketSessionClosed() const { return webSocketSessionClosed;  }

		DLL_IMPORT_OR_EXPORT void setEtpSessionClosed(bool etpSessionClosed_) { etpSessionClosed = etpSessionClosed_; }
		DLL_IMPORT_OR_EXPORT bool isEtpSessionClosed() const { return webSocketSessionClosed || etpSessionClosed; }
	};
}
