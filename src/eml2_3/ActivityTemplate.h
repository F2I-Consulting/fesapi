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

#include "../eml2/ActivityTemplate.h"

namespace EML2_3_NS
{
	/** An activity template. */
	class ActivityTemplate final : public EML2_NS::ActivityTemplate
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT ActivityTemplate(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : EML2_NS::ActivityTemplate(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	repo 	The repository where the underlying gsoap proxy is going to be
		 * 							created.
		 * @param 		  	guid 	The guid to set to the boundary horizon. If empty then a new guid
		 * 							will be generated.
		 * @param 		  	title	A title for the instance to create.
		 */
		ActivityTemplate(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title);

		/**
		 * Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		ActivityTemplate(gsoap_eml2_3::_eml23__ActivityTemplate* fromGsoap) : EML2_NS::ActivityTemplate(fromGsoap) {}

		/** Destructor */
		~ActivityTemplate() = default;

		/**
		 * Push back a parameter in the activity template instance. This parameter has an unconstrained
		 * type.
		 *
		 * @param 	title	 	The title.
		 * @param 	isInput  	True if is input, false if not.
		 * @param 	isOutput 	True if is output, false if not.
		 * @param 	minOccurs	The minimum occurs.
		 * @param 	maxOccurs	The maximum occurs.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackParameter(const std::string & title,
			bool isInput, bool isOutput,
			unsigned int minOccurs, int maxOccurs);

		/**
		 * Push back a parameter in the activity template instance. This parameter must not be of a data
		 * object kind.
		 *
		 * @param 	title	 	The title.
		 * @param 	kind	 	The kind.
		 * @param 	isInput  	True if is input, false if not.
		 * @param 	isOutput 	True if is output, false if not.
		 * @param 	minOccurs	The minimum occurs.
		 * @param 	maxOccurs	The maximum occurs.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackParameter(const std::string & title,
			gsoap_resqml2_0_1::resqml20__ParameterKind kind,
			bool isInput, bool isOutput,
			unsigned int minOccurs, int maxOccurs);

		/**
		 * Push back a parameter in the activity template instance. This parameter must be of a data
		 * object kind.
		 *
		 * @param 	title				   	The title.
		 * @param 	isInput				   	True if is input, false if not.
		 * @param 	isOutput			   	True if is output, false if not.
		 * @param 	minOccurs			   	The minimum occurs.
		 * @param 	maxOccurs			   	The maximum occurs.
		 * @param 	resqmlObjectContentType	If empty, there is no constraint on the content type of this
		 * 									parameter.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackParameter(const std::string & title,
			bool isInput, bool isOutput,
			unsigned int minOccurs, int maxOccurs,
			std::string resqmlObjectContentType);

		/**
		 * Check if the instance contains a parameter with a particular title
		 *
		 * @param 	paramTitle	The title of the parameter we are looking for into the instance.
		 *
		 * @returns	True if an existing parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAnExistingParameter(const std::string & paramTitle) const;

		/**
		 * Gets parameter count
		 *
		 * @returns	The parameter count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getParameterCount() const;

		/**
		 * Gets parameter title
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The parameter title.
		 */
		DLL_IMPORT_OR_EXPORT const std::string & getParameterTitle(unsigned int index) const;

		/**
		 * Gets parameter allowed kinds
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The parameter allowed kinds.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<gsoap_resqml2_0_1::resqml20__ParameterKind> getParameterAllowedKinds(unsigned int index) const;

		/**
		 * Gets parameter allowed kinds
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The parameter allowed kinds.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<gsoap_resqml2_0_1::resqml20__ParameterKind> getParameterAllowedKinds(const std::string & paramTitle) const;

		/**
		 * Gets parameter is input
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The parameter is input.
		 */
		DLL_IMPORT_OR_EXPORT bool getParameterIsInput(unsigned int index) const;

		/**
		 * Gets parameter is input
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The parameter is input.
		 */
		DLL_IMPORT_OR_EXPORT bool getParameterIsInput(const std::string & paramTitle) const;

		/**
		 * Gets parameter is output
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The parameter is output.
		 */
		DLL_IMPORT_OR_EXPORT bool getParameterIsOutput(unsigned int index) const;

		/**
		 * Gets parameter is output
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The parameter is output.
		 */
		DLL_IMPORT_OR_EXPORT bool getParameterIsOutput(const std::string & paramTitle) const;

		/**
		 * Gets parameter minimum occurences
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The parameter minimum occurences.
		 */
		DLL_IMPORT_OR_EXPORT int64_t getParameterMinOccurences(unsigned int index) const;

		/**
		 * Gets parameter minimum occurences
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The parameter minimum occurences.
		 */
		DLL_IMPORT_OR_EXPORT int64_t getParameterMinOccurences(const std::string & paramTitle) const;

		/**
		 * Gets parameter maximum occurences
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The parameter maximum occurences.
		 */
		DLL_IMPORT_OR_EXPORT int64_t getParameterMaxOccurences(unsigned int index) const;

		/**
		 * Gets parameter maximum occurences
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The parameter maximum occurences.
		 */
		DLL_IMPORT_OR_EXPORT int64_t getParameterMaxOccurences(const std::string & paramTitle) const;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "eml23";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

	private:

		/**
		 * Gets parameter from title
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	Null if it fails, else the parameter from title.
		 */
		gsoap_eml2_3::eml23__ParameterTemplate* getParameterFromTitle(const std::string & paramTitle) const;
	};
}
