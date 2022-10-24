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

#include "../common/AbstractObject.h"

namespace EML2_NS
{
	class AbstractHdfProxy;
	class AbstractLocal3dCrs;
	class PropertyKind;
	class TimeSeries;
}

namespace RESQML2_NS
{
	class AbstractRepresentation;

	/** @brief	Proxy class for an abstract property. */
	class AbstractProperty: public COMMON_NS::AbstractObject
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context */
		virtual ~AbstractProperty() = default;

		/**
		 * Sets the representation which is associated to the current property
		 *
		 * @exception	std::invalid_argument	If @p rep is null.
		 *
		 * @param [in]	rep	The representation to associate to the current property.
		 */
		DLL_IMPORT_OR_EXPORT void setRepresentation(AbstractRepresentation * rep);

		/**
		 * Gets the data object reference of the representation which is associated to the current
		 * property
		 *
		 * @returns	Empty data object reference if no representation is associated to this property.
		 * 			Otherwise returns the data object reference of the associated representation. Null
		 * 			should not occured since each property must be associated to a representation.
		 */
		COMMON_NS::DataObjectReference getRepresentationDor() const;

		/**  
		 * Gets the representation which is associated to the current property. That is to say the one
		 * which supports this instance values, also called supporting representation
		 * 
		 * @returns The representation which is associated to the current property.
		 */
		DLL_IMPORT_OR_EXPORT AbstractRepresentation* getRepresentation() const;

		/**
		 * Gets the count of elements per property value. If the property is a scalar one then it should
		 * be one. If it is a vectorial one, then it should be more than one. It is not possible to have
		 * some tensor property values (more dimensions than a vector)
		 *
		 * @returns	The element count per value.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getElementCountPerValue() const;

		/**
		 * Gets the kind of elements on which the property values are attached to
		 *
		 * @returns	The kind of elements on which the property values are attached to.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__IndexableElement getAttachmentKind() const;

		/**
		 * Gets the number of patches in this values property. It should be the same count as the patch
		 * count of the associated representation.
		 *
		 * @exception	std::out_of_range	If the patch count is strictly greater than unsigned int max
		 * 									value.
		 *
		 * @returns	The patch count.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getPatchCount() const = 0;

		/**
		 * Get the values data type in the HDF dataset
		 *
		 * @returns	The data type of the values if successful, else @c UNKNOWN.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::AbstractObject::numericalDatatypeEnum getValuesHdfDatatype() const = 0;

		/**
		 * Gets the count of all values contained into the underlying HDF5 dataset of a given patch of
		 * this property.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	patchIndex	The index of the patch we want to count the values from.
		 *
		 * @returns	The count of values of the @p patchIndex patch.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getValuesCountOfPatch(uint64_t patchIndex) const;

		/**
		 * Gets the count of values on a specific dimension of the underlying HDF5 dataset of a given
		 * patch of this property.
		 *
		 * @exception	std::out_of_range	If @p dimIndex is strictly greater than dimension count.
		 * @exception	std::range_error 	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	dimIndex  	The index of the dimension we want to count the values from.
		 * @param 	patchIndex	The index of the patch we want to count the values from.
		 *
		 * @returns	The count of values in the @p dimIndex dimension of @p patchIndex patch.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getValuesCountOfDimensionOfPatch(uint64_t dimIndex, uint64_t patchIndex) const = 0;

		/**
		 * Gets the count of dimensions of the underlying HDF5 dataset of a given patch of this property.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	patchIndex	The index of the patch we want to count the dimensions from.
		 *
		 * @returns	The number of values, 0 otherwise.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getDimensionsCountOfPatch(uint64_t patchIndex) const = 0;

		//*********************************************
		//************* PROPERTY SET ******************
		//*********************************************

		/**
		 * Gets all property sets which contain this property
		 *
		 * @returns A vector of all property sets which contain this property.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::PropertySet *> getPropertySets() const;

		/**
		 * Gets the count of property sets which contain this property
		 *
		 * @exception	std::range_error	If the count of property sets is strictly greater than
		 * 									unsigned int max.
		 *
		 * @returns	The count of property sets which contain this property.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getPropertySetCount() const;

		/**
		 * Gets a given property set taken from all property sets which contain this property
		 *
		 * @exception	std::out_of_range	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the property set we look for.
		 *
		 * @returns	The property set at @p index.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PropertySet* getPropertySet(uint64_t index) const;
		
		//*********************************************
		//****************** CRS **********************
		//*********************************************

		/**
		 * Sets the local CRS which is associated to the current property. You should not set any CRS if
		 * your property is not CRS related
		 *
		 * @exception	std::invalid_argument	If @p crs is null.
		 *
		 * @param [in]	crs	The local CRS to associate with the current property.
		 */
		DLL_IMPORT_OR_EXPORT void setLocalCrs(EML2_NS::AbstractLocal3dCrs * crs);

