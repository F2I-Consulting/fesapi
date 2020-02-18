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
#include "ContinuousProperty.h"

#include <limits>
#include <sstream>

#include <hdf5.h>

#include "../common/AbstractHdfProxy.h"
#include "../common/EnumStringMapper.h"

#include "../resqml2/AbstractRepresentation.h"
#include "PropertyKind.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* ContinuousProperty::XML_TAG = "ContinuousProperty";

void ContinuousProperty::init(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind)
{
	if (rep == nullptr) {
		throw invalid_argument("The representation of this property values cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREContinuousProperty(rep->getGsoapContext());
	_resqml20__ContinuousProperty* prop = static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setRepresentation(rep);
}

ContinuousProperty::ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, resqml20__ResqmlPropertyKind energisticsPropertyKind)
{
	init(rep, guid, title, dimension, attachmentKind);

	static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1)->UOM = uom;

	resqml20__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml20__StandardPropertyKind(gsoapProxy2_0_1->soap);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1)->PropertyKind = xmlStandardPropKind;
}

ContinuousProperty::ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, COMMON_NS::PropertyKind * localPropKind)
{
	init(rep, guid, title, dimension, attachmentKind);

	static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1)->UOM = uom;

	setLocalPropertyKind(localPropKind);
}

ContinuousProperty::ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind, const std::string & nonStandardUom, resqml20__ResqmlPropertyKind energisticsPropertyKind)
{
	init(rep, guid, title, dimension, attachmentKind);

	static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1)->UOM = gsoap_resqml2_0_1::resqml20__ResqmlUom__Euc;
	pushBackExtraMetadata("Uom", nonStandardUom);

	resqml20__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml20__StandardPropertyKind(gsoapProxy2_0_1->soap);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1)->PropertyKind = xmlStandardPropKind;
}

ContinuousProperty::ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind, const std::string & nonStandardUom, COMMON_NS::PropertyKind * localPropKind)
{
	init(rep, guid, title, dimension, attachmentKind);

	static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1)->UOM = gsoap_resqml2_0_1::resqml20__ResqmlUom__Euc;
	pushBackExtraMetadata("Uom", nonStandardUom);

	setLocalPropertyKind(localPropKind);
}

const gsoap_resqml2_0_1::resqml20__ResqmlUom & ContinuousProperty::getUom() const
{
	return static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1)->UOM;
}

std::string ContinuousProperty::getUomAsString() const
{
	return gsoap_resqml2_0_1::soap_resqml20__ResqmlUom2s(gsoapProxy2_0_1->soap, getUom());
}

void ContinuousProperty::pushBackDoubleHdf5Array1dOfValues(const double * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy,
	double minimumValue, double maximumValue)
{
	const hsize_t valueCountPerDimension = valueCount;
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackDoubleHdf5ArrayOfValues(values, &valueCountPerDimension, 1, proxy, &minimumValue, &maximumValue);
	}
	else {
		pushBackDoubleHdf5ArrayOfValues(values, &valueCountPerDimension, 1, proxy);
	}
}

void ContinuousProperty::pushBackDoubleHdf5Array2dOfValues(const double * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	double minimumValue, double maximumValue)
{
	const hsize_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, &minimumValue, &maximumValue);
	}
	else {
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy);
	}
}

void ContinuousProperty::pushBackDoubleHdf5Array3dOfValues(const double * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	double minimumValue, double maximumValue)
{
	const hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, &minimumValue, &maximumValue);
	}
	else {
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy);
	}
}

void ContinuousProperty::pushBackDoubleHdf5ArrayOfValues(double const * values, unsigned long long const * numValues, unsigned int numArrayDimensions, COMMON_NS::AbstractHdfProxy * proxy,
	double * minimumValue, double * maximumValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const string datasetName = pushBackRefToExistingDataset(proxy, "");
	setPropertyMinMax(values, numValues, numArrayDimensions, minimumValue, maximumValue);

	// HDF
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_DOUBLE,
		values,
		numValues, numArrayDimensions);
}

void ContinuousProperty::pushBackFloatHdf5Array1dOfValues(const float * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy,
	float minimumValue, float maximumValue)
{
	const hsize_t valueCountPerDimension = valueCount;
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackFloatHdf5ArrayOfValues(values, &valueCountPerDimension, 1, proxy, &minimumValue, &maximumValue);
	}
	else {
		pushBackFloatHdf5ArrayOfValues(values, &valueCountPerDimension, 1, proxy);
	}
}

void ContinuousProperty::pushBackFloatHdf5Array2dOfValues(const float * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	float minimumValue, float maximumValue)
{
	const hsize_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, &minimumValue, &maximumValue);
	}
	else {
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy);
	}
}

void ContinuousProperty::pushBackFloatHdf5Array3dOfValues(const float * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy,
	float minimumValue, float maximumValue)
{
	const hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, &minimumValue, &maximumValue);
	}
	else {
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy);
	}
}

