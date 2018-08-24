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

#include <regex>

#include "etp/AbstractSession.h"

using namespace ETP_NS;

void DataArrayHandlers::decodeMessageBody(const Energistics::Etp::v12::Datatypes::MessageHeader & mh, avro::DecoderPtr d)
{
	if (mh.m_protocol != Energistics::Etp::v12::Datatypes::Protocols::DataArray) {
		std::cerr << "Error : This message header does not belong to the protocol DataArray" << std::endl;
		return;
	}

	if (mh.m_messageType == Energistics::Etp::v12::Protocol::DataArray::GetDataArray::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::GetDataArray gda;
		avro::decode(*d, gda);
		session->flushReceivingBuffer();
		on_GetDataArray(gda, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::DataArray::PutDataArray::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::PutDataArray pda;
		avro::decode(*d, pda);
		session->flushReceivingBuffer();
		on_PutDataArray(pda, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::DataArray::GetDataArraySlice::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::GetDataArraySlice gdas;
		avro::decode(*d, gdas);
		session->flushReceivingBuffer();
		on_GetDataArraySlice(gdas, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::DataArray::PutDataArraySlice::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::PutDataArraySlice pdas;
		avro::decode(*d, pdas);
		session->flushReceivingBuffer();
		on_PutDataArraySlice(pdas, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::DataArray::DataArray::messageTypeId) {
		Energistics::Etp::v12::Protocol::DataArray::DataArray da;
		avro::decode(*d, da);
		session->flushReceivingBuffer();
		on_DataArray(da);
		if ((mh.m_messageFlags & 0x02) != 0 || (mh.m_messageFlags & 0x01) == 0) {
			session->do_when_finished();
		}
		else {
			session->do_read();
		}
	}
	else {
		session->flushReceivingBuffer();
		sendExceptionCode3();
	}
}

void DataArrayHandlers::on_GetDataArray(const Energistics::Etp::v12::Protocol::DataArray::GetDataArray & gda, int64_t correlationId)
{
	std::cout << "on_GetDataArray" << std::endl;

	Energistics::Etp::v12::Protocol::Core::ProtocolException error;
	error.m_errorCode = 7;
	error.m_errorMessage = "The DataArrayHandlers::on_GetDataArray method has not been overriden by the agent.";

	session->send(error);
}

void DataArrayHandlers::on_PutDataArray(const Energistics::Etp::v12::Protocol::DataArray::PutDataArray & pda, int64_t correlationId)
{
	std::cout << "on_PutDataArray" << std::endl;

	Energistics::Etp::v12::Protocol::Core::ProtocolException error;
	error.m_errorCode = 7;
	error.m_errorMessage = "The DataArrayHandlers::on_PutDataArray method has not been overriden by the agent.";

	session->send(error);
}

void DataArrayHandlers::on_GetDataArraySlice(const Energistics::Etp::v12::Protocol::DataArray::GetDataArraySlice & gdas, int64_t correlationId)
{
	std::cout << "on_GetDataArraySlice" << std::endl;

	Energistics::Etp::v12::Protocol::Core::ProtocolException error;
	error.m_errorCode = 7;
	error.m_errorMessage = "The DataArrayHandlers::on_GetDataArraySlice method has not been overriden by the agent.";

	session->send(error);
}

void DataArrayHandlers::on_PutDataArraySlice(const Energistics::Etp::v12::Protocol::DataArray::PutDataArraySlice & pdas, int64_t correlationId)
{
	std::cout << "on_PutDataArraySlice" << std::endl;

	Energistics::Etp::v12::Protocol::Core::ProtocolException error;
	error.m_errorCode = 7;
	error.m_errorMessage = "The DataArrayHandlers::on_PutDataArraySlice method has not been overriden by the agent.";

	session->send(error);
}

void DataArrayHandlers::on_DataArray(Energistics::Etp::v12::Protocol::DataArray::DataArray & da)
{
	std::cout << "*************************************************" << std::endl;
	std::cout << "Data Array received : " << std::endl;
	std::cout << "Dimension count : " << da.m_dimensions.size() << std::endl;
	for (auto i = 0; i < da.m_dimensions.size(); ++i) {
		std::cout << "Dimension " << i << " with count : " << da.m_dimensions[i] << std::endl;
	}
	std::cout << "*************************************************" << std::endl;
	if (da.m_data.m_item.idx() - 1 == Energistics::Etp::v12::Datatypes::AnyArrayTypes::arrayOfBoolean) {
		Energistics::Etp::v12::Datatypes::ArrayOfBoolean avroArray  = da.m_data.m_item.get_ArrayOfBoolean();
		auto values = avroArray.m_values;
		for (auto i = 0; i < values.size() && i < 20; ++i) {
			std::cout << "bool value " << i << " == " << values[i] << std::endl;
		}
	}
	else if (da.m_data.m_item.idx() - 1 == Energistics::Etp::v12::Datatypes::AnyArrayTypes::arrayOfBytes) {
		std::string values  = da.m_data.m_item.get_bytes();
		for (auto i = 0; i < values.size() && i < 20; ++i) {
			std::cout << "char value " << i << " == " << (int)values[i] << std::endl;
		}
	}
	else if (da.m_data.m_item.idx() - 1 == Energistics::Etp::v12::Datatypes::AnyArrayTypes::arrayOfInt) {
		Energistics::Etp::v12::Datatypes::ArrayOfInt avroArray  = da.m_data.m_item.get_ArrayOfInt();
		auto values = avroArray.m_values;
		for (auto i = 0; i < values.size() && i < 20; ++i) {
			std::cout << "int value " << i << " == " << values[i] << std::endl;
		}
	}
	else if (da.m_data.m_item.idx() - 1 == Energistics::Etp::v12::Datatypes::AnyArrayTypes::arrayOfLong) {
		Energistics::Etp::v12::Datatypes::ArrayOfLong avroArray  = da.m_data.m_item.get_ArrayOfLong();
		auto values = avroArray.m_values;
		for (auto i = 0; i < values.size() && i < 20; ++i) {
			std::cout << "long value " << i << " == " << values[i] << std::endl;
		}
	}
	else if (da.m_data.m_item.idx() - 1 == Energistics::Etp::v12::Datatypes::AnyArrayTypes::arrayOfLong) {
		Energistics::Etp::v12::Datatypes::ArrayOfFloat avroArray  = da.m_data.m_item.get_ArrayOfFloat();
		auto values = avroArray.m_values;
		for (auto i = 0; i < values.size() && i < 20; ++i) {
			std::cout << "float value " << i << " == " << values[i] << std::endl;
		}
	}
	else if (da.m_data.m_item.idx() - 1 == Energistics::Etp::v12::Datatypes::AnyArrayTypes::arrayOfDouble) {
		Energistics::Etp::v12::Datatypes::ArrayOfDouble avroArray  = da.m_data.m_item.get_ArrayOfDouble();
		auto values = avroArray.m_values;
		for (auto i = 0; i < values.size() && i < 20; ++i) {
			std::cout << "double value " << i << " == " << values[i] << std::endl;
		}
	}
	std::cout << "*************************************************" << std::endl;
}
