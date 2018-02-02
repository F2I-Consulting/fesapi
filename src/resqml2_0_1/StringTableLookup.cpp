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
/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use,
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#include "resqml2_0_1/StringTableLookup.h"

#include <stdexcept>

#include "resqml2_0_1/CategoricalProperty.h"

using namespace std;
using namespace resqml2_0_1;
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

vector<Relationship> StringTableLookup::getAllEpcRelationships() const
{
	_resqml2__StringTableLookup* stringLookup = static_cast<_resqml2__StringTableLookup*>(gsoapProxy2_0_1);

	vector<Relationship> result;

	// XML backward relationship
	for (unsigned int i = 0; i < categoricalPropertyValuesSet.size(); i++)
	{
		Relationship rel(categoricalPropertyValuesSet[i]->getPartNameInEpcDocument(), "", categoricalPropertyValuesSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

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

	for (unsigned int i = 0; i < stringLookup->Value.size(); i++)
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

	for (unsigned int i = 0; i < stringLookup->Value.size(); i++)
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

	for (unsigned int i = 0; i < stringLookup->Value.size(); i++)
	{
		if (stringLookup->Value[i]->Key == longValue)
		{
			stringLookup->Value[i]->Value = strValue;
			return;
		}
	}
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


