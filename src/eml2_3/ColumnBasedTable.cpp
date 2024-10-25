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
#include "ColumnBasedTable.h"

#include <stdexcept>
#include <sstream>

#include "../eml2/AbstractHdfProxy.h"
#include "../eml2/PropertyKind.h"

using namespace std;
using namespace EML2_3_NS;
using namespace gsoap_eml2_3;

ColumnBasedTable::ColumnBasedTable(COMMON_NS::DataObjectRepository* repo, const string & guid, const string & title)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_3 = soap_new_eml23__ColumnBasedTable(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(this);
}

gsoap_eml2_3::eml23__Column* ColumnBasedTable::getColumn(uint64_t columnIndex) const
{
	if (columnIndex >= getColumnCount()) {
		throw out_of_range("The column index is out of range.");
	}

	auto* cbt = static_cast<_eml23__ColumnBasedTable*>(gsoapProxy2_3);
	const size_t keyColumnCount = cbt->KeyColumn.size();
	return columnIndex < keyColumnCount
		? cbt->KeyColumn[columnIndex]
		: cbt->Column[columnIndex - keyColumnCount];
}

uint64_t ColumnBasedTable::getRowCount() const
{
	if (getColumnCount() == 0) {
		return 0;
	}
	return getCountOfArray(getColumn(0)->Values)/getValueCountPerRow(0);
}

uint64_t ColumnBasedTable::getColumnCount() const
{
	return static_cast<_eml23__ColumnBasedTable*>(gsoapProxy2_3)->KeyColumn.size() + static_cast<_eml23__ColumnBasedTable*>(gsoapProxy2_3)->Column.size();
}

COMMON_NS::DataObjectReference ColumnBasedTable::getPropertyKindDor(uint64_t columnIndex) const
{
	return COMMON_NS::DataObjectReference(getColumn(columnIndex)->PropertyKind);
}

std::string ColumnBasedTable::getUomAsString(uint64_t columnIndex) const
{
	auto* uom = getColumn(columnIndex)->Uom;
	return uom == nullptr ? "" : *uom;
}

uint64_t ColumnBasedTable::getValueCountPerRow(uint64_t columnIndex) const
{
	return getColumn(columnIndex)->ValueCountPerRow;
}

COMMON_NS::AbstractObject::numericalDatatypeEnum ColumnBasedTable::getDatatype(uint64_t columnIndex) const
{
	auto const * columnValues = getColumn(columnIndex)->Values;
	if (dynamic_cast<eml23__AbstractFloatingPointArray const*>(columnValues) != nullptr) {
		return COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE;
	}
	else if (dynamic_cast<eml23__AbstractIntegerArray const*>(columnValues) != nullptr) {
		return COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64;
	}
	else if (dynamic_cast<eml23__AbstractStringArray const*>(columnValues) != nullptr) {
		return COMMON_NS::AbstractObject::numericalDatatypeEnum::STRING;
	}

	throw logic_error("The datatype of the table column index \"" + std::to_string(columnIndex) + "\"is not supported by FESAPI yet.");
}

std::vector<std::string> ColumnBasedTable::getStringValues(uint64_t columnIndex) const
{
	auto* column = getColumn(columnIndex);
	if (column->Values->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__StringXmlArray) {
		return static_cast<eml23__StringXmlArray*>(column->Values)->Values;
	}

	return std::vector<std::string>();
}

void ColumnBasedTable::setStringValues(uint64_t columnIndex, const std::vector<std::string>& values)
{
	auto* column = getColumn(columnIndex);
	auto* xmlArray = soap_new_eml23__StringXmlArray(column->soap);
	xmlArray->CountPerValue = column->ValueCountPerRow;
	xmlArray->Values = values;

	column->Values = xmlArray;
}

std::vector<double> ColumnBasedTable::getDoubleValues(uint64_t columnIndex) const
{
	std::vector<double> result;

	auto* column = getColumn(columnIndex);
	eml23__AbstractFloatingPointArray* fpArray = dynamic_cast<eml23__AbstractFloatingPointArray*>(column->Values);
	if (fpArray != nullptr) {
		result.resize(getCountOfArray(fpArray));
		readArrayNdOfDoubleValues(fpArray, result.data());
	}

	return result;
}

void ColumnBasedTable::setDoubleValues(uint64_t columnIndex, const std::vector<double>& values)
{
	if (values.empty()) {
		throw invalid_argument("You cannot set a column without values");
	}

	auto* column = getColumn(columnIndex);
	auto* xmlArray = soap_new_eml23__FloatingPointXmlArray(column->soap);
	xmlArray->CountPerValue = column->ValueCountPerRow;

	ostringstream oss;
	oss << values[0];
	for (size_t i = 1; i < values.size(); ++i) {
		oss << " " << values[i];
	}
	xmlArray->Values = oss.str();

	column->Values = xmlArray;
}

