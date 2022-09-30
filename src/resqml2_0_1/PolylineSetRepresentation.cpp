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
#include "PolylineSetRepresentation.h"

#include <algorithm>
#include <sstream>

#include <hdf5.h>

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../eml2/AbstractLocal3dCrs.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* PolylineSetRepresentation::XML_NS = "resqml20";

void PolylineSetRepresentation::init(COMMON_NS::DataObjectRepository * repo,
									 const std::string & guid, const std::string & title)
{
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREPolylineSetRepresentation(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addDataObject(this);
}

PolylineSetRepresentation::PolylineSetRepresentation(COMMON_NS::DataObjectRepository * repo, const string & guid, const string & title)
{
	init(repo, guid, title);
}

PolylineSetRepresentation::PolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title)
{
	if (interp == nullptr) {
		throw invalid_argument("You must provide an interpretation");
	}
	init(interp->getRepository(), guid, title);

	setInterpretation(interp);
}

PolylineSetRepresentation::PolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title,
	gsoap_eml2_3::resqml22__LineRole roleKind)
{
	if (interp == nullptr) {
		throw invalid_argument("You must provide an interpretation");
	}
	if (roleKind == gsoap_eml2_3::resqml22__LineRole::break_x0020line) {
		throw invalid_argument("Break line role is not supported in v2.0.1");
	}

	init(interp->getRepository(), guid, title);
	static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LineRole = (resqml20__LineRole*)soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml20__LineRole));
	(*static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LineRole) = static_cast<resqml20__LineRole>(roleKind);

	setInterpretation(interp);
}

void PolylineSetRepresentation::pushBackGeometryPatch(
				unsigned int const* nodeCountPerPolyline, double const* nodes,
				unsigned int polylineCount, bool allPolylinesClosedFlag,
				EML2_NS::AbstractHdfProxy * proxy, EML2_NS::AbstractLocal3dCrs* localCrs)
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

	resqml20__PolylineSetPatch* patch = soap_new_resqml20__PolylineSetPatch(gsoapProxy2_0_1->soap);
	patch->PatchIndex = static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch.size();

	getRepository()->addRelationship(this, proxy);

	// node count
	resqml20__IntegerHdf5Array* xmlNodeCountPerPolyline = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	xmlNodeCountPerPolyline->NullValue = (std::numeric_limits<int>::max)();
	xmlNodeCountPerPolyline->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlNodeCountPerPolyline->Values->HdfProxy = proxy->newResqmlReference();
	ostringstream ossForHdf;
	ossForHdf << "NodeCountPerPolyline_patch" << patch->PatchIndex;
	xmlNodeCountPerPolyline->Values->PathInHdfFile = getHdfGroup() + "/" + ossForHdf.str();
	patch->NodeCountPerPolyline = xmlNodeCountPerPolyline;
	// ************ HDF *************
	hsize_t dim = polylineCount;
	proxy->writeArrayNd(getHdfGroup(),
		ossForHdf.str(), COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT32,
		nodeCountPerPolyline,
		&dim, 1);

	// closed polylines
	resqml20__BooleanConstantArray* xmlClosedPolylines = soap_new_resqml20__BooleanConstantArray(gsoapProxy2_0_1->soap);
	xmlClosedPolylines->Count = polylineCount;
	xmlClosedPolylines->Value = allPolylinesClosedFlag;
	patch->ClosedPolylines = xmlClosedPolylines;

	// XYZ points
	unsigned int nodeCount = 0;
	for (unsigned int i = 0; i < polylineCount; ++i) {
		nodeCount += nodeCountPerPolyline[i];
	}
	uint64_t pointCountDims = nodeCount;
	patch->Geometry = createPointGeometryPatch2_0_1(patch->PatchIndex, nodes, localCrs, &pointCountDims, 1, proxy);

	static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch.push_back(patch);
	getRepository()->addRelationship(this, localCrs);
}

