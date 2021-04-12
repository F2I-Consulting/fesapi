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
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* DoubleTableLookup::XML_NS = "resqml22";

DoubleTableLookup::DoubleTableLookup(COMMON_NS::DataObjectRepository* repo, const string & guid, const string & title)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__DoubleTableLookup(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addDataObject(this);
}

unsigned int DoubleTableLookup::getItemCount() const
{
	return static_cast<_resqml22__DoubleTableLookup*>(gsoapProxy2_3)->Value.size();
}

double DoubleTableLookup::getKeyAtIndex(unsigned int index) const
{
	if (getItemCount() <= index) {
		throw out_of_range("The index is out of range.");
	}

	return (static_cast<_resqml22__DoubleTableLookup*>(gsoapProxy2_3)->Value)[index]->Key;
}

double DoubleTableLookup::getValueAtIndex(unsigned int index) const
{
	if (getItemCount() <= index) {
		throw out_of_range("The index is out of range.");
	}

	return (static_cast<_resqml22__DoubleTableLookup*>(gsoapProxy2_3)->Value)[index]->Value;
}

bool DoubleTableLookup::containsKey(double key)
{
	_resqml22__DoubleTableLookup* DoubleLookup = static_cast<_resqml22__DoubleTableLookup*>(gsoapProxy2_3);

	for (size_t i = 0; i < DoubleLookup->Value.size(); ++i) {
		if (DoubleLookup->Value[i]->Key == key) {
			return true;
		}
	}

	return false;
}

double DoubleTableLookup::getValueAtKey(double key)
{
	_resqml22__DoubleTableLookup* DoubleLookup = static_cast<_resqml22__DoubleTableLookup*>(gsoapProxy2_3);

	for (size_t i = 0; i < DoubleLookup->Value.size(); ++i) {
		if (DoubleLookup->Value[i]->Key == key) {
			return DoubleLookup->Value[i]->Value;
		}
	}

	return std::numeric_limits<double>::quiet_NaN();
}

void DoubleTableLookup::addValue(double key, double value)
{
	_resqml22__DoubleTableLookup* DoubleLookup = static_cast<_resqml22__DoubleTableLookup*>(gsoapProxy2_3);

	resqml22__DoubleLookup* xmlValue = soap_new_resqml22__DoubleLookup(gsoapProxy2_3->soap);
	xmlValue->Key = key;
	xmlValue->Value = value;
	DoubleLookup->Value.push_back(xmlValue);
}

void DoubleTableLookup::setValue(double key, double value)
{
	_resqml22__DoubleTableLookup* DoubleLookup = static_cast<_resqml22__DoubleTableLookup*>(gsoapProxy2_3);

	for (size_t i = 0; i < DoubleLookup->Value.size(); ++i) {
		if (DoubleLookup->Value[i]->Key == key) {
			DoubleLookup->Value[i]->Value = value;
			return;
		}
	}
}

double DoubleTableLookup::getMinimumValue()
{
	_resqml22__DoubleTableLookup* DoubleLookup = static_cast<_resqml22__DoubleTableLookup*>(gsoapProxy2_3);

	int64_t min = (std::numeric_limits<int64_t>::max)();
	for (size_t i = 0; i < DoubleLookup->Value.size(); ++i) {
		if (min > DoubleLookup->Value[i]->Key) {
			min = DoubleLookup->Value[i]->Key;
		}
	}

	return min;
}

double DoubleTableLookup::getMaximumValue()
{
	_resqml22__DoubleTableLookup* DoubleLookup = static_cast<_resqml22__DoubleTableLookup*>(gsoapProxy2_3);

	int64_t max = (std::numeric_limits<int64_t>::min)();
	for (size_t i = 0; i < DoubleLookup->Value.size(); ++i) {
		if (max < DoubleLookup->Value[i]->Key) {
			max = DoubleLookup->Value[i]->Key;
		}
	}

	return max;
}

std::map<double, double> DoubleTableLookup::getMap() const
{
	std::map<double, double> result;

	_resqml22__DoubleTableLookup* DoubleLookup = static_cast<_resqml22__DoubleTableLookup*>(gsoapProxy2_3);

	for (size_t i = 0; i < DoubleLookup->Value.size(); ++i) {
		result[DoubleLookup->Value[i]->Key] = DoubleLookup->Value[i]->Value;
	}

	return result;
}
