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

#include <sstream>
#include <algorithm>
#include <stdexcept>

#include <hdf5.h>

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../resqml2/AbstractLocal3dCrs.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

void PolylineSetRepresentation::init(COMMON_NS::DataObjectRepository * repo,
									 const std::string & guid, const std::string & title)
{
	gsoapProxy2_3 = soap_new_resqml22__PolylineSetRepresentation(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addOrReplaceDataObject(this);
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
	init(interp->getRepository(), guid, title);
	static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LineRole = (resqml22__LineRole*)soap_malloc(gsoapProxy2_3->soap, sizeof(resqml22__LineRole));
	(*static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LineRole) = roleKind;

	setInterpretation(interp);
}

void PolylineSetRepresentation::pushBackGeometryPatch(
				unsigned int const* nodeCountPerPolyline, double const* nodes,
				unsigned int polylineCount, bool allPolylinesClosedFlag,
				EML2_NS::AbstractHdfProxy * proxy, RESQML2_NS::AbstractLocal3dCrs* localCrs)
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

	resqml22__PolylineSetPatch* patch = soap_new_resqml22__PolylineSetPatch(gsoapProxy2_3->soap);

	getRepository()->addRelationship(this, proxy);

	// node count
	eml23__IntegerExternalArray* xmlNodeCountPerPolyline = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	xmlNodeCountPerPolyline->NullValue = (std::numeric_limits<int>::max)();
	xmlNodeCountPerPolyline->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	auto dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	ostringstream ossForHdf;
	ossForHdf << "NodeCountPerPolyline_patch" << static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch.size();
	dsPart->PathInExternalFile = getHdfGroup() + "/" + ossForHdf.str();
	xmlNodeCountPerPolyline->Values->ExternalFileProxy.push_back(dsPart);
	patch->NodeCountPerPolyline = xmlNodeCountPerPolyline;
	// ************ HDF *************
	hsize_t dim = polylineCount;
	proxy->writeArrayNd(getHdfGroup(),
		ossForHdf.str(), H5T_NATIVE_UINT,
		nodeCountPerPolyline,
		&dim, 1);

	// closed polylines
	eml23__BooleanConstantArray* xmlClosedPolylines = soap_new_eml23__BooleanConstantArray(gsoapProxy2_3->soap);
	xmlClosedPolylines->Count = polylineCount;
	xmlClosedPolylines->Value = allPolylinesClosedFlag;
	patch->ClosedPolylines = xmlClosedPolylines;

	// XYZ points
	unsigned int nodeCount = 0;
	for (unsigned int i = 0; i < polylineCount; ++i) {
		nodeCount += nodeCountPerPolyline[i];
	}
	hsize_t pointCountDims = nodeCount;
	patch->Geometry = createPointGeometryPatch2_2(static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch.size(), nodes, localCrs, &pointCountDims, 1, proxy);

	static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch.push_back(patch);
	getRepository()->addRelationship(this, localCrs);
}

void PolylineSetRepresentation::pushBackGeometryPatch(
				unsigned int const* nodeCountPerPolyline, double const* nodes,
				unsigned int polylineCount, bool * polylineClosedFlags,
				EML2_NS::AbstractHdfProxy * proxy, RESQML2_NS::AbstractLocal3dCrs* localCrs)
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

	resqml22__PolylineSetPatch* patch = soap_new_resqml22__PolylineSetPatch(gsoapProxy2_3->soap);

	getRepository()->addRelationship(this, proxy);

	// node count
	eml23__IntegerExternalArray* xmlNodeCountPerPolyline = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	xmlNodeCountPerPolyline->NullValue = (std::numeric_limits<int>::max)();
	xmlNodeCountPerPolyline->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	auto dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	ostringstream ossForHdf;
	ossForHdf << "NodeCountPerPolyline_patch" << static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch.size();
	dsPart->PathInExternalFile = getHdfGroup() + "/" + ossForHdf.str();
	xmlNodeCountPerPolyline->Values->ExternalFileProxy.push_back(dsPart);
	patch->NodeCountPerPolyline = xmlNodeCountPerPolyline;
	// ************ HDF *************
	hsize_t dim = polylineCount;
	proxy->writeArrayNd(getHdfGroup(),
		ossForHdf.str(), H5T_NATIVE_UINT,
		nodeCountPerPolyline,
		&dim, 1);

	// closed polylines
	eml23__BooleanExternalArray* xmlClosedPolylines = soap_new_eml23__BooleanExternalArray(gsoapProxy2_3->soap);
	xmlClosedPolylines->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	ossForHdf.str("");
	ossForHdf.clear();
	ossForHdf << "ClosedPolylines_patch" << static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch.size();
	dsPart->PathInExternalFile = getHdfGroup() + "/" + ossForHdf.str();
	xmlClosedPolylines->Values->ExternalFileProxy.push_back(dsPart);
	patch->ClosedPolylines = xmlClosedPolylines;
	// ************ HDF *************
	proxy->writeArrayNd(getHdfGroup(),
		ossForHdf.str(), H5T_NATIVE_UCHAR,
		polylineClosedFlags,
		&dim, 1);

	// XYZ points
	dim = 0;
	for (unsigned int i = 0; i < polylineCount; ++i) {
		dim += nodeCountPerPolyline[i];
	}
	patch->Geometry = createPointGeometryPatch2_2(static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch.size(), nodes, localCrs, &dim, 1, proxy);

	static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch.push_back(patch);
	getRepository()->addRelationship(this, localCrs);
}

