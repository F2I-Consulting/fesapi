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

#include "GridConnectionSetRepresentation.h"

/** . */
namespace RESQML2_0_1_NS
{
	/** A structural organization interpretation. */
	class StructuralOrganizationInterpretation;
}

/** . */
namespace RESQML2_NS
{
	/** An abstract feature interpretation. */
	class AbstractFeatureInterpretation : public COMMON_NS::AbstractObject
	{
	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
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

	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~AbstractFeatureInterpretation() {}

		/**
		 * Gets interpreted feature dor
		 *
		 * @returns	null pointer if no interpreted feature is associated to this interpretation.
		 * 			Otherwise return the data objet reference of the associated interpreted feature.
		 */
		gsoap_resqml2_0_1::eml20__DataObjectReference const * getInterpretedFeatureDor() const;

		/**
		 * Gets interpreted feature uuid
		 *
		 * @returns	The interpreted feature uuid.
		 */
		DLL_IMPORT_OR_EXPORT std::string getInterpretedFeatureUuid() const;

		/**
		 * Set the feature which is interpreted by the current instance.
		 *
		 * @param [in,out]	feature	If non-null, the feature.
		 */
		DLL_IMPORT_OR_EXPORT void setInterpretedFeature(AbstractFeature* feature);

		/**
		 * Get the feature this instance interprets
		 *
		 * @returns	Null if it fails, else the interpreted feature.
		 */
		DLL_IMPORT_OR_EXPORT AbstractFeature* getInterpretedFeature() const;

		/**
		 * Init the domain of the interpretation based on its representations
		 *
		 * @param 	defaultDomain	The default domain to set when there is no representation set to this
		 * 							interpretation.
		 *
		 * @returns	A reference to a const gsoap_resqml2_0_1::resqml20__Domain.
		 */
		DLL_IMPORT_OR_EXPORT const gsoap_resqml2_0_1::resqml20__Domain & initDomain(gsoap_resqml2_0_1::resqml20__Domain defaultDomain) const;

		/**
		 * Set the domain of the interpretation
		 *
		 * @returns	The domain.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__Domain getDomain() const;

		/**
		 * Get all the representations of this interpretation
		 *
		 * @returns	Null if it fails, else the representation set.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<AbstractRepresentation *> getRepresentationSet() const;

		/**
		 * Get the interpretation count of this feature.
		 *
		 * @returns	The representation count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getRepresentationCount() const;

		/**
		 * Get all the Grid Connection Set Representation which reference this interpretation.
		 *
		 * @returns	Null if it fails, else the grid connection set representation set.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<GridConnectionSetRepresentation *> getGridConnectionSetRepresentationSet() const;

		/**
		 * Get a particular interpretation of this feature according to its position in the
		 * interpretation ordering.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	Null if it fails, else the representation.
		 */
		DLL_IMPORT_OR_EXPORT AbstractRepresentation * getRepresentation(unsigned int index) const;

	protected:
		
		/** Loads target relationships */
		virtual void loadTargetRelationships();
	};
}
