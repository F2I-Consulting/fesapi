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

#include "WellboreFrameRepresentation.h"

namespace RESQML2_NS
{
	class AbstractGridRepresentation;

	/**
	 * A blocked wellbore representation. This is the information that allows you to locate, on one
	 * or several grids (existing or planned), the intersection of volume (cells) and surface
	 * (faces) elements with a wellbore trajectory (existing or planned).
	 */
	class BlockedWellboreRepresentation : public WellboreFrameRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~BlockedWellboreRepresentation() {}

		/**
		 * Sets all information about the intersected grid cells. You must first provide MD values of
		 * the frame before to use this method.
		 *
		 * @exception	std::invalid_argument	If @p gridIndices, @p cellIndices, @p
		 * 										localFacePairPerCellIndices or @p hdfProxy is @c nullptr.
		 * @exception	std::invalid_argument	If <tt>cellCount == 0</tt>.
		 * @exception	std::logic_error	 	If MD values of the frame have not been provided before
		 * 										using this method.
		 *
		 * @param 		  	gridIndices								An array containing for each interval
		 * 															of the wellbore frame, the index of the
		 * 															grid it is associated to. The size of
		 * 															this array is the interval count of the
		 * 															wellbore frame representation. @p
		 * 															cellCount must equal the number of non-
		 * 															null entries in this array. The
		 * 															associated grids (and there indices) are
		 * 															defined using
		 * 															pushBackSupportingGridRepresentation()
		 * 															method.
		 * @param 		  	gridIndicesNullValue					The null value used in @p gridIndices
		 * 															in order to indicate that an interval
		 * 															does not correspond to any intersected
		 * 															grid.
		 * @param 		  	cellCount								The number of non-null entries in @p
		 * 															gridIndices.
		 * @param 		  	cellIndices								An array containing the intersected
		 * 															cell index for each non-null entry in @p
		 * 															gridIndices. They are ordered according
		 * 															to non-null entries of @p gridIndices.
		 * 															The array length must equal @p cellCount.
		 * @param 		  	localFacePairPerCellIndices				An array containing, for each cell,
		 * 															the entry and exit intersection faces of
		 * 															the trajectory in the cell. The array
		 * 															dimension must equal <tt>2 *
		 * 															cellCount</tt>.
		 * @param 		  	localFacePairPerCellIndicesNullValue	The null value used in @p
		 * 															localFacePerCellIndices in order to
		 * 															indicate that it corresponds to a missing
		 * 															intersection, e.g., when a trajectory
		 * 															originates or terminates within a cell.
		 * @param [in,out]	hdfProxy								The HDF proxy where the numerical
		 * 															values will be stored. It must be already
		 * 															opened for writing and won't be closed.It
		 * 															cannot be @c nullptr.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setIntevalGridCells(unsigned int const* gridIndices, unsigned int gridIndicesNullValue,
			unsigned int cellCount, ULONG64 const* cellIndices,
			unsigned char const* localFacePairPerCellIndices, unsigned char localFacePairPerCellIndicesNullValue, EML2_NS::AbstractHdfProxy * hdfProxy) = 0;

		/**
		 * Gets the cell count, that is to say the number of non-null entries in the grid indices array.
		 *
		 * @returns	The cell count.
		 */
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getCellCount() const = 0;

		/**
		 * For each interval of the wellbore frame, gets the index of the grid it is associated to.
		 *
		 * @exception	std::range_error	If the grid indices are stored in an integer constant array
		 * 									and if the the constant value is strictly superior than unsigned
		 * 									int maximum value.
		 * @exception	std::logic_error	If the grid indices are neither stored in a HDF5 integer
		 * 									array nor in an integer constant array.
		 *
		 * @param [out]	gridIndices	An array for receiving the grids indices. The size of this array is
		 * 							the interval count of the wellbore frame representation. The
		 * 							associated grids (and there indices) are defined using
		 * 							pushBackSupportingGridRepresentation() method.
		 *
		 * @returns	The null value used in @p gridIndices in order to indicate that an interval does not
		 * 			correspond to any intersected grid.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getGridIndices(unsigned int * gridIndices) const = 0;

		/**
		 * Pushes back a grid representation which is one of the support of this representation.
		 *
		 * @exception	std::invalid_argument	If <tt>supportingGridRep == nullptr</tt>.
		 *
		 * @param [in]	supportingGridRep	The supporting grid representation to push back.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackSupportingGridRepresentation(RESQML2_NS::AbstractGridRepresentation * supportingGridRep) = 0;

		/**
		 * Gets the count of supporting grid representations of this blocked wellbore representation.
		 *
		 * @exception	std::range_error	If the count of supporting grid representations is strictly
		 * 									greater than unsigned int max.
		 *
		 * @returns	The count of supporting grid representation.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getSupportingGridRepresentationCount() const = 0;

		/**
		 * Gets the supporting grid representation located at a specific index of this blocked wellbore
		 * representation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt>
		 * 									getSupportingGridRepresentationCount().
		 *
		 * @param 	index	Zero-based index of the supporting grid representation we look for.
		 *
		 * @returns	The supporting grid representation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractGridRepresentation* getSupportingGridRepresentation(unsigned int index) const;

		/**
		 * Get the DOR of the supporting grid representation located at a specific index of this blocked
		 * wellbore representation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt>
		 * 									getSupportingGridRepresentationCount().
		 *
		 * @param 	index	Zero-based index of the supporting grid representation we look for.
		 *
		 * @returns	The DOR of the supporting grid representation at position @p index.
		 */
		virtual COMMON_NS::DataObjectReference getSupportingGridRepresentationDor(unsigned int index) const = 0;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const override { return XML_TAG; }

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT BlockedWellboreRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WellboreFrameRepresentation(partialObject) {}

		/**
		 * Defatul constructor
		 */
		BlockedWellboreRepresentation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		BlockedWellboreRepresentation(gsoap_resqml2_0_1::_resqml20__BlockedWellboreRepresentation* fromGsoap) : WellboreFrameRepresentation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		BlockedWellboreRepresentation(gsoap_eml2_3::_resqml22__BlockedWellboreRepresentation* fromGsoap) : WellboreFrameRepresentation(fromGsoap) {}

		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
