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
#include "SeismicLatticeFeature.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* SeismicLatticeFeature::XML_NS = "resqml22";

SeismicLatticeFeature::SeismicLatticeFeature(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title,
	int inlineIncrement, int crosslineIncrement,
	unsigned int originInline, unsigned int originCrossline,
	unsigned int inlineCount, unsigned int crosslineCount)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__SeismicLatticeFeature(repo->getGsoapContext());
	_resqml22__SeismicLatticeFeature* seismicLattice = static_cast<_resqml22__SeismicLatticeFeature*>(gsoapProxy2_3);

	seismicLattice->InlineLabels = soap_new_eml23__IntegerLatticeArray(repo->getGsoapContext());
	seismicLattice->InlineLabels->StartValue = originInline;
	auto inlineDef = soap_new_eml23__IntegerConstantArray(repo->getGsoapContext());
	inlineDef->Value = inlineIncrement;
	inlineDef->Count = inlineCount - 1;
	seismicLattice->InlineLabels->Offset.push_back(inlineDef);
	
	seismicLattice->CrosslineLabels = soap_new_eml23__IntegerLatticeArray(repo->getGsoapContext());
	seismicLattice->CrosslineLabels->StartValue = originCrossline;
	auto crosslineDef = soap_new_eml23__IntegerConstantArray(repo->getGsoapContext());
	crosslineDef->Value = crosslineIncrement;
	crosslineDef->Count = crosslineCount - 1;
	seismicLattice->CrosslineLabels->Offset.push_back(crosslineDef);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(this);
}

int SeismicLatticeFeature::getCrosslineIncrement() const
{
	return static_cast<_resqml22__SeismicLatticeFeature*>(gsoapProxy2_3)->CrosslineLabels->Offset[0]->Value;
}
		
int SeismicLatticeFeature::getInlineIncrement() const
{
	return static_cast<_resqml22__SeismicLatticeFeature*>(gsoapProxy2_3)->InlineLabels->Offset[0]->Value;
}
		
int SeismicLatticeFeature::getOriginCrossline() const
{
	return static_cast<_resqml22__SeismicLatticeFeature*>(gsoapProxy2_3)->CrosslineLabels->StartValue;
}
		
int SeismicLatticeFeature::getOriginInline() const
{
	return static_cast<_resqml22__SeismicLatticeFeature*>(gsoapProxy2_3)->InlineLabels->StartValue;
}


