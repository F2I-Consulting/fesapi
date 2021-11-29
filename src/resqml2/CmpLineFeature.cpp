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

#include <numeric>

#include "ShotPointLineFeature.h"

using namespace std;
using namespace RESQML2_NS;
using namespace gsoap_eml2_3;

const char* CmpLineFeature::XML_TAG = "CmpLineFeature";
		
uint64_t CmpLineFeature::getTraceCount() const
{
	_resqml22__CmpLineFeature* cmpLine = static_cast<_resqml22__CmpLineFeature*>(gsoapProxy2_3);
	if (cmpLine->NearestShotPointIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerLatticeArray) {
		return static_cast<eml23__IntegerLatticeArray*>(cmpLine->NearestShotPointIndices)->Offset[0]->Count + 1;
	}
	else if (cmpLine->NearestShotPointIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		uint64_t result = 0;
		for (const auto& dataArrayPart : static_cast<eml23__IntegerExternalArray*>(cmpLine->NearestShotPointIndices)->Values->ExternalDataArrayPart) {
			// It is safe to cast to unsigned since a Count cannot be < 0
			result += static_cast<uint64_t>(std::accumulate(std::begin(dataArrayPart->Count), std::end(dataArrayPart->Count), static_cast<uint64_t>(1), std::multiplies<LONG64>()));
		}
		return result;
	}

	throw logic_error("Not implemented yet.");
}

void CmpLineFeature::setShotPointLine(ShotPointLineFeature* shotPointLine)
{
	_resqml22__CmpLineFeature* cmpLine = static_cast<_resqml22__CmpLineFeature*>(gsoapProxy2_3);
	cmpLine->ShotPointLineFeature = shotPointLine->newEml23Reference();
}

ShotPointLineFeature* CmpLineFeature::getShotPointLine() const
{
	_resqml22__CmpLineFeature* cmpLine = static_cast<_resqml22__CmpLineFeature*>(gsoapProxy2_3);
	return cmpLine->ShotPointLineFeature == nullptr
		? nullptr
		: getRepository()->getDataObjectByUuid<ShotPointLineFeature>(cmpLine->ShotPointLineFeature->Uuid);
}

void CmpLineFeature::loadTargetRelationships()
{
	AbstractSeismicLineFeature::loadTargetRelationships();

	_resqml22__CmpLineFeature* cmpLine = static_cast<_resqml22__CmpLineFeature*>(gsoapProxy2_3);

	if (cmpLine->ShotPointLineFeature != nullptr) {
		convertDorIntoRel<ShotPointLineFeature>(COMMON_NS::DataObjectReference(cmpLine->ShotPointLineFeature));
	}
}
