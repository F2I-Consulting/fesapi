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

#include "AbstractColumnLayerGridRepresentation.h"

#include <stdexcept>
#include <map>

namespace RESQML2_NS
{
	/**
	 * @brief	Proxy class for an abstract IJK grid representation. This class is semantically
	 * 			abstract. Technically speaking, it is not an abstract because it can be used in case
	 * 			of partial transfer where we don't know the geometry of the IJK grid.
	 */
	class AbstractIjkGridRepresentation : public RESQML2_NS::AbstractColumnLayerGridRepresentation
	{
	public:

		/** Values that represent geometry kinds. */
		enum geometryKind { UNKNOWN = 0, EXPLICIT = 1, PARAMETRIC = 2, LATTICE = 3, NO_GEOMETRY = 4}; // UNKNOWN exists in case of partial transfer

		/**
		 * Constructor of an IJK grid representation without link to an interpretation.
		 *
		 * @exception	std::invalid_argument	If @p repo is @c nullptr.
		 *
		 * @param [in,out]	repo				A repository which will manage the memory of this
		 * 										instance. It cannot be null.
		 * @param 		  	guid				The guid to set to the ijk grid with no geometry
		 * 										representation. If empty then a new guid will be
		 * 										generated.
		 * @param 		  	title				The title to set to the ijk grid with no geometry
		 * 										representation. If empty then \"unknown\" title will be
		 * 										set.
		 * @param 		  	iCount				Count of cells in the i-direction in the grid.
		 * @param 		  	jCount				Count of cells in the j-direction in the grid.
		 * @param 		  	kCount				Number of layers in the grid.
		 * @param 		  	kGaps				(Optional) Boolean array of length KCellCount-1.
		 *										TRUE if there is a gap after the corresponding layer.
		 *										Won't be freed by FESAPI.
		 * @param [in]		proxy				(Optional) The HDF proxy for writing the @p enabledCells
		 * 										values. If @c nullptr (default), then the default HDF proxy will be
		 * 										used.
		 */
		AbstractIjkGridRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount, bool* kGaps = nullptr, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Constructor of an IJK grid representation with a link to an interpretation.
		 *
		 * @exception	std::invalid_argument	If @p interp is @c nullptr.
		 *
		 * @param [in]	interp					The interpretation this IJK grid represents. It cannot be
		 * 										null.
		 * @param 	  	guid					The guid to set to the ijk grid with no geometry
		 * 										representation. If empty then a new guid will be generated.
		 * @param 	  	title					The title to set to the ijk grid with no geometry
		 * 										representation. If empty then \"unknown\" title will be set.
		 * @param 	  	iCount					Count of cells in the I direction in the grid.
		 * @param 	  	jCount					Count of cells in the J direction in the grid.
		 * @param 	  	kCount					Number of layers in the grid.
		 * @param 	  	kGaps					(Optional) Boolean array of length KCellCount-1.
		 *										TRUE if there is a gap after the corresponding layer.
		 *										Won't be freed by FESAPI.
		 * @param [in]	proxy					(Optional) The HDF proxy for writing the @p enabledCells
		 * 										values. If @c nullptr (default), then the default HDF proxy will be
		 * 										used.
		 */
		AbstractIjkGridRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount, bool* kGaps = nullptr, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Constructor of a truncated IJK grid representation without link to an interpretation.
		 *
		 * @exception	std::invalid_argument	If @p repo is @c nullptr.
		 *
		 * @param [in,out]	repo					A repository which will manage the memory of this
		 * 											instance. It cannot be null.
		 * @param 		  	guid					The guid to set to the ijk grid with no geometry
		 * 											representation. If empty then a new guid will be
		 * 											generated.
		 * @param 		  	title					The title to set to the ijk grid with no geometry
		 * 											representation. If empty then \"unknown\" title will be
		 * 											set.
		 * @param 		  	iCount					Count of cells in the i-direction in the grid.
		 * @param 		  	jCount					Count of cells in the j-direction in the grid.
		 * @param 		  	kCount					Number of layers in the grid.
		 * @param 		  	truncationNodeCount		Number of additional nodes required for the truncation construction.
		 * @param 		  	truncationFaceCount		Number of additional faces required for the split and truncation construction.
		 *											The construction does not modify existing face definitions,
		 *											but instead uses these new faces to redefine the truncated cell geometry. 
		 * @param 		  	truncationCellCount		Number of additional cells required for the truncation construction.
		 *											Parent cells are replaced.
		 */
		/*
		AbstractIjkGridRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount,
			unsigned int truncationNodeCount, unsigned int truncationFaceCount, unsigned int truncationCellCount);
			*/
		/**
		 * Constructor of truncated IJK grid representation with a link to an interpretation.
		 *
		 * @exception	std::invalid_argument	If @p interp is @c nullptr.
		 *
		 * @param [in]	interp					The interpretation this IJK grid represents. It cannot be
		 * 										null.
		 * @param 	  	guid					The guid to set to the ijk grid with no geometry
		 * 										representation. If empty then a new guid will be generated.
		 * @param 	  	title					The title to set to the ijk grid with no geometry
		 * 										representation. If empty then \"unknown\" title will be set.
		 * @param 	  	iCount					Count of cells in the I direction in the grid.
		 * @param 	  	jCount					Count of cells in the J direction in the grid.
		 * @param 	  	kCount					Number of layers in the grid.
		 * @param 	  	withTruncatedPillars	(Optional) True if this IJK grid has some truncated
		 * 										pillars, else false (default).
		 */
		/*
		AbstractIjkGridRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount,
			unsigned int truncationNodeCount, unsigned int truncationFaceCount, unsigned int truncationCellCount);
			*/
		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject			If non-nullptr, the partial object.
		 * @param 	  	withTruncatedPillars	(Optional) True to with truncated pillars.
		 */
		DLL_IMPORT_OR_EXPORT AbstractIjkGridRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject, bool withTruncatedPillars = false);

