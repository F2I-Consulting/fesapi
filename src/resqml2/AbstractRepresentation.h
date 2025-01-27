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

namespace EML2_NS
{
	class AbstractLocal3dCrs;
	class TimeSeries;
}

namespace RESQML2_NS
{
	class AbstractValuesProperty;
	class PointsProperty;

	/** @brief	Proxy class for an abstract representation. */
	class AbstractRepresentation : public COMMON_NS::AbstractObject
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~AbstractRepresentation() = default;

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
		DLL_IMPORT_OR_EXPORT EML2_NS::AbstractLocal3dCrs* getLocalCrs(uint64_t patchIndex) const;

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
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getLocalCrsDor(uint64_t patchIndex) const;

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
		 * Set a time index in a time series for all point geometries of all existing patches of this representation.
		 *
		 * @param 	timeIndex	The time index of the time to associate to this representation.
		 * @param 	timeSeries	The time series containing the time of the representation at @p timeIndex.
		 */
		DLL_IMPORT_OR_EXPORT void setTimeIndex(uint64_t timeIndex, EML2_NS::TimeSeries* timeSeries);

		/**
		 * @brief Gets the time index of this representation in the associated TimeSeries.
		 *		Be sure to first check that a TimeSeries is associated this representation by calling getTimeSeriesDor or getTimeSeries;
		 *
		 * @exception	std::logic_error	If this representation is partial. Or if the representation is not associated to any TimeSeries.
		 *
		 * @returns	The time index of this representation in the associated TimeSeries.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getTimeIndex() const;

		/**
		 * Gets the TimeSeries associated to this representation.
		 *
		 * @returns Null if it fails, else the TimeSeries associated to this representation.
		 */
		DLL_IMPORT_OR_EXPORT EML2_NS::TimeSeries* getTimeSeries() const;

		/**
		 * @brief Gets the data object reference of the TimeSeries containing the time of this representation at a particular index.
		 *		For now, this method only look for a TimeSeries at the first patch containing a point geometry.
		 *
		 * @exception	std::logic_error	If this representation is partial.
		 *
		 * @returns	The data object reference of the TimeSeries, or empty
		 * 			data object reference there is not TimeSeries found.
		 */
		COMMON_NS::DataObjectReference getTimeSeriesDor() const;

		/**
		 * Gets all the properties which use this representation as support.
		 *
		 * @returns	A vector of pointers on all the properties which use this representation as support.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<class AbstractProperty *> getPropertySet() const;

		GETTER_DATAOBJECTS(AbstractValuesProperty, ValuesProperty)
		GETTER_DATAOBJECTS(PointsProperty, PointsProperty)

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

		GETTER_DATAOBJECTS(SubRepresentation, SubRepresentation)
		GETTER_DATAOBJECTS(SubRepresentation, FaultSubRepresentation)
		GETTER_DATAOBJECTS(RepresentationSetRepresentation, RepresentationSetRepresentation)

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
		DLL_IMPORT_OR_EXPORT virtual uint64_t getXyzPointCountOfPatch(unsigned int patchIndex) const = 0;

		/**
		 * Get the xyz point count of all patches of this representation.
		 *
		 * @returns	The xyz point count of all patches.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getXyzPointCountOfAllPatches() const;

		/**
		 * @brief	Gets all the xyz points of a particular patch of this representation. xyz points are
		 * 			given in the local CRS.
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
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatchInGlobalCrs(unsigned int patchIndex, double * xyzPoints) const;

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
		DLL_IMPORT_OR_EXPORT virtual uint64_t getPatchCount() const = 0;

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
		DLL_IMPORT_OR_EXPORT void addSeismic3dCoordinatesToPatch(unsigned int patchIndex, double* inlines, double* crosslines, uint64_t pointCount,
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
		 * @param [in,out]	proxy		  	The HDF proxy where to write the @p lineAbscissa values. It
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
		static constexpr char const* XML_TAG = "AbstractRepresentation";

		virtual void loadTargetRelationships() override;

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
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
		virtual gsoap_resqml2_0_1::resqml20__PointGeometry* getPointGeometry2_0_1(uint64_t patchIndex) const;

		/**
		 * Get the point geometry of a specific v2.2 patch of the representation.
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	nullptr if there is no point geometry for this particular patch otherwise the found
		 * 			point geometry.
		 */
		virtual gsoap_eml2_3::resqml22__PointGeometry* getPointGeometry2_2(uint64_t patchIndex) const;

		/**
		 * Creates a v2.0.1 point geometry patch.
		 *
		 * @param 		  	patchIndex				The index of the patch which will contain this
		 * 											geometry.
		 * @param [in,out]	points					All the points to set ordered according the topology
		 * 											of the representation it is based on. It should be 3 *
		 * 											numPoints sized if 3d and 2 * numPoints sized if 2d, etc...
		 * @param [in,out]	localCrs				The local CRS where the points lie on.
		 * @param [in,out]	dimensions				The dimensions of the array to write.
		 * @param 		  	numDimensionsInArray	The number of dimensions in the array to write.
		 * @param [in,out]	proxy					The HDF proxy where to write the points. It must be
		 * 											already opened for writing and won't be closed in this
		 * 											method.
		 *
		 * @returns	Null if it fails, else the new 2.0.1 point geometry patch.
		 */
		gsoap_resqml2_0_1::resqml20__PointGeometry* createPointGeometryPatch2_0_1(uint64_t patchIndex,
			double const * points, EML2_NS::AbstractLocal3dCrs const* localCrs, uint64_t const * dimensions, uint32_t numDimensionsInArray, EML2_NS::AbstractHdfProxy * proxy);

		/**
		 * Creates a v2.2 point geometry patch.
		 *
		 * @param 		  	patchIndex				The index of the patch which will contain this
		 * 											geometry.
		 * @param [in,out]	points					All the points to set ordered according the topology
		 * 											of the representation it is based on. It should be 3 *
		 * 											numPoints sized if 3d and 2 * numPoints sized if 2d, etc...
		 * @param [in,out]	localCrs				The local CRS where the points lie on.
		 * @param [in,out]	dimensions				The dimensions of the array to write.
		 * @param 		  	numDimensionsInArray	The number of dimensions in the array to write.
		 * @param [in,out]	proxy					The HDF proxy where to write the points. It must be
		 * 											already opened for writing and won't be closed in this
		 * 											method.
		 *
		 * @returns	Null if it fails, else the new point geometry patch 2 0 1.
		 */
		gsoap_eml2_3::resqml22__PointGeometry* createPointGeometryPatch2_2(uint64_t patchIndex,
			double const * points, EML2_NS::AbstractLocal3dCrs const* localCrs, uint64_t const * dimensions, uint32_t numDimensionsInArray, EML2_NS::AbstractHdfProxy * proxy);

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
	};
}
