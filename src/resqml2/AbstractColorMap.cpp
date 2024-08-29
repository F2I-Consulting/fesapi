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

void AbstractColorMap::setRgbColors(uint64_t colorCount,
	double const* rgbColors, double const* alphas,
	double const* indices, vector<string> const& colorTitles)
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

	setHsvColors(colorCount, hsvColors.get(), alphas, indices, colorTitles);
}

void AbstractColorMap::setRgbColors(uint64_t colorCount,
	uint8_t const* rgbColors, double const* alphas,
	double const* indices, vector<string> const& colorTitles)
{
	std::unique_ptr<double[]> hsvColors(new double[colorCount * 3]);
	for (size_t colorIndex = 0; colorIndex < colorCount; ++colorIndex) {
		EML2_NS::GraphicalInformationSet::rgbToHsv(rgbColors[3 * colorIndex], rgbColors[3 * colorIndex + 1], rgbColors[3 * colorIndex + 2],
			hsvColors[3 * colorIndex], hsvColors[3 * colorIndex + 1], hsvColors[3 * colorIndex + 2]);
	}

	setHsvColors(colorCount, hsvColors.get(), alphas, indices, colorTitles);
}

double AbstractColorMap::getHue(uint64_t colorIndex) const
{
	resqml22__HsvColor const* const color = getColor(colorIndex);
	if (color == nullptr) {
		throw out_of_range("There is no color index \"" + std::to_string(colorIndex) + "\" in this color map");
	}

	return color->Hue;
}

double AbstractColorMap::getSaturation(uint64_t colorIndex) const
{
	resqml22__HsvColor const* const color = getColor(colorIndex);
	if (color == nullptr) {
		throw invalid_argument("There is no color index \"" + std::to_string(colorIndex) + "\" in this color map");
	}
	return color->Saturation;
}

double AbstractColorMap::getValue(uint64_t colorIndex) const
{
	resqml22__HsvColor const* const color = getColor(colorIndex);
	if (color == nullptr) {
		throw invalid_argument("There is no color index \"" + std::to_string(colorIndex) + "\" in this color map");
	}

	return color->Value;
}

double AbstractColorMap::getAlpha(uint64_t colorIndex) const
{
	resqml22__HsvColor const* const color = getColor(colorIndex);
	if (color == nullptr) {
		throw invalid_argument("There is no color index \"" + std::to_string(colorIndex) + "\" in this color map");
	}

	return color->Alpha;
}

void AbstractColorMap::getRgbColor(uint64_t colorIndex, double& red, double& green, double& blue) const
{
	EML2_NS::GraphicalInformationSet::hsvToRgb(getHue(colorIndex), getSaturation(colorIndex), getValue(colorIndex), red, green, blue);
}

void AbstractColorMap::getRgbColor(uint64_t colorIndex, uint8_t& red, uint8_t& green, uint8_t& blue) const
{
	EML2_NS::GraphicalInformationSet::hsvToRgb(getHue(colorIndex), getSaturation(colorIndex), getValue(colorIndex), red, green, blue);
}

bool AbstractColorMap::hasColorTitle(uint64_t colorIndex) const
{
	resqml22__HsvColor const* const color = getColor(colorIndex);
	if (color == nullptr) {
		throw invalid_argument("There is no color index \"" + std::to_string(colorIndex) + "\" in this color map");
	}

	return color->Title != nullptr;
}
std::string AbstractColorMap::getColorTitle(uint64_t colorIndex) const
{
	resqml22__HsvColor const* const color = getColor(colorIndex);
	if (color == nullptr) {
		throw invalid_argument("There is no color index \"" + std::to_string(colorIndex) + "\" in this color map");
	}

	if (!hasColorTitle(colorIndex)) {
		throw invalid_argument("This color as no title");
	}

	return *color->Title;
}

