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

#include <sstream>
#include <stdexcept>

#include <hdf5.h>

#include "../eml2/AbstractHdfProxy.h"

#include "../tools/Statistics.h"

using namespace std;
using namespace RESQML2_NS;

const char* DiscreteProperty::XML_TAG = "DiscreteProperty";

void DiscreteProperty::pushBackLongHdf5Array1dOfValues(const LONG64 * values, ULONG64 valueCount, EML2_NS::AbstractHdfProxy * proxy,
	LONG64 nullValue, LONG64  minimumValue, LONG64  maximumValue)
{
	hsize_t valueCountPerDimension[1] = {valueCount};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackIntHdf5Array1dOfValues(const int * values, ULONG64 valueCount, EML2_NS::AbstractHdfProxy * proxy,
	int nullValue, int  minimumValue, int  maximumValue)
{
	hsize_t valueCountPerDimension[1] = { valueCount };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackShortHdf5Array1dOfValues(const short * values, ULONG64 valueCount, EML2_NS::AbstractHdfProxy * proxy,
	short nullValue, short  minimumValue, short  maximumValue)
{
	hsize_t valueCountPerDimension[1] = { valueCount };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackCharHdf5Array1dOfValues(const char * values, ULONG64 valueCount, EML2_NS::AbstractHdfProxy * proxy,
	char nullValue, char  minimumValue, char  maximumValue)
{
	hsize_t valueCountPerDimension[1] = { valueCount };
	pushBackCharHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackLongHdf5Array2dOfValues(const LONG64 * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	LONG64 nullValue, LONG64  minimumValue, LONG64  maximumValue)
{
	hsize_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackIntHdf5Array2dOfValues(const int * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	int nullValue, int  minimumValue, int  maximumValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackShortHdf5Array2dOfValues(const short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	short nullValue, short  minimumValue, short  maximumValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackUShortHdf5Array2dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackCharHdf5Array2dOfValues(const char * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	char nullValue, char  minimumValue, char  maximumValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackCharHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackLongHdf5Array3dOfValues(const LONG64 * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	LONG64 nullValue, LONG64 minimumValue, LONG64 maximumValue)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackIntHdf5Array3dOfValues(const int * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	int nullValue, int  minimumValue, int  maximumValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackShortHdf5Array3dOfValues(const short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	short nullValue, short  minimumValue, short  maximumValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackUShortHdf5Array3dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	unsigned short nullValue, unsigned short  minimumValue, unsigned short  maximumValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackCharHdf5Array3dOfValues(const char * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy,
	char nullValue, char  minimumValue, char  maximumValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackCharHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackLongHdf5ArrayOfValues(const LONG64 * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy * proxy, LONG64 nullValue)
{
	size_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}
	pair<LONG64, LONG64> minMax = statistics::getMinMax(values, nullValue, numTotalValues);

	pushBackLongHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

void DiscreteProperty::pushBackIntHdf5ArrayOfValues(const int * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int nullValue)
{
	size_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}
	pair<int, int> minMax = statistics::getMinMax(values, nullValue, numTotalValues);

	pushBackIntHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

void DiscreteProperty::pushBackShortHdf5ArrayOfValues(const short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, short nullValue)
{
	size_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}
	pair<short, short> minMax = statistics::getMinMax(values, nullValue, numTotalValues);

	pushBackShortHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

void DiscreteProperty::pushBackUShortHdf5ArrayOfValues(const unsigned short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue)
{
	size_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}
	pair<unsigned short, unsigned short> minMax = statistics::getMinMax(values, nullValue, numTotalValues);

	pushBackUShortHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

void DiscreteProperty::pushBackCharHdf5ArrayOfValues(const char * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, char nullValue)
{
	size_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; ++dim) {
		numTotalValues *= numValues[dim];
	}
	pair<char, char> minMax = statistics::getMinMax(values, nullValue, numTotalValues);

	pushBackCharHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

void DiscreteProperty::pushBackLongHdf5ArrayOfValues(const LONG64 * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy * proxy,
	LONG64 nullValue, LONG64 minimumValue, LONG64 maximumValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	proxy->writeArrayNd(getHdfGroup(),
		pushBackRefToExistingDataset(proxy, "", nullValue, minimumValue, maximumValue),
		H5T_NATIVE_LLONG,
		values,
		numValues, numDimensionsInArray);
}

void DiscreteProperty::pushBackIntHdf5ArrayOfValues(const int * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int nullValue, int  minimumValue, int  maximumValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	proxy->writeArrayNd(getHdfGroup(),
		pushBackRefToExistingDataset(proxy, "", nullValue, minimumValue, maximumValue),
		H5T_NATIVE_INT,
		values,
		numValues, numDimensionsInArray);
}

void DiscreteProperty::pushBackShortHdf5ArrayOfValues(const short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, short nullValue, short  minimumValue, short  maximumValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	proxy->writeArrayNd(getHdfGroup(),
		pushBackRefToExistingDataset(proxy, "", nullValue, minimumValue, maximumValue),
		H5T_NATIVE_SHORT,
		values,
		numValues, numDimensionsInArray);
}

void DiscreteProperty::pushBackUShortHdf5ArrayOfValues(const unsigned short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue, unsigned short  minimumValue, unsigned short  maximumValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	proxy->writeArrayNd(getHdfGroup(),
		pushBackRefToExistingDataset(proxy, "", nullValue, minimumValue, maximumValue),
		H5T_NATIVE_USHORT,
		values,
		numValues, numDimensionsInArray);
}

void DiscreteProperty::pushBackCharHdf5ArrayOfValues(const char * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, char nullValue, char  minimumValue, char  maximumValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	proxy->writeArrayNd(getHdfGroup(),
		pushBackRefToExistingDataset(proxy, "", nullValue, minimumValue, maximumValue),
		H5T_NATIVE_CHAR,
		values,
		numValues, numDimensionsInArray);
}

void DiscreteProperty::pushBackLongHdf5Array3dOfValues(
	ULONG64 valueCountInFastestDim,
	ULONG64 valueCountInMiddleDim,
	ULONG64 valueCountInSlowestDim,
	LONG64 minimumValue, LONG64 maximumValue,
	LONG64 nullValue,
	EML2_NS::AbstractHdfProxy* proxy)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackLongHdf5ArrayOfValues(valueCountPerDimension, 3, &minimumValue, &maximumValue, nullValue, proxy);
}

void DiscreteProperty::setValuesOfLongHdf5Array3dOfValues(
	LONG64* values,
	ULONG64 valueCountInFastestDim,
	ULONG64 valueCountInMiddleDim,
	ULONG64 valueCountInSlowestDim,
	ULONG64 offsetInFastestDim,
	ULONG64 offsetInMiddleDim,
	ULONG64 offsetInSlowestDim,
	bool computeMinMax,
	EML2_NS::AbstractHdfProxy * proxy,
	unsigned int patchIndex)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	hsize_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };
	setValuesOfLongHdf5ArrayOfValues(
		values,
		valueCountPerDimension,
		offsetPerDimension,
		3,
		computeMinMax,
		proxy,
		patchIndex
	);
}

void DiscreteProperty::pushBackLongHdf5ArrayOfValues(
	hsize_t* numValues,
	unsigned int numArrayDimensions,
	LONG64* minimumValue, LONG64* maximumValue,
	LONG64 nullValue,
	EML2_NS::AbstractHdfProxy* proxy)
{
	pushBackLongHdf5ArrayOfValues(numValues, numArrayDimensions, nullValue, proxy);
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

	if (minimumValue != nullptr && maximumValue != nullptr) {
		const unsigned int elementCount = getElementCountPerValue();
		for (size_t propIndex = 0; propIndex < elementCount; ++propIndex) {
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

void DiscreteProperty::setValuesOfLongHdf5ArrayOfValues(
	LONG64* values, hsize_t const * numValuesInEachDimension,
	hsize_t const * offsetInEachDimension, unsigned int numArrayDimensions,
	bool computeMinMax,
	EML2_NS::AbstractHdfProxy* proxy,
	unsigned int patchIndex)
{
	AbstractDiscreteOrCategoricalProperty::setValuesOfLongHdf5ArrayOfValues(values, numValuesInEachDimension,
		offsetInEachDimension, numArrayDimensions, proxy, patchIndex);

	if (computeMinMax) {
		const unsigned int elementCount = getElementCountPerValue();
		ULONG64 nValues = numValuesInEachDimension[0];
		//If count > 1, the last (fastest) dimension has the number of properties per indexable element of the representation.
		for (unsigned int dim = 1; dim < (elementCount == 1 ? numArrayDimensions : numArrayDimensions - 1); ++dim) {
			nValues *= numValuesInEachDimension[dim];
		}

		while (getMinimumValueSize() < elementCount) {
			setMinimumValue((std::numeric_limits<LONG64>::max)(), getMinimumValueSize());
		}
		while (getMaximumValueSize() < elementCount) {
			setMaximumValue((std::numeric_limits<LONG64>::max)(), getMaximumValueSize());
		}

		LONG64 nullValue = getNullValue(patchIndex);

		for (size_t propIndex = 0; propIndex < elementCount; ++propIndex) {
			for (size_t i = 0; i < nValues; i += elementCount) {
				if (values[i] == nullValue) { continue; }
				if (getMinimumValue(propIndex) > values[i]) {
					setMinimumValue(values[i], propIndex);
				}
				if (getMaximumValue(propIndex) < values[i]) {
					setMaximumValue(values[i], propIndex);
				}
			}
		}
	}
}
