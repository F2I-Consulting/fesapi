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
#include "AbstractProperty.h"

#include <algorithm>

#include <hdf5.h>

#include "../tools/TimeTools.h"

#include "../common/EnumStringMapper.h"

#include "../eml2/AbstractHdfProxy.h"
#include "../eml2/AbstractLocal3dCrs.h"
#include "../eml2/PropertyKind.h"
#include "../eml2/TimeSeries.h"

#include "AbstractRepresentation.h"

#include "../resqml2_0_1/PropertyKindMapper.h"
#include "../resqml2_0_1/PropertySet.h"

using namespace RESQML2_NS;
using namespace std;

void AbstractProperty::loadTargetRelationships()
{
	COMMON_NS::DataObjectReference dor = getRepresentationDor();
	convertDorIntoRel<RESQML2_NS::AbstractRepresentation>(dor);

	dor = getTimeSeriesDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<EML2_NS::TimeSeries>(dor);
	}

	dor = getLocalCrsDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<EML2_NS::AbstractLocal3dCrs>(dor);
	}

	dor = getPropertyKindDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<EML2_NS::PropertyKind>(dor);
	}

	for (uint64_t patchIndex = 0; patchIndex < getPatchCount(); ++patchIndex) {
		convertDorIntoRel(getHdfProxyDor(patchIndex));
	}
}

bool AbstractProperty::validate()
{
	if (gsoapProxy2_0_1 != nullptr && isAssociatedToOneStandardEnergisticsPropertyKind()) {
		return validatePropertyKindAssociation(getEnergisticsPropertyKind201());
	}
	
	return validatePropertyKindAssociation(getPropertyKind());
}

