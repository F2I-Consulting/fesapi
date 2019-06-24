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
#include "resqml2_0_1/PolylineSetRepresentation.h"

#include <sstream>
#include <algorithm>
#include <stdexcept>

#include "hdf5.h"

#include "resqml2/AbstractFeatureInterpretation.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* PolylineSetRepresentation::XML_TAG = "PolylineSetRepresentation";

void PolylineSetRepresentation::init(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
									 const std::string & guid, const std::string & title)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREPolylineSetRepresentation(crs->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	// relationships
	localCrs = crs;
	localCrs->addRepresentation(this);

	if (interp != nullptr) {
		setInterpretation(interp);
	}
}

PolylineSetRepresentation::PolylineSetRepresentation(RESQML2_NS::AbstractLocal3dCrs * crs, const string & guid, const string & title) :
	AbstractRepresentation(nullptr, crs)
{
	init(nullptr, crs, guid, title);
}

PolylineSetRepresentation::PolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
													 const std::string & guid, const std::string & title):
	AbstractRepresentation(interp, crs)
{
	init(interp, crs, guid, title);
}

PolylineSetRepresentation::PolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
													 const std::string & guid, const std::string & title,
													 const resqml2__LineRole & roleKind):
	AbstractRepresentation(interp, crs)
{
	init(interp, crs, guid, title);
	static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LineRole = (resqml2__LineRole*)soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml2__LineRole));
	(*static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LineRole) = roleKind;
}

void PolylineSetRepresentation::pushBackGeometryPatch(
				unsigned int * NodeCountPerPolyline, double * nodes,
				const unsigned int & polylineCount, const bool & allPolylinesClosedFlag,
				COMMON_NS::AbstractHdfProxy * proxy)
{
	resqml2__PolylineSetPatch* patch = soap_new_resqml2__PolylineSetPatch(gsoapProxy2_0_1->soap, 1);
	patch->PatchIndex = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch.size();

	// node count
	resqml2__IntegerHdf5Array* xmlNodeCountPerPolyline = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlNodeCountPerPolyline->NullValue = (std::numeric_limits<int>::max)();
	xmlNodeCountPerPolyline->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlNodeCountPerPolyline->Values->HdfProxy = proxy->newResqmlReference();
	ostringstream ossForHdf;
	ossForHdf << "NodeCountPerPolyline_patch" << patch->PatchIndex;
	xmlNodeCountPerPolyline->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/" + ossForHdf.str();
	patch->NodeCountPerPolyline = xmlNodeCountPerPolyline;
	// ************ HDF *************
	hsize_t dim = polylineCount;
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		ossForHdf.str(), H5T_NATIVE_UINT,
		NodeCountPerPolyline,
		&dim, 1);

	// closed polylines
	resqml2__BooleanConstantArray* xmlClosedPolylines = soap_new_resqml2__BooleanConstantArray(gsoapProxy2_0_1->soap, 1);
	xmlClosedPolylines->Count = polylineCount;
	xmlClosedPolylines->Value = allPolylinesClosedFlag;
	patch->ClosedPolylines = xmlClosedPolylines;

	// XYZ points
	unsigned int NodeCount = 0;
	for (unsigned int i = 0; i < polylineCount; ++i)
		NodeCount += NodeCountPerPolyline[i];
	hsize_t pointCountDims[] = {NodeCount};
	patch->Geometry = createPointGeometryPatch2_0_1(patch->PatchIndex, nodes, pointCountDims, 1, proxy);

	static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch.push_back(patch);
}

