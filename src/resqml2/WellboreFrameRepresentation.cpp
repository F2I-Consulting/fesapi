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

#include "AbstractLocal3dCrs.h"
#include "../common/AbstractHdfProxy.h"
#include "../tools/Misc.h"

using namespace std;
using namespace RESQML2_NS;
using namespace gsoap_resqml2_0_1;
using namespace gsoap_eml2_2;

void WellboreFrameRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double *) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index of the patch is not in the allowed range of patch.");

	throw logic_error("Not implemented yet");
}

void WellboreFrameRepresentation::setMdValues(double const * mdValues, unsigned int mdValueCount, COMMON_NS::AbstractHdfProxy* proxy)
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
	else if (gsoapProxy2_2 != nullptr) {
		_resqml22__WellboreFrameRepresentation* frame = static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_2);
		frameUuid = frame->uuid;

		// XML
		eml22__DoubleExternalArray* xmlMdValues = soap_new_eml22__DoubleExternalArray(gsoapProxy2_2->soap);
		xmlMdValues->Values = soap_new_eml22__ExternalDataset(gsoapProxy2_2->soap);
		xmlMdValues->Values->ExternalFileProxy.push_back(soap_new_eml22__ExternalDatasetPart(gsoapProxy2_2->soap, 1));
		xmlMdValues->Values->ExternalFileProxy[0]->Count = mdValueCount;
		xmlMdValues->Values->ExternalFileProxy[0]->StartIndex = 0;
		xmlMdValues->Values->ExternalFileProxy[0]->PathInExternalFile = getHdfGroup() + "/mdValues";
		xmlMdValues->Values->ExternalFileProxy[0]->EpcExternalPartReference = proxy->newEml22Reference();

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
	else if (gsoapProxy2_2 != nullptr) {
		_resqml22__WellboreFrameRepresentation* frame = static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_2);

		// XML
		eml22__FloatingPointLatticeArray* xmlMdValues = soap_new_eml22__FloatingPointLatticeArray(gsoapProxy2_2->soap);
		xmlMdValues->StartValue = firstMdValue;
		xmlMdValues->Offset.push_back(soap_new_eml22__FloatingPointConstantArray(gsoapProxy2_2->soap, 1));
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
	else if (gsoapProxy2_2 != nullptr) {
		return static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_2)->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__FloatingPointLatticeArray;
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
	else if (gsoapProxy2_2 != nullptr) {
		return static_cast<eml22__FloatingPointLatticeArray*>(static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_2)->NodeMd)->Offset[0]->Value;
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
			COMMON_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The HDF proxy is missing.");
			}
			double* values = new double[getMdValuesCount()];
			hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, values);
			double result = values[0];
			delete[] values;

			return result;
		}
		else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
		{
			return static_cast<resqml20__DoubleLatticeArray*>(frame->NodeMd)->StartValue;
		}
		else
			throw logic_error("The array structure of MD is not supported?");
	}
	else if (gsoapProxy2_2 != nullptr) {
		_resqml22__WellboreFrameRepresentation* frame = static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_2);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__DoubleExternalArray)
		{
			eml22__ExternalDataset const* dataset = static_cast<eml22__DoubleExternalArray*>(frame->NodeMd)->Values;
			COMMON_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->ExternalFileProxy[0]->EpcExternalPartReference->Uuid);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The HDF proxy is missing.");
			}
			double* values = new double[getMdValuesCount()];
			hdfProxy->readArrayNdOfDoubleValues(dataset->ExternalFileProxy[0]->PathInExternalFile, values);
			double result = values[0];
			delete[] values;

			return result;
		}
		else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__FloatingPointLatticeArray)
		{
			return static_cast<eml22__FloatingPointLatticeArray*>(frame->NodeMd)->StartValue;
		}
		else
			throw logic_error("The array structure of MD is not supported?");
	}

	throw invalid_argument("Not implemented yet");
}

unsigned int WellboreFrameRepresentation::getMdValuesCount() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1)->NodeCount;
	}
	else if (gsoapProxy2_2 != nullptr) {
		return static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_2)->NodeCount;
	}

	throw invalid_argument("Not implemented yet");
}

