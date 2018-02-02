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
#include "resqml2_0_1/ContinuousProperty.h"

#include <limits>
#include <sstream>

#include "hdf5.h"

#include "resqml2/AbstractRepresentation.h"
#include "resqml2_0_1/PropertyKind.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

const char* ContinuousProperty::XML_TAG = "ContinuousProperty";

void ContinuousProperty::init(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREContinuousProperty(rep->getGsoapContext(), 1);
	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	setRepresentation(rep);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

ContinuousProperty::ContinuousProperty(resqml2::AbstractRepresentation * rep, const string & guid, const string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const resqml2__ResqmlPropertyKind & energisticsPropertyKind)
{
	init(rep, guid, title, dimension, attachmentKind);

	static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1)->UOM = uom;

	resqml2__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml2__StandardPropertyKind(gsoapProxy2_0_1->soap, 1);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1)->PropertyKind = xmlStandardPropKind;
}

ContinuousProperty::ContinuousProperty(resqml2::AbstractRepresentation * rep, const string & guid, const string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, resqml2::PropertyKind * localPropKind)
{
	init(rep, guid, title, dimension, attachmentKind);

	static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1)->UOM = uom;

	setLocalPropertyKind(localPropKind);
}

ContinuousProperty::ContinuousProperty(resqml2::AbstractRepresentation * rep, const string & guid, const string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const std::string & nonStandardUom, const resqml2__ResqmlPropertyKind & energisticsPropertyKind)
{
	init(rep, guid, title, dimension, attachmentKind);

	static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1)->UOM = gsoap_resqml2_0_1::resqml2__ResqmlUom__Euc;
	pushBackExtraMetadata("Uom", nonStandardUom);

	resqml2__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml2__StandardPropertyKind(gsoapProxy2_0_1->soap, 1);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1)->PropertyKind = xmlStandardPropKind;
}

ContinuousProperty::ContinuousProperty(resqml2::AbstractRepresentation * rep, const string & guid, const string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const std::string & nonStandardUom, resqml2::PropertyKind * localPropKind)
{
	init(rep, guid, title, dimension, attachmentKind);

	static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1)->UOM = gsoap_resqml2_0_1::resqml2__ResqmlUom__Euc;
	pushBackExtraMetadata("Uom", nonStandardUom);

	setLocalPropertyKind(localPropKind);
}

const gsoap_resqml2_0_1::resqml2__ResqmlUom & ContinuousProperty::getUom() const
{
	return static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1)->UOM;
}

std::string ContinuousProperty::getUomAsString() const
{
	return gsoap_resqml2_0_1::soap_resqml2__ResqmlUom2s(gsoapProxy2_0_1->soap, getUom());
}

void ContinuousProperty::pushBackDoubleHdf5Array1dOfValues(double * values, const ULONG64 & valueCount, common::AbstractHdfProxy * proxy,
		const double & minimumValue, const double & maximumValue)
{
	hsize_t valueCountPerDimension[1] = {valueCount};
	if (minimumValue == minimumValue && maximumValue == maximumValue)
	{
		double minimumValuePerDimension[1] = {minimumValue};
		double maximumValuePerDimension[1] = {maximumValue};
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, minimumValuePerDimension, maximumValuePerDimension);
	}
	else
	{
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy);
	}
}

void ContinuousProperty::pushBackDoubleHdf5Array2dOfValues(double * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
			const double & minimumValue, const double & maximumValue)
{
	hsize_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue)
	{
		double minimumValuePerDimension[1] = {minimumValue};
		double maximumValuePerDimension[1] = {maximumValue};
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, minimumValuePerDimension, maximumValuePerDimension);
	}
	else
	{
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy);
	}
}

void ContinuousProperty::pushBackDoubleHdf5Array3dOfValues(double * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
			const double & minimumValue, const double & maximumValue)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue)
	{
		double minimumValuePerDimension[1] = {minimumValue};
		double maximumValuePerDimension[1] = {maximumValue};
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, minimumValuePerDimension, maximumValuePerDimension);
	}
	else
	{
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy);
	}
}

void ContinuousProperty::pushBackDoubleHdf5ArrayOfValues(double * values, hsize_t * numValues, const unsigned int & numArrayDimensions, common::AbstractHdfProxy * proxy,
	double * minimumValue, double * maximumValue)
{
	const string datasetName = pushBackRefToExistingDataset(proxy, "");
	setPropertyMinMax(values, numValues, numArrayDimensions, minimumValue, maximumValue);

	// HDF
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_DOUBLE,
		values,
		numValues, numArrayDimensions);
}

void ContinuousProperty::pushBackFloatHdf5Array1dOfValues(float * values, const ULONG64 & valueCount, common::AbstractHdfProxy * proxy,
	const float & minimumValue, const float & maximumValue)
{
	hsize_t valueCountPerDimension[1] = {valueCount};
	if (minimumValue == minimumValue && maximumValue == maximumValue)
	{
		float minimumValuePerDimension[1] = { minimumValue };
		float maximumValuePerDimension[1] = { maximumValue };
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, minimumValuePerDimension, maximumValuePerDimension);
	}
	else
	{
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy);
	}
}

