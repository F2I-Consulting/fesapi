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
#include "WellboreGeometry.h"

#include <limits>
#include <sstream>
#include <stdexcept>

#include "Wellbore.h"

#include "../tools/TimeTools.h"

using namespace std;
using namespace WITSML2_0_NS;
using namespace gsoap_eml2_1;

const char* WellboreGeometry::XML_TAG = "WellboreGeometry";

WellboreGeometry::WellboreGeometry(WITSML2_NS::Wellbore* witsmlWellbore,
	const std::string & guid,
	const std::string & title,
	gsoap_eml2_1::witsml20__ChannelStatus channelStatus)
{
	if (witsmlWellbore == nullptr) throw invalid_argument("A wellbore must be associated to a wellbore geometry.");

	gsoapProxy2_1 = soap_new_witsml20__WellboreGeometry(witsmlWellbore->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->GrowingStatus = channelStatus;

	witsmlWellbore->getRepository()->addDataObject(this);
	setWellbore(witsmlWellbore);
}

COMMON_NS::DataObjectReference WellboreGeometry::getWellboreDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->Wellbore);
}

void WellboreGeometry::setWellbore(WITSML2_NS::Wellbore* witsmlWellbore)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("Cannot set a null witsml wellbore to a witsml trajectory");
	}

	static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->Wellbore = witsmlWellbore->newEmlReference();

	getRepository()->addRelationship(this, witsmlWellbore);
}

GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(WellboreGeometry, MdBase, gsoap_eml2_1::eml21__LengthUom, gsoap_eml2_1::soap_new_witsml20__MeasuredDepthCoord)

GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(WellboreGeometry, GapAir, gsoap_eml2_1::eml21__LengthUom, gsoap_eml2_1::soap_eml21__LengthUom2s, gsoap_eml2_1::soap_new_eml21__LengthMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(WellboreGeometry, DepthWaterMean, gsoap_eml2_1::eml21__LengthUom, gsoap_eml2_1::soap_eml21__LengthUom2s, gsoap_eml2_1::soap_new_eml21__LengthMeasure)

//***************************************
//************** SECTION ****************
//***************************************

// Mandatory
GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR_IMPL(std::string, WellboreGeometry, WellboreGeometrySection, uid)

// Optional bool
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, WellboreGeometry, WellboreGeometrySection, CurveConductor, gsoap_eml2_1::soap_new_bool)

// Optional double
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(double, WellboreGeometry, WellboreGeometrySection, FactFric, gsoap_eml2_1::soap_new_double)

// Optional string
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(std::string, WellboreGeometry, WellboreGeometrySection, Grade, gsoap_eml2_1::soap_new_std__string)

// Optional enum
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(gsoap_eml2_1::witsml20__HoleCasingType, WellboreGeometry, WellboreGeometrySection, TypeHoleCasing, gsoap_eml2_1::soap_new_witsml20__HoleCasingType)

