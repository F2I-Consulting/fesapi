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

#include "common/AbstractHdfProxy.h"

void MyOwnDataArrayProtocolHandlers::on_GetDataArray(const Energistics::Etp::v12::Protocol::DataArray::GetDataArray & gda, int64_t correlationId)
{
	std::cout << "Data array received uri : " << gda.m_uri << std::endl;

	COMMON_NS::EpcDocument epcDoc(MyOwnEtpServerSession::epcFileName, COMMON_NS::EpcDocument::READ_ONLY);
	std::string resqmlResult = epcDoc.deserialize();

	COMMON_NS::AbstractObject* obj = Helpers::getObjectFromUri(epcDoc, session, gda.m_uri);
	if (obj == nullptr) {
		epcDoc.close();
		return;
	}

	COMMON_NS::AbstractHdfProxy* hdfProxy = dynamic_cast<COMMON_NS::AbstractHdfProxy*>(obj);
	if (hdfProxy == nullptr) {
		Energistics::Etp::v12::Protocol::Core::ProtocolException error;
		error.m_errorCode = 11;
		error.m_errorMessage = obj->getUuid() + " cannot be resolved as an HDF Proxy in this store";

		session->send(error);
		epcDoc.close();
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
	epcDoc.close();
}

void MyOwnDataArrayProtocolHandlers::on_PutDataArray(const Energistics::Etp::v12::Protocol::DataArray::PutDataArray & pda, int64_t correlationId)
{
	std::cout << "on_PutDataArray : DO ALMOST NOTHING FOR NOW" << std::endl;

	std::cout << "PutDataArray in resource " << pda.m_uri << " at path " << pda.m_pathInResource << std::endl;;
	for (auto i = 0; i < pda.m_dimensions.size(); ++i) {
		std::cout << "Dimension " << i << " with count : " << pda.m_dimensions[i] << std::endl;
	}

	COMMON_NS::EpcDocument epcDoc(MyOwnEtpServerSession::epcFileName, COMMON_NS::EpcDocument::READ_ONLY);
	std::string resqmlResult = epcDoc.deserialize();

	COMMON_NS::AbstractObject* obj = Helpers::getObjectFromUri(epcDoc, session, pda.m_uri);
	if (obj == nullptr) {
		epcDoc.close();
		return;
	}

	COMMON_NS::AbstractHdfProxy* hdfProxy = dynamic_cast<COMMON_NS::AbstractHdfProxy*>(obj);
	if (hdfProxy == nullptr) {
		Energistics::Etp::v12::Protocol::Core::ProtocolException error;
		error.m_errorCode = 11;
		error.m_errorMessage = obj->getUuid() + " cannot be resolved as an HDF Proxy in this store";

		session->send(error);
		epcDoc.close();
		return;
	}

	auto hdfGroups = tokenize(pda.m_pathInResource, '/');

	if (hdfGroups.size() != 3) {
		std::cout << "This server does not support putting a data array in a path which does not follow /RESQML/groupname/datasetname convention." << std::endl;
		epcDoc.close();
		return;
	}
	if (hdfGroups[0] != "RESQML") {
		std::cout << "This server does not support putting a data array in another root group than RESQML group." << std::endl;
		epcDoc.close();
		return;
	}
	/*
	std::unique_ptr<unsigned long long[]> numValuesInEachDimension(new unsigned long long[pda.m_dimensions.size()]());
	hdfProxy->writeArrayNd(hdfGroups[1], hdfGroups[2], , , numValuesInEachDimension.get(), pda.m_dimensions.size());
	*/
	epcDoc.close();
}

void MyOwnDataArrayProtocolHandlers::on_DescribeDataArray(const Energistics::Etp::v12::Protocol::DataArray::DescribeDataArray & dda, int64_t correlationId)
{
	std::cout << "Describe Data array received uri : " << dda.m_uri << std::endl;

	COMMON_NS::EpcDocument epcDoc(MyOwnEtpServerSession::epcFileName, COMMON_NS::EpcDocument::READ_ONLY);
	std::string resqmlResult = epcDoc.deserialize();

	COMMON_NS::AbstractObject* obj = Helpers::getObjectFromUri(epcDoc, session, dda.m_uri);
	if (obj == nullptr) {
		epcDoc.close();
		return;
	}

	COMMON_NS::AbstractHdfProxy* hdfProxy = dynamic_cast<COMMON_NS::AbstractHdfProxy*>(obj);
	if (hdfProxy == nullptr) {
		Energistics::Etp::v12::Protocol::Core::ProtocolException error;
		error.m_errorCode = 11;
		error.m_errorMessage = obj->getUuid() + " cannot be resolved as an HDF Proxy in this store";

		session->send(error);
		epcDoc.close();
		return;
	}

	std::cout << "Received pathInResource : " << dda.m_pathInResource << std::endl;
	Energistics::Etp::v12::Protocol::DataArray::DataArrayMetadata dam;
	auto elemCountPerDim = hdfProxy->getElementCountPerDimension(dda.m_pathInResource);
	dam.m_dimensions.reserve(elemCountPerDim.size());
	unsigned long long globalElemCount = 1;
	for (auto i = 0; i < elemCountPerDim.size(); ++i) {
		dam.m_dimensions.push_back(elemCountPerDim[i]);
		globalElemCount *= elemCountPerDim[i];
	}

	auto dt = hdfProxy->getHdfDatatypeInDataset(dda.m_pathInResource);
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

	session->send(dam, correlationId);
	epcDoc.close();
}
