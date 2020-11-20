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
	 * @brief	An abstract stratigraphic organization interpretation is the main class that defines
	 * 			the relationships between the stratigraphic units and provides the stratigraphic
	 * 			hierarchy of the earth.
	 * 			
	 * 			BUSINESS RULE: A stratigraphic organization must be in a ranked order from a lower
	 * 			rank to an upper rank. For example, it is possible to find previous unit containment
	 * 			relationships between several ranks.
	 */
	class AbstractStratigraphicOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT AbstractStratigraphicOrganizationInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractOrganizationInterpretation(partialObject) {}

		/** Default constructor */
		AbstractStratigraphicOrganizationInterpretation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractStratigraphicOrganizationInterpretation(gsoap_resqml2_0_1::resqml20__AbstractStratigraphicOrganizationInterpretation* fromGsoap) : AbstractOrganizationInterpretation(fromGsoap) {}
		AbstractStratigraphicOrganizationInterpretation(gsoap_eml2_3::resqml22__AbstractStratigraphicOrganizationInterpretation* fromGsoap) : AbstractOrganizationInterpretation(fromGsoap) {}

	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~AbstractStratigraphicOrganizationInterpretation() = default;

		/**
		 * Gets the grid representations associated to this stratigraphic organization interpretation.
		 *
		 * @returns	A vector of pointers to all the grid representations associated to this stratigraphic
		 * 			organization interpretation.
		 */
		std::vector<AbstractGridRepresentation*> getGridRepresentations() const;

		/**
		 * Gets the count of grid representations associated to this stratigraphic organization
		 * interpretation.
		 *
		 * @exception	std::range_error	If the count of associated grid representations is strictly
		 * 									greater than <tt>unsigned int</tt> max.
		 *
		 * @returns	The count of associated grid representations.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getGridRepresentationCount() const;

		/**
		 * Gets a grid representation associated to this stratigraphic organization interpretation by
		 * means of its index.
		 *
		 * @exception	std::out_of_range	If @p index is out of range.
		 *
		 * @param 	index	The index of the grid representation to get in the array of grid
		 * 					representations of this stratigraphic organization interpretations.
		 *
		 * @returns	The associated grid representation at index @p index.
		 */
		DLL_IMPORT_OR_EXPORT AbstractGridRepresentation * getGridRepresentation(unsigned int index) const;

		/**
		 * Checks whether a given grid representation is associated to this stratigraphic organization
		 * interpretation or not.
		 *
		 * @param [in]	gridRep	The grid representation fro which we want to check its association
		 * 							with this stratigraphic organization interpretation.
		 *
		 * @returns	True if @p gridRep is associated to this stratigraphic organization interpretation or
		 * 			false if it is not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAssociatedToGridRepresentation(AbstractGridRepresentation* gridRep) const;
	};
}
