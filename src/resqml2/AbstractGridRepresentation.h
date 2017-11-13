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

#include "resqml2/GridConnectionSetRepresentation.h"
#include "resqml2_0_1/BlockedWellboreRepresentation.h"

namespace resqml2_0_1
{
	class AbstractStratigraphicOrganizationInterpretation;
	class UnstructuredGridRepresentation;
}

namespace resqml2
{
	class DLL_IMPORT_OR_EXPORT AbstractGridRepresentation : public AbstractRepresentation
	{
	private:

		/**
		* @param	 forceConstantCellCountPerInterval	If true, will assume that the child and parent cell count per interval are constant. Then it will use constant xml array instead of hdf5 array for storage.
		*												The method will consequently only consider the first cell count per interval value in childCellCountPerInterval and parentCellCountPerInterval as the constant ones.
		**/
		gsoap_resqml2_0_1::resqml2__Regrid* createRegrid(const unsigned int & indexRegridStart, unsigned int * childCellCountPerInterval, unsigned int * parentCellCountPerInterval,  const unsigned int & intervalCount, double * childCellWeights,
			const std::string & dimension, bool forceConstantCellCountPerInterval = false);

		/*
		* @param	dimension					It must be either 'i', 'j' ou 'k' (upper or lower case) for an ijk parent grid. 'k' for a strict column layer parent grid.
		* @param	childVsParentCellCount		If true return the child cell count per interval. If false return the parent cell count per interval.
		*/
		gsoap_resqml2_0_1::resqml2__AbstractIntegerArray* getCellCountPerInterval2_0_1(const char & dimension, const bool & childVsParentCellCount) const;

		gsoap_resqml2_0_1::resqml2__AbstractParentWindow* getParentWindow2_0_1() const;

	protected:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractGridRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject, bool withTruncatedPillars) :AbstractRepresentation(partialObject), withTruncatedPillars(withTruncatedPillars)  {}
		