void PolylineSetRepresentation::pushBackGeometryPatch(
				unsigned int * NodeCountPerPolyline, double * nodes,
				const unsigned int & polylineCount, bool * polylineClosedFlags,
				COMMON_NS::AbstractHdfProxy * proxy)
{
	resqml2__PolylineSetPatch* patch = soap_new_resqml2__PolylineSetPatch(gsoapProxy2_0_1->soap, 1);
	patch->PatchIndex = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch.size();

	// node count
	resqml2__IntegerHdf5Array* xmlNodeCountPerPolyline = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlNodeCountPerPolyline->NullValue = (std::numeric_limits<int>::max)();
	xmlNodeCountPerPolyline->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlNodeCountPerPolyline->Values->HdfProxy = proxy->newResqmlReference();
	ostringstream ossForHdf;
	ossForHdf << "NodeCountPerPolyline_patch" << patch->PatchIndex;
	xmlNodeCountPerPolyline->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/" + ossForHdf.str();
	patch->NodeCountPerPolyline = xmlNodeCountPerPolyline;
	// ************ HDF *************
	hsize_t dim = polylineCount;
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		ossForHdf.str(), H5T_NATIVE_UINT,
		NodeCountPerPolyline,
		&dim, 1);

	// closed polylines
	resqml2__BooleanHdf5Array* xmlClosedPolylines = soap_new_resqml2__BooleanHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlClosedPolylines->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlClosedPolylines->Values->HdfProxy = proxy->newResqmlReference();
	ossForHdf.str("");
	ossForHdf.clear();
	ossForHdf << "ClosedPolylines_patch" << patch->PatchIndex;
	xmlClosedPolylines->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/" + ossForHdf.str();
	patch->ClosedPolylines = xmlClosedPolylines;
	// ************ HDF *************
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		ossForHdf.str(), H5T_NATIVE_UCHAR,
		polylineClosedFlags,
		&dim, 1);

	// XYZ points
	dim = 0;
	for (unsigned int i = 0; i < polylineCount; ++i)
		dim += NodeCountPerPolyline[i];
	patch->Geometry = createPointGeometryPatch2_0_1(patch->PatchIndex, nodes, &dim, 1, proxy);

	static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch.push_back(patch);
}

string PolylineSetRepresentation::getHdfProxyUuid() const
{
	resqml2__PolylineSetPatch* patch = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch[0];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanConstantArray)
	{
		if (patch->NodeCountPerPolyline->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			return static_cast<resqml2__IntegerHdf5Array*>(patch->NodeCountPerPolyline)->Values->HdfProxy->UUID;
		}
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array)
	{
		return static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->HdfProxy->UUID;
	}

	return getHdfProxyUuidFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

resqml2__PointGeometry* PolylineSetRepresentation::getPointGeometry2_0_1(const unsigned int & patchIndex) const
{
	if (patchIndex < static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch.size() &&
		static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch[patchIndex]->Geometry->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__PointGeometry)
			return static_cast<resqml2__PointGeometry*>(static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch[patchIndex]->Geometry);
	else
		return nullptr;
}

unsigned int PolylineSetRepresentation::getPolylineCountOfPatch(const unsigned int & patchIndex) const
{
	resqml2__PolylineSetPatch* patch = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanConstantArray)
	{
		return static_cast<resqml2__BooleanConstantArray*>(patch->ClosedPolylines)->Count;
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array)
	{
		return hdfProxy->getElementCount(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile);
	}

	return 0;
}

unsigned int PolylineSetRepresentation::getPolylineCountOfAllPatches() const
{
	unsigned int result = 0;

	for (size_t i = 0; i < static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch.size(); i++)
	{
		result += getPolylineCountOfPatch(i);
	}

	return result;
}

void PolylineSetRepresentation::getNodeCountPerPolylineInPatch(const unsigned int & patchIndex, unsigned int * NodeCountPerPolyline) const
{
	resqml2__PolylineSetPatch* patch = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch[patchIndex];
	if (patch->NodeCountPerPolyline->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
	{
		resqml2__IntegerConstantArray* xmlNodeCountPerPolyline = static_cast<resqml2__IntegerConstantArray*>(patch->NodeCountPerPolyline);
		for (ULONG64 i = 0; i < xmlNodeCountPerPolyline->Count; ++i)
			NodeCountPerPolyline[i] = xmlNodeCountPerPolyline->Value;
	}
	else if (patch->NodeCountPerPolyline->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(patch->NodeCountPerPolyline)->Values->PathInHdfFile, NodeCountPerPolyline);
	}
}

void PolylineSetRepresentation::getNodeCountPerPolylineOfAllPatches(unsigned int * NodeCountPerPolyline) const
{
	_resqml2__PolylineSetRepresentation* rep = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1);
	for (size_t i = 0; i < rep->LinePatch.size(); ++i)
	{
		getNodeCountPerPolylineInPatch(i, NodeCountPerPolyline);
		NodeCountPerPolyline += getPolylineCountOfPatch(i);
	}
}

