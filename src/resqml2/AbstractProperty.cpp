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
#include <limits>
#include <stdexcept>

#include <hdf5.h>

#include "../common/EnumStringMapper.h"

#include "../eml2/AbstractHdfProxy.h"
#include "../eml2/PropertyKind.h"
#include "../eml2/TimeSeries.h"

#include "AbstractRepresentation.h"
#include "PropertySet.h"
#include "AbstractLocal3dCrs.h"

#include "../resqml2_0_1/PropertyKindMapper.h"

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
		convertDorIntoRel<AbstractLocal3dCrs>(dor);
	}

	dor = getPropertyKindDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<EML2_NS::PropertyKind>(dor);
	}

	for (unsigned int patchIndex = 0; patchIndex < getPatchCount(); ++patchIndex) {
		convertDorIntoRel(getHdfProxyDor(patchIndex));
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

	rep->getRepository()->addRelationship(this, rep);

	if (getRepository() == nullptr) {
		rep->getRepository()->addOrReplaceDataObject(this);
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

void AbstractProperty::setTimeIndices(uint64_t startTimeIndex, uint64_t countTimeIndices, EML2_NS::TimeSeries * ts, bool useInterval)
{
	if (countTimeIndices == 0) {
		throw std::invalid_argument("You cannot set zero time index.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		if (countTimeIndices > 1) {
			throw std::invalid_argument("RESQML 2.0.1 does not support more than one time index per property.");
		}

		static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex = gsoap_resqml2_0_1::soap_new_resqml20__TimeIndex(gsoapProxy2_0_1->soap);
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->Index = startTimeIndex;
	}
	else if (gsoapProxy2_3 != nullptr) {
		static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeIndices = gsoap_eml2_3::soap_new_eml23__TimeIndices(gsoapProxy2_3->soap);
		if (startTimeIndex != 0) {
			static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeIndices->TimeIndexStart = gsoap_eml2_3::soap_new_ULONG64(gsoapProxy2_3->soap);
			*static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeIndices->TimeIndexStart = startTimeIndex;
		}
		static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeIndices->TimeIndexCount = countTimeIndices;
		static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeIndices->UseInterval = useInterval;
	}
	else {
		throw logic_error("Not implemented yet");
	}

	setTimeSeries(ts);
}

unsigned int AbstractProperty::getTimeIndexStart() const
{
	uint64_t result = 0;

	if (gsoapProxy2_0_1 != nullptr) {
		if (static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex != nullptr) {
			result = static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->Index;
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		if (static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeIndices != nullptr &&
			static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeIndices->TimeIndexStart != nullptr) {
			result = *static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeIndices->TimeIndexStart;
		}
	}
	else {
		throw invalid_argument("This property does not have any timestamp.");
	}

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("The time index start is too big");
	}

	return static_cast<unsigned int>(result);
}

unsigned int AbstractProperty::getTimeIndicesCount() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex != nullptr
			? 1 : 0;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeIndices != nullptr
			? static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeIndices->TimeIndexCount
			: 0;
	}

	throw logic_error("Not implemented yet");
}

bool AbstractProperty::useInterval() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return false;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeIndices != nullptr
			? static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->TimeIndices->UseInterval
			: false;
	}

	throw logic_error("Not implemented yet");
}

