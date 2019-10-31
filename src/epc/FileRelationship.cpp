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
#include "FileRelationship.h"

#include <sstream>
#include <algorithm>

using namespace std; // in order not to prefix by "std::" for each class in the "std" namespace. Never use "using namespace" in *.h file but only in *.cpp file!!!
using namespace epc; // in order not to prefix by "epc::" for each class in the "epc" namespace. Never use "using namespace" in *.h file but only in *.cpp file!!!

FileRelationship::FileRelationship()
{
}

FileRelationship::FileRelationship(const Relationship & frRelationship) : pathName("_rels\\.rels"), relationship()
{
	relationship.push_back(frRelationship);
}

FileRelationship::FileRelationship(const vector<Relationship> & frRelationship):
	pathName("_rels\\.rels"), relationship(frRelationship)
{}

bool FileRelationship::isEmpty() const
{
	return relationship.empty();
}

string FileRelationship::getPathName() const
{
	return pathName;
}

vector<Relationship> FileRelationship::getAllRelationship() const
{
	return relationship;
}

Relationship FileRelationship::getIndexRelationship(const int & index) const
{
	return relationship[index];
}

string FileRelationship::toString() const
{
	ostringstream oss;
	if (!isEmpty())
	{
		// XML def + namespaces def
		oss << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" << endl << "<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\">" << endl;

		// parcourir le vector...
		for (size_t i = 0; i < relationship.size(); ++i)
		{
			oss << "\t" << relationship[i].toString() << endl;
		}

		// end tag
		oss << "</Relationships>" << endl;
	}
	return oss.str();
}

void FileRelationship::setPathName(const std::string & frPathName)
{
	pathName = frPathName;
}

void FileRelationship::addRelationship(const Relationship & frRelationship)
{
	if (std::find(relationship.begin(), relationship.end(), frRelationship) == relationship.end()) {
		relationship.push_back(frRelationship);
	}
}

void FileRelationship::readFromString(const string & textInput)
{
	relationship.clear();

	size_t pos = textInput.find("Relationship ");
	if (pos == string::npos) {
		pos = textInput.find("Relationship>");
	}
	while (pos != string::npos) {
		size_t end = textInput.find("/>", pos + 12);
		if (end == string::npos)
			end = textInput.find("Relationship>", pos + 12); // closing tag : </Relationship>
		
		//ID
		string id = "";
		size_t attStart = textInput.find("Id=\"", pos);
		if (attStart != string::npos && attStart < end)
		{
			attStart += 4;
			size_t attEnd = textInput.find("\"", attStart);
			if (attStart != string::npos && attEnd != string::npos)
				id = textInput.substr(attStart, attEnd - attStart);
		}

		//type
		string type = "";
		attStart = textInput.find("Type=\"", pos);
		if (attStart != string::npos && attStart < end)
		{
			attStart += 6;
			size_t attEnd = textInput.find("\"", attStart);
			if (attStart != string::npos && attEnd != string::npos)
				type = textInput.substr(attStart, attEnd - attStart);
		}

		//Target
		string target = "";
		attStart = textInput.find("Target=\"", pos);
		if (attStart != string::npos && attStart < end)
		{
			attStart += 8;
			size_t attEnd = textInput.find("\"", attStart);
			if (attStart != string::npos && attEnd != string::npos)
				target = textInput.substr(attStart, attEnd - attStart);
		}

		//TargetMode
		bool internalTarget = true;
		attStart = textInput.find("TargetMode=\"", pos);
		if (attStart != string::npos && attStart < end)
		{
			attStart += 12;
			size_t attEnd = textInput.find("\"", attStart);
			if (attStart != string::npos && attEnd != string::npos)
			{
				string readString = textInput.substr(attStart, attEnd - attStart);
				if (readString.compare("External") == 0)
					internalTarget = false;
			}
		}

		Relationship rel(target, type, id, internalTarget);
		addRelationship(rel);

		pos = textInput.find("Relationship ", end + 1);
		if (pos == string::npos)
			pos = textInput.find("Relationship>", end + 1);
	}
}
















