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
#include "ContinuousColorMap.h"

using namespace std;
using namespace gsoap_eml2_3;
using namespace RESQML2_2_NS;

const char* ContinuousColorMap::XML_NS = "resqml22";

ContinuousColorMap::ContinuousColorMap(COMMON_NS::DataObjectRepository* repo, string const& guid, string const& title,
	resqml22__InterpolationDomain interpolationDomain, resqml22__InterpolationMethod interpolationMethod)
{
	if (repo == nullptr) {
		throw invalid_argument("The repository cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__ContinuousColorMap(repo->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	resqml22__ContinuousColorMap* continuousColorMap = static_cast<resqml22__ContinuousColorMap*>(gsoapProxy2_3);
	continuousColorMap->InterpolationDomain = interpolationDomain;
	continuousColorMap->InterpolationMethod = interpolationMethod;

	repo->addOrReplaceDataObject(this);
}
