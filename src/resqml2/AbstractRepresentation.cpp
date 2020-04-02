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

#include <sstream>
#include <algorithm>
#include <stdexcept>

#include "H5public.h"

#include "../eml2/AbstractHdfProxy.h"

#include "AbstractFeatureInterpretation.h"
#include "RepresentationSetRepresentation.h"
#include "AbstractValuesProperty.h"
#include "SubRepresentation.h"
#include "AbstractLocal3dCrs.h"

using namespace RESQML2_NS;
using namespace std;

const char* AbstractRepresentation::XML_TAG = "AbstractRepresentation";

COMMON_NS::DataObjectReference AbstractRepresentation::getHdfProxyDorFromPointGeometryPatch(gsoap_resqml2_0_1::resqml20__PointGeometry* patch) const
{
	if (patch != nullptr) {
		switch (patch->Points->soap_type()) {
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dZValueArray: {
			gsoap_resqml2_0_1::resqml20__Point3dZValueArray* const tmp = static_cast<gsoap_resqml2_0_1::resqml20__Point3dZValueArray * const>(patch->Points);
			if (tmp->ZValues->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
				return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array * const>(tmp->ZValues)->Values->HdfProxy);
			}
			break;
		}
		case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array:
			return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__Point3dHdf5Array * const>(patch->Points)->Coordinates->HdfProxy);
		}
	}

	return COMMON_NS::DataObjectReference();
}

COMMON_NS::DataObjectReference AbstractRepresentation::getHdfProxyDorFromPointGeometryPatch(gsoap_eml2_3::resqml22__PointGeometry* patch) const
{
	if (patch != nullptr) {
		switch (patch->Points->soap_type()) {
		case SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dZValueArray: {
			auto const tmp = static_cast<gsoap_eml2_3::resqml22__Point3dZValueArray * const>(patch->Points);
			if (tmp->ZValues->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray) {
				return COMMON_NS::DataObjectReference(static_cast<gsoap_eml2_3::eml23__FloatingPointExternalArray * const>(tmp->ZValues)->Values->ExternalFileProxy[0]->EpcExternalPartReference);
			}
			break;
		}
		case SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray:
			return COMMON_NS::DataObjectReference(static_cast<gsoap_eml2_3::resqml22__Point3dExternalArray * const>(patch->Points)->Coordinates->ExternalFileProxy[0]->EpcExternalPartReference);
		}
	}

	return COMMON_NS::DataObjectReference();
}

gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates* AbstractRepresentation::getSeismic3dCoordinates2_0_1(unsigned int patchIndex) const
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

gsoap_eml2_3::resqml22__Seismic3dCoordinates* AbstractRepresentation::getSeismic3dCoordinates2_2(unsigned int patchIndex) const
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

gsoap_resqml2_0_1::resqml20__PointGeometry* AbstractRepresentation::createPointGeometryPatch2_0_1(unsigned int patchIndex,
	double const * points, AbstractLocal3dCrs const* localCrs, hsize_t const* numPoints, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy)
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

gsoap_eml2_3::resqml22__PointGeometry* AbstractRepresentation::createPointGeometryPatch2_2(unsigned int patchIndex,
	double const * points, AbstractLocal3dCrs const* localCrs, hsize_t const* numPoints, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy)
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
		gsoap_eml2_3::resqml22__Point3dExternalArray* xmlPts = gsoap_eml2_3::soap_new_resqml22__Point3dExternalArray(gsoapProxy2_3->soap);
		xmlPts->Coordinates = gsoap_eml2_3::soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
		auto dsPart = gsoap_eml2_3::soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
		dsPart->EpcExternalPartReference = proxy->newEml23Reference();
		ostringstream oss;
		oss << "points_patch" << patchIndex;
		dsPart->PathInExternalFile = getHdfGroup() + "/" + oss.str();
		xmlPts->Coordinates->ExternalFileProxy.push_back(dsPart);
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

AbstractLocal3dCrs* AbstractRepresentation::getLocalCrs(unsigned int patchIndex) const
{
	auto dor = getLocalCrsDor(patchIndex);
	return dor.isEmpty() ? nullptr : getRepository()->getDataObjectByUuid<AbstractLocal3dCrs>(dor.getUuid());
}

COMMON_NS::DataObjectReference AbstractRepresentation::getLocalCrsDor(unsigned int patchIndex) const
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

std::vector<AbstractProperty*> AbstractRepresentation::getPropertySet() const
{
	return getRepository()->getSourceObjects<RESQML2_NS::AbstractProperty>(this);
}

