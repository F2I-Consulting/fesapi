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
	class StructuralOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT StructuralOrganizationInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractOrganizationInterpretation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param orgFeat			The feature the instance interprets. It must be a structural organization feature.
		* @param guid				The guid to set to the interpretation. If empty then a new guid will be generated.
		* @param title				A title for the instance to create.
		* @param orderingCriteria	How the included horizons are ordered.
		*/
		StructuralOrganizationInterpretation(class OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml20__OrderingCriteria & orderingCriteria);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		StructuralOrganizationInterpretation(gsoap_resqml2_0_1::_resqml20__StructuralOrganizationInterpretation* fromGsoap): AbstractOrganizationInterpretation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~StructuralOrganizationInterpretation() {}

        /**
        * Add a FaultInterpretation to this StructuralOrganizationInterpretation.
        * Does add the inverse relationship i.e. from the included FaultInterpretation to this StructuralOrganizationInterpretation.
        */
		DLL_IMPORT_OR_EXPORT void pushBackFaultInterpretation(class FaultInterpretation * faultInterpretation);

		DLL_IMPORT_OR_EXPORT unsigned int getFaultInterpretationCount() const;

		DLL_IMPORT_OR_EXPORT class FaultInterpretation* getFaultInterpretation(unsigned int index);

        /**
        * Add an HorizonInterpretation to this StructuralOrganizationInterpretation.
        * Does add the inverse relationship i.e. from the included HorizonInterpretation to this StructuralOrganizationInterpretation.
        * @param horizonInterpretation the HorizonInterpretation to add
        * @param stratigraphicRank the rank of the horizon interpretation within this structural organization
        **/
		DLL_IMPORT_OR_EXPORT void pushBackHorizonInterpretation(class HorizonInterpretation * horizonInterpretation, const int & stratigraphicRank);

		DLL_IMPORT_OR_EXPORT unsigned int getHorizonInterpretationCount() const;

		DLL_IMPORT_OR_EXPORT HorizonInterpretation* getHorizonInterpretation(unsigned int index) const;

		/**
        * Add a Frontier interpretation to this StructuralOrganizationInterpretation as a top.
        * Does add the inverse relationship i.e. from the included Frontier interpretation to this StructuralOrganizationInterpretation.
        */
		DLL_IMPORT_OR_EXPORT void pushBackTopFrontierInterpretation(AbstractFeatureInterpretation * topFrontierInterpretation);

		DLL_IMPORT_OR_EXPORT unsigned int getTopFrontierInterpretationCount() const;

		DLL_IMPORT_OR_EXPORT AbstractFeatureInterpretation* getTopFrontierInterpretation(unsigned int index) const;

		/**
        * Add a Frontier interpretation to this StructuralOrganizationInterpretation as a bottom.
        * Does add the inverse relationship i.e. from the included Frontier interpretation to this StructuralOrganizationInterpretation.
        */
		DLL_IMPORT_OR_EXPORT  void pushBackBottomFrontierInterpretation(AbstractFeatureInterpretation * bottomFrontierInterpretation);

		DLL_IMPORT_OR_EXPORT unsigned int getBottomFrontierInterpretationCount() const;

		DLL_IMPORT_OR_EXPORT AbstractFeatureInterpretation* getBottomFrontierInterpretation(unsigned int index) const;

		/**
        * Add a Frontier interpretation to this StructuralOrganizationInterpretation as a side.
        * Does add the inverse relationship i.e. from the included Frontier interpretation to this StructuralOrganizationInterpretation.
        */
		DLL_IMPORT_OR_EXPORT void pushBackSideFrontierInterpretation(AbstractFeatureInterpretation * sideFrontierInterpretation);

		DLL_IMPORT_OR_EXPORT unsigned int getSideFrontierInterpretationCount() const;

		DLL_IMPORT_OR_EXPORT AbstractFeatureInterpretation* getSideFrontierInterpretation(unsigned int index) const;

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
