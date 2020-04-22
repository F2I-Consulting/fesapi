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

#include <set>

#include "../common/AbstractObject.h"

/** @brief */
namespace RESQML2_NS
{
	/** Proxy class for an abstract representation. */
	class AbstractRepresentation : public COMMON_NS::AbstractObject
	{
	public:

		/** Values that represent indexable elements */
		enum indexableElement { NODE = 0, EDGE = 1, FACE = 2, VOLUME = 3, PILLAR = 4 };

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~AbstractRepresentation() {}

		/**
		 * Gets the local 3d CRS associated to a given patch of this representation in read and write
		 * access.
		 * 
		 * @exception std::out_of_range	If @p patchIndex is out of range.
		 * 								
		 * @param patchIndex	Zero-based index of the patch for which we look for the local CRS.
		 * 						
		 * @returns Null if it fails, else the local CRS associated to the @p patchIndex patch.
		 */
		DLL_IMPORT_OR_EXPORT class AbstractLocal3dCrs* getLocalCrs(unsigned int patchIndex) const;

		/**
		 * Gets the data object reference of the local 3d CRS associated to a given patch of this
		 * representation. This local CRS is where the point ordinals are given.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of range.
		 *
		 * @param 	patchIndex	Zero-based index of the patch for which we look for the local CRS.
		 *
		 * @returns	Empty data object reference if it fails, else the data object reference of the local
		 * 			CRS associated to the @p patchIndex patch.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getLocalCrsDor(unsigned int patchIndex) const;

		/**
		 * @brief Gets the data object reference of the HDF proxy which is used for storing the numerical
		 * values of this representation (i.e. its geometry).
		 *
		 * @exception	std::logic_error	If this representation is partial.
		 *
		 * @returns	The data object reference of the HDF proxy used for storing the geometry, or empty
		 * 			data object reference if it fails.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getHdfProxyDor() const = 0;

		/**
		 * Gets all the properties which use this representation as support.
		 *
		 * @returns	A vector of pointers on all the properties which use this representation as support.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<class AbstractProperty *> getPropertySet() const;

		/**
		 * Gets of all the values properties which use this representation as support.
		 *
		 * @returns	A vector of pointers to all the values properties which use this representation as
		 * 			support.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<class AbstractValuesProperty *> getValuesPropertySet() const;

		/**
		 * Gets the count of values properties which use this representation as support.
		 *
		 * @returns	The values properties count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getValuesPropertyCount() const; // Necessary for now in SWIG context because I ma not sure if I can always wrap a vector of polymorphic class yet.

		/**
		 * Gets a particular values property which uses this representation as support.
		 * 
		 * @exception std::out_of_range If @p index is out of range of the array of properties 
		 * 								for this representation.
		 * 								
		 * @param index	The index of the values property we look for.
		 * 				
		 * @returns The values property at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT class AbstractValuesProperty * getValuesProperty(unsigned int index) const; // Necessary for now in SWIG context because I ma not sure if I can always wrap a vector of polymorphic class yet.

		/**
		 * Sets the interpretation which is associated to this representation.
		 *
		 * @exception	std::invalid_argument	If @p interp is null.
		 *
		 * @param [in]	interp	The interpretation to associate to this representation.
		 */
		DLL_IMPORT_OR_EXPORT void setInterpretation(class AbstractFeatureInterpretation * interp);

		/** 
		 * Gets the interpretation associated to this representation.
		 *
		 * @returns Null pointer if no interpretation is associated to this representation. Otherwise
		 * 			the associated interpretation.
		 */
		DLL_IMPORT_OR_EXPORT class AbstractFeatureInterpretation* getInterpretation() const;

