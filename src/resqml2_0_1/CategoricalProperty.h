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

#include "../resqml2/AbstractValuesProperty.h"

/** . */
namespace RESQML2_0_1_NS
{
	/**
	 * Proxy class for a categorical property. It contains discrete integers. This type of property
	 * is associated either: as an internally stored index to a string through a lookup mapping, or
	 * as an internally stored double to another double value through an explicitly provided table.
	 */
	class CategoricalProperty : public RESQML2_NS::AbstractValuesProperty
	{
	protected:

		/** Default constructor */
		CategoricalProperty() {}

	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT CategoricalProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractValuesProperty(partialObject) {}

		/**
		 * Creates a categorical property which is of a well known Energistics property kind
		 *
		 * @exception	std::invalid_argument	If @p rep or @p strLookup is null.
		 *
		 * @param [in]	rep					   	The representation on which this property is attached to.
		 * 										It cannot be null.
		 * @param 	  	guid				   	The guid to set to the property. If empty then a new guid
		 * 										will be generated.
		 * @param 	  	title				   	The title to set to the property. If empty then
		 * 										\"unknown\" title will be set.
		 * @param 	  	dimension			   	The dimension of each value of this property. Dimension
		 * 										is 1 for a scalar property.
		 * @param 	  	attachmentKind		   	The topological element on which the property values are
		 * 										attached to.
		 * @param [in]	strLookup			   	The string lookup which defines the possible string
		 * 										values and their keys.
		 * @param 	  	energisticsPropertyKind	The property kind of these property values which must be
		 * 										defined in the standard Energistics property type
		 * 										dictionary.
		 */
		CategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind,
			class StringTableLookup* strLookup, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		/**
		 * Creates a categorical property which is of a local property kind
		 *
		 * @exception	std::invalid_argument	If @p rep, @p strLookup or @p localPropKind is null.
		 *
		 * @param [in]	rep			  	The representation on which this property is attached to. It
		 * 								cannot be null.
		 * @param 	  	guid		  	The guid to set to the property. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the property. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	dimension	  	The dimension of each value of this property. Dimension is 1 for
		 * 								a scalar property.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param [in]	strLookup	  	The string lookup which defines the possible string values and
		 * 								their keys. It cannot be null.
		 * @param [in]	localPropKind 	The property kind of these property values which must be defined
		 * 								in the EPC document as a local property kind. It cannot be null.
		 */
		CategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind,
			class StringTableLookup* strLookup, COMMON_NS::PropertyKind * localPropKind);

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		CategoricalProperty(gsoap_resqml2_0_1::_resqml20__CategoricalProperty* fromGsoap): AbstractValuesProperty(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~CategoricalProperty() {}

		/**
		 * Adds a 1d array of explicit long values to the property values. It will
		 * be stored in the HDF5 file identified by its HDF proxy.
		 *
		 * @param 	  	values	  	All the property values to set ordered according to the topology of
		 * 							the representation it is based on.
		 * @param 	  	valueCount	The number of values to write.
		 * @param [in]	proxy	  	The HDF proxy where to write the property values. It must be already
		 * 							opened for writing and won't be closed in this method. If null then a
		 * 							default HDF proxy must be defined in the data object repository.
		 * @param 	  	nullValue 	The null value.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array1dOfValues(const LONG64 * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy, LONG64 nullValue);

		/**
		 * Adds a 2d array of explicit long values to the property values. It will
		 * be stored in the HDF5 file identified by its HDF proxy.
		 *
		 * @param 	  	values				  	All the property values to set ordered according to the
		 * 										topology of the representation it is based on.
		 * @param 	  	valueCountInFastestDim	The number of values to write in the fastest dimension
		 * 										(mainly I dimension).
		 * @param 	  	valueCountInSlowestDim	The number of values to write in the slowest dimension
		 * 										(mainly J dimension).
		 * @param [in]	proxy				  	The HDF proxy where to write the property values. It must
		 * 										be already opened for writing and won't be closed in this
		 * 										method. If null then a default HDF proxy must be defined
		 * 										in the data object repository.
		 * @param 	  	nullValue			  	The null value.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array2dOfValues(const LONG64 * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy, LONG64 nullValue);

		/**
		 * Adds a 3d array of explicit long values to the property values. It will
		 * be stored in the HDF5 file identified by its HDF proxy.
		 *
		 * @param 	  	values				  	All the property values to set ordered according to the
		 * 										topology of the representation it is based on.
		 * @param 	  	valueCountInFastestDim	The number of values to write in the fastest dimension
		 * 										(mainly I dimension).
		 * @param 	  	valueCountInMiddleDim 	The number of values to write in the middle dimension
		 * 										(mainly J dimension).
		 * @param 	  	valueCountInSlowestDim	The number of values to write in the slowest dimension
		 * 										(mainly K dimension).
		 * @param [in]	proxy				  	The HDF proxy where to write the property values. It must
		 * 										be already opened for writing and won't be closed in this
		 * 										method. If null then a default HDF proxy must be defined
		 * 										in the data object repository.
		 * @param 	  	nullValue			  	The null value.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array3dOfValues(const LONG64 * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy, LONG64 nullValue);

		/**
		 * Adds an nd array of long values to the property values. It will be stored in the HDF5 file
		 * identified by its HDF proxy.
		 *
		 * @param 	  	values					All the property values to set ordered according to the
		 * 										topology of the representation it is based on.
		 * @param [in]	numValues				The number of property values ordered by dimension of the
		 * 										array to write.
		 * @param 	  	numDimensionsInArray	The number of dimensions in the array to write.
		 * @param [in]	proxy					The HDF proxy where to write the property values. It must
		 * 										be already opened for writing and won't be closed in this
		 * 										method. If null then a default HDF proxy must be defined in
		 * 										the data object repository.
		 * @param 	  	nullValue				The null value.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5ArrayOfValues(const LONG64 * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, LONG64 nullValue);

		/**
		 * Add a 1d array of explicit unsigned short values to the property values. It will be stored
		 * in the HDF5 file identified by its HDF proxy.
		 *
		 * @param 	  	values	  	All the property values to set ordered according to the topology of
		 * 							the representation it is based on.
		 * @param 	  	valueCount	The number of values to write.
		 * @param [in]	proxy	  	The HDF proxy where to write the property values. It must be already
		 * 							opened for writing and won't be closed in this method. If null then a
		 * 							default HDF proxy must be defined in the data object repository.
		 * @param 	  	nullValue 	The null value.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5Array1dOfValues(const unsigned short * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy, unsigned short nullValue);

		/**
		 * Add a 2d array of explicit unsigned short values to the property values. It will be stored in
		 * the HDF5 file identified by its HDF proxy.
		 *
		 * @param 	  	values				  	All the property values to set ordered according to the
		 * 										topology of the representation it is based on.
		 * @param 	  	valueCountInFastestDim	The number of values to write in the fastest dimension
		 * 										(mainly I dimension).
		 * @param 	  	valueCountInSlowestDim	The number of values to write in the slowest dimension
		 * 										(mainly J dimension).
		 * @param [in]	proxy				  	The HDF proxy where to write the property values. It must
		 * 										be already opened for writing and won't be closed in this
		 * 										method. If null then a default HDF proxy must be defined
		 * 										in the data object repository.
		 * @param 	  	nullValue			  	The null value.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5Array2dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy, unsigned short nullValue);

		/**
		 * Add a 3d array of explicit unsigned short values to the property values. It will be stored in
		 * the HDF5 file identified by its HDF proxy.
		 *
		 * @param 	  	values				  	All the property values to set ordered according to the
		 * 										topology of the representation it is based on.
		 * @param 	  	valueCountInFastestDim	The number of values to write in the fastest dimension
		 * 										(mainly I dimension).
		 * @param 	  	valueCountInMiddleDim 	The number of values to write in the middle dimension
		 * 										(mainly J dimension).
		 * @param 	  	valueCountInSlowestDim	The number of values to write in the slowest dimension
		 * 										(mainly K dimension).
		 * @param [in]	proxy				  	The HDF proxy where to write the property values. It must
		 * 										be already opened for writing and won't be closed in this
		 * 										method. If null then a default HDF proxy must be defined
		 * 										in the data object repository.
		 * @param 	  	nullValue			  	The null value.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5Array3dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy, unsigned short nullValue);

		/**
		 * Add an nd array of unsigned short values to the property values. It will be stored in the
		 * HDF5 file identified by its HDF proxy.
		 *
		 * @param 	  	values					All the property values to set ordered according to the
		 * 										topology of the representation it is based on.
		 * @param [in]	numValues				The number of property values ordered by dimension of the
		 * 										array to write.
		 * @param 	  	numDimensionsInArray	The number of dimensions in the array to write.
		 * @param [in]	proxy					The HDF proxy where to write the property values. It must
		 * 										be already opened for writing and won't be closed in this
		 * 										method. If null then a default HDF proxy must be defined in
		 * 										the data object repository.
		 * @param 	  	nullValue				The null value.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5ArrayOfValues(const unsigned short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, unsigned short nullValue);

		/**
		 * Pushes back a new patch of integer values for this property where the values have not to be
		 * written in the HDF5 file. The reason can be that the values already exist in an external file
		 * (only HDF5 for now) or that the writing of the values in the external file is differed in
		 * time.
		 *
		 * @param [in]	hdfProxy 	The HDF5 proxy where the values are already or will be stored. If
		 * 							null then a default HDF proxy must be defined in the data object
		 * 							repository.
		 * @param 	  	dataset  	(Optional) If not provided during the method call, the dataset will
		 * 							be named the same as the dataset naming convention of fesapi:
		 * 							<tt>"/RESQML/" + prop-&gt;uuid + "/values_patch" + patchIndex</tt>
		 * @param 	  	nullValue	(Optional) Only relevant for integer hdf5 datasets. Indeed, RESQML
		 * 							(and fesapi) forces null value for floating point to be NaN value.
		 *
		 * @returns	The name of the HDF5 dataset.
		 */
		DLL_IMPORT_OR_EXPORT std::string pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & dataset = "", LONG64 nullValue = (std::numeric_limits<LONG64>::max)());

