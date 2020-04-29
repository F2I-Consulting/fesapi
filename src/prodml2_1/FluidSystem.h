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

namespace PRODML2_1_NS
{
	/** A fluid system. */
	class FluidSystem : public COMMON_NS::AbstractObject
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT FluidSystem(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>repo == nullptr</tt>.
		 *
		 * @param [in,out]	repo			  	The dataobject repo where the underlying gsoap proxy is
		 * 										going to be created.
		 * @param 		  	guid			  	The guid to set to this instance. If empty then a new
		 * 										guid will be generated.
		 * @param 		  	title			  	The title.
		 * @param 		  	temperatureValue  	The temperature value.
		 * @param 		  	temperatureUom	  	The temperature uom.
		 * @param 		  	pressureValue	  	The pressure value.
		 * @param 		  	pressureUom		  	The pressure uom.
		 * @param 		  	reservoirFluidKind	The reservoir fluid kind.
		 * @param 		  	gasOilRatio		  	The gas oil ratio.
		 * @param 		  	gasOilRatioUom	  	The gas oil ratio uom.
		 */
		FluidSystem(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid,
			const std::string & title,
			double temperatureValue, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom temperatureUom,
			double pressureValue, gsoap_eml2_2::eml22__PressureUom pressureUom,
			gsoap_eml2_2::prodml21__ReservoirFluidKind reservoirFluidKind,
			double gasOilRatio, gsoap_eml2_2::eml22__VolumePerVolumeUom gasOilRatioUom);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		FluidSystem(gsoap_eml2_2::prodml21__FluidSystem* fromGsoap):AbstractObject(fromGsoap)  {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~FluidSystem() {}

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

		/**
		 * Gets XML namespace
		 *
		 * @returns	The XML namespace.
		 */
		std::string getXmlNamespace() const { return "prodml21"; }

		/** Loads target relationships */
		void loadTargetRelationships() {}
	};
}
