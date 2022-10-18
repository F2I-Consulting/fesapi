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
#include "TriangulatedSetRepresentation.h"

#include <limits>
#include <sstream>
#include <stdexcept>

#include <hdf5.h>

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../resqml2/AbstractLocal3dCrs.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* TriangulatedSetRepresentation::XML_NS = "resqml20";

TriangulatedSetRepresentation::TriangulatedSetRepresentation(COMMON_NS::DataObjectRepository* repo,
	const std::string & guid, const std::string & title)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORETriangulatedSetRepresentation(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(this);
}

TriangulatedSetRepresentation::TriangulatedSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
		const std::string & guid, const std::string & title)
{
	if (interp == nullptr) {
		throw invalid_argument("The interpretation of the subrepresentation cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORETriangulatedSetRepresentation(interp->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	interp->getRepository()->addDataObject(this);
	// relationhsips
	setInterpretation(interp);
}

COMMON_NS::DataObjectReference TriangulatedSetRepresentation::getHdfProxyDor() const
{
	resqml20__TrianglePatch* patch = static_cast<_resqml20__TriangulatedSetRepresentation*>(gsoapProxy2_0_1)->TrianglePatch[0];
	if (patch->Triangles->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
	{
		return COMMON_NS::DataObjectReference(static_cast<resqml20__IntegerHdf5Array*>(patch->Triangles)->Values->HdfProxy);
	}

	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

resqml20__PointGeometry* TriangulatedSetRepresentation::getPointGeometry2_0_1(uint64_t patchIndex) const
{
	_resqml20__TriangulatedSetRepresentation* triRep = static_cast<_resqml20__TriangulatedSetRepresentation*>(gsoapProxy2_0_1);
	
	if (triRep->TrianglePatch.size() > patchIndex)
		return triRep->TrianglePatch[patchIndex]->Geometry;
	else
		throw out_of_range("The patchIndex is out of range");
}

void TriangulatedSetRepresentation::pushBackTrianglePatch(
	unsigned int nodeCount, double const * nodes,
	unsigned int triangleCount, unsigned int const * triangleNodeIndices,
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

	_resqml20__TriangulatedSetRepresentation* triRep = static_cast<_resqml20__TriangulatedSetRepresentation*>(gsoapProxy2_0_1);

	resqml20__TrianglePatch* patch = soap_new_resqml20__TrianglePatch(gsoapProxy2_0_1->soap);
	patch->PatchIndex = triRep->TrianglePatch.size();
	triRep->TrianglePatch.push_back(patch);

	uint64_t pointCountDims = nodeCount;
	patch->NodeCount = nodeCount;
	patch->Geometry = createPointGeometryPatch2_0_1(patch->PatchIndex, nodes, localCrs, &pointCountDims, 1, proxy);
	getRepository()->addRelationship(this, localCrs);

	getRepository()->addRelationship(this, proxy);

	patch->Count = triangleCount;
	resqml20__IntegerHdf5Array* hdfTriangles = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	patch->Triangles = hdfTriangles;
	hdfTriangles->NullValue = -1; // Arbitrarily decided to something almost impossible since it has no interest to write triangle node index null value in this method
	hdfTriangles->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	hdfTriangles->Values->HdfProxy = proxy->newResqmlReference();
	ostringstream ossForHdf;
	ossForHdf << "triangles_patch" << patch->PatchIndex;
	hdfTriangles->Values->PathInHdfFile = getHdfGroup() + "/" + ossForHdf.str();
	// ************ HDF *************
	hsize_t dim[2] = {triangleCount, 3};
	proxy->writeArrayNd(getHdfGroup(),
		ossForHdf.str(), COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT32,
		triangleNodeIndices,
		dim, 2);
}

uint64_t TriangulatedSetRepresentation::getXyzPointCountOfPatch(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index of the patch is not in the allowed range of patch.");

	_resqml20__TriangulatedSetRepresentation* triRep = static_cast<_resqml20__TriangulatedSetRepresentation*>(gsoapProxy2_0_1);
	return triRep->TrianglePatch[patchIndex]->NodeCount;
}

void TriangulatedSetRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index of the patch is not in the allowed range of patch.");

	resqml20__PointGeometry* pointGeom = getPointGeometry2_0_1(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array)
	{
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__Point3dHdf5Array*>(pointGeom->Points)->Coordinates;
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, xyzPoints);
	}
	else
		throw invalid_argument("The geometry of the representation either does not exist or it is not an explicit one.");
}

uint64_t TriangulatedSetRepresentation::getTriangleCountOfPatch(unsigned int patchIndex) const
{
	_resqml20__TriangulatedSetRepresentation* triRep = static_cast<_resqml20__TriangulatedSetRepresentation*>(gsoapProxy2_0_1);
	
	if (triRep->TrianglePatch.size() > patchIndex)
		return triRep->TrianglePatch[patchIndex]->Count;
	else
		throw out_of_range("The patchIndex is out of range");
}

uint64_t TriangulatedSetRepresentation::getTriangleCountOfAllPatches() const
{
	uint64_t result = 0;

	std::vector<resqml20__TrianglePatch * > patches = static_cast<_resqml20__TriangulatedSetRepresentation*>(gsoapProxy2_0_1)->TrianglePatch;
	for (uint64_t i = 0; i < patches.size(); ++i)
		result += patches[i]->Count;

	return result;
}

void TriangulatedSetRepresentation::getTriangleNodeIndicesOfPatch(unsigned int patchIndex, unsigned int * triangleNodeIndices) const
{
	_resqml20__TriangulatedSetRepresentation* triRep = static_cast<_resqml20__TriangulatedSetRepresentation*>(gsoapProxy2_0_1);

	if (patchIndex >= triRep->TrianglePatch.size()) {
		throw out_of_range("The patchIndex is out of range");
	}

	readArrayNdOfUInt32Values(triRep->TrianglePatch[patchIndex]->Triangles, triangleNodeIndices);
}

void TriangulatedSetRepresentation::getTriangleNodeIndicesOfAllPatches(unsigned int * triangleNodeIndices) const
{
	_resqml20__TriangulatedSetRepresentation* triRep = static_cast<_resqml20__TriangulatedSetRepresentation*>(gsoapProxy2_0_1);
	size_t patchCount = triRep->TrianglePatch.size();
	for (size_t patchIndex = 0; patchIndex < patchCount; patchIndex++)
	{
		getTriangleNodeIndicesOfPatch(patchIndex, triangleNodeIndices);
		triangleNodeIndices += getTriangleCountOfPatch(patchIndex) * 3;
	}
}

uint64_t TriangulatedSetRepresentation::getPatchCount() const
{
	return static_cast<_resqml20__TriangulatedSetRepresentation*>(gsoapProxy2_0_1)->TrianglePatch.size();
}
