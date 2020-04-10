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

	class RockFluidOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	public:
		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~RockFluidOrganizationInterpretation() {}
		
		DLL_IMPORT_OR_EXPORT std::vector<AbstractGridRepresentation*> getGridRepresentationSet() const;

		/**
		* @return The count of grid representation associated to this rock fluid organization.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getGridRepresentationCount() const;

		/**
		* Get a grid representation associated to this rock fluid org interp by means of its index.
		* @param index	The index of the grid representation to get in the array of grid representaitons of this rock fluid org interp.
		*/
		DLL_IMPORT_OR_EXPORT AbstractGridRepresentation* getGridRepresentation(unsigned int index) const;

		/**
		* Check if a grid representation is wether associated to this rock fluid org interp or not.
		* @param gridRep	The grid representation to check its assocaition with this rock fluid org interp.
		* @return			True or false.
		*/
		DLL_IMPORT_OR_EXPORT bool isAssociatedToGridRepresentation(AbstractGridRepresentation* gridRep) const;

		/**
		* Push back a rock fluid unit in this organization
		*
		* @param rockFluidUnitInterpretation	The rock fluid unit interpretation to push back
		*/
		DLL_IMPORT_OR_EXPORT virtual void pushBackRockFluidUnitInterpretation(class RockFluidUnitInterpretation* rockFluidUnitInterpretation) = 0;

		/**
		* @return The count of rock fluid unit interp in this rock fluid organization.
		*/
		DLL_IMPORT_OR_EXPORT virtual unsigned int getRockFluidUnitInterpCount() const = 0;

		/**
		* Get a rock fluid unit interp DOR of this rock fluid org interp by means of its index.
		* @param index	The index of the rock fluid unit interp to get in this rock fluid org interp.
		*/
		virtual COMMON_NS::DataObjectReference getRockFluidUnitInterpretationDor(unsigned int index) const = 0;

		/**
		* Get a rock fluid unit interp of this rock fluid org interp by means of its index.
		* @param index	The index of the rock fluid unit interp to get in this rock fluid org interp.
		*/
		DLL_IMPORT_OR_EXPORT class RockFluidUnitInterpretation* getRockFluidUnitInterpretation(unsigned int index) const;

		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		* Get the standard XML tag without XML namespace for serializing this data object.
		*/
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
