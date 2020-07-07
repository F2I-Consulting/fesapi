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

#include "AbstractFeatureInterpretation.h"

#include <algorithm>
#include <limits>
#include <stdexcept>

#include "AbstractFeature.h"
#include "GridConnectionSetRepresentation.h"
#include "LocalDepth3dCrs.h"
#include "LocalTime3dCrs.h"

using namespace RESQML2_NS;
using namespace std;

void AbstractFeatureInterpretation::setInterpretedFeature(AbstractFeature * feature)
{
	if (feature == nullptr) {
		throw invalid_argument("The interpreted feature cannot be null.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		if (static_cast<gsoap_resqml2_0_1::resqml20__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->InterpretedFeature != nullptr) {
			feature->getRepository()->deleteRelationship(this, getInterpretedFeature());
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		if (static_cast<gsoap_eml2_3::resqml22__AbstractFeatureInterpretation*>(gsoapProxy2_3)->InterpretedFeature != nullptr) {
			getRepository()->deleteRelationship(this, getInterpretedFeature());
		}
	}

	feature->getRepository()->addRelationship(this, feature);

	if (getRepository() == nullptr) {
		feature->getRepository()->addOrReplaceDataObject(this);
	}

	if (gsoapProxy2_0_1 != nullptr) {
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->InterpretedFeature = feature->newResqmlReference();
	}
	else if (gsoapProxy2_3 != nullptr) {
		static_cast<gsoap_eml2_3::resqml22__AbstractFeatureInterpretation*>(gsoapProxy2_3)->InterpretedFeature = feature->newEml23Reference();
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractFeatureInterpretation::loadTargetRelationships()
{
	COMMON_NS::DataObjectReference dor = getInterpretedFeatureDor();
	AbstractFeature* interpretedFeature = getRepository()->getDataObjectByUuid<AbstractFeature>(dor.getUuid());
	if (interpretedFeature == nullptr) { // partial transfer
		getRepository()->createPartial(dor);
		interpretedFeature = getRepository()->getDataObjectByUuid<AbstractFeature>(dor.getUuid());
	}
	if (interpretedFeature == nullptr) {
		throw invalid_argument("The DOR looks invalid.");
	}
	repository->addRelationship(this, interpretedFeature);
}

COMMON_NS::DataObjectReference AbstractFeatureInterpretation::getInterpretedFeatureDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->InterpretedFeature);
	}
	else if (gsoapProxy2_3 != nullptr) {
		return COMMON_NS::DataObjectReference(static_cast<gsoap_eml2_3::resqml22__AbstractFeatureInterpretation*>(gsoapProxy2_3)->InterpretedFeature);
	}

	throw logic_error("Not implemented yet");
}

AbstractFeature* AbstractFeatureInterpretation::getInterpretedFeature() const
{
	return repository->getDataObjectByUuid<AbstractFeature>(getInterpretedFeatureDor().getUuid());
}

