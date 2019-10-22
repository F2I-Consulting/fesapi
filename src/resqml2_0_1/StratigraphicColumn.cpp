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
#include "resqml2_0_1/StratigraphicColumn.h"

#include "resqml2_0_1/StratigraphicColumnRankInterpretation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* StratigraphicColumn::XML_TAG = "StratigraphicColumn";

StratigraphicColumn::StratigraphicColumn(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREStratigraphicColumn(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addOrReplaceDataObject(this);
}

void StratigraphicColumn::pushBackStratiColumnRank(StratigraphicColumnRankInterpretation * stratiColumnRank)
{
	getRepository()->addRelationship(this, stratiColumnRank);

	static_cast<_resqml20__StratigraphicColumn*>(gsoapProxy2_0_1)->Ranks.push_back(stratiColumnRank->newResqmlReference());
}

std::vector<class StratigraphicColumnRankInterpretation *> StratigraphicColumn::getStratigraphicColumnRankInterpretationSet() const
{
	return getRepository()->getTargetObjects<StratigraphicColumnRankInterpretation>(this);
}

void StratigraphicColumn::loadTargetRelationships()
{
	const std::vector<eml20__DataObjectReference *>& stratColRanks= static_cast<_resqml20__StratigraphicColumn*>(gsoapProxy2_0_1)->Ranks;
	for (size_t i = 0; i < stratColRanks.size(); ++i) {
		gsoap_resqml2_0_1::eml20__DataObjectReference const * dor = stratColRanks[i];
		if (dor != nullptr) {
			convertDorIntoRel<StratigraphicColumnRankInterpretation>(dor);
		}
	}
}
