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

#include "resqml2/AbstractColumnLayerGridRepresentation.h"

#include <stdexcept>
#include <map>

namespace RESQML2_0_1_NS
{
	/**
	* This class is semantically abstract.
	* Technically speaking, it is not an abstract because it can be used in case of partial transfer where we don't know the geometry of the ijk grid.
	*/
	class DLL_IMPORT_OR_EXPORT AbstractIjkGridRepresentation : public RESQML2_NS::AbstractColumnLayerGridRepresentation
	{
	private :

		/**
		* @param soapContext	The soap context where the underlying gsoap proxy is going to be created.
		*/
		void init(soap* soapContext, RESQML2_NS::AbstractLocal3dCrs * crs,
				const std::string & guid, const std::string & title,
				const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount,
				bool withTruncatedPillars);

		class BlockInformation
		{
		public:

			unsigned int iInterfaceStart;
			unsigned int iInterfaceEnd;
			unsigned int jInterfaceStart;
			unsigned int jInterfaceEnd;
			unsigned int kInterfaceStart;
			unsigned int kInterfaceEnd;

			/**
			* Map split coordinate lines index with local index (according to a block)
			*/
			std::map<unsigned int, unsigned int> globalToLocalSplitCoordinateLinesIndex;
			
			BlockInformation() {}

			~BlockInformation() {}
		};

	protected :

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractIjkGridRepresentation(gsoap_resqml2_0_1::_resqml2__IjkGridRepresentation* fromGsoap) : AbstractColumnLayerGridRepresentation(fromGsoap, false), splitInformation(nullptr), blockInformation(nullptr) {}
		AbstractIjkGridRepresentation(gsoap_resqml2_0_1::_resqml2__TruncatedIjkGridRepresentation* fromGsoap) : AbstractColumnLayerGridRepresentation(fromGsoap, true), splitInformation(nullptr), blockInformation(nullptr) {}

		gsoap_resqml2_0_1::_resqml2__IjkGridRepresentation* getSpecializedGsoapProxy() const;
		gsoap_resqml2_0_1::_resqml2__TruncatedIjkGridRepresentation* getSpecializedTruncatedGsoapProxy() const;

		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry2_0_1(const unsigned int & patchIndex) const;

		std::vector< std::pair< unsigned int, std::vector<unsigned int> > >* splitInformation;

		BlockInformation* blockInformation;

	public:

		enum geometryKind { UNKNOWN = 0, EXPLICIT = 1, PARAMETRIC = 2, LATTICE = 3, NO_GEOMETRY = 4}; // UNKNOWN exists in case of partial transfer

		/**
		* @param soapContext	The soap context where the underlying gsoap proxy is going to be created.
		*/
		AbstractIjkGridRepresentation(soap* soapContext, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount,
			bool withTruncatedPillars = false);

		AbstractIjkGridRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount,
			bool withTruncatedPillars = false);

