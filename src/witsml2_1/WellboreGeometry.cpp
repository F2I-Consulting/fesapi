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
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_3;

WellboreGeometry::WellboreGeometry(WITSML2_NS::Wellbore* witsmlWellbore,
	const std::string & guid,
	const std::string & title,
	bool isActive)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("A wellbore must be associated to a wellbore geometry.");
	}

	gsoapProxy2_3 = soap_new_witsml21__WellboreGeometry(witsmlWellbore->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->ActiveStatus = isActive ? eml23__ActiveStatusKind::active : eml23__ActiveStatusKind::inactive;

	// Abstract MD Growing Object
	static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->Index = soap_new_eml23__GrowingObjectIndex(witsmlWellbore->getGsoapContext());
	static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->Index->IndexKind = eml23__DataIndexKind::measured_x0020depth;
	static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->Index->Direction = eml23__IndexDirection::increasing;
	static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->Index->Uom = "Euc"; //TODO

	witsmlWellbore->getRepository()->addDataObject(this);
	setWellbore(witsmlWellbore);
}

COMMON_NS::DataObjectReference WellboreGeometry::getWellboreDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->Wellbore);
}

void WellboreGeometry::setWellbore(WITSML2_NS::Wellbore* witsmlWellbore)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("Cannot set a null witsml wellbore to a witsml trajectory");
	}

	static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->Wellbore = witsmlWellbore->newEml23Reference();

	getRepository()->addRelationship(this, witsmlWellbore);
}

//***************************************
//************** SECTION ****************
//***************************************

// Mandatory
GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR_IMPL(std::string, WellboreGeometry, WellboreGeometrySection, uid)
GETTER_AND_SETTER_TIME_T_ATTRIBUTE_IN_VECTOR_IMPL(WellboreGeometry, WellboreGeometrySection, Creation)
GETTER_AND_SETTER_TIME_T_ATTRIBUTE_IN_VECTOR_IMPL(WellboreGeometry, WellboreGeometrySection, LastUpdate)

// Optional bool
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, WellboreGeometry, WellboreGeometrySection, CurveConductor, gsoap_eml2_3::soap_new_bool)

// Optional double
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(double, WellboreGeometry, WellboreGeometrySection, FactFric, gsoap_eml2_3::soap_new_double)

// Optional string
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(std::string, WellboreGeometry, WellboreGeometrySection, Grade, gsoap_eml2_3::soap_new_std__string)

// Optional enum
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(gsoap_eml2_3::witsml21__HoleCasingType, WellboreGeometry, WellboreGeometrySection, TypeHoleCasing, gsoap_eml2_3::soap_new_witsml21__HoleCasingType)

// Optional Length Measure
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(WellboreGeometry, WellboreGeometrySection, IdSection, gsoap_eml2_3::eml23__LengthUom, gsoap_eml2_3::soap_new_eml23__LengthMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(WellboreGeometry, WellboreGeometrySection, OdSection, gsoap_eml2_3::eml23__LengthUom, gsoap_eml2_3::soap_new_eml23__LengthMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(WellboreGeometry, WellboreGeometrySection, DiaDrift, gsoap_eml2_3::eml23__LengthUom, gsoap_eml2_3::soap_new_eml23__LengthMeasure)

// Optional Mass per Length Measure
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(WellboreGeometry, WellboreGeometrySection, WtPerLen, gsoap_eml2_3::eml23__MassPerLengthUom, gsoap_eml2_3::soap_new_eml23__MassPerLengthMeasure)

double WellboreGeometry::getWellboreGeometrySectionMdIntervalTop(uint64_t index) const
{
	return static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->WellboreGeometrySection.at(index)->MdInterval->MdMin;
}

double WellboreGeometry::getWellboreGeometrySectionMdIntervalBase(uint64_t index) const
{
	return static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->WellboreGeometrySection.at(index)->MdInterval->MdMax;
}

gsoap_eml2_3::eml23__LengthUom WellboreGeometry::getWellboreGeometrySectionMdIntervalUom(uint64_t index) const
{
	gsoap_eml2_3::eml23__LengthUom result;
	soap_s2eml23__LengthUom(gsoapProxy2_3->soap, static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->WellboreGeometrySection.at(index)->MdInterval->Uom.c_str(), &result);
	return result;
}

void WellboreGeometry::setWellboreGeometrySectionTvdInterval(uint64_t index, double top, double base, gsoap_eml2_3::eml23__LengthUom uom)
{
	witsml21__WellboreGeometrySection* section = static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->WellboreGeometrySection.at(index);

	section->SectionTvdInterval = soap_new_eml23__DatumTvdInterval(gsoapProxy2_3->soap);
	section->SectionTvdInterval->Uom = soap_eml23__LengthUom2s(gsoapProxy2_3->soap, uom);
	section->SectionTvdInterval->TvdMin = top;
	section->SectionTvdInterval->TvdMax= base;
}

double WellboreGeometry::getWellboreGeometrySectionTvdIntervalTop(uint64_t index) const
{
	return static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->WellboreGeometrySection.at(index)->SectionTvdInterval->TvdMin;
}

gsoap_eml2_3::eml23__LengthUom WellboreGeometry::getWellboreGeometrySectionTvdIntervalUom(uint64_t index) const
{
	gsoap_eml2_3::eml23__LengthUom result;
	soap_s2eml23__LengthUom(gsoapProxy2_3->soap, static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->WellboreGeometrySection.at(index)->SectionTvdInterval->Uom.c_str(), &result);
	return result;
}

double WellboreGeometry::getWellboreGeometrySectionTvdIntervalBase(uint64_t index) const
{
	return static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->WellboreGeometrySection.at(index)->SectionTvdInterval->TvdMax;
}

bool WellboreGeometry::hasWellboreGeometrySectionTvdInterval(uint64_t index) const
{
	if (index >= static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->WellboreGeometrySection.size()) { throw std::range_error("The index is out of range"); }

	return static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->WellboreGeometrySection[index]->SectionTvdInterval != nullptr;
}

void WellboreGeometry::pushBackSection(double top, double base, gsoap_eml2_3::eml23__LengthUom uom, const std::string & uid)
{
	static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->WellboreGeometrySection.push_back(gsoap_eml2_3::soap_new_witsml21__WellboreGeometrySection(gsoapProxy2_3->soap));
	uint64_t index = getSectionCount() - 1;
	setWellboreGeometrySectionuid(index, uid.empty() ? std::to_string(index) : uid);

	static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->WellboreGeometrySection.back()->MdInterval = gsoap_eml2_3::soap_new_eml23__MdInterval(gsoapProxy2_3->soap);
	static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->WellboreGeometrySection.back()->MdInterval->MdMin = top;
	static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->WellboreGeometrySection.back()->MdInterval->MdMax = base;
	static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->WellboreGeometrySection.back()->MdInterval->Uom.assign(soap_eml23__LengthUom2s(gsoapProxy2_3->soap, uom));
	setWellboreGeometrySectionCreation(index, 0);
	setWellboreGeometrySectionLastUpdate(index, 0);
}

uint64_t WellboreGeometry::getSectionCount() const
{
	return static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->WellboreGeometrySection.size();
}
