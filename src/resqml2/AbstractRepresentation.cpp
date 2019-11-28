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

#include "../resqml2_0_1/AbstractTechnicalFeature.h"
#include "AbstractFeatureInterpretation.h"
#include "RepresentationSetRepresentation.h"
#include "AbstractValuesProperty.h"
#include "SubRepresentation.h"
#include "../common/AbstractHdfProxy.h"
#include "AbstractLocal3dCrs.h"
#include "../tools/Misc.h"

using namespace RESQML2_NS;
using namespace std;

const char* AbstractRepresentation::XML_TAG = "AbstractRepresentation";

gsoap_resqml2_0_1::eml20__DataObjectReference* AbstractRepresentation::getHdfProxyDorFromPointGeometryPatch(gsoap_resqml2_0_1::resqml20__PointGeometry* patch) const
{
	if (patch != nullptr) {
		if (patch->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dZValueArray) {
			gsoap_resqml2_0_1::resqml20__Point3dZValueArray* const tmp = static_cast<gsoap_resqml2_0_1::resqml20__Point3dZValueArray * const>(patch->Points);
			if (tmp->ZValues->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
				return static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array * const>(tmp->ZValues)->Values->HdfProxy;
			}
		}
		else if (patch->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array) {
			return static_cast<gsoap_resqml2_0_1::resqml20__Point3dHdf5Array * const>(patch->Points)->Coordinates->HdfProxy;
		}
	}

	return nullptr;
}

gsoap_resqml2_0_1::resqml20__Seismic2dCoordinates* AbstractRepresentation::getSeismic2dCoordinates(const unsigned int& patchIndex) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PointGeometry* const geom = getPointGeometry2_0_1(patchIndex);
		if (geom == nullptr) {
			return nullptr;
		}

		if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Seismic2dCoordinates) {
			return static_cast<gsoap_resqml2_0_1::resqml20__Seismic2dCoordinates*>(geom->SeismicCoordinates);
		}

		return nullptr;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates* AbstractRepresentation::getSeismic3dCoordinates(const unsigned int& patchIndex) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PointGeometry* const geom = getPointGeometry2_0_1(patchIndex);
		if (geom == nullptr) {
			return nullptr;
		}

		if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Seismic3dCoordinates) {
			return static_cast<gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates*>(geom->SeismicCoordinates);
		}

		return nullptr;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::resqml20__PointGeometry* AbstractRepresentation::createPointGeometryPatch2_0_1(unsigned int patchIndex,
	double* points, AbstractLocal3dCrs* localCrs, hsize_t* numPoints, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy)
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
		xmlPts->Coordinates->PathInHdfFile = "/RESQML/" + getUuid() + "/" + oss.str();
		geom->Points = xmlPts;

		// HDF
		hsize_t* const numValues = new hsize_t[numDimensionsInArray + 1];
		for (hsize_t i = 0; i < numDimensionsInArray; ++i) {
			numValues[i] = numPoints[i];
		}
		numValues[numDimensionsInArray] = 3; // 3 for X, Y and Z

		proxy->writeArrayNdOfDoubleValues(getUuid(), oss.str(), points, numValues, numDimensionsInArray + 1);

		delete[] numValues;

		return geom;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

AbstractLocal3dCrs* AbstractRepresentation::getLocalCrs(unsigned int patchIndex) const
{
	const std::string& uuid = getLocalCrsUuid(patchIndex);
	return uuid.empty() ? nullptr : getRepository()->getDataObjectByUuid<AbstractLocal3dCrs>(uuid);
}

gsoap_resqml2_0_1::eml20__DataObjectReference* AbstractRepresentation::getLocalCrsDor(unsigned int patchIndex) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PointGeometry* pointGeom = getPointGeometry2_0_1(patchIndex);
		if (pointGeom != nullptr) {
			return pointGeom->LocalCrs;
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}

	return nullptr;
}

std::string AbstractRepresentation::getLocalCrsUuid(unsigned int patchIndex) const
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getLocalCrsDor(patchIndex);
	return dor == nullptr ? "" : dor->UUID;
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
	return getValuesPropertySet().size();
}

AbstractValuesProperty* AbstractRepresentation::getValuesProperty(unsigned int index) const
{
	const std::vector<AbstractValuesProperty*>& propSet = getValuesPropertySet();

	if (propSet.size() > index) {
		return propSet[index];
	}
	else {
		throw out_of_range("The index of the property to get is out of range of the array of properties for this representation.");
	}
}

void AbstractRepresentation::setInterpretation(AbstractFeatureInterpretation* interp)
{
	if (interp == nullptr) {
		throw invalid_argument("Cannot set a null interpretation to a representation");
	}
	if (getRepository() == nullptr) {
		interp->getRepository()->addOrReplaceDataObject(this);
	}

	getRepository()->addRelationship(this, interp);

	if (gsoapProxy2_0_1 != nullptr) {
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractRepresentation*>(gsoapProxy2_0_1)->RepresentedInterpretation = interp->newResqmlReference();
	}
#if WITH_EXPERIMENTAL
	else if (gsoapProxy2_2 != nullptr) {
		static_cast<gsoap_eml2_2::resqml22__AbstractRepresentation*>(gsoapProxy2_2)->RepresentedInterpretation = interp->newEml22Reference();
	}
#endif
	else
		throw logic_error("Not implemented yet");
}

