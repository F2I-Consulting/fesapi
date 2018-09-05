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
#include "resqml2/AbstractFeatureInterpretation.h"
#include "common/AbstractHdfProxy.h"
#include "resqml2/AbstractLocal3dCrs.h"

using namespace std;
using namespace epc;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* NonSealedSurfaceFrameworkRepresentation::XML_TAG = "NonSealedSurfaceFrameworkRepresentation";

NonSealedSurfaceFrameworkRepresentation::NonSealedSurfaceFrameworkRepresentation(
        StructuralOrganizationInterpretation* interp,
        const std::string & guid, 
        const std::string & title,
        const bool & isSealed):
	RepresentationSetRepresentation(interp)
{
	if (!interp)
		throw invalid_argument("The structural organization interpretation cannot be null.");

	// proxy constructor
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORENonSealedSurfaceFrameworkRepresentation(interp->getGsoapContext(), 1);	
	_resqml2__NonSealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml2__NonSealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);
    
	orgRep->RepresentedInterpretation = soap_new_eml20__DataObjectReference(gsoapProxy2_0_1->soap, 1);
    orgRep->RepresentedInterpretation->UUID.assign(interp->getUuid());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	setInterpretation(interp);
}

void NonSealedSurfaceFrameworkRepresentation::pushBackNonSealedContactRepresentation(const unsigned int & pointCount, double * points, RESQML2_NS::AbstractLocal3dCrs* crs, COMMON_NS::AbstractHdfProxy * proxy)
{
	if (pointCount == 0)
		throw invalid_argument("Contact point count cannot be zero.");
	if (!points)
		throw invalid_argument("The contact points cannot be null.");
	if (!proxy)
		throw invalid_argument("The HDF proxy cannot be null.");

	if (localCrs == nullptr)
	{
		localCrs = crs;
		localCrs->addRepresentation(this);
	}

	setHdfProxy(proxy);
	_resqml2__NonSealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml2__NonSealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

	resqml2__NonSealedContactRepresentationPart* contactRep = soap_new_resqml2__NonSealedContactRepresentationPart(gsoapProxy2_0_1->soap, 1);
	contactRep->Index = orgRep->NonSealedContactRepresentation.size();
	orgRep->NonSealedContactRepresentation.push_back(contactRep);
	resqml2__PointGeometry* contactGeom = soap_new_resqml2__PointGeometry(gsoapProxy2_0_1->soap, 1);
	contactRep->Geometry = contactGeom;
	contactGeom->LocalCrs = localCrs->newResqmlReference();
	resqml2__Point3dHdf5Array* contactGeomPoints = soap_new_resqml2__Point3dHdf5Array(gsoapProxy2_0_1->soap, 1);
	contactGeom->Points = contactGeomPoints;
	contactGeomPoints->Coordinates = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	contactGeomPoints->Coordinates->HdfProxy = hdfProxy->newResqmlReference();
	ostringstream oss;
	oss << "points_contact_representation" << orgRep->NonSealedContactRepresentation.size()-1;
	contactGeomPoints->Coordinates->PathInHdfFile = "/RESQML/" + getUuid() + "/" + oss.str();
	
	// HDF
	hsize_t numValues[2];
	numValues[0] = pointCount;
	numValues[1] = 3; // 3 for X, Y and Z

	hdfProxy->writeArrayNdOfDoubleValues(getUuid(), oss.str(), points, numValues, 2);
}

gsoap_resqml2_0_1::eml20__DataObjectReference* NonSealedSurfaceFrameworkRepresentation::getHdfProxyDor() const
{
	_resqml2__NonSealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml2__NonSealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

	if (!orgRep->NonSealedContactRepresentation.empty())
	{
		resqml2__NonSealedContactRepresentationPart* firstContact = static_cast<resqml2__NonSealedContactRepresentationPart*>(orgRep->NonSealedContactRepresentation[0]);
		if (firstContact->Geometry->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__PointGeometry)
		{
			resqml2__PointGeometry* pointGeom = static_cast<resqml2__PointGeometry*>(firstContact->Geometry);
			if (pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dHdf5Array)
			{
				return static_cast<resqml2__Point3dHdf5Array*>(pointGeom->Points)->Coordinates->HdfProxy;
			}
		}
	}

	return nullptr;
}

vector<Relationship> NonSealedSurfaceFrameworkRepresentation::getAllTargetRelationships() const
{
	vector<Relationship> result = RepresentationSetRepresentation::getAllTargetRelationships();
        
    // supporting representations of organization sub representations
    for (size_t i = 0; i < supportingRepOfContactPatchSet.size(); ++i)
    {
		Relationship rel(supportingRepOfContactPatchSet[i]->getPartNameInEpcDocument(), "", supportingRepOfContactPatchSet[i]->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
    }
        
	return result;
}


