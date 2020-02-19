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

#include "GridConnectionSetRepresentation.h"
#include "../resqml2_0_1/BlockedWellboreRepresentation.h"

/** . */
namespace RESQML2_0_1_NS
{
	class AbstractStratigraphicOrganizationInterpretation;
	class UnstructuredGridRepresentation;
}

/** . */
namespace RESQML2_NS
{
	/** Proxy class for an abstract grid representation. */
	class AbstractGridRepresentation : public AbstractRepresentation
	{
	private:

		/**
		 * Creates a regrid
		 *
		 * @param 		  	indexRegridStart				 	The index regrid start.
		 * @param [in,out]	childCellCountPerInterval		 	If non-null, the child cell count per
		 * 														interval.
		 * @param [in,out]	parentCellCountPerInterval		 	If non-null, the parent cell count per
		 * 														interval.
		 * @param 		  	intervalCount					 	Number of intervals.
		 * @param [in,out]	childCellWeights				 	If non-null, the child cell weights.
		 * @param 		  	dimension						 	The dimension.
		 * @param [in,out]	proxy							 	If non-null, the proxy.
		 * @param 		  	forceConstantCellCountPerInterval	(Optional) If true, will assume that the
		 * 														child and parent cell count per interval
		 * 														are constant. Then it will use constant
		 * 														xml array instead of hdf5 array for
		 * 														storage. The method will consequently
		 * 														only consider the first cell count per
		 * 														interval value in
		 * 														childCellCountPerInterval and
		 * 														parentCellCountPerInterval as the
		 * 														constant ones.
		 *
		 * @returns	Null if it fails, else the new regrid.
		 */
		gsoap_resqml2_0_1::resqml20__Regrid* createRegrid(unsigned int indexRegridStart, unsigned int * childCellCountPerInterval, unsigned int * parentCellCountPerInterval, unsigned int intervalCount, double * childCellWeights,
			const std::string & dimension, COMMON_NS::AbstractHdfProxy * proxy, bool forceConstantCellCountPerInterval = false);

		/**
		 * Gets cell count per interval 2 0 1
		 *
		 * @param 	dimension			  	It must be either 'i', 'j' ou 'k' (upper or lower case) for
		 * 									an ijk parent grid. 'k' for a strict column layer parent grid.
		 * @param 	childVsParentCellCount	If true return the child cell count per interval. If false
		 * 									return the parent cell count per interval.
		 *
		 * @returns	Null if it fails, else the cell count per interval 2 0 1.
		 */
		gsoap_resqml2_0_1::resqml20__AbstractIntegerArray* getCellCountPerInterval2_0_1(const char & dimension, const bool & childVsParentCellCount) const;

		/**
		 * Gets the parent window 2 0 1
		 *
		 * @returns	Null if it fails, else the parent window 2 0 1.
		 */
		gsoap_resqml2_0_1::resqml20__AbstractParentWindow* getParentWindow2_0_1() const;

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject			If non-null, the partial object.
		 * @param 		  	withTruncatedPillars	True to with truncated pillars.
		 */
		AbstractGridRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject, bool withTruncatedPillars) :AbstractRepresentation(partialObject), withTruncatedPillars(withTruncatedPillars)  {}

		/**
		 * Default constructor
		 *
		 * @param 	withTruncatedPillars	True to with truncated pillars.
		 */
		AbstractGridRepresentation(bool withTruncatedPillars) : withTruncatedPillars(withTruncatedPillars){}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap				If non-null, from gsoap.
		 * @param 		  	withTruncatedPillars	True to with truncated pillars.
		 */
		AbstractGridRepresentation(gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation* fromGsoap, bool withTruncatedPillars) : AbstractRepresentation(fromGsoap), withTruncatedPillars(withTruncatedPillars) {}

	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~AbstractGridRepresentation() {}

		/**
		 * Gets the count of (volumetric) cells in the grid.
		 *
		 * @exception	std::range_error	If the cell count is strictly greater than unsigned int max.
		 *
		 * @returns	The cell count.
		 */
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getCellCount() const = 0;

		//************************************************************
		//****************** GRID CONNECTION SET *********************
		//************************************************************

		/**
		 * Gets the vector of all grid connection set representations associated to this grid instance.
		 *
		 * @returns	A vector of pointers to all grid connection set representations associated to this grid instance.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_NS::GridConnectionSetRepresentation *> getGridConnectionSetRepresentationSet() const;

		/**
		 * Gets the count of grid connection set representations associated to this grid instance.
		 *
		 * @exception	std::range_error	If the count of grid connection set representations is
		 * 									strictly greater than unsigned int max.
		 *
		 * @returns	The count of grid connection set representations associated to this grid instance.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getGridConnectionSetRepresentationCount() const; // It is mainly used in SWIG context for parsing the vector from a non C++ language.

		/**
		 * Gets a particular grid connection set representation associated to this grid representation.
		 *
		 * @exception	std::out_of_range	If @p index is out of range (greater than {@link getGridConnectionSetRepresentationCount()}).
		 *
		 * @param 	index	Zero-based index of the grid connection set representation we look for.
		 *
		 * @returns	The grid connection set representation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::GridConnectionSetRepresentation * getGridConnectionSetRepresentation(unsigned int index) const; // It is mainly used in SWIG context for parsing the vector from a non C++ language.


		//************************************************************
		//******************** GRID PARENTAGE ************************
		//************************************************************

		/**
		 * Gets the parent grid of this grid.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	If the parent window of this grid is neither an IJK, column
		 * 									layer nor cell window.
		 *
		 * @returns	nullptr if this grid is not a child grid (not an LGR), otherwise the parent grid.
		 */
		DLL_IMPORT_OR_EXPORT AbstractGridRepresentation* getParentGrid() const;

