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

#include "resqml2/ActivityTemplate.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT ActivityTemplate : public resqml2::ActivityTemplate
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		ActivityTemplate(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : resqml2::ActivityTemplate(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param soapContext	The soap context where the underlying gsoap proxy is going to be created.
		* @param guid			The guid to set to the boundary horizon. If empty then a new guid will be generated.
		* @param title			A title for the instance to create.
		*/
		ActivityTemplate(soap* soapContext, const std::string & guid, const std::string & title);

		ActivityTemplate(gsoap_resqml2_0_1::_resqml2__ActivityTemplate* fromGsoap) : resqml2::ActivityTemplate(fromGsoap) {}
		virtual ~ActivityTemplate() {}
		
		/**
		* Push back a parameter in the activity template instance.
		* This parameter has an unconstrained type.
		*/
		void pushBackParameter(const std::string title,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const int & maxOccurs);

		/**
		* Push back a parameter in the activity template instance.
		* This parameter must not be of a data object kind.
		*/
		void pushBackParameter(const std::string title,
			const gsoap_resqml2_0_1::resqml2__ParameterKind & kind,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const int & maxOccurs);

		/**
		* Push back a parameter in the activity template instance.
		* This parameter must be of a data object kind.
		* @param resqmlObjectContentType	If empty, there is no constraint on the content type of this parameter.
		*/
		void pushBackParameter(const std::string title,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const int & maxOccurs,
			const std::string & resqmlObjectContentType);

		/**
		* Check if the instance contains a parameter with a particular title
		* @param paramTitle	The title of the parameter we are looking for into the instance
		*/
		bool isAnExistingParameter(const std::string & paramTitle) const;

		const unsigned int getParameterCount() const;
		const std::string & getParameterTitle(const unsigned int & index) const;
		const std::vector<gsoap_resqml2_0_1::resqml2__ParameterKind> & getParameterAllowedKinds(const unsigned int & index) const;
		const std::vector<gsoap_resqml2_0_1::resqml2__ParameterKind> & getParameterAllowedKinds(const std::string & paramTitle) const;
		const bool & getParameterIsInput(const unsigned int & index) const;
		const bool & getParameterIsInput(const std::string & paramTitle) const;
		const bool & getParameterIsOutput(const unsigned int & index) const;
		const bool & getParameterIsOutput(const std::string & paramTitle) const;
		const LONG64 getParameterMinOccurences(const unsigned int & index) const;
		const LONG64 getParameterMinOccurences(const std::string & paramTitle) const;
		const LONG64 getParameterMaxOccurences(const unsigned int & index) const;
		const LONG64 getParameterMaxOccurences(const std::string & paramTitle) const;

		const std::vector<Activity*> & getActivityInstanceSet() const { return activityInstanceSet; }

		//******************************************************************
		//******************** MANDATORY FOR GsoapWrapper ******************
		//******************************************************************
		
		std::string getResqmlVersion() const;

		static const char* XML_TAG;
		std::string getXmlTag() const {return XML_TAG;}


	private:
		std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(common::EpcDocument * epcDoc) {}

		gsoap_resqml2_0_1::resqml2__ParameterTemplate* getParameterFromTitle(const std::string & paramTitle) const;
		
        std::vector<Activity*> activityInstanceSet;
	};
}

