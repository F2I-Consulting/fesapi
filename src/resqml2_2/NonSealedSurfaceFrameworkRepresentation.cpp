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
#include "NonSealedSurfaceFrameworkRepresentation.h"

#include <limits>
#include <stdexcept>
#include <sstream>

#include <H5public.h>

#include "../eml2/AbstractHdfProxy.h"

#include "../resqml2/AbstractLocal3dCrs.h"
#include "../resqml2/StructuralOrganizationInterpretation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

NonSealedSurfaceFrameworkRepresentation::NonSealedSurfaceFrameworkRepresentation(
	RESQML2_NS::StructuralOrganizationInterpretation* interp,
    const std::string & guid, 
    const std::string & title)
{
	if (interp == nullptr) {
		throw invalid_argument("The structural organization interpretation cannot be null.");
	}

	// proxy constructor
	gsoapProxy2_3 = soap_new_resqml22__NonSealedSurfaceFrameworkRepresentation(interp->getGsoapContext());	
	_resqml22__NonSealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml22__NonSealedSurfaceFrameworkRepresentation*>(gsoapProxy2_3);

	orgRep->IsHomogeneous = true;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setInterpretation(interp);
}

void NonSealedSurfaceFrameworkRepresentation::pushBackNonSealedContactRepresentation(unsigned int pointCount, double const* points, EML2_NS::AbstractHdfProxy * proxy, RESQML2_NS::AbstractLocal3dCrs* localCrs)
{
	if (pointCount == 0)
		throw invalid_argument("Contact point count cannot be zero.");
	if (points == nullptr)
		throw invalid_argument("The contact points cannot be null.");
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
	getRepository()->addRelationship(this, proxy);

	_resqml22__NonSealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml22__NonSealedSurfaceFrameworkRepresentation*>(gsoapProxy2_3);

	resqml22__NonSealedContactRepresentationPart* contactRep = soap_new_resqml22__NonSealedContactRepresentationPart(gsoapProxy2_3->soap);
	contactRep->Index = orgRep->NonSealedContactRepresentation.size();
	orgRep->NonSealedContactRepresentation.push_back(contactRep);
	resqml22__PointGeometry* contactGeom = soap_new_resqml22__PointGeometry(gsoapProxy2_3->soap);
	contactRep->Geometry = contactGeom;
	contactGeom->LocalCrs = localCrs->newEml23Reference();
	resqml22__Point3dExternalArray* contactGeomPoints = soap_new_resqml22__Point3dExternalArray(gsoapProxy2_3->soap);
	contactGeom->Points = contactGeomPoints;
	contactGeomPoints->Coordinates = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	auto dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	ostringstream oss;
	oss << "points_contact_representation" << orgRep->NonSealedContactRepresentation.size()-1;
	dsPart->PathInExternalFile = getHdfGroup() + "/" + oss.str();
	contactGeomPoints->Coordinates->ExternalFileProxy.push_back(dsPart);
	
	// HDF
	hsize_t numValues[2];
	numValues[0] = pointCount;
	numValues[1] = 3; // 3 for X, Y and Z

	proxy->writeArrayNdOfDoubleValues(getHdfGroup(), oss.str(), points, numValues, 2);

	getRepository()->addRelationship(this, localCrs);
}

unsigned int NonSealedSurfaceFrameworkRepresentation::getContactCount() const
{
	_resqml22__NonSealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml22__NonSealedSurfaceFrameworkRepresentation*>(gsoapProxy2_3);

	if (orgRep->NonSealedContactRepresentation.size() > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too much contact representations for fesapi");
	}

	return static_cast<unsigned int>(orgRep->NonSealedContactRepresentation.size());
}
