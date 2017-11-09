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
