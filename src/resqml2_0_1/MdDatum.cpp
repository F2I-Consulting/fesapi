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
#include "MdDatum.h"

#include "../eml2/AbstractLocal3dCrs.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

MdDatum::MdDatum(COMMON_NS::DataObjectRepository * repo, const string & guid, const string & title,
	EML2_NS::AbstractLocal3dCrs * locCrs, gsoap_eml2_3::eml23__ReferencePointKind originKind,
	double referenceLocationOrdinal1, double referenceLocationOrdinal2, double referenceLocationOrdinal3)
{
	if (repo == nullptr)
		throw invalid_argument("The repo must exist");

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREMdDatum(repo->getGsoapContext());
	_resqml20__MdDatum* mdInfo = static_cast<_resqml20__MdDatum*>(gsoapProxy2_0_1);

	mdInfo->MdReference = static_cast<std::underlying_type<gsoap_eml2_3::eml23__ReferencePointKind>::type>(originKind) < 5
		? static_cast<resqml20__MdReference>(static_cast<std::underlying_type<gsoap_eml2_3::eml23__ReferencePointKind>::type>(originKind))
		: static_cast<resqml20__MdReference>(static_cast<std::underlying_type<gsoap_eml2_3::eml23__ReferencePointKind>::type>(originKind) + 1);
	mdInfo->Location = soap_new_resqml20__Point3d(repo->getGsoapContext());
	mdInfo->Location->Coordinate1 = referenceLocationOrdinal1;
	mdInfo->Location->Coordinate2 = referenceLocationOrdinal2;
	mdInfo->Location->Coordinate3 = referenceLocationOrdinal3;
	
	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addDataObject(this);
	setLocalCrs(locCrs);
}

void MdDatum::setLocalCrs(EML2_NS::AbstractLocal3dCrs * localCrs)
{
	// The constructor must force getRepository() not to return nullptr

	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}

	_resqml20__MdDatum* mdDatum = static_cast<_resqml20__MdDatum*>(gsoapProxy2_0_1);
	mdDatum->LocalCrs = localCrs->newResqmlReference();

	getRepository()->addRelationship(this, localCrs);
}

double MdDatum::getX() const
{
	return static_cast<_resqml20__MdDatum*>(gsoapProxy2_0_1)->Location->Coordinate1;
}

double MdDatum::getY() const
{
	return static_cast<_resqml20__MdDatum*>(gsoapProxy2_0_1)->Location->Coordinate2;
}

double MdDatum::getZ() const
{
	return static_cast<_resqml20__MdDatum*>(gsoapProxy2_0_1)->Location->Coordinate3;
}

bool MdDatum::hasKind() const
{
	return static_cast<_resqml20__MdDatum*>(gsoapProxy2_0_1)->MdReference != resqml20__MdReference::arbitrary_x0020point;
}

gsoap_eml2_3::eml23__ReferencePointKind MdDatum::getKind() const
{
	if (!hasKind()) {
		throw logic_error("This reference point has no kind : it is an arbitrary point.");
	}

	gsoap_eml2_3::eml23__ReferencePointKind result;

	std::string mdRefStr = soap_resqml20__MdReference2s(getGsoapContext(), static_cast<_resqml20__MdDatum*>(gsoapProxy2_0_1)->MdReference);
	if (gsoap_eml2_3::soap_s2eml23__ReferencePointKind(getGsoapContext(), mdRefStr.c_str(), &result) != SOAP_OK) {
		throw invalid_argument("The reference point kind \"" + mdRefStr + "\" is not recognized by FESAPI.");
	}

	return result;
}

COMMON_NS::DataObjectReference MdDatum::getLocalCrsDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<_resqml20__MdDatum*>(gsoapProxy2_0_1)->LocalCrs);
}

void MdDatum::loadTargetRelationships()
{
	COMMON_NS::DataObjectReference dor = getLocalCrsDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<EML2_NS::AbstractLocal3dCrs>(dor);
	}
}
