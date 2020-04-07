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
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* SeismicLatticeFeature::XML_TAG = "SeismicLatticeFeature";

SeismicLatticeFeature::SeismicLatticeFeature(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title,
	int inlineIncrement, int crosslineIncrement,
	unsigned int originInline, unsigned int originCrossline,
	unsigned int inlineCount, unsigned int crosslineCount)
{
	if (repo == nullptr)
		throw invalid_argument("The repo cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORESeismicLatticeFeature(repo->getGsoapContext());
	_resqml20__SeismicLatticeFeature* seismicLattice = static_cast<_resqml20__SeismicLatticeFeature*>(gsoapProxy2_0_1);

	seismicLattice->InlineIndexIncrement = inlineIncrement;
	seismicLattice->CrosslineIndexIncrement = crosslineIncrement;
	seismicLattice->FirstInlineIndex = originInline;
	seismicLattice->FirstCrosslineIndex = originCrossline;
	seismicLattice->InlineCount = inlineCount;
	seismicLattice->CrosslineCount = crosslineCount;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addOrReplaceDataObject(this);
}

int SeismicLatticeFeature::getCrosslineIncrement() const
{
	return static_cast<_resqml20__SeismicLatticeFeature*>(gsoapProxy2_0_1)->CrosslineIndexIncrement;
}
		
int SeismicLatticeFeature::getInlineIncrement() const
{
	return static_cast<_resqml20__SeismicLatticeFeature*>(gsoapProxy2_0_1)->InlineIndexIncrement;
}
		
int SeismicLatticeFeature::getOriginCrossline() const
{
	return static_cast<_resqml20__SeismicLatticeFeature*>(gsoapProxy2_0_1)->FirstCrosslineIndex;
}
		
int SeismicLatticeFeature::getOriginInline() const
{
	return static_cast<_resqml20__SeismicLatticeFeature*>(gsoapProxy2_0_1)->FirstInlineIndex;
}


