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

#include "../resqml2/WellboreFeature.h"

namespace RESQML2_2_NS
{
	/** Proxy class for a wellbore feature. */
	class WellboreFeature final : public RESQML2_NS::WellboreFeature
	{
	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param[in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT WellboreFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::WellboreFeature(partialObject) {}

		/**
		 * Creates a wellbore feature.
		 *
		 * @exception	std::invalid_argument	If @p repo si @c nullptr.
		 *
		 * @param [in,out]	repo 	A repository which will manage the memory of this instance.
		 * @param 		  	guid 	The guid to set to the wellbore feature. If empty then a new guid
		 * 							will be generated.
		 * @param 		  	title	The title to set to the wellbore feature. If empty then \"unknown\"
		 * 							title will be set.
		 */
		WellboreFeature(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title);

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		WellboreFeature(gsoap_eml2_3::_resqml22__WellboreFeature* fromGsoap): RESQML2_NS::WellboreFeature(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~WellboreFeature() {}

		/**
		 * Sets the WITSML wellbore associated to this instance.
		 *
		 * @param [in]	wellbore	The WITSML wellbore to associate to this wellbore. It cannot be null.
		 */
		DLL_IMPORT_OR_EXPORT void setWitsmlWellbore(WITSML2_0_NS::Wellbore * wellbore) final;
	};
}