		/** Destructor. */
		DLL_IMPORT_OR_EXPORT virtual ~AbstractIjkGridRepresentation()
		{
			if (blockInformation != nullptr)
				delete blockInformation;
		}

		/**
		 * Gets the count of cells in the I direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error	If the count is strictly greater than unsigned int max.
		 *
		 * @returns	The count of cell in the I direction.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getICellCount() const;

		/**
		 * Sets the count of cells in the I direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @param 	iCount	The count of cells to set in the I direction.
		 */
		DLL_IMPORT_OR_EXPORT void setICellCount(unsigned int iCount);

		/**
		 * Gets the count of cells in the J direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error	If the count is strictly greater than unsigned int max.
		 *
		 * @returns	The count of cell in the J direction.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getJCellCount() const;

		/**
		 * @brief	Sets the count of cells in the J direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @param 	jCount	The count of cells to set in the J direction.
		 */
		DLL_IMPORT_OR_EXPORT void setJCellCount(unsigned int jCount);

		/**
		 * Gets the total count of cells in the IJK grid.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error	If the count is strictly greater than unsigned int max.
		 *
		 * @returns	The total count of cells in the IJK grid.
		*/
		DLL_IMPORT_OR_EXPORT uint64_t getCellCount() const final { return getICellCount() * getJCellCount() * getKCellCount(); }

		/**
		 * Gets the count of columns in this grid.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error	If the count of cells in I or J direction is
		 * 									strictly greater than unsigned int max.
		 *
		 * @returns	The column count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getColumnCount() const { return getICellCount() * getJCellCount(); }

		/**
		 * Gets the count of pillars in this grid.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error	If the count of cells in I or J direction is
		 * 									strictly greater than unsigned int max.
		 *
		 * @returns	The pillar count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPillarCount() const { return (getICellCount()+1) * (getJCellCount()+1); }

		/**
		 * Gets the count of K layer gaps in this grid.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error	If the count of cells in I or J direction is
		 * 									strictly greater than unsigned int max.
		 *
		 * @returns	The K Layer gaps count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getKGapsCount() const;

		/**
		* For each K Layer except the last one, indicate wether there is a layer or not after it.
		*
		* @param [out]	kGaps	An array for receiving the information about kGaps.
		*						It must have a count of getKCellCount() - 1. It won't be free. A false value in
		* 						@p kGaps means that the corresponding k layer has no gaps just after it.
		*						A true value means that the corresponding k layer has a gap just after it.
		*/
		DLL_IMPORT_OR_EXPORT void getKGaps(bool * kGaps) const;

