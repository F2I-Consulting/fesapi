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

namespace RESQML2_0_1_NS
{
	/* Information specific to one categorical property. Contains discrete integer.
	* This type of property is associated either as:
	* an internally stored index to a string through a lookup mapping.
	* an internally stored double to another double value through an explicitly provided table.
	*/
	class CategoricalProperty : public RESQML2_NS::AbstractValuesProperty
	{
	protected:

		/**
		* Default constructor
		*/
		CategoricalProperty() {}

	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT CategoricalProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractValuesProperty(partialObject) {}

		/**
		* Creates an instance of this class which is of a well known Energistics property kind.
		* @param rep						The representation which supports these property values.
		* @param guid						The guid to set to the fault. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param dimension					The dimension of each value (scalar properties == 1).
		* @param attachmentKind				The topological orbit which support each value.
		* @param strLookup					The string lookup which defines the possible string values and their keys.
		* @param energisticsPropertyKind	The property kind of these property values which must be defined in the standard energistics property type dictionary.
		*/
		CategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind,
			class StringTableLookup* strLookup, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		/**
		* Creates an instance of this class which is of a local property kind.
		* @param rep						The representation which supports these property values.
		* @param guid						The guid to set to the fault. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param dimension					The dimension of each value (scalar properties == 1).
		* @param attachmentKind				The topological orbit which support each value.
		* @param strLookup					The string lookup which defines the possible string values and their keys.
		* @param localPropKind				The property kind of these property values which must be defined in the EPC document as a local property kind.
		*/
		CategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind,
			class StringTableLookup* strLookup, COMMON_NS::PropertyKind * localPropKind);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		CategoricalProperty(gsoap_resqml2_0_1::_resqml20__CategoricalProperty* fromGsoap): AbstractValuesProperty(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~CategoricalProperty() {}

		/**
		* Add a 1d array of explicit long values to the property values.
		* @param values					All the property values to set ordered according to the topology of the representation it is based on.
		* @param valueCount				The number of values to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array1dOfValues(const LONG64 * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy, LONG64 nullValue);

		/**
		* Add a 2d array of explicit long values to the property values.
		* @param values					All the property values to set ordered according to the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly J dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array2dOfValues(const LONG64 * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy, LONG64 nullValue);

		/**
		* Add a 3d array of explicit long values to the property values.
		* @param values					All the property values to set ordered according to the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array3dOfValues(const LONG64 * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy, LONG64 nullValue);

		/**
		* Add an array (potentially multi dimensions) of long values to the property values which will be stored in the HDF file identified by its HDF proxy.
		* @param values					All the property values to set ordered according to the topology of the representation it is based on.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param numDimensionsInArray	The number of dimensions in the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5ArrayOfValues(const LONG64 * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, LONG64 nullValue);

		/**
		* Add a 1d array of explicit unsigned short values to the property values.
		* @param values					All the property values to set ordered according to the topology of the representation it is based on.
		* @param valueCount				The number of values to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5Array1dOfValues(const unsigned short * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy, unsigned short nullValue);

		/**
		* Add a 2d array of explicit unsigned short values to the property values.
		* @param values					All the property values to set ordered according to the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly J dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5Array2dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy, unsigned short nullValue);

		/**
		* Add a 3d array of explicit unsigned short values to the property values.
		* @param values					All the property values to set ordered according to the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5Array3dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy, unsigned short nullValue);

		/**
		* Add an array (potentially multi dimensions) of unsigned short values to the property values which will be stored in the HDF file identified by its HDF proxy.
		* @param values					All the property values to set ordered according to the topology of the representation it is based on.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param numDimensionsInArray	The number of dimensions in the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5ArrayOfValues(const unsigned short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, unsigned short nullValue);

		DLL_IMPORT_OR_EXPORT std::string pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & dataset = "", LONG64 nullValue = (std::numeric_limits<LONG64>::max)());

		/**
		* Get the string lookup which is associated to this categorical property values.
		*/
		DLL_IMPORT_OR_EXPORT class StringTableLookup* getStringLookup();

		/**
		* Get the string lookup uuid which is associated to this categorical property values.
		*/
		DLL_IMPORT_OR_EXPORT std::string getStringLookupUuid() const;

		/**
		* Check if the associated local property kind is allowed for this property.
		*/
		bool validatePropertyKindAssociation(COMMON_NS::PropertyKind* pk);

		/**
		* Check if the associated standard property kind is allowed for this property.
		*/
		bool validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind pk);

		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		* Get the standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

	protected:
		virtual void loadTargetRelationships();
	};
}
