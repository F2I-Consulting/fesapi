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
#include "../resqml2_0_1/PropertySet.h"
#include "../resqml2_0_1/UnstructuredGridRepresentation.h"
#include "../resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "../resqml2_0_1/IjkGridParametricRepresentation.h"
#include "../resqml2_0_1/IjkGridLatticeRepresentation.h"
#include "RepresentationSetRepresentation.h"
#include "../common/PropertyKind.h"
#include "AbstractLocal3dCrs.h"
#include "../common/AbstractHdfProxy.h"
#include "TimeSeries.h"
#include "../resqml2_0_1/PropertyKindMapper.h"

using namespace RESQML2_NS;
using namespace std;

void AbstractProperty::loadTargetRelationships()
{
	gsoap_resqml2_0_1::eml20__DataObjectReference const * dor = getRepresentationDor();
	RESQML2_NS::AbstractRepresentation* rep = getRepository()->getDataObjectByUuid<RESQML2_NS::AbstractRepresentation>(dor->UUID);
	if (rep == nullptr) { // partial transfer
		getRepository()->createPartial(dor);
		rep = getRepository()->getDataObjectByUuid<RESQML2_NS::AbstractRepresentation>(dor->UUID);
		if (rep == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
	}
	repository->addRelationship(this, rep);

	dor = getTimeSeriesDor();
	if (dor != nullptr) {
		TimeSeries* ts = getRepository()->getDataObjectByUuid<TimeSeries>(dor->UUID);
		if (ts == nullptr) { // partial transfer
			getRepository()->createPartial(dor);
			ts = getRepository()->getDataObjectByUuid<TimeSeries>(dor->UUID);
			if (ts == nullptr) {
				throw invalid_argument("The DOR looks invalid.");
			}
		}
		repository->addRelationship(this, ts);
	}

	dor = getLocalCrsDor();
	if (dor != nullptr) {
		AbstractLocal3dCrs* crs = getRepository()->getDataObjectByUuid<AbstractLocal3dCrs>(dor->UUID);
		if (crs == nullptr) { // partial transfer
			getRepository()->createPartial(dor);
			crs = getRepository()->getDataObjectByUuid<AbstractLocal3dCrs>(dor->UUID);
			if (crs == nullptr) {
				throw invalid_argument("The DOR looks invalid.");
			}
		}
		repository->addRelationship(this, crs);
	}

	if (!isAssociatedToOneStandardEnergisticsPropertyKind())
	{
		dor = getLocalPropertyKindDor();
		COMMON_NS::PropertyKind* pk = getRepository()->getDataObjectByUuid<COMMON_NS::PropertyKind>(dor->UUID);
		if (pk == nullptr) {
			getRepository()->createPartial(dor);
			pk = getRepository()->getDataObjectByUuid<COMMON_NS::PropertyKind>(dor->UUID);
			if (pk == nullptr) {
				throw invalid_argument("The DOR looks invalid.");
			}
		}
		repository->addRelationship(this, pk);
	}
}

bool AbstractProperty::validate()
{
	return isAssociatedToOneStandardEnergisticsPropertyKind() ? validatePropertyKindAssociation(getEnergisticsPropertyKind()) : validatePropertyKindAssociation(getLocalPropertyKind());
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

	getRepository()->addRelationship(this, rep);

	// XML
	if (gsoapProxy2_0_1 != nullptr) {
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->SupportingRepresentation = rep->newResqmlReference();
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

AbstractRepresentation* AbstractProperty::getRepresentation() const
{
	return getRepository()->getDataObjectByUuid<AbstractRepresentation>(getRepresentationUuid());
}

gsoap_resqml2_0_1::eml20__DataObjectReference* AbstractProperty::getRepresentationDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->SupportingRepresentation;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string AbstractProperty::getRepresentationUuid() const
{
	return getRepresentationDor()->UUID;
}

std::string AbstractProperty::getRepresentationTitle() const
{
	return getRepresentationDor()->Title;
}

std::string AbstractProperty::getRepresentationContentType() const
{
	return getRepresentationDor()->ContentType;
}

TimeSeries* AbstractProperty::getTimeSeries() const
{
	return static_cast<TimeSeries*>(repository->getDataObjectByUuid(getTimeSeriesUuid()));
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
		if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCORECategoricalPropertySeries)
		{
			if (static_cast<gsoap_resqml2_0_1::_resqml20__CategoricalPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr) {
				static_cast<gsoap_resqml2_0_1::_resqml20__CategoricalPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			}
			else {
				throw invalid_argument("The time series cannot be set on a property without time indices.");
			}
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCORECommentPropertySeries)
		{
			if (static_cast<gsoap_resqml2_0_1::_resqml20__CommentPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				static_cast<gsoap_resqml2_0_1::_resqml20__CommentPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			else {
				throw invalid_argument("The time series cannot be set on a property without time indices.");
			}
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCOREContinuousPropertySeries)
		{
			if (static_cast<gsoap_resqml2_0_1::_resqml20__ContinuousPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				static_cast<gsoap_resqml2_0_1::_resqml20__ContinuousPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			else {
				throw invalid_argument("The time series cannot be set on a property without time indices.");
			}
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCOREDiscretePropertySeries)
		{
			if (static_cast<gsoap_resqml2_0_1::_resqml20__DiscretePropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				static_cast<gsoap_resqml2_0_1::_resqml20__DiscretePropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			else {
				throw invalid_argument("The time series cannot be set on a property without time indices.");
			}
		}
		else
		{
			if (static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex) {
				static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->TimeSeries = ts->newResqmlReference();
			}
			else {
				throw invalid_argument("The time series cannot be set on a property without time indices.");
			}
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::eml20__DataObjectReference* AbstractProperty::getTimeSeriesDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCORECategoricalPropertySeries) {
			if (static_cast<gsoap_resqml2_0_1::_resqml20__CategoricalPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				return static_cast<gsoap_resqml2_0_1::_resqml20__CategoricalPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries;
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCORECommentPropertySeries) {
			if (static_cast<gsoap_resqml2_0_1::_resqml20__CommentPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				return static_cast<gsoap_resqml2_0_1::_resqml20__CommentPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries;
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCOREContinuousPropertySeries) {
			if (static_cast<gsoap_resqml2_0_1::_resqml20__ContinuousPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				return static_cast<gsoap_resqml2_0_1::_resqml20__ContinuousPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries;
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCOREDiscretePropertySeries) {
			if (static_cast<gsoap_resqml2_0_1::_resqml20__DiscretePropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				return static_cast<gsoap_resqml2_0_1::_resqml20__DiscretePropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries;
		}
		else {
			if (static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex)
				return static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->TimeSeries;
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}

	return nullptr;
}

std::string AbstractProperty::getTimeSeriesUuid() const
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getTimeSeriesDor();
	return dor == nullptr ? "" : dor->UUID;
}

std::string AbstractProperty::getTimeSeriesTitle() const
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getTimeSeriesDor();
	return dor == nullptr ? "" : dor->Title;
}

void AbstractProperty::setTimeIndex(const unsigned int & timeIndex, TimeSeries * ts)
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

void AbstractProperty::setTimeStep(const unsigned int & timeStep)
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
	if (gsoapProxy2_0_1 != nullptr) {
		const ULONG64 result = static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->Count;

		if (result > (std::numeric_limits<unsigned int>::max)()) {
			throw std::range_error("There are too much Element Count Per Value");
		}

		return static_cast<unsigned int>(result);
	}

	throw logic_error("Not implemented yet");
}

gsoap_resqml2_0_1::resqml20__IndexableElements AbstractProperty::getAttachmentKind() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->IndexableElement;
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
	else {
		throw logic_error("Not implemented yet");
	}
}

AbstractLocal3dCrs* AbstractProperty::getLocalCrs() const
{
	return getRepository()->getDataObjectByUuid<AbstractLocal3dCrs>(getLocalCrsUuid());
}

gsoap_resqml2_0_1::eml20__DataObjectReference* AbstractProperty::getLocalCrsDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->LocalCrs;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string AbstractProperty::getLocalCrsUuid() const
{
	gsoap_resqml2_0_1::eml20__DataObjectReference const * const dor = getLocalCrsDor();
	return dor == nullptr ? "" : dor->UUID;
}

std::string AbstractProperty::getLocalCrsTitle() const
{
	gsoap_resqml2_0_1::eml20__DataObjectReference const * const dor = getLocalCrsDor();
	return dor == nullptr ? "" : dor->Title;
}

bool AbstractProperty::isAssociatedToOneStandardEnergisticsPropertyKind() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->PropertyKind->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__StandardPropertyKind;
	}

	throw logic_error("Not implemented yet");
}

std::string AbstractProperty::getPropertyKindDescription() const
{
	if (isAssociatedToOneStandardEnergisticsPropertyKind()) {
		if (repository->getPropertyKindMapper() != nullptr) {
			return repository->getPropertyKindMapper()->getDescriptionOfResqmlStandardPropertyKindName(getEnergisticsPropertyKind());
		}

		throw std::invalid_argument("You must load the property kind mapping files if you want to get the parent property kind.");
	}

	return getLocalPropertyKind()->getDescription();
}

std::string AbstractProperty::getPropertyKindAsString() const
{
	if (isAssociatedToOneStandardEnergisticsPropertyKind()) {
		COMMON_NS::EnumStringMapper tmp;
		return tmp.getEnergisticsPropertyKindName(getEnergisticsPropertyKind());
	}

	return getLocalPropertyKind()->getTitle();
}

std::string AbstractProperty::getPropertyKindParentAsString() const
{
	if (isAssociatedToOneStandardEnergisticsPropertyKind()) {
		if (repository->getPropertyKindMapper() != nullptr) {
			gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind propKindEnum = repository->getPropertyKindMapper()->getPropertyKindParentOfResqmlStandardPropertyKindName(getEnergisticsPropertyKind());
			COMMON_NS::EnumStringMapper tmp;
			return tmp.getEnergisticsPropertyKindName(propKindEnum);
		}

		throw std::invalid_argument("You must load the property kind mapping files if you want to get the parent property kind.");
	}

	return getLocalPropertyKind()->getParentAsString();
}

gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind AbstractProperty::getEnergisticsPropertyKind() const
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

void AbstractProperty::setLocalPropertyKind(COMMON_NS::PropertyKind* propKind)
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
			getRepository()->deleteRelationship(this, getLocalPropertyKind());
		}
	}

	getRepository()->addRelationship(this, propKind);

	// XML
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__LocalPropertyKind* xmlLocalPropKind = gsoap_resqml2_0_1::soap_new_resqml20__LocalPropertyKind(gsoapProxy2_0_1->soap);
		xmlLocalPropKind->LocalPropertyKind = propKind->newResqmlReference();
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->PropertyKind = xmlLocalPropKind;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::eml20__DataObjectReference* AbstractProperty::getLocalPropertyKindDor() const
{
	if (!isAssociatedToOneStandardEnergisticsPropertyKind()) {
		if (gsoapProxy2_0_1 != nullptr) {
			gsoap_resqml2_0_1::resqml20__AbstractProperty* prop = static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1);
			return static_cast<gsoap_resqml2_0_1::resqml20__LocalPropertyKind*>(prop->PropertyKind)->LocalPropertyKind;
		}
		else {
			throw logic_error("Not implemented yet");
		}
	}

	throw invalid_argument("The property kind of this property is not a local one.");
}

std::string AbstractProperty::getLocalPropertyKindUuid() const
{
	return getLocalPropertyKindDor()->UUID;
}

std::string AbstractProperty::getLocalPropertyKindTitle() const
{
	return getLocalPropertyKindDor()->Title;
}

COMMON_NS::PropertyKind* AbstractProperty::getLocalPropertyKind() const
{
	return getRepository()->getDataObjectByUuid<COMMON_NS::PropertyKind>(getLocalPropertyKindUuid());
}

bool AbstractProperty::hasRealizationIndex() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->RealizationIndex != nullptr;
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
