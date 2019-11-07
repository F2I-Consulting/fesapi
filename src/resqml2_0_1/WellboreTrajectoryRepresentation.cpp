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
#include "WellboreTrajectoryRepresentation.h"

#include <stdexcept>
#include <limits>

#include "H5public.h"

#include "WellboreInterpretation.h"
#include "../resqml2/MdDatum.h"
#include "WellboreFrameRepresentation.h"
#include "../resqml2/AbstractLocal3dCrs.h"
#include "../common/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace COMMON_NS;

const char* WellboreTrajectoryRepresentation::XML_TAG = "WellboreTrajectoryRepresentation";
const char* WellboreTrajectoryRepresentation::XML_NS = "resqml20";

WellboreTrajectoryRepresentation::WellboreTrajectoryRepresentation(WellboreInterpretation * interp, const string & guid, const std::string & title, RESQML2_NS::MdDatum * mdInfo)
{
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREWellboreTrajectoryRepresentation(interp->getGsoapContext());	
	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	if (dynamic_cast<RESQML2_NS::AbstractLocal3dCrs*>(mdInfo->getLocalCrs()) != nullptr) {
		rep->MdUom = static_cast<RESQML2_NS::AbstractLocal3dCrs*>(mdInfo->getLocalCrs())->getVerticalCrsUnit();
	}
	rep->StartMd = std::numeric_limits<double>::quiet_NaN();
	rep->FinishMd = std::numeric_limits<double>::quiet_NaN();

	setMdDatum(mdInfo);
	setInterpretation(interp);
}

WellboreTrajectoryRepresentation::WellboreTrajectoryRepresentation(WellboreInterpretation * interp, const string & guid, const std::string & title, DeviationSurveyRepresentation * deviationSurvey)
{
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREWellboreTrajectoryRepresentation(interp->getGsoapContext());
	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);

	RESQML2_NS::MdDatum * mdInfo = deviationSurvey->getMdDatum();
	setMdDatum(mdInfo);

	ULONG64 stationCount = deviationSurvey->getXyzPointCountOfPatch(0);
	double* mdValues = new double[stationCount];
	deviationSurvey->getMdValues(mdValues);
	rep->StartMd = mdValues[0];
	rep->FinishMd = mdValues[stationCount-1];
	delete[] mdValues;

	setInterpretation(interp);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	if (dynamic_cast<RESQML2_NS::AbstractLocal3dCrs*>(mdInfo->getLocalCrs()) != nullptr) {
		rep->MdUom = static_cast<RESQML2_NS::AbstractLocal3dCrs*>(mdInfo->getLocalCrs())->getVerticalCrsUnit();
	}
	rep->StartMd = std::numeric_limits<double>::quiet_NaN();
	rep->FinishMd = std::numeric_limits<double>::quiet_NaN();
}

void WellboreTrajectoryRepresentation::setMinimalGeometry(double startMd, double endMd)
{
	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	rep->StartMd = startMd;
	rep->FinishMd = endMd;
}

void WellboreTrajectoryRepresentation::setGeometry(double * controlPoints, double startMd, double endMd, unsigned int controlPointCount, int lineKind, COMMON_NS::AbstractHdfProxy * proxy, RESQML2_NS::AbstractLocal3dCrs* localCrs)
{
	if (controlPoints == nullptr) {
		throw invalid_argument("The control points are missing.");
	}
	if (controlPointCount == 0) {
		throw invalid_argument("The control point count cannot be 0.");
	}

	setMinimalGeometry(startMd, endMd);

	_resqml20__WellboreTrajectoryRepresentation* const rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);

	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
	}

	rep->Geometry = soap_new_resqml20__ParametricLineGeometry(gsoapProxy2_0_1->soap);
	resqml20__ParametricLineGeometry* paramLine = soap_new_resqml20__ParametricLineGeometry(gsoapProxy2_0_1->soap);
	paramLine->LocalCrs = localCrs->newResqmlReference();
	rep->Geometry = paramLine;

	paramLine->KnotCount = controlPointCount;
	paramLine->LineKindIndex = lineKind;

	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
	}
	getRepository()->addRelationship(this, proxy);

	// XML control points
	resqml20__Point3dHdf5Array* xmlControlPoints = soap_new_resqml20__Point3dHdf5Array(gsoapProxy2_0_1->soap);
	xmlControlPoints->Coordinates = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlControlPoints->Coordinates->HdfProxy = proxy->newResqmlReference();
	xmlControlPoints->Coordinates->PathInHdfFile = "/RESQML/" + rep->uuid + "/controlPoints";
	paramLine->ControlPoints = xmlControlPoints;

	// HDF control points
	hsize_t dim[] = { controlPointCount, 3 };
	proxy->writeArrayNdOfDoubleValues(rep->uuid, "controlPoints", controlPoints, dim, 2);

	getRepository()->addRelationship(this, localCrs);
}

