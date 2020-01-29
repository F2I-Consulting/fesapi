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

/** . */
namespace RESQML2_NS
{
	/**
	 * An ordered list of indexable elements and/or indexable element pairs of an existing
	 * representation. Because the representation concepts of topology, geometry, and property
	 * values are separate in RESQML, it is now possible to select a range of nodes, edges, faces,
	 * or volumes (cell) indices from the topological support of an existing representation to
	 * define a sub-representation. A sub-representation may describe a different feature
	 * interpretation using the same geometry or property as the "parent" representation. In this
	 * case, the only information exchanged is a set of potentially non-consecutive indices of the
	 * topological support of the representation.
	 */
	class SubRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT SubRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			RESQML2_NS::AbstractRepresentation(partialObject)
		{
		}

		/** Default constructor */
		SubRepresentation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		SubRepresentation(gsoap_resqml2_0_1::_resqml20__SubRepresentation* fromGsoap) : RESQML2_NS::AbstractRepresentation(fromGsoap) {}

		/**
		 * Pushes a back XML supporting representation
		 *
		 * @param 	supportingRep	The supporting rep.
		 */
		virtual void pushBackXmlSupportingRepresentation(AbstractRepresentation const * supportingRep) = 0;

	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~SubRepresentation() {}

		/**
		 * Get the kind of the selected elements for a particular patch of this subrepresentation.
		 *
		 * @param 	patchIndex		   	Zero-based index of the patch.
		 * @param 	elementIndicesIndex	Zero-based index of the element indices.
		 *
		 * @returns	The element kind of patch.
		 */
		DLL_IMPORT_OR_EXPORT virtual indexableElement getElementKindOfPatch(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex) const = 0;

		/**
		 * Get the count of the selected elements for a particular patch of this subrepresentation.
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	The element count of patch.
		 */
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getElementCountOfPatch(const unsigned int & patchIndex) const = 0;