std::string ContinuousProperty::pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* proxy, const std::string & datasetName)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);
	gsoap_resqml2_0_1::resqml20__AbstractValuesProperty* prop = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty*>(gsoapProxy2_0_1);

	gsoap_resqml2_0_1::resqml20__PatchOfValues* patch = gsoap_resqml2_0_1::soap_new_resqml20__PatchOfValues(gsoapProxy2_0_1->soap);
	patch->RepresentationPatchIndex = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
	*(patch->RepresentationPatchIndex) = prop->PatchOfValues.size();

	// XML
	gsoap_resqml2_0_1::resqml20__DoubleHdf5Array* xmlValues = gsoap_resqml2_0_1::soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
	xmlValues->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlValues->Values->HdfProxy = proxy->newResqmlReference();

	if (datasetName.empty()) {
		ostringstream ossForHdf;
		ossForHdf << "values_patch" << *(patch->RepresentationPatchIndex);
		xmlValues->Values->PathInHdfFile = "/RESQML/" + prop->uuid + "/" + ossForHdf.str();
	}
	else {
		xmlValues->Values->PathInHdfFile = datasetName;
	}

	patch->Values = xmlValues;

	prop->PatchOfValues.push_back(patch);

	return xmlValues->Values->PathInHdfFile;
}

void ContinuousProperty::pushBackFloatHdf5Array3dOfValues(
	ULONG64 valueCountInFastestDim,
	ULONG64 valueCountInMiddleDim,
	ULONG64 valueCountInSlowestDim,
	COMMON_NS::AbstractHdfProxy* proxy,
	float minimumValue, float maximumValue)
{
	const hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackFloatHdf5ArrayOfValues(valueCountPerDimension, 3, proxy, &minimumValue, &maximumValue);
	}
	else {
		pushBackFloatHdf5ArrayOfValues(valueCountPerDimension, 3, proxy);
	}
}

void ContinuousProperty::setValuesOfFloatHdf5Array3dOfValues(
	float const * values, 
	ULONG64 valueCountInFastestDim,
	ULONG64 valueCountInMiddleDim,
	ULONG64 valueCountInSlowestDim,
	ULONG64 offsetInFastestDim,
	ULONG64 offsetInMiddleDim,
	ULONG64 offsetInSlowestDim,
	bool computeMinMax,
	COMMON_NS::AbstractHdfProxy* proxy,
	unsigned int patchIndex)
{
	const hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	const hsize_t offsetPerDimension[3] = {offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim};
	setValuesOfFloatHdf5ArrayOfValues(
		values, 
		valueCountPerDimension, 
		offsetPerDimension, 
		3,
		computeMinMax,
		proxy,
		patchIndex
	);
}

void ContinuousProperty::pushBackFloatHdf5ArrayOfValues(float const * values, unsigned long long const * numValues, unsigned int numArrayDimensions, COMMON_NS::AbstractHdfProxy * proxy,
	float * minimumValue, float * maximumValue)
{
	if ((minimumValue == nullptr && maximumValue != nullptr) ||
		(minimumValue != nullptr && maximumValue == nullptr)) {
		throw std::invalid_argument("You cannot set the minimum value without the maximum value and viceversa.");
	}

	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const string datasetName = pushBackRefToExistingDataset(proxy, "");
	if (minimumValue != nullptr) { // implies that maximumValue != nullptr as well.
		setPropertyMinMax(values, numValues, numArrayDimensions, minimumValue, maximumValue);
	}

	// HDF
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_FLOAT,
		values,
		numValues, numArrayDimensions);
}

void ContinuousProperty::pushBackFloatHdf5ArrayOfValues(
	unsigned long long const * numValues,
	unsigned int numArrayDimensions, 
	COMMON_NS::AbstractHdfProxy* proxy,
	float * minimumValue, float * maximumValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const string datasetName = pushBackRefToExistingDataset(proxy, "");

	gsoap_resqml2_0_1::_resqml20__ContinuousProperty* prop = static_cast<gsoap_resqml2_0_1::_resqml20__ContinuousProperty*>(gsoapProxy2_0_1);
	if (minimumValue != nullptr && maximumValue != nullptr) {
		setPropertyMinMax((float*)nullptr, numValues, numArrayDimensions, minimumValue, maximumValue);
	}

	// HDF
	proxy->createArrayNd(prop->uuid,
		datasetName,
		H5T_NATIVE_FLOAT,
		numValues, numArrayDimensions);
}

void ContinuousProperty::setValuesOfFloatHdf5ArrayOfValues(
	float const * values, unsigned long long const * numValuesInEachDimension,
	unsigned long long const * offsetInEachDimension, unsigned int numArrayDimensions,
	bool computeMinMax,
	COMMON_NS::AbstractHdfProxy* proxy,
	unsigned int patchIndex)
{
	_resqml20__ContinuousProperty const * prop = static_cast<_resqml20__ContinuousProperty *>(gsoapProxy2_0_1);

	if (computeMinMax) {
		setPropertyMinMax(values, numValuesInEachDimension, numArrayDimensions);
	}

	ostringstream oss;
	oss << "values_patch";
	if (patchIndex == (numeric_limits<unsigned int>::max)()) {
		oss << prop->PatchOfValues.size() - 1;
	}
	else {
		oss << patchIndex;
	}

	// HDF
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	proxy->writeArrayNdSlab(
		prop->uuid,
		oss.str(),
		H5T_NATIVE_FLOAT,
		values,
		numValuesInEachDimension, 
		offsetInEachDimension, 
		numArrayDimensions);
}