		/**
		 * Gets the data object reference of the interpretation associated to this representation.
		 *
		 * @returns	Empty data object reference if no interpretation is associated to this
		 * 			representation. Otherwise the data object reference of the associated interpretation.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getInterpretationDor() const;

		/**
		 * Gets all the subrepresentations of this representation.
		 *
		 * @returns	A vector of pointers to all of the subrepresentations associated to this
		 * 			representation.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<SubRepresentation *> getSubRepresentationSet() const;

		/**
		 * Get the count of all the subrepresentations associated to this representation.
		 *
		 * @returns	The count of all subrepresentations associated to this representation.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getSubRepresentationCount() const; //  It is mainly used in SWIG context for parsing the vector from a non C++ language.

		/**
		 * Gets a particular subrepresentation associated to this representation according to its
		 * position in the EPC document.
		 *
		 * @exception	std::out_of_range	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the subrepresentation we look for.
		 *
		 * @returns	The subrepresentaiton at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT SubRepresentation * getSubRepresentation(unsigned int index) const; //  It is mainly used in SWIG context for parsing the vector from a non C++ language.

		/**
		 * Gets all the subrepresentations of this representation which represent a fault.
		 *
		 * @returns	A vector of pointers to all the fault subrepresentations associated to this
		 * 			representation.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<SubRepresentation *> getFaultSubRepresentationSet() const;

		/**
		 * Gets the count of all the fault subrepresentations of this EPC document associated to this
		 * representation.
		 *
		 * @returns	The fault subrepresentations count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getFaultSubRepresentationCount() const; // It is mainly used in SWIG context for parsing the vector from a non C++ language.

		/**
		 * Gets a particular fault subrepresentation associated to this representation according to its position in the EPC document.
		 *
		 * @param 	index	Zero-based index of the fault subrepresentation we look for.
		 *
		 * @returns	The fault subrepresentation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT SubRepresentation * getFaultSubRepresentation(unsigned int index) const; //  It is mainly used in SWIG context for parsing the vector from a non C++ language.

		/**
		 * Get the xyz point count in a given patch of this representation.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of range.
		 * @exception	std::logic_error 	If this representation is partial.
		 *
		 * @param 	patchIndex	Zero-based index of the patch from which we look for the xyz points.
		 *
		 * @returns	The xyz point count of the patch at position @p patchIndex.
		 */
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getXyzPointCountOfPatch(unsigned int patchIndex) const = 0;

		/**
		 * Get the xyz point count of all patches of this representation.
		 *
		 * @returns	The xyz point count of all patches.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfAllPatches() const;

		/**
		 * Gets all the xyz points of a particular patch of this representation. xyz points are given in
		 * the local CRS.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of range.
		 * @exception	std::logic_error 	If this representation is partial.
		 *
		 * @param 	   	patchIndex	Zero-based index of the patch from which we look for the xyz points.
		 * @param [out]	xyzPoints 	A linearized 2d array where the first (quickest) dimension is the
		 * 							coordinate dimension (x, y or z) and second dimension is vertex
		 * 							dimension. It must be preallocated with a size of <tt>3 *
		 * 							getXyzPointCountOfPatch(patchIndex)</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const = 0;

		/**
		 * @brief Gets all the xyz points of a particular patch of this representation. xyz points are given in
		 * the global CRS.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of range.
		 *
		 * @param 	   	patchIndex	Zero-based index of the patch from which we look for the xyz points.
		 * @param [out]	xyzPoints 	A linearized 2d array where the first (quickest) dimension is the
		 * 							coordinate dimension (x, y or z) and second dimension is vertex
		 * 							dimension. It must be preallocated with a size of <tt>3 *
		 * 							getXyzPointCountOfPatch(patchIndex)</tt>.
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatchInGlobalCrs(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		 * @brief Gets all the xyz points of all patches of this representation. xyz points are given in the
		 * local CRS.
		 *
		 * @param [out]	xyzPoints	A linearized 2d array where the first (quickest) dimension is the
		 * 							coordinate dimension (x, y or z) and second dimension is vertex
		 * 							dimension. It must be preallocated with a size of <tt>3 *
		 * 							getXyzPointCountOfAllPatches()</tt>.
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfAllPatches(double * xyzPoints) const;

		/**
		 * Checks if all of the patches (geometries) of this representation are defined in a same local
		 * CRS.
		 *
		 * @returns	True if this representation is defined in a single local CRS, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isInSingleLocalCrs() const;

		/**
		 * Checks if all of the patches (geometries) of this representation are defined in a same global
		 * CRS.
		 *
		 * @returns	True if this representation is defined in a single global CRS, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isInSingleGlobalCrs() const;

		/**
		 * Gets all the xyz points of all patches of this individual representation. xyz points are
		 * given in the global CRS.
		 *
		 * @param [out]	xyzPoints	A linearized 2d array where the first (quickest) dimension is the
		 * 							coordinate dimension (x, y or Z) and second dimension is vertex
		 * 							dimension. Thus, its size is 3*(3*[count of all xyz points]). It must
		 * 							be preallocated.
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfAllPatchesInGlobalCrs(double * xyzPoints) const;

		/**
		 * Gets the seismic support of a specific patch of this representation.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of the patch count range.
		 *
		 * @param 	patchIndex	Zero-based index of the patch from which we look for the seismic support.
		 *
		 * @returns	Null if no seismic information have been provided for the patch at position @p
		 * 			patchIndex. Else, its seismic support.
		 */
		DLL_IMPORT_OR_EXPORT AbstractRepresentation* getSeismicSupportOfPatch(const unsigned int & patchIndex) const;

