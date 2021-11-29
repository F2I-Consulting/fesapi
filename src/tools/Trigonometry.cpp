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
#include "../tools/Trigonometry.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#include <stdexcept>

using namespace std;

double trigonometry::convertToRadians(const double & angleValue, const gsoap_resqml2_0_1::eml20__PlaneAngleUom & angleUom)
{
	if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::rad)
		return angleValue;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::_0_x002e001_x0020seca)
		return angleValue * M_PI / 648000000;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::ccgr)
		return angleValue * M_PI / 2000000;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::cgr)
		return angleValue * M_PI / 20000;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::dega)
		return angleValue * M_PI / 180;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::gon)
		return angleValue * M_PI / 200;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::krad)
		return angleValue * 1000;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::mila)
		return angleValue * M_PI / 3200;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::mina)
		return angleValue * M_PI / 10800;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::Mrad)
		return angleValue * 1000000;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::mrad)
		return angleValue / 1000;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::rev)
		return angleValue * M_PI * 2;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::seca)
		return angleValue * M_PI / 648000;
	else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::urad)
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