AbstractFeatureInterpretation* AbstractRepresentation::getInterpretation() const
{
	return getRepository()->getDataObjectByUuid<AbstractFeatureInterpretation>(getInterpretationUuid());
}

gsoap_resqml2_0_1::eml20__DataObjectReference* AbstractRepresentation::getInterpretationDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractRepresentation*>(gsoapProxy2_0_1)->RepresentedInterpretation != nullptr ?
			static_cast<gsoap_resqml2_0_1::resqml20__AbstractRepresentation*>(gsoapProxy2_0_1)->RepresentedInterpretation : nullptr;
	}
#if WITH_EXPERIMENTAL
	else if (gsoapProxy2_2 != nullptr) {
		return static_cast<gsoap_eml2_2::resqml22__AbstractRepresentation*>(gsoapProxy2_2)->RepresentedInterpretation != nullptr ?
			misc::eml22ToEml20Reference(static_cast<gsoap_eml2_2::resqml22__AbstractRepresentation*>(gsoapProxy2_2)->RepresentedInterpretation, gsoapProxy2_2->soap) : nullptr;
	}
#endif
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string AbstractRepresentation::getInterpretationUuid() const
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getInterpretationDor();
	return dor == nullptr ? string() : dor->UUID;
}

std::string AbstractRepresentation::getInterpretationContentType() const
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getInterpretationDor();
	return dor == nullptr ? string() : dor->ContentType;
}

std::vector<SubRepresentation*> AbstractRepresentation::getSubRepresentationSet() const
{
	return repository->getSourceObjects<SubRepresentation>(this);
}

unsigned int AbstractRepresentation::getSubRepresentationCount() const
{
	return getSubRepresentationSet().size();
}

SubRepresentation* AbstractRepresentation::getSubRepresentation(unsigned int index) const
{
	const std::vector<SubRepresentation*>& subRepresentationSet = getSubRepresentationSet();

	if (index >= subRepresentationSet.size()) {
		throw range_error("The subrepresentation at the specified index is out of range.");
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
	return getFaultSubRepresentationSet().size();
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
		throw range_error("The seismic support of the patch at the specified index is out of range.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(patchIndex);
		if (geom == nullptr || geom->SeismicCoordinates == nullptr) {
			return nullptr;
		}

		return getRepository()->getDataObjectByUuid<AbstractRepresentation>(geom->SeismicCoordinates->SeismicSupport->UUID);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::set<AbstractRepresentation*> AbstractRepresentation::getAllSeismicSupport() const
{
	std::set<AbstractRepresentation*> result;
	const unsigned int patchCount = getPatchCount();
	for (size_t patchIndex = 0; patchIndex < patchCount; ++patchIndex)
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
		throw range_error("The index of the representation set representation is out of range.");
	}

	return representationSetRepresentationSet[index];
}

void AbstractRepresentation::loadTargetRelationships()
{
	gsoap_resqml2_0_1::eml20__DataObjectReference const* dor = getInterpretationDor();
	if (dor != nullptr) {
		convertDorIntoRel<RESQML2_NS::AbstractFeatureInterpretation>(dor);
	}

	// CRS
	for (unsigned int patchIndex = 0; patchIndex < getPatchCount(); ++patchIndex) {
		dor = getLocalCrsDor(patchIndex);
		if (dor != nullptr) {
			convertDorIntoRel<RESQML2_NS::AbstractLocal3dCrs>(dor);
		}
	}

	// TODO : Currently, only one HDF proxy per representation is supported. It can be multiple (for example, regarding IJK parametric grid, parameters in one hdf proxy and control points in another one)
	dor = getHdfProxyDor();
	if (dor != nullptr) {
		convertDorIntoRel<COMMON_NS::AbstractHdfProxy>(dor);
	}

	// Seismic support
	if (gsoapProxy2_0_1 != nullptr) {
		// Seismic support
		for (unsigned int patchIndex = 0; patchIndex < getPatchCount(); ++patchIndex) {
			gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(patchIndex);
			if (geom != nullptr && geom->SeismicCoordinates != nullptr) {
				if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Seismic3dCoordinates) {
					gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates const* seis3dInfo = static_cast<gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates * const>(geom->SeismicCoordinates);
					convertDorIntoRel<AbstractRepresentation>(seis3dInfo->SeismicSupport);
				}
				else if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Seismic2dCoordinates) {
					gsoap_resqml2_0_1::resqml20__Seismic2dCoordinates const* seis2dInfo = static_cast<gsoap_resqml2_0_1::resqml20__Seismic2dCoordinates * const>(geom->SeismicCoordinates);
					convertDorIntoRel<AbstractRepresentation>(seis2dInfo->SeismicSupport);
				}
			}
		}
	}
	// TODO : else if (gsoapProxy2_2 != nullptr)
}