		/**
		 * Gets the count of faces in this grid. This method requires you have already loaded the split
		 * information thanks to loadSplitInformation().
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::range_error	 	If the count of cells in I, J or K
		 * 										direction is strictly greater than unsigned int max.
		 * @exception	std::invalid_argument	If there is no geometry on this grid.
		 *
		 * @returns	The face count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getFaceCount() const;

		/**
		 * Gets the I index of a pillar from its global index in this grid. The global (or
		 * linearized) index of a given pillar is <tt>i pillar + j pillar * (nI pillar)</tt> where
		 * <tt>i pillar</tt> and <tt>j pillar</tt> are respectively the I and J indices of the
		 * pillar and <tt>nI pillar</tt> is the count of pillars in the I direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error 	If the count of cells in I or J direction is
		 * 									strictly greater than unsigned int max.
		 * @exception	std::out_of_range	If @p globalIndex is out of range (greater than or equal to
		 * 									getPillarCount()).
		 *
		 * @param 	globalIndex	The global index of the pillar for which we want to get the I index.
		 *
		 * @returns	The I index of the pillar.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getIPillarFromGlobalIndex(unsigned int globalIndex) const;

		/**
		 * Gets the J index of a pillar from its global index in this grid. The global (or
		 * linearized) index of a given pillar is <tt>i pillar + j pillar * (nI pillar)</tt> where
		 * <tt>i pillar</tt> and <tt>j pillar</tt> are respectively the I and J indices of the
		 * pillar and <tt>nI pillar</tt> is the count of pillars in the I direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error 	If the count of cells in I or J direction is
		 * 									strictly greater than unsigned int max.
		 * @exception	std::out_of_range	If @p globalIndex is out of range (greater than or equal to
		 * 									getPillarCount()).
		 *
		 * @param 	globalIndex	The global index of the pillar for which we want to get the J index.
		 *
		 * @returns	The J index of the pillar.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getJPillarFromGlobalIndex(unsigned int globalIndex) const;

		/**
		 * Gets the global index of a pillar from its I and J indices in the grid. The global (or
		 * linearized) index of a given pillar is <tt>i pillar + j pillar * (nI pillar)</tt> where
		 * <tt>i pillar</tt> and <tt>j pillar</tt> are respectively the I and J indices of the
		 * pillar and <tt>nI pillar</tt> is the count of pillars in the I direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error 	If the count of cells in I or J direction is strictly greater
		 * 									than unsigned int max.
		 * @exception	std::out_of_range	If @p iPillar is strictly greater than getICellCount().
		 * @exception	std::out_of_range	If @p jPillar is strictly greater than getJCellCount().
		 *
		 * @param 	iPillar	The I index of the pillar.
		 * @param 	jPillar	The J index of the pillar.
		 *
		 * @returns	The global index of the pillar.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getGlobalIndexPillarFromIjIndex(unsigned int iPillar, unsigned int jPillar) const;

		/**
		 * Gets the I index of a column from its global index in the grid. The global (or linearized)
		 * index of a given column is <tt>i column + j column * (nI cell)</tt> where
		 * <tt>i column</tt> and <tt>j column</tt> are respectively the I and J indices of the
		 * column and <tt>nI cell</tt> is the count of cells in the I direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error 	If the count of cells in I or J direction is strictly greater
		 * 									than unsigned int max.
		 * @exception	std::out_of_range	If @p globalIndex is out of range (greater than or equal to
		 * 									getColumnCount()).
		 *
		 * @param 	globalIndex	The global index of the column for which we want to get the I index.
		 *
		 * @returns	The I index of the column.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getIColumnFromGlobalIndex(unsigned int globalIndex) const;

		/**
		 * Gets the J index of a column from its global index in the grid. The global (or linearized)
		 * index of a given column is <tt>i column + j column * (nI cell)</tt> where
		 * <tt>i column</tt> and <tt>j column</tt> are respectively the I and J indices of the
		 * column and <tt>nI cell</tt> is the count of cells in the I direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error 	If the count of cells in I or J direction is strictly greater
		 * 									than unsigned int max.
		 * @exception	std::out_of_range	If @p globalIndex is out of range (greater than or equal to
		 * 									getColumnCount()).
		 *
		 * @param 	globalIndex	The global index of the column for which we want to get the J index.
		 *
		 * @returns	The J index of the column.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getJColumnFromGlobalIndex(unsigned int globalIndex) const;

		/**
		 * Gets the global index of a column from its I and J indices in the grid. The global (or
		 * linearized) index of a given column is <tt>i column + j column * (nI cell)</tt> where
		 * <tt>i column</tt> and <tt>j column</tt> are respectively the I and J indices of the
		 * column and <tt>nI cell</tt> is the count of cells in the I direction.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error 	If the count of cells in I or J direction is strictly greater
		 * 									than unsigned int max.
		 * @exception	std::out_of_range	If @p iColumn is greater than or equal to getICellCount().
		 * @exception	std::out_of_range	If @p jColumn is greater than or equal to getJCellCount().
		 *
		 * @param 	iColumn	The I index of the column.
		 * @param 	jColumn	The J index of the column.
		 *
		 * @returns	The global index of the column.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getGlobalIndexColumnFromIjIndex(unsigned int iColumn, unsigned int jColumn) const;

		/**
		 * Gets the global index of a cell from its I, J and K indices in the grid.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::range_error 	If the count of cells in I, J or K direction is strictly
		 * 									greater than unsigned int max.
		 * @exception	std::out_of_range	If @p iCell is greater than or equal to getICellCount().
		 * @exception	std::out_of_range	If @p jCell is greater than or equal to getJCellCount().
		 * @exception	std::out_of_range	If @p kCell is greater than or equal to getKCellCount().
		 *
		 * @param 	iCell	The I index of the cell.
		 * @param 	jCell	The J index of the cell.
		 * @param 	kCell	The K index of the cell.
		 *
		 * @returns	The global index of the cell.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getGlobalIndexCellFromIjkIndex(unsigned int iCell, unsigned int jCell, unsigned int kCell) const;

		/**
		 * Queries if this grid is right handed, as determined by the triple product of tangent vectors
		 * in the I, J, and K directions.
		 *
		 * @exception	std::logic_error	If this grid has no geometry. Or, if it is in an unrecognized
		 * 									version of RESQML.
		 *
		 * @returns	True if this grid is right handed, false if it is not.
		 */
		DLL_IMPORT_OR_EXPORT bool isRightHanded() const;

