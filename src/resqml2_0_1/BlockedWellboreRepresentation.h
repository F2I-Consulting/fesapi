/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#pragma once

#include "resqml2_0_1/WellboreFrameRepresentation.h"

namespace resqml2
{
	class AbstractGridRepresentation;
}

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT BlockedWellboreRepresentation : public WellboreFrameRepresentation
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
        
		static const char* XML_TAG;
		std::string getXmlTag() const {return XML_TAG;}
	
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
		void setIntevalGridCells(unsigned int * gridIndices, unsigned int gridIndicesNullValue, unsigned int cellCount, ULONG64* cellIndices, unsigned char* localFacePairPerCellIndices, unsigned char localFacePairPerCellIndicesNullValue, common::AbstractHdfProxy * hdfProxy);

		/**
		* The number of non-null entries in the grid indices array.
		*/
		unsigned int getCellCount() const;

		/**
		* Size of array = IntervalCount on the wellbore frame rep. The grids (and there indices) are defined using pushBackSupportingGridRepresentation method.
		* @return nullValue
		*/
		unsigned int getGridIndices(unsigned int * gridIndices) const;

		/**
		 * Pushes back a grid representation which is one of the support of this representation.
		 * And push back this representation as a grid connection information of the grid representation as well.
		 */
		void pushBackSupportingGridRepresentation(resqml2::AbstractGridRepresentation * supportingGridRep);
		
		/**
		* Get the count of the supporting grid representations of this grid connection representation.
		*/
		unsigned int getSupportingGridRepresentationCount() const;

		/**
		* Get the supporting grid representation located at a specific index of this blocked wellbore representation.
		*/
		resqml2::AbstractGridRepresentation* getSupportingGridRepresentation(unsigned int index) const;

		/**
		* Get the supporting grid representation dor located at a specific index of this blocked wellbore representation.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getSupportingGridRepresentationDor(unsigned int index) const;
		
		/**
		* Get the supporting grid representation uuid located at a specific index of this blocked wellbore representation.
		*/
		std::string getSupportingGridRepresentationUuid(unsigned int index) const;

	private:

		std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);
	};
}