		/**
		 * Gets the data object reference of the parent grid of this grid.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	If the parent window of this grid is neither an IJK, column
		 * 									layer nor cell window.
		 *
		 * @returns	nullptr if this grid is not a child grid (not a LGR), otherwise the data object
		 * 			reference of the parent grid.
		 */
		gsoap_resqml2_0_1::eml20__DataObjectReference* getParentGridDor() const;

		/**
		 * Get the UUID of the parent of this grid.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	If the parent window of this grid is neither an IJK, column
		 * 									layer nor cell window.
		 *
		 * @returns	Empty string if the grid is not a child grid (not a LGR), otherwise the UUID of the
		 * 			parent grid.
		 */
		DLL_IMPORT_OR_EXPORT std::string getParentGridUuid() const;

		/**
		 * Gets the vector of all child grids of this grid.
		 *
		 * @returns	A vector of pointers to all child grids of this grid.
		 */
		std::vector<RESQML2_NS::AbstractGridRepresentation *> getChildGridSet() const;

		/**
		 * Gets the count of child grids of this grid.
		 *
		 * @exception	std::range_error	If the count of child grids is strictly greater than unsigned
		 * 									int max.
		 *
		 * @returns	The count of child grids of this grid.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getChildGridCount() const;

		/**
		 * Gets a particular child grid of this grid.
		 *
		 * @exception	std::out_of_range	If @p index is out of range (greater than {@link
		 * 									getChildGridCount()}).
		 *
		 * @param 	index	Zero-based index of the the child grid we look for.
		 *
		 * @returns	The child grid at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT AbstractGridRepresentation * getChildGrid(unsigned int index) const;

		/**
		 * Indicates that this grid takes place into another unstructured parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p cellIndexCount is 0 or @p cellIndices is nullptr or
		 * 										@p parentGrid is nullptr.
		 * @exception	std::invalid_argument	If <tt>cellIndexCount &gt; 1</tt> and @p proxy is
		 * 										nullptr and no default HDF proxy is defined in the
		 * 										repository.
		 *
		 * @param [in]	  	cellIndices   	Identifies the cells (of the parent grid) which are regridded.
		 * @param 		  	cellIndexCount	Identifies the count of cells (of the parent grid) which are
		 * 									regridded. // philippe
		 * 									http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-500-200-0-R-sv2010.html
		 * 									: "BUSINESS RULE: Number of cells must be consistent with the
		 * 									child grid cell count.".
		 * @param [in]	  	parentGrid	  	The parent grid which is regridded.
		 * @param [in,out]	proxy		  	(Optional) The HDF proxy where to store the numerical values.
		 * 									If nullptr (default), then the proxy will be the default
		 * 									proxy of the repository. This parameter is unused if @p
		 * 									cellIndexCount is 1 since no numerical value need to be store
		 * 									in an HDF proxy (pure XML).
		 */
		DLL_IMPORT_OR_EXPORT void setParentWindow(ULONG64 * cellIndices, ULONG64 cellIndexCount, RESQML2_0_1_NS::UnstructuredGridRepresentation* parentGrid, COMMON_NS::AbstractHdfProxy * proxy = nullptr);

		/**
		 * Indicates that this grid takes place into another column layer parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p columnIndices is nullptr or @p columnIndexCount is
		 * 										0 or
		 * 										@p childCellCountPerInterval is nullptr or @p
		 * 										parentCellCountPerInterval is nullptr or @p intervalCount
		 * 										is 0 or @p parentGrid is nullptr.
		 * @exception	std::invalid_argument	If an HDF proxy is required to store numerical values but
		 * 										@p proxy is nullptr and no default HDF proxy is defined
		 * 										in the repository.
		 *
		 * @param [in]	  	columnIndices			  	Identifies the columns (of the parent grid) which
		 * 												are regridded. The size is @p columnIndexCount.
		 * @param 		  	columnIndexCount		  	Identifies the count of columns (of the parent
		 * 												grid) which are regridded.
		 * @param 		  	kLayerIndexRegridStart	  	K index of the first K layer of all above parent
		 * 												grid columns to be regridded.
		 * @param [in]	  	childCellCountPerInterval 	The count of cells per K interval in this (child)
		 * 												grid. The size is @p intervalCount.
		 * @param [in]	  	parentCellCountPerInterval	The count of cells per K interval in the parent
		 * 												grid. The size is @p intervalCount.
		 * @param 		  	intervalCount			  	The count of intervals on K dimension. Intervals
		 * 												are portions of cells to regrid which does not
		 * 												overlap with each others. Intervals are the same
		 * 												for all the regridded columns.
		 * @param [in]	  	parentGrid				  	The parent grid which is regridded.
		 * @param [in,out]	proxy					  	(Optional) The HDF proxy where to store the
		 * 												numerical values. If nullptr (default), then the
		 * 												proxy will be the default proxy of the
		 * 												repository. This parameter is unused if no
		 * 												numerical value need to be store in an HDF proxy
		 * 												(pure XML).
		 * @param [in]	  	childCellWeights		  	(Optional) The weights that are proportional to
		 * 												the relative K sizes of child cells within each K
		 * 												interval. This is useful to set up child cells of
		 * 												different K sizes inside the intervals. The
		 * 												weights need not to be normalized. The count of
		 * 												double values must be equal to the count of all
		 * 												child cells on K dimension (sum of child cells
		 * 												per interval). Default value is nullptr.
		 */
		DLL_IMPORT_OR_EXPORT void setParentWindow(unsigned int * columnIndices, unsigned int columnIndexCount,
			unsigned int kLayerIndexRegridStart,
			unsigned int * childCellCountPerInterval, unsigned int * parentCellCountPerInterval,  unsigned int intervalCount,
			class AbstractColumnLayerGridRepresentation* parentGrid,
			COMMON_NS::AbstractHdfProxy * proxy = nullptr, double * childCellWeights = nullptr);

