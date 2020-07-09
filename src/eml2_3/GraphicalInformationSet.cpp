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
#include "GraphicalInformationSet.h"

using namespace std;
using namespace EML2_3_NS;

const char* GraphicalInformationSet::XML_NS = "eml23";

GraphicalInformationSet::GraphicalInformationSet(COMMON_NS::DataObjectRepository* repo, string const& guid, string const& title)
{
	if (repo == nullptr) {
		throw std::invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_3 = gsoap_eml2_3::soap_new_eml23__GraphicalInformationSet(repo->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addOrReplaceDataObject(this);
}
