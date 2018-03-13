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
#include "resqml2_0_1/BoundaryFeatureInterpretation.h"

#include <algorithm>
#include <stdexcept>

#include "resqml2_0_1/BoundaryFeature.h"
#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* BoundaryFeatureInterpretation::XML_TAG = "BoundaryFeatureInterpretation";

BoundaryFeatureInterpretation::BoundaryFeatureInterpretation(BoundaryFeature * feature, const string & guid, const string & title)
{
	if (!feature)
		throw invalid_argument("The interpreted feature cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREBoundaryFeatureInterpretation(feature->getGsoapContext(), 1);
	_resqml2__BoundaryFeatureInterpretation* interp = static_cast<_resqml2__BoundaryFeatureInterpretation*>(gsoapProxy2_0_1);
	interp->Domain = resqml2__Domain__mixed;
	setInterpretedFeature(feature);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

vector<Relationship> BoundaryFeatureInterpretation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractFeatureInterpretation::getAllEpcRelationships();

	vector<WellboreMarkerFrameRepresentation*> tmp;
	for (unsigned int i = 0; i < wellboreMarkerSet.size(); ++i)
	{
		bool alreadyInserted = (std::find(tmp.begin(), tmp.end(), wellboreMarkerSet[i]->getWellMarkerFrameRepresentation()) != tmp.end());
		if (!alreadyInserted)
		{
			Relationship rel(wellboreMarkerSet[i]->getWellMarkerFrameRepresentation()->getPartNameInEpcDocument(), "", wellboreMarkerSet[i]->getWellMarkerFrameRepresentation()->getUuid());
			rel.setSourceObjectType();
			result.push_back(rel);
			tmp.push_back(wellboreMarkerSet[i]->getWellMarkerFrameRepresentation());
		}
	}
        
	return result;
}

