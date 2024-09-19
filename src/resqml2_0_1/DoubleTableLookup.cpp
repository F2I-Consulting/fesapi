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

DoubleTableLookup::DoubleTableLookup(COMMON_NS::DataObjectRepository* repo, const string& guid, const string& title)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREDoubleTableLookup(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(this);
}

uint64_t DoubleTableLookup::getItemCount() const
{
	return static_cast<_resqml20__DoubleTableLookup*>(gsoapProxy2_0_1)->Value.size();
}

double DoubleTableLookup::getKeyAtIndex(uint64_t index) const
{
	return (static_cast<_resqml20__DoubleTableLookup*>(gsoapProxy2_0_1)->Value).at(index)->Key;
}

double DoubleTableLookup::getValueAtIndex(uint64_t index) const
{
	return (static_cast<_resqml20__DoubleTableLookup*>(gsoapProxy2_0_1)->Value).at(index)->Value;
}

bool DoubleTableLookup::containsKey(double key)
{
	const auto dblLookups = static_cast<_resqml20__DoubleTableLookup*>(gsoapProxy2_0_1)->Value;

	return std::find_if(dblLookups.begin(), dblLookups.end(),
		[key](resqml20__DoubleLookup const* element) {return element->Key == key; })
		!= dblLookups.end();
}

double DoubleTableLookup::getValueAtKey(double key)
{
	const auto dblLookups = static_cast<_resqml20__DoubleTableLookup*>(gsoapProxy2_0_1)->Value;

	auto it = std::find_if(dblLookups.begin(), dblLookups.end(),
		[key](resqml20__DoubleLookup const* element) {return element->Key == key; });

	return it == dblLookups.end() ? std::numeric_limits<double>::quiet_NaN() : (*it)->Value;
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
	auto dblLookups = static_cast<_resqml20__DoubleTableLookup*>(gsoapProxy2_0_1)->Value;
	auto it = std::find_if(dblLookups.begin(), dblLookups.end(),
		[key](resqml20__DoubleLookup const* element) {return element->Key == key; });

	if (it != dblLookups.end()) (*it)->Value = value;
}

namespace {
	auto doubleLookupComparator = [](resqml20__DoubleLookup * a, resqml20__DoubleLookup * b)
    {
        return a->Key < b->Key;
    };
}

double DoubleTableLookup::getMinimumValue()
{
	std::vector<resqml20__DoubleLookup *> stringLookup = static_cast<_resqml20__DoubleTableLookup*>(gsoapProxy2_0_1)->Value;

 	return (*std::min_element(stringLookup.begin(), stringLookup.end(), doubleLookupComparator))->Key;
}

double DoubleTableLookup::getMaximumValue()
{
	std::vector<resqml20__DoubleLookup *> stringLookup = static_cast<_resqml20__DoubleTableLookup*>(gsoapProxy2_0_1)->Value;

 	return (*std::max_element(stringLookup.begin(), stringLookup.end(), doubleLookupComparator))->Key;
}

std::map<double, double> DoubleTableLookup::getMap() const
{
	map<double, double> result;

	for (auto const* dblLookup : static_cast<_resqml20__DoubleTableLookup const*>(gsoapProxy2_0_1)->Value) {
		result[dblLookup->Key] = dblLookup->Value;
	}

	return result;
}
