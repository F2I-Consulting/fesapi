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
#include "resqml2_0_1/PlaneSetRepresentation.h"

#include <stdexcept>
#include <sstream>
#include <algorithm>

#include "resqml2/AbstractFeatureInterpretation.h"
#include "resqml2/AbstractLocal3dCrs.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

const char* PlaneSetRepresentation::XML_TAG = "PlaneSetRepresentation";

PlaneSetRepresentation::PlaneSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title):
	AbstractRepresentation(interp, crs)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREPlaneSetRepresentation(interp->getGsoapContext(), 1);
	_resqml2__PlaneSetRepresentation* plSetRep = static_cast<_resqml2__PlaneSetRepresentation*>(gsoapProxy2_0_1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	// relationhsips
	localCrs = crs;
	localCrs->addRepresentation(this);

	setInterpretation(interp);
}

void PlaneSetRepresentation::pushBackHorizontalPlaneGeometryPatch(const double & zCoordinate)
{
	resqml2__HorizontalPlaneGeometry* patch = soap_new_resqml2__HorizontalPlaneGeometry(gsoapProxy2_0_1->soap, 1);
	patch->LocalCrs = localCrs->newResqmlReference();
	patch->Coordinate = zCoordinate;

	static_cast<_resqml2__PlaneSetRepresentation*>(gsoapProxy2_0_1)->Planes.push_back(patch);
}

void PlaneSetRepresentation::pushBackTiltedPlaneGeometryPatch(
	const double & x1, const double & y1, const double & z1,
	const double & x2, const double & y2, const double & z2,
	const double & x3, const double & y3, const double & z3)
{
	resqml2__TiltedPlaneGeometry* patch = soap_new_resqml2__TiltedPlaneGeometry(gsoapProxy2_0_1->soap, 1);
	patch->LocalCrs = localCrs->newResqmlReference();

	patch->Plane.push_back(soap_new_resqml2__ThreePoint3d(gsoapProxy2_0_1->soap, 1));
	patch->Plane[0]->Point3d.push_back(soap_new_resqml2__Point3d(gsoapProxy2_0_1->soap, 1));
	patch->Plane[0]->Point3d[0]->Coordinate1 = x1;
	patch->Plane[0]->Point3d[0]->Coordinate2 = y1;
	patch->Plane[0]->Point3d[0]->Coordinate3 = z1;
	patch->Plane[0]->Point3d.push_back(soap_new_resqml2__Point3d(gsoapProxy2_0_1->soap, 1));
	patch->Plane[0]->Point3d[1]->Coordinate1 = x2;
	patch->Plane[0]->Point3d[1]->Coordinate2 = y2;
	patch->Plane[0]->Point3d[1]->Coordinate3 = z2;
	patch->Plane[0]->Point3d.push_back(soap_new_resqml2__Point3d(gsoapProxy2_0_1->soap, 1));
	patch->Plane[0]->Point3d[2]->Coordinate1 = x3;
	patch->Plane[0]->Point3d[2]->Coordinate2 = y3;
	patch->Plane[0]->Point3d[2]->Coordinate3 = z3;

	static_cast<_resqml2__PlaneSetRepresentation*>(gsoapProxy2_0_1)->Planes.push_back(patch);
}

ULONG64 PlaneSetRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	_resqml2__PlaneSetRepresentation* rep = static_cast<_resqml2__PlaneSetRepresentation*>(gsoapProxy2_0_1);
	if (rep->Planes[patchIndex]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__HorizontalPlaneGeometry)
	{
		return 1;
	}
	else
	{
		return static_cast<resqml2__TiltedPlaneGeometry*>(rep->Planes[patchIndex])->Plane.size() * 3;
	}
}

void PlaneSetRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index patch is not in the allowed range of patch");

	_resqml2__PlaneSetRepresentation* rep = static_cast<_resqml2__PlaneSetRepresentation*>(gsoapProxy2_0_1);
	if (rep->Planes[patchIndex]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__HorizontalPlaneGeometry)
	{
		xyzPoints[0] = numeric_limits<double>::quiet_NaN();
		xyzPoints[1] = numeric_limits<double>::quiet_NaN();
		xyzPoints[2] = static_cast<resqml2__HorizontalPlaneGeometry*>(rep->Planes[patchIndex])->Coordinate;
	}
	else
	{
		resqml2__TiltedPlaneGeometry* tiltedPlane = static_cast<resqml2__TiltedPlaneGeometry*>(rep->Planes[patchIndex]); // TODO : allow more than one plane in one tilted plane
		xyzPoints[0] = tiltedPlane->Plane[0]->Point3d[0]->Coordinate1;
		xyzPoints[1] = tiltedPlane->Plane[0]->Point3d[0]->Coordinate2;
		xyzPoints[2] = tiltedPlane->Plane[0]->Point3d[0]->Coordinate3;
		xyzPoints[3] = tiltedPlane->Plane[1]->Point3d[1]->Coordinate1;
		xyzPoints[4] = tiltedPlane->Plane[1]->Point3d[1]->Coordinate2;
		xyzPoints[5] = tiltedPlane->Plane[1]->Point3d[1]->Coordinate3;
		xyzPoints[6] = tiltedPlane->Plane[2]->Point3d[2]->Coordinate1;
		xyzPoints[7] = tiltedPlane->Plane[2]->Point3d[2]->Coordinate2;
		xyzPoints[8] = tiltedPlane->Plane[2]->Point3d[2]->Coordinate3;
	}
}

unsigned int PlaneSetRepresentation::getPatchCount() const
{
    return static_cast<_resqml2__PlaneSetRepresentation*>(gsoapProxy2_0_1)->Planes.size();
}