void AbstractProperty::setRepresentation(AbstractRepresentation * rep)
{
	if (rep == nullptr) {
		throw invalid_argument("The representation of this property values cannot be null.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		if (static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->SupportingRepresentation != nullptr) {
			rep->getRepository()->deleteRelationship(this, getRepresentation());
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		if (static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->SupportingRepresentation != nullptr) {
			getRepository()->deleteRelationship(this, getRepresentation());
		}
	}

	// XML
	if (gsoapProxy2_0_1 != nullptr) {
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->SupportingRepresentation = rep->newResqmlReference();
	}
	else if (gsoapProxy2_3 != nullptr) {
		static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->SupportingRepresentation = rep->newEml23Reference();
	}
	else {
		throw logic_error("Not implemented yet");
	}

	getRepository()->addRelationship(this, rep);
}

AbstractRepresentation* AbstractProperty::getRepresentation() const
{
	return getRepository()->getDataObjectByUuid<AbstractRepresentation>(getRepresentationDor().getUuid());
}

COMMON_NS::DataObjectReference AbstractProperty::getRepresentationDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->SupportingRepresentation);
	}
	else if (gsoapProxy2_3 != nullptr) {
		return COMMON_NS::DataObjectReference(static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->SupportingRepresentation);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

EML2_NS::TimeSeries* AbstractProperty::getTimeSeries() const
{
	return repository->getDataObjectByUuid<EML2_NS::TimeSeries>(getTimeSeriesDor().getUuid());
}

void AbstractProperty::setTimeSeries(EML2_NS::TimeSeries * ts)
{
	if (ts == nullptr) {
		throw invalid_argument("The time series of this property values cannot be null.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		if (static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex == nullptr) {
			static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex = gsoap_resqml2_0_1::soap_new_resqml20__TimeIndex(gsoapProxy2_0_1->soap);
		}
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->TimeSeries = ts->newResqmlReference();
	}
	else if (gsoapProxy2_3 != nullptr) {
		if (static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeOrIntervalSeries == nullptr) {
			static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeOrIntervalSeries = gsoap_eml2_3::soap_new_eml23__TimeOrIntervalSeries(gsoapProxy2_3->soap);
		}
		static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeOrIntervalSeries->TimeSeries = ts->newEml23Reference();
	}
	else {
		throw logic_error("Not implemented yet");
	}

	getRepository()->addRelationship(this, ts);
}

void AbstractProperty::setSingleTimestamp(time_t timestamp, LONG64 yearOffset)
{
	std::tm tmConversion = timeTools::to_calendar_time(std::chrono::system_clock::from_time_t(timestamp));
	if (gsoapProxy2_0_1 != nullptr) {
		auto const* timeSeries = getTimeSeries();
		if (timeSeries == nullptr) {
			throw invalid_argument("When writing RESQML2.0 dataobject, you must first set the associated Time Series of this property.");
		}
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->Index = getTimeSeries()->getTimestampIndex(tmConversion, yearOffset);
	}
	else if (gsoapProxy2_3 != nullptr) {
		static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->Time = gsoap_eml2_3::soap_new_eml23__GeologicTime(gsoapProxy2_3->soap);
		static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->Time->DateTime = tmConversion;
		if (yearOffset != 0) {
			static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->Time->AgeOffsetAttribute = (LONG64*)soap_malloc(gsoapProxy2_3->soap, sizeof(LONG64));
			*static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->Time->AgeOffsetAttribute = yearOffset;
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

time_t AbstractProperty::getSingleTimestamp() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		if (static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex == nullptr) {
			return -1;
		}

		auto const* timeSeries = getTimeSeries();
		if (timeSeries == nullptr) {
			throw invalid_argument("There is no time series associated to this property although it has a time index. This is not allowed by the RESQML2.0 standard.");
		}

		return getTimeSeries()->getTimestamp(static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->Index);
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->Time == nullptr
			? -1
			: timeTools::timegm(static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->Time->DateTime);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

COMMON_NS::DataObjectReference AbstractProperty::getTimeSeriesDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		if (static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex != nullptr) {
			return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->TimeSeries);
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		if (static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeOrIntervalSeries != nullptr) {
			return COMMON_NS::DataObjectReference(static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeOrIntervalSeries->TimeSeries);
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}

	return COMMON_NS::DataObjectReference();
}

bool AbstractProperty::useInterval() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return false;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeOrIntervalSeries != nullptr
			? static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeOrIntervalSeries->UseInterval
			: false;
	}

	throw logic_error("Not implemented yet");
}

uint64_t AbstractProperty::getElementCountPerValue() const
{
	uint64_t result;
	if (gsoapProxy2_0_1 != nullptr) {
		result = static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->Count;
	}
	else if (gsoapProxy2_3 != nullptr) {
		result = static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->ValueCountPerIndexableElement[0];
		for (size_t dimIndex = 1; dimIndex < static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->ValueCountPerIndexableElement.size(); ++dimIndex) {
			result *= static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->ValueCountPerIndexableElement[dimIndex];
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}

	return result;
}

gsoap_eml2_3::eml23__IndexableElement AbstractProperty::getAttachmentKind() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__IndexableElements ie201 = static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->IndexableElement;
		if (ie201 == gsoap_resqml2_0_1::resqml20__IndexableElements::cells) {
			return gsoap_eml2_3::eml23__IndexableElement::cells;
		}
		else if (static_cast<int>(ie201) < 17) {
			return static_cast<gsoap_eml2_3::eml23__IndexableElement>(static_cast<int>(ie201) + 1);
		}
		else {
			return static_cast<gsoap_eml2_3::eml23__IndexableElement>(static_cast<int>(ie201) + 2);
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->IndexableElement;
	}

	throw logic_error("Not implemented yet");
}

std::vector<RESQML2_0_1_NS::PropertySet *> AbstractProperty::getPropertySets() const
{
	return repository->getSourceObjects<RESQML2_0_1_NS::PropertySet>(this);
}

uint64_t AbstractProperty::getPropertySetCount() const
{
	return getPropertySets().size();
}

RESQML2_0_1_NS::PropertySet * AbstractProperty::getPropertySet(uint64_t index) const
{
	return getPropertySets().at(index);
}

void AbstractProperty::setLocalCrs(EML2_NS::AbstractLocal3dCrs * crs)
{
	if (crs == nullptr) {
		throw invalid_argument("The crs of this property values cannot be null.");
	}

	// XML
	if (gsoapProxy2_0_1 != nullptr) {
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->LocalCrs = crs->newResqmlReference();
	}
	else if (gsoapProxy2_3 != nullptr) {
		static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->LocalCrs = crs->newEml23Reference();
	}
	else {
		throw logic_error("Not implemented yet");
	}

	getRepository()->addRelationship(this, crs);
}

EML2_NS::AbstractLocal3dCrs* AbstractProperty::getLocalCrs() const
{
	return getRepository()->getDataObjectByUuid<EML2_NS::AbstractLocal3dCrs>(getLocalCrsDor().getUuid());
}

COMMON_NS::DataObjectReference AbstractProperty::getLocalCrsDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->LocalCrs);
	}
	else if (gsoapProxy2_3 != nullptr) {
		return COMMON_NS::DataObjectReference(static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->LocalCrs);
	}

	throw logic_error("Not implemented yet");
}

