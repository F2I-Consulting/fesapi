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
using namespace RESQML2_NS;
using namespace gsoap_resqml2_0_1;

const char* MdDatum::XML_TAG = "MdDatum";

double MdDatum::getXInGlobalCrs() const
{
	double result[] = { getX(), getY(), .0 };
	if (result[0] != result[0])
		return result[0];

	getLocalCrs()->convertXyzPointsToGlobalCrs(result, 1);

	return result[0];
}

double MdDatum::getYInGlobalCrs() const
{
	double result[] = { getX(), getY(), .0 };
	if (result[0] != result[0])
		return result[0];

	getLocalCrs()->convertXyzPointsToGlobalCrs(result, 1);

	return result[1];
}

double MdDatum::getZInGlobalCrs() const
{
	double originOrdinal3 = .0;
	EML2_NS::AbstractLocal3dCrs* localCrs = getLocalCrs();
	if (localCrs->getGsoapType() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCORELocalTime3dCrs)
		originOrdinal3 = localCrs->getOriginDepthOrElevation();
	return getZ() + originOrdinal3;
}

EML2_NS::AbstractLocal3dCrs * MdDatum::getLocalCrs() const
{
	const string uuidLocalCrs = getLocalCrsDor().getUuid();
	return static_cast<EML2_NS::AbstractLocal3dCrs*>(repository->getDataObjectByUuid(uuidLocalCrs));
}