std::vector<AbstractValuesProperty*> AbstractRepresentation::getValuesPropertySet() const
{
	return getRepository()->getSourceObjects<RESQML2_NS::AbstractValuesProperty>(this);
}

unsigned int AbstractRepresentation::getValuesPropertyCount() const
{
	const size_t result = getValuesPropertySet().size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much properties");
	}

	return static_cast<unsigned int>(result);
}

AbstractValuesProperty* AbstractRepresentation::getValuesProperty(unsigned int index) const
{
	const std::vector<AbstractValuesProperty*>& propSet = getValuesPropertySet();

	if (propSet.size() > index) {
		return propSet[index];
	}

	throw out_of_range("The index of the property to get is out of range of the array of properties for this representation.");
}

void AbstractRepresentation::setInterpretation(AbstractFeatureInterpretation* interp)
{
	if (interp == nullptr) {
		throw invalid_argument("Cannot set a null interpretation to a representation");
	}
	if (getRepository() == nullptr) {
		interp->getRepository()->addOrReplaceDataObject(this);
	}

	if (gsoapProxy2_0_1 != nullptr) {
		if (static_cast<gsoap_resqml2_0_1::resqml20__AbstractRepresentation*>(gsoapProxy2_0_1)->RepresentedInterpretation != nullptr) {
			getRepository()->deleteRelationship(this, getInterpretation());
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		if (static_cast<gsoap_eml2_3::resqml22__AbstractRepresentation*>(gsoapProxy2_3)->RepresentedInterpretation != nullptr) {
			getRepository()->deleteRelationship(this, getInterpretation());
		}
	}

	getRepository()->addRelationship(this, interp);

	if (gsoapProxy2_0_1 != nullptr) {
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractRepresentation*>(gsoapProxy2_0_1)->RepresentedInterpretation = interp->newResqmlReference();
	}
	else if (gsoapProxy2_3 != nullptr) {
		static_cast<gsoap_eml2_3::resqml22__AbstractRepresentation*>(gsoapProxy2_3)->RepresentedInterpretation = interp->newEml23Reference();
	}
	else
		throw logic_error("Not implemented yet");
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
		return COMMON_NS::DataObjectReference(static_cast<gsoap_eml2_3::resqml22__AbstractRepresentation*>(gsoapProxy2_3)->RepresentedInterpretation);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::vector<SubRepresentation*> AbstractRepresentation::getSubRepresentationSet() const
{
	return repository->getSourceObjects<SubRepresentation>(this);
}

unsigned int AbstractRepresentation::getSubRepresentationCount() const
{
	const size_t result = getSubRepresentationSet().size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much subrepresentations");
	}

	return static_cast<unsigned int>(result);
}

SubRepresentation* AbstractRepresentation::getSubRepresentation(unsigned int index) const
{
	const std::vector<SubRepresentation*>& subRepresentationSet = getSubRepresentationSet();

	if (index >= subRepresentationSet.size()) {
		throw out_of_range("The subrepresentation at the specified index is out of range.");
	}

	return subRepresentationSet[index];
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

unsigned int AbstractRepresentation::getFaultSubRepresentationCount() const
{
	const size_t result = getFaultSubRepresentationSet().size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much fault subrepresentations");
	}

	return static_cast<unsigned int>(result);
}

SubRepresentation* AbstractRepresentation::getFaultSubRepresentation(unsigned int index) const
{
	const std::vector<RESQML2_NS::SubRepresentation*>& tmp = getFaultSubRepresentationSet();

	if (index >= tmp.size()) {
		throw range_error("The fault subrepresentation at the specified index is out of range.");
	}

	return tmp[index];
}

ULONG64 AbstractRepresentation::getXyzPointCountOfAllPatches() const
{
	ULONG64 result = 0;

	const unsigned int patchCount = getPatchCount();
	for (unsigned int patchIndex = 0; patchIndex < patchCount; ++patchIndex)
	{
		result += getXyzPointCountOfPatch(patchIndex);
	}

	return result;
}

void AbstractRepresentation::getXyzPointsOfPatchInGlobalCrs(const unsigned int& patchIndex, double* xyzPoints) const
{
	getXyzPointsOfPatch(patchIndex, xyzPoints);

	getLocalCrs(patchIndex)->convertXyzPointsToGlobalCrs(xyzPoints, getXyzPointCountOfPatch(patchIndex));
}

void AbstractRepresentation::getXyzPointsOfAllPatches(double* xyzPoints) const
{
	const unsigned int patchCount = getPatchCount();
	getXyzPointsOfPatch(0, xyzPoints);
	for (unsigned int patchIndex = 1; patchIndex < patchCount; patchIndex++)
	{
		xyzPoints += getXyzPointCountOfPatch(patchIndex - 1) * 3;
		getXyzPointsOfPatch(patchIndex, xyzPoints);
	}
}

bool AbstractRepresentation::isInSingleLocalCrs() const
{
	const unsigned int patchCount = getPatchCount();
	if (patchCount < 2) {
		return true;
	}
	AbstractLocal3dCrs const* localCrsRef = getLocalCrs(0);

	for (unsigned int patchIndex = 1; patchIndex < patchCount; ++patchIndex) {
		if (getLocalCrs(patchIndex) != localCrsRef) {
			return false;
		}
	}

	return true;
}

bool AbstractRepresentation::isInSingleGlobalCrs() const
{
	const unsigned int patchCount = getPatchCount();
	if (patchCount < 2) {
		return true;
	}
	AbstractLocal3dCrs const* localCrs = getLocalCrs(0);
	const ULONG64 epsgCode = (localCrs != nullptr && localCrs->isProjectedCrsDefinedWithEpsg()) ? localCrs->getProjectedCrsEpsgCode() : (std::numeric_limits<ULONG64>::max)();

	for (unsigned int patchIndex = 1; patchIndex < patchCount; ++patchIndex) {
		localCrs = getLocalCrs(patchIndex);
		if (epsgCode != ((localCrs != nullptr && localCrs->isProjectedCrsDefinedWithEpsg()) ? localCrs->getProjectedCrsEpsgCode() : (std::numeric_limits<ULONG64>::max)())) {
			return false;
		}
	}

	return true;
}

void AbstractRepresentation::getXyzPointsOfAllPatchesInGlobalCrs(double* xyzPoints) const
{
	if (!isInSingleGlobalCrs()) {
		throw invalid_argument("The representation is not inside a single global CRS.");
	}
	getXyzPointsOfAllPatches(xyzPoints);

	getLocalCrs(0)->convertXyzPointsToGlobalCrs(xyzPoints, getXyzPointCountOfAllPatches());
}

AbstractRepresentation* AbstractRepresentation::getSeismicSupportOfPatch(const unsigned int& patchIndex) const
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
	const unsigned int patchCount = getPatchCount();
	for (unsigned int patchIndex = 0; patchIndex < patchCount; ++patchIndex)
	{
		AbstractRepresentation* seismicSupport = getSeismicSupportOfPatch(patchIndex);
		if (seismicSupport != nullptr)
			result.insert(seismicSupport);
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

std::vector<RepresentationSetRepresentation*> AbstractRepresentation::getRepresentationSetRespresentationSet() const
{
	return repository->getTargetObjects<RepresentationSetRepresentation>(this);
}

ULONG64 AbstractRepresentation::getRepresentationSetRepresentationCount() const
{
	return getRepresentationSetRespresentationSet().size();
}

RepresentationSetRepresentation* AbstractRepresentation::getRepresentationSetRepresentation(const ULONG64& index) const
{
	const std::vector<RESQML2_NS::RepresentationSetRepresentation*>& representationSetRepresentationSet = getRepresentationSetRespresentationSet();

	if (index >= getRepresentationSetRepresentationCount()) {
		throw out_of_range("The index of the representation set representation is out of range.");
	}

	return representationSetRepresentationSet[index];
}

void AbstractRepresentation::loadTargetRelationships()
{
	COMMON_NS::DataObjectReference dor = getInterpretationDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<RESQML2_NS::AbstractFeatureInterpretation>(dor);
	}

	// CRS
	for (unsigned int patchIndex = 0; patchIndex < getPatchCount(); ++patchIndex) {
		dor = getLocalCrsDor(patchIndex);
		if (!dor.isEmpty()) {
			convertDorIntoRel<RESQML2_NS::AbstractLocal3dCrs>(dor);
		}
	}

	// TODO : Currently, only one HDF proxy per representation is supported. It can be multiple (for example, regarding IJK parametric grid, parameters in one hdf proxy and control points in another one)
	dor = getHdfProxyDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<EML2_NS::AbstractHdfProxy>(dor);
	}

	// Seismic support
	if (gsoapProxy2_0_1 != nullptr) {
		// Seismic support
		for (unsigned int patchIndex = 0; patchIndex < getPatchCount(); ++patchIndex) {
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
		for (unsigned int patchIndex = 0; patchIndex < getPatchCount(); ++patchIndex) {
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

void AbstractRepresentation::addSeismic3dCoordinatesToPatch(unsigned int patchIndex, double* inlines, double* crosslines, unsigned int pointCount,
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
			gsoap_eml2_3::eml23__DoubleExternalArray* inlineValues = gsoap_eml2_3::soap_new_eml23__DoubleExternalArray(gsoapProxy2_3->soap);
			inlineValues->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
			gsoap_eml2_3::eml23__ExternalDatasetPart* dsPart = gsoap_eml2_3::soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
			dsPart->EpcExternalPartReference = proxy->newEml23Reference();
			oss << "inlineCoordinates_patch" << patchIndex;
			dsPart->PathInExternalFile = getHdfGroup() + "/" + oss.str();
			inlineValues->Values->ExternalFileProxy.push_back(dsPart);
			patch->InlineCoordinates = inlineValues;

			// crosslines XML
			gsoap_eml2_3::eml23__DoubleExternalArray* crosslineValues = gsoap_eml2_3::soap_new_eml23__DoubleExternalArray(gsoapProxy2_3->soap);
			crosslineValues->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
			dsPart = gsoap_eml2_3::soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
			dsPart->EpcExternalPartReference = proxy->newEml23Reference();
			oss2 << "crosslineCoordinates_patch" << patchIndex;
			dsPart->PathInExternalFile = getHdfGroup() + "/" + oss2.str();
			crosslineValues->Values->ExternalFileProxy.push_back(dsPart);
			patch->CrosslineCoordinates = crosslineValues;
		}

		// HDF
		hsize_t dim = pointCount;
		proxy->writeArrayNdOfDoubleValues(getHdfGroup(), oss.str(), inlines, &dim, 1);
		proxy->writeArrayNdOfDoubleValues(getHdfGroup(), oss2.str(), crosslines, &dim, 1);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractRepresentation::addSeismic3dCoordinatesToPatch(unsigned int patchIndex, double startInline, double incrInline, unsigned int countInline,
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

void AbstractRepresentation::addSeismic2dCoordinatesToPatch(unsigned int patchIndex, double* lineAbscissa,
	RESQML2_NS::AbstractRepresentation* seismicSupport, EML2_NS::AbstractHdfProxy* proxy)
{
	if (gsoapProxy2_0_1 != nullptr || gsoapProxy2_3 != nullptr) {
		getRepository()->addRelationship(this, proxy);
		getRepository()->addRelationship(this, seismicSupport);

		ostringstream oss;

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
			oss << "lineAbscissa_patch" << patchIndex;
			abscissaValues->Values->PathInHdfFile = getHdfGroup() + "/" + oss.str();
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
			gsoap_eml2_3::eml23__DoubleExternalArray* abscissaValues = gsoap_eml2_3::soap_new_eml23__DoubleExternalArray(gsoapProxy2_3->soap);
			abscissaValues->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
			gsoap_eml2_3::eml23__ExternalDatasetPart* dsPart = gsoap_eml2_3::soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
			dsPart->EpcExternalPartReference = proxy->newEml23Reference();
			oss << "lineAbscissa_patch" << patchIndex;
			dsPart->PathInExternalFile = getHdfGroup() + "/" + oss.str();
			abscissaValues->Values->ExternalFileProxy.push_back(dsPart);
			patch->LineAbscissa = abscissaValues;
		}

		// inlines HDF
		unsigned long long pointCount = getXyzPointCountOfPatch(patchIndex);
		proxy->writeArrayNdOfDoubleValues(getHdfGroup(), oss.str(), lineAbscissa, &pointCount, 1);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractRepresentation::getSeismicLineAbscissaOfPointsOfPatch(unsigned int patchIndex, double* values) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PointGeometry* const geom = getPointGeometry2_0_1(patchIndex);
		if (geom == nullptr || geom->SeismicCoordinates == nullptr ||
			geom->SeismicCoordinates->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Seismic2dCoordinates) {
			throw invalid_argument("The patch of this representation has not got any seismic information.");
		}

		gsoap_resqml2_0_1::resqml20__Seismic2dCoordinates* seisInfo = static_cast<gsoap_resqml2_0_1::resqml20__Seismic2dCoordinates*>(geom->SeismicCoordinates);
		if (seisInfo->LineAbscissa->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
			gsoap_resqml2_0_1::resqml20__DoubleHdf5Array* dblValues = static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(seisInfo->LineAbscissa);
			getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dblValues->Values->HdfProxy->UUID)
				->readArrayNdOfDoubleValues(dblValues->Values->PathInHdfFile, values);
		}
		else
			throw logic_error("Not implemented yet");
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__PointGeometry* const geom = getPointGeometry2_2(patchIndex);
		if (geom == nullptr || geom->SeismicCoordinates == nullptr ||
			geom->SeismicCoordinates->soap_type() != SOAP_TYPE_gsoap_eml2_3_resqml22__Seismic2dCoordinates) {
			throw invalid_argument("The patch of this representation has not got any seismic information.");
		}

		gsoap_eml2_3::resqml22__Seismic2dCoordinates* seisInfo = static_cast<gsoap_eml2_3::resqml22__Seismic2dCoordinates*>(geom->SeismicCoordinates);
		if (seisInfo->LineAbscissa->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__DoubleExternalArray) {
			gsoap_eml2_3::eml23__DoubleExternalArray* dblValues = static_cast<gsoap_eml2_3::eml23__DoubleExternalArray*>(seisInfo->LineAbscissa);
			getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dblValues->Values->ExternalFileProxy[0]->EpcExternalPartReference->Uuid)
				->readArrayNdOfDoubleValues(dblValues->Values->ExternalFileProxy[0]->PathInExternalFile, values);
		}
		else
			throw logic_error("Not implemented yet");
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractRepresentation::getInlinesOfPointsOfPatch(unsigned int patchIndex, double* values) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates* seisInfo = getSeismic3dCoordinates2_0_1(patchIndex);
		if (seisInfo == nullptr) {
			throw invalid_argument("The patch of this representation has not got any seismic information.");
		}

		if (seisInfo->InlineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
			gsoap_resqml2_0_1::resqml20__DoubleHdf5Array* dblValues = static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(seisInfo->InlineCoordinates);
			getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dblValues->Values->HdfProxy->UUID)
				->readArrayNdOfDoubleValues(dblValues->Values->PathInHdfFile, values);
		}
		else
			throw logic_error("Not implemented yet");
	}
	else if (gsoapProxy2_3 != nullptr) {
		auto seisInfo = getSeismic3dCoordinates2_2(patchIndex);
		if (seisInfo == nullptr) {
			throw invalid_argument("The patch of this representation has not got any seismic information.");
		}

		if (seisInfo->InlineCoordinates->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__DoubleExternalArray) {
			gsoap_eml2_3::eml23__DoubleExternalArray* dblValues = static_cast<gsoap_eml2_3::eml23__DoubleExternalArray*>(seisInfo->InlineCoordinates);
			getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dblValues->Values->ExternalFileProxy[0]->EpcExternalPartReference->Uuid)
				->readArrayNdOfDoubleValues(dblValues->Values->ExternalFileProxy[0]->PathInExternalFile, values);
		}
		else
			throw logic_error("Not implemented yet");
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractRepresentation::getCrosslinesOfPointsOfPatch(unsigned int patchIndex, double* values) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates* seisInfo = getSeismic3dCoordinates2_0_1(patchIndex);
		if (seisInfo == nullptr) {
			throw invalid_argument("The patch of this representation has not got any seismic information.");
		}

		if (seisInfo->CrosslineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
			gsoap_resqml2_0_1::resqml20__DoubleHdf5Array* dblValues = static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(seisInfo->CrosslineCoordinates);
			getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dblValues->Values->HdfProxy->UUID)->readArrayNdOfDoubleValues(dblValues->Values->PathInHdfFile, values);
		}
		else
			throw logic_error("Not implemented yet");
	}
	else if (gsoapProxy2_3 != nullptr) {
		auto seisInfo = getSeismic3dCoordinates2_2(patchIndex);
		if (seisInfo == nullptr) {
			throw invalid_argument("The patch of this representation has not got any seismic information.");
		}

		if (seisInfo->CrosslineCoordinates->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__DoubleExternalArray) {
			gsoap_eml2_3::eml23__DoubleExternalArray* dblValues = static_cast<gsoap_eml2_3::eml23__DoubleExternalArray*>(seisInfo->CrosslineCoordinates);
			getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dblValues->Values->ExternalFileProxy[0]->EpcExternalPartReference->Uuid)
				->readArrayNdOfDoubleValues(dblValues->Values->ExternalFileProxy[0]->PathInExternalFile, values);
		}
		else
			throw logic_error("Not implemented yet");
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::resqml20__PointGeometry* AbstractRepresentation::getPointGeometry2_0_1(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The patch index is out of range");
	}

	return nullptr;
}

gsoap_eml2_3::resqml22__PointGeometry* AbstractRepresentation::getPointGeometry2_2(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The patch index is out of range");
	}

	return nullptr;
}
