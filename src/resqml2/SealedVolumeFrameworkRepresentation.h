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

#include "RepresentationSetRepresentation.h"

/** . */
namespace RESQML2_NS
{
	class SealedSurfaceFrameworkRepresentation;
	class StratigraphicColumnRankInterpretation;
	class StratigraphicUnitInterpretation;

	/** A sealed volume framework representation. */
	class SealedVolumeFrameworkRepresentation : public RepresentationSetRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~SealedVolumeFrameworkRepresentation() {}

		/**
		 * Set the Sealed Surface Framework which the sealed volume framework is based on. It also sets
		 * the opposite relationship i.e. from the Sealed Surface Framework to the Sealed Volume
		 * Framework.
		 *
		 * @param [in,out]	ssf	The Sealed Surface Framework which the sealed volume framework is based
		 * 						on.
		 */
		DLL_IMPORT_OR_EXPORT void setSealedSurfaceFramework(SealedSurfaceFrameworkRepresentation* ssf);

		/**
		 * Set the strati unit interpretation of a particular volume region.
		 *
		 * @param 		  	regionIndex			The index of the region which represent the strati unit
		 * 										interpretation.
		 * @param [in,out]	stratiUnitInterp	The strati unit interpretation represented by the region.
		 */
		DLL_IMPORT_OR_EXPORT void setInterpretationOfVolumeRegion(unsigned int regionIndex, StratigraphicUnitInterpretation * stratiUnitInterp);

		/**
		 * Push back a region in this sealed volume framework.
		 *
		 * @param [in,out]	stratiUnitInterp		 	The stratigraphic unit inter^retation represented
		 * 												by this region.
		 * @param 		  	externalShellFaceCount   	The count of faces composing the region external
		 * 												shell.
		 * @param [in,out]	faceRepresentationIndices	The indices of the representation in the
		 * 												representation list of this organization for each
		 * 												external shell face.
		 * @param [in,out]	faceRepPatchIndices		 	The indices of the patch in the representation
		 * 												defined in \a faceRepresentationIndices for each
		 * 												external shell face.
		 * @param [in,out]	faceSide				 	The side "flag" dor each external shell face.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackVolumeRegion(StratigraphicUnitInterpretation * stratiUnitInterp,
			unsigned int externalShellFaceCount,
			unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide) = 0;

		/**
		 * Push back an internal shell in a particular region of this sealed volume framework. Throw
		 * exception if the region index does not correspond to a region which has been already pushed.
		 *
		 * @param 		  	regionIndex				 	The index of the framework region.. It must be in
		 * 												the interval [0..getRegionCount()[.
		 * @param 		  	externalShellFaceCount   	The count of faces composing the region internal
		 * 												shell.
		 * @param [in,out]	faceRepresentationIndices	The indices of the representation in the
		 * 												representation list of this organization for each
		 * 												internal shell face.
		 * @param [in,out]	faceRepPatchIndices		 	The indices of the patch in the representation
		 * 												defined in \a faceRepresentationIndices for each
		 * 												internal shell face.
		 * @param [in,out]	faceSide				 	The side "flag" dor each internal shell face.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackInternalShell(unsigned int regionIndex,
			unsigned int externalShellFaceCount,
			unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide) = 0;

		/** Get the Sealed Structural Framework this framework is based on. */
		DLL_IMPORT_OR_EXPORT class SealedSurfaceFrameworkRepresentation* getSealedStructuralFramework() const;

		/** Get the Stratigraphic Unit Interpretation a particular region of this framework represents. */
		DLL_IMPORT_OR_EXPORT class StratigraphicUnitInterpretation* getStratiUnitInterp(unsigned int regionIndex) const;

		/**
		 * Get the count of region in this framework.
		 *
		 * @returns	The count of region in this framework.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getRegionCount() const = 0;

		/**
		 * Get the count of internal shells in a particular region.
		 *
		 * @param 	regionIndex	The index of the framework region. It must be in the interval
		 * 						[0..getRegionCount()[.
		 *
		 * @returns	The count of internal shells in a particular region.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getInternalShellCount(unsigned int regionIndex) const = 0;

		/**
		 * Get the count of faces in a particular region external shell.
		 *
		 * @param 	regionIndex	The index of the framework region. It must be in the interval
		 * 						[0..getRegionCount()[.
		 *
		 * @returns	The count of faces in a particular region external shell.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getFaceCountOfExternalShell(unsigned int regionIndex) const = 0;

		/**
		 * Get the count of faces in a particular region internal shell.
		 *
		 * @param 	regionIndex		  	The index of the framework region. It must be in the interval
		 * 								[0..getRegionCount()[.
		 * @param 	internalShellIndex	The index of the internal shell. It must be in the interval
		 * 								[0..getInternalShellCount()[.
		 *
		 * @returns	The count of faces in a particular region internal shell.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getFaceCountOfInternalShell(unsigned int regionIndex, unsigned int internalShellIndex) const = 0;

		/**
		 * Get the representation (for instance the triangulated surface) which contains a particular
		 * face of the external shell of a particular region of this framework.
		 *
		 * @param 	regionIndex	The index of the framework region. It must be in the interval
		 * 						[0..getRegionCount()[.
		 * @param 	faceIndex  	The index of the face of the framework region external shell.
		 *
		 * @returns	The representation which contains the face \a faceIndex of the external shell of the
		 * 			region \a regionIndex of this framework.
		 */
		DLL_IMPORT_OR_EXPORT virtual RESQML2_NS::AbstractRepresentation* getRepOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const = 0;

