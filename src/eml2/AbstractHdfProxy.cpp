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
#include "AbstractHdfProxy.h"

#include <numeric>

using namespace EML2_NS;

void AbstractHdfProxy::initGsoapProxy(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, unsigned int emlVersion)
{
	if (emlVersion == 20) {
		gsoapProxy2_0_1 = gsoap_resqml2_0_1::soap_new_eml20__obj_USCOREEpcExternalPartReference(repo->getGsoapContext());
		static_cast<gsoap_resqml2_0_1::_eml20__EpcExternalPartReference*>(gsoapProxy2_0_1)->MimeType = MIME_TYPE;
	}

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(std::unique_ptr<COMMON_NS::AbstractObject>{this});
}

uint64_t AbstractHdfProxy::getElementCount(const std::string & datasetName)
{
	auto elementCountPerDim = getElementCountPerDimension(datasetName);
	return std::accumulate(elementCountPerDim.begin(), elementCountPerDim.end(), 1, std::multiplies<uint64_t>());
}
