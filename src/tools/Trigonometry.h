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

#include <math.h>
#include <stdexcept>

#include "../proxies/gsoap_resqml2_0_1Stub.h"

namespace trigonometry
{
	/**
	 * Convert an angle into radians
	 *
	 * @param 	angleValue	The angle value.
	 * @param 	angleUom  	The angle uom.
	 *
	 * @returns	The given data converted to radians.
	 */
	double convertToRadians(double angleValue, gsoap_resqml2_0_1::eml20__PlaneAngleUom angleUom)
	{
		constexpr double PI = 3.141592653589793238463;

		if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::rad)
			return angleValue;
		else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::_0_x002e001_x0020seca)
			return angleValue * PI / 648000000;
		else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::ccgr)
			return angleValue * PI / 2000000;
		else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::cgr)
			return angleValue * PI / 20000;
		else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::dega)
			return angleValue * PI / 180;
		else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::gon)
			return angleValue * PI / 200;
		else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::krad)
			return angleValue * 1000;
		else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::mila)
			return angleValue * PI / 3200;
		else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::mina)
			return angleValue * PI / 10800;
		else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::Mrad)
			return angleValue * 1000000;
		else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::mrad)
			return angleValue / 1000;
		else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::rev)
			return angleValue * PI * 2;
		else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::seca)
			return angleValue * PI / 648000;
		else if (angleUom == gsoap_resqml2_0_1::eml20__PlaneAngleUom::urad)
			return angleValue / 1000000;
		else
			throw std::invalid_argument("The uom of the angle has not been recognized.");
	}

	/**
	 * From https://fr.wikipedia.org/wiki/Matrice_de_rotation#En_dimension_deux
	 *
	 * @param 	xSource   	The X coordinate of the point to rotate.
	 * @param 	ySource   	The Y coordinate of the point to rotate.
	 * @param 	angleValue	The rotation angle value. A positive value indicates a clockwise rotation.
	 * @param 	angleUom  	The rotation angle unit of measure.
	 *
	 * @returns	A pair of double where the first value is the X coordinate of the rotated point and
	 * 			where the second value is the Y coordinate of the rotated point.
	 */
	std::pair<double, double> rotateXY(double xSource, double ySource, double angleValue, gsoap_resqml2_0_1::eml20__PlaneAngleUom angleUom)
	{
		const double radAngleValue = convertToRadians(angleValue, angleUom);
		const double cosAngle = cos(radAngleValue);
		const double sinAngle = sin(radAngleValue);

		return std::pair<double, double>(xSource * cosAngle - ySource * sinAngle, xSource * sinAngle + ySource * cosAngle);
	}
}
