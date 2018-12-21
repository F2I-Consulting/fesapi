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
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"

#include <stdexcept>

#include "H5public.h"

#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2/MdDatum.h"
#include "resqml2_0_1/WellboreFrameRepresentation.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "common/AbstractHdfProxy.h"

#include "witsml1_4_1_1/Trajectory.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;
using namespace COMMON_NS;

const char* WellboreTrajectoryRepresentation::XML_TAG = "WellboreTrajectoryRepresentation";

WellboreTrajectoryRepresentation::WellboreTrajectoryRepresentation(WellboreInterpretation* interp, const string & guid, const std::string & title, RESQML2_NS::MdDatum * mdInfo) :
	AbstractRepresentation(interp, mdInfo->getLocalCrs()), witsmlTrajectory(nullptr)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREWellboreTrajectoryRepresentation(interp->getGsoapContext(), 1);	
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);

	setMdDatum(mdInfo);

	localCrs = mdInfo->getLocalCrs();
	localCrs->addRepresentation(this);

	setInterpretation(interp);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	if (dynamic_cast<RESQML2_NS::AbstractLocal3dCrs*>(mdInfo->getLocalCrs()) != nullptr) {
		rep->MdUom = static_cast<RESQML2_NS::AbstractLocal3dCrs*>(mdInfo->getLocalCrs())->getVerticalCrsUnit();
	}
}

WellboreTrajectoryRepresentation::WellboreTrajectoryRepresentation(WellboreInterpretation* interp, const string & guid, const std::string & title, DeviationSurveyRepresentation * deviationSurvey) :
	AbstractRepresentation(interp, deviationSurvey->getLocalCrs()), witsmlTrajectory(nullptr)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREWellboreTrajectoryRepresentation(interp->getGsoapContext(), 1);
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);

	RESQML2_NS::MdDatum * mdInfo = deviationSurvey->getMdDatum();
	setMdDatum(mdInfo);

	ULONG64 stationCount = deviationSurvey->getXyzPointCountOfPatch(0);
	double* mdValues = new double[stationCount];
	deviationSurvey->getMdValues(mdValues);
	rep->StartMd = mdValues[0];
	rep->FinishMd = mdValues[stationCount-1];
	delete[] mdValues;

	localCrs = mdInfo->getLocalCrs();
	localCrs->addRepresentation(this);

	setInterpretation(interp);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	if (dynamic_cast<RESQML2_NS::AbstractLocal3dCrs*>(mdInfo->getLocalCrs()) != nullptr) {
		rep->MdUom = static_cast<RESQML2_NS::AbstractLocal3dCrs*>(mdInfo->getLocalCrs())->getVerticalCrsUnit();
	}
}

void WellboreTrajectoryRepresentation::setGeometry(double * controlPoints, const double & startMd, const double & endMd, const unsigned int & controlPointCount, const int & lineKind, COMMON_NS::AbstractHdfProxy * proxy)
{
	if (controlPoints == nullptr)
		throw invalid_argument("The control points are missing.");
	if (controlPointCount == 0)
		throw invalid_argument("The control point count cannot be 0.");
	if (proxy == nullptr)
		throw invalid_argument("The HDF proxy is missing.");

	setHdfProxy(proxy);

	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);

	rep->Geometry = soap_new_resqml2__ParametricLineGeometry(gsoapProxy2_0_1->soap, 1);
	resqml2__ParametricLineGeometry* paramLine = soap_new_resqml2__ParametricLineGeometry(gsoapProxy2_0_1->soap, 1);
	paramLine->LocalCrs = localCrs->newResqmlReference();
	rep->StartMd = startMd;
	rep->FinishMd = endMd;
	rep->Geometry = paramLine;

	paramLine->KnotCount = controlPointCount;
	paramLine->LineKindIndex = lineKind;

	// XML control points
	resqml2__Point3dHdf5Array* xmlControlPoints = soap_new_resqml2__Point3dHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlControlPoints->Coordinates = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlControlPoints->Coordinates->HdfProxy = hdfProxy->newResqmlReference();
	xmlControlPoints->Coordinates->PathInHdfFile = "/RESQML/" + rep->uuid + "/controlPoints";
	paramLine->ControlPoints = xmlControlPoints;

	// HDF control points
	hsize_t dim[] = { controlPointCount, 3 };
	hdfProxy->writeArrayNdOfDoubleValues(rep->uuid, "controlPoints", controlPoints, dim, 2);
}

