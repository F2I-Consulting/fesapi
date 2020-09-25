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

#include "etp/AbstractSession.h"
#include "etp/EtpException.h"

#include "eml2/AbstractHdfProxy.h"

#include "MyDataObjectRepository.h"

void MyOwnDataArrayProtocolHandlers::on_GetDataArrays(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrays & gda, int64_t correlationId)
{
	Energistics::Etp::v12::Protocol::DataArray::GetDataArraysResponse gdaResponse;

	Energistics::Etp::v12::Protocol::Core::ProtocolException pe;
	for (std::pair < std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier > element : gda.dataArrays) {
		Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier& dai = element.second;
		std::cout << "Data array received uri : " << dai.uri << std::endl;

		try
		{
			COMMON_NS::AbstractObject* obj = repo->getObjectFromUri(dai.uri);
			EML2_NS::AbstractHdfProxy* hdfProxy = dynamic_cast<EML2_NS::AbstractHdfProxy*>(obj);
			if (hdfProxy == nullptr) {
				pe.errors[element.first].message = "The URI points to an object which is not an HDF proxy";
				pe.errors[element.first].code = 9;
				continue;
			}

			std::cout << "Received pathInResource : " << dai.pathInResource << std::endl;
			auto elemCountPerDim = hdfProxy->getElementCountPerDimension(dai.pathInResource);
			Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray da;
			da.dimensions.reserve(elemCountPerDim.size());
			size_t globalElemCount = 1;
			for (size_t i = 0; i < elemCountPerDim.size(); ++i) {
				da.dimensions.push_back(elemCountPerDim[i]);
				globalElemCount *= elemCountPerDim[i];
			}

			auto dt = hdfProxy->getHdfDatatypeInDataset(dai.pathInResource);
			if (dt == COMMON_NS::AbstractObject::DOUBLE)
			{
				Energistics::Etp::v12::Datatypes::ArrayOfDouble avroArray;
				avroArray.values = std::vector<double>(globalElemCount);
				hdfProxy->readArrayNdOfDoubleValues(dai.pathInResource, avroArray.values.data());
				da.data.item.set_ArrayOfDouble(avroArray);
			}
			else if (dt == COMMON_NS::AbstractObject::FLOAT)
			{
				Energistics::Etp::v12::Datatypes::ArrayOfFloat avroArray;
				avroArray.values = std::vector<float>(globalElemCount);
				hdfProxy->readArrayNdOfFloatValues(dai.pathInResource, avroArray.values.data());
				da.data.item.set_ArrayOfFloat(avroArray);
			}
			else if (dt == COMMON_NS::AbstractObject::LONG_64 || dt == COMMON_NS::AbstractObject::ULONG_64)
			{
				Energistics::Etp::v12::Datatypes::ArrayOfLong avroArray;
				avroArray.values = std::vector<LONG64>(globalElemCount);
				hdfProxy->readArrayNdOfLongValues(dai.pathInResource, avroArray.values.data());
				da.data.item.set_ArrayOfLong(avroArray);
			}
			else if (dt == COMMON_NS::AbstractObject::INT || dt == COMMON_NS::AbstractObject::UINT ||
				dt == COMMON_NS::AbstractObject::SHORT || dt == COMMON_NS::AbstractObject::USHORT)
			{
				Energistics::Etp::v12::Datatypes::ArrayOfInt avroArray;
				avroArray.values = std::vector<int>(globalElemCount);
				hdfProxy->readArrayNdOfIntValues(dai.pathInResource, avroArray.values.data());
				da.data.item.set_ArrayOfInt(avroArray);
			}
			else if (dt == COMMON_NS::AbstractObject::CHAR || dt == COMMON_NS::AbstractObject::UCHAR)
			{
				std::string avroArray(globalElemCount, '\0');
				hdfProxy->readArrayNdOfCharValues(dai.pathInResource, &avroArray[0]);
				da.data.item.set_bytes(avroArray);
			}

			gdaResponse.dataArrays[element.first] = da;
		}
		catch (ETP_NS::EtpException& ex)
		{
			pe.errors[element.first].message = ex.what();
			pe.errors[element.first].code = ex.getErrorCode();
			continue;
		}		
	}

	if (!pe.errors.empty()) {
		session->send(gdaResponse, correlationId, 0x01);
		session->send(pe, correlationId, 0x01 | 0x02);
	}
	else {
		session->send(gdaResponse, correlationId, 0x01 | 0x02);
	}
}

