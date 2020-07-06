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

#include <limits>

#include "AbstractRepresentation.h"

namespace RESQML2_NS
{
	/**
	 * @brief	Proxy class for a grid connection set representation. This representation consists of
	 * 			a list of connections between grid cells, potentially on different grids.
	 * 			
	 * 			Connections are in the form of (Grid,Cell,Face)1&lt;=&gt;(Grid,Cell,Face)2 and are
	 * 			stored as three integer pair arrays (one grid index pair array, one cell index pair
	 * 			array and one face index pair array) corresponding to these six elements.
	 * 			
	 * 			Grid connection sets are the preferred means of representing faults on a grid. The
	 * 			use of cell-face-pairs is more complete than single cell- faces, which are missing a
	 * 			corresponding cell face entry, and only provide an incomplete representation of the
	 * 			topology of a fault. Unlike what is sometimes the case in reservoir simulation
	 * 			software, RESQML does not distinguish between standard and non-standard connections.
	 * 			Within RESQML, if a grid connection corresponds to a "nearest neighbor" as defined by
	 * 			the cell indices, then it is never additive to the implicit nearest neighbor
	 * 			connection.
	 * 			
	 * 			BUSINESS RULE: A single cell- face-pair should not appear within more than a single
	 * 			grid connection set. This rule is designed to simplify the interpretation of
	 * 			properties assigned to multiple grid connection sets, which might otherwise have the
	 * 			same property defined more than once on a single connection, with no clear means of
	 * 			resolving the multiple values.
	 */
	class GridConnectionSetRepresentation : public AbstractRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~GridConnectionSetRepresentation() {}

		/**
		 * Gets the cell index pair count of this grid connection set representation.
		 *
		 * @returns	The cell index pair count.
		 */
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getCellIndexPairCount() const = 0;

		/**
		 * Gets the cell index pairs of this grid connection set representation
		 *
		 * @exception	logic_error	If the cell index pairs are not stored in a HDF5 integer array.
		 *
		 * @param [out]	cellIndexPairs	A buffer for receiving the cell index pairs. It must be
		 * 								preallocated with a size of <tt>2 * getCellIndexPairCount()</tt>.
		 * 								Two consecutive values <tt>cellIndexPairs[i]</tt> and
		 * 								<tt>cellIndexPairs[i+1]</tt> constitute a pair of cell index.
		 *
		 * @returns	The null value.
		 */
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getCellIndexPairs(ULONG64 * cellIndexPairs) const = 0;

		/**
		 * @brief	Gets the count of cell index pairs which correspond to a particular interpretation.
		 *
		 * @exception	std::invalid_argument	If this grid connection set representation does not
		 * 										contain any (fault) interpretation association.
		 * @exception	std::invalid_argument	If the HDF5 library could not read the count of
		 * 										interpretation indices associated to this grid connection
		 * 										set representation.
		 * @exception	std::logic_error	 	If the intepretation indices are not stored in a HDF5
		 * 										integer array.
		 * @exception	std::out_of_range	 	If @p interpretationIndex is out of range.
		 *
		 * @param 	interpretationIndex	The index of an interpretation in the collection of feature
		 * 								interpretation of this grid connection set.
		 *
		 * @returns	The count of cell index pairs which correspond to the interpretation at index @p
		 * 			interpretationIndex.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getCellIndexPairCountFromInterpretationIndex(unsigned int interpretationIndex) const = 0;

		/**
		 * Indicates whether the cell connections are associated to interpretation or not.
		 *
		 * @returns	True if associated to interpretations, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAssociatedToInterpretations() const = 0;

		/**
		 * Gets the (fault) interpretation index cumulative counts of this grid connection
		 * representation.
		 *
		 * @exception	std::invalid_argument	If this grid connection set representation does not
		 * 										contain any (fault) interpretation association.
		 * @exception	std::logic_error	 	If the intepretation indices cumulative counts are not
		 * 										stored in a HDF5 integer array.
		 *
		 * @param [out]	cumulativeCount	A buffer for receiving the cumulative counts. Must be
		 * 								preallocated with a size of getCellIndexPairCount(). The number
		 * 								of interpretations associated to the connection at index @c i is
		 * 								<tt>cumulativeCount[i]</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getInterpretationIndexCumulativeCount(unsigned int * cumulativeCount) const = 0;

		/**
		 * Gets the (fault) interpretation indices of this grid connection representation.
		 *
		 * @exception	std::invalid_argument	If this grid connection set representation does not
		 * 										contain any (fault) interpretation association.
		 * @exception	std::logic_error	 	If the intepretation indices are not stored in a HDF5
		 * 										integer array.
		 *
		 * @param [out]	interpretationIndices	A buffer for receiving the interpretation indices. It
		 * 										must be preallocated with a size equals to the last value
		 * 										of @c cumulativeCount after calling
		 * 										<tt>getInterpretationIndexCumulativeCount(cumulativeCount).</tt>
		 */
		DLL_IMPORT_OR_EXPORT virtual void getInterpretationIndices(unsigned int * interpretationIndices) const = 0;

