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
#include "prodml2_0/FiberOpticalPath.h"

#include <stdexcept>

using namespace std;
using namespace PRODML2_0_NS;
using namespace gsoap_eml2_1;
using namespace epc;

const char* FiberOpticalPath::XML_TAG = "FiberOpticalPath";

FiberOpticalPath::FiberOpticalPath(soap* soapContext, const string & guid, const string & title,
	const std::string & firstSegmentUid, const double & firstSegmentLength, const gsoap_eml2_1::eml21__LengthUom & firstSegmentLengthUom,
	const std::string & terminatorUid, const gsoap_eml2_1::prodml2__TerminationType & terminationType)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_1 = soap_new_prodml2__FiberOpticalPath(soapContext, 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	_prodml2__FiberOpticalPath* fop = static_cast<_prodml2__FiberOpticalPath*>(gsoapProxy2_1);

	fop->Inventory = soap_new_prodml2__FiberOpticalPathInventory(soapContext, 1);
	prodml2__FiberOpticalPathSegment* fopFirstSegment = soap_new_prodml2__FiberOpticalPathSegment(soapContext, 1);
	fopFirstSegment->uid = firstSegmentUid;
	fopFirstSegment->FiberLength = soap_new_eml21__LengthMeasure(soapContext, 1);
	fopFirstSegment->FiberLength->__item = firstSegmentLength;
	fopFirstSegment->FiberLength->uom = firstSegmentLengthUom;
	fop->Inventory->Segment.push_back(fopFirstSegment);

	fop->Inventory->Terminator = soap_new_prodml2__FiberTerminator(soapContext, 1);
	fop->Inventory->Terminator->uid = terminatorUid;
	fop->Inventory->Terminator->TerminationType = terminationType;
}

vector<Relationship> FiberOpticalPath::getAllEpcRelationships() const
{
	vector<Relationship> result;
	
	// XML backward relationship
	for (size_t i = 0; i < dasAcquisitionSet.size(); i++)
	{
		Relationship rel(dasAcquisitionSet[i]->getPartNameInEpcDocument(), "", dasAcquisitionSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}
	
	return result;
}


