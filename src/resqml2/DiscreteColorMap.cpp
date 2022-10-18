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
#include "DiscreteColorMap.h"

using namespace std;
using namespace gsoap_eml2_3;
using namespace COMMON_NS;
using namespace RESQML2_NS;

const char* DiscreteColorMap::XML_TAG = "DiscreteColorMap";

void DiscreteColorMap::setHsvColors(unsigned int colorCount,
	double const* hsvColors, double const* alphas, vector<string> const& colorTitles,
	double const* indices)
{
	if (colorCount == 0)
		throw invalid_argument("The color count cannot be 0.");

	resqml22__DiscreteColorMap* const discreteColorMap = static_cast<resqml22__DiscreteColorMap*>(gsoapProxy2_3);

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

		resqml22__DiscreteColorMapEntry* discreteColorMapEntry = soap_new_resqml22__DiscreteColorMapEntry(gsoapProxy2_3->soap, 1);
		indices != nullptr ? discreteColorMapEntry->index = indices[colorIndex] : discreteColorMapEntry->index = colorIndex;
		resqml22__HsvColor* color = soap_new_resqml22__HsvColor(gsoapProxy2_3->soap, 1);
		color->Hue = hsvColors[3 * colorIndex];
		color->Saturation = hsvColors[3 * colorIndex + 1];
		color->Value = hsvColors[3 * colorIndex + 2];
		color->Alpha = alphas != nullptr ? alphas[colorIndex] : 1.0;

		if (!colorTitles.empty()) {
			color->Title = soap_new_std__string(gsoapProxy2_3->soap, 1);
			*color->Title = colorTitles[colorIndex];
		}

		discreteColorMapEntry->Hsv = color;
		discreteColorMap->Entry.push_back(discreteColorMapEntry);
	}
}

uint64_t DiscreteColorMap::getColorCount() const
{
	resqml22__DiscreteColorMap const* const discreteColorMap = static_cast<resqml22__DiscreteColorMap*>(gsoapProxy2_3);
	return discreteColorMap->Entry.size();
}

resqml22__HsvColor* DiscreteColorMap::getColor(double colorIndex) const
{
	resqml22__DiscreteColorMap const* const discreteColorMap = static_cast<resqml22__DiscreteColorMap*>(gsoapProxy2_3);

	for (size_t i = 0; i < discreteColorMap->Entry.size(); ++i) {
		if (discreteColorMap->Entry[i]->index == colorIndex) {
			return discreteColorMap->Entry[i]->Hsv;
		}
	}

	return nullptr;
}
