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
using namespace resqml2_0_1;
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

void NonSealedSurfaceFrameworkRepresentation::pushBackNonSealedContactRepresentation(const unsigned int & pointCount, double * points, resqml2::AbstractLocal3dCrs* crs, common::AbstractHdfProxy * proxy)
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

std::string NonSealedSurfaceFrameworkRepresentation::getHdfProxyUuid() const
{
	string result = "";
	_resqml2__NonSealedSurfaceFrameworkRepresentation* orgRep = static_cast<_resqml2__NonSealedSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

	if (orgRep->NonSealedContactRepresentation.size() > 0)
	{
		resqml2__NonSealedContactRepresentationPart* firstContact = static_cast<resqml2__NonSealedContactRepresentationPart*>(orgRep->NonSealedContactRepresentation[0]);
		if (firstContact->Geometry->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__PointGeometry)
		{
			resqml2__PointGeometry* pointGeom = static_cast<resqml2__PointGeometry*>(firstContact->Geometry);
			if (pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dHdf5Array)
			{
				return static_cast<resqml2__Point3dHdf5Array*>(pointGeom->Points)->Coordinates->HdfProxy->UUID;
			}
		}
	}

	return result;
}

vector<Relationship> NonSealedSurfaceFrameworkRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = RepresentationSetRepresentation::getAllEpcRelationships();
        
    // supporting representations of organization sub representations
    for (unsigned int i = 0; i < supportingRepOfContactPatchSet.size(); i++)
    {
		Relationship rel(supportingRepOfContactPatchSet[i]->getPartNameInEpcDocument(), "", supportingRepOfContactPatchSet[i]->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
    }
        
	return result;
}

