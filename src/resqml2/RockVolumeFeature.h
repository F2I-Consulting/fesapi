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
	 * @brief	A continuous portion of rock material bounded by definite rock boundaries. It is a
	 * 			volume object.
	 * 			
	 * 			Some of these rock volumes are "static", while others are "dynamic". Reservoir fluids
	 * 			are dynamic because their properties, geometries, and quantities may change over time
	 * 			during the course of field production. A RockVolume feature is a geological feature--
	 * 			which is the general concept that refers to the various categories of geological
	 * 			objects that exist in the natural world, for example, the rock volume or the fluids
	 * 			that are present before production. The geological feature is not represented in the
	 * 			RESQML design.
	 */
	class RockVolumeFeature : public AbstractFeature
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~RockVolumeFeature() {}

	protected:

		/** Default constructor Set the gsoap proxy to nullptr from superclass constructor */
		RockVolumeFeature() {}

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT RockVolumeFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractFeature(partialObject) {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		RockVolumeFeature(gsoap_resqml2_0_1::_resqml20__GeologicUnitFeature* fromGsoap) : AbstractFeature(fromGsoap) {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		RockVolumeFeature(gsoap_eml2_3::_resqml22__RockVolumeFeature* fromGsoap) : AbstractFeature(fromGsoap) {}
	};
}