		/**
		 * Gets the local CRS which is associated to this property.
		 * 
		 * @returns The local CRS which is associated to the current property if exists, null if not 
		 * 			(usually for a property which is not CRS related).
		 */
		DLL_IMPORT_OR_EXPORT EML2_NS::AbstractLocal3dCrs* getLocalCrs() const;

		/**
		 * Gets the data object reference of the local CRS which is associated to this property
		 *
		 * @returns	Empty data object reference if no local CRS is associated to this property. Otherwise
		 * 			returns the data object reference of the associated local CRS.
		 */
		COMMON_NS::DataObjectReference getLocalCrsDor() const;

		//*********************************************
		//********** REALIZATION DIMENSION ************
		//*********************************************

		/**
		 * Checks if this property has at least one realization index. Realization index is used if the property is
		 * the result of a multi-realization process.
		 * Reamrk : v2.0.1 is constrained to have a maximum of one realisation index
		 *
		 * @returns	True if the property has at least one realization index, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasRealizationIndices() const;

		/**
		 * Gets the realization index of this property. Realization index is used if the property is the
		 * result of a multi-realization process. You should have checked before that this property
		 * actually has a realization index.
		 *
		 * @exception	std::invalid_argument	If this property has actually no realization index.
		 *
		 * @returns	The realization index.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<int64_t> getRealizationIndices() const;

		/**
		 * Sets the realization indices of this property
		 *
		 * @exception	std::invalid_argument	If the @p realizationIndices size is strictly greater
		 * 										than 1 in a RESQML 2.0.1 context.
		 * @exception	std::logic_error	 	If no supported gSOAP proxy is available.
		 *
		 * @param 		  	realizationIndices	The realization indices to set to this property. If empty, remove all realization indices from the property.
		 */
		DLL_IMPORT_OR_EXPORT void setRealizationIndices(std::vector<int64_t> realizationIndices);

		//*********************************************
		//************ TIME DIMENSION *****************
		//*********************************************

		/**
		 * Sets the time series associated to the current property
		 * RESQML2.0.1	:	Must be used with and before to call setSingleTimestamp.
							Properties in v2.0.1 cannot contain values for a whole time series but only for a single timestamp of a time series.
		 * RESQML2.2	:	If, used the property must contain values for the whole time series. It cannot be used with setSingleTimestamp.
		 *
		 * @exception	invalid_argument	If @p ts is null or if the current property has no time
		 * 									indices.
		 *
		 * @param [in]	ts	The time series to associate to this property
		 */
		DLL_IMPORT_OR_EXPORT void setTimeSeries(EML2_NS::TimeSeries * ts);

		/**
		 * Set a single associated timestamp for this property.
		 * RESQML2.0.1	: Must be used with and after setTimeSeries.
		 * RESQML2.2	: The property must contain values for a single timestamp (as in 2.0.1). It cannot be used with setTimeSeries.
		 *
		 * @exception	invalid_argument	Regarding RESQML2.0.1, this method cannot be called if setTimeSeries has not been called before.
		 *
		 * @param [in]	timestamp	The single timestamps to associate to this property
		 * @param [in]	yearOffset	Indicates that the dateTime attribute must be translated according to this value.
		 */
		DLL_IMPORT_OR_EXPORT void setSingleTimestamp(time_t timestamp, LONG64 yearOffset = 0);

		/**
		 * Get a single associated timestamp for this property.
		 *
		 * @return	-1 if there is not a single timestamp related to this property meaning that no timestamp is present or more than one (i.e. a whole time series)
		 */
		DLL_IMPORT_OR_EXPORT time_t getSingleTimestamp() const;

		/**
		 * Gets the time series which is associated to this property
		 *
		 * @returns	Null pointer if no time series is associated to this property. Otherwise returns the
		 * 			associated time series.
		 */
		DLL_IMPORT_OR_EXPORT EML2_NS::TimeSeries* getTimeSeries() const;

		/**
		 * Gets the data object reference of the time series associated to this property
		 *
		 * @returns	Empty data object reference if no time series is associated to this property. Otherwise returns the
		 * 			data object reference of the associated time series.
		 */
		COMMON_NS::DataObjectReference getTimeSeriesDor() const;

		/**
		 * Check if the values are given at each time index or between each time index.
		 */
		DLL_IMPORT_OR_EXPORT bool useInterval() const;

		//*********************************************
		//****** PROP KIND ****************************
		//*********************************************

