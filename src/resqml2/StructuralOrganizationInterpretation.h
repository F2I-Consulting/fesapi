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

/** . */
namespace RESQML2_NS
{
	class FaultInterpretation;
	class HorizonInterpretation;
	
	class StructuralOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~StructuralOrganizationInterpretation() {}

		/**
		 * Add a FaultInterpretation to this StructuralOrganizationInterpretation. Does add the inverse
		 * relationship i.e. from the included FaultInterpretation to this
		 * StructuralOrganizationInterpretation.
		 *
		 * @param [in,out]	faultInterpretation	If non-null, the fault interpretation.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackFaultInterpretation(FaultInterpretation * faultInterpretation) = 0;

		/**
		 * Gets fault interpretation count
		 *
		 * @returns	The fault interpretation count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getFaultInterpretationCount() const = 0;

		/**
		 * Gets fault interpretation DAta Object Reference
		 *
		 * @param 	index	Zero-based index of the fault interpretation.
		 *
		 * @returns	Null if it fails, else the fault interpretation.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getFaultInterpretationDor(unsigned int index) const = 0;

		/** A fault interpretation*. */
		DLL_IMPORT_OR_EXPORT FaultInterpretation* getFaultInterpretation(unsigned int index) const;

		/**
		 * Add an HorizonInterpretation to this StructuralOrganizationInterpretation.
		 *       Does add the inverse relationship i.e. from the included HorizonInterpretation to this
		 *       StructuralOrganizationInterpretation.
		 *
		 * @param [in,out]	horizonInterpretation	the HorizonInterpretation to add.
		 * @param 		  	stratigraphicRank	 	the rank of the horizon interpretation within this
		 * 											structural organization.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackHorizonInterpretation(HorizonInterpretation * horizonInterpretation, int stratigraphicRank) = 0;

		/**
		 * Gets horizon interpretation count
		 *
		 * @returns	The horizon interpretation count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getHorizonInterpretationCount() const = 0;

		/**
		 * Gets fault interpretation DataObject Reference
		 *
		 * @param 	index	Zero-based index of the fault interpretation.
		 *
		 * @returns	Null if it fails, else the fault interpretation.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getHorizonInterpretationDor(unsigned int index) const = 0;

		/**
		 * Gets horizon interpretation
		 *
		 * @param 	index	Zero-based index of the horizon interpretation.
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
		DLL_IMPORT_OR_EXPORT virtual void pushBackTopFrontierInterpretation(AbstractFeatureInterpretation * topFrontierInterpretation) = 0;

		/**
		 * Gets top frontier interpretation count
		 *
		 * @returns	The top frontier interpretation count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getTopFrontierInterpretationCount() const = 0;

		/**
		 * Gets top frontier interpretation DataObject Reference
		 *
		 * @param 	index	Zero-based index of the top frontier interpretation.
		 *
		 * @returns	Null if it fails, else the top frontier interpretation.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getTopFrontierInterpretationDor(unsigned int index) const = 0;

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
		DLL_IMPORT_OR_EXPORT virtual void pushBackBottomFrontierInterpretation(AbstractFeatureInterpretation * bottomFrontierInterpretation) = 0;

		/**
		 * Gets bottom frontier interpretation count
		 *
		 * @returns	The bottom frontier interpretation count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getBottomFrontierInterpretationCount() const = 0;

		/**
		 * Gets Bottom frontier interpretation DataObject Reference
		 *
		 * @param 	index	Zero-based index of the Bottom frontier interpretation.
		 *
		 * @returns	Null if it fails, else the Bottom frontier interpretation.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getBottomFrontierInterpretationDor(unsigned int index) const = 0;

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
		DLL_IMPORT_OR_EXPORT virtual void pushBackSideFrontierInterpretation(AbstractFeatureInterpretation * sideFrontierInterpretation) = 0;

		/**
		 * Gets side frontier interpretation count
		 *
		 * @returns	The side frontier interpretation count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getSideFrontierInterpretationCount() const = 0;

		/**
		 * Gets Side frontier interpretation DataObject Reference
		 *
		 * @param 	index	Zero-based index of the Side frontier interpretation.
		 *
		 * @returns	Null if it fails, else the Side frontier interpretation.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getSideFrontierInterpretationDor(unsigned int index) const = 0;

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
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

    protected:

		/**
		* Only to be used in partial transfer context
		*/
		StructuralOrganizationInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractOrganizationInterpretation(partialObject) {}

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
		StructuralOrganizationInterpretation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		StructuralOrganizationInterpretation(gsoap_resqml2_0_1::_resqml20__StructuralOrganizationInterpretation* fromGsoap): AbstractOrganizationInterpretation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		StructuralOrganizationInterpretation(gsoap_eml2_3::_resqml22__StructuralOrganizationInterpretation* fromGsoap) : AbstractOrganizationInterpretation(fromGsoap) {}
		
		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
