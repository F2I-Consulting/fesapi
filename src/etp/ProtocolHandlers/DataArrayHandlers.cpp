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
#include  "DataArrayHandlers.h"

#include "../AbstractSession.h"
#include "../EtpHelpers.h"

using namespace ETP_NS;

void DataArrayHandlers::decodeMessageBody(const Energistics::Etp::v12::Datatypes::MessageHeader & mh, avro::DecoderPtr d)
{
	if (mh.protocol != Energistics::Etp::v12::Datatypes::Protocol::DataArray) {
		std::cerr << "Error : This message header does not belong to the protocol DataArray" << std::endl;
		return;
	}

	if (mh.messageType == Energistics::Etp::v12::Protocol::DataArray::GetDataArrays::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::GetDataArrays gda;
		avro::decode(*d, gda);
		session->flushReceivingBuffer();
		on_GetDataArrays(gda, mh.messageId);
	}
	else if (mh.messageType == Energistics::Etp::v12::Protocol::DataArray::GetDataArraysResponse::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::GetDataArraysResponse gdar;
		avro::decode(*d, gdar);
		session->flushReceivingBuffer();
		on_GetDataArraysResponse(gdar);
	}
	else if (mh.messageType == Energistics::Etp::v12::Protocol::DataArray::PutDataArrays::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::PutDataArrays pda;
		avro::decode(*d, pda);
		session->flushReceivingBuffer();
		on_PutDataArrays(pda, mh.messageId);
	}
	else if (mh.messageType == Energistics::Etp::v12::Protocol::DataArray::PutDataArraysResponse::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::PutDataArraysResponse msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_PutDataArraysResponse(msg, mh.messageId);
	}
	else if (mh.messageType == Energistics::Etp::v12::Protocol::DataArray::GetDataSubarrays::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::GetDataSubarrays msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_GetDataSubarrays(msg, mh.messageId);
	}
	else if (mh.messageType == Energistics::Etp::v12::Protocol::DataArray::GetDataSubarraysResponse::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::GetDataSubarraysResponse msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_GetDataSubarraysResponse(msg);
	}
	else if (mh.messageType == Energistics::Etp::v12::Protocol::DataArray::PutDataSubarrays::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::PutDataSubarrays msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_PutDataSubarrays(msg, mh.messageId);
	}
	else if (mh.messageType == Energistics::Etp::v12::Protocol::DataArray::PutDataSubarraysResponse::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::PutDataSubarraysResponse msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_PutDataSubarraysResponse(msg, mh.messageId);
	}
	else if (mh.messageType == Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadata::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadata gdam;
		avro::decode(*d, gdam);
		session->flushReceivingBuffer();
		on_GetDataArrayMetadata(gdam, mh.messageId);
	}
	else if (mh.messageType == Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadataResponse::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadataResponse gdamr;
		avro::decode(*d, gdamr);
		session->flushReceivingBuffer();
		on_GetDataArrayMetadataResponse(gdamr);
	}
	else {
		session->flushReceivingBuffer();
		session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(3, "The message type ID " + std::to_string(mh.messageType) + " is invalid for the data array protocol."), mh.messageId, 0x02);
	}
}

void DataArrayHandlers::on_GetDataArrays(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrays &, int64_t correlationId)
{
	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The DataArrayHandlers::on_GetDataArrays method has not been overriden by the agent."), correlationId, 0x02);
}

void DataArrayHandlers::on_GetDataArraysResponse(Energistics::Etp::v12::Protocol::DataArray::GetDataArraysResponse & gdar)
{
	for (std::pair < std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray > element : gdar.dataArrays) {
		Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray& da = element.second;
		std::cout << "*************************************************" << std::endl;
		std::cout << "Data Array received : " << std::endl;
		std::cout << "Dimension count : " << da.dimensions.size() << std::endl;
		for (auto i = 0; i < da.dimensions.size(); ++i) {
			std::cout << "Dimension " << i << " with count : " << da.dimensions[i] << std::endl;
		}
		std::cout << "*************************************************" << std::endl;
		if (da.data.item.idx() == Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfBoolean) {
			Energistics::Etp::v12::Datatypes::ArrayOfBoolean avroArray = da.data.item.get_ArrayOfBoolean();
			auto values = avroArray.values;
			for (auto i = 0; i < values.size() && i < 20; ++i) {
				std::cout << "bool value " << i << " == " << values[i] << std::endl;
			}
		}
		else if (da.data.item.idx() == Energistics::Etp::v12::Datatypes::AnyArrayType::bytes) {
			std::string values = da.data.item.get_bytes();
			for (auto i = 0; i < values.size() && i < 20; ++i) {
				std::cout << "char value " << i << " == " << (int)values[i] << std::endl;
			}
		}
		else if (da.data.item.idx() == Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfInt) {
			Energistics::Etp::v12::Datatypes::ArrayOfInt avroArray = da.data.item.get_ArrayOfInt();
			auto values = avroArray.values;
			for (auto i = 0; i < values.size() && i < 20; ++i) {
				std::cout << "int value " << i << " == " << values[i] << std::endl;
			}
		}
		else if (da.data.item.idx() == Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfLong) {
			Energistics::Etp::v12::Datatypes::ArrayOfLong avroArray = da.data.item.get_ArrayOfLong();
			auto values = avroArray.values;
			for (auto i = 0; i < values.size() && i < 20; ++i) {
				std::cout << "long value " << i << " == " << values[i] << std::endl;
			}
		}
		else if (da.data.item.idx() == Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfFloat) {
			Energistics::Etp::v12::Datatypes::ArrayOfFloat avroArray = da.data.item.get_ArrayOfFloat();
			auto values = avroArray.values;
			for (auto i = 0; i < values.size() && i < 20; ++i) {
				std::cout << "float value " << i << " == " << values[i] << std::endl;
			}
		}
		else if (da.data.item.idx() == Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfDouble) {
			Energistics::Etp::v12::Datatypes::ArrayOfDouble avroArray = da.data.item.get_ArrayOfDouble();
			auto values = avroArray.values;
			for (auto i = 0; i < values.size() && i < 20; ++i) {
				std::cout << "double value " << i << " == " << values[i] << std::endl;
			}
		}
		std::cout << "*************************************************" << std::endl;
	}
}

