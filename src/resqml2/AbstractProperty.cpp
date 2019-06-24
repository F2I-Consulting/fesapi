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
#include "resqml2/AbstractProperty.h"

#include <stdexcept>
#include <algorithm>

#include "common/EnumStringMapper.h"

#include "resqml2/SubRepresentation.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "resqml2_0_1/IjkGridParametricRepresentation.h"
#include "resqml2_0_1/IjkGridLatticeRepresentation.h"
#include "resqml2/RepresentationSetRepresentation.h"
#include "resqml2/PropertyKind.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "common/AbstractHdfProxy.h"
#include "resqml2/TimeSeries.h"
#include "resqml2_0_1/PropertyKindMapper.h"

using namespace RESQML2_NS;
using namespace std;
using namespace epc;


void AbstractProperty::setXmlRepresentation(RESQML2_NS::AbstractRepresentation * rep)
{
	if (gsoapProxy2_0_1 != nullptr) {
		static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->SupportingRepresentation = rep->newResqmlReference();
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractProperty::setXmlTimeSeries(TimeSeries * ts)
{
	if (gsoapProxy2_0_1 != nullptr) {
		if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECategoricalPropertySeries)
		{
			if (static_cast<gsoap_resqml2_0_1::_resqml2__CategoricalPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr) {
				static_cast<gsoap_resqml2_0_1::_resqml2__CategoricalPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			}
			else {
				throw invalid_argument("The time series cannot be set on a property without time indices.");
			}
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECommentPropertySeries)
		{
			if (static_cast<gsoap_resqml2_0_1::_resqml2__CommentPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				static_cast<gsoap_resqml2_0_1::_resqml2__CommentPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			else {
				throw invalid_argument("The time series cannot be set on a property without time indices.");
			}
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREContinuousPropertySeries)
		{
			if (static_cast<gsoap_resqml2_0_1::_resqml2__ContinuousPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				static_cast<gsoap_resqml2_0_1::_resqml2__ContinuousPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			else {
				throw invalid_argument("The time series cannot be set on a property without time indices.");
			}
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREDiscretePropertySeries)
		{
			if (static_cast<gsoap_resqml2_0_1::_resqml2__DiscretePropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				static_cast<gsoap_resqml2_0_1::_resqml2__DiscretePropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			else {
				throw invalid_argument("The time series cannot be set on a property without time indices.");
			}
		}
		else
		{
			if (static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex) {
				static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->TimeSeries = ts->newResqmlReference();
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

void AbstractProperty::setXmlLocalPropertyKind(class PropertyKind* propKind)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__LocalPropertyKind* xmlLocalPropKind = gsoap_resqml2_0_1::soap_new_resqml2__LocalPropertyKind(gsoapProxy2_0_1->soap, 1);
		xmlLocalPropKind->LocalPropertyKind = propKind->newResqmlReference();
		static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->PropertyKind = xmlLocalPropKind;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

vector<Relationship> AbstractProperty::getAllEpcRelationships() const
{
	vector<Relationship> result;

	// XML forward relationship
	AbstractRepresentation* representation = getRepresentation();
	Relationship relRep(representation->getPartNameInEpcDocument(), "", representation->getUuid());
	relRep.setDestinationObjectType();
	result.push_back(relRep);

	if (local3dCrs != nullptr)
	{
		Relationship relCrs(local3dCrs->getPartNameInEpcDocument(), "", local3dCrs->getUuid());
		relCrs.setDestinationObjectType();
		result.push_back(relCrs);
	}

	TimeSeries* timeSeries = getTimeSeries();
	if (timeSeries != nullptr)
	{
		Relationship relTs(timeSeries->getPartNameInEpcDocument(), "", timeSeries->getUuid());
		relTs.setDestinationObjectType();
		result.push_back(relTs);
	}

	COMMON_NS::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy != nullptr)
	{
		Relationship relHdf(hdfProxy->getPartNameInEpcDocument(), "", hdfProxy->getUuid());
		relHdf.setMlToExternalPartProxyType();
		result.push_back(relHdf);
	}

	if (isAssociatedToOneStandardEnergisticsPropertyKind() == false)
	{
		PropertyKind* pk = getLocalPropertyKind();
		if (pk != nullptr)
		{
			Relationship relPropType(pk->getPartNameInEpcDocument(), "", pk->getUuid());
			relPropType.setDestinationObjectType();
			result.push_back(relPropType);
		}
	}

	return result;
}

void AbstractProperty::resolveTargetRelationships(COMMON_NS::DataObjectRepository* epcDoc)
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getRepresentationDor();
	RESQML2_NS::AbstractRepresentation* rep = epcDoc->getDataObjectByUuid<RESQML2_NS::AbstractRepresentation>(dor->UUID);
	if (rep == nullptr) { // partial transfer
		getRepository()->createPartial(dor);
		rep = getRepository()->getDataObjectByUuid<RESQML2_NS::AbstractRepresentation>(dor->UUID);
	}
	if (rep == nullptr) {
		throw invalid_argument("The DOR looks invalid.");
	}
	updateXml = false;
	setRepresentation(rep);
	updateXml = true;

	dor = getTimeSeriesDor();
	if (dor != nullptr) {
		TimeSeries* ts = epcDoc->getDataObjectByUuid<TimeSeries>(dor->UUID);
		if (ts == nullptr) { // partial transfer
			getRepository()->createPartial(dor);
			ts = getRepository()->getDataObjectByUuid<TimeSeries>(dor->UUID);
		}
		if (ts == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
		updateXml = false;
		setTimeSeries(ts);
		updateXml = true;
	}

	if (!isAssociatedToOneStandardEnergisticsPropertyKind())
	{
		dor = getLocalPropertyKindDor();
		RESQML2_NS::PropertyKind* pk = epcDoc->getDataObjectByUuid<PropertyKind>(dor->UUID);
		if (pk == nullptr) {
			epcDoc->createPartial(dor);
			pk = epcDoc->getDataObjectByUuid<PropertyKind>(dor->UUID);
			if (pk == nullptr) {
				throw invalid_argument("The DOR looks invalid.");
			}
		}

		updateXml = false;
		setLocalPropertyKind(pk);
		updateXml = true;
	}

	string uuidHdfProxy = getHdfProxyUuid();
	if (!uuidHdfProxy.empty()) {
		COMMON_NS::AbstractHdfProxy* hdfProxy = epcDoc->getDataObjectByUuid<COMMON_NS::AbstractHdfProxy>(uuidHdfProxy);
		if (hdfProxy == nullptr) {
			epcDoc->addWarning("The referenced hdf proxy (" + uuidHdfProxy + ") is missing.");
		}
		updateXml = false;
		setHdfProxy(hdfProxy);
		updateXml = true;
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

	// EPC
	gsoap_resqml2_0_1::eml20__DataObjectReference* repDor = getRepresentationDor();
	if (repDor != nullptr) { // already associated to a representation -> Need to remove existing association
		std::vector<AbstractProperty*>& currentRepPropertySet = getRepresentation()->propertySet;
		currentRepPropertySet.erase(remove(currentRepPropertySet.begin(), currentRepPropertySet.end(), this), currentRepPropertySet.end());
	}
	rep->propertySet.push_back(this);

	// XML
	if (updateXml) {
		setXmlRepresentation(rep);
	}
}

AbstractRepresentation* AbstractProperty::getRepresentation() const
{
	return getRepository()->getDataObjectByUuid<AbstractRepresentation>(getRepresentationUuid());
}

gsoap_resqml2_0_1::eml20__DataObjectReference* AbstractProperty::getRepresentationDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->SupportingRepresentation;
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

	// EPC
	ts->propertySet.push_back(this);

	// XML
	if (updateXml) {
		setXmlTimeSeries(ts);
	}
}

gsoap_resqml2_0_1::eml20__DataObjectReference* AbstractProperty::getTimeSeriesDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECategoricalPropertySeries) {
			if (static_cast<gsoap_resqml2_0_1::_resqml2__CategoricalPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				return static_cast<gsoap_resqml2_0_1::_resqml2__CategoricalPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries;
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECommentPropertySeries) {
			if (static_cast<gsoap_resqml2_0_1::_resqml2__CommentPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				return static_cast<gsoap_resqml2_0_1::_resqml2__CommentPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries;
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREContinuousPropertySeries) {
			if (static_cast<gsoap_resqml2_0_1::_resqml2__ContinuousPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				return static_cast<gsoap_resqml2_0_1::_resqml2__ContinuousPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries;
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREDiscretePropertySeries) {
			if (static_cast<gsoap_resqml2_0_1::_resqml2__DiscretePropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				return static_cast<gsoap_resqml2_0_1::_resqml2__DiscretePropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries;
		}
		else {
			if (static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex)
				return static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->TimeSeries;
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
		static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex = gsoap_resqml2_0_1::soap_new_resqml2__TimeIndex(gsoapProxy2_0_1->soap, 1);
		static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->Index = timeIndex;
	}
	else {
		throw logic_error("Not implemented yet");
	}

	setTimeSeries(ts);
}

void AbstractProperty::setTimeStep(const unsigned int & timeStep)
{
	if (gsoapProxy2_0_1 != nullptr) {
		if (static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeStep == nullptr) {
			static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeStep = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
		}
		*(static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeStep) = timeStep;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

time_t AbstractProperty::getTimestamp() const
{
	TimeSeries* timeSeries = getTimeSeries();

	if (gsoapProxy2_0_1 != nullptr) {
		if (timeSeries && static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex) {
			return timeSeries->getTimestamp(static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->Index);
		}
		else {
			throw invalid_argument("This property does not have any timestamp.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

unsigned int AbstractProperty::getTimeIndex() const
{
	TimeSeries* timeSeries = getTimeSeries();

	if (gsoapProxy2_0_1 != nullptr) {
		if (timeSeries && static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex) {
			return static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->Index;
		}
		else {
			throw invalid_argument("This property does not have any timestamp.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractProperty::setHdfProxy(COMMON_NS::AbstractHdfProxy * proxy)
{
	if (proxy == nullptr) {
		throw invalid_argument("The hdf proxy of property " + getUuid() + " cannot be null");
	}

	proxy->propertySourceObject.push_back(this);
}

COMMON_NS::AbstractHdfProxy* AbstractProperty::getHdfProxy() const
{
	return static_cast<COMMON_NS::AbstractHdfProxy*>(repository->getDataObjectByUuid(getHdfProxyUuid()));
}

std::string AbstractProperty::getHdfProxyUuid() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREPointsProperty)
		{
			gsoap_resqml2_0_1::_resqml2__PointsProperty* prop = static_cast<gsoap_resqml2_0_1::_resqml2__PointsProperty*>(gsoapProxy2_0_1);
			gsoap_resqml2_0_1::resqml2__PatchOfPoints* firstPatch = prop->PatchOfPoints[0];

			int valuesType = firstPatch->Points->soap_type();
			if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dHdf5Array) {
				return static_cast<gsoap_resqml2_0_1::resqml2__Point3dHdf5Array*>(firstPatch->Points)->Coordinates->HdfProxy->UUID;
			}
			else {
				return "";
			}
		}
		else {
			gsoap_resqml2_0_1::resqml2__AbstractValuesProperty* prop = static_cast<gsoap_resqml2_0_1::resqml2__AbstractValuesProperty*>(gsoapProxy2_0_1);
			gsoap_resqml2_0_1::resqml2__PatchOfValues* firstPatch = prop->PatchOfValues[0];

			int valuesType = firstPatch->Values->soap_type();
			if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array) {
				return static_cast<gsoap_resqml2_0_1::resqml2__BooleanHdf5Array*>(firstPatch->Values)->Values->HdfProxy->UUID;
			}
			else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
				return static_cast<gsoap_resqml2_0_1::resqml2__DoubleHdf5Array*>(firstPatch->Values)->Values->HdfProxy->UUID;
			}
			else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
				return static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(firstPatch->Values)->Values->HdfProxy->UUID;
			}
			else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__StringHdf5Array) {
				return static_cast<gsoap_resqml2_0_1::resqml2__StringHdf5Array*>(firstPatch->Values)->Values->HdfProxy->UUID;
			}
			else {
				return "";
			}
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}

	return "";
}

unsigned int AbstractProperty::getElementCountPerValue() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->Count;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::resqml2__IndexableElements AbstractProperty::getAttachmentKind() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->IndexableElement;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

bool AbstractProperty::isAssociatedToOneStandardEnergisticsPropertyKind() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->PropertyKind->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__StandardPropertyKind;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string AbstractProperty::getPropertyKindDescription() const
{
	if (isAssociatedToOneStandardEnergisticsPropertyKind()) {
		if (repository->getPropertyKindMapper() != nullptr) {
			return repository->getPropertyKindMapper()->getDescriptionOfResqmlStandardPropertyKindName(getEnergisticsPropertyKind());
		}
		else {
			throw std::invalid_argument("You must load the property kind mapping files if you want to get the parent property kind.");
		}
	}
	else {
		return getLocalPropertyKind()->getDescription();
	}
}

std::string AbstractProperty::getPropertyKindAsString() const
{
	if (isAssociatedToOneStandardEnergisticsPropertyKind()) {
		COMMON_NS::EnumStringMapper tmp;
		return tmp.getEnergisticsPropertyKindName(getEnergisticsPropertyKind());
	}
	else {
		return getLocalPropertyKind()->getTitle();
	}
}

std::string AbstractProperty::getPropertyKindParentAsString() const
{
	if (isAssociatedToOneStandardEnergisticsPropertyKind()) {
		if (repository->getPropertyKindMapper() != nullptr) {
			gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind propKindEnum = repository->getPropertyKindMapper()->getPropertyKindParentOfResqmlStandardPropertyKindName(getEnergisticsPropertyKind());
			COMMON_NS::EnumStringMapper tmp;
			return tmp.getEnergisticsPropertyKindName(propKindEnum);
		}
		else {
			throw std::invalid_argument("You must load the property kind mapping files if you want to get the parent property kind.");
		}
	}
	else {
		return getLocalPropertyKind()->getParentAsString();
	}
}

gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind AbstractProperty::getEnergisticsPropertyKind() const
{
	if (isAssociatedToOneStandardEnergisticsPropertyKind())
	{
		if (gsoapProxy2_0_1 != nullptr) {
			gsoap_resqml2_0_1::resqml2__AbstractProperty* prop = static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1);
			return static_cast<gsoap_resqml2_0_1::resqml2__StandardPropertyKind*>(prop->PropertyKind)->Kind;
		}
		else {
			throw logic_error("Not implemented yet");
		}
	}
	
	throw invalid_argument("The property kind of this property is not an Energistics one.");
}

void AbstractProperty::setLocalPropertyKind(PropertyKind* propKind)
{
	if (propKind == nullptr) {
		throw invalid_argument("The local property kind of this property cannot be null.");
	}

	// EPC
	propKind->propertySet.push_back(this);

	// XML
	if (updateXml) {
		setXmlLocalPropertyKind(propKind);
	}
}

gsoap_resqml2_0_1::eml20__DataObjectReference* AbstractProperty::getLocalPropertyKindDor() const
{
	if (!isAssociatedToOneStandardEnergisticsPropertyKind()) {
		if (gsoapProxy2_0_1 != nullptr) {
			gsoap_resqml2_0_1::resqml2__AbstractProperty* prop = static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1);
			return static_cast<gsoap_resqml2_0_1::resqml2__LocalPropertyKind*>(prop->PropertyKind)->LocalPropertyKind;
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

PropertyKind* AbstractProperty::getLocalPropertyKind() const
{
	return getRepository()->getDataObjectByUuid<PropertyKind>(getLocalPropertyKindUuid());
}

bool AbstractProperty::hasRealizationIndex() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->RealizationIndex != nullptr;
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
		return *static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->RealizationIndex;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractProperty::setRealizationIndex(ULONG64 realizationIndex)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractProperty* prop = static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1);
		if (prop->RealizationIndex == nullptr) {
			prop->RealizationIndex = static_cast<ULONG64*>(soap_malloc(prop->soap, sizeof(ULONG64)));
		}
		*prop->RealizationIndex = realizationIndex;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}
