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
#include "AbstractGridRepresentation.h"

namespace RESQML2_NS
{
	/** An abstract stratigraphic organization interpretation. */
	class AbstractStratigraphicOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
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

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~AbstractStratigraphicOrganizationInterpretation() {}

		/**
		 * Gets grid representations
		 *
		 * @returns	Null if it fails, else the grid representations.
		 */
		std::vector<AbstractGridRepresentation*> getGridRepresentations() const;

		/**
		 * Gets grid representation count
		 *
		 * @returns	The count of grid representation assocaited to this strati organization.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getGridRepresentationCount() const;

		/**
		* Get a grid representation associated to this strati org interp by means of its index.
		* @param index	The index of the grid representation to get in the array of grid representaitons of this strati org interp.
		*/
		DLL_IMPORT_OR_EXPORT AbstractGridRepresentation * getGridRepresentation(unsigned int index) const;

		/**
		* Check if a grid representation is wether associated to this strati org interp or not.
		* @param gridRep	The grid representation to check its assocaition with this strati org interp.
		* @return			True or false.
		*/
		DLL_IMPORT_OR_EXPORT bool isAssociatedToGridRepresentation(AbstractGridRepresentation* gridRep) const;
	};
}
