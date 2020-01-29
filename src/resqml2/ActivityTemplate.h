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
	/** An activity template. */
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
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT ActivityTemplate(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/** Destructor */
		virtual ~ActivityTemplate() {}

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
		DLL_IMPORT_OR_EXPORT virtual void pushBackParameter(const std::string & title,
			bool isInput, bool isOutput,
			unsigned int minOccurs, int maxOccurs) = 0;

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
		DLL_IMPORT_OR_EXPORT virtual void pushBackParameter(const std::string & title,
			bool isInput, bool isOutput,
			unsigned int minOccurs, int maxOccurs,
			std::string resqmlObjectContentType) = 0;

		/**
		 * Check if the instance contains a parameter with a particular title
		 *
		 * @param 	paramTitle	The title of the parameter we are looking for into the instance.
		 *
		 * @returns	True if an existing parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAnExistingParameter(const std::string & paramTitle) const = 0;

		/**
		 * Gets parameter count
		 *
		 * @returns	The parameter count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getParameterCount() const = 0;

		/**
		 * Gets parameter title
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The parameter title.
		 */
		DLL_IMPORT_OR_EXPORT virtual const std::string & getParameterTitle(const unsigned int & index) const = 0;

		/**
		 * Gets parameter is input
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The parameter is input.
		 */
		DLL_IMPORT_OR_EXPORT virtual const bool & getParameterIsInput(const unsigned int & index) const = 0;

		/**
		 * Gets parameter is input
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The parameter is input.
		 */
		DLL_IMPORT_OR_EXPORT virtual const bool & getParameterIsInput(const std::string & paramTitle) const = 0;

		/**
		 * Gets parameter is output
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The parameter is output.
		 */
		DLL_IMPORT_OR_EXPORT virtual const bool & getParameterIsOutput(const unsigned int & index) const = 0;

		/**
		 * Gets parameter is output
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The parameter is output.
		 */
		DLL_IMPORT_OR_EXPORT virtual const bool & getParameterIsOutput(const std::string & paramTitle) const = 0;

		/**
		 * Gets parameter minimum occurences
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The parameter minimum occurences.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getParameterMinOccurences(const unsigned int & index) const = 0;

		/**
		 * Gets parameter minimum occurences
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The parameter minimum occurences.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getParameterMinOccurences(const std::string & paramTitle) const = 0;

		/**
		 * Gets parameter maximum occurences
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The parameter maximum occurences.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getParameterMaxOccurences(const unsigned int & index) const = 0;

		/**
		 * Gets parameter maximum occurences
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The parameter maximum occurences.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getParameterMaxOccurences(const std::string & paramTitle) const = 0;

		/**
		 * Gets activity instance set
		 *
		 * @returns	Null if it fails, else the activity instance set.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<Activity *> getActivityInstanceSet() const;

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

	private:
		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
