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
#include "EtpHdfProxy.h"

#include <stdexcept>

#include <hdf5.h>

using namespace ETP_NS;
using namespace std;

const char* EtpHdfProxy::XML_NS = "eml20";

std::string EtpHdfProxy::getUri() const
{
	return "eml:///eml20.obj_EpcExternalPartReference(" + getUuid() + ")";
}

void EtpHdfProxy::setSession(boost::asio::io_context& ioc, const std::string & host, const std::string & port, const std::string & target)
{
	session = std::make_shared<DataArrayBlockingSession>(ioc, host, port, target);
}

void EtpHdfProxy::open()
{
	if (session == nullptr) {
		throw invalid_argument("You first need to set a session associated to this ETP hdf proxy");
	}
	session->run();
}

COMMON_NS::AbstractObject::hdfDatatypeEnum EtpHdfProxy::getHdfDatatypeInDataset(const std::string & datasetName)
{
	throw logic_error("Not implemented yet");
}

int EtpHdfProxy::getHdfDatatypeClassInDataset(const std::string & datasetName)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::writeItemizedListOfList(const string & groupName, const std::string & name,
	hid_t cumulativeLengthDatatype,
	const void * cumulativeLength,
	unsigned long long cumulativeLengthSize,
	hid_t elementsDatatype,
	const void * elements,
	unsigned long long elementsSize)
{
	throw logic_error("Not implemented yet");
}

unsigned int EtpHdfProxy::getDimensionCount(const std::string & datasetName)
{
	throw logic_error("Not implemented yet");
}

std::vector<unsigned long long> EtpHdfProxy::getElementCountPerDimension(const std::string & datasetName)
{
	throw logic_error("Not implemented yet");
}

signed long long EtpHdfProxy::getElementCount(const std::string & datasetName)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::writeArrayNdOfFloatValues(const string & groupName,
	const string & name,
	const float * floatValues,
	const unsigned long long * numValuesInEachDimension,
	unsigned int numDimensions)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::writeArrayNdOfDoubleValues(const string & groupName,
	const string & name,
	const double * dblValues,
	const unsigned long long * numValuesInEachDimension,
	unsigned int numDimensions)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::writeArrayNdOfCharValues(const std::string & groupName,
	const std::string & name,
	const char * intValues,
	const unsigned long long * numValuesInEachDimension,
	unsigned int numDimensions)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::writeArrayNdOfIntValues(const string & groupName,
	const string & name,
	const int * intValues,
	const unsigned long long * numValuesInEachDimension,
	unsigned int numDimensions)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::writeArrayNdOfGSoapULong64Values(const std::string & groupName,
	const std::string & name,
	const ULONG64 * ulong64Values,
	const unsigned long long * numValuesInEachDimension,
	unsigned int numDimensions)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::writeArrayNd(const std::string & groupName,
	const std::string & name,
	hid_t datatype,
	const void * values,
	const unsigned long long * numValuesInEachDimension,
	unsigned int numDimensions)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::createArrayNd(
	const std::string& groupName,
	const std::string& datasetName,
	hid_t datatype,
	const unsigned long long* numValuesInEachDimension,
	unsigned int numDimensions)
{
	throw logic_error("Not implemented yet");
}


void EtpHdfProxy::writeArrayNdSlab(
	const string& groupName,
	const string& datasetName,
	hid_t datatype,
	const void* values,
	const unsigned long long* numValuesInEachDimension,
	const unsigned long long* offsetInEachDimension,
	unsigned int numDimensions)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::readArrayNdOfDoubleValues(const std::string & datasetName, double* values)
{
	if (!isOpened()) {
		open();
	}

	session->readArrayValues<double>(getUri(), datasetName, values);
}

void EtpHdfProxy::readArrayNdOfDoubleValues(
	const std::string & datasetName, double* values,
	unsigned long long const * numValuesInEachDimension,
	unsigned long long const * offsetInEachDimension,
	unsigned int numDimensions)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::readArrayNdOfDoubleValues(
	const std::string & datasetName, double* values,
	unsigned long long const * blockCountPerDimension,
	unsigned long long const * offsetInEachDimension,
	unsigned long long const * strideInEachDimension,
	unsigned long long const * blockSizeInEachDimension,
	unsigned int numDimensions)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::selectArrayNdOfValues(
	const std::string & datasetName,
	unsigned long long const * blockCountPerDimension,
	unsigned long long const * offsetInEachDimension,
	unsigned long long const * strideInEachDimension,
	unsigned long long const * blockSizeInEachDimension,
	unsigned int numDimensions,
	bool newSelection,
	hid_t & dataset,
	hid_t & filespace)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::readArrayNdOfDoubleValues(
	hid_t dataset,
	hid_t filespace,
	void* values,
	unsigned long long slabSize)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::readArrayNdOfFloatValues(const std::string & datasetName, float* values)
{
	if (!isOpened()) {
		open();
	}

	session->readArrayValues<float>(getUri(), datasetName, values);
}