ULONG64 PolylineSetRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index of the patch is not in the allowed range of patch.");

	const unsigned int polylineCount = getPolylineCountOfPatch(patchIndex);
	unsigned int* const nodeCountPerPolyline = new unsigned int[polylineCount];

	getNodeCountPerPolylineInPatch(patchIndex, nodeCountPerPolyline);

	ULONG64 nodeCount = 0;
	for (unsigned int nodeCountPerPolylineIndex = 0; nodeCountPerPolylineIndex < polylineCount; ++nodeCountPerPolylineIndex)
	{
		nodeCount += nodeCountPerPolyline[nodeCountPerPolylineIndex];
	}

	delete[] nodeCountPerPolyline;
	return nodeCount;
}

void PolylineSetRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
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

unsigned int PolylineSetRepresentation::getPatchCount() const
{
    return static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch.size();
}

bool PolylineSetRepresentation::areAllPolylinesClosedOfPatch(const unsigned int & patchIndex) const
{
	resqml2__PolylineSetPatch* patch = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanConstantArray)
	{
		return static_cast<resqml2__BooleanConstantArray*>(patch->ClosedPolylines)->Value;
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array)
	{
		unsigned int polylineCount = getPolylineCountOfPatch(patchIndex);
		hid_t datatype = hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile);

		bool result = true;
		if (H5Tequal(datatype, H5T_NATIVE_CHAR) > 0)
		{
			char* tmp = new char[polylineCount];
			hdfProxy->readArrayNdOfCharValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			if (find(tmp, tmp + polylineCount, 0) != tmp + polylineCount)
				result = false;
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_UCHAR) > 0)
		{
			unsigned char* tmp = new unsigned char[polylineCount];
			hdfProxy->readArrayNdOfUCharValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			if (find(tmp, tmp + polylineCount, 0) != tmp + polylineCount)
				result = false;
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_SHORT) > 0)
		{
			short* tmp = new short[polylineCount];
			hdfProxy->readArrayNdOfShortValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			if (find(tmp, tmp + polylineCount, 0) != tmp + polylineCount)
				result = false;
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_USHORT) > 0)
		{
			unsigned short* tmp = new unsigned short[polylineCount];
			hdfProxy->readArrayNdOfUShortValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			if (find(tmp, tmp + polylineCount, 0) != tmp + polylineCount)
				result = false;
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_INT) > 0)
		{
			int* tmp = new int[polylineCount];
			hdfProxy->readArrayNdOfIntValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			if (find(tmp, tmp + polylineCount, 0) != tmp + polylineCount)
				result = false;
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_UINT) > 0)
		{
			unsigned int* tmp = new unsigned int[polylineCount];
			hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			if (find(tmp, tmp + polylineCount, 0u) != tmp + polylineCount)
				result = false;
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_LONG) > 0)
		{
			long* tmp = new long[polylineCount];
			hdfProxy->readArrayNdOfLongValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			if (find(tmp, tmp + polylineCount, 0) != tmp + polylineCount)
				result = false;
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_ULONG) > 0)
		{
			unsigned long* tmp = new unsigned long[polylineCount];
			hdfProxy->readArrayNdOfULongValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			if (find(tmp, tmp + polylineCount, 0u) != tmp + polylineCount)
				result = false;
			delete [] tmp;
		}
		else
			throw logic_error("Not yet implemented.");

		return result;
	}
	else
		throw logic_error("Not yet implemented.");
}

bool PolylineSetRepresentation::areAllPolylinesClosedOfAllPatches() const
{
	_resqml2__PolylineSetRepresentation* rep = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1);
	for (unsigned int patchIndex = 0; patchIndex < rep->LinePatch.size(); patchIndex++)
	{
		if (areAllPolylinesClosedOfPatch(patchIndex) == false)
			return false;
	}

	return true;
}

bool isNotZero(const long & i)
{
	return i != 0;
}

