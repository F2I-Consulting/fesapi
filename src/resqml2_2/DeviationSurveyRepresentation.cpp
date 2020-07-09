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
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* DeviationSurveyRepresentation::XML_NS = "resqml22";

DeviationSurveyRepresentation::DeviationSurveyRepresentation(RESQML2_NS::WellboreInterpretation* interp, const string& guid, const std::string& title, bool isFinal, RESQML2_NS::MdDatum* mdInfo)
{
	if (interp == nullptr) {
		throw invalid_argument("The interpretation cannot be nullptr.");
	}

	if (mdInfo == nullptr) {
		throw invalid_argument("The MD information cannot be nullptr.");
	}

	gsoapProxy2_3 = soap_new_resqml22__DeviationSurveyRepresentation(interp->getGsoapContext());	
	_resqml22__DeviationSurveyRepresentation* rep = static_cast<_resqml22__DeviationSurveyRepresentation*>(gsoapProxy2_3);

	rep->IsFinal = isFinal;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	if (dynamic_cast<RESQML2_NS::AbstractLocal3dCrs*>(mdInfo->getLocalCrs()) != nullptr) {
		rep->MdUom = gsoap_resqml2_0_1::soap_eml20__LengthUom2s(gsoapProxy2_3->soap, static_cast<RESQML2_NS::AbstractLocal3dCrs*>(mdInfo->getLocalCrs())->getVerticalCrsUnit());
	}

	setMdDatum(mdInfo);

	setInterpretation(interp);
}

void DeviationSurveyRepresentation::setGeometry(double const* firstStationLocation, ULONG64 stationCount,
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

	_resqml22__DeviationSurveyRepresentation* rep = static_cast<_resqml22__DeviationSurveyRepresentation*>(gsoapProxy2_3);

	rep->FirstStationLocation = soap_new_resqml22__SinglePointGeometry(gsoapProxy2_3->soap);
	rep->FirstStationLocation->LocalCrs = getMdDatum()->getLocalCrs()->newEml23Reference();
	rep->FirstStationLocation->Point3d = soap_new_resqml22__Point3d(gsoapProxy2_3->soap);
	rep->FirstStationLocation->Point3d->Coordinate1 = firstStationLocation[0];
	rep->FirstStationLocation->Point3d->Coordinate2 = firstStationLocation[1];
	rep->FirstStationLocation->Point3d->Coordinate3 = firstStationLocation[2];

	rep->StationCount = stationCount;

	rep->MdUom = gsoap_resqml2_0_1::soap_eml20__LengthUom2s(gsoapProxy2_3->soap, mdUom);
	eml23__FloatingPointExternalArray* xmlMds = soap_new_eml23__FloatingPointExternalArray(gsoapProxy2_3->soap);
	xmlMds->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	auto dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = getHdfGroup() + "/mds";
	xmlMds->Values->ExternalFileProxy.push_back(dsPart);
	rep->Mds = xmlMds;
	// HDF mds
	const hsize_t dim = stationCount;
	proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "mds", mds, &dim, 1);

	rep->AngleUom = gsoap_resqml2_0_1::soap_eml20__PlaneAngleUom2s(gsoapProxy2_3->soap, angleUom);
	// XML azimuths
	eml23__FloatingPointExternalArray* xmlAzims = soap_new_eml23__FloatingPointExternalArray(gsoapProxy2_3->soap);
	xmlAzims->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = getHdfGroup() + "/azimuths";
	xmlAzims->Values->ExternalFileProxy.push_back(dsPart);
	rep->Azimuths = xmlAzims;
	// HDF azimuths
	proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "azimuths", azimuths, &dim, 1);
	// XML inclinations
	eml23__FloatingPointExternalArray* xmlIncls = soap_new_eml23__FloatingPointExternalArray(gsoapProxy2_3->soap);
	xmlIncls->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = getHdfGroup() + "/inclinations";
	xmlIncls->Values->ExternalFileProxy.push_back(dsPart);
	rep->Inclinations = xmlIncls;
	// HDF inclinations
	proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "inclinations", inclinations, &dim, 1);
}

ULONG64 DeviationSurveyRepresentation::getXyzPointCountOfPatch(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index patch is not in the allowed range of patch.");
	}

	_resqml22__DeviationSurveyRepresentation* rep = static_cast<_resqml22__DeviationSurveyRepresentation*>(gsoapProxy2_3);
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
	_resqml22__DeviationSurveyRepresentation* rep = static_cast<_resqml22__DeviationSurveyRepresentation*>(gsoapProxy2_3);
	if (dynamic_cast<eml23__FloatingPointExternalArray*>(rep->Mds) != nullptr) {
		eml23__ExternalDatasetPart const * dsPart = static_cast<eml23__FloatingPointExternalArray*>(rep->Mds)->Values->ExternalFileProxy[0];
		getHdfProxyFromDataset(dsPart)->readArrayNdOfDoubleValues(dsPart->PathInExternalFile, values);
	}
	else {
		throw logic_error("Mds can only be defined using FloatingPointExternalArray for now in fesapi.");
	}
}

