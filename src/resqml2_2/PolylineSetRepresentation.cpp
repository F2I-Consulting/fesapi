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

#include <hdf5.h>

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../eml2/AbstractLocal3dCrs.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* PolylineSetRepresentation::XML_NS = "resqml22";

void PolylineSetRepresentation::init(COMMON_NS::DataObjectRepository * repo,
									 const std::string & guid, const std::string & title)
{
	gsoapProxy2_3 = soap_new_resqml22__PolylineSetRepresentation(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

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
	init(interp->getRepository(), guid, title);
	setLineRole(roleKind);

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

	resqml22__PolylineSetPatch* patch = soap_new_resqml22__PolylineSetPatch(gsoapProxy2_3->soap);

	getRepository()->addRelationship(this, proxy);

	// node count
	eml23__IntegerXmlArray* xmlNodeCountPerPolyline = soap_new_eml23__IntegerXmlArray(gsoapProxy2_3->soap);
	xmlNodeCountPerPolyline->CountPerValue = 1;
	xmlNodeCountPerPolyline->Values = std::to_string(nodeCountPerPolyline[0]);
	for (size_t i = 1; i < polylineCount; ++i) {
		xmlNodeCountPerPolyline->Values += " " + std::to_string(nodeCountPerPolyline[1]);
	}
	patch->NodeCountPerPolyline = xmlNodeCountPerPolyline;

	// closed polylines
	eml23__BooleanConstantArray* xmlClosedPolylines = soap_new_eml23__BooleanConstantArray(gsoapProxy2_3->soap);
	xmlClosedPolylines->Count = polylineCount;
	xmlClosedPolylines->Value = allPolylinesClosedFlag;
	patch->ClosedPolylines = xmlClosedPolylines;

	// XYZ points
	uint64_t nodeCount = 0;
	uint64_t intervalCount = 0;
	for (size_t i = 0; i < polylineCount; ++i) {
		nodeCount += nodeCountPerPolyline[i];
		intervalCount += nodeCountPerPolyline[i] - 1;
	}
	patch->NodeCount = nodeCount;
	patch->IntervalCount = intervalCount;
	patch->Geometry = createPointGeometryPatch2_2(static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch.size(), nodes, localCrs, &nodeCount, 1, proxy);

	static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch.push_back(patch);
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

	resqml22__PolylineSetPatch* patch = soap_new_resqml22__PolylineSetPatch(gsoapProxy2_3->soap);

	getRepository()->addRelationship(this, proxy);

	// node count
	eml23__IntegerXmlArray* xmlNodeCountPerPolyline = soap_new_eml23__IntegerXmlArray(gsoapProxy2_3->soap);
	xmlNodeCountPerPolyline->CountPerValue = 1;
	xmlNodeCountPerPolyline->Values = std::to_string(nodeCountPerPolyline[0]);
	for (size_t i = 1; i < polylineCount; ++i) {
		xmlNodeCountPerPolyline->Values += " " + std::to_string(nodeCountPerPolyline[1]);
	}
	patch->NodeCountPerPolyline = xmlNodeCountPerPolyline;

	// closed polylines
	eml23__BooleanXmlArray* xmlClosedPolylines = soap_new_eml23__BooleanXmlArray(gsoapProxy2_3->soap);
	xmlClosedPolylines->CountPerValue = 1;
	xmlClosedPolylines->Values = polylineClosedFlags[0] ? "true" : "false";
	for (size_t i = 1; i < polylineCount; ++i) {
		xmlClosedPolylines->Values += " " + polylineClosedFlags[i] ? "true" : "false";
	}
	patch->ClosedPolylines = xmlClosedPolylines;

	// XYZ points
	uint64_t nodeCount = 0;
	uint64_t intervalCount = 0;
	for (size_t i = 0; i < polylineCount; ++i) {
		nodeCount += nodeCountPerPolyline[i];
		intervalCount += nodeCountPerPolyline[i] - 1;
	}
	patch->NodeCount = nodeCount;
	patch->IntervalCount = intervalCount;
	patch->Geometry = createPointGeometryPatch2_2(static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch.size(), nodes, localCrs, &nodeCount, 1, proxy);

	static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch.push_back(patch);
	getRepository()->addRelationship(this, localCrs);
}

COMMON_NS::DataObjectReference PolylineSetRepresentation::getHdfProxyDor() const
{
	resqml22__PolylineSetPatch* patch = static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch[0];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanConstantArray) {
		if (patch->NodeCountPerPolyline->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__IntegerExternalArray*>(patch->NodeCountPerPolyline)->Values->ExternalDataArrayPart[0]));
		}
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray)
	{
		return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__BooleanExternalArray*>(patch->ClosedPolylines)->Values->ExternalDataArrayPart[0]));
	}

	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

resqml22__PointGeometry* PolylineSetRepresentation::getPointGeometry2_2(uint64_t patchIndex) const
{
	if (patchIndex < static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch.size() &&
		static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch[patchIndex]->Geometry->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__PointGeometry)
			return static_cast<resqml22__PointGeometry*>(static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch[patchIndex]->Geometry);
	
	return nullptr;
}

