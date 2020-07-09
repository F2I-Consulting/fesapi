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
#include "PlaneSetRepresentation.h"

#include <algorithm>
#include <limits>
#include <stdexcept>
#include <sstream>

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../resqml2/AbstractLocal3dCrs.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* PlaneSetRepresentation::XML_NS = "resqml22";

PlaneSetRepresentation::PlaneSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
		const std::string & guid, const std::string & title)
{
	if (interp == nullptr) {
		throw invalid_argument("You must provide an interpretation");
	}

	gsoapProxy2_3 = soap_new_resqml22__PlaneSetRepresentation(interp->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setInterpretation(interp);
}

COMMON_NS::DataObjectReference PlaneSetRepresentation::getLocalCrsDor(unsigned int patchIndex) const
{
	_resqml22__PlaneSetRepresentation* rep = static_cast<_resqml22__PlaneSetRepresentation*>(gsoapProxy2_3);
	eml23__DataObjectReference* result = rep->Planes[patchIndex]->LocalCrs;
	for (size_t geomIndex = 1; geomIndex < rep->Planes.size(); ++geomIndex) {
		if (result->Uuid != rep->Planes[geomIndex]->LocalCrs->Uuid) {
			throw std::invalid_argument("A multi CRS plane set representation is not supported yet");
		}
	}
	return COMMON_NS::DataObjectReference(result);
}

void PlaneSetRepresentation::pushBackHorizontalPlaneGeometryPatch(double zCoordinate, RESQML2_NS::AbstractLocal3dCrs* localCrs)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}

	resqml22__HorizontalPlaneGeometry* patch = soap_new_resqml22__HorizontalPlaneGeometry(gsoapProxy2_3->soap);
	patch->LocalCrs = localCrs->newEml23Reference();
	patch->Coordinate = zCoordinate;

	static_cast<_resqml22__PlaneSetRepresentation*>(gsoapProxy2_3)->Planes.push_back(patch);

	getRepository()->addRelationship(this, localCrs);
}

void PlaneSetRepresentation::pushBackTiltedPlaneGeometryPatch(
	double x1, double y1, double z1,
	double x2, double y2, double z2,
	double x3, double y3, double z3,
	RESQML2_NS::AbstractLocal3dCrs* localCrs)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}

	resqml22__TiltedPlaneGeometry* patch = soap_new_resqml22__TiltedPlaneGeometry(gsoapProxy2_3->soap);
	patch->LocalCrs = localCrs->newEml23Reference();

	patch->Plane.push_back(soap_new_resqml22__ThreePoint3d(gsoapProxy2_3->soap, 1));
	patch->Plane[0]->Point3d.push_back(soap_new_resqml22__Point3d(gsoapProxy2_3->soap, 1));
	patch->Plane[0]->Point3d[0]->Coordinate1 = x1;
	patch->Plane[0]->Point3d[0]->Coordinate2 = y1;
	patch->Plane[0]->Point3d[0]->Coordinate3 = z1;
	patch->Plane[0]->Point3d.push_back(soap_new_resqml22__Point3d(gsoapProxy2_3->soap, 1));
	patch->Plane[0]->Point3d[1]->Coordinate1 = x2;
	patch->Plane[0]->Point3d[1]->Coordinate2 = y2;
	patch->Plane[0]->Point3d[1]->Coordinate3 = z2;
	patch->Plane[0]->Point3d.push_back(soap_new_resqml22__Point3d(gsoapProxy2_3->soap, 1));
	patch->Plane[0]->Point3d[2]->Coordinate1 = x3;
	patch->Plane[0]->Point3d[2]->Coordinate2 = y3;
	patch->Plane[0]->Point3d[2]->Coordinate3 = z3;

	static_cast<_resqml22__PlaneSetRepresentation*>(gsoapProxy2_3)->Planes.push_back(patch);

	getRepository()->addRelationship(this, localCrs);
}

ULONG64 PlaneSetRepresentation::getXyzPointCountOfPatch(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index patch is not in the allowed range of patch");
	}

	_resqml22__PlaneSetRepresentation* rep = static_cast<_resqml22__PlaneSetRepresentation*>(gsoapProxy2_3);
	return rep->Planes[patchIndex]->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__HorizontalPlaneGeometry
		? 1
		: static_cast<resqml22__TiltedPlaneGeometry*>(rep->Planes[patchIndex])->Plane.size() * 3;
}

void PlaneSetRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index patch is not in the allowed range of patch");
	}

	_resqml22__PlaneSetRepresentation* rep = static_cast<_resqml22__PlaneSetRepresentation*>(gsoapProxy2_3);
	if (rep->Planes[patchIndex]->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__HorizontalPlaneGeometry)
	{
		xyzPoints[0] = numeric_limits<double>::quiet_NaN();
		xyzPoints[1] = numeric_limits<double>::quiet_NaN();
		xyzPoints[2] = static_cast<resqml22__HorizontalPlaneGeometry*>(rep->Planes[patchIndex])->Coordinate;
	}
	else
	{
		resqml22__TiltedPlaneGeometry* tiltedPlane = static_cast<resqml22__TiltedPlaneGeometry*>(rep->Planes[patchIndex]);
		for (size_t subplaneIndex = 0; subplaneIndex < tiltedPlane->Plane.size(); ++subplaneIndex) {
			size_t offset = subplaneIndex * 9;
			xyzPoints[offset] = tiltedPlane->Plane[subplaneIndex]->Point3d[0]->Coordinate1;
			xyzPoints[offset + 1] = tiltedPlane->Plane[subplaneIndex]->Point3d[0]->Coordinate2;
			xyzPoints[offset + 2] = tiltedPlane->Plane[subplaneIndex]->Point3d[0]->Coordinate3;
			xyzPoints[offset + 3] = tiltedPlane->Plane[subplaneIndex]->Point3d[1]->Coordinate1;
			xyzPoints[offset + 4] = tiltedPlane->Plane[subplaneIndex]->Point3d[1]->Coordinate2;
			xyzPoints[offset + 5] = tiltedPlane->Plane[subplaneIndex]->Point3d[1]->Coordinate3;
			xyzPoints[offset + 6] = tiltedPlane->Plane[subplaneIndex]->Point3d[2]->Coordinate1;
			xyzPoints[offset + 7] = tiltedPlane->Plane[subplaneIndex]->Point3d[2]->Coordinate2;
			xyzPoints[offset + 8] = tiltedPlane->Plane[subplaneIndex]->Point3d[2]->Coordinate3;
		}
	}
}

unsigned int PlaneSetRepresentation::getPatchCount() const
{
    return static_cast<_resqml22__PlaneSetRepresentation*>(gsoapProxy2_3)->Planes.size();
}