void DeviationSurveyRepresentation::getInclinations(double* values) const
{
	_resqml22__DeviationSurveyRepresentation* rep = static_cast<_resqml22__DeviationSurveyRepresentation*>(gsoapProxy2_3);
	if (dynamic_cast<eml23__FloatingPointExternalArray*>(rep->Inclinations) != nullptr) {
		eml23__ExternalDatasetPart const * dsPart = static_cast<eml23__FloatingPointExternalArray*>(rep->Inclinations)->Values->ExternalFileProxy[0];
		getHdfProxyFromDataset(dsPart)->readArrayNdOfDoubleValues(dsPart->PathInExternalFile, values);
	}
	else {
		throw invalid_argument("Inclinations can only be defined using FloatingPointExternalArray for now in fesapi.");
	}
}

void DeviationSurveyRepresentation::getAzimuths(double* values) const
{
	_resqml22__DeviationSurveyRepresentation* rep = static_cast<_resqml22__DeviationSurveyRepresentation*>(gsoapProxy2_3);
	if (dynamic_cast<eml23__FloatingPointExternalArray*>(rep->Azimuths) != nullptr) {
		eml23__ExternalDatasetPart const * dsPart = static_cast<eml23__FloatingPointExternalArray*>(rep->Azimuths)->Values->ExternalFileProxy[0];
		getHdfProxyFromDataset(dsPart)->readArrayNdOfDoubleValues(dsPart->PathInExternalFile, values);
	}
	else {
		throw invalid_argument("Azimuths can only be defined using FloatingPointExternalArray for now in fesapi.");
	}
}

void DeviationSurveyRepresentation::setMdDatum(RESQML2_NS::MdDatum * mdDatum)
{
	if (mdDatum == nullptr) {
		throw invalid_argument("The md Datum is missing.");
	}
	if (getRepository() == nullptr) {
		mdDatum->getRepository()->addOrReplaceDataObject(this);
	}

	getRepository()->addRelationship(this, mdDatum);

	static_cast<_resqml22__DeviationSurveyRepresentation*>(gsoapProxy2_3)->MdDatum = mdDatum->newEml23Reference();
}

COMMON_NS::DataObjectReference DeviationSurveyRepresentation::getMdDatumDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<_resqml22__DeviationSurveyRepresentation*>(gsoapProxy2_3)->MdDatum);
}

bool DeviationSurveyRepresentation::isFinal() const
{
	return static_cast<_resqml22__DeviationSurveyRepresentation*>(gsoapProxy2_3)->IsFinal;
}

gsoap_resqml2_0_1::eml20__LengthUom DeviationSurveyRepresentation::getMdUom() const
{
	gsoap_resqml2_0_1::eml20__LengthUom result;
	gsoap_resqml2_0_1::soap_s2eml20__LengthUom(getGsoapContext(), static_cast<_resqml22__DeviationSurveyRepresentation*>(gsoapProxy2_3)->MdUom.c_str(), &result);
	return result;
}

gsoap_resqml2_0_1::eml20__PlaneAngleUom DeviationSurveyRepresentation::getAngleUom() const
{
	gsoap_resqml2_0_1::eml20__PlaneAngleUom result;
	gsoap_resqml2_0_1::soap_s2eml20__PlaneAngleUom(getGsoapContext(), static_cast<_resqml22__DeviationSurveyRepresentation*>(gsoapProxy2_3)->AngleUom.c_str(), &result);
	return result;
}

COMMON_NS::DataObjectReference DeviationSurveyRepresentation::getHdfProxyDor() const
{
	_resqml22__DeviationSurveyRepresentation* rep = static_cast<_resqml22__DeviationSurveyRepresentation*>(gsoapProxy2_3);
	if (rep->Mds != nullptr) {
		if (dynamic_cast<eml23__FloatingPointExternalArray*>(rep->Mds) != nullptr) {
			return COMMON_NS::DataObjectReference(static_cast<eml23__FloatingPointExternalArray*>(rep->Mds)->Values->ExternalFileProxy[0]->EpcExternalPartReference);
		}
	}
	else if (rep->Inclinations != nullptr) {
		if (dynamic_cast<eml23__FloatingPointExternalArray*>(rep->Inclinations) != nullptr) {
			return COMMON_NS::DataObjectReference(static_cast<eml23__FloatingPointExternalArray*>(rep->Inclinations)->Values->ExternalFileProxy[0]->EpcExternalPartReference);
		}
	}
	else if (rep->Azimuths != nullptr) {
		if (dynamic_cast<eml23__FloatingPointExternalArray*>(rep->Azimuths) != nullptr) {
			return COMMON_NS::DataObjectReference(static_cast<eml23__FloatingPointExternalArray*>(rep->Azimuths)->Values->ExternalFileProxy[0]->EpcExternalPartReference);
		}
	}

	return COMMON_NS::DataObjectReference();
}
