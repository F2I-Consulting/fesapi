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

#include <stdexcept>
#include <algorithm>

#include "../common/EnumStringMapper.h"

#include "SubRepresentation.h"
#include "PropertySet.h"
#include "RepresentationSetRepresentation.h"
#include "../eml2/PropertyKind.h"
#include "AbstractLocal3dCrs.h"
#include "../common/AbstractHdfProxy.h"
#include "TimeSeries.h"
#include "../resqml2_0_1/PropertyKindMapper.h"

using namespace RESQML2_NS;
using namespace std;

void AbstractProperty::loadTargetRelationships()
{
	COMMON_NS::DataObjectReference dor = getRepresentationDor();
	RESQML2_NS::AbstractRepresentation* rep = getRepository()->getDataObjectByUuid<RESQML2_NS::AbstractRepresentation>(dor.getUuid());
	if (rep == nullptr) { // partial transfer
		getRepository()->createPartial(dor);
		rep = getRepository()->getDataObjectByUuid<RESQML2_NS::AbstractRepresentation>(dor.getUuid());
		if (rep == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
	}
	repository->addRelationship(this, rep);

	dor = getTimeSeriesDor();
	if (!dor.isEmpty()) {
		TimeSeries* ts = getRepository()->getDataObjectByUuid<TimeSeries>(dor.getUuid());
		if (ts == nullptr) { // partial transfer
			getRepository()->createPartial(dor);
			ts = getRepository()->getDataObjectByUuid<TimeSeries>(dor.getUuid());
			if (ts == nullptr) {
				throw invalid_argument("The DOR looks invalid.");
			}
		}
		repository->addRelationship(this, ts);
	}

	dor = getLocalCrsDor();
	if (!dor.isEmpty()) {
		AbstractLocal3dCrs* crs = getRepository()->getDataObjectByUuid<AbstractLocal3dCrs>(dor.getUuid());
		if (crs == nullptr) { // partial transfer
			getRepository()->createPartial(dor);
			crs = getRepository()->getDataObjectByUuid<AbstractLocal3dCrs>(dor.getUuid());
			if (crs == nullptr) {
				throw invalid_argument("The DOR looks invalid.");
			}
		}
		repository->addRelationship(this, crs);
	}

	if (!isAssociatedToOneStandardEnergisticsPropertyKind())
	{
		dor = getPropertyKindDor();
		EML2_NS::PropertyKind* pk = getRepository()->getDataObjectByUuid<EML2_NS::PropertyKind>(dor.getUuid());
		if (pk == nullptr) {
			getRepository()->createPartial(dor);
			pk = getRepository()->getDataObjectByUuid<EML2_NS::PropertyKind>(dor.getUuid());
			if (pk == nullptr) {
				throw invalid_argument("The DOR looks invalid.");
			}
		}
		repository->addRelationship(this, pk);
	}
}

bool AbstractProperty::validate()
{
	if (gsoapProxy2_0_1 != nullptr && isAssociatedToOneStandardEnergisticsPropertyKind()) {
		return validatePropertyKindAssociation(getEnergisticsPropertyKind201());
	}
	
	return  validatePropertyKindAssociation(getPropertyKind());
}

void AbstractProperty::setRepresentation(AbstractRepresentation * rep)
{
	if (rep == nullptr) {
		throw invalid_argument("The representation of this property values cannot be null.");
	}
	if (getRepository() == nullptr) {
		rep->getRepository()->addOrReplaceDataObject(this);
	}

	if (gsoapProxy2_0_1 != nullptr) {
		if (static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->SupportingRepresentation != nullptr) {
			getRepository()->deleteRelationship(this, getRepresentation());
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		if (static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->SupportingRepresentation != nullptr) {
			getRepository()->deleteRelationship(this, getRepresentation());
		}
	}

	getRepository()->addRelationship(this, rep);

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

TimeSeries* AbstractProperty::getTimeSeries() const
{
	return static_cast<TimeSeries*>(repository->getDataObjectByUuid(getTimeSeriesDor().getUuid()));
}

void AbstractProperty::setTimeSeries(TimeSeries * ts)
{
	if (ts == nullptr) {
		throw invalid_argument("The time series of this property values cannot be null.");
	}
	if (getRepository() == nullptr) {
		ts->getRepository()->addOrReplaceDataObject(this);
	}

	getRepository()->addRelationship(this, ts);

	// XML
	if (gsoapProxy2_0_1 != nullptr) {
		if (static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex) {
			static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->TimeSeries = ts->newResqmlReference();
		}
		else {
			throw invalid_argument("The time series cannot be set on a property without time indices.");
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		if (static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeIndices) {
			static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeIndices->TimeSeries = ts->newEml23Reference();
		}
		else {
			throw invalid_argument("The time series cannot be set on a property without time indices.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

COMMON_NS::DataObjectReference AbstractProperty::getTimeSeriesDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		if (static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex)
			return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->TimeSeries);
	}
	else if (gsoapProxy2_3 != nullptr) {
		if (static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeIndices)
			return COMMON_NS::DataObjectReference(static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeIndices->TimeSeries);
	}
	else {
		throw logic_error("Not implemented yet");
	}

	return COMMON_NS::DataObjectReference();
}

void AbstractProperty::setTimeIndex(unsigned int timeIndex, TimeSeries * ts)
{
	if (gsoapProxy2_0_1 != nullptr) {
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex = gsoap_resqml2_0_1::soap_new_resqml20__TimeIndex(gsoapProxy2_0_1->soap);
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->Index = timeIndex;
	}
	else {
		throw logic_error("Not implemented yet");
	}

	setTimeSeries(ts);
}

void AbstractProperty::setTimeStep(unsigned int timeStep)
{
	if (gsoapProxy2_0_1 != nullptr) {
		if (static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeStep == nullptr) {
			static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeStep = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
		}
		*(static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeStep) = timeStep;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

time_t AbstractProperty::getTimestamp() const
{
	TimeSeries const * timeSeries = getTimeSeries();

	if (gsoapProxy2_0_1 != nullptr) {
		if (timeSeries && static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex != nullptr) {
			return timeSeries->getTimestamp(static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->Index);
		}

		throw invalid_argument("This property does not have any timestamp.");
	}

	throw logic_error("Not implemented yet");
}

unsigned int AbstractProperty::getTimeIndex() const
{
	TimeSeries const * timeSeries = getTimeSeries();

	if (gsoapProxy2_0_1 != nullptr) {
		if (timeSeries && static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex != nullptr) {
			return static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->Index;
		}

		throw invalid_argument("This property does not have any timestamp.");
	}

	throw logic_error("Not implemented yet");
}

unsigned int AbstractProperty::getElementCountPerValue() const
{
	ULONG64 result;
	if (gsoapProxy2_0_1 != nullptr) {
		result = static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->Count;
	}
	else if (gsoapProxy2_3 != nullptr) {
		result = static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->ValueCountPerIndexableElement != nullptr
			? *static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->ValueCountPerIndexableElement
			: 1;
	}
	else {
		throw logic_error("Not implemented yet");
	}

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much Element Count Per Value");
	}

	return static_cast<unsigned int>(result);
}

gsoap_eml2_3::resqml22__IndexableElement AbstractProperty::getAttachmentKind() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		auto ie201 = static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->IndexableElement;
		if (ie201 == 0) {
			return gsoap_eml2_3::resqml22__IndexableElement__cells;
		}
		else if (ie201 < 17) {
			return static_cast<gsoap_eml2_3::resqml22__IndexableElement>(static_cast<int>(ie201) + 1);
		}
		else {
			return static_cast<gsoap_eml2_3::resqml22__IndexableElement>(static_cast<int>(ie201) + 2);
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->IndexableElement;
	}

	throw logic_error("Not implemented yet");
}

std::vector<RESQML2_NS::PropertySet *> AbstractProperty::getPropertySets() const
{
	return repository->getSourceObjects<RESQML2_NS::PropertySet>(this);
}

unsigned int AbstractProperty::getPropertySetCount() const
{
	const std::vector<RESQML2_NS::PropertySet *> & propSets = getPropertySets();

	if (propSets.size() > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("Too much property set containing this property");
	}

	return static_cast<unsigned int>(propSets.size());
}

RESQML2_NS::PropertySet * AbstractProperty::getPropertySet(unsigned int index) const
{
	const std::vector<RESQML2_NS::PropertySet *> & propSets = getPropertySets();

	if (index < propSets.size()) {
		return propSets[index];
	}

	throw out_of_range("The index of the prop Set is out of range");
}

void AbstractProperty::setLocalCrs(AbstractLocal3dCrs * crs)
{
	if (crs == nullptr) {
		throw invalid_argument("The crs of this property values cannot be null.");
	}
	if (getRepository() == nullptr) {
		crs->getRepository()->addOrReplaceDataObject(this);
	}

	getRepository()->addRelationship(this, crs);

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
}

AbstractLocal3dCrs* AbstractProperty::getLocalCrs() const
{
	return getRepository()->getDataObjectByUuid<AbstractLocal3dCrs>(getLocalCrsDor().getUuid());
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
		if (!propKind->isPartial()) {
			return propKind->getOriginator() == "Energistics";
		}
		throw logic_error("The associated prop kind is partial.");
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
	if (getRepository() == nullptr) {
		propKind->getRepository()->addOrReplaceDataObject(this);
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

	getRepository()->addRelationship(this, propKind);

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
}

COMMON_NS::DataObjectReference AbstractProperty::getPropertyKindDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		if (!isAssociatedToOneStandardEnergisticsPropertyKind()) {
			gsoap_resqml2_0_1::resqml20__AbstractProperty* prop = static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1);
			return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__LocalPropertyKind*>(prop->PropertyKind)->LocalPropertyKind);
		}

		throw invalid_argument("The property kind of this property is not a local one.");
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

bool AbstractProperty::hasRealizationIndex() const
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

ULONG64 AbstractProperty::getRealizationIndex() const
{
	if (!hasRealizationIndex()) {
		throw invalid_argument("This property has not got any realization index");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return *static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->RealizationIndex;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractProperty::setRealizationIndex(ULONG64 realizationIndex)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractProperty* prop = static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1);
		if (prop->RealizationIndex == nullptr) {
			prop->RealizationIndex = static_cast<ULONG64*>(soap_malloc(prop->soap, sizeof(ULONG64)));
		}
		*prop->RealizationIndex = realizationIndex;
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
