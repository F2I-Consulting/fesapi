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
#include "witsml2_1/ToolErrorModel.h"
#include "witsml2_1/ErrorTerm.h"

#include <stdexcept>
#include <sstream>

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_2;
using namespace epc;

const char* ToolErrorModel::XML_TAG = "ToolErrorModel";

ToolErrorModel::ToolErrorModel(soap* soapContext,
	const std::string & guid,
	const std::string & title,
	gsoap_eml2_2::witsml2__MisalignmentMode misalignmentMode) :
	toolErrorModelDictionary(nullptr),
	nextVersionToolErrorModel(nullptr)
{
	if (soapContext == nullptr) throw invalid_argument("A Tool Error Model must be associated to a soap context.");

	gsoapProxy2_2 = soap_new_witsml2__ToolErrorModel(soapContext, 1);
	static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2)->MisalignmentMode = misalignmentMode;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

bool ToolErrorModel::isTopLevelElement() const
{
	return toolErrorModelDictionary == nullptr;
}

std::string ToolErrorModel::getErrorTermUuid(unsigned long index) const
{
	if (gsoapProxy2_2 != nullptr) {
		witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2);
		if (index < tem->ErrorTermValue.size()) {
			return tem->ErrorTermValue[index]->ErrorTerm->Uuid;
		}
		else{
			throw range_error("The index of error term is out of range");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::vector<ErrorTerm*> ToolErrorModel::getErrorTermSet() const
{
	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2);
	std::vector<ErrorTerm*> result;

	for (size_t index = 0; index < tem->ErrorTermValue.size(); ++index) {
		result.push_back(epcDocument->getResqmlAbstractObjectByUuid<ErrorTerm>(getErrorTermUuid(index)));
	}

	return result;
}

void ToolErrorModel::pushBackErrorTerm(ErrorTerm* errorTerm, double magnitude, gsoap_eml2_2::eml22__UomEnum uom)
{
	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2);

	if (std::find(errorTerm->toolErrorModelSet.begin(), errorTerm->toolErrorModelSet.end(), this) == errorTerm->toolErrorModelSet.end()) {
		errorTerm->toolErrorModelSet.push_back(this);
	}

	if (updateXml)
	{
		witsml2__ErrorTermValue* etv = soap_new_witsml2__ErrorTermValue(getGsoapContext(), 1);
		tem->ErrorTermValue.push_back(etv);

		eml22__GenericMeasure* gm = soap_new_eml22__GenericMeasure(getGsoapContext(), 1);
		etv->Magnitude = gm;
		gm->uom = soap_eml22__UomEnum2s(gsoapProxy2_2->soap, uom);
		gm->__item = magnitude;

		etv->ErrorTerm = errorTerm->newEml22Reference();
	}
}

void ToolErrorModel::setApplication(const std::string & application)
{
	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2);
	if (application.empty()) {
		throw invalid_argument("Cannot set an empty string");
	}

	if (tem->Application == nullptr) {
		tem->Application = soap_new_std__string(gsoapProxy2_2->soap, 1);
	}
	tem->Application->assign(application);
}

void ToolErrorModel::setNote(const std::string & note)
{
	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2);
	if (note.empty()) {
		throw invalid_argument("Cannot set an empty string");
	}

	if (tem->Note == nullptr) {
		tem->Note = soap_new_std__string(gsoapProxy2_2->soap, 1);
	}
	tem->Note->assign(note);
}

void ToolErrorModel::setSource(const std::string & source)
{
	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2);
	if (source.empty()) {
		throw invalid_argument("Cannot set an empty string");
	}

	if (tem->Source == nullptr) {
		tem->Source = soap_new_std__string(gsoapProxy2_2->soap, 1);
	}
	tem->Source->assign(source);
}

void ToolErrorModel::setToolKind(gsoap_eml2_2::witsml2__ToolKind toolKind)
{
	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2);
	if (tem->ToolKind == nullptr) {
		tem->ToolKind = soap_new_witsml2__ToolKind(gsoapProxy2_2->soap, 1);
	}

	*tem->ToolKind = toolKind;
}

void ToolErrorModel::pushBackToolSubKind(gsoap_eml2_2::witsml2__ToolSubKind toolSubKind)
{
	static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2)->ToolSubKind.push_back(soap_witsml2__ToolSubKind2s(gsoapProxy2_2->soap, toolSubKind));
}

