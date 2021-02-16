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

namespace RESQML2_NS
{
	class WellboreFeature;
}

namespace WITSML2_0_NS
{
	class WellCompletion;
}

namespace WITSML2_NS
{
	class Wellbore;

	/** 
	 * @brief	The trajectory object is used to capture information about a directional survey in a wellbore.
	 *			It contains many trajectory stations to capture the information about individual survey points.
	 */
	class Well : public COMMON_NS::AbstractObject
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT Well(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~Well() = default;

		/**
		 * Gets resqml wellbore features
		 *
		 * @returns	Null if it fails, else the resqml wellbore features.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_NS::WellboreFeature *> getResqmlWellboreFeatures() const;

		/**
		 * Gets the wellbores
		 *
		 * @returns	Null if it fails, else the wellbores.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<Wellbore *> getWellbores() const;

		/**
		 * Gets the wellcompletions
		 *
		 * @returns	Null if it fails, else the wellcompletions.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<WITSML2_0_NS::WellCompletion *> getWellcompletions() const;

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static constexpr char* XML_TAG = "Well";

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

		/** A WITSML well points towards no other dataobject */
		void loadTargetRelationships() {}

	protected:

		/** Default constructor does nothing */
		Well() = default;

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		Well(gsoap_eml2_1::witsml20__Well* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		//Well(gsoap_eml2_3::_resqml22__Well* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}
	};
}
