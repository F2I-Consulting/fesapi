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

namespace RESQML2_NS
{
	class SealedSurfaceFrameworkRepresentation;
	class StratigraphicColumnRankInterpretation;
	class StratigraphicUnitInterpretation;

	/**
	 * @brief	A strict boundary representation (BREP), which represents the volume region by
	 * 			assembling together shells.
	 * 			
	 * 			BUSINESS RULE: The sealed structural framework must be part of the same earth model
	 * 			as this sealed volume framework.
	 */
	class SealedVolumeFrameworkRepresentation : public RepresentationSetRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~SealedVolumeFrameworkRepresentation() {}

		/**
		 * Sets the sealed surface framework representation this sealed volume framework representation
		 * is based on.
		 *
		 * @exception	std::invalid_argument	If <tt>ssf == nullptr</tt>.
		 *
		 * @param [in]	ssf	The sealed surface framework representation to set.
		 */
		DLL_IMPORT_OR_EXPORT void setSealedSurfaceFramework(SealedSurfaceFrameworkRepresentation* ssf);

		/**
		 * Sets the stratigraphic unit interpretation of a particular volume region.
		 *
		 * @exception	std::out_of_range	 	If <tt>regionIndex &gt;=</tt> getRegionCount().
		 * @exception	std::invalid_argument	If <tt>stratiUnitInterp == nullptr</tt>.
		 *
		 * @param 	  	regionIndex			Zero-base index of the volume region.
		 * @param [in]	stratiUnitInterp	The stratigraphic unit interpretation represented by the
		 * 									region at position @p regionIndex.
		 */
		DLL_IMPORT_OR_EXPORT void setInterpretationOfVolumeRegion(unsigned int regionIndex, StratigraphicUnitInterpretation * stratiUnitInterp);

		/**
		 * Pushes back a volume region in this sealed volume framework.
		 *
		 * @exception	std::invalid_argument	If <tt>stratiUnitInterp == nullptr</tt>.
		 * @exception	std::invalid_argument	If <tt>externalShellFaceCount == 0</tt>.
		 *
		 * @param [in]	stratiUnitInterp		 	The stratigraphic unit interpretation represented by
		 * 											this region.
		 * @param 	  	externalShellFaceCount   	The count of faces composing the region external
		 * 											shell.
		 * @param 	  	faceRepresentationIndices	An array containing, for each external shell face,
		 * 											the index of the corresponding representation in the
		 * 											representation list of this organization. The size of
		 * 											this array is @p externalShellFaceCount.
		 * @param 	  	faceRepPatchIndices		 	An array containing, for each external shell face,
		 * 											the index of the corresponding patch in the
		 * 											corresponding representation. The size of this array
		 * 											is @p externalShellFaceCount.
		 * @param 	  	faceSide				 	An array containing the orientation of each external
		 * 											shell face. The positive orientation is defined with
		 * 											@c true while the negative one is defined with
		 * 											@c false. The size of this array is @p
		 * 											externalShellFaceCount.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackVolumeRegion(StratigraphicUnitInterpretation * stratiUnitInterp,
			unsigned int externalShellFaceCount,
			unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide) = 0;

		/**
		 * Pushes back an internal shell in a particular volume region of this sealed volume framework.
		 *
		 * @exception	std::out_of_range	 	If <tt>regionIndex &gt;=</tt> getRegionCount().
		 * @exception	std::invalid_argument	If <tt>externalShellFaceCount == 0</tt>.
		 *
		 * @param 	regionIndex				 	Zero-base index of the volume region where to push back
		 * 										the internal shell.
		 * @param 	internalShellFaceCount   	The count of faces composing the region internal shell.
		 * @param 	faceRepresentationIndices	An array containing, for each internal shell face, the
		 * 										index of the corresponding representation in the
		 * 										representation list of this organization. The size of
		 * 										this array is @p internalShellFaceCount.
		 * @param 	faceRepPatchIndices		 	An array containing, for each internal shell face, the
		 * 										index of the corresponding patch in the corresponding
		 * 										representation. The size of this array is @p
		 * 										internalShellFaceCount.
		 * @param 	faceSide				 	An array containing the orientation of each internal
		 * 										shell face. The positive orientation is defined with
		 * 										@c true while the negative one is defined with
		 * 										@c false. The size of this array is @p
		 * 										internalShellFaceCount.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackInternalShell(unsigned int regionIndex,
			unsigned int internalShellFaceCount,
			unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide) = 0;

		/** 
		 * Gets the sealed structural framework this sealed volume framework is based on.
		 *
		 * @returns The sealed structural framework this sealed volume framework is based on.
		 */
		DLL_IMPORT_OR_EXPORT SealedSurfaceFrameworkRepresentation* getSealedStructuralFramework() const;

