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

/** . */
namespace RESQML2_NS
{
	class AbstractGridRepresentation;

	/** A blocked wellbore representation. */
	class BlockedWellboreRepresentation : public WellboreFrameRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~BlockedWellboreRepresentation() {}

		/**
		 * Set all information about the intersected grid cells. You must first provide MD values of the
		 * frame before to use this method.
		 *
		 * @param [in,out]	gridIndices								Size of array = IntervalCount on the
		 * 															wellbore frame rep. BUSINESS RULE: The
		 * 															cell count must equal the number of non-
		 * 															null entries in this array. The grids
		 * 															(and there indices) are defined using
		 * 															pushBackSupportingGridRepresentation
		 * 															method.
		 * @param 		  	gridIndicesNullValue					The null value used in gridIndices in
		 * 															order to indicate that an interval deos
		 * 															not correspond to any intersected grid.
		 * @param 		  	cellCount								The number of non-null entries in the
		 * 															grid indices array.
		 * @param [in,out]	cellIndices								The intersected cell index for each
		 * 															non null gridIndices. They are ordered
		 * 															according to non null gridIndices. Array
		 * 															length must equal cell count.
		 * @param [in,out]	localFacePairPerCellIndices				For each cell, these are the entry
		 * 															and exit intersection faces of the
		 * 															trajectory in the cell. The array
		 * 															dimensions must equal 2 x CellCount.
		 * @param 		  	localFacePairPerCellIndicesNullValue	The null value used in
		 * 															localFacePerCellIndices in order to
		 * 															indicate that it corresponds to a missing
		 * 															intersection, e.g., when a trajectory
		 * 															originates or terminates within a cell.
		 * @param [in,out]	hdfProxy								The hdf proxy where the numerical
		 * 															values will be stored.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setIntevalGridCells(unsigned int const* gridIndices, unsigned int gridIndicesNullValue,
			unsigned int cellCount, ULONG64 const* cellIndices,
			unsigned char const* localFacePairPerCellIndices, unsigned char localFacePairPerCellIndicesNullValue, EML2_NS::AbstractHdfProxy * hdfProxy) = 0;

		/**
		 * The number of non-null entries in the grid indices array.
		 *
		 * @returns	The cell count.
		 */
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getCellCount() const = 0;

		/**
		 * Size of array = IntervalCount on the wellbore frame rep. The grids (and there indices) are
		 * defined using pushBackSupportingGridRepresentation method.
		 *
		 * @param [in,out]	gridIndices	If non-null, the grid indices.
		 *
		 * @returns	nullValue.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getGridIndices(unsigned int * gridIndices) const = 0;

		/**
		 * Pushes back a grid representation which is one of the support of this representation. And
		 * push back this representation as a grid connection information of the grid representation as
		 * well.
		 *
		 * @param [in,out]	supportingGridRep	If non-null, the supporting grid rep.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackSupportingGridRepresentation(RESQML2_NS::AbstractGridRepresentation * supportingGridRep) = 0;

		/**
		 * Get the count of the supporting grid representations of this grid connection representation.
		 *
		 * @returns	The supporting grid representation count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getSupportingGridRepresentationCount() const = 0;

		/**
		 * Get the supporting grid representation located at a specific index of this blocked wellbore
		 * representation.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	Null if it fails, else the supporting grid representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractGridRepresentation* getSupportingGridRepresentation(unsigned int index) const;

		/**
		 * Get the supporting grid representation dor located at a specific index of this blocked
		 * wellbore representation.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	Null if it fails, else the supporting grid representation dor.
		 */
		virtual COMMON_NS::DataObjectReference getSupportingGridRepresentationDor(unsigned int index) const = 0;

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

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