void ToolErrorModel::pushBackOperatingCondition(gsoap_eml2_2::witsml2__OperatingCondition operatingCondition)
{
	static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2)->OperatingCondition.push_back(soap_witsml2__OperatingCondition2s(gsoapProxy2_2->soap, operatingCondition));
}

void ToolErrorModel::setSurveyRunDateStart(time_t surveyRunDateStart)
{
	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2);
	if (tem->SurveyRunDateStart == nullptr) {
		tem->SurveyRunDateStart = (tm*)soap_malloc(gsoapProxy2_2->soap, sizeof(tm));
	}

	*tem->SurveyRunDateStart = *gmtime(&surveyRunDateStart);
}

void ToolErrorModel::setSurveyRunDateEnd(time_t surveyRunDateEnd)
{
	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2);
	if (tem->SurveyRunDateEnd == nullptr) {
		tem->SurveyRunDateEnd = (tm*)soap_malloc(gsoapProxy2_2->soap, sizeof(tm));
	}

	*tem->SurveyRunDateEnd = *gmtime(&surveyRunDateEnd);
}

void ToolErrorModel::pushBackCorrectionConsidered(gsoap_eml2_2::witsml2__CorrectionConsidered correctionConsidered)
{
	static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2)->CorrectionConsidered.push_back(soap_witsml2__CorrectionConsidered2s(gsoapProxy2_2->soap, correctionConsidered));
}

void ToolErrorModel::setReplacedToolErrorModel(ToolErrorModel* replaces)
{
	if (replaces == nullptr) {
		throw invalid_argument("The replaced Tool Error Model to set cannot be null");
	}

	replaces->nextVersionToolErrorModel = this;

	if (updateXml) {
		static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2)->Replaces = replaces->newEml22Reference();
	}
}

void ToolErrorModel::setAuthorization(const std::string & approvalAuthority,
	const std::string & approvedBy, time_t approvedOn,
	const std::string & checkedBy, time_t checkedOn,
	const std::string & revisionComment, time_t revisionDate,
	gsoap_eml2_2::witsml2__AuthorizationStatus* status)
{
	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2);
	witsml2__Authorization* ah = gsoap_eml2_2::soap_new_witsml2__Authorization(gsoapProxy2_2->soap, 1);
	tem->Authorization = ah;

	ah->ApprovalAuthority = approvalAuthority;

	if (!approvedBy.empty()) {
		ah->ApprovedBy = soap_new_std__string(gsoapProxy2_2->soap, 1);
		ah->ApprovedBy->assign(approvedBy);
	}
	if (approvedOn > -1) {
		ah->ApprovedOn = (tm*)soap_malloc(gsoapProxy2_2->soap, sizeof(tm));
		*ah->ApprovedOn = *gmtime(&approvedOn);
	}
	if (!checkedBy.empty()) {
		ah->CheckedBy = soap_new_std__string(gsoapProxy2_2->soap, 1);
		ah->CheckedBy->assign(checkedBy);
	}
	if (checkedOn > -1) {
		ah->CheckedOn = (tm*)soap_malloc(gsoapProxy2_2->soap, sizeof(tm));
		*ah->CheckedOn = *gmtime(&checkedOn);
	}

	if (!revisionComment.empty()) {
		ah->RevisionComment = soap_new_std__string(gsoapProxy2_2->soap, 1);
		ah->RevisionComment->assign(revisionComment);
	}
	if (revisionDate > -1) {
		ah->RevisionDate = (tm*)soap_malloc(gsoapProxy2_2->soap, sizeof(tm));
		*ah->RevisionDate = *gmtime(&revisionDate);
	}

	if (status != nullptr) {
		ah->Status = soap_new_witsml2__AuthorizationStatus(gsoapProxy2_2->soap, 1);
		*ah->Status = *status;
	}
}

void ToolErrorModel::pushBackInclinationRange(double min, double max, gsoap_eml2_2::eml22__PlaneAngleUom minMaxUom, const std::string & comment)
{
	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2);
	witsml2__OperatingConstraints* oc = gsoap_eml2_2::soap_new_witsml2__OperatingConstraints(gsoapProxy2_2->soap, 1);
	tem->OperatingConstraints = oc;

	witsml2__PlaneAngleOperatingRange* paor = gsoap_eml2_2::soap_new_witsml2__PlaneAngleOperatingRange(gsoapProxy2_2->soap, 1);
	oc->InclinationRange.push_back(paor);
	paor->Min = min;
	paor->Max = max;
	paor->Uom = soap_eml22__PlaneAngleUom2s(gsoapProxy2_2->soap, minMaxUom);
	if (!comment.empty()) {
		paor->Comment = soap_new_std__string(gsoapProxy2_2->soap, 1);
		paor->Comment->assign(comment);
	}
}

