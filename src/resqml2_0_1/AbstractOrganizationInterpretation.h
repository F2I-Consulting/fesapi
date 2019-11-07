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

#include "../resqml2/AbstractFeatureInterpretation.h"

namespace RESQML2_0_1_NS
{
	/**
	* This class defines the behaviour of all Resqml2 organizations
	*/
	class AbstractOrganizationInterpretation : public RESQML2_NS::AbstractFeatureInterpretation
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT AbstractOrganizationInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractFeatureInterpretation(partialObject) {}

		AbstractOrganizationInterpretation() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractOrganizationInterpretation(gsoap_resqml2_0_1::resqml20__AbstractOrganizationInterpretation* fromGsoap) : RESQML2_NS::AbstractFeatureInterpretation(fromGsoap) {}

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractOrganizationInterpretation() {}

		/**
		 * Add a binary contact to the organization interpretation by means of a simple sentence.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackBinaryContact(gsoap_resqml2_0_1::resqml20__ContactRelationship kind, RESQML2_NS::AbstractFeatureInterpretation* subject, gsoap_resqml2_0_1::resqml20__ContactVerb verb, RESQML2_NS::AbstractFeatureInterpretation* directObject);

		/**
		 * Add a binary contact to the organization itnerpretation by means of a sentence where the direct object can be qualified.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackBinaryContact(gsoap_resqml2_0_1::resqml20__ContactRelationship kind, RESQML2_NS::AbstractFeatureInterpretation* subject, gsoap_resqml2_0_1::resqml20__ContactVerb verb, RESQML2_NS::AbstractFeatureInterpretation* directObject,
			gsoap_resqml2_0_1::resqml20__ContactSide directObjectQualifier);

        /**
         * Add a binary contact to the organization interpretation by means of a sentence where both the subject and the direct object can be qualified.
         */
		DLL_IMPORT_OR_EXPORT void pushBackBinaryContact(gsoap_resqml2_0_1::resqml20__ContactRelationship kind, RESQML2_NS::AbstractFeatureInterpretation* subject, gsoap_resqml2_0_1::resqml20__ContactSide subjectQualifier,
			gsoap_resqml2_0_1::resqml20__ContactVerb verb, RESQML2_NS::AbstractFeatureInterpretation* directObject, gsoap_resqml2_0_1::resqml20__ContactSide directObjectQualifier);

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlNamespace() const { return XML_NS; }
	};
}
