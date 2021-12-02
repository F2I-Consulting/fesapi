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

#include <sstream>

#include "Wellbore.h"

#include "../tools/TimeTools.h"

using namespace std;
using namespace WITSML2_0_NS;
using namespace gsoap_eml2_1;

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

void WellboreGeometry::setWellboreGeometrySectionMdInterval(uint64_t index, double top, double base, const std::string & datum, gsoap_eml2_1::eml21__LengthUom uom)
{
	witsml20__WellboreGeometrySection* section = static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.at(index);

	section->SectionMdInterval = soap_new_eml21__MdInterval(gsoapProxy2_1->soap);
	section->SectionMdInterval->datum = datum;
	section->SectionMdInterval->MdTop = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
	section->SectionMdInterval->MdTop->uom = uom;
	section->SectionMdInterval->MdTop->__item = top;
	section->SectionMdInterval->MdBase = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
	section->SectionMdInterval->MdBase->uom = uom;
	section->SectionMdInterval->MdBase->__item = base;
}

double WellboreGeometry::getWellboreGeometrySectionMdIntervalTop(uint64_t index) const
{
	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.at(index)->SectionMdInterval->MdTop->__item;
}

gsoap_eml2_1::eml21__LengthUom WellboreGeometry::getWellboreGeometrySectionMdIntervalTopUom(uint64_t index) const
{
	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.at(index)->SectionMdInterval->MdTop->uom;
}

double WellboreGeometry::getWellboreGeometrySectionMdIntervalBase(uint64_t index) const
{
	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.at(index)->SectionMdInterval->MdBase->__item;
}

gsoap_eml2_1::eml21__LengthUom WellboreGeometry::getWellboreGeometrySectionMdIntervalBaseUom(uint64_t index) const
{
	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.at(index)->SectionMdInterval->MdBase->uom;
}

std::string WellboreGeometry::getWellboreGeometrySectionMdIntervaldatum(uint64_t index) const
{
	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.at(index)->SectionMdInterval->datum;
}

bool WellboreGeometry::hasWellboreGeometrySectionMdInterval(uint64_t index) const
{
	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.at(index)->SectionMdInterval != nullptr;
}

void WellboreGeometry::setWellboreGeometrySectionTvdInterval(uint64_t index, double top, double base, const std::string & datum, gsoap_eml2_1::eml21__LengthUom uom)
{
	witsml20__WellboreGeometrySection* section = static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.at(index);

	section->SectionTvdInterval = soap_new_eml21__TvdInterval(gsoapProxy2_1->soap);
	section->SectionTvdInterval->datum = datum;
	section->SectionTvdInterval->TvdTop = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
	section->SectionTvdInterval->TvdTop->uom = uom;
	section->SectionTvdInterval->TvdTop->__item = top;
	section->SectionTvdInterval->TvdBase = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
	section->SectionTvdInterval->TvdBase->uom = uom;
	section->SectionTvdInterval->TvdBase->__item = base;
}

double WellboreGeometry::getWellboreGeometrySectionTvdIntervalTop(uint64_t index) const
{
	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.at(index)->SectionTvdInterval->TvdTop->__item;
}

gsoap_eml2_1::eml21__LengthUom WellboreGeometry::getWellboreGeometrySectionTvdIntervalTopUom(uint64_t index) const
{
	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.at(index)->SectionTvdInterval->TvdTop->uom;
}

double WellboreGeometry::getWellboreGeometrySectionTvdIntervalBase(uint64_t index) const
{
	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.at(index)->SectionTvdInterval->TvdBase->__item;
}

gsoap_eml2_1::eml21__LengthUom WellboreGeometry::getWellboreGeometrySectionTvdIntervalBaseUom(uint64_t index) const
{
	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.at(index)->SectionTvdInterval->TvdBase->uom;
}

std::string WellboreGeometry::getWellboreGeometrySectionTvdIntervaldatum(uint64_t index) const
{
	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.at(index)->SectionTvdInterval->datum;
}

bool WellboreGeometry::hasWellboreGeometrySectionTvdInterval(uint64_t index) const
{
	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.at(index)->SectionTvdInterval != nullptr;
}

void WellboreGeometry::pushBackSection(const std::string & uid)
{
	static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.push_back(gsoap_eml2_1::soap_new_witsml20__WellboreGeometrySection(gsoapProxy2_1->soap));
	uint64_t index = getSectionCount() - 1;
	setWellboreGeometrySectionuid(index, uid.empty() ? std::to_string(index) : uid);
}

uint64_t WellboreGeometry::getSectionCount() const
{
	return static_cast<witsml20__WellboreGeometry*>(gsoapProxy2_1)->WellboreGeometrySection.size();
}
