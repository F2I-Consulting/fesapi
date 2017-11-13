/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use,
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
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
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* PolylineRepresentation::XML_TAG = "PolylineRepresentation";

void PolylineRepresentation::init(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
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

PolylineRepresentation::PolylineRepresentation(resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed):
	AbstractRepresentation(nullptr, crs)
{
	init(nullptr, crs, guid, title, isClosed);
}

PolylineRepresentation::PolylineRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed):
	AbstractRepresentation(interp, crs)
{
	init(interp, crs, guid, title, isClosed);
}

PolylineRepresentation::PolylineRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, const resqml2__LineRole & roleKind,
			bool isClosed):
	AbstractRepresentation(interp, crs)
{
	init(interp, crs, guid, title, isClosed);
	static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy2_0_1)->LineRole = (resqml2__LineRole*)soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml2__LineRole));
	(*static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy2_0_1)->LineRole) = roleKind;
}

std::string PolylineRepresentation::getHdfProxyUuid() const
{
	return getHdfProxyUuidFromPointGeometryPatch(getPointGeometry2_0_1(0));
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

void PolylineRepresentation::setGeometry(double * points, const unsigned int & pointCount, common::AbstractHdfProxy * proxy)
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
	return static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy2_0_1)->LineRole;
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
	vector<resqml2::AbstractValuesProperty*> allValuesProperty = getValuesPropertySet();
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
	vector<resqml2::AbstractValuesProperty*> allValuesProperty = getValuesPropertySet();
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

vector<Relationship> PolylineRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractRepresentation::getAllEpcRelationships();

	// Outer rings of
	for(unsigned int i = 0; i < outerRingOfSet.size(); ++i)
	{
		Relationship relOuterRingOf(outerRingOfSet[i]->getPartNameInEpcDocument(), "", outerRingOfSet[i]->getUuid());
		relOuterRingOf.setSourceObjectType();
		result.push_back(relOuterRingOf);
	}

	// Inner rings of
	for(unsigned int i = 0; i < innerRingOfSet.size(); ++i)
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
