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

#include <hdf5.h>

#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_NS;

const char* ContinuousProperty::XML_TAG = "ContinuousProperty";

void ContinuousProperty::pushBackDoubleHdf5Array1dOfValues(const double * values, ULONG64 valueCount,
	double minimumValue, double maximumValue, EML2_NS::AbstractHdfProxy * proxy)
{
	const hsize_t valueCountPerDimension = valueCount;
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackDoubleHdf5ArrayOfValues(values, &valueCountPerDimension, 1, &minimumValue, &maximumValue, proxy);
	}
	else {
		pushBackDoubleHdf5ArrayOfValues(values, &valueCountPerDimension, 1, nullptr, nullptr, proxy);
	}
}

void ContinuousProperty::pushBackDoubleHdf5Array2dOfValues(const double * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim,
	double minimumValue, double maximumValue, EML2_NS::AbstractHdfProxy * proxy)
{
	const hsize_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 2, &minimumValue, &maximumValue, proxy);
	}
	else {
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 2, nullptr, nullptr, proxy);
	}
}

void ContinuousProperty::pushBackDoubleHdf5Array3dOfValues(const double * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim,
	double minimumValue, double maximumValue, EML2_NS::AbstractHdfProxy * proxy)
{
	const hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 3, &minimumValue, &maximumValue, proxy);
	}
	else {
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 3, nullptr, nullptr, proxy);
	}
}

void ContinuousProperty::pushBackDoubleHdf5ArrayOfValues(double const * values, unsigned long long const * numValues, unsigned int numArrayDimensions,
	double * minimumValue, double * maximumValue, EML2_NS::AbstractHdfProxy * proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const string datasetName = pushBackRefToExistingFloatingPointDataset(proxy, "");
	setPropertyMinMax(values, numValues, numArrayDimensions, minimumValue, maximumValue);

	// HDF
	proxy->writeArrayNd(getHdfGroup(),
		datasetName,
		H5T_NATIVE_DOUBLE,
		values,
		numValues, numArrayDimensions);
}

void ContinuousProperty::pushBackFloatHdf5Array1dOfValues(const float * values, ULONG64 valueCount,
	float minimumValue, float maximumValue, EML2_NS::AbstractHdfProxy * proxy)
{
	const hsize_t valueCountPerDimension = valueCount;
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackFloatHdf5ArrayOfValues(values, &valueCountPerDimension, 1, &minimumValue, &maximumValue, proxy);
	}
	else {
		pushBackFloatHdf5ArrayOfValues(values, &valueCountPerDimension, 1, nullptr, nullptr, proxy);
	}
}

void ContinuousProperty::pushBackFloatHdf5Array2dOfValues(const float * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim,
	float minimumValue, float maximumValue, EML2_NS::AbstractHdfProxy * proxy)
{
	const hsize_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 2, &minimumValue, &maximumValue, proxy);
	}
	else {
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 2, nullptr, nullptr, proxy);
	}
}

void ContinuousProperty::pushBackFloatHdf5Array3dOfValues(const float * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim,
	float minimumValue, float maximumValue, EML2_NS::AbstractHdfProxy * proxy)
{
	const hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 3, &minimumValue, &maximumValue, proxy);
	}
	else {
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 3, nullptr, nullptr, proxy);
	}
}

void ContinuousProperty::pushBackFloatHdf5Array3dOfValues(
	ULONG64 valueCountInFastestDim,
	ULONG64 valueCountInMiddleDim,
	ULONG64 valueCountInSlowestDim,
	float minimumValue, float maximumValue,
	EML2_NS::AbstractHdfProxy* proxy)
{
	const hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackFloatHdf5ArrayOfValues(valueCountPerDimension, 3, &minimumValue, &maximumValue, proxy);
	}
	else {
		pushBackFloatHdf5ArrayOfValues(valueCountPerDimension, 3, nullptr, nullptr, proxy);
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
	EML2_NS::AbstractHdfProxy* proxy,
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

void ContinuousProperty::pushBackFloatHdf5ArrayOfValues(float const * values, unsigned long long const * numValues, unsigned int numArrayDimensions,
	float * minimumValue, float * maximumValue, EML2_NS::AbstractHdfProxy * proxy)
{
	if ((minimumValue == nullptr && maximumValue != nullptr) ||
		(minimumValue != nullptr && maximumValue == nullptr)) {
		throw std::invalid_argument("You cannot set the minimum value without the maximum value and viceversa.");
	}
	AbstractValuesProperty::pushBackFloatHdf5ArrayOfValues(values, numValues, numArrayDimensions, proxy);

	if (minimumValue != nullptr) { // implies that maximumValue != nullptr as well.
		setPropertyMinMax(values, numValues, numArrayDimensions, minimumValue, maximumValue);
	}
}

void ContinuousProperty::pushBackFloatHdf5ArrayOfValues(
	unsigned long long const * numValues,
	unsigned int numArrayDimensions,
	float * minimumValue, float * maximumValue,
	EML2_NS::AbstractHdfProxy* proxy)
{
	AbstractValuesProperty::pushBackFloatHdf5ArrayOfValues(numValues, numArrayDimensions, proxy);

	if (minimumValue != nullptr && maximumValue != nullptr) {
		setPropertyMinMax((float*)nullptr, numValues, numArrayDimensions, minimumValue, maximumValue);
	}
}

void ContinuousProperty::setValuesOfFloatHdf5ArrayOfValues(
	float const * values, unsigned long long const * numValuesInEachDimension,
	unsigned long long const * offsetInEachDimension, unsigned int numArrayDimensions,
	bool computeMinMax,
	EML2_NS::AbstractHdfProxy* proxy,
	unsigned int patchIndex)
{
	AbstractValuesProperty::setValuesOfFloatHdf5ArrayOfValues(values, numValuesInEachDimension, offsetInEachDimension, numArrayDimensions, proxy, patchIndex);

	if (computeMinMax) {
		setPropertyMinMax(values, numValuesInEachDimension, numArrayDimensions);
	}
}
