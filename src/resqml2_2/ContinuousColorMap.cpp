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
#include "ContinuousColorMap.h"

#include "../common/GraphicalInformationSet.h"

using namespace std;
using namespace gsoap_eml2_3;
using namespace COMMON_NS;
using namespace RESQML2_2_NS;

const char* ContinuousColorMap::XML_TAG = "ContinuousColorMap";

ContinuousColorMap::ContinuousColorMap(COMMON_NS::DataObjectRepository* repo, string const& guid, string const& title,
	resqml22__InterpolationDomain interpolationDomain, resqml22__InterpolationMethod interpolationMethod)
{
	if (repo == nullptr)
		throw invalid_argument("The repository cannot be null.");

	gsoapProxy2_3 = soap_new_resqml22__ContinuousColorMap(repo->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	resqml22__ContinuousColorMap* continuousColorMap = static_cast<resqml22__ContinuousColorMap*>(gsoapProxy2_3);
	continuousColorMap->InterpolationDomain = interpolationDomain;
	continuousColorMap->InterpolationMethod = interpolationMethod;

	repo->addOrReplaceDataObject(this);
}

void ContinuousColorMap::setHsvColors(unsigned int colorCount,
	double const* hsvColors, double const* alphas, vector<string> const& colorTitles,
	double const* indices)
{
	if (colorCount < 2)
		throw invalid_argument("At least 2 color must be set.");

	resqml22__ContinuousColorMap* const continuousColorMap = static_cast<resqml22__ContinuousColorMap*>(gsoapProxy2_3);

	for (size_t colorIndex = 0; colorIndex < colorCount; ++colorIndex) {
		if (hsvColors[3 * colorIndex] < 0 || hsvColors[3 * colorIndex] > 360) {
			throw invalid_argument("hue must be in range [0, 360]");
		}

		if (hsvColors[3 * colorIndex + 1] < 0 || hsvColors[3 * colorIndex + 1] > 1) {
			throw invalid_argument("saturation must be in range [0, 1]");
		}

		if (hsvColors[3 * colorIndex + 2] < 0 || hsvColors[3 * colorIndex + 2] > 1) {
			throw invalid_argument("value must be in range [0, 1]");
		}

		if (alphas != nullptr && (alphas[colorIndex] < 0 || alphas[colorIndex] > 1)) {
			throw invalid_argument("alpha must be in range [0, 1]");
		}

		resqml22__ContinuousColorMapEntry* continuousColorMapEntry = soap_new_resqml22__ContinuousColorMapEntry(gsoapProxy2_3->soap, 1);
		indices != nullptr ? continuousColorMapEntry->Index = indices[colorIndex] : continuousColorMapEntry->Index = colorIndex;
		resqml22__HsvColor* color = soap_new_resqml22__HsvColor(gsoapProxy2_3->soap, 1);
		color->Hue = hsvColors[3 * colorIndex];
		color->Saturation = hsvColors[3 * colorIndex + 1];
		color->Value = hsvColors[3 * colorIndex + 2];
		color->Alpha = alphas != nullptr ? alphas[colorIndex] : 1.0;

		if (!colorTitles.empty()) {
			color->Title = soap_new_std__string(gsoapProxy2_3->soap, 1);
			*color->Title = colorTitles[colorIndex];
		}

		continuousColorMapEntry->Hsv = color;
		continuousColorMap->Entry.push_back(continuousColorMapEntry);
	}
}

unsigned int ContinuousColorMap::getColorCount() const
{
	resqml22__ContinuousColorMap const* const continuousColorMap = static_cast<resqml22__ContinuousColorMap*>(gsoapProxy2_3);
	return continuousColorMap->Entry.size();
}

resqml22__InterpolationDomain ContinuousColorMap::getInterpolationDomain()
{
	resqml22__ContinuousColorMap const* const continuousColorMap = static_cast<resqml22__ContinuousColorMap*>(gsoapProxy2_3);
	return continuousColorMap->InterpolationDomain;
}

std::string ContinuousColorMap::getInterpolationDomainAsString()
{
	return soap_resqml22__InterpolationDomain2s(gsoapProxy2_3->soap, getInterpolationDomain());
}

resqml22__InterpolationMethod ContinuousColorMap::getInterpolationMethod()
{
	resqml22__ContinuousColorMap const* const continuousColorMap = static_cast<resqml22__ContinuousColorMap*>(gsoapProxy2_3);
	return continuousColorMap->InterpolationMethod;
}

std::string ContinuousColorMap::getInterpolationMethodAsString()
{
	return soap_resqml22__InterpolationMethod2s(gsoapProxy2_3->soap, getInterpolationMethod());
}

void ContinuousColorMap::setNanHsvColor(double hue, double saturation, double value, double alpha, std::string const& colorTitle)
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

	resqml22__ContinuousColorMap * const continuousColorMap = static_cast<resqml22__ContinuousColorMap*>(gsoapProxy2_3);

	if (continuousColorMap->NaNColor == nullptr) {
		continuousColorMap->NaNColor = soap_new_resqml22__HsvColor(gsoapProxy2_3->soap, 1);
	}

	continuousColorMap->NaNColor->Hue = hue;
	continuousColorMap->NaNColor->Saturation = saturation;
	continuousColorMap->NaNColor->Value = value;
	continuousColorMap->NaNColor->Alpha = alpha;
	if (!colorTitle.empty()) {
		continuousColorMap->NaNColor->Title = soap_new_std__string(gsoapProxy2_3->soap, 1);
		*continuousColorMap->NaNColor->Title = colorTitle;
	}
}

void ContinuousColorMap::setNanRgbColor(double red, double green, double blue, double alpha, std::string const& colorTitle)
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
	GraphicalInformationSet::rgbToHsv(red, green, blue, hue, saturation, value);

	setNanHsvColor(hue, saturation, value, alpha, colorTitle);
}

void ContinuousColorMap::setNanRgbColor(unsigned int red, unsigned int green, unsigned int blue, double alpha, std::string const& colorTitle)
{
	if (red > 255) {
		 throw invalid_argument("red must be in range [0, 255]");
	}

	if (green > 255) {
		throw invalid_argument("green must be in range [0, 255]");
	}

	if (blue > 255) {
		throw invalid_argument("blue must be in range [0, 255]");
	}

	if (alpha < 0 || alpha > 255) {
		throw invalid_argument("alpha must be in range [0, 255]");
	}

	double hue, saturation, value;
	GraphicalInformationSet::rgbToHsv(red, green, blue, hue, saturation, value);

	setNanHsvColor(hue, saturation, value, alpha, colorTitle);
}

resqml22__HsvColor* ContinuousColorMap::getColor(double colorIndex) const
{
	resqml22__ContinuousColorMap const* const continuousColorMap = static_cast<resqml22__ContinuousColorMap*>(gsoapProxy2_3);

	for (size_t i = 0; i < continuousColorMap->Entry.size(); ++i) {
		if (continuousColorMap->Entry[i]->Index == colorIndex) {
			return continuousColorMap->Entry[i]->Hsv;
		}
	}

	return nullptr;
}
