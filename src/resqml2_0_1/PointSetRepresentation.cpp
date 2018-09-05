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
#include "resqml2_0_1/PointSetRepresentation.h"

#include <stdexcept>

#include "H5public.h"

#include "resqml2/AbstractFeatureInterpretation.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* PointSetRepresentation::XML_TAG = "PointSetRepresentation";

PointSetRepresentation::PointSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title):
	AbstractRepresentation(interp, crs)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREPointSetRepresentation(interp->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	// relationhsips
	localCrs = crs;
	localCrs->addRepresentation(this);

	setInterpretation(interp);
}

void PointSetRepresentation::pushBackGeometryPatch(
	const unsigned int & xyzPointCount, double * xyzPoints,
	COMMON_NS::AbstractHdfProxy * proxy)
{
	resqml2__NodePatch* patch = soap_new_resqml2__NodePatch(gsoapProxy2_0_1->soap, 1);
	patch->PatchIndex = static_cast<_resqml2__PointSetRepresentation*>(gsoapProxy2_0_1)->NodePatch.size();
	patch->Count = xyzPointCount;

	// XYZ points
	hsize_t pointCountDims[] = {xyzPointCount};
	patch->Geometry = createPointGeometryPatch2_0_1(patch->PatchIndex, xyzPoints, pointCountDims, 1, proxy);

	static_cast<_resqml2__PointSetRepresentation*>(gsoapProxy2_0_1)->NodePatch.push_back(patch);
}

gsoap_resqml2_0_1::eml20__DataObjectReference* PointSetRepresentation::getHdfProxyDor() const
{
	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_0_1(0));
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


