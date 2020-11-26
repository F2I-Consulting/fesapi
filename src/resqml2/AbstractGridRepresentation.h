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

#include "AbstractRepresentation.h"

namespace RESQML2_NS
{
	/** @brief	Proxy class for an abstract grid representation. */
	class AbstractGridRepresentation : public AbstractRepresentation
	{
	private:

		/**
		* @param	 forceConstantCellCountPerInterval	If true, will assume that the child and parent cell count per interval are constant. Then it will use constant xml array instead of hdf5 array for storage.
		*												The method will consequently only consider the first cell count per interval value in childCellCountPerInterval and parentCellCountPerInterval as the constant ones.
		**/
		gsoap_resqml2_0_1::resqml20__Regrid* createRegrid2_0_1(unsigned int indexRegridStart, unsigned int * childCellCountPerInterval, unsigned int * parentCellCountPerInterval, unsigned int intervalCount, double * childCellWeights,
			const std::string & dimension, EML2_NS::AbstractHdfProxy * proxy, bool forceConstantCellCountPerInterval = false);
		gsoap_eml2_3::resqml22__Regrid* createRegrid2_2(unsigned int indexRegridStart, unsigned int * childCellCountPerInterval, unsigned int * parentCellCountPerInterval, unsigned int intervalCount, double * childCellWeights,
			const std::string & dimension, EML2_NS::AbstractHdfProxy * proxy, bool forceConstantCellCountPerInterval = false);

		/*
		* @param	dimension					It must be either 'i', 'j' ou 'k' (upper or lower case) for an ijk parent grid. 'k' for a strict column layer parent grid.
		* @param	childVsParentCellCount		If true return the child cell count per interval. If false return the parent cell count per interval.
		*/
		gsoap_resqml2_0_1::resqml20__AbstractIntegerArray* getCellCountPerInterval2_0_1(char dimension, bool childVsParentCellCount) const;
		gsoap_eml2_3::eml23__AbstractIntegerArray* getCellCountPerInterval2_2(char dimension, bool childVsParentCellCount) const;

		/**
		 * Gets the parent window 2 0 1
		 *
		 * @returns	Null if it fails, else the parent window 2 0 1.
		 */
		gsoap_resqml2_0_1::resqml20__AbstractParentWindow* getParentWindow2_0_1() const;
		gsoap_eml2_3::resqml22__AbstractParentWindow* getParentWindow2_2() const;

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
		AbstractGridRepresentation(gsoap_eml2_3::resqml22__AbstractGridRepresentation* fromGsoap, bool withTruncatedPillars) : AbstractRepresentation(fromGsoap), withTruncatedPillars(withTruncatedPillars) {}

	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~AbstractGridRepresentation() = default;

