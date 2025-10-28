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
#pragma once

#if defined(__clang__)
#elif defined(__GNUG__) && __GNUC__ > 12  // https://stackoverflow.com/questions/31509434/gcc-does-not-honor-pragma-gcc-diagnostic-to-silence-warnings
#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#endif
#include "../proxies/gsoap_eml2_3H.h"
#if defined(__clang__)
#elif defined(__GNUG__) && __GNUC__ > 12
#pragma GCC diagnostic pop
#endif

#include "../nsDefinitions.h"

#if defined(_WIN32) && !defined(FESAPI_STATIC)
#if defined(FesapiCpp_EXPORTS) || defined(FesapiCppUnderDev_EXPORTS)
#define DLL_IMPORT_OR_EXPORT __declspec(dllexport)
#else
#define DLL_IMPORT_OR_EXPORT __declspec(dllimport) 
#endif
#else
#define DLL_IMPORT_OR_EXPORT
#endif

#include <map>
#include <type_traits>
#include <vector>

namespace COMMON_NS
{
	template <typename T> class NumberArrayStatistics
	{
        static_assert(std::is_arithmetic_v<T>, "Template parameter T must be an integral or floating-point type.");
        static_assert(!std::is_same_v<T, bool>, "bool is not allowed");
    public:

        NumberArrayStatistics() = default;

        /*
        * Construct statistics by computing them from an array of values
        * 
        * @param 		  	values	                        The array of values which the computation is based on.
        * @param 		  	valueCount	                    The count of values in the array. 
        * @param 		  	valueCountPerIndexableElement	The number of values per indexable element. It is 1 for a scalar property.
        * @param 		  	nullVal			  		        The integer null value. Ignored (fixed to NaN) if it is a floating point value.
        */
        NumberArrayStatistics(T const* values, size_t valueCount, size_t valueCountPerIndexableElement = 1, T nullVal = getDefaultNullValue())
            : nullValue(nullVal)
        {
            computeFrom(values, valueCount, valueCountPerIndexableElement);
        }

        void computeFrom(T const* values, size_t valueCount, size_t valueCountPerIndexableElement) {
            // clear existing values and set the correct dimensions
            validValueCount = std::vector<uint64_t>(valueCountPerIndexableElement);
            minimumValue = std::vector<T>(valueCountPerIndexableElement);
            maximumValue = std::vector<T>(valueCountPerIndexableElement);
            valuesMean = std::vector<double>(valueCountPerIndexableElement);
            valuesMedian = std::vector<double>(valueCountPerIndexableElement);
            valuesMode = std::vector<T>(valueCountPerIndexableElement);
            modePercentage = std::vector<double>(valueCountPerIndexableElement);
            valuesStandardDeviation = std::vector<double>(valueCountPerIndexableElement);

            for (size_t j = 0; j < valueCountPerIndexableElement; ++j) {
                std::map<T, size_t> mapView;
                for (size_t i = j; i < valueCount; i += valueCountPerIndexableElement) {
                    if constexpr (std::is_integral_v<T>) {
                        if (values[i] != nullValue) {
                            ++validValueCount[j];
                            ++mapView[values[i]];
                        }
                    }
                    else {
                        if (!std::isnan(values[i])) {
                            ++validValueCount[j];
                            ++mapView[values[i]];
                        }
                    }
                }
                if (mapView.empty()) {
                    continue;
                }
                minimumValue[j] = mapView.begin()->first;
                maximumValue[j] = mapView.rbegin()->first;

                size_t maxCount = 0;
                size_t mid1 = (validValueCount[j] - 1) / 2;
                size_t mid2 = validValueCount[j] / 2;
                size_t currentCount = 0;
                T median1 = 0, median2 = 0;
                bool found1 = false, found2 = false;
                for (const auto& pair : mapView) {
                    //mode
                    if (pair.second > maxCount) {
                        maxCount = pair.second;
                        valuesMode[j] = pair.first;
                    }

                    //median
                    if (!found2) {
                        currentCount += pair.second;
                        if (!found1 && currentCount > mid1) {
                            median1 = pair.first;
                            found1 = true;
                        }
                        if (currentCount > mid2) {
                            median2 = pair.first;
                            found2 = true;
                        }
                    }

                    //mean
                    valuesMean[j] += (pair.second * pair.first) / validValueCount[j];
                }
                valuesMedian[j] = (validValueCount[j] % 2 == 0) ? (median1 + median2) / 2.0 : median2;
                modePercentage[j] = static_cast<double>(maxCount) / validValueCount[j];


                // Standard Deviation
                double variance = 0.0;
                for (const auto& pair : mapView) {
                    double diff = static_cast<double>(pair.first) - valuesMean[j];
                    variance += pair.second * diff * diff;
                }
                valuesStandardDeviation[j] = std::sqrt(variance / validValueCount[j]);
            }
        }

        T getNullValue() const {
            return nullValue; 
        }

        uint64_t getValidValueCount(size_t valueIndex = 0) const {
            return validValueCount.at(valueIndex);
        }

        uint64_t getValidValueCountSize() const {
            return validValueCount.size();
        }

        T getMinimum(size_t valueIndex = 0) const {
            return minimumValue.at(valueIndex);
        }

        uint64_t getMinimumSize() const {
            return minimumValue.size();
        }

        T getMaximum(size_t valueIndex = 0) const {
            return maximumValue.at(valueIndex);
        }

        uint64_t getMaximumSize() const {
            return maximumValue.size();
        }

        double getMean(size_t valueIndex = 0) const {
            return valuesMean.at(valueIndex);
        }

        uint64_t getMeanSize() const {
            return valuesMean.size();
        }

        double getMedian(size_t valueIndex = 0) const {
            return valuesMedian.at(valueIndex);
        }

        uint64_t getMedianSize() const {
            return valuesMedian.size();
        }

        T getMode(size_t valueIndex = 0) const {
            return valuesMode.at(valueIndex);
        }

        uint64_t getModeSize() const {
            return valuesMode.size();
        }

        double getModePercentage(size_t valueIndex = 0) const {
            return modePercentage.at(valueIndex);
        }

        uint64_t getModePercentageSize() const {
            return modePercentage.size();
        }

        double getStandardDeviation(size_t valueIndex = 0) const {
            return valuesStandardDeviation.at(valueIndex);
        }

        uint64_t getStandardDeviationSize() const {
            return valuesStandardDeviation.size();
        }

        void setNullValue(T value) {
            nullValue = value;
        }

        void setValidValueCount(uint64_t value, size_t valueIndex = 0) {
            while (validValueCount.size() <= valueIndex) {
                validValueCount.push_back((std::numeric_limits<size_t>::max)());
            }
            validValueCount[valueIndex] = value;
        }

        void setMinimum(T value, size_t valueIndex = 0) {
            while (minimumValue.size() <= valueIndex) {
                minimumValue.push_back(getDefaultNullValue());
            }
            minimumValue[valueIndex] = value;
        }

        void setMaximum(T value, size_t valueIndex = 0) {
            while (maximumValue.size() <= valueIndex) {
                maximumValue.push_back(getDefaultNullValue());
            }
            maximumValue[valueIndex] = value;
        }

        void setMean(double value, size_t valueIndex = 0) {
            while (valuesMean.size() <= valueIndex) {
                valuesMean.push_back(std::numeric_limits<double>::quiet_NaN());
            }
            valuesMean[valueIndex] = value;
        }

        void setMedian(double value, size_t valueIndex = 0) {
            while (valuesMedian.size() <= valueIndex) {
                valuesMedian.push_back(std::numeric_limits<double>::quiet_NaN());
            }
            valuesMedian[valueIndex] = value;
        }

        void setMode(T value, size_t valueIndex = 0) {
            while (valuesMode.size() <= valueIndex) {
                valuesMode.push_back(getDefaultNullValue());
            }
            valuesMode[valueIndex] = value;
        }

        void setModePercentage(double value, size_t valueIndex = 0) {
            while (valuesMean.size() <= valueIndex) {
                valuesMean.push_back(std::numeric_limits<double>::quiet_NaN());
            }
            valuesMean[valueIndex] = value;
        }

        void setStandardDeviation(double value, size_t valueIndex = 0) {
            while (valuesStandardDeviation.size() <= valueIndex) {
                valuesStandardDeviation.push_back(std::numeric_limits<double>::quiet_NaN());
            }
            valuesStandardDeviation[valueIndex] = value;
        }

    private:

        T nullValue = getDefaultNullValue();
        std::vector<uint64_t> validValueCount;
        std::vector<T> minimumValue;
        std::vector<T> maximumValue;
        std::vector<double> valuesMean;
        std::vector<double> valuesMedian;
        std::vector<T> valuesMode;
        std::vector<double> modePercentage;
        std::vector<double> valuesStandardDeviation;

        static constexpr T getDefaultNullValue() {
            if constexpr (std::is_floating_point<T>::value) {
                return std::numeric_limits<T>::quiet_NaN();
            }
            else {
                return (std::numeric_limits<T>::max)();
            }
        }
	};
}
