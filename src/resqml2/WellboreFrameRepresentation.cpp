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

#include <hdf5.h>

#include "../eml2/AbstractHdfProxy.h"
#include "../eml2/ReferencePointInALocalEngineeringCompoundCrs.h"

#include "AbstractValuesProperty.h"
#include "WellboreTrajectoryRepresentation.h"

using namespace std;
using namespace RESQML2_NS;
using namespace gsoap_resqml2_0_1;
using namespace gsoap_eml2_3;

void WellboreFrameRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	auto trajectory = getWellboreTrajectory();
	if (trajectory == nullptr || trajectory->isPartial()) {
		throw logic_error("Cannot compute the XYZ points of the frame without the trajectory.");
	}
	auto mdDatum = trajectory->getMdDatum();
	if (mdDatum == nullptr || mdDatum->isPartial()) {
		throw logic_error("Cannot compute the XYZ points of the frame without the MD datum.");
	}

	// We add 1 trajectory station for MDDatum support.
	auto trajStationCount = trajectory->getXyzPointCountOfPatch(patchIndex) + 1;
	if (trajStationCount == 0) {
		throw logic_error("Cannot compute the XYZ points of the frame with a trajectory which does not contain any trajectory station.");
	}
	std::unique_ptr<double[]> mdTrajValues(new double[trajStationCount]);
	mdTrajValues[0] = .0; // MD Datum
	trajectory->getMdValues(mdTrajValues.get() + 1);

	std::unique_ptr<double[]> xyzTrajValues(new double[trajStationCount*3]);
	xyzTrajValues[0] = mdDatum->getX();
	xyzTrajValues[1] = mdDatum->getY();
	xyzTrajValues[2] = mdDatum->getZ();
	trajectory->getXyzPointsOfPatch(patchIndex, xyzTrajValues.get() + 3);
	
	const auto mdCount = getXyzPointCountOfPatch(patchIndex);
	std::unique_ptr<double[]> mdFrameValues(new double[mdCount]);
	getMdAsDoubleValues(mdFrameValues.get());
	size_t nextTrajStationIndex = 1;
	for (size_t i = 0; i < mdCount; ++i) {
		while (nextTrajStationIndex < trajStationCount &&
			mdTrajValues[nextTrajStationIndex] <= mdFrameValues[i]) {
			++nextTrajStationIndex;
		}
		if (nextTrajStationIndex == trajStationCount) {
			if (mdTrajValues[nextTrajStationIndex - 1] != mdFrameValues[i]) {
				throw range_error("Cannot compute the frame MD " + std::to_string(mdFrameValues[i]) + " because it is out of the trajectory range");
			}
			nextTrajStationIndex = nextTrajStationIndex - 1;
		}

		const size_t previousTrajStationIndex = nextTrajStationIndex - 1;
		const double mdDistance = mdTrajValues[nextTrajStationIndex] - mdTrajValues[previousTrajStationIndex];
		const double ratioFromPreviousControlPoint = mdDistance != .0
			? (mdFrameValues[i] - mdTrajValues[previousTrajStationIndex]) / mdDistance
			: .0;

		xyzPoints[i * 3] = xyzTrajValues[previousTrajStationIndex * 3] + ratioFromPreviousControlPoint * (xyzTrajValues[nextTrajStationIndex * 3] - xyzTrajValues[previousTrajStationIndex * 3]);
		xyzPoints[i * 3 + 1] = xyzTrajValues[previousTrajStationIndex * 3 + 1] + ratioFromPreviousControlPoint * (xyzTrajValues[nextTrajStationIndex * 3 + 1] - xyzTrajValues[previousTrajStationIndex * 3 + 1]);
		xyzPoints[i * 3 + 2] = xyzTrajValues[previousTrajStationIndex * 3 + 2] + ratioFromPreviousControlPoint * (xyzTrajValues[nextTrajStationIndex * 3 + 2] - xyzTrajValues[previousTrajStationIndex * 3 + 2]);
	}
}

void WellboreFrameRepresentation::setMdValues(double const * mdValues, unsigned int mdValueCount, EML2_NS::AbstractHdfProxy* proxy)
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
		xmlMdValues->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/mdValues", mdValueCount, proxy));

		frame->NodeMd = xmlMdValues;
		frame->NodeCount = mdValueCount;
	}
	else {
		throw invalid_argument("Not implemented yet");
	}

	// HDF
	hsize_t dim = mdValueCount;
	proxy->writeArrayNd(getHdfGroup(),
		"mdValues",
		H5T_NATIVE_DOUBLE,
		mdValues,
		&dim, 1);
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
			double result = values[0];

			return result;
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
			double result = values[0];

			return result;
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

COMMON_NS::AbstractObject::hdfDatatypeEnum WellboreFrameRepresentation::getMdHdfDatatype() const
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
			return hdfProxy->getHdfDatatypeInDataset(dataset->PathInHdfFile);
		}
		else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
		{
			return RESQML2_NS::AbstractValuesProperty::DOUBLE;
		}

		return RESQML2_NS::AbstractValuesProperty::UNKNOWN; // unknwown datatype...
	}
	else if (gsoapProxy2_3 != nullptr) {
		_resqml22__WellboreFrameRepresentation* frame = static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_3);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray)
		{
			EML2_NS::AbstractHdfProxy* hdfProxy = getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__FloatingPointExternalArray*>(frame->NodeMd)->Values->ExternalDataArrayPart[0]);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The HDF proxy is missing.");
			}
			return hdfProxy->getHdfDatatypeInDataset(static_cast<eml23__FloatingPointExternalArray*>(frame->NodeMd)->Values->ExternalDataArrayPart[0]->PathInExternalFile);
		}
		else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
		{
			return RESQML2_NS::AbstractValuesProperty::DOUBLE;
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
			values[0] = static_cast<resqml20__DoubleLatticeArray*>(frame->NodeMd)->StartValue;
			resqml20__DoubleConstantArray* constantArray = static_cast<resqml20__DoubleLatticeArray*>(frame->NodeMd)->Offset[0];
			for (uint64_t inc = 1; inc <= constantArray->Count; ++inc)
				values[inc] = values[0] + (inc * constantArray->Value);
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
			values[0] = static_cast<eml23__FloatingPointLatticeArray*>(frame->NodeMd)->StartValue;
			eml23__FloatingPointConstantArray* constantArray = static_cast<eml23__FloatingPointLatticeArray*>(frame->NodeMd)->Offset[0];
			for (int64_t inc = 1; inc <= constantArray->Count; ++inc)
				values[inc] = values[0] + (inc * constantArray->Value);
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
			values[0] = static_cast<resqml20__DoubleLatticeArray*>(frame->NodeMd)->StartValue;
			resqml20__DoubleConstantArray* constantArray = static_cast<resqml20__DoubleLatticeArray*>(frame->NodeMd)->Offset[0];
			for (uint64_t inc = 1; inc <= constantArray->Count; ++inc) {
				values[inc] = values[0] + (inc * constantArray->Value);
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
			values[0] = static_cast<eml23__FloatingPointLatticeArray*>(frame->NodeMd)->StartValue;
			eml23__FloatingPointConstantArray* constantArray = static_cast<eml23__FloatingPointLatticeArray*>(frame->NodeMd)->Offset[0];
			for (int64_t inc = 1; inc <= constantArray->Count; ++inc)
				values[inc] = values[0] + (inc * constantArray->Value);
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
	if (!dor.isEmpty()) {
		convertDorIntoRel(dor);
	}

	AbstractRepresentation::loadTargetRelationships();
}
