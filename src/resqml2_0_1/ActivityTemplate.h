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

namespace RESQML2_0_1_NS
{
	class ActivityTemplate : public RESQML2_NS::ActivityTemplate
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		ActivityTemplate(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::ActivityTemplate(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param repo			The repository where the underlying gsoap proxy is going to be created.
		* @param guid			The guid to set to the boundary horizon. If empty then a new guid will be generated.
		* @param title			A title for the instance to create.
		*/
		ActivityTemplate(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title);

		ActivityTemplate(gsoap_resqml2_0_1::_resqml20__ActivityTemplate* fromGsoap) : RESQML2_NS::ActivityTemplate(fromGsoap) {}
		virtual ~ActivityTemplate() {}
		
		/**
		* Push back a parameter in the activity template instance.
		* This parameter has an unconstrained type.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackParameter(const std::string & title,
			bool isInput, bool isOutput,
			unsigned int minOccurs, int maxOccurs);

		/**
		* Push back a parameter in the activity template instance.
		* This parameter must not be of a data object kind.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackParameter(const std::string & title,
			gsoap_resqml2_0_1::resqml20__ParameterKind kind,
			bool isInput, bool isOutput,
			unsigned int minOccurs, int maxOccurs);

		/**
		* Push back a parameter in the activity template instance.
		* This parameter must be of a data object kind.
		* @param resqmlObjectContentType	If empty, there is no constraint on the content type of this parameter.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackParameter(const std::string & title,
			bool isInput, bool isOutput,
			unsigned int minOccurs, int maxOccurs,
			std::string resqmlObjectContentType);

		/**
		* Check if the instance contains a parameter with a particular title
		* @param paramTitle	The title of the parameter we are looking for into the instance
		*/
		DLL_IMPORT_OR_EXPORT bool isAnExistingParameter(const std::string & paramTitle) const;

		DLL_IMPORT_OR_EXPORT unsigned int getParameterCount() const;
		DLL_IMPORT_OR_EXPORT const std::string & getParameterTitle(const unsigned int & index) const;
		DLL_IMPORT_OR_EXPORT const std::vector<gsoap_resqml2_0_1::resqml20__ParameterKind> & getParameterAllowedKinds(const unsigned int & index) const;
		DLL_IMPORT_OR_EXPORT const std::vector<gsoap_resqml2_0_1::resqml20__ParameterKind> & getParameterAllowedKinds(const std::string & paramTitle) const;
		DLL_IMPORT_OR_EXPORT const bool & getParameterIsInput(const unsigned int & index) const;
		DLL_IMPORT_OR_EXPORT const bool & getParameterIsInput(const std::string & paramTitle) const;
		DLL_IMPORT_OR_EXPORT const bool & getParameterIsOutput(const unsigned int & index) const;
		DLL_IMPORT_OR_EXPORT const bool & getParameterIsOutput(const std::string & paramTitle) const;
		DLL_IMPORT_OR_EXPORT LONG64 getParameterMinOccurences(const unsigned int & index) const;
		DLL_IMPORT_OR_EXPORT LONG64 getParameterMinOccurences(const std::string & paramTitle) const;
		DLL_IMPORT_OR_EXPORT LONG64 getParameterMaxOccurences(const unsigned int & index) const;
		DLL_IMPORT_OR_EXPORT LONG64 getParameterMaxOccurences(const std::string & paramTitle) const;

		//******************************************************************
		//******************** MANDATORY FOR GsoapWrapper ******************
		//******************************************************************
		
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespaceVersion() const;

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const {return XML_TAG;}

	private:
		gsoap_resqml2_0_1::resqml20__ParameterTemplate* getParameterFromTitle(const std::string & paramTitle) const;
	};
}
