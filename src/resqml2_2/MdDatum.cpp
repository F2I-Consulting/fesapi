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

#include <stdexcept>

#include "../resqml2/AbstractLocal3dCrs.h"
#include "../resqml2/WellboreTrajectoryRepresentation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* MdDatum::XML_NS = "resqml22";

MdDatum::MdDatum(COMMON_NS::DataObjectRepository * repo, const string & guid, const string & title,
	RESQML2_NS::AbstractLocal3dCrs * locCrs, gsoap_eml2_3::eml23__WellboreDatumReference originKind,
	double referenceLocationOrdinal1, double referenceLocationOrdinal2, double referenceLocationOrdinal3)
{
	if (repo == nullptr)
		throw invalid_argument("The repo must exist");

	gsoapProxy2_3 = soap_new_resqml22__MdDatum(repo->getGsoapContext());
	_resqml22__MdDatum* mdDatum = static_cast<_resqml22__MdDatum*>(gsoapProxy2_3);

	mdDatum->MdReference = originKind;
	mdDatum->Location = soap_new_resqml22__SinglePointGeometry(repo->getGsoapContext());
	mdDatum->Location->Point3d = soap_new_resqml22__Point3d(repo->getGsoapContext());
	mdDatum->Location->Point3d->Coordinate1 = referenceLocationOrdinal1;
	mdDatum->Location->Point3d->Coordinate2 = referenceLocationOrdinal2;
	mdDatum->Location->Point3d->Coordinate3 = referenceLocationOrdinal3;
	
	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addOrReplaceDataObject(this);
	setLocalCrs(locCrs);
}

void MdDatum::setLocalCrs(RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	// The constructor must force getRepository() not to return nullptr

	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}

	_resqml22__MdDatum* mdDatum = static_cast<_resqml22__MdDatum*>(gsoapProxy2_3);
	mdDatum->Location->LocalCrs = localCrs->newEml23Reference();

	getRepository()->addRelationship(this, localCrs);
}

double MdDatum::getX() const
{
	return static_cast<_resqml22__MdDatum*>(gsoapProxy2_3)->Location->Point3d->Coordinate1;
}

double MdDatum::getY() const
{
	return static_cast<_resqml22__MdDatum*>(gsoapProxy2_3)->Location->Point3d->Coordinate2;
}

double MdDatum::getZ() const
{
	return static_cast<_resqml22__MdDatum*>(gsoapProxy2_3)->Location->Point3d->Coordinate3;
}

gsoap_eml2_3::eml23__WellboreDatumReference MdDatum::getOriginKind() const
{
	return static_cast<_resqml22__MdDatum*>(gsoapProxy2_3)->MdReference;
}

COMMON_NS::DataObjectReference MdDatum::getLocalCrsDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<_resqml22__MdDatum*>(gsoapProxy2_3)->Location->LocalCrs);
}