		/**
		 * Gets the null value for interpretation index.
		 *
		 * @exception	std::invalid_argument	If this grid connection set representation does not
		 * 										contain any (fault) interpretation association.
		 * @exception	std::logic_error	 	If the intepretation indices are not stored in a HDF5
		 * 										integer array.
		 *
		 * @returns	The interpretation index null value.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getInterpretationIndexNullValue() const = 0;

		/**
		 * Gets the cell index pairs, the grid index pairs (optional) and the local face index pairs
		 * (optional) which correspond to a particular interpretation.
		 *
		 * @exception	std::invalid_argument	If this grid connection set representation does not
		 * 										contain any (fault) interpretation association.
		 * @exception	std::logic_error	 	If the intepretation indices or interpretation indices
		 * 										cumulative counts are not stored in a HDF5 integer array.
		 *
		 * @param [out]	  	cellIndexPairs	   	Mandatory buffer to receive the cell index pairs. Must be
		 * 										preallocated with
		 * 										<tt>getCellIndexPairCountFromInterpretationIndex(interpretationIndex)</tt>.
		 * @param [in,out]	gridIndexPairs	   	Optional buffer to receive the grid index pairs. Please
		 * 										set to @p nullptr for not collecting these pairs. Must be
		 * 										preallocated with
		 * 										<tt>getCellIndexPairCountFromInterpretationIndex(interpretationIndex)</tt>.
		 * @param [in,out]	localFaceIndexPairs	Optional buffer to receive the local face index pairs.
		 * 										Please set to @p nullptr for not collecting these pairs.
		 * 										Must be preallocated with
		 * 										<tt>getCellIndexPairCountFromInterpretationIndex(interpretationIndex)</tt>.
		 * @param 		  	interpretationIndex	The index of an interpretation in the collection of
		 * 										feature interpretation of this grid connection set.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getGridConnectionSetInformationFromInterpretationIndex(ULONG64 * cellIndexPairs, unsigned short * gridIndexPairs, int * localFaceIndexPairs, unsigned int interpretationIndex) const = 0;

		/**
		 * Gets the UUID of a particular (fault) interpretation of this grid connection set.
		 *
		 * @exception	std::invalid_argument	If this grid connection set representation does not
		 * 										contain fault interpretation association.
		 * @exception	std::invalid_argument	If the associated feature interpretation at position @p
		 * 										interpretationIndex is not a fault one. This is legal but
		 * 										not yet implemented.
		 * @exception	std::out_of_range	 	If @p interpretationIndex is out of range.
		 *
		 * @param 	interpretationIndex	The index of a (fault) interpretation in the collection of
		 * 								feature interpretation of this grid connection set.
		 *
		 * @returns	The UUID of the (fault) interpretation at index @p interpretationIndex.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getInterpretationUuidFromIndex(unsigned int interpretationIndex) const = 0;

		/**
		 * Gets a particular (fault) interpretation of this grid connection set.
		 *
		 * @exception	std::invalid_argument	If this grid connection set representation does not
		 * 										contain fault interpretation association.
		 * @exception	std::invalid_argument	If the associated feature interpretation at position @p
		 * 										interpretationIndex is not a fault one. This is legal but
		 * 										not yet implemented.
		 * @exception	std::out_of_range	 	If @p interpretationIndex is out of range.
		 *
		 * @param 	interpretationIndex	The index of a (fault) interpretation in the collection of
		 * 								feature interpretation of this grid connection set.
		 *
		 * @returns	The (fault) interpretation at index @p interpretationIndex.
		 */
		DLL_IMPORT_OR_EXPORT class AbstractFeatureInterpretation* getInterpretationFromIndex(unsigned int interpretationIndex) const;