void ToolErrorModel::pushBackInclinationRange(double min, double max, gsoap_eml2_2::eml22__PlaneAngleUom minMaxUom, double horizontalEastWestMaxValue, gsoap_eml2_2::eml22__PlaneAngleUom horizontalEastWestMaxValueUom, const std::string & comment)
{
	pushBackInclinationRange(min, max, minMaxUom, comment);

	witsml2__OperatingConstraints* oc = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2)->OperatingConstraints;
	oc->HorizontalEastWestMaxValue = soap_new_eml22__PlaneAngleMeasureExt(gsoapProxy2_2->soap, 1);
	oc->HorizontalEastWestMaxValue->uom = soap_eml22__PlaneAngleUom2s(gsoapProxy2_2->soap, horizontalEastWestMaxValueUom);
	oc->HorizontalEastWestMaxValue->__item = horizontalEastWestMaxValue;
}

gsoap_eml2_2::witsml2__GyroToolConfiguration* ToolErrorModel::getOrCreateGyroToolConfig()
{
	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2);
	if (tem->GyroToolConfiguration == nullptr)  {
		tem->GyroToolConfiguration = soap_new_witsml2__GyroToolConfiguration(gsoapProxy2_2->soap, 1);
	}

	return tem->GyroToolConfiguration;
}

void ToolErrorModel::setXyzAccelerometer()
{
	getOrCreateGyroToolConfig()->AccelerometerAxisCombination = (witsml2__AccelerometerAxisCombination*)soap_malloc(gsoapProxy2_2->soap, sizeof(witsml2__AccelerometerAxisCombination));
	*getOrCreateGyroToolConfig()->AccelerometerAxisCombination = gsoap_eml2_2::witsml2__AccelerometerAxisCombination__xyz;
	getOrCreateGyroToolConfig()->XyAccelerometer = nullptr;
}

void ToolErrorModel::setXyAccelerometer(double cantAngle, gsoap_eml2_2::eml22__PlaneAngleUom cantAngleUom, bool switching)
{
	getOrCreateGyroToolConfig()->AccelerometerAxisCombination = (witsml2__AccelerometerAxisCombination*)soap_malloc(gsoapProxy2_2->soap, sizeof(witsml2__AccelerometerAxisCombination));
	*getOrCreateGyroToolConfig()->AccelerometerAxisCombination = gsoap_eml2_2::witsml2__AccelerometerAxisCombination__xy;
	getOrCreateGyroToolConfig()->XyAccelerometer = soap_new_witsml2__XyAccelerometer(gsoapProxy2_2->soap, 1);
	getOrCreateGyroToolConfig()->XyAccelerometer->CantAngle = soap_new_eml22__PlaneAngleMeasureExt(gsoapProxy2_2->soap, 1); 
	getOrCreateGyroToolConfig()->XyAccelerometer->CantAngle->__item = cantAngle;
	getOrCreateGyroToolConfig()->XyAccelerometer->CantAngle->uom = gsoap_eml2_2::soap_eml22__PlaneAngleUom2s(gsoapProxy2_2->soap, cantAngleUom);
	getOrCreateGyroToolConfig()->XyAccelerometer->Switching = switching;
}

void ToolErrorModel::setGyroReinitializationDistance(double value, gsoap_eml2_2::eml22__LengthUom uom)
{
	/*
	getOrCreateGyroToolConfig()->GyroReinitializationDistance = soap_new_eml22__LengthMeasureExt(gsoapProxy2_2->soap, 1);
	getOrCreateGyroToolConfig()->GyroReinitializationDistance->__item = value;
	getOrCreateGyroToolConfig()->GyroReinitializationDistance->uom = gsoap_eml2_2::soap_eml22__LengthUom2s(gsoapProxy2_2->soap, uom);
	*/
}

void ToolErrorModel::setNoiseReductionFactor(double value)
{
	getOrCreateGyroToolConfig()->NoiseReductionFactor = (double*)soap_malloc(gsoapProxy2_2->soap, sizeof(double));
	*getOrCreateGyroToolConfig()->NoiseReductionFactor = value;
}

void ToolErrorModel::setExternalReference(bool value)
{
	getOrCreateGyroToolConfig()->ExternalReference = (bool*)soap_malloc(gsoapProxy2_2->soap, sizeof(bool));
	*getOrCreateGyroToolConfig()->ExternalReference = value;
}

