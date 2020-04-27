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

#include "AbstractOrganizationInterpretation.h"

namespace RESQML2_NS
{
	class AbstractGridRepresentation;

	/**
	 * @brief	This class describes the organization of geological reservoir, i.e., of an
	 * 			interconnected network of porous and permeable rock units, containing an accumulation
	 * 			of economic fluids, such as oil and gas. A reservoir is normally enveloped by rock
	 * 			and fluid barriers and contains a single natural pressure system.
	 */
	class RockFluidOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	public:
		/**
		* Destructor does nothing since the memory is managed by the gSOAP context.
		*/
		virtual ~RockFluidOrganizationInterpretation() {}

		/**
		 * Gets the set of grid representations associated to this rock fluid organization.
		 *
		 * @returns	A vector of pointers to the grid representations associated to this rock fluid
		 * 			organization.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<AbstractGridRepresentation*> getGridRepresentationSet() const;

		/**
		 * Gets the count of grid representations associated to this rock fluid organization.
		 *
		 * @exception	std::range_error	If the count of associated grid representations is strictly
		 * 									greater than unsigned int max.
		 *
		 * @returns	The count of grid representations associated to this rock fluid organization.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getGridRepresentationCount() const; // It is mainly used in SWIG context for parsing the vector from a non C++ language.

		/**
		 * Gets a grid representation associated to this rock fluid organization by means of its index.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getGridRepresentationCount().
		 *
		 * @param 	index	Zero-based index of the grid representation to get in the array of grid
		 * 					representations of this rock fluid organization.
		 *
		 * @returns	The associated grid representation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT AbstractGridRepresentation* getGridRepresentation(unsigned int index) const; // It is mainly used in SWIG context for parsing the vector from a non C++ language.

		/**
		 * Checks whether a given grid representation is associated to this rock fluid organization.
		 *
		 * @param [in]	gridRep	The grid representation for which we want to know if it is associated to
		 * 						this rock fluid organization.
		 *
		 * @returns	True if @p gridRep is associated to this rock fluid organization, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAssociatedToGridRepresentation(AbstractGridRepresentation* gridRep) const;

		/**
		 * Pushes back a rock fluid unit interpretation in this rock fluid organization.
		 *
		 * @exception	std::invalid_argument	If <tt>rockFluidUnitInterpretation == nullptr</tt>.
		 *
		 * @param [in]	rockFluidUnitInterpretation	The rock fluid unit interpretation to push back.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackRockFluidUnitInterpretation(class RockFluidUnitInterpretation* rockFluidUnitInterpretation) = 0;

		/**
		 * Gets the count of rock fluid unit interpretations of this rock fluid organization.
		 *
		 * @returns	The count of rock fluid unit interpretations of this rock fluid organization.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getRockFluidUnitInterpCount() const = 0;

		/**
		 * Gets the DOR of a rock fluid unit interpretation of this rock fluid organization by means of
		 * its index.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getRockFluidUnitInterpCount().
		 *
		 * @param 	index	Zero-based index of the rock fluid unit interpretation for which we look for
		 * 					the DOR.
		 *
		 * @returns	The DOR of the rock fluid unit interpretation at position @p index.
		 */
		virtual COMMON_NS::DataObjectReference getRockFluidUnitInterpretationDor(unsigned int index) const = 0;

		/**
		 * Gets a rock fluid unit interpretation of this rock fluid organization by means of
		 * its index.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getRockFluidUnitInterpCount().
		 *
		 * @param 	index	Zero-based index of the rock fluid unit interpretation we look for.
		 *
		 * @returns	The rock fluid unit interpretation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT class RockFluidUnitInterpretation* getRockFluidUnitInterpretation(unsigned int index) const;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:
		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT RockFluidOrganizationInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractOrganizationInterpretation(partialObject) {}

		RockFluidOrganizationInterpretation() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		RockFluidOrganizationInterpretation(gsoap_resqml2_0_1::_resqml20__RockFluidOrganizationInterpretation* fromGsoap) : AbstractOrganizationInterpretation(fromGsoap) {}
		RockFluidOrganizationInterpretation(gsoap_eml2_3::_resqml22__RockFluidOrganizationInterpretation* fromGsoap) : AbstractOrganizationInterpretation(fromGsoap) {}

	private:
		void loadTargetRelationships();
	};
}
