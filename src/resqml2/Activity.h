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

#include "common/AbstractObject.h"

namespace RESQML2_NS
{
	class Activity : public COMMON_NS::AbstractObject
	{
	protected:
		Activity() : AbstractObject() {}

		Activity(gsoap_resqml2_0_1::_resqml2__Activity* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

	public:

		/**
		* Only to be used in partial transfer context
		*/
		Activity(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		virtual ~Activity() {}

		/**
		* Push back a string parameter in the instance.
		* This parameter must exist in the associated activity template.
		*/
		DLL_IMPORT_OR_EXPORT virtual void pushBackParameter(const std::string title,
			const std::string & value) = 0;

		/**
		* Push back an integer parameter in the instance.
		* This parameter must exist in the associated activity template.
		*/
		DLL_IMPORT_OR_EXPORT virtual void pushBackParameter(const std::string title,
			const LONG64 & value) = 0;

		/**
		* Push back a resqml object parameter in the instance.
		* This parameter must exist in the associated activity template.
		*/
		virtual void pushBackParameter(const std::string title,
			AbstractObject* resqmlObject) = 0;
		
		/**
		* Get the count of all the parameters
		*/
		DLL_IMPORT_OR_EXPORT virtual unsigned int getParameterCount() const = 0;

		/**
		* Get the count of all the parameters which have got the same title.
		*/
		DLL_IMPORT_OR_EXPORT virtual unsigned int getParameterCount(const std::string & paramTitle) const = 0;
		DLL_IMPORT_OR_EXPORT virtual const std::string & getParameterTitle(const unsigned int & index) const = 0;
		DLL_IMPORT_OR_EXPORT virtual std::vector<unsigned int> getParameterIndexOfTitle(const std::string & paramTitle) const = 0;

		DLL_IMPORT_OR_EXPORT virtual bool isAFloatingPointQuantityParameter(const std::string & paramTitle) const = 0;
		DLL_IMPORT_OR_EXPORT virtual bool isAFloatingPointQuantityParameter(const unsigned int & index) const = 0;
		DLL_IMPORT_OR_EXPORT virtual std::vector<double> getFloatingPointQuantityParameterValue(const std::string & paramTitle) const = 0;
		DLL_IMPORT_OR_EXPORT virtual double getFloatingPointQuantityParameterValue(const unsigned int & index) const = 0;

		DLL_IMPORT_OR_EXPORT virtual bool isAnIntegerQuantityParameter(const std::string & paramTitle) const = 0;
		DLL_IMPORT_OR_EXPORT virtual bool isAnIntegerQuantityParameter(const unsigned int & index) const = 0;
		DLL_IMPORT_OR_EXPORT virtual std::vector<LONG64> getIntegerQuantityParameterValue(const std::string & paramTitle) const = 0;
		DLL_IMPORT_OR_EXPORT virtual LONG64 getIntegerQuantityParameterValue(const unsigned int & index) const = 0;

		DLL_IMPORT_OR_EXPORT virtual bool isAStringParameter(const std::string & paramTitle) const = 0;
		DLL_IMPORT_OR_EXPORT virtual bool isAStringParameter(const unsigned int & index) const = 0;
		DLL_IMPORT_OR_EXPORT virtual std::vector<std::string> getStringParameterValue(const std::string & paramTitle) const = 0;
		DLL_IMPORT_OR_EXPORT virtual const std::string & getStringParameterValue(const unsigned int & index) const = 0;

		DLL_IMPORT_OR_EXPORT virtual bool isAResqmlObjectParameter(const std::string & paramTitle) const = 0;
		DLL_IMPORT_OR_EXPORT virtual bool isAResqmlObjectParameter(const unsigned int & index) const = 0;
		DLL_IMPORT_OR_EXPORT virtual std::vector<AbstractObject*> getResqmlObjectParameterValue(const std::string & paramTitle) const = 0;
		DLL_IMPORT_OR_EXPORT virtual AbstractObject* getResqmlObjectParameterValue(const unsigned int & index) const = 0;

		/**
		* Set the activity template of the activity
		**/
		DLL_IMPORT_OR_EXPORT virtual void setActivityTemplate(class ActivityTemplate* activityTemplate) = 0;

		/**
		* Get the activity template dor of the activity
		**/
		virtual gsoap_resqml2_0_1::eml20__DataObjectReference* getActivityTemplateDor() const = 0;
		
		/**
		* Get the activity template of the activity
		**/
		DLL_IMPORT_OR_EXPORT class ActivityTemplate* getActivityTemplate() const;

		/**
		* Get all objects which are either input or output of this acitivty
		**/
		DLL_IMPORT_OR_EXPORT std::vector<AbstractObject*> getResqmlObjectSet() const;

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const {return XML_TAG;}

	protected:
		std::vector<epc::Relationship> getAllEpcRelationships() const;
	};
}
