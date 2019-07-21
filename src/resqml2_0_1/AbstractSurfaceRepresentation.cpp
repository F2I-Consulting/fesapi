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
#include "resqml2_0_1/AbstractSurfaceRepresentation.h"

#include <algorithm>
#include <sstream>

#include "H5public.h"

#include "resqml2_0_1/Grid2dRepresentation.h"
#include "resqml2_0_1/PolylineRepresentation.h"
#include "common/AbstractHdfProxy.h"
#include "resqml2/AbstractLocal3dCrs.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

void AbstractSurfaceRepresentation::setSurfaceRole(const resqml2__SurfaceRole & surfaceRole)
{
	static_cast<resqml2__AbstractSurfaceRepresentation*>(gsoapProxy2_0_1)->SurfaceRole = surfaceRole;
}

const gsoap_resqml2_0_1::resqml2__SurfaceRole & AbstractSurfaceRepresentation::getSurfaceRole() const
{
	return static_cast<resqml2__AbstractSurfaceRepresentation*>(gsoapProxy2_0_1)->SurfaceRole;
}

resqml2__Point3dFromRepresentationLatticeArray* AbstractSurfaceRepresentation::getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(resqml2__PointGeometry* patch) const
{
	if (patch != nullptr) {
		resqml2__Point3dFromRepresentationLatticeArray* patchOfSupportingRep = nullptr;

		if (patch->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dZValueArray) {
			resqml2__Point3dZValueArray* zValuesPatch = static_cast<resqml2__Point3dZValueArray*>(patch->Points);
			if (zValuesPatch->SupportingGeometry->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dFromRepresentationLatticeArray) {
				patchOfSupportingRep = static_cast<resqml2__Point3dFromRepresentationLatticeArray*>(zValuesPatch->SupportingGeometry);
			}
		}
		else if (patch->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dFromRepresentationLatticeArray) {
			patchOfSupportingRep = static_cast<resqml2__Point3dFromRepresentationLatticeArray*>(patch->Points);
		}

		return patchOfSupportingRep;
	}
	
	return nullptr;
}

resqml2__PointGeometry* AbstractSurfaceRepresentation::createArray2dOfLatticePoints3d(
			unsigned int numPointsInFastestDirection, unsigned int numPointsInSlowestDirection,
			double xOrigin, double yOrigin, double zOrigin,
			double xOffsetInFastestDirection, double yOffsetInFastestDirection, double zOffsetInFastestDirection,
			double xOffsetInSlowestDirection, double yOffsetInSlowestDirection, double zOffsetInSlowestDirection,
			double spacingInFastestDirection, double spacingInSlowestDirection, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (localCrs == nullptr) {
		throw invalid_argument("The CRS cannot be the null pointer");
	}

	resqml2__PointGeometry* geom = soap_new_resqml2__PointGeometry(gsoapProxy2_0_1->soap, 1);
	geom->LocalCrs = localCrs->newResqmlReference();

	// XML
	resqml2__Point3dLatticeArray* xmlPoints = soap_new_resqml2__Point3dLatticeArray(gsoapProxy2_0_1->soap, 1);
	xmlPoints->Origin = soap_new_resqml2__Point3d(gsoapProxy2_0_1->soap, 1);
	xmlPoints->Origin->Coordinate1 = xOrigin;
	xmlPoints->Origin->Coordinate2 = yOrigin;
	xmlPoints->Origin->Coordinate3 = zOrigin;

	// first (slowest) dim : fastest is I (or inline), slowest is J (or crossline)
	resqml2__Point3dOffset* latticeDim = soap_new_resqml2__Point3dOffset(gsoapProxy2_0_1->soap, 1);
	latticeDim->Offset = soap_new_resqml2__Point3d(gsoapProxy2_0_1->soap, 1);
	latticeDim->Offset->Coordinate1 = xOffsetInSlowestDirection;
	latticeDim->Offset->Coordinate2 = yOffsetInSlowestDirection;
	latticeDim->Offset->Coordinate3 = zOffsetInSlowestDirection;
	resqml2__DoubleConstantArray* spacingInfo = soap_new_resqml2__DoubleConstantArray(gsoapProxy2_0_1->soap, 1);
	spacingInfo->Count = numPointsInSlowestDirection-1;
	spacingInfo->Value = spacingInSlowestDirection;
	latticeDim->Spacing = spacingInfo;
	xmlPoints->Offset.push_back(latticeDim);

	// Second (fastest) dimension :fastest is I (or inline), slowest is J (or crossline)
	latticeDim = soap_new_resqml2__Point3dOffset(gsoapProxy2_0_1->soap, 1);
	latticeDim->Offset = soap_new_resqml2__Point3d(gsoapProxy2_0_1->soap, 1);
	latticeDim->Offset->Coordinate1 = xOffsetInFastestDirection;
	latticeDim->Offset->Coordinate2 = yOffsetInFastestDirection;
	latticeDim->Offset->Coordinate3 = zOffsetInFastestDirection;
	spacingInfo = soap_new_resqml2__DoubleConstantArray(gsoapProxy2_0_1->soap, 1);
	spacingInfo->Count = numPointsInFastestDirection-1;
	spacingInfo->Value = spacingInFastestDirection;
	latticeDim->Spacing = spacingInfo;
	xmlPoints->Offset.push_back(latticeDim);

	geom->Points = xmlPoints;

	return geom;
}

