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
	/**
	 * @brief	May refer to one of these: wellore, borehole or sidetrack.
	 * 			
	 * 			Wellbore: a unique, oriented path from the bottom of a drilled borehole to the
	 * 			surface of the earth. The path must not overlap or cross itself.
	 * 			
	 * 			Borehole: a hole excavated in the earth as a result of drilling or boring operations.
	 * 			The borehole may represent the hole of an entire wellbore (when no sidetracks are
	 * 			present), or a sidetrack extension. A borehole extends from an originating point (the
	 * 			surface location for the initial borehole or kickoff point for sidetracks) to a
	 * 			terminating (bottomhole) point.
	 * 			
	 * 			Sidetrack: a borehole that originates in another borehole as opposed to originating
	 * 			at the surface.
	 */
	class WellboreFeature : public AbstractTechnicalFeature
	{
	public:

		WellboreFeature() {}

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT WellboreFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractTechnicalFeature(partialObject) {}

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		WellboreFeature(gsoap_resqml2_0_1::_resqml20__WellboreFeature* fromGsoap): AbstractTechnicalFeature(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		WellboreFeature(gsoap_eml2_3::_resqml22__WellboreFeature* fromGsoap) : AbstractTechnicalFeature(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gSOAP context.
		*/
		virtual ~WellboreFeature() = default;

		/**
		 * Gets the WITSML wellbore associated to this wellbore feature.
		 *
		 * @exception	std::logic_error	If more than one WITSML wellbore is associated to this
		 * 									wellbore feature.
		 *
		 * @returns	@c nullptr if no WITSML wellbore is associated to this wellbore feature, else the
		 * 			associated WITSML wellbore.
		 */
		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Wellbore* getWitsmlWellbore() const;

		/**
		 * Sets the WITSML wellbore associated to this instance.
		 *
		 * @exception	std::invalid_argument	If the WITSML wellbore to set is NULL.
		 *
		 * @param [in]	wellbore	The WITSML wellbore to associate to this wellbore. It cannot be null.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setWitsmlWellbore(WITSML2_0_NS::Wellbore * wellbore) = 0;

		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }
	};
}
