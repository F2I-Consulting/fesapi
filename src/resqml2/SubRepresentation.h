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

#include "resqml2/AbstractRepresentation.h"

namespace RESQML2_NS
{
	class SubRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		SubRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			RESQML2_NS::AbstractRepresentation(partialObject)
		{
		}

		SubRepresentation() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		SubRepresentation(gsoap_resqml2_0_1::_resqml2__SubRepresentation* fromGsoap) : RESQML2_NS::AbstractRepresentation(fromGsoap) {}

		virtual void pushBackXmlSupportingRepresentation(AbstractRepresentation const * supportingRep) = 0;

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~SubRepresentation() {}
        
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const {return XML_TAG;}

		/**
		* Get the kind of the selected elements for a particular patch of this subrepresentation.
		*/
		DLL_IMPORT_OR_EXPORT virtual indexableElement getElementKindOfPatch(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex) const = 0;

		/**
		* Get the count of the selected elements for a particular patch of this subrepresentation.
		*/
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getElementCountOfPatch(const unsigned int & patchIndex) const = 0;

		/**
		* Get the indices of the selected elements for a particular patch of this subrepresentation.
		* @param	elementIndicesIndex	Must be equal to 0 if the element indices are not pairwise.
		* @param	elementIndices		This array must be preallocated with getElementCountOfPatch() size.
		*/
		DLL_IMPORT_OR_EXPORT virtual void getElementIndicesOfPatch(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex, ULONG64 * elementIndices) const = 0;

		/**
		* Get the indices of the supporting representations of the selected elements for a particular patch of this subrepresentation.
		* @param	supportingRepresentationIndices	This array must be preallocated with getElementCountOfPatch() size.
		*/
		DLL_IMPORT_OR_EXPORT virtual void getSupportingRepresentationIndicesOfPatch(const unsigned int & patchIndex, short * supportingRepresentationIndices) const = 0;

		/**
		* Check if the element of a particular patch are pairwise or not.
		*/
		DLL_IMPORT_OR_EXPORT virtual bool areElementIndicesPairwise(const unsigned int & patchIndex) const = 0;

