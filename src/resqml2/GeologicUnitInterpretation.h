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

#include "AbstractFeatureInterpretation.h"
#include "RockVolumeFeature.h"

namespace RESQML2_NS
{
	/** @brief	The interpretation of a geologic unit. */
	class GeologicUnitInterpretation : public AbstractFeatureInterpretation
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param[in,out]	partialObject	If non-null, the partial object.
		 *
		 *
		 */
		DLL_IMPORT_OR_EXPORT GeologicUnitInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractFeatureInterpretation(partialObject) {}
		
		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>feature == nullptr</tt>.
		 *
		 * @param[in]	feature	The feature the instance interprets.
		 * @param 	  	guid   	The guid to set to the interpretation. If empty then a new guid will be
		 * 						generated.
		 * @param 	  	title  	A title for the instance to create.
		 */
		GeologicUnitInterpretation(RESQML2_NS::RockVolumeFeature* feature, const std::string& guid, const std::string& title)
		{
			if (feature == nullptr) {
				throw std::invalid_argument("The interpreted feature cannot be null.");
			}

			switch (feature->getRepository()->getDefaultResqmlVersion()) {
			case COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_0_1:
				gsoapProxy2_0_1 = gsoap_resqml2_0_1::soap_new_resqml20__obj_USCOREGeologicUnitInterpretation(feature->getGsoapContext());
				break;
#ifdef WITH_RESQML2_2
			case COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_2:
				gsoapProxy2_3 = gsoap_eml2_3::soap_new_resqml22__GeologicUnitInterpretation(feature->getGsoapContext());
				break;
#endif
			default:
				throw std::invalid_argument("Unrecognized Energistics standard.");
			}

			initMandatoryMetadata();
			setMetadata(guid, title, "", -1, "", "", -1, "");

			setInterpretedFeature(feature);
		}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param[in,out]	fromGsoap	If non-null, from gsoap.
		 */
		GeologicUnitInterpretation(gsoap_resqml2_0_1::_resqml20__GeologicUnitInterpretation* fromGsoap) : AbstractFeatureInterpretation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param[in,out]	fromGsoap	If non-null, from gsoap.
		 */
		GeologicUnitInterpretation(gsoap_eml2_3::_resqml22__GeologicUnitInterpretation* fromGsoap) : AbstractFeatureInterpretation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~GeologicUnitInterpretation() = default;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "GeologicUnitInterpretation";

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const { return gsoapProxy2_0_1 ? "resqml20" : "resqml22"; }

	protected:

		/**
		 * Default constructor
		 */
		GeologicUnitInterpretation() {}
	};
}
