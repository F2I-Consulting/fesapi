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