COMMON_NS::DataObjectReference PolylineSetRepresentation::getHdfProxyDor() const
{
	resqml22__PolylineSetPatch* patch = static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch[0];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanConstantArray) {
		if (patch->NodeCountPerPolyline->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			return COMMON_NS::DataObjectReference(static_cast<eml23__IntegerExternalArray*>(patch->NodeCountPerPolyline)->Values->ExternalFileProxy[0]->EpcExternalPartReference);
		}
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray)
	{
		return COMMON_NS::DataObjectReference(static_cast<eml23__BooleanExternalArray*>(patch->ClosedPolylines)->Values->ExternalFileProxy[0]->EpcExternalPartReference);
	}

	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

resqml22__PointGeometry* PolylineSetRepresentation::getPointGeometry2_2(unsigned int patchIndex) const
{
	if (patchIndex < static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch.size() &&
		static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch[patchIndex]->Geometry->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__PointGeometry)
			return static_cast<resqml22__PointGeometry*>(static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch[patchIndex]->Geometry);
	
	return nullptr;
}

unsigned int PolylineSetRepresentation::getPolylineCountOfPatch(unsigned int patchIndex) const
{
	resqml22__PolylineSetPatch* patch = static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanConstantArray)
	{
		return static_cast<eml23__BooleanConstantArray*>(patch->ClosedPolylines)->Count;
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray)
	{
		auto dsPart = static_cast<eml23__BooleanExternalArray*>(patch->ClosedPolylines)->Values->ExternalFileProxy[0];
		return getHdfProxyFromDataset(dsPart) ->getElementCount(dsPart->PathInExternalFile);
	}

	return 0;
}

unsigned int PolylineSetRepresentation::getPolylineCountOfAllPatches() const
{
	unsigned int result = 0;

	for (size_t i = 0; i < static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch.size(); i++) {
		result += getPolylineCountOfPatch(i);
	}

	return result;
}

void PolylineSetRepresentation::getNodeCountPerPolylineInPatch(unsigned int patchIndex, unsigned int * nodeCountPerPolyline) const
{
	resqml22__PolylineSetPatch* patch = static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch[patchIndex];
	readArrayNdOfUIntValues(patch->NodeCountPerPolyline, nodeCountPerPolyline);
}

void PolylineSetRepresentation::getNodeCountPerPolylineOfAllPatches(unsigned int * NodeCountPerPolyline) const
{
	_resqml22__PolylineSetRepresentation* rep = static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3);
	for (size_t i = 0; i < rep->LinePatch.size(); ++i)
	{
		getNodeCountPerPolylineInPatch(i, NodeCountPerPolyline);
		NodeCountPerPolyline += getPolylineCountOfPatch(i);
	}
}

void PolylineSetRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index of the patch is not in the allowed range of patch.");

	resqml22__PointGeometry* pointGeom = getPointGeometry2_2(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray)
	{
		auto dsPart = static_cast<resqml22__Point3dExternalArray*>(pointGeom->Points)->Coordinates->ExternalFileProxy[0];
		getHdfProxyFromDataset(dsPart) ->readArrayNdOfDoubleValues(dsPart->PathInExternalFile, xyzPoints);
	}
	else
		throw invalid_argument("The geometry of the representation either does not exist or it is not an explicit one.");
}

unsigned int PolylineSetRepresentation::getPatchCount() const
{
    return static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch.size();
}

bool PolylineSetRepresentation::areAllPolylinesClosedOfPatch(unsigned int patchIndex) const
{
	resqml22__PolylineSetPatch* patch = static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanConstantArray)
	{
		return static_cast<eml23__BooleanConstantArray*>(patch->ClosedPolylines)->Value;
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray)
	{
		const unsigned int polylineCount = getPolylineCountOfPatch(patchIndex);
		eml23__ExternalDatasetPart const * dsPart = static_cast<eml23__BooleanExternalArray*>(patch->ClosedPolylines)->Values->ExternalFileProxy[0];

		std::unique_ptr<char[]> tmp(new char[polylineCount]);
		getHdfProxyFromDataset(dsPart)->readArrayNdOfCharValues(dsPart->PathInExternalFile, tmp.get());
		const bool result = find(tmp.get(), tmp.get() + polylineCount, 0) == tmp.get() + polylineCount;

		return result;
	}
	else
		throw logic_error("Not yet implemented.");
}

