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

#include "../resqml2/SealedVolumeFrameworkRepresentation.h"

namespace RESQML2_0_1_NS
{
	/** A sealed volume framework representation. */
	class SealedVolumeFrameworkRepresentation final : public RESQML2_NS::SealedVolumeFrameworkRepresentation
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT SealedVolumeFrameworkRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::SealedVolumeFrameworkRepresentation(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt> or <tt>ssf == nullptr</tt>.
		 *
		 * @param [in]	interp	The Stratigraphic Column Rank Interpretation which the instance
		 * 						interprets.
		 * @param 	  	guid  	The guid to set to the representation. If empty then a new guid will be
		 * 						generated.
		 * @param 	  	title 	A title for the instance to create.
		 * @param [in]	ssf   	The Sealed Surface Framework which this instance is based on.
		 */
		SealedVolumeFrameworkRepresentation(RESQML2_NS::StratigraphicColumnRankInterpretation* interp,
			const std::string & guid,
			const std::string & title,
			RESQML2_NS::SealedSurfaceFrameworkRepresentation* ssf);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		SealedVolumeFrameworkRepresentation(gsoap_resqml2_0_1::_resqml20__SealedVolumeFrameworkRepresentation* fromGsoap) : RESQML2_NS::SealedVolumeFrameworkRepresentation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~SealedVolumeFrameworkRepresentation() = default;

		DLL_IMPORT_OR_EXPORT void pushBackVolumeRegion(RESQML2_NS::StratigraphicUnitInterpretation * stratiUnitInterp,
			uint64_t externalShellFaceCount,
			unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide) final;

		DLL_IMPORT_OR_EXPORT void pushBackInternalShell(uint64_t regionIndex,
			uint64_t externalShellFaceCount,
			unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide) final;

		DLL_IMPORT_OR_EXPORT uint64_t getRegionCount() const final;

		DLL_IMPORT_OR_EXPORT uint64_t getInternalShellCount(uint64_t regionIndex) const final;

		DLL_IMPORT_OR_EXPORT uint64_t getFaceCountOfExternalShell(uint64_t regionIndex) const final;

		DLL_IMPORT_OR_EXPORT uint64_t getFaceCountOfInternalShell(uint64_t regionIndex, uint64_t internalShellIndex) const final;

		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractRepresentation* getRepOfExternalShellFace(uint64_t regionIndex, uint64_t faceIndex) final;

		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractRepresentation* getRepOfInternalShellFace(uint64_t regionIndex, uint64_t internalShellIndex, uint64_t faceIndex) final;

		DLL_IMPORT_OR_EXPORT uint64_t getRepPatchIndexOfExternalShellFace(uint64_t regionIndex, uint64_t faceIndex) final;

		DLL_IMPORT_OR_EXPORT uint64_t getRepPatchIndexOfInternalShellFace(uint64_t regionIndex, uint64_t internalShellIndex, uint64_t faceIndex) final;

		DLL_IMPORT_OR_EXPORT bool getSideFlagOfExternalShellFace(uint64_t regionIndex, uint64_t faceIndex) final;

		DLL_IMPORT_OR_EXPORT bool getSideFlagOfInternalShellFace(uint64_t regionIndex, uint64_t internalShellIndex, uint64_t faceIndex) final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "resqml20";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

	private:

		/**
		 * Creates volume shell
		 *
		 * @param 		  	shellFaceCount			 	Number of shell faces.
		 * @param [in,out]	faceRepresentationIndices	The face representation indices.
		 * @param [in,out]	faceRepPatchIndices		 	The face rep patch indices.
		 * @param [in,out]	faceSide				 	The face sides.
		 *
		 * @returns	Null if it fails, else the new volume shell.
		 */
		gsoap_resqml2_0_1::resqml20__VolumeShell* createVolumeShell(
			uint64_t shellFaceCount,
			unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide);

		/**
		 * Gets a region
		 *
		 * @param 	regionIndex	Zero-based index of the region.
		 *
		 * @returns	Null if it fails, else the region.
		 */
		gsoap_resqml2_0_1::resqml20__VolumeRegion* getRegion(uint64_t regionIndex) const;

		/**
		 * Gets region external shell
		 *
		 * @param 	regionIndex	Zero-based index of the region.
		 *
		 * @returns	Null if it fails, else the region external shell.
		 */
		gsoap_resqml2_0_1::resqml20__VolumeShell* getRegionExternalShell(uint64_t regionIndex) const;

		/**
		 * Gets region internal shell
		 *
		 * @param 	regionIndex		  	Zero-based index of the region.
		 * @param 	internalShellIndex	Zero-based index of the internal shell.
		 *
		 * @returns	Null if it fails, else the region internal shell.
		 */
		gsoap_resqml2_0_1::resqml20__VolumeShell* getRegionInternalShell(uint64_t regionIndex, uint64_t internalShellIndex) const;

		/**
		 * Gets region external shell face
		 *
		 * @param 	regionIndex	Zero-based index of the region.
		 * @param 	faceIndex  	Zero-based index of the face.
		 *
		 * @returns	Null if it fails, else the region external shell face.
		 */
		gsoap_resqml2_0_1::resqml20__OrientedMacroFace* getRegionExternalShellFace(uint64_t regionIndex, uint64_t faceIndex) const;

		/**
		 * Gets region internal shell face
		 *
		 * @param 	regionIndex		  	Zero-based index of the region.
		 * @param 	internalShellIndex	Zero-based index of the internal shell.
		 * @param 	faceIndex		  	Zero-based index of the face.
		 *
		 * @returns	Null if it fails, else the region internal shell face.
		 */
		gsoap_resqml2_0_1::resqml20__OrientedMacroFace* getRegionInternalShellFace(uint64_t regionIndex, uint64_t internalShellIndex, uint64_t faceIndex) const;

		COMMON_NS::DataObjectReference getSealedStructuralFrameworkDor() const final;

		COMMON_NS::DataObjectReference getStratiUnitInterpDor(uint64_t regionIndex) const final;

		/**
		 * Sets XML sealed surface framework
		 *
		 * @param [in,out]	ssf	If non-null, the ssf.
		 */
		void setXmlSealedSurfaceFramework(RESQML2_NS::SealedSurfaceFrameworkRepresentation* ssf) final;

		/**
		 * Sets XML interpretation of volume region
		 *
		 * @param 		  	regionIndex			Zero-based index of the region.
		 * @param [in,out]	stratiUnitInterp	If non-null, the strati unit interp.
		 */
		void setXmlInterpretationOfVolumeRegion(uint64_t regionIndex, RESQML2_NS::StratigraphicUnitInterpretation * stratiUnitInterp) final;
	};
}
