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
#include "ReferencePointInALocalEngineeringCompoundCrs.h"

#include <stdexcept>

#include "../eml2/AbstractLocal3dCrs.h"

#include "../resqml2/WellboreTrajectoryRepresentation.h"

using namespace std;
using namespace EML2_3_NS;
using namespace gsoap_eml2_3;

const char* ReferencePointInALocalEngineeringCompoundCrs::XML_TAG = "ReferencePointInALocalEngineeringCompoundCrs";

ReferencePointInALocalEngineeringCompoundCrs::ReferencePointInALocalEngineeringCompoundCrs(COMMON_NS::DataObjectRepository * repo, const string & guid, const string & title,
	EML2_NS::AbstractLocal3dCrs * locCrs, gsoap_eml2_3::eml23__WellboreDatumReference originKind,
	double referenceLocationOrdinal1, double referenceLocationOrdinal2, double referenceLocationOrdinal3)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo must exist");
	}

	gsoapProxy2_3 = soap_new_eml23__ReferencePointInALocalEngineeringCompoundCrs(repo->getGsoapContext());
	_eml23__ReferencePointInALocalEngineeringCompoundCrs* refPt = static_cast<_eml23__ReferencePointInALocalEngineeringCompoundCrs*>(gsoapProxy2_3);

	refPt->Kind = soap_new_std__string(repo->getGsoapContext());
	refPt->Kind->assign(soap_eml23__WellboreDatumReference2s(gsoapProxy2_3->soap, originKind));
	refPt->Coordinates1And2 = soap_new_eml23__HorizontalCoordinates(repo->getGsoapContext());
	refPt->Coordinates1And2->Coordinate1 = referenceLocationOrdinal1;
	refPt->Coordinates1And2->Coordinate2 = referenceLocationOrdinal2;
	refPt->Coordinate3 = soap_new_double(repo->getGsoapContext());
	*refPt->Coordinate3 = referenceLocationOrdinal3;
	
	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(this);
	setLocalCrs(locCrs);
}

void ReferencePointInALocalEngineeringCompoundCrs::setLocalCrs(EML2_NS::AbstractLocal3dCrs * localCrs)
{
	// The constructor must force getRepository() not to return nullptr

	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}

	_eml23__ReferencePointInALocalEngineeringCompoundCrs* refPt = static_cast<_eml23__ReferencePointInALocalEngineeringCompoundCrs*>(gsoapProxy2_3);
	refPt->Crs = localCrs->newEml23Reference();

	getRepository()->addRelationship(this, localCrs);
}

double ReferencePointInALocalEngineeringCompoundCrs::getX() const
{
	return static_cast<_eml23__ReferencePointInALocalEngineeringCompoundCrs*>(gsoapProxy2_3)->Coordinates1And2 == nullptr
		? .0
		: static_cast<_eml23__ReferencePointInALocalEngineeringCompoundCrs*>(gsoapProxy2_3)->Coordinates1And2->Coordinate1;
}

double ReferencePointInALocalEngineeringCompoundCrs::getY() const
{
	return static_cast<_eml23__ReferencePointInALocalEngineeringCompoundCrs*>(gsoapProxy2_3)->Coordinates1And2 == nullptr
		? .0
		: static_cast<_eml23__ReferencePointInALocalEngineeringCompoundCrs*>(gsoapProxy2_3)->Coordinates1And2->Coordinate2;
}

double ReferencePointInALocalEngineeringCompoundCrs::getZ() const
{
	return static_cast<_eml23__ReferencePointInALocalEngineeringCompoundCrs*>(gsoapProxy2_3)->Coordinate3 == nullptr
		? .0
		: *static_cast<_eml23__ReferencePointInALocalEngineeringCompoundCrs*>(gsoapProxy2_3)->Coordinate3;
}

bool ReferencePointInALocalEngineeringCompoundCrs::hasKind() const
{
	return static_cast<_eml23__ReferencePointInALocalEngineeringCompoundCrs*>(gsoapProxy2_3)->Kind != nullptr;
}

gsoap_eml2_3::eml23__ReferencePointKind ReferencePointInALocalEngineeringCompoundCrs::getKind() const
{
	if (!hasKind()) {
		throw logic_error("This reference point has no kind");
	}

	gsoap_eml2_3::eml23__ReferencePointKind result;

	if (soap_s2eml23__ReferencePointKind(getGsoapContext(), static_cast<_eml23__ReferencePointInALocalEngineeringCompoundCrs*>(gsoapProxy2_3)->Kind->c_str(), &result) != SOAP_OK) {
		throw invalid_argument("The reference point kind \"" + *static_cast<_eml23__ReferencePointInALocalEngineeringCompoundCrs*>(gsoapProxy2_3)->Kind + "\" is not recognized by FESAPI.");
	}

	return result;
}

COMMON_NS::DataObjectReference ReferencePointInALocalEngineeringCompoundCrs::getLocalCrsDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<_eml23__ReferencePointInALocalEngineeringCompoundCrs*>(gsoapProxy2_3)->Crs);
}
