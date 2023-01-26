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

void ContinuousProperty::pushBackDoubleHdf5Array1dOfValues(const double * values, uint64_t valueCount,
	double minimumValue, double maximumValue, EML2_NS::AbstractHdfProxy * proxy)
{
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackDoubleHdf5ArrayOfValues(values, &valueCount, 1, &minimumValue, &maximumValue, proxy);
	}
	else {
		pushBackDoubleHdf5ArrayOfValues(values, &valueCount, 1, nullptr, nullptr, proxy);
	}
}

void ContinuousProperty::pushBackDoubleHdf5Array2dOfValues(const double * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim,
	double minimumValue, double maximumValue, EML2_NS::AbstractHdfProxy * proxy)
{
	const uint64_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 2, &minimumValue, &maximumValue, proxy);
	}
	else {
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 2, nullptr, nullptr, proxy);
	}
}

void ContinuousProperty::pushBackDoubleHdf5Array3dOfValues(const double * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim,
	double minimumValue, double maximumValue, EML2_NS::AbstractHdfProxy * proxy)
{
	const uint64_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 3, &minimumValue, &maximumValue, proxy);
	}
	else {
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 3, nullptr, nullptr, proxy);
	}
}

void ContinuousProperty::pushBackDoubleHdf5ArrayOfValues(double const * values, uint64_t const * numValues, unsigned int numArrayDimensions,
	double * minimumValue, double * maximumValue, EML2_NS::AbstractHdfProxy * proxy)
{
	if ((minimumValue == nullptr && maximumValue != nullptr) ||
		(minimumValue != nullptr && maximumValue == nullptr)) {
		throw std::invalid_argument("You cannot set the minimum value without the maximum value and viceversa.");
	}
	AbstractValuesProperty::pushBackDoubleHdf5ArrayOfValues(values, numValues, numArrayDimensions, proxy);

	setPropertyMinMax(values, numValues, numArrayDimensions, minimumValue, maximumValue);
}

void ContinuousProperty::pushBackFloatHdf5Array1dOfValues(const float * values, uint64_t valueCount,
	float minimumValue, float maximumValue, EML2_NS::AbstractHdfProxy * proxy)
{
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackFloatHdf5ArrayOfValues(values, &valueCount, 1, &minimumValue, &maximumValue, proxy);
	}
	else {
		pushBackFloatHdf5ArrayOfValues(values, &valueCount, 1, nullptr, nullptr, proxy);
	}
}

void ContinuousProperty::pushBackFloatHdf5Array2dOfValues(const float * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim,
	float minimumValue, float maximumValue, EML2_NS::AbstractHdfProxy * proxy)
{
	const uint64_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 2, &minimumValue, &maximumValue, proxy);
	}
	else {
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 2, nullptr, nullptr, proxy);
	}
}

void ContinuousProperty::pushBackFloatHdf5Array3dOfValues(const float * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim,
	float minimumValue, float maximumValue, EML2_NS::AbstractHdfProxy * proxy)
{
	const uint64_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 3, &minimumValue, &maximumValue, proxy);
	}
	else {
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 3, nullptr, nullptr, proxy);
	}
}

