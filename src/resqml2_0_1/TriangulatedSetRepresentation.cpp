/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#include "resqml2_0_1/TriangulatedSetRepresentation.h"

#include <sstream>
#include <stdexcept>

#include "hdf5.h"

#include "resqml2/AbstractFeatureInterpretation.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* TriangulatedSetRepresentation::XML_TAG = "TriangulatedSetRepresentation";

TriangulatedSetRepresentation::TriangulatedSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title):
	AbstractSurfaceRepresentation(interp, crs)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORETriangulatedSetRepresentation(interp->getGsoapContext(), 1);
	_resqml2__TriangulatedSetRepresentation* triRep = static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy2_0_1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	localCrs = crs;
	localCrs->addRepresentation(this);

	// relationhsips
	setInterpretation(interp);
}

string TriangulatedSetRepresentation::getHdfProxyUuid() const
{
	string result = "";

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
	common::AbstractHdfProxy * proxy)
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