		/**
		 * Gets all seismic supports of the current geometry of this representation (that is to say the
		 * seismic supports of all the patches). This method does not return the seismic lattice
		 * representations which are support of 2d grid representation.
		 *
		 * @returns	A vector of pointers to all the seismic supports associated to this representation.
		 */
		DLL_IMPORT_OR_EXPORT std::set<AbstractRepresentation*> getAllSeismicSupport() const;

		/**
		 * Gets the patch count.
		 *
		 * @returns	The patch count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getPatchCount() const = 0;

		/**
		 * Pushes back this representation into a representation set representation.
		 *
		 * @exception	std::invalid_argument	If @p repSet is null.
		 *
		 * @param [in]	repSet	The representation set representation which will contain this
		 * 							representation.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackIntoRepresentationSet(class RepresentationSetRepresentation * repSet);

		/**
		 * Gets all the representation set representations which contain this representation.
		 *
		 * @returns	A vector of pointers to all the representation set representations which contain this
		 * 			representation.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<RepresentationSetRepresentation *> getRepresentationSetRespresentationSet() const;

		/**
		 * Gets the count of all representation set representations which contain this representation.
		 *
		 * @returns	The count of all representation set representations which contain this representation.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getRepresentationSetRepresentationCount() const;

		/**
		 * Gets the parent representation set representation at the specified index of the
		 * representation set representation list.
		 *
		 * @exception	out_of_range	If @p index is out of the range of representation set
		 * 								representation count.
		 *
		 * @param 	index	Zero-based index of the representation set representation we look for.
		 *
		 * @returns	The parent representation set representation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT RepresentationSetRepresentation * getRepresentationSetRepresentation(const ULONG64  & index) const;

		/**
		 * Adds seismic 3d coordinates to an existing point geometry patch.
		 *
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 * @exception	std::invalid_argument	If @p patchIndex does not identify a point geometry patch.
		 * @exception	std::invalid_argument	If there already exists some seismic 2d coordinates for
		 * 										the geometry patch at position @p patchIndex.
		 *
		 * @param 		   	patchIndex	  	The index of the geometry patch which receives the seismic
		 * 									coordinates.
		 * @param [in]	   	inlines		  	The sequence of trace or inter-trace inline positions that
		 * 									correspond to the geometry coordinates. It must be in the
		 * 									same order than @p crosslines.
		 * @param [in]	   	crosslines	  	The sequence of trace or inter-trace crossline positions that
		 * 									correspond to the geometry coordinates. It must be in the
		 * 									same order than @p inlines.
		 * @param 		   	pointCount	  	Number of points. It is the size of both @p inlines and @p
		 * 									crosslines.
		 * @param [in]	   	seismicSupport	The representation of the seismic line.
		 * @param [in, out]	proxy		  	The HDF proxy where to write the @p inlines and @p crosslines
		 * 									values. It must be already opened for writing and won't be
		 * 									closed in this method.
		 */
		DLL_IMPORT_OR_EXPORT void addSeismic3dCoordinatesToPatch(unsigned int patchIndex, double* inlines, double* crosslines, unsigned int pointCount,
			RESQML2_NS::AbstractRepresentation* seismicSupport, EML2_NS::AbstractHdfProxy* proxy);

