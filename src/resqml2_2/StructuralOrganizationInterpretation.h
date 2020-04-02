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

#include "../resqml2/StructuralOrganizationInterpretation.h"

/** . */
namespace RESQML2_2_NS
{
	class StructuralOrganizationInterpretation final : public RESQML2_NS::StructuralOrganizationInterpretation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT StructuralOrganizationInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::StructuralOrganizationInterpretation(partialObject) {}

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
		StructuralOrganizationInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__OrderingCriteria orderingCriteria);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		StructuralOrganizationInterpretation(gsoap_eml2_3::_resqml22__StructuralOrganizationInterpretation* fromGsoap): RESQML2_NS::StructuralOrganizationInterpretation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~StructuralOrganizationInterpretation() {}

		/**
		 * Add a FaultInterpretation to this StructuralOrganizationInterpretation. Does add the inverse
		 * relationship i.e. from the included FaultInterpretation to this
		 * StructuralOrganizationInterpretation.
		 *
		 * @param [in,out]	faultInterpretation	If non-null, the fault interpretation.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFaultInterpretation(RESQML2_NS::FaultInterpretation * faultInterpretation) final;

		/**
		 * Gets fault interpretation count
		 *
		 * @returns	The fault interpretation count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getFaultInterpretationCount() const final;

		/**
		 * Gets fault interpretation DAta Object Reference
		 *
		 * @param 	index	Zero-based index of the fault interpretation.
		 *
		 * @returns	Null if it fails, else the fault interpretation.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getFaultInterpretationDor(unsigned int index) const final;

		/**
		 * Add an HorizonInterpretation to this StructuralOrganizationInterpretation.
		 *       Does add the inverse relationship i.e. from the included HorizonInterpretation to this
		 *       StructuralOrganizationInterpretation.
		 *
		 * @param [in,out]	horizonInterpretation	the HorizonInterpretation to add.
		 * @param 		  	stratigraphicRank	 	the rank of the horizon interpretation within this
		 * 											structural organization.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackHorizonInterpretation(RESQML2_NS::HorizonInterpretation * horizonInterpretation, int stratigraphicRank) final;

		/**
		 * Gets horizon interpretation count
		 *
		 * @returns	The horizon interpretation count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getHorizonInterpretationCount() const final;

		/**
		 * Gets fault interpretation DataObject Reference
		 *
		 * @param 	index	Zero-based index of the fault interpretation.
		 *
		 * @returns	Null if it fails, else the fault interpretation.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getHorizonInterpretationDor(unsigned int index) const final;

		/**
		 * Add a Frontier interpretation to this StructuralOrganizationInterpretation as a top. Does add
		 * the inverse relationship i.e. from the included Frontier interpretation to this
		 * StructuralOrganizationInterpretation.
		 *
		 * @param [in,out]	topFrontierInterpretation	If non-null, the top frontier interpretation.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackTopFrontierInterpretation(RESQML2_NS::AbstractFeatureInterpretation * topFrontierInterpretation) final;

		/**
		 * Gets top frontier interpretation count
		 *
		 * @returns	The top frontier interpretation count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getTopFrontierInterpretationCount() const final;

		/**
		 * Gets top frontier interpretation DataObject Reference
		 *
		 * @param 	index	Zero-based index of the top frontier interpretation.
		 *
		 * @returns	Null if it fails, else the top frontier interpretation.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getTopFrontierInterpretationDor(unsigned int index) const final;

		/**
		 * Add a Frontier interpretation to this StructuralOrganizationInterpretation as a bottom. Does
		 * add the inverse relationship i.e. from the included Frontier interpretation to this
		 * StructuralOrganizationInterpretation.
		 *
		 * @param [in,out]	bottomFrontierInterpretation	If non-null, the bottom frontier
		 * 													interpretation.
		 */
		DLL_IMPORT_OR_EXPORT  void pushBackBottomFrontierInterpretation(RESQML2_NS::AbstractFeatureInterpretation * bottomFrontierInterpretation) final;

		/**
		 * Gets bottom frontier interpretation count
		 *
		 * @returns	The bottom frontier interpretation count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getBottomFrontierInterpretationCount() const final;

		/**
		 * Gets Bottom frontier interpretation DataObject Reference
		 *
		 * @param 	index	Zero-based index of the Bottom frontier interpretation.
		 *
		 * @returns	Null if it fails, else the Bottom frontier interpretation.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getBottomFrontierInterpretationDor(unsigned int index) const final;

		/**
		 * Add a Frontier interpretation to this StructuralOrganizationInterpretation as a side. Does
		 * add the inverse relationship i.e. from the included Frontier interpretation to this
		 * StructuralOrganizationInterpretation.
		 *
		 * @param [in,out]	sideFrontierInterpretation	If non-null, the side frontier interpretation.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackSideFrontierInterpretation(RESQML2_NS::AbstractFeatureInterpretation * sideFrontierInterpretation) final;

		/**
		 * Gets side frontier interpretation count
		 *
		 * @returns	The side frontier interpretation count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getSideFrontierInterpretationCount() const final;

		/**
		 * Gets Side frontier interpretation DataObject Reference
		 *
		 * @param 	index	Zero-based index of the Side frontier interpretation.
		 *
		 * @returns	Null if it fails, else the Side frontier interpretation.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getSideFrontierInterpretationDor(unsigned int index) const final;
	};
}
