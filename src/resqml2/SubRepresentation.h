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
		virtual ~SubRepresentation() {}

		/**
		 * Gets the kind of the selected elements for a particular patch of this sub-representation.
		 *
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 * @exception	std::out_of_range	 	If @p elementIndicesIndex is out of range. Must be: 0 for
		 * 										non pairwise element indices; 0 or 1 for pairwise element
		 * 										indices (0 for the left and 1 for the right part of the
		 * 										pairs).
		 * @exception	std::invalid_argument	If the kind of the selected elements we look for is not
		 * 										supported (the kind is neither a node, edge, face, volume
		 * 										nor pillar).
		 *
		 * @param 	patchIndex		   	Zero-based index of the patch.
		 * @param 	elementIndicesIndex	Must be equal to 0 if the element indices are not pairwise. This
		 * 								method must be called twice if the element indices are pairwise:
		 * 								one call with <tt>elementIndicesIndex = 0</tt> for getting the
		 * 								kind of the left elements of the pair; one call with
		 * 								<tt>elementIndices = 1</tt> for getting the kind of the right
		 * 								elements of the pair.
		 *
		 * @returns	The kind of the selected elements.
		 */
		DLL_IMPORT_OR_EXPORT virtual indexableElement getElementKindOfPatch(unsigned int patchIndex, unsigned int elementIndicesIndex) const = 0;

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
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getElementCountOfPatch(unsigned int patchIndex) const = 0;

		/**
		 * Gets the indices of the selected elements for a particular patch of this sub-representation.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of range.
		 * @exception	std::out_of_range	If @p elementIndicesIndex is out of range. Must be: 0 for non
		 * 									pairwise element indices; 0 or 1 for pairwise element indices
		 * 									(0 for the left and 1 for the right part of the pairs).
		 * @exception	logic_error		 	If the selected elements indices of the patch are not stored
		 * 									in a HDF5 integer array.
		 *
		 * @param 	   	patchIndex		   	Zero-based index of the patch.
		 * @param 	   	elementIndicesIndex	Must be equal to 0 if the element indices are not pairwise.
		 * 									This method must be called twice if the element indices are
		 * 									pairwise: one call with <tt>elementIndicesIndex = 0</tt> for
		 * 									getting the indices of the left elements of the pair;
		 * 									one call with <tt>elementIndices = 1</tt> for getting the
		 * 									indices of the right elements of the pair.  
		 * @param [out]	elementIndices	   	Output array for collecting the indices of the selected
		 * 									elements. It must be preallocated with
		 * 									{@link getElementCountOfPatch()} size.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getElementIndicesOfPatch(unsigned int patchIndex, unsigned int elementIndicesIndex, ULONG64* elementIndices) const = 0;

		/**
		 * @brief	Gets the indices of the supporting representations that refer the selected elements
		 * 			indices of a particular patch of this sub-representation.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of range.
		 *
		 * @param 	   	patchIndex					   	Zero-based index of the patch.
		 * @param [out]	supportingRepresentationIndices	Output array for collecting the supporting
		 * 												representations indices. This array must be
		 * 												preallocated with getElementCountOfPatch()
		 * 												size. The index at a given position is the index
		 * 												of the supporting representation associated to
		 * 												the selected element (or the selected pair of
		 * 												elements) at the same position in the sub-
		 * 												elements) at the same position in the sub-
		 * 												representation patch.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getSupportingRepresentationIndicesOfPatch(unsigned int patchIndex, short* supportingRepresentationIndices) const = 0;

		/**
		 * Checks if the element indices of a particular patch are pairwise or not.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of range.
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	True if the elements indices are pairwise, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool areElementIndicesPairwise(unsigned int patchIndex) const = 0;

		/**
		 * Checks if the element indices of a particular patch are based on a lattice or not.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of range.
		 * @exception	std::out_of_range	If @p elementIndicesIndex is out of range. Must be: 0 for non
		 * 									pairwise element indices; 0 or 1 for pairwise element indices
		 * 									(0 for the left and 1 for the right part of the pairs).
		 *
		 * @param 	patchIndex		   	Zero-based index of the patch.
		 * @param 	elementIndicesIndex	(Optional) In case of pairwise elements, allows to select the
		 * 								first (<tt>elementIndicesIndex = 0</tt>)
		 * 								or second (<tt>elementIndicesIndex = 1</tt>) element index of the
		 * 								pair. Default value is @c 0, corresponding to both non-pairwise
		 * 								elements and first element of a pair.
		 *
		 * @returns	True if element indices based on lattice, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool areElementIndicesBasedOnLattice(unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const = 0;

		/**
		 * Gets the start value of the lattice the element indices of a particular patch are based on.
		 *
		 * @exception	std::invalid_argument	If the element indices are not based on a lattice.
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 * @exception	std::out_of_range	 	If @p elementIndicesIndex is out of range. Must be: 0 for
		 * 										non pairwise element indices; 0 or 1 for pairwise element
		 * 										indices (0 for the left and 1 for the right part of the
		 * 										pairs).
		 *
		 * @param 	patchIndex		   	Zero-based index of the patch.
		 * @param 	elementIndicesIndex	(Optional) In case of pairwise elements, allow to select the
		 * 								first (<tt>elementIndicesIndex = 0</tt>)
		 * 								or second (<tt>elementIndicesIndex = 1</tt>) element index of the
		 * 								pair. Default value is @c 0, corresponding to both non-pairwise
		 * 								elements and first element of a pair.
		 *
		 * @returns	The lattice start value.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getLatticeElementIndicesStartValue(unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const = 0;

		/**
		 * Gets the dimension count of the lattice the element indices of a particular patch are based
		 * on.
		 *
		 * @exception	std::invalid_argument	If the element indices are not based on a lattice.
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 * @exception	std::out_of_range	 	If @p elementIndicesIndex is out of range. Must be: 0 for
		 * 										non pairwise element indices; 0 or 1 for pairwise element
		 * 										indices (0 for the left and 1 for the right part of the
		 * 										pairs).
		 *
		 * @param 	patchIndex		   	Zero-based index of the patch.
		 * @param 	elementIndicesIndex	(Optional) In case of pairwise elements, allow to select the
		 * 								first (<tt>elementIndicesIndex = 0</tt>)
		 * 								or second (<tt>elementIndicesIndex = 1</tt>) element index of the
		 * 								pair. Default value is @c 0, corresponding to both non-pairwise
		 * 								elements and first element of a pair.
		 *
		 * @returns	The lattice dimension count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getLatticeElementIndicesDimensionCount(unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const = 0;

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
		DLL_IMPORT_OR_EXPORT virtual LONG64 getLatticeElementIndicesOffsetValue(unsigned int latticeDimensionIndex, unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const = 0;

		/**
		 * Gets the offset count at a given dimension of the lattice the element indices of a particular
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
		 * @returns	The offset count.
		 */
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getLatticeElementIndicesOffsetCount(unsigned int latticeDimensionIndex, unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const = 0;

		/**
		 * Pushes back a new lattice-based patch (without pairwise elements) in this sub-representation.
		 * The offset value is set to 1 in each dimension of the lattice.
		 *
		 * @param 	elementKind					  	The kind of (indexable) elements which constitutes
		 * 											the sub-representation patch.
		 * @param 	originIndex					  	The index of the origin (its start value).
		 * @param 	elementCountInSlowestDimension	The number of elements in the slowest dimension
		 * 											(commonly in K dimension).
		 * @param 	elementCountInMiddleDimension 	The number of elements in the middle dimension
		 * 											(commonly in J dimension).
		 * @param 	elementCountInFastestDimension	The number of elements in the fastest dimension
		 * 											(commonly in I dimension).
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement elementKind, ULONG64 originIndex,
			unsigned int elementCountInSlowestDimension,
			unsigned int elementCountInMiddleDimension,
			unsigned int elementCountInFastestDimension) = 0;

		/**
		 * Pushes back a new patch (without pairwise elements) in this sub-representation.
		 *
		 * @param 	  	elementKind				The kind of (indexable) elements which constitutes the
		 * 										sub-representation patch.
		 * @param 	  	elementCount			The count of elements which constitutes the sub-
		 * 										representation patch.
		 * @param [in]	elementIndices			The indices of the elements in the supporting
		 * 										representation.
		 * @param [in]	proxy					The HDF proxy where the numerical values (indices)
		 * 										are stored.
		 * @param [in]	supportingRepIndices	(Optional) The indices of the supporting representation
		 * 										corresponding to the element indices. The count must be
		 * 										elementCount.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement elementKind, ULONG64 elementCount, ULONG64* elementIndices, EML2_NS::AbstractHdfProxy* proxy, short* supportingRepIndices = nullptr);
		
		/**
		 * Pushes back a new patch in this sub-representation which is constituted by means of pairwise
		 * elements.
		 *
		 * @param 		  	elementKind0   	The kind of (indexable) elements which constitutes the first
		 * 									part of the pair of elements of the sub-representation patch.
		 * @param 		  	elementKind1   	The kind of (indexable) elements which constitutes the second
		 * 									part of the pair of elements of the sub-representation patch.
		 * @param 		  	elementCount   	The count of elements which constitutes the sub-
		 * 									representation patch.
		 * @param [in,out]	elementIndices0	The indices of the first part of the element pairs in the
		 * 									supporting representation.
		 * @param [in,out]	elementIndices1	The indices of the second part of the element pairs in the
		 * 									supporting representation.
		 * @param [in,out]	proxy		   	The HDF proxy where the numerical values (indices) are stored.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement elementKind0, gsoap_eml2_3::resqml22__IndexableElement elementKind1,
			ULONG64 elementCount,
			ULONG64 * elementIndices0, ULONG64 * elementIndices1,
			EML2_NS::AbstractHdfProxy* proxy) = 0;

		/**
		 * Pushes back a new patch (without pairwise elements) in this sub-representation where the
		 * indices values have not to yet been written in the HDF5 file. The reason can be that the
		 * indices values already exist in an external file (only HDF5 for now) or that the writing of
		 * these indices values in the external file is postponed in time.
		 *
		 * @param 	  	elementKind				The kind of (indexable) elements which constitutes the
		 * 										sub-representation patch.
		 * @param 	  	elementCount			The count of elements which constitutes the sub-
		 * 										representation patch.
		 * @param 	  	elementDataset			The HDF5 dataset name where the element indices are
		 * 										stored. If empty, the dataset will be named the same as the
		 * 										dataset naming convention fesapi : <tt>getHdfGroup() + subRep-
		 * 										&gt;uuid + "/subrepresentation_elementIndices0_patch" +
		 * 										patchIndex;</tt>
		 * @param 	  	nullValue				The null value which has been chosen in the referenced
		 * 										HDF5 dataset.
		 * @param [in]	proxy					The HDF5 proxy where the values are already stored or
		 * 										will be stored.
		 * @param 	  	supportingRepDataset	(Optional) The HDF5 dataset name where the element
		 * 										indices are stored. If empty (default), no information about
		 * 										suppporting representation will be exported since there is
		 * 										only one suppporting representation for this whole patch.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackRefToExistingDataset(gsoap_eml2_3::resqml22__IndexableElement elementKind, ULONG64 elementCount, const std::string& elementDataset,
			LONG64 nullValue, EML2_NS::AbstractHdfProxy* proxy, const std::string& supportingRepDataset = "") = 0;

		/**   
		 * @copydoc AbstractRepresentation::getXyzPointCountOfPatch  
		 *
		 * @exception std::logic_error If the kind of the selected elements of this patch is not node (non 
		 * 							   pairwise) or if the kind of the left part of the pairs of elements is
		 * 							    not node (pairwise case).
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(unsigned int patchIndex) const override;

		/** Please do note use : not implemented yet. */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(unsigned int patchIndex, double* xyzPoints) const override;

		DLL_IMPORT_OR_EXPORT virtual unsigned int getPatchCount() const override = 0;

		/**
		 * Pushes back a representation which is one of the support of this sub-representation. And push
		 * back this sub-representation as a subrepresentation of the representation as well.
		 *
		 * @exception	std::invalid_argument	If @p supportingRep is nullptr.
		 *
		 * @param [in]	supportingRep	If representation to set as a supporting representation of this
		 * 								sub-representation.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackSupportingRepresentation(AbstractRepresentation * supportingRep);

		/**
		 * Gets the count of supporting representations of this sub-representation.
		 *
		 * @returns	The supporting representation count if successful, otherwise 0 if no supporting
		 * 			representation is associated to this sub-representation. This should not happened in
		 * 			a serialized state but can occur after creating a sub-representation and before
		 * 			associating any supporting representation to it.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getSupportingRepresentationCount() const = 0;

		/**
		 * Gets the supporting representation located at a specific index of this sub-representation.
		 *
		 * @exception	std::invalid_argument	If no supporting representation is already associated to
		 * 										this sub-representation.
		 * @exception	std::out_of_range	 	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the supporting representation we look for.
		 *
		 * @returns	The supporting representation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT AbstractRepresentation* getSupportingRepresentation(unsigned int index) const;

		/**
		 * Gets the data object reference of the supporting representation located at a specific index
		 * of this sub-representation.
		 *
		 * @exception	std::invalid_argument	If no supporting representation is already associated to
		 * 										this sub-representation.
		 * @exception	std::out_of_range	 	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the supporting representation we look for.
		 *
		 * @returns	The data object reference of the supporting representation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getSupportingRepresentationDor(unsigned int index) const = 0;

		/** The standard XML tag without XML namespace for serializing this data object */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

		/** Loads target relationships */
		void loadTargetRelationships() final;

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
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

		/**
		 * Pushes a back XML supporting representation
		 *
		 * @param 	supportingRep	The supporting rep.
		 */
		virtual void pushBackXmlSupportingRepresentation(AbstractRepresentation const * supportingRep) = 0;
	};
}