		/**
		 * Indicates that this grid takes place into another IJK parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p childCellCountPerIInterval is nullptr or @p
		 * 										parentCellCountPerIInterval is nullptr or @p
		 * 										iIntervalCount is 0 or @p childCellCountPerJInterval is
		 * 										nullptr or @p parentCellCountPerJInterval is nullptr or
		 * 										@p jIntervalCount is 0 or @p childCellCountPerKInterval
		 * 										is nullptr or @p parentCellCountPerKInterval is nullptr
		 * 										or @p kIntervalCount is 0 or @p parentGrid is nullptr.
		 * @exception	std::invalid_argument	If an HDF proxy is required to store numerical values but
		 * 										@p proxy is nullptr and no default HDF proxy is defined
		 * 										in the repository.
		 *
		 * @param 		  	iCellIndexRegridStart	   	I index of the first parent grid cell to be
		 * 												regridded.
		 * @param [in]	  	childCellCountPerIInterval 	The count of cells per I interval in this (child)
		 * 												grid. The size is @p iIntervalCount.
		 * @param [in]	  	parentCellCountPerIInterval	The count of cells per I interval in the parent
		 * 												grid. The size is @p iIntervalCount.
		 * @param 		  	iIntervalCount			   	The count of intervals on I dimension. Intervals
		 * 												are portions of cells to regrid which does not
		 * 												overlap with each others.
		 * @param 		  	jCellIndexRegridStart	   	J index of the first parent grid cell to be
		 * 												regridded.
		 * @param [in]	  	childCellCountPerJInterval 	The count of cells per J interval in this (child)
		 * 												grid. The size is @p jIntervalCount.
		 * @param [in]	  	parentCellCountPerJInterval	The count of cells per J interval in the parent
		 * 												grid. The size is @p jIntervalCount.
		 * @param 		  	jIntervalCount			   	The count of intervals on J dimension. Intervals
		 * 												are portions of cells to regrid which does not
		 * 												overlap with each others.
		 * @param 		  	kCellIndexRegridStart	   	K index of the first parent grid cell to be
		 * 												regridded.
		 * @param [in]	  	childCellCountPerKInterval 	The count of cells per K interval in this (child)
		 * 												grid. The size is @p kIntervalCount.
		 * @param [in]	  	parentCellCountPerKInterval	The count of cells per K interval in the parent
		 * 												grid. The size is @p kIntervalCount.
		 * @param 		  	kIntervalCount			   	The count of intervals on K dimension. Intervals
		 * 												are portions of cells to regrid which does not
		 * 												overlap with each others.
		 * @param [in]	  	parentGrid				   	The parent grid which is regridded.
		 * @param [in,out]	proxy					   	(Optional) The HDF proxy where to store the
		 * 												numerical values. If nullptr (default), then the
		 * 												proxy will be the default proxy of the
		 * 												repository. This parameter is unused if no
		 * 												numerical value need to be store in an HDF proxy
		 * 												(pure XML).
		 * @param [in]	  	iChildCellWeights		   	(Optional) The weights that are proportional to
		 * 												the relative I sizes of child cells within each I
		 * 												interval. This is useful to set up child cells of
		 * 												different I sizes inside the intervals. The
		 * 												weights need not to be normalized. The count of
		 * 												double values must be equal to the count of all
		 * 												child cells on I dimension (sum of child cells
		 * 												per interval). Default value is nullptr.
		 * @param [in]	  	jChildCellWeights		   	(Optional) The weights that are proportional to
		 * 												the relative J sizes of child cells within each J
		 * 												interval. This is useful to set up child cells of
		 * 												different J sizes inside the intervals. The
		 * 												weights need not to be normalized. The count of
		 * 												double values must be equal to the count of all
		 * 												child cells on J dimension (sum of child cells
		 * 												per interval). Default value is nullptr.
		 * @param [in]	  	kChildCellWeights		   	(Optional) The weights that are proportional to
		 * 												the relative K sizes of child cells within each K
		 * 												interval. This is useful to set up child cells of
		 * 												different K sizes inside the intervals. The
		 * 												weights need not to be normalized. The count of
		 * 												double values must be equal to the count of all
		 * 												child cells on K dimension (sum of child cells
		 * 												per interval). Default value is nullptr.
		 */
		DLL_IMPORT_OR_EXPORT void setParentWindow(
			unsigned int iCellIndexRegridStart, unsigned int * childCellCountPerIInterval, unsigned int * parentCellCountPerIInterval,  unsigned int iIntervalCount,
			unsigned int jCellIndexRegridStart, unsigned int * childCellCountPerJInterval, unsigned int * parentCellCountPerJInterval,  unsigned int jIntervalCount,
			unsigned int kCellIndexRegridStart, unsigned int * childCellCountPerKInterval, unsigned int * parentCellCountPerKInterval,  unsigned int kIntervalCount,
			RESQML2_0_1_NS::AbstractIjkGridRepresentation* parentGrid, COMMON_NS::AbstractHdfProxy * proxy = nullptr, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);

