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

#include "OrganizationFeature.h"
#include "EarthModelInterpretation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* AbstractOrganizationInterpretation::XML_NS = "resqml20";

void AbstractOrganizationInterpretation::pushBackBinaryContact(gsoap_resqml2_0_1::resqml20__ContactRelationship kind, AbstractFeatureInterpretation* subject, gsoap_resqml2_0_1::resqml20__ContactVerb verb, AbstractFeatureInterpretation* directObject)
{
	if (!subject)
		throw invalid_argument("The subject of the binary contact cannot be null.");
	if (!directObject)
		throw invalid_argument("The direct object of the binary contact cannot be null.");

	resqml20__AbstractOrganizationInterpretation* org = static_cast<resqml20__AbstractOrganizationInterpretation*>(gsoapProxy2_0_1);

	resqml20__BinaryContactInterpretationPart* contact = soap_new_resqml20__BinaryContactInterpretationPart(org->soap);
	contact->Index = org->ContactInterpretation.size();
	org->ContactInterpretation.push_back(contact);

	contact->ContactRelationship = kind;
	contact->Subject = subject->newResqmlContactElementReference(); // Not to add for EPC relationships since by business rule it must be present in the object listing/stack of the organization
	contact->Verb = verb;
	contact->DirectObject = directObject->newResqmlContactElementReference(); // Not to add for EPC relationships since by business rule it must be present in the object listing/stack of the organization
}

void AbstractOrganizationInterpretation::pushBackBinaryContact(gsoap_resqml2_0_1::resqml20__ContactRelationship kind, AbstractFeatureInterpretation* subject, gsoap_resqml2_0_1::resqml20__ContactVerb verb, AbstractFeatureInterpretation* directObject,
		gsoap_resqml2_0_1::resqml20__ContactSide directObjectQualifier)
{
	resqml20__AbstractOrganizationInterpretation* org = static_cast<resqml20__AbstractOrganizationInterpretation*>(gsoapProxy2_0_1);

	pushBackBinaryContact(kind, subject, verb, directObject);
	resqml20__BinaryContactInterpretationPart* contact = static_cast<resqml20__BinaryContactInterpretationPart*>(org->ContactInterpretation[org->ContactInterpretation.size() - 1]);
	contact->DirectObject->Qualifier = static_cast<resqml20__ContactSide*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml20__ContactSide)));
	*(contact->DirectObject->Qualifier) = directObjectQualifier;
}

void AbstractOrganizationInterpretation::pushBackBinaryContact(gsoap_resqml2_0_1::resqml20__ContactRelationship kind, AbstractFeatureInterpretation* subject, gsoap_resqml2_0_1::resqml20__ContactSide subjectQualifier,
        gsoap_resqml2_0_1::resqml20__ContactVerb verb,
        AbstractFeatureInterpretation* directObject, gsoap_resqml2_0_1::resqml20__ContactSide directObjectQualifier)
{
    resqml20__AbstractOrganizationInterpretation* org = static_cast<resqml20__AbstractOrganizationInterpretation*>(gsoapProxy2_0_1);

    pushBackBinaryContact(kind, subject, verb, directObject);
    resqml20__BinaryContactInterpretationPart* contact = static_cast<resqml20__BinaryContactInterpretationPart*>(org->ContactInterpretation[org->ContactInterpretation.size() - 1]);
    contact->DirectObject->Qualifier = static_cast<resqml20__ContactSide*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml20__ContactSide)));
    *(contact->DirectObject->Qualifier) = directObjectQualifier;
    contact->Subject->Qualifier = static_cast<resqml20__ContactSide*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml20__ContactSide)));
    *(contact->Subject->Qualifier) = subjectQualifier;
}
