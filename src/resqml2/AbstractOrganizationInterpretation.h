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

#include "AbstractFeatureInterpretation.h"

namespace RESQML2_NS
{
	class Model;

	/**
	* This class defines the behaviour of all RESQML2 organizations
	*/
	class AbstractOrganizationInterpretation : public AbstractFeatureInterpretation
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT AbstractOrganizationInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractFeatureInterpretation(partialObject) {}

		/** Default constructor */
		AbstractOrganizationInterpretation() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractOrganizationInterpretation(gsoap_resqml2_0_1::resqml20__AbstractOrganizationInterpretation* fromGsoap) : AbstractFeatureInterpretation(fromGsoap) {}
		AbstractOrganizationInterpretation(gsoap_eml2_3::resqml22__AbstractOrganizationInterpretation* fromGsoap) : AbstractFeatureInterpretation(fromGsoap) {}

	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~AbstractOrganizationInterpretation() {}

		/**
		 * Add a binary contact to the organization interpretation by means of a simple sentence.
		 *
		 * @param 		  	kind			The kind.
		 * @param [in,out]	subject			If non-null, the subject.
		 * @param 		  	verb			The verb.
		 * @param [in,out]	directObject	If non-null, the direct object.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackBinaryContact(AbstractFeatureInterpretation* subject, gsoap_eml2_3::resqml22__ContactVerb verb, AbstractFeatureInterpretation* directObject);

		/**
		 * Add a binary contact to the organization itnerpretation by means of a sentence where the
		 * direct object can be qualified.
		 *
		 * @param 		  	kind				 	The kind.
		 * @param [in,out]	subject				 	If non-null, the subject.
		 * @param 		  	verb				 	The verb.
		 * @param [in,out]	directObject		 	If non-null, the direct object.
		 * @param 		  	directObjectQualifier	The direct object qualifier.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackBinaryContact(AbstractFeatureInterpretation* subject, gsoap_eml2_3::resqml22__ContactVerb verb, AbstractFeatureInterpretation* directObject,
			gsoap_resqml2_0_1::resqml20__ContactSide directObjectQualifier);

        /**
         * Add a binary contact to the organization interpretation by means of a sentence where both the subject and the direct object can be qualified.
         */
		DLL_IMPORT_OR_EXPORT void pushBackBinaryContact(AbstractFeatureInterpretation* subject, gsoap_resqml2_0_1::resqml20__ContactSide subjectQualifier,
			gsoap_eml2_3::resqml22__ContactVerb verb,
			AbstractFeatureInterpretation* directObject, gsoap_resqml2_0_1::resqml20__ContactSide directObjectQualifier);
	};
}
