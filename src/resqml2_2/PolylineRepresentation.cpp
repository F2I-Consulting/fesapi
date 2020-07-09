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
#include "../resqml2/AbstractLocal3dCrs.h"
#include "../resqml2/AbstractValuesProperty.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* PolylineRepresentation::XML_NS = "resqml22";

void PolylineRepresentation::init(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, bool isClosed)
{
	gsoapProxy2_3 = soap_new_resqml22__PolylineRepresentation(repo->getGsoapContext());
	_resqml22__PolylineRepresentation* polylineRep = static_cast<_resqml22__PolylineRepresentation*>(gsoapProxy2_3);

	polylineRep->IsClosed = isClosed;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addOrReplaceDataObject(this);
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
	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_2(0));
}

resqml22__PointGeometry* PolylineRepresentation::getPointGeometry2_2(unsigned int patchIndex) const
{
	return patchIndex == 0 ? static_cast<_resqml22__PolylineRepresentation*>(gsoapProxy2_3)->NodePatch->Geometry : nullptr;
}

ULONG64 PolylineRepresentation::getXyzPointCountOfPatch(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	return static_cast<_resqml22__PolylineRepresentation*>(gsoapProxy2_3)->NodePatch->Count;
}

void PolylineRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	resqml22__PointGeometry* pointGeom = getPointGeometry2_2(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray)
	{
		auto dsPart = static_cast<resqml22__Point3dExternalArray*>(pointGeom->Points)->Coordinates->ExternalFileProxy[0];
		getHdfProxyFromDataset(dsPart)->readArrayNdOfDoubleValues(dsPart->PathInExternalFile, xyzPoints);
	}
	else
		throw invalid_argument("The geometry of the representation either does not exist or it is not an explicit one.");
}

void PolylineRepresentation::setGeometry(double const* points, unsigned int pointCount, EML2_NS::AbstractHdfProxy * proxy, RESQML2_NS::AbstractLocal3dCrs* localCrs)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}

	_resqml22__PolylineRepresentation* polylineRep = static_cast<_resqml22__PolylineRepresentation*>(gsoapProxy2_3);
	polylineRep->NodePatch = soap_new_resqml22__NodePatch(gsoapProxy2_3->soap);
	polylineRep->NodePatch->Count = pointCount;

	hsize_t pointCountDims = pointCount;
	polylineRep->NodePatch->Geometry = createPointGeometryPatch2_2(0, points, localCrs, &pointCountDims, 1, proxy);
	getRepository()->addRelationship(this, localCrs);
}

bool PolylineRepresentation::isClosed() const
{
	return static_cast<_resqml22__PolylineRepresentation*>(gsoapProxy2_3)->IsClosed;
}

bool PolylineRepresentation::hasALineRole() const
{
	return static_cast<_resqml22__PolylineRepresentation*>(gsoapProxy2_3)->LineRole != nullptr;
}

gsoap_eml2_3::resqml22__LineRole PolylineRepresentation::getLineRole() const
{
	if (!hasALineRole()) {
		throw logic_error("The polyline doesn't have any role");
	}

	return *static_cast<_resqml22__PolylineRepresentation*>(gsoapProxy2_3)->LineRole;
}

void PolylineRepresentation::setLineRole(gsoap_eml2_3::resqml22__LineRole lineRole)
{
	if (!hasALineRole()) {
		static_cast<_resqml22__PolylineRepresentation*>(gsoapProxy2_3)->LineRole = (resqml22__LineRole*)soap_malloc(gsoapProxy2_3->soap, sizeof(resqml22__LineRole));
	}

	*static_cast<_resqml22__PolylineRepresentation*>(gsoapProxy2_3)->LineRole = lineRole;
}