void ColumnBasedTable::setDoubleValues(uint64_t columnIndex, double const* values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

	auto* column = getColumn(columnIndex);
	auto* externalArray = soap_new_eml23__FloatingPointExternalArray(column->soap);
	externalArray->CountPerValue = column->ValueCountPerRow;

	// Column datatype
	int64_t n = 1; // Endianess check https://stackoverflow.com/questions/4181951/how-to-check-whether-a-system-is-big-endian-or-little-endian
	externalArray->ArrayFloatingPointType = (*(char*)&n == 1) ? eml23__FloatingPointType::arrayOfFloat32LE : eml23__FloatingPointType::arrayOfFloat32BE;

	// Column Values
	externalArray->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	externalArray->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() + "/column" + std::to_string(columnIndex), valueCount, proxy));

	// HDF
	proxy->writeArrayNdOfDoubleValues(getHdfGroup(),
		"column" + std::to_string(columnIndex),
		values, &valueCount, 1);

	column->Values = externalArray;
}

std::vector<int64_t> ColumnBasedTable::getInt64Values(uint64_t columnIndex) const
{
	std::vector<int64_t> result;

	auto* column = getColumn(columnIndex);
	eml23__AbstractIntegerArray* intArray = dynamic_cast<eml23__AbstractIntegerArray*>(column->Values);
	if (intArray != nullptr) {
		result.resize(getCountOfArray(intArray));
		readArrayNdOfInt64Values(intArray, result.data());
	}

	return result;
}

void ColumnBasedTable::setInt64Values(uint64_t columnIndex, const std::vector<int64_t>& values)
{
	if (values.empty()) {
		throw invalid_argument("You cannot set a column without values");
	}

	auto* column = getColumn(columnIndex);
	auto* xmlArray = soap_new_eml23__IntegerXmlArray(column->soap);
	xmlArray->CountPerValue = column->ValueCountPerRow;

	ostringstream oss;
	oss << values[0];
	for (size_t i = 1; i < values.size(); ++i) {
		oss << " " << values[i];
	}
	xmlArray->Values = oss.str();

	column->Values = xmlArray;
}

void ColumnBasedTable::pushBackColumnHeader(bool isAKeyColumn, const std::string& title, EML2_NS::PropertyKind* propKind, uint64_t valueCountPerRow)
{
	auto* cbt = static_cast<_eml23__ColumnBasedTable*>(gsoapProxy2_3);
	
	gsoap_eml2_3::eml23__Column* column = gsoap_eml2_3::soap_new_eml23__Column(gsoapProxy2_3->soap);
	if (isAKeyColumn) {
		cbt->KeyColumn.push_back(column);
	}
	else {
		cbt->Column.push_back(column);
	}

	if (!title.empty()) {
		column->Title = soap_new_std__string(gsoapProxy2_3->soap);
		column->Title->assign(title);
	}

	column->ValueCountPerRow = valueCountPerRow;

	column->PropertyKind = propKind->newEml23Reference();
	getRepository()->addRelationship(this, propKind);
}

void ColumnBasedTable::loadTargetRelationships()
{
	const uint64_t columnCount = getColumnCount();
	for (uint64_t i = 0; i < columnCount; ++i) {

		//Prop Kind
		auto propKindDor = getPropertyKindDor(i);
		if (!propKindDor.isEmpty()) {
			convertDorIntoRel<EML2_NS::PropertyKind>(propKindDor);
		}

		// HDF proxy
		auto* column = getColumn(i);
		if (column->Values->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray) {
			for (auto* daPart : static_cast<eml23__FloatingPointExternalArray*>(column->Values)->Values->ExternalDataArrayPart) {
				getRepository()->addRelationship(this, getOrCreateHdfProxyFromDataArrayPart(daPart));
			}
		}
		else if (column->Values->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			for (auto* daPart : static_cast<eml23__IntegerExternalArray*>(column->Values)->Values->ExternalDataArrayPart) {
				getRepository()->addRelationship(this, getOrCreateHdfProxyFromDataArrayPart(daPart));
			}
		}
		else if (column->Values->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray) {
			for (auto* daPart : static_cast<eml23__BooleanExternalArray*>(column->Values)->Values->ExternalDataArrayPart) {
				getRepository()->addRelationship(this, getOrCreateHdfProxyFromDataArrayPart(daPart));
			}
		}
		else if (column->Values->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__StringExternalArray) {
			for (auto* daPart : static_cast<eml23__StringExternalArray*>(column->Values)->Values->ExternalDataArrayPart) {
				getRepository()->addRelationship(this, getOrCreateHdfProxyFromDataArrayPart(daPart));
			}
		}
	}
}