		/** 
		 * Gets the stratigraphic unit interpretation a particular region of this framework represents.
		 *
		 * @exception	std::out_of_range	 	If <tt>regionIndex &gt;=</tt> getRegionCount().
		 *
		 * @param	regionIndex	Zero-based index of the region.
		 * 						
		 * @returns The stratigraphic unit interpretation represented by the region at position @p regionIndex. 
		 */
		DLL_IMPORT_OR_EXPORT class StratigraphicUnitInterpretation* getStratiUnitInterp(unsigned int regionIndex) const;

		/**
		 * Gets the count of regions in this framework.
		 *
		 * @exception	std::range_error	If the count of regions is strictly greater than unsigned int.
		 *
		 * @returns	The count of regions in this framework.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getRegionCount() const = 0;

		/**
		 * Gets the count of internal shells in a particular region.
		 *
		 * @exception	std::out_of_range	If <tt>regionIndex &gt;=</tt> getRegionCount().
		 * @exception	std::range_error 	If the count of internal shells is strictly greater than
		 * 									unsigned int max.
		 *
		 * @param 	regionIndex	Zero-based index of the framework region.
		 *
		 * @returns	The count of internal shells in the region at position @p regionIndex.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getInternalShellCount(unsigned int regionIndex) const = 0;

		/**
		 * Gets the count of faces in a particular region external shell.
		 *
		 * @exception	std::out_of_range	If <tt>regionIndex &gt;=</tt> getRegionCount().
		 * @exception	std::range_error 	If the count of faces is strictly greater than unsigned int
		 * 									max.
		 *
		 * @param 	regionIndex	Zero-based index of the framework region.
		 *
		 * @returns	The count of faces in the external shell of the region at position @p regionIndex.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getFaceCountOfExternalShell(unsigned int regionIndex) const = 0;

		/**
		 * Gets the count of faces in a particular region internal shell.
		 *
		 * @exception	std::out_of_range	If <tt>regionIndex &gt;=</tt> getRegionCount().
		 * @exception	std::out_of_range	If <tt>internalShellIndex &gt;=
		 * 									getInternalShellCount(regionIndex)</tt>.
		 * @exception	std::range_error 	If the count of faces is strictly greater than unsigned int
		 * 									max.
		 *
		 * @param 	regionIndex		  	Zero-based index of the region.
		 * @param 	internalShellIndex	Zero-based index of the internal shell.
		 *
		 * @returns	The count of faces of the region @p regionIndex internal shell @p internalShellIndex.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getFaceCountOfInternalShell(unsigned int regionIndex, unsigned int internalShellIndex) const = 0;

		/**
		 * Gets the representation (for instance the triangulated surface) which contains a particular
		 * face of the external shell of a particular region of this framework.
		 *
		 * @exception	std::out_of_range	If <tt>regionIndex &gt;=</tt> getRegionCount().
		 * @exception	std::out_of_range	If <tt>faceIndex &gt;=
		 * 									getFaceCountOfExternalShell(regionIndex)</tt>.
		 *
		 * @param 	regionIndex	Zero-based index of the region.
		 * @param 	faceIndex  	Zero-base index of the external shell face.
		 *
		 * @returns	The representation which contains the face @p faceIndex of the external shell of the
		 * 			region @p regionIndex of this framework.
		 */
		DLL_IMPORT_OR_EXPORT virtual RESQML2_NS::AbstractRepresentation* getRepOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const = 0;

		/**
		 * Gets the representation (for instance the triangulated surface) which contains a particular
		 * face of a particular internal shell of a particular region of this framework.
		 *
		 * @exception	std::out_of_range	If <tt>regionIndex &gt;=</tt> getRegionCount().
		 * @exception	std::out_of_range	If <tt>internalShellIndex &gt;=
		 * 									getInternalShellCount(regionIndex)</tt>.
		 * @exception	std::out_of_range	If <tt>faceIndex &gt;=
		 * 									getFaceCountOfInternalShell(regionIndex,
		 * 									internalShellIndex)</tt>.
		 *
		 * @param 	regionIndex		  	Zero-based index of the framework region.
		 * @param 	internalShellIndex	Zero-based index of the internal shell.
		 * @param 	faceIndex		  	Zero-based index of the face of the framework region internal
		 * 								shell.
		 *
		 * @returns	The representation which contains the face @p faceIndex of the internal shell @p
		 * 			internalShellIndex of the region @p regionIndex of this framework.
		 */
		DLL_IMPORT_OR_EXPORT virtual RESQML2_NS::AbstractRepresentation* getRepOfInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const = 0;