void WellboreTrajectoryRepresentation::setGeometry(double * controlPoints, double* controlPointParameters, unsigned int controlPointCount, int lineKind,
	COMMON_NS::AbstractHdfProxy * proxy, RESQML2_NS::AbstractLocal3dCrs* localCrs)
{
	if (controlPointParameters == nullptr) {
		throw invalid_argument("The control points parameters are missing.");
	}

	setGeometry(controlPoints, controlPointParameters[0], controlPointParameters[controlPointCount - 1], controlPointCount, lineKind, proxy, localCrs);
	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	resqml20__ParametricLineGeometry* paramLine = static_cast<resqml20__ParametricLineGeometry*>(rep->Geometry);

	// XML control point parameters
	resqml20__DoubleHdf5Array* xmlControlPointParameters = soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
	xmlControlPointParameters->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlControlPointParameters->Values->HdfProxy = proxy->newResqmlReference();
	xmlControlPointParameters->Values->PathInHdfFile = "/RESQML/" + rep->uuid + "/controlPointParameters";
	paramLine->ControlPointParameters = xmlControlPointParameters;

	// HDF control point parameters
	const hsize_t dimParamDataSet = controlPointCount;
	proxy->writeArrayNdOfDoubleValues(rep->uuid, "controlPointParameters", controlPointParameters, &dimParamDataSet, 1);
}

void WellboreTrajectoryRepresentation::setGeometry(double * controlPoints,
	double * tangentVectors, double* controlPointParameters, unsigned int controlPointCount, int lineKind,
	COMMON_NS::AbstractHdfProxy * proxy, RESQML2_NS::AbstractLocal3dCrs* localCrs)
{
	setGeometry(controlPoints, controlPointParameters, controlPointCount, lineKind, proxy, localCrs);

	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);

	resqml20__ParametricLineGeometry* paramLine = static_cast<resqml20__ParametricLineGeometry*>(rep->Geometry);
	// XML tangent vectors
	resqml20__Point3dHdf5Array* xmlTangentVectors = soap_new_resqml20__Point3dHdf5Array(gsoapProxy2_0_1->soap);
	xmlTangentVectors->Coordinates = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlTangentVectors->Coordinates->HdfProxy = proxy->newResqmlReference();
	xmlTangentVectors->Coordinates->PathInHdfFile = "/RESQML/" + rep->uuid + "/tangentVectors";
	paramLine->TangentVectors = xmlTangentVectors;

	// HDF tangent vectors
	hsize_t dim[] = { controlPointCount, 3 };
	proxy->writeArrayNdOfDoubleValues(rep->uuid, "tangentVectors", tangentVectors, dim, 2);
}

void WellboreTrajectoryRepresentation::loadTargetRelationships()
{
	AbstractRepresentation::loadTargetRelationships();

	_resqml20__WellboreTrajectoryRepresentation const * rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);

	eml20__DataObjectReference const * dor = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1)->MdDatum;
	convertDorIntoRel<RESQML2_NS::MdDatum>(dor);

	dor = getDeviationSurveyDor();
	if (dor != nullptr) {
		convertDorIntoRel<DeviationSurveyRepresentation>(dor);
	}

	if (rep->ParentIntersection != nullptr) {
		dor = rep->ParentIntersection->ParentTrajectory;
		convertDorIntoRel<WellboreTrajectoryRepresentation>(dor);
	}
}

