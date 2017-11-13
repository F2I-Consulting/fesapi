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
#include "resqml2_0_1/PointSetRepresentation.h"

#include <stdexcept>

#include "H5public.h"

#include "resqml2/AbstractFeatureInterpretation.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

const char* PointSetRepresentation::XML_TAG = "PointSetRepresentation";

PointSetRepresentation::PointSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title):
	AbstractRepresentation(interp, crs)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREPointSetRepresentation(interp->getGsoapContext(), 1);
	_resqml2__PointSetRepresentation* rep = static_cast<_resqml2__PointSetRepresentation*>(gsoapProxy2_0_1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	// relationhsips
	localCrs = crs;
	localCrs->addRepresentation(this);

	setInterpretation(interp);
}

void PointSetRepresentation::pushBackGeometryPatch(
	const unsigned int & xyzPointCount, double * xyzPoints,
	common::AbstractHdfProxy * proxy)
{
	resqml2__NodePatch* patch = soap_new_resqml2__NodePatch(gsoapProxy2_0_1->soap, 1);
	patch->PatchIndex = static_cast<_resqml2__PointSetRepresentation*>(gsoapProxy2_0_1)->NodePatch.size();
	patch->Count = xyzPointCount;

	// XYZ points
	hsize_t pointCountDims[] = {xyzPointCount};
	patch->Geometry = createPointGeometryPatch2_0_1(patch->PatchIndex, xyzPoints, pointCountDims, 1, proxy);

	static_cast<_resqml2__PointSetRepresentation*>(gsoapProxy2_0_1)->NodePatch.push_back(patch);
}

string PointSetRepresentation::getHdfProxyUuid() const
{
	return getHdfProxyUuidFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

resqml2__PointGeometry* PointSetRepresentation::getPointGeometry2_0_1(const unsigned int & patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}
	
	return static_cast<_resqml2__PointSetRepresentation*>(gsoapProxy2_0_1)->NodePatch[patchIndex]->Geometry;
}

ULONG64 PointSetRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	return static_cast<_resqml2__PointSetRepresentation*>(gsoapProxy2_0_1)->NodePatch[patchIndex]->Count;
}

void PointSetRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
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

unsigned int PointSetRepresentation::getPatchCount() const
{
    return static_cast<_resqml2__PointSetRepresentation*>(gsoapProxy2_0_1)->NodePatch.size();
}