void ContinuousProperty::getDoubleValuesOfPatch(unsigned int patchIndex, double * values) const
{
	_resqml20__ContinuousProperty const * prop = static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1);
	eml20__Hdf5Dataset const * dataset = static_cast<resqml20__DoubleHdf5Array*>(prop->PatchOfValues[patchIndex]->Values) ->Values;
	COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);

	hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, values);
}

void ContinuousProperty::getFloatValuesOfPatch(unsigned int patchIndex, float * values) const
{
	_resqml20__ContinuousProperty const * prop = static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1);
	eml20__Hdf5Dataset const * dataset = static_cast<resqml20__DoubleHdf5Array*>(prop->PatchOfValues[patchIndex]->Values)->Values;
	COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);

	hdfProxy->readArrayNdOfFloatValues(dataset->PathInHdfFile, values);
}

void ContinuousProperty::getFloatValuesOfPatch(
	unsigned int patchIndex,
	float* values,
	unsigned long long const * numValuesInEachDimension,
	unsigned long long const * offsetInEachDimension,
	unsigned int numArrayDimensions) const
{
	_resqml20__ContinuousProperty const * prop = static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1);
	eml20__Hdf5Dataset const * dataset = static_cast<resqml20__DoubleHdf5Array*>(prop->PatchOfValues[patchIndex]->Values)->Values;
	COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);

	hdfProxy->readArrayNdOfFloatValues(
		dataset->PathInHdfFile,
		values, 
		numValuesInEachDimension,
		offsetInEachDimension,
		numArrayDimensions);
}

void ContinuousProperty::getFloatValuesOf3dPatch(
	unsigned int patchIndex,
	float* values,
	ULONG64 valueCountInFastestDim,
	ULONG64 valueCountInMiddleDim,
	ULONG64 valueCountInSlowestDim,
	ULONG64 offsetInFastestDim,
	ULONG64 offsetInMiddleDim,
	ULONG64 offsetInSlowestDim) const
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	hsize_t offsetPerDimension[3] = {offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim};

	getFloatValuesOfPatch(
		patchIndex,
		values, 
		valueCountPerDimension, 
		offsetPerDimension, 
		3
	);
}

double ContinuousProperty::getMinimumValue() const
{
	_resqml20__ContinuousProperty* prop = static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1);

	return prop->MinimumValue.empty() ? std::numeric_limits<double>::quiet_NaN() : prop->MinimumValue[0];
}

double ContinuousProperty::getMaximumValue() const
{
	_resqml20__ContinuousProperty* prop = static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1);

	return prop->MaximumValue.empty() ? std::numeric_limits<double>::quiet_NaN() : prop->MaximumValue[0];
}

bool ContinuousProperty::validatePropertyKindAssociation(COMMON_NS::PropertyKind* pk)
{
	if (pk == nullptr) {
		throw invalid_argument("The property kind to validate cannot be null.");
	}

	if (!pk->isPartial()) {
		if (pk->isAbstract()) {
			repository->addWarning("The continuous property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (repository->getPropertyKindMapper() != nullptr) {
			if (pk->isParentPartial()) {
				repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the continuous property " + getUuid() + " is right because one if its parent property kind is abstract.");
				return true;
			}
			if (!pk->isChildOf(resqml20__ResqmlPropertyKind__continuous)) {
				repository->addWarning("The continuous property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which does not derive from the continuous standard property kind. This property will be assumed to be a partial one.");
				changeToPartialObject();
				return false;
			}
		}
		else {
			repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the continuous property " + getUuid() + " is right because no property kind mapping files have been loaded.");
		}
	}
	else {
		repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the continuous property " + getUuid() + " is right because it is abstract.");
	}

	return true;
}

bool ContinuousProperty::validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind pk)
{
	COMMON_NS::EnumStringMapper tmp;
	std::string pkName = tmp.getEnergisticsPropertyKindName(pk);

	PropertyKindMapper* pkMapper = repository->getPropertyKindMapper();
	if (pkMapper != nullptr) {
		if (pkMapper->isAbstract(pk)) {
			repository->addWarning("The continuous property " + getUuid() + " cannot be associated to a resqml property kind \"" + pkName + "\" which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (!pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind__continuous)) {
			repository->addWarning("The continuous property " + getUuid() + " cannot be associated to a resqml property kind \"" + pkName + "\" which does not derive from the continuous standard property kind. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
	}
	else {
		repository->addWarning("Cannot verify if the resqml property kind \"" + pkName + "\" of the continuous property " + getUuid() + " is right because no property kind mapping files have been loaded.");
	}

	return true;
}
