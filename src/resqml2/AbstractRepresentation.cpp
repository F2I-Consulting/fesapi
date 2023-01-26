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
#include "AbstractRepresentation.h"

#include <algorithm>
#include <limits>
#include <sstream>
#include <stdexcept>

#include "H5public.h"

#include "../eml2/AbstractHdfProxy.h"
#include "../eml2/AbstractLocal3dCrs.h"
#include "../eml2/TimeSeries.h"

#include "AbstractFeatureInterpretation.h"
#include "RepresentationSetRepresentation.h"
#include "AbstractValuesProperty.h"
#include "PointsProperty.h"
#include "SubRepresentation.h"

using namespace RESQML2_NS;
using namespace std;

COMMON_NS::DataObjectReference AbstractRepresentation::getHdfProxyDorFromPointGeometryPatch(gsoap_resqml2_0_1::resqml20__PointGeometry* patch) const
{
	if (patch != nullptr) {
		switch (patch->Points->soap_type()) {
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dZValueArray: {
			gsoap_resqml2_0_1::resqml20__Point3dZValueArray* const tmp = static_cast<gsoap_resqml2_0_1::resqml20__Point3dZValueArray *>(patch->Points);
			if (tmp->ZValues->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
				return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array *>(tmp->ZValues)->Values->HdfProxy);
			}
			break;
		}
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array:
			return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__Point3dHdf5Array *>(patch->Points)->Coordinates->HdfProxy);
		}
	}

	return COMMON_NS::DataObjectReference();
}

COMMON_NS::DataObjectReference AbstractRepresentation::getHdfProxyDorFromPointGeometryPatch(gsoap_eml2_3::resqml22__PointGeometry* patch) const
{
	if (patch != nullptr) {
		switch (patch->Points->soap_type()) {
		case SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dZValueArray: {
			auto const tmp = static_cast<gsoap_eml2_3::resqml22__Point3dZValueArray *>(patch->Points);
			if (tmp->ZValues->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray) {
				return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<gsoap_eml2_3::eml23__FloatingPointExternalArray *>(tmp->ZValues)->Values->ExternalDataArrayPart[0]));
			}
			break;
		}
		case SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray:
			return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<gsoap_eml2_3::resqml22__Point3dExternalArray *>(patch->Points)->Coordinates->ExternalDataArrayPart[0]));
		}
	}

	return COMMON_NS::DataObjectReference();
}

gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates* AbstractRepresentation::getSeismic3dCoordinates2_0_1(uint64_t patchIndex) const
{
	gsoap_resqml2_0_1::resqml20__PointGeometry* const geom = getPointGeometry2_0_1(patchIndex);
	if (geom == nullptr) {
		return nullptr;
	}

	if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Seismic3dCoordinates) {
		return static_cast<gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates*>(geom->SeismicCoordinates);
	}

	return nullptr;
}

gsoap_eml2_3::resqml22__Seismic3dCoordinates* AbstractRepresentation::getSeismic3dCoordinates2_2(uint64_t patchIndex) const
{
	gsoap_eml2_3::resqml22__PointGeometry* const geom = getPointGeometry2_2(patchIndex);
	if (geom == nullptr) {
		return nullptr;
	}

	if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Seismic3dCoordinates) {
		return static_cast<gsoap_eml2_3::resqml22__Seismic3dCoordinates*>(geom->SeismicCoordinates);
	}

	return nullptr;
}

