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

#include "../resqml2/Activity.h"

namespace RESQML2_NS
{
	class ActivityTemplate;
}

namespace RESQML2_0_1_NS
{
	class Activity : public RESQML2_NS::Activity
	{
	protected:
		Activity() : RESQML2_NS::Activity() {}

		void loadTargetRelationships();

	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT Activity(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::Activity(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param guid		The guid to set to the boundary horizon. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		*/
		Activity(RESQML2_NS::ActivityTemplate* activityTemplate, const std::string & guid, const std::string & title);

		Activity(gsoap_resqml2_0_1::_resqml20__Activity* fromGsoap) : RESQML2_NS::Activity(fromGsoap) {}
		virtual ~Activity() {}

		/**
		* Push back a double parameter in the instance.
		* This parameter must exist in the associated activity template.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackParameter(const std::string title,
			const double & value, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom = gsoap_resqml2_0_1::resqml20__ResqmlUom__Euc);

		/**
		* Push back a string parameter in the instance.
		* This parameter must exist in the associated activity template.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackParameter(const std::string title,
			const std::string & value);

		/**
		* Push back an integer parameter in the instance.
		* This parameter must exist in the associated activity template.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackParameter(const std::string title,
			const LONG64 & value);

		/**
		* Push back a resqml object parameter in the instance.
		* This parameter must exist in the associated activity template.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackParameter(const std::string title,
			AbstractObject* resqmlObject);
		
		/**
		* Get the count of all the parameters
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getParameterCount() const;

		/**
		* Get the count of all the parameters which have got the same title.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getParameterCount(const std::string & paramTitle) const;
		DLL_IMPORT_OR_EXPORT const std::string & getParameterTitle(const unsigned int & index) const;
		DLL_IMPORT_OR_EXPORT std::vector<unsigned int> getParameterIndexOfTitle(const std::string & paramTitle) const;

		DLL_IMPORT_OR_EXPORT bool isAFloatingPointQuantityParameter(const std::string & paramTitle) const;
		DLL_IMPORT_OR_EXPORT bool isAFloatingPointQuantityParameter(const unsigned int & index) const;
		DLL_IMPORT_OR_EXPORT std::vector<double> getFloatingPointQuantityParameterValue(const std::string & paramTitle) const;
		DLL_IMPORT_OR_EXPORT double getFloatingPointQuantityParameterValue(const unsigned int & index) const;
		DLL_IMPORT_OR_EXPORT std::vector<gsoap_resqml2_0_1::resqml20__ResqmlUom> getFloatingPointQuantityParameterUom(const std::string & paramTitle) const;
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__ResqmlUom getFloatingPointQuantityParameterUom(const unsigned int & index) const;

		DLL_IMPORT_OR_EXPORT bool isAnIntegerQuantityParameter(const std::string & paramTitle) const;
		DLL_IMPORT_OR_EXPORT bool isAnIntegerQuantityParameter(const unsigned int & index) const;
		DLL_IMPORT_OR_EXPORT std::vector<LONG64> getIntegerQuantityParameterValue(const std::string & paramTitle) const;
		DLL_IMPORT_OR_EXPORT LONG64 getIntegerQuantityParameterValue(const unsigned int & index) const;

		DLL_IMPORT_OR_EXPORT bool isAStringParameter(const std::string & paramTitle) const;
		DLL_IMPORT_OR_EXPORT bool isAStringParameter(const unsigned int & index) const;
		DLL_IMPORT_OR_EXPORT std::vector<std::string> getStringParameterValue(const std::string & paramTitle) const;
		DLL_IMPORT_OR_EXPORT const std::string & getStringParameterValue(const unsigned int & index) const;

		DLL_IMPORT_OR_EXPORT bool isAResqmlObjectParameter(const std::string & paramTitle) const;
		DLL_IMPORT_OR_EXPORT bool isAResqmlObjectParameter(const unsigned int & index) const;
		DLL_IMPORT_OR_EXPORT std::vector<AbstractObject*> getResqmlObjectParameterValue(const std::string & paramTitle) const;
		DLL_IMPORT_OR_EXPORT AbstractObject* getResqmlObjectParameterValue(const unsigned int & index) const;

		/**
		* Set the activity template of the activity
		**/
		DLL_IMPORT_OR_EXPORT void setActivityTemplate(RESQML2_NS::ActivityTemplate* activityTemplate);

		COMMON_NS::DataObjectReference getActivityTemplateDor() const;

		DLL_IMPORT_OR_EXPORT std::string getXmlNamespaceVersion() const;

	private:
		std::vector<gsoap_resqml2_0_1::resqml20__AbstractActivityParameter*> getParameterFromTitle(const std::string & paramTitle) const;
	};
}
