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

#include <vector>

#include "../common/AbstractObject.h"

/** . */
namespace RESQML2_NS
{
	class AbstractFeatureInterpretation;

	/** Proxy class for an abstract feature. */
	class AbstractFeature : public COMMON_NS::AbstractObject
	{
	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT AbstractFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/** Default constructor Set the gsoap proxy to nullptr. */
		AbstractFeature() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	The gsoap proxy which shold be wrapped by the constructed feature.
		 */
		AbstractFeature(gsoap_resqml2_0_1::resqml20__AbstractFeature* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}
		AbstractFeature(gsoap_eml2_3::resqml22__AbstractFeature* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~AbstractFeature() {}

		/**
		 * Gets all the interpretations of this feature.
		 *
		 * @returns The vector of all the interpretations of this feature.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<AbstractFeatureInterpretation *> getInterpretationSet() const;

		/**
		 * Gets the interpretation count of this feature.
		 *
		 * @exception	std::range_error	If the interpretation count is strictly greater than unsigned
		 * 									int max.
		 *
		 * @returns	The interpretation count of this feature.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getInterpretationCount() const;

		/**
		 * Gets a particular interpretation of this feature according to its position in the
		 * interpretations ordering.
		 *
		 * @exception	std::out_of_range	If @p index is out of the range of the interpretation set of
		 * 									the feature.
		 *
		 * @param 	index	Zero-based index of the interpretation we look for.
		 *
		 * @returns	A pointer to the interpretation at @p index.
		 */
		DLL_IMPORT_OR_EXPORT AbstractFeatureInterpretation *	getInterpretation(unsigned int index) const;

	protected:

		/** Loads target relationships */
		virtual void loadTargetRelationships() {}
	};
}
