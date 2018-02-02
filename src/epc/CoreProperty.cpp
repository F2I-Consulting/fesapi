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


#include "CoreProperty.h"

#include <sstream>

using namespace std; // in order not to prefix by "std::" for each class in the "std" namespace. Never use "using namespace" in *.h file but only in*.cpp file!!!
using namespace epc; // in order not to prefix by "epc::" for each class in the "epc" namespace. Never use "using namespace" in *.h file but only in*.cpp file!!!

CoreProperty::CoreProperty() :
	type(undefinedCoreProperty)
{
}

CoreProperty::CoreProperty(const TypeProperty & pType):
	type(pType)
{
}

CoreProperty::CoreProperty(const TypeProperty & pType, const string & pValue):
	type(pType)
{
	value.push_back(pValue);
}

CoreProperty::CoreProperty(const TypeProperty & pType, const std::vector<std::string> & pValue):
	type(pType), value(pValue)
{
}

bool CoreProperty::isEmpty() const
{
	return value.empty();
}

CoreProperty::TypeProperty CoreProperty::getTypeProperty() const
{
	return type;
}

void CoreProperty::setTypeProperty(const TypeProperty & corePropertyType)
{
	type = corePropertyType;
}

vector<string> CoreProperty::getAllValue() const
{
	return value;
}

string CoreProperty::getValue(const int & index) const
{
	return value[index];
}

string CoreProperty::toString() const
{
	switch (type)
	{
	case category:
		return "<category>" + getValue() + "</category>";
	case contentStatus:
		return "<contentStatus>" + getValue() + "</contentStatus>";
	case created:
		return "<dcterms:created xsi:type=\"dcterms:W3CDTF\">" + getValue() + "</dcterms:created>";
	case creator:
		return "<dc:creator>" + getValue() + "</dc:creator>";
	case description:
		return "<dc:desciption>" + getValue() + "</dc:description>";
	case identifier:
		return "<dc:identifier>" + getValue() + "</dc:identifier>";
	case keywords:
		{
			vector<string> wk_Vector = getAllValue();
			unsigned int wk_SizeVector = wk_Vector.size();

			ostringstream oss;
			oss << "<keywords xml:lang=\"" << wk_Vector[0].substr(0,5) << "\"> " << wk_Vector[0].substr(5,wk_Vector[0].size()) << endl;
		
			for (unsigned int i = 1; i < wk_SizeVector; i++)
			{
				oss << "<value xml:lang=\"" << wk_Vector[i].substr(0,5) << "\">" << wk_Vector[i].substr(5,wk_Vector[i].size()) << "</value>" << endl; 
			}

			oss << "</keywords>" << endl;

			return oss.str();
		}
	case language:
		return "<dc:language>" + getValue() + "</dc:language>";
	case lastModifiedBy:
		return "<lastModifiedBy>" + getValue() + "</lastModifiedBy>";
	case lastPrinted:
		return "<lastPrinted>" + getValue() + "</lastPrinted>";
	case modified:
		return "<dcterms:modified xsi:type=\"dcterms:W3CDTF\">" + getValue() + "</dcterms:modified>";
	case revision:
		return "<revision>" + getValue() + "</revision>";
	case subject:
		return "<dc:subject>" + getValue() + "</dc:subject>";
	case title:
		return "<dc:title>" + getValue() + "</dc:title>";
	case version:
		return "<version>" + getValue() + "</version>";
	default :
		return "";
	}
}

void CoreProperty::setCategory(std::string pValue)
{
	type = category;
	value.erase(value.begin(), value.end());
	value.push_back(pValue);
}

void CoreProperty::setContentStatus(std::string pValue)
{
	type = contentStatus;
	value.erase(value.begin(), value.end());
	value.push_back(pValue);
}

void CoreProperty::setCreated(std::string pValue)
{
	type = created;
	value.erase(value.begin(), value.end());
	value.push_back(pValue);
}

void CoreProperty::setCreator(std::string pValue)
{
	type = creator;
	value.erase(value.begin(), value.end());
	value.push_back(pValue);
}

void CoreProperty::setDescription(std::string pValue)
{
	type = description;
	value.erase(value.begin(), value.end());
	value.push_back(pValue);
}

void CoreProperty::setIdentifier(std::string pValue)
{
	type = identifier;
	value.erase(value.begin(), value.end());
	value.push_back(pValue);
}

void CoreProperty::setKeywords(std::string pValue)
{
	type = keywords;
	value.erase(value.begin(), value.end());
	value.push_back(pValue);
}

void CoreProperty::addKeywords(std::string pValue)
{
	type = keywords;
	value.push_back(pValue);
}

void CoreProperty::setLanguage(std::string pValue)
{
	type = language;
	value.erase(value.begin(), value.end());
	value.push_back(pValue);
}

void CoreProperty::setLastModifiedBy(std::string pValue)
{
	type = lastModifiedBy;
	value.erase(value.begin(), value.end());
	value.push_back(pValue);
}

void CoreProperty::setLastPrinted(std::string pValue)
{
	type = lastPrinted;
	value.erase(value.begin(), value.end());
	value.push_back(pValue);
}

void CoreProperty::setModified(std::string pValue)
{
	type = modified;
	value.erase(value.begin(), value.end());
	value.push_back(pValue);
}

void CoreProperty::setRevision(std::string pValue)
{
	type = revision;
	value.erase(value.begin(), value.end());
	value.push_back(pValue);
}

void CoreProperty::setSubject(std::string pValue)
{
	type = subject;
	value.erase(value.begin(), value.end());
	value.push_back(pValue);
}

void CoreProperty::setTitle(std::string pValue)
{
	type = title;
	value.erase(value.begin(), value.end());
	value.push_back(pValue);

}

void CoreProperty::setVersion(std::string pValue)
{
	type = version;
	value.erase(value.begin(), value.end());
	value.push_back(pValue);
}















