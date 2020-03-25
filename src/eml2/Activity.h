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

#include "../common/AbstractObject.h"

/** . */
namespace EML2_NS
{
	class ActivityTemplate;

	/** Proxy class for an activity. */
	class Activity : public COMMON_NS::AbstractObject
	{
	protected:
		/** Default constructor */
		Activity() : COMMON_NS::AbstractObject() {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		Activity(gsoap_resqml2_0_1::_resqml20__Activity* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		Activity(gsoap_eml2_3::_eml23__Activity* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT Activity(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~Activity() {}

		/**
		 * Pushes back a string parameter in this instance. This parameter must exist in the associated
		 * activity template.
		 *
		 * @exception	std::invalid_argument	If the parameter @p title does not exist in the
		 * 										associated activity template.
		 * @exception	std::invalid_argument	If the maximum number of occurrences has already been
		 * 										reached for parameter @p title.
		 * @exception	std::invalid_argument	If The parameter template @p title does not allow a
		 * 										string datatype.
		 *
		 * @param 	title	The title of the parameter to push back.
		 * @param 	value	The value of the parameter to push back.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackParameter(const std::string title,
			const std::string & value) = 0;

		/**
		 * Pushes back an integer parameter in this instance. This parameter must exist in the associated
		 * activity template.
		 *
		 * @exception	std::invalid_argument	If the parameter @p title does not exist in the
		 * 										associated activity template.
		 * @exception	std::invalid_argument	If the maximum number of occurrences has already been
		 * 										reached for parameter @p title.
		 * @exception	std::invalid_argument	If The parameter template @p title does not allow a
		 * 										an integer datatype.
		 *
		 * @param 	title	The title of the parameter to push back.
		 * @param 	value	The value of the parameter to push back.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackParameter(const std::string title,
			LONG64 value) = 0;

		/**
		 * Pushes back a RESQML object parameter in this instance. This parameter must exist in the
		 * associated activity template.
		 *
		 * @exception	std::invalid_argument	If @p resqmlObject is null.
		 * 										* @exception	std::invalid_argument	If the parameter @p
		 * 										title does not exist in the
		 * 											associated activity template.
		 * @exception	std::invalid_argument	If the maximum number of occurrences has already been
		 * 										reached for parameter @p title.
		 * @exception	std::invalid_argument	If The parameter template @p title does not allow a a
		 * 										data object datatype.
		 *
		 * @param 	  	title			The title of the parameter to push back.
		 * @param [in]	resqmlObject	The RESQML object, value of the parameter to push back.
		 */
		virtual void pushBackParameter(const std::string title,
			AbstractObject* resqmlObject) = 0;

		/**
		 * Get the count of all the parameters
		 *
		 * @returns	The parameter count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getParameterCount() const = 0;

		/**
		 * Gets the count of all the parameters which have the same title.
		 *
		 * @param 	paramTitle	The title of the parameters we look for.
		 *
		 * @returns	The parameter count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getParameterCount(const std::string & paramTitle) const = 0;

		/**
		 * Gets the title of a given parameter
		 *
		 * @exception	std::out_of_range	If @p index is not in the parameter range.
		 *
		 * @param 	index	Zero-based index of the parameter for which we look for the title.
		 *
		 * @returns	The parameter title.
		 */
		DLL_IMPORT_OR_EXPORT virtual const std::string & getParameterTitle(unsigned int index) const = 0;

		/**
		 * Gets the indices of all the parameters sharing a given title.
		 *
		 * @param 	paramTitle	The title of the parameters we look for.
		 *
		 * @returns	A vector of parameter indices.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::vector<unsigned int> getParameterIndexOfTitle(const std::string & paramTitle) const = 0;

		/**
		 * Queries if all of the parameters sharing a given title are floating point quantity parameters.
		 *
		 * @exception	std::invalid_argument	If there exists no @p paramTitle parameter in this
		 * 										activity.
		 *
		 * @param 	paramTitle	The title of the parameters we want to test the datatype.
		 *
		 * @returns	True if all of the @p paramTitle parameters are floating point quantity parameters,
		 * 			false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAFloatingPointQuantityParameter(const std::string & paramTitle) const = 0;

		/**
		 * Queries if a given parameter is a floating point quantity parameter.
		 *
		 * @exception	std::out_of_range	If @p index is not in the parameter range.
		 *
		 * @param 	index	Zero-based index of the parameter we want to test the datatype.
		 *
		 * @returns	True if the parameter at position @p index is a floating point quantity parameter,
		 * 			false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAFloatingPointQuantityParameter(unsigned int index) const = 0;

		/**
		 * Gets the values of all the floating point quantity parameters sharing a given title.
		 *
		 * @exception	std::invalid_argument	If there exists no @p paramTitle parameter in this
		 * 										activity.
		 * @exception	std::invalid_argument	If one @p paramTitle parameter contains some non double
		 * 										values.
		 *
		 * @param 	paramTitle	The title of the floating point parameters we look for the value.
		 *
		 * @returns	A vector of the value of all the @p paramTitle floating point quantity parameters.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::vector<double> getFloatingPointQuantityParameterValue(const std::string & paramTitle) const = 0;

		/**
		 * Gets the floating point quantity value of a given parameter.
		 *
		 * @exception	std::out_of_range	 	If @p index is not in the parameter range.
		 * @exception	std::invalid_argument	If the parameter at @p index is not a floating point
		 * 										quantity parameter.
		 *
		 * @param 	index	Zero-based index of the parameter we look for the value. This index is taken
		 * 					in the set of all parameters of this activity.
		 *
		 * @returns	The floating point quantity value of the parameter at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getFloatingPointQuantityParameterValue(unsigned int index) const = 0;

		/**
		 * Queries if all of the parameters sharing a given title are integer quantity parameters.
		 *
		 * @exception	std::invalid_argument	If there exists no @p paramTitle parameter in this
		 * 										activity.
		 *
		 * @param 	paramTitle	The title of the parameters we want to test the datatype.
		 *
		 * @returns	True if all of the @p paramTitle parameters are integer quantity parameters,
		 * 			false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAnIntegerQuantityParameter(const std::string & paramTitle) const = 0;

		/**
		 * Queries if a given parameter is an integer quantity parameter.
		 *
		 * @exception	std::out_of_range	If @p index is not in the parameter range.
		 *
		 * @param 	index	Zero-based index of the parameter we want to test the datatype.
		 *
		 * @returns	True if the parameter at position @p index is an integer quantity parameter,
		 * 			false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAnIntegerQuantityParameter(unsigned int index) const = 0;

		/**
		 * Gets the values of all the integer quantity parameters sharing a given title.
		 *
		 * @exception	std::invalid_argument	If there exists no @p paramTitle parameter in this
		 * 										activity.
		 * @exception	std::invalid_argument	If one @p paramTitle parameter contains some non integer
		 * 										values.
		 *
		 * @param 	paramTitle	The title of the integer parameters we look for the value.
		 *
		 * @returns	A vector of the value of all the @p paramTitle integer quantity parameters.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::vector<LONG64> getIntegerQuantityParameterValue(const std::string & paramTitle) const = 0;

		/**
		 * Gets the integer quantity value of a given parameter.
		 *
		 * @exception	std::out_of_range	 	If @p index is not in the parameter range.
		 * @exception	std::invalid_argument	If the parameter at @p index is not an integer quantity
		 * 										parameter.
		 *
		 * @param 	index	Zero-based index of the parameter we look for the value. This index is taken
		 * 					in the set of all parameters of this activity.
		 *
		 * @returns	The integer quantity value of the parameter at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getIntegerQuantityParameterValue(unsigned int index) const = 0;

		/**
		 * Queries if all of the parameters sharing a given title are string parameters.
		 *
		 * @exception	std::invalid_argument	If there exists no @p paramTitle parameter in this
		 * 										activity.
		 *
		 * @param 	paramTitle	The title of the parameters we want to test the datatype.
		 *
		 * @returns	True if all of the @p paramTitle parameters are string parameters, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAStringParameter(const std::string & paramTitle) const = 0;

		/**
		 * Queries if a given parameter is a string parameter.
		 *
		 * @exception	std::out_of_range	If @p index is not in the parameter range.
		 *
		 * @param 	index	Zero-based index of the parameter we want to test the datatype.
		 *
		 * @returns	True if the parameter at position @p index is a string parameter,
		 * 			false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAStringParameter(unsigned int index) const = 0;

		/**
		 * Gets the values of all the string parameters sharing a given title.
		 *
		 * @exception	std::invalid_argument	If there exists no @p paramTitle parameter in this
		 * 										activity.
		 * @exception	std::invalid_argument	If one @p paramTitle parameter contains some non string
		 * 										values.
		 *
		 * @param 	paramTitle	The title of the string parameters we look for the value.
		 *
		 * @returns	A vector of the value of all the @p paramTitle string parameters.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::vector<std::string> getStringParameterValue(const std::string & paramTitle) const = 0;

		/**
		 * Gets the string value of a given parameter.
		 *
		 * @exception	std::out_of_range	 	If @p index is not in the parameter range.
		 * @exception	std::invalid_argument	If the parameter at @p index is not an string parameter.
		 *
		 * @param 	index	Zero-based index of the parameter we look for the value. This index is taken
		 * 					in the set of all parameters of this activity.
		 *
		 * @returns	The string value of the parameter at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual const std::string & getStringParameterValue(unsigned int index) const = 0;

		/**
		 * Queries if all of the parameters sharing a given title are RESQML object parameters.
		 *
		 * @exception	std::invalid_argument	If there exists no @p paramTitle parameter in this
		 * 										activity.
		 *
		 * @param 	paramTitle	The title of the parameters we want to test the datatype.
		 *
		 * @returns	True if all of the @p paramTitle parameters are RESQML object parameters, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAResqmlObjectParameter(const std::string & paramTitle) const = 0;

		/**
		 * Queries if a given parameter is a RESQML object parameter.
		 *
		 * @exception	std::out_of_range	If @p index is not in the parameter range.
		 *
		 * @param 	index	Zero-based index of the parameter we want to test the datatype.
		 *
		 * @returns	True if the parameter at position @p index is a RESQML object parameter,
		 * 			false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAResqmlObjectParameter(unsigned int index) const = 0;

		/**
		 * Gets the values of all the RESQML object parameters sharing a given title.
		 *
		 * @exception	std::invalid_argument	If there exists no @p paramTitle parameter in this
		 * 										activity.
		 * @exception	std::invalid_argument	If one @p paramTitle parameter contains some non RESQML object
		 * 										values.
		 *
		 * @param 	paramTitle	The title of the RESQML object parameters we look for the value.
		 *
		 * @returns	A vector of the value of all the @p paramTitle RESQML object parameters.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::vector<AbstractObject*> getResqmlObjectParameterValue(const std::string & paramTitle) const = 0;

		/**
		 * Gets the RESQML object value of a given parameter.
		 *
		 * @exception	std::out_of_range	 	If @p index is not in the parameter range.
		 * @exception	std::invalid_argument	If the parameter at @p index is not an RESQML object
		 * 										parameter.
		 *
		 * @param 	index	Zero-based index of the parameter we look for the value. This index is taken
		 * 					in the set of all parameters of this activity.
		 *
		 * @returns	The RESQML object value of the parameter at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual AbstractObject* getResqmlObjectParameterValue(unsigned int index) const = 0;

		/**
		 * Sets the activity template of this activity.
		 *
		 * @param [in]	activityTemplate	If non-null, the activity template.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setActivityTemplate(ActivityTemplate* activityTemplate) = 0;

		/**
		 * Gets the data object reference of the activity template of this activity.
		 *
		 * @returns	The data object reference of the activity template.
		 */
		virtual COMMON_NS::DataObjectReference getActivityTemplateDor() const = 0;
		
		/** 
		 * Gets the activity template of this activity.
		 * 
		 * @returns The activity template of this activity.
		 */
		DLL_IMPORT_OR_EXPORT ActivityTemplate* getActivityTemplate() const;

		/**
		 * Gets all the RESQML objects which are either input or output of this activity. That is to say
		 * all of the values of the RESQML object parameters of this activity.
		 *
		 * @returns	A vector of pointers to the RESQML objects which are either input or output of this
		 * 			activity.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<AbstractObject*> getResqmlObjectSet() const;

		/** The standard XML tag without XML namespace for serializing this data object */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Gets the standard XML tag without XML namespace for serializing this data object
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

	protected:
		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
