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

#include "../eml2/AbstractHdfProxy.h"

#include "AbstractValuesProperty.h"

using namespace std;
using namespace RESQML2_NS;
using namespace gsoap_eml2_3;

void SeismicWellboreFrameRepresentation::setTimeValues(double const * timeValues, uint64_t timeValueCount, EML2_NS::AbstractHdfProxy* proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
	}
	getRepository()->addRelationship(this, proxy);

	_resqml22__SeismicWellboreFrameRepresentation* frame = static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_3);

	// XML
	eml23__FloatingPointExternalArray* xmlTimeValues = soap_new_eml23__FloatingPointExternalArray(gsoapProxy2_3->soap);
	xmlTimeValues->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlTimeValues->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() + "/timeValues", timeValueCount, proxy));

	frame->NodeTimeValues = xmlTimeValues;
	frame->NodeCount = timeValueCount;

	// HDF
	proxy->writeArrayNd(getHdfGroup(),
		"timeValues",
		COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE,
		timeValues,
		&timeValueCount, 1);
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
		EML2_NS::AbstractHdfProxy* hdfProxy = getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__FloatingPointExternalArray*>(frame->NodeTimeValues)->Values->ExternalDataArrayPart[0]);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The HDF proxy is missing.");
		}
		std::unique_ptr<double[]> values(new double[getTimeValuesCount()]);
		hdfProxy->readArrayNdOfDoubleValues(static_cast<eml23__FloatingPointExternalArray*>(frame->NodeTimeValues)->Values->ExternalDataArrayPart[0]->PathInExternalFile, values.get());

		return values[0];
	}
	else if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
	{
		return static_cast<eml23__FloatingPointLatticeArray*>(frame->NodeTimeValues)->StartValue;
	}
	else
		throw logic_error("The array structure of time is not supported?");
}

uint64_t SeismicWellboreFrameRepresentation::getTimeValuesCount() const
{
	return getMdValuesCount();
}

COMMON_NS::AbstractObject::numericalDatatypeEnum SeismicWellboreFrameRepresentation::getTimeHdfDatatype() const
{
	_resqml22__SeismicWellboreFrameRepresentation* frame = static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_3);
	if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray)
	{
		EML2_NS::AbstractHdfProxy* hdfProxy = getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__FloatingPointExternalArray*>(frame->NodeTimeValues)->Values->ExternalDataArrayPart[0]);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The HDF proxy is missing.");
		}
		return hdfProxy->getNumericalDatatype(static_cast<eml23__FloatingPointExternalArray*>(frame->NodeTimeValues)->Values->ExternalDataArrayPart[0]->PathInExternalFile);
	}
	else if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
	{
		return COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE;
	}

	return COMMON_NS::AbstractObject::numericalDatatypeEnum::UNKNOWN; // unknwown datatype...
}

void SeismicWellboreFrameRepresentation::getTimeAsDoubleValues(double* values) const
{
	_resqml22__SeismicWellboreFrameRepresentation* frame = static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_3);
	if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray)
	{
		EML2_NS::AbstractHdfProxy* hdfProxy = getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__FloatingPointExternalArray*>(frame->NodeTimeValues)->Values->ExternalDataArrayPart[0]);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The HDF proxy is missing.");
		}
		hdfProxy->readArrayNdOfDoubleValues(static_cast<eml23__FloatingPointExternalArray*>(frame->NodeTimeValues)->Values->ExternalDataArrayPart[0]->PathInExternalFile, values);
	}
	else if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
	{
		values[0] = static_cast<eml23__FloatingPointLatticeArray*>(frame->NodeTimeValues)->StartValue;
		eml23__FloatingPointConstantArray* constantArray = static_cast<eml23__FloatingPointLatticeArray*>(frame->NodeTimeValues)->Offset[0];
		for (auto inc = 1; inc <= constantArray->Count; ++inc)
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
		EML2_NS::AbstractHdfProxy* hdfProxy = getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__FloatingPointExternalArray*>(frame->NodeTimeValues)->Values->ExternalDataArrayPart[0]);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The HDF proxy is missing.");
		}
		hdfProxy->readArrayNdOfFloatValues(static_cast<eml23__FloatingPointExternalArray*>(frame->NodeTimeValues)->Values->ExternalDataArrayPart[0]->PathInExternalFile, values);
	}
	else if (frame->NodeTimeValues->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
	{
		values[0] = static_cast<eml23__FloatingPointLatticeArray*>(frame->NodeTimeValues)->StartValue;
		eml23__FloatingPointConstantArray* constantArray = static_cast<eml23__FloatingPointLatticeArray*>(frame->NodeTimeValues)->Offset[0];
		for (int64_t inc = 1; inc <= constantArray->Count; ++inc) {
			values[inc] = values[0] + (inc * constantArray->Value);
		}
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
