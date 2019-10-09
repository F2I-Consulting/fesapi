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
#include "resqml2/WellboreFrameRepresentation.h"

#include <stdexcept>

#include "hdf5.h"

#include "resqml2/AbstractLocal3dCrs.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_NS;
using namespace gsoap_resqml2_0_1;
using namespace gsoap_eml2_2;

void WellboreFrameRepresentation::getXyzPointsOfPatch(const unsigned int& patchIndex, double* xyzPoints) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index of the patch is not in the allowed range of patch.");

	// TODO: la méthode getPointGeometry2_0_1 lève une exception ou retourne nullptr dans WellboreFrameRepresentation et n'est pas surchargée dans ses classes dérivée
	// je n'ai pas mis à jour cette méthode pour les WellboreFrameRepresentation 2.2
	resqml20__PointGeometry* pointGeom = getPointGeometry2_0_1(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array)
	{
		eml20__Hdf5Dataset const* dataset = static_cast<resqml20__Point3dHdf5Array*>(pointGeom->Points)->Coordinates;
		COMMON_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The HDF proxy is missing.");
		}
		hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, xyzPoints);
	}
	else {
		throw invalid_argument("The geometry of the representation either does not exist or it is not an explicit one.");
	}
}

void WellboreFrameRepresentation::setMdValues(double* mdValues, unsigned int mdValueCount, COMMON_NS::AbstractHdfProxy* proxy)
{
	getRepository()->addRelationship(this, proxy);

	string frameUuid;
#if WITH_EXPERIMENTAL
	if (gsoapProxy2_0_1 != nullptr) {
#endif
		_resqml20__WellboreFrameRepresentation* frame = static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1);
		frameUuid = frame->uuid;

		// XML
		resqml20__DoubleHdf5Array* xmlMdValues = soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
		xmlMdValues->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		xmlMdValues->Values->HdfProxy = proxy->newResqmlReference();
		xmlMdValues->Values->PathInHdfFile = "/RESQML/" + frame->uuid + "/mdValues";

		frame->NodeMd = xmlMdValues;

		frame->NodeCount = mdValueCount;
#if WITH_EXPERIMENTAL
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
		xmlMdValues->Values->ExternalFileProxy[0]->PathInExternalFile = "/RESQML/" + frame->uuid + "/mdValues";
		xmlMdValues->Values->ExternalFileProxy[0]->EpcExternalPartReference = proxy->newEml22Reference();

		frame->NodeMd = xmlMdValues;

		frame->NodeCount = mdValueCount;
	}
	else {
		throw invalid_argument("Not implemented yet");
	}
#endif

	// HDF
	hsize_t dim[] = { mdValueCount };
	proxy->writeArrayNd(frameUuid,
		"mdValues",
		H5T_NATIVE_DOUBLE,
		mdValues,
		dim, 1);
}

void WellboreFrameRepresentation::setMdValues(const double& firstMdValue, const double& incrementMdValue, const unsigned int& mdValueCount)
{
#if WITH_EXPERIMENTAL
	if (gsoapProxy2_0_1 != nullptr) {
#endif
		_resqml20__WellboreFrameRepresentation* frame = static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1);

		// XML
		resqml20__DoubleLatticeArray* xmlMdValues = soap_new_resqml20__DoubleLatticeArray(gsoapProxy2_0_1->soap);
		xmlMdValues->StartValue = firstMdValue;
		xmlMdValues->Offset.push_back(soap_new_resqml20__DoubleConstantArray(gsoapProxy2_0_1->soap, 1));
		xmlMdValues->Offset[0]->Count = mdValueCount - 1;
		xmlMdValues->Offset[0]->Value = incrementMdValue;

		frame->NodeMd = xmlMdValues;

		frame->NodeCount = mdValueCount;
#if WITH_EXPERIMENTAL
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
#endif
}

bool WellboreFrameRepresentation::areMdValuesRegularlySpaced() const
{
#if WITH_EXPERIMENTAL
	if (gsoapProxy2_0_1 != nullptr) {
#endif
		return static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1)->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray;
#if WITH_EXPERIMENTAL
	}
	else if (gsoapProxy2_2 != nullptr) {
		return static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_2)->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__FloatingPointLatticeArray;
	}
	else {
		throw invalid_argument("Not implemented yet");
	}
#endif
}
	
double WellboreFrameRepresentation::getMdConstantIncrementValue() const
{
	if (!areMdValuesRegularlySpaced()) {
		throw invalid_argument("The MD values are not regularly spaced.");
	}

#if WITH_EXPERIMENTAL
	if (gsoapProxy2_0_1 != nullptr) {
#endif
		return static_cast<resqml20__DoubleLatticeArray*>(static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1)->NodeMd)->Offset[0]->Value;
#if WITH_EXPERIMENTAL
	}
	else if (gsoapProxy2_2 != nullptr) {
		return static_cast<eml22__FloatingPointLatticeArray*>(static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_2)->NodeMd)->Offset[0]->Value;
	}
	else {
		throw invalid_argument("Not implemented yet");
	}
#endif
}