		/**   
		 * Get the string lookup which is associated to this categorical property values. 
		 * @returns A pointer to the string lookup which is associated to this categorical property
		 * 			values.
		 */
		DLL_IMPORT_OR_EXPORT class StringTableLookup* getStringLookup();

		/**
		 * Get the UUID of the string lookup which is associated to this categorical property values.
		 *
		 * @returns	The string lookup UUID.
		 */
		DLL_IMPORT_OR_EXPORT std::string getStringLookupUuid() const;

		/**
		 * Checks if it is allowed to associate a given local property kind to this property.
		 *
		 * @exception	std::invalid_argument	If @p pk is null.
		 *
		 * @param [in]	pk	The local property kind to check.
		 *
		 * @returns	True if it is allowed, false if it is not.
		 */
		bool validatePropertyKindAssociation(COMMON_NS::PropertyKind* pk);

		/**
		 * Checks if it is allowed to associate a given standard Energistics property kind to this
		 * property.
		 *
		 * @param 	pk	The standard Energistics property kind to check.
		 *
		 * @returns	True if it is allowed, false if it is not.
		 */
		bool validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind pk);

		/** The standard XML tag without XML namespace for serializing this data object */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Gets the standard XML tag without XML namespace for serializing this data object
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

	protected:
		/** Loads target relationships */
		virtual void loadTargetRelationships();
	};
}
