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

#include <limits>
#include "AbstractProperty.h"

namespace RESQML2_NS
{
	class AbstractValuesProperty : public AbstractProperty
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT AbstractValuesProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractProperty(partialObject) {}

		/**
		* Default constructor
		* Set the relationship with an AbstractRepresentation and a local property type.
		*/
		AbstractValuesProperty() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractValuesProperty(gsoap_resqml2_0_1::resqml20__AbstractValuesProperty* fromGsoap) : RESQML2_NS::AbstractProperty(fromGsoap) {}

		/**
		* Get the dataset which contains the property values of a particular patch.
		* @param patchIndex	The corresponding patch index of the dataset to get.
		* @param nullValue	If possible, this function will set this parameter to the RESQML null value of the dataset. If not, it will return long.min
		*/
		gsoap_resqml2_0_1::eml20__Hdf5Dataset const * getDatasetOfPatch(unsigned int patchIndex, LONG64 & nullValue) const;

		void loadTargetRelationships();

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractValuesProperty() {}

		/**
		* Get the number of patches in this values property. It should be the same count as the patch count of the associated representation.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const;

		/**
		* Get the values datatype in the HDF dataset
		*/
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractObject::hdfDatatypeEnum getValuesHdfDatatype() const;

		/**
		* Get the count of all values contained into the underlying HDF5 dataset of this property for a particular patch.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getValuesCountOfPatch (unsigned int patchIndex) const;

		/**
		* Get the count of values on a specific dimension of the underlying HDF5 dataset of this property.
		* @param dimIndex	The index of the dimension we want to know the values count in this property.
		* @param patchIndex	The index of the patch we want to know the values count in this property.
		* @return			The number of values, 0 otherwise.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getValuesCountOfDimensionOfPatch(unsigned int dimIndex, unsigned int patchIndex) const;

		/**
		* Get the count of dimension of the underlying HDF5 dataset of this property.
		* @param patchIndex	The index of the patch we want to know the dimensions in this property.
		* @return			The number of values, 0 otherwise.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getDimensionsCountOfPatch(unsigned int patchIndex) const;

		/**
		* Pushes back a new facet to this intance
		*/
		DLL_IMPORT_OR_EXPORT void pushBackFacet(const gsoap_resqml2_0_1::resqml20__Facet & facet, const std::string & facetValue);

		/**
		* Get the count of facet of this instance
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getFacetCount() const;

		/**
		* Get the facet at a particular index of the facet collection of this instance
		*/
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__Facet getFacet(unsigned int index) const;

		/**
		* Get the facet value at a particular index of the facet collection of this instance.
		*/
		DLL_IMPORT_OR_EXPORT std::string getFacetValue(unsigned int index) const;
	};
}
