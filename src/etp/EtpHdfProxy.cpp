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

using namespace ETP_NS;
using namespace std;

void EtpHdfProxy::open()
{
}

void EtpHdfProxy::close()
{
}

void EtpHdfProxy::readArrayNdOfValues(const std::string & datasetName, void* values, const int & datatype)
{
	if (!isOpened()) {
		open();
	}
}

void EtpHdfProxy::readArrayNdOfValues(
	const std::string & datasetName,
	void* values,
	const unsigned long long * numValuesInEachDimension,
	const unsigned long long * offsetInEachDimension,
	const unsigned int & numDimensions, const int & datatype)
{
}

void EtpHdfProxy::readArrayNdOfValues(
	const std::string & datasetName,
	void* values,
	const unsigned long long * blockCountPerDimension,
	const unsigned long long * offsetInEachDimension,
	const unsigned long long * strideInEachDimension,
	const unsigned long long * blockSizeInEachDimension,
	const unsigned int & numDimensions, const int & datatype)
{
}

void EtpHdfProxy::selectArrayNdOfValues(
	const std::string & datasetName,
	const unsigned long long * blockCountPerDimension,
	const unsigned long long * offsetInEachDimension,
	const unsigned long long * strideInEachDimension,
	const unsigned long long * blockSizeInEachDimension,
	const unsigned int & numDimensions,
	bool newSelection,
	int & dataset,
	int & filespace)
{

}

void EtpHdfProxy::readArrayNdOfValues(
	int dataset,
	int filespace,
	void* values, 
	unsigned long long slabSize, 
	const int & datatype)
{

}

COMMON_NS::AbstractObject::hdfDatatypeEnum EtpHdfProxy::getHdfDatatypeInDataset(const std::string & datasetName) const
{
 return COMMON_NS::AbstractObject::hdfDatatypeEnum::UNKNOWN;
}

int EtpHdfProxy::getHdfDatatypeClassInDataset(const std::string & datasetName) const
{
	return -1;
}

void EtpHdfProxy::writeItemizedListOfList(const string & groupName,
			const string & name,
			const int & cumulativeLengthDatatype,
			const void * cumulativeLength,
			const unsigned long long & cumulativeLengthSize,
			const int & elementsDatatype,
			const void * elements,
			const unsigned long long & elementsSize)
{

}

unsigned int EtpHdfProxy::getDimensionCount(const std::string & datasetName)
{
	return 0;
}

std::vector<unsigned long long> EtpHdfProxy::getElementCountPerDimension(const std::string & datasetName)
{
	std::vector<unsigned long long> result;
	return result;
}

signed long long EtpHdfProxy::getElementCount(const std::string & datasetName)
{
	return 0;
}

void EtpHdfProxy::writeArrayNdOfFloatValues(const string & groupName,
	const string & name,
	const float * floatValues,
	const unsigned long long * numValuesInEachDimension,
	const unsigned int & numDimensions)
{

}

void EtpHdfProxy::writeArrayNdOfDoubleValues(const string & groupName,
	const string & name,
	const double * dblValues,
	const unsigned long long * numValuesInEachDimension,
	const unsigned int & numDimensions)
{

}

void EtpHdfProxy::writeArrayNdOfCharValues(const std::string & groupName,
	const std::string & name,
	const char * intValues,
	const unsigned long long * numValuesInEachDimension,
	const unsigned int & numDimensions)
{

}

void EtpHdfProxy::writeArrayNdOfIntValues(const string & groupName,
	const string & name,
	const int * intValues,
	const unsigned long long * numValuesInEachDimension,
	const unsigned int & numDimensions)
{
}

void EtpHdfProxy::writeArrayNdOfGSoapULong64Values(const std::string & groupName,
	const std::string & name,
	const ULONG64 * ulong64Values,
	const unsigned long long * numValuesInEachDimension,
	const unsigned int & numDimensions)
{

}

void EtpHdfProxy::writeArrayNd(const std::string & groupName,
	const std::string & name,
	const int & datatype,
	const void * values,
	const unsigned long long * numValuesInEachDimension,
	const unsigned int & numDimensions)
{

}

void EtpHdfProxy::createArrayNd(
	const std::string& groupName,
	const std::string& datasetName,
	const int & datatype,
	const unsigned long long* numValuesInEachDimension,
	const unsigned int& numDimensions)
{

}


void EtpHdfProxy::writeArrayNdSlab(
	const string& groupName,
	const string& datasetName,
	const int & datatype,
	const void* values,
	const unsigned long long* numValuesInEachDimension,
	const unsigned long long* offsetInEachDimension,
	const unsigned int& numDimensions)
{
	
}

void EtpHdfProxy::readArrayNdOfDoubleValues(const std::string & datasetName, double* values)
{

}

void EtpHdfProxy::readArrayNdOfDoubleValues(
	const std::string & datasetName, double* values,
	const unsigned long long * numValuesInEachDimension,
	const unsigned long long * offsetInEachDimension,
	const unsigned int & numDimensions)
{
}

