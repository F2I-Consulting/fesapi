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

#include "../resqml2/DeviationSurveyRepresentation.h"

namespace RESQML2_0_1_NS
{
	/** A deviation survey representation. */
	class DeviationSurveyRepresentation final : public RESQML2_NS::DeviationSurveyRepresentation
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT DeviationSurveyRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::DeviationSurveyRepresentation(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt> or <tt>mdInfo ==
		 * 										nullptr</tt>.
		 *
		 * @param [in]	interp 	The WellboreFeature interpretation the instance represents.
		 * @param 	  	guid   	The guid to set to the new instance. If empty then a new guid will be
		 * 						generated.
		 * @param 	  	title  	A title for the instance to create.
		 * @param 	  	isFinal	Used to indicate that this is a final version of the deviation survey, as
		 * 						distinct from the interim interpretations.
		 * @param [in]	mdInfo 	The MD information of the survey, mainly the well reference point.
		 */
		DeviationSurveyRepresentation(class RESQML2_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, bool isFinal, RESQML2_NS::MdDatum * mdInfo);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		DeviationSurveyRepresentation(gsoap_resqml2_0_1::_resqml20__DeviationSurveyRepresentation* fromGsoap) : RESQML2_NS::DeviationSurveyRepresentation(fromGsoap) {}

		/** Destructor */
		~DeviationSurveyRepresentation() = default;

		DLL_IMPORT_OR_EXPORT void setGeometry(double const* firstStationLocation, uint64_t stationCount,
			gsoap_resqml2_0_1::eml20__LengthUom mdUom, double const* mds,
			gsoap_resqml2_0_1::eml20__PlaneAngleUom angleUom, double const* azimuths, double const* inclinations,
			EML2_NS::AbstractHdfProxy* proxy) final;

		DLL_IMPORT_OR_EXPORT void setMdDatum(RESQML2_NS::MdDatum * mdDatum) final;

		COMMON_NS::DataObjectReference getMdDatumDor() const final;

		DLL_IMPORT_OR_EXPORT bool isFinal() const final;

		uint64_t getXyzPointCountOfPatch(unsigned int patchIndex) const final;

		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const final;

		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::eml20__LengthUom getMdUom() const final;

		gsoap_resqml2_0_1::eml20__PlaneAngleUom getAngleUom() const final;

		DLL_IMPORT_OR_EXPORT void getMdValues(double* values) const final;

		DLL_IMPORT_OR_EXPORT void getInclinations(double* values) const final;

		DLL_IMPORT_OR_EXPORT void getAzimuths(double* values) const final;

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
