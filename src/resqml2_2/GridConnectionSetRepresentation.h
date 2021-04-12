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

#include "../resqml2/GridConnectionSetRepresentation.h"

namespace RESQML2_2_NS
{
	/** A grid connection set representation. */
	class GridConnectionSetRepresentation final : public RESQML2_NS::GridConnectionSetRepresentation
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT GridConnectionSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			RESQML2_NS::GridConnectionSetRepresentation(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The interpretation the instance represents.
		 * @param 	  	guid  	A guid for the instance to create.
		 * @param 	  	title 	A title for the instance to create.
		 */
		GridConnectionSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
                const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	repo 	The repo where this instance will be stored.
		 * @param 		  	guid 	A guid for the instance to create.
		 * @param 		  	title	A title for the instance to create.
		 */
		GridConnectionSetRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		GridConnectionSetRepresentation(gsoap_eml2_3::_resqml22__GridConnectionSetRepresentation* fromGsoap) : RESQML2_NS::GridConnectionSetRepresentation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~GridConnectionSetRepresentation() = default;

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;

		DLL_IMPORT_OR_EXPORT uint64_t getCellIndexPairCount() const final;

		DLL_IMPORT_OR_EXPORT int64_t getCellIndexPairs(int64_t * cellIndexPairs) const final;

		DLL_IMPORT_OR_EXPORT unsigned int getCellIndexPairCountFromInterpretationIndex(unsigned int interpretationIndex) const final;

		DLL_IMPORT_OR_EXPORT bool isAssociatedToInterpretations() const final;

		DLL_IMPORT_OR_EXPORT void getInterpretationIndexCumulativeCount(unsigned int * cumulativeCount) const final;

		DLL_IMPORT_OR_EXPORT void getInterpretationIndices(unsigned int * interpretationIndices) const final;

		DLL_IMPORT_OR_EXPORT int64_t getInterpretationIndexNullValue() const final;

		DLL_IMPORT_OR_EXPORT void getGridConnectionSetInformationFromInterpretationIndex(uint64_t * cellIndexPairs, unsigned short * gridIndexPairs, int * localFaceIndexPairs, unsigned int interpretationIndex) const final;

		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getInterpretationDorFromIndex(unsigned int interpretationIndex) const final;

		DLL_IMPORT_OR_EXPORT unsigned int getInterpretationCount() const final;

		DLL_IMPORT_OR_EXPORT bool hasLocalFacePerCell() const final;

		DLL_IMPORT_OR_EXPORT int64_t getLocalFacePerCellIndexPairs(int * localFacePerCellIndexPairs) const final;

		DLL_IMPORT_OR_EXPORT bool isBasedOnMultiGrids() const final;

		DLL_IMPORT_OR_EXPORT void getGridIndexPairs(unsigned short * gridIndexPairs) const final;

		DLL_IMPORT_OR_EXPORT void setCellIndexPairsUsingExistingDataset(uint64_t cellIndexPairCount, const std::string & cellIndexPair, int64_t cellIndexPairNullValue,
			EML2_NS::AbstractHdfProxy * proxy, int64_t gridIndexPairNullValue = -1, const std::string & gridIndexPair = "") final;

		DLL_IMPORT_OR_EXPORT void setLocalFacePerCellIndexPairsUsingExistingDataset(const std::string & localFacePerCellIndexPair, int64_t nullValue, EML2_NS::AbstractHdfProxy * proxy) final;

		DLL_IMPORT_OR_EXPORT void setConnectionInterpretationIndices(unsigned int const* interpretationIndices, unsigned int interpretationIndiceCount, unsigned int nullValue, EML2_NS::AbstractHdfProxy * proxy) final;

		DLL_IMPORT_OR_EXPORT unsigned int getSupportingGridRepresentationCount() const final;

		COMMON_NS::DataObjectReference getSupportingGridRepresentationDor(unsigned int index) const final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

	protected:

		/**
		 * Initializes this object
		 *
		 * @param [in,out]	repo 	If non-null, the repo.
		 * @param 		  	guid 	Unique identifier.
		 * @param 		  	title	The title.
		 */
		void init(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title);

		/**
		 * Pushes back an interpretation which can be mapped with some connections.
		 *
		 * @param [in,out]	interp	The interpration to push back.
		 */
		void pushBackXmlInterpretation(RESQML2_NS::AbstractFeatureInterpretation* interp);

		/**
		 * Pushes back a grid representation which is one of the support of this representation. And
		 * push back this representation as a grid connection information of the grid representation as
		 * well.
		 *
		 * @param [in,out]	supportingGridRep	If non-null, the supporting grid rep.
		 */
		void pushBackXmlSupportingGridRepresentation(RESQML2_NS::AbstractGridRepresentation * supportingGridRep);
	};
}
