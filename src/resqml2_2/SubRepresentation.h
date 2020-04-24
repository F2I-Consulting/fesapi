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

#include "../resqml2/SubRepresentation.h"

namespace RESQML2_2_NS
{
	/** A sub representation. */
	class SubRepresentation final : public RESQML2_NS::SubRepresentation
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT SubRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject):
			RESQML2_NS::SubRepresentation(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context. This instance is not linked to any
		 * interpretation.
		 *
		 * @param [in,out]	repo 	The repo where the underlying gsoap proxy will be created.
		 * @param 		  	guid 	The guid to set to this instance.
		 * @param 		  	title	A title for the instance to create.
		 */
		SubRepresentation(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class in a gsoap context. This instance must be linked to an
		 * interpretation.
		 *
		 * @param [in,out]	interp	The interpretation the instance represents.
		 * @param 		  	guid  	The guid to set to this instance.
		 * @param 		  	title 	A title for the instance to create.
		 */
		SubRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
                const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		SubRepresentation(gsoap_eml2_3::_resqml22__SubRepresentation* fromGsoap) : RESQML2_NS::SubRepresentation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~SubRepresentation() {}

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;

		/**
		* Get the kind of the selected elements for a particular patch of this subrepresentation.
		*/
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractRepresentation::indexableElement getElementKindOfPatch(unsigned int patchIndex, unsigned int elementIndicesIndex) const final;

		/**
		* Get the count of the selected elements for a particular patch of this subrepresentation.
		*/
		DLL_IMPORT_OR_EXPORT ULONG64 getElementCountOfPatch(unsigned int patchIndex) const final;

		/**
		* Get the indices of the selected elements in the supporting representation for a particular patch of this subrepresentation.
		* @param	elementIndicesIndex	Must be equal to 0 if the element indices are not pairwise.
		* @param	elementIndices		This array must be preallocated with getElementCountOfPatch() size.
		*/
		DLL_IMPORT_OR_EXPORT void getElementIndicesOfPatch(unsigned int patchIndex, unsigned int elementIndicesIndex, ULONG64 * elementIndices) const final;

		/**
		* Get the indices of the supporting representations of the selected elements for a particular patch of this subrepresentation.
		* @param	supportingRepresentationIndices	This array must be preallocated with getElementCountOfPatch() size.
		*/
		DLL_IMPORT_OR_EXPORT void getSupportingRepresentationIndicesOfPatch(unsigned int patchIndex, short * supportingRepresentationIndices) const final;

		/**
		* Check if the element of a particular patch are pairwise or not.
		*/
		DLL_IMPORT_OR_EXPORT bool areElementIndicesPairwise(unsigned int patchIndex) const final;

		/**
		* Check if the element indices of a particular patch are based on a lattice or not.
		* @param elementIndicesIndex	In case of pairwise element, allow to select the first or second element indice of the pair.
		*/
		DLL_IMPORT_OR_EXPORT bool areElementIndicesBasedOnLattice(unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const final;

		DLL_IMPORT_OR_EXPORT LONG64 getLatticeElementIndicesStartValue(unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const;
		DLL_IMPORT_OR_EXPORT unsigned int getLatticeElementIndicesDimensionCount(unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const final;
		DLL_IMPORT_OR_EXPORT LONG64 getLatticeElementIndicesOffsetValue(unsigned int latticeDimensionIndex, unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const final;
		DLL_IMPORT_OR_EXPORT ULONG64 getLatticeElementIndicesOffsetCount(unsigned int latticeDimensionIndex, unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const final;

		using RESQML2_NS::SubRepresentation::pushBackSubRepresentationPatch;

		/**
		* Push back a new patch in the subrepresentation which is based on a lattice definition.
		* @param elementKind						The kind of (indexable) elements which constitutes the subrepresentation.
		* @param elementCountInSlowestDimension		Commonly in K dimensionn.
		* @param elementCountInMiddleDimension		Commonly in J dimensionn.
		* @param elementCountInFastestDimension		Commonly in I dimension.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement elementKind, ULONG64 originIndex,
			unsigned int elementCountInSlowestDimension,
			unsigned int elementCountInMiddleDimension,
			unsigned int elementCountInFastestDimension) final;

		/**
		* Push back a new patch in the subrepresentation which is constituted by means of pairwise elements.
		* @param elementKind0		The kind of (indexable) elements which constitutes the first part of the pair of elements of the subrepresentation.
		* @param elementKind1		The kind of (indexable) elements which constitutes the second part of the pair of elements of the subrepresentation.
        * @param elementCount		The count of elements which constitutes the subrepresentation.
        * @param elementIndices0	The indices of the first part of the element pair in the supporting representation.
		* @param elementIndices1	The indices of the second part of the element pair in the supporting representation.
        * @param proxy				The HDF proxy where the numerical values (indices) are stored.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement elementKind0, gsoap_eml2_3::resqml22__IndexableElement elementKind1,
			ULONG64 elementCount,
			ULONG64 * elementIndices0, ULONG64 * elementIndices1,
			EML2_NS::AbstractHdfProxy* proxy) final;

		/**
		* Push back a new patch (without pairwise elements) in the subrepresentation where the indice values have not to be written in the HDF file.
		* The reason can be that the indice values already exist in an external file (only HDF5 for now) or that the writing of these indice values in the external file is defered in time.
		* @param	elementKind				The kind of (indexable) elements which constitutes the subrepresentation.
        * @param	elementCount			The count of elements which constitutes the subrepresentation.
		* @param	elementDataset			The HDF5 dataset name where the element indices are stored. If empty, the dataset will be named the same as the dataset naming convention of the fesapi :getHdfGroup() + "/subrepresentation_elementIndices0_patch" + patchIndex;
		* @param	nullValue				The null value which has been chosen in the referenced hdf dataset.
		* @param	hdfProxy				The HDF5 proxy where the values are already or will be stored.
		* @param	supportingRepDataset	The HDF5 dataset name where the element indices are stored. If empty, it won't be exported any information about suppporting rep relying on the fact there is only one suppporting rep for this whole patch.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackRefToExistingDataset(gsoap_eml2_3::resqml22__IndexableElement elementKind, ULONG64 elementCount, const std::string & elementDataset,
			LONG64 nullValue, EML2_NS::AbstractHdfProxy * proxy, const std::string & supportingRepDataset = "") final;

		/**
		 * Gets patch count
		 *
		 * @returns	The patch count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const final;

		/**
		 * Get the count of the supporting representations of this subrepresentation.
		 *
		 * @returns	The supporting representation count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getSupportingRepresentationCount() const final;

		/**
		 * Get the supporting representation dor located at a specific index of this subrepresentation.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	Null if it fails, else the supporting representation dor.
		 */
		COMMON_NS::DataObjectReference getSupportingRepresentationDor(unsigned int index) const final;

	private:

		/**
		 * Initializes this object
		 *
		 * @param [in,out]	repo 	The repo where the underlying gsoap proxy will be created.
		 * @param 		  	guid 	The guid to set to this instance.
		 * @param 		  	title	A title for the instance to init.
		 */
		void init(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title);

		/**
		 * Gets specialized gsoap proxy
		 *
		 * @returns	Null if it fails, else the specialized gsoap proxy.
		 */
		gsoap_eml2_3::_resqml22__SubRepresentation* getSpecializedGsoapProxy() const;

		/**
		* Get a patch of the current subrepresentation at a particluar index.
		*/
		gsoap_eml2_3::resqml22__SubRepresentationPatch* getSubRepresentationPatch(unsigned int index) const;

		/**
		 * Push back a representation which is one of the support of this subrepresentation. And push
		 * back this representation as a subrepresenation of the representation as well.
		 *
		 * @param 	supportingRep	The supporting rep.
		 */
		void pushBackXmlSupportingRepresentation(RESQML2_NS::AbstractRepresentation const * supportingRep);
	};
}
