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
#pragma once

#include "resqml2/AbstractFeatureInterpretation.h"

namespace resqml2_0_1
{
	/**
	* This class defines the behaviour of all Resqml2 organizations
	*/
	class DLL_IMPORT_OR_EXPORT AbstractOrganizationInterpretation : public resqml2::AbstractFeatureInterpretation
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractOrganizationInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : resqml2::AbstractFeatureInterpretation(partialObject) {}

		AbstractOrganizationInterpretation() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractOrganizationInterpretation(gsoap_resqml2_0_1::resqml2__AbstractOrganizationInterpretation* fromGsoap) : resqml2::AbstractFeatureInterpretation(fromGsoap) {}

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractOrganizationInterpretation() {}

		/**
		 * Add a binary contact to the organization interpretation by means of a simple sentence.
		 */
		void pushBackBinaryContact(const gsoap_resqml2_0_1::resqml2__ContactRelationship & kind, resqml2::AbstractFeatureInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactVerb & verb, resqml2::AbstractFeatureInterpretation* directObject);

		/**
		 * Add a binary contact to the organization itnerpretation by means of a sentence where the direct object can be qualified.
		 */
		void pushBackBinaryContact(const gsoap_resqml2_0_1::resqml2__ContactRelationship & kind, resqml2::AbstractFeatureInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactVerb & verb, resqml2::AbstractFeatureInterpretation* directObject,
				const gsoap_resqml2_0_1::resqml2__ContactSide & directObjectQualifier);

        /**
         * Add a binary contact to the organization interpretation by means of a sentence where both the subject and the direct object can be qualified.
         */
		void pushBackBinaryContact(const gsoap_resqml2_0_1::resqml2__ContactRelationship & kind, resqml2::AbstractFeatureInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactSide & subjectQualifier,
                                   const gsoap_resqml2_0_1::resqml2__ContactVerb & verb,
								   resqml2::AbstractFeatureInterpretation* directObject, const gsoap_resqml2_0_1::resqml2__ContactSide & directObjectQualifier);
	};
}

