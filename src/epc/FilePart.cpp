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

FilePart::FilePart():fileRelationship()
{}

FilePart::FilePart(string outputPartPath):
	fileRelationship()
{
	// Clean the potential ending slashes of directoryOfPart
	while (outputPartPath[outputPartPath.size() - 1] == '/' || outputPartPath[outputPartPath.size() - 1] == '\\') {
		outputPartPath = outputPartPath.substr(0, outputPartPath.size() - 1);
	}

	// extract the directory path
	size_t slashPos = outputPartPath.find_last_of("/\\");

	// Create the path for the associated relationship part
	string wkRelsPathname = slashPos == string::npos
		? "_rels/" + outputPartPath + ".rels"
		: outputPartPath.substr(0, slashPos + 1) + "_rels/" + outputPartPath.substr(slashPos + 1) + ".rels";
	fileRelationship.setPathName(wkRelsPathname);
}

const FileRelationship & FilePart::getFileRelationship() const
{
	return fileRelationship;
}

Relationship FilePart::getIndexRelationship(int index) const
{
	return fileRelationship.getIndexRelationship(index);
}

void FilePart::createRelationship(const std::string & rsTarget, const std::string & rsType,const std::string & rsId, bool internalTarget)
{
	Relationship rel(rsTarget, rsType, rsId, internalTarget);
	fileRelationship.addRelationship(rel);
}

void FilePart::addRelationship(const Relationship & relationship)
{
	fileRelationship.addRelationship(relationship);
}