		/**
		* Check if the element indices of a particular patch are based on a lattice or not.
		* @param elementIndicesIndex	In case of pairwise element, allow to select the first or second element indice of the pair.
		*/
		DLL_IMPORT_OR_EXPORT virtual bool areElementIndicesBasedOnLattice(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const = 0;

		DLL_IMPORT_OR_EXPORT virtual LONG64 getLatticeElementIndicesStartValue(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const = 0;
		DLL_IMPORT_OR_EXPORT virtual unsigned int getLatticeElementIndicesDimensionCount(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const = 0;
		DLL_IMPORT_OR_EXPORT virtual LONG64 getLatticeElementIndicesOffsetValue(const unsigned int & latticeDimensionIndex, const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const = 0;
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getLatticeElementIndicesOffsetCount(const unsigned int & latticeDimensionIndex, const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const = 0;

		/**
		* Push back a new patch in the subrepresentation which is based on a lattice definition.
		* @param elementKind						The kind of (indexable) elements which constitutes the subrepresentation.
		* @param elementCountInSlowestDimension		Commonly in K dimensionn.
		* @param elementCountInMiddleDimension		Commonly in J dimensionn.
		* @param elementCountInFastestDimension		Commonly in I dimension.
		*/
		DLL_IMPORT_OR_EXPORT virtual void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind, const ULONG64 & originIndex,
			const unsigned int & elementCountInSlowestDimension,
			const unsigned int & elementCountInMiddleDimension,
			const unsigned int & elementCountInFastestDimension) = 0;

		/**
		* Push back a new patch in the subrepresentation.
		* @param	elementKind				The kind of (indexable) elements which constitutes the subrepresentation.
        * @param	elementCount			The count of elements which constitutes the subrepresentation.
        * @param	elementIndices			The indices of the elements of the instance in the supporting representation.
        * @param	proxy					The HDF proxy where the numerical values (indices) are stored.
		* @param	supportingRepIndices	The indices of the supporting represenation for each elment in the supporting representation. The count must be elementCount.
		*/
		DLL_IMPORT_OR_EXPORT virtual void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind, const ULONG64 & elementCount, ULONG64 * elementIndices, COMMON_NS::AbstractHdfProxy* proxy, short * supportingRepIndices = nullptr) = 0;

		/**
		* Push back a new patch in the subrepresentation which is constituted by means of pairwise elements.
		* @param elementKind0		The kind of (indexable) elements which constitutes the first part of the pair of elements of the subrepresentation.
		* @param elementKind1		The kind of (indexable) elements which constitutes the second part of the pair of elements of the subrepresentation.
        * @param elementCount		The count of elements which constitutes the subrepresentation.
        * @param elementIndices0	The indices of the first part of the element pair in the supporting representation.
		* @param elementIndices1	The indices of the second part of the element pair in the supporting representation.
        * @param proxy				The HDF proxy where the numerical values (indices) are stored.
		*/
		DLL_IMPORT_OR_EXPORT virtual void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind0, const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind1,
			const ULONG64 & elementCount,
			ULONG64 * elementIndices0, ULONG64 * elementIndices1,
			COMMON_NS::AbstractHdfProxy* proxy) = 0;

		/**
		* Push back a new patch (without pairwise elements) in the subrepresentation where the indice values have not to be written in the HDF file.
		* The reason can be that the indice values already exist in an external file (only HDF5 for now) or that the writing of these indice values in the external file is defered in time.
		* @param	elementKind				The kind of (indexable) elements which constitutes the subrepresentation.
        * @param	elementCount			The count of elements which constitutes the subrepresentation.
		* @param	elementDataset			The HDF5 dataset name where the element indices are stored. If empty, the dataset will be named the same as the dataset naming convention of the fesapi :"/RESQML/" + subRep->uuid + "/subrepresentation_elementIndices0_patch" + patchIndex;
		* @param	nullValue				The null value which has been chosen in the referenced hdf dataset.
		* @param	hdfProxy				The HDF5 proxy where the values are already or will be stored.
		* @param	supportingRepDataset	The HDF5 dataset name where the element indices are stored. If empty, it won't be exported any information about suppporting rep relying on the fact there is only one suppporting rep for this whole patch.
		*/
		DLL_IMPORT_OR_EXPORT virtual void pushBackRefToExistingDataset(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind, const ULONG64 & elementCount, const std::string & elementDataset,
			const LONG64 & nullValue, COMMON_NS::AbstractHdfProxy * proxy, const std::string & supportingRepDataset = "") = 0;

		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		DLL_IMPORT_OR_EXPORT virtual unsigned int getPatchCount() const = 0;

		/**
		* Push back a representation which is one of the support of this representation.
		* And push back this representation as a subrepresentation of the representation as well.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackSupportingRepresentation(AbstractRepresentation * supportingRep);

		/**
		* Get the count of the supporting representations of this subrepresentation.
		*/
		DLL_IMPORT_OR_EXPORT virtual unsigned int getSupportingRepresentationCount() const = 0;

		/**
		* Get the supporting representation located at a specific index of this subrepresentation.
		*/
		DLL_IMPORT_OR_EXPORT AbstractRepresentation* getSupportingRepresentation(unsigned int index) const;

		/**
		* Get the supporting representation dor located at a specific index of this subrepresentation.
		*/
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::eml20__DataObjectReference* getSupportingRepresentationDor(unsigned int index) const = 0;

		/**
		* Get one of the supporting representation uuid of this subrepresentation.
		*/
		DLL_IMPORT_OR_EXPORT std::string getSupportingRepresentationUuid(unsigned int index) const;

		/**
		* Get one of the supporting representation title of this subrepresentation.
		*/
		DLL_IMPORT_OR_EXPORT std::string getSupportingRepresentationTitle(unsigned int index) const;

		/**
		* Get one of the supporting representation content type of this subrepresentation.
		* It is assumed by fesapi taht all supporting representations must have the same type.
		* This is a current limitation of fesapi compared the Resqml datamodel.
		*/
		DLL_IMPORT_OR_EXPORT std::string getSupportingRepresentationContentType() const;

		void loadTargetRelationships();
	};
}