		/**
		 * Get the count of interpretations in this grid connection set.
		 *
		 * @exception	range_error	If the count of associated interpretations is strictly greater than
		 * 							unsigned int.
		 *
		 * @returns	The interpretation count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getInterpretationCount() const = 0;

		/**
		 * Indicates if this grid connection set representation contains information on the connected
		 * faces of the cell pairs.
		 *
		 * @returns	True if there exists information on connected faces, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool hasLocalFacePerCell() const = 0;

		/**
		 * Gets the local face per cell index pairs of this grid connection representation. Please check
		 * that this grid connection set representation has local face per cell index pairs thanks to
		 * hasLocalFacePerCell() before calling this method.
		 *
		 * @exception	std::invalid_argument	If this representation has no local face per cell pair.
		 * @exception	std::logic_error	 	If the local face per cell index pairs are not stored
		 * 										in a HDF5 integer array.
		 *
		 * @param [out]	localFacePerCellIndexPairs	A buffer for receiving the local face per cell index
		 * 											pairs. It must be preallocated with a size of
		 * 											<tt>getCellIndexPairCount()*2</tt> and won't be freed
		 * 											by fesapi.
		 *
		 * @returns	The null value used in @p localFacePerCellIndexPairs.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getLocalFacePerCellIndexPairs(int * localFacePerCellIndexPairs) const = 0;

		/**
		 * Indicates if this grid connection set representation is based on several grids.
		 *
		 * @returns	True if it is based on several grids, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isBasedOnMultiGrids() const = 0;

		/**
		 * Gets the grid index pairs of this grid connection representation. Please check that this grid
		 * connection set representation is based on several grids thanks to isBasedOnMultiGrids()
		 * before calling this method.
		 *
		 * @exception	std::invalid_argument	If this representation is not based on several grids.
		 * @exception	std::logic_error	 	If the grid index pairs are not stored in a HDF5 integer
		 * 										array.
		 *
		 * @param [out]	gridIndexPairs	A buffer for receiving the grid index pairs. It must be
		 * 								preallocated with a size <tt>getCellIndexPairCount()*2</tt> and
		 * 								won't be freed by fesapi.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getGridIndexPairs(unsigned short * gridIndexPairs) const = 0;

		/**
		 * Sets the cell index pairs of this grid connection set representation using some existing HDF
		 * datasets.
		 *
		 * @exception	std::invalid_argument	If @p cellIndexPairCount is 0.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 	  	cellIndexPairCount	  	The count of cell index pairs. It is half the size of the
		 * 										1d array containing the cell index pairs (and of the one
		 * 										containing grid index pairs if there is one).
		 * @param 	  	cellIndexPair		  	The HDF dataset path where we can find all the cell index
		 * 										pairs in a 1d array where the cell indices go faster than
		 * 										the pair.
		 * @param 	  	cellIndexPairNullValue	The integer null value used in the HDF cell index pair
		 * 										dataset.
		 * @param [in]	proxy				  	The HDF proxy where the numerical values (cell indices)
		 * 										are stored. If @c nullptr, then the default HDF proxy of
		 * 										the repository will be used.
		 * @param 	  	gridIndexPairNullValue	(Optional) The integer null value used in the HDF grid
		 * 										index pair dataset.
		 * @param 	  	gridIndexPair		  	(Optional) The HDF dataset path where we can find all the
		 * 										grid index pairs in a 1d array where the grid indices go
		 * 										faster than the pair. The grid at an index must
		 * 										correspond to the cell at the same index in the
		 * 										@p cellIndexPair array. If empty string (default), then no grid
		 * 										index pair will be set and parameter @p
		 * 										gridIndexPairNullValue will be unused.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setCellIndexPairsUsingExistingDataset(ULONG64 cellIndexPairCount, const std::string & cellIndexPair, LONG64 cellIndexPairNullValue, EML2_NS::AbstractHdfProxy * proxy, LONG64 gridIndexPairNullValue = -1, const std::string & gridIndexPair = "") = 0;

		/**
		 * @brief	Sets the cell index pairs of this grid connection set representation.
		 *
		 * @exception	std::invalid_argument	If @p cellIndexPairCount is 0.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If @p cellIndexPairNullValue is strictly greater than
		 * 										ULONG64 max. The XML null value cannot be greater than a
		 * 										64 bits signed integer cause of gSOAP mappings.
		 *
		 * @param 		  	cellIndexPairCount	  	The count of cell index pairs. It is half the size of
		 * 											@p cellIndexPair (and of @p gridIndexPair if used).
		 * @param [in]	  	cellIndexPair		  	All the cell index pair in a 1d array where the cell
		 * 											indices go faster than the pair.
		 * @param 		  	cellIndexPairNullValue	The integer null value used in @p cellIndexPair.
		 * @param [in,out]	proxy				  	The HDF proxy where the numerical values (cell
		 * 											indices) are stored. If @c nullptr, then the default
		 * 											HDF proxy of the repository will be used.
		 * @param 		  	gridIndexPairNullValue	(Optional) The integer null value used in @p
		 * 											gridIndexPair.
		 * @param [in]	  	gridIndexPair		  	(Optional) All the grid index pair in a 1d array
		 * 											where the grid indices go faster than the pair. The
		 * 											grid at an index must correspond to the cell at the
		 * 											same index in the @p cellIndexPair array.
		 */
		DLL_IMPORT_OR_EXPORT void setCellIndexPairs(ULONG64 cellIndexPairCount, ULONG64 const* cellIndexPair, ULONG64 cellIndexPairNullValue, EML2_NS::AbstractHdfProxy * proxy, unsigned short gridIndexPairNullValue = (std::numeric_limits<unsigned short>::max)(), unsigned short * gridIndexPair = nullptr);

