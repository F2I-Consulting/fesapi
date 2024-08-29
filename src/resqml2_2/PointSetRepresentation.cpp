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

#include <numeric>

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../eml2/AbstractLocal3dCrs.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* PointSetRepresentation::XML_NS = "resqml22";

PointSetRepresentation::PointSetRepresentation(COMMON_NS::DataObjectRepository* repo,
	const std::string & guid, const std::string & title)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__PointSetRepresentation(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(this);
}

PointSetRepresentation::PointSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title)
{
	if (interp == nullptr) {
		throw invalid_argument("You must provide an interpretation");
	}

	gsoapProxy2_3 = soap_new_resqml22__PointSetRepresentation(interp->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	interp->getRepository()->addDataObject(this);
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

	// XYZ points
	uint64_t pointCountDims[2] = { xyzPointCount, 3 };
	static_cast<_resqml22__PointSetRepresentation*>(gsoapProxy2_3)->NodePatchGeometry.push_back(
		createPointGeometryPatch2_2(static_cast<_resqml22__PointSetRepresentation*>(gsoapProxy2_3)->NodePatchGeometry.size(), xyzPoints, localCrs, pointCountDims, 2, proxy)
	);
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

	// XYZ points
	uint64_t pointCountDims[2] = { xyPointCount, 2 };
	static_cast<_resqml22__PointSetRepresentation*>(gsoapProxy2_3)->NodePatchGeometry.push_back(
		createPointGeometryPatch2_2(static_cast<_resqml22__PointSetRepresentation*>(gsoapProxy2_3)->NodePatchGeometry.size(), xyPoints, localCrs, pointCountDims, 2, proxy)
	);
	getRepository()->addRelationship(this, localCrs);
}

COMMON_NS::DataObjectReference PointSetRepresentation::getHdfProxyDor() const
{
	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_2(0));
}

resqml22__PointGeometry* PointSetRepresentation::getPointGeometry2_2(uint64_t patchIndex) const
{
	return static_cast<_resqml22__PointSetRepresentation*>(gsoapProxy2_3)->NodePatchGeometry.at(patchIndex);
}

uint64_t PointSetRepresentation::getXyzPointCountOfPatch(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}
	auto const* ptArray = static_cast<_resqml22__PointSetRepresentation*>(gsoapProxy2_3)->NodePatchGeometry[patchIndex]->Points;
	if (ptArray->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray)
	{
		resqml22__Point3dExternalArray const* externalPtArray = dynamic_cast<resqml22__Point3dExternalArray const*>(ptArray);

		uint64_t result = 0;
		for (auto* dataArrayPart : externalPtArray->Coordinates->ExternalDataArrayPart) {
			result += std::accumulate(std::begin(dataArrayPart->Count), std::end(dataArrayPart->Count), static_cast<LONG64>(1), std::multiplies<LONG64>());
		}
		return result / 3;
	}
	else if (ptArray->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point2dExternalArray)
	{
		resqml22__Point2dExternalArray const* externalPtArray = dynamic_cast<resqml22__Point2dExternalArray const*>(ptArray);

		uint64_t result = 0;
		for (auto* dataArrayPart : externalPtArray->Coordinates->ExternalDataArrayPart) {
			result += std::accumulate(std::begin(dataArrayPart->Count), std::end(dataArrayPart->Count), static_cast<LONG64>(1), std::multiplies<LONG64>());
		}
		return result / 2;
	}
	else {
		throw invalid_argument("The geometry of the point set representation is neither simple 3d or 2d.");
	}
}

void PointSetRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const
{
	resqml22__PointGeometry const* pointGeom = getPointGeometry2_2(patchIndex);
	if (pointGeom != nullptr) {
		if (pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray)
		{
			auto const* daPart = static_cast<resqml22__Point3dExternalArray*>(pointGeom->Points)->Coordinates->ExternalDataArrayPart[0];
			getOrCreateHdfProxyFromDataArrayPart(daPart)->readArrayNdOfDoubleValues(daPart->PathInExternalFile, xyzPoints);
		}
		else if (pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point2dExternalArray)
		{
			auto const* daPart = static_cast<resqml22__Point2dExternalArray*>(pointGeom->Points)->Coordinates->ExternalDataArrayPart[0];
			getOrCreateHdfProxyFromDataArrayPart(daPart)->readArrayNdOfDoubleValues(daPart->PathInExternalFile, xyzPoints);
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
	resqml22__PointGeometry const* pointGeom = getPointGeometry2_2(patchIndex);
	if (pointGeom != nullptr) {
		if (pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray)
		{
			auto const* daPart = static_cast<resqml22__Point3dExternalArray*>(pointGeom->Points)->Coordinates->ExternalDataArrayPart[0];
			const uint64_t pointCount = getXyzPointCountOfPatch(patchIndex);
			std::unique_ptr<double[]> xyzPoints(new double[pointCount * 3]);
			getOrCreateHdfProxyFromDataArrayPart(daPart)->readArrayNdOfDoubleValues(daPart->PathInExternalFile, xyzPoints.get());
			for (size_t pointIndex = 0; pointIndex < pointCount; ++pointIndex) {
				xyPoints[pointIndex * 2] = xyzPoints[pointIndex * 3];
				xyPoints[pointIndex * 2 + 1] = xyzPoints[pointIndex * 3 + 1];
			}
		}
		else if (pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point2dExternalArray)
		{
			auto const* daPart = static_cast<resqml22__Point2dExternalArray*>(pointGeom->Points)->Coordinates->ExternalDataArrayPart[0];
			getOrCreateHdfProxyFromDataArrayPart(daPart)->readArrayNdOfDoubleValues(daPart->PathInExternalFile, xyPoints);
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
	return static_cast<_resqml22__PointSetRepresentation*>(gsoapProxy2_3)->NodePatchGeometry.size();
}