bool AbstractProperty::isAssociatedToOneStandardEnergisticsPropertyKind() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->PropertyKind->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__StandardPropertyKind;
	}
	else if (gsoapProxy2_3 != nullptr) {
		auto propKind = getPropertyKind();
		// We should find instead if the uuid is part of PWLS3. It would no more require the check on "partial"
		if (!propKind->isPartial()) {
			return propKind->getOriginator() == "Energistics";
		}
		return false;
	}

	throw logic_error("Unrecognized RESQML version");
}

std::string AbstractProperty::getPropertyKindDescription() const
{
	if (gsoapProxy2_0_1 != nullptr && isAssociatedToOneStandardEnergisticsPropertyKind()) {
		if (repository->getPropertyKindMapper() != nullptr) {
			return repository->getPropertyKindMapper()->getDescriptionOfResqmlStandardPropertyKindName(getEnergisticsPropertyKind201());
		}

		throw std::invalid_argument("You must load the property kind mapping files if you want to get the parent property kind.");
	}

	return getPropertyKind()->getDescription();
}

std::string AbstractProperty::getPropertyKindAsString() const
{
	if (gsoapProxy2_0_1 != nullptr && isAssociatedToOneStandardEnergisticsPropertyKind()) {
		COMMON_NS::EnumStringMapper tmp;
		return tmp.getEnergisticsPropertyKindName(getEnergisticsPropertyKind201());
	}

	return getPropertyKind()->getTitle();
}

std::string AbstractProperty::getPropertyKindParentAsString() const
{
	if (gsoapProxy2_0_1 != nullptr && isAssociatedToOneStandardEnergisticsPropertyKind()) {
		if (repository->getPropertyKindMapper() != nullptr) {
			gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind propKindEnum = repository->getPropertyKindMapper()->getPropertyKindParentOfResqmlStandardPropertyKindName(getEnergisticsPropertyKind201());
			COMMON_NS::EnumStringMapper tmp;
			return tmp.getEnergisticsPropertyKindName(propKindEnum);
		}

		throw std::invalid_argument("You must load the property kind mapping files if you want to get the parent property kind.");
	}

	return getPropertyKind()->getParentAsString();
}

void AbstractProperty::setPropertyKind(EML2_NS::PropertyKind* propKind)
{
	if (propKind == nullptr) {
		throw invalid_argument("The local property kind of this property cannot be null.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		if (static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->PropertyKind != nullptr &&
			static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->PropertyKind->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__LocalPropertyKind) {
			getRepository()->deleteRelationship(this, getPropertyKind());
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		if (static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->PropertyKind != nullptr) {
			getRepository()->deleteRelationship(this, getPropertyKind());
		}
	}

	// XML
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__LocalPropertyKind* xmlLocalPropKind = gsoap_resqml2_0_1::soap_new_resqml20__LocalPropertyKind(gsoapProxy2_0_1->soap);
		xmlLocalPropKind->LocalPropertyKind = propKind->newResqmlReference();
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->PropertyKind = xmlLocalPropKind;
	}
	else if (gsoapProxy2_3 != nullptr) {
		static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->PropertyKind = propKind->newEml23Reference();
	}
	else {
		throw logic_error("Unrecognized RESQML version");
	}

	getRepository()->addRelationship(this, propKind);
}

COMMON_NS::DataObjectReference AbstractProperty::getPropertyKindDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		if (!isAssociatedToOneStandardEnergisticsPropertyKind()) {
			gsoap_resqml2_0_1::resqml20__AbstractProperty* prop = static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1);
			return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__LocalPropertyKind*>(prop->PropertyKind)->LocalPropertyKind);
		}

		return COMMON_NS::DataObjectReference();
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__AbstractProperty* prop = static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3);
		return COMMON_NS::DataObjectReference(prop->PropertyKind);
	}

	throw logic_error("Unrecognized RESQML version");
}