		/**
		 * Gets all the pillars which correspond to all split coordinate lines. The order of the pillars
		 * corresponds to the order of the split coordinate lines.
		 *
		 * @exception	std::invalid_argument	If the HDF proxy is missing.
		 * @exception	std::invalid_argument	If there is no geometry or no split coordinate line in
		 * 										this grid.
		 * @exception	std::logic_error	 	If the indices of the pillars corresponding to the split
		 * 										coordinate lines are not stored within an HDF5 integer
		 * 										array.
		 *
		 * @param [out]	pillarIndices	An array for receiving the indices of the pillars corresponding
		 * 								to the split coordinate lines. It must be preallocated with a
		 * 								size of getSplitCoordinateLineCount().
		 * @param 	   	reverseIAxis 	(Optional) True to reverse I axis. Default value is false.
		 * @param 	   	reverseJAxis 	(Optional) True to reverse J axis. Default value is false.
		 */
		DLL_IMPORT_OR_EXPORT void getPillarsOfSplitCoordinateLines(unsigned int * pillarIndices, bool reverseIAxis = false, bool reverseJAxis = false) const;

		/**
		 * Gets all the columns impacted by all the split coordinate lines. The order of the columns
		 * corresponds to the order of the split coordinate lines.
		 *
		 * @exception	std::invalid_argument	If the HDF proxy is missing.
		 * @exception	std::invalid_argument	If there is no geometry or no split coordinate line in
		 * 										this grid.
		 * @exception	std::logic_error	 	If the indices of the columns impacted by the split
		 * 										coordinate lines are not stored within an HDF5 integer
		 * 										array.
		 *
		 * @param [out]	columnIndices	An array for receiving the indices of the columns impacted by the
		 * 								split coordinate lines. It must be preallocated with a size equal
		 * 								to the last value of the array outputted from
		 * 								getColumnCountOfSplitCoordinateLines().
		 * @param 	   	reverseIAxis 	(Optional) True to reverse i axis. Default value is false.
		 * @param 	   	reverseJAxis 	(Optional) True to reverse j axis. Default value is false.
		 */
		DLL_IMPORT_OR_EXPORT void getColumnsOfSplitCoordinateLines(unsigned int * columnIndices, bool reverseIAxis = false, bool reverseJAxis = false) const;

		/**
		 * Gets the cumulative count of columns impacted by all the split coordinate lines. The order of
		 * the cumulative count values corresponds to the order of the split coordinates lines.
		 *
		 * @exception	std::invalid_argument	If the HDF proxy is missing.
		 * @exception	std::invalid_argument	If there is no geometry or no split coordinate line in
		 * 										this grid.
		 * @exception	std::logic_error	 	If the cumulative count of the columns impacted by the
		 * 										split coordinate lines are not stored within an HDF5
		 * 										integer array.
		 *
		 * @param [out]	columnIndexCountPerSplitCoordinateLine	An array for receiving the cumulative
		 * 														count of columns impacted by the split
		 * 														coordinate lines.
		 */
		DLL_IMPORT_OR_EXPORT void getColumnCountOfSplitCoordinateLines(unsigned int * columnIndexCountPerSplitCoordinateLine) const;

		/**
		 * Gets the split coordinate lines count.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this IJK grid.
		 * @exception	std::range_error	 	If the count of split coordinate lines is strictly
		 * 										greater than unsigned int max.
		 *
		 * @returns	The split coordinate lines count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned long getSplitCoordinateLineCount() const;

		/**
		 * Gets the split coordinate lines count within the block. Block information must be loaded thanks
		 * to loadBlockInformation().
		 *
		 * @exception	std::invalid_argument	If the block information is not loaded.
		 *
		 * @returns	The split coordinate lines count within the block.
		 */
		DLL_IMPORT_OR_EXPORT unsigned long getBlockSplitCoordinateLineCount() const;

		/**
		 * Gets the split nodes count.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this IJK grid.
		 *
		 * @returns	The split nodes count.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getSplitNodeCount() const;

		/**
		 * Tells for each pillar if its geometry is defined. This method only looks at the corresponding
		 * @c PillarGeometryIsDefined attribute in the gSOAP proxy.
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::range_error	 	If the count of cells in I or J direction is strictly
		 * 										greater than unsigned int max.
		 * @exception	std::invalid_argument	If there is no geometry on this IJK grid.
		 * @exception	std::invalid_argument	If the values indicating for each pillar if its geometry
		 * 										is defined are neither stored in an HDF5 boolean array
		 * 										nor in a boolean constant array.
		 *
		 * @param [out]	pillarGeometryIsDefined	An array for receiving a boolean value for each pillar
		 * 										indicating if its geometry is defined or not. It must be
		 * 										preallocated with a size of getPillarCount().
		 * @param 	   	reverseIAxis		   	(Optional) True to reverse i axis. Default value is false.
		 * @param 	   	reverseJAxis		   	(Optional) True to reverse j axis. Default value is false.
		 */
		DLL_IMPORT_OR_EXPORT void getPillarGeometryIsDefined(bool * pillarGeometryIsDefined, bool reverseIAxis = false, bool reverseJAxis = false) const;

