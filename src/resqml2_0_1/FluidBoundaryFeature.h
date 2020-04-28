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

#include "BoundaryFeature.h"

namespace RESQML2_0_1_NS
{
	/** A fluid boundary feature. */
	class FluidBoundaryFeature final : public BoundaryFeature
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT FluidBoundaryFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : BoundaryFeature(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	repo			The repo which will contain the fluid boundary feature.
		 * @param 		  	guid			The guid to set to the horizon. If empty then a new guid will
		 * 									be generated.
		 * @param 		  	title			A title for the instance to create.
		 * @param 		  	fluidContact	The fluid contact.
		 */
		FluidBoundaryFeature(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__FluidContact fluidContact);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		FluidBoundaryFeature(gsoap_resqml2_0_1::_resqml20__FluidBoundaryFeature* fromGsoap): BoundaryFeature(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~FluidBoundaryFeature() {}

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
		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const final { return XML_TAG; }
	};
}
