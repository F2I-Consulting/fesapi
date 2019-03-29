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

#include "resqml2_0_1/WellboreFrameRepresentation.h"

namespace RESQML2_NS
{
	class AbstractGridRepresentation;
}

namespace RESQML2_0_1_NS
{
	class BlockedWellboreRepresentation : public WellboreFrameRepresentation
	{
	private:
		void init(const std::string & guid, const std::string & title, class WellboreTrajectoryRepresentation * traj);

	public:

		/**
		* Only to be used in partial transfer context
		*/
		BlockedWellboreRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WellboreFrameRepresentation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp	The interpretation the instance represents.
		* @param guid	A guid for the instance to create.
        * @param title	A title for the instance to create.
        * @param traj	The wellbore trajectory this intance is based on.
		*/
		BlockedWellboreRepresentation(class WellboreInterpretation* interp,
			const std::string & guid, const std::string & title, class WellboreTrajectoryRepresentation * traj);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		BlockedWellboreRepresentation(gsoap_resqml2_0_1::_resqml2__BlockedWellboreRepresentation* fromGsoap) : WellboreFrameRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~BlockedWellboreRepresentation() {}
        
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const {return XML_TAG;}
	
		/**
		* Set all information about the intersected grid cells. You must first provide MD values of the frame before to use this method.
		* @param gridIndices							Size of array = IntervalCount on the wellbore frame rep. BUSINESS RULE: The cell count must equal the number of non-null entries in this array. The grids (and there indices) are defined using pushBackSupportingGridRepresentation method.
		* @param gridIndicesNullValue					The null value used in gridIndices in order to indicate that an interval deos not correspond to any intersected grid.
		* @param cellCount								The number of non-null entries in the grid indices array.
		* @param cellIndices							The intersected cell index for each non null gridIndices. They are ordered according to non null gridIndices. Array length must equal cell count.
		* @param localFacePairPerCellIndices			For each cell, these are the entry and exit intersection faces of the trajectory in the cell. The array dimensions must equal 2 x CellCount.
		* @param localFacePairPerCellIndicesNullValue	The null value used in localFacePerCellIndices in order to indicate that it corresponds to a missing intersection, e.g., when a trajectory originates or terminates within a cell.
		* @param hdfProxy								The hdf proxy where the numerical values will be stored.
		*/
		DLL_IMPORT_OR_EXPORT void setIntevalGridCells(unsigned int * gridIndices, unsigned int gridIndicesNullValue, unsigned int cellCount, ULONG64* cellIndices, unsigned char* localFacePairPerCellIndices, unsigned char localFacePairPerCellIndicesNullValue, COMMON_NS::AbstractHdfProxy * hdfProxy);

		/**
		* The number of non-null entries in the grid indices array.
		*/
		DLL_IMPORT_OR_EXPORT ULONG64 getCellCount() const;

		/**
		* Size of array = IntervalCount on the wellbore frame rep. The grids (and there indices) are defined using pushBackSupportingGridRepresentation method.
		* @return nullValue
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getGridIndices(unsigned int * gridIndices) const;

		/**
		 * Pushes back a grid representation which is one of the support of this representation.
		 * And push back this representation as a grid connection information of the grid representation as well.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackSupportingGridRepresentation(RESQML2_NS::AbstractGridRepresentation * supportingGridRep);
		
		/**
		* Get the count of the supporting grid representations of this grid connection representation.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getSupportingGridRepresentationCount() const;

		/**
		* Get the supporting grid representation located at a specific index of this blocked wellbore representation.
		*/
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractGridRepresentation* getSupportingGridRepresentation(unsigned int index) const;

		/**
		* Get the supporting grid representation dor located at a specific index of this blocked wellbore representation.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getSupportingGridRepresentationDor(unsigned int index) const;
		
		/**
		* Get the supporting grid representation uuid located at a specific index of this blocked wellbore representation.
		*/
		DLL_IMPORT_OR_EXPORT std::string getSupportingGridRepresentationUuid(unsigned int index) const;

	private:

		std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc);
	};
}