unsigned int AbstractProperty::getElementCountPerValue() const
{
	uint64_t result;
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

std::vector<unsigned int> AbstractProperty::getRealizationIndices() const
{
	if (!hasRealizationIndices()) {
		throw invalid_argument("This property has not got any realization index");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return std::vector<unsigned int> {static_cast<unsigned int>(*static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1)->RealizationIndex)};
	}
	else if (gsoapProxy2_3 != nullptr) {
		std::vector<unsigned int> result(getCountOfIntegerArray(static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->RealizationIndices));
		readArrayNdOfUIntValues(static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->RealizationIndices, result.data());
		return result;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractProperty::setRealizationIndices(uint64_t startRealizationIndex, uint64_t countRealizationIndices)
{
	if (countRealizationIndices == 0) {
		throw std::invalid_argument("Cannot set zero realization index.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		if (countRealizationIndices > 1) {
			throw std::invalid_argument("RESQML 2.0.1 does not support more than one realization index per property.");
		}
		gsoap_resqml2_0_1::resqml20__AbstractProperty* prop = static_cast<gsoap_resqml2_0_1::resqml20__AbstractProperty*>(gsoapProxy2_0_1);
		if (prop->RealizationIndex == nullptr) {
			prop->RealizationIndex = static_cast<uint64_t*>(soap_malloc(prop->soap, sizeof(uint64_t)));
		}
		*prop->RealizationIndex = startRealizationIndex;
	}
	else if (gsoapProxy2_3 != nullptr) {
		auto rangeArray = gsoap_eml2_3::soap_new_eml23__IntegerRangeArray(gsoapProxy2_3->soap);
		rangeArray->Value = startRealizationIndex;
		rangeArray->Count = countRealizationIndices;
		static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->RealizationIndices = rangeArray;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractProperty::setRealizationIndices(const std::vector<unsigned int> & realizationIndices, EML2_NS::AbstractHdfProxy* hdfProxy)
{
	if (realizationIndices.empty()) {
		throw std::invalid_argument("Cannot set zero realization index.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		if (realizationIndices.size() > 1) {
			throw std::invalid_argument("RESQML 2.0.1 does not support more than one realization index per property.");
		}
		setRealizationIndices(realizationIndices[0], 1);
	}
	else if (gsoapProxy2_3 != nullptr) {
		if (hdfProxy == nullptr) {
			hdfProxy = getRepository()->getDefaultHdfProxy();
			if (hdfProxy == nullptr) {
				throw std::invalid_argument("A (default) HDF Proxy must be provided.");
			}
		}
		getRepository()->addRelationship(this, hdfProxy);

		auto externalArray = gsoap_eml2_3::soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
		externalArray->NullValue = (std::numeric_limits<unsigned int>::max)();
		externalArray->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
		auto dsPart = gsoap_eml2_3::soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
		dsPart->Count = realizationIndices.size();
		dsPart->StartIndex = 0;
		dsPart->EpcExternalPartReference = hdfProxy->newEml23Reference();
		dsPart->PathInExternalFile = getHdfGroup() + "/RealizationIndices";
		externalArray->Values->ExternalFileProxy.push_back(dsPart);
		static_cast<gsoap_eml2_3::resqml22__AbstractProperty*>(gsoapProxy2_3)->RealizationIndices = externalArray;

		// HDF
		hsize_t numValues = realizationIndices.size();
		hdfProxy->writeArrayNd(getHdfGroup(), "RealizationIndices", H5T_NATIVE_UINT, realizationIndices.data(), &numValues, 1);
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

unsigned int AbstractProperty::getValuesCountOfDimensionOfPatch(unsigned int dimIndex, unsigned int patchIndex) const
{
	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	std::vector<hsize_t> dims = hdfProxy->readArrayDimensions(dsPath);

	if (dimIndex < dims.size()) {
		return dims[dimIndex];
	}

	throw out_of_range("The dim index to get the count is out of range.");
}

unsigned int AbstractProperty::getDimensionsCountOfPatch(unsigned int patchIndex) const
{
	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	return hdfProxy->getDimensionCount(dsPath);
}

unsigned int AbstractProperty::getValuesCountOfPatch(unsigned int patchIndex) const
{
	int64_t nullValue = (numeric_limits<int64_t>::min)();
	std::string dsPath;
	EML2_NS::AbstractHdfProxy * hdfProxy = getDatasetOfPatch(patchIndex, nullValue, dsPath);

	return hdfProxy->getElementCount(dsPath);
}