void MyOwnDataArrayProtocolHandlers::on_PutDataArrays(const Energistics::Etp::v12::Protocol::DataArray::PutDataArrays & pda, int64_t correlationId)
{
	std::cout << "on_PutDataArray : DO ALMOST NOTHING FOR NOW" << std::endl;

	Energistics::Etp::v12::Protocol::Core::ProtocolException pe;
	for (std::pair < std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataArraysType > pdat : pda.dataArrays) {
		std::cout << "PutDataArray in resource " << pdat.second.uid.uri << " at path " << pdat.second.uid.pathInResource << std::endl;;
		for (size_t i = 0; i < pdat.second.array.dimensions.size(); ++i) {
			std::cout << "Dimension " << i << " with count : " << pdat.second.array.dimensions[i] << std::endl;
		}

		try {
			COMMON_NS::AbstractObject* obj = repo->getObjectFromUri(pdat.second.uid.uri);
			EML2_NS::AbstractHdfProxy* hdfProxy = dynamic_cast<EML2_NS::AbstractHdfProxy*>(obj);
			if (hdfProxy == nullptr) {
				pe.errors[pdat.first].message = obj->getUuid() + " cannot be resolved as an HDF Proxy in this store";
				pe.errors[pdat.first].code = 11;
				continue;
			}

			auto hdfGroups = tokenize(pdat.second.uid.pathInResource, '/');

			if (hdfGroups.size() != 3) {
				std::cout << "This server does not support putting a data array in a path which does not follow /RESQML/groupname/datasetname convention." << std::endl;
				continue;
			}
			if (hdfGroups[0] != "RESQML") {
				std::cout << "This server does not support putting a data array in another root group than RESQML group." << std::endl;
				continue;
			}
			/*
			std::unique_ptr<unsigned long long[]> numValuesInEachDimension(new unsigned long long[pda.dimensions.size()]());
			hdfProxy->writeArrayNd(hdfGroups[1], hdfGroups[2], , , numValuesInEachDimension.get(), pda.dimensions.size());
			*/
		}
		catch (ETP_NS::EtpException& ex)
		{
			pe.errors[pdat.first].message = ex.what();
			pe.errors[pdat.first].code = ex.getErrorCode();
			continue;
		}
	}

	if (!pe.errors.empty()) {
		session->send(pe, correlationId, 0x01 | 0x02);
	}
}

void MyOwnDataArrayProtocolHandlers::on_GetDataArrayMetadata(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadata & gdam, int64_t correlationId)
{
	Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadataResponse gdamResponse;

	Energistics::Etp::v12::Protocol::Core::ProtocolException pe;
	for (std::pair < std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier > element : gdam.dataArrays) {
		Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier& dai = element.second;
		std::cout << "GetDataArrayMetadata received uri : " << dai.uri << std::endl;

		try {
			COMMON_NS::AbstractObject* obj = repo->getObjectFromUri(dai.uri);
			EML2_NS::AbstractHdfProxy* hdfProxy = dynamic_cast<EML2_NS::AbstractHdfProxy*>(obj);
			if (hdfProxy == nullptr) {
				pe.errors[element.first].message = "The URI points to an object which is not an HDF proxy";
				pe.errors[element.first].code = 9;
				continue;
			}

			std::cout << "Received pathInResource : " << dai.pathInResource << std::endl;
			Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayMetadata dam;
			auto elemCountPerDim = hdfProxy->getElementCountPerDimension(dai.pathInResource);
			dam.dimensions.reserve(elemCountPerDim.size());
			unsigned long long globalElemCount = 1;
			for (auto i = 0; i < elemCountPerDim.size(); ++i) {
				dam.dimensions.push_back(elemCountPerDim[i]);
				globalElemCount *= elemCountPerDim[i];
			}

			auto dt = hdfProxy->getHdfDatatypeInDataset(dai.pathInResource);
			if (dt == COMMON_NS::AbstractObject::DOUBLE)
			{
				dam.arrayType = Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfDouble;
			}
			else if (dt == COMMON_NS::AbstractObject::FLOAT)
			{
				dam.arrayType = Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfFloat;
			}
			else if (dt == COMMON_NS::AbstractObject::LONG_64 || dt == COMMON_NS::AbstractObject::ULONG_64)
			{
				dam.arrayType = Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfLong;
			}
			else if (dt == COMMON_NS::AbstractObject::INT || dt == COMMON_NS::AbstractObject::UINT ||
				dt == COMMON_NS::AbstractObject::SHORT || dt == COMMON_NS::AbstractObject::USHORT)
			{
				dam.arrayType = Energistics::Etp::v12::Datatypes::AnyArrayType::arrayOfInt;
			}
			else if (dt == COMMON_NS::AbstractObject::CHAR || dt == COMMON_NS::AbstractObject::UCHAR)
			{
				dam.arrayType = Energistics::Etp::v12::Datatypes::AnyArrayType::bytes;
			}
			gdamResponse.arrayMetadata[element.first] = dam;
		}
		catch (ETP_NS::EtpException& ex)
		{
			pe.errors[element.first].message = ex.what();
			pe.errors[element.first].code = ex.getErrorCode();
			continue;
		}
	}

	if (!pe.errors.empty()) {
		session->send(gdamResponse, correlationId, 0x01);
		session->send(pe, correlationId, 0x01 | 0x02);
	}
	else {
		session->send(gdamResponse, correlationId, 0x01 | 0x02);
	}
}