RESQML2_NS::AbstractValuesProperty::hdfDatatypeEnum WellboreFrameRepresentation::getMdHdfDatatype() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		_resqml20__WellboreFrameRepresentation* frame = static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array)
		{
			eml20__Hdf5Dataset const* dataset = static_cast<resqml20__DoubleHdf5Array*>(frame->NodeMd)->Values;
			COMMON_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The HDF proxy is missing.");
			}
			hid_t dt = hdfProxy->getHdfDatatypeInDataset(dataset->PathInHdfFile);
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
		else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
		{
			return RESQML2_NS::AbstractValuesProperty::DOUBLE;
		}

		return RESQML2_NS::AbstractValuesProperty::UNKNOWN; // unknwown datatype...
	}
	else if (gsoapProxy2_2 != nullptr) {
		_resqml22__WellboreFrameRepresentation* frame = static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_2);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__DoubleExternalArray)
		{
			eml22__ExternalDataset const* dataset = static_cast<eml22__DoubleExternalArray*>(frame->NodeMd)->Values;
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
		else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__FloatingPointLatticeArray)
		{
			return RESQML2_NS::AbstractValuesProperty::DOUBLE;
		}

		return RESQML2_NS::AbstractValuesProperty::UNKNOWN; // unknwown datatype...
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
			COMMON_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The HDF proxy is missing.");
			}
			hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, values);
		}
		else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
		{
			values[0] = static_cast<resqml20__DoubleLatticeArray*>(frame->NodeMd)->StartValue;
			resqml20__DoubleConstantArray* constantArray = static_cast<resqml20__DoubleLatticeArray*>(frame->NodeMd)->Offset[0];
			for (ULONG64 inc = 1; inc <= constantArray->Count; ++inc)
				values[inc] = values[0] + (inc * constantArray->Value);
		}
		else {
			throw logic_error("The array structure of MD is not supported?");
		}
	}
	else if (gsoapProxy2_2 != nullptr) {
		_resqml22__WellboreFrameRepresentation* frame = static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_2);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__DoubleExternalArray)
		{
			eml22__ExternalDataset const* dataset = static_cast<eml22__DoubleExternalArray*>(frame->NodeMd)->Values;
			COMMON_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->ExternalFileProxy[0]->EpcExternalPartReference->Uuid);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The HDF proxy is missing.");
			}
			hdfProxy->readArrayNdOfDoubleValues(dataset->ExternalFileProxy[0]->PathInExternalFile, values);
		}
		else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__FloatingPointLatticeArray)
		{
			values[0] = static_cast<eml22__FloatingPointLatticeArray*>(frame->NodeMd)->StartValue;
			eml22__FloatingPointConstantArray* constantArray = static_cast<eml22__FloatingPointLatticeArray*>(frame->NodeMd)->Offset[0];
			for (ULONG64 inc = 1; inc <= constantArray->Count; ++inc)
				values[inc] = values[0] + (inc * constantArray->Value);
		}
		else {
			throw logic_error("The array structure of MD is not supported?");
		}
	}
	else {
		throw invalid_argument("Not implemented yet");
	}
}