void PolylineSetRepresentation::pushBackGeometryPatch(
				unsigned int const* nodeCountPerPolyline, double const* nodes,
				unsigned int polylineCount, bool * polylineClosedFlags,
				EML2_NS::AbstractHdfProxy * proxy, EML2_NS::AbstractLocal3dCrs* localCrs)
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

	resqml20__PolylineSetPatch* patch = soap_new_resqml20__PolylineSetPatch(gsoapProxy2_0_1->soap);
	patch->PatchIndex = static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch.size();

	getRepository()->addRelationship(this, proxy);

	// node count
	resqml20__IntegerHdf5Array* xmlNodeCountPerPolyline = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	xmlNodeCountPerPolyline->NullValue = (std::numeric_limits<int>::max)();
	xmlNodeCountPerPolyline->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlNodeCountPerPolyline->Values->HdfProxy = proxy->newResqmlReference();
	ostringstream ossForHdf;
	ossForHdf << "NodeCountPerPolyline_patch" << patch->PatchIndex;
	xmlNodeCountPerPolyline->Values->PathInHdfFile = getHdfGroup() + "/" + ossForHdf.str();
	patch->NodeCountPerPolyline = xmlNodeCountPerPolyline;
	// ************ HDF *************
	hsize_t dim = polylineCount;
	proxy->writeArrayNd(getHdfGroup(),
		ossForHdf.str(), COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT32,
		nodeCountPerPolyline,
		&dim, 1);

	// closed polylines
	resqml20__BooleanHdf5Array* xmlClosedPolylines = soap_new_resqml20__BooleanHdf5Array(gsoapProxy2_0_1->soap);
	xmlClosedPolylines->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlClosedPolylines->Values->HdfProxy = proxy->newResqmlReference();
	ossForHdf.str("");
	ossForHdf.clear();
	ossForHdf << "ClosedPolylines_patch" << patch->PatchIndex;
	xmlClosedPolylines->Values->PathInHdfFile = getHdfGroup() + "/" + ossForHdf.str();
	patch->ClosedPolylines = xmlClosedPolylines;
	// ************ HDF *************
	proxy->writeArrayNd(getHdfGroup(),
		ossForHdf.str(), COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT8,
		polylineClosedFlags,
		&dim, 1);

	// XYZ points
	uint64_t xyzPtDim = 0;
	for (unsigned int i = 0; i < polylineCount; ++i) {
		xyzPtDim += nodeCountPerPolyline[i];
	}
	patch->Geometry = createPointGeometryPatch2_0_1(patch->PatchIndex, nodes, localCrs, &xyzPtDim, 1, proxy);

	static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch.push_back(patch);
	getRepository()->addRelationship(this, localCrs);
}

COMMON_NS::DataObjectReference PolylineSetRepresentation::getHdfProxyDor() const
{
	resqml20__PolylineSetPatch* patch = static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch[0];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanConstantArray) {
		if (patch->NodeCountPerPolyline->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			return COMMON_NS::DataObjectReference(static_cast<resqml20__IntegerHdf5Array*>(patch->NodeCountPerPolyline)->Values->HdfProxy);
		}
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array)
	{
		return COMMON_NS::DataObjectReference(static_cast<resqml20__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->HdfProxy);
	}

	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

resqml20__PointGeometry* PolylineSetRepresentation::getPointGeometry2_0_1(uint64_t patchIndex) const
{
	if (patchIndex < static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch.size() &&
		static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch[patchIndex]->Geometry->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__PointGeometry)
			return static_cast<resqml20__PointGeometry*>(static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch[patchIndex]->Geometry);
	else
		return nullptr;
}

uint64_t PolylineSetRepresentation::getPolylineCountOfPatch(uint64_t patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw std::out_of_range("patchIndex id out of range.");
	}

	resqml20__PolylineSetPatch* patch = static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanConstantArray)
	{
		return static_cast<resqml20__BooleanConstantArray*>(patch->ClosedPolylines)->Count;
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array)
	{
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__BooleanHdf5Array*>(patch->ClosedPolylines)->Values;
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		return hdfProxy->getElementCount(dataset->PathInHdfFile);
	}

	return 0;
}

uint64_t PolylineSetRepresentation::getPolylineCountOfAllPatches() const
{
	uint64_t result = 0;

	for (size_t i = 0; i < static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch.size(); i++) {
		result += getPolylineCountOfPatch(i);
	}

	return result;
}

void PolylineSetRepresentation::getNodeCountPerPolylineInPatch(uint64_t patchIndex, unsigned int * nodeCountPerPolyline) const
{
	if (patchIndex >= getPatchCount()) {
		throw std::out_of_range("patchIndex id out of range.");
	}
	resqml20__PolylineSetPatch* patch = static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch[patchIndex];
	readArrayNdOfUInt32Values(patch->NodeCountPerPolyline, nodeCountPerPolyline);
}

void PolylineSetRepresentation::getNodeCountPerPolylineOfAllPatches(unsigned int * NodeCountPerPolyline) const
{
	_resqml20__PolylineSetRepresentation* rep = static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1);
	for (size_t i = 0; i < rep->LinePatch.size(); ++i)
	{
		getNodeCountPerPolylineInPatch(i, NodeCountPerPolyline);
		NodeCountPerPolyline += getPolylineCountOfPatch(i);
	}
}

void PolylineSetRepresentation::getXyzPointsOfPatch(uint64_t patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	resqml20__PointGeometry* pointGeom = getPointGeometry2_0_1(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array) {
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__Point3dHdf5Array*>(pointGeom->Points)->Coordinates;
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, xyzPoints);
	}
	else
		throw invalid_argument("The geometry of the representation either does not exist or it is not an explicit one.");
}

uint64_t PolylineSetRepresentation::getPatchCount() const
{
    return static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch.size();
}

