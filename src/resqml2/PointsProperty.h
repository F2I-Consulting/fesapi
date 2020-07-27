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

#include "AbstractProperty.h"

namespace RESQML2_NS
{
	/** @brief	Proxy class for an points property. */
	class PointsProperty : public AbstractProperty
	{
	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~PointsProperty() {}
		
		/**
		 * Get the xyz point count in a given patch of this property.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of range.
		 * @exception	std::logic_error 	If this representation is partial.
		 *
		 * @param 	patchIndex	Zero-based index of the patch from which we look for the xyz points.
		 *
		 * @returns	The xyz point count of the patch at position @p patchIndex.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(unsigned int patchIndex) const {
			return getValuesCountOfPatch(patchIndex) / 3;
		}

		/**
		 * Get the xyz point count of all patches of this property.
		 *
		 * @returns	The xyz point count of all patches.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfAllPatches() const;

		/**
		 * @brief	Gets all the xyz points of a particular patch of this property. xyz points are
		 * 			given in the local CRS.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is out of range.
		 * @exception	std::logic_error 	If this property is partial.
		 *
		 * @param 	   	patchIndex	Zero-based index of the patch from which we look for the xyz points.
		 * @param [out]	xyzPoints 	A linearized 2d array where the first (quickest) dimension is the
		 * 							coordinate dimension (x, y or z) and second dimension is vertex
		 * 							dimension. It must be preallocated with a size of <tt>3 *
		 * 							getXyzPointCountOfPatch(patchIndex)</tt>.
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const;

		/**
		 * @brief Gets all the xyz points of a particular patch of this property. xyz points are given in
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
		 * @brief Gets all the xyz points of all patches of this property. xyz points are given in the
		 * local CRS.
		 *
		 * @param [out]	xyzPoints	A linearized 2d array where the first (quickest) dimension is the
		 * 							coordinate dimension (x, y or z) and second dimension is vertex
		 * 							dimension. It must be preallocated with a size of <tt>3 *
		 * 							getXyzPointCountOfAllPatches()</tt>.
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfAllPatches(double * xyzPoints) const;

		/**
		 * Gets all the xyz points of all patches of this property. xyz points are
		 * given in the global CRS.
		 *
		 * @param [out]	xyzPoints	A linearized 2d array where the first (quickest) dimension is the
		 * 							coordinate dimension (x, y or Z) and second dimension is vertex
		 * 							dimension. Thus, its size is 3*(3*[count of all xyz points]). It must
		 * 							be preallocated.
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfAllPatchesInGlobalCrs(double * xyzPoints) const;

		/**
		 * @brief Adds a 1d array of points (in local CRS) to the property.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	xyzPoints		All the property values to set ordered according the topology
		 * 									of the representation it is based on.
		 * @param 		  	pointCount  	The number of points to write.
		 * @param [in,out]	proxy			(Optional) The HDF proxy where to write the property points.
		 * 									It must be already opened for writing and won't be closed in this
		 * 									method. If @c nullptr (default value), then a default HDF proxy
		 * 									must be defined in the repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackArray1dOfXyzPoints(const double * xyzPoints, ULONG64 pointCount, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief Adds a 2d array of points (in local CRS) to the property.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	xyzPoints				All the property values to set ordered according the
		 * 											topology of the representation it is based on.
		 * @param 		  	pointCountInFastestDim	The number of points to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	pointCountInSlowestDim	The number of points to write in the slowest
		 * 											dimension (mainly J dimension).
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											points. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default value), then a default HDF proxy must be
		 * 											defined in the repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackArray2dOfXyzPoints(const double * xyzPoints, ULONG64 pointCountInFastestDim, ULONG64 pointCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief Adds a 3d array of points (in local CRS) to the property.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	xyzPoints				All the property values to set ordered according the
		 * 											topology of the representation it is based on.
		 * @param 		  	pointCountInFastestDim	The number of points to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	pointCountInMiddleDim 	The number of points to write in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	pointCountInSlowestDim	The number of points to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											points. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default value), then a default HDF proxy must be
		 * 											defined in the repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackArray3dOfXyzPoints(const double * xyzPoints, ULONG64 pointCountInFastestDim, ULONG64 pointCountInMiddleDim, ULONG64 pointCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief Adds an nd array of points (in local CRS) to the property.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	xyzPoints				All the property values to set ordered according the
		 * 											topology of the representation it is based on.
		 * @param 		  	pointCountByDimension	The number of property points ordered by dimension of the
		 * 											array to write.
		 * @param 		  	numArrayDimensions		The number of dimensions of the array to write.
		 * @param [in,out]	proxy			  		(Optional) The HDF proxy where to write the property
		 * 											points. It must be already opened for writing and won't
		 * 											be closed in this method. If @c nullptr (default value),
		 * 											then a default HDF proxy must be defined in the
		 * 											repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackArrayOfXyzPoints(double const * xyzPoints, unsigned long long const * pointCountByDimension, unsigned int numArrayDimensions, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Pushes back a reference to an existing (or a "to exist") HDF dataset in a particular HDF
		 * proxy. The reason can be that the values already exist in an external file (only HDF5 for
		 * now) or that the writing of the values in the external file is differed in time.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param [in]	proxy	   	The HDF5 proxy where the values are already or will be stored. If
		 * 							@c nullptr, then a default HDF proxy must be defined in the
		 * 							repository.
		 * @param 	  	datasetName	(Optional) The HDF5 dataset name where the values are stored. If
		 * 							empty, the dataset will be named the same as the dataset naming
		 * 							convention of fesapi :
		 * 							<tt>getHdfGroup() + "/points_patch" + patchIndex</tt>
		 *
		 * @returns	The name of the referenced HDF5 dataset.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string pushBackRefToExistingDataset(EML2_NS::AbstractHdfProxy* proxy, const std::string & datasetName = "") = 0;
		
		/**
		 * Checks if it is allowed to associate a given property kind to this property.
		 * TODO : think about how to validate such a property.
		 *
		 * @param [in]	pk	The local property kind to check.
		 *
		 * @returns	True if it is allowed, false if it is not.
		 */
		bool validatePropertyKindAssociation(EML2_NS::PropertyKind* pk) final {
			return true;
		}

		/**
		 * Checks if it is allowed to associate a given standard Energistics property kind to this property.
		 * TODO : think about how to validate such a property.
		 *
		 * @param 	pk	The standard Energistics property kind to check.
		 *
		 * @returns	True if it is allowed, false if it is not.
		 */
		bool validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind pk) final {
			return true;
		}

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT PointsProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractProperty(partialObject) {}

		/**
		 * Default constructor Set the relationship with an AbstractRepresentation and a local property
		 * type.
		 */
		PointsProperty() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PointsProperty(gsoap_resqml2_0_1::_resqml20__PointsProperty* fromGsoap) : RESQML2_NS::AbstractProperty(fromGsoap) {}
		PointsProperty(gsoap_eml2_3::resqml22__PointsProperty* fromGsoap) : RESQML2_NS::AbstractProperty(fromGsoap) {}

		virtual EML2_NS::AbstractHdfProxy* getValuesHdfProxyAndDatasetPathOfPatch(unsigned int patchIndex, std::string & datasetPath) const = 0;
	};
}