void AbstractRepresentation::addSeismic3dCoordinatesToPatch(const unsigned int patchIndex, double* inlines, double* crosslines, const unsigned int& pointCount,
	RESQML2_NS::AbstractRepresentation* seismicSupport, COMMON_NS::AbstractHdfProxy* proxy)
{
	if (gsoapProxy2_0_1 != nullptr) {
		getRepository()->addRelationship(this, proxy);

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
		getRepository()->addRelationship(this, seismicSupport);

		// inlines XML
		gsoap_resqml2_0_1::resqml20__DoubleHdf5Array* inlineValues = gsoap_resqml2_0_1::soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
		inlineValues->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		inlineValues->Values->HdfProxy = proxy->newResqmlReference();
		ostringstream oss;
		oss << "inlineCoordinates_patch" << patchIndex;
		inlineValues->Values->PathInHdfFile = "/RESQML/" + getUuid() + "/" + oss.str();
		patch->InlineCoordinates = inlineValues;

		// inlines HDF
		hsize_t dim[] = { pointCount };
		proxy->writeArrayNdOfDoubleValues(getUuid(), oss.str(), inlines, dim, 1);

		// crosslines XML
		gsoap_resqml2_0_1::resqml20__DoubleHdf5Array* crosslineValues = gsoap_resqml2_0_1::soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
		crosslineValues->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		crosslineValues->Values->HdfProxy = proxy->newResqmlReference();
		ostringstream oss2;
		oss2 << "crosslineCoordinates_patch" << patchIndex;
		crosslineValues->Values->PathInHdfFile = "/RESQML/" + getUuid() + "/" + oss2.str();
		patch->CrosslineCoordinates = crosslineValues;

		// crosslines HDF
		proxy->writeArrayNdOfDoubleValues(getUuid(), oss2.str(), crosslines, dim, 1);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractRepresentation::addSeismic3dCoordinatesToPatch(const unsigned int patchIndex, const double& startInline, const double& incrInline, const unsigned int& countInline,
	const double& startCrossline, const double& incrCrossline, const unsigned int& countCrossline,
	RESQML2_NS::AbstractRepresentation* seismicSupport)
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
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractRepresentation::addSeismic2dCoordinatesToPatch(const unsigned int patchIndex, double* lineAbscissa,
	RESQML2_NS::AbstractRepresentation* seismicSupport, COMMON_NS::AbstractHdfProxy* proxy)
{
	if (gsoapProxy2_0_1 != nullptr) {
		getRepository()->addRelationship(this, proxy);

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
		getRepository()->addRelationship(this, seismicSupport);

		// abscissa XML
		gsoap_resqml2_0_1::resqml20__DoubleHdf5Array* abscissaValues = gsoap_resqml2_0_1::soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
		abscissaValues->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		abscissaValues->Values->HdfProxy = proxy->newResqmlReference();
		ostringstream oss;
		oss << "lineAbscissa_patch" << patchIndex;
		abscissaValues->Values->PathInHdfFile = "/RESQML/" + getUuid() + "/" + oss.str();
		patch->LineAbscissa = abscissaValues;

		// inlines HDF
		unsigned long long pointCount = getXyzPointCountOfPatch(patchIndex);
		proxy->writeArrayNdOfDoubleValues(getUuid(), oss.str(), lineAbscissa, &pointCount, 1);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractRepresentation::getSeismicLineAbscissaOfPointsOfPatch(unsigned int patchIndex, double* values) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__Seismic2dCoordinates* seisInfo = getSeismic2dCoordinates(patchIndex);
		if (seisInfo == nullptr) {
			throw invalid_argument("The patch of this representation has not got any seismic information.");
		}

		if (seisInfo->LineAbscissa->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
			gsoap_resqml2_0_1::resqml20__DoubleHdf5Array* dblValues = static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(seisInfo->LineAbscissa);
			getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dblValues->Values->HdfProxy->UUID)->readArrayNdOfDoubleValues(dblValues->Values->PathInHdfFile, values);
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
		gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates* seisInfo = getSeismic3dCoordinates(patchIndex);
		if (seisInfo == nullptr) {
			throw invalid_argument("The patch of this representation has not got any seismic information.");
		}

		if (seisInfo->InlineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
			gsoap_resqml2_0_1::resqml20__DoubleHdf5Array* dblValues = static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(seisInfo->InlineCoordinates);
			getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dblValues->Values->HdfProxy->UUID)->readArrayNdOfDoubleValues(dblValues->Values->PathInHdfFile, values);
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
		gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates* seisInfo = getSeismic3dCoordinates(patchIndex);
		if (seisInfo == nullptr) {
			throw invalid_argument("The patch of this representation has not got any seismic information.");
		}

		if (seisInfo->CrosslineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
			gsoap_resqml2_0_1::resqml20__DoubleHdf5Array* dblValues = static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(seisInfo->CrosslineCoordinates);
			getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dblValues->Values->HdfProxy->UUID)->readArrayNdOfDoubleValues(dblValues->Values->PathInHdfFile, values);
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
		throw range_error("The patch index is out of range");
	}

	return nullptr;
}
