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

#include "resqml2/AbstractRepresentation.h"

namespace RESQML2_NS
{
	class DLL_IMPORT_OR_EXPORT GridConnectionSetRepresentation : public AbstractRepresentation
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		GridConnectionSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			AbstractRepresentation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		*/
		GridConnectionSetRepresentation(class AbstractFeatureInterpretation* interp) : AbstractRepresentation(interp, nullptr) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		GridConnectionSetRepresentation(gsoap_resqml2_0_1::_resqml2__GridConnectionSetRepresentation* fromGsoap) : AbstractRepresentation(fromGsoap) {}

		virtual void pushBackXmlInterpretation(class AbstractFeatureInterpretation* interp) = 0;
		virtual void pushBackXmlSupportingGridRepresentation(class AbstractGridRepresentation * supportingGridRep) = 0;

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~GridConnectionSetRepresentation() {}
        
		static const char* XML_TAG;
		virtual std::string getXmlTag() const;

		virtual std::string getHdfProxyUuid() const = 0;

		/**
		* Get the cell index pair count of this grid connection representation
		*/
		virtual ULONG64 getCellIndexPairCount() const = 0;

		/**
		* Get the cell index pair count of this grid connection representation
		*/
		virtual ULONG64 getCellIndexPairs(ULONG64 * cellIndexPairs) const = 0;

		/**
		* Get the cell index pairs count which correspond to a particular interpretation.
		* @param interpretationIndex The index of the interpretation in the collection of feature interpretation of this grid connection set.
		*/
		virtual unsigned int getCellIndexPairCountFromInterpretationIndex(const unsigned int & interpretationIndex) const = 0;

		/**
		* Indicates wether the cell connection are associated to interpretation or not.
		*/
		virtual bool isAssociatedToInterpretations() const = 0;

		/**
		* Get the interpretation index cumulative count of this grid connection representation
		* The count of cumulativeCount must be getCellIndexPairCount().
		*/
		virtual void getInterpretationIndexCumulativeCount(unsigned int * cumulativeCount) const = 0;

		/**
		* Get the interpretation indices of this grid connection representation
		* The count of interpretationIndices is the last value of the array returning by getInterpretationIndexCumulativeCount.
		*/
		virtual void getInterpretationIndices(unsigned int * interpretationIndices) const = 0;

		/**
		* Returns the null value for interpretation index.
		*/
		virtual LONG64 getInterpretationIndexNullValue() const = 0;

		/**
		* Get the cell index pairs, the grid index pairs (optional) and the local face pairs (optional) which correspond to a particular  interpretation.
		* @param cellIndexPairs			Mandatory. Must be allocated with getCellIndexPairCountFromIndex first.
		* @param gridIndexPairs			Optional (put null if you don't want it). Must be allocated with getCellIndexPairCountFromIndex first.
		* @param localFaceIndexPairs	Optional (put null if you don't want it). Must be allocated with getCellIndexPairCountFromIndex first.
		* @param interpretationIndex	The index of the interpretation in the collection of feature interpretation of this grid connection set.
		*/
		virtual void getGridConnectionSetInformationFromInterpretationIndex(ULONG64 * cellIndexPairs, unsigned short * gridIndexPairs, int * localFaceIndexPairs, const unsigned int & interpretationIndex) const = 0;

		/**
		* Get the UUID of a particular interpretation of this grid connection set.
		* @param interpretationIndex The index of the interpretation in the collection of feature interpretation of this grid connection set.
		*/
		virtual std::string getInterpretationUuidFromIndex(const unsigned int & interpretationIndex) const = 0;

		/**
		* Get a particular interpretation of this grid connection set.
		* @param interpretationIndex The index of the interpretation in the collection of feature interpretation of this grid connection set.
		*/
		class AbstractFeatureInterpretation * getInterpretationFromIndex(const unsigned int & interpretationIndex) const;

		/**
		* Get the count of interpretations in this grid connection set.
		*/
		virtual unsigned int getInterpretationCount() const = 0;

		/**
		* Indicates if the grid connection set representation contains information on the connected faces of the two cells.
		*/
		virtual bool hasLocalFacePerCell() const = 0;

		/**
		* Get the local face cell index pairs of this grid connection representation.
		*
		* @param localFacePerCellIndexPairs Tis array must be pre allocated and won't be deallocated byt fesapi. The count of localFacePerCellIndexPairs must be getCellIndexPairCount()*2.
		* @return The used null value in localFacePerCellIndexPairs
		*/
		virtual LONG64 getLocalFacePerCellIndexPairs(int * localFacePerCellIndexPairs) const = 0;

		/**
		* Indicates if the grid connection set representation is based on several grids.
		*/
		virtual bool isBasedOnMultiGrids() const = 0;

		/**
		* Get the grid index pairs of this grid connection representation
		* The count of gridIndexPairs must be getCellIndexPairCount()*2.
		*/
		virtual void getGridIndexPairs(unsigned short * gridIndexPairs) const = 0;

