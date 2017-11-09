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

