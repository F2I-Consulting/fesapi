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

#include "ChannelMetaDataObject.h"

namespace WITSML2_0_NS
{
	/**
	* Primarily a container for one or more channel sets (ChannelSet).
	*/
	class Log : public ChannelMetaDataObject<gsoap_eml2_1::witsml20__Log>
	{
	public:
		/**
		* Constructor for partial transfer
		*/
		DLL_IMPORT_OR_EXPORT Log(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : ChannelMetaDataObject(partialObject) {}

		Log(class Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title);
	
		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		Log(gsoap_eml2_1::witsml20__Log* fromGsoap) : ChannelMetaDataObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~Log() {}

		DLL_IMPORT_OR_EXPORT void pushBackChannelSet(class ChannelSet * channelSet);

		DLL_IMPORT_OR_EXPORT std::vector<class ChannelSet*> getChannelSets() const;

#define SETTER_GENERIC_OPTIONAL_ATTRIBUTE(attributeDatatype, attributeName)\
		DLL_IMPORT_OR_EXPORT void set##attributeName(const attributeDatatype & attributeName);

		SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, TimeDepth)
		SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, RunNumber)
		SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, PassNumber)
		SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, LoggingCompanyName)
		SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, LoggingCompanyCode)
		SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, ToolName)
		SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, ToolClass)

		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		* Get the standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

		void loadTargetRelationships();
	};
}
