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

#include "../resqml2/AbstractLocal3dCrs.h"
#include "../resqml2/DeviationSurveyRepresentation.h"
#include "../resqml2/MdDatum.h"
#include "../resqml2/WellboreFrameRepresentation.h"
#include "../resqml2/WellboreInterpretation.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace COMMON_NS;

WellboreTrajectoryRepresentation::WellboreTrajectoryRepresentation(RESQML2_NS::WellboreInterpretation * interp, const string & guid, const std::string & title, RESQML2_NS::MdDatum * mdInfo)
{
	if (interp == nullptr) {
		throw invalid_argument("The represented wellbore interpretation cannot be null.");
	}
	if (mdInfo == nullptr) {
		throw invalid_argument("The associated MD information cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREWellboreTrajectoryRepresentation(interp->getGsoapContext());	
	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	if (mdInfo->getLocalCrs() != nullptr) {
		rep->MdUom = mdInfo->getLocalCrs()->getVerticalCrsUnit();
	}
	rep->StartMd = std::numeric_limits<double>::quiet_NaN();
	rep->FinishMd = std::numeric_limits<double>::quiet_NaN();

	setMdDatum(mdInfo);
	setInterpretation(interp);
}

WellboreTrajectoryRepresentation::WellboreTrajectoryRepresentation(RESQML2_NS::WellboreInterpretation * interp, const string & guid, const std::string & title, RESQML2_NS::DeviationSurveyRepresentation * deviationSurvey)
{
	if (interp == nullptr) {
		throw invalid_argument("The represented wellbore interpretation cannot be null.");
	}
	if (deviationSurvey == nullptr) {
		throw invalid_argument("The deviation survey cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREWellboreTrajectoryRepresentation(interp->getGsoapContext());
	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);

	RESQML2_NS::MdDatum * mdInfo = deviationSurvey->getMdDatum();
	setMdDatum(mdInfo);

	const ULONG64 stationCount = deviationSurvey->getXyzPointCountOfPatch(0);
	std::unique_ptr<double[]> mdValues(new double[stationCount]);
	deviationSurvey->getMdValues(mdValues.get());
	rep->StartMd = mdValues[0];
	rep->FinishMd = mdValues[stationCount-1];

	setInterpretation(interp);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	if (mdInfo->getLocalCrs() != nullptr) {
		rep->MdUom = mdInfo->getLocalCrs()->getVerticalCrsUnit();
	}
}

void WellboreTrajectoryRepresentation::setMinimalGeometry(double startMd, double endMd)
{
	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	rep->StartMd = startMd;
	rep->FinishMd = endMd;
}

void WellboreTrajectoryRepresentation::setGeometry(double const* controlPoints, double startMd, double endMd, unsigned int controlPointCount, int lineKind, EML2_NS::AbstractHdfProxy * proxy, RESQML2_NS::AbstractLocal3dCrs* localCrs)
{
	if (controlPoints == nullptr) {
		throw invalid_argument("The control points are missing.");
	}
	if (controlPointCount == 0) {
		throw invalid_argument("The control point count cannot be 0.");
	}
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	setMinimalGeometry(startMd, endMd);

	_resqml20__WellboreTrajectoryRepresentation* const rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);

	rep->Geometry = soap_new_resqml20__ParametricLineGeometry(gsoapProxy2_0_1->soap);
	resqml20__ParametricLineGeometry* paramLine = soap_new_resqml20__ParametricLineGeometry(gsoapProxy2_0_1->soap);
	paramLine->LocalCrs = localCrs->newResqmlReference();
	rep->Geometry = paramLine;

	paramLine->KnotCount = controlPointCount;
	paramLine->LineKindIndex = lineKind;

	getRepository()->addRelationship(this, proxy);

	// XML control points
	resqml20__Point3dHdf5Array* xmlControlPoints = soap_new_resqml20__Point3dHdf5Array(gsoapProxy2_0_1->soap);
	xmlControlPoints->Coordinates = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlControlPoints->Coordinates->HdfProxy = proxy->newResqmlReference();
	xmlControlPoints->Coordinates->PathInHdfFile = getHdfGroup() + "/controlPoints";
	paramLine->ControlPoints = xmlControlPoints;

	// HDF control points
	hsize_t dim[2] = { controlPointCount, 3 };
	proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "controlPoints", controlPoints, dim, 2);

	getRepository()->addRelationship(this, localCrs);
}

void WellboreTrajectoryRepresentation::setGeometry(double const* controlPoints, double const* controlPointParameters, unsigned int controlPointCount, int lineKind,
	EML2_NS::AbstractHdfProxy * proxy, RESQML2_NS::AbstractLocal3dCrs* localCrs)
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
	xmlControlPointParameters->Values->PathInHdfFile = getHdfGroup() + "/controlPointParameters";
	paramLine->ControlPointParameters = xmlControlPointParameters;

	// HDF control point parameters
	const hsize_t dimParamDataSet = controlPointCount;
	proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "controlPointParameters", controlPointParameters, &dimParamDataSet, 1);
}

