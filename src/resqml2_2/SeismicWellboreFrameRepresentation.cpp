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
#include "SeismicWellboreFrameRepresentation.h"

#include <hdf5.h>

#include "../common/AbstractHdfProxy.h"
#include "../resqml2_0_1/LocalTime3dCrs.h"
#include "../resqml2/WellboreInterpretation.h"
#include "../resqml2/WellboreTrajectoryRepresentation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_2;

const char* SeismicWellboreFrameRepresentation::XML_TAG = "SeismicWellboreFrameRepresentation";

SeismicWellboreFrameRepresentation::SeismicWellboreFrameRepresentation(
	RESQML2_NS::WellboreInterpretation* interp,
	const std::string& guid, const std::string& title,
	RESQML2_NS::WellboreTrajectoryRepresentation* traj,
	double seismicReferenceDatum,
	double weatheringVelocity,
	RESQML2_0_1_NS::LocalTime3dCrs* crs)
{
	if (interp == nullptr) {
		throw invalid_argument("The wellbore interpretation cannot be null.");
	}
	if (traj == nullptr) {
		throw invalid_argument("The trajectory cannot be null.");
	}
	if (crs == nullptr) {
		throw invalid_argument("The local time crs cannot be null.");
	}

	gsoapProxy2_2 = soap_new_resqml22__SeismicWellboreFrameRepresentation(interp->getGsoapContext());
	_resqml22__SeismicWellboreFrameRepresentation* frame = static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_2);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretation(interp);

	frame->Trajectory = traj->newEml22Reference();
	getRepository()->addRelationship(this, traj);

	frame->SeismicReferenceDatum = seismicReferenceDatum;

	frame->WeatheringVelocity = weatheringVelocity;

	frame->LocalTime3dCrs = crs->newEml22Reference();
	getRepository()->addRelationship(this, crs);
}

void SeismicWellboreFrameRepresentation::setTimeValues(double const * timeValues, unsigned int timeValueCount, COMMON_NS::AbstractHdfProxy* proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
	}
	getRepository()->addRelationship(this, proxy);

	_resqml22__SeismicWellboreFrameRepresentation* frame = static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_2);

	// XML
	eml22__DoubleExternalArray* xmlTimeValues = soap_new_eml22__DoubleExternalArray(gsoapProxy2_2->soap);
	xmlTimeValues->Values = soap_new_eml22__ExternalDataset(gsoapProxy2_2->soap);
	xmlTimeValues->Values->ExternalFileProxy.push_back(soap_new_eml22__ExternalDatasetPart(gsoapProxy2_2->soap, 1));
	xmlTimeValues->Values->ExternalFileProxy[0]->Count = timeValueCount;
	xmlTimeValues->Values->ExternalFileProxy[0]->StartIndex = 0;
	xmlTimeValues->Values->ExternalFileProxy[0]->PathInExternalFile = getHdfGroup() + "/timeValues";
	xmlTimeValues->Values->ExternalFileProxy[0]->EpcExternalPartReference = proxy->newEml22Reference();

	frame->NodeTimeValues = xmlTimeValues;

	frame->NodeCount = timeValueCount;

	// HDF
	hsize_t dim = timeValueCount;
	proxy->writeArrayNd(getHdfGroup(),
		"timeValues",
		H5T_NATIVE_DOUBLE,
		timeValues,
		&dim, 1);
}

void SeismicWellboreFrameRepresentation::setTimeValues(double firstTimeValue, double incrementTimeValue, unsigned int timeValueCount)
{
	_resqml22__SeismicWellboreFrameRepresentation* frame = static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_2);

	// XML
	eml22__FloatingPointLatticeArray* xmlTimeValues = soap_new_eml22__FloatingPointLatticeArray(gsoapProxy2_2->soap);
	xmlTimeValues->StartValue = firstTimeValue;
	xmlTimeValues->Offset.push_back(soap_new_eml22__FloatingPointConstantArray(gsoapProxy2_2->soap, 1));
	xmlTimeValues->Offset[0]->Count = timeValueCount - 1;
	xmlTimeValues->Offset[0]->Value = incrementTimeValue;

	frame->NodeTimeValues = xmlTimeValues;

	frame->NodeCount = timeValueCount;
}

bool SeismicWellboreFrameRepresentation::areTimeValuesRegularlySpaced() const
{
	return static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_2)->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__FloatingPointLatticeArray;
}

double SeismicWellboreFrameRepresentation::getTimeConstantIncrementValue() const
{
	if (!areTimeValuesRegularlySpaced()) {
		throw invalid_argument("The time values are not regularly spaced.");
	}

	return static_cast<eml22__FloatingPointLatticeArray*>(static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_2)->NodeTimeValues)->Offset[0]->Value;
}

double SeismicWellboreFrameRepresentation::getTimeFirstValue() const
{
	_resqml22__SeismicWellboreFrameRepresentation* frame = static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_2);
	if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__DoubleExternalArray)
	{
		eml22__ExternalDataset const* dataset = static_cast<eml22__DoubleExternalArray*>(frame->NodeTimeValues)->Values;
		COMMON_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->ExternalFileProxy[0]->EpcExternalPartReference->Uuid);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The HDF proxy is missing.");
		}
		double* values = new double[getTimeValuesCount()];
		hdfProxy->readArrayNdOfDoubleValues(dataset->ExternalFileProxy[0]->PathInExternalFile, values);
		double result = values[0];
		delete[] values;

		return result;
	}
	else if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__FloatingPointLatticeArray)
	{
		return static_cast<eml22__FloatingPointLatticeArray*>(frame->NodeTimeValues)->StartValue;
	}
	else
		throw logic_error("The array structure of time is not supported?");
}

