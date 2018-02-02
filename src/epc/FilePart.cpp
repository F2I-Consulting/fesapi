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



#include "FilePart.h"

#include <iostream>
#include <iterator>

using namespace std;
using namespace epc;

FilePart::FilePart():finalPathName(string())
{}

FilePart::FilePart(const string & outputPartPath):
	finalPathName(outputPartPath)
{
	string directoryOfPart(outputPartPath);

	// Clean the potential ending slashes of directoryOfPart
	while (directoryOfPart[directoryOfPart.size() - 1] == '/' || directoryOfPart[directoryOfPart.size() - 1] == '\\') {
		directoryOfPart = directoryOfPart.substr(0, directoryOfPart.size() - 1);
	}

	// extract the directory path
	size_t slashPos = directoryOfPart.find_last_of("/\\");
	directoryOfPart = slashPos == string::npos ? string() : directoryOfPart.substr(0, slashPos + 1);

	// Create the path for the associated relationship part
	string wkRelsPathname = directoryOfPart + "_rels/" + outputPartPath + ".rels";
	fileRelationship.setPathName(wkRelsPathname);
}

const string & FilePart::getFinalPathName() const
{
	return finalPathName;
}

const FileRelationship & FilePart::getFileRelationship() const
{
	return fileRelationship;
}

Relationship FilePart::getIndexRelationship(const int & index) const
{
	return fileRelationship.getIndexRelationship(index);
}

void FilePart::setFinalPathName(const string & finalPath)
{
	finalPathName = finalPath;
	/*
	int wkFileNamesize = 0;
	for(int i=finalPath.size()-1; i>=0; i--)
	{		
	if(finalPath[i]=='\\')
	{
	wkFileNamesize = i;
	break;
	}
	}
	string wkRelsPathname = finalPath.substr(0, finalPath.size() - wkFileNamesize) + "\\_rels\\" + finalPath.substr(finalPath.size() - wkFileNamesize, wkFileNamesize) + ".rels";
	*/
	string wkRelsPathname = "\\_rels\\" + finalPath + ".rels";
	fileRelationship.setPathName(wkRelsPathname);
}

void FilePart::createRelationship(const std::string & rsTarget, const std::string & rsType,const std::string & rsId, const bool & internalTarget)
{
	Relationship rel(rsTarget, rsType, rsId, internalTarget);
	fileRelationship.addRelationship(rel);
}

void FilePart::addRelationship(const Relationship & relationship)
{
	fileRelationship.addRelationship(relationship);
}
















