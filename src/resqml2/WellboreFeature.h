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

#include "AbstractTechnicalFeature.h"

namespace WITSML2_0_NS
{
	class Wellbore;
}

namespace RESQML2_NS
{
	class WellboreFeature : public AbstractTechnicalFeature
	{
	public:

		WellboreFeature() {}

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT WellboreFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractTechnicalFeature(partialObject) {}
		
		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreFeature(gsoap_resqml2_0_1::_resqml20__WellboreFeature* fromGsoap): AbstractTechnicalFeature(fromGsoap) {}
		WellboreFeature(gsoap_eml2_3::_resqml22__WellboreFeature* fromGsoap) : AbstractTechnicalFeature(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~WellboreFeature() {}
		
		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Wellbore* getWitsmlWellbore() const;
		DLL_IMPORT_OR_EXPORT virtual void setWitsmlWellbore(WITSML2_0_NS::Wellbore * wellbore) = 0;

		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		* Get the standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }
	};
}