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

#include "Helpers.h"

#include "etp/AbstractSession.h"

#include "common/AbstractHdfProxy.h"

void MyOwnDataArrayProtocolHandlers::on_GetDataArrays(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrays & gda, int64_t correlationId)
{
	Energistics::Etp::v12::Protocol::DataArray::GetDataArraysResponse gdaResponse;

	for (std::pair < std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier > element : gda.m_dataArrays) {
		Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier& dai = element.second;
		std::cout << "Data array received uri : " << dai.m_uri << std::endl;

		COMMON_NS::AbstractObject* obj = Helpers::getObjectFromUri(repo, session, dai.m_uri);
		if (obj == nullptr) {
			gdaResponse.m_errors[element.first].m_message = "The URI cannot be resolved to an object in the store";
			gdaResponse.m_errors[element.first].m_code = 9;
			continue;
		}

		COMMON_NS::AbstractHdfProxy* hdfProxy = dynamic_cast<COMMON_NS::AbstractHdfProxy*>(obj);
		if (hdfProxy == nullptr) {
			gdaResponse.m_errors[element.first].m_message = "The URI points to an object which is not an HDF proxy";
			gdaResponse.m_errors[element.first].m_code = 9;
			continue;
		}

		std::cout << "Received pathInResource : " << dai.m_pathInResource << std::endl;
		auto elemCountPerDim = hdfProxy->getElementCountPerDimension(dai.m_pathInResource);
		Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray da;
		da.m_dimensions.reserve(elemCountPerDim.size());
		unsigned long long globalElemCount = 1;
		for (size_t i = 0; i < elemCountPerDim.size(); ++i) {
			da.m_dimensions.push_back(elemCountPerDim[i]);
			globalElemCount *= elemCountPerDim[i];
		}

		auto dt = hdfProxy->getHdfDatatypeInDataset(dai.m_pathInResource);
		if (dt == COMMON_NS::AbstractObject::DOUBLE)
		{
			double* hdfValues = new double[globalElemCount];
			hdfProxy->readArrayNdOfDoubleValues(dai.m_pathInResource, hdfValues);
			Energistics::Etp::v12::Datatypes::ArrayOfDouble avroArray;
			avroArray.m_values.assign(hdfValues, hdfValues + globalElemCount);
			delete[] hdfValues;
			da.m_data.m_item.set_ArrayOfDouble(avroArray);
		}
		else if (dt == COMMON_NS::AbstractObject::FLOAT)
		{
			float* hdfValues = new float[globalElemCount];
			hdfProxy->readArrayNdOfFloatValues(dai.m_pathInResource, hdfValues);
			Energistics::Etp::v12::Datatypes::ArrayOfFloat avroArray;
			avroArray.m_values.assign(hdfValues, hdfValues + globalElemCount);
			delete[] hdfValues;
			da.m_data.m_item.set_ArrayOfFloat(avroArray);
		}
		else if (dt == COMMON_NS::AbstractObject::LONG)
		{
			LONG64* hdfValues = new LONG64[globalElemCount];
			hdfProxy->readArrayNdOfGSoapLong64Values(dai.m_pathInResource, hdfValues);
			Energistics::Etp::v12::Datatypes::ArrayOfLong avroArray;
			avroArray.m_values.assign(hdfValues, hdfValues + globalElemCount);
			delete[] hdfValues;
			da.m_data.m_item.set_ArrayOfLong(avroArray);
		}
		else if (dt == COMMON_NS::AbstractObject::ULONG)
		{
			ULONG64* hdfValues = new ULONG64[globalElemCount];
			hdfProxy->readArrayNdOfGSoapULong64Values(dai.m_pathInResource, hdfValues);
			Energistics::Etp::v12::Datatypes::ArrayOfLong avroArray;
			avroArray.m_values.assign(hdfValues, hdfValues + globalElemCount);
			delete[] hdfValues;
			da.m_data.m_item.set_ArrayOfLong(avroArray);
		}
		else if (dt == COMMON_NS::AbstractObject::INT)
		{
			int* hdfValues = new int[globalElemCount];
			hdfProxy->readArrayNdOfIntValues(dai.m_pathInResource, hdfValues);
			Energistics::Etp::v12::Datatypes::ArrayOfInt avroArray;
			avroArray.m_values.assign(hdfValues, hdfValues + globalElemCount);
			delete[] hdfValues;
			da.m_data.m_item.set_ArrayOfInt(avroArray);
		}
		else if (dt == COMMON_NS::AbstractObject::UINT)
		{
			unsigned int* hdfValues = new unsigned int[globalElemCount];
			hdfProxy->readArrayNdOfUIntValues(dai.m_pathInResource, hdfValues);
			Energistics::Etp::v12::Datatypes::ArrayOfInt avroArray;
			avroArray.m_values.assign(hdfValues, hdfValues + globalElemCount);
			delete[] hdfValues;
			da.m_data.m_item.set_ArrayOfInt(avroArray);
		}
		else if (dt == COMMON_NS::AbstractObject::SHORT)
		{
			short* hdfValues = new short[globalElemCount];
			hdfProxy->readArrayNdOfShortValues(dai.m_pathInResource, hdfValues);
			Energistics::Etp::v12::Datatypes::ArrayOfInt avroArray;
			avroArray.m_values.assign(hdfValues, hdfValues + globalElemCount);
			delete[] hdfValues;
			da.m_data.m_item.set_ArrayOfInt(avroArray);
		}
		else if (dt == COMMON_NS::AbstractObject::USHORT)
		{
			unsigned short* hdfValues = new unsigned short[globalElemCount];
			hdfProxy->readArrayNdOfUShortValues(dai.m_pathInResource, hdfValues);
			Energistics::Etp::v12::Datatypes::ArrayOfInt avroArray;
			avroArray.m_values.assign(hdfValues, hdfValues + globalElemCount);
			delete[] hdfValues;
			da.m_data.m_item.set_ArrayOfInt(avroArray);
		}
		else if (dt == COMMON_NS::AbstractObject::CHAR)
		{
			char* hdfValues = new char[globalElemCount];
			hdfProxy->readArrayNdOfCharValues(dai.m_pathInResource, hdfValues);
			std::string avroArray;
			avroArray.assign(hdfValues, hdfValues + globalElemCount);
			delete[] hdfValues;
			da.m_data.m_item.set_bytes(avroArray);
		}
		else if (dt == COMMON_NS::AbstractObject::UCHAR)
		{
			unsigned char* hdfValues = new unsigned char[globalElemCount];
			hdfProxy->readArrayNdOfUCharValues(dai.m_pathInResource, hdfValues);
			std::string avroArray;
			avroArray.assign(hdfValues, hdfValues + globalElemCount);
			delete[] hdfValues;
			da.m_data.m_item.set_bytes(avroArray);
		}
		gdaResponse.m_dataArrays[element.first] = da;
	}
	session->send(gdaResponse, correlationId, 0x01 | 0x02);
}

