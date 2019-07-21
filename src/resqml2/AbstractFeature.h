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

#include "resqml2/AbstractFeatureInterpretation.h"

namespace RESQML2_NS
{
	class AbstractFeature : public COMMON_NS::AbstractObject
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		* Default constructor
		* Set the gsoap proxy to nullptr.
		*/
		AbstractFeature() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		* @param fromGsoap	The gsoap proxy which shold be wrapped by the constructed feature.
		*/
		AbstractFeature(gsoap_resqml2_0_1::resqml2__AbstractFeature* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractFeature() {}

		/**
		* Get all the interpretations of this feature
		*/
		DLL_IMPORT_OR_EXPORT std::vector<AbstractFeatureInterpretation *> getInterpretationSet() const;

		/**
		 * Get the interpretation count of this feature.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getInterpretationCount() const;

		/**
		 * Get a particular interpretation of this feature according to its position in the interpretation ordering.
		 */
		DLL_IMPORT_OR_EXPORT AbstractFeatureInterpretation *	getInterpretation(unsigned int index) const;

		virtual void loadTargetRelationships();
	};
}
