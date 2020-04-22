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

#include "../resqml2/WellboreFrameRepresentation.h"
#include "../resqml2/AbstractValuesProperty.h"

/** @brief */
namespace RESQML2_0_1_NS
{
	/** Proxy class for a wellbore frame representation. */
	class WellboreFrameRepresentation final : public RESQML2_NS::WellboreFrameRepresentation
	{
	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT WellboreFrameRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			RESQML2_NS::WellboreFrameRepresentation(partialObject) {}

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		WellboreFrameRepresentation(gsoap_resqml2_0_1::_resqml20__WellboreFrameRepresentation* fromGsoap) : 
			RESQML2_NS::WellboreFrameRepresentation(fromGsoap) {}

		/**
		 * Creates a wellbore frame representation.
		 *
		 * @exception	std::invalid_argument	If @p interp or @p traj is @c nullptr.
		 *
		 * @param [in]	interp	The wellbore interpretation this instance represents. It cannot be null.
		 * @param 	  	guid  	The guid to set to the wellbore frame representation. If empty then a new
		 * 						guid will be generated.
		 * @param 	  	title 	The title to set to the wellbore frame representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param [in]	traj  	The wellbore trajectory that refers this wellbore frame. It cannot be
		 * 						null.
		 */
		WellboreFrameRepresentation(RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, RESQML2_NS::WellboreTrajectoryRepresentation* traj);

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const override { return XML_TAG; }

	protected:
		/** Default constructor */
		WellboreFrameRepresentation() {}
	};
}