		/**
		 * Indicates that this grid takes place into another IJK parent grid. This method assumes that
		 * the count of cells per regrid interval is constant in both child and parent grids.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p constantChildCellCountPerIInterval is 0 or @p
		 * 										constantParentCellCountPerIInterval is 0 or @p
		 * 										iIntervalCount is 0 or
		 * 										@p constantChildCellCountPerJInterval is 0 or @p
		 * 										constantParentCellCountPerJInterval is 0 or @p
		 * 										jIntervalCount is 0 or
		 * 										@p constantChildCellCountPerKInterval is 0 or @p
		 * 										constantParentCellCountPerKInterval is 0 or @p
		 * 										kIntervalCount is 0 or
		 * 										@p parentGrid is nullptr.
		 * @exception	std::invalid_argument	If an HDF proxy is required to store numerical values but
		 * 										@p proxy is nullptr and no default HDF proxy is defined
		 * 										in the repository.
		 *
		 * @param 		  	iCellIndexRegridStart			   	I index of the first parent grid cell to
		 * 														be regridded.
		 * @param 		  	constantChildCellCountPerIInterval 	The constant count of cells per I
		 * 														interval in this (child) grid.
		 * @param 		  	constantParentCellCountPerIInterval	The constant count of cells per I
		 * 														interval in the parent grid.
		 * @param 		  	iIntervalCount					   	The count of intervals on I dimension.
		 * 														Intervals are portions of cells to regrid
		 * 														which does not overlap with each others.
		 * @param 		  	jCellIndexRegridStart			   	J index of the first parent grid cell to
		 * 														be regridded.
		 * @param 		  	constantChildCellCountPerJInterval 	The constant count of cells per J
		 * 														interval in this (child) grid.
		 * @param 		  	constantParentCellCountPerJInterval	The constant count of cells per J
		 * 														interval in the parent grid.
		 * @param 		  	jIntervalCount					   	The count of intervals on J dimension.
		 * 														Intervals are portions of cells to regrid
		 * 														which does not overlap with each others.
		 * @param 		  	kCellIndexRegridStart			   	K index of the first parent grid cell to
		 * 														be regridded.
		 * @param 		  	constantChildCellCountPerKInterval 	The constant count of cells per K
		 * 														interval in this (child) grid.
		 * @param 		  	constantParentCellCountPerKInterval	The constant count of cells per K
		 * 														interval in the parent grid.
		 * @param 		  	kIntervalCount					   	The count of intervals on K dimension.
		 * 														Intervals are portions of cells to regrid
		 * 														which does not overlap with each others.
		 * @param [in]	  	parentGrid						   	The parent grid which is regridded.
		 * @param [in,out]	proxy							   	(Optional) The HDF proxy where to store
		 * 														the numerical values. If nullptr
		 * 														(default), then the proxy will be the
		 * 														default proxy of the repository. This
		 * 														parameter is unused if no numerical value
		 * 														need to be store in an HDF proxy (pure
		 * 														XML).
		 * @param [in]	  	iChildCellWeights				   	(Optional) The weights that are
		 * 														proportional to the relative I sizes of
		 * 														child cells within each I interval. This
		 * 														is useful to set up child cells of
		 * 														different I sizes inside the intervals.
		 * 														The weights need not to be normalized.
		 * 														The count of double values must be equal
		 * 														to the count of all child cells on I
		 * 														dimension
		 * 														(<tt>constantChildCellCountPerIInterval *
		 * 														iIntervalCount</tt>). Default value is
		 * 														nullptr.
		 * @param [in]	  	jChildCellWeights				   	(Optional) The weights that are
		 * 														proportional to the relative J sizes of
		 * 														child cells within each J interval. This
		 * 														is useful to set up child cells of
		 * 														different J sizes inside the intervals.
		 * 														The weights need not to be normalized.
		 * 														The count of double values must be equal
		 * 														to the count of all child cells on J
		 * 														dimension
		 * 														(<tt>constantChildCellCountPerJInterval
		 * 														* jIntervalCount</tt>).
		 * @param [in]	  	kChildCellWeights				   	(Optional) The weights that are
		 * 														proportional to the relative K sizes of
		 * 														child cells within each K interval. This
		 * 														is useful to set up child cells of
		 * 														different K sizes inside the intervals.
		 * 														The weights need not to be normalized.
		 * 														The count of double values must be equal
		 * 														to the count of all child cells on K
		 * 														dimension
		 * 														(<tt>constantChildCellCountPerKInterval
		 * 														* kIntervalCount</tt>).
		 */
		DLL_IMPORT_OR_EXPORT void setParentWindow(
			unsigned int iCellIndexRegridStart, unsigned int constantChildCellCountPerIInterval, unsigned int constantParentCellCountPerIInterval, unsigned int iIntervalCount,
			unsigned int jCellIndexRegridStart, unsigned int constantChildCellCountPerJInterval, unsigned int constantParentCellCountPerJInterval, unsigned int jIntervalCount,
			unsigned int kCellIndexRegridStart, unsigned int constantChildCellCountPerKInterval, unsigned int constantParentCellCountPerKInterval, unsigned int kIntervalCount,
			RESQML2_0_1_NS::AbstractIjkGridRepresentation* parentGrid, COMMON_NS::AbstractHdfProxy * proxy = nullptr, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);

