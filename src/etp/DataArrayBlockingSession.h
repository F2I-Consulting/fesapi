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

#include "AbstractSession.h"

#include <boost/asio/use_future.hpp>

namespace ETP_NS
{
	class DLL_IMPORT_OR_EXPORT DataArrayBlockingSession : public ETP_NS::AbstractSession
	{
	private:
		websocket::stream<tcp::socket> ws;
	    tcp::resolver resolver;
	    std::string host;
	    std::string port;
	    std::string target;
	    Energistics::Etp::v12::Protocol::Core::RequestSession requestSession;

		std::future<std::size_t> future_bytes_transferred;

	public:
	    /**
	     * @param host		The IP address on which the server is listening for etp (websocket) connection
	     * @param port		The port on which the server is listening for etp (websocket) connection
	     * @param target	usually "/" but a server can decide to serve etp on a particular target
	     */
		DataArrayBlockingSession(boost::asio::io_context& ioc,
				const std::string & host, const std::string & port, const std::string & target);

		virtual ~DataArrayBlockingSession() = default;

		boost::asio::io_context& getIoContext() {
			return static_cast<boost::asio::io_context&> (ws.get_executor().context());
		}

		bool run();

		void do_write() {
			auto completed = ws.async_write(
				boost::asio::buffer(sendingQueue[0]), boost::asio::use_future);
			completed.get();
			sendingQueue.erase(sendingQueue.begin());
			if (!sendingQueue.empty()) {
				do_write();
			}
		}

		void do_close() {
			ws.async_close(websocket::close_code::normal,
				std::bind(
					&AbstractSession::on_close,
					shared_from_this(),
					std::placeholders::_1));
		}

		void do_read();

		template<class T>
		void readArrayValues(const std::string & uri, const std::string & datasetName, T* values) {
			if (webSocketSessionClosed) {
				std::cout << "CLOSED : NOTHING MORE TO DO" << std::endl;
				return;
			}

			Energistics::Etp::v12::Protocol::DataArray::GetDataArrays gda;
			Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier dai;
			dai.uri = uri;
			dai.pathInResource = datasetName;
			gda.dataArrays["0"] = dai;
			send(gda);

			// Read a message into our buffer
			// For now hoping that this message is the response for the above sent message
			std::size_t bytes_transferred = future_bytes_transferred.get();

			boost::ignore_unused(bytes_transferred);

			if (bytes_transferred == 0) return;

			avro::InputStreamPtr in = avro::memoryInputStream(static_cast<const uint8_t*>(receivedBuffer.data().data()), bytes_transferred);
			avro::DecoderPtr d = avro::binaryDecoder();
			d->init(*in);

			Energistics::Etp::v12::Datatypes::MessageHeader receivedMh = decodeMessageHeader(d);

			if (receivedMh.protocol == Energistics::Etp::v12::Datatypes::Protocol::DataArray &&
				receivedMh.messageType == Energistics::Etp::v12::Protocol::DataArray::GetDataArraysResponse::messageTypeId) {
				Energistics::Etp::v12::Protocol::DataArray::GetDataArraysResponse gdar;
				avro::decode(*d, gdar);
				flushReceivingBuffer();

				if (gdar.dataArrays.size() == 1) {
					auto dataArray = gdar.dataArrays.begin()->second;
					if (dataArray.data.item.idx() == Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfBoolean) {
						Energistics::Etp::v12::Datatypes::ArrayOfBoolean& avroArray = dataArray.data.item.get_ArrayOfBoolean();
						for (auto i = 0; i < avroArray.values.size(); ++i) {
							values[i] = avroArray.values[i];
						}
					}
					else if (dataArray.data.item.idx() == Energistics::Etp::v12::Datatypes::AnyArrayType::bytes) {
						std::string& avroValues = dataArray.data.item.get_bytes();
						for (auto i = 0; i < avroValues.size(); ++i) {
							values[i] = avroValues[i];
						}
					}
					else if (dataArray.data.item.idx() == Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfInt) {
						Energistics::Etp::v12::Datatypes::ArrayOfInt& avroArray = dataArray.data.item.get_ArrayOfInt();
						for (auto i = 0; i < avroArray.values.size(); ++i) {
							values[i] = avroArray.values[i];
						}
					}
					else if (dataArray.data.item.idx() == Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfLong) {
						Energistics::Etp::v12::Datatypes::ArrayOfLong& avroArray = dataArray.data.item.get_ArrayOfLong();
						for (auto i = 0; i < avroArray.values.size(); ++i) {
							values[i] = avroArray.values[i];
						}
					}
					else if (dataArray.data.item.idx() == Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfFloat) {
						Energistics::Etp::v12::Datatypes::ArrayOfFloat& avroArray = dataArray.data.item.get_ArrayOfFloat();
						for (auto i = 0; i < avroArray.values.size(); ++i) {
							values[i] = avroArray.values[i];
						}
					}
					else if (dataArray.data.item.idx() == Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfDouble) {
						Energistics::Etp::v12::Datatypes::ArrayOfDouble& avroArray = dataArray.data.item.get_ArrayOfDouble();
						for (auto i = 0; i < avroArray.values.size(); ++i) {
							values[i] = avroArray.values[i];
						}
					}
				}
			}
			else {
				flushReceivingBuffer();
				std::cerr << "The data array session could not understand the received message : Protocol " << receivedMh.protocol << " and Message Type " << receivedMh.messageType << std::endl;
			}

			do_read();
		}
	};
}