void AbstractColorMap::setNullHsvColor(double hue, double saturation, double value, double alpha, std::string const& colorTitle)
{
	if (hue < 0 || hue > 360) {
		throw invalid_argument("hue must be in range [0, 360]");
	}

	if (saturation < 0 || saturation > 1) {
		throw invalid_argument("saturation must be in range [0, 1]");
	}

	if (value < 0 || value > 1) {
		throw invalid_argument("value must be in range [0, 1]");
	}

	if (alpha < 0 || alpha > 1) {
		throw invalid_argument("alpha must be in range [0, 1]");
	}

	resqml22__AbstractColorMap* const colorMap = static_cast<resqml22__AbstractColorMap*>(gsoapProxy2_3);

	if (colorMap->NullColor == nullptr) {
		colorMap->NullColor = soap_new_resqml22__HsvColor(gsoapProxy2_3->soap);
	}

	colorMap->NullColor->Hue = hue;
	colorMap->NullColor->Saturation = saturation;
	colorMap->NullColor->Value = value;
	colorMap->NullColor->Alpha = alpha;
	if (!colorTitle.empty()) {
		colorMap->NullColor->Title = soap_new_std__string(gsoapProxy2_3->soap);
		*colorMap->NullColor->Title = colorTitle;
	}
}

void AbstractColorMap::setNullRgbColor(double red, double green, double blue, double alpha, std::string const& colorTitle)
{
	if (red < 0 || red > 1) {
		throw invalid_argument("red must be in range [0, 1]");
	}

	if (green < 0 || green > 1) {
		throw invalid_argument("green must be in range [0, 1]");
	}

	if (blue < 0 || blue > 1) {
		throw invalid_argument("blue must be in range [0, 1]");
	}

	if (alpha < 0 || alpha > 1) {
		throw invalid_argument("alpha must be in range [0, 1]");
	}

	double hue, saturation, value;
	EML2_NS::GraphicalInformationSet::rgbToHsv(red, green, blue, hue, saturation, value);

	setNullHsvColor(hue, saturation, value, alpha, colorTitle);
}

void AbstractColorMap::setNullRgbColor(uint8_t red, uint8_t green, uint8_t blue, double alpha, std::string const& colorTitle)
{
	if (alpha < 0 || alpha > 1) {
		throw invalid_argument("alpha must be in range [0, 1]");
	}

	double hue, saturation, value;
	EML2_NS::GraphicalInformationSet::rgbToHsv(red, green, blue, hue, saturation, value);

	setNullHsvColor(hue, saturation, value, alpha, colorTitle);
}

double AbstractColorMap::getNullHue() const
{
	if (!hasNullColor()) {
		throw out_of_range("There is no Null color in this color map");
	}
	return static_cast<gsoap_eml2_3::resqml22__AbstractColorMap const*>(gsoapProxy2_3)->NullColor->Hue;
}

double AbstractColorMap::getNullSaturation() const
{
	if (!hasNullColor()) {
		throw out_of_range("There is no Null color in this color map");
	}
	return static_cast<gsoap_eml2_3::resqml22__AbstractColorMap const*>(gsoapProxy2_3)->NullColor->Saturation;
}

double AbstractColorMap::getNullValue() const
{
	if (!hasNullColor()) {
		throw out_of_range("There is no Null color in this color map");
	}
	return static_cast<gsoap_eml2_3::resqml22__AbstractColorMap const*>(gsoapProxy2_3)->NullColor->Value;
}

double AbstractColorMap::getNullAlpha() const
{
	if (!hasNullColor()) {
		throw out_of_range("There is no Null color in this color map");
	}
	return static_cast<gsoap_eml2_3::resqml22__AbstractColorMap const*>(gsoapProxy2_3)->NullColor->Alpha;
}

void AbstractColorMap::getNullRgbColor(double& red, double& green, double& blue) const
{
	EML2_NS::GraphicalInformationSet::hsvToRgb(getNullHue(), getNullSaturation(), getNullValue(), red, green, blue);
}

void AbstractColorMap::getNullRgbColor(uint8_t& red, uint8_t& green, uint8_t& blue) const
{
	EML2_NS::GraphicalInformationSet::hsvToRgb(getNullHue(), getNullSaturation(), getNullValue(), red, green, blue);
}
