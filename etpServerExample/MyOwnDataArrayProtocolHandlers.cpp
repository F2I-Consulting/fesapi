/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agceements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"; you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agceed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-----------------------------------------------------------------------*/
#include "MyOwnDataArrayProtocolHandlers.h"

#include "common/AbstractHdfProxy.h"

void MyOwnDataArrayProtocolHandlers::on_GetDataArray(const Energistics::Etp::v12::Protocol::DataArray::GetDataArray & gda, int64_t correlationId)
{
	std::cout << "Data array received uri : " << gda.m_uri << std::endl;
	COMMON_NS::AbstractObject* obj = static_cast<MyOwnEtpServerSession*>(session)->getObjectFromUri(gda.m_uri);
	if (obj == nullptr) {
		return;
	}

	COMMON_NS::AbstractHdfProxy* hdfProxy = dynamic_cast<COMMON_NS::AbstractHdfProxy*>(obj);
	if (hdfProxy == nullptr) {
		Energistics::Etp::v12::Protocol::Core::ProtocolException error;
		error.m_errorCode = 11;
		error.m_errorMessage = obj->getUuid() + " cannot be resolved as an HDF Proxy in this store";

		session->send(error);
		return;
	}

	std::cout << "Received pathInResource : " << gda.m_pathInResource << std::endl;
	Energistics::Etp::v12::Protocol::DataArray::DataArray daResponse;
	auto elemCountPerDim = hdfProxy->getElementCountPerDimension(gda.m_pathInResource);
	daResponse.m_dimensions.reserve(elemCountPerDim.size());
	unsigned long long globalElemCount = 1;
	for (auto i = 0; i < elemCountPerDim.size(); ++i) {
		daResponse.m_dimensions.push_back(elemCountPerDim[i]);
		globalElemCount *= elemCountPerDim[i];
	}

	auto dt = hdfProxy->getHdfDatatypeInDataset(gda.m_pathInResource);
	if (dt == COMMON_NS::AbstractObject::DOUBLE)
	{
		double* hdfValues = new double[globalElemCount];
		hdfProxy->readArrayNdOfDoubleValues(gda.m_pathInResource, hdfValues);
		Energistics::Etp::v12::Datatypes::ArrayOfDouble avroArray;
		avroArray.m_values.assign(hdfValues, hdfValues + globalElemCount );
		delete [] hdfValues;
		daResponse.m_data.m_item.set_ArrayOfDouble(avroArray);
	}
	else if (dt == COMMON_NS::AbstractObject::FLOAT)
	{
		float* hdfValues = new float[globalElemCount];
		hdfProxy->readArrayNdOfFloatValues(gda.m_pathInResource, hdfValues);
		Energistics::Etp::v12::Datatypes::ArrayOfFloat avroArray;
		avroArray.m_values.assign(hdfValues, hdfValues + globalElemCount );
		delete [] hdfValues;
		daResponse.m_data.m_item.set_ArrayOfFloat(avroArray);
	}
	else if (dt == COMMON_NS::AbstractObject::LONG)
	{
		LONG64* hdfValues = new LONG64[globalElemCount];
		hdfProxy->readArrayNdOfGSoapLong64Values(gda.m_pathInResource, hdfValues);
		Energistics::Etp::v12::Datatypes::ArrayOfLong avroArray;
		avroArray.m_values.assign(hdfValues, hdfValues + globalElemCount );
		delete [] hdfValues;
		daResponse.m_data.m_item.set_ArrayOfLong(avroArray);
	}
	else if (dt == COMMON_NS::AbstractObject::ULONG)
	{
		ULONG64* hdfValues = new ULONG64[globalElemCount];
		hdfProxy->readArrayNdOfGSoapULong64Values(gda.m_pathInResource, hdfValues);
		Energistics::Etp::v12::Datatypes::ArrayOfLong avroArray;
		avroArray.m_values.assign(hdfValues, hdfValues + globalElemCount );
		delete [] hdfValues;
		daResponse.m_data.m_item.set_ArrayOfLong(avroArray);
	}
	else if (dt == COMMON_NS::AbstractObject::INT)
	{
		int* hdfValues = new int[globalElemCount];
		hdfProxy->readArrayNdOfIntValues(gda.m_pathInResource, hdfValues);
		Energistics::Etp::v12::Datatypes::ArrayOfInt avroArray;
		avroArray.m_values.assign(hdfValues, hdfValues + globalElemCount );
		delete [] hdfValues;
		daResponse.m_data.m_item.set_ArrayOfInt(avroArray);
	}
	else if (dt == COMMON_NS::AbstractObject::UINT)
	{
		unsigned int* hdfValues = new unsigned int[globalElemCount];
		hdfProxy->readArrayNdOfUIntValues(gda.m_pathInResource, hdfValues);
		Energistics::Etp::v12::Datatypes::ArrayOfInt avroArray;
		avroArray.m_values.assign(hdfValues, hdfValues + globalElemCount );
		delete [] hdfValues;
		daResponse.m_data.m_item.set_ArrayOfInt(avroArray);
	}
	else if (dt == COMMON_NS::AbstractObject::SHORT)
	{
		short* hdfValues = new short[globalElemCount];
		hdfProxy->readArrayNdOfShortValues(gda.m_pathInResource, hdfValues);
		Energistics::Etp::v12::Datatypes::ArrayOfInt avroArray;
		avroArray.m_values.assign(hdfValues, hdfValues + globalElemCount );
		delete [] hdfValues;
		daResponse.m_data.m_item.set_ArrayOfInt(avroArray);
	}
	else if (dt == COMMON_NS::AbstractObject::USHORT)
	{
		unsigned short* hdfValues = new unsigned short[globalElemCount];
		hdfProxy->readArrayNdOfUShortValues(gda.m_pathInResource, hdfValues);
		Energistics::Etp::v12::Datatypes::ArrayOfInt avroArray;
		avroArray.m_values.assign(hdfValues, hdfValues + globalElemCount );
		delete [] hdfValues;
		daResponse.m_data.m_item.set_ArrayOfInt(avroArray);
	}
	else if (dt == COMMON_NS::AbstractObject::CHAR)
	{
		char* hdfValues = new char[globalElemCount];
		hdfProxy->readArrayNdOfCharValues(gda.m_pathInResource, hdfValues);
		std::string avroArray;
		avroArray.assign(hdfValues, hdfValues + globalElemCount );
		delete [] hdfValues;
		daResponse.m_data.m_item.set_bytes(avroArray);
	}
	else if (dt == COMMON_NS::AbstractObject::UCHAR)
	{
		unsigned char* hdfValues = new unsigned char[globalElemCount];
		hdfProxy->readArrayNdOfUCharValues(gda.m_pathInResource, hdfValues);
		std::string avroArray;
		avroArray.assign(hdfValues, hdfValues + globalElemCount );
		delete [] hdfValues;
		daResponse.m_data.m_item.set_bytes(avroArray);
	}

	session->send(daResponse, correlationId, 0x01 | 0x02);
}