gsoap_resqml2_0_1::resqml20__PointGeometry* AbstractRepresentation::createPointGeometryPatch2_0_1(uint64_t patchIndex,
	double const * points, EML2_NS::AbstractLocal3dCrs const* localCrs, uint64_t const* numPoints, uint32_t numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PointGeometry* const geom = gsoap_resqml2_0_1::soap_new_resqml20__PointGeometry(gsoapProxy2_0_1->soap);
		geom->LocalCrs = localCrs->newResqmlReference();

		// XML
		gsoap_resqml2_0_1::resqml20__Point3dHdf5Array* xmlPts = gsoap_resqml2_0_1::soap_new_resqml20__Point3dHdf5Array(gsoapProxy2_0_1->soap);
		xmlPts->Coordinates = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		xmlPts->Coordinates->HdfProxy = proxy->newResqmlReference();
		ostringstream oss;
		oss << "points_patch" << patchIndex;
		xmlPts->Coordinates->PathInHdfFile = getHdfGroup() + "/" + oss.str();
		geom->Points = xmlPts;

		// HDF
		std::unique_ptr<hsize_t[]> numValues(new hsize_t[numDimensionsInArray + 1]);
		for (hsize_t i = 0; i < numDimensionsInArray; ++i) {
			numValues[i] = numPoints[i];
		}
		numValues[numDimensionsInArray] = 3; // 3 for X, Y and Z

		proxy->writeArrayNdOfDoubleValues(getHdfGroup(), oss.str(), points, numValues.get(), numDimensionsInArray + 1);

		return geom;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_eml2_3::resqml22__PointGeometry* AbstractRepresentation::createPointGeometryPatch2_2(uint64_t patchIndex,
	double const * points, EML2_NS::AbstractLocal3dCrs const* localCrs, uint64_t const* numPoints, uint32_t numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

	if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__PointGeometry* const geom = gsoap_eml2_3::soap_new_resqml22__PointGeometry(gsoapProxy2_3->soap);
		geom->LocalCrs = localCrs->newEml23Reference();

		// XML
		size_t valueCount = numPoints[0] * 3;
		for (size_t dimIndex = 1; dimIndex < numDimensionsInArray; ++dimIndex) {
			valueCount *= numPoints[dimIndex];
		}
		gsoap_eml2_3::resqml22__Point3dExternalArray* xmlPts = gsoap_eml2_3::soap_new_resqml22__Point3dExternalArray(gsoapProxy2_3->soap);
		xmlPts->Coordinates = gsoap_eml2_3::soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
		xmlPts->Coordinates->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/points_patch" + std::to_string(patchIndex), valueCount, proxy));
		geom->Points = xmlPts;

		// HDF
		std::unique_ptr<hsize_t[]> numValues(new hsize_t[numDimensionsInArray + 1]);
		for (hsize_t i = 0; i < numDimensionsInArray; ++i) {
			numValues[i] = numPoints[i];
		}
		numValues[numDimensionsInArray] = 3; // 3 for X, Y and Z

		proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "points_patch" + std::to_string(patchIndex), points, numValues.get(), numDimensionsInArray + 1);

		return geom;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

EML2_NS::AbstractLocal3dCrs* AbstractRepresentation::getLocalCrs(uint64_t patchIndex) const
{
	const auto dor = getLocalCrsDor(patchIndex);
	return dor.isEmpty() ? nullptr : getRepository()->getDataObjectByUuid<EML2_NS::AbstractLocal3dCrs>(dor.getUuid());
}

COMMON_NS::DataObjectReference AbstractRepresentation::getLocalCrsDor(uint64_t patchIndex) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PointGeometry* pointGeom = getPointGeometry2_0_1(patchIndex);
		if (pointGeom != nullptr) {
			return COMMON_NS::DataObjectReference(pointGeom->LocalCrs);
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__PointGeometry* pointGeom = getPointGeometry2_2(patchIndex);
		if (pointGeom != nullptr) {
			return COMMON_NS::DataObjectReference(pointGeom->LocalCrs);
		}
	}

	return COMMON_NS::DataObjectReference();
}

void AbstractRepresentation::setTimeIndex(uint64_t timeIndex, EML2_NS::TimeSeries* timeSeries)
{
	const uint64_t patchCount = getPatchCount();

	bool addRel = false;
	for (uint64_t i = 0; i < patchCount; ++i) {
		if (gsoapProxy2_0_1 != nullptr) {
			gsoap_resqml2_0_1::resqml20__PointGeometry* pointGeom = getPointGeometry2_0_1(i);
			if (pointGeom != nullptr) {
				pointGeom->TimeIndex = gsoap_resqml2_0_1::soap_new_resqml20__TimeIndex(gsoapProxy2_0_1->soap);
				pointGeom->TimeIndex->Index = timeIndex;
				pointGeom->TimeIndex->TimeSeries = timeSeries->newResqmlReference();
				addRel = true;
			}
		}
		else if (gsoapProxy2_3 != nullptr) {
			gsoap_eml2_3::resqml22__PointGeometry* pointGeom = getPointGeometry2_2(i);
			if (pointGeom != nullptr) {
				pointGeom->TimeIndex = gsoap_eml2_3::soap_new_eml23__TimeIndex(gsoapProxy2_3->soap);
				pointGeom->TimeIndex->Index = timeIndex;
				pointGeom->TimeIndex->TimeSeries = timeSeries->newEml23Reference();
				addRel = true;
			}
		}
	}

	if (addRel) {
		getRepository()->addRelationship(this, timeSeries);
	}
}

uint64_t AbstractRepresentation::getTimeIndex() const
{
	const uint64_t patchCount = getPatchCount();

	for (uint64_t i = 0; i < patchCount; ++i) {
		if (gsoapProxy2_0_1 != nullptr) {
			gsoap_resqml2_0_1::resqml20__PointGeometry const* pointGeom = getPointGeometry2_0_1(i);
			if (pointGeom != nullptr && pointGeom->TimeIndex != nullptr) {
				return pointGeom->TimeIndex->Index;
			}
		}
		else if (gsoapProxy2_3 != nullptr) {
			gsoap_eml2_3::resqml22__PointGeometry const* pointGeom = getPointGeometry2_2(i);
			if (pointGeom != nullptr && pointGeom->TimeIndex != nullptr) {
				return pointGeom->TimeIndex->Index;
			}
		}
	}

	throw std::logic_error("There is no time index associated to the representation " + getUuid());
}

