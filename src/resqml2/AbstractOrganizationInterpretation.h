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

	/** @brief	This class defines the behaviour of all RESQML2 organizations */
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
		virtual ~AbstractOrganizationInterpretation() = default;

		/**
		 * Adds a binary contact to this organization interpretation by means of a simple sentence.
		 *
		 * @exception	std::invalid_argument	If @p subject or @p directObject is @c nullptr.
		 *
		 * @param [in]	subject			The subject of the sentence that defines how the contact was
		 * 								constructed.
		 * @param 	  	verb			The verb of the sentence that defines how the contact was
		 * 								constructed.
		 * @param [in]	directObject	The direct object of the sentence that defines how the contact
		 * 								was constructed.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackBinaryContact(AbstractFeatureInterpretation* subject, gsoap_eml2_3::resqml22__ContactVerb verb, AbstractFeatureInterpretation* directObject);

		/**
		 * Adds a binary contact to this organization interpretation by means of a simple sentence.
		 *
		 * @exception	std::invalid_argument	If @p subject or @p directObject is @c nullptr.
		 *
		 * @param [in]	subject			The subject of the sentence that defines how the contact was
		 * 								constructed.
		 * @param 	  	verb			The verb of the sentence that defines how the contact was
		 * 								constructed.
		 * @param [in]	directObject	The direct object of the sentence that defines how the contact
		 * 								was constructed.
		 * @param [in]	partOf			indicates the interpertation this contact is part of
		 */
		DLL_IMPORT_OR_EXPORT void pushBackBinaryContact(AbstractFeatureInterpretation* subject, gsoap_eml2_3::resqml22__ContactVerb verb, AbstractFeatureInterpretation* directObject, AbstractFeatureInterpretation* partOf);

		/**
		 * Adds a binary contact to the organization interpretation by means of a sentence where the
		 * direct object can be qualified.
		 *
		 * @exception	std::invalid_argument	If @p subject or @p directObject is @c nullptr.
		 *
		 * @param [in]	subject				 	The subject of the sentence that defines how the contact
		 * 										was constructed.
		 * @param 	  	verb				 	The verb of the sentence that defines how the contact was
		 * 										constructed.
		 * @param [in]	directObject		 	The direct object of the sentence that defines how the
		 * 										contact was constructed.
		 * @param 	  	directObjectQualifier	The direct object qualifier defining its contact side
		 * 										(footwall, hanging wall, north, south, etc.).
		 */
		DLL_IMPORT_OR_EXPORT void pushBackBinaryContact(AbstractFeatureInterpretation* subject, gsoap_eml2_3::resqml22__ContactVerb verb, AbstractFeatureInterpretation* directObject,
			gsoap_resqml2_0_1::resqml20__ContactSide directObjectQualifier);

		/**
		 * Adds a binary contact to the organization interpretation by means of a sentence where both
		 * the subject and the direct object can be qualified.
		 *
		 * @exception	std::invalid_argument	If @p subject or @p directObject is @c nullptr.
		 *
		 * @param [in]	subject				 	The subject of the sentence that defines how the contact
		 * 										was constructed.
		 * @param 	  	subjectQualifier	 	The subject qualifier defining its contact side (footwall,
		 * 										hanging wall, north, south, etc.).
		 * @param 	  	verb				 	The verb of the sentence that defines how the contact was
		 * 										constructed.
		 * @param [in]	directObject		 	The direct object of the sentence that defines how the
		 * 										contact was constructed.
		 * @param 	  	directObjectQualifier	The direct object qualifier defining its contact side
		 * 										(footwall, hanging wall, north, south, etc.).
		 */
		DLL_IMPORT_OR_EXPORT void pushBackBinaryContact(AbstractFeatureInterpretation* subject, gsoap_resqml2_0_1::resqml20__ContactSide subjectQualifier,
			gsoap_eml2_3::resqml22__ContactVerb verb,
			AbstractFeatureInterpretation* directObject, gsoap_resqml2_0_1::resqml20__ContactSide directObjectQualifier);
	};
}
