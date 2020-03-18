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

#include "../resqml2_0_1/Activity.h"

/** . */
namespace RESQML2_NS
{
	/** Proxy class for an activity template. */
	class ActivityTemplate : public COMMON_NS::AbstractObject
	{
	protected:
		/** Default constructor */
		ActivityTemplate() : AbstractObject() {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		ActivityTemplate(gsoap_resqml2_0_1::_resqml20__ActivityTemplate* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT ActivityTemplate(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~ActivityTemplate() {}

		/**
		 * Pushes back a parameter in this activity template instance. This parameter has an
		 * unconstrained type.
		 *
		 * @exception	std::invalid_argument	If @p maxOccurs is strictly lesser than @p minOccurs.
		 *
		 * @param 	title	 	The title of the parameter to push back.
		 * @param 	isInput  	True if the parameter is an input parameter, false if not.
		 * @param 	isOutput 	True if the parameter is an output parameter, false if not.
		 * @param 	minOccurs	The minimum number of occurrences of this parameter.
		 * @param 	maxOccurs	The maximum number of occurrences of this parameter.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackParameter(const std::string & title,
			bool isInput, bool isOutput,
			unsigned int minOccurs, int maxOccurs) = 0;

		/**
		 * Pushes back a parameter in the activity template instance. This parameter must be of a RESQML
		 * object kind.
		 *
		 * @exception	std::invalid_argument	If @p maxOccurs is strictly lesser than @p minOccurs.
		 *
		 * @param 	title				   	The title of the parameter to push back.
		 * @param 	isInput				   	True if the parameter is an input parameter, false if not.
		 * @param 	isOutput			   	True if the parameter is an output parameter, false if not.
		 * @param 	minOccurs			   	The minimum number of occurrences of this parameter.
		 * @param 	maxOccurs			   	The maximum number of occurrences of this parameter.
		 * @param 	resqmlObjectContentType	The content type of the RESQML object kind of the parameter.
		 * 									If empty, there is no constraint on the content type of this
		 * 									parameter.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackParameter(const std::string & title,
			bool isInput, bool isOutput,
			unsigned int minOccurs, int maxOccurs,
			std::string resqmlObjectContentType) = 0;

		/**
		 * Checks if this instance contains a parameter with a particular title.
		 *
		 * @param 	paramTitle	The title of the parameter we are looking for into this instance.
		 *
		 * @returns	True if there exists a @p paramTitle parameter in this instance false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAnExistingParameter(const std::string & paramTitle) const = 0;

		/**
		 * Gets the parameter count.
		 *
		 * @returns	The parameter count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getParameterCount() const = 0;

		/**
		 * Gets the title of a particular parameter.
		 *
		 * @exception	std::out_of_range	If @p index is not in the parameter range.
		 *
		 * @param 	index	Zero-based index of the parameter we look for the title.
		 *
		 * @returns	The title of the parameter at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual const std::string & getParameterTitle(const unsigned int & index) const = 0;

		/**
		 * Queries if a particular parameter is an input parameter.
		 *
		 * @exception	std::out_of_range	If @p index is not in the parameter range.
		 *
		 * @param 	index	Zero-based index of the parameter we want to know if it is an input one.
		 *
		 * @returns	True is the parameter at @p index is an input parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual const bool & getParameterIsInput(const unsigned int & index) const = 0;

		/**
		 * Queries if a particular parameter is an input parameter.
		 *
		 * @exception	std::invalid_argument	If there exists no @p paramTitle parameter in this
		 * 										activity.
		 *
		 * @param 	paramTitle	The title of the parameter we want to know if it is an input one.
		 *
		 * @returns	True is the parameter @p paramTitle is an input parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual const bool & getParameterIsInput(const std::string & paramTitle) const = 0;

		/**
		 * Queries if a particular parameter is an output parameter.
		 *
		 * @exception	std::out_of_range	If @p index is not in the parameter range.
		 *
		 * @param 	index	Zero-based index of the parameter we want to know if it is an output one.
		 *
		 * @returns	True is the parameter at @p index is an output parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual const bool & getParameterIsOutput(const unsigned int & index) const = 0;

		/**
		 * Queries if a particular parameter is an output parameter.
		 *
		 * @exception	std::invalid_argument	If there exists no @p paramTitle parameter in this
		 * 										activity.
		 *
		 * @param 	paramTitle	The title of the parameter we want to know if it is an output one.
		 *
		 * @returns	True is the parameter @p paramTitle is an output parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual const bool & getParameterIsOutput(const std::string & paramTitle) const = 0;

		/**
		 * Gets the minimum occurrences of a particular parameter.
		 *
		 * @exception	std::out_of_range	If @p index is not in the parameter range.
		 *
		 * @param 	index	Zero-based index of the parameter we want to know the minimum occurrences.
		 *
		 * @returns	The parameter minimum occurrences.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getParameterMinOccurences(const unsigned int & index) const = 0;

		/**
		 * Gets the minimum occurrences of a particular parameter.
		 *
		 * @exception	std::invalid_argument	If there exists no @p paramTitle parameter in this
		 * 										activity.
		 *
		 * @param 	paramTitle	The title of the parameter we want to know the minimum occurrences.
		 *
		 * @returns	The parameter minimum occurrences.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getParameterMinOccurences(const std::string & paramTitle) const = 0;

		/**
		 * Gets the maximum occurrences of a particular parameter.
		 *
		 * @exception	std::out_of_range	If @p index is not in the parameter range.
		 *
		 * @param 	index	Zero-based index of the parameter we want to know the maximum occurrences.
		 *
		 * @returns	The parameter maximum occurrences.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getParameterMaxOccurences(const unsigned int & index) const = 0;

		/**
		 * Gets the maximum occurrences of a particular parameter.
		 *
		 * @exception	std::invalid_argument	If there exists no @p paramTitle parameter in this
		 * 										activity.
		 *
		 * @param 	paramTitle	The title of the parameter we want to know the maximum occurrences.
		 *
		 * @returns	The parameter maximum occurrences.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getParameterMaxOccurences(const std::string & paramTitle) const = 0;

		/**
		 * Gets the set of activities which are based on this activity template within the repository.
		 *
		 * @returns	A vector of pointers to all the activities based on this activity template.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<Activity *> getActivityInstanceSet() const;

		/** The standard XML tag without XML namespace for serializing this data object */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Gets the standard XML tag without XML namespace for serializing this data object
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

	private:
		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
