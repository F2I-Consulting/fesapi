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
#include "DoubleTableLookup.h"

#include <limits>
#include <stdexcept>

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* DoubleTableLookup::XML_NS = "resqml20";

DoubleTableLookup::DoubleTableLookup(COMMON_NS::DataObjectRepository* repo, const string & guid, const string & title)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREDoubleTableLookup(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addOrReplaceDataObject(this);
}

unsigned int DoubleTableLookup::getItemCount() const
{
	return static_cast<_resqml20__DoubleTableLookup*>(gsoapProxy2_0_1)->Value.size();
}

double DoubleTableLookup::getKeyAtIndex(unsigned int index) const
{
	if (getItemCount() <= index) {
		throw out_of_range("The index is out of range.");
	}

	return (static_cast<_resqml20__DoubleTableLookup*>(gsoapProxy2_0_1)->Value)[index]->Key;
}

double DoubleTableLookup::getValueAtIndex(unsigned int index) const
{
	if (getItemCount() <= index) {
		throw out_of_range("The index is out of range.");
	}

	return (static_cast<_resqml20__DoubleTableLookup*>(gsoapProxy2_0_1)->Value)[index]->Value;
}

bool DoubleTableLookup::containsKey(double key)
{
	_resqml20__DoubleTableLookup* stringLookup = static_cast<_resqml20__DoubleTableLookup*>(gsoapProxy2_0_1);

	for (size_t i = 0; i < stringLookup->Value.size(); ++i) {
		if (stringLookup->Value[i]->Key == key) {
			return true;
		}
	}

	return false;
}

double DoubleTableLookup::getValueAtKey(double key)
{
	_resqml20__DoubleTableLookup* stringLookup = static_cast<_resqml20__DoubleTableLookup*>(gsoapProxy2_0_1);

	for (size_t i = 0; i < stringLookup->Value.size(); ++i) {
		if (stringLookup->Value[i]->Key == key) {
			return stringLookup->Value[i]->Value;
		}
	}

	return std::numeric_limits<double>::quiet_NaN();
}

void DoubleTableLookup::addValue(double key, double value)
{
	_resqml20__DoubleTableLookup* stringLookup = static_cast<_resqml20__DoubleTableLookup*>(gsoapProxy2_0_1);

	resqml20__DoubleLookup* xmlValue = soap_new_resqml20__DoubleLookup(gsoapProxy2_0_1->soap);
	xmlValue->Key = key;
	xmlValue->Value = value;
	stringLookup->Value.push_back(xmlValue);
}

void DoubleTableLookup::setValue(double key, double value)
{
	_resqml20__DoubleTableLookup* stringLookup = static_cast<_resqml20__DoubleTableLookup*>(gsoapProxy2_0_1);

	for (size_t i = 0; i < stringLookup->Value.size(); ++i) {
		if (stringLookup->Value[i]->Key == key) {
			stringLookup->Value[i]->Value = value;
			return;
		}
	}
}

double DoubleTableLookup::getMinimumValue()
{
	_resqml20__DoubleTableLookup* stringLookup = static_cast<_resqml20__DoubleTableLookup*>(gsoapProxy2_0_1);

	LONG64 min = (std::numeric_limits<LONG64>::max)();
	for (size_t i = 0; i < stringLookup->Value.size(); ++i) {
		if (min > stringLookup->Value[i]->Key) {
			min = stringLookup->Value[i]->Key;
		}
	}

	return min;
}

double DoubleTableLookup::getMaximumValue()
{
	_resqml20__DoubleTableLookup* stringLookup = static_cast<_resqml20__DoubleTableLookup*>(gsoapProxy2_0_1);

	LONG64 max = (std::numeric_limits<LONG64>::min)();
	for (size_t i = 0; i < stringLookup->Value.size(); ++i) {
		if (max < stringLookup->Value[i]->Key) {
			max = stringLookup->Value[i]->Key;
		}
	}

	return max;
}

std::map<double, double> DoubleTableLookup::getMap() const
{
	map<double, double> result;

	_resqml20__DoubleTableLookup* stringLookup = static_cast<_resqml20__DoubleTableLookup*>(gsoapProxy2_0_1);

	for (size_t i = 0; i < stringLookup->Value.size(); ++i) {
		result[stringLookup->Value[i]->Key] = stringLookup->Value[i]->Value;
	}

	return result;
}
