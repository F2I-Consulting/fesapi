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
using namespace epc;

const char* StratigraphicColumn::XML_TAG = "StratigraphicColumn";

StratigraphicColumn::StratigraphicColumn(soap* soapContext, const std::string & guid, const std::string & title) :earthModel(nullptr)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREStratigraphicColumn(soapContext, 1);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());
}

void StratigraphicColumn::pushBackStratiColumnRank(StratigraphicColumnRankInterpretation * stratiColumnRank)
{
	// EPC
	stratigraphicColumnRankSet.push_back(stratiColumnRank);
	stratiColumnRank->stratigraphicColumnSet.push_back(this);

	// XML
	if (updateXml)
	{
		static_cast<_resqml2__StratigraphicColumn*>(gsoapProxy2_0_1)->Ranks.push_back(stratiColumnRank->newResqmlReference());
	}
}

vector<Relationship> StratigraphicColumn::getAllEpcRelationships() const
{
	vector<Relationship> result;

	for (unsigned int i = 0; i < stratigraphicColumnRankSet.size(); i++)
	{
		Relationship rel(stratigraphicColumnRankSet[i]->getPartNameInEpcDocument(), "", stratigraphicColumnRankSet[i]->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
        
    return result;
}

void StratigraphicColumn::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	updateXml = false;

	_resqml2__StratigraphicColumn* stratCol= static_cast<_resqml2__StratigraphicColumn*>(gsoapProxy2_0_1);

	for (unsigned int i = 0; i < stratCol->Ranks.size(); i++)
	{
		pushBackStratiColumnRank(static_cast<StratigraphicColumnRankInterpretation*>(epcDoc->getDataObjectByUuid(stratCol->Ranks[i]->UUID)));
	}

	updateXml = true;
}