void EtpHdfProxy::readArrayNdOfFloatValues(
	const std::string& datasetName, float* values,
	unsigned long long const * numValuesInEachDimension,
	unsigned long long const * offsetInEachDimension,
	unsigned int numDimensions)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::readArrayNdOfLongValues(const std::string & datasetName, LONG64* values)
{
	if (!isOpened()) {
		open();
	}

	session->readArrayValues<LONG64>(getUri(), datasetName, values);
}

void EtpHdfProxy::readArrayNdOfLongValues(
	const std::string& datasetName, LONG64* values,
	unsigned long long const * numValuesInEachDimension,
	unsigned long long const * offsetInEachDimension,
	unsigned int numDimensions)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::readArrayNdOfULongValues(const std::string & datasetName, ULONG64* values)
{
	if (!isOpened()) {
		open();
	}

	session->readArrayValues<ULONG64>(getUri(), datasetName, values);
}

void EtpHdfProxy::readArrayNdOfIntValues(const std::string & datasetName, int* values)
{
	if (!isOpened()) {
		open();
	}

	session->readArrayValues<int>(getUri(), datasetName, values);
}

void EtpHdfProxy::readArrayNdOfIntValues(
	const std::string& datasetName, int* values,
	unsigned long long const * numValuesInEachDimension,
	unsigned long long const * offsetInEachDimension,
	unsigned int numDimensions)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::readArrayNdOfUIntValues(const std::string & datasetName, unsigned int* values)
{
	if (!isOpened()) {
		open();
	}

	session->readArrayValues<unsigned int>(getUri(), datasetName, values);
}

 void EtpHdfProxy::readArrayNdOfShortValues(const std::string & datasetName, short* values)
{
	 if (!isOpened()) {
		 open();
	 }

	 session->readArrayValues<short>(getUri(), datasetName, values);
}

void EtpHdfProxy::readArrayNdOfUShortValues(const std::string & datasetName, unsigned short* values)
{
	if (!isOpened()) {
		open();
	}

	session->readArrayValues<unsigned short>(getUri(), datasetName, values);
}

void EtpHdfProxy::readArrayNdOfCharValues(const std::string & datasetName, char* values)
{
	if (!isOpened()) {
		open();
	}

	session->readArrayValues<char>(getUri(), datasetName, values);
}

void EtpHdfProxy::readArrayNdOfUCharValues(const std::string & datasetName, unsigned char* values)
{
	if (!isOpened()) {
		open();
	}

	session->readArrayValues<unsigned char>(getUri(), datasetName, values);
}

std::vector<unsigned long long> EtpHdfProxy::readArrayDimensions(const std::string & datasetName)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::writeGroupAttributes(const std::string & groupName,
	const std::vector<std::string> & attributeNames,
	const std::vector<std::string> & values)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::writeGroupAttribute(const std::string & groupName,
	const std::string & attributeName,
	const std::vector<std::string> & values)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::writeGroupAttributes(const std::string & groupName,
	const std::vector<std::string> & attributeNames,
	const std::vector<double> & values)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::writeGroupAttributes(const std::string & groupName,
	const std::vector<std::string> & attributeNames,
	const std::vector<int> & values)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::writeDatasetAttributes(const std::string & datasetName,
	const std::vector<std::string> & attributeNames,
	const std::vector<std::string> & values)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::writeDatasetAttribute(const std::string & datasetName,
	const std::string & attributeName,
	const std::vector<std::string> & values)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::writeDatasetAttributes(const std::string & datasetName,
	const std::vector<std::string> & attributeNames,
	const std::vector<double> & values)
{
	throw logic_error("Not implemented yet");
}

void EtpHdfProxy::writeDatasetAttributes(const std::string & datasetName,
	const std::vector<std::string> & attributeNames,
	const std::vector<int> & values)
{
	throw logic_error("Not implemented yet");
}

std::string EtpHdfProxy::readStringAttribute(const std::string & obj_name,
	const std::string & attr_name) const
{
	throw logic_error("Not implemented yet");
}

vector<string> EtpHdfProxy::readStringArrayAttribute(const std::string & obj_name,
	const std::string & attr_name) const
{
	throw logic_error("Not implemented yet");
}

double EtpHdfProxy::readDoubleAttribute(const std::string & obj_name,
	const std::string & attr_name) const
{
	throw logic_error("Not implemented yet");
}

LONG64 EtpHdfProxy::readLongAttribute(const std::string & obj_name,
	const std::string & attr_name) const
{
	throw logic_error("Not implemented yet");
}

bool EtpHdfProxy::exist(const std::string & absolutePathInHdfFile) const
{
	throw logic_error("Not implemented yet");
}

bool EtpHdfProxy::isCompressed(const std::string & datasetName)
{
	throw logic_error("Not implemented yet");
}