		/**
		* Set the cell index pairs of the grid connections representation using some exisiting hdf5 datasets.
		* @param cellIndexPairCount	The count of cell index pair. It is half of all the stored numerical values.
		* @param cellIndexPair		The HDF dataset path where we can find all the cell index pair in a 1d Array where the cell indices go faster than the pair.
		* @param nullValue			The integer null value used in the hdf dataset for null cell and potentially null grid.
		* @param proxy				The HDF proxy where the numerical values (cell indices) are stored.
        * @param gridIndexPair		The HDF dataset path where we can find all the grid index pair in a 1d Array where the grid indices go faster than the pair. The grid at an index must correspond to the cell at the same index in the cellIndexPair array.
		*/
		virtual void setCellIndexPairsUsingExistingDataset(const ULONG64 & cellIndexPairCount, const std::string & cellIndexPair, const LONG64 & nullValue, COMMON_NS::AbstractHdfProxy * proxy, const std::string & gridIndexPair = "") = 0;

		/**
		* Set the cell index pairs of the grid connections representation
        * @param cellIndexPairCount	The count of cell index pair. It is half of all the stored numerical values.
        * @param cellIndexPair		All the cell index pair in a 1d Array where the cell indices go faster than the pair.
		* @param nullValue			The integer null value used in the hdf dataset for null cell and potentially null grid.
        * @param proxy				The HDF proxy where the numerical values (cell indices) are stored.
        * @param gridIndexPair		All the grid index pair in a 1d Array where the grid indices go faster than the pair. The grid at an index must correspond to the cell at the same index in the cellIndexPair array.
		*/
		void setCellIndexPairs(const ULONG64 & cellIndexPairCount, ULONG64 * cellIndexPair, const LONG64 & nullValue, COMMON_NS::AbstractHdfProxy * proxy, unsigned short * gridIndexPair = nullptr);

		/**
		* Optional 2 x #Connections array of local face-per-cell indices for (Cell1,Cell2) for each connection. Local face-per-cell indices are used because global face indices need not have been defined.
		* If no face-per-cell definition occurs as part of the grid representation, e.g., for a block-centered grid, then this array need not appear.
		*/
		virtual void setLocalFacePerCellIndexPairs(const ULONG64 & cellIndexPairCount, int * localFacePerCellIndexPair, const LONG64 & nullValue, COMMON_NS::AbstractHdfProxy * proxy) = 0;

		/**
		* For each connection in the grid connection set representation, allow to map zero or one feature interpretation. TODO: Resqml allows to map with more than one feature interpretation.
		* @param interpretationIndices		For each connection, the index of the corresponding interpretation in the interpretation set of this grid connection. The count of this array is given by the next parameter.
		* @param interpretationIndiceCount	The count of interpretation indices.
		* @param nullValue					The null value must be used as the corresponding interpretation index for each connection which are not associated to any interpretation.
		* @param proxy						The Hdf proxy where the numerical values will be stored.
		*/
		virtual void setConnectionInterpretationIndices(unsigned int * interpretationIndices, const unsigned int & interpretationIndiceCount, const LONG64 & nullValue, COMMON_NS::AbstractHdfProxy * proxy) = 0;

		/**
		* Push back an interpretation which can be mapped with some connections.
		* @param interp	The interpration to push back.
		*/
		void pushBackInterpretation(class AbstractFeatureInterpretation* interp);
	
		/**
		 * Push back a grid representation which is one of the support of this representation.
		 * And push back this representation as a grid connection information of the grid representation as well.
		 */
		void pushBackSupportingGridRepresentation(class AbstractGridRepresentation * supportingGridRep);
		
		/**
		* Get the count of the supporting grid representations of this grid connection representation.
		*/
		virtual unsigned int getSupportingGridRepresentationCount() const = 0;

		/**
		* Get the supporting grid representation located at a specific index of this grid connection representation.
		*/
		class AbstractGridRepresentation* getSupportingGridRepresentation(unsigned int index) const;

		/**
		* Get one of the supporting grid representation dor of this grid connection representation.
		*/
		virtual gsoap_resqml2_0_1::eml20__DataObjectReference* getSupportingGridRepresentationDor(unsigned int index) const = 0;
		
		/**
		* Get one of the supporting grid representation uuid of this grid connection representation.
		*/
		std::string getSupportingGridRepresentationUuid(unsigned int index) const;

		/**
		* Get one of the supporting grid representation title of this grid connection representation.
		*/
		std::string getSupportingGridRepresentationTitle(unsigned int index) const;

		/**
		* Get one of the supporting grid representation content type of this grid connection representation.
		*/
		std::string getSupportingGridRepresentationContentType(unsigned int index) const;

		ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		* Always return one since this representation does not contain patches.
		*/
		unsigned int getPatchCount() const {return 1;}

	private:

		std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc);
	};
}