		/**
		* Only to be used in partial transfer context
		*/
		AbstractIjkGridRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject,
			bool withTruncatedPillars = false) :
			AbstractColumnLayerGridRepresentation(partialObject, withTruncatedPillars), splitInformation(nullptr), blockInformation(nullptr)
		{
		}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractIjkGridRepresentation() 
		{
			if (blockInformation != nullptr)
				delete blockInformation;
		}

		/**
		* Get the I cell count of the grid
		*/
		unsigned int getICellCount() const;

		/**
		* Set the I cell count of the grid
		*/
		void setICellCount(const unsigned int & iCount);

		/**
		* Get the J cell count of the grid
		*/
		unsigned int getJCellCount() const;

		/**
		* Set the J cell count of the grid
		*/
		void setJCellCount(const unsigned int & jCount);

		/**
		* Get the count of cells in the grid
		*/
		ULONG64 getCellCount() const {return getICellCount() * getJCellCount() * getKCellCount();}

		/**
		* Get the count of columns in the grid
		*/
		unsigned int getColumnCount() const {return getICellCount() * getJCellCount();}

		/**
		* Get the count of pillars in the grid
		*/
		unsigned int getPillarCount() const {return (getICellCount()+1) * (getJCellCount()+1);}

		/**
		* Get the count of faces in the grid
		* This method requires you have already loaded the split information.
		*/
		unsigned int getFaceCount() const;

		/**
		* Get the I coordinate of a pillar from its global index in the grid.
		*/
		unsigned int getIPillarFromGlobalIndex(const unsigned int & globalIndex) const;

		/**
		* Get the J coordinate of a pillar from its global index in the grid.
		*/
		unsigned int getJPillarFromGlobalIndex(const unsigned int & globalIndex) const;

		/**
		* Get the global index of a pillar from its I and J indices in the grid.
		*/
		unsigned int getGlobalIndexPillarFromIjIndex(const unsigned int & iPillar, const unsigned int & jPillar) const;

		/**
		* Get the I coordinate of a column from its global index in the grid.
		*/
		unsigned int getIColumnFromGlobalIndex(const unsigned int & globalIndex) const;

		/**
		* Get the J coordinate of a column from its global index in the grid.
		*/
		unsigned int getJColumnFromGlobalIndex(const unsigned int & globalIndex) const;

		/**
		* Get the global index of a cell from its I and J indices in the grid.
		*/
		unsigned int getGlobalIndexColumnFromIjIndex(const unsigned int & iColumn, const unsigned int & jColumn) const;

		/**
		* Get the global index of a column from its I, J and K indices in the grid.
		*/
		unsigned int getGlobalIndexCellFromIjkIndex(const unsigned int & iCell, const unsigned int & jCell, const unsigned int & kCell) const;

		bool isRightHanded() const;

		/**
		 * Get all the pillars which correspond to all split coordinate lines.
		 * Order of the pillar correspond to order of the split coordinate lines.
		 * @param pillarIndices It must be pre allocated.
		 */
		void getPillarsOfSplitCoordinateLines(unsigned int * pillarIndices, bool reverseIAxis = false, bool reverseJAxis = false) const;

		/**
		 * Get all the columns impacted by all the split coordinate lines.
		 * @param columnIndices 			It must be pre allocated.
		 */
		void getColumnsOfSplitCoordinateLines(unsigned int * columnIndices, bool reverseIAxis = false, bool reverseJAxis = false) const;
		void getColumnCountOfSplitCoordinateLines(unsigned int * columnIndexCountPerSplitCoordinateLine) const;

		/**
		 * Get the split coordinate line count
		 */
		unsigned long getSplitCoordinateLineCount() const;

		/**
		 * Get the split coordinate line count within a block. Block information must be loaded.
		 */
		unsigned long getBlockSplitCoordinateLineCount() const;

		/**
		* Get the split coordinate line count
		*/
		ULONG64 getSplitNodeCount() const;
		
		void getPillarGeometryIsDefined(bool * pillarGeometryIsDefined, bool reverseIAxis = false, bool reverseJAxis = false) const;

		/**
		 * Indicates if this grid contains information on enabled and disabled information.
		 */
		bool hasEnabledCellInformation() const;

		/**
		 * Get the information on the dead/invisible cells.
		 * The enabledCells array must have a count of getCellCount() and must follow the index ordering i then j then k.
		 * A zero value in enabledCells means that the corresponding cell is disabled. A non zero value means that the corresponding cell is enabled.
		 * @param	enabledCells	It must be preallocated with the size of the cell count in the ijk grid. It won't be disallocated.
		 */
		void getEnabledCells(bool * enabledCells, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;

		/**
		 * Set the information on the dead/invisible cells. The geometry of the grid must have been defined yet.
		 * The enabledCells array must have a count of getCellCount() and must follow the index ordering i then j then k.
		 * A zero value in enabledCells means that the corresponding cell is disabled. A non zero value means that the corresponding cell is enabled.
		 */
		void setEnabledCells(unsigned char* enabledCells);

		/**
		* Load the split information into memory to speed up processes.
		* Be aware that you must unload by yourself this memory.
		*/
		void loadSplitInformation();

		/**
		 * Load the block information into memory to speed up the processes and make easier block geometry handling for the user.
		 * @param iCellStart	The starting I cell index of the block taken from zero to iCellCount - 1.
		 * @param iCellEnd		The ending I cell index of the block taken from zero to iCellCount - 1.
		 * @param jCellStart	The starting J cell index of the block taken from zero to jCellCount - 1.
		 * @param jCellEnd		The ending J cell index of the block taken from zero to jCellCount - 1.
		 * @param kCellStart	The starting K cell index of the block taken from zero to kCellCount - 1.
		 * @param kCellEnd		The ending K cell index of the block taken from zero to kCellCount - 1.
		 */
		void loadBlockInformation(const unsigned int & iInterfaceStart, const unsigned int & iInterfaceEnd, const unsigned int & jInterfaceStart, const unsigned int & jInterfaceEnd, const unsigned int & kInterfaceStart, const unsigned int & kInterfaceEnd);

		/**
		* Unload the split information from memory.
		*/
		void unloadSplitInformation();

		/**
		* Check either a column edge is splitted or not.
		* This method requires you have already loaded the split information.
		* @param iColumn	The I index of the column
		* @param jColumn	The J index of the column
		* @param edge		0 for edge from i to i+1, lower j connection
		*					1 for edge from j to j+1, upper i connection
		*					2 for edge from i+1 to i, upper j connection
		*					3 for edge from j+1 to j, lower i connection
		*/
		bool isColumnEdgeSplitted(const unsigned int & iColumn, const unsigned int & jColumn, const unsigned int & edge) const;

		/**
		* Get the XYZ point index in the HDF dataset from the corner of a cell.
		* This method requires your have already loaded the split information.
		* @param iCell	The I index of the cell
		* @param jCell	The J index of the cell
		* @param kCell	The K index of the cell
		* @param corner	0 for (0,0,0)
		*				1 for (1,0,0)
		*				2 for (1,1,0)
		*				3 for (0,1,0)
		*				4 for (0,0,1)
		*				5 for (1,0,1)
		*				6 for (1,1,1)
		*				7 for (0,1,1)
		* @return index of the XYZ point corresponding to the iCell jCell and corner 
		* parameters in the HDF dataset. Keep in mind to multiply the result by 3 to get the X index since the points are triplet of values.
		*/
		ULONG64 getXyzPointIndexFromCellCorner(const unsigned int & iCell, const unsigned int & jCell, const unsigned int & kCell, const unsigned int & corner) const;

		/**
		* Gets the x, y and z values of the corner of a cell of a given block.
		* This method requires your have already both loaded the block information and get the geometry of the block thanks to getXyzPointsOfBlockOfPatch.
		* @param iCell			The I index of the cell.
		* @param jCell			The J index of the cell.
		* @param kCell			The K index of the cell.
		* @param corner			0 for (0,0,0)
		*						1 for (1,0,0)
		*						2 for (1,1,0)
		*						3 for (0,1,0)
		*						4 for (0,0,1)
		*						5 for (1,0,1)
		*						6 for (1,1,1)
		*						7 for (0,1,1)
		* @param xyzPoints		The XYZ points of the block (resulting from a call to getXyzPointsOfBlockOfPatch).
		* @param x				(output parameter) the x value of the corner we look for.
		* @param y				(output parameter) the y value of the corner we look for.
		* @param z				(output parameter) the z value of the corner we look for.
		*/
		void getXyzPointOfBlockFromCellCorner(const unsigned int & iCell, const unsigned int & jCell, const unsigned int & kCell, const unsigned int & corner,
			const double* xyzPoints, double & x, double & y, double & z) const;

		/**
		* Get the xyz point count in each K Layer interface in a given patch.
		* @param patchIndex	The index of the patch. It is generally zero.
		*/
		ULONG64 getXyzPointCountOfKInterfaceOfPatch(const unsigned int & patchIndex) const;

		/**
		 * Get the xyz point count of the current block. Block information must be loaded.
		 */
		ULONG64 getXyzPointCountOfBlock() const;

		/**
		* Get all the XYZ points of a particular K interface of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* This method is not const since it is optimized in order not to recompute the pillar information but to get it as input.
		* @param kInterface	The K interface index starting from zero to kCellCount.
		* @param patchIndex	The index of the patch. It is generally zero.
		* @param xyzPoints 	A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated with a size of 3*getXyzPointCountOfKInterfaceOfPatch.
		*/
		void getXyzPointsOfKInterfaceOfPatch(const unsigned int & kInterface, const unsigned int & patchIndex, double * xyzPoints);

		virtual void getXyzPointsOfKInterfaceSequenceOfPatch(const unsigned int & kInterfaceStart, const unsigned int & kInterfaceEnd, const unsigned int & patchIndex, double * xyzPoints);

		virtual void getXyzPointsOfBlockOfPatch(const unsigned int & patchIndex, double * xyzPoints);

		/**
		* Get the K direction of the grid.
		*/
		gsoap_resqml2_0_1::resqml2__KDirection getKDirection() const;

		virtual geometryKind getGeometryKind() const { return UNKNOWN; }
		virtual gsoap_resqml2_0_1::eml20__DataObjectReference* getHdfProxyDor() const { throw std::logic_error("Partial object"); }
		virtual ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const { throw std::logic_error("Partial object"); }
		virtual void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const { throw std::logic_error("Partial object"); }


		static const char* XML_TAG;
		static const char* XML_TAG_TRUNCATED;
		virtual std::string getXmlTag() const;

		unsigned int getPatchCount() const {return 1;}
	};
}