		/**
		 * Gets the count of (volumetric) cells in the grid.
		 *
		 * @exception	std::range_error	If the cell count is strictly greater than unsigned int max.
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The cell count.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getCellCount() const = 0;

		//************************************************************
		//****************** GRID CONNECTION SET *********************
		//************************************************************

		/**
		 * Gets the vector of all grid connection set representations associated to this grid instance.
		 *
		 * @returns	A vector of pointers to all grid connection set representations associated to this grid instance.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<class GridConnectionSetRepresentation*> getGridConnectionSetRepresentationSet() const;

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
		DLL_IMPORT_OR_EXPORT class GridConnectionSetRepresentation * getGridConnectionSetRepresentation(unsigned int index) const; // It is mainly used in SWIG context for parsing the vector from a non C++ language.


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
		 * @returns	Empty data object reference if this grid is not a child grid (not a LGR), otherwise the data object
		 * 			reference of the parent grid.
		 */
		COMMON_NS::DataObjectReference getParentGridDor() const;

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
		 * @exception	std::out_of_range	If <tt>index >=</tt> getChildGridCount().
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
		 * 									regridded.
		 * @param [in]	  	parentGrid	  	The parent grid which is regridded.
		 * @param [in,out]	proxy		  	(Optional) The HDF proxy where to store the numerical values.
		 * 									If nullptr (default), then the proxy will be the default
		 * 									proxy of the repository. This parameter is unused if @p
		 * 									cellIndexCount is 1 since no numerical value need to be store
		 * 									in an HDF proxy (pure XML).
		 */
		DLL_IMPORT_OR_EXPORT void setParentWindow(uint64_t* cellIndices, uint64_t cellIndexCount, class UnstructuredGridRepresentation* parentGrid, EML2_NS::AbstractHdfProxy* proxy = nullptr);

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
			EML2_NS::AbstractHdfProxy * proxy = nullptr, double * childCellWeights = nullptr);

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
			class AbstractIjkGridRepresentation* parentGrid, EML2_NS::AbstractHdfProxy * proxy = nullptr, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);

		/**
		 * @brief	Indicates that this grid takes place into another IJK parent grid. This method
		 * 			assumes that the count of cells per regrid interval is constant in both child and
		 * 			parent grids.
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
		 * 														(<tt>constantChildCellCountPerJInterval</tt>
		 * 														<tt>* jIntervalCount</tt>).
		 * @param [in]	  	kChildCellWeights				   	(Optional) The weights that are
		 * 														proportional to the relative K sizes of
		 * 														child cells within each K interval. This
		 * 														is useful to set up child cells of
		 * 														different K sizes inside the intervals.
		 * 														The weights need not to be normalized.
		 * 														The count of double values must be equal
		 * 														to the count of all child cells on K
		 * 														dimension
		 * 														(<tt>constantChildCellCountPerKInterval</tt>
		 * 														<tt>* kIntervalCount</tt>).
		 */
		DLL_IMPORT_OR_EXPORT void setParentWindow(
			unsigned int iCellIndexRegridStart, unsigned int constantChildCellCountPerIInterval, unsigned int constantParentCellCountPerIInterval, unsigned int iIntervalCount,
			unsigned int jCellIndexRegridStart, unsigned int constantChildCellCountPerJInterval, unsigned int constantParentCellCountPerJInterval, unsigned int jIntervalCount,
			unsigned int kCellIndexRegridStart, unsigned int constantChildCellCountPerKInterval, unsigned int constantParentCellCountPerKInterval, unsigned int kIntervalCount,
			class AbstractIjkGridRepresentation* parentGrid, EML2_NS::AbstractHdfProxy * proxy = nullptr, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);

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
		 * 											be regridded.
		 * @param 		  	iChildCellCount		 	The count of cells for the unique I interval in this
		 * 											(child) grid.
		 * @param 		  	iParentCellCount	 	The count of cells for the unique I interval in the
		 * 											parent grid.
		 * @param 		  	jCellIndexRegridStart	J index of the first parent grid cell to
		 * 											be regridded.
		 * @param 		  	jChildCellCount		 	The count of cells for the unique J interval in this
		 * 											(child) grid.
		 * @param 		  	jParentCellCount	 	The count of cells for the unique J interval in the
		 * 											parent grid.
		 * @param 		  	kCellIndexRegridStart	K index of the first parent grid cell to
		 * 											be regridded.
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
			class AbstractIjkGridRepresentation* parentGrid, EML2_NS::AbstractHdfProxy * proxy = nullptr, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);

		/**
		 * When a parent windows has been defined, this method allows to force some parent cells to be
		 * noted as non regridded. It mainly allows non-rectangular local grids to be specified.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is neither an IJK nor a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If @p cellIndices is nullptr or @p cellIndexCount is 0.
		 * @exception	std::invalid_argument	If an HDF proxy is required and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param [in]	cellIndices   	The indices of the parent cells to be noted as non regridded. The
		 * 								size is @p cellIndexCount.
		 * @param 	  	cellIndexCount	Number of cells to be noted as non regridded.
		 */
		DLL_IMPORT_OR_EXPORT void setForcedNonRegridedParentCell(uint64_t* cellIndices, uint64_t cellIndexCount);

		/**
		 * Set optional cell overlap information between the current grid (the child) and the parent
		 * grid. Use this data-object when the child grid has an explicitly defined geometry, and these
		 * relationships cannot be inferred from the regrid descriptions. An overlap volume information
		 * can be associated to each overlapping (parent cell, child cell) pair.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined.
		 * @exception	std::invalid_argument	If @p parentChildCellPairCount is 0 or
		 * 										@p parentChildCellPair is nullptr.
		 * @exception	std::invalid_argument	If no default HDF proxy is defined in the repository.
		 *
		 * @param 	  	parentChildCellPairCount	Number of (parent cell, child cell) pairs that
		 * 											overlap.
		 * @param [in]	parentChildCellPair			The (parent cell index, child cell index) pair for
		 * 											each overlap. The size is <tt>2 *
		 * 											parentChildCellPairCount</tt>.
		 * 											<tt>parentChildCellPair[2i]</tt> are parent cell indices
		 * 											and <tt>parentChildCellPair[2i+1]</tt> are child cell
		 * 											indices.
		 * @param 	  	volumeUom					The volume unit of measure.
		 * @param [in]	overlapVolumes				(Optional) The overlapping volume for each (parent
		 * 											cell, child cell) that overlaps. Size is @p
		 * 											parentChildCellPairCount. Default value is nullptr.
		 */
		DLL_IMPORT_OR_EXPORT void setCellOverlap(uint64_t parentChildCellPairCount, uint64_t* parentChildCellPair,
			const std::string& volumeUom, double* overlapVolumes = nullptr);

		/**
		 * Gets the count of parent grid cells which are regridded. Please only run this method for an
		 * unstructured parent grid. Please use regrid information for IJK parent grid or (regrid information
		 * and columIndexCount) for strict column layer parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is not an unstructured parent window.
		 * @exception std::invalid_argument		If the list of regridded cells is not stored in an HDF5 file.
		 *
		 * @returns	The count of parent grid cells which are regridded.
		 */
		DLL_IMPORT_OR_EXPORT int64_t getParentCellIndexCount() const;

		/**
		 * Gets the indices of the parent grid cells which are regridded. Please only run this method
		 * for an unstructured parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is not an unstructured parent window.
		 * @exception	std::invalid_argument	If the list of regridded cells is not stored in an HDF5
		 * 										file.
		 *
		 * @param [out]	parentCellIndices	An array for receiving the regridded cells indices. This
		 * 									array must have been preallocated with a size of 
		 * 									getParentCellIndexCount().
		 */
		DLL_IMPORT_OR_EXPORT void getParentCellIndices(uint64_t * parentCellIndices) const;

		/**
		 * Gets the count of parent grid columns which are regridded. Please only run this method for a
		 * strict column layer parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is not a column layer parent window.
		 * @exception	std::invalid_argument	If the list of regridded cells is not stored in an HDF5
		 * 										file.
		 *
		 * @returns	The count of parent grid columns which are regridded.
		 */
		DLL_IMPORT_OR_EXPORT int64_t getParentColumnIndexCount() const;

		/**
		 * Gets the indices of the parent grid columns which are regridded. Please only run this method
		 * for a strict column layer parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is not a column layer parent window.
		 * @exception	std::invalid_argument	If the list of regridded cells is not stored in an HDF5
		 * 										file.
		 *
		 * @param [out]	parentColumnIndices	An array for collecting the regridded column indices. This
		 * 									array must have been preallocated with a size of
		 * 										getParentColumnIndexCount().
		 */
		DLL_IMPORT_OR_EXPORT void getParentColumnIndices(uint64_t * parentColumnIndices) const;

		/**
		 * Get the I, J or K index of the first parent grid cell to be regridded. Please only run this
		 * method for an IJK parent grid or a strict column layer parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is neither an IJK nor a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If @p dimension differs from 'i', 'j' or 'k' (upper or
		 * 										lower case) for an IJK parent window or if it differs
		 * 										from 'k' (upper or lower case) for a column layer parent
		 * 										window.
		 *
		 * @param 	dimension	The dimension of the index we look for. It must be either 'i', 'j' or 'k'
		 * 						(upper or lower case) for an IJK parent grid or 'k' for a strict column
		 * 						layer parent grid.
		 *
		 * @returns	The regrid start index on the parent grid in dimension @p dimension.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getRegridStartIndexOnParentGrid(char dimension) const;

		/**
		 * Gets the count of intervals which are regridded on a particular dimension. Intervals are
		 * portions of cells to regrid which does not overlap with each others. Please only run this
		 * method for an IJK parent grid or a strict column layer parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is neither an IJK nor a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If @p dimension differs from 'i', 'j' or 'k' (upper or
		 * 										lower case) for an IJK parent window or if it differs
		 * 										from 'k' (upper or lower case) for a column layer parent
		 * 										window.
		 *
		 * @param 	dimension	The dimension of the interval count we look for. It must be either 'i',
		 * 						'j' or 'k' (upper or lower case) for an IJK parent grid or 'k' for a
		 * 						strict column layer parent grid.
		 *
		 * @returns	The regrid interval count in dimension @p dimension.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getRegridIntervalCount(char dimension) const;

		/**
		 * Checks if the cell count per interval (in the child grid or in the parent grid) is constant
		 * against a particular dimension. Intervals are portions of cells to regrid which does not
		 * overlap with each others. Please only run this method for an IJK parent grid or a strict
		 * column layer parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is neither an IJK nor a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If @p dimension differs from 'i', 'j' or 'k' (upper or
		 * 										lower case) for an IJK parent window or if it differs
		 * 										from 'k' (upper or lower case) for a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If there exists no regrid interval in dimension @p
		 * 										dimension.
		 *
		 * @param 	dimension			  	The dimension of the interval we look for. It must be either
		 * 									'i', 'j' ou 'k' (upper or lower case) for an IJK parent grid
		 * 									or 'k' for a strict column layer parent grid.
		 * @param 	childVsParentCellCount	If true, checks if the child cell count per interval is
		 * 									constant. If false, checks if the parent cell count per
		 * 									interval is constant.
		 *
		 * @returns	True if the regrid cell count per interval is constant in dimension @p dimension,
		 * 			false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isRegridCellCountPerIntervalConstant(char dimension, bool childVsParentCellCount) const;

		/**
		 * Gets the constant cell count per interval (in the child grid or in the parent grid) against a
		 * particular dimension. Intervals are portions of cells to regrid which does not overlap with
		 * each others. Please only run this method for an IJK parent grid or a strict column layer
		 * parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the cell count per interval in dimension @p dimension
		 * 										is neither an integer constant array nor a HDF5 integer
		 * 										array.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is neither an IJK nor a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If @p dimension differs from 'i', 'j' or 'k' (upper or
		 * 										lower case) for an IJK parent window or if it differs
		 * 										from 'k' (upper or lower case) for a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If there exists no regrid interval in dimension @p
		 * 										dimension.
		 *
		 * @param 	dimension			  	The dimension of the interval we look for. It must be either
		 * 									'i', 'j' ou 'k' (upper or lower case) for an IJK parent grid
		 * 									or 'k' for a strict column layer parent grid.
		 * @param 	childVsParentCellCount	If true, gets the constant child cell count per interval. If
		 * 									false, gets the constant parent cell count per interval.
		 *
		 * @returns	The regrid constant cell count per interval in dimension @p dimension.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getRegridConstantCellCountPerInterval(char dimension, bool childVsParentCellCount) const;

		/**
		 * Gets the regrid cell count per interval (in the child grid or in the parent grid) against a
		 * particular dimension. Intervals are portions of cells to regrid which does not overlap with
		 * each others. Please only run this method for an IJK parent grid or a strict column layer
		 * parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the cell count per interval in dimension @p dimension
		 * 										is neither an integer constant array nor a HDF5 integer
		 * 										array.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is neither an IJK nor a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If @p dimension differs from 'i', 'j' or 'k' (upper or
		 * 										lower case) for an IJK parent window or if it differs
		 * 										from 'k' (upper or lower case) for a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If there exists no regrid interval in dimension @p
		 * 										dimension.
		 *
		 * @param 	  	dimension				 	The dimension of the interval we look for. It must be
		 * 											either 'i', 'j' ou 'k' (upper or lower case) for an
		 * 											IJK parent grid or 'k' for a strict column layer
		 * 											parent grid.
		 * @param [in]	childCellCountPerInterval	An array to receive the regrid cell count per
		 * 											interval. It must have been preallocated with a size
		 * 											of getRegridIntervalCount().
		 * @param 	  	childVsParentCellCount   	If true, gets the child cell count per interval. If
		 * 											false, gets the parent cell count per interval.
		 */
		DLL_IMPORT_OR_EXPORT void getRegridCellCountPerInterval(char dimension, uint64_t* childCellCountPerInterval, bool childVsParentCellCount) const;

		/**
		 * Checks if regrid child cell weights have been defined for a given dimension. Please only run
		 * this method for an IJK parent grid or a strict column layer parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is neither an IJK nor a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If @p dimension differs from 'i', 'j' or 'k' (upper or
		 * 										lower case) for an IJK parent window or if it differs
		 * 										from 'k' (upper or lower case) for a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If there exists no regrid interval in dimension @p
		 * 										dimension.
		 *
		 * @param 	dimension	The dimension from which we look for regrid child cell weights. It must
		 * 						be either 'i', 'j' ou 'k' (upper or lower case) for an IJK parent grid or
		 * 						'k' for a strict column layer parent grid.
		 *
		 * @returns	True if regrid child cell weights have been defined in dimension @p dimension, false
		 * 			if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasRegridChildCellWeights(char dimension) const;

		/**
		 * Gets the regrid child cell weights for a given dimension. Please only run this method for an
		 * IJK parent grid or a strict column layer parent grid.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined of if the defined
		 * 										parent window is neither an IJK nor a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If @p dimension differs from 'i', 'j' or 'k' (upper or
		 * 										lower case) for an IJK parent window or if it differs
		 * 										from 'k' (upper or lower case) for a column layer parent
		 * 										window.
		 * @exception	std::invalid_argument	If there exists no regrid interval in dimension @p
		 * 										dimension.
		 * @exception	std::invalid_argument	If the regrid child cell weights in dimension @p
		 * 										dimension are not stored in an HDF5 file.
		 *
		 * @param 		  	dimension			The dimension from which we look for regrid child cell
		 * 										weights. It must be either 'i', 'j' ou 'k' (upper or lower
		 * 										case) for an IJK parent grid or 'k' for a strict column layer
		 * 										parent grid.
		 * @param [in,out]	childCellWeights	An array for receiving the regrid child cell weights. It
		 * 										must have been preallocated with a size equal to the sum of
		 * 										regrid child cell count per interval (using
		 * 										getRegridCellCountPerInterval()).
		 */
		DLL_IMPORT_OR_EXPORT void getRegridChildCellWeights(char dimension, double* childCellWeights) const;

		/**
		 * When a parent windows has been defined, this method checks if some parent cells have been
		 * noted to be forced not to be regridded. It mainly occurs in case of non-rectangular local
		 * grids.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no parent window is already defined.
		 *
		 * @returns	True if some parent cells have been forced not to be regridded, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasForcedNonRegridedParentCell() const;

		//************************************************************
		//**************** LINK WITH STRATIGRAPHY ********************
		//************************************************************

		/**
		 * Sets the stratigraphic organization interpretation which is associated to this grid
		 * representation.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no default HDF proxy is defined in the repository.
		 *
		 * @param [in]	stratiUnitIndices	Index of the stratigraphic unit of a given stratigraphic
		 * 									column for each cell. Array length is the number of cells in
		 * 									the grid or the blocked well.
		 * @param 	  	nullValue		 	The value which is used to tell the association between a
		 * 									cell and a stratigraphic unit is unavailable.
		 * @param [in]	stratiOrgInterp  	The stratigraphic organization interpretation which is
		 * 									associated to this grid representation.
		 */
		DLL_IMPORT_OR_EXPORT void setCellAssociationWithStratigraphicOrganizationInterpretation(uint64_t* stratiUnitIndices, uint64_t nullValue, class AbstractStratigraphicOrganizationInterpretation* stratiOrgInterp);
		
		/**
		 * Gets the stratigraphic organization interpretation which is associated to this grid.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @returns	nullptr if no stratigraphic organization interpretation is associated to this grid
		 * 			representation. Otherwise return the associated stratigraphic organization
		 * 			interpretation.
		 */
		DLL_IMPORT_OR_EXPORT class AbstractStratigraphicOrganizationInterpretation* getStratigraphicOrganizationInterpretation() const;

		/**
		 * Gets the data object reference of the stratigraphic organization interpretation associated to
		 * this grid.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @returns	Empty data object reference if no stratigraphic organization interpretation is
		 * 			associated to this grid representation. Otherwise return the data object reference of
		 * 			the associated stratigraphic organization interpretation.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getStratigraphicOrganizationInterpretationDor() const;

		/**
		 * Queries if there exists some association between stratigraphic unit indices and the cells of
		 * this grid.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @returns	True if this grid representation has got some association between stratigraphic unit
		 * 			indices and cells.
		 */
		DLL_IMPORT_OR_EXPORT bool hasCellStratigraphicUnitIndices() const;

		/**
		 * Gets the stratigraphic unit indices (regarding the associated stratigraphic organization
		 * interpretation) of each cell of this grid representation.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the associated stratigraphic unit indices are not
		 * 										stored in a HDF5 integer array.
		 * @exception	std::invalid_argument	If the cells of this grid are not associated with
		 * 										stratigraphic units indices.
		 *
		 * @param [out]	stratiUnitIndices	An array to receive the stratigraphic unit indices associated
		 * 									to the cells of this grid. It must be preallocated with a
		 * 									count equal to getCellCount(). It will be filled in with the
		 * 									stratigraphic unit indices ordered as grid cells are ordered.
		 *
		 * @returns	The null value. The null value is used to tell the association between a cell and
		 * 			stratigraphic unit is unavailable.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getCellStratigraphicUnitIndices(uint64_t * stratiUnitIndices);

		//************************************************************
		//**************** LINK WITH ROCKFLUID ********************
		//************************************************************

		/**
		 * Sets the rock fluid organization interpretation which is associated to this grid
		 * representation.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If no default HDF proxy is defined in the repository.
		 *
		 * @param [in]	rockFluidUnitIndices	Index of the rock fluid unit of a given rock fluid column
		 * 										for each cell. Array length is the number of cells in the
		 * 										grid or the blocked well.
		 * @param 	  	nullValue				The value which is used to tell the association between a
		 * 										cell and a rock fluid unit is unavailable.
		 * @param [in]	rockFluidOrgInterp  	The rock fluid organization interpretation which is
		 * 										associated to this grid representation.
		 */
		DLL_IMPORT_OR_EXPORT void setCellAssociationWithRockFluidOrganizationInterpretation(uint64_t* rockFluidUnitIndices, uint64_t nullValue, class RockFluidOrganizationInterpretation* rockFluidOrgInterp);
		
		/**
		 * Gets rock fluid organization interpretation which is associated to this grid.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @returns	nullptr if no rock fluid organization interpretation is associated to this grid
		 * 			representation. Otherwise return the associated rock fluid organization
		 * 			interpretation.
		 */
		DLL_IMPORT_OR_EXPORT class RockFluidOrganizationInterpretation* getRockFluidOrganizationInterpretation() const;

		/**
		 * Gets the data object reference of the rock fluid organization interpretation associated to
		 * this grid.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @returns	Empty data object reference if no rock fluid organization interpretation is
		 * 			associated to this grid representation. Otherwise return the data object reference of
		 * 			the associated rock fluid organization interpretation.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getRockFluidOrganizationInterpretationDor() const;

		/**
		 * Queries if there exists some association between fluid phase unit indices and the cells of
		 * this grid.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @returns	True if this grid representation has got some association between rock fluid unit
		 * 			indices and cell.
		 */
		DLL_IMPORT_OR_EXPORT bool hasCellFluidPhaseUnitIndices() const;

		/**
		 * Gets the rock fluid unit indices (regarding the associated rock fluid organization
		 * interpretation) of each cell of this grid representation.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the associated stratigraphic unit indices are not
		 * 										stored in a HDF5 integer array.
		 * @exception	std::invalid_argument	If the cells of this grid are not associated with rock
		 * 										fluid units indices.
		 *
		 * @param [out]	rockfluidUnitIndices	An array to receive the rock fluid unit indices
		 * 										associated to the cells of this grid? It must be allocated
		 * 										with a count equal to getCellCount(). It will be filled in
		 * 										with the rock fluid unit indices ordered as grid cells are
		 * 										ordered.
		 *
		 * @returns	The null value. The null value is used to tell the association between a cell and
		 * 			rock fluid unit is unavailable.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getCellFluidPhaseUnitIndices(uint64_t * rockfluidUnitIndices);


		//************************************************************
		//********************** TRUNCATION **************************
		//************************************************************

		/**
		 * Indicates whether this grid instance contains truncated pillars or not.
		 *
		 * @returns	True if truncated pillars exist, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isTruncated() const;

		/**
		 * Gets the truncated face count. It does not include face of truncated cells which are not
		 * truncated.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 *
		 * @returns	The truncated face count.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getTruncatedFaceCount() const;

		/**
		 * Gets all the node indices of the truncated faces.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the node indices of the truncated faces are not stored
		 * 										in a HDF5 integer array.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 *
		 * @param [out]	nodeIndices	An array to receive the node indices of the truncated faces. It must
		 * 							be preallocated with the last value returned by
		 * 							getCumulativeNodeCountOfTruncatedFaces().
		 */
		DLL_IMPORT_OR_EXPORT void getNodeIndicesOfTruncatedFaces(uint64_t * nodeIndices) const;

		/**
		 * Gets the cumulative node count per truncated face. First value is the count of nodes in the
		 * first face. Second value is the count of nodes in the first and in the second face. Third
		 * value is the count of nodes in the first and in the second and in the third face. Etc... The
		 * length of the output array is equal to getTruncatedFaceCount(). A single node count should be
		 * at least 3.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 * @exception	std::range_error	 	If the cumulative length of nodes count per cells is
		 * 										constant (it is stored in a constant integer array).
		 *
		 * @param [in]	nodeCountPerFace	An array to receive the cumulative node count per truncated
		 * 									face. It must be preallocated with getTruncatedFaceCount()
		 * 									(equals to last value of
		 * 									getCumulativeTruncatedFaceCountPerTruncatedCell())
		 */
		DLL_IMPORT_OR_EXPORT void getCumulativeNodeCountPerTruncatedFace(uint64_t * nodeCountPerFace) const;

		/**
		 * Get the node count per truncated face. This method is less efficient than
		 * getCumulativeNodeCountPerTruncatedFace(). First value is the count of nodes in the first
		 * face. Second value is the count of nodes in the second face. etc...
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 * @exception	std::range_error	 	If the cumulative length of nodes count per cells is
		 * 										constant (it is stored in a constant integer array).
		 *
		 * @param [out]	nodeCountPerFace	An array to receive the node count per truncated face. It
		 * 									must be preallocated with getTruncatedFaceCount() (equals to last
		 * 									value of getCumulativeTruncatedFaceCountPerTruncatedCell()).
		 */
		DLL_IMPORT_OR_EXPORT void getNodeCountPerTruncatedFace(uint64_t * nodeCountPerFace) const;

		/**
		 * Gets the truncated cell count.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 *
		 * @returns	The truncated cell count.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getTruncatedCellCount() const;

		/**
		 * Gets the parent cell index for each of the truncation cells.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the parent cell indices are stored neither in a HDF5
		 * 										integer array nor in a constant integer array.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 *
		 * @param [out]	cellIndices	An array to receive the parent cell index of each truncation cell. It
		 * 							must be preallocated with getTruncatedCellCount.
		 */
		DLL_IMPORT_OR_EXPORT void getTruncatedCellIndices(uint64_t* cellIndices) const;

		/**
		 * Gets all the truncated face indices of all the truncated cells. It does not get the non
		 * truncated face indices of a truncated cell. Please use
		 * getNonTruncatedFaceIndicesOfTruncatedCells() in addition to this method in order to get the
		 * full list of face indices for a truncated cell.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the truncated face indices are not stored in a HDF5
		 * 										integer array.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 *
		 * @param [out]	faceIndices	An array to receive the truncated face indices of all the truncated
		 * 							cells. It must be preallocated with the last value returned by
		 * 							getCumulativeTruncatedFaceCountPerTruncatedCell()
		 */
		DLL_IMPORT_OR_EXPORT void getTruncatedFaceIndicesOfTruncatedCells(uint64_t * faceIndices) const;

		/**
		 * Gets the cumulative truncated face count per truncated cell. It does not take into account
		 * the non truncated face of a truncated cell. First value is the count of faces in the first
		 * cell. Second value is the count of faces in the first and in the second cell. Third value is
		 * the count of faces in the first and in the second and in the third cell. Etc... The length of
		 * the output array is equal to getTruncatedCellCount(). A single face count should be at least
		 * 4.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 * @exception	std::range_error	 	If the cumulative length of truncated faces count per
		 * 										cells is constant (it is stored in a constant integer
		 * 										array) while there is more than one cell in the grid.
		 *
		 * @param [out]	cumulativeFaceCountPerCell	An array to receive the cumulative truncated face
		 * 											count per truncated cell. It must be pre allocated
		 * 											with getTruncatedCellCount().
		 */
		DLL_IMPORT_OR_EXPORT void getCumulativeTruncatedFaceCountPerTruncatedCell(uint64_t * cumulativeFaceCountPerCell) const;

		/**
		 * Gets the truncated face count per truncated cell. This method is less efficient than
		 * getCumulativeTruncatedFaceCountPerTruncatedCell(). First value is the count of faces in the
		 * first cell. Second value is the count of faces in the second cell. etc...
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 * @exception	std::range_error	 	If the cumulative length of faces count per cells is
		 * 										constant (it is stored in a constant integer array) while
		 * 										there is more than one cell in the grid.
		 *
		 * @param [out]	faceCountPerCell	An array to receive the truncated face count per truncated
		 * 									cell. It must be preallocated with getTruncatedCellCount()
		 */
		DLL_IMPORT_OR_EXPORT void getTruncatedFaceCountPerTruncatedCell(uint64_t * faceCountPerCell) const;

		/**
		 * Gets all the non truncated face indices of all the truncated cells. It does not get the
		 * truncated face indices of a truncated cell. Please use
		 * getTruncatedFaceIndicesOfTruncatedCells() in addition to this method in order to get the full
		 * list of face indices for a truncated cell.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the non truncated face indices are not stored in a
		 * 										HDF5 integer array.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 *
		 * @param [out]	faceIndices	An array to receive the non truncated face indices of all the
		 * 							truncated cells.It must be pre allocated with the last value returned
		 * 							by getCumulativeNonTruncatedFaceCountPerTruncatedCell()
		 */
		DLL_IMPORT_OR_EXPORT void getNonTruncatedFaceIndicesOfTruncatedCells(uint64_t * faceIndices) const;

		/**
		 * Get the cumulative non truncated face count per truncated cell. It does not take into account
		 * the truncated face indices of a truncated cell. First value is the count of faces in the
		 * first cell. Second value is the count of faces in the first and in the second cell. Third
		 * value is the count of faces in the first and in the second and in the third cell. Etc...
		 * Count of this array is equal to getTruncatedCellCount(). A single face count should be at
		 * least 4.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 * @exception	std::range_error	 	If the cumulative length of non truncated faces count per
		 * 										cells is constant (it is stored in a constant integer
		 * 										array) while there is more than one cell in the grid.
		 *
		 * @param [out]	cumulativeFaceCountPerCell	An array to receive the cumulative non truncated face
		 * 											count per truncated cell. It must be preallocated with
		 * 												getTruncatedCellCount()
		 */
		DLL_IMPORT_OR_EXPORT void getCumulativeNonTruncatedFaceCountPerTruncatedCell(uint64_t * cumulativeFaceCountPerCell) const;

		/**
		 * Gets the non truncated face count per cell. This method is less efficient than
		 * getCumulativeNonTruncatedFaceCountPerTruncatedCell(). First value is the count of faces in
		 * the first cell. Second value is the count of faces in the second cell. etc...
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 * @exception	std::range_error	 	If the cumulative length of non truncated faces count per
		 * 										cells is constant (it is stored in a constant integer
		 * 										array) while there is more than one cell in the grid.
		 *
		 * @param [out]	faceCountPerCell	An array to receive the non truncated face count per
		 * 									truncated cell. It must be pre allocated with
		 * 									getTruncatedCellCount()
		 */
		DLL_IMPORT_OR_EXPORT void getNonTruncatedFaceCountPerTruncatedCell(uint64_t * faceCountPerCell) const;

		/**
		 * Retrieves the orientation of each truncated face (i.e. if each truncated face is right handed
		 * or not).
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the orientation of the truncated faces is neither
		 * 										stored in a HDF5 boolean array nor in a boolean constant
		 * 										array.
		 * @exception	std::invalid_argument	If this grid is not truncated.
		 *
		 * @param [out]	cellFaceIsRightHanded	An array to receive the orientation of truncated faces.
		 * 										Value '0' means left handed and value other than '0'
		 * 										means right handed. It must be preallocated with
		 * 										getTruncatedFaceCount()
		 */
		DLL_IMPORT_OR_EXPORT void getTruncatedFaceIsRightHanded(unsigned char* cellFaceIsRightHanded) const;

		/** The standard XML tag without XML namespace for serializing this data object */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/** Loads target relationships */
		void loadTargetRelationships();

	protected:

		/** True to with truncated pillars */
		bool withTruncatedPillars;
	};
}
