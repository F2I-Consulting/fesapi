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
#include "AbstractColorMap.h"

#include "../eml2/GraphicalInformationSet.h"

using namespace std;
using namespace gsoap_eml2_3;
using namespace RESQML2_NS;

void AbstractColorMap::setRgbColors(unsigned int colorCount,
	double const* rgbColors, double const* alphas, vector<string> const& colorTitles,
	double const* indices)
{
	std::unique_ptr<double[]> hsvColors(new double[colorCount * 3]);
	for (size_t colorIndex = 0; colorIndex < colorCount; ++colorIndex) {
		if (rgbColors[3 * colorIndex] < 0 || rgbColors[3 * colorIndex] > 1) {
			throw invalid_argument("red must be in range [0, 1]");
		}

		if (rgbColors[3 * colorIndex + 1] < 0 || rgbColors[3 * colorIndex + 1] > 1) {
			throw invalid_argument("green must be in range [0, 1]");
		}

		if (rgbColors[3 * colorIndex + 2] < 0 || rgbColors[3 * colorIndex + 2] > 1) {
			throw invalid_argument("blue must be in range [0, 1]");
		}

		EML2_NS::GraphicalInformationSet::rgbToHsv(rgbColors[3 * colorIndex], rgbColors[3 * colorIndex + 1], rgbColors[3 * colorIndex + 2],
			hsvColors[3 * colorIndex], hsvColors[3 * colorIndex + 1], hsvColors[3 * colorIndex + 2]);
	}

	setHsvColors(colorCount, hsvColors.get(), alphas, colorTitles, indices);
}

void AbstractColorMap::setRgbColors(unsigned int colorCount,
	unsigned int const* rgbColors, double const* alphas, vector<string> const& colorTitles,
	double const* indices)
{
	std::unique_ptr<double[]> hsvColors(new double[colorCount * 3]);
	for (size_t colorIndex = 0; colorIndex < colorCount; ++colorIndex) {
		if (rgbColors[3 * colorIndex] > 255) {
			throw invalid_argument("red must be in range [0, 255]");
		}

		if (rgbColors[3 * colorIndex + 1] > 255) {
			throw invalid_argument("green must be in range [0, 255]");
		}

		if (rgbColors[3 * colorIndex + 2] > 255) {
			throw invalid_argument("blue must be in range [0, 255]");
		}

		EML2_NS::GraphicalInformationSet::rgbToHsv(rgbColors[3 * colorIndex], rgbColors[3 * colorIndex + 1], rgbColors[3 * colorIndex + 2],
			hsvColors[3 * colorIndex], hsvColors[3 * colorIndex + 1], hsvColors[3 * colorIndex + 2]);
	}

	setHsvColors(colorCount, hsvColors.get(), alphas, colorTitles, indices);
}

double AbstractColorMap::getHue(double colorIndex) const
{
	resqml22__HsvColor const* const color = getColor(colorIndex);
	if (color == nullptr) {
		throw out_of_range("There is no such color index");
	}

	return color->Hue;
}

double AbstractColorMap::getSaturation(double colorIndex) const
{
	resqml22__HsvColor const* const color = getColor(colorIndex);
	if (color == nullptr) {
		throw invalid_argument("There is no such color index");
	}
	return color->Saturation;
}

double AbstractColorMap::getValue(double colorIndex) const
{
	resqml22__HsvColor const* const color = getColor(colorIndex);
	if (color == nullptr) {
		throw invalid_argument("There is no such color index");
	}

	return color->Value;
}

double AbstractColorMap::getAlpha(double colorIndex) const
{
	resqml22__HsvColor const* const color = getColor(colorIndex);
	if (color == nullptr) {
		throw invalid_argument("There is no such color index");
	}

	return color->Alpha;
}

void AbstractColorMap::getRgbColor(double colorIndex, double& red, double& green, double& blue) const
{
	EML2_NS::GraphicalInformationSet::hsvToRgb(getHue(colorIndex), getSaturation(colorIndex), getValue(colorIndex), red, green, blue);
}

void AbstractColorMap::getRgbColor(double colorIndex, unsigned int& red, unsigned int& green, unsigned int& blue) const
{
	EML2_NS::GraphicalInformationSet::hsvToRgb(getHue(colorIndex), getSaturation(colorIndex), getValue(colorIndex), red, green, blue);
}

bool AbstractColorMap::hasColorTitle(double colorIndex) const
{
	resqml22__HsvColor const* const color = getColor(colorIndex);
	if (color == nullptr) {
		throw invalid_argument("There is no such color index");
	}

	return color->Title != nullptr;
}
std::string AbstractColorMap::getColorTitle(double colorIndex) const
{
	resqml22__HsvColor const* const color = getColor(colorIndex);
	if (color == nullptr) {
		throw invalid_argument("There is no such color index");
	}

	if (!hasColorTitle(colorIndex)) {
		throw invalid_argument("This color as no title");
	}

	return *color->Title;
}
