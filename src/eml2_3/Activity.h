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

#include "../eml2/Activity.h"

namespace EML2_3_NS
{
	/** An activity. */
	class Activity final : public EML2_NS::Activity
	{
	protected:
		/** Default constructor */
		Activity() : EML2_NS::Activity() {}

		/** Loads target relationships */
		void loadTargetRelationships();

	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT Activity(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : EML2_NS::Activity(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>activityTemplate == nullptr</tt>.
		 *
		 * @param [in]	activityTemplate	If non-null, the activity template.
		 * @param 	  	guid				The guid to set to the boundary horizon. If empty then a new
		 * 									guid will be generated.
		 * @param 	  	title				A title for the instance to create.
		 */
		Activity(EML2_NS::ActivityTemplate* activityTemplate, const std::string & guid, const std::string & title);

		/**
		 * Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		Activity(gsoap_eml2_3::_eml23__Activity* fromGsoap) : EML2_NS::Activity(fromGsoap) {}

		/** Destructor */
		~Activity() {}

		/**
		 * Push back a double parameter in the instance. This parameter must exist in the associated
		 * activity template.
		 *
		 * @param 	title	The title.
		 * @param 	value	The value.
		 * @param 	uom  	(Optional) The uom.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackParameter(const std::string title,
			double value, gsoap_resqml2_0_1::resqml20__ResqmlUom uom = gsoap_resqml2_0_1::resqml20__ResqmlUom__Euc);

		/**
		 * Push back a string parameter in the instance. This parameter must exist in the associated
		 * activity template.
		 *
		 * @param 	title	The title.
		 * @param 	value	The value.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackParameter(const std::string title,
			const std::string & value);

		/**
		 * Push back an integer parameter in the instance. This parameter must exist in the associated
		 * activity template.
		 *
		 * @param 	title	The title.
		 * @param 	value	The value.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackParameter(const std::string title,
			LONG64 value);

		/**
		 * Push back a resqml object parameter in the instance. This parameter must exist in the
		 * associated activity template.
		 *
		 * @param 		  	title			The title.
		 * @param [in,out]	resqmlObject	If non-null, the resqml object.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackParameter(const std::string title,
			AbstractObject* resqmlObject);

		/**
		 * Get the count of all the parameters
		 *
		 * @returns	The parameter count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getParameterCount() const;

		/**
		 * Get the count of all the parameters which have got the same title.
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The parameter count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getParameterCount(const std::string & paramTitle) const;

		/**
		 * Gets parameter title
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The parameter title.
		 */
		DLL_IMPORT_OR_EXPORT const std::string & getParameterTitle(unsigned int index) const;

		/**
		 * Gets parameter index of title
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The parameter index of title.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<unsigned int> getParameterIndexOfTitle(const std::string & paramTitle) const;

		/**
		 * Query if 'paramTitle' is a floating point quantity parameter
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	True if a floating point quantity parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAFloatingPointQuantityParameter(const std::string & paramTitle) const;

		/**
		 * Query if 'index' is a floating point quantity parameter
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if a floating point quantity parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAFloatingPointQuantityParameter(unsigned int index) const;

		/**
		 * Gets floating point quantity parameter value
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The floating point quantity parameter value.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<double> getFloatingPointQuantityParameterValue(const std::string & paramTitle) const;

		/**
		 * Gets floating point quantity parameter value
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The floating point quantity parameter value.
		 */
		DLL_IMPORT_OR_EXPORT double getFloatingPointQuantityParameterValue(unsigned int index) const;

		/**
		 * Gets floating point quantity parameter uom
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The floating point quantity parameter uom.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<gsoap_resqml2_0_1::resqml20__ResqmlUom> getFloatingPointQuantityParameterUom(const std::string & paramTitle) const;

		/**
		 * Gets floating point quantity parameter uom
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The floating point quantity parameter uom.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__ResqmlUom getFloatingPointQuantityParameterUom(unsigned int index) const;

		/**
		 * Query if 'paramTitle' is an integer quantity parameter
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	True if an integer quantity parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAnIntegerQuantityParameter(const std::string & paramTitle) const;

		/**
		 * Query if 'index' is an integer quantity parameter
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if an integer quantity parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAnIntegerQuantityParameter(unsigned int index) const;

		/**
		 * Gets integer quantity parameter value
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The integer quantity parameter value.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<LONG64> getIntegerQuantityParameterValue(const std::string & paramTitle) const;

		/**
		 * Gets integer quantity parameter value
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The integer quantity parameter value.
		 */
		DLL_IMPORT_OR_EXPORT LONG64 getIntegerQuantityParameterValue(unsigned int index) const;

		/**
		 * Query if 'paramTitle' is a string parameter
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	True if a string parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAStringParameter(const std::string & paramTitle) const;

		/**
		 * Query if 'index' is a string parameter
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if a string parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAStringParameter(unsigned int index) const;

		/**
		 * Gets string parameter value
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The string parameter value.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<std::string> getStringParameterValue(const std::string & paramTitle) const;

		/**
		 * Gets string parameter value
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The string parameter value.
		 */
		DLL_IMPORT_OR_EXPORT const std::string & getStringParameterValue(unsigned int index) const;

		/**
		 * Query if 'paramTitle' is a resqml object parameter
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	True if a resqml object parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAResqmlObjectParameter(const std::string & paramTitle) const;

		/**
		 * Query if 'index' is a resqml object parameter
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if a resqml object parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAResqmlObjectParameter(unsigned int index) const;

		/**
		 * Gets resqml object parameter value
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	Null if it fails, else the resqml object parameter value.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<AbstractObject*> getResqmlObjectParameterValue(const std::string & paramTitle) const;

		/**
		 * Gets resqml object parameter value
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	Null if it fails, else the resqml object parameter value.
		 */
		DLL_IMPORT_OR_EXPORT AbstractObject* getResqmlObjectParameterValue(unsigned int index) const;

		/**
		 * Set the activity template of the activity
		 *
		 * @param [in,out]	activityTemplate	If non-null, the activity template.
		 */
		DLL_IMPORT_OR_EXPORT void setActivityTemplate(EML2_NS::ActivityTemplate* activityTemplate);

		/**
		 * Gets activity template dor
		 *
		 * @returns	Empty data object reference if it fails, else the activity template data object reference.
		 */
		COMMON_NS::DataObjectReference getActivityTemplateDor() const;

		/**
		 * Gets XML namespace
		 *
		 * @returns	The XML namespace.
		 */
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const { return "eml23"; }

	private:

		/**
		 * Gets parameter from title
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	Null if it fails, else the parameter from title.
		 */
		std::vector<gsoap_eml2_3::eml23__AbstractActivityParameter*> getParameterFromTitle(const std::string & paramTitle) const;
	};
}