EML2_NS::TimeSeries* AbstractRepresentation::getTimeSeries() const
{
	const auto dor = getTimeSeriesDor();
	return dor.isEmpty() ? nullptr : getRepository()->getDataObjectByUuid<EML2_NS::TimeSeries>(dor.getUuid());
}

COMMON_NS::DataObjectReference AbstractRepresentation::getTimeSeriesDor() const
{
	const uint64_t patchCount = getPatchCount();

	for (uint64_t i = 0; i < patchCount; ++i) {
		if (gsoapProxy2_0_1 != nullptr) {
			gsoap_resqml2_0_1::resqml20__PointGeometry const* pointGeom = getPointGeometry2_0_1(i);
			if (pointGeom != nullptr && pointGeom->TimeIndex != nullptr) {
				return COMMON_NS::DataObjectReference(pointGeom->TimeIndex->TimeSeries);
			}
		}
		else if (gsoapProxy2_3 != nullptr) {
			gsoap_eml2_3::resqml22__PointGeometry const* pointGeom = getPointGeometry2_2(i);
			if (pointGeom != nullptr && pointGeom->TimeIndex != nullptr) {
				return COMMON_NS::DataObjectReference(pointGeom->TimeIndex->TimeSeries);
			}
		}
	}

	return COMMON_NS::DataObjectReference();
}

std::vector<AbstractProperty*> AbstractRepresentation::getPropertySet() const
{
	return getRepository()->getSourceObjects<RESQML2_NS::AbstractProperty>(this);
}

std::vector<AbstractValuesProperty*> AbstractRepresentation::getValuesPropertySet() const
{
	return getRepository()->getSourceObjects<RESQML2_NS::AbstractValuesProperty>(this);
}

std::vector<PointsProperty*> AbstractRepresentation::getPointsPropertySet() const
{
	return getRepository()->getSourceObjects<RESQML2_NS::PointsProperty>(this);
}