		/**
		 * Indicates that this grid takes place into another IJK parent grid. This method assumes that
		 * there is only one regrid interval per dimension.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p iChildCellCount is 0 or @p iParentCellCount is 0 or
		 * 										@p jChildCellCount is 0 or @p jParentCellCount is 0 or @p
		 * 										kChildCellCount is 0 or @p kParentCellCount is 0 or @p
		 * 										parentGrid is nullptr.
		 * @exception	std::invalid_argument	If an HDF proxy is required to store numerical values but
		 * 										@p proxy is nullptr and no default HDF proxy is defined
		 * 										in the repository.
		 *
		 * @param 		  	iCellIndexRegridStart	I index of the first parent grid cell to
		 * 														be regridded.
		 * @param 		  	iChildCellCount		 	The count of cells for the unique I interval in this
		 * 											(child) grid.
		 * @param 		  	iParentCellCount	 	The count of cells for the unique I interval in the
		 * 											parent grid.
		 * @param 		  	jCellIndexRegridStart	J index of the first parent grid cell to
		 * 														be regridded.
		 * @param 		  	jChildCellCount		 	The count of cells for the unique J interval in this
		 * 											(child) grid.
		 * @param 		  	jParentCellCount	 	The count of cells for the unique J interval in the
		 * 											parent grid.
		 * @param 		  	kCellIndexRegridStart	K index of the first parent grid cell to
		 * 														be regridded.
		 * @param 		  	kChildCellCount		 	The count of cells for the unique K interval in this
		 * 											(child) grid.
		 * @param 		  	kParentCellCount	 	The count of cells for the unique K interval in the
		 * 											parent grid.
		 * @param [in]	  	parentGrid			 	The parent grid which is regridded.
		 * @param [in,out]	proxy				 	(Optional) The HDF proxy where to store the numerical
		 * 											values. If nullptr (default), then the proxy will be
		 * 											the default proxy of the repository. This parameter
		 * 											is unused if no numerical value need to be store in
		 * 											an HDF proxy (pure XML).
		 * @param [in]	  	iChildCellWeights	 	(Optional) The weights that are proportional to the
		 * 											relative I sizes of child cells. This is useful to
		 * 											set up child cells of different I sizes inside the
		 * 											unique interval. The weights need not to be
		 * 											normalized. The count of double values must be equal
		 * 											to @p iChildCellCount. Default value is nullptr.
		 * @param [in]	  	jChildCellWeights	 	(Optional) The weights that are proportional to the
		 * 											relative J sizes of child cells. This is useful to
		 * 											set up child cells of different J sizes inside the
		 * 											unique interval. The weights need not to be
		 * 											normalized. The count of double values must be equal
		 * 											to @p jChildCellCount. Default value is nullptr.
		 * @param [in]	  	kChildCellWeights	 	(Optional) The weights that are proportional to the
		 * 											relative K sizes of child cells. This is useful to
		 * 											set up child cells of different K sizes inside the
		 * 											unique interval. The weights need not to be
		 * 											normalized. The count of double values must be equal
		 * 											to @p kChildCellCount. Default value is nullptr.
		 */
		DLL_IMPORT_OR_EXPORT void setParentWindow(
			unsigned int iCellIndexRegridStart, unsigned int iChildCellCount, unsigned int iParentCellCount,
			unsigned int jCellIndexRegridStart, unsigned int jChildCellCount, unsigned int jParentCellCount,
			unsigned int kCellIndexRegridStart, unsigned int kChildCellCount, unsigned int kParentCellCount,
			RESQML2_0_1_NS::AbstractIjkGridRepresentation* parentGrid, COMMON_NS::AbstractHdfProxy * proxy = nullptr, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);

		/**
		 * When a parent windows has been defined, this method allows to force some parent cells to be
		 * noted as non regridded. It mainly allows non-rectangular local grids to be specified.
		 *
		 * @param [in,out]	cellIndices   	If non-null, the cell indices.
		 * @param 		  	cellIndexCount	Number of cell indexes.
		 */
		DLL_IMPORT_OR_EXPORT void setForcedNonRegridedParentCell(ULONG64 * cellIndices, const ULONG64 & cellIndexCount);

		/**
		 * Optional cell volume overlap information between the current grid (the child) and the parent
		 * grid. Use this data-object when the child grid has an explicitly defined geometry, and these
		 * relationships cannot be inferred from the regrid descriptions.
		 *
		 * @param 		  	parentChildCellPairCount	Number of parent child cell pairs.
		 * @param [in,out]	parentChildCellPair			If non-null, the parent child cell pair.
		 * @param 		  	volumeUom					(Optional) The volume uom.
		 * @param [in,out]	overlapVolumes				(Optional) If non-null, the overlap volumes.
		 */
		DLL_IMPORT_OR_EXPORT void setCellOverlap(const ULONG64 & parentChildCellPairCount, ULONG64 * parentChildCellPair,
			const gsoap_resqml2_0_1::eml20__VolumeUom & volumeUom = gsoap_resqml2_0_1::eml20__VolumeUom__m3, double * overlapVolumes = nullptr);

		/**
		 * Only run this method for an unstructured parent grid. Use regrid information for ijk parent
		 * grid or (regrid and columIndexCount) for strict column layer parent grid.
		 *
		 * @returns	The parent cell index count.
		 */
		DLL_IMPORT_OR_EXPORT LONG64 getParentCellIndexCount() const;

		/**
		 * Only run this method for an unstructured parent grid.
		 *
		 * @param [in,out]	parentCellIndices	This array must have been preallocated with a size of
		 * 										getParentCellIndexCount().
		 */
		DLL_IMPORT_OR_EXPORT void getParentCellIndices(ULONG64 * parentCellIndices) const;

		/**
		 * Only run this method for a strict column layer parent grid.
		 *
		 * @returns	The parent column index count.
		 */
		DLL_IMPORT_OR_EXPORT LONG64 getParentColumnIndexCount() const;

		/**
		 * Only run this method for an unstructured parent grid.
		 *
		 * @param [in,out]	parentColumnIndices	This array must have been preallocated with a size of
		 * 										getParentCellIndexCount().
		 */
		DLL_IMPORT_OR_EXPORT void getParentColumnIndices(ULONG64 * parentColumnIndices) const;

