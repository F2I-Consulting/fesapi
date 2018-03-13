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

#include "resqml2_0_1/AbstractTechnicalFeature.h"

namespace RESQML2_0_1_NS
{
	class DLL_IMPORT_OR_EXPORT FrontierFeature : public AbstractTechnicalFeature
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		FrontierFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractTechnicalFeature(partialObject) {}

		/**
		* Creates an instance of this class in an EPC document.
		* @param soapContext The soap context where the underlying gsoap proxy is going to be created.
		* @param guid	A guid for the instance to create.
		* @param title	A title for the instance to create.
		*/
		FrontierFeature(soap* soapContext, const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		FrontierFeature(gsoap_resqml2_0_1::_resqml2__FrontierFeature* fromGsoap): AbstractTechnicalFeature(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~FrontierFeature() {}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}
	};
}