void AbstractRepresentation::setInterpretation(AbstractFeatureInterpretation* interp)
{
	if (interp == nullptr) {
		throw invalid_argument("Cannot set a null interpretation to a representation");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		if (static_cast<gsoap_resqml2_0_1::resqml20__AbstractRepresentation*>(gsoapProxy2_0_1)->RepresentedInterpretation != nullptr) {
			interp->getRepository()->deleteRelationship(this, getInterpretation());
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		if (static_cast<gsoap_eml2_3::resqml22__AbstractRepresentation*>(gsoapProxy2_3)->RepresentedObject != nullptr) {
			getRepository()->deleteRelationship(this, getInterpretation());
		}
	}

	if (gsoapProxy2_0_1 != nullptr) {
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractRepresentation*>(gsoapProxy2_0_1)->RepresentedInterpretation = interp->newResqmlReference();
	}
	else if (gsoapProxy2_3 != nullptr) {
		static_cast<gsoap_eml2_3::resqml22__AbstractRepresentation*>(gsoapProxy2_3)->RepresentedObject = interp->newEml23Reference();
	}
	else
		throw logic_error("Not implemented yet");

	getRepository()->addRelationship(this, interp);
}

AbstractFeatureInterpretation* AbstractRepresentation::getInterpretation() const
{
	return getRepository()->getDataObjectByUuid<AbstractFeatureInterpretation>(getInterpretationDor().getUuid());
}

COMMON_NS::DataObjectReference AbstractRepresentation::getInterpretationDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__AbstractRepresentation*>(gsoapProxy2_0_1)->RepresentedInterpretation);
	}
	else if (gsoapProxy2_3 != nullptr) {
		return COMMON_NS::DataObjectReference(static_cast<gsoap_eml2_3::resqml22__AbstractRepresentation*>(gsoapProxy2_3)->RepresentedObject);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::vector<SubRepresentation*> AbstractRepresentation::getSubRepresentationSet() const
{
	return repository->getSourceObjects<SubRepresentation>(this);
}

std::vector<SubRepresentation*> AbstractRepresentation::getFaultSubRepresentationSet() const
{
	std::vector<SubRepresentation*> result;

	const std::vector<SubRepresentation*>& subRepresentationSet = getSubRepresentationSet();
	for (size_t i = 0; i < subRepresentationSet.size(); ++i) {
		if (subRepresentationSet[i]->getInterpretation() != nullptr && subRepresentationSet[i]->getInterpretation()->getXmlTag() == "FaultInterpretation") {
			result.push_back(subRepresentationSet[i]);
		}
	}

	return result;
}

uint64_t AbstractRepresentation::getXyzPointCountOfAllPatches() const
{
	uint64_t result = 0;

	const uint64_t patchCount = getPatchCount();
	for (uint64_t patchIndex = 0; patchIndex < patchCount; ++patchIndex) {
		result += getXyzPointCountOfPatch(patchIndex);
	}

	return result;
}

void AbstractRepresentation::getXyzPointsOfPatchInGlobalCrs(uint64_t patchIndex, double* xyzPoints) const
{
	if (getLocalCrs(patchIndex)->isPartial()) {
		throw invalid_argument("You cannot get the points in the global CRS if the local CRS is partial");
	}

	getXyzPointsOfPatch(patchIndex, xyzPoints);

	getLocalCrs(patchIndex)->convertXyzPointsToGlobalCrs(xyzPoints, getXyzPointCountOfPatch(patchIndex));
}

void AbstractRepresentation::getXyzPointsOfAllPatches(double* xyzPoints) const
{
	const uint64_t patchCount = getPatchCount();
	getXyzPointsOfPatch(0, xyzPoints);
	for (uint64_t patchIndex = 1; patchIndex < patchCount; ++patchIndex) {
		xyzPoints += getXyzPointCountOfPatch(patchIndex - 1) * 3;
		getXyzPointsOfPatch(patchIndex, xyzPoints);
	}
}

bool AbstractRepresentation::isInSingleLocalCrs() const
{
	const uint64_t patchCount = getPatchCount();
	if (patchCount < 2) {
		return true;
	}
	EML2_NS::AbstractLocal3dCrs const* localCrsRef = getLocalCrs(0);

	for (uint64_t patchIndex = 1; patchIndex < patchCount; ++patchIndex) {
		if (getLocalCrs(patchIndex) != localCrsRef) {
			return false;
		}
	}

	return true;
}

bool AbstractRepresentation::isInSingleGlobalCrs() const
{
	const uint64_t patchCount = getPatchCount();
	if (patchCount < 2) {
		return true;
	}
	EML2_NS::AbstractLocal3dCrs const* localCrs = getLocalCrs(0);
	const uint64_t epsgCode = (localCrs != nullptr && localCrs->isProjectedCrsDefinedWithEpsg()) ? localCrs->getProjectedCrsEpsgCode() : (std::numeric_limits<uint64_t>::max)();

	for (uint64_t patchIndex = 1; patchIndex < patchCount; ++patchIndex) {
		localCrs = getLocalCrs(patchIndex);
		if (epsgCode != ((localCrs != nullptr && localCrs->isProjectedCrsDefinedWithEpsg()) ? localCrs->getProjectedCrsEpsgCode() : (std::numeric_limits<uint64_t>::max)())) {
			return false;
		}
	}

	return true;
}

void AbstractRepresentation::getXyzPointsOfAllPatchesInGlobalCrs(double* xyzPoints) const
{
	const uint64_t patchCount = getPatchCount();
	for (uint64_t patchIndex = 0; patchIndex < patchCount; ++patchIndex) {
		if (getLocalCrs(patchIndex)->isPartial()) {
			throw invalid_argument("You cannot get the points in the global CRS because the local CRS of patch " + std::to_string(patchIndex) 
				+ " of representation " + getUuid() + " is partial");
		}
	}
	if (!isInSingleGlobalCrs()) {
		throw invalid_argument("The representation is not inside a single global CRS.");
	}
	getXyzPointsOfAllPatches(xyzPoints);

	getLocalCrs(0)->convertXyzPointsToGlobalCrs(xyzPoints, getXyzPointCountOfAllPatches());
}

AbstractRepresentation* AbstractRepresentation::getSeismicSupportOfPatch(uint64_t patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The seismic support of the patch at the specified index is out of range.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(patchIndex);
		if (geom == nullptr || geom->SeismicCoordinates == nullptr) {
			return nullptr;
		}

		return getRepository()->getDataObjectByUuid<AbstractRepresentation>(geom->SeismicCoordinates->SeismicSupport->UUID);
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__PointGeometry* geom = getPointGeometry2_2(patchIndex);
		if (geom == nullptr || geom->SeismicCoordinates == nullptr) {
			return nullptr;
		}

		return getRepository()->getDataObjectByUuid<AbstractRepresentation>(geom->SeismicCoordinates->SeismicSupport->Uuid);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::set<AbstractRepresentation*> AbstractRepresentation::getAllSeismicSupport() const
{
	std::set<AbstractRepresentation*> result;
	const uint64_t patchCount = getPatchCount();
	for (uint64_t patchIndex = 0; patchIndex < patchCount; ++patchIndex) {
		AbstractRepresentation* seismicSupport = getSeismicSupportOfPatch(patchIndex);
		if (seismicSupport != nullptr) {
			result.insert(seismicSupport);
		}
	}

	return result;
}

void AbstractRepresentation::pushBackIntoRepresentationSet(RepresentationSetRepresentation* repSet)
{
	if (repSet == nullptr) {
		throw invalid_argument("The representation set representation which should contain this representation cannot be null.");
	}

	repSet->pushBack(this);
}

std::vector<RepresentationSetRepresentation*> AbstractRepresentation::getRepresentationSetRepresentationSet() const
{
	return repository->getSourceObjects<RepresentationSetRepresentation>(this);
}

void AbstractRepresentation::loadTargetRelationships()
{
	COMMON_NS::DataObjectReference dor = getInterpretationDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<RESQML2_NS::AbstractFeatureInterpretation>(dor);
	}

	// CRS
	for (uint64_t patchIndex = 0; patchIndex < getPatchCount(); ++patchIndex) {
		dor = getLocalCrsDor(patchIndex);
		if (!dor.isEmpty()) {
			convertDorIntoRel<EML2_NS::AbstractLocal3dCrs>(dor);
		}
	}

	// TODO : Currently, only one HDF proxy per representation is supported. It can be multiple (for example, regarding IJK parametric grid, parameters in one hdf proxy and control points in another one)
	dor = getHdfProxyDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<EML2_NS::AbstractHdfProxy>(dor);
	}

	dor = getTimeSeriesDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<EML2_NS::TimeSeries>(dor);
	}

	// Seismic support
	if (gsoapProxy2_0_1 != nullptr) {
		// Seismic support
		for (uint64_t patchIndex = 0; patchIndex < getPatchCount(); ++patchIndex) {
			gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(patchIndex);
			if (geom != nullptr && geom->SeismicCoordinates != nullptr) {
				if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Seismic3dCoordinates) {
					gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates const* seis3dInfo = static_cast<gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates*>(geom->SeismicCoordinates);
					convertDorIntoRel<AbstractRepresentation>(seis3dInfo->SeismicSupport);
				}
				else if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Seismic2dCoordinates) {
					gsoap_resqml2_0_1::resqml20__Seismic2dCoordinates const* seis2dInfo = static_cast<gsoap_resqml2_0_1::resqml20__Seismic2dCoordinates*>(geom->SeismicCoordinates);
					convertDorIntoRel<AbstractRepresentation>(seis2dInfo->SeismicSupport);
				}
			}
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		for (uint64_t patchIndex = 0; patchIndex < getPatchCount(); ++patchIndex) {
			gsoap_eml2_3::resqml22__PointGeometry* geom = getPointGeometry2_2(patchIndex);
			if (geom != nullptr && geom->SeismicCoordinates != nullptr) {
				if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Seismic3dCoordinates) {
					gsoap_eml2_3::resqml22__Seismic3dCoordinates const* seis3dInfo = static_cast<gsoap_eml2_3::resqml22__Seismic3dCoordinates*>(geom->SeismicCoordinates);
					convertDorIntoRel<AbstractRepresentation>(seis3dInfo->SeismicSupport);
				}
				else if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Seismic2dCoordinates) {
					gsoap_eml2_3::resqml22__Seismic2dCoordinates const* seis2dInfo = static_cast<gsoap_eml2_3::resqml22__Seismic2dCoordinates*>(geom->SeismicCoordinates);
					convertDorIntoRel<AbstractRepresentation>(seis2dInfo->SeismicSupport);
				}
			}
		}
	}
}