void ToolErrorModel::pushBackGyro(gsoap_eml2_2::witsml2__GyroAxisCombination axisCombination, gsoap_eml2_2::witsml2__GyroMode mode,
	double start, gsoap_eml2_2::eml22__PlaneAngleUom startUom,
	double end, gsoap_eml2_2::eml22__PlaneAngleUom endUom,
	double initialization, gsoap_eml2_2::eml22__PlaneAngleUom initializationUom,
	gsoap_eml2_2::eml22__LengthPerTimeUom speedUom, double speed,
	gsoap_eml2_2::eml22__LengthUom uom, double reinitializationDistance)
{
	witsml2__Gyro* gyro = soap_new_witsml2__Gyro(gsoapProxy2_2->soap, 1);
	getOrCreateGyroToolConfig()->Gyro.push_back(gyro);

	gyro->AxisCombination = axisCombination;
	gyro->Mode = mode;

	gyro->Start = soap_new_eml22__PlaneAngleMeasureExt(gsoapProxy2_2->soap, 1);
	gyro->Start->__item = start;
	gyro->Start->uom = gsoap_eml2_2::soap_eml22__PlaneAngleUom2s(gsoapProxy2_2->soap, startUom);

	gyro->End = soap_new_eml22__PlaneAngleMeasureExt(gsoapProxy2_2->soap, 1);
	gyro->End->__item = end;
	gyro->End->uom = gsoap_eml2_2::soap_eml22__PlaneAngleUom2s(gsoapProxy2_2->soap, endUom);

	gyro->Initialization = soap_new_eml22__PlaneAngleMeasureExt(gsoapProxy2_2->soap, 1);
	gyro->Initialization->__item = initialization;
	gyro->Initialization->uom = gsoap_eml2_2::soap_eml22__PlaneAngleUom2s(gsoapProxy2_2->soap, initializationUom);

	if (speed == speed)
	{
		gyro->Speed = soap_new_eml22__LengthPerTimeMeasureExt(gsoapProxy2_2->soap, 1);
		gyro->Speed->__item = speed;
		gyro->Speed->uom = gsoap_eml2_2::soap_eml22__LengthPerTimeUom2s(gsoapProxy2_2->soap, speedUom);
	}

	if (reinitializationDistance == reinitializationDistance)
	{
		gyro->GyroReinitializationDistance = soap_new_eml22__LengthMeasureExt(gsoapProxy2_2->soap, 1);
		gyro->GyroReinitializationDistance->__item = reinitializationDistance;
		gyro->GyroReinitializationDistance->uom = gsoap_eml2_2::soap_eml22__LengthUom2s(gsoapProxy2_2->soap, uom);
	}
}

void ToolErrorModel::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2);

	updateXml = false;
	for (size_t index = 0; index < tem->ErrorTermValue.size(); ++index) {
		ErrorTerm* et = epcDoc->getResqmlAbstractObjectByUuid<ErrorTerm>(getErrorTermUuid(index));
		pushBackErrorTerm(et, std::numeric_limits<double>::quiet_NaN(), "");
	}

	if (tem->Replaces != nullptr) {
		ToolErrorModel* previousTem = getEpcDocument()->getResqmlAbstractObjectByUuid<ToolErrorModel>(tem->Replaces->Uuid);
		setReplacedToolErrorModel(previousTem);
	}

	updateXml = true;
}

vector<Relationship> ToolErrorModel::getAllEpcRelationships() const
{
	vector<Relationship> result;

	// XML forward relationship
	std::vector<ErrorTerm*> ets = getErrorTermSet();
	for (size_t index = 0; index < ets.size(); ++index) {
		Relationship rel(ets[index]->getPartNameInEpcDocument(), "", ets[index]->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}

	witsml2__ToolErrorModel* tem = static_cast<witsml2__ToolErrorModel*>(gsoapProxy2_2);
	if (tem->Replaces != nullptr) {
		ToolErrorModel* previousTem = getEpcDocument()->getResqmlAbstractObjectByUuid<ToolErrorModel>(tem->Replaces->Uuid);
		Relationship rel(previousTem->getPartNameInEpcDocument(), "", previousTem->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}

	// XML backward relationship
	if (nextVersionToolErrorModel != nullptr) {
		Relationship rel(nextVersionToolErrorModel->getPartNameInEpcDocument(), "", nextVersionToolErrorModel->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}
