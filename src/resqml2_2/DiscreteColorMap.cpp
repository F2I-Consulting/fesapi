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
#include "resqml2_2/DiscreteColorMap.h"

#include "common/GraphicalInformationSet.h"

using namespace std;
using namespace gsoap_eml2_2;
using namespace COMMON_NS;
using namespace RESQML2_2_NS;

const char* DiscreteColorMap::XML_TAG = "DiscreteColorMap";

DiscreteColorMap::DiscreteColorMap(COMMON_NS::DataObjectRepository* repo, string const& guid, string const& title)
{
	if (repo == nullptr)
		throw invalid_argument("The repository cannot be null.");

	gsoapProxy2_2 = soap_new_resqml2__DiscreteColorMap(repo->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addOrReplaceDataObject(this);
}

void DiscreteColorMap::setHsvColors(unsigned int colorCount,
	double const* hsvColors, double const* alphas, string const* colorTitles,
	double const* indices)
{
	if (colorCount == 0)
		throw invalid_argument("The color count cannot be 0.");

	resqml2__DiscreteColorMap* const discreteColorMap = static_cast<resqml2__DiscreteColorMap*>(gsoapProxy2_2);

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

		resqml2__DiscreteColorMapEntry* discreteColorMapEntry = soap_new_resqml2__DiscreteColorMapEntry(gsoapProxy2_2->soap, 1);
		indices != nullptr ? discreteColorMapEntry->index = indices[colorIndex] : discreteColorMapEntry->index = colorIndex;
		resqml2__HsvColor* color = soap_new_resqml2__HsvColor(gsoapProxy2_2->soap, 1);
		color->Hue = hsvColors[3 * colorIndex];
		color->Saturation = hsvColors[3 * colorIndex + 1];
		color->Value = hsvColors[3 * colorIndex + 2];
		color->Alpha = alphas != nullptr ? alphas[colorIndex] : 1.0;

		if (colorTitles != nullptr) {
			color->Title = soap_new_std__string(gsoapProxy2_2->soap, 1);
			*color->Title = colorTitles[colorIndex];
		}

		discreteColorMapEntry->Hsv = color;
		discreteColorMap->Entry.push_back(discreteColorMapEntry);
	}
}

unsigned int DiscreteColorMap::getColorCount() const
{
	resqml2__DiscreteColorMap const* const discreteColorMap = static_cast<resqml2__DiscreteColorMap*>(gsoapProxy2_2);
	return discreteColorMap->Entry.size();
}

void DiscreteColorMap::computeMinMax(LONG64& min, LONG64& max) const
{
	resqml2__DiscreteColorMap* discreteColorMap = static_cast<resqml2__DiscreteColorMap*>(gsoapProxy2_2);

	min = discreteColorMap->Entry[0]->index;
	max = min;

	for (size_t colorIndex = 1; colorIndex < discreteColorMap->Entry.size(); ++colorIndex) {
		const LONG64 index = discreteColorMap->Entry[colorIndex]->index;
		if (index < min) {
			min = index;
		}
		else if (index > max) {
			max = index;
		}
	}
}

resqml2__HsvColor* DiscreteColorMap::getColor(double colorIndex) const
{
	resqml2__DiscreteColorMap const* const discreteColorMap = static_cast<resqml2__DiscreteColorMap*>(gsoapProxy2_2);

	for (unsigned int i = 0; i < discreteColorMap->Entry.size(); ++i) {
		if (discreteColorMap->Entry[i]->index == colorIndex) {
			return discreteColorMap->Entry[i]->Hsv;
		}
	}

	return nullptr;
}