void WellboreTrajectoryRepresentation::addParentTrajectory(double kickoffMd, double parentMd, WellboreTrajectoryRepresentation* parentTrajRep)
{
	getRepository()->addRelationship(this, parentTrajRep);

	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	rep->ParentIntersection = soap_new_resqml20__WellboreTrajectoryParentIntersection(rep->soap);
	rep->ParentIntersection->KickoffMd = kickoffMd;
	rep->ParentIntersection->ParentMd = parentMd;
	rep->ParentIntersection->ParentTrajectory = parentTrajRep->newResqmlReference();
}

WellboreTrajectoryRepresentation* WellboreTrajectoryRepresentation::getParentTrajectory() const
{
	_resqml20__WellboreTrajectoryRepresentation const * rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	return rep->ParentIntersection == nullptr ? nullptr : getRepository()->getDataObjectByUuid<WellboreTrajectoryRepresentation>(rep->ParentIntersection->ParentTrajectory->UUID);
}

double WellboreTrajectoryRepresentation::getParentTrajectoryMd() const
{
	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->ParentIntersection != nullptr) {
		return rep->ParentIntersection->ParentMd;
	}

	throw logic_error("This wellbore trajectory has no parent trajecory.");
}

std::vector<WellboreTrajectoryRepresentation *> WellboreTrajectoryRepresentation::getChildrenTrajectorySet() const
{
	return getRepository()->getSourceObjects<WellboreTrajectoryRepresentation>(this);
}

ULONG64 WellboreTrajectoryRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index patch is not in the allowed range of patch.");
	}

	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->Geometry == nullptr) {
		return 0;
	}
	return static_cast<resqml20__ParametricLineGeometry*>(rep->Geometry)->KnotCount;
}

void WellboreTrajectoryRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index patch is not in the allowed range of patch");
	}

	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->Geometry != nullptr) {
		resqml20__ParametricLineGeometry* paramLine = static_cast<resqml20__ParametricLineGeometry*>(rep->Geometry);
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__Point3dHdf5Array*>(paramLine->ControlPoints)->Coordinates;
		COMMON_NS::AbstractHdfProxy * hdfProxy = getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The HDF proxy is missing.");
		}
		hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, xyzPoints);
	}
	else {
		throw invalid_argument("The wellbore trajectory has no geometry.");
	}
}

int WellboreTrajectoryRepresentation::getGeometryKind() const
{
	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->Geometry == nullptr) {
		throw logic_error("This trajectory has not got any geometry.");
	}
	if (rep->Geometry->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineGeometry) {
		throw logic_error("This kind of parametric line is not yet supported for a wellbore trajectory.");
	}
	return static_cast<resqml20__ParametricLineGeometry*>(rep->Geometry)->LineKindIndex;
}

bool WellboreTrajectoryRepresentation::hasMdValues() const
{
	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->Geometry == nullptr) {
		return false;
	}
	if (rep->Geometry->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineGeometry) {
		throw logic_error("This kind of parametric line is not yet supported for a wellbore trajectory.");
	}
	return static_cast<resqml20__ParametricLineGeometry*>(rep->Geometry)->ControlPointParameters != nullptr;
}

gsoap_resqml2_0_1::eml20__LengthUom WellboreTrajectoryRepresentation::getMdUom() const
{
	return static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1)->MdUom;
}

void WellboreTrajectoryRepresentation::getMdValues(double * values) const
{
	if (!hasMdValues()) {
		throw invalid_argument("This trajectory has not got any md value.");
	}
		
	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (static_cast<resqml20__ParametricLineGeometry*>(rep->Geometry)->ControlPointParameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__DoubleHdf5Array*>(static_cast<resqml20__ParametricLineGeometry*>(rep->Geometry)->ControlPointParameters)->Values;
		COMMON_NS::AbstractHdfProxy * hdfProxy = getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The HDF proxy is missing.");
		}
		hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, values);
	}
	else {
		throw invalid_argument("Mds can only be defined using DoubleHdf5Array for now in fesapi.");
	}
}

double WellboreTrajectoryRepresentation::getStartMd() const
{
	return static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1)->StartMd;
}

double WellboreTrajectoryRepresentation::getFinishMd() const
{
	return static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1)->FinishMd;
}

bool WellboreTrajectoryRepresentation::hasTangentVectors() const
{
	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->Geometry == nullptr) {
		return false;
	}
	if (rep->Geometry->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineGeometry) {
		throw logic_error("This kind of parametric line is not supported for a wellbore trajectory yet.");
	}
	return static_cast<resqml20__ParametricLineGeometry*>(rep->Geometry)->TangentVectors != nullptr;
}

