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
#include "DeviationSurveyRepresentation.h"

#include <stdexcept>

#include "H5public.h"

#include "../resqml2/WellboreInterpretation.h"
#include "../resqml2/MdDatum.h"
#include "../resqml2/AbstractLocal3dCrs.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* DeviationSurveyRepresentation::XML_NS = "resqml20";

DeviationSurveyRepresentation::DeviationSurveyRepresentation(RESQML2_NS::WellboreInterpretation* interp, const string& guid, const std::string& title, bool isFinal, RESQML2_NS::MdDatum* mdInfo)
{
	if (interp == nullptr) {
		throw invalid_argument("The interpretation cannot be nullptr.");
	}

	if (mdInfo == nullptr) {
		throw invalid_argument("The MD information cannot be nullptr.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREDeviationSurveyRepresentation(interp->getGsoapContext());	
	_resqml20__DeviationSurveyRepresentation* rep = static_cast<_resqml20__DeviationSurveyRepresentation*>(gsoapProxy2_0_1);

	rep->IsFinal = isFinal;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	if (dynamic_cast<RESQML2_NS::AbstractLocal3dCrs*>(mdInfo->getLocalCrs()) != nullptr) {
		rep->MdUom = static_cast<RESQML2_NS::AbstractLocal3dCrs*>(mdInfo->getLocalCrs())->getVerticalCrsUnit();
	}

	interp->getRepository()->addDataObject(this);
	setMdDatum(mdInfo);
	setInterpretation(interp);
}

void DeviationSurveyRepresentation::setGeometry(double const* firstStationLocation, uint64_t stationCount,
	gsoap_resqml2_0_1::eml20__LengthUom mdUom, double const* mds,
	gsoap_resqml2_0_1::eml20__PlaneAngleUom angleUom, double const* azimuths, double const* inclinations,
	EML2_NS::AbstractHdfProxy* proxy)
{
	if (firstStationLocation == nullptr)
		throw invalid_argument("The first station location is missing.");
	if (mds == nullptr)
		throw invalid_argument("The mds are missing.");
	if (azimuths == nullptr)
		throw invalid_argument("The azimuths are missing.");
	if (inclinations == nullptr)
		throw invalid_argument("The inclinations are missing.");
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

	_resqml20__DeviationSurveyRepresentation* rep = static_cast<_resqml20__DeviationSurveyRepresentation*>(gsoapProxy2_0_1);

	rep->FirstStationLocation = soap_new_resqml20__Point3d(gsoapProxy2_0_1->soap);
	rep->FirstStationLocation->Coordinate1 = firstStationLocation[0];
	rep->FirstStationLocation->Coordinate2 = firstStationLocation[1];
	rep->FirstStationLocation->Coordinate3 = firstStationLocation[2];

	rep->StationCount = stationCount;

	rep->MdUom = mdUom;
	resqml20__DoubleHdf5Array* xmlMds = soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
	xmlMds->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlMds->Values->HdfProxy = proxy->newResqmlReference();
	xmlMds->Values->PathInHdfFile = getHdfGroup() + "/mds";
	rep->Mds = xmlMds;
	// HDF mds
	proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "mds", mds, &stationCount, 1);

	rep->AngleUom = angleUom;
	// XML azimuths
	resqml20__DoubleHdf5Array* xmlAzims = soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
	xmlAzims->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlAzims->Values->HdfProxy = proxy->newResqmlReference();
	xmlAzims->Values->PathInHdfFile = getHdfGroup() + "/azimuths";
	rep->Azimuths = xmlAzims;
	// HDF azimuths
	proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "azimuths", azimuths, &stationCount, 1);
	// XML inclinations
	resqml20__DoubleHdf5Array* xmlIncls = soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
	xmlIncls->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlIncls->Values->HdfProxy = proxy->newResqmlReference();
	xmlIncls->Values->PathInHdfFile = getHdfGroup() + "/inclinations";
	rep->Inclinations = xmlIncls;
	// HDF inclinations
	proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "inclinations", inclinations, &stationCount, 1);
}

uint64_t DeviationSurveyRepresentation::getXyzPointCountOfPatch(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index patch is not in the allowed range of patch.");
	}

	_resqml20__DeviationSurveyRepresentation* rep = static_cast<_resqml20__DeviationSurveyRepresentation*>(gsoapProxy2_0_1);
	return rep->StationCount;
}

void DeviationSurveyRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double *) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index patch is not in the allowed range of patch");
	}

	throw logic_error("Fesapi does not know yet to transform Md/Dip/Azim values into XYZ values.");
}

void DeviationSurveyRepresentation::getMdValues(double * values) const
{		
	_resqml20__DeviationSurveyRepresentation* rep = static_cast<_resqml20__DeviationSurveyRepresentation*>(gsoapProxy2_0_1);
	if (rep->Mds->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__DoubleHdf5Array*>(rep->Mds)->Values;
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, values);
	}
	else {
		throw logic_error("Mds can only be defined using DoubleHdf5Array for now in fesapi.");
	}
}

void DeviationSurveyRepresentation::getInclinations(double* values) const
{
	_resqml20__DeviationSurveyRepresentation* rep = static_cast<_resqml20__DeviationSurveyRepresentation*>(gsoapProxy2_0_1);
	if (rep->Inclinations->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__DoubleHdf5Array*>(rep->Inclinations)->Values;
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, values);
	}
	else {
		throw invalid_argument("Inclinations can only be defined using DoubleHdf5Array for now in fesapi.");
	}
}

void DeviationSurveyRepresentation::getAzimuths(double* values) const
{
	_resqml20__DeviationSurveyRepresentation* rep = static_cast<_resqml20__DeviationSurveyRepresentation*>(gsoapProxy2_0_1);
	if (rep->Azimuths->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__DoubleHdf5Array*>(rep->Azimuths)->Values;
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, values);
	}
	else {
		throw invalid_argument("Azimuths can only be defined using DoubleHdf5Array for now in fesapi.");
	}
}

void DeviationSurveyRepresentation::setMdDatum(RESQML2_NS::MdDatum * mdDatum)
{
	if (mdDatum == nullptr) {
		throw invalid_argument("The md Datum is missing.");
	}

	static_cast<_resqml20__DeviationSurveyRepresentation*>(gsoapProxy2_0_1)->MdDatum = mdDatum->newResqmlReference();

	getRepository()->addRelationship(this, mdDatum);
}

COMMON_NS::DataObjectReference DeviationSurveyRepresentation::getMdDatumDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<_resqml20__DeviationSurveyRepresentation*>(gsoapProxy2_0_1)->MdDatum);
}

bool DeviationSurveyRepresentation::isFinal() const
{
	return static_cast<_resqml20__DeviationSurveyRepresentation*>(gsoapProxy2_0_1)->IsFinal;
}

gsoap_resqml2_0_1::eml20__LengthUom DeviationSurveyRepresentation::getMdUom() const
{
	return static_cast<_resqml20__DeviationSurveyRepresentation*>(gsoapProxy2_0_1)->MdUom;
}

gsoap_resqml2_0_1::eml20__PlaneAngleUom DeviationSurveyRepresentation::getAngleUom() const
{
	return static_cast<_resqml20__DeviationSurveyRepresentation*>(gsoapProxy2_0_1)->AngleUom;
}

COMMON_NS::DataObjectReference DeviationSurveyRepresentation::getHdfProxyDor() const
{
	_resqml20__DeviationSurveyRepresentation* rep = static_cast<_resqml20__DeviationSurveyRepresentation*>(gsoapProxy2_0_1);
	if (rep->Mds != nullptr) {
		if (rep->Mds->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
			return COMMON_NS::DataObjectReference(static_cast<resqml20__DoubleHdf5Array*>(rep->Mds)->Values->HdfProxy);
		}
	}
	else if (rep->Inclinations != nullptr) {
		if (rep->Inclinations->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
			return COMMON_NS::DataObjectReference(static_cast<resqml20__DoubleHdf5Array*>(rep->Inclinations)->Values->HdfProxy);
		}
	}
	else if (rep->Azimuths != nullptr) {
		if (rep->Azimuths->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
			return COMMON_NS::DataObjectReference(static_cast<resqml20__DoubleHdf5Array*>(rep->Azimuths)->Values->HdfProxy);
		}
	}

	return COMMON_NS::DataObjectReference();
}