unsigned int SeismicWellboreFrameRepresentation::getTimeValuesCount() const
{
	return getMdValuesCount();
}

RESQML2_NS::AbstractValuesProperty::hdfDatatypeEnum SeismicWellboreFrameRepresentation::getTimeHdfDatatype() const
{
	_resqml22__SeismicWellboreFrameRepresentation* frame = static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_2);
	if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__DoubleExternalArray)
	{
		eml22__ExternalDataset const* dataset = static_cast<eml22__DoubleExternalArray*>(frame->NodeTimeValues)->Values;
		COMMON_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->ExternalFileProxy[0]->EpcExternalPartReference->Uuid);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The HDF proxy is missing.");
		}
		hid_t dt = hdfProxy->getHdfDatatypeInDataset(dataset->ExternalFileProxy[0]->PathInExternalFile);
		if (H5Tequal(dt, H5T_NATIVE_DOUBLE) > 0)
			return RESQML2_NS::AbstractValuesProperty::DOUBLE;
		else if (H5Tequal(dt, H5T_NATIVE_FLOAT) > 0)
			return RESQML2_NS::AbstractValuesProperty::FLOAT;
		else if (H5Tequal(dt, H5T_NATIVE_LLONG) > 0)
			return RESQML2_NS::AbstractValuesProperty::LONG_64;
		else if (H5Tequal(dt, H5T_NATIVE_ULLONG) > 0)
			return RESQML2_NS::AbstractValuesProperty::ULONG_64;
		else if (H5Tequal(dt, H5T_NATIVE_INT) > 0)
			return RESQML2_NS::AbstractValuesProperty::INT;
		else if (H5Tequal(dt, H5T_NATIVE_UINT) > 0)
			return RESQML2_NS::AbstractValuesProperty::UINT;
		else if (H5Tequal(dt, H5T_NATIVE_SHORT) > 0)
			return RESQML2_NS::AbstractValuesProperty::SHORT;
		else if (H5Tequal(dt, H5T_NATIVE_USHORT) > 0)
			return RESQML2_NS::AbstractValuesProperty::USHORT;
		else if (H5Tequal(dt, H5T_NATIVE_CHAR) > 0)
			return RESQML2_NS::AbstractValuesProperty::CHAR;
		else if (H5Tequal(dt, H5T_NATIVE_UCHAR) > 0)
			return RESQML2_NS::AbstractValuesProperty::UCHAR;
	}
	else if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__FloatingPointLatticeArray)
	{
		return RESQML2_NS::AbstractValuesProperty::DOUBLE;
	}

	return RESQML2_NS::AbstractValuesProperty::UNKNOWN; // unknwown datatype...
}

void SeismicWellboreFrameRepresentation::getTimeAsDoubleValues(double* values) const
{
	_resqml22__SeismicWellboreFrameRepresentation* frame = static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_2);
	if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__DoubleExternalArray)
	{
		eml22__ExternalDataset const* dataset = static_cast<eml22__DoubleExternalArray*>(frame->NodeTimeValues)->Values;
		COMMON_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->ExternalFileProxy[0]->EpcExternalPartReference->Uuid);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The HDF proxy is missing.");
		}
		hdfProxy->readArrayNdOfDoubleValues(dataset->ExternalFileProxy[0]->PathInExternalFile, values);
	}
	else if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__FloatingPointLatticeArray)
	{
		values[0] = static_cast<eml22__FloatingPointLatticeArray*>(frame->NodeTimeValues)->StartValue;
		eml22__FloatingPointConstantArray* constantArray = static_cast<eml22__FloatingPointLatticeArray*>(frame->NodeTimeValues)->Offset[0];
		for (ULONG64 inc = 1; inc <= constantArray->Count; ++inc)
			values[inc] = values[0] + (inc * constantArray->Value);
	}
	else {
		throw logic_error("The array structure of time values is not supported?");
	}
}


void SeismicWellboreFrameRepresentation::getTimeAsFloatValues(float* values) const
{
	_resqml22__SeismicWellboreFrameRepresentation* frame = static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_2);
	if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__DoubleExternalArray)
	{
		eml22__ExternalDataset const* dataset = static_cast<eml22__DoubleExternalArray*>(frame->NodeTimeValues)->Values;
		COMMON_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->ExternalFileProxy[0]->EpcExternalPartReference->Uuid);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The HDF proxy is missing.");
		}
		hdfProxy->readArrayNdOfFloatValues(dataset->ExternalFileProxy[0]->PathInExternalFile, values);
	}
	else if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__FloatingPointLatticeArray)
	{
		values[0] = static_cast<eml22__FloatingPointLatticeArray*>(frame->NodeTimeValues)->StartValue;
		eml22__FloatingPointConstantArray* constantArray = static_cast<eml22__FloatingPointLatticeArray*>(frame->NodeTimeValues)->Offset[0];
		for (ULONG64 inc = 1; inc <= constantArray->Count; ++inc)
			values[inc] = values[0] + (inc * constantArray->Value);
	}
	else {
		throw logic_error("The array structure of time values is not supported?");
	}
}

double SeismicWellboreFrameRepresentation::getSeismicReferenceDatum() const
{
	return static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_2)->SeismicReferenceDatum;
}

double SeismicWellboreFrameRepresentation::getWeatheringVelocity() const
{
	return static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_2)->WeatheringVelocity;
}
