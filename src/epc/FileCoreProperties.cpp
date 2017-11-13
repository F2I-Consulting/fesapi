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
#include "FileCoreProperties.h"

#include <time.h>
#include <sstream>
#if defined(_WIN32)
	#include <windows.h>
#elif defined(__gnu_linux__)
	#include <unistd.h>
	#include <pwd.h>
#endif


#if (defined(_WIN32) && _MSC_VER < 1600) || (defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6)))
#include "tools/nullptr_emulation.h"
#endif

using namespace std; // in order not to prefix by "std::" for each class in the "std" namespace. Never use "using namespace" in *.h file but only in*.cpp file!!!
using namespace epc; // in order not to prefix by "epc::" for each class in the "epc" namespace. Never use "using namespace" in *.h file but only in*.cpp file!!!

FileCoreProperties::FileCoreProperties()
{
}

CoreProperty FileCoreProperties::getProperty(const CoreProperty::TypeProperty & index) const
{
	return properties[index];
}

void FileCoreProperties::initDefaultCoreProperties()
{
	// CREATOR
	if (properties[CoreProperty::creator].isEmpty())
	{
#if defined(__gnu_linux__) 
        register struct passwd *pw;
        register uid_t uid;
                
        uid = geteuid ();
        pw = getpwuid (uid);
        if (pw)
        	setCreator(pw->pw_name);
        else
        	setCreator("unknown");
#elif defined(_WIN32)
		char acUserName[32];
		DWORD nUserName = sizeof(acUserName);
		GetUserName(acUserName, &nUserName);
		setCreator(acUserName);
#endif
	}

	// CREATED
	if (properties[CoreProperty::created].isEmpty())
	{
		time_t timestamp;
		struct tm * t;
		timestamp = time(nullptr);
		t = gmtime(&timestamp);
		int year = 1900 + t->tm_year;
		int month = 1 + t->tm_mon;
		int day = t->tm_mday;
		int hour = t->tm_hour;
		int minute = t->tm_min;
		int second = t->tm_sec;

		ostringstream oss;
		oss << year << "-";
		if (month > 9)
			oss << month<< "-";
		else
			oss << '0' << month<< "-";
		if (day > 9)
			oss << day << "T";
		else
			oss << '0' << day << "T";
		if (hour > 9)
			oss << hour << ":";
		else
			oss << '0' << hour << ":";
		if (minute > 9)
			oss << minute << ":";
		else
			oss << '0' << minute << ":";
		if (second > 9)
			oss << second << "Z";
		else
			oss << '0' << second << "Z";
		setCreated(oss.str());
	}

	// VERSION
	if (properties[CoreProperty::version].isEmpty())
	{
		setVersion("1.0");
	}

	// Identifier
	if (properties[CoreProperty::identifier].isEmpty())
	{
#if defined(_WIN32)
		GUID sessionGUID = GUID_NULL;
		HRESULT hr = CoCreateGuid(&sessionGUID);
		wchar_t uuidWStr[39];
		StringFromGUID2(sessionGUID, uuidWStr, 39);
		uuidWStr[37] = '\0'; // Delete the closing bracket
		char uuidStr[37];
		wcstombs(uuidStr, uuidWStr+1, 39); // +1 in order not to take into account the opening bracket

		ostringstream oss;
		oss << "urn:uuid:" << uuidStr;
		setIdentifier(oss.str());
#endif
	}
}

std::string FileCoreProperties::toString() const 
{
	// XML def + namespaces def
	ostringstream oss;
	oss << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" << endl;
	oss << "<coreProperties xmlns=\"http://schemas.openxmlformats.org/package/2006/metadata/core-properties\"" << endl;
	oss << "xmlns:dcterms=\"http://purl.org/dc/terms/\"" << endl,
	oss << "xmlns:dc=\"http://purl.org/dc/elements/1.1/\"" << endl,
	oss << "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">" << endl;

	// content
	for (unsigned int i = 0; i < CoreProperty::undefinedCoreProperty; i++)
	{
		if (!properties[i].isEmpty())
			oss << "\t" << properties[i].toString() << endl;
	}

	// end tag
	oss << "</coreProperties>" << endl;

	return oss.str();
}

void FileCoreProperties::setCategory(const std::string & value)
{
	properties[CoreProperty::category].setCategory(value);
}

void FileCoreProperties::setContentStatus(const std::string & value)
{
	properties[CoreProperty::contentStatus].setContentStatus(value);
}

void FileCoreProperties::setCreated(const std::string & value)
{
	properties[CoreProperty::created].setCreated(value);
}

void FileCoreProperties::setCreator(const std::string & value)
{
	properties[CoreProperty::creator].setCreator(value);
}

void FileCoreProperties::setDescription(const std::string & value)
{
	properties[CoreProperty::description].setDescription(value);
}

void FileCoreProperties::setIdentifier(const std::string & value)
{
	properties[CoreProperty::identifier].setIdentifier(value);
}

void FileCoreProperties::setKeywords(const std::string & value)
{
	properties[CoreProperty::keywords].setKeywords(value);
}

void FileCoreProperties::addKeywords(const std::string & value)
{
	properties[CoreProperty::keywords].addKeywords(value);
}

void FileCoreProperties::setLanguage(const std::string & value)
{
	properties[CoreProperty::language].setLanguage(value);
}

void FileCoreProperties::setLastModifiedBy(const std::string & value)
{
	properties[CoreProperty::lastModifiedBy].setLastModifiedBy(value);
}

void FileCoreProperties::setLastPrinted(const std::string & value)
{
	properties[CoreProperty::lastPrinted].setLastPrinted(value);
}

void FileCoreProperties::setModified(const std::string & value)
{
	properties[CoreProperty::modified].setModified(value);
}

void FileCoreProperties::setRevision(const std::string & value)
{
	properties[CoreProperty::revision].setRevision(value);
}

void FileCoreProperties::setSubject(const std::string & value)
{
	properties[CoreProperty::subject].setSubject(value);
}

void FileCoreProperties::setTitle(const std::string & value)
{
	properties[CoreProperty::title].setTitle(value);
}

void FileCoreProperties::setVersion(const std::string & value)
{
	properties[CoreProperty::version].setVersion(value);
}

void FileCoreProperties::readFromString(const string & textInput)
{
	for (unsigned int i = 0; i < CoreProperty::undefinedCoreProperty; i++)
		properties[i].setTypeProperty(CoreProperty::undefinedCoreProperty);

	size_t start = textInput.find("<coreProperties ");
	if (start != string::npos)
			start = textInput.find("<coreProperties>");
	size_t end = textInput.find("</coreProperties>", start);
		
	//identifier
	size_t attStart = textInput.find("identifier", start);
	if (attStart != string::npos && attStart < end)
	{
		attStart += 11;
		size_t attEnd = textInput.find("</", attStart);
		if (attStart != string::npos && attEnd != string::npos)
			properties[CoreProperty::identifier].setIdentifier(textInput.substr(attStart, attEnd - attStart));
	}
	
}

