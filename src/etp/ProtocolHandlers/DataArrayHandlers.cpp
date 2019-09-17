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
#include  "etp/ProtocolHandlers/DataArrayHandlers.h"

#include "etp/AbstractSession.h"
#include "etp/EtpHelpers.h"

using namespace ETP_NS;

void DataArrayHandlers::decodeMessageBody(const Energistics::Etp::v12::Datatypes::MessageHeader & mh, avro::DecoderPtr d)
{
	if (mh.m_protocol != Energistics::Etp::v12::Datatypes::Protocol::DataArray) {
		std::cerr << "Error : This message header does not belong to the protocol DataArray" << std::endl;
		return;
	}

	if (mh.m_messageType == Energistics::Etp::v12::Protocol::DataArray::GetDataArrays::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::GetDataArrays gda;
		avro::decode(*d, gda);
		session->flushReceivingBuffer();
		on_GetDataArrays(gda, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::DataArray::GetDataArraysResponse::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::GetDataArraysResponse gdar;
		avro::decode(*d, gdar);
		session->flushReceivingBuffer();
		on_GetDataArraysResponse(gdar);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::DataArray::PutDataArrays::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::PutDataArrays pda;
		avro::decode(*d, pda);
		session->flushReceivingBuffer();
		on_PutDataArrays(pda, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::DataArray::GetDataArraySlices::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::GetDataArraySlices gdas;
		avro::decode(*d, gdas);
		session->flushReceivingBuffer();
		on_GetDataArraySlices(gdas, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::DataArray::GetDataArraySlicesResponse::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::GetDataArraySlicesResponse gdasr;
		avro::decode(*d, gdasr);
		session->flushReceivingBuffer();
		on_GetDataArraySlicesResponse(gdasr);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::DataArray::PutDataArraySlices::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::PutDataArraySlices pdas;
		avro::decode(*d, pdas);
		session->flushReceivingBuffer();
		on_PutDataArraySlices(pdas, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadata::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadata gdam;
		avro::decode(*d, gdam);
		session->flushReceivingBuffer();
		on_GetDataArrayMetadata(gdam, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadataResponse::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadataResponse gdamr;
		avro::decode(*d, gdamr);
		session->flushReceivingBuffer();
		on_GetDataArrayMetadataResponse(gdamr);
	}
	else {
		session->flushReceivingBuffer();
		sendExceptionCode3();
	}
}

void DataArrayHandlers::on_GetDataArrays(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrays & gdas, int64_t correlationId)
{
	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The DataArrayHandlers::on_GetDataArrays method has not been overriden by the agent."));
}

void DataArrayHandlers::on_GetDataArraysResponse(Energistics::Etp::v12::Protocol::DataArray::GetDataArraysResponse & gdar)
{
	for (std::pair < std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray > element : gdar.m_dataArrays) {
		Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray& da = element.second;
		std::cout << "*************************************************" << std::endl;
		std::cout << "Data Array received : " << std::endl;
		std::cout << "Dimension count : " << da.m_dimensions.size() << std::endl;
		for (auto i = 0; i < da.m_dimensions.size(); ++i) {
			std::cout << "Dimension " << i << " with count : " << da.m_dimensions[i] << std::endl;
		}
		std::cout << "*************************************************" << std::endl;
		if (da.m_data.m_item.idx() - 1 == Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfBoolean) {
			Energistics::Etp::v12::Datatypes::ArrayOfBoolean avroArray = da.m_data.m_item.get_ArrayOfBoolean();
			auto values = avroArray.m_values;
			for (auto i = 0; i < values.size() && i < 20; ++i) {
				std::cout << "bool value " << i << " == " << values[i] << std::endl;
			}
		}
		else if (da.m_data.m_item.idx() - 1 == Energistics::Etp::v12::Datatypes::AnyArrayType::bytes) {
			std::string values = da.m_data.m_item.get_bytes();
			for (auto i = 0; i < values.size() && i < 20; ++i) {
				std::cout << "char value " << i << " == " << (int)values[i] << std::endl;
			}
		}
		else if (da.m_data.m_item.idx() - 1 == Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfInt) {
			Energistics::Etp::v12::Datatypes::ArrayOfInt avroArray = da.m_data.m_item.get_ArrayOfInt();
			auto values = avroArray.m_values;
			for (auto i = 0; i < values.size() && i < 20; ++i) {
				std::cout << "int value " << i << " == " << values[i] << std::endl;
			}
		}
		else if (da.m_data.m_item.idx() - 1 == Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfLong) {
			Energistics::Etp::v12::Datatypes::ArrayOfLong avroArray = da.m_data.m_item.get_ArrayOfLong();
			auto values = avroArray.m_values;
			for (auto i = 0; i < values.size() && i < 20; ++i) {
				std::cout << "long value " << i << " == " << values[i] << std::endl;
			}
		}
		else if (da.m_data.m_item.idx() - 1 == Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfFloat) {
			Energistics::Etp::v12::Datatypes::ArrayOfFloat avroArray = da.m_data.m_item.get_ArrayOfFloat();
			auto values = avroArray.m_values;
			for (auto i = 0; i < values.size() && i < 20; ++i) {
				std::cout << "float value " << i << " == " << values[i] << std::endl;
			}
		}
		else if (da.m_data.m_item.idx() - 1 == Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfDouble) {
			Energistics::Etp::v12::Datatypes::ArrayOfDouble avroArray = da.m_data.m_item.get_ArrayOfDouble();
			auto values = avroArray.m_values;
			for (auto i = 0; i < values.size() && i < 20; ++i) {
				std::cout << "double value " << i << " == " << values[i] << std::endl;
			}
		}
		std::cout << "*************************************************" << std::endl;
	}
}

void DataArrayHandlers::on_PutDataArrays(const Energistics::Etp::v12::Protocol::DataArray::PutDataArrays & pda, int64_t correlationId)
{
	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The DataArrayHandlers::on_PutDataArrays method has not been overriden by the agent."));
}

void DataArrayHandlers::on_GetDataArraySlices(const Energistics::Etp::v12::Protocol::DataArray::GetDataArraySlices & gdas, int64_t correlationId)
{
	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The DataArrayHandlers::on_GetDataArraySlice method has not been overriden by the agent."));
}

void DataArrayHandlers::on_GetDataArraySlicesResponse(const Energistics::Etp::v12::Protocol::DataArray::GetDataArraySlicesResponse & gdasr)
{
	std::cout << "on_GetDataArraySlicesResponse : not implemented yet" << std::endl;
}

void DataArrayHandlers::on_PutDataArraySlices(const Energistics::Etp::v12::Protocol::DataArray::PutDataArraySlices & pdas, int64_t correlationId)
{
	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The DataArrayHandlers::on_PutDataArraySlices method has not been overriden by the agent."));
}

void DataArrayHandlers::on_GetDataArrayMetadata(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadata & gdam, int64_t correlationId)
{
	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The DataArrayHandlers::on_GetDataArrayMetadata method has not been overriden by the agent."));
}

void DataArrayHandlers::on_GetDataArrayMetadataResponse(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadataResponse & gdamr)
{
	for (std::pair < std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayMetadata > element : gdamr.m_arrayMetadata) {
		Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayMetadata& dam = element.second;
		std::cout << "*************************************************" << std::endl;
		std::cout << "Data Array Metadata received : " << std::endl;
		std::cout << "Array type : ";
		switch (dam.m_arrayType) {
		case 0: std::cout << "bool"; break;
		case 1: std::cout << "int"; break;
		case 2: std::cout << "long"; break;
		case 3: std::cout << "float"; break;
		case 4: std::cout << "double"; break;
		case 5: std::cout << "string"; break;
		case 6: std::cout << "byte"; break;
		}
		std::cout << std::endl;
		for (auto i = 0; i < dam.m_dimensions.size(); ++i) {
			std::cout << "Dimension " << i << " with count : " << dam.m_dimensions[i] << std::endl;
		}
		std::cout << "*************************************************" << std::endl;
	}
}
