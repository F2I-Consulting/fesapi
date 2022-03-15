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
	class FaultInterpretation;
	class HorizonInterpretation;

	/**
	 * @brief	One of the main types of RESQML organizations, this class gathers boundary
	 * 			interpretations (e.g., horizons and faults) plus frontier features and their
	 * 			relationships (contacts interpretations), which when taken together define the
	 * 			structure of a part of the earth.
	 */
	class StructuralOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~StructuralOrganizationInterpretation() = default;

		bool isStructural() const final { return true; }

		/**
		 * Adds a fault interpretation to this structural organization interpretation.
		 *
		 * @exception	std::invalid_argument	If <tt>faultInterpretation == nullptr</tt>.
		 *
		 * @param [in]	faultInterpretation	A fault interpretation.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackFaultInterpretation(FaultInterpretation * faultInterpretation) = 0;

		/**
		 * Gets the fault interpretations count.
		 *
		 * @exception	std::range_error	If the fault interpretation count is strictly greater than
		 * 									unsigned int max.
		 *
		 * @returns	The fault interpretations count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getFaultInterpretationCount() const = 0;

		/**
		 * Gets the DOR of a given fault interpretation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getFaultInterpretationCount().
		 *
		 * @param 	index	Zero-based index of the fault interpretation for which we look for the DOR.
		 *
		 * @returns	The DOR of the fault interpretation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getFaultInterpretationDor(unsigned int index) const = 0;

		/**
		 * Gets a given fault interpretation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getFaultInterpretationCount().
		 *
		 * @param 	index	Zero-based index of the fault interpretation we look for.
		 *
		 * @returns	The fault interpretation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT FaultInterpretation* getFaultInterpretation(unsigned int index) const;

		/**
		 * Adds a horizon interpretation at a given rank of this structural organization interpretation.
		 *
		 * @exception	std::invalid_argument	If <tt>horizonInterpretation == nullptr</tt>.
		 *
		 * @param [in]	horizonInterpretation	A horizon interpretation.
		 * @param 	  	stratigraphicRank	 	The rank of the horizon interpretation within this
		 * 										structural organization.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackHorizonInterpretation(HorizonInterpretation * horizonInterpretation, int stratigraphicRank) = 0;

		/**
		 * Gets the horizon interpretations count.
		 *
		 * @exception	std::range_error	If the horizon interpretation count is strictly greater than
		 * 									unsigned int max.
		 *
		 * @returns	The horizon interpretations count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getHorizonInterpretationCount() const = 0;

		/**
		 * Gets the DOR of a given horizon interpretation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getHorizonInterpretationCount().
		 *
		 * @param 	index	Zero-based index of the horizon interpretation for which we look for the DOR.
		 *
		 * @returns	The DOR of the horizon interpretation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getHorizonInterpretationDor(unsigned int index) const = 0;

		/**
		 * Gets a given horizon interpretation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getHorizonInterpretationCount().
		 *
		 * @param 	index	Zero-based index of the horizon interpretation we look for.
		 *
		 * @returns	The horizon interpretation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT HorizonInterpretation* getHorizonInterpretation(unsigned int index) const;

		/**
		 * Adds a frontier interpretation to this structural organization interpretation as a top.
		 *
		 * @exception	std::invalid_argument	If <tt>topFrontierInterpretation == nullptr</tt>.
		 *
		 * @param [in]	topFrontierInterpretation	A top frontier interpretation.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackTopFrontierInterpretation(AbstractFeatureInterpretation * topFrontierInterpretation) = 0;

		/**
		 * Gets the top frontier interpretations count.
		 *
		 * @exception	std::range_error	If the top frontier interpretation count is strictly greater
		 * 									than unsigned int max.
		 *
		 * @returns	The top frontier interpretations count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getTopFrontierInterpretationCount() const = 0;

		/**
		 * Gets the DOR of a given top frontier interpretation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getTopFrontierInterpretationCount().
		 *
		 * @param 	index	Zero-based index of the top frontier interpretation for which we look for the
		 * 					DOR.
		 *
		 * @returns	The DOR of the top frontier interpretation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getTopFrontierInterpretationDor(unsigned int index) const = 0;

		/**
		 * Gets a given top frontier interpretation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getTopFrontierInterpretationCount().
		 *
		 * @param 	index	Zero-based index of the top frontier interpretation we look for.
		 *
		 * @returns	The top frontier interpretation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT AbstractFeatureInterpretation* getTopFrontierInterpretation(unsigned int index) const;

		/**
		 * Adds a frontier interpretation to this structural organization interpretation as a bottom.
		 *
		 * @exception	std::invalid_argument	If <tt>bottomFrontierInterpretation == nullptr</tt>.
		 *
		 * @param [in]	bottomFrontierInterpretation	A bottom frontier interpretation.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackBottomFrontierInterpretation(AbstractFeatureInterpretation * bottomFrontierInterpretation) = 0;

		/**
		 * Gets the bottom frontier interpretations count.
		 *
		 * @exception	std::range_error	If the bottom frontier interpretation count is strictly
		 * 									greater than unsigned int max.
		 *
		 * @returns	The bottom frontier interpretations count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getBottomFrontierInterpretationCount() const = 0;

		/**
		 * Gets the DOR of a given bottom frontier interpretation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt>
		 * 									getBottomFrontierInterpretationCount().
		 *
		 * @param 	index	Zero-based index of the bottom frontier interpretation for which we look for
		 * 					the DOR.
		 *
		 * @returns	The DOR of the bottom frontier interpretation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getBottomFrontierInterpretationDor(unsigned int index) const = 0;

		/**
		 * Gets a given bottom frontier interpretation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt>
		 * 									getBottomFrontierInterpretationCount().
		 *
		 * @param 	index	Zero-based index of the bottom frontier interpretation we look for.
		 *
		 * @returns	The bottom frontier interpretation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT AbstractFeatureInterpretation* getBottomFrontierInterpretation(unsigned int index) const;

		/**
		 * Adds a frontier interpretation to this structural organization interpretation as a side.
		 *
		 * @exception	std::invalid_argument	If <tt>sideFrontierInterpretation == nullptr</tt>.
		 *
		 * @param [in]	sideFrontierInterpretation	A side frontier interpretation.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackSideFrontierInterpretation(AbstractFeatureInterpretation * sideFrontierInterpretation) = 0;

		/**
		 * Gets the side frontier interpretations count.
		 *
		 * @exception	std::range_error	If the side frontier interpretation count is strictly greater
		 * 									than unsigned int max.
		 *
		 * @returns	The side frontier interpretations count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getSideFrontierInterpretationCount() const = 0;

		/**
		 * Gets the DOR of a given side frontier interpretation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt>
		 * 									getSideFrontierInterpretationCount().
		 *
		 * @param 	index	Zero-based index of the side frontier interpretation for which we look for
		 * 					the DOR.
		 *
		 * @returns	The DOR of the side frontier interpretation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getSideFrontierInterpretationDor(unsigned int index) const = 0;

		/**
		 * Gets a given side frontier interpretation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt>
		 * 									getSideFrontierInterpretationCount().
		 *
		 * @param 	index	Zero-based index of the side frontier interpretation we look for.
		 *
		 * @returns	The side frontier interpretation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT AbstractFeatureInterpretation* getSideFrontierInterpretation(unsigned int index) const;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "StructuralOrganizationInterpretation";

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
		void loadTargetRelationships() final;
	};
}