void EtpHdfProxy::readArrayNdOfDoubleValues(
	const std::string & datasetName, double* values,
	const unsigned long long * blockCountPerDimension,
	const unsigned long long * offsetInEachDimension,
	const unsigned long long * strideInEachDimension,
	const unsigned long long * blockSizeInEachDimension,
	const unsigned int & numDimensions)
{

}

void EtpHdfProxy::readArrayNdOfDoubleValues(
	int dataset,
	int filespace,
	void* values,
	unsigned long long slabSize)
{

}

void EtpHdfProxy::readArrayNdOfFloatValues(const std::string & datasetName, float* values)
{

}

void EtpHdfProxy::readArrayNdOfFloatValues(
	const std::string& datasetName, float* values,
	const unsigned long long* numValuesInEachDimension,
	const unsigned long long* offsetInEachDimension,
	const unsigned int& numDimensions)
{

}

void EtpHdfProxy::readArrayNdOfGSoapLong64Values(const std::string & datasetName, LONG64* values)
{

}

void EtpHdfProxy::readArrayNdOfGSoapULong64Values(const std::string & datasetName, ULONG64* values)
{

}

void EtpHdfProxy::readArrayNdOfLongValues(const std::string & datasetName, long* values)
{

}

void EtpHdfProxy::readArrayNdOfLongValues(
	const std::string& datasetName, long* values,
	const unsigned long long* numValuesInEachDimension,
	const unsigned long long* offsetInEachDimension,
	const unsigned int& numDimensions)
{

}

void EtpHdfProxy::readArrayNdOfULongValues(const std::string & datasetName, unsigned long* values)
{

}

void EtpHdfProxy::readArrayNdOfIntValues(const std::string & datasetName, int* values)
{
}

void EtpHdfProxy::readArrayNdOfIntValues(
	const std::string& datasetName, int* values,
	const unsigned long long* numValuesInEachDimension,
	const unsigned long long* offsetInEachDimension,
	const unsigned int& numDimensions)
{
}

void EtpHdfProxy::readArrayNdOfUIntValues(const std::string & datasetName, unsigned int* values)
{

}

 void EtpHdfProxy::readArrayNdOfShortValues(const std::string & datasetName, short* values)
{

}

void EtpHdfProxy::readArrayNdOfUShortValues(const std::string & datasetName, unsigned short* values)
{

}

void EtpHdfProxy::readArrayNdOfCharValues(const std::string & datasetName, char* values)
{

}

void EtpHdfProxy::readArrayNdOfUCharValues(const std::string & datasetName, unsigned char* values)
{

}

int EtpHdfProxy::openOrCreateRootGroup()
{
 return -1;
}

int EtpHdfProxy::openOrCreateGroupInRootGroup(const string & groupName)
{
	 return -1;
}

std::vector<unsigned long long> EtpHdfProxy::readArrayDimensions(const std::string & datasetName)
{
	std::vector<unsigned long long> result;
	return result;
}

void EtpHdfProxy::writeGroupAttributes(const std::string & groupName,
	const std::vector<std::string> & attributeNames,
	const std::vector<std::string> & values)
{
}

void EtpHdfProxy::writeGroupAttribute(const std::string & groupName,
	const std::string & attributeName,
	const std::vector<std::string> & values)
{
}

void EtpHdfProxy::writeGroupAttributes(const std::string & groupName,
	const std::vector<std::string> & attributeNames,
	const std::vector<double> & values)
{
}

void EtpHdfProxy::writeGroupAttributes(const std::string & groupName,
	const std::vector<std::string> & attributeNames,
	const std::vector<int> & values)
{
}

void EtpHdfProxy::writeDatasetAttributes(const std::string & datasetName,
	const std::vector<std::string> & attributeNames,
	const std::vector<std::string> & values)
{
}

void EtpHdfProxy::writeDatasetAttribute(const std::string & datasetName,
	const std::string & attributeName,
	const std::vector<std::string> & values)
{
}

void EtpHdfProxy::writeDatasetAttributes(const std::string & datasetName,
	const std::vector<std::string> & attributeNames,
	const std::vector<double> & values)
{
}

void EtpHdfProxy::writeDatasetAttributes(const std::string & datasetName,
	const std::vector<std::string> & attributeNames,
	const std::vector<int> & values)
{
}

std::string EtpHdfProxy::readStringAttribute(const std::string & obj_name,
	const std::string & attr_name) const
{
	return std::string();
}

vector<string> EtpHdfProxy::readStringArrayAttribute(const std::string & obj_name,
	const std::string & attr_name) const
{
	vector<string> result;
	return result;
}

double EtpHdfProxy::readDoubleAttribute(const std::string & obj_name,
	const std::string & attr_name) const
{
 return std::numeric_limits<double>::signaling_NaN();
}

LONG64 EtpHdfProxy::readLongAttribute(const std::string & obj_name,
	const std::string & attr_name) const
{
	return -1;
}

bool EtpHdfProxy::exist(const std::string & absolutePathInHdfFile) const
{
	return false;
}