void WellboreFrameRepresentation::getMdAsFloatValues(float* values) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		_resqml20__WellboreFrameRepresentation* frame = static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array)
		{
			eml20__Hdf5Dataset const* dataset = static_cast<resqml20__DoubleHdf5Array*>(frame->NodeMd)->Values;
			COMMON_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The HDF proxy is missing.");
			}
			hdfProxy->readArrayNdOfFloatValues(dataset->PathInHdfFile, values);
		}
		else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
		{
			values[0] = static_cast<resqml20__DoubleLatticeArray*>(frame->NodeMd)->StartValue;
			resqml20__DoubleConstantArray* constantArray = static_cast<resqml20__DoubleLatticeArray*>(frame->NodeMd)->Offset[0];
			for (ULONG64 inc = 1; inc <= constantArray->Count; ++inc)
				values[inc] = values[0] + (inc * constantArray->Value);
		}
		else {
			throw logic_error("The array structure of MD is not supported?");
		}
	}
	else if (gsoapProxy2_2 != nullptr) {
		_resqml22__WellboreFrameRepresentation* frame = static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_2);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__DoubleExternalArray)
		{
			eml22__ExternalDataset const* dataset = static_cast<eml22__DoubleExternalArray*>(frame->NodeMd)->Values;
			COMMON_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->ExternalFileProxy[0]->EpcExternalPartReference->Uuid);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The HDF proxy is missing.");
			}
			hdfProxy->readArrayNdOfFloatValues(dataset->ExternalFileProxy[0]->PathInExternalFile, values);
		}
		else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__FloatingPointLatticeArray)
		{
			values[0] = static_cast<eml22__FloatingPointLatticeArray*>(frame->NodeMd)->StartValue;
			eml22__FloatingPointConstantArray* constantArray = static_cast<eml22__FloatingPointLatticeArray*>(frame->NodeMd)->Offset[0];
			for (ULONG64 inc = 1; inc <= constantArray->Count; ++inc)
				values[inc] = values[0] + (inc * constantArray->Value);
		}
		else {
			throw logic_error("The array structure of MD is not supported?");
		}
	}
	else {
		throw invalid_argument("Not implemented yet");
	}
}

COMMON_NS::DataObjectReference WellboreFrameRepresentation::getWellboreTrajectoryDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return COMMON_NS::DataObjectReference(static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1)->Trajectory);
	}
	else if (gsoapProxy2_2 != nullptr) {
		return COMMON_NS::DataObjectReference(static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_2)->Trajectory);
	}

	throw invalid_argument("Not implemented yet");
}

COMMON_NS::DataObjectReference WellboreFrameRepresentation::getLocalCrsDor(unsigned int patchIndex) const
{
	return getWellboreTrajectory()->getLocalCrsDor(patchIndex);
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
	else if (gsoapProxy2_2 != nullptr) {
		_resqml22__WellboreFrameRepresentation* frame = static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_2);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__FloatingPointExternalArray)
		{
			return COMMON_NS::DataObjectReference(static_cast<eml22__FloatingPointExternalArray*>(frame->NodeMd)->Values->ExternalFileProxy[0]->EpcExternalPartReference);
		}
	}
	else {
		throw invalid_argument("Not implemented yet");
	}

	return COMMON_NS::DataObjectReference();
}

ULONG64 WellboreFrameRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The patch index is out of range");
	}

	return getMdValuesCount();
}

RESQML2_0_1_NS::WellboreTrajectoryRepresentation* WellboreFrameRepresentation::getWellboreTrajectory() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return getRepository()->getDataObjectByUuid<RESQML2_0_1_NS::WellboreTrajectoryRepresentation>(static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1)->Trajectory->UUID);
	}
	else if (gsoapProxy2_2 != nullptr) {
		return getRepository()->getDataObjectByUuid<RESQML2_0_1_NS::WellboreTrajectoryRepresentation>(static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_2)->Trajectory->Uuid);
	}

	throw invalid_argument("Not implemented yet");
}

void WellboreFrameRepresentation::loadTargetRelationships()
{
	AbstractRepresentation::loadTargetRelationships();

	COMMON_NS::DataObjectReference dor = getWellboreTrajectoryDor();
	// todo the trajectory should be resqml2 instead of resqml2_0_1
	RESQML2_0_1_NS::WellboreTrajectoryRepresentation* traj = getRepository()->getDataObjectByUuid<RESQML2_0_1_NS::WellboreTrajectoryRepresentation>(dor.getUuid());
	if (traj == nullptr) { // partial transfer
		getRepository()->createPartial(dor);
		traj = getRepository()->getDataObjectByUuid<RESQML2_0_1_NS::WellboreTrajectoryRepresentation>(dor.getUuid());
	}
	if (traj == nullptr) {
		throw invalid_argument("The DOR looks invalid.");
	}
	repository->addRelationship(this, traj);
}