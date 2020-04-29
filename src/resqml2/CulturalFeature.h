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

#include "../resqml2/AbstractTechnicalFeature.h"

namespace RESQML2_NS
{
	/**
	 * @brief	A cultural feature. It identifies a frontier or boundary in the earth model that is
	 * 			not a geological feature but an arbitrary geographic/geometric surface used to
	 * 			delineate the boundary of the model.
	 */
	class CulturalFeature : public RESQML2_NS::AbstractTechnicalFeature
	{
	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~CulturalFeature() {}


	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT CulturalFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractTechnicalFeature(partialObject) {}

		/**
		 * Defautl constructor
		 */
		CulturalFeature() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		CulturalFeature(gsoap_resqml2_0_1::_resqml20__FrontierFeature* fromGsoap): RESQML2_NS::AbstractTechnicalFeature(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		CulturalFeature(gsoap_eml2_3::_resqml22__CulturalFeature* fromGsoap) : RESQML2_NS::AbstractTechnicalFeature(fromGsoap) {}
	};
}
