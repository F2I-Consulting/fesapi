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

namespace RESQML2_2_NS
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
		 * 							interprets.
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
		SealedVolumeFrameworkRepresentation(gsoap_eml2_3::_resqml22__SealedVolumeFrameworkRepresentation* fromGsoap) : RESQML2_NS::SealedVolumeFrameworkRepresentation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~SealedVolumeFrameworkRepresentation() {}

		DLL_IMPORT_OR_EXPORT void pushBackVolumeRegion(RESQML2_NS::StratigraphicUnitInterpretation * stratiUnitInterp,
			unsigned int externalShellFaceCount,
			unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide) final;

		DLL_IMPORT_OR_EXPORT void pushBackInternalShell(unsigned int regionIndex,
			unsigned int externalShellFaceCount,
			unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide) final;

		DLL_IMPORT_OR_EXPORT unsigned int getRegionCount() const final;

		DLL_IMPORT_OR_EXPORT unsigned int getInternalShellCount(unsigned int regionIndex) const final;

		DLL_IMPORT_OR_EXPORT unsigned int getFaceCountOfExternalShell(unsigned int regionIndex) const final;

		DLL_IMPORT_OR_EXPORT unsigned int getFaceCountOfInternalShell(unsigned int regionIndex, unsigned int internalShellIndex) const final;

		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractRepresentation* getRepOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const final;

		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractRepresentation* getRepOfInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const final;

		DLL_IMPORT_OR_EXPORT unsigned int getRepPatchIndexOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const final;

		DLL_IMPORT_OR_EXPORT unsigned int getRepPatchIndexOfInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const final;

		DLL_IMPORT_OR_EXPORT bool getSideFlagOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const final;

		DLL_IMPORT_OR_EXPORT bool getSideFlagOfInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const final;

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
		 * Creates volume shell
		 *
		 * @param 		  	shellFaceCount			 	Number of shell faces.
		 * @param [in,out]	faceRepresentationIndices	If non-null, the face representation indices.
		 * @param [in,out]	faceRepPatchIndices		 	If non-null, the face rep patch indices.
		 * @param [in,out]	faceSide				 	If non-null, true to face side.
		 *
		 * @returns	Null if it fails, else the new volume shell.
		 */
		gsoap_eml2_3::resqml22__VolumeShell* createVolumeShell(
			unsigned int shellFaceCount,
			unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide);

		/**
		 * Gets a region
		 *
		 * @param 	regionIndex	Zero-based index of the region.
		 *
		 * @returns	Null if it fails, else the region.
		 */
		gsoap_eml2_3::resqml22__VolumeRegion* getRegion(unsigned int regionIndex) const;

		/**
		 * Gets region external shell
		 *
		 * @param 	regionIndex	Zero-based index of the region.
		 *
		 * @returns	Null if it fails, else the region external shell.
		 */
		gsoap_eml2_3::resqml22__VolumeShell* getRegionExternalShell(unsigned int regionIndex) const;

		/**
		 * Gets region internal shell
		 *
		 * @param 	regionIndex		  	Zero-based index of the region.
		 * @param 	internalShellIndex	Zero-based index of the internal shell.
		 *
		 * @returns	Null if it fails, else the region internal shell.
		 */
		gsoap_eml2_3::resqml22__VolumeShell* getRegionInternalShell(unsigned int regionIndex, unsigned int internalShellIndex) const;

		/**
		 * Gets region external shell face
		 *
		 * @param 	regionIndex	Zero-based index of the region.
		 * @param 	faceIndex  	Zero-based index of the face.
		 *
		 * @returns	Null if it fails, else the region external shell face.
		 */
		gsoap_eml2_3::resqml22__OrientedMacroFace* getRegionExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const;

		/**
		 * Gets region internal shell face
		 *
		 * @param 	regionIndex		  	Zero-based index of the region.
		 * @param 	internalShellIndex	Zero-based index of the internal shell.
		 * @param 	faceIndex		  	Zero-based index of the face.
		 *
		 * @returns	Null if it fails, else the region internal shell face.
		 */
		gsoap_eml2_3::resqml22__OrientedMacroFace* getRegionInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const;

		COMMON_NS::DataObjectReference getSealedStructuralFrameworkDor() const final;

		COMMON_NS::DataObjectReference getStratiUnitInterpDor(unsigned int regionIndex) const final;

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
		void setXmlInterpretationOfVolumeRegion(unsigned int regionIndex, RESQML2_NS::StratigraphicUnitInterpretation * stratiUnitInterp) final;
	};
}
