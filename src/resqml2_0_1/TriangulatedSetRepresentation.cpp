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
#include "resqml2_0_1/TriangulatedSetRepresentation.h"

#include <sstream>
#include <stdexcept>

#include "hdf5.h"

#include "resqml2/AbstractFeatureInterpretation.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* TriangulatedSetRepresentation::XML_TAG = "TriangulatedSetRepresentation";

TriangulatedSetRepresentation::TriangulatedSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title):
	AbstractSurfaceRepresentation(interp, crs)
{
	if (crs == nullptr) {
		throw invalid_argument("The local CRS of the TriangulatedSetRepresentation cannot be null.");
	}
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORETriangulatedSetRepresentation(crs->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	localCrs = crs;
	localCrs->addRepresentation(this);

	// relationhsips
	if (interp != nullptr) {
		setInterpretation(interp);
	}
}

string TriangulatedSetRepresentation::getHdfProxyUuid() const
{
	resqml2__TrianglePatch* patch = static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy2_0_1)->TrianglePatch[0];
	if (patch->Triangles->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
	{
		return static_cast<resqml2__IntegerHdf5Array*>(patch->Triangles)->Values->HdfProxy->UUID;
	}

	return getHdfProxyUuidFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

resqml2__PointGeometry* TriangulatedSetRepresentation::getPointGeometry2_0_1(const unsigned int & patchIndex) const
{
	_resqml2__TriangulatedSetRepresentation* triRep = static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy2_0_1);
	
	if (triRep->TrianglePatch.size() > patchIndex)
		return triRep->TrianglePatch[patchIndex]->Geometry;
	else
		throw out_of_range("The patchIndex is out of range");
}

void TriangulatedSetRepresentation::pushBackTrianglePatch(
	const unsigned int & nodeCount, double * nodes,
	const unsigned int & triangleCount, unsigned int * triangleNodeIndices,
	COMMON_NS::AbstractHdfProxy * proxy)
{
	_resqml2__TriangulatedSetRepresentation* triRep = static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy2_0_1);

	resqml2__TrianglePatch* patch = soap_new_resqml2__TrianglePatch(gsoapProxy2_0_1->soap, 1);
	patch->PatchIndex = triRep->TrianglePatch.size();
	triRep->TrianglePatch.push_back(patch);

	hsize_t pointCountDims[] = {nodeCount};
	patch->NodeCount = nodeCount;
	patch->Geometry = createPointGeometryPatch2_0_1(patch->PatchIndex, nodes, pointCountDims, 1, proxy);
	patch->Geometry->LocalCrs = localCrs->newResqmlReference();

	patch->Count = triangleCount;
	resqml2__IntegerHdf5Array* hdfTriangles = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	patch->Triangles = hdfTriangles;
	hdfTriangles->NullValue = (std::numeric_limits<int>::max)();
	hdfTriangles->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	hdfTriangles->Values->HdfProxy = proxy->newResqmlReference();
	ostringstream ossForHdf;
	ossForHdf << "triangles_patch" << patch->PatchIndex;
	hdfTriangles->Values->PathInHdfFile = "/RESQML/" + triRep->uuid + "/" + ossForHdf.str();
	// ************ HDF *************
	hsize_t dim[2] = {triangleCount, 3};
	proxy->writeArrayNd(triRep->uuid,
		ossForHdf.str(), H5T_NATIVE_UINT,
		triangleNodeIndices,
		dim, 2);
}

ULONG64 TriangulatedSetRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index of the patch is not in the allowed range of patch.");

	_resqml2__TriangulatedSetRepresentation* triRep = static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy2_0_1);
	return triRep->TrianglePatch[patchIndex]->NodeCount;
}

void TriangulatedSetRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
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

unsigned int TriangulatedSetRepresentation::getTriangleCountOfPatch(const unsigned int & patchIndex) const
{
	_resqml2__TriangulatedSetRepresentation* triRep = static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy2_0_1);
	
	if (triRep->TrianglePatch.size() > patchIndex)
		return triRep->TrianglePatch[patchIndex]->Count;
	else
		throw out_of_range("The patchIndex is out of range");
}

unsigned int TriangulatedSetRepresentation::getTriangleCountOfAllPatches() const
{
	unsigned int result = 0;

	std::vector<resqml2__TrianglePatch * > patches = static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy2_0_1)->TrianglePatch;
	for (unsigned int i = 0; i < patches.size(); ++i)
		result += patches[i]->Count;

	return result;
}

void TriangulatedSetRepresentation::getTriangleNodeIndicesOfPatch(const unsigned int & patchIndex, unsigned int * triangleNodeIndices) const
{
	_resqml2__TriangulatedSetRepresentation* triRep = static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy2_0_1);
	if (triRep->TrianglePatch[patchIndex]->Triangles->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(triRep->TrianglePatch[patchIndex]->Triangles)->Values->PathInHdfFile, triangleNodeIndices);
	}
}

void TriangulatedSetRepresentation::getTriangleNodeIndicesOfAllPatches(unsigned int * triangleNodeIndices) const
{
	_resqml2__TriangulatedSetRepresentation* triRep = static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy2_0_1);
	unsigned int patchCount = triRep->TrianglePatch.size();
	for (unsigned int patchIndex = 0; patchIndex < patchCount; patchIndex++)
	{
		getTriangleNodeIndicesOfPatch(patchIndex, triangleNodeIndices);
		triangleNodeIndices += getTriangleCountOfPatch(patchIndex) * 3;
	}
}

unsigned int TriangulatedSetRepresentation::getPatchCount() const
{
	return static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy2_0_1)->TrianglePatch.size();
}

