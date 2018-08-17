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
#include "resqml2_0_1/StringTableLookup.h"

#include <stdexcept>

#include "resqml2_0_1/CategoricalProperty.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* StringTableLookup::XML_TAG = "StringTableLookup";

StringTableLookup::StringTableLookup(soap* soapContext, const string & guid, const string & title)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREStringTableLookup(soapContext, 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

vector<Relationship> StringTableLookup::getAllSourceRelationships() const
{
	vector<Relationship> result;

	// XML backward relationship
	for (size_t i = 0; i < categoricalPropertyValuesSet.size(); ++i)
	{
		Relationship rel(categoricalPropertyValuesSet[i]->getPartNameInEpcDocument(), "", categoricalPropertyValuesSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

vector<Relationship> StringTableLookup::getAllTargetRelationships() const
{
	vector<Relationship> result;
	return result;
}

unsigned int StringTableLookup::getItemCount() const
{
	return static_cast<_resqml2__StringTableLookup*>(gsoapProxy2_0_1)->Value.size();
}

long StringTableLookup::getKeyAtIndex(const unsigned int & index) const
{
	if (getItemCount() <= index)
		throw out_of_range("The index is out of range.");

	return (static_cast<_resqml2__StringTableLookup*>(gsoapProxy2_0_1)->Value)[index]->Key;
}

std::string StringTableLookup::getStringValueAtIndex(const unsigned int & index) const
{
	if (getItemCount() <= index)
		throw out_of_range("The index is out of range.");

	return (static_cast<_resqml2__StringTableLookup*>(gsoapProxy2_0_1)->Value)[index]->Value;
}

bool StringTableLookup::containsKey(const long & longValue)
{
	_resqml2__StringTableLookup* stringLookup = static_cast<_resqml2__StringTableLookup*>(gsoapProxy2_0_1);

	for (size_t i = 0; i < stringLookup->Value.size(); ++i)
	{
		if (stringLookup->Value[i]->Key == longValue)
		{
			return true;
		}
	}

	return false;
}

std::string StringTableLookup::getStringValue(const long & longValue)
{
	_resqml2__StringTableLookup* stringLookup = static_cast<_resqml2__StringTableLookup*>(gsoapProxy2_0_1);

	for (size_t i = 0; i < stringLookup->Value.size(); ++i)
	{
		if (stringLookup->Value[i]->Key == longValue)
		{
			return stringLookup->Value[i]->Value;
		}
	}

	return "";
}

void StringTableLookup::addValue(const string & strValue, const long & longValue)
{
	_resqml2__StringTableLookup* stringLookup = static_cast<_resqml2__StringTableLookup*>(gsoapProxy2_0_1);

	resqml2__StringLookup* xmlValue = soap_new_resqml2__StringLookup(gsoapProxy2_0_1->soap, 1);
	xmlValue->Key = longValue;
	xmlValue->Value = strValue;
	stringLookup->Value.push_back(xmlValue);
}

void StringTableLookup::setValue(const string & strValue, const long & longValue)
{
	_resqml2__StringTableLookup* stringLookup = static_cast<_resqml2__StringTableLookup*>(gsoapProxy2_0_1);

	for (size_t i = 0; i < stringLookup->Value.size(); ++i)
	{
		if (stringLookup->Value[i]->Key == longValue)
		{
			stringLookup->Value[i]->Value = strValue;
			return;
		}
	}
}

LONG64 StringTableLookup::getMinimumValue()
{
	_resqml2__StringTableLookup* stringLookup = static_cast<_resqml2__StringTableLookup*>(gsoapProxy2_0_1);

	LONG64 min = (std::numeric_limits<LONG64>::max)();
	for (size_t i = 0; i < stringLookup->Value.size(); ++i) {
		if (min > stringLookup->Value[i]->Key) {
			min = stringLookup->Value[i]->Key;
		}
	}

	return min;
}

LONG64 StringTableLookup::getMaximumValue()
{
	_resqml2__StringTableLookup* stringLookup = static_cast<_resqml2__StringTableLookup*>(gsoapProxy2_0_1);

	LONG64 max = (std::numeric_limits<LONG64>::min)();
	for (size_t i = 0; i < stringLookup->Value.size(); ++i) {
		if (max < stringLookup->Value[i]->Key) {
			max = stringLookup->Value[i]->Key;
		}
	}

	return max;
}

#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
unordered_map<long, string> StringTableLookup::getMap() const
{
	unordered_map<long, string> result;
#else
std::tr1::unordered_map<long, string> StringTableLookup::getMap() const
{
	std::tr1::unordered_map<long, string> result;
#endif

	_resqml2__StringTableLookup* stringLookup = static_cast<_resqml2__StringTableLookup*>(gsoapProxy2_0_1);

	for (unsigned int i = 0; i < stringLookup->Value.size(); i++)
	{
		result[stringLookup->Value[i]->Key] = stringLookup->Value[i]->Value;
	}

	return result;
}


