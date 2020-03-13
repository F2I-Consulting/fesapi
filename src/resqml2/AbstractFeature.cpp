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
#include "AbstractFeature.h"

#include <stdexcept>
#include <algorithm>

using namespace RESQML2_NS;
using namespace std;

namespace {
	class DifferentFeature {
	private:
		COMMON_NS::AbstractObject const * obj;
	public:
		explicit DifferentFeature(COMMON_NS::AbstractObject const * obj_) : obj(obj_) {}

		bool operator()(AbstractFeatureInterpretation const * dataObj) const
		{
			COMMON_NS::DataObjectReference dor = dataObj->getInterpretedFeatureDor();
			return dor.getUuid() != obj->getUuid()
				|| dor.getVersion() != obj->getVersion();
		}
	};
}

std::vector<AbstractFeatureInterpretation *> AbstractFeature::getInterpretationSet() const
{
	std::vector<AbstractFeatureInterpretation *> result = getRepository()->getSourceObjects<AbstractFeatureInterpretation>(this);
	result.erase(std::remove_if(result.begin(), result.end(), DifferentFeature(this)), result.end());

	return result;
}

unsigned int AbstractFeature::getInterpretationCount() const
{
	const std::vector<AbstractFeatureInterpretation*>& interpretationSet = getInterpretationSet();

	if (interpretationSet.size() > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too many interpretations for this feature.");
	}

	return static_cast<unsigned int>(interpretationSet.size());
}

AbstractFeatureInterpretation *	AbstractFeature::getInterpretation(unsigned int index) const
{
	const std::vector<AbstractFeatureInterpretation*>& interpretationSet = getInterpretationSet();

	if (interpretationSet.size() > index) {
		return interpretationSet[index];
	}

	throw range_error("The interpretation index is out of the range of the interpretation set of the feature.");
}