		/**
		 * Get the representation patch index corresponding to a particular face of the external shell
		 * of a particular region of this framework.
		 *
		 * @exception	std::out_of_range	If <tt>regionIndex &gt;=</tt> getRegionCount().
		 * @exception	std::out_of_range	If <tt>faceIndex &gt;=
		 * 									getFaceCountOfExternalShell(regionIndex)</tt>.
		 *
		 * @param 	regionIndex	Zero-based index of the framework region.
		 * @param 	faceIndex  	Zero-based index of the external shell face.
		 *
		 * @returns	The representation patch index (on representation
		 * 			<tt>getRepOfExternalShellFace(regionIndex, faceIndex)</tt>) which is the face @p
		 * 			faceIndex of the external shell of the region @p regionIndex of this framework.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getRepPatchIndexOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const = 0;

		/**
		 * Get the representation patch index corresponding to a particular face of particular internal
		 * shell of a particular region of this framework.
		 *
		 * @exception	std::out_of_range	If <tt>regionIndex &gt;=</tt> getRegionCount().
		 * @exception	std::out_of_range	If <tt>internalShellIndex &gt;=
		 * 									getInternalShellCount(regionIndex)</tt>.
		 * @exception	std::out_of_range	If <tt>faceIndex &gt;=
		 * 									getFaceCountOfInternalShell(regionIndex,
		 * 									internalShellIndex)</tt>.
		 *
		 * @param 	regionIndex		  	Zero-based index of the framework region.
		 * @param 	internalShellIndex	Zero-based index of the internal shell.
		 * @param 	faceIndex		  	Zero-based index of the face.
		 *
		 * @returns	The representation patch index (on representation
		 * 			<tt>getRepOfInternalShellFace(regionIndex, internalShellIndex, faceIndex)</tt>) which
		 * 			is the face @p faceIndex of the internal shell @p internalShellIndex of the region @p
		 * 			regionIndex of this framework.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getRepPatchIndexOfInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const = 0;

		/**
		 * Get the orientation (the side flag) of a particular face of the external shell of a
		 * particular region of this framework.
		 *
		 * @exception	std::out_of_range	If <tt>regionIndex &gt;=</tt> getRegionCount().
		 * @exception	std::out_of_range	If <tt>faceIndex &gt;=
		 * 									getFaceCountOfExternalShell(regionIndex)</tt>.
		 *
		 * @param 	regionIndex	Zero-based index of the framework region.
		 * @param 	faceIndex  	Zero-based index of the external shell face.
		 *
		 * @returns	The side flag of the face @p faceIndex of the external shell of the region @p
		 * 			regionIndex of this framework.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool getSideFlagOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const = 0;

		/**
		 * Get the orientation (the side flag) of a particular face of a particular internal shell of a
		 * particular region of this framework.
		 *
		 * @exception	std::out_of_range	If <tt>regionIndex &gt;=</tt> getRegionCount().
		 * @exception	std::out_of_range	If <tt>internalShellIndex &gt;=
		 * 									getInternalShellCount(regionIndex)</tt>.
		 * @exception	std::out_of_range	If <tt>faceIndex &gt;=
		 * 									getFaceCountOfInternalShell(regionIndex,
		 * 									internalShellIndex)</tt>.
		 *
		 * @param 	regionIndex		  	Zero-based index of the framework region.
		 * @param 	internalShellIndex	Zero-based index of the internal shell.
		 * @param 	faceIndex		  	Zero-based index of the face.
		 *
		 * @returns	The side flag of the face @p faceIndex of the internal shell @p internalShellIndex of
		 * 			the region @p regionIndex of this framework.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool getSideFlagOfInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const = 0;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/**
		* Only to be used in partial transfer context
		*
		* @param [in,out]	partialObject	If non-null, the partial object.
		*
		* 
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
		void loadTargetRelationships() final;

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
