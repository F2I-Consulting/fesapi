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

#include "../resqml2/BoundaryFeature.h"

/** . */
namespace RESQML2_2_NS
{
	/** A boundary feature. */
	class BoundaryFeature : public RESQML2_NS::BoundaryFeature
	{
	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT BoundaryFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::BoundaryFeature(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If @p repo is @c nullptr.
		 *
		 * @param [in,out]	repo 	The repository where the underlying gSOAP proxy is going to be
		 * 							created.
		 * @param 		  	guid 	The guid to set to the boundary feature. If empty then a new guid
		 * 							will be generated.
		 * @param 		  	title	The title to set to the boundary feature. If empty then \"unknown\"
		 * 							title will be set.
		 */
		BoundaryFeature(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		BoundaryFeature(gsoap_eml2_3::_resqml22__BoundaryFeature* fromGsoap): RESQML2_NS::BoundaryFeature(fromGsoap) {}
		
		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		~BoundaryFeature() {}
	};
}

