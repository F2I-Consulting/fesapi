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
#include "EarthModelInterpretation.h"

/** . */
namespace RESQML2_0_1_NS
{
	/** A structural organization interpretation. */
	class StructuralOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT StructuralOrganizationInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractOrganizationInterpretation(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	orgFeat				The feature the instance interprets. It must be a
		 * 										structural organization feature.
		 * @param 		  	guid				The guid to set to the interpretation. If empty then a
		 * 										new guid will be generated.
		 * @param 		  	title				A title for the instance to create.
		 * @param 		  	orderingCriteria	How the included horizons are ordered.
		 */
		StructuralOrganizationInterpretation(class OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml20__OrderingCriteria & orderingCriteria);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		StructuralOrganizationInterpretation(gsoap_resqml2_0_1::_resqml20__StructuralOrganizationInterpretation* fromGsoap): AbstractOrganizationInterpretation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~StructuralOrganizationInterpretation() {}

		/**
		 * Add a FaultInterpretation to this StructuralOrganizationInterpretation. Does add the inverse
		 * relationship i.e. from the included FaultInterpretation to this
		 * StructuralOrganizationInterpretation.
		 *
		 * @param [in,out]	faultInterpretation	If non-null, the fault interpretation.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFaultInterpretation(class FaultInterpretation * faultInterpretation);

		/**
		 * Gets fault interpretation count
		 *
		 * @returns	The fault interpretation count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getFaultInterpretationCount() const;

		/** A fault interpretation*. */
		DLL_IMPORT_OR_EXPORT class FaultInterpretation* getFaultInterpretation(unsigned int index);

		/**
		 * Add an HorizonInterpretation to this StructuralOrganizationInterpretation.
		 *       Does add the inverse relationship i.e. from the included HorizonInterpretation to this
		 *       StructuralOrganizationInterpretation.
		 *
		 * @param [in,out]	horizonInterpretation	the HorizonInterpretation to add.
		 * @param 		  	stratigraphicRank	 	the rank of the horizon interpretation within this
		 * 											structural organization.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackHorizonInterpretation(class HorizonInterpretation * horizonInterpretation, const int & stratigraphicRank);

		/**
		 * Gets horizon interpretation count
		 *
		 * @returns	The horizon interpretation count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getHorizonInterpretationCount() const;

		/**
		 * Gets horizon interpretation
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	Null if it fails, else the horizon interpretation.
		 */
		DLL_IMPORT_OR_EXPORT HorizonInterpretation* getHorizonInterpretation(unsigned int index) const;

		/**
		 * Add a Frontier interpretation to this StructuralOrganizationInterpretation as a top. Does add
		 * the inverse relationship i.e. from the included Frontier interpretation to this
		 * StructuralOrganizationInterpretation.
		 *
		 * @param [in,out]	topFrontierInterpretation	If non-null, the top frontier interpretation.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackTopFrontierInterpretation(AbstractFeatureInterpretation * topFrontierInterpretation);

		/**
		 * Gets top frontier interpretation count
		 *
		 * @returns	The top frontier interpretation count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getTopFrontierInterpretationCount() const;

		/**
		 * Gets top frontier interpretation
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	Null if it fails, else the top frontier interpretation.
		 */
		DLL_IMPORT_OR_EXPORT AbstractFeatureInterpretation* getTopFrontierInterpretation(unsigned int index) const;

		/**
		 * Add a Frontier interpretation to this StructuralOrganizationInterpretation as a bottom. Does
		 * add the inverse relationship i.e. from the included Frontier interpretation to this
		 * StructuralOrganizationInterpretation.
		 *
		 * @param [in,out]	bottomFrontierInterpretation	If non-null, the bottom frontier
		 * 													interpretation.
		 */
		DLL_IMPORT_OR_EXPORT  void pushBackBottomFrontierInterpretation(AbstractFeatureInterpretation * bottomFrontierInterpretation);

		/**
		 * Gets bottom frontier interpretation count
		 *
		 * @returns	The bottom frontier interpretation count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getBottomFrontierInterpretationCount() const;

		/**
		 * Gets bottom frontier interpretation
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	Null if it fails, else the bottom frontier interpretation.
		 */
		DLL_IMPORT_OR_EXPORT AbstractFeatureInterpretation* getBottomFrontierInterpretation(unsigned int index) const;

		/**
		 * Add a Frontier interpretation to this StructuralOrganizationInterpretation as a side. Does
		 * add the inverse relationship i.e. from the included Frontier interpretation to this
		 * StructuralOrganizationInterpretation.
		 *
		 * @param [in,out]	sideFrontierInterpretation	If non-null, the side frontier interpretation.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackSideFrontierInterpretation(AbstractFeatureInterpretation * sideFrontierInterpretation);

		/**
		 * Gets side frontier interpretation count
		 *
		 * @returns	The side frontier interpretation count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getSideFrontierInterpretationCount() const;

		/**
		 * Gets side frontier interpretation
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	Null if it fails, else the side frontier interpretation.
		 */
		DLL_IMPORT_OR_EXPORT AbstractFeatureInterpretation* getSideFrontierInterpretation(unsigned int index) const;

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

    private:	
		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
