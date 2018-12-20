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
#include "resqml2_0_1/PolylineRepresentation.h"

#include <stdexcept>

#include "H5public.h"

#include "resqml2/AbstractFeature.h"
#include "resqml2/AbstractFeatureInterpretation.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "resqml2/AbstractValuesProperty.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* PolylineRepresentation::XML_TAG = "PolylineRepresentation";

void PolylineRepresentation::init(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed)
{
	if (crs == nullptr) {
		throw invalid_argument("The CRS of a polyline representation cannot be null");
	}

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREPolylineRepresentation(crs->getGsoapContext(), 1);
	_resqml2__PolylineRepresentation* polylineRep = static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy2_0_1);

	polylineRep->IsClosed = isClosed;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	// relationships
	localCrs = crs;
	localCrs->addRepresentation(this);

	if (interp != nullptr) {
		setInterpretation(interp);
	}
}

PolylineRepresentation::PolylineRepresentation(RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed):
	AbstractRepresentation(nullptr, crs)
{
	init(nullptr, crs, guid, title, isClosed);
}

PolylineRepresentation::PolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed):
	AbstractRepresentation(interp, crs)
{
	init(interp, crs, guid, title, isClosed);
}

PolylineRepresentation::PolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, const resqml2__LineRole & roleKind,
			bool isClosed):
	AbstractRepresentation(interp, crs)
{
	init(interp, crs, guid, title, isClosed);
	static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy2_0_1)->LineRole = (resqml2__LineRole*)soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml2__LineRole));
	(*static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy2_0_1)->LineRole) = roleKind;
}

gsoap_resqml2_0_1::eml20__DataObjectReference* PolylineRepresentation::getHdfProxyDor() const
{
	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

resqml2__PointGeometry* PolylineRepresentation::getPointGeometry2_0_1(const unsigned int & patchIndex) const
{
	if (patchIndex == 0)
		return static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy2_0_1)->NodePatch->Geometry;
	else
		return nullptr;
}

ULONG64 PolylineRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index of the patch is not in the allowed range of patch.");

	return static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy2_0_1)->NodePatch->Count;
}

void PolylineRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index of the patch is not in the allowed range of patch.");

	resqml2__PointGeometry* pointGeom = getPointGeometry2_0_1(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dHdf5Array)
	{
		hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__Point3dHdf5Array*>(pointGeom->Points)->Coordinates->PathInHdfFile, xyzPoints);
	}
	else
		throw invalid_argument("The geometry of the representation either does not exist or it is not an explicit one.");
}

void PolylineRepresentation::setGeometry(double * points, const unsigned int & pointCount, COMMON_NS::AbstractHdfProxy * proxy)
{
	_resqml2__PolylineRepresentation* polylineRep = static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy2_0_1);
	polylineRep->NodePatch = soap_new_resqml2__NodePatch(gsoapProxy2_0_1->soap, 1);
	polylineRep->NodePatch->Count = pointCount;
	polylineRep->NodePatch->PatchIndex = 0;

	hsize_t pointCountDims[] = {pointCount};
	polylineRep->NodePatch->Geometry = createPointGeometryPatch2_0_1(0, points, pointCountDims, 1, proxy);
}

bool PolylineRepresentation::isClosed() const
{
	return static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy2_0_1)->IsClosed;
}

bool PolylineRepresentation::hasALineRole() const
{
	return static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy2_0_1)->LineRole != nullptr;
}

gsoap_resqml2_0_1::resqml2__LineRole PolylineRepresentation::getLineRole() const
{
	if (!hasALineRole())
		throw invalid_argument("The polyline doesn't have any role");

	return *(static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy2_0_1)->LineRole);
}

bool PolylineRepresentation::isASeismicLine() const
{
	// A Seismic line is defined by an PolylineRepresentation that has a feature of type SeismicLineFeature and that
	// has at least one continuous property (amplitude).
	bool atLeastOneContProp = false;
	vector<RESQML2_NS::AbstractValuesProperty*> allValuesProperty = getValuesPropertySet();
    for (unsigned int propIndex = 0; propIndex < allValuesProperty.size(); ++propIndex)
    {
        if (allValuesProperty[propIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREContinuousProperty)
        {
            atLeastOneContProp = true;
            break;
        }
    }
    if (!atLeastOneContProp)
        return false;

	return getInterpretation() && getInterpretation()->getInterpretedFeature()->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORESeismicLineFeature;
}

bool PolylineRepresentation::isAFaciesLine() const
{
	// A Facies line is defined by an PolylineRepresentation that has a feature of type SeismicLineFeature and that
	// has at least one categorical property (facies).
	bool atLeastOneCateProp = false;
	vector<RESQML2_NS::AbstractValuesProperty*> allValuesProperty = getValuesPropertySet();
    for (unsigned int propIndex = 0; propIndex < allValuesProperty.size(); ++propIndex)
    {
        if (allValuesProperty[propIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECategoricalProperty)
        {
            atLeastOneCateProp = true;
            break;
        }
    }
    if (!atLeastOneCateProp)
        return false;

	return getInterpretation() && getInterpretation()->getInterpretedFeature()->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORESeismicLineFeature;
}

vector<Relationship> PolylineRepresentation::getAllSourceRelationships() const
{
	vector<Relationship> result = AbstractRepresentation::getAllSourceRelationships();

	// Outer rings of
	for(size_t i = 0; i < outerRingOfSet.size(); ++i)
	{
		Relationship relOuterRingOf(outerRingOfSet[i]->getPartNameInEpcDocument(), "", outerRingOfSet[i]->getUuid());
		relOuterRingOf.setSourceObjectType();
		result.push_back(relOuterRingOf);
	}

	// Inner rings of
	for(size_t i = 0; i < innerRingOfSet.size(); ++i)
	{
		Relationship relInnerRingOf(innerRingOfSet[i]->getPartNameInEpcDocument(), "", innerRingOfSet[i]->getUuid());
		relInnerRingOf.setSourceObjectType();
		result.push_back(relInnerRingOf);
	}

	return result;
}

void PolylineRepresentation::setLineRole(const gsoap_resqml2_0_1::resqml2__LineRole & lineRole)
{
	if (hasALineRole() == false)
		static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy2_0_1)->LineRole = (resqml2__LineRole*)soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml2__LineRole));

	(*static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy2_0_1)->LineRole) = lineRole;
}

