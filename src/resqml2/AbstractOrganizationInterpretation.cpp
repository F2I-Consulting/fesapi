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
#include "AbstractOrganizationInterpretation.h"

#include <stdexcept>

#include "../resqml2_0_1/FrontierFeature.h"
#include "../resqml2_0_1/GeneticBoundaryFeature.h"
#include "../resqml2_0_1/TectonicBoundaryFeature.h"
#include "../resqml2_0_1/StratigraphicUnitFeature.h"

using namespace std;
using namespace RESQML2_NS;
using namespace gsoap_resqml2_0_1;

namespace {
	resqml20__ContactRelationship computeFrom(AbstractFeatureInterpretation* subject, AbstractFeatureInterpretation* directObject) {
		auto subjectFeature = subject->getInterpretedFeature();
		auto directObjectFeature = directObject->getInterpretedFeature();
		if (dynamic_cast<RESQML2_0_1_NS::FrontierFeature*>(subjectFeature) != nullptr) {
			if (dynamic_cast<RESQML2_0_1_NS::FrontierFeature*>(directObjectFeature) != nullptr) {
				return resqml20__ContactRelationship::resqml20__ContactRelationship__frontier_x0020feature_x0020to_x0020frontier_x0020feature;
			}
			else if (dynamic_cast<RESQML2_0_1_NS::GeneticBoundaryFeature*>(directObjectFeature) != nullptr) {
				return resqml20__ContactRelationship::resqml20__ContactRelationship__genetic_x0020boundary_x0020to_x0020frontier_x0020feature;
			}
			else if (dynamic_cast<RESQML2_0_1_NS::TectonicBoundaryFeature*>(directObjectFeature) != nullptr) {
				return resqml20__ContactRelationship::resqml20__ContactRelationship__genetic_x0020boundary_x0020to_x0020frontier_x0020feature;
			}
			else if (dynamic_cast<RESQML2_0_1_NS::StratigraphicUnitFeature*>(directObjectFeature) != nullptr) {
				return resqml20__ContactRelationship::resqml20__ContactRelationship__stratigraphic_x0020unit_x0020to_x0020frontier_x0020feature;
			}
		}
		else if (dynamic_cast<RESQML2_0_1_NS::GeneticBoundaryFeature*>(subjectFeature) != nullptr) {
			if (dynamic_cast<RESQML2_0_1_NS::FrontierFeature*>(directObjectFeature) != nullptr) {
				return resqml20__ContactRelationship::resqml20__ContactRelationship__genetic_x0020boundary_x0020to_x0020frontier_x0020feature;
			}
			else if (dynamic_cast<RESQML2_0_1_NS::GeneticBoundaryFeature*>(directObjectFeature) != nullptr) {
				return resqml20__ContactRelationship::resqml20__ContactRelationship__genetic_x0020boundary_x0020to_x0020genetic_x0020boundary;
			}
			else if (dynamic_cast<RESQML2_0_1_NS::TectonicBoundaryFeature*>(directObjectFeature) != nullptr) {
				return resqml20__ContactRelationship::resqml20__ContactRelationship__genetic_x0020boundary_x0020to_x0020tectonic_x0020boundary;
			}
		}
		else if (dynamic_cast<RESQML2_0_1_NS::StratigraphicUnitFeature*>(subjectFeature) != nullptr) {
			if (dynamic_cast<RESQML2_0_1_NS::FrontierFeature*>(directObjectFeature) != nullptr) {
				return resqml20__ContactRelationship::resqml20__ContactRelationship__stratigraphic_x0020unit_x0020to_x0020frontier_x0020feature;
			}
			else if (dynamic_cast<RESQML2_0_1_NS::StratigraphicUnitFeature*>(directObjectFeature) != nullptr) {
				return resqml20__ContactRelationship::resqml20__ContactRelationship__stratigraphic_x0020unit_x0020to_x0020stratigraphic_x0020unit;
			}
		}
		else if (dynamic_cast<RESQML2_0_1_NS::TectonicBoundaryFeature*>(subjectFeature) != nullptr) {
			if (dynamic_cast<RESQML2_0_1_NS::FrontierFeature*>(directObjectFeature) != nullptr) {
				return resqml20__ContactRelationship::resqml20__ContactRelationship__tectonic_x0020boundary_x0020to_x0020frontier_x0020feature;
			}
			else if (dynamic_cast<RESQML2_0_1_NS::GeneticBoundaryFeature*>(directObjectFeature) != nullptr) {
				return resqml20__ContactRelationship::resqml20__ContactRelationship__tectonic_x0020boundary_x0020to_x0020genetic_x0020boundary;
			}
			else if (dynamic_cast<RESQML2_0_1_NS::TectonicBoundaryFeature*>(directObjectFeature) != nullptr) {
				return resqml20__ContactRelationship::resqml20__ContactRelationship__tectonic_x0020boundary_x0020to_x0020tectonic_x0020boundary;
			}
		}

		throw std::invalid_argument("Invalid type of interpretation for creating such a contact");
	}

	resqml20__ContactVerb mapVerbFrom(gsoap_eml2_2::resqml22__ContactVerb verb) {
		return verb == gsoap_eml2_2::resqml22__ContactVerb::resqml22__ContactVerb__crosses
			? resqml20__ContactVerb::resqml20__ContactVerb__crosses
			: resqml20__ContactVerb::resqml20__ContactVerb__interrupts;
	}
}