EML2_NS::PropertyKind* AbstractProperty::getPropertyKind() const
{
	return getRepository()->getDataObjectByUuid<EML2_NS::PropertyKind>(getPropertyKindDor().getUuid());
}

bool AbstractProperty::hasRealizationIndices() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->RealizationIndex != nullptr;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->RealizationIndices != nullptr;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::vector<int64_t> AbstractProperty::getRealizationIndices() const
{
	if (!hasRealizationIndices()) {
		throw invalid_argument("This property has not got any realization index");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		ULONG64 tmp = *static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->RealizationIndex;
		if (tmp > static_cast<ULONG64>((std::numeric_limits<int64_t>::max)())) {
			throw std::range_error("The realization index \"" + std::to_string(tmp) + "\" is out of the int64 range");
		}
		return std::vector<int64_t> {static_cast<int64_t>(tmp)};
	}
	else if (gsoapProxy2_3 != nullptr) {
		std::vector<int64_t> result(getCountOfArray(static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->RealizationIndices));
		readArrayNdOfInt64Values(static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->RealizationIndices, result.data());
		return result;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractProperty::setRealizationIndices(std::vector<int64_t> realizationIndices)
{
	if (gsoapProxy2_0_1 != nullptr) {
		if (realizationIndices.size() > 1) {
			throw std::invalid_argument("RESQML 2.0.1 does not support more than one realization index per property.");
		}
		gsoap_resqml2_0_1::resqml20__AbstractProperty* prop = static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1);
		if (realizationIndices.empty()) {
			prop->RealizationIndex = nullptr;
			return;
		}
		if (prop->RealizationIndex == nullptr) {
			prop->RealizationIndex = static_cast<ULONG64*>(soap_malloc(prop->soap, sizeof(ULONG64)));
		}
		*prop->RealizationIndex = realizationIndices[0];
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__AbstractProperty* prop = static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3);
		if (realizationIndices.empty()) {
			prop->RealizationIndices = nullptr;
			return;
		}

		auto* xmlArray = gsoap_eml2_3::soap_new_eml23__IntegerXmlArray(gsoapProxy2_3->soap);
		xmlArray->CountPerValue = 1;
		xmlArray->Values = std::to_string(realizationIndices[0]);
		for (size_t i = 1; i < realizationIndices.size(); ++i) {
			xmlArray->Values += " " + std::to_string(realizationIndices[i]);
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind AbstractProperty::getEnergisticsPropertyKind201() const
{
	if (isAssociatedToOneStandardEnergisticsPropertyKind())
	{
		if (gsoapProxy2_0_1 != nullptr) {
			gsoap_resqml2_0_1::resqml20__AbstractProperty* prop = static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1);
			return static_cast<gsoap_resqml2_0_1::resqml20__StandardPropertyKind*>(prop->PropertyKind)->Kind;
		}

		throw logic_error("Not implemented yet");
	}

	throw invalid_argument("The property kind of this property is not an Energistics one.");
}


COMMON_NS::AbstractObject::hdfDatatypeEnum AbstractProperty::getValuesHdfDatatype() const
{
	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(0, nullValue, dsPath);

	return hdfProxy->getHdfDatatypeInDataset(dsPath);
}

uint64_t AbstractProperty::getValuesCountOfDimensionOfPatch(unsigned int dimIndex, uint64_t patchIndex) const
{
	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	std::vector<hsize_t> dims = hdfProxy->getElementCountPerDimension(dsPath);

	if (dimIndex < dims.size()) {
		return dims[dimIndex];
	}

	throw out_of_range("The dim index to get the count is out of range.");
}

unsigned int AbstractProperty::getDimensionsCountOfPatch(uint64_t patchIndex) const
{
	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	return hdfProxy->getDimensionCount(dsPath);
}

int64_t AbstractProperty::getValuesCountOfPatch(uint64_t patchIndex) const
{
	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	return hdfProxy->getElementCount(dsPath);
}
