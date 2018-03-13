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
#include "resqml2_0_1/EarthModelInterpretation.h"

namespace RESQML2_0_1_NS
{
	class DLL_IMPORT_OR_EXPORT StructuralOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		StructuralOrganizationInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractOrganizationInterpretation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param orgFeat			The feature the instance interprets. It must be a structural organization feature.
		* @param guid				The guid to set to the interpretation. If empty then a new guid will be generated.
		* @param title				A title for the instance to create.
		* @param orderingCriteria	How the included horizons are ordered.
		*/
		StructuralOrganizationInterpretation(class OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__OrderingCriteria & orderingCriteria);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		StructuralOrganizationInterpretation(gsoap_resqml2_0_1::_resqml2__StructuralOrganizationInterpretation* fromGsoap): AbstractOrganizationInterpretation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~StructuralOrganizationInterpretation() {}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

        /**
        * Add a FaultInterpretation to this StructuralOrganizationInterpretation.
        * Does add the inverse relationship i.e. from the included FaultInterpretation to this StructuralOrganizationInterpretation.
        */
        void pushBackFaultInterpretation(class FaultInterpretation * faultInterpretation);

		unsigned int getFaultInterpretationCount() const;

		class FaultInterpretation* getFaultInterpretation(const unsigned int & index);

        /**
        * Add an HorizonInterpretation to this StructuralOrganizationInterpretation.
        * Does add the inverse relationship i.e. from the included HorizonInterpretation to this StructuralOrganizationInterpretation.
        * @param horizonInterpretation the HorizonInterpretation to add
        * @param stratigraphicRank the rank of the horizon interpretation within this structural organization
        **/
        void pushBackHorizonInterpretation(class HorizonInterpretation * horizonInterpretation, const int & stratigraphicRank);

		/**
        * Add a Frontier interpretation to this StructuralOrganizationInterpretation as a top.
        * Does add the inverse relationship i.e. from the included Frontier interpretation to this StructuralOrganizationInterpretation.
        */
		void pushBackTopFrontierInterpretation(AbstractFeatureInterpretation * topFrontierInterpretation);

		/**
        * Add a Frontier interpretation to this StructuralOrganizationInterpretation as a bottom.
        * Does add the inverse relationship i.e. from the included Frontier interpretation to this StructuralOrganizationInterpretation.
        */
        void pushBackBottomFrontierInterpretation(AbstractFeatureInterpretation * bottomFrontierInterpretation);

		/**
        * Add a Frontier interpretation to this StructuralOrganizationInterpretation as a side.
        * Does add the inverse relationship i.e. from the included Frontier interpretation to this StructuralOrganizationInterpretation.
        */
        void pushBackSideFrontierInterpretation(AbstractFeatureInterpretation * sideFrontierInterpretation);

    private:

        std::vector<epc::Relationship> getAllEpcRelationships() const;	
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc);

        // backward relationships
        std::vector<EarthModelInterpretation *> earthModelSet;
		std::vector<RESQML2_NS::GridConnectionSetRepresentation *> gridConnectionSet;

		friend void EarthModelInterpretation::setStructuralOrganizationInterpretation(StructuralOrganizationInterpretation * structOrganization);
	};
}

