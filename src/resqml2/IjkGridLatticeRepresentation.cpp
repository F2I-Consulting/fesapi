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

#include "IjkGridLatticeRepresentation.h"

#include <stdexcept>

#include "AbstractFeature.h"
#include "AbstractFeatureInterpretation.h"
#include "AbstractLocal3dCrs.h"
#include "AbstractValuesProperty.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace RESQML2_NS;

bool IjkGridLatticeRepresentation::isASeismicCube() const
{
	// A Seismic cube is defined by an IjkGridRepresentation that has a feature of type SeismicLatticeFeature and that
	// has at least one continuous property (amplitude).
	bool atLeastOneContProp = false;
	vector<RESQML2_NS::AbstractValuesProperty *> allValuesProperty = getValuesPropertySet();
    for (size_t propIndex = 0; propIndex < allValuesProperty.size(); ++propIndex)
    {
        if (allValuesProperty[propIndex]->getXmlTag() == "ContinuousProperty")
        {
            atLeastOneContProp = true;
            break;
        }
    }
    if (!atLeastOneContProp)
        return false;

    return getInterpretation() != nullptr && getInterpretation()->getInterpretedFeature()->getXmlTag() == "SeismicLatticeFeature";
}

bool IjkGridLatticeRepresentation::isAFaciesCube() const
{
	// A Facies cube is defined by an IjkGridRepresentation that has a feature of type SeismicLatticeFeature and that
	// has at least one categorical property (facies).
	bool atLeastOneCateProp = false;
	vector<RESQML2_NS::AbstractValuesProperty *> allValuesProperty = getValuesPropertySet();
    for (size_t propIndex = 0; propIndex < allValuesProperty.size(); ++propIndex)
    {
        if (allValuesProperty[propIndex]->getXmlTag() == "CategoricalProperty")
        {
            atLeastOneCateProp = true;
            break;
        }
    }
    if (!atLeastOneCateProp)
        return false;

    return getInterpretation() != nullptr && getInterpretation()->getInterpretedFeature()->getXmlTag() == "SeismicLatticeFeature";
}

ULONG64 IjkGridLatticeRepresentation::getXyzPointCountOfPatch(unsigned int patchIndex) const
{
	if (patchIndex < getPatchCount())
	{
		return (getICellCount()+1) * (getJCellCount()+1) * (getKCellCount()+1);
	}
	
	throw out_of_range("An ijk grid has a maximum of one patch.");
}

void IjkGridLatticeRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double *) const
{
	if (patchIndex < getPatchCount())
	{
		throw logic_error("Not implemented yet. Please use lattice information.");
	}
	
	throw out_of_range("An ijk grid has a maximum of one patch.");
}

double IjkGridLatticeRepresentation::getXOriginInGlobalCrs() const
{
	double result[] = {getXOrigin(), getYOrigin(), .0};
	if (result[0] != result[0])
		return result[0];

	// Only one patch is allowed for an IJK Grid lattice
	getLocalCrs(0)->convertXyzPointsToGlobalCrs(result, 1);

	return result[0];
}

double IjkGridLatticeRepresentation::getYOriginInGlobalCrs() const
{
	double result[] = {getXOrigin(), getYOrigin(), .0};
	if (result[0] != result[0])
		return result[0];

	// Only one patch is allowed for an IJK Grid lattice
	getLocalCrs(0)->convertXyzPointsToGlobalCrs(result, 1);

	return result[1];
}

double IjkGridLatticeRepresentation::getZOriginInGlobalCrs() const
{
	double result = getZOrigin();
	if (result != result) {
		return result;
	}
	// Only one patch is allowed for an IJK Grid lattice
	RESQML2_NS::AbstractLocal3dCrs const * localCrs = getLocalCrs(0);
	if (localCrs->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCORELocalTime3dCrs) {
		return result;
	}

	return result + localCrs->getOriginDepthOrElevation();
}

AbstractIjkGridRepresentation::geometryKind IjkGridLatticeRepresentation::getGeometryKind() const
{
	return LATTICE;
}