bool PolylineSetRepresentation::areAllPolylinesClosedOfPatch(uint64_t patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	resqml20__PolylineSetPatch* patch = static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanConstantArray) {
		return static_cast<resqml20__BooleanConstantArray*>(patch->ClosedPolylines)->Value;
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array) {
		const uint64_t polylineCount = getPolylineCountOfPatch(patchIndex);
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__BooleanHdf5Array*>(patch->ClosedPolylines)->Values;

		std::unique_ptr<int8_t[]> tmp(new int8_t[polylineCount]);
		getHdfProxyFromDataset(dataset)->readArrayNdOfInt8Values(static_cast<resqml20__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp.get());
		return find(tmp.get(), tmp.get() + polylineCount, 0) == tmp.get() + polylineCount;
	}
	else
		throw logic_error("Not yet implemented.");
}

bool PolylineSetRepresentation::areAllPolylinesClosedOfAllPatches() const
{
	_resqml20__PolylineSetRepresentation* rep = static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1);
	for (size_t patchIndex = 0; patchIndex < rep->LinePatch.size(); patchIndex++) {
		if (!areAllPolylinesClosedOfPatch(patchIndex)) {
			return false;
		}
	}

	return true;
}

bool PolylineSetRepresentation::areAllPolylinesNonClosedOfPatch(uint64_t patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	resqml20__PolylineSetPatch* patch = static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanConstantArray) {
		return static_cast<resqml20__BooleanConstantArray*>(patch->ClosedPolylines)->Value == false;
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array) {
		const uint64_t polylineCount = getPolylineCountOfPatch(patchIndex);
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__BooleanHdf5Array*>(patch->ClosedPolylines)->Values;

		std::unique_ptr<int8_t[]> tmp(new int8_t[polylineCount]);
		getHdfProxyFromDataset(dataset)->readArrayNdOfInt8Values(static_cast<resqml20__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp.get());
		return find_if(tmp.get(), tmp.get() + polylineCount, [](char i) {return i != 0; }) == tmp.get() + polylineCount;
	}
	else
		throw logic_error("Not yet implemented.");
}

bool PolylineSetRepresentation::areAllPolylinesNonClosedOfAllPatches() const
{
	_resqml20__PolylineSetRepresentation* rep = static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1);
	for (size_t patchIndex = 0; patchIndex < rep->LinePatch.size(); patchIndex++) {
		if (!areAllPolylinesNonClosedOfPatch(patchIndex)) {
			return false;
		}
	}

	return true;
}
		
void PolylineSetRepresentation::getClosedFlagPerPolylineOfPatch(uint64_t patchIndex, bool * closedFlagPerPolyline) const
{
	uint64_t polylineCount = getPolylineCountOfPatch(patchIndex);
	resqml20__PolylineSetPatch* patch = static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanConstantArray) {
		fill(closedFlagPerPolyline, closedFlagPerPolyline + polylineCount, static_cast<resqml20__BooleanConstantArray*>(patch->ClosedPolylines)->Value);
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array) {
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__BooleanHdf5Array*>(patch->ClosedPolylines)->Values;

		std::unique_ptr<int8_t[]> tmp(new int8_t[polylineCount]);
		getHdfProxyFromDataset(dataset)->readArrayNdOfInt8Values(static_cast<resqml20__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp.get());
		for (size_t i = 0; i < polylineCount; ++i) {
			closedFlagPerPolyline[i] = tmp[i];
		}
	}
	else
		throw logic_error("Not yet implemented.");
}

void PolylineSetRepresentation::getClosedFlagPerPolylineOfAllPatches(bool * closedFlagPerPolyline) const
{
	_resqml20__PolylineSetRepresentation* rep = static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1);
	for (size_t i = 0; i < rep->LinePatch.size(); ++i) {
		getClosedFlagPerPolylineOfPatch(i, closedFlagPerPolyline);
		closedFlagPerPolyline += getPolylineCountOfPatch(i);
	}
}

bool PolylineSetRepresentation::hasALineRole() const
{
	return static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LineRole != nullptr;
}

gsoap_eml2_3::resqml22__LineRole PolylineSetRepresentation::getLineRole() const
{
	if (!hasALineRole()) {
		throw logic_error("The polylineSet doesn't have any role");
	}

	return static_cast<gsoap_eml2_3::resqml22__LineRole>(*static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LineRole);
}

void PolylineSetRepresentation::setLineRole(gsoap_eml2_3::resqml22__LineRole lineRole)
{
	if (lineRole == gsoap_eml2_3::resqml22__LineRole::break_x0020line) {
		throw std::invalid_argument("Break line enumerated value is not part of RESQML 2.0.1");
	}
	if (!hasALineRole()) {
		static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LineRole = (resqml20__LineRole*)soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml20__LineRole));
	}

	*static_cast<_resqml20__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LineRole = static_cast<resqml20__LineRole>(lineRole);
}
