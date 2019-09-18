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

#include "resqml2/GridConnectionSetRepresentation.h"

namespace RESQML2_0_1_NS
{
	class StructuralOrganizationInterpretation;
}

namespace RESQML2_NS
{
	class AbstractFeatureInterpretation : public COMMON_NS::AbstractObject
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractFeatureInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		* Default constructor
		* Set the gsoap proxy to nullptr.
		*/
		AbstractFeatureInterpretation() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractFeatureInterpretation(gsoap_resqml2_0_1::resqml20__AbstractFeatureInterpretation* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractFeatureInterpretation() {}

		/**
		* @return	null pointer if no interpreted feature is associated to this interpretation. Otherwise return the data objet reference of the associated interpreted feature.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference const * getInterpretedFeatureDor() const;

		DLL_IMPORT_OR_EXPORT std::string getInterpretedFeatureUuid() const;

		/**
		 * Set the feature which is interpreted by the current instance.
		 */
		DLL_IMPORT_OR_EXPORT void setInterpretedFeature(AbstractFeature* feature);

		/**
		* Get the feature this instance interprets
		*/
		DLL_IMPORT_OR_EXPORT AbstractFeature* getInterpretedFeature() const;

		/**
		* Init the domain of the interpretation based on its representations
		* @param	defaultDomain	The default domain to set when there is no representation set to this interpretation
		*/
		DLL_IMPORT_OR_EXPORT const gsoap_resqml2_0_1::resqml20__Domain & initDomain(gsoap_resqml2_0_1::resqml20__Domain defaultDomain) const;

		/**
		* Set the domain of the interpretation
		*/
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__Domain getDomain() const;

		/**
		* Get all the representations of this interpretation
		*/
		DLL_IMPORT_OR_EXPORT std::vector<AbstractRepresentation *> getRepresentationSet() const;

		/**
		 * Get the interpretation count of this feature.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getRepresentationCount() const;
		
		/**
		* Get all the Grid Connection Set Representation which reference this interpretation.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<GridConnectionSetRepresentation *> getGridConnectionSetRepresentationSet() const;

		/**
		 * Get a particular interpretation of this feature according to its position in the interpretation ordering.
		 */
		DLL_IMPORT_OR_EXPORT AbstractRepresentation * getRepresentation(unsigned int index) const;

	protected:
		
		virtual void loadTargetRelationships();
	};
}
