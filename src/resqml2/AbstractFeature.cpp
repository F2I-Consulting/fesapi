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
#include "resqml2/AbstractFeature.h"

#include <stdexcept>

using namespace RESQML2_NS;
using namespace std;
using namespace epc;

std::vector<AbstractFeatureInterpretation*> AbstractFeature::getInterpretationSet() const
{
	return interpretationSet;
}

unsigned int AbstractFeature::getInterpretationCount() const
{
	if (interpretationSet.size() > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too many interpretations for this feature.");
	}

	return static_cast<unsigned int>(interpretationSet.size());
}

AbstractFeatureInterpretation*	AbstractFeature::getInterpretation(unsigned int index) const
{
	if (interpretationSet.size() > index) {
		return interpretationSet[index];
	}

	throw range_error("The interpretation index is out of the range of the interpretation set of the feature.");
}

vector<Relationship> AbstractFeature::getAllSourceRelationships() const
{
	vector<Relationship> result;

	for (size_t i = 0; i < interpretationSet.size(); ++i) {
		Relationship rel(interpretationSet[i]->getPartNameInEpcDocument(), "", interpretationSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

vector<Relationship> AbstractFeature::getAllTargetRelationships() const
{
	vector<Relationship> result;
	return result;
}