void AbstractOrganizationInterpretation::pushBackBinaryContact(AbstractFeatureInterpretation* subject, gsoap_eml2_2::resqml22__ContactVerb verb, AbstractFeatureInterpretation* directObject)
{
	if (subject == nullptr) {
		throw invalid_argument("The subject of the binary contact cannot be null.");
	}
	if (directObject == nullptr) {
		throw invalid_argument("The direct object of the binary contact cannot be null.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		resqml20__AbstractOrganizationInterpretation* org = static_cast<resqml20__AbstractOrganizationInterpretation*>(gsoapProxy2_0_1);

		resqml20__BinaryContactInterpretationPart* contact = soap_new_resqml20__BinaryContactInterpretationPart(org->soap);
		contact->Index = org->ContactInterpretation.size();
		org->ContactInterpretation.push_back(contact);

		contact->ContactRelationship = computeFrom(subject, directObject);
		contact->Subject = subject->newContactElementReference2_0_1(); // Not to add for EPC relationships since by business rule it must be present in the object listing/stack of the organization
		contact->Verb = mapVerbFrom(verb);
		contact->DirectObject = directObject->newContactElementReference2_0_1(); // Not to add for EPC relationships since by business rule it must be present in the object listing/stack of the organization
	}
	else if (gsoapProxy2_2 != nullptr) {
		gsoap_eml2_2::resqml22__AbstractOrganizationInterpretation* org = static_cast<gsoap_eml2_2::resqml22__AbstractOrganizationInterpretation*>(gsoapProxy2_2);

		gsoap_eml2_2::resqml22__BinaryContactInterpretationPart* contact = gsoap_eml2_2::soap_new_resqml22__BinaryContactInterpretationPart(org->soap);
		org->ContactInterpretation.push_back(contact);

		contact->Subject = subject->newContactElementReference2_2(); // Not to add for EPC relationships since by business rule it must be present in the object listing/stack of the organization
		contact->Verb = verb;
		contact->DirectObject = directObject->newContactElementReference2_2(); // Not to add for EPC relationships since by business rule it must be present in the object listing/stack of the organization
	}
}

void AbstractOrganizationInterpretation::pushBackBinaryContact(AbstractFeatureInterpretation* subject, gsoap_eml2_2::resqml22__ContactVerb verb, AbstractFeatureInterpretation* directObject,
	gsoap_resqml2_0_1::resqml20__ContactSide directObjectQualifier)
{
	pushBackBinaryContact(subject, verb, directObject);

	if (gsoapProxy2_0_1 != nullptr) {
		resqml20__AbstractOrganizationInterpretation* org = static_cast<resqml20__AbstractOrganizationInterpretation*>(gsoapProxy2_0_1);
		resqml20__BinaryContactInterpretationPart* contact = static_cast<resqml20__BinaryContactInterpretationPart*>(org->ContactInterpretation[org->ContactInterpretation.size() - 1]);
		contact->DirectObject->Qualifier = static_cast<resqml20__ContactSide*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml20__ContactSide)));
		*(contact->DirectObject->Qualifier) = static_cast<resqml20__ContactSide>(directObjectQualifier);
	}
	else if (gsoapProxy2_2 != nullptr) {
		gsoap_eml2_2::resqml22__AbstractOrganizationInterpretation* org = static_cast<gsoap_eml2_2::resqml22__AbstractOrganizationInterpretation*>(gsoapProxy2_2);
		gsoap_eml2_2::resqml22__BinaryContactInterpretationPart* contact = static_cast<gsoap_eml2_2::resqml22__BinaryContactInterpretationPart*>(org->ContactInterpretation[org->ContactInterpretation.size() - 1]);
		contact->DirectObject->Qualifier = static_cast<gsoap_eml2_2::resqml22__ContactSide*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(gsoap_eml2_2::resqml22__ContactSide)));
		*(contact->DirectObject->Qualifier) = static_cast<gsoap_eml2_2::resqml22__ContactSide>(directObjectQualifier);
	}
}

void AbstractOrganizationInterpretation::pushBackBinaryContact(AbstractFeatureInterpretation* subject, gsoap_resqml2_0_1::resqml20__ContactSide subjectQualifier,
	gsoap_eml2_2::resqml22__ContactVerb verb,
	AbstractFeatureInterpretation* directObject, gsoap_resqml2_0_1::resqml20__ContactSide directObjectQualifier)
{
    pushBackBinaryContact(subject, verb, directObject, directObjectQualifier);

	if (gsoapProxy2_0_1 != nullptr) {
		resqml20__AbstractOrganizationInterpretation* org = static_cast<resqml20__AbstractOrganizationInterpretation*>(gsoapProxy2_0_1);
		resqml20__BinaryContactInterpretationPart* contact = static_cast<resqml20__BinaryContactInterpretationPart*>(org->ContactInterpretation[org->ContactInterpretation.size() - 1]);
		contact->Subject->Qualifier = static_cast<resqml20__ContactSide*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml20__ContactSide)));
		*(contact->Subject->Qualifier) = static_cast<resqml20__ContactSide>(subjectQualifier);
	}
	else if (gsoapProxy2_2 != nullptr) {
		gsoap_eml2_2::resqml22__AbstractOrganizationInterpretation* org = static_cast<gsoap_eml2_2::resqml22__AbstractOrganizationInterpretation*>(gsoapProxy2_2);
		gsoap_eml2_2::resqml22__BinaryContactInterpretationPart* contact = static_cast<gsoap_eml2_2::resqml22__BinaryContactInterpretationPart*>(org->ContactInterpretation[org->ContactInterpretation.size() - 1]);
		contact->Subject->Qualifier = static_cast<gsoap_eml2_2::resqml22__ContactSide*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(gsoap_eml2_2::resqml22__ContactSide)));
		*(contact->Subject->Qualifier) = static_cast<gsoap_eml2_2::resqml22__ContactSide>(subjectQualifier);
	}
}
