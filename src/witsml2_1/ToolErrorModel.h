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

#include <vector>
#include <string>
#include <limits>

#include "ToolErrorModelDictionary.h"

namespace WITSML2_1_NS
{
	class ToolErrorModel : public COMMON_NS::AbstractObject
	{
	private :
		gsoap_eml2_3::witsml21__GyroToolConfiguration* getOrCreateGyroToolConfig();

	public:
		
		/**
		* Only to be used in partial transfer context
		*/
		ToolErrorModel(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			COMMON_NS::AbstractObject(partialObject) {}
		
		/**
		* Creates an instance of this class in a gsoap context.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		*/
		ToolErrorModel(COMMON_NS::DataObjectRepository* repo,
			const std::string& guid,
			const std::string& title,
			gsoap_eml2_3::witsml21__MisalignmentMode misalignmentMode);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		ToolErrorModel(gsoap_eml2_3::witsml21__ToolErrorModel* fromGsoap) : AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~ToolErrorModel() {}

		DLL_IMPORT_OR_EXPORT bool isTopLevelElement() const;

		gsoap_eml2_3::eml23__DataObjectReference* getErrorTermDor(uint64_t index) const;
		DLL_IMPORT_OR_EXPORT std::string getErrorTermUuid(uint64_t index) const;
		DLL_IMPORT_OR_EXPORT std::vector<class ErrorTerm*> getErrorTermSet() const;
		DLL_IMPORT_OR_EXPORT void pushBackErrorTerm(class ErrorTerm* errorTerm, double magnitude, gsoap_eml2_3::eml23__UomEnum uom);

		DLL_IMPORT_OR_EXPORT void setApplication(const std::string& application);
		DLL_IMPORT_OR_EXPORT void setSource(const std::string& source);
		DLL_IMPORT_OR_EXPORT void setToolKind(gsoap_eml2_3::witsml21__ToolKind toolKind);
		DLL_IMPORT_OR_EXPORT void pushBackToolSubKind(gsoap_eml2_3::witsml21__ToolSubKind toolSubKind);
		DLL_IMPORT_OR_EXPORT void pushBackOperatingCondition(gsoap_eml2_3::witsml21__OperatingCondition operatingCondition);
		DLL_IMPORT_OR_EXPORT void setSurveyRunDateStart(time_t surveyRunDateStart);
		DLL_IMPORT_OR_EXPORT void setSurveyRunDateEnd(time_t surveyRunDateEnd);
		DLL_IMPORT_OR_EXPORT void pushBackCorrectionConsidered(gsoap_eml2_3::witsml21__CorrectionConsidered correctionConsidered);

		DLL_IMPORT_OR_EXPORT void setReplacedToolErrorModel(ToolErrorModel* replaces);

		/**
		* All parameters can be empty, negative or nullptr if non present. Documentation on each parameter can override this rule.
		*
		* @param approvalAuthority	Must no be empty.
		* @param status				Can be nullptr. If not null, a copy of the pointed object will be done into the WITSML Authorization History.
		*/
		DLL_IMPORT_OR_EXPORT void setAuthorization(const std::string& approvalAuthority,
			const std::string& approvedBy, time_t approvedOn,
			const std::string& checkedBy, time_t checkedOn,
			const std::string& revisionComment, time_t revisionDate,
			gsoap_eml2_3::witsml21__AuthorizationStatus* status);

		DLL_IMPORT_OR_EXPORT void pushBackInclinationRange(double start, bool startInclusive, double end, bool endInclusive, gsoap_eml2_3::eml23__PlaneAngleUom uom, const std::string& comment = std::string());
		DLL_IMPORT_OR_EXPORT void pushBackInclinationRange(double start, bool startInclusive, double end, bool endInclusive, gsoap_eml2_3::eml23__PlaneAngleUom uom, double horizontalEastWestMaxValue, gsoap_eml2_3::eml23__PlaneAngleUom horizontalEastWestMaxValueUom, const std::string & comment = std::string());

		DLL_IMPORT_OR_EXPORT void setXyzAccelerometer();
		DLL_IMPORT_OR_EXPORT void setXyAccelerometer(double cantAngle, gsoap_eml2_3::eml23__PlaneAngleUom cantAngleUom, bool switching);

		DLL_IMPORT_OR_EXPORT void setExternalReference(bool value);

		DLL_IMPORT_OR_EXPORT void pushBackContinuousGyro(gsoap_eml2_3::witsml21__GyroAxisCombination axisCombination,
			double start, bool startInclusive, double end, bool endInclusive, double initialization, gsoap_eml2_3::eml23__PlaneAngleUom rangeUom,
			double noiseReductionFactor = std::numeric_limits<double>::quiet_NaN(),
			gsoap_eml2_3::eml23__LengthPerTimeUom speedUom = gsoap_eml2_3::eml23__LengthPerTimeUom::m_x002fs, double speed = std::numeric_limits<double>::quiet_NaN(),
			gsoap_eml2_3::eml23__LengthUom reinitializationDistanceUom = gsoap_eml2_3::eml23__LengthUom::m, double reinitializationDistance = std::numeric_limits<double>::quiet_NaN());

		DLL_IMPORT_OR_EXPORT void pushBackStationaryGyro(gsoap_eml2_3::witsml21__GyroAxisCombination axisCombination,
			double start, bool startInclusive, double end, bool endInclusive, gsoap_eml2_3::eml23__PlaneAngleUom rangeUom);

		void loadTargetRelationships();

		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "ToolErrorModel";
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const {return XML_TAG;}

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "witsml21";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

	};
}
