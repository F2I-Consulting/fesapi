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
#include "WellboreFrameRepresentation.h"

#include <stdexcept>

#include "../eml2/AbstractHdfProxy.h"
#include "MdDatum.h"
#include "WellboreTrajectoryRepresentation.h"

using namespace std;
using namespace RESQML2_NS;
using namespace gsoap_resqml2_0_1;
using namespace gsoap_eml2_3;

void WellboreFrameRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double* xyzPoints) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	auto const* trajectory = getWellboreTrajectory();
	if (trajectory == nullptr || trajectory->isPartial()) {
		throw logic_error("Cannot compute the XYZ points of the frame without the trajectory.");
	}
	
	const auto mdCount = getXyzPointCountOfPatch(patchIndex);
	std::unique_ptr<double[]> mdFrameValues(new double[mdCount]);
	getMdAsDoubleValues(mdFrameValues.get());
	trajectory->convertMdValuesToXyzValues(mdFrameValues.get(), mdCount, xyzPoints);
}

void WellboreFrameRepresentation::setMdValues(double const * mdValues, uint64_t mdValueCount, EML2_NS::AbstractHdfProxy* proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

	string frameUuid;
	if (gsoapProxy2_0_1 != nullptr) {
		_resqml20__WellboreFrameRepresentation* frame = static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1);
		frameUuid = frame->uuid;

		// XML
		resqml20__DoubleHdf5Array* xmlMdValues = soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
		xmlMdValues->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		xmlMdValues->Values->HdfProxy = proxy->newResqmlReference();
		xmlMdValues->Values->PathInHdfFile = getHdfGroup() + "/mdValues";

		frame->NodeMd = xmlMdValues;

		frame->NodeCount = mdValueCount;
	}
	else if (gsoapProxy2_3 != nullptr) {
		_resqml22__WellboreFrameRepresentation* frame = static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_3);
		frameUuid = frame->uuid;

		// XML
		eml23__FloatingPointExternalArray* xmlMdValues = soap_new_eml23__FloatingPointExternalArray(gsoapProxy2_3->soap);
		xmlMdValues->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
		xmlMdValues->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() + "/mdValues", mdValueCount, proxy));

		frame->NodeMd = xmlMdValues;
		frame->NodeCount = mdValueCount;
	}
	else {
		throw invalid_argument("Not implemented yet");
	}

	// HDF
	proxy->writeArrayNd(getHdfGroup(),
		"mdValues",
		COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE,
		mdValues,
		&mdValueCount, 1);
}

void WellboreFrameRepresentation::setMdValues(double firstMdValue, double incrementMdValue, unsigned int mdValueCount)
{
	if (gsoapProxy2_0_1 != nullptr) {
		_resqml20__WellboreFrameRepresentation* frame = static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1);

		// XML
		resqml20__DoubleLatticeArray* xmlMdValues = soap_new_resqml20__DoubleLatticeArray(gsoapProxy2_0_1->soap);
		xmlMdValues->StartValue = firstMdValue;
		xmlMdValues->Offset.push_back(soap_new_resqml20__DoubleConstantArray(gsoapProxy2_0_1->soap, 1));
		xmlMdValues->Offset[0]->Count = mdValueCount - 1;
		xmlMdValues->Offset[0]->Value = incrementMdValue;

		frame->NodeMd = xmlMdValues;

		frame->NodeCount = mdValueCount;
	}
	else if (gsoapProxy2_3 != nullptr) {
		_resqml22__WellboreFrameRepresentation* frame = static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_3);

		// XML
		eml23__FloatingPointLatticeArray* xmlMdValues = soap_new_eml23__FloatingPointLatticeArray(gsoapProxy2_3->soap);
		xmlMdValues->StartValue = firstMdValue;
		xmlMdValues->Offset.push_back(soap_new_eml23__FloatingPointConstantArray(gsoapProxy2_3->soap, 1));
		xmlMdValues->Offset[0]->Count = mdValueCount - 1;
		xmlMdValues->Offset[0]->Value = incrementMdValue;

		frame->NodeMd = xmlMdValues;

		frame->NodeCount = mdValueCount;
	}
	else {
		throw invalid_argument("Not implemented yet");
	}
}

bool WellboreFrameRepresentation::areMdValuesRegularlySpaced() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1)->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_3)->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray;
	}
	
	throw invalid_argument("Not implemented yet");
}
	