void ContinuousProperty::pushBackFloatHdf5Array2dOfValues(float * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
	const float & minimumValue, const float & maximumValue)
{
	hsize_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue)
	{
		float minimumValuePerDimension[1] = { minimumValue };
		float maximumValuePerDimension[1] = { maximumValue };
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, minimumValuePerDimension, maximumValuePerDimension);
	}
	else
	{
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy);
	}
}

void ContinuousProperty::pushBackFloatHdf5Array3dOfValues(float * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy,
	const float & minimumValue, const float & maximumValue)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue)
	{
		float minimumValuePerDimension[1] = { minimumValue };
		float maximumValuePerDimension[1] = { maximumValue };
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, minimumValuePerDimension, maximumValuePerDimension);
	}
	else
	{
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy);
	}
}

std::string ContinuousProperty::pushBackRefToExistingDataset(common::AbstractHdfProxy* hdfProxy, const std::string & datasetName, const long & nullValue)
{
	setHdfProxy(hdfProxy);
	gsoap_resqml2_0_1::resqml2__AbstractValuesProperty* prop = static_cast<gsoap_resqml2_0_1::resqml2__AbstractValuesProperty*>(gsoapProxy2_0_1);

	gsoap_resqml2_0_1::resqml2__PatchOfValues* patch = gsoap_resqml2_0_1::soap_new_resqml2__PatchOfValues(gsoapProxy2_0_1->soap, 1);
	patch->RepresentationPatchIndex = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
	*(patch->RepresentationPatchIndex) = prop->PatchOfValues.size();

	// XML
	gsoap_resqml2_0_1::resqml2__DoubleHdf5Array* xmlValues = gsoap_resqml2_0_1::soap_new_resqml2__DoubleHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlValues->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlValues->Values->HdfProxy = hdfProxy->newResqmlReference();

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

void ContinuousProperty::pushBackFloatHdf5ArrayOfValues(
	const ULONG64& valueCountInFastestDim,
	const ULONG64& valueCountInMiddleDim,
	const ULONG64& valueCountInSlowestDim,
	common::AbstractHdfProxy* proxy)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	pushBackFloatHdf5ArrayOfValues(valueCountPerDimension, 3, proxy);
}

void ContinuousProperty::setValuesOfFloatHdf5ArrayOfValues(
	float* values, 
	const ULONG64& valueCountInFastestDim,
	const ULONG64& valueCountInMiddleDim,
	const ULONG64& valueCountInSlowestDim,
	const ULONG64& offsetInFastestDim,
	const ULONG64& offsetInMiddleDim,
	const ULONG64& offsetInSlowestDim,
	common::AbstractHdfProxy* proxy,
	unsigned int patchIndex)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	hsize_t offsetPerDimension[3] = {offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim};
	setValuesOfFloatHdf5ArrayOfValues(
		values, 
		valueCountPerDimension, 
		offsetPerDimension, 
		3, 
		proxy,
		patchIndex
	);
}

void ContinuousProperty::pushBackFloatHdf5ArrayOfValues(float * values, unsigned long long * numValues, const unsigned int & numArrayDimensions, common::AbstractHdfProxy * proxy,
	float * minimumValue, float * maximumValue)
{
	const string datasetName = pushBackRefToExistingDataset(proxy, string());
	setPropertyMinMax(values, numValues, numArrayDimensions, minimumValue, maximumValue);

	// HDF
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_FLOAT,
		values,
		numValues, numArrayDimensions);
}

void ContinuousProperty::pushBackFloatHdf5ArrayOfValues(
	unsigned long long* numValues,
	const unsigned int& numArrayDimensions, 
	common::AbstractHdfProxy* proxy)
{
	const string datasetName = pushBackRefToExistingDataset(proxy, string());

	gsoap_resqml2_0_1::_resqml2__ContinuousProperty* prop = static_cast<gsoap_resqml2_0_1::_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);
	for (ULONG64 i = 0; i < prop->Count; ++i) {
		prop->MinimumValue.push_back(FLT_MAX);
		prop->MaximumValue.push_back(FLT_MIN);
	}

	// HDF
	proxy->createArrayNd(prop->uuid,
		datasetName,
		H5T_NATIVE_FLOAT,
		numValues, numArrayDimensions);
}


