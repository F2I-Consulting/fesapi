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

namespace RESQML2_NS
{
	class GridConnectionSetRepresentation;

	/** @brief	Proxy class for an abstract feature interpretation. */
	class AbstractFeatureInterpretation : public COMMON_NS::AbstractObject
	{
	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT AbstractFeatureInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/** Default constructor Set the gsoap proxy to nullptr. */
		AbstractFeatureInterpretation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractFeatureInterpretation(gsoap_resqml2_0_1::resqml20__AbstractFeatureInterpretation* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}
		AbstractFeatureInterpretation(gsoap_eml2_3::resqml22__AbstractFeatureInterpretation* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~AbstractFeatureInterpretation() = default;

		/**
		 * Gets the interpreted feature data object reference.
		 *
		 * @returns	Empty data object reference if no interpreted feature is associated to this interpretation.
		 * 			Otherwise return the data objet reference of the associated interpreted feature.
		 */
		COMMON_NS::DataObjectReference getInterpretedFeatureDor() const;

		/**
		 * Sets the feature which is interpreted by the current instance.
		 *
		 * @exception	std::invalid_argument	If @p feature is null.
		 *
		 * @param [in]	feature	The feature to interpret.
		 */
		DLL_IMPORT_OR_EXPORT void setInterpretedFeature(AbstractFeature* feature);

		/**
		 * Gets the feature this instance interprets
		 *
		 * @returns	A pointer to the interpreted feature.
		 */
		DLL_IMPORT_OR_EXPORT AbstractFeature* getInterpretedFeature() const;

		/**
		 * Initializes the domain of the interpretation by looking at the local CRS domain of its
		 * representations.
		 *
		 * @param 	defaultDomain	The default domain to set when no representation is associated to
		 * 							this interpretation.
		 *
		 * @returns	The domain that have been set to this interpretation (either deduced from its
		 * 			representation or @p defaultDomain).
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__Domain initDomain(gsoap_resqml2_0_1::resqml20__Domain defaultDomain) const;

		/**
		 * Gets the domain of this interpretation.
		 *
		 * @returns	The domain of this interpretation.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__Domain getDomain() const;

		/**
		 * Gets all the representations of this interpretation.
		 *
		 * @returns	A vector of all the representations associated to this interpretation.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<AbstractRepresentation *> getRepresentationSet() const;

		/**
		 * Get the representation count of this interpretation.
		 *
		 * @exception	std::range_error	If the representation count is strictly greater than unsigned
		 * 									int max.
		 *
		 * @returns	The representation count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getRepresentationCount() const;

		/**
		 * Get all the grid connection set representations which reference this interpretation.
		 *
		 * @returns	A vector of pointers to all the grid connection set representations which reference this interpretation.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<GridConnectionSetRepresentation *> getGridConnectionSetRepresentationSet() const;

		/**
		 * Gets a particular representation of this interpretation according to its position in the
		 * representations ordering.
		 *
		 * @exception	std::out_of_range	If @p index is out of the range of the representation set.
		 *
		 * @param 	index	Zero-based index of the representation we look for.
		 *
		 * @returns	A pointer to the representation at @p index.
		 */
		DLL_IMPORT_OR_EXPORT AbstractRepresentation * getRepresentation(unsigned int index) const;
		
		/** Loads target relationships */
		virtual void loadTargetRelationships();
	};
}
