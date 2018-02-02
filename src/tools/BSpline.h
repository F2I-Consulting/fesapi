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

#include <limits>
#include <vector>

namespace geometry
{
	/**
	* From https://en.wikipedia.org/w/index.php?title=Spline_%28mathematics%29&oldid=288288033#Algorithm_for_computing_natural_cubic_splines
	*/
	class BSpline
	{
	public:
		BSpline() {};
		BSpline(const std::vector<double> & parametersAtControlPoint, const std::vector<double> & valuesAtControlPoint);
		~BSpline() {}

		double getValueFromParameter(const double & param) const;
		void setParameterAndValueAtControlPoint(const std::vector<double> & parametersAtControlPoint, const std::vector<double> & valuesAtControlPoint);

	private:

		void checkIfParametersIncreaseOrDecrease();
		std::size_t getSplineIndexFromParameter(const double & param) const;

		bool areParametersIncreasing;

		// basically each of set of 5 double describe a spline
		std::vector<double> a;
		std::vector<double> b;
		std::vector<double> c;
		std::vector<double> d;
		std::vector<double> parameter; //named x in the wiki link

	};
}