double WellboreFrameRepresentation::getMdConstantIncrementValue() const
{
	if (!areMdValuesRegularlySpaced()) {
		throw invalid_argument("The MD values are not regularly spaced.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<resqml20__DoubleLatticeArray*>(static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1)->NodeMd)->Offset[0]->Value;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<eml23__FloatingPointLatticeArray*>(static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_3)->NodeMd)->Offset[0]->Value;
	}

	throw invalid_argument("Not implemented yet");
}

double WellboreFrameRepresentation::getMdFirstValue() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		_resqml20__WellboreFrameRepresentation* frame = static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array)
		{
			eml20__Hdf5Dataset const* dataset = static_cast<resqml20__DoubleHdf5Array*>(frame->NodeMd)->Values;
			EML2_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The HDF proxy is missing.");
			}
			std::unique_ptr<double[]> values(new double[getMdValuesCount()]);
			hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, values.get());

			return values[0];
		}
		else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
		{
			return static_cast<resqml20__DoubleLatticeArray*>(frame->NodeMd)->StartValue;
		}
		else
			throw logic_error("The array structure of MD is not supported?");
	}
	else if (gsoapProxy2_3 != nullptr) {
		_resqml22__WellboreFrameRepresentation* frame = static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_3);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray)
		{
			EML2_NS::AbstractHdfProxy* hdfProxy = getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__FloatingPointExternalArray*>(frame->NodeMd)->Values->ExternalDataArrayPart[0]);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The HDF proxy is missing.");
			}
			std::unique_ptr<double[]> values(new double[getMdValuesCount()]);
			hdfProxy->readArrayNdOfDoubleValues(static_cast<eml23__FloatingPointExternalArray*>(frame->NodeMd)->Values->ExternalDataArrayPart[0]->PathInExternalFile, values.get());

			return values[0];
		}
		else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
		{
			return static_cast<eml23__FloatingPointLatticeArray*>(frame->NodeMd)->StartValue;
		}
		else
			throw logic_error("The array structure of MD is not supported?");
	}

	throw invalid_argument("Not implemented yet");
}

unsigned int WellboreFrameRepresentation::getMdValuesCount() const
{
	uint64_t result;

	if (gsoapProxy2_0_1 != nullptr) {
		result = static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1)->NodeCount;
	}
	else if (gsoapProxy2_3 != nullptr) {
		result = static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_3)->NodeCount;
	}
	else {
		throw invalid_argument("Not implemented yet");
	}

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much md values.");
	}

	return static_cast<unsigned int>(result);
}

COMMON_NS::AbstractObject::numericalDatatypeEnum WellboreFrameRepresentation::getMdHdfDatatype() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		_resqml20__WellboreFrameRepresentation* frame = static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array)
		{
			eml20__Hdf5Dataset const* dataset = static_cast<resqml20__DoubleHdf5Array*>(frame->NodeMd)->Values;
			EML2_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The HDF proxy is missing.");
			}
			return hdfProxy->getNumericalDatatype(dataset->PathInHdfFile);
		}
		else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
		{
			return COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE;
		}

		return COMMON_NS::AbstractObject::numericalDatatypeEnum::UNKNOWN; // unknwown datatype...
	}
	else if (gsoapProxy2_3 != nullptr) {
		_resqml22__WellboreFrameRepresentation* frame = static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_3);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray)
		{
			EML2_NS::AbstractHdfProxy* hdfProxy = getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__FloatingPointExternalArray*>(frame->NodeMd)->Values->ExternalDataArrayPart[0]);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The HDF proxy is missing.");
			}
			return hdfProxy->getNumericalDatatype(static_cast<eml23__FloatingPointExternalArray*>(frame->NodeMd)->Values->ExternalDataArrayPart[0]->PathInExternalFile);
		}
		else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
		{
			return COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE;
		}
	}

	throw invalid_argument("Not implemented yet");
}