bool PolylineSetRepresentation::areAllPolylinesNonClosedOfPatch(const unsigned int & patchIndex) const
{
	resqml2__PolylineSetPatch* patch = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanConstantArray)
	{
		return static_cast<resqml2__BooleanConstantArray*>(patch->ClosedPolylines)->Value == false;
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array)
	{
		unsigned int polylineCount = getPolylineCountOfPatch(patchIndex);
		hid_t datatype = hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile);

		bool result = true;
		if (H5Tequal(datatype, H5T_NATIVE_CHAR) > 0)
		{
			char* tmp = new char[polylineCount];
			hdfProxy->readArrayNdOfCharValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
#if (defined(_WIN32) && _MSC_VER >= 1600) || (__GNUC__ > 4 && __GNUC_MINOR__ > 4)
			if (find_if(tmp, tmp + polylineCount, [](char i){return i != 0;}) != tmp + polylineCount)
				result = false;
#else
			if (find_if(tmp, tmp + polylineCount, isNotZero) != tmp + polylineCount)
				result = false;
#endif
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_UCHAR) > 0)
		{
			unsigned char* tmp = new unsigned char[polylineCount];
			hdfProxy->readArrayNdOfUCharValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
#if (defined(_WIN32) && _MSC_VER >= 1600) || (__GNUC__ > 4 && __GNUC_MINOR__ > 4)
			if (find_if(tmp, tmp + polylineCount, [](unsigned char i){return i != 0;}) != tmp + polylineCount)
				result = false;
#else
			if (find_if(tmp, tmp + polylineCount, isNotZero) != tmp + polylineCount)
				result = false;
#endif
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_SHORT) > 0)
		{
			short* tmp = new short[polylineCount];
			hdfProxy->readArrayNdOfShortValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
#if (defined(_WIN32) && _MSC_VER >= 1600) || (__GNUC__ > 4 && __GNUC_MINOR__ > 4)
			if (find_if(tmp, tmp + polylineCount, [](short i){return i != 0;}) != tmp + polylineCount)
				result = false;
#else
			if (find_if(tmp, tmp + polylineCount, isNotZero) != tmp + polylineCount)
				result = false;
#endif
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_USHORT) > 0)
		{
			unsigned short* tmp = new unsigned short[polylineCount];
			hdfProxy->readArrayNdOfUShortValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
#if (defined(_WIN32) && _MSC_VER >= 1600) || (__GNUC__ > 4 && __GNUC_MINOR__ > 4)
			if (find_if(tmp, tmp + polylineCount, [](unsigned short i){return i != 0;}) != tmp + polylineCount)
				result = false;
#else
			if (find_if(tmp, tmp + polylineCount, isNotZero) != tmp + polylineCount)
				result = false;
#endif
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_INT) > 0)
		{
			int* tmp = new int[polylineCount];
			hdfProxy->readArrayNdOfIntValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
#if (defined(_WIN32) && _MSC_VER >= 1600) || (__GNUC__ > 4 && __GNUC_MINOR__ > 4)
			if (find_if(tmp, tmp + polylineCount, [](int i){return i != 0;}) != tmp + polylineCount)
				result = false;
#else
			if (find_if(tmp, tmp + polylineCount, isNotZero) != tmp + polylineCount)
				result = false;
#endif
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_UINT) > 0)
		{
			unsigned int* tmp = new unsigned int[polylineCount];
			hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
#if (defined(_WIN32) && _MSC_VER >= 1600) || (__GNUC__ > 4 && __GNUC_MINOR__ > 4)
			if (find_if(tmp, tmp + polylineCount, [](unsigned int i){return i != 0;}) != tmp + polylineCount)
				result = false;
#else
			if (find_if(tmp, tmp + polylineCount, isNotZero) != tmp + polylineCount)
				result = false;
#endif
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_LONG) > 0)
		{
			long* tmp = new long[polylineCount];
			hdfProxy->readArrayNdOfLongValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
#if (defined(_WIN32) && _MSC_VER >= 1600) || (__GNUC__ > 4 && __GNUC_MINOR__ > 4)
			if (find_if(tmp, tmp + polylineCount, [](long i){return i != 0;}) != tmp + polylineCount)
				result = false;
#else
			if (find_if(tmp, tmp + polylineCount, isNotZero) != tmp + polylineCount)
				result = false;
#endif
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_ULONG) > 0)
		{
			unsigned long* tmp = new unsigned long[polylineCount];
			hdfProxy->readArrayNdOfULongValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
#if (defined(_WIN32) && _MSC_VER >= 1600) || (__GNUC__ > 4 && __GNUC_MINOR__ > 4)
			if (find_if(tmp, tmp + polylineCount, [](unsigned long i){return i != 0;}) != tmp + polylineCount)
				result = false;
#else
			if (find_if(tmp, tmp + polylineCount, isNotZero) != tmp + polylineCount)
				result = false;
#endif
			delete [] tmp;
		}
		else
			throw logic_error("Not yet implemented.");

		return result;
	}
	else
		throw logic_error("Not yet implemented.");
}

