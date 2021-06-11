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
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getRepresentationDor() const;

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
		DLL_IMPORT_OR_EXPORT unsigned int getElementCountPerValue() const;

		/**
		 * Gets the kind of elements on which the property values are attached to
		 *
		 * @returns	The kind of elements on which the property values are attached to.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::resqml22__IndexableElement getAttachmentKind() const;

		/**
		 * Gets the number of patches in this values property. It should be the same count as the patch
		 * count of the associated representation.
		 *
		 * @exception	std::out_of_range	If the patch count is strictly greater than unsigned int max
		 * 									value.
		 *
		 * @returns	The patch count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getPatchCount() const = 0;

		/**
		 * Get the values data type in the HDF dataset
		 *
		 * @returns	The data type of the values if successful, else @c UNKNOWN.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractObject::hdfDatatypeEnum getValuesHdfDatatype() const;

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
		DLL_IMPORT_OR_EXPORT unsigned int getValuesCountOfPatch(unsigned int patchIndex) const;

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
		DLL_IMPORT_OR_EXPORT unsigned int getValuesCountOfDimensionOfPatch(unsigned int dimIndex, unsigned int patchIndex) const;

		/**
		 * Gets the count of dimensions of the underlying HDF5 dataset of a given patch of this property.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	patchIndex	The index of the patch we want to count the dimensions from.
		 *
		 * @returns	The number of values, 0 otherwise.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getDimensionsCountOfPatch(unsigned int patchIndex) const;

		//*********************************************
		//************* PROPERTY SET ******************
		//*********************************************

		/**
		 * Gets all property sets which contain this property
		 *
		 * @returns A vector of all property sets which contain this property.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_NS::PropertySet *> getPropertySets() const;

		/**
		 * Gets the count of property sets which contain this property
		 *
		 * @exception	std::range_error	If the count of property sets is strictly greater than
		 * 									unsigned int max.
		 *
		 * @returns	The count of property sets which contain this property.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPropertySetCount() const;

		/**
		 * Gets a given property set taken from all property sets which contain this property
		 *
		 * @exception	std::out_of_range	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the property set we look for.
		 *
		 * @returns	The property set at @p index.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::PropertySet * getPropertySet(unsigned int index) const;
		
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
		DLL_IMPORT_OR_EXPORT void setLocalCrs(class AbstractLocal3dCrs * crs);

		/**
		 * Gets the local CRS which is associated to this property.
		 * 
		 * @returns The local CRS which is associated to the current property if exists, null if not 
		 * 			(usually for a property which is not CRS related).
		 */
		DLL_IMPORT_OR_EXPORT class AbstractLocal3dCrs* getLocalCrs() const;

		/**
		 * Gets the data object reference of the local CRS which is associated to this property
		 *
		 * @returns	Empty data object reference if no local CRS is associated to this property. Otherwise
		 * 			returns the data object reference of the associated local CRS.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getLocalCrsDor() const;

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
		DLL_IMPORT_OR_EXPORT std::vector<unsigned int> getRealizationIndices() const;

		/**
		 * Sets the realization indices of this property
		 *
		 * @param 	startRealizationIndex	The first realization index to set to this property.
		 * @param 	countRealizationIndices	The count of realization indices to set to this property.
		 */
		DLL_IMPORT_OR_EXPORT void setRealizationIndices(int64_t startRealizationIndex, int64_t countRealizationIndices);

		/**
		 * @brief	Sets the realization indices of this property
		 *
		 * @exception	std::invalid_argument	If @p realizationIndices is empty.
		 * @exception	std::invalid_argument	If the @p realizationIndices size is strictly greater
		 * 										than 1 in a RESQML 2.0.1 context.
		 * @exception	std::invalid_argument	If, in a RESQML 2.2 context, <tt>hdfProxy == nullptr</tt>
		 * 										and no default HDF proxy is defined in the repository.
		 * @exception	std::logic_error	 	If no supported gSOAP proxy is available.
		 *
		 * @param 		  	realizationIndices	The realization indices to set to this property.
		 * @param [in,out]	hdfProxy		  	(Optional) The HDF proxy where to store @p
		 * 										realizationIndices values. If @p nullptr (default), then
		 * 										the repository default HDF proxy will be used.
		 */
		DLL_IMPORT_OR_EXPORT void setRealizationIndices(const std::vector<unsigned int> & realizationIndices, EML2_NS::AbstractHdfProxy* hdfProxy = nullptr);

		//*********************************************
		//************ TIME DIMENSION *****************
		//*********************************************

		/**
		 * Sets the time series associated to the current property
		 *
		 * @exception	invalid_argument	If @p ts is null or if the current property has no time
		 * 									indices.
		 *
		 * @param [in]	ts	The time series to associate to this property
		 */
		DLL_IMPORT_OR_EXPORT void setTimeSeries(EML2_NS::TimeSeries * ts);

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
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getTimeSeriesDor() const;

		/**
		 * @brief	Sets the timestamps of this property by means of an index in a time series
		 *
		 * @exception	invalid_argument	If @p ts is null or if the current property has no time index.
		 *
		 * @param [in]	startTimeIndex  	The first time index to set to this property.
		 * @param [in]	countTimeIndices	The count of time indices to set to this property.
		 * @param [in]	ts					The time series which contains the timestamps of this
		 * 									property.
		 * @param [in]	useInterval			(Optional) When UseInterval is true, the values are
		 * 									associated with each time intervals between two consecutive time
		 * 									entries instead of each individual time entry. As a consequence
		 * 									the dimension of the value array corresponding to the time series
		 * 									is the number of entry in the series minus one.
		 */
		DLL_IMPORT_OR_EXPORT void setTimeIndices(uint64_t startTimeIndex, uint64_t countTimeIndices, EML2_NS::TimeSeries* ts, bool useInterval = false);

		/**
		 * Get the time index of this property in its associated time series
		 *
		 * @exception	std::invalid_argument	If this property does not have any time index.
		 *
		 * @returns	The time index of this property.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getTimeIndexStart() const;

		/**
		 * Get the time indices count of this property in its associated time series
		 *
		 * @returns	The time indices count of this property.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getTimeIndicesCount() const;

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
		virtual void loadTargetRelationships();

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
		virtual EML2_NS::AbstractHdfProxy* getDatasetOfPatch(unsigned int patchIndex, int64_t & nullValue, std::string & dsPath) const = 0;

		/**
		 * Gets the data object reference of the HDF proxy which is associated to a particular
		 * property patch.
		 *
		 * @param	patchIndex	The corresponding patch index of the HDF proxy to get.
		 * @returns	Empty data object reference if no HDF proxy is associated to this property patch.
		 * 			Otherwise returns the data object reference of the associated representation. Null
		 * 			should not occured since each property must be associated to a representation.
		 */
		virtual COMMON_NS::DataObjectReference getHdfProxyDor(unsigned int patchIndex) const = 0;
	};
}
