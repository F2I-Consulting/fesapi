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
#include "ToolErrorModel.h"
#include "ErrorTerm.h"

#include <stdexcept>
#include <sstream>
#include <algorithm>

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_3;

const char* ToolErrorModel::XML_TAG = "ToolErrorModel";

ToolErrorModel::ToolErrorModel(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid,
	const std::string & title,
	gsoap_eml2_3::witsml21__MisalignmentMode misalignmentMode)
{
	if (repo == nullptr) throw invalid_argument("A Tool Error Model must be associated to a repo.");

	gsoapProxy2_3 = soap_new_witsml21__ToolErrorModel(repo->getGsoapContext(), 1);
	static_cast<witsml21__ToolErrorModel*>(gsoapProxy2_3)->MisalignmentMode = misalignmentMode;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addOrReplaceDataObject(this);
}

bool ToolErrorModel::isTopLevelElement() const
{
	return getRepository()->getSourceObjects<ToolErrorModelDictionary>(this).empty();
}

gsoap_eml2_3::eml23__DataObjectReference* ToolErrorModel::getErrorTermDor(unsigned long index) const
{
	if (gsoapProxy2_3 != nullptr) {
		witsml21__ToolErrorModel* tem = static_cast<witsml21__ToolErrorModel*>(gsoapProxy2_3);
		if (index < tem->ErrorTermValue.size()) {
			return tem->ErrorTermValue[index]->ErrorTerm;
		}
		else {
			throw range_error("The index of error term is out of range");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string ToolErrorModel::getErrorTermUuid(unsigned long index) const
{
	return getErrorTermDor(index)->Uuid;
}

std::vector<ErrorTerm*> ToolErrorModel::getErrorTermSet() const
{
	witsml21__ToolErrorModel* tem = static_cast<witsml21__ToolErrorModel*>(gsoapProxy2_3);
	std::vector<ErrorTerm*> result;

	for (size_t index = 0; index < tem->ErrorTermValue.size(); ++index) {
		result.push_back(getRepository()->getDataObjectByUuid<ErrorTerm>(getErrorTermUuid(index)));
	}

	return result;
}

void ToolErrorModel::pushBackErrorTerm(ErrorTerm* errorTerm, double magnitude, gsoap_eml2_3::eml23__UomEnum uom)
{
	witsml21__ToolErrorModel* tem = static_cast<witsml21__ToolErrorModel*>(gsoapProxy2_3);

	getRepository()->addRelationship(this, errorTerm);

	witsml21__ErrorTermValue* etv = soap_new_witsml21__ErrorTermValue(getGsoapContext(), 1);
	tem->ErrorTermValue.push_back(etv);

	eml23__GenericMeasure* gm = soap_new_eml23__GenericMeasure(getGsoapContext(), 1);
	etv->Magnitude = gm;
	gm->uom = soap_eml23__UomEnum2s(gsoapProxy2_3->soap, uom);
	gm->__item = magnitude;

	etv->ErrorTerm = errorTerm->newEml23Reference();
}

void ToolErrorModel::setApplication(const std::string & application)
{
	witsml21__ToolErrorModel* tem = static_cast<witsml21__ToolErrorModel*>(gsoapProxy2_3);
	if (application.empty()) {
		throw invalid_argument("Cannot set an empty string");
	}

	if (tem->Application == nullptr) {
		tem->Application = soap_new_std__string(gsoapProxy2_3->soap, 1);
	}
	tem->Application->assign(application);
}

void ToolErrorModel::setSource(const std::string & source)
{
	witsml21__ToolErrorModel* tem = static_cast<witsml21__ToolErrorModel*>(gsoapProxy2_3);
	if (source.empty()) {
		throw invalid_argument("Cannot set an empty string");
	}

	if (tem->Source == nullptr) {
		tem->Source = soap_new_std__string(gsoapProxy2_3->soap, 1);
	}
	tem->Source->assign(source);
}

void ToolErrorModel::setToolKind(gsoap_eml2_3::witsml21__ToolKind toolKind)
{
	witsml21__ToolErrorModel* tem = static_cast<witsml21__ToolErrorModel*>(gsoapProxy2_3);
	if (tem->ToolKind == nullptr) {
		tem->ToolKind = soap_new_witsml21__ToolKind(gsoapProxy2_3->soap, 1);
	}

	*tem->ToolKind = toolKind;
}

void ToolErrorModel::pushBackToolSubKind(gsoap_eml2_3::witsml21__ToolSubKind toolSubKind)
{
	static_cast<witsml21__ToolErrorModel*>(gsoapProxy2_3)->ToolSubKind.push_back(soap_witsml21__ToolSubKind2s(gsoapProxy2_3->soap, toolSubKind));
}

void ToolErrorModel::pushBackOperatingCondition(gsoap_eml2_3::witsml21__OperatingCondition operatingCondition)
{
	static_cast<witsml21__ToolErrorModel*>(gsoapProxy2_3)->OperatingCondition.push_back(soap_witsml21__OperatingCondition2s(gsoapProxy2_3->soap, operatingCondition));
}

void ToolErrorModel::setSurveyRunDateStart(time_t surveyRunDateStart)
{
	witsml21__ToolErrorModel* tem = static_cast<witsml21__ToolErrorModel*>(gsoapProxy2_3);
	if (tem->SurveyRunDateStart == nullptr) {
		tem->SurveyRunDateStart = (tm*)soap_malloc(gsoapProxy2_3->soap, sizeof(tm));
	}

	*tem->SurveyRunDateStart = *gmtime(&surveyRunDateStart);
}

void ToolErrorModel::setSurveyRunDateEnd(time_t surveyRunDateEnd)
{
	witsml21__ToolErrorModel* tem = static_cast<witsml21__ToolErrorModel*>(gsoapProxy2_3);
	if (tem->SurveyRunDateEnd == nullptr) {
		tem->SurveyRunDateEnd = (tm*)soap_malloc(gsoapProxy2_3->soap, sizeof(tm));
	}

	*tem->SurveyRunDateEnd = *gmtime(&surveyRunDateEnd);
}

void ToolErrorModel::pushBackCorrectionConsidered(gsoap_eml2_3::witsml21__CorrectionConsidered correctionConsidered)
{
	static_cast<witsml21__ToolErrorModel*>(gsoapProxy2_3)->CorrectionConsidered.push_back(soap_witsml21__CorrectionConsidered2s(gsoapProxy2_3->soap, correctionConsidered));
}

void ToolErrorModel::setReplacedToolErrorModel(ToolErrorModel* replaces)
{
	if (replaces == nullptr) {
		throw invalid_argument("The replaced Tool Error Model to set cannot be null");
	}

	getRepository()->addRelationship(this, replaces);

	static_cast<witsml21__ToolErrorModel*>(gsoapProxy2_3)->Replaces = replaces->newEml23Reference();
}

void ToolErrorModel::setAuthorization(const std::string & approvalAuthority,
	const std::string & approvedBy, time_t approvedOn,
	const std::string & checkedBy, time_t checkedOn,
	const std::string & revisionComment, time_t revisionDate,
	gsoap_eml2_3::witsml21__AuthorizationStatus* status)
{
	witsml21__ToolErrorModel* tem = static_cast<witsml21__ToolErrorModel*>(gsoapProxy2_3);
	witsml21__Authorization* ah = gsoap_eml2_3::soap_new_witsml21__Authorization(gsoapProxy2_3->soap, 1);
	tem->Authorization = ah;

	ah->ApprovalAuthority = approvalAuthority;

	if (!approvedBy.empty()) {
		ah->ApprovedBy = soap_new_std__string(gsoapProxy2_3->soap, 1);
		ah->ApprovedBy->assign(approvedBy);
	}
	if (approvedOn > -1) {
		ah->ApprovedOn = (tm*)soap_malloc(gsoapProxy2_3->soap, sizeof(tm));
		*ah->ApprovedOn = *gmtime(&approvedOn);
	}
	if (!checkedBy.empty()) {
		ah->CheckedBy = soap_new_std__string(gsoapProxy2_3->soap, 1);
		ah->CheckedBy->assign(checkedBy);
	}
	if (checkedOn > -1) {
		ah->CheckedOn = (tm*)soap_malloc(gsoapProxy2_3->soap, sizeof(tm));
		*ah->CheckedOn = *gmtime(&checkedOn);
	}

	if (!revisionComment.empty()) {
		ah->RevisionComment = soap_new_std__string(gsoapProxy2_3->soap, 1);
		ah->RevisionComment->assign(revisionComment);
	}
	if (revisionDate > -1) {
		ah->RevisionDate = (tm*)soap_malloc(gsoapProxy2_3->soap, sizeof(tm));
		*ah->RevisionDate = *gmtime(&revisionDate);
	}

	if (status != nullptr) {
		ah->Status = soap_new_witsml21__AuthorizationStatus(gsoapProxy2_3->soap, 1);
		*ah->Status = *status;
	}
}

void ToolErrorModel::pushBackInclinationRange(double start, bool startInclusive, double end, bool endInclusive, gsoap_eml2_3::eml23__PlaneAngleUom uom, const std::string & comment)
{
	witsml21__ToolErrorModel* tem = static_cast<witsml21__ToolErrorModel*>(gsoapProxy2_3);
	witsml21__OperatingConstraints* oc = gsoap_eml2_3::soap_new_witsml21__OperatingConstraints(gsoapProxy2_3->soap, 1);
	tem->OperatingConstraints = oc;

	witsml21__PlaneAngleOperatingRange* paor = gsoap_eml2_3::soap_new_witsml21__PlaneAngleOperatingRange(gsoapProxy2_3->soap, 1);
	oc->InclinationRange.push_back(paor);
	paor->Start = start;
	paor->StartInclusive = startInclusive;
	paor->End = end;
	paor->EndInclusive = endInclusive;
	paor->Uom = gsoap_eml2_3::soap_eml23__PlaneAngleUom2s(gsoapProxy2_3->soap, uom);
	if (!comment.empty()) {
		paor->Comment = soap_new_std__string(gsoapProxy2_3->soap, 1);
		paor->Comment->assign(comment);
	}
}

void ToolErrorModel::pushBackInclinationRange(double start, bool startInclusive, double end, bool endInclusive, gsoap_eml2_3::eml23__PlaneAngleUom uom, double horizontalEastWestMaxValue, gsoap_eml2_3::eml23__PlaneAngleUom horizontalEastWestMaxValueUom, const std::string & comment)
{
	pushBackInclinationRange(start, startInclusive, end, endInclusive, uom, comment);

	witsml21__OperatingConstraints* oc = static_cast<witsml21__ToolErrorModel*>(gsoapProxy2_3)->OperatingConstraints;
	oc->HorizontalEastWestMaxValue = soap_new_eml23__PlaneAngleMeasureExt(gsoapProxy2_3->soap, 1);
	oc->HorizontalEastWestMaxValue->uom = soap_eml23__PlaneAngleUom2s(gsoapProxy2_3->soap, horizontalEastWestMaxValueUom);
	oc->HorizontalEastWestMaxValue->__item = horizontalEastWestMaxValue;
}

gsoap_eml2_3::witsml21__GyroToolConfiguration* ToolErrorModel::getOrCreateGyroToolConfig()
{
	witsml21__ToolErrorModel* tem = static_cast<witsml21__ToolErrorModel*>(gsoapProxy2_3);
	if (tem->GyroToolConfiguration == nullptr)  {
		tem->GyroToolConfiguration = soap_new_witsml21__GyroToolConfiguration(gsoapProxy2_3->soap, 1);
	}
	tem->GyroToolConfiguration->ExternalReference = false;

	return tem->GyroToolConfiguration;
}

void ToolErrorModel::setXyzAccelerometer()
{
	getOrCreateGyroToolConfig()->AccelerometerAxisCombination = (witsml21__AccelerometerAxisCombination*)soap_malloc(gsoapProxy2_3->soap, sizeof(witsml21__AccelerometerAxisCombination));
	*getOrCreateGyroToolConfig()->AccelerometerAxisCombination = gsoap_eml2_3::witsml21__AccelerometerAxisCombination::xyz;
	getOrCreateGyroToolConfig()->XyAccelerometer = nullptr;
}

void ToolErrorModel::setXyAccelerometer(double cantAngle, gsoap_eml2_3::eml23__PlaneAngleUom cantAngleUom, bool switching)
{
	getOrCreateGyroToolConfig()->AccelerometerAxisCombination = (witsml21__AccelerometerAxisCombination*)soap_malloc(gsoapProxy2_3->soap, sizeof(witsml21__AccelerometerAxisCombination));
	*getOrCreateGyroToolConfig()->AccelerometerAxisCombination = gsoap_eml2_3::witsml21__AccelerometerAxisCombination::xy;
	getOrCreateGyroToolConfig()->XyAccelerometer = soap_new_witsml21__XyAccelerometer(gsoapProxy2_3->soap, 1);
	getOrCreateGyroToolConfig()->XyAccelerometer->CantAngle = soap_new_eml23__PlaneAngleMeasureExt(gsoapProxy2_3->soap, 1); 
	getOrCreateGyroToolConfig()->XyAccelerometer->CantAngle->__item = cantAngle;
	getOrCreateGyroToolConfig()->XyAccelerometer->CantAngle->uom = gsoap_eml2_3::soap_eml23__PlaneAngleUom2s(gsoapProxy2_3->soap, cantAngleUom);
	getOrCreateGyroToolConfig()->XyAccelerometer->Switching = switching;
}

void ToolErrorModel::setExternalReference(bool value)
{
	getOrCreateGyroToolConfig()->ExternalReference = value;
}

void ToolErrorModel::pushBackContinuousGyro(gsoap_eml2_3::witsml21__GyroAxisCombination axisCombination,
	double start, bool startInclusive, double end, bool endInclusive, double initialization, gsoap_eml2_3::eml23__PlaneAngleUom rangeUom,
	double noiseReductionFactor,
	gsoap_eml2_3::eml23__LengthPerTimeUom speedUom, double speed,
	gsoap_eml2_3::eml23__LengthUom reinitializationDistanceUom, double reinitializationDistance)
{
	witsml21__ContinuousGyro* gyro = soap_new_witsml21__ContinuousGyro(gsoapProxy2_3->soap, 1);
	getOrCreateGyroToolConfig()->ContinuousGyro.push_back(gyro);

	gyro->AxisCombination = axisCombination;

	gyro->Range = soap_new_witsml21__PlaneAngleOperatingRange(gsoapProxy2_3->soap, 1);

	gyro->Range->Start = start;
	gyro->Range->StartInclusive = startInclusive;
	gyro->Range->End = end;
	gyro->Range->EndInclusive = endInclusive;
	gyro->Range->Uom = gsoap_eml2_3::soap_eml23__PlaneAngleUom2s(gsoapProxy2_3->soap, rangeUom);

	gyro->Initialization = soap_new_eml23__PlaneAngleMeasureExt(gsoapProxy2_3->soap, 1);
	gyro->Initialization->__item = initialization;
	gyro->Initialization->uom = gsoap_eml2_3::soap_eml23__PlaneAngleUom2s(gsoapProxy2_3->soap, rangeUom);

	if (noiseReductionFactor == noiseReductionFactor) {
		gyro->NoiseReductionFactor = soap_new_double(gsoapProxy2_3->soap, 1);
		*gyro->NoiseReductionFactor = noiseReductionFactor;
	}

	if (speed == speed) {
		gyro->Speed = soap_new_eml23__LengthPerTimeMeasureExt(gsoapProxy2_3->soap, 1);
		gyro->Speed->__item = speed;
		gyro->Speed->uom = gsoap_eml2_3::soap_eml23__LengthPerTimeUom2s(gsoapProxy2_3->soap, speedUom);
	}

	if (reinitializationDistance == reinitializationDistance) {
		gyro->GyroReinitializationDistance = soap_new_eml23__LengthMeasureExt(gsoapProxy2_3->soap, 1);
		gyro->GyroReinitializationDistance->__item = reinitializationDistance;
		gyro->GyroReinitializationDistance->uom = gsoap_eml2_3::soap_eml23__LengthUom2s(gsoapProxy2_3->soap, reinitializationDistanceUom);
	}
}

void ToolErrorModel::pushBackStationaryGyro(gsoap_eml2_3::witsml21__GyroAxisCombination axisCombination,
	double start, bool startInclusive, double end, bool endInclusive, gsoap_eml2_3::eml23__PlaneAngleUom rangeUom)
{
	witsml21__StationaryGyro* gyro = soap_new_witsml21__StationaryGyro(gsoapProxy2_3->soap, 1);
	getOrCreateGyroToolConfig()->StationaryGyro.push_back(gyro);

	gyro->AxisCombination = axisCombination;

	gyro->Range = soap_new_witsml21__PlaneAngleOperatingRange(gsoapProxy2_3->soap, 1);

	gyro->Range->Start = start;
	gyro->Range->StartInclusive = startInclusive;
	gyro->Range->End = end;
	gyro->Range->EndInclusive = endInclusive;
	gyro->Range->Uom = gsoap_eml2_3::soap_eml23__PlaneAngleUom2s(gsoapProxy2_3->soap, rangeUom);
}

void ToolErrorModel::loadTargetRelationships()
{
	witsml21__ToolErrorModel const * tem = static_cast<witsml21__ToolErrorModel*>(gsoapProxy2_3);

	for (size_t index = 0; index < tem->ErrorTermValue.size(); ++index) {
		convertDorIntoRel<ErrorTerm>(getErrorTermDor(index));
	}

	if (tem->Replaces != nullptr) {
		convertDorIntoRel<ToolErrorModel>(tem->Replaces);
	}
}
