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

#include "resqml2_0_1/AbstractOrganizationInterpretation.h"
#include "resqml2/AbstractColumnLayerGridRepresentation.h"

namespace RESQML2_0_1_NS
{
	class AbstractStratigraphicOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractStratigraphicOrganizationInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractOrganizationInterpretation(partialObject) {}

		AbstractStratigraphicOrganizationInterpretation() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractStratigraphicOrganizationInterpretation(gsoap_resqml2_0_1::resqml2__AbstractStratigraphicOrganizationInterpretation* fromGsoap) : AbstractOrganizationInterpretation(fromGsoap) {}

		virtual std::vector<epc::Relationship> getAllSourceRelationships() const;

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractStratigraphicOrganizationInterpretation() {}

		/**
		* @return The count of grid representation assocaited to this strati organization.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getGridRepresentationCount() const;

		/**
		* Get a grid representation associated to this strati org interp by means of its index.
		* @param index	The index of the grid representation to get in the array of grid representaitons of this strati org interp.
		*/
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractGridRepresentation* getGridRepresentation(const unsigned int & index) const;

		/**
		* Check if a grid representation is wether associated to this strati org interp or not.
		* @param gridRep	The grid representation to check its assocaition with this strati org interp.
		* @return			True or false.
		*/
		DLL_IMPORT_OR_EXPORT bool isAssociatedToGridRepresentation(RESQML2_NS::AbstractGridRepresentation* gridRep) const;

	private:

		// Backward relationship
		std::vector<RESQML2_NS::AbstractGridRepresentation *> gridRepresentationSet;

		friend void RESQML2_NS::AbstractGridRepresentation::setCellAssociationWithStratigraphicOrganizationInterpretation(ULONG64 * stratiUnitIndices, const ULONG64 & nullValue, AbstractStratigraphicOrganizationInterpretation * stratiOrgInterp);
		friend void RESQML2_NS::AbstractColumnLayerGridRepresentation::setIntervalAssociationWithStratigraphicOrganizationInterpretation(ULONG64 * stratiUnitIndices, const ULONG64 & nullValue, AbstractStratigraphicOrganizationInterpretation* stratiOrgInterp);
	};
}