		/**
		 * Only run this method for an ijk parent grid or a strict column layer parent grid. Get the
		 * first cell index of the regrid on a particular dimension.
		 *
		 * @param 	dimension	It must be either 'i', 'j' ou 'k' (upper or lower case) for an ijk parent
		 * 						grid. 'k' for a strict column layer parent grid.
		 *
		 * @returns	The regrid start index on parent grid.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getRegridStartIndexOnParentGrid(const char & dimension) const;

		/**
		 * Only run this method for an ijk parent grid or a strict column layer parent grid. Get the
		 * count of intervals which are regridded on a particular dimension
		 *
		 * @param 	dimension	It must be either 'i', 'j' ou 'k' (upper or lower case) for an ijk parent
		 * 						grid. 'k' for a strict column layer parent grid.
		 *
		 * @returns	The regrid interval count.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getRegridIntervalCount(const char & dimension) const;

		/**
		 * Check if the cell count per interval is constant against a particular dimension. Only run
		 * this method for an ijk parent grid or a strict column layer parent grid.
		 *
		 * @param 	dimension			  	It must be either 'i', 'j' ou 'k' (upper or lower case) for
		 * 									an ijk parent grid. 'k' for a strict column layer parent grid.
		 * @param 	childVsParentCellCount	If true check if the child cell count per interval is
		 * 									constant. If false check if the parent cell count per
		 * 									interval is constant.
		 *
		 * @returns	True if regrid cell count per interval constant, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isRegridCellCountPerIntervalConstant(const char & dimension, const bool & childVsParentCellCount) const;

		/**
		 * Get the constant cell count per interval Only run this method for an ijk parent grid or a
		 * strict column layer parent grid.
		 *
		 * @param 	dimension			  	It must be either 'i', 'j' ou 'k' (upper or lower case) for
		 * 									an ijk parent grid. 'k' for a strict column layer parent grid.
		 * @param 	childVsParentCellCount	If true return the child cell count per interval. If false
		 * 									return the parent cell count per interval.
		 *
		 * @returns	The regrid constant cell count per interval.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getRegridConstantCellCountPerInterval(const char & dimension, const bool & childVsParentCellCount) const;

		/**
		 * Only run this method for an ijk parent grid or a strict column layer parent grid.
		 *
		 * @param 		  	dimension				 	It must be either 'i', 'j' ou 'k' (upper or lower
		 * 												case) for an ijk parent grid. 'k' for a strict
		 * 												column layer parent grid.
		 * @param [in,out]	childCellCountPerInterval	This array must have been preallocated with a
		 * 												size of getRegridIntervalCount().
		 * @param 		  	childVsParentCellCount   	If true return the child cell count per interval.
		 * 												If false return the parent cell count per
		 * 												interval.
		 */
		DLL_IMPORT_OR_EXPORT void getRegridCellCountPerInterval(const char & dimension, ULONG64 * childCellCountPerInterval, const bool & childVsParentCellCount) const;

		/**
		 * Only run this method for an ijk parent grid or a strict column layer parent grid.
		 *
		 * @param 	dimension	It must be either 'i', 'j' ou 'k' (upper or lower case) for an ijk parent
		 * 						grid. 'k' for a strict column layer parent grid.
		 *
		 * @returns	True if regrid child cell weights, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasRegridChildCellWeights(const char & dimension) const;

		/**
		 * Only run this method for an ijk parent grid or a strict column layer parent grid.
		 *
		 * @param 		  	dimension			It must be either 'i', 'j' ou 'k' (upper or lower case)
		 * 										for an ijk parent grid. 'k' for a strict column layer parent
		 * 										grid.
		 * @param [in,out]	childCellWeights	This array must have been preallocated with a size equal
		 * 										to the sum of ChildCellCountPerInterval.
		 */
		DLL_IMPORT_OR_EXPORT void getRegridChildCellWeights(const char & dimension, double * childCellWeights) const;

		/**
		 * When a parent windows has been defined, this method checks if some parent cells have been
		 * noted to be forced not to be regridded. It mainly occurs in case of non-rectangular local
		 * grids.
		 *
		 * @returns	True if forced non regridded parent cell, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasForcedNonRegridedParentCell() const;

		//************************************************************
		//**************** LINK WITH STRATIGRAPHY ********************
		//************************************************************

		/**
		 * Set the stratigraphic organization interpretation which is associated to this grid
		 * representation.
		 *
		 * @param [in,out]	stratiUnitIndices	Index of the stratigraphic unit of a given stratigraphic
		 * 										column for each cell. Array length is the number of cells
		 * 										in the grid or the blocked well.
		 * @param 		  	nullValue		 	The value which is used to tell the association between a
		 * 										cell and strati unit is unavailable.
		 * @param [in,out]	stratiOrgInterp  	The stratigraphic organization interpretation which is
		 * 										associated to this grid representation.
		 */
		DLL_IMPORT_OR_EXPORT void setCellAssociationWithStratigraphicOrganizationInterpretation(ULONG64 * stratiUnitIndices, const ULONG64 & nullValue, RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation* stratiOrgInterp);

		/**
		 * Gets stratigraphic organization interpretation
		 *
		 * @returns	nullptr if no stratigraphic organization interpretation is associated to this grid
		 * 			representation. Otherwise return the associated stratigraphic organization
		 * 			interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation* getStratigraphicOrganizationInterpretation() const;

		/**
		 * Gets stratigraphic organization interpretation dor
		 *
		 * @returns	null pointer if no stratigraphic organization interpretation is associated to this
		 * 			grid representation. Otherwise return the data objet reference of the associated
		 * 			stratigraphic organization interpretation.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::eml20__DataObjectReference const * getStratigraphicOrganizationInterpretationDor() const;

		/**
		 * Gets stratigraphic organization interpretation uuid
		 *
		 * @returns	empty string if no stratigraphic organization interpretation is associated to this
		 * 			grid representation. Otherwise return the uuid of the associated stratigraphic
		 * 			organization interpretation.
		 */
		DLL_IMPORT_OR_EXPORT std::string getStratigraphicOrganizationInterpretationUuid() const;