uint64_t PolylineSetRepresentation::getPolylineCountOfPatch(uint64_t patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw std::out_of_range("patchIndex id out of range.");
	}

	resqml22__PolylineSetPatch* patch = static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanConstantArray) {
		return static_cast<eml23__BooleanConstantArray*>(patch->ClosedPolylines)->Count;
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray) {
		auto const* daPart = static_cast<eml23__BooleanExternalArray*>(patch->ClosedPolylines)->Values->ExternalDataArrayPart[0];
		return getOrCreateHdfProxyFromDataArrayPart(daPart) ->getElementCount(daPart->PathInExternalFile);
	}

	return 0;
}

uint64_t PolylineSetRepresentation::getPolylineCountOfAllPatches() const
{
	uint64_t result = 0;

	for (size_t i = 0; i < static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch.size(); i++) {
		result += getPolylineCountOfPatch(i);
	}

	return result;
}

void PolylineSetRepresentation::getNodeCountPerPolylineInPatch(uint64_t patchIndex, unsigned int * nodeCountPerPolyline) const
{
	if (patchIndex >= getPatchCount()) {
		throw std::out_of_range("patchIndex id out of range.");
	}

	resqml22__PolylineSetPatch* patch = static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch[patchIndex];
	readArrayNdOfUInt32Values(patch->NodeCountPerPolyline, nodeCountPerPolyline);
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

void PolylineSetRepresentation::getXyzPointsOfPatch(uint64_t patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	resqml22__PointGeometry* pointGeom = getPointGeometry2_2(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray)
	{
		auto const* daPart = static_cast<resqml22__Point3dExternalArray*>(pointGeom->Points)->Coordinates->ExternalDataArrayPart[0];
		getOrCreateHdfProxyFromDataArrayPart(daPart) ->readArrayNdOfDoubleValues(daPart->PathInExternalFile, xyzPoints);
	}
	else
		throw invalid_argument("The geometry of the representation either does not exist or it is not an explicit one.");
}

uint64_t PolylineSetRepresentation::getPatchCount() const
{
    return static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch.size();
}

bool PolylineSetRepresentation::areAllPolylinesClosedOfPatch(uint64_t patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	resqml22__PolylineSetPatch* patch = static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanConstantArray)
	{
		return static_cast<eml23__BooleanConstantArray*>(patch->ClosedPolylines)->Value;
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray)
	{
		const uint64_t polylineCount = getPolylineCountOfPatch(patchIndex);
		eml23__ExternalDataArrayPart const * daPart = static_cast<eml23__BooleanExternalArray*>(patch->ClosedPolylines)->Values->ExternalDataArrayPart[0];

		std::unique_ptr<char[]> tmp(new char[polylineCount]);
		getOrCreateHdfProxyFromDataArrayPart(daPart)->readArrayNdOfCharValues(daPart->PathInExternalFile, tmp.get());
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

bool PolylineSetRepresentation::areAllPolylinesNonClosedOfPatch(uint64_t patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	resqml22__PolylineSetPatch* patch = static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanConstantArray)
	{
		return static_cast<eml23__BooleanConstantArray*>(patch->ClosedPolylines)->Value == false;
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray)
	{
		const uint64_t polylineCount = getPolylineCountOfPatch(patchIndex);
		eml23__ExternalDataArrayPart const * daPart = static_cast<eml23__BooleanExternalArray*>(patch->ClosedPolylines)->Values->ExternalDataArrayPart[0];

		std::unique_ptr<char[]> tmp(new char[polylineCount]);
		getOrCreateHdfProxyFromDataArrayPart(daPart)->readArrayNdOfCharValues(daPart->PathInExternalFile, tmp.get());
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
		
void PolylineSetRepresentation::getClosedFlagPerPolylineOfPatch(uint64_t patchIndex, bool * closedFlagPerPolyline) const
{
	uint64_t polylineCount = getPolylineCountOfPatch(patchIndex);
	resqml22__PolylineSetPatch* patch = static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanConstantArray) {
		fill(closedFlagPerPolyline, closedFlagPerPolyline + polylineCount, static_cast<eml23__BooleanConstantArray*>(patch->ClosedPolylines)->Value);
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray) {
		eml23__ExternalDataArrayPart const * daPart = static_cast<eml23__BooleanExternalArray*>(patch->ClosedPolylines)->Values->ExternalDataArrayPart[0];

		std::unique_ptr<char[]> tmp(new char[polylineCount]);
		getOrCreateHdfProxyFromDataArrayPart(daPart)->readArrayNdOfCharValues(daPart->PathInExternalFile, tmp.get());
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
		throw logic_error("The polyline doesn't have any role");
	}

	gsoap_eml2_3::resqml22__LineRole result;
	if (soap_s2resqml22__LineRole(gsoapProxy2_3->soap, static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LineRole->c_str(), &result) == SOAP_OK) {
		return result;
	}

	throw logic_error("The linerole is not recognized and extended line roel is not supported yet.");
}

void PolylineSetRepresentation::setLineRole(gsoap_eml2_3::resqml22__LineRole lineRole)
{
	if (!hasALineRole()) {
		static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LineRole = soap_new_std__string(gsoapProxy2_3->soap);
	}

	*static_cast<_resqml22__PolylineSetRepresentation*>(gsoapProxy2_3)->LineRole = soap_resqml22__LineRole2s(gsoapProxy2_3->soap, lineRole);
}
