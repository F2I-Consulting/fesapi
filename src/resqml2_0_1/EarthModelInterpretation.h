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

#include "resqml2/AbstractFeatureInterpretation.h"

namespace RESQML2_0_1_NS
{
	/**
	* This class is a container for other organizations that are consistent to each others.
	*/
	class DLL_IMPORT_OR_EXPORT EarthModelInterpretation : public RESQML2_NS::AbstractFeatureInterpretation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		EarthModelInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractFeatureInterpretation(partialObject) {}

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
		EarthModelInterpretation(gsoap_resqml2_0_1::_resqml2__EarthModelInterpretation* fromGsoap) : RESQML2_NS::AbstractFeatureInterpretation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~EarthModelInterpretation() {}

  	void setStructuralOrganizationInterpretation(class StructuralOrganizationInterpretation * structOrganization);

		void setStratiColumn(class StratigraphicColumn * stratiColumn);
		/*
		* Check if a strati column is associated to this earth model interpretation
		*
		* @return True if a strati column is associated to this earth model interpretation elsa false.
		*/
		bool hasStratiColumn() const;

		/*
		* Get the strati column associated to this earth model interpretation.
		* Throw an exception if there is no strati column associated. Check with hasStratiColumn().
		*
		* @return The associated stratigraphic column.
		*/
		class StratigraphicColumn* getStratiColumn() const;

		void pushBackStratiOccurence(class StratigraphicOccurrenceInterpretation * stratiOccurence);

		// Rock Fluid
		void setRockFluidOrganizationInterpretation(class RockFluidOrganizationInterpretation* rockFluid);

		bool hasRockFluidOrganizationInterpretation() const;

		RockFluidOrganizationInterpretation* getRockFluidOrganizationInterpretation() const;
		
		void pushBackRockFluidOrganizationInterpretation(class RockFluidOrganizationInterpretation * rockFluid);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

    private:
    std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc);
	};
}