		/**
		 * Get the indices of the selected elements for a particular patch of this subrepresentation.
		 *
		 * @param 		  	patchIndex		   	Zero-based index of the patch.
		 * @param 		  	elementIndicesIndex	Must be equal to 0 if the element indices are not
		 * 										pairwise.
		 * @param [in,out]	elementIndices	   	This array must be preallocated with
		 * 										getElementCountOfPatch() size.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getElementIndicesOfPatch(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex, ULONG64 * elementIndices) const = 0;

		/**
		 * Get the indices of the supporting representations of the selected elements for a particular
		 * patch of this subrepresentation.
		 *
		 * @param 		  	patchIndex					   	Zero-based index of the patch.
		 * @param [in,out]	supportingRepresentationIndices	This array must be preallocated with
		 * 													getElementCountOfPatch() size.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getSupportingRepresentationIndicesOfPatch(const unsigned int & patchIndex, short * supportingRepresentationIndices) const = 0;

		/**
		 * Check if the element of a particular patch are pairwise or not.
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	True if element indices pairwise, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool areElementIndicesPairwise(const unsigned int & patchIndex) const = 0;

		/**
		 * Check if the element indices of a particular patch are based on a lattice or not.
		 *
		 * @param 	patchIndex		   	Zero-based index of the patch.
		 * @param 	elementIndicesIndex	(Optional) In case of pairwise element, allow to select the first
		 * 								or second element indice of the pair.
		 *
		 * @returns	True if element indices based on lattice, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool areElementIndicesBasedOnLattice(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const = 0;

		/**
		 * Gets lattice element indices start value
		 *
		 * @param 	patchIndex		   	Zero-based index of the patch.
		 * @param 	elementIndicesIndex	(Optional) Zero-based index of the element indices.
		 *
		 * @returns	The lattice element indices start value.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getLatticeElementIndicesStartValue(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const = 0;

		/**
		 * Gets lattice element indices dimension count
		 *
		 * @param 	patchIndex		   	Zero-based index of the patch.
		 * @param 	elementIndicesIndex	(Optional) Zero-based index of the element indices.
		 *
		 * @returns	The lattice element indices dimension count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getLatticeElementIndicesDimensionCount(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const = 0;

		/**
		 * Gets lattice element indices offset value
		 *
		 * @param 	latticeDimensionIndex	Zero-based index of the lattice dimension.
		 * @param 	patchIndex			 	Zero-based index of the patch.
		 * @param 	elementIndicesIndex  	(Optional) Zero-based index of the element indices.
		 *
		 * @returns	The lattice element indices offset value.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getLatticeElementIndicesOffsetValue(const unsigned int & latticeDimensionIndex, const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const = 0;

		/**
		 * Gets lattice element indices offset count
		 *
		 * @param 	latticeDimensionIndex	Zero-based index of the lattice dimension.
		 * @param 	patchIndex			 	Zero-based index of the patch.
		 * @param 	elementIndicesIndex  	(Optional) Zero-based index of the element indices.
		 *
		 * @returns	The lattice element indices offset count.
		 */
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getLatticeElementIndicesOffsetCount(const unsigned int & latticeDimensionIndex, const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const = 0;

		/**
		 * Push back a new patch in the subrepresentation which is based on a lattice definition.
		 *
		 * @param 	elementKind					  	The kind of (indexable) elements which constitutes
		 * 											the subrepresentation.
		 * @param 	originIndex					  	Zero-based index of the origin.
		 * @param 	elementCountInSlowestDimension	Commonly in K dimensionn.
		 * @param 	elementCountInMiddleDimension 	Commonly in J dimensionn.
		 * @param 	elementCountInFastestDimension	Commonly in I dimension.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml20__IndexableElements & elementKind, const ULONG64 & originIndex,
			const unsigned int & elementCountInSlowestDimension,
			const unsigned int & elementCountInMiddleDimension,
			const unsigned int & elementCountInFastestDimension) = 0;

		/**
		 * Push back a new patch in the subrepresentation.
		 *
		 * @param 		  	elementKind				The kind of (indexable) elements which constitutes
		 * 											the subrepresentation.
		 * @param 		  	elementCount			The count of elements which constitutes the
		 * 											subrepresentation.
		 * @param [in,out]	elementIndices			The indices of the elements of the instance in the
		 * 											supporting representation.
		 * @param [in,out]	proxy					The HDF proxy where the numerical values (indices)
		 * 											are stored.
		 * @param [in,out]	supportingRepIndices	(Optional) The indices of the supporting
		 * 											represenation for each elment in the supporting
		 * 											representation. The count must be elementCount.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml20__IndexableElements & elementKind, const ULONG64 & elementCount, ULONG64 * elementIndices, COMMON_NS::AbstractHdfProxy* proxy, short * supportingRepIndices = nullptr) = 0;

		/**
		 * Push back a new patch in the subrepresentation which is constituted by means of pairwise
		 * elements.
		 *
		 * @param 		  	elementKind0   	The kind of (indexable) elements which constitutes the first
		 * 									part of the pair of elements of the subrepresentation.
		 * @param 		  	elementKind1   	The kind of (indexable) elements which constitutes the second
		 * 									part of the pair of elements of the subrepresentation.
		 * @param 		  	elementCount   	The count of elements which constitutes the subrepresentation.
		 * @param [in,out]	elementIndices0	The indices of the first part of the element pair in the
		 * 									supporting representation.
		 * @param [in,out]	elementIndices1	The indices of the second part of the element pair in the
		 * 									supporting representation.
		 * @param [in,out]	proxy		   	The HDF proxy where the numerical values (indices) are stored.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml20__IndexableElements & elementKind0, const gsoap_resqml2_0_1::resqml20__IndexableElements & elementKind1,
			const ULONG64 & elementCount,
			ULONG64 * elementIndices0, ULONG64 * elementIndices1,
			COMMON_NS::AbstractHdfProxy* proxy) = 0;

		/**
		 * Push back a new patch (without pairwise elements) in the subrepresentation where the indice
		 * values have not to be written in the HDF file. The reason can be that the indice values
		 * already exist in an external file (only HDF5 for now) or that the writing of these indice
		 * values in the external file is defered in time.
		 *
		 * @param 		  	elementKind				The kind of (indexable) elements which constitutes
		 * 											the subrepresentation.
		 * @param 		  	elementCount			The count of elements which constitutes the
		 * 											subrepresentation.
		 * @param 		  	elementDataset			The HDF5 dataset name where the element indices are
		 * 											stored. If empty, the dataset will be named the same as
		 * 											the dataset naming convention of the fesapi :"/RESQML/" +
		 * 											subRep->uuid + "/subrepresentation_elementIndices0_patch"
		 * 											+ patchIndex;
		 * @param 		  	nullValue				The null value which has been chosen in the
		 * 											referenced hdf dataset.
		 * @param [in,out]	proxy					The HDF5 proxy where the values are already or will
		 * 											be stored.
		 * @param 		  	supportingRepDataset	(Optional) The HDF5 dataset name where the element
		 * 											indices are stored. If empty, it won't be exported any
		 * 											information about suppporting rep relying on the fact
		 * 											there is only one suppporting rep for this whole patch.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackRefToExistingDataset(const gsoap_resqml2_0_1::resqml20__IndexableElements & elementKind, const ULONG64 & elementCount, const std::string & elementDataset,
			const LONG64 & nullValue, COMMON_NS::AbstractHdfProxy * proxy, const std::string & supportingRepDataset = "") = 0;

		/**
		 * Gets xyz point count of patch
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	The xyz point count of patch.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		 * Get all the XYZ points of a particular patch of this representation. XYZ points are given in
		 * the local CRS.
		 *
		 * @param 		  	patchIndex	Zero-based index of the patch.
		 * @param [in,out]	xyzPoints 	A linearized 2d array where the first (quickest) dimension is
		 * 								coordinate dimension (XYZ) and second dimension is vertex
		 * 								dimension. It must be pre allocated.
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		 * Gets patch count
		 *
		 * @returns	The patch count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getPatchCount() const = 0;

		/**
		 * Push back a representation which is one of the support of this representation. And push back
		 * this representation as a subrepresentation of the representation as well.
		 *
		 * @param [in,out]	supportingRep	If non-null, the supporting rep.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackSupportingRepresentation(AbstractRepresentation * supportingRep);

		/**
		 * Get the count of the supporting representations of this subrepresentation.
		 *
		 * @returns	The supporting representation count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getSupportingRepresentationCount() const = 0;

		/**
		 * Get the supporting representation located at a specific index of this subrepresentation.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	Null if it fails, else the supporting representation.
		 */
		DLL_IMPORT_OR_EXPORT AbstractRepresentation* getSupportingRepresentation(unsigned int index) const;

		/**
		 * Get the supporting representation dor located at a specific index of this subrepresentation.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	Null if it fails, else the supporting representation dor.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::eml20__DataObjectReference* getSupportingRepresentationDor(unsigned int index) const = 0;

		/**
		 * Get one of the supporting representation uuid of this subrepresentation.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The supporting representation uuid.
		 */
		DLL_IMPORT_OR_EXPORT std::string getSupportingRepresentationUuid(unsigned int index) const;

		/**
		 * Get one of the supporting representation title of this subrepresentation.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The supporting representation title.
		 */
		DLL_IMPORT_OR_EXPORT std::string getSupportingRepresentationTitle(unsigned int index) const;

		/**
		 * Get one of the supporting representation content type of this subrepresentation. It is
		 * assumed by fesapi taht all supporting representations must have the same type. This is a
		 * current limitation of fesapi compared the Resqml datamodel.
		 *
		 * @returns	The supporting representation content type.
		 */
		DLL_IMPORT_OR_EXPORT std::string getSupportingRepresentationContentType() const;

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

	private:
		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
