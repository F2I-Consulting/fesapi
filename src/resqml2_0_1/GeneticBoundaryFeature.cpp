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
#include "GeneticBoundaryFeature.h"

using namespace std;
using namespace RESQML2_0_1_NS;

const char* GeneticBoundaryFeature::XML_TAG = "GeneticBoundaryFeature";

GeneticBoundaryFeature::GeneticBoundaryFeature(COMMON_NS::DataObjectRepository * repo, const string & guid, const string & title, bool isAnHorizon)
{
	if (repo == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_0_1 = gsoap_resqml2_0_1::soap_new_resqml20__obj_USCOREGeneticBoundaryFeature(repo->getGsoapContext());
	gsoap_resqml2_0_1::_resqml20__GeneticBoundaryFeature* horizon = static_cast<gsoap_resqml2_0_1::_resqml20__GeneticBoundaryFeature*>(gsoapProxy2_0_1);
	horizon->GeneticBoundaryKind = isAnHorizon ? gsoap_resqml2_0_1::resqml20__GeneticBoundaryKind::horizon : gsoap_resqml2_0_1::resqml20__GeneticBoundaryKind::geobody_x0020boundary;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
}

bool GeneticBoundaryFeature::isAnHorizon() const
{
	cannotBePartial();
	return static_cast<gsoap_resqml2_0_1::_resqml20__GeneticBoundaryFeature*>(gsoapProxy2_0_1)->GeneticBoundaryKind == gsoap_resqml2_0_1::resqml20__GeneticBoundaryKind::horizon;
}

void GeneticBoundaryFeature::setAge(unsigned int age)
{
	gsoap_resqml2_0_1::_resqml20__GeneticBoundaryFeature* feature = static_cast<gsoap_resqml2_0_1::_resqml20__GeneticBoundaryFeature*>(gsoapProxy2_0_1);
	if (!hasAnAge()) {
		feature->AbsoluteAge = gsoap_resqml2_0_1::soap_new_resqml20__Timestamp(getGsoapContext());
		feature->AbsoluteAge->DateTime.tm_mday = 1;
	}
	if (feature->AbsoluteAge->YearOffset == nullptr) {
		feature->AbsoluteAge->YearOffset = static_cast<int64_t*>(soap_malloc(getGsoapContext(), sizeof(int64_t)));
	}

	*(feature->AbsoluteAge->YearOffset) = -static_cast<int64_t>(age);
}

bool GeneticBoundaryFeature::hasAnAge() const
{
	cannotBePartial();
	return static_cast<gsoap_resqml2_0_1::_resqml20__GeneticBoundaryFeature*>(gsoapProxy2_0_1)->AbsoluteAge != nullptr;
}

uint64_t GeneticBoundaryFeature::getAge() const
{
	if (!hasAnAge()) {
		throw invalid_argument("This feature has not an age.");
	}

	return abs(*(static_cast<gsoap_resqml2_0_1::_resqml20__GeneticBoundaryFeature*>(gsoapProxy2_0_1)->AbsoluteAge->YearOffset));
}