		/**
		 * @brief	Sets the local face per cell index pairs of this grid connection set representation.
		 * 			Local face-per-cell indices are used because global face indices need not have been
		 * 			defined. The numerical values are already stored in an existing hdf5 dataset. Null
		 * 			value = -1 according to documentation.
		 *
		 * @exception	std::invalid_argument	If <tt>proxy == nullptr</tt> and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	localFacePerCellIndexPair	The HDF dataset path where we can find all the
		 * 												local Face Per CellIndex Pair in a 1d array. The
		 * 												size of the numerical values is 2 times the
		 * 												number of connections array of local face-per-
		 * 												cell indices for (Cell1,Cell2) for each
		 * 												connection.
		 * @param 		  	nullValue				 	The null value.
		 * @param [in,out]	proxy					 	The HDF proxy where the numerical values (cell
		 * 												indices) are stored. if @c nullptr, then the
		 * 												repository default HDF proxy will be used.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setLocalFacePerCellIndexPairsUsingExistingDataset(const std::string & localFacePerCellIndexPair, LONG64 nullValue, EML2_NS::AbstractHdfProxy * proxy) = 0;

		/**
		 * @brief Sets the local face per cell index pairs of this grid connection set representation. Local
		 * face-per-cell indices are used because global face indices need not have been defined. The
		 * numerical values will be written as a new HDF5 dataset in an existing HDF5 file.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	cellIndexPairCount		 	The count of cell index pair. It is half the size
		 * 												of @p localFacePerCellIndexPair.
		 * @param [in]	  	localFacePerCellIndexPair	All the local face per cell index pairs in a 1d
		 * 												array where the local face per cell indices go
		 * 												faster than the pair. The local face per cell at
		 * 												an index must correspond to the cell at the same
		 * 												index in the 1d array containing the cell index
		 * 												pairs.
		 * @param 		  	nullValue				 	The null value in @p localFacePerCellIndexPair.
		 * @param [in,out]	proxy					 	The HDF proxy where the numerical values (cell
		 * 												indices) are stored. If @c nullptr, then the
		 * 												default HDF proxy of the repository will be used.
		 */
		DLL_IMPORT_OR_EXPORT void setLocalFacePerCellIndexPairs(ULONG64 cellIndexPairCount, int const* localFacePerCellIndexPair, int nullValue, EML2_NS::AbstractHdfProxy * proxy);