		/**
		 * Adds seismic 3d coordinates to an existing point geometry patch.
		 *
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 * @exception	std::invalid_argument	If @p patchIndex does not identify a point geometry patch.
		 * @exception	std::invalid_argument	If there already exists some seismic 2d coordinates for
		 * 										the geometry patch at position @p patchIndex.
		 *
		 * @param 	  	patchIndex	  	The index of the geometry patch which receives the seismic
		 * 								coordinates.
		 * @param 	  	startInline   	The first inline.
		 * @param 	  	incrInline	  	The inline increment.
		 * @param 	  	countInline   	The inline count.
		 * @param 	  	startCrossline	The first crossline.
		 * @param 	  	incrCrossline 	The crossline increment.
		 * @param 	  	countCrossline	The crossline count.
		 * @param [in]	seismicSupport	The representation of the seismic line.
		 */
		DLL_IMPORT_OR_EXPORT void addSeismic3dCoordinatesToPatch(unsigned int patchIndex, double startInline, double incrInline, unsigned int countInline,
			double startCrossline, double incrCrossline, unsigned int countCrossline,
			RESQML2_NS::AbstractRepresentation* seismicSupport);

		/**
		 * Adds seismic 2d coordinates to an existing point geometry patch.
		 *
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 * @exception	std::invalid_argument	If @p patchIndex does not identify a point geometry patch.
		 * @exception	std::invalid_argument	If there already exists some seismic 3d coordinates for
		 * 										the geometry patch at position @p patchIndex.
		 *
		 * @param 		  	patchIndex	  	The index of the geometry patch which receives the seismic
		 * 									coordinates.
		 * @param [in,out]	lineAbscissa  	The abscissa of each points of the patch on the seismic line.
		 * 									The count of this array must be equal to
		 * 									<tt>getXyzPointCountOfPatch(patchIndex)</tt>.
		 * @param [in,out]	seismicSupport	The representation of the seismic line.
		 * @param [in,out]	proxy		  	The HDF proxy where to write the @lineAbscissa values. It
		 * 									must be already opened for writing and won't be closed in
		 * 									this method.
		 */
		DLL_IMPORT_OR_EXPORT void addSeismic2dCoordinatesToPatch(unsigned int patchIndex, double* lineAbscissa,
			RESQML2_NS::AbstractRepresentation * seismicSupport, EML2_NS::AbstractHdfProxy * proxy);

		/**
		 * Gets all the abscissa of the points of a specific patch related to 2d seismic line.
		 *
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 * @exception	std::invalid_argument	If the patch at position @p patchIndex has no seismic
		 * 										information.
		 *
		 * @param 	   	patchIndex	The index of the geometry patch which stores the seismic coordinates.
		 * @param [out]	values	  	The array where the abscissa are going to be stored. The count of
		 * 							this array must be equal to <tt>getXyzPointCountOfPatch(patchIndex)</tt>.
		 */
		DLL_IMPORT_OR_EXPORT void getSeismicLineAbscissaOfPointsOfPatch(unsigned int patchIndex, double* values) const;

		/**
		 * Gets all the inline coordinates of the points of a specific patch related to seismic lattice.
		 *
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 * @exception	std::invalid_argument	If the patch at position @p patchIndex has no seismic
		 * 										information.
		 *
		 * @param 	   	patchIndex	The index of the geometry patch which stores the seismic coordinates.
		 * @param [out]	values	  	The array where the inlines coordinates are going to be stored. The
		 * 							count of this array must be equal to
		 * 							<tt>getXyzPointCountOfPatch(patchIndex)</tt>.
		 */
		DLL_IMPORT_OR_EXPORT void getInlinesOfPointsOfPatch(unsigned int patchIndex, double * values) const;

		/**
		 * Gets all the crossline coordinates of the points of a specific patch related to seismic
		 * lattice.
		 *
		 * @exception	std::out_of_range	 	If @p patchIndex is out of range.
		 * @exception	std::invalid_argument	If the patch at position @p patchIndex has no seismic
		 * 										information.
		 *
		 * @param 	   	patchIndex	The index of the geometry patch which stores the seismic coordinates.
		 * @param [out]	values	  	The array where the crossline coordinates are going to be stored. The
		 * 							count of this array must be equal to
		 * 							<tt>getXyzPointCountOfPatch(patchIndex)</tt>.
		 */
		DLL_IMPORT_OR_EXPORT void getCrosslinesOfPointsOfPatch(unsigned int patchIndex, double * values) const;

