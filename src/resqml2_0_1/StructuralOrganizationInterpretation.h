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

namespace RESQML2_0_1_NS
{
	/** @brief	A structural organization interpretation. This class cannot be inherited. */
	class StructuralOrganizationInterpretation final : public RESQML2_NS::StructuralOrganizationInterpretation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT StructuralOrganizationInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::StructuralOrganizationInterpretation(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt> or if @p orgFeat is not a
		 * 										structural organization.
		 *
		 * @param [in]	orgFeat				The feature the instance interprets. It must be a
		 * 										structural organization feature.
		 * @param 	  	guid				The guid to set to the interpretation. If empty then a new
		 * 									guid will be generated.
		 * @param 	  	title				A title for the instance to create.
		 * @param 	  	orderingCriteria	How the included horizons are ordered.
		 */
		StructuralOrganizationInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__OrderingCriteria orderingCriteria);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		StructuralOrganizationInterpretation(gsoap_resqml2_0_1::_resqml20__StructuralOrganizationInterpretation* fromGsoap): RESQML2_NS::StructuralOrganizationInterpretation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~StructuralOrganizationInterpretation() = default;

		DLL_IMPORT_OR_EXPORT void pushBackFaultInterpretation(RESQML2_NS::FaultInterpretation * faultInterpretation) final;

		DLL_IMPORT_OR_EXPORT unsigned int getFaultInterpretationCount() const final;

		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getFaultInterpretationDor(unsigned int index) const final;

		DLL_IMPORT_OR_EXPORT void pushBackHorizonInterpretation(RESQML2_NS::HorizonInterpretation * horizonInterpretation, int stratigraphicRank) final;

		DLL_IMPORT_OR_EXPORT unsigned int getHorizonInterpretationCount() const final;

		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getHorizonInterpretationDor(unsigned int index) const final;

		DLL_IMPORT_OR_EXPORT void pushBackTopFrontierInterpretation(RESQML2_NS::AbstractFeatureInterpretation * topFrontierInterpretation) final;

		DLL_IMPORT_OR_EXPORT unsigned int getTopFrontierInterpretationCount() const final;

		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getTopFrontierInterpretationDor(unsigned int index) const final;

		DLL_IMPORT_OR_EXPORT  void pushBackBottomFrontierInterpretation(RESQML2_NS::AbstractFeatureInterpretation * bottomFrontierInterpretation) final;

		DLL_IMPORT_OR_EXPORT unsigned int getBottomFrontierInterpretationCount() const final;

		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getBottomFrontierInterpretationDor(unsigned int index) const final;

		DLL_IMPORT_OR_EXPORT void pushBackSideFrontierInterpretation(RESQML2_NS::AbstractFeatureInterpretation * sideFrontierInterpretation) final;

		DLL_IMPORT_OR_EXPORT unsigned int getSideFrontierInterpretationCount() const final;

		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getSideFrontierInterpretationDor(unsigned int index) const final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