void WellboreTrajectoryRepresentation::setGeometry(double * controlPoints, double* controlPointParameters, const unsigned int & controlPointCount,
	COMMON_NS::AbstractHdfProxy * proxy)
{
	if (controlPointParameters == nullptr)
		throw invalid_argument("The control points parameters are missing.");

	setGeometry(controlPoints, controlPointParameters[0], controlPointParameters[controlPointCount - 1], controlPointCount, 2, proxy);
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	resqml2__ParametricLineGeometry* paramLine = static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry);

	// XML control point parameters
	resqml2__DoubleHdf5Array* xmlControlPointParameters = soap_new_resqml2__DoubleHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlControlPointParameters->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlControlPointParameters->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlControlPointParameters->Values->PathInHdfFile = "/RESQML/" + rep->uuid + "/controlPointParameters";
	paramLine->ControlPointParameters = xmlControlPointParameters;

	// HDF control point parameters
	hsize_t dimParamDataSet[] = {controlPointCount};
	hdfProxy->writeArrayNdOfDoubleValues(rep->uuid, "controlPointParameters", controlPointParameters, dimParamDataSet, 1);
}

void WellboreTrajectoryRepresentation::setGeometry(double * controlPoints,
	double * tangentVectors, double* controlPointParameters, const unsigned int & controlPointCount,
	COMMON_NS::AbstractHdfProxy * proxy)
{
	setGeometry(controlPoints, controlPointParameters, controlPointCount, proxy);

	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	resqml2__ParametricLineGeometry* paramLine = static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry);
	paramLine->LineKindIndex = 5;

	// XML tangent vectors
	resqml2__Point3dHdf5Array* xmlTangentVectors = soap_new_resqml2__Point3dHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlTangentVectors->Coordinates = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlTangentVectors->Coordinates->HdfProxy = hdfProxy->newResqmlReference();
	xmlTangentVectors->Coordinates->PathInHdfFile = "/RESQML/" + rep->uuid + "/tangentVectors";
	paramLine->TangentVectors = xmlTangentVectors;

	// HDF tangent vectors
	hsize_t dim[] = { controlPointCount, 3 };
	hdfProxy->writeArrayNdOfDoubleValues(rep->uuid, "tangentVectors", tangentVectors, dim, 2);
}

void WellboreTrajectoryRepresentation::setWitsmlTrajectory(WITSML1_4_1_1_NS::Trajectory * witsmlTraj)
{
	witsmlTrajectory = witsmlTraj;
	witsmlTraj->resqmlWellboreTrajectoryRepresentation = this;

	if (updateXml) {
		resqml2__obj_USCOREWellboreTrajectoryRepresentation* resqmlTraj = static_cast<resqml2__obj_USCOREWellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
		resqmlTraj->WitsmlTrajectory = witsmlTraj->newResqmlReference();
	}
}