		/**
		 * Gets stratigraphic organization interpretation title
		 *
		 * @returns	empty string if no stratigraphic organization interpretation is associated to this
		 * 			grid representation. Otherwise return the title of the associated stratigraphic
		 * 			organization interpretation.
		 */
		DLL_IMPORT_OR_EXPORT std::string getStratigraphicOrganizationInterpretationTitle() const;

		/**
		 * Query if this object has cell stratigraphic unit indices
		 *
		 * @returns	true if this grid representation has got some association between stratigraphic unit
		 * 			indices and cell.
		 */
		DLL_IMPORT_OR_EXPORT bool hasCellStratigraphicUnitIndices() const;

		/**
		 * Get the stratigraphic unit indices (regarding the associated stratigraphic organization
		 * interpretation) of each cell of this grid representation.
		 *
		 * @param [in,out]	stratiUnitIndices	This array must be allocated with a count equal to
		 * 										getCellCount(). It will be filled in with the
		 * 										stratigraphic unit indices ordered as grid cells are
		 * 										ordered.
		 *
		 * @returns	The null value is returned. The null value is used to tell the association between a
		 * 			cell and strati unit is unavailable.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getCellStratigraphicUnitIndices(ULONG64 * stratiUnitIndices);

		//************************************************************
		//**************** LINK WITH ROCKFLUID ********************
		//************************************************************

		/**
		 * Set the rock fluid organization interpretation which is associated to this grid
		 * representation.
		 *
		 * @param [in,out]	rockFluidUnitIndices	Index of the rock fluid unit of a given rock fluid
		 * 											column for each cell. Array length is the number of cells
		 * 											in the grid or the blocked well.
		 * @param 		  	nullValue				The value which is used to tell the association
		 * 											between a cell and rockFluid unit is unavailable.
		 * @param [in,out]	rockFluidOrgInterp  	The rock fluid organization interpretation which is
		 * 											associated to this grid representation.
		 */
		DLL_IMPORT_OR_EXPORT void setCellAssociationWithRockFluidOrganizationInterpretation(ULONG64 * rockFluidUnitIndices, const ULONG64 & nullValue, RESQML2_0_1_NS::RockFluidOrganizationInterpretation* rockFluidOrgInterp);

		/**
		 * Gets rock fluid organization interpretation
		 *
		 * @returns	nullptr if no rock fluid organization interpretation is associated to this grid
		 * 			representation. Otherwise return the associated rock fluid organization
		 * 			interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::RockFluidOrganizationInterpretation* getRockFluidOrganizationInterpretation() const;

		/**
		 * Gets rock fluid organization interpretation dor
		 *
		 * @returns	null pointer if no rock fluid organization interpretation is associated to this grid
		 * 			representation. Otherwise return the data objet reference of the associated rock
		 * 			fluid organization interpretation.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::eml20__DataObjectReference const * getRockFluidOrganizationInterpretationDor() const;

		/**
		 * Gets rock fluid organization interpretation uuid
		 *
		 * @returns	empty string if no rock fluid organization interpretation is associated to this grid
		 * 			representation. Otherwise return the uuid of the associated rock fluid organization
		 * 			interpretation.
		 */
		DLL_IMPORT_OR_EXPORT std::string getRockFluidOrganizationInterpretationUuid() const;

		/**
		 * Gets rock fluid organization interpretation title
		 *
		 * @returns	empty string if no rock fluid organization interpretation is associated to this grid
		 * 			representation. Otherwise return the title of the associated rock fluid organization
		 * 			interpretation.
		 */
		DLL_IMPORT_OR_EXPORT std::string getRockFluidOrganizationInterpretationTitle() const;

		/**
		 * Query if this object has cell fluid phase unit indices
		 *
		 * @returns	true if this grid representation has got some association between rock fluid unit
		 * 			indices and cell.
		 */
		DLL_IMPORT_OR_EXPORT bool hasCellFluidPhaseUnitIndices() const;

		/**
		 * Get the rock fluid unit indices (regarding the associated rock fluid organization
		 * interpretation) of each cell of this grid representation.
		 *
		 * @param [in,out]	rockfluidUnitIndices	This array must be allocated with a count equal to
		 * 											getCellCount(). It will be filled in with the rock fluid
		 * 											unit indices ordered as grid cells are ordered.
		 *
		 * @returns	The null value is returned. The null value is used to tell the association between a
		 * 			cell and rock fluid unit is unavailable.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getCellFluidPhaseUnitIndices(ULONG64 * rockfluidUnitIndices);


		//************************************************************
		//********************** TRUNCATION **************************
		//************************************************************

		/**
		 * Indicates wether this grid instance contains truncated pillars or not.
		 *
		 * @returns	True if truncated, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isTruncated() const;

		/**
		 * Get the truncation face count. It does not include face of truncated cells whch are not
		 * truncated.
		 *
		 * @returns	The truncated face count.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getTruncatedFaceCount() const;

		/**
		 * Get all the node indices of the truncated faces.
		 *
		 * @param [in,out]	nodeIndices	It must be pre allocated with the last value returned by
		 * 								getCumulativeNodeCountOfTruncatedFaces().
		 */
		DLL_IMPORT_OR_EXPORT void getNodeIndicesOfTruncatedFaces(ULONG64 * nodeIndices) const;

