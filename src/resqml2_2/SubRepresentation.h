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
		 * 
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
		 * @brief	Creates an instance of this class in a gsoap context. This instance must be linked to
		 * 			an interpretation.
		 *
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The interpretation the instance represents.
		 * @param 	  	guid  	The guid to set to this instance.
		 * @param 	  	title 	A title for the instance to create.
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
		~SubRepresentation() = default;

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;

		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractRepresentation::indexableElement getElementKindOfPatch(unsigned int patchIndex, unsigned int elementIndicesIndex) const final;

		DLL_IMPORT_OR_EXPORT ULONG64 getElementCountOfPatch(unsigned int patchIndex) const final;

		DLL_IMPORT_OR_EXPORT void getElementIndicesOfPatch(unsigned int patchIndex, unsigned int elementIndicesIndex, ULONG64 * elementIndices) const final;

		DLL_IMPORT_OR_EXPORT void getSupportingRepresentationIndicesOfPatch(unsigned int patchIndex, short * supportingRepresentationIndices) const final;

		DLL_IMPORT_OR_EXPORT bool areElementIndicesPairwise(unsigned int patchIndex) const final;

		DLL_IMPORT_OR_EXPORT bool areElementIndicesBasedOnLattice(unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const final;

		DLL_IMPORT_OR_EXPORT LONG64 getLatticeElementIndicesStartValue(unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const;
		DLL_IMPORT_OR_EXPORT unsigned int getLatticeElementIndicesDimensionCount(unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const final;
		DLL_IMPORT_OR_EXPORT LONG64 getLatticeElementIndicesOffsetValue(unsigned int latticeDimensionIndex, unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const final;
		DLL_IMPORT_OR_EXPORT ULONG64 getLatticeElementIndicesOffsetCount(unsigned int latticeDimensionIndex, unsigned int patchIndex, unsigned int elementIndicesIndex = 0) const final;

		using RESQML2_NS::SubRepresentation::pushBackSubRepresentationPatch;

		DLL_IMPORT_OR_EXPORT void pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement elementKind, ULONG64 originIndex,
			unsigned int elementCountInSlowestDimension,
			unsigned int elementCountInMiddleDimension,
			unsigned int elementCountInFastestDimension) final;

		DLL_IMPORT_OR_EXPORT void pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement elementKind0, gsoap_eml2_3::resqml22__IndexableElement elementKind1,
			ULONG64 elementCount,
			ULONG64 * elementIndices0, ULONG64 * elementIndices1,
			EML2_NS::AbstractHdfProxy* proxy) final;

		DLL_IMPORT_OR_EXPORT void pushBackRefToExistingDataset(gsoap_eml2_3::resqml22__IndexableElement elementKind, ULONG64 elementCount, const std::string & elementDataset,
			LONG64 nullValue, EML2_NS::AbstractHdfProxy * proxy, const std::string & supportingRepDataset = "") final;

		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const final;

		DLL_IMPORT_OR_EXPORT unsigned int getSupportingRepresentationCount() const final;

		COMMON_NS::DataObjectReference getSupportingRepresentationDor(unsigned int index) const final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

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
