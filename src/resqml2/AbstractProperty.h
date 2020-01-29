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

/** . */
namespace RESQML2_0_1_NS
{
	/** A property set. */
	class PropertySet;
}

/** . */
namespace COMMON_NS
{
	/** A property kind. */
	class PropertyKind;
}

/** . */
namespace RESQML2_NS
{
	/** An abstract property. */
	class AbstractProperty: public COMMON_NS::AbstractObject
	{
	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
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

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~AbstractProperty() {}

		/**
		 * Set the representation which is associated to the current property.
		 *
		 * @param [in,out]	rep	If non-null, the rep.
		 */
		DLL_IMPORT_OR_EXPORT void setRepresentation(class AbstractRepresentation * rep);

		/**
		 * Gets representation dor
		 *
		 * @returns	null pointer if no representation is associated to this property. Otherwise return
		 * 			the data object reference of the associated representation.
		 */
		gsoap_resqml2_0_1::eml20__DataObjectReference* getRepresentationDor() const;

		/** Getter for the representation which supports this instance values. */
		DLL_IMPORT_OR_EXPORT class AbstractRepresentation* getRepresentation() const;

		/**
		 * Getter for the uuid of the representation which is described by this property
		 *
		 * @returns	The representation uuid.
		 */
		DLL_IMPORT_OR_EXPORT std::string getRepresentationUuid() const;

		/**
		 * Getter for the title of the representation which is described by this property
		 *
		 * @returns	The representation title.
		 */
		DLL_IMPORT_OR_EXPORT std::string getRepresentationTitle() const;

		/**
		 * Getter for the content type of the representation which is described by this property
		 *
		 * @returns	The representation content type.
		 */
		DLL_IMPORT_OR_EXPORT std::string getRepresentationContentType() const;

		/**
		 * Getter (in read only mode) of the element count per property value. If the property is a
		 * scalar one then it should be one. If it is a vectorial one, then it should be more than one.
		 * It is not possible to have some tensor property values (more dimensions than a vector).
		 *
		 * @returns	The element count per value.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getElementCountPerValue() const;

		/**
		 * Get the kind of elements the property values are attached to.
		 *
		 * @returns	The attachment kind.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__IndexableElements getAttachmentKind() const;

		/**
		 * Get all property sets which contain this property
		 *
		 * @returns	Null if it fails, else the property sets.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_NS::PropertySet *> getPropertySets() const;

		/**
		 * Gets property set count
		 *
		 * @returns	The property set count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPropertySetCount() const;

		/**
		 * Gets property set
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	Null if it fails, else the property set.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::PropertySet * getPropertySet(unsigned int index) const;
		
		//*********************************************
		//****** CRS ***********************
		//*********************************************

		/**
		 * Set the local CRS which is associated to the current property. you sould not set any CRS if
		 * your property is not CRS related.
		 *
		 * @param [in,out]	crs	If non-null, the crs.
		 */
		DLL_IMPORT_OR_EXPORT void setLocalCrs(class AbstractLocal3dCrs * crs);

		/**
		 * Getter for the local CRS which is associated to this property. Usually returns null except
		 * for a property which is CRS related.
		 */
		DLL_IMPORT_OR_EXPORT class AbstractLocal3dCrs* getLocalCrs() const;

		/**
		 * Gets local crs dor
		 *
		 * @returns	null pointer if no local CRS is associated to this property. Otherwise return the
		 * 			data object reference of the associated local CRS.
		 */
		gsoap_resqml2_0_1::eml20__DataObjectReference* getLocalCrsDor() const;

		/**
		 * Getter for the uuid of the local CRS which is associated to this property
		 *
		 * @returns	Empty string if no local CRS is associated to this property.
		 */
		DLL_IMPORT_OR_EXPORT std::string getLocalCrsUuid() const;

		/**
		 * Getter for the uuid of the local CRS which is associated to this property
		 *
		 * @returns	Empty string if no local CRS is associated to this property.
		 */
		DLL_IMPORT_OR_EXPORT std::string getLocalCrsTitle() const;

		//*********************************************
		//****** REALIZATION DIMENSION ****************
		//*********************************************

		/**
		 * Check if this property has a realization index.
		 *
		 * @returns	True if realization index, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasRealizationIndex() const;

		/**
		 * Get the realization index of this property. You should have verified before that this
		 * property actually has a realization index.
		 *
		 * @returns	The realization index.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getRealizationIndex() const;

		/**
		 * Set the realization index of this property
		 *
		 * @param 	realizationIndex	Zero-based index of the realization.
		 */
		DLL_IMPORT_OR_EXPORT void setRealizationIndex(ULONG64 realizationIndex);

		//*********************************************
		//****** TIME DIMENSION ***********************
		//*********************************************

