/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2016)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use,
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
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
