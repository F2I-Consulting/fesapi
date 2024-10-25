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
#include "PolylineRepresentation.h"

#include <stdexcept>

#include "H5public.h"

#include "../resqml2/AbstractFeature.h"
#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../eml2/AbstractLocal3dCrs.h"
#include "../resqml2/AbstractValuesProperty.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* PolylineRepresentation::XML_NS = "resqml20";

void PolylineRepresentation::init(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, bool isClosed)
{
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREPolylineRepresentation(repo->getGsoapContext());
	_resqml20__PolylineRepresentation* polylineRep = static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1);

	polylineRep->IsClosed = isClosed;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
}

PolylineRepresentation::PolylineRepresentation(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, bool isClosed)
{
	init(repo, guid, title, isClosed);
}

PolylineRepresentation::PolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title, bool isClosed)
{
	if (interp == nullptr) {
		throw invalid_argument("You must provide an interpretation");
	}
	init(interp->getRepository(), guid, title, isClosed);

	setInterpretation(interp);
}

PolylineRepresentation::PolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title, gsoap_eml2_3::resqml22__LineRole roleKind,
	bool isClosed)
{
	if (interp == nullptr) {
		throw invalid_argument("You must provide an interpretation");
	}

	init(interp->getRepository(), guid, title, isClosed);
	setLineRole(roleKind);

	setInterpretation(interp);
}

COMMON_NS::DataObjectReference PolylineRepresentation::getHdfProxyDor() const
{
	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

resqml20__PointGeometry* PolylineRepresentation::getPointGeometry2_0_1(uint64_t patchIndex) const
{
	return patchIndex == 0 ? static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1)->NodePatch->Geometry : nullptr;
}

uint64_t PolylineRepresentation::getXyzPointCountOfPatch(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	return static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1)->NodePatch->Count;
}

void PolylineRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

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

void PolylineRepresentation::setGeometry(double const* points, unsigned int pointCount, EML2_NS::AbstractHdfProxy * proxy, EML2_NS::AbstractLocal3dCrs* localCrs)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}

	_resqml20__PolylineRepresentation* polylineRep = static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1);
	polylineRep->NodePatch = soap_new_resqml20__NodePatch(gsoapProxy2_0_1->soap);
	polylineRep->NodePatch->Count = pointCount;
	polylineRep->NodePatch->PatchIndex = 0;

	uint64_t pointCountDims[2] = { pointCount, 3 };
	polylineRep->NodePatch->Geometry = createPointGeometryPatch2_0_1(0, points, localCrs, pointCountDims, 2, proxy);
	getRepository()->addRelationship(this, localCrs);
}

bool PolylineRepresentation::isClosed() const
{
	return static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1)->IsClosed;
}

bool PolylineRepresentation::hasALineRole() const
{
	return static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1)->LineRole != nullptr;
}

gsoap_eml2_3::resqml22__LineRole PolylineRepresentation::getLineRole() const
{
	if (!hasALineRole()) {
		throw logic_error("The polyline doesn't have any role");
	}

	return static_cast<gsoap_eml2_3::resqml22__LineRole>(*static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1)->LineRole);
}

void PolylineRepresentation::setLineRole(gsoap_eml2_3::resqml22__LineRole lineRole)
{
	if (lineRole == gsoap_eml2_3::resqml22__LineRole::break_x0020line) {
		throw invalid_argument("Break line enumerated value is not supported in RESQML2.0.1");
	}

	if (!hasALineRole()) {
		static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1)->LineRole = (resqml20__LineRole*)soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml20__LineRole));
	}

	*static_cast<_resqml20__PolylineRepresentation*>(gsoapProxy2_0_1)->LineRole = static_cast<gsoap_resqml2_0_1::resqml20__LineRole>(lineRole);
}