void MyOwnDataArrayProtocolHandlers::on_PutDataArrays(const Energistics::Etp::v12::Protocol::DataArray::PutDataArrays & pda, int64_t correlationId)
{
	std::cout << "on_PutDataArray : DO ALMOST NOTHING FOR NOW" << std::endl;

	for (Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataArraysType pdat : pda.m_dataArrays) {
		std::cout << "PutDataArray in resource " << pdat.m_uri << " at path " << pdat.m_pathInResource << std::endl;;
		for (auto i = 0; i < pdat.m_dimensions.size(); ++i) {
			std::cout << "Dimension " << i << " with count : " << pdat.m_dimensions[i] << std::endl;
		}

		COMMON_NS::AbstractObject* obj = Helpers::getObjectFromUri(repo, session, pdat.m_uri);
		if (obj == nullptr) {
			continue;
		}

		COMMON_NS::AbstractHdfProxy* hdfProxy = dynamic_cast<COMMON_NS::AbstractHdfProxy*>(obj);
		if (hdfProxy == nullptr) {
			Energistics::Etp::v12::Protocol::Core::ProtocolException error;
			error.m_errorCode = 11;
			error.m_errorMessage = obj->getUuid() + " cannot be resolved as an HDF Proxy in this store";

			session->send(error);
			return;
		}

		auto hdfGroups = tokenize(pdat.m_pathInResource, '/');

		if (hdfGroups.size() != 3) {
			std::cout << "This server does not support putting a data array in a path which does not follow /RESQML/groupname/datasetname convention." << std::endl;
			continue;
		}
		if (hdfGroups[0] != "RESQML") {
			std::cout << "This server does not support putting a data array in another root group than RESQML group." << std::endl;
			continue;
		}
		/*
		std::unique_ptr<unsigned long long[]> numValuesInEachDimension(new unsigned long long[pda.m_dimensions.size()]());
		hdfProxy->writeArrayNd(hdfGroups[1], hdfGroups[2], , , numValuesInEachDimension.get(), pda.m_dimensions.size());
		*/
	}
}

