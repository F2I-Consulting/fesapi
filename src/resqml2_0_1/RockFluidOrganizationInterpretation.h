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
}

namespace RESQML2_0_1_NS
{
	/**
	* This class is a container for rock fluid units.
	* As a first step, This class only works for a single rock fluid unit container due to the fact that the workaround described here http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-500-106-0-R-sv2010.html is not impelemented yet.
	* Use with caution : ONLY IF YOU HAVE A SINGLE ROCK FLUID UNIT ORGANISATION !!!!
	*/
	class RockFluidOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	public:
		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT RockFluidOrganizationInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractOrganizationInterpretation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param orgFeat				The feature the instance interprets. It must be a "fluid" organization feature.
		* @param guid					The guid to set to the interpretation. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param rockFluidUnitInterp	The unique (for now) rock fluid unit which is contained by this organization
		*/
		RockFluidOrganizationInterpretation(class OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, class RockFluidUnitInterpretation * rockFluidUnitInterp);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		RockFluidOrganizationInterpretation(gsoap_resqml2_0_1::_resqml20__RockFluidOrganizationInterpretation* fromGsoap) : AbstractOrganizationInterpretation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~RockFluidOrganizationInterpretation() {}
		
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_NS::AbstractGridRepresentation *> getGridRepresentationSet() const;

		/**
		* @return The count of grid representation associated to this rock fluid organization.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getGridRepresentationCount() const;

		/**
		* Get a grid representation associated to this rock fluid org interp by means of its index.
		* @param index	The index of the grid representation to get in the array of grid representaitons of this rock fluid org interp.
		*/
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractGridRepresentation * getGridRepresentation(unsigned int index) const;

		/**
		* Check if a grid representation is wether associated to this rock fluid org interp or not.
		* @param gridRep	The grid representation to check its assocaition with this rock fluid org interp.
		* @return			True or false.
		*/
		DLL_IMPORT_OR_EXPORT bool isAssociatedToGridRepresentation(RESQML2_NS::AbstractGridRepresentation* gridRep) const;

		/**
		* Push back a rock fluid unit in this organization
		*
		* @param rockFluidUnitInterpretation	The rock fluid unit interpretation to push back
		*/
		DLL_IMPORT_OR_EXPORT void pushBackRockFluidUnitInterpretation(class RockFluidUnitInterpretation * rockFluidUnitInterpretation);

		/**
		* @return The count of rock fluid unit interp in this rock fluid organization.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getRockFluidUnitInterpCount() const;

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
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

	private:
		void loadTargetRelationships();
	};
}
