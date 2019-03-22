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
#include "resqml2_0_1/DeviationSurveyRepresentation.h"

#include <stdexcept>

#include "H5public.h"

#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2/MdDatum.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "common/HdfProxy.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;
using namespace COMMON_NS;

const char* DeviationSurveyRepresentation::XML_TAG = "DeviationSurveyRepresentation";

DeviationSurveyRepresentation::DeviationSurveyRepresentation(WellboreInterpretation* interp, const string & guid, const std::string & title, const bool & isFinal, RESQML2_NS::MdDatum * mdInfo) :
	AbstractRepresentation(interp, mdInfo->getLocalCrs())
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREDeviationSurveyRepresentation(interp->getGsoapContext(), 1);	
	_resqml2__DeviationSurveyRepresentation* rep = static_cast<_resqml2__DeviationSurveyRepresentation*>(gsoapProxy2_0_1);

	rep->IsFinal = isFinal;

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

void DeviationSurveyRepresentation::setGeometry(double * firstStationLocation, const ULONG64 & stationCount,
	const gsoap_resqml2_0_1::eml20__LengthUom & mdUom, double * mds,
	const gsoap_resqml2_0_1::eml20__PlaneAngleUom & angleUom, double * azimuths, double * inclinations,
	COMMON_NS::AbstractHdfProxy* proxy)
{
	if (firstStationLocation == nullptr)
		throw invalid_argument("The first station location is missing.");
	if (mds == nullptr)
		throw invalid_argument("The mds are missing.");
	if (azimuths == nullptr)
		throw invalid_argument("The azimuths are missing.");
	if (inclinations == nullptr)
		throw invalid_argument("The inclinations are missing.");
	if (proxy == nullptr)
		throw invalid_argument("The HDF proxy is missing.");

	setHdfProxy(proxy);

	_resqml2__DeviationSurveyRepresentation* rep = static_cast<_resqml2__DeviationSurveyRepresentation*>(gsoapProxy2_0_1);

	rep->FirstStationLocation = soap_new_resqml2__Point3d(gsoapProxy2_0_1->soap, 1);
	rep->FirstStationLocation->Coordinate1 = firstStationLocation[0];
	rep->FirstStationLocation->Coordinate2 = firstStationLocation[1];
	rep->FirstStationLocation->Coordinate3 = firstStationLocation[2];

	rep->StationCount = stationCount;

	rep->MdUom = mdUom;
	resqml2__DoubleHdf5Array* xmlMds = soap_new_resqml2__DoubleHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlMds->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlMds->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlMds->Values->PathInHdfFile = "/RESQML/" + rep->uuid + "/mds";
	rep->Mds = xmlMds;
	// HDF mds
	hsize_t dim[] = { stationCount };
	hdfProxy->writeArrayNdOfDoubleValues(rep->uuid, "mds", mds, dim, 1);

	rep->AngleUom = angleUom;
	// XML azimuths
	resqml2__DoubleHdf5Array* xmlAzims = soap_new_resqml2__DoubleHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlAzims->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlAzims->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlAzims->Values->PathInHdfFile = "/RESQML/" + rep->uuid + "/azimuths";
	rep->Azimuths = xmlAzims;
	// HDF azimuths
	hdfProxy->writeArrayNdOfDoubleValues(rep->uuid, "azimuths", azimuths, dim, 1);
	// XML inclinations
	resqml2__DoubleHdf5Array* xmlIncls = soap_new_resqml2__DoubleHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlIncls->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlIncls->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlIncls->Values->PathInHdfFile = "/RESQML/" + rep->uuid + "/inclinations";
	rep->Inclinations = xmlIncls;
	// HDF inclinations
	hdfProxy->writeArrayNdOfDoubleValues(rep->uuid, "inclinations", inclinations, dim, 1);
}

vector<Relationship> DeviationSurveyRepresentation::getAllSourceRelationships() const
{	
	vector<Relationship> result = AbstractRepresentation::getAllSourceRelationships();

	// XML backward relationship
	for (size_t i = 0; i < wbTrajectoryRepSet.size(); ++i) {
		Relationship relFrame(wbTrajectoryRepSet[i]->getPartNameInEpcDocument(), "", wbTrajectoryRepSet[i]->getUuid());
		relFrame.setSourceObjectType();
		result.push_back(relFrame);
	}

	return result;
}

vector<Relationship> DeviationSurveyRepresentation::getAllTargetRelationships() const
{
	vector<Relationship> result = AbstractRepresentation::getAllTargetRelationships();

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

	return result;
}