vector<Relationship> WellboreTrajectoryRepresentation::getAllEpcRelationships() const
{
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	
	vector<Relationship> result = AbstractRepresentation::getAllEpcRelationships();

	// XML forward relationship
	RESQML2_NS::MdDatum* mdDatum = getMdDatum();
	if (mdDatum != nullptr) {
		Relationship relMdInfo(mdDatum->getPartNameInEpcDocument(), "", getMdDatumUuid());
		relMdInfo.setDestinationObjectType();
		result.push_back(relMdInfo);
	}
	else {
		throw domain_error("The MD information associated to the WellboreFeature trajectory cannot be nullptr.");
	}

	DeviationSurveyRepresentation* dsr = getDeviationSurvey();
	if (dsr != nullptr) {
		Relationship relDsr(dsr->getPartNameInEpcDocument(), "", getDeviationSurveyDor()->Title);
		relDsr.setDestinationObjectType();
		result.push_back(relDsr);
	}

	WellboreTrajectoryRepresentation* parentTraj = getParentTrajectory();
	if (parentTraj != nullptr) {
		Relationship relParentTraj(parentTraj->getPartNameInEpcDocument(), "", rep->ParentIntersection->ParentTrajectory->UUID);
		relParentTraj.setDestinationObjectType();
		result.push_back(relParentTraj);
	}

	if (witsmlTrajectory != nullptr) {
		Relationship relWitsmlTraj(witsmlTrajectory->getPartNameInEpcDocument(), "", witsmlTrajectory->getUuid());
		relWitsmlTraj.setDestinationObjectType();
		result.push_back(relWitsmlTraj);
	}

	// XML backward relationship
	for (size_t i = 0 ; i < childrenTrajSet.size(); ++i) {
		Relationship relChildrenTraj(childrenTrajSet[i]->getPartNameInEpcDocument(), "", childrenTrajSet[i]->getUuid());
		relChildrenTraj.setSourceObjectType();
		result.push_back(relChildrenTraj);
	}

	for (size_t i = 0; i < wellboreFrameRepresentationSet.size(); ++i) {
		Relationship relFrame(wellboreFrameRepresentationSet[i]->getPartNameInEpcDocument(), "", wellboreFrameRepresentationSet[i]->getUuid());
		relFrame.setSourceObjectType();
		result.push_back(relFrame);
	}

	return result;
}

void WellboreTrajectoryRepresentation::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	AbstractRepresentation::importRelationshipSetFromEpc(epcDoc);

	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);

	RESQML2_NS::MdDatum* mdDatum = epcDoc->getResqmlAbstractObjectByUuid<RESQML2_NS::MdDatum>(getMdDatumUuid());
	if (mdDatum != nullptr) {
		updateXml = false;
		setMdDatum(mdDatum);
		updateXml = true;
	}

	gsoap_resqml2_0_1::eml20__DataObjectReference* dsrDor = getDeviationSurveyDor();
	if (dsrDor != nullptr)
	{
		DeviationSurveyRepresentation* dsr = epcDoc->getResqmlAbstractObjectByUuid<DeviationSurveyRepresentation>(dsrDor->UUID);
		if (dsr == nullptr) { // partial transfer
			getEpcDocument()->createPartial(dsrDor);
			dsr = getEpcDocument()->getResqmlAbstractObjectByUuid<DeviationSurveyRepresentation>(dsrDor->UUID);
		}
		if (dsr == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
		updateXml = false;
		setDeviationSurvey(dsr);
		updateXml = true;
	}

	if (rep->ParentIntersection != nullptr) {
		WellboreTrajectoryRepresentation* parentTraj = epcDoc->getResqmlAbstractObjectByUuid<RESQML2_0_1_NS::WellboreTrajectoryRepresentation>(rep->ParentIntersection->ParentTrajectory->UUID);
		parentTraj->addChildrenTrajectory(this);
	}

	if (rep->WitsmlTrajectory != nullptr) {
		WITSML1_4_1_1_NS::Trajectory* tmp = static_cast<WITSML1_4_1_1_NS::Trajectory*>(epcDoc->getWitsmlAbstractObjectByUuid(rep->WitsmlTrajectory->UUID));
		if (tmp)
		{
			updateXml = false;
			setWitsmlTrajectory(tmp);
			updateXml = true;
		}
	}
}