void AbstractRepresentation::addSeismic3dCoordinatesToPatch(uint64_t patchIndex, double* inlines, double* crosslines, uint64_t pointCount,
	RESQML2_NS::AbstractRepresentation* seismicSupport, EML2_NS::AbstractHdfProxy* proxy)
{
	if (gsoapProxy2_0_1 != nullptr || gsoapProxy2_3 != nullptr) {
		getRepository()->addRelationship(this, proxy);
		getRepository()->addRelationship(this, seismicSupport);

		ostringstream oss;
		ostringstream oss2;

		if (gsoapProxy2_0_1 != nullptr) {
			gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(patchIndex);
			if (geom == nullptr) {
				throw invalid_argument("The patchIndex does not identify a point geometry.");
			}

			if (geom->SeismicCoordinates == nullptr) {
				geom->SeismicCoordinates = gsoap_resqml2_0_1::soap_new_resqml20__Seismic3dCoordinates(gsoapProxy2_0_1->soap);
			}
			else if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Seismic2dCoordinates) {
				throw invalid_argument("It already exists some seismic 2d coordinates for this patch.");
			}
			else {
				throw logic_error("Not implemented yet");
			}
			gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates* patch = static_cast<gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates*>(geom->SeismicCoordinates);

			patch->SeismicSupport = seismicSupport->newResqmlReference();

			// inlines XML
			gsoap_resqml2_0_1::resqml20__DoubleHdf5Array* inlineValues = gsoap_resqml2_0_1::soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
			inlineValues->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
			inlineValues->Values->HdfProxy = proxy->newResqmlReference();
			oss << "inlineCoordinates_patch" << patchIndex;
			inlineValues->Values->PathInHdfFile = getHdfGroup() + "/" + oss.str();
			patch->InlineCoordinates = inlineValues;

			// crosslines XML
			gsoap_resqml2_0_1::resqml20__DoubleHdf5Array* crosslineValues = gsoap_resqml2_0_1::soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
			crosslineValues->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
			crosslineValues->Values->HdfProxy = proxy->newResqmlReference();
			oss2 << "crosslineCoordinates_patch" << patchIndex;
			crosslineValues->Values->PathInHdfFile = getHdfGroup() + "/" + oss2.str();
			patch->CrosslineCoordinates = crosslineValues;
		}
		else if (gsoapProxy2_3 != nullptr) {
			gsoap_eml2_3::resqml22__PointGeometry* geom = getPointGeometry2_2(patchIndex);
			if (geom == nullptr) {
				throw invalid_argument("The patchIndex does not identify a point geometry.");
			}

			if (geom->SeismicCoordinates == nullptr) {
				geom->SeismicCoordinates = gsoap_eml2_3::soap_new_resqml22__Seismic3dCoordinates(gsoapProxy2_3->soap);
			}
			else if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Seismic2dCoordinates) {
				throw invalid_argument("It already exists some seismic 2d coordinates for this patch.");
			}
			else {
				throw logic_error("Not implemented yet");
			}
			gsoap_eml2_3::resqml22__Seismic3dCoordinates* patch = static_cast<gsoap_eml2_3::resqml22__Seismic3dCoordinates*>(geom->SeismicCoordinates);

			patch->SeismicSupport = seismicSupport->newEml23Reference();

			// inlines XML
			gsoap_eml2_3::eml23__FloatingPointExternalArray* inlineValues = gsoap_eml2_3::soap_new_eml23__FloatingPointExternalArray(gsoapProxy2_3->soap);
			inlineValues->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
			inlineValues->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/inlineCoordinates_patch" + std::to_string(patchIndex), pointCount, proxy));
			patch->InlineCoordinates = inlineValues;

			// crosslines XML
			gsoap_eml2_3::eml23__FloatingPointExternalArray* crosslineValues = gsoap_eml2_3::soap_new_eml23__FloatingPointExternalArray(gsoapProxy2_3->soap);
			crosslineValues->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
			crosslineValues->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/crosslineCoordinates_patch" + std::to_string(patchIndex), pointCount, proxy));
			patch->CrosslineCoordinates = crosslineValues;
		}

		// HDF
		hsize_t dim = pointCount;
		proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "inlineCoordinates_patch" + std::to_string(patchIndex), inlines, &dim, 1);
		proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "crosslineCoordinates_patch" + std::to_string(patchIndex), crosslines, &dim, 1);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractRepresentation::addSeismic3dCoordinatesToPatch(uint64_t patchIndex, double startInline, double incrInline, unsigned int countInline,
	double startCrossline, double incrCrossline, unsigned int countCrossline, RESQML2_NS::AbstractRepresentation* seismicSupport)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(patchIndex);
		if (!geom)
			throw invalid_argument("The patchIndex does not identify a point geometry.");

		if (geom->SeismicCoordinates == nullptr) {
			geom->SeismicCoordinates = gsoap_resqml2_0_1::soap_new_resqml20__Seismic3dCoordinates(gsoapProxy2_0_1->soap);
		}
		else if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Seismic2dCoordinates) {
			throw invalid_argument("It already exists some seismic 2d coordinates for this patch.");
		}
		else {
			throw logic_error("Not implemented yet");
		}
		gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates* patch = static_cast<gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates*>(geom->SeismicCoordinates);

		patch->SeismicSupport = seismicSupport->newResqmlReference();
		getRepository()->addRelationship(this, seismicSupport);

		// inlines XML
		gsoap_resqml2_0_1::resqml20__DoubleLatticeArray* inlineValues = gsoap_resqml2_0_1::soap_new_resqml20__DoubleLatticeArray(gsoapProxy2_0_1->soap);
		patch->InlineCoordinates = inlineValues;
		inlineValues->StartValue = startInline;
		gsoap_resqml2_0_1::resqml20__DoubleConstantArray* spacInline = gsoap_resqml2_0_1::soap_new_resqml20__DoubleConstantArray(gsoapProxy2_0_1->soap);
		spacInline->Count = countInline - 1;
		spacInline->Value = incrInline;
		inlineValues->Offset.push_back(spacInline);

		// crosslines XML
		gsoap_resqml2_0_1::resqml20__DoubleLatticeArray* crosslineValues = gsoap_resqml2_0_1::soap_new_resqml20__DoubleLatticeArray(gsoapProxy2_0_1->soap);
		patch->CrosslineCoordinates = crosslineValues;
		crosslineValues->StartValue = startCrossline;
		gsoap_resqml2_0_1::resqml20__DoubleConstantArray* spacCrossline = gsoap_resqml2_0_1::soap_new_resqml20__DoubleConstantArray(gsoapProxy2_0_1->soap);
		spacCrossline->Count = countCrossline - 1;
		spacCrossline->Value = incrCrossline;
		crosslineValues->Offset.push_back(spacCrossline);
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__PointGeometry* geom = getPointGeometry2_2(patchIndex);
		if (!geom)
			throw invalid_argument("The patchIndex does not identify a point geometry.");

		if (geom->SeismicCoordinates == nullptr) {
			geom->SeismicCoordinates = gsoap_eml2_3::soap_new_resqml22__Seismic3dCoordinates(gsoapProxy2_3->soap);
		}
		else if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Seismic2dCoordinates) {
			throw invalid_argument("It already exists some seismic 2d coordinates for this patch.");
		}
		else {
			throw logic_error("Not implemented yet");
		}
		auto patch = static_cast<gsoap_eml2_3::resqml22__Seismic3dCoordinates*>(geom->SeismicCoordinates);

		patch->SeismicSupport = seismicSupport->newEml23Reference();
		getRepository()->addRelationship(this, seismicSupport);

		// inlines XML
		gsoap_eml2_3::eml23__FloatingPointLatticeArray* inlineValues = gsoap_eml2_3::soap_new_eml23__FloatingPointLatticeArray(gsoapProxy2_3->soap);
		patch->InlineCoordinates = inlineValues;
		inlineValues->StartValue = startInline;
		gsoap_eml2_3::eml23__FloatingPointConstantArray* spacInline = gsoap_eml2_3::soap_new_eml23__FloatingPointConstantArray(gsoapProxy2_3->soap);
		spacInline->Count = countInline - 1;
		spacInline->Value = incrInline;
		inlineValues->Offset.push_back(spacInline);

		// crosslines XML
		gsoap_eml2_3::eml23__FloatingPointLatticeArray* crosslineValues = gsoap_eml2_3::soap_new_eml23__FloatingPointLatticeArray(gsoapProxy2_3->soap);
		patch->CrosslineCoordinates = crosslineValues;
		crosslineValues->StartValue = startCrossline;
		gsoap_eml2_3::eml23__FloatingPointConstantArray* spacCrossline = gsoap_eml2_3::soap_new_eml23__FloatingPointConstantArray(gsoapProxy2_3->soap);
		spacCrossline->Count = countCrossline - 1;
		spacCrossline->Value = incrCrossline;
		crosslineValues->Offset.push_back(spacCrossline);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractRepresentation::addSeismic2dCoordinatesToPatch(uint64_t patchIndex, double* lineAbscissa,
	RESQML2_NS::AbstractRepresentation* seismicSupport, EML2_NS::AbstractHdfProxy* proxy)
{
	if (gsoapProxy2_0_1 != nullptr || gsoapProxy2_3 != nullptr) {
		getRepository()->addRelationship(this, proxy);
		getRepository()->addRelationship(this, seismicSupport);
		
		unsigned long long pointCount = getXyzPointCountOfPatch(patchIndex);
		if (gsoapProxy2_0_1 != nullptr) {
			gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(patchIndex);
			if (!geom)
				throw invalid_argument("The patchIndex does not identify a point geometry.");

			if (geom->SeismicCoordinates == nullptr) {
				geom->SeismicCoordinates = gsoap_resqml2_0_1::soap_new_resqml20__Seismic2dCoordinates(gsoapProxy2_0_1->soap);
			}
			else if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Seismic3dCoordinates) {
				throw invalid_argument("It already exists some seismic 3d coordinates for this patch.");
			}
			else {
				throw logic_error("Not implemented yet");
			}
			gsoap_resqml2_0_1::resqml20__Seismic2dCoordinates* patch = static_cast<gsoap_resqml2_0_1::resqml20__Seismic2dCoordinates*>(geom->SeismicCoordinates);

			patch->SeismicSupport = seismicSupport->newResqmlReference();

			// abscissa XML
			gsoap_resqml2_0_1::resqml20__DoubleHdf5Array* abscissaValues = gsoap_resqml2_0_1::soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
			abscissaValues->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
			abscissaValues->Values->HdfProxy = proxy->newResqmlReference();
			abscissaValues->Values->PathInHdfFile = getHdfGroup() + "/lineAbscissa_patch" + std::to_string(patchIndex);
			patch->LineAbscissa = abscissaValues;
		}
		else if (gsoapProxy2_3 != nullptr) {
			gsoap_eml2_3::resqml22__PointGeometry* geom = getPointGeometry2_2(patchIndex);
			if (!geom)
				throw invalid_argument("The patchIndex does not identify a point geometry.");

			if (geom->SeismicCoordinates == nullptr) {
				geom->SeismicCoordinates = gsoap_eml2_3::soap_new_resqml22__Seismic2dCoordinates(gsoapProxy2_3->soap);
			}
			else if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Seismic3dCoordinates) {
				throw invalid_argument("It already exists some seismic 3d coordinates for this patch.");
			}
			else {
				throw logic_error("Not implemented yet");
			}
			gsoap_eml2_3::resqml22__Seismic2dCoordinates* patch = static_cast<gsoap_eml2_3::resqml22__Seismic2dCoordinates*>(geom->SeismicCoordinates);

			patch->SeismicSupport = seismicSupport->newEml23Reference();

			// abscissa XML
			gsoap_eml2_3::eml23__FloatingPointExternalArray* abscissaValues = gsoap_eml2_3::soap_new_eml23__FloatingPointExternalArray(gsoapProxy2_3->soap);
			abscissaValues->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
			abscissaValues->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/lineAbscissa_patch" + std::to_string(patchIndex), pointCount, proxy));
			patch->LineAbscissa = abscissaValues;
		}

		// inlines HDF
		proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "lineAbscissa_patch" + std::to_string(patchIndex), lineAbscissa, &pointCount, 1);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractRepresentation::getSeismicLineAbscissaOfPointsOfPatch(uint64_t patchIndex, double* values) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PointGeometry* const geom = getPointGeometry2_0_1(patchIndex);
		if (geom == nullptr || geom->SeismicCoordinates == nullptr ||
			geom->SeismicCoordinates->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Seismic2dCoordinates) {
			throw invalid_argument("The patch of this representation has not got any seismic information.");
		}

		gsoap_resqml2_0_1::resqml20__Seismic2dCoordinates const* seisInfo = static_cast<gsoap_resqml2_0_1::resqml20__Seismic2dCoordinates*>(geom->SeismicCoordinates);
		readArrayNdOfDoubleValues(seisInfo->LineAbscissa, values);
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__PointGeometry* const geom = getPointGeometry2_2(patchIndex);
		if (geom == nullptr || geom->SeismicCoordinates == nullptr ||
			geom->SeismicCoordinates->soap_type() != SOAP_TYPE_gsoap_eml2_3_resqml22__Seismic2dCoordinates) {
			throw invalid_argument("The patch of this representation has not got any seismic information.");
		}

		gsoap_eml2_3::resqml22__Seismic2dCoordinates const* seisInfo = static_cast<gsoap_eml2_3::resqml22__Seismic2dCoordinates*>(geom->SeismicCoordinates);
		readArrayNdOfDoubleValues(seisInfo->LineAbscissa, values);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractRepresentation::getInlinesOfPointsOfPatch(uint64_t patchIndex, double* values) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates* seisInfo = getSeismic3dCoordinates2_0_1(patchIndex);
		if (seisInfo == nullptr) {
			throw invalid_argument("The patch of this representation has not got any seismic information.");
		}

		readArrayNdOfDoubleValues(seisInfo->InlineCoordinates, values);
	}
	else if (gsoapProxy2_3 != nullptr) {
		auto seisInfo = getSeismic3dCoordinates2_2(patchIndex);
		if (seisInfo == nullptr) {
			throw invalid_argument("The patch of this representation has not got any seismic information.");
		}

		readArrayNdOfDoubleValues(seisInfo->InlineCoordinates, values);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractRepresentation::getCrosslinesOfPointsOfPatch(uint64_t patchIndex, double* values) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates* seisInfo = getSeismic3dCoordinates2_0_1(patchIndex);
		if (seisInfo == nullptr) {
			throw invalid_argument("The patch of this representation has not got any seismic information.");
		}
		readArrayNdOfDoubleValues(seisInfo->CrosslineCoordinates, values);
	}
	else if (gsoapProxy2_3 != nullptr) {
		auto seisInfo = getSeismic3dCoordinates2_2(patchIndex);
		if (seisInfo == nullptr) {
			throw invalid_argument("The patch of this representation has not got any seismic information.");
		}
		readArrayNdOfDoubleValues(seisInfo->CrosslineCoordinates, values);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::resqml20__PointGeometry* AbstractRepresentation::getPointGeometry2_0_1(uint64_t patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The patch index is out of range");
	}

	return nullptr;
}

gsoap_eml2_3::resqml22__PointGeometry* AbstractRepresentation::getPointGeometry2_2(uint64_t patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The patch index is out of range");
	}

	return nullptr;
}
