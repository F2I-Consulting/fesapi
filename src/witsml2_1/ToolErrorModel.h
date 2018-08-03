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

#include "witsml2_1/ToolErrorModelDictionary.h"

namespace WITSML2_1_NS
{
	class DLL_IMPORT_OR_EXPORT ToolErrorModel : public WITSML2_1_NS::AbstractObject
	{
	private :
		gsoap_eml2_2::witsml2__GyroToolConfiguration* getOrCreateGyroToolConfig();

	public:
		
		/**
		* Only to be used in partial transfer context
		*/
		ToolErrorModel(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			WITSML2_1_NS::AbstractObject(partialObject),
			toolErrorModelDictionary(nullptr),
			nextVersionToolErrorModel(nullptr) {}
		
		/**
		* Creates an instance of this class in a gsoap context.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		*/
		ToolErrorModel(soap* soapContext,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_2::witsml2__MisalignmentMode misalignmentMode);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		ToolErrorModel(gsoap_eml2_2::witsml2__ToolErrorModel* fromGsoap) :AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~ToolErrorModel() {}

		bool isTopLevelElement() const;

		std::string getErrorTermUuid(unsigned long index) const;
		std::vector<class ErrorTerm*> getErrorTermSet() const;
		void pushBackErrorTerm(class ErrorTerm* errorTerm, double magnitude, gsoap_eml2_2::eml22__UomEnum uom);

		void setApplication(const std::string & application);
		void setNote(const std::string & note);
		void setSource(const std::string & source);
		void setToolKind(gsoap_eml2_2::witsml2__ToolKind toolKind);
		void pushBackToolSubKind(gsoap_eml2_2::witsml2__ToolSubKind toolSubKind);
		void pushBackOperatingCondition(gsoap_eml2_2::witsml2__OperatingCondition operatingCondition);
		void setSurveyRunDateStart(unsigned long surveyRunDateStart);
		void setSurveyRunDateEnd(unsigned long surveyRunDateEnd);
		void pushBackCorrectionConsidered(gsoap_eml2_2::witsml2__CorrectionConsidered correctionConsidered);

		/**
		* All parameters can be empty, negative or nullptr if non present. Documentation on each parameter can override this rule.
		*
		* @param approvalAuthority	Must no be empty.
		* @param status				Can be nullptr. If not null, a copy of the pointed object will be done into the WITSML Authorization History.
		*/
		void setAuthorization(const std::string & approvalAuthority,
			const std::string & approvedBy, int approvedOn,
			const std::string & checkedBy, int checkedOn,
			ToolErrorModel* replaces,
			const std::string & revisionComment, int revisionDate,
			gsoap_eml2_2::witsml2__AuthorizationStatus* status);

		void pushBackInclinationRange(double min, double max, gsoap_eml2_2::eml22__PlaneAngleUom minMaxUom, const std::string & comment = std::string());
		void pushBackInclinationRange(double min, double max, gsoap_eml2_2::eml22__PlaneAngleUom minMaxUom, double horizontalEastWestMaxValue, gsoap_eml2_2::eml22__PlaneAngleUom horizontalEastWestMaxValueUom, const std::string & comment = std::string());

		void setXyzAccelerometer();
		void setXyAccelerometer(double cantAngle, gsoap_eml2_2::eml22__PlaneAngleUom cantAngleUom, bool switching);

		void setGyroReinitializationDistance(double value, gsoap_eml2_2::eml22__LengthUom uom);
		void setNoiseReductionFactor(double value);
		void setExternalReference(bool value);

		void pushBackGyro(gsoap_eml2_2::witsml2__GyroAxisCombination axisCombination, gsoap_eml2_2::witsml2__GyroMode mode,
			double start, gsoap_eml2_2::eml22__PlaneAngleUom startUom,
			double end, gsoap_eml2_2::eml22__PlaneAngleUom endUom,
			double initialization, gsoap_eml2_2::eml22__PlaneAngleUom initializationUom,
			gsoap_eml2_2::eml22__LengthPerTimeUom speedUom = gsoap_eml2_2::eml22__LengthPerTimeUom__m_x002fs, double speed = std::numeric_limits<double>::quiet_NaN(),
			gsoap_eml2_2::eml22__LengthUom uom = gsoap_eml2_2::eml22__LengthUom__m, double reinitializationDistance = std::numeric_limits<double>::quiet_NaN());

		/**
		* Resolve all relationships of the object in an epc document.
		*/
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	protected:

		// XML backwards relationship
		ToolErrorModelDictionary* toolErrorModelDictionary;
		ToolErrorModel* nextVersionToolErrorModel;

		std::vector<epc::Relationship> getAllEpcRelationships() const;

		friend void WITSML2_1_NS::ToolErrorModelDictionary::pushBackToolErrorModel(ToolErrorModel* tem);
	};
}