resqml2__PointGeometry* AbstractSurfaceRepresentation::createArray2dOfExplicitZ(
		unsigned int patchIndex, double * zValues, RESQML2_NS::AbstractLocal3dCrs * localCrs,
		unsigned int numI, unsigned int numJ, COMMON_NS::AbstractHdfProxy * proxy,
		Grid2dRepresentation * supportingRepresentation,
		unsigned int startGlobalIndex,
		int indexIncrementI, int indexIncrementJ)
{
	if (localCrs == nullptr) {
		throw invalid_argument("The CRS cannot be the null pointer");
	}

	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
	}
	getRepository()->addRelationship(this, proxy);

	getRepository()->addRelationship(this, supportingRepresentation);

	resqml2__PointGeometry* geom = soap_new_resqml2__PointGeometry(gsoapProxy2_0_1->soap, 1);
	geom->LocalCrs = localCrs->newResqmlReference();

	// XML
	resqml2__Point3dZValueArray* xmlPoints = soap_new_resqml2__Point3dZValueArray(gsoapProxy2_0_1->soap, 1);
	resqml2__Point3dFromRepresentationLatticeArray* patchPoints = soap_new_resqml2__Point3dFromRepresentationLatticeArray(gsoapProxy2_0_1->soap, 1);
	patchPoints->SupportingRepresentation = supportingRepresentation->newResqmlReference();
	patchPoints->NodeIndicesOnSupportingRepresentation = soap_new_resqml2__IntegerLatticeArray(gsoapProxy2_0_1->soap, 1);
	patchPoints->NodeIndicesOnSupportingRepresentation->StartValue = startGlobalIndex;
	xmlPoints->SupportingGeometry = patchPoints;

	// first (slowest) dim :fastest is I (or inline), slowest is J (or crossline)
	resqml2__IntegerConstantArray* offset = soap_new_resqml2__IntegerConstantArray(gsoapProxy2_0_1->soap, 1);
	offset->Count = numJ-1;
	offset->Value = indexIncrementJ;
	patchPoints->NodeIndicesOnSupportingRepresentation->Offset.push_back(offset);

	//second (fastest) dim :fastest is I (or inline), slowest is J (or crossline)
	offset = soap_new_resqml2__IntegerConstantArray(gsoapProxy2_0_1->soap, 1);
	offset->Count = numI-1;
	offset->Value = indexIncrementI;
	patchPoints->NodeIndicesOnSupportingRepresentation->Offset.push_back(offset);

	// Z Values
	resqml2__DoubleHdf5Array* xmlZValues = soap_new_resqml2__DoubleHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlZValues->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlZValues->Values->HdfProxy = proxy->newResqmlReference();
	ostringstream oss3;
	oss3 << "points_patch" << patchIndex;
	xmlZValues->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/" + oss3.str();
	xmlPoints->ZValues = xmlZValues;

	// HDF
	hsize_t dim[] = {numJ, numI};
	proxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid,
			oss3.str(),
			zValues,
			dim, 2);

	geom->Points = xmlPoints;

	return geom;
}