// Optional Length Measure
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(WellboreGeometry, WellboreGeometrySection, IdSection, gsoap_eml2_1::eml21__LengthUom, gsoap_eml2_1::soap_new_eml21__LengthMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(WellboreGeometry, WellboreGeometrySection, OdSection, gsoap_eml2_1::eml21__LengthUom, gsoap_eml2_1::soap_new_eml21__LengthMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(WellboreGeometry, WellboreGeometrySection, DiaDrift, gsoap_eml2_1::eml21__LengthUom, gsoap_eml2_1::soap_new_eml21__LengthMeasure)

// Optional Mass per Length Measure
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(WellboreGeometry, WellboreGeometrySection, WtPerLen, gsoap_eml2_1::eml21__MassPerLengthUom, gsoap_eml2_1::soap_new_eml21__MassPerLengthMeasure)

void WellboreGeometry::setWellboreGeometrySectionMdInterval(unsigned int index, double top, double base, const std::string & datum, gsoap_eml2_1::eml21__LengthUom uom)
{
	if (index >= static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.size()) { throw std::range_error("The index is out of range"); }
	witsml20__WellboreGeometrySection* section = static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection[index];

	section->SectionMdInterval = soap_new_eml21__MdInterval(gsoapProxy2_1->soap);
	section->SectionMdInterval->datum = datum;
	section->SectionMdInterval->MdTop = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
	section->SectionMdInterval->MdTop->uom = uom;
	section->SectionMdInterval->MdTop->__item = top;
	section->SectionMdInterval->MdBase = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
	section->SectionMdInterval->MdBase->uom = uom;
	section->SectionMdInterval->MdBase->__item = base;
}

double WellboreGeometry::getWellboreGeometrySectionMdIntervalTop(unsigned int index) const
{
	if (index >= static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.size()) { throw std::range_error("The index is out of range"); }

	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection[index]->SectionMdInterval->MdTop->__item;
}

gsoap_eml2_1::eml21__LengthUom WellboreGeometry::getWellboreGeometrySectionMdIntervalTopUom(unsigned int index) const
{
	if (index >= static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.size()) { throw std::range_error("The index is out of range"); }

	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection[index]->SectionMdInterval->MdTop->uom;
}

double WellboreGeometry::getWellboreGeometrySectionMdIntervalBase(unsigned int index) const
{
	if (index >= static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.size()) { throw std::range_error("The index is out of range"); }

	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection[index]->SectionMdInterval->MdBase->__item;
}

gsoap_eml2_1::eml21__LengthUom WellboreGeometry::getWellboreGeometrySectionMdIntervalBaseUom(unsigned int index) const
{
	if (index >= static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.size()) { throw std::range_error("The index is out of range"); }

	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection[index]->SectionMdInterval->MdBase->uom;
}

std::string WellboreGeometry::getWellboreGeometrySectionMdIntervaldatum(unsigned int index) const
{
	if (index >= static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.size()) { throw std::range_error("The index is out of range"); }

	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection[index]->SectionMdInterval->datum;
}

bool WellboreGeometry::hasWellboreGeometrySectionMdInterval(unsigned int index) const
{
	if (index >= static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.size()) { throw std::range_error("The index is out of range"); }

	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection[index]->SectionMdInterval != nullptr;
}

void WellboreGeometry::setWellboreGeometrySectionTvdInterval(unsigned int index, double top, double base, const std::string & datum, gsoap_eml2_1::eml21__LengthUom uom)
{
	if (index >= static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.size()) { throw std::range_error("The index is out of range"); }
	witsml20__WellboreGeometrySection* section = static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection[index];

	section->SectionTvdInterval = soap_new_eml21__TvdInterval(gsoapProxy2_1->soap);
	section->SectionTvdInterval->datum = datum;
	section->SectionTvdInterval->TvdTop = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
	section->SectionTvdInterval->TvdTop->uom = uom;
	section->SectionTvdInterval->TvdTop->__item = top;
	section->SectionTvdInterval->TvdBase = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
	section->SectionTvdInterval->TvdBase->uom = uom;
	section->SectionTvdInterval->TvdBase->__item = base;
}

double WellboreGeometry::getWellboreGeometrySectionTvdIntervalTop(unsigned int index) const
{
	if (index >= static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.size()) { throw std::range_error("The index is out of range"); }

	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection[index]->SectionTvdInterval->TvdTop->__item;
}

gsoap_eml2_1::eml21__LengthUom WellboreGeometry::getWellboreGeometrySectionTvdIntervalTopUom(unsigned int index) const
{
	if (index >= static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.size()) { throw std::range_error("The index is out of range"); }

	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection[index]->SectionTvdInterval->TvdTop->uom;
}

double WellboreGeometry::getWellboreGeometrySectionTvdIntervalBase(unsigned int index) const
{
	if (index >= static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.size()) { throw std::range_error("The index is out of range"); }

return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection[index]->SectionTvdInterval->TvdBase->__item;
}

gsoap_eml2_1::eml21__LengthUom WellboreGeometry::getWellboreGeometrySectionTvdIntervalBaseUom(unsigned int index) const
{
	if (index >= static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.size()) { throw std::range_error("The index is out of range"); }

	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection[index]->SectionTvdInterval->TvdBase->uom;
}

std::string WellboreGeometry::getWellboreGeometrySectionTvdIntervaldatum(unsigned int index) const
{
	if (index >= static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.size()) { throw std::range_error("The index is out of range"); }

	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection[index]->SectionTvdInterval->datum;
}

bool WellboreGeometry::hasWellboreGeometrySectionTvdInterval(unsigned int index) const
{
	if (index >= static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.size()) { throw std::range_error("The index is out of range"); }

	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection[index]->SectionTvdInterval != nullptr;
}

void WellboreGeometry::pushBackSection(const std::string & uid)
{
	static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.push_back(gsoap_eml2_1::soap_new_witsml20__WellboreGeometrySection(gsoapProxy2_1->soap, 1));
	unsigned int index = getSectionCount() - 1;
	if (uid.empty()) {
		std::ostringstream oss;
		oss << index;
		setWellboreGeometrySectionuid(index, oss.str());
	}
	else {
		setWellboreGeometrySectionuid(index, uid);
	}
}

unsigned int WellboreGeometry::getSectionCount() const
{
	const size_t count = static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.size();
	if (count >= (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("Too much sections");
	}

	return static_cast<unsigned int>(count);
}