void DataArrayHandlers::on_PutDataArrays(const Energistics::Etp::v12::Protocol::DataArray::PutDataArrays&, int64_t correlationId)
{
	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The DataArrayHandlers::on_PutDataArrays method has not been overriden by the agent."), correlationId, 0x02);
}

void DataArrayHandlers::on_PutDataArraysResponse(const Energistics::Etp::v12::Protocol::DataArray::PutDataArraysResponse&, int64_t)
{
	std::cout << "Received PutDataArraysResponse." << std::endl;
}

void DataArrayHandlers::on_GetDataSubarrays(const Energistics::Etp::v12::Protocol::DataArray::GetDataSubarrays&, int64_t correlationId)
{
	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The DataArrayHandlers::on_GetDataArraySlice method has not been overriden by the agent."), correlationId, 0x02);
}

void DataArrayHandlers::on_GetDataSubarraysResponse(const Energistics::Etp::v12::Protocol::DataArray::GetDataSubarraysResponse&)
{
	std::cout << "on_GetDataArraySlicesResponse : not implemented yet" << std::endl;
}

void DataArrayHandlers::on_PutDataSubarrays(const Energistics::Etp::v12::Protocol::DataArray::PutDataSubarrays&, int64_t correlationId)
{
	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The DataArrayHandlers::on_PutDataArraySlices method has not been overriden by the agent."), correlationId, 0x02);
}

void DataArrayHandlers::on_PutDataSubarraysResponse(const Energistics::Etp::v12::Protocol::DataArray::PutDataSubarraysResponse&, int64_t)
{
	std::cout << "Received PutDataSubarraysResponse." << std::endl;
}

void DataArrayHandlers::on_GetDataArrayMetadata(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadata&, int64_t correlationId)
{
	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The DataArrayHandlers::on_GetDataArrayMetadata method has not been overriden by the agent."), correlationId, 0x02);
}

void DataArrayHandlers::on_GetDataArrayMetadataResponse(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadataResponse& gdamr)
{
	for (std::pair < std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayMetadata > element : gdamr.arrayMetadata) {
		Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayMetadata& dam = element.second;
		std::cout << "*************************************************" << std::endl;
		std::cout << "Data Array Metadata received : " << std::endl;
		std::cout << "Array type : ";
		switch (dam.arrayType) {
			case 0: std::cout << "bool"; break;
			case 1: std::cout << "int"; break;
			case 2: std::cout << "long"; break;
			case 3: std::cout << "float"; break;
			case 4: std::cout << "double"; break;
			case 5: std::cout << "string"; break;
			case 6: std::cout << "byte"; break;
		}
		std::cout << std::endl;
		for (auto i = 0; i < dam.dimensions.size(); ++i) {
			std::cout << "Dimension " << i << " with count : " << dam.dimensions[i] << std::endl;
		}
		std::cout << "*************************************************" << std::endl;
	}
}

void DataArrayHandlers::on_PutUninitializedDataArrays(const Energistics::Etp::v12::Protocol::DataArray::PutUninitializedDataArrays&, int64_t correlationId)
{
	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The DataArrayHandlers::on_PutUninitializedDataArrays method has not been overriden by the agent."), correlationId, 0x02);
}

void DataArrayHandlers::on_PutUninitializedDataArraysResponse(const Energistics::Etp::v12::Protocol::DataArray::PutUninitializedDataArraysResponse&)
{
	std::cout << "Received PutUninitializedDataArraysResponse." << std::endl;
}
