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

#include "../proxies/gsoap_resqml2_0_1Stub.h"

namespace trigonometry
{
	/**
	 * Convert an angle into radians
	 *
	 * @param 	angleValue	The angle value.
	 * @param 	angleUom  	The angle uom.
	 *
	 * @returns	The given data converted to the radians.
	 */
	double convertToRadians(const double & angleValue, const gsoap_resqml2_0_1::eml20__PlaneAngleUom & angleUom);

	/**
	 * From https://fr.wikipedia.org/wiki/Matrice_de_rotation#En_dimension_deux
	 *
	 * @param 	xSource   	Source for the.
	 * @param 	ySource   	Source for the.
	 * @param 	angleValue	A positive value indicates a clockwise rotation.
	 * @param 	angleUom  	The angle uom.
	 *
	 * @returns	A pair of double where the first value is the X coordinate of the rotated point and
	 * 			where the second value is the Y coordinate of the rotated point.
	 */
	std::pair<double, double> rotateXY(const double & xSource, const double & ySource, const double & angleValue, const gsoap_resqml2_0_1::eml20__PlaneAngleUom & angleUom);
}