		/**
		 * Indicates if this grid contains a flag on each cell indicating if its geometry is defined or not
		 * (i.e. meaning that at least one of the coordinates of at least one of the cell vertex is NaN).
		 * Do not mix this flag with the active one : http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-000-289-0-C-sv2010.html
		 *
		 * @returns	True if this grid contains a flag on each cell indicating if its geometry is defined or not, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasCellGeometryIsDefinedFlags() const;

		/**
		 * Get the flags for each cell indicating if its geometry is defined or not
		 * (i.e. meaning that at least one of the coordinates of at least one of the cell vertex is NaN).
		 * Do not mix this flag with the active one : http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-000-289-0-C-sv2010.html
		 *
		 * @exception	std::invalid_argument	If this grid has no geometry or no CellGeometryIsDefined flags.
		 * @exception	std::invalid_argument	If the CellGeometryIsDefined flags are neither
		 * 										stored in an HDF5 boolean array nor in a boolean constant
		 * 										array.
		 *
		 * @param [out]	cellGeometryIsDefinedFlags	An array for receiving the CellGeometryIsDefined flags.
		 *								It must have a count of getCellCount() and must follow the
		 * 								index ordering I then J then K. It won't be free. A zero value in
		 * 								@p cellGeometryIsDefinedFlags means that the corresponding cell geometry is not defined. A non
		 * 								zero value means that the corresponding cell geometry is defined.
		 * @param 	   	reverseIAxis	(Optional) True to reverse i axis. Default value is false.
		 * @param 	   	reverseJAxis	(Optional) True to reverse j axis. Default value is false.
		 * @param 	   	reverseKAxis	(Optional) True to reverse k axis. Default value is false.
		 */
		DLL_IMPORT_OR_EXPORT void getCellGeometryIsDefinedFlags(bool* cellGeometryIsDefinedFlags, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;

		/**
		 * Sets the flags for each cell indicating if its geometry is defined or not
		 * (i.e. meaning that at least one of the coordinates of at least one of the cell vertex is NaN).
		 * Do not mix this flag with the active one : http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-000-289-0-C-sv2010.html
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If this grid has no geometry.
		 *
		 * @param [in]	  	cellGeometryIsDefinedFlags	An array containing the CellGeometryIsDefined flags.
		 *									It must have a count of getCellCount() and must follow the
		 * 									index ordering I then J then K. A zero value in
		 * 									@p cellGeometryIsDefinedFlags means that the corresponding cell geometry is not defined. A non
		 * 									zero value means that the corresponding cell geometry is defined.
		 * @param [in]		proxy			(Optional) The HDF proxy for writing the @p cellGeometryIsDefinedFlags
		 * 									values. If @c nullptr (default), then the default HDF proxy will be
		 * 									used.
		 */
		DLL_IMPORT_OR_EXPORT void setCellGeometryIsDefinedFlags(unsigned char* cellGeometryIsDefinedFlags, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Set to "defined" the flags for each cell indicating if its geometry is defined or not
		 * (i.e. meaning that at least one of the coordinates of at least one of the cell vertex is NaN).
		 * Do not mix this flag with the active one : http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-000-289-0-C-sv2010.html
		 */
		DLL_IMPORT_OR_EXPORT void setAllCellGeometryFlagsToDefined();

		/**
		 * Loads the split information into memory to speed up processes. Be aware that you must unload
		 * by yourself this memory thanks to unloadSplitInformation().
		 */
		DLL_IMPORT_OR_EXPORT void loadSplitInformation();

		/**
		 * Loads the block information into memory to speed up the processes and make easier block
		 * geometry handling for the user. This method requires that you have
		 * already loaded the split information.
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::invalid_argument	If the split information is not loaded.
		 * @exception	std::out_of_range	 	If @p iInterfaceEnd <tt>&gt;</tt> getICellCount(), @p
		 * 										jInterfaceEnd <tt>&gt;</tt> getJCellCount() or @p
		 * 										kInterfaceEnd <tt>&gt;</tt> getKCellCount() + getKGapsCount().
		 * @exception	std::range_error	 	If @p iInterfaceStart @c > @p iInterfaceEnd, @p
		 * 										jInterfaceStart @c > @p jInterfaceEnd or @p
		 * 										kInterfaceStart @c > @p kInterfaceEnd.
		 *
		 * @param 	iInterfaceStart	The starting I interface index of the block taken from zero to
		 * 							getICellCount().
		 * @param 	iInterfaceEnd  	The ending I interface index of the block taken from zero to
		 * 							getICellCount().
		 * @param 	jInterfaceStart	The starting J interface index of the block taken from zero to
		 * 							getJCellCount().
		 * @param 	jInterfaceEnd  	The ending J interface index of the block taken from zero to
		 * 							getJCellCount().
		 * @param 	kInterfaceStart	The starting K interface index of the block taken from zero to
		 * 							getKCellCount() + getKGapsCount().
		 * @param 	kInterfaceEnd  	The ending K interface index of the block taken from zero to
		 * 							getKCellCount().
		 */
		DLL_IMPORT_OR_EXPORT void loadBlockInformation(unsigned int iInterfaceStart, unsigned int iInterfaceEnd, unsigned int jInterfaceStart, unsigned int jInterfaceEnd, unsigned int kInterfaceStart, unsigned int kInterfaceEnd);

		/** Unloads the split information from memory. */
		DLL_IMPORT_OR_EXPORT void unloadSplitInformation();

		/**
		 * @brief	Checks either a given column edge is splitted or not. This method requires that you
		 * 			have already loaded the split information.
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::invalid_argument	If the split information is not loaded.
		 * @exception	std::out_of_range	 	If @p iColumn is strictly greater than getICellCount().
		 * @exception	std::out_of_range	 	If @p iColumn is strictly greater than getJCellCount().
		 * @exception	std::out_of_range	 	If @p edge is strictly greater than 3.
		 *
		 * @param 	iColumn	The I index of the column.
		 * @param 	jColumn	The J index of the column.
		 * @param 	edge   	0 for edge from i to i+1, lower j connection; 1 for edge from j to j+1, upper
		 * 					i connection; 2 for edge from i+1 to i, upper j connection; 3 for edge from
		 * 					j+1 to j, lower i connection.
		 *
		 * @returns	True if the column edge is splitted, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isColumnEdgeSplitted(unsigned int iColumn, unsigned int jColumn, unsigned int edge) const;

		/**
		 * @brief	Gets the XYZ point index in the HDF dataset from the corner of a cell. This method
		 * 			requires that you have already loaded the split information.
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::invalid_argument	If the split information is not loaded.
		 * @exception	std::out_of_range	 	If @p iCell > getICellCount(), @p jCell >
		 * 										getJCellCount() or @p kCell > getKCellCount().
		 * @exception	std::out_of_range	 	If @p corner > 7.
		 *
		 * @param 	iCell 	The I index of the cell.
		 * @param 	jCell 	The J index of the cell.
		 * @param 	kCell 	The K index of the cell.
		 * @param 	corner	Index of the corner: 0 for (0,0,0); 1 for (1,0,0); 2 for (1,1,0); 3 for (0,1,
		 * 					0); 4 for (0,0,1); 5 for (1,0,1); 6 for (1,1,1); 7 for (0,1,1).
		 *
		 * @returns	The index of the XYZ point in the HDF dataset corresponding to the corner of the
		 * 			cell. Keep in mind to multiply the result by 3 to get the X index since the points
		 * 			are triplet of values.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getXyzPointIndexFromCellCorner(unsigned int iCell, unsigned int jCell, unsigned int kCell, unsigned int corner) const;

		/**
		 * @brief	Gets the x, y and z values of the corner of a cell of a given block. This method
		 * 			requires that you have already both loaded the block information and get the geometry
		 * 			of the block thanks to getXyzPointsOfBlock().
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::invalid_argument	If the split or block information is not loaded.
		 * @exception	std::out_of_range	 	If @p iCell > getICellCount(), @p jCell >
		 * 										getJCellCount() or @p kCell > getKCellCount().
		 * @exception	std::out_of_range	 	If @p corner > 7.
		 *
		 * @param 	   	iCell	 	The I index of the cell.
		 * @param 	   	jCell	 	The J index of the cell.
		 * @param 	   	kCell	 	The K index of the cell.
		 * @param 	   	corner   	Index of the corner: 0 for (0,0,0); 1 for (1,0,0); 2 for (1,1,0); 3
		 * 							for (0,1,0); 4 for (0,0,1); 5 for (1,0,1); 6 for (1,1,1); 7 for (0,1,
		 * 							1).
		 * @param 	   	xyzPoints	The XYZ points of the block (resulting from a call to
		 * 							getXyzPointsOfBlock()).
		 * @param [out]	x		 	The x value of the corner we look for.
		 * @param [out]	y		 	The y value of the corner we look for.
		 * @param [out]	z		 	The z value of the corner we look for.
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointOfBlockFromCellCorner(unsigned int iCell, unsigned int jCell, unsigned int kCell, unsigned int corner,
			const double* xyzPoints, double & x, double & y, double & z) const;

		/**
		 * Get the XYZ points count in each K layer interface.
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::range_error	 	If the count of cells in I or J direction is strictly
		 * 										greater than unsigned int max.
		 * @exception	std::invalid_argument	If there is no geometry on this IJK grid.
		 * @exception	std::range_error	 	If the count of split coordinate lines is strictly
		 * 										greater than unsigned int max.
		 *
		 * @returns	The XYZ point count of each K layer interface.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getXyzPointCountOfKInterface() const;

		/**
		 * Gets the XYZ points count of the current block. Block information must be loaded.
		 *
		 * @exception	std::invalid_argument	If the block information is not loaded.
		 *
		 * @returns	The XYZ point count of the current block.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getXyzPointCountOfBlock() const;

		/*
		 * Gets all the XYZ points of a particular K interface. XYZ points are given in the local CRS.
		 * This method is not const since it is optimized in order not to recompute the pillar
		 * information but to get it as input.
		 *
		 * @param 		  	kInterface	The K interface index starting from zero to kCellCount.
		 * @param [out]	xyzPoints 		A linearized 2d array where the first (quickest) dimension is
		 * 								coordinate dimension (XYZ) and second dimension is vertex
		 * 								dimension. It must be pre allocated with a size of
		 * 								<tt>3 * getXyzPointCountOfKInterface()</tt>.
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfKInterface(unsigned int kInterface, double * xyzPoints);

		/**
		 * @brief Gets all the XYZ points of a particular sequence of K interfaces. XYZ points are given in the
		 * local CRS.
		 *
		 * @exception	std::out_of_range	 	If @p kInterfaceStart @c > getKCellCount() or @p
		 * 										kInterfaceEnd @c > getKCellCount() + getKGapsCount().
		 * @exception	std::range_error	 	If @p kInterfaceStart @c > @p kInterfaceEnd.
		 * @exception	std::invalid_argument	If @p xyzPoints is @c nullptr.
		 *
		 * @param 	   	kInterfaceStart	The K index of the starting interface taken from zero to
		 * 								getKCellCount().
		 * @param 	   	kInterfaceEnd  	The K index of the ending interface taken from zero to
		 * 								getKCellCount() + getKGapsCount().
		 * @param [out]	xyzPoints	   	A linearized 2d array where the first (quickest) dimension is
		 * 								coordinate dimension (XYZ) and second dimension is vertex
		 * 								dimension. It must be preallocated with a size of
		 * 								<tt>3 *</tt> getXyzPointCountOfKInterface() <tt>*
		 * 								(kInterfaceEnd - kInterfaceStart + 1)</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getXyzPointsOfKInterfaceSequence(unsigned int kInterfaceStart, unsigned int kInterfaceEnd, double * xyzPoints);

		/**
		 * @brief Gets all the XYZ points of the current block. XYZ points are given in the local CRS. Block
		 * information must be loaded.
		 *
		 * @exception	std::invalid_argument	If the block information is not loaded.
		 * @exception	std::invalid_argument	If @p xyzPoints is @c nullptr.
		 *
		 * @param [out]	xyzPoints	A linearized 2d array where the first (quickest) dimension is
		 * 							coordinate dimension (XYZ) and second dimension is vertex dimension.
		 * 							It must be pre allocated with a size of
		 * 							<tt>3 *</tt> getXyzPointCountOfBlock().
		 */
		DLL_IMPORT_OR_EXPORT virtual void getXyzPointsOfBlock(double * xyzPoints);

		/**
		 * Checks whether the node geometry dataset is compressed or not.
		 *
		 * @exception	std::invalid_argument	If this grid has no geometry.
		 *
		 * @returns	True if the node geometry dataset is compressed, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isNodeGeometryCompressed() const { return false; }

		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__KDirection getKDirection() const override;

		/**
		 * Gets the geometry kind of this IJK grid.
		 *
		 * @returns	The geometry kind of this IJK grid.
		 */
		DLL_IMPORT_OR_EXPORT virtual geometryKind getGeometryKind() const { return UNKNOWN; }

		virtual COMMON_NS::DataObjectReference getHdfProxyDor() const override { throw std::logic_error("Partial object"); }

		DLL_IMPORT_OR_EXPORT virtual uint64_t getXyzPointCountOfPatch(unsigned int patchIndex) const override;

		/**
		* @copybrief AbstractRepresentation::getXyzPointsOfPatch
		*
		* @exception std::out_of_range	If <tt>patchIndex >=</tt> getPatchCount().
		*
		* @param patchIndex	The index of the patch.
		* @param xyzPoints	xyz double triplets ordered by i then j then split then k. It must be preallocated
		* 					with a count of <tt>((iCellCount+1) * (jCellCount+1) + splitCoordinateLineCount)</tt>
		* 					<tt> * kCellCount.</tt>
		*/
		DLL_IMPORT_OR_EXPORT virtual void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const override;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/** The standard XML tag without XML namespace for serializing this data object if truncated. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG_TRUNCATED;

		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const final;

		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const override {return 1;}

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlNamespace() const override {
			if (gsoapProxy2_0_1 != nullptr) { return "resqml20"; }
			if (gsoapProxy2_3 != nullptr) { return "resqml22"; }


			if (partialObject != nullptr) {
				if (partialObject->ContentType.find("x-resqml+xml;version=2.0") != std::string::npos) { return "resqml20"; }
				if (partialObject->ContentType.find("x-resqml+xml;version=2.2") != std::string::npos) { return "resqml22"; }
			}

			throw std::logic_error("Cannot infer what is the Energistics namespace of this instance.");
		}

	protected:

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractIjkGridRepresentation(gsoap_resqml2_0_1::_resqml20__IjkGridRepresentation* fromGsoap) : AbstractColumnLayerGridRepresentation(fromGsoap, false), splitInformation(nullptr), kCellIndexWithGapLayer(nullptr), blockInformation(nullptr) {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractIjkGridRepresentation(gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation* fromGsoap) : AbstractColumnLayerGridRepresentation(fromGsoap, true), splitInformation(nullptr), kCellIndexWithGapLayer(nullptr), blockInformation(nullptr) {}
		AbstractIjkGridRepresentation(gsoap_eml2_3::_resqml22__IjkGridRepresentation* fromGsoap) : AbstractColumnLayerGridRepresentation(fromGsoap, false), splitInformation(nullptr), kCellIndexWithGapLayer(nullptr), blockInformation(nullptr) {}
		AbstractIjkGridRepresentation(gsoap_eml2_3::_resqml22__TruncatedIjkGridRepresentation* fromGsoap) : AbstractColumnLayerGridRepresentation(fromGsoap, true), splitInformation(nullptr), kCellIndexWithGapLayer(nullptr), blockInformation(nullptr) {}

		gsoap_resqml2_0_1::_resqml20__IjkGridRepresentation* getSpecializedGsoapProxy2_0_1() const;
		gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation* getSpecializedTruncatedGsoapProxy2_0_1() const;
		gsoap_eml2_3::_resqml22__IjkGridRepresentation* getSpecializedGsoapProxy2_2() const;
		gsoap_eml2_3::_resqml22__TruncatedIjkGridRepresentation* getSpecializedTruncatedGsoapProxy2_2() const;

		/**
		 * Gets point geometry 2 0 1
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	Null if it fails, else the point geometry 2 0 1.
		 */
		gsoap_resqml2_0_1::resqml20__PointGeometry* getPointGeometry2_0_1(unsigned int patchIndex) const final;
		gsoap_eml2_3::resqml22__PointGeometry* getPointGeometry2_2(unsigned int patchIndex) const final;

		/**
		* Information about the splits (mainly due to faults) which occur in this grid.
		* A splitInformation equal to nullptr means that it has not been initialized. An initialized splitInformation has always a size of getPillarCount().
		* Indeed, each pillar of the grid (ordered I fastest then J slowest) is represented by a vector of split coordinate line information.
		* A split coordinate line information is a pair composed by :
		*  - first : the split coordinate line index
		*  - second : all grid columns (identified by their indices: i fastest, j slowest) which are incident to (and consequently affected by) this split coordinate line
		*
		* Example : split info set to => {empty, empty, ..., {{10, {51, 23}}}, empty, {{12, {51, 23}}, {15, {22}}}, empty}
		* This grid has 3 split coordinate lines (10, 12 and 15) which are related to two pillars (2 and 4).
		* On the pillar 2, only a single split coordinate line (10) affects two columns (51, 23).
		* On the pillar 4, two split coordinate lines exist (12 and 15). The split coordinate line 12 affects two columns (51 and 23). The split coordinate line 15 affects a single column (22).
		* The other pillars are not splitted at all.
		*
		* Remarks :
		* - There is a maximum of 3 split coordinate lines per pillar (the fourth one being considered as the non split one).
		* -	There is a minimum of 1 column per split coordinate line.
		* - There is a maximum of 3 columns per split coordinate line.
		*/
		std::vector< std::pair< unsigned int, std::vector<unsigned int> > >* splitInformation;

		/**
		* For each kCellIndex, indicate what is the corresponding K Cell index if K gap layer would be normal K layer.
		* A kCellIndexWithGapLayer equal to nullptr means that it has not been initialized. An initialized kCellIndexWithGapLayer has always a size of getKCellCount().
		*/
		unsigned int* kCellIndexWithGapLayer;

		/** Information about the block. */
		class BlockInformation
		{
		public:

			/** Zero-based index of the interface start */
			unsigned int iInterfaceStart;
			/** Zero-based index of the interface end */
			unsigned int iInterfaceEnd;
			/** The interface start */
			unsigned int jInterfaceStart;
			/** The interface end */
			unsigned int jInterfaceEnd;
			/** The interface start */
			unsigned int kInterfaceStart;
			/** The interface end */
			unsigned int kInterfaceEnd;

			/** Map split coordinate lines index with local index (according to a block) */
			std::map<unsigned int, unsigned int> globalToLocalSplitCoordinateLinesIndex;

			/** Default constructor */
			BlockInformation() = default;

			/** Destructor */
			~BlockInformation() = default;
		};

		/** Information describing the block */
		BlockInformation* blockInformation;

	private:

		/**
		 * Initializes this object
		 *
		 * @param [in,out]	repo  	The soap context where the underlying gsoap proxy is going to be
		 * 							created.
		 * @param 		  	guid  	Unique identifier.
		 * @param 		  	title 	The title.
		 * @param 		  	iCount	Count of cells in the i-direction in the grid.
		 * @param 		  	jCount	Count of cells in the j-direction in the grid.
		 * @param 		  	kCount	Number of layers in the grid.
		 * @param 		  	kGaps	(Optional) Boolean array of length KCellCount-1.
		 *							TRUE if there is a gap after the corresponding layer.
		 *							Won't be freed by FESAPI.
		 * @param [in]		proxy	(Optional) The HDF proxy for writing the @p enabledCells
		 * 							alues. If @c nullptr (default), then the default HDF proxy will be	used.
		 */
		void init(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount, bool* kGaps, EML2_NS::AbstractHdfProxy* proxy = nullptr);
	};
}
