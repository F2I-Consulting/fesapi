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
#include "resqml2_0_1/PlaneSetRepresentation.h"

#include <stdexcept>
#include <sstream>
#include <algorithm>

#include "resqml2/AbstractFeatureInterpretation.h"
#include "resqml2/AbstractLocal3dCrs.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* PlaneSetRepresentation::XML_TAG = "PlaneSetRepresentation";

PlaneSetRepresentation::PlaneSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title):
	AbstractRepresentation(interp, crs)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREPlaneSetRepresentation(interp->getGsoapContext(), 1);

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

