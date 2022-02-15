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

#include "AbstractFeatureInterpretation.h"

namespace RESQML2_NS
{
	class WellboreFeature;
	class WellboreTrajectoryRepresentation;

	/**
	 * @brief	Contains the data describing an opinion of a borehole.This interpretation is relative
	 * 			to one particular well trajectory.
	 */
	class WellboreInterpretation : public AbstractFeatureInterpretation
	{
	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT WellboreInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			AbstractFeatureInterpretation(partialObject)
		{}

		/** Default constructor */
		WellboreInterpretation() {};

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		WellboreInterpretation(gsoap_resqml2_0_1::_resqml20__WellboreInterpretation* fromGsoap) : AbstractFeatureInterpretation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		WellboreInterpretation(gsoap_eml2_3::_resqml22__WellboreInterpretation* fromGsoap) : AbstractFeatureInterpretation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gSOAP context.
		*/
		virtual ~WellboreInterpretation() = default;

		/**
		 * Indicates if the wellbore has been interpreted as drilled or not.
		 *
		 * @returns	True if drilled, false if not.
		 */
		virtual bool isDrilled() const = 0;

		GETTER_DATAOBJECTS(RESQML2_NS::WellboreTrajectoryRepresentation, WellboreTrajectoryRepresentation);

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "WellboreInterpretation";

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }
	};
}