void DeviationSurveyRepresentation::resolveTargetRelationships(COMMON_NS::EpcDocument* epcDoc)
{
	AbstractRepresentation::resolveTargetRelationships(epcDoc);

	RESQML2_NS::MdDatum* mdDatum = epcDoc->getDataObjectByUuid<RESQML2_NS::MdDatum>(getMdDatumUuid());
	if (mdDatum != nullptr) {
		updateXml = false;
		setMdDatum(mdDatum);
		updateXml = true;
	}
}

ULONG64 DeviationSurveyRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index patch is not in the allowed range of patch.");
	}

	_resqml2__DeviationSurveyRepresentation* rep = static_cast<_resqml2__DeviationSurveyRepresentation*>(gsoapProxy2_0_1);
	return rep->StationCount;
}

void DeviationSurveyRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double *) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index patch is not in the allowed range of patch");
	}

	throw logic_error("Fesapi does not know yet to transform Md/Dip/Azim values into XYZ values.");
}

void DeviationSurveyRepresentation::getMdValues(double * values)
{
	if (hdfProxy == nullptr) {
		throw invalid_argument("The HDF proxy is missing.");
	}
		
	_resqml2__DeviationSurveyRepresentation* rep = static_cast<_resqml2__DeviationSurveyRepresentation*>(gsoapProxy2_0_1);
	if (rep->Mds->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
		resqml2__DoubleHdf5Array* xmlMds = static_cast<resqml2__DoubleHdf5Array*>(rep->Mds);
		hdfProxy->readArrayNdOfDoubleValues(xmlMds->Values->PathInHdfFile, values);
	}
	else {
		throw invalid_argument("Mds can only be defined using DoubleHdf5Array for now in fesapi.");
	}
}

void DeviationSurveyRepresentation::getInclinations(double* values)
{
	if (hdfProxy == nullptr) {
		throw invalid_argument("The HDF proxy is missing.");
	}

	_resqml2__DeviationSurveyRepresentation* rep = static_cast<_resqml2__DeviationSurveyRepresentation*>(gsoapProxy2_0_1);
	if (rep->Inclinations->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
		resqml2__DoubleHdf5Array* xml = static_cast<resqml2__DoubleHdf5Array*>(rep->Inclinations);
		hdfProxy->readArrayNdOfDoubleValues(xml->Values->PathInHdfFile, values);
	}
	else {
		throw invalid_argument("Inclinations can only be defined using DoubleHdf5Array for now in fesapi.");
	}
}

void DeviationSurveyRepresentation::getAzimuths(double* values)
{
	if (hdfProxy == nullptr) {
		throw invalid_argument("The HDF proxy is missing.");
	}

	_resqml2__DeviationSurveyRepresentation* rep = static_cast<_resqml2__DeviationSurveyRepresentation*>(gsoapProxy2_0_1);
	if (rep->Azimuths->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
		resqml2__DoubleHdf5Array* xml = static_cast<resqml2__DoubleHdf5Array*>(rep->Azimuths);
		hdfProxy->readArrayNdOfDoubleValues(xml->Values->PathInHdfFile, values);
	}
	else {
		throw invalid_argument("Azimuths can only be defined using DoubleHdf5Array for now in fesapi.");
	}
}

void DeviationSurveyRepresentation::setMdDatum(RESQML2_NS::MdDatum* mdDatum)
{
	if (mdDatum == nullptr) {
		throw invalid_argument("The md Datum is missing.");
	}

	mdDatum->addDeviationSurveyRepresentation(this);

	if (updateXml) {
		static_cast<_resqml2__DeviationSurveyRepresentation*>(gsoapProxy2_0_1)->MdDatum = mdDatum->newResqmlReference();
	}
}

RESQML2_NS::MdDatum * DeviationSurveyRepresentation::getMdDatum() const
{
	return static_cast<RESQML2_NS::MdDatum*>(getEpcDocument()->getDataObjectByUuid(getMdDatumUuid()));
}

std::string DeviationSurveyRepresentation::getMdDatumUuid() const
{
	return static_cast<_resqml2__DeviationSurveyRepresentation*>(gsoapProxy2_0_1)->MdDatum->UUID;
}

bool DeviationSurveyRepresentation::isFinal() const
{
	return static_cast<_resqml2__DeviationSurveyRepresentation*>(gsoapProxy2_0_1)->IsFinal;
}

