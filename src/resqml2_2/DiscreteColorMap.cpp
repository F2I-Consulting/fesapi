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
using namespace epc;
using namespace common;
using namespace RESQML2_2_NS;

const char* DiscreteColorMap::XML_TAG = "DiscreteColorMap";

DiscreteColorMap::DiscreteColorMap(soap* soapContext, const string& guid, const string& title)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_2 = gsoap_eml2_2::soap_new_resqml2__DiscreteColorMap(soapContext, 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");
}

void DiscreteColorMap::setHsvColors(unsigned int colorCount,
	double const* hsvColors, double const* alphas, string const* colorTitles,
	double const* indices)
{
	if (colorCount == 0)
		throw invalid_argument("The color count cannot be 0.");

	resqml2__DiscreteColorMap* const discreteColorMap = static_cast<resqml2__DiscreteColorMap*>(gsoapProxy2_2);

	for (size_t colorIndex = 0; colorIndex < colorCount; ++colorIndex) {
		if (hsvColors[3 * colorIndex] < 0 || hsvColors[3 * colorIndex] >= 360) {
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
		gsoap_eml2_2::resqml2__HsvColor* color = gsoap_eml2_2::soap_new_resqml2__HsvColor(gsoapProxy2_2->soap, 1);
		color->Hue = hsvColors[3 * colorIndex];
		color->Saturation = hsvColors[3 * colorIndex + 1];
		color->Value = hsvColors[3 * colorIndex + 2];
		color->Alpha = alphas != nullptr ? alphas[colorIndex] : 1.0;

		if (colorTitles != nullptr) {
			color->Title = gsoap_eml2_2::soap_new_std__string(gsoapProxy2_2->soap, 1);
			*color->Title = colorTitles[colorIndex];
		}

		discreteColorMapEntry->Hsv = color;
		discreteColorMap->Entry.push_back(discreteColorMapEntry);
	}
}

void DiscreteColorMap::setRgbColors(unsigned int colorCount,
	double const* rgbColors, double const* alphas, string const* colorTitles,
	double const* indices)
{
	double* hsvColors = new double[((int)colorCount) * 3];
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

		GraphicalInformationSet::rgbToHsv(rgbColors[3 * colorIndex], rgbColors[3 * colorIndex + 1], rgbColors[3 * colorIndex + 2],
			hsvColors[3 * colorIndex], hsvColors[3 * colorIndex + 1], hsvColors[3 * colorIndex + 2]);
	}

	setHsvColors(colorCount, hsvColors, alphas, colorTitles, indices);

	delete[] hsvColors;
}

void DiscreteColorMap::setRgbColors(unsigned int colorCount,
	unsigned int const* rgbColors, double const* alphas, string const* colorTitles,
	double const* indices)
{
	double* hsvColors = new double[((int)colorCount) * 3];
	for (size_t colorIndex = 0; colorIndex < colorCount; ++colorIndex) {
		if (rgbColors[3 * colorIndex] < 0 || rgbColors[3 * colorIndex] > 255) {
			throw invalid_argument("red must be in range [0, 1]");
		}

		if (rgbColors[3 * colorIndex + 1] < 0 || rgbColors[3 * colorIndex + 1] > 255) {
			throw invalid_argument("green must be in range [0, 1]");
		}

		if (rgbColors[3 * colorIndex + 2] < 0 || rgbColors[3 * colorIndex + 2] > 255) {
			throw invalid_argument("blue must be in range [0, 1]");
		}

		// TODO to test
		GraphicalInformationSet::rgbToHsv(rgbColors[3 * colorIndex], rgbColors[3 * colorIndex + 1], rgbColors[3 * colorIndex + 2],
			hsvColors[3 * colorIndex], hsvColors[3 * colorIndex + 1], hsvColors[3 * colorIndex + 2]);
	}

	setHsvColors(colorCount, hsvColors, alphas, colorTitles, indices);

	delete[] hsvColors;
}

unsigned int DiscreteColorMap::getColorCount() const
{
	resqml2__DiscreteColorMap const* const discreteColorMap = static_cast<resqml2__DiscreteColorMap*>(gsoapProxy2_2);
	return discreteColorMap->Entry.size();
}

double DiscreteColorMap::getHue(unsigned int colorIndex) const
{
	resqml2__HsvColor const* const color = getColor(colorIndex);
	if (color == nullptr) {
		throw invalid_argument("There is no such color index");
	}
	
	return color->Hue;
}

double DiscreteColorMap::getSaturation(unsigned int colorIndex) const
{
	resqml2__HsvColor const* const color = getColor(colorIndex);
	if (color == nullptr) {
		throw invalid_argument("There is no such color index");
	}
	return color->Saturation;
}

double DiscreteColorMap::getValue(unsigned int colorIndex) const
{
	resqml2__HsvColor const* const color = getColor(colorIndex);
	if (color == nullptr) {
		throw invalid_argument("There is no such color index");
	}

	return color->Value;
}

double DiscreteColorMap::getAlpha(unsigned int colorIndex) const
{
	resqml2__HsvColor const* const color = getColor(colorIndex);
	if (color == nullptr) {
		throw invalid_argument("There is no such color index");
	}

	return color->Alpha;
}

void DiscreteColorMap::getRgbColor(unsigned int colorIndex, double& red, double& green, double& blue) const
{
	GraphicalInformationSet::hsvToRgb(getHue(colorIndex), getSaturation(colorIndex), getValue(colorIndex), red, green, blue);
}

void DiscreteColorMap::getRgbColor(unsigned int colorIndex, unsigned int& red, unsigned int& green, unsigned int& blue) const
{
	GraphicalInformationSet::hsvToRgb(getHue(colorIndex), getSaturation(colorIndex), getValue(colorIndex), red, green, blue);
}

bool DiscreteColorMap::hasColorTitle(unsigned int colorIndex) const
{
	resqml2__HsvColor const* const color = getColor(colorIndex);
	if (color == nullptr) {
		throw invalid_argument("There is no such color index");
	}
	
	return color->Title != nullptr;
}
std::string DiscreteColorMap::getColorTitle(unsigned int colorIndex) const
{
	resqml2__HsvColor const* const color = getColor(colorIndex);
	if (color == nullptr) {
		throw invalid_argument("There is no such color index");
	}

	if (!hasColorTitle(colorIndex)) {
		throw invalid_argument("This color as no title");
	}

	return *color->Title;
}

vector<Relationship> DiscreteColorMap::getAllSourceRelationships() const
{
	vector<Relationship> result;

	for (size_t i = 0; i < graphicalInformationSetSet.size(); ++i) {
		Relationship rel(graphicalInformationSetSet[i]->getPartNameInEpcDocument(), "", graphicalInformationSetSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

vector<Relationship> DiscreteColorMap::getAllTargetRelationships() const
{
	vector<Relationship> result;
	return result;
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

resqml2__HsvColor* DiscreteColorMap::getColor(unsigned int colorIndex) const
{
	resqml2__DiscreteColorMap const* const discreteColorMap = static_cast<resqml2__DiscreteColorMap*>(gsoapProxy2_2);

	for (unsigned int i = 0; i < discreteColorMap->Entry.size(); ++i) {
		if (discreteColorMap->Entry[i]->index == colorIndex) {
			return discreteColorMap->Entry[i]->Hsv;
		}
	}

	return nullptr;
}