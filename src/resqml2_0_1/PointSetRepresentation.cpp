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
#include "PointSetRepresentation.h"

#include <limits>
#include <stdexcept>

#include "H5public.h"

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../eml2/AbstractLocal3dCrs.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* PointSetRepresentation::XML_NS = "resqml20";

PointSetRepresentation::PointSetRepresentation(COMMON_NS::DataObjectRepository* repo,
	const std::string & guid, const std::string & title)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREPointSetRepresentation(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
}

PointSetRepresentation::PointSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title)
{
	if (interp == nullptr) {
		throw invalid_argument("You must provide an interpretation");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREPointSetRepresentation(interp->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	interp->getRepository()->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
	setInterpretation(interp);
}

void PointSetRepresentation::pushBackXyzGeometryPatch(
	uint64_t xyzPointCount, double const* xyzPoints,
	EML2_NS::AbstractHdfProxy * proxy, EML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}

	resqml20__NodePatch* patch = soap_new_resqml20__NodePatch(gsoapProxy2_0_1->soap);
	patch->PatchIndex = static_cast<_resqml20__PointSetRepresentation*>(gsoapProxy2_0_1)->NodePatch.size();
	patch->Count = xyzPointCount;

	// XYZ points
	uint64_t pointCountDims[2] = { xyzPointCount, 3 };
	patch->Geometry = createPointGeometryPatch2_0_1(patch->PatchIndex, xyzPoints, localCrs, pointCountDims, 2, proxy);

	static_cast<_resqml20__PointSetRepresentation*>(gsoapProxy2_0_1)->NodePatch.push_back(patch);
	getRepository()->addRelationship(this, localCrs);
}

void PointSetRepresentation::pushBackXyGeometryPatch(
	uint64_t xyPointCount, double const* xyPoints,
	EML2_NS::AbstractHdfProxy* proxy, EML2_NS::AbstractLocal3dCrs* localCrs)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}

	resqml20__NodePatch* patch = soap_new_resqml20__NodePatch(gsoapProxy2_0_1->soap);
	patch->PatchIndex = static_cast<_resqml20__PointSetRepresentation*>(gsoapProxy2_0_1)->NodePatch.size();
	patch->Count = xyPointCount;

	// XYZ points
	uint64_t pointCountDims[2] = { xyPointCount, 2 };
	patch->Geometry = createPointGeometryPatch2_0_1(patch->PatchIndex, xyPoints, localCrs, pointCountDims, 2, proxy);

	static_cast<_resqml20__PointSetRepresentation*>(gsoapProxy2_0_1)->NodePatch.push_back(patch);
	getRepository()->addRelationship(this, localCrs);
}

COMMON_NS::DataObjectReference PointSetRepresentation::getHdfProxyDor() const
{
	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

resqml20__PointGeometry* PointSetRepresentation::getPointGeometry2_0_1(uint64_t patchIndex) const
{
	return static_cast<_resqml20__PointSetRepresentation*>(gsoapProxy2_0_1)->NodePatch.at(patchIndex)->Geometry;
}

uint64_t PointSetRepresentation::getXyzPointCountOfPatch(uint64_t patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	return static_cast<_resqml20__PointSetRepresentation*>(gsoapProxy2_0_1)->NodePatch[patchIndex]->Count;
}

void PointSetRepresentation::getXyzPointsOfPatch(uint64_t patchIndex, double * xyzPoints) const
{
	resqml20__PointGeometry const* pointGeom = getPointGeometry2_0_1(patchIndex);
	if (pointGeom != nullptr) {
		if (pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array)
		{
			eml20__Hdf5Dataset const* dataset = static_cast<resqml20__Point3dHdf5Array*>(pointGeom->Points)->Coordinates;
			EML2_NS::AbstractHdfProxy* hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, xyzPoints);
		}
		else if (pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point2dHdf5Array)
		{
			eml20__Hdf5Dataset const* dataset = static_cast<resqml20__Point2dHdf5Array*>(pointGeom->Points)->Coordinates;
			EML2_NS::AbstractHdfProxy* hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, xyzPoints);
			const uint64_t pointCount = getXyzPointCountOfPatch(patchIndex);
			for (size_t pointIndex = pointCount - 1; pointIndex >= 1; --pointIndex) {
				xyzPoints[pointIndex * 3 + 2] = std::numeric_limits<double>::quiet_NaN();
				xyzPoints[pointIndex * 3 + 1] = xyzPoints[pointIndex * 2 + 1];
				xyzPoints[pointIndex * 3] = xyzPoints[pointIndex * 2];
			}
			xyzPoints[2] = std::numeric_limits<double>::quiet_NaN();
		}
		else {
			throw invalid_argument("The geometry of the point set representation is neither simple 3d or 2d.");
		}
	}
	else {
		throw invalid_argument("The geometry of the point set representation either does not exist.");
	}
}

void PointSetRepresentation::getXyPointsOfPatch(uint64_t patchIndex, double* xyPoints) const
{
	resqml20__PointGeometry const* pointGeom = getPointGeometry2_0_1(patchIndex);
	if (pointGeom != nullptr) {
		if (pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array)
		{
			eml20__Hdf5Dataset const* dataset = static_cast<resqml20__Point3dHdf5Array*>(pointGeom->Points)->Coordinates;
			EML2_NS::AbstractHdfProxy* hdfProxy = getHdfProxyFromDataset(dataset);

			const uint64_t pointCount = getXyzPointCountOfPatch(patchIndex);
			std::unique_ptr<double[]> xyzPoints(new double[pointCount*3]);
			hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, xyzPoints.get());
			for (size_t pointIndex = 0; pointIndex < pointCount; ++pointIndex) {
				xyPoints[pointIndex * 2] = xyzPoints[pointIndex * 3];
				xyPoints[pointIndex * 2 + 1] = xyzPoints[pointIndex * 3 + 1];
			}
		}
		else if (pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point2dHdf5Array)
		{
			eml20__Hdf5Dataset const* dataset = static_cast<resqml20__Point2dHdf5Array*>(pointGeom->Points)->Coordinates;
			EML2_NS::AbstractHdfProxy* hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, xyPoints);
		}
		else {
			throw invalid_argument("The geometry of the point set representation is neither simple 3d or 2d.");
		}
	}
	else {
		throw invalid_argument("The geometry of the point set representation either does not exist.");
	}
}

uint64_t PointSetRepresentation::getPatchCount() const
{
	return static_cast<_resqml20__PointSetRepresentation*>(gsoapProxy2_0_1)->NodePatch.size();
}
