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
#include "CmpLineFeature.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* CmpLineFeature::XML_NS = "resqml22";

CmpLineFeature::CmpLineFeature(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title,
	int64_t nearestShotPointIndicesIncrement, int64_t firstNearestShotPointIndex, uint64_t nearestShotPointCount)
{
	if (repo == nullptr) {
		throw invalid_argument("The soap context cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__CmpLineFeature(repo->getGsoapContext());
	_resqml22__CmpLineFeature* cmpLine = static_cast<_resqml22__CmpLineFeature*>(gsoapProxy2_3);

	eml23__IntegerLatticeArray* nearestShotPointIndices = soap_new_eml23__IntegerLatticeArray(gsoapProxy2_3->soap);
	nearestShotPointIndices->StartValue = firstNearestShotPointIndex;
	nearestShotPointIndices->Offset.push_back(soap_new_eml23__IntegerConstantArray(gsoapProxy2_3->soap));
	nearestShotPointIndices->Offset[0]->Count = nearestShotPointCount - 1;
	nearestShotPointIndices->Offset[0]->Value = nearestShotPointIndicesIncrement;
	cmpLine->NearestShotPointIndices = nearestShotPointIndices;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(this);
}