		/**
		 * Get the cumulative node count per truncated face. First value is the count of nodes in the
		 * first face. Second value is the count of nodes in the first and in the second face. Third
		 * value is the count of nodes in the first and in the second and in the third face. Etc...
		 * Count of this array is equal to getTruncatedFaceCount()
		 * A single node count should be at least 3.
		 *
		 * @param [in,out]	nodeCountPerFace	It must be pre allocated with getTruncatedFaceCount() ==
		 * 										last value of
		 * 										getCumulativeTruncatedFaceCountPerTruncatedCell()
		 */
		DLL_IMPORT_OR_EXPORT void getCumulativeNodeCountPerTruncatedFace(ULONG64 * nodeCountPerFace) const;

		/**
		 * Less efficient than getCumulativeNodeCountPerTruncatedFace. Get the node count per truncated
		 * face. First value is the count of nodes in the first face. Second value is the count of nodes
		 * in the second face. etc...
		 *
		 * @param [in,out]	nodeCountPerFace	It must be pre allocated with getTruncatedFaceCount() ==
		 * 										last value of
		 * 										getCumulativeTruncatedFaceCountPerTruncatedCell()
		 */
		DLL_IMPORT_OR_EXPORT void getNodeCountPerTruncatedFace(ULONG64 * nodeCountPerFace) const;

		/**
		 * Get the truncated cell count.
		 *
		 * @returns	The truncated cell count.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getTruncatedCellCount() const;

		/**
		 * Get the the indices of the truncated cells in the non truncated grid.
		 *
		 * @param [in,out]	cellIndices	If non-null, the cell indices.
		 */
		DLL_IMPORT_OR_EXPORT void getTruncatedCellIndices(ULONG64* cellIndices) const;

		/**
		 * Get all the truncated face indices of all the truncated cells. It does not get the non
		 * truncated face indices of a truncated cell. Please use
		 * getNonTruncatedFaceIndicesOfTruncatedCells(ULONG64 * faceIndices) in addition to this method
		 * in order to get the full list of face indices for a truncated cell.
		 *
		 * @param [in,out]	faceIndices	It must be pre allocated with the last value returned by
		 * 								getCumulativeTruncatedFaceCountPerTruncatedCell()
		 */
		DLL_IMPORT_OR_EXPORT void getTruncatedFaceIndicesOfTruncatedCells(ULONG64 * faceIndices) const;

		/**
		 * Get the cumulative truncated face count per truncated cell. It does not take into account the
		 * non truncated face indices of a truncated cell. First value is the count of faces in the
		 * first cell. Second value is the count of faces in the first and in the second cell. Third
		 * value is the count of faces in the first and in the second and in the third cell. Etc...
		 * Count of this array is equal to getCellCount()
		 * A single face count should be at least 4.
		 *
		 * @param [in,out]	cumulativeFaceCountPerCell	It must be pre allocated with
		 * 												getTruncatedCellCount()
		 */
		DLL_IMPORT_OR_EXPORT void getCumulativeTruncatedFaceCountPerTruncatedCell(ULONG64 * cumulativeFaceCountPerCell) const;

		/**
		 * Less efficient than getCumulativeTruncatedFaceCountPerTruncatedCell. Get the face count per
		 * cell. First value is the count of faces in the first cell. Second value is the count of faces
		 * in the second cell. etc...
		 *
		 * @param [in,out]	faceCountPerCell	It must be pre allocated with getTruncatedCellCount()
		 */
		DLL_IMPORT_OR_EXPORT void getTruncatedFaceCountPerTruncatedCell(ULONG64 * faceCountPerCell) const;

		/**
		 * Get all the truncated face indices of all the truncated cells. It does not get the non
		 * truncated face indices of a truncated cell. Please use
		 * getNonTruncatedFaceIndicesOfTruncatedCells(ULONG64 * faceIndices) in addition to this method
		 * in order to get the full list of face indices for a truncated cell.
		 *
		 * @param [in,out]	faceIndices	It must be pre allocated with the last value returned by
		 * 								getCumulativeTruncatedFaceCountPerTruncatedCell()
		 */
		DLL_IMPORT_OR_EXPORT void getNonTruncatedFaceIndicesOfTruncatedCells(ULONG64 * faceIndices) const;

		/**
		 * Get the cumulative truncated face count per truncated cell. It does not take into account the
		 * non truncated face indices of a truncated cell. First value is the count of faces in the
		 * first cell. Second value is the count of faces in the first and in the second cell. Third
		 * value is the count of faces in the first and in the second and in the third cell. Etc...
		 * Count of this array is equal to getCellCount()
		 * A single face count should be at least 4.
		 *
		 * @param [in,out]	cumulativeFaceCountPerCell	It must be pre allocated with
		 * 												getTruncatedCellCount()
		 */
		DLL_IMPORT_OR_EXPORT void getCumulativeNonTruncatedFaceCountPerTruncatedCell(ULONG64 * cumulativeFaceCountPerCell) const;

		/**
		 * Less efficient than getCumulativeTruncatedFaceCountPerTruncatedCell. Get the face count per
		 * cell. First value is the count of faces in the first cell. Second value is the count of faces
		 * in the second cell. etc...
		 *
		 * @param [in,out]	faceCountPerCell	It must be pre allocated with getTruncatedCellCount()
		 */
		DLL_IMPORT_OR_EXPORT void getNonTruncatedFaceCountPerTruncatedCell(ULONG64 * faceCountPerCell) const;

		/**
		 * Retrieves orientation i.e. if each truncated face is right handed or not
		 *
		 * @param [in,out]	cellFaceIsRightHanded	It must be pre allocated with getTruncatedFaceCount()
		 */
		DLL_IMPORT_OR_EXPORT void getTruncatedFaceIsRightHanded(unsigned char* cellFaceIsRightHanded) const;

		/**
		 * Gets the XML tag
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

	protected:

		/** Loads target relationships */
		void loadTargetRelationships();

		/** True to with truncated pillars */
		bool withTruncatedPillars;
	};
}