void MyOwnDataArrayProtocolHandlers::on_GetDataArrayMetadata(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadata & gdam, int64_t correlationId)
{
	Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadataResponse gdamResponse;

	for (std::pair < std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier > element : gdam.m_dataArrays) {
		Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier& dai = element.second;
		std::cout << "GetDataArrayMetadata received uri : " << dai.m_uri << std::endl;

		COMMON_NS::AbstractObject* obj = Helpers::getObjectFromUri(repo, session, dai.m_uri);
		if (obj == nullptr) {
			gdamResponse.m_errors[element.first].m_message = "The URI cannot be resolved to an object in the store";
			gdamResponse.m_errors[element.first].m_code = 9;
			continue;
		}

		COMMON_NS::AbstractHdfProxy* hdfProxy = dynamic_cast<COMMON_NS::AbstractHdfProxy*>(obj);
		if (hdfProxy == nullptr) {
			gdamResponse.m_errors[element.first].m_message = "The URI points to an object which is not an HDF proxy";
			gdamResponse.m_errors[element.first].m_code = 9;
			continue;
		}

		std::cout << "Received pathInResource : " << dai.m_pathInResource << std::endl;
		Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayMetadata dam;
		auto elemCountPerDim = hdfProxy->getElementCountPerDimension(dai.m_pathInResource);
		dam.m_dimensions.reserve(elemCountPerDim.size());
		unsigned long long globalElemCount = 1;
		for (auto i = 0; i < elemCountPerDim.size(); ++i) {
			dam.m_dimensions.push_back(elemCountPerDim[i]);
			globalElemCount *= elemCountPerDim[i];
		}

		auto dt = hdfProxy->getHdfDatatypeInDataset(dai.m_pathInResource);
		if (dt == COMMON_NS::AbstractObject::DOUBLE)
		{
			dam.m_arrayType = Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfDouble;
		}
		else if (dt == COMMON_NS::AbstractObject::FLOAT)
		{
			dam.m_arrayType = Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfFloat;
		}
		else if (dt == COMMON_NS::AbstractObject::LONG || dt == COMMON_NS::AbstractObject::ULONG)
		{
			dam.m_arrayType = Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfLong;
		}
		else if (dt == COMMON_NS::AbstractObject::INT || dt == COMMON_NS::AbstractObject::UINT ||
			dt == COMMON_NS::AbstractObject::SHORT || dt == COMMON_NS::AbstractObject::USHORT)
		{
			dam.m_arrayType = Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfInt;
		}
		else if (dt == COMMON_NS::AbstractObject::CHAR || dt == COMMON_NS::AbstractObject::UCHAR)
		{
			dam.m_arrayType = Energistics::Etp::v12::Datatypes::AnyArrayType::bytes;
		}
		gdamResponse.m_arrayMetadata[element.first] = dam;
	}

	session->send(gdamResponse, correlationId);
}
