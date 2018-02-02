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
#include "resqml2_0_1/AbstractOrganizationInterpretation.h"

#include <stdexcept>

#include "resqml2_0_1/OrganizationFeature.h"
#include "resqml2_0_1/EarthModelInterpretation.h"

using namespace std;
using namespace epc;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

void AbstractOrganizationInterpretation::pushBackBinaryContact(const gsoap_resqml2_0_1::resqml2__ContactRelationship & kind, AbstractFeatureInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactVerb & verb, AbstractFeatureInterpretation* directObject)
{
	if (!subject)
		throw invalid_argument("The subject of the binary contact cannot be null.");
	if (!directObject)
		throw invalid_argument("The direct object of the binary contact cannot be null.");

	resqml2__AbstractOrganizationInterpretation* org = static_cast<resqml2__AbstractOrganizationInterpretation*>(gsoapProxy2_0_1);

	resqml2__BinaryContactInterpretationPart* contact = soap_new_resqml2__BinaryContactInterpretationPart(org->soap, 1);
	contact->Index = org->ContactInterpretation.size();
	org->ContactInterpretation.push_back(contact);

	contact->ContactRelationship = kind;
	contact->Subject = subject->newResqmlContactElementReference(); // Not to add for EPC relationships since by business rule it must be present in the object listing/stack of the organization
	contact->Verb = verb;
	contact->DirectObject = directObject->newResqmlContactElementReference(); // Not to add for EPC relationships since by business rule it must be present in the object listing/stack of the organization
}

void AbstractOrganizationInterpretation::pushBackBinaryContact(const gsoap_resqml2_0_1::resqml2__ContactRelationship & kind, AbstractFeatureInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactVerb & verb, AbstractFeatureInterpretation* directObject,
		const gsoap_resqml2_0_1::resqml2__ContactSide & directObjectQualifier)
{
	resqml2__AbstractOrganizationInterpretation* org = static_cast<resqml2__AbstractOrganizationInterpretation*>(gsoapProxy2_0_1);

	pushBackBinaryContact(kind, subject, verb, directObject);
	resqml2__BinaryContactInterpretationPart* contact = static_cast<resqml2__BinaryContactInterpretationPart*>(org->ContactInterpretation[org->ContactInterpretation.size() - 1]);
	contact->DirectObject->Qualifier = static_cast<resqml2__ContactSide*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml2__ContactSide)));
	*(contact->DirectObject->Qualifier) = directObjectQualifier;
}

void AbstractOrganizationInterpretation::pushBackBinaryContact(const gsoap_resqml2_0_1::resqml2__ContactRelationship & kind, AbstractFeatureInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactSide & subjectQualifier,
        const gsoap_resqml2_0_1::resqml2__ContactVerb & verb,
        AbstractFeatureInterpretation* directObject, const gsoap_resqml2_0_1::resqml2__ContactSide & directObjectQualifier)
{
    resqml2__AbstractOrganizationInterpretation* org = static_cast<resqml2__AbstractOrganizationInterpretation*>(gsoapProxy2_0_1);

    pushBackBinaryContact(kind, subject, verb, directObject);
    resqml2__BinaryContactInterpretationPart* contact = static_cast<resqml2__BinaryContactInterpretationPart*>(org->ContactInterpretation[org->ContactInterpretation.size() - 1]);
    contact->DirectObject->Qualifier = static_cast<resqml2__ContactSide*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml2__ContactSide)));
    *(contact->DirectObject->Qualifier) = directObjectQualifier;
    contact->Subject->Qualifier = static_cast<resqml2__ContactSide*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml2__ContactSide)));
    *(contact->Subject->Qualifier) = subjectQualifier;
}