gsoap_resqml2_0_1::resqml20__Domain AbstractFeatureInterpretation::initDomain(gsoap_resqml2_0_1::resqml20__Domain defaultDomain) const
{
	const unsigned int repCount = getRepresentationCount();
	bool isTimeDomain = false;
	bool isDepthDomain = false;
	for (unsigned int repIndex = 0; repIndex < repCount && (!isTimeDomain || !isDepthDomain); ++repIndex) {
		AbstractRepresentation const * rep = getRepresentation(repIndex);
		const unsigned int patchCount = rep->getPatchCount();
		for (unsigned int patchIndex = 0; patchIndex < patchCount && (!isTimeDomain || !isDepthDomain); ++patchIndex) {
			AbstractLocal3dCrs* local3dCrs = rep->getLocalCrs(patchIndex);
			if (local3dCrs != nullptr) {
				if (dynamic_cast<LocalTime3dCrs*>(local3dCrs) != nullptr) {
					isTimeDomain = true;
				}
				else if (dynamic_cast<LocalDepth3dCrs*>(local3dCrs) != nullptr) {
					isDepthDomain = true;
				}
			}
		}
	}

	if (gsoapProxy2_0_1 != nullptr) {
		if (isTimeDomain && isDepthDomain) {
			static_cast<gsoap_resqml2_0_1::resqml20__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->Domain = gsoap_resqml2_0_1::resqml20__Domain__mixed;
		}
		else if (!isTimeDomain && !isDepthDomain) {
			static_cast<gsoap_resqml2_0_1::resqml20__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->Domain = defaultDomain;
		}
		else if (isTimeDomain) {
			static_cast<gsoap_resqml2_0_1::resqml20__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->Domain = gsoap_resqml2_0_1::resqml20__Domain__time;
		}
		else {
			static_cast<gsoap_resqml2_0_1::resqml20__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->Domain = gsoap_resqml2_0_1::resqml20__Domain__depth;
		}

		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->Domain;
	}
	else if (gsoapProxy2_3 != nullptr) {

		if (static_cast<gsoap_eml2_3::resqml22__AbstractFeatureInterpretation*>(gsoapProxy2_3)->Domain == nullptr) {
			static_cast<gsoap_eml2_3::resqml22__AbstractFeatureInterpretation*>(gsoapProxy2_3)->Domain = static_cast<gsoap_eml2_3::resqml22__Domain*>(soap_malloc(gsoapProxy2_3->soap, sizeof(gsoap_eml2_3::resqml22__Domain)));
		}

		if (isTimeDomain && isDepthDomain) {
			*static_cast<gsoap_eml2_3::resqml22__AbstractFeatureInterpretation*>(gsoapProxy2_3)->Domain = gsoap_eml2_3::resqml22__Domain__mixed;
		}
		else if (!isTimeDomain && !isDepthDomain) {
			*static_cast<gsoap_eml2_3::resqml22__AbstractFeatureInterpretation*>(gsoapProxy2_3)->Domain = static_cast<gsoap_eml2_3::resqml22__Domain>(defaultDomain);
		}
		else if (isTimeDomain) {
			*static_cast<gsoap_eml2_3::resqml22__AbstractFeatureInterpretation*>(gsoapProxy2_3)->Domain = gsoap_eml2_3::resqml22__Domain__time;
		}
		else {
			*static_cast<gsoap_eml2_3::resqml22__AbstractFeatureInterpretation*>(gsoapProxy2_3)->Domain = gsoap_eml2_3::resqml22__Domain__depth;
		}

		return static_cast<gsoap_eml2_3::resqml22__AbstractFeatureInterpretation*>(gsoapProxy2_3)->Domain != nullptr
			? static_cast<gsoap_resqml2_0_1::resqml20__Domain>(*static_cast<gsoap_eml2_3::resqml22__AbstractFeatureInterpretation*>(gsoapProxy2_3)->Domain)
			: gsoap_resqml2_0_1::resqml20__Domain__mixed;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::resqml20__Domain AbstractFeatureInterpretation::getDomain() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->Domain;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_eml2_3::resqml22__AbstractFeatureInterpretation*>(gsoapProxy2_3)->Domain == nullptr
			? gsoap_resqml2_0_1::resqml20__Domain__mixed
			: static_cast<gsoap_resqml2_0_1::resqml20__Domain>(*static_cast<gsoap_eml2_3::resqml22__AbstractFeatureInterpretation*>(gsoapProxy2_3)->Domain);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

namespace {
	class DifferentInterp {
	private:
		AbstractFeatureInterpretation const * interp;
	public:
		explicit DifferentInterp(AbstractFeatureInterpretation const * interp_) : interp(interp_) {}

		bool operator()(AbstractRepresentation const * rep) const
		{
			COMMON_NS::DataObjectReference dor = rep->getInterpretationDor();
			return dor.isEmpty()
				|| dor.getUuid() != interp->getUuid()
				|| dor.getVersion() != interp->getVersion();
		}
	};
}

vector<AbstractRepresentation *> AbstractFeatureInterpretation::getRepresentationSet() const
{
	std::vector<AbstractRepresentation *> result = repository->getSourceObjects<AbstractRepresentation>(this);
	result.erase(std::remove_if(result.begin(), result.end(), DifferentInterp(this)), result.end());

	return result;
}

unsigned int AbstractFeatureInterpretation::getRepresentationCount() const
{
	size_t result = getRepresentationSet().size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("The representation count is superior to unsigned int max");
	}

	return static_cast<unsigned int>(result);
}

AbstractRepresentation * AbstractFeatureInterpretation::getRepresentation(unsigned int index) const
{
	const std::vector<AbstractRepresentation*>& representationSet = getRepresentationSet();

	if (representationSet.size() > index)
		return representationSet[index];
	
	throw out_of_range("The representation index you are requesting is out of range.");
}

std::vector<GridConnectionSetRepresentation *> AbstractFeatureInterpretation::getGridConnectionSetRepresentationSet() const
{
	return getRepository()->getSourceObjects<GridConnectionSetRepresentation>(this);
}