void WellboreTrajectoryRepresentation::getTangentVectors(double* tangentVectors)
{
	if (!hasTangentVectors()) {
		throw invalid_argument("This trajectory has not got any tangent vector.");
	}
		
	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	eml20__Hdf5Dataset const * dataset = static_cast<resqml20__Point3dHdf5Array*>(static_cast<resqml20__ParametricLineGeometry*>(rep->Geometry)->TangentVectors)->Coordinates;
	COMMON_NS::AbstractHdfProxy * hdfProxy = getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
	if (hdfProxy == nullptr) {
		throw invalid_argument("The HDF proxy is missing.");
	}
	hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, tangentVectors);
}

void WellboreTrajectoryRepresentation::setMdDatum(RESQML2_NS::MdDatum * mdDatum)
{
	if (mdDatum == nullptr) {
		throw invalid_argument("The md Datum is missing.");
	}
	if (getRepository() == nullptr) {
		mdDatum->getRepository()->addOrReplaceDataObject(this);
	}

	getRepository()->addRelationship(this, mdDatum);

	static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1)->MdDatum = mdDatum->newResqmlReference();
}

RESQML2_NS::MdDatum * WellboreTrajectoryRepresentation::getMdDatum() const
{
	return static_cast<RESQML2_NS::MdDatum*>(getRepository()->getDataObjectByUuid(getMdDatumUuid()));
}

std::string WellboreTrajectoryRepresentation::getMdDatumUuid() const
{
	return static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1)->MdDatum->UUID;
}

gsoap_resqml2_0_1::eml20__DataObjectReference* WellboreTrajectoryRepresentation::getHdfProxyDor() const
{
	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->Geometry != nullptr) {
		resqml20__ParametricLineGeometry* paramLine = static_cast<resqml20__ParametricLineGeometry*>(rep->Geometry);
		return static_cast<resqml20__Point3dHdf5Array*>(paramLine->ControlPoints)->Coordinates->HdfProxy;
	}
	else {
		return nullptr;
	}
}

gsoap_resqml2_0_1::_resqml20__WellboreTrajectoryRepresentation* WellboreTrajectoryRepresentation::getSpecializedGsoapProxy() const
{
	cannotBePartial();

	return static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
}

gsoap_resqml2_0_1::eml20__DataObjectReference* WellboreTrajectoryRepresentation::getLocalCrsDor(unsigned int patchIndex) const
{
	if (patchIndex > 0) {
		throw out_of_range("There is no more than one patch in a wellbore trajectory.");
	}

	_resqml20__WellboreTrajectoryRepresentation* rep = getSpecializedGsoapProxy();
	return rep->Geometry != nullptr ? static_cast<resqml20__ParametricLineGeometry*>(rep->Geometry)->LocalCrs : nullptr;
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
	getRepository()->addRelationship(this, deviationSurvey);

	getSpecializedGsoapProxy()->DeviationSurvey = deviationSurvey->newResqmlReference();
}

DeviationSurveyRepresentation* WellboreTrajectoryRepresentation::getDeviationSurvey() const
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* dsDor = getDeviationSurveyDor();

	return dsDor == nullptr ? nullptr : repository->getDataObjectByUuid<DeviationSurveyRepresentation>(dsDor->UUID);
}

std::vector<RESQML2_NS::WellboreFrameRepresentation *> WellboreTrajectoryRepresentation::getWellboreFrameRepresentationSet() const
{
	return getRepository()->getSourceObjects<RESQML2_NS::WellboreFrameRepresentation>(this);
}

unsigned int WellboreTrajectoryRepresentation::getWellboreFrameRepresentationCount() const
{
	return getWellboreFrameRepresentationSet().size();
}

RESQML2_NS::WellboreFrameRepresentation * WellboreTrajectoryRepresentation::getWellboreFrameRepresentation(unsigned int index) const
{
	const std::vector<RESQML2_NS::WellboreFrameRepresentation *>& wfrs = getWellboreFrameRepresentationSet();
	
	if (index >= wfrs.size()) {
		throw out_of_range("The index if out of range");
	}

	return wfrs[index];
}