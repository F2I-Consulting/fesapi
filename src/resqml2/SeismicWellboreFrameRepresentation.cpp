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

#include "../eml2/AbstractHdfProxy.h"
#include "../resqml2/LocalTime3dCrs.h"
#include "../resqml2/WellboreInterpretation.h"
#include "../resqml2/WellboreTrajectoryRepresentation.h"

using namespace std;
using namespace RESQML2_NS;
using namespace gsoap_eml2_3;

const char* SeismicWellboreFrameRepresentation::XML_TAG = "SeismicWellboreFrameRepresentation";

void SeismicWellboreFrameRepresentation::setTimeValues(double const * timeValues, unsigned int timeValueCount, EML2_NS::AbstractHdfProxy* proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
	}
	getRepository()->addRelationship(this, proxy);

	_resqml22__SeismicWellboreFrameRepresentation* frame = static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_3);

	// XML

	eml23__FloatingPointExternalArray* xmlTimeValues = soap_new_eml23__FloatingPointExternalArray(gsoapProxy2_3->soap);
	xmlTimeValues->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	xmlTimeValues->Values->ExternalFileProxy.push_back(soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap, 1));
	xmlTimeValues->Values->ExternalFileProxy[0]->Count = timeValueCount;
	xmlTimeValues->Values->ExternalFileProxy[0]->StartIndex = 0;
	xmlTimeValues->Values->ExternalFileProxy[0]->PathInExternalFile = getHdfGroup() + "/timeValues";
	xmlTimeValues->Values->ExternalFileProxy[0]->EpcExternalPartReference = proxy->newEml23Reference();

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
	_resqml22__SeismicWellboreFrameRepresentation* frame = static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_3);

	// XML
	eml23__FloatingPointLatticeArray* xmlTimeValues = soap_new_eml23__FloatingPointLatticeArray(gsoapProxy2_3->soap);
	xmlTimeValues->StartValue = firstTimeValue;
	xmlTimeValues->Offset.push_back(soap_new_eml23__FloatingPointConstantArray(gsoapProxy2_3->soap, 1));
	xmlTimeValues->Offset[0]->Count = timeValueCount - 1;
	xmlTimeValues->Offset[0]->Value = incrementTimeValue;

	frame->NodeTimeValues = xmlTimeValues;

	frame->NodeCount = timeValueCount;
}

bool SeismicWellboreFrameRepresentation::areTimeValuesRegularlySpaced() const
{
	return static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_3)->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray;
}

double SeismicWellboreFrameRepresentation::getTimeConstantIncrementValue() const
{
	if (!areTimeValuesRegularlySpaced()) {
		throw invalid_argument("The time values are not regularly spaced.");
	}

	return static_cast<eml23__FloatingPointLatticeArray*>(static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_3)->NodeTimeValues)->Offset[0]->Value;
}

double SeismicWellboreFrameRepresentation::getTimeFirstValue() const
{
	_resqml22__SeismicWellboreFrameRepresentation* frame = static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_3);
	if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray)
	{
		eml23__ExternalDataset const* dataset = static_cast<eml23__FloatingPointExternalArray*>(frame->NodeTimeValues)->Values;
		EML2_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dataset->ExternalFileProxy[0]->EpcExternalPartReference->Uuid);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The HDF proxy is missing.");
		}
		double* values = new double[getTimeValuesCount()];
		hdfProxy->readArrayNdOfDoubleValues(dataset->ExternalFileProxy[0]->PathInExternalFile, values);
		double result = values[0];
		delete[] values;

		return result;
	}
	else if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
	{
		return static_cast<eml23__FloatingPointLatticeArray*>(frame->NodeTimeValues)->StartValue;
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
	_resqml22__SeismicWellboreFrameRepresentation* frame = static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_3);
	if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray)
	{
		eml23__ExternalDataset const* dataset = static_cast<eml23__FloatingPointExternalArray*>(frame->NodeTimeValues)->Values;
		EML2_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dataset->ExternalFileProxy[0]->EpcExternalPartReference->Uuid);
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
	else if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
	{
		return RESQML2_NS::AbstractValuesProperty::DOUBLE;
	}

	return RESQML2_NS::AbstractValuesProperty::UNKNOWN; // unknwown datatype...
}

void SeismicWellboreFrameRepresentation::getTimeAsDoubleValues(double* values) const
{
	_resqml22__SeismicWellboreFrameRepresentation* frame = static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_3);
	if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray)
	{
		eml23__ExternalDataset const* dataset = static_cast<eml23__FloatingPointExternalArray*>(frame->NodeTimeValues)->Values;
		EML2_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dataset->ExternalFileProxy[0]->EpcExternalPartReference->Uuid);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The HDF proxy is missing.");
		}
		hdfProxy->readArrayNdOfDoubleValues(dataset->ExternalFileProxy[0]->PathInExternalFile, values);
	}
	else if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
	{
		values[0] = static_cast<eml23__FloatingPointLatticeArray*>(frame->NodeTimeValues)->StartValue;
		eml23__FloatingPointConstantArray* constantArray = static_cast<eml23__FloatingPointLatticeArray*>(frame->NodeTimeValues)->Offset[0];
		for (ULONG64 inc = 1; inc <= constantArray->Count; ++inc)
			values[inc] = values[0] + (inc * constantArray->Value);
	}
	else {
		throw logic_error("The array structure of time values is not supported?");
	}
}


void SeismicWellboreFrameRepresentation::getTimeAsFloatValues(float* values) const
{
	_resqml22__SeismicWellboreFrameRepresentation* frame = static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_3);
	if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray)
	{
		eml23__ExternalDataset const* dataset = static_cast<eml23__FloatingPointExternalArray*>(frame->NodeTimeValues)->Values;
		EML2_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dataset->ExternalFileProxy[0]->EpcExternalPartReference->Uuid);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The HDF proxy is missing.");
		}
		hdfProxy->readArrayNdOfFloatValues(dataset->ExternalFileProxy[0]->PathInExternalFile, values);
	}
	else if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
	{
		values[0] = static_cast<eml23__FloatingPointLatticeArray*>(frame->NodeTimeValues)->StartValue;
		eml23__FloatingPointConstantArray* constantArray = static_cast<eml23__FloatingPointLatticeArray*>(frame->NodeTimeValues)->Offset[0];
		for (ULONG64 inc = 1; inc <= constantArray->Count; ++inc)
			values[inc] = values[0] + (inc * constantArray->Value);
	}
	else {
		throw logic_error("The array structure of time values is not supported?");
	}
}

double SeismicWellboreFrameRepresentation::getSeismicReferenceDatum() const
{
	return static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_3)->SeismicReferenceDatum;
}

double SeismicWellboreFrameRepresentation::getWeatheringVelocity() const
{
	return static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_3)->WeatheringVelocity;
}