		/**
		 * For each connection in this grid connection set representation, allows to map zero or one
		 * feature interpretation. RESQML allows to map with more than one feature interpretation but
		 * this feature is not implemented yet.
		 *
		 * @exception	std::invalid_argument	If <tt>proxy == nullptr</tt>.
		 *
		 * @param [in]	  	interpretationIndices	 	For each connection, the index of the
		 * 												corresponding interpretation in the
		 * 												interpretation set of this grid connection set.
		 * 												The count of this array is @p
		 * 												interpretationIndiceCount.
		 * @param 		  	interpretationIndiceCount	The count of interpretation indices.
		 * @param 		  	nullValue				 	The null value must be used as the corresponding
		 * 												interpretation index for each connection which is
		 * 												not associated to any interpretation.
		 * @param [in,out]	proxy					 	The Hdf proxy where the numerical values will be
		 * 												stored.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setConnectionInterpretationIndices(unsigned int const* interpretationIndices, unsigned int interpretationIndiceCount, unsigned int nullValue, EML2_NS::AbstractHdfProxy * proxy) = 0;

		/**
		 * Pushes back an interpretation which can be mapped with some connections.
		 *
		 * @exception	std::invalid_argument	If @p interp is @c nullptr.
		 *
		 * @param [in]	interp	The interpretation to push back.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackInterpretation(class AbstractFeatureInterpretation* interp);

		/**
		 * Pushes back a grid representation which is one of the support of this representation. Pushes
		 * back this representation as a grid connection information of the grid representation as well.
		 *
		 * @exception	std::invalid_argument	If @p supportingGridRep is @c nullptr.
		 *
		 * @param [in]	supportingGridRep	The supporting grid representation to push back.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackSupportingGridRepresentation(class AbstractGridRepresentation * supportingGridRep);

		/**
		 * Gets the count of supporting grid representations of this grid connection representation.
		 *
		 * @exception	std::range_error	If the count of supporting grid representations is strictly
		 * 									greater than unsigned int maximum value.
		 *
		 * @returns	The supporting grid representation count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getSupportingGridRepresentationCount() const = 0;

		/**
		 * Gets the supporting grid representation located at a specific index of this grid connection set
		 * representation.
		 * 
		 * @exception std::out_of_range If @p index is out of range.
		 * 								
		 * @param	index	Zero-based index of the supporting grid representation we look for.
		 * 
		 * @returns The supporting grid representation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT class AbstractGridRepresentation* getSupportingGridRepresentation(unsigned int index) const;

		/**
		 * Gets the data object reference of the supporting grid representation located at a specific
		 * index of this grid connection set representation.
		 *
		 * @exception	std::out_of_range	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the supporting grid representation we look for.
		 *
		 * @returns	The data object reference of the supporting grid representation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getSupportingGridRepresentationDor(unsigned int index) const = 0;

		/** Please do note use: not implemented yet. */
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(unsigned int patchIndex) const override;

		/** Please do note use: not implemented yet. */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const override;

		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const override {return 1;}

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const override { return XML_TAG; }

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT GridConnectionSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			AbstractRepresentation(partialObject) {}

		/** Creates an instance of this class in a gsoap context. */
		GridConnectionSetRepresentation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		GridConnectionSetRepresentation(gsoap_resqml2_0_1::_resqml20__GridConnectionSetRepresentation* fromGsoap) : AbstractRepresentation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		GridConnectionSetRepresentation(gsoap_eml2_3::_resqml22__GridConnectionSetRepresentation* fromGsoap) : AbstractRepresentation(fromGsoap) {}

		/**
		 * Pushes a back XML interpretation
		 *
		 * @param [in,out]	interp	If non-null, the interp.
		 */
		virtual void pushBackXmlInterpretation(class AbstractFeatureInterpretation* interp) = 0;

		/**
		 * Pushes a back XML supporting grid representation
		 *
		 * @param [in,out]	supportingGridRep	If non-null, the supporting grid rep.
		 */
		virtual void pushBackXmlSupportingGridRepresentation(class AbstractGridRepresentation * supportingGridRep) = 0;

		/** Loads target relationships */
		void loadTargetRelationships() final;
	};
}
