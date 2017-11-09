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

#include "resqml2/SubRepresentation.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT SubRepresentation : public resqml2::SubRepresentation
	{
	private:
		/*
		* @param soapContext	The soap context where the underlying gsoap proxy will be created.
		* @param guid			The guid to set to this instance.
		* @param title			A title for the instance to init.
		*/
		void init(soap* soapContext, const std::string & guid, const std::string & title);

		gsoap_resqml2_0_1::_resqml2__SubRepresentation* getSpecializedGsoapProxy() const;

		/**
		* Get a patch of the current subrepresentation at a particluar index.
		*/
		gsoap_resqml2_0_1::resqml2__SubRepresentationPatch* getSubRepresentationPatch(const unsigned int & index) const;

		/**
		* Push back a representation which is one of the support of this subrepresentation.
		* And push back this representation as a subrepresenation of the representation as well.
		*/
		void pushBackXmlSupportingRepresentation(resqml2::AbstractRepresentation * supportingRep);

		class DiscreteProperty* getSupportingRepresentationIndicesDiscretePropOfPatch(const unsigned int & patchIndex) const;

	public:

		/**
		* Only to be used in partial transfer context
		*/
		SubRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject):
			resqml2::SubRepresentation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context. This instance is not linked to any interpretation.
		* @param soapContext	The soap context where the underlying gsoap proxy will be created.
		* @param guid			The guid to set to this instance.
		* @param title			A title for the instance to create.
		*/
		SubRepresentation(soap* soapContext, const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class in a gsoap context. This instance must be linked to an interpretation.
		* @param interp	The interpretation the instance represents.
		* @param guid	The guid to set to this instance.
		* @param title	A title for the instance to create.
		*/
		SubRepresentation(resqml2::AbstractFeatureInterpretation* interp,
                const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		SubRepresentation(gsoap_resqml2_0_1::_resqml2__SubRepresentation* fromGsoap) : resqml2::SubRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~SubRepresentation() {}

		std::string getHdfProxyUuid() const;

		/**
		* Get the kind of the selected elements for a particular patch of this subrepresentation.
		*/
		resqml2::AbstractRepresentation::indexableElement getElementKindOfPatch(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex) const;

		/**
		* Get the count of the selected elements for a particular patch of this subrepresentation.
		*/
		ULONG64 getElementCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get the indices of the selected elements in the supporting representation for a particular patch of this subrepresentation.
		* @param	elementIndicesIndex	Must be equal to 0 if the element indices are not pairwise.
		* @param	elementIndices		This array must be preallocated with getElementCountOfPatch() size.
		*/
		void getElementIndicesOfPatch(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex, ULONG64 * elementIndices) const;

		/**
		* Get the indices of the supporting representations of the selected elements for a particular patch of this subrepresentation.
		* @param	supportingRepresentationIndices	This array must be preallocated with getElementCountOfPatch() size.
		*/
		void getSupportingRepresentationIndicesOfPatch(const unsigned int & patchIndex, short * supportingRepresentationIndices) const;

		/**
		* Check if the element of a particular patch are pairwise or not.
		*/
		bool areElementIndicesPairwise(const unsigned int & patchIndex) const;

		/**
		* Check if the element indices of a particular patch are based on a lattice or not.
		* @param elementIndicesIndex	In case of pairwise element, allow to select the first or second element indice of the pair.
		*/
		bool areElementIndicesBasedOnLattice(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const;

		LONG64 getLatticeElementIndicesStartValue(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const;
		unsigned int getLatticeElementIndicesDimensionCount(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const;
		LONG64 getLatticeElementIndicesOffsetValue(const unsigned int & latticeDimensionIndex, const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const;
		ULONG64 getLatticeElementIndicesOffsetCount(const unsigned int & latticeDimensionIndex, const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const;

		/**
		* Push back a new patch in the subrepresentation which is based on a lattice definition.
		* @param elementKind						The kind of (indexable) elements which constitutes the subrepresentation.
		* @param elementCountInSlowestDimension		Commonly in K dimensionn.
		* @param elementCountInMiddleDimension		Commonly in J dimensionn.
		* @param elementCountInFastestDimension		Commonly in I dimension.
		*/
		void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind, const ULONG64 & originIndex, 
			const unsigned int & elementCountInSlowestDimension,
			const unsigned int & elementCountInMiddleDimension,
			const unsigned int & elementCountInFastestDimension);

		/**
		* Push back a new patch in the subrepresentation.
		* @param	elementKind				The kind of (indexable) elements which constitutes the subrepresentation.
        * @param	elementCount			The count of elements which constitutes the subrepresentation.
        * @param	elementIndices			The indices of the elements of the instance in the supporting representation.
        * @param	proxy					The HDF proxy where the numerical values (indices) are stored.
		* @param	supportingRepIndices	The indices of the supporting represenation for each elment in the supporting representation. The count must be elementCount.
		*/
		void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind, const ULONG64 & elementCount, ULONG64 * elementIndices, common::AbstractHdfProxy* proxy, short * supportingRepIndices = nullptr);

		/**
		* Push back a new patch in the subrepresentation which is constituted by means of pairwise elements.
		* @param elementKind0		The kind of (indexable) elements which constitutes the first part of the pair of elements of the subrepresentation.
		* @param elementKind1		The kind of (indexable) elements which constitutes the second part of the pair of elements of the subrepresentation.
        * @param elementCount		The count of elements which constitutes the subrepresentation.
        * @param elementIndices0	The indices of the first part of the element pair in the supporting representation.
		* @param elementIndices1	The indices of the second part of the element pair in the supporting representation.
        * @param proxy				The HDF proxy where the numerical values (indices) are stored.
		*/
		void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind0, const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind1,
			const ULONG64 & elementCount,
			ULONG64 * elementIndices0, ULONG64 * elementIndices1,
			common::AbstractHdfProxy* proxy);

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
		void pushBackRefToExistingDataset(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind, const ULONG64 & elementCount, const std::string & elementDataset,
			const LONG64 & nullValue, common::AbstractHdfProxy * proxy, const std::string & supportingRepDataset = "");

		unsigned int getPatchCount() const;

		/**
		* Get the count of the supporting representations of this subrepresentation.
		*/
		unsigned int getSupportingRepresentationCount() const;

		/**
		* Get the supporting representation dor located at a specific index of this subrepresentation.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getSupportingRepresentationDor(unsigned int index) const;
	};
}