void WellboreTrajectoryRepresentation::addParentTrajectory(const double & kickoffMd, const double & parentMd, WellboreTrajectoryRepresentation* parentTrajRep)
{
	parentTrajRep->addChildrenTrajectory(this);

	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	rep->ParentIntersection = soap_new_resqml2__WellboreTrajectoryParentIntersection(rep->soap, 1);
	rep->ParentIntersection->KickoffMd = kickoffMd;
	rep->ParentIntersection->ParentMd = parentMd;
	rep->ParentIntersection->ParentTrajectory = parentTrajRep->newResqmlReference();
}

WellboreTrajectoryRepresentation* WellboreTrajectoryRepresentation::getParentTrajectory() const
{
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);

	if (rep->ParentIntersection == nullptr)
		return nullptr;

	WellboreTrajectoryRepresentation* result = nullptr;
	COMMON_NS::AbstractObject* obj = getEpcDocument()->getResqmlAbstractObjectByUuid(rep->ParentIntersection->ParentTrajectory->UUID);

	if (dynamic_cast<WellboreTrajectoryRepresentation*>(obj) != nullptr)
		return static_cast<WellboreTrajectoryRepresentation*>(obj);
	else
		throw invalid_argument("The parent trajectory (or its reference) of this wellbore trajectory does not look valid regarding EPC/XML");
}

const double& WellboreTrajectoryRepresentation::getParentTrajectoryMd() const
{
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->ParentIntersection != nullptr) {
		return rep->ParentIntersection->ParentMd;
	}
	else {
		throw logic_error("This wellbore trajectory has no parent trajecory.");
	}
}

const std::vector<WellboreTrajectoryRepresentation*> & WellboreTrajectoryRepresentation::getChildrenTrajectorySet() const
{
	return childrenTrajSet;
}

ULONG64 WellboreTrajectoryRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index patch is not in the allowed range of patch.");
	}

	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->Geometry == nullptr) {
		return 0;
	}
	return static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry)->KnotCount;
}

void WellboreTrajectoryRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index patch is not in the allowed range of patch");
	}

	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->Geometry != nullptr) {
		resqml2__ParametricLineGeometry* paramLine = static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry);
		hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__Point3dHdf5Array*>(paramLine->ControlPoints)->Coordinates->PathInHdfFile, xyzPoints);
	}
	else {
		throw invalid_argument("The wellbore trajectory has no geometry.");
	}
}

int WellboreTrajectoryRepresentation::getGeometryKind() const
{
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->Geometry == nullptr) {
		throw logic_error("This trajectory has not got any geometry.");
	}
	if (rep->Geometry->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineGeometry) {
		throw logic_error("This kind of parametric line is not yet supported for a wellbore trajectory.");
	}
	return static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry)->LineKindIndex;
}

bool WellboreTrajectoryRepresentation::hasMdValues() const
{
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->Geometry == nullptr) {
		return false;
	}
	if (rep->Geometry->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineGeometry) {
		throw logic_error("This kind of parametric line is not yet supported for a wellbore trajectory.");
	}
	return static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry)->ControlPointParameters != nullptr;
}

gsoap_resqml2_0_1::eml20__LengthUom WellboreTrajectoryRepresentation::getMdUom() const
{
	return static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1)->MdUom;
}

void WellboreTrajectoryRepresentation::getMdValues(double * values)
{
	if (!hasMdValues()) {
		throw invalid_argument("This trajectory has not got any md value.");
	}
	if (hdfProxy == nullptr) {
		throw invalid_argument("The HDF proxy is missing.");
	}
		
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry)->ControlPointParameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
		resqml2__DoubleHdf5Array* xmlControlPointParameters = static_cast<resqml2__DoubleHdf5Array*>(static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry)->ControlPointParameters);
		hdfProxy->readArrayNdOfDoubleValues(xmlControlPointParameters->Values->PathInHdfFile, values);
	}
	else {
		throw invalid_argument("Mds can only be defined using DoubleHdf5Array for now in fesapi.");
	}
}

