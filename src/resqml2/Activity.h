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
namespace RESQML2_NS
{
	/** An activity. */
	class Activity : public COMMON_NS::AbstractObject
	{
	protected:
		/** Default constructor */
		Activity() : AbstractObject() {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		Activity(gsoap_resqml2_0_1::_resqml20__Activity* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT Activity(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/** Destructor */
		virtual ~Activity() {}

		/**
		 * Push back a string parameter in the instance. This parameter must exist in the associated
		 * activity template.
		 *
		 * @param 	title	The title.
		 * @param 	value	The value.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackParameter(const std::string title,
			const std::string & value) = 0;

		/**
		 * Push back an integer parameter in the instance. This parameter must exist in the associated
		 * activity template.
		 *
		 * @param 	title	The title.
		 * @param 	value	The value.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackParameter(const std::string title,
			const LONG64 & value) = 0;

		/**
		 * Push back a resqml object parameter in the instance. This parameter must exist in the
		 * associated activity template.
		 *
		 * @param 		  	title			The title.
		 * @param [in,out]	resqmlObject	If non-null, the resqml object.
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
		 * Get the count of all the parameters which have got the same title.
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The parameter count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getParameterCount(const std::string & paramTitle) const = 0;

		/**
		 * Gets parameter title
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The parameter title.
		 */
		DLL_IMPORT_OR_EXPORT virtual const std::string & getParameterTitle(const unsigned int & index) const = 0;

		/**
		 * Gets parameter index of title
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The parameter index of title.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::vector<unsigned int> getParameterIndexOfTitle(const std::string & paramTitle) const = 0;

		/**
		 * Query if 'paramTitle' is a floating point quantity parameter
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	True if a floating point quantity parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAFloatingPointQuantityParameter(const std::string & paramTitle) const = 0;

		/**
		 * Query if 'index' is a floating point quantity parameter
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if a floating point quantity parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAFloatingPointQuantityParameter(const unsigned int & index) const = 0;

		/**
		 * Gets floating point quantity parameter value
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The floating point quantity parameter value.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::vector<double> getFloatingPointQuantityParameterValue(const std::string & paramTitle) const = 0;

		/**
		 * Gets floating point quantity parameter value
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The floating point quantity parameter value.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getFloatingPointQuantityParameterValue(const unsigned int & index) const = 0;

		/**
		 * Query if 'paramTitle' is an integer quantity parameter
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	True if an integer quantity parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAnIntegerQuantityParameter(const std::string & paramTitle) const = 0;

		/**
		 * Query if 'index' is an integer quantity parameter
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if an integer quantity parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAnIntegerQuantityParameter(const unsigned int & index) const = 0;

		/**
		 * Gets integer quantity parameter value
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The integer quantity parameter value.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::vector<LONG64> getIntegerQuantityParameterValue(const std::string & paramTitle) const = 0;

		/**
		 * Gets integer quantity parameter value
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The integer quantity parameter value.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getIntegerQuantityParameterValue(const unsigned int & index) const = 0;

		/**
		 * Query if 'paramTitle' is a string parameter
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	True if a string parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAStringParameter(const std::string & paramTitle) const = 0;

		/**
		 * Query if 'index' is a string parameter
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if a string parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAStringParameter(const unsigned int & index) const = 0;

		/**
		 * Gets string parameter value
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	The string parameter value.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::vector<std::string> getStringParameterValue(const std::string & paramTitle) const = 0;

		/**
		 * Gets string parameter value
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The string parameter value.
		 */
		DLL_IMPORT_OR_EXPORT virtual const std::string & getStringParameterValue(const unsigned int & index) const = 0;

		/**
		 * Query if 'paramTitle' is a resqml object parameter
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	True if a resqml object parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAResqmlObjectParameter(const std::string & paramTitle) const = 0;

		/**
		 * Query if 'index' is a resqml object parameter
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if a resqml object parameter, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAResqmlObjectParameter(const unsigned int & index) const = 0;

		/**
		 * Gets resqml object parameter value
		 *
		 * @param 	paramTitle	The parameter title.
		 *
		 * @returns	Null if it fails, else the resqml object parameter value.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::vector<AbstractObject*> getResqmlObjectParameterValue(const std::string & paramTitle) const = 0;

		/**
		 * Gets resqml object parameter value
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	Null if it fails, else the resqml object parameter value.
		 */
		DLL_IMPORT_OR_EXPORT virtual AbstractObject* getResqmlObjectParameterValue(const unsigned int & index) const = 0;

		/**
		 * Set the activity template of the activity
		 *
		 * @param [in,out]	activityTemplate	If non-null, the activity template.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setActivityTemplate(class ActivityTemplate* activityTemplate) = 0;

		/**
		 * Get the activity template dor of the activity
		 *
		 * @returns	Null if it fails, else the activity template dor.
		 */
		virtual gsoap_resqml2_0_1::eml20__DataObjectReference* getActivityTemplateDor() const = 0;
		
		/** Get the activity template of the activity */
		DLL_IMPORT_OR_EXPORT class ActivityTemplate* getActivityTemplate() const;

		/**
		 * Get all objects which are either input or output of this acitivty
		 *
		 * @returns	Null if it fails, else the resqml object set.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<AbstractObject*> getResqmlObjectSet() const;

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

	protected:
		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
