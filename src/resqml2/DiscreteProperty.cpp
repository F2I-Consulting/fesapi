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
#include "DiscreteProperty.h"

#include "../eml2/ColumnBasedTable.h"

#include "../eml2/AbstractHdfProxy.h"

#include "../tools/Statistics.h"

using namespace std;
using namespace RESQML2_NS;

void DiscreteProperty::pushBackInt64Hdf5Array2dOfValues(const int64_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	int64_t nullValue, int64_t minimumValue, int64_t maximumValue)
{
	const uint64_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	pushBackInt64Hdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackIntHdf5Array2dOfValues(const int * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	int nullValue, int minimumValue, int maximumValue)
{
	const uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackShortHdf5Array2dOfValues(const short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	short nullValue, short minimumValue, short maximumValue)
{
	const uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackUShortHdf5Array2dOfValues(const unsigned short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue)
{
	const uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackInt8Hdf5Array2dOfValues(const int8_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	int8_t nullValue, int8_t minimumValue, int8_t maximumValue)
{
	const uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackInt8Hdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackInt64Hdf5Array3dOfValues(const int64_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	int64_t nullValue, int64_t minimumValue, int64_t maximumValue)
{
	const uint64_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	pushBackInt64Hdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackIntHdf5Array3dOfValues(const int * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	int nullValue, int minimumValue, int maximumValue)
{
	const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackShortHdf5Array3dOfValues(const short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	short nullValue, short minimumValue, short maximumValue)
{
	const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackUShortHdf5Array3dOfValues(const unsigned short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue)
{
	const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackInt8Hdf5Array3dOfValues(const int8_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	int8_t nullValue, int8_t minimumValue, int8_t maximumValue)
{
	const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackInt8Hdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackInt64Hdf5ArrayOfValues(const int64_t * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy * proxy, int64_t nullValue)
{
	size_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}
	pair<int64_t, int64_t> minMax = statistics::getMinMax(values, nullValue, numTotalValues);

	pushBackInt64Hdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

void DiscreteProperty::pushBackIntHdf5ArrayOfValues(const int * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int nullValue)
{
	size_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}
	pair<int, int> minMax = statistics::getMinMax(values, nullValue, numTotalValues);

	pushBackIntHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

void DiscreteProperty::pushBackShortHdf5ArrayOfValues(const short * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, short nullValue)
{
	size_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}
	pair<short, short> minMax = statistics::getMinMax(values, nullValue, numTotalValues);

	pushBackShortHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

void DiscreteProperty::pushBackUShortHdf5ArrayOfValues(const unsigned short * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue)
{
	size_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}
	pair<unsigned short, unsigned short> minMax = statistics::getMinMax(values, nullValue, numTotalValues);

	pushBackUShortHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

void DiscreteProperty::pushBackInt8Hdf5ArrayOfValues(const int8_t * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue)
{
	size_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}
	pair<char, char> minMax = statistics::getMinMax(values, nullValue, numTotalValues);

	pushBackInt8Hdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

void DiscreteProperty::pushBackInt64Hdf5ArrayOfValues(const int64_t * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy * proxy,
	int64_t nullValue, int64_t minimumValue, int64_t maximumValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	const std::string datasetName = "values_patch" + std::to_string(getPatchCount());

	proxy->writeArrayNd(getHdfGroup(),
		datasetName,
		COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64,
		values,
		numValues, numDimensionsInArray);

	pushBackRefToExistingIntegerDataset(proxy, getHdfGroup() + "/" + datasetName, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackIntHdf5ArrayOfValues(const int * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int nullValue, int minimumValue, int maximumValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const std::string datasetName = "values_patch" + std::to_string(getPatchCount());

	proxy->writeArrayNd(getHdfGroup(),
		datasetName,
		COMMON_NS::AbstractObject::numericalDatatypeEnum::INT32,
		values,
		numValues, numDimensionsInArray);

	pushBackRefToExistingIntegerDataset(proxy, getHdfGroup() + "/" + datasetName, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackShortHdf5ArrayOfValues(const short * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, short nullValue, short minimumValue, short maximumValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const std::string datasetName = "values_patch" + std::to_string(getPatchCount());

	proxy->writeArrayNd(getHdfGroup(),
		datasetName,
		COMMON_NS::AbstractObject::numericalDatatypeEnum::INT16,
		values,
		numValues, numDimensionsInArray);

	pushBackRefToExistingIntegerDataset(proxy, getHdfGroup() + "/" + datasetName, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackUShortHdf5ArrayOfValues(const unsigned short * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const std::string datasetName = "values_patch" + std::to_string(getPatchCount());

	proxy->writeArrayNd(getHdfGroup(),
		datasetName,
		COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT16,
		values,
		numValues, numDimensionsInArray);

	pushBackRefToExistingIntegerDataset(proxy, getHdfGroup() + "/" + datasetName, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackInt8Hdf5ArrayOfValues(const int8_t * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy,
	int8_t nullValue, int8_t minimumValue, int8_t maximumValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const std::string datasetName = "values_patch" + std::to_string(getPatchCount());

	proxy->writeArrayNd(getHdfGroup(),
		datasetName,
		COMMON_NS::AbstractObject::numericalDatatypeEnum::INT8,
		values,
		numValues, numDimensionsInArray);

	pushBackRefToExistingIntegerDataset(proxy, getHdfGroup() + "/" + datasetName, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::setValuesOfInt64Hdf5Array3dOfValues(
	int64_t* values,
	uint64_t valueCountInFastestDim,
	uint64_t valueCountInMiddleDim,
	uint64_t valueCountInSlowestDim,
	uint64_t offsetInFastestDim,
	uint64_t offsetInMiddleDim,
	uint64_t offsetInSlowestDim,
	bool computeMinMax,
	EML2_NS::AbstractHdfProxy * proxy,
	uint64_t patchIndex)
{
	const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	const uint64_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };
	setValuesOfInt64Hdf5ArrayOfValues(
		values,
		valueCountPerDimension,
		offsetPerDimension,
		3,
		computeMinMax,
		proxy,
		patchIndex
	);
}

void DiscreteProperty::setValuesOfInt32Hdf5Array3dOfValues(
	int32_t* values,
	uint64_t valueCountInFastestDim,
	uint64_t valueCountInMiddleDim,
	uint64_t valueCountInSlowestDim,
	uint64_t offsetInFastestDim,
	uint64_t offsetInMiddleDim,
	uint64_t offsetInSlowestDim,
	bool computeMinMax,
	EML2_NS::AbstractHdfProxy * proxy,
	uint64_t patchIndex)
{
	const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	const uint64_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };
	setValuesOfInt32Hdf5ArrayOfValues(
		values,
		valueCountPerDimension,
		offsetPerDimension,
		3,
		computeMinMax,
		proxy,
		patchIndex
	);
}

void DiscreteProperty::pushBackHdf5ArrayOfValues(
	COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
	const uint64_t* numValues,
	unsigned int numArrayDimensions,
	int64_t* minimumValue, int64_t* maximumValue,
	int64_t nullValue,
	EML2_NS::AbstractHdfProxy* proxy)
{
	if (datatype == COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE ||
		datatype == COMMON_NS::AbstractObject::numericalDatatypeEnum::FLOAT  ||
		datatype == COMMON_NS::AbstractObject::numericalDatatypeEnum::UNKNOWN) {
		throw std::invalid_argument("You cannot pass a non integer datatype as a parameter of this discrete property function.");
	}

	AbstractValuesProperty::pushBackHdf5ArrayOfValues(datatype, numValues, numArrayDimensions, nullValue, proxy);

	if (minimumValue != nullptr && maximumValue != nullptr) {
		const unsigned int elementCount = getElementCountPerValue();
		for (unsigned int propIndex = 0; propIndex < elementCount; ++propIndex) {
			setMinimumValue(getMinimumValueSize() > propIndex 
					? (getMinimumValue(propIndex) > minimumValue[propIndex] ? minimumValue[propIndex] : getMinimumValue(propIndex))
					: minimumValue[propIndex]
				, propIndex);
			setMaximumValue(getMaximumValueSize() > propIndex
					? (getMaximumValue(propIndex) > maximumValue[propIndex] ? maximumValue[propIndex] : getMaximumValue(propIndex))
					: maximumValue[propIndex]
				, propIndex);
		}
	}
}

EML2_NS::ColumnBasedTable* DiscreteProperty::getLookup() const
{
	return getRepository()->getDataObjectByUuid<EML2_NS::ColumnBasedTable>(getLookupDor().getUuid());
}
