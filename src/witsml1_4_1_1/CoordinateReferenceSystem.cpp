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
#include "witsml1_4_1_1/CoordinateReferenceSystem.h"

#include <stdexcept>

#include "tools/GuidTools.h"

using namespace std;
using namespace witsml1_4_1_1;
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
		crs->uid->assign(tools::GuidTools::generateUidAsString());
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
