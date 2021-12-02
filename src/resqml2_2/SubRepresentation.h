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
		 * @param [in,out]	repo 		The repo where the underlying gsoap proxy will be created.
		 * @param 		  	guid 		The guid to set to this instance.
		 * @param 		  	title		A title for the instance to create.
		 * @param 		  	elementKind	The indexable element which will be by default used for selecting the subrepresentation of a supporting representation.
		 */
		SubRepresentation(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title, gsoap_eml2_3::eml23__IndexableElement elementKind);

		/**
		 * @brief	Creates an instance of this class in a gsoap context. This instance must be linked to
		 * 			an interpretation.
		 *
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp		The interpretation the instance represents.
		 * @param 	  	guid  		The guid to set to this instance.
		 * @param 	  	title 		A title for the instance to create.
		 * @param 		elementKind	The indexable element which will be by default used for selecting the subrepresentation of a supporting representation.
		 */
		SubRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
                const std::string & guid, const std::string & title, gsoap_eml2_3::eml23__IndexableElement elementKind);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		SubRepresentation(gsoap_eml2_3::_resqml22__SubRepresentation* fromGsoap) : RESQML2_NS::SubRepresentation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~SubRepresentation() = default;

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;

		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__IndexableElement getElementKind() const final { return getSpecializedGsoapProxy()->IndexableElement; }

		DLL_IMPORT_OR_EXPORT uint64_t getElementCountOfPatch(uint64_t patchIndex) const final;

		DLL_IMPORT_OR_EXPORT int64_t getElementIndicesOfPatch(uint64_t patchIndex, int64_t* elementIndices) const final;

		DLL_IMPORT_OR_EXPORT bool areElementIndicesBasedOnLattice(uint64_t patchIndex) const final;

		DLL_IMPORT_OR_EXPORT int64_t getLatticeElementIndicesStartValue(uint64_t patchIndex) const;
		DLL_IMPORT_OR_EXPORT uint64_t getLatticeElementIndicesDimensionCount(uint64_t patchIndex) const final;
		DLL_IMPORT_OR_EXPORT int64_t getLatticeElementIndicesOffsetValue(unsigned int latticeDimensionIndex, uint64_t patchIndex) const final;
		DLL_IMPORT_OR_EXPORT uint64_t getLatticeElementIndicesOffsetCount(unsigned int latticeDimensionIndex, uint64_t patchIndex) const final;

		DLL_IMPORT_OR_EXPORT void pushBackSubRepresentationPatch(uint64_t originIndex,
			unsigned int elementCountInSlowestDimension,
			unsigned int elementCountInMiddleDimension,
			unsigned int elementCountInFastestDimension, RESQML2_NS::AbstractIjkGridRepresentation* ijkGrid) final;

		DLL_IMPORT_OR_EXPORT void pushBackSubRepresentationPatch(uint64_t elementCount, int64_t* elementIndices,
			RESQML2_NS::AbstractRepresentation* supportingRep, EML2_NS::AbstractHdfProxy* proxy = nullptr) final;

		DLL_IMPORT_OR_EXPORT void pushBackRefToExistingDataset(uint64_t elementCount, const std::string& elementDataset,
			int64_t nullValue, RESQML2_NS::AbstractRepresentation* supportingRep, EML2_NS::AbstractHdfProxy* proxy = nullptr) final;

		DLL_IMPORT_OR_EXPORT uint64_t getPatchCount() const final;

		COMMON_NS::DataObjectReference getSupportingRepresentationOfPatchDor(uint64_t patchIndex = 0) const final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "resqml22";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

		/** Loads target relationships */
		void loadTargetRelationships() final;

	private:

		/**
		 * Initializes this object
		 *
		 * @param [in,out]	repo 		The repo where the underlying gsoap proxy will be created.
		 * @param 		  	guid 		The guid to set to this instance.
		 * @param 		  	title		A title for the instance to init.
		 * @param 		  	elementKind	The indexable element which will be by default used for selecting the subrepresentation of a supporting representation.
		 */
		void init(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title, gsoap_eml2_3::eml23__IndexableElement elementKind);

		/**
		 * Gets specialized gsoap proxy
		 *
		 * @returns	Null if it fails, else the specialized gsoap proxy.
		 */
		gsoap_eml2_3::_resqml22__SubRepresentation* getSpecializedGsoapProxy() const;

		/**
		* Get a patch of the current subrepresentation at a particluar index.
		*/
		gsoap_eml2_3::resqml22__SubRepresentationPatch* getSubRepresentationPatch(uint64_t index) const;
	};
}
