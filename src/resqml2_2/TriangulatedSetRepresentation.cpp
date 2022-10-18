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
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* TriangulatedSetRepresentation::XML_NS = "resqml22";

TriangulatedSetRepresentation::TriangulatedSetRepresentation(COMMON_NS::DataObjectRepository* repo,
	const std::string & guid, const std::string & title)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__TriangulatedSetRepresentation(repo->getGsoapContext());

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

	gsoapProxy2_3 = soap_new_resqml22__TriangulatedSetRepresentation(interp->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	interp->getRepository()->addDataObject(this);
	// relationhsips
	setInterpretation(interp);
}

COMMON_NS::DataObjectReference TriangulatedSetRepresentation::getHdfProxyDor() const
{
	resqml22__TrianglePatch* patch = static_cast<_resqml22__TriangulatedSetRepresentation*>(gsoapProxy2_3)->TrianglePatch[0];
	if (patch->Triangles->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray)
	{
		return COMMON_NS::DataObjectReference(static_cast<eml23__IntegerExternalArray*>(patch->Triangles)->Values->ExternalFileProxy[0]->EpcExternalPartReference);
	}

	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_2(0));
}

resqml22__PointGeometry* TriangulatedSetRepresentation::getPointGeometry2_2(uint64_t patchIndex) const
{
	_resqml22__TriangulatedSetRepresentation* triRep = static_cast<_resqml22__TriangulatedSetRepresentation*>(gsoapProxy2_3);
	
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

	_resqml22__TriangulatedSetRepresentation* triRep = static_cast<_resqml22__TriangulatedSetRepresentation*>(gsoapProxy2_3);

	resqml22__TrianglePatch* patch = soap_new_resqml22__TrianglePatch(gsoapProxy2_3->soap);

	uint64_t pointCountDims = nodeCount;
	patch->NodeCount = nodeCount;
	patch->Geometry = createPointGeometryPatch2_2(triRep->TrianglePatch.size(), nodes, localCrs, &pointCountDims, 1, proxy);
	getRepository()->addRelationship(this, localCrs);

	getRepository()->addRelationship(this, proxy);

	patch->Count = triangleCount;
	eml23__IntegerExternalArray* hdfTriangles = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	patch->Triangles = hdfTriangles;
	hdfTriangles->NullValue = -1; // Arbitrarily decided to something almost impossible since it has no interest to write triangle node index null value in this method
	hdfTriangles->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	auto dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	ostringstream ossForHdf;
	ossForHdf << "triangles_patch" << triRep->TrianglePatch.size();
	dsPart->PathInExternalFile = getHdfGroup() + "/" + ossForHdf.str();
	hdfTriangles->Values->ExternalFileProxy.push_back(dsPart);
	// ************ HDF *************
	hsize_t dim[2] = {triangleCount, 3};
	proxy->writeArrayNd(getHdfGroup(),
		ossForHdf.str(), COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT32,
		triangleNodeIndices,
		dim, 2);

	triRep->TrianglePatch.push_back(patch);
}

uint64_t TriangulatedSetRepresentation::getXyzPointCountOfPatch(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index of the patch is not in the allowed range of patch.");

	_resqml22__TriangulatedSetRepresentation* triRep = static_cast<_resqml22__TriangulatedSetRepresentation*>(gsoapProxy2_3);
	return triRep->TrianglePatch[patchIndex]->NodeCount;
}

void TriangulatedSetRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index of the patch is not in the allowed range of patch.");

	resqml22__PointGeometry* pointGeom = getPointGeometry2_2(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray)
	{
		eml23__ExternalDatasetPart const * dsPart = static_cast<resqml22__Point3dExternalArray*>(pointGeom->Points)->Coordinates->ExternalFileProxy[0];
		getHdfProxyFromDataset(dsPart)->readArrayNdOfDoubleValues(dsPart->PathInExternalFile, xyzPoints);
	}
	else
		throw invalid_argument("The geometry of the representation either does not exist or it is not an explicit one.");
}

uint64_t TriangulatedSetRepresentation::getTriangleCountOfPatch(unsigned int patchIndex) const
{
	_resqml22__TriangulatedSetRepresentation* triRep = static_cast<_resqml22__TriangulatedSetRepresentation*>(gsoapProxy2_3);
	
	if (triRep->TrianglePatch.size() > patchIndex)
		return triRep->TrianglePatch[patchIndex]->Count;
	else
		throw out_of_range("The patchIndex is out of range");
}

uint64_t TriangulatedSetRepresentation::getTriangleCountOfAllPatches() const
{
	uint64_t result = 0;

	std::vector<resqml22__TrianglePatch * > patches = static_cast<_resqml22__TriangulatedSetRepresentation*>(gsoapProxy2_3)->TrianglePatch;
	for (size_t i = 0; i < patches.size(); ++i)
		result += patches[i]->Count;

	return result;
}

void TriangulatedSetRepresentation::getTriangleNodeIndicesOfPatch(unsigned int patchIndex, unsigned int * triangleNodeIndices) const
{
	_resqml22__TriangulatedSetRepresentation* triRep = static_cast<_resqml22__TriangulatedSetRepresentation*>(gsoapProxy2_3);

	if (patchIndex >= triRep->TrianglePatch.size()) {
		throw out_of_range("The patchIndex is out of range");
	}

	readArrayNdOfUInt32Values(triRep->TrianglePatch[patchIndex]->Triangles, triangleNodeIndices);
}

void TriangulatedSetRepresentation::getTriangleNodeIndicesOfAllPatches(unsigned int * triangleNodeIndices) const
{
	_resqml22__TriangulatedSetRepresentation* triRep = static_cast<_resqml22__TriangulatedSetRepresentation*>(gsoapProxy2_3);
	size_t patchCount = triRep->TrianglePatch.size();
	for (size_t patchIndex = 0; patchIndex < patchCount; patchIndex++)
	{
		getTriangleNodeIndicesOfPatch(patchIndex, triangleNodeIndices);
		triangleNodeIndices += getTriangleCountOfPatch(patchIndex) * 3;
	}
}

uint64_t TriangulatedSetRepresentation::getPatchCount() const
{
	return static_cast<_resqml22__TriangulatedSetRepresentation*>(gsoapProxy2_3)->TrianglePatch.size();
}
