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

#include "../resqml2/AbstractColumnLayerGridRepresentation.h"

#include <stdexcept>
#include <map>

/** . */
namespace RESQML2_0_1_NS
{
	/**
	 * This class is semantically abstract. Technically speaking, it is not an abstract because it
	 * can be used in case of partial transfer where we don't know the geometry of the ijk grid.
	 */
	class AbstractIjkGridRepresentation : public RESQML2_NS::AbstractColumnLayerGridRepresentation
	{
	private :

		/**
		 * Initializes this object
		 *
		 * @param [in,out]	repo  	The soap context where the underlying gsoap proxy is going to be
		 * 							created.
		 * @param 		  	guid  	Unique identifier.
		 * @param 		  	title 	The title.
		 * @param 		  	iCount	Number of.
		 * @param 		  	jCount	Number of.
		 * @param 		  	kCount	Number of.
		 */
		void init(COMMON_NS::DataObjectRepository * repo,
				const std::string & guid, const std::string & title,
				unsigned int iCount, unsigned int jCount, unsigned int kCount);

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
			BlockInformation() {}

			/** Destructor */
			~BlockInformation() {}
		};

	protected :

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractIjkGridRepresentation(gsoap_resqml2_0_1::_resqml20__IjkGridRepresentation* fromGsoap) : AbstractColumnLayerGridRepresentation(fromGsoap, false), splitInformation(nullptr), blockInformation(nullptr) {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractIjkGridRepresentation(gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation* fromGsoap) : AbstractColumnLayerGridRepresentation(fromGsoap, true), splitInformation(nullptr), blockInformation(nullptr) {}

		/**
		 * Gets specialized gsoap proxy
		 *
		 * @returns	Null if it fails, else the specialized gsoap proxy.
		 */
		gsoap_resqml2_0_1::_resqml20__IjkGridRepresentation* getSpecializedGsoapProxy() const;

		/**
		 * Gets specialized truncated gsoap proxy
		 *
		 * @returns	Null if it fails, else the specialized truncated gsoap proxy.
		 */
		gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation* getSpecializedTruncatedGsoapProxy() const;

		/**
		 * Gets point geometry 2 0 1
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	Null if it fails, else the point geometry 2 0 1.
		 */
		gsoap_resqml2_0_1::resqml20__PointGeometry* getPointGeometry2_0_1(unsigned int patchIndex) const;

		/**
		* Information about the splits (mainly due to faults) which occur in this grid.
		* A splitInformation equal to nullptr means that it has not been initialized. An initialized splitInformation has always a size of getPillarCount().
		* Indeed, each pillar of the grid (ordered I fastest then J slowest) is represented by a vector of split coordinate line information.
		* A split coordinate line information is a pair composed by :
		*  - first : the split coordinate line index
		*  - second : all grid columns (identified by their indices: i fastest, j slowest) which are incident to (and consequently affected by) this split coordinate line
		*
		* Example : split info set to => {empty, empty, {{10, {51, 23}}}, empty, {{12, {51, 23}}, {15, {22}}, emtpy}
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

		/** Information describing the block */
		BlockInformation* blockInformation;

	public:

		/** Values that represent geometry kinds */
		enum geometryKind { UNKNOWN = 0, EXPLICIT = 1, PARAMETRIC = 2, LATTICE = 3, NO_GEOMETRY = 4}; // UNKNOWN exists in case of partial transfer

		/**
		 * Constructor
		 *
		 * @param [in,out]	repo					The soap context where the underlying gsoap proxy is
		 * 											going to be created.
		 * @param 		  	guid					Unique identifier.
		 * @param 		  	title					The title.
		 * @param 		  	iCount					Number of.
		 * @param 		  	jCount					Number of.
		 * @param 		  	kCount					Number of.
		 * @param 		  	withTruncatedPillars	(Optional) True to with truncated pillars.
		 */
		AbstractIjkGridRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount,
			bool withTruncatedPillars = false);

