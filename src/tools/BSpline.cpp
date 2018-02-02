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

#include "tools/BSpline.h"

#include <stdexcept>

using namespace std;
using namespace geometry;

/// From  https://en.wikipedia.org/w/index.php?title=Spline_%28mathematics%29&oldid=288288033#Algorithm_for_computing_natural_cubic_splines
BSpline::BSpline(const vector<double> & parametersAtControlPoint, const std::vector<double> & valuesAtControlPoint)
{
	setParameterAndValueAtControlPoint(parametersAtControlPoint, valuesAtControlPoint);
}

void BSpline::setParameterAndValueAtControlPoint(const std::vector<double> & parametersAtControlPoint, const std::vector<double> & valuesAtControlPoint)
{
	a = valuesAtControlPoint;
	parameter = parametersAtControlPoint;

	checkIfParametersIncreaseOrDecrease();

	vector<double> h(parametersAtControlPoint.size() - 1);
	for (size_t i = 0; i < parametersAtControlPoint.size() - 1; ++i) {
		h[i] = parametersAtControlPoint[i + 1] - parametersAtControlPoint[i];
	}

	vector<double> alpha(h.size());
	alpha[0] = numeric_limits<double>::signaling_NaN();
	for (size_t i = 1; i < h.size(); ++i) {
		alpha[i] = 3.0 * (valuesAtControlPoint[i + 1] - valuesAtControlPoint[i]) / h[i] - 3.0 * (valuesAtControlPoint[i] - valuesAtControlPoint[i - 1]) / h[i - 1];
	}

	c.resize(parametersAtControlPoint.size());
	vector<double> l(parametersAtControlPoint.size());
	vector<double> mu(parametersAtControlPoint.size());
	vector<double> z(parametersAtControlPoint.size());
	l[0] = 1;
	mu[0] = 0;
	z[0] = 0;
	for (size_t i = 1; i < h.size(); ++i) {
		l[i] = 2 * (parametersAtControlPoint[i + 1] - parametersAtControlPoint[i - 1]) - h[i - 1] * mu[i - 1];
		mu[i] = h[i] / l[i];
		z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
	}

	l[l.size() - 1] = 1;
	z[z.size() - 1] = 0;
	c[c.size() - 1] = 0;
	b.resize(h.size());
	d.resize(h.size());
	for (int i = h.size()-1; i >= 0; --i) {
		c[i] = z[i] - mu[i] * c[i + 1];
		b[i] = (valuesAtControlPoint[i + 1] - valuesAtControlPoint[i]) / h[i] - h[i] * (c[i + 1] + 2 * c[i]) / 3;
		d[i] = (c[i + 1] - c[i]) / (3 * h[i]);
	}
}

void BSpline::checkIfParametersIncreaseOrDecrease()
{
	if (parameter.empty() || parameter.size() != a.size()) {
		throw invalid_argument("Given parameter or value array are inconsistent.");
	}

	// initialization
	for (size_t i = 0; i < parameter.size() - 1; ++i) {
		if (parameter[i] == parameter[i] &&
			parameter[i + 1] == parameter[i + 1]) {
			if (parameter[i + 1] > parameter[i]) {
				areParametersIncreasing = true;
				break;
			}
			else if (parameter[i + 1] < parameter[i]) {
				areParametersIncreasing = false;
				break;
			}
			else {
				throw invalid_argument("Control points with equal parameter are not supported yet.");
			}
		}
		else {
			throw invalid_argument("Control points with NaN parameter are not supported yet.");
		}
	}

	// Checking
	if (areParametersIncreasing) {
		for (size_t i = 0; i < parameter.size() - 1; ++i) {
			if (parameter[i + 1] <= parameter[i]){
				throw invalid_argument("Control points are not ordered increasingly.");
			}
		}
	}
	else {
		for (size_t i = 0; i < parameter.size() - 1; ++i) {
			if (parameter[i + 1] >= parameter[i]){
				throw invalid_argument("Control points are not ordered decreasingly.");
			}
		}
	}
}

size_t BSpline::getSplineIndexFromParameter(const double & param) const
{
	size_t splineIndex = 0;
	if (areParametersIncreasing) {
		if (param <= parameter[0]) {
			return 0; // extrapolation if param < parameter[0]
		}
		while (splineIndex < parameter.size() && parameter[splineIndex] < param) {
			splineIndex++;
		}
	}
	else {
		if (param >= parameter[0]) {
			return 0; // extrapolation if param < parameter[0]
		}
		while (splineIndex < parameter.size() && parameter[splineIndex] > param) {
			splineIndex++;
		}
	}

	return splineIndex == parameter.size()
		? splineIndex - 2 // extrapolation
		: splineIndex - 1; // interpolation
}

double BSpline::getValueFromParameter(const double & param) const
{
	if (param != param) {
		throw invalid_argument("Cannot return a value for a NaN parameter.");
	}

	const size_t splineIndex = getSplineIndexFromParameter(param);

	const double deltaParam = param - parameter[splineIndex];
	const double deltaParam2 = deltaParam * deltaParam;

	return a[splineIndex] +
		b[splineIndex] * deltaParam +
		c[splineIndex] * deltaParam2 +
		d[splineIndex] * deltaParam2 * deltaParam;
}

