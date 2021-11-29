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
#include "PolylineRepresentation.h"

#include <stdexcept>

#include "AbstractSeismicLineFeature.h"
#include "AbstractFeatureInterpretation.h"
#include "ContinuousProperty.h"
#include "DiscreteProperty.h"

using namespace std;
using namespace RESQML2_NS;

const char* PolylineRepresentation::XML_TAG = "PolylineRepresentation";

bool PolylineRepresentation::isASeismicLine() const
{
	// A Seismic line is defined by an PolylineRepresentation that has a feature of type SeismicLineFeature and that
	// has at least one continuous property (amplitude).
	bool atLeastOneContProp = false;
	vector<RESQML2_NS::AbstractValuesProperty *> allValuesProperty = getValuesPropertySet();
    for (size_t propIndex = 0; propIndex < allValuesProperty.size(); ++propIndex) {
        if (dynamic_cast<RESQML2_NS::ContinuousProperty*>(allValuesProperty[propIndex]) != nullptr)  {
            atLeastOneContProp = true;
            break;
        }
    }
	if (!atLeastOneContProp) {
		return false;
	}

	auto interp = getInterpretation();
    return interp != nullptr && dynamic_cast<RESQML2_NS::AbstractSeismicLineFeature*>(interp->getInterpretedFeature()) != nullptr;
}

bool PolylineRepresentation::isAFaciesLine() const
{
	// A Facies line is defined by an PolylineRepresentation that has a feature of type SeismicLineFeature and that
	// has at least one categorical property (facies).
	bool atLeastOneCateProp = false;
	vector<RESQML2_NS::AbstractValuesProperty *> allValuesProperty = getValuesPropertySet();
    for (size_t propIndex = 0; propIndex < allValuesProperty.size(); ++propIndex) {
		auto* discretProp = dynamic_cast<RESQML2_NS::DiscreteProperty*>(allValuesProperty[propIndex]);
        if (discretProp != nullptr && !discretProp->getLookupDor().isEmpty()) {
            atLeastOneCateProp = true;
            break;
        }
    }
    if (!atLeastOneCateProp)
        return false;

	auto interp = getInterpretation();
	return interp != nullptr && dynamic_cast<RESQML2_NS::AbstractSeismicLineFeature*>(interp->getInterpretedFeature()) != nullptr;
}
