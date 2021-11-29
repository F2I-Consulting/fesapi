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

#include <cstddef>
#include <utility>
#include <stdexcept>

namespace statistics
{
	/**
	 * Finds the minmax of the given arguments
	 *
	 * @exception	std::invalid_argument	Thrown when an invalid argument error condition occurs.
	 *
	 * @tparam	T	Generic type parameter.
	 * @param 	values	  	The values.
	 * @param 	noValue   	The no value.
	 * @param 	valueCount	Number of values.
	 *
	 * @returns	The calculated minimum maximum.
	 */
	template <class T>
	std::pair<T, T> getMinMax(
		const T* values,
		T noValue,
		size_t valueCount)
	{
		if (valueCount == 0) {
			throw std::invalid_argument("You cannot compute min max on an empty array.");
		}

		std::pair<T, T> minMax(noValue, noValue);
		size_t i = 0;
		while (i < valueCount && (values[i] != values[i] || values[i] == noValue)) ++i;
		if (i < valueCount)
		{
			minMax.first = values[i];
			minMax.second = values[i];
		}
		for (; i < valueCount; ++i)
		{
			if (values[i] == values[i] && values[i] != noValue)
			{
				if (values[i] > minMax.second)
					minMax.second = values[i];
				else if (values[i] < minMax.first)
					minMax.first = values[i];
			}
		}

		return minMax;
	}
	
}

