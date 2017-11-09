/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use,
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
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
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;
using namespace common;

const char* DeviationSurveyRepresentation::XML_TAG = "DeviationSurveyRepresentation";

DeviationSurveyRepresentation::DeviationSurveyRepresentation(WellboreInterpretation* interp, const string & guid, const std::string & title, const bool & isFinal, resqml2::MdDatum * mdInfo) :
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
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	if (dynamic_cast<resqml2::AbstractLocal3dCrs*>(mdInfo->getLocalCrs()) != nullptr) {
		rep->MdUom = static_cast<resqml2::AbstractLocal3dCrs*>(mdInfo->getLocalCrs())->getVerticalCrsUnit();
	}
}

void DeviationSurveyRepresentation::setGeometry(double * firstStationLocation, const ULONG64 & stationCount,
	const gsoap_resqml2_0_1::eml20__LengthUom & mdUom, double * mds,
	const gsoap_resqml2_0_1::eml20__PlaneAngleUom & angleUom, double * azimuths, double * inclinations,
	common::AbstractHdfProxy* proxy)
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

vector<Relationship> DeviationSurveyRepresentation::getAllEpcRelationships() const
{	
	vector<Relationship> result = AbstractRepresentation::getAllEpcRelationships();

	// XML forward relationship
	resqml2::MdDatum* mdDatum = getMdDatum();
	if (mdDatum != nullptr) {
		Relationship relMdInfo(mdDatum->getPartNameInEpcDocument(), "", getMdDatumUuid());
		relMdInfo.setDestinationObjectType();
		result.push_back(relMdInfo);
	}
	else {
		throw domain_error("The MD information associated to the WellboreFeature trajectory cannot be nullptr.");
	}

	// XML backward relationship
	for (size_t i = 0; i < wbTrajectoryRepSet.size(); ++i) {
		Relationship relFrame(wbTrajectoryRepSet[i]->getPartNameInEpcDocument(), "", wbTrajectoryRepSet[i]->getUuid());
		relFrame.setSourceObjectType();
		result.push_back(relFrame);
	}

	return result;
}

void DeviationSurveyRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractRepresentation::importRelationshipSetFromEpc(epcDoc);

	resqml2::MdDatum* mdDatum = epcDoc->getResqmlAbstractObjectByUuid<resqml2::MdDatum>(getMdDatumUuid());
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

void DeviationSurveyRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
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

void DeviationSurveyRepresentation::setMdDatum(resqml2::MdDatum* mdDatum)
{
	if (mdDatum == nullptr) {
		throw invalid_argument("The md Datum is missing.");
	}

	mdDatum->addDeviationSurveyRepresentation(this);

	if (updateXml) {
		static_cast<_resqml2__DeviationSurveyRepresentation*>(gsoapProxy2_0_1)->MdDatum = mdDatum->newResqmlReference();
	}
}

resqml2::MdDatum * DeviationSurveyRepresentation::getMdDatum() const
{
	return static_cast<resqml2::MdDatum*>(getEpcDocument()->getResqmlAbstractObjectByUuid(getMdDatumUuid()));
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

std::string DeviationSurveyRepresentation::getHdfProxyUuid() const
{
	_resqml2__DeviationSurveyRepresentation* rep = static_cast<_resqml2__DeviationSurveyRepresentation*>(gsoapProxy2_0_1);
	if (rep->Mds != nullptr) {
		if (rep->Mds->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
			return static_cast<resqml2__DoubleHdf5Array*>(rep->Mds)->Values->HdfProxy->UUID;
		}
	}
	else if (rep->Inclinations != nullptr) {
		if (rep->Inclinations->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
			return static_cast<resqml2__DoubleHdf5Array*>(rep->Inclinations)->Values->HdfProxy->UUID;
		}
	}
	else if (rep->Azimuths != nullptr) {
		if (rep->Azimuths->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
			return static_cast<resqml2__DoubleHdf5Array*>(rep->Azimuths)->Values->HdfProxy->UUID;
		}
	}

	return "";
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
	unsigned int result = 0;
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
