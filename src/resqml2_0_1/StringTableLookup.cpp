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
#include "StringTableLookup.h"

#include <limits>
#include <stdexcept>

#include "PropertyKind.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* StringTableLookup::XML_TAG = "StringTableLookup";
const char* StringTableLookup::XML_NS = "resqml20";

StringTableLookup::StringTableLookup(COMMON_NS::DataObjectRepository* repo, const string & guid, const string & title)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREStringTableLookup(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addDataObject(this);
}

uint32_t StringTableLookup::getRowCount() const
{
	return static_cast<_resqml20__StringTableLookup*>(gsoapProxy2_0_1)->Value.size();
}

COMMON_NS::DataObjectReference StringTableLookup::getPropertyKindDor(uint32_t columnIndex) const
{
	RESQML2_0_1_NS::PropertyKind* proKind = nullptr;
	if (columnIndex == 0) {
		proKind = getRepository()->createPartial<RESQML2_0_1_NS::PropertyKind>("323df361-784e-4062-a346-ff4ba80a78f0", "ordinal number");
	}
	else if (columnIndex == 1) {
		proKind = getRepository()->createPartial<RESQML2_0_1_NS::PropertyKind>("c1bb9d28-6d72-4690-a233-285bf7cf24d8", "value string");
	}
	else {
		throw out_of_range("The column index is out of range");
	}
	return COMMON_NS::DataObjectReference(proKind->newResqmlReference());
}

std::vector<std::string> StringTableLookup::getStringValues(uint32_t columnIndex) const
{
	if (columnIndex != 1) {
		throw logic_error("Only the column at index 1 does contain string values");
	}

	std::vector<std::string> result;

	_resqml20__StringTableLookup* stringLookup = static_cast<_resqml20__StringTableLookup*>(gsoapProxy2_0_1);
	for (auto const* pair : stringLookup->Value) {
		result.push_back(pair->Value);
	}

	return result;
}

std::vector<double> StringTableLookup::getDoubleValues(uint32_t columnIndex) const
{
	throw logic_error("The column does not contain floating point values");
}

std::vector<int64_t> StringTableLookup::getInt64Values(uint32_t columnIndex) const
{
	if (columnIndex != 0) {
		throw logic_error("Only the column at index 0 does contain string values");
	}

	std::vector<int64_t> result;

	_resqml20__StringTableLookup* stringLookup = static_cast<_resqml20__StringTableLookup*>(gsoapProxy2_0_1);
	for (auto const* pair : stringLookup->Value) {
		result.push_back(pair->Key);
	}

	return result;
}
