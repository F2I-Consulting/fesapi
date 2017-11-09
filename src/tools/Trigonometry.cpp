/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

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
#include "tools/Trigonometry.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#include <stdexcept>

using namespace std;

double trigonometry::convertToRadians(const double & angleValue, const gsoap_resqml2_0_1::eml20__PlaneAngleUom & angleUom)
{
	if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom__rad)
		return angleValue;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom__0_x002e001_x0020seca)
		return angleValue * M_PI / 648000000;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom__ccgr)
		return angleValue * M_PI / 2000000;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom__cgr)
		return angleValue * M_PI / 20000;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom__dega)
		return angleValue * M_PI / 180;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom__gon)
		return angleValue * M_PI / 200;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom__krad)
		return angleValue * 1000;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom__mila)
		return angleValue * M_PI / 3200;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom__mina)
		return angleValue * M_PI / 10800;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom__Mrad)
		return angleValue * 1000000;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom__mrad)
		return angleValue / 1000;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom__rev)
		return angleValue * M_PI * 2;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom__seca)
		return angleValue * M_PI / 648000;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom__urad)
		return angleValue / 1000000;
	else
		throw invalid_argument("The uom of the angle has not been recognized.");
}

std::pair<double, double> trigonometry::rotateXY(const double & xSource, const double & ySource, const double & angleValue, const gsoap_resqml2_0_1::eml20__PlaneAngleUom & angleUom)
{
	double radAngleValue = trigonometry::convertToRadians(angleValue, angleUom);
	std::pair<double, double> result;

	double cosAngle = cos(radAngleValue);
	double sinAngle = sin(radAngleValue);

	result.first = xSource * cosAngle - ySource * sinAngle;
	result.second = xSource * sinAngle + ySource * cosAngle;

	return result;
}