		/**
		 * Get the representation (for instance the triangulated surface) which contains a particular
		 * face of a particular internal shell of a particular region of this framework.
		 *
		 * @param 	regionIndex		  	The index of the framework region. It must be in the interval
		 * 								[0..getRegionCount()[.
		 * @param 	internalShellIndex	The index of the internal shell. It must be in the interval
		 * 								[0..getInternalShellCount()[.
		 * @param 	faceIndex		  	The index of the face of the framework region external shell.
		 *
		 * @returns	The representation which contains the face \a faceIndex of the external shell of the
		 * 			region \a regionIndex of this framework.
		 */
		DLL_IMPORT_OR_EXPORT virtual RESQML2_NS::AbstractRepresentation* getRepOfInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const = 0;

		/**
		 * Get the representation patch index which is a particular face of the external shell of a
		 * particular region of this framework.
		 *
		 * @param 	regionIndex	The index of the framework region. It must be in the interval
		 * 						[0..getRegionCount()[.
		 * @param 	faceIndex  	The index of the face of the framework region external shell.
		 *
		 * @returns	The representation patch index (on representation getRepOfExternalShellFace()) which
		 * 			is the face \a faceIndex of the external shell of the region \a regionIndex of this
		 * 			framework.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getRepPatchIndexOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const = 0;

		/**
		 * Get the representation patch index which is a particular face of particular internal shell of
		 * a particular region of this framework.
		 *
		 * @param 	regionIndex		  	The index of the framework region. It must be in the interval
		 * 								[0..getRegionCount()[.
		 * @param 	internalShellIndex	The index of the internal shell. It must be in the interval
		 * 								[0..getInternalShellCount()[.
		 * @param 	faceIndex		  	The index of the face of the framework region external shell.
		 *
		 * @returns	The representation patch index (on representation getRepOfExternalShellFace()) which
		 * 			is the face \a faceIndex of the external shell of the region \a regionIndex of this
		 * 			framework.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getRepPatchIndexOfInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const = 0;

		/**
		 * Get the side flag of a particular face of the external shell of a particular region of this
		 * framework.
		 *
		 * @param 	regionIndex	The index of the framework region. It must be in the interval
		 * 						[0..getRegionCount()[.
		 * @param 	faceIndex  	The index of the face of the framework region external shell.
		 *
		 * @returns	The side flag of the face \a faceIndex of the external shell of the region \a
		 * 			regionIndex of this framework.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool getSideFlagOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const = 0;

		/**
		 * Get the side flag of a particular face of a particular internal shell of a particular region
		 * of this framework.
		 *
		 * @param 	regionIndex		  	The index of the framework region. It must be in the interval
		 * 								[0..getRegionCount()[.
		 * @param 	internalShellIndex	The index of the internal shell. It must be in the interval
		 * 								[0..getInternalShellCount()[.
		 * @param 	faceIndex		  	The index of the face of the framework region external shell.
		 *
		 * @returns	The side flag of the face \a faceIndex of the external shell of the region \a
		 * 			regionIndex of this framework.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool getSideFlagOfInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const = 0;

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

	protected:

		/**
		* Only to be used in partial transfer context
		*
		* @param [in,out]	partialObject	If non-null, the partial object.
		*
		* @returns	A DLL_IMPORT_OR_EXPORT.
		*/
		DLL_IMPORT_OR_EXPORT SealedVolumeFrameworkRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RepresentationSetRepresentation(partialObject) {}

		/**
		 * Default constructor
		*/
		SealedVolumeFrameworkRepresentation() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*
		* @param [in,out]	fromGsoap	If non-null, from gsoap.
		*/
		SealedVolumeFrameworkRepresentation(gsoap_resqml2_0_1::_resqml20__SealedVolumeFrameworkRepresentation* fromGsoap) : RepresentationSetRepresentation(fromGsoap) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*
		* @param [in,out]	fromGsoap	If non-null, from gsoap.
		*/
		SealedVolumeFrameworkRepresentation(gsoap_eml2_3::_resqml22__SealedVolumeFrameworkRepresentation* fromGsoap) : RepresentationSetRepresentation(fromGsoap) {}

		virtual COMMON_NS::DataObjectReference getSealedStructuralFrameworkDor() const = 0;

		virtual COMMON_NS::DataObjectReference getStratiUnitInterpDor(unsigned int regionIndex) const = 0;

		/** Loads target relationships */
		void loadTargetRelationships();

		/**
		 * Sets XML sealed surface framework
		 *
		 * @param [in,out]	ssf	If non-null, the ssf.
		 */
		virtual void setXmlSealedSurfaceFramework(class SealedSurfaceFrameworkRepresentation* ssf) = 0;

		/**
		 * Sets XML interpretation of volume region
		 *
		 * @param 		  	regionIndex			Zero-based index of the region.
		 * @param [in,out]	stratiUnitInterp	If non-null, the strati unit interp.
		 */
		virtual void setXmlInterpretationOfVolumeRegion(unsigned int regionIndex, class StratigraphicUnitInterpretation * stratiUnitInterp) = 0;
	};
}
