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

#include "../resqml2/CulturalFeature.h"

namespace RESQML2_2_NS
{
	/** A frontier feature. */
	class CulturalFeature final : public RESQML2_NS::CulturalFeature
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT CulturalFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::CulturalFeature(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in an EPC document.
		 *
		 * @param [in,out]	repo 	The repo where the underlying gsoap proxy is going to be created.
		 * @param 		  	guid 	A guid for the instance to create.
		 * @param 		  	title	A title for the instance to create.
		 * @param 		  	kind 	The kind.
		 */
		CulturalFeature(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			gsoap_eml2_3::resqml22__CulturalFeatureKind kind);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		CulturalFeature(gsoap_eml2_3::_resqml22__CulturalFeature* fromGsoap): RESQML2_NS::CulturalFeature(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~CulturalFeature() {}

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
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }
	};
}
