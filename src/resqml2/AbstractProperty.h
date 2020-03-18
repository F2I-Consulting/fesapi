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

namespace RESQML2_0_1_NS
{
	class PropertySet;
}

namespace COMMON_NS
{
	class PropertyKind;
}

namespace RESQML2_NS
{
	/** Proxy class for an abstract property. */
	class AbstractProperty: public COMMON_NS::AbstractObject
	{
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

	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context */
		virtual ~AbstractProperty() {}

		/**
		 * Sets the representation which is associated to the current property
		 *
		 * @exception	std::invalid_argument	If @p rep is null.
		 *
		 * @param [in]	rep	The representation to associate to the current property.
		 */
		DLL_IMPORT_OR_EXPORT void setRepresentation(class AbstractRepresentation * rep);

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
		DLL_IMPORT_OR_EXPORT class AbstractRepresentation* getRepresentation() const;

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
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__IndexableElements getAttachmentKind() const;

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
		COMMON_NS::DataObjectReference getLocalCrsDor() const;

		//*********************************************
		//********** REALIZATION DIMENSION ************
		//*********************************************

		/**
		 * Checks if this property has a realization index. Realization index is used if the property is
		 * the result of a multi-realization process
		 *
		 * @returns	True if the property has a realization index, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasRealizationIndex() const;

		/**
		 * Gets the realization index of this property. Realization index is used if the property is the
		 * result of a multi-realization process. You should have checked before that this property
		 * actually has a realization index.
		 *
		 * @exception	std::invalid_argument	If this property has actually no realization index.
		 *
		 * @returns	The realization index.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getRealizationIndex() const;

		/**
		 * Sets the realization index of this property
		 *
		 * @param 	realizationIndex	The realization index to set to this property.
		 */
		DLL_IMPORT_OR_EXPORT void setRealizationIndex(ULONG64 realizationIndex);

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
		DLL_IMPORT_OR_EXPORT void setTimeSeries(class TimeSeries * ts);

		/**
		 * Gets the time series which is associated to this property
		 *
		 * @returns	Null pointer if no time series is associated to this property. Otherwise returns the
		 * 			associated time series.
		 */
		DLL_IMPORT_OR_EXPORT TimeSeries* getTimeSeries() const;

		/**
		 * Gets the data object reference of the time series associated to this property
		 *
		 * @returns	Empty data object reference if no time series is associated to this property. Otherwise returns the
		 * 			data object reference of the associated time series.
		 */
		COMMON_NS::DataObjectReference getTimeSeriesDor() const;

		/**
		 * Sets the time stamp of this property by means of an index in a time series
		 *
		 * @exception	invalid_argument	If @p ts is null or if the current property has no time
		 * 									indices.
		 *
		 * @param [in]	timeIndex	The index of the timestamp of the property in the time series.
		 * @param [in]	ts		 	The time series which contains the timestamp of this property.
		 */
		DLL_IMPORT_OR_EXPORT void setTimeIndex(unsigned int timeIndex, class TimeSeries* ts);

		/**
		 * Sets the time step of this property. The time step indicates that the property is the output
		 * of a specific time step from a flow simulator. Time step is metadata that makes sense in the
		 * context of a specific simulation run, and should not be confused with the time index.
		 *
		 * @param 	timeStep	The time step to set to this property.
		 */
		DLL_IMPORT_OR_EXPORT void setTimeStep(unsigned int timeStep);

		/**
		 * Gets the time stamp of this property
		 *
		 * @exception	std::invalid_argument	If this property does not have any time stamp.
		 *
		 * @returns	The time stamp of this property.
		 */
		DLL_IMPORT_OR_EXPORT time_t getTimestamp() const;

		/**
		 * Get the time index of this property in its associated time series
		 *
		 * @exception	std::invalid_argument	If this property does not have any time stamp.
		 *
		 * @returns	The time index of this property.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getTimeIndex() const;

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
		 * Gets the Energistics property kind which is associated to this intance
		 *
		 * @exception	std::invalid_argument	If the property kind of this property is not an
		 * 										Energistics one.
		 *
		 * @returns	The Energistics property kind.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind() const;

		/**
		 * Sets the property kind of this property to a local one
		 *
		 * @exception	std::invalid_argument	If @p propKind is null.
		 *
		 * @param [in]	propKind	The local property kind to set to this property.
		 */
		DLL_IMPORT_OR_EXPORT void setLocalPropertyKind(COMMON_NS::PropertyKind* propKind);

		/**
		 * Gets the data object reference of the local property kind associated to this property
		 *
		 * @exception	std::invalid_argument	If the property kind of this property is not a local one.
		 *
		 * @returns	Empty data object reference if no local property kind is associated to this property.
		 * 			Otherwise return the data object reference of the associated local property kind.
		 */
		COMMON_NS::DataObjectReference getLocalPropertyKindDor() const;

		/**
		 * Gets the local property kind which is associated to this instance
		 *
		 * @exception	std::invalid_argument	If the property kind of this property is not a local one.

		 * @returns	A pointer to the local property kind.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::PropertyKind* getLocalPropertyKind() const;

		/**
		 * Checks if it is allowed to associate a given local property kind to this property.
		 *
		 * @param [in]	pk	The local property kind to check.
		 *
		 * @returns	True if it is allowed, false if it is not.
		 */
		virtual bool validatePropertyKindAssociation(COMMON_NS::PropertyKind* pk) = 0;

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

		/** Loads target relationships */
		virtual void loadTargetRelationships();
	};
}