		/**
		 * Set the representation which is associated to the current property.
		 *
		 * @param [in,out]	ts	If non-null, the ts.
		 */
		DLL_IMPORT_OR_EXPORT void setTimeSeries(class TimeSeries * ts);

		/**
		 * Getter for the time series which is associated to this property.
		 *
		 * @returns	Null if it fails, else the time series.
		 */
		DLL_IMPORT_OR_EXPORT TimeSeries* getTimeSeries() const;

		/**
		 * Gets time series dor
		 *
		 * @returns	null pointer if no time series is associated to this property. Otherwise return the
		 * 			data object reference of the associated time series.
		 */
		gsoap_resqml2_0_1::eml20__DataObjectReference* getTimeSeriesDor() const;

		/**
		 * Getter for the uuid of the time series which is associated to this property
		 *
		 * @returns	The time series uuid.
		 */
		DLL_IMPORT_OR_EXPORT std::string getTimeSeriesUuid() const;

		/**
		 * Getter for the uuid of the time series which is associated to this property
		 *
		 * @returns	The time series title.
		 */
		DLL_IMPORT_OR_EXPORT std::string getTimeSeriesTitle() const;

		/**
		 * Set the timestamp of this property by means of an index in a time series
		 *
		 * @param [in]	timeIndex	The index of the timestamp of the property in the time series.
		 * @param [in]	ts		 	The time series which contains the timestamp of this property.
		 */
		DLL_IMPORT_OR_EXPORT void setTimeIndex(const unsigned int & timeIndex, class TimeSeries * ts);

		/**
		 * Set the timestep of this property
		 *
		 * @param 	timeStep	The time step.
		 */
		DLL_IMPORT_OR_EXPORT void setTimeStep(const unsigned int & timeStep);

		/**
		 * Get the timestamp of this property
		 *
		 * @returns	maximum value of unsigned int is returned if no timestamp is allowed.
		 */
		DLL_IMPORT_OR_EXPORT time_t getTimestamp() const;

		/**
		 * Get the time index of this property in its assocaited time series
		 *
		 * @returns	The time index.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getTimeIndex() const;

		//*********************************************
		//****** PROP KIND ****************************
		//*********************************************

		/**
		 * Indicates if the property kind attached to this property is either from the standard catalog
		 * of Energistics or from a local property kind.
		 *
		 * @returns	True if associated to one standard energistics property kind, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAssociatedToOneStandardEnergisticsPropertyKind() const;

		/**
		 * Get the title of the property kind of this property
		 *
		 * @returns	The property kind description.
		 */
		DLL_IMPORT_OR_EXPORT std::string getPropertyKindDescription() const;

		/**
		 * Get the title of the property kind of this property
		 *
		 * @returns	The property kind as string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getPropertyKindAsString() const;

		/**
		 * Get the title of the parent of the property kind.
		 *
		 * @returns	The property kind parent as string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getPropertyKindParentAsString() const;

		/**
		 * Getter for the energistics property kind which is associated to this intance.
		 *
		 * @returns	The energistics property kind.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind() const;

		/**
		 * Set the property kind of the property to a local one.
		 *
		 * @param [in,out]	propKind	If non-null, the property kind.
		 */
		DLL_IMPORT_OR_EXPORT void setLocalPropertyKind(COMMON_NS::PropertyKind* propKind);

		/**
		 * Gets local property kind dor
		 *
		 * @returns	null pointer if no local property kind is associated to this property. Otherwise
		 * 			return the data object reference of the associated local property kind.
		 */
		gsoap_resqml2_0_1::eml20__DataObjectReference* getLocalPropertyKindDor() const;

		/**
		 * Get the uuid of the local property kind which is associated to this property.
		 *
		 * @returns	The local property kind uuid.
		 */
		DLL_IMPORT_OR_EXPORT std::string getLocalPropertyKindUuid() const;

		/**
		 * Get the title of the local property kind which is associated to this property.
		 *
		 * @returns	The local property kind title.
		 */
		DLL_IMPORT_OR_EXPORT std::string getLocalPropertyKindTitle() const;

		/**
		 * Getter for the local property kind which is associated to this instance. If nullptr is
		 * returned then it means this instance is associated to an energistics standard property kind.
		 *
		 * @returns	Null if it fails, else the local property kind.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::PropertyKind* getLocalPropertyKind() const;

		/**
		 * Check if the associated local property kind is allowed for this property.
		 *
		 * @param [in,out]	pk	If non-null, the pk.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		virtual bool validatePropertyKindAssociation(COMMON_NS::PropertyKind* pk) = 0;

		/**
		 * Check if the associated standard property kind is allowed for this property.
		 *
		 * @param 	pk	The pk.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		virtual bool validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind pk) = 0;

		/**
		 * Check if the associated property kind is allowed for this property.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		bool validate();

	protected:

		/** Loads target relationships */
		virtual void loadTargetRelationships();
	};
}