		/**
		* Default constructor
		*/
		AbstractGridRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs, bool withTruncatedPillars) : AbstractRepresentation(interp, crs), withTruncatedPillars(withTruncatedPillars){}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractGridRepresentation(gsoap_resqml2_0_1::resqml2__AbstractGridRepresentation* fromGsoap, bool withTruncatedPillars) : AbstractRepresentation(fromGsoap), withTruncatedPillars(withTruncatedPillars) {}

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractGridRepresentation() {}

		/**
		* Get the count of (volumic) cells in the grid.
		*/
		virtual ULONG64 getCellCount() const = 0;

		//************************************************************
		//****************** GRID CONNECTION SET *********************
		//************************************************************

		/**
		* Get the vector of all grid connection set rep asociated to this grid instance.
		*/
		std::vector<resqml2::GridConnectionSetRepresentation*> getGridConnectionSetRepresentationSet() const {return gridConnectionSetRepresentationSet;}

		/**
		 * Get the GridConnectionSetRepresentation count into this EPC document which are associated to this grid.
		 * It is mainly used in SWIG context for parsing the vector from a non C++ language.
		 */
		unsigned int getGridConnectionSetRepresentationCount() const {return gridConnectionSetRepresentationSet.size();}

		/**
		 * Get a particular ijk parametric grid according to its position in the EPC document.
		 * It is mainly used in SWIG context for parsing the vector from a non C++ language.
		 */
		resqml2::GridConnectionSetRepresentation* getGridConnectionSetRepresentation(const unsigned int & index) const;


		//************************************************************
		//******************** GRID PARENTAGE ************************
		//************************************************************

		/**
		* Get the parent grid of this grid.
		* @return	nullptr if the grid is not a child grid (not a LGR)
		*/
		AbstractGridRepresentation* getParentGrid() const;

		/**
		* Get the parent grid dor of this grid.
		* @return	null pointer if the grid is not a child grid (not a LGR)
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getParentGridDor() const;

		/**
		* Get the parent grid uuid of this grid.
		* @return	empty string if the grid is not a child grid (not a LGR)
		*/
		std::string getParentGridUuid() const;

		/**
		* Return the count of child grid in this grid.
		*/
		unsigned int getChildGridCount() const {return childGridSet.size();}

		/**
		* Return the count of child grid in this grid.
		*/
		AbstractGridRepresentation* getChildGrid(const unsigned int & index) const {return childGridSet[index];}

		/**
		* Indicates that this grid takes place into another unstructured parent grid.
		*/
		void setParentWindow(ULONG64 * cellIndices, const ULONG64 & cellIndexCount, resqml2_0_1::UnstructuredGridRepresentation* parentGrid);

		/**
		* Indicates that this grid takes place into another Column Layer parent grid.
		* @param	columnIndices				Identifies the columns (of the parent grid) which are regrided.
		* @param	columnIndexCount			Identifies the coutn of columns (of the parent grid) which are regrided.
		* @param	kLayerIndexRegridStart		Identifies the first kLayer of all above columns (of the parent grid) which is regrided.
		* @param	childCellCountPerInterval	The count of cells per interval in this (child) grid.
		* @param	parentCellCountPerInterval	The count of cells per interval in the parent grid.
		* @param	intervalCount				The count of intervals. An interval is a portion of cells to regrid which is independant to other portion of cell. Intervals are the same for all the columns.
		* @param	parentGrid					The parent grid which is regridded.
		* @param	childCellWeights			The weights that are proportional to the relative sizes of child cells within each interval. The weights need not to be normalized. The count of double values must be equal to the count of all child cells per column (sum of child cells per interval).
		*/
		void setParentWindow(unsigned int * columnIndices, const unsigned int & columnIndexCount,
			const unsigned int & kLayerIndexRegridStart,
			unsigned int * childCellCountPerInterval, unsigned int * parentCellCountPerInterval,  const unsigned int & intervalCount,
			class AbstractColumnLayerGridRepresentation* parentGrid, double * childCellWeights = nullptr);

		/**
		* Indicates that this grid takes place into another IJK parent grid.
		* @param	iCellIndexRegridStart		Identifies the first Cell by its i dimension of the regrid window.
		* @param	childCellCountPerIInterval	The count of cells per i interval in this (child) grid.
		* @param	parentCellCountPerIInterval	The count of cells per i interval in the parent grid.
		* @param	iIntervalCount				The count of intervals on i dimension. An interval is a portion of cells to regrid which is independant to other portion of cell.
		* @param	jCellIndexRegridStart		Identifies the first Cell by its j dimension of the regrid window.
		* @param	childCellCountPerJInterval	The count of cells per j interval in this (child) grid.
		* @param	parentCellCountPerJInterval	The count of cells per j interval in the parent grid.
		* @param	jIntervalCount				The count of intervals on j dimension. An interval is a portion of cells to regrid which is independant to other portion of cell.
		* @param	kCellIndexRegridStart		Identifies the first Cell by its k dimension of the regrid window.
		* @param	childCellCountPerKInterval	The count of cells per k interval in this (child) grid.
		* @param	parentCellCountPerKInterval	The count of cells per k interval in the parent grid.
		* @param	kIntervalCount				The count of intervals on k dimension. An interval is a portion of cells to regrid which is independant to other portion of cell.
		* @param	parentGrid					The parent grid which is regridded.
		* @param	iChildCellWeights			The weights that are proportional to the relative i sizes of child cells within each i interval. The weights need not to be normalized. The count of double values must be equal to the count of all child cells on i dimension (sum of child cells per interval).
		* @param	jChildCellWeights			The weights that are proportional to the relative j sizes of child cells within each j interval. The weights need not to be normalized. The count of double values must be equal to the count of all child cells on j dimension (sum of child cells per interval).
		* @param	kChildCellWeights			The weights that are proportional to the relative k sizes of child cells within each k interval. The weights need not to be normalized. The count of double values must be equal to the count of all child cells on k dimension (sum of child cells per interval).
		*/
		void setParentWindow(
			const unsigned int & iCellIndexRegridStart, unsigned int * childCellCountPerIInterval, unsigned int * parentCellCountPerIInterval,  const unsigned int & iIntervalCount,
			const unsigned int & jCellIndexRegridStart, unsigned int * childCellCountPerJInterval, unsigned int * parentCellCountPerJInterval,  const unsigned int & jIntervalCount,
			const unsigned int & kCellIndexRegridStart, unsigned int * childCellCountPerKInterval, unsigned int * parentCellCountPerKInterval,  const unsigned int & kIntervalCount,
			resqml2_0_1::AbstractIjkGridRepresentation* parentGrid, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);

		/**
		* Indicates that this grid takes place into another IJK parent grid.
		* @param	iCellIndexRegridStart				Identifies the first Cell by its i dimension of the regrid window.
		* @param	constantChildCellCountPerIInterval	The constant count of cells per i interval in this (child) grid.
		* @param	constantParentCellCountPerIInterval	The constant count of cells per i interval in the parent grid.
		* @param	iIntervalCount						The count of intervals on i dimension. An interval is a portion of cells to regrid which is independant to other portion of cell.
		* @param	jCellIndexRegridStart				Identifies the first Cell by its j dimension of the regrid window.
		* @param	constantChildCellCountPerJInterval	The constant count of cells per j interval in this (child) grid.
		* @param	constantParentCellCountPerJInterval	The constant count of cells per j interval in the parent grid.
		* @param	jIntervalCount						The count of intervals on j dimension. An interval is a portion of cells to regrid which is independant to other portion of cell.
		* @param	kCellIndexRegridStart				Identifies the first Cell by its k dimension of the regrid window.
		* @param	constantChildCellCountPerKInterval	The constant count of cells per k interval in this (child) grid.
		* @param	constantParentCellCountPerKInterval	The constant count of cells per k interval in the parent grid.
		* @param	kIntervalCount						The count of intervals on k dimension. An interval is a portion of cells to regrid which is independant to other portion of cell.
		* @param	parentGrid							The parent grid which is regridded.
		* @param	iChildCellWeights					The weights that are proportional to the relative i sizes of child cells within each i interval. The weights need not to be normalized. The count of double values must be equal to the count of all child cells on i dimension (sum of child cells per interval).
		* @param	jChildCellWeights					The weights that are proportional to the relative j sizes of child cells within each j interval. The weights need not to be normalized. The count of double values must be equal to the count of all child cells on j dimension (sum of child cells per interval).
		* @param	kChildCellWeights					The weights that are proportional to the relative k sizes of child cells within each k interval. The weights need not to be normalized. The count of double values must be equal to the count of all child cells on k dimension (sum of child cells per interval).
		*/
		void setParentWindow(
			const unsigned int & iCellIndexRegridStart, unsigned int constantChildCellCountPerIInterval, unsigned int constantParentCellCountPerIInterval, const unsigned int & iIntervalCount,
			const unsigned int & jCellIndexRegridStart, unsigned int constantChildCellCountPerJInterval, unsigned int constantParentCellCountPerJInterval, const unsigned int & jIntervalCount,
			const unsigned int & kCellIndexRegridStart, unsigned int constantChildCellCountPerKInterval, unsigned int constantParentCellCountPerKInterval, const unsigned int & kIntervalCount,
			resqml2_0_1::AbstractIjkGridRepresentation* parentGrid, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);

		/**
		* Indicates that this grid takes place into another IJK parent grid.
		* This method assumes there is only one regrid interval per dimension.
		* @param	iCellIndexRegridStart		Identifies the first Cell by its i dimension of the regrid window.
		* @param	iChildCellCount				The count of cells per i interval in this (child) grid.
		* @param	iParentCellCount			The count of cells per i interval in the parent grid.
		* @param	jCellIndexRegridStart		Identifies the first Cell by its j dimension of the regrid window.
		* @param	jChildCellCount				The count of cells per j interval in this (child) grid.
		* @param	jParentCellCount			The count of cells per j interval in the parent grid.
		* @param	kCellIndexRegridStart		Identifies the first Cell by its k dimension of the regrid window.
		* @param	kChildCellCount				The count of cells per k interval in this (child) grid.
		* @param	kParentCellCount			The count of cells per k interval in the parent grid.
		* @param	parentGrid					The parent grid which is regridded.
		* @param	iChildCellWeights			The weights that are proportional to the relative i sizes of child cells. The weights need not to be normalized. The count of double values must be equal to iChildCellCount.
		* @param	jChildCellWeights			The weights that are proportional to the relative j sizes of child cells. The weights need not to be normalized. The count of double values must be equal to jChildCellCount.
		* @param	kChildCellWeights			The weights that are proportional to the relative k sizes of child cells. The weights need not to be normalized. The count of double values must be equal to kChildCellCount.
		*/
		void setParentWindow(
			const unsigned int & iCellIndexRegridStart, unsigned int iChildCellCount, unsigned int iParentCellCount,
			const unsigned int & jCellIndexRegridStart, unsigned int jChildCellCount, unsigned int jParentCellCount,
			const unsigned int & kCellIndexRegridStart, unsigned int kChildCellCount, unsigned int kParentCellCount,
			resqml2_0_1::AbstractIjkGridRepresentation* parentGrid, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);

		/**
		* When a parent windows has been defined, this method allows to force some parent cells to be noted as non regridded.
		* It mainly allows non-rectangular local grids to be specified.
		*/
		void setForcedNonRegridedParentCell(ULONG64 * cellIndices, const ULONG64 & cellIndexCount);

		/**
		* Optional cell volume overlap information between the current grid (the child) and the parent grid. Use this data-object when the child grid has an explicitly defined geometry, and these relationships cannot be inferred from the regrid descriptions.
		*/
		void setCellOverlap(const ULONG64 & parentChildCellPairCount, ULONG64 * parentChildCellPair,
			const gsoap_resqml2_0_1::eml20__VolumeUom & volumeUom = gsoap_resqml2_0_1::eml20__VolumeUom__m3, double * overlapVolumes = nullptr);

		/**
		* Only run this method for an unstructured parent grid.
		* Use regrid information for ijk parent grid or (regrid and columIndexCount) for strict column layer parent grid.
		*/
		LONG64 getParentCellIndexCount() const;

		/**
		* Only run this method for an unstructured parent grid.
		* @param parentCellIndices	This array must have been preallocated with a size of getParentCellIndexCount().
		*/
		void getParentCellIndices(ULONG64 * parentCellIndices) const;

		/**
		* Only run this method for a strict column layer parent grid.
		*/
		LONG64 getParentColumnIndexCount() const;

		/**
		* Only run this method for an unstructured parent grid.
		* @param parentCellIndices	This array must have been preallocated with a size of getParentCellIndexCount().
		*/
		void getParentColumnIndices(ULONG64 * parentColumnIndices) const;

		/**
		* Only run this method for an ijk parent grid or a strict column layer parent grid.
		* Get the first cell index of the regrid on a particular dimension.
		* @param	dimension	It must be either 'i', 'j' ou 'k' (upper or lower case) for an ijk parent grid. 'k' for a strict column layer parent grid.
		*/
		ULONG64 getRegridStartIndexOnParentGrid(const char & dimension) const;

		/**
		* Only run this method for an ijk parent grid or a strict column layer parent grid.
		* Get the count of intervals which are regridded on a particular dimension
		* @param	dimension	It must be either 'i', 'j' ou 'k' (upper or lower case) for an ijk parent grid. 'k' for a strict column layer parent grid.
		*/
		ULONG64 getRegridIntervalCount(const char & dimension) const;

		/**
		* Check if the cell count per interval is constant against a particular dimension.
		* Only run this method for an ijk parent grid or a strict column layer parent grid.
		* @param	dimension					It must be either 'i', 'j' ou 'k' (upper or lower case) for an ijk parent grid. 'k' for a strict column layer parent grid.
		* @param	childVsParentCellCount		If true check if the child cell count per interval is constant. If false check if the parent cell count per interval is constant.
		*/
		bool isRegridCellCountPerIntervalConstant(const char & dimension, const bool & childVsParentCellCount) const;

		/*
		* Get the constant cell count per interval
		* Only run this method for an ijk parent grid or a strict column layer parent grid.
		* @param	dimension					It must be either 'i', 'j' ou 'k' (upper or lower case) for an ijk parent grid. 'k' for a strict column layer parent grid.
		* @param	childVsParentCellCount		If true return the child cell count per interval. If false return the parent cell count per interval.
		*/
		ULONG64 getRegridConstantCellCountPerInterval(const char & dimension, const bool & childVsParentCellCount) const;

		/**
		* Only run this method for an ijk parent grid or a strict column layer parent grid.
		* @param	dimension					It must be either 'i', 'j' ou 'k' (upper or lower case) for an ijk parent grid. 'k' for a strict column layer parent grid.
		* @param	childCellCountPerInterval	This array must have been preallocated with a size of getRegridIntervalCount().
		* @param	childVsParentCellCount		If true return the child cell count per interval. If false return the parent cell count per interval.
		*/
		void getRegridCellCountPerInterval(const char & dimension, ULONG64 * childCellCountPerInterval, const bool & childVsParentCellCount) const;

		/**
		* Only run this method for an ijk parent grid or a strict column layer parent grid.
		* @param	dimension					It must be either 'i', 'j' ou 'k' (upper or lower case) for an ijk parent grid. 'k' for a strict column layer parent grid.
		*/
		bool hasRegridChildCellWeights(const char & dimension) const;

		/**
		* Only run this method for an ijk parent grid or a strict column layer parent grid.
		* @param	dimension			It must be either 'i', 'j' ou 'k' (upper or lower case) for an ijk parent grid. 'k' for a strict column layer parent grid.
		* @param	childCellWeights	This array must have been preallocated with a size equal to the sum of ChildCellCountPerInterval.
		*/
		void getRegridChildCellWeights(const char & dimension, ULONG64 * childCellWeights) const;

		/**
		* When a parent windows has been defined, this method checks if some parent cells have been noted to be forced not to be regridded.
		* It mainly occurs in case of non-rectangular local grids.
		*/
		bool hasForcedNonRegridedParentCell() const;

		//************************************************************
		//**************** LINK WITH STRATIGRAPHY ********************
		//************************************************************

		/**
		* Set the stratigraphic organization interpretation which is associated to this grid representation.
		* @param stratiUnitIndices	Index of the stratigraphic unit of a given stratigraphic column for each cell. Array length is the number of cells in the grid or the blocked well.
		* @param nullValue			The value which is used to tell the association between a cell and strati unit is unavailable.
		* @param stratiOrgInterp	The stratigraphic organization interpretation which is associated to this grid representation.
		*/
		void setCellAssociationWithStratigraphicOrganizationInterpretation(ULONG64 * stratiUnitIndices, const ULONG64 & nullValue, resqml2_0_1::AbstractStratigraphicOrganizationInterpretation* stratiOrgInterp);

		/**
		* @return	nullptr if no stratigraphic organization interpretation is associated to this grid representation. Otherwise return the associated stratigraphic organization interpretation.
		*/
		resqml2_0_1::AbstractStratigraphicOrganizationInterpretation* getStratigraphicOrganizationInterpretation() const;

		/**
		* @return	null pointer if no stratigraphic organization interpretation is associated to this grid representation. Otherwise return the data objet reference of the associated stratigraphic organization interpretation.
		*/
		virtual gsoap_resqml2_0_1::eml20__DataObjectReference* getStratigraphicOrganizationInterpretationDor() const;

		/**
		* @return	empty string if no stratigraphic organization interpretation is associated to this grid representation. Otherwise return the uuid of the associated stratigraphic organization interpretation.
		*/
		std::string getStratigraphicOrganizationInterpretationUuid() const;

		/**
		* @return	empty string if no stratigraphic organization interpretation is associated to this grid representation. Otherwise return the title of the associated stratigraphic organization interpretation.
		*/
		std::string getStratigraphicOrganizationInterpretationTitle() const;
		
		/**
		* @return	true if this grid representation has got some association between stratigraphic unit indices and cell.
		*/
		bool hasCellStratigraphicUnitIndices() const;

		/**
		* Get the stratigraphic unit indices (regarding the associated stratigraphic organization interpretation) of each cell of this grid representation.
		* @param stratiUnitIndices	This array must be allocated with a count equal to getCellCount(). It will be filled in with the stratigraphic unit indices ordered as grid cells are ordered.
		* @return					The null value is returned. The null value is used to tell the association between a cell and strati unit is unavailable.
		*/
		ULONG64 getCellStratigraphicUnitIndices(ULONG64 * stratiUnitIndices);

		//************************************************************
		//********************** TRUNCATION **************************
		//************************************************************

		/**
		* Indicates wether this grid instance contains truncated pillars or not.
		*/
		bool isTruncated() const;

		/**
		* Get the truncation face count. It does not include face of truncated cells whch are not truncated.
		*/
		ULONG64 getTruncatedFaceCount() const;

		/**
		* Get all the node indices of the truncated faces.
		* @param nodeIndices 			It must be pre allocated with the last value returned by getCumulativeNodeCountOfTruncatedFaces().
		*/
		void getNodeIndicesOfTruncatedFaces(ULONG64 * nodeIndices) const;

		/**
		* Get the cumulative node count per truncated face. First value is the count of nodes in the first face.
		* Second value is the count of nodes in the first and in the second face. Third value is the count of nodes in the first and in the second and in the third face. Etc...
		* Count of this array is equal to getTruncatedFaceCount()
		* A single node count should be at least 3.
		* @param nodeCountPerFace	It must be pre allocated with getTruncatedFaceCount() == last value of getCumulativeTruncatedFaceCountPerTruncatedCell()
		*/
		void getCumulativeNodeCountPerTruncatedFace(ULONG64 * nodeCountPerFace) const;

		/**
		* Less efficient than getCumulativeNodeCountPerTruncatedFace.
		* Get the node count per truncated face. First value is the count of nodes in the first face.
		* Second value is the count of nodes in the second face. etc...
		* @param nodeCountPerFace	It must be pre allocated with getTruncatedFaceCount() == last value of getCumulativeTruncatedFaceCountPerTruncatedCell()
		*/
		void getNodeCountPerTruncatedFace(ULONG64 * nodeCountPerFace) const;

		/**
		* Get the truncated cell count.
		*/
		ULONG64 getTruncatedCellCount() const;

		/**
		* Get the the indices of the truncated cells in the non truncated grid.
		*/
		void getTruncatedCellIndices(ULONG64* cellIndices) const;

		/**
		* Get all the truncated face indices of all the truncated cells. It does not get the non truncated face indices of a truncated cell.
		* Please use getNonTruncatedFaceIndicesOfTruncatedCells(ULONG64 * faceIndices) in addition to this method in order to get the full list of face indices for a truncated cell.
		* @param faceIndices 			It must be pre allocated with the last value returned by getCumulativeTruncatedFaceCountPerTruncatedCell()
		*/
		void getTruncatedFaceIndicesOfTruncatedCells(ULONG64 * faceIndices) const;

		/**
		* Get the cumulative truncated face count per truncated cell. It does not take into account the non truncated face indices of a truncated cell.
		* First value is the count of faces in the first cell.
		* Second value is the count of faces in the first and in the second cell. Third value is the count of faces in the first and in the second and in the third cell. Etc...
		* Count of this array is equal to getCellCount()
		* A single face count should be at least 4.
		* @param cumulativeFaceCountPerCellIndex	It must be pre allocated with getTruncatedCellCount()
		*/
		void getCumulativeTruncatedFaceCountPerTruncatedCell(ULONG64 * cumulativeFaceCountPerCell) const;

		/**
		* Less efficient than getCumulativeTruncatedFaceCountPerTruncatedCell.
		* Get the face count per cell. First value is the count of faces in the first cell.
		* Second value is the count of faces in the second cell. etc...
		* @param faceCountPerCell	It must be pre allocated with getTruncatedCellCount()
		*/
		void getTruncatedFaceCountPerTruncatedCell(ULONG64 * faceCountPerCell) const;

		/**
		* Get all the truncated face indices of all the truncated cells. It does not get the non truncated face indices of a truncated cell.
		* Please use getNonTruncatedFaceIndicesOfTruncatedCells(ULONG64 * faceIndices) in addition to this method in order to get the full list of face indices for a truncated cell.
		* @param faceIndices 			It must be pre allocated with the last value returned by getCumulativeTruncatedFaceCountPerTruncatedCell()
		*/
		void getNonTruncatedFaceIndicesOfTruncatedCells(ULONG64 * faceIndices) const;

		/**
		* Get the cumulative truncated face count per truncated cell. It does not take into account the non truncated face indices of a truncated cell.
		* First value is the count of faces in the first cell.
		* Second value is the count of faces in the first and in the second cell. Third value is the count of faces in the first and in the second and in the third cell. Etc...
		* Count of this array is equal to getCellCount()
		* A single face count should be at least 4.
		* @param cumulativeFaceCountPerCellIndex	It must be pre allocated with getTruncatedCellCount()
		*/
		void getCumulativeNonTruncatedFaceCountPerTruncatedCell(ULONG64 * cumulativeFaceCountPerCell) const;

		/**
		* Less efficient than getCumulativeTruncatedFaceCountPerTruncatedCell.
		* Get the face count per cell. First value is the count of faces in the first cell.
		* Second value is the count of faces in the second cell. etc...
		* @param faceCountPerCell	It must be pre allocated with getTruncatedCellCount()
		*/
		void getNonTruncatedFaceCountPerTruncatedCell(ULONG64 * faceCountPerCell) const;

		/**
		* Retrieves orientation i.e. if each truncated face is right handed or not
		* @param cellFaceIsRightHanded	It must be pre allocated with getTruncatedFaceCount()
		*/
		void getTruncatedFaceIsRightHanded(unsigned char* cellFaceIsRightHanded) const;

		static const char* XML_TAG;

	protected:

		virtual std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		bool withTruncatedPillars;

		std::vector<AbstractGridRepresentation*> childGridSet;

		std::vector<resqml2::GridConnectionSetRepresentation*> gridConnectionSetRepresentationSet;
		std::vector<resqml2_0_1::BlockedWellboreRepresentation*> blockedWellboreRepresentationSet;

		friend void GridConnectionSetRepresentation::pushBackSupportingGridRepresentation(AbstractGridRepresentation * supportingGridRep);
		friend void resqml2_0_1::BlockedWellboreRepresentation::pushBackSupportingGridRepresentation(resqml2::AbstractGridRepresentation * supportingGridRep);

	};
}
