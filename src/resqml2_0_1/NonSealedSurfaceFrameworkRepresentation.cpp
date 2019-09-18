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
#include "resqml2_0_1/NonSealedSurfaceFrameworkRepresentation.h"

#include <algorithm>
#include <stdexcept>
#include <sstream>

#include "H5public.h"

#include "resqml2_0_1/StructuralOrganizationInterpretation.h"
#include "common/AbstractHdfProxy.h"
#include "resqml2/AbstractLocal3dCrs.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* NonSealedSurfaceFrameworkRepresentation::XML_TAG = "NonSealedSurfaceFrameworkRepresentation";

NonSealedSurfaceFrameworkRepresentation::NonSealedSurfaceFrameworkRepresentation(
        StructuralOrganizationInterpretation* interp,
        const std::string & guid, 
        const std::string & title)
{
	if (interp == nullptr) {
		throw invalid_argument("The structural organization interpretation cannot be null.");
	}

	// proxy constructor
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORENonSealedSurfaceFrameworkRepresentation(interp->getGsoapContext(), 1);	
	_resqml20__NonSealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml20__NonSealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

	orgRep->IsHomogeneous = true;
	orgRep->RepresentedInterpretation = soap_new_eml20__DataObjectReference(gsoapProxy2_0_1->soap, 1);
    orgRep->RepresentedInterpretation->UUID.assign(interp->getUuid());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setInterpretation(interp);
}

void NonSealedSurfaceFrameworkRepresentation::pushBackNonSealedContactRepresentation(unsigned int pointCount, double * points, COMMON_NS::AbstractHdfProxy * proxy, RESQML2_NS::AbstractLocal3dCrs* localCrs)
{
	if (pointCount == 0)
		throw invalid_argument("Contact point count cannot be zero.");
	if (points == nullptr)
		throw invalid_argument("The contact points cannot be null.");

	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
	}
	getRepository()->addRelationship(this, proxy);

	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
	}

	_resqml20__NonSealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml20__NonSealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

	resqml20__NonSealedContactRepresentationPart* contactRep = soap_new_resqml20__NonSealedContactRepresentationPart(gsoapProxy2_0_1->soap, 1);
	contactRep->Index = orgRep->NonSealedContactRepresentation.size();
	orgRep->NonSealedContactRepresentation.push_back(contactRep);
	resqml20__PointGeometry* contactGeom = soap_new_resqml20__PointGeometry(gsoapProxy2_0_1->soap, 1);
	contactRep->Geometry = contactGeom;
	contactGeom->LocalCrs = localCrs->newResqmlReference();
	resqml20__Point3dHdf5Array* contactGeomPoints = soap_new_resqml20__Point3dHdf5Array(gsoapProxy2_0_1->soap, 1);
	contactGeom->Points = contactGeomPoints;
	contactGeomPoints->Coordinates = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	contactGeomPoints->Coordinates->HdfProxy = proxy->newResqmlReference();
	ostringstream oss;
	oss << "points_contact_representation" << orgRep->NonSealedContactRepresentation.size()-1;
	contactGeomPoints->Coordinates->PathInHdfFile = "/RESQML/" + getUuid() + "/" + oss.str();
	
	// HDF
	hsize_t numValues[2];
	numValues[0] = pointCount;
	numValues[1] = 3; // 3 for X, Y and Z

	proxy->writeArrayNdOfDoubleValues(getUuid(), oss.str(), points, numValues, 2);

	getRepository()->addRelationship(this, localCrs);
}

std::string NonSealedSurfaceFrameworkRepresentation::getHdfProxyUuid() const
{
	string result;
	_resqml20__NonSealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml20__NonSealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

	if (!orgRep->NonSealedContactRepresentation.empty())
	{
		resqml20__NonSealedContactRepresentationPart* firstContact = static_cast<resqml20__NonSealedContactRepresentationPart*>(orgRep->NonSealedContactRepresentation[0]);
		if (firstContact->Geometry->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__PointGeometry)
		{
			resqml20__PointGeometry* pointGeom = static_cast<resqml20__PointGeometry*>(firstContact->Geometry);
			if (pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array)
			{
				return static_cast<resqml20__Point3dHdf5Array*>(pointGeom->Points)->Coordinates->HdfProxy->UUID;
			}
		}
	}

	return result;
}

unsigned int NonSealedSurfaceFrameworkRepresentation::getContactCount() const
{
	_resqml20__NonSealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml20__NonSealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

	if (orgRep->NonSealedContactRepresentation.size() > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too much contact representations for fesapi");
	}

	return static_cast<unsigned int>(orgRep->NonSealedContactRepresentation.size());
}
