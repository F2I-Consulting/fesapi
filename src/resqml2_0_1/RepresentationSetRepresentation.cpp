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
#include "resqml2_0_1/RepresentationSetRepresentation.h"

#include "resqml2/AbstractFeatureInterpretation.h"

using namespace std;
using namespace epc;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

RepresentationSetRepresentation::RepresentationSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, const std::string & guid, const string & title) :
	RESQML2_NS::RepresentationSetRepresentation(interp)
{
	if (interp == nullptr) {
		throw invalid_argument("The linked interpretation cannot be null. Please use another constructor.");
	}

	// proxy constructor
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORERepresentationSetRepresentation(interp->getGsoapContext(), 1);
	static_cast<_resqml2__RepresentationSetRepresentation*>(gsoapProxy2_0_1)->IsHomogeneous = true;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());
	
	// XML relationships
	setInterpretation(interp);
}

RepresentationSetRepresentation::RepresentationSetRepresentation(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be NULL.");
	}

	// proxy constructor
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORERepresentationSetRepresentation(repo->getGsoapContext(), 1);
	static_cast<_resqml2__RepresentationSetRepresentation*>(gsoapProxy2_0_1)->IsHomogeneous = true;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addOrReplaceDataObject(this);
}
