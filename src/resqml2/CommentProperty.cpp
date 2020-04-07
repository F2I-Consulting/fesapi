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
#include "CommentProperty.h"

#include <sstream>
#include <list>

#include <H5Tpublic.h>

#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_NS;

const char* CommentProperty::XML_TAG = "CommentProperty";

void CommentProperty::pushBackStringHdf5ArrayOfValues(const std::vector<std::string> & values,
	EML2_NS::AbstractHdfProxy * proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const string datasetName = pushBackRefToExistingDataset(proxy, "");

	// Build the CHAR array
	hsize_t dimTwo = 0;
	for (std::vector<std::string>::const_iterator it = values.begin() ; it!= values.end() ; ++it){
		if ((*it).length() > dimTwo)
			dimTwo = (*it).length();
	}

	hsize_t strNb = values.size();
	std::unique_ptr<unsigned char[]> cTab(new unsigned char[strNb*dimTwo]);

	int indStr = 0;
	for (std::vector<std::string>::const_iterator it = values.begin() ; it!= values.end() ; ++it){
		for (unsigned int indCha = 0 ; indCha < dimTwo ; indCha++) {
			if (indCha < (*it).length())
				cTab[(indStr*dimTwo)+indCha] = (*it)[indCha];
			else
				cTab[(indStr*dimTwo)+indCha] = '\0';
		}
		indStr++;
	}

	hsize_t nbValPerDim[2] = {strNb, dimTwo};
	const unsigned int nbDimensions = 2;

    // HDF
	proxy->writeArrayNd(getHdfGroup(),
		datasetName,
        H5T_NATIVE_UCHAR,
        cTab.get(),
        nbValPerDim,   // 0 = number of strings, 1 = length of the longest string 
		nbDimensions); // 2
}

std::vector<std::string> CommentProperty::getStringValuesOfPatch(unsigned int patchIndex)
{	
	std::vector<std::string> result;

	std::string datasetPath;
	EML2_NS::AbstractHdfProxy* hdfProxy = getValuesHdfProxyAndDatasetPathOfPatch(patchIndex, datasetPath);

	// Check if the hdf dataset really contains constant length string.
	std::vector<hsize_t> dims = hdfProxy->readArrayDimensions(datasetPath);
	if (dims.size() != 2) {
		return result;
	}
	// Check if the hdf dataset really contains unsigned char values.
	if (getValuesHdfDatatype() != AbstractValuesProperty::UCHAR) {
		return result;
	}

	const unsigned int nbStrings = (unsigned int)dims[0]; // The count of strings in the HDF dataset.
	const unsigned int stringLength = (unsigned int)dims[1]; // The constant string length in the hdf dataset.

	// Read all char/strings from the hdf dataset
	std::unique_ptr<unsigned char[]> values(new unsigned char[nbStrings * stringLength]);
	hdfProxy->readArrayNdOfUCharValues (datasetPath, values.get());

	for (unsigned int stringIndex = 0; stringIndex < nbStrings; ++stringIndex) {
		std::string comment = string();
		unsigned int globalCharIndex = stringIndex*stringLength;
		for (unsigned int localCharIndex = 0; localCharIndex < stringLength; ++localCharIndex) {
			if (values[globalCharIndex] != '\0') {
				comment.push_back(values[globalCharIndex]);
			}
			else {
				break;
			}
			globalCharIndex++;
		}

		result.push_back(comment);
	}

	return result;
}