bool PolylineSetRepresentation::areAllPolylinesNonClosedOfAllPatches() const
{
	_resqml2__PolylineSetRepresentation* rep = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1);
	for (size_t patchIndex = 0; patchIndex < rep->LinePatch.size(); patchIndex++)
	{
		if (areAllPolylinesNonClosedOfPatch(patchIndex) == false)
			return false;
	}

	return true;
}
		
void PolylineSetRepresentation::getClosedFlagPerPolylineOfPatch(const unsigned int & patchIndex, bool * closedFlagPerPolyline) const
{
	unsigned int polylineCount = getPolylineCountOfPatch(patchIndex);
	resqml2__PolylineSetPatch* patch = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanConstantArray)
	{
		fill(closedFlagPerPolyline, closedFlagPerPolyline + polylineCount, static_cast<resqml2__BooleanConstantArray*>(patch->ClosedPolylines)->Value);
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array)
	{
		hid_t datatype = hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile);

		if (H5Tequal(datatype, H5T_NATIVE_CHAR) > 0)
		{
			char* tmp = new char[polylineCount];
			hdfProxy->readArrayNdOfCharValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			for (unsigned int i = 0; i < polylineCount; ++i)
				closedFlagPerPolyline[i] = tmp[i];
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_UCHAR) > 0)
		{
			unsigned char* tmp = new unsigned char[polylineCount];
			hdfProxy->readArrayNdOfUCharValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			for (unsigned int i = 0; i < polylineCount; ++i)
				closedFlagPerPolyline[i] = tmp[i];
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_SHORT) > 0)
		{
			short* tmp = new short[polylineCount];
			hdfProxy->readArrayNdOfShortValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			for (unsigned int i = 0; i < polylineCount; ++i)
				closedFlagPerPolyline[i] = tmp[i];
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_USHORT) > 0)
		{
			unsigned short* tmp = new unsigned short[polylineCount];
			hdfProxy->readArrayNdOfUShortValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			for (unsigned int i = 0; i < polylineCount; ++i)
				closedFlagPerPolyline[i] = tmp[i];
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_INT) > 0)
		{
			int* tmp = new int[polylineCount];
			hdfProxy->readArrayNdOfIntValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			for (unsigned int i = 0; i < polylineCount; ++i)
				closedFlagPerPolyline[i] = tmp[i];
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_UINT) > 0)
		{
			unsigned int* tmp = new unsigned int[polylineCount];
			hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			for (unsigned int i = 0; i < polylineCount; ++i)
				closedFlagPerPolyline[i] = tmp[i];
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_LONG) > 0)
		{
			long* tmp = new long[polylineCount];
			hdfProxy->readArrayNdOfLongValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			for (unsigned int i = 0; i < polylineCount; ++i)
				closedFlagPerPolyline[i] = tmp[i];
			delete [] tmp;
		}
		else if (H5Tequal(datatype, H5T_NATIVE_ULONG) > 0)
		{
			unsigned long* tmp = new unsigned long[polylineCount];
			hdfProxy->readArrayNdOfULongValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			for (unsigned int i = 0; i < polylineCount; ++i)
				closedFlagPerPolyline[i] = tmp[i];
			delete [] tmp;
		}
		else
			throw logic_error("Not yet implemented.");
	}
	else
		throw logic_error("Not yet implemented.");
}

void PolylineSetRepresentation::getClosedFlagPerPolylineOfAllPatches(bool * closedFlagPerPolyline) const
{
	_resqml2__PolylineSetRepresentation* rep = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1);
	for (size_t i = 0; i < rep->LinePatch.size(); i++)
	{
		getClosedFlagPerPolylineOfPatch(i, closedFlagPerPolyline);
		closedFlagPerPolyline += getPolylineCountOfPatch(i);
	}
}

bool PolylineSetRepresentation::hasALineRole() const
{
	return static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LineRole;
}

gsoap_resqml2_0_1::resqml2__LineRole PolylineSetRepresentation::getLineRole() const
{
	if (!hasALineRole())
		throw invalid_argument("The polylineSet doesn't have any role");

	return *(static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LineRole);
}

void PolylineSetRepresentation::setLineRole(const gsoap_resqml2_0_1::resqml2__LineRole & lineRole)
{
	if (!hasALineRole())
		static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LineRole = (resqml2__LineRole*)soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml2__LineRole));

	(*static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy2_0_1)->LineRole) = lineRole;
}