resqml2__PointGeometry* AbstractSurfaceRepresentation::createArray2dOfExplicitZ(
		unsigned int patchIndex, double * zValues, RESQML2_NS::AbstractLocal3dCrs * localCrs,
		unsigned int numI, unsigned int numJ, COMMON_NS::AbstractHdfProxy * proxy,
		double originX, double originY, double originZ,
		double offsetIX, double offsetIY, double offsetIZ, double spacingI,
		double offsetJX, double offsetJY, double offsetJZ, double spacingJ)
{
	if (localCrs == nullptr) {
		throw invalid_argument("The CRS cannot be the null pointer");
	}

	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
	}
	getRepository()->addRelationship(this, proxy);

	resqml2__PointGeometry* geom = soap_new_resqml2__PointGeometry(gsoapProxy2_0_1->soap, 1);
	geom->LocalCrs = localCrs->newResqmlReference();

	// XML
	resqml2__Point3dZValueArray* xmlPoints = soap_new_resqml2__Point3dZValueArray(gsoapProxy2_0_1->soap, 1);
	resqml2__Point3dLatticeArray* latticePoints = soap_new_resqml2__Point3dLatticeArray(gsoapProxy2_0_1->soap, 1);
	latticePoints->Origin = soap_new_resqml2__Point3d(gsoapProxy2_0_1->soap, 1);
	latticePoints->Origin->Coordinate1 = originX;
	latticePoints->Origin->Coordinate2 = originY;
	latticePoints->Origin->Coordinate3 = originZ;

	// first (slowest) dim :fastest is I (or inline), slowest is J (or crossline)
	resqml2__Point3dOffset* latticeDimForJ = soap_new_resqml2__Point3dOffset(gsoapProxy2_0_1->soap, 1);
	latticeDimForJ->Offset = soap_new_resqml2__Point3d(gsoapProxy2_0_1->soap, 1);
	latticeDimForJ->Offset->Coordinate1 = offsetJX;
	latticeDimForJ->Offset->Coordinate2 = offsetJY;
	latticeDimForJ->Offset->Coordinate3 = offsetJZ;
	resqml2__DoubleConstantArray* spacingForJ = soap_new_resqml2__DoubleConstantArray(gsoapProxy2_0_1->soap, 1);
	spacingForJ->Value = spacingJ;
	spacingForJ->Count = numJ - 1;
	latticeDimForJ->Spacing = spacingForJ;
	latticePoints->Offset.push_back(latticeDimForJ);

	//second (fastest) dim :fastest is I (or inline), slowest is J (or crossline)
	resqml2__Point3dOffset* latticeDimForI = soap_new_resqml2__Point3dOffset(gsoapProxy2_0_1->soap, 1);
	latticeDimForI->Offset = soap_new_resqml2__Point3d(gsoapProxy2_0_1->soap, 1);
	latticeDimForI->Offset->Coordinate1 = offsetIX;
	latticeDimForI->Offset->Coordinate2 = offsetIY;
	latticeDimForI->Offset->Coordinate3 = offsetIZ;
	resqml2__DoubleConstantArray* spacingForI = soap_new_resqml2__DoubleConstantArray(gsoapProxy2_0_1->soap, 1);
	spacingForI->Value = spacingI;
	spacingForI->Count = numI - 1;
	latticeDimForI->Spacing = spacingForI;
	latticePoints->Offset.push_back(latticeDimForI);
	
	xmlPoints->SupportingGeometry = latticePoints;

	// Z Values
	resqml2__DoubleHdf5Array* xmlZValues = soap_new_resqml2__DoubleHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlZValues->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlZValues->Values->HdfProxy = proxy->newResqmlReference();
	ostringstream oss3;
	oss3 << "points_patch" << patchIndex;
	xmlZValues->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/" + oss3.str();
	xmlPoints->ZValues = xmlZValues;

	// HDF
	hsize_t dim[] = {numJ, numI};
	proxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid,
			oss3.str(),
			zValues,
			dim, 2);

	geom->Points = xmlPoints;

	return geom;
}

void AbstractSurfaceRepresentation::loadTargetRelationships()
{
	AbstractRepresentation::loadTargetRelationships();

	resqml2__AbstractSurfaceRepresentation* rep = static_cast<resqml2__AbstractSurfaceRepresentation*>(gsoapProxy2_0_1);

	for (size_t i = 0; i < rep->Boundaries.size(); ++i) {
		if (rep->Boundaries[i]->OuterRing != nullptr) {
			if (rep->Boundaries[i]->OuterRing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREPolylineRepresentation) {
				gsoap_resqml2_0_1::eml20__DataObjectReference* dor = rep->Boundaries[i]->OuterRing;
				PolylineRepresentation * outerRing = getRepository()->getDataObjectByUuid<PolylineRepresentation>(dor->UUID);
				if (outerRing == nullptr) { // partial transfer
					getRepository()->createPartial(dor);
					outerRing = getRepository()->getDataObjectByUuid<PolylineRepresentation>(dor->UUID);
					if (outerRing == nullptr) {
						throw invalid_argument("The DOR looks invalid.");
					}
				}
				getRepository()->addRelationship(this, outerRing);
			}
		}
	}
}

void AbstractSurfaceRepresentation::pushBackOuterRing(PolylineRepresentation * outerRing)
{
	resqml2__AbstractSurfaceRepresentation* rep = static_cast<resqml2__AbstractSurfaceRepresentation*>(gsoapProxy2_0_1);

	resqml2__PatchBoundaries * boundary = soap_new_resqml2__PatchBoundaries(gsoapProxy2_0_1->soap, 1);
	boundary->ReferencedPatch = rep->Boundaries.size();
	boundary->OuterRing = outerRing->newResqmlReference();
	rep->Boundaries.push_back(boundary);

	getRepository()->addRelationship(this, outerRing);
}
