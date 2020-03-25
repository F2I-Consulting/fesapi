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

#include "H5public.h"

#include "../resqml2/AbstractFeature.h"
#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../resqml2/AbstractLocal3dCrs.h"
#include "../resqml2/AbstractValuesProperty.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* PolylineRepresentation::XML_TAG = "PolylineRepresentation";

void PolylineRepresentation::init(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, bool isClosed)
{
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREPolylineRepresentation(repo->getGsoapContext());
	_resqml20__PolylineRepresentation* polylineRep = static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1);

	polylineRep->IsClosed = isClosed;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addOrReplaceDataObject(this);
}

PolylineRepresentation::PolylineRepresentation(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, bool isClosed)
{
	init(repo, guid, title, isClosed);
}

PolylineRepresentation::PolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title, bool isClosed)
{
	if (interp == nullptr) {
		throw invalid_argument("You must provide an interpretation");
	}
	init(interp->getRepository(), guid, title, isClosed);

	setInterpretation(interp);
}

PolylineRepresentation::PolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title, resqml20__LineRole roleKind,
	bool isClosed)
{
	if (interp == nullptr) {
		throw invalid_argument("You must provide an interpretation");
	}
	init(interp->getRepository(), guid, title, isClosed);
	static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1)->LineRole = (resqml20__LineRole*)soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml20__LineRole));
	(*static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1)->LineRole) = roleKind;

	setInterpretation(interp);
}

COMMON_NS::DataObjectReference PolylineRepresentation::getHdfProxyDor() const
{
	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

resqml20__PointGeometry* PolylineRepresentation::getPointGeometry2_0_1(unsigned int patchIndex) const
{
	if (patchIndex == 0)
		return static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1)->NodePatch->Geometry;
	else
		return nullptr;
}

ULONG64 PolylineRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index of the patch is not in the allowed range of patch.");

	return static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1)->NodePatch->Count;
}

void PolylineRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index of the patch is not in the allowed range of patch.");

	resqml20__PointGeometry* pointGeom = getPointGeometry2_0_1(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array)
	{
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__Point3dHdf5Array*>(pointGeom->Points)->Coordinates;
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, xyzPoints);
	}
	else
		throw invalid_argument("The geometry of the representation either does not exist or it is not an explicit one.");
}

void PolylineRepresentation::setGeometry(double * points, unsigned int pointCount, EML2_NS::AbstractHdfProxy * proxy, RESQML2_NS::AbstractLocal3dCrs* localCrs)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}

	_resqml20__PolylineRepresentation* polylineRep = static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1);
	polylineRep->NodePatch = soap_new_resqml20__NodePatch(gsoapProxy2_0_1->soap);
	polylineRep->NodePatch->Count = pointCount;
	polylineRep->NodePatch->PatchIndex = 0;

	hsize_t pointCountDims[] = {pointCount};
	polylineRep->NodePatch->Geometry = createPointGeometryPatch2_0_1(0, points, localCrs, pointCountDims, 1, proxy);
	getRepository()->addRelationship(this, localCrs);
}

bool PolylineRepresentation::isClosed() const
{
	return static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1)->IsClosed;
}

bool PolylineRepresentation::hasALineRole() const
{
	return static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1)->LineRole != nullptr;
}

gsoap_resqml2_0_1::resqml20__LineRole PolylineRepresentation::getLineRole() const
{
	if (!hasALineRole())
		throw invalid_argument("The polyline doesn't have any role");

	return *(static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1)->LineRole);
}

bool PolylineRepresentation::isASeismicLine() const
{
	// A Seismic line is defined by an PolylineRepresentation that has a feature of type SeismicLineFeature and that
	// has at least one continuous property (amplitude).
	bool atLeastOneContProp = false;
	vector<RESQML2_NS::AbstractValuesProperty *> allValuesProperty = getValuesPropertySet();
    for (unsigned int propIndex = 0; propIndex < allValuesProperty.size(); ++propIndex)
    {
        if (allValuesProperty[propIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCOREContinuousProperty)
        {
            atLeastOneContProp = true;
            break;
        }
    }
	if (!atLeastOneContProp) {
		return false;
	}

    return getInterpretation() && getInterpretation()->getInterpretedFeature()->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCORESeismicLineFeature;
}

bool PolylineRepresentation::isAFaciesLine() const
{
	// A Facies line is defined by an PolylineRepresentation that has a feature of type SeismicLineFeature and that
	// has at least one categorical property (facies).
	bool atLeastOneCateProp = false;
	vector<RESQML2_NS::AbstractValuesProperty *> allValuesProperty = getValuesPropertySet();
    for (unsigned int propIndex = 0; propIndex < allValuesProperty.size(); ++propIndex)
    {
        if (allValuesProperty[propIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCORECategoricalProperty)
        {
            atLeastOneCateProp = true;
            break;
        }
    }
    if (!atLeastOneCateProp)
        return false;

    return getInterpretation() && getInterpretation()->getInterpretedFeature()->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCORESeismicLineFeature;
}

void PolylineRepresentation::setLineRole(gsoap_resqml2_0_1::resqml20__LineRole lineRole)
{
	if (!hasALineRole())
		static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1)->LineRole = (resqml20__LineRole*)soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml20__LineRole));

	(*static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1)->LineRole) = lineRole;
}