void ContinuousProperty::setValuesOfFloatHdf5ArrayOfValues(
	float* values, unsigned long long* numValuesInEachDimension,
	unsigned long long* offsetInEachDimension, const unsigned int& numArrayDimensions,
	common::AbstractHdfProxy* proxy,
	unsigned int patchIndex)
{
	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);

	setPropertyMinMax(
		values,
		numValuesInEachDimension, 
		numArrayDimensions
	);

	ostringstream oss;
	if (patchIndex == (numeric_limits<unsigned int>::max)()) {
		oss << "values_patch" << prop->PatchOfValues.size() - 1;
	}
	else {
		oss << "values_patch" << patchIndex;
	}

	// HDF
	proxy->writeArrayNdSlab(
		prop->uuid,
		oss.str(),
		H5T_NATIVE_FLOAT,
		values,
		numValuesInEachDimension, 
		offsetInEachDimension, 
		numArrayDimensions);
}

void ContinuousProperty::getDoubleValuesOfPatch(const unsigned int & patchIndex, double * values)
{
	common::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr) {
		throw invalid_argument("The hdf proxy does not exist");
	}

	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);
	resqml2__DoubleHdf5Array* hdfValues = static_cast<resqml2__DoubleHdf5Array*>(prop->PatchOfValues[patchIndex]->Values);

	hdfProxy->readArrayNdOfDoubleValues(hdfValues->Values->PathInHdfFile, values);
}

void ContinuousProperty::getFloatValuesOfPatch(const unsigned int & patchIndex, float * values)
{
	common::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr) {
		throw invalid_argument("The hdf proxy does not exist");
	}

	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);
	resqml2__DoubleHdf5Array* hdfValues = static_cast<resqml2__DoubleHdf5Array*>(prop->PatchOfValues[patchIndex]->Values);

	hdfProxy->readArrayNdOfFloatValues(hdfValues->Values->PathInHdfFile, values);
}

void ContinuousProperty::getFloatValuesOfPatch(
	const unsigned int& patchIndex, 
	float* values, 
	unsigned long long* numValuesInEachDimension,
	unsigned long long* offsetInEachDimension,
	const unsigned int& numArrayDimensions)
{
	common::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr) {
		throw invalid_argument("The hdf proxy does not exist");
	}

	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);
	resqml2__DoubleHdf5Array* hdfValues = static_cast<resqml2__DoubleHdf5Array*>(prop->PatchOfValues[patchIndex]->Values);

	hdfProxy->readArrayNdOfFloatValues(
        hdfValues->Values->PathInHdfFile, 
		values, 
		numValuesInEachDimension,
		offsetInEachDimension,
		numArrayDimensions);
}

void ContinuousProperty::getFloatValuesOf3dPatch(
	const unsigned int& patchIndex, 
	float* values, 
	const ULONG64& valueCountInFastestDim,
	const ULONG64& valueCountInMiddleDim,
	const ULONG64& valueCountInSlowestDim,
	const ULONG64& offsetInFastestDim,
	const ULONG64& offsetInMiddleDim,
	const ULONG64& offsetInSlowestDim)
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

double ContinuousProperty::getMinimumValue()
{
	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);

	return prop->MinimumValue.empty() ? std::numeric_limits<double>::quiet_NaN() : prop->MinimumValue[0];
}

double ContinuousProperty::getMaximumValue()
{
	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);

	return prop->MaximumValue.empty() ? std::numeric_limits<double>::quiet_NaN() : prop->MaximumValue[0];
}

bool ContinuousProperty::validatePropertyKindAssociation(resqml2::PropertyKind* pk)
{
	if (pk == nullptr) {
		throw invalid_argument("The property kind to validate cannot be null.");
	}

	if (!pk->isPartial()) {
		if (pk->isAbstract()) {
			epcDocument->addWarning("The continuous property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (epcDocument->getPropertyKindMapper() != nullptr) {
			if (!pk->isChildOf(resqml2__ResqmlPropertyKind__continuous)) {
				epcDocument->addWarning("The continuous property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which does not derive from the continuous standard property kind. This property will be assumed to be a partial one.");
				changeToPartialObject();
				return false;
			}
		}
		else {
			epcDocument->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the continuous property " + getUuid() + " is right because no property kind mapping files have been loaded.");
		}
	}

	return true;
}

bool ContinuousProperty::validatePropertyKindAssociation(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & pk)
{
	PropertyKindMapper* pkMapper = epcDocument->getPropertyKindMapper();
	if (pkMapper != nullptr) {
		if (pkMapper->isAbstract(pk)) {
			epcDocument->addWarning("The continuous property " + getUuid() + " cannot be associated to a resqml property kind \"" + epcDocument->getEnergisticsPropertyKindName(pk) + "\" which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (!pkMapper->isChildOf(pk, resqml2__ResqmlPropertyKind__continuous)) {
			epcDocument->addWarning("The continuous property " + getUuid() + " cannot be associated to a resqml property kind \"" + epcDocument->getEnergisticsPropertyKindName(pk) + "\" which does not derive from the continuous standard property kind. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
	}
	else {
		epcDocument->addWarning("Cannot verify if the resqml property kind \"" + epcDocument->getEnergisticsPropertyKindName(pk) + "\" of the continuous property " + getUuid() + " is right because no property kind mapping files have been loaded.");
	}

	return true;
}

