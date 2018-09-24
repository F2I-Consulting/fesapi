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

#include "resqml2/Activity.h"

namespace RESQML2_NS
{
	class DLL_IMPORT_OR_EXPORT ActivityTemplate : public COMMON_NS::AbstractObject
	{
	protected:
		ActivityTemplate() : AbstractObject() {}

		ActivityTemplate(gsoap_resqml2_0_1::_resqml2__ActivityTemplate* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

	public:

		/**
		* Only to be used in partial transfer context
		*/
		ActivityTemplate(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		virtual ~ActivityTemplate() {}
		
		/**
		* Push back a parameter in the activity template instance.
		* This parameter has an unconstrained type.
		*/
		virtual void pushBackParameter(const std::string title,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const int & maxOccurs) = 0;

		/**
		* Push back a parameter in the activity template instance.
		* This parameter must be of a data object kind.
		* @param resqmlObjectContentType	If empty, there is no constraint on the content type of this parameter.
		*/
		virtual void pushBackParameter(const std::string title,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const int & maxOccurs,
			const std::string & resqmlObjectContentType) = 0;

		/**
		* Check if the instance contains a parameter with a particular title
		* @param paramTitle	The title of the parameter we are looking for into the instance
		*/
		virtual bool isAnExistingParameter(const std::string & paramTitle) const = 0;

		virtual const unsigned int getParameterCount() const = 0;
		virtual const std::string & getParameterTitle(const unsigned int & index) const = 0;
		virtual const bool & getParameterIsInput(const unsigned int & index) const = 0;
		virtual const bool & getParameterIsInput(const std::string & paramTitle) const = 0;
		virtual const bool & getParameterIsOutput(const unsigned int & index) const = 0;
		virtual const bool & getParameterIsOutput(const std::string & paramTitle) const = 0;
		virtual const LONG64 getParameterMinOccurences(const unsigned int & index) const = 0;
		virtual const LONG64 getParameterMinOccurences(const std::string & paramTitle) const = 0;
		virtual const LONG64 getParameterMaxOccurences(const unsigned int & index) const = 0;
		virtual const LONG64 getParameterMaxOccurences(const std::string & paramTitle) const = 0;

		const std::vector<Activity*> & getActivityInstanceSet() const { return activityInstanceSet; }

		static const char* XML_TAG;
		std::string getXmlTag() const {return XML_TAG;}

		std::vector<epc::Relationship> getAllSourceRelationships() const;
		std::vector<epc::Relationship> getAllTargetRelationships() const;
		void resolveTargetRelationships(COMMON_NS::EpcDocument * epcDoc) {}

	protected:
		
        std::vector<Activity*> activityInstanceSet;

		friend void RESQML2_NS::Activity::setActivityTemplate(RESQML2_NS::ActivityTemplate* activityTemplate);
	};
}

