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
#include "RepresentationSetRepresentation.h"

#include "../resqml2_2/GenericFeatureInterpretation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* RepresentationSetRepresentation::XML_NS = "resqml22";

RepresentationSetRepresentation::RepresentationSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, const std::string & guid, const string & title)
{
	if (interp == nullptr) {
		throw invalid_argument("The linked interpretation cannot be null. Please use another constructor.");
	}

	// proxy constructor
	gsoapProxy2_3 = soap_new_resqml22__RepresentationSetRepresentation(interp->getGsoapContext());
	static_cast<_resqml22__RepresentationSetRepresentation*>(gsoapProxy2_3)->IsHomogeneous = true;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	interp->getRepository()->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
	// XML relationships
	setInterpretation(interp);
}

RepresentationSetRepresentation::RepresentationSetRepresentation(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be NULL.");
	}

	// proxy constructor
	gsoapProxy2_3 = soap_new_resqml22__RepresentationSetRepresentation(repo->getGsoapContext());
	static_cast<_resqml22__RepresentationSetRepresentation*>(gsoapProxy2_3)->IsHomogeneous = true;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
	setInterpretation(repo->createPartial<RESQML2_2_NS::GenericFeatureInterpretation>("", "Unknown interp"));
}
