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
	/**
	 * @brief	Proxy class for a sub-representation. A sub representation is an ordered list of
	 * 			indexable elements and/or indexable element pairs of an existing representation.
	 * 			
	 * 			Because the representation concepts of topology, geometry, and property values are
	 * 			separate in RESQML, it is now possible to select a range of nodes, edges, faces, or
	 * 			volumes (cells) indices from the topological support of an existing representation to
	 * 			define a sub-representation. A sub- representation may describe a different feature
	 * 			interpretation using the same geometry or property as the "parent" representation. In
	 * 			this case, the only information exchanged is a set of potentially non-consecutive
	 * 			indices of the topological support of the representation.
	 */
	class SubRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~SubRepresentation() = default;

		/**
		 * Gets the kind of the selected elements for all patches of this sub-representation.
		 *
		 * @exception	std::invalid_argument	If the RESQML instance has got various selected element kinds
		 *										as RESQML2.0 allows.
		 *
		 * @returns	The kind of the selected elements.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_eml2_3::eml23__IndexableElement getElementKind() const = 0;

		/**
		 * Gets the count of the selected elements of a particular patch of this sub-representation.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of range.
		 *
		 * @param 	patchIndex	Zero-based index of the patch from which we want to count the selected
		 * 						elements.
		 *
		 * @returns	The count of the selected elements.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getElementCountOfPatch(uint64_t patchIndex) const = 0;

		/**
		 * Gets the indices of the selected elements for a particular patch of this sub-representation.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of range.
		 * @exception	logic_error		 	If the selected elements indices of the patch are not stored
		 * 									in a HDF5 integer array.
		 *
		 * @param 	   	patchIndex		   	Zero-based index of the patch.
		 * @param [out]	elementIndices	   	Output array for collecting the indices of the selected
		 * 									elements. It must be preallocated with
		 * 									{@link getElementCountOfPatch()} size.
		 * @return The null value
		 */
		DLL_IMPORT_OR_EXPORT virtual int64_t getElementIndicesOfPatch(uint64_t patchIndex, int64_t* elementIndices) const = 0;

		/**
		 * Checks if the element indices of a particular patch are based on a lattice or not.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of range.
		 *
		 * @param 	patchIndex		   	Zero-based index of the patch.
		 *
		 * @returns	True if element indices based on lattice, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool areElementIndicesBasedOnLattice(uint64_t patchIndex) const = 0;

		/**
		 * Gets the start value of the lattice the element indices of a particular patch are based on.
		 *
		 * @exception	std::invalid_argument	If the element indices are not based on a lattice.
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 *
		 * @param 	patchIndex		   	Zero-based index of the patch.
		 *
		 * @returns	The lattice start value.
		 */
		DLL_IMPORT_OR_EXPORT virtual int64_t getLatticeElementIndicesStartValue(uint64_t patchIndex) const = 0;

		/**
		 * Gets the dimension count of the lattice the element indices of a particular patch are based
		 * on.
		 *
		 * @exception	std::invalid_argument	If the element indices are not based on a lattice.
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 *
		 * @param 	patchIndex		   	Zero-based index of the patch.
		 *
		 * @returns	The lattice dimension count.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getLatticeElementIndicesDimensionCount(uint64_t patchIndex) const = 0;

		/**
		 * Gets the offset value at a given dimension of the lattice the element indices of a particular
		 * patch are based on.
		 *
		 * @exception	std::invalid_argument	If the element indices are not based on a lattice.
		 * @exception	std::out_of_range	 	If @p latticeDimensionIndex is out of range.
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 * @exception	std::out_of_range	 	If @p elementIndicesIndex is out of range. Must be: 0 for
		 * 										non pairwise element indices; 0 or 1 for pairwise element
		 * 										indices (0 for the left and 1 for the right part of the
		 * 										pairs).
		 *
		 * @param 	latticeDimensionIndex	Zero-based index of the lattice dimension.
		 * @param 	patchIndex			 	Zero-based index of the patch.
		 * @param 	elementIndicesIndex  	(Optional) In case of pairwise elements, allow to select the
		 * 									first (<tt>elementIndicesIndex = 0</tt>)
		 * 									or second (<tt>elementIndicesIndex = 1</tt>) element index of
		 * 									the pair. Default value is @c 0, corresponding to both non-
		 * 									pairwise elements and first element of a pair.
		 *
		 * @returns	The offset value.
		 */
		DLL_IMPORT_OR_EXPORT virtual int64_t getLatticeElementIndicesOffsetValue(unsigned int latticeDimensionIndex, uint64_t patchIndex) const = 0;

		/**
		 * Gets the offset count at a given dimension of the lattice the element indices of a particular
		 * patch are based on.
		 *
		 * @exception	std::invalid_argument	If the element indices are not based on a lattice.
		 * @exception	std::out_of_range	 	If @p latticeDimensionIndex is out of range.
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 *
		 * @param 	latticeDimensionIndex	Zero-based index of the lattice dimension.
		 * @param 	patchIndex			 	Zero-based index of the patch.
		 *
		 * @returns	The offset count.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getLatticeElementIndicesOffsetCount(unsigned int latticeDimensionIndex, uint64_t patchIndex) const = 0;

		/**
		 * Pushes back a new lattice-based patch (without pairwise elements) in this sub-representation.
		 * The offset value is set to 1 in each dimension of the lattice.
		 *
		 * @param 	originIndex					  	The index of the origin (its start value).
		 * @param 	elementCountInSlowestDimension	The number of elements in the slowest dimension
		 * 											(commonly in K dimension).
		 * @param 	elementCountInMiddleDimension 	The number of elements in the middle dimension
		 * 											(commonly in J dimension).
		 * @param 	elementCountInFastestDimension	The number of elements in the fastest dimension
		 * 											(commonly in I dimension).
		 * @param	ijkGrid							The supporting IJK grid representation.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackSubRepresentationPatch(uint64_t originIndex,
			unsigned int elementCountInSlowestDimension,
			unsigned int elementCountInMiddleDimension,
			unsigned int elementCountInFastestDimension, RESQML2_NS::AbstractIjkGridRepresentation* ijkGrid) = 0;

		/**
		 * Pushes back a new patch in this sub-representation.
		 *
		 * @param 	  	elementCount			The count of elements which constitutes the sub-
		 * 										representation patch.
		 * @param [in]	elementIndices			The indices of the elements in the supporting
		 * 										representation.
		 * @param [in]	supportingRep			The supporting representation
		 * 										corresponding to the element indices.
		 * @param [in]	proxy					(Optional) The HDF proxy where the numerical values (indices)
		 * 										are stored.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackSubRepresentationPatch(uint64_t elementCount, int64_t* elementIndices,
			RESQML2_NS::AbstractRepresentation* supportingRep, EML2_NS::AbstractHdfProxy* proxy = nullptr) = 0;

		/**
		 * Pushes back a new patch in this sub-representation where the
		 * indices values have not to yet been written in the HDF5 file. The reason can be that the
		 * indices values already exist in an external file (only HDF5 for now) or that the writing of
		 * these indices values in the external file is postponed in time.
		 *
		 * @param 	  	elementCount			The count of elements which constitutes the sub-
		 * 										representation patch.
		 * @param 	  	elementDataset			The HDF5 dataset name where the element indices are
		 * 										stored. If empty, the dataset will be named the same as the
		 * 										dataset naming convention fesapi : <tt>getHdfGroup() + subRep-
		 * 										&gt;uuid + "/subrepresentation_elementIndices0_patch" +
		 * 										patchIndex;</tt>
		 * @param 	  	nullValue				The null value which has been chosen in the referenced
		 * 										HDF5 dataset.
		 * @param [in]	supportingRep			The supporting representation
		 * 										corresponding to the element indices.
		 * @param [in]	proxy					(Optional) The HDF5 proxy where the values are already stored or
		 * 										will be stored.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackRefToExistingDataset(uint64_t elementCount, const std::string& elementDataset,
			int64_t nullValue, RESQML2_NS::AbstractRepresentation* supportingRep, EML2_NS::AbstractHdfProxy* proxy = nullptr) = 0;

		/**   
		 * @copydoc AbstractRepresentation::getXyzPointCountOfPatch  
		 *
		 * @exception std::logic_error If the kind of the selected elements of this patch is not node (non 
		 * 							   pairwise) or if the kind of the left part of the pairs of elements is
		 * 							    not node (pairwise case).
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getXyzPointCountOfPatch(uint64_t patchIndex) const override;

		/** Please do note use : not implemented yet. */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(uint64_t patchIndex, double* xyzPoints) const override;

		DLL_IMPORT_OR_EXPORT virtual uint64_t getPatchCount() const override = 0;

		/**
		 * Gets the supporting representation of a specific patch of this sub-representation.
		 *
		 * @exception	std::invalid_argument	If no supporting representation is already associated to
		 * 										this sub-representation.
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 *
		 * @param 	patchIndex	Zero-based index of the patch of the subrepresentation.
		 *
		 * @returns	The supporting representation of patch @p patchIndex.
		 */
		DLL_IMPORT_OR_EXPORT AbstractRepresentation* getSupportingRepresentationOfPatch(uint64_t patchIndex = 0) const;

		/**
		 * Gets the data object reference of the supporting representation of a specific patch of this sub-representation.
		 *
		 * @exception	std::invalid_argument	If no supporting representation is already associated to
		 * 										this sub-representation.
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 *
		 * @param 	patchIndex	Zero-based index of the patch of the subrepresentation.
		 *
		 * @returns	The data object reference of the supporting representation of patch @p patchIndex.
		 */
		virtual COMMON_NS::DataObjectReference getSupportingRepresentationOfPatchDor(uint64_t patchIndex = 0) const = 0;

		/** The standard XML tag without XML namespace for serializing this data object */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "SubRepresentation";

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT SubRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			RESQML2_NS::AbstractRepresentation(partialObject) {}

		/** Default constructor */
		SubRepresentation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		SubRepresentation(gsoap_resqml2_0_1::_resqml20__SubRepresentation* fromGsoap) : RESQML2_NS::AbstractRepresentation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		SubRepresentation(gsoap_eml2_3::_resqml22__SubRepresentation* fromGsoap) : RESQML2_NS::AbstractRepresentation(fromGsoap) {}
	};
}