		/**
		 * Constructor
		 *
		 * @param [in,out]	interp					If non-null, the interp.
		 * @param 		  	guid					Unique identifier.
		 * @param 		  	title					The title.
		 * @param 		  	iCount					Number of.
		 * @param 		  	jCount					Number of.
		 * @param 		  	kCount					Number of.
		 * @param 		  	withTruncatedPillars	(Optional) True to with truncated pillars.
		 */
		AbstractIjkGridRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount,
			bool withTruncatedPillars = false);

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject			If non-null, the partial object.
		 * @param 		  	withTruncatedPillars	(Optional) True to with truncated pillars.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT AbstractIjkGridRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject, bool withTruncatedPillars = false);

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~AbstractIjkGridRepresentation() 
		{
			if (blockInformation != nullptr)
				delete blockInformation;
		}

		/**
		 * Get the I cell count of the grid
		 *
		 * @returns	The i cell count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getICellCount() const;

		/**
		 * Set the I cell count of the grid
		 *
		 * @param 	iCount	Number of.
		 */
		DLL_IMPORT_OR_EXPORT void setICellCount(const unsigned int & iCount);

		/**
		 * Get the J cell count of the grid
		 *
		 * @returns	The j cell count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getJCellCount() const;

		/**
		 * Set the J cell count of the grid
		 *
		 * @param 	jCount	Number of.
		 */
		DLL_IMPORT_OR_EXPORT void setJCellCount(const unsigned int & jCount);

		/**
		 * Get the count of cells in the grid
		 *
		 * @returns	The cell count.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getCellCount() const {return getICellCount() * getJCellCount() * getKCellCount();}

		/**
		 * Get the count of columns in the grid
		 *
		 * @returns	The column count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getColumnCount() const {return getICellCount() * getJCellCount();}

		/**
		 * Get the count of pillars in the grid
		 *
		 * @returns	The pillar count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPillarCount() const {return (getICellCount()+1) * (getJCellCount()+1);}

		/**
		 * Get the count of faces in the grid This method requires you have already loaded the split
		 * information.
		 *
		 * @returns	The face count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getFaceCount() const;

		/**
		 * Get the I coordinate of a pillar from its global index in the grid.
		 *
		 * @param 	globalIndex	Zero-based index of the global.
		 *
		 * @returns	The i pillar from global index.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getIPillarFromGlobalIndex(unsigned int globalIndex) const;

		/**
		 * Get the J coordinate of a pillar from its global index in the grid.
		 *
		 * @param 	globalIndex	Zero-based index of the global.
		 *
		 * @returns	The j pillar from global index.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getJPillarFromGlobalIndex(unsigned int globalIndex) const;

		/**
		 * Get the global index of a pillar from its I and J indices in the grid.
		 *
		 * @param 	iPillar	Zero-based index of the pillar.
		 * @param 	jPillar	The pillar.
		 *
		 * @returns	The global index pillar from ij index.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getGlobalIndexPillarFromIjIndex(unsigned int iPillar, unsigned int jPillar) const;

		/**
		 * Get the I coordinate of a column from its global index in the grid.
		 *
		 * @param 	globalIndex	Zero-based index of the global.
		 *
		 * @returns	The i column from global index.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getIColumnFromGlobalIndex(unsigned int globalIndex) const;

		/**
		 * Get the J coordinate of a column from its global index in the grid.
		 *
		 * @param 	globalIndex	Zero-based index of the global.
		 *
		 * @returns	The j column from global index.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getJColumnFromGlobalIndex(unsigned int globalIndex) const;

		/**
		 * Get the global index of a cell from its I and J indices in the grid.
		 *
		 * @param 	iColumn	Zero-based index of the column.
		 * @param 	jColumn	The column.
		 *
		 * @returns	The global index column from ij index.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getGlobalIndexColumnFromIjIndex(unsigned int iColumn, unsigned int jColumn) const;

		/**
		 * Get the global index of a column from its I, J and K indices in the grid.
		 *
		 * @param 	iCell	Zero-based index of the cell.
		 * @param 	jCell	The cell.
		 * @param 	kCell	The cell.
		 *
		 * @returns	The global index cell from ijk index.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getGlobalIndexCellFromIjkIndex(unsigned int iCell, unsigned int jCell, unsigned int kCell) const;

		/**
		 * Query if this object is right handed
		 *
		 * @returns	True if right handed, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isRightHanded() const;

		/**
		 * Get all the pillars which correspond to all split coordinate lines. Order of the pillar
		 * correspond to order of the split coordinate lines.
		 *
		 * @param [in,out]	pillarIndices	It must be pre allocated.
		 * @param 		  	reverseIAxis 	(Optional) True to reverse i axis.
		 * @param 		  	reverseJAxis 	(Optional) True to reverse j axis.
		 */
		DLL_IMPORT_OR_EXPORT void getPillarsOfSplitCoordinateLines(unsigned int * pillarIndices, bool reverseIAxis = false, bool reverseJAxis = false) const;

		/**
		 * Get all the columns impacted by all the split coordinate lines.
		 *
		 * @param [in,out]	columnIndices	It must be pre allocated.
		 * @param 		  	reverseIAxis 	(Optional) True to reverse i axis.
		 * @param 		  	reverseJAxis 	(Optional) True to reverse j axis.
		 */
		DLL_IMPORT_OR_EXPORT void getColumnsOfSplitCoordinateLines(unsigned int * columnIndices, bool reverseIAxis = false, bool reverseJAxis = false) const;

		/**
		 * Gets column count of split coordinate lines
		 *
		 * @param [in,out]	columnIndexCountPerSplitCoordinateLine	If non-null, the column index count
		 * 															per split coordinate line.
		 */
		DLL_IMPORT_OR_EXPORT void getColumnCountOfSplitCoordinateLines(unsigned int * columnIndexCountPerSplitCoordinateLine) const;

		/**
		 * Get the split coordinate line count
		 *
		 * @returns	The split coordinate line count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned long getSplitCoordinateLineCount() const;

		/**
		 * Get the split coordinate line count within a block. Block information must be loaded.
		 *
		 * @returns	The block split coordinate line count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned long getBlockSplitCoordinateLineCount() const;

		/**
		 * Get the split coordinate line count
		 *
		 * @returns	The split node count.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getSplitNodeCount() const;

		/**
		 * Gets pillar geometry is defined
		 *
		 * @param [in,out]	pillarGeometryIsDefined	If non-null, true if pillar geometry is defined.
		 * @param 		  	reverseIAxis		   	(Optional) True to reverse i axis.
		 * @param 		  	reverseJAxis		   	(Optional) True to reverse j axis.
		 */
		DLL_IMPORT_OR_EXPORT void getPillarGeometryIsDefined(bool * pillarGeometryIsDefined, bool reverseIAxis = false, bool reverseJAxis = false) const;

		/**
		 * Indicates if this grid contains information on enabled and disabled information.
		 *
		 * @returns	True if enabled cell information, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasEnabledCellInformation() const;

		/**
		 * Get the information on the dead/invisible cells. The enabledCells array must have a count of
		 * getCellCount() and must follow the index ordering i then j then k. A zero value in
		 * enabledCells means that the corresponding cell is disabled. A non zero value means that the
		 * corresponding cell is enabled.
		 *
		 * @param [in,out]	enabledCells	It must be preallocated with the size of the cell count in
		 * 									the ijk grid. It won't be disallocated.
		 * @param 		  	reverseIAxis	(Optional) True to reverse i axis.
		 * @param 		  	reverseJAxis	(Optional) True to reverse j axis.
		 * @param 		  	reverseKAxis	(Optional) True to reverse k axis.
		 */
		DLL_IMPORT_OR_EXPORT void getEnabledCells(bool * enabledCells, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;

		/**
		 * Set the information on the dead/invisible cells. The geometry of the grid must have been
		 * defined yet. The enabledCells array must have a count of getCellCount() and must follow the
		 * index ordering i then j then k. A zero value in enabledCells means that the corresponding
		 * cell is disabled. A non zero value means that the corresponding cell is enabled.
		 *
		 * @param [in,out]	enabledCells	If non-null, the enabled cells.
		 * @param [in,out]	proxy			(Optional) If non-null, the proxy.
		 */
		DLL_IMPORT_OR_EXPORT void setEnabledCells(unsigned char* enabledCells, COMMON_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Load the split information into memory to speed up processes. Be aware that you must unload
		 * by yourself this memory.
		 */
		DLL_IMPORT_OR_EXPORT void loadSplitInformation();

		/**
		 * Load the block information into memory to speed up the processes and make easier block
		 * geometry handling for the user.
		 *
		 * @param 	iInterfaceStart	The starting I cell index of the block taken from zero to iCellCount -
		 * 							1.
		 * @param 	iInterfaceEnd  	The ending I cell index of the block taken from zero to iCellCount -
		 * 							1.
		 * @param 	jInterfaceStart	The starting J cell index of the block taken from zero to jCellCount -
		 * 							1.
		 * @param 	jInterfaceEnd  	The ending J cell index of the block taken from zero to jCellCount -
		 * 							1.
		 * @param 	kInterfaceStart	The starting K cell index of the block taken from zero to kCellCount -
		 * 							1.
		 * @param 	kInterfaceEnd  	The ending K cell index of the block taken from zero to kCellCount -
		 * 							1.
		 */
		DLL_IMPORT_OR_EXPORT void loadBlockInformation(unsigned int iInterfaceStart, unsigned int iInterfaceEnd, unsigned int jInterfaceStart, unsigned int jInterfaceEnd, unsigned int kInterfaceStart, unsigned int kInterfaceEnd);

		/** Unload the split information from memory. */
		DLL_IMPORT_OR_EXPORT void unloadSplitInformation();

		/**
		 * Check either a column edge is splitted or not. This method requires that you have already
		 * loaded the split information.
		 *
		 * @param 	iColumn	The I index of the column.
		 * @param 	jColumn	The J index of the column.
		 * @param 	edge   	0 for edge from i to i+1, lower j connection
		 * 					1 for edge from j to j+1, upper i connection
		 * 					2 for edge from i+1 to i, upper j connection
		 * 					3 for edge from j+1 to j, lower i connection.
		 *
		 * @returns	True if column edge splitted, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isColumnEdgeSplitted(unsigned int iColumn, unsigned int jColumn, unsigned int edge) const;

		/**
		 * Get the XYZ point index in the HDF dataset from the corner of a cell. This method requires
		 * that you have already loaded the split information.
		 *
		 * @param 	iCell 	The I index of the cell.
		 * @param 	jCell 	The J index of the cell.
		 * @param 	kCell 	The K index of the cell.
		 * @param 	corner	0 for (0,0,0)
		 * 					1 for (1,0,0)
		 * 					2 for (1,1,0)
		 * 					3 for (0,1,0)
		 * 					4 for (0,0,1)
		 * 					5 for (1,0,1)
		 * 					6 for (1,1,1)
		 * 					7 for (0,1,1)
		 *
		 * @returns	index of the XYZ point corresponding to the iCell jCell and corner parameters in the
		 * 			HDF dataset. Keep in mind to multiply the result by 3 to get the X index since the
		 * 			points are triplet of values.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointIndexFromCellCorner(unsigned int iCell, unsigned int jCell, unsigned int kCell, unsigned int corner) const;

		/**
		 * Gets the x, y and z values of the corner of a cell of a given block. This method requires
		 * that you have already both loaded the block information and get the geometry of the block
		 * thanks to getXyzPointsOfBlockOfPatch.
		 *
		 * @param 		  	iCell	 	The I index of the cell.
		 * @param 		  	jCell	 	The J index of the cell.
		 * @param 		  	kCell	 	The K index of the cell.
		 * @param 		  	corner   	0 for (0,0,0)
		 * 								1 for (1,0,0)
		 * 								2 for (1,1,0)
		 * 								3 for (0,1,0)
		 * 								4 for (0,0,1)
		 * 								5 for (1,0,1)
		 * 								6 for (1,1,1)
		 * 								7 for (0,1,1)
		 * @param 		  	xyzPoints	The XYZ points of the block (resulting from a call to
		 * 								getXyzPointsOfBlockOfPatch).
		 * @param [in,out]	x		 	(output parameter) the x value of the corner we look for.
		 * @param [in,out]	y		 	(output parameter) the y value of the corner we look for.
		 * @param [in,out]	z		 	(output parameter) the z value of the corner we look for.
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointOfBlockFromCellCorner(unsigned int iCell, unsigned int jCell, unsigned int kCell, unsigned int corner,
			const double* xyzPoints, double & x, double & y, double & z) const;

		/**
		 * Get the xyz point count in each K Layer interface in a given patch.
		 *
		 * @param 	patchIndex	The index of the patch. It is generally zero.
		 *
		 * @returns	The xyz point count of k interface of patch.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfKInterfaceOfPatch(unsigned int patchIndex) const;

		/**
		 * Get the xyz point count of the current block. Block information must be loaded.
		 *
		 * @returns	The xyz point count of block.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfBlock() const;

		/**
		 * Get all the XYZ points of a particular K interface of a particular patch of this
		 * representation. XYZ points are given in the local CRS. This method is not const since it is
		 * optimized in order not to recompute the pillar information but to get it as input.
		 *
		 * @param 		  	kInterface	The K interface index starting from zero to kCellCount.
		 * @param 		  	patchIndex	The index of the patch. It is generally zero.
		 * @param [in,out]	xyzPoints 	A linearized 2d array where the first (quickest) dimension is
		 * 								coordinate dimension (XYZ) and second dimension is vertex
		 * 								dimension. It must be pre allocated with a size of
		 * 								3*getXyzPointCountOfKInterfaceOfPatch.
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfKInterfaceOfPatch(unsigned int kInterface, unsigned int patchIndex, double * xyzPoints);

		/**
		 * Gets xyz points of k interface sequence of patch
		 *
		 * @param 		  	kInterfaceStart	The interface start.
		 * @param 		  	kInterfaceEnd  	The interface end.
		 * @param 		  	patchIndex	   	Zero-based index of the patch.
		 * @param [in,out]	xyzPoints	   	If non-null, the xyz points.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getXyzPointsOfKInterfaceSequenceOfPatch(const unsigned int & kInterfaceStart, const unsigned int & kInterfaceEnd, const unsigned int & patchIndex, double * xyzPoints);

		/**
		 * Gets xyz points of block of patch
		 *
		 * @param 		  	patchIndex	Zero-based index of the patch.
		 * @param [in,out]	xyzPoints 	If non-null, the xyz points.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getXyzPointsOfBlockOfPatch(const unsigned int & patchIndex, double * xyzPoints);

		/**
		 * Check wether the node geometry dataset is compressed or not.
		 *
		 * @returns	True if node geometry compressed, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isNodeGeometryCompressed() const { return false; }

		/**
		 * Get the K direction of the grid.
		 *
		 * @returns	The k direction.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__KDirection getKDirection() const;

		/**
		 * Gets geometry kind
		 *
		 * @returns	The geometry kind.
		 */
		DLL_IMPORT_OR_EXPORT virtual geometryKind getGeometryKind() const { return UNKNOWN; }

		/**
		 * Gets hdf proxy dor
		 *
		 * @exception	std::logic_error	Raised when a logic error condition occurs.
		 *
		 * @returns	Null if it fails, else the hdf proxy dor.
		 */
		virtual gsoap_resqml2_0_1::eml20__DataObjectReference* getHdfProxyDor() const { throw std::logic_error("Partial object"); }

		/**
		 * Gets xyz point count of patch
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	The xyz point count of patch.
		 */
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		 * Gets xyz points of patch
		 *
		 * @param 		  	patchIndex	Zero-based index of the patch.
		 * @param [in,out]	xyzPoints 	If non-null, the xyz points.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		 * The standard XML tag without XML namespace for serializing this data object if not truncated.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * The standard XML tag without XML namespace for serializing this data object if truncated.
		 *
		 * @returns	The XML tag truncated.
		 */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG_TRUNCATED;

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const;

		/**
		 * Gets patch count
		 *
		 * @returns	The patch count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const {return 1;}
	};
}