double WellboreTrajectoryRepresentation::getStartMd() const
{
	return static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1)->StartMd;
}

double WellboreTrajectoryRepresentation::getFinishMd() const
{
	return static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1)->FinishMd;
}

bool WellboreTrajectoryRepresentation::hasTangentVectors() const
{
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->Geometry == nullptr) {
		return false;
	}
	if (rep->Geometry->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineGeometry) {
		throw logic_error("This kind of parametric line is not supported for a wellbore trajectory yet.");
	}
	return static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry)->TangentVectors != nullptr;
}

void WellboreTrajectoryRepresentation::getTangentVectors(double* tangentVectors)
{
	if (!hasTangentVectors()) {
		throw invalid_argument("This trajectory has not got any tangent vector.");
	}
	if (hdfProxy == nullptr) {
		throw invalid_argument("The HDF proxy is missing.");
	}
		
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	resqml2__Point3dHdf5Array* xmlTangentVectors = static_cast<resqml2__Point3dHdf5Array*>(static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry)->TangentVectors);
	hdfProxy->readArrayNdOfDoubleValues(xmlTangentVectors->Coordinates->PathInHdfFile, tangentVectors);
}

void WellboreTrajectoryRepresentation::setMdDatum(RESQML2_NS::MdDatum* mdDatum)
{
	if (mdDatum == nullptr) {
		throw invalid_argument("The md Datum is missing.");
	}

	mdDatum->addWellboreTrajectoryRepresentation(this);

	if (updateXml) {
		static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1)->MdDatum = mdDatum->newResqmlReference();
	}
}

RESQML2_NS::MdDatum * WellboreTrajectoryRepresentation::getMdDatum() const
{
	return static_cast<RESQML2_NS::MdDatum*>(getEpcDocument()->getResqmlAbstractObjectByUuid(getMdDatumUuid()));
}

std::string WellboreTrajectoryRepresentation::getMdDatumUuid() const
{
	return static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1)->MdDatum->UUID;
}

std::string WellboreTrajectoryRepresentation::getHdfProxyUuid() const
{
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->Geometry != nullptr) {
		resqml2__ParametricLineGeometry* paramLine = static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry);
		return static_cast<resqml2__Point3dHdf5Array*>(paramLine->ControlPoints)->Coordinates->HdfProxy->UUID;
	}
	else {
		return "";
	}
}

gsoap_resqml2_0_1::_resqml2__WellboreTrajectoryRepresentation* WellboreTrajectoryRepresentation::getSpecializedGsoapProxy() const
{
	cannotBePartial();

	return static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
}

gsoap_resqml2_0_1::eml20__DataObjectReference* WellboreTrajectoryRepresentation::getLocalCrsDor() const
{
	_resqml2__WellboreTrajectoryRepresentation* rep = getSpecializedGsoapProxy();
	return rep->Geometry != nullptr ? static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry)->LocalCrs : nullptr;
}

gsoap_resqml2_0_1::eml20__DataObjectReference* WellboreTrajectoryRepresentation::getDeviationSurveyDor() const
{
	return getSpecializedGsoapProxy()->DeviationSurvey;
}

bool WellboreTrajectoryRepresentation::hasGeometry() const
{
	return getSpecializedGsoapProxy()->Geometry != nullptr;
}

void WellboreTrajectoryRepresentation::setDeviationSurvey(DeviationSurveyRepresentation* deviationSurvey)
{
	if (updateXml) {
		getSpecializedGsoapProxy()->DeviationSurvey = deviationSurvey->newResqmlReference();
	}

	deviationSurvey->addTrajectory(this);
}

DeviationSurveyRepresentation* WellboreTrajectoryRepresentation::getDeviationSurvey() const
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* dsDor = getDeviationSurveyDor();

	return dsDor == nullptr ? nullptr : epcDocument->getResqmlAbstractObjectByUuid<DeviationSurveyRepresentation>(dsDor->UUID);
}

