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

#include "../eml2/GraphicalInformationSet.h"

using namespace std;
using namespace gsoap_eml2_3;
using namespace RESQML2_NS;

void ContinuousColorMap::setHsvColors(unsigned int colorCount,
	double const* hsvColors, double const* alphas, vector<string> const& colorTitles,
	double const* indices)
{
	if (colorCount < 2) {
		throw invalid_argument("At least 2 color must be set.");
	}

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
		continuousColorMapEntry->Index = indices != nullptr ? indices[colorIndex] : colorIndex;
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

uint64_t ContinuousColorMap::getColorCount() const
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
