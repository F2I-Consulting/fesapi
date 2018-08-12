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
#include "witsml1_4_1_1/CoordinateReferenceSystem.h"

#include <stdexcept>

#include "tools/GuidTools.h"

using namespace std;
using namespace WITSML1_4_1_1_NS;
using namespace gsoap_witsml1_4_1_1;
using namespace epc;

const char* CoordinateReferenceSystem::XML_TAG = "coordinateReferenceSystems";

CoordinateReferenceSystem::CoordinateReferenceSystem(soap* soapContext,
		const std::string & guid,
		const std::string & title,
		const std::string & namingSystem,
		const std::string & code,
		const std::string & sourceName,
		const time_t & dTimCreation,
		const time_t & dTimLastChange,
		const std::string & comments
	)
{
	if (soapContext == nullptr)
		throw invalid_argument("A soap context must exist.");
	if (title.empty())
		throw invalid_argument("A well must have a name.");

	collection = soap_new_witsml1__obj_USCOREcoordinateReferenceSystems(soapContext, 1);
	static_cast<_witsml1__coordinateReferenceSystems*>(collection)->version = SCHEMA_VERSION;

	witsml1__obj_USCOREcoordinateReferenceSystem* crs = soap_new_witsml1__obj_USCOREcoordinateReferenceSystem(collection->soap, 1);
	static_cast<_witsml1__coordinateReferenceSystems*>(collection)->coordinateReferenceSystem.push_back(crs);

	__witsml1__obj_USCOREcoordinateReferenceSystem_sequence* crsSequence = soap_new___witsml1__obj_USCOREcoordinateReferenceSystem_sequence(collection->soap, 1);

	crsSequence->__union_obj_USCOREcoordinateReferenceSystem = 2;
	crsSequence->union_obj_USCOREcoordinateReferenceSystem.projectedCRS = soap_new_witsml1__cs_USCOREstandardProjectedCRS(collection->soap, 1);
	crsSequence->union_obj_USCOREcoordinateReferenceSystem.projectedCRS->__union_cs_USCOREstandardProjectedCRS = 1;
	crsSequence->union_obj_USCOREcoordinateReferenceSystem.projectedCRS->union_cs_USCOREstandardProjectedCRS.nameCRS = soap_new_witsml1__wellKnownNameStruct(collection->soap, 1);
	
	// here, we suppose that we can use the same name in the coordinatedReferenceSystem and in its referenced projected CRS 
	crsSequence->union_obj_USCOREcoordinateReferenceSystem.projectedCRS->union_cs_USCOREstandardProjectedCRS.nameCRS->__item = title;
	crsSequence->union_obj_USCOREcoordinateReferenceSystem.projectedCRS->union_cs_USCOREstandardProjectedCRS.nameCRS->code = soap_new_std__string(collection->soap, 1);
	crsSequence->union_obj_USCOREcoordinateReferenceSystem.projectedCRS->union_cs_USCOREstandardProjectedCRS.nameCRS->code->assign(code);
	crsSequence->union_obj_USCOREcoordinateReferenceSystem.projectedCRS->union_cs_USCOREstandardProjectedCRS.nameCRS->namingSystem = namingSystem;

	crs->__obj_USCOREcoordinateReferenceSystem_sequence = crsSequence;

	crs->uid = soap_new_std__string(collection->soap, 1);
	if (guid.empty()) {
		crs->uid->assign(GuidTools::generateUidAsString());
	} else {
		crs->uid->assign(guid);
	}

	crs->name = title;

	// create the commonData attribute, if necessary
	if (!sourceName.empty() || dTimCreation>=0 || dTimLastChange>=0 || !comments.empty())
	{
		crs->commonData = newCommonData(sourceName,
			dTimCreation,
			dTimLastChange,
			comments);
	}
}

witsml1__refNameString* CoordinateReferenceSystem::newReference() const
{
	witsml1__refNameString* result = soap_new_witsml1__refNameString(collection->soap, 1);
	result->uidRef = soap_new_std__string(collection->soap, 1);
	result->uidRef->assign(*(static_cast<_witsml1__coordinateReferenceSystems*>(collection)->coordinateReferenceSystem[0]->uid));
	result->__item = static_cast<_witsml1__coordinateReferenceSystems*>(collection)->coordinateReferenceSystem[0]->name;

	return result;
}

vector<Relationship> CoordinateReferenceSystem::getAllEpcRelationships() const
{
	vector<Relationship> result;

	// XML backward relationship
	for (unsigned int j = 0; j < objectsUsingThisCrs.size(); ++j)
	{
		Relationship rel(objectsUsingThisCrs[j]->getPartNameInEpcDocument(), "", objectsUsingThisCrs[j]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