double WellboreFrameRepresentation::getMdFirstValue() const
{
#if WITH_EXPERIMENTAL
	if (gsoapProxy2_0_1 != nullptr) {
#endif
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
#if WITH_EXPERIMENTAL
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
	else {
		throw invalid_argument("Not implemented yet");
	}
#endif
}

unsigned int WellboreFrameRepresentation::getMdValuesCount() const
{
#if WITH_EXPERIMENTAL
	if (gsoapProxy2_0_1 != nullptr) {
#endif
		return static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1)->NodeCount;

	}
	else if (gsoapProxy2_2 != nullptr) {
		return static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_2)->NodeCount;
	}
	else {
		throw invalid_argument("Not implemented yet");
	}
}

RESQML2_NS::AbstractValuesProperty::hdfDatatypeEnum WellboreFrameRepresentation::getMdHdfDatatype() const
{
#if WITH_EXPERIMENTAL
	if (gsoapProxy2_0_1 != nullptr) {
#endif
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
			else if (H5Tequal(dt, H5T_NATIVE_LONG) > 0)
				return RESQML2_NS::AbstractValuesProperty::LONG;
			else if (H5Tequal(dt, H5T_NATIVE_ULONG) > 0)
				return RESQML2_NS::AbstractValuesProperty::ULONG;
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
#if WITH_EXPERIMENTAL
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
			else if (H5Tequal(dt, H5T_NATIVE_LONG) > 0)
				return RESQML2_NS::AbstractValuesProperty::LONG;
			else if (H5Tequal(dt, H5T_NATIVE_ULONG) > 0)
				return RESQML2_NS::AbstractValuesProperty::ULONG;
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
	else {
		throw invalid_argument("Not implemented yet");
	}
#endif
}

void WellboreFrameRepresentation::getMdAsDoubleValues(double* values) const
{
#if WITH_EXPERIMENTAL
	if (gsoapProxy2_0_1 != nullptr) {
#endif
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
#if WITH_EXPERIMENTAL
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
#endif
}

void WellboreFrameRepresentation::getMdAsFloatValues(float* values) const
{
#if WITH_EXPERIMENTAL
	if (gsoapProxy2_0_1 != nullptr) {
#endif
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
#if WITH_EXPERIMENTAL
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
#endif
}

std::string WellboreFrameRepresentation::getWellboreTrajectoryUuid() const
{
#if WITH_EXPERIMENTAL
	if (gsoapProxy2_0_1 != nullptr) {
#endif
		return static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1)->Trajectory->UUID;
#if WITH_EXPERIMENTAL
	}
	else if (gsoapProxy2_2 != nullptr) {
		return static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_2)->Trajectory->Uuid;
	}
#endif
}

gsoap_resqml2_0_1::eml20__DataObjectReference* WellboreFrameRepresentation::getLocalCrsDor(unsigned int patchIndex) const
{
	return getWellboreTrajectory()->getLocalCrsDor(patchIndex);
}

gsoap_resqml2_0_1::eml20__DataObjectReference* WellboreFrameRepresentation::getHdfProxyDor() const
{
#if WITH_EXPERIMENTAL
	if (gsoapProxy2_0_1 != nullptr) {
#endif
		_resqml20__WellboreFrameRepresentation* frame = static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array)
		{
			return static_cast<resqml20__DoubleHdf5Array*>(frame->NodeMd)->Values->HdfProxy;
		}
#if WITH_EXPERIMENTAL
	}
	else if (gsoapProxy2_2 != nullptr) {
		_resqml22__WellboreFrameRepresentation* frame = static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_2);
		if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_eml2_2_eml22__DoubleExternalArray)
		{
			// TODO: ici le problème vient du fait que j'ai une référence 22 dans dataset->ExternalFileProxy[0]->EpcExternalPartReference
			eml22__ExternalDataset const* dataset = static_cast<eml22__DoubleExternalArray*>(frame->NodeMd)->Values;
			COMMON_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(dataset->ExternalFileProxy[0]->EpcExternalPartReference->Uuid);
			return hdfProxy->newResqmlReference();
		}
	}
	else {
		throw invalid_argument("Not implemented yet");
	}
#endif

	return nullptr;
}

ULONG64 WellboreFrameRepresentation::getXyzPointCountOfPatch(const unsigned int& patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The patch index is out of range");
	}

	return getMdValuesCount();
}

RESQML2_0_1_NS::WellboreTrajectoryRepresentation* WellboreFrameRepresentation::getWellboreTrajectory() const
{
#if WITH_EXPERIMENTAL
	if (gsoapProxy2_0_1 != nullptr) {
#endif
		return getRepository()->getDataObjectByUuid<RESQML2_0_1_NS::WellboreTrajectoryRepresentation>(static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1)->Trajectory->UUID);
#if WITH_EXPERIMENTAL
	}
	else if (gsoapProxy2_2 != nullptr) {
		return getRepository()->getDataObjectByUuid<RESQML2_0_1_NS::WellboreTrajectoryRepresentation>(static_cast<_resqml22__WellboreFrameRepresentation*>(gsoapProxy2_2)->Trajectory->Uuid);
	}
	else {
		throw invalid_argument("Not implemented yet");
	}
#endif
}