gsoap_resqml2_0_1::eml20__LengthUom DeviationSurveyRepresentation::getMdUom() const
{
	return static_cast<_resqml2__DeviationSurveyRepresentation*>(gsoapProxy2_0_1)->MdUom;
}

gsoap_resqml2_0_1::eml20__PlaneAngleUom DeviationSurveyRepresentation::getAngleUom() const
{
	return static_cast<_resqml2__DeviationSurveyRepresentation*>(gsoapProxy2_0_1)->AngleUom;
}

gsoap_resqml2_0_1::eml20__DataObjectReference* DeviationSurveyRepresentation::getHdfProxyDor() const
{
	_resqml2__DeviationSurveyRepresentation* rep = static_cast<_resqml2__DeviationSurveyRepresentation*>(gsoapProxy2_0_1);
	if (rep->Mds != nullptr) {
		if (rep->Mds->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
			return static_cast<resqml2__DoubleHdf5Array*>(rep->Mds)->Values->HdfProxy;
		}
	}
	else if (rep->Inclinations != nullptr) {
		if (rep->Inclinations->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
			return static_cast<resqml2__DoubleHdf5Array*>(rep->Inclinations)->Values->HdfProxy;
		}
	}
	else if (rep->Azimuths != nullptr) {
		if (rep->Azimuths->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
			return static_cast<resqml2__DoubleHdf5Array*>(rep->Azimuths)->Values->HdfProxy;
		}
	}

	return nullptr;
}

void DeviationSurveyRepresentation::addTrajectory(WellboreTrajectoryRepresentation* trajectory)
{
	wbTrajectoryRepSet.push_back(trajectory);
}

vector<WellboreFrameRepresentation*> DeviationSurveyRepresentation::getWellboreFrameRepresentationSet() const
{
	vector<WellboreFrameRepresentation*> result;

	vector<WellboreTrajectoryRepresentation*> trajectories = getWellboreTrajectoryRepresentationSet();
	for (size_t index = 0; index < trajectories.size(); ++index) {
		if (trajectories[index]->getMdDatumUuid() == getMdDatumUuid() && trajectories[index]->getMdUom() == getMdUom()) {
			vector<WellboreFrameRepresentation*> tmp = trajectories[index]->getWellboreFrameRepresentationSet();
			result.insert(result.end(), tmp.begin(), tmp.end());
		}
	}

	return result;
}

unsigned int DeviationSurveyRepresentation::getWellboreFrameRepresentationCount() const
{
	vector<WellboreTrajectoryRepresentation*> trajectories = getWellboreTrajectoryRepresentationSet();
	unsigned int result = 0;
	for (size_t index = 0; index < trajectories.size(); ++index) {
		if (trajectories[index]->getMdDatumUuid() == getMdDatumUuid() && trajectories[index]->getMdUom() == getMdUom()) {
			result += trajectories[index]->getWellboreFrameRepresentationCount();
		}
	}

	return result;
}

WellboreFrameRepresentation* DeviationSurveyRepresentation::getWellboreFrameRepresentation(unsigned int index) const
{
	vector<WellboreTrajectoryRepresentation*> trajectories = getWellboreTrajectoryRepresentationSet();
	for (size_t trajIndex = 0; trajIndex < trajectories.size(); ++trajIndex) {
		WellboreTrajectoryRepresentation* traj = trajectories[trajIndex];
		if (traj->getMdDatumUuid() == getMdDatumUuid() && traj->getMdUom() == getMdUom()) {
			unsigned int count = traj->getWellboreFrameRepresentationCount();
			if (index < count) {
				return traj->getWellboreFrameRepresentation(index);
			}
			else {
				index -= count;
			}
		}
	}

	throw invalid_argument("The index is out of range");
}

const std::vector<class WellboreTrajectoryRepresentation*>& DeviationSurveyRepresentation::getWellboreTrajectoryRepresentationSet() const
{
	return wbTrajectoryRepSet;
}

unsigned int DeviationSurveyRepresentation::getWellboreTrajectoryRepresentationCount() const
{
	return wbTrajectoryRepSet.size();
}

WellboreTrajectoryRepresentation* DeviationSurveyRepresentation::getWellboreTrajectoryRepresentation(const unsigned int & index) const
{
	if (index >= getWellboreTrajectoryRepresentationCount())
	{
		throw invalid_argument("The index is out of range");
	}

	return wbTrajectoryRepSet[index];
}
