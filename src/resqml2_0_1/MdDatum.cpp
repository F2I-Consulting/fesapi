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
#include "resqml2_0_1/MdDatum.h"

#include <stdexcept>

#include "resqml2/AbstractLocal3dCrs.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

MdDatum::MdDatum(soap* soapContext, const string & guid, const string & title,
			resqml2::AbstractLocal3dCrs * locCrs, const resqml2__MdReference & originKind,
			const double & referenceLocationOrdinal1, const double & referenceLocationOrdinal2, const double & referenceLocationOrdinal3)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context must exist");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREMdDatum(soapContext, 1);
	_resqml2__MdDatum* mdInfo = static_cast<_resqml2__MdDatum*>(gsoapProxy2_0_1);
	
	setLocalCrs(locCrs);

	mdInfo->MdReference = originKind;
	mdInfo->Location = soap_new_resqml2__Point3d(soapContext, 1);
	mdInfo->Location->Coordinate1 = referenceLocationOrdinal1;
	mdInfo->Location->Coordinate2 = referenceLocationOrdinal2;
	mdInfo->Location->Coordinate3 = referenceLocationOrdinal3;
	
	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

void MdDatum::setXmlLocalCrs(resqml2::AbstractLocal3dCrs * localCrs)
{
	_resqml2__MdDatum* mdDatum = static_cast<_resqml2__MdDatum*>(gsoapProxy2_0_1);
	mdDatum->LocalCrs = localCrs->newResqmlReference();
}

double MdDatum::getX() const
{
	return static_cast<_resqml2__MdDatum*>(gsoapProxy2_0_1)->Location->Coordinate1;
}

double MdDatum::getXInGlobalCrs() const
{	
	double result[] = {getX(), getY(), .0};
	if (result[0] != result[0])
		return result[0];

	getLocalCrs()->convertXyzPointsToGlobalCrs(result, 1);

	return result[0];
}

double MdDatum::getY() const
{
	return static_cast<_resqml2__MdDatum*>(gsoapProxy2_0_1)->Location->Coordinate2;
}

double MdDatum::getYInGlobalCrs() const
{
	double result[] = {getX(), getY(), .0};
	if (result[0] != result[0])
		return result[0];

	getLocalCrs()->convertXyzPointsToGlobalCrs(result, 1);

	return result[1];
}

double MdDatum::getZ() const
{
	return static_cast<_resqml2__MdDatum*>(gsoapProxy2_0_1)->Location->Coordinate3;
}

double MdDatum::getZInGlobalCrs() const
{
	double originOrdinal3 = .0;
	resqml2::AbstractLocal3dCrs* localCrs = getLocalCrs();
	if (localCrs->getGsoapType() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORELocalTime3dCrs)
		originOrdinal3 = localCrs->getOriginDepthOrElevation();
	return getZ() + originOrdinal3;
}

gsoap_resqml2_0_1::resqml2__MdReference MdDatum::getOriginKind() const
{
	return static_cast<_resqml2__MdDatum*>(gsoapProxy2_0_1)->MdReference;
}

gsoap_resqml2_0_1::eml20__DataObjectReference* MdDatum::getLocalCrsDor() const
{
	return static_cast<_resqml2__MdDatum*>(gsoapProxy2_0_1)->LocalCrs;
}

