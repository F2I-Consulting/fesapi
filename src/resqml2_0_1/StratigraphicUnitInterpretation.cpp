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
#include "resqml2_0_1/StratigraphicUnitInterpretation.h"

#include <stdexcept>

#include "resqml2_0_1/StratigraphicUnitFeature.h"
#include "resqml2_0_1/StratigraphicColumnRankInterpretation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* StratigraphicUnitInterpretation::XML_TAG = "StratigraphicUnitInterpretation";

StratigraphicUnitInterpretation::StratigraphicUnitInterpretation(StratigraphicUnitFeature * feature, const string & guid, const string & title)
{
	if (!feature)
		throw invalid_argument("The interpreted feature cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREStratigraphicUnitInterpretation(feature->getGsoapContext(), 1);
	static_cast<_resqml2__StratigraphicUnitInterpretation*>(gsoapProxy2_0_1)->Domain = resqml2__Domain__mixed;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	setInterpretedFeature(feature);
}

vector<Relationship> StratigraphicUnitInterpretation::getAllSourceRelationships() const
{
	vector<Relationship> result = AbstractFeatureInterpretation::getAllSourceRelationships();

	for (size_t i = 0; i < stratigraphicColumnRankSet.size(); ++i)
	{
		if (stratigraphicColumnRankSet[i] != nullptr)
		{
			Relationship rel(stratigraphicColumnRankSet[i]->getPartNameInEpcDocument(), "", stratigraphicColumnRankSet[i]->getUuid());
			rel.setSourceObjectType();
			result.push_back(rel);
		}
		else
			throw domain_error("The stratigraphicColumnRank Interpretation associated to this interpretation cannot be nullptr.");
	}

	return result;
}

bool StratigraphicUnitInterpretation::hasDepositionMode() const
{
	return static_cast<_resqml2__StratigraphicUnitInterpretation*>(gsoapProxy2_0_1)->DepositionMode != nullptr;
}

gsoap_resqml2_0_1::resqml2__DepositionMode StratigraphicUnitInterpretation::getDepositionMode() const
{
	if (hasDepositionMode() == false)
		throw invalid_argument("The stratigraphic unit interpretation has not any deposition mode.");

	return *static_cast<_resqml2__StratigraphicUnitInterpretation*>(gsoapProxy2_0_1)->DepositionMode;
}