		/** The standard XML tag without XML namespace for serializing this data object */
		static const char* XML_TAG;

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT AbstractRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/** Defatul constructor */
		AbstractRepresentation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractRepresentation(gsoap_resqml2_0_1::resqml20__AbstractRepresentation* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractRepresentation(gsoap_eml2_3::resqml22__AbstractRepresentation* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		 * Get the point geometry of a specific v2.0.1 patch of the representation.
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	nullptr if there is no point geometry for this particular patch otherwise the found
		 * 			point geometry.
		 */
		virtual gsoap_resqml2_0_1::resqml20__PointGeometry* getPointGeometry2_0_1(unsigned int patchIndex) const;

		/**
		 * Get the point geometry of a specific v2.2 patch of the representation.
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	nullptr if there is no point geometry for this particular patch otherwise the found
		 * 			point geometry.
		 */
		virtual gsoap_eml2_3::resqml22__PointGeometry* getPointGeometry2_2(unsigned int patchIndex) const;

		/**
		 * Creates a v2.0.1 point geometry patch.
		 *
		 * @param 		  	patchIndex				The index of the patch which will contain this
		 * 											geometry.
		 * @param [in,out]	points					All the points to set ordered according the topology
		 * 											of the representation it is based on. It should be 3 *
		 * 											numPoints sized.
		 * @param [in,out]	localCrs				The local CRS where the points lie on.
		 * @param [in,out]	numPoints				The number of points for each dimension of the array
		 * 											to write.
		 * @param 		  	numDimensionsInArray	The number of dimensions in the array to write.
		 * @param [in,out]	proxy					The HDF proxy where to write the points. It must be
		 * 											already opened for writing and won't be closed in this
		 * 											method.
		 *
		 * @returns	Null if it fails, else the new point geometry patch 2 0 1.
		 */
		gsoap_resqml2_0_1::resqml20__PointGeometry* createPointGeometryPatch2_0_1(unsigned int patchIndex, double const * points, class AbstractLocal3dCrs const* localCrs, unsigned long long const * numPoints, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy * proxy);

		/**
		 * Creates a v2.2 point geometry patch.
		 *
		 * @param 		  	patchIndex				The index of the patch which will contain this
		 * 											geometry.
		 * @param [in,out]	points					All the points to set ordered according the topology
		 * 											of the representation it is based on. It should be 3 *
		 * 											numPoints sized.
		 * @param [in,out]	localCrs				The local CRS where the points lie on.
		 * @param [in,out]	numPoints				The number of points for each dimension of the array
		 * 											to write.
		 * @param 		  	numDimensionsInArray	The number of dimensions in the array to write.
		 * @param [in,out]	proxy					The HDF proxy where to write the points. It must be
		 * 											already opened for writing and won't be closed in this
		 * 											method.
		 *
		 * @returns	Null if it fails, else the new point geometry patch 2 0 1.
		 */
		gsoap_eml2_3::resqml22__PointGeometry* createPointGeometryPatch2_2(unsigned int patchIndex, double const * points, class AbstractLocal3dCrs const* localCrs, unsigned long long const * numPoints, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy * proxy);

		/**
		 * Gets hdf proxy dor from point geometry patch
		 *
		 * @param [in,out]	patch	If non-null, the patch.
		 *
		 * @returns	Empty data object reference if it fails, else the hdf proxy dor from point geometry patch.
		 */
		COMMON_NS::DataObjectReference getHdfProxyDorFromPointGeometryPatch(gsoap_resqml2_0_1::resqml20__PointGeometry* patch) const;

		/**
		 * Gets hdf proxy dor from point geometry patch
		 *
		 * @param [in,out]	patch	If non-null, the patch.
		 *
		 * @returns	Empty data object reference if it fails, else the hdf proxy dor from point geometry patch.
		 */
		COMMON_NS::DataObjectReference getHdfProxyDorFromPointGeometryPatch(gsoap_eml2_3::resqml22__PointGeometry* patch) const;

		/**
		 * Gets seismic 3D coordinates
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	Null if it fails, else the seismic 3D coordinates.
		 */
		gsoap_resqml2_0_1::resqml20__Seismic3dCoordinates* getSeismic3dCoordinates2_0_1(unsigned int patchIndex) const;

		/**
		 * Gets seismic 3D coordinates
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	Null if it fails, else the seismic 3D coordinates.
		 */
		gsoap_eml2_3::resqml22__Seismic3dCoordinates* getSeismic3dCoordinates2_2(unsigned int patchIndex) const;

		/** Loads target relationships */
		virtual void loadTargetRelationships() override;
	};
}
