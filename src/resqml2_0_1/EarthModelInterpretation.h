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

#include "../resqml2/AbstractFeatureInterpretation.h"

namespace RESQML2_0_1_NS
{
	/**
	* This class is a container for other organizations that are consistent to each others.
	*/
	class EarthModelInterpretation : public RESQML2_NS::AbstractFeatureInterpretation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT EarthModelInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractFeatureInterpretation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param orgFeat	The feature the instance interprets.
		* @param guid		The guid to set to the interpretation. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		*/
		EarthModelInterpretation(class OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		EarthModelInterpretation(gsoap_resqml2_0_1::_resqml20__EarthModelInterpretation* fromGsoap) : RESQML2_NS::AbstractFeatureInterpretation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~EarthModelInterpretation() {}

		//Structural

		DLL_IMPORT_OR_EXPORT bool hasStructuralOrganizationInterpretation() const;

		DLL_IMPORT_OR_EXPORT class StructuralOrganizationInterpretation* getStructuralOrganizationInterpertation() const;

		DLL_IMPORT_OR_EXPORT void setStructuralOrganizationInterpretation(class StructuralOrganizationInterpretation * structOrganization);

		//Strati column

		/*
		* Check if a strati column is associated to this earth model interpretation
		*
		* @return True if a strati column is associated to this earth model interpretation elsa false.
		*/
		DLL_IMPORT_OR_EXPORT bool hasStratiColumn() const;

		DLL_IMPORT_OR_EXPORT void setStratiColumn(class StratigraphicColumn * stratiColumn);

		/*
		* Get the strati column associated to this earth model interpretation.
		* Throw an exception if there is no strati column associated. Check with hasStratiColumn().
		*
		* @return The associated stratigraphic column.
		*/
		DLL_IMPORT_OR_EXPORT class StratigraphicColumn* getStratiColumn() const;

		//Strati occurrences

		DLL_IMPORT_OR_EXPORT unsigned int getStratiOccurrenceCount() const;

		DLL_IMPORT_OR_EXPORT class StratigraphicOccurrenceInterpretation* getStratiOccurrence(unsigned int index) const;

		DLL_IMPORT_OR_EXPORT void pushBackStratiOccurrence(class StratigraphicOccurrenceInterpretation * stratiOccurence);

		// Rock Fluid
		DLL_IMPORT_OR_EXPORT bool hasRockFluidOrganizationInterpretation() const;

		DLL_IMPORT_OR_EXPORT void setRockFluidOrganizationInterpretation(class RockFluidOrganizationInterpretation* rockFluid);

		DLL_IMPORT_OR_EXPORT class RockFluidOrganizationInterpretation* getRockFluidOrganizationInterpretation() const;
		
		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		* Get the standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlNamespace() const { return XML_NS; }

		void loadTargetRelationships();
	};
}
