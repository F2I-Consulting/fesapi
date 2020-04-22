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

/** @brief */
namespace RESQML2_0_1_NS
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
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT GridConnectionSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			RESQML2_NS::GridConnectionSetRepresentation(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	interp	The interpretation the instance represents.
		 * @param 		  	guid  	A guid for the instance to create.
		 * @param 		  	title 	A title for the instance to create.
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
		GridConnectionSetRepresentation(gsoap_resqml2_0_1::_resqml20__GridConnectionSetRepresentation* fromGsoap) : RESQML2_NS::GridConnectionSetRepresentation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~GridConnectionSetRepresentation() {}

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;

		/**
		 * Get the cell index pair count of this grid connection representation
		 *
		 * @returns	The cell index pair count.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getCellIndexPairCount() const final;

		/**
		 * Get the cell index pair count of this grid connection representation
		 *
		 * @param [in,out]	cellIndexPairs	If non-null, the cell index pairs.
		 *
		 * @returns	The cell index pairs.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getCellIndexPairs(ULONG64 * cellIndexPairs) const final;

		/**
		 * Get the cell index pairs count which correspond to a particular interpretation.
		 *
		 * @param 	interpretationIndex	The index of the interpretation in the collection of feature
		 * 								interpretation of this grid connection set.
		 *
		 * @returns	The cell index pair count from interpretation index.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getCellIndexPairCountFromInterpretationIndex(unsigned int interpretationIndex) const final;

		/**
		 * Indicates wether the cell connection are associated to interpretation or not.
		 *
		 * @returns	True if associated to interpretations, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAssociatedToInterpretations() const final;

		/**
		 * Get the interpretation index cumulative count of this grid connection representation The
		 * count of cumulativeCount must be getCellIndexPairCount().
		 *
		 * @param [in,out]	cumulativeCount	If non-null, number of cumulatives.
		 */
		DLL_IMPORT_OR_EXPORT void getInterpretationIndexCumulativeCount(unsigned int * cumulativeCount) const final;

		/**
		 * Get the interpretation indices of this grid connection representation The count of
		 * interpretationIndices is the last value of the array returning by
		 * getInterpretationIndexCumulativeCount.
		 *
		 * @param [in,out]	interpretationIndices	If non-null, the interpretation indices.
		 */
		DLL_IMPORT_OR_EXPORT void getInterpretationIndices(unsigned int * interpretationIndices) const final;

		/**
		 * Returns the null value for interpretation index.
		 *
		 * @returns	The interpretation index null value.
		 */
		DLL_IMPORT_OR_EXPORT LONG64 getInterpretationIndexNullValue() const final;

		/**
		 * Get the cell index pairs, the grid index pairs (optional) and the local face pairs (optional)
		 * which correspond to a particular  interpretation.
		 *
		 * @param [in,out]	cellIndexPairs	   	Mandatory. Must be allocated with
		 * 										getCellIndexPairCountFromIndex first.
		 * @param [in,out]	gridIndexPairs	   	Optional (put null if you don't want it). Must be
		 * 										allocated with getCellIndexPairCountFromIndex first.
		 * @param [in,out]	localFaceIndexPairs	Optional (put null if you don't want it). Must be
		 * 										allocated with getCellIndexPairCountFromIndex first.
		 * @param 		  	interpretationIndex	The index of the interpretation in the collection of
		 * 										feature interpretation of this grid connection set.
		 */
		DLL_IMPORT_OR_EXPORT void getGridConnectionSetInformationFromInterpretationIndex(ULONG64 * cellIndexPairs, unsigned short * gridIndexPairs, int * localFaceIndexPairs, unsigned int interpretationIndex) const final;

		/**
		* Get the UUID of a particular interpretation of this grid connection set.
		* @param interpretationIndex The index of the interpretation in the collection of feature interpretation of this grid connection set.
		*/
		DLL_IMPORT_OR_EXPORT std::string getInterpretationUuidFromIndex(unsigned int interpretationIndex) const final;

		/**
		 * Get the count of interpretations in this grid connection set.
		 *
		 * @returns	The interpretation count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getInterpretationCount() const final;

		/**
		 * Indicates if the grid connection set representation contains information on the connected
		 * faces of the two cells.
		 *
		 * @returns	True if local face per cell, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasLocalFacePerCell() const final;

		/**
		 * Get the local face cell index pairs of this grid connection representation.
		 *
		 * @param [in,out]	localFacePerCellIndexPairs	Tis array must be pre allocated and won't be
		 * 												deallocated byt fesapi. The count of
		 * 												localFacePerCellIndexPairs must be
		 * 												getCellIndexPairCount()*2.
		 *
		 * @returns	The used null value in localFacePerCellIndexPairs.
		 */
		DLL_IMPORT_OR_EXPORT LONG64 getLocalFacePerCellIndexPairs(int * localFacePerCellIndexPairs) const final;

		/**
		 * Indicates if the grid connection set representation is based on several grids.
		 *
		 * @returns	True if based on multi grids, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isBasedOnMultiGrids() const final;

		/**
		 * Get the grid index pairs of this grid connection representation The count of gridIndexPairs
		 * must be getCellIndexPairCount()*2.
		 *
		 * @param [in,out]	gridIndexPairs	If non-null, the grid index pairs.
		 */
		DLL_IMPORT_OR_EXPORT void getGridIndexPairs(unsigned short * gridIndexPairs) const final;

		/**
		 * Set the cell index pairs of the grid connections representation using some exisiting hdf5
		 * datasets.
		 *
		 * @param 		  	cellIndexPairCount	  	The count of cell index pair. It is half of all the
		 * 											stored numerical values.
		 * @param 		  	cellIndexPair		  	The HDF dataset path where we can find all the cell
		 * 											index pair in a 1d Array where the cell indices go
		 * 											faster than the pair.
		 * @param 		  	cellIndexPairNullValue	The integer null value used in the hdf cell index
		 * 											pair dataset.
		 * @param [in,out]	proxy				  	The HDF proxy where the numerical values (cell
		 * 											indices) are stored.
		 * @param 		  	gridIndexPairNullValue	(Optional) The integer null value used in the hdf
		 * 											grid index pair dataset.
		 * @param 		  	gridIndexPair		  	(Optional) The HDF dataset path where we can find all
		 * 											the grid index pair in a 1d Array where the grid
		 * 											indices go faster than the pair. The grid at an index
		 * 											must correspond to the cell at the same index in the
		 * 											cellIndexPair array.
		 */
		DLL_IMPORT_OR_EXPORT void setCellIndexPairsUsingExistingDataset(ULONG64 cellIndexPairCount, const std::string & cellIndexPair, LONG64 cellIndexPairNullValue,
			EML2_NS::AbstractHdfProxy * proxy, LONG64 gridIndexPairNullValue = -1, const std::string & gridIndexPair = "") final;

		/**
		 * The numerical values
		 * 2 x #Connections array of local face-per-cell indices for (Cell1,Cell2) for each connection.
		 * Local face-per-cell indices are used because global face indices need not have been defined.
		 * The numerical values are already stored in an existing hdf5 dataset. Null value = -1 by
		 * documentation.
		 *
		 * @param 		  	localFacePerCellIndexPair	The HDF dataset path where we can find all the
		 * 												local Face Per CellIndex Pair in a 1d Array.
		 * @param 		  	nullValue				 	The null value.
		 * @param [in,out]	proxy					 	The HDF proxy where the numerical values (cell
		 * 												indices) are stored.
		 */
		DLL_IMPORT_OR_EXPORT void setLocalFacePerCellIndexPairsUsingExistingDataset(const std::string & localFacePerCellIndexPair, LONG64 nullValue, EML2_NS::AbstractHdfProxy * proxy) final;

		/**
		 * For each connection in the grid connection set representation, allow to map zero or one
		 * feature interpretation. TODO: Resqml allows to map with more than one feature interpretation.
		 *
		 * @param [in,out]	interpretationIndices	 	For each connection, the index of the
		 * 												corresponding interpretation in the
		 * 												interpretation set of this grid connection. The
		 * 												count of this array is given by the next
		 * 												parameter.
		 * @param 		  	interpretationIndiceCount	The count of interpretation indices.
		 * @param 		  	nullValue				 	The null value must be used as the corresponding
		 * 												interpretation index for each connection which
		 * 												are not associated to any interpretation.
		 * @param [in,out]	proxy					 	The Hdf proxy where the numerical values will be
		 * 												stored.
		 */
		DLL_IMPORT_OR_EXPORT void setConnectionInterpretationIndices(unsigned int const* interpretationIndices, unsigned int interpretationIndiceCount, unsigned int nullValue, EML2_NS::AbstractHdfProxy * proxy) final;

		/**
		 * Get the count of the supporting grid representations of this grid connection representation.
		 *
		 * @returns	The supporting grid representation count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getSupportingGridRepresentationCount() const final;

		/**
		* Get one of the supporting grid representation dor of this grid connection representation.
		*/
		COMMON_NS::DataObjectReference getSupportingGridRepresentationDor(unsigned int index) const final;

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