void ContinuousProperty::setValuesOfFloatHdf5Array3dOfValues(
	float const * values, 
	uint64_t valueCountInFastestDim,
	uint64_t valueCountInMiddleDim,
	uint64_t valueCountInSlowestDim,
	uint64_t offsetInFastestDim,
	uint64_t offsetInMiddleDim,
	uint64_t offsetInSlowestDim,
	bool computeMinMax,
	EML2_NS::AbstractHdfProxy* proxy,
	uint64_t patchIndex)
{
	const uint64_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	const uint64_t offsetPerDimension[3] = {offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim};
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

void ContinuousProperty::setValuesOfDoubleHdf5Array3dOfValues(
	double const * values, 
	uint64_t valueCountInFastestDim,
	uint64_t valueCountInMiddleDim,
	uint64_t valueCountInSlowestDim,
	uint64_t offsetInFastestDim,
	uint64_t offsetInMiddleDim,
	uint64_t offsetInSlowestDim,
	bool computeMinMax,
	EML2_NS::AbstractHdfProxy* proxy,
	uint64_t patchIndex)
{
	const uint64_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	const uint64_t offsetPerDimension[3] = {offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim};
	setValuesOfDoubleHdf5ArrayOfValues(
		values, 
		valueCountPerDimension, 
		offsetPerDimension, 
		3,
		computeMinMax,
		proxy,
		patchIndex
	);
}

void ContinuousProperty::pushBackFloatHdf5ArrayOfValues(float const * values, uint64_t const * numValues, unsigned int numArrayDimensions,
	float * minimumValue, float * maximumValue, EML2_NS::AbstractHdfProxy * proxy)
{
	if ((minimumValue == nullptr && maximumValue != nullptr) ||
		(minimumValue != nullptr && maximumValue == nullptr)) {
		throw std::invalid_argument("You cannot set the minimum value without the maximum value and viceversa.");
	}
	AbstractValuesProperty::pushBackFloatHdf5ArrayOfValues(values, numValues, numArrayDimensions, proxy);

	setPropertyMinMax(values, numValues, numArrayDimensions, minimumValue, maximumValue);
}

void ContinuousProperty::pushBackHdf5ArrayOfValues(
	COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
	uint64_t const * numValues,
	unsigned int numArrayDimensions,
	double * minimumValue, double * maximumValue,
	EML2_NS::AbstractHdfProxy* proxy)
{
	if (datatype != COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE && datatype != COMMON_NS::AbstractObject::numericalDatatypeEnum::FLOAT) {
		throw std::invalid_argument("You cannot pass a non floating point datatype as a parameter of this continuous property function.");
	}

	AbstractValuesProperty::pushBackHdf5ArrayOfValues(datatype, numValues, numArrayDimensions, -1, proxy); // -1 is ignored

	if (minimumValue != nullptr && maximumValue != nullptr) {
		setPropertyMinMax((double*)nullptr, numValues, numArrayDimensions, minimumValue, maximumValue);
	}
}

void ContinuousProperty::pushBackHdf5Array1dOfValues(
	COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
	uint64_t valueCount,
	double minimumValue, double maximumValue,
	EML2_NS::AbstractHdfProxy* proxy)
{
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackHdf5ArrayOfValues(datatype, &valueCount, 1, &minimumValue, &maximumValue, proxy);
	}
	else {
		pushBackHdf5ArrayOfValues(datatype, &valueCount, 1, nullptr, nullptr, proxy);
	}
}

void ContinuousProperty::pushBackHdf5Array2dOfValues(
	COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
	uint64_t valueCountInFastestDim,
	uint64_t valueCountInSlowestDim,
	double minimumValue, double maximumValue,
	EML2_NS::AbstractHdfProxy* proxy)
{
	const uint64_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackHdf5ArrayOfValues(datatype, valueCountPerDimension, 2, &minimumValue, &maximumValue, proxy);
	}
	else {
		pushBackHdf5ArrayOfValues(datatype, valueCountPerDimension, 2, nullptr, nullptr, proxy);
	}
}

void ContinuousProperty::pushBackHdf5Array3dOfValues(
	COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
	uint64_t valueCountInFastestDim,
	uint64_t valueCountInMiddleDim,
	uint64_t valueCountInSlowestDim,
	double minimumValue, double maximumValue,
	EML2_NS::AbstractHdfProxy* proxy)
{
	const uint64_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue) {
		pushBackHdf5ArrayOfValues(datatype, valueCountPerDimension, 3, &minimumValue, &maximumValue, proxy);
	}
	else {
		pushBackHdf5ArrayOfValues(datatype, valueCountPerDimension, 3, nullptr, nullptr, proxy);
	}
}

void ContinuousProperty::setValuesOfFloatHdf5ArrayOfValues(
	float const * values, uint64_t const * numValuesInEachDimension,
	uint64_t const * offsetInEachDimension, unsigned int numArrayDimensions,
	bool computeMinMax,
	EML2_NS::AbstractHdfProxy* proxy,
	uint64_t patchIndex)
{
	AbstractValuesProperty::setValuesOfFloatHdf5ArrayOfValues(values, numValuesInEachDimension, offsetInEachDimension, numArrayDimensions, proxy, patchIndex);

	if (computeMinMax) {
		setPropertyMinMax(values, numValuesInEachDimension, numArrayDimensions);
	}
}

void ContinuousProperty::setValuesOfDoubleHdf5ArrayOfValues(
	double const * values, uint64_t const * numValuesInEachDimension,
	uint64_t const * offsetInEachDimension, unsigned int numArrayDimensions,
	bool computeMinMax,
	EML2_NS::AbstractHdfProxy* proxy,
	uint64_t patchIndex)
{
	AbstractValuesProperty::setValuesOfDoubleHdf5ArrayOfValues(values, numValuesInEachDimension, offsetInEachDimension, numArrayDimensions, proxy, patchIndex);

	if (computeMinMax) {
		setPropertyMinMax(values, numValuesInEachDimension, numArrayDimensions);
	}
}