void WellboreTrajectoryRepresentation::setGeometry(double const* controlPoints,
	double const* tangentVectors, double const* controlPointParameters, unsigned int controlPointCount, int lineKind,
	EML2_NS::AbstractHdfProxy * proxy, RESQML2_NS::AbstractLocal3dCrs* localCrs)
{
	if (tangentVectors == nullptr) {
		throw invalid_argument("The tangent vectors parameter is missing.");
	}

	setGeometry(controlPoints, controlPointParameters, controlPointCount, lineKind, proxy, localCrs);

	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);

	resqml20__ParametricLineGeometry* paramLine = static_cast<resqml20__ParametricLineGeometry*>(rep->Geometry);
	// XML tangent vectors
	resqml20__Point3dHdf5Array* xmlTangentVectors = soap_new_resqml20__Point3dHdf5Array(gsoapProxy2_0_1->soap);
	xmlTangentVectors->Coordinates = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlTangentVectors->Coordinates->HdfProxy = proxy->newResqmlReference();
	xmlTangentVectors->Coordinates->PathInHdfFile = getHdfGroup() + "/tangentVectors";
	paramLine->TangentVectors = xmlTangentVectors;

	// HDF tangent vectors
	hsize_t dim[2] = { controlPointCount, 3 };
	proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "tangentVectors", tangentVectors, dim, 2);
}

void WellboreTrajectoryRepresentation::addParentTrajectory(double kickoffMd, double parentMd, RESQML2_NS::WellboreTrajectoryRepresentation* parentTrajRep)
{
	getRepository()->addRelationship(this, parentTrajRep);

	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	rep->ParentIntersection = soap_new_resqml20__WellboreTrajectoryParentIntersection(rep->soap);
	rep->ParentIntersection->KickoffMd = kickoffMd;
	rep->ParentIntersection->ParentMd = parentMd != parentMd ? kickoffMd : parentMd;
	rep->ParentIntersection->ParentTrajectory = parentTrajRep->newResqmlReference();
}

COMMON_NS::DataObjectReference WellboreTrajectoryRepresentation::getParentTrajectoryDor() const
{
	_resqml20__WellboreTrajectoryRepresentation const * rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	return rep->ParentIntersection == nullptr ? COMMON_NS::DataObjectReference() : COMMON_NS::DataObjectReference(rep->ParentIntersection->ParentTrajectory);
}

double WellboreTrajectoryRepresentation::getParentTrajectoryMd() const
{
	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->ParentIntersection != nullptr) {
		return rep->ParentIntersection->ParentMd;
	}

	throw logic_error("This wellbore trajectory has no parent trajecory.");
}

ULONG64 WellboreTrajectoryRepresentation::getXyzPointCountOfPatch(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The index patch is not in the allowed range of patch.");
	}

	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->Geometry == nullptr) {
		return 0;
	}
	return static_cast<resqml20__ParametricLineGeometry*>(rep->Geometry)->KnotCount;
}

void WellboreTrajectoryRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index patch is not in the allowed range of patch");
	}

	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->Geometry != nullptr) {
		resqml20__ParametricLineGeometry* paramLine = static_cast<resqml20__ParametricLineGeometry*>(rep->Geometry);
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__Point3dHdf5Array*>(paramLine->ControlPoints)->Coordinates;
		EML2_NS::AbstractHdfProxy * hdfProxy = getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
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
	_resqml20__WellboreTrajectoryRepresentation const * rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->Geometry == nullptr) {
		throw logic_error("This trajectory has not got any geometry.");
	}
	if (rep->Geometry->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineGeometry) {
		throw logic_error("This kind of parametric line is not supported yet for a wellbore trajectory.");
	}
	resqml20__ParametricLineGeometry const * paramLine = static_cast<resqml20__ParametricLineGeometry*>(rep->Geometry);
	if (paramLine->LineKindIndex < -1 || paramLine->LineKindIndex > 5) {
		throw out_of_range("The parametric line kind index must be in the range [-1, 5].");
	}

	return static_cast<int>(paramLine->LineKindIndex);
}

bool WellboreTrajectoryRepresentation::hasMdValues() const
{
	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->Geometry == nullptr) {
		return false;
	}
	if (rep->Geometry->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineGeometry) {
		throw logic_error("This kind of parametric line is not supported yet for a wellbore trajectory.");
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
		EML2_NS::AbstractHdfProxy * hdfProxy = getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
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
	EML2_NS::AbstractHdfProxy * hdfProxy = getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
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

COMMON_NS::DataObjectReference WellboreTrajectoryRepresentation::getMdDatumDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1)->MdDatum);
}

COMMON_NS::DataObjectReference WellboreTrajectoryRepresentation::getHdfProxyDor() const
{
	_resqml20__WellboreTrajectoryRepresentation* rep = static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
	if (rep->Geometry != nullptr) {
		resqml20__ParametricLineGeometry* paramLine = static_cast<resqml20__ParametricLineGeometry*>(rep->Geometry);
		return COMMON_NS::DataObjectReference(static_cast<resqml20__Point3dHdf5Array*>(paramLine->ControlPoints)->Coordinates->HdfProxy);
	}
	
	return COMMON_NS::DataObjectReference();
}

gsoap_resqml2_0_1::_resqml20__WellboreTrajectoryRepresentation* WellboreTrajectoryRepresentation::getSpecializedGsoapProxy() const
{
	cannotBePartial();

	return static_cast<_resqml20__WellboreTrajectoryRepresentation*>(gsoapProxy2_0_1);
}

COMMON_NS::DataObjectReference WellboreTrajectoryRepresentation::getLocalCrsDor(unsigned int patchIndex) const
{
	if (patchIndex > 0) {
		throw out_of_range("There is no more than one patch in a wellbore trajectory.");
	}

	_resqml20__WellboreTrajectoryRepresentation* rep = getSpecializedGsoapProxy();
	return rep->Geometry != nullptr
		? COMMON_NS::DataObjectReference(static_cast<resqml20__ParametricLineGeometry*>(rep->Geometry)->LocalCrs)
		: COMMON_NS::DataObjectReference();
}

COMMON_NS::DataObjectReference WellboreTrajectoryRepresentation::getDeviationSurveyDor() const
{
	return getSpecializedGsoapProxy()->DeviationSurvey;
}

bool WellboreTrajectoryRepresentation::hasGeometry() const
{
	return getSpecializedGsoapProxy()->Geometry != nullptr;
}

void WellboreTrajectoryRepresentation::setDeviationSurvey(RESQML2_NS::DeviationSurveyRepresentation* deviationSurvey)
{
	getRepository()->addRelationship(this, deviationSurvey);

	getSpecializedGsoapProxy()->DeviationSurvey = deviationSurvey->newResqmlReference();
}