bool PolylineSetRepresentation::areAllPolylinesClosedOfAllPatches() const
{
	_resqml22__PolylineSetRepresentation* rep = static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3);
	for (size_t patchIndex = 0; patchIndex < rep->LinePatch.size(); patchIndex++) {
		if (!areAllPolylinesClosedOfPatch(patchIndex)) {
			return false;
		}
	}

	return true;
}

bool PolylineSetRepresentation::areAllPolylinesNonClosedOfPatch(unsigned int patchIndex) const
{
	resqml22__PolylineSetPatch* patch = static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanConstantArray)
	{
		return static_cast<eml23__BooleanConstantArray*>(patch->ClosedPolylines)->Value == false;
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray)
	{
		const unsigned int polylineCount = getPolylineCountOfPatch(patchIndex);
		eml23__ExternalDatasetPart const * dsPart = static_cast<eml23__BooleanExternalArray*>(patch->ClosedPolylines)->Values->ExternalFileProxy[0];

		std::unique_ptr<char[]> tmp(new char[polylineCount]);
		getHdfProxyFromDataset(dsPart)->readArrayNdOfCharValues(dsPart->PathInExternalFile, tmp.get());
		return find_if(tmp.get(), tmp.get() + polylineCount, [](char i) {return i != 0; }) == tmp.get() + polylineCount;
	}
	else
		throw logic_error("Not yet implemented.");
}

bool PolylineSetRepresentation::areAllPolylinesNonClosedOfAllPatches() const
{
	_resqml22__PolylineSetRepresentation* rep = static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3);
	for (size_t patchIndex = 0; patchIndex < rep->LinePatch.size(); patchIndex++) {
		if (!areAllPolylinesNonClosedOfPatch(patchIndex)) {
			return false;
		}
	}

	return true;
}
		
void PolylineSetRepresentation::getClosedFlagPerPolylineOfPatch(unsigned int patchIndex, bool * closedFlagPerPolyline) const
{
	unsigned int polylineCount = getPolylineCountOfPatch(patchIndex);
	resqml22__PolylineSetPatch* patch = static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanConstantArray) {
		fill(closedFlagPerPolyline, closedFlagPerPolyline + polylineCount, static_cast<eml23__BooleanConstantArray*>(patch->ClosedPolylines)->Value);
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray) {
		eml23__ExternalDatasetPart const * dsPart = static_cast<eml23__BooleanExternalArray*>(patch->ClosedPolylines)->Values->ExternalFileProxy[0];

		std::unique_ptr<char[]> tmp(new char[polylineCount]);
		getHdfProxyFromDataset(dsPart)->readArrayNdOfCharValues(dsPart->PathInExternalFile, tmp.get());
		for (size_t i = 0; i < polylineCount; ++i) {
			closedFlagPerPolyline[i] = tmp[i];
		}
	}
	else
		throw logic_error("Not yet implemented.");
}

void PolylineSetRepresentation::getClosedFlagPerPolylineOfAllPatches(bool * closedFlagPerPolyline) const
{
	_resqml22__PolylineSetRepresentation* rep = static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3);
	for (size_t i = 0; i < rep->LinePatch.size(); ++i) {
		getClosedFlagPerPolylineOfPatch(i, closedFlagPerPolyline);
		closedFlagPerPolyline += getPolylineCountOfPatch(i);
	}
}

bool PolylineSetRepresentation::hasALineRole() const
{
	return static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LineRole != nullptr;
}

gsoap_eml2_3::resqml22__LineRole PolylineSetRepresentation::getLineRole() const
{
	if (!hasALineRole()) {
		throw invalid_argument("The polylineSet doesn't have any role");
	}

	return static_cast<gsoap_eml2_3::resqml22__LineRole>(*static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LineRole);
}

void PolylineSetRepresentation::setLineRole(gsoap_eml2_3::resqml22__LineRole lineRole)
{
	if (lineRole == gsoap_eml2_3::resqml22__LineRole__break_x0020line) {
		throw std::invalid_argument("Break line enumerated value is not part of RESQML 2.0.1");
	}
	if (!hasALineRole()) {
		static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LineRole = (resqml22__LineRole*)soap_malloc(gsoapProxy2_3->soap, sizeof(resqml22__LineRole));
	}

	*static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LineRole = static_cast<resqml22__LineRole>(lineRole);
}