		/**
		 * Indicates if the property kind attached to this property is either from the standard catalog
		 * of Energistics or from a local property kind
		 *
		 * @returns	True if associated to one standard Energistics property kind, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAssociatedToOneStandardEnergisticsPropertyKind() const;

		/**
		 * Gets the description of the property kind of this property
		 *
		 * @exception	std::invalid_argument	If the property kind is a standard Energistics one and
		 * 										the property kind mapping file is not loaded.
		 *
		 * @returns	The property kind description.
		 */
		DLL_IMPORT_OR_EXPORT std::string getPropertyKindDescription() const;

		/**
		 * Gets the title of the property kind of this property
		 *
		 * @returns	The property kind title.
		 */
		DLL_IMPORT_OR_EXPORT std::string getPropertyKindAsString() const;

		/**
		 * Get the title of the parent property kind of this property
		 *
		 * @exception	std::invalid_argument	If the property kind is a standard Energistics one and
		 * 										the property kind mapping file is not loaded.
		 *
		 * @returns	The parent property kind title.
		 */
		DLL_IMPORT_OR_EXPORT std::string getPropertyKindParentAsString() const;

		/**
		 * Sets the property kind of this property to a local one
		 *
		 * @exception	std::invalid_argument	If @p propKind is null.
		 *
		 * @param [in]	propKind	The local property kind to set to this property.
		 */
		DLL_IMPORT_OR_EXPORT void setPropertyKind(EML2_NS::PropertyKind* propKind);

		/**
		 * Gets the data object reference of the property kind associated to this property
		 *
		 * @exception	std::invalid_argument	If the property kind of this property is not a local one.
		 *
		 * @returns	Empty data object reference if no property kind is associated to this property.
		 * 			Otherwise return the data object reference of the associated local property kind.
		 */
		COMMON_NS::DataObjectReference getPropertyKindDor() const;

		/**
		 * Gets the local property kind which is associated to this instance
		 *
		 * @exception	std::invalid_argument	If the property kind of this property is not a local one.

		 * @returns	A pointer to the property kind.
		 */
		DLL_IMPORT_OR_EXPORT EML2_NS::PropertyKind* getPropertyKind() const;

		/**
		 * Checks if it is allowed to associate a given property kind to this property.
		 *
		 * @param [in]	pk	The local property kind to check.
		 *
		 * @returns	True if it is allowed, false if it is not.
		 */
		virtual bool validatePropertyKindAssociation(EML2_NS::PropertyKind* pk) = 0;

		/**
		 * Checks if it is allowed to associate a given standard Energistics property kind to this property.
		 *
		 * @param 	pk	The standard Energistics property kind to check.
		 *
		 * @returns	True if it is allowed, false if it is not.
		 */
		virtual bool validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind pk) = 0;

		/**
		 * Checks if the associated property kind is allowed for this property.
		 *
		 * @returns	True if it is allowed, false if it is not.
		 */
		bool validate();

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT AbstractProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/** Default constructor */
		AbstractProperty() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractProperty(gsoap_resqml2_0_1::resqml20__AbstractProperty* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}
		AbstractProperty(gsoap_eml2_3::resqml22__AbstractProperty* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/** Loads target relationships */
		virtual void loadTargetRelationships() override;

		/**
		 * Gets the Energistics property kind which is associated to this intance
		 *
		 * @exception	std::invalid_argument	If the property kind of this property is not an
		 * 										Energistics one.
		 *
		 * @returns	The Energistics property kind.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind201() const;

		/**
		 * Get the HDF Proxy which contains the property values of a particular patch.
		 *
		 * @param 		  	patchIndex	The corresponding patch index of the dataset to get.
		 * @param [out]		nullValue 	If possible, this function will set this parameter to the RESQML
		 * 								null value of the dataset. If not, it will return long.min.
		 * @param [out]		nullValue 	this function will set this parameter to the RESQML
		 * 								dataset path in the HDF file.
		 *
		 * @returns	Null if it fails, else the HDF Proxy of patch.
		 */
		virtual EML2_NS::AbstractHdfProxy* getDatasetOfPatch(uint64_t patchIndex, int64_t & nullValue, std::string & dsPath) const = 0;

		/**
		 * Gets the data object reference of the HDF proxy which is associated to a particular
		 * property patch.
		 *
		 * @param	patchIndex	The corresponding patch index of the HDF proxy to get.
		 * @returns	Empty data object reference if no HDF proxy is associated to this property patch.
		 * 			Otherwise returns the data object reference of the associated representation. Null
		 * 			should not occured since each property must be associated to a representation.
		 */
		virtual COMMON_NS::DataObjectReference getHdfProxyDor(uint64_t patchIndex) const = 0;
	};
}