void WellboreFrameRepresentation::getMdAsDoubleValues(double* values) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		_resqml20__WellboreFrameRepresentation* frame = static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array)
		{
			eml20__Hdf5Dataset const* dataset = static_cast<resqml20__DoubleHdf5Array*>(frame->NodeMd)->Values;
			EML2_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The HDF proxy is missing.");
			}
			hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, values);
		}
		else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
		{
			auto const* dla = static_cast<resqml20__DoubleLatticeArray*>(frame->NodeMd);
			values[0] = dla->StartValue;
			resqml20__DoubleConstantArray* constantArray = dla->Offset[0];
			for (uint64_t inc = 1; inc <= constantArray->Count; ++inc) {
				values[inc] = values[inc - 1] + constantArray->Value;
			}
		}
		else {
			throw logic_error("The array structure of MD is not supported?");
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		_resqml22__WellboreFrameRepresentation* frame = static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_3);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray)
		{
			EML2_NS::AbstractHdfProxy* hdfProxy = getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__FloatingPointExternalArray*>(frame->NodeMd)->Values->ExternalDataArrayPart[0]);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The HDF proxy is missing.");
			}
			hdfProxy->readArrayNdOfDoubleValues(static_cast<eml23__FloatingPointExternalArray*>(frame->NodeMd)->Values->ExternalDataArrayPart[0]->PathInExternalFile, values);
		}
		else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
		{
			auto const* fla = static_cast<eml23__FloatingPointLatticeArray*>(frame->NodeMd);
			values[0] = fla->StartValue;
			eml23__FloatingPointConstantArray* constantArray = fla->Offset[0];
			for (int64_t inc = 1; inc <= constantArray->Count; ++inc) {
				values[inc] = values[inc - 1] + constantArray->Value;
			}
		}
		else {
			throw logic_error("The array structure of MD is not supported?");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void WellboreFrameRepresentation::getMdAsFloatValues(float* values) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		_resqml20__WellboreFrameRepresentation* frame = static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array)
		{
			eml20__Hdf5Dataset const* dataset = static_cast<resqml20__DoubleHdf5Array*>(frame->NodeMd)->Values;
			EML2_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The HDF proxy is missing.");
			}
			hdfProxy->readArrayNdOfFloatValues(dataset->PathInHdfFile, values);
		}
		else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
		{
			auto const* dla = static_cast<resqml20__DoubleLatticeArray*>(frame->NodeMd);
			values[0] = dla->StartValue;
			resqml20__DoubleConstantArray* constantArray = dla->Offset[0];
			for (uint64_t inc = 1; inc <= constantArray->Count; ++inc) {
				values[inc] = values[inc - 1] + constantArray->Value;
			}
		}
		else {
			throw logic_error("The array structure of MD is not supported?");
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		_resqml22__WellboreFrameRepresentation* frame = static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_3);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray)
		{
			EML2_NS::AbstractHdfProxy* hdfProxy = getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__FloatingPointExternalArray*>(frame->NodeMd)->Values->ExternalDataArrayPart[0]);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The HDF proxy is missing.");
			}
			hdfProxy->readArrayNdOfFloatValues(static_cast<eml23__FloatingPointExternalArray*>(frame->NodeMd)->Values->ExternalDataArrayPart[0]->PathInExternalFile, values);
		}
		else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
		{
			auto const* fla = static_cast<eml23__FloatingPointLatticeArray*>(frame->NodeMd);
			values[0] = fla->StartValue;
			eml23__FloatingPointConstantArray* constantArray = fla->Offset[0];
			for (int64_t inc = 1; inc <= constantArray->Count; ++inc) {
				values[inc] = values[inc - 1] + constantArray->Value;
			}
		}
		else {
			throw logic_error("The array structure of MD is not supported?");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

COMMON_NS::DataObjectReference WellboreFrameRepresentation::getWellboreTrajectoryDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return COMMON_NS::DataObjectReference(static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1)->Trajectory);
	}
	else if (gsoapProxy2_3 != nullptr) {
		return COMMON_NS::DataObjectReference(static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_3)->Trajectory);
	}

	throw invalid_argument("Not implemented yet");
}

COMMON_NS::DataObjectReference WellboreFrameRepresentation::getLocalCrsDor(unsigned int patchIndex) const
{
	auto* traj = getWellboreTrajectory();
	return traj->isPartial() ? COMMON_NS::DataObjectReference() : getWellboreTrajectory()->getLocalCrsDor(patchIndex);
}

COMMON_NS::DataObjectReference WellboreFrameRepresentation::getHdfProxyDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		_resqml20__WellboreFrameRepresentation* frame = static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array)
		{
			return COMMON_NS::DataObjectReference(static_cast<resqml20__DoubleHdf5Array*>(frame->NodeMd)->Values->HdfProxy);
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		_resqml22__WellboreFrameRepresentation* frame = static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_3);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray) {
			return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__FloatingPointExternalArray*>(frame->NodeMd)->Values->ExternalDataArrayPart[0]));
		}
	}
	else {
		throw invalid_argument("Not implemented yet");
	}

	return COMMON_NS::DataObjectReference();
}

uint64_t WellboreFrameRepresentation::getXyzPointCountOfPatch(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The patch index is out of range");
	}

	return getMdValuesCount();
}

WellboreTrajectoryRepresentation* WellboreFrameRepresentation::getWellboreTrajectory() const
{
	return getRepository()->getDataObjectByUuid<WellboreTrajectoryRepresentation>(getWellboreTrajectoryDor().getUuid());
}

void WellboreFrameRepresentation::loadTargetRelationships()
{
	COMMON_NS::DataObjectReference dor = getWellboreTrajectoryDor();
	// todo the trajectory should be resqml2 instead of resqml2_0_1
	WellboreTrajectoryRepresentation* traj = getRepository()->getDataObjectByUuid<WellboreTrajectoryRepresentation>(dor.getUuid());
	if (traj == nullptr) { // partial transfer
		getRepository()->createPartial(dor);
		traj = getRepository()->getDataObjectByUuid<WellboreTrajectoryRepresentation>(dor.getUuid());
	}
	if (traj == nullptr) {
		throw invalid_argument("The DOR looks invalid.");
	}
	repository->addRelationship(this, traj);

	AbstractRepresentation::loadTargetRelationships();
}
