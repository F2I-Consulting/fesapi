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

#include "resqml2/GridConnectionSetRepresentation.h"

namespace RESQML2_0_1_NS
{
	class DLL_IMPORT_OR_EXPORT GridConnectionSetRepresentation : public RESQML2_NS::GridConnectionSetRepresentation
	{
	protected:
		void init(soap* soapContext, const std::string & guid, const std::string & title);

		/**
		* Pushes back an interpretation which can be mapped with some connections.
		* @param interp	The interpration to push back.
		*/
		void pushBackXmlInterpretation(RESQML2_NS::AbstractFeatureInterpretation* interp);


		/**
		* Pushes back a grid representation which is one of the support of this representation.
		* And push back this representation as a grid connection information of the grid representation as well.
		*/
		void pushBackXmlSupportingGridRepresentation(RESQML2_NS::AbstractGridRepresentation * supportingGridRep);

	public:

		/**
		* Only to be used in partial transfer context
		*/
		GridConnectionSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			RESQML2_NS::GridConnectionSetRepresentation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp	The interpretation the instance represents.
		* @param guid	A guid for the instance to create.
		* @param title	A title for the instance to create.
		*/
		GridConnectionSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
                const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp	The interpretation the instance represents.
		* @param guid	A guid for the instance to create.
		* @param title	A title for the instance to create.
		*/
		GridConnectionSetRepresentation(soap* soapContext,
			const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		GridConnectionSetRepresentation(gsoap_resqml2_0_1::_resqml2__GridConnectionSetRepresentation* fromGsoap) : RESQML2_NS::GridConnectionSetRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~GridConnectionSetRepresentation() {}

		std::string getHdfProxyUuid() const;

		/**
		* Get the cell index pair count of this grid connection representation
		*/
		ULONG64 getCellIndexPairCount() const;

		/**
		* Get the cell index pair count of this grid connection representation
		*/
		ULONG64 getCellIndexPairs(ULONG64 * cellIndexPairs) const;

		/**
		* Get the cell index pairs count which correspond to a particular interpretation.
		* @param interpretationIndex The index of the interpretation in the collection of feature interpretation of this grid connection set.
		*/
		unsigned int getCellIndexPairCountFromInterpretationIndex(const unsigned int & interpretationIndex) const;

		/**
		* Indicates wether the cell connection are associated to interpretation or not.
		*/
		bool isAssociatedToInterpretations() const;

		/**
		* Get the interpretation index cumulative count of this grid connection representation
		* The count of cumulativeCount must be getCellIndexPairCount().
		*/
		void getInterpretationIndexCumulativeCount(unsigned int * cumulativeCount) const;

		/**
		* Get the interpretation indices of this grid connection representation
		* The count of interpretationIndices is the last value of the array returning by getInterpretationIndexCumulativeCount.
		*/
		void getInterpretationIndices(unsigned int * interpretationIndices) const;

		/**
		* Returns the null value for interpretation index.
		*/
		LONG64 getInterpretationIndexNullValue() const;

		/**
		* Get the cell index pairs, the grid index pairs (optional) and the local face pairs (optional) which correspond to a particular  interpretation.
		* @param cellIndexPairs			Mandatory. Must be allocated with getCellIndexPairCountFromIndex first.
		* @param gridIndexPairs			Optional (put null if you don't want it). Must be allocated with getCellIndexPairCountFromIndex first.
		* @param localFaceIndexPairs	Optional (put null if you don't want it). Must be allocated with getCellIndexPairCountFromIndex first.
		* @param interpretationIndex	The index of the interpretation in the collection of feature interpretation of this grid connection set.
		*/
		void getGridConnectionSetInformationFromInterpretationIndex(ULONG64 * cellIndexPairs, unsigned short * gridIndexPairs, int * localFaceIndexPairs, const unsigned int & interpretationIndex) const;

		/**
		* Get the UUID of a particular interpretation of this grid connection set.
		* @param interpretationIndex The index of the interpretation in the collection of feature interpretation of this grid connection set.
		*/
		std::string getInterpretationUuidFromIndex(const unsigned int & interpretationIndex) const;

		/**
		* Get the count of interpretations in this grid connection set.
		*/
		unsigned int getInterpretationCount() const;

		/**
		* Indicates if the grid connection set representation contains information on the connected faces of the two cells.
		*/
		bool hasLocalFacePerCell() const;

		/**
		* Get the local face cell index pairs of this grid connection representation.
		*
		* @param localFacePerCellIndexPairs Tis array must be pre allocated and won't be deallocated byt fesapi. The count of localFacePerCellIndexPairs must be getCellIndexPairCount()*2.
		* @return The used null value in localFacePerCellIndexPairs
		*/
		LONG64 getLocalFacePerCellIndexPairs(int * localFacePerCellIndexPairs) const;

		/**
		* Indicates if the grid connection set representation is based on several grids.
		*/
		bool isBasedOnMultiGrids() const;

		/**
		* Get the grid index pairs of this grid connection representation
		* The count of gridIndexPairs must be getCellIndexPairCount()*2.
		*/
		void getGridIndexPairs(unsigned short * gridIndexPairs) const;

		/**
		* Set the cell index pairs of the grid connections representation using some exisiting hdf5 datasets.
		* @param cellIndexPairCount	The count of cell index pair. It is half of all the stored numerical values.
		* @param cellIndexPair		The HDF dataset path where we can find all the cell index pair in a 1d Array where the cell indices go faster than the pair.
		* @param nullValue			The integer null value used in the hdf dataset for null cell and potentially null grid.
		* @param proxy				The HDF proxy where the numerical values (cell indices) are stored.
        * @param gridIndexPair		The HDF dataset path where we can find all the grid index pair in a 1d Array where the grid indices go faster than the pair. The grid at an index must correspond to the cell at the same index in the cellIndexPair array.
		*/
		void setCellIndexPairsUsingExistingDataset(const ULONG64 & cellIndexPairCount, const std::string & cellIndexPair, const LONG64 & nullValue, COMMON_NS::AbstractHdfProxy * proxy, const std::string & gridIndexPair = "");

		/**
		* The numerical values
		* 2 x #Connections array of local face-per-cell indices for (Cell1,Cell2) for each connection. Local face-per-cell indices are used because global face indices need not have been defined.
		* The numerical values are already stored in an existing hdf5 dataset.
		* Null value = -1 by documentation.
		* @param localFacePerCellIndexPair	The HDF dataset path where we can find all the local Face Per CellIndex Pair in a 1d Array.
		* @param proxy						The HDF proxy where the numerical values (cell indices) are stored.
		*/
		void setLocalFacePerCellIndexPairsUsingExistingDataset(const std::string & localFacePerCellIndexPair, const LONG64 & nullValue, COMMON_NS::AbstractHdfProxy * proxy);

		/**
		* 2 x #Connections array of local face-per-cell indices for (Cell1,Cell2) for each connection. Local face-per-cell indices are used because global face indices need not have been defined.
		* The numerical values wil: be written as a new hdf5 dataset in an existing hdf5 file.
		* Null value = -1 by documentation.
        * @param cellIndexPairCount			The count of cell index pair. It is half of all the stored numerical values.
		* @param localFacePerCellIndexPair	The HDF dataset path where we can find all the local Face Per CellIndex Pair in a 1d Array.
		* @param proxy						The HDF proxy where the numerical values (cell indices) are stored.
		*/
		void setLocalFacePerCellIndexPairs(const ULONG64 & cellIndexPairCount, int * localFacePerCellIndexPair, const LONG64 & nullValue, COMMON_NS::AbstractHdfProxy * proxy);

		/**
		* For each connection in the grid connection set representation, allow to map zero or one feature interpretation. TODO: Resqml allows to map with more than one feature interpretation.
		* @param interpretationIndices		For each connection, the index of the corresponding interpretation in the interpretation set of this grid connection. The count of this array is given by the next parameter.
		* @param interpretationIndiceCount	The count of interpretation indices.
		* @param nullValue					The null value must be used as the corresponding interpretation index for each connection which are not associated to any interpretation.
		* @param proxy						The Hdf proxy where the numerical values will be stored.
		*/
		void setConnectionInterpretationIndices(unsigned int * interpretationIndices, const unsigned int & interpretationIndiceCount, const LONG64 & nullValue, COMMON_NS::AbstractHdfProxy * proxy);
		
		/**
		* Get the count of the supporting grid representations of this grid connection representation.
		*/
		unsigned int getSupportingGridRepresentationCount() const;
		
		/**
		* Get one of the supporting grid representation dor of this grid connection representation.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getSupportingGridRepresentationDor(unsigned int index) const;
	};
}

