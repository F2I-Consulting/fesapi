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

#include "AbstractFeature.h"

namespace RESQML2_NS
{
	/**
	 * @brief	An abstract technical feature. These are objects that exist by the action of humans.
	 * 			
	 * 			Examples include: wells and all they may contain, seismic surveys (surface, permanent
	 * 			water bottom), or injected fluid volumes. Because the decision to deploy such
	 * 			equipment is the result of studies or decisions by humans, technical features are
	 * 			usually not subject to the same kind of large changes in interpretation as geologic
	 * 			features. However, they are still subject to measurement error and other sources of
	 * 			uncertainty, and so still can be considered as subject to "interpretation". RESQML
	 * 			has these types of features: geologic and technical.
	 */
	class AbstractTechnicalFeature : public AbstractFeature
	{
	public:
		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~AbstractTechnicalFeature() {}

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT AbstractTechnicalFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractFeature(partialObject) {}

		/** Default constructor Set the gsoap proxy to nullptr from superclass constructor */
		AbstractTechnicalFeature() {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-nullptr, from gsoap.
		 */
		AbstractTechnicalFeature(gsoap_resqml2_0_1::resqml20__AbstractTechnicalFeature* fromGsoap) : AbstractFeature(fromGsoap) {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-nullptr, from gsoap.
		 */
		AbstractTechnicalFeature(gsoap_eml2_3::resqml22__AbstractTechnicalFeature* fromGsoap) : AbstractFeature(fromGsoap) {}
	};
}
