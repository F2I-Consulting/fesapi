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
#include "resqml2/MdDatum.h"

#include <stdexcept>

#include "resqml2/AbstractLocal3dCrs.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"

using namespace std;
using namespace RESQML2_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* MdDatum::XML_TAG = "MdDatum";

void MdDatum::loadTargetRelationships() const
{
	_resqml2__MdDatum* mdInfo = static_cast<_resqml2__MdDatum*>(gsoapProxy2_0_1);

	gsoap_resqml2_0_1::eml20__DataObjectReference const * dor = getLocalCrsDor();
	if (dor != nullptr) {
		AbstractLocal3dCrs* localCrs = getRepository()->getDataObjectByUuid<AbstractLocal3dCrs>(dor->UUID);
		if (localCrs == nullptr) { // partial transfer
			getRepository()->createPartial(dor);
			localCrs = getRepository()->getDataObjectByUuid<AbstractLocal3dCrs>(dor->UUID);
			if (localCrs == nullptr) {
				throw invalid_argument("The DOR looks invalid.");
			}
		}
		getRepository()->addRelationship(this, localCrs);
	}
}

void MdDatum::setLocalCrs(AbstractLocal3dCrs * localCrs)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
	}
	if (getRepository() == nullptr) {
		localCrs->getRepository()->addOrReplaceDataObject(this);
	}

	setXmlLocalCrs(localCrs);

	getRepository()->addRelationship(this, localCrs);
}

std::string MdDatum::getLocalCrsUuid() const
{
	return getLocalCrsDor()->UUID;
}

AbstractLocal3dCrs * MdDatum::getLocalCrs() const
{
	const string uuidLocalCrs = getLocalCrsUuid();
	return static_cast<AbstractLocal3dCrs*>(repository->getDataObjectByUuid(uuidLocalCrs));
}
